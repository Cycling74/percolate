// threshhold-based wraparound thingy.
// by r. luke dubois, cmc/cu, 2000.
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include <math.h>
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

t_class *sigflip_class;

typedef struct _sigflip
{
    t_pxobject x_obj;
    t_double x_val;
} t_sigflip;

void *sigflip_new(double val);
void sigflip_assist(t_sigflip *x, void *b, long m, long a, char *s);

void sigflip_int(t_sigflip *x, long n);
void sigflip_float(t_sigflip *x, double f);

// dsp stuff
void sigflip_dsp64(t_sigflip *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void sigflip_perform64(t_sigflip *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void sigflip_perform264(t_sigflip *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void ext_main(void* p)
{
    t_class *c = class_new("flip~", (method)sigflip_new, (method)dsp_free, (long)sizeof(t_sigflip), 0L, A_DEFFLOAT, 0);
    
    class_addmethod(c, (method)sigflip_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)sigflip_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)sigflip_float, "float", A_FLOAT, 0);
    class_addmethod(c, (method)sigflip_int, "int", A_LONG, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    sigflip_class = c;
    post("flip~: by r. luke dubois, cmc");
}

void sigflip_assist(t_sigflip *x, void *b, long m, long a, char *s)
{
	switch(m) {
		case 1: // inlet
			switch(a) {
				case 0:
				sprintf(s, "(Signal) Input");
				break;
				case 1:
				sprintf(s, "(Signal) Wraparound Threshhold");
				break;
			}
		break;
		case 2: // outlet
			switch(a) {
				case 0:
				sprintf(s, "(Signal) Output");
				break;
			}
		break;
	}
}

void *sigflip_new(double val)
{
    t_sigflip *x = (t_sigflip *)object_alloc(sigflip_class);
    if (x) {
        dsp_setup((t_pxobject *)x,2);
        outlet_new((t_pxobject *)x, "signal");
        x->x_val = val;
    }
    return (x);
}

// this routine covers both inlets. It doesn't matter which one is involved
void sigflip_float(t_sigflip *x, double f)
{
	x->x_val = f;
}

void sigflip_int(t_sigflip *x, long n)
{
	x->x_val = (float)n;
}

void sigflip_dsp64(t_sigflip *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    if (!count[0]) {
        object_method(dsp64, gensym("dsp_add64"), x, sigflip_perform64, 0, NULL);
    } else if (~count[1]) {
        object_method(dsp64, gensym("dsp_add64"), x, sigflip_perform64, 0, NULL);
    } else {
        object_method(dsp64, gensym("dsp_add64"), x, sigflip_perform264, 0, NULL);
    }
}

void sigflip_perform64(t_sigflip *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    t_double *in = (t_double *)(ins[0]);
    t_double *out = (t_double *)(ins[1]);
    
	double val = fabs(x->x_val);
	double inval;
	int n = sampleframes;
	
	while (--n) {
		inval = *++in;
    	if (fabs(inval)>val) {
    		if(inval>=0) {
	    		*++out = val-(inval-val);
	    	}
	    	else {
	    		*++out = (0.-val)+((fabs(inval))-val);
	    	}
    	}
		else {
    		*++out = inval;
    	}
	}
}

void sigflip_perform264(t_sigflip *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double *in1,*in2,*out;
	long n;
	double inval, val;
    
	in1 = (t_double *)(ins[0]);
	in2 = (t_double *)(ins[1]);
	out = (t_double *)(outs[0]);
	n = sampleframes;
    
	while (--n) {
		inval = *++in1;
		val = fabs(*++in2);
    	if (fabs(inval)>val) {
    		if(inval>=0) {
	    		*++out = val-(inval-val);
	    	}
	    	else {
	    		*++out = (0.-val)+((fabs(inval))-val);
	    	}
    	}
		else {
    		*++out = inval;
    	}
	}
}
