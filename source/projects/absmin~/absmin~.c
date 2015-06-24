// ------------------------------------------------------------------
// returns the minimum value of a signal based on absolute values.
// by r. luke dubois, cmc/cu, 2001.
//
// updated 2015 for Max 7, by Darwin Grosse and Tim Place
// ------------------------------------------------------------------

#include <math.h>
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

typedef struct _sigabsmin
{
    t_pxobject x_obj;
    t_float x_val;
} t_sigabsmin;

void *sigabsmin_new(double val);
void sigabsmin_float(t_sigabsmin *x, double f);
void sigabsmin_assist(t_sigabsmin *x, void *b, long m, long a, char *s);

void sigabsmin_dsp64(t_sigabsmin *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void sigabsmin1_perform64(t_sigabsmin *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void sigabsmin2_perform64(t_sigabsmin *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

static t_class *sigabsmin_class = NULL;

//***********************************************************************************************

void ext_main(void* p)
{
    t_class *c = class_new("absmin~", (method)sigabsmin_new, (method)dsp_free, (long)sizeof(t_sigabsmin), 0L, A_DEFFLOAT, 0);
    
    class_addmethod(c, (method)sigabsmin_float, "float", A_FLOAT, 0);
    class_addmethod(c, (method)sigabsmin_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)sigabsmin_assist, "assist", A_CANT, 0);
    
    class_dspinit(c);
    class_register(CLASS_BOX, c);
    sigabsmin_class = c;
    
    post("absmin~: by r. luke dubois, cmc");
}

void *sigabsmin_new(double val)
{
    t_sigabsmin *x = (t_sigabsmin *)object_alloc(sigabsmin_class);
    
    if (x) {
		dsp_setup((t_pxobject *)x, 2);
		outlet_new(x, "signal");
        x->x_val = val;
    }
    return (x);
}

void sigabsmin_assist(t_sigabsmin *x, void *b, long m, long a, char *s)
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
void sigabsmin_float(t_sigabsmin *x, double f)
{
	x->x_val = f;
}

void sigabsmin_dsp64(t_sigabsmin *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    if (!count[0]) {
        object_method(dsp64, gensym("dsp_add64"), x, sigabsmin1_perform64, 0, NULL);
    } else if (!count[1]) {
        object_method(dsp64, gensym("dsp_add64"), x, sigabsmin1_perform64, 0, NULL);
    } else {
        object_method(dsp64, gensym("dsp_add64"), x, sigabsmin2_perform64, 0, NULL);
    }
}

void sigabsmin1_perform64(t_sigabsmin *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    t_double *in = ins[0];
    t_double *out = outs[0];
    t_float val1;
    t_float val2 = x->x_val;
    
    int n = sampleframes;
    
    while (n--) {
        val1 = *in++;
        if (fabs(val1) <= fabs(val2)) {
            *out++ = val1;
        } else {
            *out++ = val2;
        }
    }
}

void sigabsmin2_perform64(t_sigabsmin *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    t_double *in1 = ins[0];
    t_double *in2 = ins[1];
    t_double *out = outs[0];
    t_float val1, val2;
    
    int n = sampleframes;
    
    while (n--) {
        val1 = *in1++;
        val2 = *in2++;
        if (fabs(val1) <= fabs(val2)) {
            *out++ = val1;
        } else {
            *out++ = val2;
        }
    }
}
