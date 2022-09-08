/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DPM_DEM_H
#define _FLUENT_DPM_DEM_H

#include "dpm_types.h"
#include "threads.h"
#include "dpm_dem_wall.h" /* need struct dpm_collision_wall  */
#include "binary_params.h"

/**
 * @addtogroup dpm Discrete Particle Model
 * @{
 *
 * @file
 * data types and routines for DEM particles
 */

/* DEM
 *
 * Data structures for collisions. Here for information NOT stored on the particles themselves.
 */


enum collision_time_integration_scheme
{
  COLLISION_PSEUDO_EULER,               /* "semi-implicit" Euler ... , like in Mohan-udf */
  COLLISION_TRAPEZOIDAL,
  COLLISION_STOERMER_VERLET,
  COLLISION_STOERMER_VERLET_VELOCITY,   /* forces depend on position only, i.e., NO   dashpot term */
  COLLISION_STOERMER_VERLET_VELOCITY_2  /* forces may depend on velocity,  i.e., WITH dashpot term */
};

typedef struct dem_ctrl_struct  /* reflecting user input */
{
  cxboolean dem_on;
  int last_update;

  /* admininistration flags etc.
   */
  int n_collision_substeps_in_time;
  enum collision_time_integration_scheme time_integration_scheme;

  real max_particle_velocity;

  cxboolean adaptive_edge_length;
  real      edge_length_factor;
  real      static_edge_length;
  real      force_range_factor;

  /* Move particles directly after collisions and do not invoke
   * particle tracking routine at all, locate particles after
   * collisions.  Else particle tracking gets called.  As of
   * 2010-05-19: experimental. Already useful for debugging.
   */
  cxboolean inhibit_particle_tracking;
  cxboolean ot_based_collision; /* use loose octree based collision partner search */


  cxboolean skip_acceleration_calculation; /* external trigger for dpm_laws.c:ParticleAcceleration
                                            * default of zero means FALSE, i.e., normal operation.
                                            */

  real friction_force_equiv_min_acceleration; /* lower limit on friction force.  Do not
                                               * bother about friction, if a force on a
                                               * parcel gives less acceleration.
                                               */
  cxboolean use_cartesian_cm;


} dem_ctrl_t;


extern FLUENT_EXPORT dem_ctrl_t dem_ctrl;


typedef struct cartesian_mesh_struct  /* holding (potentially many) data computed at runtime */
{
  cxboolean need_periodic_update;

  int *flags;     /* one set of flags for each collision cell */
  int *flags_periodic;

#if ! UDF_COMPILER /* ATTENTION: int64_t is not accepted by the udf interpreter. */

  int64_t n_cc;   /* number of collision cells */

  int64_t *head;  /* Head of particle list for each collision mesh cell.
                   * One entry per collision mesh cell.
                   */
  int64_t n_pp;   /* number of (real) particles/parcels           */

  int64_t n_pp_alloc; /* tribute to ghost particles: number of allocated entries in *lpl and **p arrays */

  int64_t *lpl;   /* Particle List: One entry per particle/parcel in the domain */
  Particle **p;   /* Array of pointers to particles/parcels       */


  real    NV_VEC(maxpos);         /* right background upper corner     */
  real    NV_VEC(minpos);         /* left  foreground lower corner     */
  int64_t NV_VEC(n_edges);        /* number of edges in each direction */
  int64_t NV_VEC(offset);         /* to convert between directional indices and cell number */
  real    NV_VEC(edge_length);    /* length of edges in each direction */
#if PARALLEL
  real    NV_VEC(maxpos_global);  /* right background upper corner     */
  real    NV_VEC(minpos_global);  /* left  foreground lower corner     */
  int64_t NV_VEC(n_edges_global); /* number of edges in each direction */
  int64_t NV_VEC(offset_global);  /* to convert between directional indices and cell number */

  /* To convert between local and global directional indices: */
  int64_t NV_VEC(minpos_index);   /* Directional indices of local minpos in global collision mesh.
                                   * These are valid indices for cells belonging to the local mesh.
                                   */
  int64_t NV_VEC(maxpos_index);   /* Directional indices of local maxpos in global collision mesh.
                                   * First INVALID indices for the local collision mesh, since indices
                                   * apply for the lower-left-front corner of a collision cell.
                                   */
#endif

#if RP_NODE
  int64_t **ghost_cc;          /* For each neighbor partition, have an array of collision cells that
              * are in the vicinity of the partition boundary towards that neighbor.
                                */
  int64_t *n_ghost_cc;         /* number of           ghost collision cells for each neighbor partition. */
  int64_t *n_ghost_cc_alloc;   /* number of allocated ghost collision cells for each neighbor partition. */
  Thread ***ghost_cc_periodic; /* For each neighbor partition, have an array of face threads of periodic boundary
                                * faces coresponding to a partition boundary towards the "periodic neighbor".
                                */
  cat_t ***periodic_cat;       /* For each neighbor , have an array of internal partition boundary cells, i.e. a
                                * part of the neighbor->int_cl_ext list which have a face corresponding to a periodic
                                * boundary face thread
                                */
  Thread ***periodic_tf;       /* For each neighbor, have an array of periodic boundary face threads */
  int64_t n_periodic_tf;
#endif /* RP_NODE */

  Particle *ghost_pl;  /* List of ghost particles RECEIVED from other partitions or from a periodic partnet boundary face thread
                        * Those are NOT sorted into injections!
                        */
  int64_t n_ghost_pl;  /* number of ghost particles/parcels */



  dpm_collision_wall_t *bcoll;


#endif /* ! UDF_COMPILER */

} cartesian_mesh_t;

