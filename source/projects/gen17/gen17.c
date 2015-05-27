// gen17 -- takes a list of harmonic values and writes a chebyshev transfer function.
//		by r. luke dubois (luke@music.columbia.edu),
//			computer music center, columbia university, 2000.
//
//		ported from real-time cmix by brad garton and dave topper.
//			http://www.music.columbia.edu/cmix
//
//	objects and source are provided without warranty of any kind, express or implied.
//

/* the required include files */
#include "ext.h"
#include <math.h>

// maximum number of harmonics specified in a list -- if you make it larger you better 
// allocated the memory dynamically (right now it's using built-in memory)...
#define MAXSIZE 64 
#define BUFFER 32768
// maximum size of transfer function -- this memory is allocated with NewPtr()

// object definition structure...
typedef struct gen17
{
	Object g_ob;				// required header
	void *g_out;				// an outlet
	long g_numharmonics;		// number of harmonics
	long g_buffsize;			// size of buffer
	long g_offset;				// offset into output buffer (for list output)
	float g_args[MAXSIZE];		// array for the harmonic fields
	float *g_table;				// internal array for computing the transfer function
	long g_rescale;				// flag to rescale array
} Gen17;

/* global that holds the class definition */
void *class;

// function prototypes here...
void gen17_list(Gen17 *x, Symbol *s, short ac, Atom *av);
void gen17_assist(Gen17 *x, void *b, long m, long a, char *s);
void gen17_bang(Gen17 *x);
void gen17_offset(Gen17 *x, long n);
void gen17_size(Gen17 *x, long n);
void gen17_rescale(Gen17 *x, long n);
void *gen17_new(long n, long o);
void *gen17_free(Gen17 *x);
void DoTheDo(Gen17 *x);

// init routine...
void ext_main(void *f)
{
	
	// define the class
	setup((t_messlist **)&class, (method)gen17_new, (method)gen17_free, (short)sizeof(Gen17), 0L, A_DEFLONG, A_DEFLONG, 0);
	// methods, methods, methods...
	addbang((method)gen17_bang); /* put out the same shit */
	addmess((method)gen17_size, "size", A_DEFLONG, 0); /* change buffer size */
	addmess((method)gen17_offset, "offset", A_DEFLONG, 0); /* change buffer offset */
	addmess((method)gen17_rescale, "rescale", A_DEFLONG, 0); /* change array rescaling */
	addmess((method)gen17_list, "list", A_GIMME, 0); /* the goods... */
	addmess((method)gen17_assist,"assist",A_CANT,0); /* help */
	
	post("gen17: by r. luke dubois, cmc");
}

// those methods

void gen17_bang(Gen17 *x)
{
						
	DoTheDo(x);
	
}


void gen17_size(Gen17 *x, long n)
{
	
	x->g_buffsize = n; // resize buffer
	if (x->g_buffsize>BUFFER) x->g_buffsize = BUFFER; // don't go beyond max limit of buffer

}

void gen17_offset(Gen17 *x, long n)
{
	
	x->g_offset = n; // change buffer offset

}

void gen17_rescale(Gen17 *x, long n)
{
	if(n>1) n = 1;
	if(n<0) n = 0;
	x->g_rescale = n; // change rescale flag

}


// instance creation...

void gen17_list(Gen17 *x, Symbol *s, short argc, Atom *argv)
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
	x->g_numharmonics = argc;
	DoTheDo(x);
}

void DoTheDo(Gen17 *x)
{
	register short i,j;
	Atom thestuff[2];
	float Tn, Tn1, Tn2, v,d;
	float wmax, xmax=0.0;
	
	// compute the transfer function using the chebyshev equation...
	d=(float)(x->g_buffsize/2-.5);
	for(i=0; i<x->g_buffsize; i++) {
		v=(i/d-1.);
		x->g_table[i]=0.;
		Tn1=1;
		Tn=v;
		for(j=0; j<x->g_numharmonics;j++) {
			x->g_table[i]=x->g_args[j]*Tn+x->g_table[i];
			Tn2=Tn1;
			Tn1=Tn;
			Tn=2*v*Tn1-Tn2;
		}
	}

if(x->g_rescale) {
	// rescale the function to make sure it stays between -1. and 1.
	for(j = 0; j < x->g_buffsize; j++) {
		if ((wmax = fabs(x->g_table[j])) > xmax) xmax = wmax;
	}
	for(j = 0; j < x->g_buffsize; j++) {
		x->g_table[j] /= xmax;
	}
}

	// output the transfer function in index/amplitude pairs...
	for(i=0;i<x->g_buffsize;i++) {
		SETLONG(thestuff,i+(x->g_offset*x->g_buffsize));
		SETFLOAT(thestuff+1,x->g_table[i]);
		outlet_list(x->g_out,0L,2,thestuff);
	}
}

void *gen17_new(long n, long o)
{
	Gen17 *x;
	register short c;
	
	x = newobject(class);		// get memory for the object

	x->g_offset = 0;
	if (o) {
		x->g_offset = o;
	}

	for(c=0;c<MAXSIZE;c++) // initialize harmonics array (static memory)
	{
		x->g_args[c] =0.0;
	}

// initialize function table size (must allocate memory)
	x->g_buffsize=512;
	
	x->g_rescale=1;

if (n) {
	x->g_buffsize=n;
	if (x->g_buffsize>BUFFER) x->g_buffsize=BUFFER; // size the function array
	}

	x->g_table=NULL;
	x->g_table = (float*) sysmem_newptr(sizeof(float) * BUFFER);
	if (x->g_table == NULL) {
		error("memory allocation error"); // whoops, out of memory...
		return (x);
	}

	for(c=0;c<x->g_buffsize;c++)
	{
		x->g_table[c]=0.0;
	}
	x->g_out = listout(x);				// create a list outlet
	return (x);							// return newly created object and go go go...


}

void *gen17_free(Gen17 *x)
{
	if (x != NULL) {
		if (x->g_table != NULL) {
			sysmem_freeptr((Ptr) x->g_table); // free the memory allocated for the table...
		}
	}
}

void gen17_assist(Gen17 *x, void *b, long msg, long arg, char *dst)
{
	switch(msg) {
		case 1: // inlet
			switch(arg) {
				case 0:
				sprintf(dst, "(list) Harmonic Partial Amplitudes");
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
