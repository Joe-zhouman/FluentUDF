/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_METRIC_H
#define _FLUENT_METRIC_H

#include "dll.h"
typedef void (*solid_cells_face_velocity)(real *V, const int f, const Thread *t);
FLUENT_EXPORT void Assign_Solid_Velocity_function_Pointer(solid_cells_face_velocity * );
FLUENT_EXPORT void F_Solid_Velocity(real *V, const int f, const Thread *t);
#if RP_2D
extern FLUENT_EXPORT cxboolean rp_axi;
#else
#define  rp_axi  00   /* for "(RP_2D && rp_axi) ? ... : ..." --> short: "rp_axi" */
#endif

extern FLUENT_EXPORT cxboolean have_old_centroids;
extern FLUENT_EXPORT cxboolean use_pre_R19_metrics;

#if !RP_HOST
FLUENT_EXPORT cxboolean Volume_Statistics(Domain *d, int verbosity);
FLUENT_EXPORT cxboolean Face_Area_Statistics (Domain *, cxboolean, int);
#endif
FLUENT_EXPORT cxboolean Need_Old_Centroids_P (Domain *);
FLUENT_EXPORT cxboolean Need_Old_Coords_P (Domain *);
FLUENT_EXPORT void Allocate_Grid_Metrics (Domain *);
FLUENT_EXPORT real C_Volume(const cell_t, const Thread *, const cxboolean);
FLUENT_EXPORT void Update_Volume (Domain *, Objp *);
FLUENT_EXPORT void Update_Virtpoly_Grid_Metrics (Domain *);
FLUENT_EXPORT void Update_Mapped_Interface_Metrics (Domain *);
FLUENT_EXPORT void Update_Mapped_Interface_After_Data_Read (Domain *);
FLUENT_EXPORT Objp *Get_Cell_Thread_List (Domain *, Objp *);
FLUENT_EXPORT Objp *Get_Cell_Thread_List_All_if_NULL (Domain *, Objp *);
FLUENT_EXPORT Objp *Get_Cell_Thread_List_Minus_Shell (Domain *, Objp *);
FLUENT_EXPORT Objp *Get_Face_Thread_List (Domain *, Objp *);
FLUENT_EXPORT Objp *Get_Face_Thread_List_All_if_NULL (Domain *, Objp *);
FLUENT_EXPORT void Update_Grid_Metrics_Optimized (Domain *, Objp *, cxboolean, cxboolean, cxboolean);
FLUENT_EXPORT void Update_Grid_Metrics (Domain *, Objp *, cxboolean);
FLUENT_EXPORT void Update_Interior_Face_Geometry_Of_Thread (Domain *, Thread *);
FLUENT_EXPORT cxboolean Set_Update_Interior_Face_Geometry (cxboolean);
FLUENT_EXPORT void Update_Interior_Face_Geometry (Domain *, Objp *, cxboolean);
#if RP_NODE
FLUENT_EXPORT void Update_Exterior_Face_Metrics (Domain *);
FLUENT_EXPORT void Update_Exterior_Face_Metrics_For_Mapped_Interface(Domain *);
FLUENT_EXPORT void Update_Exterior_Metrics (Domain *);
#endif
FLUENT_EXPORT void Set_Projected_Face_Centroid(real [ND_ND], face_t, Thread *, face_t, Thread *);
FLUENT_EXPORT void Scale_Domain (Domain *, real *, Objp *);
FLUENT_EXPORT void Translate_Cell_Thread (Domain *, Thread *, real *);
FLUENT_EXPORT void Translate_Domain (Domain *, real *, Objp *, int);
FLUENT_EXPORT void Rotate_Cell_Thread (Domain *, Thread *,
                                       real *, real *, real);
FLUENT_EXPORT cxboolean Share_Faces_With_Others(Domain *, Objp *);
FLUENT_EXPORT Objp *Cell_List_To_Face_List(Domain *, Objp *);
FLUENT_EXPORT void Rotate_Domain (Domain *, real *, real *, real, Objp *, int);
FLUENT_EXPORT void RP_Compute_Rotation_Matrix (real [3][3], real, real, real, real);
FLUENT_EXPORT cxboolean If_Zone_Rotating_As_Rigid_Get_R(Thread *, real, real [3][3], real [3]);

