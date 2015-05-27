#include "ext.h"
#include "z_dsp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#define TWOPI 6.283185307
#define MAXBANKS 31
#define PEAKNOTCH 0
#define LOWSHELF 1
#define HIGHSHELF 2

void *gq_class;

typedef struct _gq
{
	//header
    t_pxobject x_obj;
    
    //user controlled vars
    float x_cf[MAXBANKS];			//centerfreq	
    float x_bw[MAXBANKS];			//bandwidth
    float x_bt[MAXBANKS]; 			//boost
    float x_rf[MAXBANKS]; 			//response freq	
    
    short x_type[MAXBANKS];			//what type of filter (peaknotch, lowshelf, highshelf)
    
    //signals connected? or controls...
    short x_cfconnected;
    short x_bwconnected;
    short x_btconnected;
    short x_rfconnected;
    
    //filter stuff
    float inputs[2][MAXBANKS], outputs[2][MAXBANKS];
    float inputsL[2][MAXBANKS],  inputsR[2][MAXBANKS];
    float outputsL[2][MAXBANKS], outputsR[2][MAXBANKS];    
    float zeroCoeffs[2][MAXBANKS], poleCoeffs[2][MAXBANKS];
    float x_gn[MAXBANKS];	//gain;
    
    long currentbank;
    long numbanks;
    
    //response stuff
    void *outfloat;
    void *outlist;
    
    short power;
    
    //stuff
    float srate, one_over_srate;
    float cf_save[MAXBANKS], bw_save[MAXBANKS], bt_save[MAXBANKS], rf_save[MAXBANKS];
} t_gq;

/****PROTOTYPES****/

//setup funcs
void *gq_new(double val);
void gq_dsp(t_gq *x, t_signal **sp, short *count);
void gq_float(t_gq *x, double f);
void gq_int(t_gq *x, int f);
void gq_assist(t_gq *x, void *b, long m, long a, char *s);
void gq_setbank(t_gq *x, Symbol *s, short argc, Atom *argv);
void gq_numbanks(t_gq *x, Symbol *s, short argc, Atom *argv);
void gq_clear(t_gq *x, Symbol *s, short argc, Atom *argv);
void gq_clearsettings(t_gq *x, Symbol *s, short argc, Atom *argv);
void gq_updatebank(t_gq *x, Symbol *s, short argc, Atom *argv);
t_int *gq_performMono(t_int *w);
t_int *gq_performStereo(t_int *w);
void updateResponse(t_gq *x, double f);

void gq_setpower(t_gq *x, Symbol *s, short argc, Atom *argv);

void gq_setpeaknotch(t_gq *x, double f);
void gq_sethighshelf(t_gq *x, double f);
void gq_setlowshelf(t_gq *x, double f);

//filter funcs
void setFreqBoostBandwidth(t_gq *x, float freq, float boost, float thisBandwidth);
float returnFreqResponse(t_gq *x, float freq);

void updateResponse(t_gq *x, double f)
{
	float response;
	response = returnFreqResponse(x, f);
	outlet_float(x->outfloat, response);
}

float returnFreqResponse(t_gq *x, float freq)
{
	float ReTop,  ReBottom,  ImTop,  ImBottom,  w,  response, temp;
	int i;
	    
    w = TWOPI*freq/x->srate;
    response = 1.;
    
    for(i=0;i<x->numbanks;i++) {
	    if(x->x_bt[i] == 1.) temp = 1.;
	    else {
		    ReTop = x->x_gn[i]*cos(2.*w) + x->zeroCoeffs[0][i]*cos(w) + x->zeroCoeffs[1][i];
		    ReBottom = cos(2.*w) - x->poleCoeffs[0][i]*cos(w) - x->poleCoeffs[1][i];
		    ImTop = x->x_gn[i]*sin(2.*w) + x->zeroCoeffs[0][i]*sin(w);
		    ImBottom = sin(2.*w) - x->poleCoeffs[0][i]*sin(w);

		    temp = pow((pow(ReTop,  2.) + pow(ImTop,  2.)) / (pow(ReBottom,  2.) + pow(ImBottom,  2.)),  0.5);
		}
		response *= temp;
	}
	
    return response;

}

