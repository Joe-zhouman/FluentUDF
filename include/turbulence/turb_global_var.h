/*
 * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */


#ifndef _FLUENT_TURBULENCE_GLOBAL_VAR_H
#define _FLUENT_TURBULENCE_GLOBAL_VAR_H


/**
 * \file
 * \brief Header file with global variables.
 */


#include "cxbool.h"
#include "dll.h"
#include "global.h"


/**
 * \def
 * \brief External API for global turbulence variables. E.g.
 * GVAR_TURB(rp, les_rng) translates to turb_global_rp.les_rng.
 */
#define GVAR_TURB(str, var) (turb_global_##str.var)


/**
 * \brief Container for global turbulence rp_vars.
 */
typedef struct turb_global_rpvar_struct
{
  cxboolean atm;                 /** Mixing-length turbulence model (for IcePak) */
  cxboolean hvac;                /** Zero-equation turbulence model (for AirPak) */

  cxboolean ke;                  /** TRUE if any k-epsilon; FALSE if rsm */
  cxboolean ke_rng;              /** RNG k-epsilon model */
  cxboolean ke_real;             /** Realizable k-epsilon model */
  cxboolean ke_rg_std_earsm;     /** Rumsey-Gatski-(std-k-epsilon)-EARSM model */
  cxboolean ke_lowRe;            /** Low-Re k-epsilon model */
  cxboolean kw;                  /** TRUE if ant k-omega model; std or sst */
  cxboolean kw_std;              /** Std k-omega model */
  cxboolean kw_bsl;              /** BSL k-omega model */
  cxboolean kw_geko;             /** Generalized k-omega model (GEKO) */
  cxboolean kw_sst;              /** SST k-omega model */
  cxboolean kw_rg_std_earsm;     /** Rumsey-Gatski-(std-k-omega)-EARSM model */
  cxboolean kw_wj_bsl_earsm;     /** Wallin-Johansson-(bsl-k-omega)-EARSM model */
  cxboolean kklw;                /** Transition k-kl-omega   model */
  cxboolean sas;                 /** SAS model */
  cxboolean do_trans_one_eqn;    /** Solve intermittency transition model */
  cxboolean do_trans_algebraic;  /** Solve algebraic transition model */
  cxboolean trans_sst;           /** Transition SST model from CFX */
  cxboolean trans_intermit_smoothing; /** Smoothing of intermittency */
  cxboolean trans_harmonic_averaged_tke_for_tu; /** Harmonic averaging of tke for Tu */
  cxboolean machine_learning;    /** Enable generic machine learning terms */
  cxboolean machine_learning_wj_earsm_beta_coeffs; /** Enable variable beta coefficients of WJ-EARSM for machine learning */
  cxboolean consistent_specified_stress_bc; /** Consistent specified stress bc */
  cxboolean v2f;                 /** V2F model */

  cxboolean des;                 /** DES model */
  cxboolean des_sa;              /** DES model based on S-A equation */
  cxboolean des_ke_real;         /** DES model based on RKE */
  cxboolean des_kw_sst;          /** DES model based on SST */

  cxboolean les;                 /** LES subgrid-scale model */
  cxboolean les_rng;             /** RNG LES subgrid-scale model */
  cxboolean les_wale;            /** WALE LES subgrid-scale model */
  cxboolean les_wmles;           /** WMLES LES subgrid-scale model */
  cxboolean les_wmles_SmnsOmg;   /** WMLES S-O LES subgrid-scale model */
  cxboolean les_sgske;           /** RNG LES subgrid-scale model */
  cxboolean les_dynamic;         /** LES dynamic subgrid-scale model */
  cxboolean les_dynamic_mixed;   /** LES dynamic mixed subgrid-scale model */
  cxboolean les_dynamic_energy;  /** LES dynamic subgrid-scale model to determine Turb. Prandtl no. */
  cxboolean les_dynamic_species; /** LES dynamic subgrid-scale model to determine Turb. Schmidt no. */

  cxboolean rsm;                 /** Reynolds-stress model */

  cxboolean wt_enh;              /** Enhanced wall function */
  cxboolean wt_scalable;         /** Scalable wall function */
  cxboolean wt_neq;              /** Non-equlibrium wall functions */
  cxboolean wt_ke_two_layer;     /** Two layer model */
  cxboolean wt_ml;               /** Menter-Lechner near wall treatment */
  cxboolean wt_ww;               /** Werner-Wengle wall functions for LES */
  cxboolean wt_udf;              /** User defined wall treatment */
} turb_global_rpvar_type;


