/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_GRID_PAR_H
#define _FLUENT_GRID_PAR_H

#include "dll.h"
FLUENT_EXPORT void Create_Lean_Neighborhood(Domain *);
FLUENT_EXPORT void Fill_Partition_Interface_Faces(Domain*);
FLUENT_EXPORT void Fill_Regular_Exterior(Domain *);
FLUENT_EXPORT void Fill_Regular_Exterior_Nodes(Domain *,Objp *);
FLUENT_EXPORT void Neighborhood_Remove_Zones(Domain*, Objp*);
FLUENT_EXPORT void Neighborhood_Add_Zones(Domain*, Objp*);
FLUENT_EXPORT void Add_Cells_Extended_Exterior(Domain *domain);
#if RP_NODE
FLUENT_EXPORT void Fill_Exterior_Nodes(Domain *d);
FLUENT_EXPORT void Fill_Exterior_Cell_Node_Coords(Domain *d);
FLUENT_EXPORT void Fill_Exterior_Faces(Domain *d);
FLUENT_EXPORT void Fill_Exterior_Interior_BFaces(Domain *d);
FLUENT_EXPORT void Free_Exterior_Interior_BFaces(Domain *d);
# if RP_3D
FLUENT_EXPORT void Fill_Exterior_Interior_BFaces(Domain *d);
# endif
#if RP_OVERSET
FLUENT_EXPORT void Fill_Overset_Interface_Face_Lists(Domain *d);
#endif
FLUENT_EXPORT void Alloc_Exterior_Cell_CR_Storage (Domain *);
# if RP_HANG && RP_EDGE
FLUENT_EXPORT void Fill_Interface_And_Corner_Edges(Domain *d, cxboolean shell);
FLUENT_EXPORT void Fill_Interface_And_Corner_Edges_If_Changed(Domain *d, cxboolean shell);
FLUENT_EXPORT void Free_Interface_And_Corner_Edges(Domain *d);
FLUENT_EXPORT void Order_Edge_Lists(Domain *d);
# endif
FLUENT_EXPORT Dom_Neighbor *Create_Neighbor_Array(void);
FLUENT_EXPORT void Create_Neighborhood(Domain *d);
FLUENT_EXPORT void Post_Incremental_Neighborhood(Domain *d);
FLUENT_EXPORT void Free_Domain_Neighbors(Domain *d);
FLUENT_EXPORT void Free_Neighborhood(Domain *d);
FLUENT_EXPORT void Print_Neighborhood(Domain *d);
FLUENT_EXPORT int Update_Neighbor_Counts(Domain *d);

FLUENT_EXPORT Dom_Neighbor *Lookup_Neighbor(Domain *d, int pe);
FLUENT_EXPORT void Copy_Neighbor_Array(Domain *to, Domain *from);

FLUENT_EXPORT Objp *Lookup_Interior_Cell_List(Domain *d, int pe);
FLUENT_EXPORT Objp *Lookup_Exterior_Cell_List(Domain *d, int pe);
FLUENT_EXPORT Objp *Lookup_Interface_Face_List(Domain *d, int pe);
# if RP_HANG && RP_EDGE
FLUENT_EXPORT Objp *Lookup_Interface_Edge_List(Domain *d, int pe);
FLUENT_EXPORT Objp *Lookup_Corner_Edge_List(Domain *d, int pe);
FLUENT_EXPORT Objp *Lookup_Parent_Interface_Edge_List(Domain *d, int pe);
FLUENT_EXPORT Objp *Lookup_Parent_Corner_Edge_List(Domain *d, int pe);
# endif
FLUENT_EXPORT Objp *Lookup_Exterior_Face_List(Domain *d, int pe);
FLUENT_EXPORT Objp *Lookup_Interface_Node_List(Domain *d, int pe);
FLUENT_EXPORT Objp *Lookup_Exterior_Node_List(Domain *d, int pe);
FLUENT_EXPORT Objp *Lookup_Corner_Node_List(Domain *d, int pe);
FLUENT_EXPORT Node *Lookup_Node_By_Id_In_List(Objp *, cxindex);
# if RP_EDGE
FLUENT_EXPORT Edge *Lookup_Edge_By_Node_Ids_In_List (Objp *, cxindex, cxindex);
# endif

FLUENT_EXPORT cell_t Lookup_Cell_In_List(Objp *head, cxindex cid, Thread **);
FLUENT_EXPORT cell_t Sort_n_Lookup_Cell_In_List(Objp *head, cxindex cid, Thread **);
FLUENT_EXPORT Node *Sort_n_Lookup_Node_In_List(Objp *head, cxindex cid);

