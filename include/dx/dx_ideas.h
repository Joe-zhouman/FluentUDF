/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DX_IDEAS_H
#define _FLUENT_DX_IDEAS_H

#include "dll.h"

#if SEEM

#if !PARALLEL

#define IDEAS_UNITS_ID           164
#define IDEAS_NODES_ID    2411
#define IDEAS_ELEMENTS_ID 2412
#define IDEAS_RESULT_TYPE_ID  2413
#define IDEAS_ANALYSIS_DATA_ID  2414
#define IDEAS_GROUP_ID          2432

#define IDEAS_LINE      136
#define IDEAS_TRI 91
#define IDEAS_QUAD  94
#define IDEAS_TET 111
#define IDEAS_WEDGE 112
#define IDEAS_HEX 115

#define IDEAS_WRITE_ERROR Error("write-ideas: write error.")
FLUENT_EXPORT void Write_Ideas_Surfaces(Domain *, Pointer, Pointer, FILE *, Pointer, Pointer);
FLUENT_EXPORT void Write_Ideas_Domain(Domain *, FILE *, Pointer, Pointer);
FLUENT_EXPORT void Write_Ideas_Marked_Cells(Domain *, FILE *, Pointer, Pointer);
#endif /* !PARALLEL */
#endif /*SEEM*/

#endif /* _FLUENT_DX_IDEAS_H */
