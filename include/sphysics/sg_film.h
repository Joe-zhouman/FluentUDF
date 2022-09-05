/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_FILM_H
#define _FLUENT_FILM_H

#include "dpm_types.h"
#include "sg_delta.h"

#if 1
#define WALL_FILM_PHS2_SPLASH 0

#define T_STORAGE_R_MV(t, n)   (T_STORAGE((t), (n), real (*)[ND_ND][ND_ND]))
#define F_STORAGE_R_MV(f, t, n)(T_STORAGE_R_MV((t), (n))[(f)])

#define CACHE_T_SV_R_MV(x, t, sv)\
  real (* const x)[ND_ND][ND_ND] = T_STORAGE_R_MV(t, sv)

/* macros for additional face variables (new SV_s) (Note: t is the true wall thread) */
#define F_ORIGIN_CACHE(f, t)   (F_STORAGE_R_NV((f), (t), SV_EF_ORIGIN))

#define F_TM(f, t)             (F_STORAGE_R_MV((f), (t), SV_EF_TRANS_M))
#define F_ORIGIN(f, t)          F_ORIGIN_CACHE((f), (t))
#define F_NORMD0(f, t)         (F_STORAGE_R((f), (t), SV_EF_NORMD0))

#define F_HEIGHT(f, t)         (F_STORAGE_R((f), (t), SV_EF_HEIGHT)) /* use this to hold h*rho for variable density */
#define F_HEIGHT_PREV(f, t)    (F_STORAGE_R((f), (t), SV_EF_HEIGHT_PREV))
#define F_HEIGHT_SRC(f, t)     (F_STORAGE_R((f), (t), SV_EF_HEIGHT_SRC))
#define F_HEIGHT_SRC_PREV(f, t)(F_STORAGE_R((f), (t), SV_EF_HEIGHT_SRC_PREV))
#define F_HVEL_X(f, t)         (F_STORAGE_R((f), (t), SV_EF_HVEL_X))
#define F_HVEL_Y(f, t)         (F_STORAGE_R((f), (t), SV_EF_HVEL_Y))
#define F_HVEL_X_PREV(f, t)    (F_STORAGE_R((f), (t), SV_EF_HVEL_X_PREV))
#define F_HVEL_Y_PREV(f, t)    (F_STORAGE_R((f), (t), SV_EF_HVEL_Y_PREV))
#define F_HVEL_X_SRC(f, t)     (F_STORAGE_R((f), (t), SV_EF_HVEL_X_SRC))
#define F_HVEL_Y_SRC(f, t)     (F_STORAGE_R((f), (t), SV_EF_HVEL_Y_SRC))
#define F_HVEL_X_SRC_PREV(f, t)(F_STORAGE_R((f), (t), SV_EF_HVEL_X_SRC_PREV))
#define F_HVEL_Y_SRC_PREV(f, t)(F_STORAGE_R((f), (t), SV_EF_HVEL_Y_SRC_PREV))
#define F_HT(f, t)             (F_STORAGE_R((f), (t), SV_EF_HT))
#define F_HT_PREV(f, t)        (F_STORAGE_R((f), (t), SV_EF_HT_PREV))
#define F_HT_SRC(f, t)         (F_STORAGE_R((f), (t), SV_EF_HT_SRC))
#define F_HT_SRC_PREV(f, t)    (F_STORAGE_R((f), (t), SV_EF_HT_SRC_PREV))
#define F_HS(f, t)             (F_STORAGE_R((f), (t), SV_EF_HS))
#define F_HS_PREV(f, t)        (F_STORAGE_R((f), (t), SV_EF_HS_PREV))
#define F_HS_SRC(f, t)         (F_STORAGE_R((f), (t), SV_EF_HS_SRC))
#define F_HS_SRC_PREV(f, t)    (F_STORAGE_R((f), (t), SV_EF_HS_SRC_PREV))

#define F_SVEL_X(f, t)         (F_STORAGE_R((f), (t), SV_EF_SVEL_X))
#define F_SVEL_Y(f, t)         (F_STORAGE_R((f), (t), SV_EF_SVEL_Y))

#define F_HVELA_X(f, t)        (F_STORAGE_R((f), (t), SV_EF_HVELA_X))
#define F_HVELA_Y(f, t)        (F_STORAGE_R((f), (t), SV_EF_HVELA_Y))

#define F_Z_ACC(f, t)          (F_STORAGE_R((f), (t), SV_EF_Z_ACC))
#define F_Z_ACC_G(f, t)        (F_STORAGE_R_NV((f), (t), SV_EF_Z_ACC_G))
#define F_H_COV(f, t)          (F_STORAGE_R((f), (t), SV_EF_H_COV))
#define F_H_COV_G(f, t)        (F_STORAGE_R_NV((f), (t), SV_EF_H_COV_G))

#define F_VEC_X_G(f, t)       (F_STORAGE_R_NV((f), (t), SV_EF_VEC_X_G))
#define F_VEC_Y_G(f, t)       (F_STORAGE_R_NV((f), (t), SV_EF_VEC_Y_G))
#define F_VEC_Z_G(f, t)       (F_STORAGE_R_NV((f), (t), SV_EF_VEC_Z_G))

#define SV_EF_HVV_I(i)       ((Svar)((SV_EF_HVV_0+(i)*(SV_EF_HVV_1-SV_EF_HVV_0))))
#define SV_EF_HGV_I(i)       ((Svar)(SV_EF_HVV_I(i)+SV_EF_HVV_0_GV-SV_EF_HVV_0))
#define SV_EF_AUX_I(sv_s, i) ((Svar)(sv_s+_AUX_0+(i)))

