// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "buffer.h"

t_class *pokef_class;

typedef struct _pokef
{
    t_pxobject l_obj;
    t_buffer_ref *l_buffer;
    long l_chan;
    long length;
    
} t_pokef;

long Constrain(long v, long lo, long hi);
void pokef_set(t_pokef *x, t_symbol *s);

void *pokef_new(t_symbol *s, long chan);
void pokef_free(t_pokef *x);
t_max_err pokef_notify(t_pokef *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void pokef_in3(t_pokef *x, long n);
void pokef_assist(t_pokef *x, void *b, long m, long a, char *s);
void pokef_dblclick(t_pokef *x);
void pokef_length(t_pokef *x, t_symbol *s, long argc, t_atom *argv);

// dsp stuff
void pokef_dsp64(t_pokef *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void pokef_perform64(t_pokef *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_symbol *ps_buffer;

void ext_main(void* p)
{
    t_class *c = class_new("pokef~", (method)pokef_new, (method)pokef_free, (long)sizeof(t_pokef), 0L, A_SYM, A_DEFLONG, 0);
    
    class_addmethod(c, (method)pokef_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)pokef_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)pokef_in3, "in3", A_LONG, 0);
    
	class_addmethod(c, (method)pokef_set, "set", A_SYM, 0);
	class_addmethod(c, (method)pokef_length, "length", A_GIMME, 0);
    class_addmethod(c, (method)pokef_dblclick, "dblclick", A_CANT, 0);
	class_addmethod(c, (method)pokef_notify, "notify", A_CANT, 0);
	class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    pokef_class = c;
    
	ps_buffer = gensym("buffer~");
}

void *pokef_new(t_symbol *s, long chan)
{
	t_pokef *x = (t_pokef *)object_alloc(pokef_class);
	//dsp_setup((t_pxobject *)x, 1);
    intin((t_object *)x, 3);
	dsp_setup((t_pxobject *)x, 3);
	outlet_new((t_object *)x, "signal");
	pokef_set(x, s);
	pokef_in3(x,chan);
	//x->l_obj.z_misc = Z_NO_INPLACE;
	return (x);
}


void pokef_free(t_pokef *x)
{
	dsp_free((t_pxobject *)x);
	object_free(x->l_buffer);
}


t_max_err pokef_notify(t_pokef *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	return buffer_ref_notify(x->l_buffer, s, msg, sender, data);
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

void pokef_set(t_pokef *x, t_symbol *s)
{
	if (!x->l_buffer)
		x->l_buffer = buffer_ref_new((t_object *)x, s);
	else
		buffer_ref_set(x->l_buffer, s);
}

void pokef_in3(t_pokef *x, long n)
{
	if (n)
		x->l_chan = Constrain(n,1,4) - 1;
	else
		x->l_chan = 0;
}

void pokef_length(t_pokef *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	int temp;

	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = argv[i].a_w.w_long;
				x->length = temp;
				break;
			case A_FLOAT:
				temp = (int)argv[i].a_w.w_float;
				x->length = temp;
				break;
		}
	}
}

void pokef_dblclick(t_pokef *x)
{
	buffer_view(buffer_ref_getobject(x->l_buffer));
}

void pokef_assist(t_pokef *x, void *b, long m, long a, char *s)
{

    if (m == ASSIST_INLET) {
        switch (a) {
            case 0:
                sprintf(s,"(signal) value");
                break;
            case 1:
                sprintf(s,"(signal) index");
                break;
            case 2:
                sprintf(s,"(signal) coefficient");
                break;
            case 3:
                sprintf(s,"(int) channel");
                break;
        }
    } else {
        sprintf(s,"(signal) output");
    }

}

void pokef_dsp64(t_pokef *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, pokef_perform64, 0, NULL);
}

void pokef_perform64(t_pokef *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    float *in = (float *)(ins[0]);
    t_double *index = (t_double *)(ins[1]);
    t_double *fcoeff = (t_double *)(ins[2]);
    t_double *out = (t_double *)(outs[0]);
    int n = sampleframes;
    
    double alpha, om_alpha;
    
	t_float *tab;
	t_double temp, input, coeff;
	t_double chan, frames, nc, length;
	
	long pokef, pokef_next, pokef_nextnext, pokef_nextnextnext;
	
	t_buffer_obj *buffer = buffer_ref_getobject(x->l_buffer);
	
	tab = buffer_locksamples(buffer);
	if (!tab)
		goto zero;
	
	chan = (t_double)x->l_chan;
	frames = buffer_getframecount(buffer);
	nc = buffer_getchannelcount(buffer);
	length = (t_double)x->length;
	if (length <= 0.) length = frames;
	else if (length >= frames) length = frames;
	
	while (n--) {
		input 	= *in++;
		temp 	= *index++;
		coeff 	= *fcoeff++;
        
		temp += 0.5;
		
		if (temp < 0.)
			temp = 0.;
		else while (temp >= length)
			temp -= length;
        
		temp = temp * nc + chan;
        
		pokef = (long)temp;
		//bufsample = tab[pokef];
        
		alpha = temp - (double)pokef;
		om_alpha = 1. - alpha;
		
		pokef_next = pokef + nc;
		while (pokef_next >= length*nc) pokef_next -= length*nc;
		pokef_nextnext = pokef_next + nc;
		while (pokef_nextnext >= length*nc) pokef_nextnext -= length*nc;
		pokef_nextnextnext = pokef_nextnext + nc;
		while (pokef_nextnextnext >= length*nc) pokef_nextnextnext -= length*nc;
		
		//output two ahead of record point...., with interpolation
		//*out++ = tab[pokef_nextnext]*om_alpha + tab[pokef_nextnextnext]*alpha;
		//*out++ = tab[pokef_next]*om_alpha + tab[pokef_nextnext]*alpha;
		*out++ = tab[pokef_next];
		
		//interpolate recording...
		//tab[pokef] = coeff * tab[pokef] + om_alpha*input;
		//tab[pokef_next] = coeff * tab[pokef_next] + alpha*input;
		//or not....
		tab[pokef] = coeff * tab[pokef] + input;
        
		//*out++ = bufsample;
		//tab[pokef] = coeff * bufsample + input;
        
	}
	buffer_unlocksamples(buffer);
	return;
zero:
	while (n--)
		*out++ = 0.0;
}
