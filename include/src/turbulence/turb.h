/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_TURB_H
#define _FLUENT_TURB_H


/**
* \file
* \brief External API header file for common turblence methods.
*/


#include "cxbool.h"
#include "dll.h"
#include "flow.h"
#include "global.h"
#include "mem.h"


typedef enum
{
  TURB_NULL = -1,
  LAM = 0,  /* no turbulence model                      */
  /* zero equation models                                    */
  MIX = 1,  /* algebraic mixing length model for IcePak */
  LES_SMAG = 2,  /* large-eddy simulation, Smagorinsky SGS   */
  LES_RNG = 3,  /* large-eddy simulation, RNG SGS           */
  HVAC = 4,  /* algebraic model for AirPak               */
  LES_DSMAG = 5,  /* Dynamic Smagorinsky SGS                 */
  LES_WALE = 6,  /* large-eddy simulation, WALE SGS          */
  LES_WMLES = 7,  /* large-eddy simulation, Wall-Modelled    */
  LES_WMLES_SO = 8, /* large-eddy simulation, Wall-Modelled "S minus Omega" */
  /* one equation models                                     */
  KE1E = 10, /* Menter one-equation turbulence model     */
  SA = 11, /* Spalart-Allmarass 1-equation model       */
  LES_SGSKE = 12,  /* SGS kinetic energy model for LES       */
  LES_DSGSKE = 13,  /* Dynamic SGS kinetic energy model      */
  DES_SA = 14,  /* Detached eddy simulation, SA based    */
  /* two equation models                                     */
  DES_RKE = 15,  /* Detached eddy simulation, RKE based   */
  DES_SST = 16,  /* Detached eddy simulation, SST based   */
  SAS_SST = 17,  /* Scale adaptive simulation, SST based  */
  STD_KE = 21, /* standard k-epsilon                       */
  RNG_KE = 22, /* RNG k-epsilon                            */
  REAL_KE = 23, /* realizable k-epsilon                     */
  LOWRE_KE = 24, /* low-Reynolds number k-epsilon            */
  /* EASM  = 25, -- explicit algebraic stress model          */
  K_OMEGA = 26, /* std k-omega                              */
  SST = 27, /* SST version of k-omega                   */
  TRANS_K_OMEGA = 28, /* transition k-omega                 */
  EASM_KE = 29, /* easm k-epsilon                           */
  K_OMEGA_EASM = 30, /* easm k-omega                        */
  WJ_BSL_EARSM = 31, /* Wallin-Johansson-BSL-(komega)-EARSM */
  BSL = 32, /* BSL version of k-omega              */
  GEKO = 33, /* GEKO version of k-omega             */
  /* 2-4 equation eddy-viscosity models                      */
  USER = 41,
  V2F = 42, /* V2F model from Cascade Technology        */
  TRANS_SST = 43, /* transition SST                        */
  /* Reynolds stress models                                  */
  RSM_SKE = 61, /* RSM with standard epsilon equation      */
  RSM_RKE = 62, /* RSM with realizable epsilon equation    */
  RSM_K_OMEGA = 63, /* RSM with std k-omega                 */
  RSM_BSL = 64, /* RSM with BSL                         */

  TURB_MP_KE_MIXTURE = 80, /* ke-equation for phase mixture */
  TURB_MP_KE_DISPERSED = 81, /*dilute approach solving ke-eqns for primary phase*/
  TURB_MP_KE_EACH_PHASE = 82, /* ke-equation for each phase */

  TURB_MP_RSM_MIXTURE = 85,
  TURB_MP_RSM_DISPERSED = 86,
  TURB_MP_LES_MIXTURE = 90, /* LES for phase mixture */
  TURB_MP_LES_DISPERSED = 91 /*LES dilute approach for primary phase*/
} Turb_Model_Type;


extern FLUENT_EXPORT cxboolean isLaminar(const Turb_Model_Type turb_model);
extern FLUENT_EXPORT cxboolean isTurbulent(const Turb_Model_Type turb_model);
extern FLUENT_EXPORT cxboolean isTurbulentSinglephase(const Turb_Model_Type turb_model);
extern FLUENT_EXPORT cxboolean isTurbulentMultiphase(const Turb_Model_Type turb_model);


