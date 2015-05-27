// klutz~ -- reverses the order of samples in a vector.
// 		by r. luke dubois (luke@music.columbia.edu), 
//			computer music center, columbia university, 2001.
//
// objects and source are provided without warranty of any kind, express or implied.
//

// include files...
// #include <stdlib.h>
#include "ext.h"
#include "z_dsp.h"
#include "math.h"

// global for the class definition
void *klutz_class;

// my object structure
typedef struct _klutz
{
    t_pxobject r_obj; // this is an msp object...
} t_klutz;

void *klutz_new(float flag, float a); // creation function
t_int *klutz_perform(t_int *w); // dsp perform function
void klutz_dsp(t_klutz *x, t_signal **sp, short *count); // dsp add function
void klutz_assist(t_klutz *x, void *b, long m, long a, char *s); // assistance function

void ext_main(void* p)
{
    setup((t_messlist **)&klutz_class, (method)klutz_new, (method)dsp_free, (short)sizeof(t_klutz), 0L, A_DEFFLOAT, A_DEFFLOAT, 0);

	// declare the methods
    addmess((method)klutz_dsp, "dsp", A_CANT, 0);
    addmess((method)klutz_assist,"assist",A_CANT,0);
    dsp_initclass(); // required for msp

	post("klutz~: by r. luke dubois, cmc");
}

// deal with the assistance strings...
void klutz_assist(t_klutz *x, void *b, long m, long a, char *s)
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
void *klutz_new(float flag, float a)
{	
    t_klutz *x = (t_klutz *)newobject(klutz_class);
    dsp_setup((t_pxobject *)x,1);
    outlet_new((t_pxobject *)x, "signal");

    return (x);
}


// go go go...
t_int *klutz_perform(t_int *w)
{
	t_klutz *x = (t_klutz *)w[1]; // get current state of my object class
	t_float *in, *out; // variables for input and output buffer
	int n; // counter for vector size

	in = (t_float *)(w[2]);
	out = (t_float *)(w[3]); // my output vector

	for (n=0;n<(int)(w[4]);n++) {
		*++in; // my vector size
	}
	while(--n) {
	    *++out = *--in;
	}

	return (w+6); // return one greater than the arguments in the dsp_add call
}

void klutz_dsp(t_klutz *x, t_signal **sp, short *count)
{
	// add to the dsp chain -- i need my class, my input vector, my output vector, and my vector size...
	dsp_add(klutz_perform, 5, x, sp[0]->s_vec-1, sp[1]->s_vec-1, sp[0]->s_n+1);
}

