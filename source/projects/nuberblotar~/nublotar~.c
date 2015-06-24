//extension of the blotar~ to include 6 strings and pre/post distortion outputs, 
//more plucking options; closer to the Sullivan electric guitar model, while
//retaining some of the flute potentials of the blotar~
//
//dt 2004; yet another PeRColate hack
//
// updated for Max 7 by Darwin Grosse and Tim Place
// -------------------------------------------------

//messages: 	  pluck string amp position;
//		    	  vibfreq string frequency; vibamp string value;
//				  breathpressure string value;
//			      setfreq string frequency;
//				  setsustain string value;
//				  lowpasscross string;
//				  feedfreq frequency;
//				  feedgain value;
//				  distortgain value;
//signal inputs:  pre-distortion output gain;
//				  post-distortion output gain;

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "ext_strings.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "stk_c.h" 

#include "Dunlap12.lpc.h"
#include "Fiddle12.lpc.h"
#include "Mando12.lpc.h"
#include "Violin12.lpc.h"
#include "Arch12.lpc.h"
#include "Abreu12.lpc.h" 
#define ORDER 12 
 
#define GUITAR1 1
#define GUITAR2 2
#define VIOLIN 3
#define MANDOLIN 4
#define HARDANGER 5
#define ARCHTOP 6

#define LENGTH 2048 			//44100/LOWFREQ + 1 --blotar length
#define JETLENGTH LENGTH * 2 	//larger, for big rooms
#define VIBLENGTH 1024
#define NUM_STRINGS 6
//why 6? because it's half of 12. and because it's how many fingers you have.
#define ONE_OVER_NUMSTRINGS 0.1666666666666667

#define MAX_INPUTS 10 	//arbitrary
#define MAX_OUTPUTS 10	//also arbitrary

t_class *nublotar_class;

typedef struct _blostring
{
    //bore-string delay line
    DLineL boreDelay;
    float last_output;
    float lastFreq, lastLength;
    
    //DC blocker
    DCBlock killdc;

    //filters    
    OnePole flute_filter;
    OneZero lowpass; 
    
    //vibrato
    float vibTime, vibRate;
    
    //main control variables
    float fr;			//frequency	    
    float bp;			//breath pressure	
    float ng; 			//noise gain
    float vf; 			//vib freq
    float va; 			//vib amount
    float er;			//end reflection coefficient (string sustain)
    float pluckAmp;		//pluck amplitude
    float pluckPos;		//pluck position
    float pluckWidth;	//pluck width
    long squish;		//how much to squish the pluck
    float filterRatio, filterRatioInv;	//OneZero vs. OnePole filter ratio
    short resetDelay;

} BloString;

typedef struct _nublotar
{
	//header
    t_pxobject x_obj;
    
    //variables specific to this object
    float srate, one_over_srate;  	//sample rate vars
    long num_inputs, num_outputs; 	//number of inputs and outputs
    double in[MAX_INPUTS];			//values of input variables
    float in_connected[MAX_INPUTS]; //booleans: true if signals connected to the input in question
    //we use this "connected" boolean so that users can connect *either* signals or floats
    //to the various inputs; sometimes it's easier just to have floats, but other times
    //it's essential to have signals.... but we have to know. 
    
    short power; //to bypass the instrument
    
    //user controlled vars
    float x_jd;							//jet frequency
    float x_jr;							//pre-feedback gain (jet reflection coeff)
    float predistortion_gain;			//pre-distortion gain
    float predistortion_outgain;
    float postdistortion_outgain;
    
    //the string/bore
    BloString blo_string[NUM_STRINGS];
    float last_output;
    float limit; //limit amp for strings/bores
    //vibrato table
    float vibTable[VIBLENGTH];
   
    DCBlock pluckblock;
    
    //feedback/jet delayline
    DLineL jetDelay;
    short resetJetDelay;
    
    //nbody vars
    short instrument;
    short direction;
    //nbody allpole vars
    float poleCoeffs[ORDER];
    float ap_outputs[ORDER];
    float ap_gain;    
    //nbody onezero vars
    float zeroCoeff;
    float sgain;
    float oz_gain;
    float oz_input;
    
} t_nublotar;


/****PROTOTYPES****/

//setup funcs; this probably won't change, unless you decide to change the number of
//args that the user can input, in which case nublotar_new will have to change
void *nublotar_new(long num_inputs, long num_outputs);
void nublotar_free(t_nublotar *x);
void nublotar_assist(t_nublotar *x, void *b, long m, long a, char *s);

