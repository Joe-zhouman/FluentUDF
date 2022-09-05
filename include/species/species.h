/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SPECIES_H
#define _FLUENT_SPECIES_H

#include "dll.h"
#include "prop.h"
#include "sg_mphase.h"
#include "amg.h"
#define SMALL_S 1.e-29
extern FLUENT_EXPORT real MIN_lnK;
#define MAX_lnK  40.0

#define FARADAY_CONSTANT 96485339.

typedef enum
{
  POTENTIAL_BC_NEUMANN   = 0,
  POTENTIAL_BC_DIRICHLET = 1,
  POTENTIAL_BC_COUPLED   = 2
} potential_bc_type;

#define C_I_REACTOR_NET(c,t) (int)(C_STORAGE_R(c,t,SV_I_REACTOR_NET)+0.5)
#define I_REACTOR_NET(x) (int)(x+0.5)

#define GET_MASS_FRACTION_FROM_F_VAR(THREAD, TYPE, MIXTURE, YI){\
if(MIXTURE_NSPECIES(MIXTURE)>0){ \
int _ns, _nspm=MIXTURE_NSPECIES(MIXTURE)-1; \
YI[_nspm] = 1.; \
spe_loop(_ns,_nspm) \
YI[_nspm] -= YI[_ns] = F_VAR(f,THREAD,THREAD_VAR(THREAD).TYPE.yi[_ns]); \
if( YI[_nspm]<0. ){ \
spe_loop(_ns,_nspm) \
YI[_ns] /= (1.-YI[_nspm]); \
YI[_nspm] = 0.;} \
if( THREAD_VAR(THREAD).TYPE.species_in_mole_frac ){\
Material *_sp; \
real _sum = 0.; \
mixture_species_loop(MIXTURE,_sp,_ns) \
_sum += YI[_ns]*MATERIAL_PROP(_sp,PROP_mwi); \
mixture_species_loop(MIXTURE,_sp,_ns) \
YI[_ns] *= MATERIAL_PROP(_sp,PROP_mwi)/_sum;}}} \

#define GET_MASS_FRACTION_FROM_THREAD_VAR(THREAD, TYPE, MIXTURE, YI){\
int _ns, _nspm=MIXTURE_NSPECIES(MIXTURE)-1; \
YI[_nspm] = 1.; \
spe_loop(_ns,_nspm) \
YI[_nspm] -= YI[_ns] = THREAD_VAR(THREAD).TYPE.yi[_ns].constant; \
if( YI[_nspm]<0. ){ \
spe_loop(_ns,_nspm) \
YI[_ns] /= (1.-YI[_nspm]); \
YI[_nspm] = 0.;} \
if( THREAD_VAR(THREAD).TYPE.species_in_mole_frac ){\
Material *_sp; \
real _sum = 0.; \
mixture_species_loop(MIXTURE,_sp,_ns) \
_sum += YI[_ns]*MATERIAL_PROP(_sp,PROP_mwi); \
mixture_species_loop(MIXTURE,_sp,_ns) \
YI[_ns] *= MATERIAL_PROP(_sp,PROP_mwi)/_sum;}}\


/* general species scratch space */

typedef enum
{
  YIR0,  /* mass fraction scratch space - never permanent */
  YIR1,
  YIR2,
  XIR0,
  CIR0,
  CIR1,
  CIR2,
  HIR0,
  HIR1,
  HIR2,
  SIR0,
  NUR0,
  RIR0,
  RIR1,
  RIR2,
  RIR3,
  ZIR0,
  MWR0,
  MWR1,
  MWR2,
  YC0,
  XC0,
  MAX_REAL_NSPE_VARS
} real_nspe_vars;

extern FLUENT_EXPORT real **real_nspe;


typedef enum
{
  YID0,
  YID1,
  CID0,
  CID1,
  CID2,
  ZID0,
  ZID1,
  ZID2,
  PHD0,
  PHD1,
  MWD0,
  MWD1,
  MWD2,
  MAX_DOUB_NSPE_VARS
} double_nspe_vars;

extern FLUENT_EXPORT double **doub_nspe;


typedef enum
{
  YIRP0,
  HIRP0,
  MWRP0,
  MAX_REAL_MPHASE_NSPE_VARS
} real_mphase_nspe_vars;

extern FLUENT_EXPORT real ***real_mphase_nspe;


typedef enum
{
  YIIP0,
  MAX_INT_MPHASE_NSPE_VARS
} int_mphase_nspe_vars;

extern FLUENT_EXPORT int ***int_mphase_nspe;


