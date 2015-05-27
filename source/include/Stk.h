/***************************************************/
/*! \class Stk
    \brief STK base class

    Nearly all STK classes inherit from this class.
    The global sample rate and rawwave path variables
    can be queried and modified via Stk.  In addition,
    this class provides error handling and
    byte-swapping functions.

    by Perry R. Cook and Gary P. Scavone, 1995 - 2004.
*/
/***************************************************/

#ifndef STK_STK_H
#define STK_STK_H

//maxmsp add
#define __MACOSX_CORE__
//#define __cplusplus
extern "C" {
#include "ext.h"
//#include <fcntl.h>
//#include <unix.h>
//#include <stat.h>
}
#define _MAC
//end maxmsp add


#include <string>
#include <iostream>
#include <sstream>
#include <valarray>
#include <time.h>

// Most data in STK is passed and calculated with the
// following user-definable floating-point type.  You
// can change this to "float" if you prefer or perhaps
// a "long double" in the future.
typedef double StkFloat;

// The "MY_FLOAT" type was deprecated in STK
// versions higher than 4.1.3 and replaced with the variable
// "StkFloat".  
#if defined(__WINDOWS_DS__) || defined(__WINDOWS_ASIO__)
  typedef StkFloat MY_FLOAT;
  #pragma deprecated(MY_FLOAT)
#elif defined(__GXX__) 
  typedef StkFloat MY_FLOAT __attribute__ ((deprecated));
#else
  typedef StkFloat MY_FLOAT; // temporary
#endif


//! STK error handling class.
/*!
  This is a fairly abstract exception handling class.  There could
  be sub-classes to take care of more specific error conditions ... or
  not.
*/
class StkError
{
public:
  enum Type {
    STATUS,
    WARNING,
    DEBUG_WARNING,
    FUNCTION_ARGUMENT,
    FILE_NOT_FOUND,
    FILE_UNKNOWN_FORMAT,
    FILE_ERROR,
    PROCESS_THREAD,
    PROCESS_SOCKET,
    PROCESS_SOCKET_IPADDR,
    AUDIO_SYSTEM,
    MIDI_SYSTEM,
    UNSPECIFIED
  };

protected:
  std::string message_;
  Type type_;

public:
  //! The constructor.
  StkError(const std::string& message, Type type = StkError::UNSPECIFIED) : message_(message), type_(type) {}

  //! The destructor.
  virtual ~StkError(void) {};

  //! Prints thrown error message to stderr.
  virtual void printMessage(void) { std::cerr << '\n' << message_ << "\n\n"; }

  //! Returns the thrown error message type.
  virtual const Type& getType(void) { return type_; }

  //! Returns the thrown error message string.
  virtual const std::string& getMessage(void) { return message_; }

  //! Returns the thrown error message as a C string.
  virtual const char *getMessageCString(void) { return message_.c_str(); }
};


class Stk
{
public:

  typedef unsigned long StkFormat;
  static const StkFormat STK_SINT8;   /*!< -128 to +127 */
  static const StkFormat STK_SINT16;  /*!< -32768 to +32767 */
  static const StkFormat STK_SINT24;  /*!< Upper 3 bytes of 32-bit signed integer. */
  static const StkFormat STK_SINT32;  /*!< -2147483648 to +2147483647. */
  static const StkFormat STK_FLOAT32; /*!< Normalized between plus/minus 1.0. */
  static const StkFormat STK_FLOAT64; /*!< Normalized between plus/minus 1.0. */

  //! Static method which returns the current STK sample rate.
  static StkFloat sampleRate(void) { return srate_; }

  //! Static method which sets the STK sample rate.
  /*!
    The sample rate set using this method is queried by all STK
    classes which depend on its value.  It is initialized to the
    default SRATE set in Stk.h.  Many STK classes use the sample rate
    during instantiation.  Therefore, if you wish to use a rate which
    is different from the default rate, it is imperative that it be
    set \e BEFORE STK objects are instantiated.
  */
  static void setSampleRate(StkFloat rate) { if (rate > 0.0) srate_ = rate; }

  //! Static method which returns the current rawwave path.
  //static std::string rawwavePath(void) { return rawwavepath_; }
  //maxmsp
  //static std::string rawwavePath(void) { return "/Library/Application\ Support/Cycling\ \'74/PeRColate/rawwaves/"; }
  static std::string rawwavePath(void) { return ""; }
  //static std::string rawwavePath(void) { return "/Users/PLOrk1/rawwaves/"; }

  //! Static method which sets the STK rawwave path.
  static void setRawwavePath(std::string path);

  //! Static method which byte-swaps a 16-bit data type.
  static void swap16(unsigned char *ptr);

  //! Static method which byte-swaps a 32-bit data type.
  static void swap32(unsigned char *ptr);

  //! Static method which byte-swaps a 64-bit data type.
  static void swap64(unsigned char *ptr);

  //! Static cross-platform method to sleep for a number of milliseconds.
  static void sleep(unsigned long milliseconds);

