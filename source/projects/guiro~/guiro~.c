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
#define MAX_RANDOM 32768
#define MAX_SHAKE 1.0

#define GUIR_SOUND_DECAY 0.95
#define GUIR_NUM_RATCHETS 128
#define GUIR_GOURD_FREQ  2500.0
#define GUIR_GOURD_RESON 0.97
#define GUIR_GOURD_FREQ2  4000.0
#define GUIR_GOURD_RESON2 0.97

/****************************  GUIRO  ***********************/

t_class *guiro_class;

typedef struct _guiro
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars	    
	    
	float guiroScrape;
	float shakeEnergy;
	float input,output[2];
	float coeffs[2];
	float input2,output2[2];
	float coeffs2[2];
	float sndLevel;
	float gain; 
	float soundDecay;
	float systemDecay;

	long  num_objects;
    float shake_damp;
    float shake_max;
	float res_freq, res_freq2;
	    
    long num_objectsSave;	//number of beans	//resonance
    float shake_dampSave; 	//damping
    float shake_maxSave;
    float res_freqSave, res_freq2Save;

	float collLikely,scrapeVel;
	float totalEnergy;
	float ratchet,ratchetDelta;
	float finalZ[3];	
    
    //signals connected? or controls...
    short num_objectsConnected;
    short res_freqConnected, res_freq2Connected;
    short shake_dampConnected;
    short shake_maxConnected;
   
    float srate, one_over_srate;
} t_guiro;

/****PROTOTYPES****/

//setup funcs
void *guiro_new(double val);
void guiro_float(t_guiro *x, double f);
void guiro_int(t_guiro *x, int f);
void guiro_bang(t_guiro *x);
void guiro_assist(t_guiro *x, void *b, long m, long a, char *s);

void guiro_dsp64(t_guiro *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void guiro_perform64(t_guiro *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void guiro_setup(t_guiro *x);
float guiro_tick(t_guiro *x);

//noise maker
float noise_tick();
int my_random(int max) ;

/****FUNCTIONS****/

void guiro_setup(t_guiro *x) {

  x->num_objects = x->num_objectsSave = GUIR_NUM_RATCHETS;
  x->soundDecay = GUIR_SOUND_DECAY;
  x->coeffs[0] = -GUIR_GOURD_RESON * 2.0 * cos(GUIR_GOURD_FREQ * TWO_PI / x->srate);
  x->coeffs[1] = GUIR_GOURD_RESON*GUIR_GOURD_RESON;
  x->coeffs2[0] = -GUIR_GOURD_RESON2 * 2.0 * cos(GUIR_GOURD_FREQ2 * TWO_PI / x->srate);
  x->coeffs2[1] = GUIR_GOURD_RESON2*GUIR_GOURD_RESON2;
  x->ratchet = x->ratchetDelta = 0.;
  x->guiroScrape = 0.;
}

float guiro_tick(t_guiro *x) {
  float data;
  if (my_random(1024) < x->num_objects) {
    x->sndLevel += 512. * x->ratchet * x->totalEnergy;
  }
  x->input = x->sndLevel;
  x->input *= noise_tick() * x->ratchet;
  x->sndLevel *= x->soundDecay;
		 
  x->input2 = x->input;
  x->input -= x->output[0]*x->coeffs[0];
  x->input -= x->output[1]*x->coeffs[1];
  x->output[1] = x->output[0];
  x->output[0] = x->input;
  x->input2 -= x->output2[0]*x->coeffs2[0];
  x->input2 -= x->output2[1]*x->coeffs2[1];
  x->output2[1] = x->output2[0];
  x->output2[0] = x->input2;
     
  x->finalZ[2] = x->finalZ[1];
  x->finalZ[1] = x->finalZ[0];
  x->finalZ[0] = x->output[1] + x->output2[1];
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
    t_class *c = class_new("guiro~", (method)guiro_new, (method)dsp_free, (long)sizeof(t_guiro), 0L, A_DEFFLOAT, 0);
    
    class_addmethod(c, (method)guiro_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)guiro_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)guiro_float, "float", A_FLOAT, 0);
    class_addmethod(c, (method)guiro_int, "int", A_LONG, 0);
    class_addmethod(c, (method)guiro_bang, "bang", A_CANT, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    guiro_class = c;
}

void guiro_assist(t_guiro *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
            case 0:
                sprintf(s,"(signal/float) number of items");
                break;
            case 1:
                sprintf(s,"(signal/float) resonant frequency");
                break;
            case 2:
                sprintf(s,"(signal/float) damping");
                break;
            case 3:
                sprintf(s,"(signal/float) maximum shake");
                break;
            case 4:
                sprintf(s,"(signal/float) resonance frequency 2");
                break;
        }
	} else {
		sprintf(s,"(signal) output");
    }
}

