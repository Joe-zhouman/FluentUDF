/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_UDF_H
#define _FLUENT_UDF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Header file for User Defined Functions */

#define _UDF 1
#define _CRT_SECURE_NO_DEPRECATE 1
#define _CRT_NONSTDC_NO_DEPRECATE 1

#ifdef UDFCONFIG_H
# include UDFCONFIG_H
#endif

#include "global.h"
#include "entity.h"
#include "mem.h"
#include "para.h"
#include "threads.h"

#include "cudf.h"

#include "amg.h"
#include "case.h"
#include "flow.h"
#include "id.h"
#include "metric.h"
#include "prop.h"
#include "real_gas.h"
#include "lmain.h"

#include "battery.h"
#include "sg_pollut.h"
#include "pollut_nox.h"
#include "pollut_sox.h"
#include "pollut_soot.h"
#include "pollut_hg.h"
#include "sg_mphase.h"
#include "sg_ke.h"
#include "turb_global_var.h"
#include "sg_disco.h"
#include "sg_mc.h"
#include "slide.h"
#include "surf.h"
#include "dpm.h"
#include "dpm_types.h"
#include "dpm_tools.h"
#include "dpm_path.h"
#include "dpm_mem.h"
#include "dpm_laws.h"
#include "cl_dpm.h"
#include "isat.h"
#include "rwdata.h"
#include "dynamesh_tools.h"
#include "six_dof.h"
#include "sg_udms.h"
#include "sg_wetsteam.h"
#include "sg_li_battery.h"

#if RP_NETWORK
#include "sg_network.h"
#endif /* RP_NETWORK */
#include "dual_cell.h"
#if RP_PLBC
# include "phase_lag.h"
#endif
#if RP_OVERSET
#include "overset.h"
#endif

#if _MSC_VER >= 1400 /* visual studio 2005 */
# ifdef UDF_NT
#  include "ud_io1.h"
# else
#  include "ud_io.h"
# endif
# ifndef USE_FLUENT_IO_API
# define USE_FLUENT_IO_API 1
# endif
#else
# ifndef USE_FLUENT_IO_API
# define USE_FLUENT_IO_API 0
# endif
#endif /* _MSC_VER >= 1400 */

#include "machine.h"
#include "sg_reacting_channel.h"
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#undef EXTERN_C
#define EXTERN_C  extern "C"
#else
#define EXTERN_C
#endif

#ifdef USE_UDF_PAR_IO
#define fprintf fluent_par_fprintf
#define fscanf fluent_par_fscanf
#endif

#ifdef USE_UDF_HOST_DUMMY

#define DEFINE_PROFILE(name, t, i) EXTERN_C void name(Thread *t, int i)
#define DEFINE_DIFFUSIVITY(name, c, t, i) EXTERN_C real name(cell_t c, Thread *t, int i)
#define DEFINE_PROPERTY(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_SPECIFIC_HEAT(name, T, Tref, h, yi) EXTERN_C real name(real T, real Tref, real *h, real *yi)
#define DEFINE_DPM_PROPERTY(name, c, t, tp, T) \
  EXTERN_C real name(cell_t c, Thread *t, Tracked_Particle *tp, real T)
#define DEFINE_EXCHANGE_PROPERTY(name, c, mixture_thread, phase_index_1, phase_index_2) \
 EXTERN_C real name(cell_t c, Thread *mixture_thread, int phase_index_1, int phase_index_2)
#define DEFINE_BOILING_PROPERTY(name, f,t, c, mixture_thread, from_phase_index, from_species_index, to_phase_index, to_species_index) \
 EXTERN_C real name(face_t f,Thread *t,cell_t c,Thread *mixture_thread, int from_phase_index, int from_species_index, int to_phase_index, int to_species_index)
#define DEFINE_MASS_TR_PROPERTY(name, f, t, c, mixture_thread, from_phase_index, from_species_index, to_phase_index, to_species_index, mt_index, tabular_data) \
 EXTERN_C real name(face_t f, Thread *t, cell_t c, Thread *mixture_thread, int from_phase_index, int from_species_index, \
                    int to_phase_index, int to_species_index, int mt_index, MT_Tabular_Data *tabular_data)
#define DEFINE_VECTOR_EXCHANGE_PROPERTY(name, c, mixture_thread, phase_index_1, phase_index_2, vector_result) \
 EXTERN_C void name(cell_t c, Thread *mixture_thread, int phase_index_1, int phase_index_2, real *vector_result)
#define DEFINE_MASS_TRANSFER(name, c, mixture_thread, from_phase_index, from_species_index, to_phase_index, to_species_index) \
 EXTERN_C real name(cell_t c, Thread *mixture_thread, int from_phase_index, int from_species_index, int to_phase_index, int to_species_index)
#define DEFINE_LINEARIZED_MASS_TRANSFER(name, c, mixture_thread, from_phase_index, from_species_index, to_phase_index, to_species_index, lin_from, lin_to) \
 EXTERN_C real name(cell_t c, Thread *mixture_thread, int from_phase_index, int from_species_index, int to_phase_index, int to_species_index, real *lin_from, real *lin_to)
#define DEFINE_HET_RXN_RATE(name, c, t, hr, mw, yi, rr, rr_t)\
  EXTERN_C void name(cell_t c, Thread *t, Hetero_Reaction *hr, real **mw, real **yi, real *rr, real *rr_t)
#define DEFINE_SOURCE(name, c, t, dS, i)\
  EXTERN_C real name(cell_t c, Thread *t, real dS[], int i)
#define DEFINE_SOURCE_AE(name, c, t, dS, i)   \
  EXTERN_C real name(cell_t c, Thread *t, real dS[], int i)
#define DEFINE_SOURCE_FE(name, c, t)\
  EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_INIT(name, domain) EXTERN_C void name(Domain *domain)
#define DEFINE_UDS_FLUX(name, f, t, i) EXTERN_C real name(face_t f, Thread *t, int i)

#define DEFINE_UDS_UNSTEADY(name, c, t, i, apu, su) \
  EXTERN_C void name(cell_t c, Thread *t, int i, real *apu, real *su)

#define DEFINE_HEAT_FLUX(name, f, t, c0, t0, cid, cir) \
  EXTERN_C void name(face_t f, Thread *t, cell_t c0, Thread *t0, real cid[], real cir[])

#define DEFINE_VR_RATE(name, c, t, r, mw, yi, rr, rr_t) \
  EXTERN_C void name(cell_t c, Thread *t, \
      Reaction *r, real *mw, real *yi, real *rr, real *rr_t)

#define DEFINE_NET_REACTION_RATE(name, c, t, particle, pressure, temp, yi, rr, jac) \
  EXTERN_C void name(cell_t c, Thread* t, Particle *particle, double *pressure, double *temp, double *yi, double *rr, double *jac)

