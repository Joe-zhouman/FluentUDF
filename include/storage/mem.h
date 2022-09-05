/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_MEM_H
#define _FLUENT_MEM_H

#if sys_lnia64
#include <ia64intrin.h>
#endif

#include "dll.h"
#include "materials.h"
#if !UDF_COMPILER
# include "prime/tgrid/hash2.h"
#endif

#include "entity.h"
#include "store.h"
#include "mesh_flags.h"
#include "refcountedmem.h"

#define DEBUG_OBJP 0

#define MAX_POST_VARS 127

/*
 * WARNING: MAX_PHASES is equal to MAX_SUB_DOMAINS but INTERACTION DOMAINS
 * are expanded from MAX_SUB_DOMAINs = 20.
 *
 */

/* residual constants */
#define MAX_UDS_EQNS 50
#define MAX_SOOTSPECIES_EQNS 50
#define MAX_ADS_EQNS 2
#define MAX_PB_DISC_EQNS 50
#define MAX_PB_QMOM_EQNS 10
#define MAX_PB_QMOM_L_EQNS 5
#define MAX_PB_QMOM_W_EQNS 5
#define MAX_PB_SMM_EQNS 10
#define MAX_TSS_SCALAR_EQNS 10

enum
{
  EQ_NULL = -1,
  EQ_CONTINUITY,
  EQ_CONT_GP,

  EQ_X_MOM,
  EQ_Y_MOM,
  EQ_Z_MOM,

  EQ_ENERGY,

  EQ_GRANULAR_TEMP,

  EQ_NUT,
  EQ_TKE,
  EQ_LKE,
  EQ_TTKE,
  EQ_TED,
  EQ_SDR,
  EQ_V2,
  EQ_FEL,
  EQ_INTERMIT,
  EQ_RETHETA,
  EQ_AC_WAVE,
  EQ_SPECIES,
  EQ_SPECIES_LAST = EQ_SPECIES - 1 + MAX_SPE_EQNS_PDF,
  EQ_SOOTSPECIES,
  EQ_SOOTSPECIES_LAST = EQ_SOOTSPECIES + MAX_SOOTSPECIES_EQNS,
  EQ_DW,
  EQ_EPDF,
  EQ_EPDF_LAST = EQ_EPDF - 1 +  MAX_SPE_EQNS,
  EQ_EPDF_H,
  EQ_UDS,
  EQ_UDS_LAST = EQ_UDS - 1 + MAX_UDS_EQNS,

  EQ_ADS,
  EQ_ADS_LAST = EQ_ADS - 1 + MAX_ADS_EQNS,

  EQ_PB_DISC,
  EQ_PB_DISC_LAST = EQ_PB_DISC - 1 + MAX_PB_DISC_EQNS,
  EQ_PB_QMOM,
  EQ_PB_QMOM_LAST = EQ_PB_QMOM - 1 + MAX_PB_QMOM_EQNS,
  EQ_PB_SMM,
  EQ_PB_SMM_LAST = EQ_PB_SMM - 1 + MAX_PB_SMM_EQNS,

  EQ_PB_DQMOM,

  EQ_IAC,
  EQ_LSF,

  EQ_P1,

  EQ_POLLUT0,
  EQ_POLLUT1,
  EQ_POLLUT2,
  EQ_POLLUT3,
  EQ_POLLUT4,
  EQ_POLLUT5,
  EQ_POLLUT6,
  EQ_POLLUT7,
  EQ_POLLUT8,
  EQ_POLLUT9,
  EQ_POLLUT10,
  EQ_POLLUT11,
  EQ_POLLUT12,
  EQ_POLLUT13,
  EQ_POLLUT14,
  EQ_POLLUT15,
  EQ_POLLUT16,
  EQ_POLLUT17,
  EQ_POLLUT18,
  EQ_POLLUT19,
  EQ_POLLUT20,
  EQ_POLLUT21,
  EQ_POLLUT22,
#define MAX_POLLUT_EQNS (EQ_POLLUT22-EQ_POLLUT0+1)
#define EQ_POLLUT EQ_POLLUT0
  EQ_SOOT_MOM,
  EQ_SOOT_MOM_LAST = EQ_SOOT_MOM - 1 + MAX_SOOT_MOM_EQNS,
  EQ_SOOT_MOM_AGG,
  EQ_SOOT_MOM_AGG_LAST = EQ_SOOT_MOM_AGG - 1 + MAX_SOOT_MOM_EQNS,
  EQ_SOOT_MOM_AREA,

  EQ_TVAR,

  EQ_TWOTE,

  EQ_IGNITE,

  EQ_FMEAN,
  EQ_FMEAN2,
  EQ_FVAR,
  EQ_FVAR2,

  EQ_MICRO_MIX_FVAR1,
  EQ_MICRO_MIX_FVAR2,
  EQ_MICRO_MIX_FVAR3,

  EQ_UFLA_Y,
  EQ_UFLA_YI,
  EQ_UFLA_YI_LAST = EQ_UFLA_YI - 1 + MAX_PROB_EQNS,

  EQ_PREMIXC,
  EQ_TSS_SCALAR,
  EQ_TSS_SCALAR_LAST = EQ_TSS_SCALAR - 1 + MAX_TSS_SCALAR_EQNS,

  EQ_DO,

  EQ_VOF,

  EQ_RUU,
  EQ_RVV,
  EQ_RWW,
  EQ_RUV,
  EQ_RVW,
  EQ_RUW,

  EQ_WSB,
  EQ_WSN,
  EQ_WSR,

#define MAX_RSM_EQNS 6

  EQ_PULL,

  EQ_ECFM,
  EQ_GEQN,
  EQ_GVAR,
  EQ_INERT,

  EQ_PHI1,
  EQ_PHI2,
  EQ_LITHIUM,

  EQ_CONTINUITY_ADJOINT,
  EQ_X_MOM_ADJOINT,
  EQ_Y_MOM_ADJOINT,
  EQ_Z_MOM_ADJOINT,
  EQ_AP_ADJOINT,
  EQ_Energy_ADJOINT,
  EQ_K_ADJOINT,
  EQ_O_ADJOINT,

  EQ_FLOW_COUPLED,

  EQ_X_DISP,
  EQ_Y_DISP,
  EQ_Z_DISP,
  EQ_STRUCTURE_COUPLED,

  EQ_CDS,

  MAX_EQNS
};

/* Used for full derivative information returned from udfs (adjoint) */

enum
{

  D_U = MAX_EQNS,
  D_V,
  D_W,
  D_P,
  D_X_CENTROID,
  D_Y_CENTROID,
  D_Z_CENTROID,

  MAX_EQNS_PLUS_DERIVATIVES

};

#define MAX_COUPLED_EQNS (5 + MAX_SPE_EQNS)

typedef enum
{
  EQ_X_MOM_GAP_SOURCE = 0,
  EQ_Y_MOM_GAP_SOURCE = 1,
  EQ_Z_MOM_GAP_SOURCE = 2,
  EQ_ENERGY_GAP_SOURCE = 3,
  MAX_GAP_SOURCE_TERMS = 4
} Gap_Model_Sources;

/* storage marker "which" constants */
enum
{
  SM_EQN_G,                     /* equation gradient */
  SM_VIS1,      /* Cell-based postprocessing temps */
  SM_VIS2,      /* Used to hold non-standard vector components */
  SM_VIS3,
  SM_TMP0,      /* Cell-based postprocessing temp */
#define SM_TMP SM_TMP0          /* Since C_TMP is same as C_TMP0 */
  SM_CS,                        /* cell status   */
  SM_EN1,                       /* edge e1 union */
  SM_EN2,                       /* edge e2 union */
  SM_EN4,                       /* edge e4 union */
  SM_FP,      /* face mark */
  SM_FTMP,      /* face temp */
  SM_GP_G,                      /* granular pressure gradient */
  SM_VEL_BCS,                   /* equation bcs, controls call for Update_Boundary_Velocity */
  SM_MAX
};


/* storage markers and function info */
#define SM_LABEL_MAX 20
typedef struct storage_marker_struct
{
  char label[SM_LABEL_MAX + 1]; /* unique marking tag */
  const char *name;   /* cell function name */
  const char *domain;           /* domain name */
  const char *units;          /* cell function units */
  real cell_min, cell_max;  /* range for cell values */
  real node_min, node_max;  /* range for node values */
} Storage_Marker;


typedef unsigned char uchar_fl;


typedef struct timer_struct
{
#define ITER_TIMER_WALL 0
#define ITER_TIMER_CPU_U 1
#define ITER_TIMER_CPU_S 2
#define ITER_TIMER_CYCLE 3
#define ITER_TIMER_SWEEP 4
#define ITER_TIMER_EXCHANGE 5
#define ITER_TIMER_DPM 6
#define ITER_TIMER_HOST_TO_NODE_VAR 7
#define ITER_TIMER_NODE_TO_HOST_VAR 8
#define ITER_TIMER_FILL_HOST_DOMAIN 9
#define ITER_TIMER_PHYS_TIME 10
#define ITER_TIMER_STAGE1 11
#define ITER_TIMER_STAGE2 12

#define IO_TIMER_READ_WALL 0
#define IO_TIMER_READ_SECTION 1
#define IO_TIMER_WRITE_WALL 2
#define IO_TIMER_WRITE_SECTION 3
#define IO_TIMER_UPDATE 4
#define IO_TIMER_AUTO_PART 5
#define IO_HDF_READ 6
#define IO_HDF_WRITE 7
#define POST_PROCESSING_TIMER 11
#define TIMER_MAXIMUM 13
  double time[TIMER_MAXIMUM];
  double count[TIMER_MAXIMUM];

  double gop_time;
  double recv_time;
  double send_time;
  double mesg_count;
  double mesg_size;
  double gop_count;
  double exchange_count;
  double overhead;
  /* used to maintain history of cpu time, no. of cells etc
   * vs iteration number */
  int iteration_count;
  double *comp_time;
  double *wall_time;
  double *wall_comp_time;
  int *num_cells;
  int next_balance_iter;
  int last_balance_iter;
  int history_size;
  double *accumulated_n_mesg;  /* accumulate statistics for every iteration */
  double *accumulated_send_wall_time;
  double *accumulated_send_mesg_size;
} Timer;

typedef struct domain_struct Domain;

typedef struct transient_struct TransientParameters;

#include "storage.h"

#include "memblock.h"

#include "tmp_manager.h"

#include "mem_grid.h"

#include "threads.h"

typedef int Face_Element_Type;
typedef int Cell_Element_Type;

typedef struct entity_struct
{
  union
  {
    unsigned int number;
    Node *v;
#if RP_EDGE
    struct edge_struct *e;
#endif
    face_t f;
    cell_t c;
    struct thread_struct *t;
  } as;
#if PARALLEL && RP_SHELL && RP_3D
  int part;
#endif
} Entity;

struct domain_global_flags
{
  int need_storage_update;
  int need_virtual_si_update;
  int properties_need_init;
  int properties_need_update;
  int need_dual_thread_update;
  int need_reorder;
  /*
    0:  pre-nci-creation
    1:      nci-creation
    2: post-nci-creation
  */
  int nci_creation_stage;
};

#define Set_Domain_Global_Flag(domain,flag,state)\
domain->globals.flag = state
#define Get_Domain_Global_Flag(domain,flag)\
domain->globals.flag

typedef enum
{
  M_unknown = -1,
  M_granular,
  M_aiad_prim_cont, /* GM */ /* US 95649 */ /* Defining the flag for AIAD primary continuous phase */
  M_aiad_sec_cont, /* GM */ /* US 95649 */ /* Defining the flag for AIAD secondary continuous phase */
  M_aiad_sec_entr, /* GM */ /* US 95649 */ /* Defining the flag for AIAD secondary entrained phase */
  M_gentop_sec_trm, /* GM */ /* US 154621 */ /* Defining the flag for GENTOP treatment secondary phase */
  M_packed_bed,
  M_virtual_mass,
  M_virtual_mass_implicit,
  M_virtual_mass_implicit_options,
  M_wall_adhesion,
  M_include_dpm_source,
  M_pde_granular,
  M_dpm_phase,
  M_local_solve_eulerian,
  M_ddpm_static_pileup,
  M_iac,
  M_jump_adhesion,
  M_interphase_discr,
  M_interphase_visc_disp,
  M_surftens_modeling,
  M_surftens_type,
  DOMAIN_MODEL_MAX
} Domain_Model_ID;

typedef enum
{
  COMPLEX_PROP_unknown = -1,
  COMPLEX_PROP_virtual_mass_coeff,
  COMPLEX_PROP_drag_func,
  COMPLEX_PROP_drag_fac, /*US 39205*/
  COMPLEX_PROP_lift_coeff,
  COMPLEX_PROP_turbulent_dispersion_force,
  COMPLEX_PROP_turbulence_interaction,
  COMPLEX_PROP_restitution_coeff,
  COMPLEX_PROP_sfc_tension_coeff,
  COMPLEX_PROP_slip_v,
  COMPLEX_PROP_heat_coeff,
  COMPLEX_PROP_slope_limiter,
  COMPLEX_PROP_visc_disp_factor,
  COMPLEX_PROP_interfacial_area,
  COMPLEX_PROP_wall_lubrication_coeff,
  COMPLEX_PROP_MAX
} Complex_Property_ID;


typedef struct species_model_struct
{
  int n_spe;
  int n_spe_surf;
  int n_spe_site;
  int n_spe_ave;
  int *y_ave_map;
  cxboolean rp_react;
  cxboolean multicomp_diff;
  cxboolean thermal_diff;
  int nreaction_echem;
} Species_Model;

typedef enum
{
  AC_OFF = 0,
  AC_FFOWCS,
  AC_CORREL,
  AC_ARPACK,
  AC_WAVEEQ,
  AC_MODEL_MAX
} Acoustics_Model;

typedef enum
{
  PRESSURE_NO_SRC = 0,
  PRESSURE_LIGHTHILL,
  PRESSURE_LPCE,
  POTENTIAL_NO_SRC,
  POTENTIAL_LPCE
} Sound_Wave_Eq_Model;

typedef enum
{
  AC_HEXAHEDRON = 0,
  AC_CYLINDER,
  AC_SPHERE,
  AC_FRUSTUM
} Acoustics_Shape_Type;

typedef struct acoustics_shape_struct
{
  Acoustics_Shape_Type type;
  real point1[ND_3];
  real point2[ND_3];
  real radius1;
  real radius2;
  real thickness;
} Acoustics_Shape;

typedef struct acoustics_receiver_struct
{
  char *name;
  real coord[ND_3];
  char *filename;
  int index_full_end; /** End of the full signal, contributed by all source facets */
  int index_tail_end; /** End of the signal tail, contributed by any source facets */
  int index_max;      /** End of the dynamically allocated signal array */
  real reception_time_ini;
  real min_propagation_time;
  real max_propagation_time;
  real *rec_time;
  real *rec_signal;
} Acoustics_Receiver;

#define RECEIVER_NAME_LENGTH 64
#define FILE_NAME_LENGTH 256

typedef struct
{
  char name[RECEIVER_NAME_LENGTH];
  real xobs[ND_3];              /* observer location (origin) */
  /*  real vobs[ND_3]; */       /* observer velocity */
  struct
  {
    int buffer;                 /* size of buffer */
    int n_record;               /* size of record (no. of time steps) */
    double(*pa)[2];             /* pointer to time and acoustic pressure array */
    real avg;                   /* time average */
    real var;                   /* variance */
    real spl;                   /* power in dB */
    /* Signal delays for given source threads. Start, stop - for moving receivers */
    double start_min_delay;     /* minimum signal delay at t=emission_time_origin */
    double start_max_delay;     /* maximum signal delay at t=emission_time_origin */
    double stop_min_delay;      /* minimum signal delay at the end of simulation */
    double stop_max_delay;      /* maximum signal delay at the end of simulation */
    double emission_time_origin;
    int source_thread;
    cxboolean accum_p;
  } sound;                      /* pointer to Sound */
  char filename[FILE_NAME_LENGTH]; /* file pointer to x-y file */
  cxboolean speed_limit_reached;/* true if source and receiver approach each other
                                   or move apart with sonic or supersonic speed */
  real speed_limit_maxmach;     /* highest Mach number of approaching or moving apart
                                   source and receiver */
} receiver;

typedef struct acoustics_model_data_struct
{
  Acoustics_Model acoustics_model;
  Sound_Wave_Eq_Model waveeq_model;
  real rho_far_field;
  int node_id_nearest;
  Thread *thread_nearest;
  cell_t cell_nearest;
  int n_source_mask_shapes;
  int n_sponge_layer_shapes;
  int n_receivers;
  int integration_surface_id;
  real emission_time_ini;
  Acoustics_Shape *source_mask_shapes;
  Acoustics_Shape *sponge_layer_shapes;
  Acoustics_Receiver *receivers;
  receiver *receivers_list;
} Acoustics_Model_Data;

typedef struct virtualboundary_region_data_struct
{
  int  n_virtualboundary_region;
  void *IR_List;
} VirtualBoundary_Region_Data;


#if sys_lnx86
/* switch bit field off to make the gcc compiler happy */
#define BIT_FIELD1
#else
#define BIT_FIELD1 :1
#endif

typedef struct residual_struct
{
  real *res, *res_scale;
  real *locrms, *locmax;
#if RP_NODE
  real *gres, *gres_scale;
  real *glocrms, *glocmax;
#endif
  int *Mapeqns;
  int noofeqns;

  struct residual_struct *next;
  struct residual_struct *prev;
} Residual;

/* bounded scheme or not is detail not relevant in determining transient stencil */
enum
{
  FIRST_ORDER_TIME = 0,
  SECOND_ORDER_TIME,
  SECOND_FIRST_TIME,
  FIRST_SECOND_TIME
};

#if 0
/* TO DO:
 * Add parameters for managing
 * 1. adaptive time stepping
 * 2. time extrapolation
 * 3. courant number
 * */
struct transient_controls
{
  /* time step ratio options */
  /* grid flux options */
  /* bounded scheme options */
  /* equation specific options */
  cxboolean predictor_p;
  cxboolean variable_time_step_p;
  cxboolean udf_based_time_step_p;
  cxboolean vof_using_cfl_based_p;
  real dt_min;
  real dt_max;
  real dt_factor_min;
  real dt_factor_max;
  real time_end;
  real time_error;
  real courant_number;
};
#endif
struct transient_struct
{
  int  time_index;     /* time step counter, time-step */
  real time;           /* current flow time, flow-time */
  real dt_current;     /* current time step size, physical-dt */
  real dt_previous;    /* previous time level time step size, physcial-dt-m1  */
  real dtr_current;    /* timestep size ratio current time level */
  real dtr_previous;   /* timestep size ratio previous time level */
  int  scheme_current; /* current transient scheme 1st order or 2nd order, time/scheme-current */
  int  scheme_previous;/* previous time level scheme, time/scheme-previous */
  int  hybrid_scheme;  /* 0-none, 1-second-to-first, 2-first-to-second */
  real hybrid_coeff;   /* 0.0 or 1.0 sets coefficient for phi_ph = phi_n + hybrid_coeff*beta_ph*(phi_n + phi_nm1) */
  /* by definition, beta_nh = (beta_ph)_nm1 \equiv hybrid_coeff*beta_ph                      */
  /*cxboolean need_m2;    need m2 level quantities (to replace hybrid_transient_need_m2,
   * but not all store functions have domain pointers) */
#if 0
  transient_controls tnt_ctrl;
#endif
};

#define TRANSIENT_INDEX(d)           ((d)->transient_parameters.time_index)
#define TRANSIENT_TIME(d)            ((d)->transient_parameters.time)
#define TRANSIENT_CURRENT_DT(d)      ((d)->transient_parameters.dt_current)
#define TRANSIENT_PREVIOUS_DT(d)     ((d)->transient_parameters.dt_previous)
#define TRANSIENT_CURRENT_RATIO(d)   ((d)->transient_parameters.dtr_current)
#define TRANSIENT_PREVIOUS_RATIO(d)  ((d)->transient_parameters.dtr_previous)
#define TRANSIENT_SCHEME_CURRENT(d)  ((d)->transient_parameters.scheme_current)
#define TRANSIENT_SCHEME_PREVIOUS(d) ((d)->transient_parameters.scheme_previous)
#define TRANSIENT_SCHEME_HYBRID(d)   ((d)->transient_parameters.hybrid_scheme)
#define TRANSIENT_HYBRID_COEFF(d)    ((d)->transient_parameters.hybrid_coeff)
#if 0
#define TRANSIENT_NEED_M2(d)         ((d)->transient_parameters.need_m2)
#endif

typedef enum                  /*corresponds to phase state */
{
  NO_STATE = -1,
  LIQ_STATE = 0,
  GAS_STATE = 1,
  GRANULAR_STATE = 2
} Phase_State;

typedef enum                  /*corresponds to phase type */
{
  CONT_PHASE = 0,
  DISP_PHASE = 1,
  HYB_PHASE = 2
} Phase_Type;

typedef struct nz_manager_struct
{
  int mode;                  /* created mode, all or solid only */
  int n_structures;          /* number of structures for NZ creation */
  int grid_id;               /* saved grid id */
  int case_id;               /* saved case id */
  struct thread_struct *cnz; /* cell nodal zone */
  struct thread_struct *fnz; /* face nodal zone */
} nz_manager_t;

typedef enum
{
  NULL_LIST  = -1,
  FLUID_LIST = 0,
  SOLID_LIST = 1,
  /**
   * Add more indices for the start and end of other types of thread lists
   */
  LIST_ARRAY_SIZE
} Thread_List_Id;

typedef enum
{
  INIT_LIST   = -1,
  REMOVE_LIST = 0,
  ADD_LIST
} Thread_List_Operation;

typedef struct thread_list_manager_t
{
  /* Note: considering now solid and fluid
   * but more thread types can be considered */

  /* number of already added sublists in the main list */
  int nlist;

  /* current order of sublist id's in each main thread list from start to end */
  Thread_List_Id id_hist[LIST_ARRAY_SIZE];

  /* array of start of thread lists */
  struct thread_struct **list_start[LIST_ARRAY_SIZE];

  /* array of end of thread lists */
  struct thread_struct **list_end[LIST_ARRAY_SIZE];

  /* info of sub-lists saved as objects */
  struct objp_struct *o_list[LIST_ARRAY_SIZE];

  /* temporary location when unthreading the sub-list */
  struct thread_struct *t_list[LIST_ARRAY_SIZE];

  /* determines if the tlm is created and can have zones in the thread list */
  cxboolean created[LIST_ARRAY_SIZE];
} thread_list_manager;

typedef struct thread_list_managers_t
{
  thread_list_manager tlm_c;          /* thread list manager of c*/
  thread_list_manager tlm_f;          /* thread list manager of f */
  thread_list_manager tlm_nosolve_c;  /* thread list manager of nosolve_c */
  thread_list_manager tlm_nosolve_f;  /* thread list manager of nosolve_f */
}
thread_list_managers;


#define TLM_NLIST(t)            ((t)->nlist)
#define TLM_ID_HIST(t,i)        ((t)->id_hist[i])
#define TLM_LIST_START(t,i)     ((t)->list_start[i])
#define TLM_LIST_END(t,i)       ((t)->list_end[i])
#define TLM_OLIST(t,i)          ((t)->o_list[i])
#define TLM_TLIST(t,i)          ((t)->t_list[i])
#define TLM_CREATED(t,i)        ((t)->created[i])
#define DOMAIN_TLM_C(d)         ((d)->tlms.tlm_c)
#define DOMAIN_TLM_F(d)         ((d)->tlms.tlm_f)
#define DOMAIN_TLM_NOSOLVE_C(d) ((d)->tlms.tlm_nosolve_c)
#define DOMAIN_TLM_NOSOLVE_F(d) ((d)->tlms.tlm_nosolve_f)

struct domain_struct
{
  /* Note: order of cell and face threads below must be
   * maintained for thread_loop macros; modify TL_* masks
   * when modifying.  (Should perhaps rewrite as array
   * of threads.)
   */
  struct thread_struct *c;          /* cell thread list */
  struct thread_struct *nosolve_c;  /* no solver cell thread list */
  struct thread_struct *nosolve_ext_c; /* no solver exterior cell thread */
  struct thread_struct *f;      /* face thread list */
  struct thread_struct *nosolve_f;  /* no solver face thread list */
  struct thread_struct *inactive_c_f; /* deactivated cell and face thread list */
  struct thread_struct *passive_c_f;  /* misc. cell and face thread list */
  struct thread_struct **c_n_a;
  struct thread_struct **f_n_a;
  int n_c_n_a;
  int n_f_n_a;
#if RP_NETWORK
  struct thread_struct *nwc;         /* network cell */
  struct thread_struct *nwf;         /* network face */
#endif

#if USE_DOMAIN_DATA_MANAGER
  struct thread_struct *node_thread;
  domain_data_manager_t data_manager;
#endif

  nz_manager_t nz;                  /* nodal zone manager */
#if USE_FEMCORE
  inz_manager_t inz[N_INTERP_TYPE]; /* interpolation nodal zone manager */
#endif

  thread_list_managers tlms;         /* thread list managers of different entities */

  void *Cell_Memory;
  void *Face_Memory;
#if RP_POLYHEDRA
  void *Face_Edge_Memory;
  void *Face_Face_Memory;            /* used for dual faces */
#endif

#if RP_HANG
  struct objp_struct *bridge_fl;    /* hanging node bridge faces */
#endif
#if RP_NODE
  struct objp_struct *ext_vl;
  struct objp_struct *ext_fl;
  struct objp_struct *corner_vl;
# if RP_HANG && RP_EDGE
  struct objp_struct *corner_el;
# endif
  struct dom_neighbor_struct *neighbors; /* phasing out */

  int *valid_neighbors;
  int n_valid_neighbors;
  int valid_neighbors_ready;

  /* neighbor send/recv buffer caching */
  int nb_msg_buf_case_id;
  int nb_msg_buf_grid_id;
  int nb_msg_buf_nbytes;

#if NEW_PARALLEL_NEIGHBOR
  struct domain_neighbor_struct *neighbor;
#endif /* NEW_PARALLEL_NEIGHBOR */
#endif

  struct domain_struct *_coarse;/* coarser domain (FAS MG) */
  struct domain_struct *_fine;  /* finer domain (FAS MG) */
  int mg_level;     /* grid level; 0 is finest level */

  real dtmin;     /* global minimum timestep */

  struct transient_struct  transient_parameters;

#if RP_HOST
  cxindex cell_count, face_count;
#endif
  cxindex node_count;
  cxindex nosolve_face_count, nosolve_cell_count;
#if RP_EDGE
  cxindex edge_count;
#endif
#if RP_HANG
  int bridge_face_count;
#endif
#if RP_NODE
  int neighbor_count;
  int corner_node_count;
# if RP_HANG && RP_EDGE
  int corner_edge_count;
# endif /* RP_HANG && RP_EDGE */
#endif /* RP_NODE */
  struct timer_struct flow_timer, case_timer, data_timer, post_timer;
#if !RP_HOST
  cxboolean active;
#else
  cxboolean *active;
#endif /* RP_HOST */
  struct storage_marker_struct sm[SM_MAX];
  struct sliding_interface *sliding_interfaces;
  struct sliding_interface *sis;
#if RP_OVERSET
  struct overset_interface *overset_interfaces;
#if 0 /* performance related, activate once evaluation is complete */
  struct objp_struct *receptor_list;          /* list of receptors in domain */
#endif
#endif
  struct dynamic_thread_struct *dynamic_threads;

  int id;  /* id number (unique id for each domain)                    */
  int index;     /* index with respect to place within list of sub-domains
      * of parent - i.e. phase index.
      * domains that are not sub-domain (e.g. top-level mixture
      * or single fluid) have index = NULL_INDEX                 */
  int level;   /* level (e.g. how far above root)                          */
  int n_domains; /* number of sub domains branching from this domain         */

  Phase_State phase_state;  /* phase state for sub domain */
  Phase_Type phase_type;  /* phase morphology for sub domain */

  /* pointers to sub-domains; max size +1 used to permit less
     complicated logic in the third expression of the for loops
     used in the sub domain loop macros */
  struct domain_struct *sub_domains[MAX_SUB_DOMAINS + 1];

  struct domain_struct *interaction;   /* phase interactions domain */

  struct domain_struct *superdomain;   /* pointer back to superdomain  */

  struct domain_struct *parent_domain;   /* pointer to the parent domain */

  struct domain_global_flags globals;  /* global flags */

  char name[MATERIAL_NAME_LENGTH];
  char material_name[MATERIAL_NAME_LENGTH];
  cxboolean model[DOMAIN_MODEL_MAX];

  Species_Model species_model;

  Acoustics_Model_Data *acoustics_model_data;

  void *optics_model_data;

  VirtualBoundary_Region_Data *virtualboundary_region_data;

  Property property[PROP_MAX];
  Property *complex_property[COMPLEX_PROP_MAX];

  Residual *residual_top, *residual_bot;

  /* residuals */
  real rtrms[MAX_EQNS];
  real rtrms_final[MAX_EQNS];
  real d_locrms[MAX_EQNS];
  real d_locmax[MAX_EQNS];
#if RP_NODE
  real grtrms[MAX_EQNS];
  real grtrms_final[MAX_EQNS];
  real d_glocrms[MAX_EQNS];
  real d_glocmax[MAX_EQNS];
#endif
  real rscale[MAX_EQNS];
#if RP_NODE
  real grscale[MAX_EQNS];
#endif
  char equation_labels[MAX_EQNS][32];

  void *CellFunc;     /* Pointer to CELL_FUNCTION array */
  int NCellFunc;      /* total number of cell function */

  void *ddpm_I;      /* Pointer to latest injection of DDPM phase */

  /* for the network cells, because it's not included in any thread */
  unsigned char amg_mapping_status[AMG_MAX_SYSTEMS];

#if !UDF_COMPILER
  Hash_Table *hash_thread_ids;       /* used for looking up thread ids */
  int hash_thread_count;
#endif

};

extern FLUENT_EXPORT Domain *root_domain;
extern FLUENT_EXPORT Domain *mesh_domain;

/* The udf interpreter can't handle structure references.
 * Turn them into macros */
#if !UDF_COMPILER
# define DOMAIN_C(d)((d)->c)
# define DOMAIN_NOSOLVE_C(d)((d)->nosolve_c)
# define DOMAIN_NOSOLVE_EXT_C(d)((d)->nosolve_ext_c)
# define DOMAIN_F(d)((d)->f)
# define DOMAIN_NOSOLVE_F(d)((d)->nosolve_f)
# define DOMAIN_INACTIVE_C_F(d)((d)->inactive_c_f)
# define DOMAIN_PASSIVE_C_F(d)((d)->passive_c_f)
# if RP_NETWORK
#  define DOMAIN_NWC(d)((d)->nwc)
#  define DOMAIN_NWF(d)((d)->nwf)
# endif
# define DOMAIN_CNZ(d)((d)->nz.cnz)
# define DOMAIN_FNZ(d)((d)->nz.fnz)
# define DOMAIN_NZ_GRID_ID(d)((d)->nz.grid_id)
# define DOMAIN_NZ_CASE_ID(d)((d)->nz.case_id)
# define DOMAIN_NZ_MODE(d)((d)->nz.mode)
# define DOMAIN_NZ_N_STRUCTURES(d)((d)->nz.n_structures)
#if USE_FEMCORE
# define DOMAIN_CINZ(d,i)((d)->inz[i].cinz)
# define DOMAIN_FINZ(d,i)((d)->inz[i].finz)
# define DOMAIN_INZ_GRID_ID(d,i)((d)->inz[i].grid_id)
# define DOMAIN_INZ_CASE_ID(d,i)((d)->inz[i].case_id)
# define DOMAIN_INZ_MODE(d,i)((d)->inz[i].mode)
#endif
# define DOMAIN_ID(d)((d)->id)
# define PHASE_DOMAIN_INDEX DOMAIN_INDEX   /* jzs Request for UDF */
# define DOMAIN_N_DOMAINS(d)    ((d)->n_domains)
# define DOMAIN_SUB_DOMAIN(d,i) ((d)->sub_domains[i])
# define DOMAIN_SUPER_DOMAIN(d) ((d)->superdomain)
# define DOMAIN_NSPE(d) ((d)->species_model.n_spe)
# define DOMAIN_NSPE_SURF(d) ((d)->species_model.n_spe_surf)
# define DOMAIN_NSPE_SITE(d) ((d)->species_model.n_spe_site)
# define DOMAIN_NSPE_AVE(d) ((d)->species_model.n_spe_ave)
# define DOMAIN_Y_AVE_MAP(d,i) ((d)->species_model.y_ave_map[i])
# define DOMAIN_REACT(d) ((d)->species_model.rp_react)
# define DOMAIN_MULTICOMP_DIFF(d) ((d)->species_model.multicomp_diff)
# define DOMAIN_THERMAL_DIFF(d) ((d)->species_model.thermal_diff)
# define DOMAIN_NREACTION_ECHEM(d) ((d)->species_model.nreaction_echem)
#endif

