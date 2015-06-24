// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

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

t_class *bamboo_class;

typedef struct _bamboo
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
	float freq_rand;
	float soundDecay;
	float systemDecay;
    
	long  num_objects;
    float shake_damp;
    float shake_max;
	float res_freq;
    
    long num_objectsSave;	//number of beans
    float res_freqSave;	//resonance
    float shake_dampSave; 	//damping
    float shake_maxSave;
    float res_spread, res_random, res_spreadConnected, res_randomConnected;
    float res_spreadSave, res_randomSave;
    
    //signals connected? or controls...
    short num_objectsConnected;
    short res_freqConnected;
    short shake_dampConnected;
    short shake_maxConnected;
    
    float srate, one_over_srate;
} t_bamboo;

/****PROTOTYPES****/

//setup funcs
void *bamboo_new(double val);
void bamboo_assist(t_bamboo *x, void *b, long m, long a, char *s);

// dsp stuff
void bamboo_dsp64(t_bamboo *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void bamboo_perform64(t_bamboo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void bamboo_bang(t_bamboo *x);
void bamboo_int(t_bamboo *x, int f);
void bamboo_float(t_bamboo *x, double f);

void bamboo_setup(t_bamboo *x);
float bamboo_tick(t_bamboo *x);

//noise maker
float noise_tick();
int my_random(int max) ;

/****FUNCTIONS****/

void bamboo_setup(t_bamboo *x) {
    x->num_objects = BAMB_NUM_TUBES;
    x->num_objectsSave = BAMB_NUM_TUBES;
    x->soundDecay = BAMB_SOUND_DECAY;
    x->systemDecay = BAMB_SYSTEM_DECAY;
    x->gain = 4.0 / (float) x->num_objects;
    x->coeffs[0] = -0.995 * 2.0 * cos(BAMB_BASE_FREQ * TWO_PI / x->srate);
    x->coeffs[1] = 0.995*0.995;
    x->coeffs1[0] = -0.995 * 2.0 * cos(BAMB_BASE_FREQ * 0.8 * TWO_PI / x->srate);
    x->coeffs1[1] = 0.995*0.995;
    x->coeffs2[0] = -0.995 * 2.0 * cos(BAMB_BASE_FREQ * 1.2 * TWO_PI / x->srate);
    x->coeffs2[1] = 0.995*0.995;
}

float bamboo_tick(t_bamboo *x) {
    float data;
    x->shakeEnergy *= x->systemDecay;       // Exponential System Decay
    if (my_random(4096) < x->num_objects) {
        x->sndLevel += x->gain *  x->shakeEnergy;
        x->freq_rand = x->res_freq * (1.0 + (x->res_random * noise_tick()));
        x->coeffs[0] = -0.995 * 2.0 *
        cos(x->freq_rand * TWO_PI / x->srate);
        x->freq_rand = x->res_freq * (1. - x->res_spread + (x->res_random * noise_tick()));
        x->coeffs1[0] = -0.995 * 2.0 *
        cos(x->freq_rand * TWO_PI / x->srate);
        x->freq_rand = x->res_freq * (1. + 2.*x->res_spread + (2.*x->res_random * noise_tick()));
        x->coeffs2[0] = -0.995 * 2.0 *
        cos(x->freq_rand * TWO_PI / x->srate);
    }
    x->input = x->sndLevel;
    x->input *= noise_tick();             // Actual Sound is Random
    x->input1 = x->input;
    x->input2 = x->input;
	
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
	//the two A_DEFLONG arguments give us the two arguments for the user to set number of ins/outs
	//change these if you want different user args
    t_class *c = class_new("bamboo~", (method)bamboo_new, (method)dsp_free, (long)sizeof(t_bamboo), 0L, A_DEFFLOAT, 0);
    
    class_addmethod(c, (method)bamboo_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)bamboo_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)bamboo_float, "float", A_FLOAT, 0);
    class_addmethod(c, (method)bamboo_int, "int", A_LONG, 0);
    class_addmethod(c, (method)bamboo_bang, "bang", A_CANT, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    bamboo_class = c;
}

void bamboo_assist(t_bamboo *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
            case 0:
                sprintf(s,"(signal/float) number of items");
                break;
            case 1:
                sprintf(s,"(signal/float) resonance");
                break;
            case 2:
                sprintf(s,"(signal/float) damping");
                break;
            case 3:
                sprintf(s,"(signal/float) maximum shake");
                break;
            case 4:
                sprintf(s,"(signal/float) resonance spread");
                break;
            case 5:
                sprintf(s,"(signal/float) random resonance");
                break;
        }
	} else {
		sprintf(s,"(signal) output");
    }
}

