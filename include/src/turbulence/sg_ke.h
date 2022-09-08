/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SG_KE_H
#define _FLUENT_SG_KE_H

#include "turb.h"
#include "turb_eqn.h"

#include "dll.h"

#define SET_K_EFF(c0,t0,c1,t1,k0,k1)\
{\
  if (GVAR_TURB(rp, ke_rng) || GVAR_TURB(rp, les_rng))\
    {\
      if( M_thickened_flame )\
  {\
    k0 = C_RNG_ALPHA(c0,t0)*(C_MU_L(c0,t0)+C_TFM_OMEGA(c0,t0)*C_MU_T(c0,t0))*C_CP(c0,t0);\
    k1 = C_RNG_ALPHA(c1,t1)*(C_MU_L(c1,t1)+C_TFM_OMEGA(c1,t1)*C_MU_T(c1,t1))*C_CP(c1,t1);\
  }\
      else\
  {\
    k0 = C_RNG_ALPHA(c0,t0)*C_MU_EFF(c0,t0)*C_CP(c0,t0);\
    k1 = C_RNG_ALPHA(c1,t1)*C_MU_EFF(c1,t1)*C_CP(c1,t1);\
  }\
    }\
   else if (GVAR_TURB(rp, kklw))\
    {\
      real rho0 = C_R(c0,t0);\
      real rho1 = C_R(c1,t1);\
      real fac = (real)(2./3.);\
      real lambda0_T = sqrt(C_KT(c0,t0))/C_O(c0,t0);\
      real lambda1_T = sqrt(C_KT(c1,t1))/C_O(c1,t1);\
      real lambda0_eff = MIN(GVAR_TURB(coeff, trans_Clam)*C_WALL_DIST(c0,t0), lambda0_T);\
      real lambda1_eff = MIN(GVAR_TURB(coeff, trans_Clam)*C_WALL_DIST(c1,t1), lambda1_T);\
      real lambda0_fac = pow(lambda0_eff/lambda0_T, fac);\
      real lambda1_fac = pow(lambda1_eff/lambda1_T, fac);\
      k0 = (lambda0_fac*(C_KT(c0,t0)/(C_KL(c0,t0)+C_KT(c0,t0)))*C_MU_TS(c0,t0)/GVAR_TURB(coeff, ke_prt) + \
      GVAR_TURB(coeff, trans_Calpha_teta)*rho0*(1.-lambda0_fac)*sqrt(C_KT(c0,t0))*lambda0_eff )*C_CP(c0,t0);\
      k1 = (lambda1_fac*(C_KT(c1,t1)/(C_KL(c1,t1)+C_KT(c1,t1)))*C_MU_TS(c1,t1)/GVAR_TURB(coeff, ke_prt) + \
      GVAR_TURB(coeff, trans_Calpha_teta)*rho1*(1.-lambda1_fac)*sqrt(C_KT(c1,t1))*lambda1_eff )*C_CP(c1,t1);\
      if( M_thickened_flame )\
  {\
    k0 *= C_TFM_OMEGA(c0,t0);\
    k1 *= C_TFM_OMEGA(c1,t1);\
  }\
      k0 += C_K_L(c0,t0);\
      k1 += C_K_L(c1,t1);\
    }\
   else if (GVAR_TURB(rp, les_dynamic_energy))\
    {\
      real Pr0 = C_STORAGE_R(c0,t0,SV_LES_PRANDTL);\
      real Pr1 = C_STORAGE_R(c1,t1,SV_LES_PRANDTL);\
      k0 = C_K_EFF(c0,t0,Pr0);\
      k1 = C_K_EFF(c1,t1,Pr1);\
    }\
   else\
    {\
      if (user_prandtl)\
  {\
    real Pr0 = Compute_User_Prandtl(UDF_PRT_T,c0,t0);\
    real Pr1 = Compute_User_Prandtl(UDF_PRT_T,c1,t1);\
    k0 = C_K_EFF(c0,t0,Pr0);\
    k1 = C_K_EFF(c1,t1,Pr1);\
  }\
      else\
  {\
    k0 = C_K_EFF(c0,t0,GVAR_TURB(coeff, ke_prt));\
    k1 = C_K_EFF(c1,t1,GVAR_TURB(coeff, ke_prt));\
  }\
    }\
}

