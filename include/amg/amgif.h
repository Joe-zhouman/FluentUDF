/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_AMGIF_H
#define _FLUENT_AMGIF_H

#include "dll.h"

#include "amg.h"

#define AMG_MPV AMG_PVT

extern FLUENT_EXPORT Level fine[AMG_MAX_SYSTEMS];

#define AMG_SIZE      fine[AMG_SCALAR].A.tot_size
#define AMG_D(i)      fine[AMG_SCALAR].A.d[i]
#define AMG_X(i)      fine[AMG_SCALAR].x[i]
#define AMG_B(i)      fine[AMG_SCALAR].b[i]
#define AMG_CHILD(i)      fine[AMG_SCALAR].child[i]
#define AMG_ROW(i)      fine[AMG_SCALAR].A.row[i]
#define AMG_COL(i)      fine[AMG_SCALAR].A.col[i]
#define AMG_OD(i)     fine[AMG_SCALAR].A.value[i]
#define AMG_ROW_OD_LOOP(i, ip, j) \
  for (ip = AMG_ROW(i), j = AMG_COL(ip); \
       ip < AMG_ROW(i + 1); \
       ++ip, j = AMG_COL(ip))
#define AMG_ZERO_OD(i)      \
  { \
      int ip; \
      for (ip = AMG_ROW(i); ip < AMG_ROW(i + 1); ++ip) \
  AMG_OD(ip) = 0.; \
  }

#if OVERSET_NUMERICS
#define OMG_D(i)      fine[AMG_SCALAR].C.d[i]
#define OMG_ROW(i)      fine[AMG_SCALAR].C.row[i]
#define OMG_COL(i)      fine[AMG_SCALAR].C.col[i]
#define OMG_OD(i)     fine[AMG_SCALAR].C.value[i]
#define OMG_WORK(i)     fine[AMG_SCALAR].A.work[i]
#endif

#define SAMG_SIZE(id)     fine[id].A.tot_size
#define SAMG_NCOEFFS(id)    fine[id].A.n_coeffs
#define SAMG_BLK_SIZE(id)   fine[id].A.n_ceqn
#define SAMG_D(id,i)      fine[id].A.d[i]
#define SAMG_X(id,i)      fine[id].x[i]
#define SAMG_B(id,i)      fine[id].b[i]
#define SAMG_CHILD(id,i)    fine[id].child[i]
#define SAMG_ROW(id,i)      fine[id].A.row[i]
#define SAMG_COL(id,i)      fine[id].A.col[i]
#define SAMG_OD(id,i)     fine[id].A.value[i]
#define SAMG_ROW_OD_LOOP(id, i, ip, j)  \
  for (ip = SAMG_ROW(id, i), j = SAMG_COL(id, ip); \
       ip < SAMG_ROW(id, i + 1); \
       ++ip, j = SAMG_COL(id, ip))
#define SAMG_ZERO_OD(id, i)     \
  { \
      int ip; \
      for (ip = SAMG_ROW(id, i); ip < SAMG_ROW(id, i + 1); ++ip) \
  SAMG_OD(id, ip) = 0.; \
  }


#define BAMG_SIZE(id)   fine[id].A.tot_size
#define BAMG_NCOEFFS(id)  fine[id].A.n_coeffs
#define BAMG_BLK_SIZE(id) fine[id].A.n_ceqn
#define BAMG_ROW(id,i)    fine[id].A.row[i]
#define BAMG_CHILD(id,i)  fine[id].child[i]

#if AMG_CHUNKED_MEMORY
#define BAMG_D(id, nc)    (A_DP(fine[id].A, nc))
#define BAMG_OD(id, nc)   (A_VALUEP(fine[id].A, nc))
#else
#define BAMG_D(id, nc)    (&fine[id].A.d[SQR(BAMG_BLK_SIZE(id))*(nc)])
#define BAMG_OD(id, nc)   (&fine[id].A.value[SQR(BAMG_BLK_SIZE(id))*(nc)])
#endif

#define BAMG_X(id, nc)    (&fine[id].x[BAMG_BLK_SIZE(id)*(nc)])
#define BAMG_B(id, nc)    (&fine[id].b[BAMG_BLK_SIZE(id)*(nc)])

#define BAMG_ZERO_OD(id, nc, ie)                \
  {                                             \
    int neq = BAMG_BLK_SIZE(id);                \
    int ip0 = BAMG_ROW(id,nc);                  \
    int ip1 = BAMG_ROW(id,nc + 1);              \
    int ip;                                     \
    for (ip = ip0; ip < ip1; ++ip)              \
      {                                         \
        int je;                                 \
        real *value = A_VALUEP(fine[id].A, ip); \
        for (je = 0; je < neq; ++je)            \
          value[je + neq*ie] = 0.;              \
      }                                         \
  }

