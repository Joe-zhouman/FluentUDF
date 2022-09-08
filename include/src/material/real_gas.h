/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/**
 * \brief A struct holding real gas material information.
 */
typedef struct RGAS_Material_Info_struct
{
  char short_name[MATERIAL_NAME_LENGTH]; /**< Short material name */
  char full_name[PROP_UDF_NAME_LENGTH];  /**< Long material name */
  char cas_number[MATERIAL_NAME_LENGTH]; /**< Chemical Abstracts Service (CAS) registry number */
  char eos_type[MATERIAL_NAME_LENGTH];   /**< Equation of state model */
  char description[256];            /**< Description or citation of source */
  double molecular_mass;            /**< Molecular mass */
  double critical_temperature;      /**< Critical temperature [K] */
  double critical_pressure;         /**< Critical pressure [Pa] */
  double critical_density;          /**< Critical density [kg/m3] */
  double eos_minimum_temperature;   /**< EOS range of applicability */
  double eos_maximum_temperature;   /**< EOS range of applicability */
  double eos_maximum_density;       /**< EOS range of applicability */
  double eos_maximum_pressure;      /**< EOS range of applicability */
  double tcond_minimum_temperature; /**< Thermal conductivity range of applicability */
  double tcond_maximum_temperature; /**< Thermal conductivity range of applicability */
  double tcond_maximum_density;     /**< Thermal conductivity range of applicability */
  double tcond_maximum_pressure;    /**< Thermal conductivity range of applicability */
  double visc_minimum_temperature;  /**< Viscosity range of applicability */
  double visc_maximum_temperature;  /**< Viscosity range of applicability */
  double visc_maximum_density;      /**< Viscosity range of applicability */
  double visc_maximum_pressure;     /**< Viscosity range of applicability */
} RGAS_Material_Info;

/* This has to agree with udf.h. */
typedef struct RGAS_Function_struct
{
  void (*initialize)(Domain *, cxboolean vapor_phase, char *,
                     int (*)(const char *, ...),
                     void (*)(const char *, ...) );
  double (*density)(cell_t, Thread *, cxboolean vapor_phase, double, double, double *);
  double (*enthalpy)(cell_t, Thread *, double, double, double, double *);
  double (*entropy)(cell_t, Thread *, double, double, double, double *);
  double (*specific_heat)(cell_t, Thread *, double, double, double, double *);
  double (*molecular_weight)(double *);
  double (*speed_of_sound)(cell_t, Thread *, double, double, double, double *);
  double (*viscosity)(cell_t, Thread *, double, double, double, double *);
  double (*thermal_conductivity)(cell_t, Thread *, double, double, double, double *);
  double (*rho_t)(cell_t, Thread *, double, double, double, double *);
  double (*rho_p)(cell_t, Thread *, double, double, double, double *);
  double (*enthalpy_t)(cell_t, Thread *, double, double, double, double *);
  double (*enthalpy_p)(cell_t, Thread *, double, double, double, double *);
  double (*total_enthalpy)(cell_t, Thread *, double, double, double, double *, double *);
  void   (*flash)(double, double, double *, double *, double *, double *);
  void   (*sat)(double, double *, int, double *);
  void   (*mass_mole_fractions)(int, double *, double *);
  void   (*set_error_handling)(const cxboolean silent);
  int    (*get_error)(void);
  int    (*get_non_fatal_error_count)(void);
  const RGAS_Material_Info *rgas_info; /**< Read-only pointer to material information */
}
RGAS_Functions;

#define RGAS_METHOD(r,m)(r->m)

/* exported from the DLL */
extern UDF_EXPORT RGAS_Functions *real_gas_fcns;

FLUENT_EXPORT void Open_UDRG_Library(const char *name);
FLUENT_EXPORT void Open_RGAS_Library(const char *name);
FLUENT_EXPORT void Set_Real_Gas_Material(Domain *, Material *, const char *);
FLUENT_EXPORT const char *Set_Real_Gas_Material_New(Domain *domain, Material *material);
FLUENT_EXPORT void Real_Gas_Stagnation_Condition(Material *m, cell_t c, Thread *t, real yi[],
                                                 real *Tt, real *pt, real  V2, real *Ht,
                                                 real *Ts, real *ps, real *rs, real *Hs,
                                                 int compute_static);
FLUENT_EXPORT void Real_Gas_Stagnation_Condition_Nonpremixed(Material *m, cell_t c, Thread *t,
                                                             real fmean, real fvar, real fmean2, real fvar2,
                                                             real cmean, real scadis, real y_in,
                                                             real *Tt, real *pt, real  V2, real *Ht,
                                                             real *Ts, real *ps, real *rs, real *Hs,
                                                             int compute_static);
FLUENT_EXPORT void Real_Gas_Isentropic_pi(Material *m, cell_t c, Thread *t, real, real, real *, real *,
                                          real *, real *, real *, real *, int *, real *);
FLUENT_EXPORT void Real_Gas_Isentropic_pi_Nonpremixed(Material *m, cell_t c, Thread *t, real T0, real p0, real *,
                                                      real fmean, real fvar, real fmean2, real fvar2,
                                                      real cmean, real scadis, real y_in,
                                                      real *T, real *p, real *r, real *H, int *isupr, real *a);
FLUENT_EXPORT void Real_Gas_Isentropic_po_Nonpremixed_Backflow(Material *m, cell_t c, Thread *t, real T0,
                                                               real p0, real fmean, real fvar, real fmean2, real fvar2,
                                                               real cmean, real scadis, real y_in,
                                                               real *Ts, real *ps, real *rs, real *Ht);
FLUENT_EXPORT void Real_Gas_Isentropic_po_Backflow(Material *m, cell_t c, Thread *t, real T0, real p0, real yi_arg[],
                                                   real *Ts, real *ps, real *rs, real *Ht);

/* FLUENT_EXPORT Pointer lgetrealgasmolecularweights(void); */

FLUENT_EXPORT Pointer lgetrgasfluiddatafilelist(Pointer x);
FLUENT_EXPORT Pointer lgetrgasstaticinformation(Pointer x);
