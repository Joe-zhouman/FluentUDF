/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_GRID_H
#define _FLUENT_GRID_H

#include "dll.h"

/*
 * used for collection of entities to other entities
 */
#if PARALLEL && RP_3D && RP_SHELL
#define EDGE_LIST_SHELL(e) ((e)->e3.asEntity)
#endif
#define C_LIST(c,t)C_STORAGE(c,t,SV_C_LIST,struct entity_struct **)

#define ENTITY_LENGTH(l)((l)[0].as.number)
#define ENTITY_FACE(l,n)((l)[1+2*(n)].as.f)
#define ENTITY_CELL(l,n)((l)[1+2*(n)].as.c)
#define ENTITY_THREAD(l,n)((l)[1+2*(n)+1].as.t)

#if RP_NODE
#if RP_3D
#define EXT_ENTITY_SIZE 4
#else
#define EXT_ENTITY_SIZE 3
#endif
# define ENTITY_EXT_LENGTH(l) ((l)[1+2*ENTITY_LENGTH(l)].as.number)
# define ENTITY_EXT_FACE_ID(l,i) ((l)[2*(1+ENTITY_LENGTH(l)) + EXT_ENTITY_SIZE*i ].as.number)
# define ENTITY_EXT_FACE_THREAD_ID(l,i)  ((l)[2*(1+ENTITY_LENGTH(l)) + EXT_ENTITY_SIZE*i+1].as.number)
# define ENTITY_EXT_FACE_NODE1_ID(l,i)   ((l)[2*(1+ENTITY_LENGTH(l))+ EXT_ENTITY_SIZE*i + 2].as.number)
# define ENTITY_EXT_FACE_NODE2_ID(l,i)   ((l)[2*(1+ENTITY_LENGTH(l))+ EXT_ENTITY_SIZE*i + EXT_ENTITY_SIZE-1].as.number)

#endif

#if PARALLEL && RP_SHELL && RP_3D
#define ENTITY_PART(l,n)((l)[1+2*(n)].part)
#endif


# define PRISM_FACE_CELL_P(c, tc, f, tf)                                       \
    (C_NFACES(c, tc) == (F_NNODES(f, tf) + 2) && C_TYPE(c, tc) != PYRAMID_CELL)

/* used by remeshing and polyhedra code */
typedef struct patch_face_struct
{
  Thread *tf;
  int nv;
  Node *v[MAX_NODES_PER_FACE];
} patch_f;

#define PATCH_THREAD(pf)  ((pf).tf)
#define PATCH_NV(pf)      ((pf).nv)
#define PATCH_NODES(pf,n) ((pf).v[n])

FLUENT_EXPORT char *Cell_Type_Name(int);
FLUENT_EXPORT char *Face_Type_Name(int);
FLUENT_EXPORT int Face_Type_Nedges(int);



FLUENT_EXPORT char *Get_Zone_Name(Thread *);
#if RP_HANG
FLUENT_EXPORT int Face_Type_Nkids(int);
FLUENT_EXPORT int Cell_Type_Nkids(int);
#endif

FLUENT_EXPORT int Cell_Nkids_PUMA(cell_t, Thread *);

FLUENT_EXPORT Cell_Element_Type Domain_Cell_Type(Domain *);
FLUENT_EXPORT void Reset_Thread_Element_Type(Domain *);
#if !RP_HOST
FLUENT_EXPORT Cell_Element_Type Thread_Cell_Type(Thread *);
FLUENT_EXPORT Face_Element_Type Thread_Face_Type(Thread *);
#endif

FLUENT_EXPORT void Init_Node_Faces_Of_Thread_List (Domain *, Objp *, Svar);
FLUENT_EXPORT void Fill_Node_Faces_Of_Thread_List (Domain *, Objp *, Svar);
FLUENT_EXPORT void Fill_All_Node_Faces_Of_Thread_List (Domain *, Objp *, Svar);
#if PARALLEL
FLUENT_EXPORT void Fill_Exterior_Node_Faces_Of_Thread_List(Domain *, Objp *,
                                                           Svar);
