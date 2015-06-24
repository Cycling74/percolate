// escal~ -- signal operator to round signals in three ways.
// 		by r. luke dubois (luke@music.columbia.edu), 
//			computer music center, columbia university, 2000.
//
// objects and source are provided without warranty of any kind, express or implied.
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

// include files...
#include <math.h>
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

// global for the class definition
t_class *escal_class;

// my object structure
typedef struct _escal
{
    t_pxobject e_obj; // this is an msp object...
    long roundstate; // three-way flag for rounding operation
	void *e_proxy[1]; // a proxy inlet for setting the rounding flag
	long e_inletnumber; // inlet number for the proxy
} t_escal;

void *escal_new(long flag); // creation function
void escal_free(t_escal *x); // free function (we use proxies, so can't just be dsp_free()
void escal_assist(t_escal *x, void *b, long m, long a, char *s); // assistance function

void escal_int(t_escal *x, long n); // what to do with an int

// dsp stuff
void escal_dsp64(t_escal *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void escal_perform64(t_escal *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);


void ext_main(void* p)
{
    post("Verifying update.");
    t_class *c = class_new("escal~", (method)escal_new, (method)escal_free, (long)sizeof(t_escal), 0L, A_DEFLONG, 0);
    
    class_addmethod(c, (method)escal_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)escal_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)escal_int, "int", A_LONG, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    escal_class = c;
	post("escal~: by r. luke dubois, cmc");
}

// deal with the assistance strings...
void escal_assist(t_escal *x, void *b, long m, long a, char *s)
{
	switch(m) {
		case 1: // inlet
			switch(a) {
				case 0:
				sprintf(s, "(signal) Input");
				break;
				case 1:
				sprintf(s, "(int) Round Type (-1, 0, 1)");
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
void *escal_new(long flag)
{	
    t_escal *x = (t_escal *)object_alloc(escal_class);
    if (x) {
        dsp_setup((t_pxobject *)x,1);
        x->e_proxy[0] = proxy_new(x,1L,&x->e_inletnumber);
        outlet_new((t_pxobject *)x, "signal");
        x->roundstate = 1; // initialize argument
        
        // if the arguments are there check them and set them
        if(flag) x->roundstate = flag;
	    if (x->roundstate < -1) x->roundstate = -1;
	    if (x->roundstate > 1) x->roundstate = 1;

        if (x->roundstate<-1) x->roundstate=-1;
        if (x->roundstate>1) x->roundstate=1;
    }

    return (x);
}

void escal_free(t_escal *x)
{
	freeobject(x->e_proxy[0]); // flush the proxies
	dsp_free(&x->e_obj); // flush the dsp memory
}

// this routine covers both inlets. It doesn't matter which one is involved
void escal_int(t_escal *x, long n)
{
	if (x->e_inletnumber==1) { // 'minimum' value
		x->roundstate = n;
	    if (x->roundstate < -1) x->roundstate = -1;
	    if (x->roundstate > 1) x->roundstate = 1;
	}
}

void escal_dsp64(t_escal *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, escal_perform64, 0, NULL);
}

void escal_perform64(t_escal *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double *in,*out; // variables for input and output buffer
	int n; // counter for vector size
    
	// more efficient -- make local copies of class variables so i'm not constantly checking the globals...
	int flag = x->roundstate;
    
	in = (t_double *)(ins[0]); // my input vector
	out = (t_double *)(outs[0]); // my output vector
    
	n = sampleframes; // my vector size
    
	while (--n) { // loop executes a single vector
		switch(flag) {
			case(-1): // round low
                *out++ = floor(*in++);
				break;
			case(0): // round normally
                *out++ = round(*in++);
				break;
			case(1): // round up
                *out++ = ceil(*in++);
                break;
		}
	}
}
