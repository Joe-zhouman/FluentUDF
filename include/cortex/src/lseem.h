/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#include "cxmacros.h"

#if _NT
#pragma warning(disable: 4135) /* conversion between different integral types */
#pragma warning(disable: 4136) /* conversion between different floating-point types */
#endif

#ifdef sgi    /* The default cc is -xansi (extended ansi), and    */
# ifndef __STDC__ /* __STDC__ is not defined.                         */
#  define __STDC__ 1  /* These lines are unnecessary if cc -ansi is used. */
# endif
#endif

#ifdef __osf__    /* The default cc is -std0 (K&R), but io.c will not  */
# ifndef __STDC__ /* compile without __STDC__ defined.                 */
#  define __STDC__ 1  /* These lines are unnecessary if cc -std1, is used. */
# endif
#endif


#ifdef __convex__       /* the default is extended ansi, which does not      */
# ifndef __STDC__       /* define __STDC__. If compiled with -std this is    */
#  define __STDC__ 1    /* unneccessary */
# endif
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#if !_NT 
#include <unistd.h>
#endif

#if _NT
#include <process.h>
#define chdir _chdir
#define getcwd  _getcwd
#define getpid  _getpid
/* #define stat _stat */
#define strdup  _strdup
#define S_IFDIR _S_IFDIR
#define putenv  _putenv
#endif /* _NT */

/* IBM RS/6000, iPSC/860, Convex compilers do not #define unix implicitly. */
#if defined(_AIX) || defined(i860) || defined(__unix__) || defined(__unix)
# ifndef unix
#  define unix 1
# endif
#endif

/* macros not defined in sys/stat.h on iPSC/860 */
#ifdef i860
# define  S_ISBLK(m)  (((m)&S_IFMT) == S_IFBLK)
# define  S_ISCHR(m)  (((m)&S_IFMT) == S_IFCHR)
# define  S_ISDIR(m)  (((m)&S_IFMT) == S_IFDIR)
# define  S_ISFIFO(m) (((m)&S_IFMT) == S_IFIFO)
#endif

/* Which slash and path separator is used? */
#if _NT
#  define SLASH '\\'
#  define PATH_SEP ';'
#endif
#if vms
#  define SLASH '.'
#  define PATH_SEP ','
#endif
#if unix
#  define SLASH '/'
#  define PATH_SEP ':'
#endif

#if unix
#define EXPAND_HOME 1
#endif

#include "seem.h"
