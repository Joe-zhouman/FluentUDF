#ifndef _INCLUDED_PRF_H
# define _INCLUDED_PRF_H
/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_PRF_H
#define _FLUENT_PRF_H

#include "dll.h"

#if PARALLEL

# define PRF_GIAND1_WITH_HOST MPT_GIAND1_WITH_HOST
# define PRF_GIOR1_WITH_HOST MPT_GIOR1_WITH_HOST
# define PRF_GIHIGH1_WITH_HOST MPT_GIHIGH1_WITH_HOST
# define PRF_GLHIGH1_WITH_HOST MPT_GLHIGH1_WITH_HOST
# define PRF_GI64HIGH1_WITH_HOST prf_gi64high1_with_host
/* Since cx.h now verifies that sizeof(int64_t) == sizeof(long long),
 * we could now replace prf_gi64high1_with_host by MPT_GLLHIGH1_WITH_HOST
 * (*double* 'L'..! --- yet to be implemented properly in multiport...).
 */
# define PRF_GSYNC_WITH_HOST()                                         \
  {                                                                    \
     static int _id = -1;                                              \
     unsigned char if_use_profile = MPT_get_profile_flag();            \
     double _f = if_use_profile?MPT_wall_time():0.0;                   \
     MPT_GSYNC_WITH_HOST();                                            \
     if(if_use_profile) {                                              \
        log_time_used(                                                 \
          0, &_id, _f, MPT_wall_time(),                                \
          "PRF_GSYNC_WITH_HOST", __FILE__, __LINE__, __LINE__, TRUE);  \
     }                                                                 \
  }

# define PRF_ANYONE(arg,with_host) ((with_host) ? PRF_GIOR1_WITH_HOST(arg) : PRF_GIOR1(arg))
# define PRF_EVERYONE(arg,with_host) ((with_host) ? PRF_GIAND1_WITH_HOST(arg) : PRF_GIAND1(arg))

# define PRF_CSEND_BOOLEAN(a,b,c,d) MPT_CSEND_INT(a,(int *)(b),c,d)
# define PRF_CRECV_BOOLEAN(a,b,c,d) MPT_CRECV_INT(a,(int *)(b),c,d)
# define PRF_CSEND_CHAR             MPT_CSEND_CHAR
# define PRF_CRECV_CHAR             MPT_CRECV_CHAR
# define PRF_CSEND_INT              MPT_CSEND_INT
# define PRF_CRECV_INT              MPT_CRECV_INT
# define PRF_CSEND_LONG             MPT_CSEND_LONG
# define PRF_CRECV_LONG             MPT_CRECV_LONG
# define PRF_CSEND_LONG_LONG        MPT_CSEND_LONG_LONG
# define PRF_CRECV_LONG_LONG        MPT_CRECV_LONG_LONG
# define PRF_CSEND_FLOAT            MPT_CSEND_FLOAT
# define PRF_CRECV_FLOAT            MPT_CRECV_FLOAT
# define PRF_CSEND_DOUBLE           MPT_CSEND_DOUBLE
# define PRF_CRECV_DOUBLE           MPT_CRECV_DOUBLE
# define PRF_CSEND_SIZE_T           MPT_CSEND_SIZE_T
# define PRF_CRECV_SIZE_T           MPT_CRECV_SIZE_T
/* A static assertion (STATIC_ASSERT(..., ...))
 * in cx.h ensures the following equivalences: */
# define PRF_CSEND_INT64(i,d,n,t)   PRF_CSEND_LONG_LONG(i,((long long *)(d)),n,t)  /* prf_csend_int64 */
# define PRF_CRECV_INT64(i,d,n,t)   PRF_CRECV_LONG_LONG(i,((long long *)(d)),n,t)  /* prf_crecv_int64 */

/* Assume that sending 1000 (or what number should we use??) INTs takes hardly any longer than sending one INT: */
# define PRF_CSR_N_INT_N  1000
# define PRF_CSEND_N_INT(i, n, d, t)                            \
  {                                                              \
    int todo = *(n);                                              \
    int mybuff[PRF_CSR_N_INT_N + 1];                               \
    *mybuff = todo;                                                 \
    if (todo > PRF_CSR_N_INT_N)                                      \
      todo = PRF_CSR_N_INT_N;                                         \
    if (0 < todo)                                                      \
      memcpy(mybuff + 1, (d), todo * sizeof(int));                      \
    if (todo < PRF_CSR_N_INT_N)                                          \
      memset((char *)((int *)mybuff + 1 + todo),                          \
             0, (PRF_CSR_N_INT_N - todo) * sizeof (int));                  \
    PRF_CSEND_INT((i), mybuff, PRF_CSR_N_INT_N + 1, (t));                   \
    if (*(n) > PRF_CSR_N_INT_N)                                              \
      PRF_CSEND_INT((i), (d) + PRF_CSR_N_INT_N, *(n) - PRF_CSR_N_INT_N, (t)); \
  }

#define PRF_CRECV_N_INT(i, n, d, t)                                  \
  {                                                                   \
    int todo;                                                          \
    int mybuff[PRF_CSR_N_INT_N + 1];                                    \
    PRF_CRECV_INT((i), mybuff, PRF_CSR_N_INT_N + 1, (t));                \
    *(n) = *mybuff;                                                       \
    (d) = CX_Realloc((d), sizeof(int) * *mybuff);                          \
    todo = *mybuff;                                                         \
    if (todo > PRF_CSR_N_INT_N)                                              \
      todo = PRF_CSR_N_INT_N;                                                 \
    if (0 < todo)                                                              \
      memcpy((d), mybuff + 1, todo * sizeof(int));                              \
    if (*mybuff > PRF_CSR_N_INT_N)                                               \
      PRF_CRECV_INT((i), (d) + PRF_CSR_N_INT_N, *mybuff - PRF_CSR_N_INT_N, (t));  \
  }


# define PRF_ISEND_BOOLEAN(a,b,c,d) MPT_ISEND_INT(a,(int *)(b),c,d)
# define PRF_IRECV_BOOLEAN(a,b,c,d) MPT_IRECV_INT(a,(int *)(b),c,d)
# define PRF_ISEND_CHAR             MPT_ISEND_CHAR
# define PRF_IRECV_CHAR             MPT_IRECV_CHAR
# define PRF_ISEND_SHORT            MPT_ISEND_SHORT
# define PRF_IRECV_SHORT            MPT_IRECV_SHORT
# define PRF_ISEND_INT              MPT_ISEND_INT
# define PRF_IRECV_INT              MPT_IRECV_INT
# define PRF_ISEND_LONG             MPT_ISEND_LONG
# define PRF_IRECV_LONG             MPT_IRECV_LONG
# define PRF_ISEND_LONG_LONG        MPT_ISEND_LONG_LONG
# define PRF_IRECV_LONG_LONG        MPT_IRECV_LONG_LONG
# define PRF_ISEND_FLOAT            MPT_ISEND_FLOAT
# define PRF_IRECV_FLOAT            MPT_IRECV_FLOAT
# define PRF_ISEND_DOUBLE           MPT_ISEND_DOUBLE
# define PRF_IRECV_DOUBLE           MPT_IRECV_DOUBLE
# define PRF_ISEND_SIZE_T           MPT_ISEND_SIZE_T
# define PRF_IRECV_SIZE_T           MPT_IRECV_SIZE_T
#if RP_HOST
# define PRF_WAIT_ALL               MPT_Waitall
#else
# define PRF_WAIT_ALL()                                            \
  {                                                                \
     static int _id = -1;                                          \
     unsigned char if_use_profile = MPT_get_profile_flag();        \
     double _f = if_use_profile?MPT_wall_time():0.0;               \
     MPT_Waitall();                                                \
     if(if_use_profile) {                                          \
        log_time_used(                                             \
          0, &_id, _f, MPT_wall_time(),                            \
          "PRF_WAIT_ALL", __FILE__, __LINE__, __LINE__, TRUE);     \
     }                                                             \
  }
#endif
# define PRF_SEND_STATUS            MPT_Send_Status
# define PRF_RECV_STATUS            MPT_Recv_Status
# define PRF_WAIT_SEND              MPT_Wait_Send
# define PRF_WAIT_RECV              MPT_Wait_Recv

#define MPT_SEND(a,b,c,d,e)                             \
  if(0<parallel.comm_type)MPT_Isend(a,b,c,d,e); \
  else MPT_Csend(a,b,c,d,e);
