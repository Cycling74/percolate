//
// Updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

/******************************************/
/*  WaveGuide Flute ala Karjalainen,      */
/*  Smith, Waryznyk, etc.                 */
/*  with polynomial Jet ala Cook          */
/*  by Perry Cook, 1995-96                */
/*										  */
/*  ported to MSP by Dan Trueman, 2000	  */
/*  and modified to become the nearly	  */
/*  righteous Blotar.				 	  */
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

#include "stk_c.h"
#include "mandimpulses.h"
#define LENGTH 2048 	//44100/LOWFREQ + 1 --blotar length
#define JETLENGTH LENGTH * 2 //larger, for big rooms
#define VIBLENGTH 1024

t_class *blotar_class;

typedef struct _blotar
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars
    double pluckAmp;		//pluck amplitude
    double pluckPos;		//that's right
    double bodySize;		//big blotarlin
    double x_fr;			//frequency	    
    double x_bp;			//breath pressure	
    double x_jd;			//jet frequency
    double x_ng; 		//noise gain
    double x_vf; 		//vib freq
    double x_va; 		//vib amount
    double x_jr;			//pre-feedback gain (jet reflection coeff)
    double x_er;			//pre-distortion gain (end reflection coeff)
    double filterRatio;	//OneZero vs. OnePole filter ratio
    
    int mic;			//directional position (NBody)

    double fr_save;
    double jd_save;
    
    //signals connected? or controls...
    long pluckAmpconnected;
    long pluckPosconnected;
    long bodySizeconnected;
    long x_frconnected;
    long x_bpconnected;
    long x_jdconnected;
    long x_ngconnected;
    long x_vfconnected;
    long x_vaconnected;
    long x_jrconnected;
    long x_erconnected;
    long filterRatioconnected;
    
    //delay lines, flute
    DLineL boreDelay;
    DLineL jetDelay;
    DLineL combDelay;
    
    //DC blocker
    DCBlock killdc;
    
    //impulse response files
    HeaderSnd soundfile[12];
    
    //filters    
    OnePole flute_filter;
    OneZero lowpass; //lowpass filter
    
     //vibrato table
    double vibTable[VIBLENGTH];
    double vibRate;
    double vibTime;
    
    //stuff
    double endRefl;
    double jetRefl;
    
    //stuff
    long length;
    double lastFreq;
    double lastLength;
    long pluck;
    long dampTime;
    int waveDone;
    double directBody;
    
    long mode; //whether to run the "classic" (incorrect) blotar or the new ("correct") blotar
    			//"classic" by default

    double srate, one_over_srate;
} t_blotar;

/****PROTOTYPES****/

//setup funcs
void *blotar_new(double val);
void blotar_free(t_blotar *x);
void blotar_assist(t_blotar *x, void *b, long m, long a, char *s);

void blotar_bang(t_blotar *x);
void blotar_float(t_blotar *x, double f);
void setmic(t_blotar *x, t_symbol *s, long argc, t_atom *argv);
void blotar_mode(t_blotar *x, t_symbol *s, long argc, t_atom *argv);
void blotar_clear(t_blotar *x);

//helper funcs
void pluck(t_blotar *x, float amplitude, float position);
void setBodySize(t_blotar *x, float size);
void setFreq(t_blotar *x, float frequency);
void setJetDelay(t_blotar *x, float ratio);
void setVibFreq(t_blotar *x, float freq);
float vib_tick(t_blotar *x);

