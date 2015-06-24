// gen17 -- takes a list of harmonic values and writes a chebyshev transfer function.
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

// maximum number of harmonics specified in a list -- if you make it larger you better 
// allocated the memory dynamically (right now it's using built-in memory)...
#define MAXSIZE 64 
#define BUFFER 32768
// maximum size of transfer function -- this memory is allocated with NewPtr()

// object definition structure...
typedef struct gen17
{
	t_object g_ob;				// required header
	void *g_out;				// an outlet
	long g_numharmonics;		// number of harmonics
	long g_buffsize;			// size of buffer
	long g_offset;				// offset into output buffer (for list output)
	float g_args[MAXSIZE];		// array for the harmonic fields
	float *g_table;				// internal array for computing the transfer function
	long g_rescale;				// flag to rescale array
} t_gen17;

/* global that holds the class definition */
t_class *gen17_class;

// function prototypes here...
void gen17_list(t_gen17 *x, t_symbol *s, short ac, t_atom *av);
void gen17_assist(t_gen17 *x, void *b, long m, long a, char *s);
void gen17_bang(t_gen17 *x);
void gen17_offset(t_gen17 *x, long n);
void gen17_size(t_gen17 *x, long n);
void gen17_rescale(t_gen17 *x, long n);
void *gen17_new(long n, long o);
void gen17_free(t_gen17 *x);
void DoTheDo(t_gen17 *x);

// init routine...
void ext_main(void *f)
{
	t_class *c;
    
	c = class_new("gen17", (method)gen17_new, (method)gen17_free, sizeof(t_gen17), 0L, A_DEFLONG, A_DEFLONG, 0);
	class_addmethod(c, (method)gen17_bang,		"bang",		0);             // the method it uses when it gets a bang in the left inlet
	class_addmethod(c, (method)gen17_size,       "size",     A_DEFLONG, 0);  /* change buffer */
	class_addmethod(c, (method)gen17_offset,     "offset",   A_DEFLONG, 0);  /* change buffer offset */
	class_addmethod(c, (method)gen17_rescale,    "rescale",  A_DEFLONG, 0);  /* change array rescaling */
	class_addmethod(c, (method)gen17_list,       "list",     A_GIMME, 0);    /* the goods... */
	class_addmethod(c, (method)gen17_assist,     "assist",	A_CANT, 0);	// (optional) assistance method needs to be declared like this
    
	class_register(CLASS_BOX, c);
	gen17_class = c;
	post("gen17: by r. luke dubois, cmc");
}

// those methods

void gen17_bang(t_gen17 *x)
{
						
	DoTheDo(x);
	
}


void gen17_size(t_gen17 *x, long n)
{
	
	x->g_buffsize = n; // resize buffer
	if (x->g_buffsize>BUFFER) x->g_buffsize = BUFFER; // don't go beyond max limit of buffer

}

void gen17_offset(t_gen17 *x, long n)
{
	
	x->g_offset = n; // change buffer offset

}

void gen17_rescale(t_gen17 *x, long n)
{
	if(n>1) n = 1;
	if(n<0) n = 0;
	x->g_rescale = n; // change rescale flag

}


// instance creation...

void gen17_list(t_gen17 *x, t_symbol *s, short argc, t_atom *argv)
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

void DoTheDo(t_gen17 *x)
{
	short i,j;
	t_atom thestuff[2];
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
	t_gen17 *x;
	short c;
	
	x = (t_gen17 *)object_alloc(gen17_class);		// get memory for the object
    
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

void gen17_free(t_gen17 *x)
{
	if (x != NULL) {
		if (x->g_table != NULL) {
			sysmem_freeptr(x->g_table); // free the memory allocated for the table...
		}
	}
}

void gen17_assist(t_gen17 *x, void *b, long msg, long arg, char *dst)
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