/* macros for new stored face variables (new SV_s) */
#define F_EFILM_HEIGHT(f, t) (F_STORAGE_R((f), (t), SV_EFILM_HEIGHT))
#define F_EFILM_U(f, t)      (F_STORAGE_R((f), (t), SV_EFILM_U))
#define F_EFILM_V(f, t)      (F_STORAGE_R((f), (t), SV_EFILM_V))
#define F_EFILM_W(f, t)      (F_STORAGE_R((f), (t), SV_EFILM_W))
#define F_EFILM_T(f, t)      (F_STORAGE_R((f), (t), SV_EFILM_T))
#define F_EFILM_S(f, t)      (F_STORAGE_R((f), (t), SV_EFILM_S))

#define F_EFILM_T_ALPHA(f, t) (F_STORAGE_R((f), (t), SV_EFILM_T_ALPHA))
#define F_EFILM_T_BETA(f, t)  (F_STORAGE_R((f), (t), SV_EFILM_T_BETA))
#define F_EFILM_TS_FLUX(f, t) (F_STORAGE_R((f), (t), SV_EFILM_TS_FLUX))

#define F_EFILM_P(f, t)      (F_STORAGE_R((f), (t), SV_EFILM_P))

#define F_EFILM_DPM_MASS_SRC(f, t)  (F_STORAGE_R((f), (t), SV_EFILM_DPM_MASS_SRC))
#define F_EFILM_DPM_MOM_X_SRC(f, t) (F_STORAGE_R((f), (t), SV_EFILM_DPM_MOM_X_SRC))
#define F_EFILM_DPM_MOM_Y_SRC(f, t) (F_STORAGE_R((f), (t), SV_EFILM_DPM_MOM_Y_SRC))
#define F_EFILM_DPM_MOM_Z_SRC(f, t) (F_STORAGE_R((f), (t), SV_EFILM_DPM_MOM_Z_SRC))
#define F_EFILM_DPM_ENERGY_SRC(f, t)(F_STORAGE_R((f), (t), SV_EFILM_DPM_ENERGY_SRC))
#define F_EFILM_DPM_PRESSURE(f, t)  (F_STORAGE_R((f), (t), SV_EFILM_DPM_PRESSURE))

#define F_EFILM_SEPARATING_SRC(f, t) (F_STORAGE_R((f), (t), SV_EFILM_SEPARATING_SRC))
#define F_EFILM_SEPARATED_DIAM(f, t) (F_STORAGE_R((f), (t), SV_EFILM_SEPARATED_DIAM))
#define F_EFILM_SEPARATED_MASS(f, t) (F_STORAGE_R((f), (t), SV_EFILM_SEPARATED_MASS))
#define F_EFILM_STRIPPING_SRC(f, t)  (F_STORAGE_R((f), (t), SV_EFILM_STRIPPING_SRC))
#define F_EFILM_STRIPPED_DIAM(f, t)  (F_STORAGE_R((f), (t), SV_EFILM_STRIPPED_DIAM))
#define F_EFILM_STRIPPED_MASS(f, t)  (F_STORAGE_R((f), (t), SV_EFILM_STRIPPED_MASS))
#define F_EFILM_SEPARATED_MASS_SUM(f, t) (F_STORAGE_R((f), (t), SV_EFILM_SEPARATED_MASS_SUM))
#define F_EFILM_STRIPPED_MASS_SUM(f, t)  (F_STORAGE_R((f), (t), SV_EFILM_STRIPPED_MASS_SUM))
#define F_EFILM_OUTFLOW_MASS_SUM(f, t)   (F_STORAGE_R((f), (t), SV_EFILM_OUTFLOW_MASS_SUM))

#define F_EFILM_PHS2_MASS_SRC(f, t)  (F_STORAGE_R((f), (t), SV_EFILM_PHS2_MASS_SRC))
#define F_EFILM_PHS2_MOMS_SRC(f, t)  (F_STORAGE_R_NV((f), (t), SV_EFILM_PHS2_MOMS_SRC))
#define F_EFILM_PHS2_ENERGY_SRC(f, t)(F_STORAGE_R((f), (t), SV_EFILM_PHS2_ENERGY_SRC))

#define F_EFILM_VAPOR_MASS_SRC(f, t)  (F_STORAGE_R((f), (t), SV_EFILM_VAPOR_MASS_SRC))
#define F_EFILM_VAPOR_MASS_APP(f, t)  (F_STORAGE_R((f), (t), SV_EFILM_VAPOR_MASS_APP))

#define F_EFILM_US(f, t)     (F_STORAGE_R((f), (t), SV_EFILM_US))
#define F_EFILM_VS(f, t)     (F_STORAGE_R((f), (t), SV_EFILM_VS))
#define F_EFILM_WS(f, t)     (F_STORAGE_R((f), (t), SV_EFILM_WS))
#define F_EFILM_TS(f, t)     (F_STORAGE_R((f), (t), SV_EFILM_TS))
#define F_EFILM_DENSITY(f, t)(F_STORAGE_R((f), (t), SV_EFILM_DENSITY))
#define F_EFILM_CFL(f, t)     (F_STORAGE_R((f), (t), SV_EFILM_CFL))
#define F_EFILM_WEBER(f, t)   (F_STORAGE_R((f), (t), SV_EFILM_WEBER))


extern FLUENT_EXPORT cxboolean sg_wallfilm; /* Eulerian Wall Film model flag (nothing to do with M_wall_film!) */

typedef int edge_t;

/* Wall Film Equation ID */
typedef enum
{
  EQN_NULL = -1,
  EQN_CONTINUITY,
  EQN_MOMENTUM_X,
  EQN_MOMENTUM_Y,
  EQN_ENERGY,
  EQN_SCALAR,
  EQN_ALL
} FEeqn;

/* Time Discretization scheme */
enum
{
  EXPLICIT_FIRST_ORDER = 0,
  EXPLICIT_HIGH_ORDER,
  IMPLICIT_FIRST_ORDER,
  IMPLICIT_SECOND_ORDER,
  N_TIME_DISCRETIZATION
};

