// waffle~ -- interpolates between two or more wavetable 'frames' stored in a buffer.
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

#define MAXFRAMES 32

t_class *waffle_class;

typedef struct _waffle
{
    t_pxobject l_obj;
} t_waffle;

float FConstrain(float v, float lo, float hi);
long IConstrain(long v, long lo, long hi);

void *waffle_new(void);
void waffle_assist(t_waffle *x, void *b, long m, long a, char *s);

// dsp stuff
void waffle_dsp64(t_waffle *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void waffle_perform64(t_waffle *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_symbol *ps_buffer;

void ext_main(void* p)
{
    t_class *c = class_new("waffle~", (method)waffle_new, (method)dsp_free, (long)sizeof(t_waffle), 0L, 0);
    
    class_addmethod(c, (method)waffle_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)waffle_dsp64, "dsp64", A_CANT, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    waffle_class = c;
	post("waffle waffle waffle...");
}

long IConstrain(long v, long lo, long hi)
{
	if (v < lo)
		return lo;
	else if (v > hi)
		return hi;
	else
		return v;
}

float FConstrain(float v, float lo, float hi)
{
	if (v < lo)
		return lo;
	else if (v > hi)
		return hi;
	else
		return v;
}

void waffle_assist(t_waffle *x, void *b, long m, long a, char *s)
{
    switch(m) {
        case 1: // inlet
            switch(a) {
                case 0:
                    sprintf(s, "(signal) Input");
                    break;
                case 1:
                    sprintf(s, "(signal) Crossover");
                    break;
                case 2:
                    sprintf(s, "(signal) Sync");
                    break;
            }
            break;
        case 2: // outlet
            switch(a) {
                case 0:
                    sprintf(s, "(signal) Low Output");
                    break;
                case 1:
                    sprintf(s, "(signal) High Output");
                    break;
            }
            break;
    }
    
}

void *waffle_new(void)
{
    t_waffle *x = (t_waffle *)object_alloc(waffle_class);
    dsp_setup((t_pxobject *)x, 3);
    outlet_new((t_object *)x, "signal");
    outlet_new((t_object *)x, "signal");
    return (x);
}

void waffle_dsp64(t_waffle *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, waffle_perform64, 0, NULL);
}

void waffle_perform64(t_waffle *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    t_double *in = (t_double *)(ins[0]);
    t_double *cross = (t_double *)(ins[1]);
    t_double *sync = (t_double *)(ins[2]);
    t_double *out1 = (t_double *)(outs[0]);
    t_double *out2 = (t_double *)(outs[1]);
    int n = sampleframes;
    if (x->l_obj.z_disabled)
        return;
    
    while (--n) {
        if(*++sync<*++cross) {
            *++out1 = *++in;
            *++out2 = 0.;
        }
        else {
            *++out1 = 0;
            *++out2 = *++in;
        }
    }
}

