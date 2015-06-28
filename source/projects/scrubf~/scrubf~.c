/********************************************/
/*  A scrubbing delay-line instrument      	*/
/*  this one is built on the notorious		*/
/*	and now classic "scrub~" object, but	*/
/*	also includes a feedback element.		*/
/*											*/
/*	yet another PeRColate hack				*/
/*  										*/
/*  by dan trueman ('98 and on....	)		*/
/*											*/
/********************************************/
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define BUFLENGTH 132300. //3 secs
#define MAXBUFLENGTH 3.*132300. 
#define BUFSIZE BUFLENGTH

t_class *scrub_class;

typedef struct _scrub
{
	//header
    t_pxobject x_obj;

    //DC blocker
    float *buf0, *buf1, *buf2;
    float where, rate;
    float where0;
    float where1;
    float where2;
    long recordPoint;
    float coeff[3];
    int whichBuf; //which buf is currently recording
    float overlap; //number of samps to overlap buffers
    float overlapUpdate;
    float recordenv; //ramp size for record buffers
    float attkTail;
    float overlapInv; 
    float recordenvInv;   
    float delaylen; 
    float delaylen0;
    float delaylen1;
    float delaylen2;
    float delaylenUpdate;
    float recordlen;
    short updatevals;
    float buflen;
    float initbuflen;
    int record;
    
    float feedback; //sample to feedback
    short sync; 	//feedback sync mode; 	1=> feedback sample at record point
    				//						2=> feedback current output sample
    
    int rate_connected;
    int power;
    
    float srate, one_over_srate;
    float srate_ms, one_over_srate_ms;
} t_scrub;

/****PROTOTYPES****/

//setup funcs
void *scrub_new(double val);
void scrub_assist(t_scrub *x, void *b, long m, long a, char *s);

void scrub_float(t_scrub *x, double f);
void scrub_alloc(t_scrub *x);
void scrub_free(t_scrub *x);

float getSamp0(t_scrub *x);
float getSamp1(t_scrub *x);
float getSamp2(t_scrub *x);
float recordEnvelope(t_scrub *x, float sample);
float attackEnvelope(t_scrub *x, float sample);
float decayEnvelope(t_scrub *x, float sample);
void setoverlap(t_scrub *x, t_symbol *s, long argc, t_atom *argv);
void setramp(t_scrub *x, t_symbol *s, long argc, t_atom *argv);
void setdelay(t_scrub *x, t_symbol *s, long argc, t_atom *argv);
void setpower(t_scrub *x, t_symbol *s, long argc, t_atom *argv);
void setsync(t_scrub *x, t_symbol *s, long argc, t_atom *argv);
void setrecord(t_scrub *x, t_symbol *s, long argc, t_atom *argv);
void zero(t_scrub *x, t_symbol *s, long argc, t_atom *argv);
void trigger(t_scrub *x, t_symbol *s, long argc, t_atom *argv);

// dsp stuff
void scrub_dsp64(t_scrub *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void scrub_perform64(t_scrub *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

/****FUNCTIONS****/

void setoverlap(t_scrub *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	x->updatevals = 1;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (float)argv[i].a_w.w_long;
				if(temp < 10.) temp = 10.;
				x->overlapUpdate = x->srate_ms*temp;
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
				if(temp < 10.) temp = 10.;
				x->overlapUpdate = x->srate_ms*temp;
				break;
		}
	}
}

void setpower(t_scrub *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	int temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (int)argv[i].a_w.w_long;
				x->power = temp;
    			post("scrub: setting power: %d", temp);
				break;
			case A_FLOAT:
				temp = (int)argv[i].a_w.w_long;
				x->power = temp;
    			post("scrub: setting power: %d", temp);
				break;
		}
	}
}

void setsync(t_scrub *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	int temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (int)argv[i].a_w.w_long;
				x->sync = temp;
    			post("scrub: setting sync: %d", temp);
				break;
			case A_FLOAT:
				temp = (int)argv[i].a_w.w_long;
				x->sync = temp;
    			post("scrub: setting sync: %d", temp);
				break;
		}
	}
}