#define SET_K_EFF_INFLOW(c0,t0,k_eff)\
{\
  if (GVAR_TURB(rp, ke_rng) || GVAR_TURB(rp, les_rng))\
    {\
      if( M_thickened_flame )\
  k_eff = C_RNG_ALPHA(c0,t0)*(C_MU_L(c0,t0)+C_TFM_OMEGA(c0,t0)*C_MU_T(c0,t0))*C_CP(c0,t0);\
      else\
  k_eff = C_RNG_ALPHA(c0,t0)*C_MU_EFF(c0,t0)*C_CP(c0,t0);\
    }\
  else if (GVAR_TURB(rp, kklw))\
   {\
     real rho0 = C_R(c0,t0);\
     real fac = (real)(2./3.);\
     real lambda0_T =  sqrt(C_KT(c0,t0))/C_O(c0,t0);\
     real lambda0_eff = MIN(GVAR_TURB(coeff, trans_Clam)*C_WALL_DIST(c0,t0), lambda0_T);\
     real lambda0_fac = pow(lambda0_eff/lambda0_T, fac);\
     k_eff = (lambda0_fac*(C_KT(c0,t0)/(C_KL(c0,t0)+C_KT(c0,t0)))*C_MU_TS(c0,t0)/GVAR_TURB(coeff, ke_prt) + \
            GVAR_TURB(coeff, trans_Calpha_teta)*rho0*(1.-lambda0_fac)*sqrt(C_KT(c0,t0))*lambda0_eff) * C_CP(c0,t0) ;\
     if( M_thickened_flame ) k_eff *= C_TFM_OMEGA(c0,t0);\
     k_eff += C_K_L(c0,t0);\
   }\
  else\
   {\
     if (user_prandtl)\
       {\
   real Pr0 = Compute_User_Prandtl(UDF_PRT_T,c0,t0);\
   k_eff = C_K_EFF(c0,t0,Pr0);\
       }\
     else\
   k_eff = C_K_EFF(c0,t0,GVAR_TURB(coeff, ke_prt));\
   }\
}


FLUENT_EXPORT void Linearize_Negative_Source(Domain *domain,
                                             Svar sv_phi,
                                             Svar sv_phi_ap,
                                             Svar sv_phi_s);

FLUENT_EXPORT void Update_Boundary_Trb(Domain *domain,
                                       Svar sv_flux,
                                       Svar sv_phi,
                                       In_Out_Fcn_Type in_out);
FLUENT_EXPORT void In_Out_k(Thread *t, struct tv_vi_struct *vi, Svar sv_flux);
FLUENT_EXPORT void In_Out_d(Thread *t, struct tv_vi_struct *vi, Svar sv_flux);
FLUENT_EXPORT void In_Out_ksgs(Thread *t, struct tv_vi_struct *vi, Svar sv_flux);
FLUENT_EXPORT void In_Out_o(Thread *t, struct tv_vi_struct *vi, Svar sv_flux);

FLUENT_EXPORT cxboolean Has_Domain_Any_VM(Domain *d);

FLUENT_EXPORT void Init_Omega_Epsilon(Domain *domain);
FLUENT_EXPORT void Init_Wall_Normal_If_Needed(Domain *domain);
FLUENT_EXPORT void models_changed_download_for_getQsas(void);
FLUENT_EXPORT void Set_Local_LES_Const(Thread *t);
FLUENT_EXPORT void Set_All_Local_LES_Const(Domain *domain);

