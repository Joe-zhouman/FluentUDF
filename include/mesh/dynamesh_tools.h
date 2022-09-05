/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DYNAMESH_TOOLS_H
#define _FLUENT_DYNAMESH_TOOLS_H

#include "quaternion.h"
#include "entity.h"   /* Thread */
#include "metric.h"

typedef struct dynamic_thread_rigid_body_state
{
  real cg[3];                              /* center of gravity
                                              position wrt global */
  quaternion q;                            /* orientation quaternion */
  real theta[3];                           /* orientation angles wrt global,
                                              Euler angles for 6-dof */
  real v_cg[3];                            /* instantaneous cg velocity
                                              vector */
  real omega_cg[3];                        /* instantaneous cg angular
                                              velocity vector */
  real acc_cg[3];                          /* instantaneous
                cg acceleration vector */
  real alpha_cg[3];                        /* instantaneous cg angular
                acceleration vector */
  real dir[3];                             /* direction of motion */

  real W[3];                               /* Convective angular velocity */
  real A[3];                               /* Convective angular acceleration */
  real torque[3];                          /* Torque */
} Dynamic_Thread_Rigid_Body_State;

typedef struct prism_parameters
{
  int  offset_method;                      /* prism layer offset method */
  real h;                                  /* first height for constant offset
                                              method */
  real ar;                                 /* first aspect ratio for aspect
                                              ratio offset method */
  int  nlayer;                             /* number of prism layers */
  real growth_rate;                        /* geometric growth rate */
} Prism_Parameters;


typedef struct dynamic_thread_struct
{
  Dynamic_Thread_Rigid_Body_State current_state;
  Dynamic_Thread_Rigid_Body_State tmp_state;
  Dynamic_Thread_Rigid_Body_State init_state;

  real dir_ref[3];                         /* reference direction of motion */
  real dir_prev[3];                        /* previous direction of motion */
  real axis[3];                            /* body-fixed axis of motion */
  real refo[3];                            /* reference point */

  real len[3];                             /* length scales (s0, s1, skew) */
  real h[2];                               /* (hmin) (hmax), if applicable */

  real geom_origin[3];                     /* geom.: origin */
  real geom_axis[3];                       /* geom.: axis/normal */
  real geom_radius;                        /* geom.: radius */
  char geometry_name[132];                 /* geometry of geometry function */
  cxboolean geom_feature_p;                /* geom.: use feature detection */
  real geom_feature_angle;                 /* geom.: feature angle */

  cxboolean sop_comp;                      /* solver options for system coupling/six dof switch */
  real sop_scale;                          /* solver option scaling factor */
  char sop_type_name[132];                 /* solver option type name: ap, cell */
  int  sop_type;                           /* 0-volume-based, 1-coefficient-based, 2-udf (not implemented yet) */

  int layer[2];                            /* layering action */
  real layer_factor;                       /* layering split/collapse factor */

  int type;                                /* dynamic zone type */
  int udf_type;                            /* mover, motion, 6DOF */
  int face_remesh_count;                   /* remesh counter */
  int face_remesh_action;                  /* split or collapse */

  cxboolean sliding;                       /* allow nodes to slide/move? */
  cxboolean remesh;                        /* allow faces/cells to be remesh? */
  cxboolean layering;                      /* allow layering? */
  cxboolean moving;                        /* freeze node motion? */
  cxboolean remesh_globals_p;              /* use global remesh parameters */
  int sliding_method;                      /* method to slide */
  int sliding_elements;                    /* spring smoothing element type */
  int remeshing_method;                    /* method(s) to remesh */
  cxboolean boundary_layer_deform;         /* deform/move adjacent prisms
                                              with boundary */
  cxboolean user_defined_deform;           /* allow deformation of user defined
                                              zones */
  cxboolean bc_exclude_motion;             /* option to exclude boundary motion
                                              in boundary condition */

  char profile_udf_name[132];              /* udf or profile name */
  void (*update)();                        /* pointer to motion function */

  struct thread_struct *thread;            /* face/cell thread */

  cxboolean separate_region;               /* remesh region separately? */
  int nloops;                              /* number of moving loops */
  struct edge_loop_struct *loops;          /* loop data structure */
  struct objp_struct *lnodes;              /* pointer to loop nodes */

  cxboolean sdof_p;                        /* use 6DOF to compute motion */
  cxboolean sdof_contribute_p;             /* 6DOF: contribution of thread */

  cxboolean perdisp_p;                     /* use Periodic Displacement to compute motion */
  cxboolean surf_rev_done;                 /* Building surface of revolution done */
  int trim_size;                           /* number of interpolating points for surf revolution */
  real *axcrd;                             /* axial coordinate for surf of revolution */
  real *radcrd;                            /* radial coordinate for surf of revolution */

  cxboolean nested_p;
  struct thread_struct *nest_thread;       /* udf motion is specified on top of the motion of nest_thread */
  cxboolean nested_local_rot_p;            /* relative motion is specifed in local */
  cxboolean nested_local_tran_p;     /* coordinates or absolute coordinates */

  char h_udf_name[2][64];                  /* udf name for non-constant layer
                                              height [0], [1] (corresponding
                                              to height0 and height1) */

  char contact_udf_name[64];               /* UDF name for contact detection */

  real (*tmp_cg)[3];
  real *tmp_theta;
  real tmp_omega[3];                       /* zone-motion variables */

  unsigned int update_state;               /* indicates if thread has been
                                              remeshed, smoothed, etc. */

  real gocart_param[5];                    /* GoCart remeshing parameters
                (max, growth rate, skew,
                aspect ratio, remesh interval) */
  cxboolean gocart_prisms_p;               /* remesh GoCart with inflation
                                              layers */
  Prism_Parameters gocart_prism_param;     /* GoCart prism parameters */

  real tmp_r1;                             /* temporary memory */
  real tmp_r2;
  int tmp_i1;

  struct dynamic_thread_struct *next;      /* pointer to next */
} Dynamic_Thread;


typedef struct rb_state_struct
{
  real cg[3];
  quaternion q;

  real vel[3];
  real omega[3];

  real acc[3];
  real alpha[3];

  real theta[3];

  real W[3], A[3], torque[3];

} rb_state;

#define RB_CG(s)               ((s)->cg)
#define RB_Q(s)                ((s)->q)
#define RB_VEL(s)              ((s)->vel)
#define RB_OMEGA(s)            ((s)->omega)
#define RB_ACC(s)              ((s)->acc)
#define RB_ALPHA(s)            ((s)->alpha)
#define RB_THETA(s)            ((s)->theta)
#define RB_W(s)                ((s)->W)
#define RB_A(s)                ((s)->A)
#define RB_TORQUE(s)           ((s)->torque)

#define DT_THREAD_NEXT(s)      ((s)->next)
#define DT_THREAD(s)           ((s)->thread)