extern FLUENT_EXPORT cxboolean rp_visc;        /* TRUE if not inviscid                   */
extern FLUENT_EXPORT cxboolean rp_inviscid;    /* TRUE if inviscid                       */
extern FLUENT_EXPORT cxboolean rp_lam;         /* TRUE if laminar flow                   */
extern FLUENT_EXPORT cxboolean rp_turb;        /* TRUE if any turbulence model is on     */
extern FLUENT_EXPORT cxboolean rp_trb_scl;     /* TRUE if turbulent scales are computed  */
extern FLUENT_EXPORT cxboolean rp_get_tke;     /* TRUE if k-eps, k-w or rsm              */
extern FLUENT_EXPORT cxboolean rp_rough_wall;  /* TRUE if rough walls allowed            */

extern FLUENT_EXPORT cxboolean M_optional_roughness_model;  /* TRUE if optional roughness  model is allowed   */

extern FLUENT_EXPORT cxboolean M_turb_non_newton_allowed;
extern FLUENT_EXPORT cxboolean M_turb_non_newton_lb;
extern FLUENT_EXPORT cxboolean M_non_newtonian;
extern FLUENT_EXPORT real M_non_newtonian_n;
extern FLUENT_EXPORT cxboolean M_turb_pk_compress;

extern FLUENT_EXPORT cxboolean M_Curvature_Correction;
extern FLUENT_EXPORT real M_curvature_correction_ccurv;
extern FLUENT_EXPORT cxboolean M_curvature_correction_expr_ccurv;
extern FLUENT_EXPORT cxboolean M_curvature_correction_udf_ccurv;
extern FLUENT_EXPORT cxboolean M_curvature_correction_adjoint_ccurv;

extern FLUENT_EXPORT cxboolean M_corner_flow_correction;
extern FLUENT_EXPORT real M_corner_flow_correction_ccorner;
extern FLUENT_EXPORT cxboolean M_corner_flow_correction_expr_ccorner;
extern FLUENT_EXPORT cxboolean M_corner_flow_correction_udf_ccorner;
extern FLUENT_EXPORT cxboolean M_corner_flow_correction_adjoint_ccorner;

extern FLUENT_EXPORT cxboolean M_les_wale_sgs_mut_nwlim;

extern FLUENT_EXPORT cxboolean M_vm_ls_constant;
extern FLUENT_EXPORT real M_vm_grid_scale;
extern FLUENT_EXPORT real M_vm_eddy_size;
extern FLUENT_EXPORT real M_vm_eddy_vel;
extern FLUENT_EXPORT real M_vm_max_strmws_fluct_fract;

extern FLUENT_EXPORT cxboolean M_des_maxedge;
extern FLUENT_EXPORT real M_sa_cdes;
extern FLUENT_EXPORT real M_sst_cdes;
extern FLUENT_EXPORT real M_rke_cdes;

extern FLUENT_EXPORT real M_sas_cs;

extern FLUENT_EXPORT int n_stress; /* 2*ND_ND */

extern FLUENT_EXPORT cxboolean real_gas_compressible_turbulence;


extern FLUENT_EXPORT Turb_Model_Type M_turb_model;

#define KAPPA (0.4187)
#define ELOG (9.793)
#define DRIEST (26.0)
#define KBLOW (11.0) /* Blowing constant */
/* y+ cut-off for laminar sublayer.
 * Determined by matching the shear stress at the interface.
 * Compute by iterating y+ = ln(keE * y+)/KAPPA */
#define YPPLUS_LAM (11.224708)
#define YPPLUS_LIMIT (11.225) /* scalable wall functions */
#define YPPLUS_WW (11.81)
#define BIG_YP (1.e+10)
#define SMALL_YP (1.e-3)
#define SMALL_VP (1.e-10)

#define TRB_SMALL (REAL_MIN*1.0E10)

