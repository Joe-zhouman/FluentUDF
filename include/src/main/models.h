/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_MODELS_H
#define _FLUENT_MODELS_H

#include "dll.h"
#include "amg.h"
#include "turb_global_var.h"

extern FLUENT_EXPORT cxboolean rp_seg;
extern FLUENT_EXPORT cxboolean rp_amg;


typedef enum
{
  NU_T_MODEL_NONE = FALSE,
  NU_T_MODEL_SPALART_ALLMARAS,
  NU_T_MODEL_KE1E,
  NU_T_MODEL_NUMBER
} Nu_t_Model_Type;

extern FLUENT_EXPORT Nu_t_Model_Type rp_sa_nut;   /* One-eq. models: 1 for Spal.-All., 2 for KE1E -- should be renamed to:  rp_nut */

extern FLUENT_EXPORT cxboolean rf_energy;      /* TRUE if any energy/temperature eqn in on */
extern FLUENT_EXPORT cxboolean sg_temperature; /* TRUE if temperature eqn is on */
extern FLUENT_EXPORT cxboolean sg_enthalpy;    /* TRUE if enthalpy eqn is on */
extern FLUENT_EXPORT cxboolean rp_energy;      /* TRUE if total energy eqn is on */
extern FLUENT_EXPORT cxboolean sg_dpm;
extern FLUENT_EXPORT cxboolean sg_mesh_interpolate_in_time;

extern FLUENT_EXPORT cxboolean DPM_tke_coupling;  /* TRUE if two-way turbulence coupling is on */
extern FLUENT_EXPORT cxboolean M_wall_film;       /* TRUE if the wall film model is on */
extern FLUENT_EXPORT cxboolean M_dpm_wall_heat_exchange; /* for particle wall heat exchange on reflect */
extern FLUENT_EXPORT cxboolean M_wall_film_stripping; /* for lagrangian wall film model with stripping */
extern FLUENT_EXPORT cxboolean compute_localresidual_p;
extern FLUENT_EXPORT cxboolean compute_new_continuity_residual_p;
extern FLUENT_EXPORT int       locally_scaled_residual_method;
extern FLUENT_EXPORT cxboolean cache_residuals_p;
#if RP_NETWORK
extern FLUENT_EXPORT cxboolean sg_network;
#endif
#if RP_PCB
extern FLUENT_EXPORT cxboolean sg_pcb;
#endif
extern FLUENT_EXPORT cxboolean sg_pb ;    /* TRUE if population balance model is on */
extern FLUENT_EXPORT cxboolean sg_iac;          /* TRUE if interfacial area model is on */
extern FLUENT_EXPORT cxboolean sg_lsf;           /* TRUE if level-set model is on */
extern FLUENT_EXPORT cxboolean sg_crev;         /* crevice model */
extern FLUENT_EXPORT cxboolean sg_dtrm;
extern FLUENT_EXPORT cxboolean sg_p1;
extern FLUENT_EXPORT cxboolean rp_sootspecies;
extern FLUENT_EXPORT cxboolean sg_twotemp;   /* two-temperature thermal non-equilibrium model */
extern FLUENT_EXPORT cxboolean sg_rosseland;
extern FLUENT_EXPORT cxboolean lowp_slip;
extern FLUENT_EXPORT cxboolean por_vel_form;
extern FLUENT_EXPORT real time_factor;
#if RP_2D
extern FLUENT_EXPORT cxboolean sg_swirl;
#endif

extern FLUENT_EXPORT cxboolean rp_axi_swirl;    /* (rp_axi && (sg_swirl || rp_turb)) */