// dsp stuff
void nublotar_dsp64(t_nublotar *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void nublotar_perform64(t_nublotar *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

//for getting floats at inputs
void nublotar_float(t_nublotar *x, double f);
void nublotar_setpower(t_nublotar *x, t_symbol *s, long argc, t_atom *argv);

//message prototypes
void nublotar_pluck(t_nublotar *x, t_symbol *s, long argc, t_atom *argv);
void nublotar_vib(t_nublotar *x, t_symbol *s, long argc, t_atom *argv);
void nublotar_breathpressure(t_nublotar *x, t_symbol *s, long argc, t_atom *argv);
void nublotar_noisegain(t_nublotar *x, t_symbol *s, long argc, t_atom *argv);
void nublotar_setlimit(t_nublotar *x, t_symbol *s, long argc, t_atom *argv);
void nublotar_setsustain(t_nublotar *x, t_symbol *s, long argc, t_atom *argv);
void nublotar_lowpasscross(t_nublotar *x, t_symbol *s, long argc, t_atom *argv);
void nublotar_feedfreq(t_nublotar *x, t_symbol *s, long argc, t_atom *argv);
void nublotar_feedgain(t_nublotar *x, t_symbol *s, long argc, t_atom *argv);
void nublotar_distortgain(t_nublotar *x, t_symbol *s, long argc, t_atom *argv);

//string-bore functions
float blostring_tick(t_nublotar *x, BloString *blostring, float sample);
float vib_tick(t_nublotar *x, BloString *blostring);
void setVibFreq(t_nublotar *x, BloString *blostring, float freq);
void setFreq(t_nublotar *x, BloString *blostring, float frequency);
void dopluck(t_nublotar *x, BloString *blostring, float amp, float position, float width);
void pluck_squish(t_nublotar *x, BloString *blostring);

void setJetDelay(t_nublotar *x, float frequency);

//nbody funcs
void nbody_guitar1(t_nublotar *x, double f);
void nbody_guitar2(t_nublotar *x, double f);
void nbody_mandolin(t_nublotar *x, double f);
void nbody_violin(t_nublotar *x, double f);
void nbody_hardanger(t_nublotar *x, double f);
void nbody_archtop(t_nublotar *x, double f);
void nbody_int(t_nublotar *x, int f);

void nbody_setup(t_nublotar *x);
float nbody_tick(t_nublotar *x);

//allpole funcs
void setPoleCoeffs(t_nublotar *x, float *coeffs);
float ap_tick(t_nublotar *x, float sample);

//onezero funcs
void setOneZeroCoeff(t_nublotar *x, float aValue);
float oz_tick(t_nublotar *x, float sample);


/****FUNCTIONS****/

//string-bore functions
float blostring_tick(t_nublotar *x, BloString *blostring, float sample)  
{

	float temp, tempsave;
	
	temp = DLineL_tick(&blostring->boreDelay, sample + blostring->er * blostring->last_output);
	/*
	randPressure  = blostring->ng * Noise_tick();
	randPressure += blostring->va * vib_tick(x, blostring);
	randPressure *= blostring->bp;	
	*/	

	//balance OnePole (flute) with LowPass (Karplus Strong); total wacko hack, but sounds cool
	tempsave = temp;
	temp = OnePole_tick(&blostring->flute_filter, temp);
	temp = blostring->filterRatio * temp +
		   blostring->filterRatioInv * 
		   OneZero_tick(&blostring->lowpass, tempsave);

	//kill the DC component
	temp = DCBlock_tick(&blostring->killdc, temp);
	
	//limit the output
	if (temp > x->limit || temp < -x->limit) temp = 0.;
	
	//byebye
	return blostring->last_output = temp;

}

void setVibFreq(t_nublotar *x, BloString *blostring, float freq)
{
	blostring->vibRate = VIBLENGTH * x->one_over_srate * freq;
}

float vib_tick(t_nublotar *x, BloString *blostring)
{
	long temp;
	float temp_time, alpha, output;
	
	blostring->vibTime += blostring->vibRate;
	while (blostring->vibTime >= (float)VIBLENGTH) blostring->vibTime -= (float)VIBLENGTH;
	while (blostring->vibTime < 0.) blostring->vibTime += (float)VIBLENGTH;
	
	temp_time = blostring->vibTime;
	
	temp = (long) temp_time;
	alpha = temp_time - (float)temp;
	output = x->vibTable[temp];
	output = output + (alpha * (x->vibTable[temp+1] - output));
	return output;
}

#define WATCHIT 0.00001
void setFreq(t_nublotar *x, BloString *blostring, float frequency)
{
  float temp;
  if(frequency < 20.) frequency = 20.;
  blostring->lastFreq = frequency;
  blostring->lastLength = x->srate / blostring->lastFreq;        /* length - delays */
  /*
  if (x->detuning != 0.) {
  	DLineA_setDelay(&x->delayLine, (x->lastLength / x->detuning) - .5);
  	DLineA_setDelay(&x->delayLine2, (x->lastLength * x->detuning) - .5);
  }
  x->loopGain = x->baseLoopGain + (frequency * 0.000005);
  if (x->loopGain>1.0) x->loopGain = 0.99999;
  */
  blostring->lastFreq = frequency * 0.66666;
  if(blostring->lastFreq < WATCHIT) blostring->lastFreq = WATCHIT;
  temp = (x->srate / blostring->lastFreq) - 2.;
  DLineL_setDelay(&blostring->boreDelay, temp);
}

void dopluck(t_nublotar *x, BloString *blostring, float amp, float position, float width)
{
	blostring->pluckAmp = amp;
	blostring->pluckPos = blostring->squish = position;
	blostring->pluckWidth = width;
	//post("plucking with amp %f, position %f, width %f", amp, position, width);
}

//string-bore functions
void pluck_squish(t_nublotar *x, BloString *blostring)  
{

   	int i,j,p1,p2, len;
   	float mult;

	/* Low- pass filters vales of string, squish times. */
	/* Compensates for loss of level at fundamental, but not for overall loss. */
	len = blostring->boreDelay.length;
	p1 = blostring->boreDelay.inputs[len-1];
	p2 = blostring->boreDelay.inputs[len-2]; 

	mult = fabs(1./( 2.*cos((double)TWO_PI/len) + 1.));

	for(j=0; j<blostring->squish; j++){
	    
	   for(i=0;i<len;i++) {
	       blostring->boreDelay.inputs[i] = mult*(blostring->boreDelay.inputs[p2]+blostring->boreDelay.inputs[i]+blostring->boreDelay.inputs[p1]);
	       p2 = p1;
	       p1 = i;
	   }
	 }
}

void setJetDelay(t_nublotar *x, float frequency)
{
	float temp;
	if(frequency < WATCHIT) frequency = WATCHIT;
	temp = (x->srate / frequency) - 2.;
	
	x->x_jd = temp;
	
	//control jet length directly, not as function of bore length
	DLineL_setDelay(&x->jetDelay, temp);
}	


//nbody funcs
void setOneZeroCoeff(t_nublotar *x, float aValue)
{
	x->zeroCoeff = aValue;
    if (x->zeroCoeff > 0.0)                  /*  Normalize gain to 1.0 max  */
        x->sgain = x->oz_gain / ((float) 1.0 + x->zeroCoeff);
    else
        x->sgain = x->oz_gain / ((float) 1.0 - x->zeroCoeff);

}

float oz_tick(t_nublotar *x, float sample)
{
	float temp, outsamp;
    temp = x->sgain * sample;
    outsamp = (x->oz_input * x->zeroCoeff) + temp;
    x->oz_input = temp;
    return outsamp;

}

void setPoleCoeffs(t_nublotar *x, float *coeffs)
{
	int i;
	for(i=0; i<ORDER; i++) {
		x->poleCoeffs[i] = coeffs[i];
	}
}

float ap_tick(t_nublotar *x, float sample)
{
	int i;
    float temp;                          

    temp = sample * x->ap_gain;             

    for (i=ORDER-1;i>0;i--)	{
		temp -= x->ap_outputs[i] * x->poleCoeffs[i]; 
		x->ap_outputs[i] = x->ap_outputs[i-1];
    }
    temp -= x->ap_outputs[0] * x->poleCoeffs[0]; 
    x->ap_outputs[0] = temp;

    return temp;
}

void nbody_setup(t_nublotar *x) {
  
}

float nbody_tick(t_nublotar *x) {
    return 0.0;
}


//primary MSP funcs
void ext_main(void* p)
{
    t_class *c = class_new("nublotar~", (method)nublotar_new, (method)nublotar_free, (long)sizeof(t_nublotar), 0L, A_DEFLONG, A_DEFLONG, 0);
    
    class_addmethod(c, (method)nublotar_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)nublotar_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)nublotar_float, "float", A_FLOAT, 0);
    class_addmethod(c, (method)nbody_int, "int", A_LONG, 0);

    //messages: 	  pluck string amp position;
	//		    	  vibfreq string frequency; vibamp string value;
	//				  breathpressure string value;
	//			      setfreq string frequency;
	//				  setsustain string value;
	//				  lowpasscross string;
	//				  feedfreq frequency;
	//				  feedgain value;
	//				  distortgain value;
    class_addmethod(c, (method)nublotar_pluck, 			"pluck", A_GIMME, 0);
    class_addmethod(c, (method)nublotar_vib, 			"vibrato", A_GIMME, 0);
    //class_addmethod(c, (method)nublotar_breathpressure, "breathpressure", A_GIMME, 0);
    class_addmethod(c, (method)nublotar_noisegain, 		"noise", A_GIMME, 0);
    class_addmethod(c, (method)nublotar_setlimit, 		"limit", A_GIMME, 0);
    class_addmethod(c, (method)nublotar_setsustain, 	"setsustain", A_GIMME, 0);
    class_addmethod(c, (method)nublotar_lowpasscross, 	"lowpasscross", A_GIMME, 0);
    //class_addmethod(c, (method)nublotar_feedfreq, 		"feedfreq", A_GIMME, 0);
    class_addmethod(c, (method)nublotar_feedgain, 		"feedgain", A_GIMME, 0);
    class_addmethod(c, (method)nublotar_distortgain, 	"distortgain", A_GIMME, 0);
    class_addmethod(c, (method)nublotar_setpower, 		"power", A_GIMME, 0);
    
    //nbody messeages
    class_addmethod(c, (method)nbody_guitar1, "guitar1", A_GIMME, 0);
    class_addmethod(c, (method)nbody_guitar2, "guitar2", A_GIMME, 0);
    class_addmethod(c, (method)nbody_mandolin, "mandolin", A_GIMME, 0);
    class_addmethod(c, (method)nbody_violin, "violin", A_GIMME, 0);
    class_addmethod(c, (method)nbody_hardanger, "hardanger", A_GIMME, 0);
    class_addmethod(c, (method)nbody_archtop, "archtop", A_GIMME, 0);
    
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    nublotar_class = c;
}

