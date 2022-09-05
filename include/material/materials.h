/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_MATERIALS_H
#define _FLUENT_MATERIALS_H

#include "global.h" /* required for cudf.h */
#include "dll.h"
#include "cudf.h"   /* UDF_Cache_Data */
#include "tabulation.h"
#include "entity.h"

#define MATERIAL_NAME_LENGTH 60
#define MAX_SPE_EQNS 50
#define MAX_PDF_SPECIES   700
#define MAX_PROB_EQNS 10
#define MAX_SOOT_MOM_EQNS 10
#define MAX_THERMO_DATA_SPECIES 700
/* This parameter should be the maximum of MAX_SPE_EQNS and
    MAX_PDF_SPECIES. The original definition below is commented
    out because the interpreted UDF compiler complains
#define MAX_SPE_EQNS_PDF MAX(MAX_SPE_EQNS, MAX_PDF_SPECIES)
currently MAX_SPE_EQNS = 50 and MAX_PDF_SPECIES = 300 */
#define MAX_SPE_EQNS_PDF MAX_PDF_SPECIES
#define MAX_PDF_SPECIES_POST 200
#define MAX_PLOG 12
#define MAX_SUB_DOMAINS 20  /* US168773 - This has been moved here from mem_grid.h without affecting any known dependency */
#define MAX_PHASES MAX_SUB_DOMAINS  /* US168773 - This has been moved here from mem_grid.h without affecting any known dependency */
#define MP_PROP_MAX (MAX_PHASES*(MAX_PHASES+1)/2)  /* US168773 - This is a calculation of the maximum number of phase pairs */

#define PROP_UDF_NAME_LENGTH 128  /*Increasing from 64 Byte CR: 38605*/

typedef struct cueos_parameter_struct
{
  real tcrit ;
  real pcrit ;
  real vcrit ;
  real omega ;
  real a0 ;
  real b0 ;
  real c0 ;
  real bb ;
  real dd ;
  real ff ;
  real nrk ;
  cxboolean initialized;
} CUEOS_Parameter;

typedef struct property_struct
{
  int method;
  double constant;    /* constant value of property */
  union
  {
    Polynomial *poly;
    double *vector;
    double **matrix;
    cxboolean yes_or_no;
  } u;
  union
  {
    Table_2D_With_Range_Check *table_tp;
    Table_1D_With_Range_Check *table_sat;
  } u_tables;
  char *string;
  char udf_name[PROP_UDF_NAME_LENGTH];
  UDF_Cache_Data udf_prop;
  void *expr;
} Property;

typedef enum
{
  MATERIAL_UNKNOWN = -1,
  MATERIAL_FLUID = 0,
  MATERIAL_SOLID,
  MATERIAL_MIXTURE,
  MATERIAL_INERT_PARTICLE,
  MATERIAL_DROPLET_PARTICLE,
  MATERIAL_PARTICLE_MIXTURE,
  MATERIAL_COMBUSTING_PARTICLE,
  MATERIAL_TYPE_MAX
} Matl_Type_ID;

typedef struct type_names_struct
{
  char *label;
  Matl_Type_ID type_id;
} Type_Names;

/**
 * \brief An enum that provides ID's for material properties (does not include
 *        material settings that are not properties).
 *
 * Whatever is added here make sure to add to 'property_names[PROP_MAX]' list
 * in materials.c for matching with scheme symbol and user name.
 */
