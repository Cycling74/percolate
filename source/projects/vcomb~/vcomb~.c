//this one is inspired by John Gibson's "spectacle" instrument in rtcmix
//each bin gets its own feedback delay line (comb filter)
//user controls both feedback time and feedback coefficient.
//non-interpolating, to keep it relatively CPU efficient
//
//dt 2004; yet another PeRColate hack
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "ext_strings.h"
#include "stk_c.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUTS 10 	//arbitrary
#define MAX_OUTPUTS 10	//also arbitrary
#define MAX_BINS 4096	//assume a max window size of 8192
#define MAX_DELAY 1000

t_class *vcomb_class;

typedef struct _vcomb
{
	//header
    t_pxobject x_obj;
    
    //variables specific to this object
    float srate, one_over_srate;  	//sample rate vars
    long num_inputs, num_outputs; 	//number of inputs and outputs
    t_double in[MAX_INPUTS];			//values of input variables
    float in_connected[MAX_INPUTS]; //booleans: true if signals connected to the input in question
    //we use this "connected" boolean so that users can connect *either* signals or floats
    //to the various inputs; sometimes it's easier just to have floats, but other times
    //it's essential to have signals.... but we have to know. 
    
    short power;					//i like objects, especially CPU intensive ones, to have their own
    								//"power" messages so that you can bypass them individually
    
    float *bin1delays[MAX_DELAY];
    float *bin2delays[MAX_DELAY];

    
    float *last_output1, *last_output2;
    long  *delaytime;
    long  *inPoint, *outPoint;
    
} t_vcomb;


/****PROTOTYPES****/

//setup funcs; this probably won't change, unless you decide to change the number of
//args that the user can input, in which case vcomb_new will have to change
void *vcomb_new(long num_inputs, long num_outputs);
void vcomb_free(t_vcomb *x);
void vcomb_assist(t_vcomb *x, void *b, long m, long a, char *s);

