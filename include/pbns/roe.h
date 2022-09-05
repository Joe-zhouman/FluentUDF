/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/
/**
 * Implementation of Roe and AUSM flux formulations for
 * the pressure based algorithm.
 * Replaces an earlier formulation for the Roe flux, done by Sanjay.
 * This can be found can be found in svn revisions prior to r906695,
 * or earlier than 8/12/2016. Best readability is given in fluent v5.
 */
#ifndef _FLUENT_RHOE_H
#define _FLUENT_RHOE_H

typedef enum
{
  FLUX_RC = 0,
  FLUX_ROE,
  FLUX_AUSM
} Flux_Type;

typedef enum
{
  FR_SO = 0,
  FR_ROE
} Face_Recon;

struct pressure_velocity_discretization_controls_struct
{
  Flux_Type flux_t;
  Face_Recon recon_t;
  cxboolean include_kp_u;
  cxboolean fp_correct;
  cxboolean convert_to_relative;
};
typedef struct pressure_velocity_discretization_controls_struct PVDC;

struct pressure_velocity_discretization_struct
{
  real vflux;
  real pf;

  real ku_0;
  real ku_1;
  real ku_p;

  real kp_0;
  real kp_1;
  real kp_u;

  real NV_VEC(n);
  real NV_VEC(ns);

  real min_ku_p;
  real min_kp_u;
};
typedef struct pressure_velocity_discretization_struct PVD;

extern FLUENT_EXPORT PVDC pvdc;
extern FLUENT_EXPORT PVD pvd;

extern FLUENT_EXPORT void roe_flux
(Thread *t, face_t f, Thread *t0, cell_t c0, Thread *t1, cell_t c1,
 real rho_f, cxboolean high_order_rc_scheme, PVD *pvd);
extern FLUENT_EXPORT void set_pvd_controls(Domain *domain);

#define CONVERT_TO_RELATIVE_INT(t0,t1)(M_abs_frame || sg_dynmesh || \
                                      THREAD_VAR(t0).fluid.mgrid.is_moving || \
                                      THREAD_VAR(t1).fluid.mgrid.is_moving)

#define CONVERT_TO_RELATIVE_BND(t)(M_abs_frame || sg_dynmesh || \
                             THREAD_VAR((t)->t0).fluid.mgrid.is_moving);



#endif /* _FLUENT_RHOE_H */
