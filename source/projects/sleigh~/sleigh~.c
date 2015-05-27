#include "ext.h"
#include "z_dsp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TWO_PI 6.283185307
//#define ONE_OVER_RANDLIMIT 0.00006103516 // constant = 1. / 16384.0
#define ONE_OVER_RANDLIMIT 1./RAND_MAX
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

void *sleigh_class;

typedef struct _sleigh
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
	float input3,output3[2];
	float coeffs3[2];
	float input4,output4[2];
	float coeffs4[2];
	float sndLevel;
	float gain;
	float soundDecay;
	float systemDecay;
	float cymb_rand;

	long  num_objects;
    float shake_damp;
    float shake_max;
	float res_freq;
	    
    long num_objectsSave;	//number of beans	
    float res_freqSave;	//resonance
    float shake_dampSave; 	//damping
    float shake_maxSave;
    float res_freq1, res_freq2, res_freq1Connected, res_freq2Connected;
    float res_freq1Save, res_freq2Save;
    float res_freq3, res_freq4, res_freq3Connected, res_freq4Connected;
    float res_freq3Save, res_freq4Save;

	float totalEnergy;
	float finalZ[3];	
    
    //signals connected? or controls...
    short num_objectsConnected;
    short res_freqConnected;
    short shake_dampConnected;
    short shake_maxConnected;
   
    float srate, one_over_srate;
} t_sleigh;

/****PROTOTYPES****/

//setup funcs
void *sleigh_new(double val);
void sleigh_dsp(t_sleigh *x, t_signal **sp, short *count);
void sleigh_float(t_sleigh *x, double f);
void sleigh_int(t_sleigh *x, int f);
void sleigh_bang(t_sleigh *x);
t_int *sleigh_perform(t_int *w);
void sleigh_assist(t_sleigh *x, void *b, long m, long a, char *s);

void sleigh_setup(t_sleigh *x);
float sleigh_tick(t_sleigh *x);

//noise maker
float noise_tick();
int my_random(int max) ;

/****FUNCTIONS****/

#define SLEI_SOUND_DECAY 0.97
#define SLEI_SYSTEM_DECAY 0.9994
#define SLEI_NUM_BELLS 32
#define SLEI_CYMB_FREQ0 2500
#define SLEI_CYMB_FREQ1 5300
#define SLEI_CYMB_FREQ2 6500
#define SLEI_CYMB_FREQ3 8300
#define SLEI_CYMB_FREQ4 9800
#define SLEI_CYMB_RESON 0.99

void sleigh_setup(t_sleigh *x) {

  x->num_objects = x->num_objectsSave = SLEI_NUM_BELLS;
  x->soundDecay = SLEI_SOUND_DECAY;
  x->systemDecay = SLEI_SYSTEM_DECAY;
  x->res_freq = x->res_freqSave = SLEI_CYMB_FREQ0;
  x->res_freq1 = x->res_freq1Save = SLEI_CYMB_FREQ1;
  x->res_freq2 = x->res_freq2Save = SLEI_CYMB_FREQ2;
  x->res_freq3 = x->res_freq3Save =SLEI_CYMB_FREQ3;
  x->res_freq4 = x->res_freq4Save = SLEI_CYMB_FREQ4;
  x->gain = 8.0 / x->num_objects;
  x->coeffs[0] = -SLEI_CYMB_RESON * 2.0 * cos(x->res_freq * TWO_PI / x->srate);
  x->coeffs[1] = SLEI_CYMB_RESON*SLEI_CYMB_RESON;
  x->coeffs1[0] = -SLEI_CYMB_RESON * 2.0 * cos(x->res_freq1 * TWO_PI / x->srate);
  x->coeffs1[1] = SLEI_CYMB_RESON*SLEI_CYMB_RESON;
  x->coeffs2[0] = -SLEI_CYMB_RESON * 2.0 * cos(x->res_freq2 * TWO_PI / x->srate);
  x->coeffs2[1] = SLEI_CYMB_RESON*SLEI_CYMB_RESON;                      
  x->coeffs3[0] = -SLEI_CYMB_RESON * 2.0 * cos(x->res_freq3 * TWO_PI / x->srate);
  x->coeffs3[1] = SLEI_CYMB_RESON*SLEI_CYMB_RESON;
  x->coeffs4[0] = -SLEI_CYMB_RESON * 2.0 * cos(x->res_freq4 * TWO_PI / x->srate);
  x->coeffs4[1] = SLEI_CYMB_RESON*SLEI_CYMB_RESON;
}

