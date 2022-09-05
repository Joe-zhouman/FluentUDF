/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DPM_MEM_H
#define _FLUENT_DPM_MEM_H

#include "dpm_types.h"
#include "dpm_dem_wall.h"

/**
 * @file
 * DPM: internal memory structure
 *
 * @addtogroup dpm Discrete Particle Model
 *
 * Contains the following groups of functions:
 *
 */

/**
 * @addtogroup dpm_mem memory management
 * @{ */

/**
 * @addtogroup dpm_mem_injection injection memory
 * @{
 *************************************************************/

FLUENT_EXPORT Injection *Init_pdft_injection(void);
FLUENT_EXPORT Injection *pdft_injection_new(void);
FLUENT_EXPORT void delete_pdft_injection(void);
FLUENT_EXPORT Injection *Get_pathline_injection(void);
FLUENT_EXPORT Injection *Get_Efilm_Injection(void);
FLUENT_EXPORT void update_dpm_injection_ids(void);
FLUENT_EXPORT void link_I_to_dpm_injections(Injection *I);
FLUENT_EXPORT void unlink_I_from_dpm_injections(Injection *I);
FLUENT_EXPORT Injection *injection_new(void);
FLUENT_EXPORT void delete_injection(Injection *I);
FLUENT_EXPORT void delete_all_injections(void);
FLUENT_EXPORT void Reset_Injection_Data_At_Init(void);
FLUENT_EXPORT void Free_Pathlines_Memory(Injection *I);
FLUENT_EXPORT void reset_injections_start_id(void);
FLUENT_EXPORT void activate_all_injections(cxboolean active);
FLUENT_EXPORT void reset_all_injections_min_max(void);
FLUENT_EXPORT int  DPM_N_Active_Injections(void);

extern FLUENT_EXPORT int dpm_highest_inj_id;
/* @} dpm_mem_injection */

/**
 * @addtogroup dpm_mem_pvar particle pvar memory
 * @{
 ************************************************************/

typedef struct pv_particle_vars_t
{
  User_Particle_Vars u;
  Pvar pvar;
  struct pv_particle_vars_t *next;
} PV_Particle_Vars;

FLUENT_EXPORT int dpm_pvar_rsize(Injection *I, int pv);
FLUENT_EXPORT int dpm_pvar_xfp(int pv);
FLUENT_EXPORT void alloc_tp_pvars(Tracked_Particle *tp, Injection *I);
FLUENT_EXPORT void free_tp_pvars(Tracked_Particle *tp);
FLUENT_EXPORT void copy_tp_to_pvars(Particle *p, Tracked_Particle *tp);
FLUENT_EXPORT void copy_pvars_to_tp(Tracked_Particle *tp, Particle *p);
FLUENT_EXPORT real *dpm_particle_real_unpack(Injection *I, Particle *p, real *rbuf);
FLUENT_EXPORT real *dpm_particle_real_pack(Injection *I, Particle *p, real *rbuf);
FLUENT_EXPORT void initialize_pvars(Particle *p);
FLUENT_EXPORT void init_all_pvars_names(void);
FLUENT_EXPORT int reset_particle_breakup_type(Injection *);
FLUENT_EXPORT Particle_Variable_ID  Get_Particle_Variable_ID (const char *);
FLUENT_EXPORT void display_particle_list(const char *name, Particle *p);
FLUENT_EXPORT char *particle_type_print_string(int ptype);
FLUENT_EXPORT int particle_type(const char *name);
FLUENT_EXPORT Injection_Type injection_type(const char *name);
FLUENT_EXPORT int Law_Type(const char *name, Injection *I, int *user_index);
/* this are the conditions, which apply for the variables */
FLUENT_EXPORT int pv_use_component(Injection *I);
FLUENT_EXPORT int pv_use_reacting_state(Injection *I);
FLUENT_EXPORT int pv_use_cpd_state(Injection *I);
FLUENT_EXPORT int pv_use_vff_real(Injection *I);
FLUENT_EXPORT int pv_use_collision(Injection *I);
FLUENT_EXPORT int pv_use_contact_particle(Injection *I);
FLUENT_EXPORT int pv_use_contact_face(Injection *I);
FLUENT_EXPORT int pv_use_random_seed(Injection *I);
FLUENT_EXPORT int pv_use_omega(Injection *I);
FLUENT_EXPORT int pv_use_turb_dampening(Injection *I);
FLUENT_EXPORT int pv_use_quaternion(Injection *I);
FLUENT_EXPORT int pv_use_wall_film(Injection *I);
FLUENT_EXPORT int pv_use_bl_film_nu(Injection *I);
FLUENT_EXPORT int pvar_id_from_sect(Injection *I, int sect, cxboolean i_report_messages);
FLUENT_EXPORT cxboolean set_particle_vars(Injection *I);
FLUENT_EXPORT void dpm_set_particle_api_pointers(Particle *p);

