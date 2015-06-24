//blow_hole; from the STK
//
//dt 2005; yet another PeRColate hack
//
// updated for Max 7 by Darwin Grosse and Tim Place
// -------------------------------------------------

#include <math.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "ext.h"
#include "ext_obex.h"
#include "ext_strings.h"
#include "z_dsp.h"
}

#include "BlowHole.h"

#define MAX_INPUTS 10 	//arbitrary
#define MAX_OUTPUTS 10	//also arbitrary

t_class *blow_hole_class;

typedef struct _blow_hole
{
	//header
    t_pxobject x_obj;
    
    //variables specific to this object
    double srate, one_over_srate;  	//sample rate vars
    long num_inputs, num_outputs; 	//number of inputs and outputs
    double in[MAX_INPUTS];			//values of input variables
    double in_connected[MAX_INPUTS]; //booleans: true if signals connected to the input in question
    //we use this "connected" boolean so that users can connect *either* signals or floats
    //to the various inputs; sometimes it's easier just to have floats, but other times
    //it's essential to have signals.... but we have to know.
    
    BlowHole 	*myHole;
    
    long fm_type;   //which instrument
    long power;		//i like objects, especially CPU intensive ones, to have their own
                    //"power" messages so that you can bypass them individually
} t_blow_hole;


/****PROTOTYPES****/

//setup funcs; this probably won't change, unless you decide to change the number of
//args that the user can input, in which case blow_hole_new will have to change
void *blow_hole_new(long num_inputs, long num_outputs);
void blow_hole_free(t_blow_hole *x);
void blow_hole_assist(t_blow_hole *x, void *b, long m, long a, char *s);

