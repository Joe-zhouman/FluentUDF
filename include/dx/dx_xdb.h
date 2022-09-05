/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DX_XDB_H
#define _FLUENT_DX_XDB_H

#include "dll.h"

#ifdef __cplusplus
extern "C" {
#endif

FLUENT_EXPORT void Write_FV_XDB(Domain *, Pointer, Pointer, Pointer, Pointer, Pointer);

#if RP_NODE
/* Following four functions should be called at correct sequence */
FLUENT_EXPORT void XDB_Open_Pathline_File(const char *);
FLUENT_EXPORT void XDB_Add_Pathline_Spacetime(float, float, float, float);
FLUENT_EXPORT void XDB_Write_Pathline_To_File();
FLUENT_EXPORT void XDB_Close_Pathline_File();
#endif

#ifdef __cplusplus
}
#endif
#endif
