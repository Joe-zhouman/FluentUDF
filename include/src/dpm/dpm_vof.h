/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef FLUENT_DPM_VOF_H
#define FLUENT_DPM_VOF_H

#include "global.h"
#include "mem.h"
#include "prop.h"
#include "profile.h"
#include "slide.h"
#include "threads.h"
#include "dpm.h"
#include "dpm_types.h"
/*#include "dpm_laws.h"*/
#include "dpm_dist.h"
#include "flowf.h"

#define DPM_REAL_DIM   1
#define DPM_VECTOR_DIM 3

#define DPM_VOF_DIM   DPM_REAL_DIM
#define DPM_WT_DIM    DPM_REAL_DIM
#define DPM_VEL_DIM   DPM_VECTOR_DIM
#define DPM_DIAM_DIM  DPM_REAL_DIM
#define DPM_RHO_DIM   DPM_REAL_DIM
#define DPM_TEMP_DIM  DPM_REAL_DIM
#define DPM_K_DIM     DPM_REAL_DIM
#define DPM_HC_DIM    DPM_REAL_DIM

/* big values, see also sg_mphase.h */
#if RP_DOUBLE                /*single-double precision zero and epsilon*/
# define DPM_NEG_BIG -1.e+30
# define DPM_BIG 1.e+30
#else
# define DPM_NEG_BIG -1.e+20
#if (sys_ultra || sys_ultra_64)
# define DPM_BIG 1.e+17
#else
# define DPM_BIG 1.e+20
#endif
#endif

typedef enum call_spec_e
{
  INSIDE_TRACKING,
  AFTER_AVERAGING,
  CALL_SPEC_MAX
}
DPM_Vof_Call_Spec;

/* Averaging methods for primary and derived variables */
enum
{
  ENSEMBLE_AVRG = 0,
  CALORIC_AVRG,
  MAX_AVRG
};

enum
{
  STANDARD = 0,   /* uses total phase volume fraction and particle diameter for IA */
  PSEUDO_PHASE,   /* uses parcel volume fraction and related particle diameter for IA */
  DERIVED_DIAM,   /* uses total phase volume fraction and derived phase-diameter for IA... 
                   * ..Phase-diameter weighted by the exchange relevant driving force. 
                   * IA: Interfacial Area relevant for the exchange. */
  MAX_METHOD
};

FLUENT_EXPORT void Setup_DPM_Vof(cxboolean);
FLUENT_EXPORT void Setup_Exchange_Coefficients(cxboolean);
FLUENT_EXPORT void Setup_DDPM_Velocity_Correction(void);
FLUENT_EXPORT void Setup_DPM_Vof_Distributions_on_Nodes(cxboolean);
FLUENT_EXPORT void Setup_Exchange_Coefficients_on_Nodes(cxboolean);
FLUENT_EXPORT void Setup_VOF_Shared_Classification(void);
FLUENT_EXPORT void Distribute_Exchange_Coefficients_from_Nodes_to_Cells(void);
FLUENT_EXPORT void Distribute_DPM_Vof_Dist_from_Nodes_to_Cells(void);

