//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

#include "buffer.h"

t_class *indexi_class;

typedef struct _indexi
{
    t_pxobject l_obj;
    t_buffer_ref *l_buffer;
    long l_chan;
} t_indexi;

long Constrain(long v, long lo, long hi);

void *indexi_new(t_symbol *s, long chan);
void indexi_free(t_indexi *x);
t_max_err indexi_notify(t_indexi *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void indexi_assist(t_indexi *x, void *b, long m, long a, char *s);
void indexi_set(t_indexi *x, t_symbol *s);
void indexi_in1(t_indexi *x, long n);
void indexi_dblclick(t_indexi *x);

void indexi_dsp64(t_indexi *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void indexi_perform64(t_indexi *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_symbol *ps_buffer;

void ext_main(void* p)
{
    t_class *c = class_new("indexi~", (method)indexi_new, (method)indexi_free, (long)sizeof(t_indexi), 0L, A_SYM, A_DEFLONG, 0);
    
    class_addmethod(c, (method)indexi_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)indexi_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)indexi_in1, "int", A_LONG, 0);
	class_addmethod(c, (method)indexi_set, "set", A_SYM, 0);
	class_addmethod(c, (method)indexi_dblclick, "dblclick", A_CANT, 0);
	class_addmethod(c, (method)indexi_notify, "notify", A_CANT, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    indexi_class = c;
}

void *indexi_new(t_symbol *s, long chan)
{
	t_indexi *x = (t_indexi *)object_alloc(indexi_class);
	dsp_setup((t_pxobject *)x, 1);
	intin((t_object *)x,1);
	outlet_new((t_object *)x, "signal");
	indexi_in1(x,chan);
	return (x);
}


void indexi_free(t_indexi *x)
{
	dsp_free((t_pxobject *)x);
	object_free(x->l_buffer);
}


t_max_err indexi_notify(t_indexi *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	return buffer_ref_notify(x->l_buffer, s, msg, sender, data);
}


void indexi_assist(t_indexi *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
            case 0:
                sprintf(s,"signal");
                break;
            case 1:
                sprintf(s,"(signal/float) channel");
                break;
        }
	} else {
		sprintf(s,"(signal) output");
    }
}

void indexi_in1(t_indexi *x, long n)
{
	if (n)
		x->l_chan = Constrain(n,1,4) - 1;
	else
		x->l_chan = 0;
}

void indexi_dblclick(t_indexi *x)
{
	buffer_view(buffer_ref_getobject(x->l_buffer));
}

void indexi_set(t_indexi *x, t_symbol *s)
{
	if (!x->l_buffer)
		x->l_buffer = buffer_ref_new((t_object *)x, s);
	else
		buffer_ref_set(x->l_buffer, s);
}


long Constrain(long v, long lo, long hi)
{
	if (v < lo)
		return lo;
	else if (v > hi)
		return hi;
	else
		return v;
}

void indexi_dsp64(t_indexi *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, indexi_perform64, 0, NULL);
}

void indexi_perform64(t_indexi *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    t_double *in = (t_double *)(ins[0]);
    t_double *out = (t_double *)(outs[0]);

    int n = sampleframes;
	t_buffer_obj *buffer = buffer_ref_getobject(x->l_buffer);
	float *tab;
	double temp, alpha, output, blog;
	//double f;
	double chan,frames,nc;
	long indexi;
	
	tab = buffer_locksamples(buffer);
	if (!tab)
		goto zero;

	chan = (double)x->l_chan;
	frames = (double)buffer_getframecount(buffer);
	nc = (double)buffer_getchannelcount(buffer);
    
	while (--n) {
		temp = *++in;
		//temp = temp = 0.5;
		//f = temp + 0.5;
		if (temp < 0.)
			temp = 0.;
		else if (temp >= frames)
			//temp = frames - 1.;
			temp = (long)chan;
		if (nc > 1)
			temp = temp * nc + chan;
        
		indexi = (long)temp;				//integer part of address
		alpha = temp - (double)indexi; 	//fractional part
		
		output = tab[indexi];
		
		if (indexi+(long)nc >= frames) 			//wrap around if at end of buffer
			blog = tab[(long)chan];
		else
			blog = tab[(long)indexi+(long)nc];
        
		output = output + (alpha*(blog - output)); 	//linear interpolate
		
		*++out = output;
	}
	buffer_unlocksamples(buffer);
	return;
zero:
	while (--n) *++out = 0.;
}
