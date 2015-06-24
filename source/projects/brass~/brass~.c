/******************************************/
/*  Waveguide Brass Instrument Model ala  */
/*  Cook (TBone, HosePlayer)              */
/*  by Perry R. Cook, 1995-96             */
/*										  */
/*  ported to MSP by Dan Trueman, 2000	  */
/*                                        */
/*  This is a waveguide model, and thus   */
/*  relates to various Stanford Univ.     */
/*  and possibly Yamaha and other patents.*/
/*                                        */
/*   Controls:    CONTROL1 = lipTension   */
/*                CONTROL2 = slideLength  */
/*		  		  CONTROL3 = vibFreq      */
/*		  		  MOD_WHEEL= vibAmt       */
/******************************************/
//
// Updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include "stk_c.h"
#include <math.h> 
#define LENGTH 22050	//44100/LOWFREQ + 1 --brass length
#define VIBLENGTH 1024

t_class *brass_class;

typedef struct _brass
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars
    float lipTension;
    float slideTargetMult;
    float vibrGain;
    float maxPressure;
    float x_vf; 		//vib freq
    float x_fr;			//frequency	
    
    float lipTension_save;
    float slideTargetMult_save;
    float fr_save;
    
    //signals connected? or controls...
    short x_ltconnected;
    short x_stconnected;
    short x_vgconnected;
    short x_mpconnected;
    short x_vfconnected;
    short x_frconnected;
    
    //delay line
    DLineA delayLine;
    
    //lip filter
    LipFilt lipFilter;
    
    //DC blocker
    DCBlock killdc;
    
    //vibrato table
    float vibTable[VIBLENGTH];
    float vibRate;
    float vibTime;
    
    //stuff
    float lipTarget, slideTarget;
    float srate, one_over_srate;
} t_brass;

/****PROTOTYPES****/

//setup funcs
void *brass_new(double val);
void brass_free(t_brass *x);
void brass_assist(t_brass *x, void *b, long m, long a, char *s);

// dsp stuff
void brass_dsp64(t_brass *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void brass_perform64(t_brass *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void brass_float(t_brass *x, double f);

//vib funcs
void setVibFreq(t_brass *x, float freq);
float vib_tick(t_brass *x);

//brass functions
void setFreq(t_brass *x, float frequency);

/****FUNCTIONS****/

void setFreq(t_brass *x, float frequency)
{
  if(frequency < 20.) frequency = 20.;
  x->slideTarget = (x->srate / frequency * 2.0) + 3.0;
  /* fudge correction for filter delays */
  DLineA_setDelay(&x->delayLine, x->slideTarget);	/*  we'll play a harmonic  */
  x->lipTarget = frequency;
  LipFilt_setFreq(&x->lipFilter, frequency, x->srate);
}

//vib funcs
void setVibFreq(t_brass *x, float freq)
{
	x->vibRate = VIBLENGTH * x->one_over_srate * freq;
}

float vib_tick(t_brass *x)
{
	long temp;
	float temp_time, alpha, output;
	
	x->vibTime += x->vibRate;
	while (x->vibTime >= (float)VIBLENGTH) x->vibTime -= (float)VIBLENGTH;
	while (x->vibTime < 0.) x->vibTime += (float)VIBLENGTH;
	
	temp_time = x->vibTime;
	
	temp = (long) temp_time;
	alpha = temp_time - (float)temp;
	output = x->vibTable[temp];
	output = output + (alpha * (x->vibTable[temp+1] - output));
	return output;
}

//primary MSP funcs
void ext_main(void* p)
{
    t_class *c = class_new("brass~", (method)brass_new, (method)brass_free, (long)sizeof(t_brass), 0L, A_DEFFLOAT, 0);
    class_addmethod(c, (method)brass_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)brass_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)brass_float, "float", A_FLOAT, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    brass_class = c;
}

void brass_assist(t_brass *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
            case 0:
                sprintf(s,"(signal/float) lip tension");
                break;
            case 1:
                sprintf(s,"(signal/float) slide targeting");
                break;
            case 2:
                sprintf(s,"(signal/float) vibrato gain");
                break;
            case 3:
                sprintf(s,"(signal/float) maximum pressure");
                break;
            case 4:
                sprintf(s,"(signal/float) vibrato frequency");
                break;
            case 5:
                sprintf(s,"(signal/float) frequency");
                break;
        }
	} else {
		sprintf(s,"(signal) output");
    }
}

