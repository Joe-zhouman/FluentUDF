/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SG_PRESS_H
#define _FLUENT_SG_PRESS_H

#include "dll.h"

/*
#define POROUS_INTERFACE_THREAD_P(t)((THREAD_VAR(t->t0).fluid.porous)||\
                                      (THREAD_VAR(t->t1).fluid.porous) || por_vel_form)
*/

/* moved to sg_mem.h */
/*
#define POROUS_THREAD_P(t) (THREAD_VAR(t).fluid.porous)
#define POROUS_INTERFACE_THREAD_P(t) (POROUS_THREAD_P(t->t0) || POROUS_THREAD_P(t->t1))
*/

#define C_AP_PP(c,t)FAST_C_STORAGE_R(c,t,SV_P_AP)
#define C_SOURCE_PP(c,t)FAST_C_STORAGE_R(c,t,SV_P_S)

#define C_P_PRIME(c,t)FAST_C_STORAGE_R(c,t,SV_PP)

#define C_B_FAC(c,t)C_STORAGE_R(c,t,SV_B_FACTOR)

#define F_PP_COEFF(f,t)FAST_F_STORAGE_R(f,t,SV_PP_COEFF)
#define F_FP_COEFF(f,t)FAST_F_STORAGE_R(f,t,SV_FP_COEFF)
#define F_MACH(f,t)FAST_F_STORAGE_R(f,t,SV_MACH)

FLUENT_EXPORT void Update_Compressible_Face_Density(Domain *domain, cxboolean density_second_order);
FLUENT_EXPORT void update_periodic_beta(Domain *domain);

FLUENT_EXPORT void Limit_Pressure_Gradient(Domain *domain);
FLUENT_EXPORT void Reconstruct_Face_Pressure(Domain *domain);

FLUENT_EXPORT void Freeze_Mass_Flux(Domain *domain);
FLUENT_EXPORT void Init_Frozen_Mass_Flux(Domain *domain);
FLUENT_EXPORT void Add_Continuity_Sources(Domain *domain, Svar sv_imbalance);
FLUENT_EXPORT void Add_Continuity_Time_Sources(Domain *domain, Svar sv_imbalance);
FLUENT_EXPORT void Add_Continuity_Flux_Imbalance(Domain *domain, Svar sv_imbalance, cxboolean p_vof);
FLUENT_EXPORT void Update_Continuity_Imbalance(Domain *domain, Svar sv_imbalance,
                                               cxboolean add_mass_error, cxboolean p_vof);
FLUENT_EXPORT void Correct_Cell_Density(Domain *domain);
FLUENT_EXPORT void Correct_Face_Flux(Domain *domain, cxboolean piso_flag);
FLUENT_EXPORT void mfp_correct_face_flux(Domain *domain);
FLUENT_EXPORT void mfp_correct_cell_velocity(Domain *domain);
FLUENT_EXPORT void update_mfi_flux(Thread *t, cxboolean add_to_imbalance);
FLUENT_EXPORT void update_mfi_flux_channel(Domain *domain, cxboolean add_to_imbalance, real *local_inlet_flux_sum);
/* FLUENT_EXPORT void update_mfi_flux_mp(Thread *t, cxboolean add_to_imbalance);  */

FLUENT_EXPORT void p_bndr_coeffs(face_t, Thread *, cell_t, Thread *, real, real, real);
FLUENT_EXPORT void Coeff_Mod(Domain *domain);
FLUENT_EXPORT void Update_Face_Flux(Domain *domain);
FLUENT_EXPORT void Model_Initialize_pressure(void);

extern FLUENT_EXPORT cxboolean body_force_weighted_new;
FLUENT_EXPORT real bfw_new_f_pp_coeff(cell_t c, Thread *t, real NV_VEC(A), real NV_VEC(es));

FLUENT_EXPORT cxboolean Is_Compressible(Thread *);

extern FLUENT_EXPORT real physical_dt;
extern FLUENT_EXPORT real flow_dual_dt;
extern FLUENT_EXPORT real omega_p;
extern FLUENT_EXPORT real omega_v;
extern FLUENT_EXPORT real omega_m; /* (1-omega_v)/omega_v */
extern FLUENT_EXPORT real T_limit;

