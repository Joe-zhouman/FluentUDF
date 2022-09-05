/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#include "dll.h"

#if SEEM

FLUENT_EXPORT void Write_Ascii_Domain(Domain *, FILE *, Pointer, int, int );
FLUENT_EXPORT void Write_Ascii_Surfaces(Domain *, Pointer, Pointer, FILE *, Pointer, int, int );

/*  functions for APECS co-simulation  */
FLUENT_EXPORT void Write_APECS_Surfaces(Domain *, Pointer, FILE *, Pointer);
FLUENT_EXPORT void Write_APECS_Domain(Domain *, FILE *, Pointer);

#endif /* #if SEEM */