typedef enum
{
  PROP_unknown = -1,
  PROP_rho = 0,     /* density (incompressible fluid, or solid) */
  PROP_Cp,      /* specific heat at constant pressure */
  PROP_mu,      /* laminar viscosity */
  PROP_ktc,     /* thermal conductivity (isotropic) */
  PROP_ktc0,      /* thermal conductivity (anisotropic/ortho direction 0)*/
  PROP_ktc1,      /* thermal conductivity (orthotropic direction 1) */
  PROP_ktc2,      /* thermal conductivity (orthotropic direction 2) */
  PROP_diff,      /* binary mass diffusivity coeff */
  PROP_mwi,           /* molecular weight */
  PROP_hform,     /* enthalpy of formation */
  PROP_href,                    /* enthalpy of formation + integral 298.15 to Tref */
  PROP_sform,     /* entropy of formation */
  PROP_reference_temp,          /* reference temperature for PROP_hform/sform */
  PROP_Rgas,      /* universal gas constant/molecular weight */
  PROP_dof,                     /* degrees of freedom */
  PROP_charSigma,   /* Lennard-Jones characteristic length */
  PROP_charEpsK,    /* Lennard-Jones characteristic energy */
  PROP_thermAC,                 /* Thermal Accomodation Coefficient */
  PROP_velAC,                   /* Velocity Accomodation Coefficient */
  PROP_abs_coeff,               /* absorption coefficient */
  PROP_scat_coeff,              /* scattering coefficient */
  PROP_scat_phase_func,         /* scattering phase function */
  PROP_Species,                 /* list of species for mixture materials */
  PROP_Reactions,               /* list of reactions */
  PROP_Reaction_Mechs,          /* list of reaction Mechanisms */
  PROP_latent_heat,             /* latent heat */
  PROP_vap_temp,                /* vaporization temperature */
  PROP_boil_temp,               /* boiling point */
  PROP_volatile_frac,           /* volatile fraction */
  PROP_combustible_frac,        /* combustible fraction */
  PROP_binary_diffusivity,      /* binary  diffusivity */
  PROP_diffusivity_reference_pressure, /* reference pressure for binary diffusivity */
  PROP_averaging_coefficient_T, /* temperature averaging coefficient for particle film properties */
  PROP_averaging_coefficient_Y, /* composition averaging coefficient for particle film properties */
  PROP_film_binary_diffusivity, /* film binary diffusivity */
  PROP_averaging_coefficient,   /* film averaging coefficient */
  PROP_vapor_pressure,          /* vapor pressure */
  PROP_liquid_surface_tension,  /* liquid surface tension */
  PROP_non_condensable_gas,     /* non condensable gas */
  PROP_therm_exp_coeff,   /* thermal expansion coefficient */
  PROP_characteristic_vibrational_temperature,     /* characteristic vibrational temperature */
  PROP_premix_heat_trans_coeff, /* laminar heat transfer coefficient */
  PROP_premix_unburnt_density,  /* density of unburnt mixture */
  PROP_premix_unburnt_temp,   /* temperature of unburnt mixture */
  PROP_premix_unburnt_cp,   /* specific heat of unburnt mixture */
  PROP_premix_laminar_speed,    /* laminar flame speed    */
  PROP_premix_laminar_thick,    /* laminar flame thickness */
  PROP_premix_critical_strain,  /* critical rate of strain  */
  PROP_premix_adiabatic_temp,   /* adiabatic temperature  */
  PROP_premix_heat_of_comb,     /* heat of combustion     */
  PROP_premix_unburnt_fuel_mf,  /* unburnt fuel mass fraction */
  PROP_thermophoretic_co, /* thermophoretic diffusion coefficient */
  PROP_emissivity,              /* particle emissivity */
  PROP_scat_factor,             /* particle scattering factor */
  PROP_refractive_index,        /* refractive index */
  PROP_hpyrolysis,              /* heat of pyrolysis */
  PROP_swell_coeff,             /* particle swelling coefficient */
  PROP_burn_stoich,             /* burnout stoichiometry for combusting particle*/
  PROP_hreact,                  /* heat of reaction for burnout */
  PROP_hreact_frac,             /* fraction of hreact given to solid */
  PROP_vaporization,            /* evaporation model */
  PROP_devol,                   /* devolatalization model */
  PROP_combustion,              /* combustion model */
  PROP_thermolysis,             /* thermolysis model */
  PROP_melting_heat,            /* melting heat */
  PROP_tsolidus,                /* solidus temperature */
  PROP_tliqidus,                /* liquidus temperature */
  PROP_tmelt,                   /* melt temperature */
  PROP_liquidus_slope,          /* slope of liquidus line */
  PROP_k_partition,             /* partition coefficient */
  PROP_yeut,                    /* eutecti mass fraction */
  PROP_teut,                    /* eutectic temperature */
  PROP_solut_exp_coeff,         /* solutal expansion coefficient*/
  PROP_diff_solid,              /* diffusivity in solid */
  PROP_porosity,                /* porosity (Vol_void/Vol_bulk) of porous (solid) mat'ls */
  PROP_uds_diff,                /* user defined scalar diffusivity */
  PROP_thermal_diff,    /* thermal diffusion coefficient */
  PROP_dpm_surften,   /* droplet surface tension for spray suite model */
  PROP_diameter,                /* phase diameter */
  PROP_granular_c,              /* granular conductivity */
  PROP_packing,                 /* packing limit */
  PROP_solve_eulerian_max_vof_factor, /* factor * packing limit */
  PROP_static_pileup_repose_angle,   /* repose angle in DDPM static pile-up functionality */
  PROP_virtual_mass_coeff,      /*virtual mass coeff*/
  PROP_drag_func,               /* drag function */
  PROP_drag_fac,                /*drag factor e.g. Brucato re: US 39205*/
  PROP_lift_coeff,              /* lift force coefficient */
  PROP_wall_lubrication_coeff,  /* wall lubrication force coefficient */
  PROP_turbulent_dispersion_force,  /* turbulent dispersion force  */
  PROP_turbulence_interaction,  /* turbulence interaction  */
  PROP_restitution_coeff,       /* restitution coefficient */
  PROP_sfc_tension_coeff,       /* surface tension coefficient */
  PROP_slip_v,                  /* slip velocity */
  PROP_bulk_vis,                /* granular bulk viscosity */
  PROP_friction_vis,            /* frictional viscosity (plastic flow) */
  PROP_friction_angle,          /* angle of internal friction  */
  PROP_granular_t,              /* granular temperature as a property */
  PROP_heat_coeff,              /* heat transfer coeff */
  PROP_slope_limiter,           /* slope limiter for phasaic discretization */
  PROP_visc_disp_factor,        /* interfacial viscous dissipation factor */
  PROP_mass_transfer,              /* heat transfer coeff */
  PROP_elec_conductivity,       /* electric conductivity (isotropic) (1/(ohm m)) */
  PROP_dual_elec_conductivity,  /* electrolyte conductivity (isotropic) (1/(ohm m)) */
  PROP_lithium_diff,            /* lithium diffusivity */
  PROP_mag_permeability,        /* magnetic permeability (H/m) */
  PROP_charge,                  /* electric charge */
  PROP_charge_density,          /* electric charge density (C/m^3) */
  PROP_speed_of_sound,          /* speed of sound m/s */
  PROP_mpg_press,               /* solids pressure */
  PROP_mpg_radial_f,            /* radial distribution function */
  PROP_mpg_elastic_mod,         /* elasticity modulus */
  PROP_mpg_friction_p,          /* frictional pressure */
  PROP_mpg_modulus_fr,          /* frictional modulus */
  PROP_species_phase,           /* condensed species in equilibrium calculation */
  PROP_friction_pack,           /* limit to start frictional viscosity */
  PROP_vp_equilib,              /* vapor liquid equilibrium */
  PROP_metghalchi_keck_fuel,
  PROP_iac_g_rate,              /* iac gowth, coalescence and breakage kernel */
  PROP_iac_coal_kernel,
  PROP_iac_breakage_kernel,
  PROP_iac_nucleation_kernel,
  PROP_iac_surface_tension,
  PROP_iac_min_diameter,
  PROP_iac_max_diameter,
  PROP_iac_dissipation_rate,
  PROP_iac_hydraulic_diam,
  PROP_iac_critical_weber,
  PROP_critical_temperature,
  PROP_critical_pressure,
  PROP_critical_volume,
  PROP_acentric_factor,
  PROP_vapor_press,
  PROP_saturation_temperature,
  PROP_forced_convection_ht_coeff,
  PROP_forced_convection_ht_factor1,
  PROP_forced_convection_ht_factor2,
  PROP_nucleate_boiling_ht_coeff,
  PROP_nucleate_boiling_ht_factor1,
  PROP_nucleate_boiling_ht_factor2,
  PROP_boiling_ref_length,
  PROP_boiling_ref_velocity,
  PROP_boiling_ref_temperature,
  PROP_boiling_superheat_min,
  PROP_boiling_wall_liquid_frac,
  PROP_interfacial_area,
  PROP_bubble_departure_diameter,
  PROP_bubble_departure_frequency,
  PROP_nucleate_site_density,
  PROP_area_influence_coeff,
  PROP_quench_reference_temperature,
  PROP_molar_concentration_henry_coeff,
  PROP_molar_fraction_henry_coeff,
  PROP_molar_concentration_equilibrium_ratio,
  PROP_molar_fraction_equilibrium_ratio,
  PROP_mass_fraction_equilibrium_ratio,
  PROP_continuous_interface_mass_coeff,
  PROP_dispersed_interface_mass_coeff,
  PROP_mass_transfer_coeff,
  PROP_vant_hoff_reference_henry_const,
  PROP_vant_hoff_temperature_dependence,
  PROP_antal_coeff_cw1,
  PROP_antal_coeff_cw2,
  PROP_frank_coeff_cwc,
  PROP_frank_coeff_cwd,
  PROP_frank_coeff_p,
  /* GM */ /* US 114041 */ /* Defining user vars for the AIAD interfacial area model */
  PROP_aiad_ddrop,
  PROP_aiad_cdrop,
  PROP_aiad_lvdrop,
  PROP_aiad_dbubb,
  PROP_aiad_cbubb,
  PROP_aiad_lvbubb,
  PROP_aiad_cddrop,
  PROP_aiad_cdbubb,
  PROP_hydro_diam,
  PROP_hosokawa_coeff,
  PROP_grace_swarm_coeff,   /* US160011 */
  PROP_td_coeff,
  PROP_td_limiting_func,
  PROP_diff_vof_coeff,
  PROP_diff_limiting_func,
  PROP_troshko_hassan_coeff_1,
  PROP_troshko_hassan_coeff_2,
  PROP_sato_bit_coeff,
  PROP_simonin_et_al_coeff,
  PROP_syamlal_mf_vof,
  PROP_syamlal_mf_velocity,
  PROP_heat_coeff_i,
  PROP_heat_coeff_j,
  PROP_saturation_pressure,     /* vapor material saturation pressure used in EWF */
  PROP_relative_viscosity,
  PROP_model_transition,
  PROP_struct_youngs_modulus,   /* structure youngs modulus */
  PROP_struct_ym0,              /* structure youngs modulus in X direction*/
  PROP_struct_ym1,              /* structure youngs modulus in Y direction*/
  PROP_struct_ym2,              /* structure youngs modulus in Z direction*/
  PROP_struct_gxy,              /* structure shear  modulus in XY plane*/
  PROP_struct_gyz,              /* structure shear  modulus in YZ plane*/
  PROP_struct_gxz,              /* structure shear  modulus in XZ plane*/
  PROP_struct_poisson_ratio,    /* structure poisson ratio  */
  PROP_struct_nuxy,              /* structure poisson ratio in XY plane*/
  PROP_struct_nuyz,              /* structure poisson ratio in YZ plane*/
  PROP_struct_nuxz,              /* structure poisson ratio in XZ plane*/
  PROP_struct_start_temperature, /* structure starting temperature  */
  PROP_struct_thermal_expansion, /* structure thermal expansion coefficient  */
  PROP_struct_alpx,              /* structure thermal expansion coefficient in X direction*/
  PROP_struct_alpy,              /* structure thermal expansion coefficient in Y direction*/
  PROP_struct_alpz,              /* structure thermal expansion coefficient in Z direction*/
  PROP_atomic_number,
  PROP_struct_damping_alpha, /* structure damping alpha */
  PROP_struct_damping_beta, /* structure damping beta  */
  /* PSM */ /* Defining variables for the Wet Steam model */
  PROP_ws_rho_liq,
  PROP_ws_ktc_liq,
  PROP_ws_SoS_liq,
  PROP_ws_mu_liq,
  PROP_ws_Cp_liq,
  PROP_ws_S_liq,
  PROP_ws_H_liq,
  PROP_ws_H_vap_sat,
  PROP_Cv,
  PROP_MAX
} Property_ID;

