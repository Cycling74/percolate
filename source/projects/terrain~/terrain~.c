// terrain~ -- interpolates between two or more wavetable 'frames' stored in a buffer.
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "buffer.h"

#define MAXFRAMES 32

t_class *terrain_class;

typedef struct _terrain
{
    t_pxobject l_obj;
    t_buffer_ref *l_buffer;
    long l_framesize;
    long l_numframes;
    float l_hopsize;
} t_terrain;

float FConstrain(float v, float lo, float hi);
long IConstrain(long v, long lo, long hi);

void *terrain_new(t_symbol *s, long n, long f);
void terrain_free(t_terrain *x);
t_max_err terrain_notify(t_terrain *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void terrain_assist(t_terrain *x, void *b, long m, long a, char *s);

// dsp stuff
void terrain_dsp64(t_terrain *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void terrain_perform64(t_terrain *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void terrain_set(t_terrain *x, t_symbol *s);
void terrain_size(t_terrain *x, long size);
void terrain_frames(t_terrain *x, long frames);

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
    t_class *c = class_new("terrain~", (method)terrain_new, (method)terrain_free, (long)sizeof(t_terrain), 0L, A_SYM, A_DEFLONG, A_DEFLONG, 0);
    
    class_addmethod(c, (method)terrain_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)terrain_dsp64, "dsp64", A_CANT, 0);
	class_addmethod(c, (method)terrain_notify, "notify", A_CANT, 0);
 
	class_addmethod(c, (method)terrain_set, "set", A_SYM, 0);
	class_addmethod(c, (method)terrain_size, "size", A_DEFLONG, 0);
	class_addmethod(c, (method)terrain_frames, "frames", A_DEFLONG, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    terrain_class = c;
	ps_buffer = gensym("buffer~");
}

void *terrain_new(t_symbol *s, long n, long f)
{
	t_terrain *x = (t_terrain *)object_alloc(terrain_class);
	dsp_setup((t_pxobject *)x, 2);
	outlet_new((t_object *)x, "signal");
	terrain_set(x, s);
	x->l_framesize = 512;
	x->l_numframes = 2;
	if(n) x->l_framesize = n;
	if(f) x->l_numframes = IConstrain(f, 2, MAXFRAMES);
	x->l_hopsize = 1./(float)(x->l_numframes-1);
	return (x);
}


void terrain_free(t_terrain *x)
{
	dsp_free((t_pxobject *)x);
	object_free(x->l_buffer);
}


t_max_err terrain_notify(t_terrain *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	return buffer_ref_notify(x->l_buffer, s, msg, sender, data);
}


void terrain_assist(t_terrain *x, void *b, long m, long a, char *s)
{
	switch(m) {
		case 1: // inlet
			switch(a) {
				case 0:
                    sprintf(s, "(signal) X Index");
                    break;
				case 1:
                    sprintf(s, "(signal) Y Index");
                    break;
			}
            break;
		case 2: // outlet
			switch(a) {
				case 0:
                    sprintf(s, "(signal) Z Output");
                    break;
			}
            break;
	}
    
}

void terrain_set(t_terrain *x, t_symbol *s)
{
	if (!x->l_buffer)
		x->l_buffer = buffer_ref_new((t_object *)x, s);
	else
		buffer_ref_set(x->l_buffer, s);
}

void terrain_size(t_terrain *x, long size)
{
    
    if(size<1) size = 1;
    x->l_framesize = size;
    
}

void terrain_frames(t_terrain *x, long frames)
{
    
    if(frames<2) frames = 2;
    if(frames>MAXFRAMES) frames = MAXFRAMES;
    x->l_numframes=frames;
    x->l_hopsize = 1./(float)(x->l_numframes-1);
    
    
}


void terrain_dsp64(t_terrain *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, terrain_perform64, 0, NULL);
}

void terrain_perform64(t_terrain *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    t_double *inx = (t_double *)(ins[0]);
    t_double *iny = (t_double *)(ins[1]);
    t_double *out = (t_double *)(outs[0]);
    
    int n = sampleframes;
	float *tab;
	float x_coords, y_coords, hopsize;
	long index, index2, frames,nc,fsize, nframes;
	register short p,q;
	t_buffer_obj *buffer = buffer_ref_getobject(x->l_buffer);
	
	tab = buffer_locksamples(buffer);
	if (!tab)
		goto zero;
	
	frames = buffer_getframecount(buffer);
	nc = buffer_getchannelcount(buffer);
	fsize=x->l_framesize;
	nframes = x->l_numframes;
	hopsize = x->l_hopsize;
	while (--n) {
		x_coords = *++inx;
		y_coords = *++iny;
		if (y_coords<0.) y_coords = 0.;
		if (y_coords>1.0) y_coords = 1.0; // constrain y coordinates to 0 to 1
		index = x_coords*fsize;
		if (index<0) index = 0;
		if (index>=fsize) index = fsize-1; // constrain index coordinates to the frame boundaries
		// check buffer~ boundaries
		if (index >= frames)
			index = frames - 1;
		if (index+((nframes-1)*fsize) >= frames) // out of bounds
			goto zero;
		// figure out which two frames we're between...
		q=0;
		while (++q<nframes) {
			if (y_coords<=(hopsize*q)) {
				p = q-1;
				q=nframes;
			}
		}
		index = index+(p*fsize); // current frame
		index2 = index+fsize; // one frame later
		if (nc > 1) {
			index = index * nc;
			index2 = index2 * nc;
		}
		y_coords = (y_coords*(nframes-1))-p;
		*++out = ((1.-y_coords)*tab[index])+(y_coords*tab[index2]); // this is wrong -- y_coords amp isn't scaling yet.
	}
	buffer_unlocksamples(buffer);
	return;
zero:
	while (--n) *++out = 0.;
    return;
}
