// gen20 -- random number generator.
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
#include "ext.h"
#include "ext_obex.h"

#include <math.h>
#include <time.h>

#define BUFFER 32768
#define PI 3.141592654 

// object definition structure...
typedef struct gen20
{
	t_object g_ob;				// required header
	void *g_out;				// an outlet
	long g_mode;				// random mode
	long g_buffsize;			// size of buffer
	long g_offset;				// offset into output buffer (for list output)
	float *g_table;				// internal array for computing the transfer function
} t_gen20;


/* global that holds the class definition */
t_class *gen20_class;

// function prototypes here...
void gen20_int(t_gen20 *x, long mode);
void gen20_assist(t_gen20 *x, void *b, long m, long a, char *s);
void gen20_bang(t_gen20 *x);
void gen20_offset(t_gen20 *x, long n);
void gen20_size(t_gen20 *x, long n);
void *gen20_new(long n, long o);
void gen20_free(t_gen20 *x);
void DoTheDo(t_gen20 *x);

// init routine...
void ext_main(void *f)
{
	t_class *c;
    
	c = class_new("gen20", (method)gen20_new, (method)gen20_free, sizeof(t_gen20), 0L, A_DEFLONG, A_DEFLONG, 0);
	class_addmethod(c, (method)gen20_bang,		"bang",		0);             // the method it uses when it gets a bang in the left inlet
	class_addmethod(c, (method)gen20_int,        "int",     A_LONG, 0);    /* the goods... */
	class_addmethod(c, (method)gen20_size,       "size",     A_DEFLONG, 0);  /* change buffer */
	class_addmethod(c, (method)gen20_offset,     "offset",   A_DEFLONG, 0);  /* change buffer offset */
	class_addmethod(c, (method)gen20_assist,     "assist",	A_CANT, 0);	// (optional) assistance method needs to be declared like this
    
	class_register(CLASS_BOX, c);
	gen20_class = c;
	post("gen20: by r. luke dubois, cmc");
}

// those methods

void gen20_bang(t_gen20 *x)
{
	DoTheDo(x);
}


void gen20_size(t_gen20 *x, long n)
{
	x->g_buffsize = n; // resize buffer
	if (x->g_buffsize>BUFFER) x->g_buffsize = BUFFER; // don't go beyond max limit of buffer
}

void gen20_offset(t_gen20 *x, long n)
{
	x->g_offset = n; // change buffer offset
}

// instance creation...

void gen20_int(t_gen20 *x, long mode)
{
	// parse the mode...
	if(mode<0) {
	error("don't know about mode %i", mode);
	x->g_mode = 0;
	}
	else if(mode>5) {
	error("don't know about mode %i", mode);
	x->g_mode = 0;
	}
	else {
	x->g_mode = mode;
	post("mode set to %i", mode);
	DoTheDo(x);
	}
}

void DoTheDo(t_gen20 *x)
{
	register short i,j;
	int k;
	t_atom thestuff[2];
	int N=12;
	float halfN = 6;
	float scale = 1;
	float mu = 0.5;
	float sigma = .166666;
	float randnum = 0.0;
	float randnum2 = 0.0;
	float output;
	float alpha = .00628338;
	float randfunc();
	static long randx=1;

    randx = gettime();
    
    switch(x->g_mode) {
        case 0: // even distribution
            for(i=0;i<x->g_buffsize;i++){
                k = ((randx = randx*1103515245 + 12345)>>16) & 077777;
                x->g_table[i] = (float)k/32768.0;
            }
            break;
        case 1: /* low weighted */
            for(i=0;i<x->g_buffsize;i++) {
                k = ((randx = randx*1103515245 + 12345)>>16) & 077777;
                randnum = (float)k/32768.0;
                k = ((randx = randx*1103515245 + 12345)>>16) & 077777;
                randnum2 = (float)k/32768.0;
                if(randnum2 < randnum) {
                    randnum = randnum2;
                }
                x->g_table[i] = randnum;
            }
            break;
        case 2: /* high weighted */
            for(i=0;i<x->g_buffsize;i++) {
                k = ((randx = randx*1103515245 + 12345)>>16) & 077777;
                randnum = (float)k/32768.0;
                k = ((randx = randx*1103515245 + 12345)>>16) & 077777;
                randnum2 = (float)k/32768.0;
                if(randnum2 > randnum) {
                    randnum = randnum2;
                }
                x->g_table[i] = randnum;
            }
            break;
        case 3: /* triangle */
            for(i=0;i<x->g_buffsize;i++) {
                k = ((randx = randx*1103515245 + 12345)>>16) & 077777;
                randnum = (float)k/32768.0;
                k = ((randx = randx*1103515245 + 12345)>>16) & 077777;
                randnum2 = (float)k/32768.0;
                x->g_table[i] = 0.5*(randnum+randnum2);
            }
            break;
        case 4: /* gaussian */
            i=0;
            while(i<x->g_buffsize) {
                randnum = 0.0;
                for(j=0;j<N;j++)
                {
                    k = ((randx = randx*1103515245 + 12345)>>16) & 077777;
                    randnum += (float)k/32768.0;
                }
                output = sigma*scale*(randnum-halfN)+mu;
                if((output<=1.0) && (output>=0.0)) {
                    x->g_table[i] = output;
                    i++;
                }
            }
            break;
        case 5: /* cauchy */
            i=0;
            while(i<x->g_buffsize)
            {
                do {
                    k = ((randx = randx*1103515245 + 12345)>>16) & 077777;
                    randnum = (float)k/32768.0;
                }
                while(randnum==0.5);
                randnum = randnum*PI;
                output=(alpha*tan(randnum))+0.5;
                if((output<=1.0) && (output>=0.0)) {
                    x->g_table[i] = output;
                    i++;
                }
            }
            break;   
        default:
            for(i=0;i<x->g_buffsize;i++) {
                x->g_table[i]=0.;
            }
            break;
    }
	// rescale the function to make sure it stays between -1. and 1.
	for(j = 0; j < x->g_buffsize; j++) {
		x->g_table[j] = (x->g_table[j]*2.0)-1.;
	}

	// output the random series in index/amplitude pairs...
	for(i=0;i<x->g_buffsize;i++) {
		SETLONG(thestuff,i+(x->g_offset*x->g_buffsize));
		SETFLOAT(thestuff+1,x->g_table[i]);
		outlet_list(x->g_out,0L,2,thestuff);
	}
}

void *gen20_new(long n, long o)
{
	t_gen20 *x;
	register short c;
	
	x = (t_gen20 *)object_alloc(gen20_class);		// get memory for the object

	x->g_offset = 0;
	if (o) {
		x->g_offset = o;
	}


// initialize function table size (must allocate memory)
	x->g_buffsize=512;
	x->g_mode = 0; // init mode

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

void gen20_free(t_gen20 *x)
{
	if (x != NULL) {
		if (x->g_table != NULL) {
			sysmem_freeptr(x->g_table); // free the memory allocated for the table...
		}
	}
}

void gen20_assist(t_gen20 *x, void *b, long msg, long arg, char *dst)
{
	switch(msg) {
		case 1: // inlet
			switch(arg) {
				case 0:
				sprintf(dst, "(int) Mode");
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
