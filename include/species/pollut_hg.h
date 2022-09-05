/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SG_MERCURY_H
#define _FLUENT_SG_MERCURY_H

#include "dll.h"

/* Define constants, macros and prototypes for pollutants */
#define MAX_FUEL_STREAMS 3   /* Make sure to modify rpvar "pollut/max-fuel-streams" */

typedef struct Hg_struct
{
  /* Hg model specific parameters */
  int model;
  int o_mode, oh_mode;
  real h_o_ratio, h2_h_ratio;

  real Yhg_fuelvolat[MAX_FUEL_STREAMS];    /* Hg mass fraction in fuel gas/volatiles  */
  int  fuel_cl_conv[MAX_FUEL_STREAMS];     /* fuel HCl/Cl conversion. 0: scheme A; 1: scheme B; 2: scheme C. */
  real Yhcl_fuelvolat[MAX_FUEL_STREAMS];   /* HCl mass fraction in fuel gas/volatiles  */
  real Ycl_fuelvolat[MAX_FUEL_STREAMS];    /* Cl mass fraction in fuel gas/volatiles  */
  real Yhg_char[MAX_FUEL_STREAMS];         /* Hg mass fraction in char (solid fuel) */
  int  char_cl_conv[MAX_FUEL_STREAMS];     /* char HCl/Cl conversion. 0: scheme A; 1: scheme B; 2: scheme C. */
  real Yhcl_char[MAX_FUEL_STREAMS];        /* HCl mass fraction in char (solid fuel) */
  real Ycl_char[MAX_FUEL_STREAMS];         /* Cl mass fraction in char (solid fuel) */

  /* User defined Hg */
  cxboolean user_hg, user_replace;
  Tci_Params tci_params;
} Hg_Parameter;

extern FLUENT_EXPORT Hg_Parameter *Hg;
FLUENT_EXPORT int Hg_Init(Domain *domain);
FLUENT_EXPORT void HG_kinetics(Domain *domain);
FLUENT_EXPORT void HG_rates(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Rate *s_pollut);
FLUENT_EXPORT void hg_rate(cell_t c, Thread *t, Pollut_Cell *Pollut);
FLUENT_EXPORT void call_user_hg_rate(cell_t c, Thread *t, Pollut_Cell *Pollut);
FLUENT_EXPORT void hg_atomic_balance(Domain *domain);

#endif /* _FLUENT_SG_MERCURY_H */
