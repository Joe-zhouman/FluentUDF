/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_CUDF_H
#define _FLUENT_CUDF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dll.h"
#include "cxbool.h"
#include "seem.h"

#ifndef UDFCONFIG_H
# include <stdio.h>
#endif


/* These must be of the same number and order as in addon-module-master-list (udf.scm) */
typedef enum
{
  ADDON_NONE = 0,
  ADDON_MHD,
  ADDON_FIBER,
  ADDON_FUELCELLS,
  ADDON_SOFC,
  ADDON_POPBAL,
  ADDON_ADJOINT,
  ADDON_BATTERY,
  ADDON_MSMDBATT,
  ADDON_PEMFC,
  ADDON_MPM,
  ADDON_ROM,
  ADDON_PCB,
  ADDON_VBM,
  ADDON_NEW
} Addon_Module;

enum
{
  UDF_TYPE_DIFFUSIVITY,   /* per thread or per equation functions */
  UDF_TYPE_PROFILE,
  UDF_TYPE_PROPERTY,
  UDF_TYPE_SPECIFIC_HEAT,
  UDF_TYPE_EXCHANGE_PROPERTY,
  UDF_TYPE_VECTOR_EXCHANGE_PROPERTY,
  UDF_TYPE_MASS_TRANSFER,
  UDF_TYPE_LINEARIZED_MASS_TRANSFER, /* not available in GUI */
  UDF_TYPE_HET_RXN_RATE,
  UDF_TYPE_SOURCE,
  UDF_TYPE_DPM_BC,
  UDF_TYPE_INIT,    /* single definition functions */
  UDF_TYPE_ADJUST,
  UDF_TYPE_UDS_FLUX,
  UDF_TYPE_UDS_UNSTEADY,
  UDF_TYPE_HEAT_FLUX,
  UDF_TYPE_WALL_NODAL_DISP,
  UDF_TYPE_WALL_NODAL_FORCE,
  UDF_TYPE_NET_REACTION_RATE,
  UDF_TYPE_VR_RATE,
  UDF_TYPE_SR_RATE,
  UDF_TYPE_PR_RATE,
  UDF_TYPE_EC_RATE,
  UDF_TYPE_EC_KINETICS_PARAMETER,
  UDF_TYPE_BATTERY_PROPERTY,
  UDF_TYPE_BATTERY_PARAMETER_NTGK,
  UDF_TYPE_BATTERY_PARAMETER_ECM,
  UDF_TYPE_BATTERY_ECHEM_MODEL,
  UDF_TYPE_BATTERY_ENTROPIC_HEAT,
  UDF_TYPE_BATTERY_NEWMAN_OCP,
  UDF_TYPE_BATTERY_NEWMAN_BV_RATE,
  UDF_TYPE_BATTERY_NEWMAN_POSTPROCESSING,
  UDF_TYPE_BATTERY_NEWMAN_PROP_ELECTROLYTE,
  UDF_TYPE_BATTERY_NEWMAN_PROP_ELECTRODE,
  UDF_TYPE_BATTERY_NEWMAN_PROP_POROSITY,
  UDF_TYPE_BATTERY_NEWMAN_SWELL_LAYER_N,
  UDF_TYPE_BATTERY_CLUSTER,
  UDF_TYPE_BATTERY_ELOAD_PROFILE,
  UDF_TYPE_TURB_PREMIX_SOURCE,
  UDF_TYPE_ECFM_SOURCE,
  UDF_TYPE_ECFM_SPARK_SOURCE,
  UDF_TYPE_GEQN_SOURCE,
  UDF_TYPE_SPARK_GEOM,
  UDF_TYPE_IGNITE_SOURCE,
  UDF_TYPE_THICKENED_FLAME_MODEL,
  UDF_TYPE_DPM_BODY_FORCE,
  UDF_TYPE_DPM_DRAG,
  UDF_TYPE_DPM_SOURCE,
  UDF_TYPE_DPM_OUTPUT,
  UDF_TYPE_DPM_EROSION,
  UDF_TYPE_DPM_LAW,
  UDF_TYPE_DPM_SWITCH,
  UDF_TYPE_DPM_TIMESTEP,
  UDF_TYPE_IMPINGEMENT,
  UDF_TYPE_FILM_REGIME,
  UDF_TYPE_SPLASHING_DISTRIBUTION,
  UDF_TYPE_SCAT_PHASE_FUNC,
  UDF_TYPE_DPM_SCALAR_UPDATE,
  UDF_TYPE_DPM_SPRAY_COLLIDE,
  UDF_TYPE_DPM_INJECTION_INIT,
  UDF_TYPE_DPM_PROPERTY,
  UDF_TYPE_DPM_VP_EQUILIB,
  UDF_TYPE_DPM_HEAT_MASS,
  UDF_TYPE_DPM_INTERPOLATION,
  UDF_TYPE_TURBULENT_VISCOSITY,
  UDF_TYPE_PRANDTL_K,
  UDF_TYPE_PRANDTL_D,
  UDF_TYPE_PRANDTL_O,
  UDF_TYPE_PRANDTL_T,
  UDF_TYPE_PRANDTL_T_WALL,
  UDF_TYPE_TURB_SCHMIDT,
  UDF_TYPE_WALL_FUNCTIONS,
  UDF_TYPE_TRANS_FLENGTH,
  UDF_TYPE_TRANS_RETHETA_C,
  UDF_TYPE_TRANS_RETHETA_T,
  UDF_TYPE_TRANS_GEOMRGH,
  UDF_TYPE_TRANS_ALG_REC_COR,
  UDF_TYPE_CURVATURE_CORRECTION_CCURV,
  UDF_TYPE_CORNER_FLOW_CORRECTION_CCORNER,
  UDF_TYPE_KW_GEKO_CSEP,
  UDF_TYPE_KW_GEKO_CNW,
  UDF_TYPE_KW_GEKO_CMIX,
  UDF_TYPE_KW_GEKO_BF,
  UDF_TYPE_SBES_BF,
  UDF_TYPE_CAVITATION_RATE,
  UDF_TYPE_RW_FILE,
  UDF_TYPE_ON_DEMAND,
  UDF_TYPE_OUTPUT_PARAMETER,
  UDF_TYPE_REPORT_DEFINITION_FN,
  UDF_TYPE_EXECUTE_AT_END,
  UDF_TYPE_NOX_RATE,
  UDF_TYPE_SOX_RATE,
  UDF_TYPE_HG_RATE,
  UDF_TYPE_CHEM_STEP,
  UDF_TYPE_EDC_SCALES,
  UDF_TYPE_EDC_MDOT,
  UDF_TYPE_PERFORATED_CD,
  UDF_TYPE_CPHI,
  UDF_TYPE_PDF_TRANSPORT_DENSITY,
  UDF_TYPE_GRID_MOTION,
  UDF_TYPE_CG_MOTION,
  UDF_TYPE_GEOM,
  UDF_TYPE_CONTACT,
  UDF_TYPE_SDOF_PROPERTIES,
  UDF_TYPE_HXC_EFFECTIVENESS,
  UDF_TYPE_DELTAT,
  UDF_TYPE_DOM_SOURCE,
  UDF_TYPE_DOM_BC_ADJUST,
  UDF_TYPE_DOM_DIFFUSE_REFLECTIVITY,
  UDF_TYPE_DOM_SPECULAR_REFLECTIVITY,
  UDF_TYPE_NETWORK_NODE_PROP,
  UDF_TYPE_NETWORK_LINK_PROP,
  UDF_TYPE_NETWORK_END_PROP,
  UDF_TYPE_EVAL,
  UDF_TYPE_EXECUTE_ON_LOADING,
  UDF_TYPE_EXECUTE_FROM_GUI,
  /*   UDF_TYPE_PB_BREAK_UP_RATE, */
  UDF_TYPE_PB_BREAK_UP_RATE_FREQ,/*replaces old definitions*/
  UDF_TYPE_PB_BREAK_UP_RATE_PDF,
  UDF_TYPE_PB_COALESCENCE_RATE,
  UDF_TYPE_PB_GROWTH_RATE,
  UDF_TYPE_PB_NUCLEATION_RATE,
  UDF_TYPE_SOLAR_INTENSITY,
  UDF_TYPE_GRAY_BAND_ABS_COEFF,
  UDF_TYPE_SOLAR_TRANSMISSIVITY,
  UDF_TYPE_ANISOTROPIC_DIFFUSIVITY,
  UDF_TYPE_ANISOTROPIC_CONDUCTIVITY,
  UDF_TYPE_DYNAMIC_ZONE_PROPERTY,
  UDF_TYPE_EXECUTE_AT_EXIT,
  UDF_TYPE_EMISSIVITY_WEIGHTING_FACTOR,
  UDF_TYPE_EXECUTE_AFTER_CASE, /* udf to execute after case reading */
  UDF_TYPE_EXECUTE_AFTER_DATA, /* udf to execute after data reading */
  UDF_TYPE_MATRIX_SOLVER,
  UDF_TYPE_SOLIDIFICATION_PARAMS,
  UDF_TYPE_TRANSIENT_PROFILE,
  UDF_TYPE_ZONE_MOTION,
  UDF_TYPE_WSGGM_ABS_COEFF,
  UDF_TYPE_BOILING_PROPERTY,
  UDF_TYPE_MASS_TR_PROPERTY,
  UDF_TYPE_PDF_TABLE,
  UDF_TYPE_REACTING_CHANNEL_SOLVER,
  UDF_TYPE_SOOT_PRECURSOR,
  UDF_TYPE_SOOT_OXIDATION_RATE,
  UDF_TYPE_REACTING_CHANNEL_BC,
  UDF_TYPE_SOOT_NUCLEATION_RATES,
  UDF_TYPE_SOOT_MASS_RATES,
  UDF_TYPE_SOOT_MOM_RATES,
  UDF_TYPE_SOURCE_AE,  /* Adjoint-enabled user-defined sources */
  UDF_TYPE_RW_HDF_FILE,
  UDF_TYPE_FLAMELET_PARAMETERS,
  UDF_TYPE_RELAX_TO_EQUILIBRIUM,
  UDF_TYPE_SOURCE_MASK,
  UDF_TYPE_SPONGE_LAYER,
  UDF_TYPE_SOURCE_FE,
  UDF_TYPE_PERDISP_MOTION,
  UDF_TYPE_PROFILE_NODE,
  UDF_TYPE_GAP_MODEL_SOURCE,
  MAX_UDF_TYPES
};