#define DT_RB_CURR_STATE(s)    ((s)->current_state)
#define DT_CG(s)               ((s)->current_state.cg)
#define DT_Q(s)                ((s)->current_state.q)
#define DT_VEL_CG(s)           ((s)->current_state.v_cg)
#define DT_OMEGA_CG(s)         ((s)->current_state.omega_cg)
#define DT_ACC_CG(s)           ((s)->current_state.acc_cg)
#define DT_ALPHA_CG(s)         ((s)->current_state.alpha_cg)
#define DT_THETA(s)            ((s)->current_state.theta)
#define DT_DIR(s)              ((s)->current_state.dir)
#define DT_W(s)                ((s)->current_state.W)
#define DT_A(s)                ((s)->current_state.A)
#define DT_TORQUE(s)           ((s)->current_state.torque)

#define DT_RB_INIT_STATE(s)    ((s)->init_state)
#define DT_RB_TMP_STATE(s)     ((s)->tmp_state)

#define DT_INIT_CG(s)          ((s)->init_state.cg)
#define DT_INIT_Q(s)           ((s)->init_state.q)
#define DT_INIT_THETA(s)       ((s)->init_state.theta)
#define DT_INIT_VEL_CG(s)      ((s)->init_state.v_cg)
#define DT_INIT_OMEGA_CG(s)    ((s)->init_state.omega_cg)
#define DT_INIT_ACC_CG(s)      ((s)->init_state.acc_cg)
#define DT_INIT_ALPHA_CG(s)    ((s)->init_state.alpha_cg)
#define DT_INIT_DIR(s)         ((s)->init_state.dir)

#define DT_DIR_REF(s)          ((s)->dir_ref)
#define DT_DIR_PREV(s)         ((s)->dir_prev)
#define DT_AXIS(s)             ((s)->axis)
#define DT_GEOM_ORIGIN(s)      ((s)->geom_origin)
#define DT_GEOM_AXIS(s)        ((s)->geom_axis)
#define DT_GEOM_RADIUS(s)      ((s)->geom_radius)
#define DT_FEATURE_P(s)        ((s)->geom_feature_p)
#define DT_FEATURE_ANGLE(s)    ((s)->geom_feature_angle)
#define DT_UPDATE_FNC(s)       ((s)->update)
#define DT_LEN(s)              ((s)->len)
#define DT_MIN_LSCALE(s)       (DT_REMESH_GLOBALS_P(s)?         \
                                remesh_min_lscale:(s)->len[0])
#define DT_MAX_LSCALE(s)       (DT_REMESH_GLOBALS_P(s)?        \
                                remesh_max_lscale:(s)->len[1])
#define DT_MAX_SKEW(s)         (DT_REMESH_GLOBALS_P(s)?                \
                                (CELL_THREAD_P(DT_THREAD(s))?           \
                                 remesh_max_cell_skew:remesh_max_face_skew): \
                                (s)->len[2])
#define DT_REFO(s)             ((s)->refo)
#define DT_PU_NAME(s)          ((s)->profile_udf_name)
#define DT_VLIST(s)            ((s)->lnodes)
#define DT_TYPE(s)             ((s)->type)
#define DT_UDF_TYPE(s)         ((s)->udf_type)
#define DT_HEIGHT(s)           ((s)->h)
#define DT_SLIDE_P(s)          ((s)->sliding)
#define DT_SLIDE_METHOD(s)     ((s)->sliding_method)
#define DT_SLIDE_ELEMENTS(s)   ((s)->sliding_elements)
#define DT_REMESH_P(s)         ((s)->remesh)
#define DT_REMESH_METHOD(s)    ((s)->remeshing_method)
#define DT_REMESH_GLOBALS_P(s) ((s)->remesh_globals_p)
#define DT_LAYER_P(s)          ((s)->layering)
#define DT_BL_DEFORM_P(s)      ((s)->boundary_layer_deform)
#define DT_UDF_DEFORM_P(s)     ((s)->user_defined_deform)
#define DT_BC_EXCLUDE_MOTION_P(s) ((s)->bc_exclude_motion)
#define DT_COUNTER(s)          ((s)->face_remesh_count)
#define DT_LOOPS(s)            ((s)->loops)
#define DT_NLOOPS(s)           ((s)->nloops)
#define DT_LAYER(s)            ((s)->layer)
#define DT_LAY_FAC(s)          ((s)->layer_factor)
#define DT_RACTION(s)          ((s)->face_remesh_action)
#define DT_GEOM_NAME(s)        ((s)->geometry_name)
#define DT_REMESH_SEP(s)       ((s)->separate_region)
#define DT_SDOF_P(s)           ((s)->sdof_p)
#define DT_PERDISP_P(s)        ((s)->perdisp_p)
#define DT_SDOF_CONT_P(s)      ((s)->sdof_contribute_p)
#define DT_HIDEAL_UDF(s)       ((s)->h_udf_name)
#define DT_CONTACT_UDF(s)      ((s)->contact_udf_name)
#define DT_UPDATE_STATE(s)     ((s)->update_state)
#define DT_RTMP1(s)            ((s)->tmp_r1)
#define DT_RTMP2(s)            ((s)->tmp_r2)
#define DT_ITMP1(s)            ((s)->tmp_i1)
#define DT_GOCART(s)           ((s)->gocart_param)
#define DT_GOCART_MAX(s)       ((s)->gocart_param[0])
#define DT_GOCART_RATE(s)      ((s)->gocart_param[1])
#define DT_GOCART_QUALITY(s)   ((s)->gocart_param[2])
#define DT_GOCART_RATIO(s)     ((s)->gocart_param[3])
#define DT_GOCART_INTERVAL(s)  ((s)->gocart_param[4])
#define DT_GOCART_PRISMS_P(s)  ((s)->gocart_prisms_p)
#define DT_GOCART_PRISM_TYPE(s) ((s)->gocart_prism_param.offset_method)
#define DT_GOCART_PRISM_H(s)   ((s)->gocart_prism_param.h)
#define DT_GOCART_PRISM_AR(s)  ((s)->gocart_prism_param.ar)
#define DT_GOCART_PRISM_NLAYER(s) ((s)->gocart_prism_param.nlayer)
#define DT_GOCART_PRISM_RATE(s) ((s)->gocart_prism_param.growth_rate)
#define DT_SOP_SWITCH(s)       ((s)->sop_comp)
#define DT_SOP_METHOD_NAME(s)  ((s)->sop_type_name)
#define DT_SOP_METHOD(s)       ((s)->sop_type)
#define DT_SOP_SCALE(s)        ((s)->sop_scale)
#define DT_NESTED_P(s)         ((s)->nested_p)
#define DT_NEST_THREAD(s)      ((s)->nest_thread)
#define DT_NEST_LOC_ROT_P(s)   ((s)->nested_local_rot_p)
#define DT_NEST_LOC_TRAN_P(s)  ((s)->nested_local_tran_p)

