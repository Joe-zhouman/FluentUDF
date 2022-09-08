/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DPM_H
#define _FLUENT_DPM_H

#include "global.h"
#include "mem.h"
#include "profile.h"
#include "slide.h"
#include "cx.h"

/**
 * @addtogroup dpm Discrete Particle Model
 * @{
 *
 * @file
 * Interface to Discrete Particle Model (independent of internal types)
 */

#define DPM_SMALL 1.0e-9
#define CARR_VOF(c, t) C_STORAGE_R(c, t, dpm_par.sv_carr_vof)   /* DPM Carrier Phase Volume Fraction */
#if RP_3D
# define DPM_VELOCITY_DIM ND_ND
#else
# define DPM_VELOCITY_DIM (rp_axi_swirl ? 3 : ND_ND)
#endif

#if RP_3D
# define FLUID_VELOCITY_DIM ND_ND
#else
# define FLUID_VELOCITY_DIM (sg_swirl ? 3 : ND_ND)
#endif

#define MAX_REACT_POST 20 /* always set less than MAX_SPE_EQNS */
#define MAX_DPM_MATERIAL 100


/** DEM Have an enum for types of DPM BCs.
 *
 * ATTENTION: Any change here incures changing getintersectingface_secant accordingly.
 *
 * ALSO, MUST KEEP this IN SYNC with    const Particle_Fate dpm_fate_from_dpm_bc_type(),
 *  AND  MUST KEEP this IN SYNC with    const char dpm_bc_type_name(...),  both in dpm.c
 */
typedef enum dpm_bc_types
{
  DPM_BC_UNKNOWN         = -1,
  DPM_BC_INTERIOR        = 1,
  DPM_BC_REFLECT,             /*  2 */
  DPM_BC_TRAP,                /*  3 */
  DPM_BC_ESCAPE,              /*  4 */
  DPM_BC_SALTATE,             /*  5 */
  DPM_BC_PERIODIC,            /*  6 */
  DPM_BC_ABORT,               /*  7 */
  DPM_BC_SYMMETRY,            /*  8 */
  DPM_BC_SLIDING,             /*  9 */
  DPM_BC_WALL_JET,            /* 10 */
  DPM_BC_UDF,                 /* 11 */
  DPM_BC_PARALLEL,            /* 12 */
  DPM_BC_PARALLEL_PERIODIC,   /* 13 */
  DPM_BC_WALL_FILM,           /* 14 */
#if RP_WALL_FILM && RP_3D
  DPM_BC_WALL_EFILM,          /* 15 */
#endif
  DPM_BC_INTERIOR_PARENT,     /* 16 */
  DPM_BC_RELEASE,             /* 17 */
  DPM_BC_OVERSET_MIGRATION,   /* 18 */
  DPM_BC_REINJECT,            /* 19 */
  DPM_BC_OIL_FLOW,            /* 20 */
  DPM_BC_TYPES_MAX         /* one more than true number of types */
} dpm_bc_type_t;


typedef enum
{
  FILM_NONE = -1,
  FILM_STICK,
  FILM_REBOUND,
  FILM_SPREAD,
  FILM_SPLASH,
  FILM_EVAPORATIVE_SPLASH,
  FILM_USER_0,
  FILM_USER_1,
  FILM_USER_2,
  FILM_USER_3,
  FILM_USER_4,
  FILM_USER_5,
  FILM_USER_6,
  FILM_USER_7,
  FILM_USER_8,
  FILM_USER_9,
  MAX_FILM_REGIME
} Wall_Film_Regime;

typedef enum
{
  IMPINGEMENT_DEFAULT = 0,
  IMPINGEMENT_KUHNKE,
  IMPINGEMENT_STOCHASTIC_KUHNKE,
  IMPINGEMENT_DEFAULT_EWF
} Wall_Impingement_Type;

typedef enum
{
  CRITICAL_TEMPERATURE_FACTOR = 0,
  CALIBRATABLE_TEMPERATURE
} Critical_Temperature_Type;


#define MIN_LOG_EA -10 /* from Kuhnke plots 4.11 and 4.6 */

typedef enum
{
  EROSION_GENERIC = 0,
  EROSION_UDF = EROSION_GENERIC,
  EROSION_FINNIE = 1,
  EROSION_MCLAURY = 2,
  EROSION_OKA = 3,
  EROSION_WALL_SHEAR = 4,
  EROSION_DNV = 5,
  DPM_MAX_EROSION = 6
} Wall_Erosion_Models;

typedef enum
{
  FOUR_PAR_LH = 0,
  THREE_PAR_LH,
  ROSIN_RAMMLER,
  LOGISTIC,
  WEIBULL,
  NUKIYAMA_TANASAWA,
  MAX_SPLASH_DISTRIBUTIONS
} Splashing_Distribution_Type;

#define SPLASH_VEL(S,I)((S)->vel[I])
#define SPLASH_N(S,I)((S)->npar[I])
#define SPLASH_DIAM(S,I)((S)->diam[I])

/* forward declaration <dpm_types.h>
   Some models use particle pointers without needing to know how the struct is defined. */
struct particle_struct;

/**
 * @addtogroup dpm_interface interface functions/variables
 * @{ */

#define C_DPM_VIS0(c,t) C_STORAGE_R(c,t,SV_DPM_VIS_0)

/**
 * @addtogroup dpm_interface_global accessible global variables
 * @{ *************************************************************/

typedef enum
{
  EULER_IMPLICIT = 0,
  EULER_TRAPEZOIDAL,
  EXPONENTIAL_ANALYTIC,
  RK_EXPLICIT,
  EULER_SYMPLECTIC,
  EXPONENTIAL_ANALYTIC_DIAG,
  MAX_TRACKING_SCHEME
} Tracking_Scheme_Type;

typedef enum
{
  DPM_COLLISION_MESH_BARE_CFD = 0,
  DPM_COLLISION_MESH_CARTESIAN,
  DPM_COLLISION_MESH_UNDEFINED
} DPM_Collision_Mesh_Type;

#define INJECTION_SPRAY_SUITE_DDRAG(I) (DPM_DRAG_SPRAY_SUITE == (I)->drag_law)

/* forward declaration */
struct injection_struct;

#define NUM_SPRAY_CONSTS 13
typedef struct spray_suite_struct
{
  cxboolean break_up;
  cxboolean tab;
  cxboolean wave;
  cxboolean ssd;
  cxboolean madabhushi;
  cxboolean schmehl;
  cxboolean collide;
  cxboolean coalescence;
  cxboolean ddrag;
  cxboolean khrt;       /* Kelvin-Helmholtz--Rayleigh-Taylor model (ASME 97-ICE-52) */
  cxboolean wave_collide;
  cxboolean wave_mass_cutoff_adjust;
  cxboolean wave_rayleigh_growth;
  cxboolean tab_evaluate_double_ddrag;
  cxboolean collision_hybridparallelP;
  cxboolean collision_unidirectionalP;
  cxboolean collision_hybpar_everyield;

  int collision_mode;
  int collision_model_type;
  int collision_event_type;
  DPM_Collision_Mesh_Type collision_mesh_type;
  int collision_stencil_size;
  int n_coeff_restitution;
  cxboolean collision_sort_particles;

  real coeff_restitution[2];
  real constant[NUM_SPRAY_CONSTS];
  /* CK CD CB CF KENRG CV CONSTANT_1 B_1 B_2 Init_TAB_Amp */
  /* KHRT-c-levich KHRT-c-tau KHRT-c-3 */
  /* Note that CONSTANT_1 has been removed from the gui/tui - not for users */
  real wave_mass_cutoff;
  real wave_vnormal_scaling_factor;
  real min_time_step;  /* lowest time step for NANBU collision model */
  /* ssd spray model parameters */
  /* real ssd_we_cr;     -- now injection-specific */
  int ssd_np_max_child;
  real ssd_min_diam;
  /* real ssd_np_target; -- now injection-specific */
  /* real ssd_core_bu;   -- now injection-specific */
  real ssd_x_ratio;
  /* real ssd_x_si;      -- now injection-specific */
  real ssd_nu_t;

  /* madabhushi spray model parameters */
  int madabhushi_np_child;
  int madabhushi_column_breakup_np_child;
  real madabhushi_min_diam;
  real madabhushi_pe_column_breakup_time;
  real madabhushi_wave_column_breakup_time;
  real madabhushi_vnormal_scaling_factor;
  real madabhushi_column_breakup_vnormal_scaling_factor;

  /* schmehl spray model parameters */
  real schmehl_min_diam;
} spray_suite_t;

