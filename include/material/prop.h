/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_PROP_H
#define _FLUENT_PROP_H

#include "dll.h"
#include "materials.h"
#include "rng.h"
#include "turb.h"
#include "chemkin.h"
#include "species.h"
#include "flowf.h"
#include "limiterbits.h"
#include "amark.h"

/* This parameter should be the maximum of MAX_SPE_EQNS and
 * MAX_PDF_SPECIES. The original definition below is commented
 * out because the interpreted UDF compiler complains
 * #define MAX_SPE_EQNS_PDF MAX(MAX_SPE_EQNS, MAX_PDF_SPECIES)
 * currently MAX_SPE_EQNS = 50 and MAX_PDF_SPECIES = 300 */
#define MAX_SPE_EQNS_PDF MAX_PDF_SPECIES
#define MAX_SOOT_UDF_VARS 10

typedef struct pollut_rate_struct
{
  real fwdrate;
  real revrate;
  real quasirate;
  real *rate;
  real udf_rates[MAX_SOOT_UDF_VARS];
} Pollut_Rate;

typedef struct pollut_rate_table_struct
{
  real a, b, c;
} Pollut_Rate_Table_Param;
/* Notes: Currently it has been made a structure for
 * simplicity and easy handling.
 * a= forward_rate
 * b =rev_rate
 * c =any auxillary_info : e.g., denomenator for NO_THERMAL,
 * may be rev rate for NH3 and HCN giving NO sources. */

/* Fuel type. Supported ones are methane, methanol,
 * isooctane, RMFD_303_indolene.  RMFD_303_indolene is a
 * research fuel (also called indolene), which has a
 * controlled composition simulating typical gasolines. */
enum
{
  METHANE,
  METHANOL,
  PROPANE,
  ISOOCTANE,
  RMFD_303_INDOLENE,
  FUEL_MAX
};

/* anisotropic drag structure for multiphase */
typedef struct anisotropic_drag_struct
{
  int aniso_drag_method;
  real lamn;
  real lamt;
  real d;
  int den_option;
  int visc_option;
  real lamn_iner;
  real lamt_iner;
  cxboolean aniso_control;
  int time_factor;
} Anisotropic_Drag;


/* phase pair i-type and j-type  structure for multiphase area density */
typedef enum                  /*corresponds to phase-pair type */
{
  CONT_DISP = 0,
  DISP_CONT,
  DISP_DISP,
  CONT_CONT,
  CONT_HYB,
  DISP_HYB,
  HYB_CONT,
  HYB_DISP,
  HYB_HYB
} Phase_Pair_Type;

typedef enum                  /*corresponds to mass transfer model flag */
{
  MT_CONST = 0,
  MT_AIAD_ENT_ABS,        /* GM */ /* US114041 */ /* AIAD Entrainment Absortion PROP_METHOD */
  MT_GENTOP_CC,           /* GM */ /* US150386 */ /* GENTOP Complete Coalescence PROP_METHOD */
  MT_EVAP_COND,
  MT_CAV,
  MT_BOILING,
  MT_SPE_TR,
  MT_UDF,
  MT_PB,
  MT_NONE,
  /* plase add new model flag above*/
  MT_MODEL_MAX
} MT_Model_Flag;

typedef struct mt_mech_struct_global
{
  int model_id; /* use eum for mass transfer model flag */
  int from_index;
  int to_index;
  int from_spe_index;
  int to_spe_index;
  real factor_from;
  real factor_to;

} MT_Mech;

/*global phase pair struct;
 * only calculate once in each iteration;
 * if no information is changed for the phase pair,
 * no need to update the phase pair info */
