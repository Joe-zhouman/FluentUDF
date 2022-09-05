/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_CASECHECK_H
#define _FLUENT_CASECHECK_H

#include "dll.h"
#include "mem.h"
#include "global.h"

FLUENT_EXPORT cxboolean Mesh_Unstructured_P (Domain *);
FLUENT_EXPORT cxboolean Mesh_Unstructured_Node_Only_P (Domain *);
FLUENT_EXPORT cxboolean Mesh_Hexahedral_P (Domain *);
FLUENT_EXPORT cxboolean Mesh_Has_Hexahedra_P (Domain *);
FLUENT_EXPORT cxboolean Mesh_Is_Adapted_P (Domain *);
FLUENT_EXPORT cxboolean Mesh_Has_Face_Hierarchy_P (Domain *);
FLUENT_EXPORT cxboolean Mesh_Has_Cell_Hierarchy_P (Domain *);
#if RP_3D
FLUENT_EXPORT cxboolean Mesh_Hexcore_P (Domain *);
FLUENT_EXPORT cxboolean Mesh_Hex_Transition_P (Domain *);
#endif
#endif /* _FLUENT_CASECHECK_H */
