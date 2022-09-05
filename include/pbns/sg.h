/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/* macros and prototypes for segregated solver */
#ifndef _FLUENT_SG_H
#define _FLUENT_SG_H
#include "dll.h"
#include "typedefs.h"

#include "sg_delta.h"
#include "nci_numerics.h"
#include "flowf.h"

/* normalized variable */
#define NORM_VARIABLE(r,_a,_b,_c)\
{real du = (_c), c = (_a), d = (_b);\
 r = (ABS(du) > 1.e-10) ? (1. - (d - c)/du) : 10.;}

#define JASAK_LIMITER(f,r,c,u,v,b)\
{ if (r < 0. || r > 1.0)\
    f = u;\
  else if (r >= b)\
    f = c;\
  else\
  {real g = r/b;\
   f = g*c+(1.-g)*v;}\
}

#define WBCD_LIMITER(f,r,c,u,v,alfa,cslope)\
  { real beta1 = 0.5-0.4/MAX(alfa,1.0e-30);\
    real beta2 = 0.5+0.4/MAX(alfa,1.0e-30);\
    real g = 1.0;\
    if(r <0.5)\
      g = 0.5*(1.0+tanh(cslope*(r-beta1)));\
    else if(r >= 0.5 && r<= 1.0)\
      g = 1;\
    else\
      {g = 0.5*(1.0-tanh(cslope*(r-beta2)));}\
   f = g*c+(1.-g)*v;\
}
#define GAMMA_NVD_LIMITER(f,r,c,u,v,b)\
{ if (r < 0. || r > 1.0)\
    f = u;\
  else if (r >= b)\
    f = c;\
  else\
  {real g = r*r/b/b;\
   f = g*c+(1.-g)*v;}\
}

enum bcd_skew_scheme_
{
  SKEW_LINE_RECONSTRUCTION = 0,
  FACE_RECONSTRUCTION = 1,
  FACE_NORMAL_PROJECTION = 2
};

typedef enum bcd_skew_scheme_ bcd_skew_scheme;

enum noise_filter_marking_scheme_
{
  MARKING_ALL_BUT_DPM = 0,
  MARKING_SOLID = 1
};

typedef enum noise_filter_marking_scheme_ noise_filter_marking_scheme ;

FLUENT_EXPORT extern bcd_skew_scheme bcd_skew_mode;
FLUENT_EXPORT extern bcd_skew_scheme bcd_dbns_skew_mode;
FLUENT_EXPORT extern cxboolean bcd_tanh_blending ;
FLUENT_EXPORT extern cxboolean bcd_jasak_blending ;
FLUENT_EXPORT extern cxboolean  bcd_const_blending ;
FLUENT_EXPORT extern cxboolean  bcd_dbns_const_blending ;
FLUENT_EXPORT extern real bcd_const_blend_factor;
FLUENT_EXPORT extern cxboolean  bcd_jasak ;
FLUENT_EXPORT extern cxboolean bcd_bound_field ;
FLUENT_EXPORT extern real bcd_alfa ;
FLUENT_EXPORT extern real bcd_c ;
FLUENT_EXPORT extern int bcd_freeze_iter ;
FLUENT_EXPORT extern cxboolean use_mrf_advection;
FLUENT_EXPORT extern cxboolean use_msolid_advection;

/* u => upwind cell, uu => cell upwind of upwind cell, d => downwind cell */
typedef struct face_upwind_cv_struct
{
  cell_t u, uu, d;           /* cell id */
  Thread *tu, *tuu, *td;     /* cell thread */
  int Tu, Tuu, Td;           /* cell's location (interior, periodic, boundary */
  real Su, Suu, Sd;          /* distance from face (Suu is distance between u and uu) */
  real qu, quu, qd;          /* scalar value */
  face_t o;                  /* opposite face */
  Thread  *to;               /* opposite face's thread */
  Thread *tf;
  face_t f;
} Face_Upwind_CV;

typedef struct tnode
{

  int ctid;
  int tid;

  int *ifzones;
  int *bfzones;
  int *pbfzones;

  struct tnode *left;
  struct tnode *right;

} Treenode;

enum high_order_rc_scheme
{
  HO_RC_OFF = 0,
  HO_RC_RECON = 1,
  HO_RC_AP_RECON = 2,
  HO_RC_INTERPOL = 3,
  HO_RC_UDIFF = 4,
  HO_RC_DENSITY_WEIGHTED = 5,
  HO_RC_AP_VOL_AVG_RECON = 6
};

enum discretization_scheme
{
  FIRST_ORDER_UPWIND = 0,
  SECOND_ORDER_UPWIND = 1,
  POWER_LAW = 2,
  CENTRAL_DIFFERENCING = 3,
  QUICK = 4,
  HRIC = 5,
  THIRD_ORDER_MUSCL = 6,
  HR_BLEND = 7,
  CICSAM = 8,

  /* the LES flux for the cpld solver */
  LOW_DIFFUSION_FLUX = 9,

  /* these are for face pressure interpolation */
  MOMENTUM_WEIGHTED_P = 10, /* default */
  LINEAR_P = 11,
  RECON_P = 12,
  DENSITY_WEIGHTED_P = 13,
  PRESTO_P = 14,
  CONTINUITY_P = 15,

  GEOM_RECON = 16,
  DONOR_ACCEPTOR = 17,

  MODIFIED_BFW_P = 18,

  SIMPLE  = 20,
  SIMPLEC = 21,
  PISO    = 22,
  PC_SIMPLE = 23,
  COUPLED = 24,
  FRACT_STEP = 25,
  M_P_COUPLED = 26,
  M_P_FULL_COUPLED = 27,

  COMPRESSIVE = 28,
  BGM = 29,
  PC_PISO  = 30
};

typedef enum discretization_scheme Discretization_Scheme;

/* residual scaling parameters */
enum residual_scaling_option
{
  COMPONENTWISE_NORMALIZATION = 0,
  TENSOR_AVG_TRACE = 1,
  TENSOR_MAGNITUDE = 2
};

/* second order time formulation */

enum second_order_time_discretization
{
  CONSERVATIVE_VAR_FORM = 0,
  PRIMITIVE_VAR_FORM = 1
};

enum time_bounded_var_option
{
  BETA_ZERO = 0,
  BETA_ONE = 1,
  BETA_BOUNDED = 2
};

typedef enum time_bounded_vars  /* flags assignment for set of variables */
{
  VAR_UNBOUNDED = 0,
  VAR_RHO,
  VAR_VOF,
  VAR_TURB,
  VAR_REACTING,  /* bounded between 0 and 1 */
  VAR_REACTING1, /* bounded between 0 and 0.25 */
  VAR_PB_BIN,    /* bounded between 0 and 1 */
  VAR_PB_MOMENT, /* lower bound for moments */
  VAR_ENERGY,
  VAR_BOUNDED_MAX
} Time_Bounded_Var;

typedef struct time_bounded_variable_struct
{
  real beta_ph, beta_nh;  /* beta factors */
  int bounded_option;     /* 0 = First order, 1 = second order, 2= bounded */
  cxboolean lower_bnd;    /* check for availability of lower bound */
  cxboolean upper_bnd;    /* checks for availability of bounds */
  real lval, uval;        /* values of lower and upper bounds */
  cxboolean first_order_form; /* force complete transient term to be first order */
} Time_Bounded_Var_Struct;

extern FLUENT_EXPORT Time_Bounded_Var_Struct time_bounded_var_struct[VAR_BOUNDED_MAX];

#define BETA_FACE_PH(f,t) F_STORAGE_R(f,t,SV_BETA_FACE_PH)
#define BETA_FACE_NH(f,t) F_STORAGE_R(f,t,SV_BETA_FACE_NH)
extern FLUENT_EXPORT int so_verbose;
extern FLUENT_EXPORT cxboolean hybrid_transient_need_m2;
extern FLUENT_EXPORT cxboolean enhanced_second_order_in_time_p;
extern FLUENT_EXPORT void Update_Transient_Parameters_in_Subdomains(Domain *domain);
extern FLUENT_EXPORT void Set_Timestep_Size_Ratio(Domain *domain);
extern FLUENT_EXPORT void Read_Timestep_Size_Ratio(Domain *domain);
extern FLUENT_EXPORT void Init_Transient_Parameters(Domain *domain);
extern FLUENT_EXPORT void Reset_Transient_Parameters(Domain *domain, cxboolean reset_rp_values_p);
extern FLUENT_EXPORT void Update_Transient_Parameters(Domain *domain);
extern FLUENT_EXPORT void Set_Transient_Coefficient(Domain *domain, int time_step_index);
extern FLUENT_EXPORT void Update_Old_Time_Level_Beta(Domain *domain);
extern FLUENT_EXPORT void Compute_Time_Global_Beta(Domain *domain, Svar sv_beta);
extern FLUENT_EXPORT void Zero_Current_Time_Level_Beta(Domain *domain);
extern FLUENT_EXPORT void Zero_Transient_Beta_Remesh(Domain *domain, Thread *tc, cat_t *remesh_cell_list, Svar beta_g, int n_cells);
extern FLUENT_EXPORT void Fill_Grid_Flux_Coefficients(Domain *domain);
extern FLUENT_EXPORT void Print_Time_Parameters(Domain *domain);

typedef struct second_ord_correc_info
{
  ConstRealArray phi0;
  ConstRealArray phi1;
  ConstRealVectorArray phi_rg0;
  ConstRealVectorArray phi_rg1;
  ConstRealArray hr_beta_fact0;
  ConstRealArray hr_beta_fact1;
  ConstRealArray vol0;
  ConstRealArray vol1;
  ConstRealVectorArray centroid0;
  ConstRealVectorArray f_centroid;
  ConstRealVectorArray f_area;
} Second_Ord_Correc_Info;

extern FLUENT_EXPORT  Second_Ord_Correc_Info Get_Second_Ord_Correc_Info(Thread *thread, Svar, Svar);

/*implemented in src/numerics/contact numerics.c */
extern FLUENT_EXPORT cxboolean Activate_Secondary_Gradient_P(Svar nv, cxboolean set_auxillary_p);
extern FLUENT_EXPORT void Secondary_Gradient_Exclusion_Via_Viscous_Gradient(Domain *domain, Svar nv, Svar dw, Svar rgw);

#if RP_3D
#define MOM_SECONDARY_GRADIENT_SOURCE(source,dv,dx,A_by_es,A,k)\
{source[0] = k*(NV_DOT(dv[0],A) - NV_DOT(dv[0],dx)*A_by_es);\
 source[1] = k*(NV_DOT(dv[1],A) - NV_DOT(dv[1],dx)*A_by_es);\
 source[2] = k*(NV_DOT(dv[2],A) - NV_DOT(dv[2],dx)*A_by_es);}
#else
#define MOM_SECONDARY_GRADIENT_SOURCE(source,dv,dx,A_by_es,A,k)\
{source[0] = k*(NV_DOT(dv[0],A) - NV_DOT(dv[0],dx)*A_by_es);\
 source[1] = k*(NV_DOT(dv[1],A) - NV_DOT(dv[1],dx)*A_by_es);}
#endif

#define SECONDARY_GRADIENT_SOURCE(source,n,dphi,dx,A_by_es,k)\
{  NV_VVS(dphi, =, C_STORAGE_R_NV(c0,t0,n), +, C_STORAGE_R_NV(c1,t1,n), /, 2.);\
source = k*(NV_DOT(dphi,A)-NV_DOT(dphi, dx)*A_by_es);}

#define MRF_SECONDARY_GRADIENT_SOURCE(source,n,dphi,dx,A_by_es,k)\
{source = k*(NV_DOT(dphi,A)-NV_DOT(dphi, dx)*A_by_es);}

