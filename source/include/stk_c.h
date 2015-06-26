/************************************************/ 
/* PeRColate, v 0.9 beta						*/
/*												*/
/* Port of many of the function from the       	*/
/* Synthesis Toolkit (STK), originally by		*/
/* Perry Cook and Gary Scavone.					*/
/*												*/
/* Ported to MSP by Dan Trueman					*/
/*												*/
/* The STK is in C++, so most of this port		*/
/* simply involved translating the classes		*/
/* into typedefs with associated function 		*/
/* calls. In addition, most control scaling		*/
/* is left to the user in MAX, so most 			*/
/* applications of ADSRs and Envelopes are		*/
/* irrelevant.									*/
/*												*/
/* I have left most of the original commentary	*/
/* in, and some of it reflects the C++			*/
/* heritage (!) of the code. Also, I prefer 	*/
/* having all the functions in a single file--	*/
/* call me an idiot if you like--but, in a 		*/
/* future version, we may consider modularizing */
/* it, if it seems like I might look less like	*/
/* an idiot in doing so.						*/
/*												*/
/* DLT, 2/2000									*/
/*												*/
/************************************************/
#include "ext.h"
#include "ext_obex.h"

#include "z_dsp.h"
#ifdef WIN_VERSION
#include <sys/stat.h>
#else
#include <stat.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//#define PI 3.141592654
#define TWO_PI 6.283185307
#define RAWWAVE_PATH ":externals:audio:PeRColate_objects:rawwaves"
//#define ONE_OVER_RANDLIMIT 0.00006103516 // constant = 1. / 16384.0
#define ONE_OVER_RANDLIMIT 1./(RAND_MAX * 0.5)

enum { ATTACK, DECAY, SUSTAIN, RELEASE, DONE };

/****TYPEDEFS****/

//ADSR
typedef struct _ADSR {
	float value;
	float target;
	float rate;
	int state;
	float attackRate;
	float decayRate;
	float sustainLevel;
	float releaseRate;
} ADSR;

//OneZero
typedef struct _onezero {
	float zeroCoeff, gain, sgain, input, lastOutput;
} OneZero;

//OnePole
typedef struct _onepole {
	float poleCoeff, gain, sgain, output, lastOutput;
} OnePole;

//DCBlock
typedef struct _dcblock {
	float output, input, lastOutput;
} DCBlock;
  
//biQuad
typedef struct _biquad {
    float poleCoeffs[2];
    float zeroCoeffs[2];
    float inputs[2];
    float lastOutput;
    float gain;
} BiQuad;

//Bow Table
typedef struct _bowtabl {
    float offSet;
    float slope;
    float lastOutput;
} BowTabl;


//Reed Table
typedef struct _reedTable {
    float offSet;
    float slope;
    float lastOutput;
} ReedTabl;

//Lip Filter
typedef struct _lipfilt {
	float coeffs[2];
	BiQuad filter;
	float lastOutput;
} LipFilt;

//DLineA: delay line with allpass interpolation
typedef struct _dlineA {
	double *inputs; 	//delay line buffer
	long inPoint;	//where to dump in the buffer
    long outPoint;	//where to grab from the buffer
    long length;	//delay line length	
    double alpha;
    double coeff;
    double lastIn;
    double lastOutput;
} DLineA;

//DLineL: delay line with allpass interpolation
typedef struct _dlineL {
	float *inputs; 	//delay line buffer
	long inPoint;	//where to dump in the buffer
    long outPoint;	//where to grab from the buffer
    long length;	//delay line length	
    float alpha, omAlpha;
    float coeff;
    float lastIn;
    float lastOutput;
} DLineL;

//DLineN: non-interpolating, fixed length delay line
typedef struct _dlineN {
	float *inputs;
  	long inPoint;
  	long outPoint;
  	long length;
   	float lastOutput;
} DLineN;

