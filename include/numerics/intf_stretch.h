/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _INTF_STRETCH_H
#define _INTF_STRETCH_H

#define STRETCHED_INTERFACES_AVAILABLE_P(si) \
  (STRETCHED_INTERFACE_P(si) &&              \
   NNULLP(SI_TI_STR_OBJP(si)))

#define STRETCHED_BOUNDARIES_AVAILABLE_P(si)        \
  (STRETCHED_INTERFACE_P(si) &&                     \
   NNULLP(SI_T0_STR_OBJP(si)) &&                    \
   NNULLP(SI_T1_STR_OBJP(si)) &&                    \
   NNULLP(SI_T0_STR(si)) &&                         \
   NNULLP(SI_T1_STR(si)))

#define SLIDING_BOUNDARY_COPIES_EXIST(si)          \
  (NNULLP(SI_T0_STR_OBJP(si)) &&                   \
   NNULLP(SI_T1_STR_OBJP(si)) &&                   \
   NNULLP(SI_T0_STR(si)) &&                        \
   NNULLP(SI_T1_STR(si)))

#define NO_STRETCHED_BOUNDARIES_P(si)           \
  (STRETCHED_INTERFACE_P(si) &&                 \
   NULLP(SI_T0_STR_OBJP(si)) &&                 \
   NULLP(SI_T1_STR_OBJP(si)))

#define NO_GHOST_THREADS_P(si)                                  \
  ((THREAD_T0(SI_T0(si)) == THREAD_T0(SI_T0_STR(si))) &&        \
   (THREAD_T0(SI_T1(si)) == THREAD_T0(SI_T1_STR(si))))

#define GHOST_THREADS_EXISTS_P(si)                              \
  ((THREAD_T0(SI_T0(si)) != THREAD_T0(SI_T0_STR(si))) &&        \
   (THREAD_T0(SI_T1(si)) != THREAD_T0(SI_T1_STR(si))))

#define THREAD_ORIG THREAD_TMP1
#define NNULL_MARK_P(mark)((mark) == 1)

#define ONE_LAYER_GHOST_CELL_THREAD_P(t)                                \
  (GHOST_CELL_THREAD_P(t) && (Cell_Element_Type)THREAD_ELEMENT_TYPE(t) == GHOST_CELL)
#define MULTIPLE_LAYER_GHOST_CELL_THREAD_P(t)                           \
  (GHOST_CELL_THREAD_P(t) && (Cell_Element_Type)THREAD_ELEMENT_TYPE(t) != GHOST_CELL)

#define LEFT_EDGE_NODE_MARK    0x10
#define RIGHT_EDGE_NODE_MARK   0x20
#define TEMP_NODE_MARK         0x40
#define EDGE_NODE_MARK         0x11
#define CORNER_NODE_MARK       0x12
#define LOWEST_THETA_NODE_MARK 0x13

#define GC_SCALAR_SOURCE_GLOBAL 1

typedef struct cyl_coordinate
{
  real radius;
  real theta;
} cyl_coord_t;

typedef struct low_up_vertex
{
  cyl_coord_t low;
  cyl_coord_t up;
} low_up_vertex_t;

/*Thread corner radius, theta coordinates for GTI interfaces*/
/*Left and right side could be different here than base on the left and right edge marking.
For the below structure, left side will be the one making the largest angle and right side
will be the one with the smallest angle. This angle is measured between 0 to 360 degrees. */
typedef struct th_cnr_cyl_vertex
{
  low_up_vertex_t *lft;             /*Thread's left edge upper and lower*/
  low_up_vertex_t *rgt;             /*Thread's left edge upper and lower*/
} th_cnr_cyl_vertex_t;

FLUENT_EXPORT void Update_Ghost_Coeffs (Domain *, int sys_id);
FLUENT_EXPORT void Reverse_Ghost_Coeffs (Domain *);
FLUENT_EXPORT void Update_Ghost_Indices(Domain *, int sys_id, cxboolean df);
FLUENT_EXPORT void Update_PBCpld_Ghost_Coeffs (Domain *);
FLUENT_EXPORT void Reverse_PBCpld_Ghost_Coeffs (Domain *);
FLUENT_EXPORT void Update_Cpld_Ghost_Coeffs (Domain *);
FLUENT_EXPORT void Update_Cpld_Ghost_Indices(Domain *);