/* for periodics with mass flow */
extern FLUENT_EXPORT cxboolean mass_flow_periodic;
extern FLUENT_EXPORT cxboolean pressure_drop_periodic;
extern FLUENT_EXPORT real periodic_beta;
extern FLUENT_EXPORT real periodic_beta_prime;
extern FLUENT_EXPORT real last_beta_prime;

/* pressure equation */
extern FLUENT_EXPORT int pressure_scheme;
extern FLUENT_EXPORT int mom_scheme;
extern FLUENT_EXPORT cxboolean presto_p;
extern FLUENT_EXPORT cxboolean presto_limited_p;
extern FLUENT_EXPORT cxboolean linear_p;
extern FLUENT_EXPORT cxboolean recon_p;
extern FLUENT_EXPORT cxboolean density_weighted_p;
extern FLUENT_EXPORT cxboolean momentum_weighted_p;
extern FLUENT_EXPORT cxboolean continuity_p;
extern FLUENT_EXPORT cxboolean pressure_unsteady;
extern FLUENT_EXPORT cxboolean frozen_flux;
extern FLUENT_EXPORT cxboolean dissipation_flag;
extern FLUENT_EXPORT cxboolean mp_dissipation_flag;
extern FLUENT_EXPORT cxboolean unsteady_rc;
extern FLUENT_EXPORT cxboolean upd_vel_grad_before_f_press_corr;
extern FLUENT_EXPORT cxboolean rc_flux_solids_p;
extern FLUENT_EXPORT cxboolean fixed_vel_zero_p;

extern FLUENT_EXPORT int press_corr_disc_scheme;

/* p-v coupled scheme */
extern FLUENT_EXPORT int coupling_scheme;
extern FLUENT_EXPORT int coupling_dissipation;
extern FLUENT_EXPORT real cpl_expl_omega_v;
extern FLUENT_EXPORT real cpl_omega_flux;

/* dynamic zone solution stabilization flag for use in local residual scaling  */
extern FLUENT_EXPORT cxboolean solution_stabilization_p;
extern FLUENT_EXPORT cxboolean standard_initialized_flow_field_p;

extern FLUENT_EXPORT cxboolean MP_COUPLED;
extern FLUENT_EXPORT int mp_ap_weighted_face_pressure;
extern FLUENT_EXPORT int mp_ap_weighted_face_pressure_piso;
extern FLUENT_EXPORT int mp_ap_weighted_face_p_1st;
extern FLUENT_EXPORT int mp_body_force_weighted_face_p;
extern FLUENT_EXPORT int mp_face_pressure_option;
extern FLUENT_EXPORT int mp_4th_order_dissipation;
extern FLUENT_EXPORT int mp_coupled_drag;
extern FLUENT_EXPORT cxboolean neighbor_mp_ps;
extern FLUENT_EXPORT cxboolean mp_f_pp; /* needed for MP_PISO*/
extern FLUENT_EXPORT cxboolean mp_skew_force_test; /* needed for MP_PISO testing skew_force option*/
extern FLUENT_EXPORT cxboolean mp_p_face_convection; /* needed for MP_PISO testing skew_force option*/
extern FLUENT_EXPORT cxboolean piso_corrector_just_due_to_vof;/*needed for sg_mp_piso (noniterative MP-PISP)*/
enum coupled_dissipation_scheme
{
  TURNED_OFF = 0,
  MOM_DISCR = 1,
  POST_MOM_DISCR = 2
};

FLUENT_EXPORT cxboolean Presto_Limited_P(void);
FLUENT_EXPORT cxboolean Presto_Limited_PCOR(void);

FLUENT_EXPORT void
Correct_Source_Error(Domain *domain, Svar nv),
                     Pressure_Boundary_Pressure_Correction(Thread *t, cxboolean flag_intr),
                     Solve_PISO(Domain *domain, real *Avalue),
                     Cell_Pressure_Sources(Domain *domain, cxboolean outflow_p,
                                           cxboolean add_mass_source_error),
                     Update_Face_Pressure(Domain *domain),
                     Calculate_Face_Pressure_Correction(Domain *domain),
                     Save_Prev_Velocities(Domain *domain),
                     Correct_Cell_P(Domain *domain, cxboolean implicit_bf_p),
                     Pressure_Fixed_Velocity_Sources(Domain *domain, AMG_System_Type sys_id),
                     Pressure_Fixed_Velocity_Sources_Coupled(Domain *domain)
                     ;

