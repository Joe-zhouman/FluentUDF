/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/* Contains parameters, structures, variables and functions related to property calculations
   for non-/partially-premixed model */

#ifndef _FLUENT_PDF_PROPS_H
#define _FLUENT_PDF_PROPS_H

#define MAX_PDF_VARS MAX_PDF_SPECIES+5+36+22 /* include pollut vars+scalar vars as well */

#include "dll.h"

enum
{
  INTERP_TEMP = 0,
  INTERP_RHO,
  INTERP_CP,
  INTERP_MW,
  INTERP_SP_START,
  INTERP_SP_MAX = MAX_PDF_SPECIES + 4,
  INTERP_POLLUT_START,
  INTERP_POLLUT_MAX = 36 + INTERP_POLLUT_START, /*36 = MAX_POLLUT_INDEX : just to compile the code*/
  INTERP_SCALAR_START,
  INTERP_SCALAR_MAX = INTERP_SCALAR_START + 22 /*10*2 FGM scalar + 2 other scalars max scalars*/
};

enum
{
  NFGM_STORE_SHARED = 0,
  NFGM_STORE_CLASSIC,
  NFGM_STORE_MAX
};
#define pdf_interp_vars_loop(i) for(i=0;i<Num_Pdf_Interp_Vars;i++)
#define pdf_interp_vars_spe_loop(i,j,ns) for(i=j,ns=Pdf_Interp_Vars[j]-INTERP_SP_START;i<Num_Pdf_Interp_Vars;i++,ns=Pdf_Interp_Vars[i]-INTERP_SP_START)
/*in species loop: change Num_Pdf_Interp_Vars to Num_Pdf_Interp_Vars-Num_pollut_vars_interpolated*/

#define pdf_interp_vars_pollut_loop(i,j,ns) for(i=j,ns=Pdf_Interp_Vars[j]-INTERP_POLLUT_START;i<Num_Pdf_Interp_Vars;i++,ns=Pdf_Interp_Vars[i]-INTERP_POLLUT_START)
#define pdf_interp_vars_scalar_loop(i,j,ns) for(i=j,ns=Pdf_Interp_Vars[j]-INTERP_SCALAR_START;i<Num_Pdf_Interp_Vars;i++,ns=Pdf_Interp_Vars[i]-INTERP_SCALAR_START)


/*#define pdf_interp_vars_pollut_loop(i,j,ns) for(i=j,ns=Pdf_Interp_Vars[j]-INTERP_POLLUT_START;i<Num_Pdf_Interp_Vars;i++,ns=Pdf_Interp_Vars[i]-INTERP_POLLUT_START)
*/
enum
{
  IN_FMEAN = 0,
  IN_FVAR,
  IN_FMEAN2,
  IN_FVAR2,
  IN_HMEAN,
  IN_CMEAN,
  IN_SCADIS,
  IN_YINERT,
  IN_PARAMS_MAX
};

/* Define thermo variable to calculate/fetch for/from PDF table */
enum
{
  NO_THERMO = 0,
  TEMP,
  ALL,
  RATE
};

/* Define thermo variables for UDF PDF table */
enum
{
  TEMP_UDF = 0,
  DEN_UDF,
  CP_UDF,
  MOL_WT_MIX_UDF,
  POLLUT_START_UDF,
  POLLUT_MAX_UDF = 36 + POLLUT_START_UDF, /*36 = MAX_POLLUT_INDEX : just to compile the code*/
  SCALAR_PRMX_SOURCE_UDF,
  SCALAR_HRR_UDF,
  TSS_SCALAR_START_UDF,
  TSS_SCALAR_MAX_UDF = TSS_SCALAR_START_UDF + 20,
  MAX_PROP_UDF
};

typedef struct
{
  real fmean;
  real fmean2;
  real h;
  real h_adia;
  real cmean;
  real temp;
  real *enthalpy_curve;
} pdf_arg_struct;