#define GET_AMG_F_COEFF_01(fcoeff,f,t,amg_id,amg_i)     \
  {                                                     \
    if (amg_id == AMG_SCALAR)                           \
      {                                                 \
        fcoeff = F_COEFF_01(f,t);                       \
      }                                                 \
    else if (amg_id == AMG_PVT)                         \
      {                                                 \
        int const i = amg_i;                            \
        fcoeff =MATRIX(F_A01(f,t),i,i,mp_n);            \
      }                                                 \
    else                                                \
      Internal_Error("unknown amg solver id");          \
  }

#define GET_AMG_F_COEFF_10(fcoeff,f,t,amg_id,amg_i)     \
  {                                                     \
    if (amg_id == AMG_SCALAR)                           \
      {                                                 \
        fcoeff =F_COEFF_10(f,t);                        \
      }                                                 \
    else if (amg_id == AMG_PVT)                         \
      {                                                 \
        int const i = amg_i;                            \
        fcoeff =MATRIX(F_A10(f,t),i,i,mp_n);            \
      }                                                 \
    else                                                \
      Internal_Error("unknown amg solver id");          \
  }

#define MULTIPLY_KE_OD(id, nc, ie, multiplicator)               \
  {                                                             \
    int neq = BAMG_BLK_SIZE(id);                                \
    int ip0   = BAMG_ROW(id,nc);                                \
    int ip1   = BAMG_ROW(id,nc + 1);                            \
    int ip;                                                     \
    for (ip = ip0; ip < ip1; ++ip)                              \
      {                                                         \
        real *value = A_VALUEP(fine[id].A, ip);                 \
        /* real *value = &fine[id].A.value[neq*neq*ip]; */      \
        value[ie + neq*ie] *= multiplicator;                    \
      }                                                         \
  }

#define AMG_MAPPING_STATUS(t, sid)          ((NNULLP(THREAD_SUPER_THREAD(t))? \
                                              THREAD_SUPER_THREAD(t):(t))-> \
                                             amg_mapping_status[sid])
#define AMG_MAPPING_STATUS_D(d, sid)        ((NNULLP(DOMAIN_SUPER_DOMAIN(d))? \
                                              DOMAIN_SUPER_DOMAIN(d):(d))-> \
                                             amg_mapping_status[sid])
#define AMG_SET_ID_EXCLUDED 0
#define AMG_SET_ID_FLUID    1
#define AMG_SET_ID_SOLID    2
#define AMG_SET_ID_MATRIX   3
#define AMG_SET_ID_SHELL    4
#define AMG_SET_ID_NETWORK  5

#define THREAD_EXCLUDED_P(t, sid)           (AMG_MAPPING_STATUS(t, sid) == AMG_SET_ID_EXCLUDED)
#define THREAD_IN_FLUID_SET_P(t, sid)       (AMG_MAPPING_STATUS(t, sid) == AMG_SET_ID_FLUID)
#define THREAD_IN_SOLID_SET_P(t, sid)       (AMG_MAPPING_STATUS(t, sid) == AMG_SET_ID_SOLID)
#define THREAD_IN_MATRIX_P(t, sid)          (AMG_MAPPING_STATUS(t, sid) == AMG_SET_ID_MATRIX)
#define THREAD_IN_SHELL_MATRIX_P(t, sid)    (AMG_MAPPING_STATUS(t, sid) == AMG_SET_ID_SHELL)
#define NETWORK_IN_MATRIX_P(d, sid)         (AMG_MAPPING_STATUS_D(d, sid) == AMG_SET_ID_NETWORK)

#define PUT_THREAD_EXCLUDED(t, sid, changed){                   \
    changed = (changed || !THREAD_EXCLUDED_P  (t, sid) ||       \
               !THREAD_EXCLUDED_P  (t, prev_sys_id));           \
    AMG_MAPPING_STATUS(t, sid) = AMG_SET_ID_EXCLUDED;}
#define PUT_THREAD_IN_FLUID_SET(t, sid, changed){               \
    changed = (changed || !THREAD_IN_FLUID_SET_P(t, sid) ||     \
               !THREAD_IN_FLUID_SET_P(t, prev_sys_id));         \
    AMG_MAPPING_STATUS(t, sid) = AMG_SET_ID_FLUID;}
