// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

#define SEKE_SOUND_DECAY 0.96
#define SEKE_SYSTEM_DECAY 0.999
#define SEKE_NUM_BEANS 64

t_class *sekere_class;

typedef struct _sekere
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars	    
	float shakeEnergy;
	float input,output[2];
	float coeffs[2];

	float sndLevel;
	float gain; 
	
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
	float finalZ[3];	
    
    //signals connected? or controls...
    short num_objectsConnected;
    short res_freqConnected;
    short shake_dampConnected;
    short shake_maxConnected;
   
    float srate, one_over_srate;
} t_sekere;

/****PROTOTYPES****/

//setup funcs
void *sekere_new(double val);
void sekere_assist(t_sekere *x, void *b, long m, long a, char *s);

// dsp stuff
void sekere_dsp64(t_sekere *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void sekere_perform64(t_sekere *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void sekere_float(t_sekere *x, double f);
void sekere_int(t_sekere *x, int f);
void sekere_bang(t_sekere *x);

void sekere_setup(t_sekere *x);
float sekere_tick(t_sekere *x);

//noise maker
float noise_tick();
int my_random(int max) ;

/****FUNCTIONS****/

void sekere_setup(t_sekere *x) {
  x->num_objects = x->num_objectsSave = SEKE_NUM_BEANS;
  x->gain = log(x->num_objects) / log(4.0) * 40.0 / (float) x->num_objects;
  x->coeffs[0] = -0.6 * 2.0 * cos(5500.0 * TWO_PI / x->srate);
  x->coeffs[1] = 0.6*0.6;
  x->soundDecay = SEKE_SOUND_DECAY;
  x->systemDecay = SEKE_SYSTEM_DECAY;
}

float sekere_tick(t_sekere *x) {
  float data;
  x->shakeEnergy *= x->systemDecay;         // Exponential system decay
  if (my_random(1024) < x->num_objects)  	// If collision
  x->sndLevel += x->gain * x->shakeEnergy;  //   add energy
  x->input = x->sndLevel * noise_tick();    // Actual Sound is Random
  x->sndLevel *= x->soundDecay;             // Exponential Sound decay 
  x->input -= x->output[0]*x->coeffs[0];    // Do gourd
  x->input -= x->output[1]*x->coeffs[1];    //   resonance
  x->output[1] = x->output[0];              //     filter
  x->output[0] = x->input;                  //       calculations
  x->finalZ[2] = x->finalZ[1];
  x->finalZ[1] = x->finalZ[0];
  x->finalZ[0] = x->output[1];
  data = x->finalZ[0] - x->finalZ[2];
		
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
void ext_main(void* p)
{
    t_class *c = class_new("sekere~", (method)sekere_new, (method)dsp_free, (long)sizeof(t_sekere), 0L, A_DEFFLOAT, 0);
    
    class_addmethod(c, (method)sekere_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)sekere_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)sekere_float, "float", A_FLOAT, 0);
    class_addmethod(c, (method)sekere_int, "int", A_LONG, 0);
    class_addmethod(c, (method)sekere_bang, "bang", A_CANT, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    sekere_class = c;
}

void sekere_assist(t_sekere *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
            case 0:
                sprintf(s,"(signal/float) number of items");
                break;
            case 1:
                sprintf(s,"(signal/float) damping");
                break;
            case 2:
                sprintf(s,"(signal/float) maximum shake");
                break;
            case 3:
                sprintf(s,"(signal/float) resonant frequency");
                break;
        }
	} else {
		sprintf(s,"(signal) output");
    }
}

void sekere_float(t_sekere *x, double f)
{
	if (x->x_obj.z_in == 0) {
		x->num_objects = (long)f;
	} else if (x->x_obj.z_in == 3) {
		x->res_freq = f;
		x->coeffs[0] = -0.6 * 2.0 * cos(x->res_freq * TWO_PI / x->srate);
	} else if (x->x_obj.z_in == 1) {
		x->shake_damp = f;
	} else if (x->x_obj.z_in == 2) {
		x->shake_max = f;
	}
}

void sekere_int(t_sekere *x, int f)
{
	sekere_float(x, (double)f);
}

void sekere_bang(t_sekere *x)
{
	int i;
	post("sekere: zeroing delay lines");
	for(i=0; i<2; i++) {
		x->output[i] = 0.;
		//x->output1[i] = 0.;
		//x->output2[i] = 0.;
		//x->output3[i] = 0.;
		//x->output4[i] = 0.;
	}
	x->input = 0.0;
	//x->input1 = 0.0;
	//x->input2 = 0.0;
	//x->input3 = 0.0;
	//x->input4 = 0.0;
	for(i=0; i<3; i++) {
		x->finalZ[i] = 0.;
	}
}

void *sekere_new(double initial_coeff)
{
	int i;

    t_sekere *x = (t_sekere *)object_alloc(sekere_class);
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_sekere);i++)  
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
	x->gain = 0.0; 
	x->soundDecay = 0.0;
	x->systemDecay = 0.0;
	x->shake_damp = x->shake_dampSave = 0.9;
	x->shake_max = x->shake_maxSave = 0.9;
	x->res_freq = x->res_freqSave = 3000.;

 	for(i=0; i<3; i++) {
		x->finalZ[i] = 0.;
	}
    
    sekere_setup(x);
    
    srand(0.54);
    
    return (x);
}

// dsp stuff
void sekere_dsp64(t_sekere *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->num_objectsConnected = count[0];
	x->shake_dampConnected = count[1];
	x->shake_maxConnected = count[2];
	x->res_freqConnected = count[3];
	
	x->srate = samplerate;
	x->one_over_srate = 1./x->srate;
    
    object_method(dsp64, gensym("dsp_add64"), x, sekere_perform64, 0, NULL);
}

void sekere_perform64(t_sekere *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double num_objects	= x->num_objectsConnected	? 	*(t_double *)(ins[0]) : x->num_objects;
	t_double shake_damp 	= x->shake_dampConnected	? 	*(t_double *)(ins[1]) : x->shake_damp;
	t_double shake_max      = x->shake_maxConnected		? 	*(t_double *)(ins[2]) : x->shake_max;
	t_double res_freq 		= x->res_freqConnected		? 	*(t_double *)(ins[3]) : x->res_freq;
	
	t_double *out = (t_double *)(outs[0]);
	long n = sampleframes;
    
	t_double lastOutput;
    
    if(num_objects != x->num_objectsSave) {
        if(num_objects < 1.) num_objects = 1.;
        x->num_objects = (long)num_objects;
        x->num_objectsSave = (long)num_objects;
        //x->gain = log(num_objects) * 30. / (t_double)num_objects;
        x->gain = log(num_objects) / log(4.0) * 40.0 / (t_double)num_objects;
    }
    
    if(res_freq != x->res_freqSave) {
        x->res_freqSave = x->res_freq = res_freq;
        x->coeffs[0] = -0.6 * 2.0 * cos(res_freq * TWO_PI / x->srate);
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
        lastOutput = sekere_tick(x);		
        *out++ = lastOutput;
    }

}
