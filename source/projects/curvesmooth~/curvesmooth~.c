/* curvesmooth~								*/
/* like rampsmooth, sorta					*/
/* but allows user to set the curvature		*/
/* of the following signal logartimically	*/
/* or exponentially
/*
/* useful for conditioning sensor			*/
/* signals									*/
//
//dt 2005; yet another PeRColate hack

/*
here's the math:
	t = target value, updated each sample
	d = distance between t and current value c = abs(t - c)
	D = maximum distance that could be traveled, set to 1 (range of 0 to 1) when "mode" is 0.
		when the "mode" toggle is set, D is updated continously based on changes
		in the input signal. this will create variable curves (and generally more smoothing)
		but be a bit less predictable. 
	T = number of sample required to travel D, set by user
	T_up = T for ascending signals
	T_down = T for descending signals
	k = curvature coefficient
	k_up = curvature coef for ascending signals
	k_down = curvature coef for descending signals
	s = step size; how much to increment the current value towards t
		when k = 1, we are linear (like rampsmooth), and s = D/T
		otherwise s = d(k-1) / ((k^(d/D) - 1)*T) (must sign this according to sign of t-c)
		when k>1, we have exponential following curves
		when k<1, we have logorithmic following curves
	
	basically, the user is choosing how long (T) it should
	take to travel the full range (D); this establishes a baseline speed (D/T).
	if k=1, it always moves at that speed. however, for other values of k,
	the speed varies depending on its distance (d) from the target (t).
*/

#include "ext.h"
#include "z_dsp.h"
#include "ext_strings.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_INPUTS 5 	//arbitrary
#define MAX_OUTPUTS 2	//also arbitrary

//#define D 1.
//#define one_over_D 1.
#define TABLE_SIZE 1001

void *curvesmooth_class;

typedef struct _curvesmooth
{
	//header
    t_pxobject x_obj;
    
    //variables specific to this object
    double srate, one_over_srate, srate_ms;  	//sample rate vars
    long num_inputs, num_outputs; 	//number of inputs and outputs
    float in[MAX_INPUTS];			//values of input variables
    float in_connected[MAX_INPUTS]; //booleans: true if signals connected to the input in question
    
    double c, D;
    short update_D;					//update D? if not, D=1
    short current_direction;
    
    double *s_table_k_exp[TABLE_SIZE];	//2D lookup table [s, k], k>1
    double *s_table_k_log[TABLE_SIZE];	//k<1

    short power;					//i like objects, especially CPU intensive ones, to have their own
    								//"power" messages so that you can bypass them individually

    
} t_curvesmooth;


/****PROTOTYPES****/

//setup funcs; this probably won't change, unless you decide to change the number of
//args that the user can input, in which case curvesmooth_new will have to change
void *curvesmooth_new(double upsmooth, double downsmooth, double upcoeff, double downcoeff);
void curvesmooth_free(t_curvesmooth *x);
void curvesmooth_dsp(t_curvesmooth *x, t_signal **sp, short *count); 
t_int *curvesmooth_perform(t_int *w);
void curvesmooth_assist(t_curvesmooth *x, void *b, long m, long a, char *s);

//for getting floats at inputs
void curvesmooth_float(t_curvesmooth *x, double f);

//for custom messages
void curvesmooth_setupdate(t_curvesmooth *x, Symbol *s, short argc, Atom *argv);
void curvesmooth_setpower(t_curvesmooth *x, Symbol *s, short argc, Atom *argv);
double table_lookup(t_curvesmooth *x, double d, double k);


/****FUNCTIONS****/

//primary MSP funcs
void main(void)
{
	//the two A_DEFLONG arguments give us the two arguments for the user to set number of ins/outs
	//change these if you want different user args
    setup((struct messlist **)&curvesmooth_class, (method)curvesmooth_new, (method)curvesmooth_free, (short)sizeof(t_curvesmooth), 0L, A_DEFLONG, A_DEFLONG, A_DEFFLOAT, A_DEFFLOAT, 0);
   
	//standard messages; don't change these  
    addmess((method)curvesmooth_dsp, "dsp", A_CANT, 0);
    addmess((method)curvesmooth_assist,"assist", A_CANT,0);
    
    //our own messages
    addmess((method)curvesmooth_setupdate, "mode", A_GIMME, 0);
    addmess((method)curvesmooth_setpower, "power", A_GIMME, 0);
    
    //so we know what to do with floats that we receive at the inputs
    addfloat((method)curvesmooth_float);
    
    //gotta have this one....
    dsp_initclass();
}