typedef struct phase_pair_struct_global
{
  MT_Mech *mt_mech;
  cxboolean model_active[MT_MODEL_MAX];
  cxboolean mt_thermal; /* for heat transfer with mass transfer*/
  int mt_thermal_index;
  cxboolean mt_thermal_specific_seeding;
  real mt_tpc_adv_vof_seeding;
  cxboolean fixed_to_tsat; /* ht fixed to tsat option*/
  int i_index;
  int j_index;
  int i_type;
  int j_type; /* coninuous or dispersed */
  Phase_Pair_Type pp_type; /* phase pair type */
  int index;
  cxboolean ia_particle;
  cxboolean ht_two_resistance;
  cxboolean mt_tpc_adv;
  cxboolean mt_tpc_adv_one_factor;
  int mt_tpc_adv_temp_mod;
  cxboolean zero_ap_sat_temp;
  int zero_ap_mt_index;
  cxboolean ia_grad_sym; /* switch for ia-grad-symmetric */
  cxboolean mt_source_lin; /* linearization of the mt source in vof-eqn */
  real dT_min; /* min temperature difference */
  int mt_latent_verbose;/* check if latent heat less than zero*/
  real ia_max;
  real grad_mag_max; /*global max*/
  real grad_ratio_limit; /*global limit to use ia-symmertic mech*/
  real min_filter_size; /* filter size for filtered model*/

} MP_Phase_Pair_Global;

/* allocate for each iteration*/
extern FLUENT_EXPORT MP_Phase_Pair_Global *mp_phase_pair; /*[MT_MAX];*/

/* Store global parameters for filtered model in multiphase EE model;
 * phase_pair_struct_global could not be used for filtered solid pressure and viscosity
 * due to the free of allocation of phase_pair_struct_global */
typedef struct mp_filtered_model_struct_global
{
  real min_filter_size; /* min filter size from rpvar*/
  real v_t; /* terminal velocity*/
  real sr_limit; /* strain rate limiter*/
  int solid_press_md_select; /* select Sarkar different solid pressure models*/
} MP_Filtered_Model_Global;

extern FLUENT_EXPORT MP_Filtered_Model_Global mp_granular_filtered_model;

typedef struct phase_pair_struct
{
  int i_index;
  int j_index;
  int i_type;
  int j_type; /* coninuous or dispersed */
  Phase_Pair_Type pp_type;
  int index;
  cxboolean ia_particle;
  cxboolean ht_two_resistance;
  cxboolean ia_grad_sym; /* switch for ia-grad-symmetric */
  real grad_mag_max; /*global max*/
  real grad_ratio_limit; /*global limit to use ia-symmertic mech*/
  /* real d; */
} Phase_Pair;

/*  heterogenity Hd parameter*/
typedef struct heter_para_struct
{
  int heter_option;
  real v_t; /* terminal velocity from macro*/
  real vel; /* slip velocity between solid and gas phases*/
} Heter_Para;

/* area density and linearized area density coefficient*/
typedef struct area_density_struct
{
  real Ai;
  real dAi_vof_i;
  real dAi_vof_j;

  /* real d; */
} Mp_Area_Density;

/* interfacial area density subsection*/
#define MP_IAD_INDEX(i,j)(i<j? (i)+(j)*((j)-1)/2 : (j)+(i)*((i)-1)/2)
FLUENT_EXPORT void MP_Cell_IA_Density(cell_t c, Thread *t, Phase_Pair *phase_pair, cxboolean if_calc_area,
                                      Mp_Area_Density *get_Ai, real vof_min_seeding);
FLUENT_EXPORT void MP_Cell_IA_Density_Global(cell_t c, Thread *t, int pp_index, cxboolean if_calc_area,
                                             Mp_Area_Density *get_Ai, real vof_min_seeding);
FLUENT_EXPORT void Calc_Mp_Area_Density(Domain *);
FLUENT_EXPORT void Fill_Phase_Pair_Struct(Domain *, int i, int j, Phase_Pair *phase_pair);
FLUENT_EXPORT void Fill_Basic_Phase_Pair_Struct(Domain *, int i, int j, Phase_Pair *phase_pair);

FLUENT_EXPORT real Calc_Mp_IAD_Diameter(cell_t c, Thread *t, Phase_Pair *phase_pair, real seeding);
FLUENT_EXPORT real Calc_Mp_IAD_Diameter_Global(cell_t c, Thread *t, int pp_index, real seeding);
FLUENT_EXPORT void MP_Compute_IAD_Gradient_Mag(cell_t c, Thread *t, Phase_Pair *phase_pair, real *nvmag_i, real *nvmag_j);
FLUENT_EXPORT void MP_Compute_IAD_Gradient_Mag_Global(cell_t c, Thread *t, int pp_index, real *nvmag_i, real *nvmag_j);
FLUENT_EXPORT void MP_IAD_Gradient_Max(Domain *mixture_domain, Phase_Pair *phase_pair);
FLUENT_EXPORT real MP_IAD_Gradient_Max_Global(Domain *mixture_domain, int pp_index);

