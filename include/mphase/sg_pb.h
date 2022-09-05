/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#include "sg_delta.h"

/* population balance variables */
#define C_PB_DISCI(c,t,i)C_STORAGE_R(c,t,SV_PB_DISC_I(i))
#define F_PB_DISCI(e,t,i) C_PB_DISCI(e,t,i)

#define C_PB_DISCI_AP(c,t,i)C_STORAGE_R(c,t,SV_PB_DISCI_AP)
#define C_PB_DISCI_G(c,t,i)C_STORAGE_R_NV(c,t,SV_PB_DISCI_G(i))
#define C_PB_DISCI_RG(c,t,i)C_STORAGE_R_NV(c,t,SV_PB_DISCI_RG(i))
#define C_PB_DISCI_M1(c,t,i)C_STORAGE_R(c,t,SV_PB_DISCI_M1(i))
#define C_PB_DISCI_M2(c,t,i)C_STORAGE_R(c,t,SV_PB_DISCI_M2(i))
#define C_PB_DISCI_S(c,t,i)C_STORAGE_R(c,t,SV_PB_DISCI_S)
#define C_PB_DISCI_PS(c,t,i)C_STORAGE_R(c,t, (Svar)(SV_PB_DISC_PS_0+i))
#define C_PB_DISCI_DIFF(c,t,i)C_STORAGE_R(c,t, (Svar)(SV_PB_DISC_DIFF_COEFF_0+i))



/* don't know if needed */
#define F_PB_DISCI_M1(c,t,i) C_PB_DISCI_M1(c,t,i)
#define F_PB_DISCI_M2(c,t,i) C_PB_DISCI_M2(c,t,i)
#define F_PB_DISCI_FLUX(c,t,i)
#define PB_DISC_BC_FLUX 0
#define PB_DISC_BC_VALUE 1

#define C_PB_QMOMI(c,t,i)C_STORAGE_R(c,t,SV_PB_QMOM_I(i))
#define F_PB_QMOMI(e,t,i) C_PB_QMOMI(e,t,i)

#define C_PB_QMOMI_AP(c,t,i)C_STORAGE_R(c,t,SV_PB_QMOMI_AP)
#define C_PB_QMOMI_G(c,t,i)C_STORAGE_R_NV(c,t,SV_PB_QMOMI_G(i))
#define C_PB_QMOMI_RG(c,t,i)C_STORAGE_R_NV(c,t,SV_PB_QMOMI_RG(i))
#define C_PB_QMOMI_M1(c,t,i)C_STORAGE_R(c,t,SV_PB_QMOMI_M1(i))
#define C_PB_QMOMI_M2(c,t,i)C_STORAGE_R(c,t,SV_PB_QMOMI_M2(i))
#define C_PB_QMOMI_S(c,t,i)C_STORAGE_R(c,t,SV_PB_QMOMI_S)
#define C_PB_QMOMI_PS(c,t,i)C_STORAGE_R(c,t,SV_PB_QMOMI_PS(i))
#define C_PB_QMOMI_DIFF(c,t,i)C_STORAGE_R(c,t, (Svar)(SV_PB_QMOM_DIFF_COEFF_0+i))
#define C_PB_QMOMI_L(c,t,i)C_STORAGE_R(c,t,SV_PB_QMOMI_L(i))
#define C_PB_QMOMI_W(c,t,i)C_STORAGE_R(c,t,SV_PB_QMOMI_W(i))
#define C_PB_QMOM_IMB(c,t)C_STORAGE_R(c,t,SV_PB_QMOM_IMB)
#define C_PB_DISC_IMB(c,t)C_STORAGE_R(c,t,SV_PB_DISC_IMB)

#define C_PB_QMOM_real_mom(c,t) C_STORAGE_R(c,t,SV_PB_QMOM_real_mom)
#define C_PB_QMOMI_ZETA(c,t,i) C_STORAGE_R(c,t,SV_PB_QMOMI_ZETA(i))
#define F_PB_QMOMI_ZETA(e,t,i) C_PB_QMOMI_ZETA(e,t,i)


/* don't know if needed */
#define F_PB_QMOMI_M1(c,t,i) C_PB_QMOMI_M1(c,t,i)
#define F_PB_QMOMI_M2(c,t,i) C_PB_QMOMI_M2(c,t,i)
#define F_PB_QMOMI_FLUX(c,t,i)
#define PB_QMOM_BC_FLUX 0
#define PB_QMOM_BC_VALUE 1

