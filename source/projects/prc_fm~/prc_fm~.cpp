//prc_fm; all them prc_fm
//
//dt 2005; yet another PeRColate hack
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

//here are the notes from the original STK instrument
/***************************************************/
/*! \class FM
    \brief STK abstract FM synthesis base class.

    This class controls an arbitrary number of
    waves and envelopes, determined via a
    constructor argument.

    Control Change Numbers: 
       - Control One = 2
       - Control Two = 4
       - LFO Speed = 11
       - LFO Depth = 1
       - ADSR 2 & 4 Target = 128

    The basic Chowning/Stanford FM patent expired
    in 1995, but there exist follow-on patents,
    mostly assigned to Yamaha.  If you are of the
    type who should worry about this (making
    money) worry away.

    by Perry R. Cook and Gary P. Scavone, 1995 - 2004.
*/
/***************************************************/
//this port includes all the FM subclasses:
//BeeThree
//FMVoices
//HevyMetl
//PercFlut
//Rhodey
//TubeBell
//Wurley

//see http://ccrma.stanford.edu/software/stk/classFM.html for more info


extern "C" {
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "ext_strings.h"
}

#include <math.h>
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BeeThree.h"
#include "FMVoices.h"
#include "HevyMetl.h"
#include "PercFlut.h"
#include "Rhodey.h"
#include "TubeBell.h"
#include "Wurley.h"

#define MAX_INPUTS 10 	//arbitrary
#define MAX_OUTPUTS 10	//also arbitrary

t_class *prc_fm_class;

typedef struct _prc_fm
{
	//header
    t_pxobject x_obj;
    
    //variables specific to this object
    t_double srate, one_over_srate;  	//sample rate vars
    long num_inputs, num_outputs; 	//number of inputs and outputs
    t_double in[MAX_INPUTS];			//values of input variables
    float in_connected[MAX_INPUTS]; //booleans: true if signals connected to the input in question
    //we use this "connected" boolean so that users can connect *either* signals or floats
    //to the various inputs; sometimes it's easier just to have floats, but other times
    //it's essential to have signals.... but we have to know. 
    
    BeeThree 	*myBeeThree;
    FMVoices 	*myFMVoices;
    HevyMetl 	*myHevyMetl;
    PercFlut 	*myPercFlut;
    Rhodey 		*myRhodey;
    TubeBell 	*myTubeBell;
    Wurley 		*myWurley;
    
    short fm_type; //which instrument
    
    short power;					//i like objects, especially CPU intensive ones, to have their own
    								//"power" messages so that you can bypass them individually

    
} t_prc_fm;


/****PROTOTYPES****/

//setup funcs; this probably won't change, unless you decide to change the number of
//args that the user can input, in which case prc_fm_new will have to change
void *prc_fm_new(long num_inputs, long num_outputs);
void prc_fm_free(t_prc_fm *x);
void prc_fm_assist(t_prc_fm *x, void *b, long m, long a, char *s);

//for getting floats at inputs
void prc_fm_float(t_prc_fm *x, double f);