void setFreqBoostBandwidth(t_gq *x, float freq, float boost, float thisBandwidth)
{
	float d, a_boost, a_cut, Vzero, true_bw, thisSR;
	
	thisSR = x->srate;
	
	x->x_cf[x->currentbank] = freq;
	x->x_bt[x->currentbank] = boost;
	x->x_bw[x->currentbank] = thisBandwidth;
	true_bw = freq * thisBandwidth;
	Vzero = boost - 1.;

	//PEAK/NOTCH CASE
    if (x->x_type[x->currentbank] == PEAKNOTCH) {   	
		a_boost = (tan(true_bw*TWOPI/(2.*thisSR)) - 1.) / (tan(true_bw*TWOPI/(2.*thisSR)) + 1.);
	    a_cut = (tan(true_bw*TWOPI/(2.*thisSR)) - boost) / (tan(true_bw*TWOPI/(2.*thisSR)) + boost);
	    d = -cos(freq*TWOPI/thisSR); 
	     
		/* cut */
		if(boost <= 1.0) {
	    	x->x_gn[x->currentbank] 			=  1.0 + (1.0 + a_cut)*Vzero/2.0;
	    	x->zeroCoeffs[0][x->currentbank] 	= d*(1 - a_cut);
	    	x->zeroCoeffs[1][x->currentbank] 	= (-a_cut - (1 + a_cut)*Vzero/2.0);

	    	x->poleCoeffs[0][x->currentbank]	= -d*(1.0 - a_cut);
	    	x->poleCoeffs[1][x->currentbank] 	= a_cut; 
		} 

		/* boost */     
		if(boost > 1.0) {
	    	x->x_gn[x->currentbank] 			= 1.0 + (1.0 + a_boost)*Vzero/2.0;
	    	x->zeroCoeffs[0][x->currentbank] 	= d*(1 - a_boost);
	    	x->zeroCoeffs[1][x->currentbank] 	= (-a_boost - (1 + a_boost)*Vzero/2.0);

	    	x->poleCoeffs[0][x->currentbank] 	= -d*(1.0 - a_boost);
	    	x->poleCoeffs[1][x->currentbank]	= a_boost; 
		}			
	}
	
	//LOW SHELF CASE
	 else if (x->x_type[x->currentbank] == LOWSHELF) {   	
		a_boost = (tan(freq*TWOPI/(2.*thisSR)) - 1.) / (tan(freq*TWOPI/(2.*thisSR)) + 1.);
	    a_cut = (tan(freq*TWOPI/(2.*thisSR)) - boost) / (tan(freq*TWOPI/(2.*thisSR)) + boost);
	     
		/* cut */
		if(boost <= 1.0) {
	    	x->x_gn[x->currentbank] 			= 1.0 + (1.0 + a_cut)*Vzero/2.0;
	    	x->zeroCoeffs[0][x->currentbank] 	= a_cut + (1 + a_cut)*Vzero/2.0;
	    	x->zeroCoeffs[1][x->currentbank] 	= 0.;

	    	x->poleCoeffs[0][x->currentbank]	= -a_cut;
	    	x->poleCoeffs[1][x->currentbank] 	= 0.; 
		} 

		/* boost */     
		if(boost > 1.0) {
	    	x->x_gn[x->currentbank] 			= 1.0 + (1.0 + a_boost)*Vzero/2.0;
	    	x->zeroCoeffs[0][x->currentbank] 	= a_boost + (1 + a_boost)*Vzero/2.0;
	    	x->zeroCoeffs[1][x->currentbank] 	= 0.;

	    	x->poleCoeffs[0][x->currentbank] 	= -a_boost;
	    	x->poleCoeffs[1][x->currentbank]	= 0.;
		}			
	}
	
	//HIGH SHELF CASE
	 else if (x->x_type[x->currentbank] == HIGHSHELF) {   	
		a_boost = (tan(freq*TWOPI/(2.*thisSR)) - 1.) / (tan(freq*TWOPI/(2.*thisSR)) + 1.);
	    a_cut = (boost*tan(freq*TWOPI/(2.*thisSR)) - 1.) / (boost*tan(freq*TWOPI/(2.*thisSR)) + 1.); 
	     
		/* cut */
		if(boost <= 1.0) {
	    	x->x_gn[x->currentbank] 			= 1.0 + (1.0 - a_cut)*Vzero/2.0;
	    	x->zeroCoeffs[0][x->currentbank] 	= a_cut + (a_cut - 1.)*Vzero/2.0;
	    	x->zeroCoeffs[1][x->currentbank] 	= 0.;

	    	x->poleCoeffs[0][x->currentbank]	= -a_cut;
	    	x->poleCoeffs[1][x->currentbank] 	= 0.; 
		} 

		/* boost */     
		if(boost > 1.0) {
	    	x->x_gn[x->currentbank] 			= 1.0 + (1.0 - a_boost)*Vzero/2.0;
	    	x->zeroCoeffs[0][x->currentbank] 	= a_boost + (a_boost - 1.)*Vzero/2.0;
	    	x->zeroCoeffs[1][x->currentbank] 	= 0.;

	    	x->poleCoeffs[0][x->currentbank] 	= -a_boost;
	    	x->poleCoeffs[1][x->currentbank]	= 0.; 
		}			
	}
}

