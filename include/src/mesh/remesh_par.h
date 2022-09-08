/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_REMESH_PAR_H
#define _FLUENT_REMESH_PAR_H

#include "dll.h"
#include "mem.h"

# if PARALLEL
FLUENT_EXPORT cxboolean Required_Repartition_Remeshing_Threads (Domain *, cxboolean);
FLUENT_EXPORT void Repartition_Domain (Domain *);

FLUENT_EXPORT void Migrate_Cells (Domain *, cxboolean);
#  if RP_NODE
FLUENT_EXPORT void Pre_Mark_Migration_On_Node_Visit (Domain *);
FLUENT_EXPORT cxboolean Mark_Migration_On_Node_Visit (Domain *, cxboolean);
#  endif
FLUENT_EXPORT cxboolean Mark_Remigration_Cells (Domain *domain);
FLUENT_EXPORT void Remigrate_Migrated_Cells (Domain *);

FLUENT_EXPORT cxboolean Migration_Dest_Allocated (Domain *);
FLUENT_EXPORT cxboolean Migration_Owner_Allocated (Domain *);
FLUENT_EXPORT cxboolean Migration_Cache_Allocated (Domain *);
# endif /* PARALLEL */

# if RP_NODE
FLUENT_EXPORT void Count_Initial_Entities (Domain *, cxindex *, cxindex *, cxindex *);
FLUENT_EXPORT void Setup_New_Ids (Domain *, cxindex, cxindex, cxindex);

FLUENT_EXPORT void Init_Exterior_Cells_Ids (Domain *);
FLUENT_EXPORT void Exchange_Cell_Ids (Domain *);
FLUENT_EXPORT void Create_Dummy_Exterior_Cells(Domain *, cxboolean);
FLUENT_EXPORT void Create_Missing_Exterior_Cells(Domain *, cxboolean);

FLUENT_EXPORT void Reset_Interface_Face_Flags (Domain *, unsigned int);
FLUENT_EXPORT void Exchange_Cell_Flags (Domain *, unsigned int);
FLUENT_EXPORT void Exchange_Face_Flags (Domain *, unsigned int);
FLUENT_EXPORT void Exchange_Node_Flags (Domain *, unsigned int);
FLUENT_EXPORT void Exchange_Cleared_Node_Flags (Domain *, unsigned int);
FLUENT_EXPORT void Exchange_Node_Visits (Domain *);
FLUENT_EXPORT void Exchange_Node_Marks (Domain *);
FLUENT_EXPORT void Exchange_Node_Marks_As_Flags (Domain *, unsigned int);
FLUENT_EXPORT void Exchange_Coordinates_For_Moved_Nodes (Domain *,
                                                         cxboolean (*)(Node *),
                                                         void (*)(Node *));

FLUENT_EXPORT void *Alloc_Cell_Exchange_Array (Domain *, int, int);
FLUENT_EXPORT void *Alloc_Cell_Node_Exchange_Array (Domain *, int, int);
FLUENT_EXPORT void *Alloc_Face_Exchange_Array (Domain *, int, int);
FLUENT_EXPORT void *Alloc_Face_Node_Exchange_Array (Domain *, int, int);
#  if RP_3D
FLUENT_EXPORT void *Alloc_Edge_Exchange_Array (Domain *, int, int);
#  endif
FLUENT_EXPORT void *Alloc_Node_Exchange_Array (Domain *, int, int);
FLUENT_EXPORT void Alloc_Init_Node_Exchange_Arrays (Domain *, int,
                                                    void **, void **);
# endif /* RP_NODE */

#endif /* _FLUENT_REMESH_LOCAL_H */

