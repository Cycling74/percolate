/********************************************/
/*  A granular sampling instrument      	*/
/*											*/
/*	yet another PeRColate hack				*/
/*  										*/
/*  by dan trueman ('97 and on....	)		*/
/*											*/
/* 	ok, this is some butt-ugly code, what	*/
/*  can i say. always a work in progress	*/
/*											*/
/********************************************/
//
// updated for Max 7 by Darwin Grosse and Tim Place
// -------------------------------------------------

#include "stk_c.h"
#include "buffer.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ONE_OVER_MAXRAND 1./RAND_MAX
#define ONE_OVER_HALFRAND 2./RAND_MAX
//#define ONE_OVER_HALFRAND 0.00006103516 	// constant = 1. / 16384.0
//#define ONE_OVER_MAXRAND 0.000030517578 	// 1 / 32768
#define NUMVOICES 100						//max number of voices
#define MINSPEED .001 						//minimum speed through buffer on playback
#define ENVSIZE 32
#define ONE_OVER_ENVSIZE .0078125
#define MINSIZE 64							// twice ENVSIZE. minimum grainsize in samples
#define RAND01 (float)rand() * ONE_OVER_MAXRAND //random numbers 0-1
#define RAND11 ((float)rand() - RAND_MAX * 0.5) * ONE_OVER_HALFRAND //random numbers -1 to 1
#define WINLENGTH 1024
#define PITCHTABLESIZE 1000 					//max number of transpositions for the "scale" message
#define RECORDRAMP 1000
#define RECORDRAMP_INV 0.001
#define MAXCHANNELS 16



/****MAIN STRUCT****/

t_class *munger_class;

typedef struct _munger
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars
    float grate;			//grain rate	
    float grate_var;		//grain rate variation; percentage of grain rate
    float glen; 			//grain length
    float glen_var; 		
    float gpitch; 		 
    float gpitch_var;
    float gpan_spread;		//how much to spread the grains around center
				
	float pitchTable[PITCHTABLESIZE]; 	//table of pitch values to draw from
	float twelfth; //1/12
	float semitone;
	short smoothPitch;
	int scale_len;
	
	float gain, randgain;
	float position; //playback position (0-1) (if ==-1, then random, which is default)
	
	float buflen;
	float maxsize, minsize;
	float twothirdBufsize, onethirdBufsize;
	float initbuflen;
	long maxvoices;

    //signals connected? or controls...
    short grate_connected;
    short grate_var_connected;
    short glen_connected;
    short glen_var_connected;
    short gpitch_connected;
    short gpitch_var_connected;
    short gpan_spread_connected;
    
    //window stuff
    short doHanning;
    float winTime[NUMVOICES], winRate[NUMVOICES];
    float winTable[WINLENGTH];
    float rampLength; //for simple linear ramp
    
    //voice parameters
    long gvoiceSize[NUMVOICES];			//sample size
    double gvoiceSpeed[NUMVOICES];		//1 = at pitch
    double gvoiceCurrent[NUMVOICES];	//current sample position
    int gvoiceDirection[NUMVOICES];		//1 = forward, -1 backwards
    int gvoiceOn[NUMVOICES];			//currently playing? boolean
    long gvoiceDone[NUMVOICES];			//how many samples already played from grain
    float gvoiceLPan[NUMVOICES];
    float gvoiceRPan[NUMVOICES];
    float gvoiceRamp[NUMVOICES];
    float gvoiceOneOverRamp[NUMVOICES];
    float gvoiceGain[NUMVOICES];
    ADSR gvoiceADSR[NUMVOICES];
    int gvoiceADSRon[NUMVOICES]; 		//set this to 1 if ADSR is desired instead of symmetrical ramp envelope
    float gvoiceSpat[NUMVOICES][MAXCHANNELS];
    int voices;
    float gimme;
    float channelGain[MAXCHANNELS];
    float channelGainSpread[MAXCHANNELS];
    
    //sample buffer
    float *recordBuf;
    int recordOn; 		//boolean
    int recordRampVal; 	//ramp for when toggling record on and off
    int rec_ramping; 	//-1 when ramping down, 1 when ramping up, 0 when not ramping. who's a ramp?
    long recordCurrent;
    
    //other stuff
    long time; 
    int power;
    short ambi;
    int num_channels;
    
    //external record buffer vars
    //t_symbol *l_sym;
    t_buffer_ref *l_buffer;
    long l_chan;
    short externalBuffer;
    
    //note and oneshot stuff
    short oneshot;
    int newnote;
    float noteTransp[NUMVOICES], noteSize[NUMVOICES], notePan[NUMVOICES], noteGain[NUMVOICES];
    float noteAttack[NUMVOICES], noteDecay[NUMVOICES], noteSustain[NUMVOICES], noteRelease[NUMVOICES];
    int noteDirection[NUMVOICES];

    float srate, one_over_srate;
    float srate_ms, one_over_srate_ms;
} t_munger;

 t_symbol *ps_buffer;


/****PROTOTYPES****/