typedef struct property_names_struct
{
  char *label;
  Property_ID prop_id;
} Property_Names;

typedef struct
{
  Property diff;
  Property diff0;
  Property diff1;
  Property diff2;

  real k_matrix[3][3];
} UDS_Diffusivity_Property;

typedef struct
{
  /* US168773 - All the addition of the MP_PROP_MAX indexes for these coefficients of various interfacial forces */
  Property antal_coeff_cw1[MP_PROP_MAX];
  Property antal_coeff_cw2[MP_PROP_MAX];

  Property frank_coeff_cwc[MP_PROP_MAX];
  Property frank_coeff_cwd[MP_PROP_MAX];
  Property frank_coeff_p[MP_PROP_MAX];
  /* GM */ /* US 114041 */ /* Defining user vars for the AIAD interfacial area model */
  Property aiad_ddrop[MP_PROP_MAX];
  Property aiad_cdrop[MP_PROP_MAX];
  Property aiad_lvdrop[MP_PROP_MAX];
  Property aiad_dbubb[MP_PROP_MAX];
  Property aiad_cbubb[MP_PROP_MAX];
  Property aiad_lvbubb[MP_PROP_MAX];
  Property aiad_cddrop[MP_PROP_MAX];
  Property aiad_cdbubb[MP_PROP_MAX];
  Property hydro_diam[MP_PROP_MAX];

  Property hosokawa_coeff[MP_PROP_MAX];

  Property grace_swarm_coeff[MP_PROP_MAX];   /* US160011 & 168773 */

  Property td_coeff[MP_PROP_MAX];
  Property td_limiting_func[MP_PROP_MAX];
  Property diff_vof_coeff[MP_PROP_MAX];
  Property diff_limiting_func[MP_PROP_MAX];

  Property troshko_hassan_coeff_1[MP_PROP_MAX];
  Property troshko_hassan_coeff_2[MP_PROP_MAX];
  Property sato_bit_coeff[MP_PROP_MAX];
  Property simonin_et_al_coeff[MP_PROP_MAX];

  Property syamlal_mf_vof[MP_PROP_MAX];
  Property syamlal_mf_velocity[MP_PROP_MAX];

  Property heat_coeff_i[MP_PROP_MAX];
  Property heat_coeff_j[MP_PROP_MAX];
} MP_Model_Coeff;

extern MP_Model_Coeff mp_model_coeff;

typedef struct material_struct
{
  char name[MATERIAL_NAME_LENGTH];  /* name of material */
  char formula[MATERIAL_NAME_LENGTH]; /* formula of material */

  Matl_Type_ID type;      /* MATERIAL_FLUID,
           * MATERIAL_SOLID etc. */
  /* user-specified properties */
  Property p[PROP_MAX];

  /* for mixture materials */
  struct material_struct **component;
  char **component_name; /* name of material */
  int n_components;
  char mixture_name[MATERIAL_NAME_LENGTH];

  struct material_struct **surface_species;
  char **surface_species_names; /* name of material */
  int surface_n_species;

  struct material_struct **site_species;
  char **site_species_names; /* name of material */
  int site_n_species;

  Property *mass_diffusivity;
  Property *thermal_diffusivity;

  UDS_Diffusivity_Property *uds_diffusivity;
  int n_uds_diffusivity;

  float k_matrix[3][3];
  float struct_matrix[3][3];
  CUEOS_Parameter *CUEOS;

  struct reaction_struct *reaction_list;
  struct reaction_mech_struct *reaction_mech_list;
  float p_values[3][3];

  cxboolean chemkin_inp_file_loaded;
  cxboolean transport_file_loaded;

  struct material_struct *next; /* pointer to next in list */

} Material;


#if !UDF_COMPILER
# define MATERIAL_PROPERTY(m)((m)->p)
# define MATERIAL_PROP(m,prop)(m)->p[prop].constant
#endif
#define MATERIAL_PROP_METHOD(m,prop)(m)->p[prop].method
#define MATERIAL_PROP_UDF_NAME(m,prop)(m)->p[prop].udf_name

#define MATERIAL_PROP_EXPR(m,prop)(m)->p[prop].expr

#define MATERIAL_POLYNOMIAL(m,prop)(m)->p[prop].u.poly
#define MATERIAL_MATRIX(m,prop)(m)->p[prop].u.matrix
#define MATERIAL_MATRIX_ENTRY(m,prop,i,j)(m)->p[prop].u.matrix[i][j]
#define MATERIAL_TABLE_TP(m,prop)(m)->p[prop].u_tables.table_tp
#define MATERIAL_TABLE_SAT(m,prop)(m)->p[prop].u_tables.table_sat
#define MATERIAL_PROP_STRING(m,prop)(m)->p[prop].string

/* these two macros are for backward compatibility; should be phased out */
#define MATERIAL_PROP_COEF(m,prop,coef_indx)\
   POLYNOMIAL_COEFF((m)->p[prop].u.poly,coef_indx)
#define MATERIAL_PROP_NUM_COEF(m,prop)\
     (((m)->p[prop].u.poly==NULL) ? 0 : (m)->p[prop].u.poly->n_coeffs[0])


#define MATERIAL_PROP_POLYNOMIAL(m,prop,x)\
      ((MATERIAL_PROP_METHOD(m,prop)==PROP_METHOD_CONSTANT) ? \
        MATERIAL_PROP(m,prop) : evaluate_polynomial(MATERIAL_POLYNOMIAL(m,prop),x))

#define MATERIAL_PROP_INTEGRAL(m,prop,x0,x1)\
        ((MATERIAL_PROP_METHOD(m,prop)==PROP_METHOD_CONSTANT) ? \
         MATERIAL_PROP(m,prop)*((x1)-(x0)) :\
   evaluate_polynomial_integral(MATERIAL_POLYNOMIAL(m,prop),x0,x1))