#endif
FLUENT_EXPORT void Free_Node_Faces_Of_Thread_List (Domain *, Objp *, Svar);
FLUENT_EXPORT void Fill_Node_Faces_Of_Face_List(Domain *, Objp *, Svar);
FLUENT_EXPORT void Free_Node_Faces_Of_Face_List(Domain *, Objp *, Svar);
FLUENT_EXPORT face_t f_neighbor_nv (face_t, Thread *, int, int *, Thread **, Svar);
FLUENT_EXPORT face_t f_neighbor (face_t, Thread *, int, int *, Thread **);
FLUENT_EXPORT void Init_Node_Cells_Of_Thread_List(Domain *, Objp *, Svar);
FLUENT_EXPORT void Fill_Node_Cells_Of_Thread_List(Domain *, Objp *, Svar);
FLUENT_EXPORT void Fill_All_Node_Cells_Of_Thread_List(Domain *, Objp *, Svar);
#if PARALLEL
FLUENT_EXPORT void Fill_Exterior_Node_Cells_Of_Thread_List(Domain *, Objp *,
                                                           Svar);
#endif
FLUENT_EXPORT void Free_Node_Cells_Of_Thread_List(Domain *, Objp *, Svar);

FLUENT_EXPORT void Init_Cell_Objp_Of_Thread_List(Domain *, Objp *, Svar);
FLUENT_EXPORT void Free_Cell_Objp_Of_Thread_List(Domain *, Objp *, Svar);

FLUENT_EXPORT void Fill_All_Cell_Node_Cells_Of_Thread_List(Domain *, Objp *, Svar, Svar);

FLUENT_EXPORT cell_t Find_Cell_At_Location (Thread *, cell_t, real *v, int, cxboolean, cxboolean);

FLUENT_EXPORT cxboolean is_v_in_e(Node *const, Edge *const);
FLUENT_EXPORT cxboolean is_v_in_f(Node *const, const face_t, Thread *const);
FLUENT_EXPORT int get_v_index_in_f(Node *const, const face_t, Thread *const);
FLUENT_EXPORT cxboolean is_v_in_all_f_kids(Node *const, const face_t, Thread *const);
FLUENT_EXPORT cxboolean is_v_in_all_c_kids(Node *const, const cell_t, Thread *const);
FLUENT_EXPORT cxboolean is_v_in_c(Node *const, const cell_t, Thread *const);
FLUENT_EXPORT cxboolean is_v_in_c_side(Node *const, const cell_t, Thread *const, const int);
FLUENT_EXPORT cxboolean is_v_in_c_or_kids(Node *const, const cell_t, Thread *const);
#if RP_3D
FLUENT_EXPORT int get_node_edge_index_in_f (face_t, Thread *, Node *, Node *);
#define face_has_edge(_f,_tf,_v0,_v1) \
  (get_node_edge_index_in_f (_f, _tf, _v0, _v1) >= 0)
FLUENT_EXPORT face_t get_face_with_edge_in_list_not_face (Objp *,
                                                          Node *, Node *,
                                                          face_t, Thread *,
                                                          Thread **, int *);
#endif
FLUENT_EXPORT int number_of_adjacent_edges (face_t, Thread *, int, Objp *);
FLUENT_EXPORT cxboolean is_e_in_f(Edge *const, const face_t, Thread *const);
FLUENT_EXPORT cxboolean is_e_or_kids_in_f(Edge *const, const face_t, Thread *const);
FLUENT_EXPORT cxboolean is_e_kid_of_e(Edge *const, Edge *const);
FLUENT_EXPORT cxboolean is_f_in_f_kids(const face_t, Thread *const, const face_t, Thread *const);
FLUENT_EXPORT cxboolean is_f_in_c(const face_t, Thread *const, const cell_t, Thread *const);
FLUENT_EXPORT cxboolean is_f_in_c_or_kids(const face_t, Thread *const,
                                          const cell_t, Thread *const);
FLUENT_EXPORT cxboolean is_c_in_c_kids(const cell_t, Thread *const, const cell_t, Thread *const);

FLUENT_EXPORT cxboolean cell_has_parent_face (const cell_t, const Thread *);
FLUENT_EXPORT Node *get_v_in_f(Node *const, const face_t, Thread *const);
FLUENT_EXPORT Node *get_v_in_f_kids(Node *const, const face_t, Thread *const);
FLUENT_EXPORT Node *get_v_in_f_not_v(const face_t, Thread *const, Node *const);
FLUENT_EXPORT Node *get_v_in_f_and_f_not_v(const face_t, Thread *const,
                                           const face_t, Thread *const,
                                           Node *const);

FLUENT_EXPORT Node *get_v_in_c_not_in_f(const cell_t, Thread *const,
                                        const face_t, Thread *const);