#define CELL_MEM(_d)             (_d->Cell_Memory)
#define FACE_MEM(_d)             (_d->Face_Memory)
#if RP_POLYHEDRA
# define FACE_EDGE_MEM(_d)        (_d->Face_Edge_Memory)
# define FACE_FACE_MEM(_d)        (_d->Face_Face_Memory)
#endif /* RP_POLYHEDRA */

#define ROOT_DOMAIN_ID      1
#define DOMAIN_CELLFUNC(d)     ((d)->CellFunc)
#define DOMAIN_NCELLFUNC(d)    ((d)->NCellFunc)
#define DOMAIN_INDEX(d)        ((d)->index)
#define DOMAIN_LEVEL(d)        ((d)->level)
#define ROOT_DOMAIN_P(d)       (NULL == DOMAIN_SUPER_DOMAIN(d))
#define PHASE_DOMAIN_P(d)      (DOMAIN_INDEX(d) >= 0)
#define PHASE_DOMAIN_STATE(d)  ((d)->phase_state)
#define PHASE_DOMAIN_TYPE(d)   ((d)->phase_type)
#define DOMAIN_INTERACTION(d)  ((d)->interaction)
#define DOMAIN_MG_LEVEL(d)     ((d)->mg_level)
#define DOMAIN_COARSE(d)       ((d)->_coarse)
#define DOMAIN_FINE(d)         ((d)->_fine)

#define DOMAIN_NAME(d)          ((d)->name)
#define DOMAIN_MATERIAL_NAME(d) ((d)->material_name)
#define DOMAIN_MODEL(d,id)      ((d)->model[id])

#define DOMAIN_PROPERTY(d)          ((d)->property)
#define DOMAIN_COMPLEX_PROPERTY(d,a)  ((d)->complex_property[a])

#define DOMAIN_RES(d,eqn)         ((d)->residual_top->res[eqn])
#define DOMAIN_RES_SCALE(d,eqn)   ((d)->residual_top->res_scale[eqn])
#define DOMAIN_NUMEQN(d)          ((d)->residual_top->noofeqns)
#define DOMAIN_EQNS(d,eqn)        ((d)->residual_top->Mapeqns[eqn])
#define DOMAIN_LOCRMS(d,eqn)      ((d)->residual_top->locrms[eqn])
#define DOMAIN_LOCMAX(d,eqn)      ((d)->residual_top->locmax[eqn])
#define RESIDUAL_LOCRMS(d,eqn)    ((d)->locrms[eqn])
#define RESIDUAL_LOCMAX(d,eqn)    ((d)->locmax[eqn])
#define RESIDUAL_EQNS(d,eqn)      ((d)->Mapeqns[eqn])
#define RESIDUAL_RES(d,eqn)       ((d)->res[eqn])
#define RESIDUAL_RES_SCALE(d,eqn) ((d)->res_scale[eqn])
#define RESIDUAL_NUMEQN(d)        ((d)->noofeqns)
#define RESIDUAL_CFXRMS(d,eqn)      ((d)->cfxrms[eqn])
#define RESIDUAL_CFXMAX(d,eqn)      ((d)->cfxmax[eqn])
#define DOMAIN_RSCALE(d,eqn)      ((d)->rscale[eqn])
#define DOMAIN_RTRMS(d,eqn)       ((d)->rtrms[eqn])
#define DOMAIN_RTRMS_FINAL(d,eqn)       ((d)->rtrms_final[eqn])
#define DOMAIN_D_LOCRMS(d,eqn)       ((d)->d_locrms[eqn])
#define DOMAIN_D_LOCMAX(d,eqn)       ((d)->d_locmax[eqn])
#if RP_NODE
#define DOMAIN_GRES(d,eqn)         ((d)->residual_top->gres[eqn])
#define DOMAIN_GRES_SCALE(d,eqn)   ((d)->residual_top->gres_scale[eqn])
#define DOMAIN_GLOCRMS(d,eqn)         ((d)->residual_top->glocrms[eqn])
#define DOMAIN_GLOCMAX(d,eqn)   ((d)->residual_top->glocmax[eqn])
#define RESIDUAL_GRES(d,eqn)       ((d)->gres[eqn])
#define RESIDUAL_GRES_SCALE(d,eqn) ((d)->gres_scale[eqn])
#define RESIDUAL_GLOCRMS(d,eqn)    ((d)->glocrms[eqn])
#define RESIDUAL_GLOCMAX(d,eqn)    ((d)->glocmax[eqn])
#define DOMAIN_GRSCALE(d,eqn)    ((d)->grscale[eqn])
#define DOMAIN_GRTRMS(d,eqn)      ((d)->grtrms[eqn])
#define DOMAIN_GRTRMS_FINAL(d,eqn)      ((d)->grtrms_final[eqn])
#define DOMAIN_D_GLOCRMS(d,eqn)       ((d)->d_glocrms[eqn])
#define DOMAIN_D_GLOCMAX(d,eqn)       ((d)->d_glocmax[eqn])
#endif
#define DOMAIN_EQN_LABEL(d,nw)     ((d)->equation_labels[nw])

#define FINE_DOMAIN_P(domain)(DOMAIN_MG_LEVEL(domain) == 0)
#define COARSE_DOMAIN_P(domain)(!FINE_DOMAIN_P(domain))

#define coarse_domain_loop(d,init)for((d)=(init);(d)!=NULL;(d)=DOMAIN_COARSE(d))

#define sub_domain_loop(sd,d,n)for(n=0, sd=DOMAIN_SUB_DOMAIN(d,n); n<DOMAIN_N_DOMAINS(d); ++n, sd=DOMAIN_SUB_DOMAIN(d,n))
#define sub_domain_loop_i(d,n)for(n=0; n<DOMAIN_N_DOMAINS(d); ++n)
#define reverse_sub_domain_loop(sd,d,n)for(n=DOMAIN_N_DOMAINS(d)-1, sd=DOMAIN_SUB_DOMAIN(d,n); n>=0; --n, sd=DOMAIN_SUB_DOMAIN(d,n))

/* single_or_sub_domain_loop macro
 *   single-phase: execute on single-domain
 *   multi-phase:  execute on each sub-domain, do not execute on mixture domain
 */
#define single_or_sub_domain_loop(sd,d,n)for(n=0, sd=(DOMAIN_N_DOMAINS(d)==0)?d:DOMAIN_SUB_DOMAIN(d,n); n<((DOMAIN_N_DOMAINS(d)==0)?1:DOMAIN_N_DOMAINS(d)); ++n, sd=DOMAIN_SUB_DOMAIN(d,n))

/* single_and_sub_domain_loop macro
 *   single-phase: execute on single-domain
 *   multi-phase:  execute on mixture-domain and each sub-domain
 */
#define single_and_sub_domain_loop(sd,d,n)for(n=0, sd=d; n<(1+DOMAIN_N_DOMAINS(d)); ++n, sd=DOMAIN_SUB_DOMAIN(d,n-1))

/* mixture_or_multfluid_loop macro
 * !mp_mfluid: execute on mixture-domain
 * mp_mfluid : execute only on sub-domains
 */

#define mixture_or_multifluid_loop(sd,d,n)\
for(n=0, sd=(!mp_mfluid)?d:DOMAIN_SUB_DOMAIN(d,n); n<((!mp_mfluid)?1:DOMAIN_N_DOMAINS(d)); ++n, sd=DOMAIN_SUB_DOMAIN(d,n))

#define sub_thread_loop(st,t,n) \
for(n=0,st=THREAD_SUB_THREAD(t,n); n<DOMAIN_N_DOMAINS(THREAD_DOMAIN(t)) && NNULLP(st); ++n,st=THREAD_SUB_THREAD(t,n))
#define reverse_sub_thread_loop(st,t,n) \
for(n=DOMAIN_N_DOMAINS(THREAD_DOMAIN(t))-1,st=THREAD_SUB_THREAD(t,n) && NNULLP(st); n>=0; --n,st=THREAD_SUB_THREAD(t,n))

#define single_or_sub_thread_loop(st,t,n)for(n=0, st=(DOMAIN_N_DOMAINS(THREAD_DOMAIN(t))==0)?t:THREAD_SUB_THREAD(t,n); n<((DOMAIN_N_DOMAINS(THREAD_DOMAIN(t))==0)?1:DOMAIN_N_DOMAINS(THREAD_DOMAIN(t))); ++n, st=THREAD_SUB_THREAD(t,n))

#define single_and_sub_thread_loop(st,t,n) \
        for(n=0, st=t; \
            n<(1+DOMAIN_N_DOMAINS(THREAD_DOMAIN(t))); \
            ++n, st=THREAD_SUB_THREAD(t,n-1))

/*N-phase compressible***********************************************/



#define single_or_sub_thread_loop_compr(st,t,n) \
         for(n=0, st=(DOMAIN_N_DOMAINS(THREAD_DOMAIN(t))==0)?t:THREAD_SUB_THREAD(t,iphase_compr_np[n]); \
             n<((DOMAIN_N_DOMAINS(THREAD_DOMAIN(t))==0)?1:num_compr_ph); \
       ++n, st=THREAD_SUB_THREAD(t,iphase_compr_np[n]))


#define sub_thread_loop_compr(st,t,n) \
  for(n=0, st=THREAD_SUB_THREAD(t,iphase_compr_np[n]); \
      n<num_compr_ph; \
      ++n, st=THREAD_SUB_THREAD(t,iphase_compr_np[n]))

/************************************************************/

#define STORAGE_MARKER(domain,which)((domain)->sm[which])
#define MAPEQN_INDEX(r,eqn,indx,i)  for(i=0;i<RESIDUAL_NUMEQN(r);i++)\
                                      if(RESIDUAL_EQNS(r,i)==eqn){indx=i;break;}


#define THREAD_COMM_HANDLE(t) ((t)->comm_handle)

#define SET_BITS(bits, mask) (bits |= mask)
#define CLEAR_BITS(bits, mask) (bits &= (~mask))
#define CHECK_BITS(bits, mask) (bits & mask)
#define SET_BITS_TO_VALUE(bits, mask, value) (bits = CLEAR_BITS(bits, mask) | CHECK_BITS(value, mask))

#define THREAD_ELEMENT_TYPE_MASK 0x3f /* bits 1-6 */
#define THREAD_ELEMENT_TYPE_LVALUE(t)((t)->element_type)

#define THREAD_ELEMENT_TYPE(t) (CHECK_BITS(THREAD_ELEMENT_TYPE_LVALUE(t), THREAD_ELEMENT_TYPE_MASK))
#define SET_THREAD_ELEMENT_TYPE(t, etype) (SET_BITS_TO_VALUE(THREAD_ELEMENT_TYPE_LVALUE(t), THREAD_ELEMENT_TYPE_MASK, etype))

#define CART_THREAD_BIT 0x80 /* (bit 8) */
#define SET_CART_THREAD_BIT(type) (SET_BITS(type, CART_THREAD_BIT))
#define SET_CART_THREAD(t) (SET_CART_THREAD_BIT(THREAD_ELEMENT_TYPE_LVALUE(t)))
#define CLEAR_CART_THREAD_BIT(type) (CLEAR_BITS(type, CART_THREAD_BIT))
#define CLEAR_CART_THREAD(t) (CLEAR_CART_THREAD_BIT(THREAD_ELEMENT_TYPE_LVALUE(t)))
#define CART_THREAD(t) (CHECK_BITS(THREAD_ELEMENT_TYPE_LVALUE(t), CART_THREAD_BIT))

#define ANY_CART_ENTITY_IN_THREAD_BIT 0x200 /* bit 10 */
#define SET_ANY_CART_ENTITY_IN_THREAD_BIT(type) (SET_BITS(type, ANY_CART_ENTITY_IN_THREAD_BIT))
#define SET_ANY_CART_ENTITY_IN_THREAD(t) (SET_ANY_CART_ENTITY_IN_THREAD_BIT(THREAD_ELEMENT_TYPE_LVALUE(t)))
#define CLEAR_ANY_CART_ENTITY_IN_THREAD_BIT(type) (CLEAR_BITS(type, ANY_CART_ENTITY_IN_THREAD_BIT))
#define CLEAR_ANY_CART_ENTITY_IN_THREAD(t) (CLEAR_ANY_CART_ENTITY_IN_THREAD_BIT(THREAD_ELEMENT_TYPE_LVALUE(t)))
#define ANY_CART_ENTITY_IN_THREAD(t) (CHECK_BITS(THREAD_ELEMENT_TYPE_LVALUE(t), ANY_CART_ENTITY_IN_THREAD_BIT))

extern FLUENT_EXPORT int svarIndexMap[SV_MAX];
extern FLUENT_EXPORT int numSvarsAllocated;

#if !UDF_COMPILER
#if COMPACT_STORAGE_ARRAY
# define THREAD_STORAGE(t,nv) ((t)->storage[svarIndexMap[nv]])
# define THREAD_STORE(t,nv) ((t)->store[svarIndexMap[nv]])
# define THREAD_STORAGE_NO_CHECK(t,nv) THREAD_STORAGE(t,nv)
# define THREAD_STORE_NO_CHECK(t,nv) THREAD_STORE(t,nv)
#else
#if ALLOCATE_STORAGE_ARRAY_ON_DEMAND
# define THREAD_STORAGE(t,nv)((t)->storage?(t)->storage[nv]:NULL)
# define THREAD_STORE(t,nv)((t)->store?(t)->store[nv]:NULL)
# define THREAD_STORAGE_NO_CHECK(t,nv) ((t)->storage[nv])
# define THREAD_STORE_NO_CHECK(t,nv) ((t)->store[nv])
#else /* ALLOCATE_STORAGE_ARRAY_ON_DEMAND */
# define THREAD_STORAGE(t,nv) ((t)->storage[nv])
# define THREAD_STORE(t,nv) ((t)->store[nv])
# define THREAD_STORAGE_NO_CHECK(t,nv) THREAD_STORAGE(t,nv)
# define THREAD_STORE_NO_CHECK(t,nv) THREAD_STORE(t,nv)
#endif /* ALLOCATE_STORAGE_ARRAY_ON_DEMAND */
#endif

# define THREAD_T0(t)((t)->t0)
# define THREAD_T1(t)((t)->t1)
# define THREAD_NAME(t) ((t)->name)

# define THREAD_CNZ(t)((t)->cnz)
# define THREAD_FNZ(t)((t)->fnz)
#if USE_FEMCORE
# define THREAD_CINZ(t,i)((t)->cinz[i])
# define THREAD_FINZ(t,i)((t)->finz[i])
# define THREAD_INZ_OBJECT_ACCESSES(t) ((t)->inz_obj_access)
# define THREAD_INZ_INTERPOLATION(t)(THREAD_INZ_OBJECT_ACCESSES(t)->interp)
# define THREAD_INZ_OBJECT_ACCESS(t,i) (THREAD_INZ_OBJECT_ACCESSES(t)->access[i])
# define THREAD_INZ_NVERTICES(t) (THREAD_INZ_OBJECT_ACCESS(t,INZACC_N_VERTICES))
#if RP_EDGE
# define THREAD_INZ_NEDGES(t) (THREAD_INZ_OBJECT_ACCESS(t,INZACC_N_EDGES))
#endif
# define THREAD_INZ_NFACES(t) (THREAD_INZ_OBJECT_ACCESS(t,INZACC_N_FACES))
# define THREAD_INZ_NCELLS(t) (THREAD_INZ_OBJECT_ACCESS(t,INZACC_N_CELLS))
# define THREAD_INZ_VERTEX0(t) (THREAD_INZ_OBJECT_ACCESS(t,INZACC_PO_VERTEX))
#if RP_EDGE
# define THREAD_INZ_EDGE0(t) (THREAD_INZ_OBJECT_ACCESS(t,INZACC_P0_EDGES))
#endif
# define THREAD_INZ_FACE0(t) (THREAD_INZ_OBJECT_ACCESS(t,INZACC_P0_FACES))
# define THREAD_INZ_CELL0(t) (THREAD_INZ_OBJECT_ACCESS(t,INZACC_P0_CELLS))
#if RP_NODE
# define THREAD_INZ_VERTEXEXT0(t) (THREAD_INZ_OBJECT_ACCESS(t,INZACC_PO_EXT_VERTEX))
#if RP_EDGE
# define THREAD_INZ_EDGEEXT0(t) (THREAD_INZ_OBJECT_ACCESS(t,INZACC_P0_EXT_EDGES))
#endif
# define THREAD_INZ_FACEEXT0(t) (THREAD_INZ_OBJECT_ACCESS(t,INZACC_P0_EXT_FACES))
# define THREAD_INZ_CELLEXT0(t) (THREAD_INZ_OBJECT_ACCESS(t,INZACC_P0_EXT_CELLS))
#endif
#endif
#define THREAD_ORIGINAL_STRETCHED(t) ((t)->tmp1)
#define GET_STRETCHED_THREAD(t) ((t)->tmp1)

#if DEBUG_MEMORY
# define SET_THREAD_T0(t,t0) Set_Thread_T0(t,t0,__FILE__,__LINE__)
# define SET_THREAD_T1(t,t1) Set_Thread_T1(t,t1,__FILE__,__LINE__)
#else /* DEBUG_MEMORY */
# define SET_THREAD_T0(t,t0) THREAD_T0(t) = (t0)
# define SET_THREAD_T1(t,t1) THREAD_T1(t) = (t1)
#endif /* DEBUG_MEMORY */
# define THREAD_NEXT(t)((t)->next)
# define THREAD_ID(t)((t)->id)
# define THREAD_N_ELEMENTS(t)((t)->nelements)
# define THREAD_FLAGS(t)((t)->flags)
# define THREAD_DOMAIN(t)((t)->domain)
# define THREAD_SUB_THREAD(t,i)((t)->sub_threads[i])
# define THREAD_SUB_THREADS(t)((t)->sub_threads)
# define THREAD_SUPER_THREAD(t)((t)->super_thread)
# define SET_PHASE_THREAD(_tfp,tf,_phase_id) (_tfp = (_phase_id < 0) ? tf: THREAD_SUB_THREAD(tf,_phase_id))

#define THREAD_SHADOW(t)((t)->shadow)
#define THREAD_RENDERP(t)(THREAD_SUPER_THREAD(t) ? THREAD_SUPER_THREAD(t)->renderp : (t)->renderp)
#define SET_THREAD_RENDERP(t, val) do {Thread *_t=t; if(THREAD_SUPER_THREAD(_t)) THREAD_SUPER_THREAD(_t)->renderp = val; else (_t)->renderp = val;}while(0)
/* Above is used in functions used for the 'double (*f)()' in CELL_FUNCTION;
 * therefore, GCC (needed for ARM porting!) requires the typed local variable '_t'.
 */
#endif /* !UDF_COMPILER */
#define THREAD_STREE(t)((t)->tp.astree)
#define THREAD_VIRTUAL(t) ((t)->virtual_thread)
#define THREAD_DUAL(t) ((t)->dual_thread)
#define THREAD_DT(t)   ((t)->dtptr)
#if RP_OVERSET
#define THREAD_OT(t)   ((t)->otptr)
#define THREAD_OTREE(t) ((t)->otree)
#endif
#define THREAD_TINT(t) ((t)->tint)
#define THREAD_TMP1(t) ((t)->tmp1)
#define THREAD_TMP2(t) ((t)->tmp2)
#define THREAD_COPY(t) ((t)->tmp1)
#define THREAD_TWIN(t) ((t)->tmp2)
#if RP_SHELL
#define THREAD_SHADOW_JUNCTION(t)((t)->shadow_junction)
#endif
#define THREAD_CHILD(t)((t)->child)
#define THREAD_PARENT(t)((t)->parent)
#define THREAD_COARSE(t)((t)->coarse)
#if RP_GEOM

#define GEOMFL_PROJECT_CLOSEST 0x1
#define GEOMFL_PROJECT_DIR     0x2
#define GEOMFL_HAS_BGMESH      0x4
#define GEOMFL_DISABLE         0x8

#define THREAD_BG(t) ((t)->geometry.bg.bgMesh)
#define THREAD_BGID(t) ((t)->geometry.bg.bgMeshId)
#define THREAD_PROJECTION_DIR(t) ((t)->geometry.dir)
#define THREAD_GEOM_THREAD(t) ((t)->geometry.geom_thread)
#define THREAD_PROPAGATION_LEVELS(t) ((t)->geometry.levels)
#define THREAD_GEOM_FLAGS(t) ((t)->geometry.geomflags)
#define SET_THREAD_GEOMFL(t, mask) (THREAD_GEOM_FLAGS(t) |= (mask))
#define CLEAR_THREAD_GEOMFL(t, mask)  (THREAD_GEOM_FLAGS(t) &= ~(mask))
#define SET_DISABLE_GEOMFL(t, mask) (THREAD_GEOM_FLAGS(tf) &= ~(GEOMFL_DISABLE)); \
                              (THREAD_GEOM_FLAGS(tf) |= (((mask)<<3) & GEOMFL_DISABLE))

#define THREAD_PROJECT_CLOSEST_POINT_P(t) (THREAD_GEOM_FLAGS(t) & GEOMFL_PROJECT_CLOSEST)
#define THREAD_PROJECT_DIR_P(t) (THREAD_GEOM_FLAGS(t) & GEOMFL_PROJECT_DIR)
#define THREAD_HAS_BGMESH_P(t) (THREAD_GEOM_FLAGS(t) & GEOMFL_HAS_BGMESH)
#define THREAD_GEOM_DISABLE_P(t) (THREAD_GEOM_FLAGS(t) & GEOMFL_DISABLE)
#endif
# define PF0_THREAD(t)((t)->sm.tpf0)
# define PF1_THREAD(t)((t)->sm.tpf1)
# define THREAD_SI_PARENT(t)((t)->sm.siparent)  /* obsolete, for perpendicular
                                                   face thread of old non-
                                                   conformal interface */
# define THREAD_SI_CHILD(t)((t)->sm.sichild)
# define THREAD_SI_CHILDS(t)(*((face_t **)&((t)->sm.childs)))
# define THREAD_SI_CHILD_THREADS(t)(*((Thread ***)&(t)->sm.child_threads))
# define THREAD_SI_CHILD_P(t,i)(&(THREAD_SI_CHILDS(t)[i]))
# define THREAD_SI_CHILD_THREAD_P(t,i)(&(THREAD_SI_CHILD_THREADS(t)[i]))
# define THREAD_SI_NCHILDS(t)((t)->sm.nchilds)
# define EXTENDED_THREAD(t) ((t)->extended_thread)
# define HELPER_THREAD(t) ((t)->sm.thelper)
# define MAPPED_THREAD(t) ((t)->sm.tmapped)
# define NON_OVERLAP_THREAD(t) ((t)->sm.tnoverlap)
# define NON_OVERLAP_GTI_THREAD(t) ((t)->sm.tnoverlap_gti)
# define SIDED_AREA_P(t) ((t)->sm.sided_area_p)

#if RP_PLBC
# define THREAD_SI(t) ((t)->si)
#endif

#define T_STORAGE_ALLOCATED_P(t) (NULL != (t)->storage)
#define SV_ALLOCATED_P(t,nv)(T_STORAGE_ALLOCATED_P(t) &&        \
                             NULL != THREAD_STORAGE((t),(nv)))

#define SV_ALLOCATED_AND_INITIALIZED_P(t,nv)( SV_ALLOCATED_P(t,nv) && SV_INITIALIZED_P(t,nv) )

#define NULL_INDEX_P(index)((index) == -1)
#define SV_LENGTH(t)((t)->sv_length)

#if PARALLEL
# if ALLOCATE_STORAGE_ARRAY_ON_DEMAND

#define STORAGE_ALLOCATED_MASK   (1)     /* data allocated on any process */
#define STORE_ALLOCATED_MASK     (1<<4)  /* data allocated on any process */
#define STORAGE_INITIALIZED_MASK (1<<5)  /* remember the intialized */

# define SV_ANY_ALLOCATED_P_BIT_GET(t,nv, m)      \
  ((t)->any_storage_allocated[(nv)]&(m))
# define SV_ANY_ALLOCATED_P_BIT_SET(t,nv, m)      \
  (t)->any_storage_allocated[nv] |= (m)
# define SV_ANY_ALLOCATED_P_BIT_CLEAR(t,nv, m)    \
  (t)->any_storage_allocated[nv] &= ~(m)

# define SV_ANY_ALLOCATED_P_SET(t,nv,s) {                               \
    if(s)SV_ANY_ALLOCATED_P_BIT_SET(t,nv, STORAGE_ALLOCATED_MASK);      \
    else SV_ANY_ALLOCATED_P_BIT_CLEAR(t,nv, STORAGE_ALLOCATED_MASK);}
# define SV_ANY_ALLOCATED_P(t,nv)                               \
  SV_ANY_ALLOCATED_P_BIT_GET(t,nv, STORAGE_ALLOCATED_MASK)

# define SV_STORE_ANY_ALLOCATED_P_SET(t,nv,s) {                         \
    if(s)SV_ANY_ALLOCATED_P_BIT_SET(t,nv, STORE_ALLOCATED_MASK);        \
    else SV_ANY_ALLOCATED_P_BIT_CLEAR(t,nv, STORE_ALLOCATED_MASK);}
# define SV_STORE_ANY_ALLOCATED_P(t,nv)                         \
  SV_ANY_ALLOCATED_P_BIT_GET(t,nv, STORE_ALLOCATED_MASK)

# define SV_ANY_INITIALIZED_P_SET(t,nv,s) {                             \
    if(s)SV_ANY_ALLOCATED_P_BIT_SET(t,nv, STORAGE_INITIALIZED_MASK);    \
    else SV_ANY_ALLOCATED_P_BIT_CLEAR(t,nv, STORAGE_INITIALIZED_MASK);}
# define SV_ANY_INITIALIZED_P(t,nv)                             \
  SV_ANY_ALLOCATED_P_BIT_GET(t,nv, STORAGE_INITIALIZED_MASK)
#if 1
#define SV_ALLOCATED_P_NEW(t,nv) (T_STORAGE_ALLOCATED_P(t) &&   \
                                  NULL != THREAD_STORE((t),(nv)))
#else
#define SV_ALLOCATED_P_NEW(t,nv) SV_ALLOCATED_P(t,nv)
#endif
#define SV_ALLOCATED_P_OD(t,nv) SV_STORE_ANY_ALLOCATED_P(t,nv)
# else /* ALLOCATE_STORAGE_ARRAY_ON_DEMAND */
# define SV_ANY_ALLOCATED_P(t,nv)   ((t)->any_storage_allocated[nv])
# define SV_ANY_ALLOCATED_P_SET(t,nv,s) SV_ANY_ALLOCATED_P(t,nv)=(s);
# define SV_STORE_ANY_ALLOCATED_P SV_ANY_ALLOCATED_P
# define SV_STORE_ANY_ALLOCATED_P_SET SV_ANY_ALLOCATED_P_SET
# define SV_ANY_INITIALIZED_P_SET(t,nv,s)
# define SV_ANY_INITIALIZED_P(t,nv)
#define SV_ALLOCATED_P_NEW(t,nv) (T_STORAGE_ALLOCATED_P(t) &&   \
                                  NULL != THREAD_STORE((t),(nv)))
# define SV_ALLOCATED_P_OD(t,nv) SV_ALLOCATED_P_NEW(t,nv)
# endif /* ALLOCATE_STORAGE_ARRAY_ON_DEMAND */
#else /* PARALLEL */
# define SV_ANY_ALLOCATED_P SV_ALLOCATED_P
# define SV_ANY_ALLOCATED_P_SET(t,nv,s)
# define SV_STORE_ANY_ALLOCATED_P SV_ANY_ALLOCATED_P
# define SV_STORE_ANY_ALLOCATED_P_SET SV_ANY_ALLOCATED_P_SET
# define SV_ANY_INITIALIZED_P_SET(t,nv,s)
# define SV_ANY_INITIALIZED_P(t,nv)
#define SV_ALLOCATED_P_NEW(t,nv) (T_STORAGE_ALLOCATED_P(t) &&   \
                                  NULL != THREAD_STORE((t),(nv)))
# define SV_ALLOCATED_P_OD(t,nv) SV_ALLOCATED_P_NEW(t,nv)
#endif /* PARALLEL */

#if FIXED_PROFILE_NAME_LENGTH
#define FREE_TEMP(p) if (NNULLP (p)) {CX_Free ((char *)p); p = NULL;}
#else
#define FREE_TEMP(p) if (NNULLP (p)) {Free_Ref_Counted_Memory(p, NULL); CX_Free ((char *)p); p = NULL;}
#endif

#define FREEIF(x) if (NNULLP(x)) CX_Free(x)
#ifndef  __GNUC__
#define  __typeof__  typeof
#endif
/* Try to detect when CX_Free'd elements of a linked list are still used:
 * Set the next pointer to 1, not NULL, which usually means the end of the list: */
#define FREEWIPENEXT(x) if ( ! NULLP(x))         (x)->next = (__typeof__(x)) 1, CX_Free(x)
#define FREEWIPEFULL(x) if ( ! NULLP(x)) memset(x, -1, sizeof(__typeof__(*x))), CX_Free(x)

#if RP_NODE
/*
 * Note 1: On a compute-node, THREAD_N_ELEMENTS(t) contains the combined
 * number of elements in the compute-node's interior region and
 * all exterior layers of the compute-node
 */

/*
 * Note 2: faces with correct cell neighbors exist only to depth "nlayer-1".
 * Faces in depth "nlayer" will in general only have one valid
 * cell neighbor; the other will be NULL.
 */

# if !UDF_COMPILER
#  define THREAD_N_ELEMENTS_LAYER(t,l)((t)->nelements_in_layer[l])
# endif
# define THREAD_N_ELEMENTS_INT(t) THREAD_N_ELEMENTS_LAYER(t,LAYER_INTERIOR)
# if RP_HANG
#  define THREAD_N_ELEMENTS_LAYER_NEW(t,nl) THREAD_N_ELEMENTS_LAYER(t,(N_LAYER/2)+(nl))
#  define THREAD_N_ELEMENTS_INT_NEW(t) THREAD_N_ELEMENTS_LAYER_NEW(t,LAYER_INTERIOR)
# endif /* RP_HANG */

# define F_THREAD_N_ELEMENTS_ALL(t) THREAD_N_ELEMENTS(t)
# define C_THREAD_N_ELEMENTS_ALL(t) THREAD_N_ELEMENTS(t)

# define THREAD_N_ELEMENTS_EXT(t) (THREAD_N_ELEMENTS_LAYER(t, LAYER_PRIMARY) + THREAD_N_ELEMENTS_LAYER(t, LAYER_SECONDARY))
# define THREAD_N_ELEMENTS_REXT(t) (THREAD_N_ELEMENTS_LAYER(t, LAYER_PRIMARY))
# define THREAD_N_ELEMENTS_EEXT(t) (THREAD_N_ELEMENTS_LAYER(t, LAYER_SECONDARY))

#else
# define THREAD_N_ELEMENTS_INT(t) THREAD_N_ELEMENTS(t)
# define THREAD_N_ELEMENTS_EXT(t) 0
# define THREAD_N_ELEMENTS_REXT(t) 0
# define THREAD_N_ELEMENTS_EEXT(t) 0
#endif /* RP_NODE */

#define T_STORAGE(t,n,type)((type)THREAD_STORAGE(t,n))

#define T_STORAGE_CHECK(t,n,type)((type)THREAD_STORAGE(t,n))
#define C_STORAGE(c,t,sv,type)(T_STORAGE(t,sv,type)[c])
#define F_STORAGE(f,t,sv,type)(T_STORAGE(t,sv,type)[f])
#define N_STORAGE(V,t,sv,type)(T_STORAGE(t,sv,type)[V])