//primary MSP funcs
void ext_main(void* p)
{
    setup((struct messlist **)&gq_class, (method)gq_new, (method)dsp_free, (short)sizeof(t_gq), 0L, A_DEFFLOAT, 0);
    addmess((method)gq_dsp, "dsp", A_CANT, 0);
    addmess((method)gq_assist,"assist",A_CANT,0);
    addmess((method)gq_setpower, "power", A_GIMME, 0);
    addmess((method)gq_setbank, "currentbank", A_GIMME, 0);
    addmess((method)gq_numbanks, "numbanks", A_GIMME, 0);
    addmess((method)gq_clear, "clear", A_GIMME, 0);
    addmess((method)gq_clearsettings, "clearsettings", A_GIMME, 0);
    addmess((method)gq_updatebank, "setbank", A_GIMME, 0);
    addmess((method)gq_setpeaknotch, "peaknotch", A_GIMME, 0);
    addmess((method)gq_sethighshelf, "highshelf", A_GIMME, 0);
    addmess((method)gq_setlowshelf, "lowshelf", A_GIMME, 0);
    addfloat((method)gq_float);
    addint((method)gq_int);
    dsp_initclass();
    rescopy('STR#',9800);
}

void gq_assist(t_gq *x, void *b, long m, long a, char *s)
{
	assist_string(9800,m,a,1,7,s);
}


void gq_int(t_gq *x, int f)
{
	gq_float(x, (double)f);
}

void gq_setpower(t_gq *x, Symbol *s, short argc, Atom *argv)
{
	short i;
	float temp;
	long temp2; 
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp2 = argv[i].a_w.w_long;
				//probably should comment these out when the object is debugged.
				x->power = temp2;
    			post("gQ: power = %d", x->power);
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
    			//post("template~: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
}


void gq_setbank(t_gq *x, Symbol *s, short argc, Atom *argv)
{
	short i;
	int temp;
	float banksettings[4];
	Atom outlist[4];
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = argv[i].a_w.w_long;
				if(temp < 0) temp = 0;
				if(temp > x->numbanks) temp = x->numbanks;
				x->currentbank = temp;
    			//post("gq: using bank %d ", x->currentbank);
				break;
			case A_FLOAT:
				temp = (int)argv[i].a_w.w_float;
				if(temp < 0) temp = 0;
				if(temp > x->numbanks) temp = x->numbanks;
				x->currentbank = temp;
    			//post("gq: using bank %d ", x->currentbank);
				break;
		}
	
	//send the settings for the current bank out....
	banksettings[0] = x->x_cf[x->currentbank];			//centerfreq	
	banksettings[1] = x->x_bw[x->currentbank];			//bandwidth
	banksettings[2] = x->x_bt[x->currentbank];			//boost
	banksettings[3] = x->x_type[x->currentbank];		//filter type
	for(i=0;i<4;i++) {
		atom_setfloat(outlist+i, banksettings[i]);
	}
	outlet_list(x->outlist, 0L, 4, outlist);
	}
}

