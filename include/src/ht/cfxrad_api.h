/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/
/*
 **********************************************************************
 *
  File: $Id: cfxrad_api.h 134471 2015-07-09 14:20:04Z jmpenros $
 *
 * Module:  CFXrad
 *      CFX radiation shared module and interface
 *
 * Purpose: header for CFXrad.so entry routines, and interface
 *          data structures
 *
 * History:
 *   05.15  JMP Created
 *
 */
#include "fortran_types.h"
#include "dll.h"

#define MXDNAM 20

/* logical states */
#define CFXRAD_FALSE 0
#define CFXRAD_TRUE  1

/* parallel states */
#define CFXRAD_PARMODE_MASTER   1
#define CFXRAD_PARMODE_SLAVE    2

#define CFXRAD_RUNMODE_SERIAL   0
#define CFXRAD_RUNMODE_PARALLEL 1


/*
 * ---- Helper structures for Radiation Module API ----
 */
typedef enum
{
  cfxrad_model_monte_ = 0,
  cfxrad_model_dtm_
} CFXrad_model;

typedef enum
{
  cfxrad_ok_ = 0,
  cfxrad_err_action_unknown_,
  cfxrad_err_action_failed_,
  cfxrad_err_input_,
  cfxrad_err_data_
} CFXrad_err;

typedef enum
{
  cfxrad_action_null_ = 0,
  cfxrad_action_init_system_,
  cfxrad_action_update_system_,
  cfxrad_action_solve_,
  cfxrad_action_delete_system_,
  cfxrad_action_iotest_
} CFXrad_act;

typedef struct
{
  Freal pi;
  Freal eps;
  Freal rinf;
  Freal stefan;
  Freal clight;
  Freal plank;
  Freal boltzman;
} CFXrad_constants;

typedef struct
{
  Freal x;
  Freal y;
  Freal z;
} CFXrad_pt;

typedef struct
{
  Freal nx;
  Freal ny;
  Freal nz;
} CFXrad_nvec;

typedef struct
{
  Fint i;
  Fint j;
  Fint k;
} CFXrad_tri;

typedef struct
{
  Fint  runmode; /**/
  Fint  parmode; /**/
  Fint  partid; /*partition number starting from 1- 1 is master and rest is for slaves*/
  Fint  npart;  /*Total number of partitions*/
  Fint  nthreads;
  Fint  paropt;
  Fint  *gthreadnos;
} CFXrad_parallel;

typedef struct
{
  Freal        flux;
  Freal        radt;
  CFXrad_pt    ploc;
  CFXrad_nvec  dir;
  Freal       *calib;
} CFXrad_radiometer;

typedef struct
{
  Fint *ipsur;
  Fint *ipz;
  Fint *ipzon;
  Fint *isurf;
  Fint *neighb;
  Fint *iatrib;
} CFXrad_zoning;

typedef struct
{
  Fint *iuzon;
  Fint *iusur;
  Fint *iubdry;
  Fint *iuside;
} CFXrad_ums;

typedef struct
{
  CFXrad_pt  *pts;
  CFXrad_tri *trvx;
  Fint       *iptrps;
} CFXrad_points;

typedef struct
{
  Fint   npts;
  Fint   nintpts;
  Freal *pangle;
  Freal *pinten;
} CFXrad_poldfun;

typedef struct
{
  Freal *smbfr;
  Freal *albedo;
  Freal *rough;
  Freal *sxri;
  Freal *tsur;
  Freal *cond;
  Freal *t0;
  Freal *area;
  Freal *ftol;
  Freal *sflux;
  Freal *sdv;
  Freal *irrad;
  Freal *reflx;
  /* non-thermal source definitions */
  Freal *sflnt;
  CFXrad_nvec *sangnt;
  /* Polar Distribution Function definitions */
  Fint   npoldfun;
  Fint  *kbsrcsur;
  CFXrad_poldfun *poldfun;
} CFXrad_surrad;

typedef struct
{
  Freal *xabs;
  Freal *xri;
  Freal *xscat;
  Freal *aniso;
  Freal *vmbfr;
  Freal *tvol;
  Freal *vol;
  Freal *vheat;
  Freal *avi;
  Freal *sdv;
  /* non-thermal source definitions */
  Freal *vflnt;
  CFXrad_nvec *vangnt;
} CFXrad_volrad;

typedef struct
{
  void *cstk;
  void *dstk;
  void *istk;
  void *lstk;
  void *rstk;
  Freal size;
  Fint8 nc;
  Fint8 nd;
  Fint8 ni;
  Fint8 nl;
  Fint8 nr;
  Fint  mode;
#if _NT
  HANDLE HeapHandle;
  HANDLE intwrk_h, relwrk_h, dblwrk_h, chrwrk_h, logwrk_h;
#endif
} CFXrad_mms;

/*
 * ---- Main Data structure for Radiation Module API ----
 */
typedef struct
{
  CFXrad_model model;
  Fchar ctradm[MXDNAM];
  Fint  lvldia;
  /* Parallel specifications */
  CFXrad_parallel *parallel; /**/
  /* Global model definitions */
  Fint  nhist;
  Fint  maxwkunit;
  Fint  nrays;
  Fint  nps;
  Fint  nphys;
  Fint  numats;
  Fint  nz;
  Fint  nband;
  Fint  npts;
  Fint  ntri;
  Fint  nprim;
  Fint  npan;
  Fint  nnodes;
  Fint  mbmod;
  Freal frace;
  Freal tband;
  Freal tref;
  Flogical lntsur;
  Flogical lntvol;
  Flogical lmask;
  /* Topology definitions */
  CFXrad_zoning zoning;
  CFXrad_ums    ums;
  /* Geometry definitions */
  CFXrad_points points;
  /* Property definitions */
  Freal *band;
  CFXrad_surrad surrad;
  CFXrad_volrad volrad;
  /* Radiometer definitions */
  Fint  npnod;
  Fint  ncal;
  Fint  nquad;
  CFXrad_radiometer *radiometer;
  /* Constants and internal MMS data */
  CFXrad_constants contants;
  CFXrad_mms       mms;
} CFXrad_data;

/*
 * ---- API entry routine prototype ----
 */

FLUENT_EXPORT void CFXrad_action (CFXrad_act, void *data, CFXrad_err * );



