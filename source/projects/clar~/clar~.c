/******************************************/
/*  Clarinet model ala Smith              */
/*  after McIntyre, Schumacher, Woodhouse */
/*  by Perry Cook, 1995-96                */
/*										  */
/*  ported to MSP by Dan Trueman, 2000	  */
/*                                        */
/*  This is a waveguide model, and thus   */
/*  relates to various Stanford Univ.     */
/*  and possibly Yamaha and other patents.*/
/*                                        */
/*   Controls:    CONTROL1 = reedStiffns  */
/*                CONTROL2 = noiseGain    */
/*                CONTROL3 = vibFreq      */
/*                MOD_WHEEL= vibAmt       */
/******************************************/

#include "stk_c.h"
#include <math.h> 
#define LENGTH 2205	//44100/LOWFREQ + 1 --clar length
#define VIBLENGTH 1024

void *clar_class;

typedef struct _clar
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars
    float reedStiffness;
    float noiseGain;
    float vibrGain;
    float maxPressure;
    float x_vf; 		//vib freq
    float x_fr;			//frequency	
    
    float reedStiffness_save;
    float fr_save;
    
    //signals connected? or controls...
    short x_rsconnected;
    short x_ngconnected;
    short x_vgconnected;
    short x_mpconnected;
    short x_vfconnected;
    short x_frconnected;

    //delay line
    DLineL delayLine;
    
    //lip filter
    ReedTabl reedTable;
    
    //one zero filter
    OneZero filter;
    
    //vibrato table
    float vibTable[VIBLENGTH];
    float vibRate;
    float vibTime;
    
    //stuff
    float srate, one_over_srate;
} t_clar;

/****PROTOTYPES****/

//setup funcs
void *clar_new(double val);
void clar_free(t_clar *x);
void clar_dsp(t_clar *x, t_signal **sp, short *count);
void clar_float(t_clar *x, double f);
t_int *clar_perform(t_int *w);
void clar_assist(t_clar *x, void *b, long m, long a, char *s);

//vib funcs
void setVibFreq(t_clar *x, float freq);
float vib_tick(t_clar *x);

//clar functions
void setFreq(t_clar *x, float frequency);


/****FUNCTIONS****/

void setFreq(t_clar *x, float frequency)
{
   if(frequency < 20.) frequency = 20.;
  /* length - approx filter delay */
  DLineL_setDelay(&x->delayLine,
  	(x->srate / frequency) * .5 - 1.5);	
}

//vib funcs
void setVibFreq(t_clar *x, float freq)
{
	x->vibRate = VIBLENGTH * x->one_over_srate * freq;
}

float vib_tick(t_clar *x)
{
	long temp;
	float temp_time, alpha, output;
	
	x->vibTime += x->vibRate;
	while (x->vibTime >= (float)VIBLENGTH) x->vibTime -= (float)VIBLENGTH;
	while (x->vibTime < 0.) x->vibTime += (float)VIBLENGTH;
	
	temp_time = x->vibTime;
	
	temp = (long) temp_time;
	alpha = temp_time - (float)temp;
	output = x->vibTable[temp];
	output = output + (alpha * (x->vibTable[temp+1] - output));
	return output;
}

//primary MSP funcs
void main(void)
{
    setup((struct messlist **)&clar_class, (method)clar_new, (method)clar_free, (short)sizeof(t_clar), 0L, A_DEFFLOAT, 0);
    addmess((method)clar_dsp, "dsp", A_CANT, 0);
    addmess((method)clar_assist,"assist",A_CANT,0);
    addfloat((method)clar_float);
    dsp_initclass();
    rescopy('STR#',32486);
}

void clar_assist(t_clar *x, void *b, long m, long a, char *s)
{
	assist_string(32486,m,a,1,7,s);
}

void clar_float(t_clar *x, double f)
{
	if (x->x_obj.z_in == 0) {
		x->reedStiffness = f;
	} else if (x->x_obj.z_in == 1) {
		x->noiseGain = f;
	} else if (x->x_obj.z_in == 2) {
		x->vibrGain = f;
	} else if (x->x_obj.z_in == 3) {
		x->maxPressure = f;
	} else if (x->x_obj.z_in == 4) {
		x->x_vf = f;
	} else if (x->x_obj.z_in == 5) {
		x->x_fr = f;
	}
}