/* dynamic zone solver options : artificial compressibility at boundary cells */
FLUENT_EXPORT void System_Coupling_Artificial_Compressibility(Domain *domain);
FLUENT_EXPORT void General_Artificial_Compressibility(Domain *domain);

/* Coupled VOF related functions */
FLUENT_EXPORT void Coupled_PV_VOF_Coeffs(Domain *domain);

/* for communication with mp_press.c */

FLUENT_EXPORT void correct_mp_v(Domain *domain);
FLUENT_EXPORT void mp_correct_flux(Domain *domain);
FLUENT_EXPORT void mp_coupled_set_vel(Domain *domain);
FLUENT_EXPORT void mp_correct_mass_volume_flux(Domain *domain, cxboolean p_vof);
FLUENT_EXPORT void mp_save_prev_face_vof(Domain *domain);
FLUENT_EXPORT void mp_update_face_pressure(Domain *domain);
FLUENT_EXPORT void mp_update_face_capillary_pressure(Domain *domain);
FLUENT_EXPORT void mp_save_prev_vflux(Domain *domain);
FLUENT_EXPORT void mp_calculate_face_pressure_correction(Domain *domain);
FLUENT_EXPORT void mpg_calculate_face_pressure_correction(Domain *domain);
FLUENT_EXPORT void mpg_correct_flux(Domain *domain);
FLUENT_EXPORT void mpg_correct_v(Domain *domain);
FLUENT_EXPORT void mpg_correct_cell_gp(Domain *domain);
FLUENT_EXPORT void mpg_update_face_pressure(Domain *domain);

FLUENT_EXPORT void interior_pressure_coeffs_mp(Thread *t);
FLUENT_EXPORT void periodic_pressure_coeffs_mp(Thread *t);
FLUENT_EXPORT void pinlet_pressure_coeffs_mp(Thread *t);
FLUENT_EXPORT void poutlet_pressure_coeffs_mp(Thread *t);
FLUENT_EXPORT void solve_gpp(Domain *domain);
FLUENT_EXPORT void vinlet_pressure_coeffs_mp(Thread *t);
FLUENT_EXPORT void wall_pressure_coeffs_mp(Thread *t);
FLUENT_EXPORT void outflow_pressure_coeffs_mp(Thread *t);
FLUENT_EXPORT void mfi_pressure_coeffs_mp(Thread *t);
FLUENT_EXPORT void mp_od_pressure_velocity_coefficients(Domain *domain);
FLUENT_EXPORT void set_mp_velocity_coefficients(Domain *domain);
FLUENT_EXPORT void set_mp_velocity_coefficients_test(Domain *domain);
FLUENT_EXPORT void Relative_absolute_H(real *H, face_t f, Thread *t, Thread *t0, cxboolean specified_relative);
FLUENT_EXPORT void Relative_absolute_p0(real *p0, face_t f, Thread *t, Thread *t0, cxboolean specified_relative);
FLUENT_EXPORT void Relative_absolute_Vmag2(real *PTR_RESTRICT Vmag2, face_t f, Thread *PTR_RESTRICT t, Thread *PTR_RESTRICT t0, cxboolean specified_relative);
/* end mp_press.c */

#define BLEND_FACTOR_TIME(b_factor,phi,phi_M1,phi_M2, beta)\
{ if(!tvd_time_bounded_second_order || ABS(phi) < 1.e-15)\
     b_factor = 1.0;  \
  else \
    {\
      real phi_diff = ABS((phi - phi_M1)/phi); \
      if(phi_diff < 1.e-10) \
         b_factor = 1.0; \
      else \
       {\
         real phi_r = (phi_M1 - phi_M2)/(phi - phi_M1); \
         phi_r = fabs(phi_r); \
         if(phi_r< 3.0)  \
           b_factor = 1.0;\
         else              \
          b_factor = beta/(phi_r - 1.0); \
       }\
    }\
}

/* used in piso.c and mp_press.c */
#define ADD_SKEW_FORCE(bf,dpf,es,A,cv,omega_pp)\
{\
  real NV_VEC(skew), dps;\
  dps = NV_DOT(es,dpf)/NV_DOT(es,A);\
  NV_V_VS(skew,=,dpf,-,A,*,dps);\
  NV_S(skew,*=,cv);\
  NV_VS(bf,+=,skew,*,omega_pp);       \
}