typedef enum
{
  ELES_NULL = -1,
  ELES_SMAG = 0,
  ELES_WALE = 1,
  ELES_D_SMAG = 2,
  ELES_WMLES  = 3,
  ELES_WMLES_SO = 4
} Eles_Model_Type;

typedef enum
{
  ELES_MOM_NULL = -1,
  ELES_MOM_BCD  = 0,
  ELES_MOM_CD = 1
} Eles_Mom_Discr_Type;

typedef enum
{
  TRB_CELL_VALUE = 0,
  TRB_WALL_VALUE = 1,
  TRB_ZERO_FLUX  = 2
} Turb_BC_Type;
#define N_TURB_BC_TYPES 3

typedef enum
{
  UPLUS_LAM  = 0,
  UPLUS_TRB  = 1,
  DUPLUS_LAM = 2,
  DUPLUS_TRB = 3,
  D2UPLUS_TRB = 4
} Wall_Function_Ret_Val_Type;
#define N_TURB_WF_RET_TYPES 5

typedef enum
{
  F_MU = 0,
  F_1  = 1,
  F_2  = 2
} Damping_Function_Type;
#define N_DAMPING_FUNCTION_TYPES 3

typedef enum
{
  ABID              = 0,
  LAM_BREMHORST     = 1,
  LAUNDER_SHARMA    = 2,
  YANG_SHIH         = 3,
  ABE_KONDOH_NAGANO = 4,
  CHANG_HSIEH_CHEN  = 5,
  PEROT             = 6
} Low_Re_Model_Type;
#define N_LOW_RE_MODEL_TYPES 7

typedef enum
{
  WOLFSHTEIN      = 1,
  NORRIS_REYNOLDS = 2,
  RODI_V2         = 3
} Two_Layer_Model_Type;

typedef enum
{
  FDES_SA  = 1,
  FDDES_SA = 2,
  FDES_RKE = 1,
  FDDES_RKE = 2,
  FSST_0  = 1,
  FSST_F1 = 2,
  FSST_F2 = 3,
  FDDES_SST = 4,
  FIDDES_SST = 5
} Des_Limiter_Type;

typedef enum
{
  UDF_PRT_OFF = 0,
  UDF_PRT_K,
  UDF_PRT_D,
  UDF_PRT_O,
  UDF_PRT_T,
  UDF_PRT_T_WALL,
  UDF_PRT_H,
  UDF_PRT_MAX
} UDF_Prt_Type;

typedef enum
{
  SBES_SDES = 1,
  SBES = 2,
  SBES_UDF = 3
} Sbes_Bf_Type;

typedef enum
{
  SBES_SMAG = 1,
  SBES_D_SMAG = 2,
  SBES_WALE = 3,
  SBES_WMLES_SO = 4
} Sbes_Sgs_Type;

extern FLUENT_EXPORT Two_Layer_Model_Type M_ke_two_layer_option;
extern FLUENT_EXPORT Des_Limiter_Type M_des_limiter_option;
extern Sbes_Bf_Type M_sbes_bf_option;
extern Sbes_Sgs_Type M_sbes_sgs_option;

extern real M_ddes_Cd1;
extern FLUENT_EXPORT real get_ddes_Fd(cell_t, Thread *PTR_RESTRICT);

extern FLUENT_EXPORT Turb_BC_Type tke_bc_type;
extern FLUENT_EXPORT Turb_BC_Type tdr_bc_type;
extern FLUENT_EXPORT real tdr_wall_value;

#define CONST_OR_CACHED(const,cache,c)(NULLP(cache) ? const : cache[c0]) ;

#define TWO_LAYER_BLEND(Re_y, Re_y_c, A) \
(0.5*(1. + tanh((Re_y - Re_y_c)/A)))

#define TRB_VEL_SCAL(c,t) Compute_Trb_Vscal(c,t)
#define TRB_TIM_SCAL(c,t) Compute_Trb_Tscal(c,t)
#define TRB_LEN_SCAL(c,t) Compute_Trb_Vscal(c,t)*Compute_Trb_Tscal(c,t)
#define TRB_RE(c,t) C_R(c,t)*TRB_VEL_SCAL(c,t)*TRB_LEN_SCAL(c,t)/C_MU_L(c,t)

