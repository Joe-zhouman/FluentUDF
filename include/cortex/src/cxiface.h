/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/*
 *  cxiface.h
 *  Included by cx.h only
 */

#ifndef Cxiface_h
#define Cxiface_h

#include "itype.h"   /* cxindex */

/* Cell type definitions. Note these do not match rampant/uns types. */
#define CX_CELL_POLY    0       /* n nodes, m faces */
#define CX_CELL_TRI 1 /* 3 nodes, 3 faces */
#define CX_CELL_QUAD  2 /* 4 nodes, 4 faces */
#define CX_CELL_TET     3 /* 4 nodes, 4 faces */
#define CX_CELL_HEX 4 /* 8 nodes, 6 faces */
#define CX_CELL_PYRAMID 5 /* 5 nodes, 5 faces */
#define CX_CELL_WEDGE 6       /* 6 nodes, 5 faces */

/* Compatibility */
#define POLY    CX_CELL_POLY
#define TRI CX_CELL_TRI
#define QUAD  CX_CELL_QUAD
#define TET CX_CELL_TET
#define HEX CX_CELL_HEX
#define PYR CX_CELL_PYRAMID
#define WEDGE CX_CELL_WEDGE

/* MAX_FACE_NODE is also present in cxgcontour.c and lcx.c.
   Change here also means change there */
#define MAX_FACE_NODES 256
#define MAX_CELL_NODES 1024

#if WIN64
typedef ULONG_PTR CX_Node_Id;
#else
typedef unsigned long CX_Node_Id;
#endif
typedef int CX_Face_Id;

#define X_DIM 0
#define Y_DIM 1
#define Z_DIM 2

/* CX_Cell_Id definition; Union of Cell_IDs due to all solvers */
#define CELL_COMPATIBILITY  1

typedef union cell_id_struct
{
  cxindex c;
  /* struct dv_struct    --- not used anywhere (?)
   * {
   *   long c;
   *   short sc;
   * } dv;
   */
  struct
  {
    void *t;   /* Thread, cell_t, face_t: not available here in cortex... */
    int   f;   /* Do we need f and c separately, with just a single *t ...?? */
    int   c;   /* IF we put them in a union, make sure to never set both..!! */
  } ct;  /* cell/thread pair */
} CX_Cell_Id;

/* CX_Edge struct hangs off a node temp in the solvers.  The first node
 * in all these edges is the node that it hangs off of.
 */
typedef struct edge_str
{
  CX_Node_Id    n;  /* the second node that forms an edge. */
  struct edge_str   *next;
  float   value;  /* > 1 isovalues on same edge ? */
  int     tag;   /* this is the temp. */
} CX_Edge;


/* ***********************************************
 * TAG ( face_def )
 *
 *  Cell pointer and face within cell.
 */
typedef struct CX_Face_Def
{
  CX_Cell_Id  c;
  CX_Face_Id  fNum;
  struct CX_Face_Def  *prev;
  struct CX_Face_Def  *next;
} CX_Face_Def;


typedef struct interpolation_vector
{
  int nid;
  float wt;
} ip_vec;

/* A single data point on a surface */
typedef struct Surface_Point_Struct
{
  short nc;   /* number of nodes in cell contributing to interpolation */
  ip_vec *ip;     /* (pointer to) interpolation vector*/
  CX_Cell_Id  cell; /* (one of the) cell(s) containing  point */
} Surf_Point;

/* Used for maintaining and sending compact surface  descriptions to Cortex.
 *  For each facet, the facets list contains the number of points and indices
 *  of those points.
 */

