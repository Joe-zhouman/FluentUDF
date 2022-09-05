/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

FLUENT_EXPORT real CUEOS_Density(Material *m, real T, real p, real yi[], cxboolean forcegas);
FLUENT_EXPORT real CUEOS_Speed_of_Sound(Material *m, real T, real r, real p, real yi[])  ;
FLUENT_EXPORT real CUEOS_Departure_Specific_Heat(Material *m, real T, real  r,  real p, real xi[], real mwm)  ;
FLUENT_EXPORT real CUEOS_Departure_Enthalpy(cxboolean init, Material *m, real T, real r, real p, real xi[], real mwm)  ;
FLUENT_EXPORT real CUEOS_Entropy(Material *m, real T, real p, real r, real yi[])  ;
FLUENT_EXPORT real CUEOS_Viscosity(Material *m, real T, real yi[])  ;
FLUENT_EXPORT real CUEOS_Thermal_Conductivity(Material *m, real T, real yi[])  ;

FLUENT_EXPORT real CUEOS_Rho_T(Material *m, real T, real r, real yi[])  ;
FLUENT_EXPORT real CUEOS_Rho_P(Material *m, real T, real r, real yi[])  ;
FLUENT_EXPORT real CUEOS_Enthalpy_T(Material *m, real T, real r, real yi[])  ;
FLUENT_EXPORT real CUEOS_Enthalpy_P(Material *m, real T, real r, real yi[])  ;

FLUENT_EXPORT real CUEOS_Tlimit(cxboolean init, Material *m, real temp, real density, real xi[], real mwm);
FLUENT_EXPORT real get_critical_property(Material *m, real xi[], real mwm, int PROP, cxboolean get_from_structure);
FLUENT_EXPORT real getnrk(Material *m, real omega);
FLUENT_EXPORT real generic_mole_fraction_average(Material *m, int PROP, real xi[]);
#define DEN_SMLL 1.E-5