//this gets called when the object is created; everytime the user types in new args, this will get called
void *curvesmooth_new(double upsmooth, double downsmooth, double upcoeff, double downcoeff) //up/down smooth in ms
{
	int i, j;
	
	//leave this; creates our object
    t_curvesmooth *x = (t_curvesmooth *)newobject(curvesmooth_class);
    
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_curvesmooth);i++)  
                ((char *)x)[i]=0; 
	} 
	
	x->num_inputs = 5;
	x->num_outputs = 1;

	//setup up inputs and outputs, for audio
	
	//inputs
    dsp_setup((t_pxobject *)x, x->num_inputs);
    //if you just need one input for message (not using audio), you can just set num_inputs = 1
    //i don't think this causes a performance hit.
    
    //outputs
    for (i=0;i<x->num_outputs;i++) {
    	outlet_new((t_object *)x, "signal");
    }   
    //can use intin, floatout, listout, etc... for setting up non-audio ins and outs.
    //but, the order in which you call these funcs is important.
    //for instance, from gQ~
    /*    
    x->outfloat = floatout((t_object *)x);
    x->outlist = listout((t_object *)x);
    outlet_new((t_object *)x, "signal");
    outlet_new((t_object *)x, "signal");
   */
   //this will create four outputs, *rightmost* created first, so the outlets, from left to right, will look like
   //(signal) (signal) (list) (float)
   //when you instantiate gQ~ in Max/MSP.
    
    //initialize some variables; important to do this!
    for (i=0;i<x->num_inputs;i++){
    	x->in[i] = 0.;
    	x->in_connected[i] = 0;
    }
    x->power = 1;

	x->in[1] = upsmooth;
	x->in[2] = downsmooth;
	x->in[3] = upcoeff;
	x->in[4] = downcoeff;
	x->c = 0.;
	x->update_D = 1;
	x->current_direction = 1;
	x->D = 0.;
	
	//lookup table alloc and init
	for(i=0;i<TABLE_SIZE;i++) {
	    //x->s_table_k_exp[i]= t_getbytes(TABLE_SIZE*sizeof(double));
	    x->s_table_k_exp[i]= (double *)sysmem_newptr(TABLE_SIZE*sizeof(double));
		if (!x->s_table_k_exp[i]) {
			error("curvesmooth~: out of memory");
			return;
		}
			
		//x->s_table_k_log[i] = t_getbytes(TABLE_SIZE*sizeof(double));
		x->s_table_k_log[i] = (double *)sysmem_newptr(TABLE_SIZE*sizeof(double));
		if (!x->s_table_k_log[i]) {
			error("curvesmooth~: out of memory");
			return;
		}
	}
	for(i=2;i<TABLE_SIZE;i++) { //k, indices 2 to 1000 (exp) and 1 to 1000 (log, so .001 to 1, though we should never use 1)
		for(j=1;j<TABLE_SIZE;j++) { //d or d/D, 0 to 1
			x->s_table_k_exp[i][j] = (i-1.) / ((powf(i, j*.001) - 1.));
			x->s_table_k_log[i-1][j] = ((i-1.)*.001 - 1.) / ((powf((i-1.)*.001, j*.001) - 1.));
		}
		x->s_table_k_exp[i][0] = 0.;
		x->s_table_k_log[i][0] = 0.;
	}

	//occasionally this line is necessary if you are doing weird asynchronous things with the in/out vectors
	//x->x_obj.z_misc = Z_NO_INPLACE;

    return (x);
}


//this gets called when an object is destroyed. do stuff here if you need to clean up.
void curvesmooth_free(t_curvesmooth *x)
{
	int i;
	
	//gotta call this one, *before* you free other resources! thanks to Rob Sussman for pointing this out to me.
	dsp_free((t_pxobject *)x);
	
	for(i=0;i<TABLE_SIZE;i++) {
		if (x->s_table_k_exp[i])
			//t_freebytes(x->s_table_k_exp[i], TABLE_SIZE*sizeof(double));
			sysmem_freeptr(x->s_table_k_exp[i]);
		if (x->s_table_k_log[i])
			//t_freebytes(x->s_table_k_log[i], TABLE_SIZE*sizeof(double));
			sysmem_freeptr(x->s_table_k_log[i]);
	}
}