typedef struct Surface_Struct
{
  Surf_Point  *points;    /* points to array of np points */
  ip_vec *ip;             /* (pointer to) interpolation vector*/
  int *facets;            /* array of length nfl */
  CX_Cell_Id *cells;    /* cell pointers for faces in surface */
  int nf;     /* size of facet array */
  int np;     /* number of distinct points in the surface */
  int nfl;      /* size of facets list */
  int nc_sum;     /* sum of cell nodes (over all point cells) */
  int nloops;                   /* number of loops (in curvi-linear surfaces)*/
  int n_ext_facets;   /* any intersection with any exterior cell of this partition?
                       * --> reason enough to try to sample particles at this plane.
                       */

#define CXSURFACE_TYPE_UNKNOWN  0
#define CXSURFACE_TYPE_CELLZONE 1
#define CXSURFACE_TYPE_FACEZONE 2
#define CXSURFACE_TYPE_LB_BOUNDARY_FACEZONE 3

  short srfType;    /* type of surface */
  cxboolean periodic;   /* set if the surface is periodic */
  void *data;     /* depends upon type */

  cxboolean plane_bounded;      /* surface is a plane and bounded */
  float plane_pts[3][3];        /* points needed to compute boundedness of planes */

#if CX_NODE
  /* [0-based] prefix sums of surface chunks in nodes*/
  int point_sum, facelist_sum, face_sum;
#endif
} Surface;


extern FLUENT_EXPORT Surface *SurfaceList;
extern FLUENT_EXPORT int maxSurfaceId;  /* Sync'd with maxCortexSurfaceId in cxserv.h */

/* Surface Kernel*/

/* Basic visualization kernel functions provided by the solver */


typedef enum
{
  SVFIELD_CURRENT,
  SVFIELD_DENSITY,
  SVFIELD_U_VELOCITY,
  SVFIELD_V_VELOCITY,
  SVFIELD_W_VELOCITY,
  SVFIELD_VISCOSITY,
  SVFIELD_PRESSURE,
  SVFIELD_TKE,
  SVFIELD_MASS_FLUX,
  SVFIELD_ROU, /* needed for multiphase mass flow rate calculation */
  SVFIELD_ROV,
  SVFIELD_ROW,
  SVFIELD_CUSTOM_VEC,
  SVFIELD_POWERDEN
} CX_Field_Id;

#define svboolean 0
#define svfloat 1
#define svint 2

typedef void *ThreadHandle;

double SV_Cell_Field(CX_Field_Id, CX_Cell_Id *);
double SV_Face_Field(CX_Field_Id, CX_Cell_Id *);
double SV_Face_Density(CX_Field_Id, CX_Cell_Id *, CX_Cell_Id *);
void SV_Vector_Cell_Field (CX_Field_Id, CX_Cell_Id *, double v[]);
void SV_Initialize_Face_Field(CX_Field_Id, CX_Cell_Id *);
void SV_Lb_Initialize_Face_Fields(CX_Field_Id);

int SV_Face_Only (void);
int SV_Face_Val (void);
FLUENT_EXPORT int SV_Get_Svar_Index(char *);

/* support for user-defined field function calculator */
int SV_Field_Count_Elements (int nv);
int SV_Field_Face_Count_Elements(void);
void SV_Field_Derivative  (void);
void SV_Field_Get_Values  (int nv, char *fname, float *field, size_t size);
void SV_Field_Set_Values  (int nv, float *field, CXBoolean isSingleValued, char *fname, int ntmp);
void Set_Domain_Thread_Render   (void);
cxboolean Check_Field_Evaluable(ThreadHandle threadH, const char *fname);
#if CX_HOST
void SV_Free_Host_Domain(void);
#endif

/* ---- these need to be verified as to usefulness ----- */

void SV_set_node_mark (CX_Node_Id n, int val);
int SV_get_node_mark (CX_Node_Id n);
void SV_set_node_ptr_temp (CX_Node_Id n, void *val);
void *SV_get_node_ptr_temp ( CX_Node_Id n );
void SV_allocate_node_ptr_storage(void);
void SV_deallocate_node_ptr_storage(void);
void SV_allocate_node_value_storage(void);
void SV_deallocate_node_value_storage(void);
int SV_cell_nnodes(CX_Cell_Id *c);
int SV_cell_node_index(CX_Cell_Id *c, CX_Node_Id node);
FLUENT_EXPORT CX_Node_Id SV_cell_node_id (CX_Cell_Id *c, int i);
CX_Node_Id SV_face_node_id (CX_Cell_Id *, CX_Face_Id, int, int );
FLUENT_EXPORT int SV_cell_type (CX_Cell_Id *c);
FLUENT_EXPORT int SV_cell_num_faces( CX_Cell_Id *, int * );

