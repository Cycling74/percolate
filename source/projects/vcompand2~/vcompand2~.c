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
#include <math.h>
//#define TWOPI 6.283185307
#define RSRC_ID 12108

typedef struct _vectorcompand
{
	//header
    t_pxobject x_obj;
    short power;

} t_vectorcompand;


//setup funcs
void *vectorcompand_new(double val);
void vectorcompand_assist(t_vectorcompand *x, void *b, long m, long a, char *s);
void vectorcompand_setpower(t_vectorcompand *x, t_symbol *s, long argc, t_atom *argv);

// dsp stuff
void vectorcompand_dsp64(t_vectorcompand *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void vectorcompand_perform64(t_vectorcompand *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

//t_symbol *ps_spvector;
t_class *vectorcompand_class;


//primary MSP funcs
void ext_main(void* p)
{
    t_class *c = class_new("vcompand2~", (method)vectorcompand_new, (method)dsp_free, (long)sizeof(t_vectorcompand), 0L, A_GIMME, 0);
    
    class_addmethod(c, (method)vectorcompand_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)vectorcompand_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)vectorcompand_setpower, "power", A_GIMME, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    vectorcompand_class = c;
}

void vectorcompand_assist(t_vectorcompand *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
            case 0:
                sprintf(s,"(signal/float) signal");
                break;
            case 1:
                sprintf(s,"(signal/float) comp threshold");
                break;
            case 2:
                sprintf(s,"(signal/float) comp amplitude");
                break;
            case 3:
                sprintf(s,"(signal/float) exp threshold");
                break;
            case 4:
                sprintf(s,"(signal/float) exp amplitude");
                break;
        }
	} else {
		sprintf(s,"(signal) output");
    }
}

//what to do when we get the message "mymessage" and a value (or list of values)
void vectorcompand_setpower(t_vectorcompand *x, t_symbol *s, long argc, t_atom *argv)
{
	short i;
	t_double temp;
	long temp2; 
	for (i=0; i < argc; i++) {
		switch (argv[i].a_type) {
			case A_LONG:
				temp2 = argv[i].a_w.w_long;
				//probably should comment these out when the object is debugged.
				x->power = temp2;
    			post("vcompand2~: power = %d", x->power);
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
    			//post("template~: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
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
	
    dsp_setup((t_pxobject *)x, 5);
	x->x_obj.z_misc = Z_NO_INPLACE;	//shouldn't need to do this
	outlet_new((t_object *)x, "signal");
    
    x->power = 1;
    
    return (x);
}


void vectorcompand_dsp64(t_vectorcompand *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, vectorcompand_perform64, 0, NULL);
}

void vectorcompand_perform64(t_vectorcompand *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double *in 			= (t_double *)(ins[0]);
	t_double *compthresh 	= (t_double *)(ins[1]);
	t_double *compamp	 	= (t_double *)(ins[2]);
	t_double *expthresh 	= (t_double *)(ins[3]);
	t_double *expamp	 	= (t_double *)(ins[4]);
	t_double *out 			= (t_double *)(outs[0]);
	long n = sampleframes;
	
	t_double temp, ct, ca, et, ea;
	
	if (x->x_obj.z_disabled || !x->power)
		return;
	
	while (n--) {
		temp = *in++;
		ct = *compthresh++;
		ca = *compamp++;
		et = *expthresh++;
		ea = *expamp++;
		
		if(temp > ct) {
			temp = ct + (ca*(temp - ct));
		} else if(temp < et) {
			temp = et - (ea*(et - temp));
			if (temp < 0.) temp = 0.;
		}
		
		*out++ = temp;
	}

}