extern FLUENT_EXPORT cxboolean sg_cylindrical;
extern FLUENT_EXPORT cxboolean sg_pdf;
extern FLUENT_EXPORT cxboolean sg_premixed;
extern FLUENT_EXPORT cxboolean sg_par_premix;
extern FLUENT_EXPORT cxboolean sg_pdf_transport;
extern FLUENT_EXPORT cxboolean sg_dqmom_iem ;
extern FLUENT_EXPORT int dqmom_nmodes ;
extern FLUENT_EXPORT cxboolean sg_spark;          /* spark model */
extern FLUENT_EXPORT cxboolean sg_ignite;         /* Autoignition model */
extern FLUENT_EXPORT cxboolean sg_ecfm;           /* ECFM model */
extern FLUENT_EXPORT cxboolean sg_geqn;           /* g equation model */
extern FLUENT_EXPORT cxboolean sg_inert;          /* inert (EGR) model */
extern FLUENT_EXPORT cxboolean sg_melt;
extern FLUENT_EXPORT cxboolean sg_pull;
extern FLUENT_EXPORT cxboolean sg_dynmesh;
#if RP_OVERSET
extern FLUENT_EXPORT cxboolean sg_overset;
#endif
extern FLUENT_EXPORT cxboolean sg_nox;
extern FLUENT_EXPORT cxboolean sg_sox;
extern FLUENT_EXPORT cxboolean sg_soot;
extern FLUENT_EXPORT cxboolean sg_soot_mom;
extern FLUENT_EXPORT cxboolean sg_soot_mech;
extern FLUENT_EXPORT cxboolean sg_soot_mom_agg;
extern FLUENT_EXPORT cxboolean sg_tss_scalar;
extern FLUENT_EXPORT int tss_num_scalars;
extern FLUENT_EXPORT cxboolean sg_hg;
extern FLUENT_EXPORT cxboolean if_pb_qmom(void);
extern FLUENT_EXPORT int new_inf;
extern FLUENT_EXPORT int sg_disco;
extern FLUENT_EXPORT int  comet_iter_count;
extern FLUENT_EXPORT int n_bands_disco;
extern FLUENT_EXPORT int sg_bee_gees; /* what else to call a gray band disco model ? */
extern FLUENT_EXPORT int sg_multi_band_rad;
extern FLUENT_EXPORT cxboolean doCoupling_eqn;
extern FLUENT_EXPORT cxboolean sg_vfr;
extern FLUENT_EXPORT cxboolean sg_s2s;
extern FLUENT_EXPORT cxboolean sg_montecarlo;
extern FLUENT_EXPORT cxboolean sg_solar;
extern FLUENT_EXPORT cxboolean p_v_coupled_available;
extern FLUENT_EXPORT cxboolean p_vof_coupled;
extern FLUENT_EXPORT cxboolean momentum_delta_form;
extern FLUENT_EXPORT cxboolean delta_form_post_discretization;
extern FLUENT_EXPORT cxboolean MP_COUP_or_P_VOF;
extern FLUENT_EXPORT cxboolean mp_face_p_effect;
extern FLUENT_EXPORT int p_vof_option;
extern FLUENT_EXPORT int recalculate_p_coeff;
extern FLUENT_EXPORT int piso_neighbor_option;
extern FLUENT_EXPORT int neighbor_add_option;
extern FLUENT_EXPORT int number_of_correctors;
extern FLUENT_EXPORT cxboolean mp_nita_force_expl;
extern FLUENT_EXPORT cxboolean bf_includes_axi_visc_term;
extern FLUENT_EXPORT int N_soot_mom;
extern FLUENT_EXPORT int N_soot_mom_agg;
extern FLUENT_EXPORT cxboolean need_amg;
extern FLUENT_EXPORT cxboolean need_face_flux;
extern FLUENT_EXPORT cxboolean need_mass_imbal;
extern FLUENT_EXPORT cxboolean mp_pcor_coef_sym;

extern FLUENT_EXPORT cxboolean rp_dpm_cache; /* parallel DPM mpdel */

extern FLUENT_EXPORT cxboolean rp_unsteady; /* unsteady: global time or dual time */
extern FLUENT_EXPORT cxboolean sg_noniterative;
extern FLUENT_EXPORT cxboolean sg_mp_noniterative; /*Eulerian multi-phase noniterative solver */
extern FLUENT_EXPORT cxboolean mp_fractstep;
extern FLUENT_EXPORT cxboolean vof_piso_corrector; /*Eulerian multi-phase piso solver */
/*extern FLUENT_EXPORT cxboolean piso_corrector_just_due_to_vof; *//*Eulerian multi-phase piso solver */
extern FLUENT_EXPORT cxboolean sg_mp_piso; /*Eulerian multi-phase piso solver */
extern FLUENT_EXPORT cxboolean mp_piso;
extern FLUENT_EXPORT cxboolean body_force_dissipation; /* Add Body Force Dissipation to Rhie_CHOW Euleran MP */
extern FLUENT_EXPORT cxboolean need_explicit_urf;
extern FLUENT_EXPORT cxboolean need_implicit_urf;
#if USE_FEMCORE
extern FLUENT_EXPORT cxboolean rp_fem_core;
#endif
extern FLUENT_EXPORT cxboolean rp_perforated;

