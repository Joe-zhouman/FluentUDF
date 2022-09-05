/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_GLOBAL_H
#define _FLUENT_GLOBAL_H

#if !UDF_COMPILER
# include <stdio.h>
#endif

#include "config.h"
#include "dll.h"
#include "cxbool.h"
#include "itype.h"

#if UDF_COMPILER
typedef void FILE;

FLUENT_EXPORT FILE *fopen(const char *filename, const char *type);
FLUENT_EXPORT int fclose(FILE *fd);
FLUENT_EXPORT int fprintf(FILE *fd, const char *format, ...);
FLUENT_EXPORT int printf(const char *format, ...);
FLUENT_EXPORT int fscanf(FILE *fd, const char *format, ...);

#endif /* UDF_COMPILER */

#if !UDF_COMPILER
#include <stdlib.h>
#include <stddef.h>
#endif

#if sys_lnamd64
#include <xmmintrin.h>
#endif


#if !UDF_COMPILER && !RP_DOUBLE && (sys_ultra || sys_ultra_64)
# include <sunmath.h>
# define sin(x) sinf(x)
# define cos(x) cosf(x)
# define tan(x) tanf(x)
# define exp(x) expf(x)
# define log(x) logf(x)
# define log10(x) log10f(x)
# define log1p(x) log1pf(x)
# define pow(x, y) powf(x, y)
# define sqrt(x) sqrtf(x)
# define ceil(x) ceilf(x)
# define fabs(x) fabsf(x)
# define floor(x) floorf(x)
# define fmod(x, y) fmodf(x, y)
#endif /* !UDF_COMPILER && !RP_DOUBLE && (sys_ultra || sys_ultra_64) */

#if !UDF_COMPILER
#if defined(RAG_TGMATH) && !defined(_UDF)
# include <tgmath.h>
# undef I
#else
# include <math.h>
#endif
#else /* UDF_COMPILER */
FLUENT_EXPORT double acos(double x);
FLUENT_EXPORT double asin(double x);
FLUENT_EXPORT double atan(double x);
FLUENT_EXPORT double atan2(double x, double y);
FLUENT_EXPORT double cos(double x);
FLUENT_EXPORT double sin(double x);
FLUENT_EXPORT double tan(double x);
FLUENT_EXPORT double cosh(double x);
FLUENT_EXPORT double sinh(double x);
FLUENT_EXPORT double tanh(double x);
FLUENT_EXPORT double sqrt(double x);
FLUENT_EXPORT double pow(double x, double y);
FLUENT_EXPORT double exp(double x);
FLUENT_EXPORT double log(double x);
FLUENT_EXPORT double log10(double x);
FLUENT_EXPORT double log1p(double x);
FLUENT_EXPORT double fabs(double x);
FLUENT_EXPORT double ceil(double x);
FLUENT_EXPORT double floor(double x);
#endif /* UDF_COMPILER */

#if RP_DOUBLE
# define REAL_MAX DBL_MAX
# define REAL_MIN DBL_MIN
# define EPSILON DBL_EPSILON
# define REAL_FORMAT "%lg"
#else
# define REAL_MAX FLT_MAX
# define REAL_MIN FLT_MIN
# define EPSILON FLT_EPSILON
# define REAL_FORMAT "%g"
#endif

#define FLT_EQUAL(r1,r2)              (ABS((r1) - (r2)) <= MAX(FLT_MIN,MAX(ABS(r1),ABS(r2)) * FLT_EPSILON))
#define DBL_EQUAL(r1,r2)              (ABS((r1) - (r2)) <= MAX(DBL_MIN,MAX(ABS(r1),ABS(r2)) * DBL_EPSILON))
#define REAL_EQUAL(r1,r2)             (ABS((r1) - (r2)) <= MAX(REAL_MIN,MAX(ABS(r1),ABS(r2)) * EPSILON))
#define REAL_EQUAL_SCALED(r1,r2,fact) (ABS((r1) - (r2)) <= MAX(REAL_MIN,MAX(ABS(r1),ABS(r2)) * EPSILON * (fact)))
#define SIGN(b)    ((b) >= 0. ? 1. : -1.)
#define SIGN2(a,b) (ABS(a) * SIGN(b))
#define ROUND(fp) (int)((fp) >= 0 ? (fp) + 0.5 : (fp) - 0.5)

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

#ifndef M_SQRT2
# define M_SQRT2 1.414213562373095048801689
#endif

#ifndef M_SQRT3
# define M_SQRT3 1.732050807568877293527446
#endif

#ifndef POST_REAL_MAX
# define POST_REAL_MAX 1.0e20
#endif

#ifndef POST_REAL_MIN
# define POST_REAL_MIN  (-1.0e20)
#endif

#if !UDF_COMPILER
# include <string.h>
# include <ctype.h>
# if _NT || sys_ntx86 || sys_win64
#  ifndef vsnprintf
/* so this applies even if the function vsnprintf is available,
 * just not as a macro but as a real, properly declared function..
 */
