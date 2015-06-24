/********************************************/
/*  Vibraphone SubClass of Modal4 Instrument*/
/*  by Perry R. Cook, 1995-96               */ 
/*										  	*/
/*  ported to MSP by Dan Trueman, 2000	  	*/
/*                                          */
/*   Controls:    CONTROL1 = stickHardness  */
/*                CONTROL2 = strikePosition */
/*		  		  CONTROL3 = vibFreq       	*/
/*		  		  MOD_WHEEL= vibAmt        	*/
/********************************************/

// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include "stk_c.h"
#include <math.h> 
#include "marmstk1.h"

t_class *vibraphone_class;

typedef struct _vibraphone
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars
    t_double x_sh;			//stick hardness	
    t_double x_spos;		//stick position
    t_double x_sa; 		//amplitude
    t_double x_vf; 		//vib freq
    t_double x_va; 		//vib amount
    t_double x_fr;			//frequency	

    t_double fr_save, sh_save, spos_save, sa_save;
    
    Modal4 modal;
    
    //signals connected? or controls...
    short x_shconnected;
    short x_sposconnected;
    short x_saconnected;
    short x_vfconnected;
    short x_vaconnected;
    short x_frconnected;

    //stuff
    int multiStrike;
    t_double srate, one_over_srate;
} t_vibraphone;

/****PROTOTYPES****/

//setup funcs
void *vibraphone_new(double val);
void vibraphone_free(t_vibraphone *x);
void vibraphone_assist(t_vibraphone *x, void *b, long m, long a, char *s);

// dsp stuff
void vibraphone_dsp64(t_vibraphone *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void vibraphone_perform64(t_vibraphone *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void vibraphone_float(t_vibraphone *x, double f);

//vib funcs
void setVibFreq(t_vibraphone *x, float freq);
float vib_tick(t_vibraphone *x);

//vibraphone functions
void Vibraphone_setStickHardness(t_vibraphone *x, float hardness);
void Vibraphone_setStrikePosition(t_vibraphone *x, float position);
void vibraphone_noteon(t_vibraphone *x);
void vibraphone_noteoff(t_vibraphone *x);


/****FUNCTIONS****/
void Vibraphone_setStickHardness(t_vibraphone *x, float hardness)
{
  x->x_sh = hardness;
  HeaderSnd_setRate(&x->modal.wave, 2. + 22.66 * hardness);
  x->modal.masterGain =  0.2 + (1.6 * hardness);
}

void Vibraphone_setStrikePosition(t_vibraphone *x, float position)
{
  float temp,temp2;
  temp2 = position * PI;
  x->x_spos = position;                        /*  Hack only first three modes */
  temp = sin(temp2);
  Modal4_setFiltGain(&x->modal, 0, .025 * temp);      /*  1st mode function of pos.   */                            
  temp = sin(0.1 + (2.01 * temp2));
  Modal4_setFiltGain(&x->modal, 1, .015 * temp);     /*  2nd mode function of pos.   */
  temp = sin(3.95 * temp2);
  Modal4_setFiltGain(&x->modal, 2, .015 * temp);      /*  3rd mode function of pos.   */
}

//primary MSP funcs
void ext_main(void* p)
{
    t_class *c = class_new("vibraphone~", (method)vibraphone_new, (method)vibraphone_free, (long)sizeof(t_vibraphone), 0L, A_DEFFLOAT, 0);
    
    class_addmethod(c, (method)vibraphone_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)vibraphone_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)vibraphone_noteon, "noteon", A_GIMME, 0);
    class_addmethod(c, (method)vibraphone_noteoff, "noteoff", A_GIMME, 0);
    class_addmethod(c, (method)vibraphone_float, "float", A_FLOAT, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    vibraphone_class = c;
}

void vibraphone_noteon(t_vibraphone *x)
{
	Modal4_noteOn(&x->modal, x->x_fr, x->x_sa);
}

void vibraphone_noteoff(t_vibraphone *x)
{
	Modal4_noteOff(&x->modal, x->x_sa);
}

void vibraphone_assist(t_vibraphone *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
            case 0:
                sprintf(s,"(signal/float) stick hardness");
                break;
            case 1:
                sprintf(s,"(signal/float) stick position");
                break;
            case 2:
                sprintf(s,"(signal/float) stick amplitude");
                break;
            case 3:
                sprintf(s,"(signal/float) vibrato frequency");
                break;
            case 4:
                sprintf(s,"(signal/float) vibrato amount");
                break;
            case 5:
                sprintf(s,"(signal/float) frequency");
                break;
        }
	} else {
		sprintf(s,"(signal) output");
    }
}

