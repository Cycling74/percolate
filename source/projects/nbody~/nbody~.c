//PeRColate hack. by dan trueman from perry cook's code. 
//applies 12 pole filters based on LPC anals of Nbody analysis
//see help patch and http://music.princeton.edu/~dan/nbody for more information
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include "ext.h"
#include "ext_obex.h"

#include "z_dsp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SQRT_TWO 1.414213562
#define BUFSIZE 8192 //4*2048

#include "Dunlap12.lpc.h"
#include "Fiddle12.lpc.h"
#include "Mando12.lpc.h"
#include "Violin12.lpc.h"
#include "Arch12.lpc.h"
#include "Abreu12.lpc.h" 
#define ORDER 12 
 
#define GUITAR1 1
#define GUITAR2 2
#define VIOLIN 3
#define MANDOLIN 4
#define HARDANGER 5
#define ARCHTOP 6

t_class *nbody_class;

typedef struct _nbody
{
	//header
    t_pxobject x_obj;
    
    short instrument;
    short direction;
    
    //allpole vars
    float poleCoeffs[ORDER];
    float ap_outputs[ORDER];
    float ap_gain;
    
    //onezero vars
    float zeroCoeff;
    float sgain;
    float oz_gain;
    float oz_input;
    
    //user controlled vars	    
    
    //signals connected? or controls...
    short num_objectsConnected;
    short res_freqConnected;
    short shake_dampConnected;
    short shake_maxConnected;
   
    double srate, one_over_srate;
} t_nbody;

/****PROTOTYPES****/

//setup funcs
void *nbody_new(double val);
void nbody_assist(t_nbody *x, void *b, long m, long a, char *s);

void nbody_float(t_nbody *x, double f);
void nbody_int(t_nbody *x, int f);
void nbody_bang(t_nbody *x);

// dsp stuff
void nbody_dsp64(t_nbody *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void nbody_perform64(t_nbody *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void nbody_guitar1(t_nbody *x, double f);
void nbody_guitar2(t_nbody *x, double f);
void nbody_mandolin(t_nbody *x, double f);
void nbody_violin(t_nbody *x, double f);
void nbody_hardanger(t_nbody *x, double f);
void nbody_archtop(t_nbody *x, double f);

void nbody_setup(t_nbody *x);
float nbody_tick(t_nbody *x);

//allpole funcs
void setPoleCoeffs(t_nbody *x, float *coeffs);
float ap_tick(t_nbody *x, float sample);

//onezero funcs
void setOneZeroCoeff(t_nbody *x, float aValue);
float oz_tick(t_nbody *x, float sample);


/****FUNCTIONS****/
void setOneZeroCoeff(t_nbody *x, float aValue)
{
	x->zeroCoeff = aValue;
    if (x->zeroCoeff > 0.0)                  /*  Normalize gain to 1.0 max  */
        x->sgain = x->oz_gain / ((float) 1.0 + x->zeroCoeff);
    else
        x->sgain = x->oz_gain / ((float) 1.0 - x->zeroCoeff);

}

float oz_tick(t_nbody *x, float sample)
{
	float temp, outsamp;
    temp = x->sgain * sample;
    outsamp = (x->oz_input * x->zeroCoeff) + temp;
    x->oz_input = temp;
    return outsamp;

}

void setPoleCoeffs(t_nbody *x, float *coeffs)
{
	int i;
	for(i=0; i<ORDER; i++) {
		x->poleCoeffs[i] = coeffs[i];
	}
}

float ap_tick(t_nbody *x, float sample)
{
	int i;
    float temp;                          

    temp = sample * x->ap_gain;             

    for (i=ORDER-1;i>0;i--)	{
		temp -= x->ap_outputs[i] * x->poleCoeffs[i]; 
		x->ap_outputs[i] = x->ap_outputs[i-1];
    }
    temp -= x->ap_outputs[0] * x->poleCoeffs[0]; 
    x->ap_outputs[0] = temp;

    return temp;
}

void nbody_setup(t_nbody *x) {
}

float nbody_tick(t_nbody *x) {
    return 0.0;
}

//primary MSP funcs
void ext_main(void* p)
{
    t_class *c = class_new("nbody~", (method)nbody_new, (method)dsp_free, (long)sizeof(t_nbody), 0L, A_DEFFLOAT, 0);
    
    class_addmethod(c, (method)nbody_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)nbody_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)nbody_float, "float", A_FLOAT, 0);
    class_addmethod(c, (method)nbody_int, "int", A_LONG, 0);
    class_addmethod(c, (method)nbody_bang, "bang", A_CANT, 0);

    class_addmethod(c, (method)nbody_guitar1, "guitar1", A_GIMME, 0);
    class_addmethod(c, (method)nbody_guitar2, "guitar2", A_GIMME, 0);
    class_addmethod(c, (method)nbody_mandolin, "mandolin", A_GIMME, 0);
    class_addmethod(c, (method)nbody_violin, "violin", A_GIMME, 0);
    class_addmethod(c, (method)nbody_hardanger, "hardanger", A_GIMME, 0);
    class_addmethod(c, (method)nbody_archtop, "archtop", A_GIMME, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    nbody_class = c;
}

void nbody_assist(t_nbody *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
            case 0:
                sprintf(s,"(signal/float) number of items");
                break;
            case 1:
                sprintf(s,"(signal/float) frequency");
                break;
            case 2:
                sprintf(s,"(signal/float) damping");
                break;
        }
	} else {
		sprintf(s,"(signal) output");
    }
}

