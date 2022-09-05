/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/

#ifndef _FLUENT_DPM_TYPES_H
#define _FLUENT_DPM_TYPES_H

#include "global.h"
#include "dpm.h"
#include "mem.h"
#include "prop.h"
#include "surf.h"
#include "cudf.h"   /* UDF_Cache_Data */
#include "random.h"
#include "file_tools.h"

/* particle types */
#define DPM_TYPE_MASSLESS            0
#define DPM_TYPE_INERT               1
#define DPM_TYPE_DROPLET             2
#define DPM_TYPE_DROPLET_2_PHASE     3
#define DPM_TYPE_COMBUSTING          4
#define DPM_TYPE_CUSTOM              5
#define DPM_TYPE_PDF_TRANSPORT       6
#define DPM_TYPE_WALL_FILM           7
#define DPM_TYPE_MULTICOMPONENT      8
#define DPM_MAX_TYPES                9

/* particle drag laws */
#define DPM_DRAG_SPHERICAL    0
#define DPM_DRAG_NONSPHERICAL 1
#define DPM_DRAG_STOKES       2
#define DPM_DRAG_HIGH_MACH_NUMBER 3
#define DPM_DRAG_SPRAY_SUITE  4
#define DPM_DRAG_USER         5
#define DPM_DRAG_WEN_YU       6
#define DPM_DRAG_GIDASPOW     7
#define DPM_DRAG_ISHIIZUBER   8
#define DPM_DRAG_GRACE        9
#define DPM_DRAG_SYAMLAL_OBRIEN 10
#define DPM_DRAG_NONE         11
#define DPM_DRAG_MULTIPLE    12
#define DPM_DRAG_HUILIN_GIDASPOW 13
#define DPM_DRAG_GIBILARO        14
#define DPM_DRAG_EMMS            15
#define DPM_DRAG_FILTERED        16

/* particle rotational drag laws */
#define DPM_DRAG_ROT_DENNIS  17
#define DPM_DRAG_ROT_USER    18

/* particle rotational lift (RL) laws */
#define DPM_RL_OESTERLE  0
#define DPM_RL_TSUJI     1
#define DPM_RL_RUBINOW   2
#define DPM_RL_NONE      3
#define DPM_RL_USER      4

/* heat/mass transfer law types */
#define DPM_LAW_NULL                    0
#define DPM_LAW_INITIAL_INERT_HEATING   1
#define DPM_LAW_VAPORIZATION            2
#define DPM_LAW_BOILING                 3
#define DPM_LAW_DEVOLATILIZATION        4
#define DPM_LAW_SURFACE_COMBUSTION      5
#define DPM_LAW_FINAL_INERT_HEATING     6
#define DPM_LAW_MULTICOMPONENT_EVAP     7
#define DPM_LAW_USER_1                  8
#define DPM_LAW_USER_2                  9
#define DPM_LAW_USER_3                 10
#define DPM_LAW_CONDENSATION           11
#define DPM_MAX_LAWS                   12
#define DPM_NULL_SPECIES_INDEX -1

#define DPM_LAW_MULTICOMPONENT DPM_LAW_MULTICOMPONENT_EVAP  /* backward compatibility for UDFs */

/** Reporting types */
#define NO_DPM_REPORT        -1
#define STEP_BY_STEP_SCREEN   1
#define STEP_BY_STEP_FILE     2
#define SUMMARY_SCREEN        3
#define SUMMARY_FILE          4
#define SORT_FILE             5


#define COMBUSTING_FRACTIONS 4 /* volatiles fraction, char fraction, 
          fraction of volatiles remaining for Kobayashi devolatilization model,
                fraction Dv/Dinit where Dv particle diameter at the beginning of Devolatilization Law
                                  Dinit == init_state.diam */
enum film_prop
{
  NUMBER_Re = PROP_ktc + 1,
  NUMBER_Nu,
  NUMBER_Pr,
  MAX_FILM_PROP
};

enum vapor_prop
{
  NUMBER_Sc = 0,
  NUMBER_Sh,
  NUMBER_Le,
  NUMBER_phi,
  VAPOR_PROP_Cp,
  VAPOR_PROP_binary_diffusivity,
  MAX_VAPOR_PROP
};

typedef enum
{
  HTC_CONSTANT = 0,
  NU_RANZ_MARSHALL = 1,
  NU_CONSTANT,
  NU_GUNN,
  NU_HUGHMARK,
  NU_TOMIYAMA,
  HTC_USER,
  HTC_NONE
} Htc_Corr;

typedef enum
{
  INJECTION_SURFACE,
  INJECTION_SINGLE,
  INJECTION_GROUP,
  INJECTION_CONE,
  INJECTION_PLAIN_ORIFICE,
  INJECTION_PRESSURE_SWIRL,
  INJECTION_AIR_BLAST,
  INJECTION_FLAT_FAN,
  INJECTION_EFFERVESCENT,
  INJECTION_MATRIX,
  INJECTION_FILE,
  INJECTION_POINT_CONE,
  INJECTION_HOLLOW_CONE,
  INJECTION_RING_CONE,
  INJECTION_SOLID_CONE,
  INJECTION_PDF_TRANSPORT,
  INJECTION_FUNCTION,
  INJECTION_PARALLEL,
  INJECTION_VOLUME,
  INJECTION_CONDENSATE,
  INJECTION_TYPE_MAX
} Injection_Type;

typedef enum
{
  PARTICLE_VARIABLE_INVALID = -4,
  PARTICLE_CELL_VIS_1 = -3,
  PARTICLE_CELL_VIS_0 = -2,
  PARTICLE_CELL_FUNCTION = -1,
  PARTICLE_RESIDENCE_TIME = 0,
  PARTICLE_ID,
  SURFACE_ID,
  PARTICLE_X_POSITION,
  PARTICLE_Y_POSITION,
  PARTICLE_RADIAL_POSITION,
  PARTICLE_Z_POSITION,
  PARTICLE_THETA_POSITION,
  PARTICLE_X_VELOCITY,
  PARTICLE_Y_VELOCITY,
  PARTICLE_RADIAL_VELOCITY,
  PARTICLE_Z_VELOCITY,
  PARTICLE_SWIRL_VELOCITY,
  PARTICLE_VELOCITY_MAG,
  PARTICLE_DIAMETER,
  PARTICLE_DENSITY,
  PARTICLE_CP,
  PARTICLE_BINARY_DIFFUSIVITY,
  PARTICLE_MASS,
  PARTICLE_TEMPERATURE,
  PARTICLE_LAW_INDEX,
  PARTICLE_BREAKUP_TYPE,
  PARTICLE_ON_WALL,
  PARTICLE_RE,
  PARTICLE_TIME_STEP,
  LIQUID_VOLUME,
  LIQUID_MASS,
  VOLATILE_MASS,
  CHAR_MASS,
  BOILING_POINT,
  LATENT_HEAT,
  LIMITING_TIME,
  PARTICLE_NUMBER_IN_PARCEL,
  PARTICLE_WEBER_NUMBER_GAS,
  PARTICLE_WEBER_NUMBER_LIQUID,
  PARTICLE_LEWIS_NUMBER,
  PARTICLE_NUSSELT_NUMBER,
  MASS_TRANSFER_NUMBER_BM,
  HEAT_TRANSFER_NUMBER_BT,
  PARTICLE_TS,
  PARTICLE_NO_REFINEMENT,
  PARTICLE_PENETRATION,
  PARCEL_MASS,
  PARCEL_DIAM,
  FORCE_X_TOTAL,
  FORCE_Y_TOTAL,
  FORCE_Z_TOTAL,
  FORCE_TOTAL_MAG,
  FORCE_X_COLL,
  FORCE_Y_COLL,
  FORCE_Z_COLL,
  FORCE_COLL_MAG,
  ACC_X_TOTAL,
  ACC_Y_TOTAL,
  ACC_Z_TOTAL,
  ACC_TOTAL_MAG,
  PARTICLE_OMEGA_X,
  PARTICLE_OMEGA_Y,
  PARTICLE_OMEGA_Z,
  PARTICLE_OMEGA_MAG,
  PARTICLE_CURRENT_TIME,
  PARTICLE_VARIABLE_MAX
} Particle_Variable_ID;

typedef enum
{
  TAB_DISPLACEMENT = 0,
  TAB_VELOCITY,
  WAVE_BREAKUP_TIME,
  WAVE_MASS_IN_SHED_DROPS,
  WAVE_SHED_DROPS_CUTOFF_MASS,
  KHRT_BREAKUP_TIME,
  PILCH_ERDMAN_DEFORMATION_TIME,
  PILCH_ERDMAN_BREAKUP_TIME,
  PILCH_ERDMAN_TOTAL_BREAKUP_TIME,
  PILCH_ERDMAN_INITIAL_WEBER_NUMBER,
  PILCH_ERDMAN_INITIAL_DIAMETER,
  MADABHUSHI_COLUMN_BREAKUP_TIME
} Spray_Suite_ID;

typedef enum
{
  PATH_END,
  PATH_FINAL_STEP,
  PATH_ACTIVE,
  PATH_BREAK,
  PATH_ABORT,
  PATH_STOP,
  PATH_NON_LOCAL_PERIODIC,
  PATH_NON_LOCAL_OVERSET,
  PATH_NON_LOCAL_GTI,
  PATH_NON_LOCAL,
  PATH_REINJECT,
  PATH_MAX_STATUS
} Path_Status;

#define DPM_COLLISION_PARTNER_NAME_LENGTH 128
#define DPM_COLLISION_LAW_NAME_LENGTH 128

typedef enum
{
  BREAKUP_NULL = -1,
  BREAKUP_NONE,
  BREAKUP_LEVICH,
  BREAKUP_TAB,
  BREAKUP_WAVE,
  BREAKUP_KHRT,
  BREAKUP_SSD,
  BREAKUP_MADABHUSHI,
  BREAKUP_SCHMEHL,
  BREAKUP_MAX
} Breakup_Type;

typedef enum
{
  DURING_TRACKING = 0,
  DURING_UPDATE,
  PRE_TRACKING,
  PRE_TIMESTEP,
  POST_TRACKING,
  POST_TIMESTEP,
  COLLISION_MODE_MAX
} Collision_Mode;

typedef enum
{
  FATE_INCOMPLETE = 0,   /* keep this first, so that we can skip it under certain conditions by starting the loop after this */
  FATE_TRANSFORMED,      /* ...e.g. in model-transition (DPM-to-VOF), secondary break-up, LWF stripping...
                          * If this can appear, "incomplete" probably will / cannot. This fate can, at least
                          * in the first part of the summary, appear just as a parcel count without any further
                          * information. Keep it out of the "real" list; but I cannot have it at the end of it
                          * because the code first loops over all "real" fates and then over all boundaries,
                          * and I don't want to change that because users / customers are used to it that way.
                          */
  FATE_LOST,             /* lost in migration or relocalization, e.g. for sliding / moving / deforming mesh,
                          * or even during data writing or reading...
                          */
  FATE_ABORTED,          /* rarely used, just in certain situations that somehow cannot continue to track */
  FATE_EVAPORATED,       /* particle mass has (at least almost, for numerical inaccuracy) completely vanished */
  FATE_ABSORBED,         /* ...into an Eulerian wall film... */
  /* Following 4 (four) fates not used in default print_dpm_summary. */
  /* INFLUID & INFILM denote unsteady particles currently in the domain.
   * These need to be updated at times before a summary is produced.
   */
  FATE_INFLUID,    /* This word is used elsewhere for the first "non-standard" fate...! */
  FATE_INFILM,
  FATE_DELETED,    /* When an injection is deleted, particles go to this fate: */

  /* Following is summarised thread-wise... */
  FATE_ESCAPED,    /* also includes trapped in most cases */
  FATE_REINJECT,
  FATE_BC_UDF,
  FATE_TRAPPED,    /* Used in DPM per-injection summaries ONLY,
                    * AND ONLY if per-injection thread summaries are OFF! */
  FATE_INSERTED,   /* INSERTED holds particles created by "Spawn_Particle()" etc.
                    * This word is used elsewhere for the first "non-regular" fate..
                    */
  FATE_INJECTED,   /* INJECTED holds all newly injected particles, for balancing. */
  FATE_MAX
} Particle_Fate;

typedef enum
find_bndry_face_err_code_e
{
  FIND_FACE_ERROR,
  FIND_FACE_SUCCESS,
  FIND_FACE_ERR_CODE_MAX
}
Find_Face_Err_Code;

typedef enum
{
  NONE_MODEL = 0,
  CONSTANT_NUMBER,
  CONSTANT_MASS,
  CONSTANT_DIAMETER
} Parcel_Model;

/* non-premixed model streams */
enum
{
  PRIMARY,
  SECONDARY,
  INERT
};

typedef struct plane_struct
{
  real   norm[5][3];
  float  pt[5][3];
  real   current_side;
  real   d[5];          /* distance from origin */
  cxboolean valid;      /* plane has faces on compute node */
  cxboolean bounded;    /* additional checks are done */
  char   *sort_file_name;
  FILE   *sort_file;
  struct plane_struct *next;
} Plane;

typedef struct common_par
{
  int max_steps;                                         /* max steps per particle */
  int backwards;                                         /* reverse? */
  int skip;
  int oil_flow;                                          /* oil_flow pathlines? */
  int high_res_oil_flow;                                 /* track oil flow pathlines on surface? */
  int nzone;                                             /* for oil flow */
  int *on_zone;
  int display;                                           /* display tracks? */
  int cphase_interaction;                                /* particles interact with the fluid phase? */
  int report;                                            /* report type */
  Plane *plane;                                          /* probe planes */
} common_parameters_t;

typedef struct user_particle_vars_t
{
  char name[DPM_NAME_LENGTH];
  char label[DPM_NAME_LENGTH];
  char units[DPM_NAME_LENGTH];
  char *vector_name;
  char vector_component;
} User_Particle_Vars;

/* particle_state_struct contains those attributes of the particle that we need
   both at the current time and at the time of entry in the current cell. all
   other attributes are stored in the particle struct */
