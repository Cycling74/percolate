/************************************************/ 
/* PeRColate, v.0.9 beta						*/
/*												*/
/* Port of many of the functions from the       */
/* Synthesis Toolkit (STK), originally by		*/
/* Perry Cook and Gary Scavone.					*/
/*												*/
/* Ported to MSP by Dan Trueman					*/
/*												*/
/* The STK is in C++, so most of this port		*/
/* simply involved translating the classes		*/
/* into typedefs with associated function 		*/
/* calls. In addition, most control scaling		*/
/* is left to the user in MAX, so 	 			*/
/* applications of ADSRs and Envelopes are		*/
/* irrelevant (though not all of the time).		*/
/*												*/
/* I have left most of the original commentary	*/
/* in, and some of it reflects the C++			*/
/* heritage (!) of the code. Some functions		*/
/* that are not relevant for MSP may be			*/
/* mentioned, which should be ignored			*/
/*
/* Also, I prefer having all the functions 		*/
/* in a single file--call me an idiot if		*/
/* you like--but, in a future version, we may	*/
/* consider modularizing it, if it seems like   */
/* I might look less like an idiot in doing so. */
/*												*/
/* DLT, 2/2000									*/
/*												*/
/************************************************/

#include "stk_c.h"
#include "sinewave.h"
#include <fcntl.h>
#include <unix.h>
#include <rand.c>

/***************************************************/
/*! \class ADSR
    \brief STK ADSR envelope class.

    This Envelope subclass implements a
    traditional ADSR (Attack, Decay,
    Sustain, Release) envelope.  It
    responds to simple keyOn and keyOff
    messages, keeping track of its state.
    The \e state = ADSR::DONE after the
    envelope value reaches 0.0 in the
    ADSR::RELEASE state.

    by Perry R. Cook and Gary P. Scavone, 1995 - 2002.
    hacked for PeRColate by dan trueman.
*/
/***************************************************/


void ADSR_init(ADSR *adsr)
{
  adsr->target = (float) 0.0;
  adsr->value = (float) 0.0;
  adsr->attackRate = (float) 0.001;
  adsr->decayRate = (float) 0.001;
  adsr->sustainLevel = (float) 0.5;
  adsr->releaseRate = (float) 0.01;
  adsr->state = ATTACK;
}

void ADSR_keyOn(ADSR *adsr)
{
  adsr->target = (float) 1.0;
  adsr->rate = adsr->attackRate;
  adsr->state = ATTACK;
}

void ADSR_keyOff(ADSR *adsr)
{
  adsr->target = (float) 0.0;
  adsr->rate = adsr->releaseRate;
  adsr->state = RELEASE;
}

void ADSR_setAttackRate(ADSR *adsr, float aRate)
{
  if (aRate < 0.0) {
    //printf("ADSR: negative rates not allowed ... correcting!\n");
    adsr->attackRate = -aRate;
  }
  else adsr->attackRate = aRate;
}

void ADSR_setDecayRate(ADSR *adsr, float aRate)
{
  if (aRate < 0.0) {
    //printf("ADSR: negative rates not allowed ... correcting!\n");
    adsr->decayRate = -aRate;
  }
  else adsr->decayRate = aRate;
}

void ADSR_setSustainLevel(ADSR *adsr, float aLevel)
{
  if (aLevel < 0.0 ) {
    //printf("ADSR: sustain level out of range ... correcting!\n");
    adsr->sustainLevel = (float)  0.0;
  }
  else adsr->sustainLevel = aLevel;
}

void ADSR_setReleaseRate(ADSR *adsr, float aRate)
{
  if (aRate < 0.0) {
    //printf("ADSR: negative rates not allowed ... correcting!\n");
    adsr->releaseRate = -aRate;
  }
  else adsr->releaseRate = aRate;
}

void ADSR_setAttackTime(ADSR *adsr, float aTime, float srate)
{
  if (aTime < 0.0) {
    //printf("ADSR: negative rates not allowed ... correcting!\n");
    adsr->attackRate = 1.0 / ( -aTime * srate );
  }
  else adsr->attackRate = 1.0 / ( aTime * srate );
}

void ADSR_setDecayTime(ADSR *adsr, float aTime, float srate)
{
  if (aTime < 0.0) {
    //printf("ADSR: negative times not allowed ... correcting!\n");
    adsr->decayRate = 1.0 / ( -aTime * srate );
  }
  else adsr->decayRate = 1.0 / ( aTime * srate );
}

void ADSR_setReleaseTime(ADSR *adsr, float aTime, float srate)
{
  if (aTime < 0.0) {
    //printf("ADSR: negative times not allowed ... correcting!\n");
    adsr->releaseRate = 1.0 / ( -aTime * srate );
  }
  else adsr->releaseRate = 1.0 / ( aTime * srate );
}

void ADSR_setAllTimes(ADSR *adsr, float aTime, float dTime, float sLevel, float rTime, float srate)
{
  ADSR_setAttackTime(adsr, aTime, srate);
  ADSR_setDecayTime(adsr, dTime, srate);
  ADSR_setSustainLevel(adsr, sLevel);
  ADSR_setReleaseTime(adsr, rTime, srate);
}

void ADSR_setTarget(ADSR *adsr, float aTarget)
{
  adsr->target = aTarget;
  if (adsr->value < adsr->target) {
    adsr->state = ATTACK;
    ADSR_setSustainLevel(adsr, adsr->target);
    adsr->rate = adsr->attackRate;
  }
  if (adsr->value > adsr->target) {
    ADSR_setSustainLevel(adsr, adsr->target);
    adsr->state = DECAY;
    adsr->rate = adsr->decayRate;
  }
}

void ADSR_setValue(ADSR *adsr, float aValue)
{
  adsr->state = SUSTAIN;
  adsr->target = aValue;
  adsr->value = aValue;
  ADSR_setSustainLevel(adsr, aValue);
  adsr->rate = (float)  0.0;
}

int ADSR_getState(ADSR *adsr)
{
  return adsr->state;
}

float ADSR_tick(ADSR *adsr)
{
  switch (adsr->state) {

  case ATTACK:
    adsr->value += adsr->rate;
    if (adsr->value >= adsr->target) {
      adsr->value = adsr->target;
      adsr->rate = adsr->decayRate;
      adsr->target = adsr->sustainLevel;
	  adsr->state = DECAY;
    }
    break;

  case DECAY:
    adsr->value -= adsr->decayRate;
    if (adsr->value <= adsr->sustainLevel) {
      adsr->value = adsr->sustainLevel;
      adsr->rate = (float) 0.0;
      adsr->state = SUSTAIN;
    }
    break;

  case RELEASE:
    adsr->value -= adsr->releaseRate;
    if (adsr->value <= 0.0)       {
      adsr->value = (float) 0.0;
      adsr->state = DONE;
    }
  }

  return adsr->value;
}