void nbody_guitar1(t_nbody *x, double f)
{
	x->instrument = GUITAR1;
	x->ap_gain = (0.07*abreuGains[abreuMap[x->direction]]);
	setPoleCoeffs(x, abreu_coeffs[abreuMap[x->direction]]);
	setOneZeroCoeff(x, abreuZero);
}

void nbody_guitar2(t_nbody *x, double f)
{
	x->instrument = GUITAR2;
	x->ap_gain = (0.07*dunlapGains[dunlapMap[x->direction]]);
	setPoleCoeffs(x, dunlap_coeffs[dunlapMap[x->direction]]);
	setOneZeroCoeff(x, dunlapZero);
}

void nbody_mandolin(t_nbody *x, double f)
{
	x->instrument = MANDOLIN;
	x->ap_gain = (0.1*mandoGains[mandoMap[x->direction]]);
	setPoleCoeffs(x, mando_coeffs[mandoMap[x->direction]]);
	setOneZeroCoeff(x, mandoZero);
}

void nbody_violin(t_nbody *x, double f)
{
	x->instrument = VIOLIN;
	x->ap_gain = (0.2*violinGains[violinMap[x->direction]]);
	setPoleCoeffs(x, violin_coeffs[violinMap[x->direction]]);
	setOneZeroCoeff(x, violinZero);
}

void nbody_hardanger(t_nbody *x, double f)
{
	x->instrument = HARDANGER;
	x->ap_gain = (fiddleGain*fiddleGains[fiddleMap[x->direction]]);
	setPoleCoeffs(x, fiddle_coeffs[fiddleMap[x->direction]]);
	setOneZeroCoeff(x, fiddleZero);
}

void nbody_archtop(t_nbody *x, double f)
{
	x->instrument = ARCHTOP;
	x->ap_gain = (0.07*archGains[archMap[x->direction]]);
	setPoleCoeffs(x, arch_coeffs[archMap[x->direction]]);
	setOneZeroCoeff(x, archZero);
}

void nbody_float(t_nbody *x, double f)
{
    nbody_int(x, (int)f);
}

void nbody_int(t_nbody *x, int f)
{
	if(f > 12) f = 12;
	if(f < 1) f = 1;
	
	post("nbody: changing input to %d", f);
	
	f--;
	x->direction = f;
	
	if (x->instrument == GUITAR1) nbody_guitar1(x, 0.);
	if (x->instrument == GUITAR2) nbody_guitar2(x, 0.);
	if (x->instrument == VIOLIN) nbody_violin(x, 0.);
	if (x->instrument == HARDANGER) nbody_hardanger(x, 0.);
	if (x->instrument == MANDOLIN) nbody_mandolin(x, 0.);
	if (x->instrument == ARCHTOP) nbody_archtop(x, 0.);
}

void nbody_bang(t_nbody *x)
{
}

void *nbody_new(double initial_coeff)
{
	int i;

    t_nbody *x = (t_nbody *)object_alloc(nbody_class);
    dsp_setup((t_pxobject *)x,1);
    inlet_new((t_pxobject *)x, "int");
    outlet_new((t_object *)x, "signal");
    
    //allpole init
    for (i=0;i<ORDER;i++) x->ap_outputs[i] = (float) 0.0;
    x->ap_gain = 1.;
    
    //onezero init
    x->zeroCoeff = 1.;
    x->sgain = .5;
    x->oz_gain = 1.;
    x->oz_input = 0.;
 
 	x->instrument = GUITAR1;
 	x->direction = 1;
 	nbody_guitar1(x, 0.);

    x->srate = sys_getsr();
    x->one_over_srate = 1./x->srate;
    
    return (x);
}

void nbody_dsp64(t_nbody *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, nbody_perform64, 0, NULL);
}

void nbody_perform64(t_nbody *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double *in = (t_double *)(ins[0]);
	t_double *out = (t_double *)(outs[0]);
	long n = sampleframes;
	
	t_double temp;
	
	while(n--) {
		temp = oz_tick(x, *in++);
		temp = ap_tick(x, temp);
		*out++ = temp;
	}
}	