FLUENT_EXPORT int SV_cell_id_eq_cache(CX_Cell_Id *, CX_Cell_Id *);
FLUENT_EXPORT int SV_cell_id_cache(CX_Cell_Id *);
FLUENT_EXPORT int SV_periodic_face(CX_Cell_Id *, CX_Face_Id);

FLUENT_EXPORT int SV_cell_id_eq (CX_Cell_Id *c1, CX_Cell_Id *c2);
FLUENT_EXPORT int SV_face_eq (CX_Cell_Id *, CX_Face_Id, CX_Cell_Id *, CX_Face_Id);
FLUENT_EXPORT float SV_node_value (CX_Node_Id n);
FLUENT_EXPORT void SV_node_value_all (CX_Cell_Id *c, float *val);
FLUENT_EXPORT double SV_node_coord (CX_Node_Id n, int d);
FLUENT_EXPORT void  SV_node_coord_all (CX_Cell_Id *c, float time, float *co_ord);
FLUENT_EXPORT void SV_Get_Cell_Dimension(CX_Cell_Id *cell, float *cdim);
FLUENT_EXPORT int  SV_face_coord_all (CX_Cell_Id *, CX_Face_Id, float, float *, int *);

FLUENT_EXPORT void SV_node_vel_all (CX_Cell_Id *c, float *v, char *vel_type);
FLUENT_EXPORT void CX_Zone_Get_Min_Max(Pointer zid, float *min, float *max);
FLUENT_EXPORT void SV_Point_Surface (int surf_id, Pointer lpt_list, cxboolean structural);
FLUENT_EXPORT void SV_Lb_Point_Surface(int surf_id, Pointer lpt_list);
FLUENT_EXPORT void SV_Structural_Point_Surface(int index, int threadid, int cellid, short nc, ip_vec *ip);
FLUENT_EXPORT void SV_Get_Structural_Thread_and_Cell_ID(CX_Cell_Id *cx_cell, int *thread_id, int *cell_id);
FLUENT_EXPORT int *SV_Old_Planar_Point_Surface (int surf_id, Pointer lpt_list,
                                                Pointer leqn, int *out_list_len);
FLUENT_EXPORT int *SV_Planar_Point_Surface (int surf_id, Pointer edge,
                                            Pointer points, int *out_list_len);
FLUENT_EXPORT void SV_Iso_Domain (int surf_id, float *iso_vals, int nvals, int nt, int *tids);
FLUENT_EXPORT cxboolean SV_Compute_Facet_Normal(Surface *, int, float []);
FLUENT_EXPORT void SV_Iso_Zones(int index, int *zids, int nzids,
                                float *iso_vals, int nvals);
FLUENT_EXPORT void SV_Zone_Surface (Pointer lsurf_id, Pointer lzone_list);
FLUENT_EXPORT void SV_Register_Surface(int surfaceId, unsigned int rbitIndex,
                                       unsigned int cbitIndex, int surfFlag,
                                       int maxCells);
FLUENT_EXPORT double *SV_Get_Surface_Weights(Surface *s);
FLUENT_EXPORT cxboolean SV_Is_Lb_Enabled(void);
FLUENT_EXPORT void SV_Clip_Surface_To_Lb_Boundaries(int newSurfId, int origSurfId);
FLUENT_EXPORT void SV_Lb_Fill_Zone_Facet_Cells(Surface *surf, float *x, float *y, float *z, CX_Cell_Id **cells);


void Zero_array1_pointer_and_length (void);
/* Surface probes */
int SV_print_surface_cell_info (CX_Cell_Id *c);
void CX_Get_Cell_Centroid(CX_Cell_Id *c, float *centroid);

