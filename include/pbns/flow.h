/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_FLOW_H
#define _FLUENT_FLOW_H

#include "dll.h"
#include "global.h"
#include "models.h"

#define DEFAULT_MAX_RES 1024

extern FLUENT_EXPORT int nres;  /* current number of residuals */
extern FLUENT_EXPORT int max_res; /* size of residual history buffer */
extern FLUENT_EXPORT real *count2;

extern FLUENT_EXPORT real brucato_k;
extern FLUENT_EXPORT real wde_factor;
extern FLUENT_EXPORT cxboolean Drag_Factor_WDE_AW;

extern FLUENT_EXPORT cxboolean flux_converted;




/* CR 15856 */
/* use these macros with care and be aware that using RP_Get_ .. is time
 * consuming. You should not use these macros inside loops, etc. */
#define N_ITER ((nres==0) ? 0 : (int)(count2[nres-1]+0.5)) /* iteration number, integer */
#define N_TIME (RP_Get_Integer ("time-step"))   /* integer timestep          */
#define CURRENT_TIME (RP_Get_Double("flow-time")) /*                           */
#define CURRENT_TIMESTEP (RP_Get_Real("physical-time-step")) /* real, time step size */
#define DUAL_TIMESTEP (RP_Get_Boolean("pseudo-auto-time-step?")) ? (RP_Get_Real("pseudo-auto-time-step")):(RP_Get_Real("pseudo-time-step"))
#define SOLID_TIMESTEP (RP_Get_Real("cht/solid-time-step-size"))
#define SOLID_TIME (RP_Get_Real("cht/solid-time"))
#define DBNS_E_TIMEINTER (RP_Get_Double("coupled-explicit/user-specified-time-interval"))
/* Adaptive time stepping for DBNS explicit unsteady (explicit formulation)*/
#define PREVIOUS_TIME (CURRENT_TIME - CURRENT_TIMESTEP)      /* real                  */
#define PREVIOUS_TIMESTEP (CURRENT_TIMESTEP/dt_factor)       /* real, prev. time step */
#define PREVIOUS_2_TIME (CURRENT_TIME - CURRENT_TIMESTEP - PREVIOUS_TIMESTEP) /* real */
#define END_TIME (RP_Get_Real("time-end"))                   /* real                  */
/* CR 15856 */

extern FLUENT_EXPORT real adaptive_physical_dt_initial;
extern FLUENT_EXPORT cxboolean adaptive_physical_dt_intermediate_p;

enum flow_init_type
{
  UNINIT_DATA = -1, /* uninitialized flow */
  SOLVED_DATA,    /* set value after solution has begun */
  STD_INIT,
  HYB_INIT,
  FMG_INIT,
  INTERP_DATA    /* data read from interpolation file */
};

FLUENT_EXPORT cxboolean is_statistics_on(void);

FLUENT_EXPORT void Set_Fan_Table(Domain *d, real *P, real *Q, int nrows, int threadid);
FLUENT_EXPORT void read_input_fancurve(FILE *fp, int threadid, int *nrows, real *P, real *Q);
FLUENT_EXPORT void read_fancurve_datapoints(FILE *fp, int threadid, int *nrows);
FLUENT_EXPORT void Init_3dFans(Domain *d);
FLUENT_EXPORT void Init_3dFan_Zone(Domain *d, Thread *ct);

#if HOTR_RESTART
FLUENT_EXPORT void recon_uninitialize_storage(Domain *d);
extern FLUENT_EXPORT cxboolean pre_or_post_gradient_p;
extern FLUENT_EXPORT cxboolean restart_from_case_data_p;
#endif

extern FLUENT_EXPORT real physical_dt_m1;
extern FLUENT_EXPORT real physical_dt_p;
extern FLUENT_EXPORT cxboolean remesh_force_first_order_in_time;
extern FLUENT_EXPORT cxboolean swap_adapt_force_first_order_in_time;
extern FLUENT_EXPORT cxboolean mdm_allow_unsteady_rc_p;
extern FLUENT_EXPORT real transient_blend_factor;

extern FLUENT_EXPORT int current_iter;
extern FLUENT_EXPORT int current_global_iter;
extern FLUENT_EXPORT int step_iteration;
extern FLUENT_EXPORT cxboolean first_iter_in_interval_p;
extern FLUENT_EXPORT cxboolean first_iteration;
extern FLUENT_EXPORT cxboolean flow_warnings_p;
extern FLUENT_EXPORT cxboolean pollut_post;
#if RP_NODE
extern FLUENT_EXPORT cxboolean sync_p;
extern FLUENT_EXPORT cxboolean sync_amg_p;
#endif
extern FLUENT_EXPORT int uref2_update_count;  /* counter for update_uref2 */
extern FLUENT_EXPORT cxboolean final_stage_p;
extern FLUENT_EXPORT cxboolean fine_domain_iter_p;

extern FLUENT_EXPORT cxboolean FMG_fine_domain_iter_p; /* changes for FMG */

extern FLUENT_EXPORT cxboolean limiter_warnings_p;
extern FLUENT_EXPORT real dom_blending_factor;
extern FLUENT_EXPORT cxboolean solve_radiation;
extern FLUENT_EXPORT cxboolean solve_radiation_mc;
extern FLUENT_EXPORT cxboolean solve_radiation_s2s;
extern FLUENT_EXPORT cxboolean solve_radiation_solar;
extern FLUENT_EXPORT cxboolean solve_radiation_n_time_step;
extern FLUENT_EXPORT real pbns_blending;
extern FLUENT_EXPORT real dbns_blending;

extern FLUENT_EXPORT int current_domain_iter_stage;

FLUENT_EXPORT void Set_Residual_History_Size(int);
FLUENT_EXPORT void Free_Domain_Residuals(Domain *);
FLUENT_EXPORT void Init_Residuals(void);
FLUENT_EXPORT void Compact_Residuals_As_Needed(void);

FLUENT_EXPORT void Flow_Iterate(Domain *, int);
FLUENT_EXPORT void Reset_Residuals(Domain *);
FLUENT_EXPORT int Get_Step_Counter (void);
FLUENT_EXPORT int Get_Current_Iteration(void);
FLUENT_EXPORT void Calculation_Time_Out_Check(int *, const int);
FLUENT_EXPORT void FMG_Init_Flow(Domain *);
FLUENT_EXPORT void Init_Flow(Domain *);
FLUENT_EXPORT void Update_After_Flow_Init(Domain *);
FLUENT_EXPORT void Clear_Cell_Function_Names(Domain *);
FLUENT_EXPORT void Set_Flow_Time (double);
FLUENT_EXPORT void Update_Physical_Time(Domain *, int);
FLUENT_EXPORT void Update_Transient_Time_Scheme(void);
FLUENT_EXPORT void Update_Motion(Domain *, real);
FLUENT_EXPORT void Update_Grid(Domain *, real, cxboolean, cxboolean);

FLUENT_EXPORT void Update_Before_Data_Read(Domain *, cxboolean);
FLUENT_EXPORT void Update_After_Data_Read(Domain *);
FLUENT_EXPORT void Viscous_Derivatives(Domain *);
FLUENT_EXPORT void ConvRG_ViscDer(Domain *);
FLUENT_EXPORT void Mark_Derivatives_Unknown(Domain *);

FLUENT_EXPORT void RP_Boundary_Viscous_Flux(Thread *thread,
                                            real integral[],
                                            int compute);

#if PARALLEL
FLUENT_EXPORT void Update_After_Migration(Domain *);
#endif

FLUENT_EXPORT cxboolean Limit_Turb_SVar(Domain *domain, Svar nv, cxboolean tell);

FLUENT_EXPORT void Patch_Variable_Names(Domain *, Pointer *);
FLUENT_EXPORT void Patch(Domain *, Pointer args);
FLUENT_EXPORT void Update_Before_Patch(Domain *, Domain *, Svar,  int *, cxboolean *, cxboolean *, cxboolean *, real *, real * );
FLUENT_EXPORT void Update_Thread_After_Patch(Domain *, Thread *, Svar, cxboolean, real, real, cxboolean, cxboolean);
FLUENT_EXPORT void Update_After_Patch(Domain *, Domain *, Svar, int, cxboolean,  int );
FLUENT_EXPORT void Smooth_Volume_Fraction_After_Patch(Domain *);
FLUENT_EXPORT void Initialize_On_Demand(Domain *);