//just like ADSR_tick, but skips SUSTAIN state
float ADSR_ADRtick(ADSR *adsr)
{
  switch (adsr->state) {

  case ATTACK:
    adsr->value += adsr->rate;
    if (adsr->value >= adsr->target) {
      adsr->value = adsr->target;
      adsr->rate = adsr->decayRate;
      adsr->target = adsr->sustainLevel;
	  adsr->state = DECAY;
    }
    break;

  case DECAY:
    adsr->value -= adsr->decayRate;
    if (adsr->value <= adsr->sustainLevel) {
      adsr->value = adsr->sustainLevel;
      adsr->rate = (float) 0.0;
      adsr->target = (float) 0.0;
      adsr->state = RELEASE;
    }
    break;

  case RELEASE:
    adsr->value -= adsr->releaseRate;
    if (adsr->value <= 0.0)       {
      adsr->value = (float) 0.0;
      adsr->state = DONE;
    }
  }

  return adsr->value;
}

/***********************************************/ 
/*  Simple Bow Table Object, after Smith       */
/*    by Perry R. Cook, 1995-96                */
/***********************************************/
void BowTabl_init(BowTabl *bowtable)
{
    bowtable->offSet =  0.0;    /*  offset is a bias, really not needed unless   */
		     					/*  friction is different in each direction      */
    bowtable->slope =  0.1;     /*  controls width of friction pulse,            */
		     					/*         related to bowForce                   */
}

float BowTabl_lookup(BowTabl *bowtable, float sample) 	/*  Perform Table Lookup    */
{                                           			/*  sample is differential  */				    								/*  string vs. bow velocity */
    float input;
    input = sample + bowtable->offSet;                				/*  add bias to sample      */
    input *= bowtable->slope;                         				/*  scale it                */
    bowtable->lastOutput = (float)fabs((double) input) + 0.75;   	/*  below min delta, friction = 1 */
    bowtable->lastOutput = (float)pow(bowtable->lastOutput, -4.0);
    if (bowtable->lastOutput > 1.0 ) bowtable->lastOutput = 1.0; 	/*  maximum friction is 1.0 */
    return bowtable->lastOutput;
}

/**********************************************/
/*  One break point linear reed table object  */
/*  by Perry R. Cook, 1995-96                 */
/*  Consult McIntyre, Schumacher, & Woodhouse */
/*        Smith, Hirschman, Cook, Scavone,    */
/*        more for information.               */
/**********************************************/
void ReedTabl_init(ReedTabl *reedtable) 
{
    reedtable->offSet = 0.6;    /* Offset is a bias, related to reed rest position  */
    reedtable->slope = -0.8;    /* Slope corresponds loosely to reed stiffness      */
}

float ReedTabl_lookup(ReedTabl *reedtable, float deltaP)   { 
    /*   Perform "Table Lookup" by direct clipped  */
    /*   linear function calculation               */
    /*   deltaP is differential reed pressure      */
    reedtable->lastOutput = reedtable->offSet + (reedtable->slope * deltaP); 	/* compute basic non-linearity     */
    if (reedtable->lastOutput > 1.0) reedtable->lastOutput = 1.0;     			/* if other way, reed slams shut   */
    if (reedtable->lastOutput < -1.0) reedtable->lastOutput = -1.0;   			/* if all the way open, acts like open end */
    return reedtable->lastOutput;
}


/**********************************************/
/*  Lip Filter Object by Perry R. Cook, 1995-96*/    
/*  The lip of the brass player has dynamics  */
/*  which are controlled by the mass, spring  */
/*  constant, and damping of the lip.  This   */
/*  filter simulates that behavior and the    */
/*  transmission/reflection properties as     */
/*  well.  See Cook TBone and HosePlayer      */
/*  instruments and articles.                 */
/**********************************************/
void LipFilt_init(LipFilt *lipfilt)
{
	lipfilt->coeffs[0] = 0.0;
    lipfilt->coeffs[1] = 0.0;
    BiQuad_init(&lipfilt->filter);
    BiQuad_setZeroCoeffs(&lipfilt->filter, lipfilt->coeffs);
    LipFilt_clear(lipfilt);
}

void LipFilt_clear(LipFilt *lipfilt)
{
	BiQuad_clear(&lipfilt->filter);
    lipfilt->lastOutput = 0.;
}

void LipFilt_setFreq(LipFilt *lipfilt, float frequency, float srate)
{
    float coeffs[2];
    if (srate < 22050.) srate = 22050.;
    coeffs[0] = 2.0 * 0.997 * 
		cos(TWO_PI * frequency / srate);      	/* damping should change with  */
    coeffs[1] = (-0.997 * 0.997);  				/* lip parameters, but not yet.*/
    BiQuad_setPoleCoeffs(&lipfilt->filter, coeffs);
    BiQuad_setGain(&lipfilt->filter, 0.03);                   
}

/*  NOTE:  Here we should add lip tension                 */
/*              settings based on Mass/Spring/Damping     */
/*              Maybe in TookKit97                        */

float LipFilt_tick(LipFilt *lipfilt, float mouthSample, float boreSample)    
		/*   Perform "Table Lookup" By Polynomial Calculation */
{
    float temp;
    temp = mouthSample - boreSample;          			/* Differential pressure              */
    temp = BiQuad_tick(&lipfilt->filter,temp); 			/* Force -> position                  */
    temp = temp*temp;                        		 	/* Simple position to area mapping    */
    if (temp > 1.0) temp = 1.0;    						/* Saturation at + 1.0                */
    lipfilt->lastOutput = temp * mouthSample;          	/* Assume mouth input = area          */
    lipfilt->lastOutput += (1.0 - temp) * boreSample;  	/* and Bore reflection is compliment. */
    return lipfilt->lastOutput;
}


/**********************************************/
/* Jet Table Object by Perry R. Cook, 1995-96 */
/* Consult Fletcher and Rossing, Karjalainen, */
/*       Cook, more, for information.         */
/* This, as with many other of my "tables",   */
/* is not a table, but is computed by poly-   */
/* nomial calculation.                        */
/**********************************************/
float JetTabl_lookup(float sample)
{
	float output;
	output = sample * (sample*sample - 1.);
	if (output > 1.) output = 1.;
	if (output < -1.) output = -1.;
	return output;
}

//Noise Maker
float Noise_tick() 
{
	float output;
	output = (float)rand() - 16384.;
	output *= ONE_OVER_RANDLIMIT;
	return output;
}

