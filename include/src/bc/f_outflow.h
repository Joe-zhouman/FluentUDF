/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_F_OUTFLOW_H
#define _FLUENT_F_OUTFLOW_H

#include "dll.h"

struct tv_outflow_struct
{
  STD_FLOW_BOUNDARY_BCS;

  real flowrate_weight;       /* specified relative weighting of
             * total inflow to be directed
             * out of this thread            */

  real specified_flowrate;    /* flowrate to be directed
             * out of this thread, computed as a
             * normalized fraction of 'inlet_flux_sum'
             */

  /* local variables */
  real flow_rate;               /* current flow rate through this thread   */
  real rho_area_sum;            /* sum of rho*area over all the faces      */
  cxboolean solar_fluxes;         /* identify surfaces with solar load  ? */
  real  solar_shining_factor;   /* specify shining factor with solar load  ? */
  cxboolean radiating_s2s_surface;  /* identify s2s radiating surface  ?  */
};

extern FLUENT_EXPORT real inlet_flux_sum;

FLUENT_EXPORT void thread_outflow_default(Domain *domain, Thread *t);
FLUENT_EXPORT void Set_Specified_Outflow_Split(Domain *);

#endif /* _FLUENT_F_OUTFLOW_H */