FLUENT_EXPORT void cell_frame_velocity(cell_t c, Thread *t, real u[]);

FLUENT_EXPORT void Uninitialize_Solver_Storage_After_Grid_Update (Domain *,
                                                                  cxboolean);
FLUENT_EXPORT void Uninitialize_Gradient_Flags (void);
FLUENT_EXPORT void Update_Modified_Grid(Domain *domain);

FLUENT_EXPORT int Get_Dynamic_Adapt_Sweep_Counter(void);
FLUENT_EXPORT void Reset_Adaption_Counter(void);
FLUENT_EXPORT void Perform_Dynamic_Mesh_Adaption(Domain *);
FLUENT_EXPORT void Init_Interior_Face_Data (face_t, Thread *);
FLUENT_EXPORT void Interpolate_Face_Data_List (face_t *lo, Thread **tlo, int no, face_t *ln, Thread **tln, int nn);
FLUENT_EXPORT void Interpolate_Cell_Data_List(cell_t *lo, Thread **tlo, int no, cell_t *ln, Thread **tln, int nn);
FLUENT_EXPORT void Interpolate_Cell_Data_List_Time_Second_Order(cell_t *lo, Thread **tlo, int no, cell_t *ln, Thread **tln, int nn);
FLUENT_EXPORT void update_udiff_after_remesh(face_t, Thread *);
FLUENT_EXPORT void update_udiff_after_layer(face_t *, Thread **, int );
FLUENT_EXPORT cxboolean Transient_Check_Swap_Or_Adapt_Mesh(cxboolean);
FLUENT_EXPORT void mdm_press_work_energy_source_correction(Domain *, Svar );
FLUENT_EXPORT void Calculate_MDM_Press_Work_Source(Domain *);

FLUENT_EXPORT void transform_thread_velocities(Thread *t, int sgn1, Thread *t2, int sgn2);
FLUENT_EXPORT void cell_velocity_absolute(cell_t c, Thread *t, real *u);
FLUENT_EXPORT void convt_vel_absolute(cell_t c, Thread *t, real *u);
FLUENT_EXPORT void cell_velocity_reference_relative(cell_t c, Thread *t, Thread *tref, real *u);
FLUENT_EXPORT void boundary_face_velocity_absolute(face_t f, Thread *t, real u[]);
FLUENT_EXPORT void boundary_face_velocity_reference_relative(face_t f, Thread *t, Thread *tref, real u[]);
FLUENT_EXPORT void cell_mp_v_absolute(cell_t c, Thread *t, real *u);
FLUENT_EXPORT void cell_mp_v_reference_relative(cell_t c, Thread *t, Thread *tref, real *u);
FLUENT_EXPORT void Rel_cell_velocity(cell_t c, Thread *t, real *u, real *dOM);
FLUENT_EXPORT void Flags_Additional_Inits(void);
FLUENT_EXPORT float *Ref_Pressure_Location(Thread *t, cell_t c, int set);

FLUENT_EXPORT void absolute_to_solved_velocities(Domain *domain);
FLUENT_EXPORT void solved_to_absolute_velocities(Domain *domain);
FLUENT_EXPORT void absolute_to_solved_velocity_gradients(Domain *domain);
FLUENT_EXPORT void Convert_Data_To_Relative(Domain *domain);
FLUENT_EXPORT void Convert_Data_To_Absolute(Domain *domain);
FLUENT_EXPORT real Cell_Strain_Rate_Mag(cell_t c, Thread *t);

FLUENT_EXPORT void Get_Wall_Face_Velocity_Value(face_t f, Thread *tf, cell_t c0, Thread *tc0, real V_w[]);

extern FLUENT_EXPORT cxboolean recon_disabled;
extern FLUENT_EXPORT cxboolean reconstruction_converged_p;

FLUENT_EXPORT void Initialize_Reconstruction(Domain *);
FLUENT_EXPORT void Set_Reconstruction_Converged_P(cxboolean value);
FLUENT_EXPORT void Converge_Reconstruction(Domain *);
FLUENT_EXPORT void Linear_Reconstruction(Domain *);
FLUENT_EXPORT void Update_Boundary_Species_on_wall_thread(Thread *);
FLUENT_EXPORT void LSQ_Init_Reconstruction(Domain *);
FLUENT_EXPORT void solver_update(Domain *domain);
FLUENT_EXPORT void Calculate_Automatic_pseudo_time_step(Domain *domain);
FLUENT_EXPORT void MP_Calculate_Automatic_pseudo_time_step(Domain *domain);
FLUENT_EXPORT real Solid_Zone_Automatic_Time_Step(Domain *domain);
FLUENT_EXPORT real Thread_Solid_Zone_Automatic_Time_Step(Thread *thread);
FLUENT_EXPORT void Calculate_solid_time_step_auto(Domain *domain);

FLUENT_EXPORT void Set_All_Node_Weight_Init_P(cxboolean);
FLUENT_EXPORT void Set_Node_Weight_Init_P(cxboolean);
FLUENT_EXPORT cxboolean Get_Node_Weight_Init_P(void);

FLUENT_EXPORT real  Get_MCFL_Multiplier (cell_t c, Thread *);

#if RP_NODE
FLUENT_EXPORT void Init_Timer_History(Domain *d);
FLUENT_EXPORT void Clear_Timer_History(Domain *d);
FLUENT_EXPORT void Print_Timer_History(Domain *, int, int);
#endif

FLUENT_EXPORT int  Get_AR_Tag (cell_t c, Thread *);
FLUENT_EXPORT real Directional_Min_AR (cell_t c, Thread *, cxboolean);

FLUENT_EXPORT real Strainrate_Sqr(cell_t c, Thread *t, real u_g[], real v_g[], real w_g[],
                                  real omega_g[], real v);

FLUENT_EXPORT real Rotationrate_Sqr(cell_t c, Thread *t, real u_g[], real v_g[], real w_g[],
                                    real omega_g[], real axis[], real omega, real v, real swirl);

FLUENT_EXPORT real Strainrate_Mag(cell_t, Thread *);
FLUENT_EXPORT real Rotationrate_Mag(cell_t, Thread *);

FLUENT_EXPORT void Calc_Porous_Forces(Thread *thread, Svar sv_force);
FLUENT_EXPORT void Retrieve_Porous_Force_Moment(Thread *thread, real *m_center, real *forces, real *moments);
FLUENT_EXPORT void Retrieve_Porous_Force_Moment_Nodes(Thread *thread, real *m_center, real *forces, real *moments);

FLUENT_EXPORT void save_current_residuals(int count);

/* NV_S (a, =, 2) */
#define NV_S(a,EQ,s)ND_VEC((a)[0]EQ(s),(a)[1]EQ(s),(a)[2]EQ(s))
#define ND_S(a0,a1,a2,EQ,s)ND_VEC((a0)EQ(s),(a1)EQ(s),(a2)EQ(s))
#define NT_S(a,EQ,s)ND_VEC(NV_S((a)[0],EQ,s), \
                           NV_S((a)[1],EQ,s), \
                           NV_S((a)[2],EQ,s))
/* NV_V (a, =, x) */
#define NV_V(a,EQ,x)ND_VEC((a)[0]EQ(x)[0],(a)[1]EQ(x)[1],(a)[2]EQ(x)[2])
#define ND_D(a0,a1,a2,EQ,x0,x1,x2)ND_VEC((a0)EQ(x0),(a1)EQ(x1),(a2)EQ(x2))
#define NV_D(a,EQ,x0,x1,x2)ND_D((a)[0],(a)[1],(a)[2],EQ,x0,x1,x2)
#define ND_V(a0,a1,a2,EQ,x)ND_D(a0,a1,a2,EQ,(x)[0],(x)[1],(x)[2])
#define NVD_V NV_D          /*obsolete*/
#define NT_T(a,EQ,x)ND_VEC(NV_V((a)[0],EQ,(x)[0]), \
                           NV_V((a)[1],EQ,(x)[1]), \
                           NV_V((a)[2],EQ,(x)[2]))