typedef enum
{
  MUIPR0,
  KIPR0,
  YIPR0,
  XIPR0,
  HIPR0,
  MWPR0,
  MAX_REAL_PROP_NSPE_VARS
} real_prop_nspe_vars;

extern FLUENT_EXPORT real **real_prop_nspe;

typedef enum
{
  YIPD0,
  YIPD1,
  YIPD2,
  YIPD3,
  YIPD4,
  YIPD5,
  YIPD6,
  YIPD7,
  HIPD0,
  HIPD1,
  HIPD2,
  MAX_DOUB_PROP_NSPE_VARS
} doub_prop_nspe_vars;

extern FLUENT_EXPORT double **doub_prop_nspe;

typedef enum
{
  PHPR0,
  APR0,
  BPR0,
  DBPR0,
  MAX_REAL_PROP_NSPESQ_VARS
} real_prop_nspesq_vars;

extern FLUENT_EXPORT real **real_prop_nspesq;

extern FLUENT_EXPORT real *real_dbns_neqnsq0;
extern FLUENT_EXPORT real *real_dbns_neqnsq1;
extern FLUENT_EXPORT real *real_dbns_neqnsq2;
extern FLUENT_EXPORT real *real_dbns_neqnsq3;
extern FLUENT_EXPORT real *real_dbns_neqnsq4;
extern FLUENT_EXPORT real *real_dbns_neqnsq5;

/* SY_Y_RMS storage map */
extern FLUENT_EXPORT int *y_ave_map;
extern FLUENT_EXPORT cxboolean Hybrid_Turb_Comb_P(void);

typedef enum
{
  ZIMONT,
  PETERS,
  MAX_FLAME_SPEED_MODELS
} Flame_Speed_Model;

typedef struct Flame_Speed_Struct
{
  real c1, c2, c3, l2, bl1, bl2;
  cxboolean ewald;
  cxboolean blint;
  Flame_Speed_Model flame_speed_model;
} Flame_Speed_Par;

typedef enum
{
  MELT_PARAM_CONSTANT = 0,
  MELT_PARAM_UDF
} Melt_param_method;

typedef struct meltinputs
{
  Melt_param_method method_melt_param ;
  union
  {
    real value ;
    void (*pudf)(cell_t, Thread *, real *, real *);
  } param;
} Meltinputs;

FLUENT_EXPORT void Compute_Reaction_Rate(Reaction *r, int reaction_model, real T,
                                         int nspe, real mw[], real ci[], real hi[], real si[], real tau,
                                         real *rr, real *rr_t, real *Kf, real *Kb, real *third_be,
                                         real *sum_H, real *sum_nu);
FLUENT_EXPORT void Chemical_Kinetics(Domain *, int spe_indx);
FLUENT_EXPORT void species_diffusive_flux_BC(Domain *domain);
FLUENT_EXPORT void surface_rxn_DBNS(Domain *domain);
FLUENT_EXPORT void Wall_Surface_Reactions(Thread *);
FLUENT_EXPORT int specie_index(Domain *, const char *);
FLUENT_EXPORT char *specie_name(Domain *, int i);
FLUENT_EXPORT char *surface_specie_name(Domain *, int i);
FLUENT_EXPORT char *site_specie_name(Domain *, int i);
FLUENT_EXPORT void cell_reaction_rates(cell_t c, Thread *t, int n,
                                       real *rr, real *rr_l, real *rr_t);
FLUENT_EXPORT void cvd_rate_jac(face_t f, Thread *t, Material *m, Reaction *r,
                                Reaction_Mech *rm, double T, double *cw_i, double rho_w, double *mw,
                                double *r_rate, double *jacob, real *rr_l, int rate_only);
FLUENT_EXPORT real Micro_Mixing_Sc(cell_t c, Thread *t);
FLUENT_EXPORT void Integrate_stiff_chemistry(Domain *domain);
FLUENT_EXPORT void get_fuel_oxid_compositions(Domain *domain, real *temp_str);
FLUENT_EXPORT real species_enthalpy(const cell_t c, const Thread *t, Material *m, const int i, const real T);
FLUENT_EXPORT real cell_species_enthalpy(const cell_t c, const Thread *t, const int i);
FLUENT_EXPORT real face_species_enthalpy(const cell_t c0, const Thread *t0, const int i, const real faceT);
FLUENT_EXPORT void Chemical_Kinetics_Dqmom(Domain *, int spe_indx);
FLUENT_EXPORT void patch_dqmom_species(cell_t c, Thread *t);
FLUENT_EXPORT void patch_dqmom_enthalpy(cell_t c, Thread *t);
FLUENT_EXPORT void Melt_Unsteady_Species_Sources(cell_t c, Thread *t, real *s, int ns) ;
FLUENT_EXPORT void Update_Total_Species(Domain *domain);
typedef enum
{
  REUSE_SOLUTION = 0,
  REUSE_JACOBIAN
} Agglomerate_Chemistry_Method;

