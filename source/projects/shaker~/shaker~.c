// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#define TWOPI 6.283185307
//#define ONE_OVER_RANDLIMIT 0.00006103516 // constant = 1. / 16384.0
#define ONE_OVER_RANDLIMIT 1./RAND_MAX 
#define ATTACK 0
#define DECAY 1
#define SUSTAIN 2
#define RELEASE 3
#define MAX_RANDOM RAND_MAX


t_class *shaker_class;

typedef struct _shaker
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars
    long num_beans;	//number of beans	
    float res_freq;	//resonance
    float shake_damp; 	//damping
    float shake_speed;
    long shake_times;
    float shake_max;
    
    long num_beansSave;	//number of beans	
    float res_freqSave;	//resonance
    float shake_dampSave; 	//damping
    float shake_speedSave;
    long shake_timesSave;
    float shake_maxSave;
    
    //other vars
    long wait_time;
    long shake_num;
    float coll_damp;
    float shakeEnergy;
    float shakeVel;
    float noiseGain;
    float gain_norm;
        
    //signals connected? or controls...
    short num_beansConnected;
    short res_freqConnected;
    short shake_dampConnected;
    short shake_speedConnected;
    short shake_timesConnected;
    short shake_maxConnected;
    
    //biquad stuff
    float bq_inputs[2];
    float bq_lastOutput;
    float bq_zeroCoeffs[2], bq_poleCoeffs[2];
    float bq_gain;
    
    //ADSR stuff
    float e_target;
    float e_value;
    float e_rate;
    float e_attackRate;
    float e_decayRate;
    float e_sustainLevel;
    float e_releaseRate;
    float e_state;
    float attack_ratio, decay_ratio, release_ratio;

    float srate, one_over_srate;
} t_shaker;

/****PROTOTYPES****/

//setup funcs
void *shaker_new(double val);
void shaker_assist(t_shaker *x, void *b, long m, long a, char *s);

void shaker_float(t_shaker *x, double f);
void shaker_int(t_shaker *x, int f);
void shaker_bang(t_shaker *x);

