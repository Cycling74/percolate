// klutz~ -- reverses the order of samples in a vector.
// 		by r. luke dubois (luke@music.columbia.edu), 
//			computer music center, columbia university, 2001.
//
// objects and source are provided without warranty of any kind, express or implied.
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

// include files...
// #include <stdlib.h>
#include "math.h"
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

// global for the class definition
t_class *klutz_class;

// my object structure
typedef struct _klutz
{
    t_pxobject r_obj; // this is an msp object...
} t_klutz;

void *klutz_new(float flag, float a); // creation function
void klutz_assist(t_klutz *x, void *b, long m, long a, char *s); // assistance function

// dsp stuff
void klutz_dsp64(t_klutz *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void klutz_perform64(t_klutz *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void ext_main(void* p)
{
    t_class *c = class_new("klutz~", (method)klutz_new, (method)dsp_free, (long)sizeof(t_klutz), 0L, A_DEFFLOAT, A_DEFFLOAT, 0);
    class_addmethod(c, (method)klutz_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)klutz_dsp64, "dsp64", A_CANT, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    klutz_class = c;
	post("klutz~: by r. luke dubois, cmc");
}

// deal with the assistance strings...
void klutz_assist(t_klutz *x, void *b, long m, long a, char *s)
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
void *klutz_new(float flag, float a)
{	
    t_klutz *x = (t_klutz *)object_alloc(klutz_class);
    dsp_setup((t_pxobject *)x,1);
    outlet_new((t_pxobject *)x, "signal");

    return (x);
}


void klutz_dsp64(t_klutz *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, klutz_perform64, 0, NULL);
}

void klutz_perform64(t_klutz *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double *in, *out; // variables for input and output buffer
	int n; // counter for vector size
    
	in = (t_double *)(ins[0]);
	out = (t_double *)(outs[0]); // my output vector
    
	for (n=0; n<sampleframes; n++) {
		*++in; // my vector size
	}

	while(--n) {
	    *++out = *--in;
	}
}