FLUENT_EXPORT void Update_Ghost_Original_Source(Domain *);
FLUENT_EXPORT void Update_Ghost_Original_Turb_Source(Domain *, Svar, Svar);
#if GC_SCALAR_SOURCE_GLOBAL
FLUENT_EXPORT void Update_Ghost_Original_Scalar_Source(Domain *, Svar);
#else
FLUENT_EXPORT void Update_Ghost_Original_Scalar_Source(Domain *, Svar, Svar);
#endif
FLUENT_EXPORT void Transform_Vector_To_Ghost_Storage(Thread *, ND_VEC(Svar, Svar, Svar), cxboolean);
FLUENT_EXPORT void Transform_Matrix_To_Ghost_Storage(Thread *, ND_VEC(Svar, Svar, Svar), cxboolean);
FLUENT_EXPORT void Copy_Scalar_To_Ghost_Storage (Thread *, Svar, cxboolean);
FLUENT_EXPORT void Rotate_Vector_To_Ghost_Storage (Thread *, Svar, cxboolean);
FLUENT_EXPORT void Scale_Vector_To_Ghost_Storage(Thread *, ND_VEC(Svar, Svar, Svar), cxboolean);

FLUENT_EXPORT void Fill_Ghost_Cells_Qs (Domain *);
FLUENT_EXPORT void Fill_Ghost_Cells_RG_Qs (Domain *);
FLUENT_EXPORT void Fill_Ghost_Cells_G_Qs (Domain *);

FLUENT_EXPORT void Fill_Ghost_Cells_scalar (Domain *, Svar);
FLUENT_EXPORT void Fill_Ghost_Cells_vector (Domain *, Svar, cxboolean, cxboolean);

FLUENT_EXPORT void Fill_Ghost_Cells_Vector_Comp (Domain *, ND_VEC(Svar, Svar, Svar) );
FLUENT_EXPORT void Fill_Ghost_Cells_Tensor_Comp (Domain *, ND_VEC(Svar, Svar, Svar), cxboolean, cxboolean);

FLUENT_EXPORT void Create_Stretched_Boundary_Threads(Domain *);
FLUENT_EXPORT void Create_Stretched_Interface(Sliding_interface *, Domain *);
FLUENT_EXPORT void Create_Stretched_NCI_Threads(Domain *);
FLUENT_EXPORT void Update_Ghost_Storage_From_Stretched_Threads(Domain *);
FLUENT_EXPORT void Update_Ghost_Cell_Storage(Domain *);
FLUENT_EXPORT void Delete_SI_Ghost_Cell_Threads (Sliding_interface *, Domain *);
FLUENT_EXPORT void Fill_Sliding_Boundary_Vertex_Pairs (Sliding_interface *, Domain *);
FLUENT_EXPORT int Count_Stretched_Interfaces(Domain *);
FLUENT_EXPORT int Count_Mixing_Interfaces(Domain *);
FLUENT_EXPORT int Count_Unequal_Pitch_Interfaces(Domain *);

FLUENT_EXPORT void Thread_Sliding_Boundary_Copies(Domain *, cxboolean, cxboolean);
FLUENT_EXPORT void Assign_Interface_Parents (Sliding_interface *);
FLUENT_EXPORT void Fill_Ghost_Cell_Links (Domain *);

FLUENT_EXPORT void Flip_Interface_Parent_Faces(Thread *);
FLUENT_EXPORT cxboolean Check_Ghost_Cells(Domain *, cxboolean);
FLUENT_EXPORT void Set_Original_Threads_In_Ghost(Domain *);
#if RP_NODE
FLUENT_EXPORT void Create_Real_Cells_Of_Ghost_Cells_In_Ext (Domain *);
FLUENT_EXPORT void Mark_Real_Cells_Of_Ghost_Cells_Refuse (Domain *);
FLUENT_EXPORT void Exchange_Ghost_Cell_Links(Domain *);
#endif
FLUENT_EXPORT void Fill_Ghost_Cell_Partition(Domain *);

#endif  /* _INTF_STRETCH_H */