/* long diffusion secondary gradient for solids in porous zones */
#define SECONDARY_GRADIENT_SOURCE_LD(source,n,A,dr0,dr1,A_by_dr0,A_by_dr1,k)\
{\
 real NV_VEC(_dphi0), NV_VEC(_dphi1);\
 real NV_VEC(lp0),NV_VEC(lp1),NV_VEC(lp);\
 NV_VS(lp,=,A,/,A_by_dr0);\
 NV_VV(lp0,=,lp,-,dr0);\
 NV_V(_dphi0,=,C_STORAGE_R_NV(c0,t0,n));\
 NV_VS(lp ,=,A,/,A_by_dr1);\
 NV_VV(lp1,=,lp,-,dr1);\
 NV_V(_dphi1,=,C_STORAGE_R_NV(c1,t1,n));\
 source = k*(NV_DOT(_dphi0,lp0) - NV_DOT(_dphi1,lp1));\
}

#define SECONDARY_GRADIENT_SOURCE_LONG(source,sv_g,A,es0,es1,A_by_es0,A_by_es1,d0,d1,k)\
  {\
    real NV_VEC(_dphi), NV_VEC(_dphi0), NV_VEC(_dphi1);\
    real _d = d0 + d1;\
    real _ws = 0.0;\
    if (_d == 0.0) {\
      source = 0.0;\
    }\
    else {\
      _ws = d0 / _d;\
      NV_VS(_dphi0, =, C_STORAGE_R_NV(c0,t0,sv_g), *, _ws);\
      NV_V(_dphi, =, _dphi0);\
      _ws = d1 /_d;\
      NV_VS(_dphi1, =, C_STORAGE_R_NV(c1,t1,sv_g), *, _ws);\
      NV_V(_dphi, +=, _dphi1);\
      source = k*(NV_DOT(_dphi,A)-(NV_DOT(_dphi0,es0)*A_by_es0+NV_DOT(_dphi1,es1)*A_by_es1));\
    }\
  }

/* Limits secondary gradient source based on n.s */
#define SECONDARY_GRADIENT_SOURCE_LIM(lim,A,es,fmin,fmax)\
  {\
    real n_dot_s = NV_DOT(A,es) / (NV_MAG(A)*NV_MAG(es));\
    if (n_dot_s <= fmin)\
      lim = 0.0;\
    else if (n_dot_s >= fmax)\
      lim = 1.0;\
    else\
      lim = (n_dot_s-fmin) / (fmax-fmin);\
  }

#define POROUS_SECONDARY_GRADIENT_SOURCE(c0,t0,source,n,dphi,dx,A_by_es,k)\
{     NV_V(dphi, =, C_STORAGE_R_NV(c0,t0,n));\
source = k*(NV_DOT(dphi,A)-NV_DOT(dphi, dx)*A_by_es);}

#define BOUNDARY_SECONDARY_GRADIENT_SOURCE(source,n,dphi,dx,A_by_es,k)\
{     NV_V(dphi, =, C_STORAGE_R_NV(c0,t0,n));\
source = k*(NV_DOT(dphi,A)-NV_DOT(dphi, dx)*A_by_es);}

#define BOUNDARY_C1_SECONDARY_GRADIENT_SOURCE(source,n,dphi,dx,A_by_es,k)\
{     NV_V(dphi, =, C_STORAGE_R_NV(c1,t1,n));\
source = k*(NV_DOT(dphi,A)-NV_DOT(dphi, dx)*A_by_es);}

#define BOUNDARY_SHADOW_SECONDARY_GRADIENT_SOURCE(source,n,dphi,dx,A_by_es,k)\
{     NV_V(dphi, =, C_STORAGE_R_NV(c1,t1,n));\
source = k*(NV_DOT(dphi,A_s)-NV_DOT(dphi, dx)*A_by_es);}

#define PERIODIC_SECONDARY_GRADIENT_SOURCE(source,n,dphi,dx,A_by_es,k,m)\
{     NV_V(dphi, =, C_STORAGE_R_NV(c0,t0,n));\
     NV_ROTN_V(dphi, +=, C_STORAGE_R_NV(c1,t1,n),m);\
     NV_S(dphi,/=,2);\
source = k*(NV_DOT(dphi,A)-NV_DOT(dphi, dx)*A_by_es);}

#define PERIODIC_SECONDARY_GRADIENT_SOURCE_LONG(source,sv_g,dphi,A,es,A_by_es,d0,d1,k,m) \
  { \
     real dT[ND_ND]; \
     real d = d0 + d1; \
     real ws = 0.0; \
     if (d == 0.0) {\
       source = 0.0;\
     }\
     else {\
       ws = d0/d;\
       NV_VS(dphi, =, C_STORAGE_R_NV(c0,t0,sv_g), *, ws);       \
       NV_ROTN_V(dT, =, C_STORAGE_R_NV(c1,t1,sv_g), m);         \
       ws = d1/d;                                               \
       NV_VS(dphi, +=, dT, *, ws);                              \
       source = k*(NV_DOT(dphi,A)-NV_DOT(dphi,es)*A_by_es);     \
     }\
  }

#if LSQ_RECON
#define LSQ_PERIODIC_SECONDARY_GRADIENT_SOURCE(source,n,dphi,dx,s,A_by_es,k,m)\
{     NV_VS(dphi, =, C_STORAGE_R_NV(c0,t0,n), *, s);\
      NV_DS(dphi, +=, NV_ROTN_X(C_STORAGE_R_NV(c1,t1,n),m),\
                NV_ROTN_Y(C_STORAGE_R_NV(c1,t1,n),m),\
          NV_ROTN_Z(C_STORAGE_R_NV(c1,t1,n),m), *, (1.- s));\
source = k*(NV_DOT(dphi,A)-NV_DOT(dphi, dx)*A_by_es);}
#define LSQ_SECONDARY_GRADIENT_SOURCE(source,n,dphi,dx,s,A_by_es,k)\
{NV_VS_VS(dphi, =, C_STORAGE_R_NV(c0,t0,n),*,s, +,C_STORAGE_R_NV(c1,t1,n),*, (1.-s));\
source = k*(NV_DOT(dphi,A)-NV_DOT(dphi, dx)*A_by_es);}

#define MRF_LSQ_SECONDARY_GRADIENT_SOURCE(source,n,dphi,dx,s,A_by_es,k)\
{source = k*(NV_DOT(dphi,A)-NV_DOT(dphi, dx)*A_by_es);}

#define NODE_LSQ_SECONDARY_GRADIENT_SOURCE(source,sv_n,sv_c,dphi,dx,A_by_es,mu,phi0,phi1)\
{int k;\
 NV_S(dphi,=,0.0);\
   f_node_loop (f,t,k) {\
     register Node *v = F_NODE(f,t,k);\
     NV_V(dphi, +=,N_STORAGE_R_NV(NODE_INDEX(v),NODE_THREAD(v),sv_n));\
  }\
  NV_S(dphi,/=,(F_NNODES(f,t)));\
  source =mu*(NV_DOT(dphi,A)-(phi1-phi0)/dx*A_by_es);}
#endif
#define FACE_AV_VEC(vec,n)\
     NV_VVS(vec, =, C_STORAGE_R_NV(c0,t0,n), +, C_STORAGE_R_NV(c1,t1,n), *, 0.5)

#define PERIODIC_FACE_AV_VEC(vec,n,m)\
{     NV_V(vec, =, C_STORAGE_R_NV(c0,t0,n));\
     NV_ROTN_V(vec, +=, C_STORAGE_R_NV(c1,t1,n),m);\
NV_S(vec,*=,0.5);}


#define SECOND_ORDER_CORRECTION(n,c,t,dx) NV_DOT(C_STORAGE_R_NV(c,t,n),dx)
#define SECOND_ORDER_CORRECTION_CACHE(_cp,c,dx) NV_DOT(_cp[c],dx)

#if RP_2D
# define FACE_VELOCITY_DIVERGENCE(f,t,t0,t1,DV,v0,v1)\
  (explicit_zero_divergence ? 0 : (ND_SUM(DV[0][0],DV[1][1],DV[2][2])+\
   (rp_axi ?\
    0.5*(v0+v1)/F_AVE_Y(f,t) : 0)))
# define BOUNDARY_FACE_VELOCITY_DIVERGENCE(f,t,t0,DV,v0)\
  (explicit_zero_divergence ? 0 :  ND_SUM(DV[0][0],DV[1][1],DV[2][2])+\
   (rp_axi ?\
    v0/F_AVE_Y(f,t) : 0))
#if 0 /*old definition*/
# define FACE_VELOCITY_DIVERGENCE(f,t,t0,t1,DV)\
  (explicit_zero_divergence ? 0 : (ND_SUM(DV[0][0],DV[1][1],DV[2][2])+\
   (rp_axi ?\
    (C_V(F_C0(f,t),t0) + C_V(F_C1(f,t),t1))/(NODE_Y(F_NODE(f,t,0))+NODE_Y(F_NODE(f,t,1))) : 0)))
# define BOUNDARY_FACE_VELOCITY_DIVERGENCE(f,t,t0,DV)\
  (explicit_zero_divergence ? 0 :  ND_SUM(DV[0][0],DV[1][1],DV[2][2])+\
   (rp_axi ?\
    (2.*C_V(F_C0(f,t),t0))/(NODE_Y(F_NODE(f,t,0))+NODE_Y(F_NODE(f,t,1))) : 0))
#endif

# define C_VELOCITY_DIVERGENCE(c,t)\
  (explicit_zero_divergence ? 0 :  ND_SUM(C_DUDX(c,t),C_DVDY(c,t),C_DWDZ(c,t))+\
   (rp_axi ?\
    C_V(c,t)*C_VOLUME_2D(c,t)/C_VOLUME(c,t) : 0))
#else
# define FACE_VELOCITY_DIVERGENCE(f,t,t0,t1,DV,v0,v1)\
    (explicit_zero_divergence ? 0 : ND_SUM(DV[0][0],DV[1][1],DV[2][2]))
# define BOUNDARY_FACE_VELOCITY_DIVERGENCE(f,t,t0,DV,v0)\
    (explicit_zero_divergence ? 0 : ND_SUM(DV[0][0],DV[1][1],DV[2][2]))
# define C_VELOCITY_DIVERGENCE(c,t)\
    (explicit_zero_divergence ? 0 : ND_SUM(C_DUDX(c,t),C_DVDY(c,t),C_DWDZ(c,t)))
#endif

#if 0
#if sys_ultra_64
#define INTERIOR_FACE_GEOMETRY(f,t,A,ds,es,A_by_es,dr0,dr1)\
{ real NV_VEC(xf);\
   double NV_VEC(esd);\
    F_AREA(A, f,t);\
    C_CENTROID(dr0, F_C0(f,t),t->t0);\
    C_CENTROID(dr1, F_C1(f,t),t->t1);\
    NV_VV(es, =, dr1,-,dr0);\
   NV_V(esd,=,es);\
   ds = NV_MAG(esd);\
    NV_S(es,/=,ds);\
    A_by_es = NV_DOT(A,A)/NV_DOT(es,A);\
    F_CENTROID(xf, f,t);\
    NV_VV(dr0, =, xf,-,dr0);\
    NV_VV(dr1, =, xf,-,dr1);\
}
#else
#define INTERIOR_FACE_GEOMETRY(f,t,A,ds,es,A_by_es,dr0,dr1)\
{ real NV_VEC(xf);\
    F_AREA(A, f,t);\
    C_CENTROID(dr0, F_C0(f,t),t->t0);\
    C_CENTROID(dr1, F_C1(f,t),t->t1);\
    NV_VV(es, =, dr1,-,dr0);\
    ds = NV_MAG(es);\
    NV_S(es,/=,ds);\
    A_by_es = NV_DOT(A,A)/NV_DOT(es,A);\
    F_CENTROID(xf, f,t);\
    NV_VV(dr0, =, xf,-,dr0);\
    NV_VV(dr1, =, xf,-,dr1);\
}
#endif
#else
#define INTERIOR_FACE_GEOMETRY(f,t,A,ds,es,A_by_es,dr0,dr1)\
{   F_AREA(A, f,t); \
    F_DR0(dr0, f,t); \
    F_DR1(dr1, f,t); \
    ds = FAST_F_STORAGE_R(f, t, SV_FACE_DS); \
    A_by_es = FAST_F_STORAGE_R(f, t, SV_FACE_ABYES); \
    NV_V (es, =, FAST_F_STORAGE_R_NV(f, t, SV_FACE_ES)); \
}
#define INTERIOR_SHELL_FACE_GEOMETRY(f,t,A,ds,es,A_by_es,dr0,dr1)\
{\
  real NV_VEC(x0), NV_VEC(x1), NV_VEC(xf);\
  cell_t C0 = F_C0(f,t);\
  cell_t C1 = F_C1(f,t);\
  Thread * PTR_RESTRICT T0=t->t0;\
  Thread * PTR_RESTRICT T1=t->t1;\
  C_CENTROID(x0, C0,T0);\
  C_CENTROID(x1, C1,T1);\
  F_CENTROID(xf, f,t);\
  F_AREA(A, f,t); \
  NV_VV(es, =, x1,-,x0);\
  ds = NV_MAG(es);\
  NV_S(es,/=,ds);\
  A_by_es = NV_DOT(A,A)/NV_DOT(es,A);\
  NV_VV(dr0, =, xf,-,x0);\
  NV_VV(dr1, =, xf,-,x1);\
}
#endif