void gq_numbanks(t_gq *x, Symbol *s, short argc, Atom *argv)
{
	short i;
	int temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = argv[i].a_w.w_long;
				if(temp < 1) temp = 1;
				if(temp > MAXBANKS) temp = MAXBANKS;
				x->numbanks = temp;
    			//post("gq: using bank %d ", x->currentbank);
				break;
			case A_FLOAT:
				temp = (int)argv[i].a_w.w_float;
				if(temp < 1) temp = 1;
				if(temp >MAXBANKS) temp = MAXBANKS;
				x->numbanks = temp;
    			//post("gq: using bank %d ", x->currentbank);
				break;
		}

	}
}

void gq_updatebank(t_gq *x, Symbol *s, short argc, Atom *argv)
{
	long bank, banksave, type;
	float cf, bw, mult;
	
	if(argc<4) post("gQ: need 'bank cf bw mult type' to setbank");
	
	switch (argv[0].a_type) {
		case A_LONG:
			bank = argv[0].a_w.w_long; 
			break;
		case A_FLOAT:
			bank = (long)argv[0].a_w.w_float;
			break;
	}
	switch (argv[1].a_type) {
		case A_LONG:
			cf = (float)argv[1].a_w.w_long; 
			break;
		case A_FLOAT:
			cf = argv[1].a_w.w_float;
			break;
	}
	switch (argv[2].a_type) {
		case A_LONG:
			bw = (float)argv[2].a_w.w_long; 
			break;
		case A_FLOAT:
			bw = argv[2].a_w.w_float;
			break;
	}
	switch (argv[3].a_type) {
		case A_LONG:
			mult = (float)argv[3].a_w.w_long; 
			break;
		case A_FLOAT:
			mult = argv[3].a_w.w_float;
			break;
	}
	switch (argv[4].a_type) {
		case A_LONG:
			type = argv[4].a_w.w_long; 
			break;
		case A_FLOAT:
			type = (long)argv[4].a_w.w_float;
			break;
	}

	if (bank < MAXBANKS) {
		banksave = x->currentbank;
		x->currentbank = bank;
		if (type > 2 || type < 0) 
			post("gQ: invalid filter type, ignoring");
		else
			x->x_type[x->currentbank] = type;
		setFreqBoostBandwidth(x, cf, mult, bw);
		x->currentbank = banksave;
		
	} else
		post("gQ: not a valid bank number");
	
}

void gq_clear(t_gq *x, Symbol *s, short argc, Atom *argv)
{
	int i;
	post("gQ: clearing delay lines");
	
	for(i=0;i<MAXBANKS;i++) {
	    
	    x->inputsL[0][i] = 0.;
		x->inputsL[1][i] = 0.;
		x->inputsR[0][i] = 0.;
		x->inputsR[1][i] = 0.;
		
		x->inputs[0][i] = 0.;
		x->inputs[1][i] = 0.;

	}
}

void gq_clearsettings(t_gq *x, Symbol *s, short argc, Atom *argv)
{
	int i;
	post("gQ: clearing settings and delay lines");
	
	for(i=0;i<MAXBANKS;i++) {
	    x->x_cf[i] = 440.;			//centerfreq	
	    x->x_bw[i] = 0.1;			//bandwidth
	    x->x_bt[i] = 1.;			//boost
	    x->x_rf[i] = 440.; 			//response freq	
	    
	    x->cf_save[i] = 232.;
	    x->bw_save[i] = .13;
	    x->bt_save[i] = 1.;
	    x->rf_save[i] = 223.;
	    
	    x->inputsL[0][i] = 0.;
		x->inputsL[1][i] = 0.;
		x->inputsR[0][i] = 0.;
		x->inputsR[1][i] = 0.;
		
		x->inputs[0][i] = 0.;
		x->inputs[1][i] = 0.;
		
		x->poleCoeffs[0][i] = 0.;
		x->poleCoeffs[1][i] = 0.;
		x->zeroCoeffs[0][i] = 0.;
		x->zeroCoeffs[1][i] = 0.;
		
		x->x_gn[i] = 1.;
		
		setFreqBoostBandwidth(x, x->x_cf[i], x->x_bt[i], x->x_bw[i]);
	}
}

