/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DPM_LAWS_H
#define _FLUENT_DPM_LAWS_H

#include "global.h"
#include "dpm_types.h"

/*************************************************************
 * @addtogroup dpmaccel Acceleration / Drag
 * @{
 *************************************************************/

FLUENT_EXPORT void Saffman_lift(real *, Tracked_Particle *, int );
FLUENT_EXPORT real DiskDragCoeff(real RE);
FLUENT_EXPORT real SphereDragCoeff(real Re);
FLUENT_EXPORT real ShapeDragCoeff(real Re, real shape_factor);
FLUENT_EXPORT real StokesDragCoeff(Tracked_Particle *tp);
FLUENT_EXPORT real CompressibleDragCoeff(Tracked_Particle *tp);
FLUENT_EXPORT real SpraySuiteDynamicDrag_Madabhushi(Tracked_Particle *tp);
FLUENT_EXPORT real SpraySuiteDynamicDragCoeff(Tracked_Particle *tp);
FLUENT_EXPORT real DragCoeff(Tracked_Particle *tp);
FLUENT_EXPORT real FrictDragCoeff(Tracked_Particle *tp, real);
FLUENT_EXPORT real SyamlalOBrienDragCoeff(Tracked_Particle *tp);
FLUENT_EXPORT real WenYuDragCoeff(Tracked_Particle *tp);
FLUENT_EXPORT real GidaspowDragCoeff(Tracked_Particle *tp);
FLUENT_EXPORT real HuilinGidaspowDragCoeff(Tracked_Particle *tp);
FLUENT_EXPORT real GibilaroDragCoeff(Tracked_Particle *tp);
FLUENT_EXPORT real EMMSDragCoeff(Tracked_Particle *tp);
FLUENT_EXPORT real FilteredDragCoeff(Tracked_Particle *tp);
FLUENT_EXPORT real IshiiZuberCoeff(Tracked_Particle *tp);
FLUENT_EXPORT real GraceCoeff(Tracked_Particle *tp);
FLUENT_EXPORT real DragCoeffRot(Tracked_Particle *tp);
FLUENT_EXPORT void Calculate_V_prime(Tracked_Particle *tp, cxboolean *check_time, cxboolean caller_will_obey_check_time);
FLUENT_EXPORT void ParticleAcceleration (Tracked_Particle *, real[], real[], real *, real *, cxboolean);
FLUENT_EXPORT void ParticleAngularAcceleration(Tracked_Particle *, real[], real *);
FLUENT_EXPORT real Particle_Heat_Coeff(Tracked_Particle *tp, Htc_Corr model_index, cxboolean use_newest_diam_p);
FLUENT_EXPORT real DPM_binary_diffusivity(Tracked_Particle *tp, Material *m, real T);
FLUENT_EXPORT real Get_Particle_Strength(Tracked_Particle *tp);
/* number of physical particles in a parcel */
FLUENT_EXPORT real Number_Particles(Tracked_Particle *tp);
/* number of physical particles weighted by current  particle residence time */
FLUENT_EXPORT real Number_Particles_Weighted(Tracked_Particle *tp);
FLUENT_EXPORT void Magnus_lift(real [], Tracked_Particle *, int);
FLUENT_EXPORT real RLCoeff(Tracked_Particle *, real, real);
FLUENT_EXPORT void DPM_Surface_Vapor_X_to_Y(Tracked_Particle *tp, real *x_surf, real *y_surf);
FLUENT_EXPORT void DPM_Fill_Averaged_Properties(Tracked_Particle *tp);
/* @} */

/*************************************************************
 * @addtogroup dpmprop Properties
 * @{
 *************************************************************/
/* options for particle enthalpy calculation */
#define ENTHALPY_SENS 0
#define ENTHALPY_TOT 1
#define ENTHALPY_SOURCES 2

#define DPM_AVERAGING_COEFFICIENT_T(tp,m)         \
  (MATERIAL_PROP_METHOD(m, PROP_averaging_coefficient_T) == PROP_METHOD_NONE) ? 1 : \
  DPM_generic_property(tp,m,PROP_averaging_coefficient_T,TP_T(tp))
#define DPM_AVERAGING_COEFFICIENT_Y(tp,m)         \
  (MATERIAL_PROP_METHOD(m, PROP_averaging_coefficient_Y) == PROP_METHOD_NONE) ? 1 : \
  DPM_generic_property(tp,m,PROP_averaging_coefficient_Y,TP_T(tp))
#define DPM_SWELLING_COEFF(tp)\
     DPM_generic_property(tp,TP_MATERIAL(tp),PROP_swell_coeff,TP_T(tp))