/*******************************************/
/*  One Pole Filter Class,                 */
/*  by Perry R. Cook, 1995-96              */ 
/*  The parameter gain is an additional    */
/*  gain parameter applied to the filter   */  
/*  on top of the normalization that takes */
/*  place automatically.  So the net max   */
/*  gain through the system equals the     */
/*  value of gain.  sgain is the combina-  */
/*  tion of gain and the normalization     */
/*  parameter, so if you set the poleCoeff */
/*  to alpha, sgain is always set to       */
/*  gain * (1.0 - fabs(alpha)).            */
/*******************************************/
void OnePole_init(OnePole *onepole) 
{
  onepole->poleCoeff 	= 0.9;
  onepole->gain 		= 1.0;
  onepole->sgain 		= 0.1;
  onepole->output 		= 0.0;
  onepole->lastOutput	= 0.;
}

void OnePole_setPole(OnePole *onepole, float aValue)
{
  onepole->poleCoeff = aValue;
  if (onepole->poleCoeff > 0.0)                   // Normalize gain to 1.0 max
    onepole->sgain = onepole->gain * (1.0 - onepole->poleCoeff);
  else
    onepole->sgain = onepole->gain * (1.0 + onepole->poleCoeff);
}

void OnePole_setGain(OnePole *onepole, float aValue)
{
  onepole->gain = aValue;
  if (onepole->poleCoeff > 0.0)        
    onepole->sgain = onepole->gain * (1.0 - onepole->poleCoeff);  // Normalize gain to 1.0 max
  else
    onepole->sgain = onepole->gain * (1.0 + onepole->poleCoeff);
}

float OnePole_tick(OnePole *onepole, float sample)  // Perform Filter Operation
{
  onepole->output = (onepole->sgain * sample) + (onepole->poleCoeff * onepole->output);              
  onepole->lastOutput = onepole->output;
  return onepole->lastOutput;
}

void OnePole_clear(OnePole *onepole)
{
  onepole->output = 0.0;
  onepole->lastOutput = 0.0;
}

/*******************************************/
/*  One Zero Filter Class,                 */
/*  by Perry R. Cook, 1995-96              */ 
/*  The parameter gain is an additional    */
/*  gain parameter applied to the filter   */  
/*  on top of the normalization that takes */
/*  place automatically.  So the net max   */
/*  gain through the system equals the     */
/*  value of gain.  sgain is the combina-  */
/*  tion of gain and the normalization     */
/*  parameter, so if you set the poleCoeff */
/*  to alpha, sgain is always set to       */
/*  gain / (1.0 - fabs(alpha)).            */
/*******************************************/
void OneZero_init(OneZero *onezero)
{
  onezero->gain = 1.0;
  onezero->zeroCoeff = 1.0;
  onezero->sgain = 0.5;
  onezero->lastOutput = 0.;
  onezero->input = 0.;
}

void OneZero_setGain(OneZero *onezero, float aValue)
{
  onezero->gain = aValue;
  if (onezero->zeroCoeff > 0.0)    // Normalize gain to 1.0 max
    onezero->sgain = onezero->gain / (1.0 + onezero->zeroCoeff);
  else
    onezero->sgain = onezero->gain / (1.0 - onezero->zeroCoeff);
}

void OneZero_setCoeff(OneZero *onezero, float aValue)
{
  onezero->zeroCoeff = aValue;
  if (onezero->zeroCoeff > 0.0)     // Normalize gain to 1.0 max
    onezero->sgain = onezero->gain / (1.0 + onezero->zeroCoeff);
  else
    onezero->sgain = onezero->gain / (1.0 - onezero->zeroCoeff);
}

float OneZero_tick(OneZero *onezero, float sample) // Perform Filter Operation
{
  float temp;
  temp = onezero->sgain * sample;
  onezero->lastOutput = (onezero->input * onezero->zeroCoeff) + temp;
  onezero->input = temp;
  return onezero->lastOutput;
}

/*******************************************/
/*  DC Blocking Filter                     */ 
/*  by Perry R. Cook, 1995-96              */ 
/*  This guy is very helpful in, uh,       */
/*  blocking DC.  Needed because a simple  */
/*  low-pass reflection filter allows DC   */
/*  to build up inside recursive           */ 
/*  structures.                            */
/*******************************************/
float DCBlock_tick(DCBlock *dcblock, float sample)    
{
  dcblock->output = sample - dcblock->input + (0.99 * dcblock->output);
  dcblock->input = sample;
  dcblock->lastOutput = dcblock->output;
  return dcblock->lastOutput;
}

void DCBlock_clear(DCBlock *dcblock) 
{
  dcblock->output = 0.;
  dcblock->lastOutput = 0.;
}

/*******************************************/
/*  BiQuad (2-pole, 2-zero) Filter Class,  */
/*  by Perry R. Cook, 1995-96              */ 
/*  See books on filters to understand     */
/*  more about how this works.  Nothing    */
/*  out of the ordinary in this version.   */
/*******************************************/
void BiQuad_init(BiQuad *biquad)
{
  biquad->zeroCoeffs[0] = 0.0;
  biquad->zeroCoeffs[1] = 0.0;
  biquad->poleCoeffs[0] = 0.0;
  biquad->poleCoeffs[1] = 0.0;
  biquad->gain = 1.0;
  BiQuad_clear(biquad);
}

void BiQuad_clear(BiQuad *biquad)
{
  biquad->inputs[0] = 0.0;
  biquad->inputs[1] = 0.0;
  biquad->lastOutput = 0.0;
}

void BiQuad_setPoleCoeffs(BiQuad *biquad, float *coeffs)
{
  biquad->poleCoeffs[0] = coeffs[0];
  biquad->poleCoeffs[1] = coeffs[1];
}

void BiQuad_setZeroCoeffs(BiQuad *biquad, float *coeffs)
{
  biquad->zeroCoeffs[0] = coeffs[0];
  biquad->zeroCoeffs[1] = coeffs[1];
}

void BiQuad_setFreqAndReson(BiQuad *biquad, float freq, float reson, float srate)
{
  if(srate <= 0) srate = 44100; 
  biquad->poleCoeffs[1] = - (reson * reson);
  biquad->poleCoeffs[0] = 2.0 * reson * cos(TWO_PI * freq / srate);
}

void BiQuad_setEqualGainZeroes(BiQuad *biquad)
{
  biquad->zeroCoeffs[1] =  -1.0;
  biquad->zeroCoeffs[0] =  0.0;
}

void BiQuad_setGain(BiQuad *biquad, float aValue)
{
  biquad->gain = aValue;
}

