/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#define FILENAMEMAX 216
#define CHAR_SIZE 256
#define MAX_EQUILIBRIUM_SPECIES 1000 /* Maximum species in product */

#define UZIND(ih,i,it,k)  uz[(ih)*(ng-2)*nt*neq + (i-1)*nt*neq + (it)*neq + k]
#define max_fla_iter 1000

enum
{
  STEADY_FLAMELET = 0,
  UNSTEADY_FLAMELET = 1,
  DIESEL_UNSTEADY_FLAMELET = 2
};

extern FLUENT_EXPORT cxboolean  dufl_num_fla_changed;


FLUENT_EXPORT void Calc_Flamelet(double *zf, double *zo,
                                 cxboolean species_in_mass_fraction);
FLUENT_EXPORT cxboolean calculate_fsto(Material *m, int nspe, real pres,
                                       real *yi_fuel, real *yi_oxid,
                                       real *fsto, real *adiatemp,
                                       int *equil_n_species,
                                       char **equil_species_names,
                                       int exclude_species,
                                       char **exclude_species_names,
                                       double *equil_xmol, int stream_type);
FLUENT_EXPORT cxboolean Chemical_Equilibrium(Material *m, real ht, real p, real *yi,
                                             real *te, int const_h, cxboolean reset_init, int close);
FLUENT_EXPORT void interpolate_failed_equilibrium(double *fm, double *curve,
                                                  double *zo, double *zf, cxboolean *success, int size, int fl_spe);
FLUENT_EXPORT int discretize_f(int ng, double *f, double fsto, cxboolean prmx_fla);
FLUENT_EXPORT void Update_Unsteady_Flamelet(Domain *domain, double *zf, double *zo,
                                            cxboolean species_in_mass_fraction, cxboolean force_initialization);
FLUENT_EXPORT cxboolean Check_Species_In_Thermodb(const char *sp);
FLUENT_EXPORT void Free_Unsteady_Flamelet_Memory(void);
FLUENT_EXPORT void compute_net_react_rate_helper(real *y, real p, real temp, real *dydt,
                                                 real *dydt_a, real *dydt_b, int ksplit_rate);
FLUENT_EXPORT real compute_heat_release_rate_helper(real *y, real p, real atemp);
FLUENT_EXPORT void Init_Ufla(Domain *domain, cxboolean restart);
FLUENT_EXPORT void Update_Ufla(Domain *domain);
FLUENT_EXPORT cxboolean Ufla_Initialized(void);
FLUENT_EXPORT void Free_ufla_Memory(void);
FLUENT_EXPORT cxboolean compute_unsteady_flamelet_parameters(Domain *domain, real *ascd, real *avp,
                                                             real *tox, real *tfuel, real fsto, int numfl);
FLUENT_EXPORT void Fill_Unsteady_Flamelet_Arrays(int total_num_flmlts, int max_grd_pnts,
                                                 real **z_x, real **phit_x, real  ***phix_x);
FLUENT_EXPORT void set_rif_fsto_pold( real fsto, real pold);
FLUENT_EXPORT void get_rif_fsto_pold( real *fsto, real *pold);
FLUENT_EXPORT void default_thermo_file_name(char *);
FLUENT_EXPORT void default_DR_thermo_file_name(char *);
FLUENT_EXPORT void fill_zt_fgm(int *ist, double *z);
FLUENT_EXPORT void Model_Initialize_ufla_y(void);
FLUENT_EXPORT void Reset_Diesel_Flamelets(Objp *tlist);
FLUENT_EXPORT void Calc_Strained_Flamelet(double *zf, double *zo,
                                          cxboolean species_in_mass_fraction);
FLUENT_EXPORT void Calc_Freely_Propagating_Flame_Speed(double *zf, double *zo, cxboolean species_in_mass_fraction);
extern FLUENT_EXPORT  double fla_resid_vals[3][max_fla_iter];
extern FLUENT_EXPORT int fla_niter;
extern FLUENT_EXPORT cxboolean flush_fla_resid ;
extern FLUENT_EXPORT int num_fla_spe_check_conv;
extern FLUENT_EXPORT int fla_spe_check_conv[10];
