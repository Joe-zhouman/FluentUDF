/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_REMESH_TOOLS_H
#define _FLUENT_REMESH_TOOLS_H

FLUENT_EXPORT void Init_Remesh (Domain *);
FLUENT_EXPORT void Close_Remesh (Domain *);

FLUENT_EXPORT cxboolean Remesh_Cavity (Domain *, Objp *, Objp *, Thread *,
                                       int, int);
FLUENT_EXPORT cxboolean Remesh_Cavities (Domain *, Objp *, Objp *, Thread *);
/* T166050,  temporrrarily  suspend CutCell remesh*/
#if 0
FLUENT_EXPORT cxboolean Remesh_Gocart (Domain *, Objp *, Objp *, Thread *);
#endif
FLUENT_EXPORT cxboolean Refine_Local_Cavity (Domain *, Objp *, Thread *,
                                             double, double,
                                             Thread *, double (*xc)[3]);
FLUENT_EXPORT cxboolean Coarsen_Local_Cavity (Domain *, Objp *, Thread *,
                                              double, Thread *);
#if RP_3D
FLUENT_EXPORT cxboolean Remesh_Local_Prism_Cavity (Domain *, Objp *, Thread *,
                                                   Thread *);
#endif
#if RP_POLYHEDRA
FLUENT_EXPORT cxboolean Remesh_Polyhedra (Domain *, cell_t, Thread *, Thread *,
                                          cxboolean);
#endif
FLUENT_EXPORT cxboolean Remesh_Prism_Cavity (Domain *, Objp *, Thread *, int,
                                             patch_f *, Thread *, Thread *,
                                             int, double *, double *);
FLUENT_EXPORT cxboolean Remesh_Region_Cavity (Domain *, Objp *, Loop *,
                                              Thread *, Thread *);
#if RP_3D
FLUENT_EXPORT void reset_topology (Domain *domain);
#endif

FLUENT_EXPORT cxboolean Mesh_Planar_Loops (Domain *, Thread *, Objp *, real *,
                                           void (*)(double *, double *, void *));

FLUENT_EXPORT void Set_Next_Remesh_Entity_Ids (cxindex, cxindex, cxindex);
FLUENT_EXPORT void Get_Next_Remesh_Entity_Ids (cxindex *, cxindex *, cxindex *);


FLUENT_EXPORT void Init_Thread_Interior_Face_Data (Domain *, Thread *);
FLUENT_EXPORT void Init_Interior_Face_Thread_Data (Domain *, Thread *);
FLUENT_EXPORT void Init_Boundary_Face_Thread_Data (Domain *, Thread *);
FLUENT_EXPORT void Interpolate_Face_Thread_Data (Thread *, Thread *);
FLUENT_EXPORT void Interpolate_Cell_Thread_List_Data (Objp *, Objp *);
FLUENT_EXPORT void Interpolate_Cell_Thread_Data (Thread *, Thread *);
FLUENT_EXPORT void Conserve_Cell_Thread_Data (Thread *, Thread *);
FLUENT_EXPORT void Interpolate_Bounding_Cell_Data (cell_t, Thread *,
                                                   cell_t, Thread *);
FLUENT_EXPORT void interpolate_old_coords_from_nodes (Node *, Objp *);
#if RP_NODE
FLUENT_EXPORT void Exchange_Cell_Data_After_Interpolation(Domain *);
FLUENT_EXPORT void Adjust_Interface_Face_List(Domain *);
FLUENT_EXPORT void Unthread_Outdated_Ifaces(Domain *);
FLUENT_EXPORT void Thread_New_Ifaces(Domain *);
#endif

#if RP_3D
# define PRNT_VEC(v) (v)[0],(v)[1],(v)[2]
#else
# define PRNT_VEC(v) (v)[0],(v)[1],0.0
#endif

#endif /* _FLUENT_REMESH_TOOLS_H */
