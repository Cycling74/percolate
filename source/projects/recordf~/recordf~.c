#include "ext.h"
#include "z_dsp.h"
#include "buffer.h"

void *recordf_class;

typedef struct _recordf
{
    t_pxobject l_obj;
    t_symbol *l_sym;
    t_buffer *l_buf;
    long l_chan;
    long length;
    long loop_start, loop_end;
    long index;
    long srate;
    float srate_ms;
    short record;
    short loop;
    short reset;
    short append;

} t_recordf;

long Constrain(long v, long lo, long hi);
t_int *recordf_perform(t_int *w);
void recordf_dsp(t_recordf *x, t_signal **sp);
void recordf_set(t_recordf *x, t_symbol *s);
void *recordf_new(t_symbol *s, long chan);
void recordf_in1(t_recordf *x, long n);
void recordf_in2(t_recordf *x, long n);
void recordf_in0(t_recordf *x, long n);
void record_loop(t_recordf *x, Symbol *s, short argc, Atom *argv);
void record_goto(t_recordf *x, Symbol *s, short argc, Atom *argv);
void record_reset(t_recordf *x, Symbol *s, short argc, Atom *argv);
void record_append(t_recordf *x, Symbol *s, short argc, Atom *argv);
void recordf_assist(t_recordf *x, void *b, long m, long a, char *s);
void recordf_dblclick(t_recordf *x);

t_symbol *ps_buffer;

void ext_main(void* p)
{
	setup((struct messlist **)&recordf_class, (method)recordf_new, (method)dsp_free, (short)sizeof(t_recordf), 0L, 
		A_SYM, A_DEFLONG, 0);
	addmess((method)recordf_dsp, "dsp", A_CANT, 0);
	addmess((method)recordf_set, "set", A_SYM, 0);
	addinx((method)recordf_in2,3); //loop start
	addinx((method)recordf_in1,2); //loop end
	addint((method)recordf_in0); //start/stop recording
	addmess((method)recordf_assist, "assist", A_CANT, 0);
	addmess((method)recordf_dblclick, "dblclick", A_CANT, 0);
	addmess((method)record_reset, "reset", A_GIMME, 0);
	addmess((method)record_loop, "loop", A_GIMME, 0);
	addmess((method)record_goto, "goto", A_GIMME, 0);
	addmess((method)record_append, "append", A_GIMME, 0);
	dsp_initclass();
	ps_buffer = gensym("buffer~");
	rescopy('STR#',19988);
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

t_int *recordf_perform(t_int *w)
{
    t_recordf *x = (t_recordf *)(w[1]);
    float *in = (float *)(w[2]);
    float *fcoeff = (float *)(w[3]);
    float *out = (float *)(w[4]);
    int n = (int)(w[5]);
    
	t_buffer *b = x->l_buf;
	float *tab;
	float temp, input, coeff, bufsample;
	float chan, frames, nc, one_over_length;
	long index;
	float loop_start, loop_end;
	
	if (x->l_obj.z_disabled)
		goto out;
	if (!b)
		goto zero;
	if (!b->b_valid)
		goto zero;
	
	tab = b->b_samples;
	chan = (float)x->l_chan;
	frames = (float)b->b_frames;
	nc = (float)b->b_nchans;
	
	if(!x->reset) {
		loop_start = (float)x->loop_start * x->srate_ms;
		loop_end = (float)x->loop_end * x->srate_ms;
		
		if (loop_end < 0) loop_end = frames;
		else if (loop_end > frames) loop_end = frames;
		if (loop_start < 0) loop_start = 0;
		else if (loop_start >= loop_end) loop_start = 0;
		if (loop_end <= loop_start) loop_end = frames;
	} else {
		loop_start = 0;
		loop_end = frames;
		x->reset = 0;
	}
	
	x->length = loop_end - loop_start;
	if (x->length != 0) one_over_length = 1./(float)x->length;
	else one_over_length = 1./frames;
	
	if(x->record) {
		while (n--) {
			input 	= *in++;
			coeff 	= *fcoeff++;

			*out++ = ((float)x->index - loop_start) * one_over_length; //needs to be sync val (0-1)
			
			if(x->loop) {
				if (x->index >= loop_end) x->index = loop_start;
				if (x->index < loop_start) x->index = loop_start;
				index = x->index*nc + chan;
				
				tab[index] = coeff * tab[index] + input;
				x->index++;
			} else {
				if (x->index < loop_end) {
					index = x->index*nc + chan;
					tab[index] = coeff * tab[index] + input;
					x->index++;
				} else x->record = 0;
			}

		}
	} else while (n--) *out++ =  ((float)x->index - loop_start) * one_over_length; //needs to be sync val (0-1);

zero:
out:
	return (w+6);
}

void recordf_set(t_recordf *x, t_symbol *s)
{
	t_buffer *b;
	
	x->l_sym = s;
	if ((b = (t_buffer *)(s->s_thing)) && ob_sym(b) == ps_buffer) {
		x->l_buf = b;
		x->loop_end = b->b_frames;
		x->loop_start  = 0;
		//post("recordf~: setting record end point to %d", x->loop_end);
	} else {
		error("recordf~: no buffer~ %s", s->s_name);
		x->l_buf = 0;
	}
}

void recordf_in1(t_recordf *x, long n)
{
	x->loop_start = n;
	//post("recordf: loopstart = %d ", n);
}

void recordf_in2(t_recordf *x, long n)
{
	x->loop_end = n;
	//post("recordf: loopend = %d ", n);
}


void recordf_in0(t_recordf *x, long n)
{
	x->record = n;
	if(!x->append) x->index = 0; //reset recording point to beginning of loop
	//post("recordf: recording = %d ", n);
}

void record_loop(t_recordf *x, Symbol *s, short argc, Atom *argv)
{
	short i;
	int temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (int)argv[i].a_w.w_long;
				x->loop = temp;
				break;
			case A_FLOAT:
				temp = (int)argv[i].a_w.w_long;
				x->loop = temp;
				break;
		}
	}
}