/* NV_VS (a, =, x,/,2) */
#define NV_VS(a,EQ,x,S,s)ND_VEC((a)[0]EQ(x)[0]S(s),(a)[1]EQ(x)[1]S(s),(a)[2]EQ(x)[2]S(s))
#define NV_DS(a,EQ,x0,x1,x2,S,s)ND_VEC((a)[0]EQ(x0)S(s),(a)[1]EQ(x1)S(s),(a)[2]EQ(x2)S(s))
#define ND_VS(a0,a1,a2,EQ,x,S,s)ND_VEC((a0)EQ(x)[0]S(s),(a1)EQ(x)[1]S(s),(a2)EQ(x)[2]S(s))
#define ND_DS(a0,a1,a2,EQ,x0,x1,x2,S,s)ND_VEC((a0)EQ(x0)S(s),(a1)EQ(x1)S(s),(a2)EQ(x2)S(s))
#define NT_TS(a,EQ,x,S,s)ND_VEC(NV_VS((a)[0],EQ,(x)[0],S,s), \
                                NV_VS((a)[1],EQ,(x)[1],S,s), \
                                NV_VS((a)[2],EQ,(x)[2],S,s))
/* NV_VV (a, =, x,+,y) */
#define NV_VV(a,EQ,x,V,y)ND_VEC((a)[0]EQ(x)[0]V(y)[0],(a)[1]EQ(x)[1]V(y)[1],(a)[2]EQ(x)[2]V(y)[2])
#define NV_DD(a,EQ,x0,x1,x2,V,y0,y1,y2) ND_VEC((a)[0]EQ(x0)V(y0),(a)[1]EQ(x1)V(y1),(a)[2]EQ(x2)V(y2))
#define NV_DV(a,EQ,x0,x1,x2,V,y) ND_VEC((a)[0]EQ(x0)V(y)[0],(a)[1]EQ(x1)V(y)[1],(a)[2]EQ(x2)V(y)[2])
#define ND_DD(a0,a1,a2,EQ,x0,x1,x2,V,y0,y1,y2) ND_VEC((a0)EQ(x0)V(y0),(a1)EQ(x1)V(y1),(a2)EQ(x2)V(y2))
#define NT_TT(a,EQ,x,V,y)ND_VEC(NV_VV((a)[0],EQ,(x)[0],V,(y)[0]), \
                                NV_VV((a)[1],EQ,(x)[1],V,(y)[1]), \
                                NV_VV((a)[2],EQ,(x)[2],V,(y)[2]))

/* NV_VV_S (a, =, x,+,y, /, 2) */
#define NV_VV_S(a,EQ,x,V,y,S,s)ND_VEC((a)[0]EQ((x)[0]V(y)[0])S(s),(a)[1]EQ((x)[1]V(y)[1])S(s),(a)[2]EQ((x)[2]V(y)[2])S(s))
#define NV_VVS NV_VV_S
#define NV_DV_S(a,EQ,x0,x1,x2,V,y,S,s)ND_VEC((a)[0]EQ((x0)V(y)[0])S(s),(a)[1]EQ((x1)V(y)[1])S(s),(a)[2]EQ((x2)V(y)[2])S(s))
#define NV_DD_S(a,EQ,x0,x1,x2,V,y0,y1,y2,S,s)ND_VEC((a)[0]EQ((x0)V(y0))S(s),(a)[1]EQ((x1)V(y1))S(s),(a)[2]EQ((x2)V(y2))S(s))
#define ND_VV_S(a0,a1,a2,EQ,x,V,y,S,s)ND_VEC((a0)EQ((x)[0]V(y)[0])S(s),(a1)EQ((x)[1]V(y)[1])S(s),(a2)EQ((x)[2]V(y)[2])S(s))

#define ND_VD_S(a0,a1,a2,EQ,x,V,y0,y1,y2,S,s)ND_VEC((a0)EQ((x)[0]V(y0))S(s),(a1)EQ((x)[1]V(y1))S(s),(a2)EQ((x)[2]V(y2))S(s))
#define ND_DV_S(a0,a1,a2,EQ,x0,x1,x2,V,y,S,s)ND_VEC((a0)EQ((x0)V(y)[0])S(s),(a1)EQ((x1)V(y)[1])S(s),(a2)EQ((x2)V(y)[2])S(s))
#define ND_DD_S(a0,a1,a2,EQ,x0,x1,x2,V,y0,y1,y2,S,s)ND_VEC((a0)EQ((x0)V(y0))S(s),(a1)EQ((x1)V(y1))S(s),(a2)EQ((x2)V(y2))S(s))

#define NT_TT_S(a,EQ,x,V,y,S,s)ND_VEC(NV_VV_S((a)[0],EQ,(x)[0],V,(y)[0],S,s), \
                                      NV_VV_S((a)[1],EQ,(x)[1],V,(y)[1],S,s), \
                                      NV_VV_S((a)[2],EQ,(x)[2],V,(y)[2],S,s))

/* NV_V_VS (a, =, x, +, (y, *, 0.5)) */
#define NV_V_VS(a,EQ,x,V,y,S,s)ND_VEC((a)[0]EQ(x)[0]V((y)[0]S(s)),(a)[1]EQ(x)[1]V((y)[1]S(s)),(a)[2]EQ(x)[2]V((y)[2]S(s)))

/* NV_VS_VS (a, =, x,*,s, +, y,*,(1-s)) */
#define NV_VS_VS(a,EQ,x,SX,sx,V,y,SY,sy)ND_VEC((a)[0]EQ(((x)[0]SX(sx))V((y)[0]SY(sy))),(a)[1]EQ(((x)[1]SX(sx))V((y)[1]SY(sy))),(a)[2]EQ(((x)[2]SX(sx))V((y)[2]SY(sy))))
#define NV_VSVS NV_VS_VS   /*obsolete*/
#define ND_DS_DS(a0,a1,a2,EQ,x0,x1,x2,SX,sx,V,y0,y1,y2,SY,sy)ND_VEC((a0)EQ(((x0)SX(sx))V((y0)SY(sy))),(a1)EQ(((x1)SX(sx))V((y1)SY(sy))),(a2)EQ(((x2)SX(sx))V((y2)SY(sy))))
#define ND_DS_VS(a0,a1,a2,EQ,x0,x1,x2,SX,sx,V,y,SY,sy)ND_VEC((a0)EQ(((x0)SX(sx))V((y)[0]SY(sy))),(a1)EQ(((x1)SX(sx))V((y)[1]SY(sy))),(a2)EQ(((x2)SX(sx))V((y)[2]SY(sy))))

/*
Tensor double dot product when A is
a 2nd order Tensor A[3][3]
a ND_ND x ND_ND matrix
a Reynolds-stress matrix reformed into an one dimensional array (a[3] for 2D and a[6] for 3D)
*/
#define RANK2_TENSOR_TRACE(A)(A[0][0]+A[1][1]+A[2][2])
#define RANK2_TENSOR_DOUBLE_DOT_PRODUCT(A,B)(\
  (A[0][0]*B[0][0])+(A[1][1]*B[1][1])+(A[2][2]*B[2][2])+\
  (A[0][1]*B[1][0])+(A[0][2]*B[2][0])+\
  (A[1][0]*B[0][1])+(A[1][2]*B[2][1])+\
  (A[2][0]*B[0][2])+(A[2][1]*B[1][2]))

#if RP_3D
#define TRACE_RST(a)(a[0]+a[1]+a[2])
#define NV_MATRIX_TRACE(A)RANK2_TENSOR_TRACE(A)
#define DOUBLE_DOT_PRODUCT_RST(a,b)(\
(a[0]*b[0])+(a[1]*b[1])+(a[2]*b[2])+\
(2.*((a[3]*b[3])+(a[4]*b[4])+(a[5]*b[5]))))
#define NV_MATRIX_DOUBLE_DOT_PRODUCT(A,B)RANK2_TENSOR_DOUBLE_DOT_PRODUCT(A,B)