// dsp stuff
void blotar_dsp64(t_blotar *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void blotar_perform64(t_blotar *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);


/****FUNCTIONS****/

void pluck(t_blotar *x, float amplitude, float position)
{ /* this function gets interesting here, */
  /* because pluck may be longer than     */
  /* string length, so we just reset the  */
  /* soundfile and add in the pluck in    */
  /* the tick method.                     */
  x->pluckPos = position;     /* pluck position is zeroes at pos*length  */
  HeaderSnd_reset(&x->soundfile[x->mic]);
  x->pluckAmp = amplitude;
  /* Set Pick Position which puts zeroes at pos*length  */
  DLineL_setDelay(&x->combDelay, 0.5 * x->pluckPos * x->lastLength);
  x->dampTime = (long) x->lastLength;      /* See tick method below */
  x->waveDone = 0;
}

void setBodySize(t_blotar *x, float size)
{
  int i;
  for (i=0;i<12;i++)	{
  	HeaderSnd_setRate(&x->soundfile[i], size);
  }
}

#define WATCHIT 0.00001
void setFreq(t_blotar *x, float frequency)
{
  float temp;
  if(frequency < 20.) frequency = 20.;
  x->lastFreq = frequency;
  x->lastLength = x->srate / x->lastFreq;        /* length - delays */
  /*
  if (x->detuning != 0.) {
  	DLineA_setDelay(&x->delayLine, (x->lastLength / x->detuning) - .5);
  	DLineA_setDelay(&x->delayLine2, (x->lastLength * x->detuning) - .5);
  }
  x->loopGain = x->baseLoopGain + (frequency * 0.000005);
  if (x->loopGain>1.0) x->loopGain = 0.99999;
  */
  x->lastFreq = frequency * 0.66666;
  if(x->lastFreq < WATCHIT) x->lastFreq = WATCHIT;
  temp = (x->srate / x->lastFreq) - 2.;
  DLineL_setDelay(&x->boreDelay, temp);
}

void setJetDelay(t_blotar *x, float frequency)
{
	float temp;
	if(frequency < WATCHIT) frequency = WATCHIT;
	temp = (x->srate / frequency) - 2.;
	
	//control jet length directly, not as function of bore length
	DLineL_setDelay(&x->jetDelay, temp);
}	

//vib funcs
void setVibFreq(t_blotar *x, float freq)
{
	x->vibRate = VIBLENGTH * x->one_over_srate * freq;
}

float vib_tick(t_blotar *x)
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
    t_class *c = class_new("blotar~", (method)blotar_new, (method)blotar_free, (long)sizeof(t_blotar), 0L, A_DEFFLOAT, 0);
    class_addmethod(c, (method)blotar_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)blotar_assist,"assist",A_CANT,0);
    class_addmethod(c, (method)blotar_bang, "bang", A_CANT, 0);
    class_addmethod(c, (method)blotar_float, "float", A_FLOAT, 0);
    class_addmethod(c, (method)setmic, "mic", A_GIMME, 0);
    class_addmethod(c, (method)blotar_clear, "clear", A_GIMME, 0);
    class_addmethod(c, (method)blotar_mode, "mode", A_GIMME, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    blotar_class = c;
}

void *blotar_new(double initial_coeff)
{
	int i;
	
    t_blotar *x = (t_blotar *)object_alloc(blotar_class);
    if (x) {
        for(i=sizeof(t_pxobject);i<sizeof(t_blotar);i++) {
            ((char *)x)[i]=0;
        }

        dsp_setup((t_pxobject *)x, 12);
        outlet_new((t_object *)x, "signal");
        
        x->length = LENGTH;
        /*
         x->baseLoopGain = 0.995;
         x->loopGain = 0.999;
         */
        x->directBody = 1.0;
        x->mic = 0;
        x->dampTime = 0;
        x->waveDone = 1;
        x->pluckAmp = 0.3;
        x->pluckPos = 0.4;
        x->lastFreq = 80.;
        x->lastLength = x->length * 0.5;
        x->x_fr = 440.;
        x->pluck = 0;
        x->filterRatio = 1.;
        x->mode = 0;
        
        x->srate = sys_getsr();
        x->one_over_srate = 1./x->srate;
        
        DLineL_alloc(&x->boreDelay, LENGTH);
        DLineL_alloc(&x->jetDelay, JETLENGTH); //longer here, for long feedback loops, big rooms
        DLineL_alloc(&x->combDelay, LENGTH);
        
        for(i=0; i<VIBLENGTH; i++) x->vibTable[i] = sin(i*TWO_PI/VIBLENGTH);
        x->vibRate = 1.;
        x->vibTime = 0.;
        
        //clear stuff flute
        DLineL_clear(&x->boreDelay);
        DLineL_clear(&x->jetDelay);
        OnePole_init(&x->flute_filter);
        OneZero_init(&x->lowpass);
        DLineL_clear(&x->combDelay);
        
        //impulse responses
        for (i=0;i<12;i++) {
            HeaderSnd_alloc(&x->soundfile[i], &mand[i][0], 721, "oneshot");
        }
        
        setFreq(x, x->x_fr);
        DLineL_setDelay(&x->jetDelay, 49.);
        
        OnePole_setPole(&x->flute_filter, 0.7 - (0.1 * 22050. / x->srate));
        OnePole_setGain(&x->flute_filter, -1.);
        
        x->fr_save = x->x_fr;
        x->jd_save = 49.;
        
        post("dooooooooooode, air guitar!");
    }
    return (x);
}

