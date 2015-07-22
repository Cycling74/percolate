//flapper~ 
//a triggered input flapper. 
//takes a trigger signal in left input (0 or 1; 1 triggers new flap)
//when triggered, starts playing back input buffer immediately, marking current point in buffer (mark point)
//when playback reeaches record point (immediately, if playback speed > 1), playback turns around
//and goes backwards until it hits mark point, at which point it turns around and goes forward again
//playback flaps back and forth between mark point and record point until specified duration passes
//envelope using ADSR
//playback speed can be variable

//dt 2004; yet another PeRColate hack
//
// update for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

//#define ONE_OVER_HALFRAND 0.00006103516 	// constant = 1. / 16384.0
//#define ONE_OVER_MAXRAND 0.000030517578 	// 1 / 32768
#define ONE_OVER_HALFRAND 2./RAND_MAX
#define ONE_OVER_MAXRAND 1./RAND_MAX

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "stk_c.h"
#include "ext.h"
#include "ext_obex.h"
#include "ext_strings.h"
#include "z_dsp.h"

#ifdef WIN_VERSION
#include <limits.h>
#include <float.h>
#endif

#define MAX_INPUTS 10 	//arbitrary
#define MAX_OUTPUTS 10	//also arbitrary

#define MAX_FLAPS 6

#define INT_LINEAR 0
#define INT_POLY 1

t_class *flapper_class;

typedef struct _flapper
{
	//header
    t_pxobject x_obj;
    
    //variables specific to this object
    float srate, one_over_srate, srate_ms;  	//sample rate vars
    long num_inputs, num_outputs; 	//number of inputs and outputs
    double in[MAX_INPUTS];			//values of input variables
    float in_connected[MAX_INPUTS]; //booleans: true if signals connected to the input in question
    //we use this "connected" boolean so that users can connect *either* signals or floats
    //to the various inputs; sometimes it's easier just to have floats, but other times
    //it's essential to have signals.... but we have to know. 
	
    double buflen; 					//length of record buffer
    double *recordBuf;				//pointer to record buffer
    
    long flap_start[MAX_FLAPS];				//start sample for flap
    double flap_current[MAX_FLAPS];			//flap playback position
    long flap_playcounter[MAX_FLAPS];		//how long (samples) has the flap been playing
    long record_point;						//record point for delay line
    short wait;								//wait before allowing another trigger; needed if trigger hasn't gone to zero yet	
   											//	or if a re-attack minimum time is necessary
   	short flap_on[MAX_FLAPS];					//boolean; yes, we've got a flap
   	double flap_speed[MAX_FLAPS];				//flap playback speed;
   	long flap_length[MAX_FLAPS];				//length of flap in samples
   	long flap_default_length;
   	
   	float flap_panL[MAX_FLAPS];
   	float flap_panR[MAX_FLAPS];
   	float pan_spread;
   	
   	ADSR flap_adsr[MAX_FLAPS];					//adsr envelope for flap
   	long flapAttack[MAX_FLAPS], flapDecay[MAX_FLAPS], flapRelease[MAX_FLAPS];	//a d r times (ms)
	float flapSustain[MAX_FLAPS];				//sustain level
	long flapAttackDefault, flapDecayDefault, flapReleaseDefault;
	float flapSustainDefault;
	
	int flap_queue[MAX_FLAPS + 1];	//queue for keeping track of oldest flap; voice management
	int fq_head, fq_tail;
	short trigger_off;				//boolean: if this is set, then whenever we get a new trigger, 
									//		   the oldest flap will be turned off
	
	long which_flap;				//counter for flaps
	
	short interp_method;			//interpolation type (linear, polynomial)
	short polylen;					//interpolation size
	
	double overlap_len[MAX_FLAPS];				//overlap crossfade time when switching directions
	double overlap_len_default;
	long fade_counter[MAX_FLAPS];
	short fading[MAX_FLAPS];
	double fade_backposition[MAX_FLAPS];
} t_flapper;


/****PROTOTYPES****/

//setup funcs; this probably won't change, unless you decide to change the number of
//args that the user can input, in which case flapper_new will have to change
void *flapper_new(long num_inputs, long num_outputs);
void flapper_free(t_flapper *x);
void flapper_assist(t_flapper *x, void *b, long m, long a, char *s);

