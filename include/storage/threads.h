/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_THREADS_H
#define _FLUENT_THREADS_H

#include "dll.h"

/* Thread types */
typedef enum
{
  THREAD_NULL = 0,
  THREAD_C_GENERIC = 1,
  THREAD_F_INTERIOR = 2,
  THREAD_F_WALL = 3,
  THREAD_F_PINLET = 4,
  THREAD_F_POUTLET = 5,
  THREAD_F_PERIODIC_OLD = 6,
  THREAD_F_SYMMETRIC = 7,
  THREAD_F_SHADOW = 8,
  THREAD_F_PFAR = 9,
  THREAD_F_VINLET = 10,
  THREAD_F_VOUTLET = 11,  /* obsolete */
  THREAD_F_PERIODIC = 12,
  THREAD_F_VFAR = 13,   /* obsolete */
  THREAD_F_JUMP = 14,
  THREAD_F_INTERNAL = 15,
  THREAD_C_SOLID = 17,    /* obsolete, merged into THREAD_C_GENERIC */
  THREAD_F_MFINLET = 20,
  THREAD_F_SLIDING_BOUNDARY = 24,
#if RP_OVERSET
  THREAD_F_OVERSET = 25,
#endif
  THREAD_F_WRAPPER = 29,
  THREAD_F_BRIDGE = 30,   /* obsolete */
  THREAD_F_PARENT = 31,
  THREAD_C_PARENT = 32,
  THREAD_F_OUTFLOW = 36,
  THREAD_F_AXIS = 37,
  THREAD_F_SI_PARENT = 38,      /* obsolete, for perpendicular face creation
                                   of old non-conformal interface */
  THREAD_N_GENERIC = 39,  /* node thread */

  THREAD_F_UNREFERENCED = 40,   /* facetted geometry */
  THREAD_NETWORK = 51,
  THREAD_NETWORK_END = 52,

  THREAD_TYPE_CNZ = 55,
  THREAD_TYPE_FNZ = 56,
#if USE_FEMCORE
  THREAD_TYPE_CINZ = 57,
  THREAD_TYPE_FINZ = 58,
#endif
  THREAD_TYPE_MAX
} Thread_Type;

/* When adding a new thread type, be sure to update the thread_type_names array
 * in threads.c and to create a new thread object in rpthreads.scm.  (If the
 * thread type is for internal solver use only, that is, not to be seen in the
 * user-interface, these steps can be omitted.)
 *
 * THREAD_TYPEs of threads which are saved in case files should
 * never be changed.
 */

/* Thread flags */

#define THREAD_FL_CELL     (1)
#define THREAD_FL_FACE     (1<<1)
#define THREAD_FL_BOUNDARY_FACE  (1<<2) /* non-removable, else removable */
#define THREAD_FL_INTERNAL_FACE  (1<<3) /* has two cell pointers, else one */
#define THREAD_FL_PERIODIC_FACE  (1<<4)
#define THREAD_FL_EXTERIOR_CELL  (1<<5)
#define THREAD_FL_NODELESS_FACE  (1<<6) /* created from sliding boundaries */
#define THREAD_FL_SLIDING_INTERFACE (1<<7) /* created from sliding boundaries*/
#define THREAD_FL_SHADOW_FACE    (1<<8)
#define THREAD_FL_MAJOR_FACE     (1<<9)
#define THREAD_FL_MINOR_FACE     (1<<10)
#define THREAD_FL_COARSE_LEVEL   (1<<11) /* coarse grid level (FAS multigrid) */
#define THREAD_FL_TAG            (1<<12)
#define THREAD_FL_SHELL_FACE     (1<<13) /* shell face thread */
#define THREAD_FL_SHELL_CELL     (1<<14) /* shell cell thread */
#define THREAD_FL_SHELL_JUNCTION (1<<15) /* shell junction thread */
#define THREAD_FL_DEFORMING      (1<<16) /* deforming thread flag */
#define THREAD_FL_MOVING         (1<<17)
#define THREAD_FL_NODE     (1<<18)
#define THREAD_FL_REMESH         (1<<19) /* remeshing flag */
#define THREAD_FL_GEOMETRY       (1<<20)
#define THREAD_FL_NETWORK_CELL   (1<<21) /* network cell */
#define THREAD_FL_NETWORK_FACE   (1<<22) /* network face */
#define THREAD_FL_MARK           (1<<23)
#define THREAD_FL_DEACTIVATED    (1<<24)
#define THREAD_FL_NEW            (1<<25)
#define THREAD_FL_EXTENDED       (1<<28)
#define THREAD_FL_DUAL           (1<<29)
#define THREAD_FL_STRETCHED_INTERFACE (1<<30) /* interface stretching; same flag
             is used for both the ghost
             cells and the interface */
#define THREAD_FL_LABEL          (1<<31)
/* Thread flag is (unsigned int), and cannot carry more flags.
   The Intel compiler currently doesn't allow larger shift operations
   and making the flag (long) is not an option to get more flags. */
#define THREAD_FL_CNZ            4294967296 /* (1<<32) cell nodal zone */
#define THREAD_FL_FNZ            8589934592 /* (1<<33) face nodal zone */
#if USE_FEMCORE
#define THREAD_FL_CINZ           17179869184 /* (1<<34) cell interpolation nodal zone */
#define THREAD_FL_FINZ           34359738368 /* (1<<35) face interpolation nodal zone */
#endif
/* Thread predicates */

#define CELL_THREAD_P(t)(THREAD_FLAGS(t) & THREAD_FL_CELL)
#define FACE_THREAD_P(t)(THREAD_FLAGS(t) & THREAD_FL_FACE)
#define NODE_THREAD_P(t)(THREAD_FLAGS(t) & THREAD_FL_NODE)
#define INTERNAL_FACE_THREAD_P(t)(THREAD_FLAGS(t) & THREAD_FL_INTERNAL_FACE)
#define INTERIOR_FACE_THREAD_P(t)(INTERNAL_FACE_THREAD_P(t) && THREAD_T0(t) == THREAD_T1(t))
#define BOUNDARY_FACE_THREAD_P(t)(THREAD_FLAGS(t) & THREAD_FL_BOUNDARY_FACE)
#define PERIODIC_FACE_THREAD_P(t)(THREAD_FLAGS(t) & THREAD_FL_PERIODIC_FACE)
#define PERIODIC_OR_PERIODIC_SHADOW_THREAD_P(t) \
  (PERIODIC_FACE_THREAD_P(t) || \
   (NNULLP(THREAD_SHADOW(t)) && PERIODIC_FACE_THREAD_P(THREAD_SHADOW(t))))
