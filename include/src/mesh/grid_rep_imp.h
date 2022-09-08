/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_GRID_REP_IMP_H
#define _FLUENT_GRID_REP_IMP_H

#include "dll.h"

FLUENT_EXPORT Objp *mesh_invalid_cells;
FLUENT_EXPORT Objp *mesh_modified_centroid_cells;
FLUENT_EXPORT Objp *mesh_poor_quality_cells;
FLUENT_EXPORT Objp *mesh_user_defined_cells;
FLUENT_EXPORT Objp *mesh_solver_identified_cells;
FLUENT_EXPORT Objp *mesh_gqm_cells;
FLUENT_EXPORT Objp *mesh_mass_imb_oq_cells;

FLUENT_EXPORT int pmn_solver_identified_cells;
FLUENT_EXPORT cxindex mesh_count_face_handedness_correction;
FLUENT_EXPORT cxboolean mesh_report_face_handedness_correction_p;

FLUENT_EXPORT void Enable_Pure_Mesh_Metrics (cxboolean, Domain *);
FLUENT_EXPORT cxboolean Enable_Low_Aspect_Ratio_Pure_Mesh_Metrics (cxboolean,
                                                                   Domain *);
FLUENT_EXPORT void Init_Poor_Mesh_Quality_Lists (Domain *, Objp *);
FLUENT_EXPORT void Init_User_Defined_Poor_Quality_List (void);
FLUENT_EXPORT void Init_Solver_Identified_Poor_Quality_List (void);
FLUENT_EXPORT void Set_User_Defined_Poor_Quality_List (Domain *, unsigned int,
                                                       unsigned int);
FLUENT_EXPORT void Set_Solver_Identified_Poor_Quality_List (Domain *domain);
FLUENT_EXPORT void Identify_Poor_Mesh_Quality_Elements (Domain *, Objp *);
FLUENT_EXPORT cxindex Identify_Invalid_Cells_From_Virtpoly_LHF (Domain *, Objp *);
FLUENT_EXPORT void Update_Poor_Mesh_Quality_Metrics (Domain *, Objp *, cxboolean);
FLUENT_EXPORT void Identify_Poor_Mesh_Quality_Residual_Imbalance_Elements(Domain *);
FLUENT_EXPORT void Identify_Poor_Mesh_Gradient_Quality_Measure_Elements(Domain *);
FLUENT_EXPORT void Improve_Cell_Centroids_Based_On_Orthogonality(Domain *domain, Objp *);

FLUENT_EXPORT cxboolean Has_Poor_Mesh_Quality_Elements (cxboolean);
FLUENT_EXPORT void Set_Info_Poor_Mesh_Quality_Elements (int);
FLUENT_EXPORT void Info_Poor_Mesh_Quality_Elements (Domain *);
FLUENT_EXPORT void Report_Poor_Mesh_Elements_Count (Domain *);
FLUENT_EXPORT void Report_Poor_Elements_Exceeding_Solution_Limits (Domain *);

FLUENT_EXPORT void Improve_Cell_Centroids_At_Left_Handed_Faces (Domain *,
                                                                Objp *);
FLUENT_EXPORT void Repair_Shadow_Nodes_Of_Face_Pair (face_t, Thread *,
                                                     face_t, Thread *,
                                                     cxboolean);
FLUENT_EXPORT void Repair_Face_Node_Shadow_Connectivity (Domain *);
FLUENT_EXPORT void Align_Node_And_Node_Shadow (Domain *);
FLUENT_EXPORT void Check_And_Repair_Face_Node_Order (Domain *, int);
FLUENT_EXPORT cxboolean Check_And_Repair_Face_Handedness (Domain *,
                                                          cxboolean);
FLUENT_EXPORT void Mark_User_Defined_Cells(Domain *);
#if RP_AXI
FLUENT_EXPORT void Repair_Axisymmetric_Mesh_Positivity (Domain *);
#endif
FLUENT_EXPORT void Repair_Grid (Domain *);
FLUENT_EXPORT void Improve_Grid (Domain *, int, real, cxindex, int);
FLUENT_EXPORT void Print_Grid_Repair_Improve_Solver_Stats (Domain *);

FLUENT_EXPORT int Mark_NonConvex_Cells (Domain *, int);

FLUENT_EXPORT real Smooth_Quality_Laplace (Domain *, int, real, int, real,
                                           int, int);
FLUENT_EXPORT void Init_Smooth_Quality_Random (void);
FLUENT_EXPORT real Smooth_Quality_Random (Domain *, int, real, cxboolean,
                                          cxboolean, int, cxboolean, int);

FLUENT_EXPORT cxboolean Compute_Kernel_Centroid (real *, cell_t, Thread *);
FLUENT_EXPORT cxboolean alloc_and_initialize_cell_marks (Domain *);
FLUENT_EXPORT void free_cell_marks (Domain *);

FLUENT_EXPORT void init_pmn_entity_flags(Domain *);
#endif /* _FLUENT_GRID_REP_IMP_H */
