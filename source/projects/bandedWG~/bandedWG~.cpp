//bandedWG; all them bandedWG
//
//dt 2005; yet another PeRColate hack
//
// updated for Max 7 by Darwin Grosse and Tim Place
//
/***************************************************/
/*! \class BandedWG
    \brief Banded waveguide modeling class.

    This class uses banded waveguide techniques to
    model a variety of sounds, including bowed
    bars, glasses, and bowls.  For more
    information, see Essl, G. and Cook, P. "Banded
    Waveguides: Towards Physical Modelling of Bar
    Percussion Instruments", Proceedings of the
    1999 International Computer Music Conference.

    Control Change Numbers: 
       - Bow Pressure = 2
       - Bow Motion = 4
       - Strike Position = 8 (not implemented)
       - Vibrato Frequency = 11
       - Gain = 1
       - Bow Velocity = 128
       - Set Striking = 64
       - Instrument Presets = 16
         - Uniform Bar = 0
         - Tuned Bar = 1
         - Glass Harmonica = 2
         - Tibetan Bowl = 3

    by Georg Essl, 1999 - 2004.
    Modified for Stk 4.0 by Gary Scavone.
*/
/***************************************************/

#include <math.h>
// extern "C" {
#include "ext.h"
#include "ext_obex.h"
#include "ext_strings.h"
#include "z_dsp.h"
// }

#include <stdlib.h>
#include <string.h>

#include "BandedWG.h"

#define MAX_INPUTS 10 	//arbitrary
#define MAX_OUTPUTS 10	//also arbitrary

t_class *bandedWG_class;

typedef struct _bandedWG
{
	//header
    t_pxobject x_obj;
    
    //variables specific to this object
    double srate, one_over_srate;  	//sample rate vars
    long num_inputs, num_outputs; 	//number of inputs and outputs
    double in[MAX_INPUTS];			//values of input variables
    long in_connected[MAX_INPUTS]; //booleans: true if signals connected to the input in question
    
    //we use this "connected" boolean so that users can connect *either* signals or floats
    //to the various inputs; sometimes it's easier just to have floats, but other times
    //it's essential to have signals.... but we have to know. 
    
    BandedWG 	*myBanded;
    long power;					//i like objects, especially CPU intensive ones, to have their own
    								//"power" messages so that you can bypass them individually
} t_bandedWG;


/****PROTOTYPES****/

//setup funcs; this probably won't change, unless you decide to change the number of
//args that the user can input, in which case bandedWG_new will have to change
void *bandedWG_new(long num_inputs, long num_outputs);
void bandedWG_free(t_bandedWG *x);
void bandedWG_assist(t_bandedWG *x, void *b, long m, long a, char *s);

//for getting floats at inputs
void bandedWG_float(t_bandedWG *x, double f);

//for custom messages
void bandedWG_setpower(t_bandedWG *x, t_symbol *s, long argc, t_atom *argv);
void bandedWG_controlchange(t_bandedWG *x, t_symbol *s, long argc, t_atom *argv);
void bandedWG_noteon(t_bandedWG *x, t_symbol *s, long argc, t_atom *argv);
void bandedWG_noteoff(t_bandedWG *x, t_symbol *s, long argc, t_atom *argv);

