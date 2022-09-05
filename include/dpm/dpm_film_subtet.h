/*
 * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef DPM_FILM_SUBTET_H
#define DPM_FILM_SUBTET_H

#include "dpm.h"
#include "dpm_types.h"
#include "dpm_tools.h"
#include "global.h"


FLUENT_EXPORT void convert_to_free_stream_particle(Tracked_Particle *tp);
FLUENT_EXPORT void abort_or_convert_to_free_stream_particle(Tracked_Particle *tp);
FLUENT_EXPORT void convert_to_wall_film_particle(Tracked_Particle *tp, const face_t f, Thread *tf);
FLUENT_EXPORT void convert_to_wall_film_particle_nci(Tracked_Particle *tp, const face_t f, Thread *tf,
                                                     const face_t f_int, Thread *tf_int);
FLUENT_EXPORT void project_particle_to_film(Tracked_Particle *tp);
FLUENT_EXPORT void project_point_to_wall_film_face(double pos[3], struct global_tracked_particle_vars_struct *pgvtp, const double t_delta);
FLUENT_EXPORT void project_point_to_wall_with_normal(double pos[3], struct global_tracked_particle_vars_struct *pgvtp, const double normal[3],
                                                     const double t_delta);
FLUENT_EXPORT void release_particle_from_film(Tracked_Particle *tp);
FLUENT_EXPORT void abort_or_release_particle_from_film(Tracked_Particle *tp);

FLUENT_EXPORT cxboolean get_subtet_face_normal(struct global_tracked_particle_vars_struct *pgvtp, double normal[3], const double t_delta);
FLUENT_EXPORT cxboolean is_point_on_face(const double pos[3], const face_t f, Thread *tf, const double t_delta, const double tolerance);
FLUENT_EXPORT cxboolean is_point_on_wall_film_face(const double pos[3], Tracked_Particle *tp, const double dt);


#endif  /* #ifndef DPM_FILM_SUBTET_H */


