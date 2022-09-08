/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SG_SOX_H
#define _FLUENT_SG_SOX_H

#include "dll.h"

/* Define constants, macros and prototypes for pollutants */
#define MAX_FUEL_STREAMS 3   /* Make sure to modify rpvar "pollut/max-fuel-streams" */

typedef struct Sox_Struct
{
  /* SOx model specific parameters */
  int  o_mode;
  int  oh_mode;

  int  fuel_s_conv[MAX_FUEL_STREAMS];     /* fuel s conversion. 0: scheme A; 1: scheme B; 2: scheme C. */
  real Ys_fuelvolat[MAX_FUEL_STREAMS];    /* sulphur mass fraction in fuel gas/volatiles  */
  real fuels_so2_frac[MAX_FUEL_STREAMS];  /* fuel sulphur to so2 conversion fraction */
  real fuels_h2s_frac[MAX_FUEL_STREAMS];  /* fuel sulphur to h2s conversion fraction */
  int  char_s_conv[MAX_FUEL_STREAMS];     /* char s conversion. 0: scheme A; 1: scheme B; 2: scheme C. */
  real Ys_char[MAX_FUEL_STREAMS];         /* sulphur mass fraction in char (solid fuel) */
  real chars_so2_frac[MAX_FUEL_STREAMS];  /* char sulphur to so2 conversion fraction */
  real chars_h2s_frac[MAX_FUEL_STREAMS];  /* char sulphur to h2s conversion fraction */
  real h_o_ratio;
  real h2_h_ratio;

  /* User defined SOx and Other */
  cxboolean user_sox;
  cxboolean user_replace;
  cxboolean old_kp;
  real rate_limit;
  Tci_Params tci_params;
} SOx_Parameter;

extern FLUENT_EXPORT SOx_Parameter *SOx;

FLUENT_EXPORT int Sox_Init(Domain *domain);
FLUENT_EXPORT void SOx_kinetics(Domain *domain);
FLUENT_EXPORT void SOx_rates(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Rate *s_pollut);
FLUENT_EXPORT void sox_rate(cell_t c, Thread *t, Pollut_Cell *Pollut);
FLUENT_EXPORT void call_user_sox_rate(cell_t c, Thread *t, Pollut_Cell *Pollut);
FLUENT_EXPORT void sox_s_atomic_balance(Domain *domain);

#endif /* _FLUENT_SG_SOX_H */
