/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_WETSTEAM_H_
#define _FLUENT_WETSTEAM_H_

/*Mass fraction of liquid-phase (betta) */
#define C_WSB(c,t)    C_STORAGE_R(c,t,SV_WSB)
#define C_WSB_AP(c,t) C_STORAGE_R(c,t,SV_WSB_AP)
#define C_WSB_S(c,t)  C_STORAGE_R(c,t,SV_WSB_S)
#define C_WSB_EG(c,t) C_STORAGE_R(c,t,SV_WSB_RG)

/*Number of droplets per unit mass (etta_s) */
#define C_WSN(c,t)    C_STORAGE_R(c,t,SV_WSN)
#define C_WSN_AP(c,t) C_STORAGE_R(c,t,SV_WSN_AP)
#define C_WSN_S(c,t)  C_STORAGE_R(c,t,SV_WSN_S)
#define C_WSN_EG(c,t) C_STORAGE_R(c,t,SV_WSN_RG)

/*vapor density (rho_v) */
#define C_WSR(c,t)    C_STORAGE_R(c,t,SV_WSR)
#define C_WSR_AP(c,t) C_STORAGE_R(c,t,SV_WSR_AP)
#define C_WSR_S(c,t)  C_STORAGE_R(c,t,SV_WSR_S)
#define C_WSR_EG(c,t) C_STORAGE_R(c,t,SV_WSR_RG)


#define F_WSB(e,t)  C_WSB(e,t)
#define F_WSN(e,t)  C_WSN(e,t)
#define F_WSR(e,t)  C_WSR(e,t)

#define C_WSB_BOUNDED(c,t) C_WSB(c,t)
/* Template for further development */
/*#define C_WSB_BOUNDED(c,t) MAX(MIN(C_WSB(c,t),ws_b_max),ws_b_min)*/

/* Local variable: number of droplet per unit volume */
#define C_WSN_PER_VOL(c,t) MAX(ws_etta_min, C_WSN(c,t)*C_R(c,t)*ws_etta_scale)

/*relative humidity*/
#define F_RHUM(f,t)    F_STORAGE_R(f,t,SV_REL_HUMD)


/* mass gen & nucleation rates*/
#define Mas_Gen(c,t)  C_STORAGE_R(c,t,SV_MAS_GEN)
#define Nuc_Rat(c,t)  C_STORAGE_R(c,t,SV_NUCL_RATE)


#define Flx_Bal(c,t)  C_STORAGE_R(c,t,SV_FLX_BAL)

/* lower limit for the solver variable: liquid mass fraction */
#define ws_b_min 0.0
/* lower limit for the solver variable: number of droplet per unit mass */
#define ws_e_min 0.0
/* lower limit for the local variable: number of droplet per unit volume */
#define ws_etta_min 1.0

extern FLUENT_EXPORT real ws_Tref ; /*Reference Temp.*/
extern FLUENT_EXPORT real ws_Tc  ;  /*Critical Temp.*/
extern FLUENT_EXPORT real ws_Pc  ;  /*Critical Pressure*/
extern FLUENT_EXPORT real ws_Tp  ;
extern FLUENT_EXPORT real ws_a   ;

extern FLUENT_EXPORT real ws_qc  ;  /*condensation coeff  */
extern FLUENT_EXPORT real ws_qe  ;  /*evaporation  coeff  */

extern FLUENT_EXPORT real ws_gama_g ; /* specific heat ratio */
extern FLUENT_EXPORT real ws_K_bolt ; /*Boltzmann constant  */

extern FLUENT_EXPORT real ws_b_max  ; /* limit max liquid mass fraction */

extern FLUENT_EXPORT real mw_f      ; /* liquid droplet fluid Molecular weight*/

extern FLUENT_EXPORT real Rgas_a    ; /* for dry air*/
extern FLUENT_EXPORT real Rgas_v    ; /* for vapor  */
extern FLUENT_EXPORT real Rgas_g    ; /* for gaseous mixture of air + vapor */
extern FLUENT_EXPORT real ws_tinit  ; /* used it for initialization..
                             value will be set in
           Get_Thread_Derived_Variables*/
