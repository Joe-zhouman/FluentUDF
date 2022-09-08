/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/
/**********************************************************
 *
 *   fortran_types.h
 *
 **********************************************************/

/* Declare C typedef's for each Fortran data type */

#ifndef _fortran_types_h

#define _fortran_types_h

/* Character */

typedef char   Fchar;

/* Double Precision */

typedef double Fdouble;

/* Integer */
#  if _NT
typedef long long Fint;
#else
typedef long Fint;
#endif

typedef int Fint4;

#if _NT
typedef long long Fint8;
#else
typedef long Fint8;
#endif

/* Logical */
#  if _NT
typedef long long Flogical;
#else
typedef long Flogical;
#endif

/* Real */

/*CFX uses CFX5_ATTR_DOUBLE instead of RP_DOUBLE*/
#if RP_DOUBLE
typedef double Freal;
#else
typedef float  Freal;
#endif

/* Hidden lengths for character strings are 8 bytes on some platforms, 4 on others */
#if defined(CFX5_OS_HPUX) || defined(CFX5_OS_HPUX_IA64)
#  if defined(__ia64) || defined(_LP64)
typedef long FLen;
#  else
typedef int FLen;
#  endif
#elif defined(CFX5_OS_SOLARIS_AMD64) || defined(CFX5_OS_SOLARIS) || defined(CFX5_OS_LINUX_IA64)
typedef long FLen;
#elif defined(CFX5_OS_WINNT_AMD64)
typedef __int64 FLen;
#elif defined(CFX5_OS_LINUX_AMD64) && defined(__INTEL_COMPILER)
typedef long FLen;
#else
typedef int FLen;
#endif

/* Fortran stack pointers */

#  if _NT
typedef long long Fpoint;
#else
typedef long Fpoint;
#endif

#endif /* !_fortran_types_h*/
