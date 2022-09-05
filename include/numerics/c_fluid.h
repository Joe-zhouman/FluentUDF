/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_C_FLUID_H
#define _FLUENT_C_FLUID_H

#include "dll.h"
#include "syn_turb.h"

#define UDF_MOTION_NAME_SIZE 128

typedef struct basis_vector_struct
{
  real i[3];
} Basis_Vector;

typedef struct vector_basis_struct
{
  Basis_Vector e[3];
} Vector_Basis;

typedef struct motion_spec_struct
{
  cxboolean is_moving;
  cxboolean is_superposed;
  cxboolean is_set;

  cxboolean accel_uptodate;                    /* used to allow acceleration update
            * once per timestep only */
  cxboolean is_moving_frame;

  real omega;
  real origin[3];
  real axis[3];
  real velocity[3];
  Profile omega_p;
  Profile origin_p[3];
  Profile axis_p[3];
  Profile velocity_p[3];
  real alpha[3];
  real accel[3];
  Vector_Basis b;
  Thread *t_relative;
  struct motion_spec_struct *relative;         /* motion specification relative
                                                * to thread */
  char udf_zmotion_name[UDF_MOTION_NAME_SIZE]; /* name for DEFINE_ZONE_MOTION udf */

} Motion_Spec;

typedef struct fan3d_struct
{
  cxboolean fan3dzone;
  real glo_origin[ND_ND];    /* 3D fan rotation axis origin*/
  real th;                 /*fan thickness*/
  real inrdia;                 /*fan inner diameter*/
  real outdia;                 /*fan outer diameter*/
  real Cm;                 /*fan inflection point*/
  real nt;                 /*fan test angular velocity*/
  real nr;                  /*fan operating angular velocity*/
  real test_temp;              /*fan test temperature*/
  cxboolean tan_source;           /*flag for tangential source*/
  cxboolean axial_source;         /*flag for axial source*/
  cxboolean radial_source;       /*flag for axial source*/
  /* cxboolean read_dp_from_file;       *flag for axial source*/
  cxboolean limit_flow;
  cxboolean fan_curve;
  real max_flow;
  real min_flow;
  real delP;
  int axials_method;       /*flag for axial source method*/
  real poly_order ;
  int curve_fit ;
  real ini_flow ;
  int rot_dir;
  int inlet_id, exit_id, shroud_id;
  real tr[ND_ND][ND_ND];
  real loc_origin[ND_ND];    /* 3D fan rotation axis origin*/
  real axis[ND_ND];
  /*Polynomial p_jump; */
  real *P;
  real *Q;
  real *Cp;
  int nrows;
} Fan3d_Var;

typedef struct premix_var_struct
{
  /* cache for unburned and burned quantities */
  real rho_u;
  real rho_b;
  real Cp_u;
  real T_u;
  real T_b;
  real tdiff_u;
  real delta_l;
  real rho_ratio;
} premix_var_t;

/* for Open Channel case in VOF  */

typedef struct oc_beach_dir_list_struct
{
  /* main variables */
  real ni, nj, nk;
  real xe, len;
  /* derived variables */
  real xs;
  real NV_VEC(fl_dir);
} oc_beach_dir_list;

typedef struct numerical_beach_struct
{
  /* Numerical Beach related variables */
  real wave_len, fs_level, bottom_level;
  real ni, nj, nk;
  int damp_type, len_spec;
  real xs, xe, len_factor;
  real damp_resist_lin, damp_resist_quad;

  real NV_VEC(fl_dir), NV_VEC(ht_dir);
  real damp_len, ht_liquid;
  cxboolean relative_damping;
#if RP_3D
  cxboolean multi_direct;
  int count;
  struct oc_beach_dir_list_struct *dir_list;
#endif
} Numerical_Beach;

struct tv_cell_struct
{
  cxboolean sources;    /* sources specified? */
  Profile **source_pointer/*[MAX_EQNS]*/; /* equation source terms */
  unsigned char *nsources_pointer/*[MAX_EQNS]*/;

  cxboolean fixedFlag;    /* sources specified? */
  cxboolean fixedCyl;   /* use local cylindrical coordinates for fixed velocity? */
  Profile   *fixed_pointer/*[MAX_EQNS]*/; /* equation fixed terms */

  /* ---------------------------- */

  real omega;     /* angular speed */
  real origin[3];   /* origin of axis of rotation */
  real axis[3];     /* axis of rotation (always specified as 3d) */
  real velocity[3];   /* translational velocity */
  real accel[3];                /* translational acceleration vector */
  real alpha[3];                /* angular acceleration vector */

  Motion_Spec mrf;              /* moving reference frame */
  Motion_Spec mgrid;            /* moving grid */
  Motion_Spec msolid;           /* moving solid */
  Motion_Spec msuperposed;      /* superposed motion, same as cell.omega, cell.velocity etc. */
  Motion_Spec lcmrf;            /* moving frame spec in local coordinates, for embedded moving mesh */
  Motion_Spec lcmgrid;          /* moving grid spec in local coordinates, for embedded moving mesh */
  Motion_Spec lcmsolid;

