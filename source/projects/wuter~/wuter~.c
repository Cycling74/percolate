//reallly the wuter drops, not wuter

#include "ext.h"
#include "z_dsp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TWO_PI 6.283185307
//#define ONE_OVER_RANDLIMIT 0.00006103516 // constant = 1. / 16384.0
#define ONE_OVER_RANDLIMIT 1./RAND_MAX
//#define RANDNORM .000030519
#define RANDNORM 0.5/(RAND_MAX)
#define ATTACK 0
#define DECAY 1
#define SUSTAIN 2
#define RELEASE 3
#define MAX_RANDOM RAND_MAX
#define MAX_SHAKE 1.0

#define BAMB_SOUND_DECAY 0.95
#define BAMB_SYSTEM_DECAY 0.99995
#define BAMB_NUM_TUBES 5
#define BAMB_BASE_FREQ  2800

void *wuter_class;

typedef struct _wuter
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars	    
	float shakeEnergy;
	float input,output[2];
	float coeffs[2];
	float input1,output1[2];
	float coeffs1[2];
	float input2,output2[2];
	float coeffs2[2];
	float sndLevel;
	float gain, gain1, gain2;
	float soundDecay;
	float systemDecay;
	float freq, freq1, freq2;

	long  num_objects;
    float shake_damp;
    float shake_max;
	float res_freq;
	float res_spread;
	float res_random;
	    
    long num_objectsSave;	//number of beans	
    float res_freqSave;	//resonance
    float shake_dampSave; 	//damping
    float shake_maxSave;

	float totalEnergy;
	float finalZ[3];	
    
    //signals connected? or controls...
    short num_objectsConnected;
    short res_freqConnected;
    short shake_dampConnected;
    short shake_maxConnected;
    
    float pandropL, pandropR;
   
    float srate, one_over_srate;
} t_wuter;

/****PROTOTYPES****/

//setup funcs
void *wuter_new(double val);
void wuter_dsp(t_wuter *x, t_signal **sp, short *count);
void wuter_float(t_wuter *x, double f);
void wuter_int(t_wuter *x, int f);
void wuter_bang(t_wuter *x);
t_int *wuter_perform(t_int *w);
void wuter_assist(t_wuter *x, void *b, long m, long a, char *s);

void wuter_setup(t_wuter *x);
float wuter_tick(t_wuter *x);

//noise maker
float noise_tick();
int my_random(int max) ;

/****FUNCTIONS****/

#define WUTR_SOUND_DECAY 0.95
#define WUTR_NUM_SOURCES 4
#define WUTR_FILT_POLE   0.9985
#define WUTR_FREQ_SWEEP  1.0001
#define WUTR_BASE_FREQ  600

