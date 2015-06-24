/******************************************/
/*  WaveGuide Flute ala Karjalainen,      */
/*  Smith, Waryznyk, etc.                 */
/*  with polynomial Jet ala Cook          */
/*  by Perry Cook, 1995-96                */
/*										  */
/*  ported to MSP by Dan Trueman, 2000	  */
/*                                        */
/*  This is a waveguide model, and thus   */
/*  relates to various Stanford Univ.     */
/*  and possibly Yamaha and other patents.*/
/*                                        */
/*   Controls:    CONTROL1 = jetDelay     */
/*                CONTROL2 = noiseGain    */
/*                CONTROL3 = vibFreq      */
/*                MOD_WHEEL= vibAmt       */
/******************************************/
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include <math.h>
#include "stk_c.h"

#define LENGTH 882 	//44100/LOWFREQ + 1 --flute length
#define JETLENGTH (LENGTH >> 1)
#define VIBLENGTH 1024

t_class *flute_class;

typedef struct _flute
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars
    float x_bp;			//breath pressure	
    float x_jd;			//jet delay
    float x_ng; 		//noise gain
    float x_vf; 		//vib freq
    float x_va; 		//vib amount
    float x_fr;			//frequency	
    
    float jd_save;
    float fr_save;
    
    //signals connected? or controls...
    short x_bpconnected;
    short x_jdconnected;
    short x_ngconnected;
    short x_vfconnected;
    short x_vaconnected;
    short x_frconnected;
    
    //delay lines
    DLineL boreDelay;
    DLineL jetDelay;
    
    //one pole filter
    OnePole filter;
    
    //DC blocker
    DCBlock killdc;
    
    //vibrato table
    float vibTable[VIBLENGTH];
    float vibRate;
    float vibTime;
    
    //stuff
    float endRefl;
    float jetRefl;
    float jetRatio;
    float lastFreq;
    float srate, one_over_srate;
} t_flute;

/****PROTOTYPES****/

//setup funcs
void *flute_new(double val);
void flute_free(t_flute *x);
void flute_assist(t_flute *x, void *b, long m, long a, char *s);

void flute_float(t_flute *x, double f);
void flute_dsp64(t_flute *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void flute_perform64(t_flute *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

//vib funcs
void setVibFreq(t_flute *x, float freq);
float vib_tick(t_flute *x);

//flute functions
void setFreq(t_flute *x, float freq);
void setJetDelay(t_flute *x, float ratio);


/****FUNCTIONS****/

#define WATCHIT 0.00001
void setFreq(t_flute *x, float freq)
{
	float temp;
	x->lastFreq = freq * 0.66666;
	if(x->lastFreq < WATCHIT) x->lastFreq = WATCHIT;
	temp = (x->srate / x->lastFreq) - 2.;
	DLineL_setDelay(&x->boreDelay, temp);
	DLineL_setDelay(&x->jetDelay, temp * x->jetRatio);
}

void setJetDelay(t_flute *x, float ratio)
{
	float temp;
	temp = (x->srate / x->lastFreq) - 2.;
	x->jetRatio = ratio;
	DLineL_setDelay(&x->jetDelay, (temp * ratio));
}	

//vib funcs
void setVibFreq(t_flute *x, float freq)
{
	x->vibRate = VIBLENGTH * x->one_over_srate * freq;
}

float vib_tick(t_flute *x)
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
    t_class *c = class_new("flute~", (method)flute_new, (method)flute_free, (long)sizeof(t_flute), 0L, A_DEFFLOAT, 0);
    
    class_addmethod(c, (method)flute_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)flute_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)flute_float, "float", A_FLOAT, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    flute_class = c;

}

void flute_assist(t_flute *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
            case 0:
                sprintf(s,"(signal/float) breath pressure");
                break;
            case 1:
                sprintf(s,"(signal/float) jet delay");
                break;
            case 2:
                sprintf(s,"(signal/float) noise gain");
                break;
            case 3:
                sprintf(s,"(signal/float) vibrato frequency");
                break;
            case 4:
                sprintf(s,"(signal/float) vibrato amount");
                break;
            case 5:
                sprintf(s,"(signal/float) frequency");
                break;
        }
	} else {
		sprintf(s,"(signal) output");
    }
}

void flute_float(t_flute *x, double f)
{
	if (x->x_obj.z_in == 0) {
		x->x_bp = f;
	} else if (x->x_obj.z_in == 1) {
		x->x_jd = f;
	} else if (x->x_obj.z_in == 2) {
		x->x_ng = f;
	} else if (x->x_obj.z_in == 3) {
		x->x_vf = f;
	} else if (x->x_obj.z_in == 4) {
		x->x_va = f;
	} else if (x->x_obj.z_in == 5) {
		x->x_fr = f;
	}
}