// dsp stuff
void vcomb_dsp64(t_vcomb *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void vcomb_perform64(t_vcomb *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

//for getting floats at inputs
void vcomb_float(t_vcomb *x, double f);
void dline_setDelay(t_vcomb *x, long whichLine, long lag);
void dline_tick(t_vcomb *x, long whichLine, t_double *samples);

//for custom messages
void vcomb_mymessage(t_vcomb *x, t_symbol *s, long argc, t_atom *argv);
void vcomb_setpower(t_vcomb *x, t_symbol *s, long argc, t_atom *argv);


/****FUNCTIONS****/

void dline_setDelay(t_vcomb *x, long whichLine, long lag)
{
  if (lag > MAX_DELAY - 1) {                   						  // if delay is too big,
    x->outPoint[whichLine] = x->inPoint[whichLine] + 1;               // force delay to max_length
  }
  else 
    x->outPoint[whichLine] = x->inPoint[whichLine] - lag;      			// read chases write
  while (x->outPoint[whichLine]<0) x->outPoint[whichLine] += x->delaytime[whichLine];  	// modulo maximum length
}

void dline_tick(t_vcomb *x, long whichLine, t_double *samples)        			// Take two, yield two
{
  x->bin1delays[x->inPoint[whichLine]   ][whichLine] = samples[0];
  x->bin2delays[x->inPoint[whichLine]++ ][whichLine] = samples[1];
  if (x->inPoint[whichLine] >= MAX_DELAY)                 	// Check for end condition
      x->inPoint[whichLine] -= MAX_DELAY;
      
  samples[0] = x->bin1delays[x->outPoint[whichLine]   ][whichLine];          	// Read out next value
  samples[1] = x->bin2delays[x->outPoint[whichLine]++ ][whichLine];         	// Read out next value
  if (x->outPoint[whichLine] >= MAX_DELAY)       				// Check for end condition
      x->outPoint[whichLine] -= MAX_DELAY;                             
}



//primary MSP funcs
void ext_main(void* p)
{
    t_class *c = class_new("vcomb~", (method)vcomb_new, (method)vcomb_free, (long)sizeof(t_vcomb), 0L, A_DEFLONG, A_DEFLONG, 0);
    
    class_addmethod(c, (method)vcomb_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)vcomb_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)vcomb_mymessage, "mymessage", A_GIMME, 0);
    class_addmethod(c, (method)vcomb_setpower, "power", A_GIMME, 0);
    class_addmethod(c, (method)vcomb_float, "float", A_FLOAT, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    vcomb_class = c;
}

//this gets called when the object is created; everytime the user types in new args, this will get called
void *vcomb_new(long num_inputs, long num_outputs)
{
	int i;
	
	//leave this; creates our object
    t_vcomb *x = (t_vcomb *)object_alloc(vcomb_class);
    
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_vcomb);i++)  
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
	x->num_inputs = 4; 	//fft components in 1 and 2; delay time in 3; feedback coefficient in 4
	x->num_outputs = 2; //fft components out

	//setup up inputs and outputs, for audio
	
	//inputs
    dsp_setup((t_pxobject *)x, x->num_inputs);

    //outputs
    for (i=0;i<x->num_outputs;i++) {
    	outlet_new((t_object *)x, "signal");
    }   
    
    //initialize some variables; important to do this!
    for (i=0;i<x->num_inputs;i++){
    	x->in[i] = 0.;
    	x->in_connected[i] = 0;
    }
    //turn it on, by default
    x->power = 1;

	//allocate memory for the delay lines; lotso them!
	
    for(i=0;i<MAX_DELAY;i++) {
	    x->bin1delays[i] = t_getbytes(MAX_BINS*sizeof(float));
		if (!x->bin1delays[i]) {
			error("vcomb~: out of memory");
			return x;
		}
		
		x->bin2delays[i] = t_getbytes(MAX_BINS*sizeof(float));
		if (!x->bin2delays[i]) {
			error("vcomb~: out of memory");
			return x;
		}
	}
	
	x->delaytime = t_getbytes(MAX_BINS*sizeof(long));
	if (!x->delaytime) {
		error("vcomb~: out of memory");
		return x;
	}
	x->inPoint = t_getbytes(MAX_BINS*sizeof(long));
	if (!x->inPoint) {
		error("vcomb~: out of memory");
		return x;
	}
	x->outPoint = t_getbytes(MAX_BINS*sizeof(long));
	if (!x->outPoint) {
		error("vcomb~: out of memory");
		return x;
	}
	
	x->last_output1 = t_getbytes(MAX_BINS*sizeof(float));
	if (!x->last_output1) {
		error("vcomb~: out of memory");
		return x;
	}
	
	x->last_output2 = t_getbytes(MAX_BINS*sizeof(float));
	if (!x->last_output2) {
		error("vcomb~: out of memory");
		return x;
	}
	
	for(i=0;i<MAX_BINS;i++) {
		x->delaytime[i] = 50;
		dline_setDelay(x, i, 50);
		
	}
	
	//zero them out; takes a long time!
	/*
	for(i=0;i<MAX_BINS;i++) {
		
		for(j=0;j<MAX_DELAY;j++) {
			x->bin1delays[j][i] = 0.;
			x->bin2delays[j][i] = 0.;
		}
	}
	*/

	//occasionally this line is necessary if you are doing weird asynchronous things with the in/out vectors
	//x->x_obj.z_misc = Z_NO_INPLACE;

    return (x);
}


//this gets called when an object is destroyed. do stuff here if you need to clean up.
void vcomb_free(t_vcomb *x)
{
	int i;
	
	//gotta call this one
	dsp_free((t_pxobject *)x);
	
	//free delay lines
	if (x->delaytime)
		t_freebytes(x->delaytime, MAX_BINS * sizeof(long));
		
	for(i=0;i<MAX_DELAY;i++) {
		if (x->bin1delays[i])
			t_freebytes(x->bin1delays[i], MAX_BINS*sizeof(float));
		if (x->bin2delays[i])
			t_freebytes(x->bin2delays[i], MAX_BINS*sizeof(float));
	}
	
}


