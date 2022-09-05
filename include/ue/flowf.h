/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_FLOWF_H
#define _FLUENT_FLOWF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dll.h"
#include "mem.h"

#if SEEM
FLUENT_EXPORT Pointer Cell_Function_Names(Domain *domain);
FLUENT_EXPORT Pointer Cell_Function_Names_Filtered(Domain *domain);
FLUENT_EXPORT Pointer Cell_Function_Names_Sectioned(Domain *domain);
FLUENT_EXPORT Pointer Cell_Vector_Function_Names(Domain *domain);
#endif
FLUENT_EXPORT char *Cell_Function_Name(const char *pick, Domain *domain);
FLUENT_EXPORT char *Enabled_Cell_Function_Name(Domain *domain, const char *pick);
FLUENT_EXPORT cxboolean Cell_Center_Function_Values(Domain *, const char *, Svar, int mark, cxboolean onhost);
FLUENT_EXPORT void Save_Cell_Min_Max(Domain *domain, Svar storage_var,
                                     int storage_mark, const char *name, const char *unit, cxboolean onhost);
FLUENT_EXPORT cxboolean Cell_Function_Values(Domain *, const char *what);
FLUENT_EXPORT cxboolean Face_Thread_Function_Values(Domain *, Thread *, const char *what, cxboolean cff);
FLUENT_EXPORT cxboolean Face_Only_Field(const char *what);
FLUENT_EXPORT cxboolean Is_Face_Field(Domain *, const char *what);
FLUENT_EXPORT Pointer Cell_Function_Type(Domain *, const char *);
FLUENT_EXPORT cxboolean Fill_Boundary_Values(Domain *domain, const char *what, Svar svar);
FLUENT_EXPORT const char *Get_Field_Variable_Unit(Domain *, const char *what);
void Compute_SI_Node_Values(Domain *domain);

FLUENT_EXPORT void Init_Interface_Node_Weight(Domain *domain);
FLUENT_EXPORT void Init_Node_Value_And_Weight(Thread *t, cxboolean isFE);
FLUENT_EXPORT void Init_pf0_Node_Value_And_Weight(Thread *t);
FLUENT_EXPORT void Accumulate_Face_Node_Value(face_t f, Thread *t, real value, cxboolean isFE);
FLUENT_EXPORT void Set_Interface_Node_Value(Domain *domain);
FLUENT_EXPORT void Norm_pf0_Node_Values(Thread *t);
FLUENT_EXPORT void Norm_Node_Values(Thread *t, cxboolean isFE);
FLUENT_EXPORT void Norm_Interface_Node_Value(Domain *domain);

#if !RP_HOST
FLUENT_EXPORT void Fill_Sliding_Boundary_Data(Domain *);
FLUENT_EXPORT void Set_cvf_cvs(int);
#endif

#if !RP_NODE
FLUENT_EXPORT Pointer Fill_Render_Info(Domain *domain, const char *what);
#endif

struct cell_function_struct;

FLUENT_EXPORT void Reset_Cached_Cell_Function(void);
FLUENT_EXPORT void Compute_Node_Cell_Min_Max (Domain *, real *, real *, real *, real *);
FLUENT_EXPORT void Compute_Node_Average (Domain *, real *, real *);
FLUENT_EXPORT void Compute_Cell_Average (Domain *, real *, real *);
FLUENT_EXPORT void Compute_Cell_Thread_Average (Thread *, real *, real *);
FLUENT_EXPORT void Compute_Cell_Values_From_Node_Values(Domain *domain);
FLUENT_EXPORT void Compute_Cell_Values_From_Face_Values(Domain *domain);
FLUENT_EXPORT void Compute_Node_Values_From_Cell_Values(Domain *domain,
                                                        struct cell_function_struct *cf,
                                                        cxboolean skip_interior);
FLUENT_EXPORT void Compute_Node_Values_From_Cell_Values_CellLoop_Based(Domain *domain,
    struct cell_function_struct *cf);
FLUENT_EXPORT void Compute_Node_Values_From_Cell_Values_FaceLoop_Based(Domain *domain,
    struct cell_function_struct *cf,
    cxboolean skip_interior);
FLUENT_EXPORT void Compute_Node_Values_From_Cell_Values_NodeLoop_Based(Domain *domain,
    struct cell_function_struct *cf);