  cxboolean radiating;          /* participating in disco radiation */
  /*
   * fluid-specific variables
   */
  cxboolean laminar;    /* laminar "transitional" region? */
  cxboolean laminar_mut_zero; /* control of mu_t calculation within laminar zone. */

  /* embedded LES */
  cxboolean eles;     /* embedded les region? */
  int eles_spec;    /* embedded LES model  specification:
                                 * 0 = Smagorinsky
                                 * 1 = WALE
                                 * 2 = Dynamic Smagorinsky */
  int eles_mom_scheme;    /* embedded LES momentum scheme: * 0 = BCD * 1 = CD */
  real eles_const;    /* les model constant */
  real eles_smag_const;   /* les model Smagorinsky constant */
  real eles_wale_const;   /* les model WALE constant */
  real eles_Pr_wall;
  cxboolean eles_dyn_energy_flux;
  real eles_Pr_energy;
  cxboolean eles_dyn_scalar_flux;
  real eles_Sc_scalar;
  real eles_Sc_pdf;

  /* Synthetic turbulence */
#if RP_3D
  syn_turb_synthetic_turbulence_generator_type syn_turb_synthetic_turbulence_generator;
#endif

  /* Zonal compressive scheme specific */
  real mp_compressive_beta_max;

  /* glass modeling */
  cxboolean glass;

  /*
   * porous definition
   */
  Profile porosity;
  Profile area_density; /*Interfacial Area Density of porous material*/
  Profile heat_transfer_coeff; /*Heat Transfer Coeff of porous Material*/
  real surf_vol_ratio;    /* surface-volume ratio        */
  cxboolean electrolyte;        /* zone is electrolyte */
  cxboolean porous;   /* non-zero porous definition? */
  cxboolean non_equib_thermal;     /*Non Equilibrium Thermal Model for Porous Medium*/
  cxboolean rel_vel_resist; /* relative velocity resistance for moving porous media? */
  cxboolean resistp;    /* non-zero resist definition? */
  cxboolean C2p;    /* non-zero C2 definition? */
  cxboolean alt_inertial_form;  /* Alternative inertial formulation */
  cxboolean var_res;              /* non-constant resist specification? */
  int dual_zn_id;

  /* principle-axis definition */
  int porous_principle_n_axis;  /* number of axis specified (0,1,2) */
  Profile porous_principle_axis[ND_ND][ND_ND];
  Profile porous_principle_r[ND_3];
  Profile porous_principle_c[ND_3];


  /* multiphase porous medium  */
  cxboolean none;                    /* no relative permeability?  */
  cxboolean corey;                   /* 2-phase relative permeability?  */
  cxboolean stone_1;                 /* 3-phase relative permeability?  */
  cxboolean stone_2;                 /* 3-phase relative permeability?  */
  int wetting_phase;               /* wetting-phase for two-phase corey model*/
  int non_wetting_phase;           /* non-wetting-phase for two-phase corey model*/


  real res_sat_p1;          /* wetting phase residual saturation       */
  real res_sat_p2;          /* non-wetting phase residual saturation       */
  real res_sat_p3;          /* stone phase residual saturation       */

  real exponent_p1;         /* wetting phase corey model exponent            */
  real exponent_p2;         /* non-wetting phase corey model exponent     */
  real exponent_p3;         /* stone corey model exponent            */

  real ref_rel_perm_p1;     /* wetting phase reference relative permeability */
  real ref_rel_perm_p2;     /* non-wetting phase reference relative permeability */
  real ref_rel_perm_p3;     /* stone reference relative permeability */

  real van_genuchten_pg;
  real van_genuchten_ng;
  real skjaeveland_nw_pc_coef;
  real skjaeveland_nw_pc_pwr;
  real skjaeveland_wet_pc_coef;
  real skjaeveland_wet_pc_pwr;
  real brooks_corey_pe;
  real brooks_corey_ng;
  real lev_con_ang;
  real max_capillary_pressure;
  real rel_perm_limit_p1;
  real rel_perm_limit_p2;

  char cpt_name[PROP_UDF_NAME_LENGTH];
  char cpt_satw[PROP_UDF_NAME_LENGTH];
  char cpt_cap_press[PROP_UDF_NAME_LENGTH];


  int cap_method;
  char cap_udf_name[PROP_UDF_NAME_LENGTH];