typedef struct edge_loop_struct
{
  real gmin;                  /* maximum height of marked faces */
  real gmax;                  /* minimum height of marked faces */
  real ave_h;                 /* average height */
  real min_h;                 /* minimum height */
  real prism_size_fac;        /* prism cap size factor */
  real loop_normal[3];        /* loop normal */
  real normal_dir[3];         /* direction in which face height is computed */
  int method;                 /* insertion method */
  int flag;                   /* loop action */
  int id;                     /* id of cells marked by loop */
  int ncells;                 /* number of cells associated with loop */
  struct thread_struct *tf;
  struct thread_struct *prism_tc;
  struct objp_struct *lnodes; /* list of nodes associated with loop */
  struct objp_struct *lts;    /* list of adjacent deforming threads */
} Loop;

#define L_VLIST(l)      ((l)->lnodes)
#define L_LTF(l)        ((l)->lts)
#define L_TF(l)         ((l)->tf)
#define L_GMAX(l)       ((l)->gmax)
#define L_GMIN(l)       ((l)->gmin)
#define L_AVE_H(l)      ((l)->ave_h)
#define L_MIN_H(l)      ((l)->min_h)
#define L_PRISM_SFAC(l) ((l)->prism_size_fac)
#define L_PRISM_TC(l)   ((l)->prism_tc)
#define L_NORMAL(l)     ((l)->loop_normal)
#define L_NORMAL_DIR(l) ((l)->normal_dir)
#define L_METHOD(l)     ((l)->method)
#define L_FLAG(l)       ((l)->flag)
#define L_ID(l)         ((l)->id)
#define L_NCELLS(l)     ((l)->ncells)

/* Update enumerants */
enum
{
  DT_UPDATE_DPM,
  DT_UPDATE_NCI,
  DT_UPDATE_PMN,
  DT_UPDATE_SHELL,
  DT_UPDATE_OVERSET,
  DT_UPDATE_EXPRESSION,
  MAX_DT_UPDATES
};

/* region face remeshing type */
enum
{
  LOOP_SKIP = 0,
  LOOP_INSERT,
  LOOP_REMOVE,
  LOOP_REFINE
};

/* dynamic zone type */
enum
{
  DT_UNSPECIFIED_MOTION = -1,
  DT_NO_MOTION,
  DT_SOLID_BODY_MOTION,
  DT_USER_DEFINED,
  DT_DEFORMING,
  DT_SYSTEM_COUPLING,
  DT_INTRINSIC_COUPLING_MOTION,
  DT_UDF_DEFORM_BASE
};

#define DT_NO_MOTION_P(_dt) (DT_TYPE (_dt) == DT_NO_MOTION)
#define DT_SOLID_BODY_MOTION_P(_dt) (DT_TYPE (_dt) == DT_SOLID_BODY_MOTION)
#define DT_INTRINSIC_COUPLING_MOTION_P(_dt) (DT_TYPE (_dt) == DT_INTRINSIC_COUPLING_MOTION)
#define DT_DEFORMING_P(_dt) (DT_TYPE (_dt) == DT_DEFORMING || \
                             DT_UDF_DEFORM_P(_dt))
#define DT_USER_DEFINED_P(_dt) (DT_TYPE (_dt) == DT_USER_DEFINED)
#define DT_SYSTEM_COUPLING_P(_dt) (DT_TYPE (_dt) == DT_SYSTEM_COUPLING)
#define DT_USER_DEFINED_OR_ENABLED_SYSTEM_COUPLING_P(_dt) \
  (DT_USER_DEFINED_P (_dt) || \
   (DT_SYSTEM_COUPLING_P (_dt) && dynamesh_sc_enabled_p))
#define DT_NO_MOTION_OR_DISABLED_SYSTEM_COUPLING_P(_dt) \
  (DT_NO_MOTION_P (_dt) || \
   (DT_SYSTEM_COUPLING_P (_dt) && !dynamesh_sc_enabled_p))
#define DT_UDF_DEFORM_BASE_P(_dt)(DT_TYPE(_dt)==DT_UDF_DEFORM_BASE)

/* solver options for dynamic zone */
enum
{
  SOLVER_METHOD_CELL = 1,
  SOLVER_METHOD_AP   = 2
                       /* SOLVER_METHOD_UDF  = 3*/
};

/* sliding method */
enum
{
  DT_SLIDE_OFF =     0,
  DT_SLIDE_SPRING =  1,
  DT_SLIDE_LAPLACE = 2
};

/* smoothing method */
enum
{
  DT_SMOOTH_SPRING =  1,
  DT_SMOOTH_LAPLACE = 2,  /* diffusion-based smoothing, FVM */
  DT_SMOOTH_FEM =     3,  /* diffusion or linear elastic solid smoothing, FEM */
  DT_SMOOTH_RBF =     4
};

/* equation for FEM smoothing */
enum
{
  FEM_SMOOTH_DIFFUSION = 0,
  FEM_SMOOTH_LINELAST = 1
};

/* volume remeshing method */
enum
{
  DT_REMESH_OFF =     0,
  DT_REMESH_REGION =  1,
  DT_REMESH_LOCAL  =  2,
  DT_REMESH_GOCART =  4
};

/* surface remeshing method */
enum
{
  SURF_REMESH_STANDARD =     0,
  SURF_REMESH_IMPROVED =     1,
  SURF_REMESH_SKEW_IMPROVE = 2
};

/* Marking of cells and nodes */
enum
{
  MARK_ALL = 0,
  MARK_BY_REGISTERS = 1
                      /* ,
                       * MARK_FROM_FACES_BY_DISTANCE = 2,
                       * MARK_FROM_FACES_BY_LAYERS = 3
                       */
};

/* dynamic thread update states */
#define DT_STATE_UNCHANGED   0x0000
#define DT_STATE_SMOOTHED    0x0001
#define DT_STATE_REMESHED    0x0002
#define DT_STATE_MIGRATED    0x0004
#define DT_STATE_MOVED       0x0008

#define DT_SET_UPDATE_STATE(_dt,_state) (DT_UPDATE_STATE (_dt) |= (_state))
#define DT_CLEAR_UPDATE_STATE(_dt,_state) (DT_UPDATE_STATE (_dt) &= ~(_state))
#define DT_UPDATE_STATE_P(_dt,_state) (DT_UPDATE_STATE (_dt) & (_state))
#define THREAD_DYNAMIC_MESH_STATE_P(_t,_state) \
  (NNULLP (THREAD_DT (_t)) ? DT_UPDATE_STATE_P (THREAD_DT (_t), _state) : FALSE)

FLUENT_EXPORT void Create_Dynamic_Thread (Domain *, Pointer *);
FLUENT_EXPORT void Delete_Dynamic_Thread (Domain *, Thread *);
FLUENT_EXPORT void Copy_Dynamic_Thread_Rigid_Body_State(
  Dynamic_Thread_Rigid_Body_State *,
  Dynamic_Thread_Rigid_Body_State *);
FLUENT_EXPORT real Dynamic_Thread_Ideal_Length_Scale (Dynamic_Thread *);
FLUENT_EXPORT void Update_Dynamic_Threads_Update_Function (Domain *);
FLUENT_EXPORT void Init_Dynamic_Threads_Update_State (Domain *);
FLUENT_EXPORT Objp *Create_Udf_Deform_Base_Dt(Domain *, Objp *);
FLUENT_EXPORT void Free_Udf_Deform_Base_Dt(Domain *, Objp *);