/* Space Discretization scheme */
enum
{
  UPWIND_FIRST_ORDER = 0,
  UPWIND_SECOND_ORDER,
  CENTERED_SECOND_ORDER,
  N_SPACE_DISCRETIZATION
};

/* monodimensional-limiter scheme */
enum
{
  NO_LIMITER = 0,
  MINMOD_LINEAR,
  MINMOD_QUADRATIC,
  MINMOD_CUBIC,
  N_LIMITER_SCHEME
};

typedef enum
{
  FEV_NULL = -1,
#define EV_MIN ((FEvar)(FEV_NULL+1))
  /* edge variables with edge thread length */
  EV_EDGE,
  EV_LENGTH,
  EV_CENTROID,
  EV_NORM0,
  EV_NORM1,
  EV_NORMC,
  EV_ANGLE,

  EV_UPWIND,
  EV_HVFLUX,
  EV_SHED_COUNT,
  EV_SHED_MASS,
  EV_SHED_DIAM,

  EV_SCALAR,
  EV_VECTOR,
  EV_TENSOR,

  EV_DUMMY_R,
#define EV_MAX ((FEvar)(EV_DUMMY_R+1))
#define FV_MIN ((FEvar)(EV_DUMMY_R+1))
  /* face variables with face thread length */
#if WALL_FILM_PHS2_SPLASH
  FV_PHS2_SPLASH_COEF,
  FV_PHS2_SPLASH_MASS,
  FV_PHS2_SPLASH_MOMS,
  FV_PHS2_SPLASH_NUMS,
  FV_PHS2_SPLASH_DIAM,
#endif
  FV_STRIP_COUNT,
  FV_STRIP_MASS,
  FV_SHED_COUNT,

  FV_DPM_DYNAMIC_PRES,
  FV_DPM_DYNAMIC_HITS,

  FV_MRF_VELOCITY,
  FV_MRF_ACCELERATION,

  FV_T_LAMBDA_GF,
  FV_T_BULK_TEMP,

  FV_FILM_MU,
  FV_FILM_CP,
  FV_FILM_KD,

  FV_GAUSS_PDF,

  FV_FILM_VOF_SWITCH,

  FV_DUMMY_R,
  FV_DUMMY_R_NV,

  FEV_MAX
#define FV_MAX ((FEvar)(FEV_MAX))
} FEvar;

typedef enum
{
  FEV_ST_DEFAULT = 0, /* temp storage can be allocated on demand */
  FEV_ST_ESSENTIAL,   /* storage must be allocated before calculation can start */
  FEV_ST_PERMANENT    /* storage allocted when edge/face trees are built */
} FEV_Store_Type;

typedef struct _fe_variable_attribute
{
  FEvar nv;
  SV_Dimension dimension;
  FEV_Store_Type store_flags;

  void (*init)(Domain *, struct _fe_variable_attribute *);

} FEVar_Attribute;

#define FEV_METHOD(ev, method)((ev)->method)

#define FEV(ev,dim,flag,init) {ev,dim,flag,init}

typedef struct _fe_thread
{
  Thread *t;

  int sv_length;
  int nelements;
#if RP_NODE
  int nelements_in_layer[N_LAYER]; /* see thread_struct definition... */
  int nlayer;
#endif
  void *storage[FEV_MAX];

} FE_Thread;

typedef enum
{
  ET_INTERIOR = 0, /* interior edge on film wall thread */
  ET_BOUNDARY = 1, /* boundary edge on film wall thread */
  ET_JUNCTION = 2, /* edge joining 2 film wall threads  */
  ET_PARTITION,    /* edge on partition line */
  ET_SYMMETRY,     /* edge on symmetric line */
  ET_PERIODIC      /* edge on periodic  line */
} Edge_Element_Type;

enum
{
  VAPOR_DIFFUSION_BALANCE = 0, /* Species diffusion balance (SLi) */
  VAPOR_BOUNDARY_LAYER,        /* Wall boundary layer model (as in LWF)    */
  VAPOR_USER
};

typedef enum
{
  PHASE2_MASS = 0,
  PHASE2_MOM_X,
  PHASE2_MOM_Y,
  PHASE2_MOM_Z,
  PHASE2_HEAT,
  PHASE2_TURB_K,
  PHASE2_TURB_D
} Phase2_Src_Index;

typedef struct _e_struct
{
  Node *v0;
  Node *v1;

  Thread *t0;
  Thread *t1;
  face_t f0;
  face_t f1;

  Thread *tb; /* boundary face thread the edge is adjacent to */
  face_t fb;

  FE_Thread *et_shadow;
  edge_t e_shadow;

  Edge_Element_Type type;  /* interior or exterior */
  int flag;
} E_Edge;

/*
 * Edge flags (default zero)
 */
#define E_FL_NONE     (0)
#define E_FL_FLOW_IN  (1)    /* edge on fluid flow inlet  */
#define E_FL_FLOW_OUT (1<<1) /* edge on fluid flow outlet */
#define E_FL_SHARP    (1<<2) /* edge with sharp angle for forced separation */
#define E_FL_PART_SEP (1<<3) /* edge on partition edge with separation      */

#define E_FLOW_IN_FL(e, et) (E_EDGE_Flag(e, et) & E_FL_FLOW_IN)
#define E_FLOW_OUT_FL(e, et)(E_EDGE_Flag(e, et) & E_FL_FLOW_OUT)
#define E_SHARP_FL(e, et)   (E_EDGE_Flag(e, et) & E_FL_SHARP)
#define E_PART_SEP_FL(e, et)(E_EDGE_Flag(e, et) & E_FL_PART_SEP)