FLUENT_EXPORT void Compute_Values_From_Wall_Face_Values(Domain *domain, cxboolean skip_interior, cxboolean compute_node_values, const char *);
FLUENT_EXPORT void Compute_Interface_Values_From_Wall_Values(Domain *domain);
FLUENT_EXPORT void Save_Storage_Info(Domain *, int which,
                                     const char *name, const char *domain_name, const char *units,
                                     double cell_min, double cell_max,
                                     double node_min, double node_max);

FLUENT_EXPORT void Cell_Bins(Domain *d, real cmn, real cmx, int n, int *lst, int nt, int *tids);
FLUENT_EXPORT void Mrotation( real M[3][3], real axis[3], real angle );

/* strf.c */
#if RP_2D
FLUENT_EXPORT void Stream_Function(Domain *d);
FLUENT_EXPORT void MD_Stream_Function(Domain *domain);
#endif

#if 0
#define FACE_PRESSURE(f,t) (!limit_output_p? F_P(f,t) : MAX(p_cav_limit-op_pres, F_P(f,t)) )
#define CELL_PRESSURE(c,t) (!limit_output_p? C_P(c,t) : MAX(p_cav_limit-op_pres, C_P(c,t)) )
#else
#define p_cell_limit ((vof_linearized && model_cav)? C_STORAGE_R(c,t,SV_VAPOR_PRESS) : p_cav_limit)
#define FACE_PRESSURE(f,t) (!limit_output_p? F_P(f,t) : MAX(p_cav_limit -op_pres, F_P(f,t)) )
#define CELL_PRESSURE(c,t) (!limit_output_p? C_P(c,t) : MAX(p_cell_limit-op_pres, C_P(c,t)) )
#endif

#define CELL_FUNCTION_DEF(f) double f(const cell_t c, const Thread *t)

FLUENT_EXPORT void Alloc_Ftmp(Thread *);
#define ALLOC_FTMP Alloc_Ftmp

FLUENT_EXPORT void Alloc_Svar(Thread *, Svar);
#define ALLOC_SVAR Alloc_Svar


/* cell function types */
#define CFT_1        (-1)
#define CFT_SECTION      (-2)
#define CFT_ND         (-3)
#define CFT_NW         (-4)
#define CFT_NWV        (-5)
#define CFT_QV         (-6)
#define CFT_NSPE       (-7)
#define CFT_NEQ        (-8)
#define CFT_NEQV       (-9)
#define CFT_NSPE_SURF        (-10)
#define CFT_NNOX       (-11)
#define CFT_DO         (-12)

#define CFT_NRSE             (-13)
#define CFT_SOOT             (-14)
#define CFT_NUCLEI           (-15)
#define CFT_NUDS       (-16)
#define CFT_ND3        (-17)
#define CFT_NREACT       (-18)
#define CFT_NREACT_SURF      (-19)
#define CFT_DO_NBAND         (-20)

#define CFT_NDND             (-21)
#define CFT_NMT              (-22)
#define CFT_NHRXN            (-23)

#define CFT_NUDM       (-24)

#define CFT_RESIDUAL         (-25)
#define CFT_NSPE_SITE        (-26)

#define CFT_SOLAR_BAND       (-27)
#define CFT_VOL_NREACT       (-28)
#define CFT_SURF_NREACT      (-29)

#define CFT_NPB_DISC         (-30) /* population balance */
#define CFT_NPB_QMOM         (-31)
#define CFT_NPB_QMOM_ABS_WT  (-32)
#define CFT_NPB_SMM          (-33)

#define CFT_POLLUT_NO        (-34)
#define CFT_NSOX       (-35)
#define CFT_ND3_RST          (-36)
#define CFT_ND3_HF         (-37)

#define CFT_EPDF             (-38)
#define CFT_EPDF_MODE        (-39)

#define CFT_POLLUT_SOOT      (-40)
#define CFT_POLLUT_NUCLEI    (-41)

#define CFT_DPM_DIST         (-42)
#define CFT_POST             (-43)

#define CFT_NSPE_UFLA        (-44)

#define CFT_CTAR             (-45)
#define CFT_POLLUT_SOX       (-46)

#define CFT_INERT_NSPE       (-47)