// dsp stuff
void flapper_dsp64(t_flapper *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void flapper_perform64(t_flapper *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

//for getting floats at inputs
void flapper_float(t_flapper *x, double f);

//for custom messages
void flapper_overlap(t_flapper *x, t_symbol *s, long argc, t_atom *argv);
void flapper_length(t_flapper *x, t_symbol *s, long argc, t_atom *argv);

void flapper_alloc(t_flapper *x);
void record_sample(t_flapper *x, double sample);
void new_flap(t_flapper *x);
float get_flap(t_flapper *x,long whichone);
void queue_put(t_flapper *x, int v);
int queue_get(t_flapper *x);

void flapper_attack(t_flapper *x, t_symbol *s, long argc, t_atom *argv);
void flapper_decay(t_flapper *x, t_symbol *s, long argc, t_atom *argv);
void flapper_sustain(t_flapper *x, t_symbol *s, long argc, t_atom *argv);
void flapper_release(t_flapper *x, t_symbol *s, long argc, t_atom *argv);

void flapper_setlinear(t_flapper *x, t_symbol *s, long argc, t_atom *argv);
void flapper_setpoly(t_flapper *x, t_symbol *s, long argc, t_atom *argv);
void flapper_setpoly2(t_flapper *x, t_symbol *s, long argc, t_atom *argv);

double interpolator(t_flapper *x, double where);
void flapper_overlap_len(t_flapper *x, t_symbol *s, long argc, t_atom *argv);


void ext_main(void* p)
{
    t_class *c = class_new("flapper~", (method)flapper_new, (method)flapper_free, (long)sizeof(t_flapper), 0L, A_DEFLONG, A_DEFLONG, 0);
    
    class_addmethod(c, (method)flapper_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)flapper_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)flapper_float, "float", A_FLOAT, 0);

    //our own messages
    class_addmethod(c, (method)flapper_overlap, "trigger_off", A_GIMME, 0);
    class_addmethod(c, (method)flapper_length, "length", A_GIMME, 0);
    class_addmethod(c, (method)flapper_attack, "attack", A_GIMME, 0);
    class_addmethod(c, (method)flapper_decay, "decay", A_GIMME, 0);
    class_addmethod(c, (method)flapper_sustain, "sustain", A_GIMME, 0);
    class_addmethod(c, (method)flapper_release, "release", A_GIMME, 0);
    
    class_addmethod(c, (method)flapper_setlinear, "linear", A_GIMME, 0);
    class_addmethod(c, (method)flapper_setpoly, "poly", A_GIMME, 0);
    class_addmethod(c, (method)flapper_setpoly, "poly2", A_GIMME, 0);
    
    class_addmethod(c, (method)flapper_overlap_len, "overlap", A_GIMME, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    flapper_class = c;
}


//this gets called when the object is created; everytime the user types in new args, this will get called
void *flapper_new(long num_inputs, long num_outputs)
{
	int i;
    t_flapper *x = (t_flapper*)object_alloc(flapper_class);
    
    if (x) {
        x->num_inputs = 3;
        x->num_outputs = 2;

        //inputs
        dsp_setup((t_pxobject *)x, x->num_inputs);
		
        //outputs
        for (i=0; i<x->num_outputs; i++)
            outlet_new((t_object *)x, "signal");
		
        //occasionally this line is necessary if you are doing weird asynchronous things with the in/out vectors
        //x->x_obj.z_misc = Z_NO_INPLACE;
        
        x->buflen = 5000. * 44.1; //allocate 5 seconds worth for now
        flapper_alloc(x);
        x->flap_default_length = 44100;
        
        for (i=0; i<MAX_FLAPS; i++) {
            x->flap_speed[i] = 10.;
            x->flap_length[i] = 44100; //set to one second by default for now
            ADSR_init(&x->flap_adsr[i]);
            x->flapAttack[i] = 20; x->flapDecay[i] = (44100 - 40); x->flapRelease[i] = 20;
            x->flapSustain[i] = 1.;
            x->fading[i] = 0;
            x->overlap_len[i] = 20. * x->srate_ms; //make 20ms by default
            ADSR_setAllTimes(&x->flap_adsr[i], x->flapAttack[i], x->flapDecay[i], x->flapSustain[i], x->flapRelease[i], x->srate_ms);
        }
        
        //default ADSR values
        x->flapAttackDefault = 20;
        x->flapDecayDefault = 44100 - 40;
        x->flapSustainDefault = 1.;
        x->flapReleaseDefault = 20;
        
        x->which_flap = 0;
        x->fq_head = x->fq_tail = 0;
        x->trigger_off = 1; //on by default
        
        x->pan_spread = 1.;
        
        x->interp_method = INT_LINEAR; //linear by default
        
        x->overlap_len_default = 20. * x->srate_ms;
    }
	
    return x;
}


//this gets called when an object is destroyed. do stuff here if you need to clean up.
void flapper_free(t_flapper *x)
{
	dsp_free((t_pxobject *)x);
	if (x->recordBuf)
		sysmem_freeptr(x->recordBuf);
}


//tells the user about the inputs/outputs when mousing over them
void flapper_assist(t_flapper *x, void *b, long m, long a, char *s)
{
	//could use switch/case inside for loops, to give more informative assist info....
	if (m==1) {
		if (a==0)  sprintf(s, "trigger (signal/float, 0/1)");
		if (a==1)  sprintf(s, "input (signal)");
		if (a==2)  sprintf(s, "playback speed (signal/float)");
	}
	if (m==2) {
		if (a==0)  sprintf(s, "out left (signal)");
		if (a==1)  sprintf(s, "out right (signal)");
	}
}

//this gets called when ever a float is received at *any* input
void flapper_float(t_flapper *x, double f)
{
	int i;
	
	//check to see which input the float came in, then set the appropriate variable value
	for(i=0;i<x->num_inputs;i++) {
		if (x->x_obj.z_in == i) {
			x->in[i] = f;
			// post("template~: setting in[%d] =  %f", i, f);
		}
	}
}

void flapper_alloc(t_flapper *x)
{
	//x->recordBuf = t_getbytes(BUFLENGTH * sizeof(float));
	//x->recordBuf = t_getbytes(x->buflen * sizeof(float));
	x->recordBuf = (double *)sysmem_newptr(x->buflen * sizeof(double));
	if (!x->recordBuf) {
		error("flapper~: out of memory");
		return;
	}
}

void flapper_dsp64(t_flapper *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	int i;
    
	//set sample rate vars
	x->srate = samplerate;
	x->one_over_srate = 1./x->srate;
	x->srate_ms = x->srate * 0.001;
	
	//check to see if there are signals connected to the various inputs
	for (i=0;i<x->num_inputs;i++)
		x->in_connected[i]	= count[i];
    
    object_method(dsp64, gensym("dsp_add64"), x, flapper_perform64, 0, NULL);
}

void flapper_perform64(t_flapper *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	long i;
	double trig, input, tempsample;
	double temp;
	double *in0 = ins[0];
	double *in1 = ins[1];
	double *in2 = ins[2];
	double *out0 = outs[0];
	double *out1 = outs[1];
	
	while (sampleframes--) {
		double outputL = 0.0;
		double outputR = 0.0;
		
		//grab signal inputs
		if (x->in_connected[0])
			trig = *in0++; //use the signal vector if there is one
		else
			trig = x->in[0];						//otherwise use the global variable
		
		if (x->in_connected[1])
			input = *in1++;
		else
			input = x->in[1];
		
		if (x->in_connected[2])
			temp = *in2++; //flap speed
		else
			temp = x->in[2];
		temp *= 2.0; //there's a bug somewhere, not sure where. shouldn't have to do this.....
		
		//record sample into buffer
		record_sample(x, input);
		
		//trigger new flap if we have a new trigger and aren't waiting
		if (trig > 0. && x->wait == 0) 	{
			x->wait = 1;
			new_flap(x);
		}
		
		//turn off waiting if trigger signal goes to 0
		if (x->wait == 1 && trig <= 0.0)
			x->wait = 0;
		
		//get flap sample
		for (i=0; i<MAX_FLAPS; i++) {
			if (x->flap_speed[i] < 0.0)
				x->flap_speed[i] = -temp;
			else
				x->flap_speed[i] = temp;
			
			tempsample = get_flap(x, i);
			outputL += tempsample * x->flap_panL[i];
			outputR += tempsample * x->flap_panR[i];
		}
		
		*out0++ = outputL;
		*out1++ = outputR;
	}
}


void record_sample(t_flapper *x, double sample) {
	if (x->record_point >= x->buflen)
		x->record_point = 0;
	x->recordBuf[x->record_point++] = sample; //add sample
}


void new_flap(t_flapper *x) {
	
	int i;
	
	//turn off oldest flap, if in trigger_off mode 
	if (x->trigger_off) {
		i = queue_get(x);
		ADSR_keyOff(&x->flap_adsr[i]);
	}
	
	for (i=0;i<MAX_FLAPS; i++) {
		if (!x->flap_on[i]) {
			x->flap_start[i] = x->record_point - x->overlap_len_default - 1.;
			x->flap_current[i] = (float)x->record_point - x->overlap_len_default - 1.; //add arbitrary offset?
			x->flap_playcounter[i] = 0;
			x->flap_on[i] = 1;
			x->flap_speed[i] = 1.;
			x->flap_length[i] = x->flap_default_length;
			x->flapAttack[i] = x->flapAttackDefault;
			x->flapDecay[i] = x->flapDecayDefault;
			x->flapSustain[i] = x->flapSustainDefault;
			x->flapRelease[i] = x->flapReleaseDefault;
			ADSR_setAllTimes(&x->flap_adsr[i], x->flapAttack[i], x->flapDecay[i], x->flapSustain[i], x->flapRelease[i], x->srate_ms);
			ADSR_keyOn(&x->flap_adsr[i]);
			x->flap_panL[i] 		= CLAMP((((float)rand() - ( RAND_MAX /2 )) * ONE_OVER_MAXRAND * x->pan_spread + 0.5), FLT_MIN, 1.0);
			x->flap_panR[i]			= 1.0 - x->flap_panL[i];
			//make equal power panning....
			x->flap_panL[i] 		= powf(x->flap_panL[i], 0.5);
			x->flap_panR[i] 		= powf(x->flap_panR[i], 0.5);
			
			queue_put(x, i); //add this to queue; newest flap
			break;	//break out once we've got a new flap
		}
	}
}

double interpolator(t_flapper *x, double where)
{
	double output;

	if (x->interp_method == INT_LINEAR) {
		long	first = (long)where;
		double	alpha = where - first;
		double	om_alpha = 1.0 - alpha;
		
		output = x->recordBuf[first++] * om_alpha;
		if (first < x->buflen)
			output += x->recordBuf[first] * alpha;
		else
			output += x->recordBuf[0] * alpha;
	}
	else // if (x->interp_method == INT_POLY)
		output = polyinterpolate_d(x->recordBuf, x->polylen, x->buflen, where);
	
	return output;

}

float get_flap(t_flapper *x, long whichone) {

	double output, where;
	double hc = 0.0, rp, td;
	double in_coeff, out_coeff, iw;
			
	if (ADSR_getState(&x->flap_adsr[whichone]) == DONE) {
		x->flap_on[whichone] = 0;
		return 0.;
	}
	
	if (x->flap_playcounter[whichone] >= x->flap_length[whichone])
		ADSR_keyOff(&x->flap_adsr[whichone]);
	
	//flap book-keeping...., overlapping at direction changes
	x->flap_playcounter[whichone]++;
	x->flap_current[whichone] += x->flap_speed[whichone];
	
	//check to see if we need to cross fade
	if (!x->fading[whichone]) {
		rp = (double)(x->flap_start[whichone] + x->flap_playcounter[whichone] + (long)x->overlap_len_default); //record point
		td = fabs((double)(x->flap_playcounter[whichone] + x->overlap_len_default) / x->flap_speed[whichone]);
		
		x->overlap_len[whichone] = x->overlap_len_default;
		if (td < x->overlap_len[whichone])
			x->overlap_len[whichone] = td - 1.0;
		
		if (x->flap_speed[whichone] > 0.0)
			hc = rp - x->flap_current[whichone];
		else if (x->flap_speed[whichone] < 0.0)
			hc = x->flap_current[whichone] - x->flap_start[whichone];
		
		if (hc < x->overlap_len[whichone] * x->flap_speed[whichone]) {
			x->fading[whichone] = 1;
			x->fade_counter[whichone] = 0;
			if (x->flap_speed[whichone] > 0.0)
				x->fade_backposition[whichone] = x->flap_current[whichone] + x->overlap_len[whichone] - x->flap_speed[whichone];
			else if (x->flap_speed[whichone] < 0.0)
				x->fade_backposition[whichone] = x->flap_current[whichone] - x->overlap_len[whichone] + x->flap_speed[whichone];
		}
	}
	
	if (x->fading[whichone]) {
		in_coeff = x->fade_counter[whichone]++ / x->overlap_len[whichone];
		out_coeff = 1.0 - in_coeff;
		in_coeff = powf(in_coeff, 0.5);
		out_coeff = powf(out_coeff, 0.5);
		iw = x->fade_backposition[whichone];
		x->fade_backposition[whichone] -= x->flap_speed[whichone];
	}
	
	if (x->fade_counter[whichone] >= x->overlap_len[whichone]) {
		x->flap_speed[whichone] = -x->flap_speed[whichone];
		x->flap_current[whichone] = x->fade_backposition[whichone];
		x->fading[whichone] = 0;
		x->fade_counter[whichone] = 0;
	}
	
	where = x->flap_current[whichone];
	while (where < 0.0)
		where += x->buflen;
	while (where >= x->buflen)
		where -= x->buflen;
	
	output = interpolator(x, where);
	if (x->fading[whichone]) {
		while (iw < 0.0)
			iw += x->buflen;
		while (iw >= x->buflen)
			iw -= x->buflen;
		output = output * out_coeff + interpolator(x, iw) * in_coeff;
	}
	
	return (float)output * ADSR_tick(&x->flap_adsr[whichone]);
	
}

//add to the flap queue
void queue_put(t_flapper *x, int v)
{
	x->flap_queue[x->fq_tail++] = v;
	if (x->fq_tail > MAX_FLAPS) x->fq_tail = 0;
}

int queue_get(t_flapper *x)
{
	int t = x->flap_queue[x->fq_head++];
	if (x->fq_head > MAX_FLAPS) x->fq_head = 0;
	return t;
}

//interpolation messages
void flapper_setlinear(t_flapper *x, t_symbol *s, long argc, t_atom *argv)
{
	x->interp_method = INT_LINEAR;
}

void flapper_setpoly(t_flapper *x, t_symbol *s, long argc, t_atom *argv)
{
	x->interp_method = INT_POLY;
	x->polylen = 3;
}

void flapper_setpoly2(t_flapper *x, t_symbol *s, long argc, t_atom *argv)
{
	x->interp_method = INT_POLY;
	x->polylen = 4;
}


//what to do when we get the message "mymessage" and a value (or list of values)
void flapper_overlap(t_flapper *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	long temp2; 
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp2 = argv[i].a_w.w_long;
				x->trigger_off = (int) temp2;
				//probably should comment these out when the object is debugged.
    			//post("flapper: received argument %d of mymessage with value %d", i+1, temp2);
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
				x->trigger_off = (int) temp;
    			//post("flapper: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
}

void flapper_length(t_flapper *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	long temp2; 
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp2 = argv[i].a_w.w_long;
				x->flap_default_length = (long) ((float)temp2 * x->srate_ms);
				//probably should comment these out when the object is debugged.
    			//post("flapper: received argument %d of mymessage with value %d", i+1, temp2);
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
				x->flap_default_length = (long) (temp * x->srate_ms);
    			//post("flapper: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
}

void flapper_attack(t_flapper *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	long temp2; 
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp2 = argv[i].a_w.w_long;
				x->flapAttackDefault = temp2;
				//probably should comment these out when the object is debugged.
    			//post("flapper: received argument %d of mymessage with value %d", i+1, temp2);
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
				x->flapAttackDefault = (long) temp;
    			//post("flapper: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
}

void flapper_decay(t_flapper *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	long temp2; 
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp2 = argv[i].a_w.w_long;
				x->flapDecayDefault  = temp2;
				//probably should comment these out when the object is debugged.
    			//post("flapper: received argument %d of mymessage with value %d", i+1, temp2);
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
				x->flapDecayDefault = (long) temp;
    			//post("flapper: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
}

void flapper_sustain(t_flapper *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	long temp2; 
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp2 = argv[i].a_w.w_long;
				x->flapSustainDefault = (float)temp2;
				//probably should comment these out when the object is debugged.
    			//post("flapper: received argument %d of mymessage with value %d", i+1, temp2);
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
				x->flapSustainDefault = temp;
    			//post("flapper: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
}

void flapper_release(t_flapper *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	long temp2; 
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp2 = argv[i].a_w.w_long;
				x->flapReleaseDefault = temp2;
				//probably should comment these out when the object is debugged.
    			//post("flapper: received argument %d of mymessage with value %d", i+1, temp2);
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
				x->flapReleaseDefault = (long) temp;
    			//post("flapper: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
}

void flapper_overlap_len(t_flapper *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	long temp2; 
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp2 = argv[i].a_w.w_long;
				x->overlap_len_default = (double)temp2 * x->srate_ms;
				if (x->overlap_len_default <= 1.) x->overlap_len_default = 1.;
				//probably should comment these out when the object is debugged.
    			//post("flapper: received argument %d of mymessage with value %d", i+1, temp2);
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
				x->overlap_len_default = temp * x->srate_ms;
				if (x->overlap_len_default <= 1.) x->overlap_len_default = 1.;
    			//post("flapper: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
}