FLUENT_EXPORT void Wall_tke_Coeffs(Thread *t,
                                   Thread *tp,
                                   Svar sv_phi,
                                   Svar sv_phi_ap,
                                   Svar sv_phi_s,
                                   Svar sv_phi_g,
                                   Svar sv_flux,
                                   Svar sv_vof,
                                   int pass);

FLUENT_EXPORT void Wall_tdr_Coeffs(Thread *t,
                                   Thread *tp,
                                   Svar sv_phi,
                                   Svar sv_phi_ap,
                                   Svar sv_phi_s,
                                   Svar sv_phi_g,
                                   Svar sv_flux,
                                   Svar sv_vof,
                                   int pass);

FLUENT_EXPORT void Wall_sdr_Coeffs(Thread *t,
                                   Thread *tp,
                                   Svar sv_phi,
                                   Svar sv_phi_ap,
                                   Svar sv_phi_s,
                                   Svar sv_phi_g,
                                   Svar sv_flux,
                                   Svar sv_vof,
                                   int pass);

FLUENT_EXPORT void Compute_tke_Stress_Production(Domain *domain);
FLUENT_EXPORT void Compute_tke_Buoyancy_Production(Domain *domain,
                                                   UDF_Prt_Type user_prandtl);

FLUENT_EXPORT void Alloc_Strain_Rate_Derivative(Domain *domain);
FLUENT_EXPORT void Free_Strain_Rate_Derivative(Domain *domain);
FLUENT_EXPORT void Alloc_Curvature_Correction_Coefficient(Domain *domain);
FLUENT_EXPORT void Free_Curvature_Correction_Coefficient(Domain *domain);
FLUENT_EXPORT real Compute_Curvature_Correction(cell_t, Thread *);

FLUENT_EXPORT cxboolean do_sas_with_other_kw_model(void);
FLUENT_EXPORT cxboolean do_des_with_other_turb_model(void);
FLUENT_EXPORT cxboolean do_sbes_with_turb_model(void);

/**
 * \brief Checks if the RANS part of an SBES solution is updated at the current timestep.
 */
FLUENT_EXPORT cxboolean sbes_rans_is_updated(void);

FLUENT_EXPORT cxboolean CAN_do_sas_with_other_kw_model(void);
FLUENT_EXPORT cxboolean CAN_do_des_with_other_turb_model(void);
FLUENT_EXPORT cxboolean CAN_do_sbes_with_turb_model(void);


FLUENT_EXPORT void Turb_Scalar_Solve(Domain *domain,
                                     Svar sv_phi, Svar sv_phi_ap, Svar sv_phi_s,
                                     Svar sv_phi_residual,
                                     Turb_BC_Type bc_type,
                                     char *title,
                                     real alpha,
                                     real beta,
                                     int cycle_type,
                                     int amg_method,
                                     int amg_stabilization,
                                     int eqn,
                                     real min_phi,
                                     real relax,
                                     cxboolean time_marching,
                                     int sub_iter,
                                     int max_sub_iter,
                                     cxboolean need_explicit,
                                     real explicit_relax,
                                     real iter_tolerance,
                                     real res_tolerance,
                                     cxboolean  *stop_iteration);

FLUENT_EXPORT void Init_Coeffs(Domain *domain,
                               Svar sv_phi,
                               Svar sv_phi_g,
                               Svar sv_phi_rg,
                               Svar sv_phi_ap,
                               Svar sv_phi_s);

FLUENT_EXPORT void Update_Sqrt_Phi_Grad(Domain *domain,
                                        Svar sv_phi,
                                        Svar sv_phi_rg,
                                        Svar sv_phi_g,
                                        Svar sv_phi_k,
                                        Svar sv_dterm);

FLUENT_EXPORT void Turb_Wall_Diff_Coeffs(Domain *domain,
                                         Svar sv_phi,
                                         Svar sv_phi_g,
                                         Svar sv_phi_rg,
                                         Svar sv_phi_ap,
                                         Svar sv_phi_s,
                                         Svar sv_flux,
                                         Svar sv_vof,
                                         int amg_id,
                                         int amg_i,
                                         real Prt,
                                         Wall_Coeffs_Fcn_Type wall_coeffs);

