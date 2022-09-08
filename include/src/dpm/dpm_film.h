/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef DPM_FILM_H
#define DPM_FILM_H

#include "dpm_types.h"


/* ***** wall film functions defined in <dpm_film.c> */

FLUENT_EXPORT void Calculate_Film_Face_Variables (Domain *domain);
FLUENT_EXPORT void check_wallfilm_particle(Particle *p, const real t_delta, double wall_eqn1[3], double wall_eqnV[3]);
FLUENT_EXPORT void clear_wallfilm_particle(Particle *p);
FLUENT_EXPORT void abort_or_clear_wallfilm_particle(Particle *p);
FLUENT_EXPORT void FilmParticleAcceleration (Tracked_Particle *, real[], real[], real *);
FLUENT_EXPORT void FilmInertHeatingLaw(Tracked_Particle *);
FLUENT_EXPORT void FilmVaporizationLaw(Tracked_Particle *);
FLUENT_EXPORT void get_position_of_spawned_particles(real pos_new[3], Tracked_Particle *tp);
FLUENT_EXPORT void Init_Wall_Film(Domain *domain, cxboolean post_p);
FLUENT_EXPORT void Init_Wall_Film_After_Flow_Init(Domain *domain);
FLUENT_EXPORT void print_wallfilm_particles(void);
FLUENT_EXPORT void Reset_Wall_Film_Particles(Injection *I);
FLUENT_EXPORT void rotate_wall_film_particle_velocities(Tracked_Particle *tp, Node *v0, Node *v1, real angle);
#if RP_3D
FLUENT_EXPORT void rotate_velocity_into_film_plane(Tracked_Particle *tp);
#endif

/* FLUENT_EXPORT void Save_Prev_Wall_Film_Data(Domain *domain); */
FLUENT_EXPORT void Accumulate_Wallfilm_Properties(Tracked_Particle *tp);
FLUENT_EXPORT void Deposit_Cache_Film_Props(Tracked_Particle *tp);
FLUENT_EXPORT void Splash_Particle(Tracked_Particle *tp, Particle *p, const real f_normal[], const real imp_ang, real rel_vel[],
                                   real vp_d[], const real rel_dot_n, const int n_samp, const cxboolean update);
FLUENT_EXPORT void Update_Wall_Film(Domain *domain, cxboolean post_p);
FLUENT_EXPORT void Update_Wall_Film_OLD(Domain *domain, cxboolean post_p);
FLUENT_EXPORT Path_Status Wall_Film_Interaction(Tracked_Particle *tp, Particle *pn, const real f_normal[], const face_t f, Thread *t, const cxboolean update);
FLUENT_EXPORT void add_particle_to_film_face_mass_and_height(face_t f, Thread *t, real parcel_mass, real face_area_rho);
FLUENT_EXPORT void Wall_Jet_Film(Tracked_Particle *tp, const real normal[], real rel_vel[]);

FLUENT_EXPORT int getintersectingedge(real pos[], Tracked_Particle *tp, real *min_t, int *int_edge, real beta, real acc[]);
FLUENT_EXPORT real Get_hw(Tracked_Particle *tp, real ktc, real area_face, real *Pr_term);
FLUENT_EXPORT real bl_film_transfer_gas(Tracked_Particle *tp, real tCond, real visc, real rho, real cp, real k_lam, cxboolean thermal, int gas_index);
FLUENT_EXPORT real film_Nu_Sh_gas(Tracked_Particle *tp, const real len, const real psn);
FLUENT_EXPORT void store_impingement_data(Tracked_Particle *tp, Particle *p, const real rel_dot_n);
FLUENT_EXPORT cxboolean check_for_film_separation(Tracked_Particle *tp, Particle *p, const face_t f_new, Thread *tf_new,
                                                  const real vel_unit[3], const real angle, Node *nodes[2], const cxboolean update);
FLUENT_EXPORT cxboolean check_wallfilm_threads(Domain *);
FLUENT_EXPORT cxboolean compute_walleqn_at_t_delta(double weqn[3], Tracked_Particle *tp);
FLUENT_EXPORT cxboolean find_wallfilm_face(Domain *domain, Particle *p, const real t_delta, double wall_eqn1[3], double wall_eqnV[3]);
FLUENT_EXPORT cxboolean find_wallfilm_face_on_cell(Domain *domain, Particle *p, const real t_delta);
FLUENT_EXPORT cxboolean Particle_Film_Area(Tracked_Particle *, real *, real *, real *, real *);

FLUENT_EXPORT Path_Status Check_Film_Face_Angle(Tracked_Particle *tp, Particle *p, real pos[3], Thread *t_new, const face_t f_new, int edge_crossed, Thread *t_old,
                                                const face_t f_old, const cxboolean update);
FLUENT_EXPORT Path_Status FindFilmNeighbour(real [], real [], Tracked_Particle *, Particle *, real [], real [], real, int *, cxboolean, real);
FLUENT_EXPORT Path_Status update_tracked_wall_particle_at_new_face(Tracked_Particle *tp, face_t f, Thread *tf, cxboolean update_summary, real pos[]);
FLUENT_EXPORT Path_Status update_tracked_wall_particle_at_old_face(Tracked_Particle *tp, real min_t, real vel[], real acc[], real dvdt[], real beta, cxboolean update_summary);

FLUENT_EXPORT void update_wallfilm_particle(Particle *p, face_t f, Thread *tf);
FLUENT_EXPORT void Move_To_Film_Height(face_t f, Thread *tf, real pos[], real factor);
FLUENT_EXPORT void Apply_Leidenfrost_Limit(Tracked_Particle *tp, real *Tw);
FLUENT_EXPORT void Check_Critical_Flux(Tracked_Particle *tp, real *vap_rate, cxboolean limit);

FLUENT_EXPORT void Patch_LWF(Thread *t);
FLUENT_EXPORT cxboolean Patch_Film_Particle(face_t f, Thread *tf, Injection *I, real A, int *int_film_parcel_number);
FLUENT_EXPORT void Reset_LWF(void);

#endif /* #ifndef DPM_FILM_H */