typedef enum
{
  FINITE_DIFFERENCE,
  FINITE_VOLUME
} Temporal_Discretizations;

typedef enum
{
  NO_PREDICTOR,
  DO_PREDICTION,
  CORRECT_PREDICTION
} Predvar;
extern FLUENT_EXPORT Predvar  predictor_option;
extern FLUENT_EXPORT Temporal_Discretizations Temporal_Discretization;


extern FLUENT_EXPORT int n_time_levels;
extern FLUENT_EXPORT int rp_dual_time;
extern FLUENT_EXPORT cxboolean rp_global_time;
extern FLUENT_EXPORT cxboolean sg_time_second_order;
extern FLUENT_EXPORT cxboolean db_time_first_order; /* dbns time scheme control for mesh changes */
extern FLUENT_EXPORT int number_of_samples;
extern FLUENT_EXPORT real delta_time_sampled;
extern FLUENT_EXPORT real delta_time_sampled_shear;
extern FLUENT_EXPORT real delta_time_sampled_heat_flux;
extern FLUENT_EXPORT real delta_time_sampled_wall;
extern FLUENT_EXPORT real delta_time_sampled_force;
extern FLUENT_EXPORT real delta_time_sampled_non_premix;
extern FLUENT_EXPORT real delta_time_sampled_premix;
extern FLUENT_EXPORT real *delta_time_sampled_species;
extern FLUENT_EXPORT real delta_time_sampled_cff;
extern FLUENT_EXPORT real delta_time_sampled_dpm;
extern FLUENT_EXPORT real delta_time_sampled_dpm_volfrac;
extern FLUENT_EXPORT real delta_time_sampled_scr_urea_depo_risk;
extern FLUENT_EXPORT real delta_time_sampled_datasets;
extern FLUENT_EXPORT cxboolean cn_time_scheme;
extern FLUENT_EXPORT int time_step_old_0;
extern FLUENT_EXPORT int time_step_old_1;
extern FLUENT_EXPORT cxboolean tvd_time_bounded_second_order;
extern FLUENT_EXPORT cxboolean primitive_time_bounded_second_order;
extern FLUENT_EXPORT cxboolean so_time_primitive_var_alt_form;
extern FLUENT_EXPORT cxboolean so_time_conservative_var_bnd;

extern FLUENT_EXPORT cxboolean rp_spe;   /* species transport model flag */
extern FLUENT_EXPORT cxboolean rp_react; /* species reaction model flag */
extern FLUENT_EXPORT cxboolean rp_spe_surf;   /* surface reaction model flag */
extern FLUENT_EXPORT cxboolean rp_spe_part;   /* combusting particle surface reaction model flag */
extern FLUENT_EXPORT cxboolean rp_potential;
extern FLUENT_EXPORT cxboolean rp_lithium;
extern FLUENT_EXPORT cxboolean rp_electrolysis;
extern FLUENT_EXPORT cxboolean rp_dual_potential;
extern FLUENT_EXPORT cxboolean rp_electro_chem;
extern FLUENT_EXPORT cxboolean rp_spe_surf_rc;
extern FLUENT_EXPORT cxboolean rp_absorbing_media; /* participating porous media flag */
extern FLUENT_EXPORT int n_spe;        /* number of species composing the fluid */
extern FLUENT_EXPORT int n_spe_surf;   /* number of surface species  */
extern FLUENT_EXPORT int n_spe_site;   /* number of site species  */
extern FLUENT_EXPORT int max_n_spe;
extern FLUENT_EXPORT int max_n_soot;
extern FLUENT_EXPORT cxboolean M_species;
extern FLUENT_EXPORT int n_ufla_probs;
extern FLUENT_EXPORT int dufl_numfla;

extern FLUENT_EXPORT cxboolean M_thickened_flame; /* Thickened Flame model */
extern FLUENT_EXPORT cxboolean M_reactor_net; /* Stirred reactor network model */

extern FLUENT_EXPORT int M_sp_vfc; /* single phase volume flux continuity */
extern FLUENT_EXPORT int iphase_compr;   /* index (id) of compressible phase  */
extern FLUENT_EXPORT int iphase_compr_np[MAX_PHASES];
extern FLUENT_EXPORT int is_phase_compr_np[MAX_PHASES];
extern FLUENT_EXPORT int num_compr_ph;