#define MARK_EDGE_FLAG(e, et, flag)   (E_EDGE_Flag(e, et) |=  (flag))
#define UNMARK_EDGE_FLAG(e, et, flag) (E_EDGE_Flag(e, et) &= ~(flag))
#define TOGGLE_EDGE_FLAG(e, et, flag) (E_EDGE_Flag(e, et) ^=  (flag))

/*
 * Edge storage
 */
#define THREAD_FTREE(t)          ((t)->ftree)
#define FE_THREAD(t)             ((FE_Thread *)(THREAD_FTREE((t))))
#define FE_THREAD_ALLOCATED_P(t) (THREAD_FTREE((t)) != NULL)
#define FET_STORAGE(t, nv)       ((t)->storage[nv]) /* This storage is used by both edge and auxciliary face storage */
#define FE_STORAGE(t, n, type)   ((type)FET_STORAGE(t, n))

#define FT_T(ft) ((ft)->t)
#define FT_STORAGE(t, nv) (FET_STORAGE((t), (nv)))
#define FV_ALLOCATED_P(t, nv) (NULL != FT_STORAGE((t), (nv)))

#define FE_STORAGE_I(t, n)    (FE_STORAGE((t), (n), int*))
#define FE_STORAGE_R(t, n)    (FE_STORAGE((t), (n), real*))
#define FE_STORAGE_R_NV(t, n) (FE_STORAGE((t), (n), real (*)[ND_ND]))
#define FE_STORAGE_R_MV(t, n) (FE_STORAGE((t), (n), real (*)[ND_ND][ND_ND]))

/* t is normal face thread */
#define CACHE_T_FV_R(x, t, fv)\
  real * const x = FE_STORAGE_R(FE_THREAD((t)), (fv))
#define CACHE_T_FV_R_NV(x, t, fv)\
  real (* const x)[ND_ND] = FE_STORAGE_R_NV(FE_THREAD((t)), (fv))

#define THREAD_ETREE(t)         ((t)->etree)
#define E_THREAD(t)             ((FE_Thread *)(THREAD_ETREE((t))))
#define E_THREAD_ALLOCATED_P(t) (THREAD_ETREE((t)) != NULL)

#define ET_T(et) ((et)->t)                                       /* edge thread hosting face thread   */
#define ET_T0(et) (ET_T(et)->t0)                                 /* hosting face adjacent cell thread */
#define ET_STORAGE(et, nv) (FET_STORAGE((et), (nv)))
#define ET_EDGE(et) ((E_Edge *)ET_STORAGE((et), EV_EDGE))
#define ET_N_ELEMENTS(et) (THREAD_N_ELEMENTS((et)))

#define E_STORAGE_I(e, et, n)    (FE_STORAGE_I((et), (n))[(e)])
#define E_STORAGE_R(e, et, n)    (FE_STORAGE_R((et), (n))[(e)])
#define E_STORAGE_R_NV(e, et, n) (FE_STORAGE_R_NV((et), (n))[(e)])
#define E_STORAGE_R_MV(e, et, n) (FE_STORAGE_R_MV((et), (n))[(e)])

#define EV_LENGTH(et) (SV_LENGTH((et)))
#define EV_ALLOCATED_P(et, nv) (NULL != ET_STORAGE((et), (nv)))

/* et is edge thread from E_THREAD(t) */
#define CACHE_T_EV_R(x, et, ev)\
  real * const x = FE_STORAGE_R((et), (ev))
#define CACHE_T_EV_R_NV(x, et, ev)\
  real (* const x)[ND_ND] = FE_STORAGE_R_NV((et), (ev))

/* macros for edge variables */
#define E_EDGE(e, et)      (ET_EDGE((et))[(e)])
#define E_EDGE_V0(e, et)   (E_EDGE((e), (et)).v0)
#define E_EDGE_V1(e, et)   (E_EDGE((e), (et)).v1)
#define E_EDGE_T0(e, et)   (E_EDGE((e), (et)).t0)
#define E_EDGE_T1(e, et)   (E_EDGE((e), (et)).t1)
#define E_EDGE_F0(e, et)   (E_EDGE((e), (et)).f0)
#define E_EDGE_F1(e, et)   (E_EDGE((e), (et)).f1)
#define E_EDGE_TB(e, et)   (E_EDGE((e), (et)).tb)
#define E_EDGE_FB(e, et)   (E_EDGE((e), (et)).fb)
#define E_EDGE_Type(e, et) (E_EDGE((e), (et)).type)
#define E_EDGE_Flag(e, et) (E_EDGE((e), (et)).flag)
#define E_SHADOW(e, et)    (E_EDGE((e), (et)).e_shadow)
#define ET_SHADOW(e, et)   (E_EDGE((e), (et)).et_shadow)

#define E_LENGTH_CACHE(e, et)  (E_STORAGE_R_NV((e), (et), EV_LENGTH))
#define E_CENTROID_CACHE(e, et)(E_STORAGE_R_NV((e), (et), EV_CENTROID))
#define E_NORM0_CACHE(e, et)   (E_STORAGE_R_NV((e), (et), EV_NORM0))
#define E_NORM1_CACHE(e, et)   (E_STORAGE_R_NV((e), (et), EV_NORM1))
#define E_NORMC_CACHE(e, et)   (E_STORAGE_R_NV((e), (et), EV_NORMC))

#define E_LENGTH(L, e, et)  NV_V(L,=,E_LENGTH_CACHE((e), (et)))
#define E_CENTROID(x, e, et)NV_V(x,=,E_CENTROID_CACHE((e), (et)))
#define E_NORM0(n, e, et)   NV_V(n,=,E_NORM0_CACHE((e), (et)))
#define E_NORM1(n, e, et)   NV_V(n,=,E_NORM1_CACHE((e), (et)))
#define E_NORMC(n, e, et)   NV_V(n,=,E_NORMC_CACHE((e), (et)))
#define E_ANGLE(e, et)      (E_STORAGE_R((e), (et), EV_ANGLE))