#define SHADOW_FACE_THREAD_P(t)(THREAD_FLAGS(t) & THREAD_FL_SHADOW_FACE)
#define EXTERIOR_CELL_THREAD_P(t)(THREAD_FLAGS(t) & THREAD_FL_EXTERIOR_CELL)
#define NODELESS_FACE_THREAD_P(t)(THREAD_FLAGS(t) & THREAD_FL_NODELESS_FACE)
#define SLIDING_INTERFACE_THREAD_P(t)(THREAD_FLAGS(t) & THREAD_FL_SLIDING_INTERFACE)
#define STRETCHED_INTERFACE_THREAD_P(t)(THREAD_FLAGS(t) & THREAD_FL_STRETCHED_INTERFACE)
#define GHOST_CELL_THREAD_P(t) (THREAD_FLAGS(t) & THREAD_FL_STRETCHED_INTERFACE)

#define SLIDING_BOUNDARY_THREAD_P(t)(THREAD_TYPE(t)==THREAD_F_SLIDING_BOUNDARY)
#define HELPER_THREAD_P(t) ((t) == HELPER_THREAD(t))
#define MAPPED_THREAD_P(t) ((t) == MAPPED_THREAD(t))
#if RP_OVERSET
#define OVERSET_FACE_THREAD_P(t)(THREAD_TYPE(t)==THREAD_F_OVERSET)
#define OVERSET_EXTENDED_INTERIOR_THREAD_P(t)(EXTENDED_THREAD_P(t) && \
                                              DUAL_THREAD_P(t))
#endif
#define COARSE_LEVEL_THREAD_P(t)(THREAD_FLAGS(t) & THREAD_FL_COARSE_LEVEL)

#define MAJOR_FACE_THREAD_P(t)(THREAD_FLAGS(t) & THREAD_FL_MAJOR_FACE)
#define MINOR_FACE_THREAD_P(t)(THREAD_FLAGS(t) & THREAD_FL_MINOR_FACE)
#define COUPLED_WALL_FACE_THREAD_P(t)(THREAD_TYPE(t) == THREAD_F_WALL && (THREAD_FLAGS(t) & \
         (THREAD_FL_MAJOR_FACE | THREAD_FL_MINOR_FACE)))
#define COUPLED_FACE_THREAD_P(t)(THREAD_FLAGS(t) & \
         (THREAD_FL_MAJOR_FACE | THREAD_FL_MINOR_FACE))
#define FLUID_CELL_THREAD_P(t)(CELL_THREAD_P(t) && FLUID_THREAD_P(t))
#define SOLID_CELL_THREAD_P(t)(CELL_THREAD_P(t) && SOLID_THREAD_P(t))
#define STRUCTURE_CELL_THREAD_P(t)(CELL_THREAD_P(t) && STRUCTURE_THREAD_P(t))

#define TAGGED_THREAD_P(t)(THREAD_FLAGS(t) & THREAD_FL_TAG)
#define TAG_THREAD(t)(THREAD_FLAGS(t) |= THREAD_FL_TAG)
#define UNTAG_THREAD(t)(THREAD_FLAGS(t) &= ~THREAD_FL_TAG)

#define MARKED_THREAD_P(t)(THREAD_FLAGS(t) & THREAD_FL_MARK)
#define MARK_THREAD(t)(THREAD_FLAGS(t) |= THREAD_FL_MARK)
#define UNMARK_THREAD(t)(THREAD_FLAGS(t) &= ~THREAD_FL_MARK)

#define LABELED_THREAD_P(t)(THREAD_FLAGS(t) & THREAD_FL_LABEL)
#define LABEL_THREAD(t)(THREAD_FLAGS(t) |= THREAD_FL_LABEL)
#define UNLABEL_THREAD(t)(THREAD_FLAGS(t) &= ~THREAD_FL_LABEL)

#define SHELL_FACE_THREAD_P(t) (THREAD_FLAGS(t) & THREAD_FL_SHELL_FACE)
#define SHELL_CELL_THREAD_P(t) (NNULLP(t) && (THREAD_FLAGS(t) & THREAD_FL_SHELL_CELL))
#define SHELL_JUNCTION_THREAD_P(t) (THREAD_FLAGS(t) & THREAD_FL_SHELL_JUNCTION)

#define WALL_THREAD_P(t) (THREAD_TYPE(t)==THREAD_F_WALL)
#define SHELL_SKIP_THREAD_P(t) (WALL_THREAD_P(t) && \
                                SHELL_FACE_THREAD_P(t) && \
                                THREAD_VAR(t).wall.thermal_bc == THERMAL_BC_SKIP)

#define NETWORK_CELL_THREAD_P(t) (THREAD_FLAGS(t) & THREAD_FL_NETWORK_CELL)
#define NETWORK_FACE_THREAD_P(t) (THREAD_FLAGS(t) & THREAD_FL_NETWORK_FACE)

#define EXTENDED_THREAD_P(t) (THREAD_FLAGS(t) & THREAD_FL_EXTENDED)

#define TWO_CELL_FACE_THREAD_P(t)((THREAD_FLAGS(t) & \
   (THREAD_FL_INTERNAL_FACE | THREAD_FL_PERIODIC_FACE | THREAD_FL_SHADOW_FACE)) | \
    (!WALL_THREAD_P(t) && MAJOR_FACE_THREAD_P(t)))

#define TWO_CELL_SIDED_FACE_P(f, t)                                 \
  ( !NULL_CELL_P(F_C0 (f, t)) && NNULLP(F_C0_THREAD (f, t)) &&      \
    !NULL_CELL_P(F_C1 (f, t)) && NNULLP(F_C1_THREAD (f, t)))