FLUENT_EXPORT Edge *get_e_in_f(Edge *const, const face_t, Thread *const);
FLUENT_EXPORT Edge *get_e_in_f_kids(Edge *const, const face_t, Thread *const);

FLUENT_EXPORT face_t get_opposing_f_in_c (cell_t, Thread *, face_t, Thread *, Thread **);
FLUENT_EXPORT Node *get_opposing_v_in_c (Node *, face_t, Thread *, cell_t, Thread *);
#if RP_2D
FLUENT_EXPORT face_t get_f_in_c_w_v_not_f (cell_t, Thread *, Node *, face_t, Thread *, Thread **);
#else
FLUENT_EXPORT face_t get_f_in_c_w_vs_not_f (cell_t, Thread *, Node *, Node *, face_t, Thread *, Thread **);
#endif

FLUENT_EXPORT void get_f_kid_w_v(face_t *, Thread **,
                                 const face_t, Thread *const,
                                 Node *const);

FLUENT_EXPORT void get_f_in_c_w_f_kid(face_t *, Thread **,
                                      const face_t, Thread *const,
                                      const cell_t, Thread *const);
FLUENT_EXPORT void get_f_in_c_w_f_si_kid(face_t *, Thread **,
                                         const face_t, Thread *const,
                                         const cell_t, Thread *const);
FLUENT_EXPORT face_t get_f_in_c_w_e_not_f(const cell_t, Thread *const,
                                          Edge *,
                                          const face_t, Thread *const,
                                          Thread **);

FLUENT_EXPORT void get_c_kid_w_f(cell_t *, Thread **,
                                 const cell_t, Thread *const,
                                 const face_t, Thread *const);
FLUENT_EXPORT cell_t get_c_in_f_not_c(const face_t, Thread *const,
                                      const cell_t, Thread *const,
                                      Thread **);
FLUENT_EXPORT Objp *get_c_neighbors (const cell_t, Thread *const, void **);

FLUENT_EXPORT Objp *get_ivs_on_fe(const face_t, Thread *const, const int);
#define free_vs_on_fe(l) free_o_list(l)

FLUENT_EXPORT Objp *get_fs_with_e(const face_t, Thread *const, const int);
FLUENT_EXPORT Objp *get_fs_with_inclusive_fe(const face_t f, Thread *const t, const int i);
#define free_fs_with_e(l) free_o_list(l)

FLUENT_EXPORT Edge *get_inclusive_e_on_fe(const face_t, Thread *const, const int,
                                          face_t *, Thread **, int *);
FLUENT_EXPORT Objp *get_vs_with_inclusive_fe(face_t, Thread *, int, Objp *);

FLUENT_EXPORT cxboolean get_valid_face_neighbor (face_t *, Thread **, int *,
                                                 face_t, Thread *, int, Objp *);


FLUENT_EXPORT void replace_v_in_f(Node *const, const face_t, Thread *const, Node *const);
FLUENT_EXPORT void replace_v_in_c(Node *const, const cell_t, Thread *const, Node *const);

FLUENT_EXPORT void replace_f_in_c(const face_t, Thread *const,
                                  const cell_t, Thread *const,
                                  const face_t, Thread *const);
FLUENT_EXPORT void replace_f_in_f_kids(const face_t, Thread *const,
                                       const face_t, Thread *const,
                                       const face_t, Thread *const);

FLUENT_EXPORT void replace_c_in_f(const cell_t, Thread *const,
                                  const face_t, Thread *const,
                                  const cell_t, Thread *const);
FLUENT_EXPORT void replace_c_in_c_kids(const cell_t, Thread *const,
                                       const cell_t, Thread *const,
                                       const cell_t, Thread *const);

FLUENT_EXPORT cxboolean periodic_face_thread_p(Domain *d);
FLUENT_EXPORT cxboolean coupled_face_thread_p(Domain *d);

FLUENT_EXPORT void IntersectV(double *, double *, double *, double *, double *);
FLUENT_EXPORT void Project_Coord_On_Plane (real *, real *, real *);

#if RP_2D
FLUENT_EXPORT void PerpendicularV(double *, double *);
#endif

FLUENT_EXPORT void initialize_CellAratio(Domain *domain, Svar sv);
FLUENT_EXPORT void initialize_CellAratio_if_needed(Domain *domain);
FLUENT_EXPORT void initialize_CellMindist(Domain *domain, Svar sv);