void SV_cyclic_transform  ( CX_Cell_Id *, CX_Face_Id, int *, float[]);
int  SV_vel_node_values   ( void );
int  SV_get_omega               ( float *, float *, float *, float *);
int  SV_get_neighbour     (CX_Cell_Id *, CX_Face_Id, CX_Cell_Id *, int);

int  SV_is_bndry_face     ( CX_Cell_Id *, CX_Face_Id );
int  SV_is_symmetry_face  ( CX_Cell_Id *, CX_Face_Id );
int  SV_is_periodic_face  ( CX_Cell_Id *, CX_Face_Id );
int  SV_live_cell   (CX_Cell_Id *);
#if 0
int  SV_is_wall_face    ( CX_Cell_Id *, CX_Face_Id);
#endif
int  SV_get_next_cell   ( CX_Cell_Id *, int, int );
int  SV_get_cell_tag    ( CX_Cell_Id *);
void SV_set_cell_tag    ( CX_Cell_Id *, int);
int  SV_cell_zone   ( CX_Cell_Id *);
int  SV_face_zone   ( CX_Cell_Id *, CX_Face_Id );
int  SV_moving      ( void );
int  SV_axi     ( void );
int  SV_Is_X_Axis_Symmetry      ( void );
int  SV_Use_Cell_Values         ( void );

void SV_Write_Ray   (FILE *, int, int *, float *, int, int);


/* Cortex Initialization Routines */
/* allocates space for point interpolation vectors, initializes
   scheme bindings*/
FLUENT_EXPORT void  CX_Init_Surfaces (int max_nodes_per_cell, int dimension);

/* Surface Creation Routines */

FLUENT_EXPORT void CX_Start_Surface (int index, int nfaces, int face_list_len); /* open surface */
FLUENT_EXPORT int CX_End_Surface (int n); /* close surface */
FLUENT_EXPORT void CX_Free_Surfaces (void);
FLUENT_EXPORT void CX_Create_Empty_Surface (int id);
FLUENT_EXPORT int CX_Same_Point(CX_Cell_Id *c, int m, int n, double *di, double *dj);
FLUENT_EXPORT void CX_Orient_Facets(void); /* orient facets */
FLUENT_EXPORT cxboolean CX_Is_Tmp_Surface_Empty(void);

/* Iso-Surface Routines */
FLUENT_EXPORT void CX_Iso_Surface (int *s_index, int d_index, float *vals, int nsurfs,
                                   int nvals, int nt, int *tids, int rake);

/* Return number of iso-facets in a cell for given iso-values */
int CX_Tri_Iso_Facets_Num (CX_Cell_Id *c, float *vals, int nvals);
int CX_Tet_Iso_Facets_Num (CX_Cell_Id *c, float *vals, int nvals);
int CX_Quad_Iso_Facets_Num (CX_Cell_Id *c, float *vals, int nvals);
int CX_Hex_Iso_Facets_Num (CX_Cell_Id *c, float *vals, int nvals);
int CX_Pyr_Iso_Facets_Num (CX_Cell_Id *c, float *vals, int nvals);
int CX_Wedge_Iso_Facets_Num (CX_Cell_Id *c, float *vals, int nvals);

/* Generate and Add Iso_facets in given cell for given iso-values to
   currently opened surface */
void CX_Add_Tri_Iso_Facets (CX_Cell_Id *c, float *vals, int nvals);
void CX_Add_Tet_Iso_Facets (CX_Cell_Id *c, float *vals, int nvals);
void CX_Add_Quad_Iso_Facets (CX_Cell_Id *c, float *vals, int nvals);
void CX_Add_Hex_Iso_Facets (CX_Cell_Id *c, float *vals, int nvals);
void CX_Add_Pyr_Iso_Facets (CX_Cell_Id *c, float *vals, int nvals);
void CX_Add_Wedge_Iso_Facets (CX_Cell_Id *c, float *vals, int nvals);
void SV_Add_Poly_Iso_Facets(CX_Cell_Id *cell, float *vals, int nval);