/* thread flags manipulation macros */
#define SET_THREAD_FLAGS(t,flag) (THREAD_FLAGS(t) |= ((size_t)(flag)))
#define CLEAR_THREAD_FLAGS(t,flag) (THREAD_FLAGS(t) &= ~((size_t)(flag)))

#define DEFORMING_THREAD_P(t) (THREAD_FLAGS(t) & THREAD_FL_DEFORMING)
#define MOVING_THREAD_P(t)    (THREAD_FLAGS(t) & THREAD_FL_MOVING)
#define REMESH_THREAD_P(t)    (THREAD_FLAGS (t) & THREAD_FL_REMESH)

#define SET_DEFORMING_THREAD_FLAG(t) SET_THREAD_FLAGS(t,THREAD_FL_DEFORMING)
#define UNSET_DEFORMING_THREAD_FLAG(t) CLEAR_THREAD_FLAGS(t,THREAD_FL_DEFORMING)
#define SET_REMESH_THREAD_FLAG(t) SET_THREAD_FLAGS(t,THREAD_FL_REMESH)
#define UNSET_REMESH_THREAD_FLAG(t) CLEAR_THREAD_FLAGS(t,THREAD_FL_REMESH)

#define THREAD_FLAG_P(t,flags) (THREAD_FLAGS(t) & ((size_t)(flags)))

/* active thread booleans */
#define GENERIC_CELL_THREAD_P(t)(THREAD_TYPE(t)==THREAD_C_GENERIC)

/* parent thread booleans */
#define PARENT_FACE_THREAD_P(t)(THREAD_TYPE(t)==THREAD_F_PARENT)
#define PARENT_CELL_THREAD_P(t)(THREAD_TYPE(t)==THREAD_C_PARENT)
#define PARENT_THREAD_P(t)\
   ((THREAD_TYPE(t)==THREAD_F_PARENT) || (THREAD_TYPE(t)==THREAD_C_PARENT))
#define HAS_PARENT_THREAD_P(t)(NULLP(THREAD_PARENT(t)) ? 0 : 1)

#define SI_PARENT_FACE_THREAD_P(t)(THREAD_TYPE(t)==THREAD_F_SI_PARENT) /* obsolete, used for perpendicular face of old nonconformal interface */
#define DEACTIVATED_THREAD_P(t) (THREAD_FLAGS(t) & THREAD_FL_DEACTIVATED)
#define UNREFERENCED_THREAD_P(t) (THREAD_TYPE(t) == THREAD_F_UNREFERENCED)
#define NEW_THREAD_P(t) (THREAD_FLAGS(t) & THREAD_FL_NEW)

#define DUAL_THREAD_P(t) (THREAD_FLAGS(t) & THREAD_FL_DUAL)

#define FIXED_THREAD_P(t) \
  (COUPLED_FACE_THREAD_P (t) || (THREAD_T0 (t) != THREAD_T1 (t)))

#define CNZ_THREAD_P(t)((THREAD_FLAGS(t) & THREAD_FL_CNZ) > 0)
#define FNZ_THREAD_P(t)((THREAD_FLAGS(t) & THREAD_FL_FNZ) > 0)

#if USE_FEMCORE
#define CINZ_THREAD_P(t)((THREAD_FLAGS(t) & THREAD_FL_CINZ) > 0)
#define FINZ_THREAD_P(t)((THREAD_FLAGS(t) & THREAD_FL_FINZ) > 0)
#endif

#include "profile.h"

/* turbulence specification methods */
enum
{
  TURB_SPEC_VALUE = 0,
  TURB_SPEC_INTENS_LEN,
  TURB_SPEC_INTENS_RATIO,
  TURB_SPEC_INTENS_DIAM,
  TURB_SPEC_EPS_OMEGA,
  TURB_SPEC_MIXING_PLANE
};

/* subgrid-scale k  specification methods */
enum
{
  KSGS_SPEC_VALUE = 0,
  KSGS_SPEC_INTENSITY
};

#define  OPT_STR_VAR_VAL_LEN  64

/* les inlet specification methods */
#ifndef _FLUENT_THREADS_C
FLUENT_EXPORT extern char les_spec_name_strings[][OPT_STR_VAR_VAL_LEN];
#else
/* Create the following exactly once in threads.o,
 * but have the source code here in order to keep
 * it in perfect sync with the enum below it.
 * These name strings must be consistent with
 * what is used on the Scheme side..!!
 */
char les_spec_name_strings[][OPT_STR_VAR_VAL_LEN] =
{
  "No Perturbations",
  "Vortex Method",
  "Spectral Synthesizer",
  "Random Perturbations",
  "Synthetic Turbulence Generator",
  ""
};
#endif
typedef enum
{
  LES_SPEC_NO_PERTURB = 0,
  LES_SPEC_VORTEX_METHOD = 1,
  LES_SPEC_RFG = 2,
  LES_SPEC_RANDOM_PERTURB = 3,
  LES_SPEC_SYNTHETIC_TURBULENCE_GENERATOR = 4
} LES_Spec_Type;

/* MAX_DO_BANDS needed for f_wall.h (and sg_disco.{ch}) */
/*#define MAX_DO_BANDS 50*/

typedef struct udf_thread_data_struct  /* data structure to cache udfs */
{
  char *name;
  cxboolean used;
  void (*fcn)(void);    /* pointer to a function returning void */
} UDF_Thread_Data;

#define MAX_IMP 10

struct impedance_struct
{
  real d;

  int n1;
  real lambda[MAX_IMP];
  real a[MAX_IMP];

  int n2;
  real alpha[MAX_IMP];
  real beta[MAX_IMP];

  real b[MAX_IMP];
  real c[MAX_IMP];
};

typedef struct impedance_struct Impedance;

/**
 * \brief Additional storage used during automatic initialization.
 *
 * Make it a union because average pressure is only needed for mixing planes,
 * and pressure_from_bc flag is only for boundaries that are not mixing planes.
 */
