/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DPM_PATH_H
#define _FLUENT_DPM_PATH_H

#include "dpm_types.h"
#include "threads.h"
#include "dpm.h"        /* e.g. for dpm_bc_type_t */

/**
 * @addtogroup dpm Discrete Particle Model
 * @{
 *
 * @file
 * routines for tracking particles
 */

/**
 * @addtogroup dpm_create creating particles
 * @{ */

typedef struct
{
  Thread *thread;
  int surf_id;
  cxindex lfid;
  cxindex gfid;
  real a;
} surface_select_t;

FLUENT_EXPORT int facet_select_scan(int n_facets, surface_select_t **facet_select,
                                    int *a_offset, cxboolean accum_area, int *a_size, real scale_area);

/**
 * @addtogroup dpm_create_rr Rosin-Rammler size-distribution
 * @{
 *************************************************************/

FLUENT_EXPORT void
I_extract_rr_parameters(Injection *Ilist, double d10, double d1_max, double d1_min, double spray_mass,
                        double *rr_diam, double *spread_param, double *rr_fit_error);
FLUENT_EXPORT void extract_rr_parameters(real, real, real, real, int, real *, double *, double *, double *);
FLUENT_EXPORT real compute_rr_delta_d(Injection *);
FLUENT_EXPORT real compute_rr_norm(Injection *);
FLUENT_EXPORT real compute_rr_diam(Injection *, int);
FLUENT_EXPORT real compute_rr_flowrate(Injection *, real, real);
FLUENT_EXPORT real Rosin_Rammler(uniform_random_seed *, real, real);
/* @} dpm_create_rr */

/**
 * @addtogroup dpm_create_nonatom non-atomizers
 * @{
 *************************************************************/

FLUENT_EXPORT void Read_Discrete_Diam_from_Table(const char *table_name, const int ref_diam_indx, const int mass_frc_indx, cxboolean mas_frc_accum, const int num_frc_indx, cxboolean num_frc_accum);

FLUENT_EXPORT FILE *open_injection_file(Injection *I, char *opened_file);
FLUENT_EXPORT int Set_Injection_Refs(Injection *I);
FLUENT_EXPORT void span_particles_over_partitions(Injection *I, Particle **p_list, cxboolean do_broadcast_p);
#if RP_NODE
FLUENT_EXPORT void span_surface_inj_over_partitions(Injection *I);
#endif
FLUENT_EXPORT Particle *set_particle(Injection *I, real x, real y, real z, real u, real v, real w,
                                     real diam, real temp, real m_dot, int i, CX_Cell_Id *c, cxboolean set_id);
FLUENT_EXPORT void volume_injection(Injection *I, Particle *p);
/* @} dpm_create_nonatom */

/**
 * @addtogroup dpm_create_atom atomizers
 * @{
 ************************************************************/

FLUENT_EXPORT cxboolean is_cone_injection(Injection *I);
FLUENT_EXPORT cxboolean is_atomizer_injection(Injection *I);
FLUENT_EXPORT void plain_orifice_atomizer(Injection *I);
FLUENT_EXPORT void solid_cone_atomizer(Injection *I);
FLUENT_EXPORT void cone_injection(Injection *I);
FLUENT_EXPORT void pressure_swirl_atomizer(Injection *I);
FLUENT_EXPORT void air_blast_atomizer(Injection *I);
FLUENT_EXPORT void effervescent_atomizer(Injection *I);
FLUENT_EXPORT void flat_fan_atomizer(Injection *I);
FLUENT_EXPORT void Create_Particles (Injection *, cxboolean set_id);
FLUENT_EXPORT void DPM_Init_Particles(const cxboolean force_creation);
/* @} dpm_create_atom */
/* @} dpm_create */

/**
 * @addtogroup dpm_tracking tracking
 * @{ */

/**
 * @addtogroup dpm_tracking_collision collision / coalescence
 * @{
 ************************************************************/
FLUENT_EXPORT void print_collision_counters(void);
FLUENT_EXPORT void reset_collision_counters(void);

/**
 * @addtogroup dpm_tracking_breakup breakup models
 * @{
 ************************************************************/