/* Other Surface Routines */
FLUENT_EXPORT int CX_Pt_In_Quad_Cell  (float v[][2], float *);
FLUENT_EXPORT int CX_Pt_In_Wedge_Cell (float v[][3], float *);
FLUENT_EXPORT int CX_Pt_In_Pyr_Cell (float v[][3], float *);
FLUENT_EXPORT int CX_Pt_In_Tri_Cell (float v[][2], float *);
FLUENT_EXPORT int CX_Pt_In_Tet_Cell (float v[][3], float *);
FLUENT_EXPORT int CX_Pt_In_Hex_Cell (float v[][3], float *);
FLUENT_EXPORT int CX_Point_In_Cell  (float *, int, float [][3], CX_Cell_Id *);
FLUENT_EXPORT int CX_Pt_In_Poly_Cell(CX_Cell_Id *cx_cell, float time, float *pt);
FLUENT_EXPORT cxboolean CX_IsPointInCell_Wrapper(CX_Cell_Id *cx_cell, double point[3], double time);
FLUENT_EXPORT double Comp_Dist2_To_Cell(CX_Cell_Id *cell, double *pt);
FLUENT_EXPORT void CX_Set_Surf_n_ext_facets(int n_ext_facets);

int CX_Add_Tri_Point_To_Surface (CX_Cell_Id *cx_cell, float verts[3][2], float *point, ip_vec *ip);
int CX_Add_Tet_Point_To_Surface (CX_Cell_Id *cx_cell, float verts[4][3], float *point, ip_vec *ip);
int CX_Add_Quad_Point_To_Surface (CX_Cell_Id *cx_cell, float verts[4][2], float *point, ip_vec *ip);
int CX_Add_Hex_Point_To_Surface (CX_Cell_Id *cx_cell, float verts[8][3], float *point, ip_vec *ip);
int CX_Add_Pyr_Point_To_Surface (CX_Cell_Id *cx_cell, float verts[5][3], float *point, ip_vec *ip);
int CX_Add_Wedge_Point_To_Surface (CX_Cell_Id *cx_cell, float verts[6][3], float *point, ip_vec *ip);
int CX_Add_Poly_Point_To_Surface (CX_Cell_Id *cx_cell, float *point, int n, ip_vec *ip);
void CX_Update_Point_Creation_Tolerance(int val);

int compute_poly_ip(CX_Cell_Id *cx_cell, float *pt, ip_vec ip[]);
int compute_tet_ip(float v[4][3], float *point, ip_vec ip[4]);

void  CX_Add_Point_To_Surface (CX_Cell_Id *c, int nc, ip_vec ip[]);
void    CX_AddPointToSurface(CX_Cell_Id *c, ip_vec *ip, int nc);
void    CX_Add_New_Facet_To_Surface (CX_Cell_Id *, int *, int);
void    CX_Add_Node_Point_To_Surface (CX_Cell_Id *, int, float []);

int CX_Check_Tri_Line_Intersection (float *verts, float *line);
int CX_Check_Quad_Line_Intersection (float *verts, float *line);
int CX_Check_Tet_Plane_Intersection (float *verts, float *plane);
int CX_Check_Hex_Plane_Intersection (float *verts, float *plane);
int CX_Check_Pyr_Plane_Intersection (float *verts, float *plane);
int CX_Check_Wedge_Plane_Intersection (float *verts, float *plane);
int CX_Check_Poly_Plane_Intersection (float *verts, float *plane, int n);

int CX_Check_Tri_Line_Extents (float *verts, float *lmin, float *lmax);
int CX_Check_Quad_Line_Extents (float *verts, float *lmin, float *lmax);
int CX_Check_Tet_Plane_Extents (float *verts, float *pmin, float *pmax);
int CX_Check_Hex_Plane_Extents (float *verts, float *pmin, float *pmax);
int CX_Check_Pyr_Plane_Extents (float *verts, float *pmin, float *pmax);
int CX_Check_Wedge_Plane_Extents (float *verts, float *pmin, float *pmax);
int CX_Check_Poly_Plane_Extents (float *verts, float *pmin, float *pmax, int n);

