/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SG_MPHASE_H
#define _FLUENT_SG_MPHASE_H

#include "dll.h"

#include "sg_delta.h"

#define MT_PROP_MAX 100

#define DT_INV_SMALL 1.e-20

/* type definition section */
typedef enum
{
  MP_OFF = 0,       /* same as FALSE */
  MP_VOF,           /* corresponds to boolean mp_vof    */
  MP_HOMOGENEOUS,   /*                        mp_hom    */
  MP_DRIFT_FLUX,    /*                        mp_drift  */
  MP_MULTI_FLUID,   /*                        mp_mfluid */
  MP_MODEL_MAX
} MP_Model;

typedef enum                  /*corresponds to scheme-var mp/scheme-type*/
{
  VOF_NULL = -1,
  VOF_IMPLICIT,
  VOF_EXPLICIT
} VOF_Scheme_Type;

typedef enum                  /*corresponds to mp/regime-type */
{
  SHARP = 0,
  SHARP_DISPERSED,
  DISPERSED
} MP_Regime_Type;

typedef enum                  /*corresponds to backflow vof type at poutlet */
{
  BACKFLOW_VOF = 0,
  FROM_NEIGHBOR
} MP_BackFlow_Type;

typedef enum                  /*corresponds to scheme-var mp-ke-type*/
{
  MP_KE_NULL = -1,
  MP_KE_MIXTURE,
  MP_KE_DISPERSED,  /* dilute approach assumes solving equations for primary phase */
  MP_KE_EACH_PHASE
} MP_KE_Type;

typedef enum                  /*corresponds to scheme-var mp-rsm-type*/
{
  MP_RSM_NULL = -1,
  MP_RSM_MIXTURE,
  MP_RSM_DISPERSED  /* dilute approach assumes solving equations for primary phase */
} MP_RSM_Type;

typedef enum                  /*corresponds to scheme-var mp-les-type*/
{
  MP_LES_NULL = -1,
  MP_LES_MIXTURE,
  MP_LES_DISPERSED  /* dilute approach assumes solving equations for primary phase */
} MP_LES_TYPE;

typedef enum                  /*corresponds to scheme-var mp/mass-trans-type*/
{
  MP_MT_OFF = 0,
  MP_MT_CAVITATION
} MP_Mass_Transfer_Type;

typedef enum                  /*corresponds to scheme-var dpm/dpm_vof_scheme_type*/
{
  DPM_AVERAGE = 0,
  TRANSP_EQN,
  INITIAL_GUESS
} DPM_Vof_Scheme_Type;

typedef enum                  /*corresponds to species mass transfer model in scheme side */
{
  MP_SMT_MTC_OVERALL,
  MP_SMT_MTC_PER_PHASE,
  MP_SMT_RAOULT,
  MP_SMT_HENRY,
  MP_SMT_EQU_RATIO,
  MP_SMT_MOLAR_CON,
  MP_SMT_MOLAR_FRAC,
  MP_SMT_MASS_FRAC
} Mp_Spe_Mass_Trans_Type;

typedef enum                  /*corresponds to cavitation mass transfer model in scheme side */
{
  MP_CAV_MODEL_SCHNERR,
  MP_CAV_MODEL_ZWART
  /* MP_CAV_SCHNERR_BND_INPUT,
   MP_CAV_SCHNERR_BND_COMPUTE */

} Mp_Cav_Mass_Trans_Type;

typedef enum                  /*corresponds to evaporation-condensation mass transfer model in scheme side */
{
  MP_EVAP_COND_LEE = 0,
  MP_EVAP_COND_TPC = 1,
  MP_EVAP_COND_HERTZ_KNUDSEN_T = 2,
  MP_EVAP_COND_HERTZ_KNUDSEN_P = 3,
  MP_EVAP_COND_IHF = 4

} Mp_Evap_Cond_Mass_Trans_Type;

typedef enum                  /*corresponds to boiling model, could be utilized to add other boling models in N-phase framework   */
{
  MP_BOIL_NONE,
  MP_BOIL_SEMI_MECH,  /* Semi-Mechanistic boiling model */
  MP_WALL_EVAP_COND  /* Wall evaporation-condensation model */

} Mp_Boiling_Mass_Trans_Type;

typedef enum          /*corresponds to sbm model   */
{
  MP_SBM_CHEN,  /* Chen method */
  MP_SBM_USER   /* User-Defined Method */

} Mp_SBM_Type;

typedef struct
{
  /* Data for mass transfer specific tabulation options */
  real *tsat;
  real *psat;
  real *lsat;
  int npts;

  /* Data for generic tabulation options */
  Table_1D_With_Range_Check tsat_table;
  Table_1D_With_Range_Check psat_table;
  Table_1D_With_Range_Check hsat_l_table;
  Table_1D_With_Range_Check hsat_v_table;
} MT_Tabular_Data;

/* end of type definition section */

/*multiphase model global variables,
see definition for comments and defaults*/
extern FLUENT_EXPORT cxboolean sg_vFlux;
extern FLUENT_EXPORT Svar sv_nFlux;
extern FLUENT_EXPORT MP_Model sg_mphase;
extern FLUENT_EXPORT cxboolean n_phase_solver;
extern FLUENT_EXPORT cxboolean mp_mfluid;
extern FLUENT_EXPORT cxboolean mp_vof;
extern FLUENT_EXPORT cxboolean mp_vof_channel_flow;
extern FLUENT_EXPORT cxboolean initialized_open_channel;
extern FLUENT_EXPORT cxboolean oc_po_backflow_pb;
extern FLUENT_EXPORT cxboolean mp_vof_wave_bc;
extern FLUENT_EXPORT cxboolean mp_anisotropic_drag;
extern FLUENT_EXPORT cxboolean surf_tens_vars_update;
extern FLUENT_EXPORT cxboolean mp_drift;
extern FLUENT_EXPORT cxboolean mp_hom;
extern FLUENT_EXPORT cxboolean mp_mixture;
extern FLUENT_EXPORT cxboolean mp_explicit;
extern FLUENT_EXPORT cxboolean velocity_limit_filter;
extern FLUENT_EXPORT cxboolean velocity_limit_dampener;
extern FLUENT_EXPORT cxboolean mp_exp_new_framework;
extern FLUENT_EXPORT cxboolean mp_exp_rel_motion;
extern FLUENT_EXPORT int mp_exp_mass_tr_option;
extern FLUENT_EXPORT cxboolean mp_filter_flotsam;
extern FLUENT_EXPORT cxboolean mp_instability_detector;
extern FLUENT_EXPORT cxboolean mp_vf_mass_form;
extern FLUENT_EXPORT MP_Regime_Type mp_regime_type;
extern FLUENT_EXPORT cxboolean cav_l;
extern FLUENT_EXPORT cxboolean vof_linearized;
extern FLUENT_EXPORT cxboolean new_linearization;
extern FLUENT_EXPORT cxboolean mp_mt_udf_linearize_alt;
extern FLUENT_EXPORT cxboolean new_boiling_treatment;
extern FLUENT_EXPORT cxboolean intf_mass_transfer;
extern FLUENT_EXPORT cxboolean intf_mass_transfer_active;
extern FLUENT_EXPORT cxboolean mp_mt_total_enthalpy;
extern FLUENT_EXPORT cxboolean mp_mt_total_enthalpy_liquid_work;
extern FLUENT_EXPORT cxboolean ht_fixed_to_tsat;
extern FLUENT_EXPORT cxboolean to_phase_temp_fixed;
extern FLUENT_EXPORT cxboolean mp_hmt_particle_mode;
extern FLUENT_EXPORT cxboolean update_energy_m2;
extern FLUENT_EXPORT cxboolean linearized_udf;
extern FLUENT_EXPORT cxboolean model_cav;
extern FLUENT_EXPORT cxboolean model_evap_cond;
extern FLUENT_EXPORT cxboolean model_boiling;
extern FLUENT_EXPORT cxboolean model_sbm; /* semi-mechanistic boiling */
extern FLUENT_EXPORT cxboolean model_hertz_p;
extern FLUENT_EXPORT cxboolean model_hertz_t;
extern FLUENT_EXPORT cxboolean model_species_transfer;
extern FLUENT_EXPORT cxboolean boiling_model_pars;
extern FLUENT_EXPORT cxboolean RPI_model;
extern FLUENT_EXPORT cxboolean NEQ_model;
extern FLUENT_EXPORT cxboolean CHF_model;
extern FLUENT_EXPORT cxboolean VAP_heat;
extern FLUENT_EXPORT cxboolean update_partition;
extern FLUENT_EXPORT cxboolean rpi_mixture_mu;
extern FLUENT_EXPORT cxboolean limit_output_p;
extern FLUENT_EXPORT cxboolean p_enhancement;
extern FLUENT_EXPORT cxboolean press_bc;
extern FLUENT_EXPORT cxboolean sato_enhancement;
extern FLUENT_EXPORT cxboolean troshko_hassan_enhancement;
extern FLUENT_EXPORT cxboolean simonin_enhancement;
extern FLUENT_EXPORT cxboolean method_tsat_tabulation;
extern FLUENT_EXPORT int mp_n;
extern FLUENT_EXPORT int mp_n_ke;
extern FLUENT_EXPORT int mp_n_rsm;
extern FLUENT_EXPORT int mp_n_les;
extern FLUENT_EXPORT int mpg_n;
extern FLUENT_EXPORT int n_mass_transfer;
extern FLUENT_EXPORT int n_pb_mt;
extern FLUENT_EXPORT int n_vmass_vflux;
extern FLUENT_EXPORT int n_het_reactions;
extern FLUENT_EXPORT MP_Mass_Transfer_Type mp_mass_transfer;
extern FLUENT_EXPORT char mp_name[MAX_PHASES][MATERIAL_NAME_LENGTH];
extern FLUENT_EXPORT char mp_material_name[MAX_PHASES][MATERIAL_NAME_LENGTH];
extern FLUENT_EXPORT cxboolean mpg_material[MAX_PHASES];
extern FLUENT_EXPORT cxboolean lift_shaver_podowski_correction_on;
extern FLUENT_EXPORT cxboolean lift_montoya_correction_on;
extern FLUENT_EXPORT cxboolean lift_tomiyama_model;
extern FLUENT_EXPORT cxboolean lift_moraga_model_old;
extern FLUENT_EXPORT cxboolean wl_total_velocity_on;
extern FLUENT_EXPORT cxboolean wl_hosokawa_model;
extern FLUENT_EXPORT int mpg_index[MAX_PHASES];
extern FLUENT_EXPORT real Ci_B [MAX_PHASES][3];
extern FLUENT_EXPORT real Cid_B[MAX_PHASES][3];
extern FLUENT_EXPORT real Cir_B[MAX_PHASES][3];
extern FLUENT_EXPORT real ht_l_coeff;
extern FLUENT_EXPORT real ht_cont_coeff;
extern FLUENT_EXPORT real ht_disp_coeff;
extern FLUENT_EXPORT real diam_h;
extern FLUENT_EXPORT real td_vofV_L;
extern FLUENT_EXPORT real td_vofV_U;
extern FLUENT_EXPORT real superheat_min;
extern FLUENT_EXPORT real heat_flux_min;
extern FLUENT_EXPORT real mp_inlet_flux;
extern FLUENT_EXPORT real f_gas;
extern FLUENT_EXPORT real f_gas_spe;
extern FLUENT_EXPORT real f_limit;
/* extern FLUENT_EXPORT real temp; */
extern FLUENT_EXPORT real gmw;
extern FLUENT_EXPORT real T_FLUID;
extern FLUENT_EXPORT real H_latent;
extern FLUENT_EXPORT real h_cont;
extern FLUENT_EXPORT real h_disp;
extern FLUENT_EXPORT real rpi_time_scale;
extern FLUENT_EXPORT real p_vap;
extern FLUENT_EXPORT real p_cav_limit;
extern FLUENT_EXPORT real p_cav_min;
extern FLUENT_EXPORT real plimit;
extern FLUENT_EXPORT real cav_coeff;
extern FLUENT_EXPORT real cn_alpha;
extern FLUENT_EXPORT real dvof_dp(cell_t c, Thread *t, real vof_n, int phase);
extern FLUENT_EXPORT real drho_gas_dp(cell_t c, Thread *t);
extern FLUENT_EXPORT real rho_gas(real press, real p_cav_min, real temp_m);
extern FLUENT_EXPORT real vof_gas(real rho, real p);
extern FLUENT_EXPORT real rho_r_bc(face_t f, Thread *t, Thread **pt, int phase, int n);
extern FLUENT_EXPORT int VAPOR_SPE;
extern FLUENT_EXPORT int mass_transfer_1;
extern FLUENT_EXPORT int mass_transfer_2;
extern FLUENT_EXPORT int density_scheme;
extern FLUENT_EXPORT int RPI_IA;
extern FLUENT_EXPORT int RPI_BDD;
extern FLUENT_EXPORT int CHF_HEAT;
extern FLUENT_EXPORT int from_phase[MT_PROP_MAX];
extern FLUENT_EXPORT int to_phase[MT_PROP_MAX];
extern FLUENT_EXPORT int from_species_ht[MT_PROP_MAX];
extern FLUENT_EXPORT int to_species_ht[MT_PROP_MAX];
extern FLUENT_EXPORT int rpi_liq_phase;
extern FLUENT_EXPORT int rpi_vap_phase;
extern FLUENT_EXPORT int rpi_liq_species;
extern FLUENT_EXPORT int rpi_vap_species;
extern FLUENT_EXPORT cxboolean packed_bed;
extern FLUENT_EXPORT cxboolean packed_bed_phase[MAX_PHASES];
extern FLUENT_EXPORT cxboolean p_correct;
extern FLUENT_EXPORT cxboolean density_second_order;
extern FLUENT_EXPORT cxboolean extrap_p;
extern FLUENT_EXPORT real p_cvd;
extern FLUENT_EXPORT real p_cvd_1;