//setup funcs
//void *munger_new(double val);
void *munger_new(double maxdelay, long channels);
void munger_free(t_munger *x);
t_max_err munger_notify(t_munger *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void munger_assist(t_munger *x, void *b, long m, long a, char *s);

void munger_float(t_munger *x, double f);

// dsp stuff
void munger_dsp64(t_munger *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void munger_perform64(t_munger *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void munger_alloc(t_munger *x);
void setpower(t_munger *x, t_symbol *s, long argc, t_atom *argv);

//sample buffer funcs
void recordSamp(t_munger *x, float sample);		//stick a sample in the buffer
float getSamp(t_munger *x, double where); 		//get sample, using linear interpolation

//grain funcs
int findVoice(t_munger *x);						//tries to find an available voice
float newSetup(t_munger *x, int whichVoice, double frames);	//creates a new start position for a new grain
float newSize(t_munger *x, int whichVoice);		//creates a size for a new grain
int newDirection(t_munger *x);
float envelope(t_munger *x, int whichone, float sample);

//note funcs
float newNote(t_munger *x, int whichVoice, int newNote, double frames);			//creates a new start position for a new note (oneshot grain)
float newNoteSize(t_munger *x, int whichVoice, int newNote);		//creates a size for a new note

//window funcs
float win_tick(t_munger *x, int whichone);
void munger_setramp(t_munger *x, t_symbol *s, long argc, t_atom *argv);
void munger_sethanning(t_munger *x, t_symbol *s, long argc, t_atom *argv);

//scale funcs
void munger_scale(t_munger *x, t_symbol *s, long argc, t_atom *argv);
void munger_tempered(t_munger *x, t_symbol *s, long argc, t_atom *argv);
void munger_smooth(t_munger *x, t_symbol *s, long argc, t_atom *argv);

//multichannel func
void munger_spat(t_munger *x, t_symbol *s, long argc, t_atom *argv);

//note funcs
void munger_note(t_munger *x, t_symbol *s, long argc, t_atom *argv);
void munger_oneshot(t_munger *x, t_symbol *s, long argc, t_atom *argv);

//buffersize change
void munger_bufsize(t_munger *x, t_symbol *s, long argc, t_atom *argv);

//buffersize change (ms)
void munger_bufsize_ms(t_munger *x, t_symbol *s, long argc, t_atom *argv);

//set maximum number of voices possible
void munger_maxvoices(t_munger *x, t_symbol *s, long argc, t_atom *argv);

//set number of voices to actually use
void munger_setvoices(t_munger *x, t_symbol *s, long argc, t_atom *argv);

//set min grain size
void munger_setminsize(t_munger *x, t_symbol *s, long argc, t_atom *argv);

//turn on/off backwards grains 
void munger_ambidirectional(t_munger *x, t_symbol *s, long argc, t_atom *argv);

//turn on/off recording
void munger_record(t_munger *x, t_symbol *s, long argc, t_atom *argv);

//clear buffer
void munger_clear(t_munger *x, t_symbol *s, long argc, t_atom *argv);

//set overall gain and rand gain range
void munger_gain(t_munger *x, t_symbol *s, long argc, t_atom *argv);
void munger_randgain(t_munger *x, t_symbol *s, long argc, t_atom *argv);

//fix position for start of grain playback
void munger_setposition(t_munger *x, t_symbol *s, long argc, t_atom *argv);

//post current parameter values
void munger_poststate(t_munger *x, t_symbol *s, long argc, t_atom *argv);

//external buffer funcs
void munger_setbuffer(t_munger *x, t_symbol *s);
float getExternalSamp(t_munger *x, double where, t_float *tab, double frames, double nc);


/****FUNCTIONS****/

//window stuff
float win_tick(t_munger *x, int whichone)
{
	long temp;
	float temp_time, alpha, output;
	
	x->winTime[whichone] += x->winRate[whichone];
	while (x->winTime[whichone] >= (float)WINLENGTH) x->winTime[whichone] -= (float)WINLENGTH;
	while (x->winTime[whichone] < 0.) x->winTime[whichone] += (float)WINLENGTH;
	
	temp_time = x->winTime[whichone];
	
	temp = (long)temp_time;
	alpha = temp_time - (float)temp;
	output = x->winTable[temp];
	output = output + (alpha * (x->winTable[temp+1] - output));
	return output;
}

//external buffer stuff
void munger_setbuffer(t_munger *x, t_symbol *s)
{
	if (!x->l_buffer)
		x->l_buffer = buffer_ref_new((t_object *)x, s);
	else
		buffer_ref_set(x->l_buffer, s);
		
	if (buffer_ref_exists(x->l_buffer)) {
		x->externalBuffer = 1;
		x->l_chan = 0;
	}
	else {
		x->externalBuffer = 0;
	}
}


//grain funcs
float envelope(t_munger *x, int whichone, float sample)
{
	long done = x->gvoiceDone[whichone];
	long tail = x->gvoiceSize[whichone] - x->gvoiceDone[whichone];
	
	/*
	if(x->doHanning) sample *= win_tick(x, whichone);
	else{
		if(done < x->gvoiceRamp[whichone]) sample *= (done*x->gvoiceOneOverRamp[whichone]);
		else if(tail < x->gvoiceRamp[whichone]) sample *= (tail*x->gvoiceOneOverRamp[whichone]);
	}
	*/
	if(done < x->gvoiceRamp[whichone]) sample *= (done*x->gvoiceOneOverRamp[whichone]);
	else if(tail < x->gvoiceRamp[whichone]) sample *= (tail*x->gvoiceOneOverRamp[whichone]);
	
	return sample;
}

//tries to find an available voice; return -1 if no voices available
int findVoice(t_munger *x)
{
	int i = 0, foundOne = -1;
	while(foundOne < 0 && i < x->voices ) {
		if (!x->gvoiceOn[i]) foundOne = i;
		i++;
	}
	return foundOne;
}

//creates a new (random) start position for a new grain, returns beginning start sample
//sets up size and direction
//max grain size is BUFLENGTH / 3, to avoid recording into grains while they are playing
float newSetup(t_munger *x, int whichVoice, double frames)
{
	float newPosition;
	int i;
	
	x->gvoiceSize[whichVoice] 		= newSize(x, whichVoice);
	x->gvoiceDirection[whichVoice] 	= newDirection(x);
	
	if(x->num_channels == 2) {
		x->gvoiceLPan[whichVoice] 		= ((float)rand() - RAND_MAX * 0.5) * ONE_OVER_MAXRAND * x->gpan_spread + 0.5;
		x->gvoiceRPan[whichVoice]		= 1. - x->gvoiceLPan[whichVoice];
		//make equal power panning....
		//x->gvoiceLPan[whichVoice] 		= powf(x->gvoiceLPan[whichVoice], 0.5);
		//x->gvoiceRPan[whichVoice] 		= powf(x->gvoiceRPan[whichVoice], 0.5);
	}
	else {
		for(i=0;i<x->num_channels;i++) {
			x->gvoiceSpat[whichVoice][i] = x->channelGain[i] + ((float)rand() - RAND_MAX * 0.5) * ONE_OVER_HALFRAND * x->channelGainSpread[i];
		}
	}
	
	x->gvoiceOn[whichVoice] 		= 1;
	x->gvoiceDone[whichVoice]		= 0;
	x->gvoiceGain[whichVoice]		= x->gain + ((float)rand() - RAND_MAX * 0.5) * ONE_OVER_HALFRAND * x->randgain;
	
	x->gvoiceADSRon[whichVoice]		= 0;
	
	if(x->gvoiceSize[whichVoice] < 2.*x->rampLength) {
		x->gvoiceRamp[whichVoice] = .5 * x->gvoiceSize[whichVoice];
		if(x->gvoiceRamp[whichVoice] <= 0.) x->gvoiceRamp[whichVoice] = 1.;
		x->gvoiceOneOverRamp[whichVoice] = 1./x->gvoiceRamp[whichVoice];
	}
	else {
		x->gvoiceRamp[whichVoice] = x->rampLength;
		if(x->gvoiceRamp[whichVoice] <= 0.) x->gvoiceRamp[whichVoice] = 1.;
		x->gvoiceOneOverRamp[whichVoice] = 1./x->gvoiceRamp[whichVoice];
	}
	
	
/*** set start point; tricky, cause of moving buffer, variable playback rates, backwards/forwards, etc.... ***/

	if(!x->externalBuffer) {
		// 1. random positioning and moving buffer (default)
		if(x->position == -1. && x->recordOn == 1) { 
			if(x->gvoiceDirection[whichVoice] == 1) {//going forward			
				if(x->gvoiceSpeed[whichVoice] > 1.) 
					newPosition = x->recordCurrent - x->onethirdBufsize - (float)rand() * ONE_OVER_MAXRAND * x->onethirdBufsize;
				else
					newPosition = x->recordCurrent - (float)rand() * ONE_OVER_MAXRAND * x->onethirdBufsize;//was 2/3rds
			}
			
			else //going backwards
				newPosition = x->recordCurrent - (float)rand() * ONE_OVER_MAXRAND * x->onethirdBufsize;
		}
		
		// 2. fixed positioning and moving buffer	
		else if (x->position >= 0. && x->recordOn == 1) {
			if(x->gvoiceDirection[whichVoice] == 1) {//going forward			
				if(x->gvoiceSpeed[whichVoice] > 1.) 
					//newPosition = x->recordCurrent - x->onethirdBufsize - x->position * x->onethirdBufsize;
					//this will follow more closely...
					newPosition = x->recordCurrent - x->gvoiceSize[whichVoice]*x->gvoiceSpeed[whichVoice] - x->position * x->onethirdBufsize;
					
				else
					newPosition = x->recordCurrent - x->position * x->onethirdBufsize;//was 2/3rds
			}
			
			else //going backwards
				newPosition = x->recordCurrent - x->position * x->onethirdBufsize;
		}
		
		// 3. random positioning and fixed buffer	
		else if (x->position == -1. && x->recordOn == 0) {
			if(x->gvoiceDirection[whichVoice] == 1) {//going forward			
				newPosition = x->recordCurrent - x->onethirdBufsize - (float)rand() * ONE_OVER_MAXRAND * x->onethirdBufsize;
			}	
			else //going backwards
				newPosition = x->recordCurrent - (float)rand() * ONE_OVER_MAXRAND * x->onethirdBufsize;
		}
		
		// 4. fixed positioning and fixed buffer	
		else if (x->position >= 0. && x->recordOn == 0) {
			if(x->gvoiceDirection[whichVoice] == 1) {//going forward			
				newPosition = x->recordCurrent - x->onethirdBufsize - x->position * x->onethirdBufsize;
			} else { //going backwards
				newPosition = x->recordCurrent - x->position * x->onethirdBufsize;
            }
		}
	}
	else {
		if (x->position == -1.) {
			newPosition = (float)rand() * ONE_OVER_MAXRAND * frames;
		} else if (x->position >= 0.) {
            newPosition = x->position * frames;
        } else {
            newPosition = 0.0;
        }
	}
	
	return newPosition;
	
}	

//creates a size for a new grain
//actual number of samples PLAYED, regardless of pitch
//might be shorter for higher pitches and long grains, to avoid collisions with recordCurrent
//size given now in milliseconds!
float newSize(t_munger *x, int whichOne)
{
	float newsize, temp, pitchExponent;
	int pitchChoice;
	
	//set grain pitch
	if(x->smoothPitch == 1) x->gvoiceSpeed[whichOne] = x->gpitch + ((float)rand() - RAND_MAX * 0.5) * ONE_OVER_HALFRAND*x->gpitch_var;
	else {
		//temp = (float)rand() * ONE_OVER_MAXRAND * x->gpitch_var * (float)PITCHTABLESIZE;
		temp = (float)rand() * ONE_OVER_MAXRAND * x->gpitch_var * (float)x->scale_len;
		pitchChoice = (int) temp;
		if(pitchChoice > PITCHTABLESIZE) pitchChoice = PITCHTABLESIZE;
		if(pitchChoice < 0) pitchChoice = 0;
		pitchExponent = x->pitchTable[pitchChoice];
		x->gvoiceSpeed[whichOne] = x->gpitch * pow(x->semitone, pitchExponent);
	}
	
	if(x->gvoiceSpeed[whichOne] < MINSPEED) x->gvoiceSpeed[whichOne] = MINSPEED;
	newsize = x->srate_ms*(x->glen + ((float)rand() - RAND_MAX * 0.5) * ONE_OVER_HALFRAND*x->glen_var);
	if(newsize > x->maxsize) newsize = x->maxsize;
	if(newsize*x->gvoiceSpeed[whichOne] > x->maxsize) 
		newsize = x->maxsize/x->gvoiceSpeed[whichOne];
	if(newsize < x->minsize) newsize = x->minsize;
	return newsize;

}	

int newDirection(t_munger *x)
{
//-1 == always backwards
//0  == backwards and forwards (default)
//1  == only forwards
	int dir;
	if(x->ambi == 0) {
		dir = rand() - RAND_MAX * 0.5;
		if (dir < 0) dir = -1;
		else dir = 1;
	} 
	else 
		if(x->ambi == -1) dir = -1;
	else
		dir = 1;

	return dir;
}


float newNote(t_munger *x, int whichVoice, int newNote, double frames)
{
	float newPosition;
	int i, temp;
	
	x->gvoiceSize[whichVoice] 		= newNoteSize(x, whichVoice, newNote);
	//x->gvoiceDirection[whichVoice] 	= newDirection(x);	 
	x->gvoiceDirection[whichVoice]	= x->noteDirection[newNote];
	
	if(x->num_channels == 2) {
		//x->gvoiceLPan[whichVoice] 		= ((float)rand() - 16384.) * ONE_OVER_MAXRAND * x->gpan_spread + 0.5;
		//x->gvoiceRPan[whichVoice]		= 1. - x->gvoiceLPan[whichVoice];
		//make equal power panning....
		//x->gvoiceLPan[whichVoice] 		= powf(x->gvoiceLPan[whichVoice], 0.5);
		//x->gvoiceRPan[whichVoice] 		= powf(x->gvoiceRPan[whichVoice], 0.5);
		x->gvoiceLPan[whichVoice] 		= powf(x->notePan[newNote], 0.5);
		x->gvoiceRPan[whichVoice] 		= powf((1. - x->notePan[newNote]), 0.5);
	}
	else {
		if(x->notePan[newNote] == -1.) {
			for(i=0;i<x->num_channels;i++) {
				x->channelGain[i] 		= 1.;	
				x->channelGainSpread[i] = 0.;
			}
		} else {
			for(i=0;i<x->num_channels;i++) {
				x->channelGain[i] 		= 0.;	//initialize all to 0.
				x->channelGainSpread[i] = 0.;
			}
			temp = (int)x->notePan[newNote];
			if(temp>=x->num_channels) temp=0;
			x->channelGain[temp] = 1.;			//update the one we want
		}
		for(i=0;i<x->num_channels;i++) {
			x->gvoiceSpat[whichVoice][i] = x->channelGain[i] + ((float)rand() - RAND_MAX * 0.5) * ONE_OVER_HALFRAND * x->channelGainSpread[i];
		}
	}
	
	x->gvoiceOn[whichVoice] 		= 1;
	x->gvoiceDone[whichVoice]		= 0;
	x->gvoiceGain[whichVoice]		= x->noteGain[newNote];
	
	x->gvoiceADSRon[whichVoice]		= 1;
	ADSR_setAllTimes(&x->gvoiceADSR[whichVoice], x->noteAttack[newNote], x->noteDecay[newNote], x->noteSustain[newNote], x->noteRelease[newNote], x->srate_ms);
	ADSR_keyOn(&x->gvoiceADSR[whichVoice]);
	
/*** set start point; tricky, cause of moving buffer, variable playback rates, backwards/forwards, etc.... ***/

    if(!x->externalBuffer) {
		// 1. random positioning and moving buffer (default)
		if(x->position == -1. && x->recordOn == 1) { 
			if(x->gvoiceDirection[whichVoice] == 1) {//going forward			
				if(x->gvoiceSpeed[whichVoice] > 1.) 
					newPosition = x->recordCurrent - x->onethirdBufsize - (float)rand() * ONE_OVER_MAXRAND * x->onethirdBufsize;
				else
					newPosition = x->recordCurrent - (float)rand() * ONE_OVER_MAXRAND * x->onethirdBufsize;//was 2/3rds
			}
			
			else //going backwards
				newPosition = x->recordCurrent - (float)rand() * ONE_OVER_MAXRAND * x->onethirdBufsize;
		}
		
		// 2. fixed positioning and moving buffer	
		else if (x->position >= 0. && x->recordOn == 1) {
			if(x->gvoiceDirection[whichVoice] == 1) {//going forward			
				if(x->gvoiceSpeed[whichVoice] > 1.) 
					//newPosition = x->recordCurrent - x->onethirdBufsize - x->position * x->onethirdBufsize;
					//this will follow more closely...
					newPosition = x->recordCurrent - x->gvoiceSize[whichVoice]*x->gvoiceSpeed[whichVoice] - x->position * x->onethirdBufsize;
					
				else
					newPosition = x->recordCurrent - x->position * x->onethirdBufsize;//was 2/3rds
			}
			
			else //going backwards
				newPosition = x->recordCurrent - x->position * x->onethirdBufsize;
		}
		
		// 3. random positioning and fixed buffer	
		else if (x->position == -1. && x->recordOn == 0) {
			if(x->gvoiceDirection[whichVoice] == 1) {//going forward			
				newPosition = x->recordCurrent - x->onethirdBufsize - (float)rand() * ONE_OVER_MAXRAND * x->onethirdBufsize;
			}	
			else //going backwards
				newPosition = x->recordCurrent - (float)rand() * ONE_OVER_MAXRAND * x->onethirdBufsize;
		}
		
		// 4. fixed positioning and fixed buffer	
		else if (x->position >= 0. && x->recordOn == 0) {
			if(x->gvoiceDirection[whichVoice] == 1) {//going forward			
				newPosition = x->recordCurrent - x->onethirdBufsize - x->position * x->onethirdBufsize;
			}	
			else //going backwards
				newPosition = x->recordCurrent - x->position * x->onethirdBufsize;
		}
	}
	else {
		if (x->position == -1.) {
			newPosition = (float)rand() * ONE_OVER_MAXRAND * frames;
		}
		else  if (x->position >= 0.) newPosition = x->position * frames;
	}
	
	return newPosition;
	
}	

//creates a size for a new grain
//actual number of samples PLAYED, regardless of pitch
//might be shorter for higher pitches and long grains, to avoid collisions with recordCurrent
//size given now in milliseconds!
//for oneshot notes, this will also scale the ADSR and make it smaller, if the grainSpeed is high
float newNoteSize(t_munger *x, int whichOne, int newNote)
{
	float newsize, temp, temp2, pitchExponent;
	
	//set grain pitch
	pitchExponent = x->noteTransp[newNote];
	x->gvoiceSpeed[whichOne] = x->gpitch * pow(x->semitone, pitchExponent);
	
	if(x->gvoiceSpeed[whichOne] < MINSPEED) x->gvoiceSpeed[whichOne] = MINSPEED;
	newsize = x->srate_ms*(x->noteSize[newNote]);
	//if(newsize > x->maxsize) newsize = x->maxsize;
	if(newsize*x->gvoiceSpeed[whichOne] > x->maxsize) {
		temp2 = x->maxsize/x->gvoiceSpeed[whichOne]; //newsize
		temp = temp2/newsize;
		x->noteAttack[newNote] *= temp;
		x->noteDecay[newNote] *= temp;
		x->noteRelease[newNote] *= temp;
		newsize = temp2;
	}
	//if(newsize < x->minsize) newsize = x->minsize;
	return newsize;

}


//buffer funcs
void recordSamp(t_munger *x, float sample)
{
	if(x->recordCurrent >= x->buflen) x->recordCurrent = 0;
	
	if(x->recordOn) {
		if(x->rec_ramping == 0) x->recordBuf[x->recordCurrent++] = sample; //add sample
		else { //ramp up or down if turning on/off recording
			x->recordBuf[x->recordCurrent++] = sample * RECORDRAMP_INV * (float)x->recordRampVal;
			x->recordRampVal += x->rec_ramping;
			if(x->recordRampVal <= 0) {
				x->rec_ramping = 0;
				x->recordOn = 0;
			}
			if(x->recordRampVal >= RECORDRAMP) x->rec_ramping = 0;
		}
	}
}

float getSamp(t_munger *x, double where)
{
	double alpha, om_alpha, output;
	long first;
	
	//while(where < 0.) where += (double)x->buflen;
	//while(where >= (double)x->buflen) where -= (double)x->buflen;

	if(where < 0.) where = x->buflen + fmod(where, x->buflen);
	if(where >= x->buflen) where = fmod(where, x->buflen);
	
	first = (long)where;
	
	alpha = where - first;
	om_alpha = 1. - alpha;
	
	output = x->recordBuf[first++] * om_alpha;
	if(first <  x->buflen) {
		output += x->recordBuf[first] * alpha;
	}
	else {
		output += x->recordBuf[0] * alpha;
	}
	
	return (float)output;
	
}

float getExternalSamp(t_munger *x, double where, t_float *tab, double frames, double nc)
{
	double alpha, om_alpha, output;
	long first;
	double sampNum;
	
	if (where < 0.) where = 0.;
	else if (where >= frames) where = 0.;
	
	sampNum = where*nc;
	
	first = (long)sampNum;
	
	alpha = sampNum - first;
	om_alpha = 1. - alpha;
	
	output = tab[first] * om_alpha;
	first += (long)nc;
	output += tab[first] * alpha;
	
	return (float)output;
}

//primary MSP funcs
void ext_main(void *f)
{
    t_class *c = class_new("munger~", (method)munger_new, (method)munger_free, (long)sizeof(t_munger), 0L, A_DEFFLOAT, A_DEFLONG, 0);
    
    class_addmethod(c, (method)munger_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)munger_dsp64, "dsp64", A_CANT, 0);
	class_addmethod(c, (method)munger_notify, "notify", A_CANT, 0);
	
    class_addmethod(c, (method)munger_float, "float", A_FLOAT, 0);
    class_addmethod(c, (method)munger_setramp, "ramptime", A_GIMME, 0);
    class_addmethod(c, (method)munger_sethanning, "hanning", A_GIMME, 0);
    class_addmethod(c, (method)munger_tempered, "tempered", A_GIMME, 0);
    class_addmethod(c, (method)munger_smooth, "smooth", A_GIMME, 0);
    class_addmethod(c, (method)munger_scale, "scale", A_GIMME, 0);
    class_addmethod(c, (method)munger_spat, "spatialize", A_GIMME, 0);
    class_addmethod(c, (method)munger_note, "note", A_GIMME, 0);
    class_addmethod(c, (method)munger_oneshot, "oneshot", A_GIMME, 0);
    class_addmethod(c, (method)munger_bufsize, "delaylength", A_GIMME, 0);
    class_addmethod(c, (method)munger_bufsize_ms, "delaylength_ms", A_GIMME, 0);
    class_addmethod(c, (method)munger_setvoices, "voices", A_GIMME, 0);
    class_addmethod(c, (method)munger_maxvoices, "maxvoices", A_GIMME, 0);
    class_addmethod(c, (method)munger_setminsize, "minsize", A_GIMME, 0);
    class_addmethod(c, (method)setpower, "power", A_GIMME, 0);
    class_addmethod(c, (method)munger_ambidirectional, "ambidirectional", A_GIMME, 0);
    class_addmethod(c, (method)munger_record, "record", A_GIMME, 0);
    class_addmethod(c, (method)munger_gain, "gain", A_GIMME, 0);
    class_addmethod(c, (method)munger_randgain, "rand_gain", A_GIMME, 0);
    class_addmethod(c, (method)munger_setposition, "position", A_GIMME, 0);
    class_addmethod(c, (method)munger_poststate, "state", A_GIMME, 0);
    class_addmethod(c, (method)munger_clear, "clear", A_GIMME, 0);
    class_addmethod(c, (method)munger_setbuffer, "buffer", A_SYM, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    munger_class = c;
    ps_buffer = gensym("buffer~");
}

void munger_setramp(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	x->doHanning = 0;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				//post("munger: setting ramp to: %ld ms", argv[i].a_w.w_long);
				x->rampLength = x->srate_ms * (float)argv[i].a_w.w_long; 
				if(x->rampLength <= 0.) x->rampLength = 1.;
				break;
			case A_FLOAT:
				//post("munger: setting ramp to: %lf ms", argv[i].a_w.w_float);
				x->rampLength = x->srate_ms * argv[i].a_w.w_float;
				if(x->rampLength <= 0.) x->rampLength = 1.; 
				break;
		}
	}
}

void munger_scale(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	int i,j;
	
	//post("munger: loading scale from input list");
	x->smoothPitch = 0;
	
	for(i=0;i<PITCHTABLESIZE;i++) x->pitchTable[i] = 0.;
	if (argc > PITCHTABLESIZE) argc = PITCHTABLESIZE;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				x->pitchTable[i] = (float)argv[i].a_w.w_long; 
				break;
			case A_FLOAT:
				x->pitchTable[i] = argv[i].a_w.w_float;
				break;
		}
	}
	
	x->scale_len = argc;
	
	i=0;
	//wrap input list through all of pitchTable
	for (j=argc; j < PITCHTABLESIZE; j++) {
		x->pitchTable[j] = x->pitchTable[i++];
		if (i >= argc) i = 0;
	}
		
}