/* @} dpm_mem_pvar */

/**
 * @addtogroup dpm_mem_partid particle id
 * @{
 *************************************************************/

/* These six macros are used by AFD sources for HDF5 I/O,
 * therefore they still start with a single P_...:
 */
#define PP_REALVAR(pp,var) \
  (*((real *) (&((char *) CHECK_PP_TYPE(pp))[var])))
#define PP_INTVAR(pp,var) \
  (*((int *) (&((char *) CHECK_PP_TYPE(pp))[var])))
#define PP_LONGVAR(pp,var) \
  (*((long *) (&((char *) CHECK_PP_TYPE(pp))[var])))
#define PP_INT64VAR(pp,var) \
  (*((int64_t *) (&((char *) CHECK_PP_TYPE(pp))[var])))
#define PP_UNSTEADYVAR(pp,var) \
  (*((real *) (&((char *) PP_UNSTEADY_COUPLED(pp))[var])))
#define P_INJ_REALARRAY(I,var) \
  (*((real **) (&((char *) I)[var])))

#if ! UDF_COMPILER
FLUENT_EXPORT int64_t get_next_part_id(void);
FLUENT_EXPORT int64_t set_injections_start_id(void);
FLUENT_EXPORT void set_max_id_in_injection(Injection *I);
FLUENT_EXPORT void reset_part_id_count(int64_t start);
FLUENT_EXPORT void renumber_particles(void);
FLUENT_EXPORT void print_partids(Injection *injections);
FLUENT_EXPORT void generate_unique_partids(Injection *injections);
FLUENT_EXPORT int dpm_mpi_exscan(int *i);
FLUENT_EXPORT int dpm_mpi_scan(int *i);
FLUENT_EXPORT void assign_particle_ids(Particle *pl, int64_t *, int);
#endif
/* @} dpm_mem_partid */

/**
 * @addtogroup dpm_mem_part particle memory
 * @{
 *************************************************************/

typedef struct particle_vars_t
{
  char *name;
  char *label;
  char *units;
  Particle_Variable_ID index;
  char *vector_name;
  char vector_component;
} Particle_Vars;

typedef struct
{
  char name[DPM_NAME_LENGTH];
  cxboolean (* condition) ();
} ParticleType_t;

extern FLUENT_EXPORT User_Particle_Vars *user_particle_vars;
extern FLUENT_EXPORT User_Particle_Vars *scalar_particle_vars;

FLUENT_EXPORT void clear_dpm_breakup_memory(Injection *dpm_injections, int old_dpm_n_scalars);
FLUENT_EXPORT void clear_dpm_user_memory(Injection *dpm_injections);
FLUENT_EXPORT void clear_dpm_cbk_memory(Injection *dpm_injections);
FLUENT_EXPORT void deep_copy_particle(Particle *np, Particle *p);
FLUENT_EXPORT void copy_dpms_t_source(dpms_t *new_source, dpms_t *source);
FLUENT_EXPORT void free_particle(Particle *particle);
FLUENT_EXPORT void Free_Unsteady_Particles(Domain *domain, Injection *dpm_injections, real current_time, cxboolean update);
FLUENT_EXPORT void init_read_pdf_particle(Material *m, Particle *p);
FLUENT_EXPORT void setup_particle_memory(Injection *I);
FLUENT_EXPORT void Init_Scalar_Particle_Vars(void);
FLUENT_EXPORT void Init_User_Particle_Vars(void);
FLUENT_EXPORT void init_particle_pvar(Particle *p, Pvar pv, Particle *old_p, int old_pv_index);

/* deprecated functions: call
 *   init_particle_pvar(p,PV_...,NULL,-1);
 * instead. */
FLUENT_EXPORT void Init_DPM_cbk(Particle *p);
FLUENT_EXPORT void Init_DPM_Scalars(Particle *p);
FLUENT_EXPORT void Init_Unsteady_Coupled(Particle *p);
FLUENT_EXPORT void Init_Unsteady_User(Particle *p);

