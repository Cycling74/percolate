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

#include "stk_c.h"
#include <math.h> 
#include "marmstk1.h"

void *vibraphone_class;

typedef struct _vibraphone
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars
    float x_sh;			//stick hardness	
    float x_spos;		//stick position
    float x_sa; 		//amplitude
    float x_vf; 		//vib freq
    float x_va; 		//vib amount
    float x_fr;			//frequency	

    float fr_save, sh_save, spos_save, sa_save;
    
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
    float srate, one_over_srate;
} t_vibraphone;

/****PROTOTYPES****/

//setup funcs
void *vibraphone_new(double val);
void vibraphone_free(t_vibraphone *x);
void vibraphone_dsp(t_vibraphone *x, t_signal **sp, short *count);
void vibraphone_float(t_vibraphone *x, double f);
t_int *vibraphone_perform(t_int *w);
void vibraphone_assist(t_vibraphone *x, void *b, long m, long a, char *s);

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
void main(void)
{
    setup((struct messlist **)&vibraphone_class, (method)vibraphone_new, (method)vibraphone_free, (short)sizeof(t_vibraphone), 0L, A_DEFFLOAT, 0);
    addmess((method)vibraphone_dsp, "dsp", A_CANT, 0);
    addmess((method)vibraphone_assist,"assist",A_CANT,0);
    addmess((method)vibraphone_noteon, "noteon", A_GIMME, 0);
    addmess((method)vibraphone_noteoff, "noteoff", A_GIMME, 0);
    addfloat((method)vibraphone_float);
    dsp_initclass();
    rescopy('STR#',9279);
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
	assist_string(9279,m,a,1,7,s);
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

    t_vibraphone *x = (t_vibraphone *)newobject(vibraphone_class);
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

void vibraphone_dsp(t_vibraphone *x, t_signal **sp, short *count)
{
	x->x_shconnected = count[0];
	x->x_sposconnected = count[1];
	x->x_saconnected = count[2];
	x->x_vfconnected = count[3];
	x->x_vaconnected = count[4];
	x->x_frconnected = count[5];
	x->srate = sp[0]->s_sr;
    x->one_over_srate = 1./x->srate;
	dsp_add(vibraphone_perform, 9, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[0]->s_n);	
	
}

t_int *vibraphone_perform(t_int *w)
{
	t_vibraphone *x = (t_vibraphone *)(w[1]);
	
	float sh = x->x_shconnected? *(float *)(w[2]) : x->x_sh;
	float spos = x->x_sposconnected? *(float *)(w[3]) : x->x_spos;
	float sa = x->x_saconnected? *(float *)(w[4]) : x->x_sa;
	float vf = x->x_vfconnected? *(float *)(w[5]) : x->x_vf;
	float va = x->x_vaconnected? *(float *)(w[6]) : x->x_va;
	float fr = x->x_frconnected? *(float *)(w[7]) : x->x_fr;
	
	float *out = (float *)(w[8]);
	long n = w[9];	

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
	return w + 10;
}	