  cxboolean rel_perm_tabular_p1;
  char rel_perm_table_p1[PROP_UDF_NAME_LENGTH];
  char rel_perm_satw_p1[PROP_UDF_NAME_LENGTH];
  char rel_perm_rp_p1[PROP_UDF_NAME_LENGTH];

#if 1
  cxboolean rel_perm_tabular_p2;
  char rel_perm_table_p2[PROP_UDF_NAME_LENGTH];
  char rel_perm_satw_p2[PROP_UDF_NAME_LENGTH];
  char rel_perm_rp_p2[PROP_UDF_NAME_LENGTH];
#endif


#if RP_3D
  /* conical porous media inputs */
  cxboolean conicalp;   /* conical porous media? */
  real cone_axis[ND_ND];  /* conical axis vector */
  real cone_axis_pt[ND_ND]; /* coordinates of point on axis of cone */
  real cone_angle;    /* angle of cone relative to its axis */
  Fan3d_Var fan3d ;            /*3d fan variables*/
#endif

#if RP_SHELL
  int nShellLayer;
  real dShell;
#endif

  /* raw cartesian matrices */
  real resist[ND_3][ND_3];  /* inverse-permeability coefficients */
  real C2[ND_3][ND_3];  /* inertial resistance coefficients */

  /* a "power law" model */
  real C0, C1;      /* power law coefficients */

  cxboolean react;            /* reaction is on/off at this thread */
  Reaction_Mech *react_mech;   /* reaction mechanism pointer at this thread */
  char *react_mech_name;       /* reaction mechanism name at this thread */
  real gasoline_flame_speed_f_t_u;/*Gasoline flame speed*/

  struct premix_var_struct premix_var; /* cached premixed combustion variables */

  /* cell zone specific boiling */
  cxboolean mp_boiling_zone;

  /* Numerical Beach related variables */
  cxboolean numerical_beach;
  struct numerical_beach_struct num_beach;

  cxboolean anisotropic_spe_diffusion;
  real spe_diff_matrix[ND_ND][ND_ND];

  cxboolean porous_structure;
  int *curv_coord_index;
  cxboolean ccs_assigned;
};

#define CELL_PROFILE_FIXED_BASE(_c) ((_c).fixed_pointer)
#define CELL_PROFILE_SOURCE_BASE(_c) ((_c).source_pointer)
#define CELL_PROFILE_NSOURCES_BASE(_c) ((_c).nsources_pointer)

#define CELL_PROFILE_FIXED(_c) (CELL_PROFILE_FIXED_BASE(_c)?            \
                                CELL_PROFILE_FIXED_BASE(_c):            \
                                (CELL_PROFILE_FIXED_BASE(_c) = (Profile*)CX_Calloc(MAX_EQNS, sizeof(Profile))))
#define CELL_PROFILE_SOURCE(_c) (CELL_PROFILE_SOURCE_BASE(_c)?          \
                                 CELL_PROFILE_SOURCE_BASE(_c):          \
                                 (CELL_PROFILE_SOURCE_BASE(_c) = (Profile**)CX_Calloc(MAX_EQNS, sizeof(Profile*))))
#define CELL_PROFILE_NSOURCES(_c) (CELL_PROFILE_NSOURCES_BASE(_c)?      \
                                   CELL_PROFILE_NSOURCES_BASE(_c):      \
                                   (CELL_PROFILE_NSOURCES_BASE(_c) = (unsigned char*)CX_Calloc(MAX_EQNS, sizeof(unsigned char))))

FLUENT_EXPORT cxboolean Global_Pseudo_Time_Method_Active_P(void);
FLUENT_EXPORT cxboolean Local_Pseudo_Time_Method_Active_P(void);

FLUENT_EXPORT cxboolean fixed_eqn_phase(Thread *, int eqn, int phase);
FLUENT_EXPORT cxboolean fixed_eqn(Thread *, int eqn);
FLUENT_EXPORT cxboolean fixed_all_phase(Thread *, int phase);
FLUENT_EXPORT cxboolean fixed_all(Thread *);
FLUENT_EXPORT cxboolean fixed_all_zero_p(Thread *);

FLUENT_EXPORT void radiation_sources(Domain *);
FLUENT_EXPORT void porous_sources(Domain *);
#if RP_2D
FLUENT_EXPORT void swirl_porous_sources(Domain *);
#endif
FLUENT_EXPORT void body_forces(Domain *);

#if RP_2D
FLUENT_EXPORT void axi_sources(Domain *);
#endif

FLUENT_EXPORT void Update_Cell_Zone_Motion(Domain *, real);
FLUENT_EXPORT void Init_Cell_Zone_Motion(Domain *);
FLUENT_EXPORT void Set_Cell_Zone_Motion(Thread *t);
FLUENT_EXPORT void Init_Thread_Frame_Basis(Thread *t);
FLUENT_EXPORT cxboolean Check_MRF_Mgrid_Coaxial(Thread *t);
FLUENT_EXPORT int Check_Any_MRF_Mgrid_Coaxial(Domain *d);
FLUENT_EXPORT void Frame_Acceleration_Forces(Domain *);
FLUENT_EXPORT cxboolean Thread_Motion_Equal(Thread *PTR_RESTRICT t1, Thread *PTR_RESTRICT t2);
FLUENT_EXPORT cxboolean Thread_Solid_Motion_Equal(Thread *PTR_RESTRICT t1, Thread *PTR_RESTRICT t2);