#else
#define TRACE_RST(a)(a[0]+a[1])
#define NV_MATRIX_TRACE(A)(A[0][0]+A[1][1])
#define DOUBLE_DOT_PRODUCT_RST(a,b)(\
(a[0]*b[0])+(a[1]*b[1])+\
(2.*(a[2]*b[2])))
#define NV_MATRIX_DOUBLE_DOT_PRODUCT(A,B)(\
(A[0][0]*B[0][0])+(A[1][1]*B[1][1])+\
(A[1][0]*B[0][1])+(A[0][1]*B[1][0]))
#endif

#define TENSOR_MAG_RST(a)sqrt(DOUBLE_DOT_PRODUCT_RST(a,a))
#define MATRIX_MAG(A)sqrt(NV_MATRIX_DOUBLE_DOT_PRODUCT(A,A))
#define RANK2_TENSOR_MAG(A)sqrt(RANK2_TENSOR_DOUBLE_DOT_PRODUCT(A,A))


/* Bare sequence of MAX/MIN values, no assignment. */
#define NDD_MAX(a0,a1,a2,b0,b1,b2)ND_VEC(MAX((a0),(b0)),MAX((a1),(b1)),MAX((a2),(b2)))
#define NVD_MAX(a,b)ND_VEC(MAX((a)[0],(b)[0]),MAX((a)[1],(b)[1]),MAX((a)[2],(b)[2]))
#define NDD_MIN(a0,a1,a2,b0,b1,b2)ND_VEC(MIN((a0),(b0)),MIN((a1),(b1)),MIN((a2),(b2)))
#define NVD_MIN(a,b)ND_VEC(MIN((a)[0],(b)[0]),MIN((a)[1],(b)[1]),MIN((a)[2],(b)[2]))

/* Assign MAX/MIN to the FIRST argument(s) */
#define ND_MAX(a0,a1,a2,b0,b1,b2)ND_D((a0),(a1),(a2),=,MAX((a0),(b0)),MAX((a1),(b1)),MAX((a2),(b2)))
#define NV_MAX(a,b)NV_D((a),=,MAX((a)[0],(b)[0]),MAX((a)[1],(b)[1]),MAX((a)[2],(b)[2]))
#define ND_MIN(a0,a1,a2,b0,b1,b2)ND_D((a0),(a1),(a2),=,MIN((a0),(b0)),MIN((a1),(b1)),MIN((a2),(b2)))
#define NV_MIN(a,b)NV_D((a),=,MIN((a)[0],(b)[0]),MIN((a)[1],(b)[1]),MIN((a)[2],(b)[2]))

#define NV_MIN_I(v)((v)[0]<(v)[1]?((v)[0]<(v)[2]?0:2):((v)[1]<(v)[2]?1:2))

/* NV_OP_V (a, =, fabs, b) */
#define NV_OP_V(a,EQ,f,b)ND_VEC((a)[0]EQ(f((b)[0])),(a)[1]EQ(f((b)[1])),(a)[2]EQ(f((b)[2])))

#if RP_3D
# define ND_OP(OP,x,y,z)((x)OP(y)OP(z))
# define NV_LIST(a)(a)[0],(a)[1],(a)[2]
# define NV_STR(fmt, sep) fmt sep fmt sep fmt
#else
# define ND_OP(OP,x,y,z)((x)OP(y))
# define NV_LIST(a)(a)[0],(a)[1]
# define NV_STR(fmt, sep) fmt sep fmt
#endif
#define NV_OP(op,x)ND_OP(op,(x)[0],(x)[1],(x)[2])
#define N3D_OP(OP,x,y,z)((x)OP(y)OP(z))

#define ND_MAP ND_D /*obsolete*/
#define ND_SET(x0,x1,x2,y0,y1,y2)ND_D(x0,x1,x2,=,y0,y1,y2)
#define NV_SET(x, y)ND_SET(x[0], x[1], x[2], y[0], y[1], y[2]);
#define NT_SET(x, y)ND_VEC(NV_SET(x[0], y[0]), \
                           NV_SET(x[1], y[1]), \
                           NV_SET(x[2], y[2]))
#define ND_SUM(x0,x1,x2)ND_OP(+,x0,x1,x2)
#define NV_SUM(x)NV_OP(+,x)

#define ND_DOT(x0,x1,x2,y0,y1,y2)ND_OP(+,(x0)*(y0),(x1)*(y1),(x2)*(y2))
#define NV_DOT(x,y)ND_OP(+,(x)[0]*(y)[0],(x)[1]*(y)[1],(x)[2]*(y)[2])
#define NVD_DOT(x,y0,y1,y2)ND_OP(+,(x)[0]*(y0),(x)[1]*(y1),(x)[2]*(y2))

#define ND_MAG2(x0,x1,x2)ND_DOT(x0,x1,x2,x0,x1,x2)
#define NV_MAG2(x)NV_DOT(x,x)
#define ND_MAG(x0,x1,x2)sqrt(ND_MAG2(x0,x1,x2))
#define NV_MAG(x)sqrt(NV_MAG2(x))

#define NV_DST2(x1,x2)ND_OP(+,SQR((x2)[0]-(x1)[0]),SQR((x2)[1]-(x1)[1]),SQR((x2)[2]-(x1)[2]))
#define NV_DST(x1,x2)sqrt(NV_DST2(x1,x2))

/* these magnitude macros assume three components are available regardless
 * of the solver's dimension (i.e same for RP_2D & RP_3D) - useful for
 * computing velocity magnitude for 2D axi swirl */
#define N3D_SET(x,y,z,u,v,w) ((x) = (u), (y) = (v), (z) = (w))
#define N3V_SET(x, y)N3D_SET(x[0], x[1], x[2], y[0], y[1], y[2]);
#define N3T_SET(x, y)N3D_VEC(N3V_SET(x[0], y[0]), \
                             N3V_SET(x[1], y[1]), \
                             N3V_SET(x[2], y[2]))
#define N3D_SUM(x0,x1,x2)N3D_OP(+,x0,x1,x2)
#define N3V_SUM(x)N3V_OP(+,x)

#define N3D_MAG2(x0,x1,x2)((x0)*(x0)+(x1)*(x1)+(x2)*(x2))
#define N3V_MAG2(x)N3D_MAG2((x)[0],(x)[1],(x)[2])
#define N3D_MAG(x0,x1,x2)sqrt(N3D_MAG2(x0,x1,x2))
#define N3V_MAG(x)sqrt(N3V_MAG2(x))

#define N3V_DOT(x,y)N3D_OP(+,(x)[0]*(y)[0],(x)[1]*(y)[1],(x)[2]*(y)[2])
#define N3VD_DOT(x,y0,y1,y2)N3D_OP(+,(x)[0]*(y0),(x)[1]*(y1),(x)[2]*(y2))