extern FLUENT_EXPORT cartesian_mesh_t dem_cartesian_mesh;

extern FLUENT_EXPORT interaction_partner_table_t dem_collision_partner_table;


/* DEM  collision cell flags:  DEM_CC_FLAG....
 */
#define DEM_CC_FLAG_HAS_WALLS      (1)
#define DEM_CC_FLAG_IS_GHOST_CC    (1<<1)
#define DEM_CC_FLAG_IS_PERIODIC_CC (1<<2)

#define DEM_CC_FLAG_P(cartesian_mesh, icc, flag)     (cartesian_mesh->flags[icc] &   (flag))
#define DEM_SET_CC_FLAG(cartesian_mesh, icc, flag)   (cartesian_mesh->flags[icc] |=  (flag))
#define DEM_CLEAR_CC_FLAG(cartesian_mesh, icc, flag) (cartesian_mesh->flags[icc] &= ~(flag))

#define DEM_INTEGRATE_DURING ( DURING_TRACKING == dpm_par.spray_suite.collision_mode || DURING_UPDATE == dpm_par.spray_suite.collision_mode )

/* DEM end of  data structures for collisions. Here for information NOT stored on the particles themselves.
 */


/* DEM
 */
FLUENT_EXPORT void Fill_dem_collision_partner_table(void);

FLUENT_EXPORT void      Reset_Cartesian_Mesh(cartesian_mesh_t *cartesian_mesh);
FLUENT_EXPORT void Initialize_Cartesian_Mesh(cartesian_mesh_t *cartesian_mesh);
FLUENT_EXPORT void       Fill_Cartesian_Mesh(cartesian_mesh_t *cartesian_mesh);

FLUENT_EXPORT void Reset_Cartesian_Mesh_Wall_Intersection(cartesian_mesh_t *cartesian_mesh);
FLUENT_EXPORT void  Fill_Cartesian_Mesh_Wall_Intersection(cartesian_mesh_t *cartesian_mesh);

#if RP_NODE
FLUENT_EXPORT void DEM_Reset_Ghost_Cc(cartesian_mesh_t *cartesian_mesh);
FLUENT_EXPORT void DEM_Allocate_Ghost_Cc(cartesian_mesh_t *cartesian_mesh);
FLUENT_EXPORT void DEM_Initialize_Ghost_Cc(cartesian_mesh_t *cartesian_mesh);
FLUENT_EXPORT void Fill_Cartesian_Mesh_Ghost_Cc(cartesian_mesh_t *cartesian_mesh);
FLUENT_EXPORT void DEM_Get_Ghost_Particles(cartesian_mesh_t *cartesian_mesh, cxboolean allow_collision_mesh_extension);
FLUENT_EXPORT void DEM_Allocate_Parallel_Periodic(cartesian_mesh_t *cartesian_mesh);
FLUENT_EXPORT void DEM_Initialize_Parallel_Periodic(cartesian_mesh_t *cartesian_mesh);
FLUENT_EXPORT void DEM_Reset_Parallel_Periodic(cartesian_mesh_t *cartesian_mesh);
FLUENT_EXPORT void Build_Update_Cartesian_Mesh_Parallel_Periodic(cartesian_mesh_t *cartesian_mesh);
#endif /* RP_NODE */