// dsp stuff
void blow_hole_dsp64(t_blow_hole *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void blow_hole_perform64(t_blow_hole *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

//for getting floats at inputs
void blow_hole_float(t_blow_hole *x, double f);

//for custom messages
void blow_hole_setpower(t_blow_hole *x, t_symbol *s, long argc, t_atom *argv);
void blow_hole_controlchange(t_blow_hole *x, t_symbol *s, long argc, t_atom *argv);
void blow_hole_noteon(t_blow_hole *x, t_symbol *s, long argc, t_atom *argv);
void blow_hole_noteoff(t_blow_hole *x, t_symbol *s, long argc, t_atom *argv);
void blow_hole_settype(t_blow_hole *x, t_symbol *s, long argc, t_atom *argv);


/****FUNCTIONS****/

//primary MSP funcs
void ext_main(void* p)
{
	//the two A_DEFLONG arguments give us the two arguments for the user to set number of ins/outs
	//change these if you want different user args
    t_class *c = class_new("blow_hole~", (method)blow_hole_new, (method)blow_hole_free, (long)sizeof(t_blow_hole), 0L, A_DEFLONG, A_DEFLONG, 0);
    
    class_addmethod(c, (method)blow_hole_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)blow_hole_float, "float", A_FLOAT, 0);
    
    class_addmethod(c, (method)blow_hole_setpower, "power", A_GIMME, 0);
    class_addmethod(c, (method)blow_hole_controlchange, "control", A_GIMME, 0);
    class_addmethod(c, (method)blow_hole_noteon, "noteon", A_GIMME, 0);
    class_addmethod(c, (method)blow_hole_noteoff, "noteoff", A_GIMME, 0);
    
    class_addmethod(c, (method)blow_hole_dsp64, "dsp64", A_CANT, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    blow_hole_class = c;
}

//this gets called when the object is created; everytime the user types in new args, this will get called
void *blow_hole_new(long xD, long yD)
{
	int i;
	
	//leave this; creates our object
    t_blow_hole *x = (t_blow_hole *)object_alloc(blow_hole_class);
    
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) {
        for(i=sizeof(t_pxobject);i<sizeof(t_blow_hole);i++) {
            ((char *)x)[i]=0;
        }
        
        //if you just need one input for message (not using audio), you can just set num_inputs = 1
        //i don't think this causes a performance hit.
        x->num_inputs = 1;
        x->num_outputs = 1;
        
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
        x->power = 1;
        
        //occasionally this line is necessary if you are doing weird asynchronous things with the in/out vectors
        //x->x_obj.z_misc = Z_NO_INPLACE;
        //Stk::setRawwavePath("../../rawwaves/");
        
        x->myHole = new BlowHole(100);
    }
    
    return (x);
}

//this gets called when an object is destroyed. do stuff here if you need to clean up.
void blow_hole_free(t_blow_hole *x)
{
	//gotta call this one, *before* you free other resources! thanks to Rob Sussman for pointing this out to me.
	dsp_free((t_pxobject *)x);
	delete x->myHole;
}

//tells the user about the inputs/outputs when mousing over them
void blow_hole_assist(t_blow_hole *x, void *b, long m, long a, char *s)
{
	int i;
	
	//could use switch/case inside for loops, to give more informative assist info....
	if (m==1) {
		for(i=0; i<x->num_inputs; i++)
			if (a==i) std::sprintf(s, "control messages");
	}
	if (m==2) {
		for(i=0; i<x->num_outputs; i++)
			if (a==i) std::sprintf(s, "output (signal)");
	}
	
}

//this gets called when ever a float is received at *any* input
void blow_hole_float(t_blow_hole *x, double f)
{
	int i;
	
	//check to see which input the float came in, then set the appropriate variable value
	for(i=0; i<x->num_inputs; i++) {
		if (x->x_obj.z_in == i) {
			x->in[i] = f;
			post("blow_hole~: setting in[%d] =  %f", i, f);
		}
	}
}

//what to do when we get the message "mymessage" and a value (or list of values)
void blow_hole_setpower(t_blow_hole *x, t_symbol *s, long argc, t_atom *argv)
{
	long i;
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

void blow_hole_controlchange(t_blow_hole *x, t_symbol *s, long argc, t_atom *argv)
{
	long i;
	float temp[2];
    
	if(argc<2) {
		post("blow_hole~ error: need two arguments, control number and control value\n");
		return;
	}
    
	for(i=0;i<2;i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp[i] = (float)argv[i].a_w.w_long;
				//probably should comment these out when the object is debugged.
				//post("template~: received argument %d of mymessage with value %d", i+1, temp2);
				break;
			case A_FLOAT:
				temp[i] = argv[i].a_w.w_float;
				//post("template~: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
	
	x->myHole->controlChange(temp[0], temp[1]);
}

void blow_hole_noteon(t_blow_hole *x, t_symbol *s, long argc, t_atom *argv)
{
	long i;
	float temp[2];
    
	if(argc<2) {
		post("blow_hole~ error: need two arguments, frequency and amplitude\n");
		return;
	}
    
	for(i=0;i<2;i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp[i] = (float)argv[i].a_w.w_long;
				//probably should comment these out when the object is debugged.
				//post("template~: received argument %d of mymessage with value %d", i+1, temp2);
				break;
			case A_FLOAT:
				temp[i] = argv[i].a_w.w_float;
				//post("template~: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
	x->myHole->noteOn(temp[0], temp[1]);
}

void blow_hole_noteoff(t_blow_hole *x, t_symbol *s, long argc, t_atom *argv)
{
	long i;
	float temp = 0.;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (float)argv[i].a_w.w_long;
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
				break;
		}
	}
	x->myHole->noteOff(temp);
}

void blow_hole_dsp64(t_blow_hole *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	int i;
    
	//set sample rate vars
	x->srate = samplerate;
	x->one_over_srate = 1./x->srate;
	Stk::setSampleRate(x->srate);
	
	//check to see if there are signals connected to the various inputs
	for(i=0;i<x->num_inputs;i++) {
        x->in_connected[i]	= count[i];
    }
    
    object_method(dsp64, gensym("dsp_add64"), x, blow_hole_perform64, 0, NULL);
}

void blow_hole_perform64(t_blow_hole *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	double *in[MAX_INPUTS]; 		//pointers to the input vectors
	double *out[MAX_OUTPUTS];	//pointers to the output vectors
    
	long n = sampleframes;	//number of samples per vector
	
	//random local vars
	long i;
	
	//check to see if we should skip this routine if the patcher is "muted"
	//i also setup of "power" messages for expensive objects, so that the
	//object itself can be turned off directly. this can be convenient sometimes.
	//in any case, all audio objects should have this
	if (x->power == 0) {
        while (n--)
            *outs[0]++ = *ins[0]++;
        return;
    }
	
	//check to see if we have a signal or float message connected to input
	//then assign the pointer accordingly
	for (i=0; i<x->num_inputs; i++) {
		in[i] = x->in_connected[i] ? (double *)(ins[i]) : &x->in[i];
	}
	
	//assign the output vectors
	for (i=0;i<x->num_outputs;i++) {
		out[i] = (double *)(outs[i]);
	}
    
	while(n--) {
		*out[0]++ = x->myHole->tick();
	}
}