typedef struct reacting_particle_state_struct
{
  real *species_mass;        /* multiple char reactions model: total species mass depleted or produced kg */
  real cohreadm;             /* multiple char reactions model: total heat of reaction evolved up to time t, J */
  real *reaction_rate_dt;    /* multiple char reactions model: total solid species mole depleted or produced by reaction i */
} reacting_particle_state_t;

typedef struct particle_state_struct
{
  real pos[3];
  real V[3];
  real diam;
  real rho;
  real mass;
  real temp;
  real time;
  real lmf;                  /* liquid mass fraction for droplet and wet-combustion */
} particle_state_t;

typedef struct cphase_state_struct
{
  real V[3];                    /* Velocity interpolated to the particle location */
  real V_ensemble[3];           /* Ensemble average gas velocity (cloud model) */
  real DelV[3][3];
  real curlV[3];
  real radius;                  /* radius of cell center in cylinder coordinates */
  real omega[3];                /* cell thread's angular velocity */
  real origin[3];               /* cell thread's origin */
  real rho, mu, mut;
  real temp;
  real temp_aux;                /* auxilliary temperature */
  real tCond;                   /* thermal conductivity */
  real sHeat;
  real tke, ted, to;            /* k, epsilon, omega(if available) */
  real uu, uv, uw, vv, vw, ww;  /* Reynolds stresses */
  real tauG;
  real strain_rate_mag;         /* Strain rate magnitude */
  real G;                       /* theta_R**4 */
  real pressure;
  real press_grad[3];
  real vel_x_grad[3];           /* gradient of U */
  real vel_y_grad[3];           /* gradient of V */
  real vel_z_grad[3];           /* gradient of W */
  real cell_volume;
  real cell_eqv_length;
  real temp_grad[3];
  real gran_press_grad[3];
  real liq_press_grad[3];
  real vof_grad[3];
  real cont_phase_vof;
  real particle_phase_vof;
  real unclipped_particle_phase_vof;
  real particle_phase_vof_nmax; /* from each node's MAX of all connected cells' values of DDPM phase volume fraction */
  real static_pileup_pack_flag_grad[3];
  real thermal_exp_coeff;
  real mol_wt_bulk;
  real vof;                     /* phase volume fraction (Eulerian context) */
  real film_mass;               /* wall film mass */
  real film_height;             /* wall film height */
  real wall_shear[3];           /* wall shear force */
  cxboolean include_omega;
  cxboolean rho_boussinesq;
  real *yi;
  real *xi;
  real *udmi;
  cxboolean needs_updating;     /* interpolation is outdated when True */
} cphase_state_t;

typedef struct dpms_struct
{
  real steps_in_cell;
  real mass;
  real momentum_s[3];
  real momentum_ap[3];
  real energy;
  real energy_ap;
  real *species_ap;
  real concentration;
  real burnout;

  /* mixture fraction and inert source for non-premixed model */
  real pdf_s[3];
  real pdf_s_ap[3];

  /* turbulence interaction sources */
  real tke;
  real epsilon;
  real omega;
  real tke_rs[3][3];

  /* wall film sources */
  real q_wall;
  real q_gas;

  real t_aux;
  real film_heat_flux;
  real film_h_wall;
  real reflect_heat_flux;

  real bf_acc[3]; /* stores the acceleration due to body force during
                   * the current time step; momentum changes due to
                   * this force should not be included in the exchange */

  /* for particle - radiation model interaction */
  real abs;       /* sum of the particle projected area * emissivity delta_t for the current cell */
  real emiss;     /* sum of projected_area * emissivity * Tp^4 * delta_t */
  real scat;      /* sum of projected area * (1 - scatt_factor)*(1-emissivity)) delta_t */

  /* for generalized gas solid particle surface reactions */
  real *species_concentration;
  real *reaction_rate_post;

  real *species;
  real *vaporization_per_material;
  real *devolatilization_per_material;
  real *burnout_per_material;

  /* needed to accumulate linearised terms */
  real drag;
  real *mtc;
  real pdfc[3];

  /* needed for MP-PIC */
  real acc_dt[3];
  real beta_dt;
  real htc_A_dt;
} dpms_t;

typedef struct dpm_wallfilm_props
{
  real mass0;                            /* mass when the particle last accumulated film props */
  real time0;                            /* time when the particle last accumulated film props */

  real film_m_imp;                       /*  (added_mass) / (flow_time_step * area)   */

  real film_volume;                      /*  (parcel_volume * delta_t)                */
  real film_height;                      /*  (parcel_volume * delta_t) / area         */

  real film_mass;                        /*  (parcel_mass * delta_t)                  */
  real film_mass_temp;                   /*  (parcel_mass * delta_t * temperature)    */
  real film_mass_surface_temp;           /*  (parcel_mass * delta_t * surface temperature)    */
  real film_mass_ktc;                    /*  (parcel_mass * delta_t * conductivity)   */
  real film_mass_mu;                     /*  (parcel_mass * delta_t * viscosity)      */
  real film_mass_surf_tension;           /*  (parcel_mass * delta_t * sigma)          */
  real NV_VEC(film_mass_velocity);       /*  (parcel_mass * delta_t * velocity)       */
} film_props_t;

#if RP_DPM_CACHE
typedef struct dpm_source_cache_struct
{
  cat_t cat;
  cat_t cat_st;
  fat_t fat;

  dpms_t source;

  int law;
  int pdf_source_sv[2];
  int *iis;
  cxboolean multiple_surface_p;
  int ptype;
  real xp[3];
  real dp_ave;
}
dpm_source_cache_t;

typedef struct dpm_film_prop_cache_struct
{
  fat_t fat;

  film_props_t film_props;
}
film_prop_cache_t;

typedef struct dpm_real_cache_struct
{
  char o;
  real *p;
  real v;
}
dpm_real_cache_t;

typedef struct dpm_workpile_struct
{
  struct particle_struct *p;
}
dpm_workpile_t;
#endif /* RP_DPM_CACHE */

struct subtet_tracking_location_struct;

typedef struct global_tracked_particle_vars_struct
{

#if RP_DPM_CACHE
  /* avoids having to pass additional arguments to AddSources();
   * later should add extra function args to make clean */
  dpm_source_cache_t *source_cache;
  int source_cache_size;
  int source_cache_count;

  film_prop_cache_t *film_prop_cache;
  int film_prop_cache_size;
  int film_prop_cache_count;

  dpm_real_cache_t *real_cache;
  int real_cache_size;
  int real_cache_count;
  dpm_workpile_t *workpile;
  int workpile_size;
  int workpile_count;
  int next_particle;
  float *random_cache;         /* store precomputed random numbers */
  int random_cache_size;
  int next_random;
  float next_gauss_random;     /* save second random generated by gauss_random() */
#endif /* RP_DPM_CACHE */

  /*
   * Current cell type and number of faces in current cell.  Don't use
   * cxfaces_per_cell[ctype] for number of faces as hanging nodes may
   * add additional faces.
   */
  int path_ctype, path_n_faces, path_incl_test;
  int path_n_nodes;               /* number of nodes in current cell */
  int path_face_num;

  /* all of the following global data pertains to the cell in which the current
   * particle is currently located. Should be updated whenever we start a new
   * particle or the particle enters a new cell.
   */
  real prevVel[3];                  /* velocity of particle in prev step. */

  double (*faceEq)[5];              /* faceEq[6*MAX_CELL_NODES][5];  MAX is 6*MAX_CELL_NODES -- polyhedral cell with hanging nodes.
                                     * last element holds magnitude of cross product of edges, e.g., for intersections */
  double (*faceEqV)[5];             /* face equation velocity - for face equations moving in time */
#if RP_3D
  double (*faceEqA)[4];             /* face equation acceleration - for face equations moving in time */
#endif
  double (*facePts)[3][3];          /* facePts[6*MAX_CELL_NODES][3][3]; */
  double (*facePtV)[3][3];          /* facePtV[6*MAX_CELL_NODES][3][3]; */

  int *validEq;                     /* validEq[6*MAX_CELL_NODES];    */
  cxboolean validMovingEquations;   /* safeguard missuse of uninitialized variables */
  int *numFacePts;                  /* numFacePts[6*MAX_CELL_NODES]; */
  int *faceIndx;                    /* faceIndx[6*MAX_CELL_NODES];   */
  real zoneEq[3];
  int zoneEqSet;
  int numCellVisited;

  /* equations for perpendicular planes at each edge on the wall film face (max of 4 edges of physical face, not cortex face) */
  int  *edge_valid;                 /* edge_valid[MAX_FACE_NODES]; */
  double (*edgeEq)[4];              /* edgeEq[MAX_FACE_NODES][4]; */
  double (*edgeEqV)[5];             /* for edge equations moving in time */
#if RP_3D
  double (*edgeEqA)[4];             /* for edge equations moving in time */
#endif
  double (*edgePts)[2][3];          /* for edges moving in time */
  double (*edgePtV)[2][3];          /* for edges moving in time */

  /* interpolation factors for function values at the current location of the particle. updated every step. */
  float *intFact;                 /* intFact[MAX_CELL_NODES]; */

  int n_tracked;
  int n_escaped;
  int n_aborted;
  int n_trapped;
  int n_stripped;
  int n_separated;
#if RP_3D && RP_WALL_FILM
  int n_absorbed;
#endif
  int n_transformed;
  int n_inserted;
  int n_evaporated;
  int n_incomplete;
  int n_incomplete_parallel;
  int n_coalesced;
  int n_collided;
  int n_splashed;
  int n_shed;
  int n_stick;
  int n_rebound;
  int n_spread;
#if RP_DPM_CACHE
  int n_source_cache_deposits;
  int n_cell_updates;
  int n_workpile_updates;
#endif /* RP_DPM_CACHE */
  int n_migrant;
  int n_tracked_migrants;
  double dpm_time;

  float fldmax[3], fldmin[3];        /* also part of c_par */

  struct particle_struct *p_spawned; /* list to carry spawned particles */
  struct particle_struct *p_impinging; /* list for impinging particles */

  /* subtet tracking */
  struct subtet_tracking_location_struct *subtet;

} gtpv_t; /* type for global tracked particle vars */

struct cubiceos_s;

/* coal_cpd model vars */
typedef struct
{
  real x2;
  real x3;
  real fmet;
  real fvol;
  real fgas;
  real ftar;
  real fxf;
  real pstar;
  real fgasold, ftarold, fcross;
  real y[3], rrp[3];
  real ftold[35], metold[35], tarold[35];
} cpd_state_t;

/* coal_cpd model temp vars */
typedef struct
{
  /*inputs*/
  real p0_cpd, c0_cpd, sigp1_cpd, mw1_cpd, mdel_cpd;

  /*other variables*/
  real l0_cpd, mb_cpd, ma_cpd, sig_cpd, siginv_cpd, rba_cpd;
  real vol_cpd, ratecr_cpd;
  real fmetold_cpd, fcrossold_cpd, fvolold_cpd;
  real fchar_cpd, ftart_cpd, gmw_cpd, fracr_cpd;
  real ft_cpd[35], mt_cpd[35];

  cxboolean ltar_cpd;  /* = FALSE; -- make sure to initialise..! */
} cpd_temp_vars_t;

/* DEM  particle variables for collision    accessed through PV_COLLISION
 */
typedef struct pv_collision_struct
{
  real collision_range;      /* dem_spring_dashpot model: radius of the parcel, not of its individual particles */
  real NV_VEC(pos);          /* positions during collision substepping */
  real NV_VEC(vel);          /* velocities during collision substepping */
  real NV_VEC(force);        /* collective forces from collisions */

  real NV_VEC(ncf_acc);     /* collective acceleration(!) from non-collision forces */
  real NV_VEC(ncbf_acc);    /* collective acceleration(!) from non-collision body forces */
  real NV_VEC(cbf_acc);     /* collective acceleration(!) from collision body forces
                             * Never mind the redundancy here: Collision forces are always body forces. */

  real NV_VEC(omega);       /* angular velocities during collision substepping */
  real NV_VEC(torque);      /* summarized torques from collisions */
  real NV_VEC(nct_ang_acc); /* summarized angular acceleration(!) from non-collision torques */
  real NV_VEC(cbt_ang_acc); /* summarized angular acceleration(!) from collision body torques */

  real beta_angular;        /* rotation drag factor */
  real beta;                /* drag factor */
  real vmf_inv;

  real time;

  union
  {
    real NV_VEC(last_pos);
    real jacobian[ND_ND * ND_ND];
  } work;

} pv_collision_t;

#if RP_2D
typedef struct pv_collision2d_struct
{
  real n_invariant; /* The number of particles in the invariant direction.
                     * This is 1 / PP_DIAM(p) for the very first diameter.
                     * So this is indeed a floating point number.
                     * This needs to be saved with data! */
} pv_collision2d_t;
#endif

typedef real pv_turb_dampening_t[3];
typedef real pv_omega_t[3];
typedef real pv_quaternion_t[4];

struct interpolation_memory_struct; /* see: dpm_interpolation.h */