void munger_spat(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	int i, j;
	
	for (i=j=0; i < (argc - 1); i+=2) {
		switch (argv[i].a_type) {
			case A_LONG:
				x->channelGain[j] = (float)argv[i].a_w.w_long; 
				break;
			case A_FLOAT:
				x->channelGain[j] = argv[i].a_w.w_float;
				break;
		}
		switch (argv[i+1].a_type) {
			case A_LONG:
				x->channelGainSpread[j] = (float)argv[i+1].a_w.w_long; 
				break;
			case A_FLOAT:
				x->channelGainSpread[j] = argv[i+1].a_w.w_float;
				break;
		}
		//post("munger: channel gain %d = %f, spread = %f", j, x->channelGain[j], x->channelGainSpread[j]);
		j++;
	}
}

void munger_note(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	if(argc < 8) {
		post("munger: need 8 args -- transposition, gain, pan, attkT, decayT, susLevel, relT, direction [-1/1]");
		return;
	}
	
	x->newnote++;
	
	if(x->newnote >= NUMVOICES) {
		post("munger: too many notes amadeus.");
		return;
	}
	
	switch (argv[0].a_type) {
		case A_LONG:
			x->noteTransp[x->newnote] = (float)argv[0].a_w.w_long; 
			break;
		case A_FLOAT:
			x->noteTransp[x->newnote] = argv[0].a_w.w_float;
			break;
	}
	
	switch (argv[1].a_type) {
		case A_LONG:
			x->noteGain[x->newnote] = (float)argv[1].a_w.w_long; 
			break;
		case A_FLOAT:
			x->noteGain[x->newnote] = argv[1].a_w.w_float;
			break;
	}
	
	switch (argv[2].a_type) {
		case A_LONG:
			x->notePan[x->newnote] = (float)argv[2].a_w.w_long; 
			break;
		case A_FLOAT:
			x->notePan[x->newnote] = argv[2].a_w.w_float;
			break;
	}
		
	switch (argv[3].a_type) {
		case A_LONG:
			x->noteAttack[x->newnote] = (float)argv[3].a_w.w_long; 
			break;
		case A_FLOAT:
			x->noteAttack[x->newnote] = argv[3].a_w.w_float;
			break;
	}
	
	switch (argv[4].a_type) {
		case A_LONG:
			x->noteDecay[x->newnote] = (float)argv[4].a_w.w_long; 
			break;
		case A_FLOAT:
			x->noteDecay[x->newnote] = argv[4].a_w.w_float;
			break;
	}
	
	switch (argv[5].a_type) {
		case A_LONG:
			x->noteSustain[x->newnote] = (float)argv[5].a_w.w_long; 
			break;
		case A_FLOAT:
			x->noteSustain[x->newnote] = argv[5].a_w.w_float;
			break;
	}
	
	switch (argv[6].a_type) {
		case A_LONG:
			x->noteRelease[x->newnote] = (float)argv[6].a_w.w_long; 
			break;
		case A_FLOAT:
			x->noteRelease[x->newnote] = argv[6].a_w.w_float;
			break;
	}
	
	switch (argv[7].a_type) {
		case A_LONG:
			x->noteDirection[x->newnote] = (int)argv[7].a_w.w_long; 
			break;
		case A_FLOAT:
			x->noteDirection[x->newnote] = (int)argv[7].a_w.w_float;
			break;
	}
	
	
	x->noteSize[x->newnote] = x->noteAttack[x->newnote] + x->noteDecay[x->newnote] + x->noteRelease[x->newnote];
	

}