#define PDF_NONE 0
#define PDF_NONADIABATIC 1 /*old definition*/
#define PDF_NONADIABATIC_EQUILIBRIUM 1
#define PDF_ADIABATIC_FLAMELET_SINGLE 2
#define PDF_ADIABATIC 3 /*old definition */
#define PDF_ADIABATIC_EQUILIBRIUM 3
#define PDF_ADIABATIC_FLAMELET_STRAINED 4
#define PDF_NONADIABATIC_MULTI 5
#define PDF_NONADIABATIC_FLAMELET_SINGLE 6
#define PDF_ADIABATIC_MULTI 7
#define PDF_ADIABATIC_MIXEDISBURNT 8
#define PDF_NONADIABATIC_FLAMELET_STRAINED 9
#define PDF_NONADIABATIC_FLAMELET 9 /*old definition */
#define PDF_NONADIABATIC_MIXEDISBURNT 10
#define PDF_ADIABATIC_PREMIX_FLAMELET 11
#define PDF_NONADIABATIC_PREMIX_FLAMELET 12
#define PDF_TYPE_MAX 13

#define N_MF 2 /*number of mixture fractions */
#define N_STRMS (N_MF+1) /*number of streams */

extern FLUENT_EXPORT int n_spe_pdf;
extern FLUENT_EXPORT int n_spe_pdf_save;
extern FLUENT_EXPORT int pdf_species_names_length;
extern FLUENT_EXPORT char **pdf_species_names;
extern FLUENT_EXPORT Material *pdf_mixture;
extern FLUENT_EXPORT Material *thermo_data_mixture;
extern FLUENT_EXPORT int num_spe_pdf_interp ;
extern FLUENT_EXPORT int *xmol_pdf_interp;
extern FLUENT_EXPORT cxboolean Pdf_Interpolation_Method_Linear;
extern FLUENT_EXPORT int pdf_interp_method ;
extern FLUENT_EXPORT real cvar_small;
/*To revert back to R17.x FGM properties calculations*/
extern FLUENT_EXPORT cxboolean fgm_r17_props;
extern FLUENT_EXPORT cxboolean les_flamtype;
extern FLUENT_EXPORT cxboolean pdf_dynamic_fvar;
extern FLUENT_EXPORT int Nfgm_tab_storage_method;
extern FLUENT_EXPORT real ***Xnfgm_sc;
extern FLUENT_EXPORT int  Xfgm_nx;
extern FLUENT_EXPORT int  Xfgm_nf;
extern FLUENT_EXPORT int  Xfgm_nh;
extern FLUENT_EXPORT real Xfgm_xrate[10000];
extern FLUENT_EXPORT real Xfgm_hloss[500];
extern FLUENT_EXPORT real Xfgm_ff[1000];


typedef struct pdf_model_struct
{
  int pdf_function_type;
  int pdf_type;
  cxboolean flamelet_case;
  cxboolean strained_flamelet_case;
  cxboolean strained_nonadiabatic_case;
  cxboolean nonadiabatic_case;
  cxboolean adiabatic_case;
  cxboolean nonadiabatic_multi_case;
  cxboolean adiabatic_multi_case;
  cxboolean Pdf_strained;
  cxboolean Pdf_multi;
  cxboolean Pdf_nonadiabatic;
  cxboolean Pdf_nonadiabatic_single;
  cxboolean premix_flamelet;
  cxboolean premix_flamelet_ad;
  cxboolean premix_flamelet_nad;
  int version;
  int ladia;
} Pdf_Model;

extern FLUENT_EXPORT Pdf_Model PdfModel;
FLUENT_EXPORT int Pdf_Type(void);
FLUENT_EXPORT int Pdf_All_Nospecies (cell_t c, Thread *t, real fmean, real fvar, real fmean2, real fvar2, real h,
                                     real cmean, real scadis, real y_inert, int *limit,
                                     real *temp, real *den, real *Cp, real *mol_wt, int what);
FLUENT_EXPORT int Pdf_All (Material *m, cell_t c, Thread *t, real fmean, real fvar, real fmean2, real fvar2,
                           real h, real cmean, real scadis, real y_inert, int *limit,
                           real *temp, real *den, real *Cp, real *mol_wt, real *x, real *y,
                           Pollut_Rate *s_pollut[]);
