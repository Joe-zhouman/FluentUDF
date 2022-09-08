/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_UDF_UTIL_H
#define _FLUENT_UDF_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dll.h"
#include "prop.h"
#include "profile.h"
#include "slide.h"
#include "threads.h"
#include "para.h"
#include "dpm.h"
#include "dpm_tools.h"
#include "dpm_dem_wall.h"
#include "binary_params.h"

typedef struct udf_utility_struct
{
  int     (*fl_udf_initialize)(Domain *);
  int     (*fl_udf_uninitialize)(Domain *);

  void    (*fl_uds_inquire_eqns)(char *, int, char *, char *);
  cxboolean (*fl_uds_solid_solve_p)(int, cxboolean *);
  void    (*fl_uds_rgrad_accumulate)(Thread *, Svar, int, Svar);
  void    (*fl_uds_deriv_accumulate)(Thread *, Svar, int, Svar, Svar);
  real    (*fl_uds_contact_resistance)(face_t, Thread *, int);
  real    (*fl_uds_contact_jump)(face_t, Thread *, int);
  void    (*fl_uds_compute_coeffs)(Domain *, int);
  void    (*fl_uds_post_solve_update)(Domain *, int);

  real    (*fl_udf_thermal_ctk)(face_t, Thread *);
  void    (*fl_udf_non_reflecting_bc)(Domain *, int);

  void    (*fl_dpm_pre_solve_update)(Domain *, cxboolean);
  void    (*fl_dpm_post_solve_update)(Domain *, cxboolean);
  void    (*fl_dpm_interp_state)(CX_Cell_Id *, real [], cphase_state_t *, cxboolean, void *);
  void    (*fl_dpm_interp_velocity)(CX_Cell_Id *, real [], real [], int);
  void    (*fl_dpm_interp_post_command)(Tracked_Particle *tp);
  void    (*fl_dpm_particle_fate)(Tracked_Particle *tp);
  void    (*fl_dpm_particle_acceleration)(Tracked_Particle *, real [], real [], real *, cxboolean);
  cxboolean (*fl_ddpm_solve_eulerian)(cell_t, Thread *, Tracked_Particle *, int);

  void    (*fl_dpm_cm_pre)(Domain *);
  void    (*fl_dpm_cm_pre_particle_particle)(Particle *, Particle *);
  void    (*fl_dpm_cm_pre_particle_wall)(Particle *, dpm_collision_face_t *);

  void    (*fl_dpm_cm_post_particle_particle)(Particle *, Particle *);
  void    (*fl_dpm_cm_post_particle_wall)(Particle *, dpm_collision_face_t *);
  void    (*fl_dpm_cm_post)(Domain *);

  void    (*fl_dpm_cm_add_particle_particle_force)(Particle *pi, Particle *pj, dpm_interaction_param_t *param, int current_stage,
                                                   real pair_collision_force[], real collision_torque_pi[], real collision_torque_pj[],
                                                   real overlap, real dr[]);
  void    (*fl_dpm_cm_add_particle_wall_force)(Particle *pi, dpm_collision_face_t *face_data, dpm_interaction_param_t *param, int current_stage,
                                               real pair_collision_force[], real collision_torque_pi[],
                                               real overlap, real force_dir[]);
  void    (*fl_dpm_madabhushi_lc_extension)(Tracked_Particle *);
  void    (*fl_dpm_particle_body_force)(Tracked_Particle *, real acceleration[]);

}
UDF_Utilities;

extern FLUENT_EXPORT UDF_Utilities *udf_util_fcns;

#define UDF_METHOD(r,m)(r->m)
#define UDF_METHOD_AVAILABLE_P(r,m)(NNULLP(r) && NNULLP(UDF_METHOD(r,m)))

#ifdef __cplusplus
}
#endif

#endif /* _FLUENT_UDF_UTIL_H */