#define MATERIAL_PROP_OVER_X_INTEGRAL(m,prop,x0,x1)\
        ((MATERIAL_PROP_METHOD(m,prop)==PROP_METHOD_CONSTANT) ? \
         MATERIAL_PROP(m,prop)*log((x1)/(x0)) :\
   evaluate_polynomial_over_x_integral(MATERIAL_POLYNOMIAL(m,prop),x0,x1))

#define MIXTURE_NCOMPONENTS(m)(m)->n_components
#define MIXTURE_COMPONENT(m,i)m->component[i]
#define MIXTURE_COMPONENT_NAME(m,i)m->component_name[i]

#define MIXTURE_NSPECIES  MIXTURE_NCOMPONENTS
#define MIXTURE_SPECIE    MIXTURE_COMPONENT
#define MIXTURE_SPECIE_NAME MIXTURE_COMPONENT_NAME

#define MIXTURE_SURFACE_NSPECIES(m)(m)->surface_n_species
#define MIXTURE_SURFACE_SPECIE(m,i)(m)->surface_species[i]
#define MIXTURE_SURFACE_SPECIE_NAME(m,i)(m)->surface_species_names[i]

#define MIXTURE_SITE_NSPECIES(m)(m)->site_n_species
#define MIXTURE_SITE_SPECIE(m,i)(m)->site_species[i]
#define MIXTURE_SITE_SPECIE_NAME(m,i)(m)->site_species_names[i]

#define N_SITE_TYPES(rm)(rm)->n_site_types
#define GLOBAL_SITE_SPE_ID(rm,i)(rm)->global_id_site_spe[i]
#define GLOBAL_SITE_SPE_ID_BY_TYPE(rm,i,j)(rm)->global_id_site_spe_t[i][j]
#define SITE_ID(rm,i)(rm)->site_id_of_spe[i]
#define SITE_DENSITY(rm,i)(rm)->site_den[i]

#define MATERIAL_NAME(m)(m)->name
#define MATERIAL_FORMULA(m)(m)->formula
#define MATERIAL_TYPE(m)(m)->type
#define MATERIAL_MIXTURE_NAME(m)(m)->mixture_name

#define MATERIAL_DIFFUSIVITY(m,i)(m)->mass_diffusivity[i]
#define MATERIAL_DIFFUSIVITY_METHOD(m,i)(m)->mass_diffusivity[i].method
#define MATERIAL_DIFFUSIVITY_CONSTANT(m,i)(m)->mass_diffusivity[i].constant
#define MATERIAL_DIFFUSIVITY_POLYNOMIAL(m,i)(m)->mass_diffusivity[i].u.poly
#define MATERIAL_DIFFUSIVITY_UDF_NAME(m,i)(m)->mass_diffusivity[i].udf_name

#define MATERIAL_UDS_DIFFUSIVITY_PROP(m)(m)->uds_diffusivity

#define MATERIAL_UDS_DIFFUSIVITY(m,i) MATERIAL_UDS_DIFFUSIVITY_PROP(m)[i].diff
#define MATERIAL_UDS_DIFFUSIVITY_METHOD(m,i) MATERIAL_UDS_DIFFUSIVITY(m,i).method
#define MATERIAL_UDS_DIFFUSIVITY_CONSTANT(m,i) MATERIAL_UDS_DIFFUSIVITY(m,i).constant
#define MATERIAL_UDS_DIFFUSIVITY_POLYNOMIAL(m,i) MATERIAL_UDS_DIFFUSIVITY(m,i).u.poly
#define MATERIAL_UDS_DIFFUSIVITY_UDF_NAME(m,i) MATERIAL_UDS_DIFFUSIVITY(m,i).udf_name
#define MATERIAL_UDS_DIFFUSIVITY_EXPR(m,i) MATERIAL_UDS_DIFFUSIVITY(m,i).expr

#define MATERIAL_UDS_DIFFUSIVITY_MATRIX(m,i) MATERIAL_UDS_DIFFUSIVITY_PROP(m)[i].k_matrix
#define MATERIAL_UDS_DIFFUSIVITY_D0(m,i) MATERIAL_UDS_DIFFUSIVITY_PROP(m)[i].diff0
#define MATERIAL_UDS_DIFFUSIVITY_D1(m,i) MATERIAL_UDS_DIFFUSIVITY_PROP(m)[i].diff1
#define MATERIAL_UDS_DIFFUSIVITY_D2(m,i) MATERIAL_UDS_DIFFUSIVITY_PROP(m)[i].diff2

#define MATERIAL_THERMAL_DIFFUSIVITY(m,i)(m)->thermal_diffusivity[i]
#define MATERIAL_THERMAL_DIFFUSIVITY_METHOD(m,i)(m)->thermal_diffusivity[i].method
#define MATERIAL_THERMAL_DIFFUSIVITY_CONSTANT(m,i)(m)->thermal_diffusivity[i].constant
#define MATERIAL_THERMAL_DIFFUSIVITY_POLYNOMIAL(m,i)(m)->thermal_diffusivity[i].u.poly
#define MATERIAL_THERMAL_DIFFUSIVITY_UDF_NAME(m,i)(m)->thermal_diffusivity[i].udf_name

#define mixture_component_loop(m,sp,i)\
     for(sp=(m)->component[i=0]; i<m->n_components; sp=(m)->component[++i])
#define mixture_component_loop_i(m,i)\
     for(i=0; i<m->n_components; ++i)
#define bounded_mixture_component_loop(m,sp,i,min_i,max_i)\
     for(sp=(m)->component[i=min_i]; i< max_i; sp=(m)->component[++i])
#define bounded_mixture_component_loop_i(m,i,min_i,max_i)\
     for(i=min_i; i< max_i; ++i)

#define mixture_species_loop    mixture_component_loop
#define mixture_species_loop_i    mixture_component_loop_i
#define bounded_mixture_species_loop  bounded_mixture_component_loop
#define bounded_mixture_species_loop_i  bounded_mixture_component_loop_i

#define mixture_surface_species_loop(m,sp,i)\
     for(sp=(m)->surface_species[i=0]; i<m->surface_n_species; sp=(m)->surface_species[++i])
#define mixture_surface_species_loop_i(m,i)\
     for(i=0; i<m->surface_n_species; ++i)

#define mixture_site_species_loop(m,sp,i)\
     for(sp=(m)->site_species[i=0]; i<m->site_n_species; sp=(m)->site_species[++i])
#define mixture_site_species_loop_i(m,i)\
     for(i=0; i<m->site_n_species; ++i)
/* methods */
/* Indices 0 through 9 are reserved for generic methods (such as constant,
   polynomial, piecewise polynomial, etc.) Specific methods applicable for only
   one property (eg. Sutherland's law for viscosity) should use indices 10 and higher */

enum
{
  /* PROP_METHOD_STRING = -4,   -- may become necessary for a DPM-to-VOF "conversion transcript" option */
  PROP_METHOD_EXPR = -3,
  PROP_METHOD_BOOLEAN = -2,  /* Adding as > 0 causes PROP_METHOD_NONE (below) to conflict with many others defined as = 10..:-| */
  PROP_METHOD_CONSTANT = 0,
  PROP_METHOD_POLYNOMIAL,
  PROP_METHOD_UDF,    /* user defined function */
  PROP_METHOD_REAL_GAS,
  PROP_METHOD_UDF_DPM,    /* user defined properties for particles */
  PROP_METHOD_UDF_PDF_TRAN,     /* UDF for PDF Transport, which couples thru density */
  PROP_METHOD_UDF_MIXING_LAW, /* user defined mixing law */
  PROP_METHOD_UDF_GRAY_BAND_ABS_COEFF,  /* user defined gray band */
  PROP_METHOD_WET_STEAM,
  PROP_METHOD_NONE          /* = 9, must not change or will incur lots of conflicts with other things defined as 10... */
};
#define  PROP_METHOD_REAL_GAS_MIXTURE 100
#define PROP_METHOD_LIQ_SLOPE 10
#define PROP_METHOD_UDF_WSGGM_ABS_COEFF 40
#define PROP_METHOD_TABLE_TP 80
#define PROP_METHOD_TABLE_SAT 81

