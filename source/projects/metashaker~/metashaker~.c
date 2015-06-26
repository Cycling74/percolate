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
#define ATTACK 0
#define DECAY 1
#define SUSTAIN 2
#define RELEASE 3
//#define MAX_RANDOM 32768
#define MAX_RANDOM RAND_MAX
#define ONE_OVER_RANDLIMIT 1./RAND_MAX
#define MAX_SHAKE 1.0

#define NUMOBJECTS_SCALE 1000.
#define FREQ_SCALE 20000.

#define SLEI_SOUND_DECAY 0.97
#define SLEI_SYSTEM_DECAY 0.9994
#define SLEI_NUM_BELLS 32.
#define SLEI_CYMB_FREQ0 2500.
#define SLEI_CYMB_FREQ1 5300.
#define SLEI_CYMB_FREQ2 6500.
#define SLEI_CYMB_FREQ3 8300.
#define SLEI_CYMB_FREQ4 9800.
#define SLEI_CYMB_RESON 0.99

#define BAMB_SOUND_DECAY 0.95
#define BAMB_SYSTEM_DECAY 0.99995
#define BAMB_NUM_TUBES 5.
#define BAMB_BASE_FREQ  2800.

#define GUIR_SOUND_DECAY 0.95
#define GUIR_NUM_RATCHETS 128.
#define GUIR_GOURD_FREQ  2500.0
#define GUIR_GOURD_RESON 0.97
#define GUIR_GOURD_FREQ2  4000.0
#define GUIR_GOURD_RESON2 0.97

#define TAMB_SOUND_DECAY 0.95
#define TAMB_SYSTEM_DECAY 0.9985
#define TAMB_NUM_TIMBRELS 32.
#define TAMB_SHELL_FREQ 2300.
#define TAMB_SHELL_GAIN 0.1
#define TAMB_CYMB_FREQ  5600.
#define TAMB_CYMB_FREQ2 8100.
#define TAMB_CYMB_RESON 0.99

#define SEKE_SOUND_DECAY 0.96
#define SEKE_SYSTEM_DECAY 0.999
#define SEKE_NUM_BEANS 64.

#define CABA_SOUND_DECAY 0.95
#define CABA_SYSTEM_DECAY 0.997
#define CABA_NUM_BEADS 512.

#define MARA_SOUND_DECAY 0.95
#define MARA_SYSTEM_DECAY 0.999
#define MARA_NUM_BEANS 25.

#define SLEIGH 10
#define BAMBOO 11
#define GUIRO 12
#define TAMB 13
#define SEKE 14
#define CABA 15
#define MARA 16
#define OFF 17

t_class *metashake_class;

typedef struct _metashake
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars	    
	    
	float guiroScrape;
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
	float gain, gain1, gain2;
	float freq_rand;
	float soundDecay;
	float systemDecay;
	float cymb_rand;
	
	int shakertype;

	float num_objects;
    float shake_damp;
    float shake_max;
	float res_freq;
	    
    float num_objectsSave;	//number of beans	
    float res_freqSave;	//resonance
    float shake_dampSave; 	//damping
    float shake_maxSave;
    float res_freq1, res_freq2, res_freq1Connected, res_freq2Connected;
    float res_freq1Save, res_freq2Save;
    float res_freq3, res_freq4, res_freq3Connected, res_freq4Connected;
    float res_freq3Save, res_freq4Save;
    float res_spread, res_random, res_spreadConnected, res_randomConnected;
    float res_spreadSave, res_randomSave;
    float scrapeVelConnected;
    float scrapeVelSave;

	float collLikely,scrapeVel;
	float totalEnergy;
	float ratchet,ratchetDelta;
	float finalZ[3];	
    
    //signals connected? or controls...
    short num_objectsConnected;
    short res_freqConnected;
    short shake_dampConnected;
    short shake_maxConnected;
   
    float srate, one_over_srate;
    int power;
} t_metashake;

/****PROTOTYPES****/