typedef struct UDF_Data
{
  char *name;
  void (*fcn)(void);    /* pointer to a function returning void */
  int type;
}
UDF_Data;

FLUENT_EXPORT cxboolean Check_UDF_For_T1default(void);
FLUENT_EXPORT cxboolean Check_UDF_For_IO_Macro(void);
FLUENT_EXPORT int fluent_par_fprintf(FILE *fp, const char *format, ...);
FLUENT_EXPORT int fluent_par_fscanf(FILE *fp, const char *format, ...);
#if _NT
FLUENT_EXPORT int fluent_par_vfscanf(FILE *fp, const char *format, va_list ap);
#endif

#if  ! UDF_COMPILER

# include "chip.h"

typedef struct UDF_Cache_Data
{
  cxboolean used;
  void (*fcn)(void);    /* pointer to a function returning void */
  Chip_Cache cache;
}
UDF_Cache_Data;


typedef struct UDF_Cache
{
#if 0
  UDF_Cache_Data adjust;
#endif
  UDF_Cache_Data uds_flux;
  UDF_Cache_Data uds_unsteady;
  UDF_Cache_Data heat_flux;
  UDF_Cache_Data wall_nodal_disp;
  UDF_Cache_Data wall_nodal_force;
  UDF_Cache_Data net_reaction_rate;
  UDF_Cache_Data relax_to_equilibrium;
  UDF_Cache_Data vr_rate;
  UDF_Cache_Data sr_rate;
  UDF_Cache_Data pr_rate;
  UDF_Cache_Data ec_rate;
  UDF_Cache_Data ec_kinetics_parameter;
  UDF_Cache_Data battery_property; 
  UDF_Cache_Data battery_parameter_ntgk;
  UDF_Cache_Data battery_parameter_ecm;
  UDF_Cache_Data battery_echem_model;
  UDF_Cache_Data battery_entropic_heat;
  UDF_Cache_Data battery_newman_ocp;
  UDF_Cache_Data battery_newman_bv_rate;
  UDF_Cache_Data battery_newman_postprocessing;
  UDF_Cache_Data battery_newman_prop_kappa;
  UDF_Cache_Data battery_newman_prop_de;
  UDF_Cache_Data battery_newman_prop_dsn;
  UDF_Cache_Data battery_newman_prop_dsp;
  UDF_Cache_Data battery_newman_prop_tplus;
  UDF_Cache_Data battery_newman_prop_dlnfdlnce;
  UDF_Cache_Data battery_newman_prop_porp;
  UDF_Cache_Data battery_newman_prop_porn;
  UDF_Cache_Data battery_newman_swell_layer_n; 
  UDF_Cache_Data battery_cluster;
  UDF_Cache_Data battery_eload_profile; 
  UDF_Cache_Data trb_prmx_src;
  UDF_Cache_Data ecfm_src;
  UDF_Cache_Data geqn_src;
  UDF_Cache_Data ignite_src;
  UDF_Cache_Data thickened_flame_model;
  UDF_Cache_Data dpm_body_force;
  /* UDF_Cache_Data dpm_drag; */
  UDF_Cache_Data dpm_source;
  UDF_Cache_Data dpm_output;
  UDF_Cache_Data dpm_erosion;
  UDF_Cache_Data dpm_scalar_update;
  UDF_Cache_Data dpm_spray_collide;
  UDF_Cache_Data dpm_timestep;
  UDF_Cache_Data dpm_interpolation;
  UDF_Cache_Data impingement;
  UDF_Cache_Data film_regime;
  UDF_Cache_Data splashing_distribution;
  UDF_Cache_Data pr_k;
  UDF_Cache_Data pr_d;
  UDF_Cache_Data pr_o;
  UDF_Cache_Data pr_t;
  UDF_Cache_Data pr_t_wall;
  UDF_Cache_Data turb_sc;
  UDF_Cache_Data wall_func;
  UDF_Cache_Data trans_flength;
  UDF_Cache_Data trans_retheta_c;
  UDF_Cache_Data trans_retheta_t;
  UDF_Cache_Data trans_geomrgh;
  UDF_Cache_Data trans_alg_rec_cor;
  UDF_Cache_Data curvature_correction_ccurv;
  UDF_Cache_Data corner_flow_correction_ccorner;
  UDF_Cache_Data kw_geko_csep;
  UDF_Cache_Data kw_geko_cnw;
  UDF_Cache_Data kw_geko_cmix;
  UDF_Cache_Data kw_geko_bf;
  UDF_Cache_Data sbes_bf;
  UDF_Cache_Data slip_velocity;
  UDF_Cache_Data cav_rate;
  UDF_Cache_Data nox_rate;
  UDF_Cache_Data sox_rate;
  UDF_Cache_Data hg_rate;
  UDF_Cache_Data chem_step;
  UDF_Cache_Data edc_scales;
  UDF_Cache_Data edc_mdot;
  UDF_Cache_Data perforated_cd;
  UDF_Cache_Data cphi;
  UDF_Cache_Data deltat;
  UDF_Cache_Data dom_source;
  UDF_Cache_Data dom_bc_adjust;
  UDF_Cache_Data dom_diffuse_reflectivity;
  UDF_Cache_Data dom_specular_reflectivity;
  UDF_Cache_Data solar_intensity;
  UDF_Cache_Data solar_transmissivity;
  UDF_Cache_Data solar_diff_intensity;
  UDF_Cache_Data emissivity_weighting_factor;
  UDF_Cache_Data pb_break_up_rate_freq;
  UDF_Cache_Data pb_break_up_rate_pdf;
  UDF_Cache_Data pb_coalescence_rate;
  UDF_Cache_Data pb_growth_rate;
  UDF_Cache_Data pb_nucleation_rate;
  UDF_Cache_Data matrix_solver;
  UDF_Cache_Data solidification_params;
  UDF_Cache_Data pdf_table;
  UDF_Cache_Data channel_solver;
  UDF_Cache_Data soot_precursor;
  UDF_Cache_Data soot_oxidation_rate;
  UDF_Cache_Data soot_nucleation_rates;
  UDF_Cache_Data soot_mass_rates;
  UDF_Cache_Data soot_mom_rates;
  UDF_Cache_Data flamelet_parameters;
}
UDF_Cache;