#define DEFINE_RELAX_TO_EQUILIBRIUM(name, c, t, pressure, temp, yi, tau) \
  EXTERN_C void name(cell_t c, Thread *t, real pressure, real temp, real *yi, real *tau)

#define DEFINE_SOURCE_MASK(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_SPONGE_LAYER(name, c, t) EXTERN_C real name(cell_t c, Thread *t)

#define DEFINE_SR_RATE(name, f, t, r, mw, yi, rr) \
  EXTERN_C void name(face_t f, Thread *t, \
      Reaction *r, double *mw, double *yi, double *rr)
#define DEFINE_PR_RATE(name, c, t, r, mw, ci, tp, sf, dif_index, cat_index, rr) \
  EXTERN_C void name(cell_t c, Thread *t, \
      Reaction *r, real *mw, real *ci, Tracked_Particle *tp, \
        real *sf , int dif_index, int cat_index, real *rr)
#define DEFINE_EC_RATE(name, f, t, r, eta, i, dideta, Eeq) \
  EXTERN_C void name(face_t f, Thread *t, Reaction *r, double eta, double *i, double *dideta, double *Eeq)
#define DEFINE_EC_KINETICS_PARAMETER(name, f, t) \
  EXTERN_C real name(face_t f, Thread *t)
#define DEFINE_BATTERY_PROPERTY(name, x, T) \
  EXTERN_C real name(real x, real T)
#define DEFINE_BATTERY_PARAMETER_NTGK(name, c, t, T, soc, U, Y) \
  EXTERN_C void name(cell_t c, Thread *t, real T, real soc, real *U, real *Y)
#define DEFINE_BATTERY_PARAMETER_ECM(name, c, t, T, soc, mode, Voc, Rs, R1, C1, R2, C2, R3, C3) \
  EXTERN_C void name(cell_t c, Thread *t, real T, real soc, int mode, real *Voc, real *Rs, real *R1, real *C1, real *R2, real *C2, real *R3, real *C3)
#define DEFINE_BATTERY_ENTROPIC_HEAT(name, soc)  EXTERN_C real name(real soc)
#define DEFINE_BATTERY_ECHEM_MODEL(name, zero_start, mode, T, V_in, I_in, dt, I_out, Qe, V_out) \
  EXTERN_C void name(int zero_start, int mode, real T, real V_in, real I_in, real dt, real *I_out, real  *Qe, real *V_out)
#define DEFINE_BATTERY_NEWMAN_OCP(name, mode, x, T) EXTERN_C real name(int mode, real x, real T)
#define DEFINE_BATTERY_NEWMAN_BV_RATE(name, Ce, Cs, Cs_max, T, eta, i_0, alpha_a, alpha_c, mode) \
       EXTERN_C real name(real Ce, real Cs, real Cs_max, real T, real eta, real i_0, real alpha_a, real alpha_c, int mode)
#define DEFINE_BATTERY_NEWMAN_POSTPROCESSING(name, c, t, T, Vp, Vn)  EXTERN_C void name(cell_t c, Thread *t, real T, real Vp, real Vn)
#define DEFINE_BATTERY_NEWMAN_PROP_ELECTROLYTE(name, Ce, T)  EXTERN_C real name(real Ce, real T)
#define DEFINE_BATTERY_NEWMAN_PROP_ELECTRODE(name, Cs, T)    EXTERN_C real name(real Cs, real T)
#define DEFINE_BATTERY_NEWMAN_PROP_POROSITY(name, c, t)      EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_BATTERY_NEWMAN_SWELL_LAYER_N(name, c , t, N_vector) EXTERN_C void name(cell_t c, Thread *t, real *N_vector)
#define DEFINE_BATTERY_CLUSTER(name, c, t)      EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_BATTERY_ELOAD_PROFILE(name, time, current, voltage, power, type, value)  \
  EXTERN_C void name(real time, real current, real voltage, real power, int *type, real *value)
#define DEFINE_TURB_PREMIX_SOURCE(name, c, t, turbulent_flame_speed, source) \
  EXTERN_C void name(cell_t c, Thread *t, real *turbulent_flame_speed, real *source)
#define DEFINE_ECFM_SOURCE(name, c, t, source, ap) \
  EXTERN_C void name(cell_t c, Thread *t, real *source, real *ap)
#define DEFINE_ECFM_SPARK_SOURCE(name, c, t, source, ap) \
  EXTERN_C void name(cell_t c, Thread *t, real *source, real *ap)
#define DEFINE_GEQN_SOURCE(name, c, t, source, ap) \
  EXTERN_C void name(cell_t c, Thread *t, real *source, real *ap)
#define DEFINE_SPARK_GEOM(name, c, t) EXTERN_C int name(cell_t c, Thread *t)
#define DEFINE_IGNITE_SOURCE(name, c, t, source) \
  EXTERN_C void name(cell_t c, Thread *t, real *source)
#define DEFINE_THICKENED_FLAME_MODEL(name, c, t, f, e, omega) \
  EXTERN_C void name(cell_t c, Thread *t, real *f, real *e, real *omega)
#define DEFINE_DPM_BODY_FORCE(name, tp, i) EXTERN_C real name(Tracked_Particle *tp, int i)
#define DEFINE_DPM_DRAG(name, Re, tp) EXTERN_C real name(real Re, Tracked_Particle *tp)
#define DEFINE_DPM_SOURCE(name, c, t, S, strength, tp) \
  EXTERN_C void name(cell_t c, Thread *t, dpms_t *S, real strength, Tracked_Particle *tp)
#define DEFINE_DPM_OUTPUT(name, header, fp, tp, t, plane) \
  EXTERN_C void name(int header, FILE *fp, Tracked_Particle *tp, Thread *t, Plane *plane)
#define DEFINE_DPM_EROSION(name, tp, t, f, normal, alpha, Vmag, mdot) \
  EXTERN_C void name(Tracked_Particle *tp, Thread *t, face_t f, real normal[], \
      real alpha, real Vmag, real mdot)
#define DEFINE_DPM_SCALAR_UPDATE(name, c, t, initialize, tp) \
  EXTERN_C void name(cell_t c, Thread *t, int initialize, Tracked_Particle *tp)
#define DEFINE_DPM_SPRAY_COLLIDE(name, tp, p) \
  EXTERN_C void name(Tracked_Particle *tp, Particle *p)
#define DEFINE_DPM_LAW(name, tp, ci) EXTERN_C void name(Tracked_Particle *tp, int ci)
#define DEFINE_DPM_SWITCH(name, tp, ci) EXTERN_C void name(Tracked_Particle *tp, int ci)
#define DEFINE_DPM_INJECTION_INIT(name, I) EXTERN_C void name(Injection *I)
#define DEFINE_DPM_BC(name, tp, t, f, normal, dim) \
  EXTERN_C int name(Tracked_Particle *tp, Thread *t, face_t f, real normal[], int dim)
