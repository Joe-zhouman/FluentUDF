/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_F_PFAR_H
#define _FLUENT_F_PFAR_H

#include "dll.h"
#include "icing_bc.h"

struct tv_pfar_struct
{
  STD_FLOW_BOUNDARY_BCS;

  Profile M;      /* free-stream mach number */
  Profile p;      /* free-stream static pressure */
  Profile T;      /* free-stream static temperature */
  cxboolean non_equil_boundary;
  Profile Tve;    /* free-stream vibrational-electronic temperature */
  Profile ni, nj, nk;       /* inflow direction */
  cxboolean solar_fluxes;       /* identify surfaces with solar load  ? */
  real solar_shining_factor;    /* specify  shining factor with solar load  ? */
#if RP_3D
  cxboolean cylindricalp; /* r,theta,z direction specification? */
  cxboolean localcylindricalp;  /* local r,theta,z direction specification? */
  real NV_VEC(axis);    /* local cylindrical coordinate axis */
  real NV_VEC(origin);    /* local cylindrical coordinate origin */
#endif
  icing_inlet icingp;

#if RP_AXI
  real omega_swirl;   /* swirl velocity = omega_swirl *r */
#endif
};

FLUENT_EXPORT void thread_pfar_default(Domain *domain, Thread *t);

#endif /* _FLUENT_F_PFAR_H */