#if PARALLEL
FLUENT_EXPORT void Exchange_Dynamic_Threads_Update_State (Domain *, cxboolean);
#endif
FLUENT_EXPORT void Free_Dynamic_Mesh (Domain *);

FLUENT_EXPORT void Update_Nested_RB_State (Dynamic_Thread *, rb_state *, quaternion,
                                           real [], real, real);

FLUENT_EXPORT void Dynamic_Mesh_Clear_Sliding_Interfaces (Domain *, cxboolean);
FLUENT_EXPORT void Dynamic_Mesh_Update_Sliding_Interfaces (Domain *);

FLUENT_EXPORT void Init_Dynamic_Mesh (Domain *, cxboolean);
FLUENT_EXPORT void Reset_Motion_Attributes (Domain *);
FLUENT_EXPORT void Free_Dynamic_Mesh_Node_Ids (Domain *);
FLUENT_EXPORT void Set_Void_Dynamic_Mesh_Node_Ids (Domain *);
FLUENT_EXPORT void Copy_Node_Coordinates (Domain *domain, cxboolean);
#if RP_NODE
FLUENT_EXPORT cxboolean Node_Moved_P (Node *);
FLUENT_EXPORT void Set_Node_Moved (Node *);
#endif
FLUENT_EXPORT void Update_Dynamic_Threads (Domain *,
                                           real, real,
                                           cxboolean, cxboolean);
FLUENT_EXPORT void Project_Dynamic_Thread (Domain *, Dynamic_Thread *);
FLUENT_EXPORT void Fill_Dynamic_Mesh_Node_Motion (Domain *);
FLUENT_EXPORT void Get_Min_Max_Volume_On_Thread (Thread *,
                                                 real *, real *, real *);
FLUENT_EXPORT void Get_Min_Max_Length_Scale_On_Thread (Thread *,
                                                       cxboolean, real *,
                                                       real *, real *);
FLUENT_EXPORT void Get_Min_Max_Edge_Length_At_Face_Thread (Domain *, Thread *,
                                                           real *, real *);

FLUENT_EXPORT real Max_Cell_Aspect_Ratio_On_Thread (Thread *, cxboolean);
FLUENT_EXPORT real Max_Cell_Skewness_On_Thread (Thread *, cxboolean, cxboolean);
FLUENT_EXPORT int Count_Skewed_Cells_On_Thread (Thread *, real, real *, real *);
#if RP_3D
FLUENT_EXPORT real Max_Face_Skewness_On_Thread (Thread *);
#endif
FLUENT_EXPORT real Simplex_Max_Ideal_Edge_Length (cell_t, Thread *);
FLUENT_EXPORT real Get_Erosion_Time_Step(Domain *, real, real);
FLUENT_EXPORT cxboolean Check_Dynamic_Mesh (Domain *, cxboolean);
FLUENT_EXPORT void Update_Dynamic_Mesh (Domain *, real);
FLUENT_EXPORT cxboolean Dynamic_Mesh_Check_Motion_Convergence (Domain *);
FLUENT_EXPORT void Update_Dynamic_Mesh_In_Timestep (Domain *, real);
FLUENT_EXPORT cxboolean Dynamic_Mesh_Needs_Extended_Neighborhood (Domain *);
FLUENT_EXPORT void Dynamic_Mesh_Clear_Update (Domain *, cxboolean []);
FLUENT_EXPORT void Dynamic_Mesh_Reset_Update (Domain *, cxboolean []);
FLUENT_EXPORT void Pre_Update_Dynamic_Mesh (Domain *, real, cxboolean,
                                            cxboolean, cxboolean, cxboolean,
                                            cxboolean);
FLUENT_EXPORT void Pre_Update_Dynamic_Mesh_In_Timestep (Domain *, real);
FLUENT_EXPORT void Post_Update_Dynamic_Mesh (Domain *, cxboolean, cxboolean, cxboolean);
FLUENT_EXPORT cxboolean Update_All_Dynamic_Mesh (Domain *, cxboolean, cxboolean);
FLUENT_EXPORT cxboolean Steady_Update_All_Dynamic_Mesh (Domain *);
FLUENT_EXPORT void Update_Dynamic_Mesh_Parameters(Domain *, real, cxboolean);
FLUENT_EXPORT void Update_Dynamic_Threads_State(Domain *, real, real);

FLUENT_EXPORT cxboolean In_Cylinder_Thread_P(Thread *);
FLUENT_EXPORT real Compute_Lift (char *, real, cxboolean);
FLUENT_EXPORT void Modify_Lift (const char *, int, real);
FLUENT_EXPORT void Free_Dynamic_Mesh_Ref_Coords(Domain *);
FLUENT_EXPORT void Alloc_And_Fill_Ref_Coords (Domain *);
FLUENT_EXPORT void Alloc_And_Init_Ref_Coords (Domain *);
FLUENT_EXPORT cxboolean Is_Ref_Coords_Allocated_And_Filled(Domain *);

#if !RP_NODE
FLUENT_EXPORT void Write_File_Motion_History (char *, real, real[3], real[3]);
FLUENT_EXPORT void Get_File_Motion_History_Data_At_Time (char *, real,
                                                         real[3], real[3]);
FLUENT_EXPORT cxboolean Motion_History_File_Exist (char *, char *);
#endif
FLUENT_EXPORT void Free_Motion_History (Domain *, Thread *);
FLUENT_EXPORT void Compute_Motion_History (Domain *, Thread *, int, real, real);
FLUENT_EXPORT void Get_Motion_History (Thread *, real, real *, real *, real *);


FLUENT_EXPORT void Compute_And_Write_Swirl_Tumble (const char *, int, Thread **, int,
                                                   const char *, real [3], real[3],
                                                   real[3], real[3]);

FLUENT_EXPORT void Dynamic_Mesh_Fill_Bridge_Nodes_Of_Cells (Domain *);
FLUENT_EXPORT void Dynamic_Mesh_Free_Bridge_Nodes_Of_Cells (Domain *);
FLUENT_EXPORT void Tag_Adapted_Cells_Adjacent_Moving_Thread (Domain *, Thread *,
                                                             int);

FLUENT_EXPORT void Sort_Element_Array_On_Skewness (void *, Thread *, int);
FLUENT_EXPORT Objp *Sort_Cell_List_On_Skewness (Objp *);
FLUENT_EXPORT cell_t *Fill_Cell_Thread_Array_On_Skewness (Thread *, int *);
#if RP_3D
FLUENT_EXPORT face_t *Fill_Face_Thread_Array_On_Skewness (Thread *, int *);
#endif

#if RP_3D
FLUENT_EXPORT real Cosine_Face_Angle (const face_t, const Thread *,
                                      const face_t, const Thread *);
#endif