#define CFT_NHG              (-48)
#define CFT_POLLUT_HG        (-49)

#define CFT_EPDF_PROB        (-50)

#define CFT_NODE_NUDM      (-51)

#define CFT_NMA              (-52)  /* modal analysis */

#define CFT_NSPE_DIM_RED     (-53)
#define CFT_UNSTD_STAT_CFF   (-54)
#define CFT_DPM_DROP         (-55)
#define CFT_DPM_COMB         (-56)
#define CFT_NSPE_REACTOR_NET (-57)
#define CFT_DPM_DIST_TIME_STAT (-58)
#define CFT_DPM_DIST_RMS     (-59)
#define CFT_NPROB            (-60)
#define CFT_SOOT_MOM         (-61)
#define CFT_ECHEM_NREACT     (-62)
#define CFT_COARSE_AMG       (-63)
#define CFT_SPE_RESID        (-64)
#define CFT_DPM_EROSION      (-65)
#define CFT_PDF_SCALAR       (-66)
#define CFT_DPM_FILM         (-67)
#define CFT_LUMP_POSTPROC    (-68)
#define CFT_NIAD             (-69)
#define CFT_SCR_UREA_DEPO    (-70)
#define CFT_NROM             (-71)
#define CFT_SOOTSPECIES_AREA    (-72)
#define CFT_FCFC_0           (-73)
#define CFT_FCFC             (-74)
#define CFT_ICFC_0           (-75)
#define CFT_ICFC             (-76)
#define CFT_REFC             (-77)
#define CFT_ERFC             (-78)
#define CFT_STAT_DATASET     (-79)

#define CFT_RTDFT_ABS        (-80)
#define CFT_RTDFT_ARG        (-81)
#define CFT_BCFC             (-82)
#define CFT_CBCFC            (-83)
#define CFT_IDFT             (-84)

#define CFT_MAX              (-85)  /* this must be the largest (negative) CFT */

#define CF_NAME_MAX_LEN 70

/* velocity frame types */
typedef enum vframe
{
  V_SOLVED, /* velocities not used or use the frame they are solved in */
  V_ABSOLUTE, /* velocities in inertial frame */
  V_RELATIVE  /* velocities in reference thread's frame */
} VelocityFrame_t;


/* vector fields */
typedef enum vecfield
{
  VFT_0,      /* scalar */
  VFT_1       /* vector */
} VectorField_t;

/* velocity types */
typedef enum veltype
{
  VEL_TYPE_X,
  VEL_TYPE_Y,
  VEL_TYPE_Z,
  VEL_TYPE_MAG,
  VEL_TYPE_AXIAL,
  VEL_TYPE_RADIAL,
  VEL_TYPE_TANGENTIAL
} VEL_TYPE;

/* mphase types */
typedef enum mphasetype
{
  TYPE_ONLY_MIXTURE_DOMAIN = 0,
  TYPE_ALL_DOMAINS = 1
} MPHASE_DOMAIN_TYPE;


/* Need the following, postprocessing-related, here to
 * provide MAX_LUMP_PROPS to SV_Size() in storage/storage.c:
 * The following list MUST match a corresponding list in vof_to_dpm.c --
 * find it there by searching that file for MAX_LUMP_PROPS!
 */

typedef enum lump_prop_enum
{
  LUMP_PP_DIAMETER,
  LUMP_PP_DENSITY,
  /*LUMP_PP_ASPHITY_BY_AV_RADIUS,*/
  /*LUMP_PP_ASPHITY_BY_SURF_AREA,*/
  LUMP_PP_ASPHITY_BY_SIGMA_RAD,
  LUMP_PP_ASPHITY_BY_ORTHOGITY,
  LUMP_PP_X_COOR,
  LUMP_PP_Y_COOR,
  LUMP_PP_Z_COOR,
  LUMP_PP_U_VELO,
  LUMP_PP_V_VELO,
  LUMP_PP_W_VELO,
  /*LUMP_PP_MAXI_VOF,*/
  LUMP_PP_TEMPERAT,
  LUMP_PP_ENTHALPY,
  LUMP_PP_PRESSURE,
  MAX_LUMP_PROPS
} lump_prop_t;