#define PUT_THREAD_IN_SOLID_SET(t, sid, changed){               \
    changed = (changed || !THREAD_IN_SOLID_SET_P(t, sid) ||     \
               !THREAD_IN_SOLID_SET_P(t, prev_sys_id));         \
    AMG_MAPPING_STATUS(t, sid) = AMG_SET_ID_SOLID;}
#define PUT_THREAD_IN_MATRIX(t, sid, changed){                  \
    changed = (changed || !THREAD_IN_MATRIX_P   (t, sid) ||     \
               !THREAD_IN_MATRIX_P   (t, prev_sys_id));         \
    AMG_MAPPING_STATUS(t, sid) = AMG_SET_ID_MATRIX;}
#define PUT_THREAD_IN_SHELL_MATRIX(t, sid, changed){            \
    changed = (changed || !THREAD_IN_SHELL_MATRIX_P(t, sid) ||  \
               !THREAD_IN_SHELL_MATRIX_P   (t, prev_sys_id));   \
    AMG_MAPPING_STATUS(t, sid) = AMG_SET_ID_SHELL;}
#define PUT_NETWORK_EXCLUDED(d, sid, changed){                  \
    changed = (changed || NETWORK_IN_MATRIX_P  (d, sid) ||      \
               NETWORK_IN_MATRIX_P  (d, prev_sys_id));          \
    AMG_MAPPING_STATUS_D(d, sid) = AMG_SET_ID_EXCLUDED;}
#define PUT_NETWORK_IN_MATRIX(d, sid, changed){                 \
    changed = (changed || !NETWORK_IN_MATRIX_P  (d, sid) ||     \
               !NETWORK_IN_MATRIX_P  (d, prev_sys_id));         \
    AMG_MAPPING_STATUS_D(d, sid) = AMG_SET_ID_NETWORK;}

#define Residual_Tolerance_Iteration \
(RP_Get_Integer("nita/outer-iter") - RP_Get_Integer("nita/residual-tolerance/iter"))


FLUENT_EXPORT void Make_Fine_Level(Domain *domain, int sys_id,
                                   cxboolean compute_solid, int n_ceqn,
                                   int idx,
                                   int (*mapping)(Domain *, int,
                                                  cxboolean, int, int));

FLUENT_EXPORT void Make_Fine_Level_AWE(Domain *domain, int sys_id,
                                       cxboolean compute_solid, int n_ceqn,
                                       int idx,
                                       int (*mapping)(Domain *, int,
                                                      cxboolean, int, int));

FLUENT_EXPORT void Free_Fine_Level(Domain *domain, int sys_id);

/* the make fine level interface --- start */
FLUENT_EXPORT int makeFineLevelReuse(Level *f, const int sys_id);
FLUENT_EXPORT int makeFineLevelStart(Level *f, const int sys_id, const int n_ceqn,
                                     const int size, const int tot_size, const int n_coeffs,
                                     const int nsets, const int *sets,
                                     int **row, int **col);
FLUENT_EXPORT int makeFineLevelExchanger(Level *f, const int nNeighbors, const int *nbId,
                                         const int *intrSize, const int *extrSize,
                                         const int **intr, const int **extr);
FLUENT_EXPORT int makeFineLevelEnd(Level *f, const int sys_id);
/* the make fine level interface --- end */

FLUENT_EXPORT void Fill_AMG_Controls_Scalar(AMG_Controls *amg, char *name,
                                            real alpha, real beta, AMG_Cycle_Type type,
                                            int method, Level *f);
FLUENT_EXPORT void Fill_AMG_Controls_Block(int sys_id, AMG_Controls *amg, char *name,
                                           real alpha, real beta, AMG_Cycle_Type type,
                                           int method, Level *f);
FLUENT_EXPORT void LinearSolve(AMG_System_Type sys_id, Domain *d, int eqn,
                               Svar nv, Svar nvap, Svar nvres, char *name,
                               real alpha, real beta, AMG_Cycle_Type type,
                               int method, int stabilization,
                               real *rtrms, real *scale, int *iter,
                               void (*resfunptr)(Domain *const, Level *const, Svar, Svar, int, real *),
                               cxboolean do_residual,
                               int dbns_ntries,
                               int sub_iter,
                               int max_iter,
                               cxboolean *stop_iteration,
                               real iter_tolerance, AMG_Solver_Mode amg_solver_mode);
/* obsolete, UDF users should move to the LinearSolver() interface function */
FLUENT_EXPORT void Subiter_LinearSolve(AMG_System_Type sys_id, Domain *d, int eqn,
                                       Svar nv, Svar nvap, Svar nvres, char *name,
                                       int sub_iter, int max_iter, real iter_tolerance, real residual_tolerance,
                                       cxboolean *stop_iteration,
                                       real alpha, real beta, AMG_Cycle_Type type,
                                       int method, int stabilization,
                                       real *rtrms, real *scale, int *iter,
                                       void (*resfunptr)(Domain *const, Level *const, Svar, Svar, int, real *),
                                       cxboolean do_residual,
                                       int dbns_ntries);