#define E_UPWIND(e, et)     (E_STORAGE_I((e), (et), EV_UPWIND))
#define E_HVFLUX(e, et)     (E_STORAGE_R((e), (et), EV_HVFLUX))
#define E_SHED_COUNT(e, et) (E_STORAGE_I((e), (et), EV_SHED_COUNT))
#define E_SHED_MASS(e, et)  (E_STORAGE_R((e), (et), EV_SHED_MASS))
#define E_SHED_DIAM(e, et)  (E_STORAGE_R((e), (et), EV_SHED_DIAM))

#define E_SCALAR(e, et)  (E_STORAGE_R((e), (et), EV_SCALAR))
#define E_VECTOR(e, et)  (E_STORAGE_R_NV((e), (et), EV_VECTOR))
#define E_TENSOR(e, et)  (E_STORAGE_R_MV((e), (et), EV_TENSOR))

#define E_DUMMY_R(e, et) (E_STORAGE_R((e), (et), EV_DUMMY_R))

#define begin_e_loop(e, et) begin_generic_loop(e, et)
#define end_e_loop(e, et)   end_generic_loop(e, et)

#define FV_STORAGE_I(f, ft, n)    (FE_STORAGE_I((ft), (n))[(f)])
#define FV_STORAGE_R(f, ft, n)    (FE_STORAGE_R((ft), (n))[(f)])
#define FV_STORAGE_R_NV(f, ft, n) (FE_STORAGE_R_NV((ft), (n))[(f)])
#define FV_STORAGE_R_MV(f, ft, n) (FE_STORAGE_R_MV((ft), (n))[(f)])

#define F_STRIP_COUNT(f, t) (FV_STORAGE_I((f), FE_THREAD((t)), FV_STRIP_COUNT))
#define F_STRIP_MASS(f, t)  (FV_STORAGE_R((f), FE_THREAD((t)), FV_STRIP_MASS))
#define F_SHED_COUNT(f, t)  (FV_STORAGE_I((f), FE_THREAD((t)), FV_SHED_COUNT))

#define F_DPM_DYNAMIC_PRES(f, t) (FV_STORAGE_R((f), FE_THREAD((t)), FV_DPM_DYNAMIC_PRES))
#define F_DPM_DYNAMIC_HITS(f, t) (FV_STORAGE_R((f), FE_THREAD((t)), FV_DPM_DYNAMIC_HITS))

#define F_MRF_VELOCITY(f, t)     (FV_STORAGE_R_NV((f), FE_THREAD((t)), FV_MRF_VELOCITY))
#define F_MRF_ACCELERATION(f, t) (FV_STORAGE_R_NV((f), FE_THREAD((t)), FV_MRF_ACCELERATION))

#define F_T_LAMBDA_GF(f, t) (FV_STORAGE_R((f), FE_THREAD((t)), FV_T_LAMBDA_GF))
#define F_T_BULK_TEMP(f, t) (FV_STORAGE_R((f), FE_THREAD((t)), FV_T_BULK_TEMP))

#define F_FILM_MU(f, t) (FV_STORAGE_R((f), FE_THREAD((t)), FV_FILM_MU))
#define F_FILM_CP(f, t) (FV_STORAGE_R((f), FE_THREAD((t)), FV_FILM_CP))
#define F_FILM_KD(f, t) (FV_STORAGE_R((f), FE_THREAD((t)), FV_FILM_KD))

#define F_FILM2VOF(f, t)(FV_STORAGE_I((f), FE_THREAD((t)), FV_FILM_VOF_SWITCH))

#define F_DUMMY_R(f, t)    (FV_STORAGE_R((f), FE_THREAD((t)), FV_DUMMY_R))
#define F_DUMMY_R_NV(f, t) (FV_STORAGE_R_NV((f), FE_THREAD((t)), FV_DUMMY_R_NV))
/* macros for additional face variables (new SV_s) (Note: t is the true wall thread) */
#define UNV_DOT(n, m) MIN(1.0, MAX(-1.0, NV_DOT(n, m)))

/*
 * Transformation MACROs
 */
#define NV_VM_G2L(l,EQ,g,r)\
{\
  real NV_VEC(_g)={0.0};  \
  NV_V((_g),=,(g));   \
  NV_ROTP_V((l),EQ,(_g),(r)); \
}

#define NV_VM_L2G(g,EQ,l,r)\
{\
  real NV_VEC(_l)={0.0};  \
  NV_V((_l),=,(l));   \
  NV_ROTN_V((g),EQ,(_l),(r)); \
}

#define NV_VMM_L2L(y,EQ,x,a,r)\
{\
  real NV_VEC(_x)={0.0};  \
  NV_VM_L2G((_x),EQ,(x),(a)); \
  NV_VM_G2L((y),EQ,(_x),(r)); \
}

#define NT_TV(m,x,y,z)\
ND_VEC(\
       NV_V((m)[0],=,(x)),\
       NV_V((m)[1],=,(y)),\
       NV_V((m)[2],=,(z)))

#define NT_TM(a,b)\
ND_VEC(\
       NV_V((a)[0],=,(b)[0]),\
       NV_V((a)[1],=,(b)[1]),\
       NV_V((a)[2],=,(b)[2]))
/*
 * matrix multiply: B = A . R^T (matrices are ND_ND x ND_ND)
 */
#define _M_A_RT(b,EQ,a,r) MAT_A_RT(b,EQ,a,r)
#define M_A_RT(b,EQ,a,r)\
ND_VEC(\
NV_D((b)[0],=,NV_ROTP_X((a)[0],(r)),NV_ROTP_Y((a)[0],(r)),NV_ROTP_Z((a)[0],(r))),\
NV_D((b)[1],=,NV_ROTP_X((a)[1],(r)),NV_ROTP_Y((a)[1],(r)),NV_ROTP_Z((a)[1],(r))),\
NV_D((b)[2],=,NV_ROTP_X((a)[2],(r)),NV_ROTP_Y((a)[2],(r)),NV_ROTP_Z((a)[2],(r))))
/*
 * matrix multiply: B = A . R (matrices are ND_ND x ND_ND)
 */