void gq_setpeaknotch(t_gq *x, double f)
{
	x->x_type[x->currentbank] = PEAKNOTCH;
	setFreqBoostBandwidth(x, x->x_cf[x->currentbank], x->x_bt[x->currentbank], x->x_bw[x->currentbank]);
}

void gq_sethighshelf(t_gq *x, double f)
{
	x->x_type[x->currentbank] = HIGHSHELF;
	setFreqBoostBandwidth(x, x->x_cf[x->currentbank], x->x_bt[x->currentbank], x->x_bw[x->currentbank]);
}

void gq_setlowshelf(t_gq *x, double f)
{
	x->x_type[x->currentbank] = LOWSHELF;
	setFreqBoostBandwidth(x, x->x_cf[x->currentbank], x->x_bt[x->currentbank], x->x_bw[x->currentbank]);
}

void gq_float(t_gq *x, double f)
{
	if (x->x_obj.z_in == 2) {
		x->x_cf[x->currentbank] = f;
	} else if (x->x_obj.z_in == 3) {
		x->x_bw[x->currentbank] = f;
	} else if (x->x_obj.z_in == 4) {
		x->x_bt[x->currentbank] = f;
	} else if (x->x_obj.z_in == 5) {
		x->x_rf[x->currentbank] = f;
		updateResponse(x, f);
	} 
}

void *gq_new(double initial_coeff)
{
	int i;

    t_gq *x = (t_gq *)newobject(gq_class);
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_gq);i++)  
                ((char *)x)[i]=0; 
	} 
    dsp_setup((t_pxobject *)x,6);
    x->outfloat = floatout((t_object *)x);
    x->outlist = listout((t_object *)x);
    outlet_new((t_object *)x, "signal");
    outlet_new((t_object *)x, "signal");
   
    x->srate = sys_getsr();
    x->one_over_srate = 1./x->srate;
    
    x->numbanks = (long)initial_coeff;
    //post("gQ: initial coeff =  %f banks", initial_coeff);
    if(x->numbanks < 1) x->numbanks = 1;
    post("gQ: using %d banks", (int)x->numbanks);
    x->currentbank = 0;
    
    for(i=0;i<MAXBANKS;i++) {
	    x->x_cf[i] = 440.;			//centerfreq	
	    x->x_bw[i] = 0.1;			//bandwidth
	    x->x_bt[i] = 1.;			//boost
	    x->x_rf[i] = 440.; 			//response freq	
	    x->x_type[i] = PEAKNOTCH;	//make them all peaknotch filters by default
	    
	    x->cf_save[i] = 232.;
	    x->bw_save[i] = .13;
	    x->bt_save[i] = 1.;
	    x->rf_save[i] = 223.;
	    
	    x->inputsL[0][i] = 0.;
		x->inputsL[1][i] = 0.;
		x->inputsR[0][i] = 0.;
		x->inputsR[1][i] = 0.;
		
		x->inputs[0][i] = 0.;
		x->inputs[1][i] = 0.;
		
		x->poleCoeffs[0][i] = 0.;
		x->poleCoeffs[1][i] = 0.;
		x->zeroCoeffs[0][i] = 0.;
		x->zeroCoeffs[1][i] = 0.;
		
		x->x_gn[i] = 1.;
		
		setFreqBoostBandwidth(x, x->x_cf[i], x->x_bt[i], x->x_bw[i]);
	}
    
    x->power = 1;

    return (x);
}


void gq_dsp(t_gq *x, t_signal **sp, short *count)
{
	x->x_cfconnected = count[2];
	x->x_bwconnected = count[3];
	x->x_btconnected = count[4];
	x->x_rfconnected = count[5];
	
	x->srate = sp[0]->s_sr;
    x->one_over_srate = 1./x->srate;

	if(count[1])						//inL			inR			cf				bw			  boost			rf			  outL			outR			
		dsp_add(gq_performStereo, 10, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec, sp[0]->s_n);	
	else 								//in		   cf			bw			boost			rf			out				
		dsp_add(gq_performMono, 8, x, sp[0]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[0]->s_n);	
		//dsp_add(gq_performStereo, 10, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec, sp[7]->s_vec, sp[0]->s_n);	
}


