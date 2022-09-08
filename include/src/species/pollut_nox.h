/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SG_NOX_H
#define _FLUENT_SG_NOX_H

#include "dll.h"
#include "pdf_props.h"
#include "pdf_table.h"

/* Define constants, macros and prototypes for pollutants */
#define MAX_FUEL_STREAMS 3   /* Make sure to modify rpvar "pollut/max-fuel-streams" */

typedef struct nox_parameter_struct
{
  /* NOx model specific parameters */
  /* Thermal NO */
  cxboolean thermal_nox;
  int o_mode;
  int oh_mode;
  int thermal_limit_switch;

  /* Prompt NO */
  cxboolean prompt_nox;
  real equiv_ratio[MAX_FUEL_STREAMS];     /* equivalence ratio */
  real c_number[MAX_FUEL_STREAMS];        /* # of carbon atoms per molecule for the hydrocarbon fuel */

  /* Fuel NO */
  cxboolean fuel_nox;
  int  fuel_n_conv[MAX_FUEL_STREAMS];     /* fuel n conversion. 0: scheme A; 1: scheme B; 2: scheme C.*/
  real Yn_fuelvolat[MAX_FUEL_STREAMS];    /* nitrogen mass fraction in fuel gas or volatiles (liquid and solid devol) */
  real fueln_nox_frac[MAX_FUEL_STREAMS];  /* fuel nitrogen to no conversion fraction */
  real fueln_hcn_frac[MAX_FUEL_STREAMS];  /* fuel nitrogen to hcn conversion fraction */
  real fueln_nh3_frac[MAX_FUEL_STREAMS];  /* fuel nitrogen to nh3 conversion fraction */
  int  char_n_conv[MAX_FUEL_STREAMS];     /* char n conversion. 0: scheme A; 1: scheme B; 2: scheme C.; 3: scheme D.*/
  real Yn_char[MAX_FUEL_STREAMS];         /* nitrogen mass fraction in char (solid fuel) */
  real charn_nox_frac[MAX_FUEL_STREAMS];  /* char nitrogen to no conversion fraction */
  real charn_hcn_frac[MAX_FUEL_STREAMS];  /* char nitrogen to hcn conversion fraction */
  real charn_nh3_frac[MAX_FUEL_STREAMS];  /* char nitrogen to nh3 conversion fraction */
  real bet_area[MAX_FUEL_STREAMS];        /* BET surface area (m^2/kg) (solid fuel) */
  int  nh3_switch;                        /* A switch to set nh3 source term to old method */

  /* N2O Path */
  cxboolean n2opath_nox;
  int  n2opath_n2o_model;                 /*Quasi-steady, Transported-simple, Transported-extended*/
  int  n2opath_o_mode;
  int  n2opath_oh_mode;
  /* Reburn */
  cxboolean reburn_nox;
  int  reburn_model;
  int  nrbspe;                            /* number of reburn fuel species */
  int  reburn_fuel_type;
  real reburn_modno_rate;
  real reburn_modhcn_rate;
  real reburn_temp_min;
  real reburn_temp_max;
  /* SNCR */
  cxboolean sncr_nox;
  char *sncr_species;
  int  sncr_chem_model;
  real sncr_temp_min;
  real sncr_temp_max;
  real sncr_o2vf_limit;
  cxboolean sncr_co_shift;
  real sncr_co_ts[2];
  int urea_decomp_model;
  real urea_to_nh3_frac;
  real urea_to_hnco_frac;
  /* User defined NO or Other */
  cxboolean user_nox;
  cxboolean thermal_udf_replace, prompt_udf_replace, fuel_udf_replace, n2opath_udf_replace;
  cxboolean sncr_udf_replace;
  Tci_Params tci_params;
} NOx_Parameter;

extern FLUENT_EXPORT NOx_Parameter *NOx;

FLUENT_EXPORT int Nox_Init(Domain *domain);
FLUENT_EXPORT void NOx_kinetics(Domain *domain);
FLUENT_EXPORT void NOx_rates(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Rate *s_pollut,
                             int *Num_Pdf_Interp_Vars, int *Pdf_Interp_Vars);
FLUENT_EXPORT void nox_rate(cell_t c, Thread *t, Pollut_Cell *Pollut, real noxr[]);
FLUENT_EXPORT void call_user_nox_rate(cell_t c, Thread *t, Pollut_Cell *Pollut);

FLUENT_EXPORT void fill_table_point_nox_data(Domain *domain, Table_Point *point, Pollut_Cell *Pollut);
FLUENT_EXPORT void Fill_Table_Point_Pollut_Data(cell_t c, Thread *t, Domain *domain, Table_Point *point,
                                                Pollut_Cell *Pollut, real *xx, int i0, int i1);
FLUENT_EXPORT extern void Alloc_or_Free_temp_pollut_memory(int flag, cxboolean *free_curve,
                                                           cxboolean *free_slice, cxboolean *free_vol);
FLUENT_EXPORT void Calculate_prompt_fuel_nox_rates(Domain *domain, Table_Point *point_mean,
                                                   Table_Point *point, Pollut_Cell *Pollut, int flag, real *xmean, real *x);

#endif /* _FLUENT_SG_NOX_H */