//turn oneshot mode on/off. in oneshot mode, the internal granular voice allocation method goes away
//	so the munger will be silent, except when it receives "note" messages
void munger_oneshot(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	int temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (int)argv[i].a_w.w_long;
				x->oneshot = temp;
    			post("munger: setting oneshot: %d", temp);
				break;
			case A_FLOAT:
				temp = (int)argv[i].a_w.w_long;
				x->oneshot = temp;
    			post("munger: setting oneshot: %d", temp);
				break;
		}
	}
}

void munger_bufsize(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = x->srate * (float)argv[i].a_w.w_long;
				if(temp < 20.*(float)MINSIZE) temp = 20.*(float)MINSIZE;
				//if(temp > (float)BUFLENGTH) temp = (float)BUFLENGTH;
				if(temp > x->initbuflen) temp = x->initbuflen;
				//x->buflen = temp;
				//x->maxsize = x->buflen / 3.;
				x->maxsize = temp / 3.;
    			x->twothirdBufsize = x->maxsize * 2.;
    			x->onethirdBufsize = x->maxsize; 
    			//post("munger: setting delaylength to: %f seconds", (x->buflen/x->srate));
				break;
			case A_FLOAT:
				temp = x->srate * argv[i].a_w.w_float;
				if(temp < 20.*(float)MINSIZE) temp = 20.*(float)MINSIZE;
				//if(temp > (float)BUFLENGTH) temp = (float)BUFLENGTH;
				if(temp > x->initbuflen) temp = x->initbuflen;
				//x->buflen = temp;
				//x->maxsize = x->buflen / 3.;
				x->maxsize = temp / 3.;
    			x->twothirdBufsize = x->maxsize * 2.;
    			x->onethirdBufsize = x->maxsize; 
    			//post("munger: setting delaylength to: %f seconds", x->buflen/x->srate);
				break;
		}
	}
}

