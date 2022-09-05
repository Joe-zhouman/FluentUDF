/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DYNAMESH_EVENTS_H
#define _FLUENT_DYNAMESH_EVENTS_H

FLUENT_EXPORT void Push_Dynamic_Mesh_Event (Pointer *);
FLUENT_EXPORT void Free_Dynamic_Mesh_Events (void);
FLUENT_EXPORT cxboolean Stacked_Dynamic_Mesh_Event (int);
FLUENT_EXPORT cxboolean Setup_Event_Insert_Remove_Cell_Layer (void);

enum
{
  LAYER_INSERT_EVENT = 10,
  LAYER_REMOVE_EVENT
};

#endif /* _FLUENT_DYNAMESH_EVENTS_H */