float BiQuad_tick(BiQuad *biquad, float sample) /*  Perform Filter Operation             */
{                                           	/*  Biquad is two pole, two zero filter  */
  float temp;                            		/*  Look it up in your favorite DSP text */

  temp = sample * biquad->gain;                      			/* Here's the math for the  */
  temp += biquad->inputs[0] * biquad->poleCoeffs[0];         	/* version which implements */
  temp += biquad->inputs[1] * biquad->poleCoeffs[1];         	/* only 2 state variables.  */
    
  biquad->lastOutput = temp;                          					/* This form takes          */
  biquad->lastOutput += (biquad->inputs[0] * biquad->zeroCoeffs[0]);  	/* 5 multiplies and         */
  biquad->lastOutput += (biquad->inputs[1] * biquad->zeroCoeffs[1]);  	/* 4 adds                   */
  biquad->inputs[1] = biquad->inputs[0];                      			/* and 3 moves              */
  biquad->inputs[0] = temp;                           					/* like the 2 state-var form*/

  return biquad->lastOutput;

}

/*******************************************/
/*  AllPass Interpolating Delay Line       */
/*  Object by Perry R. Cook 1995-96.       */
/*  Revised by Gary P. Scavone, 1999.      */
/*                                         */
/*  This one uses a delay line of maximum  */
/*  length specified on creation, and      */
/*  interpolates fractional length using   */
/*  an all-pass filter.  This version is   */
/*  more efficient for computing static    */
/*  length delay lines (alpha and coeff    */
/*  are computed only when the length      */
/*  is set, there probably is a more       */
/*  efficient computational form if alpha  */
/*  is changed often (each sample)).       */
/*                                         */
/*******************************************/
void DLineA_alloc(DLineA *delayLine, long max_length)
{
  	long i;
  	delayLine->length = max_length;
  	//delayLine->inputs = t_getbytes(delayLine->length * sizeof(double));
  	delayLine->inputs = (double *)sysmem_newptr(delayLine->length * sizeof(double));
  	if (!delayLine->inputs) {
		error("DlineA: out of memory");
		return;
  	}
	DLineA_clear(delayLine);
  	delayLine->inPoint = 0;
  	delayLine->outPoint = delayLine->length >> 1;
}

void DLineA_free(DLineA *delayLine)
{
	if (delayLine->inputs)
		//t_freebytes(delayLine->inputs, delayLine->length * sizeof(double));
		sysmem_freeptr(delayLine->inputs);
}

void DLineA_clear(DLineA *delayLine)
{
  	long i;
  	for (i=0;i<delayLine->length;i++) delayLine->inputs[i] = 0.;
  	delayLine->lastIn = 0.;
  	delayLine->lastOutput = 0.;
}

void DLineA_setDelay(DLineA *delayLine, double lag)  
{
  double outPointer;

  if (lag > delayLine->length-1) {        // if delay is too big,
    //post("DLineA: Delay length too big.\n");
    //post("Setting to maximum length of %ld.\n",delayLine->length-1);
    outPointer = delayLine->inPoint + 1.0;          // force delay to max_length
  }
  else if (lag < 0.1) {
    //post("DLineA: Delays < 0.1 not possible with current structure.\n");
    //post("Setting delay length to 0.1.\n");
    outPointer = delayLine->inPoint + 0.8999999999;
  }
  else
    outPointer = delayLine->inPoint - lag + 1.0;     // outPoint chases inpoint

  if (outPointer < 0)
    outPointer += delayLine->length;                 			// modulo table length
  delayLine->outPoint = (long) outPointer;           			// Integer part of delay
  delayLine->alpha = 1.0 + delayLine->outPoint - outPointer;    // fractional part of delay

  if (delayLine->alpha == 0.0) {  // exact integer delay
    delayLine->outPoint -= 1;
    if (delayLine->outPoint < 0) 
    	delayLine->outPoint += delayLine->length;
  }

  if (delayLine->alpha<0.1) {                             	// Hack to avoid pole/zero
    delayLine->outPoint += 1;                             	// cancellation.  Keeps allpass
    if (delayLine->outPoint >= delayLine->length) 
    	delayLine->outPoint -= delayLine->length;
    delayLine->alpha += 1.0;                   				// delay in range of .1 to 1.1
  }

  delayLine->coeff = (1.0 - delayLine->alpha) / 
  	(1.0 + delayLine->alpha);   							// coefficient for all pass
}

float DLineA_tick(DLineA *delayLine, double sample) // Take sample, yield sample
{
  double temp;
  delayLine->inputs[delayLine->inPoint++] = sample;            // Write input sample
  if (delayLine->inPoint == delayLine->length)                 // Increment input pointer
    delayLine->inPoint -= delayLine->length;                   // modulo length
  temp = delayLine->inputs[delayLine->outPoint++];             // filter input
  if (delayLine->outPoint == delayLine->length)                // Increment output pointer
    delayLine->outPoint -= delayLine->length;                  // modulo length
  delayLine->lastOutput = -delayLine->coeff * delayLine->lastOutput;      // delayed output
  delayLine->lastOutput += delayLine->lastIn + (delayLine->coeff * temp); // input + delayed Input
  delayLine->lastIn = temp;
  return delayLine->lastOutput;                     			// save output and return
}

/*******************************************/
/*  Linearly Interpolating Delay Line      */
/*  Object by Perry R. Cook 1995-96        */
/*  This one uses a delay line of maximum  */
/*  length specified on creation, and      */ 
/*  linearly interpolates fractional       */
/*  length.  It is designed to be more     */
/*  efficient if the delay length is not   */
/*  changed very often.                    */
/*******************************************/
void DLineL_alloc(DLineL *delayLine, long max_length)
{
	long i;
  	delayLine->length = max_length;
  	//delayLine->inputs = t_getbytes(delayLine->length * sizeof(float));
  	delayLine->inputs = (float *)sysmem_newptr(delayLine->length * sizeof(float));
  	if (!delayLine->inputs) {
		error("DlineA: out of memory");
		return;
  	}
	DLineL_clear(delayLine);
  	delayLine->inPoint = 0;
  	delayLine->outPoint = delayLine->length >> 1;
}

void DLineL_free(DLineL *delayLine)
{
	if (delayLine->inputs)
		//t_freebytes(delayLine->inputs, delayLine->length * sizeof(float));
		sysmem_freeptr(delayLine->inputs);
}

void DLineL_clear(DLineL *delayLine)
{
  	long i;
  	for (i=0;i<delayLine->length;i++) delayLine->inputs[i] = 0.;
  	delayLine->lastIn = 0.;
  	delayLine->lastOutput = 0.;
}

void DLineL_setDelay(DLineL *delayLine, float lag)
{
  float outPointer;

  if (lag > delayLine->length-1) {               			// if delay is too big,
    //post("DLineL: Delay length too big.\n");
    //post("Setting to maximum length of %ld.\n", delayLine->length-1);
    outPointer = delayLine->inPoint + 1;         			// force delay to max_length
  }
  else
    outPointer = delayLine->inPoint - lag;       			// read chases write
  while (outPointer<0)
    outPointer += delayLine->length;             			// modulo maximum length
  delayLine->outPoint = (long) outPointer;       			// integer part
  delayLine->alpha = outPointer - delayLine->outPoint;      // fractional part
  delayLine->omAlpha = 1.0 - delayLine->alpha;   			// 1.0 - fractional part (more efficient)
}