typedef enum scr_urea_depo_risk_post_var_enum
{
  SCR_UREA_DEPO_RISK_ANAL_CRYST = 0,
  SCR_UREA_DEPO_RISK_ANAL_SECRX,
  SCR_UREA_DEPO_RISK_ANAL_TOTAL,
  MAX_SCR_UREA_DEPO_RISK_POST_VARS
} scr_urea_depo_risk_post_var_t;

/* =============================================== */

typedef struct cell_function_struct
{
  char pick[CF_NAME_MAX_LEN]; /* key */
  char name[CF_NAME_MAX_LEN]; /* printing name */
  char *unit;     /* units name */
  double (*f)();    /* fluid cell function */
  double (*s)();    /* solid cell function */
  void (*vf)();     /* fluid node function */
  void (*vs)();     /* solid node function */
  void (*init)();   /* init function */
  cxboolean (*enable)();  /* enabling flag for visc,ke solvers */
  int type;     /* function type/index */
  VelocityFrame_t vframe;       /* frame of reference for velocities */
  VectorField_t vfield;         /* flag for vector field */
  /* The face_only functions are those functions which are present on the faces.
   * They are stored in F_TMP and then with area wtd avg into the cells.
   * Face zones directly use this F_TMP, but post-processing surfaces use C_TMP.*/
  cxboolean face_only;    /* flag for quantities undefined at cells*/
  void (*face)(Thread *t, int type, Svar sv);/* face function, NULL if undefined */
  cxboolean (*if_face)(); /* test whether to call face() */
  int mphase_domain_type;       /* Multiphase domain type */
  int vector_comp;              /* flag for vector component? */
  int svar_index;               /* will store the svar index in sv_master if the cell-fn corresponds to an svar else -1*/
  float *dim; /* Pointer to dimension array of length 10 */
  cxboolean is_mesh_fn;

} CELL_FUNCTION;

typedef struct cft_type_struct
{
  int cft_index;
  const char *context;
  int(*nvars)(Domain *domain);
  void(*var_name)(Domain *, int, char *name);
  void(*cell_function_name)(const char *pick_name, const char *option_name, char *fn_name);
} CFT_Type;

typedef struct
{
  CELL_FUNCTION *data;
  int *ndata;
} Cell_Func_Pattern_Def;

typedef struct quantity_dimension
{
  char quantity[CF_NAME_MAX_LEN];
  char si_units[CF_NAME_MAX_LEN];
  float dim[10];
} Dimension;

FLUENT_EXPORT float *Get_Dimension_Array(char *unit);
#define BEGIN_SECTION(name,enable){"",name,NULL,NULL,NULL,NULL,NULL,NULL,enable,CFT_SECTION,V_SOLVED,VFT_0}
#define END_SECTION(name,enable){"",name,NULL,NULL,NULL,NULL,NULL,NULL,enable,CFT_SECTION,V_SOLVED,VFT_0}

extern int nCellFuncPatterns;
extern FLUENT_EXPORT CELL_FUNCTION *last_cf;
extern FLUENT_EXPORT Thread *tref;
FLUENT_EXPORT void init_reference_thread(Domain *domain);
FLUENT_EXPORT Cell_Func_Pattern_Def *Get_Cell_Function_Patterns(void);

FLUENT_EXPORT cxboolean if_true(void);
FLUENT_EXPORT cxboolean if_rp_turb(void);
FLUENT_EXPORT cxboolean if_sg_pdf(void);
FLUENT_EXPORT cxboolean if_expert(void);
FLUENT_EXPORT cxboolean if_mp_expert(void);
FLUENT_EXPORT cxboolean if_mfluid_expert(void);
FLUENT_EXPORT cxboolean if_sg_mphase(void);
FLUENT_EXPORT cxboolean if_mpg(Domain *);
FLUENT_EXPORT cxboolean if_mf_temp(Domain *);
FLUENT_EXPORT cxboolean if_shared_unless_mphase(Domain *d);
FLUENT_EXPORT cxboolean if_shared_unless_mfluid(Domain *d);
FLUENT_EXPORT cxboolean if_visc_temp(void);