FLUENT_EXPORT int Fill_Domain(Domain *d);
FLUENT_EXPORT void Store_Old_Node_Coords (Domain *);
FLUENT_EXPORT void Clear_Node_Shadows (Domain *);
FLUENT_EXPORT void Fill_Node_Shadows (Domain *, cxboolean);
FLUENT_EXPORT void Resolve_Multiple_Periodic_Node_Shadows (Domain *d);
FLUENT_EXPORT void Mark_Periodic_Boundary_Nodes(Domain *d);
#if RP_NODE
FLUENT_EXPORT void Fill_Node_Parts(Domain *d, int mark);
#endif
FLUENT_EXPORT void Fill_Node_Marks(Domain *d, int mark);
FLUENT_EXPORT cxboolean Collect_Cells_To_Nodes(Domain *d);
FLUENT_EXPORT cxboolean Collect_Faces_To_Nodes(Domain *d, Thread *t, cxboolean, cxboolean);
FLUENT_EXPORT cxboolean Collect_Faces_To_Nodes_Local(Domain *, Objp *, cxboolean, cxboolean);
#if RP_3D && RP_NODE && PARALLEL && 0
FLUENT_EXPORT cxboolean Collect_Faces_To_Nodes_Parallel(Domain *d, Thread *t, cxboolean, cxboolean);
#endif
FLUENT_EXPORT void Free_NodeList_At_Nodes(Domain *d, Thread *t);
#define Free_Cells_At_Nodes(d) Free_NodeList_At_Nodes(d,NULL)
#define Free_Faces_At_Nodes(d,t) Free_NodeList_At_Nodes(d,t)
FLUENT_EXPORT cxboolean Collect_Faces_To_Cells(Domain *d);
FLUENT_EXPORT void Free_Faces_At_Cells(Domain *d);

FLUENT_EXPORT void Fill_Collect_Face_To_Cell(Domain *);
FLUENT_EXPORT void Free_Collect_Face_To_Cell(Domain *);
FLUENT_EXPORT void Fill_Cell_Faces(Domain *);
FLUENT_EXPORT void Fill_Face_Cell_Arrays (Domain *);
FLUENT_EXPORT int Fill_Cell_Nodes(Domain *, cxboolean);
FLUENT_EXPORT int Fill_Cell_Faces_Nodes(Domain *, cxboolean);

#if RP_EDGE
FLUENT_EXPORT Edge *find_or_create_edge(Domain *, face_t, Thread *, int);
FLUENT_EXPORT void Init_Edge_Mark (Domain *, int);
FLUENT_EXPORT void Set_Faces_Per_Edge(Domain *d);
FLUENT_EXPORT void Fill_Face_Edges (Domain *, cxboolean);
FLUENT_EXPORT void Fill_Face_Thread_Edges(Domain *d, Thread *t);
FLUENT_EXPORT void Free_Face_Thread_Edges(Domain *d, Thread *t);
FLUENT_EXPORT void Fill_Face_Thread_List_Edges (Domain *, Objp *);
FLUENT_EXPORT void Free_Face_Thread_List_Edges (Domain *, Objp *);
FLUENT_EXPORT void Mark_Thread_Faces_Per_Edge(Domain *d, Thread *t);
#if RP_3D && RP_NODE && PARALLEL && 0
FLUENT_EXPORT void Mark_Thread_Faces_Per_Edge_Parallel(Domain *d, Thread *t);
#endif
FLUENT_EXPORT cxboolean Single_Connected_Edge_P(Edge *e);
# if RP_HANG
FLUENT_EXPORT cxboolean find_edge_children(face_t, Thread *, Edge *);
FLUENT_EXPORT void Fill_Edge_Children(Domain *d);
# endif
#endif

FLUENT_EXPORT Objp *Cells_W_Node(Objp *, cell_t, Thread *, Node *, Thread *, Thread *);
FLUENT_EXPORT Objp *Cells_W_Node_F(Objp *, cell_t, Thread *, Node *);
FLUENT_EXPORT Objp *Cells_W_Node_Of_Shadow_Side(Objp *, cell_t, Thread *, Node *, int, cxindex *, Thread *);

FLUENT_EXPORT Objp *Sort_Cell_List (Objp *,
                                    int (*)(const void *, const void *),
                                    cxboolean);

FLUENT_EXPORT Thread *Find_Most_Frequent_Interior_Thread (Domain *, Thread *,
                                                          cxboolean, cxboolean);
