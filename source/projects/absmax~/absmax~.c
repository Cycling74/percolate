// returns the maximum value of a signal based on absolute values.
// by r. luke dubois, cmc/cu, 2001.

#include <math.h>
#include "ext.h"
#include "z_dsp.h"

void *sigabsmax_class;

typedef struct _sigabsmax
{
    t_pxobject x_obj;
    t_float x_val;
} t_sigabsmax;

void *sigabsmax_new(double val);
void offset_perform64(t_sigabsmax *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void sigabsmax2_perform64(t_sigabsmax *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void sigabsmax_float(t_sigabsmax *x, double f);
void sigabsmax_int(t_sigabsmax *x, long n);
void sigabsmax_dsp(t_sigabsmax *x, t_signal **sp, short *count);
void sigabsmax_dsp64(t_sigabsmax *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void sigabsmax_assist(t_sigabsmax *x, void *b, long m, long a, char *s);

void ext_main(void* p)
{
    setup((t_messlist **)&sigabsmax_class, (method)sigabsmax_new, (method)dsp_free, (short)sizeof(t_sigabsmax), 0L, A_DEFFLOAT, 0);
    addmess((method)sigabsmax_dsp64, "dsp64", A_CANT, 0);
    addfloat((method)sigabsmax_float);
    addint((method)sigabsmax_int);
    addmess((method)sigabsmax_assist,"assist",A_CANT,0);
    dsp_initclass();
    
    post("absmax~: by r. luke dubois, cmc");
}

void sigabsmax_assist(t_sigabsmax *x, void *b, long m, long a, char *s)
{
	switch(m) {
		case 1: // inlet
			switch(a) {
				case 0:
				sprintf(s, "(Signal) Input 1");
				break;
				case 1:
				sprintf(s, "(Signal) Input 2");
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

void *sigabsmax_new(double val)
{
    t_sigabsmax *x = (t_sigabsmax *)newobject(sigabsmax_class);
    dsp_setup((t_pxobject *)x,2);
    outlet_new((t_pxobject *)x, "signal");
    x->x_val = val;
    return (x);
}

// this routine covers both inlets. It doesn't matter which one is involved

void sigabsmax_float(t_sigabsmax *x, double f)
{
	x->x_val = f;
}

void sigabsmax_int(t_sigabsmax *x, long n)
{
	x->x_val = (float)n;
}

void offset_perform64(t_sigabsmax *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    double *in = ins[0];
    double *out = outs[0];
	double val2 = fabs(x->x_val);
	double val1;
	int n = sampleframes;
	
	while (--n) {
		val1 = *++in;
    	if (fabs(val1)>=fabs(val2)) {
	    		*++out = val1;
    	}
		else {
    		*++out = val2;
    	}
	}
}

void sigabsmax2_perform64(t_sigabsmax *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	double *in1,*in2,*out;
	int n;
	double val1, val2;

	in1 = ins[0];
	in2 = ins[1];
	out = outs[0];
	n = sampleframes;
	while (--n) {
		val1 = *++in1;
		val2 = *++in2;
    	if (fabs(val1)>=fabs(val2)) {
	    		*++out = val1;
    	}
		else {
    		*++out = val2;
    	}
	}
}

void sigabsmax_dsp64(t_sigabsmax *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	long i;
		
	if (!count[0])
		object_method(dsp64, gensym("dsp_add64"), (t_object*)x, offset_perform64, 0, NULL);
	else if (!count[1])
		object_method(dsp64, gensym("dsp_add64"), (t_object*)x, offset_perform64, 0, NULL);
	else
		object_method(dsp64, gensym("dsp_add64"), (t_object*)x, sigabsmax2_perform64, 0, NULL);
}