extern FLUENT_EXPORT int iphase_compr_np_real[MAX_PHASES];
extern FLUENT_EXPORT int is_phase_compr_np_real[MAX_PHASES];
extern FLUENT_EXPORT int num_compr_ph_real;

extern FLUENT_EXPORT cxboolean sg_uds;    /* user defined scalars model flag */
extern FLUENT_EXPORT int n_uds;         /* number of user defined scalars */
extern FLUENT_EXPORT cxboolean sg_udm;      /* user defined memory location flag */
extern FLUENT_EXPORT cxboolean sg_node_udm; /* user defined node memory location flag */
extern FLUENT_EXPORT int n_udm;         /* number of user defined memory locations */
extern FLUENT_EXPORT int n_node_udm;  /* number of user defined node memory locations */
extern FLUENT_EXPORT cxboolean sg_addon;   /* udf addon module flag (Electric/Magnetic modules for now) */
extern FLUENT_EXPORT int sg_addon_loaded;  /* loaded udf addon module index */

extern FLUENT_EXPORT cxboolean hyb_init;    /* hybrid initialization flag */

extern FLUENT_EXPORT cxboolean sg_wetsteam;          /* Wet Steam model */
extern FLUENT_EXPORT cxboolean sg_moistair;          /* Wet Steam model */

#define N_UDS  n_uds   /* this to suggest also that this is a constant */
#define N_UDM  n_udm   /* idem */
#define N_NODE_UDM  n_node_udm

extern FLUENT_EXPORT int n_pollut_nox;    /* number of nox pollutants defined */
extern FLUENT_EXPORT int n_pollut_sox;    /* number of sox pollutants defined */
extern FLUENT_EXPORT int n_pollut_soot;   /* number of soot pollutants defined */
extern FLUENT_EXPORT int n_pollut_hg;     /* number of mercury pollutants defined */

extern FLUENT_EXPORT int rp_structure_time; /* structural time integration scheme */
extern FLUENT_EXPORT int rp_structure_damping; /* structural damping scheme */

/* modeling constants */
extern FLUENT_EXPORT real M_max_wall_dist;
extern FLUENT_EXPORT real M_species_sct;
extern FLUENT_EXPORT real M_sootspecies_sct;
extern FLUENT_EXPORT real M_cdvar;
extern FLUENT_EXPORT real M_cgvar;
extern FLUENT_EXPORT cxboolean M_premixed_adiabatic;
extern FLUENT_EXPORT real M_PRMX_Cd;
extern FLUENT_EXPORT real M_PRMX_A;
extern FLUENT_EXPORT real M_PRMX_Mu;
extern FLUENT_EXPORT int M_pollut_turbulent_mode;
extern FLUENT_EXPORT real M_peters_coeff_b1;
extern FLUENT_EXPORT real M_peters_coeff_b3;
extern FLUENT_EXPORT real M_peters_coeff_cs;
extern FLUENT_EXPORT real M_ewald_exponent_q;
extern FLUENT_EXPORT real M_wall_damping_const;

extern FLUENT_EXPORT cxboolean M_update_derivatives_after_flow_solve;
extern FLUENT_EXPORT cxboolean M_update_derivatives_after_turb_solve;
extern FLUENT_EXPORT cxboolean M_update_derivatives_before_turb_solve;
extern FLUENT_EXPORT cxboolean M_boussinesq;
extern FLUENT_EXPORT cxboolean M_compressible;
extern FLUENT_EXPORT cxboolean M_roe;
extern FLUENT_EXPORT cxboolean M_pdf_compressible;
extern FLUENT_EXPORT cxboolean M_pdf_real_gas;
extern FLUENT_EXPORT cxboolean M_vapor_phase;