void wuter_setup(t_wuter *x)  {
  x->num_objects = x->num_objectsSave = WUTR_NUM_SOURCES;
  x->soundDecay = WUTR_SOUND_DECAY;
  x->res_spread = 0.25;
  x->res_random = 0.25;
  x->freq =  WUTR_BASE_FREQ * TWO_PI / x->srate;
  x->freq1 = WUTR_BASE_FREQ * 2.0 * TWO_PI / x->srate;
  x->freq2 = WUTR_BASE_FREQ * 3.0 * TWO_PI / x->srate;
  x->coeffs[0]  = -WUTR_FILT_POLE * 2.0 * cos(x->freq);
  x->coeffs[1]  = WUTR_FILT_POLE * WUTR_FILT_POLE;
  x->coeffs1[0] = -WUTR_FILT_POLE * 2.0 * cos(x->freq1);
  x->coeffs1[1] = WUTR_FILT_POLE * WUTR_FILT_POLE;
  x->coeffs2[0] = -WUTR_FILT_POLE * 2.0 * cos(x->freq2);
  x->coeffs2[1] = WUTR_FILT_POLE * WUTR_FILT_POLE;
}
float wuter_tick(t_wuter *x) {
  float data;
  int j;
  if (my_random(32767) < (long)x->num_objects) {     
    x->sndLevel = x->shakeEnergy;
    x->pandropL = (float)rand()*RANDNORM;  
    x->pandropR = 1. - x->pandropL;
    x->pandropL = powf(x->pandropL, 0.5);
    x->pandropR = powf(x->pandropR, 0.5);
    
    j = my_random(3);
	  if (j == 0)   {
      x->freq = x->res_freq * (1. - x->res_spread + (x->res_random * noise_tick()));
	    x->gain = fabs(noise_tick());
	  }
	  else if (j == 1)      {
      x->freq1 = x->res_freq * (1.0 + (x->res_random * noise_tick()));
	   x->gain1 = fabs(noise_tick());
	  }
	  else  {
      x->freq2 = x->res_freq * (1. + 2.*x->res_spread + (2.*x->res_random * noise_tick()));
	    x->gain2 = fabs(noise_tick());
	  }
	}
	
  x->gain  *= WUTR_FILT_POLE;
  if (x->gain >  0.001) {
    x->freq  *= WUTR_FREQ_SWEEP;
    x->coeffs[0] = -WUTR_FILT_POLE * 2.0 * 
      cos(x->freq * TWO_PI / x->srate);
  }
  x->gain1 *= WUTR_FILT_POLE;
  if (x->gain1 > 0.001) {
    x->freq1 *= WUTR_FREQ_SWEEP;
    x->coeffs1[0] = -WUTR_FILT_POLE * 2.0 * 
      cos(x->freq1 * TWO_PI / x->srate);
  }
  x->gain2 *= WUTR_FILT_POLE;
  if (x->gain2 > 0.001) {
    x->freq2 *= WUTR_FREQ_SWEEP;
    x->coeffs2[0] = -WUTR_FILT_POLE * 2.0 * 
      cos(x->freq2 * TWO_PI / x->srate);
  }
	
  x->sndLevel *= x->soundDecay;        // Each (all) event(s) 
  // decay(s) exponentially 
  x->input = x->sndLevel;
  x->input *= noise_tick();         // Actual Sound is Random
  x->input1 = x->input * x->gain1;
  x->input2 = x->input * x->gain2;
  x->input *= x->gain;
  x->input -= x->output[0]*x->coeffs[0];
  x->input -= x->output[1]*x->coeffs[1];
  x->output[1] = x->output[0];
  x->output[0] = x->input;
  data = x->output[0];
  x->input1 -= x->output1[0]*x->coeffs1[0];
  x->input1 -= x->output1[1]*x->coeffs1[1];
  x->output1[1] = x->output1[0];
  x->output1[0] = x->input1;
  data += x->output1[0];
  x->input2 -= x->output2[0]*x->coeffs2[0];
  x->input2 -= x->output2[1]*x->coeffs2[1];
  x->output2[1] = x->output2[0];
  x->output2[0] = x->input2;
  data += x->output2[0];
 
  x->finalZ[2] = x->finalZ[1];
  x->finalZ[1] = x->finalZ[0];
  x->finalZ[0] = data * 4.;

  data = x->finalZ[2] - x->finalZ[0];
  return data;
}

int my_random(int max)  {   //  Return Random Int Between 0 and max
	unsigned long temp;
  	temp = (unsigned long) rand();
	temp *= (unsigned long) max;
	temp >>= 15;
	return (int) temp; 
}

//noise maker
float noise_tick() 
{
	float output;
	output = (float)rand() - 16384.;
	output *= ONE_OVER_RANDLIMIT;
	return output;
}

//primary MSP funcs
void main(void)
{
    setup((struct messlist **)&wuter_class, (method)wuter_new, (method)dsp_free, (short)sizeof(t_wuter), 0L, A_DEFFLOAT, 0);
    addmess((method)wuter_dsp, "dsp", A_CANT, 0);
    addmess((method)wuter_assist,"assist",A_CANT,0);
    addfloat((method)wuter_float);
    addint((method)wuter_int);
    addbang((method)wuter_bang);
    dsp_initclass();
    rescopy('STR#',9821);
}

void wuter_assist(t_wuter *x, void *b, long m, long a, char *s)
{
	assist_string(9821,m,a,1,5,s);
}

void wuter_float(t_wuter *x, double f)
{
	if (x->x_obj.z_in == 0) {
		x->num_objects = (long)f;
	} else if (x->x_obj.z_in == 1) {
		x->res_freq = f;
	} else if (x->x_obj.z_in == 2) {
		x->shake_damp = f;
	} else if (x->x_obj.z_in == 3) {
		x->shake_max = f;
	}
}

void wuter_int(t_wuter *x, int f)
{
	wuter_float(x, (double)f);
}

