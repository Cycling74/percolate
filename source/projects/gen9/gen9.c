// gen9 -- writes a wavetable from a triplet list of harmonic, amp, phase.
//		by r. luke dubois (luke@music.columbia.edu),
//			computer music center, columbia university, 2001.
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

// maximum number of p-fields specified in a list -- if you make it larger you better
// allocated the memory dynamically (right now it's using built-in memory)...
#define MAXSIZE 64
#define BUFFER 32768

// maximum size of wavetable -- this memory is allocated with NewPtr()
#define PI2 6.2831853    // the big number...

// t_object definition structure...
typedef struct gen9 {
	t_object g_ob;               // required header
	void*    g_out;              // an outlet
	long     g_numpoints;        // number of points in the bpf
	long     g_buffsize;         // size of buffer
	long     g_offset;           // offset into the output buffer (for list output)
	float    g_args[MAXSIZE];    // array for the harmonic fields
	float*   g_table;            // internal array for the wavetable
	long     g_rescale;          // flag to rescale array
} t_gen9;


/* globalthat holds the class definition */
t_class* gen9_class;

// function prototypes here...
void  gen9_list(t_gen9* x, t_symbol* s, long ac, t_atom* av);
void  gen9_assist(t_gen9* x, void* b, long m, long a, char* s);
void  gen9_bang(t_gen9* x);
void  gen9_offset(t_gen9* x, long n);
void  gen9_size(t_gen9* x, long n);
void  gen9_rescale(t_gen9* x, long n);
void* gen9_new(long n, long o);
void  gen9_free(t_gen9* x);
void  DoTheDo(t_gen9* x);

// init routine...
void ext_main(void* f) {
	t_class* c;

	c = class_new("gen9", (method)gen9_new, (method)gen9_free, sizeof(t_gen9), 0L, A_DEFLONG, A_DEFLONG, 0);

	class_addmethod(c, (method)gen9_bang, "bang", 0);                  // the method it uses when it gets a bang in the left inlet
	class_addmethod(c, (method)gen9_size, "size", A_DEFLONG, 0);       /* change buffer */
	class_addmethod(c, (method)gen9_offset, "offset", A_DEFLONG, 0);   /* change buffer offset */
	class_addmethod(c, (method)gen9_rescale, "rescale", A_DEFLONG, 0); /* change array rescaling */
	class_addmethod(c, (method)gen9_list, "list", A_GIMME, 0);         /* the goods... */
	class_addmethod(c, (method)gen9_assist, "assist", A_CANT, 0);      // (optional) assistance method needs to be declared like this

	class_register(CLASS_BOX, c);
	gen9_class = c;
	post("gen9: by r. luke dubois, cmc");
}

// those methods

void gen9_bang(t_gen9* x) {

	DoTheDo(x);
}

void gen9_size(t_gen9* x, long n) {

	x->g_buffsize = n;    // resize buffer
	if (x->g_buffsize > BUFFER)
		x->g_buffsize = BUFFER;
}

void gen9_offset(t_gen9* x, long n) {

	x->g_offset = n;    // change buffer offset
}

void gen9_rescale(t_gen9* x, long n) {
	if (n > 1)
		n = 1;
	if (n < 0)
		n = 0;
	x->g_rescale = n;    // change rescale flag
}

// instance creation...

void gen9_list(t_gen9* x, t_symbol* s, long argc, t_atom* argv) {

	// parse the list of incoming harmonics...
	short i;
	for (i = 0; i < argc; i++) {
		if (argv[i].a_type == A_LONG) {
			x->g_args[i] = (float)argv[i].a_w.w_long;
		}
		else if (argv[i].a_type == A_FLOAT) {
			x->g_args[i] = argv[i].a_w.w_float;
		}
	}
	x->g_numpoints = argc;
	DoTheDo(x);
}

void DoTheDo(t_gen9* x) {
	short  i, j;
	t_atom thestuff[2];
	float  wmax, xmax = 0.0;
	double sin();


	for (i = 0; i < x->g_buffsize; i++)
		x->g_table[i] = 0;

	for (j = x->g_numpoints - 1; j > 0; j -= 3) {
		if (x->g_args[j - 1] != 0) {
			for (i = 0; i < x->g_buffsize; i++) {
				x->g_table[i] += (float)(sin(PI2 * ((float)i / ((float)(x->g_buffsize) / x->g_args[j - 2]) + x->g_args[j] / 360.))
					* x->g_args[j - 1]);
			}
		}
	}

	if (x->g_rescale) {
		// rescale the wavetable to go between -1. and 1.
		for (j = 0; j < x->g_buffsize; j++) {
			if ((wmax = fabs(x->g_table[j])) > xmax)
				xmax = wmax;
		}
		for (j = 0; j < x->g_buffsize; j++) {
			x->g_table[j] /= xmax;
		}
	}

	// output the wavetable in index, amplitude pairs...
	for (i = 0; i < x->g_buffsize; i++) {
		atom_setlong(thestuff, i + (x->g_offset * x->g_buffsize));
		atom_setfloat(thestuff + 1, x->g_table[i]);
		outlet_list(x->g_out, 0L, 2, thestuff);
	}
}

void* gen9_new(long n, long o) {
	t_gen9* x;
	short   c;

	x = (t_gen9*)object_alloc(gen9_class);    // get memory for the object

	x->g_offset = 0;
	if (o) {
		x->g_offset = o;
	}

	for (c = 0; c < MAXSIZE; c++)    // initialize bpf array (static memory)
	{
		x->g_args[c] = 0.0;
	}

	// initialize wavetable size (must allocate memory)
	x->g_buffsize = 512;

	x->g_rescale = 1;


	if (n) {
		x->g_buffsize = n;
		if (x->g_buffsize > BUFFER)
			x->g_buffsize = BUFFER;    // size the wavetable
	}

	x->g_table = NULL;
	x->g_table = (float*)sysmem_newptr(sizeof(float) * BUFFER);
	if (x->g_table == NULL) {
		error("memory allocation error\n");    // whoops, out of memory...
		return (x);
	}

	for (c = 0; c < x->g_buffsize; c++) {
		x->g_table[c] = 0.0;
	}
	x->g_out = listout(x);    // create a list outlet
	return (x);               // return newly created t_object and go go go...
}

void gen9_free(t_gen9* x) {
	if (x != NULL) {
		if (x->g_table != NULL) {
			sysmem_freeptr(x->g_table);    // free the memory allocated for the table...
		}
	}
}

void gen9_assist(t_gen9* x, void* b, long msg, long arg, char* dst) {
	switch (msg) {
		case 1:    // inlet
			switch (arg) {
				case 0:
					sprintf(dst, "(list) Breakpoint Function for Waveform");
					break;
			}
			break;
		case 2:    // outlet
			switch (arg) {
				case 0:
					sprintf(dst, "(list) Index/Amplitude Pairs");
					break;
			}
			break;
	}
}