#define K_FROM_TU(I,V2)(1.5*(V2)*(I)*(I))
#define D_FROM_LEN_SCL(l,k)((k)*sqrt(k)/(l))
#define D_FROM_VIS_RAT(r,rho,k,mu,cmu)((cmu)*(rho)*(k)*(k)/((r)*(mu)))
#define W_FROM_LEN_SCL(l,k,cmu)(sqrt(k)/((cmu)*(l)))
#define W_FROM_VIS_RAT(r,rho,k,mu)((rho)*(k)/((r)*(mu)))
#define W_FROM_VIS_RAT_KKLW(r,rho,k,mu,cmu)((rho)*(k)*(cmu)/((r)*(mu)))

#define C_MU_T_REG(c,t) (C_MU_T(c,t) + 0.001*C_MU_L(c,t));

#define LES_IN_CELL_THREAD_P(t)  (GVAR_TURB(rp, les) || THREAD_VAR(t).fluid.eles)

FLUENT_EXPORT real Get_Upstream_Tke_Value(cell_t c, Thread *t);

FLUENT_EXPORT real Get_Harmonic_Averaged_Tke_Value(cell_t c, Thread *t);

FLUENT_EXPORT real Get_Trans_Alg_Rec_Cor(cell_t c, Thread *t, real rho, real mu, real wall_dist,
                                         real omg, real Smag, real Rmag);

FLUENT_EXPORT real Get_Trans_Alg_Tul(cell_t c, Thread *t, real omg, real wall_dist);

FLUENT_EXPORT real Get_Trans_Alg_Lambda(cell_t c, Thread *t, real rho, real mu, real wall_dist);

FLUENT_EXPORT void Alloc_Corner_Flow_Correction_Coefficient(Domain *domain);
FLUENT_EXPORT void Free_Corner_Flow_Correction_Coefficient(Domain *domain);
FLUENT_EXPORT void Nonlinear_Terms(cell_t c, Thread *t, real(*AST)[3], Svar sv_k);

FLUENT_EXPORT real Nonlinear_Alpha1_Tau(cell_t c, Thread *t, real eta2, real tau2,
                                        real gama0_star, real gama1_star,
                                        real a1, real a2, real a3, real wmod2);

FLUENT_EXPORT real WJ_BSL_EARSM_Compute_N(real iiS, real iiW, real a1, real a3, real a4,
                                          real c1Prime,       real cDiff,       real nEq);

FLUENT_EXPORT real Strainrate_Term_Wale(cell_t c, Thread *t, real u_g[], real v_g[], real w_g[],
                                        real omega_g[], real v, real swirl);

FLUENT_EXPORT void Get_Strain_Tensor(cell_t c, Thread *t, real u_g[], real v_g[], real w_g[],
                                     real omega_g[], real v, real swirl, real(*S)[3]);

FLUENT_EXPORT void Get_Vorticity_Tensor(cell_t c, Thread *t, real u_g[], real v_g[], real w_g[],
                                        real omega_g[], real axis[], real omega, real v, real swirl,
                                        cxboolean rotation, real(*W)[3]);

FLUENT_EXPORT void Std_Thermal_Wall_Func(real rkcon, real kPlus,
                                         real yPlus, real uStar, real rho, real Cp,
                                         real Pr, real Prt, real up, real *a, real *b);

FLUENT_EXPORT void Enh_Thermal_Wall_Func(real rkcon, real kPlus, real vwPlus, real alpha,
                                         real beta, real gamma, real yPlus, real nu_t_Plus, real uStar,
                                         real rho, real Cp, real Pr, real Prt, real u,
                                         real *a, real *b);

FLUENT_EXPORT real Compute_tSlip(face_t f, Thread *t, cell_t c0, Thread *t0,
                                 real up, real yp, real uStar,
                                 real Tw, real Tc,
                                 real Prt, real ks, real rkcon,
                                 real rho, real mu, real cp, real k,
                                 real alpha, real beta, real gamma,
                                 real vwPlus, cxboolean eles_in_t0);

