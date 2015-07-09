//warps the left signal vector input by the right signal vector input.
//	each value in the right vector is interpreted as a multiply value
//	for remapping the bin in the left signal vector. like vstretch, 
//	except the stretch factor varies with each bin.
//	stretch is still used as an overall offset for each bin, so you can
//  stretch a particular warping shape. nutty.

//you can, of course, run this in the time domain; there is nothing about 
//it that *requires* that you run itt in pfft~. sounds kinda funny.

//another PeRColate hack: dan trueman, 2002
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------


#include "stk_c.h"
//#define TWOPI 6.283185307
#define RSRC_ID 12106
#define INT_LINEAR 0
#define INT_POLY 1
#define INT_SPLINE 2

typedef struct _vectorwarp
{
	//header
    t_pxobject x_obj;    
	
	float stretch;	//stretch factor for bins
	short interp_method; //0=linear (default), 1=polynomial, 2=spline (eventually)
	short polylen;
	short power;
    
} t_vectorwarp;


//setup funcs
void *vectorwarp_new(t_double val);
void vectorwarp_assist(t_vectorwarp *x, void *b, long m, long a, char *s);

// dsp stuff
void vectorwarp_dsp64(t_vectorwarp *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void vectorwarp_perform64(t_vectorwarp *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void vectorwarp_setstretch(t_vectorwarp *x, t_symbol *s, long argc, t_atom *argv);
void vectorwarp_setlinear(t_vectorwarp *x, t_symbol *s, long argc, t_atom *argv);
void vectorwarp_setpoly(t_vectorwarp *x, t_symbol *s, long argc, t_atom *argv);
void vectorwarp_setpoly2(t_vectorwarp *x, t_symbol *s, long argc, t_atom *argv);
void vectorwarp_setpower(t_vectorwarp *x, t_symbol *s, long argc, t_atom *argv);

//t_symbol *ps_spvector;
t_class *vectorwarp_class;


//primary MSP funcs
void ext_main(void* p)
{
    t_class *c = class_new("vwarp~", (method)vectorwarp_new, (method)dsp_free, (long)sizeof(t_vectorwarp), 0L, A_DEFFLOAT, 0);
    
    class_addmethod(c, (method)vectorwarp_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)vectorwarp_dsp64, "dsp64", A_CANT, 0);
    
    class_addmethod(c, (method)vectorwarp_setpower, "power", A_GIMME, 0);
    class_addmethod(c, (method)vectorwarp_setstretch, "stretch", A_GIMME, 0);
    class_addmethod(c, (method)vectorwarp_setlinear, "linear", A_GIMME, 0);
    class_addmethod(c, (method)vectorwarp_setpoly, "poly", A_GIMME, 0);
    class_addmethod(c, (method)vectorwarp_setpoly, "poly2", A_GIMME, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    vectorwarp_class = c;
}

//what to do when we get the message "mymessage" and a value (or list of values)
void vectorwarp_setpower(t_vectorwarp *x, t_symbol *s, long argc, t_atom *argv)
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
    			post("vwarp~: power = %d", x->power);
				break;
			case A_FLOAT:
				temp = argv[i].a_w.w_float;
    			//post("template~: received argument %d of mymessage with value %f", i+1, temp);
				break;
		}
	}
}

void vectorwarp_assist(t_vectorwarp *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET) {
        sprintf(s,"(signal/float) input");
    } else {
        sprintf(s,"(signal) output");
    }
}

void *vectorwarp_new(t_double initial_coeff)
{
	int i;

    t_vectorwarp *x = (t_vectorwarp *)object_alloc(vectorwarp_class);
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_vectorwarp);i++)  
                ((char *)x)[i]=0; 
	} 
	
    dsp_setup((t_pxobject *)x, 2);
	x->x_obj.z_misc = Z_NO_INPLACE;	//need this here!
									//though the effect is quite cool without it.....
	outlet_new((t_object *)x, "signal");


	x->stretch = 1.;
	x->interp_method = 0;
	x->polylen = 3;
    x->power = 1;
    //post("vwarp: power = %d", x->power);
    
    return (x);
}

void vectorwarp_setstretch(t_vectorwarp *x, t_symbol *s, long argc, t_atom *argv)
{
    short i;
    float temp;
    for (i=0; i < argc; i++) {
        switch (argv[i].a_type) {
            case A_LONG:
                temp = (float)argv[i].a_w.w_long;
                if (temp < 0.) temp = 0.;
                //post("vwarp: setting stretch to: %f ", temp);
                x->stretch = temp;
                break;
            case A_FLOAT:
                temp = argv[i].a_w.w_float;
                if (temp < 0.) temp = 0.;
                //post("vwarp: setting stretch to: %f ", temp);
                x->stretch = temp;
                break;
        }
    }
}

void vectorwarp_setlinear(t_vectorwarp *x, t_symbol *s, long argc, t_atom *argv)
{
    x->interp_method = INT_LINEAR;
}

void vectorwarp_setpoly(t_vectorwarp *x, t_symbol *s, long argc, t_atom *argv)
{
    x->interp_method = INT_POLY;
    x->polylen = 3;
}

void vectorwarp_setpoly2(t_vectorwarp *x, t_symbol *s, long argc, t_atom *argv)
{
    x->interp_method = INT_POLY;
    x->polylen = 4;
}

void vectorwarp_dsp64(t_vectorwarp *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, vectorwarp_perform64, 0, NULL);
}

void vectorwarp_perform64(t_vectorwarp *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    long i;
    
    t_double *in 			= (t_double *)(ins[0]);
    t_double *warptable 	= (t_double *)(ins[1]);
    t_double *out 			= (t_double *)(outs[0]);
    long n                  = sampleframes;
    
    double temp, temp2;
    long warpStart, warpEnd;
    double warpOffset;
    
    if (x->x_obj.z_disabled) return;
    if (!x->power) return;
    
    if (x->interp_method == INT_LINEAR) {
        for(i=0;i<n;i++) {
            temp = (double)i * (float)x->stretch * warptable[i]; 		//float index for startpoint
            warpStart = (long)temp;										//integer value of index
            warpOffset = temp - (double)warpStart;						//interpolation factor
            warpEnd = warpStart + 1;									//interpolation endpoint index
            
            if (warpStart >= n) temp = 0.;								//requests for frames above max are set to 0.
            else temp = in[warpStart];
            
            if (warpEnd >= n) temp2 = 0.;
            else temp2 = in[warpEnd];
            
            *out++ = temp + warpOffset * (temp2 - temp);
        }
    }
    
    else if(x->interp_method == INT_POLY) {
        for(i=0;i<n;i++) {
            temp = (double)i*(float)x->stretch * warptable[i]; 	//what's the index we want
            *out++ = polyinterpolate_d(in, x->polylen, n, temp);		//2nd order poly interpolate
        }	
    }

}
