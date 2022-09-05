/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/

#ifndef _FLUENT_REDUCE_SAMPLE_DATA_H
#define _FLUENT_REDUCE_SAMPLE_DATA_H


FLUENT_EXPORT void Model_Initialize_redu_samp_data_to_file(void);

/* An enum that can only have the values "linear" and "logarithmic":
 */
typedef enum
{
  ONE_RSD_VAR_SCALE_LIN,
  ONE_RSD_VAR_SCALE_LOG,
  ONE_RSD_VAR_SCALE_MAX
} one_rsd_var_scale_t;   /* one_rsd_var_scale = scale of one variable from reduction sample data */

/* A struct that holds all user inputs for
 * a single sample variable for the
 * data reduction:
 */
typedef struct redu_samp_dat_one_var_par_set_struct
{
  struct redu_samp_dat_one_var_par_set_struct *next;
  char name[64];
  real min;
  real min_log;
  real max;
  int  steps;
  one_rsd_var_scale_t scale;
  real step_size;
  real step_size_log;
} redu_samp_dat_one_var_par_set_t;

/* Data structure for all user inputs for the
 * data reduction -- contains a pointer to a
 * linked list of instances of the above:
 */
typedef struct redu_samp_dat_param_set_struct
{
  char out_file_name[512];
  char the_smpl_name[64];
  char wght_var_name[64];
  cxboolean stdy_from_unst;
  /* int num_of_vars; */
  redu_samp_dat_one_var_par_set_t *var_par_sets;
} redu_samp_dat_param_set_t;


FLUENT_EXPORT void init_redu_samp_dat_param_set(redu_samp_dat_param_set_t *pmyrsdps, cxboolean freedata);
FLUENT_EXPORT void do_redu_samp_dat_to_file(redu_samp_dat_param_set_t *myrsdps);


#endif /* _FLUENT_REDUCE_SAMPLE_DATA_H */

