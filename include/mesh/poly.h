/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_POLY_H
#define _FLUENT_POLY_H

#include "dll.h"

#if RP_POLYHEDRA
FLUENT_EXPORT real Max_Boundary_Aspect_Ratio (Domain *d);
FLUENT_EXPORT int Set_Dual_Conversion_Feature_Angle (Domain *domain);
FLUENT_EXPORT void Create_Dual_Mesh (Domain *);
FLUENT_EXPORT void Create_Polygonal_Faces (Domain *);
FLUENT_EXPORT void Agglomerate_Thread (Domain *, Thread *, int);

FLUENT_EXPORT void Thread_Remesh_Polyhedra_Cells (Domain *, Thread *);

FLUENT_EXPORT void Decompose_NonConvex_Cells (Domain *);

FLUENT_EXPORT void Enforce_Recheck_On_Polyhedra (void);

FLUENT_EXPORT int Triangulate_Ordered_Node_List (Objp *, patch_f *);

FLUENT_EXPORT void Draw_Cluster (cell_t, Thread *);
FLUENT_EXPORT void Draw_Slice (Domain *, int, real);

# if DEBUG
FLUENT_EXPORT Objp *ordered_node_list (face_t, Thread *, int *);
# endif

# define NODE_POLY_NEXT(v) \
   C_STORAGE(NODE_INDEX(v),NODE_THREAD(v),SV_N_NEXT,Node **)
# define NODE_POLY_PREV(v) \
   C_STORAGE(NODE_INDEX(v),NODE_THREAD(v),SV_N_PREV,Node **)

FLUENT_EXPORT real Poly_Smooth_Quality (Domain *, int, real, int);
FLUENT_EXPORT int Poly_Mark_NonConvex_Cells (Domain *);

FLUENT_EXPORT void Poly_Convert_Hanging_Node_Mesh (Domain *, Objp *, int);

# define F_NDUAL_FACES(f,t)          F_NDUALS(f,t)
# define f_dual_face_loop            f_dual_loop
# define F_DUAL_FACES(f,t)           F_DUALS(f,t)
# define SET_F_DUAL_FACES(_f,_t,_fd) (F_DUAL_FACES (_f, _t) = _fd)
# define F_DUAL_FACE(f,t,i)          F_DUAL(f,t,i)

#endif /* RP_POLYHEDRA */

FLUENT_EXPORT cxboolean Mesh_Is_Polyhedra_P (Domain *);
FLUENT_EXPORT cxboolean Mesh_Has_Polyhedra_P (Domain *, Objp *, cxboolean);
FLUENT_EXPORT cxboolean Mesh_Has_Polygonal_Faces_P (Domain *);
FLUENT_EXPORT cxboolean Thread_Has_Polygonal_Faces_P (Thread *);

#if RP_POLYHEDRA
FLUENT_EXPORT void Analyze_Polyhedra (Domain *);
#endif

FLUENT_EXPORT void Clear_Dual_Threads  (Domain *, cxboolean);
FLUENT_EXPORT void Update_Dual_Threads (Domain *, int, Thread **);
FLUENT_EXPORT void Delete_Dual_Threads (Domain *);

#endif /* _FLUENT_POLY_H */
