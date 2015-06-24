// gen24 -- writes a wavetable from a generic break-point function.
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

// maximum number of time/amp. pairs specified in a list -- if you make it larger you better 
// allocated the memory dynamically (right now it's using built-in memory)...
#define MAXSIZE 64
#define BUFFER 32768

// maximum size of wavetable -- this memory is allocated with NewPtr()
#define      PI2    6.2831853 // the big number...

// object definition structure...
typedef struct gen24
{
	t_object g_ob;				// required header
	void *g_out;				// an outlet
	long g_numpoints;			// number of points in the bpf
	long g_buffsize;			// size of buffer
	long g_offset;				// offset into the output buffer (for list output)
	float g_args[MAXSIZE];		// array for the harmonic fields
	float *g_table;				// internal array for the wavetable
	long g_rescale;				// flag to rescale array
} t_gen24;

/* globalthat holds the class definition */
t_class *gen24_class;

// function prototypes here...
void gen24_list(t_gen24 *x, t_symbol *s, long ac, t_atom *av);
void gen24_assist(t_gen24 *x, void *b, long m, long a, char *s);
void gen24_bang(t_gen24 *x);
void gen24_offset(t_gen24 *x, long n);
void gen24_size(t_gen24 *x, long n);
void gen24_rescale(t_gen24 *x, long n);
void *gen24_new(long n, long o);
void gen24_free(t_gen24 *x);
void DoTheDo(t_gen24 *x);

// init routine...
void ext_main(void *f)
{
	t_class *c;
    
	c = class_new("gen24", (method)gen24_new, (method)gen24_free, sizeof(t_gen24), 0L, A_DEFLONG, A_DEFLONG, 0);
	class_addmethod(c, (method)gen24_bang,		"bang",		0);             // the method it uses when it gets a bang in the left inlet
	class_addmethod(c, (method)gen24_size,       "size",     A_DEFLONG, 0);  /* change buffer */
	class_addmethod(c, (method)gen24_offset,     "offset",   A_DEFLONG, 0);  /* change buffer offset */
	class_addmethod(c, (method)gen24_rescale,    "rescale",  A_DEFLONG, 0);  /* change array rescaling */
	class_addmethod(c, (method)gen24_list,       "list",     A_GIMME, 0);    /* the goods... */
	class_addmethod(c, (method)gen24_assist,     "assist",	A_CANT, 0);	// (optional) assistance method needs to be declared like this
    
	class_register(CLASS_BOX, c);
	gen24_class = c;
	post("gen24: by r. luke dubois, cmc");
}

// those methods

void gen24_bang(t_gen24 *x)
{
						
	DoTheDo(x);
	
}

void gen24_size(t_gen24 *x, long n)
{
	
	x->g_buffsize = n; // resize buffer
	if (x->g_buffsize>BUFFER) x->g_buffsize = BUFFER;

}

void gen24_offset(t_gen24 *x, long n)
{
	
	x->g_offset = n; // change buffer offset

}


void gen24_rescale(t_gen24 *x, long n)
{
	if(n>1) n = 1;
	if(n<0) n = 0;
	x->g_rescale = n; // change rescale flag

}



// instance creation...

void gen24_list(t_gen24 *x, t_symbol *s, long argc, t_atom *argv)
{

	// parse the list of incoming harmonics...
	register short i;

	for (i=0; i < argc; i++) {
		if (argv[i].a_type==A_LONG) {
			x->g_args[i] = (float)argv[i].a_w.w_long;
		}
		else if (argv[i].a_type==A_FLOAT) {
			x->g_args[i] = argv[i].a_w.w_float;
		}
	}
	x->g_numpoints = argc;
	DoTheDo(x);
}

void DoTheDo(t_gen24 *x)
{
	register short i,j,k,l;
	t_atom thestuff[2];
	float scaler, amp2, amp1, wmax, xmax=0.0;
	
	// compute the wavetable...
	for(i = 0; i<x->g_buffsize; i++) x->g_table[i] = 0.0;
	i=0;
	scaler = ((float) x->g_buffsize)/x->g_args[x->g_numpoints-2];
	amp2 = x->g_args[1];
	for(k = 1; k < x->g_numpoints; k += 2) {
		amp1 = amp2;
		amp2 = x->g_args[k+2];
		j = i + 1;
		i = x->g_args[k+1]*scaler + 1;
		for(l=j; l<=i; l++) {
			if(l <= x->g_buffsize)
				x->g_table[l-1] = amp1 +
				(amp2-amp1) * (float)(l-j) / (i-j+1);
			}
		}

    if(x->g_rescale) {
        // rescale the wavetable to go between -1. and 1.
        for(j = 0; j < x->g_buffsize; j++) {
            if ((wmax = fabs(x->g_table[j])) > xmax) xmax = wmax;
        }
        for(j = 0; j < x->g_buffsize; j++) {
            x->g_table[j] /= xmax;
        }
    }

	// output the wavetable in index, amplitude pairs...
	for(i=0;i<x->g_buffsize;i++) {
		SETLONG(thestuff,i+(x->g_offset*x->g_buffsize));
		SETFLOAT(thestuff+1,x->g_table[i]);
		outlet_list(x->g_out,0L,2,thestuff);
	}
}

void *gen24_new(long n, long o)
{
	t_gen24 *x;
	register short c;
	
	x = (t_gen24 *)object_alloc(gen24_class);		// get memory for the object
	
	x->g_offset = 0;
	if (o) {
		x->g_offset = o;
	}

	for(c=0;c<MAXSIZE;c++) // initialize bpf array (static memory)
	{
		x->g_args[c] =0.0;
	}

// initialize wavetable size (must allocate memory)
	x->g_buffsize=512;
	
	x->g_rescale=1;
    
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

void gen24_free(t_gen24 *x)
{
	if (x != NULL) {
		if (x->g_table != NULL) {
			sysmem_freeptr(x->g_table); // free the memory allocated for the table...
		}
	}
}

void gen24_assist(t_gen24 *x, void *b, long msg, long arg, char *dst)
{
	switch(msg) {
		case 1: // inlet
			switch(arg) {
				case 0:
				sprintf(dst, "(list) Breakpoint Function for Waveform");
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
	

	