#define T_STORAGE_I(t,sv)T_STORAGE_CHECK(t,sv,int *)
#define T_STORAGE_INDEX(t,sv)T_STORAGE_CHECK(t,sv,cxindex *)
#define T_STORAGE_UI(t,sv)T_STORAGE_CHECK(t,sv,unsigned int *)
#define T_STORAGE_R(t,sv)T_STORAGE_CHECK(t,sv,real *)
#define T_STORAGE_R_NV(t,sv)T_STORAGE_CHECK(t,sv,real (*)[ND_ND])
#define T_STORAGE_R_RST(t,sv)T_STORAGE_CHECK(t,sv,real (*)[MAX_RSM_EQNS])
#define T_STORAGE_R_N3V(t,sv)T_STORAGE_CHECK(t,sv,real (*)[ND_3])
#define T_STORAGE_R_N3V_BY_N3V(t,sv)T_STORAGE_CHECK(t,sv,real (*)[ND_3*ND_3])
#define T_STORAGE_DP_NV(t,sv)T_STORAGE_CHECK(t,sv,double (*)[ND_ND])
#define T_STORAGE_I_XV(t,sv,i)(T_STORAGE_CHECK(t,sv,int **)[i])
#define T_STORAGE_R_XV(t,sv,i)(T_STORAGE_CHECK(t,sv,real **)[i])
#define T_STORAGE_R_NV_XV(t,sv,i)(T_STORAGE(t,sv,real (**)[ND_ND])[i])
#define T_STORAGE_R_XV_LEN(t,sv) ST_STORE_DIMENSION(THREAD_STORE(t,sv))
#define T_STORAGE_PNTR(t, sv)T_STORAGE_CHECK(t,sv,void **)
#if COMPACT_STORAGE_ARRAY
#define SET_SV_FROM_XV(t,sv0,sv1,n) { if(THREAD_N_ELEMENTS(t) > 0) {\
                                        if(svarIndexMap[sv0]==0) svarIndexMap[sv0] = numSvarsAllocated++; \
                                        THREAD_STORAGE(t,sv0) = T_STORAGE_R_XV(t,sv1,n);}}
#define SET_SV_FROM_NV_XV(t,sv0,sv1,n) { if(svarIndexMap[sv0]==0) svarIndexMap[sv0] = numSvarsAllocated++; \
                                         THREAD_STORAGE(t, sv0) = T_STORAGE_R_NV_XV(t,sv1,n);}
#else
#define SET_SV_FROM_XV(t,sv0,sv1,n) { if(THREAD_N_ELEMENTS(t) > 0) THREAD_STORAGE(t,sv0) = T_STORAGE_R_XV(t,sv1,n);}
#define SET_SV_FROM_NV_XV(t,sv0,sv1,n) {THREAD_STORAGE(t, sv0) = T_STORAGE_R_NV_XV(t,sv1,n);}

#endif

#define NNULLP_SET_SV_FROM_XV(t,sv0,sv1,n) \
          if ( NNULLP(THREAD_STORAGE(t,sv1)) ) \
            SET_SV_FROM_XV(t,sv0,sv1,n)
#define NNULLP_SET_SV_FROM_NV_XV(t,sv0,sv1,n) \
          if ( NNULLP(THREAD_STORAGE(t,sv1)) ) \
            SET_SV_FROM_NV_XV(t,sv0,sv1,n)

#define IF_SPE_EQN_SET(t,n) \
          if ( n>=THREAD_NS0_EQN(t) && n<THREAD_NS0_EQN(t)+THREAD_NSPE(t) )
#define IF_SOOTSPE_EQN_SET(t,n) \
          if ( n>=THREAD_NS0_EQN(t) && n<THREAD_NS0_EQN(t)+THREAD_NSOOTSPE(t) )
#define IF_SOOTSPE_AREA_EQN_SET(t,n) \
          if ( n>=THREAD_NS0_EQN(t) && n<THREAD_NS0_EQN(t)+THREAD_NSOOT_SPE_AREA(t) )
#define SET_SV_FROM_XV_AND_EQN(t,sv0,sv1,n) \
          SET_SV_FROM_XV(t,sv0,sv1,n-THREAD_NS0_EQN(t))
#define SET_SV_FROM_NV_XV_AND_EQN(t,sv0,sv1,n) \
          SET_SV_FROM_NV_XV(t,sv0,sv1,n-THREAD_NS0_EQN(t))
#define NNULLP_SET_SV_FROM_XV_AND_EQN(t,sv0,sv1,n) \
          NNULLP_SET_SV_FROM_XV(t,sv0,sv1,n-THREAD_NS0_EQN(t))
#define NNULLP_SET_SV_FROM_NV_XV_AND_EQN(t,sv0,sv1,n) \
          NNULLP_SET_SV_FROM_NV_XV(t,sv0,sv1,n-THREAD_NS0_EQN(t))

#define T_STORAGE_I_NO_CHECK(t,sv)T_STORAGE(t,sv,int *)
#define T_STORAGE_INDEX_NO_CHECK(t,sv)T_STORAGE(t,sv,cxindex *)
#define T_STORAGE_UI_NO_CHECK(t,sv)T_STORAGE(t,sv,unsigned int *)
#define T_STORAGE_R_NO_CHECK(t,sv)T_STORAGE(t,sv,real *)
#define T_STORAGE_DB_NO_CHECK(t,sv)T_STORAGE(t,sv,double *)
#define T_STORAGE_R_NV_NO_CHECK(t,sv)T_STORAGE(t,sv,real (*)[ND_ND])
#define T_STORAGE_DP_NV_NO_CHECK(t,sv)T_STORAGE(t,sv,double (*)[ND_ND])
#define T_STORAGE_R_RST_NO_CHECK(t,sv)T_STORAGE(t,sv,real (*)[MAX_RSM_EQNS])
#define T_STORAGE_R_N3V_NO_CHECK(t,sv)T_STORAGE(t,sv,real (*)[ND_3])
#define T_STORAGE_R_N3V_BY_N3V_NO_CHECK(t,sv)T_STORAGE(t,sv,real (*)[ND_3*ND_3])
#define T_STORAGE_I_XV_NO_CHECK(t,sv,i)(T_STORAGE(t,sv,int **)[i])
#define T_STORAGE_R_XV_NO_CHECK(t,sv,i)(T_STORAGE(t,sv,real **)[i])
#define T_STORAGE_R_XV_LEN_NO_CHECK(t,sv) ST_STORE_DIMENSION(THREAD_STORE(t,sv))

#define CACHE_T_SV(type,x,t,sv) \
  type (* const x) = T_STORAGE(t,sv,type *)
#define CACHE_T_SV_I(x,t,sv)\
  int   * const x = T_STORAGE_I(t,sv)
#define CACHE_T_SV_INDEX(x,t,sv)\
  cxindex * const x = T_STORAGE_INDEX(t,sv)
#define CACHE_T_SV_UINDEX(x,t,sv)\
  cxindexU * const x = (cxindexU *)T_STORAGE_INDEX(t,sv)
#define CACHE_T_SV_R(x,t,sv)\
  real  * const x = T_STORAGE_R(t,sv)
#define CACHE_T_SV_R_NV(x,t,sv)\
  real (* const x)[ND_ND] = T_STORAGE_R_NV(t,sv)
#define CACHE_T_SV_R_N3V(x,t,sv)\
  real (* const x)[ND_3 ] = T_STORAGE_R_N3V(t,sv)
#define CACHE_T_SV_R_N3V_BY_N3V(x,t,sv)\
  real (* const x)[ND_3*ND_3] = T_STORAGE_R_N3V_BY_N3V(t,sv)
#define CACHE_T_SV_R_RST(x,t,sv)\
  real (* const x)[MAX_RSM_EQNS] = T_STORAGE_R_RST(t,sv)

#define CACHE_T_SV_R_XV(x,t,sv,ns)\
  real * const x = NNULLP(THREAD_STORAGE(t,sv)) ? T_STORAGE_R_XV(t,sv,ns) : NULL
#define CACHE_T_SV_R_NV_XV(x,t,sv,ns)\
  real (* const x)[ND_ND] = NNULLP(THREAD_STORAGE(t, sv)) ? T_STORAGE_R_NV_XV(t,sv,ns) : NULL
#define CACHE_T_SV_PNTR(x,t,sv)\
  void ** const x = NNULLP(THREAD_STORAGE(t,sv)) ? T_STORAGE_PNTR(t,sv) : NULL

#define CACHE_T_SV_R_COUPLED_MP(x,t,sv)\
  real (* const x)[MAX_PHASES] = T_STORAGE_R_RST(t,sv)

#if RP_3D
#define ND_CACHE_T_SV_R(x,y,z,t,sv_x,sv_y,sv_z)\
  real  * const x = T_STORAGE_R(t,sv_x),\
        * const y = T_STORAGE_R(t,sv_y),\
        * const z = T_STORAGE_R(t,sv_z)
#define ND_CACHE_T_SV_R_NV(x,y,z,t,sv_x,sv_y,sv_z)\
  real  (* const x)[ND_ND] = T_STORAGE_R_NV(t,sv_x),\
        (* const y)[ND_ND] = T_STORAGE_R_NV(t,sv_y),\
        (* const z)[ND_ND] = T_STORAGE_R_NV(t,sv_z)
#else
#define ND_CACHE_T_SV_R(x,y,z,t,sv_x,sv_y,sv_z)\
  real  * const x = T_STORAGE_R(t,sv_x),\
        * const y = T_STORAGE_R(t,sv_y)
#define ND_CACHE_T_SV_R_NV(x,y,z,t,sv_x,sv_y,sv_z)\
  real  (* const x)[ND_ND] = T_STORAGE_R_NV(t,sv_x),\
        (* const y)[ND_ND] = T_STORAGE_R_NV(t,sv_y)
#endif
#define ND_3_CACHE_T_SV_R(x,y,z,t,sv_x,sv_y,sv_z)\
  real  * const x = T_STORAGE_R(t,sv_x),\
        * const y = T_STORAGE_R(t,sv_y),\
        * const z = T_STORAGE_R(t,sv_z)
#define ND_3_CACHE_T_SV_R_NV(x,y,z,t,sv_x,sv_y,sv_z)\
  real  (* const x)[ND_ND] = T_STORAGE_R_NV(t,sv_x),\
        (* const y)[ND_ND] = T_STORAGE_R_NV(t,sv_y),\
        (* const z)[ND_ND] = T_STORAGE_R_NV(t,sv_z)

#define MP_CACHE_T_SV(type,x,n_phases,pt,sv)\
  type * x[MAX_PHASES] = {0};\
  for(int _phase=0; (_phase < n_phases) && (_phase < MAX_PHASES); ++_phase)\
  {\
    x[_phase] = T_STORAGE(pt[_phase],sv,type *);\
  }

#define MP_ND_CACHE_T_SV(type,x,n_phases,pt,sv)\
  type * x[MAX_PHASES][ND_ND] = {{0}};\
  for(int _phase=0; (_phase < n_phases) && (_phase < MAX_PHASES); ++_phase)\
  {\
    x[_phase] = T_STORAGE(pt[_phase],sv,type (*)[ND_ND]);\
  }


#define MP_CACHE_T_SV_I(x,n_phases,pt,sv)         MP_CACHE_T_SV(int,x,n_phases,pt,sv)
#define MP_CACHE_T_SV_INDEX(x,n_phases,pt,sv)     MP_CACHE_T_SV(cxindex,x,n_phases,pt,sv)
#define MP_CACHE_T_SV_UINDEX(x,n_phases,pt,sv)    MP_CACHE_T_SV(cxindexU,x,n_phases,pt,sv)
#define MP_CACHE_T_SV_R(x,n_phases,pt,sv)         MP_CACHE_T_SV(real,x,n_phases,pt,sv)
#define MP_CACHE_T_SV_DB(x,n_phases,pt,sv)        MP_CACHE_T_SV(double,x,n_phases,pt,sv)

#define MP_ND_CACHE_T_SV_I(x,n_phases,pt,sv)      MP_ND_CACHE_T_SV(int,x,n_phases,pt,sv)
#define MP_ND_CACHE_T_SV_INDEX(x,n_phases,pt,sv)  MP_ND_CACHE_T_SV(cxindex,x,n_phases,pt,sv)
#define MP_ND_CACHE_T_SV_UINDEX(x,n_phases,pt,sv) MP_ND_CACHE_T_SV(cxindexU,x,n_phases,pt,sv)
#define MP_ND_CACHE_T_SV_R(x,n_phases,pt,sv)      MP_ND_CACHE_T_SV(real,x,n_phases,pt,sv)
#define MP_ND_CACHE_T_SV_DB(x,n_phases,pt,sv)     MP_ND_CACHE_T_SV(double,x,n_phases,pt,sv)

#define C_STORAGE_I(c,t,n)(T_STORAGE_I_NO_CHECK(t,n)[c])
#define C_STORAGE_INDEX(c,t,n)(T_STORAGE_INDEX_NO_CHECK(t,n)[c])
#define C_STORAGE_UI(c,t,n)(T_STORAGE_UI_NO_CHECK(t,n)[c])
#define F_STORAGE_I(f,t,n) C_STORAGE_I(f,t,n)
#define F_STORAGE_INDEX(f,t,n) C_STORAGE_INDEX(f,t,n)
#define F_STORAGE_UI(f,t,n) C_STORAGE_UI(f,t,n)
#define N_STORAGE_I(V,t,n) C_STORAGE_I(V,t,n)
#define C_STORAGE_R(c,t,n)(T_STORAGE_R_NO_CHECK(t,n)[c])
#define F_STORAGE_R(f,t,n) C_STORAGE_R(f,t,n)
#define N_STORAGE_R(V,t,n) C_STORAGE_R(V,t,n)
#define C_STORAGE_DB(c,t,n)(T_STORAGE_DB_NO_CHECK(t,n)[c])
#define F_STORAGE_DB(f,t,n) C_STORAGE_DB(f,t,n)
#define N_STORAGE_DB(V,t,n) C_STORAGE_DB(V,t,n)
#define N_STORAGE_R_N3V(V,t,n) C_STORAGE_R_N3V(V,t,n)
#define C_STORAGE_R_NV(c,t,n)(T_STORAGE_R_NV_NO_CHECK(t,n)[c])
#define C_STORAGE_DP_NV(c,t,n)(T_STORAGE_DP_NV_NO_CHECK(t,n)[c])
#define F_STORAGE_R_NV(f,t,n) C_STORAGE_R_NV(f,t,n)
#define N_STORAGE_R_NV(V,t,n) C_STORAGE_R_NV(V,t,n)
#define N_STORAGE_DP_NV(V,t,n) C_STORAGE_DP_NV(V,t,n)
#define C_STORAGE_R_N3V(c,t,n)(T_STORAGE_R_N3V_NO_CHECK(t,n)[c])
#define F_STORAGE_R_N3V(f,t,n) C_STORAGE_R_N3V(f,t,n)
#define C_STORAGE_I_XV(c,t,n,i)(T_STORAGE_I_XV_NO_CHECK(t,n,i)[c])
#define C_STORAGE_R_XV(c,t,n,i)(T_STORAGE_R_XV_NO_CHECK(t,n,i)[c])
#define C_STORAGE_R_NV_XV(c,t,n,i)(T_STORAGE_R_NV_XV(t,n,i)[c])
#define N_STORAGE_R_XV(V,t,n,i) C_STORAGE_R_XV(V,t,n,i)
#define F_STORAGE_R_XV(f,t,n,i) C_STORAGE_R_XV(f,t,n,i)
#define F_STORAGE_I_XV(f,t,n,i) C_STORAGE_I_XV(f,t,n,i)
#define F_STORAGE_R_NV_XV(f,t,n,i)(T_STORAGE_R_NV_XV(t,n,i)[f])

#if STORAGE_SHORTCUTS &&(!UDF_COMPILER)
#include "svar_shortcuts.h"
#define FAST_T_STORAGE(t, sv, type) ((type)((t)->storageArray[DECLARE_SVAR_SHORTCUT(sv)]))
#define FAST_C_STORAGE(c, t, sv, type) (FAST_T_STORAGE(t, sv, type)[c])
#define FAST_C_STORAGE_R(c, t, sv) FAST_C_STORAGE(c, t, sv, real*)
#define FAST_C_STORAGE_I(c, t, sv) FAST_C_STORAGE(c, t, sv, int*)
#define FAST_C_STORAGE_INDEX(c, t, sv) FAST_C_STORAGE(c, t, sv, cxindex *)
#define FAST_C_STORAGE_UI(c, t, sv) FAST_C_STORAGE(c, t, sv, unsigned int *)
#define FAST_C_STORAGE_R_NV(c, t, sv) FAST_C_STORAGE(c, t, sv, real(*)[ND_ND])
#define FAST_C_STORAGE_R_XV(c, t, sv, i) FAST_T_STORAGE(t, sv, real**)[i][c]
#define FAST_C_STORAGE_R_N3V(c, t, sv) FAST_C_STORAGE(c, t,sv, real (*)[ND_3])
#define FAST_C_STORAGE_DP_NV(c,t,sv) FAST_C_STORAGE(c, t, sv, double(*)[ND_ND])
#else
#define FAST_C_STORAGE(c, t, sv, type)    C_STORAGE(c, t, sv, type)
#define FAST_C_STORAGE_R(c, t, sv)        C_STORAGE_R(c, t, sv)
#define FAST_C_STORAGE_I(c, t, sv)        C_STORAGE_I(c, t, sv)
#define FAST_C_STORAGE_INDEX(c, t, sv)    C_STORAGE_INDEX(c, t, sv)
#define FAST_C_STORAGE_UI(c, t, sv)       C_STORAGE_UI(c, t, sv)
#define FAST_C_STORAGE_R_NV(c, t, sv)     C_STORAGE_R_NV(c, t, sv)
#define FAST_C_STORAGE_R_XV(c, t, sv, i)  C_STORAGE_R_XV(c, t, sv, i)
#define FAST_C_STORAGE_R_N3V(c, t, sv)    C_STORAGE_R_N3V(c, t, sv)
#define FAST_C_STORAGE_DP_NV(c,t,sv)      C_STORAGE_DP_NV(c,t,sv)
#endif

#define FAST_F_STORAGE(e, t, sv, type)    FAST_C_STORAGE(e, t, sv, type)
#define FAST_F_STORAGE_R(e, t, sv)        FAST_C_STORAGE_R(e, t, sv)
#define FAST_F_STORAGE_I(e, t, sv)        FAST_C_STORAGE_I(e, t, sv)
#define FAST_F_STORAGE_INDEX(e, t, sv)    FAST_C_STORAGE_INDEX(e, t, sv)
#define FAST_F_STORAGE_UI(e, t, sv)       FAST_C_STORAGE_UI(e, t, sv)
#define FAST_F_STORAGE_R_NV(e, t, sv)     FAST_C_STORAGE_R_NV(e, t, sv)
#define FAST_F_STORAGE_R_XV(e, t, sv, i)  FAST_C_STORAGE_R_XV(e, t, sv, i)
#define FAST_F_STORAGE_R_N3V(e, t, sv)    FAST_C_STORAGE_R_N3V(e, t, sv)
#define FAST_F_STORAGE_DP_NV(e,t,sv)      FAST_C_STORAGE_DP_NV(e,t,sv)

#define FAST_N_STORAGE(e, t, sv, type)    FAST_C_STORAGE(e, t, sv, type)
#define FAST_N_STORAGE_R(e, t, sv)        FAST_C_STORAGE_R(e, t, sv)
#define FAST_N_STORAGE_I(e, t, sv)        FAST_C_STORAGE_I(e, t, sv)
#define FAST_N_STORAGE_INDEX(e, t, sv)    FAST_C_STORAGE_INDEX(e, t, sv)
#define FAST_N_STORAGE_UI(e, t, sv)       FAST_C_STORAGE_UI(e, t, sv)
#define FAST_N_STORAGE_R_NV(e, t, sv)     FAST_C_STORAGE_R_NV(e, t, sv)
#define FAST_N_STORAGE_R_XV(e, t, sv, i)  FAST_C_STORAGE_R_XV(e, t, sv, i)
#define FAST_N_STORAGE_R_N3V(e, t, sv)    FAST_C_STORAGE_R_N3V(e, t, sv)
#define FAST_N_STORAGE_DP_NV(e,t,sv)      FAST_C_STORAGE_DP_NV(e,t,sv)

#define C_PSEUDO_DT(c,t)  C_STORAGE_R(c,t,dual_ts_param.sv_dtau)
#define C_FLUX_SUM(c,t) C_STORAGE_R(c,t,SV_FLUX_SUM)


/* dependent variable cell storage */
#define C_R(c,t)  FAST_C_STORAGE_R(c,t,SV_DENSITY)
#define C_P(c,t)  FAST_C_STORAGE_R(c,t,SV_P)
#define C_U(c,t)  FAST_C_STORAGE_R(c,t,SV_U)
#define C_V(c,t)  FAST_C_STORAGE_R(c,t,SV_V)
#define C_W(c,t)  FAST_C_STORAGE_R(c,t,SV_W)
#define C_T(c,t)  FAST_C_STORAGE_R(c,t,SV_T)
#define C_T_MEAN(c,t)  FAST_C_STORAGE_R(c,t,SV_T_MEAN)
#define C_H(c,t)  FAST_C_STORAGE_R(c,t,SV_H)
#define C_K(c,t)  FAST_C_STORAGE_R(c,t,SV_K)
#define C_KL(c,t)  C_STORAGE_R(c,t,SV_KL)
#define C_KT(c,t)  C_STORAGE_R(c,t,SV_KT)
#define C_NUT(c,t)  FAST_C_STORAGE_R(c,t,SV_NUT)
#define C_D(c,t)  FAST_C_STORAGE_R(c,t,SV_D)
#define C_O(c,t)  FAST_C_STORAGE_R(c,t,SV_O)
#define C_V2(c,t)  C_STORAGE_R(c,t,SV_V2)
#define C_FEL(c,t)  C_STORAGE_R(c,t,SV_FEL)
#define C_INTERMIT(c,t)  C_STORAGE_R(c,t,SV_INTERMIT)
#define C_INTERMIT_EFF(c,t)  C_STORAGE_R(c,t,SV_INTERMIT_EFF)
#define C_INTERMIT_EFF_SMOOTH(c,t)  C_STORAGE_R(c,t,SV_INTERMIT_EFF_SMOOTH)
#define C_INTERMIT_ALGEBRAIC(c,t)  C_STORAGE_R(c,t,SV_INTERMIT_ALGEBRAIC)
#define C_INTERMIT_ALGEBRAIC_SMOOTH(c,t)  C_STORAGE_R(c,t,SV_INTERMIT_ALGEBRAIC_SMOOTH)
#define C_TRANS_ALG_REC(c,t)  C_STORAGE_R(c,t,SV_TRANS_ALG_REC)
#define C_ML_TKE_COEF(c,t)  C_STORAGE_R(c,t,SV_ML_TKE_COEF)
#define C_ML_OMEGA_COEF(c,t)  C_STORAGE_R(c,t,SV_ML_OMEGA_COEF)
#define C_ML_TRANS_ALG_COEF(c,t)  C_STORAGE_R(c,t,SV_ML_TRANS_ALG_COEF)
#define C_ML_WJ_EARSM_BETA1(c,t)  C_STORAGE_R(c,t,SV_ML_WJ_EARSM_BETA1)
#define C_ML_WJ_EARSM_BETA3(c,t)  C_STORAGE_R(c,t,SV_ML_WJ_EARSM_BETA3)
#define C_ML_WJ_EARSM_BETA4(c,t)  C_STORAGE_R(c,t,SV_ML_WJ_EARSM_BETA4)
#define C_ML_WJ_EARSM_BETA6(c,t)  C_STORAGE_R(c,t,SV_ML_WJ_EARSM_BETA6)
#define C_VSTG_SBES_FW(c,t)  C_STORAGE_R(c,t,SV_VSTG_SBES_FW)
#define C_RETHETA(c,t)  C_STORAGE_R(c,t,SV_RETHETA)
#define C_GEOMRGH(c,t)  C_STORAGE_R(c,t,SV_GEOMETRIC_ROUGHNESS_HEIGHT)
#define C_TKE_FOR_TU(c,t)  C_STORAGE_R(c,t,SV_TKE_FOR_TU)
#define C_UINI(c,t)  C_STORAGE_R(c,t,SV_UINI)
#define C_UINI_G(c,t)  C_STORAGE_R_NV(c,t,SV_UINI_G)
#define C_VORTNORM_X_G(c,t)  C_STORAGE_R_NV(c,t,SV_VORTNORM_X_G)
#define C_VORTNORM_Y_G(c,t)  C_STORAGE_R_NV(c,t,SV_VORTNORM_Y_G)
#define C_VORTNORM_Z_G(c,t)  C_STORAGE_R_NV(c,t,SV_VORTNORM_Z_G)
#define C_D2U(c,t)  C_STORAGE_R(c,t,SV_D2U)
#define C_D2V(c,t)  C_STORAGE_R(c,t,SV_D2V)
#define C_D2W(c,t)  C_STORAGE_R(c,t,SV_D2W)
#define C_SAS_STRAIN_MAG(c,g)  C_STORAGE_R(c,t,SV_SAS_STRAIN_MAG)
#define C_YI_MELT(c,t,i)C_STORAGE_R(c,t,(Svar)(SV_YI_MELT_0+i))
#define C_YI(c,t,i)  FAST_C_STORAGE_R_XV(c,t,SV_Y,i)
#define C_SOOTSPECIES(c,t,i)  C_STORAGE_R_XV(c,t,SV_SOOTSPECIES,i)
#define C_SOOTSPECIES_SOURCE(c,t,i)  C_STORAGE_R_XV(c,t,SV_SOOTSPECIES_S,i)
#define C_SOOTSPECIES_SOURCE_AP(c,t,i)  C_STORAGE_R_XV(c,t,SV_SOOTSPECIES_AP,i)
#define C_SOOTSPECIES_DENSITY(c,t)  C_STORAGE_R(c,t,SV_SOOTSPECIES_DENSITY)
#define C_SOOTSPECIES_OCCUPANCY(c,t,i)  C_STORAGE_R_XV(c,t,SV_SOOTSPECIES_OCCUPANCY,i)
#define C_TFM_F(c,t)  C_STORAGE_R(c,t,SV_TFM_F)
#define C_TFM_E(c,t)  C_STORAGE_R(c,t,SV_TFM_E)
#define C_TFM_OMEGA(c,t)  C_STORAGE_R(c,t,SV_TFM_OMEGA)
#define C_UDSI(c,t,i)C_STORAGE_R(c,t,SV_UDS_I(i))
#define C_ADSI(c,t,i)C_STORAGE_R(c,t,SV_ADS_I(i))
#define C_CDS(c,t) C_STORAGE_R(c,t,SV_CDS)
#define C_UDMI(c,t,i)  C_STORAGE_R_XV(c,t,SV_UDM_I,i)
#define C_RTDFT_RP_I(c,t,i)  C_STORAGE_R_XV(c,t,SV_RTDFT_RP_I,i)
#define C_RTDFT_IP_I(c,t,i)  C_STORAGE_R_XV(c,t,SV_RTDFT_IP_I,i)
#define C_YI_EDC(c,t,i)  C_STORAGE_R_XV(c,t,SV_YI_EDC,i)
#define C_MEAN_YI_PDFT(c,t,i) (DOMAIN_Y_AVE_MAP(THREAD_DOMAIN(t),i)>=0 ?   FAST_C_STORAGE_R_XV(c,t,SV_Y_MEAN,DOMAIN_Y_AVE_MAP(THREAD_DOMAIN(t),i)) / MAX(   C_STORAGE_R(c,t,SV_PDFT_MASS_TA), SMALL_S ) : 0.0)
#define C_VAR_YI_PDFT(c,t,i) (DOMAIN_Y_AVE_MAP(THREAD_DOMAIN(t),i)>=0 ?   FAST_C_STORAGE_R_XV(c,t,SV_Y_RMS,DOMAIN_Y_AVE_MAP(THREAD_DOMAIN(t),i)) / MAX(   C_STORAGE_R(c,t,SV_PDFT_MASS_TA), SMALL_S ) : 0.0)
#define C_MEAN_T_PDFT(c,t)   FAST_C_STORAGE_R(c,t,SV_T_MEAN) / MAX(   C_STORAGE_R(c,t,SV_PDFT_MASS_TA), SMALL_S )
#define C_VAR_T_PDFT(c,t)   FAST_C_STORAGE_R(c,t,SV_T_RMS) / MAX(   C_STORAGE_R(c,t,SV_PDFT_MASS_TA), SMALL_S )
#define C_EPDF_CORR(c,t,i,j) (T_STORAGE(t,SV_EPDF_CORR, real *)[c*j+i])
#define C_EPDF_STIFF(c,t,ns,i,j) (T_STORAGE(t, (Svar)(SV_EPDF_STIFF_0+(ns)),real *)[c*j+i])
#define C_EPDF_YI(c,t)   C_STORAGE_R(c,t,SV_EPDF_YI)
#define C_EPDF(c,t,ns,mode) C_STORAGE_R_XV(c,t,SV_EPDF_I(ns),mode)
#define C_DW(c,t,mode)   C_STORAGE_R_XV(c,t,SV_DW,mode)
#define C_EPDF_VAR(c,t,i) C_STORAGE_R(c,t,(Svar)(SV_EPDF_VAR_0+i))
#define C_EPDF_T(c,t,mode)   C_STORAGE_R_XV(c,t,SV_EPDF_T,mode)
#define C_EPDF_H(c,t,mode)   C_STORAGE_R_XV(c,t,SV_EPDF_H,mode)
#define C_EPDF_HSRC_YI(c,t,mode)   C_STORAGE_R_XV(c,t,SV_EPDF_HSRC_YI,mode)
#define C_LMS_U(c,t)  C_STORAGE_R(c,t,SV_LMS_U)
#define C_LMS_V(c,t)  C_STORAGE_R(c,t,SV_LMS_V)
#define C_LMS_W(c,t)  C_STORAGE_R(c,t,SV_LMS_W)
#define C_LMS_BD(c,t)  C_STORAGE_R(c,t,SV_LMS_BD)
#define C_SOOT_MOM(c,t,i) C_STORAGE_R(c,t,SV_SOOT_MOM_I(i))
#define C_SOOT_MOM_AGG(c,t,i) C_STORAGE_R(c,t,SV_SOOT_MOM_AGG_I(i))
#define C_SOOT_MOM_AREA(c,t) C_STORAGE_R(c,t,SV_SOOT_MOM_AREA)
#if QUADRATIC_FIT_SCHEME  /* QUADRATIC_FIT_SCHEME is defined in store.h */
#define C_QUAD_FIT_MATRIX(c,t,i,j)(T_STORAGE(t,SV_QUAD_FIT_MATRIX,real *)[(c)*196+(i)*14+(j)])
#endif
#define C_MOVING_AVG(c,t,n,i)  C_STORAGE_R_XV(c,t,SV_STAT_SEG_DATASET_MOV_AVG(n), i)

/* dependent variable face storage */
#define F_R(e,t) C_R(e,t)
#define F_P(e,t) C_P(e,t)
#define F_U(e,t) C_U(e,t)
#define F_V(e,t) C_V(e,t)
#define F_W(e,t) C_W(e,t)
#define F_T(e,t) C_T(e,t)
#define F_T_MEAN(e,t) C_T_MEAN(e,t)
#define F_H(e,t) C_H(e,t)
#define F_NUT(e,t) C_NUT(e,t)
#define F_K(e,t) C_K(e,t)
#define F_KL(e,t) C_KL(e,t)
#define F_KT(e,t) C_KT(e,t)
#define F_D(e,t) C_D(e,t)
#define F_O(e,t) C_O(e,t)
#define F_YI(e,t,i) C_YI(e,t,i)
#define F_SOOTSPECIES(e,t,i) C_SOOTSPECIES(e,t,i)
#define F_V2(e,t) C_V2(e,t)
#define F_FEL(e,t) C_FEL(e,t)
#define F_INTERMIT(e,t) C_INTERMIT(e,t)
#define F_RETHETA(e,t) C_RETHETA(e,t)
#define F_UDSI(e,t,i) C_UDSI(e,t,i)
#define F_ADSI(e,t,i) C_ADSI(e,t,i)
#define F_CDS(e,t) C_CDS(e,t)
#define F_UDMI(e,t,i) C_UDMI(e,t,i)
#define F_RTDFT_RP_I(e,t,i) C_RTDFT_RP_I(e,t,i)
#define F_RTDFT_IP_I(e,t,i) C_RTDFT_IP_I(e,t,i)
#define F_DW(e,t,mode) C_DW(e,t,mode)
#define F_EPDF(e,t,ns,mode) C_EPDF(e,t,ns,mode)
#define F_EPDF_YI(e,t) C_EPDF_YI(e,t)
#define F_EPDF_VAR(e,t) C_EPDF_VAR(e,t)
#define F_EPDF_T(e,t,mode) C_EPDF_T(e,t,mode)
#define F_EPDF_H(e,t,mode) C_EPDF_H(e,t,mode)
#define F_P0(f,t)   F_STORAGE_R(f,t,SV_P_STAGNATION)
#define F_T0(f,t)   F_STORAGE_R(f,t,SV_T_STAGNATION)
#define F_TDP(f,t)   FAST_F_STORAGE_R(f,t,SV_DP_TMFR)
#define F_LMS_U(e,t) C_LMS_U(e,t)
#define F_LMS_V(e,t) C_LMS_V(e,t)
#define F_LMS_W(e,t) C_LMS_W(e,t)
#define F_LMS_BD(e,t) C_LMS_BD(e,t)
#define F_MOVING_AVG(f,t,n,i) C_MOVING_AVG(f,t,n,i)