// dsp stuff
void shaker_dsp64(t_shaker *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void shaker_perform64(t_shaker *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

//noise maker
float noise_tick();

//biquad funcs
void bq_setFreqAndReson(t_shaker *x, float freq, float reson);
void bq_setEqualGainZeros(t_shaker *x);
void bq_setGain(t_shaker *x, float gain);
float bq_tick(t_shaker *x, float sample);

//ADSR funcs
void e_keyOn(t_shaker *x);
void e_keyOff(t_shaker *x);
void e_setAttackRate(t_shaker *x, float rate);
void e_setDecayRate(t_shaker *x, float rate);
void e_setSustainLevel(t_shaker *x, float level);
void e_setReleaseRate(t_shaker *x, float rate);
void e_setAll(t_shaker *x, float attRate, float decRate, float susLevel, float relRate);
float e_tick(t_shaker *x);
void shaker_adr(t_shaker *x, t_symbol *s, long argc, t_atom *argv);

//shaker funcs
void shake(t_shaker *x, float amplitude);
void setFreq(t_shaker *x, float freq);
void noteOn(t_shaker *x, float freq, float amp);
void noteOff(t_shaker *x, float amplitude);
long one_in(long one_in_howmany);

/****FUNCTIONS****/

//shaker funcs
void shake(t_shaker *x, float amplitude)
{
	x->shake_max = 2. * amplitude;
	x->shake_speed = .0008 + (amplitude * .0004);
	x->shake_num = x->shake_times;
	e_setAll(x, x->shake_speed, x->shake_speed, 0., x->shake_speed);
	e_keyOn(x);
}


void setFreq(t_shaker *x, float freq)
{
	bq_setFreqAndReson(x, freq, 0.96);
}

void noteOn(t_shaker *x, float freq, float amp)
{
	bq_setFreqAndReson(x, freq, 0.96);
	shake(x, amp);
}

void noteOff(t_shaker *x, float amplitude)
{
	x->shake_num = 0;
}

long one_in(long one_in_howmany)
{
	if(rand() < one_in_howmany) return 1;
	else return 0;
}


//ADSR funcs
void e_keyOn(t_shaker *x)
{
	x->e_target = 1.;
	x->e_rate = x->e_attackRate;
	x->e_state = ATTACK;
}

void e_keyOff(t_shaker *x)
{
	x->e_target = 0.;
	x->e_rate = x->e_releaseRate;
	x->e_state = RELEASE;
}

void e_setAttackRate(t_shaker *x, float rate)
{
	if(rate < 0.) rate = -rate;
	x->e_attackRate = rate * 22050./x->srate;
}

void e_setDecayRate(t_shaker *x, float rate)
{
	if(rate < 0.) rate = -rate;
	x->e_decayRate = rate;
}

void e_setSustainLevel(t_shaker *x, float level)
{
	if(level < 0.) level = 0.;
	x->e_sustainLevel = level;
}

void e_setReleaseRate(t_shaker *x, float rate)
{
	if(rate < 0.) rate = -rate;
	x->e_releaseRate = rate * 22050./x->srate;
}

void e_setAll(t_shaker *x, float attRate, float decRate, float susLevel, float relRate)
{
	 e_setAttackRate(x, attRate);
	 e_setDecayRate(x,  decRate);
	 e_setSustainLevel(x,  susLevel);
	 e_setReleaseRate(x,  relRate);
}
	
float e_tick(t_shaker *x)
{
	if(x->e_state == ATTACK) {
		x->e_value += x->e_rate;
		if(x->e_value > x->e_target) {
			x->e_value = x->e_target;
			x->e_rate = x->e_decayRate;
			x->e_target = x->e_sustainLevel;
			x->e_state = DECAY;
		}
	}
	else if(x->e_state == DECAY) {
		x->e_value -= x->e_decayRate;
		if(x->e_value <= x->e_sustainLevel) {
			x->e_value = x->e_sustainLevel;
			x->e_rate = 0.;
			x->e_state = SUSTAIN;	
		}
	}
	else if(x->e_state == RELEASE) {
		x->e_value -= x->e_releaseRate;
		if(x->e_value <= 0.) {
			x->e_value = 0.;
			x->e_state = 4;
		}
	}
	return x->e_value;
}

void bq_setFreqAndReson(t_shaker *x, float freq, float reson)
{
	x->bq_poleCoeffs[1] = -(reson*reson);
	x->bq_poleCoeffs[0] = 2. * reson * cos(TWOPI * freq / x->srate);
}

void bq_setEqualGainZeros(t_shaker *x)
{
	x->bq_zeroCoeffs[1] = -1.;
	x->bq_zeroCoeffs[0] = 0.;
}

void bq_setGain(t_shaker *x, float gain)
{
	x->bq_gain = gain;
}

float bq_tick(t_shaker *x, float sample)
{
	float temp;
	float output;
	
	temp = sample * x->bq_gain;
	temp += x->bq_inputs[0] * x->bq_poleCoeffs[0];
	temp += x->bq_inputs[1] * x->bq_poleCoeffs[1];
	
	output = temp;
	output += x->bq_inputs[0] * x->bq_zeroCoeffs[0];
	output += x->bq_inputs[1] * x->bq_zeroCoeffs[1];
	x->bq_inputs[1] = x->bq_inputs[0];
	x->bq_inputs[0] = temp;
	
	x->bq_lastOutput = output;
	
	return output;
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
    t_class *c = class_new("shaker~", (method)shaker_new, (method)dsp_free, (long)sizeof(t_shaker), 0L, A_DEFFLOAT, 0);
    
    class_addmethod(c, (method)shaker_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)shaker_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)shaker_adr, "envelope", A_GIMME, 0);
    class_addmethod(c, (method)shaker_float, "float", A_FLOAT, 0);
    class_addmethod(c, (method)shaker_int, "int", A_LONG, 0);
    class_addmethod(c, (method)shaker_bang, "bang", A_CANT, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    shaker_class = c;
}

void shaker_assist(t_shaker *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
            case 0:
                sprintf(s,"(signal/float) number of beans");
                break;
            case 1:
                sprintf(s,"(signal/float) resonance");
                break;
            case 2:
                sprintf(s,"(signal/float) damping");
                break;
            case 3:
                sprintf(s,"(signal/float) shake speed");
                break;
            case 4:
                sprintf(s,"(signal/float) shake max");
                break;
        }
	} else {
		sprintf(s,"(signal) output");
    }
}

void shaker_float(t_shaker *x, double f)
{
	if (x->x_obj.z_in == 0) {
		x->num_beans = (long)f;
	} else if (x->x_obj.z_in == 1) {
		x->res_freq = f;
	} else if (x->x_obj.z_in == 2) {
		//x->shake_damp = .98 + f*0.02;
		x->shake_damp = f;
	} else if (x->x_obj.z_in == 3) {
		//x->shake_speed = f * 0.002;
		x->shake_speed = f;
	} else if (x->x_obj.z_in == 4) {
		//x->shake_max = f * 2.;
		x->shake_max = f;
	}
}

void shaker_int(t_shaker *x, int f)
{
	shaker_float(x, (double)f);
}

void shaker_bang(t_shaker *x)
{
	post("shaker: zeroing delay lines");
	x->bq_inputs[0] = 0.;
	x->bq_inputs[1] = 0.;
    x->bq_lastOutput = 0.;
}