//this gets called when the object is created; everytime the user types in new args, this will get called
void *nublotar_new(long num_inputs, long num_outputs)
{
	int i;
	
	//leave this; creates our object
    t_nublotar *x = (t_nublotar *)object_alloc(nublotar_class);
    
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_nublotar);i++)  
                ((char *)x)[i]=0; 
	} 
	
	//constrain number of inputs and outputs
	//could also just define these internally, and not have user control via arguments....
	if (num_inputs < 1) num_inputs = 1;
	if (num_inputs > MAX_INPUTS) num_inputs = 1;
	if (num_outputs < 1) num_outputs = 1;
	if (num_outputs > MAX_OUTPUTS) num_outputs = 1;
	
	//obviously, you could ignore the user args if you don't want them to control
	//the number of ins/outs, and just set them here.
	//x->num_inputs = num_inputs;
	x->num_inputs = 10; //freqs 1-6, feedback freq, pre and post distortion gains, breathpressure, input source
	x->num_outputs = 1; //only need one output for the nublotar

	//setup inputs and outputs, for audio
	
	//inputs
    dsp_setup((t_pxobject *)x, x->num_inputs);
    //if you just need one input for message (not using audio), you can just set num_inputs = 1
    //i don't think this causes a performance hit.
    
    //outputs
    for (i=0;i<x->num_outputs;i++) {
    	outlet_new((t_object *)x, "signal");
    }   
    
    //initialize some variables; important to do this!
    for (i=0;i<x->num_inputs;i++){
    	x->in[i] = 0.;
    	x->in_connected[i] = 0;
    }
    
    x->srate = 44100.;
    x->one_over_srate = 1./x->srate;
  
    for (i=0;i<NUM_STRINGS;i++) {
	    DLineL_alloc(&x->blo_string[i].boreDelay, LENGTH);
	    DLineL_clear(&x->blo_string[i].boreDelay);
	    OnePole_init(&x->blo_string[i].flute_filter);
    	OneZero_init(&x->blo_string[i].lowpass);
    	setFreq(x, &x->blo_string[i], 100*(i+1));    
    	OnePole_setPole(&x->blo_string[i].flute_filter, 0.7 - (0.1 * 22050. / x->srate));
    	OnePole_setGain(&x->blo_string[i].flute_filter, -1.);
    	x->blo_string[i].last_output = 0.;
    	x->blo_string[i].lastLength = 0.;
    	x->blo_string[i].lastFreq = 100.*(i+1);
    	x->blo_string[i].vibTime = 0.;
    	x->blo_string[i].vibRate = 0.;
    	x->blo_string[i].fr = 100.*(i+1);
    	x->blo_string[i].bp = 0.;
    	x->blo_string[i].ng = 0.;
    	x->blo_string[i].vf = 0.;
    	x->blo_string[i].va = 0.;
    	x->blo_string[i].er = 0.;
    	x->blo_string[i].filterRatio = 1.;
    	x->blo_string[i].filterRatioInv = 0.;
    	x->blo_string[i].pluckAmp = 0.;
    	x->blo_string[i].pluckPos = 0.;
    }
    
    DLineL_alloc(&x->jetDelay, JETLENGTH); //longer here, for long feedback loops, big rooms
    DLineL_clear(&x->jetDelay);
    DLineL_setDelay(&x->jetDelay, 49.);
    
    x->power = 1;
    for(i=0; i<VIBLENGTH; i++) x->vibTable[i] = sin(i*TWO_PI/VIBLENGTH);
    
    x->x_jd = 49.;
    x->x_jr = 0.;
    x->predistortion_gain = 1.;
    x->predistortion_outgain = 0.;
    x->postdistortion_outgain = 1.;
    x->limit = 10.;
    
     //allpole init
    for (i=0;i<ORDER;i++) x->ap_outputs[i] = (float) 0.0;
    x->ap_gain = 1.;
    
    //onezero init
    x->zeroCoeff = 1.;
    x->sgain = .5;
    x->oz_gain = 1.;
    x->oz_input = 0.;
 
 	x->instrument = GUITAR1;
 	x->direction = 1;
 	nbody_guitar1(x, 0.);
    
	//occasionally this line is necessary if you are doing weird asynchronous things with the in/out vectors
	//x->x_obj.z_misc = Z_NO_INPLACE;

    return (x);
}


