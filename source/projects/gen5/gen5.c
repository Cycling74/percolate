// gen5 -- writes a wavetable from an exponential bpf.
//		by r. luke dubois (luke@music.columbia.edu),
//			computer music center, columbia university, 2001.
//
//		ported from real-time cmix by brad garton and dave topper.
//			http://www.music.columbia.edu/cmix
//
//	objects and source are provided without warranty of any kind, express or implied.
//

/* the required include files */
#include "ext.h"
#include <math.h>

// maximum number of p-fields specified in a list -- if you make it larger you better 
// allocated the memory dynamically (right now it's using built-in memory)...
#define MAXSIZE 64
#define BUFFER 32768
// maximum size of wavetable -- this memory is allocated with NewPtr()
#define      PI2    6.2831853 // the big number...

// object definition structure...
typedef struct gen5
{
	Object g_ob;				// required header
	void *g_out;				// an outlet
	long g_numpoints;			// number of points in the bpf
	long g_buffsize;			// size of buffer
	long g_offset;				// offset into the output buffer (for list output)
	float g_args[MAXSIZE];		// array for the harmonic fields
	float *g_table;				// internal array for the wavetable
	long g_rescale;				// flag to rescale array
} gen5;


/* globalthat holds the class definition */
void *class;

// function prototypes here...
void gen5_list(gen5 *x, Symbol *s, short ac, Atom *av);
void gen5_assist(gen5 *x, void *b, long m, long a, char *s);
void gen5_bang(gen5 *x);
void gen5_offset(gen5 *x, long n);
void gen5_size(gen5 *x, long n);
void gen5_rescale(gen5 *x, long n);
void *gen5_new(long n, long o);
void *gen5_free(gen5 *x);
void DoTheDo(gen5 *x);

// init routine...
void ext_main(void *f)
{
	
	// define the class
	setup((t_messlist **)&class, (method)gen5_new, (method)gen5_free, (short)sizeof(gen5), 0L, A_DEFLONG, A_DEFLONG, 0);
	// methods, methods, methods...
	addbang((method)gen5_bang); /* put out the same shit */
	addmess((method)gen5_size, "size", A_DEFLONG, 0); /* change buffer */
	addmess((method)gen5_offset, "offset", A_DEFLONG, 0); /* change buffer offset */
	addmess((method)gen5_rescale, "rescale", A_DEFLONG, 0); /* change array rescaling */
	addmess((method)gen5_list, "list", A_GIMME, 0); /* the goods... */
	addmess((method)gen5_assist,"assist",A_CANT,0); /* help */
	
	post("gen5: by r. luke dubois, cmc");
}

// those methods

void gen5_bang(gen5 *x)
{
						
	DoTheDo(x);
	
}

void gen5_size(gen5 *x, long n)
{
	
	x->g_buffsize = n; // resize buffer
	if (x->g_buffsize>BUFFER) x->g_buffsize = BUFFER;

}

void gen5_offset(gen5 *x, long n)
{
	
	x->g_offset = n; // change buffer offset

}

void gen5_rescale(gen5 *x, long n)
{
	if(n>1) n = 1;
	if(n<0) n = 0;
	x->g_rescale = n; // change rescale flag

}

// instance creation...

void gen5_list(gen5 *x, Symbol *s, short argc, Atom *argv)
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

void DoTheDo(gen5 *x)
{
	register short j,k,l;
	Atom thestuff[2];
	float c, amp2, amp1, wmax, xmax=0.0;
	int i=0;


	amp2 = x->g_args[0];
	for(k = 1; k < x->g_numpoints; k += 2) {
		amp1 = amp2;
		amp2 = x->g_args[k+1];
		j = i + 1;
		x->g_table[i] = amp1;
		c = (float) pow((amp2/amp1),(1./x->g_args[k]));
		i = (j - 1) + x->g_args[k];
		for(l = j; l < i; l++) {
			if(l < x->g_buffsize)
				x->g_table[l] = x->g_table[l-1] * c;
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
		atom_setlong(thestuff,i+(x->g_offset*x->g_buffsize));
		atom_setfloat(thestuff+1,x->g_table[i]);
		outlet_list(x->g_out,0L,2,thestuff);
	}
}

void *gen5_new(long n, long o)
{
	gen5 *x;
	register short c;
	
	x = newobject(class);		// get memory for the object
	
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

void *gen5_free(gen5 *x)
{
	if (x != NULL) {
		if (x->g_table != NULL) {
			sysmem_freeptr(x->g_table); // free the memory allocated for the table...
		}
	}
}

void gen5_assist(gen5 *x, void *b, long msg, long arg, char *dst)
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
	

	