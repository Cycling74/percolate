//prc_chorus
//
//dt 2005; yet another PeRColate hack
//
// updated for Max 7 by Darwin Grosse and Tim Place
// ------------------------------------------------

//here are the notes from the original STK instrument
/***************************************************/
/*! \class Chorus
    \brief STK chorus effect class.

    This class implements a chorus effect.

    by Perry R. Cook and Gary P. Scavone, 1995 - 2004.
*/
/***************************************************/

extern "C" {
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "ext_strings.h"
}

#include <math.h>
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Chorus.h"

t_class *prc_chorus_class;


typedef struct _prc_chorus {
    t_pxobject	x_obj;
    Chorus		*mychorus;
} t_prc_chorus;


/****PROTOTYPES****/

//setup funcs; this probably won't change, unless you decide to change the number of
//args that the user can input, in which case prc_chorus_new will have to change
void *prc_chorus_new(long num_inputs);
void prc_chorus_free(t_prc_chorus *x);
void prc_chorus_assist(t_prc_chorus *x, void *b, long m, long a, char *s);

// dsp stuff
void prc_chorus_dsp64(t_prc_chorus *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void prc_chorus_perform64(t_prc_chorus *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

//for custom messages
void prc_chorus_setModDepth(t_prc_chorus *x, t_symbol *s, long argc, t_atom *argv);
void prc_chorus_setModFrequency(t_prc_chorus *x, t_symbol *s, long argc, t_atom *argv);
void prc_chorus_setEffectMix(t_prc_chorus *x, t_symbol *s, long argc, t_atom *argv);
void prc_chorus_clearmesh(t_prc_chorus *x, t_symbol *s, long argc, t_atom *argv);


/****FUNCTIONS****/

//primary MSP funcs
void ext_main(void* p)
{
    t_class *c = class_new("prc_chorus~", (method)prc_chorus_new, (method)prc_chorus_free, sizeof(t_prc_chorus), 0, A_DEFLONG, 0);
    
    class_addmethod(c, (method)prc_chorus_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)prc_chorus_dsp64, "dsp64", A_CANT, 0);
	
    //our own messages
    class_addmethod(c, (method)prc_chorus_setModDepth, "depth", A_GIMME, 0);
    class_addmethod(c, (method)prc_chorus_setModFrequency, "frequency", A_GIMME, 0);
    class_addmethod(c, (method)prc_chorus_setEffectMix, "mix", A_GIMME, 0);
    class_dspinit(c);
    
    class_register(CLASS_BOX, c);
    prc_chorus_class = c;
}


//this gets called when the object is created; everytime the user types in new args, this will get called
void *prc_chorus_new(long baseDelay)
{
    t_prc_chorus *x = (t_prc_chorus *)object_alloc(prc_chorus_class);
    
    if (x) {
		dsp_setup((t_pxobject *)x, 1);		//inputs
		outlet_new((t_object*)x, "signal");	//outputs
		
		if (baseDelay<1)
			baseDelay = 1;
		x->mychorus = new Chorus(baseDelay);
	}
    return x;
}


//this gets called when an object is destroyed. do stuff here if you need to clean up.
void prc_chorus_free(t_prc_chorus *x)
{
	dsp_free((t_pxobject *)x);
	delete x->mychorus;
}


//tells the user about the inputs/outputs when mousing over them
void prc_chorus_assist(t_prc_chorus *x, void *b, long m, long a, char *s)
{
	if (m==1)
		std::sprintf(s, "input (signal)");
	else
		std::sprintf(s, "output (signal)");
}


void prc_chorus_setModDepth(t_prc_chorus *x, t_symbol *s, long argc, t_atom *argv)
{
	x->mychorus->setModDepth(atom_getfloat(argv));
}


void prc_chorus_setModFrequency(t_prc_chorus *x, t_symbol *s, long argc, t_atom *argv)
{
	x->mychorus->setModFrequency(atom_getfloat(argv));
}


void prc_chorus_setEffectMix(t_prc_chorus *x, t_symbol *s, long argc, t_atom *argv)
{
	x->mychorus->setEffectMix(atom_getfloat(argv));
}


void prc_chorus_clearmesh(t_prc_chorus *x, t_symbol *s, long argc, t_atom *argv)
{
	x->mychorus->clear();
}


void prc_chorus_dsp64(t_prc_chorus *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	Stk::setSampleRate(samplerate);
    object_method(dsp64, gensym("dsp_add64"), x, prc_chorus_perform64, 0, NULL);
}


void prc_chorus_perform64(t_prc_chorus *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double	*in = ins[0];
	t_double	*out = outs[0];
	
	while (sampleframes--)
		*out++ = x->mychorus->tick(*in++);
}