typedef union initialization_bc_data_union
{
  cxboolean pressure_from_bc; /**< whether specified static pressure is used */
  real pavg_at_mp;            /**< average pressure at mixing plane interface */
} Initialization_BC_Data;

/**********************************************************
 * Thread variable declarations
 **********************************************************/
/*comment_rsy : add the value of dw as std_flow_boundary bc option */
/* standard boundary variables used by mfi, outflow, pfar, pi, po, vi */
/* below follows a macro that tells whether a thread type uses this.. */

#define STD_FLOW_BOUNDARY_BCS \
  int turb_spec;    /* turbulence specification method: */ \
        /* 0 = specified value*/ \
        /* 1 = intensity, length scale */ \
        /* 2 = intensity, viscosity ratio */ \
                                /* 3 = intensity, hyd diam */ \
                                /* 4 = mixing plane */ \
  int ksgs_spec;    /* subgrid k  specification method: */ \
        /* 0 = specified value*/ \
                                /* 1 = intensity */ \
  Profile nut,kl,k,ksgs,e,v2,o,intermit,turb_viscosity_ratio_prof; \
  real turb_intensity; \
  real sgs_turb_intensity; \
  real turb_length_scale; \
  real turb_hydraulic_diam; \
  real turb_viscosity_ratio; \
 \
  int rst_spec;                 /* Reynolds-stress specification method */ \
                                /* 0 = reynolds-stress components       */ \
                                /* 1 = computed from turbulence intensity */ \
  Profile uu,vv,ww,uv,vw,uw; \
 \
  Profile vof;            /* volume fractions */ \
 \
 Profile gt;                    /* granular temperature */ \
 \
  Profile *yi;                  /* species mass / mole fractions */ \
  cxboolean species_in_mole_frac;  /* mole fractions specified at inlets ? */ \
 \
  Profile phi1;                 /* electric potential */ \
  int phi1_type;                /* electric potential BC type */ \
 \
  int x_disp_type;              /* x displacement BC type */ \
  Profile x_disp_value;         /* x displacement */ \
  int y_disp_type;              /* y displacement BC type */ \
  Profile y_disp_value;         /* y displacement */ \
  int z_disp_type;              /* z displacement BC type */ \
  Profile z_disp_value;         /* z displacement */ \
 \
 Profile dw[NUM_ENV]; \
 cxboolean equ_required;       /* equilibrium calculation required at mixed inlets?*/ \
 \
 Profile *uds;                 /* user defined scalar bc's */ \
  int *uds_bc_type; \
 \
  Profile *pb_disc;            /* population balance bc */ \
  int *pb_disc_bc_type; \
 \
  Profile *pb_qmom;            /* population balance bc */ \
  int *pb_qmom_bc_type; \
 \
  Profile *pb_smm;             /* population balance bc */ \
  int *pb_smm_bc_type; \
 \
  Profile pb_dqmom[1]; /* DQMOM */ \
  int pb_dqmom_bc_type[1]; \
 \
  Profile iac; /* interfacial area */ \
  int iac_bc_type; \
 \
  Profile lsf; /* level-set */ \
  int lsf_bc_type; \
 \
  int radiation_bc;   /* radiation bc type */\
  int Tbb_spec;     /* use local T or Tbb */ \
        /*  0 = face value */ \
        /*  1 = user specified value */ \
  real Tbb;     /* black body temperature */ \
  Profile in_emiss;   /* emissivity */ \
  Profile *q_irrad; /*direct irradiation*/\
  Profile *q_irrad_diffuse; /*diffuse irradiation*/\
  real coll_dtheta, coll_dphi;  /* collimated direction solid angle */\
  Profile qn[3];                   /* collimated radiation direction */\
  cxboolean parallel_collimated_beam; /*direction for irradiation w.r.t beam direction*/\
  cxboolean solar_direction;\
  Profile fmean;                /* mean mixture fraction */ \
  Profile fmean2;               /* Secondary mean mixture fraction */ \
  Profile fvar;                 /* mixture fraction variance */   \
  Profile fvar2;                /* Secondary mixture fraction variance */ \
 \
  Profile premix_c;             /* progress variable */ \
  Profile premix_cvar;          /* progress variable variance */ \
  Profile *tss_scalar;                  /* Scalar mass fractions*/ \
 \
  Profile ecfm_sigma;           /* flame area density */ \
 \
  Profile gvar;                 /* g equation variance */ \
 \
  Profile inert;                /* inert stream */ \
 \
  Profile yi_pollut[MAX_POLLUT_EQNS]; /* pollutant species mass fractions or soot nuclei number */ \
 \
  Profile tvar;                 /* temperature variance */ \
 \
  int dpm_bc;                   /* DPM bc type (types defined in dpm.h) */\
  int dpm_reinj_inj_id;  /* do not want to #include "dpm_types.h" here --> need to use Lookup_Injection_In_List() later on... */ \
  Objp *dpm_bc_collision_partner; /* DEM */\
  int dpm_bc_collision_partner_index; /* DEM */\
 \
  int ac_op;                    /* acoustic options */    \
 Impedance imp; \
 Profile ac_wave; \
 \
  Initialization_BC_Data initialization; /* storage for initialization */ \
 \
  UDF_Thread_Data dpm_udf;                 /* UDF fcn for DPM_BC_UDF */\
\
  Profile phi2;  \
  int phi2_type; \
  cxboolean relative       /* is velocity relative to rot. frame? */


#define  IS_STD_FLOW_BNDRY_TYPE_P(tt)  \
        ((THREAD_F_PFAR    == tt) ||   \
         (THREAD_F_VINLET  == tt) ||   \
         (THREAD_F_PINLET  == tt) ||   \
         (THREAD_F_POUTLET == tt) ||   \
         (THREAD_F_MFINLET == tt) ||   \
         (THREAD_F_OUTFLOW == tt))


#include "f_exterior.h"

#include "f_fluid.h"

#if RP_NETWORK  /* Compact heat conduction model for ICEPAK */
#include "sg_network.h"
#endif

/* jump (fan, radiator (heat exchanger), porous) */
#include "f_jump.h"