float sleigh_tick(t_sleigh *x) {
  float data;
  x->shakeEnergy *= x->systemDecay;         // Exponential System Decay
  if (my_random(1024) < x->num_objects) {     
    x->sndLevel += x->gain *  x->shakeEnergy;   
    x->cymb_rand = noise_tick() * x->res_freq * 0.05;
    x->coeffs[0] = -SLEI_CYMB_RESON * 2.0 * 
      cos((x->res_freq + x->cymb_rand) * TWO_PI * x->one_over_srate);
    x->cymb_rand = noise_tick() * x->res_freq1 * 0.03;
    x->coeffs1[0] = -SLEI_CYMB_RESON * 2.0 * 
      cos((x->res_freq1 + x->cymb_rand) * TWO_PI * x->one_over_srate);
    x->cymb_rand = noise_tick() * x->res_freq2 * 0.03;
    x->coeffs2[0] = -SLEI_CYMB_RESON * 2.0 * 
      cos((x->res_freq2 + x->cymb_rand) * TWO_PI * x->one_over_srate);
    x->cymb_rand = noise_tick() * x->res_freq3 * 0.03;
    x->coeffs3[0] = -SLEI_CYMB_RESON * 2.0 * 
      cos((x->res_freq3 + x->cymb_rand) * TWO_PI * x->one_over_srate);
    x->cymb_rand = noise_tick() * x->res_freq4 * 0.03;
    x->coeffs4[0] = -SLEI_CYMB_RESON * 2.0 * 
      cos((x->res_freq4 + x->cymb_rand) * TWO_PI * x->one_over_srate);
  }
  x->input = x->sndLevel;
  x->input *= noise_tick();        // Actual Sound is Random
  x->input1 = x->input;
  x->input2 = x->input;
  x->input3 = x->input * 0.5;
  x->input4 = x->input * 0.3;

  x->sndLevel *= x->soundDecay;            // Each (all) event(s) 
  // decay(s) exponentially 
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
	
  x->input3 -= x->output3[0]*x->coeffs3[0];
  x->input3 -= x->output3[1]*x->coeffs3[1];
  x->output3[1] = x->output3[0];
  x->output3[0] = x->input3;
  data += x->output3[0];
	
  x->input4 -= x->output4[0]*x->coeffs4[0];
  x->input4 -= x->output4[1]*x->coeffs4[1];
  x->output4[1] = x->output4[0];
  x->output4[0] = x->input4;
  data += x->output4[0];
	 
  x->finalZ[2] = x->finalZ[1];
  x->finalZ[1] = x->finalZ[0];
  x->finalZ[0] = data;
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
    setup((struct messlist **)&sleigh_class, (method)sleigh_new, (method)dsp_free, (short)sizeof(t_sleigh), 0L, A_DEFFLOAT, 0);
    addmess((method)sleigh_dsp, "dsp", A_CANT, 0);
    addmess((method)sleigh_assist,"assist",A_CANT,0);
    addfloat((method)sleigh_float);
    addint((method)sleigh_int);
    addbang((method)sleigh_bang);
    dsp_initclass();
    rescopy('STR#',9322);
}

void sleigh_assist(t_sleigh *x, void *b, long m, long a, char *s)
{
	assist_string(9322,m,a,1,9,s);
}

void sleigh_float(t_sleigh *x, double f)
{
	if (x->x_obj.z_in == 0) {
		x->num_objects = (long)f;
	} else if (x->x_obj.z_in == 3) {
		x->res_freq = f;
	} else if (x->x_obj.z_in == 1) {
		x->shake_damp = f;
	} else if (x->x_obj.z_in == 2) {
		x->shake_max = f;
	} else if (x->x_obj.z_in == 4) {
		x->res_freq1 = f;
	} else if (x->x_obj.z_in == 5) {
		x->res_freq2 = f;
	} else if (x->x_obj.z_in == 6) {
		x->res_freq3 = f;
	} else if (x->x_obj.z_in == 7) {
		x->res_freq4 = f;
	}
}

void sleigh_int(t_sleigh *x, int f)
{
	sleigh_float(x, (double)f);
}

void sleigh_bang(t_sleigh *x)
{
	int i;
	post("sleigh: zeroing delay lines");
	for(i=0; i<2; i++) {
		x->output[i] = 0.;
		x->output1[i] = 0.;
		x->output2[i] = 0.;
		x->output3[i] = 0.;
		x->output4[i] = 0.;
	}
	x->input = 0.0;
	x->input1 = 0.0;
	x->input2 = 0.0;
	x->input3 = 0.0;
	x->input4 = 0.0;
	for(i=0; i<3; i++) {
		x->finalZ[i] = 0.;
	}
}