FLUENT_EXPORT void Fill_Face_Area_X(Domain *d);
FLUENT_EXPORT void Fill_Face_Area_Y(Domain *d);
#if RP_3D
FLUENT_EXPORT void Fill_Face_Area_Z(Domain *d);
#endif
FLUENT_EXPORT void Fill_Face_Area_Mag(Domain *d);
FLUENT_EXPORT void Fill_Face_Area(Domain *d, int);

FLUENT_EXPORT void Face_Area_X(Thread *thread, int type, Svar svar);
FLUENT_EXPORT void Face_Area_Y(Thread *thread, int type, Svar svar);
#if RP_3D
FLUENT_EXPORT void Face_Area_Z(Thread *thread, int type, Svar svar);
#endif
FLUENT_EXPORT void Face_Area_Magnitude(Thread *thread, int type, Svar svar);
FLUENT_EXPORT void Fill_Face_Area_Thread(Thread *thread, int nd, Svar svar);


#define CSP_Centroid_Nodes(_x,_csp)                \
{                                                  \
  register int _n;                                 \
  NV_S (_x, =, 0.0);                               \
  csp_node_loop (_csp, _n)                         \
    NV_V (_x, +=, NODE_COORD(CSP_NODE(_csp, _n))); \
  NV_S (_x, /=, _n);                               \
}

#define C_Centroid_Nodes(_x,_c,_t)                   \
{                                                    \
  register int _n = 0;                               \
  NV_S (_x, =, 0.0);                                 \
  c_node_loop (_c,_t,_n)                             \
    NV_V (_x, +=, NODE_COORD (C_NODE (_c, _t, _n))); \
  if (_n > 0)                                        \
    NV_S (_x, /=, _n);                               \
}

#define CSP_Centroid_Nodes_N(_x,_csp)                \
{                                                  \
  register int _n;                                 \
  NV_S (_x, =, 0.0);                               \
  csp_node_loop (_csp, _n)                         \
    NV_V (_x, +=, NODE_COORD_N(CSP_NODE(_csp, _n))); \
  NV_S (_x, /=, _n);                               \
}

#define CSP_Centroid_Nodes_M1(_x,_csp)                \
{                                                  \
  register int _n;                                 \
  NV_S (_x, =, 0.0);                               \
  csp_node_loop (_csp, _n)                         \
    NV_V (_x, +=, NODE_COORD_M1(CSP_NODE(_csp, _n))); \
  NV_S (_x, /=, _n);                               \
}

#define C_Centroid_Nodes_N(_x,_c,_t)         \
{                                                    \
  register int _n;                                   \
  NV_S (_x, =, 0.0);                                 \
  c_node_loop (_c,_t,_n)                             \
    NV_V (_x, +=, NODE_COORD_N (C_NODE (_c, _t, _n))); \
  NV_S (_x, /=, _n);                                 \
}

FLUENT_EXPORT void Calculate_Cell_Centroid_DP (double *, const cell_t,
                                               const Thread *, const cxboolean);
#if RP_DOUBLE
#define Calculate_Cell_Centroid Calculate_Cell_Centroid_DP
#else
FLUENT_EXPORT void Calculate_Cell_Centroid (real *, const cell_t,
                                            const Thread *, const cxboolean);
#endif

#define C_Centroid(_x,_c,_t) Calculate_Cell_Centroid (_x,_c,_t,FALSE)

FLUENT_EXPORT void C_Centroid_Fast_N (real *, const cell_t, const Thread *,
                                      const cxboolean);
#define C_Centroid_N(_x,_c,_t) C_Centroid_Fast_N(_x,_c,_t,FALSE)
FLUENT_EXPORT void C_Centroid_Fast_M1 (real *, const cell_t, const Thread *,
                                       const cxboolean);
#define C_Centroid_M1(_x,_c,_t) C_Centroid_Fast_M1(_x,_c,_t,FALSE)
FLUENT_EXPORT void C_Modified_Centroid (real *, const cell_t, const Thread *);
FLUENT_EXPORT real C_Centroid_X (const cell_t, const Thread *);
FLUENT_EXPORT real C_Centroid_Y (const cell_t, const Thread *);
#if RP_3D
FLUENT_EXPORT real C_Centroid_Z (const cell_t, const Thread *);
#endif

# if RP_2D