//this gets called everytime audio is started; even when audio is running, if the user
//changes anything (like deletes a patch cord), audio will be turned off and
//then on again, calling this func.
//this adds the "perform" method to the DSP chain, and also tells us
//where the audio vectors are and how big they are
void curvesmooth_dsp(t_curvesmooth *x, t_signal **sp, short *count)
{
	void *dsp_add_args[MAX_INPUTS + MAX_OUTPUTS + 2];
	int i;

	//set sample rate vars
	x->srate = sp[0]->s_sr;
	x->one_over_srate = 1./x->srate;
	x->srate_ms = x->srate * .001;
	
	//check to see if there are signals connected to the various inputs
	for(i=0;i<x->num_inputs;i++) x->in_connected[i]	= count[i];
	
	//construct the array of vectors and stuff
	dsp_add_args[0] = x; //the object itself
    for(i=0;i< (x->num_inputs + x->num_outputs); i++) { //pointers to the input and output vectors
    	dsp_add_args[i+1] = sp[i]->s_vec;
    }
    dsp_add_args[x->num_inputs + x->num_outputs + 1] = (void *)sp[0]->s_n; //pointer to the vector size
	dsp_addv(curvesmooth_perform, (x->num_inputs + x->num_outputs + 2), dsp_add_args); //add them to the signal chain
	
}

//this is where the action is
//we get vectors of samples (n samples per vector), process them and send them out
t_int *curvesmooth_perform(t_int *w)
{
	t_curvesmooth *x = (t_curvesmooth *)(w[1]);

	float *in[MAX_INPUTS]; 		//pointers to the input vectors
	float *out[MAX_OUTPUTS];	//pointers to the output vectors

	long n = w[x->num_inputs + x->num_outputs + 2];	//number of samples per vector
	
	//random local vars
	int i, skip_calc, direction;
	double c, t, d, k, k_up, k_down, s, T, T_up, T_down, D;
	
	//check to see if we should skip this routine if the patcher is "muted"
	//i also setup of "power" messages for expensive objects, so that the
	//object itself can be turned off directly. this can be convenient sometimes.
	//in any case, all audio objects should have this
	if (x->x_obj.z_disabled || (x->power == 0)) goto out;
	
	//check to see if we have a signal or float message connected to input
	//then assign the pointer accordingly
	for (i=0;i<x->num_inputs;i++) {
		in[i] = x->in_connected[i] ? (float *)(w[i+2]) : &x->in[i];
	}
	
	//assign the output vectors
	for (i=0;i<x->num_outputs;i++) {
		out[i] = (float *)(w[x->num_inputs+i+2]);
	}
	
	D = x->D;
	
	while(n--) {	//this is where the action happens..... let's make something up

		//assign the inputs
		if(x->in_connected[0]) t = *in[0]++; //use the signal vector if there is one
		else t = *in[0];					 //otherwise use the global variable
		if(x->in_connected[1]) T_up = (double)*in[1]++; 
		else T_up = (double)*in[1];					 
		if(x->in_connected[2]) T_down = (double)*in[2]++; 
		else T_down = (double)*in[2];					 
		if(x->in_connected[3]) k_up = (double)*in[3]++; 
		else k_up = (double)*in[3];					
		if(x->in_connected[4]) k_down = (double)*in[4]++; 
		else k_down = (double)*in[4];		
		
		c = x->c;
		
		//determine which direction we are going; make it symmetrical around 0
		skip_calc = 0;

		if (t>0.) 	{
			if(t>c) {
				k = k_up;
				T = T_up * x->srate_ms;
			} else if (t<c) {
				k = k_down;
				T = T_down * x->srate_ms;
			} else { //t must = c
				s = 0.;
				c=t;
				skip_calc = 1;
			}
		} else if(t<0.) {
			if(t>c) {
				k = k_down;
				T = T_down * x->srate_ms;
			} else if (t<c) {
				k = k_up;
				T = T_up * x->srate_ms;
			} else { //t must = c
				s = 0.;
				skip_calc = 1;
			}
		} else { //t == 0., so always in "decreasing" mode.
			if(t!=c) {
				k = k_down;
				T = T_down * x->srate_ms;
			} else { //t must = c
				s = 0.;
				c=t;
				skip_calc = 1;
			}
		}
		
		//if smooth time is 0, set c to t immediately and skip calculations
		if(T < 1.) {
			skip_calc = 1;
			c = t;
			s = 0.;
		}
		
		//distance
		d = fabs(t-c);
		
		//calculate s
		if(!x->update_D) {//when D is constant 1
			D = 1.;
			if(!skip_calc) {
				if(k==1.) s = D/T;
				else {
					if(d>D) d = D;
					//s = d*(k-1.) / ((powf(k, d) - 1.) * T);	//should turn this into a lookup table, in which case
															//it would be best not to modulate k. or could make 2D
															//lookup table s(d, k), with k constrained to, say, .001 to 1000
															//then, any of the parameters could be modulated. 
															//truncate k's to table indices, interpolate d's linearly.
															//could also map k so -1 -> .001, and 1 -> 1000
															
					s = table_lookup(x, d, k) * d/T;		//and here it is!
				}
				if ((t-c) < 0.) s = -s;
			} else s = 0.;
							 
			//assign new current
			if (s>d) s = d; //make sure we don't overshoot
			else if (s<-d) s = -d;
			x->c = c + s;
				
			for(i=0;i<x->num_outputs;i++) *out[i]++ = x->c;
			
		} else {//when D varies
			if(!skip_calc) {
				//update D if we change directions or if we stretch beyond current D
				if(d>D) D=d;
				if(t<c) direction = -1;
				else direction = 1;
				if (direction != x->current_direction) {
					D=d;
					x->current_direction = direction;
				}
				if(k==1.) s = D/T;
				else {
					//s = d*(k-1.) / ((powf(k, d/D) - 1.) * T);	//again, lookup table,this time s(d/D, k)
					s = table_lookup(x, d/D, k) * d/T;
				}
				if ((t-c) < 0.) s = -s;	
			} else s = 0.;
							 
			//assign new current
			if (s>d) s = d; //make sure we don't overshoot
			else if (s<-d) s = -d;
			x->c = c + s;
				
			for(i=0;i<x->num_outputs;i++) *out[i]++ = x->c;
		}

	}
	
	//return a pointer to the next object in the signal chain.
out:
	x->D = D;
	return w + x->num_inputs + x->num_outputs + 3;
}	