FLUENT_EXPORT Thread *Find_Most_Frequent_Adjacent_Interior_Thread (Domain *,
                                                                   Thread *,
                                                                   int,
                                                                   cxboolean);
FLUENT_EXPORT void Fill_Interior_Face_Threads (Domain *);
FLUENT_EXPORT void Free_Interior_Face_Threads (Domain *);

FLUENT_EXPORT void Init_Node_Flags (Domain *);
FLUENT_EXPORT void Init_Periodic_Node_Flags (Domain *);
FLUENT_EXPORT void Update_Node_Flags (Domain *);
#if GRAPHICS && CORTEX
FLUENT_EXPORT void Display_Node_Flags (Domain *);
#endif

FLUENT_EXPORT void Thread_Clear_Cell_Flags (Thread *, unsigned int);
FLUENT_EXPORT void Thread_Set_Cell_Flags (Thread *, unsigned int);
FLUENT_EXPORT void Thread_Clear_Face_Flags (Thread *, unsigned int);
FLUENT_EXPORT void Thread_Set_Face_Flags (Thread *, unsigned int);
FLUENT_EXPORT void Clear_Node_Flags (Domain *, unsigned int);

FLUENT_EXPORT void Print_Domain(Domain *d, const char *);

FLUENT_EXPORT void Set_Update_Domain_Counts (cxboolean);
FLUENT_EXPORT void Update_Domain_Counts(Domain *);
#if PARALLEL
FLUENT_EXPORT void Update_Host_Domain_Counts(Domain *);
#endif
FLUENT_EXPORT void Update_Domain_Node_Count (Domain *, cxboolean);
FLUENT_EXPORT cxindex Domain_Cell_Count(Domain *);
FLUENT_EXPORT cxindex Domain_Face_Count(Domain *);
FLUENT_EXPORT int count_list_o(Objp *head);
FLUENT_EXPORT int count_thread_t(Thread *t);
FLUENT_EXPORT cxindex local_count_thread_c(Thread *t);
FLUENT_EXPORT cxindex local_count_thread_f_all(Thread *t);
FLUENT_EXPORT cxindex local_count_thread_f_once(Thread *t);
FLUENT_EXPORT cxindex global_count_nodes_on_face_thread(Thread *t);
FLUENT_EXPORT cxindex local_count_thread_f_and_fnode_once(int *, Thread *);
#if PARALLEL
FLUENT_EXPORT cxindex global_count_thread_c(Thread *t, cxboolean with_host);
FLUENT_EXPORT cxindex global_count_thread_f_all(Thread *t, cxboolean with_host);
FLUENT_EXPORT cxindex global_count_thread_f_once(Thread *t, cxboolean with_host);
#endif
FLUENT_EXPORT cxindex local_count_c(Domain *d);
FLUENT_EXPORT cxindex local_count_f_all(Domain *d);
#if RP_EDGE
FLUENT_EXPORT cxindex local_count_e(Domain *d);
#endif
FLUENT_EXPORT cxindex local_count_v(Domain *d);
FLUENT_EXPORT cxindex local_count_nosolve_c(Domain *d);
FLUENT_EXPORT cxindex local_count_nosolve_f_all(Domain *d);
#if PARALLEL
FLUENT_EXPORT cxindex local_count_f_once(Domain *d);
FLUENT_EXPORT cxindex local_count_nosolve_f_once(Domain *d);
FLUENT_EXPORT cxindex global_count_c(Domain *d, cxboolean with_host);
FLUENT_EXPORT cxindex global_count_f_all(Domain *d, cxboolean with_host);
FLUENT_EXPORT cxindex global_count_f_once(Domain *d, cxboolean with_host);
FLUENT_EXPORT cxindex global_count_v(Domain *d, cxboolean with_host);
FLUENT_EXPORT cxindex global_count_nosolve_c(Domain *d, cxboolean with_host);
FLUENT_EXPORT cxindex global_count_nosolve_f_all(Domain *d, cxboolean with_host);
FLUENT_EXPORT cxindex global_count_nosolve_f_once(Domain *d, cxboolean with_host);
#endif

#define C_SURFACE_AREA(c,t)  C_POST_VAR(c,t)
/* fine CELL_SURFACE_AREA    CELL_TMP0  -- not used anywhere */
#define SV_CELL_SURFACE_AREA SV_POST_VAR

