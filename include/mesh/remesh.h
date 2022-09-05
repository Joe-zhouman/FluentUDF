/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_REMESH_H
#define _FLUENT_REMESH_H

extern FLUENT_EXPORT Svar sv_node_faces;
extern FLUENT_EXPORT Svar sv_fc0_i;
extern FLUENT_EXPORT Svar sv_fc1_i;
extern FLUENT_EXPORT Svar sv_cell_seed;
extern FLUENT_EXPORT Svar sv_remesh_tmp;

extern FLUENT_EXPORT Svar sv_part_local;
/* List of node connected faces, used throught by all remeshing functionality*/
#define F_LIST(v)(NODE_MANAGED_TMP_OBJP(v, sv_node_faces))

/* Storage for connectivity used during domain extraction */
#define F_C0_I(f,tf)(FACE_MANAGED_TMP_INT(f,tf,sv_fc0_i))
#define F_C1_I(f,tf)(FACE_MANAGED_TMP_INT(f,tf,sv_fc1_i))

/* Storage for grouping used during extract_remesh_domain  and interpolation */
#define C_SEED(c,tc)(CELL_MANAGED_TMP_INT(c,tc, sv_cell_seed))
/* Temporary node storage for remeshing */
#define N_REMESH_TMP(v)(NODE_MANAGED_TMP_TMPUNION(v, sv_remesh_tmp))
/* Marking used by local remeshing to identity compute node assignment
   for exterior cells */
#define C_PART_LOCAL(c,tc)(CELL_MANAGED_TMP_INT(c,tc, sv_part_local))

FLUENT_EXPORT void Prepare_Remesh (Domain *);
FLUENT_EXPORT void Cleanup_Remesh (Domain *, cxboolean, Objp *);
FLUENT_EXPORT void Alloc_Remesh_Memory(Domain *);
FLUENT_EXPORT void Free_Remesh_Memory(Domain *);

FLUENT_EXPORT void Clear_Face_Flag_Of_Clist (Objp *, int);
FLUENT_EXPORT void Flag_Exterior_Faces_Of_Clist (Objp *, int);
FLUENT_EXPORT cxboolean Clist_Contains_Coupled_Or_Dynamic_Thread_P (Objp *);

/* TODO Move to correct file */
FLUENT_EXPORT void
Mark_Remesh_Clusters(Domain *domain, Thread *thread,
                     unsigned int marked_bit, unsigned int layered_bit,
                     cxindex *nmarked, cxindex *nlayered);

# if DEBUG
FLUENT_EXPORT void Dynamic_Mesh_Write_Debug (char *, ...);
FLUENT_EXPORT void Dynamic_Mesh_New_Debug (void);

#  define DYNAMESH_OUT Dynamic_Mesh_Write_Debug
#  define DYNAMESH_OUT_NEW Dynamic_Mesh_New_Debug ()

FLUENT_EXPORT void Print_Cell_At_Location (Domain *, Thread *,
                                           real, real, real);
FLUENT_EXPORT void Print_Node_At_Face_Location (Domain *, Thread *, real *,
                                                real);
FLUENT_EXPORT void Print_Cell_With_Id (Domain *, cxindex);
FLUENT_EXPORT void Print_Face_With_Id (Domain *, cxindex);
FLUENT_EXPORT void Print_Node_With_Id (Domain *, cxindex);
FLUENT_EXPORT void Print_Cells_With_Node_Id_Index (Domain *, cxindex, cxboolean);
FLUENT_EXPORT void Print_Faces_With_Node_Id_Index (Domain *, cxindex, cxboolean);
# endif /* DEBUG */

#endif /* _FLUENT_REMESH_H */