typedef struct tracked_particle_struct
{
  int cInd;                                           /* curr_index into pts array */
#if ! UDF_COMPILER
  int64_t part_id;                                    /* particle id, which is different from array index */
#endif
  int type;

  CX_Cell_Id cCell;                                   /* current cell  */

  void *cell_list;                                    /* pointer to list of cells in cloud */

  real time_of_birth;
  real stop_time;                                     /* time remaining until end of particle time step */
  real time_step_at_birth;
  real time_step;
  real next_time_step;
  real last_time_step;
  real brownian_randoms[3];
  real brownian_factor;
  Tracking_Scheme_Type tracking_scheme;               /* current tracking scheme */
  Tracking_Scheme_Type free_stream_tracking_scheme;   /* current tracking scheme for free stream particles */
  int refinement_steps;
  real time_step_odeint;
  int nn_odeint;
  struct odeint_work_s *odeint_work;
  real flow_rate;
  real number_in_parcel;                              /* number of particles in parcel (unsteady only)*/
  real Re;
  real Re_rot;                                        /* Re number based on relative (fluid to particle) angular velocity */
  real omega_rel_mag;                                 /* magnitude of relative angular velocity */
  real We;                                            /* liquid Weber number = rho_p*rel_v*rel_v*radius/surf_ten */
  real Nu;                                            /* Nusselt Number */
  real impingement_location[3];
  real impingement_vmag;
  real Nu_wall;                                       /* Nusselt number for film-wall heat transfer */
  real film_surface_temp;
  real Le;
  real Bm;
  real Bt;
  real *hgas;                                         /* evaporation enthalpies */
  real *hvap;
  real Cp;                                            /* specific heat */
  real diffusivity;                                   /* binary diffusivity */
  real enthalpy;                                      /* used in UDFs of specific heat capacity */
  real htcA;                                          /* thermal conductance: = h * A */
  real *averaged_i;                                   /* averaged evaporating species properties and dimensionless numbers */
  real averaged[MAX_FILM_PROP];                       /* averaged properties and dimensionless numbers */
  real mol_wt_bulk_non_evap;
  real V_prime[3];
  real resid_time;                                    /* residence time only for post processing purposes */
  real V_mag;                                         /* used for tp min max */
  real radius;                                        /* used for tp min max */
  real theta;                                         /* used for tp min max */
  real v_r;                                           /* used for tp min max */
  real v_swirl;                                       /* used for tp min max */
  real eddy_time;
  real breakup_time;                                  /* spray breakup time, used to limit integration time step */
  real khrt_wave_len;
  real old_tke, old_ted;
  real variance[3];
  real Rp[3];
  real dsig_dt[3];
  real Rp_time;
  int steps_in_cell;
  int current_law_index;

  Thread *wallfilm_thread;
  face_t  wallfilm_face;                              /* flags for wall film model */
  int film_part_id;
  cxboolean on_wall;
  cxboolean reflected;
  cxboolean first_hit;
  real y_s;
  real E_imp;
  real weber_imp;
  real film_height;                                   /* film height from previous particle step */
  Breakup_Type breakup;

  cxboolean seco_breakup_on;
  /* cxboolean seco_breakup_tab;
   * cxboolean seco_breakup_wave;
   * cxboolean seco_breakup_khrt;
   * cxboolean seco_breakup_ssd;
   * cxboolean seco_breakup_madabhushi;
   * cxboolean seco_breakup_schmehl;
   */
  int number_tab_diameters;
  real seco_breakup_tab_y0;
  real seco_breakup_wave_b1;
  real seco_breakup_wave_b0;
  real seco_breakup_khrt_cl;
  real seco_breakup_khrt_ctau;
  real seco_breakup_khrt_crt;
  real seco_breakup_ssd_we_cr;
  real seco_breakup_ssd_core_bu;
  real seco_breakup_ssd_np_target;
  real seco_breakup_ssd_x_si;
  real seco_breakup_madabhushi_c0;
  real seco_breakup_madabhushi_column_drag_cd;
  real seco_breakup_madabhushi_ligament_factor;
  real seco_breakup_madabhushi_jet_diameter;
  int seco_breakup_schmehl_np;

  double wall_eqn[3];
  double wall_eqn1[3];
  double wall_eqnV[3];
  real *user;
  real *scalar;
  real *cbk;                                          /* store integration points in annealing model in cbk*/

  real T_ave4;                                        /* Effective radiating T**4 over current time step (particle/radiation) */
  real proj_area;                                     /* Projected area of particle for radiation over current time step (particle/radiation) */
  struct injection_struct *injection;
  struct injection_struct *reinj_inj;                 /* injection to use to assign new position and velocity in reinjection */
  int stream_index;
  int flags;
  particle_state_t init_state;                        /* state at injection */
  particle_state_t state0, state;                     /* states at entry to current cell and current location respectively */

  cphase_state_t *cphase;
  film_props_t film_props;

  dpms_t source;
  dpms_t source_total;                                /* used for cloud model */
  dpms_t source_dzdt;                                 /* used with multicomponent particle */
  real vff[4];                                        /* combusting particle related fractions
                                                       *  [0] volatile fraction - wet-basis if wet-combuating
                                                       *  [1] char fraction - wet-basis if wet-combuating
                                                       *  [2] fraction of the volatiles remaining for Kobayashi model
                                                       *  [3] fraction Dv/Dinit where Dv particle diameter at the beginning of Devolatilization Law
                                                       *      Dinit dry particle diameter at the Injection temperature
                                                       */

  /* Multiple particle char reactions */
  reacting_particle_state_t  reacting_state0;         /* state at entry to current cell */
  reacting_particle_state_t  reacting_state;          /* state at current location */
  real *species_rate;                                 /* for multiple char combustion */
  real cohreadmdt;
  real *species_rate_odeint;                          /* for multiple char combustion coupled solver */
  real cohreadmdt_odeint;
  real *reaction_rate;

  gtpv_t gvtp;                                        /* global variables */

  struct interpolation_memory_struct *intrpl;

  cpd_state_t cpd;
  cpd_temp_vars_t cpd_tvar;

  /* DEM */
  real *ncf_acc;                                      /* collective acceleration(!) from non-collision forces */
  real *ncbf_acc;                                     /* collective acceleration(!) from non-collision body forces */
  real *cbf_acc;                                      /* collective acceleration(!) from collision body forces
                                                       * (Never mind the redundancy here: Collision forces are always body forces.)
                                                       */

  real beta;                                          /* drag factor */

  /* variables only aloccated in tp_min_max for displaying maximum and minimum values in graphic output */
  real *total_force;
  real total_force_mag;
  real coll_force_mag;
  real total_acc_mag;

  /* multicomponent */
  struct
  {
    int n;
    real *state;
    real *state0;
    real *init;
    int *fluid_index;
  } component;

  real tp_accumulated_time;
  real T_boil;
  real time_to_boil;                                  /* Time step to reach boiling point of particle */
  real swelling_voidage;
  real latent_heat;
  real limiting_time;
  real parcel_diam;
  real parcel_mass;
  cxboolean in_rk;
  int mc_boiling_condition;                           /* -1 failure, 0 particle is not boiling, 1 particle is boiling */
  struct cubiceos_s *cubiceos_data;

  void **uniform_randomp;
  gauss_random_seed random_seed;

  int heat_mass_laws[DPM_MAX_LAWS];

  pv_turb_dampening_t v_prime_dampening;
  pv_omega_t omega;
  real omega_mag;                                     /* needed for postprocessing purposes only. */
  pv_quaternion_t q;

  real *nct_ang_acc;                                  /* summarized angular acceleration(!) from non-collision torques */
  real *cbt_ang_acc;                                  /* summarized angular acceleration(!) from collision body torques */
  real beta_angular;                                  /* rotation drag factor */

  int surface_id;

  struct particle_struct *pp;
  cxboolean update;

  short my_thread_id;
  FILE *my_thread_debug_file;

  int n_cphases;                                      /* Number of Eulerian phases interacting with tp */

  /* park migrating particles in multi-threaded mode (DPM Hybrid)  */
  struct particle_struct *neighbor_particle_list_mt;

  cxboolean p_any_static_pileup_treatment_p;   /* particle has been affected by static pile-up treatment,
                                                * must not calculate gas phase momentum source terms
                                                * from the change in the particle velocity.
                                                */
} Tracked_Particle;

typedef struct unsteady_coupled_storage
{
  real time_step_at_birth;
  real V_prime[3];
  real eddy_time;
  real old_tke, old_ted;

} unsteady_dpm_storage;

typedef enum
{
  DPM_PV_TYPE_INT,
  DPM_PV_TYPE_REAL,
  DPM_PV_TYPE_POINTER,
  DPM_PV_TYPE_STRUCT,
  DPM_PV_TYPE_MAX
} dpm_pvar_type;

typedef enum
{
  PV_UNKNOWN = -1,
  PV_COMPONENT = 0,
  PV_COMPONENT_INIT,
  PV_REACTING_STATE,
  PV_CPD_STATE,
  PV_COLLISION,        /* DEM */
#if RP_2D
  PV_COLLISION2D,      /* DEM */
#endif
  PV_CONTACT_PARTICLE, /* DEM Particle-Particle Contact Management */
  PV_CONTACT_FACE,     /* DEM Particle-Face Contact Management */
  PV_VFF_REAL,
  PV_TURB_EDDY,
  PV_RANDOM_SEED,
  PV_OMEGA,
  PV_TURB_DAMPENING,
  PV_QUATERNION,
  PV_WALL_FILM,
  PV_BL_FILM_NU,
  PV_SCALAR,
  PV_USER_REAL,
  PV_UNSTEADY_COUPLED,
  PV_CBK,
  PV_MAX
} Pvar;


/* variables that need to be migrated but not stored on the particle */
typedef struct particle_migration_struct
{
  /* If you add non-reals here, make sure to update the calculation of
   * net_pack_particle_migration_data_size in dpm_pvar_real_set_ops().
   */

  /* variables used for wallfilm particles */
#if RP_2D
  real edge_node_coords[3];
#else
  real edge_node_coords[6];
#endif
  real wall_film_normal[3]; /* also used to store delta_x in correct_over_packing_in_parallel_loop */
  real wall_film_velocity[3];
  real cell_velocity[3];
  real wall_film_face_area;
  real wall_film_height;

  int  film_separation;     /* film separation criteria met (except for film face angle) */
  int  separation_model;    /* film separation model */
  real separation_angle;
#if ! UDF_COMPILER
  int64_t global_face_id;  /* ID of the face through which the particle enters the cell after migration */
#endif

  /* variable used for overset mesh and GTI mixing plane migration */
  int migration_zone_id;

  /* used for velocity-based timestep adaption */
  real prev_vel[3];

} particle_migration_struct_t;


typedef struct particle_struct
{
  /* changes to the Particle struct may entail changes to parallel DPM.
     The Particle struct should be same on host and nodes for parallel.
     p->ntries is used in Par-DPM (Message Passing) to hold stream_index
     during particle migration */

  /* Jochen, B63100: I suggest to sort the entries in this struct by type
   * so that we avoid memory-wasting gaps from padding and aligning
   * addresses to multiples of the data sizes..!
   */

  /* keeping this the first member allows faster looping through particle lists */
  struct particle_struct *next;

  struct injection_struct *injection;

  /* int typed members, most frequently used first */
  int I_id;
  int flags;                   /* carry flags of particle */

#if ! UDF_COMPILER
  int64_t part_id;             /* particle id, is different from array index */
#endif
  int type;
  int to_part;                 /* parallel target partition */    /* --> move to particle_migration_struct?? */
  CX_Cell_Id cCell;            /* current cell */
  int current_law_index;                                          /* --> move to particle_migration_struct?? */
  int stream_index;
  int wallfilm_thread_id;
  face_t wallfilm_face;        /* Information for wall film model */
  face_t wallfilm_intf_face;   /* Information for wall film model */
  cxboolean on_wall;

  Breakup_Type breakup;
  int n_steps;
  short my_thread_id;          /* No macro access -- never to be used in UDFs */

#if ! UDF_COMPILER
  /* int64_t typed members */
  int64_t particle_cell_id;    /* cell id particle belongs to: used in I/O, relocation */
  int64_t wallfilm_face_id;    /* face ID wall film particle belongs to: used in I/O, relocation */

  /* needed for migration only, not for I/O or unsteady tracking */
  particle_migration_struct_t *particle_migration_data;

  int64_t wallfilm_intf_face_id;
#endif  /*  #if ! UDF_COMPILER  */
  int wallfilm_intf_thread_id;

  /* real typed members */
  real time_of_birth;
  real flow_rate;
  real number_in_parcel;        /* number of particles in parcel (unsteady only) */
  particle_state_t state;       /* current state, OR at entry to current cell */
  particle_state_t init_state;  /* state at injection */
  real accumulated_time;        /* in I->p_init, ("ab-") use for injection time e.g. read from unsteady injection file */
  real next_time_step;          /* in I->p_init, ("ab-") use for injection duration  read from unsteady injection file */
  real last_time_step;

  /* pointers to */
  struct unsteady_coupled_storage *unsteady_coupled;
  real *cbk;
  real *user;        /* user defined storage */
  real *scalar;      /* storage of scalars for spray-suite OR pdf transport */

} Particle;

typedef struct particle_contact_struct
{
  struct particle_contact_struct *next;     /* pointer to next particle contact in particle contact list */

  int flags;

  struct particle_struct *contact_particle; /* pointer to particle in contact */
  real NV_VEC(tangential_displacemet);      /* 3D/2D Vector of tangential displacement of pre-load tangential force */
  real NV_VEC(rolling_displacemet);         /* 3D/2D Vector of rolling displacement of pre-load rolling force */
} Particle_Contact;

typedef struct face_contact_struct
{
  struct face_contact_struct *next;    /* pointer to next face contact in face contact list */

  int flags;

  real NV_VEC(contact_A);              /* Face Normal of particle in contact */
  real NV_VEC(tangential_displacemet); /* 3D/2D Vector of tangential displacement of pre-load tangential force */
  real NV_VEC(rolling_displacemet);    /* 3D/2D Vector of rolling displacement of pre-load rolling force */
} Face_Contact;

typedef struct dpm_solver_parameters_struct
{
  real G[3]; /* gravity */
  int nSpecies;
  int nSpeSurf;
  int nReactPost;
  real molWeight[MAX_SPE_EQNS_PDF];
  real refPressure;
  real refTemperature;
  real flow_time;
  real flow_time_step;
  real Rzero[3]; /* radial vector at theta = 0 set from rpvar 'in-plane/zero-dir */
} dpm_solver_parameters_t;

typedef struct dpm_injection_parameters_struct
{
  int nMaterialDrop;
  int nMaterialComb;
  int nMaterialFilm;
  char Drop_material_name[MAX_DPM_MATERIAL][MATERIAL_NAME_LENGTH];
  char Film_material_name[MAX_DPM_MATERIAL][MATERIAL_NAME_LENGTH];
  char Comb_material_name[MAX_DPM_MATERIAL][MATERIAL_NAME_LENGTH];
  int nSpeciesSources;
  int yi2s[MAX_SPE_EQNS_PDF]; /* global array of DPM source index for species i */
  int iis[MAX_SPE_EQNS_PDF];  /* global array of species index for DPM source i */
} dpm_injection_parameters_t;