void UDF_EXPORT UDF_Inquire_Release(int *major, int *minor, int *revision);

extern FLUENT_EXPORT struct UDF_Data *coupling_data;
extern FLUENT_EXPORT int n_coupling_data;

/* exported from Fluent */
extern FLUENT_EXPORT UDF_Cache udf_cache;
Pointer FLUENT_EXPORT Open_UDF_Library(const char *name);
void FLUENT_EXPORT (*Get_UDF_Function(const char *name, int type))(void);
int FLUENT_EXPORT Get_UDF_Function_Type (const char *);
void FLUENT_EXPORT Cache_User_Functions(void);
void FLUENT_EXPORT Remove_UDF_Library(const char *);
void FLUENT_EXPORT Run_UDF_Apply(int mode);
void FLUENT_EXPORT Run_UDF_From_GUI(int mode);
char FLUENT_EXPORT *Get_UDF_Type_Name(int type);
void FLUENT_EXPORT Run_UDF_After_Case_Data(int mode);

typedef struct udf_lib_struct
{

  void *lib;
  char name[4096];

  UDF_Data *udf_data;
  int n_udf_data;

  UDF_Data *udf_util_data;
  int n_udf_util_data;

  struct udf_lib_struct *next;
} UDF_Lib;

#define UDF_NAME(u) ((u)->name)
#define UDF_DATA_LENGTH(u) ((u)->n_udf_data)
#define UDF_DATA(u) ((u)->udf_data)
#define UDF_LIBRARY(u) ((u)->lib)
#define UDF_NEXT_LIBRARY(u) ((u)->next)
#define UDF_UTIL_DATA(u) ((u)->udf_util_data)
#define UDF_UTIL_DATA_LENGTH(u) ((u)->n_udf_util_data)

