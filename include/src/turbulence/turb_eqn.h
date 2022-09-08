/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */


#ifndef _FLUENT_TURBULENCE_EQUATION__H
#define _FLUENT_TURBULENCE_EQUATION__H


/**
 * \file
 * \brief External API header file for turbulence differential equations.
 */


#include "turb.h"

#include "global.h"
#include "mem.h"


typedef struct controls_turb_eqn_struct
{
  real trans_model_one_eqn_ca2;
  real trans_model_one_eqn_ce2;
  real trans_model_one_eqn_lam1;
  real trans_model_one_eqn_lam2;
  real trans_model_one_eqn_tu_fac;
  real trans_model_one_eqn_lam2_cf;
  real trans_model_one_eqn_lam_cf_max;
  real trans_model_one_eqn_cg01;
  real trans_model_one_eqn_cg02;
  real trans_model_one_eqn_cg03;
  real trans_model_one_eqn_coef_g;
  real trans_model_one_eqn_g0_max;
  real trans_model_one_eqn_crev_cf;

  real ke_sbes_cmu;

  real coeff_ke_mu_dok;
  real coeff_kw_mu_dok;

  real sst_po_lam_factor;

  real kw_vorticity_pk;

  real sst_kato_launder;
  real sst_production_limiter;
  real trans_sst_production_limiter;

  cxboolean vol_syn_turbulence;
} controls_turb_eqn_type;


typedef void(*Linearized_Sources_Fcn_Type)(controls_turb_eqn_type *PTR_RESTRICT const setup,
                                           cell_t c, Thread *t,
                                           cxboolean compress_mod,
                                           cxboolean user_turb_viscosity,
                                           cxboolean buoyancy_tke,
                                           cxboolean buoyancy_tdr,
                                           real axis[3],
                                           real omega,
                                           real(*PTR_RESTRICT const u_g)[ND_ND],
                                           real(*PTR_RESTRICT const v_g)[ND_ND],
                                           real(*PTR_RESTRICT const w_g)[ND_ND],
                                           real(*PTR_RESTRICT const k_g)[ND_ND],
                                           real(*PTR_RESTRICT const d_g)[ND_ND],
                                           real(*PTR_RESTRICT const o_g)[ND_ND],
                                           real(*PTR_RESTRICT const omega_g)[ND_ND],
                                           real(*PTR_RESTRICT const centroid)[ND_ND],
                                           real *PTR_RESTRICT const volume,
                                           real *PTR_RESTRICT const tvolume,
                                           real *PTR_RESTRICT const u,
                                           real *PTR_RESTRICT const v,
                                           real *PTR_RESTRICT const w,
                                           real *PTR_RESTRICT const ruu,
                                           real *PTR_RESTRICT const rvv,
                                           real *PTR_RESTRICT const rww,
                                           real *PTR_RESTRICT const production,
                                           real *PTR_RESTRICT const production_l,
                                           real *PTR_RESTRICT const buoy_prod,
                                           real *PTR_RESTRICT const c_epsilon,
                                           real *PTR_RESTRICT const k,
                                           real *PTR_RESTRICT const kl,
                                           real *PTR_RESTRICT const kt,
                                           real *PTR_RESTRICT const d,
                                           real *PTR_RESTRICT const o,
                                           real *PTR_RESTRICT const v2,
                                           real *PTR_RESTRICT const fel,
                                           real *PTR_RESTRICT const mu_t,
                                           real *PTR_RESTRICT const mu,
                                           real *PTR_RESTRICT const rho,
                                           real *PTR_RESTRICT const wall_dist,
                                           real const sound_speed_2,
                                           real const divV,
                                           real const Dterm,
                                           real const Rterm,
                                           real const Rnat,
                                           real *s, real *ap, Svar sv_phi);

typedef void(*Wall_Coeffs_Fcn_Type)(Thread *t,
                                    Thread *tp,
                                    Svar sv_phi,
                                    Svar sv_phi_ap,
                                    Svar sv_phi_s,
                                    Svar sv_phi_g,
                                    Svar sv_flux,
                                    Svar sv_vof,
                                    int pass);

typedef void(*In_Out_Fcn_Type)(Thread *t,
                               struct tv_vi_struct *vi,
                               Svar sv_flux);

typedef void(*Two_Layer_Model_Fcn_Type)(Domain *domain,
                                        Svar sv_phi,
                                        Svar sv_phi_ap,
                                        Svar sv_phi_s,
                                        int amg_id,
                                        int phase);

/* Buoyancy effects in turbulence production?
 */
FLUENT_EXPORT cxboolean if_turb_buoyancy_effects_production(void);

/* Full buoyancy effects in turbulence model?
 */
FLUENT_EXPORT cxboolean if_turb_buoyancy_effects_full(void);

