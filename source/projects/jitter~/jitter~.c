// jitter~ -- modifies an incoming signal by a jitter amount of jitter.
// 		by r. luke dubois (luke@music.columbia.edu), 
//			computer music center, columbia university, 2000.
//
// objects and source are provided without warranty of any kind, express or implied.
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

// include files...
#include <stdlib.h>
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

// global for the class definition
t_class *jitter_class;

// my object structure
typedef struct _jitter
{
    t_pxobject r_obj; // this is an msp object...
    float range; // range of jitter generation
	long aflag; // whether to jitter at audio rate or when banged
	float jitter;
} t_jitter;

void *jitter_new(double flag, double a); // creation function
void jitter_assist(t_jitter *x, void *b, long m, long a, char *s); // assistance function
void jitter_bang(t_jitter *x); // bang function

void jitter_range(t_jitter *x, long n); // set jitter range
void jitter_manual(t_jitter *x, long n); // set jitter auto flag

// dsp stuff
void jitter_dsp64(t_jitter *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void jitter_perform64(t_jitter *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void ext_main(void* p)
{
    t_class *c = class_new("jitter~", (method)jitter_new, (method)dsp_free, (long)sizeof(t_jitter), 0L, A_DEFFLOAT, A_DEFFLOAT, 0);
    
    class_addmethod(c, (method)jitter_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)jitter_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)jitter_range, "range", A_DEFLONG, 0);
    class_addmethod(c, (method)jitter_manual, "manual", A_DEFLONG, 0);
    class_addmethod(c, (method)jitter_bang, "bang", A_CANT, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    jitter_class = c;
	post("jitter~: by r. luke dubois, cmc");
}

// deal with the assistance strings...
void jitter_assist(t_jitter *x, void *b, long m, long a, char *s)
{
	switch(m) {
		case 1: // inlet
			switch(a) {
				case 0:
				sprintf(s, "(signal) Input");
				break;
			}
		break;
		case 2: // outlet
			switch(a) {
				case 0:
				sprintf(s, "(signal) Output");
				break;
			}
		break;
	}
}

// instantiate the object
void *jitter_new(double flag, double a)
{
    post("flag: %f; a-flag: %f", flag, a);
    
    t_jitter *x = (t_jitter *)object_alloc(jitter_class);
    if (x) {
        dsp_setup((t_pxobject *)x,1);
        outlet_new((t_pxobject *)x, "signal");
        x->range = 0.0; // initialize argument
        x->jitter = 0.0;
        
        // if the arguments are there check them and set them
        if (flag) x->range = flag;
        if (x->range<=0.0) x->range=0.0;
        if (x->range>65535) x->range=65535;

        if (a) {
            x->aflag = (long)a;
        } else {
            x->aflag = 0;
        }
        
        if (x->aflag<0) x->aflag = 0;
        if (x->aflag>1) x->aflag = 1;
    }

    return (x);
}

void jitter_bang(t_jitter *x)
{
	x->jitter = ( ( ((float)rand()/(float)RAND_MAX) * x->range) *2) - (x->range);
}

void jitter_range(t_jitter *x, long n)
{
		x->range = (float)n;
	    if (x->range<0.0) x->range = 0.0;
	    if (x->range>65535.) x->range = 65535.;
}

void jitter_manual(t_jitter *x, long n)
{
		x->aflag = n;
	    if (x->aflag<0) x->aflag = 0;
	    if (x->aflag>1) x->aflag = 1;
}

void jitter_dsp64(t_jitter *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, jitter_perform64, 0, NULL);
}

void jitter_perform64(t_jitter *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    t_double *in, *out;  // variables for input and output buffer
	int n;              // counter for vector size
    
	// more efficient -- make local copies of class variables so i'm not constantly checking the globals...
	double range = x->range;
	long aflag = x->aflag;
	double jitter = x->jitter;
    double temp;
    
	in = ins[0];
	out = outs[0]; // my output vector
    
	n = sampleframes; // my vector size
    
	while (--n) { // loop executes a single vector
        /*
		if(!aflag) *++out = *++in + ((((float)rand()/(float)RAND_MAX)*range)*2)-range;
		else *++out = *++in + jitter;
         */
        if (!aflag) {
            temp = *in++;
            temp += ((((float)rand()/(float)RAND_MAX)*range)*2)-range;
            *out++ = temp;
        } else {
            temp = *in++;
            temp += jitter;
            *out++ = temp;
        }
	}
}