/* dependent variable node storage */
#define N_UDMI(v,i)N_STORAGE_R_XV(NODE_INDEX(v),NODE_THREAD(v),SV_NODE_UDM_I,i)

#if RP_FC
#define N_SVI(v,sv,i)N_STORAGE_R_XV(NODE_INDEX(v),NODE_THREAD(v),sv,i)
#endif

/* dependent variable time level 1 cell storage */
#define C_R_M1(c,t)  FAST_C_STORAGE_R(c,t,SV_DENSITY_M1)
#define C_P_M1(c,t)  FAST_C_STORAGE_R(c,t,SV_P_M1)
#define C_U_M1(c,t)  FAST_C_STORAGE_R(c,t,SV_U_M1)
#define C_V_M1(c,t)  FAST_C_STORAGE_R(c,t,SV_V_M1)
#define C_W_M1(c,t)  FAST_C_STORAGE_R(c,t,SV_W_M1)
#define C_T_M1(c,t)  FAST_C_STORAGE_R(c,t,SV_T_M1)
#define C_H_M1(c,t)  FAST_C_STORAGE_R(c,t,SV_H_M1)
#define C_YI_M1(c,t,i)  C_STORAGE_R_XV(c,t,SV_Y_M1,i)
#define C_UDSI_M1(c,t,i)C_STORAGE_R(c,t,SV_UDSI_M1(i))
#define C_SOOTSPECIES_M1(c,t,i)  C_STORAGE_R_XV(c,t,SV_SOOTSPECIES_M1,i)

#define F_R_M1(e,t) C_R_M1(e,t)

/* dependent variable time level 2 cell storage */
#define C_R_M2(c,t)  FAST_C_STORAGE_R(c,t,SV_DENSITY_M2)
#define C_P_M2(c,t)  FAST_C_STORAGE_R(c,t,SV_P_M2)
#define C_U_M2(c,t)  FAST_C_STORAGE_R(c,t,SV_U_M2)
#define C_V_M2(c,t)  FAST_C_STORAGE_R(c,t,SV_V_M2)
#define C_W_M2(c,t)  FAST_C_STORAGE_R(c,t,SV_W_M2)
#define C_T_M2(c,t)  FAST_C_STORAGE_R(c,t,SV_T_M2)
#define C_H_M2(c,t)  C_STORAGE_R(c,t,SV_H_M2)
#define C_YI_M2(c,t,i)  C_STORAGE_R_XV(c,t,SV_Y_M2,i)
#define C_UDSI_M2(c,t,i)C_STORAGE_R(c,t,SV_UDSI_M2(i))
#define C_SOOTSPECIES_M2(c,t,i)  C_STORAGE_R_XV(c,t,SV_SOOTSPECIES_M2,i)

#define F_R_M2(e,t) C_R_M2(e,t)

/*for gen. nrbc use*/
#define F_U_M1(e,t) C_U_M1(e,t)
#define F_V_M1(e,t) C_V_M1(e,t)
#define F_W_M1(e,t) C_W_M1(e,t)
#define F_T_M1(e,t) C_T_M1(e,t)
#define F_P_M1(e,t) C_P_M1(e,t)

#define F_U_M2(e,t) C_U_M2(e,t)
#define F_V_M2(e,t) C_V_M2(e,t)
#define F_W_M2(e,t) C_W_M2(e,t)
#define F_T_M2(e,t) C_T_M2(e,t)
#define F_P_M2(e,t) C_P_M2(e,t)

/* dependent variables for generic time bounded second order formulation
 * PH = time level n+1/2
 * NH = time level n-1/2 */
#define C_RHO_PH(c,t)   FAST_C_STORAGE_R(c,t,SV_DENSITY_PH)
#define C_RHO_NH(c,t)   FAST_C_STORAGE_R(c,t,SV_DENSITY_NH)

/* dependent variable cell gradient (derivative) storage */
#define C_P_G(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_P_G)       /* replaces C_DP(c,t), see sg_mem.h*/
#define C_P_G_LIMITED(c,t)  C_STORAGE_R_NV(c,t,SV_P_G_LIMITED)
#define C_R_G(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_DENSITY_G) /* replaces C_D_DENSITY(c,t), see sg_mem.h*/
#define C_U_G(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_U_G)
#define C_V_G(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_V_G)
#define C_W_G(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_W_G)
#define C_T_G(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_T_G)
#define C_H_G(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_H_G)
#define C_NUT_G(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_NUT_G)
#define C_OMEGA_G(c,t)  C_STORAGE_R_NV(c,t,SV_OMEGA_G)
#define C_K_G(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_K_G)
#define C_KL_G(c,t)  C_STORAGE_R_NV(c,t,SV_KL_G)
#define C_KT_G(c,t)  C_STORAGE_R_NV(c,t,SV_KT_G)
#define C_D_G(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_D_G)
#define C_O_G(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_O_G)
#define C_V2_G(c,t)  C_STORAGE_R_NV(c,t,SV_V2_G)
#define C_FEL_G(c,t)  C_STORAGE_R_NV(c,t,SV_FEL_G)
#define C_INTERMIT_G(c,t)  C_STORAGE_R_NV(c,t,SV_INTERMIT_G)
#define C_RETHETA_G(c,t)  C_STORAGE_R_NV(c,t,SV_RETHETA_G)
#define C_YI_G(c,t,i)C_STORAGE_R_NV_XV(c,t,SV_Y_G,i)
#define C_UDSI_G(c,t,i) C_STORAGE_R_NV(c,t,SV_UDS_I(i)+SV_UDS_0_G-SV_UDS_0)
#define C_ADSI_G(c,t,i) C_STORAGE_R_NV(c,t,SV_ADS_I(i)+SV_ADS_0_G-SV_ADS_0)
#define C_PHI_1_G(c,t)  C_STORAGE_R_NV(c,t,SV_PHI_1_SAVED_G)
#define C_PHI_2_G(c,t)  C_STORAGE_R_NV(c,t,SV_PHI_2_SAVED_G)
#define C_CDS_G(c,t) C_STORAGE_R_NV(c,t,SV_CDS_G)

/* dependent variable cell reconstruction gradient storage */
#define C_P_RG(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_P_RG)
#define C_R_RG(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_DENSITY_RG)
#define C_U_RG(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_U_RG)
#define C_V_RG(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_V_RG)
#define C_W_RG(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_W_RG)
#define C_T_RG(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_T_RG)
#define C_H_RG(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_H_RG)
#define C_NUT_RG(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_NUT_RG)
#define C_K_RG(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_K_RG)
#define C_KL_RG(c,t)  C_STORAGE_R_NV(c,t,SV_KL_RG)
#define C_KT_RG(c,t)  C_STORAGE_R_NV(c,t,SV_KT_RG)
#define C_D_RG(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_D_RG)
#define C_V2_RG(c,t)  C_STORAGE_R_NV(c,t,SV_V2_RG)
#define C_FEL_RG(c,t)  C_STORAGE_R_NV(c,t,SV_FEL_RG)
#define C_INTERMIT_RG(c,t)  C_STORAGE_R_NV(c,t,SV_INTERMIT_RG)
#define C_RETHETA_RG(c,t)  C_STORAGE_R_NV(c,t,SV_RETHETA_RG)
#define C_YI_RG(c,t,i)C_STORAGE_R_NV_XV(c,t,SV_Y_RG,i)

#define C_SQRT_KT_G(c,t)  C_STORAGE_R_NV(c,t,SV_SQRT_KT_G)
#define C_SQRT_KL_G(c,t)  C_STORAGE_R_NV(c,t,SV_SQRT_KL_G)

/* absolute pressure */
#define ABS_P(p,op)((p)+(op))

/* velocity magnitude */
#define C_VMAG2(c,t)N3D_MAG2(C_U(c,t),C_V(c,t),C_W(c,t))
#define F_VMAG2(e,t) C_VMAG2(e,t)

/* velocity gradients */
#define C_DUDX(c,t)(C_U_G(c,t)[0])
#define C_DUDY(c,t)(C_U_G(c,t)[1])
#define C_DUDZ(c,t)(C_U_G(c,t)[2])
#define C_DVDX(c,t)(C_V_G(c,t)[0])
#define C_DVDY(c,t)(C_V_G(c,t)[1])
#define C_DVDZ(c,t)(C_V_G(c,t)[2])
#define C_DWDX(c,t)(C_W_G(c,t)[0])
#define C_DWDY(c,t)(C_W_G(c,t)[1])
#define C_DWDZ(c,t)(C_W_G(c,t)[2])

#if RP_2D
#define C_STRAIN_RATE_MAG(c,t)\
sqrt(ND_SUM(ND_DOT(C_DUDX(c,t), C_DUDY(c,t), C_DUDZ(c,t),\
       (C_DUDX(c,t) + C_DUDX(c,t)),\
       (C_DUDY(c,t) + C_DVDX(c,t)),\
       (C_DUDZ(c,t) + C_DWDX(c,t))),\
      ND_DOT(C_DVDX(c,t), C_DVDY(c,t), C_DVDZ(c,t),\
       (C_DVDX(c,t) + C_DUDY(c,t)),\
       (C_DVDY(c,t) + C_DVDY(c,t)),\
       (C_DVDZ(c,t) + C_DWDY(c,t))),\
      ND_DOT(C_DWDX(c,t), C_DWDY(c,t), C_DWDZ(c,t),\
       (C_DWDX(c,t) + C_DUDZ(c,t)),\
       (C_DWDY(c,t) + C_DVDZ(c,t)),\
       (C_DWDZ(c,t) + C_DWDZ(c,t))))\
            + (rp_axi ? \
               (2.*SQR(C_V(c,t)/C_AVE_Y(c,t)) \
                + (sg_swirl ? \
                   (SQR(C_AVE_Y(c,t))*NV_MAG2(  C_STORAGE_R_NV(c,t,SV_OMEGA_G))): \
                   0.)): \
               0.) \
              )
#else
#define C_STRAIN_RATE_MAG(c,t)\
sqrt(ND_SUM(ND_DOT(C_DUDX(c,t), C_DUDY(c,t), C_DUDZ(c,t),\
       (C_DUDX(c,t) + C_DUDX(c,t)),\
       (C_DUDY(c,t) + C_DVDX(c,t)),\
       (C_DUDZ(c,t) + C_DWDX(c,t))),\
      ND_DOT(C_DVDX(c,t), C_DVDY(c,t), C_DVDZ(c,t),\
       (C_DVDX(c,t) + C_DUDY(c,t)),\
       (C_DVDY(c,t) + C_DVDY(c,t)),\
       (C_DVDZ(c,t) + C_DWDY(c,t))),\
      ND_DOT(C_DWDX(c,t), C_DWDY(c,t), C_DWDZ(c,t),\
       (C_DWDX(c,t) + C_DUDZ(c,t)),\
       (C_DWDY(c,t) + C_DVDZ(c,t)),\
       (C_DWDZ(c,t) + C_DWDZ(c,t)))))
#endif

/* diffusion coefficients (mu, ktc, diff) */
#define C_MU_L(c,t)  FAST_C_STORAGE_R(c,t,SV_MU_LAM)
#define C_MU_L_CACHE(_ml,c)(_ml[c])

#ifndef RP_ALWAYS_ALLOCATE_MU_T
# define RP_ALWAYS_ALLOCATE_MU_T 0
#endif

#if RP_ALWAYS_ALLOCATE_MU_T
# define C_MU_T(c,t)  FAST_C_STORAGE_R(c,t,SV_MU_T)
# define C_MU_T_CACHE(_mt,c)(_mt[c])
# define C_MU_T_STORAGE(c,t) C_MU_T(c,t)
#else
# define C_MU_T_STORAGE(c,t)  FAST_C_STORAGE_R(c,t,SV_MU_T)
# define C_MU_T(c,t)((rp_turb)?C_MU_T_STORAGE(c,t):0.)
# define C_MU_T_CACHE(_mt,c)((rp_turb)?(_mt[c]):0.)
#endif

#define C_MU_T_LES_ZONE(c,t)  C_STORAGE_R(c,t,SV_MU_T_LES_ZONE)
#define C_MU_T_SBES_RANS(c,t)  C_STORAGE_R(c,t,SV_MU_T_SBES_RANS)

#define C_MU_TL(c,t)  C_STORAGE_R(c,t,SV_MU_TL)
#define C_MU_TS(c,t)  C_STORAGE_R(c,t,SV_MU_TS)

#define C_MU_EFF_USE_K(c,t,sc) (C_K_L(c,t)/C_CP(c,t) + C_MU_T(c,t)/sc)
#define C_MU_EFF(c,t)(C_MU_L(c,t)+C_MU_T(c,t))
#define C_MU_EFF_CACHE(_ml, _mt, c)((_ml)[c] + (_mt)[c])

#define C_K_L(c,t)(NULLP(THREAD_STORAGE(t,SV_KTC)) ?\
       THREAD_PROP(t,PROP_ktc,0) :   FAST_C_STORAGE_R(c,t,SV_KTC))
#define C_K_T(c,t,prt)(C_MU_T(c,t)*C_CP(c,t)/prt)
#define C_K_EFF(c,t,prt)(C_K_L(c,t) + (M_thickened_flame ?\
               C_TFM_OMEGA(c,t)*C_K_T(c,t,prt) : C_K_T(c,t,prt)))
#define C_K_POR(c,t)(NULLP(THREAD_STORAGE(t,SV_KTC_por)) ?\
                   (NULLP(THREAD_SOLID_MATERIAL(t)) ? 0: \
                   MATERIAL_PROP(THREAD_SOLID_MATERIAL(t),PROP_ktc)): C_STORAGE_R(c,t,SV_KTC_por))

#define C_DIFF_L(c,t,i,j) \
  C_STORAGE_R_XV((DOMAIN_MULTICOMP_DIFF(THREAD_DOMAIN(t)) ? \
                 ((c)*THREAD_NSPE(t)) + j : c),t,SV_DIFF_COEFF,i)

#define C_DIFF_EFF(c,t,i)\
(rp_turb ?\
 (C_DIFF_L(c,t,i,i) + (M_thickened_flame ?\
           C_TFM_OMEGA(c,t)*(C_MU_T(c,t)/(C_R(c,t)*M_species_sct)):\
           (C_MU_T(c,t)/(C_R(c,t)*M_species_sct)))):\
    C_DIFF_L(c,t,i,i))

#define C_THERMAL_DIFF(c,t,i)  C_STORAGE_R_XV(c,t,SV_THERMAL_DIFF_COEFF,i)
#define C_UDSI_DIFF(c,t,i)C_STORAGE_R(c,t, (Svar)(SV_UDS_DIFF_COEFF_0+i))

/*
#define C_POR(c,t) (NULLP(THREAD_STORAGE(t,SV_POROSITY)) ?\
                       1.0:   FAST_C_STORAGE_R(c,t,SV_POROSITY))
*/
#if 1
#define C_POR(c,t) ((FLUID_THREAD_P(t) && THREAD_VAR(t).fluid.porous) ? \
                     F_VAR(c,t,THREAD_VAR(t).fluid.porosity) : 1.0)
#define C_POR_M1(c,t) (NULLP(THREAD_STORAGE(t,SV_POROSITY_M1)) ?\
                       1.0:   C_STORAGE_R(c,t,SV_POROSITY_M1))
#define C_POR_M2(c,t) (NULLP(THREAD_STORAGE(t,SV_POROSITY_M2)) ?\
                       1.0 :   C_STORAGE_R(c,t,SV_POROSITY_M2))
#else
#define C_POR(c,t) ( (sg_mphase && DOMAIN_N_DOMAINS(THREAD_DOMAIN(t))==0)? \
                   ((FLUID_THREAD_P(THREAD_SUPER_THREAD(t)) && THREAD_VAR(THREAD_SUPER_THREAD(t)).fluid.porous) ? \
                     F_VAR(c,THREAD_SUPER_THREAD(t),THREAD_VAR(THREAD_SUPER_THREAD(t)).fluid.porosity) : 1.0) \
                 : ((FLUID_THREAD_P(t) && THREAD_VAR(t).fluid.porous) ? \
                     F_VAR(c,t,THREAD_VAR(t).fluid.porosity) : 1.0) )
#define C_POR_M1(c,t) (NULLP(THREAD_STORAGE(t,SV_POROSITY_M1)) ?\
                       1.0:   C_STORAGE_R(c,t,SV_POROSITY_M1))
#define C_POR_M2(c,t) (NULLP(THREAD_STORAGE(t,SV_POROSITY_M2)) ?\
                       1.0 :   C_STORAGE_R(c,t,SV_POROSITY_M2))
#endif

#define C_AREA_DENSITY(c, t) ((FLUID_THREAD_P(t) && THREAD_VAR(t).fluid.porous) ? \
                        F_VAR(c, t, THREAD_VAR(t).fluid.area_density) : 1.0)

#define C_HEAT_TRANSFER_COEFF(c, t) ((FLUID_THREAD_P(t)  && THREAD_VAR(t).fluid.porous) ? \
                                F_VAR(c, t, THREAD_VAR(t).fluid.heat_transfer_coeff) : 1.0)

#define C_DUAL_ZN_POROSITY(c,t) ((SOLID_THREAD_P(t) && THREAD_VAR(t).solid.non_equib_thermal) ?\
                                    C_STORAGE_R(c,t,SV_DC_FLUID_POR) :1.0)
#define C_POR_v_form(c,t)(por_vel_form? (C_POR(c,t)) : 1.0)
#define C_POR_M1_v_form(c,t)(por_vel_form? (C_POR_M1(c,t)) : 1.0)
#define C_POR_M2_v_form(c,t)(por_vel_form? (C_POR_M2(c,t)) : 1.0)
#if 0
#define VEL_FORM_POROUS_INTERFACE_THREAD_P(t) ( por_vel_form && new_inf && !M_compressible &&\
                                                (t->t0 != t->t1)   && (THREAD_TYPE(t) == THREAD_F_INTERIOR) &&\
                                                (  (THREAD_VAR(t->t0).fluid.porous) \
                                                 ||(THREAD_VAR(t->t1).fluid.porous)\
                                                )\
                                              )
#else
#define VEL_FORM_POROUS_INTERFACE_THREAD_P(t) ( por_vel_form && new_inf && !M_compressible &&\
                                                (t->t0 != t->t1)   &&\
                                                (  (THREAD_VAR(t->t0).fluid.porous) \
                                                 ||(THREAD_VAR(t->t1).fluid.porous)\
                                                )\
                                              )
#endif
#define REL_PERM_OFF(t) (THREAD_VAR(THREAD_SUPER_THREAD(t)).fluid.none)
#define C_REL_PERM(c,t,satw,relperm,npts,rptab) ((mp_mfluid && !alternative_rel_perm && FLUID_THREAD_P(t) && THREAD_VAR(t).fluid.porous) ? \
       relative_permeability(c,t,satw,relperm,npts,rptab) : 1.0)
#if 0
#define RELATIVE_PERM(c,t,satw,relperm,npts,rptab) ((mp_mfluid && alternative_rel_perm && FLUID_THREAD_P(t) && THREAD_VAR(t).fluid.porous)? \
          relative_permeability(c,t,satw,relperm,npts,rptab) : 1.0)
#endif

#define RELATIVE_PERM(c,t) 1.0

/*solidification melting partition coefficient*/
#define C_MELT_KP(c,t,i)(NNULLP(THREAD_STORAGE(t,(Svar) (SV_MELT_KP_0+i)))\
                        && MATERIAL_PROP_METHOD(THREAD_MATERIAL(t)->component[i],\
                        PROP_k_partition) != PROP_METHOD_CONSTANT)?\
                        C_STORAGE_R(c,t,(Svar)(SV_MELT_KP_0+i)):\
                        MATERIAL_PROP(THREAD_MATERIAL(t)->component[i],PROP_k_partition)

/* thermodynamic properties */
#define C_CP(c,t)(NULLP(THREAD_STORAGE(t,SV_CP)) ?\
      THREAD_PROP(t,PROP_Cp,0) :   FAST_C_STORAGE_R(c,t,SV_CP))
#define C_RGAS(c,t)(NULLP(THREAD_STORAGE(t,SV_RGAS)) ?\
        THREAD_PROP(t,PROP_Rgas,0) :   FAST_C_STORAGE_R(c,t,SV_RGAS))

/* speed of sound, squared */

#define RHO_P(c,t)(!NULLP(THREAD_STORAGE(t,SV_SOUND_SPEED)) ?\
                     (SQR(1.0/  FAST_C_STORAGE_R(c,t,SV_SOUND_SPEED))/C_R(c,t)):0.0 )

#define C_C2(c,t)(NULLP(THREAD_STORAGE(t,SV_SOUND_SPEED)) ?\
      (C_CP(c,t)*C_RGAS(c,t)/(C_CP(c,t)-C_RGAS(c,t))*C_T(c,t)) :\
      (REAL_EQUAL(  FAST_C_STORAGE_R(c,t,SV_SOUND_SPEED),SD_BIG) ?\
                  SD_BIG:(SQR(  FAST_C_STORAGE_R(c,t,SV_SOUND_SPEED)))))

#define C_C2_T(c,t)(NULLP(THREAD_STORAGE(t,SV_SOUND_SPEED)) ?\
      (C_CP(c,t)*C_RGAS(c,t)/(C_CP(c,t)-C_RGAS(c,t))) : 0)

#define SQRT_C_C2(c,t)(NULLP(THREAD_STORAGE(t,SV_SOUND_SPEED)) ?\
                      sqrt(C_C2(c,t)):   FAST_C_STORAGE_R(c,t,SV_SOUND_SPEED))

#define C_SOUND_SPEED(c,t)  FAST_C_STORAGE_R(c,t,SV_SOUND_SPEED)

/* electro-magnetic properties (electricl conductivity) */
#define C_ELEC_COND(c, t) (MAX((NULLP(THREAD_STORAGE(t, SV_ELEC_COND)) ?\
                          THREAD_PROP(t, PROP_elec_conductivity, 0) :\
                            C_STORAGE_R(c, t, SV_ELEC_COND)), 1.0e-15))
#define C_DUAL_ELEC_COND(c, t) (MAX((NULLP(THREAD_STORAGE(t, SV_DUAL_ELEC_COND)) ?\
                          THREAD_PROP(t, PROP_dual_elec_conductivity, 0) :\
                            C_STORAGE_R(c, t, SV_DUAL_ELEC_COND)), 1.0e-15))
#define C_MAGN_PERM(c, t) THREAD_PROP(t, PROP_mag_permeability, 0)

#define C_LI_DIFF(c, t) (IS_LI_SOLVED_ZONE_THREAD(t) ? (NULLP(THREAD_STORAGE(t, SV_LITHIUM_DIFF)) ?\
                        THREAD_PROP(t, PROP_lithium_diff, 0) :\
                            C_STORAGE_R(c, t, SV_LITHIUM_DIFF)) : 0.0)

#define C_WALL_DIST(c,t)  FAST_C_STORAGE_R(c,t,SV_WALL_DIST)
#define FACE_FORCE(f,t)   FAST_F_STORAGE_R_NV(f,t,SV_WALL_FACE_FORCE)
#define C_WALL_DIST_SKIP(c,t)C_STORAGE_BIT_GET(c,t,SV_WALL_DIST_SKIP)
#define C_WALL_DIST_SKIP_SET(c,t)C_STORAGE_BIT_SET(c,t,SV_WALL_DIST_SKIP)
#define C_WALL_DIST_SKIP_CLEAR(c,t)C_STORAGE_BIT_CLEAR(c,t,SV_WALL_DIST_SKIP)



#define C_ROUGH_SIZE(c,t) (NNULLP(THREAD_STORAGE(t,SV_ROUGH_SIZE)) ?   FAST_C_STORAGE_R(c,t,SV_ROUGH_SIZE) : 0.)

#define C_GRAD_QUALITY(_c,_t)   C_STORAGE_R(_c,_t,SV_GRAD_QUALITY)

#include "sg_mem.h"
#include "rp_mem.h"

#define F_INDEX0(f,t)  FAST_F_STORAGE_I(f,t,SV_F_A0)
#define F_INDEX1(f,t)  FAST_F_STORAGE_I(f,t,SV_F_A1)
#define F_GHOSTLINK(f,t)  F_STORAGE_I(f,t,SV_F_GHOSTLINK)

/*
 * pointers to block coefficient matrices in AMG matrix
 */

#define C_AP(c,t) BAMG_D( AMG_PVT,C_INDEX(c,t))
#define F_A01(f,t)BAMG_OD(AMG_PVT,F_INDEX0(f,t))
#define F_A10(f,t)BAMG_OD(AMG_PVT,F_INDEX1(f,t))
#define F_A01_CACHE(_cp,f)BAMG_OD(AMG_PVT,_cp[f])
#define F_A10_CACHE(_cp,f)BAMG_OD(AMG_PVT,_cp[f])

#define MATRIX(a,i,j,n) a[(j)+(i)*(n)]

/* SNCI Ghost Cells */
#define F_A_GHOSTLINK(f,t)BAMG_OD(AMG_PVT,F_GHOSTLINK(f,t))

/* mesh connectivity */
#if RP_OVERSET
#define SV_C0_THREAD_P(_t) (PARENT_FACE_THREAD_P (_t) || \
                            OVERSET_EXTENDED_INTERIOR_THREAD_P (_t))
#define SV_C1_THREAD_P(_t) (PARENT_FACE_THREAD_P (_t) || \
                            OVERSET_EXTENDED_INTERIOR_THREAD_P (_t))
#else
#define SV_C0_THREAD_P(_t) PARENT_FACE_THREAD_P (_t)
#define SV_C1_THREAD_P(_t) PARENT_FACE_THREAD_P (_t)
#endif

#ifndef CHECK_STRUCT_MACROS
/* for debugging, code will crash if macros are used on wrong type of thread */
# define CHECK_STRUCT_MACROS 0
#endif

/* cell struct macros */
#define CSP_TYPE(_e) CELL_TYPE(_e)
#define C_TYPE(_c,_t) CSP_TYPE(C_CELL(_c,_t))

#define SET_CSP_TYPE(_e, _n) SET_CELL_TYPE(_e, _n)
#define SET_C_TYPE(_c,_t,_n) SET_CSP_TYPE(C_CELL(_c, _t), _n)

#define C_CELL(_c,_t)   FAST_C_STORAGE(_c, _t, SV_CELL, Cell **)

#define C_TYPE_AND_FLAGS(_c,_t) (C_TYPE(_c, _t) | \
    (CART_ENTITY(C_CELL(_c, _t)) ? CART_IO_FLAG : 0))

#define SET_C_TYPE_AND_FLAGS(_c,_t,_n) do {   \
    SET_C_TYPE(_c,_t,_n);                     \
    if (CHECK_BITS(_n, CART_IO_FLAG))    \
    {                                         \
      SET_CART_ENTITY(C_CELL(_c, _t));        \
    }                                         \
    if (CHECK_BITS(_n, BL_IO_FLAG))    \
    {                                         \
      SET_BL_ENTITY(C_CELL(_c, _t));          \
    }                                         \
  } while(0)

#define CSP_ENTITY_KIND(_s) ENTITY_KIND(_s)
#define CSP_ENTITY_FLAGS(_s) ENTITY_FLAGS(_s)
#define SET_CSP_ENTITY_FLAGS(_s, _mask) SET_ENTITY_FLAGS(_s, _mask)
#define CLEAR_CSP_ENTITY_FLAGS(_s, _mask) CLEAR_ENTITY_FLAGS(_s, _mask)
#define CSP_ENTITY_FLAG(_s, _mask) ENTITY_FLAG(_s, _mask)

#define C_ENTITY_KIND(_c,_t) CSP_ENTITY_KIND(C_CELL(_c, _t))
#define C_ENTITY_FLAGS(_c,_t) CSP_ENTITY_FLAGS(C_CELL(_c, _t))
#define SET_C_ENTITY_FLAGS(_c,_t,_flags) SET_CSP_ENTITY_FLAGS(C_CELL(_c,_t),_flags)
#define CLEAR_C_ENTITY_FLAGS(_c,_t,_flags) CLEAR_CSP_ENTITY_FLAGS(C_CELL(_c,_t),_flags)
#define C_ENTITY_FLAG(_c,_t,_flags) CSP_ENTITY_FLAG(C_CELL(_c,_t),_flags)
#define CSP_ID(_s) ENTITY_ID1(_s)
#if CHECK_STRUCT_MACROS
# if PARALLEL
#  define C_ID(_c,_t) CSP_ID(C_CELL(_c, CELL_THREAD_P(_t) ? _t : NULL))
# else
#  define C_ID(_c,_t) ((cxindex)CSP_ID(C_CELL(_c, CELL_THREAD_P(_t) ? _t : NULL)))
# endif
#else
# if 1 /*PARALLEL*/
#  define C_ID(_c,_t) CSP_ID(C_CELL(_c, _t))
# else
#  define C_ID(_c,_t) ((cxindex)CSP_ID(C_CELL(_c, _t)))
# endif
#endif
#define CSP_IDX(_e) ENTITY_SV_IDX(_e)
#define C_IDX(_c,_t) CSP_IDX(C_CELL(_c, _t))
#define CSP_THREAD(_e) ENTITY_THREAD2(_e)
#define C_THREAD(_c,_t) CSP_THREAD(C_CELL(_c, _t))
#define CSP_THREAD_MD(_csp,_phase_id) \
  ((_phase_id < 0) ? CSP_THREAD(_csp) : THREAD_SUB_THREAD(CSP_THREAD(_csp),_phase_id))

#if RP_POLYHEDRA
# define CSP_NODES(_s)  CELL_NODES(_s)
# define CSP_NNODES(_s) CELL_NNODES(_s)
# define CSP_FACES(_s)  CELL_FACES(_s)
# define CSP_NFACES(_s) CELL_NFACES(_s)

# define SET_CSP_NNODES(_e, _nn) SET_CELL_NNODES(_e, _nn)
# define SET_CSP_NFACES(_e, _nf) SET_CELL_NFACES(_e, _nf)
# if !UDF_COMPILER
#  define C_NFACES(_c,_t) CSP_NFACES(C_CELL(_c,_t))
#  define SET_C_NFACES(_c,_t,_nf) SET_CSP_NFACES(C_CELL(_c, _t), _nf)
# endif

# define C_NODES(_c,_t)  CSP_NODES(C_CELL(_c,_t))
# define C_NNODES(_c,_t) CSP_NNODES(C_CELL(_c,_t))
# define C_FACES(_c,_t) CSP_FACES(C_CELL(_c,_t))
# define SET_C_NNODES(_c,_t,_nn) SET_CSP_NNODES(C_CELL(_c,_t),_nn)

#else
# define CSP_NODES(_s) CELL_NODES(_s)
# define C_NODES(_c,_t)  CSP_NODES(C_CELL(_c,_t))
# define C_NNODES(_c,_t) (cell_type_nnodes[C_TYPE((_c),(_t))])
# define CSP_FACES(_s) CELL_FACES(_s)
# define C_FACES(_c,_t)  CSP_FACES(C_CELL(_c,_t))
# define C_NFACES(_c,_t) (cell_type_nfaces[C_TYPE((_c),(_t))])
# define SET_C_NNODES(_c,_t) (C_NNODES(_c, _t) = \
                              cell_type_nnodes[C_TYPE((_c),(_t))])
# define SET_C_NFACES(_c,_t) (C_NFACES(_c, _t) = \
                              cell_type_nfaces[C_TYPE((_c),(_t))])
# define CSP_NNODES(_csp) (cell_type_nnodes[CSP_TYPE((_csp))])
# define CSP_NFACES(_csp) (cell_type_nfaces[CSP_TYPE((_csp))])
# define SET_CSP_NNODES(_csp, _nn)  (CSP_NNODES(_csp) = nn)
# define SET_CSP_NFACES(_csp, _nf)  (CSP_NFACES(_csp) = nf)
#endif
#define CSP_NODE(_csp,_i) (CSP_NODES(_csp)[_i])
#define C_NODE(_c,_t,_i) CSP_NODE(C_CELL(_c, _t),_i)
#define C_FACE_STRUCT(_c,_t,_i) (C_FACES (_c, _t)[_i])
#define C_FACE(_c,_t,_i) \
  (NNULLP (C_FACES (_c, _t)[_i]) ? (FSP_IDX (C_FACES (_c, _t)[_i])) : NULL_FACE)
#define CSP_FACE_STRUCT(_csp,_i) (CSP_FACES (_csp)[_i])
#define CSP_FACE(_csp,_i) (FSP_IDX (CSP_FACES (_csp)[_i]))
#define C_FACE_THREAD(_c,_t,_i) \
  (NNULLP (C_FACES (_c, _t)[_i]) ? (FSP_THREAD (C_FACES (_c, _t)[_i])) : NULL)
