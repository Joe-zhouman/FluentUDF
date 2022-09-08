/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DX_ABAQUS_H
#define _FLUENT_DX_ABAQUS_H

#include "dll.h"

#if SEEM

# if !PARALLEL
FLUENT_EXPORT void Write_Abaqus_Domain(Domain *, FILE *, Pointer, Pointer);
FLUENT_EXPORT void Write_Abaqus_Surfaces(Domain *, Pointer, Pointer, FILE *, Pointer, Pointer);
# endif

#endif /* SEEM */

#endif /* _FLUENT_DX_ABAQUS_H */