extern FLUENT_EXPORT real gran_fric_press_max_limit;

extern FLUENT_EXPORT void Mark_Boundary_Cells(Domain *domain);

extern FLUENT_EXPORT cxboolean capillary_pressure_on;

extern FLUENT_EXPORT cxboolean darcy_solver;
extern FLUENT_EXPORT cxboolean mp_aniso_rc;
extern FLUENT_EXPORT int mp_aniso_rc_method;
extern FLUENT_EXPORT cxboolean add_capillary_pressure_to_flux;
extern FLUENT_EXPORT cxboolean alternative_rel_perm;

extern FLUENT_EXPORT cxboolean mp_turb_visc_damp;
extern FLUENT_EXPORT real M_mp_keC3;
extern FLUENT_EXPORT real M_mp_sig_v;
extern FLUENT_EXPORT int mp_fpi;
extern FLUENT_EXPORT int mp_ref;
extern FLUENT_EXPORT real mp_wall_d_limit;
extern FLUENT_EXPORT void mp_drho_dt_term(Domain *domain, Svar nv, real *local_inlet_flux_sum);
extern FLUENT_EXPORT void mp_collect_fluxes(Domain *domain, Svar nv, cxboolean p_vof);
extern FLUENT_EXPORT void Update_CN_Continuity_Imbalance(Domain *domain, Svar sv_imbalance,
                                                         cxboolean add_mass_error);
extern FLUENT_EXPORT void Model_Initialize_mphase(void);

extern FLUENT_EXPORT void update_outlet_vof(Domain *phaseDomain, cxboolean second_order,
                                            VOF_Scheme_Type scheme_type, Svar sv_vof, Svar sv_vFlux);

extern FLUENT_EXPORT void scale_face_vof(Domain *domain);

extern FLUENT_EXPORT unsigned int vof_patch_bit;

extern FLUENT_EXPORT cxboolean vof_anti_diffusion;
extern FLUENT_EXPORT real vof_sharpen_factor;
extern FLUENT_EXPORT cxboolean vof_anti_diff_enhanced;
extern FLUENT_EXPORT cxboolean vof_anti_diff_enhanced_linearization;
extern FLUENT_EXPORT cxboolean vof_anti_diff_dynamic;
extern FLUENT_EXPORT real vof_anti_diff_dynamic_exponent;
extern FLUENT_EXPORT int vof_anti_diff_dynamic_method;
extern FLUENT_EXPORT int vof_anti_diff_grad_method;
extern FLUENT_EXPORT real Interior_Anti_Diff_Flux(face_t f, Thread *t, cell_t c0, Thread *t0,
                                                  cell_t c1, Thread *t1, real flux);
extern FLUENT_EXPORT real Periodic_Anti_Diff_Flux(face_t f, Thread *t, cell_t c0, Thread *t0,
                                                  cell_t c1, Thread *t1, real flux);
extern FLUENT_EXPORT real Boundary_Anti_Diff_Flux(face_t f, Thread *t, cell_t c0, Thread *t0,
                                                  real flux);
extern FLUENT_EXPORT cxboolean vof_improved_wall_treatment;
extern FLUENT_EXPORT cxboolean node_based_vof_grad;
extern FLUENT_EXPORT cxboolean node_based_vof_new_framework;
extern FLUENT_EXPORT cxboolean mp_regime_modeling_flag;
extern FLUENT_EXPORT cxboolean mp_alloc_bridge_nodes_p;
extern FLUENT_EXPORT void set_mp_alloc_bridge_nodes_p(Domain *domain);
extern FLUENT_EXPORT cxboolean mp_first_time_step;
extern FLUENT_EXPORT real omega_p_conv;

extern FLUENT_EXPORT cxboolean enable_vof_min_treatment;
extern FLUENT_EXPORT double mp_vol_frac_min;
extern FLUENT_EXPORT double mp_vol_frac_max;
extern FLUENT_EXPORT double mp_vol_frac_low;
extern FLUENT_EXPORT double mp_vol_frac_top;
extern FLUENT_EXPORT double mp_vol_frac_low_cutoff;
extern FLUENT_EXPORT double mp_vol_frac_min_ia_hmt;

extern FLUENT_EXPORT real SD_EPS;

extern FLUENT_EXPORT cxboolean mp_compress_alt_bc;
extern FLUENT_EXPORT cxboolean mp_compress_use_maxwell;

extern FLUENT_EXPORT cxboolean mp_pbndr_vof_enhanced;
extern FLUENT_EXPORT void mp_get_poutlet_f_vofs_enhanced(face_t f, Thread *t, Thread **pt, cell_t c0,
                                                         Thread **pt0, real f_vof[MAX_PHASES]);

/*end of multiphase model global variables */

/* min time scale post-processing */
extern FLUENT_EXPORT void Fill_MP_Min_Time_Scale(Domain *domain);
extern FLUENT_EXPORT void Compute_Locally_Averaged_DT_Inv(Domain *domain, Svar sv_flux_sum,
                                                          Svar sv_dt_avg_inv, cxboolean exchange);

/* interphase heat transfer*/
extern FLUENT_EXPORT void Add_Interphase_Heat_Transfer_Global(Domain *PTR_RESTRICT domain);
extern FLUENT_EXPORT void MP_Check_Zero_Ap_Global(cell_t c, Thread *PTR_RESTRICT t, Svar nx,
                                                  real *PTR_RESTRICT const AP, real *PTR_RESTRICT const b,
                                                  real *PTR_RESTRICT const x, real volume);
extern FLUENT_EXPORT real Vapor_To_Interface_Heat_Transfer_Coeff_New(cell_t c,
                                                                     Thread *ti, Thread *tj, cxboolean vapor_phase_i);

/* Type of multi-phase coupling)*/
extern FLUENT_EXPORT void Cal_Adv_TPC_Const(real T_from, real T_to, real T_SAT, real vof_from, real vof_to,
                                            int *const_from, int *const_to);

extern FLUENT_EXPORT void Cal_Adv_TPC_Const_One_Factor(real m_dot, real T_from, real T_to, real T_SAT,
                                                       real vof_from, real vof_to, int *const_mt);
/* check verbose function*/
extern FLUENT_EXPORT void Check_MT_Latent_Heat(cell_t c, int pp_index,
                                               int from_index, int to_index, real from_phase_latent, real to_phase_latent);

extern FLUENT_EXPORT cxboolean MP_COUPLED_PV;
extern FLUENT_EXPORT cxboolean MP_COUPLED_FULL;

/* End of multi-phase coupling type*/

#if DRIFT_COUPLED
extern FLUENT_EXPORT cxboolean DRIFT_FORCE_COUPLED;
extern FLUENT_EXPORT cxboolean DRIFT_FORCE_BOUNDARY_COUPLED;
#endif

/* Solution of VOF in Delta FORM for P_V_VOF Coupling*/
extern FLUENT_EXPORT cxboolean coupled_vof_delta_form;
/* End of Vof Delta Form*/

/*  coupled vof related variables */
extern FLUENT_EXPORT cxboolean COUPLED_VOF;
extern FLUENT_EXPORT cxboolean cvf_mom_impl_relax;
extern FLUENT_EXPORT cxboolean mp_mom_pseudo_smoothed;
extern FLUENT_EXPORT cxboolean mp_pseudo_false_linearization;

/* NLBF functions definitions */
extern FLUENT_EXPORT void Non_Local_Boundary_Field(Domain *mixDomain);
extern FLUENT_EXPORT void NLBF_Coordinate_Finder(Domain *mixDomain);
extern FLUENT_EXPORT void NLBF_cleaner(void);
extern FLUENT_EXPORT double nlbf_temperature_seeker(face_t f, Thread *from_t);
extern FLUENT_EXPORT cxboolean nlbf_activation;

#define SV_X_I(nX,i)((Svar)((nX)+(i)))
#define SV_DRAG_COEFF_I(i)SV_X_I(SV_DRAG_COEFF_0,i)
#define SV_DRAG_COEFF_IJ(i,j)SV_X_I(SV_DRAG_COEFF_0,(i)+(j)*((j)-1)/2)

