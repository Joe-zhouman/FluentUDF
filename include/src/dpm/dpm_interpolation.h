
/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef DPM_INTERPOLATION_H
#define DPM_INTERPOLATION_H

#include "dpm.h"
#include "dpm_types.h"
#include "global.h"


/**
 * @addtogroup dpm Discrete Particle Model
 * @{
 *
 * @file
 * DPM: functions required for variable interpolation
 *
 */



typedef struct
{
  size_t offset;          /* offset in cphase_state_t */
  size_t vsize;           /* number of real values */
  Thread *thread;         /* cell thread */
  Svar svar;              /* variable */
  Svar svar2;             /* for node thread or gradient */
  SV_Dimension sv_dim;    /* dimension type */
  int *sv_comp;           /* components of svar */
} intrpl_var_def_t;

typedef struct
{
  intrpl_var_def_t *def;
  int              n;              /* number of variables used */
  int              n_allocated;    /* number of variables allocated */
  int              nsize;          /* total size of all variables */
} intrpl_vars_t;

typedef void (* intrpl_post_fn) (cell_t c, real pos[], Thread *t, char *c_ptr);

typedef struct
{
  size_t var_offset;
  Thread *thread;
  intrpl_post_fn fn;
} intrpl_post_cmd_t;

typedef struct
{
  int n;
  int n_allocated;
  intrpl_post_cmd_t *cmd;
} intrpl_post_cmds_t;

struct listStruct;

typedef struct interpolation_memory_struct
{
  struct intrpl_nodal_t          /* nodal interpolation data */
  {
    intrpl_vars_t var;           /* intrpl vars corresponding to the current timestep */

    /* keeping these separate will make the code easier to read */
    real (*pt_vars);             /* variables: velocity, ... at interpolation points (current timestep) */
    real (*pt_vars_previous);    /* variables: velocity, ... at previous flow solver timestep */

    int    n_pts;                /* number of interpolation points */
    int    n_pts_alloc;          /* allocated size of interpolation vector */
    real (*pts)[ND_ND];          /* coordinates of interpolation points */
    dpm_intrpl_nvars_t *gl_intrpl_nvars; /* global nodal variables */
  } nodal;

  real  *ivar;                   /* interpolated variables, used for nodal and cloud */
  int    ivar_n;
  int    ivar_n_alloc;

  intrpl_vars_t grad;            /* gradient interpolation data */

  intrpl_vars_t cell;            /* data copied from cell */
  intrpl_vars_t cell_pos;        /* data copied from cell each step*/

  intrpl_post_cmds_t post_cmds;
  intrpl_post_cmds_t post_cmds_pos;

  Svar current_svar;
  Thread *current_thread;
  Thread *current_film_thread;
  cell_t  current_cell;
  Injection *current_injection;

  cxboolean cloud;
  cxboolean only_collect_vars;

  struct listStruct *cell_list;

} intrpl_t;

typedef enum
{
  MID_EDGE_NODE,
  MID_FACE_NODE,
  PARENT_NODE
} Dpm_Node_Type;


/* nodal interpolation macros */
#define DPM_SVAR_NODE(_nv) (dpm_par.svar_iv_index[(int) (_nv)] < 0 ? SV_NULL : dpm_par.interp_vars_node[dpm_par.svar_iv_index[(int) (_nv)]])

/* svars at current timestep */
#define SV_DPM_NODE_BASE(_sv_node_dpm)      ((Svar)((_sv_node_dpm) - (SV_P_DPM_N - SV_P)))
#define SV_DPM_NODE(_sv_var)                ((Svar)((_sv_var)      + (SV_P_DPM_N - SV_P)))

/* gradients of svars at current timestep */
#define SV_DPM_NODE_BASE_GRAD(_sv_node_dpm) ((Svar)((_sv_node_dpm) - (SV_P_G_DPM_N - SV_P_G)))
#define SV_DPM_NODE_GRAD(_sv_var)           ((Svar)((_sv_var)      + (SV_P_G_DPM_N - SV_P_G)))

/* svars at previous timestep (not compatible with gradients) */
#define SV_DPM_NODE_M1(_sv_var)             ((Svar)((_sv_var)      + (SV_P_DPM_NM1 - SV_P)))
#define SV_DPM_CELL_M1(_sv_var)             ((Svar)((_sv_var)      + (SV_U_M1 - SV_U)))