void vibraphone_float(t_vibraphone *x, double f)
{
	if (x->x_obj.z_in == 0) {
		x->x_sh = f;
	} else if (x->x_obj.z_in == 1) {
		x->x_spos = f;
	} else if (x->x_obj.z_in == 2) {
		x->x_sa = f;
	} else if (x->x_obj.z_in == 3) {
		x->x_vf = f;
	} else if (x->x_obj.z_in == 4) {
		x->x_va = f;
	} else if (x->x_obj.z_in == 5) {
		x->x_fr = f;
	}
}

void *vibraphone_new(double initial_coeff)
{
	int i;
	char file[128];

    t_vibraphone *x = (t_vibraphone *)object_alloc(vibraphone_class);
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_vibraphone);i++)  
                ((char *)x)[i]=0; 
	} 
    dsp_setup((t_pxobject *)x,6);
    outlet_new((t_object *)x, "signal");
   
   	x->srate = sys_getsr();
    x->one_over_srate = 1./x->srate;
    
    Modal4_init(&x->modal, x->srate);
  	strcpy(file, RAWWAVE_PATH);
  	HeaderSnd_alloc(&x->modal.wave, marmstk1, 256, "oneshot");
	HeaderSnd_setRate(&x->modal.wave, 13.33);				/*  normal stick  */
	
	Modal4_setRatioAndReson(&x->modal, 0, 1.00, 0.99995);
	Modal4_setRatioAndReson(&x->modal, 1, 2.01, 0.99991);
	Modal4_setRatioAndReson(&x->modal, 2, 3.9, 0.99992);
	Modal4_setRatioAndReson(&x->modal, 3, 14.37, 0.99990);
	Modal4_setFiltGain(&x->modal, 0, .025);
	Modal4_setFiltGain(&x->modal, 1, .015);
	Modal4_setFiltGain(&x->modal, 2, .015);
	Modal4_setFiltGain(&x->modal, 3, .015);
  	x->modal.directGain = 0.0;
  	x->multiStrike = 0;
  	x->modal.masterGain = 1.;

    x->fr_save = x->x_fr;
    
    post("vibraphone...");
    
    return (x);
}

void vibraphone_free(t_vibraphone *x)
{
	dsp_free((t_pxobject *)x);
	HeaderSnd_free(&x->modal.wave);
	HeaderSnd_free(&x->modal.vibr);
}


void vibraphone_dsp64(t_vibraphone *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->x_shconnected = count[0];
	x->x_sposconnected = count[1];
	x->x_saconnected = count[2];
	x->x_vfconnected = count[3];
	x->x_vaconnected = count[4];
	x->x_frconnected = count[5];
	x->srate = samplerate;
    x->one_over_srate = 1./x->srate;
    
    object_method(dsp64, gensym("dsp_add64"), x, vibraphone_perform64, 0, NULL);
}

void vibraphone_perform64(t_vibraphone *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double sh = x->x_shconnected      ? *(t_double *)(ins[0]) : x->x_sh;
	t_double spos = x->x_sposconnected  ? *(t_double *)(ins[1]) : x->x_spos;
	t_double sa = x->x_saconnected      ? *(t_double *)(ins[2]) : x->x_sa;
	t_double vf = x->x_vfconnected      ? *(t_double *)(ins[3]) : x->x_vf;
	t_double va = x->x_vaconnected      ? *(t_double *)(ins[4]) : x->x_va;
	t_double fr = x->x_frconnected      ? *(t_double *)(ins[5]) : x->x_fr;
	
	t_double *out = (t_double *)(outs[0]);
	long n = sampleframes;
    
	if(fr != x->fr_save) {
		Modal4_setFreq(&x->modal, fr);
		x->fr_save = fr;
	}
	
	if(sh != x->sh_save) {
		Vibraphone_setStickHardness(x, sh);
		x->sh_save = sh;
	}
	
	if(spos != x->spos_save) {
		Vibraphone_setStrikePosition(x, spos);
		x->spos_save = spos;
	}
	
	if(sa != x->sa_save) {
		Modal4_strike(&x->modal, sa);
		x->sa_save = sa;
	}
	
	HeaderSnd_setFreq(&x->modal.vibr, vf, x->srate);
	x->modal.vibrGain = va;
    
	while(n--) {
        
		*out++ = Modal4_tick(&x->modal);
	}
}

