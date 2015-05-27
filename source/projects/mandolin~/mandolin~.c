/********************************************/
/*  Commuted Mandolin Subclass of enhanced  */
/*  dual plucked-string model               */
/*  by Perry Cook, 1995-96                  */
/*   Controls:    CONTROL1 = bodySize       */
/*                CONTROL2 = pluckPosition  */
/*                CONTROL3 = loopGain       */
/*                MOD_WHEEL= deTuning       */
/*										  	*/
/*  ported to MSP by Dan Trueman, 2000	  	*/
/*                                          */
/*  Note: Commuted Synthesis, as with many  */
/*  other WaveGuide techniques, is covered  */
/*  by patents, granted, pending, and/or    */
/*  applied-for.  All are assigned to the   */
/*  Board of Trustees, Stanford University. */
/*  For information, contact the Office of  */ 
/*  Technology Licensing, Stanford U.       */
/********************************************/ 

#include "stk_c.h" 

#include "mandimpulses.h"
#define LENGTH 2048 	//44100/LOWFREQ + 1 --mando length

void *mando_class;

typedef struct _mando
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars
    float pluckAmp;		//bow pressure
    float pluckPos;		//that's right
    float stringDamping;//yep...
    float detuning;		//tone deafness
    float bodySize;		//big mandolin
    float x_fr;			//frequency	
    
    int mic;			//directional position (NBody)

    float fr_save, detuning_save;
    
    //signals connected? or controls...
    short pluckAmpconnected;
    short pluckPosconnected;
    short stringDampingconnected;
    short detuningconnected;
    short bodySizeconnected;
    short x_frconnected;
   
    //delay lines0
    DLineA delayLine;
    DLineA delayLine2;
    DLineL combDelay;
    
    //impulse response files
    HeaderSnd soundfile[12];
    
    //filters
    OneZero filter;
    OneZero filter2;
    
    //stuff
    long length;
    float loopGain;
    float baseLoopGain;
    float lastFreq;
    float lastLength;
    short pluck;
    long dampTime;
    int waveDone;
    float directBody;

    float srate, one_over_srate;
} t_mando;

/****PROTOTYPES****/

//setup funcs
void *mando_new(double val);
void mando_free(t_mando *x);
void mando_dsp(t_mando *x, t_signal **sp, short *count);
void mando_float(t_mando *x, double f);
void mando_bang(t_mando *x);
t_int *mando_perform(t_int *w);
void mando_assist(t_mando *x, void *b, long m, long a, char *s);

//mando functions
void setFreq(t_mando *x, float frequency);
void pluck(t_mando *x, float amplitude, float position);
void setDetune(t_mando *x, float detune);
void setBodySize(t_mando *x, float size);
void setmic(t_mando *x, Symbol *s, short argc, Atom *argv);
void setBaseLoopGain(t_mando *x, float aGain);


/****FUNCTIONS****/

void pluck(t_mando *x, float amplitude, float position)
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

void setBodySize(t_mando *x, float size)
{
  int i;
  for (i=0;i<12;i++)	{
  	HeaderSnd_setRate(&x->soundfile[i], size);
  }
}

void mando_bang(t_mando *x)
{
	x->pluck = 1;
}

void setFreq(t_mando *x, float frequency)
{
  if(frequency < 20.) frequency = 20.;
  x->lastFreq = frequency;
  x->lastLength = x->srate / x->lastFreq;        /* length - delays */
  if (x->detuning != 0.) {
  	DLineA_setDelay(&x->delayLine, (x->lastLength / x->detuning) - .5);
  	DLineA_setDelay(&x->delayLine2, (x->lastLength * x->detuning) - .5);
  }
  x->loopGain = x->baseLoopGain + (frequency * 0.000005);
  if (x->loopGain>1.0) x->loopGain = 0.99999;
}

void setDetune(t_mando *x, float detune)
{
  if (detune != 0.) {
  	x->detuning = detune;
  	DLineA_setDelay(&x->delayLine, (x->lastLength / x->detuning) - .5);
  	DLineA_setDelay(&x->delayLine2, (x->lastLength * x->detuning) - .5);
  }
}