void setrecord(t_scrub *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	int temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (int)argv[i].a_w.w_long;
				x->record = temp;
    			post("scrub: record: %d", temp);
				break;
			case A_FLOAT:
				temp = (int)argv[i].a_w.w_long;
				x->record = temp;
    			post("scrub: record: %d", temp);
				break;
		}
	}
}

void zero(t_scrub *x, t_symbol *s, long argc, t_atom *argv)
{
	long i;
	
	post ("scrub: zeroing delay lines");
	//for(i=0; i<BUFSIZE; i++) {
	for(i=0; i<x->buflen; i++) {
    	x->buf0[i] = 0.;
    	x->buf1[i] = 0.;
    	x->buf2[i] = 0.;
    }

}

void trigger(t_scrub *x, t_symbol *s, long argc, t_atom *argv)
{
	post ("scrub: triggering");
	x->recordPoint = 0;
	x->where0 = 0.;
	x->where1 = 0.;
	x->where2 = 0.;
	x->where = 0.;

}

void setramp(t_scrub *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (float)argv[i].a_w.w_long;
				if(temp < 10.) temp = 10.;
				x->recordenv = x->srate_ms*temp;
				if(x->recordenv > 0.5*x->delaylen) x->recordenv = 0.5*x->delaylen;
				x->recordenvInv = 1./x->recordenv;
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
				if(temp < 10.) temp = 10.;
				x->recordenv = x->srate_ms*temp;
				if(x->recordenv > 0.5*x->delaylen) x->recordenv = 0.5*x->delaylen;
				x->recordenvInv = 1./x->recordenv;
				break;
		}
	}
}

//delay length in ms (sorta)
void setdelay(t_scrub *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	x->updatevals = 1;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (float)argv[i].a_w.w_long;
				if(temp < 10.) temp = 10.;
				x->delaylenUpdate = x->srate_ms*temp;
				if(x->delaylen  > x->buflen) x->delaylen = x->buflen;
				if(x->delaylenUpdate  > x->buflen) x->delaylenUpdate = x->buflen;
				//if(x->delaylenUpdate > BUFSIZE) x->delaylenUpdate = BUFSIZE;
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
				if(temp < 10.) temp = 10.;
				x->delaylenUpdate = x->srate_ms*temp;
				if(x->delaylen  > x->buflen) x->delaylen = x->buflen;
				if(x->delaylenUpdate  > x->buflen) x->delaylenUpdate = x->buflen;
				//if(x->delaylenUpdate > BUFSIZE) x->delaylenUpdate = BUFSIZE;
				break;
		}
	}
}

float getSamp0(t_scrub *x)
{
	float alpha, om_alpha, output;
	long first;
	
	
	while(x->where0 < 0.) x->where0 += x->delaylen0;
	while(x->where0 >= x->delaylen0) x->where0 -= x->delaylen0;
	
	/*
	//could do the above with fmod as well. less efficient, more efficient?
	if(x->where0 < 0.) x->where0 = fmod(x->where0, x->delaylen);
	else if(x->where0 >= x->delaylen0) x->where0 = fmod(x->where0, x->delaylen);
	*/
	
	first = (long)x->where0;
	
	alpha = x->where0 - first;
	om_alpha = 1. - alpha;
	
	output = x->buf0[first++] * om_alpha;
	if(first <  x->delaylen0) {
		output += x->buf0[first] * alpha;
	}
	else {
		output += x->buf0[0] * alpha;
	}
	
	return output;
	
}

float getSamp2(t_scrub *x)
{
	float alpha, om_alpha, output;
	long first;

	
	while(x->where2 < 0.) x->where2 += x->delaylen2;
	while(x->where2 >= x->delaylen2) x->where2 -= x->delaylen2;
	
	/*
	//could do the above with fmod as well. less efficient, more efficient?
	if(x->where2 < 0.) x->where2 = fmod(x->where2, x->delaylen2);
	else if(x->where2 >= x->delaylen2) x->where2 = fmod(x->where2, x->delaylen2);
	*/
	
	first = (long)x->where2;
	
	alpha = x->where2 - first;
	om_alpha = 1. - alpha;
	
	output = x->buf2[first++] * om_alpha;
	if(first <  x->delaylen2) {
		output += x->buf2[first] * alpha;
	}
	else {
		output += x->buf2[0] * alpha;
	}
	
	return output;
	
}

