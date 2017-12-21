/* source/config.h.  Generated automatically by configure.  */
#ifndef _CONFIG_H_
#define _CONFIG_H_
/*
  Vrml 97 library
  Copyright (C) 1998 Chris Morley

  config.h
*/

#define LIBVRML_MAJOR_VERSION	0
#define LIBVRML_MINOR_VERSION	7
#define LIBVRML_MICRO_VERSION	9

/* cfront 1.2 defines "c_plusplus" instead of "__cplusplus" */
#ifdef c_plusplus
#ifndef __cplusplus
#define __cplusplus
#endif
#endif


#ifdef  __cplusplus

#ifdef _WIN32

// Disable warning messages about truncation from const double to float
# pragma warning( disable : 4305 )  
// Disable warning messages about truncating names in debug info
# pragma warning( disable : 4786 )  

static const char SLASH = '\\';

#else

static const char SLASH = '/';

#endif

#if defined AW_NEW_IOSTREAMS
   #include <iosfwd> // temp - remove this later
   using namespace std;
#endif


#endif	/* __cplusplus */

static const char COLON = ':';

/* Make sure that PI and friends are defined.  This is needed under 
   platforms that are not directly BSD derived (even under GNU libc
   this is not included by default).
*/
#ifndef M_PI
#define M_PI            3.14159265358979323846  /* pi */
#endif

#ifndef M_PI_2
#define M_PI_2          1.57079632679489661923  /* pi/2 */
#endif

#ifndef M_PI_4
#define M_PI_4          0.78539816339744830962  /* pi/4 */
#endif

#ifndef M_1_PI
#define M_1_PI          0.31830988618379067154  /* 1/pi */
#endif


/* General feature configuration */
#ifndef BASELEVEL

#define HAVE_LIBJPEG	0
#define HAVE_LIBPNG	0
#define HAVE_GL		1
#define HAVE_GLUT	0
#define HAVE_XT		0
#define HAVE_XM		0
#define HAVE_GTK	0
#define HAVE_JAVASCRIPT	0
#define HAVE_JDK	0
#define HAVE_HOOPS	0
#define HAVE_SOUND	0
#define HAVE_ESD	0

#else

#define HAVE_LIBJPEG	1
#define HAVE_LIBPNG	1
#define HAVE_GL		1
#define HAVE_GLUT	1
#define HAVE_XT		1
#define HAVE_XM		1
#define HAVE_GTK	1
#define HAVE_JAVASCRIPT	0
#define HAVE_JDK	0
#define HAVE_HOOPS	0
#define HAVE_SOUND	0
#define HAVE_ESD	0
#endif

/* General Compiler Capabilities */
#define HAVE_CONST_CAST		    1
#define HAVE_NATIVE_BOOL	    1
#define HAVE_PARTIAL_SPECIALIZATION 1
#define HAVE_MEMBER_TEMPLATES	    1
#define HAVE_NO_STATIC_TEMPLATES    0
#define HAVE_VOID_RETURN_TYPE	    0


#endif	/* _CONFIG_H_ */