FLUENT_EXPORT void Set_MP_Phase_Pair_Global_Flags(Domain *mixture_domain);
FLUENT_EXPORT void Alloc_And_Init_Phase_Pair_Global_Array(void);
FLUENT_EXPORT void Free_Phase_Pair_Global_Array(void);
/* end of interfacial area density subsection */

FLUENT_EXPORT real Interphase_Heat_Coeff(cell_t c, Thread *t, Property *prop, int i, int j, Phase_Pair *phase_pair);
FLUENT_EXPORT real Interphase_Heat_Coeff_Models(cell_t c, Thread *t, Property *prop, int i, int j,
                                                Phase_Pair *phase_pair, cxboolean index_j_resistance);
FLUENT_EXPORT real Interphase_Heat_Coeff_Models_Global(cell_t c, Thread *t, Property *prop, int i, int j,
                                                       real *h, cxboolean index_j_resistance);

FLUENT_EXPORT real Interphase_Mass_Coeff_Index(cell_t c, Thread *t, Property *prop, int index,
                                               int ns_ii, int ns_jj, Phase_Pair *phase_pair, cxboolean if_liq_gas);
FLUENT_EXPORT real Lift_Coefficient(cell_t c, Thread *t, Property *prop, int i, int j, cxboolean ia_particle);
FLUENT_EXPORT void Turbulent_Dispersion_Force(cell_t c, Thread *t, Property *prop, int i, int j, Phase_Pair *phase_pair, real *val);


FLUENT_EXPORT void Material_Property_Diagnostics(Domain *domain, cxboolean update_state_only);
FLUENT_EXPORT void Update_Domain_Diameters(Domain *domain, cxboolean update_state_only);
FLUENT_EXPORT void Update_Properties(Domain *, cxboolean, cxboolean);
FLUENT_EXPORT void Update_Subiteration_Domain_Properties(Domain *, cxboolean, cxboolean);
FLUENT_EXPORT cxboolean Get_Properties_Need_Init(Domain *domain);
FLUENT_EXPORT cxboolean Get_Properties_Need_Update(Domain *domain);
FLUENT_EXPORT void Set_Properties_Need_Init(Domain *domain, cxboolean init);
FLUENT_EXPORT void Set_Properties_Need_Update(Domain *domain, cxboolean update);
FLUENT_EXPORT cxboolean Properties_Require_Velocity_Derivatives(Domain *);
FLUENT_EXPORT void Update_Mixture_Materials(Domain *);
FLUENT_EXPORT cxboolean material_requires_sdot(Material *m);