#define DEFINE_DPM_TIMESTEP(name, tp, ts) EXTERN_C real name(Tracked_Particle *tp,real ts)
#define DEFINE_IMPINGEMENT(name, tp, rel_dot_n, f, t, y_s, E_imp)   \
  EXTERN_C int name(Tracked_Particle *tp, real rel_dot_n, face_t f, Thread *t, real *y_s, real *E_imp)
#define DEFINE_FILM_REGIME(name, regime, tp, pn, f, t, f_normal, update) \
  EXTERN_C void name(Wall_Film_Regime regime, Tracked_Particle *tp, Particle *pn, face_t f, Thread *t, \
      real f_normal[], cxboolean update)
#define DEFINE_SPLASHING_DISTRIBUTION(name, tp, rel_dot_n, f_normal, n_samp, s) \
  EXTERN_C void name(Tracked_Particle *tp, real rel_dot_n, real f_normal[], int n_samp, splashing_distribution_t *s)
#define DEFINE_DPM_VP_EQUILIB(name, tp, Tp, cvap_surf, Z) \
  EXTERN_C void name(Tracked_Particle *tp, real Tp, real *cvap_surf, real *Z)
#define DEFINE_DPM_HEAT_MASS(name, tp, Cp, hgas, hvap, cvap_surf, Z, dydt, dzdt) \
  EXTERN_C void name(Tracked_Particle *tp, real Cp, \
            real *hgas, real *hvap, real *cvap_surf, real Z, real *dydt, dpms_t *dzdt)
#define DEFINE_DPM_INTERPOLATION(name, tp) \
  EXTERN_C void name(Tracked_Particle *tp)
#define DEFINE_SCAT_PHASE_FUNC(name, c, f) \
     EXTERN_C real name(real c, real *f)
#define DEFINE_CAVITATION_RATE(name, c, t, p, rhoV, rhoL, vofV, p_v, cigma, f_gas, m_dot) \
  EXTERN_C void name(cell_t c, Thread *t, real *p, real *rhoV, real *rhoL, real *vofV, \
                   real *p_v, real *cigma, real *f_gas, real *m_dot)
#define DEFINE_RW_FILE(name, fp) EXTERN_C void name(FILE *fp)
#define DEFINE_OUTPUT_PARAMETER(name, n, parlist) EXTERN_C real name (int n, real* parlist)

#define DEFINE_REPORT_DEFINITION_FN(name) EXTERN_C real name ()
#define DEFINE_TURBULENT_VISCOSITY(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_PRANDTL_K(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_PRANDTL_D(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_PRANDTL_O(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_PRANDTL_T(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_PRANDTL_T_WALL(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_TURB_SCHMIDT(name, c, t, i) EXTERN_C real name(cell_t c, Thread *t, int i)
#define DEFINE_WALL_FUNCTIONS(name, f, t, c0, t0, wf_ret, yPlus, Emod) \
  EXTERN_C real name(face_t f, Thread *t, cell_t c0, Thread *t0, int wf_ret, real yPlus, real Emod)
#define DEFINE_TRANS_FLENGTH(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_TRANS_RETHETA_C(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_TRANS_RETHETA_T(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_TRANS_GEOMRGH(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_TRANS_ALG_REC_COR(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_CURVATURE_CORRECTION_CCURV(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_CORNER_FLOW_CORRECTION_CCORNER(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_KW_GEKO_CSEP(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_KW_GEKO_CNW(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_KW_GEKO_CMIX(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_KW_GEKO_BF(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_SBES_BF(name, c, t) EXTERN_C real name(cell_t c, Thread *t)

#define DEFINE_FLAMELET_PARAMETERS(name, nf,nc,ns,xf,xc,xs) \
  EXTERN_C void name(int nf, int nc, int ns, real *xf, real *xc, real *xs)
#define DEFINE_NOX_RATE(name, c, t, Pollut, Pollut_Par, NOx) \
  EXTERN_C void name(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, NOx_Parameter *NOx)
#define DEFINE_SOOT_PRECURSOR(name, Pollut, Pollut_Par, Soot) \
  EXTERN_C real name(Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, Soot_Parameter *Soot)
#define DEFINE_SOOT_OXIDATION_RATE(name, c, t, Pollut, Pollut_Par, Soot, soot_oxi_rates) \
  EXTERN_C void name(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, Soot_Parameter *Soot, real *soot_oxi_rates)
#define DEFINE_SOOT_NUCLEATION_RATES(name, c, t, Pollut, Pollut_Par, Soot, rates_lin,rates_nonlin,index) \
  EXTERN_C void name(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, Soot_Parameter *Soot, real *rates_lin, real *rates_nonlin, int index)
#define DEFINE_SOOT_MASS_RATES(name, c, t, Pollut, Pollut_Par, Soot, rates_lin, rates_nonlin,index) \
  EXTERN_C void name(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, Soot_Parameter *Soot, real *rates_lin, real *rates_nonlin, int index)
#define DEFINE_SOOT_MOM_RATES(name, c, t, Nnuc, Rnuc, NCnuc, Nsurf, Rsurf, Dsurf) \
  EXTERN_C void name(cell_t c, Thread *t, int *Nnuc, real *Rnuc, real *NCnuc, int *Nsurf, real *Rsurf, real *Dsurf)
#define DEFINE_SOX_RATE(name, c, t, Pollut, Pollut_Par, SOx) \
  EXTERN_C void name(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, SOx_Parameter *SOx)
#define DEFINE_HG_RATE(name, c, t, Pollut, Pollut_Par, Hg) \
  EXTERN_C void name(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, Hg_Parameter *Hg)
#define DEFINE_CHEM_STEP(name, c, t, p, num_p, n_spe, dt, pres, temp, yk) \
  EXTERN_C void name(cell_t c, Thread *t, Particle *p, int num_p, int n_spe, double *dt, double *pres, double *temp, double *yk)
#define DEFINE_EDC_SCALES(name, c, t, c1, c2, calc_tau, tau)  \
  EXTERN_C void name(cell_t c, Thread *t, real *c1, real *c2, int calc_tau, real *tau)
#define DEFINE_EDC_MDOT(name, c, t, mdot, calc_tau, tau)  \
  EXTERN_C void name(cell_t c, Thread *t, real *mdot, int calc_tau, real *tau)
#define DEFINE_PERFORATED_CD(name, t, cd, input)  \
  EXTERN_C void name(Thread *t, real *cd, real *input)
#define DEFINE_CPHI(name, c, t) \
  EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_PDF_TRANSPORT_DENSITY(name, c, t, p) \
  EXTERN_C real name(cell_t c, Thread *t, Particle *p)
#define DEFINE_GRID_MOTION(name, d, dt, time, dtime) \
  EXTERN_C void name(Domain *d, Dynamic_Thread *dt, real time, real dtime)

#define DEFINE_GEOM(name, d, dt, position) \
  EXTERN_C void name(Domain *d, Dynamic_Thread *dt, real *position)