void *flute_new(double initial_coeff)
{
	int i;

    t_flute *x = (t_flute *)object_alloc(flute_class);
     //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject)-1;i<sizeof(t_flute);i++)  
                ((char *)x)[i]=0; 
	} 
    dsp_setup((t_pxobject *)x,6);
    outlet_new((t_object *)x, "signal");
    x->x_bp = 0.5;
    x->x_ng = 0.15;
    x->x_vf = 0.5;
    x->x_va = 0.05;
    x->x_fr = 440.;
    x->lastFreq = 440.;
    
    DLineL_alloc(&x->boreDelay, LENGTH);
    DLineL_alloc(&x->jetDelay, JETLENGTH);
    
    x->srate = sys_getsr();
    x->one_over_srate = 1./x->srate;
    
    for(i=0; i<VIBLENGTH; i++) x->vibTable[i] = sin(i*TWO_PI/VIBLENGTH);
    x->vibRate = 1.;
    x->vibTime = 0.;
    
    //clear stuff
    DLineL_clear(&x->boreDelay);
    DLineL_clear(&x->jetDelay);
    OnePole_init(&x->filter);
    
    //initialize things
    x->endRefl = 0.5;
    x->jetRefl = 0.5;
    x->jetRatio = 0.32;
    DLineL_setDelay(&x->boreDelay, 100.);
    DLineL_setDelay(&x->jetDelay, 49.);
    
    OnePole_setPole(&x->filter, 0.7 - (0.1 * 22050. / x->srate));
    OnePole_setGain(&x->filter, -1.);

    setFreq(x, x->x_fr);
    setVibFreq(x, 5.925);
    setJetDelay(x, x->jetRatio);
    
    x->jd_save = x->jetRatio;
    x->fr_save = x->x_fr;
    
    post("you can play the flute too");
    
    return (x);
}

void flute_free(t_flute *x)
{
	dsp_free((t_pxobject *)x);
	DLineL_free(&x->boreDelay);
	DLineL_free(&x->jetDelay);
}

void flute_dsp64(t_flute *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->x_bpconnected = count[0];
	x->x_jdconnected = count[1];
	x->x_ngconnected = count[2];
	x->x_vfconnected = count[3];
	x->x_vaconnected = count[4];
	x->x_frconnected = count[5];
	x->srate = samplerate;
    x->one_over_srate = 1./x->srate;
    OnePole_setPole(&x->filter, 0.7 - (0.1 * 22050. / x->srate));

    object_method(dsp64, gensym("dsp_add64"), x, flute_perform64, 0, NULL);
}

void flute_perform64(t_flute *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	double bp = x->x_bpconnected? *(double *)(ins[0]) : x->x_bp;
	double jd = x->x_jdconnected? *(double *)(ins[1]) : x->x_jd;
	double ng = x->x_ngconnected? *(double *)(ins[2]) : x->x_ng;
	double vf = x->x_vfconnected? *(double *)(ins[3]) : x->x_vf;
	double va = x->x_vaconnected? *(double *)(ins[4]) : x->x_va;
	double fr = x->x_frconnected? *(double *)(ins[5]) : x->x_fr;
	
	double *out = (double *)(outs[0]);
	long n = sampleframes;
	
	double jr = x->jetRefl;
	double er = x->endRefl;
	double temp, pressureDiff, randPressure;
    
	if(fr != x->fr_save) {
		setFreq(x, fr);
		x->fr_save = fr;
	}
    
	x->vibRate = VIBLENGTH * x->one_over_srate * vf;
	
	if(jd != x->jd_save) {
		setJetDelay(x, jd);
		x->jd_save = jd;
	}
    
	while(n--) {
		
		randPressure  = ng * Noise_tick();
		randPressure += va * vib_tick(x);
		randPressure *= bp;
		
		temp = OnePole_tick(&x->filter, x->boreDelay.lastOutput);
		temp = DCBlock_tick(&x->killdc, temp);
		pressureDiff = bp + randPressure - (jr * temp);
		pressureDiff = DLineL_tick(&x->jetDelay, pressureDiff);
		pressureDiff =  JetTabl_lookup(pressureDiff) + (er * temp);
		
		*out++ = DLineL_tick(&x->boreDelay, pressureDiff);
	}
}