#define _M_A_R(b,EQ,a,r) MAT_A_R(b,EQ,a,r)
#define M_A_R(b,EQ,a,r)\
ND_VEC(\
NV_D((b)[0],=,NV_ROTN_X((a)[0],(r)),NV_ROTN_Y((a)[0],(r)),NV_ROTN_Z((a)[0],(r))),\
NV_D((b)[1],=,NV_ROTN_X((a)[1],(r)),NV_ROTN_Y((a)[1],(r)),NV_ROTN_Z((a)[1],(r))),\
NV_D((b)[2],=,NV_ROTN_X((a)[2],(r)),NV_ROTN_Y((a)[2],(r)),NV_ROTN_Z((a)[2],(r))))
/*
 * matrix multiply: B = A^T . R (matrices are ND_ND x ND_ND)
 */
#define M_RT_A(b,EQ,r,a)\
ND_VEC(\
NV_D((b)[0],=,\
     ROTN_X((r)[0][0],(r)[1][0],(r)[2][0],(a)),    \
     ROTN_Y((r)[0][0],(r)[1][0],(r)[2][0],(a)),    \
     ROTN_Z((r)[0][0],(r)[1][0],(r)[2][0],(a))),   \
NV_D((b)[1],=,\
     ROTN_X((r)[0][1],(r)[1][1],(r)[2][1],(a)),    \
     ROTN_Y((r)[0][1],(r)[1][1],(r)[2][1],(a)),    \
     ROTN_Z((r)[0][1],(r)[1][1],(r)[2][1],(a))),   \
NV_D((b)[2],=,\
     ROTN_X((r)[0][2],(r)[1][2],(r)[2][2],(a)),    \
     ROTN_Y((r)[0][2],(r)[1][2],(r)[2][2],(a)),    \
     ROTN_Z((r)[0][2],(r)[1][2],(r)[2][2],(a))))

/* G->L */
#define R_M_RT(m,r,i,j)\
  NVD_DOT((r)[i],NV_DOT((m)[0],(r)[j]),NV_DOT((m)[1],(r)[j]),NV_DOT((m)[2],(r)[j]))
/* L->G */
#define RT_M_R(m,r,i,j)\
  ND_DOT((r)[0][i],(r)[1][i],(r)[2][i],\
   NVD_DOT((m)[0],(r)[0][j],(r)[1][j],(r)[2][j]),\
   NVD_DOT((m)[1],(r)[0][j],(r)[1][j],(r)[2][j]),\
   NVD_DOT((m)[2],(r)[0][j],(r)[1][j],(r)[2][j]))

#define NT_TM_G2L(lt,EQ,gt,r)\
{\
  real _t[ND_ND][ND_ND]={{0.0}};\
  M_A_RT((_t),=,(gt),(r));      \
  M_A_R((lt),=,(r),(_t));       \
}

#define NT_TM_L2G(gt,EQ,lt,r)\
{\
  real _t[ND_ND][ND_ND]={{0.0}};\
  M_A_R((_t),=,(lt),(r));       \
  M_RT_A((gt),=,(r),(_t));      \
}

#define NT_TMM_L2L(y,EQ,x,a,r)\
{\
  real _t[ND_ND][ND_ND]={{0.0}};\
  real _g[ND_ND][ND_ND]={{0.0}};\
  _t[0][0]=(x)[0];\
  _t[0][1]=(x)[1];\
  _t[1][0]=(x)[1];\
  _t[1][1]=(x)[2];\
  NT_TM_L2G(_g,=,_t,(a));       \
  (y)[0]=R_M_RT(_g,(r),0,0);  \
  (y)[1]=R_M_RT(_g,(r),0,1);  \
  (y)[2]=R_M_RT(_g,(r),1,1);    \
}

/* 2D vector macros */
#define N2V_VEC(a)a[2]
#define N2D_VEC(x,y)x,y
#define N2V_S(a,EQ,s)N2D_VEC((a)[0]EQ(s),(a)[1]EQ(s))
#define N2D_S(a0,a1,EQ,s)N2D_VEC((a0)EQ(s),(a1)EQ(s))
#define N2V_V(a,EQ,x)N2D_VEC((a)[0]EQ(x)[0],(a)[1]EQ(x)[1])
#define N2D_D(a0,a1,EQ,x0,x1)N2D_VEC((a0)EQ(x0),(a1)EQ(x1))
#define N2V_D(a,EQ,x0,x1)N2D_D((a)[0],(a)[1],EQ,x0,x1)
#define N2D_V(a0,a1,EQ,x)N2D_D(a0,a1,EQ,(x)[0],(x)[1])

#define N2V_VS(a,EQ,x,S,s)N2D_VEC((a)[0]EQ(x)[0]S(s),(a)[1]EQ(x)[1]S(s))
#define N2V_DS(a,EQ,x0,x1,S,s)N2D_VEC((a)[0]EQ(x0)S(s),(a)[1]EQ(x1)S(s))
#define N2D_VS(a0,a1,EQ,x,S,s)N2D_VEC((a0)EQ(x)[0]S(s),(a1)EQ(x)[1]S(s))
#define N2D_DS(a0,a1,EQ,x0,x1,S,s)N2D_VEC((a0)EQ(x0)S(s),(a1)EQ(x1)S(s))