FLUENT_EXPORT real Molecular_Weight(Material *, real yi[]);
FLUENT_EXPORT real Gas_Constant(Material *, real yi[]);
FLUENT_EXPORT real Pdf_Molecular_Weight(Material *, real xi[]);
FLUENT_EXPORT real Pdf_Gas_Constant(Material *, real xi[]);
FLUENT_EXPORT real Premixed_Combustion_Density(Material *, real prmx_temp);
FLUENT_EXPORT real Density(cell_t, Thread *, Material *, real T, real p, real yi[], real fmean, real fvar, real fmean2, real fvar2, real h, real prmx_temp, real cmean, real scadis);
FLUENT_EXPORT real Density_Derivative_T(const cell_t c, Thread *t, Material *m, const real T, const real rho, const real p, const real ws_rgas, const real ws_b, const real yi[], const real rho_i[]);
FLUENT_EXPORT void Mole_Fraction(Material *, real yi[], real xi[]);
FLUENT_EXPORT void Mole_Fraction_RG(Material *, double yi[], double xi[]);
FLUENT_EXPORT void Mass_Fraction(Material *, real yi[], real xi[]);
FLUENT_EXPORT void Convert_Mole_to_Mass_Fraction(Material *, real xi[]);
FLUENT_EXPORT real Specific_Heat(cell_t, Thread *, Material *, real T, real rho, real p, real yi[]);
FLUENT_EXPORT real Specific_Heat_Integral(cell_t, Thread *, Material *, real T0, real T1, real yi[]);
FLUENT_EXPORT real Specific_Heat_by_T_Integral(cell_t, Thread *, Material *, real T0, real T1, real rho, real yi[]);
FLUENT_EXPORT real GasFormationEnthalpy(Material *, Material *, int i);
FLUENT_EXPORT real Enthalpy(cell_t, Thread *, Material *, real T, real rho, real p, real yi[], real hi[]);
FLUENT_EXPORT real MP_Total_Enthalpy(cell_t, Thread *, Material *, real T, real rho, real p, real yi[], real hi[]);
FLUENT_EXPORT real Entropy(cell_t, Thread *, Material *m, real T, real rho, real p, real yi[], real xi[]);
FLUENT_EXPORT real Reference_Enthalpy(Material *, real yi[], real hi[]);
FLUENT_EXPORT real Calc_Reference_Enthalpy(Material *);
FLUENT_EXPORT real Temperature(cell_t, Thread *, Material *, real h, real rho, real p, real T_old, real yi[], real hi[]);
FLUENT_EXPORT void Set_Reference_Density(Domain *);
FLUENT_EXPORT real Calc_MP_Operating_Density(Domain *);
FLUENT_EXPORT void Set_Explicit_Zero_Divergence(Domain *);
FLUENT_EXPORT real Latent_Heat_Content (cell_t c, Thread *t, Material *m, real T, real *ci);
FLUENT_EXPORT real Transition_Function(real vofV, real vofV_L1, real vofV_L2, int option);
FLUENT_EXPORT real Virtual_Mass_Coefficient(cell_t c, Thread *t, Property *prop, int i, int j);
FLUENT_EXPORT real Drag_Coefficient(cell_t c, Thread *t, Property *prop, int i, int j, Phase_Pair *phase_pair);
FLUENT_EXPORT real Drag_Factor(cell_t c, Thread *t, Property *prop, int i, int j); /*US 39205*/
FLUENT_EXPORT void calc_ave_diss(Domain *mix_domain);
FLUENT_EXPORT void Drag_Coefficient_Anisotropic(cell_t c, Thread *t, Property *prop, int i, int j, Svar sv_g, Svar sv_sm_g,
                                                real drag_coeff[ND_3][ND_3], Anisotropic_Drag *aniso_drag);
FLUENT_EXPORT real drag_constant_cd(cell_t c, Thread *ti, Thread *tj, Phase_Pair *phase_pair, Property *prop);
FLUENT_EXPORT real drag_schiller_naumann_pb(cell_t c, Thread *ti, Thread *tj, Phase_Pair *phase_pair);
FLUENT_EXPORT real drag_schiller_naumann(cell_t c, Thread *ti, Thread *tj, Phase_Pair *phase_pair);
FLUENT_EXPORT real drag_morsi_alexander(cell_t c, Thread *ti, Thread *tj, Phase_Pair *phase_pair);
FLUENT_EXPORT real drag_grace(cell_t c, Thread *ti, Thread *tj, int i, int j, Phase_Pair *phase_pair);   /* US160011 */ /* US168773 */
FLUENT_EXPORT real drag_tomiyama(cell_t c, Thread *ti, Thread *tj, int i, int j, Phase_Pair *phase_pair);
FLUENT_EXPORT real drag_symmetric(cell_t c, Thread *ti, Thread *tj, int i, Phase_Pair *phase_pair);
FLUENT_EXPORT real drag_syamlal_obrien(cell_t c, Thread *ti, Thread *tj, Phase_Pair *phase_pair);
FLUENT_EXPORT real drag_syamlal_obrien_para(cell_t c, Thread *ti, Thread *tj, Phase_Pair *phase_pair);
FLUENT_EXPORT real drag_syamlal_obrien_symmetric(cell_t c, Thread *ti, Thread *tj, int i, int j, Phase_Pair *phase_pair);
FLUENT_EXPORT real drag_wen_yu_pb( cell_t c, Thread *ti, Thread *tj, Phase_Pair *phase_pair );
FLUENT_EXPORT real drag_wen_yu( cell_t c, Thread *ti, Thread *tj, Phase_Pair *phase_pair );
FLUENT_EXPORT real drag_gidaspow( cell_t c, Thread *ti, Thread *tj, Phase_Pair *phase_pair );
FLUENT_EXPORT real drag_huilin_gidaspow(cell_t c, Thread *ti, Thread *tj, Phase_Pair *phase_pair);
FLUENT_EXPORT real drag_gibilaro(cell_t c, Thread *ti, Thread *tj, Phase_Pair *phase_pair);
FLUENT_EXPORT real Drag_Emms(cell_t c, Thread *ti, Thread *tj, Phase_Pair *phase_pair);
FLUENT_EXPORT real Emms_Hd_Lu(real vof, real Re); /* Re is mean slip Reynold number*/
FLUENT_EXPORT real Emms_Hd(real vofi, real Re);
FLUENT_EXPORT real Filtered_Drag_Hd(cell_t c, Thread *ti, Thread *tj, Heter_Para *heter_para, Phase_Pair *phase_pair);
FLUENT_EXPORT real Drag_Filtered_Sarkar(cell_t c, Thread *ti, Thread *tj, Phase_Pair *phase_pair);
FLUENT_EXPORT real drag_coeffs_universal(real d, real Re, real alpha_d, cell_t c, Thread *tc,
                                         Thread *td, Thread *tm, int i, int j);
