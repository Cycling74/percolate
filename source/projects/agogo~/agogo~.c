/********************************************/
/*  Agogo SubClass of Modal4 Instrument		*/
/*  by Perry R. Cook, 1995-96               */ 
/*										  	*/
/*  ported to MSP by Dan Trueman, 2000	  	*/
/*                                          */
/*   Controls:    CONTROL1 = stickHardness  */
/*                CONTROL2 = strikePosition */
/*		  		  CONTROL3 = vibFreq       	*/
/*		  		  MOD_WHEEL= vibAmt        	*/
/********************************************/
//
// Updated for Max 7 by Darwin Grosse and Tim Place
// -------------------------------------------------

#include <math.h>
#include "stk_c.h"
#include "ext_obex.h"
#include "britestk.h"

typedef struct _agogo
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars
    t_float x_sh;			//stick hardness
    t_float x_spos;         //stick position
    t_float x_sa;           //amplitude
    t_float x_vf;           //vib freq
    t_float x_va;           //vib amount
    t_float x_fr;			//frequency

    t_float fr_save, sh_save, spos_save, sa_save;
    
    Modal4 modal;
    
    //signals connected? or controls...
    long x_shconnected;
    long x_sposconnected;
    long x_saconnected;
    long x_vfconnected;
    long x_vaconnected;
    long x_frconnected;

    //stuff
    long multiStrike;
    t_float srate, one_over_srate;
} t_agogo;

static t_class *agogo_class = NULL;

/****PROTOTYPES****/
//setup funcs
void *agogo_new(double val);
void agogo_free(t_agogo *x);
void agogo_assist(t_agogo *x, void *b, long m, long a, char *s);

void agogo_float(t_agogo *x, double f);

void agogo_dsp64(t_agogo *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void agogo_perform64(t_agogo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

//vib funcs
void setVibFreq(t_agogo *x, float freq);
float vib_tick(t_agogo *x);

//agogo functions
void Agogo_setStickHardness(t_agogo *x, float hardness);
void Agogo_setStrikePosition(t_agogo *x, float position);
void agogo_noteon(t_agogo *x);
void agogo_noteoff(t_agogo *x);


/****FUNCTIONS****/
void Agogo_setStickHardness(t_agogo *x, float hardness)
{
  x->x_sh = hardness;
  HeaderSnd_setRate(&x->modal.wave, 3. + 8. * hardness);
  x->modal.masterGain =  1.;
}

void Agogo_setStrikePosition(t_agogo *x, float position)
{
  float temp,temp2;
  temp2 = position * PI;
  x->x_spos = position;                        /*  Hack only first three modes */
  temp = sin(0.7*temp2);
  Modal4_setFiltGain(&x->modal, 0, .08 * temp);      /*  1st mode function of pos.   */                            
  temp = sin(.1 + 5. * temp2);
  Modal4_setFiltGain(&x->modal, 1, .07 * temp);     /*  2nd mode function of pos.   */
  temp = sin(.2 + 7. * temp2);
  Modal4_setFiltGain(&x->modal, 2, .04 * temp);      /*  3rd mode function of pos.   */
}

//primary MSP funcs
void ext_main(void* p)
{
    t_class *c = class_new("agogo~", (method)agogo_new, (method)agogo_free, (long)sizeof(t_agogo), 0L, A_DEFFLOAT, 0);
    
    class_addmethod(c, (method)agogo_float, "float", A_FLOAT, 0);
    class_addmethod(c, (method)agogo_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)agogo_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)agogo_noteon, "noteon", A_GIMME, 0);
    class_addmethod(c, (method)agogo_noteoff, "noteoff", A_GIMME, 0);
    
    class_dspinit(c);
    class_register(CLASS_BOX, c);
    agogo_class = c;
    // rescopy('STR#',9280);
}