FLUENT_EXPORT void DEM_Cleanup_Ghost_Particles(cartesian_mesh_t *cartesian_mesh);

FLUENT_EXPORT void DEM_Get_Ghost_Particles_Periodic(cartesian_mesh_t *cartesian_mesh);

FLUENT_EXPORT void dem_update_cartesian_mesh_with_ghost_particles(cartesian_mesh_t *cartesian_mesh, cxboolean adapt_cm);

FLUENT_EXPORT void DEM_Initialize_Particle_Collision_Storage(void);
FLUENT_EXPORT void DEM_Update_Collision_Partner_Indices(Domain *domain);

FLUENT_EXPORT void Get_Face_Bounding_Box_Coordinates(face_t f, Thread *t, real xfmin[], real xfmax[]);
FLUENT_EXPORT void Get_Cell_Bounding_Box_Coordinates(cell_t c, Thread *t, real xfmin[], real xfmax[]);


#if ! UDF_COMPILER
FLUENT_EXPORT cxboolean Bounding_Box_Intersects_Cartesian_Mesh(real xfmin[], real xfmax[], cartesian_mesh_t *cartesian_mesh);
FLUENT_EXPORT void Get_Bounding_Box_Cartesian_Mesh_Coverage(real xfmin[], real xfmax[], int64_t idxmin[], int64_t idxmax[], cartesian_mesh_t *cartesian_mesh);
FLUENT_EXPORT void Compute_Cartesian_Mesh_Global(real *minpos, real *maxpos,
                                                 int64_t *n_edges, real *edge_length,
                                                 int64_t *offset, real margin);
FLUENT_EXPORT void DEM_Compute_Global_Collision_Mesh(real minpos[], real maxpos[],
                                                     int64_t n_edges[], real edge_length[],
                                                     int64_t offset[], const real margin);
#if RP_NODE
FLUENT_EXPORT void DEM_Compute_Local_Collision_Mesh(real          minpos[],
                                                    real          maxpos[],
                                                    int64_t       n_edges[],
                                                    int64_t       offset[],
                                                    int64_t       minpos_index[],
                                                    int64_t       maxpos_index[],
                                                    const real    minpos_global[],
                                                    const real    maxpos_global[],
                                                    const int64_t n_edges_global[],
                                                    const real    edge_length[],
                                                    const real    margin
                                                   );

FLUENT_EXPORT int64_t DEM_Local_To_Global_Cellno(int64_t cellno, cartesian_mesh_t *cartesian_mesh);
FLUENT_EXPORT int64_t DEM_Global_To_Local_Cellno(int64_t global_cellno, cartesian_mesh_t *cartesian_mesh);
#endif  /* RP_NODE */

#endif /* ! UDF_COMPILER */


FLUENT_EXPORT int64_t DEM_Get_Cartesian_Cell_Number_For_Point(real *xxx, cartesian_mesh_t *cartesian_mesh);

FLUENT_EXPORT void DEM_Cartesian_Collision_Mesh_Loop(void (*particle_particle)(Particle *, Particle *),
                                                     void (*particle_wall)(Particle *, dpm_collision_face_t *)
                                                    );



FLUENT_EXPORT void DEM_Calculate_Non_Collision_Acceleration(real time_step);
FLUENT_EXPORT void DEM_Collide_Particles_Single_Substep(real time_step);
FLUENT_EXPORT void DEM_Limit_Particle_Velocity(real *vel);

FLUENT_EXPORT void set_collision_partner_search_method(void);
FLUENT_EXPORT void dem_particle_particle_collision(Particle *pi, Particle *pj);
FLUENT_EXPORT void dem_particle_wall_collision(Particle *pi, dpm_collision_face_t *face_data);
FLUENT_EXPORT void dem_add_forces_from_sub_step(void);
FLUENT_EXPORT int get_thread_dpm_bc_collision_partner_index(Thread *thread);


#endif /* _FLUENT_DPM_DEM_H */