FLUENT_EXPORT real MP_Strain_Rate(cell_t c, Thread *t);
/* US160011 */
FLUENT_EXPORT real drag_ishiizuber_swarm(cell_t c, Thread *ti, Thread *tj, int i, int j, Phase_Pair *phase_pair);

/* GM */ /* US160011 */ /* Defining the drag coefficient function for AIAD */
FLUENT_EXPORT real drag_aiad(cell_t c, Thread *ti, Thread *tj, int i, int j, Phase_Pair *phase_pair);

FLUENT_EXPORT real TD_Transition_Function(cell_t c, Thread *t, int j);
FLUENT_EXPORT real drag_universal(cell_t c, Thread *ti, Thread *tj, Thread *tm, int i, int j, Phase_Pair *phase_pair);
FLUENT_EXPORT real Capillary_Pressure(cell_t c, Thread *t, int i, int j, real *satw, real *cp, int npts, int method);

FLUENT_EXPORT void Capillary_Pressure_Gradient(cell_t c, Thread *t, Property *prop, int i, int j, real *val);
FLUENT_EXPORT void Turbulence_Interaction_Models(Property *prop);
FLUENT_EXPORT real Wall_Lubrication_Coefficient(cell_t c, Thread *t, Property *prop, int i, int j);
FLUENT_EXPORT real Syamlal_OBrien_Viscosity(cell_t c, Thread *t, real diam, real rho, real eltic, real g0);
FLUENT_EXPORT real Gidaspow_Viscosity(cell_t c, Thread *t, real diam, real rho, real eltic, real g0);
FLUENT_EXPORT real Filtered_Sarkar_Viscosity(cell_t c, Thread *t, real diam, real rho);

FLUENT_EXPORT real Syamlal_OBrien_Conductivity(cell_t c, Thread *t, real diam, real rho, real eltic, real g0);
FLUENT_EXPORT real mpg_gamma(real T, real rho, real vof, real packing, real e);
FLUENT_EXPORT real mpg_pressure(real T, real rho, real vof, real packing, real e);
FLUENT_EXPORT real mpg_rdf_g0(real vof, real packing);
FLUENT_EXPORT void Slip_Velocity(cell_t c, Thread *t, Property *prop, int i, int j, real *val);
FLUENT_EXPORT real Bulk_Viscosity(cell_t c, Thread *t, Property *p, real rho, real T);
FLUENT_EXPORT real generic_property(cell_t c, Thread *t, Property *prop, Property_ID id, real T);
FLUENT_EXPORT real generic_mp_model_coeff(cell_t c, Thread *t, Property *prop, int i, int j);
FLUENT_EXPORT real generic_mp_model_coeff_NF(cell_t c, Thread *t, Property *prop, int i, int j);   /* US168773 */
FLUENT_EXPORT real Generic_PROP_ktc(face_t f, Thread *tf, Material *m_solid, real T);
FLUENT_EXPORT void Wilkes_Coeffs(Material *m);
FLUENT_EXPORT void clear_Wilkes_vars(void);
FLUENT_EXPORT real Relative_Viscosity(cell_t c, Thread *t, Material *m);
FLUENT_EXPORT real Viscosity(cell_t c, Thread *t, Material *m, real T, real rho,
                             real yi[], real xi[], real S_dot);
