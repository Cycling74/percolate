// weave~ -- puts out pwm based on zerocrossings... sort of a subharmonic oscillator.
// sort of like how the boss octave pedal works, but a little wackier.
// 		by r. luke dubois (luke@music.columbia.edu), 
//			computer music center, columbia university, 2000.
//
// objects and source are provided without warranty of any kind, express or implied.
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

// include files...
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

// global for the class definition
t_class *weave_class;

// my object structure
typedef struct _weave
{
    t_pxobject w_obj; // this is an msp object...
    long min_val; // number of high to low crossings to count as a -1.
    long max_val; // number of low to high crossings to count as a 1.
    long pwm, cval_old; // current state of pwm and last state of previous vector
    long upcount, downcount; // current count of how many crossings have occured
	void *w_proxy[2]; // two proxy inlets for setting the min and max number of crossings
	long w_inletnumber; // inlet number for the crossing function
} t_weave;

void *weave_new(long neg, long pos); // creation function
void weave_free(t_weave *x); // free function (we use proxies, so can't just be dsp_free()
void weave_assist(t_weave *x, void *b, long m, long a, char *s); // assistance function

void weave_int(t_weave *x, long n); // what to do with an int

// dsp stuff
void weave_dsp64(t_weave *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void weave_perform64(t_weave *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void ext_main(void* p)
{
    t_class *c = class_new("weave~", (method)weave_new, (method)weave_free, (long)sizeof(t_weave), 0L, A_DEFLONG, A_DEFLONG, 0);
    
    class_addmethod(c, (method)weave_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)weave_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)weave_int, "int", A_LONG, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    weave_class = c;
	post("weave~: by r. luke dubois, cmc");
}

// deal with the assistance strings...
void weave_assist(t_weave *x, void *b, long m, long a, char *s)
{
	switch(m) {
		case 1: // inlet
			switch(a) {
				case 0:
				sprintf(s, "(signal) Input");
				break;
				case 1:
				sprintf(s, "(int) Lower Crossing Threshhold");
				break;
				case 2:
				sprintf(s, "(int) Upper Crossing Threshhold");
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
void *weave_new(long neg, long pos)
{	
    t_weave *x = (t_weave *)object_alloc(weave_class);
    dsp_setup((t_pxobject *)x,1);
	x->w_proxy[1] = proxy_new(x,2L,&x->w_inletnumber);
	x->w_proxy[0] = proxy_new(x,1L,&x->w_inletnumber);
    outlet_new((t_pxobject *)x, "signal");
	x->max_val = 2; // initialize arguments
	x->min_val = 2;
	
	// if the arguments are there check them and set them
    if(pos) x->max_val = pos;
    if(neg) x->min_val = neg;
    if (x->max_val<1) x->max_val=1;
    if (x->min_val<1) x->min_val=1;
    
    x->pwm=0; // start out with pwm low
	x->cval_old=0; // clear current state
    x->upcount=0; // start counting from scratch
    x->downcount=0;

    return (x);
}

void weave_free(t_weave *x)
{
	freeobject(x->w_proxy[1]); // flush the proxies
	freeobject(x->w_proxy[0]);
	dsp_free(&x->w_obj); // flush the dsp memory
}

// this routine covers both inlets. It doesn't matter which one is involved
void weave_int(t_weave *x, long n)
{
	if (x->w_inletnumber==1) { // 'minimum' value
		x->min_val = n;
	    if (x->min_val<1) x->min_val=1;
	}
	if (x->w_inletnumber==2) { // 'maximum' value
		x->max_val = n;
	    if (x->max_val<1) x->max_val=1;
	}
}

// dsp stuff
void weave_dsp64(t_weave *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, weave_perform64, 0, NULL);
}

void weave_perform64(t_weave *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    t_double *in,*out; // variables for input and output buffer
    int n; // counter for vector size
    
    // more efficient -- make local copies of class variables so i'm not constantly checking the globals...
    int pwm = x->pwm;
    int upcount = x->upcount;
    int downcount = x->downcount;
    int max_val = x->max_val;
    int min_val = x->min_val;
    int cval_old = x->cval_old;
    
    int cval_new; // local variable to get polarity of current sample
    
    in = (t_double *)(ins[0]); // my input vector
    out = (t_double *)(outs[0]); // my output vector
    
    n = sampleframes; // my vector size
    
    while (--n) { // loop executes a single vector
        if (*++in>0.0) {
            cval_new=1;
        }
        else cval_new=0; // check current sample and assign its polarity to cval_new
        if(cval_new==cval_old) // check to see if a zerocrossing has occured since the last sample
        {
            goto end; // if not, nothing has changed, so you can just put out the last value...
        }
        else
        {
            if(cval_new==1) // we went from low to high
            {
                if (pwm) { // we're already high
                    if (upcount>=max_val) { // we've been high for long enough (ha ha ha)
                        pwm=0; // drive pwm low
                        upcount=0; // reset high count
                        downcount++; // start downcount
                    }
                    else {
                        upcount++; // increment upcount
                    }
                }
            }
            if(cval_new==0) // we went from high to low
            {
                if (!pwm) { // we're already low
                    if (downcount>=min_val) { // we've been low for long enough...
                        pwm=1; // drive pwm high
                        downcount=0; // reset low count
                        upcount++; // start upcount
                    }
                    else {
                        downcount++; // increment downcount
                    }		
                }		
            }
        }
    end: // get us out of this mess...
        if(pwm==0) {
            *++out = -1.; // pwm low, put out a -1. signal
        }
        if(pwm==1) {
            *++out = 1.; // pwm high, put out a 1. signal
        }
        cval_old = cval_new; // keep track of previous state
    }
    x->cval_old=cval_old; // store state of cval_old across to a new vector
    x->pwm=pwm; // store state of variables that may have changed...
    x->upcount=upcount;
    x->downcount=downcount;
}