FLUENT_EXPORT cxboolean User_Turb_Viscosity_P(Domain *);
FLUENT_EXPORT void Update_Turbulent_Viscosity(Domain *domain,
                                              cxboolean update_tke,
                                              Turb_Model_Type turb_model,
                                              cxboolean relax,
                                              cxboolean init_only);


FLUENT_EXPORT void Solve_Turb_Eqn(Domain *domain,
                                  Svar sv_phi, Svar sv_phi_g, Svar sv_phi_rg,
                                  Svar sv_phi_ap, Svar sv_phi_s, Svar sv_phi_residual,
                                  Svar sv_flux, Svar sv_vof, Svar sv_vof_m1,
                                  Svar sv_sqrt_phi, Svar sv_sqrt_phi_g, Svar sv_sqrt_phi_rg, Svar sv_k, Svar sv_dterm,
                                  cxboolean time_marching,
                                  cxboolean buoyancy_tke,
                                  cxboolean buoyancy_tdr,
                                  UDF_Prt_Type user_prandtl,
                                  Turb_BC_Type bc_type,
                                  char *title, real alpha, real beta,
                                  int cycle_type, int amg_method, int amg_stabilization, int eqn, int amg_id, int amg_i,
                                  real min_phi, real relax, real trb_pr,
                                  In_Out_Fcn_Type in_out,
                                  Wall_Coeffs_Fcn_Type wall_coeffs,
                                  Two_Layer_Model_Fcn_Type two_layer_model,
                                  Linearized_Sources_Fcn_Type linearized_sources,
                                  int sub_iter,
                                  int max_sub_iter,
                                  cxboolean need_explicit,
                                  real explicit_relax,
                                  real iter_tolerance,
                                  real res_tolerance,
                                  cxboolean *stop_iteration);


FLUENT_EXPORT void Compute_Linearized_retheta_Sources(controls_turb_eqn_type *PTR_RESTRICT const setup,
                                                      cell_t c, Thread *t,
                                                      cxboolean compress_mod,
                                                      cxboolean user_turb_viscosity,
                                                      cxboolean buoyancy_tke,
                                                      cxboolean buoyancy_tdr,
                                                      real axis[3],
                                                      real omega,
                                                      real(*PTR_RESTRICT const u_g)[ND_ND],
                                                      real(*PTR_RESTRICT const v_g)[ND_ND],
                                                      real(*PTR_RESTRICT const w_g)[ND_ND],
                                                      real(*PTR_RESTRICT const k_g)[ND_ND],
                                                      real(*PTR_RESTRICT const d_g)[ND_ND],
                                                      real(*PTR_RESTRICT const o_g)[ND_ND],
                                                      real(*PTR_RESTRICT const omega_g)[ND_ND],
                                                      real(*PTR_RESTRICT const centroid)[ND_ND],
                                                      real *PTR_RESTRICT const vol,
                                                      real *PTR_RESTRICT const tvol,
                                                      real *PTR_RESTRICT const u,
                                                      real *PTR_RESTRICT const v,
                                                      real *PTR_RESTRICT const w,
                                                      real *PTR_RESTRICT const ruu,
                                                      real *PTR_RESTRICT const rvv,
                                                      real *PTR_RESTRICT const rww,
                                                      real *PTR_RESTRICT const production,
                                                      real *PTR_RESTRICT const production_l,
                                                      real *PTR_RESTRICT const buoy_prod,
                                                      real *PTR_RESTRICT const ceps,
                                                      real *PTR_RESTRICT const k,
                                                      real *PTR_RESTRICT const kl,
                                                      real *PTR_RESTRICT const kt,
                                                      real *PTR_RESTRICT const d,
                                                      real *PTR_RESTRICT const o,
                                                      real *PTR_RESTRICT const v2,
                                                      real *PTR_RESTRICT const fel,
                                                      real *PTR_RESTRICT const mu_t,
                                                      real *PTR_RESTRICT const mu,
                                                      real *PTR_RESTRICT const rho,
                                                      real *PTR_RESTRICT const wall_dist,
                                                      real const sound_speed_2,
                                                      real const divV,
                                                      real const Dterm,
                                                      real const Rterm,
                                                      real const Rnat,
                                                      real *s, real *ap, Svar sv_phi);

