// only let the top n samples through in a vector.
// by r. luke dubois, cmc/cu, 2005.

#include <math.h>
#include "ext.h"
#include "z_dsp.h"

void *sigcasey_class;

typedef struct _sigcasey
{
    t_pxobject x_obj;
    t_float x_val;
    t_float x_biggest;
} t_sigcasey;

void *sigcasey_new(double val);
t_int *offset_perform(t_int *w);
t_int *sigcasey2_perform(t_int *w);
void sigcasey_float(t_sigcasey *x, double f);
void sigcasey_int(t_sigcasey *x, long n);
void sigcasey_bang(t_sigcasey *x);
void sigcasey_dsp(t_sigcasey *x, t_signal **sp, short *count);
void sigcasey_assist(t_sigcasey *x, void *b, long m, long a, char *s);

void main(void)
{
    setup((t_messlist **)&sigcasey_class, (method)sigcasey_new, (method)dsp_free, (short)sizeof(t_sigcasey), 0L, A_DEFFLOAT, 0);
    addmess((method)sigcasey_dsp, "dsp", A_CANT, 0);
	addbang((method)sigcasey_bang);
    addfloat((method)sigcasey_float);
    addint((method)sigcasey_int);
    addmess((method)sigcasey_assist,"assist",A_CANT,0);
    dsp_initclass();
    
    post("casey~: by r. luke dubois, cmc");
}

void sigcasey_assist(t_sigcasey *x, void *b, long m, long a, char *s)
{
	switch(m) {
		case 1: // inlet
			switch(a) {
				case 0:
				sprintf(s, "(Signal) Input");
				break;
				case 1:
				sprintf(s, "(Signal) Top N in Vector");
				break;
			}
		break;
		case 2: // outlet
			switch(a) {
				case 0:
				sprintf(s, "(Signal) Output");
				break;
			}
		break;
	}
}

void *sigcasey_new(double val)
{
    t_sigcasey *x = (t_sigcasey *)newobject(sigcasey_class);
    dsp_setup((t_pxobject *)x,2);
    outlet_new((t_pxobject *)x, "signal");
	if(val>0) 
	{
		x->x_val = val;
	}
	else 
	{
		x->x_val = 1;
	}
    x->x_biggest = 0.;
    return (x);
}

void sigcasey_bang(t_sigcasey *x)
{
	post("x is %f", x->x_biggest);
}

// this routine covers both inlets. It doesn't matter which one is involved

void sigcasey_float(t_sigcasey *x, double f)
{
	x->x_val = f;
}

void sigcasey_int(t_sigcasey *x, long n)
{
	x->x_val = (float)n;
}

t_int *offset_perform(t_int *w)
{
    t_float *in = (t_float *)(w[1]);
    t_float *out = (t_float *)(w[2]);
	t_sigcasey *x = (t_sigcasey *)(w[3]);
	int val = (int)fabs(x->x_val);
	float inval;
	int n = (int)(w[4]);
	int bigsofar = 0;
	float lastbiggest = 0.;
	int used[8192];
	int i;
	for(i=0;i<8192;i++)
	{
		used[i] = 0;
	}
	
	if (x->x_obj.z_disabled)
		goto out;
	for(i=0;i<val;i++) 
	{
		n = (int)(w[4]);
		in = (float *)(w[1]);
		bigsofar = 0;
		lastbiggest = 0;
		while (--n) {
			inval = *++in;
			if((inval>lastbiggest)&&(used[n]==0))
			{
				bigsofar = n;
				lastbiggest = inval;
			}
		
		}
		used[bigsofar] = 1;
	}

	n = (int)(w[4]);
	in = (float *)(w[1]);
	while (--n) 
	{
		*++out = *++in*used[n];
	}
    
out:
    x->x_biggest = val;
    return (w+5);
}

t_int *sigcasey2_perform(t_int *w)
{
	t_float *in1,*in2,*out;
	int n;
	float inval, val;

	if (*(long *)(w[1]))
	    goto out;

	in1 = (t_float *)(w[2]);
	in2 = (t_float *)(w[3]);
	out = (t_float *)(w[4]);
	n = (int)(w[5]);
	while (--n) {
		inval = *++in1;
		val = fabs(*++in2);
    	if (fabs(inval)>val) {
    		if(inval>=0) {
	    		*++out = val-(inval-val);
	    	}
	    	else {
	    		*++out = (0.-val)+((fabs(inval))-val);
	    	}
    	}
		else {
    		*++out = inval;
    	}
	}
out:
	return (w+6);
}		

void sigcasey_dsp(t_sigcasey *x, t_signal **sp, short *count)
{
	long i;
		
	if (!count[0])
		dsp_add(offset_perform, 4, sp[1]->s_vec-1, sp[2]->s_vec-1, x, sp[0]->s_n+1);
	else if (!count[1])
		dsp_add(offset_perform, 4, sp[0]->s_vec-1, sp[2]->s_vec-1, x, sp[0]->s_n+1);
	else
		dsp_add(sigcasey2_perform, 5, &x->x_obj.z_disabled, sp[0]->s_vec-1, sp[1]->s_vec-1, sp[2]->s_vec-1, sp[0]->s_n+1);
}