FLUENT_EXPORT cxboolean Is_User_Defined_Motion(Motion_Spec *m);

FLUENT_EXPORT void Report_Mspec(Motion_Spec *m, const char *name);

#if SEEM
FLUENT_EXPORT void cell_set_var(Thread *t, char *name, Pointer value);
#endif
FLUENT_EXPORT void thread_cell_default(Domain *domain, Thread *t);
FLUENT_EXPORT void thread_cell_update(Domain *domain, Thread *t);

FLUENT_EXPORT void Set_SVar_To_Min(Domain *domain, Svar sv, real epsilon);

/**
 * \brief Discretization routine for transient term in a scalar transport equation
 *
 * Calls routine Equation_Unsteady_Sources_CS"()" with transient parameters stored in domain pointer
 *
 * \param[in] domain    Global domain pointer
 * \param[in] sv_phi    Svar for equation
 * \param[in] sv_ap     Corresponding Ap SVar
 * \param[in] sv_s      RHS SVar
 * \param[in] sv_vof    Relevant in VOF computations, e.g. sv_vof
 * \param[in] sv_vof_m1 Last time step VOF, e.g. sv_vof_m1
 */
FLUENT_EXPORT void Equation_Unsteady_Sources(Domain *domain,
                                             Svar sv_phi,
                                             Svar sv_ap,
                                             Svar sv_s,
                                             Svar sv_vof,
                                             Svar sv_vof_m1);

/**
 * \brief Discretization routine for transient term in a scalar transport equation with custom/local transient parameters (LT)
 *
 * Discretization of transient term according to the time-scheme passed by the argument trans_params_local.
 *
 * \note Currently only different dt values w.r.t. to the global parameters in domain pointer are supported.
 *
 * \param[in] domain             Global domain pointer
 * \param[in] sv_phi             Svar for equation
 * \param[in] sv_ap              Corresponding Ap SVar
 * \param[in] sv_s               RHS SVar
 * \param[in] sv_vof             Relevant in VOF computations, e.g. sv_vof
 * \param[in] sv_vof_m1          Last time step VOF, e.g. sv_vof_m1
 * \param[in] trans_params_local Transient parameters for the call
 */
FLUENT_EXPORT void Equation_Unsteady_Sources_LT(Domain *domain,
                                                Svar sv_phi,
                                                Svar sv_ap,
                                                Svar sv_s,
                                                Svar sv_vof,
                                                Svar sv_vof_m1,
                                                TransientParameters *trans_params_local);

FLUENT_EXPORT void Pseudo_Transient_Sources(Domain *domain, Svar sv_v, int i, Svar sv_ap, Svar sv_source, real pseudo_time_step, cxboolean dpm_block);
FLUENT_EXPORT void Energy_Pseudo_Transient_Sources(Domain *domain, Svar sv_v, Svar sv_ap, Svar sv_source, real pseudo_time_step);
FLUENT_EXPORT void Energy_Pseudo_Transient_Sources_Porous_Melt(Domain *domain, Svar sv_v, Svar sv_ap, Svar sv_source, real pseudo_time_step);
FLUENT_EXPORT void Energy_PT_Sources(Domain *domain, Svar sv_v, Svar sv_ap, Svar sv_source, real pseudo_time_step);
FLUENT_EXPORT void potential_energy_sources(Domain *domain, Svar sv_v, Svar sv_ap, Svar sv_s);

FLUENT_EXPORT real relative_permeability(cell_t c, Thread *t, real *satw, real *rel_perm, int npts, cxboolean rp_tabular);

FLUENT_EXPORT cxboolean is_ph_thread_rel_perm_tabular(Thread *thread);
FLUENT_EXPORT void get_rel_perm_tab_info(Thread *thread, int *numpts, real **data_satw, real **data_rel_perm);

#if RP_NETWORK
FLUENT_EXPORT void thread_network_default(Domain *, Thread *);
#endif

/** save data contained in the rpvar into the spec of the threads */
FLUENT_EXPORT void Mspecs_From_RPvar(const char *spec, const char *varname);
/** return a list of threads spec satisfies cond */
FLUENT_EXPORT Pointer RPvar_From_Mspecs(const char *spec, const char *cond);
/** sync the motion spec value with host */
FLUENT_EXPORT void Sync_Mspec(Domain *domain, const char *spec);
FLUENT_EXPORT void Solid_MRF_Warning(Domain *domain);

#define C_R_SOLID(c,t)THREAD_PROP(t,PROP_rho,0)
#define C_K_SOLID(c,t)C_K_L(c,t)
#define C_CP_SOLID(c,t)THREAD_PROP(t,PROP_Cp,0)