void brass_float(t_brass *x, double f)
{
	if (x->x_obj.z_in == 0) {
		x->lipTension = f;
	} else if (x->x_obj.z_in == 1) {
		x->slideTargetMult = f;
	} else if (x->x_obj.z_in == 2) {
		x->vibrGain = f;
	} else if (x->x_obj.z_in == 3) {
		x->maxPressure = f;
	} else if (x->x_obj.z_in == 4) {
		x->x_vf = f;
	} else if (x->x_obj.z_in == 5) {
		x->x_fr = f;
	}
}

void *brass_new(double initial_coeff)
{
	int i;

    t_brass *x = (t_brass *)object_alloc(brass_class);
    
    if (x) {
        //zero out the struct, to be careful (takk to jkclayton)
        for(i=sizeof(t_pxobject)-1;i<sizeof(t_brass);i++)  {
            ((char *)x)[i]=0;
        }

        dsp_setup((t_pxobject *)x,6);
        outlet_new((t_object *)x, "signal");
        x->lipTension 			= 0.5;
        x->lipTension_save 		= 0.5;
        x->slideTargetMult 		= 0.5;
        x->slideTargetMult_save = 0.5;
        x->vibrGain 			= 0.5;
        x->maxPressure 			= 0.05;
        x->lipTarget  = x->x_fr = 440.;
        x->x_vf = 5.;
        
        x->srate = sys_getsr();
        x->one_over_srate = 1./x->srate;
        
        DLineA_alloc(&x->delayLine, LENGTH);
        
        for(i=0; i<VIBLENGTH; i++) x->vibTable[i] = sin(i*TWO_PI/VIBLENGTH);
        x->vibRate = 1.;
        x->vibTime = 0.;
        
        //clear stuff
        DLineA_clear(&x->delayLine);
        LipFilt_init(&x->lipFilter);
        
        //initialize things
        DLineA_setDelay(&x->delayLine, 100.);

        setFreq(x, x->x_fr);
        setVibFreq(x, 5.925);

        x->fr_save = x->x_fr;
        
        post("what exactly is that sound?");
    }
    
    return (x);
}

void brass_free(t_brass *x)
{
	dsp_free((t_pxobject *)x);
	DLineA_free(&x->delayLine);
}

void brass_dsp64(t_brass *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->x_ltconnected = count[0];
	x->x_stconnected = count[1];
	x->x_vgconnected = count[2];
	x->x_mpconnected = count[3];
	x->x_vfconnected = count[4];
	x->x_frconnected = count[5];
	x->srate = samplerate;
    x->one_over_srate = 1./x->srate;
    
    object_method(dsp64, gensym("dsp_add64"), x, brass_perform64, 0, NULL);
}

void brass_perform64(t_brass *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	double lipTension 		= x->x_ltconnected? *(double *)(ins[0]) : x->lipTension;
	double slideTargetMult 	= x->x_stconnected? *(double *)(ins[1]) : x->slideTargetMult;
	double vibrGain 		= x->x_vgconnected? *(double *)(ins[2]) : x->vibrGain;
	double maxPressure		= x->x_mpconnected? *(double *)(ins[3]) : x->maxPressure;
	double vf 				= x->x_vfconnected? *(double *)(ins[4]) : x->x_vf;
	double fr 				= x->x_frconnected? *(double *)(ins[5]) : x->x_fr;
	
	double *out = (double *)(outs[0]);
	long n = sampleframes;
	
	double temp, breathPressure;
    
	if(fr != x->fr_save) {
		if(fr < 20.) fr = 20.;
  		x->slideTarget = (x->srate / fr * 2.0) + 3.0;
  		x->lipTarget = fr;
		LipFilt_setFreq(&x->lipFilter, x->lipTarget*lipTension, x->srate);
		DLineA_setDelay(&x->delayLine, x->slideTarget*slideTargetMult);
		x->fr_save = fr;
	}
	
    if(lipTension != x->lipTension_save) {
    	LipFilt_setFreq(&x->lipFilter, x->lipTarget*lipTension, x->srate);
    	x->lipTension_save = lipTension;
    }
    
    if(slideTargetMult != x->slideTargetMult_save) {
   		DLineA_setDelay(&x->delayLine, x->slideTarget*slideTargetMult);
   		x->slideTargetMult_save = slideTargetMult;
   	}
	
	x->vibRate = VIBLENGTH * x->one_over_srate * vf;
    
	while(n--) {
		breathPressure = maxPressure;
  		breathPressure += vibrGain * vib_tick(x);
  		/* mouth input and bore reflection */
  		temp = LipFilt_tick(&x->lipFilter, .3*breathPressure, .85*x->delayLine.lastOutput);
  		temp = DCBlock_tick(&x->killdc, temp);			/* block DC    */
  		*out++ = DLineA_tick(&x->delayLine, temp);		/* bore delay  */
	}
}

