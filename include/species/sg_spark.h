/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SPARK_H
#define _FLUENT_SPARK_H

#include "sg_ecfm.h"

#define SPARKMAX 16

typedef enum
{
  SPHERICAL,
  CYLINDRICAL,
  BOX,
  USER_GEOM
} Spark_Shape;

typedef enum
{
  ECFM_SPARK_TURBULENT,
  ECFM_SPARK_BOUDIER,
  ECFM_SPARK_TERAJI,
  ECFM_SPARK_ZIMONT,
  ECFM_SPARK_CONSTANT,
  ECFM_SPARK_USER,
  ECFM_SPARK_MAX
} Ecfm_Spark_Type;

typedef enum
{
  SPARK_TURBULENT_CURVATURE,
  SPARK_TURBULENT_LENGTH,
  SPARK_HERWEG_MALY,
  SPARK_LAMINAR
} Spark_Flame_Speed_Model;

typedef struct Spark_Struct
{
  cxboolean off;              /* on/off flag */
  cxboolean td_geo;           /* time dependent radius flag */
  cxboolean initialized;      /* init flag */
  Spark_Shape spark_shape;    /* type of spark */
  real spark_center[3];       /* center of spark location, axis start for cyl */
  real dx[3];                 /* dx,dy,dz for box option, axis end for cyl */
  real r0, rf, rtrans;        /* initial, final and transition radius of spark */
  real te;                    /* time exponent for geometry */
  real radius;                /* spark radius */

  cxboolean ecfm_spark_drdt;  /* ecfm spark treatment flag */
  real ecfm_spark_const;      /* sigma in the spark region */
  /* when ECFM_SPARK_CONSTANT */
  Ecfm_Spark_Type ecfm_spark_type; /* Options for ECFM spark calculation */
  real sl;                    /* spark laminar burning velocity */
  real tts;                   /* spark turbulent time scale */
  real dts;                   /* spark turbulent diffusion coeff */
  real drat;                  /* spark rhou/rhob */
  real tdu;                   /* spark thermal diffusivity */
  real itnfs;                 /* spark itnfs */
  real tls;                   /* spark turbulent length scale */
  real sigma;                 /* spark ecfm sigma */
  Spark_Flame_Speed_Model model; /* spark flame speed model */

  char *ecfm_spark_src_fcn;   /* ecfm user source function name */
  char *spark_geom_fcn;       /* ecfm user geometry function name */

  real sv_ratio;              /* surface area / volume ratio of spark volume */
  real time;                  /* Cache'd current time */
  real time_step;             /* Cache'd current time step */
  real duration;              /* spark duration (s) */
  real energy;                /* spark energy (mJ)*/
  real power;                 /* energy/duration */
  real start_ca;              /* starting & stopping crank angle, time */
  real start_time;
  real stop_time;
  real diff_time;             /* relaxation time for spark */
  real diff_term;             /* cache'd 1-exp(-(t-t_0)/t_r) */
  real diff_arg;              /* cache'd (t-t_0)/t_r */
  real t_max;                 /* Maximum cell temperature for energy addition */
} Spark_Par;

FLUENT_EXPORT Objp **Compute_Spark(Domain *domain);
FLUENT_EXPORT Objp **Compute_Spark_r145(Domain *domain);
FLUENT_EXPORT void freeSparks(void);
FLUENT_EXPORT void spark_model_init(void);
FLUENT_EXPORT Spark_Par *getSparkPar(void);
FLUENT_EXPORT Spark_Flame_Speed_Model get_spark_flame_speed_model(void);
FLUENT_EXPORT void setPSpark(int snum, real *p_spark, int is, int ie);
FLUENT_EXPORT real Spark_St(Spark_Flame_Speed_Model model, real t, real r,
                            real rtrans, real sl, real tts, real drat, real tls,
                            real sigma, real tdu, real dts);
FLUENT_EXPORT void set_spark_props(Domain *domain, Objp *spark_cell_list[],
                                   Ecfm_Par *ecfm_par, cxboolean spark_start);
FLUENT_EXPORT Objp **get_spark_cell_list(void);

FLUENT_EXPORT void Read_Spark_Data(FILE *file, cxboolean binary, cxboolean double_data);
FLUENT_EXPORT void Write_Spark_Data(FILE *file, cxboolean binary);

#if MPI_IO
FLUENT_EXPORT void Read_MPI_Spark_Data(int fhandle, int *headerbuf, cxboolean double_data);
FLUENT_EXPORT void Write_MPI_Spark_Data(int fhandle);
#endif

#endif /* _FLUENT_SPARK_H */
