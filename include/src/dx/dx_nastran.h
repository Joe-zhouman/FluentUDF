/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DX_NASTRAN_H
#define _FLUENT_DX_NASTRAN_H

#include "dll.h"

#if SEEM
#if !PARALLEL
FLUENT_EXPORT void Write_Nastran_Surfaces(Domain *, Pointer, Pointer, FILE *, Pointer);
FLUENT_EXPORT void Write_Nastran_Domain(Domain *domain, FILE *fp, Pointer scalars);
FLUENT_EXPORT void Write_Nastran_Marked_Domain(Domain *, FILE *, Pointer);
#endif /* !PARALLEL */
#endif /* SEEM */

#endif /* _FLUENT_DX_NASTRAN_H */