/*====================================================================*/
/* For Dual Time Stepping formulation */
/*====================================================================*/
/** Defining constants */
#define EQN_NAME_STRING_SIZE 50
#define EQN_RPVAR_STRING_SIZE 30
#define RPVAR_STRING_SIZE 100
/** Equation specific dual time-stepping parameters struct */
typedef struct eqn_dual_time_stepping_param_
{
  Svar sv;                      /**< equation Svar of solution variable */
  cxboolean eqn_specific;       /**< flag to determine if dual time-stepping (dualts) is applied to this equation */
  cxboolean limit_eff_omega;    /**< flag to determine if limiting of effective implicit relaxation factor (omega) is needed */
  real omega_min;               /**< minimum omega for verbosity */
  real omega_max;               /**< maximum omega for verbosity */
  real omega_eff_min;           /**< minimum user specified effective omega if limiting of omega is on */
  real omega_eff_max;           /**< miximum user specified effective omega if limiting of omega is on */
  real dtau_scale;              /**< pseudo time-step scaling factor */
  int verbosity;                /**< flag for verbosity */
  void (*print_verbosity)(Svar sv_eqn, real omg_min, real omg_max); /**< print verbosity function */
} Eqn_DualTimeStepping_Param;

/** Generic dual time-stepping parameters struct */
typedef struct dual_time_stepping_param_
{
  cxboolean dualtime_on;             /**< flag to determine if dual time-stepping formulation is on */
  Svar sv_dtau;                      /**< Svar of pseudo time-step */
  Svar sv_at_tau;                    /**< Svar of pseudo time coefficient */
  real cfl_dtau;                     /**< pseudo-time courant number */
  const char *cfl_method;            /**< flag to determine if DBNS or PBNS function is used for computing the pseudo time-step */
  real cflvnn;                       /**< ratio between advection (CFL) and diffusion (VNN) stability conditions, = CFL/VNN, used in PBNS cfl-method */
  real cARcutoff;                    /**< Aspect ratio (AR) cutoff for CASM-like algorithm */
  real solid_dtau_scale;             /**< scaling factor for the pseudo time-step in solid zones */
  cxboolean solid_zones_specific;    /**< flag to determine if dual time stepping is active for solid-zones */
  cxboolean use_prec_vel;            /**< flag to determine if preconditioned velocity should be used to compute the time-step */
  cxboolean converg_accelerate_stretch_mesh; /**< flag to determine the usage of the casm algorithm for stretched meshes */
  cxboolean use_visc_scale;          /**< flag to determine if viscous scale is used in computing pseudo time-step in PBNS cfl-method */
  cxboolean use_cellAR;              /**< flag to determine if scaling by AR is needed, in PBNS cfl-method */
  cxboolean compute_dtau_every_iter; /**< flag to determine if computing pseudo time-step each subiteration is needed */
  cxboolean rm_atau_localresid;      /**< flag to determine if dualts coefficient is included in ap for local scaling of residuals */
  cxboolean use_explicit_relax;        /**< flag to determine the mode of relaxation for the segregated solver */
  cxboolean use_coupled_explicit_relax;  /**< flag to determine the mode of relxation for the coupled solver, assuming momentum is always explicitly relaxed */
  cxboolean relax_drhodt; /**< flag to determine if pseudo time-step relaxation should be added in the compressible continuity for drhodt */
  int verbosity;                     /**< flag for verbosity */
  void (*compute_local_pseudo_time_step)(Domain *domain, real cfl, real cfl_solid);  /**< function pointer to compute pseudo time-step function */
} DualTimeStepping_Param;

/** enum for time-stepping method */
typedef enum
{
  UNDEFINED_TIME_STEPPING_METHOD,
  FIRST_ORDER_IMPLICIT_TIME,
  FIRST_ORDER_IMPLICIT_DUAL_TIME,
  SECOND_ORDER_IMPLICIT_TIME,
  SECOND_ORDER_IMPLICIT_DUAL_TIME,
  FIRST_ORDER_IMPLICIT_PSEUDO_TIME,
  STEADY_UNDERRELAXED_METHOD
} Time_Stepping_Method;

typedef enum
{
  DUAL_LIMIT_DT_EQUATION_BASED = 0,
  DUAL_LIMIT_DT_ALL_EQUATIONS = 1,
  DUAL_LIMIT_DT_FLOW_ONLY = 2,
  DUAL_LIMIT_DT_SCALARS_ONLY = 3,
  DUAL_LIMIT_DT_FLOW_AND_SCALARS = 4  
} Dual_Time_Step_Size_Limit_Method;

typedef enum
{
  DUAL_DT_AND_RELAXATION = 0,
  DUAL_DT_BOUNDED_EFFECTIVE_RELAXATION = 1,
  DUAL_DT_NO_ADDITIONAL_RELAXATION = 2
} Dual_Time_Step_Relaxation_Treatment;

/** Struct to hold equation relevant coeff, source, and solution vars at different time levels */
typedef struct
{
  Svar Xn, Xm1, Xm2;
  Svar Ap;
  Svar S;
} Equation_Svars;

