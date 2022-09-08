/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SG_SOOT_H
#define _FLUENT_SG_SOOT_H

#include "dll.h"
#include "pdf_props.h"
#include "pdf_table.h"

/* Define constants, macros and prototypes for pollutants */
#define MAX_FUEL_STREAMS 3   /* Make sure to modify rpvar "pollut/max-fuel-streams" */

typedef enum
{
  NUCLEATION_MODEL_MB = 0,
  NUCLEATION_MODEL_MBH
} Soot_Nuc_Model;

typedef enum
{
  OXIDATION_MODEL_FJ = 0,
  OXIDATION_MODEL_LEE,
  OXIDATION_MODEL_USER
} Soot_Oxy_Model;

typedef struct Soot_struct
{
  cxboolean one_step, two_step, moss_brookes, moss_brookes_hall;
  cxboolean method_of_moments;
  cxboolean user_source_only;
  real soot_mdiam, soot_mdens, soot_pmass;
  real soot_stoic, fuel_stoic;
  real one_cf, one_n, one_acen, one_magnus;
  real equiv_min, equiv_max;
  real two_alpha, two_beta, two_magnus;
  real two_limit, two_branch, two_linear, two_exp, two_acen;
  real fuel_mole_fraction;

  int prec_from;
  int nprec, nsgrows;
  int nucleation_model, oxidation_model;
  /* moss/brookes soot model parameters */
  real calpha, cbeta, cgamma, talpha, tgamma;
  real nuc_exp_l, sgs_exp_m, sgs_exp_n;
  /* fenimore & jones oxidation parameters */
  real comega, coleff;
  real coxid; /* Oxidation model scaling constant */
  /* Hall extension */
  real c1hall, c2hall, t1hall, t2hall;
  /* Lee oxidation parameters */
  real c1lee, c2lee, t2lee;
  int o_mode, oh_mode;
  int nsfuel;
  int mixf_option, uds_id;
  real ncfuel[MAX_SOOT_FUEL], nhfuel[MAX_SOOT_FUEL], fuelmf[MAX_SOOT_FUEL];
  real oxid_o2mf, oxid_co2mf, oxid_h2omf, mwprec;
  real ncfuelmix, nhfuelmix, eta, b_fuel, b_oxid;
  real prec_coeff[MAX_PREC_COEFF];
  cxboolean coal_derived, solve_ctar;
  Tci_Params tci_params;
} Soot_Parameter;

enum
{
  UDF_NUC = 0,
  UDF_COAG
};
enum
{
  UDF_MASS_NUC = 0,
  UDF_MASS_SGS,
  UDF_MASS_OXID
};
typedef struct Soot_mom_struct
{
  cxboolean nuc_mech;
  int n_nuc_reactions;
  double diam_catom;
  double mean_free_path;
  double free_ca_limit;
  double cont_ca_limit;
  double nnorm;
  real soot_site_dens;
  int interp_order;
  int interp_order_agg;
  int exterp_order;
  int gfn_interp_order;
  double ca_free_fac;
  double crit_diam_fac;
  double soot_min_dia;
  int soot_min_nc;
  cxboolean sgs_user_mech;
  int num_sgs_rxns;
  real crit_diam_agg;
  real fract_dim;
} Soot_Mom_Param;

extern FLUENT_EXPORT Soot_Parameter *Soot;
extern FLUENT_EXPORT Soot_Mom_Param *Soot_Mom;
FLUENT_EXPORT int Soot_Init(Domain *domain);
FLUENT_EXPORT void SOOT_rates(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Rate *s_pollut,
                              int *Num_Pdf_Interp_Vars, int *Pdf_Interp_Vars);
FLUENT_EXPORT void soot_rate(Pollut_Cell *Pollut, real sootr[]);
FLUENT_EXPORT void SOOT_kinetics(Domain *domain);
FLUENT_EXPORT void fill_table_point_soot_data(Domain *domain, Table_Point *point, Pollut_Cell *Pollut);
FLUENT_EXPORT int Init_Soot_Mom_Vars(Domain *domain);

extern FLUENT_EXPORT cxboolean clip_moment_vars ;

#define C_SOOT_MOM_CLIP(c,t,i) (clip_moment_vars? C_SOOT_MOM(c,t,i): \
                                ((i > 0)? MAX(1e-15, MAX(C_SOOT_MOM(c,t,i-1),C_SOOT_MOM(c,t,i))):\
                                 MAX(1e-15, C_SOOT_MOM(c,t,i))))\

#define C_SOOT_MOM_AGG_CLIP(c,t,i) (clip_moment_vars? C_SOOT_MOM_AGG(c,t,i): \
                                ((i > 0)? MAX(1e-15, MAX(C_SOOT_MOM_AGG(c,t,i-1),C_SOOT_MOM_AGG(c,t,i))):\
                                 MAX(1e-15, C_SOOT_MOM_AGG(c,t,i))))\

#endif /* _FLUENT_SG_SOOT_H */