# define PRF_SEND_CHAR(a,b,c,d)       \
  if(0<parallel.comm_type)PRF_ISEND_CHAR(a,b,c,d);  \
  else PRF_CSEND_CHAR(a,b,c,d);
# define PRF_SEND_INT(a,b,c,d)        \
  if(0<parallel.comm_type)PRF_ISEND_INT(a,b,c,d); \
  else PRF_CSEND_INT(a,b,c,d);
# define PRF_SEND_LONG(a,b,c,d)       \
  if(0<parallel.comm_type)PRF_ISEND_LONG(a,b,c,d);  \
  else PRF_CSEND_LONG(a,b,c,d);
# define PRF_SEND_LONG_LONG(a,b,c,d)                            \
  if(0<parallel.comm_type)PRF_ISEND_LONG_LONG(a,b,c,d); \
  else PRF_CSEND_LONG_LONG(a,b,c,d);
# define PRF_SEND_FLOAT(a,b,c,d)      \
  if(0<parallel.comm_type)PRF_ISEND_FLOAT(a,b,c,d); \
  else PRF_CSEND_FLOAT(a,b,c,d);
# define PRF_SEND_DOUBLE(a,b,c,d)     \
  if(0<parallel.comm_type)PRF_ISEND_DOUBLE(a,b,c,d);  \
  else PRF_CSEND_DOUBLE(a,b,c,d);
# define PRF_SEND_SIZE_T(a,b,c,d)     \
  if(0<parallel.comm_type)PRF_ISEND_SIZE_T(a,b,c,d);  \
  else PRF_CSEND_SIZE_T(a,b,c,d);

#define MPT_RECV(a,b,c,d,e)                             \
  if(0<parallel.comm_type)MPT_Irecv(a,b,c,d,e);      \
  else MPT_Crecv(a,b,c,d,e);
# define PRF_RECV_CHAR(a,b,c,d)       \
  if(0<parallel.comm_type)PRF_IRECV_CHAR(a,b,c,d);  \
  else PRF_CRECV_CHAR(a,b,c,d);
# define PRF_RECV_INT(a,b,c,d)        \
  if(0<parallel.comm_type)PRF_IRECV_INT(a,b,c,d); \
  else PRF_CRECV_INT(a,b,c,d);
# define PRF_RECV_LONG(a,b,c,d)       \
  if(0<parallel.comm_type)PRF_IRECV_LONG(a,b,c,d);  \
  else PRF_CRECV_LONG(a,b,c,d);
# define PRF_RECV_LONG_LONG(a,b,c,d)                            \
  if(0<parallel.comm_type)PRF_IRECV_LONG_LONG(a,b,c,d); \
  else PRF_CRECV_LONG_LONG(a,b,c,d);
# define PRF_RECV_FLOAT(a,b,c,d)      \
  if(0<parallel.comm_type)PRF_IRECV_FLOAT(a,b,c,d); \
  else PRF_CRECV_FLOAT(a,b,c,d);
# define PRF_RECV_DOUBLE(a,b,c,d)     \
  if(0<parallel.comm_type)PRF_IRECV_DOUBLE(a,b,c,d);  \
  else PRF_CRECV_DOUBLE(a,b,c,d);
# define PRF_RECV_SIZE_T(a,b,c,d)     \
  if(0<parallel.comm_type)PRF_IRECV_SIZE_T(a,b,c,d);  \
  else PRF_CRECV_SIZE_T(a,b,c,d);

# define PRF_CPASS_STRUCT_INT       MPT_CPASS_STRUCT_INT
# define PRF_CPASS_STRUCT_LONG      MPT_CPASS_STRUCT_LONG
# define PRF_CPASS_STRUCT_LONG_LONG MPT_CPASS_STRUCT_LONG_LONG
# define PRF_CPASS_STRUCT_FLOAT     MPT_CPASS_STRUCT_FLOAT
# define PRF_IPROBE       MPT_IPROBE
# define PRF_RESET_COMM       MPT_RESET_COMM

# define PRF_CPASS_STRUCT_DOUBLE    MPT_CPASS_STRUCT_DOUBLE

# define PRF_CSEND_STRUCT_INT       MPT_CSEND_STRUCT_INT
# define PRF_CSEND_STRUCT_LONG      MPT_CSEND_STRUCT_LONG
# define PRF_CSEND_STRUCT_LONG_LONG MPT_CSEND_STRUCT_LONG_LONG
# define PRF_CSEND_STRUCT_FLOAT     MPT_CSEND_STRUCT_FLOAT
# define PRF_CSEND_STRUCT_DOUBLE    MPT_CSEND_STRUCT_DOUBLE
# define PRF_CRECV_STRUCT_INT       MPT_CRECV_STRUCT_INT
# define PRF_CRECV_STRUCT_LONG      MPT_CRECV_STRUCT_LONG
# define PRF_CRECV_STRUCT_LONG_LONG MPT_CRECV_STRUCT_LONG_LONG
# define PRF_CRECV_STRUCT_FLOAT     MPT_CRECV_STRUCT_FLOAT
# define PRF_CRECV_STRUCT_DOUBLE    MPT_CRECV_STRUCT_DOUBLE


# define PRF_swap_int          MPT_swap_int
# define PRF_swap_struct_int     MPT_swap_struct_int
# define PRF_swap_float          MPT_swap_float
# define PRF_swap_struct_float   MPT_swap_struct_float
# define PRF_swap_double         MPT_swap_double
# define PRF_swap_struct_double  MPT_swap_struct_double

# if RP_DOUBLE

#  define PRF_swap_real          MPT_swap_double
#  define PRF_swap_struct_real   MPT_swap_struct_double
#  define PRF_CPASS_STRUCT_REAL  MPT_CPASS_STRUCT_DOUBLE
#  define PRF_CSEND_STRUCT_REAL  MPT_CSEND_STRUCT_DOUBLE
#  define PRF_CRECV_STRUCT_REAL  MPT_CRECV_STRUCT_DOUBLE
#  define MPT_PACK_REAL          MPT_PACK_DOUBLE

#  define PRF_CRECV_REAL   PRF_CRECV_DOUBLE
#  define PRF_CSEND_REAL   PRF_CSEND_DOUBLE
#  define PRF_IRECV_REAL   PRF_IRECV_DOUBLE
#  define PRF_ISEND_REAL   PRF_ISEND_DOUBLE
#  define PRF_RECV_REAL          PRF_RECV_DOUBLE
#  define PRF_SEND_REAL          PRF_SEND_DOUBLE

#  define PRF_S_CRECV_REAL   PRF_S_CRECV_DOUBLE
#  define PRF_S_CSEND_REAL   PRF_S_CSEND_DOUBLE
#  define PRF_S_IRECV_REAL   PRF_S_IRECV_DOUBLE
#  define PRF_S_ISEND_REAL   PRF_S_ISEND_DOUBLE

# else

#  define PRF_swap_real          MPT_swap_float
#  define PRF_swap_struct_real   MPT_swap_struct_float
#  define PRF_CPASS_STRUCT_REAL  MPT_CPASS_STRUCT_FLOAT
#  define PRF_CSEND_STRUCT_REAL  MPT_CSEND_STRUCT_FLOAT
#  define PRF_CRECV_STRUCT_REAL  MPT_CRECV_STRUCT_FLOAT
#  define MPT_PACK_REAL          MPT_PACK_FLOAT

#  define PRF_CRECV_REAL   PRF_CRECV_FLOAT
#  define PRF_CSEND_REAL   PRF_CSEND_FLOAT
#  define PRF_IRECV_REAL   PRF_IRECV_FLOAT
#  define PRF_ISEND_REAL   PRF_ISEND_FLOAT
#  define PRF_RECV_REAL          PRF_RECV_FLOAT
#  define PRF_SEND_REAL          PRF_SEND_FLOAT

#  define PRF_S_CRECV_REAL   PRF_S_CRECV_FLOAT
#  define PRF_S_CSEND_REAL   PRF_S_CSEND_FLOAT
#  define PRF_S_IRECV_REAL   PRF_S_IRECV_FLOAT
#  define PRF_S_ISEND_REAL   PRF_S_ISEND_FLOAT

# endif /* RP_DOUBLE */

# define PRF_CSEND_UCHAR       PRF_CSEND_CHAR
# define PRF_CRECV_UCHAR       PRF_CRECV_CHAR
# define PRF_ISEND_UCHAR       PRF_ISEND_CHAR
# define PRF_IRECV_UCHAR       PRF_IRECV_CHAR
# define PRF_SEND_UCHAR        PRF_SEND_CHAR
# define PRF_RECV_UCHAR        PRF_RECV_CHAR