float getSamp1(t_scrub *x)
{
	float alpha, om_alpha, output;
	long first;
	
	
	while(x->where1 < 0.) x->where1 += x->delaylen1;
	while(x->where1 >= x->delaylen1) x->where1 -= x->delaylen1;
	

	/*	
	//could do the above with fmod as well. less efficient, more efficient?
	if(x->where1 < 0.) x->where1 = fmod(x->where1, x->delaylen1);
	else if(x->where1 >= x->delaylen1) x->where1 = fmod(x->where1, x->delaylen1);
	*/
	
	first = (long)x->where1;
	
	alpha = x->where1 - first;
	om_alpha = 1. - alpha;
	
	output = x->buf1[first++] * om_alpha;
	if(first <  x->delaylen1) {
		output += x->buf1[first] * alpha;
	}
	else {
		output += x->buf1[0] * alpha;
	}
	
	return output;
	
}

void scrub_assist(t_scrub *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
            case 0:
                sprintf(s,"signal input");
                break;
            case 1:
                sprintf(s,"(signal/float) rate");
                break;
        }
	} else {
		sprintf(s,"(signal) output");
    }
}


//primary MSP funcs
void ext_main(void* p)
{
    t_class *c = class_new("scrubf~", (method)scrub_new, (method)scrub_free, (long)sizeof(t_scrub), 0L, A_DEFFLOAT, 0);
    
    class_addmethod(c, (method)scrub_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)scrub_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)scrub_float, "float", A_FLOAT, 0);
    
    class_addmethod(c, (method)setoverlap, "overlap", A_GIMME, 0);
    class_addmethod(c, (method)setramp, "ramp", A_GIMME, 0);
    class_addmethod(c, (method)setdelay, "delay", A_GIMME, 0);
    class_addmethod(c, (method)setpower, "power", A_GIMME, 0);
    class_addmethod(c, (method)setsync, "sync", A_GIMME, 0);
    class_addmethod(c, (method)setrecord, "record", A_GIMME, 0);
    class_addmethod(c, (method)zero, "zero", A_GIMME, 0);
    class_addmethod(c, (method)trigger, "trigger", A_GIMME, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    scrub_class = c;

}

void scrub_alloc(t_scrub *x){
	//x->buf0 = t_getbytes(BUFLENGTH * sizeof(float));
	//x->buf0 = t_getbytes(x->buflen * sizeof(float));
	x->buf0 = (float *)sysmem_newptr(x->buflen * sizeof(float));
	if (!x->buf0) {
		error("scrub: out of memory");
		return;
	}
	//x->buf1 = t_getbytes(BUFLENGTH * sizeof(float));
	//x->buf1 = t_getbytes(x->buflen * sizeof(float));
	x->buf1 = (float *)sysmem_newptr(x->buflen * sizeof(float));
	if (!x->buf1) {
		error("scrub: out of memory");
		return;
	}
	//x->buf2 = t_getbytes(BUFLENGTH * sizeof(float));
	//x->buf2 = t_getbytes(x->buflen * sizeof(float));
	x->buf2 = (float *)sysmem_newptr(x->buflen * sizeof(float));
	if (!x->buf2) {
		error("scrub: out of memory");
		return;
	}
}

void scrub_free(t_scrub *x)
{
	dsp_free((t_pxobject *)x);
	if (x->buf1)
		//t_freebytes(x->buf1, BUFLENGTH * sizeof(float));
		//t_freebytes(x->buf1, x->buflen * sizeof(float));
		sysmem_freeptr(x->buf1);
	if (x->buf2)
		//t_freebytes(x->buf2, BUFLENGTH * sizeof(float));
		//t_freebytes(x->buf2, x->buflen * sizeof(float));
		sysmem_freeptr(x->buf2);
	if (x->buf0)
		//t_freebytes(x->buf0, BUFLENGTH * sizeof(float));
		//t_freebytes(x->buf0, x->buflen * sizeof(float));
		sysmem_freeptr(x->buf0);
}