#define CSP_FACE_THREAD(_csp,_i) (FSP_THREAD (CSP_FACES (_csp)[_i]))
#define CSP_FACE_THREAD_MD(_csp,_i,_phase_id)       \
  ((_phase_id < 0) ? CSP_FACE_THREAD(_csp,_i) : THREAD_SUB_THREAD(CSP_FACE_THREAD(_csp,_i),_phase_id))
#define SET_C_FACE(_c,_tc,_i,_f,_tf) \
  (C_FACE_STRUCT (_c, _tc, _i) = !NULL_FACE_P (_f) ? F_FACE (_f, _tf) : NULL)
#define CLEAR_C_FACE(_c,_tc,_i) (C_FACE_STRUCT (_c, _tc, _i) = NULL)

#define C_SET_FLAG_MODIFIED_CENTROID(_c,_t) \
  (SET_C_ENTITY_FLAGS (_c, _t, CELL_MODIFIED_CENTROID_FLAG))
#define C_CLEAR_FLAG_MODIFIED_CENTROID(_c,_t) \
  (CLEAR_C_ENTITY_FLAGS (_c, _t, CELL_MODIFIED_CENTROID_FLAG))
#define C_FLAG_MODIFIED_CENTROID_P(_c,_t) \
  (C_ENTITY_FLAGS (_c, _t) & CELL_MODIFIED_CENTROID_FLAG)

#define C_SET_FLAG_PMN(_c,_t) \
  (SET_C_ENTITY_FLAGS (_c, _t, CELL_PMN_FLAG))
#define C_CLEAR_FLAG_PMN(_c,_t) \
  (CLEAR_C_ENTITY_FLAGS (_c, _t, CELL_PMN_FLAG))
#define C_FLAG_PMN_P(_c,_t) \
  (C_ENTITY_FLAGS (_c, _t) & CELL_PMN_FLAG)

#define CONTACT_ZONE_CELL_P(_c,_t) \
  (C_ENTITY_FLAGS (_c, _t) & NARROW_GAP_BLOCKED_CELL_FL)
#define CONTACT_ZONE_CELL_OLD_P(_c,_t) \
  (C_ENTITY_FLAGS (_c, _t) & NARROW_GAP_BLOCKED_CELL_FL_OLD)

#define SKIP_CONTACT_ZONE_CELL_P(_c,_t) \
  (contact_active_p?CONTACT_ZONE_CELL_P(_c,_t):0)

#define NARROW_GAP_ALL_CELL_FL_MASK (NARROW_GAP_BLOCKED_CELL_FL | NARROW_GAP_MODELED_CELL_FL)
#define NARROW_GAP_ALL_FACE_FL_MASK (NARROW_GAP_ALL_BLOCKED_FACE_FL | NARROW_GAP_ALL_MODELED_FACE_FL)
#define NARROW_GAP_EXT_FACE_FL_MASK (NARROW_GAP_EXT_BLOCKED_FACE_FL | NARROW_GAP_EXT_MODELED_FACE_FL)
#define BLOCKED_NARROW_GAP_CELL_P(_c,_t)     (C_ENTITY_FLAGS (_c, _t) & NARROW_GAP_BLOCKED_CELL_FL)
#define BLOCKED_NARROW_GAP_CELL_OLD_P(_c,_t) (C_ENTITY_FLAGS (_c, _t) & NARROW_GAP_BLOCKED_CELL_FL_OLD)
#define BLOCKED_NARROW_GAP_ALL_FACE_P(_f,_t) (F_ENTITY_FLAGS (_f, _t) & NARROW_GAP_ALL_BLOCKED_FACE_FL)
#define BLOCKED_NARROW_GAP_EXT_FACE_P(_f,_t) (F_ENTITY_FLAGS (_f, _t) & NARROW_GAP_EXT_BLOCKED_FACE_FL)
#define BLOCKED_NARROW_GAP_INT_FACE_P(_f,_t) (BLOCKED_NARROW_GAP_ALL_FACE_P(_f,_t) && !BLOCKED_NARROW_GAP_EXT_FACE_P(_f,_t))

#define MODELED_NARROW_GAP_CELL_P(_c,_t)     (C_ENTITY_FLAGS (_c, _t) & NARROW_GAP_MODELED_CELL_FL)
#define MODELED_NARROW_GAP_CELL_OLD_P(_c,_t) (C_ENTITY_FLAGS (_c, _t) & NARROW_GAP_MODELED_CELL_FL_OLD)
#define MODELED_NARROW_GAP_ALL_FACE_P(_f,_t) (F_ENTITY_FLAGS (_f, _t) & NARROW_GAP_ALL_MODELED_FACE_FL)
#define MODELED_NARROW_GAP_EXT_FACE_P(_f,_t) (F_ENTITY_FLAGS (_f, _t) & NARROW_GAP_EXT_MODELED_FACE_FL)
#define MODELED_NARROW_GAP_INT_FACE_P(_f,_t) (MODELED_NARROW_GAP_ALL_FACE_P(_f,_t) && !MODELED_NARROW_GAP_EXT_FACE_P(_f,_t))

#define NARROW_GAP_CELL_P(_c,_t)               (BLOCKED_NARROW_GAP_CELL_P((_c), (_t)) || MODELED_NARROW_GAP_CELL_P((_c), (_t)))
#define NARROW_GAP_ALL_FACE_P(_f,_t)          ((F_ENTITY_FLAGS (_f, _t) & (NARROW_GAP_ALL_FACE_FL_MASK)) == NARROW_GAP_ALL_FACE_FL_MASK)
#define NARROW_GAP_EXT_FACE_P(_f,_t)          ((F_ENTITY_FLAGS (_f, _t) & (NARROW_GAP_EXT_FACE_FL_MASK)) == NARROW_GAP_EXT_FACE_FL_MASK)
#define NARROW_GAP_INT_FACE_P(_f,_t)          (BLOCKED_NARROW_GAP_INT_FACE_P(_f,_t) || MODELED_NARROW_GAP_INT_FACE_P(_f,_t))

FLUENT_EXPORT extern cxboolean gap_blocking_active_p;
FLUENT_EXPORT extern cxboolean gap_blocking_active_old_p;
FLUENT_EXPORT extern cxboolean gap_modeling_active_p;
FLUENT_EXPORT extern cxboolean gap_modeling_active_old_p;
#define SKIP_NARROW_GAP_CELL_P(_c,_t)         (gap_blocking_active_p ? BLOCKED_NARROW_GAP_CELL_P(_c,_t) : 0)
#define SOLVE_NARROW_GAP_CELL_P(_c,_t)        (gap_blocking_active_p ? !BLOCKED_NARROW_GAP_CELL_P(_c,_t): 1)
#define SKIP_NARROW_GAP_FACE_P(_f,_t)         (gap_blocking_active_p ? BLOCKED_NARROW_GAP_ALL_FACE_P(_f,_t) : 0)
#define SOLVE_NARROW_GAP_FACE_P(_f,_t)        (gap_blocking_active_p ? !BLOCKED_NARROW_GAP_ALL_FACE_P(_f,_t): 1)

#define FSP_TYPE(_e) FACE_TYPE(_e)
#define F_TYPE(_f,_t) FSP_TYPE(F_FACE(_f,_t))

#define SET_FSP_TYPE(_e, _n) SET_ENTITY_TYPE(_e, _n)
#define SET_F_TYPE(_f,_t,_n) SET_FSP_TYPE(F_FACE(_f,_t),_n)

/* face struct macros */
#define F_FACE(_f,_t)   FAST_F_STORAGE(_f, _t, SV_FACE, Face **)

#define FSP_ENTITY_KIND(_s) ENTITY_KIND(_s)
#define FSP_ENTITY_FLAGS(_s) ENTITY_FLAGS(_s)
#define SET_FSP_ENTITY_FLAGS(_s, _mask) SET_ENTITY_FLAGS(_s, _mask)
#define CLEAR_FSP_ENTITY_FLAGS(_s, _mask) CLEAR_ENTITY_FLAGS(_s, _mask)
#define FSP_ENTITY_FLAG(_s, _mask) ENTITY_FLAG(_s, _mask)
#define FSP_ID(_s)     ENTITY_ID1(_s)
#define FSP_IDX(_e)    ENTITY_SV_IDX(_e)
#define FSP_THREAD(_e) ENTITY_THREAD2(_e)

#define F_ENTITY_KIND(_f,_t) FSP_ENTITY_KIND(F_FACE(_f, _t))
#define F_ENTITY_FLAGS(_f,_t) FSP_ENTITY_FLAGS(F_FACE(_f, _t))
#define SET_F_ENTITY_FLAGS(_f,_t,_flags) SET_FSP_ENTITY_FLAGS(F_FACE(_f,_t),_flags)
#define CLEAR_F_ENTITY_FLAGS(_f,_t,_flags) CLEAR_FSP_ENTITY_FLAGS(F_FACE(_f,_t),_flags)
#define F_ENTITY_FLAG(_f,_t,_flags) FSP_ENTITY_FLAG(F_FACE(_f,_t),_flags)
#if CHECK_STRUCT_MACROS
# if PARALLEL
#  define F_ID(_f,_t) FSP_ID(F_FACE(_f, FACE_THREAD_P(_t) ? _t : NULL))
# else
#  define F_ID(_f,_t)((cxindex)FSP_ID(F_FACE(_f, FACE_THREAD_P(_t) ? _t : NULL)))
# endif
#else
# if 1 /*PARALLEL*/
#  define F_ID(_f,_t) FSP_ID(F_FACE(_f, _t))
# else
#  define F_ID(_f,_t) ((cxindex)FSP_ID(F_FACE(_f, _t)))
# endif
#endif
#define F_IDX(_f,_t) FSP_IDX(F_FACE(_f, _t))
#define F_THREAD(_f,_t) FSP_THREAD(F_FACE(_f, _t))

#if RP_POLYHEDRA
# define FSP_NNODES(_e) FACE_NNODES(_e)
# define F_NNODES(_f,_t) FSP_NNODES(F_FACE(_f,_t))
# define FSP_NODES(_s) FACE_NODES(_s)
# define F_NODES(_f,_t) FSP_NODES(F_FACE (_f,_t))

# define SET_FSP_NNODES(_e, _nn) SET_FACE_NNODES(_e, _nn)
# define SET_F_NNODES(_f,_t,_nn) SET_FSP_NNODES(F_FACE(_f,_t), _nn)

# define FSP_CELLS(_s) F_NEIGH(_s)
# define FSP_C0_CELL(_s) LEFT_F_NEIGHBOR(_s)
# define FSP_C1_CELL(_s) RIGHT_F_NEIGHBOR(_s)
# define F_CELLS(_f,_t) FSP_CELLS(F_FACE(_f,_t))
# define F_C0_CELL(_f,_t) FSP_C0_CELL(F_FACE(_f, _t))
# define F_C1_CELL(_f,_t) FSP_C1_CELL(F_FACE(_f, _t))
#else
# define F_NNODES(_f, _t) F_TYPE(_f, _t)
# define FSP_NNODES(_e) FSP_TYPE(_e)
# define FSP_NODES(_s) FACE_NODES(_s)
# define FSP_C0_CELL(_s) LEFT_F_NEIGHBOR(_s)
# define FSP_C1_CELL(_s) RIGHT_F_NEIGHBOR(_s)

# define SET_F_NNODES(_f,_t,_nn)   (F_NNODES(_f,_t) = _nn)
# define SET_FSP_NNODES(_f, _nn) (FSP_NNODES(_f) = _nn)
# define F_NODES(_f,_t) FSP_NODES(F_FACE(_f,_t))
# define F_C0_CELL(_f,_t) FSP_C0_CELL(F_FACE(_f,_t))
# define F_C1_CELL(_f,_t) FSP_C1_CELL(F_FACE(_f,_t))
#endif
#define F_NODE(_f,_t,_i) (F_NODES(_f, _t)[_i])
#define FSP_NODE(_fsp,_i) (FSP_NODES(_fsp)[_i])
#define F_C0_THREAD_DIRECT(_f,_t) CSP_THREAD (F_C0_CELL (_f,_t))
#define F_C1_THREAD_DIRECT(_f,_t) CSP_THREAD (F_C1_CELL (_f,_t))
#define F_C0_THREAD_SAFE(_f,_t) \
  (NNULLP (F_C0_CELL (_f,_t)) ? CSP_THREAD (F_C0_CELL (_f,_t)) : NULL)
#define F_C1_THREAD_SAFE(_f,_t) \
  (NNULLP (F_C1_CELL (_f,_t)) ? CSP_THREAD (F_C1_CELL (_f,_t)) : NULL)
#define F_C0_THREAD(_f,_t) \
  (SV_C0_THREAD_P (_t) ? F_C0_THREAD_SAFE (_f, _t) : THREAD_T0 (_t))
#define F_C1_THREAD(_f,_t) \
  (SV_C1_THREAD_P (_t) ? F_C1_THREAD_SAFE (_f, _t) : THREAD_T1 (_t))
#define SET_F_C0_CELL(_f,_tf,_c,_tc) \
  (F_C0_CELL (_f, _tf) = (!NULL_CELL_P (_c) && NNULLP (_tc)) ? C_CELL (_c, _tc) : NULL)
#define CLEAR_F_C0_CELL(_f,_tf) (F_C0_CELL (_f, _tf) = NULL)
#define SET_F_C1_CELL(_f,_tf,_c,_tc) \
  (F_C1_CELL (_f, _tf) = (!NULL_CELL_P (_c) && NNULLP (_tc)) ? C_CELL (_c, _tc) : NULL)
#define CLEAR_F_C1_CELL(_f,_tf) (F_C1_CELL (_f, _tf) = NULL)

#define CONTACT_ZONE_FACE0_P(_f,_t) \
  (F_ENTITY_FLAGS (_f, _t) & NARROW_GAP_ALL_BLOCKED_FACE_FL)
#define CONTACT_ZONE_FACE1_P(_f,_t) \
  (F_ENTITY_FLAGS (_f, _t) & NARROW_GAP_EXT_BLOCKED_FACE_FL)

#define CONTACT_ZONE_SOLVE_FACE_P(_f,_t) \
  (contact_active_p?!CONTACT_ZONE_FACE0_P(_f,_t):1)

#define CONTACT_ZONE_INTERFACE_FACE_P(c0,t0,c1,t1)\
    (( CONTACT_ZONE_CELL_P(c0,t0) && !CONTACT_ZONE_CELL_P(c1,t1)) ||\
     (!CONTACT_ZONE_CELL_P(c0,t0) &&  CONTACT_ZONE_CELL_P(c1,t1)) )

#define C_FACE_THREAD_PHASE(c,t,i,phase) \
  (THREAD_SUB_THREAD (C_FACE_THREAD (c, t, i), phase))
#define C_FACE_THREAD_MD(c,t,i) \
  (ROOT_DOMAIN_P (THREAD_DOMAIN (t)) ? C_FACE_THREAD (c, t, i) : \
   C_FACE_THREAD_PHASE (c, t, i, DOMAIN_INDEX (THREAD_DOMAIN (t))))

#if RP_POLYHEDRA
# define F_EDGES(f,t)(  FAST_F_STORAGE(f,t,SV_CR_EDGE,struct edge_struct ***))
# define F_EDGE(f,t,i)(F_EDGES(f,t)[i])
#else
# define F_EDGE(f,t,i)(  F_STORAGE(f,t,SV_EDGE,struct edge_struct *(*)[MAX_EDGES_PER_FACE])[i])
#endif

#define C_FACE_NEIGHBOR(c,t,i)(  C_STORAGE(c,t,SV_C_FACE_NEIGHBOR,face_t (*)[MAX_FACES_PER_CELL])[i])
#define C_FACE_THREAD_NEIGHBOR(c,t,i)(  C_STORAGE(c,t,SV_C_FACE_THREAD_NEIGHBOR,Thread *(*)[MAX_FACES_PER_CELL])[i])

#define NULL_FACE (~0)
#define NULL_FACE_P(f)((f) == NULL_FACE)
#define NULL_CELL NULL_FACE
#define NULL_CELL_P NULL_FACE_P

extern FLUENT_EXPORT const int cell_type_nnodes[];
extern FLUENT_EXPORT const int cell_type_nfaces[];

#define C_HAS_TYPE_P(_c,_t,_type) ((Cell_Element_Type)C_TYPE (_c, _t) == _type)
#define CSP_HAS_TYPE_P(_csp,_type) ((Cell_Element_Type)CSP_TYPE (_csp) == _type)
#define F_HAS_TYPE_P(_f,_t,_type) ((Face_Element_Type)F_TYPE (_f, _t) == _type)
#define FSP_HAS_TYPE_P(_fsp,_type) ((Face_Element_Type)FSP_TYPE (_fsp) == _type)

#define C0_HAS_TYPE(f,t,type) \
  ((!NULL_CELL_P (F_C0 (f, t))) && \
   C_HAS_TYPE_P (F_C0 (f, t), F_C0_THREAD (f, t), type))
#define C1_HAS_TYPE(f,t,type) \
  ((!NULL_CELL_P (F_C1 (f, t))) && \
   C_HAS_TYPE_P (F_C1 (f, t), F_C1_THREAD (f, t), type))
#define C0_OR_C1_HAS_TYPE(f,t,type) \
  (C0_HAS_TYPE (f, t, type) || C1_HAS_TYPE (f, t, type))
#define C0_AND_C1_HAVE_TYPE(f,t,type) \
  (C0_HAS_TYPE (f, t, type) && C1_HAS_TYPE (f, t, type))

#if RP_POLYHEDRA
# define F_NEDGES(f,t) F_NNODES(f,t)
# define SET_F_NEDGES(f,t,n) SET_F_NNODES(f,t,n)
#else
# define F_NEDGES(f,t) Face_Type_Nedges(F_TYPE(f,t))
# define SET_F_NEDGES(f,t,n) (Face_Type_Nedges(F_TYPE(f,t) = n)
#endif

#if RP_POLYHEDRA

#ifndef C_NODE_WTS
#define C_NODE_WTS(c,t,type)(C_STORAGE(c,t,SV_CR_NODE_##type,real **))
#endif
#ifndef F_NODE_WTS
#define F_NODE_WTS(f,t,type)(F_STORAGE(f,t,SV_CR_NODE_##type,real **))
#endif

#define ALLOC_C_NODE_WT(c,t)                                                                  \
  {                                                                                           \
        if (SV_ALLOCATED_P(t, SV_CR_NODE_WT)    &&    THREAD_NODE_WT(t))                      \
          C_NODE_WTS(c,t,WT)    = (real *)Get_Memory (THREAD_NODE_WT(t),    C_NNODES (c, t)); \
        if (SV_ALLOCATED_P(t, SV_CR_NODE_WT_GX) &&    THREAD_NODE_WT_GX(t))                   \
          C_NODE_WTS(c,t,WT_GX) = (real *)Get_Memory (THREAD_NODE_WT_GX(t), C_NNODES (c, t)); \
        if (SV_ALLOCATED_P(t, SV_CR_NODE_WT_GY) &&    THREAD_NODE_WT_GY(t))                   \
          C_NODE_WTS(c,t,WT_GY) = (real *)Get_Memory (THREAD_NODE_WT_GY(t), C_NNODES (c, t)); \
        if (SV_ALLOCATED_P(t, SV_CR_NODE_WT_GZ) &&    THREAD_NODE_WT_GZ(t))                   \
          C_NODE_WTS(c,t,WT_GZ) = (real *)Get_Memory (THREAD_NODE_WT_GZ(t), C_NNODES (c, t)); \
  }
#define ALLOC_F_NODE_WT(f,t)                                                                  \
  {                                                                                           \
        if (SV_ALLOCATED_P(t, SV_CR_NODE_WT)    &&    THREAD_NODE_WT(t))                      \
          F_NODE_WTS(f,t,WT)    = (real *)Get_Memory (THREAD_NODE_WT(t),    F_NNODES (f, t)); \
        if (SV_ALLOCATED_P(t, SV_CR_NODE_WT_GX) &&    THREAD_NODE_WT_GX(t))                   \
          F_NODE_WTS(f,t,WT_GX) = (real *)Get_Memory (THREAD_NODE_WT_GX(t), F_NNODES (f, t)); \
        if (SV_ALLOCATED_P(t, SV_CR_NODE_WT_GY) &&    THREAD_NODE_WT_GY(t))                   \
          F_NODE_WTS(f,t,WT_GY) = (real *)Get_Memory (THREAD_NODE_WT_GY(t), F_NNODES (f, t)); \
        if (SV_ALLOCATED_P(t, SV_CR_NODE_WT_GZ) &&    THREAD_NODE_WT_GZ(t))                   \
          F_NODE_WTS(f,t,WT_GZ) = (real *)Get_Memory (THREAD_NODE_WT_GZ(t), F_NNODES (f, t)); \
  }

#define ALLOC_THREAD_EDGE_STORAGE(_t)                                      \
  {                                                                        \
    Domain *_d = THREAD_DOMAIN (_t);                                       \
    register int _n;                                                       \
    face_t _face;                                                          \
                                                                           \
    if (NULLP (FACE_EDGE_MEM (_d)))                                        \
      FACE_EDGE_MEM (_d) =                                                 \
        Create_Memory_Manager (Get_Size_Item_Per_Element (_t, 2)*          \
                               THREAD_N_ELEMENTS (_t), sizeof (Edge *));   \
    begin_f_loop_all (_face, _t)                                           \
      {                                                                    \
        if (NULLP (F_EDGES (_face, _t)))                                   \
          F_EDGES (_face, _t) =                                            \
            (Edge **)Get_Memory (FACE_EDGE_MEM (_d),                       \
                                 F_NEDGES (_face, _t));                    \
        intloop (_n, F_NEDGES (_face, _t))                                 \
          F_EDGE (_face, _t, _n) = NULL;                                   \
      }                                                                    \
    end_f_loop_all (_face, _t)                                             \
  }

#define ALLOC_DOMAIN_EDGE_STORAGE(_d)                                      \
  {                                                                        \
    register int _nt;                                                      \
    Thread *_t;                                                            \
                                                                           \
    if (NULLP (FACE_EDGE_MEM (_d)))                                        \
      FACE_EDGE_MEM (_d) =                                                 \
        Create_Memory_Manager (Get_Size_Storage_Domain (_d, FALSE, 2),     \
                               sizeof (Edge *));                           \
    thread_loop_all_f (_t, _d, _nt)                                        \
      ALLOC_THREAD_EDGE_STORAGE (_t);                                      \
  }

#define NULLIFY_THREAD_EDGE_STORAGE(_t)                                    \
  {                                                                        \
    register int _n;                                                       \
    face_t _face;                                                          \
                                                                           \
    begin_f_loop_all (_face, _t)                                           \
      {                                                                    \
        if (SV_ALLOCATED_P (_t, SV_CR_EDGE) &&                             \
            NNULLP (F_EDGES (_face, _t)))                                  \
          {                                                                \
            intloop (_n, F_NEDGES (_face, _t))                             \
              F_EDGE (_face, _t, _n) = NULL;                               \
            F_EDGES (_face, _t) = NULL;                                    \
          }                                                                \
      }                                                                    \
    end_f_loop_all (_face, _t)                                             \
  }

#define FREE_DOMAIN_EDGE_STORAGE(_d)                                       \
  {                                                                        \
    register int _nt ;                                                     \
    Thread *_t;                                                            \
                                                                           \
    thread_loop_all_f (_t, _d, _nt)                                        \
      NULLIFY_THREAD_EDGE_STORAGE(_t)                                      \
                                                                           \
    if (NNULLP (FACE_EDGE_MEM (_d)))                                       \
      Free_Memory_Manager (&FACE_EDGE_MEM (_d));                           \
  }