//this gets called when an object is destroyed. do stuff here if you need to clean up.
void nublotar_free(t_nublotar *x)
{
	//gotta call this one
	int i;
	
	for(i=0;i<NUM_STRINGS;i++) {
		DLineL_free(&x->blo_string[i].boreDelay);
	}
	DLineL_free(&x->jetDelay);
	dsp_free((t_pxobject *)x);
}

//tells the user about the inputs/outputs when mousing over them
void nublotar_assist(t_nublotar *x, void *b, long m, long a, char *s)
{
	int i;
	//could use switch/case inside for loops, to give more informative assist info....
	if (m==1) {
		if (a==0)  sprintf(s, "input %ld: string/bore 1 frequency", a);
		if (a==1)  sprintf(s, "input %ld: string/bore 2 frequency", a);
		if (a==2)  sprintf(s, "input %ld: string/bore 3 frequency", a);
		if (a==3)  sprintf(s, "input %ld: string/bore 4 frequency", a);
		if (a==4)  sprintf(s, "input %ld: string/bore 5 frequency", a);
		if (a==5)  sprintf(s, "input %ld: string/bore 6 frequency", a);
		if (a==6)  sprintf(s, "input %ld: feedback/jet frequency", a);
		if (a==7)  sprintf(s, "input %ld: predistortion output level", a);
		if (a==8)  sprintf(s, "input %ld: postdistortion output level", a);
		if (a==9)  sprintf(s, "input %ld: breath pressure", a);
		if (a==10)  sprintf(s, "input %ld: input signal", a);
        
	}
	if (m==2) {
		for(i=0;i<x->num_outputs;i++)
			if (a==i)  sprintf(s, "output mix");
	}
}

