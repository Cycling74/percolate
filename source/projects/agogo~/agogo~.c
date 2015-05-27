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

#include "stk_c.h"
#include <math.h> 
#include "britestk.h"

void *agogo_class;

typedef struct _agogo
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
} t_agogo;

/****PROTOTYPES****/

//setup funcs
void *agogo_new(double val);
void agogo_free(t_agogo *x);
void agogo_dsp(t_agogo *x, t_signal **sp, short *count);
void agogo_float(t_agogo *x, double f);
t_int *agogo_perform(t_int *w);
void agogo_assist(t_agogo *x, void *b, long m, long a, char *s);

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
void main(void)
{
    setup((struct messlist **)&agogo_class, (method)agogo_new, (method)agogo_free, (short)sizeof(t_agogo), 0L, A_DEFFLOAT, 0);
    addmess((method)agogo_dsp, "dsp", A_CANT, 0);
    addmess((method)agogo_assist,"assist",A_CANT,0);
    addmess((method)agogo_noteon, "noteon", A_GIMME, 0);
    addmess((method)agogo_noteoff, "noteoff", A_GIMME, 0);
    addfloat((method)agogo_float);
    dsp_initclass();
    rescopy('STR#',9280);
}

void agogo_noteon(t_agogo *x)
{
	Modal4_noteOn(&x->modal, x->x_fr, x->x_sa);
}

void agogo_noteoff(t_agogo *x)
{
	Modal4_noteOff(&x->modal, x->x_sa);
}

void agogo_assist(t_agogo *x, void *b, long m, long a, char *s)
{
	assist_string(9280,m,a,1,7,s);
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

void *agogo_new(double initial_coeff)
{
	int i;
	char file[128];

    t_agogo *x = (t_agogo *)newobject(agogo_class);
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_agogo);i++)  
                ((char *)x)[i]=0; 
	} 
    dsp_setup((t_pxobject *)x,6);
    outlet_new((t_object *)x, "signal");
   
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
    
    return (x);
}

void agogo_free(t_agogo *x)
{
	dsp_free((t_pxobject *)x);
	HeaderSnd_free(&x->modal.wave);
	HeaderSnd_free(&x->modal.vibr);
}

void agogo_dsp(t_agogo *x, t_signal **sp, short *count)
{
	x->x_shconnected = count[0];
	x->x_sposconnected = count[1];
	x->x_saconnected = count[2];
	x->x_vfconnected = count[3];
	x->x_vaconnected = count[4];
	x->x_frconnected = count[5];
	x->srate = sp[0]->s_sr;
    x->one_over_srate = 1./x->srate;
	dsp_add(agogo_perform, 9, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[0]->s_n);	
	
}

t_int *agogo_perform(t_int *w)
{
	t_agogo *x = (t_agogo *)(w[1]);
	
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
	return w + 10;
}	