#if 0
#define INTERIOR_FACE_GEOMETRY_LONG(f,t,A,ds,es,es0,es1,A_by_es,A_by_es0,A_by_es1,dr0,dr1)\
{ \
    real NV_VEC(xf);\
    F_AREA(A, f,t);\
    C_CENTROID(dr0, F_C0(f,t),t->t0);\
    C_CENTROID(dr1, F_C1(f,t),t->t1);\
    NV_VV(es, =, dr1,-,dr0);\
    ds = NV_MAG(es);\
    NV_S(es,/=,ds);\
    A_by_es = NV_DOT(A,A)/NV_DOT(es,A);\
    F_CENTROID(xf, f,t);\
    NV_VV(dr0, =, xf,-,dr0);\
    NV_VV(dr1, =, xf,-,dr1);\
    NV_VS(es0, =, dr0, /, NV_MAG(dr0)); \
    NV_VS(es1, =, dr1, /, NV_MAG(dr1)); \
    A_by_es0 = NV_DOT(A,A)/NV_DOT(es0,A); \
    A_by_es1 = NV_DOT(A,A)/NV_DOT(es1,A); \
}
#else
#define INTERIOR_FACE_GEOMETRY_LONG(f,t,A,ds,es,es0,es1,A_by_es,A_by_es0,A_by_es1,dr0,dr1)\
{   F_AREA(A, f,t); \
    F_DR0(dr0, f,t); \
    F_DR1(dr1, f,t); \
    ds = FAST_F_STORAGE_R(f, t, SV_FACE_DS); \
    A_by_es = FAST_F_STORAGE_R(f, t, SV_FACE_ABYES); \
    NV_V (es,  =, FAST_F_STORAGE_R_NV(f, t, SV_FACE_ES)); \
    NV_VS(es0, =, dr0, /, NV_MAG(dr0)); \
    NV_VS(es1, =, dr1, /, NV_MAG(dr1)); \
    A_by_es0 = NV_DOT(A,A)/NV_DOT(es0,A); \
    A_by_es1 = NV_DOT(A,A)/NV_DOT(es1,A); \
}
#endif
/* long diffusion for solid materials in porous regions */
#define INTERIOR_FACE_GEOMETRY_LD(f,t,A,fA,ds,es,A_by_es,dr0,dr1,d0,d1,A_by_dr0,A_by_dr1)\
{\
  F_AREA(A, f,t); \
  F_DR0(dr0, f,t); \
  F_DR1(dr1, f,t); \
  ds = FAST_F_STORAGE_R(f, t, SV_FACE_DS); \
  A_by_es = FAST_F_STORAGE_R(f, t, SV_FACE_ABYES); \
  NV_V (es,  =, FAST_F_STORAGE_R_NV(f, t, SV_FACE_ES)); \
  A_by_dr0 = NV_DOT(A,A)/NV_DOT(dr0,A); \
  A_by_dr1 = NV_DOT(A,A)/NV_DOT(dr1,A); \
  fA =  NV_MAG(A);        /* face Area magnitude */ \
  d0 =  NV_DOT(dr0,A)/fA; /* dr0 = X_f - X_c0    */ \
  d1 =  NV_DOT(dr1,A)/fA; /* dr1 = X_f - X_c1    */ \
  if(d0 < REAL_MIN) d0 = ABS(d0); /* in case of dr0 or dr1  */ \
  if(d1 < REAL_MIN) d1 = ABS(d1); /* in opp. dir. w.r.t A */ \
}

#define INTERIOR_FACE_SHADOW_GEOMETRY(f,t,A,ds,es,A_by_es,dr0,dr1)\
{ real NV_VEC(xf);\
    F_AREA(A, f,t);\
    C_CENTROID(dr0, F_C0(f,t),t->t0);\
    C_CENTROID(dr1, F_C0(F_SHADOW(f,t),THREAD_SHADOW(t)),THREAD_SHADOW(t)->t0);\
    NV_VV(es, =, dr1,-,dr0);\
    ds = NV_MAG(es);\
    NV_S(es,/=,ds);\
    A_by_es = NV_DOT(A,A)/NV_DOT(es,A);\
    F_CENTROID(xf, f,t);\
    NV_VV(dr0, =, xf,-,dr0);\
    NV_VV(dr1, =, xf,-,dr1);\
}

#define INTERIOR_FACE_SHADOW_GEOMETRY_LONG(f,t,A,ds,es,es0,es1,A_by_es,A_by_es0,A_by_es1,dr0,dr1)\
{ real NV_VEC(xf);\
    F_AREA(A,f,t);\
    C_CENTROID(dr0, F_C0(f,t), t->t0);\
    C_CENTROID(dr1, F_C0(F_SHADOW(f,t),THREAD_SHADOW(t)),THREAD_SHADOW(t)->t0);\
    NV_VV(es, =, dr1,-,dr0);\
    ds = NV_MAG(es);\
    NV_S(es,/=,ds);\
    A_by_es = NV_DOT(A,A)/NV_DOT(es,A);\
    F_CENTROID(xf, f,t);\
    NV_VV(dr0, =, xf,-,dr0);\
    NV_VV(dr1, =, xf,-,dr1);\
    NV_VS(es0, =, dr0, /, NV_MAG(dr0)); \
    NV_VS(es1, =, dr1, /, NV_MAG(dr1)); \
    A_by_es0 = NV_DOT(A,A)/NV_DOT(es0,A); \
    A_by_es1 = NV_DOT(A,A)/NV_DOT(es1,A); \
}

#define PERIODIC_FACE_GEOMETRY(f,t,A,ds,es,A_by_es,dr0,dr1,rm)\
{ real NV_VEC(xf), NV_VEC(dr1r);\
    F_AREA(A, f,t);\
    C_CENTROID(dr0, F_C0(f,t),t->t0);\
    F_CENTROID(xf, f,t);\
    NV_VV(dr0, =, xf,-,dr0);\
    F_CENTROID(xf, F_SHADOW(f,t),THREAD_SHADOW(t));\
    C_CENTROID(dr1, F_C1(f,t),t->t1);\
    NV_VV(dr1, =, xf,-,dr1);\
    NV_ROTN_V(dr1r, =, dr1,rm);\
    NV_VV(es, =, dr0,-,dr1r);\
    ds = NV_MAG(es);\
    NV_S(es,/=,ds);\
    A_by_es = NV_DOT(A,A)/NV_DOT(es,A);\
}

#define BOUNDARY_FACE_GEOMETRY(f,t,A,ds,es,A_by_es,dr0)\
{ real NV_VEC(xf);\
    F_AREA(A, f,t);\
    C_CENTROID(dr0, F_C0(f,t),t->t0);\
    F_CENTROID(xf, f,t);\
    NV_VV(dr0, =, xf,-,dr0);\
    ds = NV_MAG(dr0);\
    NV_VS(es,=,dr0,/,ds);\
    A_by_es = NV_DOT(A,A)/MAX(NV_DOT(es,A), REAL_MIN);\
}

#define BOUNDARY_C1_FACE_GEOMETRY(f,t,A,ds,es,A_by_es,dr0)\
{ real NV_VEC(xf);\
    F_AREA(A, f,t);\
    C_CENTROID(dr0, F_C1(f,t),t->t1);\
    F_CENTROID(xf, f,t);\
    NV_VV(dr0, =, xf,-,dr0);\
    ds = NV_MAG(dr0);\
    NV_VS(es,=,dr0,/,ds);\
    A_by_es = NV_DOT(A,A)/NV_DOT(es,A);\
}

#if 0
#define INTERIOR_FACE_GEOMETRY_SHORT(f,t,A,dr0,dr1)\
{   real NV_VEC(xf);\
    F_AREA(A, f,t);\
    C_CENTROID(dr0, F_C0(f,t),t->t0);\
    C_CENTROID(dr1, F_C1(f,t),t->t1);\
    F_CENTROID(xf, f,t);\
    NV_VV(dr0, =, xf,-,dr0);\
    NV_VV(dr1, =, xf,-,dr1);\
}
#else
#define INTERIOR_FACE_GEOMETRY_SHORT(f,t,A,dr0,dr1)\
{   F_AREA(A, f,t);\
    F_DR0(dr0, f,t);\
    F_DR1(dr1, f,t);\
}
#endif

#define PERIODIC_FACE_GEOMETRY_SHORT(f,t,A,dr0,dr1)\
{ real NV_VEC(xf);\
    F_AREA(A, f,t);\
    C_CENTROID(dr0, F_C0(f,t),t->t0);\
    F_CENTROID(xf, f,t);\
    NV_VV(dr0, =, xf,-,dr0);\
    F_CENTROID(xf, F_SHADOW(f,t),THREAD_SHADOW(t));\
    C_CENTROID(dr1, F_C1(f,t),t->t1);\
    NV_VV(dr1, =, xf,-,dr1);\
}

#define BOUNDARY_FACE_GEOMETRY_SHORT(f,t,A,dr0)\
{ real NV_VEC(xf);\
    F_AREA(A, f,t);\
    C_CENTROID(dr0, F_C0(f,t),t->t0);\
    F_CENTROID(xf, f,t);\
    NV_VV(dr0, =, xf,-,dr0);\
}

#define FACE_VOF_FOR_DIFFUSION(f,t,c0,t0,c1,t1) \
  (NULLP(THREAD_STORAGE(t,SV_VOF)) ? \
    1. : \
    (((C_VOF(c0,t0) < VOF_LOW_CUTOFF) && (C_VOF(c1,t1) < VOF_LOW_CUTOFF)) ? \
     0. : \
     (((C_VOF(c0,t0) < VOF_LOW_CUTOFF) || (C_VOF(c1,t1) < VOF_LOW_CUTOFF)) ? \
      VOF_LOW_CUTOFF : \
      F_VOF(f,t))))

#define GET_INTERIOR_FACE_GEOMETRY_DR0(f,t,dr0,stored_dr0)\
{ if (SV_ALLOCATED_P(t, SV_FACE_DR0))\
     NV_V(dr0, =, stored_dr0);\
  else\
     NV_VV(dr0,=,F_CENTROID_CACHE(f,t),-,C_CENTROID_CACHE(F_C0(f, t), F_C0_THREAD(f, t)));\
}

#define GET_INTERIOR_FACE_GEOMETRY_DR1(f,t,dr1,stored_dr1)\
{ if (SV_ALLOCATED_P(t, SV_FACE_DR1))\
     NV_V(dr1, =, stored_dr1);\
  else\
     NV_VV(dr1,=,F_CENTROID_CACHE(f,t),-,C_CENTROID_CACHE(F_C1(f, t), F_C1_THREAD(f, t)));\
}