typedef struct impingement_constant_struct
{
  real E_2_crit[MAX_FILM_REGIME]; /* critical constants for impingement regimes definition */
  real KTmin;
  real KTmax;
  real cT;
  real We_limit;
} impingement_constant_t;

typedef struct splashing_distribution_struct
{
  real **vel;
  real *npar;
  real *diam;

} splashing_distribution_t;

typedef struct dpm_intrpl_nvar_def_s
{
  int phase;
  Svar svar;
  int node_sv_offset;
  int size;
  int comp;
} dpm_intrpl_nvar_def_t;

typedef struct
{
  Svar node_svar;
  Svar node_m1_svar;
  int n_phases;
  int n_nvars;
  int total_nvars_size;
  int *svar[SV_MAX];
  cxboolean used_svar[SV_MAX];
  dpm_intrpl_nvar_def_t *nvar;          /* dynamically allocated array */
  dpm_intrpl_nvar_def_t *do_max_nvar;   /* pointer to one entry in the above array --
                                         * for that single var., information transfer
                                         * from cells to nodes will be done not by
                                         * weighted averaging but by a MAX operation.
                                         */
  cxboolean velocity_average;
} dpm_intrpl_nvars_t;

typedef struct dpm_parameters_struct
{
  cxboolean replace_dpm_mass_source_by_mixture_fraction;
  cxboolean warn_in_test;   /* whether to issue some diagnostic messages.. */
  cxboolean radiation_p;
  cxboolean use_len_scale;
  real len_scale;
  real len_factor;
  real len_factor_receptor;
  int max_steps;
  int correlation_func; /* correlation function for DPM cloud model*/
  cxboolean ensemble_average; /* do ensemble-average for DPM cloud model*/
  int n_user_reals;
  cxboolean unsteady_tracking;
  cxboolean reallocate_unsteady_coupled;

  real time;
  real particle_time_step;
  real time_step;
  real last_time_step;
  real unsteady_accum_time;    /* unsteady_accum_time + tp_accumulated_time = time since last flow solver timestep */
  real end_of_prev_time_step;  /* time @end of prev time step - needed for unsteady injection file to avoid round-off error issues */
  int n_time_steps;
  cxboolean create_with_particle_time_step;
  cxboolean fluid_flow_time_stepping;

  cxboolean thermophoretic_force;
  cxboolean pressure_force_explicit;
  cxboolean pressure_force;
  cxboolean virtual_mass;
  real virtual_mass_factor;
  int drag_law;   /* will be set if uniform across all injections. */

  cxboolean saffman_lift;
  cxboolean binary;
  FILE *fp;
  cxboolean track_in_absolute;
#if 0
  cxboolean coupled_update; /* not used anymore */
#endif
  cxboolean coupled_update_droplet;
  cxboolean coupled_update_combusting;
  real Tmin, Tmax;
  Tracking_Scheme_Type tracking_scheme;           /* actual tracking scheme */
  Tracking_Scheme_Type tracking_scheme_low;       /* tracking_scheme for large steps and low accuracy */
  Tracking_Scheme_Type tracking_scheme_high;      /* tracking scheme for small steps and high accuracy */
  Tracking_Scheme_Type film_tracking_scheme;      /* tracking scheme for film particles */
  cxboolean step_size_control;
  cxboolean massless_second_order;
  Tracking_Scheme_Type massless_scheme;
  cxboolean track_spawned_particles;                   /* consider spawned particles during the same tracking step */
  cxboolean update_position_before_spawning_children;  /* flag to recover pre-R20.1 behavior */
  int spawned_particle_relocate_method;                /* method to use when moving spawned particles off a wall */
  int display_steps;
  int max_step_size_refinements;
  cxboolean tracking_scheme_selection;
  cxboolean limit_min_time_step;
  cxboolean injections_have_positive_flowrate;
  real max_error;
  cxboolean timestep_limiter_thermal_relax_time;
  real timestep_limiter_thermal_relax_time_factor;
  cxboolean time_to_boil;
  real boiling_pabs_to_pvap_ratio;
  real subcooled_boiling_temperature_offset;
  cxboolean update_props_before_tracking;
  real multicomponent_tolerance;
  int multicomponent_max_nsteps;
  int multicomponent_max_nred;
  real multicomponent_min_dt;
  cxboolean mc_old_handling_at_limit; /* Control on how particles are handled if the RK solver fails. */
  int mc_particle_failed_rk;
  real cells_to_cross;  /* maximum number of cells to be crossed per step */
  real lowest_diam;
  real lowest_film_diam;
  real leidenfrost_dt;
  real lowest_volume;
  real minimum_vapor_fraction;
  real mut_to_mul;
  real eddy_cross_time_factor;
  cxboolean sbes_treatment_pre192;
  cxboolean dynamic_les_treatment_pre192;
  cxboolean consistent_tke_ted_clipping;
  cxboolean rkvaporization;
  cxboolean rkmulticomponent;
  real fractional_change_factor_mass;
  real fractional_change_factor_heat;
  cxboolean limiting_time_algorithm;
  int surface_composition_assumption;
  cxboolean absolute_pressure;
  cxboolean latent_heat_at_boiling;
  cxboolean boiling_pressure_depend;
  cxboolean latent_heat_temperature_depend;
  cxboolean allow_condensation;
  cxboolean allow_supercritical_pressure;
  int mc_boiling_formulation;
  int mc_film_boiling_formulation;
  cxboolean allow_mc_boiling_failure;
  cxboolean variable_pr_number_in_boiling;
  cxboolean check_leidenfrost_on_faces;
  cxboolean apply_leidenfrost;
  cxboolean check_critical_flux;
  cxboolean high_temperature_correction;
  cxboolean set_law_on_first_timestep;
  int face_intersection; /* algorithm choice */
  int pathline_face_intersection;
  int locate_method; /* as used in dpm+path.c:NextPos */
  int particle_relocation;   /* method used for migrant particles --
                              * this also affects whether other code parts allow a film particle to be outside its cell,
                              * which can happen if the particle travels at a certain "cruise height" above the wall face.
                              */
  cxboolean acceleration_to_faces_for_rk; /* consider acceleration terms during
             computation of face intersection for
             RK_EXPLICIT and EXPONENTIAL_ANALYTIC */
  int particle_repartition;   /* algorithm choice */
  int debug_output;
  cxboolean temperature_limiter;

  cxboolean use_single_prec_face_points;  /* enables the legacy method (to be removed at some point in the future) */
  cxboolean search_before_iteration;
  cxboolean closest_cell_search;
  cxboolean closest_face_search;
  cxboolean disallow_aborted_particles;
  cxboolean use_face_v_with_b_injection;
  cxboolean pre_write_particle_check;
  cxboolean pre_write_particle_project;
  cxboolean pre_write_particle_project_dem;
  cxboolean relocate_init_particles;
  cxboolean dynamic_adaption_enabled;

  cxboolean wall_jet_interact;
  int wall_jet_level; /* 0 = only projection, 1 = simple computation of beta, 2 = full computation of beta */
  cxboolean wall_film_active;
  cxboolean wall_film_expert;
  cxboolean film_node_values;
  cxboolean lwf_ot_based_wall_interaction;

  real film_separation_angle;
  real film_separation_height;

  int stripping_scheme;
  int stripping_crit;
  real strip_m_const;
  real strip_f_const;
  real strip_beta;

  cxboolean film_visc_interaction;
  cxboolean film_gas_interaction;
  real film_mean_interaction;
  real film_p_imp_interaction;
  real film_m_imp_interaction;
  real film_min_dsplash_param;
  real film_splash_angle;
  real film_splash_angle_slope;
  real max_wallfilm_dist;
  real limiting_film_height;
  real film_accel_limit_divisor;
  real film_intrnl_drag_coeff;
  real film_intrnl_drag_vel_frac_limit;
  cxboolean film_boiling_rate;
  cxboolean film_intersection_scheme;
  cxboolean use_previous_film_height;
  real underrelax_film_height;
  cxboolean use_average_film_height;
  cxboolean smooth_film_height;
  cxboolean scale_by_residence_time;
  cxboolean scale_film_vel_by_res_time;
  cxboolean enable_spotty_film_corrections;
  real thermolysis_limit;
  cxboolean random_friedrich;
  cxboolean htc_film_bl_model_wall;
  cxboolean improved_film_gas_energy_balance;
  int film_breakup_particles;
  cxboolean film_interpolate_mesh;
  cxboolean film_interpolate_vars;
  impingement_constant_t impingement_constant;
  cxboolean limit_contact_time;
  real contact_time_factor;
  real reflection_distance_limit;
  real vle_limit;
  real ft_limiter;
  real orourke_splash_fraction_tail;
  cxboolean orourke_splash_fraction;
  cxboolean splash_pdf_tail_limiting;
  real splash_size_limit_low;
  real splash_size_limit_high;
  real splash_vel_limit_n;
  real splash_vel_limit_a;
  cxboolean limit_splash_film_height;
  cxboolean limit_kuhnke_init_film_height;
  cxboolean static_film_condensation;

  cxboolean scr_urea_depo_risk_unst_stat;

  cxboolean stagger_temporally;
  real stagger_factor;
  real stagger_radius_std_inj;
  int  stagger_spatial_n_tries;
  cxboolean solid_cone_uniform_mass_distribution;
  cxboolean atomizer_uniform_mass_distribution;
  real critical_caviation_number;
  real atomizer_downstream_closest_cell_epsilon;
  int atomizer_downstream_iterations;
  cxboolean atomizer_downstream_try_locate;
  cxboolean random_inj_pos_with_swirl;
  int pressure_swirl_atomizer_swirl_direction;
  int zone_volume_injection_method;
  int minimum_parcels_per_cell;
  real vol_inj_min_cell_volume;

  spray_suite_t spray_suite;
  cxboolean coalesc_avg_enth_not_temp;

  cxboolean levich_breakup_model;
  int levich_breakup_type;
  real levich_breakup_const;
  cxboolean all_p_in_liquid_core;

  int n_scalars;
  int n_cbk; /*CBK model integration constants*/

  real devolat_limit;

  cxboolean implicit_momentum_coupling;
  cxboolean old_implicit_momentum_coupling;
  cxboolean sources_every_flow_iteration;
  cxboolean view_full_sources; /* By default if sources_every_flow_iteration
                                * is active, variables from the DPM Sources section show
                                * the full sources and not the effectively applied
                                * to the flow solver sources after the under-relaxation.
                                * This new variable controls what part of the sources to be shown. */
  cxboolean linearized_source_terms;
  cxboolean linearized_source_terms_pic;
  cxboolean const_linearized_source;
  real source_linearization_limit; /* disable limiter, if set to zero, otherwise relative to flow */
  cxboolean linearize_mixture_fraction_source_terms;
  cxboolean linearize_species_source_terms;
  real      turb_cpling_eps_const;         /* constant multiplying production term into epsilon equation */
  real      turb_cpling_omega_const;       /* constant multiplying production term into omega equation */

  real      min_interpolated_density;      /* minimum value for cphase->rho */
  real      min_interpolated_viscosity;    /* minimum value for cphase->mu */
  cxboolean separate_turb_svar;
  cxboolean precompute_pdf_species;
  cxboolean barycentric_interpolation;     /* use barycentric coordinate interpolation (BCI) */
  cxboolean flow_gradient_interpolation;   /* interpolate flow solution gradients to the particle position */
  cxboolean extrapolate_from_subtet;       /* extrapolate flow during adaptive timestepping */
  cxboolean use_vof_face_svars;
  cxboolean clip_interp_weights;           /* limit interpolation weights to positive values (free-stream particles) */
  cxboolean clip_lwf_interp_weights;       /* limit interpolation weights to positive values (LWF particles) */
  cxboolean reconstruct_face_values_old;   /* recover pre-22.2 behavior when True */
  cxboolean reconstruct_face_values;
  cxboolean reconstruct_cell_values;
  cxboolean interpolate_use_face_udm;
  cxboolean interpolate_vof;
  cxboolean velocity_interpolation;
  cxboolean univ_grad_based_interpolation;
  cxboolean temperature_interpolation;
  cxboolean variable_interpolate_in_time;  /* transient variable interpolation */
  cxboolean mesh_interpolate_in_time;      /* transient mesh interpolation */
  cxboolean interpolate_nodes;
  int       interpolate_kernel;
  int       interpolate_stencil;
  real      interpolate_gauss;
  cxboolean interpolate_p;
  cxboolean interpolate_vel;
  cxboolean interpolate_temp;
  cxboolean interpolate_turb;
  cxboolean interpolate_granular;
  cxboolean interpolate_memory_initialized;
  cxboolean have_nodal_m1_variables;
  cxboolean use_averaged_nodal_velocity;
  cxboolean interpolate_all_vars_from_nodes;
  cxboolean interpolate_parameters_changed;

  cxboolean interpolate_coarse; /* interpolation on coarse mesh */
  real interpolate_coarse_factor;
  cxboolean interpolate_coarse_sources;
  cxboolean interpolate_coarse_new;

  /* global nodal interpolation setup for dpm particles and pathlines */
  dpm_intrpl_nvars_t      dpm_intrpl_nvars;
  dpm_intrpl_nvars_t pathline_intrpl_nvars;

  int       nci_node_correction_algorithm;

  cxboolean velocity_wall_interpolation;
  cxboolean sources_implicit;

  /** alternate source term formulation used by dense flow model*/
  cxboolean eulerian_source_term_coupling;
  cxboolean dpm_vof_apply_total_src_correction;
  cxboolean dpm_vof_energy_cplng_via_source_term;
  cxboolean use_interp_flow_vars_for_sources;
  cxboolean dpm_vof_heat_source_prior_r222;
  cxboolean consider_discrete_phase_vof;
  cxboolean relocate_unsteady_particles_for_mdm;  /* DE21583 */

  /** averaging of cell based variables */
  cxboolean avg_nodes;
  int avg_kernel;
  cxboolean avg_sources;   /* node based averages of source terms */
  cxboolean avg_ddpm_vars; /* node based averages of DDPM variables */
  cxboolean avg_each_step; /* do averaging after each integration step */
  real avg_gauss;
  cxboolean avg_volume_heat_coeff; /* use volumetric averaging instead of particle averaging for DDPM heat coeff */

  cxboolean short_wave_airblast;
  real atomizer_spread_param;

  real momentum_ap_coeff_multiplier;   /* dpm source term ap coeff multiplier */
  real energy_ap_coeff_multiplier;
  real species_ap_coeff_multiplier;

  cxboolean dpm_linear_source_term_change;

  /* pdf transport */
  cxboolean number_control;
  cxboolean position_correction;
  cxboolean local_time_step;
  int mixing_model;
  int num_pdf_steps;
  int num_fv_steps;
  int i_ta;
  int micro_mixing;
  real n_ta, inc_ta;
  real num_part_per_cell;
  real ppc_consts[4];
  real C_phi;
  real pdft_cfl;
  real pdft_fourier;
  real pdft_freq;
  real pdft_time_step;

  cxboolean par_dpm, par_mig;
  cxboolean homogeneous_net;
  cxboolean cell_face_weighting;
  cxboolean injections_defined;
  cxboolean particles_in_domain;
  cxboolean source_non_zero;

  cxboolean random_tab_diam;
  /* int number_tab_diameters;   -- now injection-specific */
  real lower_tab_diam_ratio;
  real tab_spread_param;
  int tracking_order_randomizations;
  cxboolean random_uniform;
  real uniform_random;
  cxboolean random_gauss;
  real gauss_random;
  cxboolean cp_correction;
  cxboolean multicomponent_boiling;
  cxboolean density_multispecies;
  cxboolean dpm_vof;
  cxboolean fill_sources_per_material;
  int dpm_vof_scheme_type;
  cxboolean dpm_vof_velocity_correction;
  real dpm_vof_gran_temp_lower_limit;
  int n_dpm_domains;
  cxboolean dpm_vof_show_internal_variables;
  int dpm_vof_temperature_avrg_method;
  int dpm_vof_heat_exch_method;
  cxboolean dpm_vof_euler_check_neighbour_vof;
  int  dpm_vof_clp_sub_model;                      /* Sub-models related to close packing. Can be switched individually or in combination */
  real dpm_vof_clp_sub_model_threshold;            /* Fraction of packing limit vof used as threshold for activation of some sub-models   */
  real dpm_vof_low_cutoff;
  cxboolean dpm_vof_skip_mom_ap;   /* skip SV_U/V/W_AP in DPM_Fix_SVar */
  cxboolean dpm_vof_solids_drag_enabled;
  real dpm_vof_solids_drag_scaling_factor;
  real dpm_vof_clp_step_factor;
  real dpm_vof_clp_static_gpress_slope;
  real dpm_vof_clp_static_gpress_shift;
  cxboolean dpm_vof_clp_corrector;
  cxboolean dpm_vof_clp_corrector_tracking;
  cxboolean dpm_vof_clp_corrector_move_all;
  cxboolean dpm_vof_clp_corrector_update_vof;
  cxboolean dpm_vof_clp_corrector_vof_node_based;
  cxboolean dpm_vof_clp_corrector_update_distribution_vof;
  cxboolean dpm_vof_clp_corrector_sort_particles;
  int dpm_vof_clp_corrector_iterations;
  int dpm_vof_clp_corrector_max_cells;
  int dpm_vof_clp_corrector_cell_factor;
  real dpm_vof_clp_corrector_dist_factor;
  real dpm_vof_clp_corrector_pl;
  int tp_log_id;                                  /* Only for debugging purposes: Can be used in combination with LOG_ID */
  cxboolean dpm_vof_euler_allow_parallel_hybrid;
  real dpm_vof_fixed_urf_in_fix_dpm_svar;
  cxboolean dpm_vof_iad_particle;                 /* set interfacial area density method to particle-method */

  cxboolean reset_partition_weights;
  cxboolean display_free_particles;
  cxboolean display_wallfilm_particles;
  int verbosity;
  cxboolean is_pathline;  /* we are doing the pathline plot */
  int polyhedron_tet_division_level; /* 0 = no division, 1 = based on faces, 2 = based on nodes */
  int n_time; /* number of the current flow time step */
  int n_dpm_time; /* number of the current dpm time step (rpvar 'dpm/time-step) */
  cxboolean sub_cycling_no_update; /* indicates status during sub cycling within a time step */
  cxboolean parallel_hybrid; /* switch for parallel hybrid model */
  cxboolean dem_hybrid; /* switch for dem hybrid model */
  cxboolean hybrid_deposit_in_order;   /* mitigate run-to-run variation (at some run-time expense..!) */
  int dem_part_method; /* switch for dem part method, 0-1d, 1-metis */
  real parallel_imbalance_tolerant; /* the allowable group size deviation */
  int parallel_group_size_minimum; /* the minimum allowable group size */
  int parallel_nthreads; /* the number of threads */
  int parallel_lb_method; /* the type of load balance method */
  int memory_alloc_limit; /* maximum memory in bytes allocated for particle exchange arrays */
  cxboolean enforce_locks_in_mallocs;
  void ***omp_mem; /* the thread specific memory */
  int nomp_mem; /* the number of thread specific memory */
  size_t lock_count;
  int cfunc_level;      /* us20658 */
  int cfunc_level_last; /* us20658 */
  int dpm_summary_data_id;
  cxboolean dpm_vof_last;
  cxboolean unsteady_statistics;
  cxboolean do_dpm_per_inj_thread_summaries;
  cxboolean use_particle_random_seeds;
  cxboolean serial_particle_id;
  cxboolean use_iteration_seed;
  cxboolean use_timestep_seed;
  cxboolean use_timestep_seed_corrected; /* de176638 */
  cxboolean use_injection_name_seed; /* bugfix */

  cxboolean surf_inj_cont_part_id;

  cxboolean do_rotation; /* used to control visibility of postprocessing variables */
  cxboolean visualize_rotation; /* will require additional memory for storing quaternion (4-tuple array) per particle. */

  /* DEM */
  real dem_max_van_der_waals_range;
  char pl_velocity_domain[MATERIAL_NAME_LENGTH]; /* velocity domain for pathlines. Use name instead of
                                                    domain index since "all-phases" is also an option. */

  /* Subtet tracking */
  cxboolean use_subtet_tracking;
  cxboolean remove_stuck_particles;
  cxboolean use_high_res_oil_flow;
  cxboolean use_subtet_tracking_at_case_read;
  cxboolean warnings_cause_regression_failures;         /* causes regression tests to fail if message appears */
  cxboolean incompletes_cause_regression_failures;      /* test fails if there are any incomplete particles */
  cxboolean check_cubic_roots;
  cxboolean check_for_local_min_max;
  cxboolean check_subtet_validity;                      /* test for degenerate subtets */
  cxboolean use_quad_face_centroid;                     /* use face centroid when decomposing quad faces */
  cxboolean use_face_centroid_with_periodics;           /* always use quad face centroids if the case has periodic boundaries */
  cxboolean store_interpolation_weights;                /* store the barycentric coordinates for using in DPM_Interpolation_State */
  cxboolean check_subtet_before_intersections;          /* skip intersection calculations if the particle is within the subtet */
  cxboolean barycentric_intersections;
  cxboolean check_if_particle_is_in_cell;               /* only accumulate sources if the particle is in the expected cell */
  cxboolean ensure_tp_is_in_cell_after_migration;       /* ensure the particle is in the cell following parallel migration */
  cxboolean always_reflect_turbulent_fluctuations;      /* recovers the behavior prior to Fluent 21.1 when enabled */
  cxboolean check_for_missed_intersections;             /* confirm particle is in subtet when interpolating variables */
  cxboolean reflect_pathlines_from_walls;               /* reflect pathlines and hold the velocity constant for one timestep */
  cxboolean update_vel_at_intersections;                /* update velocity at crossing point even if (include_acc == False) */
  cxboolean ignore_acceleration_for_intersections;      /* update intersection parameters if point is outside of subtet */
  cxboolean move_lost_particles_to_donor_cells;
  cxboolean use_barycentric_sampling;
  cxboolean error_control_based_upon_velocity;
  cxboolean zero_gradients_on_walls;
  cxboolean zero_node_velocity_on_walls;
  cxboolean use_wall_normal_for_wall_node_correction;
  cxboolean move_particles_traveling_in_plane;          /* move particles off of subtet planes if they are traveling within them */
  cxboolean scale_intersection_tolerance;
  cxboolean include_lwf_in_concentration;               /* include LWF particles in DPM Concentration */
  cxboolean use_particle_dt_for_intersection_tol;       /* use TP_DT(tp) for the subtet intersection tolerance with 2D-axi grids */
  cxboolean abort_lost_film_particles;                  /* when tracking of a film particle fails, do not make it free-stream, abort it */
  cxboolean lwf_vel_correction_for_non_planar_faces;    /* treat subtet face intersections as timestep limiters when True */
  cxboolean project_lwf_particle_to_film;               /* project wall film particles to film when entering a new face */
  cxboolean project_lwf_particle_for_subtet_tracking;   /* project the particle to the film to change from standard tracking */
  cxboolean disable_film_particle_acceleration;         /* disable acceleration to separate tracking from physics */
  cxboolean disable_wallfilm_stick_regime;              /* ensure that wall film particles have an initial velocity */
  cxboolean freeze_wallfilm_properties;                 /* holds the film constant, permitting "one-way" tracking of film particles */
  cxboolean film_particles_reflect_from_walls;          /* reflect from walls, else released from film */
  cxboolean include_film_particles_in_sample_file;
  cxboolean search_film_thread_directly;                /* loop over face thread to find new film face after mesh has changed */
  cxboolean search_film_thread_directly_overset;        /* loop over face threads to find new film face during overset migration */
  cxboolean anisotropic_cell_length;                    /* consider aspect ratio in setting timestep - recommended in boundary layers */
  cxboolean use_legacy_location_method;                 /* use legacy approach to locating point in domain (not decomposing cells into subtets) */
  cxboolean search_cell_threads_directly;               /* search for lost particles by looping over cell threads */
  cxboolean locate_legacy_particles;                    /* load particles previously tracked with standard tracking */
  cxboolean limit_nd_table_search_by_distance;
  cxboolean check_cell_bounding_box;
  cxboolean inject_in_dead_cells;
  cxboolean reflect_from_orphan_cells;
  cxboolean mesh_is_adapted;                            /* indicates that the mesh has parent faces */
  cxboolean anisotropic_turbulent_dispersion;           /* boundary layer particle dispersion model is active */
  cxboolean remove_particles_from_walls;                /* move particles off the wall following a reflection */
  cxboolean log_exterior_cells;
  cxboolean move_lost_particles_to_known_cell;
  cxboolean average_pos_at_gti_mixing_plane;
  cxboolean clip_species_fractions_intrpl;
  cxboolean store_grid_id_after_relocation;
  real anisotropic_damping_constant;
  real min_eddy_time_at_birth;
  real overset_cell_length_scale_factor;
  real max_aspect_ratio;
  real min_vel_angle_change;
  real max_vel_angle_change;
  real glancing_intersection_tolerance;
  real move_from_stationary_plane_fraction;             /* fraction to move the particle towards the subtet center */
  real move_from_moving_plane_fraction;                 /* fraction to move the particle towards the subtet center */
  real move_from_nci_fraction;                          /* subtet tracking crossover tolerance for NCI */
  real move_from_sample_face_fraction;                  /* move towards subtet center by this fraction when sampling particles */
  real subtet_intersection_tolerance;                   /* intersection tolerance (linear) constant */
  real nci_overlap_fraction;
  real max_face_normal_dot_product;                     /* limit for face normal when grid walking through prism layer */
  real film_spreading_parameter;
  double locate_filter_scale_factor;
  double relocation_tol_scaling;
  double film_face_tol_scaling;                         /* scaling for is_point_on_face() tolerance when relocating film particles */
  double missed_face_intersection_tolerance;            /* tolerance for missed intersection warning */
  double max_intersect_tolerance_frac;                  /* fraction of the timestep to use as a tolerance limiter */
  double wallfilm_colinearity_tolerance;                /* tolerance scaling for are_points_colinear */
  double negative_discriminant_limit;
  double crossing_direction_tolerance;
  double check_cubic_roots_tolerance;
  double low_order_intersect_factor;
  double gti_crossover_tolerance;
  double max_sum_of_timesteps_before_stuck;
  double parent_face_barycentric_tolerance;             /* tolerance when searching for points in subtets made up of child face nodes */
  int anisotropic_dispersion_n_layers;                  /* max number of prism layers included in model */
  int wallfilm_node_correction_method;                  /* nodal velocity correction method for wallfilm faces */
  int num_edge_update_tolerance_increases;              /* maximum number of times the tolerance will be increased */
  int num_edge_update_tolerance_refinements;            /* number of tolerance refinements when too many nodes are found */
  int subtet_warning_verbosity;
  int newton_method_max_cycles;
  int pathline_performance_level;
  int relocation_robustness_level;
  int overset_relocation_robustness_level;
  int n_samples_in_running_sum;
  int max_relocation_attempts;
  int nodal_var_update_freq;                            /* frequency for nodal reconstruction */
  int nodal_var_update_requests;                        /* number of times the tracker was called */

  /* Erosion - MDM coupling and boundary face smoothing */
  cxboolean couple_erosion_mdm;
  cxboolean include_shear_erosion;
  int face_smoothing_number_of_sweeps;
  int face_smoothing_weighting_option;
  cxboolean face_smoothing_conservative;
  real wall_material_density;
  real erosion_mdm_termination_total_time;
  real erosion_mdm_termination_max_disp;
  real erosion_mdm_mesh_max_disp;
  int erosion_mdm_ref_erosion_model;
  int erosion_mdm_simulation_cntl_num_flow_iterations;
  real crossover_tol;
  real sample_plane_tolerance;

  real min_particle_density;
  real max_particle_density;

  cxboolean new_acceleration_form;

  /* Wall interaction control factors */
  cxboolean always_move_away_from_face;
  real push_from_wall_fract;
  real minimum_wall_impact_angle;
  real momentum_relaxation_time_ratio;
  cxboolean dpm_wall_force;
  cxboolean ddpm_implicit_drag_udf;

  cxboolean breakup_new_partid;

  cxboolean is_dpm_to_vof_active_p;

  /* Blocking*/
  cxboolean incorp_blocking_effect;
  real max_vf_allowed_for_blocking;
  real min_vf_threshold_for_dpm_src_scaling;
  Svar sv_carr_vof;                  /* DPM Carrier Phase Volume Fraction */
  cxboolean blocking_effect_scale_dpm_src;
  cxboolean blocking_effect_scale_drag_coeff;

  cxboolean is_liquid_p_active;
  cxboolean is_particle_p_active;
  real liquid_p_speed_of_sound;
  real liquid_p_cole_n;
  real liquid_max_vof;
  cxboolean store_vof;

  /* MP-PIC related control */
  cxboolean pic_enabled;
  cxboolean pic_mp;       /* multiphase specific extension enabled? */

  cxboolean span_particles_use_cell_locator;
  cxboolean non_final_inner_sub_cycle_p;
  cxboolean dpm_vof_do_node_based_max_for_ddpm_vol_frac;
  cxboolean ddpm_static_pileup_p;     /* general switch, will be true if any domain has it active */
  real ddpm_static_pileup_pack_flag_grad_thresh;
  real ddpm_static_pileup_high_ddpm_phase_vol_frac_limit;
  real ddpm_static_pileup_halt_p_above_vol_frac;
  real ddpm_static_pileup_holefiller_thrsh_vof;
  real ddpm_static_pileup_frict_drag_onset_vof;
  real ddpm_static_pileup_frict_drag_limit_vof;
  real ddpm_static_pileup_frict_drag_onset_slope;
  real ddpm_static_pileup_frict_drag_max_Cd;
  real ddpm_static_pileup_frict_drag_exponent;
  real ddpm_static_pileup_frict_drag_offset;
  real ddpm_static_pileup_frict_drag_min_delta;
  real ddpm_static_pileup_bulk_velocity_scaling_factor;
  real ddpm_static_pileup_instant_cell_volf_use_factor;
  cxboolean ddpm_static_pileup_use_fixed_thread_vel;
  cxboolean ddpm_static_pileup_use_max_not_avg_in_ddpm_vol_frac_nba;
  cxboolean ddpm_static_pileup_zero_gran_press_grad_at_bottom_walls;   /* #if HAVE_SUPP_WALL_GRAN_PRES_GRAD ... #endif */
  cxboolean ddpm_static_pileup_zero_gran_press_grad_at_all_walls;      /* #if HAVE_SUPP_WALL_GRAN_PRES_GRAD ... #endif */
  cxboolean ddpm_static_pileup_frict_drag_cont_phs_mom_src_suppress;
  real ddpm_static_pileup_bott_wall_max_slope_angle;
  real ddpm_static_pileup_norm_coeff_of_restitution;
  real ddpm_static_pileup_tang_coeff_of_restitution;
  real ddpm_static_pileup_surface_control;

#if ! UDF_COMPILER /* disable for interpreted udfs */
  int64_t next_part_id;
#endif

} dpm_parameters_t;

