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

#include "stk_c.h"
#include <math.h> 
#define LENGTH 1024 	//44100/LOWFREQ + 1 --plucked length

void *plucked_class;

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

    float srate, one_over_srate;
} t_plucked;

/****PROTOTYPES****/

//setup funcs
void *plucked_new(double val);
void plucked_free(t_plucked *x);
void plucked_dsp(t_plucked *x, t_signal **sp, short *count);
void plucked_float(t_plucked *x, double f);
void plucked_bang(t_plucked *x);
t_int *plucked_perform(t_int *w);
void plucked_assist(t_plucked *x, void *b, long m, long a, char *s);

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
void main(void)
{
    setup((struct messlist **)&plucked_class, (method)plucked_new, (method)plucked_free, (short)sizeof(t_plucked), 0L, A_DEFFLOAT, 0);
    addmess((method)plucked_dsp, "dsp", A_CANT, 0);
    addmess((method)plucked_assist,"assist",A_CANT,0);
    addfloat((method)plucked_float);
    addbang((method)plucked_bang);
    dsp_initclass();
    rescopy('STR#',9980);
}

void plucked_assist(t_plucked *x, void *b, long m, long a, char *s)
{
	assist_string(9980,m,a,1,3,s);
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

    t_plucked *x = (t_plucked *)newobject(plucked_class);
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

void plucked_dsp(t_plucked *x, t_signal **sp, short *count)
{
	x->x_pluckAmpconnected = count[0];
	x->x_frconnected = count[1];

	x->srate = sp[0]->s_sr;
    x->one_over_srate = 1./x->srate;
	dsp_add(plucked_perform, 5, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[0]->s_n);	
}

t_int *plucked_perform(t_int *w)
{
	t_plucked *x = (t_plucked *)(w[1]);
	
	float pluckAmp = x->x_pluckAmpconnected? *(float *)(w[2]) : x->x_pluckAmp;
	float fr = x->x_frconnected? *(float *)(w[3]) : x->x_fr;
	float *out = (float *)(w[4]);
	long n = w[5];

	float temp;	

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
	return w + 6;
}	