#define DEFINE_CONTACT(name, dt, contacts) \
  EXTERN_C void name(Dynamic_Thread *dt, Objp *contacts)
#define DEFINE_GAP_MODEL_SOURCE(name, c, tc, Source, dS) \
  EXTERN_C void name(cell_t c, Thread *tc, real Source[], real dS[])  
  
#define DEFINE_PERDISP_MOTION(name, t, perdisp) \
  EXTERN_C void name(Thread *t, double *perdisp)

#define DEFINE_PROFILE_NODE(name, t, udf_node) \
  EXTERN_C void name(Thread *t, double *udf_node)

#define DEFINE_DELTAT(name, domain) EXTERN_C real name(Domain *domain)
#define DEFINE_DOM_SOURCE(name,c,t,ni,nb,emission,in_scattering,abs_coeff,scat_coeff)\
  EXTERN_C void name(cell_t c, Thread* t, int ni, int nb, real *emission, real *in_scattering,\
             real *abs_coeff, real *scat_coeff)

#define DEFINE_DOM_DIFFUSE_REFLECTIVITY(name,t,nb,n_a,n_b,diff_ref_a, \
diff_tran_a, diff_ref_b, diff_tran_b) \
EXTERN_C void name(Thread *t, int nb,  real n_a, real n_b, real *diff_ref_a, \
real *diff_tran_a, real *diff_ref_b, real *diff_tran_b)

#define DEFINE_DOM_SPECULAR_REFLECTIVITY(name,f,t,nb,n_a, n_b, \
ray_direction,  e_n, total_internal_reflection, \
specular_reflectivity, specular_transmissivity) \
 EXTERN_C void name(face_t f, Thread *t, int nb,  real n_a, real n_b , \
real ray_direction[], real e_n[],  int *total_internal_reflection, \
real *specular_reflectivity,  real *specular_transmissivity)

#define DEFINE_EMISSIVITY_WEIGHTING_FACTOR(name,c,t,T,nb,emissivity_weighting_factor)\
  EXTERN_C void name(cell_t c, Thread* t, real T, int nb, real *emissivity_weighting_factor)

#define DEFINE_SOLAR_TRANSMISSIVITY(name, f, t, e_n, e_sun, trans_V, trans_I, \
absorptivity_V, absorptivity_I) \
EXTERN_C void name(face_t f, Thread *t, double e_n[], double e_sun[], \
double *trans_V, double *trans_I, double *absorptivity_V, double *absorptivity_I)

#define DEFINE_SOLAR_INTENSITY(name, sun_x, sun_y, sun_z, S_hour, S_minute) \
  EXTERN_C real name(real sun_x, real sun_y, real sun_z, int S_hour,int S_minute)

#define DEFINE_GRAY_BAND_ABS_COEFF(name, c, t, nb)  \
   EXTERN_C real name(cell_t c, Thread *t, int nb)

#define DEFINE_WSGGM_ABS_COEFF(name, c, t, xi, p_t, s, soot_conc, Tcell, nb, ab_wsggm, ab_soot)  \
   EXTERN_C void name(cell_t c, Thread *t, real xi[], real p_t, real s, real soot_conc, real Tcell, int nb, real *ab_wsggm, real *ab_soot)

#define DEFINE_ANISOTROPIC_DIFFUSIVITY(name, c, t, ns, dmatrix)   \
  EXTERN_C void name(cell_t c, Thread *t, int ns, real dmatrix[ND_ND][ND_ND])

#define DEFINE_ANISOTROPIC_CONDUCTIVITY(name, c, t, dmatrix)    \
  EXTERN_C void name(cell_t c, Thread *t, real dmatrix[ND_ND][ND_ND])

#define DEFINE_DYNAMIC_ZONE_PROPERTY(name, dt, lh)  \
  EXTERN_C void name(Dynamic_Thread *dt, real *lh)

#define DEFINE_NETWORK_NODE_PROP(name, network_id, network_cell_id) \
  EXTERN_C real name(int network_id, int network_cell_id)
#define DEFINE_NETWORK_LINK_PROP(name, network_id, network_cell_id, network_cellnb, nbflag) \
  EXTERN_C real name(int network_id, int network_cell_id, int network_cellnb, int nbflag)
#define DEFINE_NETWORK_END_PROP(name, networkend_id)  \
  EXTERN_C real name(int networkend_id)
#define DEFINE_EVAL(name, domain)   \
  EXTERN_C cxboolean name(Domain *domain)
#define DEFINE_EXECUTE_ON_LOADING(name, libname) EXTERN_C void name(char *libname)

#define DEFINE_MATRIX_SOLVER(name, controls, fine, r0) \
    EXTERN_C int name(AMG_Controls controls, Level fine, real r0[])


/*population balance udf's*/

#define DEFINE_PB_BREAK_UP_RATE_FREQ(name, cell, thread, d_1) \
   EXTERN_C real name(cell_t cell, Thread *thread, real d_1)
#define DEFINE_PB_BREAK_UP_RATE_PDF(name, cell, thread_1, d_1, thread_2, d_2) \
   EXTERN_C real name(cell_t cell, Thread *thread_1, real d_1, Thread *thread_2, real d_2)
#define DEFINE_PB_COALESCENCE_RATE(name, cell, thread_1, d_1, thread_2, d_2) \
   EXTERN_C real name(cell_t cell, Thread *thread_1, real d_1, Thread *thread_2, real d_2)
#define DEFINE_PB_NUCLEATION_RATE(name, cell, thread)\
   EXTERN_C real name(cell_t cell, Thread *thread)
#define DEFINE_PB_GROWTH_RATE(name, cell, thread, d_i)\
   EXTERN_C real name(cell_t cell, Thread *thread, real d_i)
#define DEFINE_SOLIDIFICATION_PARAMS(name,c,t,Amush,back_diff_beta) \
        EXTERN_C void name(cell_t c, Thread *t, real *Amush, real *back_diff_beta)
#define DEFINE_TRANSIENT_PROFILE(name, current_time) \
        EXTERN_C real name(real current_time)
#define DEFINE_ZONE_MOTION(name,omega,axis,origin,velocity,time,dtime) \
        EXTERN_C void name(real *omega, real axis[ND_3], real origin[ND_3], real velocity[ND_3],real time,real dtime)

/* backward compatibility */
#define C_PART(c,t) C_PART_ACTIVE(c,t)
#define DEFINE_PDF_TABLE(name, m, c, t, fmean, fvar, fmean2, fvar2, cmean, cvar, h, what, prop, x, s_pollut) \
        EXTERN_C void name(Material * m, cell_t c, Thread *t, real fmean, real fvar, real fmean2, real fvar2, \
                           real cmean, real cvar, real h, int what, real prop[], real * x, Pollut_Rate * s_pollut[])