FLUENT_EXPORT cell_t Lookup_Interior_Cell_In_Lists(Domain *d, cxindex cid, Thread **);
FLUENT_EXPORT cell_t Lookup_Exterior_Cell_In_Lists(Domain *d, cxindex cid, Thread **);
FLUENT_EXPORT face_t Lookup_Interface_Face_In_Lists(Domain *d, cxindex fid, Thread **);
FLUENT_EXPORT face_t Lookup_Exterior_Face_In_Lists(Domain *d, cxindex fid, Thread **);
FLUENT_EXPORT Node *Lookup_Interface_Node_In_Lists(Domain *domain, cxindex vid);
FLUENT_EXPORT Node *Lookup_Exterior_Node_In_Lists(Domain *domain, cxindex vid);
FLUENT_EXPORT Node *Lookup_Corner_Node_In_Lists(Domain *domain, cxindex vid);

FLUENT_EXPORT cell_t Lookup_Interior_Cell(Domain *d, cxindex cid, Thread **);
FLUENT_EXPORT cell_t Lookup_Exterior_Cell(Domain *d, cxindex cid, Thread **);

FLUENT_EXPORT int Local_Max_Interior_Cell_List_Size(Domain *d);
FLUENT_EXPORT int Local_Max_Exterior_Cell_List_Size(Domain *d);
FLUENT_EXPORT int Local_Max_Interface_Face_List_Size(Domain *d);
FLUENT_EXPORT int Local_Max_Helper_Interface_Face_List_Size(Domain *d);
# if RP_HANG
FLUENT_EXPORT int Local_Max_Parent_Interior_Cell_List_Size(Domain *d);
FLUENT_EXPORT int Local_Max_Parent_Exterior_Cell_List_Size(Domain *d);
FLUENT_EXPORT int Local_Max_Parent_Interface_Face_List_Size(Domain *d);
#  if RP_EDGE
FLUENT_EXPORT int Local_Max_Interface_Edge_List_Size(Domain *d);
FLUENT_EXPORT int Local_Max_Corner_Edge_List_Size(Domain *d);
FLUENT_EXPORT int Local_Max_Parent_Interface_Edge_List_Size(Domain *d);
FLUENT_EXPORT int Local_Max_Parent_Corner_Edge_List_Size(Domain *d);
#  endif
# endif /* RP_HANG */
FLUENT_EXPORT int Local_Max_Exterior_Face_List_Size(Domain *d);
FLUENT_EXPORT int Local_Max_Interior_BFace_List_Size(Domain *d);
FLUENT_EXPORT int Local_Max_Exterior_BFace_List_Size(Domain *d);
FLUENT_EXPORT int Local_Max_Corner_Node_List_Size(Domain *d);
FLUENT_EXPORT int Local_Max_Interface_Node_List_Size(Domain *d);
FLUENT_EXPORT int Local_Max_Exterior_Node_List_Size(Domain *d);
#if RP_POLYHEDRA
FLUENT_EXPORT int Local_Max_Interior_Cell_Face_Node_Count(Domain *d);
FLUENT_EXPORT int Local_Max_Exterior_Cell_Face_Node_Count(Domain *d);
FLUENT_EXPORT int Local_Max_Exterior_Cell_Face_Count(Domain *d);
FLUENT_EXPORT int Local_Max_Exterior_Cell_Face_Shadow_Count(Domain *d);
FLUENT_EXPORT int Local_Max_Parent_Exterior_Cell_Face_Count(Domain *d);
#endif
FLUENT_EXPORT int local_count_ext_c(Domain *d);
FLUENT_EXPORT int local_count_nosolve_ext_c(Domain *d);

FLUENT_EXPORT cxboolean Interface_Face_Cell_P(const cell_t, const Thread *);
FLUENT_EXPORT cxboolean Interface_Node_Cell_P(Domain *domain, const cell_t c, const Thread *);

FLUENT_EXPORT void Init_Parallel_Injections(Domain *domain, Dom_Neighbor *neighbor);
FLUENT_EXPORT int sv_allocated_on_any_thread(int nv, Domain *domain);

# define MAX_BUFF_LEN 16
# define BUFF_LEN MAX_BUFF_LEN
# define FREE_BUFF_MEM(ptr,len) \
  if (NNULLP(ptr)) FREE_ARRAY((char *)ptr); \
  ptr = NULL; \
  len=0
# define BUFF_MEM_CHK(i,len,ptr,type) \
  if ((i)>=len) \
    { \
       len = ((i) >= (len+BUFF_LEN)) ? ((i)+1)  : (len+BUFF_LEN); \
       ptr = (type *)REALLOC_ARRAY((char *)ptr,sizeof(type)*len); \
       if (NULLP(ptr)) \
   CX_Primitive_Error("Parallel Buffer: out of memory"); \
   }

# define Global_Max_Interior_Cell_List_Size(d) \
    PRF_GIHIGH1(Local_Max_Interior_Cell_List_Size(d))
# define Global_Max_Exterior_Cell_List_Size(d) \
    PRF_GIHIGH1(Local_Max_Exterior_Cell_List_Size(d))
# define Global_Max_Interface_Face_List_Size(d) \
    PRF_GIHIGH1(Local_Max_Interface_Face_List_Size(d))
#  define Global_Max_Helper_Interface_Face_List_Size(d) \
    PRF_GIHIGH1(Local_Max_Helper_Interface_Face_List_Size(d))
