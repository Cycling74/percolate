//applies uniform linear compression/expansion on freq bins
//another PeRColate hack, inspired by some of paul koonce's work: dan trueman, 2002

#include "ext.h"
#include "z_dsp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
void vectorcompand_dsp(t_vectorcompand *x, t_signal **sp, short *count); 
t_int *vectorcompand_perform(t_int *w);
void vectorcompand_assist(t_vectorcompand *x, void *b, long m, long a, char *s);

void vectorcompand_setcompthresh(t_vectorcompand *x, Symbol *s, short argc, Atom *argv);
void vectorcompand_setcompratio(t_vectorcompand *x, Symbol *s, short argc, Atom *argv);
void vectorcompand_setexpthresh(t_vectorcompand *x, Symbol *s, short argc, Atom *argv);
void vectorcompand_setexpratio(t_vectorcompand *x, Symbol *s, short argc, Atom *argv);


//t_symbol *ps_spvector;
void *vectorcompand_class;


//primary MSP funcs
void ext_main(void* p)
{
    setup((struct messlist **)&vectorcompand_class, (method)vectorcompand_new, (method)dsp_free, (short)sizeof(t_vectorcompand), 0L, A_GIMME, 0);
    addmess((method)vectorcompand_dsp, "dsp", A_CANT, 0);
    addmess((method)vectorcompand_assist,"assist",A_CANT,0);
    addmess((method)vectorcompand_setcompthresh, "compthresh", A_GIMME, 0);
    addmess((method)vectorcompand_setcompratio, "compratio", A_GIMME, 0);
    addmess((method)vectorcompand_setexpthresh, "expthresh", A_GIMME, 0);
    addmess((method)vectorcompand_setexpratio, "expratio", A_GIMME, 0);
    dsp_initclass();
 
    rescopy('STR#',RSRC_ID);
}

void vectorcompand_assist(t_vectorcompand *x, void *b, long m, long a, char *s)
{
	assist_string(RSRC_ID,m,a,1,2,s);
}

void *vectorcompand_new(double initial_coeff)
{
	int i;

    t_vectorcompand *x = (t_vectorcompand *)newobject(vectorcompand_class);
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


void vectorcompand_dsp(t_vectorcompand *x, t_signal **sp, short *count)
{
		dsp_add(vectorcompand_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);	
}

t_int *vectorcompand_perform(t_int *w)
{
	t_vectorcompand *x = (t_vectorcompand *)(w[1]);

	long i;

	float *in = (float *)(w[2]);
	float *out = (float *)(w[3]);
	long n = w[4];
	
	float temp;
	
	if (x->x_obj.z_disabled)
		goto out;
	
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

out:
	return w + 5;
}	

void vectorcompand_setcompthresh(t_vectorcompand *x, Symbol *s, short argc, Atom *argv)
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

void vectorcompand_setcompratio(t_vectorcompand *x, Symbol *s, short argc, Atom *argv)
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

void vectorcompand_setexpthresh(t_vectorcompand *x, Symbol *s, short argc, Atom *argv)
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

void vectorcompand_setexpratio(t_vectorcompand *x, Symbol *s, short argc, Atom *argv)
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