void *agogo_new(double initial_coeff)
{
	int i;
	char file[128];
    
    t_agogo *x = (t_agogo *)object_alloc(agogo_class);
    if (x) {
        for(i=sizeof(t_pxobject);i<sizeof(t_agogo);i++)
            ((char *)x)[i]=0;

        dsp_setup((t_pxobject *)x, 6);
        outlet_new(x, "signal");
        
        x->srate = sys_getsr();
        x->one_over_srate = 1./x->srate;
        
        Modal4_init(&x->modal, x->srate);
        strcpy(file, RAWWAVE_PATH);
        HeaderSnd_alloc(&x->modal.wave, britestk, 2048, "oneshot");
        HeaderSnd_setRate(&x->modal.wave, 7.);				/*  normal stick  */
        
        Modal4_setRatioAndReson(&x->modal, 0, 1.00, 0.999);
        Modal4_setRatioAndReson(&x->modal, 1, 4.08, 0.999);
        Modal4_setRatioAndReson(&x->modal, 2, 6.669, 0.999);
        Modal4_setRatioAndReson(&x->modal, 3, -3725., 0.999);
        Modal4_setFiltGain(&x->modal, 0, .06);
        Modal4_setFiltGain(&x->modal, 1, .05);
        Modal4_setFiltGain(&x->modal, 2, .03);
        Modal4_setFiltGain(&x->modal, 3, .02);
        x->modal.directGain = 0.25;
        x->multiStrike = 0;
        x->modal.masterGain = 1.;
        
        x->fr_save = x->x_fr;
        
        post("agogo...");
	}
    return (x);
}

void agogo_free(t_agogo *x)
{
	dsp_free((t_pxobject *)x);
	HeaderSnd_free(&x->modal.wave);
	HeaderSnd_free(&x->modal.vibr);
}

void agogo_assist(t_agogo *x, void *b, long m, long a, char *s)
{
	switch(m) {
		case 1: // inlet
			switch(a) {
				case 0:
                    sprintf(s, "(float) stick hardness");
                    break;
				case 1:
                    sprintf(s, "(float) stick position");
                    break;
				case 2:
                    sprintf(s, "(float) amplitude");
                    break;
				case 3:
                    sprintf(s, "(float) vib frequency");
                    break;
				case 4:
                    sprintf(s, "(float) vib amplitude");
                    break;
				case 5:
                    sprintf(s, "(float) frequency");
                    break;
			}
            break;
		case 2: // outlet
			switch(a) {
				case 0:
                    sprintf(s, "(signal) output");
                    break;
			}
            break;
	}
}

void agogo_float(t_agogo *x, double f)
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

void agogo_noteon(t_agogo *x)
{
	Modal4_noteOn(&x->modal, x->x_fr, x->x_sa);
}

void agogo_noteoff(t_agogo *x)
{
	Modal4_noteOff(&x->modal, x->x_sa);
}

void agogo_dsp64(t_agogo *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->x_shconnected = count[0];
	x->x_sposconnected = count[1];
	x->x_saconnected = count[2];
	x->x_vfconnected = count[3];
	x->x_vaconnected = count[4];
	x->x_frconnected = count[5];

	x->srate = samplerate;
    x->one_over_srate = 1./x->srate;
    object_method(dsp64, gensym("dsp_add64"), x, agogo_perform64, 0, NULL);
}

void agogo_perform64(t_agogo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	float sh = x->x_shconnected ? *(float *)(ins[0]) : x->x_sh;
	float spos = x->x_sposconnected ? *(float *)(ins[1]) : x->x_spos;
	float sa = x->x_saconnected ? *(float *)(ins[2]) : x->x_sa;
	float vf = x->x_vfconnected ? *(float *)(ins[3]) : x->x_vf;
	float va = x->x_vaconnected ? *(float *)(ins[4]) : x->x_va;
	float fr = x->x_frconnected ? *(float *)(ins[5]) : x->x_fr;
    
    t_double *out = outs[0];
    long n = sampleframes;
    
    if (fr != x->fr_save) {
		Modal4_setFreq(&x->modal, fr);
		x->fr_save = fr;
	}
	
	if(sh != x->sh_save) {
		Agogo_setStickHardness(x, sh);
		x->sh_save = sh;
	}
	
	if(spos != x->spos_save) {
		Agogo_setStrikePosition(x, spos);
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