enum
{
  OM_OBJP_MANAGER = 0,
  OM_UNIFORM_RANDOM,
  OM_MEMORY_MANAGER,
  OM_MAX
};

typedef enum
{
  DPM_TRACKING_CHANGED = 0,
  DPM_GRID_PARTITIONING_CHANGED,
  DPM_MESH_CHANGED,
  DPM_CELL_THREAD_ACTIVATED,
  DPM_DATA_REDUCTION
} DPM_Reset_Trigger;


#define SG_NODE_INTERPOLATE_IN_TIME(domain) (dpm_par.mesh_interpolate_in_time && SV_ALLOCATED_P_NEW ((Get_Node_Thread (domain)), SV_N_X_M1))

/* informs about first DPM iteration per time step, always true for steady flows */
FLUENT_EXPORT cxboolean DPM_First_Iteration_P(void);
extern FLUENT_EXPORT dpm_parameters_t dpm_par;
extern FLUENT_EXPORT int DPM_Phase_Id;

/* @} dpm_interface_global */

/**
 * @addtogroup dpm_interface_storage storage definition section
 * @{ *************************************************************/
FLUENT_EXPORT void init_dpm_scalar_on_node(Var_Attribute *sv, Domain *);
FLUENT_EXPORT void init_dpm_vector_on_node(Var_Attribute *sv, Domain *);
FLUENT_EXPORT void init_dpms_species_on_node(Var_Attribute *sv, Domain *);
FLUENT_EXPORT size_t DPM_Get_Storage_Size(Svar sv, Thread *t);