/** Generic temporal data structure, should be encompassed/combined with Transient_Parameters struct */
typedef struct
{
  Time_Stepping_Method time_method; /**< time-stepping method enum */
  Svar sv_at, sv_at_m1, sv_at_m2;   /**< temporal coefficients Svars*/
  real phys_dt;                     /**< physical fixed time-step */
  DualTimeStepping_Param pseudo_p;  /**< generic dual time-stepping/pseudo-transient data struct */
} Temporal_Param;

/**Equation specific temporal data structure */
typedef struct
{
  Time_Stepping_Method time_method;    /**< time-stepping method enum */
  Svar sv_at, sv_at_m1, sv_at_m2;      /**< temporal coefficients Svars*/
  real phys_dt;                        /**< physical fixed time-step */
  Eqn_DualTimeStepping_Param pseudo_p; /**< equation specific dual time-stepping/pseudo-transient data struct */
} Temporal_Eqn_Param;

/** Equation data structure, need to be expanded to include several parameters for each equation */
typedef struct Equation_Param_
{
  Equation_Svars sv;         /**< equation relevant solution Svars for temporal computations */
  char name[EQN_NAME_STRING_SIZE];                /**< equation name, also can be used for verbosity printing */
  char rpvar_str[EQN_RPVAR_STRING_SIZE];           /**< equation rpvar string identifier for reading equation based rpvars */
  real omega;                /**< implicit relaxation factor */
  real urf;                  /**< explicit relaxation factor */
  int cpld_index;            /**< for coupled equations */
#if 0
  Temporal_Eqn_Param time_p; /**< We can have equation specific temporal parameters in the future  */
  and then the equation dualtime parameters can be one of its members * /
#endif
  Eqn_DualTimeStepping_Param pseudo_p;  /**< data structure for equation specific pseudo-time formulations */
} Equation_Param;

/**
 * \brief Generic function pointer for filling/assembling AMG/BAMG
 * \details This pointer has the following capabilities:
 *          1-Computation of unsteady equation terms in both Ap and S coefficients
 *          2-Under-relaxation of the equations
 *          3-Fill/Assemble of the AMG or BAMG systems
 *          4-Works for both steady and unsteady cases
 * \param[in] *domain: domain pointer
 * \param[in] time_param_: generic temporal data structure
 * \param[in] eqn_param_: equation specific parameters
 */
typedef void (*Compute_Fill_Equation_Time_Coeff_Sources)(Domain *domain, Temporal_Param time_param_, Equation_Param eqn_param_);

/**
 * \brief Specializations of Compute_Fill_Equation_Time_Coeff_Sources for steady formulations
 */
FLUENT_EXPORT void Steady_Underrelaxed_Equation_Terms_SP(Domain *domain, Temporal_Param time_param_, Equation_Param eqn_param_);
FLUENT_EXPORT void First_Order_Implicit_Pseudo_Time_SP(Domain *domain, Temporal_Param time_param_, Equation_Param eqn_param_);
FLUENT_EXPORT void First_Order_Implicit_Time_SP(Domain *domain, Temporal_Param time_param_, Equation_Param eqn_param_);
FLUENT_EXPORT void First_Order_Implicit_Dual_Time_SP(Domain *domain, Temporal_Param time_param_, Equation_Param eqn_param_);
FLUENT_EXPORT void Second_Order_Implicit_Time_SP(Domain *domain, Temporal_Param time_param_, Equation_Param eqn_param_);
FLUENT_EXPORT void Second_Order_Implicit_Dual_Time_SP(Domain *domain, Temporal_Param time_param_, Equation_Param eqn_param_);

/**
 * \brief Discretization routines for dual time terms in a scalar transport equation
 * \details these functions follows the old workflow and applies Dual time stepping to cell Ap
 * \param[in] domain    Global domain pointer
 * \param[in] sv_phi    Svar for equation
 * \param[in] sv_ap     Corresponding Ap SVar
 * \param[in] sv_s      RHS SVar
 * \param[in] sv_dual_dt Svar for cell-wise dual time array
 * \param[in] eqn_dualts_param struct of dual time-stepping equation specific parameters
 */
FLUENT_EXPORT void Energy_Dual_Time_Sources(Domain *domain, Svar sv_v, Svar sv_ap, Svar sv_source, Svar sv_dual_dt,
                                            Eqn_DualTimeStepping_Param eqn_dualts_param);
FLUENT_EXPORT void Dual_Time_Sources(Domain *domain, Svar sv_v, int i, Svar sv_ap, Svar sv_source, Svar sv_dual_dt,
                                     Eqn_DualTimeStepping_Param eqn_dualts_param);
/**
 * \brief Utility function for updating equation specific parameters
 */
FLUENT_EXPORT void Update_Eqn_Param(Svar sv, real omega, real urf, Equation_Param *);
/**
 * \brief Utility function for updating generic temporal parameters
 */
FLUENT_EXPORT void Update_Temporal_Param(Temporal_Param * );
/**
 * \brief Utility function for updating equation-specific temporal parameters
 */
