/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/
#ifndef _FLUENT_DEM_OT_COLLISION_H
#define _FLUENT_DEM_OT_COLLISION_H

#include "dpm_dem_wall.h"
#include "dpm_types.h"
#include "threads.h"
#include "loose_octree.h"

/* this is the element type for particles indexed by search tree */
typedef struct ot_particle_element_s
{
  octree_element_t octree_element;
  Particle *p;
} ot_particle_element;

FLUENT_EXPORT ot_particle_element *create_particle_octree_element(Particle *p, void *otpe_storage);

FLUENT_EXPORT void dem_compute_all_collisions_ot(void);
FLUENT_EXPORT int compute_particle_face_collision_weight(dpm_collision_face_t *face_data, real p_pos[], real colrng);
FLUENT_EXPORT void triangle_rbbox(real tri_coord[ND_ND][ND_ND], octree_rbbox *rbbox, real add_range);
FLUENT_EXPORT void create_collision_face_from_triangle(face_t f, Thread *t, real tri_coord[ND_ND][ND_ND], dpm_collision_face_t *face_data);

#endif /* _FLUENT_DEM_OT_COLLISION_H */
