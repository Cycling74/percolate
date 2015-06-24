/*********************************************/
/*  Bowed Bar model                          */
/*  by Georg Essl, 1999                      */
/*  For details refer to:                    */
/*    G.Essl, P.R.Cook: "Banded Waveguides:  */
/*    Towards Physical Modelling of Bar      */
/*    Percussion Instruments", ICMC'99       */
/*										     */
/*  ported to MSP by Dan Trueman, 2000	     */
/*********************************************/
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include "stk_c.h"
#include <math.h> 

t_class *bowedbar_class;

typedef struct _bowedbar
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars
    float x_bp;					//bow pressure	
    float x_bpos;				//bow position
    float x_bv; 				//bow velocity
    float x_GAIN; 				//uh, gain...
    float x_integration_const_; //cool bug var
    float x_freq;				//frequency	

	//to avoid updating freq unnecessarily...
    float fr_save;
    
    //signals connected? or controls...
    short x_bpconnected;
    short x_bposconnected;
    short x_bvconnected;
    short x_GAINconnected;
    short x_ic_connected;
    short x_freqconnected;
    
    //delay lines
  	DLineN delay[4];
    
    //biquad
    BiQuad bandpass_[4];

    //bow table
    BowTabl bowTabl;
  
    //stuff
	float modes[4];
    float Zs[4][2];
    float coeffs[4][2];
  	float filtOut[4];
  	float filtIn[4];
 	float filtGain[4];
  	int length;
  	float R;
  	float gains[4];
  	float slope;
  	float velinput;
  	float integration_const_;
  	int NR_MODES;
    
    float srate, one_over_srate;
} t_bowedbar;

/****PROTOTYPES****/

//setup funcs
void *bowedbar_new(double val);
void bowedbar_free(t_bowedbar *x);
void bowedbar_assist(t_bowedbar *x, void *b, long m, long a, char *s);