void blotar_free(t_blotar *x)
{
	int i;
	dsp_free((t_pxobject *)x);
	DLineL_free(&x->combDelay);
	DLineL_free(&x->boreDelay);
	DLineL_free(&x->jetDelay);
	for (i=0;i<12;i++) {
		HeaderSnd_free(&x->soundfile[i]);
    }
}

void blotar_assist(t_blotar *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
            case 0:
                sprintf(s,"(signal/float) pluck amplitude");
                break;
            case 1:
                sprintf(s,"(signal/float) pluck position");
                break;
            case 2:
                sprintf(s,"(signal/float) body size");
                break;
            case 3:
                sprintf(s,"(signal/float) breath pressure");
                break;
            case 4:
                sprintf(s,"(signal/float) jet frequency");
                break;
            case 5:
                sprintf(s,"(signal/float) noise gain");
                break;
            case 6:
                sprintf(s,"(signal/float) vib frequency");
                break;
            case 7:
                sprintf(s,"(signal/float) vib amount");
                break;
            case 8:
                sprintf(s,"(signal/float) frequency");
                break;
            case 9:
                sprintf(s,"(signal/float) pre-feedback gain");
                break;
            case 10:
                sprintf(s,"(signal/float) pre-distortion gain");
                break;
            case 11:
                sprintf(s,"(signal/float) filter ratio (one-zero vs. one-pole)");
            break;		}
	} else {
		sprintf(s,"(signal) output");
    }
}

void blotar_bang(t_blotar *x)
{
	x->pluck = 1;
}

void blotar_float(t_blotar *x, double f)
{
	if (x->x_obj.z_in == 0) {
		x->pluckAmp = f;
	} else if (x->x_obj.z_in == 1) {
		x->pluckPos = f;
	} else if (x->x_obj.z_in == 2) {
		x->bodySize = f;
	} else if (x->x_obj.z_in == 3) {
		x->x_bp = f;
	} else if (x->x_obj.z_in == 4) {
		x->x_jd = f;
	} else if (x->x_obj.z_in == 5) {
		x->x_ng = f;
	} else if (x->x_obj.z_in == 6) {
		x->x_vf = f;
	} else if (x->x_obj.z_in == 7) {
		x->x_va = f;
	} else if (x->x_obj.z_in == 8) {
		x->x_fr = f;
	} else if (x->x_obj.z_in == 9) {
		x->x_jr = f;
	} else if (x->x_obj.z_in == 10) {
		x->x_er = f;
	} else if (x->x_obj.z_in == 11) {
		x->filterRatio = f;
	}
}

void setmic(t_blotar *x, t_symbol *s, long argc, t_atom *argv)
{
	long i;
	int temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (int)argv[i].a_w.w_long;
				x->mic = abs(temp % 12);
    			post("blotar: setting mic: %d", x->mic);
				break;
			case A_FLOAT:
				temp = (int)argv[i].a_w.w_long;
				x->mic = abs(temp % 12);
    			post("blotar: setting mic: %d", x->mic);
				break;
		}
	}
}

void blotar_mode(t_blotar *x, t_symbol *s, long argc, t_atom *argv)
{
	long i;
	int temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (int)argv[i].a_w.w_long;
				x->mode = temp % 2;
    			post("blotar: setting mode: %d", x->mode);
				break;
			case A_FLOAT:
				temp = (int)argv[i].a_w.w_long;
				x->mode = temp % 2;
    			post("blotar: setting mode: %d", x->mode);
				break;
		}
	}
}

void blotar_clear(t_blotar *x)
{
	DLineL_clear(&x->boreDelay);
    DLineL_clear(&x->jetDelay);
    DLineL_clear(&x->combDelay);
    OnePole_init(&x->flute_filter);
    OneZero_init(&x->lowpass);
    DCBlock_clear(&x->killdc);
    OnePole_setPole(&x->flute_filter, 0.7 - (0.1 * 22050. / x->srate));
    OnePole_setGain(&x->flute_filter, -1.);
}

void blotar_dsp64(t_blotar *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->pluckAmpconnected = count[0];
	x->pluckPosconnected = count[1];
	x->bodySizeconnected = count[2];
	x->x_bpconnected = count[3];
	x->x_jdconnected = count[4];
	x->x_ngconnected = count[5];
	x->x_vfconnected = count[6];
	x->x_vaconnected = count[7];
	x->x_frconnected = count[8];
	x->x_jrconnected = count[9];
	x->x_erconnected = count[10];
	x->filterRatioconnected = count[11];
	
	x->srate = samplerate;
    x->one_over_srate = 1./x->srate;
    OnePole_setPole(&x->flute_filter, 0.7 - (0.1 * 22050. / x->srate));
    
    object_method(dsp64, gensym("dsp_add64"), x, blotar_perform64, 0, NULL);
}