FLUENT_EXPORT real Compute_ke_effective_conductivity(face_t f, Thread *t, cell_t c0, Thread *t0,
                                                     real up, real yp, real uStar, real At,
                                                     real Prt, real ks, real rkcon,
                                                     real rho, real mu, real cp, real k,
                                                     real alpha, real beta, real gamma,
                                                     real vwPlus,
                                                     real *q_diss, cxboolean eles_in_t0);

FLUENT_EXPORT real Get_Wall_k_Prod(face_t f, Thread *t, cell_t c0, Thread *t0,
                                   real ks, real rkcon, real yp, real uStar, real up,
                                   real rho, real mu,
                                   real alpha, real beta, real gamma, real vwPlus,
                                   int ictyp);

FLUENT_EXPORT real Get_Linearized_Wall_Eps(face_t f, Thread *t, cell_t c0, Thread *t0,
                                           real ks, real rkcon, real yp,
                                           real uStar, real rho, real mu,
                                           real alpha, real beta, real gamma, real vwPlus,
                                           real tke, int ictyp);

FLUENT_EXPORT real Get_kwPlus(real kPlus);
FLUENT_EXPORT real Get_wwPlus(real kPlus);
FLUENT_EXPORT real Get_wnuPlus(real yp, real ks, real rho, real mu, real uStar);
FLUENT_EXPORT real Get_Wall_Omega(real ks, real rkcon, real yp, real uStar, real rho, real mu);
FLUENT_EXPORT real Get_Wall_k(real ks, real rkcon, real yp, real uStar, real rho, real mu);

FLUENT_EXPORT real Get_kw_Cross_Deriv(real k_g[], real o_g[], real o);

FLUENT_EXPORT real Extrapolated_Wall_Eps(face_t f, Thread *t, cell_t c0, Thread *t0,
                                         real ks, real rkcon, real yp, real uStar,
                                         real rho, real mu, real tdr,
                                         real alpha, real beta, real gamma, real vwPlus);

FLUENT_EXPORT real Extrapolated_Wall_Omega(real ks, real rkcon, real yp, real uStar, real rho,
                                           real mu, real sdr);

FLUENT_EXPORT real Two_Layer_Vis_Rat(real Re_y, real C_mu);

FLUENT_EXPORT real Two_Layer_L_eps(real yp, real Re_y, real c_l);

FLUENT_EXPORT real Compute_Trb_Vscal(cell_t c, Thread *t);

FLUENT_EXPORT real Compute_Trb_Tscal(cell_t c, Thread *t);

FLUENT_EXPORT real Compute_L_sgs(cell_t c, Thread *t, real vol, real dist, real les_con);

FLUENT_EXPORT real Compute_Hmax(cell_t c, Thread *t);

FLUENT_EXPORT real Compute_Filter_L_sgs(cell_t c, Thread *t, real vol);

FLUENT_EXPORT void Update_Second_Velocity_Derivative(Domain *domain);

FLUENT_EXPORT real Get_Up(real u, real v, real w, real xf[], real x0[], real A[],
                          real Vw[ND_3], real Vp[ND_3]);

FLUENT_EXPORT real uStar_From_k(real k, real yp, real up, real rho, real mu);

FLUENT_EXPORT real uStar_From_mu_t(real mu_t, real yp, real up, real rho, real mu,
                                   real ks, real rkcon, cxboolean les_in_t0);

FLUENT_EXPORT real Get_Turb_Resistance(face_t f, Thread *t, cell_t c0, Thread *t0,
                                       real alpha, real beta, real gamma, real vwPlus,
                                       real yp, real ks, real rkcon, real rho, real mu,
                                       real uStar, real pg[], real up, real Vp[ND_3],
                                       cxboolean les_in_t0);

FLUENT_EXPORT void Compute_uSlip(face_t f, Thread *t, cell_t c0, Thread *t0,
                                 real uStar, real ks, real rkcon,
                                 real up, real yp, real rho, real mu,
                                 real vwPlus, real alpha, real beta, real gamma,
                                 real u, real v, real w,
                                 real uw[], real us[], real Vp[], cxboolean les_in_t0);