void wuter_bang(t_wuter *x)
{
	int i;
	post("wuter: zeroing delay lines");
	for(i=0; i<2; i++) {
		x->output[i] = 0.;
		x->output1[i] = 0.;
		x->output2[i] = 0.;
	}
	x->input = 0.0;
	x->input1 = 0.0;
	x->input2 = 0.0;
	
	for(i=0; i<3; i++) {
		x->finalZ[i] = 0.;
	}
}

void *wuter_new(double initial_coeff)
{
	int i;

    t_wuter *x = (t_wuter *)newobject(wuter_class);
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_wuter);i++)  
                ((char *)x)[i]=0; 
	} 
    dsp_setup((t_pxobject *)x,4);
    outlet_new((t_object *)x, "signal");
    outlet_new((t_object *)x, "signal");
    
    x->srate = sys_getsr();
    x->one_over_srate = 1./x->srate;
    x->freq = x->freq1 = x->freq2 = 500.;
    x->res_freq = x->res_freqSave = 500.;
    x->totalEnergy = 0.;
    
	x->shakeEnergy = 0.0;
	for(i=0; i<2; i++) {
		x->output[i] = 0.;
		x->output1[i] = 0.;
		x->output2[i] = 0.;
	}
	x->input = 0.0;
	x->input1 = 0.0;
	x->input2 = 0.0;
	x->sndLevel = 0.0;
	x->gain = 0.0; x->gain1 = 0; x->gain2 = 0;
	x->soundDecay = 0.0;
	x->systemDecay = 0.0;	
	x->shakeEnergy = 1.;
	
    x->shake_damp = 0.9;
    x->shake_max = 0.9;
    x->shake_dampSave = 0.9; 	//damping
    x->shake_maxSave = 0.9;

 	for(i=0; i<3; i++) {
		x->finalZ[i] = 0.;
	}
	
	x->pandropL = x->pandropR = 0.76;
    
    wuter_setup(x);
    
    srand(0.54);
    
    return (x);
}


void wuter_dsp(t_wuter *x, t_signal **sp, short *count)
{
	x->num_objectsConnected = count[0];
	x->res_freqConnected = count[1];
	x->shake_dampConnected = count[2];
	x->shake_maxConnected = count[3];
	
	x->srate = sp[0]->s_sr;
	x->one_over_srate = 1./x->srate;
	
	dsp_add(wuter_perform, 8, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, \
								  sp[4]->s_vec, sp[5]->s_vec, sp[0]->s_n);	
	
}

t_int *wuter_perform(t_int *w)
{
	t_wuter *x = (t_wuter *)(w[1]);
	
	float num_objects	= x->num_objectsConnected	? 	*(float *)(w[2]) : x->num_objects;
	float res_freq 		= x->res_freqConnected		? 	*(float *)(w[3]) : x->res_freq;
	float shake_damp 	= x->shake_dampConnected	? 	*(float *)(w[4]) : x->shake_damp;
	float shake_max 	= x->shake_maxConnected		? 	*(float *)(w[5]) : x->shake_max;
	
	float *outL = (float *)(w[6]);
	float *outR = (float *)(w[7]);
	long n = w[8];

	float lastOutput, temp;
	long temp2;

	if(num_objects != x->num_objectsSave) {
		if(num_objects < 1.) num_objects = 1.;
		x->num_objects = (long)num_objects;
		x->num_objectsSave = (long)num_objects;
		x->gain = log(num_objects) * 30. / (float)num_objects;
	}
	
	if(res_freq != x->res_freqSave) {
		x->res_freqSave = x->res_freq = res_freq;
		//temp = 900. * pow(1.015,res_freq);
    	//x->coeffs[0] = -0.96 * 2.0 * cos(temp * TWO_PI / x->srate);
    	//x->coeffs[1] = 0.96*0.96; 
	}
	
	if(shake_damp != x->shake_dampSave) {
		x->res_spread = x->shake_dampSave = x->shake_damp = shake_damp;
		x->systemDecay = .998 + (shake_damp * .002);
	}
	
	if(shake_max != x->shake_maxSave) {
		x->res_random = x->shake_maxSave = x->shake_max = shake_max;
	 	//x->shakeEnergy += shake_max * MAX_SHAKE * 0.1;
    	//if (x->shakeEnergy > MAX_SHAKE) x->shakeEnergy = MAX_SHAKE;
	}	

	while(n--) {
		lastOutput = wuter_tick(x);		
		*outL++ = lastOutput*x->pandropL;
		*outR++ = lastOutput*x->pandropR;
	}
	return w + 9;
}	

