/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_ISAT_H
#define _FLUENT_ISAT_H

#include "global.h"
#include "mem.h"
extern cxboolean isat_initialized;
/**
 * @addtogroup isat ISAT
 * @{
 * @file
 * ISAT: interface to tabulation library
 */

struct particle_struct;

typedef struct ISAT_Function_struct
{
  void (*isat_disable_mkl_multithreading)(void);
  void (*isat_init)(int d_id);
  void (*isat_step)(cell_t c, Thread *t, struct particle_struct *pp, double dt, double p, double rho,
                    double *phi0, double *phit, int t_id);
  void (*isat_read)(char *fn);
  void (*isat_write)(char *fn);
  int (*isat_tab_size)(void);
  void (*isat_change_params)(void);
  void (*isat_clear_cache)(void);
  void (*isat_free)(void);
  void (*calculate_flamelet)(int *iinfo, double *rinfo, double *f, double *x,
                             double *zo, double *zf, double *z, double *prmx_alpha);
  void (*net_react_rate)(double *yk, double p, double temp, double *dykdt,
                         double *dydt_a, double *dydt_b, int ksplit_rate);
  void (*emst_driver)(int np, int nc, float *f, float *state, float *wt,
                      float omdt, float *fscale, float *cvars, int *info);
  cxboolean (*isat_mp_step)(cell_t c, Thread *t, int *iinfo, double *rinfo, double *y);
  void (*isat_ceq_full_mech_species)(double *red, double h, double p, double *full);
  void (*surface_rxn_step)(face_t f, Thread *t, double *cw, double *cc, double *cw_o, double m_dep, double *diff_term,
                           double *JT_i, double *diff_term_ij, int *iinfo, double *rinfo, double *r_rate, double *mw);
  void (*echem_rxn_diff_balance)(face_t f, Thread *t, face_t f0, Thread *t0, int nspe, Reaction_Mech *rm, double T, double *charge,
                                 real max_exp_term, real min_yi_term, double *yc, double *yw, double *Vjump, real current,
                                 double vjump_explicit, double ctr_explicit, double *diff_term, double *mw, double At,
                                 double m_dep, double *JT_i, cxboolean multicomp_diff, double *diff_term_ij, double *rx_rate,
                                 double *jacobian, cxboolean kinsol_analytical_jacobian, cxboolean *succeed);
  void (*isat_change_material) (char *new_name);
  cxboolean (*isat_Models_Changed)(void);
  void (*calc_reactor_net)(char *mat_name, int *iinfo, double *rinfo, double *reactor_fluxes, double *y);
  int (*ceq_main)(Material *m, int const_h, int in_n_spe, char **in_species_names, int ns_equil, char **equil_species_names, int mode, double p_atm, double *x_in, double ht, int not_first_call, int close, int *out_n_spe, char **out_species_names, double *x_equil, double *t_equil);
  void (*ceq_memory)(Material *m, int ioflag);
  void (*flrmap2cvode_malloc)();
  void (*flrmap2cvode_free)();
  void (*ISATabulate) (int mode, int nx, int nf, double *input_vals, double *output_vals, int *int_params, double *real_params, void (*eval_func) (int nx, int nf, double *input_vals, double *output_vals), void (*eval_jacob) (int nx, int nf, double *input_vals, double *output_vals, double *func_deriv));
} ISAT_Functions;

extern FLUENT_EXPORT ISAT_Functions *isat_fcns;
FLUENT_EXPORT void Open_ISAT_Library(char *dir);
FLUENT_EXPORT void Open_ISAT_Library_CEQ(char *dir);
FLUENT_EXPORT void Open_ISAT_Library_User(void);
FLUENT_EXPORT void update_isat_vars(void);
FLUENT_EXPORT void write_isat_table(char *fn);
FLUENT_EXPORT int isat_table_size(void);
FLUENT_EXPORT void change_isat_params(void);
FLUENT_EXPORT void isat_models_changed(void);
FLUENT_EXPORT void read_isat_table(char *fn);
FLUENT_EXPORT void kill_isat_table(void);
FLUENT_EXPORT void clear_isat_cache(void);
FLUENT_EXPORT char *get_isat_dir_name(void);

FLUENT_EXPORT void InitializeISATPrimitives(void);
FLUENT_EXPORT extern void set_isat_initialized(void);
FLUENT_EXPORT void user_isat_change_params(int table_id, real isat_tol, real store_mb);
FLUENT_EXPORT void free_user_isat_table(int table_id, int max_num_tables);
FLUENT_EXPORT void init_user_isat(int table_id);
/* @} isat */

#endif
