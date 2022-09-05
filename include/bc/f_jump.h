/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_F_JUMP_H
#define _FLUENT_F_JUMP_H

#include "dll.h"

/* jump (fan, radiator (heat exchanger), porous) */

#define JUMP_MAX_N 8  /* allows up to 7th order polynomials */
struct tv_jump_struct
{
  int dir;      /* (fan) flow direction (-1,0,+1) */

  /* velocity polynomials */
  Polynomial a;           /* dp = a(V) */
  Polynomial b;         /* dp = b(V)*rho*V^2/2 */
  Polynomial c;           /* dp = c(V)*mu */
  cxboolean porous_jump_turb_wall_treatment; /* enable turbulent wall treatment on porous jump? */
  Polynomial hc;    /* h = hc(V), q = h*dT */

  cxboolean Vlimit;   /* limit velocity polynomials? */
  real Vmin, Vmax;  /* range of applicability */

  cxboolean new_fan_definition;   /* TRUE => dp is difference of
                                   upstream total and downstream static
                                   pressure */
  Profile strength;             /* to allow dp etc. to vary with time */

  real T;     /* temperature */
  real q;     /* heat flux */
  real thermal_ctk;       /* thermal contact resistance */
  cxboolean use_ave_dp;   /* use an average dp for the thread? */

  cxboolean profile_dp;   /* profile specification of dp? */
  Profile dp_profile;   /* dp profile */
  cxboolean profile_vt;   /* profile specification of v_t? */
  Profile vt_profile;   /* v_t profile */
  cxboolean profile_vr;   /* profile specification of v_r? */
  Profile vr_profile;   /* v_r profile */

  cxboolean fan_p;    /* enable fan velocity model */
  real fan_vt[JUMP_MAX_N];  /* fan tangential velocity coefficients */
  int  fan_nvt;
  real fan_vr[JUMP_MAX_N];  /* fan radial velocity coefficients */
  int  fan_nvr;
  real fan_axis[3];   /* fan rotation axis vector */
  real fan_origin[3];   /* rotation axis origin */
  real fan_r_hub;   /* raduis of fan hub */
  real swirl_factor;

  int dpm_bc;                   /* DPM bc type (types defined in dpm.h) */
  int dpm_reinj_inj_id;   /* do not want to #include "dpm_types.h" here --> need to use Lookup_Injection_In_List() later on... */
  Objp *dpm_bc_collision_partner; /* DEM */
  int dpm_bc_collision_partner_index; /* DEM */
  cxboolean solar_fluxes;       /* identify surfaces with solar load  ? */
  Profile v_absp;               /* Visible Absorptivity*/
  Profile ir_absp;              /* IR Absorptivity */
  Profile v_trans;              /* Visual Transmissivity*/
  Profile ir_trans;             /* IR Transmissivity*/
  real solar_shining_factor;    /* Specify shining factor with solar load  ? */
  UDF_Thread_Data dpm_udf;                 /* UDF fcn for DPM_BC_UDF */

  /* Porous jump + contact angle treatment */
  cxboolean jump_adhesion;
  cxboolean constrained_adhesion;
  Profile *adh_angle;
  int n_adh_angle;

  int jump_bc_type;                 /*jump type of thread  0: FAN, 1: RADIATOR, 2:POROUS_JUMP*/

  int x_disp_type;              /* x displacement BC type */
  Profile x_disp_value;         /* x displacement */
  int y_disp_type;              /* y displacement BC type */
  Profile y_disp_value;         /* y displacement */
  int z_disp_type;              /* z displacement BC type */
  Profile z_disp_value;         /* z displacement */

};

enum bc_type_jump
{
  FAN_BC = 0,
  RADIATOR_BC,
  POROUS_JUMP_BC
};



FLUENT_EXPORT void Thread_Jump_Default(Domain *, Thread *);
FLUENT_EXPORT real Jump_Pressure_Jump(Thread *, real rho, real V, real mu);
FLUENT_EXPORT real Jump_Pressure_Jump_Derivative(Thread *, real rho, real V, real mu);
FLUENT_EXPORT real Jump_Heat_Transfer_Coeff(Thread *, real V);

FLUENT_EXPORT real Jump_Heat_Source(Thread *, real T, real V, real *h);
FLUENT_EXPORT cxboolean compute_fan_velocities(face_t, Thread *, real *ur, real *ut,
                                               real *r, real unit_r[], real unit_t[]);

/* exported for f_fluid */
FLUENT_EXPORT void Fluid_Jump_Reconstruct(Thread *);

FLUENT_EXPORT void Write_Fan_Profile(Thread *,
#if !RP_NODE
                                     FILE *,
#endif
                                     int nbin);

#endif /* _FLUENT_F_JUMP_H */
