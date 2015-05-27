//warps the left signal vector input by the right signal vector input.
//	each value in the right vector is interpreted as a multiply value
//	for remapping the bin in the left signal vector. like vstretch, 
//	except the stretch factor varies with each bin.
//	stretch is still used as an overall offset for each bin, so you can
//  stretch a particular warping shape. nutty.

//you can, of course, run this in the time domain; there is nothing about 
//it that *requires* that you run itt in pfft~. sounds kinda funny.

//another PeRColate hack: dan trueman, 2002


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
void *vectorwarp_new(double val);
void vectorwarp_dsp(t_vectorwarp *x, t_signal **sp, short *count); 
t_int *vectorwarp_perform(t_int *w);
void vectorwarp_assist(t_vectorwarp *x, void *b, long m, long a, char *s);
void vectorwarp_setstretch(t_vectorwarp *x, Symbol *s, short argc, Atom *argv);
void vectorwarp_setlinear(t_vectorwarp *x, Symbol *s, short argc, Atom *argv);
void vectorwarp_setpoly(t_vectorwarp *x, Symbol *s, short argc, Atom *argv);
void vectorwarp_setpoly2(t_vectorwarp *x, Symbol *s, short argc, Atom *argv);
void vectorwarp_setpower(t_vectorwarp *x, Symbol *s, short argc, Atom *argv);

//t_symbol *ps_spvector;
void *vectorwarp_class;


//primary MSP funcs
void main(void)
{
    setup((struct messlist **)&vectorwarp_class, (method)vectorwarp_new, (method)dsp_free, (short)sizeof(t_vectorwarp), 0L, A_GIMME, 0);
    addmess((method)vectorwarp_dsp, "dsp", A_CANT, 0);
    addmess((method)vectorwarp_assist,"assist",A_CANT,0);
    addmess((method)vectorwarp_setpower, "power", A_GIMME, 0);
    addmess((method)vectorwarp_setstretch, "stretch", A_GIMME, 0);
    addmess((method)vectorwarp_setlinear, "linear", A_GIMME, 0);
    addmess((method)vectorwarp_setpoly, "poly", A_GIMME, 0);
    addmess((method)vectorwarp_setpoly, "poly2", A_GIMME, 0);
    dsp_initclass();
 
    rescopy('STR#',RSRC_ID);
}

//what to do when we get the message "mymessage" and a value (or list of values)
void vectorwarp_setpower(t_vectorwarp *x, Symbol *s, short argc, Atom *argv)
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
	assist_string(RSRC_ID,m,a,1,3,s);
}

void *vectorwarp_new(double initial_coeff)
{
	int i;

    t_vectorwarp *x = (t_vectorwarp *)newobject(vectorwarp_class);
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


void vectorwarp_dsp(t_vectorwarp *x, t_signal **sp, short *count)
{
		dsp_add(vectorwarp_perform, 5, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[0]->s_n);	
}

t_int *vectorwarp_perform(t_int *w)
{
	t_vectorwarp *x = (t_vectorwarp *)(w[1]);

	long i;

	float *in 			= (float *)(w[2]);
	float *warptable 	= (float *)(w[3]);
	float *out 			= (float *)(w[4]);
	long n 				= w[5];
	
	double temp, temp2;
	long warpStart, warpEnd;
	double warpOffset;
	
	if (x->x_obj.z_disabled) goto skipout;
	if (!x->power) goto skipout;
	
	if (x->interp_method == INT_LINEAR) {	
		for(i=0;i<n;i++) {
			temp = (double)i * (double)x->stretch * warptable[i]; 		//float index for startpoint
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
			temp = (double)i*(double)x->stretch * warptable[i]; 	//what's the index we want
			*out++ = polyinterpolate(in, x->polylen, n, temp);		//2nd order poly interpolate
		}	
	}

skipout:
	return w + 6;
}	

void vectorwarp_setstretch(t_vectorwarp *x, Symbol *s, short argc, Atom *argv)
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

void vectorwarp_setlinear(t_vectorwarp *x, Symbol *s, short argc, Atom *argv)
{
	x->interp_method = INT_LINEAR;
}

void vectorwarp_setpoly(t_vectorwarp *x, Symbol *s, short argc, Atom *argv)
{
	x->interp_method = INT_POLY;
	x->polylen = 3;
}

void vectorwarp_setpoly2(t_vectorwarp *x, Symbol *s, short argc, Atom *argv)
{
	x->interp_method = INT_POLY;
	x->polylen = 4;
}