  //! Static function for error reporting and handling using c-strings.
  static void handleError( const char *message, StkError::Type type );

  //! Static function for error reporting and handling using c++ strings.
  static void handleError( std::string message, StkError::Type type );

private:
  static StkFloat srate_;
  static std::string rawwavepath_;

protected:

  std::ostringstream errorString_;

  //! Default constructor.
  Stk(void);

  //! Class destructor.
  virtual ~Stk(void);

  //! Internal function for error reporting which assumes message in \c errorString_ variable.
  void handleError( StkError::Type type );
};


/***************************************************/
/*! \class StkFrames
    \brief An STK class to handle vectorized audio data.

    This class can hold single- or multi-channel audio data in either
    interleaved or non-interleaved formats.  The data type is always
    StkFloat.

    Possible future improvements in this class could include static
    functions to inter- or de-interleave the data and to convert to
    and return other data types.

    by Perry R. Cook and Gary P. Scavone, 1995 - 2004.
*/
/***************************************************/

class StkFrames
{
public:

  //! The default constructor initializes the frame data structure to size zero.
  StkFrames( unsigned int nFrames = 0, unsigned int nChannels = 1, bool interleaved = true );

  //! Overloaded constructor which initializes the frame data to the specified size with \c value.
  StkFrames( const StkFloat& value, unsigned int nFrames, unsigned int nChannels, bool interleaved = true );

  //! Subscript operator which returns a reference to element \c n of self.
  /*!
    The result can be used as an lvalue . This reference is valid
    until the resize function is called or the array is destroyed. The
    index \c n must be between 0 and size less one.  No range checking
    is performed.
  */
  StkFloat& operator[]( size_t n ) { return data_[n]; };

  //! Subscript operator which returns the value at element \c n of self.
  /*!
    The index \c n must be between 0 and size less one.  No range
    checking is performed.
  */
  StkFloat operator[]( size_t n ) const { return data_[n]; };

  //! Returns the total number of audio samples represented by the object.
  size_t size() const { return size_; }; 

  //! Resize self to represent the specified number of channels and frames.
  /*!
    Changes the size of self based on the number of frames and
    channels, and assigns \c value to every element.
  */
  void resize( unsigned int nFrames, unsigned int nChannels = 1, StkFloat value = 0.0 );

  //! Return the number of channels represented by the data.
  unsigned int channels( void ) const { return nChannels_; };

  //! Return the number of sample frames represented by the data.
  unsigned int frames( void ) const { return nFrames_; };

  //! Returns \c true if the data is in interleaved format, \c false if the data is non-interleaved.
  bool interleaved( void ) const { return interleaved_; };

  //! Set the flag to indicate whether the internal data is in interleaved (\c true) or non-interleaved (\c false) format.
  void setInterleaved( bool isInterleaved ) { interleaved_ = isInterleaved; };

private:
  std::valarray<StkFloat> data_;
  unsigned int nFrames_;
  unsigned int nChannels_;
  size_t size_;
  bool interleaved_;

};


// Here are a few other useful typedefs.
typedef signed short SINT16;
typedef signed int SINT32;
typedef float FLOAT32;
typedef double FLOAT64;

// The default sampling rate.
const StkFloat SRATE = 44100.0;

// The default real-time audio input and output buffer size.  If
// clicks are occuring in the input and/or output sound stream, a
// larger buffer size may help.  Larger buffer sizes, however, produce
// more latency.
const unsigned int RT_BUFFER_SIZE = 512;

// The default rawwave path value is set with the preprocessor
// definition RAWWAVE_PATH.  This can be specified as an argument to
// the configure script, in an integrated development environment, or
// below.  The global STK rawwave path variable can be dynamically set
// with the Stk::setRawwavePath() function.  This value is
// concatenated to the beginning of all references to rawwave files in
// the various STK core classes (ex. Clarinet.cpp).  If you wish to
// move the rawwaves directory to a different location in your file
// system, you will need to set this path definition appropriately.
#if !defined(RAWWAVE_PATH)
  #define RAWWAVE_PATH "../../rawwaves/"
  //maxmsp
  //#define RAWWAVE_PATH "/Volumes/plork1_drive/Library/Application\ Support/Cycling\ \'74/PeRColate/rawwaves/"
#endif


#if !defined(PI)
	const StkFloat PI			= 3.14159265359;
#endif
const StkFloat TWO_PI       = 2 * PI;

const StkFloat ONE_OVER_128 = 0.0078125;

#if defined(__WINDOWS_DS__) || defined(__WINDOWS_ASIO__)
  #define __OS_WINDOWS__
  #define __STK_REALTIME__
#elif defined(__LINUX_OSS__) || defined(__LINUX_ALSA__) || defined(__LINUX_JACK__)
  #define __OS_LINUX__
  #define __STK_REALTIME__
#elif defined(__IRIX_AL__)
  #define __OS_IRIX__
  #define __STK_REALTIME__
#elif defined(__MACOSX_CORE__)
  #define __OS_MACOSX__
  #define __STK_REALTIME__
#endif

//#define _STK_DEBUG_

#endif