FLUENT_EXPORT void Unmark_Face_Threads (Domain *);
FLUENT_EXPORT void Reverse_Dynamic_Thread_Orientation (Dynamic_Thread *);
FLUENT_EXPORT void Assure_Face_Thread_Orientation (Domain *, Thread *);
FLUENT_EXPORT void Reverse_Orientation_Marked_Face_Threads (Domain *);
FLUENT_EXPORT void Reverse_Orientation_Marked_Dynamic_Face_Threads (Domain *);
FLUENT_EXPORT void Contour_Node_Displacement (Thread *);

FLUENT_EXPORT real cell_height (face_t, Thread *, cell_t, Thread *, cxboolean);
FLUENT_EXPORT void fill_cell_skewness_on_thread (Thread *);
FLUENT_EXPORT void fill_cell_skewness (Domain *);
FLUENT_EXPORT int Get_Cellfaces_Inzone(cell_t, Thread *, Thread *);
#if RP_3D
FLUENT_EXPORT void fill_face_skewness_on_thread (Thread *);
FLUENT_EXPORT void fill_face_skewness (Domain *);
FLUENT_EXPORT real Evaluate_Face_Skewness (cell_t, Thread *);
#endif

FLUENT_EXPORT void DM_Free_TG_Memory (void);
FLUENT_EXPORT void *DM_Alloc_TG_Memory (size_t);
FLUENT_EXPORT void *DM_Get_TG_Memory (void);

FLUENT_EXPORT void Print_Global_Conserved_Vars (Domain *);
FLUENT_EXPORT void Conserve_Cell_Data (Objp *, Thread *, Objp *, Thread *,
                                       cxboolean);

FLUENT_EXPORT void Init_Cell_Interior_Face_Data (cell_t, Thread *);
FLUENT_EXPORT real Reconstruct_Scalar_From_Cell_At_Position (real *, real (*)[ND_ND],
                                                             cell_t, Thread *, real *);

FLUENT_EXPORT void Model_Initialize_dynamesh (void);
FLUENT_EXPORT void Download_Dynamic_Mesh_Parameters (void);
FLUENT_EXPORT void Download_All_Dynamic_Mesh_Parameters (void);

FLUENT_EXPORT int Prism_Layer_Count(Domain *, Thread *, int, cxboolean);
FLUENT_EXPORT cxboolean Valid_Prism_Layer_Base_Thread(Thread *, int);
FLUENT_EXPORT cxboolean Check_Deforming_Cell_Threads(Domain *, Objp *, cxboolean);
FLUENT_EXPORT cxboolean Check_Smoothing_Cell_Threads(Domain *, cxboolean);
FLUENT_EXPORT void Relax_Node_Motion(Node *v);

FLUENT_EXPORT void Set_Thread_Deforming_Flag(Thread *);
FLUENT_EXPORT cxboolean Cell_Thread_Can_Have_Deforming_Flag(Thread *);

FLUENT_EXPORT void PerDisp_Needs_Update(cxboolean);
FLUENT_EXPORT void Initialize_Periodic_Motion (Domain *);

FLUENT_EXPORT cxboolean Dynamic_Mesh_Check_Moving_Threads (Domain *);
FLUENT_EXPORT cxboolean Dynamic_Mesh_Possible (Domain *);

FLUENT_EXPORT void Set_Thread_Nodes(Thread *);

/* remeshing methods */
#define REMESH_UNIDENTIFIED     0x0000
#define REMESH_CELL_LOCAL       0x0001
#define REMESH_CELL_THREAD      0x0002
#define REMESH_GOCART_THREAD    0x0004
#define REMESH_FACE_LOCAL       0x0010
#define REMESH_FACE_REGION      0x0020
#define REMESH_TWO_FIVE_LOCAL   0x0100

#define ENABLE_REMESH_METHOD(method)  (remesh_methods |= (method))
#define DISABLE_REMESH_METHOD(method) (remesh_methods &= ~(method))
#define SET_REMESH_METHOD(method,status) \
  (status ? ENABLE_REMESH_METHOD (method) : DISABLE_REMESH_METHOD (method))
#define CHECK_REMESH_METHOD_P(method) (remesh_methods & (method))

#define IMPROVE_MESH_ALL       0x0001
#define IMPROVE_MESH_ZONE      0x0002
#define AVG_HEIGHT             0x0004
#define ACTUAL_DIST            0x0008
#define TRANSLATION_DIR_CHECK  0x0010
#define LOCAL_DIR              0x0020
#define CUT_LOOPS_AT_CORNERS   0x0040
#define ACCEPT_AVG_SKEW        0x0080
#define BL_NORMAL_DIR          0x0100

#define REMESH_IMPROVEMENT_P(method)(remesh_improvements & (method))

/* number of conserved variables */
# define MAX_NCBVARS 9
#define MAX_NCVARS (MAX_NCBVARS+MAX_SPE_EQNS-1)

/* temporary node data */
#define NODE_LINK   NODE_DL_PREV
#define NODE_DUP    NODE_DL_NEXT

#define LOCAL_LIST(v)  (NODE_TMP_0(v).asObjp)
#define FACE_LIST(v)   (NODE_TMP_1(v).asObjp)

/*used in updating svars during transient cases with layering */
#define F_AREA_MAG_M1(_f,_t) F_STORAGE_R(_f,_t, SV_AREA_MAG_M1)
#define C_VOLUME_M1(_c,_t)   C_STORAGE_R(_c,_t, SV_VOLUME_M1)
#define C_VOLUME_M1_SAFE(c, t, dt) (( ! NULLP(THREAD_STORAGE(t, SV_VOLUME_M1)))  ? C_VOLUME_M1(c,t) : \
                                    ( ! NULLP(THREAD_STORAGE(t, SV_DVOLUME_DT))) ? C_VOLUME(c,t) - CELL_DVOLUME_DT(c,t) * (dt) : \
                                    C_VOLUME(c,t))
#define C_VOLUME_INTERPOLATION(c,t) (SV_ALLOCATED_P_NEW(t,SV_VOLUME_M1)?\
                                     C_VOLUME_M1(c,t):C_VOLUME(c,t))
#define C_VOLUME_INTERPOLATION_M1(c,t,dt) (SV_ALLOCATED_P_NEW(t,SV_DVOLUME_DT)?\
                                           C_VOLUME_INTERPOLATION(c,t)-CELL_DVOLUME_DT(c,t)*(dt):\
                                           C_VOLUME_INTERPOLATION(c,t))

#define DT_GMIN(dt)    DT_HEIGHT(dt)[0]
#define DT_GMAX(dt)    DT_HEIGHT(dt)[1]

/* specific flags that are shared by multiple dynamic mesh subroutines */
#define NEW_FLAG           NEW_ENTITY_FLAG
#define EXT_FLAG           UNREAD_NODE
#define CELL_REMESH_FLAG   INTERNAL_ORIG_NODE
#define FACE_REMESH_FLAG   VISITED_NODE
#define FACE_REVERSED_FLAG HANGING_FACE_NODE
#if PARALLEL
# define PHANTOM_NODE_FLAG KEEP_FLAG
#endif