void munger_bufsize_ms(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = x->srate_ms * (float)argv[i].a_w.w_long;
				if(temp < 20.*(float)MINSIZE) temp = 20.*(float)MINSIZE;
				//if(temp > (float)BUFLENGTH) temp = (float)BUFLENGTH;
				if(temp > x->initbuflen) temp = x->initbuflen;
				//x->buflen = temp;
				//x->maxsize = x->buflen / 3.;
				x->maxsize = temp / 3.;
    			x->twothirdBufsize = x->maxsize * 2.;
    			x->onethirdBufsize = x->maxsize; 
    			//post("munger: setting delaylength to: %f seconds", (x->buflen/x->srate));
				break;
			case A_FLOAT:
				temp = x->srate_ms * argv[i].a_w.w_float;
				if(temp < 20.*(float)MINSIZE) temp = 20.*(float)MINSIZE;
				//if(temp > (float)BUFLENGTH) temp = (float)BUFLENGTH;
				if(temp > x->initbuflen) temp = x->initbuflen;
				//x->buflen = temp;
				//x->maxsize = x->buflen / 3.;
				x->maxsize = temp / 3.;
    			x->twothirdBufsize = x->maxsize * 2.;
    			x->onethirdBufsize = x->maxsize; 
    			//post("munger: setting delaylength to: %f seconds", x->buflen/x->srate);
				break;
		}
	}
}

