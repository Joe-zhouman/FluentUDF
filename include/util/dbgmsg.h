/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/********************************************************************/
/*
 * Macros for generating text output, e.g. for reporting.
 * But also useful for debugging possibly optimized code...
 *
 * by
 * Ulrich Becker,   ubecker@ansys.com
 */

#ifndef  _FLUENT_DBGMSG_H
#define  _FLUENT_DBGMSG_H

/* compiler flags to influence behaviour .. see below for use and consequences:
 *
 * DBGMSG_FP     a FILE pointer where to print to. Default is stdout.
 *
 *
 * DBGMSG_CX_MESSAGE_CMD
 * DBGMSG_USE_CX_MESSAGE
 * DBGMSG_ONLY_SINGLE_NODE   restrict to output from single compute node in PARALLEL
 *
 * DBGMSG_REAL_IS_FLOAT      by default real is treated as double
 */

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*
 *
 * Helper macros. NOT to be called directly ! ... usually ...
 */


#ifndef DBGMSG_CX_MESSAGE_CMD
/* only print from compute node 0:*/
/* #define DBGMSG_CX_MESSAGE_CMD Message0 */

/* OR print from all compute nodes: */
#  define DBGMSG_CX_MESSAGE_CMD CX_Message
#endif

#ifdef DBGMSG_ONLY_SINGLE_NODE /* define as node number from which to issue messages only */
#  define DBGMSG_EFFECTIVE_OUT(sexp) ( DBGMSG_ONLY_SINGLE_NODE == myid ? (sexp) : 0 )
#else
#  define DBGMSG_EFFECTIVE_OUT(sexp) (sexp)
#endif

#if DBGMSG_USE_CX_MESSAGE
#  ifdef DBGMSG_FP
#    warning "Using " DBGMSG_CX_MESSAGE_CMD " is enforced. Will not make use of definition of DBGMSG_FP."
#  endif
#  if PARALLEL
#    define dm_print1(a1         ) DBGMSG_EFFECTIVE_OUT(((DBGMSG_CX_MESSAGE_CMD("myid=%d::",myid)),(DBGMSG_CX_MESSAGE_CMD(a1         ))))
#    define dm_print2(a1,a2      ) DBGMSG_EFFECTIVE_OUT(((DBGMSG_CX_MESSAGE_CMD("myid=%d::",myid)),(DBGMSG_CX_MESSAGE_CMD(a1,a2      ))))
#    define dm_print3(a1,a2,a3   ) DBGMSG_EFFECTIVE_OUT(((DBGMSG_CX_MESSAGE_CMD("myid=%d::",myid)),(DBGMSG_CX_MESSAGE_CMD(a1,a2,a3   ))))
#    define dm_print4(a1,a2,a3,a4) DBGMSG_EFFECTIVE_OUT(((DBGMSG_CX_MESSAGE_CMD("myid=%d::",myid)),(DBGMSG_CX_MESSAGE_CMD(a1,a2,a3,a4))))
#  else /* serial */
#    define dm_print1(a1         ) (DBGMSG_CX_MESSAGE_CMD(a1         ))
#    define dm_print2(a1,a2      ) (DBGMSG_CX_MESSAGE_CMD(a1,a2      ))
#    define dm_print3(a1,a2,a3   ) (DBGMSG_CX_MESSAGE_CMD(a1,a2,a3   ))
#    define dm_print4(a1,a2,a3,a4) (DBGMSG_CX_MESSAGE_CMD(a1,a2,a3,a4))
#  endif
#else
#  ifndef DBGMSG_FP
#    if ( defined(_WIN32) || defined (WIN64) ) /* windows does not know stderr */
#      define DBGMSG_FP stdout
#    else
#      define DBGMSG_FP stdout
/* #      define DBGMSG_FP stderr */
#    endif
#  endif
#  if PARALLEL
/*   2010-12-07 Print myid only when printing to stdout. When printing to a file, assume that files are different for all compute nodes. Then myid must not clutter the text.*/
#    define dm_print1_buf(a1         ) DBGMSG_EFFECTIVE_OUT(((stdout == DBGMSG_FP ? fprintf(DBGMSG_FP,"myid=%d::",myid) : 0),(NULL != DBGMSG_FP ? fprintf(DBGMSG_FP,a1         ) : 0)))
#    define dm_print2_buf(a1,a2      ) DBGMSG_EFFECTIVE_OUT(((stdout == DBGMSG_FP ? fprintf(DBGMSG_FP,"myid=%d::",myid) : 0),(NULL != DBGMSG_FP ? fprintf(DBGMSG_FP,a1,a2      ) : 0)))
#    define dm_print3_buf(a1,a2,a3   ) DBGMSG_EFFECTIVE_OUT(((stdout == DBGMSG_FP ? fprintf(DBGMSG_FP,"myid=%d::",myid) : 0),(NULL != DBGMSG_FP ? fprintf(DBGMSG_FP,a1,a2,a3   ) : 0)))
#    define dm_print4_buf(a1,a2,a3,a4) DBGMSG_EFFECTIVE_OUT(((stdout == DBGMSG_FP ? fprintf(DBGMSG_FP,"myid=%d::",myid) : 0),(NULL != DBGMSG_FP ? fprintf(DBGMSG_FP,a1,a2,a3,a4) : 0)))
#  else /* serial */
#    define dm_print1_buf(a1         ) (NULL != DBGMSG_FP ? fprintf(DBGMSG_FP,a1         ) : 0)
#    define dm_print2_buf(a1,a2      ) (NULL != DBGMSG_FP ? fprintf(DBGMSG_FP,a1,a2      ) : 0)
#    define dm_print3_buf(a1,a2,a3   ) (NULL != DBGMSG_FP ? fprintf(DBGMSG_FP,a1,a2,a3   ) : 0)
#    define dm_print4_buf(a1,a2,a3,a4) (NULL != DBGMSG_FP ? fprintf(DBGMSG_FP,a1,a2,a3,a4) : 0)
#  endif
#  define dm_flush               (NULL != DBGMSG_FP ? fflush(DBGMSG_FP) : 0)
#  define dm_print1(a1         ) (dm_print1_buf(a1         ),dm_flush)
#  define dm_print2(a1,a2      ) (dm_print2_buf(a1,a2      ),dm_flush)
#  define dm_print3(a1,a2,a3   ) (dm_print3_buf(a1,a2,a3   ),dm_flush)
#  define dm_print4(a1,a2,a3,a4) (dm_print4_buf(a1,a2,a3,a4),dm_flush)
#endif