extern FLUENT_EXPORT real ws_etta_scale; /* scaling factor for the droplet number equation */

typedef enum
{
  NO_CLIP = 0,
  CLIP_HARD,
  CLIP_MINMAX,
  CLIP_DECREASING
} Clip_Type;

/* This has to agree with udf.h. */
typedef struct WS_Function_struct
{
  void (*Init_ws)(Domain *) ;
  real (*Sat_P)(real);
  real (*Sat_T)(real, real);

  real (*eos_p)(real, real);
  real (*eos_density)(real, real);

  real (*enthalpy_v)(real, real);
  real (*entropy_v)(real, real);
  real (*cp_v)(real, real);
  real (*cv_v)(real, real);
  real (*viscosity_v)(real, real);
  real (*thermal_cond_v)(real, real);

  real (*rho_l)(real);
  real (*cp_l)(real);
  real (*viscosity_l)(real);
  real (*thermal_cond_l)(real);
  real (*surface_tension)(real);
}
WS_Functions;

extern FLUENT_EXPORT cxboolean UDWS_PROP ;

#define UDWS_METHOD(r,m)(r->m)

/* exported from the DLL */
extern UDF_EXPORT WS_Functions *udws_fcns;
FLUENT_EXPORT void Open_UDWS_Library(const char *name, cxboolean lopenlib);


FLUENT_EXPORT real ws_Psat(real T);
FLUENT_EXPORT real ws_Tsat(real P, real T);
FLUENT_EXPORT real ws_Hgl(real T);

FLUENT_EXPORT real WS_Rgas_f(face_t f, Thread *t);
FLUENT_EXPORT real WS_Rgas(cell_t c, Thread *t);
FLUENT_EXPORT real WS_density(real T, real P, real rgasg, real b);
FLUENT_EXPORT real WS_pressure(real T, real p, real r, real rgasg, real b);
FLUENT_EXPORT real WS_speed_of_sound(real T, real P, real r, real rgasg, real b);
FLUENT_EXPORT real WS_specific_heat(real T, real P, real r, real rgasg, real b);
FLUENT_EXPORT real WS_enthalpy(real T, real P, real r, real rgasg, real b);
FLUENT_EXPORT real WS_entropy(real T, real P, real r, real rgasg, real b);
FLUENT_EXPORT real WS_viscosity(real T, real P, real r, real rgasg, real b);
FLUENT_EXPORT real WS_thermal_conductivity(real T, real P, real r, real rgasg, real b);
/*FLUENT_EXPORT real WS_mw()  ;*/
FLUENT_EXPORT real WS_rho_t(real T, real P, real r, real rgasg, real b);
FLUENT_EXPORT real WS_rho_p(real T, real P, real r, real rgasg, real b);
FLUENT_EXPORT real WS_enthalpy_t(real T, real P, real r, real rgasg, real b);
FLUENT_EXPORT real WS_enthalpy_p(real T, real P, real r, real rgasg, real b);
FLUENT_EXPORT real WS_entropy_t(real T, real P, real r, real rgasg, real b);
FLUENT_EXPORT real WS_Specific_Heat_by_T_Integral(real T0, real T1, real P, real r, real rgasg, real b);
FLUENT_EXPORT void Init_Wetsteam(Domain *domain);
FLUENT_EXPORT void Set_Wet_Steam_Material(Domain *domain, Material *m, const char *name);

FLUENT_EXPORT void Wet_Steam_Stagnation_Condition(real rgasg, real b, real *Tt, real *pt, real  V2,
                                                  real *Ht, real *Ts, real *ps, real *rs, real *Hs,
                                                  int compute_static);

FLUENT_EXPORT void Wet_Steam_Isentropic_pi(real rgasg, real b, real Tt, real pt, real *V2,
                                           real *Ts, real *ps, real *rs, real *Ht, int *isupr);


#endif /* _FLUENT_WETSTEAM_H_ */