#define DEFINE_REACTING_CHANNEL_SOLVER(name,params,inlet_state,dist,dt,wall_temp,wall_hf,compute_htc)\
        EXTERN_C void name(int *params,real *inlet_state, real *dist, real *dt, real *wall_temp, real *wall_hf, cxboolean *compute_htc)
#define DEFINE_REACTING_CHANNEL_BC(name,i,group) EXTERN_C void name(int i, Channel_Group *group)
#else /* USE_UDF_HOST_DUMMY */
#define DEFINE_PROFILE(name, t, i) EXTERN_C void name(Thread *t, int i)
#define DEFINE_DIFFUSIVITY(name, c, t, i) EXTERN_C real name(cell_t c, Thread *t, int i)
#define DEFINE_PROPERTY(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_SPECIFIC_HEAT(name, T, Tref, h, yi) EXTERN_C real name(real T, real Tref, real *h, real *yi)
#define DEFINE_DPM_PROPERTY(name, c, t, tp, T) \
  EXTERN_C real name(cell_t c, Thread *t, Tracked_Particle *tp, real T)
#define DEFINE_EXCHANGE_PROPERTY(name, c, mixture_thread, second_column_phase_index, first_column_phase_index) \
EXTERN_C real name(cell_t c, Thread *mixture_thread, int second_column_phase_index, int first_column_phase_index)
#define DEFINE_BOILING_PROPERTY(name, f,t, c, mixture_thread, from_phase_index, from_species_index, to_phase_index, to_species_index) \
EXTERN_C real name(face_t f,Thread *t,cell_t c,Thread *mixture_thread, int from_phase_index, int from_species_index, int to_phase_index, int to_species_index)
#define DEFINE_MASS_TR_PROPERTY(name, f, t, c, mixture_thread, from_phase_index, from_species_index, to_phase_index, to_species_index, mt_index, tabular_data) \
EXTERN_C real name(face_t f, Thread *t, cell_t c, Thread *mixture_thread, int from_phase_index, int from_species_index, \
                   int to_phase_index, int to_species_index, int mt_index, MT_Tabular_Data *tabular_data)
#define DEFINE_VECTOR_EXCHANGE_PROPERTY(name, c, mixture_thread, second_column_phase_index, first_column_phase_index, vector_result) \
EXTERN_C void name(cell_t c, Thread *mixture_thread, int second_column_phase_index, int first_column_phase_index, real *vector_result)
#define DEFINE_MASS_TRANSFER(name, c, mixture_thread, from_phase_index, from_species_index, to_phase_index, to_species_index) \
EXTERN_C real name(cell_t c, Thread *mixture_thread, int from_phase_index, int from_species_index, int to_phase_index, int to_species_index)
#define DEFINE_LINEARIZED_MASS_TRANSFER(name, c, mixture_thread, from_phase_index, from_species_index, to_phase_index, to_species_index, lin_from, lin_to) \
EXTERN_C real name(cell_t c, Thread *mixture_thread, int from_phase_index, int from_species_index, int to_phase_index, int to_species_index, real *lin_from, real *lin_to)
#define DEFINE_HET_RXN_RATE(name, c, t, hr, mw, yi, rr, rr_t) \
  EXTERN_C void name(cell_t c, Thread *t, Hetero_Reaction *hr, real **mw, real **yi, real *rr, real *rr_t)
#define DEFINE_SOURCE(name, c, t, dS, i) \
  EXTERN_C real name(cell_t c, Thread *t, real dS[], int i)
#define DEFINE_SOURCE_AE(name, c, t, dS, i)   \
  EXTERN_C real name(cell_t c, Thread *t, real dS[], int i)
#define DEFINE_SOURCE_FE(name, c, t) \
  EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_INIT(name, domain) EXTERN_C void name(Domain *domain)
#define DEFINE_UDS_FLUX(name, f, t, i) EXTERN_C real name(face_t f, Thread *t, int i)
#define DEFINE_UDS_UNSTEADY(name, c, t, i, apu, su) \
  EXTERN_C void name(cell_t c, Thread *t, int i, real *apu, real *su)
#define DEFINE_HEAT_FLUX(name, f, t, c0, t0, cid, cir) \
  EXTERN_C void name(face_t f, Thread *t, cell_t c0, Thread *t0, real cid[], real cir[])
#define DEFINE_VR_RATE(name, c, t, r, mw, yi, rr, rr_t) \
  EXTERN_C void name(cell_t c, Thread *t, \
      Reaction *r, real *mw, real *yi, real *rr, real *rr_t)
#define DEFINE_NET_REACTION_RATE(name, c, t, particle, pressure, temp, yi, rr, jac) \
  EXTERN_C void name(cell_t c, Thread* t, Particle *particle, double *pressure, double *temp, double *yi, double *rr, double *jac)
#define DEFINE_RELAX_TO_EQUILIBRIUM(name, c, t, pressure, temp, yi, tau) \
  EXTERN_C void name(cell_t c, Thread *t, real pressure, real temp, real *yi, real *tau)
#define DEFINE_SOURCE_MASK(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_SPONGE_LAYER(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_SR_RATE(name, f, t, r, mw, yi, rr) \
  EXTERN_C void name(face_t f, Thread *t, \
      Reaction *r, double *mw, double *yi, double *rr)
#define DEFINE_PR_RATE(name, c, t, r, mw, ci, tp, sf, dif_index, cat_index, rr) \
  EXTERN_C void name(cell_t c, Thread *t, \
      Reaction *r, real *mw, real *ci, Tracked_Particle *tp, \
        real *sf , int dif_index, int cat_index, real *rr)
#define DEFINE_EC_RATE(name, f, t, r, eta, i, dideta, Eeq) \
  EXTERN_C void name(face_t f, Thread *t, Reaction *r, double eta, double *i, double *dideta, double *Eeq)
#define DEFINE_EC_KINETICS_PARAMETER(name, f, t) \
  EXTERN_C real name(face_t f, Thread *t)
#define DEFINE_BATTERY_PROPERTY(name, x, T) \
  EXTERN_C real name(real x, real T)
#define DEFINE_BATTERY_PARAMETER_NTGK(name, c, t, T, soc, U, Y) \
  EXTERN_C void name(cell_t c, Thread *t, real T, real soc, real *U, real *Y)
#define DEFINE_BATTERY_PARAMETER_ECM(name, c, t, T, soc, mode, Voc, Rs, R1, C1, R2, C2, R3, C3) \
  EXTERN_C void name(cell_t c, Thread *t, real T, real soc, int mode, real *Voc, real *Rs, real *R1, real *C1, real *R2, real *C2, real *R3, real *C3)
#define DEFINE_BATTERY_ENTROPIC_HEAT(name, soc)  EXTERN_C real name(real soc)
#define DEFINE_BATTERY_ECHEM_MODEL(name, zero_start, mode, T, V_in, I_in, dt, I_out, Qe, V_out) \
  EXTERN_C void name(int zero_start, int mode, real T, real V_in, real I_in, real dt, real *I_out, real  *Qe, real *V_out)