void *shaker_new(double initial_coeff)
{
	int i;

    t_shaker *x = (t_shaker *)object_alloc(shaker_class);
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_shaker);i++)  
                ((char *)x)[i]=0; 
	} 
    dsp_setup((t_pxobject *)x,5);
    outlet_new((t_object *)x, "signal");
    
    x->srate = sys_getsr();
    x->one_over_srate = 1./x->srate;
    
    //clear stuff
 	x->bq_inputs[0] = x->bq_inputs[1] = x->bq_lastOutput = 0.;
 	
 	//init stuff
 	x->res_freq = 3200.;
 	bq_setFreqAndReson(x, x->res_freq, 0.96);
 	bq_setEqualGainZeros(x);
 	bq_setGain(x, 1.);
 	x->shake_speed = 0.001;
 	e_setAll(x, x->shake_speed, x->shake_speed, 0., x->shake_speed);
 	x->shakeEnergy = 0.;
 	x->noiseGain = 0.;
 	x->coll_damp = 0.95;
 	x->shake_damp = 0.999;
 	x->num_beans = 8;
 	x->wait_time = MAX_RANDOM / x->num_beans;
 	x->gain_norm = 0.0005;
 	x->shake_times = x->shake_num = 100;
 	
 	x->num_beansSave = -1;	
    x->res_freqSave = -1.;	
    x->shake_dampSave = -1.; 	
    x->shake_speedSave = -1.;
    x->shake_timesSave = -1;
    x->shake_maxSave = -1.;
    
    x->attack_ratio = x->decay_ratio = x->release_ratio = 1.;
 	
    srand(0.54);
    
    return (x);
}

//set attack, decay, release ratios
void shaker_adr(t_shaker *x, t_symbol *s, long argc, t_atom *argv)
{
	if(argc < 3) {
		post("shaker: need three arguments (attack ratio, decay ratio, release ratio");
		return;
	}
	x->attack_ratio = argv[0].a_w.w_float;
	x->decay_ratio = argv[1].a_w.w_float;
	x->release_ratio = argv[2].a_w.w_float;
	post("attack ratio = %f, decay ratio = %f, release ratio = %f", x->attack_ratio, x->decay_ratio, x->release_ratio);
	
}

void shaker_dsp64(t_shaker *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->num_beansConnected = count[0];
	x->res_freqConnected = count[1];
	x->shake_dampConnected = count[2];
	x->shake_speedConnected = count[3];
	x->shake_maxConnected = count[4];
	
	x->srate = samplerate;
	x->one_over_srate = 1./x->srate;
    object_method(dsp64, gensym("dsp_add64"), x, shaker_perform64, 0, NULL);
}

void shaker_perform64(t_shaker *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double num_beans		= x->num_beansConnected		? 	*(t_double *)(ins[0]) : x->num_beans;
	t_double res_freq 		= x->res_freqConnected		? 	*(t_double *)(ins[1]) : x->res_freq;
	t_double shake_damp 	= x->shake_dampConnected	? 	*(t_double *)(ins[2]) : x->shake_damp;
	t_double shake_speed	= x->shake_speedConnected	? 	*(t_double *)(ins[3]) : x->shake_speed;
	t_double shake_max      = x->shake_maxConnected		? 	*(t_double *)(ins[4]) : x->shake_max;
	
	t_double *out = (t_double *)(outs[0]);
	long n = sampleframes;
	
	t_double temp;
	int state = x->e_state;
	long shake_num = x->shake_num;
	t_double gain_norm = x->gain_norm;
	long wait_time = x->wait_time;
	t_double lastOutput;
	t_double coll_damp = x->coll_damp;
	
	if(num_beans != x->num_beansSave) {
		num_beans = 129 - num_beans;
		x->num_beans = num_beans;
		x->num_beansSave = num_beans;
		wait_time = x->wait_time = MAX_RANDOM / num_beans;
	}
	
	if(res_freq != x->res_freqSave) {
		x->res_freqSave = x->res_freq = res_freq;
		bq_setFreqAndReson(x, res_freq, 0.96);
	}
	
	if(shake_damp != x->shake_dampSave) {
		x->shake_dampSave = x->shake_damp = (.98 + 0.02*shake_damp);
	}
	
	if(shake_speed != x->shake_speedSave) {
		x->shake_speedSave = x->shake_speed = shake_speed * .002;
		e_setAll(x, shake_speed, shake_speed, 0., shake_speed);
	}
	
	if(shake_max != x->shake_maxSave) {
		x->shake_maxSave = x->shake_max = 2.*shake_max;
		temp = (shake_max * 0.5 - 0.5) * 0.0002;
		temp += shake_speed;
		e_setAll(x, temp*x->attack_ratio, temp*x->decay_ratio, 0., temp*x->release_ratio);
		e_keyOn(x);
	}
	
    
	while(n--) {
		temp = e_tick(x) * shake_max;
		if(shake_num > 0) {
			if(state == SUSTAIN) {
				if(shake_num < 64) {
					shake_num -= 1;
					x->shake_num -= 1;
				}
			}
		}
		if(temp > x->shakeEnergy) x->shakeEnergy = temp;
		x->shakeEnergy *= shake_damp;
		
		if(one_in(wait_time) == 1) {
			x->noiseGain += gain_norm * x->shakeEnergy * num_beans;
		}
		
		lastOutput = x->noiseGain * noise_tick();
		x->noiseGain *= coll_damp;
		lastOutput = bq_tick(x, lastOutput);
		
		*out++ = lastOutput;
	}
}