FLUENT_EXPORT real Thermal_Conductivity(cell_t c, Thread *t, Material *m, real T,
                                        real rho, real yi[], real xi[], real S_dot);
FLUENT_EXPORT real binary_mass_diffusivity(cell_t c, Thread *t, Material *m,
                                           int index, real T, real T32, real p,
                                           real sig_ab[], real eps_ab[]);
FLUENT_EXPORT void Mass_Diffusivity(cell_t c, Thread *t, Material *m, real T,
                                    real p, real xi[], real D[]);
FLUENT_EXPORT void update_laminar_flame_speed(Domain *domain);
FLUENT_EXPORT void update_laminar_flame_thickness(Domain *domain);
FLUENT_EXPORT real Speed_Of_Sound(cell_t c, Thread *t, Material *m, real T, real rho, real p, real yi[]);
FLUENT_EXPORT void Thermal_Diffusivity(cell_t c, Thread *t, Material *m, real T, real xi[], real yi[], real DT[]);
FLUENT_EXPORT void UDS_Diffusivity(cell_t c, Thread *t, Material *m, real T, real diff[], cxboolean store_p[]);
FLUENT_EXPORT real Absorption_Coefficient(Material *m, real T, cell_t c, Thread *t);
FLUENT_EXPORT real Scattering_Coefficient(Material *m, real T, cell_t c, Thread *t);
FLUENT_EXPORT real Friction_Viscosity(cell_t c, Thread *t, Property *p );
FLUENT_EXPORT real omega_mu_kt(const real epsilon_over_t);
FLUENT_EXPORT real Granular_Conductivity(cell_t c, Thread *t, Property *p, real rho);
FLUENT_EXPORT Pointer inquire_property_methods(Matl_Type_ID, const char *);
FLUENT_EXPORT Pointer inquire_properties(Matl_Type_ID);
FLUENT_EXPORT real get_nu_granular_slip(face_t, Thread *t, cell_t c0, Thread *t0);
FLUENT_EXPORT real Interfacial_Area(real vof_vapor, real vof_liqid, real diameter);
FLUENT_EXPORT real Algebraic_Interfacial_Area(cell_t c, Thread *t, int i, int j, real vof_v, real vof_l, real diam);
FLUENT_EXPORT void Ncgs_Mass_Fraction(Domain *);
FLUENT_EXPORT void Vapor_Pressure_Cav(Domain *);
FLUENT_EXPORT void Set_f_T_u(Thread *t);
FLUENT_EXPORT void Update_Inert_Properties(Domain *, cxboolean);
FLUENT_EXPORT void Saturation_Temperature(Domain *);
FLUENT_EXPORT real get_path_length(Domain *);
FLUENT_EXPORT void Correct_Enthalpy(Domain * );
FLUENT_EXPORT void Model_Initialize_properties(void);
FLUENT_EXPORT void InitializeSyamlalDragParameters(void);
FLUENT_EXPORT CELL_FUNCTION_DEF(cellRgas);
FLUENT_EXPORT CELL_FUNCTION_DEF(cellSpeedOfSound);
FLUENT_EXPORT CELL_FUNCTION_DEF(cellMeanMW);
extern FLUENT_EXPORT int operating_density_inlet_id;
extern FLUENT_EXPORT cxboolean if_compressible_liquid(Domain *domain);
extern FLUENT_EXPORT void getsatvalues_NIST(int index, double x, double y[]);
FLUENT_EXPORT int getsatvalues_NIST_msp(int index, double x, double y[], int ibubbleordew);
FLUENT_EXPORT void get_satprop_NIST_msp(int index, double z[], double minrho, double maxrho, int nsat, int npts[],
                                        double p_bub[], double t_bub[], double p_dew[], double t_dew[]);
extern FLUENT_EXPORT void get_prop_NIST_msp(double T, double press, double z[], double prop[]);

#define MAX_TEMP_ITER (10)
#define TEMP_eps (1.0e-5)
#define T_REF 298.15
#define P_REF 101325.
#define NN_SMALL 1.0e-10

