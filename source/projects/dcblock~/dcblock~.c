// updated for Max 7 by Darwin Grosse and Tim Place
// -------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

//#define TWOPI 6.283185307

t_class *dcblock_class;

typedef struct _dcblock
{
	//header; keep this
    t_pxobject x_obj;

    //DC blocker
    double dc_input, dc_output;
    double srate, one_over_srate;
} t_dcblock;

/****PROTOTYPES****/

//setup funcs; needed for all objects
void *dcblock_new(double val); //called when the object is created
void dcblock_assist(t_dcblock *x, void *b, long m, long a, char *s); //for getting assistance when rolling mouse over inputs/outputs

// dsp stuff
void dcblock_dsp64(t_dcblock *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void dcblock_perform64(t_dcblock *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

//DC blocker
float dcblock_tick(t_dcblock *x, float sample); //my own method; high-pass filter


/****FUNCTIONS****/

void ext_main(void* p)
{
    t_class *c = class_new("dcblock~", (method)dcblock_new, (method)dsp_free, (long)sizeof(t_dcblock), 0L, 0);
    
    class_addmethod(c, (method)dcblock_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)dcblock_dsp64, "dsp64", A_CANT, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    dcblock_class = c;
}

//one argument (as specified in the "setup" call above, which isn't actually used in this particular object
void *dcblock_new(double initial_coeff)
{
	int i;
    
	//new object
    t_dcblock *x = (t_dcblock *)object_alloc(dcblock_class);
    
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) {
        for(i=sizeof(t_pxobject);i<sizeof(t_dcblock);i++) {
            ((char *)x)[i]=0;
        }
	
        //set it up, with the number of audio inputs that you want
        dsp_setup((t_pxobject *)x,1);
        
        //set up the number of outputs that you want
        outlet_new((t_object *)x, "signal");
        
        //init variables
        x->dc_input = 0.;
        x->dc_output = 0.;
    }
    
    return (x);
}

void dcblock_assist(t_dcblock *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
        sprintf(s,"(signal) input");
	} else {
		sprintf(s,"(signal) output");
    }
}


//DC blocker
float dcblock_tick(t_dcblock *x, float sample)
{
	x->dc_output = sample - x->dc_input + (0.99 * x->dc_output);
	x->dc_input = sample;
	return x->dc_output;
}

void dcblock_dsp64(t_dcblock *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	//initialize sampling rate
	x->srate = samplerate;
	x->one_over_srate = 1./x->srate;
    
    object_method(dsp64, gensym("dsp_add64"), x, dcblock_perform64, 0, NULL);
}

void dcblock_perform64(t_dcblock *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	//get the in and out signal vector pointers (corresponds to places in the dsp_add call above)
	double *in = (double *)(ins[0]);
	double *out = (double *)(outs[0]);
	
	//get the vector size
	long n = sampleframes;
	
	//run the effect loop, for each sample in the vector
	while(n--) {
		//out is a pointer to the first sample in the output vector
		//in is a pointer to the first sample of the input vector
		//we have to manually increment these after we access them
		*out++ = dcblock_tick(x, *in++);
	}
}