FLUENT_EXPORT void Turb_Eqn_Sources(Domain *domain,
                                    Svar sv_phi,
                                    Svar sv_phi_ap,
                                    Svar sv_phi_s,
                                    Svar sv_vof,
                                    cxboolean buoyancy_tke,
                                    cxboolean buoyancy_tdr,
                                    Linearized_Sources_Fcn_Type linearized_sources);

FLUENT_EXPORT void Two_Layer_Model(Domain *domain,
                                   Svar sv_phi,
                                   Svar sv_phi_ap,
                                   Svar sv_phi_s,
                                   int amg_id,
                                   int phase);

FLUENT_EXPORT extern real
Compute_User_Prandtl(UDF_Prt_Type udf_prandtl, cell_t c, Thread *t);

FLUENT_EXPORT cxboolean if_rp_sa(void);
FLUENT_EXPORT cxboolean if_rp_spal_all_rans(void);
FLUENT_EXPORT cxboolean if_rp_ke_1e(void);
FLUENT_EXPORT cxboolean if_rp_any_les(void);
FLUENT_EXPORT cxboolean if_rp_les_des_sas(void);
FLUENT_EXPORT cxboolean if_rp_any_les_des_sas(void);
FLUENT_EXPORT cxboolean if_glob_turb_mod_for_rli(void);

/* Allow execution of TKE prandtl number UDF based on turbulence model?
 */
FLUENT_EXPORT cxboolean if_turb_mod_allows_pr_k_udf(void);

/* Allow execution of TDR prandtl number UDF based on turbulence model?
 */
FLUENT_EXPORT cxboolean if_turb_mod_allows_pr_d_udf(void);

/* Allow execution of SDR prandtl number UDF based on turbulence model?
 */
FLUENT_EXPORT cxboolean if_turb_mod_allows_pr_o_udf(void);

/* Allow execution of turbulent heat/energy diffusion prandtl number UDF based on turbulence model?
 */
FLUENT_EXPORT cxboolean if_turb_mod_allows_pr_t_udf(void);

/* Allow execution of turbulent heat/energy diffusion WALL prandtl number UDF based on turbulence model?
 */
FLUENT_EXPORT cxboolean if_turb_mod_allows_pr_t_wall_udf(void);

/* Allow execution of turbulent species diffusion schmidt number UDF based on turbulence model?
 */
FLUENT_EXPORT cxboolean if_turb_mod_allows_sc_t_udf(void);

FLUENT_EXPORT cxboolean if_asm(void);

FLUENT_EXPORT cxboolean if_mf_get_tke_expert(Domain *PTR_RESTRICT d);
FLUENT_EXPORT cxboolean if_mf_ke_expert(Domain *PTR_RESTRICT d);
FLUENT_EXPORT cxboolean if_mf_kw_expert(Domain *PTR_RESTRICT d);

FLUENT_EXPORT cxboolean if_rp_turb_rans(Domain *d);
FLUENT_EXPORT cxboolean Mu_t_Strain_Related(cxboolean allow_les);
FLUENT_EXPORT cxboolean Turb_Mod_Allows_Por_Jump_Turb_Wall_Treatment(void);
FLUENT_EXPORT cxboolean Do_Porous_Jump_Turbulent_Wall_Treatment(Thread *t);

FLUENT_EXPORT cxboolean Cross_Diffusion_Term_Needed_In_Turb_Model(void);
FLUENT_EXPORT cxboolean F1_Needed_In_Tke_Equation(void);
FLUENT_EXPORT cxboolean F1_Needed_In_Omega_Equation(void);
FLUENT_EXPORT cxboolean Wall_Dist_Needed_In_Turb_Model(void);

FLUENT_EXPORT extern void
Update_Face_Transport_Coeff(Domain *domain, Svar sv_phi, real Pr,
                            UDF_Prt_Type user_prandtl,
                            cxboolean do_sigma_blending, real Pr_2);