void *sleigh_new(double initial_coeff)
{
	int i;

    t_sleigh *x = (t_sleigh *)newobject(sleigh_class);
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_sleigh);i++)  
                ((char *)x)[i]=0; 
	} 
    dsp_setup((t_pxobject *)x,8);
    outlet_new((t_object *)x, "signal");
    
    x->srate = sys_getsr();
    x->one_over_srate = 1./x->srate;
    
	x->shakeEnergy = 0.0;
	for(i=0; i<2; i++) {
		x->output[i] = 0.;
		x->output1[i] = 0.;
		x->output2[i] = 0.;
		x->output3[i] = 0.;
		x->output4[i] = 0.;
	}
	x->input = 0.0;
	x->input1 = 0.0;
	x->input2 = 0.0;
	x->input3 = 0.0;
	x->input4 = 0.0;
	x->sndLevel = 0.0;
	x->gain = 0.0;
	x->soundDecay = 0.0;
	x->systemDecay = 0.0;
	x->cymb_rand = 0.0;
	x->totalEnergy = 0.;
	x->shake_damp = x->shake_dampSave = 0.9;
	x->shake_max = x->shake_maxSave = 0.9;
	x->res_freq = x->res_freqSave = 4000.;
	x->res_freq1 = x->res_freq1Save = 4000.;
	x->res_freq2 = x->res_freq2Save = 4000.;
	x->res_freq3 = x->res_freq3Save = 4000.;
	x->res_freq4 = x->res_freq4Save = 4000.;
	
 	for(i=0; i<3; i++) {
		x->finalZ[i] = 0.;
	}
    
    sleigh_setup(x);
    
    srand(0.54);
    
    return (x);
}


void sleigh_dsp(t_sleigh *x, t_signal **sp, short *count)
{
	x->num_objectsConnected = count[0];
	x->shake_dampConnected = count[1];
	x->shake_maxConnected = count[2];
	x->res_freqConnected = count[3];
	x->res_freq1Connected = count[4];
	x->res_freq2Connected = count[5];
	x->res_freq3Connected = count[6];
	x->res_freq4Connected = count[7];
	
	x->srate = sp[0]->s_sr;
	x->one_over_srate = 1./x->srate;
	
	dsp_add(sleigh_perform, 11, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec, sp[8]->s_vec, sp[0]->s_n);	
	
}

t_int *sleigh_perform(t_int *w)
{
	t_sleigh *x = (t_sleigh *)(w[1]);
	
	float num_objects	= x->num_objectsConnected	? 	*(float *)(w[2]) : x->num_objects;
	float shake_damp 	= x->shake_dampConnected	? 	*(float *)(w[3]) : x->shake_damp;
	float shake_max 	= x->shake_maxConnected		? 	*(float *)(w[4]) : x->shake_max;
	float res_freq 		= x->res_freqConnected		? 	*(float *)(w[5]) : x->res_freq;
	float res_freq1 	= x->res_freq1Connected		? 	*(float *)(w[6]) : x->res_freq1;
	float res_freq2 	= x->res_freq2Connected		? 	*(float *)(w[7]) : x->res_freq2;
	float res_freq3 	= x->res_freq3Connected		? 	*(float *)(w[8]) : x->res_freq3;
	float res_freq4 	= x->res_freq4Connected		? 	*(float *)(w[9]) : x->res_freq4;
	
	float *out = (float *)(w[10]);
	long n = w[11];

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
	}
	
	if(shake_damp != x->shake_dampSave) {
		x->shake_dampSave = x->shake_damp = shake_damp;
		x->systemDecay = .998 + (shake_damp * .002);
	}
	
	if(shake_max != x->shake_maxSave) {
		x->shake_maxSave = x->shake_max = shake_max;
	 	x->shakeEnergy += shake_max * MAX_SHAKE * 0.1;
    	if (x->shakeEnergy > MAX_SHAKE) x->shakeEnergy = MAX_SHAKE;
	}	

	if(res_freq1 != x->res_freq1Save) {
		x->res_freq1Save = x->res_freq1 = res_freq1;
	}
	
	if(res_freq2 != x->res_freq2Save) {
		x->res_freq2Save = x->res_freq2 = res_freq2;
	}	
	
	if(res_freq3 != x->res_freq3Save) {
		x->res_freq3Save = x->res_freq3 = res_freq3;
	}
	
	if(res_freq4 != x->res_freq4Save) {
		x->res_freq4Save = x->res_freq4 = res_freq4;
	}	
	
	while(n--) {
		lastOutput = sleigh_tick(x);		
		*out++ = lastOutput;
	}
	return w + 12;
}	