/* node id: used for TGrid remeshing */
#if RP_3D || PARALLEL || DEBUG
# define NODE_SID(v) N_STORAGE_I (NODE_INDEX (v), NODE_THREAD (v), SV_ID)
#else
# define NODE_SID(v) NODE_TMP_0(v).asInt
#endif

/* node id: used if dynamesh_node_id_p is enabled for code coupling */
#define NODE_DM_ID(v) N_STORAGE_I (NODE_INDEX (v), NODE_THREAD (v), SV_DM_ID)

/* node marks */
#define NODE_NULL       0x0000
#define NODE_FIXED      0x0001
#define NODE_MOVABLE    0x0002
#define NODE_CONTACT    0x0004
#define NODE_MOVED      0x0008
#define NODE_ADAPT      0x0010
#define NODE_DEFORMED   0x0020

#define NODE_SET_NULL(v) (NODE_MARK(v) = NODE_NULL)
#define NODE_SET_MARK(v, mark) (NODE_MARK(v) |= (mark))
#define NODE_CLEAR_MARK(v, mark) (NODE_MARK(v) &= ~(mark))

#define NODE_POS_FIXED(v) \
  (NODE_CLEAR_MARK(v, NODE_MOVED | NODE_MOVABLE | NODE_ADAPT), \
   NODE_SET_MARK(v, NODE_FIXED))
#define NODE_POS_FIXED_P(v) (NODE_MARK(v) & NODE_FIXED)
#define NODE_POS_MOVABLE(v) \
  (NODE_CLEAR_MARK(v, NODE_MOVED | NODE_FIXED | NODE_ADAPT), \
   NODE_SET_MARK(v, NODE_MOVABLE))
#define NODE_POS_NEED_UPDATE(v) (NODE_MARK(v) & NODE_MOVABLE)
#define NODE_POS_UPDATED(v) \
  (NODE_CLEAR_MARK(v, NODE_MOVABLE | NODE_FIXED | NODE_ADAPT), \
   NODE_SET_MARK(v, NODE_MOVED))
#define NODE_POS_UPDATED_P(v) (NODE_MARK(v) & NODE_MOVED)
#define NODE_POS_DEFORMED_P(v) (NODE_MARK(v) & NODE_DEFORMED)
#define NODE_POS_DEFORMED(v) (NODE_SET_MARK(v, NODE_DEFORMED))
#define NODE_POS_DEFORMABLE_P(v) ((NODE_POS_NEED_UPDATE(v) || NODE_POS_UPDATED(v)) && !NODE_POS_DEFORMED_P(v))
#define NODE_POS_CONTACT(v) (NODE_SET_MARK(v, NODE_CONTACT))
#define NODE_POS_CONTACT_P(v) (NODE_MARK(v) & NODE_CONTACT)
#define NODE_POS_ADAPTED_NEED_UPDATE(v) (NODE_SET_MARK(v, NODE_ADAPT))
#define NODE_POS_ADAPTED_NEED_UPDATE_P(v) (NODE_MARK(v) & NODE_ADAPT)

/* identify tri/tet/mixed etc. threads */
#if RP_3D
# define SIMPLEX_FACE TRI_FACE
# define TRI_FACE_THREAD_P(_thread) \
   ((Face_Element_Type)THREAD_ELEMENT_TYPE (_thread) == SIMPLEX_FACE)
# define QUAD_FACE_THREAD_P(_thread) \
   ((Face_Element_Type)THREAD_ELEMENT_TYPE (_thread) == QUAD_FACE)
# define EXTRUDABLE_THREAD_P(_thread) \
   (THREAD_ELEMENT_TYPE(_thread) == WEDGE_CELL || \
    THREAD_ELEMENT_TYPE(_thread) == HEX_CELL || \
    THREAD_ELEMENT_TYPE(_thread) == QUAD_CELL)
#else
# define SIMPLEX_FACE LINEAR_FACE
# define EXTRUDABLE_THREAD_P(_thread) FALSE
#endif
#define TRI_TET_THREAD_P(_thread) \
  ((Cell_Element_Type)THREAD_ELEMENT_TYPE (_thread) == SIMPLEX_CELL)
#define DEFORMABLE_CELL_THREAD_P(_thread) \
  ((((Cell_Element_Type)THREAD_ELEMENT_TYPE (_thread) == SIMPLEX_CELL) || \
    ((Cell_Element_Type)THREAD_ELEMENT_TYPE (_thread) == MIXED_CELL)) && \
   !SHELL_CELL_THREAD_P (_thread))
#define DEFORMABLE_FACE_THREAD_P(_thread) \
  (BOUNDARY_FACE_THREAD_P (_thread) &&                \
   !SHELL_FACE_THREAD_P (_thread) &&                  \
   (DEFORMABLE_CELL_THREAD_P (THREAD_T0 (_thread)) || \
    EXTRUDABLE_THREAD_P (THREAD_T0 (_thread))))
#define REMESHABLE_FACE_THREAD_P(_thread)                               \
  (DEFORMABLE_FACE_THREAD_P(_thread) ||                                 \
   (remesh_poly_p &&                                                    \
    BOUNDARY_FACE_THREAD_P(_thread) &&                                  \
    !SHELL_FACE_THREAD_P(_thread) &&                                    \
    MIXED_OR_POLY_FACE_THREAD_P(_thread)))
#define DEFORMABLE_CELL_P(_c,_t) SIMPLEX_CELL_P (_c, _t)
#define DEFORMABLE_FACE_P(_f,_t) \
  ((Face_Element_Type)F_TYPE (_f, _t) == SIMPLEX_FACE)
#if RP_3D
#define DEFORMING_BOUNDARY_LAYER_THREAD_P(_thread) \
 ((((Cell_Element_Type)THREAD_ELEMENT_TYPE(_thread) == HEX_CELL) || \
   ((Cell_Element_Type)THREAD_ELEMENT_TYPE(_thread) == WEDGE_CELL)) && \
  !SHELL_CELL_THREAD_P (_thread) && \
  (NNULLP (THREAD_DT (_thread)) && (DT_DEFORMING_P(THREAD_DT(_thread))) && \
   DT_SLIDE_P (THREAD_DT (_thread))))
#else
#define DEFORMING_BOUNDARY_LAYER_THREAD_P(_thread) \
 (((Cell_Element_Type)THREAD_ELEMENT_TYPE(_thread) == QUAD_CELL) && \
  (NNULLP (THREAD_DT (_thread)) && (DT_DEFORMING_P(THREAD_DT(_thread))) && \
   DT_SLIDE_P (THREAD_DT (_thread))))
#endif
#if RP_3D
# define PRISMATIC_CELL_P(_c,_tc) \
  (((Cell_Element_Type)C_TYPE(_c,_tc) == HEX_CELL) || \
   ((Cell_Element_Type)C_TYPE(_c,_tc) == WEDGE_CELL))