t_int *gq_performMono(t_int *w)
{
	t_gq *x = (t_gq *)(w[1]);
	
	float *in = (float *)(w[2]);

	float cf = x->x_cfconnected? *(float *)(w[3]) : x->x_cf[x->currentbank];
	float bw = x->x_bwconnected? *(float *)(w[4]) : x->x_bw[x->currentbank];
	float bt = x->x_btconnected? *(float *)(w[5]) : x->x_bt[x->currentbank];
	float rf = x->x_rfconnected? *(float *)(w[6]) : x->x_rf[x->currentbank];
	
	float *out = (float *)(w[7]);

	long n = w[8];
	
	float temp, outputs, outputsSave;
	float gain[MAXBANKS];
	float inputs[2][MAXBANKS];
	float poleCoeffs[2][MAXBANKS];
	float zeroCoeffs[2][MAXBANKS];
	
	float response;
	int i;
	long numbanks = x->numbanks;
	
	if (x->x_obj.z_disabled || (x->power == 0)) goto out;
	
	for(i=0;i<numbanks;i++) {
		inputs[0][i] 	= x->inputs[0][i];
		inputs[1][i] 	= x->inputs[1][i];
		gain[i] 		= x->x_gn[i];
		
		poleCoeffs[0][i] = x->poleCoeffs[0][i];
		poleCoeffs[1][i] = x->poleCoeffs[1][i];
		zeroCoeffs[0][i] = x->zeroCoeffs[0][i];
		zeroCoeffs[1][i] = x->zeroCoeffs[1][i];
	}
	
	if(x->cf_save[x->currentbank] != cf) {
		x->cf_save[x->currentbank] = cf;
		setFreqBoostBandwidth(x, cf, bt, bw);
	}
	
	if(x->bw_save[x->currentbank] != bw) {
		x->bw_save[x->currentbank] = bw;
		setFreqBoostBandwidth(x, cf, bt, bw);
	}
	
	if(x->bt_save[x->currentbank] != bt) {
		x->bt_save[x->currentbank] = bt;
		setFreqBoostBandwidth(x, cf, bt, bw);
	}

	while(n--) {
		
	    outputsSave = *in++; 
		    
		//run the filters in series
		for(i=0;i<numbanks;i++) { 
		
			temp = outputsSave;			//feed output of last filter in to next filter     
			            
																/* Here's the math for the  */
		    temp += inputs[0][i] * poleCoeffs[0][i];          	/* version which implements */
		    temp += inputs[1][i] * poleCoeffs[1][i];          	/* only 2 state variables.  */
		    
		    outputs = gain[i] * temp;                   		/* This form takes          */
		    outputs += (inputs[0][i] * zeroCoeffs[0][i]); 		/* 5 multiplies and         */
		    outputs += (inputs[1][i] * zeroCoeffs[1][i]);  		/* 4 adds                   */
		    inputs[1][i] = inputs[0][i];                      	/* and 3 moves              */
		    inputs[0][i] = temp;                           		/* too!!!                   */
		    
		    outputsSave = outputs;  	//filters are in series
		    
		}

	    *out++ = outputsSave;
	}
	for(i=0;i<numbanks;i++) {
		x->inputs[0][i] = inputs[0][i];
		x->inputs[1][i] = inputs[1][i];
	}
out:
	return w + 9;
}	