#define N3V_DST2(x1,x2)N3D_OP(+,SQR((x2)[0]-(x1)[0]),SQR((x2)[1]-(x1)[1]),SQR((x2)[2]-(x1)[2]))
#define N3V_DST(x1,x2)sqrt(N3V_DST2(x1,x2))
/* the following macros assume three components */
#if RP_3D
# define N3V_LIST NV_LIST
# define N3V_STR NV_STR
# define N3V_VEC NV_VEC
# define N3V_S NV_S
# define N3D_S ND_S
# define N3V_V NV_V
# define N3D_V ND_V
# define N3V_D NV_D
# define N3D_D ND_D
# define N3V_VV NV_VV
# define N3V_VV_S NV_VV_S
# define N3V_VS NV_VS
# define N3V_DS NV_DS
# define N3D_DS ND_DS
# define N3V_V_VS NV_V_VS
# define N3V_VS_VS NV_VS_VS
#else
# define N3V_LIST(a)(a)[0],(a)[1],(a)[2]
# define N3V_STR(fmt, sep) fmt sep fmt sep "0.0"
# define N3V_VEC(a)(a)[3]
# define N3V_S(a,EQ,s)((a)[0]EQ(s),(a)[1]EQ(s),(a)[2]EQ(s))
# define N3D_S(a0,a1,a2,EQ,s)((a0)EQ(s),(a1)EQ(s),(a2)EQ(s))
# define N3V_V(a,EQ,x)((a)[0]EQ(x)[0],(a)[1]EQ(x)[1],(a)[2]EQ(x)[2])
# define N3D_V(a0,a1,a2,EQ,x)((a0)EQ(x)[0],(a1)EQ(x)[1],(a2)EQ(x)[2])
# define N3V_D(a,EQ,x0,x1,x2)((a)[0]EQ(x0),(a)[1]EQ(x1),(a)[2]EQ(x2))
# define N3D_D(a0,a1,a2,EQ,x0,x1,x2)((a0)EQ(x0),(a1)EQ(x1),(a2)EQ(x2))
# define N3V_VV(a,EQ,x,V,y)((a)[0]EQ(x)[0]V(y)[0],(a)[1]EQ(x)[1]V(y)[1],(a)[2]EQ(x)[2]V(y)[2])
# define N3V_VV_S(a,EQ,x,V,y,S,s)((a)[0]EQ((x)[0]V(y)[0])S(s),(a)[1]EQ((x)[1]V(y)[1])S(s),(a)[2]EQ((x)[2]V(y)[2])S(s))
# define N3V_VS(a,EQ,x,S,s)((a)[0]EQ(x)[0]S(s),(a)[1]EQ(x)[1]S(s),(a)[2]EQ(x)[2]S(s))
# define N3V_DS(a,EQ,x0,x1,x2,S,s)((a)[0]EQ(x0)S(s),(a)[1]EQ(x1)S(s),(a)[2]EQ(x2)S(s))
# define N3D_DS(a0,a1,a2,EQ,x0,x1,x2,S,s)((a0)EQ(x0)S(s),(a1)EQ(x1)S(s),(a2)EQ(x2)S(s))
# define N3V_V_VS(a,EQ,x,V,y,S,s)((a)[0]EQ(x)[0]V((y)[0]S(s)),(a)[1]EQ(x)[1]V((y)[1]S(s)),(a)[2]EQ(x)[2]V((y)[2]S(s)))
# define N3V_VS_VS(a,EQ,x,SX,sx,V,y,SY,sy)((a)[0]EQ(((x)[0]SX(sx))V((y)[0]SY(sy))),(a)[1]EQ(((x)[1]SX(sx))V((y)[1]SY(sy))),(a)[2]EQ(((x)[2]SX(sx))V((y)[2]SY(sy))))
#endif

#if RP_3D
# define ND_CROSS_X(x0,x1,x2,y0,y1,y2)(((x1)*(y2))-((y1)*(x2)))
# define ND_CROSS_Y(x0,x1,x2,y0,y1,y2)(((x2)*(y0))-((y2)*(x0)))
#else
/* (x0,x1,0) X (y0,y1,0) */
# define ND_CROSS_X(x0,x1,x2,y0,y1,y2)(0.0)
# define ND_CROSS_Y(x0,x1,x2,y0,y1,y2)(0.0)
#endif
# define ND_CROSS_Z(x0,x1,x2,y0,y1,y2)(((x0)*(y1))-((y0)*(x1)))

#define NV_CROSS_X(x,y)ND_CROSS_X(x[0],x[1],x[2],y[0],y[1],y[2])
#define NV_CROSS_Y(x,y)ND_CROSS_Y(x[0],x[1],x[2],y[0],y[1],y[2])
#define NV_CROSS_Z(x,y)ND_CROSS_Z(x[0],x[1],x[2],y[0],y[1],y[2])
#define NV_CROSS(a,x,y)NV_D(a,=,NV_CROSS_X(x,y),NV_CROSS_Y(x,y),NV_CROSS_Z(x,y))

/* The following N3D, N3V macros are used when one of the vectors
 * becomes (0,0,1) in 2D (e.g., an axis of rotation) */

#if RP_3D
# define N3D_VEC ND_VEC
# define N3D_DOT ND_DOT
# define N3D_CROSS_X ND_CROSS_X
# define N3D_CROSS_Y ND_CROSS_Y
# define N3D_CROSS_Z ND_CROSS_Z
# define N3V_CROSS_X NV_CROSS_X
# define N3V_CROSS_Y NV_CROSS_Y
# define N3V_CROSS_Z NV_CROSS_Z
#else
# define N3D_VEC(x,y,z)0.0,0.0,1.0
/* (0,0,1) . (y0,y1,y2) */
# define N3D_DOT(x1,y1,z1,x2,y2,z2)(z2)
/* (0,0,1) X (y0,y1,0) */
# define N3D_CROSS_X(x0,x1,x2,y0,y1,y2)(-(y1))
# define N3D_CROSS_Y(x0,x1,x2,y0,y1,y2)(y0)
# define N3D_CROSS_Z(x0,x1,x2,y0,y1,y2)(0.0)
# define N3V_CROSS_X(x,y)(-(y[1]))
# define N3V_CROSS_Y(x,y)(y[0])
# define N3V_CROSS_Z(x,y)(0.0)
#endif

#define N3V_CROSS(a,x,y)NV_D(a,=,N3V_CROSS_X(x,y),N3V_CROSS_Y(x,y),N3V_CROSS_Z(x,y))

/* Macros for cross-products of 3D vectors giving a 3D vector
   These are needed when Reynolds-stresses are transformed
   from local to global coordinates.

   x,y are 3D vetors, and a is the resulting 3D vector. */

#define N2V_CROSS_X(x,y)(x[1]*y[2]-x[2]*y[1])
#define N2V_CROSS_Y(x,y)(x[2]*y[0]-x[0]*y[2])
#define N2V_CROSS_Z(x,y)(x[0]*y[1]-x[1]*y[0])
#define N2V_CROSS(a,x,y)(a[0]=N2V_CROSS_X(x,y),a[1]=N2V_CROSS_Y(x,y),a[2]=N2V_CROSS_Z(x,y))

/* Macros for second-order stress tensor transfomation.
   Needed for transformation of Reynolds-stress tensor
   which is a 3 x 3 tensor regardless of dimension

   R[3][3] : stress tensor or any other second-order tensor
   A[3][3] : transformation matrix           */

#define ND_PROD(x0,x1,x2,y0,y1,y2)((x0)*(y0)+(x1)*(y1)+(x2)*(y2))
#define NV_PROD(x,y)(x[0]*y[0]+x[1]*y[1]+x[2]*y[2])
#define TENSOR_TRANS_P(R,A,i,j)\
ND_PROD(A[i][0],A[i][1],A[i][2],\
       ND_PROD(R[0][0],R[1][0],R[2][0],A[j][0],A[j][1],A[j][2]),\
       ND_PROD(R[0][1],R[1][1],R[2][1],A[j][0],A[j][1],A[j][2]),\
       ND_PROD(R[0][2],R[1][2],R[2][2],A[j][0],A[j][1],A[j][2]))
#define TENSOR_TRANS_N(R,A,i,j)\
ND_PROD(A[0][i],A[1][i],A[2][i],\
       ND_PROD(R[0][0],R[1][0],R[2][0],A[0][j],A[1][j],A[2][j]),\
       ND_PROD(R[0][1],R[1][1],R[2][1],A[0][j],A[1][j],A[2][j]),\
       ND_PROD(R[0][2],R[1][2],R[2][2],A[0][j],A[1][j],A[2][j]))

/* Macros for derivatives-of-stress-tensor (third-order
   tensor) transfomation.

   DR[3][3][ND_ND] : derivatives-of-stress-tensor
   A[3][3]         : transformation matrix
 */

