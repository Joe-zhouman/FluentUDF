/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef DPM_SUBTET_H
#define DPM_SUBTET_H

#include "dpm.h"
#include "dpm_types.h"
#include "dpm_tools.h"
#include "global.h"


/**
 * @addtogroup dpm Discrete Particle Model
 * @{
 *
 * @file
 * DPM: functions required for subtet tracking
 *
 */

#define DIM ND_ND
#define FACES_PER_SUBTET (DIM+1)
#define NODES_PER_SUBTET_FACE (DIM)

#define PARENT_TOLERANCE    (FLT_EPSILON * 1000.0)        /* relaxed tolerance for finding new parent face */
#define FILM_FACE_TOLERANCE (FLT_EPSILON * 100.0)         /* used when relocating film particles after mesh update */
#define LOCATE_TOLERANCE    (DBL_EPSILON * 10000.0)       /* tolerance when locating a point within a subtet */
#define ENSURE_TOLERANCE    (DBL_EPSILON * 100.0)         /* tolerance when making certain a point is within a subtet */
#define T_DELTA_TOLERANCE   (DBL_EPSILON * 50.0)          /* tolerance when deciding if interpolation is required */

#define MAX_SUBTET_INTERSECTIONS 100                      /* maximum number of intersections within a given cell */


/* struct for keeping running averages */
typedef struct running_ave_values
{
  int n_values;
  int oldest;
  double *values;
  struct subtet_tracking_location_struct *loc;
} Running_Ave;

/*
 * @brief
 * struct to store necessary information regarding the
 * parent cell face with which the subtet is associated.
 */
typedef struct subtet_tracking_location_struct
{
  /* parent cell face that contains one side of the subtet */
  face_t f;
  Thread *tf;

  /* all nodes of the associated face */
  Node *faceNodes[MAX_FACE_NODES + 1];
  int numFacePts;    /* 3 for tri face, 4 for quad face, etc. */

  /* the coordinates and velocity of the face nodes */
  double facePts[MAX_FACE_NODES + 1][3];
  double facePtsVel[MAX_FACE_NODES + 1][3];

  /* nodes used for the subtet (beside face and cell centroids) */
  Node *tetNodes[4];
  int numTetNodes;    /* 2 for poly face, 3 for quad face, 4 for tet cells, etc. */

  /* coordinates and velocity of the subtet points */
  double tetPts[4][3];
  double tetPtsVel[4][3];

  /* index of first face node when constructing subtet */
  int inode;

  /* forward (0) or reverse (1) ordering */
  int order;

  /* particle might have changed cell */
  cxboolean eval_bc;

  /* validity of subtet - indicates if this subtet is degenerate */
  cxboolean degenerate;

  /* hanging node parameters - use child face nodes if face, f, corresponds to a parent face  */
  int faceIndxChild;
  int subtet_face_crossed;

  cxboolean hold_constant;               /* flag to prevent subtet from being modified */
  cxboolean new_subtet;                  /* the particle has entered a new subtet */
  cxboolean hold_vel_constant;           /* hold the velocity constant for a timestep after a reflection */
  cxboolean velocity_updated;            /* indicates the velocity was updated at the crossing point */
  cxboolean barycentric_intersections;   /* use barycentric intersections when true */
  cell_t    current_cell;

  double r_matrix[3][3];
  double bary_coords[4];

  int in_plane_index;                    /* subtet face index when traveling within a plane */


  /* variables for wall film particles (and oil flow pathlines with subtet tracking) */
  cxboolean wall_film_needs_update;      /* indicates the particle has left the last face and is searching for the next */

  /* wall film face */
  int wall_film_face_index;              /* subtet face index */
  face_t   f_wall_film;                  /* cell face index */
  Thread *tf_wall_film;                  /* NNULLP(tf_wall_film) indicates the particle is on the wall */
  face_t   f_interface;                  /* face index for the nci */
  Thread *tf_interface;                  /* face thread for the nci */

  Node *edgeNodes[2];                    /* pointers to the nodes of the wall-film edge crossed */
  cxboolean on_edge;                     /* indicates we have just completed grid walking to the new wall film face */

  double normal[3];                      /* wall film face normal */

  /* film variables used for physics, not tracking (and can therefore be reals) */
  real film_vel[3];                      /* wall film velocity */
  real cell_vel[3];                      /* continuous phase cell velocity */
  real film_height;                      /* wall film height */
  real film_face_area;                   /* area of the wall film face */

  cxindex   global_face_id;              /* global face index of face crossed (for particle migration) */
  cxboolean separates;                   /* indicates all separation criteria except face angle have been met */
  int       separation_model;            /* film separation model */
  real      separation_angle;            /* minimum angle for film separation */

  Tracked_Particle *tp;
  gtpv_t oil_flow_vars;                  /* cell face eqns and other variables for oil flow with legacy intersections */

  CX_Cell_Id last_solve_cell;            /* for two-way coupling in overset meshes */

  /* for velocity-based time-step adaption */
  real prevVel[3];

  /* for GTI mixing plane */
  real vel_gti[3];
  real pos_gti[3];
  real num_in_parcel_gti;

  struct running_ave_values t_cross_sum; /* to detect particles stuck at faces/edges */

} Subtet_Tracking_Location;