# define PRF_CSEND_UINT        PRF_CSEND_INT
# define PRF_CRECV_UINT        PRF_CRECV_INT
# define PRF_ISEND_UINT        PRF_ISEND_INT
# define PRF_IRECV_UINT        PRF_IRECV_INT
# define PRF_SEND_UINT         PRF_SEND_INT
# define PRF_RECV_UINT         PRF_RECV_INT

#else
/* !PARALLEL */

# define PRF_GIAND1_WITH_HOST(thunk) (thunk)
# define PRF_GIOR1_WITH_HOST(thunk) (thunk)
# define PRF_GSYNC_WITH_HOST()

# define PRF_ANYONE(thunk,with_host) (thunk)
# define PRF_EVERYONE(thunk,with_host) (thunk)

#endif /* PARALLEL */


# define PRF_GBAND1 PRF_GIAND1
# define PRF_GBOR1  PRF_GIOR1

/* B for boolean -- elsewhere L for logical --
 * do not mix with B for bitwise (mostly after
\* UI for unsigned int or UC for unsignec char) */
# define PRF_GBAND  PRF_GIAND
# define PRF_GBOR   PRF_GIOR

# define PRF_GBOR2  PRF_GIOR2
# define PRF_GBOR3  PRF_GIOR3
# define PRF_GBOR4  PRF_GIOR4

# define PRF_GBAND2 PRF_GIAND2
# define PRF_GBAND3 PRF_GIAND3
# define PRF_GBAND4 PRF_GIAND4

# define PRF_GBOR1_WITH_HOST  PRF_GIOR1_WITH_HOST
# define PRF_GBAND1_WITH_HOST PRF_GIAND1_WITH_HOST


#if RP_NODE

# define PRF_GSYNC()                                               \
  {                                                                \
     static int _id = -1;                                          \
     unsigned char if_use_profile = MPT_get_profile_flag();        \
     double _f = if_use_profile?MPT_wall_time():0.0;               \
     MPT_GSYNC();                                                  \
     if(if_use_profile) {                                          \
        log_time_used(                                             \
          0, &_id, _f, MPT_wall_time(),                            \
          "PRF_GSYNC", __FILE__, __LINE__, __LINE__, TRUE);        \
     }                                                             \
  }
# define PRF_GIAND1(a)           MPT_GIAND1(a)
# define PRF_GIOR1(a)            MPT_GIOR1(a)
/* efine PRF_GLAND1(a)           MPT_GLAND1(a) --- used to work in int, now works on long; currently not used. Uncomment if needed! */
/* efine PRF_GLOR1(a)            MPT_GLOR1(a) --- used to work in int, now works on long; currently not used. Uncomment if needed! */
# define PRF_GLLAND1(a)          MPT_GLLAND1(a)
# define PRF_GLLOR1(a)           MPT_GLLOR1(a)
# define PRF_GIHIGH1             MPT_GIHIGH1
# define PRF_GILOW1              MPT_GILOW1
# define PRF_GISUM1              MPT_GISUM1
# define PRF_GISUM1_0            MPT_GISUM1_0
# define PRF_PISUM1              MPT_PISUM1
# define PRF_GLHIGH1             MPT_GLHIGH1
# define PRF_GLLOW1              MPT_GLLOW1
# define PRF_GLSUM1              MPT_GLSUM1
# define PRF_GLLHIGH1            MPT_GLLHIGH1
# define PRF_GLLLOW1             MPT_GLLLOW1
# define PRF_GLLSUM1             MPT_GLLSUM1
# define PRF_GTHIGH1             MPT_GTHIGH1
# define PRF_GTLOW1              MPT_GTLOW1
# define PRF_GTSUM1              MPT_GTSUM1
/* A static assertion (STATIC_ASSERT(..., ...))
 * in cx.h ensures the following equivalences: */
# define PRF_GI64HIGH1(a)        ((long long) PRF_GLLHIGH1((long long)(a)))
# define PRF_GI64LOW1(a)         ((long long) PRF_GLLLOW1((long long)(a)))
# define PRF_GI64SUM1(a)         ((long long) PRF_GLLSUM1((long long)(a)))  /* prf_gi64sum1 */
# define PRF_PLSUM1              MPT_PLSUM1
# define PRF_PLLSUM1             MPT_PLLSUM1
# define PRF_PTSUM1              MPT_PTSUM1
# define PRF_GDHIGH1             MPT_GDHIGH1
# define PRF_GDLOW1              MPT_GDLOW1
# define PRF_GDSUM1              MPT_GDSUM1
# define PRF_GSHIGH1             MPT_GSHIGH1
# define PRF_GSLOW1              MPT_GSLOW1
# define PRF_GSSUM1              MPT_GSSUM1
# define PRF_GIHIGH              MPT_GIHIGH
# define PRF_GILOW               MPT_GILOW
# define PRF_GISUM               MPT_GISUM
# define PRF_GLHIGH              MPT_GLHIGH
# define PRF_GLLOW               MPT_GLLOW
# define PRF_GLSUM               MPT_GLSUM
# define PRF_GLLHIGH             MPT_GLLHIGH
# define PRF_GLLLOW              MPT_GLLLOW
# define PRF_GLLSUM              MPT_GLLSUM
# define PRF_GTHIGH              MPT_GTHIGH
# define PRF_GTLOW               MPT_GTLOW
# define PRF_GTSUM               MPT_GTSUM
# define PRF_PTSUM               MPT_PTSUM
/* A static assertion (STATIC_ASSERT(..., ...))
 * in cx.h ensures the following equivalences: */
# define PRF_GI64HIGH(x,n,w)     PRF_GLLHIGH((long long *)(x), n, (long long *)(w))
# define PRF_GI64LOW(x,n,w)      PRF_GLLLOW((long long *)(x), n, (long long *)(w))
# define PRF_GI64SUM(x,n,w)      PRF_GLLSUM((long long *)(x), n, (long long *)(w))
# define PRF_GSHIGH              MPT_GSHIGH
# define PRF_GSLOW               MPT_GSLOW
# define PRF_GSSUM               MPT_GSSUM
# define PRF_GDHIGH              MPT_GDHIGH
# define PRF_GDLOW               MPT_GDLOW
# define PRF_GDSUM               MPT_GDSUM
# define PRF_GIOR                MPT_GIOR
/* efine PRF_GLOR                MPT_GLOR --- used to work in int, now works on long; currently not used. Uncomment if needed! */
# define PRF_GLLOR               MPT_GLLOR
# define PRF_GIAND               MPT_GIAND
/* efine PRF_GLAND               MPT_GLAND --- used to work in int, now works on long; currently not used. Uncomment if needed! */
# define PRF_GLLAND              MPT_GLLAND
# define PRF_GUCBOR              MPT_GUCBOR    /* bitwise OR */
# define PRF_GUCBAND             MPT_GUCBAND   /* bitwise AND */
# define PRF_GUIBOR              MPT_GUIBOR    /* bitwise OR */
# define PRF_GUIBAND             MPT_GUIBAND   /* bitwise AND */

# define PRF_BCAST_INT(x,n,r)    MPT_REDUCE(x,n,NULL,MPT_INT,MPT_BCAST,r)
# define PRF_BCAST_UINT(x,n,r)   MPT_REDUCE(x,n,NULL,MPT_UINT,MPT_BCAST,r)
# define PRF_BCAST_UCHAR(x,n,r)  MPT_REDUCE(x,n,NULL,MPT_UCHAR,MPT_BCAST,r)
# define PRF_BCAST_DOUBLE(x,n,r) MPT_REDUCE(x,n,NULL,MPT_DOUBLE,MPT_BCAST,r)
# define PRF_BCAST_SIZE_T(x,n,r) MPT_REDUCE(x,n,NULL,MPT_SIZE_T,MPT_BCAST,r)
# define PRF_BCAST_CHAR(x,n,r)   MPT_REDUCE(x,n,NULL,MPT_CHAR,MPT_BCAST,r)

# define PRF_ALLTOALL_INT        MPT_ALLTOALL_INT
# define PRF_ALLTOALL_SIZE_T     MPT_ALLTOALL_SIZE_T
# define PRF_ALLTOALL_INDEX      MPT_ALLTOALL_INDEX
# define PRF_ALLTOALL_FLOAT      MPT_ALLTOALL_FLOAT
# define PRF_ALLTOALL_DOUBLE     MPT_ALLTOALL_DOUBLE