/* mass-flow inlet */
#include "f_mfi.h"

/* periodic */
#include "f_periodic.h"

/* pressure inlet */
#include "f_pi.h"

/* pressure outlet */
#include "f_po.h"

/* pressure far field */
#include "f_pfar.h"

/* sliding boundary */
#include "f_slide.h"

/* symmetry, axis */
#include "f_sym.h"

/* velocity inlet */
#include "f_vi.h"

/* wall */
#include "f_wall.h"

/* outflow */
#include "f_outflow.h"

/* fluid (fluid cells) */
#include "c_fluid.h"

struct thread_var_struct
{
  Thread_Type type;
  union
  {
    struct tv_pi_struct pi;
    struct tv_po_struct po;
    struct tv_outflow_struct outflow;
    struct tv_jump_struct jump;
    struct tv_vi_struct vi;
    struct tv_pfar_struct pfar;
    struct tv_mfi_struct mfi;
    struct tv_wall_struct wall;
    struct tv_sym_struct sym;
#if RP_NETWORK
    struct tv_network_end_struct network_end;
#endif
    struct tv_per_struct per;
    /* cell, fluid, and solid can be used interchangeably */
    struct tv_cell_struct cell;
    struct tv_cell_struct fluid;
    struct tv_cell_struct solid;
    struct tv_si_struct si;
    struct tv_interior_struct interior;
  } thread_var_struct_u;
};

/* #include "dpm_types.h"
 * This causes a  hen-and-egg problem in the
 * order in which things are declared in the
 * header files.
 */
typedef struct dpm_summary_struct
{
  int n_particles;
  double mass, mass_init;
  double liquid_mass, liquid_mass_init;
  double volatile_mass, volatile_mass_init;
  double char_mass, char_mass_init;
  double surface_species_mass[MAX_SPE_EQNS];  /* for multiple char combustion */
  double surface_species_init[MAX_SPE_EQNS];
  double time_min, time_max, time_avg, time_std;
  char injection_min[80], injection_max[80];
#if ! UDF_COMPILER
  int64_t id_min, id_max;
#endif
  double h, h_init;
  double h_sensible, h_sensible_init;
  double h_latent;
  double h_reaction;
  FILE *sort_file;
  char *sort_file_name;
  void *I;   /* Injection -- cannot include dpm_types.h -- see comment above */
  cxboolean reduced_to_node_zero_p;
} dpm_summary_t;

typedef struct pathline_summary_struct
{
  int n_particles;
  /* NOTE:
   * Please keep all reals in a contiguous block at the end of this struct,
   * and keep "time_min" the first variable within that contiguous block of reals.
   * These conventions are relied upon in print_pathline_summary().
   */
  real time_min, time_max, time_avg, time_std;
  real pos_min[3], pos_max[3];
} pathline_summary_t;

typedef struct ddpm_flux_struct
{
  real mass_flux;
  real heat_tot;
  real heat_sens;
} ddpm_flux_t;

typedef struct thread_head_struct
{
  int n_eqns;      /* # of eqns in the coupled system */
  int ns0_eqn;     /* # eqn number for first specie */
  int n_pvt_eqns;  /* # of p-v-T eqns in the coupled
        * - varies with dimension & inclusion/omission of energy
        *   eqn */
  int n_flow_eqns; /* # of eqns other than species in the coupled system
        * - varies with # of p-v-T eqns, inclusion/omission of
        *   k-e, swirl, etc. */
  /* This array contains the SV_* values for each equation. */
  Svar eqn_index[MAX_EQNS];

  cxboolean mv_p;   /* are there non-zero grid velocities */
  int n_profiles; /* the number of profile variables being used */
  Profile *profile_vars[MAX_PROFILE];/* the list of vars with profiles. Not
                                      all the vars with profiles are stored here.
                                      Only the vars that have a distinct profile
                                      are stored. So, valid data in this array
                                      is only upto length n_profiles. */

  struct
  {
#if SEEM
    void (*set_var)(Thread *, char *, Pointer);
#endif
    void (*update)(Domain *, Thread *);
    void (*update_profiles)(Thread *);
    void (*integrals)(Thread *, real *, int);
    void (*inviscid_flux)(Thread *, real *, cxboolean);
    void (*inviscid_flux_coarse)(Thread *, real *, cxboolean);
    void (*face_flux)(Thread *, real *, cxboolean);
    void (*viscous_derivative)(Thread *);
    void (*viscous_flux)(Thread *,  real *, cxboolean);
    void (*reconstruction_flux)(Thread *);
    void (*init_memory)(Thread *);
    void (*free_memory)(Thread *);
    void (*alloc_species_memory)(Thread *);
    void (*alloc_tss_scalar_memory)(Thread *);
    void (*alloc_uds_memory)(Thread *);
    void (*alloc_pb_memory)(Thread *);
    void (*reinitialize)(Thread *);   /* to update "private" data after e.g. the zone has been split */
    void (*copy_thread_head)(struct thread_head_struct *, struct thread_head_struct *, Thread *, Thread *);
  } method;
  struct thread_var_struct var;
  struct dpm_summary_struct dpm_summary;
  struct dpm_summary_struct  *dpm_per_inj_summaries;
  int                         dpm_per_inj_summaries_alloced;
  struct pathline_summary_struct pathline_summary;
  struct ddpm_flux_struct ddpm_flux;
  struct material_struct *material;
  struct material_struct *solid_material;
  struct material_struct *structure_material;
  int num_material;
  real q_rad; /* surface-to-surface net radiation heat flux for thread */
  real rad_sum; /* surface-to-surface radiosity sum for thread */
  cxboolean rad_flag; /* is thread included in radiation enclosure ? */
  int vapor_phase_realgas; /* thread phase for real-gas models: -1 global setting, 0 liquid, 1 vapor */
} Thread_Head;

