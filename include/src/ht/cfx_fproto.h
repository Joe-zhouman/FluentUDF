/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/
/*
  cfx_fproto.h

  This file declares the following symbols, for use mainly in porting
  to Windows NT but hopefully more generally useful:

  STDCALL     A C declaration for a Fortran-callable function. Use as
              void STDCALL FUNC(void).

  FortranSubPtr
              A pointer to a subroutine.

  PROTOTYPE   Preprocessor symbol, defined if we want function
              prototypes.

  UNDERSCORE  Preprocessor symbol, defined if fortran functions should
              have underscores appended.

  UNDERSCORE_DBL
              Preprocessor symbol, defined if Fortran functions
              containing an underscore already should have two
              underscores appended, in the Linux g77 style.  Functions
              not containing an underscore still have just a single
              underscore appended, and UNDERSCORE will always be
              defined whenever UNDERSCORE_DBL is.

  NT_DECL     Preprocessor symbol, defined if the NT style of
              declaring Fortran-callable functions from C is
        needed. Ie, the name should be in uppercase, and the
        arguments giving the lengths of strings follow the
        string they reference, rather than being collected at
        the end.


              C types for default fortran intrinsic types:
  F_CHAR_T      CHARACTER
  F_INTEGER_T   INTEGER
  F_LOGICAL_T   LOGICAL
  F_REAL_T      REAL
  F_DOUBLE_T    DOUBLE
              C types for special fortran types:
  F_LENGTH_T    Fortran hidden string lengths
  F_POINTER_T   Fortran stack pointers
  F_CRAY_PTR_T  Fortran Cray pointers
  F_PTR64_T     Use 64-bit integer to store cray/C pointers


  It relies on the preprocessor symbol WINDOWS_NT being defined on NT
  by the caller.

  Example usage is as follows, if the function in question doesn't
  take any difficult (ie, string) parameters:

    #if defined NT_DECL
    #  define USER_ABORT  USER_ABORT
    #elif defined UNDERSCORE_DBL
    #  define USER_ABORT  user_abort__
    #elif defined UNDERSCORE
    #  define USER_ABORT  user_abort_
    #else
    #  define USER_ABORT   user_abort
    #endif

  Note that the UNDERSCORE_DBL test comes before that for UNDERSCORE.
  If it does take string parameters, the need to reorder them is also
  signalled by the NT_DECL define.
*/

#ifndef _CFX_FPROTO_H
#define _CFX_FPROTO_H

#if (defined(_WIN32) || defined(WIN64)) && !defined(MAINWIN)
#ifndef _NT
#error _WIN32 defined without _NT. Fix cfx_proto.h.
#endif
#endif

#if defined __STDC__ || defined _NT
#define PROTOTYPE
#endif

#if defined (_WIN32)
#define STDCALL __cdecl
#elif defined (WIN64)
#define STDCALL __stdcall
/*#if defined _NT
#  define STDCALL __stdcall
#  define NT_DECL*/
#elif defined _AIX
#  define STDCALL
#elif defined __APPLE__
#  define STDCALL
#elif defined(__linux) && defined(__powerpc__)
#  define STDCALL
#elif defined(__blrts__)
#  define STDCALL
#elif defined __hpux
#  define STDCALL
#  if defined __ia64 || defined _LP64
/* the IA64 (or 64-bit HP-UX builds, when we get there) uses underscores too */
#    ifndef UNDERSCORE
#      define UNDERSCORE
#    endif
#  endif
#elif defined __linux
#  ifndef UNDERSCORE
#    define UNDERSCORE
#  endif
#  define STDCALL
#  ifndef __ia64
#    if !defined (LINUXIA32_SYS) && !defined (LINUXIA64_SYS)  /* Not Ansys LINUX 32 and not LINUX 64*/
#      define UNDERSCORE_DBL
#    endif
#  endif
#else
#  ifndef UNDERSCORE
#    define UNDERSCORE
#  endif
#  define STDCALL
#endif

typedef void STDCALL FortranSub(void);
typedef FortranSub *FortranSubPtr;

/*=======================================================================*/
/* C Declarations of Intrinsic Fortran Data Types                        */
/*=======================================================================*/

/* CHARACTER */
typedef char   F_CHAR_T;

/* DOUBLE PRECISION */
typedef double F_DOUBLE_T;

/* INTEGER */
#if defined(CFX5_ATTR_INT64)
#  if defined(_M_IX86) || defined(_M_X64) || defined(_M_AMD64)
typedef __int64 F_INTEGER_T;
#  else
typedef long long F_INTEGER_T;
#  endif
#else
typedef int F_INTEGER_T;
#endif

/* INTEGER(KIND=8) */
#if defined(_M_IX86) || defined(_M_X64) || defined(_M_AMD64)
typedef __int64 F_INTEGER8_T;
#else
typedef long long F_INTEGER8_T;
#endif

/* LOGICAL */
#if defined(CFX5_ATTR_INT64)
#  if defined(_M_IX86) || defined(_M_X64) || defined(_M_AMD64)
typedef __int64 F_LOGICAL_T;
#  else
typedef long long F_LOGICAL_T;
#  endif
#else
typedef int F_LOGICAL_T;
#endif

/* REAL */
#if defined(CFX5_ATTR_DOUBLE)
typedef double F_REAL_T;
#else
typedef float  F_REAL_T;
#endif

/* Fortran Hidden String Lengths */
#if defined(__hpux)
/* HP 64-bit uses 64-bit length args */
#  if defined __ia64 || defined _LP64
#    define F_LENGTH_T long
#  else
#    define F_LENGTH_T int
#  endif
#elif defined(__sun)
#  define F_LENGTH_T long
#elif defined(__ia64) && defined(__linux)
#  define F_LENGTH_T long
#elif defined(_M_IX86)
#  define F_LENGTH_T int
#elif defined(_M_X64) || defined(_M_AMD64)
#  define F_LENGTH_T __int64
#elif defined (__INTEL_COMPILER)
#  define F_LENGTH_T long
#else
#  define F_LENGTH_T int
#endif

/* Fortran Stack Pointers */
#if defined(CFX_MMSPTR64) || defined(CFX5_ATTR_INT64)
#  if defined(_M_IX86) || defined(_M_X64) || defined(_M_AMD64)
typedef __int64 F_POINTER_T;
#  else
typedef long long F_POINTER_T;
#  endif
#else
typedef int F_POINTER_T;
#endif

/* Fortran Cray Pointers: Does not work yet */
#if defined(CFX_MMSPTR64)
#  if defined(_M_IX86) || defined(_M_X64) || defined(_M_AMD64)
typedef __int64 F_CRAY_PTR_T;
#  else
typedef long long F_CRAY_PTR_T;
#  endif
#else
typedef int F_CRAY_PTR_T;
#endif


/* Fortran 64-bit integers for Pointers */
#  if defined(_M_IX86) || defined(_M_X64) || defined(_M_AMD64)
typedef __int64 F_PTR64_T;
#  else
typedef long long F_PTR64_T;
#  endif

#endif /* _CFX_FPROTO_H */