FLUENT_EXPORT Particle *Spawn_Particle(Tracked_Particle *tp, Particle *pn, const real vel[], const real num,
                                       const real diam, cxboolean update, cxboolean split, Particle **spawned_plist);
FLUENT_EXPORT dpm_bc_type_t get_thread_dpm_bc(Thread *thread);
FLUENT_EXPORT void compute_wave_scales(Tracked_Particle *tp, real *lambda, real *growth, real *drop_tau, real *rel_v);
/* @} dpm_tracking_breakup */

/**
 * @addtogroup dpm_tracking_boundary boundary conditions
 * @{
 *************************************************************/

FLUENT_EXPORT void Trap_Particle (Tracked_Particle *);
FLUENT_EXPORT Path_Status Vaporize_Particle (Tracked_Particle *, cxboolean update_summary);
FLUENT_EXPORT void Wall_Jet_Particle (Tracked_Particle *, real [], int, Thread *, face_t);
FLUENT_EXPORT Path_Status check_dpm_bc_udf(Tracked_Particle *, UDF_Thread_Data, Thread *, face_t, int, Thread *, face_t);
FLUENT_EXPORT void find_si_face(Tracked_Particle *tp, real pos[], real dt, face_t  slide0F, Thread  *slide0T,
                                face_t *iface_F, Thread **iface_T, face_t *slide1F, Thread **slide1T);

FLUENT_EXPORT int get_cell_face_index(const cell_t c, Thread *tc, const face_t f, Thread *tf, const cxboolean children, const cxboolean check_child);
FLUENT_EXPORT int get_sliding_face_bc(Tracked_Particle *, int, real *, CX_Cell_Id *, CX_Face_Id *, Thread **, face_t *, Thread **, face_t *);

FLUENT_EXPORT void Calc_DPM_Wall_Force(Tracked_Particle *, real[], real[], face_t, Thread *);
FLUENT_EXPORT void Reflect_Particle_Given_Coeffs(Tracked_Particle *, real[], real[], face_t, Thread *, Thread *, face_t, real, real);
FLUENT_EXPORT void Reflect_Particle (Tracked_Particle *, real[], real[], face_t, Thread *, Thread *, face_t);
FLUENT_EXPORT void reset_m_par(void);
FLUENT_EXPORT void print_m_par(void);
FLUENT_EXPORT int  SV_get_face_bndry_condn (Tracked_Particle *, int, CX_Cell_Id *, int *, Thread **, face_t *);

/**
 * @addtogroup dpm_tracking_general general algorithm
 * @{
 *************************************************************/

FLUENT_EXPORT void put_particles_into_array(Injection *injections_list, Particle **p_array, int n_new_particles, cxboolean add_chunk_list_particles, int do_only_pid);
FLUENT_EXPORT void call_dpm_scalar_update( cell_t, Thread *, int, Tracked_Particle *);
FLUENT_EXPORT void TrackStepEnd(Tracked_Particle *);
#if ! UDF_COMPILER /* ATTENTION: int64_t is not accepted by the udf interpreter. */
FLUENT_EXPORT void CL_Compute_Pathlines(int nsurf, int *from, const char *of, double length_scale, int max_steps, int reverse, int x_section, int skip, int pt_id, int error_control, double max_error, int step_skip, FILE *report_file, real *position, int64_t *particleId, int64_t *cellIndex, int *cellZone);
#endif
FLUENT_EXPORT cxboolean DPM_Compute_Pathlines (Injection *, const char *, int, int, int, const char *, FILE *, int, cxboolean, int, int);
FLUENT_EXPORT void Update_Particles_Before_Iteration(Domain *domain);
FLUENT_EXPORT void DPM_Iteration(int display, int cphase_interaction, const char *of, int report, const char *fname,
                                 FILE *report_file, int pt_id, const cxboolean update, int pdf_tran_nskip);
FLUENT_EXPORT void Particle_Scalar_Minmax (real *, real *, int);
struct track_data_s;
FLUENT_EXPORT Path_Status FindNeighbour(real pos[], real vel[], Tracked_Particle *tp, Particle *pp, real acc[], real dvdt[], real beta, int int_face[],
                                        cxboolean update_summary, struct track_data_s *track_post, real t_cross, real acc_rot[], real beta_rot, real next_pos_pdf[]);