#define THREAD_HEAD_VAR(_h)((_h)->var.thread_var_struct_u)
#define THREAD_VAR(t) THREAD_HEAD_VAR(THREAD_HEAD(t))
#define THREAD_TYPE(t)(THREAD_HEAD(t)->var.type)
#define THREAD_METHOD(t,f)(THREAD_HEAD(t)->method.f)
#define THREAD_PHASE_REALGAS(t) (THREAD_HEAD(t)->vapor_phase_realgas)

#if !UDF_COMPILER
# define THREAD_HEAD(t) ((struct thread_head_struct *)((t)->head))
# define THREAD_MATERIAL(t)(THREAD_HEAD(t)->material)
#endif
#define THREAD_SOLID_MATERIAL(t)(THREAD_HEAD(t)->solid_material)
#define THREAD_STRUCTURE_MATERIAL(t)(THREAD_HEAD(t)->structure_material)
#define THREAD_N_PROFILES(t) (THREAD_HEAD(t)->n_profiles)
#define THREAD_PROFILE_VAR(t,n) (THREAD_HEAD(t)->profile_vars[n])
/* SOLID_THREAD_P and FLUID_THREAD_P assume <t> is a cell thread.
 * A "fluid thread" contains either a fluid or mixture material. */
#define SOLID_THREAD_P(t)(MATERIAL_TYPE(THREAD_MATERIAL(t)) == MATERIAL_SOLID)
#define FLUID_THREAD_P(t)(!SOLID_THREAD_P(t))
#define FLUID_THREAD_WITH_NSPE(t)  (FLUID_THREAD_P(t) && THREAD_NSPE(t))
#define THREAD_NSPE(t)MIXTURE_NSPECIES(THREAD_MATERIAL(t))
#define THREAD_NSPE_SURF(t)((rp_spe_surf || rp_spe_part) ? \
                            MIXTURE_SURFACE_NSPECIES(THREAD_MATERIAL(t)) :\
                            0)
#define THREAD_NSPE_SITE(t)((rp_spe_surf) ? \
                            MIXTURE_SITE_NSPECIES(THREAD_MATERIAL(t)) :\
                            0)
#define THREAD_NSOOTSPE(t) ((sg_soot && sg_soot_mom && sg_soot_mech) ? \
                            MIXTURE_SITE_NSPECIES(THREAD_MATERIAL(t)) :\
                            0)
#define THREAD_NSOOT_SPE_AREA(t) ((sg_soot && sg_soot_mom && sg_soot_mech) ? \
                            MIXTURE_SITE_NSPECIES(THREAD_MATERIAL(t)) + 1 :\
                            0)
#define FLUID_THREAD_WITH_NSOOT(t) (FLUID_THREAD_P(t) && (THREAD_NSOOTSPE(t) > 0))

#define THREAD_MV_P(t)(THREAD_HEAD(t)->mv_p)

#define THREAD_RAD(t)(THREAD_HEAD(t))

#define THREAD_N_EQNS(t)(THREAD_HEAD(t)->n_eqns)
#define THREAD_NS0_EQN(t)(THREAD_HEAD(t)->ns0_eqn)
#define THREAD_N_PVT_EQNS(t)(THREAD_HEAD(t)->n_pvt_eqns)
#define THREAD_N_FLOW_EQNS(t)(THREAD_HEAD(t)->n_flow_eqns)
#define THREAD_EQN_INDEX(t,n)(THREAD_HEAD(t)->eqn_index[(n)])

FLUENT_EXPORT void flow_boundary_integrals(Thread *t, real integral[], int compute);
FLUENT_EXPORT real compute_torque(Thread *t);

FLUENT_EXPORT const char *Thread_Type_Name(int type);
FLUENT_EXPORT int Set_Thread_Type(Domain *, Thread *, Thread_Type, cxboolean);
FLUENT_EXPORT void MD_Set_Thread_Type(Domain *, int, Thread_Type, cxboolean);
FLUENT_EXPORT cxboolean Check_Thread_Type(Thread *);

FLUENT_EXPORT void MD_Set_Thread_Flags (Thread *, int);
FLUENT_EXPORT void MD_Clear_Thread_Flags (Thread *, int);

FLUENT_EXPORT void Set_Thread_Id(Domain *, Thread *, int id);
FLUENT_EXPORT void MD_Set_Thread_T1(Domain *, int, int);
#if SEEM
FLUENT_EXPORT void Set_Thread_Variables(Domain *, Thread *, Pointer);
FLUENT_EXPORT Pointer Get_Thread_Derived_Variables(Domain *, Thread *);
#endif
FLUENT_EXPORT Thread *Lookup_Thread(Domain *, int id);
FLUENT_EXPORT Thread *Lookup_Thread_All(Domain *, int id);
FLUENT_EXPORT int Get_Thread_List_from_String_of_IDs(Domain *, const char *, Objp **);
FLUENT_EXPORT void Initialize_Thread_All_Map(Domain *);
FLUENT_EXPORT void Finalize_Thread_All_Map(Domain *);
FLUENT_EXPORT void Create_Thread_Arrays(Domain *);
FLUENT_EXPORT void Free_Thread_Arrays(Domain *);

FLUENT_EXPORT void (*Thread_Default (int type))(Domain *, Thread *);
FLUENT_EXPORT void Thread_Null_Default(Domain *, Thread *);
FLUENT_EXPORT void thread_null_update(Domain *, Thread *);

FLUENT_EXPORT void thread_null_storage(Domain *domain, Thread *t);

FLUENT_EXPORT cxboolean Thread_Id_Used_P(Domain *, int);
FLUENT_EXPORT int Next_Thread_Id(Domain *);
FLUENT_EXPORT int Current_Thread_Id(Domain *);
FLUENT_EXPORT int Next_tmp_Thread_Id(Domain *);
FLUENT_EXPORT int Max_Thread_Id(Domain *);
FLUENT_EXPORT void Reset_Max_Thread_Id(Domain *);
FLUENT_EXPORT void Reset_Thread_Id(void);
FLUENT_EXPORT void Fill_Reserved_Thread_Id_List(int *, int);
FLUENT_EXPORT void Free_Reserved_Thread_Id_List(void);