# define PRISMATIC_BASE_FACE_P(_f,_tf,_c,_tc) \
  ((((Cell_Element_Type)C_TYPE(_c,_tc) == HEX_CELL) && \
    ((Face_Element_Type)F_TYPE(_f,_tf) == QUAD_FACE))    || \
   (((Cell_Element_Type)C_TYPE(_c,_tc) == WEDGE_CELL) && \
    ((Face_Element_Type)F_TYPE(_f,_tf) == TRI_FACE)))
#else
# define PRISMATIC_CELL_P(_c,_tc) \
  ((Cell_Element_Type)C_TYPE(_c,_tc) == QUAD_CELL)
# define PRISMATIC_BASE_FACE_P(_f,_tf,_c,_tc) TRUE
#endif

/* identify GoCart cell threads */
#if RP_3D
# define ACTIVE_GOCART_CELL_THREAD_P(_thread) \
  (NNULLP (THREAD_DT (_thread)) && \
   CELL_THREAD_P (_thread) && \
   (DT_DEFORMING_P(THREAD_DT(_thread))) &&    \
   DT_REMESH_P (THREAD_DT (_thread)) && \
   CHECK_METHOD_BIT (DT_REMESH_METHOD (THREAD_DT (_thread)), DT_REMESH_GOCART))
#else
# define ACTIVE_GOCART_CELL_THREAD_P(_thread) FALSE
#endif

/* check on reasonable size/skewness limits */
#if RP_2D
# define MIN_REASONABLE_CELL_SKEWNESS 0.4
# define MIN_REASONABLE_FACE_SKEWNESS 0.0
#else
# define MIN_REASONABLE_CELL_SKEWNESS 0.7
# define MIN_REASONABLE_FACE_SKEWNESS 0.4
#endif
#define MAX_REASONABLE_SKEWNESS 0.95

#define VALID_SIZE_LIMITS_P(min,max) \
  (min >= 0.0 && max > 0.0 && max > min)
#define VALID_CELL_SKEWNESS_LIMIT_P(skew) \
  (skew >= MIN_REASONABLE_CELL_SKEWNESS && skew <= MAX_REASONABLE_SKEWNESS)
#define VALID_FACE_SKEWNESS_LIMIT_P(skew) \
  (skew >= MIN_REASONABLE_FACE_SKEWNESS && skew <= MAX_REASONABLE_SKEWNESS)
#define VALID_THREAD_SKEWNESS_LIMIT_P(skew,_thread) \
  (CELL_THREAD_P (_thread) ? \
    VALID_CELL_SKEWNESS_LIMIT_P (skew): VALID_FACE_SKEWNESS_LIMIT_P (skew))
#define DT_VALID_LSCALE_P(dt) \
  VALID_SIZE_LIMITS_P (DT_MIN_LSCALE (dt), DT_MAX_LSCALE (dt))
#define DT_IDEAL_LSCALE(dt) Dynamic_Thread_Ideal_Length_Scale (dt)

/* misc */
#define FIND_CELL_DEPTH 2000
#define CHECK_METHOD_BIT(method,bit) ((method) & (bit))
#define ROUNDOFF_NTH_DECIMAL(v,n) ((long)((v*1.0e##n + 0.5))/1.0e##n)
#define THREAD_T_DIR(_thread,_dir) \
  (((_dir) == 0) ? THREAD_T0 (_thread) : THREAD_T1 (_thread))
#define DYNAMIC_INTERIOR_FACE_THREAD_P(_thread) \
  (NNULLP (THREAD_DT (_thread)) && INTERIOR_FACE_THREAD_P (_thread))
#if RP_NODE
# define CORNER_NODE_P(d,v) \
   NNULLP (Lookup_Corner_Node_In_Lists (d, NODE_ID (v)))
#else
# define CORNER_NODE_P(d,v) FALSE
#endif

/* different verbosity levels */
#define DYNMESH_VB1 remesh_verbosity > 0
#define DYNMESH_VB2 remesh_verbosity > 1
#define DYNMESH_VB3 remesh_verbosity > 2
#define DYNMESH_VB4 remesh_verbosity > 3

/* debugging */
#if !RP_HOST && DEBUG
# define NOBJP(where) \
    Message ("\n%s: number of Objps on %d: %d\n", \
             where, myid, Get_Number_Objps_Used ());
#endif

/* global variables */
extern FLUENT_EXPORT cxboolean remesh_p;
extern FLUENT_EXPORT cxboolean unified_remeshing_p;
extern FLUENT_EXPORT cxboolean remesh_poly_p;
extern FLUENT_EXPORT cxboolean remesh_exterior_p;
extern FLUENT_EXPORT cxboolean remesh_exterior_enhanced_p;
extern FLUENT_EXPORT cxboolean remesh_skewness_priority_marking_p;
extern FLUENT_EXPORT int remesh_methods;
extern FLUENT_EXPORT real remesh_max_cell_skew;
extern FLUENT_EXPORT real remesh_max_face_skew;
extern FLUENT_EXPORT real remesh_face_skew_rejection_threshold;
extern FLUENT_EXPORT real remesh_min_lscale;
extern FLUENT_EXPORT real remesh_max_lscale;
extern FLUENT_EXPORT real remesh_height_relax_factor;
extern FLUENT_EXPORT int remesh_max_sweeps;
extern FLUENT_EXPORT cxboolean remesh_refine_coarsen_order_p;
extern FLUENT_EXPORT int remesh_verbosity;
extern FLUENT_EXPORT int remesh_improvements;
extern FLUENT_EXPORT real remesh_swap_angle;
extern FLUENT_EXPORT int remesh_swap_iter;
extern FLUENT_EXPORT int remesh_refine_method;
extern FLUENT_EXPORT int remesh_skewness_method;
extern FLUENT_EXPORT int remesh_surfer_improve_method;
extern FLUENT_EXPORT real remesh_boundary_sliver_threshold;
extern FLUENT_EXPORT real remesh_sliver_skew;
extern FLUENT_EXPORT real remesh_improve_remeshed_cavity_threshold;
extern FLUENT_EXPORT cxboolean remesh_improve_remesh_local_p;
extern FLUENT_EXPORT cxboolean remesh_sizing_function_p;
extern FLUENT_EXPORT int remesh_size_interval;
extern FLUENT_EXPORT real remesh_lscale_limit_factor;
extern FLUENT_EXPORT cxboolean adapted_threads_readapt_after_remeshing_p;
extern FLUENT_EXPORT cxboolean adapted_threads_move_cells_p;
extern FLUENT_EXPORT cxboolean remesh_perturb_cavity_nodes_p;
extern FLUENT_EXPORT cxboolean remesh_with_prisms_p;
extern FLUENT_EXPORT cxboolean remesh_allow_prism_stairstepping_p;
extern FLUENT_EXPORT cxboolean remesh_check_self_intersecting_loops;
extern FLUENT_EXPORT cxboolean remesh_thread_parallel_p;
extern FLUENT_EXPORT cxboolean remesh_thread_multinode_p;
extern FLUENT_EXPORT cxboolean remesh_thread_include_quad_faces_p;
extern FLUENT_EXPORT cxboolean remesh_cavities_on_same_cpu;
extern FLUENT_EXPORT real remesh_intersecting_padding;
extern FLUENT_EXPORT real remesh_prism_first_height;
extern FLUENT_EXPORT real remesh_prism_growth_rate;
extern FLUENT_EXPORT int remesh_prism_nlayers;
extern FLUENT_EXPORT int remesh_prism_nlayers_max;
extern FLUENT_EXPORT cxboolean remesh_threads_on_prism_quality_p;
extern FLUENT_EXPORT cxboolean collect_node_connected_tetrahedra_p;
extern FLUENT_EXPORT cxboolean collect_connected_wedges_p;
extern FLUENT_EXPORT cxboolean remesh_udf_deform_p;
extern FLUENT_EXPORT int tetrahedra_connectivity_level;
extern FLUENT_EXPORT real max_prism_size_factor;
extern FLUENT_EXPORT cxboolean cmplx_perdisp;
extern FLUENT_EXPORT cxboolean update_per_disp_p;
#if RP_3D
extern FLUENT_EXPORT cxboolean remesh_local_prism_all_layer_prox_p;
#endif
#if PARALLEL
extern cxboolean remesh_repartition_enable_p;
extern cxboolean remesh_repartition_auto_p;
extern int remesh_repartition_interval;
extern real remesh_repartition_load_threshold;
extern real remesh_repartition_interface_threshold;
extern real remesh_repartition_last_interface_ratio;
#endif

