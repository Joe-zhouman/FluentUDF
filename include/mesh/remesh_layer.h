/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_REMESH_LAYER_H
#define _FLUENT_REMESH_LAYER_H

enum
{
  LAYER_SKIP_CASE = 0,
  LAYER_SUBDIVIDE_CASE,
  LAYER_COALESCE_CASE,
  LAYER_SUBDIVIDE_BLOCKED_CASE,
  LAYER_COALESCE_BLOCKED_CASE,
  LAYER_SUB_AND_COALESCE_BLOCKED_CASE,
  LAYER_BLOCKED_CASE = 99
};

FLUENT_EXPORT void Subdivide_Coalesce_Mesh_Layer (Domain *);
FLUENT_EXPORT void Subdivide_Mesh_Layer (Domain *);
# if PARALLEL
FLUENT_EXPORT cxboolean Mark_Migration_Layer_Cells (Domain *);
#  if 0
FLUENT_EXPORT void Migrate_Layer_Cells (Domain *, cxboolean);
#  endif
FLUENT_EXPORT void Migrate_Layer_Cells_Of_Thread_List (Domain *, Objp *,
                                                       cxboolean);
FLUENT_EXPORT void Thread_Migrate_Layer_Cells (Domain *, Thread *, int);
# endif

FLUENT_EXPORT void Store_Metrics_On_Layering_Threads (Domain *);

FLUENT_EXPORT Thread *Insert_Cell_Layer (Domain *, Thread *, real *, Objp **);
FLUENT_EXPORT cxboolean Remove_Cell_Layer (Domain *, Thread *);
FLUENT_EXPORT void Insert_Prismatic_Layer (Domain *, Thread *, Thread *,
                                           Objp **);
FLUENT_EXPORT void Collapse_Prismatic_Layer (Domain *, Thread *, Thread *,
                                             int **);
FLUENT_EXPORT void Thread_Subdivide_Coalesce_Layer (Domain *, Thread *,
                                                    int, int);

#endif /* _FLUENT_REMESH_LAYER_H */