#define GET_INTERIOR_FACE_GEOMETRY_DR(f, t, dr0, dr1, stored_dr0, stored_dr1)\
{ GET_INTERIOR_FACE_GEOMETRY_DR0(f, t, dr0, stored_dr0);\
  GET_INTERIOR_FACE_GEOMETRY_DR1(f, t, dr1, stored_dr1);\
}
extern FLUENT_EXPORT cxboolean node_weight_initialized_p;
extern FLUENT_EXPORT cxboolean force_init_node_weights;
extern FLUENT_EXPORT cxboolean node_grad_weight_initialized_p;
extern FLUENT_EXPORT int discr_scheme;
extern FLUENT_EXPORT int second_order_time_form;
extern FLUENT_EXPORT cxboolean power_law; /* set in sg_*.c */
extern FLUENT_EXPORT cxboolean second_order;  /* set in sg_*.c */
extern FLUENT_EXPORT real bcd_beta_mom;          /* set in sg_mom.c  */

#if LSQ_RECON
extern FLUENT_EXPORT cxboolean node_based_lsq;      /* set in sg_*.c */
extern FLUENT_EXPORT cxboolean node_based_lsq_grad; /* set in sg_recon.c */
extern FLUENT_EXPORT cxboolean node_based_lsq_all;  /* set in sg_recon.c */
extern FLUENT_EXPORT cxboolean node_grad_diff;      /* set in sg_recon.c */
extern FLUENT_EXPORT cxboolean node_grad_d2udx2;
extern FLUENT_EXPORT cxboolean node_phi_realloc_p;
extern FLUENT_EXPORT cxboolean node_vel_realloc_p;
extern FLUENT_EXPORT cxboolean old_nb_NCI;
#endif

extern FLUENT_EXPORT int       cb_lsq_correction;   /* set in rp_recon.c & sg_recon*/
/* 0 zero boundary grad 1st-o approx
1 dphi/dn = 0 (defualt)
2 phi at bdry implicity accounted for
*/
extern FLUENT_EXPORT cxboolean cell_based_lsq;      /* set in rp_recon.c & sg_recon */
extern FLUENT_EXPORT cxboolean cell_based_lsq_init; /* set in rp_recon.c & sg_recon */
extern FLUENT_EXPORT cxboolean cell_lsf_init; /* set in rp_recon.c & sg_recon */
extern FLUENT_EXPORT cxboolean cell_lsf_gg_init; /* set in rp_recon.c & sg_recon */
extern FLUENT_EXPORT cxboolean flux_init_done;      /* set in sg_init.c & flow.c */
extern FLUENT_EXPORT cxboolean cell_lsf;      /* set in sg_deriv.c & sg_recon */
extern FLUENT_EXPORT cxboolean cell_lsf_eco;      /* set in sg_deriv.c & sg_recon */
extern FLUENT_EXPORT cxboolean skip_gg_lsq;      /* set in sg_deriv.c & sg_recon */
extern FLUENT_EXPORT cxboolean extended_lsq_init; /* set in rp_recon.c & sg_recon */
extern FLUENT_EXPORT cxboolean nci_sided_area; /* set in sg_deriv.c, sg_recon, rp_recon, &rp_visc  */
extern FLUENT_EXPORT cxboolean nci_wt; /* set in sg_deriv.c, sg_recon, rp_recon, &rp_visc  */
extern FLUENT_EXPORT NCI_WS *nci_ws ;

enum filter_option
{
  FILTER_OFF = 0,
  FILTER_FIRST_ORD_BLEND = 1,
  FILTER_SECOND_ORD_BLEND = 2
};
typedef enum filter_option Filter_Option;

extern FLUENT_EXPORT cxboolean boiling_partition;


#define SET_DISCRETIZATION_SCHEME(var)\
  discr_scheme = var;\
  second_order = ((SECOND_ORDER_UPWIND == discr_scheme) ||\
     (CENTRAL_DIFFERENCING == discr_scheme) ||\
                 (HRIC == discr_scheme) ||\
                 (CICSAM == discr_scheme ) ||\
                 (COMPRESSIVE == discr_scheme ) ||\
                 (BGM == discr_scheme)||\
     (THIRD_ORDER_MUSCL == discr_scheme) ||\
         (LOW_DIFFUSION_FLUX == discr_scheme) ||\
     (HR_BLEND == discr_scheme) ||\
     (QUICK == discr_scheme)||\
         (LOW_DIFFUSION_FLUX == discr_scheme));\
  if(second_order)\
   {\
    if(flexible_numerics_engaged_p)\
     {\
      switch(flexible_numerics_advection_scheme)\
       {\
        case 0:\
           {\
            second_order = FIRST_ORDER_UPWIND;\
           }\
          break;\
        default:\
          break;\
       }\
     }\
   }


#define SET_DISCRETIZATION_OPTIONS(var)\
{\
  SET_DISCRETIZATION_SCHEME(var);\
  power_law = (POWER_LAW == discr_scheme);\
  bcd_skew_mode = (bcd_skew_scheme) RP_Get_Integer("bcd-skew-correction-mode"); \
  bcd_dbns_skew_mode = (bcd_skew_scheme) RP_Get_Integer("bcd-dbns-skew-correction-mode"); \
  bcd_tanh_blending = RP_Get_Boolean("bcd-tanh-blending?");\
  bcd_jasak_blending = RP_Get_Boolean("bcd-jasak-blending?");\
  bcd_const_blending = RP_Get_Boolean("bcd-constant-blending-t?");\
  bcd_dbns_const_blending = RP_Get_Boolean("bcd-dbns-constant-blending?");  \
  bcd_const_blend_factor = rp_seg? RP_Get_Real("bcd-constant-blending-factor-t"):RP_Get_Real("bcd-dbns-constant-blending-factor-t") ; \
  bcd_jasak = RP_Get_Boolean("bcd-jasak-scheme?");\
  bcd_bound_field = RP_Get_Boolean("bcd-bound-field?");\
  bcd_alfa = RP_Get_Real("bcd-alfa");\
  bcd_c = RP_Get_Real("bcd-c");\
  bcd_freeze_iter = RP_Get_Integer("bcd-freeze-iter");\
}

#define CONV_DIFF_COEFFS(f,t,C,D)               \
  {                                             \
    if (power_law && (D>0))                     \
      {                                         \
        real d = 1.0 - 0.1*ABS(C)/D;            \
        d = (d<0.) ? 0. : d*d*d*d*d*D;          \
        F_COEFF_01(f,t) = F_COEFF_10(f,t) = d;  \
      }                                         \
    else                                        \
      {                                         \
        F_COEFF_01(f,t) = F_COEFF_10(f,t) = D;  \
      }                                         \
    if ((C) > 0)                                \
      F_COEFF_10(f,t) += (C);                   \
    else                                        \
      F_COEFF_01(f,t) -= (C);                   \
  }

#define CONV_DIFF_COEFFS_NO_POWER_LAW(f,t,C,D)  \
  {                                             \
    F_COEFF_01(f,t) = F_COEFF_10(f,t) = D;      \
    if ((C) > 0)                                \
      F_COEFF_10(f,t) += (C);                   \
    else                                        \
      F_COEFF_01(f,t) -= (C);                   \
  }

#define F_CONV_DIFF_COEFFS(coeff_01,coeff_10,C,D)       \
  {                                                     \
    if (power_law && (D>0))                             \
      {                                                 \
        real d = 1-.1*ABS(C)/D;                         \
        d = (d<0) ? 0 : d*d*d*d*d*D;                    \
        coeff_01 = coeff_10 = d;                        \
      }                                                 \
    else                                                \
      {                                                 \
        coeff_01 = coeff_10 = D;                        \
      }                                                 \
    if ((C) > 0)                                        \
      coeff_10 += (C);                                  \
    else                                                \
      coeff_01 -= (C);                                  \
  }

#define F_CONV_DIFF_COEFFS_NO_POWER_LAW(coeff_01,coeff_10,C,D) \
  {                                                     \
    coeff_01 = coeff_10 = D;                            \
    if ((C) > 0)                                        \
      coeff_10 += (C);                                  \
    else                                                \
      coeff_01 -= (C);                                  \
  }

#define CONVECTIVE_COEFFS(coeff_01,coeff_10,C)  \
  {                                             \
    if ((C) >= 0.)                              \
      (coeff_01) = 0.,(coeff_10) = (C);         \
    else                                        \
      (coeff_01) = -(C),(coeff_10) = 0.;        \
  }

/* Macro for linearizing negative source terms for the
 * equations for positive quantities (k, epsilon, nut,
 * normal Reynolds stresses). */
#define C_NEGATIVE_SOURCE_LINEARIZE(c,phi,phi_ap,phi_s)\
{\
  real const var = phi[c];\
  real const source = phi_s[c];\
  if ((var > 0.) && (source < 0.))\
    {\
      phi_s[c] = 0.;\
      phi_ap[c] += source/var;\
    }\
}
#define C_NEGATIVE_SOURCE_LINEARIZE_RST(c,phi,phi_ap,phi_s,i)\
{\
  real const var = phi[c];\
  real const source = (phi_s[c])[i];\
  if ((var > 0.) && (source < 0.))\
    {\
      (phi_s[c])[i] = 0.;\
      phi_ap[c] += source/var;\
    }\
}

#define C_B_PH(c,t) FAST_C_STORAGE_R(c,t,SV_BETA_PH)
#define C_B_NH(c,t) FAST_C_STORAGE_R(c,t,SV_BETA_NH)

#define C_SO_TIME_BETA_TVD(c,t,beta_ph,beta_nh)\
{\
  beta_ph = C_B_PH(c,t);\
  beta_nh = C_B_NH(c,t);\
  if(tvd_time_bounded_second_order)\
   {\
     real b_factor = C_B_FAC(c,t);\
     beta_ph *= b_factor;\
     beta_nh *= b_factor;\
   }\
}

#define C_SO_TIME_BETA(c,t,beta_ph,beta_nh)\
{\
  beta_ph = C_B_PH(c,t);\
  beta_nh = C_B_NH(c,t);\
}

#if RP_POLYHEDRA
#define C_NODE_WTS(c,t,type)(C_STORAGE(c,t,SV_CR_NODE_##type,real **))
#define F_NODE_WTS(f,t,type)(F_STORAGE(f,t,SV_CR_NODE_##type,real **))
#define C_NODE_WT(c,t,i)(C_NODE_WTS(c,t,WT)[i])
#define F_NODE_WT(f,t,i)(F_NODE_WTS(f,t,WT)[i])
#define C_NODE_WT_GX(c,t,i)(C_NODE_WTS(c,t,WT_GX)[i])
#define F_NODE_WT_GX(f,t,i)(F_NODE_WTS(f,t,WT_GX)[i])
#define C_NODE_WT_GY(c,t,i)(C_NODE_WTS(c,t,WT_GY)[i])
#define F_NODE_WT_GY(f,t,i)(F_NODE_WTS(f,t,WT_GY)[i])
# if RP_3D
#define C_NODE_WT_GZ(c,t,i)(C_NODE_WTS(c,t,WT_GZ)[i])
#define F_NODE_WT_GZ(f,t,i)(F_NODE_WTS(f,t,WT_GZ)[i])
# endif /* RP_3D */
#else
#define C_NODE_WT(c,t,i)(C_STORAGE(c,t,SV_NODE_WT,real(*)[MAX_NODES_PER_CELL])[i])
#define F_NODE_WT(f,t,i)(F_STORAGE(f,t,SV_NODE_WT,real(*)[MAX_NODES_PER_FACE])[i])
#define C_NODE_WT_GX(c,t,i)(C_STORAGE(c,t,SV_NODE_WT_GX,real(*)[MAX_NODES_PER_CELL])[i])
#define C_NODE_WT_GY(c,t,i)(C_STORAGE(c,t,SV_NODE_WT_GY,real(*)[MAX_NODES_PER_CELL])[i])
#define F_NODE_WT_GX(f,t,i)(F_STORAGE(f,t,SV_NODE_WT_GX,real(*)[MAX_NODES_PER_FACE])[i])
#define F_NODE_WT_GY(f,t,i)(F_STORAGE(f,t,SV_NODE_WT_GY,real(*)[MAX_NODES_PER_FACE])[i])
# if RP_3D
#define C_NODE_WT_GZ(c,t,i)(C_STORAGE(c,t,SV_NODE_WT_GZ,real(*)[MAX_NODES_PER_CELL])[i])
#define F_NODE_WT_GZ(f,t,i)(F_STORAGE(f,t,SV_NODE_WT_GZ,real(*)[MAX_NODES_PER_FACE])[i])
# endif /* RP_3D */
#endif