FLUENT_EXPORT real get_lowRe_damping_fmu(real rho, real k, real d, real y, real mu,
                                         Low_Re_Model_Type model_index);
FLUENT_EXPORT real get_lowRe_damping_f1(real rho, real k, real d, real y, real mu,
                                        real production, Low_Re_Model_Type model_index);
FLUENT_EXPORT real get_lowRe_damping_f2(real rho, real k, real d, real y, real mu,
                                        Low_Re_Model_Type model_index);
FLUENT_EXPORT real compute_keC3(real u, real v, real w);
FLUENT_EXPORT real f_beta(real u_g[], real v_g[], real w_g[], real omega_g[],
                          real axis[], real omega, real r, real v, real swirl,
                          real o);
FLUENT_EXPORT real variable_KeCmu(real u_g[], real v_g[], real w_g[], real omega_g[],
                                  real axis[], real omega, real v, real r, real swirl,
                                  real k, real d, real divV,
                                  cxboolean rke_cmu_rotation, cxboolean compress_mod);
FLUENT_EXPORT void Update_Geko_Coefficients_And_Bf(Domain *domain);
FLUENT_EXPORT real Get_Geko_Blending_Function_Pre193(cell_t c, Thread *t, real rho,
                                                     real mu, real wall_dist,
                                                     real tke, real omg, real k_g[], real o_g[]);
FLUENT_EXPORT real Get_Geko_Blending_Function(cell_t c, Thread *t, real rho,
                                              real mu, real wall_dist,
                                              real tke, real omg);
FLUENT_EXPORT void Update_bsl_sst_F1(Domain *domain);
FLUENT_EXPORT real get_sst_F1(real rho, real k, real o, real mu, real y,
                              real cross_deriv);
FLUENT_EXPORT real get_sst_F2(real rho, real k, real o, real mu, real y);
FLUENT_EXPORT real get_sst_Fdes(cell_t c, Thread *t, real rho, real k, real o,
                                real mu, real ls_rans, real wall_distance, real cdes);
FLUENT_EXPORT real get_sst_Fddes(cell_t c, Thread *t, real rho, real k, real o,
                                 real mu, real mu_t, real ls_rans, real wall_distance,
                                 real Smag, real cdes);
FLUENT_EXPORT real get_sst_Fiddes(cell_t c, Thread *t, real rho, real k, real o,
                                  real mu, real mu_t, real ls_rans, real wall_distance,
                                  real cdes);
FLUENT_EXPORT void Update_Sbes_Blending_Function(Domain *domain);
FLUENT_EXPORT void Update_Omega_For_Sbes_Based_On_Ke(Domain *domain);
FLUENT_EXPORT real get_Sbes_Bf_For_TwoEquationModels(cell_t c, Thread *t, real rho,
                                                     real mu, real wall_dist, real wall_normal[],
                                                     real tke, real omg, real k_g[], real o_g[]);
FLUENT_EXPORT real Get_sst_Sig(Svar sv_phi, real F1);
FLUENT_EXPORT real Get_bsl_Sig(Svar sv_phi, real F1);
FLUENT_EXPORT real Get_Sig_Blended(real sig1, real sig2, real F1);

FLUENT_EXPORT real get_v2f_ts(real rho, real k, real d, real mu,
                              real v2, real smag, cxboolean both);

