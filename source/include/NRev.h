/***************************************************/
/*! \class NRev
    \brief CCRMA's NRev reverberator class.

    This class is derived from the CLM NRev
    function, which is based on the use of
    networks of simple allpass and comb delay
    filters.  This particular arrangement consists
    of 6 comb filters in parallel, followed by 3
    allpass filters, a lowpass filter, and another
    allpass in series, followed by two allpass
    filters in parallel with corresponding right
    and left outputs.

    by Perry R. Cook and Gary P. Scavone, 1995 - 2004.
*/
/***************************************************/

#ifndef STK_NREV_H
#define STK_NREV_H

#include "Effect.h" 
#include "DelayL.h" 

class NRev : public Effect
{
 public:
  //! Class constructor taking a T60 decay time argument (one second default value).
  NRev( StkFloat T60 = 1.0 );

  //! Class destructor.
  ~NRev();

  //! Reset and clear all internal state.
  void clear();

  //! Set the reverberation T60 decay time.
  void setT60( StkFloat T60 );

  //! Compute one output sample.
  StkFloat tick(StkFloat input);

  //! Take \e vectorSize inputs, compute the same number of outputs and return them in \e vector.
  StkFloat *tick( StkFloat *vector, unsigned int vectorSize );

  //! Take a channel of the StkFrames object as inputs to the effect and replace with corresponding outputs.
  /*!
    The \c channel argument should be one or greater (the first
    channel is specified by 1).  An StkError will be thrown if the \c
    channel argument is zero or it is greater than the number of
    channels in the StkFrames object.
  */
  StkFrames& tick( StkFrames& frames, unsigned int channel = 1 );

 protected:  
  DelayL allpassDelays_[8];
  DelayL combDelays_[6];
  StkFloat allpassCoefficient_;
  StkFloat combCoefficient_[6];
	StkFloat lowpassState_;

};

#endif