//the interpolation may need to become doubles to avoid roundoff problems...
float DLineL_tick(DLineL *delayLine, float sample)     // Take one, yield one
{
  delayLine->inputs[delayLine->inPoint++] = sample;               	 // Input next sample
  if (delayLine->inPoint == delayLine->length)                     	// Check for end condition
    delayLine->inPoint -= delayLine->length;
  delayLine->lastOutput = 
  	delayLine->inputs[delayLine->outPoint++] * delayLine->omAlpha; 	// first 1/2 of interpolation
  if (delayLine->outPoint<delayLine->length) {              		// Check for end condition
    delayLine->lastOutput += 
    	delayLine->inputs[delayLine->outPoint] * delayLine->alpha;  // second 1/2 of interpolation
  }                                          
  else        {                             						 // if at end . . .
    delayLine->lastOutput += 
    	delayLine->inputs[0] * delayLine->alpha;        			 // second 1/2 of interpolation
    delayLine->outPoint -= delayLine->length;                             
  }
  return delayLine->lastOutput;
}

/*******************************************/
/*  Non-Interpolating Delay Line           */
/*  Object by Perry R. Cook 1995-96.       */
/*  Revised by Gary Scavone, 1999.         */
/*                                         */
/*  This one uses either a delay line of   */
/*  maximum length specified on creation   */
/*  or a default length of 2048 samples.   */
/*  A non-interpolating delay line is      */
/*  typically used in non-time varying     */
/*  (reverb) applications.                 */
/*******************************************/
void DLineN_alloc(DLineN *delayLine, long max_length)
{
  // Writing before reading allows delays from 0 to length-1.
  // Thus, if we want to allow a delay of max_length, we need
  // a delay-line of length = max_length+1.
  delayLine->length = max_length+1;
  //delayLine->inputs = t_getbytes(delayLine->length * sizeof(float));
  delayLine->inputs = (float *)sysmem_newptr(delayLine->length * sizeof(float));
  if (!delayLine->inputs) {
		error("DlineN: out of memory");
		return;
  }
  DLineN_clear(delayLine);
  delayLine->inPoint = 0;
  delayLine->outPoint = delayLine->length >> 1;
}

void DLineN_free(DLineN *delayLine)
{
	if (delayLine->inputs)
		//t_freebytes(delayLine->inputs, delayLine->length * sizeof(float));
		sysmem_freeptr(delayLine->inputs);
}

void DLineN_clear(DLineN *delayLine)
{
  long i;
  for (i=0;i<delayLine->length;i++) delayLine->inputs[i] = 0.0;
  delayLine->lastOutput = 0.;
}

void DLineN_setDelay(DLineN *delayLine, float lag)
{
  if (lag > delayLine->length-1) {                   			// if delay is too big,
  	//post("DLineN: Delay length too big.\n");
    //post("Setting to maximum length of %ld.\n", delayLine->length-1);
    delayLine->outPoint = delayLine->inPoint + 1;               // force delay to max_length
  }
  else 
    delayLine->outPoint = delayLine->inPoint - (long) lag;      			// read chases write
  while (delayLine->outPoint<0) delayLine->outPoint += delayLine->length;  	// modulo maximum length
}

float DLineN_tick(DLineN *delayLine, float sample)  // Take one, yield one
{
  delayLine->inputs[delayLine->inPoint++] = sample;             			// Input next sample
  if (delayLine->inPoint == delayLine->length)                  			// Check for end condition
    delayLine->inPoint -= delayLine->length;
  delayLine->lastOutput = delayLine->inputs[delayLine->outPoint++];        	// Read out next value
  if (delayLine->outPoint>=delayLine->length)                   			// Check for end condition
    delayLine->outPoint -= delayLine->length;                             
  return delayLine->lastOutput;
}

/*******************************************/
/*  RawWvIn Input Class,                   */
/*  by Gary P. Scavone, 1999               */
/*                                         */
/*  This object inherits from WvIn and is  */
/*  used to open raw 16-bit data (signed   */
/*  integer) files for playback.           */
/*                                         */
/*  STK RawWave files are assumed to be    */
/*  monaural and big-endian.               */
/*******************************************/

//RawWvIn_alloc(x, ":externals:audio:PeRColate:rawwaves:sinewave.raw", "oneshot");
void RawWvIn_alloc(RawWvIn *inwave, char *fileName, char *mode) 
{
	long i=0;
	short temp;
	long fdlength;	
	struct stat bufinfo;
	long stattest;	
	FILE *fd;

	fd = fopen(fileName,"rb"); //need full pathname
    if (!fd)   {
		post("RawWvIn: Couldn't find soundfile %s  !!!!!!!!\n",fileName);
    }    
    stat(fileName, &bufinfo);
    fdlength = bufinfo.st_size/sizeof(short);
    inwave->length = fdlength;    
    //inwave->data = t_getbytes((fdlength+1) * sizeof(float));
    inwave->data - (float *)sysmem_newptr((fdlength+1) * sizeof(float));
	if (!inwave->data) {
		post("RawWvIn: out of memory!");
		return;
	}

	
	while (fread(&temp,2,1,fd) && (i < fdlength)) {
		inwave->data[i++] = (float)temp;
	}

	post("loaded file %s, length %ld samples", fileName, fdlength);
     
    fseek(fd,0,0);
    fclose(fd);
    
    // Setup for looping or one-shot playback
  	if (!strcmp(mode,"looping")) {
    	inwave->looping = 1;
    	inwave->data[inwave->length] = inwave->data[0];          // extra sample for interpolation
  	}
  	else if (!strcmp(mode,"oneshot")) {
    	inwave->looping = 0;
    	inwave->data[inwave->length] = inwave->data[inwave->length-1];  // extra sample for interpolation
  	}
  	else {
  		post("RawWvIn: Unsupported mode, defaulting to one-shot");
    	inwave->looping = 0;
    	inwave->data[inwave->length] = inwave->data[inwave->length-1];
  	}

  	inwave->time = 0.0;
  	inwave->phaseOffset = 0.0;
  	inwave->rate = 1.0;
  	inwave->interpolate = 0;
  	inwave->finished = 0;
  	inwave->lastOutput = 0.;
  	inwave->channels = 1; //all STK raw waves are mono.
    
    RawWvIn_normalize(inwave, 1.); //normalize
    
    return;
}