#define DEFINE_BATTERY_NEWMAN_OCP(name, mode, x, T) EXTERN_C real name(int mode, real x, real T)
#define DEFINE_BATTERY_NEWMAN_BV_RATE(name, Ce, Cs, Cs_max, T, eta, i_0, alpha_a, alpha_c, mode) \
       EXTERN_C real name(real Ce, real Cs, real Cs_max, real T, real eta, real i_0, real alpha_a, real alpha_c, int mode)
#define DEFINE_BATTERY_NEWMAN_POSTPROCESSING(name, c, t, T, Vp, Vn)  EXTERN_C void name(cell_t c, Thread *t, real T, real Vp, real Vn)
#define DEFINE_BATTERY_NEWMAN_PROP_ELECTROLYTE(name, Ce, T)  EXTERN_C real name(real Ce, real T)
#define DEFINE_BATTERY_NEWMAN_PROP_ELECTRODE(name, Cs, T)    EXTERN_C real name(real Cs, real T)
#define DEFINE_BATTERY_NEWMAN_PROP_POROSITY(name, c, t)      EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_BATTERY_NEWMAN_SWELL_LAYER_N(name, c , t, N_vector) EXTERN_C void name(cell_t c, Thread *t, real *N_vector)
#define DEFINE_BATTERY_CLUSTER(name, c, t)      EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_BATTERY_ELOAD_PROFILE(name, time, current, voltage, power, type, value) \
  EXTERN_C void name(real time, real current, real voltage, real power, int *type, real *value)
#define DEFINE_TURB_PREMIX_SOURCE(name, c, t, turbulent_flame_speed, source) \
  EXTERN_C void name(cell_t c, Thread *t, real *turbulent_flame_speed, real *source)
#define DEFINE_ECFM_SOURCE(name, c, t, source, ap) \
  EXTERN_C void name(cell_t c, Thread *t, real *source, real *ap)
#define DEFINE_ECFM_SPARK_SOURCE(name, c, t, source, ap) \
  EXTERN_C void name(cell_t c, Thread *t, real *source, real *ap)
#define DEFINE_GEQN_SOURCE(name, c, t, source, ap) \
  EXTERN_C void name(cell_t c, Thread *t, real *source, real *ap)
#define DEFINE_SPARK_GEOM(name, c, t) EXTERN_C int name(cell_t c, Thread *t)
#define DEFINE_IGNITE_SOURCE(name, c, t, source) \
  EXTERN_C void name(cell_t c, Thread *t, real *source)
#define DEFINE_THICKENED_FLAME_MODEL(name, c, t, f, e, omega) \
  EXTERN_C void name(cell_t c, Thread *t, real *f, real *e, real *omega)
#define DEFINE_DPM_BODY_FORCE(name, tp, i) EXTERN_C real name(Tracked_Particle *tp, int i)
#define DEFINE_DPM_DRAG(name, Re, tp) EXTERN_C real name(real Re, Tracked_Particle *tp)
#define DEFINE_DPM_SOURCE(name, c, t, S, strength, tp) \
  EXTERN_C void name(cell_t c, Thread *t, dpms_t *S, real strength, Tracked_Particle *tp)
#define DEFINE_DPM_OUTPUT(name, header, fp, tp, t, plane) \
  EXTERN_C void name(int header, FILE *fp, Tracked_Particle *tp, Thread *t, Plane *plane)
#define DEFINE_DPM_EROSION(name, tp, t, f, normal, alpha, Vmag, mdot) \
  EXTERN_C void name(Tracked_Particle *tp, Thread *t, face_t f, real normal[], \
      real alpha, real Vmag, real mdot)
#define DEFINE_DPM_SCALAR_UPDATE(name, c, t, initialize, tp) \
  EXTERN_C void name(cell_t c, Thread *t, int initialize, Tracked_Particle *tp)
#define DEFINE_DPM_SPRAY_COLLIDE(name, tp, p) \
  EXTERN_C void name(Tracked_Particle *tp, Particle *p)
#define DEFINE_DPM_LAW(name, tp, ci) EXTERN_C void name(Tracked_Particle *tp, int ci)
#define DEFINE_DPM_SWITCH(name, tp, ci) EXTERN_C void name(Tracked_Particle *tp, int ci)
#define DEFINE_DPM_INJECTION_INIT(name, I) EXTERN_C void name(Injection *I)
#define DEFINE_DPM_BC(name, tp, t, f, normal, dim) \
  EXTERN_C int name(Tracked_Particle *tp, Thread *t, face_t f, real normal[], int dim)
#define DEFINE_DPM_TIMESTEP(name, tp, ts) EXTERN_C real name(Tracked_Particle *tp,real ts)
#define DEFINE_IMPINGEMENT(name, tp, rel_dot_n, f, t, y_s, E_imp)   \
  EXTERN_C int name(Tracked_Particle *tp, real rel_dot_n, face_t f, Thread *t, real *y_s, real *E_imp)
#define DEFINE_FILM_REGIME(name, regime, tp, pn, f, t, f_normal, update) \
  EXTERN_C void name(Wall_Film_Regime regime, Tracked_Particle *tp, Particle *pn, face_t f, Thread *t, \
      real f_normal[], cxboolean update)
#define DEFINE_SPLASHING_DISTRIBUTION(name, tp, rel_dot_n, f_normal, n_samp, s) \
  EXTERN_C void name(Tracked_Particle *tp, real rel_dot_n, real f_normal[], int n_samp, splashing_distribution_t *s)
#define DEFINE_DPM_VP_EQUILIB(name, tp, Tp, cvap_surf, Z) \
  EXTERN_C void name(Tracked_Particle *tp, real Tp, real *cvap_surf, real *Z)
#define DEFINE_DPM_HEAT_MASS(name, tp, Cp, hgas, hvap, cvap_surf, Z, dydt, dzdt) \
  EXTERN_C void name(Tracked_Particle *tp, real Cp, \
            real *hgas, real *hvap, real *cvap_surf, real Z, real *dydt, dpms_t *dzdt)
#define DEFINE_DPM_INTERPOLATION(name, tp) \
  EXTERN_C void name(Tracked_Particle *tp)
#define DEFINE_SCAT_PHASE_FUNC(name, c, f) \
     EXTERN_C real name(real c, real *f)
#define DEFINE_CAVITATION_RATE(name, c, t, p, rhoV, rhoL, vofV, p_v, cigma, f_gas, m_dot) \
  EXTERN_C void name(cell_t c, Thread *t, real *p, real *rhoV, real *rhoL, real *vofV, \
                   real *p_v, real *cigma, real *f_gas, real *m_dot)