FLUENT_EXPORT void Compute_Linearized_tke_Sources(controls_turb_eqn_type *PTR_RESTRICT const setup,
                                                  cell_t c, Thread *t,
                                                  cxboolean compress_mod,
                                                  cxboolean user_turb_viscosity,
                                                  cxboolean buoyancy_tke,
                                                  cxboolean buoyancy_tdr,
                                                  real axis[3],
                                                  real omega,
                                                  real(*PTR_RESTRICT const u_g)[ND_ND],
                                                  real(*PTR_RESTRICT const v_g)[ND_ND],
                                                  real(*PTR_RESTRICT const w_g)[ND_ND],
                                                  real(*PTR_RESTRICT const k_g)[ND_ND],
                                                  real(*PTR_RESTRICT const d_g)[ND_ND],
                                                  real(*PTR_RESTRICT const o_g)[ND_ND],
                                                  real(*PTR_RESTRICT const omega_g)[ND_ND],
                                                  real(*PTR_RESTRICT const centroid)[ND_ND],
                                                  real *PTR_RESTRICT const vol,
                                                  real *PTR_RESTRICT const tvol,
                                                  real *PTR_RESTRICT const u,
                                                  real *PTR_RESTRICT const v,
                                                  real *PTR_RESTRICT const w,
                                                  real *PTR_RESTRICT const ruu,
                                                  real *PTR_RESTRICT const rvv,
                                                  real *PTR_RESTRICT const rww,
                                                  real *PTR_RESTRICT const production,
                                                  real *PTR_RESTRICT const production_l,
                                                  real *PTR_RESTRICT const buoy_prod,
                                                  real *PTR_RESTRICT const ceps,
                                                  real *PTR_RESTRICT const k,
                                                  real *PTR_RESTRICT const kl,
                                                  real *PTR_RESTRICT const kt,
                                                  real *PTR_RESTRICT const d,
                                                  real *PTR_RESTRICT const o,
                                                  real *PTR_RESTRICT const v2,
                                                  real *PTR_RESTRICT const fel,
                                                  real *PTR_RESTRICT const mu_t,
                                                  real *PTR_RESTRICT const mu,
                                                  real *PTR_RESTRICT const rho,
                                                  real *PTR_RESTRICT const wall_dist,
                                                  real const sound_speed_2,
                                                  real const divV,
                                                  real const Dterm,
                                                  real const Rterm,
                                                  real const Rnat,
                                                  real *s, real *ap, Svar sv_phi);

FLUENT_EXPORT void Compute_Linearized_tdr_Sources(controls_turb_eqn_type *PTR_RESTRICT const setup,
                                                  cell_t c, Thread *t,
                                                  cxboolean compress_mod,
                                                  cxboolean user_turb_viscosity,
                                                  cxboolean buoyancy_tke,
                                                  cxboolean buoyancy_tdr,
                                                  real axis[3],
                                                  real omega,
                                                  real(*PTR_RESTRICT const u_g)[ND_ND],
                                                  real(*PTR_RESTRICT const v_g)[ND_ND],
                                                  real(*PTR_RESTRICT const w_g)[ND_ND],
                                                  real(*PTR_RESTRICT const k_g)[ND_ND],
                                                  real(*PTR_RESTRICT const d_g)[ND_ND],
                                                  real(*PTR_RESTRICT const o_g)[ND_ND],
                                                  real(*PTR_RESTRICT const omega_g)[ND_ND],
                                                  real(*PTR_RESTRICT const centroid)[ND_ND],
                                                  real *PTR_RESTRICT const vol,
                                                  real *PTR_RESTRICT const tvol,
                                                  real *PTR_RESTRICT const u,
                                                  real *PTR_RESTRICT const v,
                                                  real *PTR_RESTRICT const w,
                                                  real *PTR_RESTRICT const ruu,
                                                  real *PTR_RESTRICT const rvv,
                                                  real *PTR_RESTRICT const rww,
                                                  real *PTR_RESTRICT const production,
                                                  real *PTR_RESTRICT const production_l,
                                                  real *PTR_RESTRICT const buoy_prod,
                                                  real *PTR_RESTRICT const ceps,
                                                  real *PTR_RESTRICT const k,
                                                  real *PTR_RESTRICT const kl,
                                                  real *PTR_RESTRICT const kt,
                                                  real *PTR_RESTRICT const d,
                                                  real *PTR_RESTRICT const o,
                                                  real *PTR_RESTRICT const v2,
                                                  real *PTR_RESTRICT const fel,
                                                  real *PTR_RESTRICT const mu_t,
                                                  real *PTR_RESTRICT const mu,
                                                  real *PTR_RESTRICT const rho,
                                                  real *PTR_RESTRICT const wall_dist,
                                                  real const sound_speed_2,
                                                  real const divV,
                                                  real const Dterm,
                                                  real const Rterm,
                                                  real const Rnat,
                                                  real *s, real *ap, Svar sv_phi);