/* @} dpm_interface_storage */

/**
 * @addtogroup dpm_interface_solver routines called from flow solver or cortex(cxhost/cxnode)
 * @{ *************************************************************/

FLUENT_EXPORT void SV_FlushDPMSources (void);
FLUENT_EXPORT void DPM_Set_Particles_In_Domain (void);
FLUENT_EXPORT void Shift_Unsteady_Particles_In_Cell_Thread(Thread *, STrans *const);
FLUENT_EXPORT void DPM_Reset_Iter(void);
FLUENT_EXPORT void Unsteady_PDF_Transport(Domain *domain);
FLUENT_EXPORT void Move_Unsteady_Particles(real dtime);
FLUENT_EXPORT void InitializeDPMPrimitives(void);
FLUENT_EXPORT void DPM_Update(Domain *);
FLUENT_EXPORT void Model_Initialize_dpm(void);
FLUENT_EXPORT void Init_Unsteady_Particles(void);
FLUENT_EXPORT void Correct_PDF_Transport_Density(Domain *domain);
FLUENT_EXPORT void Init_DPM_c_par_for_CUP(void);
FLUENT_EXPORT void Create_Unsteady_Particles(const real flow_time, const cxboolean update);
FLUENT_EXPORT cxboolean need_dpm_surften_mu(void);
FLUENT_EXPORT void DPM_Convert_Transient_Swirl_Component(void);
FLUENT_EXPORT void DPM_Momentum_Source(Domain *, int, Svar);
FLUENT_EXPORT void DPM_Scalar_Source(Domain *, int, Svar, Svar, Svar, Svar, Svar, Svar);
FLUENT_EXPORT void DPM_Turb_Sources (Domain *domain, int eqn, Svar sv_phi, Svar sv_phi_ap, Svar sv_phi_s );
FLUENT_EXPORT void SV_UpdateDPMSourcesWithIteration(void);
FLUENT_EXPORT void DPM_Reset (const DPM_Reset_Trigger trigger);
FLUENT_EXPORT void DPM_Sync(cxboolean);
FLUENT_EXPORT void DPM_Get_injection_flows(real *sumdt, real *sumnt);
FLUENT_EXPORT void SV_GetSolverParameters (void);
FLUENT_EXPORT void SV_GetSolverRdef (void);
FLUENT_EXPORT void DPM_Free_Thread_Data(Thread *);
FLUENT_EXPORT void DEM_Set_Boundary_Collision_Partner(Thread *thread, char *as_name);
FLUENT_EXPORT void Reset_inDomain_Particles_Summaries(void);
FLUENT_EXPORT void DPM_Compute_Particle_Gradient(Domain *domain);