#define DEFINE_RW_FILE(name, fp) EXTERN_C void name(FILE *fp)
#define DEFINE_RW_HDF_FILE(name, fname) EXTERN_C void name(char *fname)
#define DEFINE_OUTPUT_PARAMETER(name, n, parlist) EXTERN_C real name (int n, real* parlist)
#define DEFINE_REPORT_DEFINITION_FN(name) EXTERN_C real name ()
#define DEFINE_TURBULENT_VISCOSITY(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_PRANDTL_K(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_PRANDTL_D(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_PRANDTL_O(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_PRANDTL_T(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_PRANDTL_T_WALL(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_TURB_SCHMIDT(name, c, t, i) EXTERN_C real name(cell_t c, Thread *t, int i)
#define DEFINE_WALL_FUNCTIONS(name, f, t, c0, t0, wf_ret, yPlus, Emod) \
  EXTERN_C real name(face_t f, Thread *t, cell_t c0, Thread *t0, int wf_ret, real yPlus, real Emod)
#define DEFINE_TRANS_FLENGTH(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_TRANS_RETHETA_C(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_TRANS_RETHETA_T(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_TRANS_GEOMRGH(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_TRANS_ALG_REC_COR(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_CURVATURE_CORRECTION_CCURV(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_CORNER_FLOW_CORRECTION_CCORNER(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_KW_GEKO_CSEP(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_KW_GEKO_CNW(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_KW_GEKO_CMIX(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_KW_GEKO_BF(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_SBES_BF(name, c, t) EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_FLAMELET_PARAMETERS(name, nf,nc,ns,xf,xc,xs) \
  EXTERN_C void name(int nf, int nc, int ns, real *xf, real *xc, real *xs)
#define DEFINE_NOX_RATE(name, c, t, Pollut, Pollut_Par, NOx) \
  EXTERN_C void name(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, NOx_Parameter *NOx)
#define DEFINE_SOOT_PRECURSOR(name, Pollut, Pollut_Par, Soot) \
  EXTERN_C real name(Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, Soot_Parameter *Soot)
#define DEFINE_SOOT_OXIDATION_RATE(name, c, t, Pollut, Pollut_Par, Soot, soot_oxi_rates) \
  EXTERN_C void name(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, Soot_Parameter *Soot, real *soot_oxi_rates)
#define DEFINE_SOOT_NUCLEATION_RATES(name, c, t, Pollut, Pollut_Par, Soot, rates_lin,rates_nonlin,index) \
  EXTERN_C void name(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, Soot_Parameter *Soot, real *rates_lin, real *rates_nonlin, int index)
#define DEFINE_SOOT_MASS_RATES(name, c, t, Pollut, Pollut_Par, Soot, rates_lin, rates_nonlin,index) \
  EXTERN_C void name(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, Soot_Parameter *Soot, real *rates_lin, real *rates_nonlin, int index)
#define DEFINE_SOOT_MOM_RATES(name, c, t, Nnuc, Rnuc, NCnuc, Nsurf, Rsurf, Dsurf) \
  EXTERN_C void name(cell_t c, Thread *t, int *Nnuc, real *Rnuc, real *NCnuc, int *Nsurf, real *Rsurf, real *Dsurf)
#define DEFINE_SOX_RATE(name, c, t, Pollut, Pollut_Par, SOx) \
  EXTERN_C void name(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, SOx_Parameter *SOx)
#define DEFINE_HG_RATE(name, c, t, Pollut, Pollut_Par, Hg) \
  EXTERN_C void name(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Parameter *Pollut_Par, Hg_Parameter *Hg)
#define DEFINE_CHEM_STEP(name, c, t, p, num_p, n_spe, dt, pres, temp, yk) \
  EXTERN_C void name(cell_t c, Thread *t, Particle *p, int num_p, int n_spe, double *dt, double *pres, double *temp, double *yk)
#define DEFINE_EDC_SCALES(name, c, t, c1, c2, calc_tau, tau)  \
  EXTERN_C void name(cell_t c, Thread *t, real *c1, real *c2, int calc_tau, real *tau)
#define DEFINE_EDC_MDOT(name, c, t, mdot, calc_tau, tau)  \
  EXTERN_C void name(cell_t c, Thread *t, real *mdot, int calc_tau, real *tau)
#define DEFINE_PERFORATED_CD(name, t, cd, input)  \
  EXTERN_C void name(Thread *t, real *cd, real *input)
#define DEFINE_CPHI(name, c, t) \
  EXTERN_C real name(cell_t c, Thread *t)
#define DEFINE_PDF_TRANSPORT_DENSITY(name, c, t, p) \
  EXTERN_C real name(cell_t c, Thread *t, Particle *p)
#define DEFINE_GRID_MOTION(name, d, dt, time, dtime) \
  EXTERN_C void name(Domain *d, Dynamic_Thread *dt, real time, real dtime)
#define DEFINE_GEOM(name, d, dt, position) \
  EXTERN_C void name(Domain *d, Dynamic_Thread *dt, real *position)
#define DEFINE_CONTACT(name, dt, contacts) \
  EXTERN_C void name(Dynamic_Thread *dt, Objp *contacts)
#define DEFINE_GAP_MODEL_SOURCE(name, c, tc, Source, dS) \
  EXTERN_C void name(cell_t c, Thread *tc, real Source[], real dS[])
#define DEFINE_DELTAT(name, domain) EXTERN_C real name(Domain *domain)

#define DEFINE_PERDISP_MOTION(name, t, perdisp) \
  EXTERN_C void name(Thread *t, double *perdisp)

#define DEFINE_PROFILE_NODE(name, t, udf_node) \
  EXTERN_C void name(Thread *t, double *udf_node)

#define DEFINE_DOM_SOURCE(name,c,t,ni,nb,emission,in_scattering,abs_coeff,scat_coeff)\
  EXTERN_C void name(cell_t c, Thread* t, int ni, int nb, real *emission, real *in_scattering,\
             real *abs_coeff, real *scat_coeff)
#define DEFINE_DOM_DIFFUSE_REFLECTIVITY(name,t,nb,n_a,n_b,diff_ref_a, \
diff_tran_a, diff_ref_b, diff_tran_b) \
EXTERN_C void name(Thread *t, int nb,  real n_a, real n_b, real *diff_ref_a, \
real *diff_tran_a, real *diff_ref_b, real *diff_tran_b)

#define DEFINE_DOM_SPECULAR_REFLECTIVITY(name,f,t,nb,n_a, n_b, \
ray_direction,  e_n, total_internal_reflection, \
specular_reflectivity, specular_transmissivity) \
 EXTERN_C void name(face_t f, Thread *t, int nb,  real n_a, real n_b , \
real ray_direction[], real e_n[],  int *total_internal_reflection, \
real *specular_reflectivity,  real *specular_transmissivity)

#define DEFINE_EMISSIVITY_WEIGHTING_FACTOR(name,c,t,T,nb,emissivity_weighting_factor)\
  EXTERN_C void name(cell_t c, Thread* t, real T, int nb, real *emissivity_weighting_factor)