typedef struct udsm_mngr_struct
{
  char *lib_name;
  int n_udsm;
  int offset;
  struct udsm_mngr_struct *next;
  struct udsm_mngr_struct *prev;
} UDSM_Mngr;

void FLUENT_EXPORT UDSM_Add_Entry(const char *lib_type, cxboolean add_reserved, Pointer entry);
void FLUENT_EXPORT UDSM_Remove_Entry(const char *lib_type, const char *name);
int FLUENT_EXPORT Check_UDM_Registered(int n);
int FLUENT_EXPORT Check_UDS_Registered(int n);
void FLUENT_EXPORT UDSM_Clear_Registered(void);

extern FLUENT_EXPORT UDF_Lib *udf_list;

void FLUENT_EXPORT Execute_UDF_On_Loading(UDF_Lib *new_lib, int uds_set[2], int udm_set[2]);
void FLUENT_EXPORT Clear_UDF_Library_User_Functions_Cache(const UDF_Lib *const);
void FLUENT_EXPORT Delete_UDF_Library(UDF_Lib *lib);
FLUENT_EXPORT cxboolean Add_UDF_Library(const char *name, const char *dir);
FLUENT_EXPORT UDF_Lib *Get_UDF_Library(const char *name);


#endif /*  ! UDF_COMPILER */

#ifdef __cplusplus
}
#endif

#endif /* _FLUENT_CUDF_H */