#define THREAD_PROP(t,prop,matl_indx)\
 MATERIAL_PROP(THREAD_MATERIAL(t),prop)
#define THREAD_PROP_METHOD(t,prop,matl_indx)\
 MATERIAL_PROP_METHOD(THREAD_MATERIAL(t),prop)
#define THREAD_PROP_COEF(t,prop,matl_indx,coef_indx)\
 MATERIAL_PROP_COEF(THREAD_MATERIAL(t),prop,coef_indx)
#define THREAD_PROP_NUM_COEF(t,prop,matl_indx)\
 MATERIAL_PROP_NUM_COEF(THREAD_MATERIAL(t),prop)

#define THREAD_LAS_COEFF(t)\
     ((SCAT_PHASE_FUNC_LINEAR == THREAD_PROP_METHOD(t,PROP_scat_phase_func,0)) ? \
 THREAD_PROP(t,PROP_scat_phase_func,0) : 0)
/* all (relevant) property methods are set by material-0 */
#define DENSITY_METHOD(t) THREAD_PROP_METHOD(t,PROP_rho,0)

#define GRNLR_T_METHOD(t) THREAD_PROP_METHOD(t,PROP_granular_t,0)

#if SEEM
FLUENT_EXPORT Pointer client_property_methods(Domain *, const char *material_name,
                                              const char *mix_mat_name,
                                              const char *const *property_names,
                                              const cxboolean include_expr,
                                              const cxboolean include_nist);
#endif

FLUENT_EXPORT Material *mixture_material(Domain *);

/* use harmonic mean for diffusion coefficients */
#define DIFFUSION_COEF_AVE(d0,d1)((ABS((d0)+(d1))<SMALL_S) ? 0.0 : (2*(d0)*(d1)/((d0)+(d1))))

/* use distance weighted harmonic mean for diffusion coefficients */
#define DIFFUSION_COEF_AVE_LONG(g,g0,g1,d0,d1,r)        \
  {\
    real _d;\
    g = (g0)*(g1);\
    _d = (d1)*(g0)+(d0)*(g1)+(r)*(g);\
    g = (_d == 0.0) ? 0.0 : ((d0)+(d1))*(g)/_d;\
  }
#define DIFFUSION_COEF_AVE_LONG0(g0,g1,d0,d1,r)\
  ((((d1)*(g0)+(d0)*(g1)+(r)*(g0)*(g1))==0.0) ? 0.0 : \
   ((d0)+(d1))*(g0)*(g1)/((d1)*(g0)+(d0)*(g1)+(r)*(g0)*(g1)))


/* --------------------------------------------------
   cubic equation of state library interface
   -------------------------------------------------- */

typedef struct
{
  /* component critical temperature [K] */
  real Tc;
  /* component critical pressure [Pa] */
  real Pc;
  /* component acentric factor [-] */
  real Wc;
  /* vaporization temperature [K] */
  real Tvap;

} cubiceos_component_t;

typedef struct
{
  /* mole fraction */
  real *x;

  /* fugacity */
  real *phi;

  /* departure enthalpy */
  real Hdep;

  /* departure entropy */
  real Sdep;

  real Z;

} cubiceos_phase_t;

typedef enum
{
  EOS_SOAVE_REDLICH_KWONG = 1,
  EOS_PENG_ROBINSON,
  EOS_PENG_ROBINSON_GASEM
} cubic_eos_type_t;

typedef struct cubiceos_s
{
  /* gas constant */
  real R;
  /* pressure */
  real P;
  /* temperature */
  real T;

  cubiceos_phase_t vapor;
  cubiceos_phase_t liquid;

  /* number of components */
  int ncomp;

  /* size of allocated space for component data */
  int ncomp_allocated;

  cubiceos_component_t *comp;

  /* interaction parameter */
  real k12;

  /* equation type */
  cubic_eos_type_t eqtype;

  /* temporary storage for eos parameters (Bi,Xi,Aij) */
  real *realtemp;

} cubiceos_t;

FLUENT_EXPORT cubiceos_t *
cubiceos_realloc(cubiceos_t *eos, int n);