# define SET_C_NODE_WT(c, t, type) \
  C_NODE_WTS(c,t,type) = (real *)Get_Memory (THREAD_NODE_##type(t), C_NNODES (c, t))

# define ALLOC_THREAD_NODE_WT(t,type)                                      \
  {                                                                        \
    int node_cnt = 0;                                                      \
    if (CELL_THREAD_P(t))                                                  \
      {                                                                    \
        cell_t c = NULL_CELL;                                              \
        begin_c_loop_all(c, thread)                                        \
          node_cnt += C_NNODES(c, thread);                                 \
        end_c_loop_all(c, thread)                                          \
      }                                                                    \
    else                                                                   \
      {                                                                    \
        face_t f = NULL_FACE;                                              \
        begin_f_loop_all(f, thread)                                        \
          node_cnt += F_NNODES(f, thread);                                 \
        end_f_loop_all(f, thread)                                          \
      }                                                                    \
                                                                           \
    if (NULLP(THREAD_NODE_##type(t)))                                      \
      THREAD_NODE_##type(t) =                                              \
      Create_Memory_Manager(node_cnt, sizeof(real));                       \
    if (CELL_THREAD_P(t))                                                  \
      {                                                                    \
        register cell_t _c;                                                \
                                                                           \
        begin_c_loop_int_ext(_c, t)                                        \
          SET_C_NODE_WT(_c, t, type);                                      \
        end_c_loop_int_ext(_c, t)                                          \
      }                                                                    \
    else                                                                   \
      {                                                                    \
        register face_t _f;                                                \
                                                                           \
        begin_f_loop_all(_f, t)                                            \
          F_NODE_WTS(_f,t,type) =                                          \
            (real *)Get_Memory(THREAD_NODE_##type(t), F_NNODES(_f, t));    \
        end_f_loop_all(_f, t)                                              \
      }                                                                    \
  }

# define FREE_THREAD_NODE_WT(t,type)               \
   if (NNULLP (THREAD_NODE_##type (t)))            \
     Free_Memory_Manager (&THREAD_NODE_##type (t))
#endif /* RP_POLYHEDRA */

#define F_INTERIOR(f,t)  F_STORAGE(f,t,SV_F_INTERIOR,uchar_fl *)
#define C_STATUS(c,t)  FAST_C_STORAGE(c,t,SV_STATUS,uchar_fl *)
#define SET_C_STATUS(c,t,s)C_STATUS(c,t) = (uchar_fl)(s)
#define F_STATUS(e,t) C_STATUS(e,t)
#define SET_F_STATUS(e,t,s) SET_C_STATUS(e,t,s)
#define SET_F_SHADOW_STATUS(f,t,s) \
        SET_C_STATUS(F_SHADOW(f,t),THREAD_SHADOW(t),s)

#define F_STATE(f,t)  FAST_F_STORAGE(f,t,SV_STATE,int *)
#define C_STATE(c,t)  FAST_C_STORAGE(c,t,SV_STATE,int *)

#define C_TREE_LEVEL(c,t)  C_STORAGE(c,t,SV_TREE_LEVEL,uchar_fl *)
#define SET_C_TREE_LEVEL(c,t,s)C_TREE_LEVEL(c,t) = (uchar_fl)(s)
#define C_OF_TREE_LEVEL_P(c,t,s)(C_TREE_LEVEL(c,t) == (uchar_fl)(s))

#define CSP_CENTROID_CACHE(csp) C_CENTROID_CACHE(CSP_IDX(csp), CSP_THREAD(csp))
#define C_CENTROID_CACHE(c,t)  FAST_C_STORAGE_R_NV(c,t,SV_CENTROID)
#define C_CENTROID_COMP(c,t)  C_STORAGE_R(c,t,SV_CENTROID_COMP)

#define C_CHILDREN(c,t)  FAST_C_STORAGE(c,t,SV_CHILD,int (*)[MAX_KIDS_PER_CELL])
#if 0
#define C_CHILDREN_INDEX(c,t)  C_STORAGE(c,t,SV_CHILD_INDEX,cxindex (*)[MAX_KIDS_PER_CELL])
#else
#if WIN64
#define C_CHILDREN_INDEX(c,t)  FAST_C_STORAGE(c,t,SV_CHILD_THREAD,long long (*)[MAX_KIDS_PER_CELL])
#else
#define C_CHILDREN_INDEX(c,t)  FAST_C_STORAGE(c,t,SV_CHILD_THREAD,cxindex (*)[MAX_KIDS_PER_CELL])
#endif
#endif
#define C_CHILDREN_THREADS(c,t)  FAST_C_STORAGE(c,t,SV_CHILD_THREAD,Thread *(*)[MAX_KIDS_PER_CELL])
#define C_CHILD(c,t,i)(C_CHILDREN(c,t)[i])

#define C_CHILD_THREAD(c,t,i)(C_CHILDREN_THREADS(c,t)[i])

#if USE_INT64
#define C_CHILD_INDEX(c,t,i)(C_CHILDREN_INDEX(c,t)[i])
#else
#define C_CHILD_INDEX(c,t,i)(C_CHILD(c,t,i))
#endif

#define C_INTERIOR_THREAD(c,t)  C_STORAGE(c,t,SV_INTERIOR_THREAD,Thread *(*))

#define C_PARENT(c,t)  FAST_C_STORAGE(c,t,SV_C_PARENT,cell_t *)
#define C_PARENT_THREAD(c,t)THREAD_PARENT(t)
#define F_PARENT(f,t)  FAST_F_STORAGE(f,t,SV_F_PARENT,face_t *)
#define F_PARENT_THREAD(f,t)THREAD_PARENT(t)

/* Laplace group */
#define C_LAPLACE_GRP_STORAGE(c,t)  C_STORAGE_INDEX(c,t,SV_LAPLACE_GROUP)

/* partition */
#define C_PART_STORAGE(c,t)  FAST_C_STORAGE_INDEX(c,t,SV_PARTITION)

#if USE_INT64
#define GET_I_PART(i) ((i)&0x00000000ffffffff)
#define SET_I_PART(i,p) i = ((i)&0xffffffff00000000) | ((cxindex)(p))
#define GET_I_PART_S(i) ((i)>>32)
#define SET_I_PART_S(i,p) i = ((i)&0x00000000ffffffff) | (((cxindex)(p))<<32)
#else
#define GET_I_PART(i) ((i)&0x0000ffff)
#define SET_I_PART(i,p) i = ((i)&0xffff0000) | (p)
#define GET_I_PART_S(i) ((i)>>16)
#define SET_I_PART_S(i,p) i = ((i)&0x0000ffff) | ((p)<<16)
#endif

#define C_PART_ACTIVE(c,t) (GET_I_PART(C_PART_STORAGE(c,t)))
#define SET_C_PART_ACTIVE(c,t,p) SET_I_PART(C_PART_STORAGE(c,t),p)
#define C_PART_STORED(c,t) (GET_I_PART_S(C_PART_STORAGE(c,t)))
#define SET_C_PART_STORED(c,t,p) SET_I_PART_S(C_PART_STORAGE(c,t),p)
#if RP_NODE
# define F_PART(f,t)  FAST_F_STORAGE_INDEX(f,t,SV_PARTITION)
#endif

/* Note: the final cast makes this an invalid lvalue so C_*_SET
 * and C_*_CLEAR can't be inadvertently circumvented with a
 * simple assignment statement */

#define C_STORAGE_BIT_GET(c,t,sv)\
  ((int)(C_STORAGE((c)/8,(t),sv,unsigned char *) & (1<<((c)%8))))

#define C_STORAGE_BIT_SET(c,t,sv)\
  C_STORAGE((c)/8,(t),sv,unsigned char *) |=  (1<<((c)%8))

#define C_STORAGE_BIT_CLEAR(c,t,sv)\
  C_STORAGE((c)/8,(t),sv,unsigned char *) &= ~(1<<((c)%8))

#define FAST_C_STORAGE_BIT_GET(c,t,sv)\
  ((int)(FAST_C_STORAGE((c)/8,(t),sv,unsigned char *) & (1<<((c)%8))))

#define FAST_C_STORAGE_BIT_SET(c,t,sv)\
  FAST_C_STORAGE((c)/8,(t),sv,unsigned char *) |=  (1<<((c)%8))

#define FAST_C_STORAGE_BIT_CLEAR(c,t,sv)\
  FAST_C_STORAGE((c)/8,(t),sv,unsigned char *) &= ~(1<<((c)%8))

#define C_TMP0(c,t)  C_STORAGE_R(c,t,SV_RTMP_0)
#define C_TMP_C0(c,t)  FAST_C_STORAGE_R(c,t,SV_C_TMP_0)

#define C_TMP1(c,t)  C_STORAGE_R(c,t,SV_RTMP_1)
#define C_TMP2(c,t)  C_STORAGE_R(c,t,SV_RTMP_2)
#define C_TMP3(c,t)  C_STORAGE_R(c,t,SV_RTMP_3)
#define C_TMP4(c,t)  C_STORAGE_R(c,t,SV_RTMP_4)
#define C_TMP5(c,t)  C_STORAGE_R(c,t,SV_RTMP_5)
#define C_TMP6(c,t)  C_STORAGE_R(c,t,SV_RTMP_6)
#define C_TMP7(c,t)  C_STORAGE_R(c,t,SV_RTMP_7)
#define C_TMP8(c,t)  FAST_C_STORAGE_R(c,t,SV_RTMP_8)
#define C_TMP9(c,t)  FAST_C_STORAGE_R(c,t,SV_RTMP_9)

#define F_COEFF(f,t)  F_STORAGE_R(f,t,SV_F_COEFF)

/* used by Broadband noise optimization */
#define C_SNGR_SELF(c,t)  C_STORAGE_R(c,t,SV_SNGR_SELF)
#define C_SNGR_SHEAR(c,t)  C_STORAGE_R(c,t,SV_SNGR_SHEAR)
#define C_SNGR_TOTAL(c,t)  C_STORAGE_R(c,t,SV_SNGR_TOTAL)
#define C_SNGR_SELF_Y(c,t)  C_STORAGE_R(c,t,SV_SNGR_SELF_Y)
#define C_SNGR_SHEAR_Y(c,t)  C_STORAGE_R(c,t,SV_SNGR_SHEAR_Y)
#define C_SNGR_TOTAL_Y(c,t)  C_STORAGE_R(c,t,SV_SNGR_TOTAL_Y)
#if RP_3D
#define C_SNGR_SELF_Z(c,t)  C_STORAGE_R(c,t,SV_SNGR_SELF_Z)
#define C_SNGR_SHEAR_Z(c,t)  C_STORAGE_R(c,t,SV_SNGR_SHEAR_Z)
#define C_SNGR_TOTAL_Z(c,t)  C_STORAGE_R(c,t,SV_SNGR_TOTAL_Z)
#endif

#define C_VIS1(c,t)  FAST_C_STORAGE_R(c,t,SV_VIS_1)

/* used by Broadband noise optimization */
#define C_VIS2(c,t)  FAST_C_STORAGE_R(c,t,SV_VIS_2)
#define C_VIS3(c,t)  FAST_C_STORAGE_R(c,t,SV_VIS_3)
#define C_VIS4(c,t)  C_STORAGE_R(c,t,SV_VIS_4)
#define C_VIS5(c,t)  C_STORAGE_R(c,t,SV_VIS_5)
#define C_VIS6(c,t)  C_STORAGE_R(c,t,SV_VIS_6)
#if RP_3D
#define C_VIS7(c,t)  C_STORAGE_R(c,t,SV_VIS_7)
#define C_VIS8(c,t)  C_STORAGE_R(c,t,SV_VIS_8)
#define C_VIS9(c,t)  C_STORAGE_R(c,t,SV_VIS_9)
#endif

#define C_ITMP0(c,t)  FAST_C_STORAGE_I(c,t,SV_ITMP_0)
#define C_ITMP1(c,t)  FAST_C_STORAGE_I(c,t,SV_ITMP_1)
#define C_ID_TMP(_c,_t)  FAST_C_STORAGE_INDEX(_c,_t,SV_ID_TMP)
#define F_ID_TMP(_f,_t)  FAST_F_STORAGE_INDEX(_f,_t,SV_ID_TMP)
#define C_ID_SC(_c,_t)  C_STORAGE_INDEX(_c,_t,SV_ID_SC)
#define F_ID_SC(_f,_t)  F_STORAGE_INDEX(_f,_t,SV_ID_SC)

#define C_ISO_MARK(c,t)  FAST_C_STORAGE_I(c,t,SV_ISO_MARK)

#define C_BTMP0(c,t)  FAST_C_STORAGE_I(c,t,SV_ITMP_0)

#define C_INTERFACE_INFO(c,t)  C_STORAGE_I(c,t,SV_INTERFACE_INFO)
#define C_CLUSTER(c,t)  FAST_C_STORAGE_I(c,t,SV_CLUSTER)
#define C_NEXT_IN_CLUSTER(c,t)  FAST_C_STORAGE_I(c,t,SV_NEXT_IN_CLUSTER)
#define C_DEGREE(c,t)  C_STORAGE_I(c,t,SV_DEGREE)
#define C_ECCENTRICITY(c,t)  C_STORAGE_I(c,t,SV_ECCENTRICITY)
#define C_DIST(c,t)  C_STORAGE_I(c,t,SV_DIST)
#define C_LEVEL(c,t)  C_STORAGE_I(c,t,SV_LEVEL)
#define C_METIS(c,t)  C_STORAGE_I(c,t,SV_METIS)
#define C_NUMKIDS(c,t)  C_STORAGE_I(c,t,SV_NUMKIDS)
#define C_PART_OWNER(c,t)  FAST_C_STORAGE_I(c,t,SV_PARTITION_OWNER)
#define C_PART_CACHE(c,t)  C_STORAGE_I(c,t,SV_PARTITION_CACHE)
#define C_WEIGHT(c,t)  FAST_C_STORAGE_I(c,t,SV_C_WEIGHT)
#define F_WEIGHT(e,t)  C_WEIGHT(e,t)

#define C_TMP(c,t)   C_TMP0(c,t)

#define C_LAYER(c,t)  C_STORAGE_I(c,t,SV_LAYER)
#define F_LAYER(f,t)  F_STORAGE_I(f,t,SV_F_LAYER)

#define C_INDEX(c,t)  FAST_C_STORAGE_I(c,t,SV_C_INDEX)

#define C_PART_DEST(c,t)  FAST_C_STORAGE_I(c,t,SV_PARTITION_DEST)
#define F_PART_DEST(e,t) C_PART_DEST(e,t)
#define SM_DEST 0xffffffff /* need a marker? */

#define C_NRMDIST(c,t)  C_STORAGE_R(c,t,SV_C_NRMDIST)
#define C_EQLENSQ(c,t)  C_STORAGE_R(c,t,SV_C_EQLENSQ)
#define C_SPONGE_DIST(c,t) C_STORAGE_R(c,t,SV_C_SPONGE_DIST)

#define CSP_VOLUME(csp) C_VOLUME(CSP_IDX(csp), CSP_THREAD(csp))
#define C_VOLUME(c,t)  FAST_C_STORAGE_R(c,t,SV_VOLUME)
#if RP_AXI
# define C_VOLUME_2D(c,t)  C_STORAGE_R(c,t,SV_VOLUME_2D)
#else
# define C_VOLUME_2D(c,t) C_VOLUME(c,t)
#endif

/* for alternate time-step impl. */
#define C_ARATIO(c,t)   FAST_C_STORAGE_R(c,t,SV_ARATIO)
#define C_MINDIST(c,t)  FAST_C_STORAGE_R(c,t,SV_CMIN_DIST)

#define F_PROFILE(f,t,n)F_STORAGE_R(f,t, (Svar)(SV_PROFILE_0+(n)))
#define C_PROFILE(e,t,n) F_PROFILE(e,t,n)
#define C_PROFILE_S(c,t,n) C_STORAGE_R(c,t, (Svar)(SV_PROFILE_0+(n)))

#define USE_OPTIONAL_ROUGHNESS_MODEL(M_optional_roughness_model,t)\
{\
  if (!rp_rough_wall)\
    M_optional_roughness_model = FALSE;\
  else\
    {\
      if (THREAD_VAR(t).wall.rough_bc == ROUGH_BC_STANDARD)\
        M_optional_roughness_model = FALSE;\
      else\
        M_optional_roughness_model = TRUE;\
    }\
}

#define FREE_OPTIONAL_ROUGHNESS_MODEL(M_optional_roughness_model,t)\
{\
    M_optional_roughness_model = FALSE;\
}

#define F_WALL_KS(f,t) (!M_optional_roughness_model?  F_VAR(f,t,THREAD_VAR(t).wall.ks) :     \
                        ((sg_mphase && DOMAIN_N_DOMAINS(THREAD_DOMAIN(t)) == 0)?             \
                            FAST_F_STORAGE_R(f,THREAD_SUPER_THREAD(t),SV_WALL_KS) :   FAST_F_STORAGE_R(f,t,SV_WALL_KS) ))
#define F_WALL_KCON(f,t) (!M_optional_roughness_model?  F_VAR(f,t,THREAD_VAR(t).wall.kcon) :     \
                        ((sg_mphase && DOMAIN_N_DOMAINS(THREAD_DOMAIN(t)) == 0 )?                \
                            FAST_F_STORAGE_R(f,THREAD_SUPER_THREAD(t),SV_WALL_KCON):   FAST_F_STORAGE_R(f,t,SV_WALL_KCON)))

#define F_SHADOW(f,t)  FAST_F_STORAGE(f,t,SV_SHADOW,face_t *)
#define F_SHADOW_THREAD(f,t)THREAD_SHADOW(t)
#define F_SHADOW_SAFE(f,t)(!SV_ALLOCATED_P(t,SV_SHADOW) ? NULL_FACE : F_SHADOW(f,t))

#if RP_SHELL
#define F_SHADOW_JUNCTION(f,t)  F_STORAGE(f,t,SV_SHADOW_JUNCTION,face_t *)
#define F_SHADOW_JUNCTION_THREAD(f,t)THREAD_SHADOW_JUNCTION(t)
#define SHELL_IO (RP_Get_Boolean("shell/new-method?") && RP_Get_Boolean("shell/zone-io?"))
#endif /* RP_SHELL */

#define F_C0(f,t)  FAST_F_STORAGE(f,t,SV_C0,cell_t *)
#define F_C1(f,t)  FAST_F_STORAGE(f,t,SV_C1,cell_t *)

#if USE_INT64
#define F_C0_INDEX(f,t)  FAST_F_STORAGE(f,t,SV_C0_INDEX,cxindex *)
#define F_C1_INDEX(f,t)  FAST_F_STORAGE(f,t,SV_C1_INDEX,cxindex *)
#define F_SHADOW_INDEX(f,t)  F_STORAGE(f,t,SV_SHADOW_INDEX,cxindex *)
#else
#define F_C0_INDEX(f,t)F_C0(f,t)
#define F_C1_INDEX(f,t)F_C1(f,t)
#define F_SHADOW_INDEX(f,t)F_SHADOW(f,t)
#endif

#define F_VIRTUAL(f,t)   F_STORAGE_I(f,t,SV_F_VIRTUAL)
#define F_NDUALS(f,t)   F_STORAGE(f,t,SV_F_NDUALS,uchar_fl *)
#define F_DUALS(f,t)   F_STORAGE(f,t,SV_F_DUAL,face_t **)
#define F_DUAL(f,t,i) F_DUALS(f,t)[i]
#define f_dual_loop(f,t,n) intloop(n,F_NDUALS(f,t))

/* These can be used on a per face basis, but are very redundant for
 * for most threads, only the parent threads storage these thread pointers
 */

#define SET_F_C0_THREAD(_f,_t,_tt) \
  do {                                   \
    if (!SV_C0_THREAD_P (_t))            \
      SET_THREAD_T0 (_t, _tt);           \
    else                                 \
      SET_THREAD_T0 (_t, NULL);          \
    if (NNULLP (F_C0_CELL (_f, _t)))     \
      F_C0_THREAD_DIRECT (_f, _t) = _tt; \
  } while (0)
#define SET_F_C1_THREAD(_f,_t,_tt) \
  do {                                   \
    if (!SV_C1_THREAD_P (_t))            \
      SET_THREAD_T1 (_t, _tt);           \
    else                                 \
      SET_THREAD_T1 (_t, NULL);          \
    if (NNULLP (F_C1_CELL (_f, _t)))     \
      F_C1_THREAD_DIRECT (_f, _t) = _tt; \
  } while (0)

#define F_C_DIR(_f,_thread,_dir) \
  (((_dir) == 0) ? F_C0 (_f, _thread) : F_C1 (_f, _thread))
#define SET_F_C_DIR(_f,_thread,_dir,_c)         \
  {if (_dir == 0)             \
      F_C0 (_f, _thread) = _c;            \
    else                \
      F_C1 (_f, _thread) = _c;            \
  }

#define F_C_DIR_THREAD(_f,_thread,_dir) \
  (((_dir) == 0) ? F_C0_THREAD (_f, _thread) : F_C1_THREAD (_f, _thread))

#define F_STORAGE_BIT_GET(e,t,sv) C_STORAGE_BIT_GET(e,t,sv)
#define F_STORAGE_BIT_SET(e,t,sv) C_STORAGE_BIT_SET(e,t,sv)
#define F_STORAGE_BIT_CLEAR(e,t,sv) C_STORAGE_BIT_CLEAR(e,t,sv)
#define FAST_F_STORAGE_BIT_GET(e,t,sv) FAST_C_STORAGE_BIT_GET(e,t,sv)
#define FAST_F_STORAGE_BIT_SET(e,t,sv) FAST_C_STORAGE_BIT_SET(e,t,sv)
#define FAST_F_STORAGE_BIT_CLEAR(e,t,sv) FAST_C_STORAGE_BIT_CLEAR(e,t,sv)

#if RP_HANG
# define COLLECT_FACE_TO_C0_P(f,t)FAST_F_STORAGE_BIT_GET(f,t,SV_C0_COLLECT)
# define COLLECT_FACE_TO_C1_P(f,t)FAST_F_STORAGE_BIT_GET(f,t,SV_C1_COLLECT)
#else
# define COLLECT_FACE_TO_C0_P(f,t) 1
# define COLLECT_FACE_TO_C1_P(f,t) 1
#endif

#define COLLECT_FACE_TO_C0_SET(f,t) FAST_F_STORAGE_BIT_SET(f,t,SV_C0_COLLECT)
#define COLLECT_FACE_TO_C1_SET(f,t) FAST_F_STORAGE_BIT_SET(f,t,SV_C1_COLLECT)

#define COLLECT_FACE_TO_C0_CLEAR(f,t) FAST_F_STORAGE_BIT_CLEAR(f,t,SV_C0_COLLECT)
#define COLLECT_FACE_TO_C1_CLEAR(f,t) FAST_F_STORAGE_BIT_CLEAR(f,t,SV_C1_COLLECT)

#define C_HAS_PARENT_SET(c,t) C_STORAGE_BIT_SET(c,t,SV_HAS_PARENT_CELL)
#define C_HAS_PARENT_CLEAR(c,t)C_STORAGE_BIT_CLEAR(c,t,SV_HAS_PARENT_CELL)
#define C_HAS_PARENT(c,t) C_STORAGE_BIT_GET(c,t,SV_HAS_PARENT_CELL)

#define F_VISITED_SET(f,t)F_STORAGE_BIT_SET(f,t,SV_F_VISITED)
#define F_VISITED_CLEAR(f,t)F_STORAGE_BIT_CLEAR(f,t,SV_F_VISITED)
#define F_VISITED(f,t)F_STORAGE_BIT_GET(f,t,SV_F_VISITED)

#define C_VISITED_SET(c,t)FAST_C_STORAGE_BIT_SET(c,t,SV_C_VISITED)
#define C_VISITED_CLEAR(c,t)FAST_C_STORAGE_BIT_CLEAR(c,t,SV_C_VISITED)
#define C_VISITED(c,t)FAST_C_STORAGE_BIT_GET(c,t,SV_C_VISITED)

#define F_GLOB_ID(f,t)  F_STORAGE_I(f,t,SV_F_GLOB_ID)

#define F_SGLOB_ID(f,t)  F_STORAGE_I(f,t,SV_F_SGLOB_ID)
#define F_SGLOB_ID_MAP(f,t)  F_STORAGE_I(f,t,SV_F_SGLOB_ID_MAP)
#define VALID_GLOB_ID(id) ((id) >= 0)

# define F_PF0(f,t)  FAST_F_STORAGE(f,t,SV_SPF0,cxindex *)
# define F_PF1(f,t)  FAST_F_STORAGE(f,t,SV_SPF1,cxindex *)
# define F_PF0_THREAD(f,t)  FAST_F_STORAGE(f,t,SV_SPF0_THREAD,Thread **)
# define F_PF1_THREAD(f,t)  FAST_F_STORAGE(f,t,SV_SPF1_THREAD,Thread **)
# define F_SI_CHILDS(f,t)  FAST_F_STORAGE(f,t,SV_CHILDS,face_t **)
# define F_SI_CHILD_THREADS(f,t)(  FAST_F_STORAGE(f,t,SV_CHILD_THREADS,Thread ***))
# define F_SI_NCHILDS(f,t)  FAST_F_STORAGE_I(f,t,SV_NCHILDS)
# define F_SI_CHILD(f,t,i)(F_SI_CHILDS(f,t)[i])
# define F_SI_CHILD_THREAD(f,t,i)(F_SI_CHILD_THREADS(f,t)[i])

# define SET_F_PF0_INDEX(f,t,indx) ((F_PF0_THREAD(f,t)) = (Thread *)indx)
# define SET_F_PF1_INDEX(f,t,indx) ((F_PF1_THREAD(f,t)) = (Thread *)indx)
# define SET_F_SI_CHILD_INDEX(f,t,i,indx) ((F_SI_CHILD_THREAD(f,t,i)) = (Thread *)indx)
# define F_PF0_INDEX(f,t) ((cxindex)(F_PF0_THREAD(f,t)))
# define F_PF1_INDEX(f,t) ((cxindex)(F_PF1_THREAD(f,t)))
# define F_SI_CHILD_INDEX(f,t,i) ((cxindex)(F_SI_CHILD_THREAD(f,t,i)))

#define F_MAPPED_NFACES(f, t)   F_STORAGE_I(f,t,SV_N_MAPPED_FACES)
#define F_MAPPED_FACES(f,t)   F_STORAGE(f,t,SV_MAPPED_FACES,face_t **)
#define F_MAPPED_FACE_THREADS(f,t)(  F_STORAGE(f,t,SV_MAPPED_FACE_THREADS,Thread ***))
#define F_MAPPED_FACE(f,t,i) (F_MAPPED_FACES(f,t)[i])
#define F_MAPPED_FACE_THREAD(f,t,i)(F_MAPPED_FACE_THREADS(f,t)[i])
#define F_MAPPED_FACE_AREAS(f,t)   F_STORAGE(f,t,SV_MAPPED_FACE_AREAS,real **)
#define F_MAPPED_FACE_AREA(f,t,i) (F_MAPPED_FACE_AREAS(f,t)[i])
#define F_TOT_MAPPED_FACE_AREA(f,t)   F_STORAGE_R(f,t,SV_TOT_MAPPED_AREA)

#define F_NNODE_COORDS(f, t) F_STORAGE_I(f, t, SV_N_NODE_COORDS)
#define F_NODE_COORDS(f, t) F_STORAGE(f, t, SV_NODE_COORDS, real (**)[ND_ND])
#define F_NODE_COORD(f, t, i)  SV_ALLOCATED_P_NEW (t, SV_NODE_COORDS) ? F_NODE_COORDS(f, t)[i] : F_NODE_COORDS(f, THREAD_SHADOW(t))[i]
#define F_AREA_CACHE(f,t)  FAST_F_STORAGE(f,t,SV_AREA,real (*)[ND_ND])
#define FSP_AREA_CACHE(fsp) F_AREA_CACHE(FSP_IDX(fsp), FSP_THREAD(fsp))
#if RP_AXI
# define F_AREA_2D_CACHE(f,t)  F_STORAGE(f,t,SV_AREA_2D,real (*)[ND_ND])
#else
# define F_AREA_2D_CACHE(e,t) F_AREA_CACHE(e,t)
#endif
#define FSP_CENTROID_CACHE(fsp) F_CENTROID_CACHE(FSP_IDX(fsp), FSP_THREAD(fsp))
#define F_CENTROID_CACHE(e,t)  FAST_C_STORAGE_R_NV(e,t,SV_CENTROID)
#define F_CENTROID_COMP(f,t)  F_STORAGE_R(f,t,SV_CENTROID_COMP)

#define F_DR0_CACHE(f,t)  FAST_F_STORAGE(f,t,SV_FACE_DR0,real (*)[ND_ND])
#define F_DR1_CACHE(f,t)  FAST_F_STORAGE(f,t,SV_FACE_DR1,real (*)[ND_ND])

#define F_CHILDREN(f,t)  FAST_F_STORAGE(f,t,SV_CHILD,face_t (*)[MAX_KIDS_PER_FACE])
#define F_CHILDREN_THREADS(f,t)  FAST_F_STORAGE(f,t,SV_CHILD_THREAD,Thread *(*)[MAX_KIDS_PER_FACE])
#define F_CHILD(f,t,i)(F_CHILDREN(f,t)[i])
#if 0
#define F_CHILDREN_INDEX(f,t)  F_STORAGE(f,t,SV_CHILD_INDEX,cxindex (*)[MAX_KIDS_PER_FACE])
#else
#if WIN64
#define F_CHILDREN_INDEX(f,t)  FAST_F_STORAGE(f,t,SV_CHILD_THREAD,long long (*)[MAX_KIDS_PER_FACE])
#else
#define F_CHILDREN_INDEX(f,t)  FAST_F_STORAGE(f,t,SV_CHILD_THREAD,cxindex (*)[MAX_KIDS_PER_FACE])
#endif
#endif
#if USE_INT64
#define F_CHILD_INDEX(f,t,i)((F_CHILDREN_INDEX(f,t))[i])
#else
#define F_CHILD_INDEX(f,t,i)(F_CHILD(f,t,i))
#endif

#define F_CHILD_THREAD(f,t,i)(F_CHILDREN_THREADS(f,t)[i])
#define F_NEIGHBOR(f,t,i)(  F_STORAGE(f,t,SV_F_NEIGHBOR,face_t(*)[MAX_EDGES_PER_FACE])[i])

#define C_MARK(c,t)  C_STORAGE_INDEX(c,t,SV_MARKING_REGISTER)

#define SV_GHOSTLINK_CELL(c,t)   C_STORAGE_I(c,t,SV_GHOSTLINK)
#define C_GHOST_MARK(c, t)  C_STORAGE_I(c,t,SV_GHOST_MARK)
#define C_MAPPED_MARK(c, t)   C_STORAGE_I(c,t,SV_MAPPED_CELL_MARK)
#define F_MARK(f,t)  FAST_F_STORAGE_I(f,t,SV_F_MARK)
#define C_UD_MARK(c, t)   C_STORAGE_R(c,t,SV_UD_CELL_MARK)
#define F_TMP(f,t)   FAST_F_STORAGE_R(f,t,SV_F_TMP_0)
#define C_POST_VAR(f,t)   FAST_F_STORAGE_R(f, t, SV_POST_VAR)
#define F_POST_VAR(f,t) C_POST_VAR(f,t)

#define F_BVIS(f,t)   FAST_F_STORAGE_R(f,t,SV_F_BVIS)

#if RP_SHELL
#define F_SHELL_JUNCTION(f,t)   F_STORAGE(f,t,SV_JUNCTION_FACE_LIST,struct objp_struct **)
#define F_SHELL_SHADOW_JUNCTION(f,t)   F_STORAGE(f,t,SV_SHADOW_JUNCTION_FACE_LIST,struct objp_struct **)
#define F_SHELL_SHADOW_JUNCTION_THREAD(f,t) (NNULLP(F_SHELL_SHADOW_JUNCTION(f,t))? O_F_THREAD(F_SHELL_SHADOW_JUNCTION(f,t)):NULL)
#define F_SHELL_SHADOW_JUNCTION_FACE(f,t) (NNULLP(F_SHELL_SHADOW_JUNCTION(f,t))? O_F(F_SHELL_SHADOW_JUNCTION(f,t)):NULL_FACE)
#endif

#if RP_DTRM || RP_S2S
# define CX_C_MARK(c,t)   C_STORAGE_I(c,t,SV_CX_C_MARK)
# define CX_CID_CACHE(c,t)   C_STORAGE_I(c,t,SV_CX_ID)
#endif

#define NODE_POST_MARK(v) N_STORAGE_I (NODE_INDEX(v), NODE_THREAD(v), SV_N_POST_MARK)
typedef struct edge_struct
{
  Node *v0, *v1;
#if RP_EDGE
  union
  {
    int asInt;
    real asReal;
    void *asPtr;
    face_t asFace;
    int mark;
    struct edge_struct *asEdge;
    Node *asNode;
    struct face_and_thread_struct f;
    struct cell_and_thread_struct c;
    struct edge_struct **prev;
    struct objp_struct *asObjp;
#if PARALLEL && RP_SHELL && RP_3D
    struct entity_struct *asEntity;
#endif
  } e1, e2, e3
#if PARALLEL && RP_SHELL && RP_3D
  , e4
#endif
  ;
#endif
  struct edge_struct *child[2];
#if DEBUG || USE_FEMCORE
  int eid;
#endif
#if RP_EDGE && RP_HANG && RP_NODE
  int partition;
#endif
} Edge;

#if RP_EDGE
# define EDGE_NEXT(e)((e)->e1.asEdge)
# define EDGE_NEXT_SHELL(e)((e)->e4.asEdge)
# define EDGE_MARK(e)((e)->e2.mark)
# define EDGE_FACE0(e)((e)->e1.asFace)
# define EDGE_FACE1(e)((e)->e2.asFace)
# if RP_HANG
#  define EDGE_ADULT(e)((e)->e1.asEdge)
#  define EDGE_CHILD(e,n)((e)->child[n])
#  if RP_NODE
#   define EDGE_PART(e)((e)->partition)
#  endif
# endif
#if DEBUG || USE_FEMCORE
# define EDGE_ID(e)((e)->eid)
#else
# define EDGE_ID(e) (-1)
#endif
#endif

#define EDGE_ITMP1(e) (e)->e1.asInt
#define EDGE_ITMP2(e) (e)->e2.asInt
#define EDGE_VTMP1(e) (e)->e1.asNode
#define EDGE_VTMP2(e) (e)->e2.asNode
#define EDGE_ETMP1(e) (e)->e1.asEdge
#define EDGE_ETMP2(e) (e)->e2.asEdge
#define EDGE_FTMP1(e) (e)->e1.asFace
#define EDGE_FTMP2(e) (e)->e2.asFace
#define EDGE_CTMP1(e) (e)->e1.asCell
#define EDGE_CTMP2(e) (e)->e2.asCell

/*
 * Node storage. For now, nodes are stored in blocks
 * of structs for permanent variables, with indices
 * into a single (per-process) node thread for optional
 * and temporary storage. The node thread could eventually
 * hang off the domain and contain all the storage.
 */

typedef struct node_block_struct
{
  Node *b;  /* Pointer to node block */
  int n;      /* Number of nodes in block */
} NodeBlock;

typedef union tmp_union
{
  cxindex asIndex;
  cxboolean asBool;
  real asReal;
  float asFloat;
  int asInt;
  void *asPtr;
  struct thread_struct *asThread;
  Node *asNode;
#if RP_EDGE
  struct edge_struct *asEdge;
#endif
  struct entity_struct *asEntity;
  struct objp_struct *asObjp;
} TempUnion;

#if LSQ_RECON
#define NODE_VEL_U_G(v) N_STORAGE_R_NV(NODE_INDEX(v),NODE_THREAD(v),SV_N_VEL_U_G)
#define NODE_VEL_V_G(v) N_STORAGE_R_NV(NODE_INDEX(v),NODE_THREAD(v),SV_N_VEL_V_G)
#if RP_3D
#define NODE_VEL_W_G(v) N_STORAGE_R_NV(NODE_INDEX(v),NODE_THREAD(v),SV_N_VEL_W_G)
#endif /* RP_3D */
#define NODE_RST_XX(v) N_STORAGE_R(NODE_INDEX(v),NODE_THREAD(v),SV_N_RST_XX)
#define NODE_RST_XY(v) N_STORAGE_R(NODE_INDEX(v),NODE_THREAD(v),SV_N_RST_XY)
#define NODE_RST_XZ(v) N_STORAGE_R(NODE_INDEX(v),NODE_THREAD(v),SV_N_RST_XZ)
#define NODE_RST_YY(v) N_STORAGE_R(NODE_INDEX(v),NODE_THREAD(v),SV_N_RST_YY)
#define NODE_RST_YZ(v) N_STORAGE_R(NODE_INDEX(v),NODE_THREAD(v),SV_N_RST_YZ)
#define NODE_RST_ZZ(v) N_STORAGE_R(NODE_INDEX(v),NODE_THREAD(v),SV_N_RST_ZZ)
#define NODE_PHI_G(v) N_STORAGE_R_NV(NODE_INDEX(v),NODE_THREAD(v),SV_N_PHI_G)
#define NODE_VEL(v) FAST_N_STORAGE_R_NV(NODE_INDEX(v),NODE_THREAD(v),SV_N_VEL)
#define NODE_PHI(v) FAST_N_STORAGE_R(NODE_INDEX(v),NODE_THREAD(v),SV_N_PHI)
#define NODE_SUM(v) FAST_N_STORAGE_R(NODE_INDEX(v),NODE_THREAD(v),SV_N_SUM)
#define NODE_G(v) FAST_N_STORAGE_R_NV(NODE_INDEX(v),NODE_THREAD(v),SV_N_G)
#define NODE_Lambda(v) N_STORAGE_R_NV(NODE_INDEX(v),NODE_THREAD(v),SV_N_Lambda)
#define NODE_I(v) FAST_N_STORAGE_R_NV(NODE_INDEX(v),NODE_THREAD(v),SV_N_I)
#define NODE_IXY(v) N_STORAGE_R(NODE_INDEX(v),NODE_THREAD(v),SV_N_Ixy)
#if RP_3D
#define NODE_IYZ(v) N_STORAGE_R(NODE_INDEX(v),NODE_THREAD(v),SV_N_Iyz)
#define NODE_IZX(v) N_STORAGE_R(NODE_INDEX(v),NODE_THREAD(v),SV_N_Izx)
#endif /* RP_3D */
#endif /* LSQ_RECON */
#if RP_GEOM
#define NODE_OBJP(v)   C_STORAGE(NODE_INDEX(v), NODE_THREAD(v), SV_N_OBJP, struct objp_struct **)
#endif

#define NODE_RTMP_0(v)N_STORAGE_R(NODE_INDEX(v),NODE_THREAD(v),SV_N_RTMP_0)
#define NODE_RTMP_1(v)FAST_N_STORAGE_R(NODE_INDEX(v),NODE_THREAD(v),SV_N_RTMP_1)
#define NODE_RTMP_2(v)FAST_N_STORAGE_R(NODE_INDEX(v),NODE_THREAD(v),SV_N_RTMP_2)

#define NODE_MAX(v) N_STORAGE_R(NODE_INDEX(v),NODE_THREAD(v),SV_N_MAX)
#define NODE_MIN(v) N_STORAGE_R(NODE_INDEX(v),NODE_THREAD(v),SV_N_MIN)

#define NODE_MSN(v) (  C_STORAGE(NODE_INDEX(v),NODE_THREAD(v),SV_N_MSN,msn_t **))

#define F_NODE_SHADOW(f,t,n)F_NODE(F_SHADOW(f,t),THREAD_SHADOW(t),F_NNODES(f,t)-(n)-1)
#define F_NODE_SHADOW_SAFE(f,t,n)((!SV_ALLOCATED_P(t,SV_SHADOW) || NULL_FACE_P(F_SHADOW(f,t))) ? NULL : F_NODE_SHADOW(f,t,n))

/* Single (per-process) node thread for accessing node storage */


/* Node fields */
#if !UDF_COMPILER
#define NODE_COORD NODE_COORD1
#endif
#define NODE_X(v)(NODE_COORD(v)[0])
#define NODE_Y(v)(NODE_COORD(v)[1])
#if RP_3D
#define NODE_Z(v)(NODE_COORD(v)[2])
#else
#define NODE_Z(v)0.0
#endif

#define NODE_X_M1(v)(NODE_COORD_M1(v)[0])
#define NODE_Y_M1(v)(NODE_COORD_M1(v)[1])
#if RP_3D
#define NODE_Z_M1(v)(NODE_COORD_M1(v)[2])
#else
#define NODE_Z_M1(v)0.0
#endif

#define NODE_X_N(v)(NODE_COORD_N(v)[0])
#define NODE_Y_N(v)(NODE_COORD_N(v)[1])
#if RP_3D
#define NODE_Z_N(v)(NODE_COORD_N(v)[2])
#else
#define NODE_Z_N(v)0.0
#endif

#define NODE_X_INIT(v)(NODE_COORD_INIT(v)[0])
#define NODE_Y_INIT(v)(NODE_COORD_INIT(v)[1])
#if RP_3D
#define NODE_Z_INIT(v)(NODE_COORD_INIT(v)[2])
#else
#define NODE_Z_INIT(v)0.0
#endif

#define NODE_ID(v)((v)->id)
#define NODE_FLAGS(v)((v)->flags)
#define NODE_INDEX(v)((v)->idx)
#define NODE_THREAD(v)((v)->thread)
#if DEBUG && 0
#define SET_NODE_SHADOW(v,vs) Set_Node_Shadow (v, vs)
#define NODE_SHADOW(v) Get_Node_Shadow (v)
#else
#define SET_NODE_SHADOW(v,vs) \
  {                 \
  if (!FREE_NODE_P(v) && NNULLP(THREAD_STORAGE(NODE_THREAD(v),SV_N_SHADOW)))  \
    FAST_N_STORAGE(NODE_INDEX(v),NODE_THREAD(v),SV_N_SHADOW,Node **) = vs;\
  }
#define NODE_SHADOW(v) (            \
  (!FREE_NODE_P(v) && NNULLP(THREAD_STORAGE(NODE_THREAD(v),SV_N_SHADOW))? \
   FAST_N_STORAGE(NODE_INDEX(v),NODE_THREAD(v),SV_N_SHADOW,Node **):NULL))
#endif
#define C_DVOLUME_DT(c,t)  FAST_C_STORAGE_R(c,t,SV_DVOLUME_DT)
#define NODE_COORD_INIT(v) \
  N_STORAGE_DP_NV(NODE_INDEX(v),NODE_THREAD(v),SV_N_XINIT)
/* Nodal coordinates at the beginning of the time step */
#define NODE_COORD_M1(v) FAST_N_STORAGE_DP_NV(NODE_INDEX(v),NODE_THREAD(v),SV_N_X_M1)
/* Nodal coordinates at the beginning of dynamic mesh
   NODE_COORD_N(v) - NODE_COORD_M1(v) = difference due to mesh motion */
#define NODE_COORD_N(v) FAST_N_STORAGE_DP_NV(NODE_INDEX(v),NODE_THREAD(v),SV_N_XN)
#define NODE_COORD_REF(v) N_STORAGE_DP_NV(NODE_INDEX(v),NODE_THREAD(v),SV_N_X_REF)
#define NODE_PERDISP(v) N_STORAGE_DP_NV(NODE_INDEX(v),NODE_THREAD(v),SV_N_PERDISP)
#define NODE_PERIMAG(v) N_STORAGE_DP_NV(NODE_INDEX(v),NODE_THREAD(v),SV_N_PERIMAG)
#define NODE_PNUMBER(v) N_STORAGE_R(NODE_INDEX(v),NODE_THREAD(v),SV_N_PNUMBER)
#define NODE_COORD_NI(v) N_STORAGE_DP_NV(NODE_INDEX(v),NODE_THREAD(v),SV_N_XNI)
#define NODE_COORD_DX(v) FAST_N_STORAGE_DP_NV(NODE_INDEX(v),NODE_THREAD(v),SV_N_DX)
#define NODE_COORD_DX1(v) N_STORAGE_DP_NV(NODE_INDEX(v),NODE_THREAD(v),SV_N_DX1)
#define NODE_COORD_NEST(v) FAST_N_STORAGE_R_NV(NODE_INDEX(v),NODE_THREAD(v),SV_N_NEST)
#define NODE_DL_NEXT(v) FAST_C_STORAGE(NODE_INDEX(v),NODE_THREAD(v),SV_N_NEXT,Node **)
#define NODE_DL_PREV(v) FAST_C_STORAGE(NODE_INDEX(v),NODE_THREAD(v),SV_N_PREV,Node **)
#define NODE_ITMP(v) FAST_N_STORAGE_I (NODE_INDEX(v), NODE_THREAD(v), SV_N_ITMP)
#define NODE_ID_SC(v) N_STORAGE_I (NODE_INDEX(v), NODE_THREAD(v), SV_N_SC_ID)
#define NODE_ID_S2S(v) N_STORAGE_I (NODE_INDEX(v), NODE_THREAD(v), SV_N_S2S_ID)
#define NODE_SHADOW_ID(v)(NODE_TMP_0(v).asInt)

#define NODE_TMP(_v,_svar) \
  N_STORAGE (NODE_INDEX (_v), NODE_THREAD (_v), _svar, TempUnion *)
#define FAST_NODE_TMP(_v,_svar) \
  FAST_N_STORAGE (NODE_INDEX (_v), NODE_THREAD (_v), _svar, TempUnion *)
#define NODE_TMP_0(_v) FAST_NODE_TMP (_v, SV_N_TMP_0)
#define NODE_TMP_1(_v) FAST_NODE_TMP (_v, SV_N_TMP_1)
#define NODE_TMP_2(_v) FAST_NODE_TMP (_v, SV_N_TMP_2)
#define NODE_TMP_3(_v) FAST_NODE_TMP (_v, SV_N_TMP_3)

#define NODE_NEXT(v)((v)->thread)
#define NODE_NXT(v)(NODE_TMP_0(v).asNode) /* replacement of NODE_NEXT */
#if RP_NODE
#define NODE_PART(v)(NODE_TMP_0(v).asInt)
#endif
#define NODE_VISIT(v)(NODE_TMP_0(v).asInt)
#define NODE_EDGE(v)(NODE_TMP_0(v).asEdge)
#define NODE_VALUE(v)(NODE_TMP_0(v).asReal)
#define NODE_VALUE2(v)(NODE_TMP_1(v).asReal)
#define NODE_FORCE(v)((real *)(NODE_TMP_0(v).asPtr))
#define NODE_FORCE_P(v) (NODE_TMP_0(v).asPtr)
#define NODE_VELOCITY NODE_FORCE
#define NODE_RVAL1(v)(NODE_TMP_0(v).asReal)
#define NODE_RVAL2(v)(NODE_TMP_1(v).asReal)
#define NODE_MARK(v)(NODE_TMP_1(v).asInt)
#define NODE_COPY(v)(NODE_TMP_1(v).asNode)
#define NODE_PTR1(v)(NODE_TMP_0(v).asPtr)
#define NODE_PTR2(v)(NODE_TMP_1(v).asPtr)
#define NODE_PTR NODE_PTR2
#define NODE_ITMP1(v)(NODE_TMP_0(v).asInt)
#define NODE_ITMP2(v)(NODE_TMP_1(v).asInt)
#define NODE_LIST(v)(NODE_TMP_0(v).asEntity)
#define NODE_THREAD_PTR(v)(NODE_TMP_1(v).asThread)

#define CNZ_NODE(n, t)   C_STORAGE(n,t,SV_CNZ_NODEP,Node**)
#define FNZ_NODE(n, t)   C_STORAGE(  C_STORAGE(n,t,SV_FNZ_IDX,int*),THREAD_CNZ(t),SV_CNZ_NODEP,Node**)
#define CNZ_NODE_INDEX(v)   C_STORAGE(NODE_INDEX(v),NODE_THREAD(v),SV_N_CNZ_IDX,int*)
/*----------------svar macros end here....*/
#define UNIDENTIFIED_NODE      0x0000
#define INTERNAL_REFN_NODE     0x0001|USED_NODE
#define BOUNDARY_REFN_NODE     0x0002|USED_NODE
#define PERIODIC_REFN_NODE     0x0004|USED_NODE
#define USED_NODE        0x0008
#define INTERNAL_ORIG_NODE     0x0010|USED_NODE
#define BOUNDARY_ORIG_NODE     0x0020|USED_NODE
#define PERIODIC_ORIG_NODE     0x0040|USED_NODE
#define FIXED_NODE             0x0080
#define HANGING_EDGE_NODE      0x0100|USED_NODE
#define HANGING_FACE_NODE      0x0200|USED_NODE
#define HANGING_CELL_NODE      0x0400|USED_NODE
#define GRID_INTERFACE_NODE    0x0800
#define INTERFACE_NODE_ON_NODE 0x1000
#define INTERFACE_NODE         0x2000
#define V_FLAGS_INT            0x4000
#define UNREAD_NODE            0x8000 /* for case read */
#define VISITED_NODE           0x10000
#define TMP_NODE_FLAG          0x20000
#define ACTIVE_INTERFACE_NODE  0x40000 /* temp flag */
#define MARK_FLAG              0x80000
#define TAG_FLAG               0x100000
#define REFINE_FLAG            0x200000
#define COARSEN_FLAG           0x400000
#define GARBAGE_FLAG           0x800000 /*To be used in garbage collect only!*/
#define RP_RECON_MARK_FLAG     0x888000
#define RP_MAPPED_MARK_FLAG    0x888800 /*This flag is for cells have mapped interface faces*/
/* for tri/tet meshes */
#define SETTLED_FLAG           0x1000000
#define REMOVE_FLAG            0x2000000
#define KEEP_FLAG              0x4000000
#define QUEUE_FLAG             0x8000000
#define NEW_ENTITY_FLAG        0x10000000
#define OLD_COORDS_STORED      0x20000000
#define V_FLAGS_VST            0x40000000
#define V_FLAGS_CNR            0x80000000


#define REFN_MASK 0x0007
#define ORIG_MASK 0x00f0
#define INTR_MASK 0x0011
#define BDRY_MASK 0x0022
#define PERI_MASK 0x0044
#define HANG_MASK 0x0f00
#define TRI_TET_MASK 0xf000000

#define UNUSED_NODE_P(n)  (NODE_FLAGS(n) == UNIDENTIFIED_NODE || FREE_NODE_P(n))
#define FREE_NODE_P(n) (!(NODE_FLAGS(n) & USED_NODE))
#define USED_NODE_P(n) (NODE_FLAGS(n) & USED_NODE)
#define ORIGINAL_NODE_P(n)(NODE_FLAGS(n) & ORIG_MASK)
#define ADAPTION_NODE_P(n)(NODE_FLAGS(n) & REFN_MASK)
#define INTERNAL_NODE_P(n)(NODE_FLAGS(n) & INTR_MASK)
#define BOUNDARY_NODE_P(n)(NODE_FLAGS(n) & BDRY_MASK)
#define PERIODIC_NODE_P(n)(NODE_FLAGS(n) & PERI_MASK)
#define HANGING_NODE_P(n) (NODE_FLAGS(n) & HANG_MASK)
#define HANGING_EDGE_NODE_P(n)(NODE_FLAGS(n) & HANGING_EDGE_NODE)
#define HANGING_FACE_NODE_P(n)(NODE_FLAGS(n) & HANGING_FACE_NODE)
#define HANGING_CELL_NODE_P(n)(NODE_FLAGS(n) & HANGING_CELL_MASK)

#define GRID_INTERFACE_NODE_P(n)(NODE_FLAGS(n) & GRID_INTERFACE_NODE)
#define ACTIVE_INTERFACE_NODE_P(n)(NODE_FLAGS(n) & ACTIVE_INTERFACE_NODE)
#define INTERFACE_NODE_ON_NODE_P(n)(NODE_FLAGS(n) & INTERFACE_NODE_ON_NODE)
#define INTERFACE_NODE_P(n)(NODE_FLAGS(n) & INTERFACE_NODE)

#if DEBUG
FLUENT_EXPORT void Set_Node_Shadow (Node *, Node *);
FLUENT_EXPORT Node *Get_Node_Shadow (Node *);
#endif

FLUENT_EXPORT Objp *i_add (int, Objp *);
FLUENT_EXPORT Objp *i_del(int, Objp *);
FLUENT_EXPORT Objp *v_add (Node *, Objp *);
FLUENT_EXPORT Objp *v_del (Node *, Objp *);
FLUENT_EXPORT cxboolean v_mem (Node *, Objp *);
FLUENT_EXPORT Objp *f_add (face_t, Thread *, Objp *);
FLUENT_EXPORT Objp *f_add_mt (face_t, Thread *, Objp *, void **);
FLUENT_EXPORT Objp *f_del (face_t, Thread *, Objp *);
FLUENT_EXPORT Objp *f_del_mt (face_t, Thread *, Objp *, void **);
FLUENT_EXPORT cxboolean f_mem (face_t, Thread *, Objp *);
FLUENT_EXPORT cxboolean i_mem (int, Objp *);
FLUENT_EXPORT Objp *i_get(int, Objp *);
#if DEBUG_OBJP
FLUENT_EXPORT Objp *c_add_debug(char *, int,
                                cell_t, Thread *, Objp *, ...);
#define c_add(...) c_add_debug(__FILE__, __LINE__, __VA_ARGS__)
#else
FLUENT_EXPORT Objp *c_add (cell_t, Thread *, Objp *);
#endif
FLUENT_EXPORT Objp *c_list_add (Objp *, Objp *, cxboolean);
FLUENT_EXPORT Objp *c_list_add_check (Objp *, Objp *);
FLUENT_EXPORT Objp *c_del (cell_t, Thread *, Objp *);
FLUENT_EXPORT Objp *c_del_mt (cell_t, Thread *, Objp *, void **);
FLUENT_EXPORT cxboolean c_mem (cell_t, Thread *, Objp *);
FLUENT_EXPORT Objp *t_add (Thread *, Objp *);
FLUENT_EXPORT Objp *t_del (Thread *, Objp *);
FLUENT_EXPORT cxboolean t_mem (Thread *, Objp *);
FLUENT_EXPORT Objp *p_add (void *, Objp *);
FLUENT_EXPORT Objp *p_del (void *, Objp *);
FLUENT_EXPORT cxboolean p_mem (void *, Objp *);

/* registry for use of shared fw,dw,tmp arrays in cell struct, n[12] arrays in
 * node struct.
 */
FLUENT_EXPORT void Mark_Storage(Domain *, int which, const char label[]);
FLUENT_EXPORT cxboolean Is_Storage_P(Domain *, int which, char label[]);

FLUENT_EXPORT Cell *new_c_struct (Thread *, int, int);
FLUENT_EXPORT cell_t new_c_mem (const char *, int,
                                Thread *, Domain *, Cell_Element_Type, ...);
FLUENT_EXPORT cell_t new_c_type_mem (const char *, int,
                                     cell_t, Thread *, Domain *,
                                     Cell_Element_Type, ...);
FLUENT_EXPORT void update_c_struct (cell_t, Thread *);
#if !UDF_COMPILER
# define new_c(...) new_c_mem (__FILE__, __LINE__, __VA_ARGS__)
# define new_c_type(...) new_c_type_mem (__FILE__, __LINE__, __VA_ARGS__)
#endif

FLUENT_EXPORT void Fill_Cell_Face_Pointer (Domain *, Thread *);
FLUENT_EXPORT void Fill_Face_Cell_Pointer (Domain *, Thread *);

FLUENT_EXPORT Face *new_f_struct (Thread *, int);
FLUENT_EXPORT face_t new_f_mem (const char *, int,
                                Thread *, Domain *, Face_Element_Type, ...);
FLUENT_EXPORT face_t new_f_type_mem (const char *, int,
                                     face_t, Thread *, Domain *,
                                     Face_Element_Type, ...);
#if !UDF_COMPILER
# define new_f(...) new_f_mem (__FILE__, __LINE__, __VA_ARGS__)
# define new_f_type(...) new_f_type_mem (__FILE__, __LINE__, __VA_ARGS__)
#endif

FLUENT_EXPORT cell_t new_copy_of_c(cell_t, Thread *, Thread *, Domain *);
FLUENT_EXPORT cell_t new_mesh_copy_of_c(cell_t, Thread *, Thread *, Domain *);
FLUENT_EXPORT face_t new_copy_of_f(face_t, Thread *, Thread *, Domain *);
FLUENT_EXPORT face_t new_mesh_copy_of_f(face_t, Thread *, Thread *, Domain *);
FLUENT_EXPORT void copy_c_storage(cell_t, Thread *, cell_t, Thread *,
                                  cxboolean);
FLUENT_EXPORT void copy_f_storage(face_t, Thread *, face_t, Thread *,
                                  cxboolean);
FLUENT_EXPORT void copy_svar_storage(face_t, Thread *, face_t, Thread *,
                                     cxboolean);
FLUENT_EXPORT void copy_f_mesh_storage (face_t, Thread *, face_t, Thread *,
                                        Domain *);
FLUENT_EXPORT void copy_all_f_storage(Thread *, Thread *);

FLUENT_EXPORT Node *new_v(Domain *);
FLUENT_EXPORT Node *new_copy_of_v(Node *, Domain *);
FLUENT_EXPORT void free_v(Node *);
FLUENT_EXPORT void free_all_v(cxboolean, Domain *);
FLUENT_EXPORT void Insert_Node_Block(Domain *, void *, int, Thread *);
FLUENT_EXPORT void Update_Subthread_N_Elements(Thread *);
#if RP_EDGE
FLUENT_EXPORT Edge *new_e(void);
FLUENT_EXPORT void free_e(Edge *);
FLUENT_EXPORT void free_e_on_t(Domain *, Thread *);
FLUENT_EXPORT void free_all_e(Domain *);
#endif

FLUENT_EXPORT void thread_t(Thread *, Thread **);
FLUENT_EXPORT void unthread_t(Thread *);
FLUENT_EXPORT void md_unthread_t(Thread *);
FLUENT_EXPORT void unthread_and_free_t(Thread *);
FLUENT_EXPORT void unthread_and_free_t_and_head(Thread *);
FLUENT_EXPORT void md_unthread_and_free_t_and_head(Thread *);
FLUENT_EXPORT void Double_Link_Domain(Domain *);
FLUENT_EXPORT void double_link_t_thread(Thread **t);
FLUENT_EXPORT void md_double_link_t_all_f_threads(Domain *domain);
FLUENT_EXPORT void md_double_link_t_all_c_threads(Domain *domain);
FLUENT_EXPORT void free_thread(Thread *);
FLUENT_EXPORT void free_thread_and_head(Thread *);
FLUENT_EXPORT void md_free_thread_and_head(Thread *);
FLUENT_EXPORT void rfree_face_thread(Domain *, Thread *);
FLUENT_EXPORT void copy_thread_head(struct thread_head_struct *,
                                    struct thread_head_struct *,
                                    Thread *, Thread *);
FLUENT_EXPORT Thread *new_thread(void);
FLUENT_EXPORT Thread *new_thread_copy(Thread *);
FLUENT_EXPORT Thread *new_thread_and_head_copy(Thread *);
FLUENT_EXPORT void Allocate_Storage_Array_If_Needed(Thread *, size_t);
FLUENT_EXPORT void Zero_Thread_N_Elements(Thread *);
FLUENT_EXPORT void MD_Zero_Thread_N_Elements(Thread *);
FLUENT_EXPORT Domain *new_domain(void);
FLUENT_EXPORT int Next_Domain_Id(Domain *);
FLUENT_EXPORT Domain *Lookup_Domain(Domain *, int);
FLUENT_EXPORT Thread *lookup_thread_by_id(Domain *domain, int id);
FLUENT_EXPORT void Alloc_Domain_Managers (Domain *, size_t);
FLUENT_EXPORT void free_domain(Domain *, cxboolean isacopy);
FLUENT_EXPORT void rfree_domain(Domain *);
FLUENT_EXPORT void free_domain_threads(Domain *domain, cxboolean withheads, cxboolean alltypes);
FLUENT_EXPORT void free_coarse_levels(Domain *);
FLUENT_EXPORT void reinitialize_dump(Domain *);
FLUENT_EXPORT void Mem_Stats(Domain *);
FLUENT_EXPORT void Misc_Mem_Stats(Domain *);
FLUENT_EXPORT void Display_Memory_On_Thread(Domain *, int);
FLUENT_EXPORT void Display_Memory(Domain *);
FLUENT_EXPORT void Dump_Memory(Domain *, FILE *);
#if RP_EDGE
FLUENT_EXPORT void Set_Edges_Per_Alloc(int);
#endif
FLUENT_EXPORT void Reset_Node_List(Domain *);
FLUENT_EXPORT void Set_Nodes_Per_Alloc(int, Domain *);
FLUENT_EXPORT void Alloc_Node_Thread(Domain *);
FLUENT_EXPORT void Alloc_Node_Thread_With_Id(Domain *const, const int);
FLUENT_EXPORT cxboolean Check_Unreferenced_Nodes (Domain *, int,
                                                  cxboolean, cxboolean);
FLUENT_EXPORT cxboolean Minimize_Node_Storage (Domain *);

#if DEBUG_OBJP
#define new_o(...) new_o_debug(__FILE__, __LINE__)
FLUENT_EXPORT Objp *new_o_debug(char *, int);
#else
FLUENT_EXPORT Objp *new_o(void);
#endif
FLUENT_EXPORT Objp *new_copy_of_o(Objp *);
FLUENT_EXPORT void free_o(Objp *);
FLUENT_EXPORT void free_o_list(Objp *);
#define free_init_o_list(_o) \
  if (NNULLP (_o)) {free_o_list (_o); _o = NULL;}
FLUENT_EXPORT Objp *copy_o_list(Objp *);
FLUENT_EXPORT Objp *ccat_o_list(Objp *, Objp *);
FLUENT_EXPORT Objp *reverse_o_list(Objp *);
FLUENT_EXPORT Objp *o_list_tail(Objp *obj);
FLUENT_EXPORT int o_length(Objp *);
FLUENT_EXPORT cxboolean o_length_greater_equal_n (Objp *, int);
FLUENT_EXPORT void unthread_and_free_o(Objp *);
FLUENT_EXPORT void unthread_o(Objp *);
FLUENT_EXPORT void thread_o(Objp *, Objp **);
FLUENT_EXPORT void double_link_o_thread(Objp **);
FLUENT_EXPORT void Set_Objps_Per_Alloc(int);
FLUENT_EXPORT cxboolean Minimize_Object_Pointer_Storage (Domain *);


FLUENT_EXPORT void *new_object_manager(size_t object_size, size_t objects_per_alloc);
FLUENT_EXPORT void free_object_manager(void *vm);
FLUENT_EXPORT void object_manager_info(void *vm);
FLUENT_EXPORT void *new_object_mt(void *vm);
FLUENT_EXPORT void free_object_mt(void *obj, void *vm);
#define OLIST_NEXT(o) (*((void **) o))
FLUENT_EXPORT void free_object_list_mt(void *obj, void *vm);

FLUENT_EXPORT void free_om_mt(void **);
FLUENT_EXPORT Objp *new_o_mt(void **);
FLUENT_EXPORT void free_o_mt(Objp *, void *);
FLUENT_EXPORT void free_o_list_mt(Objp *, void **);
FLUENT_EXPORT Objp *c_add_mt (cell_t, Thread *, Objp *, void **);
FLUENT_EXPORT Objp *p_add_mt (void *, Objp *, void **);
FLUENT_EXPORT Objp *t_add_mt (Thread *, Objp *, void **);

FLUENT_EXPORT void alloc_more_storage(Thread *);
FLUENT_EXPORT void alloc_cell_thread_storage(Thread *, int);
FLUENT_EXPORT void realloc_cell_thread_storage(Domain *, Thread *, int old_len, int new_len);
FLUENT_EXPORT void alloc_face_thread_storage(Thread *, int);
FLUENT_EXPORT void realloc_face_thread_storage(Domain *, Thread *, int old_len, int new_len);
FLUENT_EXPORT void rebuild_free_list(Domain *, Thread *, int);

FLUENT_EXPORT void Fill_Face_Status(Domain *);
FLUENT_EXPORT void Fill_Cell_Status(Domain *);

FLUENT_EXPORT void Free_Face_Status(Domain *);
FLUENT_EXPORT void Free_Cell_Status(Domain *);
FLUENT_EXPORT void Set_Svar_Initialized(Domain *, Svar, cxboolean);

FLUENT_EXPORT cxboolean Garbage_Collect_Thread_All_Nodes(cxboolean);
FLUENT_EXPORT void Garbage_Collect_Entities(Domain *);
FLUENT_EXPORT void Garbage_Collect_Nodes(Domain *);
#if RP_3D
FLUENT_EXPORT void Garbage_Collect_Edges(Domain *);
#endif
FLUENT_EXPORT void Garbage_Collect_Faces(Domain *);

#if RP_NODE
FLUENT_EXPORT int thread_layer_first(Thread *, int);
FLUENT_EXPORT int thread_layer_last(Thread *, int);
#endif /* RP_NODE */

FLUENT_EXPORT size_t Get_Size_Item_Per_Element_Mem (Thread *, int, char *, int);
FLUENT_EXPORT size_t Get_Size_Storage_Domain_Mem (Domain *, cxboolean,
                                                  int, char *, int);
#define Get_Size_Item_Per_Element(a,b) \
  Get_Size_Item_Per_Element_Mem((a),(b),__FILE__,__LINE__)
#define Get_Size_Storage_Domain(a,b,c) \
  Get_Size_Storage_Domain_Mem((a),(b),(c),__FILE__,__LINE__)

#if DEBUG_MEMORY
FLUENT_EXPORT void Set_Thread_T0(Thread *, Thread *, char *, int);
FLUENT_EXPORT void Set_Thread_T1(Thread *, Thread *, char *, int);
#endif

FLUENT_EXPORT void *CX_Malloc_With_Check(size_t, char *, int);
#define CX_MALLOC_WITH_CHECK(size) CX_Malloc_With_Check((size), __FILE__, __LINE__)

FLUENT_EXPORT void *CX_Calloc_With_Check(size_t, char *, int);
#define CX_CALLOC_WITH_CHECK(size) CX_Calloc_With_Check((size), __FILE__, __LINE__)

/*  For direct access to nodes without threading them.
 *  Eventually something will hang off the domain struct.
 */
#if !USE_DOMAIN_DATA_MANAGER
extern FLUENT_EXPORT NodeBlock *node_block; /* Array of pointers to node blocks. */
extern FLUENT_EXPORT int nnode_blocks;  /* Number of node block entries used. */
#endif

FLUENT_EXPORT cxboolean Is_Root_Domain_P(Domain *domain);

#define begin_node_loop_all(_n, _domain) { int b,var_nn;  Domain *_root_domain = Lookup_Node_Thread_Domain(_domain); \
    for (b=0; b<RDOMAIN_NNODE_BLOCKS(_root_domain); ++b)                    \
    for (_n=RDOMAIN_NODE_BLOCK(_root_domain)[b].b,var_nn=0; var_nn<(RDOMAIN_NODE_BLOCK(_root_domain))[b].n; ++_n,++var_nn)

#define end_node_loop_all(n) }

#define begin_node_loop(_n, _domain) { int b,var_nn;  Domain *_root_domain = Lookup_Node_Thread_Domain(_domain); \
    for (b=0; b<RDOMAIN_NNODE_BLOCKS(_root_domain); ++b)                    \
    for (_n=RDOMAIN_NODE_BLOCK(_root_domain)[b].b,var_nn=0; var_nn<(RDOMAIN_NODE_BLOCK(_root_domain))[b].n; ++_n,++var_nn)\
      if (!UNUSED_NODE_P (_n)) \
  {

#define end_node_loop(n) } }

/* thread loops */

#define TL_C               (1)    /* domain->c */
#define TL_NOSOLVE_C       (1<<1) /* domain->nosolve_c */
#define TL_NOSOLVE_EXT_C   (1<<2) /* domain->nosolve_ext_c */
#define TL_F               (1<<3) /* domain->f */
#define TL_NOSOLVE_F       (1<<4) /* domain->nosolve_f */
#define TL_INACTIVE_C_F    (1<<5) /* domain->inactive_c_f */
#define TL_PASSIVE_C_F     (1<<6) /* domain->passive_c_f */

/* TL_N is the number of mask bits */
#define TL_N 7

#define thread_loop_of loop
#define md_thread_loop_of(p,init,pp)for((p)=(init),(pp)=THREAD_SUB_THREADS(p);(p)!=NULL;(p)=THREAD_NEXT(p),(pp)=NULLP(p)?NULL:THREAD_SUB_THREADS(p))

/* The thread_type_loop macro depends on the ordering in domain_struct */
#define thread_type_loop(t,d,mask,n) \
  for (n = 0; n < TL_N; ++n) \
    if ((mask) & (1<<n)) \
      thread_loop_of(t, (&(DOMAIN_C(d)))[n])
#define md_thread_type_loop(t,d,mask,n,tp) \
  for (n = 0; n < TL_N; ++n) \
    if ((mask) & (1<<n)) \
      md_thread_loop_of(t,(&(DOMAIN_C(d)))[n],tp)

#define md_thread_loop_c(t,d,tp)md_thread_loop_of(t,DOMAIN_C(d),tp)
#define md_thread_loop_f(t,d,tp)md_thread_loop_of(t,DOMAIN_F(d),tp)
#define md_thread_loop_nosolve_c(t,d,tp)md_thread_loop_of(t,DOMAIN_NOSOLVE_C(d),tp)
#define md_thread_loop_all_c(t,d,n,tp)md_thread_type_loop(t,d,TL_C|TL_NOSOLVE_C,n,tp)
#define md_thread_loop_nosolve_ext_c(t,d,tp)md_thread_loop(t,DOMAIN_NOSOLVE_EXT_C(d),tp)
#define md_thread_loop_f(t,d,tp)md_thread_loop_of(t,DOMAIN_F(d),tp)
#define md_thread_loop_nosolve_f(t,d,tp)md_thread_loop_of(t,DOMAIN_NOSOLVE_F(d),tp)
#define md_thread_loop_all_f(t,d,n,tp)md_thread_type_loop(t,d,TL_F|TL_NOSOLVE_F,n,tp)
#define md_thread_loop_except_slide_f(t,d,tp) \
  md_thread_loop_f(t,d,tp) \
    if (!SLIDING_INTERFACE_THREAD_P(t))
#define md_thread_loop_nosolve_except_slide_f(t,d,tp) \
  md_thread_loop_nosolve_f(t,d,tp) \
    if (!SLIDING_INTERFACE_THREAD_P(t))
#define md_thread_loop_all_except_slide_f(t,d,n,tp) \
  md_thread_loop_all_f(t,d,n,tp) \
    if (!SLIDING_INTERFACE_THREAD_P(t))

#define mp_thread_loop_c(ct,d,pt)\
for((ct)=DOMAIN_C(d),(pt)=THREAD_SUB_THREADS(ct);(ct)!=NULL;(ct)=THREAD_NEXT(ct),(pt)=NULLP(ct)?NULL:THREAD_SUB_THREADS(ct))
#define mp_thread_loop_f(ft,d,pt)\
for((ft)=DOMAIN_F(d),(pt)=THREAD_SUB_THREADS(ft);(ft)!=NULL;(ft)=THREAD_NEXT(ft),(pt)=NULLP(ft)?NULL:THREAD_SUB_THREADS(ft))

#define thread_loop_a_c(d,n) \
  for(n=0;n<d->n_c_n_a;n++)

#define thread_loop_a_f(d,n) \
  for(n=0;n<d->n_f_n_a;n++)

#define THREAD_ARRAY_C(d,n) (d->c_n_a[n])
#define THREAD_ARRAY_F(d,n) (d->f_n_a[n])

#define thread_loop(t,d,n)thread_type_loop(t,d,TL_C|TL_F,n)
#define thread_loop_all(t,d,n)thread_type_loop(t,d,TL_C|TL_NOSOLVE_C|TL_F|TL_NOSOLVE_F,n)
#define thread_loop_c(ct,d)thread_loop_of(ct,DOMAIN_C(d))
#define thread_loop_nosolve_c(ct,d)thread_loop_of(ct,DOMAIN_NOSOLVE_C(d))
#define thread_loop_all_c(ct,d,n)thread_type_loop(ct,d,TL_C|TL_NOSOLVE_C,n)
#define thread_loop_nosolve_ext_c(ct,d)thread_loop_of(ct,DOMAIN_NOSOLVE_EXT_C(d))
#define thread_loop_f(ft,d)thread_loop_of(ft,DOMAIN_F(d))
#define thread_loop_nosolve_f(ft,d)thread_loop_of(ft,DOMAIN_NOSOLVE_F(d))
#define thread_loop_all_f(ft,d,n)thread_type_loop(ft,d,TL_F|TL_NOSOLVE_F,n)
#define thread_loop_inactive_c_f(ft,d)thread_loop_of(ft,DOMAIN_INACTIVE_C_F(d))
#define thread_loop_inactive_and_passive_c_f(t,d,n)thread_type_loop(t,d,TL_INACTIVE_C_F|TL_PASSIVE_C_F,n)
#define thread_loop_all_plus_inactive(t,d,n)thread_type_loop(t,d,TL_C|TL_NOSOLVE_C|TL_F|TL_NOSOLVE_F|TL_INACTIVE_C_F,n)
#define thread_loop_all_plus_inactive_and_passive(t,d,n)thread_type_loop(t,d,TL_C|TL_NOSOLVE_C|TL_F|TL_NOSOLVE_F|TL_INACTIVE_C_F|TL_PASSIVE_C_F,n)
#define thread_loop_except_slide_f(ft,d) \
  thread_loop_f(ft,d) \
    if (!SLIDING_INTERFACE_THREAD_P(ft))
#define thread_loop_nosolve_except_slide_f(ft,d) \
  thread_loop_nosolve_f(ft,d) \
    if (!SLIDING_INTERFACE_THREAD_P(ft))
#define thread_loop_all_except_slide_f(ft,d,n) \
  thread_loop_all_f(ft,d,n) \
    if (!SLIDING_INTERFACE_THREAD_P(ft))
#define MAPPED_SLIDING_INTERFACE_THREAD_P(t) \
  (SLIDING_INTERFACE_THREAD_P((t)) && SV_ALLOCATED_P(t, SV_N_MAPPED_FACES))
#define thread_loop_except_slide_f_but_mapped(ft,d) \
  thread_loop_f(ft,d) \
    if (!SLIDING_INTERFACE_THREAD_P(ft) || MAPPED_SLIDING_INTERFACE_THREAD_P(ft))
#define thread_loop_all_except_slide_f_but_mapped(ft,d,n) \
  thread_loop_all_f(ft,d,n) \
    if (!SLIDING_INTERFACE_THREAD_P(ft) || MAPPED_SLIDING_INTERFACE_THREAD_P(ft))
#define thread_loop_except_internal_and_slide_f_but_mapped(ft,d) \
  thread_loop_f(ft,d) \
    if ((THREAD_F_INTERIOR != THREAD_TYPE(ft)) || !SLIDING_INTERFACE_THREAD_P(ft) || MAPPED_SLIDING_INTERFACE_THREAD_P(ft)) //FLUID_THREAD_P(thread->t0)
#define thread_loop_all_except_internal_and_slide_f_but_mapped(ft,d,n) \
  thread_loop_all_f(ft,d,n) \
    if ((THREAD_F_INTERIOR != THREAD_TYPE(ft)) || !SLIDING_INTERFACE_THREAD_P(ft) || MAPPED_SLIDING_INTERFACE_THREAD_P(ft)) //FLUID_THREAD_P(thread->t0)
#if RP_OVERSET
#define thread_loop_overset_c(ct,d) \
  thread_loop_c(ct,d) \
    if (NNULLP(THREAD_OT(ct)))
#endif
#define thread_loop_cnz(ct,d)thread_loop_of(ct,DOMAIN_CNZ(d))
#define thread_loop_fnz(ct,d)thread_loop_of(ct,DOMAIN_FNZ(d))
#if USE_FEMCORE
#define thread_loop_cinz(ct,d)thread_loop_of(ct,DOMAIN_CINZ(d,INTERP_BEGIN))
#define thread_loop_finz(ct,d)thread_loop_of(ct,DOMAIN_FINZ(d,INTERP_BEGIN))
#endif
#define thread_loop_c_solid(t,d) \
  thread_loop_c (t, d) \
    if (SOLID_THREAD_P(t))
#define thread_loop_c_fluid(t,d) \
  thread_loop_c (t, d) \
    if (FLUID_THREAD_P(t))
#define thread_loop_c_structure(t,d) \
  thread_loop_c (t, d) \
    if (STRUCTURE_THREAD_P(t))

/* thread loop for persistent data.  Pick the following threads:
 * 1) all solved cell threads except for (old framework) shell cell threads
 * 2) all solved face threads except for (old framework) shell face threads
 * 3) non-solved face threads that are shadow threads (shell threads cannot
 *    be of shadow type so no separate conditional is needed for shells)
 * 4) non-solved face threads that are sliding boundaries (correspond to the
 *    stretched sliding boundaries
 */
#define thread_loop_persistent_data(t,domain,n) \
  thread_loop_all(t,domain,n) \
       if ( (((1<<n) == TL_C) && (!SHELL_CELL_THREAD_P(t) || SHELL_IO))  || \
            (((1<<n) == TL_F) && (!SHELL_CELL_THREAD_P(THREAD_T0(t)) || SHELL_IO))  || \
            (THREAD_F_SHADOW == THREAD_TYPE(t)) || \
            (((1<<n) == TL_NOSOLVE_F) && (THREAD_F_SLIDING_BOUNDARY == THREAD_TYPE(t))))

#if RP_NETWORK
# define thread_loop_nwc(ct,d)thread_loop_of(ct,DOMAIN_NWC(d))
# define thread_loop_nwf(ft,d)thread_loop_of(ft,DOMAIN_NWF(d))
#endif

/* loop through dual faces if present, otherwise return face */
#define single_or_dual_face_loop(f,tf,_f,_tf,n)\
   for(n=0, tf = (NULLP(THREAD_DUAL(_tf)) ? _tf : THREAD_DUAL(_tf)),\
       f = (NULLP(THREAD_DUAL(_tf)) ? _f : F_DUAL(_f,_tf,0));\
       n < (NULLP(THREAD_DUAL(_tf)) ? 1 : F_NDUALS(_f,_tf));\
       n++, f = (NULLP(THREAD_DUAL(_tf)) ? _f : F_DUAL(_f,_tf,n)))

#define begin_generic_loop_1(e,t,last)       {const int e##_loop_last = last; for (e=0; e<e##_loop_last; ++e){
#define   end_generic_loop_1(e,t)            }}
#define begin_generic_loop_2(e,t,first,last) {const int e##_loop_first = first, e##_loop_last = last; for (e=e##_loop_first; e<e##_loop_last; ++e){
#define   end_generic_loop_2(e,t)            }}
#define begin_generic_loop(e,t)              begin_generic_loop_1(e,t,THREAD_N_ELEMENTS(t))
#define   end_generic_loop                   end_generic_loop_1

/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
/* overset loops_{3,4} derived from generic_loop_1 - upper limit specified  */
#define begin_generic_loop_3(e,t,last,check) {const int e##_loop_last = last; for (e=0; e<e##_loop_last; ++e){ if(check) {
#define   end_generic_loop_3(e,t)            }}}
#define begin_generic_loop_4(e,t,last,skip)  {const int e##_loop_last = last; for (e=0; e<e##_loop_last; ++e){ if(skip) continue; {
#define   end_generic_loop_4(e,t)            }}}
/* overset loops_{5,6} derived from generic_loop_2 (for parallel) lower and upper limits specified */
#define begin_generic_loop_5(e,t,first,last,check) {const int e##_loop_first = first, e##_loop_last = last;\
                                                    for (e=e##_loop_first; e<e##_loop_last; ++e){\
                                                    if(check) {
#define   end_generic_loop_5(e,t)            }}}
#define begin_generic_loop_6(e,t,first,last,skip) {const int e##_loop_first = first, e##_loop_last = last;\
                                                   for (e=e##_loop_first; e<e##_loop_last; ++e){\
                                                   if(skip) continue; {
#define   end_generic_loop_6(e,t)            }}}

/* active entity loops - skip overset interface faces i.e. overset thread boundary faces + {faces b/t receptor and dead cells} */
#define begin_f_loop_overset_active(e,t) begin_generic_loop_4(e,t,THREAD_N_ELEMENTS(t), (!OVERSET_SOLVE_FACE_P(e,t) || !CONTACT_ZONE_SOLVE_FACE_P(e,t) || !SOLVE_NARROW_GAP_FACE_P(e,t) ))
#define   end_f_loop_overset_active(e,t)   end_generic_loop_4(e,t)
/* active entity loops - skip only overset dead cells - may change, but this is the R17.0 implementation  */
#define begin_c_loop_overset_active(e,t) begin_generic_loop_4(e,t,THREAD_N_ELEMENTS(t), (OVERSET_DEAD_CELL_P(e,t) || SKIP_CONTACT_ZONE_CELL_P(e,t) || SKIP_NARROW_GAP_CELL_P(e,t) ))
#define   end_c_loop_overset_active(e,t)   end_generic_loop_4(e,t)

#define begin_c_loop_overset_solve(e,t) begin_generic_loop_4(e,t,THREAD_N_ELEMENTS(t),(OVERSET_RECEPTOR_CELL_P(e,t) || OVERSET_DEAD_CELL_P(e,t) || SKIP_CONTACT_ZONE_CELL_P(e,t) || SKIP_NARROW_GAP_CELL_P(e,t) ))
#define   end_c_loop_overset_solve(e,t)   end_generic_loop_4(e,t)

/* overset entity type loops over only
 - receptor cells
 - dead cells
 - orphan cells
 */
#define begin_c_loop_receptor_int(e,t) begin_generic_loop_3(e,t,THREAD_N_ELEMENTS_INT(t),(OVERSET_RECEPTOR_CELL_P(e,t) && !SKIP_CONTACT_ZONE_CELL_P(e,t) && !SKIP_NARROW_GAP_CELL_P(e,t)))
#define begin_c_loop_dead_int(e,t)     begin_generic_loop_3(e,t,THREAD_N_ELEMENTS_INT(t),OVERSET_DEAD_CELL_P(e,t))
#define begin_c_loop_orphan_int(e,t)   begin_generic_loop_3(e,t,THREAD_N_ELEMENTS_INT(t),(OVERSET_ORPHAN_CELL_P(e,t) && !SKIP_CONTACT_ZONE_CELL_P(e,t) && !SKIP_NARROW_GAP_CELL_P(e,t)))
#define   end_c_loop_orphan_int(e,t)   end_generic_loop_3(e,t)
#define   end_c_loop_receptor_int(e,t) end_generic_loop_3(e,t)
#define   end_c_loop_dead_int(e,t)     end_generic_loop_3(e,t)
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/

#if !RP_NODE

# define begin_f_loop_int      begin_f_loop
# define   end_f_loop_int        end_f_loop
# define begin_f_loop(f,t)     begin_generic_loop(f,t)
# define   end_f_loop(f,t)       end_generic_loop(f,t)
# define begin_f_loop_all      begin_f_loop
# define   end_f_loop_all        end_f_loop
# define begin_f_loop_ext(f,t) {if (FALSE) {
# define   end_f_loop_ext(f,t) }}
# define begin_f_loop_int_or_all(f,t,a)  begin_f_loop(f,t)
# define   end_f_loop_int_or_all(f,t,a)    end_f_loop(f,t)

# define begin_c_loop(c,t)      begin_generic_loop(c,t){
# define   end_c_loop(c,t)       }end_generic_loop(c,t)
# define begin_c_loop_int       begin_c_loop
# define   end_c_loop_int         end_c_loop
# define begin_c_loop_ext(c,t)  {if (FALSE) {{
# define   end_c_loop_ext(c,t)  }}}
# define begin_c_loop_rext(c,t) {if (FALSE) {{
# define   end_c_loop_rext(c,t) }}}
# define begin_c_loop_eext(c,t) {if (FALSE) {{
# define   end_c_loop_eext(c,t) }}}
# define begin_c_loop_int_ext   begin_c_loop
# define   end_c_loop_int_ext     end_c_loop
# define begin_c_loop_all       begin_c_loop
# define   end_c_loop_all         end_c_loop

# define begin_cnz_loop(c,t)      begin_generic_loop(c,t){
# define   end_cnz_loop(c,t)       }end_generic_loop(c,t)
# define begin_cnz_loop_int       begin_cnz_loop
# define   end_cnz_loop_int         end_cnz_loop

# define begin_fnz_loop(c,t)      begin_generic_loop(c,t){
# define   end_fnz_loop(c,t)       }end_generic_loop(c,t)
# define begin_fnz_loop_int       begin_fnz_loop
# define   end_fnz_loop_int         end_fnz_loop
#if USE_FEMCORE
# define begin_cinz_loop(in,t)    begin_generic_loop(in,t){
# define   end_cinz_loop           }end_generic_loop
#endif

/* loop macros for overset discretization - serial - start */
/* faces */
# define begin_f_loop_active(f,t)   begin_f_loop_overset_active(f,t) /* strategically replaces begin_f_loop in discretization code  */
# define   end_f_loop_active(f,t)     end_f_loop_overset_active(f,t)
# define begin_f_loop_active_int    begin_f_loop_active              /* same as begin_f_loop_active in serial - trivial case  */
# define   end_f_loop_active_int      end_f_loop_active
/*cells  */
# define begin_c_loop_active(c,t)   begin_c_loop_overset_active(c,t)
# define   end_c_loop_active(c,t)     end_c_loop_overset_active(c,t)
# define begin_c_loop_active_int    begin_c_loop_active
# define   end_c_loop_active_int      end_c_loop_active
# define begin_c_loop_solve(c,t)   begin_c_loop_overset_solve(c,t)
# define   end_c_loop_solve(c,t)     end_c_loop_overset_solve(c,t)
# define begin_c_loop_solve_int    begin_c_loop_solve
# define   end_c_loop_solve_int      end_c_loop_solve

/* loop macros for overset discretization - serial - end */
#else

# define begin_f_loop_int(f,t)     begin_generic_loop_1(f,t,THREAD_N_ELEMENTS_INT(t))
# define   end_f_loop_int            end_generic_loop_1
# define begin_f_loop              begin_f_loop_int
# define   end_f_loop                end_f_loop_int
# define begin_f_loop_all(f,t)     begin_generic_loop_1(f,t,F_THREAD_N_ELEMENTS_ALL(t))
# define   end_f_loop_all            end_generic_loop_1
# define begin_f_loop_ext(f,t)     begin_generic_loop_2(f,t,THREAD_N_ELEMENTS_INT(t),thread_layer_last(t,MAX_LAYER))
# define   end_f_loop_ext            end_generic_loop_2
# define begin_f_loop_layer(f,t,l) begin_generic_loop_2(f,t,thread_layer_first(t,l),thread_layer_last(t,l))
# define   end_f_loop_layer(f,t,l)   end_generic_loop_2(f,t)
# define begin_f_loop_int_or_all(f,t,a) begin_generic_loop_1(f,t,a?F_THREAD_N_ELEMENTS_ALL(t):THREAD_N_ELEMENTS_INT(t))
# define   end_f_loop_int_or_all(f,t,a) end_generic_loop_1(f,t)

# define begin_c_loop(c,t)         begin_generic_loop_1(c,t,THREAD_N_ELEMENTS_INT(t)+THREAD_N_ELEMENTS_LAYER(t,LAYER_PRIMARY)){
# define   end_c_loop               }end_generic_loop_1
# define begin_c_loop_int(c,t)     begin_generic_loop_1(c,t,THREAD_N_ELEMENTS_INT(t)){
# define   end_c_loop_int           }end_generic_loop_1
# define begin_c_loop_ext(c,t)     begin_generic_loop_2(c,t,THREAD_N_ELEMENTS_INT(t),thread_layer_last(t,MAX_LAYER)){
# define   end_c_loop_ext           }end_generic_loop_2
# define begin_c_loop_rext(c,t)    begin_generic_loop_2(c,t,thread_layer_first(t,LAYER_PRIMARY),thread_layer_last(t,LAYER_PRIMARY)){
# define   end_c_loop_rext          }end_generic_loop_2
# define begin_c_loop_eext(c,t)    begin_generic_loop_2(c,t,thread_layer_first(t,LAYER_SECONDARY),thread_layer_last(t,LAYER_SECONDARY)){
# define   end_c_loop_eext          }end_generic_loop_2
# define begin_c_loop_int_ext(c,t) begin_generic_loop_1(c,t,thread_layer_last(t,LAYER_SECONDARY))
# define   end_c_loop_int_ext        end_generic_loop_1
# define begin_c_loop_all(c,t)     begin_generic_loop_1(c,t,C_THREAD_N_ELEMENTS_ALL(t)){
# define   end_c_loop_all           }end_generic_loop_1
# define begin_c_loop_layer(c,t,l) begin_generic_loop_2(c,t,thread_layer_first(t,l),thread_layer_last(t,l)){
# define   end_c_loop_layer(c,t,l)  }end_generic_loop_2(c,t)


# define begin_cnz_loop(c,t)         begin_generic_loop_1(c,t,THREAD_N_ELEMENTS_INT(t)+THREAD_N_ELEMENTS_LAYER(t,LAYER_PRIMARY)){
# define   end_cnz_loop               }end_generic_loop_1
# define begin_cnz_loop_int(c,t)     begin_generic_loop_1(c,t,THREAD_N_ELEMENTS_INT(t)){
# define   end_cnz_loop_int           }end_generic_loop_1
# define begin_cnz_loop_ext(c,t)     begin_generic_loop_2(c,t,THREAD_N_ELEMENTS_INT(t),thread_layer_last(t,MAX_LAYER)){
# define   end_cnz_loop_ext           }end_generic_loop_2

# define begin_fnz_loop_int(c,t)     begin_generic_loop_1(c,t,THREAD_N_ELEMENTS_INT(t)){
# define   end_fnz_loop_int           }end_generic_loop_1
# define begin_fnz_loop(c,t)         begin_fnz_loop_int(c,t)
# define   end_fnz_loop              end_fnz_loop_int
# define begin_fnz_loop_ext(c,t)     begin_generic_loop_2(c,t,THREAD_N_ELEMENTS_INT(t),thread_layer_last(t,MAX_LAYER)){
# define   end_fnz_loop_ext           }end_generic_loop_2
#if USE_FEMCORE
# define begin_cinz_loop(in,t)       begin_generic_loop_1(in,t,THREAD_N_ELEMENTS_INT(t)+THREAD_N_ELEMENTS_LAYER(t,LAYER_PRIMARY)){
# define   end_cinz_loop               }end_generic_loop_1
#endif

# if RP_HANG
# define thread_layer_new_first(t,nl) thread_layer_first(t,(N_LAYER/2)+(nl))
# define thread_layer_new_last(t,nl)  thread_layer_last(t,(N_LAYER/2)+(nl))
# define begin_c_loop_layer_new(c,t,nl) begin_c_loop_layer(c,t,(N_LAYER/2)+(nl))
# define   end_c_loop_layer_new           end_c_loop_layer
# define begin_f_loop_layer_new(f,t,nl) begin_f_loop_layer(f,t,(N_LAYER/2)+(nl))
# define   end_f_loop_layer_new           end_f_loop_layer
# endif

/* loop macros for overset discretization - parallel - start */
/* faces */
# define begin_f_loop_active_int(f,t)    begin_generic_loop_4(f,t,THREAD_N_ELEMENTS_INT(t),(!OVERSET_SOLVE_FACE_P(f,t) || !CONTACT_ZONE_SOLVE_FACE_P(f,t) || !SOLVE_NARROW_GAP_FACE_P(f,t)) ) /* strategically replaces begin_f_loop in discretization code  */
# define   end_f_loop_active_int(f,t)      end_generic_loop_4(f,t)
# define begin_f_loop_active             begin_f_loop_active_int         /* mirrors begin_f_loop and begin_f_loop_int only skipping overset interface faces  */
# define   end_f_loop_active               end_f_loop_active_int
/* cells  */
/* cell loop over regular exterior skipping dead cells - replaces begin_c_loop */
# define begin_c_loop_active(c,t)   begin_generic_loop_4(c,t,(THREAD_N_ELEMENTS_INT(t)+THREAD_N_ELEMENTS_LAYER(t,LAYER_PRIMARY)),(OVERSET_DEAD_CELL_P(c,t) || SKIP_CONTACT_ZONE_CELL_P(c,t)  || SKIP_NARROW_GAP_CELL_P(c,t) ))
# define   end_c_loop_active(c,t)     end_generic_loop_4(c,t)
/* cell loop over interior(parallel context) skipping dead cells - replaces begin_c_loop_int */
# define begin_c_loop_active_int(c,t)  begin_generic_loop_4(c,t,THREAD_N_ELEMENTS_INT(t),(OVERSET_DEAD_CELL_P(c,t) || SKIP_CONTACT_ZONE_CELL_P(c,t)) || SKIP_NARROW_GAP_CELL_P(c,t))
# define   end_c_loop_active_int(c,t)    end_generic_loop_4(c,t)
/* cell loops over just the regular discretization cells, skip receptors and dead cells  */
#define begin_c_loop_solve(c,t)     begin_generic_loop_4(c,t,THREAD_N_ELEMENTS_INT(t)+THREAD_N_ELEMENTS_LAYER(t,LAYER_PRIMARY),\
                                                                (OVERSET_RECEPTOR_CELL_P(c,t) || OVERSET_DEAD_CELL_P(c,t) || SKIP_CONTACT_ZONE_CELL_P(c,t) || SKIP_NARROW_GAP_CELL_P(c,t) ))
/* cell loops over just interior(parallel) regular discretization cells, skip receptors and dead cells */
#define begin_c_loop_solve_int(c,t) begin_generic_loop_4(c,t,THREAD_N_ELEMENTS_INT(t),\
                                                                (OVERSET_RECEPTOR_CELL_P(c,t) || OVERSET_DEAD_CELL_P(c,t) || SKIP_CONTACT_ZONE_CELL_P(c,t) || SKIP_NARROW_GAP_CELL_P(c,t) ))
#define   end_c_loop_solve_int(c,t)   end_generic_loop_4(c,t)
#define   end_c_loop_solve(c,t)       end_generic_loop_4(c,t)
/* overset exterior(parallel) cell loops for receptors */

/*regular exterior */
#define begin_c_loop_receptor_rext(e,t) begin_generic_loop_5(e,t,\
                                                                     thread_layer_first(t,LAYER_PRIMARY),thread_layer_last(t,LAYER_PRIMARY),\
                                                                     (OVERSET_RECEPTOR_CELL_P(e,t) && !SKIP_CONTACT_ZONE_CELL_P(e,t) && !SKIP_NARROW_GAP_CELL_P(e,t) ))
/*extended exterior */
#define begin_c_loop_receptor_ext(e,t) begin_generic_loop_5(e,t,THREAD_N_ELEMENTS_INT(t),thread_layer_last(t,MAX_LAYER),\
                                                                    (OVERSET_RECEPTOR_CELL_P(e,t) && !SKIP_CONTACT_ZONE_CELL_P(e,t) && !SKIP_NARROW_GAP_CELL_P(e,t) ))
#define   end_c_loop_receptor_rext(e,t)  end_generic_loop_5(e,t)
#define   end_c_loop_receptor_ext(e,t)   end_generic_loop_5(e,t)

/* loop macros for overset discretization - parallel - end */
#endif

/* solution variable loops */
#define spe_loop(ns,nspe)for(ns=0;ns<nspe;++ns)
#define dpm_spe_loop(ns,nspe)for(ns=0;ns<MIN(nspe,MAX_SPE_EQNS);++ns)

#define f_edge_loop(f,t,n)for(n=0;n<F_NEDGES(f,t);++n)
#define f_node_loop(f,t,n)for(n=0;n<F_NNODES(f,t);++n)
#define reversed_f_node_loop(f,t,n)for(n=F_NNODES(f,t)-1;n>=0;--n)
#define c_node_loop(c,t,n)for(n=0;n<C_NNODES(c,t);++n)
#define c_face_loop(c,t,n)for(n=0;n<C_NFACES(c,t);++n)
#define reversed_c_face_loop(c,t,n)for(n=C_NFACES(c,t)-1;n>=0;--n)

#define fsp_node_loop(_fsp,_n)for(_n=0;_n<FSP_NNODES(_fsp);++_n)
#define csp_node_loop(_csp,_n)for(_n=0;_n<CSP_NNODES(_csp);++_n)
#define csp_face_loop(_csp,_n)for(_n=0;_n<CSP_NFACES(_csp);++_n)

#define F_NKIDS(f,t)Face_Type_Nkids(F_TYPE(f,t))
#define C_NKIDS(c,t)Cell_Type_Nkids(C_TYPE(c,t))
#define C_NKIDS_PUMA(c,t)Cell_Nkids_PUMA(c,t)
#define f_child_loop(f,t,n)for(n=0;n<F_NKIDS(f,t);++n)
#define c_child_loop(c,t,n)for(n=0;n<C_NKIDS(c,t);++n)
#if RP_3D
#define edge_child_loop(e,n)for(n=0;n<2;++n)
#define reverse_edge_child_loop(e,n)for(n=1;n>=0;--n)
#endif
#define f_si_child_loop(f,t,n)for(n=0;n<F_SI_NCHILDS(f,t);++n)
#define       ALLOCATED_SI_CHILD_P(t) (SLIDING_BOUNDARY_THREAD_P((t)) && SV_ALLOCATED_P((t), SV_NCHILDS))
#define    ALLOCATED_SI_CHILDREN_P(t) (SLIDING_BOUNDARY_THREAD_P((t)) && SV_ALLOCATED_P((t), SV_CHILDS))
#define ALLOCATED_SI_CHILD_THRDS_P(t) (SLIDING_BOUNDARY_THREAD_P((t)) && SV_ALLOCATED_P((t), SV_CHILD_THREADS))

/* loop through child faces if present, otherwise return face */
#define single_or_child_face_loop(f, tf, fp, tfp, kid)                         \
   for (kid = 0,                                                               \
          f =  PARENT_FACE_THREAD_P(tfp) ?        F_CHILD(fp, tfp, 0) :  fp,   \
         tf =  PARENT_FACE_THREAD_P(tfp) ? F_CHILD_THREAD(fp, tfp, 0) : tfp;   \
        kid < (PARENT_FACE_THREAD_P(tfp) ?        F_NKIDS(fp, tfp)    :   1);  \
        ++kid,                                                                 \
          f =  PARENT_FACE_THREAD_P(tfp) ?        F_CHILD(fp, tfp, kid) : fp,  \
         tf =  PARENT_FACE_THREAD_P(tfp) ? F_CHILD_THREAD(fp, tfp, kid) : tfp) \
     if (!NULL_FACE_P(f) && NNULLP(tf))

#define      FACE_HAS_SI_CHILDREN_P(f, t) (   ALLOCATED_SI_CHILDREN_P((t)) && NNULLP(F_SI_CHILDS(       (f), (t))))
#define FACE_HAS_SI_CHILD_THREADS_P(f, t) (ALLOCATED_SI_CHILD_THRDS_P((t)) && NNULLP(F_SI_CHILD_THREADS((f), (t))))

#define single_or_child_or_sichild_face_loop(f, tf, fp, tfp, kid) \
   for (kid = 0,                                                  \
          f =  PARENT_FACE_THREAD_P(    tfp) ?           F_CHILD(fp, tfp, 0) :        \
             FACE_HAS_SI_CHILDREN_P(fp, tfp) ?        F_SI_CHILD(fp, tfp, 0) : fp,    \
         tf =  PARENT_FACE_THREAD_P(    tfp) ?    F_CHILD_THREAD(fp, tfp, 0) :        \
        FACE_HAS_SI_CHILD_THREADS_P(fp, tfp) ? F_SI_CHILD_THREAD(fp, tfp, 0) : tfp;   \
        kid < (PARENT_FACE_THREAD_P(    tfp) ?           F_NKIDS(fp, tfp)    :        \
               ALLOCATED_SI_CHILD_P(    tfp) ?      F_SI_NCHILDS(fp, tfp)    :   1);  \
        ++kid,                                                                        \
          f =  PARENT_FACE_THREAD_P(    tfp) ?           F_CHILD(fp, tfp, kid) :      \
             FACE_HAS_SI_CHILDREN_P(fp, tfp) ?        F_SI_CHILD(fp, tfp, kid) : fp,  \
         tf =  PARENT_FACE_THREAD_P(    tfp) ?    F_CHILD_THREAD(fp, tfp, kid) :      \
        FACE_HAS_SI_CHILD_THREADS_P(fp, tfp) ? F_SI_CHILD_THREAD(fp, tfp, kid) : tfp) \
     if (!NULL_FACE_P(f) && NNULLP(tf))



#define PREV_INDEX(max,i) (i == 0 ? max-1 : i-1)
#define NEXT_INDEX(max,i) (i == max-1 ? 0 : i+1)

/* partition loop */
#if !RP_NODE
# define partition_loop(d,p)for((p)=0;(p)<ACTIVE_PARTITION_COUNT(d);++(p))
#else
# define partition_loop(d,p)for((p)=myid; (p)==myid; (p) = -1)
#endif

/* loop through a linked, NULL terminated list */
/* The udf interpreter can't handle structure references.
 * Turn them into macros */
#define loop(p,init)for((p)=(init);NULL!=(p);(p)=THREAD_NEXT(p))
#define double_loop(p1,init1,p2,init2)for((p1)=(init1),(p2)=(init2); NULL!=(p1) && NULL!=(p2); (p1)=THREAD_NEXT(p1),(p2)=THREAD_NEXT(p2))

/* face and cell status */
enum
{
  REFUSE = 1,
  ACTIVE,
  CHARGE,
  BRIDGE,
  PARENT,
  SHADOW,
  CHILD,
  CHILD_W_PARENT
};

/* face and cell flags */
#define C_FLAGS(c,t)   FAST_C_STORAGE_UI(c,t,SV_FLAGS)
#define F_FLAGS(e,t) C_FLAGS(e,t)
#define C_FLAG(c,t,mask) (C_FLAGS(c,t) & (mask))
#define F_FLAG(e,t,mask) C_FLAG(e,t,mask)
#define SET_C_FLAGS(c,t,mask)  (C_FLAGS(c,t) |= (mask))
#define SET_F_FLAGS(e,t,mask) SET_C_FLAGS(e,t,mask)
#define CLEAR_C_FLAGS(c,t,mask) (C_FLAGS(c,t) &= ~(mask))
#define CLEAR_F_FLAGS(e,t,mask) CLEAR_C_FLAGS(e,t,mask)

#define SET_V_FLAGS(v,mask) (NODE_FLAGS(v) |= (mask))
#define CLEAR_V_FLAGS(v,mask) (NODE_FLAGS(v) &= ~(mask & ~USED_NODE))
#define NODE_FLAG(v,mask) (NODE_FLAGS(v) & (mask))
#define NODE_FLAG_EXACT(v,mask) ( ( NODE_FLAGS(v) & (mask) ) == mask)

#define SET_V_INT(v) SET_V_FLAGS(v,V_FLAGS_INT)
#define CLEAR_V_INT(v) CLEAR_V_FLAGS(v,V_FLAGS_INT)
#define V_IS_INT(v) NODE_FLAG(v,V_FLAGS_INT)

#define SET_V_VST(v) SET_V_FLAGS(v,V_FLAGS_VST)
#define CLEAR_V_VST(v) CLEAR_V_FLAGS(v,V_FLAGS_VST)
#define V_IS_VST(v) NODE_FLAG(v,V_FLAGS_VST)

#define SET_V_CNR(v) SET_V_FLAGS(v,V_FLAGS_CNR)
#define CLEAR_V_CNR(v) CLEAR_V_FLAGS(v,V_FLAGS_CNR)
#define V_IS_CNR(v) NODE_FLAG(v,V_FLAGS_CNR)

/*these mecros are used only to mark the boundary cells;
  required by multidimensional limiter and node based reconstruction*/
#define C_FLAGS_CELL_MARK(c,t)  FAST_C_STORAGE_UI(c,t,SV_FLAGS_CELL_MARK)
#define C_FLAG_CELL_MARK(c,t,mask) (C_FLAGS_CELL_MARK(c,t) & (mask))
#define SET_C_FLAGS_CELL_MARK(c,t,mask)  (C_FLAGS_CELL_MARK(c,t) |= (mask))
#define CLEAR_C_FLAGS_CELL_MARK(c,t,mask) (C_FLAGS_CELL_MARK(c,t) &= ~(mask))
#define SET_CELL_MARK(c,t,mask)  (C_FLAGS_CELL_MARK(c,t) = (mask))
#define CLEAR_CELL_MARK(c,t,mask)  (C_FLAGS_CELL_MARK(c,t) = (mask)&~(mask))

#define NODE_VISITED_FLAG TMP_NODE_FLAG
#define SET_NODE_VISITED(v) SET_V_FLAGS(v, NODE_VISITED_FLAG)
#define CLEAR_NODE_VISITED(v) CLEAR_V_FLAGS(v,NODE_VISITED_FLAG)
#define NODE_IS_VISITED(v)  NODE_FLAG(v,NODE_VISITED_FLAG)

#define OLD_NODE_COORDS_STORED(v)(NODE_FLAG(v,OLD_COORDS_STORED))
#define OLD_NODE_COORDS_NOT_STORED(v)(!NODE_FLAG(v,OLD_COORDS_STORED))

#if RP_POLYHEDRA
#define THREAD_NODE_WT(t)      (t)->node_weight_manager[0]
#define THREAD_NODE_WT_GX(t)   (t)->node_weight_manager[1]
#define THREAD_NODE_WT_GY(t)   (t)->node_weight_manager[2]
# if RP_3D
#define THREAD_NODE_WT_GZ(t)   (t)->node_weight_manager[3]
# endif
#endif

#define EVAL_FLAG(a,f)   ((a)&(f))
#define SET_FLAGS(a,f)   (a)|=(f)
#define CLEAR_FLAGS(a,f) (a)&=~(f)

#define START_SCHEME_STACK(_result) \
{ \
   size_t _offset = Save_Stack(); \
   Push_Stack(_result)

#define END_SCHEME_STACK(_result) \
   Restore_Stack(_offset); \
}

#include "msn.h"


#if USE_INT64
#define PRI_CXIDX "I64d"
#else
#define PRI_CXIDX "d"
#endif

#endif /* _FLUENT_MEM_H */
