/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DYNAMESH_SURFDEFORM_H
#define _FLUENT_DYNAMESH_SURFDEFORM_H

typedef struct surf_deform_params_struct
{
  real min_dt;
  real max_dt;
  real max_dt_growth;

  cxboolean adaptive_dt_p;
  cxboolean local_limiting_p;
  cxboolean clip_inward_p;
  cxboolean smooth_inward_p;
  cxboolean smooth_small_faces_p;
  cxboolean node_data_p;

  int smoothing_passes;

  real max_move_fac;
  real clip_inward_dir;
  real conserve_mag_factor;

  cxboolean smooth_as_vector_p;
  cxboolean face_based_p;
  cxboolean local_norm_p;
  cxboolean remove_tang_component_p;
  cxboolean true_dx_v_v_p;
  cxboolean true_dx_v_p;

  int smooth_f_to_n;
  int smooth_n_to_f;
  int small_faces_method;

  real smooth_relax_factor;
  real small_area;
  real small_faces_smooth_amount;
  real small_faces_dx_threshold;

  void *get_face_dx;
  void *get_node_dx;
  void *smooth_op;

  Svar sv_n_dx;
  Svar sv_f_tot_dx;

} DM_Surf_Deform_Params;

FLUENT_EXPORT void DM_Fill_Surface_Deformation(Domain *, int);
FLUENT_EXPORT real DM_Surface_Deformation(Domain *, Objp *, real, real,
                                          cxboolean,
                                          void (*get_params)
                                          (DM_Surf_Deform_Params *));
FLUENT_EXPORT void DM_Surface_Smoother(Domain *, Objp *);
FLUENT_EXPORT void DM_Init_Surf_Deform_Params(DM_Surf_Deform_Params *);

#endif /* _FLUENT_DYNAMESH_SURFDEFORM_H */
