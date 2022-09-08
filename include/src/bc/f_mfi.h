/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */
#include "icing_bc.h"

enum
{
  RECIRCULATION_NONE = 0,
  RECIRCULATION_INLET = 1,
  RECIRCULATION_OUTLET = 2
};

enum
{
  RECIRCULATION_TEMP_RISE = 0,
  RECIRCULATION_HEAT_SOURCE = 1,
  RECIRCULATION_CONVECTION = 2
};

/* mass boundary type  (masstype) */
enum
{
  MASS_FLOW_TYPE   = 0,
  MASS_FLUX_TYPE   = 1,
  MASS_FLUXAVE_TYPE = 2,
  CORRECTED_MASS_FLOW_TYPE = 3
};

enum
{
  VEL_RATIO_TYPE  = 0,
  VOF_TYPE        = 1
};

typedef struct open_channel_mfi_struct
{
  int inlet_number;
  int phase_spec, den_spec;
  Profile ht_local, ht_bottom;
  real Fr, fs_level, fs_level_num, btm_level;
  int inlet_min, inlet_max;
  real NV_VEC(g), gmag;
} Open_Channel_mfi;

struct tv_mfi_struct
{
  STD_FLOW_BOUNDARY_BCS;
  Profile T0;     /* upstream stagnation temperature, keep it as in f_po.h */

  Profile mass_flow ;   /* inlet mass flowrate */
  Profile mass_flux ;   /* inlet mass flux */

  int  flow_spec    ;           /* 0=mass-flow 1=mass-flux  2=mass-flux & ave. mass-flux */
  real mass_flux_ave;           /* inlet average mass flux*/
  real upstream_torque;         /* upstream boundary torque for mixing plane*/
  real upstream_t_enthalpy;     /* upstream boundary total enthalpy integral for mixing plane*/

  int slip_velocity ;           /* 0=velocity-ratio 1=volume-fraction */
  Profile velocity_ratio;       /* phase to primary velocity ratio. 1=non-slip */
  Profile volume_fraction;      /* given volume fractio to calculate phase velocity */

  cxboolean normalp;    /* normal flow direction? */
  cxboolean outwardnormalp; /* outward normal flow direction? */
  Profile ni, nj, nk; /* flow direction */
  Profile p;      /* supersonic/initialization pressure */
  real ecmf_tref;
  real ecmf_pref;
  cxboolean outlet;

  cxboolean solar_fluxes;         /* identify surfaces with solar load  ? */
  real solar_shining_factor;     /* specify shining factor with solar load  ? */
  cxboolean mixing_plane_thread;

  /*  Open channel flow for VOF  */
  cxboolean open_channel;
  struct open_channel_mfi_struct oc_head;

  /*for dir spec. method */
#if RP_3D
  cxboolean cylindricalp;   /* r,theta,z direction specification? */
  cxboolean localcylindricalp;  /* local r,theta,z direction specification? */
  cxboolean swirlvelp;          /* Only swirl comp. magninude specification, Turbo specific*/
  real NV_VEC(axis);    /* local cylindrical coordinate axis */
  real NV_VEC(origin);    /* local cylindrical coordinate origin */
#endif
  icing_inlet icingp;


  cxboolean recirculation_type;
  int temp_spec;

  Profile delta_T;
  Profile heat_source;
  Polynomial hc;
  real Tinf;
  Thread *outlet_thread;
  Profile *mass_flow_multiplier;
#if RP_NETWORK
  cxboolean connected_to_network_node;
  Network_Objp *network_objp;
#endif
#if RP_3D
  cxboolean swirlp;
  real swirl_factor;
  real NV_VEC(fan_origin);
#endif

  /*wet steam model*/
  Profile relhumd; /* relative humidity */
  Profile etta   ; /* No. of droplets per unit Volume*/
  Profile betta  ; /* Mass fraction of liquid-phase (betta) */
};

void thread_mfi_default(Domain *domain, Thread *t);
cxboolean mf_direction_vector(Thread *thread, real rhou, real Gscale);

FLUENT_EXPORT real F_mfi_pi_Calc_Un(real rhoUn, face_t f, Thread *thread, Thread *t0);
FLUENT_EXPORT void F_mfi_Calc_ni(real *ni, real *rhovmag, real Un, face_t, Thread *, Thread *, cxboolean do_cyl, real *ni1);
FLUENT_EXPORT void F_Mfi_Calc_Ni_Swirlvelp(real *ni, real *en, real rhou, face_t f, Thread *thread, Thread *t0, cxboolean specified_relative, cxboolean want_relative, real *ni_spec, real *rhovmag, real *rhovmag1);
FLUENT_EXPORT void Calc_Rhovmag_BC_SpecFrame(real *ni_spec, real *en, real Un, face_t f, Thread *thread, Thread *t0, cxboolean specified_relative, real *rhovmag);
#if RP_3D
FLUENT_EXPORT void Cyl_to_Car(face_t f, Thread *thread, real *rhovel);
#endif
FLUENT_EXPORT void Calculate_Physical_MFR_From_ECMFR(Thread *thread, Material *m, real *rhou, real *wt_fact);
FLUENT_EXPORT real Abs_Total_Pressure(face_t f, Thread *thread);