#   define vsnprintf _vsnprintf
/* beware -- _vsnprintf is dangerous:
 *  -- it returns -1 when the buffer is too small
 *  -- it does not necessarily write a terminating '\0'..!
 */
#  endif
#  ifndef snprintf
#   if _MSC_VER < 1900
#   define snprintf _snprintf
#   endif
#  endif
#  ifndef putenv
#   define putenv _putenv
#  endif
# else
#  ifndef __cplusplus
extern int snprintf (char *s, size_t maxlen, const char *format, ...);
extern int strcasecmp (const char *s1, const char *s2);
#  endif /* __cplusplus */
# endif
# ifndef stricmp
#  if _NT || sys_ntx86 || sys_win64
#   define stricmp _stricmp
#  else
#   define stricmp strcasecmp
#  endif
# endif
# ifndef STRIEQ
#  define STRIEQ(x,y) (0==stricmp((x),(y)))
# endif
#else
FLUENT_EXPORT char *strcat(char *dst, const char *src);
FLUENT_EXPORT char *strncat(char *dst, const char *src, size_t n);
FLUENT_EXPORT int strcmp(const char *s1, const char *s2);
FLUENT_EXPORT int strncmp(const char *s1, const char *s2, size_t n);
FLUENT_EXPORT char *strcpy(char *dst, const char *src);
FLUENT_EXPORT char *strncpy(char *dst, const char *src, size_t n);
FLUENT_EXPORT size_t strlen(const char *s);
#endif /* UDF_COMPILER */

#define STREQ(_s1,_s2)      (0 == strcmp ((_s1), (_s2)))
#define STRNEQ(_s1,_s2)     (0 != strcmp ((_s1), (_s2)))
#define STREQN(_s1,_s2,_n)  (0 == strncmp ((_s1), (_s2), (_n)))
#define STRNEQN(_s1,_s2,_n) (0 != strncmp ((_s1), (_s2), (_n)))

#if !UDF_COMPILER
#ifndef __convex__
# include <malloc.h>
#endif
#else /* UDF_COMPILER */
FLUENT_EXPORT void *malloc(size_t size);
FLUENT_EXPORT void *calloc(size_t nelem, size_t elsize);
FLUENT_EXPORT void free(void *ptr);
FLUENT_EXPORT void *realloc(void *ptr, size_t size);
#endif /* UDF_COMPILER */

#if !UDF_COMPILER
#if !CORTEX || RP_NODE
# include <setjmp.h>
#endif
#endif /* UDF_COMPILER */

#define NULLP(x)((x) == NULL)
#define NNULLP(x)((x) != NULL)

#if RP_DOUBLE
typedef double real;
# if sys_lnia64
/* typedef long double realplus; */
typedef double realplus;
# else
typedef double realplus;
# endif
#else
typedef float real;
# if sys_lnia64
typedef double realplus;
/* typedef float realplus; */
# else
typedef float realplus;
# endif
#endif

#if RP_3D
# define ND_ND 3
# define ND_VEC(x,y,z)x,y,z
#else
# define ND_ND 2
# define ND_VEC(x,y,z)x,y
#endif
#define ND_3 3
#define NV_VEC(a)a[ND_ND]


#if RP_DOUBLE
# define REAL_NODE_COORD(v)(NODE_COORD(v))
#else
# define REAL_NODE_COORD(v)(ND_VEC((real)NODE_COORD(v)[0],(real)NODE_COORD(v)[1],(real)NODE_COORD(v)[2]))
#endif


typedef real realVec[ND_ND];
typedef real realMat[ND_ND][ND_ND];


#if HPUX
/* HP decided to define MIN and MAX in sys/param.h,
 * which is included by <dl.h>.
 * Take advantage of the fact that sys/param.h is reloadable. */
# include <sys/param.h>
# undef MIN
# undef MAX
#endif

#define MAX(a,b)((b)>(a)?(b):(a))
#define MIN(a,b)((b)<(a)?(b):(a))
#define MIN3(a,b,c)((a)<(b)?((a)<(c)?(a):(c)):((b)<(c)?(b):(c)))
#define MAX3(a,b,c)((a)<(b)?((b)<(c)?(c):(b)):((a)<(c)?(c):(a)))
#define MINMAX(a,mn,mx)((a)<(mn)?(mn):((a)<(mx)?(a):(mx)))
#define ABS(a)(((a)<0)?-(a):(a))
#define SETMAX(a,b)((b)>(a)?(a=b):(a))
#define SETMIN(a,b)((b)<(a)?(a=b):(a))
/* a = b, if b < a; c = b, if b > c */
#define SETMINMAX( a, b, c) ((b) < (a) ? (a=b) : (b)), ((b) > (c) ? (c=b) : (b))
#define SQR(a)((a)*(a))
#define CUB(a)(SQR(a)*(a))
#define PW4(a)(CUB(a)*(a))
#define PW5(a)(PW4(a)*(a))
#define PW6(a)(PW5(a)*(a))