#define DPM_EMISSIVITY(tp,m)\
     DPM_generic_property(tp,m,PROP_emissivity,TP_T(tp))
#define DPM_VAPOR_PRESSURE(tp,m,T)\
     DPM_generic_property(tp,m,PROP_vapor_pressure,T)
#define DPM_EVAPORATION_TEMPERATURE(tp,m)\
     DPM_generic_property(tp,m,PROP_vap_temp,TP_T(tp))
#define DPM_VAPOR_TEMP(tp,m)\
     DPM_generic_property(tp,m,PROP_vap_temp,TP_T(tp)) /* duplicate entry is retained for old UDF compatibility */
#define DPM_BOILING_TEMPERATURE(tp,m)\
     DPM_generic_property(tp,m,PROP_boil_temp,TP_T(tp))
#define DPM_LATENT_HEAT(tp,m)\
    DPM_generic_property(tp,m,PROP_latent_heat,TP_T(tp))

#define TP_HEAT_OF_PYROLYSIS(tp)\
    MATERIAL_PROP(TP_MATERIAL(tp),PROP_hpyrolysis)
#define TP_HEAT_OF_REACTION(tp)\
    MATERIAL_PROP(TP_MATERIAL(tp),PROP_hreact)
#define TP_VOLATILE_FRACTION(tp)\
    MATERIAL_PROP(TP_MATERIAL(tp),PROP_volatile_frac)
#define TP_CHAR_FRACTION(tp)\
    MATERIAL_PROP(TP_MATERIAL(tp),PROP_combustible_frac)

#define PP_HEAT_OF_PYROLYSIS(pp)\
    MATERIAL_PROP(PP_MATERIAL(pp),PROP_hpyrolysis)
#define PP_HEAT_OF_REACTION(pp)\
    MATERIAL_PROP(PP_MATERIAL(pp),PROP_hreact)
#define PP_VOLATILE_FRACTION(pp)\
    MATERIAL_PROP(PP_MATERIAL(pp),PROP_volatile_frac)
#define PP_CHAR_FRACTION(pp)\
    MATERIAL_PROP(PP_MATERIAL(pp),PROP_combustible_frac)

#if HAVE_OLD_P_MACROS
#define DPM_HEAT_OF_PYROLYSIS(tp)\
    MATERIAL_PROP(P_MATERIAL(tp),PROP_hpyrolysis)
#define DPM_HEAT_OF_REACTION(tp)\
    MATERIAL_PROP(P_MATERIAL(tp),PROP_hreact)
#define DPM_VOLATILE_FRACTION(tp)\
    MATERIAL_PROP(P_MATERIAL(tp),PROP_volatile_frac)
#define DPM_CHAR_FRACTION(tp)\
    MATERIAL_PROP(P_MATERIAL(tp),PROP_combustible_frac)
#endif

#define DPM_SPECIFIC_HEAT(tp,T)\
    DPM_Specific_Heat(tp,TP_MATERIAL(tp),T)
#define DPM_LIQUID_SPECIFIC_HEAT(tp,T)\
    DPM_Specific_Heat(tp,TP_WET_COMB_MATERIAL(tp),T)
#define DPM_DIFFUSION_COEFF(tp,T)\
    DPM_Binary_Diffusivity(tp, TP_MATERIAL(tp),T)
#define DPM_SCATT_FACTOR(tp,m)\
     DPM_generic_property(tp,m,PROP_scat_factor,TP_T(tp))
#define DPM_MU(tp)\
     DPM_Liquid_Property(tp,PROP_mu,TP_T(tp))
#define DPM_RHO(tp,m,T)\
     DPM_Density(tp,m,T)
#define DPM_SURFTEN(tp)\
      DPM_Liquid_Property(tp,PROP_dpm_surften,TP_T(tp))
#define DPM_KTC(tp)\
     DPM_generic_property(tp,TP_MATERIAL(tp),PROP_ktc,TP_T(tp))
#define DPM_ELEC_COND(tp)\
     DPM_generic_property(tp,TP_MATERIAL(tp),PROP_elec_conductivity,TP_T(tp))
#define DPM_MAGN_PERM(tp)\
     DPM_generic_property(tp,TP_MATERIAL(tp),PROP_mag_permeability,TP_T(tp))
#define DPM_CHARGE_DENSITY(tp)\
     DPM_generic_property(tp,TP_MATERIAL(tp),PROP_charge_density,TP_T(tp))
#define DPM_BINARY_DIFFUSIVITY(tp, m, T) \
     DPM_Binary_Diffusivity(tp, m, T)