t_int *gq_performStereo(t_int *w)
{
	t_gq *x = (t_gq *)(w[1]);
	
	float *inL = (float *)(w[2]);
	float *inR = (float *)(w[3]);

	float cf = x->x_cfconnected? *(float *)(w[4]) : x->x_cf[x->currentbank];
	float bw = x->x_bwconnected? *(float *)(w[5]) : x->x_bw[x->currentbank];
	float bt = x->x_btconnected? *(float *)(w[6]) : x->x_bt[x->currentbank];
	float rf = x->x_rfconnected? *(float *)(w[7]) : x->x_rf[x->currentbank];
	
	float *outL = (float *)(w[8]); 
	float *outR = (float *)(w[9]); 
	
	float response;
	
	long n = w[10];
	int i;
	int numbanks = x->numbanks;
	
	float temp, outputs, outputsLsave, outputsRsave;
	float gain[MAXBANKS];
	float inputsL[2][MAXBANKS], inputsR[2][MAXBANKS];
	float poleCoeffs[2][MAXBANKS];
	float zeroCoeffs[2][MAXBANKS];
	
	if (x->x_obj.z_disabled || (x->power == 0)) goto out2;
	
	for (i=0;i<numbanks;i++){
		inputsL[0][i] = x->inputsL[0][i];
		inputsL[1][i] = x->inputsL[1][i];
		inputsR[0][i] = x->inputsR[0][i];
		inputsR[1][i] = x->inputsR[1][i];
		
		poleCoeffs[0][i] = x->poleCoeffs[0][i];
		poleCoeffs[1][i] = x->poleCoeffs[1][i];
		zeroCoeffs[0][i] = x->zeroCoeffs[0][i];
		zeroCoeffs[1][i] = x->zeroCoeffs[1][i];
		gain[i] = x->x_gn[i];
	
	}
		
	if(x->cf_save[x->currentbank] != cf) {
		x->cf_save[x->currentbank] = cf;
		setFreqBoostBandwidth(x, cf, bt, bw);
	}
	
	if(x->bw_save[x->currentbank] != bw) {
		x->bw_save[x->currentbank] = bw;
		setFreqBoostBandwidth(x, cf, bt, bw);
	}
	
	if(x->bt_save[x->currentbank] != bt) {
		x->bt_save[x->currentbank] = bt;
		setFreqBoostBandwidth(x, cf, bt, bw);
	}

	while(n--) {
			    
	    //left channel
	    outputsLsave = *inL++;                       			  
	    for(i=0;i<numbanks;i++) {
	    
	    	temp = outputsLsave;
	    														/* Here's the math for the  */
		    temp += inputsL[0][i] * poleCoeffs[0][i];         	/* version which implements */
		    temp += inputsL[1][i] * poleCoeffs[1][i];         	/* only 2 state variables.  */
		    
		    outputs = gain[i] * temp;                   		/* This form takes          */
		    outputs += (inputsL[0][i] * zeroCoeffs[0][i]);  	/* 5 multiplies and         */
		    outputs += (inputsL[1][i] * zeroCoeffs[1][i]);  	/* 4 adds                   */
		    inputsL[1][i] = inputsL[0][i];                      /* and 3 moves              */
		    inputsL[0][i] = temp;                           	/* too!!!                   */
		    
		    outputsLsave = outputs;
	    }
	    
	    //right channel
        outputsRsave = *inR++;          											
	    for(i=0;i<numbanks;i++) {
	    
	    	temp = outputsRsave;
	    														/* Here's the math for the  */
		    temp += inputsR[0][i] * poleCoeffs[0][i];         	/* version which implements */
		    temp += inputsR[1][i] * poleCoeffs[1][i];         	/* only 2 state variables.  */
		    
		    outputs = gain[i] * temp;                   		/* This form takes          */
		    outputs += (inputsR[0][i] * zeroCoeffs[0][i]);  	/* 5 multiplies and         */
		    outputs += (inputsR[1][i] * zeroCoeffs[1][i]);  	/* 4 adds                   */
		    inputsR[1][i] = inputsR[0][i];                      /* and 3 moves              */
		    inputsR[0][i] = temp;                           	/* too!!!                   */
		    
		    outputsRsave = outputs;
		}

	    //outputs
	    *outL++ = outputsLsave;
	    *outR++ = outputsRsave;
	}

	for(i=0;i<numbanks;i++){
		x->inputsL[0][i] = inputsL[0][i];
		x->inputsL[1][i] = inputsL[1][i];
		x->inputsR[0][i] = inputsR[0][i];
		x->inputsR[1][i] = inputsR[1][i];
	}
out2:
	return w + 11;
}	

