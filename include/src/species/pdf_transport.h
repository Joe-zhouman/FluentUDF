/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_PDF_TRANSPORT_H
#define _FLUENT_PDF_TRANSPORT_H

#include "dpm_types.h"

#define n_pdf_work 3

typedef enum
{
  NO_MIXING,
  IEM,
  MODIFIED_CURL,
  EMST,
  MIXING_MODEL_MAX
} PDF_Transport_Mixing_Model;

extern FLUENT_EXPORT real heat_of_reaction_pdft;

FLUENT_EXPORT void update_pdf_particle_density(Particle *p, Material *m, real yk[]);
FLUENT_EXPORT void pdf_transport_mix(Domain *domain);
FLUENT_EXPORT void pdf_transport_react(Domain *domain);
FLUENT_EXPORT void pdf_transport_stats(Domain *domain);
FLUENT_EXPORT void pdf_transport_create_particles(Injection *pdft_inj);
FLUENT_EXPORT void pdf_transport_particle_number_control(Domain *domain);
FLUENT_EXPORT void pdf_transport_particle_position_correction(Domain *domain, Injection *pdft_inj);
FLUENT_EXPORT void pdf_transport_iteration(Domain *domain, Injection *pdft_inj);
FLUENT_EXPORT void pdf_transport_particle_init(Injection *pdft_inj);
FLUENT_EXPORT real CalcLocalTimeStep(cell_t c, Thread *t);
FLUENT_EXPORT void Set_IEM_Wall_Junction_Flag(Domain *domain);
FLUENT_EXPORT void patch_pdf_transport_particles(cell_t c, Thread *, Svar nv, int nd, real value);
FLUENT_EXPORT void pdf_transport_radiation_sources(Domain *domain);
FLUENT_EXPORT void pdf_transport_sources(Domain *domain);
FLUENT_EXPORT real init_emst_age_state(void);
FLUENT_EXPORT real turbulent_mixing_rate(cell_t c, Thread *t, int liquid_micro_mix, real c_phi);
#endif