#  define Calc_F_Area(A,f,t)\
  switch (F_NNODES(f,t))\
    {\
    case MIXED_FACE:            /* Accumulated face  */\
      NV_V (A, =, ACCUMULATED_F_AREA(f,t));\
      break;\
\
    case LINEAR_FACE:   /* 2D face */\
    default: \
      if (rp_axi)\
  {\
    A[0] = AXI_AREA_X(F_NODE(f,t,0),F_NODE(f,t,1));\
    A[1] = AXI_AREA_Y(F_NODE(f,t,0),F_NODE(f,t,1));\
  }\
      else\
  {\
    A[0] = TWOD_AREA_X(F_NODE(f,t,0),F_NODE(f,t,1));\
    A[1] = TWOD_AREA_Y(F_NODE(f,t,0),F_NODE(f,t,1));\
  }\
      break;\
    }

# else /* RP_3D */

#  define Calc_F_Area(A,f,t)\
  switch (F_NNODES(f,t))\
    {\
    case MIXED_FACE:            /* Accumulated face  */\
      NV_V (A, =, ACCUMULATED_F_AREA(f,t));\
      break;\
\
    case TRI_FACE:    /* 3D triangular face */\
      {\
  Node *n0 = F_NODE(f,t,0);\
  Node *n1 = F_NODE(f,t,1);\
  Node *n2 = F_NODE(f,t,2);\
  A[0] = TRI_AREA_X(n0,n1,n2);\
  A[1] = TRI_AREA_Y(n0,n1,n2);\
  A[2] = TRI_AREA_Z(n0,n1,n2);\
      }\
      break;\
\
    case QUAD_FACE:   /* 3D quad face */\
      {\
  Node *n0 = F_NODE(f,t,0);\
  Node *n1 = F_NODE(f,t,1);\
  Node *n2 = F_NODE(f,t,2);\
  Node *n3 = F_NODE(f,t,3);\
  A[0] = QUAD_AREA_X(n0,n1,n2,n3);\
  A[1] = QUAD_AREA_Y(n0,n1,n2,n3);\
  A[2] = QUAD_AREA_Z(n0,n1,n2,n3);\
      }\
      break;\
\
    case POLY_FACE:\
    default:      /* 3D polygonal face */\
      {\
  register int _i;\
  \
  NV_S (A, =, 0.);\
\
  for (_i = 0; _i < F_NNODES(f,t); ++_i)\
    {\
      Node *n0 = F_NODE (f, t, _i);\
      Node *n1 = F_NODE (f, t, (_i+1)%F_NNODES(f,t));\
      ND_MAP(A[0],A[1],A[2], +=,\
       (NODE_Y(n1) + NODE_Y(n0))*(NODE_Z(n1) - NODE_Z(n0)),\
       (NODE_Z(n1) + NODE_Z(n0))*(NODE_X(n1) - NODE_X(n0)),\
       (NODE_X(n1) + NODE_X(n0))*(NODE_Y(n1) - NODE_Y(n0)));\
    }\
  NV_S (A, /=, 2.);\
      }\
      break;\
    }
# endif /* RP_3D */

FLUENT_EXPORT void Update_Face_Area_Cache_On_Thread (Thread *);
FLUENT_EXPORT void Update_Face_Area_Cache (Domain *);

#define FSP_Centroid_Nodes(_x,_fsp)                    \
{                                                      \
  if (FSP_TYPE (_fsp) != MIXED_FACE)                   \
    {                                                  \
      register int _n;                                 \
      NV_S (_x, =, 0.0);                               \
      fsp_node_loop (_fsp, _n)                         \
        NV_V (_x, +=, NODE_COORD(FSP_NODE(_fsp, _n))); \
      NV_S (_x, /=, _n);                               \
    }                                                  \
  else                                                 \
    NV_V (_x, =, NODE_COORD(FSP_NODE(_fsp, 0)));       \
}

#define F_Centroid_Nodes(_x,_f,_t)                       \
{                                                        \
  register int _n;                                       \
  if (F_TYPE (_f,_t) != MIXED_FACE)                      \
    {                                                    \
      NV_S (_x, =, 0.0);                                 \
      f_node_loop (_f, _t, _n)                           \
  NV_V (_x, +=, NODE_COORD (F_NODE (_f, _t, _n))); \
      NV_S (_x, /=, _n);                                 \
    }                                                    \
  else                                                   \
    NV_V (_x, =, NODE_COORD (F_NODE (_f, _t, 0)));       \
}