FLUENT_EXPORT cxboolean DPM_Cloud_Model_Used_P(void);
FLUENT_EXPORT cxboolean DPM_Breakup_Used_P(void);
FLUENT_EXPORT cxboolean DPM_DDPM_Used_P(void);
FLUENT_EXPORT cxboolean DPM_Coalescence_Used_P(void);
FLUENT_EXPORT int DPM_Collision_Mode_Used(void);
FLUENT_EXPORT int DPM_Collision_Model_Type_Used(void);
FLUENT_EXPORT cxboolean DPM_PDF_Transport_Model_Used_P(void);

/* @} dpm_interface_solver */

/* @} dpm_interface */

/**
 * @addtogroup dpm_io dpm i/o
 * @{ */

#if ! UDF_COMPILER /* disable for interpreted udfs */

typedef void (* dpm_start_tracks_f) (int nTracks, int64_t *trackIdList);
typedef void (* dpm_insert_track_f) (int64_t   part_id,
                                     int       nPoints,
                                     real     *positions,
                                     int      *cellZones,
                                     size_t   *cellIds,
                                     int       nScalars,
                                     real     *scalars);
typedef void (* dpm_end_tracks_f) ();

typedef struct
{

  dpm_start_tracks_f start_tracks;
  dpm_insert_track_f insert_track;
  dpm_end_tracks_f   end_tracks;

} dpm_track_callbacks_t;