void munger_setminsize(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = x->srate_ms * (float)argv[i].a_w.w_long;
				if(temp < (float)MINSIZE) temp = (float)MINSIZE;
				if(temp >= x->initbuflen) {
					temp = (float)MINSIZE;
					post("munger error: minsize too large!");
				}
				x->minsize = temp;
    			//post("munger: setting min grain size to: %f ms", (x->minsize/x->srate_ms));
				break;
			case A_FLOAT:
				temp = x->srate_ms * argv[i].a_w.w_float;
				if(temp < (float)MINSIZE) temp = (float)MINSIZE;
				if(temp >= x->initbuflen) {
					temp = (float)MINSIZE;
					post("munger error: minsize too large!");
				}
				x->minsize = temp;
    			//post("munger: setting min grain size to: %f ms", (x->minsize/x->srate_ms));
				break;
		}
	}
}


void munger_setvoices(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	int temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = argv[i].a_w.w_long;
				if(temp < 0) temp = 0;
				if(temp > x->maxvoices) temp = x->maxvoices;
				x->voices = temp;
    			//post("munger: setting max voices to: %d ", x->voices);
				break;
			case A_FLOAT:
				temp = (int)argv[i].a_w.w_float;
				if(temp < 0) temp = 0;
				if(temp > x->maxvoices) temp = x->maxvoices;
				x->voices = temp;
    			//post("munger: setting max voices to: %d ", x->voices);
				break;
		}
	}
}

void munger_maxvoices(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	int temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = argv[i].a_w.w_long;
				if(temp < 0) temp = 0;
				if(temp > NUMVOICES) temp = NUMVOICES;
				x->maxvoices = temp;
    			//post("munger: setting max voices to: %d ", x->voices);
				break;
			case A_FLOAT:
				temp = (int)argv[i].a_w.w_float;
				if(temp < 0) temp = 0;
				if(temp > NUMVOICES) temp = NUMVOICES;
				x->maxvoices = temp;
    			//post("munger: setting max voices to: %d ", x->voices);
				break;
		}
	}
}


void setpower(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	int temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (int)argv[i].a_w.w_long;
				x->power = temp;
    			post("munger: setting power: %d", temp);
				break;
			case A_FLOAT:
				temp = (int)argv[i].a_w.w_long;
				x->power = temp;
    			post("munger: setting power: %d", temp);
				break;
		}
	}
}

void munger_record(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	int temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (int)argv[i].a_w.w_long;
				//x->recordOn = temp;
				if (!temp) {
					x->recordRampVal = RECORDRAMP;
					x->rec_ramping = -1;
				} else {
					x->recordOn = 1;
					x->recordRampVal = 0;
					x->rec_ramping = 1;
				}
    			//post("munger: setting record: %d", temp);
				break;
			case A_FLOAT:
				temp = (int)argv[i].a_w.w_float;
				//x->recordOn = temp;
				if (!temp) {
					x->recordRampVal = RECORDRAMP;
					x->rec_ramping = -1;
				} else {
					x->recordOn = 1;
					x->recordRampVal = 0;
					x->rec_ramping = 1;
				}
	 			//post("munger: setting record: %d", temp);
				break;
		}
	}
}

void munger_ambidirectional(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	int temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (int)argv[i].a_w.w_long;
				x->ambi = temp;
    			//post("munger: setting ambidirectional: %d", temp);
				break;
			case A_FLOAT:
				temp = (int)argv[i].a_w.w_float;
				x->ambi = temp;
    			//post("munger: setting ambidirectional: %d", temp);
				break;
		}
	}
}

void munger_gain(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (float)argv[i].a_w.w_long;
    			//post("munger: setting gain to: %f ", temp);
    			x->gain = temp;
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
				//post("munger: setting gain to: %f ", temp);
				x->gain = temp;
				break;
		}
	}
}

void munger_setposition(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (float)argv[i].a_w.w_long;
				if (temp > 1.) temp = 1.;
    			if (temp < 0.) temp = -1.;
    			//post("munger: setting position to: %f ", temp);
    			x->position = temp;
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
				if (temp > 1.) temp = 1.;
    			else if (temp < 0.) temp = -1.;
    			//post("munger: setting position to: %f ", temp);
    			x->position = temp;
				break;
		}
	}
}

void munger_randgain(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (float)argv[i].a_w.w_long;
    			//post("munger: setting rand_gain to: %f ", temp);
    			x->randgain = temp;
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
				//post("munger: setting rand_gain to: %f ", temp);
				x->randgain = temp;
				break;
		}
	}
}

void munger_sethanning(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	post("munger: hanning window is busted");
	x->doHanning = 1;
}

void munger_tempered(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	int i;
	//post("munger: doing tempered scale");
	x->smoothPitch = 0;
	x->scale_len = 100;
	for(i=0; i<x->scale_len-1; i += 2) {
		x->pitchTable[i] = 0.5*i;
		x->pitchTable[i+1] = -0.5*i;
	}
	x->scale_len = PITCHTABLESIZE;
}
void munger_smooth(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	//post("munger: doing smooth scale");
	x->smoothPitch = 1;
}

