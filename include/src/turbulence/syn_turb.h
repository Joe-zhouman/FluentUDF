/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */


#ifndef _FLUENT_SYNTHETIC_TURBULENCE__H
#define _FLUENT_SYNTHETIC_TURBULENCE__H


/**
 * \file
 * \brief External API header file for synthetic turbulence.
 */


#include "global.h"
#include "mem.h"


typedef struct syn_turb_spectral_synthesizer_struct
{
  int number_fourier_modes;
  real **wave_number;         /* wave number vectors */
  real **velocity_p;          /* velocity amplitude vectors */
  real **velocity_q;          /* velocity amplitude vectors */
  real *frequency;            /* frequencies */
} syn_turb_spectral_synthesizer_type;

#if RP_3D
typedef struct syn_turb_synthetic_turbulence_generator_struct
{
  cxboolean volumetric_method;
  cxboolean volumetric_specified_forcing_zone_thickness;
  real volumetric_forcing_zone_thickness;
  real time_tau;
  real **d;
  real **sigma;
  real *omega;
  real *phi;
} syn_turb_synthetic_turbulence_generator_type;

typedef struct syn_turb_vortex_method_struct
{
  cxboolean init;
  cxboolean init_stream;
  cxboolean streamwise;
  cxboolean massconservation;
  int n_vortex;
  real *xi;
  real *yi;
  real *zi;
  real *sign;
  real *gama;
  real *sig;
  real *ti;
  real *ti_max;
  real *gx;
  real *gy;
  real *gz;
} syn_turb_vortex_method_type;
#endif


FLUENT_EXPORT void Synthetic_Turbulence_Mom_Coeffs(Thread *t, Domain *PTR_RESTRICT domain, const cxboolean eles, const cxboolean is_new_time_step, const int les_spec, Svar sv_flux);

FLUENT_EXPORT void Spectral_Synthesizer_Alloc(const Thread *PTR_RESTRICT const t);
FLUENT_EXPORT void Spectral_Synthesizer_Free(const Thread *PTR_RESTRICT const t);
FLUENT_EXPORT void Spectral_Synthesizer_Sample_Thread_Parameters(const Thread *PTR_RESTRICT const t);
FLUENT_EXPORT void Spectral_Synthesizer_Update_Boundary_Velocity(const Thread *PTR_RESTRICT const t);
FLUENT_EXPORT void Spectral_Synthesizer_Interior_Velocity_Patch(const Domain *PTR_RESTRICT const domain, const int nmodes, const real flow_time);

#if RP_3D
FLUENT_EXPORT void Synthetic_Turbulence_Generator_Alloc(const Thread *PTR_RESTRICT const t);
FLUENT_EXPORT void Synthetic_Turbulence_Generator_Free(const Thread *PTR_RESTRICT const t);
FLUENT_EXPORT void Synthetic_Turbulence_Generator_Sample_Thread_Parameters(const Thread *PTR_RESTRICT const t);
FLUENT_EXPORT void Synthetic_Turbulence_Generator_Update_Boundary_Velocity(const Thread *PTR_RESTRICT const t);
FLUENT_EXPORT void Synthetic_Turbulence_Generator_Mom_Source_Init(const Domain *PTR_RESTRICT const domain, const Thread *PTR_RESTRICT const t);
FLUENT_EXPORT void Synthetic_Turbulence_Generator_Mom_Source(const Domain *PTR_RESTRICT const domain);
FLUENT_EXPORT void Synthetic_Turbulence_Generator_Volumetric_Scaling(const Domain *PTR_RESTRICT const domain);
FLUENT_EXPORT void Synthetic_Turbulence_Generator_Interior_Velocity_Patch(const Domain *PTR_RESTRICT const domain);
FLUENT_EXPORT void Synthetic_Turbulence_Generator_Update_Time_Arg_RP_List(const Domain *PTR_RESTRICT const domain);
FLUENT_EXPORT void Synthetic_Turbulence_Generator_Init_Time_Arg(const Domain *PTR_RESTRICT const domain);

FLUENT_EXPORT void Vortex_Method_Alloc(const Thread *PTR_RESTRICT const t, const int vmn);
FLUENT_EXPORT void Vortex_Method_Free(const Thread *PTR_RESTRICT const t);
FLUENT_EXPORT void Vortex_Method_Update_Boundary_Velocity(Domain *PTR_RESTRICT domain, Thread *PTR_RESTRICT t, Thread *PTR_RESTRICT t0, real *PTR_RESTRICT const u, real *PTR_RESTRICT const v, real *PTR_RESTRICT const w, cxboolean eles);
#endif


#endif