void setBaseLoopGain(t_mando *x, float aGain)
{
  x->baseLoopGain = aGain;
  x->loopGain = x->baseLoopGain + (x->lastFreq * 0.000005);
  if (x->loopGain>1.0) x->loopGain = 0.99999;
}


//primary MSP funcs
void main(void)
{
    setup((struct messlist **)&mando_class, (method)mando_new, (method)mando_free, (short)sizeof(t_mando), 0L, A_DEFFLOAT, 0);
    addmess((method)mando_dsp, "dsp", A_CANT, 0);
    addmess((method)mando_assist,"assist",A_CANT,0);
    addmess((method)setmic, "mic", A_GIMME, 0);
    addfloat((method)mando_float);
    addbang((method)mando_bang);
    dsp_initclass();
    rescopy('STR#',9981);
}

void setmic(t_mando *x, Symbol *s, short argc, Atom *argv)
{
	short i;
	int temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (int)argv[i].a_w.w_long;
				x->mic = temp % 12;
    			post("mando: setting mic: %d", temp);
				break;
			case A_FLOAT:
				temp = (int)argv[i].a_w.w_long;
				x->mic = temp % 12;
    			post("mando: setting mic: %d", temp);
				break;
		}
	}
}

void mando_assist(t_mando *x, void *b, long m, long a, char *s)
{
	assist_string(9981,m,a,1,7,s);
}

void mando_float(t_mando *x, double f)
{
	if (x->x_obj.z_in == 0) {
		x->pluckAmp = f;
	} else if (x->x_obj.z_in == 1) {
		x->pluckPos = f;
	} else if (x->x_obj.z_in == 2) {
		x->stringDamping = f;
	} else if (x->x_obj.z_in == 3) {
		x->detuning = f;
	} else if (x->x_obj.z_in == 4) {
		x->bodySize = f;
	} else if (x->x_obj.z_in == 5) {
		x->x_fr = f;
	} 
}

void *mando_new(double initial_coeff)
{
	int i;
	char temp[128];
	
	
    t_mando *x = (t_mando *)newobject(mando_class);
     //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject)-1;i<sizeof(t_mando);i++)  
                ((char *)x)[i]=0; 
	} 
    dsp_setup((t_pxobject *)x,6);
    outlet_new((t_object *)x, "signal");
   
    x->length = LENGTH;
    x->baseLoopGain = 0.995;
    x->loopGain = 0.999;
    x->directBody = 1.0;
  	x->mic = 0;
  	x->dampTime = 0;
  	x->waveDone = 1;
  	x->pluckAmp = 0.3;
  	x->pluckPos = 0.4;
  	x->detuning = 0.995;
  	x->lastFreq = 80.;
  	x->lastLength = x->length * 0.5;
  	x->x_fr = 440.;
  	x->pluck = 0;
    
    x->srate = sys_getsr();
    x->one_over_srate = 1./x->srate;
    
    DLineA_alloc(&x->delayLine, LENGTH);
    DLineA_alloc(&x->delayLine2, LENGTH);
    DLineL_alloc(&x->combDelay, LENGTH);
    
    //clear stuff
    DLineA_clear(&x->delayLine);
    DLineA_clear(&x->delayLine2);
    DLineL_clear(&x->combDelay);
    OneZero_init(&x->filter);
    OneZero_init(&x->filter2);
    
    //impulse responses    
    for (i=0;i<12;i++) {
    	HeaderSnd_alloc(&x->soundfile[i], &mand[i][0], 721, "oneshot");
    }

    setFreq(x, x->x_fr);
   
    x->fr_save = x->x_fr;
    x->detuning_save = x->detuning;
    
    post("if you believe the mandolin is linear, i've got another one for ya...");
    
    
    return (x);
}

