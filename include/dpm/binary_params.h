/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/

#ifndef _FLUENT_BINARY_PARAMS_H
#define _FLUENT_BINARY_PARAMS_H

#include "global.h"
#include "mem.h"

typedef enum
{
  /* Stochastical Interaction Laws */
  COLLIDE_OROURKE = 0,
  COLLIDE_NTC,
  COLLIDE_NTC_HYBRID,
  COLLIDE_NANBU,
  /* DEM Interaction Laws */
  DEM_COLLIDE_SPRING,
  DEM_COLLIDE_SPRING_DASHPOT,
  DEM_COLLIDE_HERTZIAN,
  DEM_COLLIDE_HERTZIAN_DASHPOT,
  DEM_COLLIDE_FRICTION_BETA,
  DEM_COLLIDE_FRICTION_DSHF,
  DEM_COLLIDE_FRICTION_CUNDALL_STRACK,
  DEM_COLLIDE_FRICTION_DSHF_ROLLING,
  DEM_COLLIDE_FRICTION_CUNDALL_STRACK_ROLLING,
  /* Van der Waals interaction */
  DEM_VAN_DER_WAALS_HAMAKER,
  /* User specific Interaction Laws */
  COLLIDE_USER,
  INTERACTION_TYPE_MAX
} Interaction_Type;

/* DEM Collision Laws */

typedef struct spring_param_struct
{
  real K;

} spring_param_t;

typedef struct spring_dashpot_param_struct
{
  real K;
  real log_restitution;

} spring_dashpot_param_t;

typedef struct hertzian_param_struct
{
  real K;

} hertzian_param_t;

typedef struct hertzian_dashpot_param_struct
{
  real K;
  real log_restitution;

} hertzian_dashpot_param_t;

typedef struct friction_dshf_param_struct
{
  real mu_stick;
  real mu_glide;
  real mu_limit;
  real vel_glide;
  real vel_limit;
  real slope_limit;
  real mu_rolling;

} friction_dshf_param_t;

typedef struct friction_cundall_strack_param_struct
{
  real K_tangential;
  real log_restitution_tangential;
  real scale;
  real mu_stick;
  real mu_glide;
  real K_rolling;
  real log_restitution_rolling;
  real rolling_scale;
  real mu_rolling;

} friction_cundall_strack_param_t;

typedef struct van_der_waals_hamaker_param_struct
{
  real H;
  real force_limiting_distance;
} van_der_waals_hamaker_param_t;

typedef struct interaction_param_struct
{
  Interaction_Type type;
  int stage;

  /* DEM boolean if a rolling or tangetial friction law is enabled.
     This is needed because this influences the formula for the tangential
     velocity in the normal collision laws */
  cxboolean have_tangential_friction_model;
  cxboolean have_rolling_friction_model;

  union
  {
    /* normal collsion laws, stage 1 */
    spring_param_t          spring          ;
    spring_dashpot_param_t  spring_dashpot  ;
    hertzian_param_t   hertzian   ;
    hertzian_dashpot_param_t hertzian_dashpot;
    /* tangential collision laws, stage 2 */
    friction_dshf_param_t   friction_dshf   ;
    friction_cundall_strack_param_t friction_cundall_strack;
    /* van der waals laws, stage 3 */
    van_der_waals_hamaker_param_t van_der_waals_hamaker;

  } u;

} dpm_interaction_param_t;


typedef struct interaction_law_list_struct
{
  int n_laws;
  dpm_interaction_param_t *law_params;

} dpm_interaction_law_list_t;

typedef struct interaction_partner_table_struct
{
  /* The central data for describing individual collisions:
  */
  int n_binary_partners;

  Objp *binary_partners;                    /* list of objects containing name and index     */
  dpm_interaction_law_list_t **interaction_matrix; /* set of collision laws for each collision pair */

  int min_stage;
  int max_stage;

} interaction_partner_table_t;


#define DPM_N_BINARY_PARTNERS(partner_table)        (partner_table.n_binary_partners)
#define DPM_MIN_STAGE(partner_table)                (partner_table.min_stage)
#define DPM_MAX_STAGE(partner_table)                (partner_table.max_stage)
#define DPM_BINARY_PARTNER_OBJP_LIST(partner_table) (partner_table.binary_partners)
#define DPM_INTERACTION_MATRIX(partner_table)       (partner_table.interaction_matrix)

#define DPM_INTERACTION_N_LAWS(partner_table, i, j)     ((DPM_INTERACTION_MATRIX(partner_table)[i][j]).n_laws)
#define DPM_INTERACTION_PARAMETERS(partner_table, i, j) ((DPM_INTERACTION_MATRIX(partner_table)[i][j]).law_params)

#define DPM_INTERACTION_TYPE(partner_table, i, j, k)                  ((DPM_INTERACTION_PARAMETERS(partner_table, i, j)[k]).type)
#define DPM_INTERACTION_STAGE(partner_table, i, j, k)                 ((DPM_INTERACTION_PARAMETERS(partner_table, i, j)[k]).stage)
#define DPM_INTERACTION_HAVE_GLIDING_FRICTION(partner_table, i, j, k) ((DPM_INTERACTION_PARAMETERS(partner_table, i, j)[k]).have_tangential_friction_model)
#define DPM_INTERACTION_HAVE_ROLLING_FRICTION(partner_table, i, j, k) ((DPM_INTERACTION_PARAMETERS(partner_table, i, j)[k]).have_rolling_friction_model)
#define DPM_INTERACTION_LAW_PARAMETERS(partner_table, i, j, k)        ((DPM_INTERACTION_PARAMETERS(partner_table, i, j)[k]).u)

FLUENT_EXPORT void Reset_interaction_partner_table(interaction_partner_table_t partner_table);
FLUENT_EXPORT Interaction_Type Interaction_Type_From_Name(char *law_name);
FLUENT_EXPORT const char *Interaction_Name_From_Type(Interaction_Type law_type);

#endif /* _FLUENT_BINARY_PARAMS_H */