#define ADD_SKEW_FORCE_test2(bf,dpf,es,A,cv,omega_pp)\
{\
  real NV_VEC(skew), dps;\
  dps = -NV_DOT(es,dpf)/NV_DOT(es,A);\
  NV_VS(skew,=,A,*,dps);\
  NV_S(skew,*=,cv);\
  NV_VS(bf,+=,skew,*,omega_pp);       \
}

#define ADD_SKEW_FORCE_test3(bf,dpf,es,A,cv,omega_pp)\
{\
  real NV_VEC(skew);\
  NV_VS(skew,=,dpf,*,-1.0);\
  NV_S(skew,*=,cv);\
  NV_VS(bf,+=,skew,*,omega_pp);       \
}

#define ADD_SKEW_FORCE_TEST(bf,dpf,es,A,cv,omega_pp)\
{\
  real NV_VEC(skew), dps;\
  dps = NV_DOT(es,dpf)*SIGN(NV_DOT(es,A));\
  NV_V_VS(skew,=,dpf,-,es,*,dps);\
  NV_S(skew,*=,cv);\
  NV_VS(bf,+=,skew,*,omega_pp);       \
}

#define ADD_SKEW_FORCE_PROJ(vf, dr0, dr1, ds01, Area, ppGrad0, ppGrad1, cvf, urf_pp)\
{\
  real dsnAbs, skew_grad;\
  real NV_VEC(face_normal), NV_VEC(dr0_tangent), NV_VEC(dr1_tangent);\
  \
  NV_VS(face_normal, =, Area, /, NV_MAG(Area));\
  \
  NV_V_VS(dr0_tangent, =, dr0, -, face_normal, *, (NV_DOT(dr0, face_normal)));\
  NV_V_VS(dr1_tangent, =, dr1, -, face_normal, *, (NV_DOT(dr1, face_normal)));\
  \
  dsnAbs = ABS(NV_DOT(ds01, face_normal));\
  skew_grad = urf_pp * cvf * (NV_DOT(ppGrad1, dr1_tangent) - NV_DOT(ppGrad0, dr0_tangent)) / dsnAbs;\
  NV_VS(vf, +=, face_normal, *, skew_grad);\
}

#define ADD_SKEW_FORCE_BNDR_PROJ(vf, dr0, Area, ppGrad0, cv0, urf_pp)\
{\
  real dsfn, skew_grad;\
  real NV_VEC(face_normal), NV_VEC(dr0_tangent);\
  \
  NV_VS(face_normal, =, Area, /, NV_MAG(Area));\
  \
  NV_V_VS(dr0_tangent, =, dr0, -, face_normal, *, (NV_DOT(dr0, face_normal)));\
  \
  dsfn = ABS(NV_DOT(dr0, face_normal));\
  skew_grad = urf_pp * cv0 * (- NV_DOT(ppGrad0, dr0_tangent)) / dsfn;\
  NV_VS(vf, +=, face_normal, *, skew_grad);\
}


/**
 * Equi-distant projection of the skewness correction
 * Where the projections to the face-normal  direction are not equal,
 * the smaller projected distance is considered as the normal projection and
 * the larger projection is set equal to the smaller one;
 * thus the correction vector of the largest projection may not be perpendicular to the normal direction
 * This equi-distant projection enables second order accuracy at the face-center.
 * Details in Comp. methods. for Fluid Dynamics by Ferziger, Peric and Street 4th Ed. Section 9.7.2, pg. 311
 */
#define ADD_SKEW_FORCE_PROJ_ED(vf, dr0, dr1, Area, ppGrad0, ppGrad1, cvf, urf_pp)\
{\
  real drn0, drn1, drnMin, skew_grad;\
  real NV_VEC(face_normal), NV_VEC(dr0_tangent), NV_VEC(dr1_tangent);\
  \
  NV_VS(face_normal, =, Area, /, NV_MAG(Area));\
  drn0 = NV_DOT(dr0, face_normal);\
  drn1 = NV_DOT(dr1, face_normal);\
  if(ABS(drn0) <= ABS(drn1)) {drnMin = ABS(drn0); drn1 *= drnMin/ABS(drn1); } \
  else                       {drnMin = ABS(drn1); drn0 *= drnMin/ABS(drn0); } \
  \
  NV_V_VS(dr0_tangent, =, dr0, -, face_normal, *, drn0);\
  NV_V_VS(dr1_tangent, =, dr1, -, face_normal, *, drn1);\
  \
  skew_grad = urf_pp * cvf * (NV_DOT(ppGrad1, dr1_tangent) - NV_DOT(ppGrad0, dr0_tangent)) / (2 * drnMin);\
  NV_VS(vf, +=, face_normal, *, skew_grad);\
}


