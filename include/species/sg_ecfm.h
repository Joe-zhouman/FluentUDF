/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/* Define constants, macros and prototypes for the
   extended coherent flamelet model (ECFM) */

#ifndef _FLUENT_ECFM_H
#define _FLUENT_ECFM_H

#include "dll.h"

/* Cache'd rpvars for ECFM */

typedef enum
{
  ITNFS_MENEVEAU,
  ITNFS_BLINT,
  ITNFS_POINSOT,
  ITNFS_CONSTANT_DELTA,
  ITNFS_CONSTANT
} Itnfs_Type;

typedef enum
{
  SUTHERLAND,
  DIFFUSIVITY,
  SUTHERLAND_FGM_TFS,
  FGM_POLY_ALPHA
} Delta_Type;

typedef enum
{
  ECFM_P1,
  ECFM_P2,
  ECFM_P3,
  ECFM_P4,
  ECFM_ITNFS,
  ECFM_D
} Ecfm_Term;

typedef enum
{
  ECFM_MENEVEAU,
  ECFM_TERAJI,
  ECFM_POINSOT,
  ECFM_VEYNANTE,
  ECFM_MAX
} Ecfm_Type;

typedef struct ECFM_Struct
{
  cxboolean ecfm_enabled;
  cxboolean ecfm_sigma_solved;
  cxboolean local_property;     /* Use local burned and unburned property*/
  cxboolean kinetic_theory_ktc; /* Use kinetic theory to calculate thermal conductivity*/
  cxboolean p3_rho_ratio;       /* Flag to include unburned/burned density ratio in p3 term */
  cxboolean p_restrict;         /* Flag to restrict production terms */

  int verbosity;           /* More information per time step/iteration */

  real dt;                 /* Cache'd flow time step */
  real min_prod_sl;        /* Minimum flame speed for production of sigma (P1) */
  real min_dest_sl;        /* Minimum flame speed for destruction of sigma (P3) */
  real min_p3_c;           /* Minimum progress variable for production of sigma (P3) */
  real max_dest_c;         /* Maximum progress variable for destruction of sigma (D) */
  real alpha0;             /* Constant multiplier for ITNFS term */
  real alpha1;             /* Constant multiplier for P1 term */
  real alpha2;             /* "                 " for P2 term */
  real alpha3;             /* "                 " for P3 term */
  real alpha4;             /* "                 " for P4 term */
  real beta1;              /* "                 " for D term */
  real beta2;              /* "                 " for Nissan D term */
  real delta_l;            /* optional hardwired flame thickness */
  real itnfs_fixed;        /* optional hardwired ITNFS value */
  real min_itnfs;          /* Minimum ITNFS value */
  real wall_flux_const;    /* constant for wall flux */
  real min_dl;             /* minimum laminar flame thickness */
  real thermal_diff_u;     /* Unburnt-thermal_diffusivity */
  real blint_coeff;        /* For calculation of Intermittent flame stretch*/
  real drat;               /* ratio of burnt and unburnt density*/
  real nres_les;           /* les grid resolution constant */
  real alpha1_les;         /* les source term constant */
  real beta1_les;          /* les source term constant */
  real beta2_les;          /* les source term constant */

  Itnfs_Type itnfs_type;   /* Options for ITNFS */
  Delta_Type delta_type;   /* Options for deltal calc. */
  Ecfm_Type ecfm_type;     /* Options for ECFM source terms */
} Ecfm_Par;

FLUENT_EXPORT void ecfm_model_init(void);
FLUENT_EXPORT real Get_Ecfm_Sources(cell_t, Thread *, Ecfm_Term);
FLUENT_EXPORT void ECFM_unburned_properties(Domain *d, Ecfm_Par *ecfm_par);
FLUENT_EXPORT real calc_cell_itnfs(cell_t c, Thread *t, Ecfm_Par *ecfm_par);
FLUENT_EXPORT Ecfm_Par *getEcfmPar(void);
FLUENT_EXPORT real ktc_u(cell_t c, Thread *t, real temp_u, real den_u);

FLUENT_EXPORT void Model_Initialize_ecfm(void);

#endif  /* _FLUENT_ECFM_H */
