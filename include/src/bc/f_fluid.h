/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_F_FLUID_H
#define _FLUENT_F_FLUID_H

#include "dll.h"
#include "syn_turb.h"

/* interior interface */
struct tv_interior_struct
{
  /*
   *    Please NOTE !!!
   *
   *  Historically, interior threads did not have any
   *  thread variables attached to them at all, meaning
   *  that for them the "THREAD_VAR(t)" union contained
   *  zeroes only.
   *        This assumption is still made in many places
   *  in the code, e.g. when the type of a thread is
   *  changed but its "THREAD_VAR(t)" union isn't
   *  reinitialized.
   *        Therefore, all the variables defined below
   *  should have complete zeroes as their default
   *  values, and should only become non-zero when
   *  there is any need.
   *        Currently, only variables related to the
   *  vortex method for rans-les-interfaces are
   *  listed here. So, when all these are initialized
   *  to zero by default, the old assumption should
   *  at least not do any harm for all interiors
   *  that are not made "rans-les-interface".
   */

  /* Les inlet specification method */
  LES_Spec_Type les_spec;

  /* Synthetic turbulence */
  syn_turb_spectral_synthesizer_type syn_turb_spectral_synthesizer;
#if RP_3D
  syn_turb_synthetic_turbulence_generator_type syn_turb_synthetic_turbulence_generator;
  syn_turb_vortex_method_type syn_turb_vortex_method;
#endif
};

FLUENT_EXPORT void thread_interior_default(Domain *, Thread *);

FLUENT_EXPORT void Fluid_Derivative(Thread *);
FLUENT_EXPORT void Solid_Flux_Coarse(Thread *, real *, int);
FLUENT_EXPORT void Solid_Reconstruct(Thread *);

FLUENT_EXPORT void thermodynamic_face_recon( cell_t c, const Thread *const t, real w[],
                                             real u[], real *H, real *r );

extern FLUENT_EXPORT cxboolean face_recon_therm_consistent;


#endif /* _FLUENT_F_FLUID_H */