// dsp stuff
void prc_fm_dsp64(t_prc_fm *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void prc_fm_perform64(t_prc_fm *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

//for custom messages
void prc_fm_setpower(t_prc_fm *x, t_symbol *s, long argc, t_atom *argv);
void prc_fm_controlchange(t_prc_fm *x, t_symbol *s, long argc, t_atom *argv);
void prc_fm_noteon(t_prc_fm *x, t_symbol *s, long argc, t_atom *argv);
void prc_fm_noteoff(t_prc_fm *x, t_symbol *s, long argc, t_atom *argv);
void prc_fm_settype(t_prc_fm *x, t_symbol *s, long argc, t_atom *argv);


/****FUNCTIONS****/

//primary MSP funcs
void ext_main(void* p)
{
	//the two A_DEFLONG arguments give us the two arguments for the user to set number of ins/outs
	//change these if you want different user args
    t_class *c = class_new("prc_fm~", (method)prc_fm_new, (method)prc_fm_free, (long)sizeof(t_prc_fm), 0L, A_DEFLONG, A_DEFLONG, 0);
    
    class_addmethod(c, (method)prc_fm_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)prc_fm_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)prc_fm_float, "float", A_FLOAT, 0);
    
    //our own messages
    class_addmethod(c, (method)prc_fm_setpower, "power", A_GIMME, 0);
    class_addmethod(c, (method)prc_fm_controlchange, "control", A_GIMME, 0);
    class_addmethod(c, (method)prc_fm_noteon, "noteon", A_GIMME, 0);
    class_addmethod(c, (method)prc_fm_noteoff, "noteoff", A_GIMME, 0);
    class_addmethod(c, (method)prc_fm_settype, "type", A_GIMME, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    prc_fm_class = c;
}

//this gets called when the object is created; everytime the user types in new args, this will get called
void *prc_fm_new(long xD, long yD)
{
	int i;
	
	//leave this; creates our object
    t_prc_fm *x = (t_prc_fm *)object_alloc(prc_fm_class);
    
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_prc_fm);i++)  
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

	x->myBeeThree = new BeeThree(); 	
	x->myFMVoices = new FMVoices(); 
	x->myHevyMetl = new HevyMetl(); 
	x->myPercFlut = new PercFlut(); 
	x->myRhodey   = new Rhodey(); 
	x->myTubeBell = new TubeBell(); 
	x->myWurley   = new Wurley(); 

	x->fm_type = 1;

    return (x);
}


//this gets called when an object is destroyed. do stuff here if you need to clean up.
void prc_fm_free(t_prc_fm *x)
{
	//gotta call this one, *before* you free other resources! thanks to Rob Sussman for pointing this out to me.
	dsp_free((t_pxobject *)x);
	
	delete x->myBeeThree;
    delete x->myFMVoices;
    delete x->myHevyMetl;
    delete x->myPercFlut;
    delete x->myRhodey;
    delete x->myTubeBell;
    delete x->myWurley;
}

//tells the user about the inputs/outputs when mousing over them
void prc_fm_assist(t_prc_fm *x, void *b, long m, long a, char *s)
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
void prc_fm_float(t_prc_fm *x, double f)
{
	int i;
	
	//check to see which input the float came in, then set the appropriate variable value
	for(i=0;i<x->num_inputs;i++) {
		if (x->x_obj.z_in == i) {
			x->in[i] = f;
			post("prc_fm~: setting in[%d] =  %f", i, f);
		}
	}
}


//what to do when we get the message "mymessage" and a value (or list of values)
void prc_fm_setpower(t_prc_fm *x, t_symbol *s, long argc, t_atom *argv)
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