// dsp stuff
void bandedWG_dsp64(t_bandedWG *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void bandedWG_perform64(t_bandedWG *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

/****FUNCTIONS****/

//primary MSP funcs
void ext_main(void* p)
{
	//the two A_DEFLONG arguments give us the two arguments for the user to set number of ins/outs
	//change these if you want different user args
    t_class *c = class_new("bandedWG~", (method)bandedWG_new, (method)bandedWG_free, (long)sizeof(t_bandedWG), 0L, A_DEFLONG, A_DEFLONG, 0);
    
    class_addmethod(c, (method)bandedWG_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)bandedWG_float, "float", A_FLOAT, 0);
    class_addmethod(c, (method)bandedWG_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)bandedWG_setpower, "power", A_GIMME, 0);
    class_addmethod(c, (method)bandedWG_controlchange, "control", A_GIMME, 0);
    class_addmethod(c, (method)bandedWG_noteon, "noteon", A_GIMME, 0);
    class_addmethod(c, (method)bandedWG_noteoff, "noteoff", A_GIMME, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    bandedWG_class = c;
}

//this gets called when the object is created; everytime the user types in new args, this will get called
void *bandedWG_new(long xD, long yD)
{
	int i;
	
    t_bandedWG *x = (t_bandedWG *)object_alloc(bandedWG_class);
    
    if (x) {
        //zero out the struct, to be careful (takk to jkclayton)
        for(i=sizeof(t_pxobject);i<sizeof(t_bandedWG);i++) {
            ((char *)x)[i]=0;
        }

        x->num_inputs = 1;
        x->num_outputs = 1;

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
        x->myBanded = new BandedWG(); 	 
	}
    
    return (x);
}

//this gets called when an object is destroyed. do stuff here if you need to clean up.
void bandedWG_free(t_bandedWG *x)
{
	//gotta call this one, *before* you free other resources! thanks to Rob Sussman for pointing this out to me.
	dsp_free((t_pxobject *)x);
	delete x->myBanded;
}

//tells the user about the inputs/outputs when mousing over them
void bandedWG_assist(t_bandedWG *x, void *b, long m, long a, char *s)
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
void bandedWG_float(t_bandedWG *x, double f)
{
	int i;
	
	//check to see which input the float came in, then set the appropriate variable value
	for(i=0;i<x->num_inputs;i++) {
		if (x->x_obj.z_in == i) {
			x->in[i] = f;
			post("bandedWG~: setting in[%d] =  %f", i, f);
		}
	}
}

//what to do when we get the message "mymessage" and a value (or list of values)
void bandedWG_setpower(t_bandedWG *x, t_symbol *s, long argc, t_atom *argv)
{
	long i;
	double temp;
	long temp2;
    
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp2 = argv[i].a_w.w_long;
				//probably should comment these out when the object is debugged.
				x->power = temp2;
    			post("bandedWG~: power = %d", x->power);
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
    			//post("template~: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
}

void bandedWG_controlchange(t_bandedWG *x, t_symbol *s, long argc, t_atom *argv)
{
	long i;
	double temp[2];
    
	if(argc<2) {
		post("bandedWG~ error: need two arguments, control number and control value\n");
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
	x->myBanded->controlChange((int)temp[0], temp[1]);
}

void bandedWG_noteon(t_bandedWG *x, t_symbol *s, long argc, t_atom *argv)
{
	long i;
	double temp[2];
    
	if(argc<2) {
		post("bandedWG~ error: need two arguments, frequency and amplitude\n");
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
	
	x->myBanded->noteOn((int)temp[0], temp[1]);
}

void bandedWG_noteoff(t_bandedWG *x, t_symbol *s, long argc, t_atom *argv)
{
	long i;
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
	x->myBanded->noteOff(temp);
}

void bandedWG_dsp64(t_bandedWG *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    // void *dsp_add_args[MAX_INPUTS + MAX_OUTPUTS + 2];
	int i;
    
	//set sample rate vars
	x->srate = samplerate;
	x->one_over_srate = 1./x->srate;
	Stk::setSampleRate(x->srate);
    
    for(i=0; i<x->num_inputs; i++) {
        x->in_connected[i]	= count[i];
    }
    
    object_method(dsp64, gensym("dsp_add64"), x, bandedWG_perform64, 0, NULL);
}

void bandedWG_perform64(t_bandedWG *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	long n = sampleframes;
    double *in[MAX_INPUTS];
    double *out[MAX_OUTPUTS];
	
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
	for (i=0; i<x->num_outputs; i++) {
		out[i] = (double *)(outs[i]);
	}
    
	while(n--) {
		*out[0]++ = x->myBanded->tick();
	}
}
