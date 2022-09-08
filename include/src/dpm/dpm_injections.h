/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _DPM_INJECTIONS_H
#define _DPM_INJECTIONS_H

/* Volume injection */
typedef struct volinj_cell_s
{
  struct volinj_cell_s *next;

  cell_t  cell;
  Thread *cell_thread;
  real    load;        /* cell filling 0 > cell load > 1 , 0 empty 1 full maximum should be 0.95 */
  real    ridx;        /* real index 0 < ridx < 1 to randomly chose a cell out of list */
  int     empty;       /* is cell filleed for the very first time */
} volinj_cell_t;

typedef struct volinj_checkdata_s
{
  int nparcels;
  real parcel_diameter;
  real parcel_volume;
  real total_mass;
  real vc_min;
  real volume_fraction;
} volinj_checkdata_t;

FLUENT_EXPORT Thread **fill_thread_list_zone_volume_inj( int tmax, int *tid_list);
FLUENT_EXPORT int total_parcel_number_in_volume(Injection *I);
FLUENT_EXPORT int local_parcel_number_in_zone_volume(Thread **tlist, Injection *I);
FLUENT_EXPORT real calc_bgeom_volume_cell(bound_geom_coord_t bgeom_coord, bound_geom_t shape);
FLUENT_EXPORT real calc_bgeom_volume_shape(bound_geom_coord_t bgeom_coord, bound_geom_t shape);
FLUENT_EXPORT real calc_zone_volume(Thread **tlist, int tlist_length);
FLUENT_EXPORT int calc_ddpm_nparcels_and_parcel_diameter(real inj_volume,
                                                         real *parcel_diameter,
                                                         real *parcel_volume,
                                                         real packing_limit_per_cell,
                                                         real volume_fraction,
                                                         int min_parcels_per_cell,
                                                         real *total_flow_rate,
                                                         real inj_time,
                                                         real material_density,
                                                         cxboolean use_volume_fraction,
                                                         int verbose,
                                                         volinj_checkdata_t *check_data);
FLUENT_EXPORT void compute_pt_locations_and_props_zone_volume_inj(Thread **tlist, Injection *I, cxboolean set_id);
FLUENT_EXPORT void compute_pt_locations_and_props_bbox_zone_volume_inj(Thread **tlist, Injection *I, cxboolean set_id);
FLUENT_EXPORT void compute_pt_locations_and_props_bgeom_volume_inj(Injection *I, cxboolean set_id);
FLUENT_EXPORT void Generate_Cartesian_Mesh_Cell_List(int *ncells, int64_t **cell_list, Thread *t,
                                                     int parcel_count, Injection *I, uniform_random_seed *seed);
FLUENT_EXPORT void Generate_CFD_Mesh_Cell_List(int *ncells,  volinj_cell_t **cell_list, Thread *t, real packing_limit_per_cell);

/* Flags used on arbitrary Cartesian mesh. */

#define CC_FLAG_HAS_WALLS   (1)
#define CC_FLAG_IS_GHOST_CC (2)
#define CC_FLAG_FULL        (3)

#define CC_FLAG_P(data, icc, flag)     (data.flags[icc] &   flag)
#define SET_CC_FLAG(data, icc, flag)   (data.flags[icc] |=  flag)
#define CLEAR_CC_FLAG(data, icc, flag) (data.flags[icc] &= ~flag)

/* random seeds */
FLUENT_EXPORT void dpm_inj_create_seed_from_id(Particle *p);
FLUENT_EXPORT void dpm_inj_create_seed(Injection *I, gauss_random_seed *seed);
FLUENT_EXPORT void dpm_inj_create_seed_from_global_cell_id(cell_t c, Thread *t, gauss_random_seed *seed);
FLUENT_EXPORT void dpm_create_seed(gauss_random_seed *seed);

/* injection specific tools */
FLUENT_EXPORT void get_injection_start_stop_time(Injection *I, real flow_time, real *start_time, real *stop_time);
FLUENT_EXPORT void randomPositionOnFace(uniform_random_seed *seed, face_t f, Thread *tf, const real t_delta,
                                        const cxboolean interp_in_time, real *position, real *normal);
FLUENT_EXPORT real compute_number_in_parcel(Injection *I, Particle *p, real delta_t);
/** @brief Injection settings for which a reset of the accumulated mass_next_time is needed.
 */
typedef struct
{
  int type;
  Parcel_Model parcel_model;
  int streams; /* For Group injection RR distribution discretization is based on the stream number */
  cxboolean rr_distrib;
  cxboolean rr_uniform_lnD;
  real diam0;
  real diam1;
  int number_diameters;
  real min_diam;
  real max_diam;
} I_old_settings_t;

FLUENT_EXPORT void number_init_parcels_per_diameter_class(Injection *I, int *ppc);
FLUENT_EXPORT int number_diameter_classes(Injection *I);
FLUENT_EXPORT int adjust_reset_injection_mass_next_time(Injection *I, I_old_settings_t *old);
FLUENT_EXPORT real triangleArea2(real *p0, real *p1, real *p2);

FLUENT_EXPORT int MessagePopup(const char *format, ... );

FLUENT_EXPORT cxboolean Check_Inj_File_Type(Injection *I, cxboolean popups);

#endif /* _DPM_INJECTIONS_H */