#define SV_DRAG_COEFF_ANISO_XX_I(i)SV_X_I(SV_DRAG_COEFF_ANISO_XX_0,i)
#define SV_DRAG_COEFF_ANISO_XX_IJ(i,j)SV_X_I(SV_DRAG_COEFF_ANISO_XX_0,(i)+(j)*((j)-1)/2)
#define SV_DRAG_COEFF_ANISO_YY_I(i)SV_X_I(SV_DRAG_COEFF_ANISO_YY_0,i)
#define SV_DRAG_COEFF_ANISO_YY_IJ(i,j)SV_X_I(SV_DRAG_COEFF_ANISO_YY_0,(i)+(j)*((j)-1)/2)
#define SV_DRAG_COEFF_ANISO_ZZ_I(i)SV_X_I(SV_DRAG_COEFF_ANISO_ZZ_0,i)
#define SV_DRAG_COEFF_ANISO_ZZ_IJ(i,j)SV_X_I(SV_DRAG_COEFF_ANISO_ZZ_0,(i)+(j)*((j)-1)/2)
#define SV_DRAG_COEFF_ANISO_XY_I(i)SV_X_I(SV_DRAG_COEFF_ANISO_XY_0,i)
#define SV_DRAG_COEFF_ANISO_XY_IJ(i,j)SV_X_I(SV_DRAG_COEFF_ANISO_XY_0,(i)+(j)*((j)-1)/2)
#if RP_3D
#define SV_DRAG_COEFF_ANISO_XZ_I(i)SV_X_I(SV_DRAG_COEFF_ANISO_XZ_0,i)
#define SV_DRAG_COEFF_ANISO_XZ_IJ(i,j)SV_X_I(SV_DRAG_COEFF_ANISO_XZ_0,(i)+(j)*((j)-1)/2)
#define SV_DRAG_COEFF_ANISO_YZ_I(i)SV_X_I(SV_DRAG_COEFF_ANISO_YZ_0,i)
#define SV_DRAG_COEFF_ANISO_YZ_IJ(i,j)SV_X_I(SV_DRAG_COEFF_ANISO_YZ_0,(i)+(j)*((j)-1)/2)
#endif

/* macros for accessing cell/face values */

#define C_PHASE_DIAMETER(c,t)FAST_C_STORAGE_R(c,t,SV_PHASE_DIAMETER)

/* VOF macros when storing one VOF per domain (multi-domain version) */
#define SV_VOF_N (!n_phase_solver? SV_VOF : SV_VOF_NORM)

#define C_VOF(c,t) C_STORAGE_R(c,t,SV_VOF_N)
#define C_VOF_SOLVE(c,t)FAST_C_STORAGE_R(c,t,SV_VOF)
#define C_VOF_M1(c,t)FAST_C_STORAGE_R(c,t,SV_VOF_M1)
#define C_VOF_M2(c,t)C_STORAGE_R(c,t,SV_VOF_M2)
#define F_VOF(e,t)    C_VOF(e,t)
#define F_VOF_SOLVE(e,t)   C_VOF_SOLVE(e,t)
#define F_VOF_M1(e,t) C_VOF_M1(e,t)
#define F_VOF_M2(e,t) C_VOF_M2(e,t)
#define F_VOF_INST(f,t)FAST_F_STORAGE_R(f,t,SV_VOF_INST)

#define C_SMOOTHED_VOF(c,t) C_STORAGE_R(c,t,SV_SMOOTHED_VOF)
#define C_VOF_G(c,t)FAST_C_STORAGE_R_NV(c,t,SV_VOF_G)
#define C_VOF_RG(c,t)FAST_C_STORAGE_R_NV(c,t,SV_VOF_RG)
#define C_MU_INTERFACE(c,t) C_STORAGE_R(c,t,SV_MU_INTERFACE)

#define C_SLIP_U(c,t)C_STORAGE_R(c,t,SV_SLIP_U)
#define C_SLIP_V(c,t)C_STORAGE_R(c,t,SV_SLIP_V)
#if RP_3D
#define C_SLIP_W(c,t)C_STORAGE_R(c,t,SV_SLIP_W)
#endif
#define C_RELAX_TIME(c,t) C_STORAGE_R(c,t,SV_RELAX_TIME)

#define F_TCOEFF(f,t) FAST_F_STORAGE_R(f,t,SV_F_TCOEFF)
#define F_TCOEFF_RS(f,t) F_STORAGE_R(f,t,SV_F_TCOEFF_RS)
#define F_VFLUX(f,t) FAST_F_STORAGE_R(f,t,SV_VFLUX)
#define F_VFLUX_M1(f,t) FAST_F_STORAGE_R(f,t,SV_VFLUX_M1)
#define F_VFLUX_M2(f,t) F_STORAGE_R(f,t,SV_VFLUX_M2)

#define C_DRAG_COEFF_IJ(c,t,i,j)C_STORAGE_R(c,t,SV_DRAG_COEFF_IJ(i,j))
#define C_DRAG_COEFF_ANISO_XX_IJ(c,t,i,j)C_STORAGE_R(c,t,SV_DRAG_COEFF_ANISO_XX_IJ(i,j))
#define C_DRAG_COEFF_ANISO_YY_IJ(c,t,i,j)C_STORAGE_R(c,t,SV_DRAG_COEFF_ANISO_YY_IJ(i,j))
#define C_DRAG_COEFF_ANISO_ZZ_IJ(c,t,i,j)C_STORAGE_R(c,t,SV_DRAG_COEFF_ANISO_ZZ_IJ(i,j))
#define C_DRAG_COEFF_ANISO_XY_IJ(c,t,i,j)C_STORAGE_R(c,t,SV_DRAG_COEFF_ANISO_XY_IJ(i,j))
#if RP_3D
#define C_DRAG_COEFF_ANISO_XZ_IJ(c,t,i,j)C_STORAGE_R(c,t,SV_DRAG_COEFF_ANISO_XZ_IJ(i,j))
#define C_DRAG_COEFF_ANISO_YZ_IJ(c,t,i,j)C_STORAGE_R(c,t,SV_DRAG_COEFF_ANISO_YZ_IJ(i,j))
#endif

#define C_GP(c,t)FAST_C_STORAGE_R(c,t,SV_GP)
#define C_GPP(c,t)C_STORAGE_R(c,t,SV_GPP)
#define C_GP_AP(c,t)C_STORAGE_R(c,t,SV_GP_AP)
#define C_GP_S(c,t)C_STORAGE_R(c,t,SV_GP_S)
#define C_GP_G(c,t)FAST_C_STORAGE_R_NV(c,t,SV_GP_G)

#define C_CAP(c,t)FAST_C_STORAGE_R(c,t,SV_CAP)
#define C_CAP_G(c,t)FAST_C_STORAGE_R_NV(c,t,SV_CAP_G)
#define F_CAP(e,t) C_CAP(e,t)

#define C_RELATIVE_PERMEABILITY(c,t)FAST_C_STORAGE_R(c,t,SV_RELATIVE_PERMEABILITY)

#define F_C0_FGP_COEFF(f,t)C_STORAGE_R(f,t,SV_C0_FGP_COEFF)
#define F_C1_FGP_COEFF(f,t)C_STORAGE_R(f,t,SV_C1_FGP_COEFF)
#define F_GP(e,t) C_GP(e,t)
#define F_GPP(e,t) C_GPP(e,t)

#define C_VOF_OLD(c,t)C_STORAGE_R(c,t,SV_MP_VOF_OLD)

#define S_NET_FLUX_DIFF(c,t)C_STORAGE_R(c,t,SV_NET_FLUX_DIFF)

#define F_VFLUX_PREV(f,t)FAST_F_STORAGE_R(f,t,SV_VFLUX_PREV)

#define F_C0_FP_COEFF(f,t)FAST_F_STORAGE_R(f,t,SV_C0_FP_COEFF)
#define F_C1_FP_COEFF(f,t)FAST_F_STORAGE_R(f,t,SV_C1_FP_COEFF)

#define F_C0_FPV_COEFF(f,t,i)F_STORAGE_R(f,t,SV_C0_FPV_COEFF(i))
#define F_C1_FPV_COEFF(f,t,i)F_STORAGE_R(f,t,SV_C1_FPV_COEFF(i))

#define F_C0_FPVOF_COEFF(f,t,i)F_STORAGE_R(f,t,SV_C0_FPVOF_COEFF(i))
#define F_C1_FPVOF_COEFF(f,t,i)F_STORAGE_R(f,t,SV_C1_FPVOF_COEFF(i))

#define C_FF_COEFF(c,t,i)C_STORAGE_R_NV(c,t,SV_C0_FF_COEFF(i))

#if DRIFT_COUPLED
#define F_C0_FPV_DRIFT_COEFF(f,t,i)F_STORAGE_R(f,t,SV_C0_FPV_DRIFT_COEFF(i))
#define F_C1_FPV_DRIFT_COEFF(f,t,i)F_STORAGE_R(f,t,SV_C1_FPV_DRIFT_COEFF(i))

#define S_VOF_DRIFT(c,t)C_STORAGE_R(c,t,SV_MP_DRIFT_FORCE)
#define S_DRIFT_COEFF(c,t)C_STORAGE_R(c,t,SV_MP_DRIFT_COEFF)
#define P_DRIFT_COEFF(c,t)C_STORAGE_R(c,t,SV_MP_DRIFT_S_P_COEFF)
#endif



#define F_PREV_FACE_VOF(f,t)F_STORAGE_R(f,t,SV_PREV_FACE_VOF)
#define F_VOF_SO_CORR(f,t)F_STORAGE_R(f,t,SV_VOF_SO_CORR)
#define F_FACE_P_S0(f,t)F_STORAGE_R(f,t,SV_MP_FACE_P_S0)
#define F_FACE_P_S1(f,t)F_STORAGE_R(f,t,SV_MP_FACE_P_S1)
/* end of macros for accessing cell/face values */


/* section for constants and loops */
#if RP_DOUBLE                /*single-double precision zero and epsilon*/
# define SD_ZERO 1.e-40
/* # define SD_EPS 1.e-08 */
# define SD_NEG_BIG -1.e+30
# define SD_BIG 1.e+30
#else
# define SD_ZERO 1.e-10
/* # define SD_EPS 1.e-06 */
# define SD_NEG_BIG -1.e+20
#if (sys_ultra || sys_ultra_64)
# define SD_BIG 1.e+17
#else
# define SD_BIG 1.e+20
#endif
#endif

/*volume fraction limits for multiphase models*/
#define VOF_MIN mp_vol_frac_min
#define VOF_MAX mp_vol_frac_max
#define VOF_LOW_LIMIT mp_vol_frac_low
#define VOF_TOP_LIMIT mp_vol_frac_top
/*volume fraction cut-off for phase-level equations */
#define VOF_LOW_CUTOFF mp_vol_frac_low_cutoff
/* Minimum volume fraction for area density calculations in heat/mass transfer */
#define VOF_MIN_IA_HMT mp_vol_frac_min_ia_hmt
#define VOF_MAX_IA_HMT (1.- mp_vol_frac_min_ia_hmt)
#define VOF_MIN_IAD VOF_MIN_IA_HMT
#define VOF_MAX_IAD VOF_MAX_IA_HMT

/*area density storage */
#define C_MP_AREA_DENSITY(c,t,i)FAST_C_STORAGE_R_XV(c,t,SV_MP_AREA_DENSITY,i)
/* diffusion coeff storage */
#define F_VOF_DIFF_COEFF(f,t,i)FAST_F_STORAGE_R_XV(f,t,SV_VOF_DIFF_COEFF,i)
#define F_VOF_DIFF_FLUX(f,t,i)FAST_F_STORAGE_R_XV(f,t,SV_VOF_DIFF_FLUX,i)