/* deprecated function: can be dropped */
FLUENT_EXPORT void alloc_pvars(Particle *p);

FLUENT_EXPORT real Particle_Scalar_Value(Tracked_Particle *, Particle_Variable_ID);
FLUENT_EXPORT void Particle_Vector_Value(Tracked_Particle *, Particle_Variable_ID, float *);
FLUENT_EXPORT Particle *new_particle(Injection *I, cxboolean set_id);
FLUENT_EXPORT void Set_Particles_Per_Alloc(int n);
FLUENT_EXPORT Particle_Contact *new_particle_contact(void);
FLUENT_EXPORT Face_Contact *new_face_contact(void);
FLUENT_EXPORT void free_particle_contact(Particle_Contact *particle_contact);
FLUENT_EXPORT void free_face_contact(Face_Contact *face_contact);
FLUENT_EXPORT void Set_Particle_Contacts_Per_Alloc(int n);
FLUENT_EXPORT void Set_Face_Contacts_Per_Alloc(int n);
FLUENT_EXPORT void prepend_face_contact_to_face_contact_list(Face_Contact *face_contact, Face_Contact **face_list);
FLUENT_EXPORT void insert_particle_contact_into_particle_contact_list(Particle_Contact *particle_contact, Particle_Contact **particle_contact_list);
FLUENT_EXPORT void unlink_particle_contact_from_particle_contact_list(Particle_Contact *particle_contact, Particle_Contact **particle_contact_list);
FLUENT_EXPORT void unlink_face_contact_from_face_contact_list(Face_Contact *face_contact, Face_Contact **face_contact_list);
FLUENT_EXPORT Particle_Contact *is_particle_in_particle_contact_list(Particle *p, Particle_Contact *particle_contact_list);
FLUENT_EXPORT Face_Contact *is_face_in_face_contact_list(dpm_collision_face_t *face_data, Face_Contact *face_contact_list);
FLUENT_EXPORT void free_particle_contact_list(Particle_Contact **particle_contact_list);
FLUENT_EXPORT void free_face_contact_list(Face_Contact **face_contact_list);
/* @} dpm_mem_part */

/**
 * @addtogroup dpm_mem_tracked tracked_particle memory
 * @{
 *************************************************************/
FLUENT_EXPORT void alloc_tp_faceEq_memory(gtpv_t *pgvtp);
FLUENT_EXPORT void alloc_tp_source_memory(dpms_t *source);
FLUENT_EXPORT void alloc_tp_reacting_state_memory(reacting_particle_state_t *state);
FLUENT_EXPORT void alloc_tp_gvtp_memory(gtpv_t *pgvtp);
FLUENT_EXPORT void alloc_tp_phys_models_memory(Tracked_Particle *tp);
FLUENT_EXPORT void alloc_tp_collision_force_memory(Tracked_Particle *tp);
FLUENT_EXPORT void alloc_tp_cphase_memory(Tracked_Particle *tp);
FLUENT_EXPORT void alloc_tracked_particle_memory(Tracked_Particle *tp);
FLUENT_EXPORT void copy_tp_to_p(Tracked_Particle *, Particle *);
FLUENT_EXPORT void copy_tp_to_tp_min_max(Tracked_Particle *);
FLUENT_EXPORT void reset_I_min_max(Injection *);
FLUENT_EXPORT void free_tp_faceEq_memory(gtpv_t *pgvtp);
FLUENT_EXPORT void free_tp_source_memory(dpms_t *source);
FLUENT_EXPORT void free_tp_reacting_state_memory(reacting_particle_state_t *state);
FLUENT_EXPORT void free_tp_gvtp_memory(gtpv_t *pgvtp);
FLUENT_EXPORT cxboolean cleanup_spawned_particles(Particle **p_spawned);
FLUENT_EXPORT void free_tp_phys_models_memory(Tracked_Particle *tp);
FLUENT_EXPORT void free_tp_collision_force_memory(Tracked_Particle *tp);
FLUENT_EXPORT void free_tp_cphase_memory(Tracked_Particle *tp);
FLUENT_EXPORT void free_tracked_particle_memory(Tracked_Particle *tp);
FLUENT_EXPORT void Reset_init_state_From_state(Particle *p);
FLUENT_EXPORT void copy_p_to_tp(Tracked_Particle *tp, Particle *p);