#define FSP_Centroid_Nodes_N(_x,_fsp)                    \
{                                                      \
  if (FSP_TYPE (_fsp) != MIXED_FACE)                   \
    {                                                  \
      register int _n;                                 \
      NV_S (_x, =, 0.0);                               \
      fsp_node_loop (_fsp, _n)                         \
        NV_V (_x, +=, NODE_COORD_N(FSP_NODE(_fsp, _n))); \
      NV_S (_x, /=, _n);                               \
    }                                                  \
  else                                                 \
    NV_V (_x, =, NODE_COORD_N(FSP_NODE(_fsp, 0)));       \
}

#define FSP_Centroid_Nodes_M1(_x,_fsp)                    \
{                                                      \
  if (FSP_TYPE (_fsp) != MIXED_FACE)                   \
    {                                                  \
      register int _n;                                 \
      NV_S (_x, =, 0.0);                               \
      fsp_node_loop (_fsp, _n)                         \
        NV_V (_x, +=, NODE_COORD_M1(FSP_NODE(_fsp, _n))); \
      NV_S (_x, /=, _n);                               \
    }                                                  \
  else                                                 \
    NV_V (_x, =, NODE_COORD_M1(FSP_NODE(_fsp, 0)));       \
}

#define FSP_Centroid_PERDISP(_x,_fsp)                    \
{                                                      \
  if (FSP_TYPE (_fsp) != MIXED_FACE)                   \
    {                                                  \
      register int _n;                                 \
      NV_S (_x, =, 0.0);                               \
      fsp_node_loop (_fsp, _n)                         \
        NV_V (_x, +=, NODE_PERDISP(FSP_NODE(_fsp, _n))); \
      NV_S (_x, /=, _n);                               \
    }                                                  \
  else                                                 \
    NV_V (_x, =, NODE_PERDISP(FSP_NODE(_fsp, 0)));       \
}

#define FSP_Centroid_PERIMAG(_x,_fsp)                    \
{                                                      \
  if (FSP_TYPE (_fsp) != MIXED_FACE)                   \
    {                                                  \
      register int _n;                                 \
      NV_S (_x, =, 0.0);                               \
      fsp_node_loop (_fsp, _n)                         \
        NV_V (_x, +=, NODE_PERIMAG(FSP_NODE(_fsp, _n))); \
      NV_S (_x, /=, _n);                               \
    }                                                  \
  else                                                 \
    NV_V (_x, =, NODE_PERIMAG(FSP_NODE(_fsp, 0)));       \
}

#define F_Centroid_Nodes_N(_x,_f,_t)                       \
{                                                        \
  register int _n;                                       \
  if (F_TYPE (_f,_t) != MIXED_FACE)                      \
    {                                                    \
      NV_S (_x, =, 0.0);                                 \
      f_node_loop (_f, _t, _n)                           \
  NV_V (_x, +=, NODE_COORD_N (F_NODE (_f, _t, _n))); \
      NV_S (_x, /=, _n);                                 \
    }                                                    \
  else                                                   \
    NV_V (_x, =, NODE_COORD_N (F_NODE (_f, _t, 0)));       \
}

#define F_Centroid_Nodes_M1(_x,_f,_t)                       \
{                                                        \
  register int _n;                                       \
  if (F_TYPE (_f,_t) != MIXED_FACE)                      \
    {                                                    \
      NV_S (_x, =, 0.0);                                 \
      f_node_loop (_f, _t, _n)                           \
  NV_V (_x, +=, NODE_COORD_M1 (F_NODE (_f, _t, _n))); \
      NV_S (_x, /=, _n);                                 \
    }                                                    \
  else                                                   \
    NV_V (_x, =, NODE_COORD_M1 (F_NODE (_f, _t, 0)));       \
}

/* edge length of ideal equilateral tri/tet */
#define ideal_tet_edge_length(vol) pow ((vol)*8.485281, 0.333333333333333)
#define ideal_tri_edge_length(vol) sqrt ((vol)*2.309401)
#if RP_3D
# define ideal_cell_edge_length(vol) ideal_tet_edge_length(vol)
# define ideal_face_edge_length(vol) ideal_tri_edge_length(vol)
#else
# define ideal_cell_edge_length(vol) ideal_tri_edge_length(vol)
# define ideal_face_edge_length(vol) (vol)
#endif