struct dpm_distribution_s;

typedef enum
{
  INJECTION_VAR_REAL = 0,
  INJECTION_VAR_PROFILE
} injection_var_type_t;

typedef struct injection_var_s
{
  struct
  {
    char pname[PROFILE_NAME_LENGTH];
    char fieldname[PROFILE_NAME_LENGTH];
    Input_Profile *p;
    Profile_Field *pfield;
  } profile;

  injection_var_type_t method;

} injection_var_t;

typedef enum
{
  VOLI_ZONE,
  VOLI_BGEOM
} vol_inj_method;

typedef enum
{
  BG_SPHERE = 0,
  BG_CYLINDER,
  BG_CONE,
  BG_HEX
} bound_geom_t; /* simple geometry shape used in volume injection. */

typedef struct
{
  real NV_VEC(xmin);
  real NV_VEC(xmax);
  real radius;
  real angle;
} bound_geom_coord_t;

typedef enum
{
  NUMSTR_TOTAL = 0,
  NUMSTR_PER_CELL,
  NUMSTR_PARCEL_METHOD
} stream_spec_t;

typedef struct injection_volume_s
{
  vol_inj_method method;
  int nzone;
  int *lzone;
  bound_geom_t bgeom_shape;

  bound_geom_coord_t bgeom_coord;

  stream_spec_t stream_spec;
  int streams;

  real packing_limit_per_cell;

} injection_volume_t;

typedef real *(* dpm_pvar_real_pack_fn ) (Particle *p, real *rbuf, int pv_index, int pv_size);

typedef struct
{

  dpm_pvar_real_pack_fn pack;
  dpm_pvar_real_pack_fn unpack;
  int pv_index;
  int pv_size;

} dpm_pvar_real_op_t;

typedef real (* dpm_pvar_get_value_fn) (Tracked_Particle *, int);

typedef struct injection_struct
{
  struct injection_struct *next;

  void *particle_storage;

  /* particle variable index, the last entry contains the size of particle in memory */
  int pv_index[PV_MAX + 1];
  int pv_size[PV_MAX];

  int                pv_real_size;
  int                pv_real_n_ops;
  dpm_pvar_real_op_t pv_real_op[PV_MAX];

  size_t net_pack_particle_migration_data_size;

  int *surf, nsurf;
  int *surf_nf, nsurf_nf;          /* table to map surface ids to particle ids in parallel */
  injection_volume_t volume_inj;   /* data specific to volume injection only */
  int type;                        /* particle type */
  char name[DPM_NAME_LENGTH];
  int heat_mass_laws[DPM_MAX_LAWS];
  char *user_law_name[DPM_MAX_LAWS];
  void (*user_law_fcn[DPM_MAX_LAWS])(Tracked_Particle *, int);
  char *user_switch_name;
  char *user_initialize_name;
  char *user_heat_mass_name;
  char *injection_file;
  FILE *inj_fil_ptr;
  DPM_FPOS  inj_fil_loc;
  DPM_FPOS  prev_inj_fil_loc;
  DPM_FPOS  inj_fil_loc_bfr_rpt_intvl;   /* where to start reading the time-repetitive passage in the file */
  int       inj_fil_repeat_count; /* number of passes already completed */
  cxboolean inj_file_is_unsteady;
  cxboolean inj_file_has_duration;
  cxboolean  user_heat_mass_law_exists;
  cxboolean active;
  cxboolean initialized;
  cxboolean has_profile;
  Injection_Type injection_type;
  int n_particles;                /* number of particles (initial or total) */
  int n_particle_ids;             /* number of partids distributed */
  int nbound;                     /* number of boundaries */
#if ! UDF_COMPILER
  int64_t start_id;               /* particle ids are based on this */
#endif
  int  *bnd_inj_thread_id;        /* thread IDs for boundary injection type */
  cxboolean use_face_normal;      /* injection w/components normal to the local face */
  real pos1[3];                   /* If locations specified explicitly or rake/group. */
  real pos2[3];
  real posu[3];
  real posr[3];
  real axis[3];
  real inner_radius, outer_radius;
  real swirl_frac;
  cxboolean scale_by_area;
  cxboolean random_surface;       /* random surface injection */
  real surface_area;              /* of a surface injection, needed for scaling in parallel */
  int n_facets;                   /* number of facets for surface injection, needed for allocating random arrays */
  int n_pts;                      /* If group or cone or (matrix), number of injections (along i). */
  int n_pts_j;                    /* If matrix, number of injections along j. */
  real diam[2];                   /* in case of groups, the first and last elements. */
  cxboolean  rr_distrib;          /* TRUE/FALSE */
  cxboolean  rr_uniform_lnD;      /* TRUE/FALSE use uniform increments of ln(Diam)*/

  real  mean_diam;                /* if Rosin-Rammler. */
  real  spread_parameter;         /* if Rosin-Rammler. */
  real max_diam, min_diam;        /* if Rosin-Rammler */
  int  number_diameters;          /* if Rosin-Rammler */

  real V1[3];
  real V2[3];
  real Vmag;                      /* for cone */
  real Vang1[3];                  /* angular velocity */
  real Vang2[3];
  real Vang_mag;

  struct injection_var_s v_vel[2][3];
  struct injection_var_s v_vel_mag;

  struct injection_var_s v_ang_vel[2][3];
  struct injection_var_s v_ang_vel_mag;

  real cone_angle;                /* for cone */
  struct injection_var_s v_cone_angle;

  cxboolean use_input_mass;       /* allows to specify injection mass [kg] instead of total flow rate [kg/s]. */

  real total_flow_rate;
  struct injection_var_s v_total_flowrate;

  real flow_rate[2];              /* flow rate per particle for single or Non Rosin-Rammler group, total flow rate otherwise */

  struct injection_var_s v_flowrate[2];

  real total_mass;
  struct injection_var_s v_total_mass;

  cxboolean use_input_volfrac;    /* allows to specify volume fraction instead of total flow rate [kg/s] in volume injection only. */

  real volume_fraction;
  struct injection_var_s v_volume_fraction;

  real temp[2];
  real start_time;
  real unsteady_start;
  real unsteady_stop;
  real unsteady_ca_start;
  real unsteady_ca_stop;

  real start_flow_time_in_unst_file;   /* start at flow-time in unsteady injection file */
  real repeat_intrvl_from_unst_file;   /* repeat time interval from the unsteady injection file */

  /* constant parcel mass and diameter variables */
  Parcel_Model parcel_model;
  real parcel_mass;
  real parcel_diameter;
  real number_in_parcel;
  real *mass_next_time;
  int len_mass_next_time;

  /* drag parameters */
  int drag_law;
  real shape_factor;
  real cunningham_correction;
  /* === UDF_Cache_Data drag_fcn; === moved to the end of this struct to
   *                                  avoid conflicts with UDF interpreter ("UDF_COMPILER"),
   *                                  which uses a dummy definition for UDF_Cache_Data...
   */
  Htc_Corr htc_correlation;           /* heat transfer correlation */
  real htc_const_htc;                 /* constant value for const. HTC setting, dflt 0. */
  real htc_const_nu;                  /* constant value for const. Nu  setting, dflt 0. */
  cxboolean brownian_motion;

  /* secondary break-up parameters */
  cxboolean seco_breakup_on;
  cxboolean seco_breakup_tab;
  cxboolean seco_breakup_wave;
  cxboolean seco_breakup_khrt;
  cxboolean seco_breakup_ssd;
  cxboolean seco_breakup_madabhushi;
  cxboolean seco_breakup_schmehl;

  int number_tab_diameters;
  real seco_breakup_tab_y0;
  real seco_breakup_wave_b1;
  real seco_breakup_wave_b0;
  real seco_breakup_khrt_cl;
  real seco_breakup_khrt_ctau;
  real seco_breakup_khrt_crt;
  real seco_breakup_ssd_we_cr;
  real seco_breakup_ssd_core_bu;
  real seco_breakup_ssd_np_target;
  real seco_breakup_ssd_x_si;
  real seco_breakup_madabhushi_c0;
  real seco_breakup_madabhushi_column_drag_cd;
  real seco_breakup_madabhushi_ligament_factor;
  real seco_breakup_madabhushi_jet_diameter;
  int seco_breakup_schmehl_np;

  /* primary atomizer parameters */
  real atomizer_axis[3];
  real vapor_pressure, half_angle, inner_diam, outer_diam;
  real plain_length, plain_corner_size, plain_const_a;
  real pswirl_inj_press, airbl_rel_vel, phi_start, phi_stop;
  real effer_quality, effer_t_sat;
  real ff_orifice_width, ff_center[3], ff_virtual_origin[3], ff_normal[3];
  real sheet_const, lig_const, effer_const, effer_half_angle_max, ff_sheet_const;
  real atomizer_disp_angle;
  real rho_g, p_down;

  struct injection_var_s v_half_angle;
  struct injection_var_s v_effer_half_angle_max;

  int n_new;

  Material *material;
  Material *evap_species;
  Material *devol_species;
  Material *oxid_species;
  Material *prod_species;

  int drop_material_index;
  int comb_material_index;

  int evap_species_index;
  int devol_species_index;
  int oxid_species_index;
  int prod_species_index;

  int iis[DPM_MAX_LAWS][MAX_SPE_EQNS_PDF + 1];  /* indirect species index for source terms active at each law */
  real surface_species_fraction[MAX_SPE_EQNS];  /* for multiple char combustion */

  real latent_heat_ref;
  cxboolean stochastic_p;
  cxboolean cloud_model_p;
  cxboolean random_eddy_lifetime_p;
  int  ntries;
  int cloud_update;
  real time_scale_constant;
  real cloud_min_rad;        /* min. cloud radius */
  real cloud_max_rad;        /* max. cloud radius */

  /* The global post-processing variables might be in a different order as the sub-variables within a Pvar.
   * The following 2 arrays define for each postprossing variable, that is defined through the Pvar,
   * which sub-index it can be found within an injection and how to retrieve its value. Variables that
   * are defined in the Particle_Variable_ID enum, scalars and user reals are not contained in this arrays. */
  int                   *post_pvar_sub_index;
  dpm_pvar_get_value_fn *post_pvar_get_value;

  real ref_diam;
  real ref_pos[3];

  Tracked_Particle tp_min_max[2];       /* holding min/max values for reporting during display */
  Tracked_Particle *tp_prop_data;       /* holding values used for property calculations -- NOTE: must always be initialized from a Particle before use!! */
  Tracked_Particle *tp_prop_data_nulls; /* similar, but many internal pointers remain NULL in order to not provide uninitialized values anywhere... */
  cxboolean wet_combustion;
  Material *evaporating_material;
  real liquid_fraction;
  real cp_diff_enthalpy;                /* enthalpy related to different cp's of injection material and destination species */

  /* multi-component particles */
  struct
  {
    real *massfr;                /* mass fractions of particle components */
    int *fluid_index;            /* index of vaporized species in mixture */
    real *latent_heat_ref;       /* latent heat at boiling point */
    int *pdf_stream;             /* destination mixture fraction stream */
    cxboolean unique_species;    /* each particle component has an unique corresponding gas phase species */
    int ncomp;                   /* size of above allocated fields */
  } component;


  /* DEM
   */
  Objp *collision_partner;           /* DEM */
  int  collision_partner_index;      /* Used to determine collision law + parameters
                                      * Have -1 to exclude from any collision and to avoid access to Pvar storage. */

  cxboolean need_time_integration;   /* Any collision law requiring explict time integration? */
  cxboolean need_contact_management; /* Any collision law requiring contact management? */

  /* particle rotation */
  cxboolean compute_omega;           /* omega: particle angular velocity */
  int drag_law_rot;
  int rot_lift_law;

  /* rough wall model */
  cxboolean rough_wall;

  /* particle statistics phases */
  int n_distributions;
  struct dpm_distribution_s **distributions;

  Particle *p;
  Particle *p_init;
  Particle *p_t0;                    /* stored list at beginning of fluid time step during sub cycling */

  Particle *p_tail;
  Particle *p_init_tail;

  Particle *p_list_for_dpm_to_vof;
  Particle *p_list_to_reinject;

  Domain *dpm_phase_domain;
  int dpm_to_vof_mech;

  int try_id;                        /* unique injection id, set in lDPMSetInjection */

#if ! UDF_COMPILER
  int   (* fn_param_function) (struct injection_struct *);
  real    *fn_param_position;
  int64_t *fn_param_part_id;
  int64_t *fn_param_cellId;
  int     *fn_param_cellZone;
#endif

  /* UDF definitions:
   * Moved to the end of this struct to
   * avoid conflicts with UDF interpreter ("UDF_COMPILER"),
   * which uses a dummy definition for UDF_Cache_Data...:
   */
  UDF_Cache_Data drag_fcn;

  real *diameter_classes; /* used for the parcel model */
  real limited_time_step;
  cxboolean mass_next_time_reset;

  /* cone type specific settings */
  cxboolean cone_uniform_massflow_dist;          /* uniform mass flow distribution for cone injection */
  cxboolean spatial_staggering_std;              /* use spatial staggering during injection (standard injections) */
  cxboolean spatial_staggering_atom;             /* use spatial staggering during injection (atomizer injections) */
  real stagger_radius;                           /* stagger radius for standard injections */

  int phase_of_interaction_idx;                  /* domain index of a real Eulerian phase [0; 19] OR -2 for all phases */

  /* tracking parameters */
  cxboolean             step_size_control;
  cxboolean             tracking_scheme_selection;
  Tracking_Scheme_Type  tracking_scheme_init;

  /* local coordinate frame name */
  cxboolean use_local_reference_frame;

  /* discrete diameter distribution */
  cxboolean discrete_diam_dist;
  int discrete_diam_ref_diam;
  int discrete_diam_num_frac;
  int discrete_diam_mas_frac;
  char *discrete_diam_table_name;
  cxboolean discrete_diam_num_frac_accum;
  cxboolean discrete_diam_mas_frac_accum;

  cxboolean lwf_injection;
} Injection;

