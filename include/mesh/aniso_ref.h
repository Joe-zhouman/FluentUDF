/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_ANISO_H
#define _FLUENT_ANISO_H

/**
 * @file  aniso_ref.h
 * @brief Header file for the anisotropic adaptation routines
 */

#include "global.h"
#include "dll.h"
#include "mem.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * Global functions
 */
FLUENT_EXPORT cxboolean
Aniso_Refine_Mesh (Domain *, Objp *, int, cxboolean, real, cxboolean);

FLUENT_EXPORT cxboolean
Mark_Cells_From_Boundary
(
  Objp *, int, cxboolean, cxboolean, Domain *,
  void (*fill)(cell_t, Thread *, int)
);

#if RP_3D && RP_POLYHEDRA

FLUENT_EXPORT void
Redistribute_Boundary_Layer (Thread *, real);

#endif

#endif /* _FLUENT_ANISO_H */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
