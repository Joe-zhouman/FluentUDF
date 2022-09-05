/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_F_PI_H
#define _FLUENT_F_PI_H

#include "dll.h"
#include "syn_turb.h"
#include "icing_bc.h"

/* pressure inlet */

enum
{
  FL_SPEC_LOCALHT_N_VEL = 0,
  FL_SPEC_TOTALHT_N_VEL = 1,
  FL_SPEC_LOCALHT_N_TOTALHT = 2
};

typedef struct open_channel_pi_struct
{
  int inlet_number;
  int flow_spec, phase_spec, den_spec;
  Profile ht_local, ht_total, ht_bottom;
  Profile vmag;
  real fs_level, Es, btm_level;
  real Fr, fs_level_num;
  int inlet_min, inlet_max;
  real NV_VEC(g), gmag;
} Open_Channel_pi;


struct tv_pi_struct
{
  STD_FLOW_BOUNDARY_BCS;
  Profile T0;      /*don't move upstream stagnation temperature*/

  /* specified common quantities */
  Profile p0;     /* upstream stagnation pressure */
  Profile ni, nj, nk; /* flow direction */
  Profile p;      /* inlet pressure (supersonic) */


#if 0
  cxboolean relative_pr ; /* is velocity relative to rot. frame for pressure-for eulerian model? */
#endif

#if RP_3D
  cxboolean cylindricalp;         /* r,theta,z direction specification? */
  cxboolean localcylindricalp;  /* local r,theta,z direction specification? */
  cxboolean swirlvelp;          /* Only swirl comp. magninude specification, Turbo specific*/
  real NV_VEC(axis);    /* local cylindrical coordinate axis */
  real NV_VEC(origin);    /* local cylindrical coordinate origin */
#endif
  /* normalp: inlet velocity direction is normal to boundary. */
  cxboolean normalp;
  cxboolean solar_fluxes;         /* identify surfaces with solar load  ? */
  real solar_shining_factor;    /* specify shining factor with solar load  ? */
  cxboolean mixing_plane_thread;
  cxboolean build_artificial_wall;

  /*  Open channel struct for VOF */
  cxboolean open_channel;
  struct open_channel_pi_struct oc_head;

  /* for intake-fan/vent */
  cxboolean fanp;
  cxboolean resistp;
  Polynomial a;           /* dp = a(V) */
  Polynomial b;         /* dp = b(V)*rho*V^2/2 */
  Profile strength;             /* to allow dp etc. to vary with time */
  cxboolean new_fan_definition;    /* TRUE => dp is difference of
                                   upstream total and downstream static
                                   pressure */
#if RP_3D
  cxboolean swirlp;
  real swirl_factor;
  real fan_omega;
  real NV_VEC(fan_origin);
#endif
  icing_inlet icingp;

  /*wet steam model*/
  Profile relhumd; /* relative humidity */
  Profile etta   ; /* No. of droplets per unit Volume*/
  Profile betta  ; /* Mass fraction of liquid-phase (betta) */

  cxboolean user_values_p;

  /* Les inlet specification method */
  LES_Spec_Type les_spec;

  /* Synthetic turbulence */
  syn_turb_spectral_synthesizer_type syn_turb_spectral_synthesizer;
#if RP_3D
  syn_turb_synthetic_turbulence_generator_type syn_turb_synthetic_turbulence_generator;
  syn_turb_vortex_method_type syn_turb_vortex_method;
#endif
};

FLUENT_EXPORT void thread_pi_default(Domain *domain, Thread *t);
FLUENT_EXPORT real Get_T_from_T0P0P(cell_t c, Thread *t, Material *m0, real r, real Cp, real T0, real Tsmin, real p0, real p, real yi[]);
FLUENT_EXPORT void Update_Heat_Flux_Storage(Thread *thread, face_t f, real flux_w, real flux_g,
                                            real H, real p, real T, real epsilonw, double Tbb, cxboolean Tbb_spec);
FLUENT_EXPORT void Calc_flow_dir(face_t f, Thread *t, cxboolean normalp,
                                 Profile *ni, Profile *nj, Profile *nk, real ev[3]
#if RP_3D
                                 , cxboolean cylindricalp, cxboolean swirlvelp, real rad_vel, real ax_vel
                                 , real NV_VEC(axis), real NV_VEC(origin)
#endif
                                );

#define FAN_BACKFLOW_KL 1.0 /* inlet fan is modeled as a vent with this
             loss coefficient in case of backflow */

#endif /* _FLUENT_F_PI_H */

