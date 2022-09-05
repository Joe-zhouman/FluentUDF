/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_F_SYM_H
#define _FLUENT_F_SYM_H

#include "dll.h"
#include "surf.h"

FLUENT_EXPORT void Symmetry_Dissipation_Flux(Thread *);
FLUENT_EXPORT void Sym_Momentum_Dissipation_Flux(face_t f, Thread *thread, real fw[]);
FLUENT_EXPORT void thread_sym_default(Domain *, Thread *);
FLUENT_EXPORT void thread_axis_default(Domain *, Thread *);
#if RP_OVERSET
FLUENT_EXPORT void thread_overset_default(Domain *, Thread *);
#endif

/* symmetry and degassing bc */
struct tv_sym_struct
{
  cxboolean degassing_p;
};

#endif /* _FLUENT_F_SYM_H */