FLUENT_EXPORT int
cubiceos_bubble_pressure(cubiceos_t *eos, int maxiter);

FLUENT_EXPORT void
cubiceos_free(cubiceos_t *eos);

FLUENT_EXPORT void InitializeSyamlalDragParameters(void);
FLUENT_EXPORT void InitializeNISTLookUpTable(void);
FLUENT_EXPORT void InitializeNISTLookUpTable_msp(void);
FLUENT_EXPORT void Initializesetusetablep(void);

enum
{
  NIST_q_molar = 0,
  NIST_q_mass,
  NIST_q_vol,
  NIST_den_m,
  NIST_den_l,
  NIST_den_v,
  NIST_cp_m,
  NIST_cp_l,
  NIST_cp_v,
  NIST_ktc_m,
  NIST_ktc_l,
  NIST_ktc_v,
  NIST_mu_m,
  NIST_mu_l,
  NIST_mu_v,
  NIST_h_m,
  NIST_h_l,
  NIST_h_v,
  NIST_a_m,
  NIST_a_l,
  NIST_a_v,
  NIST_massfrac0_l,
  NIST_massfrac20_l = NIST_massfrac0_l + 19,
  NIST_massfrac0_v,
  NIST_massfrac20_v = NIST_massfrac0_v + 19,
  NIST_molefrac0_l,
  NIST_molefrac20_l = NIST_molefrac0_l + 19,
  NIST_molefrac0_v,
  NIST_molefrac20_v = NIST_molefrac0_v + 19,
  NIST_prop_MAX
};

typedef struct cpt_curve_struct
{
  int numPoints;
  double pcrit;
  double tcrit;
  double pmin;
  double tmin;
  double *pressures;
  double *temps;
} CPTCurve;

typedef struct cpt_curve_set_struct
{
  int numCurves;
  double *mfractions;
  CPTCurve **curves;
} CPTCurveSet;

FLUENT_EXPORT CPTCurve *newCPTCurve(int npoints);
FLUENT_EXPORT CPTCurve *freeCPTCurve(CPTCurve *curve);
FLUENT_EXPORT CPTCurveSet *newCPTCurveSet(int ncurves);
FLUENT_EXPORT CPTCurveSet *freeCPTCurveSet(CPTCurveSet *cset);

FLUENT_EXPORT void sortCPTCurve(CPTCurve *curve);
FLUENT_EXPORT void sortCPTCurveSet(CPTCurveSet *cset);
/*#if !RP_NODE*/
FLUENT_EXPORT CPTCurveSet *readCPTCurveSet(const char *filename);
FLUENT_EXPORT int writeCPTCurveSet(int index, CPTCurveSet *cset, char *filename);
/*#endif*/ /* !RP_NODE */

FLUENT_EXPORT double getTempFromCPTCurve(CPTCurve *curve, double pressure, cxboolean press_norm_p);
FLUENT_EXPORT double getTempFromCPTCurveSet(CPTCurveSet *cset, double mass_frac, double pressure, cxboolean press_norm_p);
FLUENT_EXPORT void getInterpLimitsFromCPTCurveSet(double interp[], CPTCurveSet *cset, double mass_frac);
FLUENT_EXPORT void locate_index_bisect(real xx[], int n, real x, int *j);
FLUENT_EXPORT real Get_Tabular_Interpolated_Value(real *data_x, real val_x, real *data_y, int size);

enum
{
  ID_Bubble = 0,
  ID_Dew,
  ID_Bubble_Dew_Max
};

enum
{
  ID_pcrit = 0,
  ID_tcrit,
  ID_pmin,
  ID_tmin,
  ID_Curve_Max
};

/*Capillary Pressure Methods*/

enum
{
  CAP_METHOD_NONE = 0,
  CAP_METHOD_BROOKS_COREY,
  CAP_METHOD_VAN_GENUCHTEN,
  CAP_METHOD_LEVERETT_J_FUNCTION,
  CAP_METHOD_SKJAEVELAND,
  CAP_METHOD_UDF,
  CAP_METHOD_TABULAR
};



/*
#if PARALLEL
void host_to_node_CPTCurveSet(CPTCurveSet *cset);
#else
# define host_to_node_CPTCurveSet(cset)
#endif*/

#endif /* _FLUENT_PROP_H */