// dsp stuff
void bowedbar_dsp64(t_bowedbar *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void bowedbar_perform64(t_bowedbar *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void bowedbar_float(t_bowedbar *x, double f);

//bowedbar functions
void setFreq(t_bowedbar *x, float freq);
void setFreq(t_bowedbar *x, float freq);
void clear(t_bowedbar *x);
void setStrikePosition(t_bowedbar *x, float position);
void tuneBandPasses(t_bowedbar *x);
void pluck(t_bowedbar *x, float amplitude);

/****FUNCTIONS****/

void setFreq(t_bowedbar *x, float freq)
{
	int i;
	if(freq < 20.) freq = 20.;
  	x->x_freq = freq;
  	if(x->x_freq > 1568.0) x->x_freq = 1568.0;
  	x->length = (int)(x->srate/x->x_freq);

	x->NR_MODES = 4;
  	for(i = 0; i<x->NR_MODES; i++) {
      if((int)(x->length/x->modes[i]) > 4)
        DLineN_setDelay(&x->delay[i], (int)(x->length/x->modes[i]));
      else	{
        x->NR_MODES = i;
        break;
      }
      
      /*   FIX THIS BETTER!!!!! */
      DLineN_clear(&x->delay[i]);
    
	  BiQuad_clear(&x->bandpass_[i]);    

      // x->Zs[i][1] = 0.0;
      // x->Zs[i][2] = 0.0;
      x->Zs[i][0] = 0.0;
      x->Zs[i][1] = 0.0;
      x->filtOut[i] = 0.0;
      x->filtIn[i] = 0.0;
    }
  
  	tuneBandPasses(x);
}

void clear(t_bowedbar *x)
{
  long i;  
  for(i = 0; i<x->NR_MODES; i++)
    {
      DLineN_clear(&x->delay[i]);
      BiQuad_clear(&x->bandpass_[i]);
        
      // x->Zs[i][1] = 0.0;
      // x->Zs[i][2] = 0.0;
      x->Zs[i][0] = 0.0;
      x->Zs[i][1] = 0.0;
        
      x->filtOut[i] = 0.0;
      x->filtIn[i] = 0.0;
    }
}

void setStrikePosition(t_bowedbar *x, float position)
{
  float temp2;
  temp2 = position * TWO_PI * .5;
  x->gains[0] = fabs(sin(temp2 / 2) * pow(0.9,0));                                       
  x->gains[1] = fabs(sin(temp2) * pow(0.9,1));
  x->gains[2] = fabs(sin(temp2 * 3 / 2) * pow(0.9,2));
  x->gains[3] = fabs(sin(temp2 * 2) * pow(0.9,3));
}

void tuneBandPasses(t_bowedbar *x)
{
  long i;  
  for(i=0; i<x->NR_MODES; i++)
    {
      x->R = 1 - 6.28318530718 * x->x_freq * x->modes[i] / x->srate / 2.0;
      BiQuad_setFreqAndReson(&x->bandpass_[i], x->x_freq * x->modes[i], x->R, x->srate);
	  BiQuad_setEqualGainZeroes(&x->bandpass_[i]);
	  BiQuad_setGain(&x->bandpass_[i], (1.0-x->R*x->R)/2.0);
      x->filtGain[i] = (1.0 - (x->R*x->R))/2.0;
      x->coeffs[i][1] = -x->R * x->R;
      x->coeffs[i][0] = 2.0 * x->R * cos(6.28318530718 * x->x_freq * x->modes[i] / x->srate);
    
      DLineN_clear(&x->delay[i]); 	//(rand()) - 16384;
    }
}

void pluck(t_bowedbar *x, float amplitude)
{
  long i,j;
  int pluckLen;
  float temp;
  
  pluckLen = (int)(x->length/x->modes[x->NR_MODES-1]);
  for (j=1;j<pluckLen/2;j++)	{
    temp = amplitude*2.0*Noise_tick();
    for(i=0; i<x->NR_MODES; i++)
      DLineN_tick(&x->delay[i], temp*j/pluckLen*x->gains[i]);
  }
  for (j=pluckLen/2;j>0;j--)	{
    temp = amplitude*2.0*Noise_tick();
    for(i=0; i<x->NR_MODES; i++)
      DLineN_tick(&x->delay[i], temp*j/pluckLen*x->gains[i]);;
  }
}

//primary MSP funcs
void ext_main(void* p)
{
    t_class *c = class_new("bowedbar~", (method)bowedbar_new, (method)bowedbar_free, (long)sizeof(t_bowedbar), 0L, A_DEFFLOAT, 0);
    
    class_addmethod(c, (method)bowedbar_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)bowedbar_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)bowedbar_float, "float", A_FLOAT, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    bowedbar_class = c;
}

void *bowedbar_new(double initial_coeff)
{
	int i;
    
    t_bowedbar *x = (t_bowedbar *)object_alloc(bowedbar_class);
    
    if (x) {
        //zero out the struct, to be careful (takk to jkclayton)
        for(i=sizeof(t_pxobject)-1;i<sizeof(t_bowedbar);i++) {
            ((char *)x)[i]=0;
        }
        dsp_setup((t_pxobject *)x,6);
        outlet_new((t_object *)x, "signal");
        
        x->x_bp = 0.5;
        x->x_bpos = 0.15;
        x->x_bv = 0.5;
        x->x_freq = 440.;
        
        x->modes[0] = 1.0;
        x->modes[1] = 2.756;
        x->modes[2] = 5.404;
        x->modes[3] = 8.933;
        
        x->length = 100.;
        
        for (i=0;i<4;i++)	{
            x->gains[i] = pow(0.9,(double) i);
            DLineN_alloc(&x->delay[i], 2408);
            DLineN_setDelay(&x->delay[i], (int)(x->length/x->modes[i]));
            DLineN_clear(&x->delay[i]);
            BiQuad_init(&x->bandpass_[i]);
            BiQuad_clear(&x->bandpass_[i]);
            x->Zs[i][0] = 0.0;
            x->Zs[i][1] = 0.0;
            x->filtOut[i] = 0.0;
            x->filtIn[i] = 0.0;
        }
        
        x->srate = sys_getsr();
        x->one_over_srate = 1./x->srate;
        
        //initialize things
        BowTabl_init(&x->bowTabl);
        x->bowTabl.slope = 3.0;
        x->slope = 3.;
        x->R = 0.97;
        x->x_GAIN = 0.999;
        x->integration_const_ = 0.;
        x->velinput = 0.;
        
        x->fr_save = x->x_freq;
        
        post("some people do this for a living...");
    }
    
    return (x);
}

void bowedbar_free(t_bowedbar *x)
{
	int i;
	dsp_free((t_pxobject *)x);
	for(i=0;i<4;i++) {
		DLineN_free(&x->delay[i]);
	}
}

void bowedbar_assist(t_bowedbar *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
            case 0:
                sprintf(s,"(signal/float) bow pressure");
                break;
            case 1:
                sprintf(s,"(signal/float) bow position");
                break;
            case 2:
                sprintf(s,"(signal/float) bow velocity");
                break;
            case 3:
                sprintf(s,"(signal/float) gain");
                break;
            case 4:
                sprintf(s,"(signal/float) integration");
                break;
            case 5:
                sprintf(s,"(signal/float) frequency");
                break;
        }
	} else {
		sprintf(s,"(signal) output");
    }
}