void *clar_new(double initial_coeff)
{
	int i;

    t_clar *x = (t_clar *)newobject(clar_class);
     //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_clar);i++)  
                ((char *)x)[i]=0; 
	} 
    dsp_setup((t_pxobject *)x,6);
    outlet_new((t_object *)x, "signal");
    x->reedStiffness = 0.5;
    x->noiseGain = 0.2;
    x->vibrGain = 0.1;
    x->maxPressure = 0.05;
    
    x->reedTable.offSet = .7;
    x->reedTable.slope = -.3;
    
    x->srate = sys_getsr();
    x->one_over_srate = 1./x->srate;
    
    DLineL_alloc(&x->delayLine, LENGTH);
    
    for(i=0; i<VIBLENGTH; i++) x->vibTable[i] = sin(i*TWO_PI/VIBLENGTH);
    x->vibRate = 1.;
    x->vibTime = 0.;
    
    //clear stuff
    DLineL_clear(&x->delayLine);
    ReedTabl_init(&x->reedTable);
    
    //initialize things
    DLineL_setDelay(&x->delayLine, 100.);
    OneZero_init(&x->filter);

    setFreq(x, x->x_fr);
    setVibFreq(x, 5.925);

    x->fr_save = x->x_fr;
    
    x->x_vf = 5.; 		//vib freq
    x->x_fr = 500.;		//frequency	
	x->reedStiffness_save = 0.5;
    
    
    post("just try to sound like Beeny Goodman!");
    
    return (x);
}

void clar_free(t_clar *x)
{
	dsp_free((t_pxobject *)x);
	DLineL_free(&x->delayLine);
}

void clar_dsp(t_clar *x, t_signal **sp, short *count)
{
	x->x_rsconnected = count[0];
	x->x_ngconnected = count[1];
	x->x_vgconnected = count[2];
	x->x_mpconnected = count[3];
	x->x_vfconnected = count[4];
	x->x_frconnected = count[5];
	x->srate = sp[0]->s_sr;
    x->one_over_srate = 1./x->srate;
	dsp_add(clar_perform, 9, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[0]->s_n);	
	
}

t_int *clar_perform(t_int *w)
{
	t_clar *x = (t_clar *)(w[1]);

	float reedStiffness		= x->x_rsconnected? *(float *)(w[2]) : x->reedStiffness;
	float noiseGain		 	= x->x_ngconnected? *(float *)(w[3]) : x->noiseGain;
	float vibrGain 			= x->x_vgconnected? *(float *)(w[4]) : x->vibrGain;
	float maxPressure		= x->x_mpconnected? *(float *)(w[5]) : x->maxPressure;
	float vf 				= x->x_vfconnected? *(float *)(w[6]) : x->x_vf;
	float fr 				= x->x_frconnected? *(float *)(w[7]) : x->x_fr;
	
	float *out = (float *)(w[8]);
	long n = w[9];
	
	float temp, breathPressure, pressureDiff;	

	if(fr != x->fr_save) {
		setFreq(x,  fr);
		x->fr_save = fr;
	}
	
	x->reedTable.slope = reedStiffness;
	
	x->vibRate = VIBLENGTH * x->one_over_srate * vf; 

	while(n--) {
		breathPressure = maxPressure + maxPressure * noiseGain * Noise_tick();;
  		breathPressure += breathPressure * vibrGain * vib_tick(x);

		pressureDiff = OneZero_tick(&x->filter, x->delayLine.lastOutput);	/* differential pressure  */    
  		pressureDiff = (pressureDiff * -0.95) - breathPressure; 			/* of reflected and mouth */
  		*out++ = DLineL_tick(&x->delayLine, breathPressure +                				/* perform scattering     */
                 pressureDiff * ReedTabl_lookup(&x->reedTable, pressureDiff)); 			/* in economical way      */
	}
	return w + 10;
}	