void record_goto(t_recordf *x, Symbol *s, short argc, Atom *argv)
{
	short i;
	float temp;
		switch (argv[1].a_type) {
			case A_LONG:
				temp = (float)argv[1].a_w.w_long;
				break;
			case A_FLOAT:
				temp = argv[1].a_w.w_float;
				break;
		
	}
	temp *= x->srate_ms;
	x->index = (long)(temp);
	//post("recordf~: setting new record point to %ld", x->index);
}

void record_append(t_recordf *x, Symbol *s, short argc, Atom *argv)
{
	short i;
	int temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (int)argv[i].a_w.w_long;
				x->append = (long)((float)temp * x->srate_ms);
				break;
			case A_FLOAT:
				temp = (int)argv[i].a_w.w_long;
				x->append = (long)((float)temp * x->srate_ms);
				break;
		}
	}
}

void record_reset(t_recordf *x, Symbol *s, short argc, Atom *argv)
{
	x->reset = 1;
}

void recordf_dsp(t_recordf *x, t_signal **sp)
{
    x->srate = sp[0]->s_sr;
    x->srate_ms = (float)x->srate * .001;
    recordf_set(x,x->l_sym);
    //dsp_add(recordf_perform, 5, x, sp[0]->s_vec-1, sp[1]->s_vec-1, sp[2]->s_vec-1, sp[0]->s_n+1);
    dsp_add(recordf_perform, 5, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[0]->s_n);
}

void recordf_dblclick(t_recordf *x)
{
	t_buffer *b;
	
	if ((b = (t_buffer *)(x->l_sym->s_thing)) && ob_sym(b) == ps_buffer)
		mess0((struct object *)b,gensym("dblclick"));
}

void recordf_assist(t_recordf *x, void *b, long m, long a, char *s)
{
	assist_string(19988,m,a,1,5,s);
}

void *recordf_new(t_symbol *s, long chan)
{
	t_recordf *x = (t_recordf *)newobject(recordf_class);
	//dsp_setup((t_pxobject *)x, 1);
    intin((t_object *)x, 3);
    intin((t_object *)x, 2);
	dsp_setup((t_pxobject *)x, 2);
	outlet_new((t_object *)x, "signal");
	x->l_sym = s;
	x->index = 0;
	x->record = 0;
	x->reset = 0;
	x->loop_start = 0;
	x->loop_end = 100;
	x->l_chan = 0;
	x->loop = 0;
	
	recordf_set(x, s);
	//recordf_in1(x,chan);
	//x->l_obj.z_misc = Z_NO_INPLACE;
	return (x);
}