extern FLUENT_EXPORT real mesh_face_area_threshold;
#define F_SMALL_AREA_P(_f,_t) \
  (NV_MAG (F_DERIVATIVE_AREA_CACHE (_f, _t)) < mesh_face_area_threshold)

#if RP_DOUBLE
#define F_Centroid F_Centroid_DP
#else
FLUENT_EXPORT void F_Centroid (real *, const face_t, const Thread *);
#endif


FLUENT_EXPORT void F_Centroid_DP (double *, const face_t, const Thread *);
FLUENT_EXPORT void F_Centroid_N (real *, const face_t, const Thread *);
FLUENT_EXPORT void F_Centroid_M1 (real *, const face_t, const Thread *);
FLUENT_EXPORT real F_Centroid_X(const face_t, const Thread *);
FLUENT_EXPORT real F_Centroid_Y(const face_t, const Thread *);
FLUENT_EXPORT void F_Centroid_PERDISP (double *, const face_t, const Thread *);
#if RP_3D
FLUENT_EXPORT real F_Centroid_Z(const face_t, const Thread *);
#endif
FLUENT_EXPORT void Update_Face_Centroid_Cache_On_Thread (Thread *);
FLUENT_EXPORT void Update_Face_Centroid_Cache (Domain *);
FLUENT_EXPORT void Update_Virtual_Face_Centroid_Cache (Domain *);
FLUENT_EXPORT void Update_Cell_Centroid_Cache (Domain *);

FLUENT_EXPORT void Update_Face_Metrics (face_t, Thread *);
FLUENT_EXPORT void Update_Cell_Metrics (const cell_t, const Thread *, const cxboolean);

FLUENT_EXPORT void Reverse_Face(const face_t, Thread *const);
FLUENT_EXPORT void Reverse_Face_Nodes(const face_t, Thread *const);

FLUENT_EXPORT void Store_Old_Metrics (Domain *);
FLUENT_EXPORT void Store_Old_Face_Centroids (Thread *);
FLUENT_EXPORT void Store_Old_Cell_Centroids (Thread *);

FLUENT_EXPORT void Store_Slide_Metrics (Domain *);
FLUENT_EXPORT void Store_Slide_Face_Centroids (Thread *);
FLUENT_EXPORT void Store_Slide_Cell_Centroids (Thread *);

#define TWOD_AREA_X(v0,v1)(NODE_Y(v1) - NODE_Y(v0))
#define TWOD_AREA_Y(v0,v1)(NODE_X(v0) - NODE_X(v1))

#define AXI_AREA_X(v0,v1)\
((NODE_Y(v1) - NODE_Y(v0))*(NODE_Y(v1) + NODE_Y(v0))/2.)
#define AXI_AREA_Y(v0,v1)\
((NODE_X(v0) - NODE_X(v1))*(NODE_Y(v1) + NODE_Y(v0))/2.)

# define TRI_AREA_i(ND_CROSS_i,v0,v1,v2)(ND_CROSS_i(\
NODE_X(v1) - NODE_X(v0),NODE_Y(v1) - NODE_Y(v0),NODE_Z(v1) - NODE_Z(v0),\
NODE_X(v2) - NODE_X(v0),NODE_Y(v2) - NODE_Y(v0),NODE_Z(v2) - NODE_Z(v0))/2)

# define TRI_AREA_X(v0,v1,v2)TRI_AREA_i(ND_CROSS_X,v0,v1,v2)
# define TRI_AREA_Y(v0,v1,v2)TRI_AREA_i(ND_CROSS_Y,v0,v1,v2)
# define TRI_AREA_Z(v0,v1,v2)TRI_AREA_i(ND_CROSS_Z,v0,v1,v2)

# define QUAD_AREA_i(ND_CROSS_i,v0,v1,v2,v3)(ND_CROSS_i(\
NODE_X(v2) - NODE_X(v0),NODE_Y(v2) - NODE_Y(v0),NODE_Z(v2) - NODE_Z(v0),\
NODE_X(v3) - NODE_X(v1),NODE_Y(v3) - NODE_Y(v1),NODE_Z(v3) - NODE_Z(v1))/2)