//this gets called when ever a float is received at *any* input
void nublotar_float(t_nublotar *x, double f)
{
	int i;
	
	//check to see which input the float came in, then set the appropriate variable value
	for(i=0;i<x->num_inputs;i++) {
		if (x->x_obj.z_in == i) {
			x->in[i] = f;
			//post("nublotar~: setting in[%d] =  %f", i, f);
		}
	}
}

//messages
//				  pluck string amp position;
void nublotar_pluck(t_nublotar *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp[10], amp, position, width;
	short stringtopluck;
	if (argc>10) argc = 10;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp[i] = (float)argv[i].a_w.w_long;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
			case A_FLOAT:
				temp[i] = argv[i].a_w.w_float;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
		}
	}
	
	if (argc < 3) temp[2] = temp[3] = -1.;
	
	stringtopluck = (short)temp[0];
	amp = temp[1];
	position = temp[2];
	width = temp[3];
	dopluck(x, &x->blo_string[stringtopluck], amp, position, width);
    
}

//		    	  vib string frequency amp;
void nublotar_vib(t_nublotar *x, t_symbol *s, long argc, t_atom *argv)
{
    
	short i;
	float temp[10], freq;
	if (argc>10) argc = 10;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp[i] = (float)argv[i].a_w.w_long;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
			case A_FLOAT:
				temp[i] = argv[i].a_w.w_float;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
		}
	}
	
	//string = (short)temp[0];
	freq = temp[0];
	x->blo_string[0].va = temp[1];
	setVibFreq(x, &x->blo_string[0], freq);
    
}