#if RP_DOUBLE
#define SMALL_CONTINUITY_RESIDUAL 1.e-10
#else
#define SMALL_CONTINUITY_RESIDUAL 1.e-7
#endif

FLUENT_EXPORT void Solve_V (Domain *);
FLUENT_EXPORT void Solve_Wswirl (Domain *);
FLUENT_EXPORT void Solve_P (Domain *);
FLUENT_EXPORT void Solve_T (Domain *);
FLUENT_EXPORT real rothalpy_transfer(cell_t, Thread *, Thread *, real);
FLUENT_EXPORT void Solve_Species (Domain *);
FLUENT_EXPORT void Solve_SootSpecies(Domain *);
FLUENT_EXPORT void Solve_Fmean (Domain *, Svar);
FLUENT_EXPORT void Solve_Fvar (Domain *, Svar);
FLUENT_EXPORT void Solve_Fvar_Micro_Mix (Domain *, Svar);
FLUENT_EXPORT void Solve_TSS_Scalar (Domain *);
FLUENT_EXPORT void Solve_Dqmom_Iem(Domain *domain);
FLUENT_EXPORT void Update_Last_Specie (Domain *);
FLUENT_EXPORT void Update_Last_Dw(Domain *);
FLUENT_EXPORT void Update_Last_Dqmom_Species(Domain *);
FLUENT_EXPORT void Update_Boundary_Dqmom_Dw(Domain *domain);
FLUENT_EXPORT void Update_Boundary_Dqmom_Species(Domain *domain);
FLUENT_EXPORT void Update_Boundary_Dqmom_Enthalpy(Domain *domain);
FLUENT_EXPORT void Update_Dqmom_Old_Species(Thread *, Svar, Svar);
FLUENT_EXPORT void Update_Dqmom_Old_Energy(Thread *, cxboolean);

FLUENT_EXPORT void Load_CVD_Mass_Source(Domain *);
FLUENT_EXPORT void Load_Wall_Deposition_Rate(Domain *);
FLUENT_EXPORT void Load_Wall_Diff_BC_Mass(Domain *);
FLUENT_EXPORT void Pressure_Derivatives (Domain *);
FLUENT_EXPORT cxboolean Delete_Velocity_Reconstruction_P(void);
FLUENT_EXPORT void Recompute_Velocity_Derivatives (Domain *);
FLUENT_EXPORT void Velocity_Derivatives(Domain *);
FLUENT_EXPORT void Update_Velocity_Derivatives (Domain *);
FLUENT_EXPORT void Update_Omega_Derivatives (Domain *);
FLUENT_EXPORT void Omega_derivatives (Domain *domain, Svar sv_omega_g, Svar sv_w, Svar sv_w_rg);
FLUENT_EXPORT void Alloc_Velocity_Reconstruction(Domain *);
FLUENT_EXPORT void Free_Velocity_Reconstruction(Domain *);
FLUENT_EXPORT void Update_Derivatives_Around_Turbulence_Model(Domain *domain, cxboolean doit);

FLUENT_EXPORT void T_derivatives(Domain *);
FLUENT_EXPORT void Init_Face_Density(Domain *);
FLUENT_EXPORT void Init_Face_Flux (Domain *);
FLUENT_EXPORT void Init_Face_Pressure (Domain *);
FLUENT_EXPORT void Init_Enthalpy (Domain *, cxboolean force);
FLUENT_EXPORT void Init_Mass_Source (Domain *);
FLUENT_EXPORT void Mp_Expl_Init_Mass_Source (Domain *, Svar);
FLUENT_EXPORT void Add_Mass_or_Volume_Source (Domain *, Svar, Svar, Svar, real,
                                              cxboolean, Delta_Form);
FLUENT_EXPORT void Add_Heterogeneous_Rxn_Source
(Domain *domain, Svar sv, Svar sv_ap, Svar sv_s,
 int species_id, cxboolean volume_source,
 cxboolean subtract_mass_source, int dir);
FLUENT_EXPORT void Add_Mass_Transfer_and_Het_Rxn_Source
(Domain *, int, Svar, Svar, Svar, cxboolean, cxboolean, int, Delta_Form);
FLUENT_EXPORT void Add_Cavitation_Mass_Source (Domain *, cxboolean, cxboolean, int, Delta_Form);
FLUENT_EXPORT void add_iac_mass_sources(Domain *, Svar, Svar, Svar);

FLUENT_EXPORT void periodic_pressure_sources (Domain *);
FLUENT_EXPORT void Set_Reference_Pressure (Domain *);
FLUENT_EXPORT int Compute_Reference_Pressure (Domain *, double *);
FLUENT_EXPORT void Need_Reference_Pressure (Domain *, Treenode *[], int *, int);
FLUENT_EXPORT void Compute_Reference_Pressure_MRP(Domain *, Treenode *, double *);
FLUENT_EXPORT void Compute_Reference_Pressure_MRP_Overset(Domain *, int **, int *, double *);
FLUENT_EXPORT int Compute_Reference_Pressure (Domain *, double *);
FLUENT_EXPORT void fzone_belongs_to_tree(Treenode *, Thread *, cxboolean *);
FLUENT_EXPORT void Set_Reference_Pressure_Overset(Domain *, Treenode *[], int, int, cxboolean);
FLUENT_EXPORT int  Get_Num_Trees_Formed(int *ntrees);
FLUENT_EXPORT int  Get_Num_Trees_RefP(int *ntrees_refP);
FLUENT_EXPORT int **get_trees_info(int *[], int, int, cxboolean);
FLUENT_EXPORT int **get_trees_info_refp(int *[], int, int, cxboolean);

FLUENT_EXPORT void Accumulate_Statistics_And_Update_Time_Sampled(Domain *);

FLUENT_EXPORT void Update_Physical_Time(Domain *, int);
FLUENT_EXPORT void Update_Old_Sites(Thread *t, int iface);
FLUENT_EXPORT real MP_Compute_Courant_Based_Adaptive_DT(Domain *);
FLUENT_EXPORT void Update_Old_Energy(Domain *domain, Thread *t, cxboolean initp);

FLUENT_EXPORT void Update_Boundary_Velocity(Domain *domain, int i, cxboolean nrbc_force);
FLUENT_EXPORT void Update_Boundary_Rstress(Domain *);
FLUENT_EXPORT void Update_Boundary_Temperature(Domain *);
FLUENT_EXPORT void Update_Boundary_Enthalpy(Domain *);
FLUENT_EXPORT void Update_Boundary_Species(Domain *);
FLUENT_EXPORT void Update_Boundary_Fmean(Domain *, Svar nv);
FLUENT_EXPORT void Update_Boundary_Fvar(Domain *, Svar nv);

FLUENT_EXPORT void Set_Marangoni_Stresses(Domain *);

FLUENT_EXPORT void interior_accumulate_cell_interp_scalar(Thread *,
                                                          const real *w0, const real *w1,
                                                          real (*rg0)[ND_ND], real (*rg1)[ND_ND]);
FLUENT_EXPORT void interior_accumulate_cell_avg_scalar(Thread *,
                                                       const real *w0, const real *w1,
                                                       real (*rg0)[ND_ND], real (*rg1)[ND_ND]);
FLUENT_EXPORT void interior_accumulate_cell_avg_rothalpy(Thread *,
                                                         const real *w0, const real *w1,
                                                         real (*rg0)[ND_ND], real (*rg1)[ND_ND]);
FLUENT_EXPORT void interior_accumulate_cell_harmonic_avg_scalar(Thread *,
                                                                const real *w0, const real *w1,
                                                                real (*rg0)[ND_ND],
                                                                real (*rg1)[ND_ND]);
FLUENT_EXPORT void interior_accumulate_recon_scalar(Thread *,
                                                    const real *w0, const real *w1,
                                                    real (*rg0)[ND_ND],
                                                    real (*rg1)[ND_ND],
                                                    real (*g0)[ND_ND], real (*g1)[ND_ND]);
FLUENT_EXPORT void interior_accumulate_recon_rothalpy(Thread *PTR_RESTRICT thread,
                                                      const real *PTR_RESTRICT w0, const real *PTR_RESTRICT w1,
                                                      real (*rg0)[ND_ND], real (*rg1)[ND_ND],
                                                      real (*g0)[ND_ND], real (*g1)[ND_ND]);
FLUENT_EXPORT void interior_accumulate_cell_interp_rstress(Thread *thread,
                                                           Svar nv);
FLUENT_EXPORT void interior_accumulate_cell_avg_rstress(Thread *thread,
                                                        Svar nv);
FLUENT_EXPORT void interior_accumulate_node_avg_rstress(Thread *thread,
                                                        Svar nv);
FLUENT_EXPORT void interior_accumulate_recon_rstress(Thread *thread);

FLUENT_EXPORT void exterior_accumulate_face_scalar(Thread *,
                                                   const real *w, real (*rg0)[ND_ND]);

FLUENT_EXPORT void exterior_accumulate_face_scalar_lsf(Thread *thread,
                                                       const real *w, const real *w0,
                                                       real (*rg0)[ND_ND]);

FLUENT_EXPORT void exterior_accumulate_cell_avg_scalar(Thread *, const real *w0,
                                                       real (*rg0)[ND_ND]);

FLUENT_EXPORT void exterior_accumulate_cell_avg_scalar_lsf(Thread *, const real *w0,
                                                           real (*rg0)[ND_ND]);

FLUENT_EXPORT void exterior_accumulate_node_avg_scalar(Thread *thread,
                                                       const real *w, real (*rg0)[ND_ND]);

FLUENT_EXPORT void exterior_accumulate_recon_scalar(Thread *,
                                                    const real *w0,
                                                    real (*rg0)[ND_ND],
                                                    real (*g0)[ND_ND]);
FLUENT_EXPORT void exterior_accumulate_face_rstress(Thread *thread, Svar drst);

FLUENT_EXPORT void periodic_accumulate_face_scalar(Thread *,
                                                   const real *w,
                                                   real (*rg0)[ND_ND], real (*rg1)[ND_ND]);
FLUENT_EXPORT void periodic_accumulate_cell_avg_scalar(Thread *,
                                                       const real *w0, const real *w1,
                                                       real (*rg0)[ND_ND], real (*rg1)[ND_ND]);
FLUENT_EXPORT void periodic_accumulate_cell_avg_rothalpy(Thread *thread,
                                                         const real *w0, const real *w1,
                                                         real (* rg0)[ND_ND], real (* rg1)[ND_ND]);
FLUENT_EXPORT void periodic_accumulate_cell_harmonic_avg_scalar(Thread *,
                                                                const real *w0, const real *w1,
                                                                real (*rg0)[ND_ND],
                                                                real (*rg1)[ND_ND]);

FLUENT_EXPORT void periodic_accumulate_cell_avg_rstress(Thread *thread,
                                                        Svar nv);
FLUENT_EXPORT void periodic_accumulate_node_avg_rstress(Thread *thread,
                                                        Svar nv);

FLUENT_EXPORT void periodic_accumulate_jump_scalar(Thread *,
                                                   const real *w, const real *ws,
                                                   real (*rg0)[ND_ND], real (*rg1)[ND_ND]);

FLUENT_EXPORT void periodic_accumulate_jump_scalar_lsf(Thread *thread,
                                                       const real *w, const real *ws,
                                                       const real *w0, const real *w1,
                                                       real (* rg0)[ND_ND], real (* rg1)[ND_ND]);

FLUENT_EXPORT void periodic_accumulate_recon_scalar(Thread *,
                                                    const real *w0, const real *w1,
                                                    real (*rg0)[ND_ND],
                                                    real (*rg1)[ND_ND],
                                                    real (*g0)[ND_ND], real (*g1)[ND_ND],
                                                    real periodic_delta);