FLUENT_EXPORT void DPM_Set_Track_Callbacks(dpm_start_tracks_f start, dpm_insert_track_f insert, dpm_end_tracks_f end);
FLUENT_EXPORT void DPM_Track_Pathlines(int nTracks,
                                       real *position,
                                       int64_t *cellIndex,
                                       int *cellZone,
                                       int64_t *particleId,
                                       int surfaceId,
                                       int maxSteps,
                                       int reverse,
                                       int nodalValues,
                                       int errorControl,
                                       real maxError,
                                       real lengthScale);
#endif /* ! UDF_COMPILER */

/**
 * @addtogroup dpm_io_file file I/O functions
 * @{ *************************************************************/
FLUENT_EXPORT void Read_Particle_Data(Domain *domain, cxboolean mpi, int fhandle, int *headerbuf, FILE *fd, cxboolean binary, cxboolean double_data);
FLUENT_EXPORT void Write_Particle_Data(Domain *domain, cxboolean mpi, int fhandle, FILE *fd, cxboolean binary);

/* @} dpm_io_file */

/* @} dpm_io */

/**
 * @addtogroup dpm_parallel parallel functions
 * @{ */
FLUENT_EXPORT void init_parallel_injections(Domain *domain, cxboolean init_all_neighbors);
FLUENT_EXPORT void free_parallel_injections(Domain *domain);
/* @} */


