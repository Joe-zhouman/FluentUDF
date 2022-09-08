/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_CHECK_H
#define _FLUENT_CHECK_H

#include "dll.h"

FLUENT_EXPORT int Report_Face_Location (face_t, Thread *, char *);
FLUENT_EXPORT int Report_Cell_Location (cell_t, Thread *, char *);
FLUENT_EXPORT int Report_Node_Location (Node *, char *);
FLUENT_EXPORT void Set_max_mesh_check_report (int, int);
FLUENT_EXPORT cxboolean Check_Nodes_Per_Cell (Domain *, int);
FLUENT_EXPORT cxboolean Check_Faces_Per_Cell (Domain *, int);
FLUENT_EXPORT cxboolean Check_Cell_Thread (Domain *d);
FLUENT_EXPORT cxboolean Check_Cells_Per_Face (Domain *d, int verbosity);
FLUENT_EXPORT cxboolean Check_Face_Cells (Domain *d, int verbosity);
FLUENT_EXPORT cxboolean Check_Face_Cell_Threads (Domain *d, int verbosity);
FLUENT_EXPORT cxboolean Check_Cell_Connectivity (Domain *domain, int verbosity);
FLUENT_EXPORT int Check_Bridge_Faces (Domain *d);
FLUENT_EXPORT int Check_Face_Righthand_Cells (Domain *d);
FLUENT_EXPORT cxboolean Check_Face_Handedness (Domain *, cxboolean, cxboolean,
                                               int);
#if DEBUG && RP_NODE
FLUENT_EXPORT cxboolean Check_Exterior_Face_Handedness (Domain *d, cxboolean,
                                                        int);
#endif
FLUENT_EXPORT cxboolean Right_Face_Node_Order (cell_t, Thread *, cxboolean,
                                               cxboolean, int *, cxboolean *);
FLUENT_EXPORT cxboolean Check_Face_Node_Order (Domain *, cxboolean, cxboolean,
                                               int, cxboolean *);
FLUENT_EXPORT cxboolean Check_Boundary_Face_Orientation (Domain *, int, cxboolean,
                                                         Objp *, Objp **);
FLUENT_EXPORT cxboolean Check_Edges_Per_Face (Domain *d);
FLUENT_EXPORT real Normalized_Sum_Face_Area (cell_t, Thread *, cxboolean);
FLUENT_EXPORT cxboolean Check_Closed_Cells (Domain *, cxboolean, int);
FLUENT_EXPORT cxboolean Check_Contact_Points (Domain *, void (*)(Node *),
                                              cxboolean, int);
FLUENT_EXPORT cxboolean Check_Element_Type (Domain *);
FLUENT_EXPORT cxboolean Check_Boundary_Types (Domain *);
FLUENT_EXPORT cxboolean Check_Face_Pairs (Domain *);
FLUENT_EXPORT cxboolean Check_Face_Children (Domain *, int);
FLUENT_EXPORT cxboolean Check_Cell_Children (Domain *, int);
FLUENT_EXPORT void Check_Angle_Face_Children (Domain *, cxboolean, int);
FLUENT_EXPORT cxboolean Check_Unused_But_Referenced_Nodes (Domain *, int);
FLUENT_EXPORT cxboolean Check_Wall_Distance (Domain *, cxboolean);
FLUENT_EXPORT void Print_Contact_Points (Domain *);
FLUENT_EXPORT cxboolean Check_Boundary_Type(Domain *d);
FLUENT_EXPORT void Compute_Periodic_Thread_Angle(Thread *, real *, real *,
                                                 real *, int *);
FLUENT_EXPORT cxboolean Check_Periodic_Boundaries(Domain *, int);
#if RP_EDGE
FLUENT_EXPORT cxboolean Check_Edges_Per_Face(Domain *d);
#endif
FLUENT_EXPORT cxboolean Grid_Check (Domain *, cxboolean *);

FLUENT_EXPORT void Local_Domain_Extents (Domain *, real *, real *);
#if !RP_HOST
FLUENT_EXPORT int Grid_Check_Storage(Domain *domain);
FLUENT_EXPORT int Grid_Check_Multidomain (Domain *domain, int verbosity);
FLUENT_EXPORT void Grid_Check_Duplicate_Nodes(Domain *d);
FLUENT_EXPORT void Domain_Extents (Domain *, real *, real *);

FLUENT_EXPORT cxboolean Check_Cell_Parent_Child_Pointer(Domain *, int);
FLUENT_EXPORT cxboolean Check_Face_Parent_Child_Pointer(Domain *, int);
#endif
#if RP_NODE
FLUENT_EXPORT int Grid_Check_Parallel(Domain *domain, int verbosity);
#endif

FLUENT_EXPORT cxboolean Grid_Quality (Domain *, char *);

FLUENT_EXPORT real Min_Orthogonal_Quality_On_Thread (Thread *, cxboolean,
                                                     cxboolean, cxboolean);
FLUENT_EXPORT real Min_Orthogonal_Quality (Domain *, cxboolean, cxboolean,
                                           cxboolean);
FLUENT_EXPORT int Cells_With_Orthogonal_Quality_On_Thread(Thread *, real,
                                                          cxboolean, cxboolean,
                                                          cxboolean);

FLUENT_EXPORT cxboolean Get_Grid_Repairable_P(void);
FLUENT_EXPORT void Set_Grid_Repairable_P (cxboolean);
#endif /* _FLUENT_CHECK_H */