FLUENT_EXPORT real Solve(int sys_id, char *name, real alpha, real beta,
                         AMG_Cycle_Type type, int method, int stabilization, real *scale, Svar var);
FLUENT_EXPORT int Block_Solve(int sys_id, char *name, real alpha, real beta,
                              AMG_Cycle_Type type, real residual[], real scale[]);
FLUENT_EXPORT void Subiteration_Solve(Domain *domain, int sub_iter, int max_iter, real iter_tolerance,
                                      real residual_tolerance, cxboolean *stop_iteration, cxboolean need_scale,
                                      int eqn, int sys_id, char *name, real alpha, real beta, AMG_Cycle_Type type,
                                      int method, int stabilization, Svar var);
FLUENT_EXPORT void AMG_Flag_Recreate_Fine_Level(cxboolean flag);
typedef enum
{
  MASS_FLOW_BASED_SCALING = 0,
  DEFECT_BASED_SCALING = 1,
  AP_BASED_SCALING = 2,
  MAX_DEFINED_RESIDUAL_METHODS
} Residual_Scaling_Method;

typedef enum
{
  SCALE_RMS = 0,
  SCALE_AVG_LOCAL = 1,
  SCALE_AVG_GLOBAL = 2
} Local_Scaling_Method;

FLUENT_EXPORT void Store_Residual(Domain *domain, Svar nv);
FLUENT_EXPORT void Store_Residual_Coupled(Domain *domain, Svar nv, int eqn);
FLUENT_EXPORT void Store_Locally_Scaled_Residuals(Domain *const, Level *const, Svar, Svar, int, int, void (*resfunptr)(Domain *, Level *, Svar, Svar, int, real *), real *const);
FLUENT_EXPORT void Calculate_Store_Continuity_Residual(Domain *const, Level *const, Svar, Svar, int, int, void (*resfunptr)(Domain *, Level *, Svar, Svar, int, real *), real *const);
FLUENT_EXPORT void Calculate_Store_Locally_Scaled_Residuals(Domain *const, Level *const, Svar, Svar, int, int, void (*resfunptr)(Domain *, Level *, Svar, Svar, int, real *), real *const);
FLUENT_EXPORT void Collect_Mdot_From_Faces(Domain *, Svar, Svar );
FLUENT_EXPORT void Collect_Mdot_From_Faces_Mixture(Domain *, Svar, Svar );
FLUENT_EXPORT void Collect_Mdot_From_Faces_Mfluid(Domain *, Svar, Svar);
FLUENT_EXPORT void Get_Linear_System_Info(Level *const, const int, const int, real *, real *, real *, real *);
FLUENT_EXPORT real Compute_Average_Phi(Domain *, Svar);
FLUENT_EXPORT cxboolean Need_Diagonal_Ap(Domain *const, Svar, Svar);
FLUENT_EXPORT real Transient_Local_Residual_Scaling_Factor(Domain *const, Svar, Svar);
FLUENT_EXPORT void Calculate_Locally_Scaled_Residuals(Domain *const, Level *const, Svar, Svar, int, int, real *, real *);


#if RP_AMG_DO
extern FLUENT_EXPORT AMG_Controls amg;
extern FLUENT_EXPORT Matrix *get_matrix(int l);
extern FLUENT_EXPORT Level *get_level(int l);
extern FLUENT_EXPORT real *get_x(int l);
extern FLUENT_EXPORT real *get_b(int l);
/* FLUENT_EXPORT void Get_Residual(Matrix A, real x[], real b[], real
 * residual[]); */
FLUENT_EXPORT void Create_Temperature_Coarse_Levels(Domain *domain, int sys_id,
                                                    real alpha, real beta, AMG_Cycle_Type type);
FLUENT_EXPORT int  Get_Coarse_Level_Indices(Domain *domain, int l);
FLUENT_EXPORT void Get_Parents(Domain *domain);
FLUENT_EXPORT void Get_Interior_Faces(Domain *domain);
FLUENT_EXPORT void Get_Boundary_Faces(Domain *domain);
#endif

FLUENT_EXPORT void Init_Protection_Status(AMG_Controls *amg);

FLUENT_EXPORT void Fill_C_Coarse_Indices(char *, int);

FLUENT_EXPORT void Fill_AMG_Export_Functions(void);

#endif /* _FLUENT_AMGIF_H */
