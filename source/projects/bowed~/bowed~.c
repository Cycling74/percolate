/******************************************/
/*  Bowed String model ala Smith          */
/*  after McIntyre, Schumacher, Woodhouse */
/*  by Perry Cook, 1995-96                */
/*										  */
/*  ported to MSP by Dan Trueman, 2000	  */
/*                                        */
/*  This is a waveguide model, and thus   */
/*  relates to various Stanford Univ.     */
/*  and possibly Yamaha and other patents.*/
/*                                        */
/*   Controls:    CONTROL1 = bowPressure  */
/*                CONTROL2 = bowPosition  */
/*                CONTROL3 = vibrFreq     */
/*                MOD_WHEEL= vibrGain     */
/*                                        */
/******************************************/

#include "stk_c.h"
#include <math.h> 
#define LENGTH 882 	//44100/LOWFREQ + 1 --bowed length
#define BRIDGELENGTH (LENGTH >> 1)
#define VIBLENGTH 1024

void *bowed_class;

typedef struct _bowed
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars
    float x_bp;			//bow pressure	
    float x_bpos;		//bow position
    float x_bv; 		//bow velocity
    float x_vf; 		//vib freq
    float x_va; 		//vib amount
    float x_fr;			//frequency	

    float fr_save;
    
    //signals connected? or controls...
    short x_bpconnected;
    short x_bposconnected;
    short x_bvconnected;
    short x_vfconnected;
    short x_vaconnected;
    short x_frconnected;
    
    //delay lines
    DLineL neckDelay;
    DLineL bridgeDelay;
    
    //one pole filter
    OnePole reflFilt;
    
    //biquad
    BiQuad bodyFilt;
    
    BowTabl bowTabl;
    
    //vibrato table
    float vibTable[VIBLENGTH];
    float vibRate;
    float vibTime;
    
    //stuff
	float maxVelocity, baseDelay, betaRatio;
    float srate, one_over_srate;
} t_bowed;

/****PROTOTYPES****/

//setup funcs
void *bowed_new(double val);
void bowed_free(t_bowed *x);
void bowed_dsp(t_bowed *x, t_signal **sp, short *count);
void bowed_float(t_bowed *x, double f);
t_int *bowed_perform(t_int *w);
void bowed_assist(t_bowed *x, void *b, long m, long a, char *s);

//vib funcs
void setVibFreq(t_bowed *x, float freq);
float vib_tick(t_bowed *x);

//bowed functions
void setFreq(t_bowed *x, float freq);


/****FUNCTIONS****/

void setFreq(t_bowed *x, float freq)
{
	if(freq < 20.) freq = 20.;
	x->baseDelay = x->srate / freq - 4.0;   	/* delay - approx. filter delay */
	DLineL_setDelay(&x->bridgeDelay, x->baseDelay * x->betaRatio); /* bow to bridge length */
	DLineL_setDelay(&x->neckDelay, x->baseDelay * (1. - x->betaRatio));/* bow to nut (finger) length */
}

//vib funcs
void setVibFreq(t_bowed *x, float freq)
{
	x->vibRate = VIBLENGTH * x->one_over_srate * freq;
}

float vib_tick(t_bowed *x)
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
void main(void)
{
    setup((t_messlist **)&bowed_class, (method)bowed_new, (method)bowed_free, (short)sizeof(t_bowed), 0L, A_DEFFLOAT, 0);
    addmess((method)bowed_dsp, "dsp", A_CANT, 0);
    addmess((method)bowed_assist,"assist",A_CANT,0);
    addfloat((method)bowed_float);
    dsp_initclass();
    rescopy('STR#',9978);
}

void bowed_assist(t_bowed *x, void *b, long m, long a, char *s)
{
	assist_string(9978,m,a,1,7,s);
}

void bowed_float(t_bowed *x, double f)
{
	if (x->x_obj.z_in == 0) {
		x->x_bp = f;
	} else if (x->x_obj.z_in == 1) {
		x->x_bpos = f;
	} else if (x->x_obj.z_in == 2) {
		x->x_bv = f;
	} else if (x->x_obj.z_in == 3) {
		x->x_vf = f;
	} else if (x->x_obj.z_in == 4) {
		x->x_va = f;
	} else if (x->x_obj.z_in == 5) {
		x->x_fr = f;
	}
}

