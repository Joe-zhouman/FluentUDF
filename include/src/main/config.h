/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_CONFIG_H
#define _FLUENT_CONFIG_H

#if _NT
#  if !UDF_COMPILER
#    include <localize.h>
#  endif
#  include <sys_master.h>
#else
#  if !UDF_COMPILER
#    include "localize.h"
#  endif
#  include "sys_master.h"
#endif

#if sys_linmic
#include <immintrin.h>
#endif

#if !RP_CONFIG_LIB
#include "mparchconfig.h"
#endif

/* specific to tglib in Meshing */
#if RP_CONFIG_LIB
# define RP_CONFIG_3DDP 1
#endif

/* Set standard flags based on specified solver name. */

#if RP_CONFIG_2D
# define RP_2D 1
# define RP_CONFIG "2d"
#endif

#if RP_CONFIG_3D
# define RP_3D 1
# define RP_CONFIG "3d"
#endif

#if RP_CONFIG_2D_HOST
# define RP_2D 1
# define RP_HOST 1
# define RP_CONFIG "2d_host"
#endif

#if RP_CONFIG_2D_NODE
# define RP_2D 1
# define RP_NODE 1
# define RP_CONFIG "2d_node"
#endif

#if RP_CONFIG_3D_HOST
# define RP_3D 1
# define RP_HOST 1
# define RP_CONFIG "3d_host"
#endif

#if RP_CONFIG_3D_NODE
# define RP_3D 1
# define RP_NODE 1
# define RP_CONFIG "3d_node"
#endif

#if RP_CONFIG_2DDP
# define RP_2D 1
# define RP_DOUBLE 1
# define RP_CONFIG "2ddp"
#endif

#if RP_CONFIG_3DDP
# define RP_3D 1
# define RP_DOUBLE 1
# define RP_CONFIG "3ddp"
#endif

#if RP_CONFIG_2DDP_HOST
# define RP_2D 1
# define RP_DOUBLE 1
# define RP_HOST 1
# define RP_CONFIG "2ddp_host"
#endif

#if RP_CONFIG_2DDP_NODE
# define RP_2D 1
# define RP_DOUBLE 1
# define RP_NODE 1
# define RP_CONFIG "2ddp_node"
#endif

#if RP_CONFIG_3DDP_HOST
# define RP_3D 1
# define RP_DOUBLE 1
# define RP_HOST 1
# define RP_CONFIG "3ddp_host"
#endif

#if RP_CONFIG_3DDP_NODE
# define RP_3D 1
# define RP_DOUBLE 1
# define RP_NODE 1
# define RP_CONFIG "3ddp_node"
#endif

#ifndef RP_2D
# define RP_2D 0
#endif

#ifndef RP_3D
# define RP_3D 0
#endif

#if RP_2D && RP_3D
Error: both RP_2D and RP_3D are defined
#endif

#if !(RP_2D || RP_3D)
Error: both RP_2D and RP_3D are undefined
#endif

#ifndef RP_HOST
# define RP_HOST 0
#endif

#ifndef RP_NODE
# define RP_NODE 0
#endif

#if RP_HOST && RP_NODE
Error: both RP_HOST and RP_NODE are defined
#endif

#if RP_NODE || RP_HOST
# include "pconfig.h"
#else
# define PARALLEL 0
# define MULTIPORT 0
#endif

#ifndef NEW_PARALLEL_NEIGHBOR
# define NEW_PARALLEL_NEIGHBOR 0
#endif

#ifndef RP_ADAPT
# define RP_ADAPT (!PARALLEL)
#endif

#ifndef TG_LIB
# define TG_LIB 1
#endif

#ifndef TGRID
# if RP_3D
#  define TGRID 1
# else
#  define TGRID 0
# endif
#endif

#if !(sys_ntx86 || sys_win64) && TGRID
# undef WORKING_CXX
# if RP_HOST_LIB || RP_NODE_LIB
#  define WORKING_CXX 0
# else
#  define WORKING_CXX 1
# endif
#endif


#ifndef RP_METIS
# define RP_METIS 1
#endif

#ifndef  RP_METIS_V3
#define RP_METIS_V3 1
#endif

#ifndef RP_GEOM
# define RP_GEOM 1
#endif