typedef enum
{
  CONSTANT_VOLUME_REACTOR,
  CONSTANT_PRESSURE_REACTOR,
  PERFECTLY_STIRRED_REACTOR,
  REACTOR_NETWORK
}
EDC_Reactor_Type;

FLUENT_EXPORT real calc_tau_edc(cell_t c, Thread *t, real time_step, real c2, real cfl_fac);
FLUENT_EXPORT real calc_mdot_edc(cell_t c, Thread *t, real c1, real tau);

#define SV_CVD_I(nX,i)((Svar)((nX)+(i)))
#define SV_CVD_S_I(i)SV_CVD_I(SV_CVD_S_0,i)
#define SV_CVD_AP_I(i)SV_CVD_I(SV_CVD_AP_0,i)

FLUENT_EXPORT cxboolean r_in_mech(Reaction *r, Reaction_Mech *rm);
FLUENT_EXPORT void Surface_Reaction_Rate_Thread(Thread *thread, int spe_indx);

FLUENT_EXPORT void KINetics_gas_rate(double *, double *, double *, double *);
FLUENT_EXPORT int KIN_ODE_Initialize(void);
FLUENT_EXPORT cxboolean species_unsteady_stats(Domain *);

FLUENT_EXPORT real relative_humidity(cell_t, Thread *t);

extern FLUENT_EXPORT real heat_of_reaction;
extern FLUENT_EXPORT real dpm_mass_source;
extern FLUENT_EXPORT real dpm_heat_source;
extern FLUENT_EXPORT real dpm_sensible_heat_source;
extern FLUENT_EXPORT real dpm_fmean_source;
extern FLUENT_EXPORT real dpm_fmean2_source;

extern FLUENT_EXPORT real solid_dqmom_prob[NUM_ENV] ;
extern FLUENT_EXPORT int dqmom_current_mode ;
extern FLUENT_EXPORT real SMALL_PROB ;
extern FLUENT_EXPORT cxboolean sol_tot_spe_scheil ;
extern FLUENT_EXPORT cxboolean limit_spe_seg ;
extern FLUENT_EXPORT cxboolean  include_back_diffusion;
extern FLUENT_EXPORT real back_diff_beta ;
extern FLUENT_EXPORT Meltinputs Melt_back_diff ;
extern FLUENT_EXPORT real **solute_ref_mf;
extern FLUENT_EXPORT real **mf_str;
extern FLUENT_EXPORT cxboolean RD_KINetics_stiff;
extern FLUENT_EXPORT double  dac_tor;
extern FLUENT_EXPORT int  n_target_species;
extern FLUENT_EXPORT int *target_spe_index;
extern FLUENT_EXPORT cxboolean chemistry_call_successful;
extern FLUENT_EXPORT cxboolean need_transfer_chemkin_file;
FLUENT_EXPORT void set_isat_time(cell_t cell, Thread *thread, double time);
FLUENT_EXPORT double get_tfm_rate_factor(cell_t c, Thread *t);
FLUENT_EXPORT void mphase_stiff_rate(cell_t cell,
                                     Thread *thread,
                                     double *y,
                                     void (**mp_rxn_fcns)(cell_t, Thread *, Hetero_Reaction *r,
                                                          real *mp_mw[MAX_PHASES],
                                                          real *yi[MAX_PHASES],
                                                          real *rr, real *rr_t),
                                     double *dydt,
                                     cxboolean initialized,
                                     int neq, int solve_temp);
FLUENT_EXPORT void mphase_stiff_reactions(Domain *domain);
FLUENT_EXPORT real Compute_User_Schmidt(cell_t c, Thread *t, int i);

FLUENT_EXPORT void species_recon_gradient_limiting(Domain *domain, Svar sv, Svar rgw, int ns, real *swmin, real *swmax);
FLUENT_EXPORT void species_gradient_limiting(Domain *domain, Svar sv, Svar rgw);
FLUENT_EXPORT void yi_derivatives(Domain *domain, int ns);
FLUENT_EXPORT void surface_rxn_wall_postproc(Thread *, int);
FLUENT_EXPORT real surface_rxn_cell_postproc(cell_t, Thread *, int);
FLUENT_EXPORT void Wall_Surface_Reactions_postproc(Thread *thread, int post_proc_rxn_indx);
FLUENT_EXPORT cxboolean calc_hydrocarbon_composition(Material *m, real *y, cxboolean reset,
                                                     real *phi, real *yc, real *yh, real *yo);