extern FLUENT_EXPORT cxboolean M_compressible_liquid;
extern FLUENT_EXPORT cxboolean M_drhodp_defined;
extern FLUENT_EXPORT cxboolean M_conservative_energy;
extern FLUENT_EXPORT cxboolean M_viscous_dissipation;
extern FLUENT_EXPORT cxboolean M_pressure_work;
extern FLUENT_EXPORT cxboolean M_kinetic_energy;
extern FLUENT_EXPORT cxboolean M_inertial_force;
extern FLUENT_EXPORT cxboolean M_inertial_force_work;
extern FLUENT_EXPORT cxboolean M_spe_thermal_j;
extern FLUENT_EXPORT int M_edc;
extern FLUENT_EXPORT int M_relax_chem_equil;
extern FLUENT_EXPORT int M_stiff_chem;
extern FLUENT_EXPORT int M_multiphase_stiff_chem[MAX_PHASES];
extern FLUENT_EXPORT cxboolean M_multiphase_stiff_chem_init;
extern FLUENT_EXPORT int M_hetero_stiff_chem;
extern FLUENT_EXPORT int M_stiff_dqmom ;
extern FLUENT_EXPORT cxboolean dqmom_iem_energy ;
extern FLUENT_EXPORT cxboolean sg_dqmom_enthalpy ;
extern FLUENT_EXPORT real M_gravity[ND_ND];
extern FLUENT_EXPORT cxboolean M_gravity_p;
extern FLUENT_EXPORT cxboolean M_par_premix_local_unburnt_props;

extern FLUENT_EXPORT cxboolean approximate_wall_temperature_p;
extern FLUENT_EXPORT real SIGMA_SBC;

extern FLUENT_EXPORT cxboolean M_icepak;
extern FLUENT_EXPORT cxboolean M_ffc;
extern FLUENT_EXPORT cxboolean M_reacting_channel_model;

/* extern FLUENT_EXPORT cxboolean M_elec_mag;   2005-09-27 uhb */
extern FLUENT_EXPORT cxboolean M_electric_conductivity;
extern FLUENT_EXPORT cxboolean M_electric_conductivity_only_const;
extern FLUENT_EXPORT cxboolean M_magnetic_permeability;
extern FLUENT_EXPORT cxboolean M_charge_density;

extern FLUENT_EXPORT cxboolean M_erosion_accretion;
extern FLUENT_EXPORT cxboolean save_residuals;     /* rpvar residuals/debug? */
extern FLUENT_EXPORT cxboolean save_cell_residuals; /* rpvar save-cell-residuals? */
extern FLUENT_EXPORT cxboolean M_abs_frame;
extern FLUENT_EXPORT cxboolean M_rframe_origin_abs;
extern FLUENT_EXPORT cxboolean M_fixed_vel_zero_p;

/* LES subgrid-scale model constants */
extern FLUENT_EXPORT real les_const;
extern FLUENT_EXPORT real les_sgske_Prt;
extern FLUENT_EXPORT real les_sgske_Ceps;

extern FLUENT_EXPORT real    op_pres;              /* operating pressure */
extern FLUENT_EXPORT real    pdf_compress_op_pres;
extern FLUENT_EXPORT Thread *pressure_ref_thread;  /* pressure reference thread location */
extern FLUENT_EXPORT cell_t  pressure_ref_cell;    /* pressure reference cell location   */
extern FLUENT_EXPORT int pressure_ref_rank;        /* pressure reference rank id   */

extern FLUENT_EXPORT real op_temp;  /* operating temperature */
extern FLUENT_EXPORT real op_dens;  /* operating density (rpvar)  */
extern FLUENT_EXPORT real reference_density; /* computed value (or rpvar) */

extern FLUENT_EXPORT cxboolean M_pdf_unsteady_flamelet;
extern FLUENT_EXPORT cxboolean M_ufla;
extern FLUENT_EXPORT cxboolean melt_method_lever;
extern FLUENT_EXPORT cxboolean Unity_Le_Use_K;
extern FLUENT_EXPORT cxboolean Pollut_Unity_Le_Use_K;

/* Solution based Poor Mesh Numerics Controls */
extern FLUENT_EXPORT cxboolean solution_based_pmn;
typedef struct solution_based_pmn_struct
{
  cxboolean mark_primary_limits;
  cxboolean mark_temp_limit;
  cxboolean mark_p_limit;
  cxboolean mark_mut_limit;
  cxboolean mark_vel_limit;
  cxboolean mark_cfl_limit;
  cxboolean mark_cfl_jump;
  cxboolean mark_once_per_dt;
  cxboolean mp_compress[MAX_PHASES];
  real vel_limit;
  real cfl_limit;
  real cfl_jump;
  real offset;
  real Pmin;
  real Pmax;
  real Tmin;
  real Tmax;
  real Mut_r_max;
} Solution_Based_PMN;