extern FLUENT_EXPORT cxboolean layer_p;
extern FLUENT_EXPORT real layer_relax_sub;
extern FLUENT_EXPORT real layer_relax_col;
extern FLUENT_EXPORT cxboolean layer_adapt_p;
extern FLUENT_EXPORT cxboolean layer_constant_layer_height_p;
extern FLUENT_EXPORT cxboolean subdivide_dvolume_dt;

extern FLUENT_EXPORT cxboolean contact_active_p;
extern FLUENT_EXPORT int contact_model_type;

extern FLUENT_EXPORT cxboolean spring_all_cell_type_p;
extern FLUENT_EXPORT cxboolean spring_deformable_cell_type_p;
extern FLUENT_EXPORT int spring_verbosity;
extern FLUENT_EXPORT int spring_itermax;
extern FLUENT_EXPORT real spring_epsilon;
extern FLUENT_EXPORT real spring_relax;
extern FLUENT_EXPORT real spring_bnd_relax;
extern FLUENT_EXPORT real spring_bnd_stiffness;
extern FLUENT_EXPORT real spring_face_node_skewness;

extern FLUENT_EXPORT real bnd_laplace_relax;

extern FLUENT_EXPORT int smooth_method;
extern FLUENT_EXPORT int smooth_iter;
extern FLUENT_EXPORT real smooth_face_skew;
extern FLUENT_EXPORT real smooth_cell_skew;

extern FLUENT_EXPORT cxboolean smooth_from_ref_p;
extern FLUENT_EXPORT cxboolean update_moving_smooth_ref_p;

extern FLUENT_EXPORT cxboolean local_smooth;
extern FLUENT_EXPORT int local_smooth_mark_method;
extern FLUENT_EXPORT char *local_smooth_mark_register_name;
extern FLUENT_EXPORT int local_smooth_verbosity;
extern FLUENT_EXPORT Svar sv_def_cell_mark;

extern FLUENT_EXPORT int mesh_smooth_boundary_distance_method;
extern FLUENT_EXPORT int  mesh_smooth_diff_coeff_func;
extern FLUENT_EXPORT real mesh_smooth_diff_coeff_param;
extern FLUENT_EXPORT int laplace_smooth_verbosity;
extern FLUENT_EXPORT cxboolean laplace_smooth_memory_allocated_p;
extern FLUENT_EXPORT cxboolean lms_use_node_based_lsq;
extern FLUENT_EXPORT int fem_smooth_verbosity;
extern FLUENT_EXPORT int fem_smooth_model;
extern FLUENT_EXPORT cxboolean fem_smooth_memory_allocated_p;
extern FLUENT_EXPORT cxboolean rbf_smooth_memory_allocated_p;

extern FLUENT_EXPORT cxboolean dynmesh_use_cell_data_when_face_interpol_fails_p;
extern FLUENT_EXPORT real dynmesh_face_interpol_range;

extern FLUENT_EXPORT cxboolean in_cylinder_p;
extern FLUENT_EXPORT real in_cyn_ca;
extern FLUENT_EXPORT real in_cyn_min_lift;
extern FLUENT_EXPORT real in_cyn_min_stroke;
extern FLUENT_EXPORT real in_cyn_ca_start;
extern FLUENT_EXPORT real in_cyn_ca_period;
extern FLUENT_EXPORT real in_cyn_ca_rpm;
extern FLUENT_EXPORT real in_cyn_piston_data[3];

extern FLUENT_EXPORT cxboolean pump25d_p;
extern FLUENT_EXPORT cxboolean sdof_p;

extern FLUENT_EXPORT cxboolean dynamesh_node_id_p;
extern FLUENT_EXPORT cxboolean grid_motion_retain_normal_bc_p;
extern FLUENT_EXPORT cxboolean dynamesh_set_dynamic_threads_state_p;

extern FLUENT_EXPORT real dynamesh_time;
extern FLUENT_EXPORT real dynamesh_dtime;

extern FLUENT_EXPORT cxboolean dynamesh_sc_enabled_p;

extern FLUENT_EXPORT int num_domain;
extern FLUENT_EXPORT int num_extract;
extern FLUENT_EXPORT int num_remesh_cells;

#define DYNAMESH_CURRENT_TIME (dynamesh_time + dynamesh_dtime)

#define TIME_TO_ABSOLUTE_CRANK_ANGLE(time) \
 (in_cyn_ca_start + 6.0 * in_cyn_ca_rpm * time)

FLUENT_EXPORT real CA_to_time(real time, real crank_angle);

FLUENT_EXPORT void Register_Dyamic_Mesh_HDF_IO_Managers(void);
FLUENT_EXPORT void Deregister_Dyamic_Mesh_HDF_IO_Managers(void);

#define SMOOTHING_CELL_THREAD_P(t) ((NULLP(THREAD_DT(t)) && DEFORMING_THREAD_P(t)) || \
                               (NNULLP(THREAD_DT(t)) && DT_DEFORMING_P(THREAD_DT(t)) && DT_SLIDE_P(THREAD_DT(t))))


/* partial/local smoothing of deforming cell zone */
#define DEF_CELL_MARK(c,t) (CELL_MANAGED_TMP_INT(c,t,sv_def_cell_mark))

FLUENT_EXPORT int icm_blade_numbering(Domain *, int *, int *, int *);
FLUENT_EXPORT int icm_blade_amplitude(Domain *, int, double *);
FLUENT_EXPORT void icm_error_mesg(int);
FLUENT_EXPORT int icm_row(Domain *, int, int, int *, int **);

#endif /* _FLUENT_DYNAMESH_TOOLS_H */
