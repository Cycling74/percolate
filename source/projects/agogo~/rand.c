/* Metrowerks Standard Library
 * Copyright © 1995-2002 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2002/01/30 23:10:21 $
 * $Revision: 1.17 $
 */

/*
 *	Routines
 *	--------
 *		rand
 *		srand
 *
 *	Note
 *	----
 *		This is exactly the function described in the standard, including the
 *		assumption that RAND_MAX == 32767.
 */

#include <stdlib.h>

#if _MSL_THREADSAFE && (__dest_os == __win32_os || __dest_os == __wince_os)
	#include <ThreadLocalData.h>
#else

	_MSL_TLS static unsigned long int next = 1;			/*- cc 011128 -*/

#endif

int _MSL_CDECL rand(void)
{
#if _MSL_THREADSAFE && (__dest_os == __win32_os || __dest_os == __wince_os)
	_GetThreadLocalData(_MSL_TRUE)->random_next =
			_GetThreadLocalData(_MSL_TRUE)->random_next * 1103515245 + 12345;
	return((_GetThreadLocalData(_MSL_TRUE)->random_next >> 16) & 0x7FFF);
#else
	next = next * 1103515245 + 12345;
	return((next >> 16) & 0x7FFF);
#endif
}

void _MSL_CDECL srand(unsigned int seed)
{
#if _MSL_THREADSAFE && (__dest_os == __win32_os || __dest_os == __wince_os)
	_GetThreadLocalData(_MSL_TRUE)->random_next = seed;	/*- cc 010531 -*/
#else
	next = seed;
#endif
}

/* Change record:
 * JFH 950607 First code release.
 * JFH 960429 Merged Win32 changes in.
 * KO  961219 Changed this file to use the thread local data structure instead
 *            of a global.
 * mf  980512 wince changes
 * mf  990309 use _MWMT instead of _MT for single threaded lib
 * cc  010531 Added _GetThreadLocalData's flag
 * cc  011128 Made __tls _MSL_TLS
 * cc  011203 Added _MSL_CDECL for new name mangling
 * JWW 020130 Changed _MWMT to _MSL_THREADSAFE for consistency's sake
 */