#define DPM_vapor_pressure(tp, m, T)\
     DPM_generic_property(tp,m,PROP_vapor_pressure,T) /* is retained for old UDF compatibility */

#define PR_NUMBER(cp,mu,k) ((cp)*(mu)/(k))
#define LA_NUMBER(rho, sigma, dp, mu) ((rho)*(sigma) *(dp)/MAX(DPM_SMALL,(mu * mu)))
#define NU_NUMBER_RANZ_MARSHALL(Re,Pr) (2. + 0.6*sqrt(Re)*pow(Pr,1./3.))
#define PE_NUMBER(u,rho,cp,len,k) ((u)*(rho)*(cp)*(len)/(k))

FLUENT_EXPORT cxboolean wall_wet_p(face_t f, Thread *t, Tracked_Particle *tp, real *eff_fh);
#if 0
FLUENT_EXPORT cxboolean wall_cold_p(face_t f, Thread *t, Tracked_Particle *tp, real *T_star);
#endif
FLUENT_EXPORT void tracked_particle_re_we(Tracked_Particle *tp, real *);
FLUENT_EXPORT void set_current_law_index(Tracked_Particle *tp);
FLUENT_EXPORT void DPM_Averaged_Properties(Tracked_Particle *tp, real T, real *y_surf);
FLUENT_EXPORT void DPM_Surface_Vapor_Y(Tracked_Particle *tp, real T, real *y_surf);
FLUENT_EXPORT real DPM_generic_property(Tracked_Particle *, Material *, Property_ID, real T);
FLUENT_EXPORT real DPM_Density( Tracked_Particle *tp, Material *m, real T);
FLUENT_EXPORT real DPM_Get_Density( Tracked_Particle *tp, real T);
FLUENT_EXPORT real DPM_Specific_Heat(Tracked_Particle *tp, Material *m, real T);
FLUENT_EXPORT real DPM_Specific_Heat_Integral(Tracked_Particle *tp, Material *m, real T0, real T1);
FLUENT_EXPORT real DPM_Get_Specific_Heat(Tracked_Particle *tp, real T);
FLUENT_EXPORT void UpdateTemperature(Tracked_Particle *tp, real hsource, real mp, real Ft);
FLUENT_EXPORT real Get_Lmf_From_Injection(Particle *);
FLUENT_EXPORT real Thermophoretic_Diff(Tracked_Particle *);
FLUENT_EXPORT real Get_Lmf(Tracked_Particle *tp, real mass_ratio, real init_lmf);
FLUENT_EXPORT real lf_to_lmf(Tracked_Particle *tp, real lf);
FLUENT_EXPORT real get_molecular_weight_bulk_non_evaporating_species(Tracked_Particle *tp);
FLUENT_EXPORT void Solid_Species_Mass_Fractions(Tracked_Particle *tp, real *sf, real *char_mass);
FLUENT_EXPORT real Solid_Species_Enthalpy(Tracked_Particle *tp, real T, real y[], real p_mass, cxboolean);
FLUENT_EXPORT real Solid_Species_Specific_Heat(Tracked_Particle *tp, real T);
FLUENT_EXPORT real Solid_Species_Density(Tracked_Particle *tp, real T);
FLUENT_EXPORT real Particle_Enthalpy(Tracked_Particle *tp, real T, real vf, real cf, real lmf, real ys[], real p_mass, int calc_type);
FLUENT_EXPORT real Particle_Enthalpy_Of_State(Tracked_Particle *tp, cxboolean init_state, int calc_type);
FLUENT_EXPORT real DPM_Binary_Diffusivity( Tracked_Particle *tp, Material *m, real T);
FLUENT_EXPORT real Get_Initial_Dry_Mass_And_Diameter(Tracked_Particle *tp, real *dry_diam);
FLUENT_EXPORT void set_TrackedParticle_fractions( Tracked_Particle *tp );
FLUENT_EXPORT void Particle_Volatile_Char_Fractions(Tracked_Particle *tp, real mass_ratio, real lmf, real *vf, real *cf);
FLUENT_EXPORT real Particle_Material_Enthalpy(Tracked_Particle *tp, Material *, real T);
FLUENT_EXPORT void update_particle_density_and_mass(Particle *p);
FLUENT_EXPORT void init_pvar_and_density_p_list(Particle *start);
FLUENT_EXPORT void update_density_p_list(Particle *start);
FLUENT_EXPORT void multicomponent_vaporization_enthalpy( Tracked_Particle *tp);
FLUENT_EXPORT real DPM_Liquid_Property(Tracked_Particle *tp, Property_ID prop, real T);
FLUENT_EXPORT real DPM_Min_Property(Tracked_Particle *tp, Material *m, Property_ID prop);
FLUENT_EXPORT real DPM_Max_Property(Tracked_Particle *tp, Material *m, Property_ID prop);
FLUENT_EXPORT real DPM_Boiling_Temperature(Tracked_Particle *tp, Material *m);
FLUENT_EXPORT real DPM_saturation_temperature(Tracked_Particle *tp, real absp, Material *m, cxboolean *ifail);
FLUENT_EXPORT real DPM_Latent_Heat(Tracked_Particle *tp, Material *m, real T, int i);
FLUENT_EXPORT void Get_Weber_Impact(Tracked_Particle *tp, int dim, real f_normal[], face_t f, Thread *t);
FLUENT_EXPORT cxboolean Check_DPM_Wall_Heat_Exchange(Domain *domain);
FLUENT_EXPORT cxboolean Check_DPM_Wall_Film_Stripping(Domain *domain);
FLUENT_EXPORT void Init_Condensation(Injection *I);
FLUENT_EXPORT cxboolean DPM_condensation_condition(face_t f, Thread *tf, Injection *I);
FLUENT_EXPORT real DPM_generic_film_particle_property(Particle *p, Material *m, Property_ID prop, real T);
/* @} */

