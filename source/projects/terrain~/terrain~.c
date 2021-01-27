// terrain~ -- interpolates between two or more wavetable 'frames' stored in a buffer.
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "buffer.h"

#define MAXFRAMES 64

t_class *terrain_class;

typedef struct _terrain
{
    t_pxobject l_obj;
    t_buffer_ref *l_buffer;
    long l_framesize;
    long l_numframes;
} t_terrain;

void *terrain_new(t_symbol *s, long n, long f);
void terrain_free(t_terrain *x);
t_max_err terrain_notify(t_terrain *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void terrain_assist(t_terrain *x, void *b, long m, long a, char *s);
void terrain_dsp64(t_terrain *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void terrain_perform64(t_terrain *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void terrain_set(t_terrain *x, t_symbol *s);
void terrain_size(t_terrain *x, long size);
void terrain_frames(t_terrain *x, long frames);

t_symbol *ps_buffer;


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

	// Single frame size (samples)
	if (n) {
		x->l_framesize = n;
	} else {
		x->l_framesize = 512;
	}

	// Number of frames
	if (f) {
		x->l_numframes = CLAMP(f, 2, MAXFRAMES);
	} else {
		x->l_numframes = 2;
	}

	return x;
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
                    sprintf(s, "(signal) x-index");
                    break;
				case 1:
                    sprintf(s, "(signal) y-index");
                    break;
			}
            break;
		case 2: // outlet
			switch(a) {
				case 0:
                    sprintf(s, "(signal) z-output");
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
    if (size < 1) size = 1;
    x->l_framesize = size;
}


void terrain_frames(t_terrain *x, long frames)
{
	frames = CLAMP(frames, 2, MAXFRAMES);
    x->l_numframes=frames;
}


void terrain_dsp64(t_terrain *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, terrain_perform64, 0, NULL);
}


void terrain_perform64(t_terrain *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    t_double *inx = ins[0];
    t_double *iny = ins[1];
    t_double *out = outs[0];
    
    int n = sampleframes;

	t_buffer_obj *buffer = buffer_ref_getobject(x->l_buffer);
	float *tab = buffer_locksamples(buffer);
	if (!tab)
		goto zero;

	long buffer_size = buffer_getframecount(buffer);
	long nc = buffer_getchannelcount(buffer);
	long fsize = x->l_framesize;
	long num_frames = x->l_numframes;

	float x_coord, y_coord;
	long index, index2;
    long frame;
    float frac;
	
	while (n--) {
		// Location in single frame
		x_coord = *inx++;
		index = x_coord * fsize;
		index = CLAMP(index, 0, fsize - 1);

		if (index + ((num_frames - 1) * fsize) >= buffer_size) {
			goto zero;  // Out of bounds of buffer
		}

		// Location in terrain (which frame?)
		y_coord = CLAMP(*iny++, 0.0, 1.0);
        frame = (num_frames - 1) * y_coord;  // Integer part of the terrain location (lower frame)
        frac = (num_frames - 1) * y_coord - frame;  // Fractional part

		// Get the frame index in the frame above and below the y-coord
		index = index + (frame * fsize);  // Current frame
		index2 = index + fsize;  // One frame later

		// Scale by the number of channels of audio
		index = index * nc;
		index2 = index2 * nc;
        
        // Make sure we don't go out of bounds
        index = CLAMP(index, 0, buffer_size - 1);
        index2 = CLAMP(index, 0, buffer_size - 1);

		// Interpolate between tab[index] and tab[index2]
		*out++ = ((1.0 - frac) * tab[index]) + (frac * tab[index2]);
	}

	buffer_unlocksamples(buffer);
	return;

zero:
	while (--n) *++out = 0.;
    return;
}
