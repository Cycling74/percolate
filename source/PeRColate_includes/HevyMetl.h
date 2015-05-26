/***************************************************/
/*! \class HevyMetl
    \brief STK heavy metal FM synthesis instrument.

    This class implements 3 cascade operators with
    feedback modulation, also referred to as
    algorithm 3 of the TX81Z.

    \code
    Algorithm 3 is :    4--\
                    3-->2-- + -->1-->Out
    \endcode

    Control Change Numbers: 
       - Total Modulator Index = 2
       - Modulator Crossfade = 4
       - LFO Speed = 11
       - LFO Depth = 1
       - ADSR 2 & 4 Target = 128

    The basic Chowning/Stanford FM patent expired
    in 1995, but there exist follow-on patents,
    mostly assigned to Yamaha.  If you are of the
    type who should worry about this (making
    money) worry away.

    by Perry R. Cook and Gary P. Scavone, 1995 - 2004.
*/
/***************************************************/

#ifndef STK_HEVYMETL_H
#define STK_HEVYMETL_H

#include "FM.h"

class HevyMetl : public FM
{
 public:
  //! Class constructor.
  /*!
    An StkError will be thrown if the rawwave path is incorrectly set.
  */
  HevyMetl();

  //! Class destructor.
  ~HevyMetl();

  //! Start a note with the given frequency and amplitude.
  void noteOn(StkFloat frequency, StkFloat amplitude);

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
};

#endif
