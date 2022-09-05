/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_BATTERY_H_
#define _FLUENT_BATTERY_H_

typedef enum
{
  NEWMAN_INPUT_CONSTANT = 0,
  NEWMAN_INPUT_POLYNOMIAL,
  NEWMAN_INPUT_UDF
} NEWMAN_Input_type;

enum
{
  NEWMAN_P2D_AVERAGE_CS_N = 0,
  NEWMAN_P2D_AVERAGE_CS_P,
  NEWMAN_P2D_AVERAGE_CE_N,
  NEWMAN_P2D_AVERAGE_CE_P,
  NEWMAN_P2D_AVERAGE_CE_S
};

typedef struct newman_input
{
  NEWMAN_Input_type type;  /* constant, polynomial or udf */
  union
  {
    Polynomial *pl;
    real (*pudf)(real, real);
  } input;
  real xoutval;
} NEWMAN_Pinput;

extern FLUENT_EXPORT int     msmd_battery_on, battery_method;
extern FLUENT_EXPORT real    *USER_DEFINED_ECHEM;
extern FLUENT_EXPORT int     battery_n_XN, battery_n_XS, battery_n_XP, battery_n_RP, battery_n_RN;
extern FLUENT_EXPORT double  *battery_X_cv_PE, *battery_X_cv_SP, *battery_X_cv_NE, *battery_R_cv_PE, *battery_R_cv_NE;
extern FLUENT_EXPORT double  *battery_sigma_PE, *battery_sigma_NE;
extern FLUENT_EXPORT double  *battery_PhieNE, *battery_PhisNE, *battery_CeNE, *battery_PhiePE, *battery_PhisPE, *battery_CePE, *battery_PhieSP, *battery_CeSP;
extern FLUENT_EXPORT double  *battery_kappa_NE, *battery_kappa_SP, *battery_kappa_PE, *battery_kappa2_NE, *battery_kappa2_SP, *battery_kappa2_PE;
extern FLUENT_EXPORT double  *battery_t_plus_NE, *battery_t_plus_SP, *battery_t_plus_PE, *battery_diff_NE, *battery_diff_SP, *battery_diff_PE;
extern FLUENT_EXPORT double  *battery_eta_NE, *battery_eta_PE, *battery_i_NE, *battery_i_PE;
extern FLUENT_EXPORT double   battery_CsNE[200][200], battery_CsPE[200][200];
extern FLUENT_EXPORT Thread  *battery_t_called;
extern FLUENT_EXPORT cell_t   battery_c_called;
extern FLUENT_EXPORT real    *battery_module_phi_correction;

extern FLUENT_EXPORT NEWMAN_Pinput *newman_diff_p, *newman_diff_n;
extern FLUENT_EXPORT NEWMAN_Pinput *newman_cond_p, *newman_cond_n;
extern FLUENT_EXPORT NEWMAN_Pinput *newman_ocp_p,  *newman_ocp_n;
extern FLUENT_EXPORT NEWMAN_Pinput *newman_diff_e, *newman_tplus;
extern FLUENT_EXPORT NEWMAN_Pinput *newman_kappa,  *newman_activity;
extern FLUENT_EXPORT void Init_Battery_Profile1(Pointer x1, Pointer x2, Pointer x3, Pointer x4);
extern FLUENT_EXPORT void Init_Battery_Profile2(Pointer x5, Pointer x6, Pointer x7, Pointer x8);
extern FLUENT_EXPORT void Init_Battery_Profile3(Pointer x9, Pointer x10);
extern FLUENT_EXPORT cxboolean battery_orthocylinder_on;
extern FLUENT_EXPORT real *battery_origin_x, *battery_origin_y, *battery_origin_z, *battery_axis_x, *battery_axis_y, *battery_axis_z, battery_k_value[3];

typedef struct BATTERY_Function_struct
{
  cxboolean (*is_active_thread)(Thread *t);
  cxboolean (*is_tab_thread)(Thread *t);
  cxboolean (*is_busbar_thread)(Thread *t);
  int  (*Level_Order)(Thread *t);
  void (*get_network_results)(Thread *t, real *current, real *voltage, real *soc, real *cap_loss);
  void (*Update_Battery_Input_Parameters)(void);
  void (*Get_Battery_Model_Settings)(cxboolean *msmd_battery_on, int *solution_method,
                                     cxboolean *battery_joule_source_on, cxboolean *battery_abuse_model_on,
                                     int *battery_abuse_model_type, cxboolean *battery_abuse_isc_on, 
                                     cxboolean *battery_cluster, int *battery_echem_model, cxboolean *battery_cap_loss_on, cxboolean *battery_swelling);
  void (*battery_init)(Domain *domain);
  void (*battery_adjustment)(Domain *domain);
  void (*battery_data_write)(FILE *file_p);
  void (*battery_data_read)(FILE *file_p);
  void (*battery_data_write_hdf)(char *fname);
  void (*battery_data_read_hdf)(char *fname);
  void (*get_cluster_info)(cell_t c, Thread *t, int *cluster, int *total_cell_in_cluster, cell_t cell_list[]);
  real (*battery_p2d_postprocessing)(cell_t c, Thread *t, int var_id);
  real (*abuse_heat_4eq)(cell_t c, Thread *t, int var_id);
  int  (*battery_thread_to_id_index)(Thread *t);
  int  (*module_series_index)(Thread *t);
} BATTERY_Functions;
extern FLUENT_EXPORT BATTERY_Functions *battery_fcns;

#endif