/*************************************************************
 * DPM Laws
 *************************************************************/
FLUENT_EXPORT void InertHeatingLaw(Tracked_Particle *tp);
FLUENT_EXPORT void VaporizationLaw(Tracked_Particle *tp);
FLUENT_EXPORT void BoilingLaw(Tracked_Particle *tp);
FLUENT_EXPORT void DevolatilizationLaw(Tracked_Particle *tp);
FLUENT_EXPORT void SurfaceCombustionLaw(Tracked_Particle *tp);
FLUENT_EXPORT void MulticomponentLaw( Tracked_Particle *tp);
FLUENT_EXPORT void HeatMassUpdate (Tracked_Particle *, int);
FLUENT_EXPORT void AddSources(Tracked_Particle *tp);
FLUENT_EXPORT void AddPICSources(Tracked_Particle *tp);
FLUENT_EXPORT void ReflectUpdateTemperature(Tracked_Particle *tp, face_t face, Thread *t);
/* Parts of AddSources that are used elsewhere: */
FLUENT_EXPORT void Advance_tp_State(Tracked_Particle *tp);
FLUENT_EXPORT void Zero_out_a_dpms_struct(Tracked_Particle *tp, dpms_t *S);

FLUENT_EXPORT real
zbrent_pr_rate(real (*func)(real, real [], int [], cxboolean [], char *),
               real ruser[], int iuser[], cxboolean buser[], char *cuser,
               real x1, real x2, real tol, cxboolean *ifail);
FLUENT_EXPORT cxboolean check_unique_mc_species( Injection *I );

/*************************************************************
 * Cloud Model
 *************************************************************/

#define OBJ char*

typedef struct listStruct
{
  struct element *first;
  struct element *last;
  struct element *current;
  int             size;
}
DPM_List;

typedef struct element
{
  struct element *prev;
  struct element *next;
  OBJ             t;
  cell_t          c;
  real            pdf;
}
DPM_Element;

FLUENT_EXPORT void Free_Cloud_List(DPM_List **list);
FLUENT_EXPORT void FillCloud(Tracked_Particle *tp);
FLUENT_EXPORT void Find_Cloud_Wall_Faces(Tracked_Particle *tp, DPM_List *q);
FLUENT_EXPORT void DPM_List_Add(DPM_List *list, OBJ t, cell_t c);
FLUENT_EXPORT void DPM_List_Reset(DPM_List **list);
FLUENT_EXPORT OBJ  DPM_List_Next(DPM_List *list);
FLUENT_EXPORT void DPM_List_Rewind(DPM_List *list);
FLUENT_EXPORT void DPM_Free_All_Elements(void);
FLUENT_EXPORT void FillCloud(Tracked_Particle *);
FLUENT_EXPORT void Update_Cloud_Weights(Tracked_Particle *);
FLUENT_EXPORT void Find_Cloud_Wall_Cells(Tracked_Particle *);
FLUENT_EXPORT void GetVariance(Tracked_Particle *);

FLUENT_EXPORT void EnsembleAverage(real pos[], cell_t cell, Thread *tcell, cphase_state_t *cphase,
                                   DPM_List *q, Domain *dpm_phase_domain);

#endif