#define RANK3_TENSOR_TRANS(DR,A,i,j,k)\
ND_PROD(A[0][k],A[1][k],A[2][k],\
 ND_PROD(A[0][i],A[1][i],A[2][i],\
  ND_PROD(DR[0][0][0],DR[1][0][0],DR[2][0][0],A[0][j],A[1][j],A[2][j]),\
  ND_PROD(DR[0][1][0],DR[1][1][0],DR[2][1][0],A[0][j],A[1][j],A[2][j]),\
  ND_PROD(DR[0][2][0],DR[1][2][0],DR[2][2][0],A[0][j],A[1][j],A[2][j])),\
 ND_PROD(A[0][i],A[1][i],A[2][i],\
  ND_PROD(DR[0][0][1],DR[1][0][1],DR[2][0][1],A[0][j],A[1][j],A[2][j]),\
  ND_PROD(DR[0][1][1],DR[1][1][1],DR[2][1][1],A[0][j],A[1][j],A[2][j]),\
  ND_PROD(DR[0][2][1],DR[1][2][1],DR[2][2][1],A[0][j],A[1][j],A[2][j])),\
 ND_PROD(A[0][i],A[1][i],A[2][i],\
  ND_PROD(DR[0][0][2],DR[1][0][2],DR[2][0][2],A[0][j],A[1][j],A[2][j]),\
  ND_PROD(DR[0][1][2],DR[1][1][2],DR[2][1][2],A[0][j],A[1][j],A[2][j]),\
  ND_PROD(DR[0][2][2],DR[1][2][2],DR[2][2][2],A[0][j],A[1][j],A[2][j])))

/* macros to computed "rotated" components of a vector */
/* ROTP_{XYZ} compute components of the product of matrix r with vector [x y z]
   while ROTN_{XYZ} those of the transpose of r and vector [x y z] */

#define ROTP_X(x,y,z,r)ND_DOT(x,y,z, r[0][0],r[0][1],r[0][2])
#define ROTN_X(x,y,z,r)ND_DOT(x,y,z, r[0][0],r[1][0],r[2][0])
#define ROTP_Y(x,y,z,r)ND_DOT(x,y,z, r[1][0],r[1][1],r[1][2])
#define ROTN_Y(x,y,z,r)ND_DOT(x,y,z, r[0][1],r[1][1],r[2][1])
#if RP_3D
#define ROTP_Z(x,y,z,r)ND_DOT(x,y,z, r[2][0],r[2][1],r[2][2])
#define ROTN_Z(x,y,z,r)ND_DOT(x,y,z, r[0][2],r[1][2],r[2][2])
#endif

#define NV_ROTP_X(x,r)NV_DOT(x, r[0])
#define NV_ROTN_X(x,r)NVD_DOT(x, r[0][0],r[1][0],r[2][0])
#define NV_ROTP_Y(x,r)NV_DOT(x, r[1])
#define NV_ROTN_Y(x,r)NVD_DOT(x, r[0][1],r[1][1],r[2][1])
#if RP_3D
#define NV_ROTP_Z(x,r)NV_DOT(x, r[2])
#define NV_ROTN_Z(x,r)NVD_DOT(x, r[0][2],r[1][2],r[2][2])
#endif

#define NV_ROTN_V(y,op,x,r)\
     ND_MAP((y)[0],(y)[1],(y)[2],op,NV_ROTN_X(x,r),NV_ROTN_Y(x,r),NV_ROTN_Z(x,r))

#define NV_ROTP_V(y,op,x,r)\
     ND_MAP((y)[0],(y)[1],(y)[2],op,NV_ROTP_X(x,r),NV_ROTP_Y(x,r),NV_ROTP_Z(x,r))

/* the following macros assume three components */
#define N3V_ROTP_X(x,r)N3V_DOT(x, r[0])
#define N3V_ROTN_X(x,r)N3VD_DOT(x, r[0][0],r[1][0],r[2][0])
#define N3V_ROTP_Y(x,r)N3V_DOT(x, r[1])
#define N3V_ROTN_Y(x,r)N3VD_DOT(x, r[0][1],r[1][1],r[2][1])
#define N3V_ROTP_Z(x,r)N3V_DOT(x, r[2])
#define N3V_ROTN_Z(x,r)N3VD_DOT(x, r[0][2],r[1][2],r[2][2])

#define N3V_ROTN_V(y,op,x,r)\
     N3D_D((y)[0],(y)[1],(y)[2],op,N3V_ROTN_X(x,r),N3V_ROTN_Y(x,r),N3V_ROTN_Z(x,r))

#define N3V_ROTP_V(y,op,x,r)\
     N3D_D((y)[0],(y)[1],(y)[2],op,N3V_ROTP_X(x,r),N3V_ROTP_Y(x,r),N3V_ROTP_Z(x,r))


/*
 * matrix multiply: B = A . R^T (matrices are ND_ND x ND_ND)
 */
#define MAT_A_RT(b,op,a,r)\
ND_VEC(\
NVD_V(b[0],=,NV_ROTP_X(a[0],r),NV_ROTP_Y(a[0],r),NV_ROTP_Z(a[0],r)),\
NVD_V(b[1],=,NV_ROTP_X(a[1],r),NV_ROTP_Y(a[1],r),NV_ROTP_Z(a[1],r)),\
NVD_V(b[2],=,NV_ROTP_X(a[2],r),NV_ROTP_Y(a[2],r),NV_ROTP_Z(a[2],r)))

/*
 * matrix multiply: B = A . R (matrices are ND_ND x ND_ND)
 */
#define MAT_A_R(b,op,a,r)\
ND_VEC(\
NVD_V(b[0],=,NV_ROTN_X(a[0],r),NV_ROTN_Y(a[0],r),NV_ROTN_Z(a[0],r)),\
NVD_V(b[1],=,NV_ROTN_X(a[1],r),NV_ROTN_Y(a[1],r),NV_ROTN_Z(a[1],r)),\
NVD_V(b[2],=,NV_ROTN_X(a[2],r),NV_ROTN_Y(a[2],r),NV_ROTN_Z(a[2],r)))


/* macros to compute "rotated" components of a tensor A desribed by the matrix
   [ [xx xy xz] [yx yy yz] [zx zy zz] ]*/
/* ROTP_{ij} computes the ij'th entry of the matrix product r A r^T
   while ROTN_{ij} computes those of r^T A r */
#define R_A_RT(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,i,j)\
ND_DOT(r[i][0],r[i][1],r[i][2],\
       ND_DOT(xx,xy,xz,r[j][0],r[j][1],r[j][2]),\
       ND_DOT(yx,yy,yz,r[j][0],r[j][1],r[j][2]),\
       ND_DOT(zx,zy,zz,r[j][0],r[j][1],r[j][2]))
#define RT_A_R(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,i,j)\
ND_DOT(r[0][i],r[1][i],r[2][i],\
       ND_DOT(xx,xy,xz,r[0][j],r[1][j],r[2][j]),\
       ND_DOT(yx,yy,yz,r[0][j],r[1][j],r[2][j]),\
       ND_DOT(zx,zy,zz,r[0][j],r[1][j],r[2][j]))
#define ROTP_XX(xx,xy,xz,yx,yy,yz,zx,zy,zz,r)R_A_RT(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,0,0)
#define ROTP_XY(xx,xy,xz,yx,yy,yz,zx,zy,zz,r)R_A_RT(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,0,1)
#define ROTP_YX(xx,xy,xz,yx,yy,yz,zx,zy,zz,r)R_A_RT(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,1,0)
#define ROTP_YY(xx,xy,xz,yx,yy,yz,zx,zy,zz,r)R_A_RT(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,1,1)
#if RP_3D
#define ROTP_XZ(xx,xy,xz,yx,yy,yz,zx,zy,zz,r)R_A_RT(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,0,2)
#define ROTP_YZ(xx,xy,xz,yx,yy,yz,zx,zy,zz,r)R_A_RT(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,1,2)
#define ROTP_ZX(xx,xy,xz,yx,yy,yz,zx,zy,zz,r)R_A_RT(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,2,0)
#define ROTP_ZY(xx,xy,xz,yx,yy,yz,zx,zy,zz,r)R_A_RT(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,2,1)
#define ROTP_ZZ(xx,xy,xz,yx,yy,yz,zx,zy,zz,r)R_A_RT(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,2,2)
#endif

