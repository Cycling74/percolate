/********************************************/
/*  Marimba SubClass of Modal4 Instrument,  */
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

void *marimba_class;

typedef struct _marimba
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
} t_marimba;

/****PROTOTYPES****/

//setup funcs
void *marimba_new(double val);
void marimba_free(t_marimba *x);
void marimba_dsp(t_marimba *x, t_signal **sp, short *count);
void marimba_float(t_marimba *x, double f);
t_int *marimba_perform(t_int *w);
void marimba_assist(t_marimba *x, void *b, long m, long a, char *s);

//vib funcs
void setVibFreq(t_marimba *x, float freq);
float vib_tick(t_marimba *x);

//marimba functions
void Marimba_setStickHardness(t_marimba *x, float hardness);
void Marimba_setStrikePosition(t_marimba *x, float position);
void Marimba_strike(t_marimba *x, float amplitude);
void marimba_noteon(t_marimba *x);
void marimba_noteoff(t_marimba *x);


/****FUNCTIONS****/
void Marimba_setStickHardness(t_marimba *x, float hardness)
{
  x->x_sh = hardness;
  HeaderSnd_setRate(&x->modal.wave, (0.25 *  pow(4.0,x->x_sh)));
  x->modal.masterGain =  0.1 + (1.8 * x->x_sh);
}

void Marimba_setStrikePosition(t_marimba *x, float position)
{
  float temp,temp2;
  temp2 = position * PI;
  x->x_spos = position;                        /*  Hack only first three modes */
  temp = sin(temp2);
  Modal4_setFiltGain(&x->modal, 0, .12 * temp);      /*  1st mode function of pos.   */                            
  temp = sin(0.05 + (3.9 * temp2));
  Modal4_setFiltGain(&x->modal, 1, -.03 * temp);     /*  2nd mode function of pos.   */
  temp = sin(-0.05 + (11. * temp2));
  Modal4_setFiltGain(&x->modal, 2, .11 * temp);      /*  3rd mode function of pos.   */
}

void Marimba_strike(t_marimba *x, float amplitude)
{
  int temp;
  temp = rand() >> 10;
  if (temp < 2) {
    x->multiStrike = 1;
  }
  else if (temp < 1) {
    x->multiStrike = 2;
  }
  else x->multiStrike = 0;
  Modal4_strike(&x->modal, amplitude);
}

//primary MSP funcs
void main(void)
{
    setup((struct messlist **)&marimba_class, (method)marimba_new, (method)marimba_free, (short)sizeof(t_marimba), 0L, A_DEFFLOAT, 0);
    addmess((method)marimba_dsp, "dsp", A_CANT, 0);
    addmess((method)marimba_assist,"assist",A_CANT,0);
    addmess((method)marimba_noteon, "noteon", A_GIMME, 0);
    addmess((method)marimba_noteoff, "noteoff", A_GIMME, 0);
    addfloat((method)marimba_float);
    dsp_initclass();
    rescopy('STR#',9278);
}

void marimba_noteon(t_marimba *x)
{
	Modal4_noteOn(&x->modal, x->x_fr, x->x_sa);
}

void marimba_noteoff(t_marimba *x)
{
	Modal4_noteOff(&x->modal, x->x_sa);
}

void marimba_assist(t_marimba *x, void *b, long m, long a, char *s)
{
	assist_string(9278,m,a,1,7,s);
}

void marimba_float(t_marimba *x, double f)
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

void *marimba_new(double initial_coeff)
{
	int i;
	char file[128];

    t_marimba *x = (t_marimba *)newobject(marimba_class);
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_marimba);i++)  
                ((char *)x)[i]=0; 
	} 
    dsp_setup((t_pxobject *)x,6);
    outlet_new((t_object *)x, "signal");
   
   	x->srate = sys_getsr();
    x->one_over_srate = 1./x->srate;
    
    Modal4_init(&x->modal, x->srate);
  	//strcpy(file, RAWWAVE_PATH);
  	HeaderSnd_alloc(&x->modal.wave, marmstk1, 256, "oneshot");
	HeaderSnd_setRate(&x->modal.wave, .5);				/*  normal stick  */
	
	Modal4_setRatioAndReson(&x->modal, 0, 1.00, 0.9996);
	Modal4_setRatioAndReson(&x->modal, 1, 3.99, 0.9994);
	Modal4_setRatioAndReson(&x->modal, 2, 10.65, 0.9994);
	Modal4_setRatioAndReson(&x->modal, 3, 2443.0, 0.999);
	Modal4_setFiltGain(&x->modal, 0, .04);
	Modal4_setFiltGain(&x->modal, 1, .01);
	Modal4_setFiltGain(&x->modal, 2, .01);
	Modal4_setFiltGain(&x->modal, 3, .008);
  	x->modal.directGain = 0.1;
  	x->multiStrike = 0;

    x->fr_save = x->x_fr;
    
    post("marimba...");
    
    return (x);
}

void marimba_free(t_marimba *x)
{
	dsp_free((t_pxobject *)x);
	HeaderSnd_free(&x->modal.wave);
	HeaderSnd_free(&x->modal.vibr);
}

void marimba_dsp(t_marimba *x, t_signal **sp, short *count)
{
	x->x_shconnected = count[0];
	x->x_sposconnected = count[1];
	x->x_saconnected = count[2];
	x->x_vfconnected = count[3];
	x->x_vaconnected = count[4];
	x->x_frconnected = count[5];
	x->srate = sp[0]->s_sr;
    x->one_over_srate = 1./x->srate;
	dsp_add(marimba_perform, 9, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[0]->s_n);	
	
}

t_int *marimba_perform(t_int *w)
{
	t_marimba *x = (t_marimba *)(w[1]);
	
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
		Marimba_setStickHardness(x, sh);
		x->sh_save = sh;
	}
	
	if(spos != x->spos_save) {
		Marimba_setStrikePosition(x, spos);
		x->spos_save = spos;
	}
	
	if(sa != x->sa_save) {
		Marimba_strike(x, sa);
		x->sa_save = sa;
	}
	
	HeaderSnd_setFreq(&x->modal.vibr, vf, x->srate);
	x->modal.vibrGain = va;

	while(n--) {
		
		if (x->multiStrike > 0) {
			if(x->modal.wave.finished) {
				HeaderSnd_reset(&x->modal.wave);
				x->multiStrike -= 1;
			}
		}
		
		*out++ = Modal4_tick(&x->modal);
	}
	return w + 10;
}	