FLUENT_EXPORT real Get_Pdf_HeatReleaserate(cell_t c, Thread *t);
FLUENT_EXPORT real Get_Pdf_Tss_FwdRates_new(cell_t c, Thread *t, int n);
FLUENT_EXPORT real Get_Pdf_Tss_FwdRates(cell_t c, Thread *t, int n);
FLUENT_EXPORT real Get_Pdf_Tss_RevRates(cell_t c, Thread *t, int n);
FLUENT_EXPORT real Get_Pdf_Min_Enthalpy (cell_t c, Thread *t);
FLUENT_EXPORT real Get_Pdf_Max_Enthalpy (cell_t c, Thread *t);
FLUENT_EXPORT real Pdf_Temperature(cell_t c, Thread *t, real fmean, real fvar, real fmean2, real fvar2,
                                   real h, real cmean, real y_inert, real scadis, int *limit);
FLUENT_EXPORT real Pdf_Density(cell_t c, Thread *t, real fmean, real fvar, real fmean2, real fvar2,
                               real h, real cmean, real scadis);
FLUENT_EXPORT real Get_Pdf_Cp(cell_t c, Thread *t);
FLUENT_EXPORT real Get_Pdf_MolWeight(cell_t c, Thread *t);
FLUENT_EXPORT real Get_Pdf_Temperature(cell_t c, Thread *t);
FLUENT_EXPORT real Get_Pdf_Density(cell_t c, Thread *t);
FLUENT_EXPORT real Get_Pdf_Xi(cell_t c, Thread *t, int n);
FLUENT_EXPORT real Get_Premix_Frate_Source_Term(cell_t c, Thread *t);
FLUENT_EXPORT real Pdf_Yi(cell_t c, Thread *t, int n);
FLUENT_EXPORT void Pdf_XY(cell_t c, Thread *t, real *x, real *y);
FLUENT_EXPORT void Calc_Pdf_XY(Material *m, cell_t c, Thread *t, real fmean, real fvar, real fmean2, real fvar2,
                               real h, real *x, real *y, real cmean, real scadis, real y_inert);
FLUENT_EXPORT real Pdf_Adiabatic_Enthalpy(real fmean);
FLUENT_EXPORT real Pdf_Adiabatic_Enthalpy_dufl(real fmean, int ii);
FLUENT_EXPORT real Pdf_hstream(real T, int stream_index);
FLUENT_EXPORT real Pdf_Adiabatic_Enthalpy_2mix(real fmean, real fmean2);
FLUENT_EXPORT real pdf_initial_enthalpy(cell_t c, Thread *t, real T, real fmean, real fvar,
                                        real fmean2, real fvar2, real cmean, real y_inert, real *h_pdf, int *limit);
FLUENT_EXPORT real Ul_par_premix(real fmean, real fvar, real h, int strm_indx);
FLUENT_EXPORT real Interpolate_Tabulated_Flame_Speed(real fmean, real h, real fvar);
FLUENT_EXPORT real Pdf_Unburnt_therm_diff(cell_t c, Thread *t, real fmean);
FLUENT_EXPORT void Pdf_Unburnt_Properties(cell_t c, Thread *t, real h, real fmean, real fmean2,
                                          real fvar, real *rho_u, real *T_u, real *Cp_u, int *limit);
FLUENT_EXPORT void pdf_unburnt_mass_fraction(real fmean, real fmean2, real *y_u);
FLUENT_EXPORT real kinetic_energy(cell_t c, Thread *t);
FLUENT_EXPORT real Pdf_Total_Temperature(cell_t c, Thread *t);
FLUENT_EXPORT real Calc_Pdf_RMS(cell_t c, Thread *t, int k);
FLUENT_EXPORT void Pdf_Enthalpy_Without_Inert(cell_t c, Thread *t, real fmean, real fvar, real fmean2,
                                              real fvar2, real cmean, real scadis, real H, real T_guess,
                                              real y_inert, real *h_pdf, real *h_inert, real *T_new);

