//saxofony
//
//dt 2005; yet another PeRColate hack
//
// ------------------------------------------------

/***************************************************/
/*! \class Saxofony
    \brief STK faux conical bore reed instrument class.

    This class implements a "hybrid" digital
    waveguide instrument that can generate a
    variety of wind-like sounds.  It has also been
    referred to as the "blowed string" model.  The
    waveguide section is essentially that of a
    string, with one rigid and one lossy
    termination.  The non-linear function is a
    reed table.  The string can be "blown" at any
    point between the terminations, though just as
    with strings, it is impossible to excite the
    system at either end.  If the excitation is
    placed at the string mid-point, the sound is
    that of a clarinet.  At points closer to the
    "bridge", the sound is closer to that of a
    saxophone.  See Scavone (2002) for more details.

    This is a digital waveguide model, making its
    use possibly subject to patents held by Stanford
    University, Yamaha, and others.

    Control Change Numbers: 
       - Reed Stiffness = 2
       - Reed Aperture = 26
       - Noise Gain = 4
       - Blow Position = 11
       - Vibrato Frequency = 29
       - Vibrato Gain = 1
       - Breath Pressure = 128

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

#include "Saxofony.h"

#define MAX_INPUTS 10 	//arbitrary
#define MAX_OUTPUTS 10	//also arbitrary

t_class *saxofony_class;

typedef struct _saxofony
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
    
    Saxofony 	*mySax;
    
    short power;					//i like objects, especially CPU intensive ones, to have their own
    								//"power" messages so that you can bypass them individually

    
} t_saxofony;


/****PROTOTYPES****/

//setup funcs; this probably won't change, unless you decide to change the number of
//args that the user can input, in which case saxofony_new will have to change
void *saxofony_new(long num_inputs, long num_outputs);
void saxofony_free(t_saxofony *x);
void saxofony_assist(t_saxofony *x, void *b, long m, long a, char *s);

// dsp stuff
void saxofony_dsp64(t_saxofony *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void saxofony_perform64(t_saxofony *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

//for getting floats at inputs
void saxofony_float(t_saxofony *x, double f);

//for custom messages
void saxofony_setpower(t_saxofony *x, t_symbol *s, long argc, t_atom *argv);
void saxofony_controlchange(t_saxofony *x, t_symbol *s, long argc, t_atom *argv);
void saxofony_noteon(t_saxofony *x, t_symbol *s, long argc, t_atom *argv);
void saxofony_noteoff(t_saxofony *x, t_symbol *s, long argc, t_atom *argv);


/****FUNCTIONS****/

//primary MSP funcs
void ext_main(void* p)
{
    t_class *c = class_new("saxofony~", (method)saxofony_new, (method)saxofony_free, (long)sizeof(t_saxofony), 0L, A_DEFLONG, A_DEFLONG, 0);
    
    class_addmethod(c, (method)saxofony_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)saxofony_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)saxofony_float, "float", A_FLOAT, 0);
    class_addmethod(c, (method)saxofony_setpower, "power", A_GIMME, 0);
    class_addmethod(c, (method)saxofony_controlchange, "control", A_GIMME, 0);
    class_addmethod(c, (method)saxofony_noteon, "noteon", A_GIMME, 0);
    class_addmethod(c, (method)saxofony_noteoff, "noteoff", A_GIMME, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    saxofony_class = c;
}

//this gets called when the object is created; everytime the user types in new args, this will get called
void *saxofony_new(long xD, long yD)
{
	int i;
	
	//leave this; creates our object
    t_saxofony *x = (t_saxofony *)object_alloc(saxofony_class);
    
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_saxofony);i++)  
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
	
	//Stk::setRawwavePath("../../rawwaves/");

	x->mySax = new Saxofony(50.); 	 
	
    return (x);
}


//this gets called when an object is destroyed. do stuff here if you need to clean up.
void saxofony_free(t_saxofony *x)
{
	//gotta call this one, *before* you free other resources! thanks to Rob Sussman for pointing this out to me.
	dsp_free((t_pxobject *)x);
	
	delete x->mySax;
}


//tells the user about the inputs/outputs when mousing over them
void saxofony_assist(t_saxofony *x, void *b, long m, long a, char *s)
{
	int i;
	
	//could use switch/case inside for loops, to give more informative assist info....
	if (m==1) {
		for(i=0;i<x->num_inputs;i++)
			if (a==i) std::sprintf(s, "control messages");
	}
	if (m==2) {
		for(i=0;i<x->num_outputs;i++)
			if (a==i) std::sprintf(s, "output (signal)");
	}
	
}


//this gets called when ever a float is received at *any* input
void saxofony_float(t_saxofony *x, double f)
{
	int i;
	
	//check to see which input the float came in, then set the appropriate variable value
	for(i=0;i<x->num_inputs;i++) {
		if (x->x_obj.z_in == i) {
			x->in[i] = f;
			post("saxofony~: setting in[%d] =  %f", i, f);
		}
	}
}


//what to do when we get the message "mymessage" and a value (or list of values)
void saxofony_setpower(t_saxofony *x, t_symbol *s, long argc, t_atom *argv)
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
    			post("saxofony~: power = %d", x->power);
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
    			//post("template~: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
    
}

void saxofony_controlchange(t_saxofony *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp[2];
    
	if(argc<2) {
		post("saxofony~ error: need two arguments, control number and control value\n");
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
	x->mySax->controlChange((int)temp[0], temp[1]);
}

void saxofony_noteon(t_saxofony *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp[2];
    
	if(argc<2) {
		post("saxofony~ error: need two arguments, frequency and amplitude\n");
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
	
	x->mySax->noteOn((int)temp[0], temp[1]);
}

void saxofony_noteoff(t_saxofony *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (float)argv[i].a_w.w_long;
				//probably should comment these out when the object is debugged.
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
    			//post("template~: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
	x->mySax->noteOff(temp);
}

void saxofony_dsp64(t_saxofony *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
   	int i;
    
	//set sample rate vars
	x->srate = samplerate;
	x->one_over_srate = 1./x->srate;
	
	Stk::setSampleRate(x->srate);
	
	//check to see if there are signals connected to the various inputs
	for(i=0;i<x->num_inputs;i++) x->in_connected[i]	= count[i];
    
    object_method(dsp64, gensym("dsp_add64"), x, saxofony_perform64, 0, NULL);
}

void saxofony_perform64(t_saxofony *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
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
    
	while(n--) {
		*out[0]++ = x->mySax->tick();
	}
}