/* some properties define their own method symbols if they allow methods
   other than the generic ones.  */
#if 0
#define UNIVERSAL_GAS_CONSTANT    8314.34 /* SI units: J/Kmol/K */
#define AVOGADRO_NUMBER          6.022E26 /* SI units: molecules/Kmol */
#define BOLTZMANN_NUMBER          1.3806504e-23
#else
/*Note: The values below are from NIST 2006 and in Sync with Chemkin used value*/
#define AVOGADRO_NUMBER           6.02214179e+26              /* SI units: molecules/Kmol */
#define BOLTZMANN_NUMBER          1.3806504e-23               /* SI units:   [J/K]  */
#define UNIVERSAL_GAS_CONSTANT    8314.47247122               /*(AVOGADRO_NUMBER*BOLTZMANN_NUMBER) SI units: J/Kmol/K */
#endif

/* method for calculating specific heat */
#define CP_MIXTURE                  10
#define CP_KINETIC_THEORY           11
#define CP_REACTION_DESIGN          12
#define CP_BOLTZMANN_THEORY         13

/* method for calculating viscosity */
enum
{
  MU_MIXTURE = 10,
  MU_SUTHERLAND,
  MU_BLOTTNER,
  MU_POWER_LAW,
  MU_KINETIC_THEORY,
  MU_IDEAL_GAS_MIXTURE,
  MU_NON_NEWTONIAN_POWER_LAW,
  MU_CARREAU_MODEL,
  MU_HERSCHEL_BULKLEY,
  MU_CROSS_MODEL,
  MU_SYAMLAL_OBRIEN,
  MU_GIDASPOW,
  MU_FILTERED,
  MU_REACTION_DESIGN,
  MU_PDF
};


/* method for calculating thermal conductivity */

#define KTC_MIXTURE                 10
#define KTC_KINETIC_THEORY          11
#define KTC_IDEAL_GAS_MIXTURE       12
#define KTC_ANISOTROPIC             13
#define KTC_ORTHOTROPIC             14
#define KTC_ORTHOCYLIND             15
#define KTC_BIAXIAL                 16
#define KTC_REACTION_DESIGN         17
#define KTC_ANISO_UDF               18
#define KTC_PA_PV                   19
#define KTC_EUCKEN                  20
#define KTC_PDF                     21


/* method for calculating mass diffusivity */
#define MASS_DIFF_CONSTANT_DILUTE                 10
#define MASS_DIFF_DILUTE                          11
#define MASS_DIFF_MULTICOMP                       12
#define MASS_DIFF_KINETIC_THEORY                  13
#define MASS_DIFF_REACTION_DESIGN                 14
#define MASS_DIFF_UNITY_LE                        15
#define MASS_DIFF_CONSTANT_LE                     16

/* method for calculating thermal diffusion coefficient */
#define THERMAL_DIFF_MIXTURE    10
#define THERMAL_DIFF_KINETIC_THEORY 11
#define THERMAL_DIFF_REACTION_DESIGN  12

/* method for calculating user defined scalar diffusion coefficient */
#define UDS_METHOD                  10
#define UDS_DIFF_ANISOTROPIC        13
#define UDS_DIFF_ORTHOTROPIC        14
#define UDS_DIFF_ORTHOCYLIND        15
#define UDS_DIFF_ANISO_UDF          16

/* method for calculating structural coefficients */
#define STRUCT_YM_ORTHOTROPIC       10
#define STRUCT_NU_ORTHOTROPIC       11
#define STRUCT_TE_ORTHOTROPIC       12

/* method for calculating electric conductivity using mixing law */
#define ELEC_VOL_WEIGHTED_MIXTURE   10

/* method for calculating density */
#define RHO_CONSTANT                PROP_METHOD_CONSTANT
#define RHO_POLYNOMIAL              PROP_METHOD_POLYNOMIAL
#define RHO_EXPR                    PROP_METHOD_EXPR
enum
{
  RHO_BOUSSINESQ = 10,
  RHO_INCOMPRESSIBLE_IDEAL_GAS,
  RHO_IDEAL_GAS,
  RHO_VOL_WEIGHTED_MIXTURE,
  RHO_PDF,
  RHO_PREMIXED_COMBUSTION,
  RHO_AUNGIER_REDLICH_KWONG,
  RHO_REDLICH_KWONG,
  RHO_SOAVE_REDLICH_KWONG,
  RHO_PENG_ROBINSON,
  RHO_CUEOS_END, /* this follows the last cubic equation of state model definition */
  RHO_TAIT,
  RHO_COMPRESSIBLE_VOL_WEIGHTED_MIXTURE
};
#define RHO_CUEOS_START RHO_AUNGIER_REDLICH_KWONG

/* method for calculating absorption coefficient */
#define ABS_COEFF_WSGGM_CELL        10
#define ABS_COEFF_WSGGM_DOMAIN        11
#define ABS_COEFF_WSGGM_USER        12
#define ABS_COEFF_GRAY_BAND                 13

#define PROP_las_coeff PROP_scat_phase_func

/* method for scattering phase function */
#define SCAT_PHASE_FUNC_ISOTROPIC 10
#define SCAT_PHASE_FUNC_LINEAR 11
#define SCAT_PHASE_FUNC_DELTA_EDDINGTON 12

/* devolatalization models */
#define DEVOL_SINGLE_RATE 10
#define DEVOL_TWO_RATES 11
#define DEVOL_CPD 12 /* coal_cpd*/

/* thermophoretic coefficients */
#define THERMO_DIFF_TALBOT 10

/* combustion model */
#define CMB_DIFF_LIMITED 10
#define CMB_DIFF_KINETICS_LIMITED 11
#define CMB_INTRINSIC 12
#define CMB_MULTIPLE 13
#define CMB_CBK 14

/* vaporization and thermolysis model */
#define EVAP_DIFFUSION 10
#define EVAP_CONVECTION_DIFFUSION 11
#define EVAP_THERMOLYSIS 12
#define EVAP_THERMOLYSIS_FILM 13

/* reaction mechanisms */
#define REACT_NONE 10
#define REACT_FINITE 11
#define REACT_FINITE_EDDY_DISS 12
#define REACT_EDDY_DISS 13

#define REACT_MECHANISM 10

/* partially premixed polynomial for laminar flame speed */
#define PREPDF_POLY 10
/* laminar flame speed for Gasoline*/
#define GASOLINE_LAW 11
/* laminar flame speed from chemkin MFL libaray*/
#define CHEMKIN_MFL_LAW 12
#define CHEMKIN_FLA_SL 14
/* mixture fraction based laminar flame thickness */
#define DIFFUSIVITY_OVER_FLAME_SPEED 10

/* method for binary diffusivity for DPM  */
#define DPM_DIFFUSIVITY_FILM 10
#define DPM_DIFFUSIVITY_UNITY_LE 11