/* Print an entire real vector in one line, possibly preceeded by the variable name.
 * Save on the digits printed for legibility!
 *
 * tof==TrueOrFalse to print or not to print the variable name.
 */
#define dm_rvecmsg(n, V, tof)                   \
{                                               \
  int _ii;                                      \
  if (tof) dm_print2("%s: ",#V);                \
  for(_ii=0; _ii<n; _ii++)                      \
    dm_print2_buf("%8.5e   ",V[_ii]);           \
  if (tof) nlmsg;                               \
  dm_flush;                                     \
}

#define dm_lvecmsg(n, V, tof)                   \
{                                               \
  int _ii;                                      \
  if (tof) dm_print2("%s: ",#V);                \
  for(_ii=0; _ii<n; _ii++)                      \
    dm_print2_buf("%"int64_fmt"   ",V[_ii]);    \
  if (tof) nlmsg;                               \
  dm_flush;                                     \
}

/* bare bones version for any sort of vector or formatting: */
#define dm_fmtvecmsg(fmt,n, V, tof)   \
{                                               \
  int _ii;                                      \
  if (tof) dm_print2("%s: ",#V);                \
  for(_ii=0; _ii<n; _ii++)                      \
    dm_print2_buf(fmt,V[_ii]);      \
  if (tof) nlmsg;                               \
  dm_flush;                                     \
}

/* Print an entire real vector in one line, possibly preceeded by the variable name.
 * Print all the digits!
 *
 * tof==TrueOrFalse to print or not to print the variable name.
 */
#define dm_rrvecmsg(n, V, tof)                  \
{                                               \
  int _ii;                                      \
  if (tof) dm_print2("%s: ",#V);                \
  for(_ii=0; _ii<n; _ii++)                      \
    ((sizeof(real)==sizeof(double)) ?           \
     dm_print2_buf("%24.16e \t", V[_ii]) :      \
     dm_print2_buf("%16.8e \t" , V[_ii]) );     \
  if (tof) nlmsg;                               \
  dm_flush;                                     \
}


/* Print an entire real matrix, line by line, possibly preceeded by the variable name.
 * Save on the digits printed for legibility!
 *
 * tof==TrueOrFalse to print or not to print the variable name.
 */
#define dm_rmatmsg(m, n, M, tof)                \
{                                               \
  int _ii,_jj;                                  \
                                                \
  if (tof) dm_print2("%s: ",#M);                \
  if (tof) nlmsg;                               \
  for(_ii=0; _ii<m; _ii++)                      \
  {                                             \
    /* real *M##_ii=&M[_ii*n];  */              \
    for(_jj=0; _jj<n; _jj++)                    \
    {                                           \
      dm_print2_buf("%8.2g   ",M[_ii][_jj]);    \
      if ((n-1) == _jj) nlmsg;                  \
    }                                           \
  }                                             \
  if (tof) nlmsg;                               \
  dm_flush;                                     \
}
#ifndef int64_fmt
# if (_lnamd64)
#  define int64_fmt "ld"
# else
#  define int64_fmt "lld"
# endif
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* need to provide "real" for non-fluent code:
 */
#ifndef _FLUENT_CONFIG_H
# if DBGMSG_REAL_IS_FLOAT
#  define real float
# else
#  define real double
# endif
#endif

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*
 *
 * Macros to be called directly.
 *
 * Generally:
 *   macros containing   ..msg()   will print the variable name together with its value.
 *   macros containing   ..val()   will only print the value.

 * Exception:
 *   msg     prints the message string provided as argument
 *   nlmsg   prints a line break
 *   tabmsg  prints a tab
 */

#define msg(s) dm_print1(s)    /* s is a string */
#define nlmsg  dm_print1("\n")
#define tabmsg dm_print1("\t")


/* boolean is cx_boolean in FLUENT
 */
#define bmsg(b)         ((b) ? dm_print2("%-s = true \t", #b) : dm_print2("%-s = false \t", #b))

/* int
 */
#define imsg(i)          dm_print3("%-s = %d \t", #i, i)
#define imsgw(i,w)       dm_print3("%s = %"#w"d  ", #i, i)
#define imsg3(i)         imsgw(i,3)
#define ivmsg(v,i)       dm_print4("%-s[%2d] = %d \t", #v, i, v[i])           /* vector component i of integer vector */

#define ival(i)          dm_print2("%d \t", i)
#define ivalw(i,w)       dm_print2("%"#w"d  ", i)
#define ival3(i)         ivalw(i,3)
#define ivval(v,i)       dm_print2("%d \t", v[i])                             /* vector component i of integer vector */

/* long is int64_t in FLUENT
 */
#define lmsg(i)          dm_print3("%-s = %"int64_fmt" \t", #i, i)
#define lmsgw(i,w)       dm_print3("%s = %"#w""int64_fmt"  ", #i, i)
#define lmsg3(i)         lmsgw(i,3)
#define lvmsg(v,i)       dm_print4("%-s[%2d] = %"int64_fmt" \t", #v, i, v[i]) /* vector component i of long vector */

#define lval(i)          dm_print2("%"int64_fmt" \t", i)
#define lvalw(i,w)       dm_print2("%"#w""int64_fmt"  ", i)
#define lval3(i)         lmsgw(i,3)
#define lvval(v,i)       dm_print2("%%"int64_fmt" \t", v[i])                  /* vector component i of long vector */
#define lvecmsg(n, V)    dm_lvecmsg(n, V, TRUE)   /* entire long vector */
#define lvecval(n, V)    dm_lvecmsg(n, V, FALSE)  /* entire long vector */


/* real
 */
#define rmsg(r)          dm_print3("%-s = %12.4e \t", #r, r)
#define rmsgw(r,w)       dm_print3("%"#w"s = %12.4e \t", #r, r)
#define rmsg7(r)         rmsgw(r,7)
#define rmsgX(r)         rmsgw(r,10)
#define rvmsg(v,i)       dm_print4("%-s[%2d] = %12.4e \t", #v, i, v[i])       /* vector component i of real vector */

#define rval(r)          dm_print2("%12.4e \t", r)
#define rvval(v,i)       dm_print2("%%12.4e \t", v[i])                        /* vector component i of real vector */

#define rvecmsg(n, V)    dm_rvecmsg(n, V, TRUE)   /* entire real vector */
#define rvecval(n, V)    dm_rvecmsg(n, V, FALSE)  /* entire real vector */

#define rmatmsg(m, n, M) dm_rmatmsg(m, n, M, TRUE)  /* entire real matrix */
#define rmatval(m, n, M) dm_rmatmsg(m, n, M, FALSE) /* entire real matrix */


/* show all the digits in a real number:  rr == really_real
 */
#define rrmsg(r)        ((sizeof(real)==sizeof(double)) ?       \
                         dm_print3("%-s = %24.16e \t", #r, r) : \
                         dm_print3("%-s = %16.8e \t" , #r, r) )
#define rrvmsg(v,i)     ((sizeof(real)==sizeof(double)) ?                       \
                         dm_print4("%-s[%2d] = %24.16e \t", #v, i, v[i]) :      \
                         dm_print4("%-s[%2d] = %16.8e \t" , #v, i, v[i]) )

#define rrval(r)        ((sizeof(real)==sizeof(double)) ?       \
                         dm_print2("%24.16e \t", r) :           \
                         dm_print2("%16.8e \t" , r) )
#define rrvval(v,i)     ((sizeof(real)==sizeof(double)) ?       \
                         dm_print2("%24.16e \t", v[i]) :        \
                         dm_print2("%16.8e \t" , v[i]) )

#define rrvecmsg(n, V)  dm_rrvecmsg(n, V, TRUE)   /* entire real vector with all its digits */
#define rrvecval(n, V)  dm_rrvecmsg(n, V, FALSE)  /* entire real vector with all its digits  */

/* 2010-05-07 Nothing for really real matices ... yet. */


/* string variables
 */
#define smsg(s)         dm_print3("%-s : %-s \t", #s, s)
#define smsgw(s,w1,w2)  dm_print3("%-"#w1"s : %-"#w2"s \t", #s, s)
#define sval(s)         dm_print2("%-s \t", s)            /* other than msg(), this includes tab alignment */

/* enums
 */
#define enmsg(e)        dm_print3("%-3d %-20s \t", e, #e)

/* function name and location
 */
#define fmsg(f)         dm_print4("%-s (%s:%d): \t", #f, __FILE__ , __LINE__)
#define fmsgline(f)     dm_print4("\n%-s (%s:%d): ----------------------------------------------------------------------\n", #f, __FILE__ , __LINE__)



/* FLUENT data types ... only available with FLUENT headers.
 */

#define tmsg(t)         dm_print2("t-id: %d \t",THREAD_ID(t))

#define udsmsg(c,t,enm) dm_print3("%s =%12.4e \t", #enm, C_UDSI(c,t,enm))      /* Cell values of UDS */
#define udmmsg(c,t,enm) dm_print3("%s =%12.4e \t", #enm, C_UDMI(c,t,enm))      /* Cell values of UDM */
#define svmsg(c,t,sv)   dm_print3("%s =%12.4e \t", #sv,  C_STORAGE_R(c,t,sv))  /* Cell values of SVar */

#define svenmsg(sv)     dm_print4("%s = %-4d (%s) \t", #sv, sv, sv_master[sv].print_name) /* name, value, and print-name of storage variable */


#define DBGMSG_PMYID_FMT "%-5d"
#if PARALLEL
#  if (DBGMSG_USE_CX_MESSAGE && DBGMSG_CX_MESSAGE_CMD == CX_Message0)
#    warning "Using CX_Message0. Will not print compute node IDs. Consider redefining DBGMSG_CX_MESSAGE_CMD."
#  else
#    define myidmsg imsg(DBGMSG_PMYID_FMT,myid)
#  endif
#else
#  define myidmsg
#endif


#endif  /* _FLUENT_DBGMSG_H */