int CX_Compute_Plane (float [][3], float *);

/* Client-side Contouring */
void CX_Contour_Tri (CX_Cell_Id *c, int node_values);
void CX_Contour_Quad (CX_Cell_Id *c, int node_values);
void CX_CL_Contour_Surface (int index, int node_values, char *name);
void CX_CL_Fill_Field_Data(char *name, int *indices, int nids, int node_values);

/* These functions are defined on fluent side , in turbo.c . */
FLUENT_EXPORT void SV_initTurbo(void);
FLUENT_EXPORT void SV_freeTurbo(void);
FLUENT_EXPORT float SV_getSpanwiseCoordinate(float axial, float radial, int nAbs, int
                                             index, int method);
FLUENT_EXPORT float SV_getPitchwiseCoordinate(float axial, float radial, float theta, int
                                              nAbs, int index, int method, float
                                              thetamin);
FLUENT_EXPORT float SV_getMeridionalCoordinate (float a, float r, int nAbs,
                                                int index, int method);

/*Print Routines */
FLUENT_EXPORT void CX_Surface_Values (int index, int node_values);
FLUENT_EXPORT void CX_Prof_Surface_Values (int index, int node_values);
FLUENT_EXPORT void CX_Surface_Velocity_Vectors (int index, int node_values);
FLUENT_EXPORT void CX_Surface_Write_Values (FILE *fp, int index, int node_values,
                                            float xunit[], float vunit[]);

/*Oct-tree API */
#define CX_POINT_ELT 0
#define CX_LINE_ELT 1
#define CX_TRI_ELT 2
#define CX_QUAD_ELT 3
#define CX_POLY_ELT 4

typedef struct CX_Face_Struct
{
  int np;
  float v[MAX_FACE_NODES][3];
  char *prop;
} CX_Face_t;

FLUENT_EXPORT void CX_Start_Tree (void);
FLUENT_EXPORT int  CX_End_Tree (cxboolean);
FLUENT_EXPORT int  CX_End_Tree_New (int);
FLUENT_EXPORT void CX_Cache_Elt_Ptrs (void);
FLUENT_EXPORT void CX_Delete_Elt_Ptrs (void);
FLUENT_EXPORT void CX_Free_Tree (void);
FLUENT_EXPORT void CX_Add_Elems_To_Tree (float *, int);

FLUENT_EXPORT double CX_Shortest_Dist_Point_Tree (float *p, CX_Face_t *f);
FLUENT_EXPORT double CX_Shortest_Dist_Point_Tree_New (float *p, CX_Face_t *f, float cur_min_sq);
FLUENT_EXPORT double CX_Shortest_Dist_Point_Tree_New1 (float *p, CX_Face_t *f, float cur_min_sq);
FLUENT_EXPORT double CX_Shortest_Sign_Dist_Point_Tree (float *p, CX_Face_t *f);
double CX_Shortest_Sign_Proj_Dist_Point_Tree (float *p, CX_Face_t *f);

FLUENT_EXPORT void SV_Set_All_Node_Values (double (*)(float *, CX_Face_t *));

void SV_Add_Face_Thread_To_Tree (int id);

/* Fast Iso-Surf API */

typedef struct CX_Cell_List_Struct
{
  CX_Cell_Id cell;
  float min;
  float max;
  struct CX_Cell_List_Struct *next;
} CX_Cell_List_t;

int SV_Count_Nodes (void);
int SV_Count_Cells (void);
int SV_Count_Cells_Poly_Divided (void);
int SV_Count_Cells_Poly_Divided_Receptor (const cxboolean receptor_cells);
int SV_Count_Faces (void);
void SV_Get_All_Node_Values (float *node_list);
void SV_Get_All_Cells (CX_Cell_List_t *cell_list, float *min, float *max);
void SV_Exchange_Node_Values (void);