# if RP_HANG
#  define Global_Max_Parent_Interior_Cell_List_Size(d) \
    PRF_GIHIGH1(Local_Max_Parent_Interior_Cell_List_Size(d))
#  define Global_Max_Parent_Exterior_Cell_List_Size(d) \
    PRF_GIHIGH1(Local_Max_Parent_Exterior_Cell_List_Size(d))
#  define Global_Max_Parent_Interface_Face_List_Size(d) \
    PRF_GIHIGH1(Local_Max_Parent_Interface_Face_List_Size(d))
#  if RP_EDGE
#   define Global_Max_Interface_Edge_List_Size(d) \
     PRF_GIHIGH1(Local_Max_Interface_Edge_List_Size(d))
#   define Global_Max_Corner_Edge_List_Size(d) \
     PRF_GIHIGH1(Local_Max_Corner_Edge_List_Size(d))
#   define Global_Max_Parent_Interface_Edge_List_Size(d) \
     PRF_GIHIGH1(Local_Max_Parent_Interface_Edge_List_Size(d))
#   define Global_Max_Parent_Corner_Edge_List_Size(d) \
     PRF_GIHIGH1(Local_Max_Parent_Corner_Edge_List_Size(d))
#  endif
# endif /* RP_HANG */
# define Global_Max_Exterior_Face_List_Size(d) \
    PRF_GIHIGH1(Local_Max_Exterior_Face_List_Size(d))
# define Global_Max_Interior_BFace_List_Size(d) \
    PRF_GIHIGH1(Local_Max_Interior_BFace_List_Size(d))
# define Global_Max_Exterior_BFace_List_Size(d) \
    PRF_GIHIGH1(Local_Max_Exterior_BFace_List_Size(d))
# define Global_Max_Interface_Node_List_Size(d) \
    PRF_GIHIGH1(Local_Max_Interface_Node_List_Size(d))
# define Global_Max_Exterior_Node_List_Size(d) \
    PRF_GIHIGH1(Local_Max_Exterior_Node_List_Size(d))
# define Global_Max_Corner_Node_List_Size(d) \
    PRF_GIHIGH1(Local_Max_Corner_Node_List_Size(d))
#endif /* RP_NODE */
#if RP_POLYHEDRA
# define Global_Max_Exterior_Cell_Face_Node_Count(d) \
    PRF_GIHIGH1(Local_Max_Exterior_Cell_Face_Node_Count(d))
# define Global_Max_Exterior_Cell_Face_Count(d) \
    PRF_GIHIGH1(Local_Max_Exterior_Cell_Face_Count(d))
# define Global_Max_Exterior_Cell_Face_Shadow_Count(d) \
    PRF_GIHIGH1(Local_Max_Exterior_Cell_Face_Shadow_Count(d))
# define Global_Max_Parent_Exterior_Cell_Face_Count(d) \
    PRF_GIHIGH1(Local_Max_Parent_Exterior_Cell_Face_Count(d))
#endif

#if PARALLEL
FLUENT_EXPORT int global_count_ext_c(Domain *d, cxboolean with_host);
FLUENT_EXPORT int global_count_nosolve_ext_c(Domain *d, cxboolean with_host);
#endif
#if RP_NODE
FLUENT_EXPORT void Free_Unused_Interface_Corner_Nodes(Domain *);
FLUENT_EXPORT void Free_Domain_Exterior_Face_List(Domain *);
FLUENT_EXPORT void Free_Exterior_Nodes(Domain *, int);
FLUENT_EXPORT void Free_Exterior_Faces(Domain *);
FLUENT_EXPORT void Free_Exterior_Cells(Domain *);
#if RP_3D
FLUENT_EXPORT void Free_Exterior_Interior_BFaces(Domain *d);
#endif
FLUENT_EXPORT void Resolve_Node_Lists(Domain *);
# if sys_debug
FLUENT_EXPORT void Check_Cell_Face_Relation(Domain *);
FLUENT_EXPORT void Check_Cell_Face_Nodes(Domain *);
FLUENT_EXPORT cxboolean Check_Uniqueness_Exterior_Cells (Domain *);
FLUENT_EXPORT cxboolean Check_Exterior_Node_Count (Domain *);
FLUENT_EXPORT void Print_Exterior_Cells (Domain *);
FLUENT_EXPORT void Print_Exterior_Cell_Nodes (Domain *);
FLUENT_EXPORT void Print_Exterior_Cell_Faces (Domain *);
FLUENT_EXPORT void Print_Exterior_Face_Nodes (Domain *);
FLUENT_EXPORT void Check_Face_Uniqueness (Domain *);
FLUENT_EXPORT void Check_Node_Uniqueness (Domain *);
# endif
FLUENT_EXPORT void Add_SI_Bridge_Nodes_to_Interface_and_Corner(Domain *);

#include "grid_par_ext.h"

#endif /* RP_NODE */

#endif /* _FLUENT_GRID_PAR_H */