/* speciesphase types */
enum
{
  SPECIES_PHASE_TYPE_GAS = 10,
  SPECIES_PHASE_TYPE_LIQUID,
  SPECIES_PHASE_TYPE_SOLID
};

/* multiphase methods and types */
enum
{
  PHASE_TYPE_GAS = 10,
  PHASE_TYPE_LIQUID,
  PHASE_TYPE_SOLID
};

/* for mass transfer & model transition */
enum
{
  PROP_METHOD_CONSTANT_RATE = 10,
  PROP_METHOD_AIAD_ENTRAINMENT_ABSORPTION, /* GM */ /* US114041 */ /* AIAD Entrainment Absortion PROP_METHOD */
  PROP_METHOD_GENTOP_COMPLETE_COALESCENCE, /* GM */ /* US150386 */ /* GENTOP Complete Coalescence PROP_METHOD */
  PROP_METHOD_PB,               /*population balance method*/
  PROP_METHOD_CAVITATION,
  PROP_METHOD_EVAPORATION_CONDENSATION,
  PROP_METHOD_BOILING,
  PROP_METHOD_SPECIES_TRANSFER,
  PROP_METHOD_VOF_TO_DPM,        /* model transition (above are all mass transfer) */
  PROP_METHOD_DPM_TO_VOF         /* model transition (above are all mass transfer) */
};

/* Heterogeneous index function for drag model */
#define HETER_OPTION_EMMS_LU              11
#define HETER_OPTION_FILTERED_SARKAR2016  12

/* methods for calculating drag functions */
#define DRAG_SCHILLER_NAUMANN         11
#define DRAG_MORSI_ALEXANDER          12
#define DRAG_SYAMLAL_OBRIEN           13
#define DRAG_WEN_YU                   14
#define DRAG_GIDASPOW                 15
#define DRAG_SYAMLAL_OBRIEN_SYMMETRIC 16
#define DRAG_SYMMETRIC                17
#define DRAG_UNIVERSAL                18
#define DRAG_ANISOTROPIC              19
#define DRAG_SCHILLER_NAUMANN_PB      20
#define DRAG_WEN_YU_PB                21
#define DRAG_ISHII                    22
/*
#define DRAG_BOILING_ISHII            22
*/
#define DRAG_HUILIN_GIDASPOW          23
#define DRAG_GIBILARO                 24
#define DRAG_GRACE                    25 /*US 39204*/ /*US 160011*/ /* US168773 */
#define DRAG_TOMIYAMA                 26 /*US 39204*/
#define DRAG_SYAMLAL_OBRIEN_PARA      27
#define DRAG_ISHIIZUBER               28 /*US 160011*/
#define DRAG_AIAD                     29 /* GM */ /* US 95649 */ /* Defining Drag variable for AIAD */
#define DRAG_EMMS                     30
#define DRAG_FILTERED                 31
/* US 39205 method for calculating drag factor*/

#define DRAG_FACTOR_BRUCATO           11
#define DRAG_FACTOR_WDE               12

/* methods for calculating lift coefficient */
#define LIFT_MORAGA                   11
#define LIFT_SAFFMAN_MEI              12
#define LIFT_LEGENDRE_MAGNAUDET       13
#define LIFT_TOMIYAMA                 14
#define LIFT_HESSENKEMPER_ET_AL       15
/*
#define LIFT_BOILING_MORAGA           11
#define LIFT_BOILING_TOMIYAMA_ET_AL   12
*/

/* methods for calculating wall lubrication coefficient */
#define WALL_LUBRICATION_ANTAL        11
#define WALL_LUBRICATION_TOMIYAMA     12
#define WALL_LUBRICATION_FRANK        13
#define WALL_LUBRICATION_HOSOKAWA     14
#define WALL_LUBRICATION_LUBCHENKO    15

/* methods for calculating turbulent dispersion force */
#define TD_LOPEZ_DE_BERTODANO         11
#define TD_SIMONIN                    12
#define TD_BURNS_ET_AL                13
#define DIFFUSION_IN_VOF              14

/* methods for calculating turbulent dispersion force */
#define TI_SATO_BIT                   11
#define TI_TROSHKO_HASSAN             12
#define TI_SIMONIN_ET_AL              13

/*methods for calculating slip velocity */
#define SLIP_MANNINEN_ET_AL           11

/*methods for calculating bulk viscosity */
#define B_MU_LUN_ET_AL                10

/*methods for calculating friction viscosity */
#define FRICTION_MU_SCHAEFFER         11
#define FRICTION_MU_JOHNSON           12

/*methods for calculating frictional pressure */
#define FRICTIONAL_PRESSURE_JOHNSON   10
#define FRICTIONAL_PRESSURE_SYAMLAL   11
#define FRICTIONAL_PRESSURE_KTGF      12

/*methods for calculating granular conductivity */
#define GRAN_CONDUCTIVITY_SYAM        10
#define GRAN_CONDUCTIVITY_GIDS        11

/*methods for calculating relative viscosity */
#define REL_VIS_BRINKMAN              10
#define REL_VIS_EINSTEIN              11
#define REL_VIS_BREUGEM               12

/*methods for heat trasfer coefficient */
#define HEAT_COEFF_RANZ_MARSHALL      11
#define HEAT_COEFF_GUNN               12
#define HEAT_COEFF_TOMIYAMA           13
#define HEAT_COEFF_HUGHMARK           14
#define HEAT_COEFF_LAVIEVILLE         15
#define HEAT_COEFF_TWO_RESISTANCE     16
#define HEAT_TRANSFER_COEFFICINET     17
#define HEAT_COEFF_NUSSELT_NUMBER     18
#define HEAT_COEFF_ZERO_RESISTANCE    19
#define HEAT_FIXED_TO_SAT_TEMP        20

/*methods for calculating granular Temperature */
#define GRAN_ALGEBRAIC_SYAM           11

/*methods for calculating solids pressure */
#define GP_LUN_ET_AL                  11
#define GP_SYAMLAL                    12
#define GP_AHMADI                     13
#define GP_FILTERED                   14

/*methods for calculating radial distribution function */
#define G0_LUN_ET_AL                  11
#define G0_AHMADI                     12
#define G0_ARASTAPOUR                 13
#define G0_SYAMLAL                    14
#define G0_FILTERED                   15

/*methods for calculating Elasticity Modulus */
#define DP_DVOF                       11

/*methods for calculationg Frictional Modulus */
#define DP_FRICTION_DVOF              11

/*method for phase diameter when PB is on*/
#define PB_SAUTER_DIA                    10
#define IAC_SAUTER_DIA                   11 /* interfacial area model */
#define NB_SAUTER_DIA                    12 /* boiling model */

/* method for vapor liquid equilibrium */
#define VPE_RAOULT                    10

/* method for interfacial area model */
#define IAC_HI                          11
#define IAC_IK                          12
#define IAC_WIK                         13
#define IAC_FL_KE                       14
#define IAC_YM                          15

/* methods for calculating interfacial */
#define MP_IA_SYMMETRIC          11
#define MP_IA_PARTICLE           12
#define MP_IA_ISHII              13
#define MP_IA_GRADIENT           14
#define MP_IA_AIAD               15 /* GM */ /* US 95649 */ /* Defining Interfacial Area variable for AIAD */
#define MP_IA_GENTOP             16 /* GM */ /* US 150385 */ /* Defining Interfacial Area variable for GENTOP */