/** model switches institutionalized as functions
 */
cxboolean if_traditional_dpm_collide(void);
cxboolean if_traditional_dpm_collide_no_vof(void);

#define DPM_NAME_LENGTH 80

/*
 * For IO2 library
 */
#define TO_STRING(v) #v
typedef struct dpm_io_t_
{
  int xf_id;
  char name[DPM_NAME_LENGTH];
  int offset;
  int type;
  int mpt_type;
  int size;
  struct dpm_io_t_ *next;
} dpm_io_t;

typedef enum
{
  PARTICLE_DTYPE_PARTICLE_REAL = 0,
  PARTICLE_DTYPE_PARTICLE_INT,
  PARTICLE_DTYPE_PARTICLE_INT64,
  PARTICLE_DTYPE_UNSTEADY_REAL,
  PARTICLE_DTYPE_USER_REAL,
  PARTICLE_DTYPE_SCALAR_REAL,
  PARTICLE_DTYPE_CELL_THREAD_ID,
  PARTICLE_DTYPE_PVAR_REAL,
  PARTICLE_DTYPE_INJECTION_REAL,
  PARTICLE_DTYPE_PARTICLE_INT_SKIP,
  PARTICLE_DTYPE_MAX
} particle_data_t;

FLUENT_EXPORT struct injection_struct *Pick_Injection(const char *name);
FLUENT_EXPORT struct injection_struct *Get_dpm_injections(void);
FLUENT_EXPORT struct injection_struct *Get_pdft_injection(void);
FLUENT_EXPORT struct injection_struct *Get_Next_Injection(struct injection_struct *);

FLUENT_EXPORT size_t Get_Injection_Particle_Count(struct injection_struct *);
FLUENT_EXPORT const char *Get_Injection_Name(struct injection_struct *);
#if ! UDF_COMPILER
FLUENT_EXPORT int pack_injection_var(Domain *domain, struct injection_struct *I, int var, particle_data_t dtype, int *ibuff, real *rbuff, int64_t *i64buff);
FLUENT_EXPORT int unpack_injection_var(Domain *domain, const struct injection_struct *I, int var, particle_data_t dtype, int *ibuff, real *rbuff, int64_t *i64buff, size_t size_var_buf);
FLUENT_EXPORT int pack_injection_array_real(struct injection_struct *I, int var, int size_var, particle_data_t dtype, real *rbuff);
FLUENT_EXPORT int unpack_injection_array_real(struct injection_struct *I, int var, int size_var, particle_data_t dtype, real *rbuff);
#endif

FLUENT_EXPORT dpm_io_t *Get_DPM_IO_List_Created(struct injection_struct *, int);
FLUENT_EXPORT void Get_DPM_IO_List_Freed(dpm_io_t **);
FLUENT_EXPORT int Get_Particle_Data_Write_Initialized(Domain *);
FLUENT_EXPORT real Get_Flow_Time(void);
FLUENT_EXPORT int Is_Next_Particle_ID_Required(struct injection_struct *);
FLUENT_EXPORT int Get_Particles_Created_For_Reading(struct injection_struct *, int);
FLUENT_EXPORT int Get_Particle_Data_Read_Initialized(Domain *, size_t);
FLUENT_EXPORT int Get_Particle_Data_Read_Finalized(Domain *, struct injection_struct *, int, int, int);

FLUENT_EXPORT void Fix_Unsteady_Particles_Ages(real flow_time);
FLUENT_EXPORT void Cache_DPM_RP_Vars_Depend_On_NITA(void);


/* ***** oct tree search <cl_dpm.c> */
FLUENT_EXPORT void DPM_Init_Oct_Tree_Search(void);
FLUENT_EXPORT void DPM_Update_Oct_Tree_Search(void);
FLUENT_EXPORT void DPM_End_Oct_Tree_Search(void);
FLUENT_EXPORT void DPM_Set_Oct_Tree_Init_Flag(cxboolean);
FLUENT_EXPORT void DPM_Print_Search_Statistics(void);
FLUENT_EXPORT int SV_locate_point (real [], CX_Cell_Id *);

/* For smoothing wallfilm height and erosion */
FLUENT_EXPORT void calculate_node_from_face_values(Domain *domain, Svar sw);
FLUENT_EXPORT void calculate_face_from_node_values(Domain *domain, Svar sw);

/******   For incoporation of blocking effect of DPM in Eulerian Phase*/
FLUENT_EXPORT void Implement_Blocking_Effect(Domain *domain, Svar sv_flux, int auxi_yes);
FLUENT_EXPORT void Implement_Blocking_Effect_on_old_Density(Domain *domain);
FLUENT_EXPORT void Implement_Blocking_Effect_on_old_Vof(Domain *domain);
FLUENT_EXPORT void Block_Unblock_Effect_on_Density(Domain *domain, cxboolean block);
FLUENT_EXPORT void Undo_Blocking_Effect(Domain *domain, Svar sv_flux, int auxi_yes);
FLUENT_EXPORT void Calculate_Carr_Vof_Value(Domain *domain);   /* DPM Carrier Phase Volume Fraction */
FLUENT_EXPORT void Reset_Shared_Memory_Warning_Flags(void);

/* For degenerate subtets */
FLUENT_EXPORT void Degenerate_Subtet_Check(Domain *domain);
FLUENT_EXPORT void Enable_Degenerate_Subtet_Settings(Domain *domain, const cxboolean settings[2], const int verbosity);
FLUENT_EXPORT cxboolean Check_For_Degenerate_Subtets(Domain *domain, cxboolean *warnings, const int verbosity);

FLUENT_EXPORT int Get_Inj_ID_From_Inj_Name(const char *inj_name);

#define PARALLEL_DPM (dpm_par.par_dpm)

#define I_DO_DPM ( I_AM_NODE_SERIAL_P || \
                   ( PARALLEL_DPM && I_AM_COMPUTE_NODE_P) || \
                   (!PARALLEL_DPM && I_AM_NODE_HOST_P)  )
#define DPM_NODE_ZERO_OR_HOST ((dpm_par.par_dpm && I_AM_NODE_ZERO_P) || (!dpm_par.par_dpm && I_AM_NODE_HOST_P))

#define PARTICLE_MIGRATION (dpm_par.par_mig)
#define HIGH_RESOLUTION_TRACKING_ENABLED (dpm_par.use_subtet_tracking && dpm_par.barycentric_interpolation)

#if RP_2D
#  define ADD_SV_VOLUME_2D SV_VOLUME_2D, SV_AREA_2D,
#else
#  define ADD_SV_VOLUME_2D
#endif