# define PRF_ALLTOALLV_INT       MPT_ALLTOALLV_INT
# define PRF_ALLTOALLV_LONG      MPT_ALLTOALLV_LONG
# define PRF_ALLTOALLV_LONG_LONG MPT_ALLTOALLV_LONG_LONG
# define PRF_ALLTOALLV_FLOAT     MPT_ALLTOALLV_FLOAT
# define PRF_ALLTOALLV_DOUBLE    MPT_ALLTOALLV_DOUBLE
# define PRF_ALLTOALLV_INDEX     MPT_ALLTOALLV_INDEX
# define PRF_ALLTOALLV_SIZE_T    MPT_ALLTOALLV_SIZE_T
# define PRF_ALLTOALLV_CHAR      MPT_ALLTOALLV_CHAR

# if RP_DOUBLE
#  define PRF_GRHIGH           MPT_GDHIGH
#  define PRF_GRLOW          MPT_GDLOW
#  define PRF_GRSUM          MPT_GDSUM
#  define PRF_GRHIGH1            MPT_GDHIGH1
#  define PRF_GRLOW1             MPT_GDLOW1
#  define PRF_GRSUM1             MPT_GDSUM1
#  define PRF_ALLTOALL_REAL      MPT_ALLTOALL_DOUBLE
#  define PRF_ALLTOALLV_REAL     MPT_ALLTOALLV_DOUBLE
#  define PRF_BCAST_REAL(x,n,r)  MPT_REDUCE(x,n,NULL,MPT_DOUBLE,MPT_BCAST,r)
# else
#  define PRF_GRHIGH           MPT_GSHIGH
#  define PRF_GRLOW              MPT_GSLOW
#  define PRF_GRSUM          MPT_GSSUM
#  define PRF_GRHIGH1            MPT_GSHIGH1
#  define PRF_GRLOW1             MPT_GSLOW1
#  define PRF_GRSUM1             MPT_GSSUM1
#  define PRF_ALLTOALL_REAL      MPT_ALLTOALL_FLOAT
#  define PRF_ALLTOALLV_REAL     MPT_ALLTOALLV_FLOAT
#  define PRF_BCAST_REAL(x,n,r)  MPT_REDUCE(x,n,NULL,MPT_FLOAT,MPT_BCAST,r)
# endif

# define PRF_GISUM2 MPT_GISUM2
# define PRF_GISUM3 MPT_GISUM3
# define PRF_GISUM4 MPT_GISUM4
# define PRF_GISUM5 MPT_GISUM5
# define PRF_GISUM6 MPT_GISUM6
# define PRF_GISUM7 MPT_GISUM7
# define PRF_GISUM8 MPT_GISUM8

# define PRF_GILOW2 MPT_GILOW2
# define PRF_GILOW3 MPT_GILOW3
# define PRF_GILOW4 MPT_GILOW4

# define PRF_GIHIGH2 MPT_GIHIGH2
# define PRF_GIHIGH3 MPT_GIHIGH3
# define PRF_GIHIGH4 MPT_GIHIGH4

# define PRF_GDSUM2 MPT_GDSUM2
# define PRF_GDSUM3 MPT_GDSUM3
# define PRF_GSSUM2 MPT_GSSUM2

# define PRF_GDHIGH2 MPT_GDHIGH2
# define PRF_GSHIGH2 MPT_GSHIGH2

# define PRF_GDLOW2 MPT_GDLOW2
# define PRF_GSLOW2 MPT_GSLOW2

# define PRF_GDHIGH3 MPT_GDHIGH3
# define PRF_GSHIGH3 MPT_GSHIGH3

# define PRF_GDLOW3 MPT_GDLOW3
# define PRF_GSLOW3 MPT_GSLOW3

# if RP_DOUBLE
# define PRF_GRSUM2 MPT_GDSUM2
# define PRF_GRSUM3 MPT_GDSUM3
# define PRF_GRSUM4 MPT_GDSUM4
# define PRF_GRSUM5 MPT_GDSUM5
# define PRF_GRSUM6 MPT_GDSUM6
# define PRF_GRSUM7 MPT_GDSUM7
# define PRF_GRSUM8 MPT_GDSUM8
# define PRF_GRLOW2 MPT_GDLOW2
# define PRF_GRLOW3 MPT_GDLOW3
# define PRF_GRLOW4 MPT_GDLOW4
# define PRF_GRLOW5 MPT_GDLOW5
# define PRF_GRLOW6 MPT_GDLOW6
# define PRF_GRLOW7 MPT_GDLOW7
# define PRF_GRLOW8 MPT_GDLOW8
# define PRF_GRHIGH2 MPT_GDHIGH2
# define PRF_GRHIGH3 MPT_GDHIGH3
# define PRF_GRHIGH4 MPT_GDHIGH4
# define PRF_GRHIGH5 MPT_GDHIGH5
# define PRF_GRHIGH6 MPT_GDHIGH6
# define PRF_GRHIGH7 MPT_GDHIGH7
# define PRF_GRHIGH8 MPT_GDHIGH8
# define PRF_GRSUM_ND MPT_GDSUM_ND
# define PRF_GRHIGH_ND MPT_GDHIGH_ND
# define PRF_GRLOW_ND MPT_GDLOW_ND
#else
# define PRF_GRSUM2 MPT_GSSUM2
# define PRF_GRSUM3 MPT_GSSUM3
# define PRF_GRSUM4 MPT_GSSUM4
# define PRF_GRSUM5 MPT_GSSUM5
# define PRF_GRSUM6 MPT_GSSUM6
# define PRF_GRSUM7 MPT_GSSUM7
# define PRF_GRSUM8 MPT_GSSUM8
# define PRF_GRLOW2 MPT_GSLOW2
# define PRF_GRLOW3 MPT_GSLOW3
# define PRF_GRLOW4 MPT_GSLOW4
# define PRF_GRLOW5 MPT_GSLOW5
# define PRF_GRLOW6 MPT_GSLOW6
# define PRF_GRLOW7 MPT_GSLOW7
# define PRF_GRLOW8 MPT_GSLOW8
# define PRF_GRHIGH2 MPT_GSHIGH2
# define PRF_GRHIGH3 MPT_GSHIGH3
# define PRF_GRHIGH4 MPT_GSHIGH4
# define PRF_GRHIGH5 MPT_GSHIGH5
# define PRF_GRHIGH6 MPT_GSHIGH6
# define PRF_GRHIGH7 MPT_GSHIGH7
# define PRF_GRHIGH8 MPT_GSHIGH8
# define PRF_GRSUM_ND MPT_GSSUM_ND
# define PRF_GRHIGH_ND MPT_GSHIGH_ND
# define PRF_GRLOW_ND MPT_GSLOW_ND
#endif

# define PRF_GIOR2 MPT_GIOR2
# define PRF_GIOR3 MPT_GIOR3
# define PRF_GIOR4 MPT_GIOR4

# define PRF_GIAND2 MPT_GIAND2
# define PRF_GIAND3 MPT_GIAND3
# define PRF_GIAND4 MPT_GIAND4

/* # define PRF_GLOR2 MPT_GLOR2 --- used to work in int, now works on long; currently not used. Uncomment if needed! */
/* # define PRF_GLOR3 MPT_GLOR3 --- used to work in int, now works on long; currently not used. Uncomment if needed! */
/* # define PRF_GLOR4 MPT_GLOR4 --- used to work in int, now works on long; currently not used. Uncomment if needed! */

/* # define PRF_GLAND2 MPT_GLAND2 --- used to work in int, now works on long; currently not used. Uncomment if needed! */
/* # define PRF_GLAND3 MPT_GLAND3 --- used to work in int, now works on long; currently not used. Uncomment if needed! */
/* # define PRF_GLAND4 MPT_GLAND4 --- used to work in int, now works on long; currently not used. Uncomment if needed! */

# define PRF_GLSUM2 MPT_GLSUM2
# define PRF_GLSUM3 MPT_GLSUM3
# define PRF_GLSUM4 MPT_GLSUM4

# define PRF_GLLOW2 MPT_GLLOW2
# define PRF_GLLOW3 MPT_GLLOW3
# define PRF_GLLOW4 MPT_GLLOW4

