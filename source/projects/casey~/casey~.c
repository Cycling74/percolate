// only let the top n samples through in a vector.
// by r. luke dubois, cmc/cu, 2005.
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include <math.h>
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

t_class *sigcasey_class;

typedef struct _sigcasey
{
    t_pxobject x_obj;
    t_double x_val;
    t_double x_biggest;
} t_sigcasey;

void *sigcasey_new(double val);
void sigcasey_float(t_sigcasey *x, double f);
void sigcasey_int(t_sigcasey *x, long n);
void sigcasey_bang(t_sigcasey *x);
void sigcasey_assist(t_sigcasey *x, void *b, long m, long a, char *s);

void sigcasey_dsp64(t_sigcasey *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void sigcasey_perform64(t_sigcasey *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void sigcasey_2perform64(t_sigcasey *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void ext_main(void* p)
{
    t_class *c = class_new("casey~", (method)sigcasey_new, (method)dsp_free, (long)sizeof(t_sigcasey), 0L, A_DEFFLOAT, 0);
    
    class_addmethod(c, (method)sigcasey_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)sigcasey_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)sigcasey_bang, "bang", A_CANT, 0);
    class_addmethod(c, (method)sigcasey_int, "int", A_LONG, 0);
    class_addmethod(c, (method)sigcasey_float, "float", A_FLOAT, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    sigcasey_class = c;
    post("casey~: by r. luke dubois, cmc");
}

void sigcasey_assist(t_sigcasey *x, void *b, long m, long a, char *s)
{
	switch(m) {
		case 1: // inlet
			switch(a) {
				case 0:
				sprintf(s, "(Signal) Input");
				break;
				case 1:
				sprintf(s, "(Signal) Top N in Vector");
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

void *sigcasey_new(double val)
{
    t_sigcasey *x = (t_sigcasey *)object_alloc(sigcasey_class);
    if (x) {
        dsp_setup((t_pxobject *)x,2);
        outlet_new((t_pxobject *)x, "signal");
        if(val > 0.0) {
            x->x_val = val;
        } else {
            x->x_val = 1.0;
        }
        x->x_biggest = 0.;
    }
    return (x);
}

void sigcasey_bang(t_sigcasey *x)
{
	post("x is %f", x->x_biggest);
}

// this routine covers both inlets. It doesn't matter which one is involved

void sigcasey_float(t_sigcasey *x, double f)
{
	x->x_val = f;
}

void sigcasey_int(t_sigcasey *x, long n)
{
	x->x_val = (float)n;
}

void sigcasey_dsp64(t_sigcasey *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	if (!count[0])
        object_method(dsp64, gensym("dsp_add64"), x, sigcasey_perform64, 0, NULL);
	else if (!count[1])
        object_method(dsp64, gensym("dsp_add64"), x, sigcasey_perform64, 0, NULL);
	else
        object_method(dsp64, gensym("dsp_add64"), x, sigcasey_2perform64, 0, NULL);
}

void sigcasey_perform64(t_sigcasey *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    t_double *in = (t_double *)(ins[0]);
    t_double *out = (t_double *)(outs[0]);
	int n = sampleframes;

	long val = (long)fabs(x->x_val);
	float lastbiggest = 0.;
	int bigsofar = 0;
	float inval;
	int used[8192];
	int i;

	for(i=0;i<8192;i++) {
		used[i] = 0;
	}
	
	for(i=0;i<val;i++)
	{
		n = sampleframes;
		in = (t_double *)(ins[0]);
		bigsofar = 0;
		lastbiggest = 0;
		while (--n) {
			inval = *++in;
			if((inval>lastbiggest)&&(used[n]==0))
			{
				bigsofar = n;
				lastbiggest = inval;
			}
            
		}
		used[bigsofar] = 1;
	}
    
	n = sampleframes;
	in = (t_double *)(ins[0]);
	while (--n)
	{
		*++out = *++in * used[n];
	}
    
    x->x_biggest = val;
}

void sigcasey_2perform64(t_sigcasey *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double *in1,*in2,*out;
	int n;
	float inval, val;
    
    /*
	if (*(long *)(w[1]))
	    goto out;
    */
    
	in1 = (t_double *)(ins[0]);
	in2 = (t_double *)(ins[1]);
	out = (t_double *)(outs[0]);
	n = sampleframes;
    
	while (--n) {
		inval = *++in1;
		val = fabs(*++in2);
    	if (fabs(inval) > val) {
    		if(inval >= 0) {
	    		*++out = val - (inval-val);
	    	} else {
	    		*++out = (0.-val)+((fabs(inval))-val);
	    	}
    	}
		else {
    		*++out = inval;
    	}
	}
}

