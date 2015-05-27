#include "ext.h"
#include "z_dsp.h"
#include "buffer.h"

void *index_class;

typedef struct _index
{
    t_pxobject l_obj;
    t_symbol *l_sym;
    t_buffer *l_buf;
    long l_chan;
} t_index;

long Constrain(long v, long lo, long hi);
t_int *index_perform(t_int *w);
void index_dsp(t_index *x, t_signal **sp);
void index_set(t_index *x, t_symbol *s);
void *index_new(t_symbol *s, long chan);
void index_in1(t_index *x, long n);
void index_assist(t_index *x, void *b, long m, long a, char *s);
void index_dblclick(t_index *x);

t_symbol *ps_buffer;

void main(void)
{
	setup((struct messlist **)&index_class, (method)index_new, (method)dsp_free, (short)sizeof(t_index), 0L, 
		A_SYM, A_DEFLONG, 0);
	addmess((method)index_dsp, "dsp", A_CANT, 0);
	addmess((method)index_set, "set", A_SYM, 0);
	addinx((method)index_in1,1);
	addmess((method)index_assist, "assist", A_CANT, 0);
	addmess((method)index_dblclick, "dblclick", A_CANT, 0);
	dsp_initclass();
	ps_buffer = gensym("buffer~");
	rescopy('STR#',9294);
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

t_int *index_perform(t_int *w)
{
    t_index *x = (t_index *)(w[1]);
    t_float *in = (t_float *)(w[2]);
    t_float *out = (t_float *)(w[3]);
    int n = (int)(w[4]);
	t_buffer *b = x->l_buf;
	float *tab;
	double temp, alpha, output, blog;
	//double f;
	double chan,frames,nc;
	long index;
	
	if (x->l_obj.z_disabled)
		goto out;
	if (!b)
		goto zero;
	if (!b->b_valid)
		goto zero;
	tab = b->b_samples;
	chan = (double)x->l_chan;
	frames = (double)b->b_frames;
	nc = (double)b->b_nchans;
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
			
		index = (long)temp;				//integer part of address
		alpha = temp - (double)index; 	//fractional part
		
		output = tab[index];
		
		if (index+(long)nc >= frames) 			//wrap around if at end of buffer
			blog = tab[(long)chan];
		else 
			blog = tab[(long)index+(long)nc];
			
		output = output + (alpha*(blog - output)); 	//linear interpolate
		
		*++out = output;
	}
	return (w+5);
zero:
	while (--n) *++out = 0.;
out:
	return (w+5);
}

void index_set(t_index *x, t_symbol *s)
{
	t_buffer *b;
	
	x->l_sym = s;
	if ((b = (t_buffer *)(s->s_thing)) && ob_sym(b) == ps_buffer) {
		x->l_buf = b;
	} else {
		error("index~: no buffer~ %s", s->s_name);
		x->l_buf = 0;
	}
}

void index_in1(t_index *x, long n)
{
	if (n)
		x->l_chan = Constrain(n,1,4) - 1;
	else
		x->l_chan = 0;
}

void index_dsp(t_index *x, t_signal **sp)
{
    index_set(x,x->l_sym);
    dsp_add(index_perform, 4, x, sp[0]->s_vec-1, sp[1]->s_vec-1, sp[0]->s_n+1);
}

void index_dblclick(t_index *x)
{
	t_buffer *b;
	
	if ((b = (t_buffer *)(x->l_sym->s_thing)) && ob_sym(b) == ps_buffer)
		mess0((struct object *)b,gensym("dblclick"));
}

void index_assist(t_index *x, void *b, long m, long a, char *s)
{
	assist_string(3294,m,a,1,3,s);
}

void *index_new(t_symbol *s, long chan)
{
	t_index *x = (t_index *)newobject(index_class);
	dsp_setup((t_pxobject *)x, 1);
	intin((t_object *)x,1);
	outlet_new((t_object *)x, "signal");
	x->l_sym = s;
	index_in1(x,chan);
	return (x);
}