FLUENT_EXPORT void Update_Unburnt_Rho_and_Xl(Domain *d);
FLUENT_EXPORT void Turbulent_Premixed_Source(cell_t c, Thread *t, real *turbulent_flame_speed, real *source);
FLUENT_EXPORT Flame_Speed_Par *getFlameSpeedPar(void);
FLUENT_EXPORT void Pdf_unburnt_props(cell_t c, Thread *t, real *tu, real *tb, real *thermal_diff_u, real *drat);
FLUENT_EXPORT void Calculate_unburnt_rho_and_Xl(Thread *t, real *unburnt_density, real *PRMX_Xl);
FLUENT_EXPORT void Calculate_local_unburnt_rho_and_Xl(cell_t c, Thread *t);
FLUENT_EXPORT void Model_Initialize_premixed(void);
FLUENT_EXPORT void render_spe(Domain *domain);
FLUENT_EXPORT void Free_nonadia_c(void);
FLUENT_EXPORT real Get_Yc_eq(real fmean, real fvar);
FLUENT_EXPORT real Get_Yc_eq_sqr(real fmean, real fvar);
FLUENT_EXPORT real Get_Yc_In(cell_t c, Thread *t, real fmean, real hmean);
FLUENT_EXPORT real Get_Yc_Eqm(cell_t c, Thread *t, real fmean, real hmean);
FLUENT_EXPORT real Get_Yc_Eqm_Sqr(cell_t c, Thread *t, real fmean, real hmean);
FLUENT_EXPORT real get_norm_cvar(real yc, real ycvar, real fmean, real fvar);
FLUENT_EXPORT real Premixed_Flamelet_Kinetic_Source(cell_t c, Thread *t, real cmean, real cvar);
FLUENT_EXPORT int Pdf_Interpolate_Variables(cell_t c, Thread *t, int Num_Pdf_Interp_Vars,
                                            int *Pdf_Interp_Vars, real *input_params,
                                            real *output_vals, int *limit, real *xi, cxboolean do_local_inert_transform);
FLUENT_EXPORT void
Update_Pdf_Properties_Linear_Interpolation(Thread *t, Material *m, cxboolean relax,
                                           real omega_T, real omega_rho, cxboolean init_only);
FLUENT_EXPORT int Allocate_Multi_Pdf_Memory (void);
FLUENT_EXPORT int Allocate_Pdf_Memory (void);
FLUENT_EXPORT int Allocate_Prepdf_Memory(void);
FLUENT_EXPORT int Allocate_Single_Pdf_Memory (void);
FLUENT_EXPORT void boundp (real fmean1, real fmean2, real fbactv[]);
FLUENT_EXPORT int GetPdfType(void);
FLUENT_EXPORT int GetPdfVarsFromUser(void);
FLUENT_EXPORT int Inquire_Pdf_Version(void);
FLUENT_EXPORT real Get_Non_Equilibrium_Variable (Thread *t, real scadis, real fvar, real expterm) ;
FLUENT_EXPORT real Calculate_Cell_Scadis_Value(cell_t c, Thread *t);
FLUENT_EXPORT void Pdf_Unburnt_Mole_Fraction(real fmean, real fmean2, real *x_u) ;
FLUENT_EXPORT real Pdf_fsto(real press, real yi[], int *ni, char **inames);
FLUENT_EXPORT int Allocate_Single_Pdf_Memory_Multi_Fgm(void);
FLUENT_EXPORT void Copy_Fgm_Table_Multi_Fgm(int id, cxboolean last_table);
FLUENT_EXPORT void Free_Single_Pdf_Memory_Multi_Fgm(void);
FLUENT_EXPORT void Handle_Pdf_Warnings(Domain *domain, int *args);
FLUENT_EXPORT real Get_Nfgm_Data(int ie, int ic, int icv, int ifb, int ifv, int data_id);
FLUENT_EXPORT void Set_Nfgm_Data(int ie, int ic, int icv, int ifb, int ifv, int data_id, real val);
FLUENT_EXPORT real Interpolate_2d_array_linear(int nx, int ny, real x, real y, real *xa, real *ya, real **phi, real interp_tol);
FLUENT_EXPORT real Interpolate_3d_array_linear(int nx, int ny, int nz, real x, real y, real z, real *xa, real *ya, real *za, real ***phi, real interp_tol);
FLUENT_EXPORT void Allocate_Xnfgm_consumption_speed_table(int nh, int nx, int nf);
FLUENT_EXPORT void Free_Xnfgm_consumption_speed_table(int nh, int nx, int nf);
#define Get_Pdf_Yi(c , t, n) Pdf_Yi(c, t, n)
#endif /*_FLUENT_PDF_PROPS_H*/