FLUENT_EXPORT void Thread_Set_Profile_Var(void *, Profile *, Pointer, Thread *, int);
FLUENT_EXPORT void Thread_Set_Profile_Only_Var(void *, Profile *, Pointer, Thread *, int);
FLUENT_EXPORT void Thread_Set_Const_Profile_Var(Profile *, real);
FLUENT_EXPORT void Thread_Set_Non_Const_Profile_Var(void *, Profile *, Thread *, const char *, const char *);
FLUENT_EXPORT void Thread_Set_Profile_List_Var(void *, Profile *, int *, int, Pointer, Thread *, int);
FLUENT_EXPORT void Thread_Set_Profile_List_UDS_Var(void *, Profile *, int *, int, Pointer, Thread *, int);
FLUENT_EXPORT void Thread_Set_Real_Var(real *, Pointer);
FLUENT_EXPORT void Thread_Set_Real_List_Var(real *, int *, int, Pointer);
FLUENT_EXPORT void Thread_Set_Real_Matrix_Var(real *, int, Pointer, const char *);
FLUENT_EXPORT void Thread_Set_Int_Var(int *, Pointer);
FLUENT_EXPORT void Thread_Set_Int_Var_byString(int *, Pointer, char strlst[][OPT_STR_VAR_VAL_LEN]);
FLUENT_EXPORT void Thread_Set_Int_List_Var(int *, int *, int, Pointer);
FLUENT_EXPORT void Thread_Set_Int_List_UDS_Var(int *, int *, int, Pointer, Thread *);
FLUENT_EXPORT void Thread_Set_Boolean_Var(cxboolean *, Pointer);
FLUENT_EXPORT void Thread_Set_String_Var(const char *, int, Pointer);
FLUENT_EXPORT void Thread_Set_Polynomial_Var(Polynomial *p, Pointer value);

FLUENT_EXPORT cxboolean Flow_BC_Set_Var(Thread *t, const char *name, Pointer value);
FLUENT_EXPORT void Flow_BC_Update_Profiles(Thread *t);

FLUENT_EXPORT cxboolean Solve_Face_Thread_P(Thread *thread, Domain *d);

/* Note: wrap with braces when needed */
#if PARALLEL
# define PRIMITIVE_ERROR(arg_list) {Message arg_list; return;} /* don't use ; after this. It will trigger an warning!*/
#else
# define PRIMITIVE_ERROR(arg_list) {Error arg_list;}
#endif

#define EXPAND_INTEGRAL_helper(i,s,base)INTEGRAL_##base##_##i
#define EXPAND_FLUX_C_helper(i,s,base)FLUX_C_##base##_##i
#define EXPAND_NPHASE_INTEGRAL(base) EXPAND_0_TO_4(EXPAND_INTEGRAL_helper,base)
#define EXPAND_NPHASE_FLUX_C(base) EXPAND_0_TO_4(EXPAND_FLUX_C_helper,base)
#define EXPAND_NELEM_INTEGRAL(base) EXPAND_0_TO_9(EXPAND_INTEGRAL_helper,base)
#define EXPAND_NUDS_INTEGRAL(base) EXPAND_0_TO_49(EXPAND_INTEGRAL_helper,base)

/* integral types (indices into integral[] array) */
typedef enum
{
  INTEGRAL_FLUX_MASS = 0,
  EXPAND_NUDS_INTEGRAL(UDS_FLUX),
#define INTEGRAL_UDS_FLUX INTEGRAL_UDS_FLUX_0
  INTEGRAL_FLUX_HEAT,
  INTEGRAL_FLUX_HEAT_SENSIBLE,
  INTEGRAL_FORCE_PRESSURE_X,
  INTEGRAL_FORCE_PRESSURE_Y,
  INTEGRAL_FORCE_PRESSURE_Z,
  INTEGRAL_MOMENT_PRESSURE_X,
  INTEGRAL_MOMENT_PRESSURE_Y,
  INTEGRAL_MOMENT_PRESSURE_Z,
  INTEGRAL_FORCE_VISCOUS_X,
  INTEGRAL_FORCE_VISCOUS_Y,
  INTEGRAL_FORCE_VISCOUS_Z,
  INTEGRAL_MOMENT_VISCOUS_X,
  INTEGRAL_MOMENT_VISCOUS_Y,
  INTEGRAL_MOMENT_VISCOUS_Z,
  INTEGRAL_INPUT_VECTOR_X,
  INTEGRAL_INPUT_VECTOR_Y,
  INTEGRAL_INPUT_VECTOR_Z,
  INTEGRAL_FLUX_HEAT_RAD,
  INTEGRAL_FLUX_TORQUE,
  INTEGRAL_FLUX_T_ENTHALPY,
  INTEGRAL_FLUX_FILM_MASS,
  INTEGRAL_FLUX_FILM_HEAT,
  INTEGRAL_PRESSURE_WORK,
  INTEGRAL_VISCOUS_WORK,
  EXPAND_NELEM_INTEGRAL(ELEM_FLUX),
#define INTEGRAL_ELEM_FLUX INTEGRAL_ELEM_FLUX_0
  INTEGRAL_MASS_FLUX_Y, /* INTEGRAL_MASS_FLUX_Y must always be the last */
  INTEGRAL_TYPE_MAX
} Integral_Type;