double table_lookup(t_curvesmooth *x, double d, double k)
{

	int k_index, d_index;
	double s1, s2, interp;
	
	if(k<1.) { //log
		k *= 1000.;
		d *= 1000.;
		k_index = (int)(k);
		d_index = (int)(d);
		s1 = x->s_table_k_log[k_index][d_index];
		s2 = x->s_table_k_log[k_index][d_index+1];
		interp = d - (double)d_index;
		return s2*interp + s1*(1.-interp);
	} else { //exp
		d *= 1000.;
		k_index = (int)(k);
		d_index = (int)(d);
		s1 = x->s_table_k_exp[k_index][d_index];
		s2 = x->s_table_k_exp[k_index][d_index+1];
		interp = d - (double)d_index;
		return s2*interp + s1*(1.-interp);
	}
		
}

//tells the user about the inputs/outputs when mousing over them
void curvesmooth_assist(t_curvesmooth *x, void *b, long m, long a, char *s)
{
	int i;
	//could use switch/case inside for loops, to give more informative assist info....
	if (m==1) {
		for(i=0;i<x->num_inputs;i++) {
			if (a==0)  sprintf(s, "target (signal)");
			if (a==1)  sprintf(s, "upsmooth time (signal/float)");
			if (a==2)  sprintf(s, "downsmooth time (signal/float)");
			if (a==3)  sprintf(s, "upsmooth coeff (signal/float)");
			if (a==4)  sprintf(s, "downsmooth coeff (signal/float)");
		}
	}
	if (m==2) {
		for(i=0;i<x->num_outputs;i++)
			if (a==0)  sprintf(s, "output (signal)");
	}
}


//this gets called when ever a float is received at *any* input
void curvesmooth_float(t_curvesmooth *x, double f)
{
	int i;
	
	//check to see which input the float came in, then set the appropriate variable value
	for(i=0;i<x->num_inputs;i++) {
		if (x->x_obj.z_in == i) {
			x->in[i] = f;
			//post("template~: setting in[%d] =  %f", i, f);
		} 
	}
}


//what to do when we get the message "mymessage" and a value (or list of values)
void curvesmooth_setupdate(t_curvesmooth *x, Symbol *s, short argc, Atom *argv)
{
	short i;
	float temp;
	long temp2; 
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				x->update_D = (short)argv[i].a_w.w_long;
				//probably should comment these out when the object is debugged.
    			//post("curvesmooth~: setting updatemode to %d", x->update_D);
				break;
			case A_FLOAT:
				x->update_D = (short)argv[i].a_w.w_float;
    			//post("curvesmooth~: setting updatemode to %d", x->update_D);
				break;
		}
	}
}

//what to do when we get the message "mymessage" and a value (or list of values)
void curvesmooth_setpower(t_curvesmooth *x, Symbol *s, short argc, Atom *argv)
{
	short i;
	float temp;
	long temp2; 
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp2 = argv[i].a_w.w_long;
				//probably should comment these out when the object is debugged.
				x->power = temp2;
    			post("template~: power = %d", x->power);
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
    			//post("template~: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
}