/**
 * @brief
 * struct to contain variables required when tracking through adapted meshes
 *
 * Keep this struct small because it must be copied each
 * time intersect_subtet_with_ray is called.
 */
typedef struct subtet_lightweight_struct
{
  face_t f;
  Thread *tf;
  int numTetNodes;

  Node *tetNodes[4];
  double tetPts[4][3];

} Subtet_LightWeight;


struct global_tracked_particle_vars_struct;
struct tracked_particle_struct;


FLUENT_EXPORT void coord_and_vel_cell(const cell_t c, const Thread *tc, double (*co_ord)[3], double (*pt_vel)[3],
                                      const cxboolean interpolate_in_time);
FLUENT_EXPORT void coord_and_vel_face(const face_t f, const Thread *tf, double (*co_ord)[3], double (*pt_vel)[3],
                                      const cxboolean interpolate_in_time);
FLUENT_EXPORT void coord_and_vel_node(const int n_nodes, Node **nodes, double (*co_ord)[3], double (*pt_vel)[3],
                                      const cxboolean interpolate_in_time);

FLUENT_EXPORT void ensure_point_is_in_cell(double *pos, CX_Cell_Id *cell, const double dt);
FLUENT_EXPORT void get_face_normal(double normal[3], const face_t f, Thread *tf, const double t_delta);
FLUENT_EXPORT void get_node_position(double pt[3], Node *node, const double t_delta);
FLUENT_EXPORT void get_plane_velocity(const double pos[3], double facePts[][3], double facePtV[][3], double planeVel[3],
                                      double normal[3], const double t_delta);
FLUENT_EXPORT void init_subtet_object(Tracked_Particle *tp, struct subtet_tracking_location_struct *loc);
FLUENT_EXPORT void interpolate_subtet_points(struct subtet_tracking_location_struct *loc, const double t_delta, double (**vtx_coord)[3]);
FLUENT_EXPORT void remove_particle_from_subtet_plane(double pos[3], const double dt, struct subtet_tracking_location_struct *loc, const double factor);

FLUENT_EXPORT int search_cell_for_degenerate_subtets(const cell_t c, Thread *tc, const int verbosity, double point[3],
                                                     cxboolean *in_subtet, struct subtet_tracking_location_struct *loc, const double dt);
FLUENT_EXPORT int Search_Domain_For_Degenerate_Subtets(Domain *domain, const int verbosity);
FLUENT_EXPORT int set_subtet_tracking_location(struct subtet_tracking_location_struct *loc, CX_Cell_Id *cell,
                                               const double t_delta, const double *pos, const Subtet_LightWeight *loc_current);

#if RP_3D
FLUENT_EXPORT cxboolean ensure_point_is_in_subtet_wallfilm(double pos[3], const double dt, Subtet_Tracking_Location *loc);
#endif
FLUENT_EXPORT cxboolean ensure_point_is_in_subtet(double pos[3], const double dt, Subtet_Tracking_Location *loc);
FLUENT_EXPORT cxboolean is_point_in_cell(const double *pos, CX_Cell_Id *cell, const double dt, const double tol);
FLUENT_EXPORT cxboolean is_point_in_subtet(const double *pos, double tetPts[4][3], const double epsilon,
                                           double (* p_r_matrix)[3][3], double bary_coors[4]);
FLUENT_EXPORT cxboolean particle_is_stuck_p(struct tracked_particle_struct *tp);

/* wrappers to expose static and inline functions for UDFs */
FLUENT_EXPORT void Get_Subtet_Center(double centroid[3], double tetPts[4][3]);
FLUENT_EXPORT void Move_Particle_Towards_Point(double pos[3], const double point[3], const double factor);
FLUENT_EXPORT void Interpolate_Subtet_Points(struct subtet_tracking_location_struct *loc, const double t_delta, double (**vtx_coord)[3]);

FLUENT_EXPORT double Get_T_Delta(Tracked_Particle *tp);
FLUENT_EXPORT double Get_Particle_T_Delta(Particle *p);
FLUENT_EXPORT double Get_Minimum_T_Delta(CX_Cell_Id *cell);

FLUENT_EXPORT cxboolean Interpolate_Mesh_In_Time_P(const real t_delta);

/* @} dpm */

#endif   /* #ifndef DPM_SUBTET_H */