void *scrub_new(double scrubsize)
{
	int i;

    t_scrub *x = (t_scrub *)object_alloc(scrub_class);
       //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_scrub);i++)  
                ((char *)x)[i]=0; 
	} 
    dsp_setup((t_pxobject *)x, 3);
    outlet_new((t_object *)x, "signal");
    
    x->srate = sys_getsr();
    x->one_over_srate = 1./x->srate;
    x->srate_ms = .001 * x->srate;
    x->one_over_srate_ms = 1. / x->srate_ms;
    
    if (scrubsize < 100.) scrubsize = 3000;
    if (scrubsize > 100000.) scrubsize = 3000;
    post("scrubber: maximum scrubsize set to = %f milliseconds", scrubsize);
    
    if (x->buf1)
		t_freebytes(x->buf1, x->initbuflen * sizeof(float));
	if (x->buf2)
		t_freebytes(x->buf2, x->initbuflen * sizeof(float));
	if (x->buf0)
		t_freebytes(x->buf0, x->initbuflen * sizeof(float));
				    
    x->initbuflen = (float)scrubsize * 44.1;
    x->buflen = (float)scrubsize * 44.1;
	
    scrub_alloc(x);

    x->rate = 1.;
    x->where = 0.;
    x->where0 = 0.;
    x->where1 = 0.;
    x->where2 = 0.;
    x->recordPoint = 0;
    x->whichBuf = 0;
    x->overlap = 4410.;
    x->overlapUpdate = 4410.;
    x->recordenv = 4410.;
    x->record = 1;
    
    /*
    x->recordlen = BUFSIZE;
    x->delaylen = BUFSIZE;
    x->delaylen0 = BUFSIZE;
    x->delaylen1 = BUFSIZE;
    x->delaylen2 = BUFSIZE;
    x->delaylenUpdate = BUFSIZE;
    */
    
    x->recordlen = x->buflen;
    x->delaylen = x->buflen;
    x->delaylen0 = x->buflen;
    x->delaylen1 = x->buflen;
    x->delaylen2 = x->buflen;
    x->delaylenUpdate = x->buflen;
    x->recordPoint = 0;

    x->attkTail = x->delaylen - x->overlap;    
    x->overlapInv = 1./x->overlap; 
    x->recordenvInv = 1./x->recordenv;
    x->rate_connected = 0;
    
    x->power = 1;
    x->updatevals = -1;
    
    x->coeff[0] = x->coeff[1] = x->coeff[2] = 0.;
    
    //for(i=0; i<BUFSIZE; i++) {
    for(i=0; i<x->buflen; i++) {
    	x->buf0[i] = 0.;
    	x->buf1[i] = 0.;
    	x->buf2[i] = 0.;
    }
    
    x->sync = 1;
    x->feedback = 0.;
    
    return (x);
}

void scrub_float(t_scrub *x, double f)
{
	if (x->x_obj.z_in == 1) {
		x->rate = f;
		//post("scrub: setting rate =  %f", f);
	}
}

float recordEnvelope(t_scrub *x, float sample)
{
	long done = x->recordPoint;
	//long tail = x->delaylen - x->recordPoint;
	long tail = x->recordlen - x->recordPoint;
	
	if(done < x->recordenv) sample *= done*x->recordenvInv;
	else if(tail < x->recordenv) sample *= tail*x->recordenvInv;
	
	return sample;
}

/*
 float attackEnvelope(t_scrub *x, float sample)
 //float decayEnvelope(t_scrub *x, float sample)
 {
 //long tail = x->attkTail;
 long tail = x->recordlen - x->overlap;
 float coeff = (x->recordPoint - (float)tail)*x->overlapInv;
 
 if(x->recordPoint > tail) sample *= coeff;
 else sample = 0.;
 
 return sample;
 }
 */
float attackEnvelope(t_scrub *x, float sample)
{
	if(x->recordPoint < x->overlap) sample *= x->recordPoint*x->overlapInv;
	else sample = 1.;
	
	return sample;
}

float decayEnvelope(t_scrub *x, float sample)
{
	long tail = x->recordlen - x->recordPoint;
	
	if(tail < x->overlap) sample *= (float)tail*x->overlapInv;
	else sample = 1.;
	
	return sample;
}

void scrub_dsp64(t_scrub *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->rate_connected 	= count[1];
	x->srate = samplerate;
    x->one_over_srate = 1./x->srate;
    x->srate_ms = .001 * x->srate;
    x->one_over_srate_ms = 1. / x->srate_ms;

    object_method(dsp64, gensym("dsp_add64"), x, scrub_perform64, 0, NULL);
}