# define QUAD_AREA_X(v0,v1,v2,v3)QUAD_AREA_i(ND_CROSS_X,v0,v1,v2,v3)
# define QUAD_AREA_Y(v0,v1,v2,v3)QUAD_AREA_i(ND_CROSS_Y,v0,v1,v2,v3)
# define QUAD_AREA_Z(v0,v1,v2,v3)QUAD_AREA_i(ND_CROSS_Z,v0,v1,v2,v3)

#if RP_3D
FLUENT_EXPORT real Calc_F_Area_X (face_t, Thread *);
FLUENT_EXPORT real Calc_F_Area_Y (face_t, Thread *);
FLUENT_EXPORT real Calc_F_Area_Z (face_t, Thread *);

# define Calc_F_Area_2D_X Calc_F_Area_X
# define Calc_F_Area_2D_Y Calc_F_Area_Y
# define Calc_F_Area_2D_Z Calc_F_Area_Z

#else /* !RP_3D */

# define Calc_F_Area_2D_X(f,t)TWOD_AREA_X(F_NODE(f,t,0),F_NODE(f,t,1))
# define Calc_F_Area_2D_Y(f,t)TWOD_AREA_Y(F_NODE(f,t,0),F_NODE(f,t,1))

# define Calc_F_Area_X(f,t)AXI_AREA_X(F_NODE(f,t,0),F_NODE(f,t,1))
# define Calc_F_Area_Y(f,t)AXI_AREA_Y(F_NODE(f,t,0),F_NODE(f,t,1))

#endif /* RP_3D */

#define F_AREA(A,f,t)NV_V(A, =, F_AREA_CACHE(f,t))
#define F_AREA_2D(A,f,t)NV_V(A, =, F_AREA_2D_CACHE(f,t))
#define F_AREA_2D_X(f,tf)(F_AREA_2D_CACHE(f,tf)[0])
#define F_AREA_2D_Y(f,tf)(F_AREA_2D_CACHE(f,tf)[1])
#if RP_3D
#define F_AREA_2D_Z(f,tf)(F_AREA_2D_CACHE(f,tf)[2])
#endif
#define ACCUMULATED_F_AREA(f,t)F_AREA_CACHE(f,t)
#define F_AREA_FRACTION_SIDE0(f, t) F_STORAGE_R(f, t, SV_AREA_FRACTION)
#define F_AREA_FRACTION_SIDE1(f, t) F_STORAGE_R(f, t, SV_AREA_FRACTION_SIDE1)
#define F_AREA_FRACTION(f, t) F_AREA_FRACTION_SIDE0(f, t)

#define F_DR0(A,f,t)NV_V(A, =, F_DR0_CACHE(f,t))
#define F_DR1(A,f,t)NV_V(A, =, F_DR1_CACHE(f,t))

/* for dynamic mesh */
FLUENT_EXPORT void Calc_F_Area_N (real *, face_t, Thread *tf);
FLUENT_EXPORT void Calc_F_Area_M1 (real *, face_t, Thread *tf);
# define F_AREA_N(A,f,t) Calc_F_Area_N (A, f, t)

#if RP_3D
FLUENT_EXPORT void Calc_F_Area_Init_Structure_3D (real *, face_t, Thread *tf,
                                                  int  *PTR_RESTRICT const cnz_index,
                                                  real *PTR_RESTRICT const x_init,
                                                  real *PTR_RESTRICT const y_init,
                                                  real *PTR_RESTRICT const z_init);
# define F_AREA_INIT_STRUCTURE_3D(A,f,t,cnz_index,x_init,y_init,z_init) \
   Calc_F_Area_Init_Structure_3D (A, f, t, cnz_index, x_init, y_init, z_init)
#endif

#if RP_2D
FLUENT_EXPORT void Calc_F_Area_Init_Structure_2D (real *, face_t, Thread *tf,
                                                  int  *PTR_RESTRICT const cnz_index,
                                                  real *PTR_RESTRICT const x_init,
                                                  real *PTR_RESTRICT const y_init);
# define F_AREA_INIT_STRUCTURE_2D(A,f,t,cnz_index,x_init,y_init) \
   Calc_F_Area_Init_Structure_2D (A, f, t, cnz_index, x_init, y_init)