#if sys_alpha || sys_hpux11 || sys_hpux11_64 || sys_hpux11_ia64 || sys_lnx86 || sys_lnia64 || sys_lnamd64 || sys_linmic || sys_lop64 || sys_lnarm64 || sys_ultra || sys_ultra_64  || sys_aix51 || sys_aix51_64 || sys_power3 || sys_power3_64 || sys_irix65_mips4 || sys_irix65_mips4_64 || sys_ntx86 || sys_win64
# ifndef CGNS_LIB
#  define CGNS_LIB 1
# endif
#else
# define CGNS_LIB 0
#endif
#if sys_lnx86  || sys_lnamd64 || sys_linmic || sys_lop64 || sys_lnarm64 || sys_ultra_64 || sys_aix51_64 || sys_hpux11_64 ||  sys_ntx86

# ifndef HDF5_LIB
#  define HDF5_LIB  0
# endif
#else
# define HDF5_LIB 0
#endif

# ifndef VKI_LIB
#   define VKI_LIB 1
# endif

/* flag for parallel MPI IO code */
#ifndef MPI_IO
#define MPI_IO 1 && PARALLEL
#endif

#if sys_alpha || sys_hpux11 || sys_hpux11_64 || sys_solaris || sys_ultra || sys_aix51 || sys_power3 || sys_irix65_mips4 || sys_lnx86 || sys_ntx86
# ifndef ANSYS_LIB
#  define ANSYS_LIB (!PARALLEL)
# endif
#else
#  define ANSYS_LIB 0
#endif

# ifndef CPROPEP_LIB
#  define CPROPEP_LIB 1
# endif

#ifndef PTR_RESTRICT
#  if sys_lnia64
#    define PTR_RESTRICT restrict
#  elif sys_lnx86 || sys_lnamd64 || sys_linmic || sys_lop64 || sys_lnarm64
#    if !sys_debug
#      if USE_INTEL_COMPILER
#        define PTR_RESTRICT restrict
#      else
#        define PTR_RESTRICT __restrict__
#      endif
#    else
#      define PTR_RESTRICT
#    endif
#  elif sys_ultra || sys_ultra_64
#    define PTR_RESTRICT _Restrict
#  elif sys_ntx86 || sys_win64
#    if INTEL_C
#      define PTR_RESTRICT restrict
#    else
#      define PTR_RESTRICT
#    endif
#  else
#    define PTR_RESTRICT
#  endif
#endif

#if (sys_lnia64 || sys_lnx86 || sys_lnamd64 || sys_linmic || sys_lop64 || sys_lnarm64 || sys_hpux11_ia64 || sys_ntx86 || sys_win64)
#  define GEM_UNROLL  1
#else
#  undef GEM_UNROLL
#endif

#if sys_lnia64
#  define IA64_SPARSE 1
#  define RAG_TGMATH  1
#  define FETCH(X) __lfetch(__lfhint_nt1,X);
#  define PREFETCH(X)
#elif sys_linmic
#  undef IA64_SPARSE
#  undef RAG_TGMATH
#  define PREFETCH(X) _mm_prefetch((char *)(X),2);
#  define FETCH(X) _mm_prefetch((char *)(X),2);
#elif sys_lnamd64
#  undef IA64_SPARSE
#  undef RAG_TGMATH
/*#  define PREFETCH(X) _mm_prefetch((char *)(X),_MM_HINT_T1); */
#  define PREFETCH(X)
#  define FETCH(X)
#else
#  undef IA64_SPARSE
#  undef RAG_TGMATH
#  define PREFETCH(X)
#  define FETCH(X)
#endif

#define RP_AXI RP_2D

/* RP_PLBC: Phase Lag Boundary Condition
 * for transient Turbo Stage simulation */
#ifndef RP_PLBC
# define RP_PLBC 1
#endif

/* RP_FC: Fourier Decomposition Reconstruction library (FDR)
   Note: needs to be set if RP_PLBC is set */
#ifndef RP_FC
# define RP_FC (RP_PLBC || 1)
#endif

#ifndef DYNAMIC_MESH_TIMING
# define DYNAMIC_MESH_TIMING 0
#else
# define USE_FLUENT_PROFILE 1
#endif