typedef cxboolean (* node_cond_fcn_t) (Node *v);


/* UDF programmers can use...
#define  HAVE_OLD_P_MACROS  00   in their (UDF) code to verify it's compatible with R19 and beyond */
#ifndef  HAVE_OLD_P_MACROS
#define  HAVE_OLD_P_MACROS  11
#endif


/* Particle flags are used to mark the particles temporary,
 * replacing stream_index = -1, -2, and -3
 * all flags are initialized with zero.
 * Flags are not stored in data file. */
#define P_FL_TRACKED           (1)
#define P_FL_MIGRATED          (1<<1)
#define P_FL_REMOVED           (1<<2)
#define P_FL_REGISTERED_CL     (1<<3)
#define P_FL_NOT_ORIGINAL      (1<<4)
#define P_FL_CHILD             (1<<5)
#define P_FL_SPLASHED          (1<<6)
#define P_FL_PERIODIC_SIDE     (1<<7)
#define P_FL_STRIPPED          (1<<8)
#define P_FL_SEPARATED         (1<<9)
#define P_FL_GHOST             (1<<10)
#define P_FL_SPAWNED           (1<<11)
#define P_FL_NEW_UNSTEADY      (1<<12)
#define P_FL_PARALLEL_PERIODIC (1<<13)
#define P_FL_FROZEN_VEL        (1<<14)
#define P_FL_FROZEN_HEAT_MASS  (1<<15)
#define P_FL_LOW_ORDER_SCM     (1<<16)
#define P_FL_CONDENSING        (1<<17)
#define P_FL_RELOCATE          (1<<18)
#define P_FL_NOT_IN_STATIC_PILEUP   (1<<19) /* added in 2021 -- hope this will not conflict with old UDFs..
                                        * Inverted the meaning (flag says "_not_ in static pile-up" because
                                        * I need the flag initialised as "IS in the static pile-up" just to
                                        * be sure particles that in fact are in the static pile-up will not
                                        * start to move and bounce around in a restart situation.
                                        */
#define P_FL_LAST              (1<<20) /* available for UDF or addon purposes */

#if  DEBUG  &&  11   /*  ! defined(__HELGRIND_H) --- does not work, dpm_parallel.h is not included here -->
                      *  --> must deactivate this in debug builds manually by replacing 11 with 00..
                      */
/* some add-on modules like MPM are compiled using GCC: */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static Tracked_Particle *check_tp_type_tp = NULL;
static         Particle *check_pp_type_p  = NULL;
#pragma GCC diagnostic pop
#define CHECK_TP_TYPE(tp)  (((void) (check_tp_type_tp=(tp))),(tp))
#define CHECK_PP_TYPE(pp)  (((void) (check_pp_type_p =(pp))),(pp))
#else
#define CHECK_TP_TYPE(tp)  (tp)
#define CHECK_PP_TYPE(pp)  (pp)
#endif

#define TP_TRACKED_P(p)           (TP_FLAGS(p) & P_FL_TRACKED)
#define TP_MIGRATED_P(p)          (TP_FLAGS(p) & P_FL_MIGRATED)
#define TP_REMOVED_P(p)           (TP_FLAGS(p) & P_FL_REMOVED)
#define TP_REGISTERED_CL_P(p)     (TP_FLAGS(p) & P_FL_REGISTERED_CL)
#define TP_NOT_ORIGINAL_P(p)      (TP_FLAGS(p) & P_FL_NOT_ORIGINAL)
#define TP_CHILD_P(p)             (TP_FLAGS(p) & P_FL_CHILD)
#define TP_SPLASHED_P(p)          (TP_FLAGS(p) & P_FL_SPLASHED)
#define TP_STRIPPED_P(p)          (TP_FLAGS(p) & P_FL_STRIPPED)
#define TP_SEPARATED_P(p)         (TP_FLAGS(p) & P_FL_SEPARATED)
#define TP_PERIODIC_SIDE_P(p)     (TP_FLAGS(p) & P_FL_PERIODIC_SIDE)
#define TP_GHOST_P(p)             (TP_FLAGS(p) & P_FL_GHOST)
#define TP_SPAWNED_P(p)           (TP_FLAGS(p) & P_FL_SPAWNED)
#define TP_NEW_UNSTEADY_P(p)      (TP_FLAGS(p) & P_FL_NEW_UNSTEADY)
#define TP_PARALLEL_PERIODIC_P(p) (TP_FLAGS(p) & P_FL_PARALLEL_PERIODIC)
#define TP_FROZEN_VEL_P(p)        (TP_FLAGS(p) & P_FL_FROZEN_VEL)
#define TP_FROZEN_HEAT_MASS_P(p)  (TP_FLAGS(p) & P_FL_FROZEN_HEAT_MASS)
#define TP_LOW_ORDER_SCM_P(p)     (TP_FLAGS(p) & P_FL_LOW_ORDER_SCM)
#define TP_CONDENSING_P(p)        (TP_FLAGS(p) & P_FL_CONDENSING)
#define TP_RELOCATE_P(p)          (TP_FLAGS(p) & P_FL_RELOCATE)
#define TP_NOT_IN_STATIC_PILEUP_P(p)   (TP_FLAGS(p) & P_FL_NOT_IN_STATIC_PILEUP)
#define TP_GET_FLAG(tp, flag)     (TP_FLAGS(tp) & flag)
#define MARK_TP(p, flag)          (TP_FLAGS(p) |=  (flag))
#define UNMARK_TP(p, flag)        (TP_FLAGS(p) &= ~(flag))
#define TOGGLE_TP(p, flag)        (TP_FLAGS(p) ^=  (flag))
#define PP_TRACKED_P(p)           (PP_FLAGS(p) & P_FL_TRACKED)
#define PP_MIGRATED_P(p)          (PP_FLAGS(p) & P_FL_MIGRATED)
#define PP_REMOVED_P(p)           (PP_FLAGS(p) & P_FL_REMOVED)
#define PP_REGISTERED_CL_P(p)     (PP_FLAGS(p) & P_FL_REGISTERED_CL)
#define PP_NOT_ORIGINAL_P(p)      (PP_FLAGS(p) & P_FL_NOT_ORIGINAL)
#define PP_CHILD_P(p)             (PP_FLAGS(p) & P_FL_CHILD)
#define PP_SPLASHED_P(p)          (PP_FLAGS(p) & P_FL_SPLASHED)
#define PP_STRIPPED_P(p)          (PP_FLAGS(p) & P_FL_STRIPPED)
#define PP_SEPARATED_P(p)         (PP_FLAGS(p) & P_FL_SEPARATED)
#define PP_PERIODIC_SIDE_P(p)     (PP_FLAGS(p) & P_FL_PERIODIC_SIDE)
#define PP_GHOST_P(p)             (PP_FLAGS(p) & P_FL_GHOST)
#define PP_SPAWNED_P(p)           (PP_FLAGS(p) & P_FL_SPAWNED)
#define PP_NEW_UNSTEADY_P(p)      (PP_FLAGS(p) & P_FL_NEW_UNSTEADY)
#define PP_PARALLEL_PERIODIC_P(p) (PP_FLAGS(p) & P_FL_PARALLEL_PERIODIC)
#define PP_FROZEN_VEL_P(p)        (PP_FLAGS(p) & P_FL_FROZEN_VEL)
#define PP_FROZEN_HEAT_MASS_P(p)  (PP_FLAGS(p) & P_FL_FROZEN_HEAT_MASS)
#define PP_LOW_ORDER_SCM_P(p)     (PP_FLAGS(p) & P_FL_LOW_ORDER_SCM)
#define PP_CONDENSING_P(p)        (PP_FLAGS(p) & P_FL_CONDENSING)
#define PP_RELOCATE_P(p)          (PP_FLAGS(p) & P_FL_RELOCATE)
#define PP_NOT_IN_STATIC_PILEUP_P(p)   (PP_FLAGS(p) & P_FL_NOT_IN_STATIC_PILEUP)
#define PP_GET_FLAG(pp, flag)     (PP_FLAGS(pp) & flag)
#define MARK_PP(p, flag)          (PP_FLAGS(p) |=  (flag))
#define UNMARK_PP(p, flag)        (PP_FLAGS(p) &= ~(flag))
#define TOGGLE_PP(p, flag)        (PP_FLAGS(p) ^=  (flag))

#if HAVE_OLD_P_MACROS
#define  P_TRACKED_P(p)            (P_FLAGS(p) & P_FL_TRACKED)
#define  P_MIGRATED_P(p)           (P_FLAGS(p) & P_FL_MIGRATED)
#define  P_REMOVED_P(p)            (P_FLAGS(p) & P_FL_REMOVED)
#define  P_REGISTERED_CL_P(p)      (P_FLAGS(p) & P_FL_REGISTERED_CL)
#define  P_NOT_ORIGINAL_P(p)       (P_FLAGS(p) & P_FL_NOT_ORIGINAL)
#define  P_CHILD_P(p)              (P_FLAGS(p) & P_FL_CHILD)
#define  P_SPLASHED_P(p)           (P_FLAGS(p) & P_FL_SPLASHED)
#define  P_STRIPPED_P(p)           (P_FLAGS(p) & P_FL_STRIPPED)
#define  P_SEPARATED_P(p)          (P_FLAGS(p) & P_FL_SEPARATED)
#define  P_PERIODIC_SIDE_P(p)      (P_FLAGS(p) & P_FL_PERIODIC_SIDE)
#define  P_GHOST_P(p)              (P_FLAGS(p) & P_FL_GHOST)
#define  P_SPAWNED_P(p)            (P_FLAGS(p) & P_FL_SPAWNED)
#define  P_NEW_UNSTEADY_P(p)       (P_FLAGS(p) & P_FL_NEW_UNSTEADY)
#define  P_PARALLEL_PERIODIC_P(p)  (P_FLAGS(p) & P_FL_PARALLEL_PERIODIC)
#define  P_FROZEN_VEL_P(p)         (P_FLAGS(p) & P_FL_FROZEN_VEL)
#define  P_FROZEN_HEAT_MASS_P(p)   (P_FLAGS(p) & P_FL_FROZEN_HEAT_MASS)
#define  P_LOW_ORDER_SCM_P(p)      (P_FLAGS(p) & P_FL_LOW_ORDER_SCM)
#define  P_CONDENSING_P(p)         (P_FLAGS(p) & P_FL_CONDENSING)
#define  P_RELOCATE_P(p)           (P_FLAGS(p) & P_FL_RELOCATE)
#define  P_NOT_IN_STATIC_PILEUP_P(p)    (P_FLAGS(p) & P_FL_NOT_IN_STATIC_PILEUP)
#define  MARK_PARTICLE(p, flag)    (P_FLAGS(p) |=  (flag))
#define  UNMARK_PARTICLE(p, flag)  (P_FLAGS(p) &= ~(flag))
#define  TOGGLE_PARTICLE(p, flag)  (P_FLAGS(p) ^=  (flag))
#endif

#define TP_FLAGS(tp) (CHECK_TP_TYPE(tp)->flags)
#define PP_FLAGS(pp) (CHECK_PP_TYPE(pp)->flags)
#if HAVE_OLD_P_MACROS
#define  P_FLAGS(p)   ((p)->flags)
#endif

#define WALL_FILM_THREAD_P(t) \
  ((THREAD_TYPE(t) == THREAD_F_WALL) && \
   (THREAD_VAR(t).wall.dpm_bc == DPM_BC_WALL_FILM) )

#define WALL_HEAT_EXCHANGE_THREAD_P(t) \
  ((THREAD_TYPE(t) == THREAD_F_WALL) && \
   ((THREAD_VAR(t).wall.dpm_bc == DPM_BC_WALL_FILM) || (THREAD_VAR(t).wall.dpm_bc == DPM_BC_WALL_JET) || \
    (THREAD_VAR(t).wall.dpm_bc == DPM_BC_REFLECT)) &&     \
   (THREAD_VAR(t).wall.dpm_wall_heat_exchange))

#define DPM_EULER_IMPLICIT(p) ((p)->tracking_scheme == EULER_IMPLICIT)
#define DPM_EULER_TRAPEZOIDAL(p) ((p)->tracking_scheme == EULER_TRAPEZOIDAL)
#define DPM_HIGHER_ORDER DPM_EULER_TRAPEZOIDAL
#define DPM_EXPONENTIAL(p) ((p)->tracking_scheme == EXPONENTIAL_ANALYTIC)
#define DPM_RK_EXPLICIT(p) ((p)->tracking_scheme == RK_EXPLICIT)

#if !UDF_COMPILER
#define TP_INJECTION(tp) (CHECK_TP_TYPE(tp)->injection)
#define PP_INJECTION(pp) (CHECK_PP_TYPE(pp)->injection)
#if HAVE_OLD_P_MACROS
#define  P_INJECTION(p)   ((p)->injection)
#endif

#define PP_INJ_ID(pp) (CHECK_PP_TYPE(pp)->I_id)

#define TP_ID(tp) (CHECK_TP_TYPE(tp)->part_id)
#define PP_ID(pp) (CHECK_PP_TYPE(pp)->part_id)

#define TP_TYPE(tp) (CHECK_TP_TYPE(tp)->type)
#define PP_TYPE(pp) (CHECK_PP_TYPE(pp)->type)

/* consistency with other macros: */
#define PP_NEXT(pp)                (CHECK_PP_TYPE(pp)->next)
#define PP_TO_PART(pp)             (CHECK_PP_TYPE(pp)->to_part)
#define PP_N_STEPS(pp)             (CHECK_PP_TYPE(pp)->n_steps)
#define PP_UNSTEADY_COUPLED(pp)    (CHECK_PP_TYPE(pp)->unsteady_coupled)
#define PP_ACCUMULATED_TIME(pp)    (CHECK_PP_TYPE(pp)->accumulated_time)
#define TP_ACCUMULATED_TIME(tp)    (CHECK_TP_TYPE(tp)->tp_accumulated_time)

/* For use only on I->p_init (which may be transiently "mounted" to I->p): */
#define PP_INJ_FLOWTIME(pp)   (CHECK_PP_TYPE(pp)->accumulated_time)

#define TP_NEXT_TIME_STEP(tp) (CHECK_TP_TYPE(tp)->next_time_step)
#define PP_NEXT_TIME_STEP(pp) (CHECK_PP_TYPE(pp)->next_time_step)

/* For use only on I->p_init (which may be transiently "mounted" to I->p): */
#define PP_INJ_DURATIME(pp)   (CHECK_PP_TYPE(pp)->next_time_step)

#define TP_TIME_OF_BIRTH(tp)  (CHECK_TP_TYPE(tp)->time_of_birth)
#define PP_TIME_OF_BIRTH(pp)  (CHECK_PP_TYPE(pp)->time_of_birth)

/* macros for Injections */
#define DPM_STOCHASTIC_P(I)  (rp_trb_scl && (I)->stochastic_p)
#define DPM_CLOUD_MODEL_P(I) (rp_trb_scl && (I)->cloud_model_p && !HIGH_RESOLUTION_TRACKING_ENABLED)
#define DPM_STOCHASTIC_NTRIES(I) ((dpm_par.unsteady_tracking ||  ! DPM_STOCHASTIC_P(I)) ? 1 : (I)->ntries)
#define DPM_PHASE_DOMAIN(I)  ((I)->dpm_phase_domain)
#define DPM_INTERACT_DOMAIN_INDX(I) ((I)->phase_of_interaction_idx)

/* macros for particle variables */

/* Requested by CR-16518 */
#define TP_FLOW_RATE(tp) (CHECK_TP_TYPE(tp)->flow_rate)
#define PP_FLOW_RATE(pp) (CHECK_PP_TYPE(pp)->flow_rate)
#if HAVE_OLD_P_MACROS
#define  P_FLOW_RATE(p)   ((p)->flow_rate)
#endif

#define TP_CELL(tp) RP_CELL(TP_CCELL(tp))
#define PP_CELL(pp) RP_CELL(PP_CCELL(pp))
#if HAVE_OLD_P_MACROS
#define  P_CELL(p)  RP_CELL(P_CCELL(p))
#endif

#define STORE_CX_CELL(cx_cell,cell,thread)((cx_cell)->ct.c = (cell), (cx_cell)->ct.t = (thread))
#define STORE_TP_CELL(tp, cell, thread)(TP_CCELL(tp)->ct.c = (cell), TP_CCELL(tp)->ct.t = (thread));
#define STORE_PP_CELL(pp, cell, thread)(PP_CCELL(pp)->ct.c = (cell), PP_CCELL(pp)->ct.t = (thread));

#define TP_CELL_THREAD(tp) RP_THREAD(TP_CCELL(tp))
#define PP_CELL_THREAD(pp) RP_THREAD(PP_CCELL(pp))
#if HAVE_OLD_P_MACROS
#define  P_CELL_THREAD(p)  RP_THREAD(P_CCELL(p))
#endif
#define SET_PP_CELL(pp, cell)(PP_CCELL(pp)->ct.c = (cell))
#define SET_PP_CELL_THREAD(pp, thread) SET_RP_THREAD(PP_CCELL(pp), (thread))

#if !UDF_COMPILER
#if HAVE_OLD_P_MACROS
#define  P_CELL_ID(p)      ((p)->particle_cell_id)
/* #define  P_FACE_ID(p)   P_FILM_FACE_ID(p) */
#endif
#define PP_CELL_ID(pp)     (CHECK_PP_TYPE(pp)->particle_cell_id)
/* #define PP_FACE_ID(pp)  PP_FILM_FACE_ID(pp) */

#endif

/* Requested by CR-16518 */

#define TP_INIT_STATE(tp) (CHECK_TP_TYPE(tp)->init_state)
#define PP_INIT_STATE(pp) (CHECK_PP_TYPE(pp)->init_state)
#define TP_INIT_POS(tp)   (CHECK_TP_TYPE(tp)->init_state.pos)
#define PP_INIT_POS(pp)   (CHECK_PP_TYPE(pp)->init_state.pos)
#define TP_INIT_VEL(tp)   (CHECK_TP_TYPE(tp)->init_state.V)
#define PP_INIT_VEL(pp)   (CHECK_PP_TYPE(pp)->init_state.V)
#define TP_INIT_DIAM(tp)  (CHECK_TP_TYPE(tp)->init_state.diam)
#define PP_INIT_DIAM(pp)  (CHECK_PP_TYPE(pp)->init_state.diam)
#define TP_INIT_RHO(tp)   (CHECK_TP_TYPE(tp)->init_state.rho)
#define PP_INIT_RHO(pp)   (CHECK_PP_TYPE(pp)->init_state.rho)
#define TP_INIT_MASS(tp)  (CHECK_TP_TYPE(tp)->init_state.mass)
#define PP_INIT_MASS(pp)  (CHECK_PP_TYPE(pp)->init_state.mass)
#define TP_INIT_TEMP(tp)  (CHECK_TP_TYPE(tp)->init_state.temp)
#define PP_INIT_TEMP(pp)  (CHECK_PP_TYPE(pp)->init_state.temp)
#define TP_INIT_TIME(tp)  (CHECK_TP_TYPE(tp)->init_state.time)
#define PP_INIT_TIME(pp)  (CHECK_PP_TYPE(pp)->init_state.time)
#define TP_INIT_LMF(tp)   (CHECK_TP_TYPE(tp)->init_state.lmf)
#define PP_INIT_LMF(pp)   (CHECK_PP_TYPE(pp)->init_state.lmf)

#if HAVE_OLD_P_MACROS
#define  P_INIT_POS(p)    ((p)->init_state.pos)
#define  P_INIT_VEL(p)    ((p)->init_state.V)
#define  P_INIT_DIAM(p)   ((p)->init_state.diam)
#define  P_INIT_RHO(p)    ((p)->init_state.rho)
#define  P_INIT_MASS(p)   ((p)->init_state.mass)
#define  P_INIT_TEMP(p)   ((p)->init_state.temp)
#define  P_INIT_TIME(p)   ((p)->init_state.time)
#define  P_INIT_LMF(p)    ((p)->init_state.lmf)
#endif

#define TP_MATERIAL(p) (TP_INJECTION(p)->material)
#define PP_MATERIAL(p) (PP_INJECTION(p)->material)
#if HAVE_OLD_P_MACROS
#define  P_MATERIAL(p)  (P_INJECTION(p)->material)
#endif
#define TP_VF(tp)  (CHECK_TP_TYPE(tp)->vff[0])
#define TP_CF(tp)  (CHECK_TP_TYPE(tp)->vff[1])
#define TP_VFF(tp) (CHECK_TP_TYPE(tp)->vff[2])
#define TP_DF(tp)  (CHECK_TP_TYPE(tp)->vff[3])
#define TP_DT(tp)  (CHECK_TP_TYPE(tp)->time_step)
#if HAVE_OLD_P_MACROS
#define  P_VF(tp)   TP_VF(tp)
#define  P_CF(tp)   TP_CF(tp)
#define  P_VFF(tp)  TP_VFF(tp)
#define  P_DF(tp)   TP_DF(tp)
#define  P_DT(tp)   TP_DT(tp)
#endif

#define TP_N(tp) (CHECK_TP_TYPE(tp)->number_in_parcel)
#define PP_N(pp) (CHECK_PP_TYPE(pp)->number_in_parcel)
#if HAVE_OLD_P_MACROS
#define  P_N(p)   ((p)->number_in_parcel)
#endif

#define TP_FILM_FACE(tp) (CHECK_TP_TYPE(tp)->wallfilm_face)
#define PP_FILM_FACE(pp) (CHECK_PP_TYPE(pp)->wallfilm_face)
#if HAVE_OLD_P_MACROS
#define  P_FILM_FACE(p)   ((p)->wallfilm_face)
#endif

#if !UDF_COMPILER
#if HAVE_OLD_P_MACROS
#define   P_FILM_FACE_ID(p)   ((p)->wallfilm_face_id)
#endif
#define  PP_FILM_FACE_ID(pp)  (CHECK_PP_TYPE(pp)->wallfilm_face_id)
#endif

#define TP_ON_WALL(tp) (CHECK_TP_TYPE(tp)->on_wall)
#define PP_ON_WALL(pp) (CHECK_PP_TYPE(pp)->on_wall)
#if HAVE_OLD_P_MACROS
#define  P_ON_WALL(p)   ((p)->on_wall)
#endif

#define TP_REFLECTED(tp)             (CHECK_TP_TYPE(tp)->reflected)
#define TP_SPLASHED_FRACTION(tp)     (CHECK_TP_TYPE(tp)->y_s)
#define TP_IMPINGEMENT_PARAMETER(tp) (CHECK_TP_TYPE(tp)->E_imp)
#define TP_WEBER_IMP(tp)             (CHECK_TP_TYPE(tp)->weber_imp)
#if HAVE_OLD_P_MACROS
#define  P_REFLECTED(tp)             TP_REFLECTED(tp)
#define  P_SPLASHED_FRACTION(tp)     TP_SPLASHED_FRACTION(tp)
#define  P_IMPINGEMENT_PARAMETER(tp) TP_IMPINGEMENT_PARAMETER(tp)
#define  P_WEBER_IMP(tp)             TP_WEBER_IMP(tp)
#endif

#define TP_CCELL(tp) (&(CHECK_TP_TYPE(tp)->cCell))
#define PP_CCELL(pp) (&(CHECK_PP_TYPE(pp)->cCell))
#if HAVE_OLD_P_MACROS
#define  P_CCELL(p)   (&((p)->cCell))
#endif

#define TP_STATE(tp) (CHECK_TP_TYPE(tp)->state)
#define PP_STATE(pp) (CHECK_PP_TYPE(pp)->state)
#define TP_POS(tp)   (CHECK_TP_TYPE(tp)->state.pos)
#define PP_POS(pp)   (CHECK_PP_TYPE(pp)->state.pos)
#define TP_VEL(tp)   (CHECK_TP_TYPE(tp)->state.V)
#define PP_VEL(pp)   (CHECK_PP_TYPE(pp)->state.V)
#define TP_DIAM(tp)  (CHECK_TP_TYPE(tp)->state.diam)
#define PP_DIAM(pp)  (CHECK_PP_TYPE(pp)->state.diam)
#define TP_RHO(tp)   (CHECK_TP_TYPE(tp)->state.rho)
#define PP_RHO(pp)   (CHECK_PP_TYPE(pp)->state.rho)
#define TP_MASS(tp)  (CHECK_TP_TYPE(tp)->state.mass)
#define PP_MASS(pp)  (CHECK_PP_TYPE(pp)->state.mass)
#define TP_T(tp)     (CHECK_TP_TYPE(tp)->state.temp)
#define PP_T(pp)     (CHECK_PP_TYPE(pp)->state.temp)
#define TP_TIME(tp)  (CHECK_TP_TYPE(tp)->state.time)
#define PP_TIME(pp)  (CHECK_PP_TYPE(pp)->state.time)
#define TP_LMF(tp)   (CHECK_TP_TYPE(tp)->state.lmf)
#define PP_LMF(pp)   (CHECK_PP_TYPE(pp)->state.lmf)

#if HAVE_OLD_P_MACROS
#define  P_POS(p)     ((p)->state.pos)
#define  P_VEL(p)     ((p)->state.V)
#define  P_DIAM(p)    ((p)->state.diam)
#define  P_RHO(p)     ((p)->state.rho)
#define  P_MASS(p)    ((p)->state.mass)
#define  P_T(p)       ((p)->state.temp)
#define  P_TIME(p)    ((p)->state.time)
#define  P_LMF(p)     ((p)->state.lmf)
#endif


#define TP_LF(tp) ((TP_WET_COMBUSTION(tp) && (NNULLP(TP_WET_COMB_MATERIAL(tp)))) ? \
                   (TP_LMF(tp) * TP_RHO(tp) / DPM_generic_property(tp, TP_WET_COMB_MATERIAL(tp), PROP_rho, TP_T(tp))) : \
                   TP_LMF(tp))