/* GENTOP variables storage */
#define C_MP_GENTOP_PHI_SURF(c,t,i)C_STORAGE_R_XV(c,t,SV_MP_GENTOP_PHI_SURF,i)
#define C_MP_GENTOP_PHI_MORPH(c,t,i)C_STORAGE_R_XV(c,t,SV_MP_GENTOP_PHI_MORPH,i)
#define C_MP_GENTOP_PHI_BGND(c,t,i)C_STORAGE_R_XV(c,t,SV_MP_GENTOP_PHI_BGND,i)
#define C_MP_GENTOP_PHI_COAL(c,t,i)C_STORAGE_R_XV(c,t,SV_MP_GENTOP_PHI_COAL,i)

/* type of phase pairs */
#define CONT_DISP_PHASE_P(i_type,j_type) \
  ((i_type == CONT_PHASE && j_type == DISP_PHASE) || \
   (i_type == DISP_PHASE && j_type == CONT_PHASE))
#define CONT_CONT_PHASE_P(i_type,j_type) (i_type == CONT_PHASE && j_type == CONT_PHASE)
#define DISP_DISP_PHASE_P(i_type,j_type) (i_type == DISP_PHASE && j_type == DISP_PHASE)

#define RP_NOT_ALLOCATE_MASS_FLUX 0

#define P_PHASE 0          /*primary phase for all multiphase models*/
#define S_PHASE 1          /*secondary phase for drift-flux and cavitation*/

#define phase_loop(phase,n_phases) for(phase=0; phase < n_phases; ++phase)
#define secondary_phase_loop(n,nphase) for(n=1; n < nphase; ++n)
#define loop_solved_phases(n,nphase) for(n=(n_phase_solver? 0 :1); n < nphase; ++n)

#define matrix_loop(i,j,n)for(i=0;i<n;++i)for(j=0;j<n;++j)
#define matrix_loop_up_off_diagonal(i,j,n)for(j=1;j<n;++j)for(i=0;i<j;++i)

#define KS_INIT_ZERO(ks) \
  { \
    int iks; \
    for(iks=0; iks < mp_n; ++iks) \
      ks[iks] = 0.; \
  }

/* end of section for constants and loops*/


/*section for derived macros*/
/* mostly all of the derived macros show some kind of inefficiency
   in the data structure or control flow */

/*Eulerian multiphase macros*/
#if 0
#define C_VOF_M_DENSITY(c,t)(!n_phase_solver? C_VOF(c,t)*C_R(c,t) : C_VOF_SOLVE(c,t)*C_R(c,t))
#else
#define C_VOF_M_DENSITY(c,t)(C_VOF(c,t)*C_R(c,t))
#endif
#define C_MU_EFF_MIXTURE(c,t,pt,phase)\
(C_MU_L(c,pt[phase])+C_R(c,pt[phase])/C_R(c,t)*C_MU_T(c,t))
#define C_VOF_M_DENSITY_M1(c,t)(C_VOF_M1(c,t)*C_R_M1(c,t))
#define C_VOF_M_DENSITY_M2(c,t)(C_VOF_M2(c,t)*C_R_M2(c,t))

#define C_TCOEFF(c,t,Pr) (C_MU_L(c,t)+MAX(C_MU_T(c,t),0.)/Pr)

#define C_TCOEFF_MIXTURE(c,t,pt,phase,Pr) (C_MU_L(c,pt[phase])+\
C_R(c,pt[phase])/C_R(c,t)*MAX(C_MU_T(c,t),0.)/Pr)

#define C_NUT_EFF(c,t,Pr) ((C_MU_L(c,t)+C_R(c,t)*MAX(C_NUT(c,t),0.))/Pr)

#define C_NUT_EFF_MIXTURE(c,t,pt,phase,Pr) ((C_MU_L(c,pt[phase])+\
C_R(c,pt[phase])*MAX(C_NUT(c,t),0.))/Pr)

#if 0 /* CAVVOF */
#define RHO_PHASE_F_INT(c0,t0,c1,t1,phase)\
  (0.5*(C_R(c0,t0[phase])+C_R(c1,t1[phase])) )
#define RHO_PHASE_M1_F_INT(c0,t0,c1,t1,phase)\
  (0.5*(C_R_M1(c0,t0[phase])+C_R_M1(c1,t1[phase])))
#define RHO_PHASE_F_BND(c0,t0,phase) C_R(c0,t0[phase])
#else
#define RHO_PHASE_F_INT(c0,t0,c1,t1,phase)\
  (cav_l? 0.5*(C_R(c0,THREAD_SUPER_THREAD(t0[phase])) + C_R(c1,THREAD_SUPER_THREAD(t1[phase])))  \
              : 0.5*(C_R(c0,t0[phase])+C_R(c1,t1[phase])) )
#define RHO_PHASE_M1_F_INT(c0,t0,c1,t1,phase)\
  (cav_l? 0.5*(C_R_M1(c0,THREAD_SUPER_THREAD(t0[phase]))+C_R_M1(c1,THREAD_SUPER_THREAD(t1[phase])))  \
              : 0.5*(C_R_M1(c0,t0[phase])+C_R_M1(c1,t1[phase])))
#define RHO_PHASE_F_BND(c0,t0,phase) \
  (cav_l? C_R(c0,THREAD_SUPER_THREAD(t0[phase])) : C_R(c0,t0[phase]) )
#endif

#define F_R_PHASE(f,t,c0,t0,c1,t1) \
        ( NNULLP(THREAD_STORAGE(t,SV_DENSITY))? F_R(f,t) : 0.5*(C_R(c0,t0)+C_R(c1,t1)) )
#define F_R_PHASE_BND(f,t,c0,t0)  \
        ( NNULLP(THREAD_STORAGE(t,SV_DENSITY))? F_R(f,t) : C_R(c0,t0))

#define RHO_FLUID_F_INT(rho,f,t,c0,t0,c1,t1,fluid) \
{ if (!mp_mfluid) (rho) = mp_mixture? F_R(f,t):.5*(C_R(c0,t0)+C_R(c1,t1));\
  else  \
   {\
      int pphase;\
      Thread **ppt  = THREAD_SUB_THREADS(t); \
      Thread **ppt0 = THREAD_SUB_THREADS(t0); \
      Thread **ppt1 = THREAD_SUB_THREADS(t1); \
      (rho) = 0.;\
      phase_loop(pphase,mp_n)\
        (rho) += F_VOF(f,ppt[pphase])*F_R_PHASE(f,t,c0,ppt0[pphase],c1,ppt1[pphase]); \
   }\
}

#define RHO_FLUID_F_BND(rho,f,t,c0,t0,fluid) \
{ if (!mp_mfluid) (rho) = mp_mixture ? F_R(f,t):C_R(c0,t0);\
  else \
   {\
     int phase_loc;         \
      Thread **pt  = THREAD_SUB_THREADS(t); \
      Thread **pt0 = THREAD_SUB_THREADS(t0); \
      (rho) = 0.;\
      phase_loop(phase_loc,mp_n)\
        (rho) += F_VOF(f,pt[phase_loc])*F_R_PHASE_BND(f,pt[phase_loc],c0,pt0[phase_loc]);\
   }\
}

#define MU_DOMAIN_LAM_FLUID_F_BND(mu,f,pt,c0,t0,pt0,fluid) \
{ if (mp_mixture)\
    {\
      int phase_loc;\
      (mu) = 0.;\
      phase_loop(phase_loc,mp_n)            \
  (mu) += F_VOF(f,pt[phase_loc])*C_MU_L(c0,pt0[phase_loc]);\
    }\
  else\
    (mu) = C_MU_L(c0,t0);\
}

/*  #if CAVVOF */
#if 0
#define MP_F_RHO_BND(f,t) F_R(f,t)
#define MP_C_RHO(c,t)     C_R(c,t)
#define MP_C_RHO_M1(c,t)  C_R_M1(c,t)
#define C_P_M_RHO_RATIO(c,t,pt) C_R(c,pt)/C_R(c,t)
#define F_M_P_RHO_RATIO(f,t,c0,pt0,c1,pt1) 1.0
#define MP_C_MU_T(c,t)  C_MU_T(c,t)
#else
/* #define MP_F_RHO_BND(f,t) (cav_l? F_R(f,THREAD_SUPER_THREAD(t)) : F_R(f,t)) */
#define MP_C_RHO(c,t)     (cav_l? C_R(c,THREAD_SUPER_THREAD(t))   : C_R(c,t))
#define MP_C_RHO_M1(c,t)  (cav_l? C_R_M1(c,THREAD_SUPER_THREAD(t)): C_R_M1(c,t))
#define C_P_M_RHO_RATIO(c,t,pt) (cav_l? 1.0 : C_R(c,pt)/C_R(c,t))
#define F_M_P_RHO_RATIO(f,t,c0,pt0,c1,pt1) \
         (cav_l? (NNULLP(THREAD_STORAGE(t,SV_DENSITY))? F_R(f,t): C_R(c0,t->t0)) \
                 /((F_VFLUX(f,t)>0.)?C_R(c0,pt0): C_R(c1,pt1)) : 1.0)
#define MP_C_MU_T(c,t)  (cav_l? ( p_enhancement ?  \
                                  C_MU_T  (c,THREAD_SUPER_THREAD(t)):         \
                                  C_MU_EFF(c,THREAD_SUPER_THREAD(t)) ): C_MU_T(c,t))
#endif

#if 0
#define MP_F_RHO(f,t,c0,t0,c1,t1)\
      ( (M_compressible || cav_l) ? \
               ((F_VFLUX(f,t) > 0.) ?  MP_C_RHO(c0,t0) : MP_C_RHO(c1,t1)) :\
               (0.5*(C_R(c0,t0)+C_R(c1,t1))) )
#endif

#if 1
#define MP_F_RHO(f,t,c0,t0,c1,t1)   \
        (cav_l? F_R(f,THREAD_SUPER_THREAD(t)) : F_R_PHASE(f,t,c0,t0,c1,t1) )
#define MP_F_RHO_BND(f,t,c0,t0) \
        (cav_l? F_R(f,THREAD_SUPER_THREAD(t)) : F_R_PHASE_BND(f,t,c0,t0))

#else
#define MP_F_RHO(f,t,c0,t0,c1,t1)((F_VFLUX(f,t)>0.)?C_R(c0,t0):C_R(c1,t1))
#endif

#define TEMP_M(c,t) ( (sg_temperature && NNULLP(THREAD_STORAGE(t,SV_T)) )?  C_T(c,t) : T_REF)

/* Macros for generic time bounded second order formulation */
#define C_VOF_PH(c,t) C_STORAGE_R(c,t,SV_VOF_PH)
#define C_VOF_NH(c,t) C_STORAGE_R(c,t,SV_VOF_NH)
#define MP_C_RHO_PH(c,t)  (cav_l? C_RHO_PH(c,THREAD_SUPER_THREAD(t)): C_RHO_PH(c,t))
#define MP_C_RHO_NH(c,t)  (cav_l? C_RHO_NH(c,THREAD_SUPER_THREAD(t)): C_RHO_NH(c,t))
#define C_VOF_M_DENSITY_PH(c,t) (C_VOF_PH(c,t)*C_RHO_PH(c,t))
#define C_VOF_M_DENSITY_NH(c,t) (C_VOF_NH(c,t)*C_RHO_NH(c,t))

#define C_AP_FALSE(c,t) C_STORAGE_R(c,t,SV_AP_FALSE)

