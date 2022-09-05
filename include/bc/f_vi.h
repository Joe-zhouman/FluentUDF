/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_F_VI_H
#define _FLUENT_F_VI_H

#include "dll.h"
#include "syn_turb.h"
#include "icing_bc.h"

#define MAX_RFG_MODES 400
#define MAX_N_VORTEX 600

enum
{
  VEL_SPEC_MAG_N_DIR = 0,
  VEL_SPEC_COMPONENTS = 1,
  VEL_SPEC_MAG_N_NORML = 2
};

/* Open Channel Wave inlet for VOF  */
enum
{
  AVG_VEL_MAG_N_DIR = 0,
  AVG_VEL_MAG_N_NORMAL = 1,
  AVG_VEL_COMPONENTS = 2
};

enum
{
  WAVE_REF_DIR_DEFAULT = 0,
  WAVE_REF_DIR_VECTOR = 1,
  WAVE_REF_DIR_NORMAL = 2
};

enum
{
  WIND_VEL_MAG_N_DIR    = 0,
  WIND_VEL_MAG_N_NORMAL = 1,
  WIND_LAW_MAG_N_DIR    = 2,
  WIND_LAW_MAG_N_NORMAL = 3
};

typedef struct oc_wave_group_struct
{
  /* main variables */
  int wave_theory;
  Profile wave_height;
  Profile wave_length;
  Profile phase_diff;
  Profile heading_angle;

  /* derived varibles */
  int theory;
  cxboolean short_gravity;
  cxboolean linear_wave;
  cxboolean stokes_wave;
  real wave_ht, amp, lambda, pdiff, angle;
  real k, ak, omega, wc, wc_vel;
  real A11, A22, A33, A44, A55;
  real A31, A42, A51, A53;
  real B22, B33, B44, B55;
  real B31, B42, B51, B53;
} oc_wave_group;

typedef struct oc_wave_shallow_struct
{
  /* main variables */
  int wave_theory;
  Profile wave_height;
  Profile wave_length;
  Profile offset;
  Profile heading_angle;

  /* derived varibles */
  real wave_ht, lambda, x0, angle;
  real k, wc, omega;
  real del, m_stored, m, ht_trough;
  real phi[6][6][6];
} oc_wave_shallow;

typedef struct oc_wave_spectrum_struct
{
  /* main variables */
  int method_freq;
  real gamma;
  Profile wave_height;
  Profile omega_peak;
  Profile omega_max;
  Profile omega_min;
  int n_components;
  int method_dir;
  Profile angle_mean;
  Profile deviation;
  int n_angles;
  int s;

  /* derived varibles */
  real Hs, omega_p, omega_i, omega_diff;
  real angle_p, angle_min, angle_diff;
  int n_phase_diffs;
  real *phase_diff;
  real A, B, A_gamma;
  real beta, G0;
  cxboolean short_gravity;
  int freq_integral_m;
  int dir_integral_m;
} oc_wave_spectrum;


typedef struct open_channel_wave_struct
{
  /*  Wave BC varible for VOF */
  Profile ht_local, ht_bottom;
  real ht_liquid;
  real fs_level, btm_level;
  int wave_bc_type;
  int wave_modeling_type;
  int phase_spec;
  int flow_avg_vel_spec, wave_ref_dir_spec;
  Profile vmag_avg, u_avg, v_avg, w_avg;
  Profile ni_ref, nj_ref, nk_ref;

  cxboolean vel_segregated;
  int ship_vel_spec, current_vel_spec;
  Profile vmag_ship, vmag_current;
  Profile ni_ship, nj_ship, nk_ship;
  Profile ni_current, nj_current, nk_current;
  int wind_vel_spec;
  Profile vmag_wind, vmag_wind_ref;
  Profile ni_wind, nj_wind, nk_wind;
  real wind_power_coeff, wind_ref_ht;
  real buffer_layer_ht;

  int n_waves;
  int n_waves_shallow;
  real NV_VEC(g), gmag;
  cxboolean fenton_stokes_form;
  struct oc_wave_group_struct *wave_group;
  struct oc_wave_shallow_struct *wave_shallow;
  struct oc_wave_spectrum_struct wave_spectrum;
} Open_Channel_Wave;

struct tv_vi_struct
{
  STD_FLOW_BOUNDARY_BCS;

  /* Les inlet specification method */
  LES_Spec_Type les_spec;

  /* Synthetic turbulence */
  syn_turb_spectral_synthesizer_type syn_turb_spectral_synthesizer;
#if RP_3D
  syn_turb_synthetic_turbulence_generator_type syn_turb_synthetic_turbulence_generator;
  syn_turb_vortex_method_type syn_turb_vortex_method;
#endif

  /*  Wave BC struct for VOF */
  cxboolean open_channel_wave_bc;
  struct open_channel_wave_struct oc_head;

  int velocity_spec;
  Profile vmag;
#if RP_3D
  cxboolean cylindricalp;   /* r,theta,z direction specification? */
  cxboolean localcylindricalp;  /* local r,theta,z direction specification? */
  real NV_VEC(axis);    /* local cylindrical coordinate axis */
  real NV_VEC(origin);    /* local cylindrical coordinate origin */
#endif
  Profile u, v, w;              /* inlet velocity */
  Profile ni, nj, nk;
  real omega_swirl;   /* used to compute (Omega X r), the
         * "solid body rotation" contribution to
         * tangential (swirl) velocity */

  cxboolean solar_fluxes;         /* identify surfaces with solar load  ? */
  real solar_shining_factor;     /* specify shining factor with solar load  ? */
  cxboolean mixing_plane_thread;
  icing_inlet icingp;

#if RP_NETWORK
  cxboolean connected_to_network_node;
  Network_Objp *network_objp;
#endif
  Profile T;      /* temperature */
  cxboolean non_equil_boundary;
  Profile Tve;    /* vibrational-electronic temperature */
  Profile p;      /* outflow static pressure */
  Profile p_sup;                /*bhaskar : supersonic pressure*/
};

FLUENT_EXPORT void thread_vi_default(Domain *, Thread *);
FLUENT_EXPORT void F_vi_Calc_Velocity(real *u, face_t, Thread *, Thread *);
FLUENT_EXPORT void F_vi_ocw_Velocity_Profiles(real NV_VEC(u), face_t f, Thread *t, real time);

FLUENT_EXPORT real Face_K_From_BC(face_t f, Thread *t, struct tv_vi_struct *vi, real V2);
FLUENT_EXPORT real Face_Ksgs_From_BC(face_t f, Thread *t, struct tv_vi_struct *vi, real V2);
FLUENT_EXPORT real Face_V2_From_BC(face_t f, Thread *t, struct tv_vi_struct *vi, real Vel2);
FLUENT_EXPORT real Face_D_From_BC(face_t f, Thread *t, struct tv_vi_struct *vi,
                                  real rho, real mu, real k);
FLUENT_EXPORT real Face_O_From_BC(face_t f, Thread *t, struct tv_vi_struct *vi,
                                  real rho, real mu, real k);
FLUENT_EXPORT real Face_Nut_From_BC(face_t f, Thread *t, struct tv_vi_struct *vi,
                                    real V2, real rho, real mu);

FLUENT_EXPORT real Get_Correlation_Re_theta(real Tu, real dUds, real Vmag, real mu, real rho);

#if RP_3D
FLUENT_EXPORT void Init_VM_gx_gy_gz(Thread *t);
#endif
extern FLUENT_EXPORT cxboolean rp_vm_stream;

#endif /* _FLUENT_F_VI_H */
