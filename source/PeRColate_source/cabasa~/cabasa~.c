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
//#define MAX_RANDOM 32768
#define MAX_RANDOM RAND_MAX
#define MAX_SHAKE 1.0

#define BAMB_SOUND_DECAY 0.95
#define BAMB_SYSTEM_DECAY 0.99995
#define BAMB_NUM_TUBES 5
#define BAMB_BASE_FREQ  2800

#define SEKE_SOUND_DECAY 0.96
#define SEKE_SYSTEM_DECAY 0.999
#define SEKE_NUM_BEANS 64

#define CABA_SOUND_DECAY 0.95
#define CABA_SYSTEM_DECAY 0.997
#define CABA_NUM_BEADS 512

void *cabasa_class;

typedef struct _cabasa
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars	    
	float shakeEnergy;
	float input,output[2];
	float coeffs[2];
	float sndLevel;
	float gain;//, gain1, gain2;
	float soundDecay;
	float systemDecay;

	long  num_objects;
    float shake_damp;
    float shake_max;
	float res_freq;
	    
    long num_objectsSave;	//number of beans	
    float res_freqSave;		//resonance
    float shake_dampSave; 	//damping
    float shake_maxSave;

    //signals connected? or controls...
    short num_objectsConnected;
    short res_freqConnected;
    short shake_dampConnected;
    short shake_maxConnected;
   
    float srate, one_over_srate;
} t_cabasa;

/****PROTOTYPES****/

//setup funcs
void *cabasa_new(double val);
void cabasa_dsp(t_cabasa *x, t_signal **sp, short *count);
void cabasa_float(t_cabasa *x, double f);
void cabasa_int(t_cabasa *x, int f);
void cabasa_bang(t_cabasa *x);
t_int *cabasa_perform(t_int *w);
void cabasa_assist(t_cabasa *x, void *b, long m, long a, char *s);

void cabasa_setup(t_cabasa *x);
float cabasa_tick(t_cabasa *x);

//noise maker
float noise_tick();
int my_random(int max) ;

/****FUNCTIONS****/

void cabasa_setup(t_cabasa *x) {

  x->num_objects = x->num_objectsSave = CABA_NUM_BEADS;
  x->gain = log(x->num_objects) / log(4.0) * 120.0 / (float) x->num_objects;
  x->coeffs[0] = -0.7 * 2.0 * cos(3000.0 * TWO_PI / x->srate);
  x->coeffs[1] = 0.7*0.7;
  x->soundDecay = CABA_SOUND_DECAY;
  x->systemDecay = CABA_SYSTEM_DECAY;
  x->shake_damp = x->shake_dampSave = 0.9;
  x->shake_max = x->shake_maxSave = 0.9;
  x->res_freq = x->res_freqSave = 2000.;
  
}

float cabasa_tick(t_cabasa *x) {
  float data;
  x->shakeEnergy *= x->systemDecay;         	// Exponential system decay
  if (my_random(1024) < x->num_objects)  		// If collision
  	x->sndLevel += x->gain * x->shakeEnergy;   	//   add energy
  x->input = x->sndLevel * noise_tick();    	// Actual Sound is Random
  x->sndLevel *= x->soundDecay;             	// Exponential Sound decay 
  x->input -= x->output[0]*x->coeffs[0];       	// Do gourd
  x->input -= x->output[1]*x->coeffs[1];       	//   resonance
  x->output[1] = x->output[0];              	//     filter
  x->output[0] = x->input;                  	//       calculations
  data = x->output[0] - x->output[1];
		
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
    setup((struct messlist **)&cabasa_class, (method)cabasa_new, (method)dsp_free, (short)sizeof(t_cabasa), 0L, A_DEFFLOAT, 0);
    addmess((method)cabasa_dsp, "dsp", A_CANT, 0);
    addmess((method)cabasa_assist,"assist",A_CANT,0);
    addfloat((method)cabasa_float);
    addint((method)cabasa_int);
    addbang((method)cabasa_bang);
    dsp_initclass();
    rescopy('STR#',9332);
}

void cabasa_assist(t_cabasa *x, void *b, long m, long a, char *s)
{
	assist_string(9332,m,a,1,5,s);
}

void cabasa_float(t_cabasa *x, double f)
{
	if (x->x_obj.z_in == 0) {
		x->num_objects = (long)f;
	} else if (x->x_obj.z_in == 3) {
		x->res_freq = f;
	} else if (x->x_obj.z_in == 1) {
		x->shake_damp = f;
	} else if (x->x_obj.z_in == 2) {
		x->shake_max = f;
	}
}

void cabasa_int(t_cabasa *x, int f)
{
	cabasa_float(x, (double)f);
}

void cabasa_bang(t_cabasa *x)
{
	int i;
	post("cabasa: zeroing delay lines");
	for(i=0; i<2; i++) {
		x->output[i] = 0.;
	}
	x->input = 0.0;
}

void *cabasa_new(double initial_coeff)
{
	int i;
	
	    //user controlled vars	    
	float coeffs[2];

    t_cabasa *x = (t_cabasa *)newobject(cabasa_class);
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_cabasa);i++)  
                ((char *)x)[i]=0; 
	} 
    dsp_setup((t_pxobject *)x,4);
    outlet_new((t_object *)x, "signal");
    
    x->srate = sys_getsr();
    x->one_over_srate = 1./x->srate;

	x->shakeEnergy = 0.0;
	for(i=0; i<2; i++) {
		x->output[i] = 0.;
	}
	x->input = 0.0;
	x->sndLevel = 0.0;
    
    cabasa_setup(x);
    
    srand(0.54);
    
    return (x);
}


void cabasa_dsp(t_cabasa *x, t_signal **sp, short *count)
{
	x->num_objectsConnected = count[0];
	x->shake_dampConnected = count[1];
	x->shake_maxConnected = count[2];
	x->res_freqConnected = count[3];
	x->srate = sp[0]->s_sr;
	x->one_over_srate = 1./x->srate;
	dsp_add(cabasa_perform, 7, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, \
							sp[4]->s_vec, sp[0]->s_n);	
	
}

t_int *cabasa_perform(t_int *w)
{
	t_cabasa *x = (t_cabasa *)(w[1]);
	
	float num_objects	= x->num_objectsConnected	? 	*(float *)(w[2]) : x->num_objects;
	float shake_damp 	= x->shake_dampConnected	? 	*(float *)(w[3]) : x->shake_damp;
	float shake_max 	= x->shake_maxConnected		? 	*(float *)(w[4]) : x->shake_max;
	float res_freq 		= x->res_freqConnected		? 	*(float *)(w[5]) : x->res_freq;
	
	float *out = (float *)(w[6]);
	long n = w[7];

	float lastOutput, temp;
	long temp2;

		if(num_objects != x->num_objectsSave) {
			if(num_objects < 1.) num_objects = 1.;
			x->num_objects = (long)num_objects;
			x->num_objectsSave = (long)num_objects;
			//x->gain = log(num_objects) * 30. / (float)num_objects;
			//x->gain = log(num_objects) / log(4.0) * 40.0 / (float)num_objects;
			x->gain = log(num_objects) / log(4.0) * 120.0 / (float) num_objects;
		}
		
		if(res_freq != x->res_freqSave) {
			x->res_freqSave = x->res_freq = res_freq;
	  		x->coeffs[0] = -0.7 * 2.0 * cos(res_freq * TWO_PI / x->srate);
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

		while(n--) {
			lastOutput = cabasa_tick(x);		
			*out++ = lastOutput;
		}
	return w + 8;
}	