extern FLUENT_EXPORT Solution_Based_PMN pmn_solution;

typedef enum
{
  INQ_EQN_SOLVE,
  INQ_EQN_SCHEME,
  INQ_EQN_RELAX,
  INQ_EQN_MG,
  INQ_EQN_SOURCE,
  INQ_EQN_INIT,
  INQ_EQN_FIXED,
  INQ_EQN_NITA_CONTROLS,
  INQ_EQN_NITA_RELAX,
  INQ_EQN_EXTRAPOLATE,
  INQ_EQN_PSEUDO,
  INQ_EQN_PSEUDO_EXPERT,
  INQ_EQN_SYMMETRIC,
  INQ_EQN_DUALTS,
  INQ_EQN_DUALTS_EXPERT,
  INQ_EQN_DUALTS_IMPLICIT_RELAX
} Inq_Eqn_Selector;

/*Hybrid initialization related*/
typedef enum
{
  INLET_OUTLET_BOTH = 0,
  INLET_ONLY,
  OUTLET_ONLY,
  NO_INLET_NO_OUTLET,
  PRESS1_PRESS2_BOTH,
  PFAR_ONLY,
  MORE_THEN_ONE_PFAR
} case_topology_type;

extern FLUENT_EXPORT case_topology_type case_topology_pfi;

typedef struct weight_struct
{
  char use;
  double weight;
  double weight_max;
  real scale;
  char user_defined;
  real user_value;
} weight_t;

typedef struct model_description_struct
{
  /* storage description */
  Var_Attribute *sv_def;
  int n_sv_def;
  void (*sv_adjust_master_flags)(void);

  /* Inquire_Equations() methods */
  void (*inquire_equations)(Domain *, Inq_Eqn_Selector, Pointer *);

  /* Models_Changed() methods */
  void (*models_changed_download)(void);
  void (*models_changed_update)(void);

  /* Solver_Update() methods */
  void (*update_pre)(Domain *);
  void (*update_solve)(Domain *);
  void (*update_post)(Domain *);
  void (*update_boundary)(Domain *);
  void (*update_time)(Domain *);

  /* Get_Weights methods */
  /* return 0 - no weight for this model, 1 - has weight */
  /* only set those non-parent cell/face weight */
  int (*cell_weight)(Domain *);
  int (*face_weight)(Domain *);

  /**
   * Bookkeeping of Objp's
   * The ones listed here will be deleted
   * on case reread, which is what one
   * most probably wants anyway.
   */
  Objp ***objps;
  int  nobjps;

  char name[256];
  int timer_count;
  double timer_seconds;
  double cpu_time;
  int timer_count_sub;
  double timer_seconds_sub;
  weight_t weight;
} Model_Description;

FLUENT_EXPORT Model_Description *New_Model_Description(void);
FLUENT_EXPORT void Register_Model(Model_Description *, char *);
FLUENT_EXPORT void Print_Model_Names(void);
FLUENT_EXPORT void Reset_Model_Timers(void);
FLUENT_EXPORT void Print_Model_Timers(int mpid);
FLUENT_EXPORT void Models_Send_adjust_master_flags(void);
FLUENT_EXPORT void Models_Send_update_boundary(Domain *domain);
FLUENT_EXPORT void Models_Send_update_pre(Domain *domain);
FLUENT_EXPORT void Models_Send_update_solve(Domain *domain);
FLUENT_EXPORT void Models_Send_update_physical_time(Domain *domain);
FLUENT_EXPORT int Record_Model_Time(double t, char *name, int sub);
FLUENT_EXPORT void Models_Send_update_post(Domain *domain);
FLUENT_EXPORT void Init_Solver_Modules(void);
FLUENT_EXPORT void Register_Model_Objps(Model_Description *md, Objp ***objps, int nobjps);
FLUENT_EXPORT void Reset_Model_Objps(void);

FLUENT_EXPORT void Set_Storage_Need_Update(Domain *domain, cxboolean update);

FLUENT_EXPORT Pointer lrpconfig(Pointer x);

FLUENT_EXPORT void Inquire_PV_Options(Domain *, Pointer *);
FLUENT_EXPORT Pointer Inquire_Equations(Domain *, const char *property);
FLUENT_EXPORT int Pick_Equation(const char *label);