void bamboo_float(t_bamboo *x, double f)
{
	if (x->x_obj.z_in == 0) {
		x->num_objects = (long)f;
	} else if (x->x_obj.z_in == 1) {
		x->res_freq = f;
	} else if (x->x_obj.z_in == 2) {
		x->shake_damp = f;
	} else if (x->x_obj.z_in == 3) {
		x->shake_max = f;
	} else if (x->x_obj.z_in == 4) {
		x->res_spread = f;
	} else if (x->x_obj.z_in == 5) {
		x->res_random = f;
	}
}

void bamboo_int(t_bamboo *x, int f)
{
	bamboo_float(x, (double)f);
}

void bamboo_bang(t_bamboo *x)
{
	int i;
	post("bamboo: zeroing delay lines");
	for(i=0; i<2; i++) {
		x->output[i] = 0.;
		x->output1[i] = 0.;
		x->output2[i] = 0.;
	}
	x->input = 0.0;
	x->input1 = 0.0;
	x->input2 = 0.0;
	x->num_objects = BAMB_NUM_TUBES;
  	x->gain = 4.0 / (float) x->num_objects;
  	x->sndLevel = 0.;
}

void *bamboo_new(double initial_coeff)
{
	int i;
    
    t_bamboo *x = (t_bamboo *)object_alloc(bamboo_class);
    
    if (x) {
        //zero out the struct, to be careful (takk to jkclayton)
        for(i=sizeof(t_pxobject);i<sizeof(t_bamboo);i++) {
            ((char *)x)[i]=0;
        }
        
        dsp_setup((t_pxobject *)x, 6);
        outlet_new((t_object *)x, "signal");
        
        x->srate = sys_getsr();
        x->one_over_srate = 1./x->srate;
        
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
        x->freq_rand = 0.0;
        x->soundDecay = 0.0;
        x->systemDecay = 0.0;
        
        x->shake_damp = 0.9;
        x->shake_max = 0.;
        x->res_freq = 4000.;
        
        x->res_freqSave = x->res_freq;	//resonance
        x->shake_dampSave = x->shake_damp; 	//damping
        x->shake_maxSave = x->shake_max;
        
        x->res_spread = 0.; x->res_random = 0.;
        x->res_spreadSave = 0.; x->res_randomSave = 0.;
        
        bamboo_setup(x);
        
        srand(0.54);
    }
    
    return (x);
}

void bamboo_dsp64(t_bamboo *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->num_objectsConnected 	= count[0];
	x->res_freqConnected 		= count[1];
	x->shake_dampConnected 		= count[2];
	x->shake_maxConnected 		= count[3];
	x->res_spreadConnected 		= count[4];
	x->res_randomConnected 		= count[5];
	x->srate = samplerate;
	x->one_over_srate = 1./x->srate;
    
    object_method(dsp64, gensym("dsp_add64"), x, bamboo_perform64, 0, NULL);
}

void bamboo_perform64(t_bamboo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	double num_objects	= x->num_objectsConnected	? 	*(double *)(ins[0]) : x->num_objects;
	double res_freq 	= x->res_freqConnected		? 	*(double *)(ins[1]) : x->res_freq;
	double shake_damp 	= x->shake_dampConnected	? 	*(double *)(ins[2]) : x->shake_damp;
	double shake_max 	= x->shake_maxConnected		? 	*(double *)(ins[3]) : x->shake_max;
	double res_spread 	= x->res_spreadConnected	? 	*(double *)(ins[4]) : x->res_spread;
	double res_random 	= x->res_randomConnected	? 	*(double *)(ins[5]) : x->res_random;
	
	double *out = (double *)(outs[0]);
	long n = sampleframes;
    
	double lastOutput;
    
	if(num_objects != x->num_objectsSave) {
		if(num_objects < 1.) num_objects = 1.;
		x->num_objects = (long)num_objects;
		x->num_objectsSave = (long)num_objects;
		x->gain = log(num_objects) * 30. / (double)num_objects;
	}
	
	if(res_freq != x->res_freqSave) {
		x->res_freqSave = x->res_freq = res_freq;
		//temp = 900. * pow(1.015,res_freq);
    	//x->coeffs[0] = -0.96 * 2.0 * cos(temp * TWO_PI / x->srate);
    	//x->coeffs[1] = 0.96*0.96;
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
    
	if(res_spread != x->res_spreadSave) {
		x->res_spreadSave = x->res_spread = res_spread;
	}
	
	if(res_random != x->res_randomSave) {
		x->res_randomSave = x->res_random = res_random;
	}
	
	while(n--) {
		lastOutput = bamboo_tick(x);
		*out++ = lastOutput;
	}
}


