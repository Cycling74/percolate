#include "ext.h"
#include "z_dsp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#define TWOPI 6.283185307

void *dcblock_class;

typedef struct _dcblock
{
	//header; keep this
    t_pxobject x_obj;

    //DC blocker
    float dc_input, dc_output;
    
    float srate, one_over_srate;
} t_dcblock;

/****PROTOTYPES****/

//setup funcs; needed for all objects
void *dcblock_new(double val); //called when the object is created
void dcblock_dsp(t_dcblock *x, t_signal **sp, short *count); //called when audio is turned on
t_int *dcblock_perform(t_int *w); //called every signal vector
void dcblock_assist(t_dcblock *x, void *b, long m, long a, char *s); //for getting assistance when rolling mouse over inputs/outputs

//DC blocker
float dcblock_tick(t_dcblock *x, float sample); //my own method; high-pass filter


/****FUNCTIONS****/

void dcblock_assist(t_dcblock *x, void *b, long m, long a, char *s)
{
	assist_string(3214,m,a,1,2,s);
}


//DC blocker
float dcblock_tick(t_dcblock *x, float sample)
{
	x->dc_output = sample - x->dc_input + (0.99 * x->dc_output);
	x->dc_input = sample;
	return x->dc_output;
}

//primary MSP funcs
void ext_main(void* p)
{
	//basic setup of the object
    setup((struct messlist **)&dcblock_class, (method)dcblock_new, (method)dsp_free, (short)sizeof(t_dcblock), 0L, A_DEFFLOAT, 0);
    //add more penultimate arguments (A_DEFLONG, ....) if you want to be able to use more arguments
    
    //addmess lets you add message types, and address the functions that they should call.
    addmess((method)dcblock_dsp, "dsp", A_CANT, 0); //essential messages
    addmess((method)dcblock_assist,"assist",A_CANT,0); //assist message; essential
    
    //gotta have this
    dsp_initclass();
    rescopy('STR#',3214); //only needed if using resource files for assistance
}

//one argument (as specified in the "setup" call above, which isn't actually used in this particular object
void *dcblock_new(double initial_coeff)
{
	int i;

	//new object
    t_dcblock *x = (t_dcblock *)newobject(dcblock_class);
    
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_dcblock);i++)  
                ((char *)x)[i]=0; 
	} 
	
	//set it up, with the number of audio inputs that you want
    dsp_setup((t_pxobject *)x,1);
    
    //set up the number of outputs that you want
    outlet_new((t_object *)x, "signal");

	/* //obsolete
    x->srate = sys_getsr();
    x->one_over_srate = 1./x->srate;
    */
    
    //init variables
    x->dc_input = 0.; x->dc_output = 0.;
    
    return (x);
}


void dcblock_dsp(t_dcblock *x, t_signal **sp, short *count)
{
	
	//initialize sampling rate
	x->srate = sp[0]->s_sr;
	x->one_over_srate = 1./x->srate;

	//add us to the DSP chain; this needs to change depending on how many ins/outs we have
	dsp_add(dcblock_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);	
	//dsp_add(perform_method, num_args to follow, the object itself, the input vector, this output vector, number of samps per vector)	
	
	// an example of this call for a larger object....
	//dsp_add(munger_perform, 12, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, \
		//sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec, sp[8]->s_vec, sp[9]->s_vec, sp[0]->s_n);	
	
}

t_int *dcblock_perform(t_int *w)
{
	//get back the pointer to our struct
	t_dcblock *x = (t_dcblock *)(w[1]);

	//get the in and out signal vector pointers (corresponds to places in the dsp_add call above)
	float *in = (float *)(w[2]);
	float *out = (float *)(w[3]);
	
	//get the vector size
	long n = w[4];
	
	//run the effect loop, for each sample in the vector
	while(n--) {	
		//out is a pointer to the first sample in the output vector
		//in is a pointer to the first sample of the input vector
		//we have to manually increment these after we access them	
		*out++ = dcblock_tick(x, *in++);
	}
	
	//return a pointer to the next object (will always be dsp_add argument number two + 1)
	return w + 5;
}	