void blotar_perform64(t_blotar *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	double pluckAmp = x->pluckAmpconnected          ?   *(double *)(ins[0]) : x->pluckAmp;
	double pluckPos = x->pluckPosconnected          ?   *(double *)(ins[1]) : x->pluckPos;
	double bodySize = x->bodySizeconnected          ?   *(double *)(ins[2]) : x->bodySize;
	double bp = x->x_bpconnected                    ?   *(double *)(ins[3]) : x->x_bp;
	double jd = x->x_jdconnected                    ?   *(double *)(ins[4]) : x->x_jd;
	double ng = x->x_ngconnected                    ?   *(double *)(ins[5]) : x->x_ng;
	double vf = x->x_vfconnected                    ?   *(double *)(ins[6]) : x->x_vf;
	double va = x->x_vaconnected                    ?   *(double *)(ins[7]) : x->x_va;
	double fr = x->x_frconnected                    ?   *(double *)(ins[8]) : x->x_fr;
	double jr = x->x_jrconnected                    ?   *(double *)(ins[9]) : x->x_jr;
	double er = x->x_erconnected                    ?   *(double *)(ins[10]) : x->x_er;
	double filterRatio = x->filterRatioconnected    ?   *(double *)(ins[11]) : x->filterRatio;
    
    double *out = (double *)outs[0];
    long n = sampleframes;
    
	double temp, tempsave, pressureDiff, randPressure, filterRatioInv;
    
	if(fr != x->fr_save) {
		setFreq(x, fr);
		x->fr_save = fr;
	}
	
 	//room feedback length, or jet delay length
	if(jd != x->jd_save) {
		setJetDelay(x, jd);
		x->jd_save = jd;
	}
	
	filterRatioInv = 1. - filterRatio;
	setBodySize(x, bodySize);
	x->vibRate = VIBLENGTH * x->one_over_srate * vf;
	
	if(x->pluck) {
		pluck(x, pluckAmp, pluckPos);
		x->pluck = 0;
	}
    
	while(n--) {
		randPressure  = ng * Noise_tick();
		randPressure += va * vib_tick(x);
		randPressure *= bp;
        
		temp = 0.;
  		//if (!x->waveDone)      {
        x->waveDone = HeaderSnd_informTick(&x->soundfile[x->mic]);/* as long as it goes . . .   */
        temp = x->soundfile[x->mic].lastOutput * pluckAmp; 		  /* scaled pluck excitation    */
        temp = temp - DLineL_tick(&x->combDelay, temp);			  /* with comb filtering        */
  		//}
  		
  		//balance OnePole (flute) with LowPass (Karplus Strong); total wacko hack, but sounds cool
  		tempsave = temp;
  		temp = OnePole_tick(&x->flute_filter, (x->boreDelay.lastOutput + temp));
  		temp = filterRatio * temp +
        filterRatioInv *
        OneZero_tick(&x->lowpass, (x->boreDelay.lastOutput + tempsave));
        
    	temp = DCBlock_tick(&x->killdc, temp);
		pressureDiff = bp + randPressure - (jr * temp);
		pressureDiff = DLineL_tick(&x->jetDelay, pressureDiff);
		
		//the original blotar fed the output of both delay lines into the non-linearity (somehow a parenthesis got moved)
		//which makes it different than the flute, but also more stable (constraining the range of values)
		//the "mode" message lets the user choose "classic" (incorrect)	mode or the more "correct" (but less stable mode)
		//"classic" by default, of course.....
		if(!x->mode) pressureDiff = JetTabl_lookup(pressureDiff + (er * temp)); //from the original, "incorrect" blotar
		else {
		 	pressureDiff =  JetTabl_lookup(pressureDiff) + (er * temp); 		//this is "correct"
			//constrain? to keep it from blowing up
	    	if (pressureDiff > 10.) pressureDiff = 0.; //make this threshold user-controllable
	    	else if (pressureDiff < -10.) pressureDiff = 0.;
	    }
        
    	*out++ = DLineL_tick(&x->boreDelay, pressureDiff);
	}
}

