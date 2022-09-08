/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_HANG_H
#define _FLUENT_HANG_H

#include "dll.h"
#include "mem.h"

FLUENT_EXPORT void Subdivide_Coalesce_Mesh (Domain *, cxboolean, cxboolean);
FLUENT_EXPORT void Balance_Subdivide_Coalesce_Mesh(Domain *, cxboolean);

FLUENT_EXPORT void Cell_Count_Change_After_Adaption(Domain *, int *);
FLUENT_EXPORT void Fill_Cell_Refine_Level(Domain *);
FLUENT_EXPORT void Free_Parents(Domain *, Objp *, Objp *, cxboolean);

FLUENT_EXPORT void Remove_Orphan_Bridge_Faces (Domain *, int);
#if !RP_HOST
FLUENT_EXPORT void Update_Hanging_Node_Node_Values(Domain *);
#endif
FLUENT_EXPORT void Update_Hanging_Node_Positions (Domain *, cxboolean);
FLUENT_EXPORT void Set_Hanging_Node_Flags(Domain *);

FLUENT_EXPORT void Make_Bridge_Faces(Domain *);
FLUENT_EXPORT void Free_Bridge_Faces(Domain *);

FLUENT_EXPORT void Smooth_Cell_Level(Domain *);

FLUENT_EXPORT cxboolean parent_thread_p(Domain *);

FLUENT_EXPORT face_t subdivide_face_and_shadow(Domain *, face_t, Thread *,
                                               Thread **);
FLUENT_EXPORT void install_face_parent(face_t, Thread *, face_t, Thread *);
FLUENT_EXPORT void install_cell_parent(cell_t, Thread *, cell_t, Thread *);
FLUENT_EXPORT cell_t make_cell_parent(Domain *, cell_t, Thread *, Thread *);
FLUENT_EXPORT cell_t make_cell_coalesce(Domain *, cell_t, Thread *, Thread **);
FLUENT_EXPORT void update_threads(Domain *, cxboolean);
FLUENT_EXPORT void clear_cell_kid_marks(cell_t, Thread *, unsigned int);
FLUENT_EXPORT void update_face_status(Domain *);
FLUENT_EXPORT void update_face_storage_after_coalesce(face_t, Thread *, face_t, Thread *);
#if RP_EDGE
FLUENT_EXPORT Edge *make_edge_child(Node *, Node *, Edge *);
FLUENT_EXPORT Node *find_mid_edge_node(Edge *);
FLUENT_EXPORT Node *make_mid_edge_node(Domain *, Edge *);
#endif
FLUENT_EXPORT void Fill_Cell_Parent(Domain *d);
FLUENT_EXPORT void Free_Cell_Parent(Domain *d);
FLUENT_EXPORT cell_t Topmost_Cell_Parent (cell_t, Thread *, Thread **);
FLUENT_EXPORT void Fill_Any_Has_Cell_Parent(Domain *d);
FLUENT_EXPORT void Free_Any_Has_Cell_Parent(Domain *d);
FLUENT_EXPORT void Fill_Has_Cell_Parent(Domain *d);
FLUENT_EXPORT void Free_Has_Cell_Parent(Domain *d);
FLUENT_EXPORT void Fill_Thread_Cell_Parent(Thread *);
FLUENT_EXPORT void Free_Thread_Cell_Parent(Thread *);
FLUENT_EXPORT void Fill_Face_Parent(Domain *d);
FLUENT_EXPORT void Free_Face_Parent(Domain *d);
FLUENT_EXPORT void Fill_Thread_Face_Parent(Thread *);
FLUENT_EXPORT void Free_Thread_Face_Parent(Thread *);
FLUENT_EXPORT void adapt_error(Domain *, char *);
FLUENT_EXPORT cxboolean is_f_kid_in_cnbr(const face_t, Thread *const,
                                         const face_t, Thread *const,
                                         const cell_t, Thread *const );
FLUENT_EXPORT face_t make_face_coalesce(Domain *, face_t, Thread *, Thread **);
FLUENT_EXPORT Node *find_mid_face_node (face_t, Thread *);
#if RP_3D
FLUENT_EXPORT Node *find_edge_hanging_node(face_t f, Thread *, int);
#endif

FLUENT_EXPORT int Fill_Cell_Tree_Level (Domain *);
FLUENT_EXPORT cxboolean Cell_Thread_Has_Adapted_Face_Threads(Thread *);
FLUENT_EXPORT cxboolean Face_Thread_Has_Nonuniform_Refinement_Level(Thread *);
FLUENT_EXPORT int Clear_Inappropriate_Coarsening_Bits (Domain *);
FLUENT_EXPORT void Mark_All_Cells_To_Be_Refined (Domain *);
FLUENT_EXPORT void Mark_All_Cells_Per_Level_To_Be_Coarsened (Domain *, int);
FLUENT_EXPORT void Free_Cell_Tree_Level (Domain *);
FLUENT_EXPORT void Free_Adaption_Storage_Variables (Domain *);
#if !RP_HOST
FLUENT_EXPORT int Fill_Bridge_Nodes_Of_Cells (Domain *);

#endif
FLUENT_EXPORT void Free_Bridge_Nodes_Of_Cells (Domain *);
FLUENT_EXPORT void Draw_Cell_Bridge_Nodes (
#if !RP_HOST
  cell_t, Thread *
#else
  void
#endif
);
#if RP_NODE
FLUENT_EXPORT void Rebuild_Exterior_Refine_Hang(Domain *);
FLUENT_EXPORT void Rebuild_Exterior_Coarsen_Hang(Domain *, int, cxboolean);
FLUENT_EXPORT void Resolve_Duplicate_Hanging_Nodes(Domain *);
FLUENT_EXPORT void Synch_Parent_Child_Faces (Domain *);
#endif

/* data structure needed for lsq at nodes */
typedef struct bridge_node_struct
{
  Node *v;
  real wt;
  real NV_VEC(wt_g);
  Thread *tper;   /* MAZAB : added due to a change in NBG computations at NCI */
} Bridge_Node;

#define BN_NODE(b) ((b)->v)
#define BN_WT(b) ((b)->wt)
#define BN_WT_G(b) ((b)->wt_g)
#define BN_FT(b) ((b)->tper)  /* pointer to face thread */


#define C_BRIDGE_NODES(c,t) \
  C_STORAGE(c,t,SV_C_BRIDGE_NODES,struct bridge_node_struct **)
#define C_BRIDGE_NODE(c,t,i) (C_BRIDGE_NODES(c,t)[i])
#define C_BRIDGE_NNODES(c,t) C_STORAGE_I(c,t,SV_C_BRIDGE_NNODES)
#define C_BRIDGE_NNODES_SAFE(c,t) (SV_ALLOCATED_P(t,SV_C_BRIDGE_NNODES) ? \
            C_STORAGE_I(c,t,SV_C_BRIDGE_NNODES) : 0)

#define F_BRIDGE_NODES(e,t)       C_BRIDGE_NODES(e,t)
#define F_BRIDGE_NODE(e,t,i)      C_BRIDGE_NODE(e,t,i)
#define F_BRIDGE_NNODES(e,t)      C_BRIDGE_NNODES(e,t)
#define F_BRIDGE_NNODES_SAFE(e,t) C_BRIDGE_NNODES_SAFE(e,t)
#define SV_F_BRIDGE_NODES      SV_C_BRIDGE_NODES
#define SV_F_BRIDGE_NNODES     SV_C_BRIDGE_NNODES

#endif /* _FLUENT_HANG_H */