FLUENT_EXPORT void periodic_accumulate_recon_rothalpy(Thread *,
                                                      const real *w0, const real *w1,
                                                      real (*rg0)[ND_ND],
                                                      real (*rg1)[ND_ND],
                                                      real (*g0)[ND_ND], real (*g1)[ND_ND]);
FLUENT_EXPORT void periodic_accumulate_recon_rstress(Thread *thread);
FLUENT_EXPORT void interior_accumulate_cell_avg_vector(Thread *,
                                                       Svar NV_VEC(from),
                                                       Svar NV_VEC(to));
FLUENT_EXPORT void interior_accumulate_recon_vector(Thread *,
                                                    Svar NV_VEC(from),
                                                    Svar NV_VEC(rg),
                                                    Svar NV_VEC(to));
FLUENT_EXPORT void exterior_accumulate_cell_avg_vector(Thread *, Svar from, Svar to);

FLUENT_EXPORT void exterior_accumulate_face_vector( Thread *,
                                                    Svar NV_VEC(from),
                                                    Svar NV_VEC(to));

FLUENT_EXPORT void exterior_accumulate_face_vector_lsf( Thread *,
                                                        Svar NV_VEC(from),
                                                        Svar NV_VEC(to));

FLUENT_EXPORT void symmetry_accumulate_cell_avg_vector( Thread *,
                                                        Svar NV_VEC(from),
                                                        Svar NV_VEC(to));

FLUENT_EXPORT void symmetry_accumulate_cell_avg_vector_lsf( Thread *,
                                                            Svar NV_VEC(from),
                                                            Svar NV_VEC(to));

FLUENT_EXPORT void symmetry_accumulate_recon_vector( Thread *,
                                                     Svar NV_VEC(from),
                                                     Svar NV_VEC(rg),
                                                     Svar NV_VEC(to));
FLUENT_EXPORT void periodic_accumulate_cell_avg_vector( Thread *,
                                                        Svar NV_VEC(from),
                                                        Svar NV_VEC(to));
FLUENT_EXPORT void periodic_accumulate_recon_vector( Thread *,
                                                     Svar NV_VEC(from),
                                                     Svar NV_VEC(rg),
                                                     Svar NV_VEC(to));
FLUENT_EXPORT void interior_accumulate_jump_scalar(Thread *,
                                                   const real *w0, const real *w1,
                                                   real (*rg0)[ND_ND], real (*rg1)[ND_ND]);

FLUENT_EXPORT void interior_accumulate_jump_scalar_lsf(Thread *,
                                                       const real *w0, const real *w1,
                                                       real (*rg0)[ND_ND], real (*rg1)[ND_ND]);

FLUENT_EXPORT void zero_cell_scalar(Thread *, real *v);
FLUENT_EXPORT void zero_face_scalar(Thread *, real *v);
FLUENT_EXPORT void zero_cell_vector(Thread *, real (*v)[ND_ND]);
FLUENT_EXPORT void zero_face_vector(Thread *, real (*v)[ND_ND]);
FLUENT_EXPORT void zero_cell_3d_vector(Thread *, real (*v)[ND_3 ]);
FLUENT_EXPORT void zero_face_3d_vector(Thread *, real (*v)[ND_3 ]);
FLUENT_EXPORT void zero_cell_matrix(Thread *, real (*v)[ND_ND][ND_ND]);
FLUENT_EXPORT void zero_face_matrix(Thread *, real (*v)[ND_ND][ND_ND]);
FLUENT_EXPORT void init_cell_vector(Thread *, Svar s);
FLUENT_EXPORT void init_face_vector(Thread *, Svar s);
FLUENT_EXPORT void zero_cell_tensor(Thread *, ND_VEC(real (*vx)[ND_ND], real (*vy)[ND_ND],
                                                     real (*vz)[ND_ND]));
FLUENT_EXPORT void zero_cell_rst_tensor(Thread *thread, Svar sv);

FLUENT_EXPORT void norm_cell_vector(Thread *, real (*v)[ND_ND]);
FLUENT_EXPORT void norm_cell_tensor(Thread *, ND_VEC(real (*vx)[ND_ND], real (*vy)[ND_ND],
                                                     real (*vz)[ND_ND]));
FLUENT_EXPORT void norm_cell_rst_tensor(Thread *thread, Svar sv);

FLUENT_EXPORT void Node_Based_Min_Max_Recon(Domain *domain, Svar sw, Svar sw_min, Svar sw_max, Svar sw_phi, int ns);

FLUENT_EXPORT void Vector_Derivatives(Domain *,
                                      ND_VEC(Svar wx, Svar wy, Svar wz),
                                      ND_VEC(Svar dwx, Svar dwy, Svar dwz),
                                      ND_VEC(Svar rgwx, Svar rgwy, Svar rgwz),
                                      void (*accumulation_func)(Thread *t,
                                                                ND_VEC(Svar wx, Svar wy, Svar wz),
                                                                ND_VEC(Svar dwx, Svar dwy, Svar dwz),
                                                                ND_VEC(Svar rgwx, Svar rgwy, Svar rgwz)));
FLUENT_EXPORT void Scalar_Derivatives(Domain *, Svar w, int ns, Svar dw, Svar rgw,
                                      void (*accumulation_func)(Thread *t, Svar w, int ns, Svar dw, Svar rgw));
FLUENT_EXPORT void Vector_Reconstruction(Domain *,
                                         ND_VEC(Svar wx, Svar wy, Svar wz),
                                         ND_VEC(Svar rgwx, Svar rgwy, Svar rgwz),
                                         void (*accumulation_func)(Thread *t,
                                                                   ND_VEC(Svar wx, Svar wy, Svar wz),
                                                                   ND_VEC(Svar rgwx, Svar rgwy, Svar rgwz)));
FLUENT_EXPORT void Scalar_Reconstruction(Domain *, Svar w, int ns, Svar rgw,
                                         void (*accumulation_func)
                                         (Thread *t, Svar w, int ns, Svar rgw));
FLUENT_EXPORT void Scalar_Hessians(Domain *PTR_RESTRICT domain,
                                   Svar sv_val, Svar sv_hess, Svar rgw);
FLUENT_EXPORT void smoothen_scalar_deriv(Domain *PTR_RESTRICT domain, Svar dw, Svar sdw);
/* FLUENT_EXPORT void Store_Scalar_Gradient(Domain *domain, Svar rgw); */
/* FLUENT_EXPORT void Store_Vector_Gradient(Domain *domain,  */
/*           ND_VEC(Svar rgwx, Svar rgwy, Svar rgwz)); */

FLUENT_EXPORT void Relax_Scalar_Gradient(Domain *domain,
                                         Svar rgw);
FLUENT_EXPORT void Relax_Vector_Gradient(Domain *domain,
                                         ND_VEC(Svar rgwx_aux, Svar rgwy_aux, Svar rgwz_aux));

FLUENT_EXPORT cxboolean Skip_LSQ(Svar w);

/*Limiter Filter Related*/
FLUENT_EXPORT Filter_Option Apply_Filter(Svar w);
FLUENT_EXPORT void  Update_Filter_Flags(Pointer vars);
FLUENT_EXPORT void Filter_Flags(void);

FLUENT_EXPORT void Turb_Scalar_Rgrad_Accumulate(Thread *t, Svar sw, int ns, Svar rgw);
FLUENT_EXPORT void Disco_Rgrad_Accumulate(Thread *t, Svar sv_doic, int ns, Svar sv_do_rg);

#if LSQ_RECON
FLUENT_EXPORT void Scalar_Gradient_Reconstruction(Domain *, Svar w, int ns, Svar dw,
                                                  Svar rgw, cxboolean limiter,
                                                  void (*accumulation_func)
                                                  (Thread *t, Svar w, int ns, Svar rgw));
FLUENT_EXPORT void Vector_Gradient_Reconstruction(Domain *,
                                                  ND_VEC(Svar wx, Svar wy, Svar wz),
                                                  ND_VEC(Svar dwx, Svar dwy, Svar dwz),
                                                  ND_VEC(Svar rgwx, Svar rgwy, Svar rgwz),
                                                  void (*accumulation_func)(Thread *t,
                                                      ND_VEC(Svar wx, Svar wy, Svar wz),
                                                      ND_VEC(Svar rgwx, Svar rgwy, Svar rgwz)));
FLUENT_EXPORT void Node_Scalar_Reconstruct(Domain *, Svar sw, int ns, cxboolean renderp_only, CELL_FUNCTION *cf);
FLUENT_EXPORT void Fast_Solid_Node_Scalar_Reconstruction(Domain *, Svar sw, int ns);
FLUENT_EXPORT void Node_Scalar_Boundary_Reconstruct(Domain *, Svar sw);
FLUENT_EXPORT void Node_Vector_Reconstruct(Domain *, ND_VEC(Svar wx, Svar wy, Svar wz));
FLUENT_EXPORT void Node_Stress_Reconstruct(Domain *, Svar nv);
FLUENT_EXPORT void interior_accumulate_node_avg_scalar(Thread *t,
                                                       const real *w0, const real *w1,
                                                       real (*rg0)[ND_ND], real (*rg1)[ND_ND]);
FLUENT_EXPORT void periodic_accumulate_node_avg_scalar(Thread *t,
                                                       const real *w0, const real *w1,
                                                       real (*rg0)[ND_ND], real (*rg1)[ND_ND]);
FLUENT_EXPORT void interior_accumulate_node_avg_vector(Thread *t, Svar NV_VEC(from),
                                                       Svar NV_VEC(to));

FLUENT_EXPORT void sliding_boundary_accumulate_node_avg_scalar(Thread *t,
                                                               const real *w0, real (* rg0)[ND_ND]);

FLUENT_EXPORT void sliding_boundary_accumulate_node_avg_vector(Thread *t,
                                                               Svar NV_VEC(from),
                                                               Svar NV_VEC(to));

FLUENT_EXPORT void periodic_accumulate_node_avg_vector(Thread *t, Svar NV_VEC(to));
FLUENT_EXPORT void copy_cell_tensor(Thread *t, ND_VEC(real (*vx)[ND_ND], real (*vy)[ND_ND],
                                                      real (*vz)[ND_ND]),
                                    ND_VEC(real (*vrx)[ND_ND], real (*vry)[ND_ND],
                                           real (*vrz)[ND_ND]));
FLUENT_EXPORT void copy_cell_rst_tensor(Thread *t, Svar sv, Svar svr);
FLUENT_EXPORT void copy_cell_vector(Thread *t, real (*from)[ND_ND], real (*to)[ND_ND]);
#endif

FLUENT_EXPORT void Compute_Grad_Node_Weights(Node *v, real *lambda, real *dx, real scale, cxboolean lsq_p);
FLUENT_EXPORT void Accumulate_Grad_Node_Weights(Node *v, real *dx, cxboolean weight_p, real scale, cxboolean lsq_p);
FLUENT_EXPORT real Get_Grad_Node_Scale(cell_t c, Thread *tc, real *xc);

FLUENT_EXPORT void LSQ_Scalar_Reconstruction(Domain *domain, Svar w, int ns, Svar rgw);

FLUENT_EXPORT void LSQ_Vector_Reconstruction(Domain *domain,
                                             ND_VEC(Svar wx,   Svar wy,   Svar wz),
                                             ND_VEC(Svar rgwx, Svar rgwy, Svar rgwz));


FLUENT_EXPORT void LSQ_Scalar_Extended_Reconstruction(Domain *domain, Svar sw, Svar rgw);
FLUENT_EXPORT void LSQ_Vector_Extended_Reconstruction(Domain *domain,
                                                      ND_VEC(Svar wx,   Svar wy,   Svar wz),
                                                      ND_VEC(Svar rgwx, Svar rgwy, Svar rgwz));