//RawWvIn
typedef struct _rawwWvIn {
	long length;
    int channels;
    int looping;
    int finished;
    int interpolate;
    float *data;
    float time;
    float rate;
    float phaseOffset;
    float lastOutput;
} RawWvIn;


//HeaderSnd
typedef struct _headerSnd {
	long length;
    int channels;
    int looping;
    int finished;
    int interpolate;
    float *data;
    float time;
    float rate;
    float phaseOffset;
    float lastOutput;
} HeaderSnd;

//Envelope
typedef struct _envelope {
  	float value;
  	float target;
  	float rate;
  	int state;
} Envelope;

//Modal 4
typedef struct _modal4 {  
    Envelope envelope; 
    HeaderSnd  wave;
    BiQuad   filters[4];
    OnePole  onepole;
    HeaderSnd  vibr;
    float srate;
    float lastOutput;
    float vibrGain;
    float masterGain;
    float directGain;
    float stickHardness;
    float strikePosition;
    float baseFreq;
    float ratios[4];
    float resons[4];
} Modal4;

/***PROTOTYPES***/

//ADSR
void ADSR_init(ADSR *adsr);
void ADSR_keyOn(ADSR *adsr);
void ADSR_keyOff(ADSR *adsr);
void ADSR_setAttackRate(ADSR *adsr, float aRate);
void ADSR_setDecayRate(ADSR *adsr, float aRate);
void ADSR_setSustainLevel(ADSR *adsr, float aLevel);
void ADSR_setReleaseRate(ADSR *adsr, float aRate);
void ADSR_setAttackTime(ADSR *adsr, float aTime, float srate);
void ADSR_setDecayTime(ADSR *adsr, float aTime, float srate);
void ADSR_setReleaseTime(ADSR *adsr, float aTime, float srate);
void ADSR_setAllTimes(ADSR *adsr, float aTime, float dTime, float sLevel, float rTime, float srate);
void ADSR_setTarget(ADSR *adsr, float aTarget);
void ADSR_setValue(ADSR *adsr, float aValue);
int ADSR_getState(ADSR *adsr);
float ADSR_tick(ADSR *adsr);
float ADSR_ADRtick(ADSR *adsr);

//Bow Table
void BowTabl_init(BowTabl *bowtable);
float BowTabl_lookup(BowTabl *bowtable, float sample);	/*  Perform Table Lookup    */

//Reed Table
void ReedTabl_init(ReedTabl *reedtable);
float ReedTabl_lookup(ReedTabl *reedtable, float deltaP);

//Lip Filter
void LipFilt_init(LipFilt *lipfilt);
void LipFilt_clear(LipFilt *lipfilt);
void LipFilt_setFreq(LipFilt *lipfilt, float frequency, float srate);
float LipFilt_tick(LipFilt *lipfilt, float mouthSample, float boreSample);

//Jet "Table"
float JetTabl_lookup(float sample);

//Noise
float Noise_tick();

//OneZero
void OneZero_init(OneZero *onezero);
void OneZero_setGain(OneZero *onezero, float aValue);
void OneZero_setCoeff(OneZero *onezero, float aValue);
float OneZero_tick(OneZero *onezero, float sample); // Perform Filter Operation

//OnePole
void OnePole_init(OnePole *onepole);
void OnePole_setPole(OnePole *onepole, float aValue);
void OnePole_setGain(OnePole *onepole, float aValue);
float OnePole_tick(OnePole *onepole, float sample);  // Perform Filter Operation
void OnePole_clear(OnePole *onepole);

//DCBlock functions
float DCBlock_tick(DCBlock *dcblock, float sample);
void DCBlock_clear(DCBlock *dcblock);

//BiQuad functions
void BiQuad_init(BiQuad *biquad);
void BiQuad_clear(BiQuad *biquad);
void BiQuad_setPoleCoeffs(BiQuad *biquad, float *coeffs);
void BiQuad_setZeroCoeffs(BiQuad *biquad, float *coeffs);
void BiQuad_setGain(BiQuad *biquad, float aValue);
void BiQuad_setFreqAndReson(BiQuad *biquad, float freq, float reson, float srate);
void BiQuad_setEqualGainZeroes(BiQuad *biquad);
float BiQuad_tick(BiQuad *biquad, float sample);