FLUENT_EXPORT void Set_RP_Unsteady(cxboolean val);

FLUENT_EXPORT cxboolean Materials_Require_Model_Change(Domain *);
FLUENT_EXPORT cxboolean Materials_Have_Udf_For_Initialization(Domain *);
FLUENT_EXPORT void Check_And_Fix_ELES_Zone_Settings(Thread *);
FLUENT_EXPORT void Check_And_Fix_RANS_LES_Interface_Settings(Thread *);
FLUENT_EXPORT void Models_Changed(Domain *);
FLUENT_EXPORT void Update_Eqn_Indices(Domain *);
FLUENT_EXPORT void Set_Species_Model_Flags(Domain *);
FLUENT_EXPORT void Init_Model_Weight(Model_Description *md);
FLUENT_EXPORT void Update_Parameter_Rpvar_Caches(void);

FLUENT_EXPORT int null_weight(Domain *domain);
FLUENT_EXPORT void null_inquire_equations(Domain *domain, Inq_Eqn_Selector inq, Pointer *result);
FLUENT_EXPORT void null_models_changed(void);
FLUENT_EXPORT void null_update(Domain *domain);
FLUENT_EXPORT void Add_Residual(Domain *);
FLUENT_EXPORT void eqn_store_residual(Domain *);
FLUENT_EXPORT void Resize_Residual(Domain *, int);
FLUENT_EXPORT cxboolean solve_flow_last_p(void);
FLUENT_EXPORT cxboolean solve_pb_after_vof_p(void);
FLUENT_EXPORT cxboolean nita_iterative_p(void);

#define ADD_EQUATION_OPTION(result,i)\
{\
 Pointer current_options = CDR(CDR(CAR(result)));\
 CDR(CDR(CAR(result))) = cons(NIL,NIL);\
 CDR(CDR(CDR(CAR(result)))) = current_options;\
}\
 CAR(CDR(CDR(CAR(result)))) = fixcons(i)

#define ADD_EQUATION_WITH_UNIT(result,pick,print_name,unit)\
 result = cons(NIL,result);\
 CAR(result) = cons(NIL,NIL);\
 CAR(CAR(result)) = intern(unit);\
 CAR(result) = cons(NIL,CAR(result));\
 CAR(CAR(result)) = stringcons(print_name);\
 CAR(result) = cons(NIL,CAR(result));\
 CAR(CAR(result)) = intern(pick)


#define ADD_EQUATION(result,pick,print_name)\
 result = cons(NIL,result);\
 CAR(result) = cons(NIL,NIL);\
 CAR(CAR(result)) = stringcons(print_name);\
 CAR(result) = cons(NIL,CAR(result));\
 CAR(CAR(result)) = intern(pick)


#define ADD_STD_EQUATION_OPTION(result)\
{\
cxboolean power_law_active = RP_Get_Boolean("allow-expert-dis-schemes?") || RP_Get_Boolean("activate-power-law-scheme?");\
ADD_EQUATION_OPTION(result,THIRD_ORDER_MUSCL);\
ADD_EQUATION_OPTION(result,QUICK);\
ADD_EQUATION_OPTION(result,SECOND_ORDER_UPWIND);\
ADD_EQUATION_OPTION(result,FIRST_ORDER_UPWIND);\
if (power_law_active)\
{\
  ADD_EQUATION_OPTION(result, POWER_LAW);\
}\
}

#define START_MODEL_TIMER(_model_name)                          \
  {double _u, _s, _cpu; MPT_CPUtime(&_u,&_s); _cpu = _u + _s;

#define STOP_MODEL_TIMER(_model_name)                                   \
  MPT_CPUtime(&_u,&_s); Record_Model_Time(((_u+_s)-_cpu), _model_name, 0);}

int Get_Model_Definition(Model_Description ***md);
Model_Description *Get_Model_by_Name(char *name);

#define SLIDING_OR_DYNAMIC_MESH_P(_domain) (Is_Moving_P (_domain) || sg_dynmesh)

#define NITA_NONITERATIVE_P() (sg_noniterative && !nita_iterative_p())
#define NITA_INSTABILITY_DETECTOR_P() (sg_noniterative && !nita_iterative_p() && \
                                       (mp_instability_detector || RP_Get_Boolean("nita/hybrid/mom/impl-relax?")))

#endif /* _FLUENT_MODELS_H */
