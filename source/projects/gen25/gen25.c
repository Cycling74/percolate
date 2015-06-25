// gen25 -- fills a buffer with a hamming or hanning window.
//		by r. luke dubois (luke@music.columbia.edu),
//			computer music center, columbia university, 2000.
//
//		ported from real-time cmix by brad garton and dave topper.
//			http://www.music.columbia.edu/cmix
//
//	objects and source are provided without warranty of any kind, express or implied.
//
// updated for Max 7 by Darwin Grosse and Tim Place
// -------------------------------------------------

/* the required include files */
#include <math.h>
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

#define BUFFER 32768
// maximum size of table -- this memory is allocated with NewPtr()
// #define      M_PI     3.141592654 // the big number...

// object definition structure...
typedef struct gen25
{
	t_object g_ob;				// required header
	void *g_out;				// an outlet
	long g_wintype;			// number of points in the bpf
	long g_buffsize;			// size of buffer
	long g_offset;				// offset into the output buffer (for list output)
	float *g_table;				// internal array for the wavetable
} t_gen25;


/* globalthat holds the class definition */
t_class *gen25_class;

// function prototypes here...
void gen25_int(t_gen25 *x, long n);
void gen25_assist(t_gen25 *x, void *b, long m, long a, char *s);
void gen25_bang(t_gen25 *x);
void gen25_offset(t_gen25 *x, long n);
void gen25_size(t_gen25 *x, long n);
void gen25_size(t_gen25 *x, long n);
void *gen25_new(long n, long o);
void gen25_free(t_gen25 *x);
void DoTheDo(t_gen25 *x);

// init routine...
void ext_main(void *f)
{
	t_class *c;
    
	c = class_new("gen25", (method)gen25_new, (method)gen25_free, sizeof(t_gen25), 0L, A_DEFLONG, A_DEFLONG, 0);
	class_addmethod(c, (method)gen25_bang,		"bang",		0);             // the method it uses when it gets a bang in the left inlet
	class_addmethod(c, (method)gen25_size,      "size",     A_DEFLONG, 0);  /* change buffer */
	class_addmethod(c, (method)gen25_offset,    "offset",   A_DEFLONG, 0);  /* change buffer offset */
	class_addmethod(c, (method)gen25_int,       "int",      A_LONG, 0);     /* change array rescaling */
	class_addmethod(c, (method)gen25_assist,    "assist",	A_CANT, 0);	// (optional) assistance method needs to be declared like this
    
	class_register(CLASS_BOX, c);
	gen25_class = c;
	post("gen25: by r. luke dubois, cmc");
}

// those methods

void gen25_bang(t_gen25 *x)
{
	DoTheDo(x);
}

void gen25_size(t_gen25 *x, long n)
{
	x->g_buffsize = n; // resize buffer
	if (x->g_buffsize>BUFFER) x->g_buffsize = BUFFER;
}

void gen25_offset(t_gen25 *x, long n)
{
	x->g_offset = n; // change buffer offset
}


// instance creation...

void gen25_int(t_gen25 *x, long n)
{
	switch (n) {
		case 1: // hanning
			x->g_wintype = 1;
			break;
		case 2: // hamming
			x->g_wintype = 2;
			break;
		default:
			x->g_wintype = 1;
			error("only two window types (yet)");
			break;	
	}
	DoTheDo(x);
}

void DoTheDo(t_gen25 *x)
{
	register short i, j;
	t_atom thestuff[2];
	float wmax, xmax=0.0;

	switch (x->g_wintype) {
		case 1: /* hanning window */
			for (i = 0; i < x->g_buffsize; i++)
				x->g_table[i] = -cos(2.0*PI * (float)i/(float)(x->g_buffsize)) * 0.5 + 0.5;
			break;
		case 2: /* hamming window */
			for (i = 0; i < x->g_buffsize; i++)
				x->g_table[i] = 0.54 - 0.46*cos(2.0*PI * (float)i/(float)(x->g_buffsize));
			break;
		}

	// rescale the wavetable to go between -1. and 1.
	for(j = 0; j < x->g_buffsize; j++) {
		if ((wmax = fabs(x->g_table[j])) > xmax) xmax = wmax;
	}
	for(j = 0; j < x->g_buffsize; j++) {
		x->g_table[j] /= xmax;
	}

	// output the wavetable in index, amplitude pairs...
	for(i=0;i<x->g_buffsize;i++) {
		SETLONG(thestuff,i+(x->g_offset*x->g_buffsize));
		SETFLOAT(thestuff+1,x->g_table[i]);
		outlet_list(x->g_out,0L,2,thestuff);
	}
}

void *gen25_new(long n, long o)
{
	t_gen25 *x;
	register short c;
	
	x = (t_gen25 *)object_alloc(gen25_class);		// get memory for the object
	
	x->g_offset = 0;
	if (o) {
		x->g_offset = o;
	}

// initialize wavetable size (must allocate memory)
	x->g_buffsize=512;

if (n) {
	x->g_buffsize=n;
	if (x->g_buffsize>BUFFER) x->g_buffsize=BUFFER; // size the wavetable
	}

	x->g_table=NULL;
	x->g_table = (float*) sysmem_newptr(sizeof(float) * BUFFER);
	if (x->g_table == NULL) {
		error("memory allocation error\n"); // whoops, out of memory...
		return (x);
	}

	for(c=0;c<x->g_buffsize;c++)
	{
		x->g_table[c]=0.0;
	}
	x->g_out = listout(x);				// create a list outlet
	return (x);							// return newly created object and go go go...
}

void gen25_free(t_gen25 *x)
{
	if (x != NULL) {
		if (x->g_table != NULL) {
			sysmem_freeptr(x->g_table); // free the memory allocated for the table...
		}
	}
}

void gen25_assist(t_gen25 *x, void *b, long msg, long arg, char *dst)
{
	switch(msg) {
		case 1: // inlet
			switch(arg) {
				case 0:
				sprintf(dst, "(int) Window Type (1 or 2)");
				break;
			}
		break;
		case 2: // outlet
			switch(arg) {
				case 0:
				sprintf(dst, "(list) Index/Amplitude Pairs");
				break;
			}
		break;
	}
}
	

	