void RawWvIn_free(RawWvIn *inwave)
{
	if (inwave->data)
		//t_freebytes(inwave->data, (inwave->length + 1) * sizeof(float));
		sysmem_freeptr(inwave->data);
}


void RawWvIn_normalize(RawWvIn *inwave, float newPeak)
{
  long i;
  float max = 0.0;

  for (i=0;i<inwave->length;i++) {
    if (fabs(inwave->data[i]) > max)
      max = (float)fabs((double) inwave->data[i]);
  }
  if (max > 0.0) {
    max = 1.0 / max;
    max *= newPeak;
    for (i=0;i<=inwave->length;i++)
	    inwave->data[i] *= max;
  }
}

void RawWvIn_setRate(RawWvIn *inwave, float aRate)
{
  inwave->rate = aRate;
  if (fmod(inwave->rate, 1.0) > 0.0) inwave->interpolate = 1;
  else inwave->interpolate = 0;
}

void RawWvIn_setFreq(RawWvIn *inwave, float aFreq, float srate)
{
  inwave->rate = inwave->length * 1./srate * aFreq;
  if (fmod(inwave->rate, 1.0) > 0.0) inwave->interpolate = 1;
  else inwave->interpolate = 0;
}

void RawWvIn_reset(RawWvIn *inwave)
{
  inwave->finished = 0;
  inwave->time = 0.0;
  inwave->lastOutput = 0.0;
}

float RawWvIn_tick(RawWvIn *inwave)
{
  RawWvIn_informTick(inwave);
  return inwave->lastOutput;
}


int RawWvIn_informTick(RawWvIn *inwave)
{
  static float temp_time, alpha;
  static long temp;

  if (!inwave->finished) {

    temp_time = inwave->time;
    
    if (inwave->phaseOffset != 0.0) {
      temp_time += inwave->phaseOffset;              /*  Add phase offset        */
      if (inwave->looping) {
        while (temp_time >= inwave->length)          /*  Check for end of sound  */
          temp_time -= inwave->length;               /*  loop back to beginning  */
        while (temp_time < 0.0)             		 /*  Check for end of sound  */
          temp_time += inwave->length;               /*  loop back to beginning  */
      }
      else {
        if (temp_time >= inwave->length)             /*  Check for end of sound  */
          temp_time = inwave->length - 1.; 			 /*  stick at end            */
        else if (temp_time < 0.0)            		 /*  check for end of sound  */
          temp_time = 0.0;       					 /*  stick at beginning      */
      }
    }

    temp = (long) temp_time;                /*  Integer part of time address    */

    if (inwave->interpolate) {
      alpha = temp_time - temp;  			/*  fractional part of time address */
      //temp *= inwave->channels;			//mono for now...
      /*  Do linear interpolation  */
      inwave->lastOutput = inwave->data[temp];
      inwave->lastOutput = inwave->lastOutput + 
          (alpha*(inwave->data[temp+1] - inwave->lastOutput));
      }    
    else {
      inwave->lastOutput = inwave->data[temp];
    }

    inwave->time += inwave->rate;                   /*  Increment time               */
    if (inwave->looping)        {
      while (inwave->time >= inwave->length)        /*  Check for end of sound       */
        inwave->time -= inwave->length;             /*  loop back to beginning       */
      while (inwave->time < 0.0)            		/*  Check for end of sound       */
        inwave->time += inwave->length;             /*  loop back to beginning       */
    }
    else {                          				/*  OneShot                      */
      if (inwave->time >= inwave->length)  {        /*  Check for end of sound       */
        inwave->time = inwave->length - 1.; 		/*  stick at end                 */
        inwave->finished = 1;               		/*  Information for one-shot use */
      }
      else if (inwave->time < 0.0)          		/*  Check for end of sound       */
        inwave->time =  0.0;      					/*  stick at beginning           */
    }
  }
  return inwave->finished;
}
  
/*******************************************/
/*  Envelope Class, Perry R. Cook, 1995-96 */
/*                                         */
/*  This is the base class for envelopes.  */
/*  This one is capable of ramping state   */
/*  from where it is to a target value by  */
/*  a rate.  It also responds to simple    */
/*  KeyOn and KeyOff messages, ramping to  */         
/*  1.0 on keyon and to 0.0 on keyoff.     */
/*  There are two tick (update value)      */
/*  methods, one returns the value, and    */
/*  other returns 0 if the envelope is at  */
/*  the target value (the state bit).      */
/*******************************************/

void Envelope_init(Envelope *env)
{    
  env->target = 0.0;
  env->value = 0.0;
  env->rate = 0.001;
  env->state = 0;
}

void Envelope_keyOn(Envelope *env)
{
  env->target = 1.0;
  if (env->value != env->target) env->state = 1;
}

void Envelope_keyOff(Envelope *env)
{
  env->target = 0.0;
  if (env->value != env->target) env->state = 1;
}

void Envelope_setRate(Envelope *env, float aRate)
{
  if (aRate < 0.0) {
    //printf("negative rates not allowed!!, correcting\n");
    env->rate = -aRate;
  }
  else env->rate = aRate;
}

void Envelope_setTime(Envelope *env, float aTime, int srate)
{
  if (aTime < 0.0) {
    //printf("negative times not allowed!!, correcting\n");
    //env->rate = ONE_OVER_SRATE / -aTime ;
    env->rate = 1. / -aTime * srate;
  }
  else env->rate = 1. / aTime * srate;
}

void Envelope_setTarget(Envelope *env, float aTarget)
{
  env->target = aTarget;
  if (env->value != env->target) env->state = 1;
}

void Envelope_setValue(Envelope *env, float aValue)
{
  env->state = 0;
  env->target = aValue;
  env->value = aValue;
}

float Envelope_tick(Envelope *env)
{
  if (env->state)  {
    if (env->target > env->value)    {
      env->value += env->rate;
      if (env->value >= env->target)    {
        env->value = env->target;
        env->state = 0;
      }
    }
    else    {
      env->value -= env->rate;
      if (env->value <= env->target)    {
        env->value = env->target;
        env->state = 0;
      }
    }
  }
  return env->value;
}

int Envelope_informTick(Envelope *env)
{
  Envelope_tick(env);
  return env->state;
}

float Envelope_lastOut(Envelope *env)
{
  return env->value;
}

/*******************************************/
/*  4 Resonance Modal Synthesis Instrument */
/*  by Perry R. Cook, 1995-96              */ 
/*  This instrument contains an excitation */
/*  wavetable, an envelope, and four reso- */
/*  nances (Non-Sweeping BiQuad Filters).  */
/*******************************************/