FLUENT_EXPORT void Update_Eqn_Temporal_Param(Svar sv, Temporal_Eqn_Param * );
/**
 * \brief Utility function for updating equation-sepcific dual time-stepping parameters
 */
FLUENT_EXPORT void Update_Eqn_DualTimeStepping_Param(Svar sv, Eqn_DualTimeStepping_Param *);
/**
 * \brief Utility function for updating generic dual time-stepping parameters
 */
FLUENT_EXPORT void Update_DualTimeStepping_Param(DualTimeStepping_Param * );
/**
 * \brief Utility function for printing verbosity of equation-specific dual time-stepping
 */
FLUENT_EXPORT void Print_Eqn_Effective_URF_Verbosity(Svar sv, real omega_min, real omega_max);
/**
 * \brief Utility function to parse the approperiate implicit relaxation factor based on models and formulations
 */
FLUENT_EXPORT real Get_Eqn_Implicit_Relax_Factor(Svar sv);
/**
 * \brief Utility function to parse the approperiate explicit relaxation factor based on models and formulations
 */
FLUENT_EXPORT real Get_Eqn_Explicit_Relax_Factor(Svar sv);

/****************************************************************/
/*                          MACROS                              */
/****************************************************************/
/**
 * \brief Macro for limiting the effective relaxation
 * \param[in] ap: Equation Ap including transient terms
 * \param[in] omega_min: minimum under-relaxation factor
 * \param[in] omega_max: maximum under-relaxation factor
 * \param[in,out] atau: pseudo-time coefficient to be adjusted/limited
 */
#define ADJUST_PSEUDO_TIME_COEFF(ap, omega_imp, omega_min, omega_max, atau)\
{\
  Dual_Time_Step_Relaxation_Treatment dts_relaxtion_method = (Dual_Time_Step_Relaxation_Treatment) dual_time_stepping_implicit_relax_type; \
  if(omega_imp>REAL_MIN)\
  {\
    if(dts_relaxtion_method==DUAL_DT_BOUNDED_EFFECTIVE_RELAXATION) \
    { \
       real omega_eff = ABS((ap) / ( (ap) + (atau) )); \
       real omega_eff_limited = MINMAX((omega_eff), (omega_min), (omega_max)); \
       omega_eff_limited = MINMAX(omega_eff_limited, 0.0, 1.0); \
       atau = (omega_eff_limited>REAL_MIN)? -(fabs(ap) *(1.0 - omega_eff_limited)/omega_eff_limited) : -fabs(atau); \
    } \
    else if(dts_relaxtion_method==DUAL_DT_AND_RELAXATION)\
    { \
     real omega_eff_1 = (omega_imp) * ABS((ap) / ( (ap) + (atau) )); \
     real omega_eff = MINMAX((omega_eff_1), (omega_min), (omega_max)); \
     atau = ((omega_imp)/(omega_eff)>1.0)? -fabs(ap) *((omega_imp)/(omega_eff) - 1.) : (atau); \
    } \
  }\
  else\
  {\
   atau = 0.0;\
  }\
}
/**
 * \brief Macro for the specialization of Compute_Fill_Equation_Time_Coeff_Sources function pointer
 * \param[in] time_method: time-stepping method
 * \param[in,out] func_ptr:    function pointer specialization
 */
#define ASSIGN_COMPUTE_FILL_TEMPORAL_COEFF_SOURCES_FUNCTION(time_method, func_ptr)\
{\
  if (time_method == FIRST_ORDER_IMPLICIT_TIME) \
    func_ptr = First_Order_Implicit_Time_SP; \
  else if (time_method == FIRST_ORDER_IMPLICIT_DUAL_TIME) \
    func_ptr = First_Order_Implicit_Dual_Time_SP; \
  else if (time_method == SECOND_ORDER_IMPLICIT_TIME) \
    func_ptr = Second_Order_Implicit_Time_SP; \
  else if (time_method == SECOND_ORDER_IMPLICIT_DUAL_TIME) \
    func_ptr = Second_Order_Implicit_Dual_Time_SP; \
  else if (time_method == FIRST_ORDER_IMPLICIT_PSEUDO_TIME) \
    func_ptr = First_Order_Implicit_Pseudo_Time_SP; \
  else if (time_method == STEADY_UNDERRELAXED_METHOD) \
    func_ptr = Steady_Underrelaxed_Equation_Terms_SP; \
  else \
    func_ptr = NULL; \
}

/**
 * \brief Macro to fill/assemble segeregated AMG system and under-relax equation Ap, S
 * \param[in] c: cell index
 * \param[in] tc: thread index
 * \param[in] phi: real value of cell-centered solution
 * \param[in] ap_: Ap coefficient
 * \param[in] b_src_: Source coefficient including unsteady and pseudo-time terms
 * \param[in] omega_imp_: implicit relaxation factor
 */
