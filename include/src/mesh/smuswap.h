/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SMUSWAP_H
# define _FLUENT_SMUSWAP_H

#include "dll.h"

FLUENT_EXPORT void Smooth_Mesh(Domain *d, real relax, int iter);
FLUENT_EXPORT void Smooth_Mesh_By_Laplace(Domain *d, real skew, int iter);
FLUENT_EXPORT void Swap_Mesh_Faces(Domain *d, Thread *, int *nswap, int *ntotl);
FLUENT_EXPORT void Smooth_Cell_Thread_By_Squish (Domain *, Thread *, int, real, cxboolean);

#endif /* _FLUENT_SMUSWAP_H */