FLUENT_EXPORT void Compute_Linearized_sdr_Sources(controls_turb_eqn_type *PTR_RESTRICT const setup,
                                                  cell_t c, Thread *t,
                                                  cxboolean compress_mod,
                                                  cxboolean user_turb_viscosity,
                                                  cxboolean buoyancy_tke,
                                                  cxboolean buoyancy_tdr,
                                                  real axis[3],
                                                  real omega,
                                                  real(*PTR_RESTRICT const u_g)[ND_ND],
                                                  real(*PTR_RESTRICT const v_g)[ND_ND],
                                                  real(*PTR_RESTRICT const w_g)[ND_ND],
                                                  real(*PTR_RESTRICT const k_g)[ND_ND],
                                                  real(*PTR_RESTRICT const d_g)[ND_ND],
                                                  real(*PTR_RESTRICT const o_g)[ND_ND],
                                                  real(*PTR_RESTRICT const omega_g)[ND_ND],
                                                  real(*PTR_RESTRICT const centroid)[ND_ND],
                                                  real *PTR_RESTRICT const vol,
                                                  real *PTR_RESTRICT const tvol,
                                                  real *PTR_RESTRICT const u,
                                                  real *PTR_RESTRICT const v,
                                                  real *PTR_RESTRICT const w,
                                                  real *PTR_RESTRICT const ruu,
                                                  real *PTR_RESTRICT const rvv,
                                                  real *PTR_RESTRICT const rww,
                                                  real *PTR_RESTRICT const production,
                                                  real *PTR_RESTRICT const production_l,
                                                  real *PTR_RESTRICT const buoy_prod,
                                                  real *PTR_RESTRICT const ceps,
                                                  real *PTR_RESTRICT const k,
                                                  real *PTR_RESTRICT const kl,
                                                  real *PTR_RESTRICT const kt,
                                                  real *PTR_RESTRICT const d,
                                                  real *PTR_RESTRICT const o,
                                                  real *PTR_RESTRICT const v2,
                                                  real *PTR_RESTRICT const fel,
                                                  real *PTR_RESTRICT const mu_t,
                                                  real *PTR_RESTRICT const mu,
                                                  real *PTR_RESTRICT const rho,
                                                  real *PTR_RESTRICT const wall_dist,
                                                  real const sound_speed_2,
                                                  real const divV,
                                                  real const Dterm,
                                                  real const Rterm,
                                                  real const Rnat,
                                                  real *s, real *ap, Svar sv_phi);

FLUENT_EXPORT void Compute_Linearized_intermit_Sources(controls_turb_eqn_type *PTR_RESTRICT const setup,
                                                       cell_t c,
                                                       Thread *t,
                                                       cxboolean compress_mod,
                                                       cxboolean user_turb_viscosity,
                                                       cxboolean buoyancy_tke,
                                                       cxboolean buoyancy_tdr,
                                                       real axis[3],
                                                       real omega,
                                                       real(* PTR_RESTRICT const u_g)[ND_ND],
                                                       real(* PTR_RESTRICT const v_g)[ND_ND],
                                                       real(* PTR_RESTRICT const w_g)[ND_ND],
                                                       real(* PTR_RESTRICT const k_g)[ND_ND],
                                                       real(* PTR_RESTRICT const d_g)[ND_ND],
                                                       real(* PTR_RESTRICT const o_g)[ND_ND],
                                                       real(* PTR_RESTRICT const omega_g) [ND_ND],
                                                       real(* PTR_RESTRICT const centroid)[ND_ND],
                                                       real *PTR_RESTRICT const vol,
                                                       real *PTR_RESTRICT const tvol,
                                                       real *PTR_RESTRICT const u,
                                                       real *PTR_RESTRICT const v,
                                                       real *PTR_RESTRICT const w,
                                                       real *PTR_RESTRICT const ruu,
                                                       real *PTR_RESTRICT const rvv,
                                                       real *PTR_RESTRICT const rww,
                                                       real *PTR_RESTRICT const production,
                                                       real *PTR_RESTRICT const production_l,
                                                       real *PTR_RESTRICT const buoy_prod,
                                                       real *PTR_RESTRICT const ceps,
                                                       real *PTR_RESTRICT const k,
                                                       real *PTR_RESTRICT const kl,
                                                       real *PTR_RESTRICT const kt,
                                                       real *PTR_RESTRICT const d,
                                                       real *PTR_RESTRICT const o,
                                                       real *PTR_RESTRICT const v2,
                                                       real *PTR_RESTRICT const fel,
                                                       real *PTR_RESTRICT const mu_t,
                                                       real *PTR_RESTRICT const mu,
                                                       real *PTR_RESTRICT const rho,
                                                       real *PTR_RESTRICT const wall_dist,
                                                       real const sound_speed_2,
                                                       real const divV,
                                                       real const Dterm,
                                                       real const Rterm,
                                                       real const Rnat,
                                                       real *s,
                                                       real *ap,
                                                       Svar sv_phi);


#endif