#endif

#define C_SKEW(c,t) C_STORAGE_R(c,t,SV_SKEW)
#if RP_3D
#define F_SKEW(f,t) F_STORAGE_R(f,t,SV_SKEW)
#endif

#if RP_2D
# define F_DERIVATIVE_AREA(A,f,t) NV_V(A, =, F_AREA_2D_CACHE(f,t))
# define F_DERIVATIVE_AREA_CACHE(f,t) F_AREA_2D_CACHE(f,t)
# define C_DERIVATIVE_VOLUME(c,t) C_VOLUME_2D(c,t)
#else
# define F_DERIVATIVE_AREA(A,f,t) F_AREA(A,f,t)
# define F_DERIVATIVE_AREA_CACHE(f,t) F_AREA_CACHE(f,t)
# define C_DERIVATIVE_VOLUME(c,t) C_VOLUME(c,t)
#endif

#if RP_AXI
# define SV_DERIVATIVE_VOLUME SV_VOLUME_2D
# define SV_DERIVATIVE_AREA SV_AREA_2D
# define AXI_VOL(v0,v1)\
   ((NODE_Y(v0)*NODE_Y(v0) + \
     NODE_Y(v0)*NODE_Y(v1) + \
     NODE_Y(v1)*NODE_Y(v1))/6. * (NODE_X(v0) - NODE_X(v1)))
# define F_ON_AXIS_P(_f,_t) \
   (!SLIDING_INTERFACE_THREAD_P (_t) && \
    rp_axi &&            \
    (NODE_Y (F_NODE (_f,_t, 0)) < 1.0e-20 && \
     NODE_Y (F_NODE (_f,_t, 1)) < 1.0e-20))
#else
# define SV_DERIVATIVE_VOLUME SV_VOLUME
# define SV_DERIVATIVE_AREA SV_AREA
# define F_ON_AXIS_P(_f,_t) FALSE
#endif

/* Cell centroids */
#define C_CENTROID(_x,c,t)NV_V(_x,=,C_CENTROID_CACHE(c,t))
#define C_AVE_X(c,t)(C_CENTROID_CACHE(c,t)[0])
#define C_AVE_Y(c,t)(C_CENTROID_CACHE(c,t)[1])
#if RP_3D
# define C_AVE_Z(c,t)(C_CENTROID_CACHE(c,t)[2])
#else
# define C_AVE_Z(c,t)0.0
#endif
#define C_CENTROID_M1_CACHE(_c,_t) C_STORAGE_R_NV (_c, _t, SV_CENTROID_M1)
#define C_CENTROID_M1(_x,_c,_t) NV_V (_x, =, C_CENTROID_M1_CACHE (_c, _t))
#define C_CENTROID_SLIDE_CACHE(_c,_t) C_STORAGE_R_NV (_c, _t, SV_CENTROID_SLIDE)
#define C_CENTROID_SLIDE(_x,_c,_t) NV_V (_x, =, C_CENTROID_SLIDE_CACHE (_c, _t))

/* Face centroids */
#define F_CENTROID(x, f,t)NV_V(x, =, F_CENTROID_CACHE(f,t))
#define F_AVE_X(f,t)(F_CENTROID_CACHE(f,t)[0])
#define F_AVE_Y(f,t)(F_CENTROID_CACHE(f,t)[1])
#if RP_3D
# define F_AVE_Z(f,t)(F_CENTROID_CACHE(f,t)[2])
#else
# define F_AVE_Z(f,t)0.0
#endif
#define F_CENTROID_M1_CACHE(_f,_t) F_STORAGE_R_NV (_f, _t, SV_CENTROID_M1)
#define F_CENTROID_M1(_x,_f,_t) NV_V (_x, =, F_CENTROID_M1_CACHE (_f, _t))
#define F_CENTROID_SLIDE_CACHE(_f,_t) F_STORAGE_R_NV (_f, _t, SV_CENTROID_SLIDE)
#define F_CENTROID_SLIDE(_x,_f,_t) NV_V (_x, =, F_CENTROID_SLIDE_CACHE (_f, _t))