//setup funcs
void *metashake_new(double val);
void metashake_assist(t_metashake *x, void *b, long m, long a, char *s);

void metashake_dsp64(t_metashake *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void metashake_perform64(t_metashake *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void metashake_float(t_metashake *x, double f);
void metashake_int(t_metashake *x, int f);
void metashake_bang(t_metashake *x);

//setups and ticks
void sleigh_setup(t_metashake *x);
float sleigh_tick(t_metashake *x);
void bamboo_setup(t_metashake *x);
float bamboo_tick(t_metashake *x);
void guiro_setup(t_metashake *x);
float guiro_tick(t_metashake *x);
void tamb_setup(t_metashake *x);
float tamb_tick(t_metashake *x);
void sekere_setup(t_metashake *x);
float sekere_tick(t_metashake *x);
void cabasa_setup(t_metashake *x);
float cabasa_tick(t_metashake *x);
void maraca_setup(t_metashake *x);
float maraca_tick(t_metashake *x);
void metashake_setsleigh(t_metashake *x, t_symbol *s, short argc, t_atom *argv);
void metashake_setbamboo(t_metashake *x, t_symbol *s, short argc, t_atom *argv);
void metashake_setguiro(t_metashake *x, t_symbol *s, short argc, t_atom *argv);
void metashake_settamb(t_metashake *x, t_symbol *s, short argc, t_atom *argv);
void metashake_setseke(t_metashake *x, t_symbol *s, short argc, t_atom *argv);
void metashake_setcabasa(t_metashake *x, t_symbol *s, short argc, t_atom *argv);
void metashake_setmaraca(t_metashake *x, t_symbol *s, short argc, t_atom *argv);
void metashake_setoff(t_metashake *x, t_symbol *s, short argc, t_atom *argv);
void setpower(t_metashake *x, t_symbol *s, short argc, t_atom *argv);

void metashake_clear_dlines(t_metashake *x);

//noise maker
float noise_tick();
int my_random(int max) ;

/****FUNCTIONS****/
void maraca_setup(t_metashake *x) {
  x->num_objects = MARA_NUM_BEANS;
  x->num_objectsSave = x->num_objects;
  x->gain = log(x->num_objects) / log(4.0) * 40. / (float) x->num_objects;
  x->coeffs[0] = -0.96 * 2.0 * cos(3200.0 * TWO_PI / x->srate);
  x->coeffs[1] = 0.96*0.96;
  x->soundDecay = MARA_SOUND_DECAY;
  x->systemDecay = MARA_SYSTEM_DECAY;
}

float maraca_tick(t_metashake *x) {
  float data;
  x->shakeEnergy *= x->systemDecay;         // Exponential system decay
  if (my_random(1024) < x->num_objects)  // If collision
  	x->sndLevel += x->gain * x->shakeEnergy;   //   add energy
  x->input = x->sndLevel * noise_tick();    // Actual Sound is Random
  x->sndLevel *= x->soundDecay;             // Exponential Sound decay 
  x->input -= x->output[0]*x->coeffs[0];       // Do gourd
  x->input -= x->output[1]*x->coeffs[1];       //   resonance
  x->output[1] = x->output[0];              //     filter
  x->output[0] = x->input;                  //       calculations
  data = x->output[0] - x->output[1];
		
  return 40.*data;
}

void cabasa_setup(t_metashake *x) {
  x->num_objects = CABA_NUM_BEADS;
  x->num_objectsSave = x->num_objects;
  x->gain = log(x->num_objects) / log(4.0) * 120.0 / (float) x->num_objects;
  x->coeffs[0] = -0.7 * 2.0 * cos(3000.0 * TWO_PI / x->srate);
  x->coeffs[1] = 0.7*0.7;
  x->soundDecay = CABA_SOUND_DECAY;
  x->systemDecay = CABA_SYSTEM_DECAY;
}

float cabasa_tick(t_metashake *x) {
  float data;
  x->shakeEnergy *= x->systemDecay;         // Exponential system decay
  if (my_random(1024) < x->num_objects)  // If collision
  	x->sndLevel += x->gain * x->shakeEnergy;   //   add energy
  x->input = x->sndLevel * noise_tick();    // Actual Sound is Random
  x->sndLevel *= x->soundDecay;             // Exponential Sound decay 
  x->input -= x->output[0]*x->coeffs[0];       // Do gourd
  x->input -= x->output[1]*x->coeffs[1];       //   resonance
  x->output[1] = x->output[0];              //     filter
  x->output[0] = x->input;                  //       calculations
  data = x->output[0] - x->output[1];
		
  return 10.*data;
}

void sekere_setup(t_metashake *x) {
  x->num_objects = SEKE_NUM_BEANS;
  x->num_objectsSave = x->num_objects;
  x->gain = log(x->num_objects) / log(4.0) * 40.0 / (float) x->num_objects;
  x->coeffs[0] = -0.6 * 2.0 * cos(5500.0 * TWO_PI / x->srate);
  x->coeffs[1] = 0.6*0.6;
  x->soundDecay = SEKE_SOUND_DECAY;
  x->systemDecay = SEKE_SYSTEM_DECAY;
}

float sekere_tick(t_metashake *x) {
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
		
  return 10.*data;
}

void tamb_setup(t_metashake *x) {
  x->num_objects = TAMB_NUM_TIMBRELS;
  x->num_objectsSave = x->num_objects;
  x->soundDecay = TAMB_SOUND_DECAY;
  x->systemDecay = TAMB_SYSTEM_DECAY;
  x->gain = 24.0 / x->num_objects;
  x->coeffs[0] = -0.96 * 2.0 * cos(TAMB_SHELL_FREQ * TWO_PI / x->srate);
  x->coeffs[1] = 0.96*0.96;
  x->coeffs1[0] = -TAMB_CYMB_RESON * 2.0 * cos(TAMB_CYMB_FREQ * TWO_PI / x->srate);
  x->coeffs1[1] = TAMB_CYMB_RESON * TAMB_CYMB_RESON;
  x->coeffs2[0] = -TAMB_CYMB_RESON * 2.0 * cos(TAMB_CYMB_FREQ2 * TWO_PI / x->srate);
  x->coeffs2[1] = TAMB_CYMB_RESON * TAMB_CYMB_RESON;
}

float tamb_tick(t_metashake *x) {
  float data;
  x->shakeEnergy *= x->systemDecay;    // Exponential System Decay
  if (my_random(1024) < x->num_objects) {     
    x->sndLevel += x->gain *  x->shakeEnergy;   
    x->cymb_rand = noise_tick() * x->res_freq1 * x->res_random;// * 0.05;
    x->coeffs1[0] = -TAMB_CYMB_RESON * 2.0 * 
      cos((x->res_freq1 + x->cymb_rand) * TWO_PI / x->srate);
    x->cymb_rand = noise_tick() * x->res_freq2 * x->res_random;//* 0.05;
    x->coeffs2[0] = -TAMB_CYMB_RESON * 2.0 * 
      cos((x->res_freq2 + x->cymb_rand) * TWO_PI / x->srate);
  }
  x->input = x->sndLevel;
  x->input *= noise_tick();         // Actual Sound is Random
  x->input1 = x->input * 0.8;
  x->input2 = x->input;
  x->input *= TAMB_SHELL_GAIN;
	
  x->sndLevel *= x->soundDecay;          // Each (all) event(s) 
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
	
  x->finalZ[2] = x->finalZ[1];
  x->finalZ[1] = x->finalZ[0];
  x->finalZ[0] = data;
  data = x->finalZ[2] - x->finalZ[0];
		
  return 100.*data; //tambourine is quiet...
}

void guiro_setup(t_metashake *x) {
  x->num_objects = GUIR_NUM_RATCHETS;
  x->num_objectsSave = x->num_objects;
  x->soundDecay = GUIR_SOUND_DECAY;
  x->coeffs[0] = -GUIR_GOURD_RESON * 2.0 * cos(GUIR_GOURD_FREQ * TWO_PI / x->srate);
  x->coeffs[1] = GUIR_GOURD_RESON*GUIR_GOURD_RESON;
  x->coeffs1[0] = -GUIR_GOURD_RESON2 * 2.0 * cos(GUIR_GOURD_FREQ2 * TWO_PI / x->srate);
  x->coeffs1[1] = GUIR_GOURD_RESON2*GUIR_GOURD_RESON2;
  x->ratchet = 0.;
  x->guiroScrape = 0.;
}

float guiro_tick(t_metashake *x) {
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
  x->input2 -= x->output2[0]*x->coeffs1[0];
  x->input2 -= x->output2[1]*x->coeffs1[1];
  x->output2[1] = x->output2[0];
  x->output2[0] = x->input2;
     
  x->finalZ[2] = x->finalZ[1];
  x->finalZ[1] = x->finalZ[0];
  x->finalZ[0] = x->output[1] + x->output2[1];
  data = x->finalZ[0] - x->finalZ[2];
		
  return 0.05*data; //guiro is LOUD
}

void bamboo_setup(t_metashake *x) {
  x->num_objects = BAMB_NUM_TUBES;
  x->num_objectsSave = x->num_objects;
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

float bamboo_tick(t_metashake *x) {
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
  return 5.*data;		
}

void sleigh_setup(t_metashake *x) {
  x->num_objects = SLEI_NUM_BELLS;
  x->num_objectsSave = x->num_objects;
  x->soundDecay = SLEI_SOUND_DECAY;
  x->systemDecay = SLEI_SYSTEM_DECAY;
  /*x->res_freq = SLEI_CYMB_FREQ0;
  x->res_freq1 = SLEI_CYMB_FREQ1;
  x->res_freq2 = SLEI_CYMB_FREQ2;
  x->res_freq3 = SLEI_CYMB_FREQ3;
  x->res_freq4 = SLEI_CYMB_FREQ4;*/

  //x->gain = 8.0 / x->num_objects;
  x->gain = log(x->num_objects) * 30. / (float)x->num_objects;

  x->coeffs[1] = SLEI_CYMB_RESON*SLEI_CYMB_RESON;
  x->coeffs1[1] = SLEI_CYMB_RESON*SLEI_CYMB_RESON;
  x->coeffs2[1] = SLEI_CYMB_RESON*SLEI_CYMB_RESON;                      
  x->coeffs3[1] = SLEI_CYMB_RESON*SLEI_CYMB_RESON;
  x->coeffs4[1] = SLEI_CYMB_RESON*SLEI_CYMB_RESON;
}

float sleigh_tick(t_metashake *x) {
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
		
  return 5.*data;
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
    t_class *c = class_new("metashaker~", (method)metashake_new, (method)dsp_free, (long)sizeof(t_metashake), 0L, A_DEFFLOAT, 0);
    
    class_addmethod(c, (method)metashake_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)metashake_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)metashake_float, "float", A_FLOAT, 0);
    class_addmethod(c, (method)metashake_int, "int", A_LONG, 0);
    class_addmethod(c, (method)metashake_bang, "bang", A_CANT, 0);

    class_addmethod(c, (method)metashake_setsleigh, "sleigh", A_GIMME, 0);
    class_addmethod(c, (method)metashake_setbamboo, "bamboo", A_GIMME, 0);
    class_addmethod(c, (method)metashake_setguiro, "guiro", A_GIMME, 0);
    class_addmethod(c, (method)metashake_settamb, "tambourine", A_GIMME, 0);
    class_addmethod(c, (method)metashake_setseke, "sekere", A_GIMME, 0);
    class_addmethod(c, (method)metashake_setcabasa, "cabasa", A_GIMME, 0);
    class_addmethod(c, (method)metashake_setmaraca, "maraca", A_GIMME, 0);
    class_addmethod(c, (method)metashake_setoff, "off", A_GIMME, 0);
    class_addmethod(c, (method)setpower, "power", A_GIMME, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    metashake_class = c;
}

void metashake_setsleigh(t_metashake *x, t_symbol *s, short argc, t_atom *argv)
{	
	post("metashaker: sleigh bells");
	metashake_clear_dlines(x);
	
	x->guiroScrape = 1.;
	x->totalEnergy = 0.;
	x->sndLevel = 0.;
	
	x->shakertype = SLEIGH;
	sleigh_setup(x);
}

void metashake_setoff(t_metashake *x, t_symbol *s, short argc, t_atom *argv)
{	
	post("metashaker: turning off");
	metashake_clear_dlines(x);
	
	x->guiroScrape = 1.;
	x->totalEnergy = 0.;
	x->sndLevel = 0.;
	
	x->shakertype = OFF;
}


void metashake_setseke(t_metashake *x, t_symbol *s, short argc, t_atom *argv)
{	
	post("metashaker: sekere");
	metashake_clear_dlines(x);
	
	x->guiroScrape = 1.;
	x->totalEnergy = 0.;
	x->sndLevel = 0.;
	
	x->shakertype = SEKE;
	sekere_setup(x);
}

void metashake_settamb(t_metashake *x, t_symbol *s, short argc, t_atom *argv)
{	
	post("metashaker: tambourine");
	metashake_clear_dlines(x);
	
	x->guiroScrape = 1.;
	x->totalEnergy = 0.;
	x->sndLevel = 0.;
	
	x->shakertype = TAMB;
	tamb_setup(x);
}

void metashake_setguiro(t_metashake *x, t_symbol *s, short argc, t_atom *argv)
{	
	post("metashaker: guiro");
	metashake_clear_dlines(x);
	
	x->guiroScrape = 0;
	x->scrapeVel = 0.00015;
	
	x->shakertype = GUIRO;
	guiro_setup(x);
}

void metashake_setbamboo(t_metashake *x, t_symbol *s, short argc, t_atom *argv)
{	
	post("metashaker: bamboo chimes");
	metashake_clear_dlines(x);
	
	x->guiroScrape = 1.;
	x->totalEnergy = 0.;
	x->sndLevel = 0.;
	
	x->shakertype = BAMBOO;
	bamboo_setup(x);
}

void metashake_setcabasa(t_metashake *x, t_symbol *s, short argc, t_atom *argv)
{	
	post("metashaker: cabasa");
	metashake_clear_dlines(x);
	
	x->guiroScrape = 1.;
	x->totalEnergy = 0.;
	x->sndLevel = 0.;
	
	x->shakertype = CABA;
	cabasa_setup(x);
}

void metashake_setmaraca(t_metashake *x, t_symbol *s, short argc, t_atom *argv)
{	
	post("metashaker: maraca");
	metashake_clear_dlines(x);
	
	x->guiroScrape = 1.;
	x->totalEnergy = 0.;
	x->sndLevel = 0.;
	
	x->shakertype = MARA;
	maraca_setup(x);
}

void metashake_assist(t_metashake *x, void *b, long m, long a, char *s)
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
                sprintf(s,"(signal/float) resonance frequency 1");
                break;
            case 5:
                sprintf(s,"(signal/float) resonance frequency 2");
                break;
            case 6:
                sprintf(s,"(signal/float) resonance frequency 3");
                break;
            case 7:
                sprintf(s,"(signal/float) resonance frequency 4");
                break;
            case 8:
                sprintf(s,"(signal/float) scrape velocity");
                break;
            case 9:
                sprintf(s,"(signal/float) resonant spread");
                break;
            case 10:
                sprintf(s,"(signal/float) resonance random");
                break;
        }
	} else {
		sprintf(s,"(signal) output");
    }

}