# define PRF_GLHIGH2 MPT_GLHIGH2
# define PRF_GLHIGH3 MPT_GLHIGH3
# define PRF_GLHIGH4 MPT_GLHIGH4

# define PRF_GLLSUM2 MPT_GLLSUM2
# define PRF_GLLSUM3 MPT_GLLSUM3
# define PRF_GLLSUM4 MPT_GLLSUM4

# define PRF_GLLLOW2 MPT_GLLLOW2
# define PRF_GLLLOW3 MPT_GLLLOW3
# define PRF_GLLLOW4 MPT_GLLLOW4

# define PRF_GLLHIGH2 MPT_GLLHIGH2
# define PRF_GLLHIGH3 MPT_GLLHIGH3
# define PRF_GLLHIGH4 MPT_GLLHIGH4

# define PRF_GTSUM2 MPT_GTSUM2
# define PRF_GTSUM3 MPT_GTSUM3
# define PRF_GTSUM4 MPT_GTSUM4

# define PRF_GTLOW2 MPT_GTLOW2
# define PRF_GTLOW3 MPT_GTLOW3
# define PRF_GTLOW4 MPT_GTLOW4

# define PRF_GTHIGH2 MPT_GTHIGH2
# define PRF_GTHIGH3 MPT_GTHIGH3
# define PRF_GTHIGH4 MPT_GTHIGH4

# define PRF_SISUM2 MPT_SISUM2

/*
 * ----------------------------------------------------------------
 * Point to point MPI calls that take communicator handle
 * as an argument are differentiated by "_S"
 * ----------------------------------------------------------------
 */
#define PRF_S_CSEND_CHAR       MPT_S_CSEND_CHAR
#define PRF_S_CRECV_CHAR       MPT_S_CRECV_CHAR
#define PRF_S_CSEND_INT        MPT_S_CSEND_INT
#define PRF_S_CRECV_INT        MPT_S_CRECV_INT
#define PRF_S_CSEND_LONG       MPT_S_CSEND_LONG
#define PRF_S_CRECV_LONG       MPT_S_CRECV_LONG
#define PRF_S_CSEND_FLOAT      MPT_S_CSEND_FLOAT
#define PRF_S_CRECV_FLOAT      MPT_S_CRECV_FLOAT
#define PRF_S_CSEND_DOUBLE     MPT_S_CSEND_DOUBLE
#define PRF_S_CRECV_DOUBLE     MPT_S_CRECV_DOUBLE
#define PRF_S_CSEND_SIZE_T     MPT_S_CSEND_SIZE_T
#define PRF_S_CRECV_SIZE_T     MPT_S_CRECV_SIZE_T
#define PRF_S_CSEND_SHORT      MPT_S_CSEND_SHORT
#define PRF_S_CRECV_SHORT      MPT_S_CRECV_SHORT
#define PRF_S_CSEND_LONG_LONG  MPT_S_CSEND_LONG_LONG
#define PRF_S_CRECV_LONG_LONG  MPT_S_CRECV_LONG_LONG

#define PRF_S_ISEND_CHAR       MPT_S_ISEND_CHAR
#define PRF_S_IRECV_CHAR       MPT_S_IRECV_CHAR
#define PRF_S_ISEND_INT        MPT_S_ISEND_INT
#define PRF_S_IRECV_INT        MPT_S_IRECV_INT
#define PRF_S_ISEND_LONG       MPT_S_ISEND_LONG
#define PRF_S_IRECV_LONG       MPT_S_IRECV_LONG
#define PRF_S_ISEND_FLOAT      MPT_S_ISEND_FLOAT
#define PRF_S_IRECV_FLOAT      MPT_S_IRECV_FLOAT
#define PRF_S_ISEND_DOUBLE     MPT_S_ISEND_DOUBLE
#define PRF_S_IRECV_DOUBLE     MPT_S_IRECV_DOUBLE
#define PRF_S_ISEND_SIZE_T     MPT_S_ISEND_SIZE_T
#define PRF_S_IRECV_SIZE_T     MPT_S_IRECV_SIZE_T
#define PRF_S_ISEND_SHORT      MPT_S_ISEND_SHORT
#define PRF_S_IRECV_SHORT      MPT_S_IRECV_SHORT
#define PRF_S_ISEND_LONG_LONG  MPT_S_ISEND_LONG_LONG
#define PRF_S_IRECV_LONG_LONG  MPT_S_IRECV_LONG_LONG

/*
 * ----------------------------------------------------------------
 */

#else
/* !RP_NODE */

