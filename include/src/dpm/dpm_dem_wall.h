/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DPM_DEM_WALL_H
#define _FLUENT_DPM_DEM_WALL_H

/**
 * @addtogroup dpm Discrete Particle Model
 * @{
 *
 * @file
 *
 * Header file for DEM particles and their collison with ANY BOUNDARY, not
 * just walls as the name of the file might suggest.  But collision
 * with a wall is just so much the predominant case that this choice
 * of file name appears to be acceptable.
 *
 */


/* Construct collision faces as triangles from the
 * outset instead splitting the true mesh faces into triangles
 * at a later time, i.e., in compute_detailed_distance2_to_face.
 * So all collision faces are triangles.
 */
typedef struct dpm_collision_face
{
  Thread *t;          /* need the collision partner!    .... anything else? */
  face_t f;           /* face index of boundary thread face needed to store dem wall collision forces on boundary thread face SVar */
  int neighbor_idx;   /* index of home partition the collision face orginates from */
  int64_t pfcoll_idx; /* index in cartesian_mesh->bcoll->pfcoll array */
  real pfd;           /* point-face distance                               */
  real NV_VEC(pof);   /* point-on-face: the point on the face used for pfd */
  real weight;        /* collision force weight */

  /* Geometry data: Only triangles !! */
  real A[ND_ND];         /* face normal */
  real C[ND_ND];         /* face centroid */
  real vx[ND_ND][ND_ND]; /* face node coordinates of an edge in 2D or a triangle in 3D */

  real wall_collision_force[3]; /* collision force on wall caused by DEM particles */

  real u_wall[3];   /* explicit(!) components of wall velocity from BCs */
  real T;           /* wall temperature */
} dpm_collision_face_t;

#define F_DATA_THREAD(pface_data)         ((pface_data)->t)
#define F_DATA_FACE(pface_data)           ((pface_data)->f)
#define F_DATA_NEIGHBOR_IDX(pface_data)   ((pface_data)->neighbor_idx)
#define F_DATA_PFD(pface_data)            ((pface_data)->pfd)
#define F_DATA_WEIGHT(pface_data)         ((pface_data)->weight)
#define F_DATA_POF(pof_,pface_data)       NV_V((pof_), =, (pface_data)->pof)
#define F_DATA_POF_CACHE(pface_data)      ((pface_data)->pof)
#define F_DATA_AREA(A_,pface_data)        NV_V((A_)  , =, (pface_data)->A)
#define F_DATA_AREA_CACHE(pface_data)     ((pface_data)->A)
#define F_DATA_CENTROID(C_,pface_data)    NV_V((C_)  , =, (pface_data)->C)
#define F_DATA_CENTROID_CACHE(pface_data) ((pface_data)->C)
#define F_DATA_NODE_COORD(pface_data)     ((pface_data)->vx)
#define F_DATA_WALL_COLLISION_FORCE_CACHE(pface_data)   ((pface_data)->wall_collision_force)
#define F_DATA_UWALL3_CACHE(pface_data)   ((pface_data)->u_wall)
#define F_DATA_TEMPERATURE(pface_data)    ((pface_data)->T)


/* ATTENTION: int64_t is not accepted by the udf interpreter. Must guard by  "!UDF_COMPILER"
 */
#if !UDF_COMPILER
typedef struct dpm_collision_bcc_struct
{
  int64_t cellno;  /* serial index of a boundary cartesian cell;
        * i.e., a cartesian cell in the vicinity of a face of a reflecting boundary */
  int64_t ifcoll; /* that boundary face: index into the array pfcoll */
} dpm_collision_bcc_t;
#endif

typedef struct dpm_collision_wall
{
#if !UDF_COMPILER
  dpm_collision_bcc_t *bcc; /* array(!) of boundary collision cells;
           * i.e., collision cells in the vicinity of a reflecting boundary */

  int64_t n_bcc;            /* number of boundary collision cells           */
  int64_t n_bcc_alloc;      /* number of boundary collision cells allocated */
#endif

  dpm_collision_face_t *pfcoll; /* the array of collision faces */
#if !UDF_COMPILER
  int64_t n_pfcoll;         /* number of collision faces           */
  int64_t n_pfcoll_alloc;   /* number of collision faces allocated */
#endif
} dpm_collision_wall_t;

int get_boundary_face_node_coords(face_t f, Thread *tf, real vcoord[][3]);

#endif /* _FLUENT_DPM_DEM_WALL_H */