FLUENT_EXPORT real get_wall_face_temp(face_t f, Thread *t) ;
FLUENT_EXPORT void Cell_K_Matrix(const cell_t c, const Thread *PTR_RESTRICT t, Material *PTR_RESTRICT m, real km[ND_ND][ND_ND], int k_method, int ktc_index, int ortho_ktc_index, real (*PTR_RESTRICT rm)[3]);
FLUENT_EXPORT real compute_wall_face_scalar(face_t f, Thread *tf, Svar sv, Svar rgv);
FLUENT_EXPORT real rothalpy_face_transfer(face_t f, Thread *tf, Thread *from, Thread *to, real h);
FLUENT_EXPORT real cell_to_face_dx(cell_t c, Thread *tc, face_t f, Thread *tf,  real *dxx);
/*End of functions declaration   */
FLUENT_EXPORT cxboolean MRF_15(Domain *domain) ;
FLUENT_EXPORT cxboolean Mrf_Relative_Velocity(cxboolean mrf15, Thread *t0, Thread *t1);

FLUENT_EXPORT cxboolean Mapped_Interface_Exist (Domain *domain);
FLUENT_EXPORT cxboolean Shifted_Mapped_Interface_Exist (Domain *domain);
FLUENT_EXPORT cxboolean Is_Shifted_Mapped_Interface(Thread *t);
FLUENT_EXPORT void Virt_Poly_Scalar_Mapped_Correct(Domain *PTR_RESTRICT domain, Svar sw, Svar swg, int ns);
FLUENT_EXPORT void Virt_Poly_Vector_Mapped_Correct(Domain *PTR_RESTRICT domain, ND_VEC(Svar wx, Svar wy, Svar wz),
                                                   ND_VEC(Svar dwx, Svar dwy, Svar dwz));
FLUENT_EXPORT void Virt_Poly_Vector_Mapped_Leftover_Correct(Domain *PTR_RESTRICT domain, ND_VEC(Svar wx, Svar wy, Svar wz),
                                                            ND_VEC(Svar dwx, Svar dwy, Svar dwz));

FLUENT_EXPORT void Virt_Poly_Scalar_Mapped_Leftover_Correct(Domain *PTR_RESTRICT domain, Svar sw, Svar swg, int ns);

FLUENT_EXPORT void Recompute_Cell_Gradient_For_Boundary_Cells_LSQ(Domain *domain, Svar sw, int ns, Svar rgw);

FLUENT_EXPORT void Recompute_Cell_Vect_Gradients_For_Boundary_Cells_LSQ(Domain *domain,
    ND_VEC(Svar wx, Svar wy, Svar wz),
    ND_VEC(Svar rgwx, Svar rgwy, Svar rgwz)) ;

/* FLUENT_EXPORT void Recompute_Solid_Cells_Scalar_Gradient_Nbg_LSF(Domain* domain, Svar sw, int ns, Svar rgw); */

FLUENT_EXPORT void Recompute_Cell_Hessian_LSQ(Domain *domain, Svar sv_val, Svar sv_hess, Svar rgw,
                                              cxboolean include_boundary, cxboolean include_all_grad, cxboolean use_grad_adaptive);

FLUENT_EXPORT void Recompute_Cell_Gradient_Via_Shape_Function(Domain *domain, Svar sw, int ns, Svar rgw, Svar gw, int gmode);
FLUENT_EXPORT void Recompute_Cell_Pressure_Gradient_At_NCI_Via_Shape_Function(Domain *domain, Svar sw, int ns, Svar rgw, Svar gw);

FLUENT_EXPORT void Recompute_Cell_Vect_Gradients_Via_Shape_Function(Domain *domain,
                                                                    ND_VEC(Svar wx, Svar wy, Svar wz),
                                                                    ND_VEC(Svar rgwx, Svar rgwy, Svar rgwz),
                                                                    ND_VEC(Svar gx, Svar gy, Svar gz),
                                                                    int gmode) ;

FLUENT_EXPORT void Construct_Node_Scalar(Domain *domain, Svar w, int ns);
FLUENT_EXPORT void Construct_Node_Vector(Domain *domain, ND_VEC(Svar wx, Svar wy, Svar wz) );

FLUENT_EXPORT void Normalize_All_Svar_Grad_DBNS(Domain *domain, int mode);
FLUENT_EXPORT void Fill_Overset_All_Svar_Grad_DBNS(Domain *domain, int mode);
FLUENT_EXPORT void Compute_LSF_Weights_And_GG_Weights_Optimized(Domain *domain, cxboolean recom_wt, cxboolean recom_ggwt);
FLUENT_EXPORT void Compute_LSF_Weights(Domain *domain);
FLUENT_EXPORT void Compute_LSF_GGWeights(Domain *domain);
FLUENT_EXPORT void Smooth_Scalar_Extrema(Domain *domain, Svar rgw);
FLUENT_EXPORT void correct_face_thread(Thread **st, Thread *ft, Domain *d);

FLUENT_EXPORT int  Mark_All_Boundary_Nodes(Domain *domain);
FLUENT_EXPORT int  Mark_All_Wall_Nodes(Domain *domain);
FLUENT_EXPORT int  Mark_All_Wall_Cells(Domain *domain);
FLUENT_EXPORT int  Clear_All_Cell_Recon_Marks(Domain *domain);
FLUENT_EXPORT int  UnMark_All_Nodes(Domain *domain);
FLUENT_EXPORT int  Mark_All_Nodes(Domain *domain);
FLUENT_EXPORT cxboolean Mark_All_Boundary_Cells(Domain *domain);
FLUENT_EXPORT cxboolean Mark_Sliding_Boundary_Cells(Domain *domain);
FLUENT_EXPORT void Mark_All_Mixed_Children_Cells (Domain *domain);
FLUENT_EXPORT void Mark_All_Mapped_Leftover_Cells (Domain *domain);
FLUENT_EXPORT void Mark_All_Mapped_Interface_Cells (Domain *domain);
FLUENT_EXPORT void Mark_All_Shifted_Mapped_Interface_Cells (Domain *domain);
FLUENT_EXPORT void Initialize_Gradient_And_Reconstruction_Flags(void);
FLUENT_EXPORT void Assign_Area_Weighted_Property_To_Children(Domain *domain, Svar w);
FLUENT_EXPORT int ReInit_Cell_Vect_Gradients_For_Boundary_Cells(Domain *domain,
                                                                ND_VEC(Svar rgwx, Svar rgwy, Svar rgwz));
FLUENT_EXPORT int ReInitialize_Cell_Gradient_For_Boundary_Cells(Domain *domain, Svar rgw);

FLUENT_EXPORT void shell_junction_temperature_coeffs(Thread *);
FLUENT_EXPORT void shell_interior_temperature_coeffs(Thread *);
FLUENT_EXPORT void set_wall_temperature(Thread *, real dw, cxboolean do_limit_p,
                                        real Tmin, real Tmax, int *nftmin, int *nftmax);
FLUENT_EXPORT void wall_temperature_coeffs(Thread *, real dw);
FLUENT_EXPORT void wall_heat_flux_coeffs(Thread *, real dw);
FLUENT_EXPORT void Inquire_Secondary_Gradient_Limiting_Coupled_Wall(Domain *domain);
FLUENT_EXPORT void wall_mixed_bc_coeffs(Thread *, real dw);
FLUENT_EXPORT void wall_coupled_coeffs(Thread *, real dw);
FLUENT_EXPORT void boundary_pressure_work(Thread *);
FLUENT_EXPORT void fluid_interior_uds_coeffs(Thread *, int ns);
FLUENT_EXPORT void fluid_interior_uds_coeffs_side(Thread *, int ns, cxboolean side0);
FLUENT_EXPORT void fluid_periodic_uds_coeffs(Thread *, int ns);
FLUENT_EXPORT void solid_interior_uds_coeffs(Thread *, int ns);
FLUENT_EXPORT void solid_interior_uds_coeffs_side(Thread *, int ns, cxboolean side0);
FLUENT_EXPORT void solid_periodic_uds_coeffs(Thread *, int ns);
FLUENT_EXPORT void boundary_uds_coeffs(Thread *, int ns, int uds_bc_type[],
                                       Profile uds[], cxboolean compute_coeffs,
                                       cxboolean inlet_diff);
FLUENT_EXPORT void wall_coupled_uds_coeffs(Thread *thread, int ns, cxboolean compute_coeffs);
FLUENT_EXPORT real face_uds_flux(face_t f, Thread *t, int ns);
FLUENT_EXPORT cxboolean uds_solved_in_solid(int n, cxboolean *any_uds_solved_in_solid);
FLUENT_EXPORT cxboolean uds_solved_in_zone(Thread *t, int n);
FLUENT_EXPORT void UDS_Rgrad_Accumulate(Thread *, Svar, int, Svar);
FLUENT_EXPORT void UDS_Deriv_Accumulate(Thread *, Svar, int, Svar, Svar);

FLUENT_EXPORT void T_derivatives(Domain *);
FLUENT_EXPORT void get_linearized_qiw(Thread *, face_t f, cell_t c0, Thread *t0,
                                      real A[], real es0[], real *ds0, real Tiw,
                                      real Cid[], real Cir[], real Ci[], real Cit[],
                                      cxboolean update_flux, cxboolean eles_in_t0, cxboolean in_film);
FLUENT_EXPORT void get_linearized_qiw_mp(Thread *PTR_RESTRICT thread, face_t f,
                                         cell_t c0, Thread *PTR_RESTRICT mixture_t0,
                                         real A[], real es0[], real *ds0,
                                         real Cid[MAX_PHASES][3], real Cir[MAX_PHASES][3], real Ci[MAX_PHASES][3],
                                         cxboolean boiling_flux_partition,
                                         cxboolean update_flux, cxboolean eles_in_t0);

FLUENT_EXPORT void Inertial_Work(Domain *, Svar);
FLUENT_EXPORT void Thermally_Couple_Mapped_Thread(Thread *, cxboolean);
FLUENT_EXPORT void Compute_Mapped_Interface_Lineraized_Coefficients(Domain *);
FLUENT_EXPORT void Update_Mapped_Interface_Temperature(Domain *);

extern FLUENT_EXPORT real periodic_beta; /* for periodics with mass flow */
extern FLUENT_EXPORT real periodic_beta_prime;

extern FLUENT_EXPORT real periodic_alpha;
extern FLUENT_EXPORT cxboolean const_temperature_periodic;
extern FLUENT_EXPORT cxboolean heat_flux_periodic;
extern FLUENT_EXPORT cxboolean explicit_zero_divergence;
extern FLUENT_EXPORT real initial_continuity_residual;
extern FLUENT_EXPORT real max_face_size_sqr(face_t, Thread *);
extern FLUENT_EXPORT void min_max_face_size_sqr(face_t, Thread *, real *hmin, real *hmax);

FLUENT_EXPORT void unsteady_sources(Domain *, Svar sv_v, int i, Svar sv_ap, Svar sv_source, cxboolean dpm_block);
FLUENT_EXPORT void Unsteady_Sources(Domain *, Svar sv_v, int i, Svar sv_ap, Svar sv_source);
FLUENT_EXPORT void pseudo_transient_sources(Domain *domain, Svar sv_v, int i, Svar sv_ap, Svar sv_source, real pseudo_time_step, cxboolean dpm_block);
FLUENT_EXPORT void Calculate_Blend_Factor(Domain *domain, Svar sv_b_fac);
FLUENT_EXPORT void MP_Calculate_Blend_Factor(Domain *domain, Svar sv_b_fac);
FLUENT_EXPORT real Calc_Time_Bounded_Beta(real phi, real phi_m1, Time_Bounded_Var_Struct *bnd_var, real dt_r_alpha);
FLUENT_EXPORT void Calc_Time_Bounded_Variables_NH(Domain *domain, cxboolean rho_update, cxboolean vof_update);
FLUENT_EXPORT void Calc_Time_Bounded_Variables_PH(Domain *domain, cxboolean rho_update, cxboolean vof_update);
FLUENT_EXPORT void Calc_Time_Bounded_VOF_PH(Domain *subdomain);
FLUENT_EXPORT void Calc_SO_Time_Beta(Domain *domain, Svar sv_beta, cxboolean update_ph);
FLUENT_EXPORT void Print_SO_Time_Beta_PH(Domain *domain);
FLUENT_EXPORT void user_sources(Domain *, int eqn, Svar sv_v, Svar sv_ap, Svar sv_source, Delta_Form df);
FLUENT_EXPORT void md_convert_face_flux_to_vn(Domain *);
FLUENT_EXPORT void md_convert_vn_to_face_flux(Domain *);
FLUENT_EXPORT int interp_face_vars_from_sliding_boundaries(Domain *);
FLUENT_EXPORT void restrict_face_vars_to_sliding_boundaries(Domain *);
FLUENT_EXPORT void fixed_var_sources(Domain *, int eqn, Svar sv_v, Svar sv_ap, int amg_id);
FLUENT_EXPORT cxboolean var_stored_in_any_cell(Domain *domain, Var_Attribute *sv);

