/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_EVENT_H
#define _FLUENT_EVENT_H

#include "dll.h"

#if GRAPHICS
FLUENT_EXPORT void Probe_Thread_Info(cxboolean active, Thread *t, int item);
FLUENT_EXPORT void Probe_Surface_Info(cxboolean active, int id, int item);

#if !RP_HOST
FLUENT_EXPORT void Print_Cell_Info(Thread *, cell_t, cxboolean surface_cell);
FLUENT_EXPORT void Print_Face_Info(Thread *, face_t);
FLUENT_EXPORT void Print_Node_Info(Node *v, Thread *);
FLUENT_EXPORT void Get_Cell_Centroid_Info(Thread *, cell_t, float *centroid);
#endif

FLUENT_EXPORT void mouse_split(Domain *d);
#endif

#endif /* _FLUENT_EVENT_H */