#define Internal_Error(s)internal_Error((s),__LINE__,__FILE__)
FLUENT_EXPORT void internal_Error(char *, int, char *);
#define Error Primitive_Error


FLUENT_EXPORT void Delay_Error(const char *, ...);

/* To throw an error and stop iterations,
 * but only at a code place where it will
 * not bail out of the depths of the code
 * and thus leave Fluent in a (potentially)
 * corrupt / inconsistent state...
 *
 * This will push out a message and set a flag
 * that is checked between iterations and when
 * TUI commands are expected or processed:
 */
#define DELAY_ERROR(format, ...)   \
  do {                              \
    CX_Warning("\nERROR: " format "\n", __VA_ARGS__); \
    Delay_Error(format, __VA_ARGS__); \
  } while (0)


#include "var.h"
#include "seem.h"
#include "cx.h"

FLUENT_EXPORT char *Fl_Getexecname(void);
FLUENT_EXPORT char *get_fluent_arch(void);
FLUENT_EXPORT char *get_fluent_inc(void);
FLUENT_EXPORT char *get_fluent_prod_dir(void);

#if MULTIPORT
# include "mport.h"
#endif

#ifndef ANSYS_FLUX
# include "mpthreads.h"
#endif

#if PURIFY_DEBUG
# include </usr/local/packages/pure/purify-4.2-solaris2/purify.h>
#endif

#if DEBUG
# include <assert.h>
# define   ASSERT(a) assert(a)
#else
# if 00   /* <--- set this to '11' to have assertions issue up to 100 messages in NON-DEBUG builds... */
#  define  ASSERT(a) \
           do {       \
             static int messleft = 100; \
             if (messleft &&  ! (a))     \
             {                            \
               CX_Message("\n\"non-fatal\" Error: On node-%d, file %s, line %d: assertion '%s' failed. Will go on...\n", \
                          myid, __FILE__, __LINE__, #a);   \
               --messleft; \
             }             \
           } while (0)
# else
# define   ASSERT(a)
#endif
#endif

/* Wrappers for disabling/restoring interrupts.
 * Insures that an inner scope does not enable interrupts when
 * and outer scope has disabled them.
 * Usage/format (the braces are required):
 *
 *   {
 *     DISABLE_INTERRUPTS();
 *
 *     statement;
 *     ...
 *     if (error)
 *       {
 *         RESTORE_INTERRUPTS();
 *         return;
 *       }
 *     statement;
 *
 *     RESTORE_INTERRUPTS();
 *   }
 */

#define DISABLE_INTERRUPTS() \
  volatile cxboolean _interrupts_were_on = interrupts_enabled(); \
  if (_interrupts_were_on) disable_interrupts()

#define RESTORE_INTERRUPTS() \
  if (_interrupts_were_on) enable_interrupts()

#define fl_interrupted CX_Check_Interrupt()

/* allow alternate ways of disabling/enabling interrupts. Eg.:
 *
 *  {
 *     Init_Interrupts();
 *     if (X)
 *       Disable_Interrupts();
 *
 *     ...
 *     ...
 *
 *     if (X)
 *       Restore_Interrupts();
 *  }
 */

#define Init_Interrupts() \
  cxboolean _interrupts_were_on = FALSE

#define Disable_Interrupts() \
  _interrupts_were_on = interrupts_enabled(); \
  if (_interrupts_were_on) disable_interrupts()

#define Restore_Interrupts() \
  if (_interrupts_were_on) enable_interrupts()

#define MTRACE_LOG_START(cmt) {char cmtline[1024] ; sprintf(cmtline,"%s Begins",(cmt)); setmtracelog(cmtline);}
#define MTRACE_LOG_STOP(cmt) {char cmtline[1024] ; sprintf(cmtline,"%s Ends",(cmt)); setmtracelog(cmtline);}

#if USE_INT64
#define INDEX_CAST(id) (((id)==0)?0:(((id)>0)?1:(-1)))
#else
#define INDEX_CAST(id) (id)
#endif

#define OMP_CHUNK 100

#if _OPENMP
# include <omp.h>
#define OMP_START \
{ \
    int n1omp = omp_get_num_threads(); \
    int n2omp = Get_OMP_Nthreads(); \
    if (n2omp>1) \
    { \
        omp_set_num_threads(n2omp); \
        MPT_Reset_Process_Affinity(TRUE); \
    }

#define OMP_STOP \
    if (n2omp>1)\
    { \
        omp_set_num_threads(n1omp); \
        if (n1omp==1) \
            MPT_Reset_Process_Affinity(FALSE); \
    } \
}
#else
#define OMP_START
#define OMP_STOP
#endif

#ifndef ALLOW_ONE_SIDED
#define ALLOW_ONE_SIDED 1
#endif /* ALLOW_ONE_SIDED */

#endif /* _FLUENT_GLOBAL_H */