FLUENT_EXPORT real Get_WF_Alpha(real pg[], real Vp[], real up, real rho, real mu,
                                real uStar);

FLUENT_EXPORT real Get_WF_Beta(real At, real T_w, real q_w, real Prt, real cp, real rho,
                               real uStar);

FLUENT_EXPORT real Get_WF_Gamma(real Prt, real uStar, real cp, real T_w);

FLUENT_EXPORT void Compute_Tfiltered_Scalar(Domain *d,
                                            Svar sv, Svar svf);

FLUENT_EXPORT void Compute_Tfiltered_Vector_Svar(Domain *d,
                                                 Svar sv, Svar svf);

FLUENT_EXPORT void Compute_Tfiltered_Vector(Domain *d,
                                            ND_VEC(Svar svx, Svar svy, Svar svz),
                                            ND_VEC(Svar svfx, Svar svfy, Svar svfz));

FLUENT_EXPORT void Compute_Tfiltered_Stress(Domain *d,
                                            Svar sv, Svar svf);

FLUENT_EXPORT void Update_Leonard_Stress(Domain *d);
FLUENT_EXPORT void Update_Modeled_Stress(Domain *d,
                                         Turb_Model_Type turb_model);

FLUENT_EXPORT void Update_Dynamic_Viscosity_Const(Domain *d,
                                                  Turb_Model_Type turb_model);
FLUENT_EXPORT void Update_Dynamic_Dissipation(Domain *domain);
FLUENT_EXPORT void Compute_Dynamic_Prandtl_Number(Domain *d, Svar sw, Svar rgw, Svar pr);

FLUENT_EXPORT cxboolean is_eles_rans_les_interface_flow_from_t0(Thread *t);

FLUENT_EXPORT Turb_Model_Type Thread_Turb_Model(Thread *);
FLUENT_EXPORT real Thread_LES_Const(Thread *);
FLUENT_EXPORT real Thread_Wall_Prandtl(Thread *);
FLUENT_EXPORT void alloc_thread_tmp_sv(Thread *thread, Svar nv, size_t nbytes);

#define COMPUTE_L_DES(ls_les,c,t,cfac,cdes)\
{\
if (M_des_maxedge)\
  {\
    real hmax = Compute_Hmax(c,t);\
    ls_les = cdes * hmax;\
  }\
else\
  {\
    ls_les   = cdes * pow(C_VOLUME(c,t), cfac);\
  }\
}

#define COMPUTE_HDIAGONAL(hdiagonal,c,t)\
{\
  int ni0, ni1;\
  real diagonal = -1e10;\
  real d10;\
  real NV_VEC(xnode0), NV_VEC(xnode);\
  c_node_loop (c,t,ni0)\
  {\
    NV_V(xnode0,=,NODE_COORD(C_NODE(c,t,ni0)));\
    for(ni1=ni0+1; ni1<C_NNODES(c,t); ni1++)\
    {\
      NV_V(xnode,=,NODE_COORD(C_NODE(c,t,ni1)));\
      d10 = NV_DST2(xnode0,xnode);\
      if (diagonal<d10)\
        diagonal = d10;\
    }\
  }\
  hdiagonal = sqrt(diagonal);\
}

#define USE_LOCAL_DISCRETIZATION(t0,eles_interior,discr_scheme_local,second_order_local)\
{\
if (eles_interior)\
  {\
    Eles_Mom_Discr_Type \
    embedded_les_scheme = (Eles_Mom_Discr_Type) THREAD_VAR(t0).fluid.eles_mom_scheme;\
    switch (embedded_les_scheme)\
    {\
      case ELES_MOM_BCD:\
  discr_scheme_local = HR_BLEND;\
  second_order_local = TRUE;\
  break;\
      case ELES_MOM_CD:\
  discr_scheme_local = CENTRAL_DIFFERENCING;\
  second_order_local = TRUE;\
  break;\
      default:\
  Internal_Error("embedded les  scheme type unavailable");\
    }\
  }\
}