void metashake_float(t_metashake *x, double f)
{
	if (x->x_obj.z_in == 0) {
		x->num_objects = f;
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
	} else if (x->x_obj.z_in == 8) {
		x->scrapeVel = f;
	} else if (x->x_obj.z_in == 9) {
		x->res_spread = f;
	} else if (x->x_obj.z_in == 10) {
		x->res_random = f;
	}
}

void metashake_int(t_metashake *x, int f)
{
	metashake_float(x, (double)f);
}

void metashake_bang(t_metashake *x)
{
	int i;
	post("metashake: zeroing delay lines");
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

void setpower(t_metashake *x, t_symbol *s, short argc, t_atom *argv)
{
	short i;
	int temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (int)argv[i].a_w.w_long;
				x->power = temp;
    			post("metashake: setting power: %d", temp);
				break;
			case A_FLOAT:
				temp = (int)argv[i].a_w.w_long;
				x->power = temp;
    			post("shake: setting power: %d", temp);
				break;
		}
	}
}


void metashake_clear_dlines(t_metashake *x)
{
	int i;
	post("metashake: zeroing delay lines");
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

void *metashake_new(double initial_coeff)
{
	int i;

    t_metashake *x = (t_metashake *)object_alloc(metashake_class);
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_metashake);i++)  
                ((char *)x)[i]=0; 
	} 
    dsp_setup((t_pxobject *)x,11);
    outlet_new((t_object *)x, "signal");
    
    x->srate = sys_getsr();
    x->one_over_srate = 1./x->srate;
    x->power = 1;

	x->guiroScrape = 0;
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
	x->gain = 0.0; x->gain1 = 0; x->gain2 = 0;
	x->freq_rand = 0.0;
	x->soundDecay = 0.0;
	x->systemDecay = 0.0;
	x->cymb_rand = 0.0;
	x->num_objects = x->num_objectsSave = 20;
	x->totalEnergy = 0.;
	x->res_spread = x->res_spreadSave = 0.;
	x->res_random = x->res_randomSave = 0.;	
	x->res_freq = x->res_freq1 = x->res_freq2 = x->res_freq3 =x->res_freq4 = 2220.;
	x->res_freqSave = x->res_freq1Save = x->res_freq2Save = x->res_freq3Save =x->res_freqSave = 2220.;
 	x->collLikely = 0.;
 	x->scrapeVel = x->scrapeVelSave = 0.00015;
 	x->ratchet=0.0; x->ratchetDelta=0.0005;
 	x->shake_damp = x->shake_dampSave = 0.9;
 	x->shake_max = x->shake_maxSave = 0.9;
 	for(i=0; i<3; i++) {
		x->finalZ[i] = 0.;
	}
	
	x->shakertype = SLEIGH;
    
    sleigh_setup(x);
    
    srand(0.54);
    
    return (x);
}

