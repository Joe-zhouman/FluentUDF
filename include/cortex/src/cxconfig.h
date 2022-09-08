/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/*
 *  cxconfig.h
 */

#pragma once

#include "cxlocalize.h"

#if defined(_M_IA64) || defined(_M_AMD64) || defined(WIN64) || defined(_WIN64) || defined(_M_X64)     /* MSVS/Windows specific macros. */
#define CX_POINTER_SIZED_INT                        __int64
#define strtopointersizedint(str, endptr, base)     _strtoi64(str, endptr, base)
#define CX_POINTER_SIZED_INT_FORMAT                 "%I64d"
/*If testing for limits using limits.h, include that header before including this.*/
#if defined(LLONG_MAX) && defined(LLONG_MIN)
#define CX_POINTER_SIZED_INT_MAX LLONG_MAX
#define CX_POINTER_SIZED_INT_MIN LLONG_MIN
#endif
#else
#define CX_POINTER_SIZED_INT                        long
#define strtopointersizedint(str, endptr, base)     strtol(str, endptr, base)
#define CX_POINTER_SIZED_INT_FORMAT                 "%ld"
#if defined(LONG_MAX) && defined(LONG_MIN)
#define CX_POINTER_SIZED_INT_MAX LONG_MAX
#define CX_POINTER_SIZED_INT_MIN LONG_MIN
#endif
#endif

/*Common limits and constants used in both cortex and library created for solver modules*/
#define MAX_HOST_NAME_LEN 1024

#ifndef CX_SINGLE
# define CX_SINGLE 0
#endif

#ifndef CX_HOST_SINGLE
#  define CX_HOST_SINGLE 0
#endif

#if CX_HOST_SINGLE
#  define GRAPHICS 0
#  define LICENSE_MANAGER 1
#  define CX_GUI 0
#  undef HAVE_MOTIF
#  define HAVE_MOTIF 0
#endif

#ifndef GRAPHICS
# define GRAPHICS 1
#endif

#ifndef CX_GUI
#define CX_GUI 1
#endif

#ifndef LICENSE_MANAGER
# define LICENSE_MANAGER 1
#endif

#ifndef FLUENT_BETA
# define FLUENT_BETA 0
#endif

#ifndef HAVE_MOTIF
# if _NT
#  define HAVE_MOTIF 0
# else
#  define HAVE_MOTIF 1
# endif
#endif

#if GRAPHICS
# ifndef HAVE_TIFF
#  define HAVE_TIFF 1
# endif

#if 1
# ifndef HAVE_PNG
#  define HAVE_PNG 1
# endif
#endif

# ifndef HAVE_VRML
#  define HAVE_VRML 1
# endif

# ifndef HAVE_AVZ
#  define HAVE_AVZ 1
# endif

# ifndef HAVE_GLB
#  define HAVE_GLB 1
# endif

# ifndef HAVE_MPEG
#  define HAVE_MPEG 1
# endif

# ifndef HAVE_JPEG
#  define HAVE_JPEG 1
# endif

# ifndef SPACEBALL
#  define SPACEBALL 0
# endif

# ifndef LIB_HOOPS
#if DEVELOP
#  define LIB_HOOPS -lhoopsd
#else
#  define LIB_HOOPS -lhoops
#endif
# endif

# ifndef HOOPS_INCLUDES
#  define HOOPS_INCLUDES -I../include/hoops/3dgs -I../include/hoops/base_stream -I../include/hoops/stream -I../include/hoops/utility
# endif

# ifndef HAVE_HOOPS_STREAMS
#  define HAVE_HOOPS_STREAMS 1
# endif

# ifndef HAVE_IMAGE
#  define HAVE_IMAGE 0
# endif

#else
# define HAVE_TIFF 0
# define HAVE_PNG 0
# define HAVE_VRML 0
# define HAVE_IMAGE 0
# define HAVE_MPEG 0
# define HAVE_JPEG 0
# define HAVE_HOOPS_STREAM 0
# define SPACEBALL 0
# undef LIB_HOOPS
# define LIB_HOOPS
# undef HOOPS_INCLUDES
# define HOOPS_INCLUDES
#endif

#ifndef PARALLEL
# define PARALLEL 0
# define CX_HOST 0
# define CX_NODE 0
#endif

#ifndef NODE_ONLY
# define NODE_ONLY 0
#endif


#ifndef CXX_FLAGS
# define CXX_FLAGS
#endif

#ifndef  DEBUG
# define DEBUG 0
#endif