/* overset/chimera mesh model */
#ifndef RP_OVERSET
#define RP_OVERSET 1
#if RP_OVERSET
#define OVERSET_NUMERICS 1
#define IMPLICIT_OVERSET 1
#define OVERSET_DEBUG  0
#define OLD_LOOP  0
#define OVERSET_COEFF_MATRIX   0
#if RP_NODE
#define OVERSET_PAR_DEBUG  0
#endif
#endif
#endif

#ifndef HOTR_RESTART
#define HOTR_RESTART 1
#endif

#ifndef USE_MKL
#if sys_lop64 || sys_lnarm64
#  define USE_MKL 0
# else
#  define USE_MKL 1
# endif
#endif


/* polyhedra cell support */
#if RP_3D
# ifndef RP_POLYHEDRA
#  define RP_POLYHEDRA 1
# endif
#else
# ifdef RP_POLYHEDRA
#  undef RP_POLYHEDRA
# endif
# define RP_POLYHEDRA 0
#endif

/* sided metrics for mesh interface */
#ifndef SIDED_METRICS
# define SIDED_METRICS 1
#endif

/* RP_NETWORK => compact network model for modeling electronic chips.
 * Used in ICEPAK */
#ifndef RP_NETWORK
# define RP_NETWORK 1
#endif

#ifndef RP_PCB
# define RP_PCB 1
#endif

/* external coupling with one-d code */
#ifndef ONE_D
# define ONE_D 1
#endif

#ifndef SYSV
# define SYSV 0
#endif

#ifndef RP_DOUBLE
# define RP_DOUBLE 0
#endif
#define XF_DOUBLE RP_DOUBLE

#ifndef CORTEX
# define CORTEX 0
#endif

#ifndef GRAPHICS
# define GRAPHICS 0
#endif

#ifndef SEEM
# define SEEM 0
#endif

#ifndef CX_2_PROC
# define CX_2_PROC 0
#endif

#define RP_HANG 1

#define RP_EDGE RP_3D

#ifndef RP_AMG_DO
# define RP_AMG_DO 1
#endif
#ifndef RP_S2S
# define RP_S2S 1
#endif

#ifndef RP_SOLAR
# define RP_SOLAR 1
# define SOLAR_ASYNC 0
#endif

#ifndef RP_DTRM
# define RP_DTRM 1
#endif

#ifndef PURIFY_DEBUG
# define PURIFY_DEBUG 0
#endif

#ifndef LICENSE_NOX
# define LICENSE_NOX 0
#endif

/* for checking mass flow in mixing plane */
#ifndef  MFI_DEBUG
# define MFI_DEBUG 0
#endif


/* enable low-Re k-epsilon model */
#ifndef RP_LOWRE_KE
# define RP_LOWRE_KE 1
#endif

/* least squares reconstruction */
#ifndef LSQ_RECON
# define LSQ_RECON 1
#endif

/* Drift force coupled */
#ifndef DRIFT_COUPLED
# define DRIFT_COUPLED 1
#endif

/* stiff chemistry solver */
#ifndef RP_STIFF_CHEM
# define RP_STIFF_CHEM 1
#endif

/* overridden by TRUE if running under the udf interpreter */
#ifndef UDF_COMPILER
# define UDF_COMPILER 0
#endif

/* defines for dynamic library loader */
#ifndef LIBS_DL
# define LIBS_DL -ldl
#endif
#ifndef DL_AVAILABLE
# define DL_AVAILABLE 1
#endif

#ifndef PDF_TRANSPORT
# define PDF_TRANSPORT 1
#endif

/* shared-memory-parallel DPM */
# ifndef RP_DPM_CACHE
#  define RP_DPM_CACHE 1
# endif

/* distributed-memory-parallel DPM */
#ifndef DPM2
# define DPM2 1
#endif

/* shell conduction */
#ifndef RP_SHELL
# define RP_SHELL 1
#endif

#ifndef MULTI_SHELL
# define MULTI_SHELL 1
#endif

/* acoustics */
#ifndef RP_ACOUSTICS
# define RP_ACOUSTICS 1
#endif

/* wall film */
#ifndef RP_WALL_FILM
# define RP_WALL_FILM RP_3D
#endif

#ifndef PREPDF
#define PREPDF 0
#endif

