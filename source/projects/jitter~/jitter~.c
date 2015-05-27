// jitter~ -- modifies an incoming signal by a jitter amount of jitter.
// 		by r. luke dubois (luke@music.columbia.edu), 
//			computer music center, columbia university, 2000.
//
// objects and source are provided without warranty of any kind, express or implied.
//

// include files...
#include <stdlib.h>
#include "ext.h"
#include "z_dsp.h"

// global for the class definition
void *jitter_class;

// my object structure
typedef struct _jitter
{
    t_pxobject r_obj; // this is an msp object...
    float range; // range of jitter generation
	long aflag; // whether to jitter at audio rate or when banged
	float jitter;
} t_jitter;

void *jitter_new(float flag, float a); // creation function
t_int *jitter_perform(t_int *w); // dsp perform function
void jitter_range(t_jitter *x, long n); // set jitter range
void jitter_manual(t_jitter *x, long n); // set jitter auto flag
void jitter_dsp(t_jitter *x, t_signal **sp, short *count); // dsp add function
void jitter_assist(t_jitter *x, void *b, long m, long a, char *s); // assistance function
void jitter_bang(t_jitter *x); // bang function

void ext_main(void* p)
{
    setup((t_messlist **)&jitter_class, (method)jitter_new, (method)dsp_free, (short)sizeof(t_jitter), 0L, A_DEFFLOAT, A_DEFFLOAT, 0);

	// declare the methods
    addmess((method)jitter_dsp, "dsp", A_CANT, 0);
    addmess((method)jitter_assist,"assist",A_CANT,0);
	addmess((method)jitter_range, "range", A_DEFLONG, 0);
	addmess((method)jitter_manual, "manual", A_DEFLONG, 0);
	addbang((method)jitter_bang);
    dsp_initclass(); // required for msp

	post("jitter~: by r. luke dubois, cmc");
}

// deal with the assistance strings...
void jitter_assist(t_jitter *x, void *b, long m, long a, char *s)
{
	switch(m) {
		case 1: // inlet
			switch(a) {
				case 0:
				sprintf(s, "(signal) Input");
				break;
			}
		break;
		case 2: // outlet
			switch(a) {
				case 0:
				sprintf(s, "(signal) Output");
				break;
			}
		break;
	}
}

// instantiate the object
void *jitter_new(float flag, float a)
{	
    t_jitter *x = (t_jitter *)newobject(jitter_class);
    dsp_setup((t_pxobject *)x,1);
    outlet_new((t_pxobject *)x, "signal");
	x->range = 0.0; // initialize argument
	x->jitter = 0.0;
	// if the arguments are there check them and set them
	if(flag) x->range = flag;
    if (x->range<=0.0) x->range=0.0;
    if (x->range>65535) x->range=65535;

	if(a) x->aflag = (long)a; else	x->aflag = 0; // auto-jitter enabled by default
    if (x->aflag<0) x->aflag = 0;
    if (x->aflag>1) x->aflag = 1;

    return (x);
}

void jitter_bang(t_jitter *x)
{
	x->jitter = ((((float)rand()/(float)RAND_MAX)*x->range)*2)-x->range;
}

void jitter_range(t_jitter *x, long n)
{
		x->range = n;
	    if (x->range<0.0) x->range = 0.0;
	    if (x->range>65535) x->range = 65535;
}

void jitter_manual(t_jitter *x, long n)
{
		x->aflag = n;
	    if (x->aflag<0) x->aflag = 0;
	    if (x->aflag>1) x->aflag = 1;
}

// go go go...
t_int *jitter_perform(t_int *w)
{
	t_jitter *x = (t_jitter *)w[1]; // get current state of my object class
	t_float *in, *out; // variables for input and output buffer
	int n; // counter for vector size

	// more efficient -- make local copies of class variables so i'm not constantly checking the globals...
	float range = x->range;
	int aflag = x->aflag;
	float jitter = x->jitter;

	in = (t_float *)(w[2]);
	out = (t_float *)(w[3]); // my output vector

	n = (int)(w[4]); // my vector size

	while (--n) { // loop executes a single vector
		if(!aflag) *++out = *++in + ((((float)rand()/(float)RAND_MAX)*range)*2)-range;
		else *++out = *++in + jitter;
	}

	return (w+6); // return one greater than the arguments in the dsp_add call
}

void jitter_dsp(t_jitter *x, t_signal **sp, short *count)
{
	// add to the dsp chain -- i need my class, my input vector, my output vector, and my vector size...
	dsp_add(jitter_perform, 5, x, sp[0]->s_vec-1, sp[1]->s_vec-1, sp[0]->s_n+1);
}