/** This approach applies the Equi-distant normal projection (NPED) formulation with a deferred correction
 * The implicit part is same as the Normal Projection (NP) formulation,
 * The explicit source term is from ED formulation
 * To account for the difference in the implicit term; an explicit, deferred correction
 * (ED - NP) (implicit) is applied.
 *
 * The hypothesis of this approach is that in case of large cell size jump, such as
 * sudden transition from a wall resolved boundary layer to interior cells, the ratio
 * of projected distance between face-center to cell-center distance may get very large
 * This will result in aggressive amplification of the implicit term, while the non-orthogonal
 * correction is largely coming off the larger cell.
 *
 * A deferred correction will keep the non-orthogonal amplification of the implicit term smaller
 * while accounting for the ED formulation source in a deferred way.
**/
#define ADD_SKEW_FORCE_PROJ_ED_DEFERRED(vf, dr0, dr1, ds01, Area, del_pp_f, ppGrad0, ppGrad1, cvf, urf_pp)\
{\
  real drn0, drn1, drnMin, dsnAbs, skew_grad;\
  real NV_VEC(face_normal), NV_VEC(dr0_tangent), NV_VEC(dr1_tangent);\
  \
  NV_VS(face_normal, =, Area, /, NV_MAG(Area));\
  dsnAbs = ABS(NV_DOT(ds01, face_normal));\
  drn0 = NV_DOT(dr0, face_normal);\
  drn1 = NV_DOT(dr1, face_normal);\
  if(ABS(drn0) <= ABS(drn1)) {drnMin = ABS(drn0); drn1 *= drnMin/ABS(drn1); } \
  else                       {drnMin = ABS(drn1); drn0 *= drnMin/ABS(drn0); } \
  \
  NV_V_VS(dr0_tangent, =, dr0, -, face_normal, *, drn0);\
  NV_V_VS(dr1_tangent, =, dr1, -, face_normal, *, drn1);\
  \
  skew_grad = urf_pp * cvf * (NV_DOT(ppGrad1, dr1_tangent) - NV_DOT(ppGrad0, dr0_tangent)) / (2 * drnMin);\
  skew_grad += del_pp_f * (1./(2 * drnMin) - 1./dsnAbs);\
  \
  NV_VS(vf, +=, face_normal, *, skew_grad); \
}

typedef enum
{
  PP_DD_OFF = 0,
  PP_DD_ENFORCE,
  PP_DD_MASS_IMBALANCE,
  PP_DD_MAX
} Coupled_PP_DD_Select;

typedef struct
{
  cxboolean enable;
  real relax;
} Change_Limiter;

typedef enum
{
  LV_P = 0,
  LV_T,
  LV_MAX
} Limited_Var_Map;

typedef struct
{
  cxboolean enable;
  cxboolean use_normal_mach;
  real mach_limit;
} Strong_Shock_Detector;

typedef struct
{
  cxboolean enable;
  cxboolean correct_enthalpy_ke;
  cxboolean correct_enthalpy_pres;
  Coupled_PP_DD_Select pp_dd_select;
  Change_Limiter limited_vars[2];
  Strong_Shock_Detector ssd;
} Enhanced_Numerics_Controls;

extern FLUENT_EXPORT Enhanced_Numerics_Controls enhanced_numerics;
extern FLUENT_EXPORT void Limit_P_Prime(Domain *PTR_RESTRICT domain, Enhanced_Numerics_Controls *enc);
extern FLUENT_EXPORT void Correct_Cell_Enthalpy(Domain *PTR_RESTRICT domain, Enhanced_Numerics_Controls *enc);
extern void (* Exchange_BNSF)(Domain *);
extern void (* Fill_NSF)(Domain *, real);
extern FLUENT_EXPORT cxboolean check_cap_press(Domain *domain);

#endif /* _FLUENT_SG_PRESS_H */