void Modal4_init(Modal4 *modal, float srate)
{
  int i;
  char file[128];
  
  modal->srate = srate;
  Envelope_init(&modal->envelope);
  // We don't make the excitation wave here yet,
  // because we don't know what it's going to be.
  
  for(i=0;i<4;i++) {
  	BiQuad_init(&modal->filters[i]);
  }
  OnePole_init(&modal->onepole);

  // Concatenate the STK RAWWAVE_PATH to the rawwave file
  strcpy(file, RAWWAVE_PATH);
  HeaderSnd_alloc(&modal->vibr, sinewave, 2048, "looping");
  HeaderSnd_setFreq(&modal->vibr, 6., srate);
  modal->vibrGain = 0.05;
    
  modal->directGain = 0.0;
  modal->masterGain = 1.0;
  modal->baseFreq = 440.0;
  Modal4_setRatioAndReson(modal, 0, 1.00, 0.9997);    /*  Set some      */
  Modal4_setRatioAndReson(modal, 1, 1.30, 0.9997);    /*  silly         */
  Modal4_setRatioAndReson(modal, 2, 1.77, 0.9997);    /*  default       */
  Modal4_setRatioAndReson(modal, 3, 2.37, 0.9997);    /*  values here   */
  Modal4_setFiltGain(modal, 0, 0.01);
  Modal4_setFiltGain(modal, 1, 0.01);
  Modal4_setFiltGain(modal, 2, 0.01);
  Modal4_setFiltGain(modal, 3, 0.01);
  Modal4_clear(modal);
  for(i=0;i<4;i++) {
  	BiQuad_setEqualGainZeroes(&modal->filters[i]);
  }
  modal->stickHardness = 0.5;
  modal->strikePosition = 0.561;
}  

void Modal4_clear(Modal4 *modal)
{    
	int i;
    OnePole_clear(&modal->onepole);
    for(i=0;i<4;i++) {
    	BiQuad_clear(&modal->filters[i]);
    }
}

void Modal4_setFreq(Modal4 *modal, float frequency)
{    
    modal->baseFreq = frequency;
    Modal4_setRatioAndReson(modal, 0, modal->ratios[0],modal->resons[0]);    /*  Set some      */
  	Modal4_setRatioAndReson(modal, 1, modal->ratios[1],modal->resons[1]);    /*  silly         */
  	Modal4_setRatioAndReson(modal, 2, modal->ratios[2],modal->resons[2]);    /*  default       */
  	Modal4_setRatioAndReson(modal, 3, modal->ratios[3],modal->resons[3]);    /*  values here   */
}

void Modal4_setRatioAndReson(Modal4 *modal, int whichOne, float ratio, float reson)
{
    float temp;
    if (ratio*modal->baseFreq < modal->srate*0.5) {
        modal->ratios[whichOne] = ratio;
    }
    else {
        temp = ratio;
        while (temp*modal->baseFreq > modal->srate*0.5) temp *= 0.5;
        modal->ratios[whichOne] = temp;   
    }
    modal->resons[whichOne] = reson;
    if (ratio<0) 
        temp = -ratio;
    else
        temp = ratio*modal->baseFreq;
    BiQuad_setFreqAndReson(&modal->filters[whichOne], temp, reson, modal->srate);
}

void Modal4_setMasterGain(Modal4 *modal, float aGain)
{
    modal->masterGain = aGain;
}

void Modal4_setDirectGain(Modal4 *modal, float aGain)
{
    modal->directGain = aGain;
}

void Modal4_setFiltGain(Modal4 *modal, int whichOne, float gain)
{
	BiQuad_setGain(&modal->filters[whichOne], gain);
}

void Modal4_strike(Modal4 *modal, float amplitude)
{
    int i;
    float temp;
    Envelope_setRate(&modal->envelope, 1.);
	Envelope_setTarget(&modal->envelope, amplitude);
	OnePole_setPole(&modal->onepole, 1. - amplitude);
	Envelope_tick(&modal->envelope);
	HeaderSnd_reset(&modal->wave);
    for (i=0;i<4;i++)   {
        if (modal->ratios[i] < 0)
            temp = -modal->ratios[i];
        else
            temp = modal->ratios[i] * modal->baseFreq;
        BiQuad_setFreqAndReson(&modal->filters[i], temp, modal->resons[i], modal->srate);
    }
}

void Modal4_noteOn(Modal4 *modal, float freq, float amp)
{
    Modal4_strike(modal, amp);
    Modal4_setFreq(modal, freq);    
}

void Modal4_noteOff(Modal4 *modal, float amp) 		/*  This calls damp, but inverts the    */
{                                    				/*  meaning of amplitude.               */
    Modal4_damp(modal, 1.0 - (amp *  0.03));  		/*  (high amplitude means fast damping) */
    Envelope_setTarget(&modal->envelope, 0.);
}

void Modal4_damp(Modal4 *modal, float amplitude)
{
    int i;
    float temp;
    for (i=0;i<4;i++)   {
        if (modal->ratios[i] < 0)
            temp = -modal->ratios[i];
        else
            temp = modal->ratios[i] * modal->baseFreq;
        BiQuad_setFreqAndReson(&modal->filters[i], temp, modal->resons[i]*amplitude, modal->srate);
    }
}

float Modal4_tick(Modal4 *modal)
{
    float temp,temp2;
    HeaderSnd_informTick(&modal->wave);
    temp   = modal->masterGain  * 	OnePole_tick(&modal->onepole, 
    								Envelope_tick(&modal->envelope) *
    								modal->wave.lastOutput);
    temp2 = BiQuad_tick(&modal->filters[0], temp);
	temp2 += BiQuad_tick(&modal->filters[1], temp);
	temp2 += BiQuad_tick(&modal->filters[2], temp);
	temp2 += BiQuad_tick(&modal->filters[3], temp);
    temp2  = temp2 - (temp2 * modal->directGain);
    temp2 += modal->directGain * temp;

    if (modal->vibrGain != 0.0)	{
        temp =  1.0 + HeaderSnd_tick(&modal->vibr) * modal->vibrGain;    	/*  Calculate AM             */
        temp2 = temp * temp2;              								/*  and apply to master out */
    }
    
    modal->lastOutput = temp2 * 2.0;
    return modal->lastOutput;
}
 
/*******************************************/
/*  HeaderSnd Input Class,                 */
/*  by Gary P. Scavone, 1999               */
/*                                         */
/*  This object is silly, really silly     */
/*  used manipulate short files that are   */
/*  included as header files. just         */
/*	like RawWvIn. Used for impulse	       */ 
/*  responses							   */
/*                                         */
/*  STK RawWave files are assumed to be    */
/*  monaural and big-endian.               */
/*******************************************/