FLUENT_EXPORT Path_Status init_tracked_particle(Tracked_Particle *tp, Particle *p, cxboolean unsteady_tracking, cxboolean update, cxboolean need_cphase);
/* @} dpm_mem_tracked */


/**
 * @addtogroup dpm_mem_plist Particle Lists
 * @{
 *************************************************************/
FLUENT_EXPORT void print_particle_list(Particle *p_start);
FLUENT_EXPORT void injection_release_particles( Injection *I );
FLUENT_EXPORT int free_migrated_particle_list(Particle **pl);
FLUENT_EXPORT void free_injection_particles(Injection *I);
FLUENT_EXPORT void Clear_All_Particles(void);
FLUENT_EXPORT void sort_particle_list_to_Ip(Particle **pl);
FLUENT_EXPORT void sort_particle_list_to_Ip_init(Particle **pl);
FLUENT_EXPORT void sort_particle_list_by_partid(Particle **pl);
FLUENT_EXPORT void sort_particle_pointer_array_by_part_id(Particle **ppa, int np);
FLUENT_EXPORT int count_p_list(Particle *p_start);
FLUENT_EXPORT int count_not_removed_p_list(Particle *p_start);
FLUENT_EXPORT real compute_mass_p_list(Particle *p_start);
FLUENT_EXPORT int count_particles_in_active_injections(Injection *injections_list, int do_only_pid);
FLUENT_EXPORT void randomize_particles_in_array(gauss_random_seed *rand_picles_seed, Particle **p_array, int n_particles);
FLUENT_EXPORT void Sort_Particles_and_WF_Particles(Particle **particles, Particle **pl, Particle **wfpl);
FLUENT_EXPORT void Free_Particles(Injection *);
FLUENT_EXPORT int Mark_Particles_In_Non_Fluid_Zones(Particle **plist);
FLUENT_EXPORT int cleanup_particle_list(Particle **plist, Particle **p_tail, int *np);
FLUENT_EXPORT int delete_freestream_particles(void);
FLUENT_EXPORT int have_any_wallfilm_particles_P(void);
FLUENT_EXPORT int delete_wallfilm_particles(void);
FLUENT_EXPORT int delete_particles_of_thread(int tid);
FLUENT_EXPORT int free_particle_list(Particle *);
FLUENT_EXPORT void thread_particles_to_first_injection(void);
FLUENT_EXPORT void unlink_particle_from_list(Particle *p, Particle **pl);
FLUENT_EXPORT void reset_injections_nparticles_and_tail(void);
FLUENT_EXPORT void reset_injection_nparticles_and_tail(Injection *I);
FLUENT_EXPORT void append_particle_to_list(Particle *p, Particle **pl, Injection *I);
FLUENT_EXPORT void prepend_particle_to_list(Particle *p, Particle **pl);
FLUENT_EXPORT void prepend_particle_list(Particle **p, Particle **pl);
FLUENT_EXPORT Particle *find_particle_list_tail(Particle *p);
FLUENT_EXPORT void splice_particle_to_list(Particle *p, Particle **pl, Particle *last);
/* @} dpm_mem_plist */

/**
 * @addtogroup dpm_mem_valloc int/real vector alloc/free
 * @{
 *************************************************************/
FLUENT_EXPORT real **dpm_matrix(int nrl, int nrh, int ncl, int nch);
FLUENT_EXPORT void free_dpm_matrix(real **m, int nrl, int nrh, int ncl);
FLUENT_EXPORT int **i_dpm_matrix(int nrl, int nrh, int ncl, int nch);
FLUENT_EXPORT void free_i_dpm_matrix(int **m, int nrl, int nrh, int ncl, int nch);
FLUENT_EXPORT real *dpm_vector(int nl, int nh);
FLUENT_EXPORT void free_dpm_vector(real *v, int nl);
FLUENT_EXPORT int *i_dpm_vector(int nl, int nh);
FLUENT_EXPORT void free_i_dpm_vector(int *v, int nl);
/* @} dpm_mem_valloc */

FLUENT_EXPORT void *Particle_Malloc(void **, size_t);
FLUENT_EXPORT void *Particle_Realloc(void **, size_t);
FLUENT_EXPORT void Particle_Free(void **);

/* IO2 */
FLUENT_EXPORT real *Get_Pvar_Packed(real *, int, Particle *);
FLUENT_EXPORT real *Get_Pvar_Unpacked(real *, int, Particle *);

#endif