/* SMM */
#define C_PB_SMMI(c,t,i)C_STORAGE_R(c,t,SV_PB_SMM_I(i))
#define F_PB_SMMI(e,t,i) C_PB_SMMI(e,t,i)

#define C_PB_SMMI_AP(c,t,i)C_STORAGE_R(c,t,SV_PB_SMMI_AP)
#define C_PB_SMMI_G(c,t,i)C_STORAGE_R_NV(c,t,SV_PB_SMMI_G(i))
#define C_PB_SMMI_RG(c,t,i)C_STORAGE_R_NV(c,t,SV_PB_SMMI_RG(i))
#define C_PB_SMMI_M1(c,t,i)C_STORAGE_R(c,t,SV_PB_SMMI_M1(i))
#define C_PB_SMMI_M2(c,t,i)C_STORAGE_R(c,t,SV_PB_SMMI_M2(i))
#define C_PB_SMMI_S(c,t,i)C_STORAGE_R(c,t,SV_PB_SMMI_S)
#define C_PB_SMMI_PS(c,t,i)C_STORAGE_R(c,t,SV_PB_SMMI_PS(i))
#define C_PB_SMMI_DIFF(c,t,i)C_STORAGE_R(c,t, (Svar)(SV_PB_SMM_DIFF_COEFF_0+i))
#define C_PB_SMM_IMB(c,t)C_STORAGE_R(c,t,SV_PB_SMM_IMB)

/* don't know if needed */
#define F_PB_SMMI_M1(c,t,i) C_PB_SMMI_M1(c,t,i)
#define F_PB_SMMI_M2(c,t,i) C_PB_SMMI_M2(c,t,i)
#define F_PB_SMMI_FLUX(c,t,i)
#define PB_SMM_BC_FLUX 0
#define PB_SMM_BC_VALUE 1

/* DQMOM */
#define DQMOM_T 1
#define C_PB_DQMOM(c,t) C_STORAGE_R(c,t,SV_PB_DQMOM)
#define F_PB_DQMOM(e,t) C_PB_DQMOM(e,t)

#define C_PB_DQMOM_AP(c,t) C_STORAGE_R(c,t,SV_PB_DQMOM_AP)
#define C_PB_DQMOM_G(c,t) C_STORAGE_R_NV(c,t,SV_PB_QMOM_G)
#define C_PB_DQMOM_RG(c,t) C_STORAGE_R_NV(c,t,SV_PB_DQMOM_RG)
#define C_PB_DQMOM_M1(c,t) C_STORAGE_R(c,t,SV_PB_DQMOM_M1)
#define C_PB_DQMOM_M2(c,t) C_STORAGE_R(c,t,SV_PB_DQMOM_M2)
#define C_PB_DQMOM_S(c,t) C_STORAGE_R(c,t,SV_PB_DQMOM_S)
#define C_PB_DQMOM_vof_src(c,t) C_STORAGE_R(c,t,SV_PB_DQMOM_vof_src)
#define C_PB_DQMOM_vof_src_ng(c,t) C_STORAGE_R(c,t,SV_PB_DQMOM_vof_src_ng)
#define C_PB_DQMOM_m4_src(c,t) C_STORAGE_R(c,t,SV_PB_DQMOM_m4_src)
#define C_PB_DQMOM_IMB(c,t) C_STORAGE_R(c,t,SV_PB_DQMOM_IMB)

/* don't know if needed */
#define F_PB_DQMOM_M1(c,t) C_PB_DQMOM_M1(c,t)
#define F_PB_DQMOM_M2(c,t) C_PB_DQMOM_M2(c,t)
#define PB_DQMOM_BC_FLUX 0
#define PB_DQMOM_BC_VALUE 1

/*struct to store the rpvar for pb qmom*/
typedef struct pb_param_struct
{
  int n_m; /* number of moments, set to be even number*/
  int n_m_half; /* half of number of moments*/

  int dmin;
  int dmax;
  int w_a_alg; /* pd and wheeler algorithm to find weights and abscissas
                       0 is pd, 1 is wheeler */
  cxboolean real_mom; /* check if moments are realizable */
  cxboolean real_mom_printout; /* print out the info about realizable moments */
  real zi_min; /* zeta min for realizable mom*/
  cxboolean zeta_scheme; /* use of zeta scheme*/
  /* real d; */
} PB_Param;


extern FLUENT_EXPORT void sg_pb_get_all_rp_and_domain_vars(Domain *domain);
extern FLUENT_EXPORT real get_m1_m2(cell_t c, Thread *t, real Re, real fxi);
extern FLUENT_EXPORT void Model_Initialize_pb(void);