void munger_alloc(t_munger *x)
{
	//x->recordBuf = t_getbytes(BUFLENGTH * sizeof(float));
	//x->recordBuf = t_getbytes(x->buflen * sizeof(float));
	x->recordBuf = (float *)sysmem_newptr(x->buflen * sizeof(float));
	if (!x->recordBuf) {
		error("munger: out of memory");
		return;
	}
}

void munger_clear(t_munger *x, t_symbol *s, long argc, t_atom *argv)
{
	long i;
	for(i=0; i<x->initbuflen; i++) x->recordBuf[i] = 0.;
}


void munger_free(t_munger *x)
{
	dsp_free((t_pxobject *)x);
	object_free(x->l_buffer);
	if (x->recordBuf)
		//t_freebytes(x->recordBuf, BUFLENGTH * sizeof(float));
		//t_freebytes(x->recordBuf, x->initbuflen * sizeof(float));
		sysmem_freeptr(x->recordBuf);
}


t_max_err munger_notify(t_munger *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	return buffer_ref_notify(x->l_buffer, s, msg, sender, data);
}


void munger_assist(t_munger *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
			case 0:
				sprintf(s,"(signal) input");
				break;
            case 1:
                sprintf(s,"(signal/float) grain rate");
                break;
            case 2:
                sprintf(s,"(signal/float) grain rate variation");
                break;
            case 3:
                sprintf(s,"(signal/float) grain length");
                break;
            case 4:
                sprintf(s,"(signal/float) grain length variation");
                break;
            case 5:
                sprintf(s,"(signal/float) grain pitch");
                break;
            case 6:
                sprintf(s,"(signal/float) grain pitch variation");
                break;
            case 7:
                sprintf(s,"(signal/float) grain pan spread");
                break;
        }
	} else {
		sprintf(s,"(signal) output");
    }
}

void munger_float(t_munger *x, double f)
{
	if (x->x_obj.z_in == 1) {
		x->grate = f;
	} else if (x->x_obj.z_in == 2) {
		x->grate_var = f;
	} else if (x->x_obj.z_in == 3) {
		x->glen = f;
	} else if (x->x_obj.z_in == 4) {
		x->glen_var = f;
	} else if (x->x_obj.z_in == 5) {
		x->gpitch = f;
	} else if (x->x_obj.z_in == 6) {
		x->gpitch_var = f;
	} else if (x->x_obj.z_in == 7) {
		x->gpan_spread = f;
	}
}

//hanning y = 0.5 + 0.5*cos(TWOPI * n/N + PI)

void *munger_new(double maxdelay, long channels)
{
	int i, j;
    
    t_munger *x = (t_munger *)object_alloc(munger_class);
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_munger);i++)  
                ((char *)x)[i]=0; 
	} 
	
	if (maxdelay < 100.) maxdelay = 3000.; //set maxdelay to 3000ms by default
	post("munger: maxdelay = %f milliseconds", maxdelay);
	
	if (channels < 2) x->num_channels = 2;
	else x->num_channels = channels;
	if (x->num_channels > MAXCHANNELS) x->num_channels = MAXCHANNELS;
	post ("munger: number channels = %d", x->num_channels);
	
    dsp_setup((t_pxobject *)x,8);
    for (i=0;i<x->num_channels;i++) {
    	outlet_new((t_object *)x, "signal");
    }
    			   
    x->srate = sys_getsr();
    x->one_over_srate = 1./x->srate;
    x->srate_ms = x->srate/1000.;
    x->one_over_srate_ms = 1./x->srate_ms;
    
    //x->buflen = (float)BUFLENGTH;
    if (x->recordBuf)
		sysmem_freeptr(x->recordBuf);
		
    x->initbuflen = (float)(maxdelay + 50.) * 44.1; //adding a little extra to avoid boundary bugs.
    x->buflen = x->initbuflen;
    x->maxsize = x->buflen / 3.;
    x->twothirdBufsize = x->maxsize * 2.;
    x->onethirdBufsize = x->maxsize;
    x->minsize = MINSIZE;
    x->voices = 10;
    x->gain = 1.;
    x->randgain = 0.;
    
    munger_alloc(x);
    
    x->twelfth = 1./12.;
    x->semitone = pow(2., 1./12.);
    x->smoothPitch = 1;
    x->scale_len = PITCHTABLESIZE;
    
    x->grate = 1.;				
    x->grate_var = 0.;	
    x->glen = 1.; 				
    x->glen_var = 0.; 		
    x->gpitch = 1.; 		 
    x->gpitch_var = 0.;
    x->gpan_spread = 0.;
    x->time = 0;	
    x->position = -1.; //-1 default == random positioning
    
    x->gimme = 0.;	
    
    x->power = 1;
    x->ambi = 0;
    x->maxvoices = 20;
    
	x->oneshot = 0;
    x->newnote = 0;
      
    for(i=0; i<NUMVOICES; i++) {
    	x->gvoiceSize[i] = 1000;			
    	x->gvoiceSpeed[i] = 1.;			
    	x->gvoiceCurrent[i] = 0.;		
    	x->gvoiceDirection[i] = 1;		
    	x->gvoiceOn[i] = 0;			
    	x->gvoiceDone[i] = 0;			
    	x->gvoiceRPan[i] = .5;
    	x->gvoiceLPan[i] = .5;
    	x->gvoiceGain[i] = 1.;
    	ADSR_init(&x->gvoiceADSR[i]);
    	x->gvoiceADSRon[i] = 0;
    	for(j=0;j<MAXCHANNELS;j++) {
    		x->gvoiceSpat[i][j] = 0.;
    	}
    	
    	//note and oneshot inits
	    x->noteTransp[i] = 0.;
	    x->noteSize[i] = 100.;
	    x->notePan[i] = 0.5;
	    x->noteGain[i] = 1.;
	    x->noteAttack[i] = 20.;
	    x->noteDecay[i] = 50.;
	    x->noteSustain[i] = 0.3;
	    x->noteRelease[i] = 200.;
    }
    
    for(i=0;i<MAXCHANNELS;i++) {
    	x->channelGain[i] = 0.;
    	x->channelGainSpread[i] = 0.;
    }
    
    //init hanning window
    x->doHanning = 0;
    for(i=0; i<WINLENGTH; i++) 
    	x->winTable[i] = 0.5 + 0.5*cos(TWOPI * i/WINLENGTH + .5*TWOPI);
    	
    for(i=0; i<PITCHTABLESIZE; i++) {
		x->pitchTable[i] = 0.;
	}
    	
    x->rampLength = 256.;
    
    //sample buffer
    //for(i=0; i<BUFLENGTH; i++) x->recordBuf[i] = 0.;
    for(i=0; i<x->initbuflen; i++) x->recordBuf[i] = 0.;
    x->recordOn = 1; //boolean
	x->recordCurrent = 0;
	x->recordRampVal = 0; 
	x->rec_ramping = 0;
	
	x->externalBuffer = 0; //use internal buffer by default

    srand(0.54);
    //post("mungery away");
    
    return (x);
}