//				  breathpressure string value;
void nublotar_breathpressure(t_nublotar *x, t_symbol *s, long argc, t_atom *argv)
{
    
	short i;
	float temp[10];
	if (argc>10) argc = 10;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp[i] = (float)argv[i].a_w.w_long;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
			case A_FLOAT:
				temp[i] = argv[i].a_w.w_float;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
		}
	}
	
	//need to set this up so that string = -1 will set *all* string vals
	//string = (short)temp[0];
	x->blo_string[0].bp = temp[0];
	//post("bp = %f", x->blo_string[0].bp);
	
}

void nublotar_noisegain(t_nublotar *x, t_symbol *s, long argc, t_atom *argv)
{
    
	short i;
	float temp[10];
	if (argc>10) argc = 10;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp[i] = (float)argv[i].a_w.w_long;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
			case A_FLOAT:
				temp[i] = argv[i].a_w.w_float;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
		}
	}
	
	//need to set this up so that string = -1 will set *all* string vals
	//string = (short)temp[0];
	x->blo_string[0].ng = temp[0];
	//post("ng = %f",  x->blo_string[0].ng);
	
}

//			      setfreq string frequency;
void nublotar_setlimit(t_nublotar *x, t_symbol *s, long argc, t_atom *argv)
{
    
	short i;
	float temp[10];
	if (argc>10) argc = 10;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp[i] = (float)argv[i].a_w.w_long;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
			case A_FLOAT:
				temp[i] = argv[i].a_w.w_float;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
		}
	}
	
	x->limit = temp[0];
    
}

//				  setsustain string value;
void nublotar_setsustain(t_nublotar *x, t_symbol *s, long argc, t_atom *argv)
{
    
	short i;
	float temp[10];
	short string;
	if (argc>10) argc = 10;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp[i] = (float)argv[i].a_w.w_long;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
			case A_FLOAT:
				temp[i] = argv[i].a_w.w_float;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
		}
	}
	
	string = (short)temp[0];
	if(string >=0) x->blo_string[string].er = temp[1];
	else for(i=0;i<NUM_STRINGS;i++) {
		x->blo_string[i].er = temp[1];
	}
    
}

//				  lowpasscross string;
void nublotar_lowpasscross(t_nublotar *x, t_symbol *s, long argc, t_atom *argv)
{
    
	short i;
	float temp[10];
	short string;
	if (argc>10) argc = 10;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp[i] = (float)argv[i].a_w.w_long;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
			case A_FLOAT:
				temp[i] = argv[i].a_w.w_float;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
		}
	}
	
	string = (short)temp[0];
	if(string >=0) {
		x->blo_string[string].filterRatio = temp[1];
		x->blo_string[string].filterRatioInv = 1. - temp[1];
	} else for(i=0;i<NUM_STRINGS;i++) {
		x->blo_string[i].filterRatio = temp[1];
		x->blo_string[i].filterRatioInv = 1. - temp[1];
	}
    
}

//				  feedfreq frequency
void nublotar_feedfreq(t_nublotar *x, t_symbol *s, long argc, t_atom *argv)
{
    
	short i;
	float temp[10];
	if (argc>10) argc = 10;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp[i] = (float)argv[i].a_w.w_long;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
			case A_FLOAT:
				temp[i] = argv[i].a_w.w_float;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
		}
	}
	
	x->resetJetDelay = 1;
	x->x_jd = temp[0];
	
}