/*  macros for volumeFlux-massFlux operation */
/* these macros show a conflict between models:
   single fluid uses mass flux, mphase uses velocity flux*/

#define C_VOLUME_IMBALANCE(e,t) C_MASS_IMBALANCE(e,t)
#define BNDR_RHO(c0,t0) C_R(c0,t0)

#define BNDR_FLUX_M_RHO(flux,c0,t0)\
{\
  if (!sg_vFlux)\
    {\
      flux *= BNDR_RHO(c0,t0);\
    }\
}
/* end of macros for volumeFlux-massFlux operation*/

#define MP_F_INTERP_AUX_VAR_UPWIND(f,t,sv,phi_f)\
{\
  Svar _m_sv_flux = sv_nFlux;\
  real _m_C;\
  _m_C = F_STORAGE_R(f,t,_m_sv_flux);\
  if (_m_C > 0.0)\
    {\
      Thread *_m_t0 = THREAD_T0(t);\
      cell_t _m_c0 = F_C0(f,t);\
      real _m_phi_0 = C_STORAGE_R(_m_c0,_m_t0,sv);\
      phi_f = _m_phi_0;\
    }\
  else\
    {\
      Thread *_m_t1 = THREAD_T1(t);\
      cell_t _m_c1 = F_C1(f,t);\
      real _m_phi_1 = C_STORAGE_R(_m_c1,_m_t1,sv);\
      phi_f = _m_phi_1;\
    }\
}

#define MP_F_INTERP_AUX_VAR_CENTRAL(f,t,sv,phi_f)\
{\
  Thread *_m_t0 = THREAD_T0(t);\
  Thread *_m_t1 = THREAD_T1(t);\
  cell_t _m_c0 = F_C0(f,t);\
  cell_t _m_c1 = F_C1(f,t);\
  phi_f = 0.5 * (C_STORAGE_R(_m_c0,_m_t0,sv) + C_STORAGE_R(_m_c1,_m_t1,sv));\
}

#define MP_F_INTERP_AUX_VAR(f,t,sv,phi_f)\
{\
  extern FLUENT_EXPORT Discretization_Scheme mp_f_aux_var_interp;\
  switch(mp_f_aux_var_interp)\
    {\
    case CENTRAL_DIFFERENCING:\
      MP_F_INTERP_AUX_VAR_CENTRAL(f,t,sv,phi_f);\
      break;\
    case FIRST_ORDER_UPWIND:\
      MP_F_INTERP_AUX_VAR_UPWIND(f,t,sv,phi_f);\
      break;\
    default:\
      Error("Interpolation scheme %d not available for auxiliary variables",mp_f_aux_var_interp);\
      break;\
    }\
}

#define LIMIT_G(vof) (1.-exp(-30000.0*(vof)))
#define CONST_GVOF 1.5e-04
#define EPSLIM 0.998
#define LIMIT_FRICTION_MU 100000.0
#define EPS_FRICTION_JOHN 0.83333
#define EPS_FRICTION_SYAM 0.98333


#define LIMIT_VOF(vof)\
{\
  if ((vof) < (VOF_LOW_LIMIT))\
    (vof) = VOF_MIN;\
  else if ((vof) > (VOF_TOP_LIMIT))\
    (vof) = VOF_MAX;\
}

#define LIMIT_VOF_LOW(vof)\
{\
  if ((vof) < (VOF_LOW_LIMIT))\
    (vof) = VOF_MIN;\
}

#define LIMIT_VOF_TOP(vof)\
{\
  if ((vof) > (VOF_TOP_LIMIT))\
    (vof) = VOF_MAX;\
}

#define FILTER_VOF(vof,low,top)\
{\
  if ((vof) < (low))\
    (vof) = VOF_MIN;\
  else if ((vof) > (top))\
    (vof) = VOF_MAX;\
}

#define GET_PHASE_K_SVAR(i,sv_k)\
{\
  if (GVAR_TURB(rp, rsm))\
    {\
      if (mp_mfluid && mp_n_rsm && (mp_rsm_type == TURB_MP_RSM_DISPERSED))\
  sv_k = (i==0) ? SV_K : SV_NULL;\
      else\
  sv_k = SV_K;\
    }\
  else\
    {\
      if (mp_mfluid && ((mp_n_ke && (mp_ke_type == TURB_MP_KE_DISPERSED))\
         || (mp_n_les && (mp_les_type == TURB_MP_LES_DISPERSED))))\
  sv_k = (i==0) ? SV_K : SV_NULL;\
      else\
  sv_k = SV_K;\
    }\
}

#define USE_ISOTROPIC_MODEL(isotropic_model,t,eles)\
{\
  if (mp_mfluid && GVAR_TURB(rp, rsm) && mp_n_rsm)\
    {\
      if (DOMAIN_INDEX(THREAD_DOMAIN(t)) == P_PHASE)\
  isotropic_model = !GVAR_TURB(rp, rsm);\
      else\
  isotropic_model = TRUE;\
    }\
  else\
    {\
      if (eles)\
  isotropic_model = TRUE;\
      else\
  isotropic_model = !GVAR_TURB(rp, rsm);\
    }\
}

#define LIMIT_MPG_VELOCITY(vof,uvel,vvel,wvel)\
{\
  if ( (vof) <= CONST_GVOF )\
    {\
      real limit = LIMIT_G( (vof) );\
      (uvel) *= limit;\
      (vvel) *= limit;\
      (wvel) *= limit;\
    }\
}

#define LIMIT_MPG_FLUX(vof0,vof1,voff,fluxf)\
{\
  if ( ( (vof0) <= CONST_GVOF ) && ( (vof1) <= CONST_GVOF ) ) \
    {\
      real limit = LIMIT_G( (voff) );\
      (fluxf) *= limit;\
    }\
}

#define LIMIT_A_G_T(gTemp,vof)\
{\
  SETMIN( (gTemp), 0.1 );\
  if( (vof) <= CONST_GVOF ) (gTemp) = SD_EPS;\
}

#define GET_PARENT_THREAD(tk,thread)\
{\
  if (GVAR_TURB(rp, rsm))\
    {\
      if (mp_mfluid && ((mp_rsm_type == TURB_MP_RSM_DISPERSED)))\
        tk = lookup_thread_by_id(DOMAIN_SUPER_DOMAIN(THREAD_DOMAIN(thread)),\
               thread->id);\
      else\
        tk = thread; \
    }\
  else if (GVAR_TURB(rp, les))\
    {\
      if (mp_mfluid && (mp_les_type == TURB_MP_LES_DISPERSED))\
        tk = lookup_thread_by_id(DOMAIN_SUPER_DOMAIN(THREAD_DOMAIN(thread)),\
           thread->id);\
      else\
        tk = thread; \
    }\
  else\
    {\
      if (mp_mfluid && ((mp_ke_type == TURB_MP_KE_DISPERSED) ||\
            (mp_ke_type == TURB_MP_KE_EACH_PHASE) ))\
        tk = lookup_thread_by_id(DOMAIN_SUPER_DOMAIN(THREAD_DOMAIN(thread)),\
               thread->id);\
      else\
        tk = thread; \
    }\
}

FLUENT_EXPORT void Add_Cell_Source(Domain *domain, Svar sv_imbalance, Svar sv_source);
FLUENT_EXPORT void Add_Time_Volume_Source(Domain *domain);
FLUENT_EXPORT void Update_MP_AP_for_PISO(Domain *domain, Svar sv_source);

/*add wall flux to the ap or to the source */
#define ADD_WFLUX(c,t,nv,nv_ap,nv_s,flux)\
{\
  if (flux < 0.)\
     C_STORAGE_R(c,t,nv_ap) += flux;\
  else\
     C_STORAGE_R(c,t,nv_s)  += flux*C_STORAGE_R(c,t,nv);\
}

#define FROM_DOMAIN(m) m->from.domain
#define   TO_DOMAIN(m) m->to.domain
#define FROM_SPECIES_NAME(m) m->from.species_name
#define   TO_SPECIES_NAME(m) m->to.species_name
#define FROM_SPECIES_ID(m) m->from.species_id
#define   TO_SPECIES_ID(m) m->to.species_id

#define C_MT_LATENT_HEAT(c,t,i)C_STORAGE_R_XV(c,t,SV_LATENT_HEAT,i)
#define C_MT_VAPOR_PRESS(c,t,i)FAST_C_STORAGE_R_XV(c,t,SV_MT_VAPOR_PRESS,i)
#define C_VAPOR_PRESS(c,t)FAST_C_STORAGE_R(c,t,SV_VAPOR_PRESS)

#define C_MT_SAT_TEMPERATURE(c,t,i)FAST_C_STORAGE_R_XV(c,t,SV_MT_SAT_TEMPERATURE,i)

/* sbm related */
#define F_MT_WALL_LIQ_FRAC(f,t,i) F_STORAGE_R_XV(f,t,SV_MT_WALL_LIQ_FRAC,i)
#define F_MT_LREF(f,t,i) F_STORAGE_R_XV(f,t,SV_MT_LREF,i)
#define F_MT_UREF(f,t,i) F_STORAGE_R_XV(f,t,SV_MT_UREF,i)
#define F_MT_TREF(f,t,i) F_STORAGE_R_XV(f,t,SV_MT_TREF,i)
#define F_MT_SUPHT_MIN(f,t,i) F_STORAGE_R_XV(f,t,SV_MT_SUPHT_MIN,i)
#define F_MT_QSP_FLUX(f,t,i) F_STORAGE_R_XV(f,t,SV_MT_QSP_FLUX,i)
#define F_MT_QSP_FAC1(f,t,i) F_STORAGE_R_XV(f,t,SV_MT_QSP_FAC1,i)
#define F_MT_QSP_FAC2(f,t,i) F_STORAGE_R_XV(f,t,SV_MT_QSP_FAC2,i)
#define F_MT_QNUC_FLUX(f,t,i) F_STORAGE_R_XV(f,t,SV_MT_QNUC_FLUX,i)
#define F_MT_QNUC_FAC(f,t,i) F_STORAGE_R_XV(f,t,SV_MT_QNUC_FAC,i)
#define F_MT_QSP_TOTAL_FLUX(f,t) F_STORAGE_R(f,t,SV_MT_QSP_TOTAL_FLUX)
#define F_MT_QNUC_TOTAL_FLUX(f,t) F_STORAGE_R(f,t,SV_MT_QNUC_TOTAL_FLUX)

#define C_VAP_P(c,t) ( (mp_mass_transfer||NULLP(THREAD_STORAGE(t,SV_VAPOR_PRESS)))? \
                        p_vap : FAST_C_STORAGE_R(c,t,SV_VAPOR_PRESS))
#define P_CAV_L(c,t) cav_coeff*C_VAP_P(c,t)
#define P_CAV_L_F(f,t,c0,t0,c1,t1) \
          ((F_VFLUX(f,t) > 0.) ? P_CAV_L(c0,t0) : P_CAV_L(c1,t1) )
#define P_CAV_L_F_BND(f,t,c0,t0) P_CAV_L(c0,t0)

#define C_SUBTRACT_MASS_SOURCE(c,t,v,ap,s,include_dpm_source)\
{\
  real mass;\
  mass = C_SOURCE_MASS_USER(c,t);\
  if (sg_dpm && include_dpm_source)\
    mass += C_DPMS_MASS(c,t);\
    if (mass > 0.)\
       (ap) -= mass;\
    else\
       (s) -= mass*(v);\
}