void mando_free(t_mando *x)
{
	int i;
	dsp_free((t_pxobject *)x);
	DLineA_free(&x->delayLine);
	DLineA_free(&x->delayLine2);
	DLineL_free(&x->combDelay);
	for (i=0;i<12;i++) 
		HeaderSnd_free(&x->soundfile[i]);
}

void mando_dsp(t_mando *x, t_signal **sp, short *count)
{
   	x->pluckAmpconnected 		= count[0];
	x->pluckPosconnected 		= count[1];
	x->stringDampingconnected 	= count[2];
	x->detuningconnected 		= count[3];
	x->bodySizeconnected 		= count[4];
	x->x_frconnected 			= count[5];

	x->srate = sp[0]->s_sr;
    x->one_over_srate = 1./x->srate;
	dsp_add(mando_perform, 9, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, 
		sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[0]->s_n);	
}

t_int *mando_perform(t_int *w)
{
	t_mando *x = (t_mando *)(w[1]);
	
	float pluckAmp = x->pluckAmpconnected? *(float *)(w[2]) : x->pluckAmp;
	float pluckPos = x->pluckPosconnected? *(float *)(w[3]) : x->pluckPos;
	float stringDamping = x->stringDampingconnected? *(float *)(w[4]) : x->stringDamping;
	float detuning = x->detuningconnected? *(float *)(w[5]) : x->detuning;
	float bodySize = x->bodySizeconnected? *(float *)(w[6]) : x->bodySize;
	float fr = x->x_frconnected? *(float *)(w[7]) : x->x_fr;
	float *out = (float *)(w[8]);
	long n = w[9];

	float temp, lastOutput;	

	if(fr != x->fr_save) {
		setFreq(x, fr);
		x->fr_save = fr;
	} 
	
	setBodySize(x, bodySize);
	setBaseLoopGain(x, stringDamping);
	
	if(detuning != x->detuning_save) {
		setDetune(x, detuning);
		x->detuning_save = detuning;
	}
	
	if(x->pluck) {
		pluck(x, pluckAmp, pluckPos);
		x->pluck = 0;
	}

	while(n--) {
		/* //this is busted, for some mysterious reason...
  		if (!x->waveDone)      {
  			x->waveDone = HeaderSnd_informTick(&x->soundfile[x->mic]);
    		temp = x->soundfile[x->mic].lastOutput * pluckAmp; 		
    		temp = temp - DLineL_tick(&x->combDelay, temp);			        		
  		}
  		*/	
  		
  		x->waveDone = HeaderSnd_informTick(&x->soundfile[x->mic]);   	
    	temp = x->soundfile[x->mic].lastOutput * pluckAmp; 	
    	temp = temp - DLineL_tick(&x->combDelay, temp);	 
    	                                 
  		if (x->dampTime>=0) {                             		/* Damping hack to help avoid */
    		x->dampTime -= 1;                               	/* overflow on replucking     */
    		lastOutput = DLineA_tick(&x->delayLine,				/* Calculate 1st delay */
    			OneZero_tick(&x->filter, temp +					/* filterered reflection      */
    			(x->delayLine.lastOutput * .7)));				/* plus pluck excitation      */
    		lastOutput += DLineA_tick(&x->delayLine2,			/* and 2nd delay              */
    			OneZero_tick(&x->filter2, temp +				/* just like the 1st          */
    			(x->delayLine2.lastOutput * .7)));
  		}
  		else { /*  No damping hack after 1 period */
  			lastOutput = DLineA_tick(&x->delayLine,				/* Calculate 1st delay */
    			OneZero_tick(&x->filter, temp +					/* filterered reflection      */
    			(x->delayLine.lastOutput * x->loopGain)));		/* plus pluck excitation      */
    		lastOutput += DLineA_tick(&x->delayLine2,			/* and 2nd delay              */
    			OneZero_tick(&x->filter2, temp +				/* just like the 1st          */
    			(x->delayLine2.lastOutput * x->loopGain)));
  		}
    	
		*out++ = lastOutput;
		
	}
	return w + 10;
}	