void prc_fm_controlchange(t_prc_fm *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp[2];
    
	if(argc<2) {
		post("prc_fm~ error: need two arguments, control number and control value\n");
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
	
	switch(x->fm_type) {
		case 1:
			x->myBeeThree->controlChange((int)temp[0], temp[1]);
			break;
		case 2:
			x->myFMVoices->controlChange((int)temp[0], temp[1]);
			break;
		case 3:
			x->myHevyMetl->controlChange((int)temp[0], temp[1]);
			break;
		case 4:
			x->myPercFlut->controlChange((int)temp[0], temp[1]);
			break;
		case 5:
			x->myRhodey->controlChange((int)temp[0], temp[1]);
			break;
		case 6:
			x->myTubeBell->controlChange((int)temp[0], temp[1]);
			break;
		case 7:
			x->myWurley->controlChange((int)temp[0], temp[1]);
			break;
	}
}

void prc_fm_noteon(t_prc_fm *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp[2];
    
	if(argc<2) {
		post("prc_fm~ error: need two arguments, frequency and amplitude\n");
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
	
	switch(x->fm_type) {
		case 1:
			x->myBeeThree->noteOn((int)temp[0], temp[1]);
			break;
		case 2:
			x->myFMVoices->noteOn((int)temp[0], temp[1]);
			break;
		case 3:
			x->myHevyMetl->noteOn((int)temp[0], temp[1]);
			break;
		case 4:
			x->myPercFlut->noteOn((int)temp[0], temp[1]);
			break;
		case 5:
			x->myRhodey->noteOn((int)temp[0], temp[1]);
			break;
		case 6:
			x->myTubeBell->noteOn((int)temp[0], temp[1]);
			break;
		case 7:
			x->myWurley->noteOn((int)temp[0], temp[1]);
			break;
	}
}

void prc_fm_noteoff(t_prc_fm *x, t_symbol *s, long argc, t_atom *argv)
{
	switch(x->fm_type) {
		case 1:
			x->myBeeThree->noteOff(0.);
			break;
		case 2:
			x->myFMVoices->noteOff(0.);
			break;
		case 3:
			x->myHevyMetl->noteOff(0.);
			break;
		case 4:
			x->myPercFlut->noteOff(0.);
			break;
		case 5:
			x->myRhodey->noteOff(0.);
			break;
		case 6:
			x->myTubeBell->noteOff(0.);
			break;
		case 7:
			x->myWurley->noteOff(0.);
			break;
	}
}

void prc_fm_settype(t_prc_fm *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	long temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = argv[i].a_w.w_long;
				//probably should comment these out when the object is debugged.
    			//post("template~: power = %d", x->power);
				break;
			case A_FLOAT:
				temp = (long)argv[i].a_w.w_float;
    			//post("template~: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
	
	switch(temp) {
		case 1:
			post("prc_fm~: BeeThree\n");
			x->fm_type = 1;
			break;
		case 2:
			post("prc_fm~: FMVoices\n");
			x->fm_type = 2;
			break;
		case 3:
			post("prc_fm~: HevyMetl\n");
			x->fm_type = 3;
			break;
		case 4:
			post("prc_fm~: PercFlut\n");
			x->fm_type = 4;
			break;
		case 5:
			post("prc_fm~: Rhodey\n");
			x->fm_type = 5;
			break;
		case 6:
			post("prc_fm~: TubeBell\n");
			x->fm_type = 6;
			break;
		case 7:
			post("prc_fm~: Wurley\n");
			x->fm_type = 7;
			break;
	}
}

void prc_fm_dsp64(t_prc_fm *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	int i;
    
	//set sample rate vars
	x->srate = samplerate;
	x->one_over_srate = 1./x->srate;
	
	//check to see if there are signals connected to the various inputs
	for(i=0;i<x->num_inputs;i++) x->in_connected[i]	= count[i];
    
    object_method(dsp64, gensym("dsp_add64"), x, prc_fm_perform64, 0, NULL);
}

void prc_fm_perform64(t_prc_fm *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
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
	
	//check to see if we have a signal or t_double message connected to input
	//then assign the pointer accordingly
	for (i=0;i<x->num_inputs;i++) {
		in[i] = x->in_connected[i] ? (t_double *)(ins[i]) : &x->in[i];
	}
	
	//assign the output vectors
	for (i=0;i<x->num_outputs;i++) {
		out[i] = (t_double *)(outs[i]);
	}
    
	switch(x->fm_type) {
		case 1:
			while(n--) {
				*out[0]++ = x->myBeeThree->tick();
			}
			break;
		case 2:
			while(n--) {
				*out[0]++ = x->myFMVoices->tick();
			}
			break;
		case 3:
			while(n--) {
				*out[0]++ = x->myHevyMetl->tick();
			}
			break;
		case 4:
			while(n--) {
				*out[0]++ = x->myPercFlut->tick();
			}
			break;
		case 5:
			while(n--) {
				*out[0]++ = x->myRhodey->tick();
			}
			break;
		case 6:
			while(n--) {
				*out[0]++ = x->myTubeBell->tick();
			}
			break;
		case 7:
			while(n--) {
				*out[0]++ = x->myWurley->tick();
			}
			break;
	}	

}