#define PP_LF(pp) ((PP_WET_COMBUSTION(pp) && (NNULLP(PP_WET_COMB_MATERIAL(pp)))) ? \
                   (Error("misuse of PP_LF(pp): Cannot call DPM_generic_property() on a Particle"), 0.0) : \
                   PP_LMF(pp))

#if HAVE_OLD_P_MACROS
#define P_LF(p) ((P_WET_COMBUSTION(p) && (NNULLP(P_WET_COMB_MATERIAL(p)))) ? \
                 (P_LMF(p) * P_RHO(p) / DPM_generic_property(p, P_WET_COMB_MATERIAL(p), PROP_rho, P_T(p))) : \
                  P_LMF(p))
#endif


#define TP_STATE0(tp) (CHECK_TP_TYPE(tp)->state0)
#define TP_POS0(tp)   (CHECK_TP_TYPE(tp)->state0.pos)
#define TP_VEL0(tp)   (CHECK_TP_TYPE(tp)->state0.V)
#define TP_DIAM0(tp)  (CHECK_TP_TYPE(tp)->state0.diam)
#define TP_RHO0(tp)   (CHECK_TP_TYPE(tp)->state0.rho)
#define TP_MASS0(tp)  (CHECK_TP_TYPE(tp)->state0.mass)
#define TP_T0(tp)     (CHECK_TP_TYPE(tp)->state0.temp)
#define TP_TIME0(tp)  (CHECK_TP_TYPE(tp)->state0.time)
#define TP_LMF0(tp)   (CHECK_TP_TYPE(tp)->state0.lmf)

#if HAVE_OLD_P_MACROS
#define  P_POS0(p)     ((p)->state0.pos)
#define  P_VEL0(p)     ((p)->state0.V)
#define  P_DIAM0(p)    ((p)->state0.diam)
#define  P_RHO0(p)     ((p)->state0.rho)
#define  P_MASS0(p)    ((p)->state0.mass)
#define  P_T0(p)       ((p)->state0.temp)
#define  P_TIME0(p)    ((p)->state0.time)
#define  P_LMF0(p)     ((p)->state0.lmf)
#endif