//DlineA functions
void DLineA_alloc(DLineA *delayLine, long max_length);
void DLineA_free(DLineA *delayLine);
void DLineA_clear(DLineA *delayLine);
void DLineA_setDelay(DLineA *delayLine, double lag);
float DLineA_tick(DLineA *delayLine, double sample); 

//DlineL functions
void DLineL_alloc(DLineL *delayLine, long max_length);
void DLineL_free(DLineL *delayLine);
void DLineL_clear(DLineL *delayLine);
void DLineL_setDelay(DLineL *delayLine, float lag);
float DLineL_tick(DLineL *delayLine, float sample); 

//DLine N functions
void DLineN_alloc(DLineN *delayLine, long max_length);
void DLineN_free(DLineN *delayLine);
void DLineN_clear(DLineN *delayLine);
void DLineN_setDelay(DLineN *delayLine, float lag);
float DLineN_tick(DLineN *delayLine, float sample);  

//RawWvIn functions
void RawWvIn_alloc(RawWvIn *inwave, char *fileName, char *mode); 
void RawWvIn_free(RawWvIn *inwave);
void RawWvIn_normalize(RawWvIn *inwave, float newPeak);
void RawWvIn_setRate(RawWvIn *inwave, float aRate);
void RawWvIn_reset(RawWvIn *inwave);
int RawWvIn_informTick(RawWvIn *inwave);
float RawWvIn_tick(RawWvIn *inwave);
void RawWvIn_setFreq(RawWvIn *inwave, float aFreq, float srate);

//HeaderSnd functions
void HeaderSnd_alloc(HeaderSnd *inwave, float *sndarray, long arraylen, char *mode); 
void HeaderSnd_free(HeaderSnd *inwave);
void HeaderSnd_normalize(HeaderSnd *inwave, float newPeak);
void HeaderSnd_setRate(HeaderSnd *inwave, float aRate);
void HeaderSnd_reset(HeaderSnd *inwave);
int HeaderSnd_informTick(HeaderSnd *inwave);
float HeaderSnd_tick(HeaderSnd *inwave);
void HeaderSnd_setFreq(HeaderSnd *inwave, float aFreq, float srate);


//Envelope functions
void Envelope_init(Envelope *env);
void Envelope_keyOn(Envelope *env);
void Envelope_keyOff(Envelope *env);
void Envelope_setRate(Envelope *env, float aRate);
void Envelope_setTime(Envelope *env, float aTime, int srate);
void Envelope_setTarget(Envelope *env, float aTarget);
void Envelope_setValue(Envelope *env, float aValue);
float Envelope_tick(Envelope *env);
int Envelope_informTick(Envelope *env);
float Envelope_lastOut(Envelope *env);

//Modal4 
void Modal4_init(Modal4 *modal, float srate);
void Modal4_clear(Modal4 *modal);
void Modal4_setFreq(Modal4 *modal, float frequency);
void Modal4_setRatioAndReson(Modal4 *modal, int whichOne, float ratio, float reson);
void Modal4_setMasterGain(Modal4 *modal, float aGain);
void Modal4_setDirectGain(Modal4 *modal, float aGain);
void Modal4_setFiltGain(Modal4 *modal, int whichOne, float gain);
void Modal4_strike(Modal4 *modal, float amplitude);
void Modal4_noteOn(Modal4 *modal, float freq, float amp);
void Modal4_noteOff(Modal4 *modal, float amp) 	;	/*  This calls damp, but inverts the    */
void Modal4_damp(Modal4 *modal, float amplitude);
float Modal4_tick(Modal4 *modal);

//non-linear interpolation algorithms
float polyinterpolate(float ya[], int n, long vsize, float x);
double polyinterpolate_d(double yinput[], int n, long vsize, float x);