#define N2V_VV(a,EQ,x,V,y)N2D_VEC((a)[0]EQ(x)[0]V(y)[0],(a)[1]EQ(x)[1]V(y)[1])
#define N2V_DD(a,EQ,x0,x1,V,y0,y1)N2D_VEC((a)[0]EQ(x0)V(y0),(a)[1]EQ(x1)V(y1))
#define N2D_DD(a0,a1,EQ,x0,x1,V,y0,y1)N2D_VEC((a0)EQ(x0)V(y0),(a1)EQ(x1)V(y1))

#define N2V_VV_S(a,EQ,x,V,y,S,s)N2D_VEC((a)[0]EQ((x)[0]V(y)[0])S(s),(a)[1]EQ((x)[1]V(y)[1])S(s))
#define N2V_VVS N2V_VV_S
#define N2V_DV_S(a,EQ,x0,x1,V,y,S,s)N2D_VEC((a)[0]EQ((x0)V(y)[0])S(s),(a)[1]EQ((x1)V(y)[1])S(s))
#define N2V_DD_S(a,EQ,x0,x1,V,y0,y1,S,s)N2D_VEC((a)[0]EQ((x0)V(y0))S(s),(a)[1]EQ((x1)V(y1))S(s))
#define N2D_VV_S(a0,a1,EQ,x,V,y,S,s)N2D_VEC((a0)EQ((x)[0]V(y)[0])S(s),(a1)EQ((x)[1]V(y)[1])S(s))

#define N2D_VD_S(a0,a1,EQ,x,V,y0,y1,S,s)N2D_VEC((a0)EQ((x)[0]V(y0))S(s),(a1)EQ((x)[1]V(y1))S(s))
#define N2D_DV_S(a0,a1,EQ,x0,x1,V,y,S,s)N2D_VEC((a0)EQ((x0)V(y)[0])S(s),(a1)EQ((x1)V(y)[1])S(s))
#define N2D_DD_S(a0,a1,EQ,x0,x1,V,y0,y1,S,s)N2D_VEC((a0)EQ((x0)V(y0))S(s),(a1)EQ((x1)V(y1))S(s))

/* Export EWF model functions and parameters */
FLUENT_EXPORT cxboolean if_wall_film(void);
FLUENT_EXPORT cxboolean if_wall_film_t(void);
FLUENT_EXPORT cxboolean if_wall_film_accretion(void);
FLUENT_EXPORT cxboolean if_wall_film_phase_change(void);
FLUENT_EXPORT cxboolean if_wall_film_secondphase(void);
FLUENT_EXPORT cxboolean if_wall_film_vof_coupled(void);
FLUENT_EXPORT cxboolean if_wall_film_grid_changed(const cxboolean reset);
FLUENT_EXPORT cxboolean FE_THREAD_VALID_P(const Thread *thread);
FLUENT_EXPORT cxboolean E_THREAD_VALID_P(const Thread *thread);

FLUENT_EXPORT void Model_Initialize_film(void);
FLUENT_EXPORT void Init_Eulerian_Wall_Film(Domain *domain, cxboolean restart);
FLUENT_EXPORT void SV_Init_Efilm_Dpm_Source(Domain *domain);
FLUENT_EXPORT void SV_Update_Efilm_Dpm_Source(Domain *domain);
FLUENT_EXPORT void SV_Update_Efilm_Dpm_Pressure(Domain *domain);
FLUENT_EXPORT void Create_All_Wall_Film_Threads(Domain *domain, cxboolean verbose);
FLUENT_EXPORT void Remove_All_Wall_Film_Threads(Domain *domain, cxboolean verbose);

FLUENT_EXPORT cxboolean Get_WFM_Boolean(char *para_name);
FLUENT_EXPORT int  Get_WFM_Int(char *para_name);
FLUENT_EXPORT real Get_WFM_Real(char *para_name);
FLUENT_EXPORT char *Get_WFM_Char(char *para_name);

FLUENT_EXPORT cxboolean Efilm_Height_Non_Small(const face_t f, const Thread *t);
FLUENT_EXPORT void Get_Efilm_Mass_Cutoffs(real *strip, real *shed);
FLUENT_EXPORT real Efilm_Density(face_t f, Thread *t);
FLUENT_EXPORT real Efilm_Viscosity(face_t f, Thread *t);
FLUENT_EXPORT real Efilm_ktc(face_t f, Thread *t);
FLUENT_EXPORT real Efilm_Cp(face_t f, Thread *t);
FLUENT_EXPORT real Get_Dpm_Efilm_Relax(void);
FLUENT_EXPORT Wall_Film_Regime Efilm_Dpm_Impingement(Tracked_Particle *tp, Particle *pn, real f_normal[],
                                                     face_t f, Thread *t, cxboolean update_summary);

FLUENT_EXPORT int Efilm_Edge_Npar(void);
FLUENT_EXPORT Injection *Get_Efilm_Injection(void);
FLUENT_EXPORT cxboolean Check_Efilm_Material(Material *pm);

FLUENT_EXPORT int  Get_Face_Separation(face_t f, Thread *t, real *mdot, real *diam);
FLUENT_EXPORT int  Get_Edge_Separation(edge_t e, FE_Thread *et, real *mdot, real *diam);
FLUENT_EXPORT void compute_efilm_lambda(face_t f, Thread *t, real *lambda_gn, real *lambda_g, real *lambda_f);
FLUENT_EXPORT real compute_mfluid_bulk_temperature(face_t f, Thread *t, real *lambda_gn);

FLUENT_EXPORT real Collect_Film_Phase2_Sources(cell_t c, Thread *t, real *dS, Phase2_Src_Index SRC_INDEX);
FLUENT_EXPORT void Collect_Wall_Film_Phase2_Sources(Domain *domain, Svar sv, Svar sv_s, Svar sv_ap, Delta_Form df);
FLUENT_EXPORT int  Get_Efilm_Phase2_Index(void);