# define PRF_GSYNC()
# define PRF_GIAND1(thunk) (thunk)
# define PRF_GIOR1(thunk) (thunk)
/* efine PRF_GLAND1(thunk) (thunk) --- used to work in int, now works on long; currently not used. Uncomment if needed! */
/* efine PRF_GLOR1(thunk) (thunk) --- used to work in int, now works on long; currently not used. Uncomment if needed! */
# define PRF_GLLAND1(thunk) (thunk)
# define PRF_GLLOR1(thunk) (thunk)
# define PRF_GIHIGH1(thunk) thunk
# define PRF_GIHIGH2(v0,v1)        /* nothing */
# define PRF_GIHIGH3(v0,v1,v2)     /* nothing */
# define PRF_GIHIGH4(v0,v1,v2,v3)  /* nothing */
# define PRF_GILOW1(thunk) thunk
# define PRF_GILOW2(v0,v1)        /* nothing */
# define PRF_GILOW3(v0,v1,v2)     /* nothing */
# define PRF_GILOW4(v0,v1,v2,v3)  /* nothing */
# define PRF_GISUM1(thunk) thunk
# define PRF_GISUM1_0(thunk) thunk
# define PRF_GISUM2(v0,v1)
# define PRF_GISUM3(v0,v1,v2)
# define PRF_GISUM4(v0,v1,v2,v3)
# define PRF_GISUM5(v0,v1,v2,v3,v4)
# define PRF_GISUM6(v0,v1,v2,v3,v4,v5)
# define PRF_GISUM7(v0,v1,v2,v3,v4,v5,v6)
# define PRF_GISUM8(v0,v1,v2,v3,v4,v5,v6,v7)
# define PRF_PISUM1(thunk) thunk
# define PRF_GLHIGH1(thunk) thunk
# define PRF_GLHIGH2(v0,v1)        /* nothing */
# define PRF_GLHIGH3(v0,v1,v2)     /* nothing */
# define PRF_GLHIGH4(v0,v1,v2,v3)  /* nothing */
# define PRF_GLLHIGH1(thunk) thunk
# define PRF_GLLHIGH2(v0,v1)        /* nothing */
# define PRF_GLLHIGH3(v0,v1,v2)     /* nothing */
# define PRF_GLLHIGH4(v0,v1,v2,v3)  /* nothing */
# define PRF_GTHIGH1(thunk) thunk
# define PRF_GTHIGH2(v0,v1)        /* nothing */
# define PRF_GTHIGH3(v0,v1,v2)     /* nothing */
# define PRF_GTHIGH4(v0,v1,v2,v3)  /* nothing */
# define PRF_GTLOW1(thunk) thunk
# define PRF_GTLOW2(v0,v1)        /* nothing */
# define PRF_GTLOW3(v0,v1,v2)     /* nothing */
# define PRF_GTLOW4(v0,v1,v2,v3)  /* nothing */
# define PRF_GTSUM1(thunk) thunk
# define PRF_GTSUM2(v0,v1)        /* nothing */
# define PRF_GTSUM3(v0,v1,v2)     /* nothing */
# define PRF_GTSUM4(v0,v1,v2,v3)  /* nothing */
# define PRF_GI64HIGH1(thunk) thunk
# define PRF_GI64HIGH2(v0,v1)        /* nothing */
# define PRF_GI64HIGH3(v0,v1,v2)     /* nothing */
# define PRF_GI64HIGH4(v0,v1,v2,v3)  /* nothing */
# define PRF_GLLOW1(thunk) thunk
# define PRF_GLLOW2(v0,v1)        /* nothing */
# define PRF_GLLOW3(v0,v1,v2)     /* nothing */
# define PRF_GLLOW4(v0,v1,v2,v3)  /* nothing */
# define PRF_GLLLOW1(thunk) thunk
# define PRF_GLLLOW2(v0,v1)        /* nothing */
# define PRF_GLLLOW3(v0,v1,v2)     /* nothing */
# define PRF_GLLLOW4(v0,v1,v2,v3)  /* nothing */
# define PRF_GI64LOW1(thunk) thunk
# define PRF_GI64LOW2(v0,v1)        /* nothing */
# define PRF_GI64LOW3(v0,v1,v2)     /* nothing */
# define PRF_GI64LOW4(v0,v1,v2,v3)  /* nothing */
# define PRF_GLSUM1(thunk) thunk
# define PRF_GLLSUM1(thunk) thunk
# define PRF_GI64SUM1(thunk) thunk
# define PRF_GIOR2(v0,v1)
# define PRF_GIOR3(v0,v1,v2)
# define PRF_GIOR4(v0,v1,v2,v3)
# define PRF_GIAND2(v0,v1)
# define PRF_GIAND3(v0,v1,v2)
# define PRF_GIAND4(v0,v1,v2,v3)
/* # define PRF_GLOR2(v0,v1) --- used to work in int, now works on long; currently not used. Uncomment if needed! */
/* # define PRF_GLOR3(v0,v1,v2) --- used to work in int, now works on long; currently not used. Uncomment if needed! */
/* # define PRF_GLOR4(v0,v1,v2,v3) --- used to work in int, now works on long; currently not used. Uncomment if needed! */
/* # define PRF_GLAND2(v0,v1) --- used to work in int, now works on long; currently not used. Uncomment if needed! */
/* # define PRF_GLAND3(v0,v1,v2) --- used to work in int, now works on long; currently not used. Uncomment if needed! */
/* # define PRF_GLAND4(v0,v1,v2,v3) --- used to work in int, now works on long; currently not used. Uncomment if needed! */
# define PRF_GLSUM2(v0,v1)
# define PRF_GLSUM3(v0,v1,v2)
# define PRF_GLSUM4(v0,v1,v2,v3)
# define PRF_GLLSUM2(v0,v1)
# define PRF_GLLSUM3(v0,v1,v2)
# define PRF_GLLSUM4(v0,v1,v2,v3)
# define PRF_GI64SUM2(v0,v1)
# define PRF_GI64SUM3(v0,v1,v2)
# define PRF_GI64SUM4(v0,v1,v2,v3)
# define PRF_PLSUM1(thunk) thunk
# define PRF_PLLSUM1(thunk) thunk
# define PRF_PTSUM1(think) think
# define PRF_PTSUM(v0,v1,v2,v3,v4,v5) thunk
# define PRF_GDHIGH1(thunk) thunk
# define PRF_GDHIGH2(v0,v1)  /* nothing */
# define PRF_GDLOW1(thunk) thunk
# define PRF_GDLOW2(v0,v1)   /* nothing */
# define PRF_GDSUM1(thunk) thunk
# define PRF_GDSUM2(v0,v1)
# define PRF_GDSUM3(v0,v1,v2)
# define PRF_GSHIGH1(thunk) thunk
# define PRF_GSHIGH2(v0,v1)
# define PRF_GSLOW1(thunk) thunk
# define PRF_GSLOW2(v0,v1)
# define PRF_GSSUM1(thunk) thunk
# define PRF_GSSUM2(v0,v1)
# define PRF_GIHIGH(vx,vy,vz)  /* nothing */
# define PRF_GILOW(vx,vy,vz)   /* nothing */
# define PRF_GISUM(vx,vy,vz)   /* nothing */
# define PRF_GLHIGH(vx,vy,vz)  /* nothing */
# define PRF_GLLOW(vx,vy,vz)   /* nothing */
# define PRF_GLSUM(vx,vy,vz)   /* nothing */
# define PRF_GLLHIGH(vx,vy,vz)  /* nothing */
# define PRF_GLLLOW(vx,vy,vz)   /* nothing */
# define PRF_GLLSUM(vx,vy,vz)   /* nothing */
# define PRF_GTHIGH(vx,vy,vz)   /* nothing */
# define PRF_GI64HIGH(vx,vy,vz)  /* nothing */
# define PRF_GI64LOW(vx,vy,vz)   /* nothing */
# define PRF_GI64SUM(vx,vy,vz)   /* nothing */
# define PRF_GSHIGH(vx,vy,vz)  /* nothing */
# define PRF_GSLOW(vx,vy,vz)   /* nothing */
# define PRF_GSSUM(vx,vy,vz)   /* nothing */
# define PRF_GDHIGH(vx,vy,vz)  /* nothing */
# define PRF_GDLOW(vx,vy,vz)   /* nothing */
# define PRF_GDSUM(vx,vy,vz)   /* nothing */
# define PRF_GIOR(vx,vy,vz)    /* nothing */
/* efine PRF_GLOR(vx,vy,vz) --- used to work in int, now works on long; currently not used. Uncomment if needed! */
# define PRF_GLLOR(vx,vy,vz)    /* nothing */
# define PRF_GIAND(vx,vy,vz)    /* nothing */
/* efine PRF_GLAND(vx,vy,vz) --- used to work in int, now works on long; currently not used. Uncomment if needed! */
# define PRF_GLLAND(vx,vy,vz)    /* nothing */
# define PRF_GUCBOR(vx,vy,vz)     /* nothing */
# define PRF_GUCBAND(vx,vy,vz)    /* nothing */
# define PRF_GUIBOR(vx,vy,vz)     /* nothing */
# define PRF_GUIBAND(vx,vy,vz)    /* nothing */

# define PRF_BCAST_INT(x,n,r)      /* nothing */
# define PRF_BCAST_UINT(x,n,r)     /* nothing */
# define PRF_BCAST_UCHAR(x,n,r)    /* nothing */
# define PRF_BCAST_SIZE_T(x,n,r)   /* nothing */

# define PRF_ALLTOALL_INT(s,r,c)     /* nothing */
# define PRF_ALLTOALL_SIZE_T(s,r,c)  /* nothing */
# define PRF_ALLTOALL_INDEX(s,r,c)   /* nothing */
# define PRF_ALLTOALL_FLOAT(s,r,c)   /* nothing */
# define PRF_ALLTOALL_DOUBLE(s,r,c)  /* nothing */
# define PRF_ALLTOALL_REAL(s,r,c)    /* nothing */

# define PRF_ALLTOALLV_INT(s,sc,sd,r,rc,rd)      /* nothing */
# define PRF_ALLTOALLV_LONG(s,sc,sd,r,rc,rd)     /* nothing */
# define PRF_ALLTOALLV_LONG_LONG(s,sc,sd,r,rc,rd)/* nothing */
# define PRF_ALLTOALLV_FLOAT(s,sc,sd,r,rc,rd)    /* nothing */
# define PRF_ALLTOALLV_DOUBLE(s,sc,sd,r,rc,rd)   /* nothing */
# define PRF_ALLTOALLV_INDEX(s,sc,sd,r,rc,rd)    /* nothing */
# define PRF_ALLTOALLV_SIZE_T(s,sc,sd,r,rc,rd)   /* nothing */
# define PRF_ALLTOALLV_CHAR(s,sc,sd,r,rc,rd)     /* nothing */

# define PRF_BCAST_REAL(x,n,r)

# define PRF_GRHIGH1(thunk) thunk
# define PRF_GRHIGH2(v0,v1)
# define PRF_GRHIGH3(v0,v1,v2)
# define PRF_GRHIGH4(v0,v1,v2,v3)
# define PRF_GRHIGH5(v0,v1,v2,v3,v4)
# define PRF_GRHIGH6(v0,v1,v2,v3,v4,v5)
# define PRF_GRHIGH7(v0,v1,v2,v3,v4,v5,v6)
# define PRF_GRHIGH8(v0,v1,v2,v3,v4,v5,v6,v7)
# define PRF_GRLOW1(thunk) thunk
# define PRF_GRLOW2(v0,v1)
# define PRF_GRLOW3(v0,v1,v2)
# define PRF_GRLOW4(v0,v1,v2,v3)
# define PRF_GRLOW5(v0,v1,v2,v3,v4)
# define PRF_GRLOW6(v0,v1,v2,v3,v4,v5)
# define PRF_GRLOW7(v0,v1,v2,v3,v4,v5,v6)
# define PRF_GRLOW8(v0,v1,v2,v3,v4,v5,v6,v7)
# define PRF_GRSUM1(thunk) thunk
# define PRF_GRSUM2(v0,v1)
# define PRF_GRSUM3(v0,v1,v2)
# define PRF_GRSUM4(v0,v1,v2,v3)
# define PRF_GRSUM5(v0,v1,v2,v3,v4)
# define PRF_GRSUM6(v0,v1,v2,v3,v4,v5)
# define PRF_GRSUM7(v0,v1,v2,v3,v4,v5,v6)
# define PRF_GRSUM8(v0,v1,v2,v3,v4,v5,v6,v7)
# define PRF_GRSUM(v0,v1,v2)
# define PRF_GRSUM_ND(vx,vy,vz)
# define PRF_GRHIGH(vx,vy,vz)
# define PRF_GRHIGH_ND(vx,vy,vz)
# define PRF_GRLOW(vx,vy,vz)
# define PRF_GRLOW_ND(vx,vy,vz)
# define PRF_SISUM2(v0,v1)