//tells the user about the inputs/outputs when mousing over them
void vcomb_assist(t_vcomb *x, void *b, long m, long a, char *s)
{
	int i;
	if (m==1) {
		for(i=0;i<x->num_inputs;i++)
			if (a==0)  sprintf(s, "fft in 1");
        if (a==1)  sprintf(s, "fft in 2");
        if (a==2)  sprintf(s, "delay time (int: in unit samples)");
        if (a==3)  sprintf(s, "feedback coefficient (float)");
	}
	if (m==2) {
		for(i=0;i<x->num_outputs;i++)
			if (a==0)  sprintf(s, "fft out 1");
        if (a==1)  sprintf(s, "fft out 2");
	}
}


//this gets called when ever a float is received at *any* input
void vcomb_float(t_vcomb *x, double f)
{
	int i;
	
	//check to see which input the float came in, then set the appropriate variable value
	for(i=0;i<x->num_inputs;i++) {
		if (x->x_obj.z_in == i) {
			x->in[i] = f;
			post("vcomb~: setting in[%d] =  %f", i, f);
		}
	}
}


//what to do when we get the message "mymessage" and a value (or list of values)
void vcomb_mymessage(t_vcomb *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	long temp2;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp2 = argv[i].a_w.w_long;
				//probably should comment these out when the object is debugged.
    			post("vcomb~: received argument %d of mymessage with value %d", i+1, temp2);
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
    			post("vcomb~: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
}

//what to do when we get the message "mymessage" and a value (or list of values)
void vcomb_setpower(t_vcomb *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	long temp2;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp2 = argv[i].a_w.w_long;
				//probably should comment these out when the object is debugged.
				x->power = temp2;
    			post("vcomb~: power = %d", x->power);
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
    			//post("vcomb~: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
}


void vcomb_dsp64(t_vcomb *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	int i;
    
	//set sample rate vars
	x->srate = samplerate;
	x->one_over_srate = 1./x->srate;
	
	//check to see if there are signals connected to the various inputs
	for(i=0;i<x->num_inputs;i++) x->in_connected[i]	= count[i];
	
    object_method(dsp64, gensym("dsp_add64"), x, vcomb_perform64, 0, NULL);
}

void vcomb_perform64(t_vcomb *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double *in[MAX_INPUTS]; 		//pointers to the input vectors
	t_double *out[MAX_OUTPUTS];	//pointers to the output vectors
	t_double temp[MAX_INPUTS];
	t_double samples[2];
    
	long n = sampleframes;	//number of samples per vector
	
	//random local vars
	int i, j;
	t_double fft1, fft2, feedback_coeff;
	long delaytime;
	
	//bypass if necessary
	if (x->x_obj.z_disabled || (x->power == 0)) return;
	
	//check to see if we have a signal or float message connected to input
	//then assign the pointer accordingly
	for (i=0;i<x->num_inputs;i++) {
		in[i] = x->in_connected[i] ? (t_double *)(ins[i]) : &x->in[i];
	}
	
	//assign the output vectors
	for (i=0;i<x->num_outputs;i++) {
		out[i] = (t_double *)(outs[i]);
	}
	
	for(j=0;j<n;j++) {
		
		for(i=0;i<x->num_inputs;i++) {
			if(x->in_connected[i]) temp[i] = *in[i]++; //use the signal vector if there is one
			else temp[i] = *in[i];					   //otherwise use the global variable
		}
		
		//grab inputs
		fft1 			= temp[0];
		fft2 			= temp[1];
		delaytime 		= (long)temp[2]; //in samples!
		feedback_coeff 	= temp[3];
		
		//set delay time if necessary
		if(delaytime != x->delaytime[j]) {
			x->delaytime[j] = delaytime;
			dline_setDelay(x, j, delaytime);
		}
		
		samples[0] = x->last_output1[j];
		samples[1] = x->last_output2[j];
		dline_tick(x, j, samples); //delay them, get the new ones back, in place
		*out[0]++ = x->last_output1[j] = feedback_coeff*samples[0] + fft1;
		*out[1]++ = x->last_output2[j] = feedback_coeff*samples[1] + fft2;
		
	}
}