extern FLUENT_EXPORT real Sauter_d(cell_t c, Thread *t);
FLUENT_EXPORT real gammp(real a, real x);
extern FLUENT_EXPORT real *compute_pbmom_coefficient(const char *i_m, real up_lim, int nm, real *mom);

#if RP_DOUBLE
#define PB_SMALL 1.e-40
#else
#define PB_SMALL 1.e-20
#endif

#define N_GEN_BU_MAX 2 /* max number of parameter sets for the generalized pdf */
#define N_ZPoints_Max 1000
#define BK_CHECK_P 0

/* static real inlet_outlet_MOM_flux(Domain *domain, Svar sv_v); */
void Unsteady_Adjust_QMOM_SMM(Domain *domain, int eqn, Svar sv_v, Svar sv_source, int ns);
void qmom_generalized_bu_pdf(Domain *domain, real bk_qmom_bu_pdf[]);
real sf_beta(real p, real q);
real pb_generalized_bu_pdf(real z, int n_gen_bu, real wi[], real pi[], real qi[], real ri[]);
void discrete_generalized_bu_pdf(Domain *domain, int n_gen_bu, real nik_pdf[][MAX_PB_DISC_EQNS],
                                 real wi[], real pi[], real qi[], real ri[]);
void pb_generalized_bu_pdf_inputs(Domain *domain, int n_gen_bu, real wi[], real pi[], real qi[], real ri[]);
void compute_generalized_bu_pdf_discrete_source(cell_t c, Thread *t, real nik_pdf[][MAX_PB_DISC_EQNS]);
void Calculate_PB_Sources_for_NITA(Domain *domain);
extern FLUENT_EXPORT cxboolean if_pb_qmom_phase_domain(Domain *subdomain);
/* DQMOM Section */
#if DQMOM_T
extern FLUENT_EXPORT cxboolean if_pb_dqmom_phase_domain(Domain *subdomain);
real j0_pb_mom(cell_t c, Thread *t);
real g_pb_mom(cell_t c, Thread *t, int i);
real beta_pb_mom(cell_t c, Thread *t, int i, int j);
cxboolean if_pb_dqmom(void);
extern FLUENT_EXPORT int
Gauss_Elimination_DQMOM(const int n_rows,
                        const int n_cols,
                        real A[], /* A[n_rows, n_rows] matrix (destroyed) */
                        real X[], /* X[n_rows, n_cols] solution matrix  */
                        real B[], /* B[n_rows, n_cols] source (destroyed) */
                        int swap_rows);
void compute_dqmom_an_and_bn(cell_t c, Thread *mt, /*mixture thread*/
                             real  l[], /* length */
                             real  w[], /* weights */
                             real xn[], /* solution an and bn */
                             int    nq, /* number of quadrature points */
                             int  ip[]); /* quadrature point index for phase */

FLUENT_EXPORT void InitializeDQMOMValues(void);
void DQMOM_Internal_Calculate_Mass_Transfer(Domain *domain);
#endif /* DQMOM_T */

extern FLUENT_EXPORT cxboolean phenomenon[4];
extern FLUENT_EXPORT cxboolean sg_pb_disc_inhomo;
extern FLUENT_EXPORT cxboolean sg_pb_disc_homo;
extern FLUENT_EXPORT cxboolean sg_pb_qmom;
extern FLUENT_EXPORT cxboolean sg_pb_smm;

#define C_PB_DISC_INHOMO_GR(c,t)C_STORAGE_R(c,t,SV_PB_DISC_INHOMO_GR)
#define C_PB_DISC_INHOMO_RPI_SRC(c,t)C_STORAGE_R(c,t,SV_PB_DISC_INHOMO_RPI_SRC)
#define C_PB_EXP(c,t) C_STORAGE_R(c,t,SV_PB_EXP)
#define C_PB_MT(c,t,i) C_STORAGE_R_XV(c,t,SV_PB_MT,i)
extern FLUENT_EXPORT void Add_PB_Mass_Transfer_and_Het_Rxn_Source (Domain *domain, int species_id, Svar sv, Svar sv_ap, Svar sv_s, cxboolean volume_source, cxboolean subtract_mass_source, int dir, Delta_Form df);
extern FLUENT_EXPORT void Free_PB_Mass_Transfer_List(void);
extern FLUENT_EXPORT int pb_domain_id(void);
extern FLUENT_EXPORT int min_dia_phase_boiling_pbm;
extern FLUENT_EXPORT cxboolean mp_pb_inhomo_rpi_boiling_src;