void *bowed_new(double initial_coeff)
{
	int i;

    t_bowed *x = (t_bowed *)newobject(bowed_class);
    
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_bowed);i++)  
                ((char *)x)[i]=0; 
	} 
	//x->x_obj.z_misc  = Z_NO_INPLACE;
	
    dsp_setup((t_pxobject *)x,6);
    outlet_new((t_object *)x, "signal");
    x->x_bp = 0.5;
    x->x_bpos = 0.15;
    x->x_bv = 0.5;
    x->x_vf = 0.5;
    x->x_va = 0.05;
    x->x_fr = 440.;
    
    x->srate = sys_getsr();
    x->one_over_srate = 1./x->srate;
    
    DLineL_alloc(&x->neckDelay, LENGTH);
    DLineL_alloc(&x->bridgeDelay, BRIDGELENGTH);
    
    for(i=0; i<VIBLENGTH; i++) x->vibTable[i] = sin(i*TWO_PI/VIBLENGTH);
    x->vibRate = 1.;
    x->vibTime = 0.;
    
    //clear stuff
    DLineL_clear(&x->neckDelay);
    DLineL_clear(&x->bridgeDelay);
    OnePole_init(&x->reflFilt);
    
    //initialize things
    x->bowTabl.slope = 3.0;
    DLineL_setDelay(&x->neckDelay, 100.);
    DLineL_setDelay(&x->bridgeDelay, 29.);
    
    OnePole_setPole(&x->reflFilt, 0.6 - (0.1 * 22050. / x->srate));
    OnePole_setGain(&x->reflFilt, .95);
	
	BiQuad_init(&x->bodyFilt);
	BiQuad_setFreqAndReson(&x->bodyFilt, 500., .85, x->srate);
	BiQuad_setEqualGainZeroes(&x->bodyFilt);
	BiQuad_setGain(&x->bodyFilt, 0.2);
	
    setFreq(x, x->x_fr);
    setVibFreq(x, 5.925);
    
    x->betaRatio = 0.127236;

    x->fr_save = x->x_fr;
    
    post("scritch, scritch, SCRITCH...");
    
    return (x);
}

void bowed_free(t_bowed *x)
{
	dsp_free((t_pxobject *)x);
	DLineL_free(&x->bridgeDelay);
	DLineL_free(&x->neckDelay);
}

void bowed_dsp(t_bowed *x, t_signal **sp, short *count)
{
	x->x_bpconnected = count[0];
	x->x_bposconnected = count[1];
	x->x_bvconnected = count[2];
	x->x_vfconnected = count[3];
	x->x_vaconnected = count[4];
	x->x_frconnected = count[5];
	x->srate = sp[0]->s_sr;
    x->one_over_srate = 1./x->srate;
    OnePole_setPole(&x->reflFilt, 0.6 - (0.1 * 22050. / x->srate));
	dsp_add(bowed_perform, 9, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, \
								 sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[0]->s_n);	
	
}

t_int *bowed_perform(t_int *w)
{
	t_bowed *x = (t_bowed *)(w[1]);
	
	float bp = x->x_bpconnected? *(float *)(w[2]) : x->x_bp;
	float bpos = x->x_bposconnected? *(float *)(w[3]) : x->x_bpos;
	float bv = x->x_bvconnected? *(float *)(w[4]) : x->x_bv;
	float vf = x->x_vfconnected? *(float *)(w[5]) : x->x_vf;
	float va = x->x_vaconnected? *(float *)(w[6]) : x->x_va;
	float fr = x->x_frconnected? *(float *)(w[7]) : x->x_fr;
	
	float *out = (float *)(w[8]);
	long n = w[9];

	float temp, nutRefl, newVel, velDiff, stringVel, bridgeRefl;	

	if(fr != x->fr_save) {
		setFreq(x, fr);
		x->fr_save = fr;
	}

	x->vibRate = VIBLENGTH * x->one_over_srate * vf; 
	
	x->bowTabl.slope = bp;

	if(bpos != x->betaRatio) {
		x->betaRatio = bpos;
		DLineL_setDelay(&x->bridgeDelay, x->baseDelay * x->betaRatio); /* bow to bridge length   */
    	DLineL_setDelay(&x->neckDelay, x->baseDelay * (1. - x->betaRatio));	/* bow to nut (finger) length   */
  	}

	while(n--) {
		
		bridgeRefl = -OnePole_tick(&x->reflFilt, 
			x->bridgeDelay.lastOutput);		/* Bridge Reflection      */
		nutRefl = x->neckDelay.lastOutput; 	/* Nut Reflection         */
		stringVel = bridgeRefl + nutRefl; 	/* Sum is String Velocity */
		velDiff = bv - stringVel;			/* Differential Velocity  */
		newVel = velDiff * BowTabl_lookup(&x->bowTabl, velDiff);	 /* Non-Lin Bow Function   */
		DLineL_tick(&x->neckDelay, bridgeRefl + newVel); /* Do string              */   
		DLineL_tick(&x->bridgeDelay, nutRefl + newVel);  /*   propagations         */
    
  		if (va > 0.)  {
  			DLineL_setDelay(&x->neckDelay, (x->baseDelay * (1.0 - x->betaRatio)) + 
            			    (x->baseDelay * va * vib_tick(x)));
    	}

		*out++ = BiQuad_tick(&x->bodyFilt, x->bridgeDelay.lastOutput);
	}
	return w + 10;
}	