FLUENT_EXPORT void Free_Constitutional_Species_Arrays(void);
FLUENT_EXPORT void Model_Initialize_species(void);
FLUENT_EXPORT void Model_Initialize_sootspecies(void);
FLUENT_EXPORT void Model_Initialize_electro_chem(void);
FLUENT_EXPORT void Model_Initialize_lithium(void);
FLUENT_EXPORT void Align_New_Species(Domain *, int, int, int *);
FLUENT_EXPORT void Switch_Species_Data(Domain *, int, int);
FLUENT_EXPORT void get_mp_heatflux_ratio(Thread *t, real *Hscale);
FLUENT_EXPORT void get_tliqidus_and_tsolidus(cell_t c, Thread *t, Material *m, real *yi, real *tliqidus, real *tsolidus);
FLUENT_EXPORT void Model_Initialize_pull(void);
FLUENT_EXPORT void Model_Initialize_enthalpy(void);
FLUENT_EXPORT void Update_Solidification_Parameters(Domain *, Pointer );
#define C_BACK_DIFF_BETA(c,t)  ((NNULLP(THREAD_STORAGE(t, SV_SOLID_BETA)) &&\
                              !(Melt_back_diff.method_melt_param == MELT_PARAM_CONSTANT))?\
                              C_STORAGE_R(c,t,SV_SOLID_BETA):Melt_back_diff.param.value)

struct particle_struct;
FLUENT_EXPORT void Integrate_point_chemistry(cell_t c, Thread *t, struct particle_struct *p, Material *m,
                                             cxboolean compress, cxboolean equil, cxboolean pressure_work,
                                             double dtd, real *yk, real *temp, real *hs,
                                             real pgauge, real rho);
FLUENT_EXPORT int SV_SpeciesIndex (const char *, const char *);
FLUENT_EXPORT void surface_stiff_source(face_t f, Thread *t, double *cw_i, double *cc_i, double *cw_i_o, double m_dep,
                                        double *diff_term, double *JT_i, double *diff_term_ij, cxboolean calc_jac,
                                        double *dzdt, double *r_rate, double *jacob, double *mw);
FLUENT_EXPORT cxboolean store_spe_on_thread(Thread *t);
FLUENT_EXPORT void  Calculate_Pollutant_Equilibrium_Species(Domain *domain);
FLUENT_EXPORT void TFM_thickening_and_efficiency_factors(Domain *domain);

FLUENT_EXPORT void dqmom_local_residual(Domain *const, Level *const, Svar, Svar, int, real *);

FLUENT_EXPORT void calc_reactor_network(Domain *domain, const char *mat_name, int max_num_reactors);
FLUENT_EXPORT void fill_reactor_network_cff(Domain *domain, int cff_index);
FLUENT_EXPORT void Read_Reactor_Network_Data(Domain *d, FILE *fd, cxboolean binary, cxboolean double_data);
FLUENT_EXPORT void Write_Reactor_Network_Data(Domain *d, FILE *fd, cxboolean binary);
FLUENT_EXPORT double *get_y_reactor_net(void);
FLUENT_EXPORT int get_nspe_reactor(void);
FLUENT_EXPORT int get_num_reactors(void);

FLUENT_EXPORT cxboolean Par_Premix_with_nspe_or_fluid_thread(Thread *t);
FLUENT_EXPORT void Get_mechanism_reactions(Thread *t, cxboolean *reaction_on);
FLUENT_EXPORT void Disable_isat_for_multi_mech(int *modeci_in);
FLUENT_EXPORT void Alloc_DRG_expert_svars(Domain *domain);
FLUENT_EXPORT void Update_DRG_expert_svars(cell_t c, Thread *t, int *ns, int *nr, int *slist, int *rlist);
FLUENT_EXPORT double update_echem_value(Echem_Pinput *p, face_t f, Thread *t);
FLUENT_EXPORT void Update_Echem_Deposition_Rate(Domain *domain);
FLUENT_EXPORT real get_face_vof_in_echem(face_t f, Thread *t);
FLUENT_EXPORT real F_Var_Neumann_Or_Catalytic(face_t f, Thread *t, int i);
#endif /* _FLUENT_SPECIES_H */