/* I trust that the optimizing compiler will understand that (RP_2D && rp_axi) never can be true in 3d..: */
#define TP_PARCEL_DIAM(tp) ((RP_3D || rp_axi) ? (cbrt(TP_N(tp)               )  * TP_DIAM(tp)) \
                                              : (sqrt(TP_N(tp)  * TP_DIAM(tp))  * TP_DIAM(tp)))
#define PP_PARCEL_DIAM(pp) ((RP_3D || rp_axi) ? (cbrt(PP_N(pp)               )  * PP_DIAM(pp)) \
                                              : (sqrt(PP_N(pp)  * PP_DIAM(pp))  * PP_DIAM(pp)))
#if HAVE_OLD_P_MACROS
#define  P_PARCEL_DIAM(p)  ((RP_3D || rp_axi) ? (cbrt( P_N(p)                )  *  P_DIAM(p) ) \
                                              : (sqrt( P_N(p)   *  P_DIAM(p) )  *  P_DIAM(p) ))
#endif

#define       TP_EVAP_SPECIES_INDEX(tp) (TP_INJECTION(tp)->evap_species_index)
#define      TP_DEVOL_SPECIES_INDEX(tp) (TP_INJECTION(tp)->devol_species_index)
#define       TP_OXID_SPECIES_INDEX(tp) (TP_INJECTION(tp)->oxid_species_index)
#define       TP_PROD_SPECIES_INDEX(tp) (TP_INJECTION(tp)->prod_species_index)
#define        TP_EVAP_SOURCE_INDEX(tp) (injection_par.yi2s[TP_INJECTION(tp)->evap_species_index])
#define       TP_DEVOL_SOURCE_INDEX(tp) (injection_par.yi2s[TP_INJECTION(tp)->devol_species_index])
#define        TP_OXID_SOURCE_INDEX(tp) (injection_par.yi2s[TP_INJECTION(tp)->oxid_species_index])
#define        TP_PROD_SOURCE_INDEX(tp) (injection_par.yi2s[TP_INJECTION(tp)->prod_species_index])
#define    TP_EVAP_SPECIES_MATERIAL(tp) (TP_INJECTION(tp)->evap_species)
#define   TP_DEVOL_SPECIES_MATERIAL(tp) (TP_INJECTION(tp)->devol_species)
#define    TP_OXID_SPECIES_MATERIAL(tp) (TP_INJECTION(tp)->oxid_species)
#define    TP_PROD_SPECIES_MATERIAL(tp) (TP_INJECTION(tp)->prod_species)
#define        TP_WET_COMB_MATERIAL(tp) (TP_INJECTION(tp)->evaporating_material)
#define TP_SOLID_SPECIES_FRACTION(tp,i) (TP_INJECTION(tp)->surface_species_fraction[i])

#define       PP_EVAP_SPECIES_INDEX(pp) (PP_INJECTION(pp)->evap_species_index)
#define      PP_DEVOL_SPECIES_INDEX(pp) (PP_INJECTION(pp)->devol_species_index)
#define       PP_OXID_SPECIES_INDEX(pp) (PP_INJECTION(pp)->oxid_species_index)
#define       PP_PROD_SPECIES_INDEX(pp) (PP_INJECTION(pp)->prod_species_index)
#define        PP_EVAP_SOURCE_INDEX(pp) (injection_par.yi2s[PP_INJECTION(pp)->evap_species_index])
#define       PP_DEVOL_SOURCE_INDEX(pp) (injection_par.yi2s[PP_INJECTION(pp)->devol_species_index])
#define        PP_OXID_SOURCE_INDEX(pp) (injection_par.yi2s[PP_INJECTION(pp)->oxid_species_index])
#define        PP_PROD_SOURCE_INDEX(pp) (injection_par.yi2s[PP_INJECTION(pp)->prod_species_index])
#define    PP_EVAP_SPECIES_MATERIAL(pp) (PP_INJECTION(pp)->evap_species)
#define   PP_DEVOL_SPECIES_MATERIAL(pp) (PP_INJECTION(pp)->devol_species)
#define    PP_OXID_SPECIES_MATERIAL(pp) (PP_INJECTION(pp)->oxid_species)
#define    PP_PROD_SPECIES_MATERIAL(pp) (PP_INJECTION(pp)->prod_species)
#define        PP_WET_COMB_MATERIAL(pp) (PP_INJECTION(pp)->evaporating_material)
#define PP_SOLID_SPECIES_FRACTION(pp,i) (PP_INJECTION(pp)->surface_species_fraction[i])

#if HAVE_OLD_P_MACROS
#define        P_EVAP_SPECIES_INDEX(p)  (P_INJECTION(p)->evap_species_index)
#define       P_DEVOL_SPECIES_INDEX(p)  (P_INJECTION(p)->devol_species_index)
#define        P_OXID_SPECIES_INDEX(p)  (P_INJECTION(p)->oxid_species_index)
#define        P_PROD_SPECIES_INDEX(p)  (P_INJECTION(p)->prod_species_index)
#define         P_EVAP_SOURCE_INDEX(p)  (injection_par.yi2s[P_INJECTION(p)->evap_species_index])
#define        P_DEVOL_SOURCE_INDEX(p)  (injection_par.yi2s[P_INJECTION(p)->devol_species_index])
#define         P_OXID_SOURCE_INDEX(p)  (injection_par.yi2s[P_INJECTION(p)->oxid_species_index])
#define         P_PROD_SOURCE_INDEX(p)  (injection_par.yi2s[P_INJECTION(p)->prod_species_index])
#define     P_EVAP_SPECIES_MATERIAL(p)  (P_INJECTION(p)->evap_species)
#define    P_DEVOL_SPECIES_MATERIAL(p)  (P_INJECTION(p)->devol_species)
#define     P_OXID_SPECIES_MATERIAL(p)  (P_INJECTION(p)->oxid_species)
#define     P_PROD_SPECIES_MATERIAL(p)  (P_INJECTION(p)->prod_species)
#define         P_WET_COMB_MATERIAL(p)  (P_INJECTION(p)->evaporating_material)
#define  P_SOLID_SPECIES_FRACTION(p,i)  (P_INJECTION(p)->surface_species_fraction[i])
#endif


#define TP_WET_COMBUSTION(tp) ((DPM_TYPE_COMBUSTING == TP_TYPE(tp)) && TP_INJECTION(tp)->wet_combustion)
#define TP_LIQUID(tp) ((DPM_TYPE_DROPLET        == TP_TYPE(tp)) || \
                       (DPM_TYPE_MULTICOMPONENT == TP_TYPE(tp)) || \
                       (TP_WET_COMBUSTION(tp) && (TP_LMF(tp)> DPM_SMALL)))
#define TP_COMBUSTING_SOLID(tp)   ((DPM_TYPE_COMBUSTING == TP_TYPE(tp)) && \
                 (TP_INJECTION(tp)->wet_combustion ? (TP_LMF(tp)< DPM_SMALL) : TRUE))
#define TP_DROP_MATERIAL_INDEX(tp) (TP_INJECTION(tp)->drop_material_index)
#define TP_COMB_MATERIAL_INDEX(tp) (TP_INJECTION(tp)->comb_material_index)


#define PP_WET_COMBUSTION(pp) ((DPM_TYPE_COMBUSTING == PP_TYPE(pp)) && PP_INJECTION(pp)->wet_combustion)
#define PP_LIQUID(pp) ((DPM_TYPE_DROPLET        == PP_TYPE(pp)) || \
                       (DPM_TYPE_MULTICOMPONENT == PP_TYPE(pp)) || \
                       (PP_WET_COMBUSTION(pp) && (PP_LMF(pp)> DPM_SMALL)))
#define PP_COMBUSTING_SOLID(pp)   ((DPM_TYPE_COMBUSTING == PP_TYPE(pp)) && \
                 (PP_INJECTION(pp)->wet_combustion ? (PP_LMF(pp)< DPM_SMALL) : TRUE))
#define PP_DROP_MATERIAL_INDEX(pp) (PP_INJECTION(pp)->drop_material_index)
#define PP_COMB_MATERIAL_INDEX(pp) (PP_INJECTION(pp)->comb_material_index)


#if HAVE_OLD_P_MACROS
#define  P_WET_COMBUSTION(p) ((DPM_TYPE_COMBUSTING == (p)->type) && P_INJECTION(p)->wet_combustion)
#define  P_LIQUID(p) ((DPM_TYPE_DROPLET        == (p)->type) || \
                      (DPM_TYPE_MULTICOMPONENT == (p)->type) || \
                      (P_WET_COMBUSTION(p) && (P_LMF(p)> DPM_SMALL)))
#define  P_COMBUSTING_SOLID(p)   ((DPM_TYPE_COMBUSTING == (p)->type) && \
                      (P_INJECTION(p)->wet_combustion ? (P_LMF(p)< DPM_SMALL) : TRUE))
#define  P_DROP_MATERIAL_INDEX(p) (P_INJECTION(p)->drop_material_index)
#define  P_COMB_MATERIAL_INDEX(p) (P_INJECTION(p)->comb_material_index)
#endif


#define TP_LAWS(tp, in) (CHECK_TP_TYPE(tp)->heat_mass_laws[in])
#if HAVE_OLD_P_MACROS
#define  P_LAWS(tp,in)    TP_LAWS(tp, in)
#endif

#define TP_STREAM_INDEX(tp) (CHECK_TP_TYPE(tp)->stream_index)
#define PP_STREAM_INDEX(pp) (CHECK_PP_TYPE(pp)->stream_index)

#define TP_CURRENT_LAW_INDEX(tp) (CHECK_TP_TYPE(tp)->current_law_index)
#define PP_CURRENT_LAW_INDEX(pp) (CHECK_PP_TYPE(pp)->current_law_index)
#if HAVE_OLD_P_MACROS
#define  P_CURRENT_LAW_INDEX(p)   ((p)->current_law_index)
#endif

#define TP_CURRENT_LAW(tp) (CHECK_TP_TYPE(tp)->heat_mass_laws[TP_CURRENT_LAW_INDEX(tp)])
#define TP_NEXT_LAW(tp) (CHECK_TP_TYPE(tp)->heat_mass_laws[TP_CURRENT_LAW_INDEX(tp) + 1])

#if HAVE_OLD_P_MACROS
#define  P_CURRENT_LAW(tp) TP_CURRENT_LAW(tp)   /* applicable for TP only */
#define     P_NEXT_LAW(tp)    TP_NEXT_LAW(tp)   /* applicable for TP only */
#endif


#define TP_CBK(tp, i) (CHECK_TP_TYPE(tp)->cbk[i])
#define PP_CBK(pp, i) (CHECK_PP_TYPE(pp)->cbk[i])

#define TP_SCALAR(tp, i) (CHECK_TP_TYPE(tp)->scalar[i])
#define PP_SCALAR(pp, i) (CHECK_PP_TYPE(pp)->scalar[i])

#define TP_ACCUMULATED_BREAKUP_TIME(tp) (CHECK_TP_TYPE(tp)->scalar[5])
#define TP_PILCH_ERDMAN_DEFORMATION_TIME(tp) (CHECK_TP_TYPE(tp)->scalar[6])
#define TP_PILCH_ERDMAN_BREAKUP_TIME(tp) (CHECK_TP_TYPE(tp)->scalar[7])
#define TP_PILCH_ERDMAN_TOTAL_BREAKUP_TIME(tp) (CHECK_TP_TYPE(tp)->scalar[8])
#define TP_PILCH_ERDMAN_INITIAL_WEBER_NUMBER(tp) (CHECK_TP_TYPE(tp)->scalar[9])
#define TP_PILCH_ERDMAN_INITIAL_DIAMETER(tp) (CHECK_TP_TYPE(tp)->scalar[10])
#define TP_MADABHUSHI_COLUMN_BREAKUP_TIME(tp) (CHECK_TP_TYPE(tp)->scalar[11])
#define TP_MADABHUSHI_B0(tp) (CHECK_TP_TYPE(tp)->scalar[12])
#define TP_MADABHUSHI_B1(tp) (CHECK_TP_TYPE(tp)->scalar[13])

#define TP_SCHMEHL_BREAKUP_REGIME(tp) (CHECK_TP_TYPE(tp)->scalar[11])
#define TP_SCHMEHL_CRITICAL_WEBER_NUMBER(tp) (CHECK_TP_TYPE(tp)->scalar[12])
#define TP_SCHMEHL_LIQUID_CORE_MASS_FACTOR(tp) (CHECK_TP_TYPE(tp)->scalar[13])

#define PP_ACCUMULATED_BREAKUP_TIME(pp) (CHECK_PP_TYPE(pp)->scalar[5])
#define PP_PILCH_ERDMAN_DEFORMATION_TIME(pp) (CHECK_PP_TYPE(pp)->scalar[6])
#define PP_PILCH_ERDMAN_BREAKUP_TIME(pp) (CHECK_PP_TYPE(pp)->scalar[7])
#define PP_PILCH_ERDMAN_TOTAL_BREAKUP_TIME(pp) (CHECK_PP_TYPE(pp)->scalar[8])
#define PP_PILCH_ERDMAN_INITIAL_WEBER_NUMBER(pp) (CHECK_PP_TYPE(pp)->scalar[9])
#define PP_PILCH_ERDMAN_INITIAL_DIAMETER(pp) (CHECK_PP_TYPE(pp)->scalar[10])
#define PP_MADABHUSHI_COLUMN_BREAKUP_TIME(pp) (CHECK_PP_TYPE(pp)->scalar[11])
#define PP_MADABHUSHI_B0(pp) (CHECK_PP_TYPE(pp)->scalar[12])
#define PP_MADABHUSHI_B1(pp) (CHECK_PP_TYPE(pp)->scalar[13])

#define PP_SCHMEHL_BREAKUP_REGIME(pp) (CHECK_PP_TYPE(pp)->scalar[11])
#define PP_SCHMEHL_CRITICAL_WEBER_NUMBER(pp) (CHECK_PP_TYPE(pp)->scalar[12])
#define PP_SCHMEHL_LIQUID_CORE_MASS_FACTOR(pp) (CHECK_PP_TYPE(pp)->scalar[13])