#define DONT_SOLVE_IF_AP_SMALL(index,ap)\
{\
  if ((ap) > -SD_EPS)\
    {\
      AMG_D(index) = -1.;\
      AMG_B(index) = -AMG_X(index);\
      AMG_ZERO_OD(index);\
      AMG_CHILD(index) = CHILD_NONE;\
    }\
}

#define DONT_SOLVE_IF_VOF_AP_SMALL_COUPLED(id,index,ap,i)\
{\
  if ((ap) > -SD_EPS)\
    {\
      int neq = BAMG_BLK_SIZE(id);\
      int je;\
      BAMG_ZERO_OD(id,index,i);\
      for (je = 0; je < neq; ++je) \
        BAMG_D(id,index)[i*neq+je] = .0;\
      BAMG_D(id,index)[i*neq+i] = -1.;\
      BAMG_B(id, index)[i] = -BAMG_X(id, index)[i];\
    }\
}



#define DONT_SOLVE_IF_VOF_SMALL(index,vof)\
{\
  if ((vof) <= VOF_LOW_CUTOFF)\
    {\
      AMG_D(index) = -1.;\
      AMG_B(index) = -AMG_X(index);\
      AMG_ZERO_OD(index);\
      AMG_CHILD(index) = CHILD_NONE;\
    }\
}
#define DONT_SOLVE_IF_AP_OR_VOF_SMALL(index,ap,vof, AP_LIMIT, VOF_LIMIT)\
{\
  if ( ((ap) > -AP_LIMIT) || ((vof) <= VOF_LIMIT) )\
    {\
      AMG_D(index) = -1.;\
      AMG_B(index) = -AMG_X(index);\
      AMG_ZERO_OD(index);\
      AMG_CHILD(index) = CHILD_NONE;\
    }\
}

typedef enum
{
  MP_CELL_PARTIAL      = 0,  /* cell surrounded by partially filled cells */
  MP_CELL_VOID         = 1,  /* cell surrounded by void cells */
  MP_CELL_FULL         = 2,  /* cell surrounded by full cells */
  MP_CELL_FLOTSAM_VOID = 3,  /* cell containing flotsam treated as void */
  MP_CELL_FLOTSAM_FULL = 4   /* cell containing flotsam treated as full  */
} MP_CELL_TYPE;

typedef enum
{
  PIN     = 0,
  POUT    = 1,
  OUTFLOW = 2,
  VIN = 3
} BNDR_INDEX;

/* Heterogeneous Reaction structure */
typedef struct hetero_reaction_struct
{
  char name[REACTION_NAME_LENGTH];  /* reaction name */

  int n_reactants;      /* number of reactants */
  Material **mat_reactant;          /* species materials of reactants */
  Domain **domain_reactant;             /* domains of reactants */
  int *reactant;            /* species indices of reactants */
  real *stoich_reactant;          /* stoichiometric coefficients of reactants */
  real *exp_reactant;                 /* rate exponents of reactants: not used */
  real *eff_reactant;                 /* 3rd body efficiencies of reactants: not used */

  int n_products;     /* number of products */
  Material **mat_product;         /* species materials of products */
  Domain **domain_product;              /* domains of products */
  int *product;                   /* species indices of products */
  real *stoich_product;             /* stoichiometric coefficients of products */
  real *exp_product;              /* rate exponents of products : not used*/
  real *eff_product;                    /* 3rd body efficiencies of products: not used*/

  int n_others;                         /* no. of other species : not used */
  Material **mat_other;                 /* species materials of other species: not used */
  Domain **domain_other;                /*domains of other species: not used */
  int *other;                     /* species indices of other species: not used */
  real *exp_other;                  /* rate exponents of other species: not used */
  real *eff_other;                  /* 3rd body efficiencies of other species: not used */

  cxboolean arrh_data_read;             /* flag to identify successful data read */
  int arrh_phid_prev, arrh_spid_prev;   /* preceding reactant species */
  real arrh_a, arrh_e, arrh_b, arrh_tr; /* arrhenius rate constants */
  int arrh_ph;                          /* phase ID to select temperature */
  real arrh_tmin;                       /* minimum temperature to kick-off reaction */

  cxboolean diff_data_read;             /* flag to identify successful data read */
  int diff_ph_solid, diff_ph_gas;       /* phase id's for solid and gas */
  int diff_phid_prev, diff_spid_prev;   /* preceding reactant species */
  int diff_phid_ash, diff_spid_ash;     /* residue species */
  real diff_yash_i, diff_yb_i;          /* mass fractions of residue and bulk */
  real diff_c_kg, diff_mw_bath, diff_r_a_bath, diff_ek_a_bath; /* constants */
  real diff_area_bet, diff_denp;        /* BET area and char density */
  real diff_a, diff_e, diff_b, diff_tr; /* surface reaction rate constants */

  char udf_name[PROP_UDF_NAME_LENGTH];

  struct hetero_reaction_struct *next;    /* next reaction in list */


} Hetero_Reaction;

extern FLUENT_EXPORT Hetero_Reaction *Get_het_reaction_list(void);

typedef struct mass_transfer_struct
{

  struct domain_species_struct
  {
    Domain *domain;
    char species_name[MATERIAL_NAME_LENGTH];
    int species_id;
  } from;

  struct domain_species_struct to;

  Property p[1];

  struct mass_transfer_struct *next;
} Mass_Transfer_Function;

extern FLUENT_EXPORT Mass_Transfer_Function *mass_transfer_list;

typedef struct
{
  Property use_for_lump_post_proc   [MT_PROP_MAX];
  Property lump_det_vof_inside      [MT_PROP_MAX];
  Property max_Lump_Vof             [MT_PROP_MAX];
  Property lump_det_vof_lower_limit [MT_PROP_MAX];
  Property lump_max_vof_surface     [MT_PROP_MAX];
  Property mesh_coarsening          [MT_PROP_MAX];
  /*       dpm_to_vof_picle_conv_trn[MT_PROP_MAX]; */
  Property dpm_to_vof_vof_threshold [MT_PROP_MAX];
  Property dpm_to_vof_vof_thrsh_brkp[MT_PROP_MAX];
  Property dpm_to_vof_vof_thrsh_lwf [MT_PROP_MAX];
  Property dpm_to_vof_refine_mesh   [MT_PROP_MAX];
  Property dpm_to_vof_coarsen_mesh  [MT_PROP_MAX];
  Property dpm_to_vof_do_wall_film  [MT_PROP_MAX];
  Property dpm_to_vof_do_vof_to_lwf [MT_PROP_MAX];
  Property dpm_to_vof_lwf_hght_thrsh[MT_PROP_MAX];
  Property dpm_to_vof_lwf_vof_thrsh [MT_PROP_MAX];
  Property dpm_to_vof_VtL_vof_thrsh [MT_PROP_MAX];
} General_Model_Transition;

extern FLUENT_EXPORT General_Model_Transition general_model_transition;

/* Yes, following ("ab-") uses Mass_Transfer_Function, too..! */
extern FLUENT_EXPORT Mass_Transfer_Function *model_transition_list;
extern FLUENT_EXPORT int n_model_transition;

/* for evap-cond model*/
extern FLUENT_EXPORT void TPC_Mech_In_Phase_Pair(Domain *domain, int phase_i, int phase_j);
#define MT_PROPERTY(m) (m->p[0])


/*drag subsection*/
#define RE_NUMBER(ro,u,d,mu)((ro)*(u)*(d)/(mu))
#define DRAG_FUNCTION(Re)(((Re) < 1000)?(1+0.15*pow((Re),0.687)):0.018*(Re))
#define DRAG_RELAX_TIME(rho,d2,mu)((rho)*(d2)/(18.*(mu)))
/* end of drag subsection*/

typedef enum
{
  FILL_SURF_TENS_VARS_SURF_TENS,   /* the generic purpose to call this -- calculate surface tension */
  FILL_SURF_TENS_VARS_STAT_PILE,   /* special use of this function inside the DDPM static pile-up option */
  FILL_SURF_TENS_VARS_MAX_VALUES   /* special use of this function inside the DDPM static pile-up option */
} fill_surf_tens_vars_purpose_t;