#define FILL_EQN_A_X_B_SCALAR(c,tc,phi_,ap_,b_src_,omega_imp_)\
{\
  int index = C_INDEX((c),(tc)); \
  real ap_tot_ = (ap_)/(omega_imp_); \
  AMG_X(index) =  (phi_); \
  AMG_D(index) = (ap_tot_); \
  AMG_B(index) = - (b_src_); \
  AMG_CHILD(index) = NULL_INDEX; \
  /* if receptor set child index == 0*/ \
  if (OVERSET_RECEPTOR_CELL_P((c), (tc)))\
  {\
    AMG_X(index) = CHILD_NONE; \
    AMG_ZERO_OD(index); \
    AMG_D(index) = -1.0; \
    AMG_B(index) = 0.0; \
  }\
}

#define FILL_EQN_A_X_B_SCALAR_LEVELFORM(c,tc,phi_,ap_,b_src_,axM_,omega_imp_)\
{\
  int index = C_INDEX((c), (tc)); \
  real ap_tot_ = (ap_)/(omega_imp_); \
  AMG_X(index) = (phi_); \
  AMG_D(index) = (ap_tot_); \
  AMG_B(index) = - ((b_src_)  - (ap_tot_) * (phi_) * ( 1. - (omega_imp_) ) - (axM_)); \
  AMG_CHILD(index) = NULL_INDEX; \
  /* if receptor set child index == 0*/ \
  if (OVERSET_RECEPTOR_CELL_P((c), (tc)))\
  {\
    AMG_X(index) = CHILD_NONE; \
    AMG_ZERO_OD(index); \
    AMG_D(index) = -1.0; \
    AMG_B(index) = 0.0; \
  }\
}

/**
 * \brief Macro to fill/assemble coupled BAMG system and under-relax equation Ap, S
 * \param[in] c: cell index
 * \param[in] tc: thread index
 * \param[in] cpld_dir: coupled system index of equation
 * \param[in] phi: real value of cell-centered solution
 * \param[in] ap_: Ap coefficient
 * \param[in] b_src_: Source coefficient including unsteady and pseudo-time terms
 * \param[in] omega_imp_: implicit relaxation factor
 */

#define FILL_EQN_A_X_B_COUPLED(c,tc,cpld_dir,phi_,ap_,b_src_,omega_imp_)\
{\
  int index = C_INDEX((c), (tc)); \
  real ap_tot_ = (ap_)/(omega_imp_); \
  BAMG_X(AMG_PVT,index)[cpld_dir] =  (phi_);\
  MATRIX(BAMG_D(AMG_PVT, index), cpld_dir, cpld_dir, BAMG_BLK_SIZE(AMG_PVT)) = (ap_tot_);\
  BAMG_B(AMG_PVT,index)[cpld_dir] += - (b_src_); \
  SAMG_CHILD(AMG_PVT, index) = NULL_INDEX;\
  /* if receptor set child index == 0*/ \
  if (OVERSET_RECEPTOR_CELL_P((c), (tc))) \
  {\
    SAMG_CHILD(AMG_PVT, index) = CHILD_NONE; \
    /*     BAMG_ZERO_OD(AMG_PVT,index,dir);  */ \
    MATRIX(BAMG_D(AMG_PVT, index), (cpld_dir), (cpld_dir), BAMG_BLK_SIZE(AMG_PVT)) = -1.0; \
    BAMG_B(AMG_PVT, index)[(cpld_dir)] = 0.0; \
  }\
}

#define FILL_EQN_A_X_B_COUPLED_LEVELFORM(c,tc,cpld_dir,phi_,ap_,b_src_,axM_,omega_imp_)\
{\
  int index = C_INDEX((c),(tc)); \
  real ap_tot_ = (ap_)/(omega_imp_); \
  BAMG_X(AMG_PVT,index)[(cpld_dir)] =  (phi_);\
  MATRIX(BAMG_D(AMG_PVT, index), (cpld_dir), (cpld_dir), BAMG_BLK_SIZE(AMG_PVT)) = (ap_tot_);\
  BAMG_B(AMG_PVT,index)[cpld_dir] += - ( (b_src_) - ( (ap_tot_) * (phi_) * ( 1. - (omega_imp_) ) ) - (axM_) ); \
  SAMG_CHILD(AMG_PVT, index) = NULL_INDEX;\
  /* if receptor set child index == 0*/ \
  if (OVERSET_RECEPTOR_CELL_P((c), (tc))) \
  {\
    SAMG_CHILD(AMG_PVT, index) = CHILD_NONE; \
    /*     BAMG_ZERO_OD(AMG_PVT,index,dir);  */ \
    MATRIX(BAMG_D(AMG_PVT, index), (cpld_dir), (cpld_dir), BAMG_BLK_SIZE(AMG_PVT)) = -1.0; \
    BAMG_B(AMG_PVT, index)[(cpld_dir)] = 0.0; \
  }\
}

#endif /* _FLUENT_C_FLUID_H */