#define IS_ELES_PRESENT(domain,eles_present)\
{\
 Thread *_t_eles;\
 thread_loop_c (_t_eles,domain)\
  {\
   if (THREAD_MATERIAL(_t_eles) != NULL)\
   {\
     if (FLUID_THREAD_P(_t_eles)) eles_present = THREAD_VAR(_t_eles).fluid.eles; \
     if (eles_present) break;\
   }\
  }\
}


#define  RANS_LES_INTERFACE_THREAD_P(t)  \
         ((THREAD_F_INTERIOR == THREAD_TYPE(t)) && \
             (LES_SPEC_NO_PERTURB != THREAD_VAR(t).interior.les_spec))


#define IS_RANS_LES_INTERFACE_PRESENT(domain,rli_present)\
{\
 Thread *_t_eles;\
 thread_loop_f (_t_eles,domain)\
   {\
     rli_present = RANS_LES_INTERFACE_THREAD_P(_t_eles); \
     if (rli_present) \
       break; \
   }\
}


#define COMPUTE_RANS_TURB_INTERIOR(crans,trans,l_scale,t_scale,k,eps)\
{\
   switch (M_turb_model)\
     {\
     case STD_KE:\
     case RNG_KE:\
     case REAL_KE:\
     case LOWRE_KE:\
     case EASM_KE:\
     case DES_RKE:\
     case V2F:\
       {\
         k   = C_K(crans,trans);\
         eps = C_D(crans,trans);\
         l_scale = pow(k,3./2.)/eps;\
         t_scale = k/eps;\
       }\
       break;\
     case RSM_SKE:\
     case RSM_RKE:\
       {\
   k   = 0.5*(C_RUU(crans,trans)+C_RVV(crans,trans)+C_RWW(crans,trans));\
   eps = C_D(crans,trans);\
         l_scale = pow(k,3./2.)/eps;\
         t_scale = k/eps;\
       }\
       break;\
     case RSM_K_OMEGA:\
     case RSM_BSL:\
       {\
         k   = 0.5*(C_RUU(crans,trans)+C_RVV(crans,trans)+C_RWW(crans,trans));\
         eps = GVAR_TURB(coeff, kw_beta_star_inf)*k*C_O(crans,trans);\
         l_scale = pow(k,3./2.)/eps;\
         t_scale = k/eps;\
       }\
       break;\
     case TRANS_K_OMEGA:\
       {\
   k   = C_K(crans,trans);\
         eps = k*C_O(crans,trans);\
         l_scale = pow(k,3./2.)/eps;\
         t_scale = k/eps;\
       }\
       break;\
     case K_OMEGA:\
     case K_OMEGA_EASM:\
     case WJ_BSL_EARSM:\
     case BSL:\
     case GEKO:\
     case SST:\
     case TRANS_SST:\
     case SAS_SST:\
     case DES_SST:\
       {\
   k   = C_K(crans,trans);\
         eps = GVAR_TURB(coeff, kw_beta_star_inf)*k*C_O(crans,trans);\
         l_scale = pow(k,3./2.)/eps;\
         t_scale = k/eps;\
       }\
       break;\
     case SA:\
     case DES_SA:\
       {\
         real nut = C_NUT(crans,trans);\
         real d_w = C_WALL_DIST(crans,trans);\
         real nu = C_MU_L(crans, trans) / C_R(crans, trans);   \
         k =  SQR(nut)/(sqrt(0.09) * SQR(KAPPA) * SQR(d_w));   \
         l_scale = pow(0.09, -0.75) * KAPPA * d_w;   \
         t_scale = SQR(KAPPA) / sqrt(0.09) * SQR(d_w) / (nut + nu);   \
       }\
       break;\
     default:\
       if (0 == crans) \
         CX_Message("\nArtifical Fluctuation Generation on Zone no. %d: Unexpected global turbulence model.\n", \
                                                                THREAD_ID(trans));       \
       k =       1.e-12;   \
       eps =     1.e-15;   \
       l_scale = 1.e-03;   \
       t_scale = 1.e+03;   \
     }\
}


#include "turb_ke.h"
#include "turb_rst.h"
#include "turb_wall.h"

#endif /* _FLUENT_TURB_H */