/*
 * ----------------------------------------------------------------
 * Point to point MPI calls that take communicator handle
 * as an argument are differentiated by "_S"
 * ----------------------------------------------------------------
 */
#define PRF_S_CSEND_CHAR
#define PRF_S_CRECV_CHAR
#define PRF_S_CSEND_INT
#define PRF_S_CRECV_INT
#define PRF_S_CSEND_LONG
#define PRF_S_CRECV_LONG
#define PRF_S_CSEND_FLOAT
#define PRF_S_CRECV_FLOAT
#define PRF_S_CSEND_DOUBLE
#define PRF_S_CRECV_DOUBLE
#define PRF_S_CSEND_SIZE_T
#define PRF_S_CRECV_SIZE_T
#define PRF_S_CSEND_SHORT
#define PRF_S_CRECV_SHORT
#define PRF_S_CSEND_LONG_LONG
#define PRF_S_CRECV_LONG_LONG

#define PRF_S_ISEND_CHAR
#define PRF_S_IRECV_CHAR
#define PRF_S_ISEND_INT
#define PRF_S_IRECV_INT
#define PRF_S_ISEND_LONG
#define PRF_S_IRECV_LONG
#define PRF_S_ISEND_FLOAT
#define PRF_S_IRECV_FLOAT
#define PRF_S_ISEND_DOUBLE
#define PRF_S_IRECV_DOUBLE
#define PRF_S_ISEND_SIZE_T
#define PRF_S_IRECV_SIZE_T
#define PRF_S_ISEND_SHORT
#define PRF_S_IRECV_SHORT
#define PRF_S_ISEND_LONG_LONG
#define PRF_S_IRECV_LONG_LONG

#endif /* RP_NODE */

# define PRF_GRSUM_NV(v)  PRF_GRSUM_ND((v[0]),(v[1]),(v[2]))
# define PRF_GRHIGH_NV(v) PRF_GRHIGH_ND((v[0]),(v[1]),(v[2]))
# define PRF_GRLOW_NV(v)  PRF_GRLOW_ND((v[0]),(v[1]),(v[2]))

# if USE_INT64
#if _NT
# define PRF_CSEND_INDEX            PRF_CSEND_LONG_LONG
# define PRF_CRECV_INDEX            PRF_CRECV_LONG_LONG
# define PRF_ISEND_INDEX            PRF_ISEND_LONG_LONG
# define PRF_IRECV_INDEX            PRF_IRECV_LONG_LONG
# define PRF_SEND_INDEX             PRF_SEND_LONG_LONG
# define PRF_RECV_INDEX             PRF_RECV_LONG_LONG
# define PRF_S_CSEND_INDEX          PRF_S_CSEND_LONG_LONG
# define PRF_S_CRECV_INDEX          PRF_S_CRECV_LONG_LONG
# define PRF_S_ISEND_INDEX          PRF_S_ISEND_LONG_LONG
# define PRF_S_IRECV_INDEX          PRF_S_IRECV_LONG_LONG
# define PRF_S_SEND_INDEX           PRF_S_SEND_LONG_LONG
# define PRF_S_RECV_INDEX           PRF_S_RECV_LONG_LONG
# define PRF_GXHIGH1 PRF_GLLHIGH1
# define PRF_GXHIGH2 PRF_GLLHIGH2
# define PRF_GXHIGH3 PRF_GLLHIGH3
# define PRF_GXHIGH4 PRF_GLLHIGH4
# define PRF_GXLOW1  PRF_GLLLOW1
# define PRF_GXLOW2  PRF_GLLLOW2
# define PRF_GXLOW3  PRF_GLLLOW3
# define PRF_GXLOW4  PRF_GLLLOW4
# define PRF_GXSUM1  PRF_GLLSUM1
# define PRF_GXSUM2  PRF_GLLSUM2
# define PRF_GXSUM3  PRF_GLLSUM3
# define PRF_GXSUM4  PRF_GLLSUM4
# define PRF_PXSUM1  PRF_PLLSUM1

# define PRF_GXHIGH PRF_GLLHIGH
# define PRF_GXLOW  PRF_GLLLOW
# define PRF_GXSUM  PRF_GLLSUM
# define PRF_PXSUM  PRF_PLLSUM
# define MPT_PACK_INDEX MPT_PACK_LONG_LONG
# define PRF_CPASS_STRUCT_INDEX       PRF_CPASS_STRUCT_LONG_LONG
# define PRF_CSEND_STRUCT_INDEX       PRF_CSEND_STRUCT_LONG_LONG
# define PRF_CRECV_STRUCT_INDEX       PRF_CRECV_STRUCT_LONG_LONG
# define MPT_serialize_cxindex MPT_serialize_long_long
# define MPT_unpack_cxindex MPT_unpack_long_long
# define MPT_Array_copy_cxindex   MPT_Array_copy_long_long
#else
# define PRF_CSEND_INDEX            PRF_CSEND_LONG
# define PRF_CRECV_INDEX            PRF_CRECV_LONG
# define PRF_ISEND_INDEX            PRF_ISEND_LONG
# define PRF_IRECV_INDEX            PRF_IRECV_LONG
# define PRF_SEND_INDEX             PRF_SEND_LONG
# define PRF_RECV_INDEX             PRF_RECV_LONG
# define PRF_S_CSEND_INDEX          PRF_S_CSEND_LONG
# define PRF_S_CRECV_INDEX          PRF_S_CRECV_LONG
# define PRF_S_ISEND_INDEX          PRF_S_ISEND_LONG
# define PRF_S_IRECV_INDEX          PRF_S_IRECV_LONG
# define PRF_S_SEND_INDEX           PRF_S_SEND_LONG
# define PRF_S_RECV_INDEX           PRF_S_RECV_LONG
# define PRF_GXHIGH1 PRF_GLHIGH1
# define PRF_GXHIGH2 PRF_GLHIGH2
# define PRF_GXHIGH3 PRF_GLHIGH3
# define PRF_GXHIGH4 PRF_GLHIGH4
# define PRF_GXLOW1  PRF_GLLOW1
# define PRF_GXLOW2  PRF_GLLOW2
# define PRF_GXLOW3  PRF_GLLOW3
# define PRF_GXLOW4  PRF_GLLOW4
# define PRF_GXSUM1  PRF_GLSUM1
# define PRF_GXSUM2  PRF_GLSUM2
# define PRF_GXSUM3  PRF_GLSUM3
# define PRF_GXSUM4  PRF_GLSUM4
# define PRF_PXSUM1  PRF_PLSUM1

# define PRF_GXHIGH PRF_GLHIGH
# define PRF_GXLOW  PRF_GLLOW
# define PRF_GXSUM  PRF_GLSUM
# define PRF_PXSUM  PRF_PLSUM
# define MPT_PACK_INDEX MPT_PACK_LONG
# define PRF_CPASS_STRUCT_INDEX       PRF_CPASS_STRUCT_LONG
# define PRF_CSEND_STRUCT_INDEX       PRF_CSEND_STRUCT_LONG
# define PRF_CRECV_STRUCT_INDEX       PRF_CRECV_STRUCT_LONG
# define MPT_serialize_cxindex MPT_serialize_long
# define MPT_unpack_cxindex MPT_unpack_long
# define MPT_Array_copy_cxindex   MPT_Array_copy_long
#endif
#else
# define PRF_CSEND_INDEX            PRF_CSEND_INT
# define PRF_CRECV_INDEX            PRF_CRECV_INT
# define PRF_ISEND_INDEX            PRF_ISEND_INT
# define PRF_IRECV_INDEX            PRF_IRECV_INT
# define PRF_SEND_INDEX             PRF_SEND_INT
# define PRF_RECV_INDEX             PRF_RECV_INT
# define PRF_GXHIGH1 PRF_GIHIGH1
# define PRF_GXHIGH2 PRF_GIHIGH2
# define PRF_GXHIGH3 PRF_GIHIGH3
# define PRF_GXHIGH4 PRF_GIHIGH4
# define PRF_GXLOW1  PRF_GILOW1
# define PRF_GXLOW2  PRF_GILOW2
# define PRF_GXLOW3  PRF_GILOW3
# define PRF_GXLOW4  PRF_GILOW4
# define PRF_GXSUM1  PRF_GISUM1
# define PRF_GXSUM2  PRF_GISUM2
# define PRF_GXSUM3  PRF_GISUM3
# define PRF_GXSUM4  PRF_GISUM4
# define PRF_PXSUM1  PRF_PISUM1

