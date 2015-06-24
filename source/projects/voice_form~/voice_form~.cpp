//voice_form; from the STK
//
//dt 2005; yet another PeRColate hack
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------
/***************************************************/
/*! \class VoicForm
    \brief Four formant synthesis instrument.

    This instrument contains an excitation singing
    wavetable (looping wave with random and
    periodic vibrato, smoothing on frequency,
    etc.), excitation noise, and four sweepable
    complex resonances.

    Measured formant data is included, and enough
    data is there to support either parallel or
    cascade synthesis.  In the floating point case
    cascade synthesis is the most natural so
    that's what you'll find here.

    Control Change Numbers: 
       - Voiced/Unvoiced Mix = 2
       - Vowel/Phoneme Selection = 4
       - Vibrato Frequency = 11
       - Vibrato Gain = 1
       - Loudness (Spectral Tilt) = 128

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

#include "VoicForm.h"

#define MAX_INPUTS 10 	//arbitrary
#define MAX_OUTPUTS 10	//also arbitrary

t_class *voice_form_class;

typedef struct _voice_form
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
    
    VoicForm 	*myVoice;

    short fm_type; //which instrument
    
    short power;					//i like objects, especially CPU intensive ones, to have their own
    								//"power" messages so that you can bypass them individually
} t_voice_form;


/****PROTOTYPES****/

//setup funcs; this probably won't change, unless you decide to change the number of
//args that the user can input, in which case voice_form_new will have to change
void *voice_form_new(long num_inputs, long num_outputs);
void voice_form_free(t_voice_form *x);
void voice_form_assist(t_voice_form *x, void *b, long m, long a, char *s);

// dsp stuff
void voice_form_dsp64(t_voice_form *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void voice_form_perform64(t_voice_form *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

//for getting floats at inputs
void voice_form_float(t_voice_form *x, double f);

//for custom messages
void voice_form_setpower(t_voice_form *x, t_symbol *s, long argc, t_atom *argv);
void voice_form_controlchange(t_voice_form *x, t_symbol *s, long argc, t_atom *argv);
void voice_form_noteon(t_voice_form *x, t_symbol *s, long argc, t_atom *argv);
void voice_form_noteoff(t_voice_form *x, t_symbol *s, long argc, t_atom *argv);
void voice_form_settype(t_voice_form *x, t_symbol *s, long argc, t_atom *argv);


/****FUNCTIONS****/

//primary MSP funcs
void ext_main(void* p)
{
    t_class *c = class_new("voice_form~", (method)voice_form_new, (method)voice_form_free, (long)sizeof(t_voice_form), 0L, A_DEFLONG, A_DEFLONG, 0);
    
    class_addmethod(c, (method)voice_form_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)voice_form_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)voice_form_float, "float", A_FLOAT, 0);
    
    //our own messages
    class_addmethod(c, (method)voice_form_setpower, "power", A_GIMME, 0);
    class_addmethod(c, (method)voice_form_controlchange, "control", A_GIMME, 0);
    class_addmethod(c, (method)voice_form_noteon, "noteon", A_GIMME, 0);
    class_addmethod(c, (method)voice_form_noteoff, "noteoff", A_GIMME, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    voice_form_class = c;
}

//this gets called when the object is created; everytime the user types in new args, this will get called
void *voice_form_new(long xD, long yD)
{
	int i;
	
	//leave this; creates our object
    t_voice_form *x = (t_voice_form *)object_alloc(voice_form_class);
    
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_voice_form);i++)  
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

	x->myVoice = new VoicForm();
    return (x);
}


//this gets called when an object is destroyed. do stuff here if you need to clean up.
void voice_form_free(t_voice_form *x)
{
	//gotta call this one, *before* you free other resources! thanks to Rob Sussman for pointing this out to me.
	dsp_free((t_pxobject *)x);
	delete x->myVoice;

}

//tells the user about the inputs/outputs when mousing over them
void voice_form_assist(t_voice_form *x, void *b, long m, long a, char *s)
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
void voice_form_float(t_voice_form *x, double f)
{
    int i;
    
    //check to see which input the float came in, then set the appropriate variable value
    for(i=0;i<x->num_inputs;i++) {
        if (x->x_obj.z_in == i) {
            x->in[i] = f;
            post("voice_form~: setting in[%d] =  %f", i, f);
        }
    }
}


//what to do when we get the message "mymessage" and a value (or list of values)
void voice_form_setpower(t_voice_form *x, t_symbol *s, long argc, t_atom *argv)
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

void voice_form_controlchange(t_voice_form *x, t_symbol *s, long argc, t_atom *argv)
{
    short i;
    float temp[2];
    
    if(argc<2) {
        post("voice_form~ error: need two arguments, control number and control value\n");
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
    x->myVoice->controlChange(temp[0], temp[1]);
}

void voice_form_noteon(t_voice_form *x, t_symbol *s, long argc, t_atom *argv)
{
    short i;
    float temp[2];
    
    if(argc<2) {
        post("voice_form~ error: need two arguments, frequency and amplitude\n");
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
    x->myVoice->noteOn(temp[0], temp[1]);
}

void voice_form_noteoff(t_voice_form *x, t_symbol *s, long argc, t_atom *argv)
{
    short i;
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
    x->myVoice->noteOff(temp);
}

void voice_form_dsp64(t_voice_form *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    int i;
    
    //set sample rate vars
    x->srate = samplerate;
    x->one_over_srate = 1./x->srate;
    
    Stk::setSampleRate(x->srate);
    
    //check to see if there are signals connected to the various inputs
    for(i=0;i<x->num_inputs;i++) x->in_connected[i]	= count[i];
    
    object_method(dsp64, gensym("dsp_add64"), x, voice_form_perform64, 0, NULL);
}

void voice_form_perform64(t_voice_form *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    t_double *in[MAX_INPUTS]; 		//pointers to the input vectors
    t_double *out[MAX_OUTPUTS];	//pointers to the output vectors
    
    long n = sampleframes;	//number of samples per vector
    
    //random local vars
    int i;
    
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
        *out[0]++ = x->myVoice->tick();
    }
}