#define TP_USER_REAL(tp, i) (CHECK_TP_TYPE(tp)->user[i])
#define PP_USER_REAL(pp, i) (CHECK_PP_TYPE(pp)->user[i])
#if HAVE_OLD_P_MACROS
#define  P_USER_REAL(p,i)    ((p)->user[i])
#endif
#endif  /* !UDF_COMPILER */

#define TP_FILM_THREAD_ID(tp)     THREAD_ID(TP_FILM_THREAD(tp))
#define PP_FILM_THREAD_ID(pp)       (CHECK_PP_TYPE(pp)->wallfilm_thread_id)
#define TP_FILM_THREAD(tp)          (CHECK_TP_TYPE(tp)->wallfilm_thread)    /* replaces an older, similar definition elsewhere */
#define PP_FILM_THREAD(domain,pp) (Lookup_Thread_All(domain,PP_FILM_THREAD_ID(pp)))
#if HAVE_OLD_P_MACROS
#define  P_FILM_THREAD_ID(pp)      PP_FILM_THREAD_ID(pp)      /* is it correct that this is called for Particles only? */
#define  P_FILM_THREAD(domain,pp)  PP_FILM_THREAD(domain,pp)  /* ...and this TOO..? */
#endif

#define P_INJ_ID(I) ((I)->try_id)

#define P_INJ_VINDEX_I(I,pv) ((I)->pv_index[pv])
#define P_INJ_VSIZE_I(I,pv)  ((I)->pv_size[pv])
#define PP_VAR(pp,pvi,type)   ((type *) (((char *) (pp)) + (pvi)))

#define PP_STORAGE(p,pv,type) PP_VAR(p, P_INJ_VINDEX_I(PP_INJECTION(p),pv), type)
#if HAVE_OLD_P_MACROS
#define  P_VAR(p,pvi,type)    PP_VAR(p,pvi,type)
#define  P_STORAGE(p,pv,type) PP_STORAGE(p,pv,type)   /* applicable for PP only */
#endif

#define P_INJ_VAR_P(I,pv) (P_INJ_VSIZE_I(I,pv) > 0)
#define P_INJ_ANY_VAR_P(I) (0 != P_INJ_VINDEX_I(I,PV_MAX) - P_INJ_VINDEX_I(I,0))

#define P_INJ_MATERIAL(I) ((I)->material)
#define P_INJ_N_COMPONENTS(I) ((I)->material->n_components)

/* #define TP_N_COMPONENTS(p) P_INJ_N_COMPONENTS(TP_INJECTION(p)) -- conflicts with a different definition below. */
#define PP_N_COMPONENTS(p) P_INJ_N_COMPONENTS(PP_INJECTION(p))
#if HAVE_OLD_P_MACROS
#define  P_N_COMPONENTS(p) P_INJ_N_COMPONENTS(P_INJECTION(p))
#endif

#define PP_COMPONENT(p)          (PP_STORAGE(p, PV_COMPONENT,real))
#define PP_COMPONENT_I(p,i)      (PP_COMPONENT(p)[i])
#define PP_COMPONENT_INIT(p)     (PP_STORAGE(p, PV_COMPONENT_INIT,real))
#define PP_COMPONENT_INIT_I(p,i) (PP_COMPONENT_INIT(p)[i])

#define PP_REACTING_STATE_MASS(p) (PP_STORAGE(p, PV_REACTING_STATE, real))
#define PP_REACTING_STATE_COHREADM(p)           (PP_REACTING_STATE_MASS(p)[solver_par.nSpecies + solver_par.nSpeSurf])
#define PP_REACTING_STATE_REACT(p)            (&(PP_REACTING_STATE_MASS(p)[solver_par.nSpecies + solver_par.nSpeSurf + 1]))

#if HAVE_OLD_P_MACROS             /* All applicable for PP only: */
#define  P_COMPONENT(p)           PP_COMPONENT(p)
#define  P_COMPONENT_I(p,i)       PP_COMPONENT_I(p,i)
#define  P_COMPONENT_INIT(p)      PP_COMPONENT_INIT(p)
#define  P_COMPONENT_INIT_I(p,i)  PP_COMPONENT_INIT_I(p,i)

#define  P_REACTING_STATE_MASS(p)      PP_REACTING_STATE_MASS(p)
#define  P_REACTING_STATE_COHREADM(p)  PP_REACTING_STATE_COHREADM(p)
#define  P_REACTING_STATE_REACT(p)     PP_REACTING_STATE_REACT(p)
#endif

#define PP_CPD_STATE(p) (PP_STORAGE(p,PV_CPD_STATE,cpd_state_t))
#define PP_VFF_REAL(p)  (PP_STORAGE(p,PV_VFF_REAL,real))

#define PP_COLLISION(p) (PP_STORAGE(p,PV_COLLISION,pv_collision_t))
#if RP_2D
#define PP_N_INVAR2D(p) (PP_STORAGE(p,PV_COLLISION2D,pv_collision2d_t)->n_invariant) /* Note: a real value! */
#endif

#define PP_PARTICLE_CONTACTS(p) (PP_STORAGE(p,PV_CONTACT_PARTICLE,Particle_Contact*))[0]
#define PP_FACE_CONTACTS(p)     (PP_STORAGE(p,PV_CONTACT_FACE,Face_Contact*))[0]

#if HAVE_OLD_P_MACROS   /* All applicable for PP only: */
#define  P_CPD_STATE(p) PP_CPD_STATE(p)
#define  P_VFF_REAL(p)  PP_VFF_REAL(p)
#define  P_COLLISION(p) PP_COLLISION(p)
#if RP_2D
#define  P_N_INVAR2D(p) PP_N_INVAR2D(p)
#endif

#define  P_PARTICLE_CONTACTS(p) PP_PARTICLE_CONTACTS(p)
#define  P_FACE_CONTACTS(p)     PP_FACE_CONTACTS(p)
#endif

#define TP_STOCHASTIC_NTRIES(p) DPM_STOCHASTIC_NTRIES(TP_INJECTION(p))  /* DOES check dpm_par.unsteady_tracking. */
#define TP_STOCHASTIC(p)        DPM_STOCHASTIC_P(TP_INJECTION(p))       /* Does NOT check dpm_par.unsteady_tracking. */
#define TP_CLOUD_MODEL(p)       DPM_CLOUD_MODEL_P(TP_INJECTION(p))      /* Does NOT check dpm_par.unsteady_tracking. */
#define TP_PHASE_DOMAIN(p)      DPM_PHASE_DOMAIN(TP_INJECTION(p))

#define PP_STOCHASTIC_NTRIES(p) DPM_STOCHASTIC_NTRIES(PP_INJECTION(p))  /* DOES check dpm_par.unsteady_tracking. */
#define PP_STOCHASTIC(p)        DPM_STOCHASTIC_P(PP_INJECTION(p))       /* Does NOT check dpm_par.unsteady_tracking. */
#define PP_CLOUD_MODEL(p)       DPM_CLOUD_MODEL_P(PP_INJECTION(p))      /* Does NOT check dpm_par.unsteady_tracking. */
#define PP_PHASE_DOMAIN(p)      DPM_PHASE_DOMAIN(PP_INJECTION(p))

#if HAVE_OLD_P_MACROS
#define  P_STOCHASTIC_NTRIES(p) DPM_STOCHASTIC_NTRIES(P_INJECTION(p))  /* DOES check dpm_par.unsteady_tracking. */
#define  P_STOCHASTIC(p)        DPM_STOCHASTIC_P(P_INJECTION(p))       /* Does NOT check dpm_par.unsteady_tracking. */
#define  P_CLOUD_MODEL(p)       DPM_CLOUD_MODEL_P(P_INJECTION(p))      /* Does NOT check dpm_par.unsteady_tracking. */
#define  P_PHASE_DOMAIN(p)      DPM_PHASE_DOMAIN(P_INJECTION(p))
#endif

#define PP_TURB_EDDY(p)      (PP_STORAGE(p, PV_TURB_EDDY, real))
#define PP_TURB_DAMPENING(p) (PP_STORAGE(p, PV_TURB_DAMPENING, real))
#define PP_OMEGA(p)          (PP_STORAGE(p, PV_OMEGA, real))
#define PP_QUATERNION(p)     (PP_STORAGE(p, PV_QUATERNION, real))
#define PP_FILM_HEIGHT(p)    (PP_STORAGE(p, PV_WALL_FILM, real))
#define PP_BL_FILM_NU(p)     (PP_STORAGE(p, PV_BL_FILM_NU, real))
#define PP_RANDOM_SEED(p)    (PP_STORAGE(p, PV_RANDOM_SEED, gauss_random_seed))

#if HAVE_OLD_P_MACROS
#define P_TURB_EDDY(p)      PP_TURB_EDDY(p)
#define P_TURB_DAMPENING(p) PP_TURB_DAMPENING(p)
#define P_OMEGA(p)          PP_OMEGA(p)
#define P_QUATERNION(p)     PP_QUATERNION(p)
#define P_FILM_HEIGHT(p)    PP_FILM_HEIGHT(p)
#define P_RANDOM_SEED(p)    PP_RANDOM_SEED(p)
#endif

#define TP_FILM_HEIGHT(tp) (CHECK_TP_TYPE(tp)->film_height)
#define TP_RANDOM_SEED(tp) (&(CHECK_TP_TYPE(tp)->random_seed))

#define TP_N_COMPONENTS(tp) (CHECK_TP_TYPE(tp)->component.n)
#define TP_COMPONENT(tp) (CHECK_TP_TYPE(tp)->component.state)
#define TP_COMPONENT_I(tp,i) (CHECK_TP_TYPE(tp)->component.state[i])
#define TP_COMPONENT0(tp) (CHECK_TP_TYPE(tp)->component.state0)
#define TP_COMPONENT0_I(tp,i) (CHECK_TP_TYPE(tp)->component.state0[i])
#define TP_COMPONENT_INIT(tp) (CHECK_TP_TYPE(tp)->component.init)
#define TP_COMPONENT_INIT_I(tp,i) (CHECK_TP_TYPE(tp)->component.init[i])
#define TP_COMPONENT_INDEX(tp) (CHECK_TP_TYPE(tp)->component.fluid_index)
#define TP_COMPONENT_INDEX_I(tp,i) (CHECK_TP_TYPE(tp)->component.fluid_index[i])

#define TP_BREAKUP_TYPE(tp) (CHECK_TP_TYPE(tp)->breakup)
#define PP_BREAKUP_TYPE(pp) (CHECK_PP_TYPE(pp)->breakup)
#if HAVE_OLD_P_MACROS
#define  P_BREAKUP_TYPE(p)   ((p)->breakup)
#endif

#define TP_LEVICH_BREAKUP_CONST(tp) ( /* TP_BREAKUP_TYPE(tp) == BREAKUP_KHRT  ? */ \
                                        (TP_INJECTION(tp)->seco_breakup_khrt) ?    \
                                         TP_INJECTION(tp)->seco_breakup_khrt_cl :  \
                                         dpm_par.levich_breakup_const)
#if HAVE_OLD_P_MACROS           /* _This could probably be replaced by TP_...(tp). */
#define  P_LEVICH_BREAKUP_CONST(tp)  ( /* P_BREAKUP_TYPE(tp) == BREAKUP_KHRT  ? */ \
                                         (P_INJECTION(tp)->seco_breakup_khrt) ?    \
                                          P_INJECTION(tp)->seco_breakup_khrt_cl :  \
                                         dpm_par.levich_breakup_const)
#endif

/* DEM Contact Management: Contact Flags for Friction, Sliding and Torsion Models */

#define CONTACT_FLAGS(contact) ((contact)->flags)

#define DEM_CONTACT_SLIDING (1)
#define DEM_CONTACT_ROLLING (1<<1)
#define DEM_CONTACT_TORSION (1<<2)

#define DEM_CONTACT_FLAG(contact, flag)       (CONTACT_FLAGS(contact) &  (flag))
#define DEM_SET_CONTACT_FLAG(contact, flag)   (CONTACT_FLAGS(contact) |=  (flag))
#define DEM_CLEAR_CONTACT_FLAG(contact, flag) (CONTACT_FLAGS(contact) &= ~(flag))

/* Interaction with Eulerian Phase */
#define TP_INTERACT_DOMAIN_INDX(tp) (DPM_INTERACT_DOMAIN_INDX(TP_INJECTION(tp)))
#define TP_CPHASE_INDX(tp, phase) (CHECK_TP_TYPE(tp)->cphase[phase].domain_idx)
/**
 * Number of Eulerian phases considered for interaction
 * in Discrete Particle Tracking model. */
#define DPM_N_PHASES(I) ((mp_mfluid && DPM_INTERACT_WITH_ALL_PHASES(I)) ? DOMAIN_N_DOMAINS(root_domain) : 1)
#define TP_N_PHASES(tp) (CHECK_TP_TYPE(tp)->n_cphases)

#define TP_UDMI_AVAILABLE(tp) (NNULLP(CHECK_TP_TYPE(tp)->cphase->udmi))
#define TP_UDMI(tp,i)         (CHECK_TP_TYPE(tp)->cphase->udmi[i])

#define TP_HTC_METHOD(tp) (TP_INJECTION(tp)->htc_correlation)

typedef struct Particle_Search_Data_t_
{
  /* For 2d cases, DPM particles might still in 3d, z is the third coordinate of dpm particles,
   * which will be passed into particle search callback function as attached data here
   */
#if RP_2D
  real z;
#endif
  real time;
  CX_Cell_Id *current_cell;
  Particle *p_ptr;

  struct
  {
    real u[3];
    real d;
    real p;
    real temperature;
    real fr;
    int ci;
    int64_t pid;

    unsigned int rand_uvar[3];
    real rg;

    real ft;
    real dt;
  } data;
} particle_search_data_t;

typedef struct Particle_Search_Partition_Data_t_
{
  int max_depth;
  struct
  {
    int transfer_seeds;
    int transfer_flow_and_dura_time;
  } para;
  Particle *curr_p;
} particle_search_partition_data_t;
#endif /* _FLUENT_DPM_TYPES_H */
