/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DYNAMESH_SMOOTH_H
# define _FLUENT_DYNAMESH_SMOOTH_H

FLUENT_EXPORT void Model_Initialize_laplace_mesh_smooth(void);
FLUENT_EXPORT void Model_Initialize_fem_mesh_smooth(void);
FLUENT_EXPORT void Model_Initialize_rbf_mesh_smooth(void);

FLUENT_EXPORT cxboolean Smooth_Cell_Thread_By_Springs (Domain *, Thread *,
                                                       real, int, cxboolean);
FLUENT_EXPORT void Fill_Mesh_Smooth_Thread_Lists(Domain *);
FLUENT_EXPORT void Free_Mesh_Smooth_Thread_Lists(Domain *);
FLUENT_EXPORT void Print_Mesh_Smooth_Thread_Lists(Domain *, Objp *, Objp *, Objp *);
FLUENT_EXPORT void Get_Mesh_Smooth_Thread_Lists(Domain *, Objp **, Objp **, Objp **);
FLUENT_EXPORT void Fill_Mesh_Smooth_Diff(Domain *);
FLUENT_EXPORT void Smooth_Cell_Threads_By_Laplace (Domain *, real, real);
FLUENT_EXPORT void Solve_Laplace_Mesh_Smoothing(Domain *, cxboolean);
FLUENT_EXPORT void Smooth_Cell_Threads_By_FEM (Domain *, real, real);
FLUENT_EXPORT void Smooth_Cell_Threads_By_RBF (Domain *, real, real);
FLUENT_EXPORT void Smooth_Cell_Threads_By_FSI (Domain *, real, real, cxboolean);
FLUENT_EXPORT void Solve_FEM_Mesh_Smoothing(Domain *);
FLUENT_EXPORT void Solve_RBF_Mesh_Smoothing(Domain *);
FLUENT_EXPORT void nodeMeshSmoothVel(Domain *, Svar);
FLUENT_EXPORT void nodeRBFSmoothVel(Domain *, Svar);

FLUENT_EXPORT void Fems_Make_Amg_Overlap_Tables (Domain *domain, System *s);
FLUENT_EXPORT int Bamg_OD_Index(int sys_id, int i, int j);

#  if !RP_HOST
FLUENT_EXPORT void Laplace_Smooth_Boundary_Thread (Domain *, Thread *, int,
                                                   real, cxboolean);
#  endif

FLUENT_EXPORT cxboolean Init_Smooth_By_Skewness (Domain *);
FLUENT_EXPORT void Free_Smooth_By_Skewness (Domain *);
FLUENT_EXPORT cxboolean Smooth_Cell_Thread_By_Skewness (Domain *, Thread *,
                                                        real, real, int);
FLUENT_EXPORT void Smooth_Mesh_By_Skewness (Domain *, real, int);

#  if PARALLEL
FLUENT_EXPORT cxboolean Mark_Migration_Skewness_Smoothing_Cells (Domain *,
                                                                 real, real);
FLUENT_EXPORT void Migrate_Skewness_Smoothing_Cells (Domain *, real, real);
#  endif

FLUENT_EXPORT cxboolean Smooth_Deforming_Boundary_Layer (Domain *, Thread *);

#if RP_NODE
EXTERNC FLUENT_EXPORT void SolveRBFMeshSmoothing(Domain *, Objp *, Objp *, Objp *);
EXTERNC FLUENT_EXPORT void SolveRBFMeshSmoothingZonal(Domain *, Thread *, Objp *, Objp *);
#endif
#endif /* _FLUENT_DYNAMESH_SMOOTH_H */