#ifndef RP_TOUCH_MEMORY
# define RP_TOUCH_MEMORY 1
#endif


#ifndef DEBUG_PARALLEL
# define DEBUG_PARALLEL 0
#endif

#ifndef DEBUG_MEMORY
# define DEBUG_MEMORY 0
#endif

#ifndef DEBUG
# define DEBUG 0
#endif

#ifndef RP_CHIP
# define RP_CHIP CHIP_AVAILABLE
#endif

#ifndef RP_AMG_V5 /* Fluent version 5 AMG, before loop unrolling opts */
# define RP_AMG_V5 1
#endif

#ifndef RP_AMG_SM
# define RP_AMG_SM 0
#endif

#ifndef RP_AMG_LAPLACE_C
# define RP_AMG_LAPLACE_C 1
#endif

#ifdef MAKEFILE

#ifndef BUILD_net
# define BUILD_net 0
#endif
#ifndef BUILD_smpi
# define BUILD_smpi 0
#endif
#ifndef BUILD_nmpi
# define BUILD_nmpi 0
#endif
#ifndef BUILD_xmpi
# define BUILD_xmpi 0
#endif
#ifndef BUILD_vmpi
# define BUILD_vmpi 0
#endif
#ifndef BUILD_tmpi
# define BUILD_tmpi 0
#endif
#ifndef BUILD_gmpi
# define BUILD_gmpi 0
#endif
#ifndef BUILD_scampi
# define BUILD_scampi 0
#endif
#ifndef BUILD_beo
# define BUILD_beo 0
#endif
#ifndef BUILD_vmi
# define BUILD_vmi 0
#endif
#ifndef BUILD_iba
# define BUILD_iba 0
#endif
#ifndef BUILD_nmpissh
# define BUILD_nmpissh 0
#endif
#ifndef BUILD_pvm
# define BUILD_pvm 0
#endif
#ifndef BUILD_lsmpi
# define BUILD_lsmpi 0
#endif
#ifndef BUILD_lnmpi
# define BUILD_lnmpi 0
#endif
#ifndef BUILD_host
# define BUILD_host 0
#endif
#ifndef BUILD_serial
# define BUILD_serial 1
#endif

#endif

/* Switch off the amg chunked memory for 64-bit systems */
#define sys_64 (sys_aix51_64 || sys_hpux11_64 || sys_hpux11_ia64 || sys_irix65_mips4_64 || sys_lnia64 || sys_ultra_64 || sys_lnamd64 || sys_linmic || sys_lop64 || sys_lnarm64 || sys_win64)

#ifndef AMG_CHUNKED_MEMORY
# if sys_ntx86
#  define AMG_CHUNKED_MEMORY 1
# else
#  define AMG_CHUNKED_MEMORY 0
# endif
#endif

#ifndef USE_OFFSET_MALLOC
/* use it for all the linux and windows versions */
#define USE_OFFSET_MALLOC (sys_lnx86 || sys_lnia64 || sys_lnamd64 || sys_linmic || sys_lop64 || sys_lnarm64 || sys_ntx86 || sys_win64 || sys_aix51_64)
#endif

/* the process cleanup code */
#ifndef USE_MOINITOR_RING
#define USE_MOINITOR_RING 1
#endif

/* support of 64-bit indexing */
#ifndef USE_INT64
# if (sys_lnamd64 || sys_linmic || sys_lop64 || sys_lnarm64 || sys_win64 || sys_ntx86) && PARALLEL
#  define USE_INT64 1
# else
#  define USE_INT64 0
# endif
#endif

/* support of hybrid OMP in AMG */
#ifndef USE_HYBRID_OMP
# if (((sys_lnamd64 || sys_linmic || sys_lop64 || sys_lnarm64 || sys_win64) && _INTEL_CC) || sys_aix51_64) && RP_NODE
#  define USE_HYBRID_OMP 1
# else
#  define USE_HYBRID_OMP 0
# endif
#endif

/* HTC support */
#define RP_HTC 1

#ifndef _NT
# if (sys_ntx86 || sys_win64)
#  define _NT 1
# else
#  define _NT 0
# endif
#endif

/* ... for the FEM prototype.
**/
#define USE_FEMCORE 1

#endif /* _FLUENT_CONFIG_H */

