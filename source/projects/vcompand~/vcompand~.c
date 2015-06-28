//applies uniform linear compression/expansion on freq bins
//another PeRColate hack, inspired by some of paul koonce's work: dan trueman, 2002
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//#define TWOPI 6.283185307
#define RSRC_ID 12107

typedef struct _vectorcompand
{
	//header
    t_pxobject x_obj;    
	
	float compthresh, compamp;	//compression threshold and multiplier (1/ratio)
	float expthresh, expamp;	//expansion threshold and multiplier (1/ratio)
    
} t_vectorcompand;


//setup funcs
void *vectorcompand_new(double val);
void vectorcompand_assist(t_vectorcompand *x, void *b, long m, long a, char *s);

// dsp stuff
void vectorcompand_dsp64(t_vectorcompand *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void vectorcompand_perform64(t_vectorcompand *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void vectorcompand_setcompthresh(t_vectorcompand *x, t_symbol *s, long argc, t_atom *argv);
void vectorcompand_setcompratio(t_vectorcompand *x, t_symbol *s, long argc, t_atom *argv);
void vectorcompand_setexpthresh(t_vectorcompand *x, t_symbol *s, long argc, t_atom *argv);
void vectorcompand_setexpratio(t_vectorcompand *x, t_symbol *s, long argc, t_atom *argv);


//t_symbol *ps_spvector;
t_class *vectorcompand_class;


//primary MSP funcs
void ext_main(void* p)
{
    t_class *c = class_new("vcompand~", (method)vectorcompand_new, (method)dsp_free, (long)sizeof(t_vectorcompand), 0L, A_GIMME, 0);
    
    class_addmethod(c, (method)vectorcompand_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)vectorcompand_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)vectorcompand_setcompthresh, "compthresh", A_GIMME, 0);
    class_addmethod(c, (method)vectorcompand_setcompratio, "compratio", A_GIMME, 0);
    class_addmethod(c, (method)vectorcompand_setexpthresh, "expthresh", A_GIMME, 0);
    class_addmethod(c, (method)vectorcompand_setexpratio, "expratio", A_GIMME, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    vectorcompand_class = c;
}

void vectorcompand_assist(t_vectorcompand *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		sprintf(s,"(signal) input");
	} else {
		sprintf(s,"(signal) output");
    }
}

void *vectorcompand_new(double initial_coeff)
{
	int i;

    t_vectorcompand *x = (t_vectorcompand *)object_alloc(vectorcompand_class);
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_vectorcompand);i++)  
                ((char *)x)[i]=0; 
	} 
	
    dsp_setup((t_pxobject *)x, 1);
	x->x_obj.z_misc = Z_NO_INPLACE;	//shouldn't have to do this here....
	outlet_new((t_object *)x, "signal");


	x->compthresh = 1.;
	x->compamp = 1.; //no compression by default
	x->expthresh = 0.;
	x->compamp = 1.; //no expansion by default
    
    return (x);
}


void vectorcompand_setcompthresh(t_vectorcompand *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (float)argv[i].a_w.w_long;
    			//post("vectorcompand: setting comp threshold to: %f ", temp);
    			x->compthresh = temp;
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
				//post("vectorcompand: setting comp thresh to: %f ", temp);
				x->compthresh = temp;
				break;
		}
	}
}

void vectorcompand_setcompratio(t_vectorcompand *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (float)argv[i].a_w.w_long;
				if (temp == 0.) temp = 1.;
    			//post("vectorcompand: setting comp ratio to: %f ", temp);
    			x->compamp = 1./temp;
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
				if (temp == 0.) temp = 1.;
				//post("vectorcompand: setting comp ratio to: %f ", temp);
				x->compamp = 1./temp;
				break;
		}
	}
}

void vectorcompand_setexpthresh(t_vectorcompand *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (float)argv[i].a_w.w_long;
    			//post("vectorcompand: setting exp threshold to: %f ", temp);
    			x->expthresh = temp;
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
				//post("vectorcompand: setting exp thresh to: %f ", temp);
				x->expthresh = temp;
				break;
		}
	}
}

void vectorcompand_setexpratio(t_vectorcompand *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	float temp;
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp = (float)argv[i].a_w.w_long;
				if (temp == 0.) temp = 1.;
    			//post("vectorcompand: setting exp ratio to: %f ", temp);
    			x->expamp = 1./temp;
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
				if (temp == 0.) temp = 1.;
				//post("vectorcompand: setting exp ratio to: %f ", temp);
				x->expamp = 1./temp;
				break;
		}
	}
}


void vectorcompand_dsp64(t_vectorcompand *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, vectorcompand_perform64, 0, NULL);
}

void vectorcompand_perform64(t_vectorcompand *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	long i;
    
	t_double *in = (t_double *)(ins[0]);
	t_double *out = (t_double *)(outs[0]);
	long n = sampleframes;
	
	t_double temp;
	
	if (x->x_obj.z_disabled)
		return;
	
	while (n--) {
		temp = *in++;
		
		if(temp > x->compthresh) {
			temp = x->compthresh + (x->compamp*(temp - x->compthresh));
		} else if(temp < x->expthresh) {
			temp = x->expthresh - (x->expamp*(x->expthresh - temp));
			if (temp < 0.) temp = 0.;
		}
		
		*out++ = temp;
	}
}