//				  feedgain value;
void nublotar_feedgain(t_nublotar *x, t_symbol *s, long argc, t_atom *argv)
{
    
	short i;
	float temp[10];
	if (argc>10) argc = 10;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp[i] = (float)argv[i].a_w.w_long;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
			case A_FLOAT:
				temp[i] = argv[i].a_w.w_float;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
		}
	}
    
	x->x_jr = temp[0];
	//post ("x_jr = %f", x->x_jr);
    
}

//				  distortgain value;
void nublotar_distortgain(t_nublotar *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp[10];
	if (argc>10) argc = 10;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp[i] = (float)argv[i].a_w.w_long;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
			case A_FLOAT:
				temp[i] = argv[i].a_w.w_float;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
		}
	}
	
	x->predistortion_gain = temp[0];
	//post("predistortion_gain set to %f", x->predistortion_gain);
    
    
}

void nublotar_setpower(t_nublotar *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp[10];
	if (argc>10) argc = 10;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp[i] = (float)argv[i].a_w.w_long;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
			case A_FLOAT:
				temp[i] = argv[i].a_w.w_float;
    			//post("nublotar: received argument %d of mymessage with value %f", i+1, temp[i]);
				break;
		}
	}
	
	x->power = (short)temp[0];
	post("nublotar: power = %d", x->power);
}

void nbody_guitar1(t_nublotar *x, double f)
{
	x->instrument = GUITAR1;
	x->ap_gain = (0.07*abreuGains[abreuMap[x->direction]]);
	setPoleCoeffs(x, abreu_coeffs[abreuMap[x->direction]]);
	setOneZeroCoeff(x, abreuZero);
}

void nbody_guitar2(t_nublotar *x, double f)
{
	x->instrument = GUITAR2;
	x->ap_gain = (0.07*dunlapGains[dunlapMap[x->direction]]);
	setPoleCoeffs(x, dunlap_coeffs[dunlapMap[x->direction]]);
	setOneZeroCoeff(x, dunlapZero);
}

void nbody_mandolin(t_nublotar *x, double f)
{
	x->instrument = MANDOLIN;
	x->ap_gain = (0.1*mandoGains[mandoMap[x->direction]]);
	setPoleCoeffs(x, mando_coeffs[mandoMap[x->direction]]);
	setOneZeroCoeff(x, mandoZero);
}

void nbody_violin(t_nublotar *x, double f)
{
	x->instrument = VIOLIN;
	x->ap_gain = (0.2*violinGains[violinMap[x->direction]]);
	setPoleCoeffs(x, violin_coeffs[violinMap[x->direction]]);
	setOneZeroCoeff(x, violinZero);
}

void nbody_hardanger(t_nublotar *x, double f)
{
	x->instrument = HARDANGER;
	x->ap_gain = (fiddleGain*fiddleGains[fiddleMap[x->direction]]);
	setPoleCoeffs(x, fiddle_coeffs[fiddleMap[x->direction]]);
	setOneZeroCoeff(x, fiddleZero);
}

void nbody_archtop(t_nublotar *x, double f)
{
	x->instrument = ARCHTOP;
	x->ap_gain = (0.07*archGains[archMap[x->direction]]);
	setPoleCoeffs(x, arch_coeffs[archMap[x->direction]]);
	setOneZeroCoeff(x, archZero);
}


void nbody_int(t_nublotar *x, int f)
{
	if(f > 12) {
		f = 12;
	}
	
	if(f < 1) {
		x->direction = -1;
		post("nublotar: nbody filter bypassed");
	} else {
		post("nublotar: changing filter to %d", f);
        
		f--;
		x->direction = f;
		
		if (x->instrument == GUITAR1) nbody_guitar1(x, 0.);
		if (x->instrument == GUITAR2) nbody_guitar2(x, 0.);
		if (x->instrument == VIOLIN) nbody_violin(x, 0.);
		if (x->instrument == HARDANGER) nbody_hardanger(x, 0.);
		if (x->instrument == MANDOLIN) nbody_mandolin(x, 0.);
		if (x->instrument == ARCHTOP) nbody_archtop(x, 0.);
	}
}


void nublotar_dsp64(t_nublotar *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	int i;
    
	//set sample rate vars
	x->srate = samplerate;
	x->one_over_srate = 1./x->srate;
	
	//check to see if there are signals connected to the various inputs
	for(i=0;i<x->num_inputs;i++) x->in_connected[i]	= count[i];
    object_method(dsp64, gensym("dsp_add64"), x, nublotar_perform64, 0, NULL);
}



