/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_REMESH_SF_H
#define _FLUENT_REMESH_SF_H

#include "dll.h"

typedef enum
{
  BG_SF_UNKNOWN = -1,
  BG_SF_FROM_BOUNDARY,
  BG_SF_FROM_INTERIOR
} BG_SF_Type;

FLUENT_EXPORT int Setup_Background_Sizing_Function (Domain *, Thread *,
                                                    int, BG_SF_Type, int);
FLUENT_EXPORT void Free_Background_Sizing_Function (int);

FLUENT_EXPORT real BG_SF_Value_At_Cell (cell_t, Thread *, int, cxboolean);
FLUENT_EXPORT real BG_SF_Value_At_Face (face_t, Thread *, int, cxboolean);
FLUENT_EXPORT real BG_SF_Value_At_Position (real *, int, cxboolean);

#endif /* _FLUENT_REMESH_SF_H */
