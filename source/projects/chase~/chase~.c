// chase~ -- uses a sync signal to determine who gets out which outlet.
//
// updated for Max 7 by Darwin Grosse and Tim Place
// -------------------------------------------------

#include <math.h>
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

#define MAXFRAMES 32

t_class *chase_class;

typedef struct _chase
{
    t_pxobject l_obj;
} t_chase;

float FConstrain(float v, float lo, float hi);
long IConstrain(long v, long lo, long hi);

void *chase_new(void);
void chase_assist(t_chase *x, void *b, long m, long a, char *s);

void chase_dsp64(t_chase *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void chase_perform64(t_chase *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_symbol *ps_buffer;

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

void ext_main(void* p)
{
    t_class *c = class_new("chase~", (method)chase_new, (method)dsp_free, (long)sizeof(t_chase), 0L, 0);
    class_addmethod(c, (method)chase_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)chase_dsp64, "dsp64", A_CANT, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    chase_class = c;
	post("chase chase chase...");
}

void *chase_new(void)
{
	t_chase *x = (t_chase *)object_alloc(chase_class);
    if (x) {
        dsp_setup((t_pxobject *)x, 3);
        outlet_new((t_object *)x, "signal");
        outlet_new((t_object *)x, "signal");
    }
	return (x);
}

void chase_assist(t_chase *x, void *b, long m, long a, char *s)
{
	switch(m) {
		case 1: // inlet
			switch(a) {
				case 0:
                    sprintf(s, "(signal) Input 1");
                    break;
				case 1:
                    sprintf(s, "(signal) Input 2");
                    break;
				case 2:
                    sprintf(s, "(signal) Sync");
                    break;
			}
            break;
		case 2: // outlet
			switch(a) {
				case 0:
                    sprintf(s, "(signal) Near Output");
                    break;
				case 1:
                    sprintf(s, "(signal) Far Output");
                    break;
			}
            break;
	}
    
}

void chase_dsp64(t_chase *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, chase_perform64, 0, NULL);
}

void chase_perform64(t_chase *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    t_double *in1 = (t_double *)(ins[0]);
    t_double *in2 = (t_double *)(ins[1]);
    t_double *sync = (t_double *)(ins[2]);
    t_double *out1 = (t_double *)(outs[0]);
    t_double *out2 = (t_double *)(outs[1]);
    int n = sampleframes;
    
    double dist1, dist2;
	
	while (--n) {
		if(*++sync>*++in1) {
            dist1 = fabs(*sync-*in1);
		}
		else {
            dist1 = fabs(*in1-*sync);
		}
		if(*sync>*++in2) {
            dist2 = fabs(*sync-*in1);
		}
		else {
            dist2 = fabs(*in2 - *sync);
		}
		if(dist1>dist2) {
            *++out1 = dist1;
            *++out2 = dist2;
		}
		else {
            *++out1 = dist2;
            *++out2 = dist1;
		}
	}
}


