/******************************************/  
/*  Karplus-Strong plucked string model   */
/*  by Perry Cook, 1995-96                */
/*										  */
/*  ported to MSP by Dan Trueman, 2000	  */
/*                                        */
/*					  					  */
/*  There exist at least two patents,     */
/*  assigned to Stanford, bearing the     */
/*  names of Karplus and/or Strong.       */
/******************************************/
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include "stk_c.h"
#include <math.h> 
#define LENGTH 1024 	//44100/LOWFREQ + 1 --plucked length

t_class *plucked_class;

typedef struct _plucked
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars
    float x_pluckAmp;	//bow pressure	
    float x_fr;			//frequency	

    float fr_save;
    
    //signals connected? or controls...
    short x_pluckAmpconnected;
    short x_frconnected;
   
    //delay lines
    DLineA delayLine;
    
    //filters
    OneZero loopFilt;
    OnePole pickFilt;
    
    //stuff
    long length;
    float loopGain;
    short pluck;

    t_double srate, one_over_srate;
} t_plucked;

/****PROTOTYPES****/

//setup funcs
void *plucked_new(double val);
void plucked_free(t_plucked *x);
void plucked_assist(t_plucked *x, void *b, long m, long a, char *s);

// dsp stuff
void plucked_dsp64(t_plucked *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void plucked_perform64(t_plucked *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void plucked_float(t_plucked *x, double f);
void plucked_bang(t_plucked *x);

//plucked functions
void setFreq(t_plucked *x, float frequency);
void pluck(t_plucked *x, float amplitude);


/****FUNCTIONS****/

void plucked_bang(t_plucked *x)
{
	x->pluck = 1;
}

void setFreq(t_plucked *x, float frequency)
{
	float delay;
	if(frequency < 20.) frequency = 20.;
  	delay = (x->srate / frequency) -  0.5;   /* length - delays */
  	DLineA_setDelay(&x->delayLine, delay);
  	x->loopGain = 0.995 + (frequency * 0.000005);
  	if (x->loopGain>1.0) x->loopGain = 0.99999;
}

void pluck(t_plucked *x, float amplitude)
{
  long i;
  OnePole_setPole(&x->pickFilt, 0.999 - (amplitude * 0.15));
  OnePole_setGain(&x->pickFilt, amplitude *  0.5);
  for (i=0;i<x->length;i++)   
  	DLineA_tick(&x->delayLine, x->delayLine.lastOutput 
  					+ OnePole_tick(&x->pickFilt, Noise_tick()));                       
 /* fill delay with noise    */
 /* additively with current  */
 /* contents                 */
}

//primary MSP funcs
void ext_main(void* p)
{
    t_class *c = class_new("plucked~", (method)plucked_new, (method)plucked_free, (long)sizeof(t_plucked), 0L, A_DEFFLOAT, 0);
    
    class_addmethod(c, (method)plucked_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)plucked_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)plucked_float, "float", A_FLOAT, 0);
    class_addmethod(c, (method)plucked_bang, "bang", A_CANT, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    plucked_class = c;
}

void plucked_assist(t_plucked *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
            case 0:
                sprintf(s,"(signal/float) pluck amplitude");
                break;
            case 1:
                sprintf(s,"(signal/float) frequency");
                break;
        }
	} else {
		sprintf(s,"(signal) output");
    }
}

void plucked_float(t_plucked *x, double f)
{
	if (x->x_obj.z_in == 0) {
		x->x_pluckAmp = f;
	} else if (x->x_obj.z_in == 1) {
		x->x_fr = f;
	} 
}

void *plucked_new(double initial_coeff)
{
	int i;

    t_plucked *x = (t_plucked *)object_alloc(plucked_class);
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_plucked);i++)  
                ((char *)x)[i]=0; 
	} 
    dsp_setup((t_pxobject *)x,2);
    outlet_new((t_object *)x, "signal");
    
    x->length = LENGTH;
    
    x->srate = sys_getsr();
    x->one_over_srate = 1./x->srate;
    
    DLineA_alloc(&x->delayLine, LENGTH);
    
    //clear stuff
    DLineA_clear(&x->delayLine);
    OnePole_init(&x->pickFilt);
    OneZero_init(&x->loopFilt);
    
    //initialize things
    //length = (long) (SRATE / lowestFreq + 1);
  	x->loopGain =  0.999;
    DLineA_setDelay(&x->delayLine, 100.);
	
    setFreq(x, x->x_fr);
   
    x->fr_save = x->x_fr;
    
    post("oh karplus strong, the...");
    
    return (x);
}

void plucked_free(t_plucked *x)
{
	dsp_free((t_pxobject *)x);
	DLineA_free(&x->delayLine);
}

void plucked_dsp64(t_plucked *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->x_pluckAmpconnected = count[0];
	x->x_frconnected = count[1];
    
	x->srate = samplerate;
    x->one_over_srate = 1./x->srate;
    
    object_method(dsp64, gensym("dsp_add64"), x, plucked_perform64, 0, NULL);
}

void plucked_perform64(t_plucked *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double pluckAmp = x->x_pluckAmpconnected? *(t_double *)(ins[0]) : x->x_pluckAmp;
	t_double fr = x->x_frconnected? *(t_double *)(ins[1]) : x->x_fr;
	t_double *out = (t_double *)(outs[0]);
	long n = sampleframes;
    
	t_double temp;
    
	if(fr != x->fr_save) {
		setFreq(x, fr);
		x->fr_save = fr;
	}
	
	if(x->pluck) {
		pluck(x, pluckAmp);
		x->pluck = 0;
	}
    
	while(n--) {
		/* check this out */
  		/* here's the whole inner loop of the instrument!!  */
  		temp = 	DLineA_tick(&x->delayLine,
                            OneZero_tick(&x->loopFilt,
                                         x->delayLine.lastOutput * x->loopGain));
		*out++ = temp * 3.;
	}

}