void bowedbar_float(t_bowedbar *x, double f)
{
	if (x->x_obj.z_in == 0) {
		x->x_bp = f;
	} else if (x->x_obj.z_in == 1) {
		x->x_bpos = f;
	} else if (x->x_obj.z_in == 2) {
		x->x_bv = f;
	} else if (x->x_obj.z_in == 3) {
		x->x_GAIN = f;
	} else if (x->x_obj.z_in == 4) {
		x->x_integration_const_ = f;
	} else if (x->x_obj.z_in == 5) {
		x->x_freq = f;
	}
}

void bowedbar_dsp64(t_bowedbar *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->x_bpconnected = count[0];
	x->x_bposconnected = count[1];
	x->x_bvconnected = count[2];
	x->x_GAINconnected = count[3];
	x->x_ic_connected = count[4];
	x->x_freqconnected = count[5];
	x->srate = samplerate;
    x->one_over_srate = 1./x->srate;

    object_method(dsp64, gensym("dsp_add64"), x, bowedbar_perform64, 0, NULL);
}

void bowedbar_perform64(t_bowedbar *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	double bp 	= x->x_bpconnected                  ? *(double *)(ins[0]) : x->x_bp;
	double bpos = x->x_bposconnected                ? *(double *)(ins[1]) : x->x_bpos;
	double bv 	= x->x_bvconnected                  ? *(double *)(ins[2]) : x->x_bv;
	double GAIN = x->x_GAINconnected                ? *(double *)(ins[3]) : x->x_GAIN;
	double integration_const_ = x->x_ic_connected   ? *(double *)(ins[4]) : x->x_integration_const_;
	double fr 	= x->x_freqconnected                ? *(double *)(ins[5]) : x->x_freq;
	
	double *out = (double *)(outs[0]);
	long n = sampleframes;
    
	double input, data;
	long k;
	
	if(fr != x->fr_save) {
		setFreq(x, fr);
		x->fr_save = fr;
	}
	
	x->bowTabl.slope = bp;
	x->slope = bp;
	setStrikePosition(x, bpos);
    
	while(n--) {
        
 		data = 0.0;
  		input = 0.0;
        
  		if(integration_const_ == 0.0)
    		x->velinput = 0.0;
  		else
    		x->velinput = integration_const_ * x->velinput;
        
  		for(k=0; k<x->NR_MODES; k++) {
      		x->velinput += GAIN * x->delay[k].lastOutput;
    	}
        
      	input = bv - x->velinput;
      	input = input * BowTabl_lookup(&x->bowTabl, input);
      	input = input/(double)x->NR_MODES;
        
  		for(k=0; k<x->NR_MODES; k++) {
  			BiQuad_tick(&x->bandpass_[k], input*x->gains[k] + GAIN * x->delay[k].lastOutput);
      		DLineN_tick(&x->delay[k], x->bandpass_[k].lastOutput);
      		data += x->bandpass_[k].lastOutput;
    	}
        
		*out++ =  data * 4.0;
	}
}