typedef void (*faceFunction)(Thread *thread, Svar svar);
FLUENT_EXPORT real Evaluate_Cell_Function(CELL_FUNCTION *cf, cell_t c, Thread *t);
FLUENT_EXPORT void Get_Cell_Velocity(cell_t c, Thread *t, real *u);
FLUENT_EXPORT void Convt_Cell_Velocity_Ref_Frame(cell_t c, Thread *t, real *u);
FLUENT_EXPORT void nodeVof(Domain *subdomain);
FLUENT_EXPORT void nodePressure(Domain *domain);
FLUENT_EXPORT void nodeTotalPressure(Domain *domain);
FLUENT_EXPORT void nodeAbsolutePressure(Domain *domain);
FLUENT_EXPORT void nodeTemperature(Domain *domain);
FLUENT_EXPORT void nodeVelocity(Domain *domain, VEL_TYPE type);
FLUENT_EXPORT void nodeNDVelocity(Domain *domain, int nd);
FLUENT_EXPORT void nodeNDG(Domain *domain, int nd);
FLUENT_EXPORT void facePressure(Thread *thread, int type, Svar svar);
FLUENT_EXPORT void faceDensity(Thread *thread, int type, Svar svar);
FLUENT_EXPORT void faceAbsolutePressure(Thread *thread, int type, Svar svar);
FLUENT_EXPORT void faceTemperature(Thread *thread, int type, Svar svar);
FLUENT_EXPORT void faceTotalPressure(Thread *thread, int type, Svar svar);
FLUENT_EXPORT void faceTotalTemperature(Thread *thread, int type, Svar svar);
FLUENT_EXPORT void faceVelocity(Thread *thread, Svar svar, VEL_TYPE type);
FLUENT_EXPORT void faceNDVelocity(Thread *thread, int nd, Svar svar);
FLUENT_EXPORT void faceNDG(Thread *thread, int nd, Svar svar);
FLUENT_EXPORT void faceVof(Thread *thread, int type, Svar svar);
FLUENT_EXPORT void Get_Face_Thread_List_By_Priority(Domain *, Objp **, char *);
extern FLUENT_EXPORT cxboolean relative_velocity;

#if RP_3D
FLUENT_EXPORT CELL_FUNCTION_DEF(cellHelicity);
#endif
FLUENT_EXPORT CELL_FUNCTION_DEF(cellWallDistance);
FLUENT_EXPORT CELL_FUNCTION_DEF(cellRe);
FLUENT_EXPORT CELL_FUNCTION_DEF(cellVorticity);
FLUENT_EXPORT CELL_FUNCTION_DEF(cellcourant);
FLUENT_EXPORT CELL_FUNCTION_DEF(cellTotalTemperature);
FLUENT_EXPORT CELL_FUNCTION_DEF(cellTotalPressure);
FLUENT_EXPORT CELL_FUNCTION_DEF(cellAbsolutePressure);
FLUENT_EXPORT CELL_FUNCTION_DEF(cellPressure);
FLUENT_EXPORT CELL_FUNCTION_DEF(cellInternalEnergy);

FLUENT_EXPORT void Init_Hessian_Indicator(Domain *domain, Svar sv_val);

FLUENT_EXPORT void face_sv(Thread *thread, Svar store_in, Svar store_from);
FLUENT_EXPORT void node_sv(Domain *domain, Svar nv);
FLUENT_EXPORT CELL_FUNCTION_DEF(cellZero);
FLUENT_EXPORT void cellMassFractions(cell_t c, Thread *t, real yi[]);
FLUENT_EXPORT real cellMoleFractions(cell_t c, Thread *t, real xi[]);

FLUENT_EXPORT CELL_FUNCTION_DEF(cellVelocityMagnitude);

FLUENT_EXPORT CELL_FUNCTION_DEF(cellDPMSTotalEnergy);
FLUENT_EXPORT CELL_FUNCTION_DEF(cellDPMSEnergy);
FLUENT_EXPORT CELL_FUNCTION_DEF(cellDPMSMass);
FLUENT_EXPORT CELL_FUNCTION_DEF(cellDPMSMixtureFraction);
FLUENT_EXPORT CELL_FUNCTION_DEF(cellDPMSMixtureFractionSecondary);
FLUENT_EXPORT CELL_FUNCTION_DEF(cellDPMSInert);

