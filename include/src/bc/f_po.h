/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_F_PO_H
#define _FLUENT_F_PO_H

#include "dll.h"

/* pressure outlet */

typedef struct open_channel_po_struct
{
  int outlet_number;
  int press_spec, phase_spec;
  int den_spec;
  Profile ht_local, ht_bottom;
  real fs_level, btm_level;
  real Fr, fs_level_num;
  int outlet_min, outlet_max;
  real NV_VEC(g), gmag;
} Open_Channel_po;

typedef struct
{
  cxboolean avg_press_spec;
  cxboolean prof_radial;
  int avg_option;
  int *bin;
  int nbins;
  int nelements;
} avg_p;

enum
{
  TOTAL_PRESSURE = 0,
  STATIC_PRESSURE = 1
};

struct tv_po_struct
{
  STD_FLOW_BOUNDARY_BCS;
  Profile T0;   /*don't move backflow total temperature */

  int press_spec_gen;  /* pressure specification method, so far for VOF */
  Profile p;      /* static pressure */
  real multiplier;    /* scaling multiplier */
  cxboolean build_artificial_wall; /* to prevent reverse flow */
  cxboolean radialp;    /* radial equilibrium pressure */
  cxboolean backflowp;    /* resist backflow */

  Profile ni, nj, nk; /* flow direction */
#if RP_3D
  cxboolean cylindricalp;   /* r,theta,z direction specification? */
  cxboolean localcylindricalp;  /* local r,theta,z direction specification? */
  real NV_VEC(axis);    /* local cylindrical coordinate axis */
  real NV_VEC(origin);    /* local cylindrical coordinate origin */
#endif
  icing_outlet icingp;
  /* cxboolean normalp;*/ /*inlet velocity direction is normal to boundary. */
  int dir_spec ; /* 0=direction vectors 1=normal to boundary 2=from neighboring cells*/

  cxboolean user_values_p;        /* for NRBC  */

  cxboolean solar_fluxes;         /* identify surfaces with solar load  ? */
  real solar_shining_factor;    /* specify shining factor for solar load  ? */
  cxboolean mixing_plane_thread;
  int     gen_nrbc_spec;

  avg_p pavg;

  int p_backflow_spec_gen; /* 0=total pressure, 1=static pressure */
  int p_backflow_spec; /* 0=static pressure, 1=total pressure */
  cxboolean targeted_mf_boundary ;
  Profile targeted_mf;
  Profile targeted_mf_pmax;
  Profile targeted_mf_pmin;

  /* volume fraction specification method */
  int vof_spec;

  /* Open channel bc for VOF  */
  cxboolean open_channel;
  struct open_channel_po_struct oc_head;

  /* for exhaust-fan/vent */
  cxboolean fanp;
  cxboolean resistp;
  Polynomial a;           /* dp = a(V) */
  Polynomial b;         /* dp = b(V)*rho*V^2/2 */
  Profile strength;             /* to allow dp etc. to vary with time */
  cxboolean new_fan_definition;    /* TRUE => dp is difference of
                                   upstream total and downstream static
                                   pressure */

  /*wet steam model*/
  Profile relhumd; /* relative humidity */
  Profile etta   ; /* No. of droplets per unit Volume*/
  Profile betta  ; /* Mass fraction of liquid-phase (betta) */

};

FLUENT_EXPORT void thread_po_default(Domain *domain, Thread *t);
FLUENT_EXPORT void compute_radial_pressure_profile(Thread *t, int nbins, real bin_p[],
                                                   real *rmax, real *rmin, real *dp_tmfr);

FLUENT_EXPORT real adjust_pressure_from_targeted_mf_rate_1(Thread *t);
FLUENT_EXPORT real adjust_pressure_from_targeted_mf_rate_2(Thread *t);
FLUENT_EXPORT real adjust_pressure_from_targeted_mf_rate_3(Thread *t);
FLUENT_EXPORT real adjust_pressure_from_targeted_mf_rate_4(Thread *t);


#endif /* _FLUENT_F_PO_H */
