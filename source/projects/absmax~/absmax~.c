// ------------------------------------------------------------------
// returns the maximum value of a signal based on absolute values.
// by r. luke dubois, cmc/cu, 2001.
//
// updated 2015 for Max 7, by Darwin Grosse and Tim Place
// ------------------------------------------------------------------

#include <math.h>
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

typedef struct _sigabsmax
{
    t_pxobject x_obj;
    t_float x_val;
} t_sigabsmax;

void *sigabsmax_new(double val);
void sigabsmax_float(t_sigabsmax *x, double f);
void sigabsmax_assist(t_sigabsmax *x, void *b, long m, long a, char *s);

void sigabsmax_dsp64(t_sigabsmax *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void sigabsmax1_perform64(t_sigabsmax *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void sigabsmax2_perform64(t_sigabsmax *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

static t_class *sigabsmax_class = NULL;

//***********************************************************************************************

void ext_main(void* p)
{
    t_class *c = class_new("absmax~", (method)sigabsmax_new, (method)dsp_free, (long)sizeof(t_sigabsmax), 0L, A_DEFFLOAT, 0);
    
    class_addmethod(c, (method)sigabsmax_float, "float", A_FLOAT, 0);
    class_addmethod(c, (method)sigabsmax_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)sigabsmax_assist, "assist", A_CANT, 0);

    class_dspinit(c);
    class_register(CLASS_BOX, c);
    sigabsmax_class = c;
    
    post("absmax~: by r. luke dubois, cmc");
}

void *sigabsmax_new(double val)
{
    t_sigabsmax *x = (t_sigabsmax *)object_alloc(sigabsmax_class);
    
    if (x) {
		dsp_setup((t_pxobject *)x, 2);
		outlet_new(x, "signal");
        x->x_val = val;
    }
    return (x);
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

// this routine covers both inlets. It doesn't matter which one is involved
void sigabsmax_float(t_sigabsmax *x, double f)
{
	x->x_val = f;
}

void sigabsmax_dsp64(t_sigabsmax *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    if (!count[0]) {
        object_method(dsp64, gensym("dsp_add64"), x, sigabsmax1_perform64, 0, NULL);
    } else if (!count[1]) {
        object_method(dsp64, gensym("dsp_add64"), x, sigabsmax1_perform64, 0, NULL);
    } else {
        object_method(dsp64, gensym("dsp_add64"), x, sigabsmax2_perform64, 0, NULL);
    }
}

void sigabsmax1_perform64(t_sigabsmax *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    t_double *in = ins[0];
    t_double *out = outs[0];
    t_float val1;
    t_float val2 = x->x_val;
    
    int n = sampleframes;
    
    while (n--) {
        val1 = *in++;
        if (fabs(val1) >= fabs(val2)) {
            *out++ = val1;
        } else {
            *out++ = val2;
        }
    }
}

void sigabsmax2_perform64(t_sigabsmax *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    t_double *in1 = ins[0];
    t_double *in2 = ins[1];
    t_double *out = outs[0];
    t_float val1, val2;
    
    int n = sampleframes;

    while (n--) {
        val1 = *in1++;
        val2 = *in2++;
        if (fabs(val1) >= fabs(val2)) {
            *out++ = val1;
        } else {
            *out++ = val2;
        }
    }
}


