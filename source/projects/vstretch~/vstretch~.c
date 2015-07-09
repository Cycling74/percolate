//expands or contracts a signal vector. good for transposing fft bins
//another PeRColate hack: dan trueman, 2002
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

#include "stk_c.h"
//#define TWOPI 6.283185307
#define RSRC_ID 12105
#define INT_LINEAR 0
#define INT_POLY 1
#define INT_SPLINE 2

typedef struct _vectorstretch
{
	//header
    t_pxobject x_obj;    
	
	float stretch;	//stretch factor for bins
	short interp_method; //0=linear (default), 1=polynomial, 2=spline (eventually)
	short polylen;
    
} t_vectorstretch;


//setup funcs
void *vectorstretch_new(double val);
void vectorstretch_assist(t_vectorstretch *x, void *b, long m, long a, char *s);

void vectorstretch_dsp64(t_vectorstretch *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void vectorstretch_perform64(t_vectorstretch *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void vectorstretch_setstretch(t_vectorstretch *x, t_symbol *s, long argc, t_atom *argv);
void vectorstretch_setlinear(t_vectorstretch *x, t_symbol *s, long argc, t_atom *argv);
void vectorstretch_setpoly(t_vectorstretch *x, t_symbol *s, long argc, t_atom *argv);
void vectorstretch_setpoly2(t_vectorstretch *x, t_symbol *s, long argc, t_atom *argv);


//t_symbol *ps_spvector;
void *vectorstretch_class;


//primary MSP funcs
void ext_main(void* p)
{
    t_class *c = class_new("vstretch~", (method)vectorstretch_new, (method)dsp_free, (long)sizeof(t_vectorstretch), 0L, A_GIMME, 0);
    
    class_addmethod(c, (method)vectorstretch_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)vectorstretch_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)vectorstretch_setstretch, "stretch", A_GIMME, 0);
    class_addmethod(c, (method)vectorstretch_setlinear, "linear", A_GIMME, 0);
    class_addmethod(c, (method)vectorstretch_setpoly, "poly", A_GIMME, 0);
    class_addmethod(c, (method)vectorstretch_setpoly, "poly2", A_GIMME, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    vectorstretch_class = c;

}

void vectorstretch_assist(t_vectorstretch *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET) {
        sprintf(s,"(signal) inputput");
    } else {
        sprintf(s,"(signal) output");
    }
}

void *vectorstretch_new(double initial_coeff)
{
	int i;

    t_vectorstretch *x = (t_vectorstretch *)object_alloc(vectorstretch_class);
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_vectorstretch);i++)  
                ((char *)x)[i]=0; 
	} 
	
    dsp_setup((t_pxobject *)x, 1);
	x->x_obj.z_misc = Z_NO_INPLACE;	
	outlet_new((t_object *)x, "signal");


	x->stretch = 1.;
	x->interp_method = 0;
	x->polylen = 3;
    
    return (x);
}


void vectorstretch_setstretch(t_vectorstretch *x, t_symbol *s, long argc, t_atom *argv)
{
    short i;
    float temp;
    for (i=0; i < argc; i++) {
        switch (argv[i].a_type) {
            case A_LONG:
                temp = (float)argv[i].a_w.w_long;
                if (temp < 0.) temp = 0.;
                //post("vectorstretch: setting stretch to: %f ", temp);
                x->stretch = temp;
                break;
            case A_FLOAT:
                temp = argv[i].a_w.w_float;
                if (temp < 0.) temp = 0.;
                //post("vectorstretch: setting stretch to: %f ", temp);
                x->stretch = temp;
                break;
        }
    }
}

void vectorstretch_setlinear(t_vectorstretch *x, t_symbol *s, long argc, t_atom *argv)
{
    x->interp_method = INT_LINEAR;
}

void vectorstretch_setpoly(t_vectorstretch *x, t_symbol *s, long argc, t_atom *argv)
{
    x->interp_method = INT_POLY;
    x->polylen = 3;
}

void vectorstretch_setpoly2(t_vectorstretch *x, t_symbol *s, long argc, t_atom *argv)
{
    x->interp_method = INT_POLY;
    x->polylen = 4;
}

void vectorstretch_dsp64(t_vectorstretch *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, vectorstretch_perform64, 0, NULL);
}

void vectorstretch_perform64(t_vectorstretch *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    
    long i;
    
    t_double *in = (t_double *)(ins[0]);
    t_double *out = (t_double *)(outs[0]);
    long n = sampleframes;
    
    double temp, temp2;
    long stretchStart, stretchEnd;
    double stretchOffset;
    
    if (x->x_obj.z_disabled)
        return;
    
    if (x->interp_method == INT_LINEAR) {
        for(i=0;i<n;i++) {
            temp = (double)i * (float)x->stretch; 			//float index for startpoint
            stretchStart = (long)temp;						//integer value of index
            stretchOffset = temp - (double)stretchStart;	//interpolation factor
            stretchEnd = stretchStart + 1;					//interpolation endpoint index
            
            //could add an if(stretchOffset == 0.) *out++ = in[stretchStart];
            //              else.... interpolation stuff.
            if (stretchStart >= n) temp = 0.;				//requests for frames above max are set to 0.
            else temp = in[stretchStart];
            
            if (stretchEnd >= n) temp2 = 0.;
            else temp2 = in[stretchEnd];
            
            *out++ = temp + stretchOffset * (temp2 - temp);
        }
    }
    
    else if(x->interp_method == INT_POLY) {
        for(i=0;i<n;i++) {
            temp = (double)i * (float)x->stretch; 					//what's the index we want
            *out++ = polyinterpolate_d(in, x->polylen, n, temp);		//2nd order poly interpolate
        }	
    }

}