#define C_SKEWNESS(c,t)      C_POST_VAR(c,t)
/* fine CELL_SKEWNESS        CELL_TMP0  -- not used anywhere */
#define SV_CELL_SKEWNESS     SV_POST_VAR

FLUENT_EXPORT cxindex Boundary_Node_Count(Domain *d, cxboolean with_host);

FLUENT_EXPORT void Fill_Cell_Surface_Area(Domain *d);
FLUENT_EXPORT void Fill_Cell_Eq_Volume(Domain *d);
FLUENT_EXPORT void Fill_Cell_Eq_Surface_Deviation(Domain *d);
FLUENT_EXPORT void Fill_Cell_Skewness (Domain *d);
FLUENT_EXPORT void Fill_Equiangle_Cell_Skewness (Domain *d);
FLUENT_EXPORT void Fill_Simplex_Cell_Skewness (Domain *d, Svar);
FLUENT_EXPORT void Fill_Cell_Warp (Domain *);
FLUENT_EXPORT void Fill_Face_Warp (Domain *);
FLUENT_EXPORT void Fill_Orthogonal_Quality (Domain *, Objp *);
FLUENT_EXPORT void Fill_Face_Squish (Domain *);
FLUENT_EXPORT void Fill_Cell_Squish (Domain *);

FLUENT_EXPORT real Minimum_Face_Edge_Length (face_t, Thread *);
FLUENT_EXPORT real Minimum_Face_Node_Distance (face_t, Thread *);
FLUENT_EXPORT double Face_Skewness (face_t, Thread *);
FLUENT_EXPORT void Face_Circumcenter(face_t, Thread *, double *vcen);
FLUENT_EXPORT double Cell_Circumcenter (const cell_t, const Thread *, double *);
FLUENT_EXPORT double Simplex_Cell_Skewness (cell_t c, Thread *);
FLUENT_EXPORT double Cell_Skewness (cell_t c, Thread *);
FLUENT_EXPORT double Cell_Expansion_Ratio (cell_t c, Thread *, cxboolean);
FLUENT_EXPORT double Cell_Edge_Length_Ratio (cell_t c, Thread *);
FLUENT_EXPORT real Directional_Aspect_Ratio (cell_t c, Thread *, real *);
FLUENT_EXPORT real Cell_Minimum_Distance (cell_t c, Thread *);

FLUENT_EXPORT real Aspect_Ratio (cell_t c, Thread *);
FLUENT_EXPORT real Squish (cell_t, Thread *, cxboolean, cxboolean, cxboolean);
FLUENT_EXPORT real Orthogonal_Quality (cell_t, Thread *, cxboolean, cxboolean, cxboolean, int, real);
FLUENT_EXPORT real Cell_Squish (cell_t, Thread *, cxboolean, cxboolean);
FLUENT_EXPORT cxboolean Face_Right_Handed (face_t, Thread *,
                                           cxboolean, cxboolean, int,
                                           int *);
FLUENT_EXPORT cxboolean Face_Of_Cell_Right_Handed (face_t, Thread *,
                                                   cell_t, Thread *,
                                                   cxboolean, int);
FLUENT_EXPORT cxboolean Cell_With_Right_Handed_Faces (cell_t, Thread *,
                                                      cxboolean, int);
FLUENT_EXPORT cxboolean Cell_With_Right_Handed_Faces_Self (cell_t, Thread *,
                                                           cxboolean, int);

FLUENT_EXPORT real Vector_Variation (real *, real *);
FLUENT_EXPORT real Quad_Face_Normal_Variation (const face_t, const Thread *,
                                               int *);
FLUENT_EXPORT real Face_Warp (const face_t, const Thread *);

FLUENT_EXPORT double Triangle_Skew(double *, double *, double *);
FLUENT_EXPORT double Triangle_Size(double *, double *, double *);
FLUENT_EXPORT double Circumcenter_Triangle(double *, double *, double *, double *, double *);
#if RP_3D
FLUENT_EXPORT double Tetrahedron_Size(double *, double *, double *, double *);
FLUENT_EXPORT double Tetrahedron_Skew(double *, double *, double *, double *);
FLUENT_EXPORT double Circumcenter_Tetrahedron(double *, double *, double *, double *, double *);
#endif

FLUENT_EXPORT void print_face(const face_t, Thread *const);
FLUENT_EXPORT void print_cell(const cell_t, Thread *const, cxboolean);