void nublotar_perform64(t_nublotar *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double *in[MAX_INPUTS]; 		//pointers to the input vectors
	t_double *out[MAX_OUTPUTS];	//pointers to the output vectors

	long n = sampleframes;	//number of samples per vector
	
	//random local vars
	long i, j;
	t_double inputs[MAX_INPUTS];
	t_double string_bore_output, distortion_output, temp, pressureDiff, randPressure;
	t_double fr[NUM_STRINGS], jd;
	
	if (x->x_obj.z_disabled || !x->power) return;
	
	//check to see if we have a signal or float message connected to input
	//then assign the pointer accordingly
	for (i=0;i<x->num_inputs;i++) {
		in[i] = x->in_connected[i] ? (t_double *)(ins[i]) : &x->in[i];
	}
	
	//assign the output vectors
	for (i=0;i<x->num_outputs;i++) {
		out[i] = (t_double *)(outs[i]);
	}
	
	for(j=0;j<NUM_STRINGS;j++) {
		if (x->blo_string[j].pluckAmp > 0.) {
			if(x->blo_string[j].pluckPos < 0.) {
				//load with noise
				for (i=0;i<x->blo_string[j].boreDelay.length;i++) {
					x->blo_string[j].boreDelay.inputs[i] = Noise_tick() * x->blo_string[j].pluckAmp;
				}
			} else {
				//load with noise
				for (i=0;i<x->blo_string[j].boreDelay.length;i++) {
					x->blo_string[j].boreDelay.inputs[i] = DCBlock_tick(&x->pluckblock, Noise_tick() * x->blo_string[j].pluckAmp);
				}
				//lowpass a few times; isn't this just wildly brilliant?
				pluck_squish(x, &x->blo_string[j]);
			}
			x->blo_string[j].pluckAmp = 0.;
		}
	}
	
	while(n--) {
		
		//grab the inputs; ok, this isn't the most efficient way to do this, but what the hell....
		for(i=0;i<x->num_inputs;i++)
			if(x->in_connected[i]) inputs[i] = *in[i]++; //use and increment the signal vector if there is one
			else inputs[i] += *in[i];					 //otherwise use the global variable
		
		//set variables
		jd						  = inputs[NUM_STRINGS];
		x->predistortion_outgain  = inputs[NUM_STRINGS+1];
		x->postdistortion_outgain = inputs[NUM_STRINGS+2];
		x->blo_string[0].bp		  = inputs[NUM_STRINGS+3];
		//inPressure				  = inputs[NUM_STRINGS+4];
		
		//blowing; this could probably be done on each string individually.... but maybe not.
		randPressure  = x->blo_string[0].ng * Noise_tick();
		randPressure += x->blo_string[0].va * vib_tick(x, &x->blo_string[0]);
		randPressure *= x->blo_string[0].bp;
		
		//set string frequencies, if necessary, and then sum their outputs
		string_bore_output = 0.;
		for(i=0;i<NUM_STRINGS;i++) {
			fr[i] = inputs[i];
			if(fr[i] != x->blo_string[i].fr) {
				setFreq(x, &x->blo_string[i], fr[i]);
				x->blo_string[i].fr = fr[i];
			}
			string_bore_output += blostring_tick(x, &x->blo_string[i], x->x_jr * x->last_output);
		}
		
		
		//do nbody filter
		if(x->direction > -1) {
			string_bore_output = oz_tick(x, string_bore_output);
			string_bore_output = ap_tick(x, string_bore_output);
		}
		
		
		//calculate pressure difference
		//pressureDiff = x->blo_string[0].bp + randPressure + inPressure - string_bore_output*ONE_OVER_NUMSTRINGS;	
		pressureDiff = x->blo_string[0].bp + randPressure - string_bore_output*ONE_OVER_NUMSTRINGS;

		//reset the feedback delay time, if necessary
		if(jd != x->x_jd) {
			setJetDelay(x, jd);
			x->x_jd = jd;
		}
		
		//feedback delay line
		temp = DLineL_tick(&x->jetDelay, pressureDiff);
		
		//distortion
		distortion_output = x->last_output = JetTabl_lookup(x->predistortion_gain*temp);
		
		//send it all out
		*out[0]++ =  x->predistortion_outgain*string_bore_output + x->postdistortion_outgain*distortion_output;
	}
}	