/* Radiation .. */
int  CX_Num_S_Globs               (void);
int  CX_Get_S_Glob      (int, int *, int *, CX_Face_Def **);
int  CX_Get_S_Glob_Cache          (int, int *, int *, CX_Face_Def **);
int  CX_Num_V_Globs     (void);
void CX_Get_V_Glob      (int, int *, int *, CX_Cell_Id ***);
void CX_Delete_All_Globs    (void);
void CX_Ray_Trace     (FILE *, int, int, int, int);
#if GRAPHICS
void CX_Change_Curr_Display_Glob  (int, float coords[]);
void CX_Display_Curr_Display_Glob (void);
void CX_Display_Globs     (int);
#endif
void CX_Glob_Elements     (int, int, float, cxboolean);
int CX_Fill_Surface_Glob_Ptrs     (int);
void CX_Free_Surface_Glob_Ptrs    (void);

/*Init cfsubrs */
void CX_Init_CellFunctions (void);
float *CX_Get_New_Field_Tmp (char *name, float **ftmp);


/*
is domain active?
Serial client is always active.
Parallel host is always active.
Only parallel nodes may have inactive domains (for viz. purposes only).
*/
FLUENT_EXPORT int SV_Is_Domain_Active (void);

FLUENT_EXPORT cxboolean SV_Need_To_Check_If_Cell_Active(void);
FLUENT_EXPORT cxboolean SV_Check_If_Cell_Active(CX_Cell_Id *cid);

FLUENT_EXPORT cxboolean SV_Need_To_Check_If_Cell_Solved(void);
FLUENT_EXPORT cxboolean SV_Check_If_Cell_Solved(CX_Cell_Id *cid);
/* The following function can be used to get the active facets
   If the return value is FALSE, there are no active facets.
   If the return value is TRUE and array pointer is NULL. All points are active.
   If the return value is TRUE and array pointer is not NULL. The array[i] will
   provide if the facet is active or not.
 */
FLUENT_EXPORT cxboolean SV_Get_Active_Facets(Surface *s, int **array);
/*
host domain filled?
Serial client is always filled.
*/
int SV_Is_Host_Domain_Filled_P (int with_node);

struct vec; /*forward declaration for struct vec in cxfields.h*/

#if PARALLEL
# if CX_HOST
void PSV_Host_repl (void);
FLUENT_EXPORT extern const char *PRF_Command_Start (const char *, ...);
void CX_Host_Define_Surface (int id);
void CX_Host_Get_Ints (int **ilist, int *plen);
void CX_Host_Get_Floats (float **flist, int *plen);
void CX_Host_Get_Vec(struct vec **v, int *plen);
# else
void CX_Node_Send_Floats (float *val, int len);
void CX_Node_Send_Ints (int *val, int len);
void CX_Node_Send_Vec(struct vec *val, int len);
void CX_Node_Send_Intersect_Ints (int *val, int len);
void CX_Node_Get_Host_Floats (float **flist, int *plen);
int SV_Exterior_Cell_P (CX_Cell_Id *cell);
int *SV_Nb_Partitions (int *npartitions);
int SV_Cell_Partition (CX_Cell_Id *c);
void SV_CX_Cell_Id (CX_Cell_Id *c, int Cell_id, int part_id);
int SV_All_Nodes_Err_Msgs (void);
# endif       /* CX_HOST */
#endif        /* PARALLEL */


/* Quadrics -- shared by cortex and client now. */

typedef struct quadric_struct
{
  float xx, yy, zz;
  float xy, yz, zx;
  float x, y, z;
  float c;
} Quadric;

/* Polyhedral post-processing */
int CX_Get_Points_On_Poly_Face(CX_Cell_Id *c, float val, CX_Node_Id nid[],
                               int n, float rmax, int pt_list[], int flip);
void CX_Create_Poly_Facet(CX_Cell_Id *c, int list[], int n);
#endif /* Cxiface_h */
