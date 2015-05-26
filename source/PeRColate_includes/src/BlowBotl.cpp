/***************************************************/
/*! \class BlowBotl
    \brief STK blown bottle instrument class.

    This class implements a helmholtz resonator
    (biquad filter) with a polynomial jet
    excitation (a la Cook).

    Control Change Numbers: 
       - Noise Gain = 4
       - Vibrato Frequency = 11
       - Vibrato Gain = 1
       - Volume = 128

    by Perry R. Cook and Gary P. Scavone, 1995 - 2004.
*/
/***************************************************/

#include "BlowBotl.h"
#include "SKINI.msg"

#define __BOTTLE_RADIUS_ 0.999

BlowBotl :: BlowBotl()
{
  dcBlock_.setBlockZero();

  // Concatenate the STK rawwave path to the rawwave file
  vibrato_ = new WaveLoop( (Stk::rawwavePath() + "sinewave.raw").c_str(), true );
  vibrato_->setFrequency( 5.925 );
  vibratoGain_ = 0.0;

  resonator_.setResonance(500.0, __BOTTLE_RADIUS_, true);
  adsr_.setAllTimes( 0.005, 0.01, 0.8, 0.010);

  noiseGain_ = 20.0;
	maxPressure_ = (StkFloat) 0.0;
}

BlowBotl :: ~BlowBotl()
{
  delete vibrato_;
}

void BlowBotl :: clear()
{
  resonator_.clear();
}

void BlowBotl :: setFrequency(StkFloat frequency)
{
  StkFloat freakency = frequency;
  if ( frequency <= 0.0 ) {
    errorString_ << "BlowBotl::setFrequency: parameter is less than or equal to zero!";
    handleError( StkError::WARNING );
    freakency = 220.0;
  }

  resonator_.setResonance( freakency, __BOTTLE_RADIUS_, true );
}

void BlowBotl :: startBlowing(StkFloat amplitude, StkFloat rate)
{
  adsr_.setAttackRate(rate);
  maxPressure_ = amplitude;
  adsr_.keyOn();
}

void BlowBotl :: stopBlowing(StkFloat rate)
{
  adsr_.setReleaseRate(rate);
  adsr_.keyOff();
}

void BlowBotl :: noteOn(StkFloat frequency, StkFloat amplitude)
{
  this->setFrequency(frequency);
  startBlowing( 1.1 + (amplitude * 0.20), amplitude * 0.02);
  outputGain_ = amplitude + 0.001;

#if defined(_STK_DEBUG_)
  errorString_ << "BlowBotl::NoteOn: frequency = " << frequency << ", amplitude = " << amplitude << ".";
  handleError( StkError::DEBUG_WARNING );
#endif
}

void BlowBotl :: noteOff(StkFloat amplitude)
{
  this->stopBlowing(amplitude * 0.02);

#if defined(_STK_DEBUG_)
  errorString_ << "BlowBotl::NoteOff: amplitude = " << amplitude << ".";
  handleError( StkError::DEBUG_WARNING );
#endif
}

StkFloat BlowBotl :: tick()
{
  StkFloat breathPressure;
  StkFloat randPressure;
  StkFloat pressureDiff;

  // Calculate the breath pressure (envelope + vibrato)
  breathPressure = maxPressure_ * adsr_.tick();
  breathPressure += vibratoGain_ * vibrato_->tick();

  pressureDiff = breathPressure - resonator_.lastOut();

  randPressure = noiseGain_ * noise_.tick();
  randPressure *= breathPressure;
  randPressure *= (1.0 + pressureDiff);

  resonator_.tick( breathPressure + randPressure - ( jetTable_.tick( pressureDiff ) * pressureDiff ) );
  lastOutput_ = 0.2 * outputGain_ * dcBlock_.tick( pressureDiff );

  return lastOutput_;
}

StkFloat *BlowBotl :: tick(StkFloat *vector, unsigned int vectorSize)
{
  return Instrmnt::tick( vector, vectorSize );
}

StkFrames& BlowBotl :: tick( StkFrames& frames, unsigned int channel )
{
  return Instrmnt::tick( frames, channel );
}

void BlowBotl :: controlChange(int number, StkFloat value)
{
  StkFloat norm = value * ONE_OVER_128;
  if ( norm < 0 ) {
    norm = 0.0;
    errorString_ << "BlowBotl::controlChange: control value less than zero ... setting to zero!";
    handleError( StkError::WARNING );
  }
  else if ( norm > 1.0 ) {
    norm = 1.0;
    errorString_ << "BlowBotl::controlChange: control value greater than 128.0 ... setting to 128.0!";
    handleError( StkError::WARNING );
  }

  if (number == __SK_NoiseLevel_) // 4
    noiseGain_ = norm * 30.0;
  else if (number == __SK_ModFrequency_) // 11
    vibrato_->setFrequency( norm * 12.0 );
  else if (number == __SK_ModWheel_) // 1
    vibratoGain_ = norm * 0.4;
  else if (number == __SK_AfterTouch_Cont_) // 128
    adsr_.setTarget( norm );
  else {
    errorString_ << "BlowBotl::controlChange: undefined control number (" << number << ")!";
    handleError( StkError::WARNING );
  }

#if defined(_STK_DEBUG_)
    errorString_ << "BlowBotl::controlChange: number = " << number << ", value = " << value << ".";
    handleError( StkError::DEBUG_WARNING );
#endif
}