/* methods for calculating nucleate site density */
#define BOILING_NUC_LEMMERT_CHAWLA    11
#define BOILING_NUC_KOCAMUSTAFAOGULLARI_ISHII 12

/* methods for calculating bubble departure diameter  */
#define BOILING_BDD_TOLUBINSKI_ET_AL  11
#define BOILING_BDD_UNAL              12
#define BOILING_BDD_KOCAMUSTAFAOGULLARI_ISHII 13

/* methods for calculating bubble departure frequency  */
#define BOILING_BDF_COLE  11

/*methods for calculating area influence coefficient  */
#define BOILING_AIC_DELVALLE_KENNING  11

/*methods for calculating reference temp.for quenching  */
#define BOILING_QUENCH_TEMPERATURE    11

/* methods for calculating forced convection htc */
#define BOILING_QSP_HTC_STANDARD 11
#define BOILING_QSP_HTC_DITTUS_BOELTER_CALIBRATION 12

/* methods for calculating forced convection reynolds factor */
#define BOILING_QSP_FAC1_CHEN 11

/* methods for calculating nucleate boiling htc */
#define BOILING_QNUC_HTC_FORSTER_ZUBER 11

/* methods for flow-induced/sub-cooled boiling ht factor */
#define BOILING_QNUC_FAC1_CHEN_STEINER 11
#define BOILING_QNUC_FAC1_CHEN 12

/* methods for calculating boiling reference velocity  */
#define BOILING_REF_VEL_YSTAR 11

/* methods for calculating boiling reference temperature */
#define BOILING_REF_TEMP_YSTAR 11
#define BOILING_REF_TEMP_BULK 12

/* methods for calculating minimun superheat */
#define BOILING_SUPHT_MIN_HSU 11

/* methods for calculating wall liquid volume fraction */
#define BOILING_WALL_LIQ_FRAC_TRANSITION 11
#define BOILING_WALL_LIQ_FRAC_NEIGHBOR 12

/*methods for calculating limiting func. in TD force  */
#define TD_LIMITING_FUNCTION    11

/* methods for calculating henry coefficient */
#define SPECIES_TRANSFER_HENRY_CONST_VANT_HOFF      11

/* methods for calculating mass-transfer coefficient */
#define SPECIES_TRANSFER_RANZ_MARSHALL      11
#define SPECIES_TRANSFER_HUGHMARK           12
#define SPECIES_TRANSFER_SHERWOOD_NUMBER    13
#define SPECIES_TRANSFER_ZERO_RESISTANCE    14
#define SPECIES_TRANSFER_HIGBIE    15

/* methods for taylor-approxiamtion  */
#define CAVITATION_TAYLOR_APPROXIMATION     11


enum
{
  PROP_METHOD_MASS_WEIGHTED_ARITHMETIC_MIXTURE = 30,
  PROP_METHOD_MASS_WEIGHTED_HARMONIC_MIXTURE,
  PROP_METHOD_REAL_GAS_PENG_ROBINSON
};

enum
{
  PROP_METHOD_DPM_AVERAGE = 50
};

/* methods for calculating critical constants for real gas mixtures */
#define MOLE_WEIGHTED_MIXTURE             10
#define AUNGIER_REDLICH_KWONG_MIXTURE     11

/* methods for calculating vapor saturation pressure used in Eulerian Wall Film  model */
enum
{
  PROP_METHOD_EWF_SAT_PRESSURE_DEFAULT = 10
};

/* methods for calculating saturation temperature used in mass transfer models */
enum
{
  PROP_METHOD_TSAT_TABULATION = 10,
  PROP_METHOD_PT_SAT_TABULAR = 12,  /* 11 has conflict with taylor-approximation */
  PROP_METHOD_PTL_SAT_TABULAR = 13
};

/* methods for vibrational temperature used in two-temperature models */
enum
{
  PROP_METHOD_VIBRATIONAL_MODES = 10
};


/**
 * \brief A struct that holds global parameters for the materials module.
 */
typedef struct material_params_struct
{
  cxboolean blended_table_derivatives; /**< Whether to use blended (true) or raw derivatives (false) for tables */
  real cueos_cp_departure_limit;       /**< Limits by how much real specific heat may depart from ideal value   */
  int property_warnings;               /**< Property warnings verbosity (0:off, 1:per material, 2:per property) */
  int mixture_therm_cond_option;       /**< Therm. cond. mixture averaging (0:Wilkes, 1:arithmetic+harmonic)    */
} Material_Params_Type;
FLUENT_EXPORT extern Material_Params_Type material_params;
FLUENT_EXPORT void Set_Material_Params(void);

FLUENT_EXPORT void Create_Material(const char *name, const char *mix_name, const char *formula, const Matl_Type_ID type, const cxboolean name_and_formula);
FLUENT_EXPORT void Set_Material(Material *m, Pointer y);
FLUENT_EXPORT void Delete_Material(Material *m);
FLUENT_EXPORT void Assign_Species_to_Mixtures(void);
FLUENT_EXPORT void Free_Materials(void);
FLUENT_EXPORT Material *Pick_Material(const char *name, const char *mix_name);
FLUENT_EXPORT Material *Pick_Material_Name_And_Formula(const char *name, const char *mix_name);
FLUENT_EXPORT Matl_Type_ID Material_Type(const char *name);
FLUENT_EXPORT Property_ID  Material_Property_ID(const char *name);
FLUENT_EXPORT int  Property_Method(Property_ID, const char *name);
FLUENT_EXPORT char   *Material_Property_Name(Property_ID );
FLUENT_EXPORT int Material_Multicomponent_Index(Material *m, int i1, int i2);
FLUENT_EXPORT void Set_Saturation_Table_Property(Property *prop, const int i, const Property_ID prop_id, Pointer value);
extern FLUENT_EXPORT int MAX_FLAMELET_SPECIES;

/*************************************************************************
  Reactions
*************************************************************************/

#define REACTION_NAME_LENGTH 32
#define STOICHIOMETRY_LENGTH 128

typedef enum
{
  ECHEM_INPUT_CONSTANT = 0,
  ECHEM_INPUT_POLYNOMIAL,
  ECHEM_INPUT_UDF
} Echem_Input_type;

typedef struct echem_input
{
  Echem_Input_type type;  /* constant, polynomial or udf */
  union
  {
    Polynomial *pl;
    real (*pudf)(int, Thread *);
  } input;
  real xoutval;
} Echem_Pinput;