/* declaration section, keep it alphabetic order */
FLUENT_EXPORT extern void
Calculate_Mass_Flux(Domain *domain),
                    Calculate_Heterogeneous_Reaction_Rates (Domain *domain),
                    Calc_Drag_Coeffs(Domain *domain),
                    Calculate_Mass_Transfer(Domain *domain),
                    Calc_MP_Latent_Heat(Domain *domain),
                    Calculate_Cavitation_Sources(Domain *domain),
                    Calc_Drag_Momentum_Coupled_Terms(Domain *domain),
                    Cavitation_Imbalance(Domain *domain, real *inlet_flux, Svar nv),
                    Cavitation_Phase_Source(Domain *domain),
                    Cavitation_P(Domain *domain ),
                    Collect_Node_Values_Wrapper(Domain *domain, Svar nv),
                    Cvt_Mass_Rate(Domain *domain),
                    Correct_Fluids_Velocities(Domain *domain),
                    coupled_vof(Domain *domain),
                    Coupled_VOF_Coeffs(Domain *domain),
                    vof_included_in_piso_corrector(Domain *domain, int iter_no),
                    Coupled_VOF_Damping_Source(Domain *domain),
                    Hybrid_RC_Blending_Factor(Domain *domain),
                    MP_Pseudo_Mom_Density_Smoothing(Domain *domain),
                    MP_Pseudo_False_Time_Step_Linearization(Domain *domain),
                    Scalar_Local_n_Global_minmax(Domain *domain, Svar sw, real *sw_min, real *sw_max),
                    Cvt_VOF_P_Source(Domain *domain, cxboolean update_vof_source, cxboolean update_p_source),
                    End_VOF_Interpolation(Domain *domain),
                    Fill_VOF_Value(cell_t c, Thread *mt),
                    Pressure_Fixed_Velocity_Sources_coupled_mp(Domain *domain),
                    Initialize_Primary_Phase(Domain *domain),
                    Init_Mfluid_Face_Vof(Domain *domain),
                    Initialize_VOF_Interpolation(Domain *domain),
                    Inter_Phase_Mass_Transfer(Domain *domain,
                                              cxboolean update_vof_source,
                                              cxboolean update_p_source),
                    Drift_Mom_Source(Domain *domain),
                    Drift_Pressure_Source(Domain *domain),
                    Drift_VOF_Source(Domain *domain),
                    Gpressure_Derivatives(Domain *subdomain),
                    Limit_Svar_To_Phase(Domain *domain, Svar sv),
                    Marangoni_Forces(Domain *domain),
                    Marangoni_Forces_Mfluid(Domain *domain),
                    Mark_Cylinder_Surface(Domain *domain, real xmin, real xmax, real ymin, real ymax,
                                          real zmin, real zmax, real rad),
                    Mark_Hex_Surface(Domain *domain, real xmin, real xmax, real ymin, real ymax,
                                     real zmin, real zmax),
                    Mark_Sphere_Surface(Domain *domain, real xcen, real ycen, real zcen, real rad),
                    MP_Correct_Outflow_Flux(Domain *domain, Svar nv),
                    MP_Dispersed_ke_mu_t(Thread *t, real const urf, cxboolean relax),
                    MP_Dispersed_les_mu_t(Thread *t, real const urf, cxboolean relax),
                    MP_Dispersed_Phase_Turb_Ap_S(Domain *domain, Svar sv_ap, Svar sv_sP, real mp_C3),
                    MP_Dispersed_Phase_Turb_S(Domain *domain, Svar sv_apP, Svar sv_sP, int eqnP_index, real mp_C3),
                    MP_Mixture_ke_mu_t(Thread *t),
                    MP_Fill_Mixture_Fields(Domain *domain),
                    MP_Init_Flux(Domain *domain),
                    MP_Mixture_Velocity_Derivatives(Domain *domain),
                    MP_Face_P_Effect_on_Velocity(Domain *domain, int direction),
                    MP_Face_P_Term(Domain *domain),
                    MP_OD_Fixed_Velocity_Coeffs(Domain *domain, int eqn),
                    MP_Sum_Outgoing_Flux(Domain *domain),
                    Calculate_Convective_CFL(Domain *domain),
                    Patch_VOF(Domain *domain, Svar nv, real value),
                    MP_Init_Local_Turbulent_Field(Domain *PTR_RESTRICT domain),
                    Phases_Interaction(Domain *domain),
                    Reset_Interface_Info(Domain *),
                    solve_coupled_phase_implicit(Domain *domain, Svar sv_vof, Svar sv_vof_m1,
                                                 Svar sv_vflux, cxboolean second_order, int phase),
                    Solve_ke_MP(Domain *domain),
                    Solve_ke_rst_MP(Domain *domain),
                    Solve_k_omega_MP(Domain *domain),
                    Solve_sgs_tke_MP(Domain *domain),
                    Solve_P_MP(Domain *domain),
                    Store_Interface_Info (cell_t c, Thread *mt),
                    Store_Vof_Res(Domain *domain, int turn,
                                  int phase),
                    MP_Update_Eqn_Face_Coeff(Domain *domain, real Pr_t),
                    MP_Update_MEqn_Face_Bvis(Domain *domain),
                    MP_Update_KE_Face_Coeff(Domain *domain, Svar sv_phi, real Pr_t),
                    MP_Update_Face_Gran_Conductivity(Domain *domain),
                    MPG_Init_P(Domain *domain, Var_Attribute *sv),
                    MPG_Init_dP(Domain *domain, Var_Attribute *sv),
                    set_f_vofs_from_bc(face_t f, Thread *t, Thread **pt, int n),
                    set_f_vofs_from_pr_bc(face_t f, Thread *t, Thread **pt, int n, cxboolean pinlet),
                    set_f_vofs_from_mfi_bc(face_t f, Thread *t, Thread **pt, int n),
                    mfi_bndr_vof(Thread *t, cxboolean update_mfi_phase_vflux),
                    i_bndr_vof(Thread *t),
                    p_bndr_vof(Thread *t, cxboolean pinlet),
                    Solve_Explicit_VOF(Domain *domain),
                    Solve_VOF(Domain *domain, int iter_num, cxboolean not_piso_vof),
                    Fill_Surface_Tension_Vars(Domain *mdomain, fill_surf_tens_vars_purpose_t purpose),
                    Fill_Surface_Tension_Force(Domain *mdomain),
                    Calculate_Surface_Tension_Force(Domain *domain, Svar sv_vof),
                    Add_Mfluid_Surface_Tension_Force(Domain *domain),
                    Add_Mixture_Surface_Tension_Force(Domain *domain),
                    Update_Expansion_Source(Domain *domain, Svar sv_source, cxboolean
                                            update_mp_inlet_flux),
                    Update_Diffusion_Source(Domain *domain, int phase, Svar sv_source),
                    Update_Bndr_Mixture_Enthalpy(Domain *domain),
                    Update_Cell_Mixture_Property(Domain *domain, Svar nv, Property_ID prop_id, cxboolean mass_av_mixing),
                    Update_Cell_Mixture_Radiative_Property(Domain *domain, Svar nv, Property_ID prop_id),
                    Update_Cell_Mixture_Refractive_Index(Domain *domain, Svar nv, Property_ID prop_id),
                    Update_Compressible_Phase_Face_Density(Domain *domain, cxboolean density_second_order_scheme),
                    Update_Face_Mixture_Density(Domain *domain),
                    Update_Face_Mixture_Viscosity(Domain *domain),
                    Update_Face_MP_Flux(Domain *PTR_RESTRICT domain),
                    Update_Face_Nut_Coeff(Domain *domain, real Pr),
                    Update_Fluid_Density(Domain *domain),
                    MP_Artificial_Interfacial_Viscosity(Domain *domain),
                    Update_Inlet_Vof(Domain *domain),
                    Update_Face_Vof_During_Init(Domain *domain),
                    update_pgrad_from_mp_pressure_corrections(Domain *domain),
                    update_pgrad_from_mp_velocity_corrections(Domain *domain),
                    Update_PhaseVelocities_and_Fluxes(Domain *domain),
                    Update_Primary_Cell_Vof(Domain *domain, cxboolean do_adjust_global_mass_p),
                    Scale_Cell_Vof(Domain *domain, cxboolean do_adjust_global_mass_p),
                    Update_Slip_Velocity(Domain *domain),
                    Update_Time_Vof(Domain *domain),
                    Update_VOF_Solution(Domain *domain),
                    Reset_VOF_Solution(Domain *domain),
                    Copy_Phase_Level_Scalar(Domain *domain, Svar sv_from, Svar sv_to, int choice),
                    print_VAP(Domain *, int),
                    Subtract_Reference_P_Prime(Domain *domain),
                    VEqn_Dispersed_Phase_Turbulent_Source(Domain *domain),
                    Vof_Derivatives_Alloc_And_Calc(Domain *subdomain),
                    Vof_Derivatives_Free(Domain *subdomain),
                    Zero_Solver_Vof_Values(Domain *domain),
#if 0
                    troshko_hassan_turbulence_sources(Domain *domain, Svar sv_phi, Svar sv_phi_ap, Svar sv_phi_s),
#else
                    troshko_hassan_turbulence_sources(Domain *domain, Svar sv_phi, Svar sv_phi_ap, Svar sv_phi_s, real mp_C3),
#endif
                    mp_sato_bit_viscosity(Domain *domain, real urf, cxboolean relax, cxboolean init_only),
                    boiling_inter_phase_heat_transfer(Domain *domain, Svar sv_phi, Svar sv_phi_ap, Svar sv_phi_s),
                    boiling_wall_heat_flux(face_t f, Thread *t, cell_t c0, Thread *t0, real cid[], real cir[], real Tiw),
                    boiling_wall_heat_flux_partition(face_t f, Thread *t, cell_t c0, Thread *t0, int thermal_bc),
                    MP_Add_SBM_Heat_Flux(face_t f, Thread *tf, cell_t c0, Thread *t0, real At, real Tiw, real cid[]),
                    VOF_Coupled_Post_Solution(Domain *domain),
                    Vof_Deriv_Accumulate(Thread *t, Svar sw, int ns, Svar gw, Svar rgw),
                    VOF_Slope_Wrapper(Domain *domain, Svar nv, Svar ng),
                    Calc_VOF_Slope_From_Node_Values(Domain *domain, Svar nv, Svar ng),
                    calc_VOF_slope_for_IAD(Domain *subdomain, Svar sv_vof, Svar sv_vof_g, Svar sv_vof_rg), /* GM */ /* US114041 */ /* Variable declaration for gradient calculations /storage in drag (AIAD) */
                    aiad_phase_tke_source(Domain *subdomain, Svar sv_phi_s), /* GM */ /* US114041 */ /* Subgrid wave turbulence (AIAD) */
                    aiad_mixture_tke_source(Domain *domain, Svar sv_phi_s) /* GM */
                    ;

FLUENT_EXPORT void get_linearized_qiw_boiling(face_t f, Thread *t, cell_t c0, Thread *t0,
                                              int thermal_bc, cxboolean boiling_flux_partition, cxboolean nlbf_on);
#if 0
FLUENT_EXPORT void get_wall_temperature_boiling(face_t f, Thread *t, cell_t c0, Thread *t0, int thermal_bc,
                                                real multiplier, real aic_coeff, real subcool,
                                                real Hv, real freq, real coeff_sphase_vap, real coeff_sphase_liq,
                                                real coeff_quench, real coeff_evap,
                                                real coeff_film, real f_thin_film);
#endif

FLUENT_EXPORT extern real
Get_Tabular_T_Given_P(MT_Tabular_Data *tabular_data, real p_abs),
                      Get_Tabular_L_Given_P(MT_Tabular_Data *tabular_data, real p_abs),
                      Get_Tabular_P_Given_T(MT_Tabular_Data *tabular_data, real T),
                      Get_Tabular_L_Given_T(MT_Tabular_Data *tabular_data, real T)
                      ;

FLUENT_EXPORT void Update_Cell_Mixture_Sound_Speed(Domain *domain);
FLUENT_EXPORT void Initialize_Mixture_Properties(Domain *);
FLUENT_EXPORT cxboolean MP_Phase_Granular_Material(int phase);
extern FLUENT_EXPORT cxboolean mp_generic_framework; /* generalized framework controlling flag */
extern FLUENT_EXPORT cxboolean mp_vof_diff_generic;
extern FLUENT_EXPORT cxboolean mp_vof_diff_generic_full;
extern FLUENT_EXPORT cxboolean mp_vof_diff_generic_mom;
FLUENT_EXPORT void Calc_Vof_Diff_Coeff_n_Flux(Domain *domain, cxboolean free_vof_grad);
FLUENT_EXPORT void MP_Save_Prev_Vof(Domain *domain);
FLUENT_EXPORT void Update_Phase_Diffusion_Expansion_Source(Domain *domain, Svar sv_source, cxboolean exchange_source);
FLUENT_EXPORT void Add_MP_Vof_Diff_Source(Domain *mdomain, Svar sv, Svar sv_ap, Svar sv_source, Delta_Form);
FLUENT_EXPORT void Calc_Phase_Vof_Gradients(Domain *subdomain, Svar sv, Svar sv_rg, Svar sv_g, cxboolean calc_deriv);
extern FLUENT_EXPORT cxboolean Surface_Tension_Present(Domain *domain);
FLUENT_EXPORT cxboolean Variable_Surface_Tension_Present(Domain *domain);
FLUENT_EXPORT void Store_MP_Flux_Sum(Domain *domain, int method, cxboolean variable_time);
FLUENT_EXPORT real DA_update_time_step(Domain *domain, real cfl, int method, int time_steps, int verbosity);
FLUENT_EXPORT real phase_time_step(Domain *domain, real cfl, int method, cxboolean include_dflux, int time_steps, int verbosity);
/* Pseudo Transient Method related changes  */
FLUENT_EXPORT void  Pseudo_Equation_Unsteady_Sources(Domain *domain, Svar sv_phi, Svar sv_ap, Svar sv_s, Svar sv_vof, Svar sv_vof_m1, real pseudo_time_step,
                                                     cxboolean dpm_block);
/* End Pseudo Transient Method related changes */

extern FLUENT_EXPORT cxboolean mp_gentop_on; /* GENTOP on flag */

extern FLUENT_EXPORT char
*MP_Model_Name(MP_Model i);
extern FLUENT_EXPORT cxboolean
Check_FluidSlideMesh(Domain *domain);