void scrub_perform64(t_scrub *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double *in = (t_double *)(ins[0]);
	t_double rate = x->rate_connected? *(t_double *)(ins[1]) : x->rate;
	t_double *fcoeff = (t_double *)(ins[2]);
	t_double output, input, insave, outsave;
	t_double *out = (t_double *)(outs[0]);
	long n = sampleframes;
	
	if (x->x_obj.z_disabled) return;
	
	if(x->power) {
		while(n--) {
            
			input = *in++;
			
			//x->where += rate;
			x->where0 += rate;
			x->where1 += rate;
			x->where2 += rate;
            
			if(x->recordPoint == 0 && x->record) {
				x->whichBuf += 1;
				if(x->whichBuf >= 3) x->whichBuf = 0;
				
				x->recordlen = x->delaylenUpdate;
				if(x->recordenv > 0.5*x->recordlen) x->recordenv = 0.5*x->recordlen;
				x->recordenvInv = 1./x->recordenv;
				
				x->overlap = x->overlapUpdate;
				if(x->overlap > 0.5*x->recordlen) x->overlap = 0.5*x->recordlen;
	    		x->overlapInv = 1./x->overlap;
				
				//if(x->updatevals-- == 0) {
                x->delaylen = x->delaylenUpdate;
                /*
                 x->overlap = x->overlapUpdate;
                 if(x->overlap > 0.5*x->delaylen) x->overlap = 0.5*x->delaylen;
                 x->overlapInv = 1./x->overlap;
                 */
				//}
			}
			
			//calcCoeffs(x), put sample;
			if(x->whichBuf == 0) {
				x->coeff[0] = 0.;
				x->coeff[1] = decayEnvelope(x, 1.);
				x->coeff[2] = attackEnvelope(x, 1.);
				
				x->buf0[x->recordPoint] = recordEnvelope(x, input + *fcoeff++ * x->feedback);
				
				x->delaylen0 = x->delaylen;
				x->where0 = x->where2;
				
				if(x->record)
					output = x->coeff[1]*getSamp1(x) + x->coeff[2]*getSamp2(x);
				else
					output = getSamp1(x);
				
				insave = x->buf1[x->recordPoint];
				outsave = getSamp1(x);
				if (++x->recordPoint >= x->recordlen) x->recordPoint = 0;
			}
			else if(x->whichBuf == 1) {
				x->coeff[2] = decayEnvelope(x, 1.);
				x->coeff[1] = 0.;
				x->coeff[0] = attackEnvelope(x, 1.);
				
				x->buf1[x->recordPoint] = recordEnvelope(x, input + *fcoeff++ * x->feedback);
				
				x->delaylen1 = x->delaylen;
				x->where1 = x->where0;
				
				if(x->record)
					output = x->coeff[0]*getSamp0(x) + x->coeff[2]*getSamp2(x);
				else
					output = getSamp2(x);
                
				insave = x->buf2[x->recordPoint];
				outsave = getSamp2(x);
				if (++x->recordPoint >= x->recordlen) x->recordPoint = 0;
			}
			else if(x->whichBuf == 2) {
				x->coeff[0] = decayEnvelope(x, 1.);
				x->coeff[2] = 0.;
				x->coeff[1] = attackEnvelope(x, 1.);
                
				x->buf2[x->recordPoint] = recordEnvelope(x, input + *fcoeff++ * x->feedback);
				
				x->delaylen2 = x->delaylen;
				x->where2 = x->where1;
				
				if(x->record)
					output = x->coeff[0]*getSamp0(x) + x->coeff[1]*getSamp1(x);
				else
					output = getSamp0(x);
                
				insave = x->buf0[x->recordPoint];
				outsave = getSamp0(x);
				if (++x->recordPoint >= x->recordlen) x->recordPoint = 0;
                
			}
			else output = 0.;
		    
		    if(x->sync) 	x->feedback = insave; //feedback sample at record point
		    else 			x->feedback = outsave; //feedback current output sample
		    
		    *out++ = output;
		}
	}
	else while(n--) *out++ = 0.;
}