#define SV_DPM_DIST_LIST \
  SV_DPM_BNDRY_DIST,\
  SV_DPM_DIST

#define SV_DPM_WALL_FILM_LIST \
  SV_FILM_HEIGHT,\
  SV_FILM_MASS,\
  SV_FILM_HEIGHT_M0,\
  SV_FILM_MASS_M0,\
  SV_FILM_TEMP,\
  SV_FILM_SURFACE_TEMP,\
  SV_FILM_HFLUX,\
  SV_FILM_TEMP_M0,\
  SV_FILM_SURFACE_TEMP_M0,\
  SV_FILM_HFLUX_M0,\
  SV_FILM_H_WALL,\
  SV_FILM_VELOCITY,\
  SV_FILM_VELOCITY_M0,\
  SV_FILM_M_IMP_M0,\
  SV_FILM_M_IMP_M1,\
  SV_FILM_MU,\
  SV_FILM_SURF_TENSION,\
  SV_FILM_MU_M0,\
  SV_FILM_SURF_TENSION_M0,\
  SV_FILM_STRIPPED,\
  SV_FILM_LEIDENFROST,\
  SV_WALL_SHEAR, \
  EXPAND_PER_MAT_SV(FILM_MASS_OF)

#define SV_DPM_LEAN_LIST \
  SV_P, SV_DENSITY, \
  SV_U, SV_V, SV_W, \
  SV_U_G, SV_V_G, SV_W_G, SV_OMEGA_G, \
  SV_P_G, SV_T_G, \
  SV_U_RG, SV_V_RG, SV_W_RG, \
  SV_P_RG, SV_T_RG, \
  SV_FLUX, \
  SV_MU_LAM, SV_MU_T, \
  SV_D, SV_K, SV_O, SV_NUT, \
  SV_N_FILM_HEIGHT, SV_WALL_V, SV_BND_GRID_V, \
  SV_DPM_WALL_FILM_LIST, \
  SV_REFLECT_HFLUX, \
  SV_RUU, SV_RVV, SV_RWW, SV_RUV, SV_RVW, SV_RUW, \
  SV_T, SV_H, SV_HEAT_FLUX, \
  SV_P1, SV_DO_IRRAD, SV_DO_IRRAD_OLD, SV_KTC, SV_CP, \
  SV_ABS_COEFF, SV_SCAT_COEFF, \
  SV_FMEAN, SV_FMEAN2, SV_FVAR, SV_FVAR2, SV_PDF_MW, SV_PREMIXC, \
  SV_INERT, SV_INERT_H, \
  SV_Y, \
  EXPAND_NPROB_SV(UFLA_YI), \
  EXPAND_NUDS_SV(UDS), \
  SV_UDM_I, \
  SV_DPM_VIS_0, \
  SV_DPM_VIS_1, \
  SV_DPM_DIST_LIST, /* DE29924 */ \
  SV_WALL_DIST, \
  SV_RTMP_0 /* DE59560  */

#define SV_DPM_LIST \
  SV_DPM_LEAN_LIST,\
  SV_VOLUME, SV_AREA,\
  SV_DPM_CELLSTEPS,\
  ADD_SV_VOLUME_2D SV_CENTROID,\
  SV_CENTROID_M1,\
  SV_CENTROID_SLIDE,\
  SV_ZERO_VOLUME_M1

#define DPM_SRC_LIST \
  SV_DPMS_MASS,\
  SV_DPMS_MOM_S,\
  SV_DPMS_MOM_AP,\
  SV_DPMS_WSWIRL_S,\
  SV_DPMS_WSWIRL_AP,\
  SV_DPMS_ENERGY,\
  SV_DPMS_ENERGY_AP,\
  SV_DPMS_TKE,\
  SV_DPMS_D,\
  SV_DPMS_O,\
  SV_DPMS_TKE_RUU,\
  SV_DPMS_TKE_RVV,\
  SV_DPMS_TKE_RWW,\
  SV_DPMS_TKE_RUV,\
  SV_DPMS_TKE_RVW,\
  SV_DPMS_TKE_RUW,\
  SV_DPMS_SPECIES,\
  SV_DPMS_SPECIES_AP,\
  EXPAND_NSPE_SV(DPMS_SURFACE_SPECIES),\
  EXPAND_NSPE_SV(DPMS_REACTION_RATE_POST),\
  EXPAND_PER_MAT_SV(DPMS_VAP_PER_MAT),\
  EXPAND_PER_MAT_SV(DPMS_DEVOL_PER_MAT),\
  EXPAND_PER_MAT_SV(DPMS_BURN_PER_MAT),\
  SV_DPMS_PDF_1,\
  SV_DPMS_PDF_2,\
  SV_DPMS_INERT,\
  SV_DPMS_PDF_1_AP,\
  SV_DPMS_PDF_2_AP,\
  SV_DPMS_INERT_AP,\
  SV_DPMS_EMISS,\
  SV_DPMS_ABS,\
  SV_DPMS_SCAT,\
  SV_DPMS_BURNOUT,\
  SV_DPMS_CONCENTRATION,\
  SV_DPM_P_LIQ,\
  SV_DPM_P_LIQ_G,\
  SV_DPM_P_LIQ_RG,\
  SV_DPM_VOF,   \
  SV_DPM_VOF_G, \
  SV_DPM_VOF_RG


#define DPM_SRC_DS_LIST \
  SV_DPMS_DS_MASS,\
  SV_DPMS_DS_MOM_S,\
  SV_DPMS_DS_MOM_AP,\
  SV_DPMS_DS_WSWIRL_S,\
  SV_DPMS_DS_WSWIRL_AP,\
  SV_DPMS_DS_ENERGY,\
  SV_DPMS_DS_ENERGY_AP,\
  SV_DPMS_DS_TKE,\
  SV_DPMS_DS_D,\
  SV_DPMS_DS_O,\
  SV_DPMS_DS_TKE_RUU,\
  SV_DPMS_DS_TKE_RVV,\
  SV_DPMS_DS_TKE_RWW,\
  SV_DPMS_DS_TKE_RUV,\
  SV_DPMS_DS_TKE_RVW,\
  SV_DPMS_DS_TKE_RUW,\
  SV_DPMS_DS_SPECIES,\
  SV_DPMS_DS_SPECIES_AP,\
  EXPAND_NSPE_SV(DPMS_DS_SURFACE_SPECIES),\
  EXPAND_PER_MAT_SV(DPMS_DS_VAP_PER_MAT),\
  EXPAND_PER_MAT_SV(DPMS_DS_DEVOL_PER_MAT),\
  EXPAND_PER_MAT_SV(DPMS_DS_BURN_PER_MAT),\
  SV_DPMS_DS_PDF_1,\
  SV_DPMS_DS_PDF_2,\
  SV_DPMS_DS_INERT,\
  SV_DPMS_DS_PDF_1_AP,\
  SV_DPMS_DS_PDF_2_AP,\
  SV_DPMS_DS_INERT_AP,\
  SV_DPMS_DS_EMISS,\
  SV_DPMS_DS_ABS,\
  SV_DPMS_DS_SCAT,\
  SV_DPMS_DS_BURNOUT

#define SV_DPMS_LIST \
  DPM_SRC_LIST,\
  SV_DPMS_EROSION,\
  SV_DPMS_EROSION_MDM,\
  SV_DPMS_ACCRETION, \
  SV_DPMS_EROSION_SHIELDING, \
  SV_DPMS_WALL_FORCE, \
  DPM_SRC_DS_LIST,\
  SV_UDM_I

/* @} dpm */

#endif /* _FLUENT_DPM_H */