/* dpm_par.unsteady_tracking is modified temporarily when tracking pathlines; therefore, we
 * need this check to avoid pathlines using m1 values. */
#define TRANS_INTRPL_ACTIVE() (dpm_par.variable_interpolate_in_time && dpm_par.unsteady_tracking)


/*
 * functions used outside of dpm_interpolation.c
 */
FLUENT_EXPORT void Get_VelDiff_TrackFrame_ContPhaseFrame(cell_t c, Thread *t, real given_pos[], real vel_diff[]);

FLUENT_EXPORT void calcInterpFactors(Tracked_Particle *tp, real *pos);
FLUENT_EXPORT void Update_Subtet(Tracked_Particle *tp);

FLUENT_EXPORT void SV_InterpVelocity(CX_Cell_Id *c, real pos[], real V[], int velocity_domain_id, void *v_intrpl, Injection *I);
FLUENT_EXPORT void SV_InterpT(CX_Cell_Id *c, real pos[], real *T, int temperature_domain_index, void *v_intrpl, Injection *I);
FLUENT_EXPORT void SV_InterpState(CX_Cell_Id *cxcell, real pos[], cphase_state_t *cphase,
                                  cxboolean do_cloud, void *cell_list, Domain *dpm_phase_domain,
                                  cxboolean stochastic_on, int particle_type, void *v_intrpl, int cphase_domain_idx, int in_mixture,
                                  Injection *I);

FLUENT_EXPORT struct interpolation_memory_struct *DPM_Interpolate_Alloc(void);
FLUENT_EXPORT void  DPM_Interpolate_Free(struct interpolation_memory_struct **);
FLUENT_EXPORT void  DPM_Interpolate_State(Tracked_Particle *tp);
FLUENT_EXPORT void  DPM_Interpolate_Set_Parameters(void);
FLUENT_EXPORT void  DPM_Interpolate_Set_Pathline_Parameters(Injection *I);
FLUENT_EXPORT void  DPM_Interpolate_Parameters_Changed(void);

FLUENT_EXPORT void  Calculate_Node_Normals(Domain *domain, const cxboolean use_m1_variable);
FLUENT_EXPORT void  Correct_NCI_Node_Velocities(Domain *domain, const cxboolean use_m1_variable, dpm_intrpl_nvars_t *gl_intrpl_nvars);
FLUENT_EXPORT void  Correct_Orphan_Contact_Or_Gap_Node_Velocities(Domain *domain, const cxboolean use_m1_variable, dpm_intrpl_nvars_t *gl_intrpl_nvars);
FLUENT_EXPORT void  Correct_Wall_Node_Velocities(Domain *domain, const cxboolean use_m1_variable, dpm_intrpl_nvars_t *gl_intrpl_nvars);

FLUENT_EXPORT real PDFT_kinetic_energy(Particle *p);
FLUENT_EXPORT real eval_scalar(float field[], float int_fact[], int n_verts);

FLUENT_EXPORT cxboolean correct_nci_values(const Thread *t);
FLUENT_EXPORT cxboolean correct_boundary_values(const Thread *t);
FLUENT_EXPORT cxboolean is_vel_component(const Svar var);
FLUENT_EXPORT cxboolean use_face_svar_values_p(const Svar sv, const Thread *tf, const cxboolean correctFaceValues);
FLUENT_EXPORT int DPM_Interpolate_UDM_from_Nodes(struct tracked_particle_struct *tp, int n_comp_selected, int *components);

FLUENT_EXPORT void DPM_Set_Turb_KE(Domain *domain);
FLUENT_EXPORT void DPM_Set_PDF_Species(Domain *domain);
FLUENT_EXPORT void DPM_Set_Strain_Rate_Magnitude(Domain *domain);
FLUENT_EXPORT SV_Store_Type store_dpm_turb(Thread *PTR_RESTRICT t, Svar nv);
FLUENT_EXPORT SV_Store_Type store_dpm_pdf_species(Thread *PTR_RESTRICT t, Svar nv);
FLUENT_EXPORT SV_Store_Type store_dpm_strain_rate_mag(Thread *PTR_RESTRICT t, Svar nv);
FLUENT_EXPORT real *weight_cell_vars_to_vec(cell_t c, Thread *t, Svar sv, SV_Dimension sv_dim, size_t vsize, int *sv_comp, double w, real *ivar);

/* @} dpm */

#endif   /* #ifndef DPM_INTERPOLATION_H */