extern FLUENT_EXPORT real
c_rd(cell_t c0, Thread **pt0, int i),
     F_Drift_FLUX(face_t f, Thread *t, Thread *t0,
                  Thread **pt, Thread **pt0, int fluid),
     Total_Phase_Volume(Domain *), Total_Phase_Volume_Cav(Domain *, int);

FLUENT_EXPORT void MP_Turbulent_Drag_Time(real Cmu,
                                          real Pdensity,
                                          real k_drag,
                                          real C_vm,
                                          ND_VEC(real Pu, real Pv, real Pw),
                                          real Pk, real Pd, real Pmu_lam,
                                          real Sdensity,
                                          real Svof,
                                          ND_VEC(real Su, real Sv, real Sw),
                                          real Sdiam,
                                          real *tau_t,
                                          real *tau_d);

/*end of modified*/

/* for communication with sg_mom.c */
FLUENT_EXPORT void zero_init_3d_vector(Domain *domain, Var_Attribute *sv);

FLUENT_EXPORT void mpg_calculate_gp(Domain *domain);
FLUENT_EXPORT void mpg_calculate_dgp(Domain *domain);
FLUENT_EXPORT void mpg_calculate_face_gp(Domain *domain);
FLUENT_EXPORT void MP_Get_Reference_Densities(Domain *);

/* some utility functions */
FLUENT_EXPORT cxboolean Is_Primary_Phase_Domain(Domain *);
FLUENT_EXPORT cxboolean Is_Secondary_Phase_Domain(Domain *);
FLUENT_EXPORT cxboolean Is_Primary_Phase_Thread(Thread *);
FLUENT_EXPORT cxboolean Is_Secondary_Phase_Thread(Thread *);

/* end of declaration section */

FLUENT_EXPORT real Calc_Poutlet_Boundary_Pressure(face_t f, Thread *t);
FLUENT_EXPORT real Calc_Open_Channel_Inlet_Pressure(face_t f, Thread *t);
FLUENT_EXPORT real Calc_Open_Channel_Inlet_Static_Pressure(face_t f, Thread *t);
FLUENT_EXPORT real Calc_Open_Channel_Outlet_Pressure(face_t f, Thread *t);
FLUENT_EXPORT void Update_Open_Channel_Parameters(Domain *domain, cxboolean update_inputs, cxboolean update_fr, cxboolean force_update);
FLUENT_EXPORT real Calc_Channel_Surface_Fraction_Fixed(face_t f, Thread *mt, Thread *t);
FLUENT_EXPORT real Calc_Channel_Surface_Fraction(face_t f, Thread *t, real ht_local);
FLUENT_EXPORT void set_channel_f_vofs_from_cells(face_t f, cell_t c0, Thread **pt,
                                                 Thread **pt0, int n);
FLUENT_EXPORT void Update_oc_bndr_Vof(Domain *domain, cxboolean channel_flow_downstream);
extern FLUENT_EXPORT unsigned int open_channel_init_thread_id;
FLUENT_EXPORT void F_vi_ocw_Averaged_Velocity_Profiles(real NV_VEC(U), real NV_VEC(fl_avg), real NV_VEC(u_current), face_t f, Thread *t);
FLUENT_EXPORT void Set_Open_Channel_Wave_Parameters(Domain *d);
FLUENT_EXPORT void update_wave_inlet_vof(Thread *t);
FLUENT_EXPORT void patch_open_channel_variables(Domain *domain);
FLUENT_EXPORT void Turbulence_Damping_Sources(Domain *domain, Svar sv_phi_s, Svar sv_phi);
FLUENT_EXPORT void Open_Channel_Wave_Analysis(Domain *domain);
FLUENT_EXPORT void Open_Channel_Wave_Analytical_Profiles(Domain *domain, int thread_id, real time);
FLUENT_EXPORT void Open_Channel_Wave_Ht_vs_Time(Domain *domain, int thread_id, real x, real y, real z);
FLUENT_EXPORT void Set_Numerical_Beach_Parameters(Thread *t);
FLUENT_EXPORT void Numerical_Beach_Wave_Damping_Source(Domain *domain);
FLUENT_EXPORT void Get_Beach_Input_Parameters(Domain *domain, int id,
                                              real *fs, real *bl, real *c_lin, real *c_quad,
                                              real *len, real *xs, real *xe, real NV_VEC(fl),
                                              real NV_VEC(fl2), real *xe2, real *len2,
                                              real NV_VEC(fl3), real *xe3, real *len3);

FLUENT_EXPORT void pb_het_mt(cell_t c, Thread *t,
                             Hetero_Reaction *r,
                             real **mw,
                             real **yi,
                             real *rr, real *rr_t,
                             int pb_domain_id, cxboolean sg_pb_qmom,
                             cxboolean sg_pb_smm, int n_bins,
                             int n_pb_qmom, real ka,
                             cxboolean *phenomenon1);


FLUENT_EXPORT void arrh_het_rate(cell_t c, Thread *t, Hetero_Reaction *r,
                                 real **mw, real **yi,
                                 real *rr, real *rr_t);
FLUENT_EXPORT void diff_het_rate(cell_t c, Thread *t,
                                 Hetero_Reaction *r,
                                 real **mw, real **yi,
                                 real *rr, real *rr_t);

/*Eulerian model*/
#define MP_PINLET_SET_V 0
#define MP_TEST 0
#define MP_VOLUME_VOF 0
#define MP_ZERO_AP 0
#define MP_ZERO_AP_FIX_VEL 1
#define MP_ZERO_AP_NO_INTERVEN 0
#define MP_VOF_KE_INTERACT 1
/* #define MP_CVM 0.5 */

extern FLUENT_EXPORT void Save_Prev_Flux(Domain *domain);
/*end of Eulerian model*/

/*cavitation model*/
#define CAVVOF 0    /* 1 -- vof eqn.;  0 -- mass-fraction eqn. */
#define CAVITATION_IN_P 1  /*flag for inclusion cavitation source */
/*in pressure equation*/

/*end of cavitation model*/

/*Multi_phase PISO*/
extern FLUENT_EXPORT void Solve_MP_PISO(Domain *domain, real *Avalue, cxboolean add_mass_source_error);
extern FLUENT_EXPORT void outflow_flux_mp_piso(Thread *t);
extern FLUENT_EXPORT void pboundary_flux_mp_piso(Thread *t);
extern FLUENT_EXPORT void interior_flux_mp_piso(Thread *t);
extern FLUENT_EXPORT void periodic_flux_mp_piso(Thread *t);
extern FLUENT_EXPORT void outflow_flux_mp_piso_nf(Thread *t);
extern FLUENT_EXPORT void pboundary_flux_mp_piso_nf(Thread *t);
extern FLUENT_EXPORT void interior_flux_mp_piso_nf(Thread *t);
extern FLUENT_EXPORT void periodic_flux_mp_piso_nf(Thread *t);
extern FLUENT_EXPORT void update_mp_P_S(Domain *domain, cxboolean add_mass_source_error);
extern FLUENT_EXPORT void correct_piso_mp_v(Domain *domain);
extern FLUENT_EXPORT void c_pp_coeff_prdc_piso(cell_t c, Thread *t, face_t f, Thread *t_f,
                                               real (*V_coeff)[MAX_PHASES]);
extern FLUENT_EXPORT void c_pp_coeff_piso(cell_t c, Thread *t, face_t f, Thread *t_f,
                                          real (*V_coeff)[MAX_PHASES]);
extern FLUENT_EXPORT void intr_fpp_piso(Thread *t, int coupled_ps);
extern FLUENT_EXPORT void prdc_fpp_piso(Thread *t, int coupled_ps);
extern FLUENT_EXPORT void bndr_fpp_piso(Thread *t);
extern FLUENT_EXPORT void p_bndr_fpp_piso(Thread *t);
extern FLUENT_EXPORT void mp_calculate_face_pressure_correction_piso(Domain *domain, int coupled_ps);
extern FLUENT_EXPORT void add_piso_mp_vp(Domain *domain);
extern FLUENT_EXPORT void calculate_MP_SAVP(Domain *domain, real *Avalue);
extern FLUENT_EXPORT void calc_inverse_ap(Domain *domain);
extern FLUENT_EXPORT void calculate_mp_vp_correction(Domain *domain, cxboolean not_first, int coupled_ps
                                                     , int scheme_ps);
extern FLUENT_EXPORT void recalculate_pp_coeff_piso(Domain *PTR_RESTRICT domain, AMG_System_Type sys_id);
extern FLUENT_EXPORT void update_primary_face_vof(Domain *domain);

extern FLUENT_EXPORT real omega_pp;/* skew correction*/
extern FLUENT_EXPORT cxboolean skew_mp_ps;

/*end of Multi_phase PISO*/

extern FLUENT_EXPORT void alloc_mp_drag_coeff(Domain *domain);
extern FLUENT_EXPORT void free_mp_drag_coeff(Domain *domain);

/* new framework related functions */
extern FLUENT_EXPORT void Add_Lift_Force_Source_New_Framework(Domain *PTR_RESTRICT domain);
extern FLUENT_EXPORT void Add_Wall_Lubrication_Force_Source_New_Framework(Domain *PTR_RESTRICT domain);

#include "granular.h"

/*define velocity locations*/
#define W_U_MP(i)  (1+(i))
#define jj_index(i,l) (1+(i)+(l)*mp_n)
#define W_V_MP(i)  (mp_n+(i)+1)
#if RP_3D
#define W_W_MP(i) (2*mp_n+(i)+1)
#define W_VOF_MP(i) (!n_phase_solver? ( p_vof_coupled? ((i)) : (3*mp_n+(i))) :(p_vof_coupled? ((i)+1) : (3*mp_n+(i)+1)))

#else
#define W_W_MP(i)  (mp_n+(i)+1)
#define W_VOF_MP(i) (!n_phase_solver? ( p_vof_coupled? ((i)) : (2*mp_n+(i))) : \
( p_vof_coupled ? ((i+1)) : (2*mp_n+(i)+1)))
#endif

/* define vof locations for COUPLED_VOF */
#define W_VOF(i) (!n_phase_solver? (ND_ND+(i)) : (ND_ND+(i)+1))

#define W_VEL_INDEX_MP(_eqn_index,_phase_index) (mp_n * (_eqn_index - W_U) + W_U + _phase_index)

FLUENT_EXPORT void save_old_vof(Domain *domain);

#define C_MASS_TRANSFER(c,t,i)C_STORAGE_R_XV(c,t,SV_MASS_TRANSFER,i)
#define C_WALL_MASS_TRANSFER(c,t,i)C_STORAGE_R_XV(c,t,SV_WALL_MASS_TRANSFER,i)

#define C_PBM_RPI_MT(c,t,i)C_STORAGE_R_XV(c,t,SV_PBM_RPI_MT,i)

FLUENT_EXPORT real Get_Tp_At_Given_Ystar_Alt1(real Pr, real ystar_far, real yplus, real Tw, real Tc);
FLUENT_EXPORT real Get_Ystar_At_Given_Yp(real rho, real mu, real u_ke, real yp);

#define C_MP_MT_KL(c,t,i)FAST_C_STORAGE_R_XV(c,t,SV_MP_MT_KL,i)
#endif /* _FLUENT_SG_MPHASE_H */