FLUENT_EXPORT int get_dpm_n_tracked(void);
FLUENT_EXPORT Path_Status LimitTimeStep (Tracked_Particle *);
FLUENT_EXPORT cxboolean check_turn_off_hybrid(Injection *injections_list, cxboolean display_or_report);
FLUENT_EXPORT void sample_particle(Tracked_Particle *tp, const face_t f, Thread *tf, const cxboolean update);
FLUENT_EXPORT cxboolean Mark_Too_Small_Non_Inert_tp_Deleted(Tracked_Particle *tp, real mass, cxboolean update_summary);

FLUENT_EXPORT void Escape_Tracked_Particle(Tracked_Particle *tp, cxboolean update_summary, face_t face, Thread *thread);
FLUENT_EXPORT void Reinject_Tracked_Particle(Tracked_Particle *tp, cxboolean update_summary, face_t face, Thread *thread);
FLUENT_EXPORT void Escape_OR_Reinject_Tracked_Particle(Tracked_Particle *tp, cxboolean update_summary, face_t face, Thread *thread);

FLUENT_EXPORT void apply_gti_crossover_tolerance(Tracked_Particle *tp);

/*  common dpm boundary condition functions  */
FLUENT_EXPORT void dpm_bc_periodic(Tracked_Particle *tp, Particle *p, Thread *tf, CX_Cell_Id *neigh, real *pos,
                                   const cxboolean parallel);

FLUENT_EXPORT Path_Status dpm_bc_udf(Tracked_Particle *tp, const face_t f, Thread *tf, const face_t f_nci, Thread *tf_nci,
                                     const int int_f, cxboolean *is_wall, const cxboolean update);


/* @} dpm_tracking_general */

/**
 * @addtogroup dpm_tracking_workpile workpile algorithm
 * @{
 *************************************************************/

#if RP_DPM_CACHE
FLUENT_EXPORT void Deposit_Cache_Sources(Tracked_Particle *tp);
FLUENT_EXPORT void Deposit_Cache_Real (Tracked_Particle *tp);
FLUENT_EXPORT real *Get_Real_Cache (Tracked_Particle *tp, real *p, char o);
#define GET_REAL_CACHE(_tp, _p, _o)                                \
  ((dpm_par.parallel_hybrid && dpm_par.parallel_nthreads > 1)?  \
   Get_Real_Cache ((_tp), (_p), (_o)) : (_p))

FLUENT_EXPORT void Print_Cache_Report(Injection *);
# if MPT_THREAD
extern FLUENT_EXPORT int dpm_nthreads;
FLUENT_EXPORT int DPM_Suggest_Nthreads(void);
# endif /* MPT_THREAD */
#define GET_REAL_CACHE1(_tp, _p, _o) (_p)
#else  /* RP_DPM_CACHE */
#define GET_REAL_CACHE(_tp, _p, _o) (_p)
#endif /* RP_DPM_CACHE */
/* @} dpm_tracking_workpile */

/**
 * @defgroup dpm_tracking_reset relocating particles after grid change
 * @{
 *************************************************************/

FLUENT_EXPORT void set_dpm_reset(void);
FLUENT_EXPORT void check_dpm_reset(void);
FLUENT_EXPORT void reset_dpm_grid_ids(void);
FLUENT_EXPORT int  get_stored_dpm_grid_id(void);
FLUENT_EXPORT int  get_stored_dpm_grid_partition_id(void);
FLUENT_EXPORT int  get_current_dpm_grid_partition_id(void);
FLUENT_EXPORT void increment_dpm_stored_partition_id(void);
FLUENT_EXPORT void set_stored_dpm_grid_id(int grid_id);

/* @} dpm_tracking_reset */

/**
 * @addtogroup dpm_tracking_erosion erosion/accretion
 * @{
 *************************************************************/
FLUENT_EXPORT void Erosion_Accretion(Tracked_Particle *, Thread *, face_t, real []);
/* @} dpm_tracking_erosion */
/* @} dpm_tracking */
/* @} dpm */

FLUENT_EXPORT void dpm_free_o_list(Objp *objps);

#endif /* _FLUENT_DPM_PATH_H */