FLUENT_EXPORT real get_transition_fnu(real rho, real o, real mu, real kt, real lam_fac);
FLUENT_EXPORT real get_transition_ftaul(real ktl, real rmag, real lam_eff);
FLUENT_EXPORT void Update_Geometric_Roughness_Height(Domain *domain);
FLUENT_EXPORT real udf_geomrgh(cell_t c, Thread *t);
FLUENT_EXPORT real udf_curvature_correction_ccurv(cell_t c, Thread *PTR_RESTRICT t);
FLUENT_EXPORT real udf_corner_flow_correction_ccorner(cell_t c, Thread *t);
/*psuedo_transient_add*/
FLUENT_EXPORT real Calc_Turb_Eqn_Pseudo_Explicit_Relax(Svar sv_phi);
/* US28224: pseudo transient coupled solver expert options */
FLUENT_EXPORT cxboolean Calc_Turb_Eqn_Pseudo_Specific_on_or_off(Svar sv_phi);
FLUENT_EXPORT real Calc_Turb_Eqn_Pseudo_Implicit_Relax(Svar sv_phi);
FLUENT_EXPORT real Calc_Turb_Eqn_Pseudo_Time_Step_Scaled(Svar sv_phi);
FLUENT_EXPORT int       Turb_Eqn_Pseudo_AMG_Cycle(Svar sv_phi);
FLUENT_EXPORT int       Turb_Eqn_Dual_TS_AMG_Cycle(Svar sv_phi);
FLUENT_EXPORT void Update_Wall_Roughness_Profiles(Thread *t);

FLUENT_EXPORT real get_dUdn_based_on_velocity_gradient(real wall_normal[], real u_g[], real v_g[], real w_g[]);
FLUENT_EXPORT real get_dUdn_based_on_wall_normal_velocity_gradient(real wall_normal[], real uini_g[]);
FLUENT_EXPORT real get_crossflow_indicator(real wall_dist, real wall_normal[], real vortnorm_x_g[], real vortnorm_y_g[], real vortnorm_z_g[]);

FLUENT_EXPORT real get_geko_fsep(cell_t c, Thread *t, real rho, real mu, real tke, real omg);
FLUENT_EXPORT real get_geko_alpha(cell_t c, Thread *t);
FLUENT_EXPORT real get_geko_fmix(cell_t c, Thread *t, real omg);

FLUENT_EXPORT cxboolean sas_source_term_needed_in_turb_model(void);

FLUENT_EXPORT real getQsas(cell_t c, Thread *t,
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
                           real *PTR_RESTRICT s, real *PTR_RESTRICT ap, Svar sv_phi);

FLUENT_EXPORT real Compute_Roughness_Correlation(real u, real v, real w, real rho, real mu, real Re_thetat_bar, real geomrgh);

FLUENT_EXPORT real get_correlation_Flength(real Re, real Fsub);
FLUENT_EXPORT real udf_correlation_Flength(cell_t c, Thread *PTR_RESTRICT t);
FLUENT_EXPORT real get_correlation_Re_tauc(real Re);
FLUENT_EXPORT real udf_correlation_Re_tauc(cell_t c, Thread *PTR_RESTRICT t);
FLUENT_EXPORT real F_theta_t(real mu, real rho, real Vmag, real Rmag, real yp, real o, real Re_thetat_bar, real gam);
FLUENT_EXPORT real UDF_Correlation_Re_theta(cell_t c, Thread *PTR_RESTRICT t);
FLUENT_EXPORT real get_dUds(real u_g[], real v_g[], real w_g[], real vel[], real Vmag);

FLUENT_EXPORT real get_omega_from_tke_and_tdr(real tke, real tdr, real Cmu);
FLUENT_EXPORT real get_linearized_sbes_source(cell_t c, Thread *t, real rho, real tke, real omg, real mu, real Cmu);
FLUENT_EXPORT real get_tke_dissipation_multiplier(cell_t c, Thread *t, real beta_star, real rho, real k, real o, real mu, real mu_t, real wall_dist);

TransientParameters *getTransientParameters(void);
void Modify_Two_Layer_Model_For_Porous_Jump_WT(Domain *PTR_RESTRICT domain, Svar sv_phi, int idir);


/*psuedo_transient_add_end*/

FLUENT_EXPORT void Update_Sgs_Tke(Thread *t);

FLUENT_EXPORT unsigned int Get_Overset_Bl_Temp_Flag(void);
#endif /* _FLUENT_SG_KE_H */