# define PRF_GXHIGH PRF_GIHIGH
# define PRF_GXLOW  PRF_GILOW
# define PRF_GXSUM  PRF_GISUM
# define PRF_PXSUM  PRF_PISUM

# define MPT_PACK_INDEX MPT_PACK_INT
# define PRF_CPASS_STRUCT_INDEX       PRF_CPASS_STRUCT_INT
# define PRF_CSEND_STRUCT_INDEX       PRF_CSEND_STRUCT_INT
# define PRF_CRECV_STRUCT_INDEX       PRF_CRECV_STRUCT_INT
# define MPT_serialize_cxindex MPT_serialize_int
# define MPT_unpack_cxindex MPT_unpack_int
# define MPT_Array_copy_cxindex   MPT_Array_copy_int
#endif
# define PRF_PACK_INDEX MPT_PACK_INDEX

#if !PARALLEL
/* keep same order as in mport.h */
typedef enum
{
  MPT_DATATYPE_NULL  =  0,
  MPT_CHAR           =  1,
  MPT_SHORT          =  2,
  MPT_INT            =  3,
  MPT_LONG           =  4,
  MPT_FLOAT          =  5,
  MPT_DOUBLE         =  6,
  MPT_SIZE_T         =  7,
  MPT_LONG_LONG      =  8,
  MPT_UNSIGNED_CHAR  =  9,
  MPT_UNSIGNED_INT   = 10,
  MPT_DATATYPE_MAX
} MPT_Datatype;

#define  MPT_UCHAR  MPT_UNSIGNED_CHAR
#define  MPT_UINT   MPT_UNSIGNED_INT

#endif /* !PARALLEL */

# if USE_INT64
#if _NT
#define MPT_INDEX MPT_LONG_LONG
#else
#define MPT_INDEX MPT_LONG
#endif
#else
#define MPT_INDEX MPT_INT
#endif /* USE_INT64 */

# if RP_DOUBLE
#define MPT_REAL MPT_DOUBLE
#else
#define MPT_REAL MPT_FLOAT
#endif /* RP_DOUBLE */


/* START: Scalar reductions using subcommunicator */
#define PRF_SIHIGH1_ALL MPT_SIHIGH1_ALL
#define PRF_SLHIGH1_ALL MPT_SLHIGH1_ALL
#define PRF_SSHIGH1_ALL MPT_SSHIGH1_ALL
#define PRF_SDHIGH1_ALL MPT_SDHIGH1_ALL
#define PRF_SILOW1_ALL  MPT_SILOW1_ALL
#define PRF_SLLOW1_ALL  MPT_SLLOW1_ALL
#define PRF_SSLOW1_ALL  MPT_SSLOW1_ALL
#define PRF_SDLOW1_ALL  MPT_SDLOW1_ALL
#define PRF_SISUM1_ALL  MPT_SISUM1_ALL
#define PRF_SLSUM1_ALL  MPT_SLSUM1_ALL
#define PRF_SSSUM1_ALL  MPT_SSSUM1_ALL
#define PRF_SDSUM1_ALL  MPT_SDSUM1_ALL
#if RP_DOUBLE
#define PRF_SRHIGH1_ALL MPT_SDHIGH1_ALL
#define PRF_SRLOW1_ALL  MPT_SDLOW1_ALL
#define PRF_SRSUM1_ALL  MPT_SDSUM1_ALL
#else
#define PRF_SRHIGH1_ALL MPT_SSHIGH1_ALL
#define PRF_SRLOW1_ALL  MPT_SSLOW1_ALL
#define PRF_SRSUM1_ALL  MPT_SSSUM1_ALL
#endif
#if USE_INT64
#define PRF_SXHIGH1_ALL MPT_SLHIGH1_ALL
#define PRF_SXLOW1_ALL  MPT_SLLOW1_ALL
#define PRF_SXSUM1_ALL  MPT_SLSUM1_ALL
#else
#define PRF_SXHIGH1_ALL MPT_SIHIGH1_ALL
#define PRF_SXLOW1_ALL  MPT_SILOW1_ALL
#define PRF_SXSUM1_ALL  MPT_SISUM1_ALL
#endif

#define PRF_SIHIGH1     MPT_SIHIGH1
#define PRF_SLHIGH1     MPT_SLHIGH1
#define PRF_SSHIGH1     MPT_SSHIGH1
#define PRF_SDHIGH1     MPT_SDHIGH1
#define PRF_SILOW1      MPT_SILOW1
#define PRF_SLLOW1      MPT_SLLOW1
#define PRF_SSLOW1      MPT_SSLOW1
#define PRF_SDLOW1      MPT_SDLOW1
#define PRF_SISUM1      MPT_SISUM1
#define PRF_SLSUM1      MPT_SLSUM1
#define PRF_SSSUM1      MPT_SSSUM1
#define PRF_SDSUM1      MPT_SDSUM1
#if RP_DOUBLE
#define PRF_SRHIGH1     MPT_SDHIGH1
#define PRF_SRLOW1      MPT_SDLOW1
#define PRF_SRSUM1      MPT_SDSUM1
#define PRF_SRSUM2      MPT_SDSUM2
#define PRF_SRSUM       MPT_SDSUM
#else
#define PRF_SRHIGH1     MPT_SSHIGH1
#define PRF_SRLOW1      MPT_SSLOW1
#define PRF_SRSUM1      MPT_SSSUM1
#define PRF_SRSUM2      MPT_SSSUM2
#define PRF_SRSUM       MPT_SSSUM
#endif
#if USE_INT64
#define PRF_SXHIGH1     MPT_SLHIGH1
#define PRF_SXLOW1      MPT_SLLOW1
#define PRF_SXSUM1      MPT_SLSUM1
#else
#define PRF_SXHIGH1     MPT_SIHIGH1
#define PRF_SXLOW1      MPT_SILOW1
#define PRF_SXSUM1      MPT_SISUM1
#endif

#define PRF_SIHIGH1_0   MPT_SIHIGH1_0
#define PRF_SLHIGH1_0   MPT_SLHIGH1_0
#define PRF_SSHIGH1_0   MPT_SSHIGH1_0
#define PRF_SDHIGH1_0   MPT_SDHIGH1_0
#define PRF_SILOW1_0    MPT_SILOW1_0
#define PRF_SLLOW1_0    MPT_SLLOW1_0
#define PRF_SSLOW1_0    MPT_SSLOW1_0
#define PRF_SDLOW1_0    MPT_SDLOW1_0
#define PRF_SISUM1_0    MPT_SISUM1_0
#define PRF_SLSUM1_0    MPT_SLSUM1_0
#define PRF_SSSUM1_0    MPT_SSSUM1_0
#define PRF_SDSUM1_0    MPT_SDSUM1_0
#if RP_DOUBLE
#define PRF_SRHIGH1_0   MPT_SDHIGH1_0
#define PRF_SRLOW1_0    MPT_SDLOW1_0
#define PRF_SRSUM1_0    MPT_SDSUM1_0
#else
#define PRF_SRHIGH1_0   MPT_SSHIGH1_0
#define PRF_SRLOW1_0    MPT_SSLOW1_0
#define PRF_SRSUM1_0    MPT_SSSUM1_0
#endif
#if USE_INT64
#define PRF_SXHIGH1_0   MPT_SLHIGH1_0
#define PRF_SXLOW1_0    MPT_SLLOW1_0
#define PRF_SXSUM1_0    MPT_SLSUM1_0
#else
#define PRF_SXHIGH1_0   MPT_SIHIGH1_0
#define PRF_SXLOW1_0    MPT_SILOW1_0
#define PRF_SXSUM1_0    MPT_SISUM1_0
#endif
/* END  : Scalar reductions using subcommunicator */


#endif /* _INCLUDED_PRF_H */

#endif /* _FLUENT_PRF_H */