/**
* \brief Container for global turbulence coefficients.
*/
typedef struct turb_global_coeff_struct
{
  real ke_Cmu;                       /** Ke model constant */
  real ke_C1;                        /** Ke model constant */
  real ke_C2;                        /** Ke model constant */
  real ke_sige;                      /** Ke model constant */
  real ke_sigk;                      /** Ke model constant */
  real ke_prt;                       /** Ke model constant */

  real kw_alpha_star_inf;            /** Kw model constant */
  real kw_alpha_inf;                 /** Kw model constant */
  real kw_alpha_0;                   /** Kw model constant */
  real kw_beta_star_inf;             /** Kw model constant */
  real kw_r_beta;                    /** Kw model constant */
  real kw_r_k;                       /** Kw model constant */
  real kw_r_w;                       /** Kw model constant */
  real kw_zeta_star;                 /** Kw model constant */
  real kw_mt0;                       /** Kw model constant */
  real kw_alpha_star_0;              /** Kw model constant */

  real bsl_sig_k1;                   /** BSL model constant */
  real bsl_sig_k2;                   /** BSL model constant */
  real bsl_sig_w1;                   /** BSL model constant */
  real bsl_sig_w2;                   /** BSL model constant */
  real bsl_beta_i1;                  /** BSL model constant */
  real bsl_beta_i2;                  /** BSL model constant */
  real bsl_alpha_inf1;               /** BSL model constant */
  real bsl_alpha_inf2;               /** BSL model constant */

  real sst_sig_k1;                   /** SST model constant */
  real sst_sig_k2;                   /** SST model constant */
  real sst_sig_w1;                   /** SST model constant */
  real sst_sig_w2;                   /** SST model constant */
  real sst_beta_i1;                  /** SST model constant */
  real sst_beta_i2;                  /** SST model constant */
  real sst_a1;                       /** SST model constant */
  real sst_alpha_inf1;               /** SST model constant */
  real sst_alpha_inf2;               /** SST model constant */
  real sst_pk_factor;                /** SST model constant */
  real sst_cdes_i1;                  /** SST model constant */
  real sst_cdes_i2;                  /** SST model constant */
  real sst_ddes_Cd1;                 /** SST model constant */

  real geko_coeff;                   /** GEKO model constant */
  real geko_sig_k;                   /** GEKO model constant */
  real geko_sig_w;                   /** GEKO model constant */
  real geko_beta;                    /** GEKO model constant */
  real geko_csep;                    /** GEKO model constant */
  real geko_cnw;                     /** GEKO model constant */
  real geko_cnw_sub;                 /** GEKO model constant */
  real geko_cmix;                    /** GEKO model constant */
  real geko_cjet;                    /** GEKO model constant */
  real geko_cjet_aux;                /** GEKO model constant */
  real geko_creal;                   /** GEKO model constant */
  real geko_bf_blend;                /** GEKO model constant */
  real geko_bf_blam;                 /** GEKO model constant */
  real geko_bf_tur;                  /** GEKO model constant */
  real geko_bf_lam;                  /** GEKO model constant */

  real rg_std_earsm_C10;             /** Rumsey-Gatski-EARSM model constant */
  real rg_std_earsm_C11;             /** Rumsey-Gatski-EARSM model constant */
  real rg_std_earsm_C2;              /** Rumsey-Gatski-EARSM model constant */
  real rg_std_earsm_C3;              /** Rumsey-Gatski-EARSM model constant */
  real rg_std_earsm_C4;              /** Rumsey-Gatski-EARSM model constant */
  real rg_std_earsm_a1;              /** Rumsey-Gatski-EARSM model constant */
  real rg_std_earsm_a2;              /** Rumsey-Gatski-EARSM model constant */
  real rg_std_earsm_a3;              /** Rumsey-Gatski-EARSM model constant */
  real rg_std_earsm_gama0_star;      /** Rumsey-Gatski-EARSM model constant */
  real rg_std_earsm_gama1_star;      /** Rumsey-Gatski-EARSM model constant */

  real rg_kw_std_earsm_Cmu;          /** Rumsey-Gatski-(std-k-omega)-EARSM model constant */
  real rg_kw_std_earsm_gama;         /** Rumsey-Gatski-(std-k-omega)-EARSM model constant */
  real rg_kw_std_earsm_beta;         /** Rumsey-Gatski-(std-k-omega)-EARSM model constant */

  real wj_bsl_earsm_a1;              /** Wallin-Johansson-EARSM model constant */
  real wj_bsl_earsm_a3;              /** Wallin-Johansson-EARSM model constant */
  real wj_bsl_earsm_a4;              /** Wallin-Johansson-EARSM model constant */
  real wj_bsl_earsm_cMu;             /** Wallin-Johansson-EARSM model constant */
  real wj_bsl_earsm_c1_prime;        /** Wallin-Johansson-EARSM model constant */
  real wj_bsl_earsm_nEq;             /** Wallin-Johansson-EARSM model constant */
  real wj_bsl_earsm_cDiff;           /** Wallin-Johansson-EARSM model constant */
  real wj_bsl_earsm_beta_fact;       /** Wallin-Johansson-EARSM model constant */

  real v2f_enn;                      /** V2F model constant */
  real v2f_c1;                       /** V2F model constant */
  real v2f_c2;                       /** V2F model constant */
  real v2f_ceta;                     /** V2F model constant */
  real v2f_cl;                       /** V2F model constant */
  real v2f_alpha;                    /** V2F model constant */

  real sas_term_cmu;                 /** SAS model constant */
  real sas_term_beta_i1;             /** SAS model constant */
  real sas_term_beta_i2;             /** SAS model constant */
  real sas_term_alpha_i1;            /** SAS model constant */
  real sas_term_alpha_i2;            /** SAS model constant */
  real sas_cross_derivative_sig_w2;  /** SAS model constant */
  real sas_term_const_alpha;         /** SAS model constant */
  real sas_term_const_beta;          /** SAS model constant */

  real sbes_cs;                      /** SBES model constant */
  real sbes_csdes;                   /** SBES model constant */
  real sbes_cnu;                     /** SBES model constant */
  real sbes_cbl;                     /** SBES model constant */
  real sbes_cvtm;                    /** SBES model constant */
  real sbes_cgrid;                   /** SBES model constant */

  real trans_Cmu;                    /** Transition model constant */
  real trans_Clam;                   /** Transition model constant */
  real trans_Anu;                    /** Transition model constant */
  real trans_Cw1;                    /** Transition model constant */
  real trans_Cw3;                    /** Transition model constant */
  real trans_CINT;                   /** Transition model constant */
  real trans_Abp;                    /** Transition model constant */
  real trans_Cbpcrit;                /** Transition model constant */
  real trans_CR;                     /** Transition model constant */
  real trans_ANAT;                   /** Transition model constant */
  real trans_ATS;                    /** Transition model constant */
  real trans_CNATcrit;               /** Transition model constant */
  real trans_CTScrit;                /** Transition model constant */
  real trans_CRNAT;                  /** Transition model constant */
  real trans_Calpha_teta;            /** Transition model constant */
  real trans_Ctaul;                  /** Transition model constant */
  real trans_sig_k;                  /** Transition model constant */
  real trans_sig_w;                  /** Transition model constant */

  real trans_one_eqn_ctu1;           /** Transition model constant */
  real trans_one_eqn_ctu2;           /** Transition model constant */
  real trans_one_eqn_ctu3;           /** Transition model constant */
  real trans_one_eqn_cpg1;           /** Transition model constant */
  real trans_one_eqn_cpg2;           /** Transition model constant */
  real trans_one_eqn_cpg3;           /** Transition model constant */
  real trans_one_eqn_csep;           /** Transition model constant */
  real trans_one_eqn_sig;            /** Transition model constant */
  real trans_one_eqn_lim_cpg1;       /** Transition model constant */
  real trans_one_eqn_lim_cpg2;       /** Transition model constant */
  real trans_one_eqn_tke_term_coef;  /** Transition model constant */
  real trans_one_eqn_crossflow_crsf; /** Transition model constant */

  real trans_alg_rv1_switch;         /** Transition model constant */
  real trans_alg_cbubble_c1;         /** Transition model constant */
  real trans_alg_cbubble_c2;         /** Transition model constant */
  real trans_alg_ctu_higtu;          /** Transition model constant */
  real trans_alg_ctu_lowtu;          /** Transition model constant */
  real trans_alg_rec_max;            /** Transition model constant */
  real trans_alg_rec_c1;             /** Transition model constant */
  real trans_alg_rec_c2;             /** Transition model constant */
  real trans_alg_clambda_scale;      /** Transition model constant */
  real trans_alg_capg_higtu;         /** Transition model constant */
  real trans_alg_cfpg_higtu;         /** Transition model constant */
  real trans_alg_capg_lowtu;         /** Transition model constant */
  real trans_alg_cfpg_lowtu;         /** Transition model constant */

  real trans_sst_ca1;                /** Transition model constant */
  real trans_sst_ca2;                /** Transition model constant */
  real trans_sst_ce1;                /** Transition model constant */
  real trans_sst_ce2;                /** Transition model constant */
  real trans_sst_cthetat;            /** Transition model constant */
  real trans_sst_s1;                 /** Transition model constant */

  real wall_prt;                           /** Wall treatment model constant */
  real wall_Rey_c;                         /** Wall treatment model constant */
  real wall_ke_tl_A;                       /** Wall treatment model constant */
  real wall_ke_tl_A_mu;                    /** Wall treatment model constant */
  real wall_ke_tl_C_l_mu;                  /** Wall treatment model constant */
  real wall_ke_elog_udf;                   /** Wall treatment model constant */
  real wall_ke_yplus_udf;                  /** Wall treatment model constant */
  real wall_ke_nwt_ml_source_coeff;        /** Wall treatment model constant */
  real wall_ke_nwt_ml_wall_coeff;          /** Wall treatment model constant */
  real wall_ke_nwt_ml_c1;                  /** Wall treatment model constant */
  real wall_ke_nwt_ml_c2;                  /** Wall treatment model constant */
  real wall_wf_yp_prg;                     /** Wall treatment model constant */
  real wall_wf_beta_min;                   /** Wall treatment model constant */
  real wall_wf_beta_max;                   /** Wall treatment model constant */
  real wall_wf_gamma_min;                  /** Wall treatment model constant */
  real wall_wf_gamma_max;                  /** Wall treatment model constant */
  real wall_wf_vwplus_min;                 /** Wall treatment model constant */
  real wall_wf_vwplus_max;                 /** Wall treatment model constant */
  real wall_wf_thermal_han_and_reitz_beta; /** Wall treatment model constant */
  real wall_wf_ustar_limiter_coef;         /** Wall treatment model constant */
} turb_global_coeff_type;


extern FLUENT_EXPORT turb_global_rpvar_type turb_global_rp;
extern FLUENT_EXPORT turb_global_coeff_type turb_global_coeff;


#endif