typedef struct reaction_struct
{
  char name[REACTION_NAME_LENGTH];        /* reaction name */
  char stoichiometry[STOICHIOMETRY_LENGTH]; /* stoichiometry equation */

  int n_reactants;          /* number of reactants */
  Material **mat_reactant;                  /* species materials of reactants */
  int *reactant;                      /* species indices of reactants */
  real *stoich_reactant;                    /* stoichiometric coefficients of reactants */
  real *exp_reactant;                     /* rate exponents of reactants */
  real *eff_reactant;                     /* 3rd body efficiencies of reactants */

  int n_products;         /* number of products */
  Material **mat_product;                   /* species materials of products */
  int *product;                       /* species indices of products */
  real *stoich_product;                     /* stoichiometric coefficients of products */
  real *exp_product;                      /* rate exponents of products */
  real *eff_product;                  /* 3rd body efficiencies of products */

  int n_others;           /* number of other species */
  Material **mat_other;                     /* materials of other species */

  int *other;                       /* species indices of other species */
  real *exp_other;                    /* rate exponents of other species */
  real *eff_other;                    /* 3rd body efficiencies of other species */

  /* Coefficients for Arrhenius rate expression */
  double A;       /* "pre-exponential" factor */
  double logA;
  double b;       /* temperature exponent     */
  double E;       /* activation energy        */
  real Cmin;                            /* minimum concentration for negative reaction order */

  /* Coefficients for turbulent mixing rate (eddy breakup) model */
  real Amix, Bmix;

  /* Coefficients for controlling temperature in two-temperature model */
  real acontrol;

  /* Data for particle surface reaction */
  int diffusion_species;                /* index for diffusion limited species */
  int catalyst_species;                 /* index for catalyst species */
  real C1, eff;                         /* diffusion rate and effectiveness factor */

  /* pressure dependent reaction */
  int press_react;
  int press_type;                       /* Lindeman, Troe, SRI */
  int bath_gas;                         /* mixture or individual species */
  int chem_act_bi_mol;                  /* Chemically Activated Bimolecular Reaction */
  real press_params[8];
  int plog_reaction;
  int nplog;
  double plog_params[4 * MAX_PLOG];
  int plog_npress[MAX_PLOG];

  int use_third_body_efficiencies;
  int surface_reaction;
  int particle_reaction;
  int electro_chem_reaction;

  /* reverse reaction */
  int backward_reaction;
  int rev_arrhenius;
  double rev_A;
  double rev_logA;
  double rev_E;
  double rev_b;

  /* cache sum of exponents for rampant jacobians */
  real sum_exponents;

  int surface_coverage ;
  int num_cov_sp ;
  int *cov_sp_index;
  real *cover_para0;
  real *cover_para1;
  real *cover_para2;

  /* Butler-Volmer parameters */
  int  tafelmethod;
  Echem_Pinput *Palpha_a;
  Echem_Pinput *Palpha_c;
  Echem_Pinput *Pio;
  Echem_Pinput *PEeq;
  real *yi_ref;

  struct reaction_struct *next;   /* next reaction in list */

} Reaction;

FLUENT_EXPORT void Create_Reaction(Pointer l, Material *m);
FLUENT_EXPORT void Free_Reactions(Material *m);
FLUENT_EXPORT void Delete_Reaction(Pointer l, Material *m);
FLUENT_EXPORT void List_Reactions(Material *m);
FLUENT_EXPORT Reaction *Pick_Reaction(const char *name, Material *m);
FLUENT_EXPORT int mixture_specie_index(Material *m, const char *name);

/*************************************************************************
  Reaction Mechanisms
*************************************************************************/

typedef enum
{
  REACT_UNKNOWN = -1,
  REACT_ALL,
  REACT_VOL,
  REACT_SURF,
  REACT_PART,
  REACT_ECHEM,
  REACT_TYPE_MAX
} React_Type_ID;

typedef struct react_type_names_struct
{
  char *label;
  React_Type_ID type_id;
} React_Type_Names;

#define REACTION_MECH_NAME_LENGTH 64
#define MAX_SITE 50
#define NUM_ENV 4
typedef struct reaction_mech_struct
{
  char name[REACTION_MECH_NAME_LENGTH];   /* name of reaction mechanism */

  React_Type_ID    type;                  /* volumetric, wall or particle */
  int      n_site_types;                  /* number of site types */
  int      n_reactions;                   /* number of reactions */
  int      tot_site_spe_mech;             /* number of site species per mech */
  int      *n_site_spe_persite;           /* number of site species per site */
  int      *last_site_spe_id;             /* ID of last site species in each type */
  real     *site_den;                     /* site density */

  char    *site_spe_names[MAX_SITE];      /*site species names */
  real     site_spe_init_cov[MAX_SITE];
  int      site_occupancy[MAX_SITE];

  int      global_id_site_spe[MAX_SITE];  /*global index of site species */
  int      global_id_site_spe_t[MAX_SITE][MAX_SITE];
  /*global index of site species */
  int      site_id_of_spe[MAX_SITE];      /*given global index of site species,
                                                 find the site ID */
#if 0
  Material *mat_site_species[MAX_SPE_EQNS];   /*given global index of site species,
                                                find its Material* */
#endif
  Reaction **reactions;                      /*reactions in this mech. */
  struct  reaction_mech_struct  *next;       /* pointer to next in list */
} Reaction_Mech;

FLUENT_EXPORT void Create_Reaction_Mech(Pointer l, Material *m);
FLUENT_EXPORT void Free_Reaction_Mechs(Material *m);
FLUENT_EXPORT void Delete_Reaction_Mech(Pointer l, Material *m);
FLUENT_EXPORT void List_Reaction_Mechs(Material *m);
FLUENT_EXPORT Reaction_Mech *Pick_Reaction_Mech(const char *name, Material *m);
FLUENT_EXPORT char *Reaction_Mech_Id_to_Name(int id, Material *m);

FLUENT_EXPORT int Mixture_Species_ID(Material *m, const char *name);

FLUENT_EXPORT cxboolean Check_MATERIAL_PARTICLE_MIXTURE_Exists(void);
FLUENT_EXPORT cxboolean Check_Solid_Density_Required(void);
FLUENT_EXPORT cxboolean Check_Vapor_Properties_Required(Material *mixture, Material *vm);

FLUENT_EXPORT cxboolean Is_Material_Incompressible(Material *m);


/* property macros */
#define PROPERTY_STRING(p,prop)(p)[prop].string
#define PROPERTY_BOOLEAN(p,prop)(p)[prop].u.yes_or_no
#define PROPERTY_CONSTANT(p,prop)(p)[prop].constant
#define PROPERTY_METHOD(p,prop)(p)[prop].method
#define PROPERTY_UDF_NAME(p,prop)(p)[prop].udf_name
#define PROPERTY_POLYNOMIAL(p,prop)(p)[prop].u.poly
#define PROPERTY_EXPR_ARRAY(p,prop)(p)[prop].expr
#define PROPERTY_TABLE_TP(p,prop)(p)[prop].u_tables.table_tp
#define PROPERTY_TABLE_SAT(p,prop)(p)[prop].u_tables.table_sat

#define DOMAIN_PROP_CONSTANT(d,id)PROPERTY_CONSTANT(DOMAIN_PROPERTY(d),id)
#define DOMAIN_PROP_METHOD(d,id)    ((d)->property[id].method)
#define DOMAIN_PROP_UDF_NAME(d,id)  ((d)->property[id].udf_name)
#define DOMAIN_PROP_POLYNOMIAL(d,id)((d)->property[id].u.poly)

/* before R19.0 is #define COMPLEX_PROP_INDEX(i,j)((i)+(j)*((j)+1)/2) */
#define COMPLEX_PROP_INDEX(i,j)((i<j)? (i)+(j)*((j)+1)/2 : (j)+(i)*((i)+1)/2)
#define DOMAIN_COMPLEX_PROP_PROPERTY(d,id,i,j)(DOMAIN_COMPLEX_PROPERTY(d,id)+COMPLEX_PROP_INDEX(i,j))
#define DOMAIN_COMPLEX_PROP_CONSTANT(d,id,i,j)PROPERTY_CONSTANT(DOMAIN_COMPLEX_PROPERTY(d,id),COMPLEX_PROP_INDEX(i,j))

#endif /* _FLUENT_MATERIALS_H */