void metashake_dsp64(t_metashake *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->num_objectsConnected = count[0];
	x->shake_dampConnected = count[1];
	x->shake_maxConnected = count[2];
	x->res_freqConnected = count[3];
	x->res_freq1Connected = count[4];
	x->res_freq2Connected = count[5];
	x->res_freq3Connected = count[6];
	x->res_freq4Connected = count[7];
	x->scrapeVelConnected = count[8];
	x->res_spreadConnected = count[9];
	x->res_randomConnected = count[10];
	
	x->srate = samplerate;
	x->one_over_srate = 1./x->srate;
    object_method(dsp64, gensym("dsp_add64"), x, metashake_perform64, 0, NULL);
}

void metashake_perform64(t_metashake *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double num_objects	= x->num_objectsConnected	? 	*(t_double *)(ins[0]) : x->num_objects;
	t_double shake_damp 	= x->shake_dampConnected	? 	*(t_double *)(ins[1]) : x->shake_damp;
	t_double shake_max 	= x->shake_maxConnected         ? 	*(t_double *)(ins[2]) : x->shake_max;
	t_double res_freq 		= x->res_freqConnected		? 	*(t_double *)(ins[3]) : x->res_freq;
	t_double res_freq1 	= x->res_freq1Connected         ? 	*(t_double *)(ins[4]) : x->res_freq1;
	t_double res_freq2 	= x->res_freq2Connected         ? 	*(t_double *)(ins[5]) : x->res_freq2;
	t_double res_freq3 	= x->res_freq3Connected         ? 	*(t_double *)(ins[6]) : x->res_freq3;
	t_double res_freq4 	= x->res_freq4Connected         ? 	*(t_double *)(ins[7]) : x->res_freq4;
	
	t_double scrapeVel 	= x->scrapeVelConnected         ? 	*(t_double *)(ins[8]) : x->scrapeVel;
	t_double res_spread 	= x->res_spreadConnected	? 	*(t_double *)(ins[9]) : x->res_spread;
	t_double res_random 	= x->res_randomConnected	? 	*(t_double *)(ins[10]) : x->res_random;
    
	t_double *out = (t_double *)(outs[0]);
	long n = sampleframes;
    
	t_double lastOutput, temp;
    
	//if(num_objects < 1.) num_objects *= NUMOBJECTS_SCALE;
	
	if(!x->power)  {
		while(n--) *out++ = 0.;
	}
	else if(x->shakertype == MARA) {
        
		if(num_objects != x->num_objectsSave) {
			if(num_objects < 1.) num_objects = 1.;
			x->num_objects = num_objects;
			x->num_objectsSave = num_objects;
			x->gain = log(num_objects) / log(4.0) * 120.0 / (float) num_objects;
		}
		
		if(res_freq != x->res_freqSave) {
			//res_freq *= FREQ_SCALE;
			x->res_freqSave = x->res_freq = res_freq;
	  		x->coeffs[0] = -0.96 * 2.0 * cos(res_freq * TWO_PI / x->srate);
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
			lastOutput = maraca_tick(x);
			*out++ = lastOutput;
		}
	}
	
	else if(x->shakertype == CABA) {
        
		if(num_objects != x->num_objectsSave) {
			if(num_objects < 1.) num_objects = 1.;
			x->num_objects = num_objects;
			x->num_objectsSave = num_objects;
			x->gain = log(num_objects) / log(4.0) * 120.0 / (float) num_objects;
		}
		if(res_freq != x->res_freqSave) {
			//res_freq *= FREQ_SCALE;
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
			*out++ = 10.*lastOutput;
		}
	}
	
	else if(x->shakertype == SEKE) {
        
		if(num_objects != x->num_objectsSave) {
			if(num_objects < 1.) num_objects = 1.;
			x->num_objects = num_objects;
			x->num_objectsSave = num_objects;
			//x->gain = log(num_objects) * 30. / (float)num_objects;
			x->gain = log(num_objects) / log(4.0) * 40.0 / (float)num_objects;
		}
		
		if(res_freq != x->res_freqSave) {
			//res_freq *= FREQ_SCALE;
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
			*out++ = 10.*lastOutput;
		}
	}
    
	else if(x->shakertype == GUIRO) {
		if(num_objects != x->num_objectsSave) {
			if(num_objects < 1.) num_objects = 1.;
			x->num_objects = num_objects;
			x->num_objectsSave = num_objects;
			x->gain = log(num_objects) * 30.0 / (float) num_objects;
		}
		
		if(res_freq != x->res_freqSave) {
			//res_freq *= FREQ_SCALE;
			x->res_freqSave = x->res_freq = res_freq;
			x->coeffs[0] = -GUIR_GOURD_RESON * 2.0 * cos(res_freq * TWO_PI / x->srate);
		}
		
		if(scrapeVel != x->scrapeVelSave) {
			x->scrapeVelSave = x->scrapeVel = scrapeVel;
			//x->scrapeVel = shake_damp;
		}
		
		if(shake_max != x->shake_maxSave) {
			x->shake_maxSave = x->shake_max = shake_max;
	    	x->guiroScrape = shake_max;
		}
        
		if(res_freq1 != x->res_freq1Save) {
			//res_freq1 *= FREQ_SCALE;
			x->res_freq1Save = x->res_freq1 = res_freq1;
			x->coeffs1[0] = -GUIR_GOURD_RESON2 * 2.0 * cos(res_freq1 * TWO_PI / x->srate);
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
	
	else if(x->shakertype == TAMB) {
		
		if(num_objects != x->num_objectsSave) {
			if(num_objects < 1.) num_objects = 1.;
			x->num_objects = num_objects;
			x->num_objectsSave = num_objects;
			x->gain = 24.0 / x->num_objects;
		}
		
		if(res_freq != x->res_freqSave) {
			//res_freq *= FREQ_SCALE;
			x->res_freqSave = x->res_freq = res_freq;
			x->coeffs[0] = -0.96 * 2.0 * cos(res_freq * TWO_PI / x->srate);
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
			//res_freq1 *= FREQ_SCALE;
			x->res_freq1Save = x->res_freq1 = res_freq1;
			//x->coeffs1[0] = -TAMB_CYMB_RESON * 2.0 * cos(res_freq1 * TWO_PI / x->srate);
		}
		
		if(res_freq2 != x->res_freq2Save) {
			//res_freq2 *= FREQ_SCALE;
			x->res_freq2Save = x->res_freq2 = res_freq2;
			//x->coeffs2[0] = -TAMB_CYMB_RESON * 2.0 * cos(res_freq2 * TWO_PI / x->srate);
		}
		if(res_random != x->res_randomSave) {
			x->res_random = x->res_randomSave = res_random;
			if (x->res_random > .4) x->res_random = .4;
			if (x->res_random < 0.) x->res_random = 0.;
		}
		
		while(n--) {
			lastOutput = tamb_tick(x);
			*out++ = lastOutput;
		}
        
	}
	
	else if(x->shakertype == SLEIGH) {
		if(num_objects != x->num_objectsSave) {
			if(num_objects < 1.) num_objects = 1.;
			x->num_objects = num_objects;
			x->num_objectsSave = num_objects;
			x->gain = log(num_objects) * 30. / (float)num_objects;
		}
		
		if(res_freq != x->res_freqSave) {
			x->res_freqSave = x->res_freq = res_freq;//*FREQ_SCALE;
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
			x->res_freq1Save = x->res_freq1 = res_freq1;//*FREQ_SCALE;
		}
		
		if(res_freq2 != x->res_freq2Save) {
			x->res_freq2Save = x->res_freq2 = res_freq2;//*FREQ_SCALE;
		}
		
		if(res_freq3 != x->res_freq3Save) {
			x->res_freq3Save = x->res_freq3 = res_freq3;//*FREQ_SCALE;
		}
		
		if(res_freq4 != x->res_freq4Save) {
			x->res_freq4Save = x->res_freq4 = res_freq4;//*FREQ_SCALE;
		}
		while(n--) {
			lastOutput = sleigh_tick(x);
			*out++ = lastOutput;
		}
	}
	else if(x->shakertype == BAMBOO) {
		if(num_objects != x->num_objectsSave) {
			if(num_objects < 1.) num_objects = 1.;
			x->num_objects = num_objects;
			x->num_objectsSave = num_objects;
			x->gain = log(num_objects) * 30. / (float)num_objects;
		}
        
		if(res_freq != x->res_freqSave) {
			x->res_freqSave = x->res_freq = res_freq;//*FREQ_SCALE;
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
			x->res_spread = x->res_spreadSave = res_spread;
			if (x->res_spread > .4) x->res_spread = .4;
			if (x->res_spread < 0.) x->res_spread = 0.;
		}
		
		if(res_random != x->res_randomSave) {
			x->res_random = x->res_randomSave = res_random;
			if (x->res_random > .4) x->res_random = .4;
			if (x->res_random < 0.) x->res_random = 0.;
		}
        
		while(n--) {
			lastOutput = bamboo_tick(x);
			*out++ = lastOutput;
		}
	}
	
	else if(x->shakertype == OFF) {			
		while(n--) {
			lastOutput = 0.;		
			*out++ = lastOutput;
		}
	}
}