/* flux function "compute" values */
enum
{
  FLUX_C_RESIDUALS,   /* residual contributions */
  FLUX_C_INTEGRALS,   /* integral contributions */
  FLUX_C_YPLUS,     /* y-plus contour values (fill C_TMP) */
  FLUX_C_WALL_SHEAR,    /* wall-shear contour values (fill C_TMP) */
  FLUX_C_WALL_SHEAR_MEAN, /* mean wall-shear contour values (fill C_TMP) */
  FLUX_C_WALL_HEAT_TRANSFER,    /* wall heat-transfer coeficient (fill C_TMP) */
  FLUX_C_WALL_HEAT_TRANSFER_WALL_ADJ, /*heat transfer coeff based on adjacent wall*/
  FLUX_C_WALL_HEAT_TRANSFER_WALL_YPLUS, /*heat transfer coeff based on wall y plus*/
  FLUX_C_WALL_HEAT_TRANSFER_MEAN,    /* mean wall heat-transfer coeficient (fill C_TMP) */
  FLUX_C_SC_WALL_HEAT_TRANSFER_MEAN, /*SC mean wall HTC*/
  FLUX_C_SC_REFERENCE_TEMP_MEAN, /*SC mean ref temp*/
  FLUX_C_WALL_FUNCT_BASED_HTC,  /* heat-trans. coef. based on turbulent wall funct(fill C_TMP) */
  FLUX_C_WALL_HEAT_FLUX,  /* wall heat-flux (fill C_TMP) */
  FLUX_C_WALL_HEAT_FLUX_MEAN, /* mean wall heat-flux (fill C_TMP) */
  FLUX_C_WALL_NUSSELT_NUMBER,   /* wall Nusselt number= h_eff*L_ref/k_eff (fill C_TMP) */
  FLUX_C_WALL_NUSSELT_NUMBER_MEAN,   /* mean wall Nusselt number= h_eff*L_ref/k_eff (fill C_TMP) */
  FLUX_C_WALL_STANTON_NUMBER,   /* wall Stanton number= h_eff/(rho*U*Cp) (fill C_TMP) */
  FLUX_C_WALL_STANTON_NUMBER_MEAN,   /* mean wall Stanton number= h_eff/(rho*U*Cp) (fill C_TMP) */
  FLUX_C_WALL_SHEAR_X,    /* x-wall-shear contour values */
  FLUX_C_WALL_SHEAR_Y,    /* x-wall-shear contour values */
  FLUX_C_WALL_SHEAR_Z,    /* x-wall-shear contour values */
  FLUX_C_WALL_SHEAR_X_MEAN, /* mean x-wall-shear contour values */
  FLUX_C_WALL_SHEAR_Y_MEAN, /* mean y-wall-shear contour values */
  FLUX_C_WALL_SHEAR_Z_MEAN, /* mean z-wall-shear contour values */

  FLUX_C_WALL_TEMP_OUTER_SURF,  /* wall-temperature on c0 */
  FLUX_C_WALL_TEMP_INNER_SURF,  /* wall-temperature on c1 */
  FLUX_C_WALL_EXT_TEMP_SHELL, /*temperature on external planar wall*/
  FLUX_C_WALL_ADJ_TEMP_SURF, /*wall adjacent temperature*/
  FLUX_C_WALL_YPLUS_TEMP_SURF, /*Y plus reference temperature*/
  FLUX_C_NODES,     /* forces accumulated at nodes */
  FLUX_JUMP_FACE_FORCE,               /* face forces at jump boundaries*/
  FLUX_WALL_FACE_FORCE,              /* force accumulation at face */
  FLUX_WALL_NODE_FORCE,              /* average force at node */
  FLUX_JUMP_NODE_FORCE,             /*average force at face node at jump boundary*/
  FLUX_C_WALL_RAD_HEAT_FLUX,  /* radiation heat flux */
  FLUX_C_YPLUS_UTAU,    /* y-plus contour values */
  FLUX_C_FACE_FLUX,             /* face-flux contributions */
  FLUX_C_FACE_FLUX_MASS_BAL,    /* face-flux contributions and mass balance */
  FLUX_C_WALL_INCIDENT_RADIATION,/* Q_minus in sg_disco */
  FLUX_C_BOUNDARY_VALUES,        /* update b.c. dependent values at boundary */
  FLUX_C_TORQUE,                 /* torque on boundary for swirl cons. in MP */
  FLUX_C_T_ENTHALPY,             /* total enthalpy integration for MP */

  SKIN_FRICTION_COEFF,           /* Skin Friction Coefficient */
  SKIN_FRICTION_MEAN_COEFF,      /* Skin Friction Mean Coefficient */
  FORCE_MOMENT_VECTOR,             /* For things related to force monitor only */

  FLUX_C_WALL_EVAP_FLUX,       /*  evaporation heat flux in boiling model */
  FLUX_C_WALL_THIN_FILM_FLUX,  /*  thin liquid film heat flux            */
  FLUX_C_WALL_QUENCH_FLUX,     /*  quench heat flux in boiling model     */
  FLUX_C_WALL_LIQUID_FLUX,     /*  liquid phase heat flux                */
  FLUX_C_WALL_VAPOR_FLUX,      /*  vapor  phase heat flux                */
  FLUX_C_WALL_NLBF_AVG_TEMP,  /* NLBF Averaged Line Temperature */

  FLUX_C_WALL_SBM_SP_FLUX,       /*  Semi-Mechanistic Boiling single phase flux */
  FLUX_C_WALL_SBM_NUC_FLUX,     /*   Semi-Mechanistic Boiling nucleate heat flux */

  FLUX_C_WALL_SURF_TENSION,
  FLUX_C_WALL_SURF_TENSION_X,
  FLUX_C_WALL_SURF_TENSION_Y,
  FLUX_C_WALL_SURF_TENSION_Z,
  FLUX_C_WALL_ABLATION_RATE
};

FLUENT_EXPORT void fluid_inviscid_flux_jacobians(cell_t c, const Thread *const t, real w[],
                                                 real r, real H, real flux_w, real flux_g,
                                                 const real *const A,
                                                 real a0[], real a1[]);

FLUENT_EXPORT void po_inviscid_flux_jacobian(cell_t c, Thread *t,
                                             real w[], real r, real H,
                                             real flux_w, real flux_g, real A[],
                                             int isupr);

FLUENT_EXPORT void pi_inviscid_flux_jacobian(cell_t c, Thread *t,
                                             real w[], real r, real H,
                                             real flux_w, real flux_g, real A[],
                                             real V, real R, real Cp, real ni[],
                                             const cxboolean ideal_gas,
                                             const cxboolean use_extrap_pressure);

FLUENT_EXPORT void fluid_dissipation_flux_jacobian(const Thread *const t, real w[], real H,
                                                   real alpha, real ur2, real V, real r,
                                                   real eig_V, real eig_p, real eig_m,
                                                   real At, const real *const A, real d[]);

#endif /* _FLUENT_THREADS_H */