#define ROTN_XX(xx,xy,xz,yx,yy,yz,zx,zy,zz,r)RT_A_R(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,0,0)
#define ROTN_XY(xx,xy,xz,yx,yy,yz,zx,zy,zz,r)RT_A_R(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,0,1)
#define ROTN_YX(xx,xy,xz,yx,yy,yz,zx,zy,zz,r)RT_A_R(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,1,0)
#define ROTN_YY(xx,xy,xz,yx,yy,yz,zx,zy,zz,r)RT_A_R(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,1,1)
#if RP_3D
#define ROTN_XZ(xx,xy,xz,yx,yy,yz,zx,zy,zz,r)RT_A_R(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,0,2)
#define ROTN_YZ(xx,xy,xz,yx,yy,yz,zx,zy,zz,r)RT_A_R(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,1,2)
#define ROTN_ZX(xx,xy,xz,yx,yy,yz,zx,zy,zz,r)RT_A_R(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,2,0)
#define ROTN_ZY(xx,xy,xz,yx,yy,yz,zx,zy,zz,r)RT_A_R(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,2,1)
#define ROTN_ZZ(xx,xy,xz,yx,yy,yz,zx,zy,zz,r)RT_A_R(xx,xy,xz,yx,yy,yz,zx,zy,zz,r,2,2)
#endif

/* the following macros assume that D is a ND_ND x ND_ND matrix
   and D[0][0]=u_x, D[0][1]=u_y, D[0][2]=u_z and so on. */
#define NT_R_A_RT(D,r,i,j)\
ND_DOT(r[i][0],r[i][1],r[i][2],\
       ND_DOT(D[0][0],D[1][0],D[2][0],r[j][0],r[j][1],r[j][2]),\
       ND_DOT(D[0][1],D[1][1],D[2][1],r[j][0],r[j][1],r[j][2]),\
       ND_DOT(D[0][2],D[1][2],D[2][2],r[j][0],r[j][1],r[j][2]))
#define NT_RT_A_R(D,r,i,j)\
ND_DOT(r[0][i],r[1][i],r[2][i],\
       ND_DOT(D[0][0],D[1][0],D[2][0],r[0][j],r[1][j],r[2][j]),\
       ND_DOT(D[0][1],D[1][1],D[2][1],r[0][j],r[1][j],r[2][j]),\
       ND_DOT(D[0][2],D[1][2],D[2][2],r[0][j],r[1][j],r[2][j]))
#define NT_ROTP_XX(D,r)NT_R_A_RT(D,r,0,0)
#define NT_ROTP_XY(D,r)NT_R_A_RT(D,r,0,1)
#define NT_ROTP_YX(D,r)NT_R_A_RT(D,r,1,0)
#define NT_ROTP_YY(D,r)NT_R_A_RT(D,r,1,1)
#if RP_3D
#define NT_ROTP_XZ(D,r)NT_R_A_RT(D,r,0,2)
#define NT_ROTP_YZ(D,r)NT_R_A_RT(D,r,1,2)
#define NT_ROTP_ZX(D,r)NT_R_A_RT(D,r,2,0)
#define NT_ROTP_ZY(D,r)NT_R_A_RT(D,r,2,1)
#define NT_ROTP_ZZ(D,r)NT_R_A_RT(D,r,2,2)
#endif

#define NT_ROTN_XX(D,r)NT_RT_A_R(D,r,0,0)
#define NT_ROTN_XY(D,r)NT_RT_A_R(D,r,0,1)
#define NT_ROTN_YX(D,r)NT_RT_A_R(D,r,1,0)
#define NT_ROTN_YY(D,r)NT_RT_A_R(D,r,1,1)
#if RP_3D
#define NT_ROTN_XZ(D,r)NT_RT_A_R(D,r,0,2)
#define NT_ROTN_YZ(D,r)NT_RT_A_R(D,r,1,2)
#define NT_ROTN_ZX(D,r)NT_RT_A_R(D,r,2,0)
#define NT_ROTN_ZY(D,r)NT_RT_A_R(D,r,2,1)
#define NT_ROTN_ZZ(D,r)NT_RT_A_R(D,r,2,2)
#endif

#if RP_3D
#define MAT3T(m,v0,v1,v2,v3)   ((m)[0][0] = (v1)[0] - (v0)[0], \
        (m)[1][0] = (v1)[1] - (v0)[1], \
        (m)[2][0] = (v1)[2] - (v0)[2], \
        (m)[0][1] = (v2)[0] - (v0)[0], \
        (m)[1][1] = (v2)[1] - (v0)[1], \
        (m)[2][1] = (v2)[2] - (v0)[2], \
        (m)[0][2] = (v3)[0] - (v0)[0], \
        (m)[1][2] = (v3)[1] - (v0)[1], \
        (m)[2][2] = (v3)[2] - (v0)[2])
#endif

#define  ROTATE_OR_UNROTATE_SYMM_TENSOR_2D(PN, rotated, original, rm, n_s) \
         {                                     \
           int rstress_iterator;               \
           int __ii;                           \
           int __jj;                           \
           loop_rstress(rstress_iterator, n_s) \
             {                                 \
               __ii = stress_tensor_ii[rstress_iterator];  \
               __jj = stress_tensor_jj[rstress_iterator];  \
               rotated[__ii][__jj] =  \
               rotated[__jj][__ii] =  \
                     TENSOR_TRANS_ ## PN(original, rm, __ii, __jj); \
             }  \
         }

#if RP_3D
#define  ROTATE_OR_UNROTATE_SYMM_TENSOR_3D_ADD(PN, rotated, original, rm, n_s)  /* Nothing -- ... */
/* ROTATE_OR_UNROTATE_SYMM_TENSOR_2D does it all because n_s tells it how many components (4 or 6) to treat. */
#endif

/* Note: The following useD ROTP_XX / ROTN_XX etc. on a (symmetric) tensor in a two-dim. array.
 *       Now it uses TENSOR_TRANS_P(..., ..., ..., ...) and TENSOR_TRANS_N(..., ..., ..., ...) instead.
 *       I've stated this here so that a search for ROTP_XY / ROTN_XY etc. will find this.
 */
/* Last arg. n_s intentionally ignored! */
#define  ROTATE_OR_UNROTATE_TENSOR_2D(PN, rotated, original, rm, n_s)                                       \
                        rotated[0][0] = TENSOR_TRANS_ ## PN(original, rm, 0, 0),                            \
                        rotated[0][1] = TENSOR_TRANS_ ## PN(original, rm, 0, 1),                            \
                        rotated[1][0] = TENSOR_TRANS_ ## PN(original, rm, 1, 0),                            \
                        rotated[1][1] = TENSOR_TRANS_ ## PN(original, rm, 1, 1)

#if 00
rotated[0][0] = ROT ## PN ## _XX(original[0][0],original[0][1],original[0][2],      \
                                 original[1][0],original[1][1],original[1][2],      \
                                 original[2][0],original[2][1],original[2][2],rm),  \
                rotated[0][1] = ROT ## PN ## _XY(original[0][0],original[0][1],original[0][2],      \
                                                 original[1][0],original[1][1],original[1][2],      \
                                                 original[2][0],original[2][1],original[2][2],rm),  \
                                rotated[1][0] = ROT ## PN ## _YX(original[0][0],original[0][1],original[0][2],      \
                                                                 original[1][0],original[1][1],original[1][2],      \
                                                                 original[2][0],original[2][1],original[2][2],rm),  \
                                                rotated[1][1] = ROT ## PN ## _YY(original[0][0],original[0][1],original[0][2],      \
                                                                original[1][0],original[1][1],original[1][2],      \
                                                                original[2][0],original[2][1],original[2][2],rm)
#endif


#if RP_3D
                                                                /* Last arg. n_s intentionally ignored! */
#define  ROTATE_OR_UNROTATE_TENSOR_3D_ADD(PN, rotated, original, rm, n_s)      ,                            \
                        rotated[0][2] = TENSOR_TRANS_ ## PN(original, rm, 0, 2),                            \
                        rotated[1][2] = TENSOR_TRANS_ ## PN(original, rm, 1, 2),                            \
                        rotated[2][0] = TENSOR_TRANS_ ## PN(original, rm, 2, 0),                            \
                        rotated[2][1] = TENSOR_TRANS_ ## PN(original, rm, 2, 1),                            \
                        rotated[2][2] = TENSOR_TRANS_ ## PN(original, rm, 2, 2)