void munger_dsp64(t_munger *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->grate_connected 			= count[1];
	x->grate_var_connected		= count[2];
	x->glen_connected			= count[3];
	x->glen_var_connected		= count[4];
	x->gpitch_connected			= count[5];
	x->gpitch_var_connected		= count[6];
	x->gpan_spread_connected	= count[7];
	
	x->srate = samplerate;
    x->one_over_srate = 1./x->srate;
    
    x->srate_ms = x->srate * .001;
    x->one_over_srate_ms = 1000. * x->one_over_srate;
    
    object_method(dsp64, gensym("dsp_add64"), x, munger_perform64, 0, NULL);
}

void munger_perform64(t_munger *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double *in = (t_double *)(ins[0]);
	
	t_double grate 		= x->grate_connected? 		*(t_double *)(ins[0]) : x->grate;
	t_double grate_var 	= x->grate_var_connected? 	*(t_double *)(ins[1]) : x->grate_var;
	t_double glen 		= x->glen_connected? 		*(t_double *)(ins[2]) : x->glen;
	t_double glen_var 	= x->glen_var_connected? 	*(t_double *)(ins[3]) : x->glen_var;
	t_double gpitch 	= x->gpitch_connected? 		*(t_double *)(ins[4]) : x->gpitch;
	t_double gpitch_var	= x->gpitch_var_connected? 	*(t_double *)(ins[5]) : x->gpitch_var;
	t_double gpan_spread= x->gpan_spread_connected? *(t_double *)(ins[6]) : x->gpan_spread;
	
	t_double outsamp[MAXCHANNELS], samp;
	int newvoice, i, j;
	long n;
	t_double *out[MAXCHANNELS];
	//t_double *outL = (t_double *)(w[10]);
	//t_double *outR = (t_double *)(w[11]);
	
	for (i=0;i<x->num_channels;i++) {
		out[i] = (t_double *)(outs[i]);
	}
	n = sampleframes;
	
	//make sure vars are updated if signals are connected; stupid, lazy, boob.
	x->grate = grate;
	x->grate_var = grate_var;
	x->glen = glen;
	x->glen_var = glen_var;
	x->gpitch = gpitch;
	x->gpitch_var = gpitch_var;
	x->gpan_spread = gpan_spread;
		
	//grate = grate + RAND01 * grate_var;
	//grate = grate + ((t_double)rand() - 16384.) * ONE_OVER_HALFRAND * grate_var;
	//gimme = x->srate_ms * grate; //grate is actually time-distance between grains

	if(gpan_spread > 1.) gpan_spread = 1.;
	if(gpan_spread < 0.) gpan_spread = 0.;

	if(!x->power) {
		while(n--) { 	//copy and zero out when unpowered (this is slightly less efficient than
						//the z_disabled approach, but some users expect it now
			for(i=0;i<x->num_channels;i++) {
				*out[i]++ = 0.;
			}
		}
	}
	else {
		t_buffer_obj	*buffer = buffer_ref_getobject(x->l_buffer);
		t_float			*tab = buffer_locksamples(buffer);
		double			frames = 0;
		double			nc = 0;

		if (tab) {
			frames = buffer_getframecount(buffer);
			nc = buffer_getchannelcount(buffer);
		}
		
		while(n--) {
			//outsampL = outsampR = 0.;
			for(i=0;i<x->num_channels;i++) outsamp[i] = 0.;
			
			//record a sample
			//if(x->recordOn) recordSamp(x, *in++);
			recordSamp(x, *in++);
			
			//grab a note if requested; works in oneshot mode or otherwise
			while(x->newnote > 0) {
				newvoice = findVoice(x);
				if(newvoice >= 0) {
					x->gvoiceCurrent[newvoice] = newNote(x, newvoice, x->newnote, frames);
				}
				x->newnote--;
			}
			
			//find a voice if it's time (high resolution). ignore if in "oneshot" mode		
			if(!x->oneshot) {
				if(x->time >= (long)x->gimme) {
					x->time = 0;
					newvoice = findVoice(x);
					if(newvoice >= 0) {
						x->gvoiceCurrent[newvoice] = newSetup(x, newvoice, frames);
					}
					grate = grate + ((t_double)rand() - RAND_MAX * 0.5) * ONE_OVER_HALFRAND * grate_var;
					x->gimme = x->srate_ms * grate; //grate is actually time-distance between grains
				}
			} 
			x->time++;
			
			//mix 'em, pan 'em
			for(i=0; i< x->maxvoices; i++) {
			//for(i=0; i<x->voices; i++) {
				if(x->gvoiceOn[i]) {
					//get a sample, envelope it
					if(x->externalBuffer) samp = getExternalSamp(x, x->gvoiceCurrent[i], tab, frames, nc);
					else samp = getSamp(x, x->gvoiceCurrent[i]);
					if (!x->gvoiceADSRon[i]) samp = envelope(x, i, samp) * x->gvoiceGain[i];
					else samp = samp * ADSR_ADRtick(&x->gvoiceADSR[i]) * x->gvoiceGain[i];
					
					//pan it
					if(x->num_channels == 2) {
						outsamp[0] += samp * x->gvoiceLPan[i];
						outsamp[1] += samp * x->gvoiceRPan[i];
					}
					else { //multichannel subroutine
						for(j=0;j<x->num_channels;j++) {
							outsamp[j] += samp * x->gvoiceSpat[i][j];
						}
					}
					
					//see if grain is done after jumping to next sample point
					x->gvoiceCurrent[i] += (double)x->gvoiceDirection[i] * (double)x->gvoiceSpeed[i];
					if (!x->gvoiceADSRon[i]) {
						if(++x->gvoiceDone[i] >= x->gvoiceSize[i]) x->gvoiceOn[i] = 0;
					}
					else {
						if(ADSR_getState(&x->gvoiceADSR[i]) == DONE) x->gvoiceOn[i] = 0;
					}
				}
			}
			for(i=0;i<x->num_channels;i++) {
				*out[i]++ = outsamp[i];
			}
		}
		if (tab)
			buffer_unlocksamples(buffer);
	}
}


void munger_poststate(t_munger *x, t_symbol *s, long argc, t_atom *argv) {

	post (">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
	post ("***CURRENT MUNGER PARAMETER VALUES***:");
	post ("all times in milliseconds");
	post ("grain spacing = %f", x->grate);	
    post ("grain spacing variation = %f", x->grate_var);
    post ("grain length = %f", x->glen);
    post ("grain length variation = %f", x->glen_var);				 
    post ("grain transposition multiplier = %f", x->gpitch);
    post ("grain transposition multiplier variation = %f", x->gpitch_var);
    post ("panning spread = %f", x->gpan_spread);
	post ("grain gain = %f", x->gain);
	post ("grain gain variation = %f", x->randgain);
	post ("playback position (-1 = random) = %f", x->position);
	post ("grain playback direction (0 = both) = %d", x->ambi);
	post ("buffer length = %f", x->buflen * x->one_over_srate_ms);
	post ("max grain size = %f", x->maxsize * x->one_over_srate_ms);
	post ("min grain size = %f", x->minsize * x->one_over_srate_ms);
	post ("max number of voices = %ld", x->maxvoices);
	post ("current number of voices = %d", x->voices);
	post ("grain envelope (ramp) length = %f", x->rampLength * x->one_over_srate_ms);
	post ("recording? = %d", x->recordOn);
	post ("power = %d", x->power);
	post ("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    
}