FLUENT_EXPORT CELL_FUNCTION *Cell_Function(const char *, Domain *);
FLUENT_EXPORT cxboolean Is_Grid_Function(const CELL_FUNCTION *cf);
#if !RP_NODE
FLUENT_EXPORT void Domain_Wall_Monitor_Header(Pointer pz, Pointer pn, Pointer fargs);
FLUENT_EXPORT void Write_Fast_Force_Header(Pointer t, Pointer l, Pointer c, Pointer index);
#endif
FLUENT_EXPORT void Domain_Wall_Monitor(Pointer pz, Pointer cd_args, Pointer cl_args, Pointer cm_args);
FLUENT_EXPORT cxboolean Domain_Thread_Integrals(Pointer args, real integral[], int *tid, int *did);
/*FLUENT_EXPORT void Set_Fast_Force_Monitor(Pointer t, Pointer l, char *file);*/
FLUENT_EXPORT void Set_Fast_Force_Monitor(Pointer t);
FLUENT_EXPORT void Set_Fast_Force_Parameter(Pointer t, Pointer l, Pointer d, Pointer a);
FLUENT_EXPORT Pointer Compute_Fast_Force_Monitor(Pointer d, Pointer l, Pointer m);
FLUENT_EXPORT Pointer Compute_Fast_Force_Parameter(Pointer d, Pointer l, Pointer m);
FLUENT_EXPORT void add_monitor(const char *namey, const char *type, const char *unit);
FLUENT_EXPORT void save_current_user_monitor(const char *name, const int iter_or_time_steps, const real value);
FLUENT_EXPORT void write_user_monitors(FILE *fd, cxboolean binary);
FLUENT_EXPORT void computeForceMomentIntegrals(int mthreadIds, real *, real *_fvals, real *_mvals);
FLUENT_EXPORT void computeForceIntegralsNodes(Thread *thread, int option, real *forces);
FLUENT_EXPORT void computeMomentsIntegralsNodes(Thread *thread, const real *momentCenter, real *mval);

FLUENT_EXPORT void Fill_Vector_Field_Data(char *vname, int *indices, int nids, char *components[]);
FLUENT_EXPORT cxboolean Is_Node_Wt_Needed_For_Post(void);
FLUENT_EXPORT real calc_net_rad_source(int domain_id);
FLUENT_EXPORT real calc_dpm_rad_source(int domain_id);
FLUENT_EXPORT void Cell_Functions_List_Cleared();
FLUENT_EXPORT void update_expert_value(void);
FLUENT_EXPORT cxboolean cf_is_in_CellFuncPattern_p(CELL_FUNCTION *cf, const char *pattern);

CFT_Type *Get_CFT_type_from_index(int type);

#define POST_NODEWT_BASED_INTERP_P (!sg_overset && RP_Get_Boolean("post/node-weight-interpolation?"))

extern FLUENT_EXPORT cxboolean post_use_local_nodes;

#define F_NODE_POST(f,t,n) ( post_use_local_nodes ? F_NODE_LOCAL(f, t, n) : F_NODE(f, t, n) )
#define C_NODE_POST(c,t,n) ( post_use_local_nodes ? C_NODE_LOCAL(c, t, n) : C_NODE(c, t, n) )
#define F_NODE_POST_SHADOW(f,t,n) ( post_use_local_nodes ? F_NODE_LOCAL_SHADOW(f, t, n) : F_NODE_SHADOW(f, t, n) )
#define F_NODE_POST_SHADOW_SAFE(f,t,n) ( (!SV_ALLOCATED_P(t,SV_SHADOW) || NULL_FACE_P(F_SHADOW(f,t))) ? NULL : F_NODE_POST_SHADOW(f,t,n))
#define C_NODE_POST_SHADOW(c,t,n) ( post_use_local_nodes ? C_NODE_LOCAL_SHADOW(c, t, n) : NODE_SHADOW(C_NODE(c, t, n)) )

#define Exchange_Post_Var(d)EXCHANGE_SVAR_MESSAGE(d,(SV_POST_VAR,SV_NULL))
extern cxboolean render_blocked_cells;
extern cxboolean registerexpronhost;
void update_render_blocked_cells (cxboolean render);
cxboolean is_non_conformal_zone (Thread *thread);
cxboolean is_non_conformal_periodic_zone (Thread *thread);
extern cxboolean face_only_val;

#ifdef __cplusplus
}
#endif

#endif /* _FLUENT_FLOWF_H */