#if 00
                                                                rotated[0][2] = ROT ## PN ## _XZ(original[0][0],original[0][1],original[0][2],      \
                                                                    original[1][0],original[1][1],original[1][2],      \
                                                                    original[2][0],original[2][1],original[2][2],rm),  \
                                                                    rotated[1][2] = ROT ## PN ## _YZ(original[0][0],original[0][1],original[0][2],      \
                                                                        original[1][0],original[1][1],original[1][2],      \
                                                                        original[2][0],original[2][1],original[2][2],rm),  \
                                                                        rotated[2][0] = ROT ## PN ## _ZX(original[0][0],original[0][1],original[0][2],      \
                                                                            original[1][0],original[1][1],original[1][2],      \
                                                                            original[2][0],original[2][1],original[2][2],rm),  \
                                                                            rotated[2][1] = ROT ## PN ## _ZY(original[0][0],original[0][1],original[0][2],      \
                                                                                original[1][0],original[1][1],original[1][2],      \
                                                                                original[2][0],original[2][1],original[2][2],rm),  \
                                                                                rotated[2][2] = ROT ## PN ## _ZZ(original[0][0],original[0][1],original[0][2],      \
                                                                                    original[1][0],original[1][1],original[1][2],      \
                                                                                    original[2][0],original[2][1],original[2][2],rm)
#endif
#endif

                                                                                    /* By way of the ## operator, the following macros use...
                                                                                     *  - ROTATE_OR_UNROTATE_TENSOR_2D
                                                                                     *  - ROTATE_OR_UNROTATE_TENSOR_3D_ADD
                                                                                     *  - ROTATE_OR_UNROTATE_SYMM_TENSOR_2D
                                                                                     *  - ROTATE_OR_UNROTATE_SYMM_TENSOR_3D_ADD
                                                                                     */

#define  ROTATE_OR_UNROTATE_ANY_TENSOR_2D(SYMORNOT, PN, rotated, original, rm, n_s) \
         ROTATE_OR_UNROTATE ## SYMORNOT ## TENSOR_2D(PN, rotated, original, rm, n_s)
#if RP_3D
#define  ROTATE_OR_UNROTATE_ANY_TENSOR_3D_ADD(SYMORNOT, PN, rotated, original, rm, n_s) \
         ROTATE_OR_UNROTATE ## SYMORNOT ## TENSOR_3D_ADD(PN, rotated, original, rm, n_s)
#endif

#if RP_2D
#define  ROTATE_OR_UNROTATE_ANY_TENSOR(SYMORNOT, PN, rotated, original, rm, n_s) \
         ROTATE_OR_UNROTATE_ANY_TENSOR_2D(SYMORNOT, PN, rotated, original, rm, n_s)
#else
#define  ROTATE_OR_UNROTATE_ANY_TENSOR(SYMORNOT, PN, rotated, original, rm, n_s) \
         ROTATE_OR_UNROTATE_ANY_TENSOR_2D(SYMORNOT, PN, rotated, original, rm, n_s)  \
         ROTATE_OR_UNROTATE_ANY_TENSOR_3D_ADD(SYMORNOT, PN, rotated, original, rm, n_s)
#endif

                                                                                    /* rotate a tensor (actually a symmetric tensor..!) by rotation matrix rm:
                                                                                     */
#define  ROTATE_TENSOR(rotated, original, rm) \
         ROTATE_OR_UNROTATE_ANY_TENSOR(_, P, rotated, original, rm, 0)

#define  UNROTATE_TENSOR(rotated, original, rm) \
         ROTATE_OR_UNROTATE_ANY_TENSOR(_, N, rotated, original, rm, 0)

                                                                                    /* rotate a symmetric tensor by rotation matrix rm -- reduce effort
                                                                                     * by only calculating the diagonal and one off-diag. half and
                                                                                     * copying the latter:
                                                                                     */
#define  ROTATE_SYMMETRIC_TENSOR(rotated, original, rm, n_s) \
         ROTATE_OR_UNROTATE_ANY_TENSOR(_SYMM_, P, rotated, original, rm, n_s)

#define  UNROTATE_SYMMETRIC_TENSOR(rotated, original, rm, n_s) \
         ROTATE_OR_UNROTATE_ANY_TENSOR(_SYMM_, N, rotated, original, rm, n_s)


                                                                                    /* WARNING: The following "PROJECT_..." macros are N3V versions only!! */

                                                                                    /* Project a vector "velo" onto a unit direction vector "dir": */
#define PROJECT_TO_DIR(velo, dir)                                       \
{                                                                       \
  register real _project_to_dir_scalar_prod = N3V_DOT(velo, dir);       \
  N3V_VS(velo, =, dir, *, _project_to_dir_scalar_prod);                 \
}

                                                                                    /* Project a vector "velo" onto a direction vector "vec" of arbitrary length: */
#define PROJECT_TO_VEC(velo, vec)                                       \
{                                                                       \
  register real _project_to_vec_quot = N3V_DOT(velo, vec);              \
  _project_to_vec_quot /= N3V_MAG2(vec);                                \
  N3V_VS(velo, =, vec, *, _project_to_vec_quot);                        \
}


                                                                                    /* Project a vector "velo" onto plane, given by its normal vector "vec" of arbitrary length: */
#define PROJECT_TO_PLANE(velo, plane)                                   \
{                                                                       \
  real N3V_VEC(_project_to_plane_projed_to_vect);                       \
  N3V_V(_project_to_plane_projed_to_vect, =, velo);                     \
  PROJECT_TO_VEC(_project_to_plane_projed_to_vect, plane);              \
  N3V_V(velo, -=, _project_to_plane_projed_to_vect);                    \
}
                                                                                    /* ******************************************************************* */

#define RADIANS(deg) (M_PI*(deg)/180.0)
#define DEGREES(rad) ((rad)*180.0/M_PI)

#define NINT(x) (((x - ((cxindex)(x))) > 0.5) ? ((cxindex)(x) + 1) : ((cxindex)(x)))

#define intloop(n,m) for(n=0; n<m; ++n)
#define nd_loop(n) intloop (n, ND_ND)

                                                                                    /* marks related to the shadow faces on partition interfaces */
#if PARALLEL
#define INTERIOR_REFERENCED_ROOT(_f, _t)                                \
  (!MULTIPLE_COMPUTE_NODE_P || !THREAD_SHADOW(_t) ||                    \
   THREAD_TYPE(_t) == THREAD_F_PERIODIC ||                              \
   THREAD_TYPE(THREAD_SHADOW(_t)) == THREAD_F_PERIODIC ||               \
   F_INTERIOR(_f, _t))

#define INTERIOR_REFERENCED(_f, _t)                                     \
  INTERIOR_REFERENCED_ROOT(_f, (NNULLP(THREAD_SUPER_THREAD(_t))?        \
                                THREAD_SUPER_THREAD(_t):(_t)))
#else /* PARALLEL */
#define INTERIOR_REFERENCED(_f, _t) (1)
#endif /* PARALLEL */
                                                                                    FLUENT_EXPORT void Mark_Faces_Referenced_By_Interior_Cells(Domain *domain);
FLUENT_EXPORT void Init_Iface_Corner_Shadow_Node_Value(Domain *domain, ...);
FLUENT_EXPORT void Set_Iface_Corner_Shadow_Node_Mark(int, Domain *);
FLUENT_EXPORT void Fill_Capillary_Pressure(Domain *PTR_RESTRICT domain);
FLUENT_EXPORT void Update_Wall_Mom_Coeffs(Domain *domain);

#define F_BLENDING(x,xmin,xmax,ymin,ymax) \
  ((ymin) + ((ymax) - (ymin)) * MAX(0, MIN(1, ((x) - (xmin)) / ((xmax) - (xmin)))))

#define F_BLENDING_TANH(x,xmin,xmax,ymin,ymax) \
  ((ymin) + ((ymax) - (ymin)) * 0.5*(1+tanh(M_PI*((x)-0.5*((xmax)+(xmin)))/((xmax)-(xmin)))))

#define F_BLENDING_SINE(x,xmin,xmax,ymin,ymax)\
  ( ((x) < (xmin)) ? (ymin) :  ( ((x) > (xmax)) ? (ymax) : ((ymin) + ((ymax)-(ymin))*0.5*(1+sin(M_PI*((x)-((xmax)+(xmin))/2.)/((xmax)-(xmin)))))))

#endif /* _FLUENT_FLOW_H */