FLUENT_EXPORT void Collect_Film_Phase_Change_Sources(Domain *domain, Svar sv, Svar sv_s, Svar sv_ap, cxboolean is_vapor, Delta_Form df);
FLUENT_EXPORT int  Get_Efilm_Vapor_Index(void);
FLUENT_EXPORT int  Get_Efilm_Vapor_Phase_Index(void);
FLUENT_EXPORT void Film_Mass_Flux_Report(Thread *t, real integral[]);
FLUENT_EXPORT void Film_Heat_Flux_Report(Thread *t, real integral[]);
FLUENT_EXPORT void Get_Efilm_Velocity(const face_t f, const Thread *t, real *film_v, cxboolean surface_v, cxboolean relative_v);
FLUENT_EXPORT real Get_Film_VOF_Transion_Threshold(const Thread *t, const real crit_fraction, cxboolean trans_high);

#if !RP_NODE
#define begin_f_loop_film(f, t) begin_f_loop(f, t)
#define   end_f_loop_film(f, t)   end_f_loop(f, t)
#else
#define begin_f_loop_film(f, t) begin_generic_loop_3(f, t, THREAD_N_ELEMENTS_INT(t), PRINCIPAL_FACE_P(f, t))
#define   end_f_loop_film(f, t)   end_generic_loop_3(f, t)
#endif
#endif /* RP_WALL_FILM */

enum
{
  SEPARATION_FOUCART = 0,
  SEPARATION_OROURKE,   /* O'Rourke & Amsden, SAE 961961 */
  SEPARATION_FRIEDRICH, /* Friedrich ASME May 2008 Vol 130 051301-1. */
  SEPARATION_USER
};

enum
{
  STRIPPING_MAYER = 0, /* MAYER 1961 */
  STRIPPING_FOUCART,   /* FOUCART 2005 */
  STRIPPING_USER
};

FLUENT_EXPORT void Efilm_Dpm_Rebound(Tracked_Particle *tp, real V_p_a[], real V_p[], real We_n, real e_n[],
                                     real V_ref[], real del_mom[], real *rest_n, real *rest_t,
                                     Wall_Impingement_Type impinge_model);

typedef struct _imp_struct
{
  real Re_n;
  real We_n, We_n_cr;
  real Oh;
  real Km, Km_cr;
  real E;
  real T_star;
  real T_crit;
  cxboolean W_cold;
  cxboolean W_wet;
  real Y_splash;
} Imp_State;

FLUENT_EXPORT void InitializeWallFilmPrimitives(void);
FLUENT_EXPORT void Update_Impingement_Parameters(Tracked_Particle *tp, real V_p_n, face_t f, Thread *t,
                                                 Imp_State *Imp_Par, real *film_h, real *dT_s, cxboolean ewf_call);
FLUENT_EXPORT Wall_Film_Regime Efilm_Impingement_Regime(Tracked_Particle *tp, Particle *pn, const real e_n[], face_t f, Thread *t,
                                                        real V_p[], real V_p_rel[], real V_ref[], cxboolean dpm_update,
                                                        Imp_State *Imp_Par, cxboolean ewf_call);
FLUENT_EXPORT void Efilm_Dpm_Rebound(Tracked_Particle *tp, real V_p_a[], real V_p[], real We_n, real e_n[],
                                     real V_ref[], real del_mom[], real *rest_n, real *rest_t,
                                     Wall_Impingement_Type impinge_model);
FLUENT_EXPORT void Efilm_Dpm_Splash_Stanton(Tracked_Particle *tp, Particle *pn, const real e_n[],
                                            real V_p_a[], real V_p[], real V_ref[], int N_parc,
                                            const Imp_State *Imp_Par, cxboolean dpm_update, cxboolean ewf_call);
FLUENT_EXPORT void Efilm_Dpm_Splash_Kuhnke(Tracked_Particle *tp, Particle *pn, const real e_n[], face_t f, Thread *t,
                                           real V_p_a[], real V_p[], real V_ref[], int N_parc,
                                           const Imp_State *Imp_Par, cxboolean dpm_update, cxboolean ewf_call);
FLUENT_EXPORT void UDF_Splash(Tracked_Particle *tp, Particle *pn, real f_normal[], real rel_dot_n, int n_samp, cxboolean update);
FLUENT_EXPORT void Friedrich_Shed_Mdot_Diam(real alpha, real e_norm[], face_t f, Thread *tf,  face_t f_d, Thread *tf_d, real film_v[], 
                                            real film_l, real film_h, real rho_l, real sig_l, real mu_l, real *m_shed, real *d_shed);
FLUENT_EXPORT void Friedrich_Shed_Mdot_Diam_NCI(real alpha, real e_norm[], face_t f_d, Thread *tf_d, real film_v[], real film_l, 
                                                real film_h, real rho_l, real sig_l, real mu_l, real *m_shed, real *d_shed, real U_gas[], real rho_gas, real A[]);
FLUENT_EXPORT real Strip_Weber_Number(face_t f, Thread *t);
FLUENT_EXPORT cxboolean Stripped_Mdot_Diam_new(face_t f, Thread *tf, real time_step, real *mdot, real *diam);

/*    no longer used
 * FLUENT_EXPORT real Efilm_Dpm_Splash(Tracked_Particle *tp, Particle *pn, real V_p_a[], real V_p[], real e_n[], real V_ref[],
 *                                     real We_n, real Ky, real Ky_c, real E, real Km_c, real V_sc, int N_parc, cxboolean update,
 *                                     Wall_Impingement_Type impingement_model);
 * FLUENT_EXPORT void Kuhnke_Splash(Tracked_Particle *tp, Particle *pn, real V_p_a[], real V_p[], real f_e_n[], real V_ref[],
 *                                  int N_parc, cxboolean dpm_update);
 */


#endif /* _FLUENT_FILM_H */