//HeaderSnd_alloc(x, arrayname, arraylen, "oneshot");
void HeaderSnd_alloc(HeaderSnd *inwave, float *sndarray, long arraylen, char *mode) 
{
	long i;
	
    inwave->length = arraylen - 1;

	inwave->data = t_getbytes((arraylen) * sizeof(float));
	if (!inwave->data) {
		post("HeaderSnd: out of memory!");
		return;
	}
	
	for (i=0;i<inwave->length;i++){
		inwave->data[i] = sndarray[i];
	}
	//post("impulse length = %ld", inwave->length);

    // Setup for looping or one-shot playback
  	if (!strcmp(mode,"looping")) {
    	inwave->looping = 1;
    	inwave->data[inwave->length] = inwave->data[0];          // extra sample for interpolation
  	}
  	else if (!strcmp(mode,"oneshot")) {
    	inwave->looping = 0;
    	inwave->data[inwave->length] = inwave->data[inwave->length-1];  // extra sample for interpolation
  	}
  	else {
  		post("HeaderSnd: Unsupported mode, defaulting to one-shot");
    	inwave->looping = 0;
    	inwave->data[inwave->length] = inwave->data[inwave->length-1];
  	}

  	inwave->time = 0.0;
  	inwave->phaseOffset = 0.0;
  	inwave->rate = 1.0;
  	inwave->interpolate = 0;
  	inwave->finished = 0;
  	inwave->lastOutput = 0.;
  	inwave->channels = 1; //all STK raw waves are mono.
    
    HeaderSnd_normalize(inwave, 1.); //normalize
    
    return;
}

void HeaderSnd_free(HeaderSnd *inwave)
{
	if (inwave->data)
		t_freebytes(inwave->data, (inwave->length+1) * sizeof(float));
}


void HeaderSnd_normalize(HeaderSnd *inwave, float newPeak)
{
  long i;
  double max = 0.0;
  double temp;

  for (i=0;i<inwave->length;i++) {
    if (fabs(inwave->data[i]) > max)
      max = fabs((double) inwave->data[i]);
  }
  if (max > 0.0) {
    max = 1.0 / max;
    max *= (double)newPeak;
    for (i=0;i<=inwave->length;i++) {
    	temp = (double)inwave->data[i] * max;
	    inwave->data[i] = (float)temp;
  	}
  }	
}

void HeaderSnd_setRate(HeaderSnd *inwave, float aRate)
{
  inwave->rate = aRate;
  if (fmod(inwave->rate, 1.0) > 0.0) inwave->interpolate = 1;
  else inwave->interpolate = 0;
}

void HeaderSnd_setFreq(HeaderSnd *inwave, float aFreq, float srate)
{
  inwave->rate = inwave->length * 1./srate * aFreq;
  if (fmod(inwave->rate, 1.0) > 0.0) inwave->interpolate = 1;
  else inwave->interpolate = 0;
}

void HeaderSnd_reset(HeaderSnd *inwave)
{
  inwave->finished = 0;
  inwave->time = 0.0;
  inwave->lastOutput = 0.0;
}

float HeaderSnd_tick(HeaderSnd *inwave)
{
  HeaderSnd_informTick(inwave);
  return inwave->lastOutput;
}


int HeaderSnd_informTick(HeaderSnd *inwave)
{
  static float temp_time, alpha;
  static long temp;

  if (!inwave->finished) {

    temp_time = inwave->time;
    
    if (inwave->phaseOffset != 0.0) {
      temp_time += inwave->phaseOffset;             
      if (inwave->looping) {
        while (temp_time >= inwave->length)          
          temp_time -= inwave->length;               
        while (temp_time < 0.0)             		 
          temp_time += inwave->length;               
      }
      else {
        if (temp_time >= inwave->length)             
          temp_time = inwave->length - 1.; 			 
        else if (temp_time < 0.0)            		 
          temp_time = 0.0;       					 
      }
    }

    temp = (long) temp_time;               

    if (inwave->interpolate) {
      alpha = temp_time - temp;  			
      inwave->lastOutput = inwave->data[temp];
      inwave->lastOutput = inwave->lastOutput + 
          (alpha*(inwave->data[temp+1] - inwave->lastOutput));
      }    
    else {
      inwave->lastOutput = inwave->data[temp];
    }
	
    inwave->time += inwave->rate;                   
    if (inwave->looping)        {
      while (inwave->time >= inwave->length)        /*  Check for end of sound       */
        inwave->time -= inwave->length;             /*  loop back to beginning       */
      while (inwave->time < 0.0)            		/*  Check for end of sound       */
        inwave->time += inwave->length;             /*  loop back to beginning       */
    }
    else {                          				/*  OneShot                      */
      if (inwave->time >= inwave->length)  {        /*  Check for end of sound       */
        //inwave->time = inwave->length; 			/*  stick at end                 */
        inwave->finished = 1;               		/*  Information for one-shot use */
      }
      else if (inwave->time < 0.0)          		/*  Check for end of sound       */
        inwave->time =  0.0;      					/*  stick at beginning           */
    }
  }
  return inwave->finished;
}
  
#define MAXORDER 5 //max order + 1
// polynomial interpolation for vector values (used with FFT bins, mostly)
// hacked in from The Joy of Numerical Recipes....
//
// ya[] 	= input vector (of fft bins)
// n 		= number of points to weigh in (n-1 = order)
// vsize 	= vector size
// x		= desired point within vector
float polyinterpolate(float yinput[], int n, long vsize, float x)
{
	int i, m, ns=2;
	long closest;
	float den, dif, dift, ho, hp, w, output;
	float c[MAXORDER], d[MAXORDER], ya[MAXORDER]; //arbitrary max to order of polynomial
	long xa[MAXORDER];
	if (n>MAXORDER-1) n == MAXORDER-1;
	
	if (x>vsize) return 0.;
	
	x += 0.5;
	closest = (long)(x); //find closest x 
	if (closest >= vsize) closest = vsize - 1;
	
	//initialize values in neighborhood around closest
	for (i=1;i<=n;i++) {
		xa[i] = m = closest - 2 + i; //this is bogus: offsetting so closest is always second in arrays.
		if(m >= 0 && m < vsize) 
			c[i] = d[i] = ya[i] = yinput[m];
		else { //wrap around vector size
			while (m < 0) m += vsize;
			while (m > vsize) m -= vsize;
			//c[i] = d[i] = ya[i] = 0.;
			c[i] = d[i] = ya[i] = yinput[m];
		}
	}
		
	output = ya[ns--];
	for (m=1;m<n;m++) {
		for (i=1;i<=n-m;i++) {
			ho = (float)xa[i] - x;
			hp = (float)xa[i+m] - x;
			w  = c[i+1] - d[i];
			den = ho - hp; //shouldn't have to check for zeros here....
			den = w/den;
			d[i] = hp*den;
			c[i] = ho*den;
		}
		output += (2*ns < (n-m) ? c[ns+1] : d[ns--]);
	}
	return output;
}