#if DEBUG
FLUENT_EXPORT int Solve_or_Nosolve(Thread *, int, Domain *);
#if GRAPHICS && CORTEX
FLUENT_EXPORT void Display_Domain_Labels(Domain *d);
FLUENT_EXPORT void Display_Path_Cone(float p[], float v[], float x[], float y[],
                                     float dist, int npts);
FLUENT_EXPORT void Display_Thread(Domain *, ...);
FLUENT_EXPORT void Display_Cell(cell_t, Thread *, cxboolean);
FLUENT_EXPORT void Display_Face(face_t, Thread *, cxboolean);
FLUENT_EXPORT void Display_Node(Node *);
FLUENT_EXPORT void Display_Cell_Neighbors(cell_t, Thread *);
#if RP_EDGE
FLUENT_EXPORT void Display_Edge(Edge *);
#endif
#endif
#endif /* DEBUG */

typedef struct face_cv_struct
{
  real A[ND_ND];
  real x[ND_ND];
  int n_side_faces;
  face_t side_face[4];
  Thread *side_face_thread[4];
  real side_face_area_frac[4];
} Face_CV;
FLUENT_EXPORT int get_face_cv(Face_CV *cv, const face_t, const Thread *, const cell_t, const Thread *);

FLUENT_EXPORT void get_opposite_face(face_t *f_op, Thread **tf_op, face_t f, Thread *tf,
                                     cell_t c, Thread *tc);

FLUENT_EXPORT int Order_Faces_of_Cell_by_Nodes(cell_t, Thread *);
FLUENT_EXPORT int Order_Cell_Faces(Domain *domain);

#if RP_EDGE && RP_HANG
FLUENT_EXPORT void Order_Edges_of_Face_by_Nodes(face_t, Thread *);
#endif

#if !PARALLEL
# define global_count_thread_c(t,wh) local_count_thread_c(t)
# define global_count_thread_f_all(t,wh) local_count_thread_f_all(t)
# define global_count_thread_f_once(t,wh) local_count_thread_f_once(t)
# define global_count_c(d,wh) local_count_c(d)
# define global_count_f_all(d,wh) local_count_f_all(d)
# define local_count_f_once(d) local_count_f_all(d)
# define global_count_f_once(d,wh) local_count_f_all(d)
# define global_count_v(d,wh) local_count_v(d)
# define global_count_nosolve_c(d,wh) local_count_nosolve_c(d)
# define global_count_nosolve_f_all(d,wh) local_count_nosolve_f_all(d)
# define local_count_nosolve_f_once(d) local_count_nosolve_f_all(d)
# define global_count_nosolve_f_once(d,wh) local_count_nosolve_f_all(d)
#endif

FLUENT_EXPORT void replace_cells_on_faces(const cell_t, Thread *const,
                                          const face_t, Thread *const,
                                          const cell_t, Thread *const,
                                          const uchar_fl);
FLUENT_EXPORT void replace_faces_on_neighbor_cells(const face_t, Thread *const,
                                                   const face_t, Thread *const);

FLUENT_EXPORT Node *Thread_Nodes(Domain *);
FLUENT_EXPORT void Fill_Face_Parent(Domain *);
FLUENT_EXPORT void Fill_Cell_Parent(Domain *);
FLUENT_EXPORT void Free_Face_Parent(Domain *);
FLUENT_EXPORT void Free_Cell_Parent(Domain *);
#if !RP_HOST
FLUENT_EXPORT void Total_Cell_Usage(Domain *, long long int *, double *, long long int *, double *);
FLUENT_EXPORT void Total_Face_Usage(Domain *, long long int *, double *, long long int *, double *);
FLUENT_EXPORT int Get_Number_Nodes_Used(Domain *);
FLUENT_EXPORT int Get_Number_Objps_Used(void);
FLUENT_EXPORT real Get_A_By_Es(face_t, Thread *);
#endif

#if RP_POLYHEDRA
FLUENT_EXPORT void Fill_Thread_Poly_Cell_Faces (Domain *, Thread *);
FLUENT_EXPORT void Fill_Thread_Poly_Cell_Nodes (Domain *, Thread *);
#endif
FLUENT_EXPORT void Model_Initialize_grid(void);
#endif /* _FLUENT_GRID_H */

FLUENT_EXPORT cxboolean is_periodic_sandwich(Thread *, Thread * );
FLUENT_EXPORT cxboolean is_symmetry_sandwich(Thread *, Thread * );