FLUENT_EXPORT cxboolean fluid_periodics_p(const Domain *);

FLUENT_EXPORT void User_Mass_Sources (Domain *);

FLUENT_EXPORT void Init_Face_Upwind_CV(Face_Upwind_CV *);

FLUENT_EXPORT void Set_CICSAM_dt(real dt);
FLUENT_EXPORT real second_order_correction(face_t f, Thread *t,
                                           cell_t c0, Thread *t0, cell_t c1, Thread *t1,
                                           real flux, Svar n,
                                           real NV_VEC(dr0), real NV_VEC(dr1), Svar nrg,
                                           int scheme, Second_Ord_Correc_Info *socInfo, Face_Upwind_CV *fcv);
FLUENT_EXPORT void vector_second_order_correction(face_t f, Thread *t,
                                                  cell_t c0, Thread *t0,
                                                  cell_t c1, Thread *t1,
                                                  real flux,
                                                  ND_VEC(Svar nU, Svar nV, Svar nW),
                                                  ND_VEC(real c0_u, real c0_v, real c0_w),
                                                  ND_VEC(real c1_u, real c1_v, real c1_w),
                                                  real NV_VEC(dr0), real NV_VEC(dr1),
                                                  ND_VEC(Svar nrgU, Svar nrgV, Svar nrgW),
                                                  ND_VEC(real NV_VEC(u_rg0), real NV_VEC(v_rg0), real NV_VEC(w_rg0)),
                                                  ND_VEC(real NV_VEC(u_rg1), real NV_VEC(v_rg1), real NV_VEC(w_rg1)),
                                                  real NV_VEC(dV), int scheme,
                                                  Face_Upwind_CV *fcv);

FLUENT_EXPORT void find_frame_omega(Thread *t0, real Omega[3][3]);
#define OTHER_FRAME_GRAD_V_TENSOR(Omega0,DV0,Omega1,DV1)  \
  {/* int nd; */              \
    for(nd=0; nd<ND_ND; nd++)         \
      {               \
  NV_V(DV1[nd],=,DV0[nd]);        \
  NV_VV(DV1[nd],+=,Omega1[nd],-,Omega0[nd]);}}

#define C_GRAD_V_TENSOR(c,t,nx,ny,nz,DV) \
ND_VEC(NV_V(DV[0], =, C_STORAGE_R_NV(c,t,nx)),\
       NV_V(DV[1], =, C_STORAGE_R_NV(c,t,ny)),\
       NV_V(DV[2], =, C_STORAGE_R_NV(c,t,nz)))

FLUENT_EXPORT void mult_frame_vector_second_order_correction(face_t f, Thread *t,
                                                             cell_t c0, Thread *t0,
                                                             cell_t c1, Thread *t1,
                                                             real NV_VEC(f_cent), real NV_VEC(c0_cent),
                                                             real flux,
                                                             ND_VEC(Svar nU, Svar nV, Svar nW),
                                                             ND_VEC(real c0_u, real c0_v, real c0_w),
                                                             ND_VEC(real c1_u, real c1_v, real c1_w),
                                                             real NV_VEC(dr0), real NV_VEC(dr1),
                                                             ND_VEC(Svar nrgU, Svar nrgV, Svar nrgW),
                                                             ND_VEC(real NV_VEC(u_rg0), real NV_VEC(v_rg0), real NV_VEC(w_rg0)),
                                                             ND_VEC(real NV_VEC(u_rg1), real NV_VEC(v_rg1), real NV_VEC(w_rg1)),
                                                             real NV_VEC(dV0), real NV_VEC(dV1), int scheme,
                                                             Face_Upwind_CV *fcv);

FLUENT_EXPORT void vector_second_order_quick_correction(face_t f, Thread *PTR_RESTRICT t,
                                                        real flux,
                                                        real NV_VEC(dr0), real NV_VEC(dr1),
                                                        ND_VEC(real NV_VEC(u_rg0), real NV_VEC(v_rg0), real NV_VEC(w_rg0)),
                                                        ND_VEC(real NV_VEC(u_rg1), real NV_VEC(v_rg1), real NV_VEC(w_rg1)),
                                                        real NV_VEC(dV), int scheme,
                                                        Face_Upwind_CV *v);

FLUENT_EXPORT void rothalpy_second_order_correction(face_t f, Thread *PTR_RESTRICT t,
                                                    cell_t c0, Thread *PTR_RESTRICT t0, cell_t c1, Thread *PTR_RESTRICT t1,
                                                    real flux, Svar n, real c0_H, real c1_H,
                                                    real NV_VEC(dr0), real NV_VEC(dr1), Svar nrg,
                                                    real NV_VEC(H_rg0), real NV_VEC(H_rg1),
                                                    real hr_beta_fact0, real hr_beta_fact1,
                                                    int scheme, Face_Upwind_CV *PTR_RESTRICT v, real *dH0, real *dH1);

FLUENT_EXPORT void mult_frame_vel_trans(cell_t c0, Thread *t0, Thread *t1, real NV_VEC(Vtrans01));
FLUENT_EXPORT void mult_frame_point_vel_trans(real xc[ND_ND], Thread *t0, Thread *t1, real NV_VEC(Vtrans01));

FLUENT_EXPORT void mult_frame_face_vel_trans(face_t f, Thread *t, Thread *t0, Thread *t1, real NV_VEC(Vtrans01));

FLUENT_EXPORT cxboolean MRF15(Domain *domain);
extern FLUENT_EXPORT cxboolean mrf15_check;
extern FLUENT_EXPORT cxboolean mrf15_interior_flag;
FLUENT_EXPORT real dom_second_order_correction(face_t f, Thread *t,
                                               cell_t c0, Thread *t0, cell_t c1, Thread *t1,
                                               real flux, Svar n, int ns,
                                               real NV_VEC(dr0), real NV_VEC(dr1),
                                               real do_i0, real do_i1,
                                               real NV_VEC(do_rg0), real NV_VEC(do_rg1),
                                               real hr_beta_fact0, real hr_beta_fact1,
                                               int scheme, Face_Upwind_CV *fcv);
FLUENT_EXPORT real rstress_second_order_correction(face_t f, Thread *t,
                                                   cell_t c0, Thread *t0,
                                                   cell_t c1, Thread *t1,
                                                   real flux, int nr,
                                                   real NV_VEC(dr0), real NV_VEC(dr1),
                                                   int scheme, Face_Upwind_CV *fcv);

/*Note: this is used by explicit VOF */
FLUENT_EXPORT real boundary_second_order_correction(real flux, real c_volume,
                                                    real c_vof,
                                                    real NV_VEC(d), real NV_VEC(vof_rg),
                                                    real hr_beta_fact,
                                                    int scheme);
/*Note: this is used by  discrete ordinate model */
FLUENT_EXPORT real dom_boundary_second_order_correction(real NV_VEC(d), real NV_VEC(do_rg),
                                                        real hr_beta_fact, int scheme);

FLUENT_EXPORT void Turb_Linearized_Shear_Stress(ND_VEC(real u0, real v0, real w0),
                                                real resistance,
#if RP_2D
                                                real xf[], real x0[],
#endif
                                                real A[], real At,
                                                real a[], real b[], real c[], real Vw[]);

FLUENT_EXPORT void Lam_Linearized_Shear_Stress(ND_VEC(real u_g0[], real v_g0[], real w_g0[]),
                                               real mu0, real divV, real bmu0,
#if RP_2D
                                               real omega_g0[],
#endif
                                               real xf[], real x0[], real A[], real At,
                                               real a[], real b[], real c[]);
FLUENT_EXPORT void Init_Liquid_Fraction(Domain *domain, cxboolean force);

FLUENT_EXPORT void Update_Liquid_Fraction(Domain *domain);

FLUENT_EXPORT void Unsteady_Melt_Coeffs(cell_t c, Thread *t, real liqf, real rho,
                                        real vol, real *ap, real *s,
                                        real physical_dt, real factor);

FLUENT_EXPORT void Melt_Resistance(Domain *domain, Svar sv_phi_ap,
                                   Svar sv_phi_s, Svar sv_phi,
                                   Svar sv_target,
                                   real target_value,
                                   Delta_Form df);

FLUENT_EXPORT real BGM_Correction(face_t f, Thread *t, cell_t c0, Thread *t0, cell_t c1, Thread *t1, real vflux, real NV_VEC(dr0), real NV_VEC(dr1));
FLUENT_EXPORT void Calc_High_Resolution_Beta_Factor(Domain *domain, Svar sw, int ns, Svar sw_rg, Svar sv_beta, real beta_max,
                                                    cxboolean local_min_max, real lower_bound, real upper_bound);
FLUENT_EXPORT int Gradient_Method(void);
FLUENT_EXPORT cxboolean Is_Periodic_Heat(const Domain *domain);
extern FLUENT_EXPORT cxboolean pseudo_transient;
extern FLUENT_EXPORT cxboolean pseudo_auto_time_step;
extern FLUENT_EXPORT Temporal_Param temporal_param;
extern FLUENT_EXPORT cxboolean dual_time_stepping;
extern FLUENT_EXPORT int dual_time_stepping_implicit_relax_type;
extern FLUENT_EXPORT DualTimeStepping_Param dual_ts_param;
extern FLUENT_EXPORT Equation_Param mom_eqn_param[ND_ND];  /* momentum eqution data structures structs */

extern FLUENT_EXPORT cxboolean is_turbo_p;
extern FLUENT_EXPORT cxboolean turbo_art_compress_p;

FLUENT_EXPORT cxboolean sandwich_symmetry_setup(Thread *tf, Thread *tc);

#define CF_COMPRESSIBLE 1
#if CF_COMPRESSIBLE
extern FLUENT_EXPORT real
acr_T0gamma(real T0, real R, real gamma),
            lambda_pi(real pi, real gamma),
            lambda_T0prvRgamma (real T0, real p, real rv, real R, real gamma),
            mach_lambda(real lambda, real gamma);
#endif

FLUENT_EXPORT void Allocate_Dynamic_Mesh_Bridge_Nodes (cxboolean);

FLUENT_EXPORT void Update_Node_Based_Meshing_Info(Domain *domain);
FLUENT_EXPORT void Set_Node_Based_Mesh_Info_Update_P(void);
extern FLUENT_EXPORT cxboolean node_based_mesh_info_update;

FLUENT_EXPORT void Init_Pout_Vars(Domain *);
FLUENT_EXPORT void Init_Pinlet_Vars(Domain *);
FLUENT_EXPORT void Init_Vinlet_Vars(Domain *);

FLUENT_EXPORT void Compute_Cell_Pgrad_Velocity_Correction(cell_t c, Thread *tc, real NV_VEC(pgrad_corr));

FLUENT_EXPORT void update_artificial_wall_flag(Thread *t);

FLUENT_EXPORT void Velocity_Filter(Domain *domain, cxboolean cell_filter, cxboolean print_verbosity);
FLUENT_EXPORT cxboolean Hybrid_Nita_Instability_Detector(Domain *d);

FLUENT_EXPORT void SG_Increment_Case_Id_Storage(void);

FLUENT_EXPORT void Compute_Local_Pseudo_Time_Step_PBNS ( Domain *domain, real cfl_fluid_, real cfl_solid_ );
FLUENT_EXPORT void ap_dual_dt_coeffs(Domain *d);
#if 0
FLUENT_EXPORT Svar sv_mu_effective;
#endif

#endif /* _FLUENT_SG_H */

