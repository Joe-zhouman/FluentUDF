/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#include "dll.h"

#if SEEM

#define VAL_FMT " %12.5e"
#define VAL_PER 5
#define DX_MIXED_FACE 1
#define DX_LINEAR_FACE 2
#define DX_TRI_FACE 3
#define DX_QUAD_FACE 4

FLUENT_EXPORT void Write_Dx_Domain(Domain *, FILE *, Pointer );
FLUENT_EXPORT void Write_Dx_Surfaces(Domain *, Pointer, Pointer, Pointer, FILE *);

#endif /*SEEM */

