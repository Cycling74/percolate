// rnadom~ -- generates random numbers in a positive range at signal rate.
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
t_class *random_class;

// my object structure
typedef struct _random
{
    t_pxobject r_obj; // this is an msp object...
    long range; // range of random generation
	void *r_proxy[1]; // a proxy inlet for setting the rounding flag
	long r_inletnumber; // inlet number for the proxy
} t_random;

void *random_new(long flag); // creation function
void *random_free(t_random *x); // free function (we use proxies, so can't just be dsp_free()
void random_range(t_random *x, long n); // set random range
void random_assist(t_random *x, void *b, long m, long a, char *s); // assistance function

// dsp stuff
void random_dsp64(t_random *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void random_perform64(t_random *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void ext_main(void* p)
{
    t_class *c = class_new("random~", (method)random_new, (method)random_free, (long)sizeof(t_random), 0L,A_DEFLONG, A_DEFLONG, 0);
    
    class_addmethod(c, (method)random_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)random_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)random_range, "range", A_DEFLONG, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    random_class = c;
	post("random~: by r. luke dubois, cmc");
    
}

// deal with the assistance strings...
void random_assist(t_random *x, void *b, long m, long a, char *s)
{
	switch(m) {
		case 1: // inlet
			switch(a) {
				case 0:
				sprintf(s, "Messages...");
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
void *random_new(long flag)
{	
    t_random *x = (t_random *)object_alloc(random_class);
    dsp_setup((t_pxobject *)x,0);
    outlet_new((t_pxobject *)x, "signal");
	x->range = 1000; // initialize argument
	
	// if the arguments are there check them and set them
	if(flag) x->range = flag;

    if (x->range<1) x->range=1;
    if (x->range>65535) x->range=65535;

    return (x);
}

void *random_free(t_random *x)
{
	dsp_free(&x->r_obj); // flush the dsp memory
    return 0;
}

void random_range(t_random *x, long n)
{
		x->range = n;
	    if (x->range<1) x->range = 1;
	    if (x->range>65535) x->range = 65535;
}

void random_dsp64(t_random *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, random_perform64, 0, NULL);
}

void random_perform64(t_random *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double *out; // variables for input and output buffer
	int n; // counter for vector size
    
	// more efficient -- make local copies of class variables so i'm not constantly checking the globals...
	int range = x->range;
    
	out = (t_double *)(outs[0]); // my output vector
    
	n = sampleframes; // my vector size
    
	while (--n) { // loop executes a single vector
		*++out = ((float)rand()/(float)RAND_MAX)*(float)range;
        
	}
    

}
