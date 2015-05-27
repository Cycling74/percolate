//applies uniform linear compression/expansion on freq bins
//another PeRColate hack, inspired by some of paul koonce's work: dan trueman, 2002

#include "ext.h"
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
void vectorcompand_dsp(t_vectorcompand *x, t_signal **sp, short *count); 
t_int *vectorcompand_perform(t_int *w);
void vectorcompand_assist(t_vectorcompand *x, void *b, long m, long a, char *s);
void vectorcompand_setpower(t_vectorcompand *x, Symbol *s, short argc, Atom *argv);

//t_symbol *ps_spvector;
void *vectorcompand_class;


//primary MSP funcs
void ext_main(void* p)
{
    setup((struct messlist **)&vectorcompand_class, (method)vectorcompand_new, (method)dsp_free, (short)sizeof(t_vectorcompand), 0L, A_GIMME, 0);
    addmess((method)vectorcompand_dsp, "dsp", A_CANT, 0);
    addmess((method)vectorcompand_assist,"assist",A_CANT,0);
    addmess((method)vectorcompand_setpower, "power", A_GIMME, 0);
    
    dsp_initclass();
 
    rescopy('STR#',RSRC_ID);
}

void vectorcompand_assist(t_vectorcompand *x, void *b, long m, long a, char *s)
{
	assist_string(RSRC_ID,m,a,1,6,s);
}

//what to do when we get the message "mymessage" and a value (or list of values)
void vectorcompand_setpower(t_vectorcompand *x, Symbol *s, short argc, Atom *argv)
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

    t_vectorcompand *x = (t_vectorcompand *)newobject(vectorcompand_class);
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


void vectorcompand_dsp(t_vectorcompand *x, t_signal **sp, short *count)
{
		dsp_add(vectorcompand_perform, 8, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[0]->s_n);	
}

t_int *vectorcompand_perform(t_int *w)
{
	t_vectorcompand *x = (t_vectorcompand *)(w[1]);

	long i;

	float *in 			= (float *)(w[2]);
	float *compthresh 	= (float *)(w[3]);
	float *compamp	 	= (float *)(w[4]);
	float *expthresh 	= (float *)(w[5]);
	float *expamp	 	= (float *)(w[6]);
	float *out 			= (float *)(w[7]);
	long n = w[8];
	
	float temp, ct, ca, et, ea;
	
	if (x->x_obj.z_disabled || !x->power)
		goto out;
	
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

out:
	return w + 9;
}	