/* Face orientation check */
#if RP_2D
# define FACE_NEIGHBORS_ORIENTED_P(_f,_t,_n,_fn,_tn,_nn) (_n != _nn)
#else
# define FACE_NEIGHBORS_ORIENTED_P(_f,_t,_n,_fn,_tn,_nn) \
   (F_NODE (_f, _t, NEXT_INDEX (F_NNODES (_f, _t), _n)) != \
    F_NODE (_fn, _tn, NEXT_INDEX (F_NNODES (_fn, _tn), _nn)))
#endif

/* Grid velocity at face and cell centroids */
FLUENT_EXPORT void F_Velocity_Pos(real *V, const int f, const Thread *t, real NV_VEC(pos));
FLUENT_EXPORT void F_Velocity(real *V, const int f, const Thread *t);
FLUENT_EXPORT void F_MRF_Velocity(real *V, const int f, const Thread *t);
FLUENT_EXPORT void F_Solid_Velocity(real *V, const int f, const Thread *t);
#define F_VELOCITY F_Velocity

FLUENT_EXPORT void C_Velocity_Pos(real *V, const cell_t c, const Thread *t, real NV_VEC(pos));
FLUENT_EXPORT void C_Velocity(real *V, const cell_t c, const Thread *t);
#define C_VELOCITY C_Velocity

FLUENT_EXPORT real Cell_Height(cell_t c, Thread *tc,
                               face_t f, Thread *tf,
                               real *A, real At);
#define C_HEIGHT Cell_Height

FLUENT_EXPORT real Cell_Height_Wall(cell_t c, Thread *tc,
                                    face_t f, Thread *tf,
                                    real *A, real At, real ks);
#define C_HEIGHT_WALL Cell_Height_Wall

/* Approximate cell diameter: apply volume to a square/cube */
#if RP_3D
# define C_DIAMETER(c,t)cbrt(C_DERIVATIVE_VOLUME(c,t))
#else
# define C_DIAMETER(c,t)sqrt(C_DERIVATIVE_VOLUME(c,t))
#endif

/* check on cell/face type */
#define MIXED_OR_POLY_CELL_THREAD_P(t) \
 (((Cell_Element_Type)THREAD_ELEMENT_TYPE(t) == MIXED_CELL) || \
  ((Cell_Element_Type)THREAD_ELEMENT_TYPE(t) == POLY_CELL))
#define MIXED_OR_POLY_FACE_THREAD_P(t) \
 (((Face_Element_Type)THREAD_ELEMENT_TYPE(t) == MIXED_FACE) || \
  ((Face_Element_Type)THREAD_ELEMENT_TYPE(t) == POLY_FACE))

#define POLY_CELL_P(c,t) ((Cell_Element_Type)C_TYPE (c, t) == POLY_CELL)
#define GHOST_CELL_P(c,t)((Cell_Element_Type)C_TYPE (c, t) == GHOST_CELL)
#define MIXED_OR_POLY_CELL_P(c,t) \
  (((Cell_Element_Type)C_TYPE (c, t) == MIXED_CELL) || POLY_CELL_P (c, t))
#define POLY_OR_GHOST_CELL_P(c,t) \
  (((Cell_Element_Type)C_TYPE(c,t) == GHOST_CELL) || POLY_CELL_P(c,t))
#define POLY_FACE_P(f,t) ((Face_Element_Type)F_TYPE (f, t) == POLY_FACE)
#define MIXED_OR_POLY_FACE_P(f,t) \
  (((Face_Element_Type)F_TYPE (f, t) == MIXED_FACE) || POLY_FACE_P (f, t))

/* check on tri/tet cell */
#if RP_2D
# define SIMPLEX_CELL TRI_CELL
#else
# define SIMPLEX_CELL TET_CELL
#endif /* RP_2D */

#define SIMPLEX_CELL_P(c,t) ((Cell_Element_Type)C_TYPE(c, t) == SIMPLEX_CELL)
#define TET_OR_PYRAMID_CELL_P(c,t) \
  (((Cell_Element_Type)C_TYPE (c, t) == TET_CELL) || \
   ((Cell_Element_Type)C_TYPE (c, t) == PYRAMID_CELL))

#define C_ZERO_VOLUME_M1_P(c,tc)(SV_ALLOCATED_P_NEW(tc, SV_ZERO_VOLUME_M1) && \
                                 C_STORAGE_R(c, tc, SV_ZERO_VOLUME_M1) > 0.5)
#endif /* _FLUENT_METRIC_H */

