//pit_shift
//
//dt 2005; yet another PeRColate hack
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

//here are the notes from the original STK instrument
/***************************************************/
/*! \class PitShift
    \brief STK simple pitch shifter effect class.

    This class implements a simple pitch shifter
    using delay lines.

    by Perry R. Cook and Gary P. Scavone, 1995 - 2004.
*/
/***************************************************/

extern "C" {
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "ext_strings.h"
}

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "PitShift.h"

#define MAX_INPUTS 10 	//arbitrary
#define MAX_OUTPUTS 10	//also arbitrary

t_class *pit_shift_class;

typedef struct _pit_shift
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
    
    PitShift *myshift;
    
    short power;					//i like objects, especially CPU intensive ones, to have their own
    								//"power" messages so that you can bypass them individually

    
} t_pit_shift;


/****PROTOTYPES****/

//setup funcs; this probably won't change, unless you decide to change the number of
//args that the user can input, in which case pit_shift_new will have to change
void *pit_shift_new(long num_inputs, long num_outputs);
void pit_shift_free(t_pit_shift *x);
void pit_shift_assist(t_pit_shift *x, void *b, long m, long a, char *s);

// dsp stuff
void pit_shift_dsp64(t_pit_shift *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void pit_shift_perform64(t_pit_shift *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

//for getting floats at inputs
void pit_shift_float(t_pit_shift *x, double f);

//for custom messages
void pit_shift_setShift(t_pit_shift *x, t_symbol *s, long argc, t_atom *argv);
void pit_shift_clear(t_pit_shift *x, t_symbol *s, long argc, t_atom *argv);


void pit_shift_setpower(t_pit_shift *x, t_symbol *s, long argc, t_atom *argv);


/****FUNCTIONS****/

//primary MSP funcs
void ext_main(void* p)
{
    t_class *c = class_new("pit_shift~", (method)pit_shift_new, (method)pit_shift_free, (long)sizeof(t_pit_shift), 0L, A_DEFLONG, A_DEFLONG, 0);
    
    class_addmethod(c, (method)pit_shift_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)pit_shift_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)pit_shift_float, "float", A_FLOAT, 0);
    class_addmethod(c, (method)pit_shift_setpower, "power", A_GIMME, 0);
    class_addmethod(c, (method)pit_shift_setShift, "shift", A_GIMME, 0);
    class_addmethod(c, (method)pit_shift_clear, "clear", A_GIMME, 0);    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    pit_shift_class = c;
}

//this gets called when the object is created; everytime the user types in new args, this will get called
void *pit_shift_new(long baseDelay, long yD)
{
	int i;
	
	//leave this; creates our object
    t_pit_shift *x = (t_pit_shift *)object_alloc(pit_shift_class);
    
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_pit_shift);i++)  
                ((char *)x)[i]=0; 
	} 

	x->num_inputs = 1;
	x->num_outputs = 1;

	//setup up inputs and outputs, for audio
	
	//inputs
    dsp_setup((t_pxobject *)x, x->num_inputs);
    //if you just need one input for message (not using audio), you can just set num_inputs = 1
    //i don't think this causes a performance hit.
    
    //outputs
    for (i=0;i<x->num_outputs;i++) {
    	outlet_new((t_object *)x, "signal");
    }   
    //can use intin, floatout, listout, etc... for setting up non-audio ins and outs.
    //but, the order in which you call these funcs is important.
    //for instance, from gQ~
    /*    
    x->outfloat = floatout((t_object *)x);
    x->outlist = listout((t_object *)x);
    outlet_new((t_object *)x, "signal");
    outlet_new((t_object *)x, "signal");
   */
   //this will create four outputs, *rightmost* created first, so the outlets, from left to right, will look like
   //(signal) (signal) (list) (float)
   //when you instantiate gQ~ in Max/MSP.
    
    //initialize some variables; important to do this!
    for (i=0;i<x->num_inputs;i++){
    	x->in[i] = 0.;
    	x->in_connected[i] = 0;
    }
    x->power = 1;

	//occasionally this line is necessary if you are doing weird asynchronous things with the in/out vectors
	//x->x_obj.z_misc = Z_NO_INPLACE;
	
	x->myshift = new PitShift();

    return (x);
}


//this gets called when an object is destroyed. do stuff here if you need to clean up.
void pit_shift_free(t_pit_shift *x)
{
	//gotta call this one, *before* you free other resources! thanks to Rob Sussman for pointing this out to me.
	dsp_free((t_pxobject *)x);
	delete x->myshift;
}

//tells the user about the inputs/outputs when mousing over them
void pit_shift_assist(t_pit_shift *x, void *b, long m, long a, char *s)
{
	int i;
	//could use switch/case inside for loops, to give more informative assist info....
	if (m==1) {
		for(i=0;i<x->num_inputs;i++)
			if (a==i) std::sprintf(s, "input (signal)");
	}
	if (m==2) {
		for(i=0;i<x->num_outputs;i++)
			if (a==i) std::sprintf(s, "output (signal)");
	}
}


//this gets called when ever a float is received at *any* input
void pit_shift_float(t_pit_shift *x, double f)
{
	int i;
	
	//check to see which input the float came in, then set the appropriate variable value
	for(i=0;i<x->num_inputs;i++) {
		if (x->x_obj.z_in == i) {
			x->in[i] = f;
			post("pit_shift~: setting in[%d] =  %f", i, f);
		}
	}
}

void pit_shift_setShift(t_pit_shift *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (float)argv[i].a_w.w_long;
				//probably should comment these out when the object is debugged.
    			//post("template~: received argument %d of mymessage with value %d", i+1, temp2);
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
    			//post("template~: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
	
	x->myshift->setShift(temp);
}

void pit_shift_clear(t_pit_shift *x, t_symbol *s, long argc, t_atom *argv)
{
    
	x->myshift->clear();
}

//what to do when we get the message "mymessage" and a value (or list of values)
void pit_shift_setpower(t_pit_shift *x, t_symbol *s, long argc, t_atom *argv)
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
    			post("template~: power = %d", x->power);
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
    			//post("template~: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
}

void pit_shift_dsp64(t_pit_shift *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	int i;
    
	//set sample rate vars
	x->srate = samplerate;
	x->one_over_srate = 1./x->srate;
	
	//check to see if there are signals connected to the various inputs
	for(i=0;i<x->num_inputs;i++) x->in_connected[i]	= count[i];
	
	Stk::setSampleRate(x->srate);
    object_method(dsp64, gensym("dsp_add64"), x, pit_shift_perform64, 0, NULL);
}

void pit_shift_perform64(t_pit_shift *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double *in[MAX_INPUTS]; 		//pointers to the input vectors
	t_double *out[MAX_OUTPUTS];	//pointers to the output vectors
    
	long n = sampleframes;	//number of samples per vector
	
	//random local vars
	int i;
	t_double temp;
	
	//check to see if we should skip this routine if the patcher is "muted"
	//i also setup of "power" messages for expensive objects, so that the
	//object itself can be turned off directly. this can be convenient sometimes.
	//in any case, all audio objects should have this
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
	
	while(n--) {	//this is where the action happens..... let's make something up
        
		if(x->in_connected[0]) temp = *in[0]++; //use the signal vector if there is one
		else temp = *in[0];					 	//otherwise use the global variable
		*out[0]++ = x->myshift->tick(temp);
        
	}
}