#define DEFINE_SOLAR_TRANSMISSIVITY(name, f, t, e_n, e_sun, trans_V, trans_I, \
absorptivity_V, absorptivity_I) \
EXTERN_C void name(face_t f, Thread *t, double e_n[], double e_sun[], \
double *trans_V, double *trans_I, double *absorptivity_V, double *absorptivity_I)


#define DEFINE_SOLAR_INTENSITY(name, sun_x, sun_y, sun_z, S_hour, S_minute) \
   EXTERN_C real name(real sun_x, real sun_y, real sun_z, int S_hour,int S_minute)
#define DEFINE_GRAY_BAND_ABS_COEFF(name, c, t, nb)  \
   EXTERN_C real name(cell_t c, Thread *t, int nb)

#define DEFINE_WSGGM_ABS_COEFF(name, c, t, xi, p_t, s, soot_conc, Tcell, nb, ab_wsggm, ab_soot)  \
   EXTERN_C void name(cell_t c, Thread *t, real xi[], real p_t, real s, real soot_conc, real Tcell, int nb, real *ab_wsggm, real *ab_soot)

#define DEFINE_ANISOTROPIC_DIFFUSIVITY(name, c, t, ns, dmatrix)   \
  EXTERN_C void name(cell_t c, Thread *t, int ns, real dmatrix[ND_ND][ND_ND])

#define DEFINE_ANISOTROPIC_CONDUCTIVITY(name, c, t, dmatrix)    \
  EXTERN_C void name(cell_t c, Thread *t, real dmatrix[ND_ND][ND_ND])


#define DEFINE_DYNAMIC_ZONE_PROPERTY(name, dt, lh)  \
  EXTERN_C void name(Dynamic_Thread *dt, real *lh)

#define DEFINE_NETWORK_NODE_PROP(name, network_id, network_cell_id) \
  EXTERN_C real name(int network_id, int network_cell_id)

#define DEFINE_NETWORK_LINK_PROP(name, network_id, network_cell_id, network_cellnb, nbflag) \
  EXTERN_C real name(int network_id, int network_cell_id, int network_cellnb, int nbflag)
#define DEFINE_NETWORK_END_PROP(name, networkend_id)  \
  EXTERN_C real name(int networkend_id)

#define DEFINE_EVAL(name, domain)   \
  EXTERN_C cxboolean name(Domain *domain)

#define DEFINE_EXECUTE_ON_LOADING(name, libname) EXTERN_C void name(char *libname)

#define DEFINE_MATRIX_SOLVER(name, controls, fine, r0) \
    EXTERN_C int name(AMG_Controls controls, Level fine, real r0[])

/*population balance udf's*/

#define DEFINE_PB_BREAK_UP_RATE_FREQ(name, cell, thread, d_1) \
   EXTERN_C real name(cell_t cell, Thread *thread, real d_1)
#define DEFINE_PB_BREAK_UP_RATE_PDF(name, cell, thread_1, d_1, thread_2, d_2) \
   EXTERN_C real name(cell_t cell, Thread *thread_1, real d_1, Thread *thread_2, real d_2)
#define DEFINE_PB_COALESCENCE_RATE(name, cell, thread_1, d_1, thread_2, d_2) \
   EXTERN_C real name(cell_t cell, Thread *thread_1, real d_1, Thread *thread_2, real d_2)
#define DEFINE_PB_NUCLEATION_RATE(name, cell, thread)\
   EXTERN_C real name(cell_t cell, Thread *thread)
#define DEFINE_PB_GROWTH_RATE(name, cell, thread, d_i)\
   EXTERN_C real name(cell_t cell, Thread *thread, real d_i)

#define DEFINE_SOLIDIFICATION_PARAMS(name,c,t,Amush,back_diff_beta) \
        EXTERN_C void name(cell_t c, Thread *t, real *Amush, real *back_diff_beta)

#define DEFINE_TRANSIENT_PROFILE(name, current_time) \
        EXTERN_C real name(real current_time)

#define DEFINE_ZONE_MOTION(name,omega,axis,origin,velocity,time,dtime) \
        EXTERN_C void name(real *omega, real axis[ND_3], real origin[ND_3], real velocity[ND_3],real time,real dtime)

/* backward compatibility */
#define C_PART(c,t) C_PART_ACTIVE(c,t)

#define DEFINE_PDF_TABLE(name, m, c, t, fmean, fvar, fmean2, fvar2, cmean, cvar, h, what, prop, x, s_pollut) \
        EXTERN_C void name(Material * m, cell_t c, Thread *t, real fmean, real fvar, real fmean2, real fvar2, \
                           real cmean, real cvar, real h, int what, real prop[], real * x, Pollut_Rate * s_pollut[])

#define DEFINE_REACTING_CHANNEL_SOLVER(name,params,inlet_state,dist,dt,wall_temp,wall_hf,compute_htc)\
        EXTERN_C void name(int *params,real *inlet_state, real *dist, real *dt, real *wall_temp, real *wall_hf, cxboolean *compute_htc)

#define DEFINE_REACTING_CHANNEL_BC(name,i,group) EXTERN_C void name(int i, Channel_Group *group)
#endif /* USE_UDF_HOST_DUMMY */

#define DEFINE_ON_DEMAND(name) EXTERN_C void name(void)
#define DEFINE_ADJUST(name, domain) EXTERN_C void name(Domain *domain)
#define DEFINE_EXECUTE_AT_END(name) EXTERN_C void name(void)
#define DEFINE_CG_MOTION(name, dt, vel, omega, time, dtime)   \
  EXTERN_C void name(Dynamic_Thread *dt, real vel[], real omega[], real time, real dtime)
#define DEFINE_SDOF_PROPERTIES(name, properties, dt, time, dtime) \
  EXTERN_C void name(real *properties, Dynamic_Thread *dt, real time, real dtime)
#define DEFINE_DOM_BC_ADJUST(name, domain) EXTERN_C void name(Domain *domain)
#define DEFINE_EXECUTE_FROM_GUI(name, libname, mode) EXTERN_C void name(char *libname, int mode)
#define DEFINE_EXECUTE_AFTER_CASE(name, libname) EXTERN_C void name(char *libname)
#define DEFINE_EXECUTE_AFTER_DATA(name, libname) EXTERN_C void name(char *libname)
#define DEFINE_EXECUTE_AT_EXIT(name) EXTERN_C void name(void)

#define DEFINE_WALL_NODAL_DISP(name, f, t, v, m) \
  EXTERN_C real name(face_t f, Thread *t, Node *v, int m)
#define DEFINE_WALL_NODAL_FORCE(name, f, t, v, m) \
  EXTERN_C real name(face_t f, Thread *t, Node *v, int m)
/* end of udf.h */

#endif /* _FLUENT_UDF_H */