FLUENT_EXPORT void DPM_Fix_SVar(Domain *domain, int eqn, Svar sv_v, Svar sv_ap, int amg_id);
FLUENT_EXPORT void DPM_Fix_SVar_On_Thread(Thread *thread, int eqn, Svar sv_v, Svar sv_ap, int amg_id);
FLUENT_EXPORT void DPM_Correct_Coupled_AP_Coefficient(Domain *domain);
FLUENT_EXPORT void Fill_Discrete_Phase_Diameter(Thread *pt);
FLUENT_EXPORT void Fill_Discrete_Phase_Slip_Velocity(Domain *domain, Thread *t, int disPhase);
FLUENT_EXPORT real DPM_Unlimited_Vof(cell_t c, Thread *t, DPM_Vof_Call_Spec call_spec);
FLUENT_EXPORT real DPM_Averaged_Density(cell_t c, Thread *t);
FLUENT_EXPORT real DPM_Averaged_Drag(cell_t c, Thread *ti, Thread *tj, Thread *t, int i, int j, Phase_Pair *phase_pair);
FLUENT_EXPORT void DPM_Dist_Velocity(cell_t c, Thread *t, real v[ND_3]);
FLUENT_EXPORT real DPM_Momentum_AP(cell_t c, Thread *t);
FLUENT_EXPORT real DPM_Averaged_Heat_Coeff(cell_t c, Thread *ti, Thread *tj);
FLUENT_EXPORT void DPM_Averaged_Granular_Temperature(Domain *d);
FLUENT_EXPORT real DDPM_Specific_Heat(cell_t c, Thread *t);
FLUENT_EXPORT real DDPM_Enthalpy(cell_t c, Thread *t);
FLUENT_EXPORT void DDPM_Boundary_Velocity(real V[DPM_VEL_DIM], face_t f, Thread *t);
FLUENT_EXPORT real DDPM_Boundary_Vof(face_t f, Thread *t);
FLUENT_EXPORT real DDPM_Boundary_Temp(face_t f, Thread *t);
FLUENT_EXPORT real DDPM_Boundary_Rho(face_t f, Thread *t);
FLUENT_EXPORT void DDPM_Calc_Flow_Dir(real *e_n, face_t f, Thread *t);
FLUENT_EXPORT real DDPM_Inflow_Flux(Domain *domain);
FLUENT_EXPORT void DDPM_Flux_Reset(void);
FLUENT_EXPORT void DDPM_Flux_Report(Thread *thread, real integral[]);
FLUENT_EXPORT cxboolean Is_Inflow_Boundary_Thread(Thread *t);
FLUENT_EXPORT cxboolean Is_Outflow_Boundary_Thread(Thread *t);
FLUENT_EXPORT void Add_To_DDPM_Flux_Report(Tracked_Particle *tp, Thread *t, Accum_Cmd_Spec accum_cmd);
FLUENT_EXPORT void Limit_Dense_DPM_Properties(Domain *domain);
FLUENT_EXPORT void Init_Solve_Eulerian_Flag(void);
FLUENT_EXPORT void Free_Solve_Eulerian_Flag(void);
FLUENT_EXPORT void Update_Solve_Eulerian_Flag(Domain *domain);
FLUENT_EXPORT cxboolean Hybrid_Phase_Domains_Present(void);

#if RP_NODE
FLUENT_EXPORT void DPM_Vof_Sync_Exch_Coeffs(Domain *domain, int eqn);
#endif

#define C_SOLVE_EULERIAN_BIT_SET(c,t)C_STORAGE_BIT_SET(c,t,SV_DPM_SOLVE_EULERIAN)
#define C_SOLVE_EULERIAN_BIT_CLEAR(c,t)C_STORAGE_BIT_CLEAR(c,t,SV_DPM_SOLVE_EULERIAN)
#define C_SOLVE_EULERIAN_BIT(c,t)C_STORAGE_BIT_GET(c,t,SV_DPM_SOLVE_EULERIAN)

FLUENT_EXPORT real injected_ddpm_granular_mass_for_time_step[MAX_PHASES];

typedef struct dpm_vof_and_postproc_struct
{
  Dpm_Distribution vof_dist;
  DPM_Dist_Var vof;
  DPM_Dist_Var vel;
  DPM_Dist_Var diam;
  DPM_Dist_Var rho;
  DPM_Dist_Var temp;
  DPM_Dist_Var cp;
  DPM_Dist_Var h;
  DPM_Dist_Var n_part_caloric;
  DPM_Dist_Var np_temp_weight;
  DPM_Dist_Var diam_thermal;
  DPM_Dist_Var gr_temp;
  DPM_Dist_Var number_density;
  DPM_Dist_Var nparcel;
  DPM_Dist_Var d20;
  DPM_Dist_Var d30;
  DPM_Dist_Var d32;
  DPM_Dist_Var d43;
  DPM_Dist_Var species_mean;
  DPM_Dist_Var vel_sqr;
  DPM_Dist_Var temp_sqr;
  DPM_Dist_Var diam_sqr;
} DPM_Vof_and_Postproc_s;

FLUENT_EXPORT DPM_Vof_and_Postproc_s *Get_DPM_Postproc_Struct(void);

typedef struct ddpm_exchange_coeffs_struct
{
  Dpm_Distribution exch_coeff_dist;
  DPM_Dist_Var Kdpm;
  DPM_Dist_Var HeatCoeff;
} DDPM_Exchange_Coeffs_s;

FLUENT_EXPORT DDPM_Exchange_Coeffs_s *Get_DDPM_Exchange_Struct(void);

FLUENT_EXPORT double cell_euler_ddpm_prop(cell_t c, Thread *t, double prop);

#endif /* FLUENT_DPM_VOF_H */
