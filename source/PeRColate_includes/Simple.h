/***************************************************/
/*! \class Simple
    \brief STK wavetable/noise instrument.

    This class combines a looped wave, a
    noise source, a biquad resonance filter,
    a one-pole filter, and an ADSR envelope
    to create some interesting sounds.

    Control Change Numbers: 
       - Filter Pole Position = 2
       - Noise/Pitched Cross-Fade = 4
       - Envelope Rate = 11
       - Gain = 128

    by Perry R. Cook and Gary P. Scavone, 1995 - 2004.
*/
/***************************************************/

#ifndef STK_SIMPLE_H
#define STK_SIMPLE_H

#include "Instrmnt.h"
#include "ADSR.h"
#include "WaveLoop.h"
#include "OnePole.h"
#include "BiQuad.h"
#include "Noise.h"

class Simple : public Instrmnt
{
 public:
  //! Class constructor.
  /*!
    An StkError will be thrown if the rawwave path is incorrectly set.
  */
  Simple();

  //! Class destructor.
  ~Simple();

  //! Clear internal states.
  void clear();

  //! Set instrument parameters for a particular frequency.
  void setFrequency(StkFloat frequency);

  //! Start envelope toward "on" target.
  void keyOn();

  //! Start envelope toward "off" target.
  void keyOff();

  //! Start a note with the given frequency and amplitude.
  void noteOn(StkFloat frequency, StkFloat amplitude);

  //! Stop a note with the given amplitude (speed of decay).
  void noteOff(StkFloat amplitude);

  //! Compute one output sample.
  StkFloat tick();

  //! Computer \e vectorSize outputs and return them in \e vector.
  StkFloat *tick(StkFloat *vector, unsigned int vectorSize);

  //! Fill a channel of the StkFrames object with computed outputs.
  /*!
    The \c channel argument should be one or greater (the first
    channel is specified by 1).  An StkError will be thrown if the \c
    channel argument is zero or it is greater than the number of
    channels in the StkFrames object.
  */
  StkFrames& tick( StkFrames& frames, unsigned int channel = 1 );

  //! Perform the control change specified by \e number and \e value (0.0 - 128.0).
  void controlChange(int number, StkFloat value);

 protected:  
  ADSR      adsr_; 
  WaveLoop *loop_;
  OnePole   filter_;
  BiQuad    biquad_;
  Noise     noise_;
  StkFloat  baseFrequency_;
  StkFloat  loopGain_;

};

#endif