void guiro_float(t_guiro *x, double f)
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
		x->res_freq2 = f;
	}
}

void guiro_int(t_guiro *x, int f)
{
	guiro_float(x, (double)f);
}

void guiro_bang(t_guiro *x)
{
	post("guiro: scraping");
	x->guiroScrape = 0.;
	/*
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
	*/
}

void *guiro_new(double initial_coeff)
{
	int i;

    t_guiro *x = (t_guiro *)object_alloc(guiro_class);
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_guiro);i++)  
                ((char *)x)[i]=0; 
	} 
    dsp_setup((t_pxobject *)x,5);
    outlet_new((t_object *)x, "signal");
    
    x->srate = sys_getsr();
    x->one_over_srate = 1./x->srate;
    
	x->guiroScrape = 0;
	x->shakeEnergy = 0.0;
	for(i=0; i<2; i++) {
		x->output[i] = 0.;
		x->output2[i] = 0.;
	}
	x->shake_damp = x->shake_dampSave = 0.9;
	x->shake_max = x->shake_maxSave = 0.9;
	x->totalEnergy = 0.9;
	x->input = 0.0;
	x->input2 = 0.0;
	x->sndLevel = 0.0;
	x->gain = 0.0;
	x->soundDecay = 0.0;
	x->systemDecay = 0.0;
	x->res_freq = x->res_freqSave = 2000.; 
	x->res_freq2 = x->res_freq2Save = 3500.;
 	x->collLikely = 0.;
 	x->scrapeVel = 0.00015;
 	x->ratchet=0.0;x->ratchetDelta=0.0005;
 	for(i=0; i<3; i++) {
		x->finalZ[i] = 0.;
	}
    
    guiro_setup(x);
    
    srand(0.54);
    
    return (x);
}

void guiro_dsp64(t_guiro *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->num_objectsConnected = count[0];
	x->shake_dampConnected = count[1];
	x->shake_maxConnected = count[2];
	x->res_freqConnected = count[3];
	x->res_freq2Connected = count[4];
	x->srate = samplerate;
	x->one_over_srate = 1./x->srate;
    
    object_method(dsp64, gensym("dsp_add64"), x, guiro_perform64, 0, NULL);
}

void guiro_perform64(t_guiro *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	double num_objects	= x->num_objectsConnected	? 	*(double *)(ins[0]) : x->num_objects;
	double shake_damp 	= x->shake_dampConnected	? 	*(double *)(ins[1]) : x->shake_damp;
	double shake_max 	= x->shake_maxConnected		? 	*(double *)(ins[2]) : x->shake_max;
	double res_freq 	= x->res_freqConnected		? 	*(double *)(ins[3]) : x->res_freq;
	double res_freq2 	= x->res_freq2Connected		? 	*(double *)(ins[4]) : x->res_freq2;
	
	double *out = (double *)(outs[0]);
	long n = sampleframes;
    
	double lastOutput;
    
    if(num_objects != x->num_objectsSave) {
        if(num_objects < 1.) num_objects = 1.;
        x->num_objects = (long)num_objects;
        x->num_objectsSave = (long)num_objects;
        x->gain = log(num_objects) * 30.0 / (double) num_objects;
    }
    
    if(res_freq != x->res_freqSave) {
        x->res_freqSave = x->res_freq = res_freq;
        x->coeffs[0] = -GUIR_GOURD_RESON * 2.0 * cos(res_freq * TWO_PI / x->srate);
    }
    
    if(shake_damp != x->shake_dampSave) {
        x->shake_dampSave = x->shake_damp = shake_damp;
        //x->systemDecay = .998 + (shake_damp * .002);
        //x->ratchetDelta = shake_damp;
        x->scrapeVel = shake_damp;
    }
    
    if(shake_max != x->shake_maxSave) {
        x->shake_maxSave = x->shake_max = shake_max;
        //x->shakeEnergy += shake_max * MAX_SHAKE * 0.1;
        //if (x->shakeEnergy > MAX_SHAKE) x->shakeEnergy = MAX_SHAKE;
        x->guiroScrape = shake_max;
    }
    
    if(res_freq2 != x->res_freq2Save) {
        x->res_freq2Save = x->res_freq2 = res_freq2;
        x->coeffs2[0] = -GUIR_GOURD_RESON2 * 2.0 * cos(res_freq2 * TWO_PI / x->srate);
    }
    
    
    while(n--) {
        if (x->guiroScrape < 1.0)      {
	      	x->guiroScrape += x->scrapeVel;
	      	x->totalEnergy = x->guiroScrape;
	      	x->ratchet -= (x->ratchetDelta + (0.002*x->totalEnergy));
	      	if (x->ratchet<0.0) x->ratchet = 1.0;
	      	lastOutput = guiro_tick(x);
        }
        else lastOutput = 0.0;
        *out++ = lastOutput;
    }
}

