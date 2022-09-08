/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#define C_IAC(c,t)   C_STORAGE_R(c,t,SV_IAC)
#define F_IAC(e,t) C_IAC(e,t)

#define C_IAC_AP(c,t)   C_STORAGE_R(c,t,SV_IAC_AP)
#define C_IAC_G(c,t)    C_STORAGE_R_NV(c,t,SV_IAC_G)
#define C_IAC_RG(c,t)   C_STORAGE_R_NV(c,t,SV_IAC_RG)
#define C_IAC_M1(c,t)   C_STORAGE_R(c,t,SV_IAC_M1)
#define C_IAC_M2(c,t)   C_STORAGE_R(c,t,SV_IAC_M2)
#define C_IAC_S(c,t)    C_STORAGE_R(c,t,SV_IAC_S)
#define C_IAC_DIFF(c,t)   C_STORAGE_R(c,t,SV_IAC_DIFF_COEFF)
#define C_IAC_IMB(c,t)   C_STORAGE_R(c,t,SV_IAC_IMB)
#define C_IAC_EXP(c,t)   C_STORAGE_R(c,t,SV_IAC_EXP)
/*#define C_IAC_FP(c,t)   C_STORAGE_R(c,t,SV_IAC_FP)
#define C_IAC_FP_G(c,t)   C_STORAGE_R_NV(c,t,SV_IAC_FP_G)*/

#define IAC_BC_FLUX 0
#define IAC_BC_VALUE 1

extern FLUENT_EXPORT void sg_iac_get_all_rp_and_domain_vars(Domain *domain);
extern FLUENT_EXPORT real IAC_Sauter_d(cell_t c, Thread *t);

/* declaration of functions */
static void add_iac_coal_breakup_nucl_sources(Domain *domain);
static void compute_iac_mp_correction(Domain *domain);
static void add_iac_mp_correction_sources(Domain *domain);
static void IAC_Unsteady_Sources(Domain *domain, Svar sv_v, Svar sv_ap, Svar sv_source);
static void fluid_interior_iac_coeffs(Thread *thread);
static void fluid_periodic_iac_coeffs(Thread *thread);
static void boundary_iac_coeffs(Thread *thread, int iac_bc_type, Profile iac,
                                cxboolean compute_coeffs, cxboolean inlet_diff);
static void IAC_Derivatives(Domain *domain);
static void Solve_IAC(Domain *domain);
static SV_Store_Type store_iac(Thread *t, Svar nv);
static int residual_iac(Domain *domain, Var_Attribute *sv, SV_Residual_Code code);
static void init_iac(Domain *domain, Var_Attribute *sv);
static void inquire_equations(Domain *domain, Inq_Eqn_Selector inq, Pointer *result);
cxboolean if_iac(void);
int iac_count(void);
cxboolean if_iac_on_domain(Domain *domain);

static real wik_epsilon(Thread *t, Thread *pt, cell_t c, Property *p, Property_ID pid);
static void hi_iac_breakage_source(Domain *domain);
static void hi_iac_coal_source(Domain *domain);
static void udf_iac_cb_source(Domain *domain, Property *p, Property_ID pid);
static void udf_iac_nucleation_source(Domain *domain, Property *p, Property_ID pid);
static void constant_iac_cb_source(Domain *domain, real s);
static void constant_iac_nucleation_source(Domain *domain, real J0);
static void add_iac_breakup_sources(Domain *domain);
static void add_iac_coal_sources(Domain *domain);
static void add_iac_nucleation_sources(Domain *domain);
static void ik_iac_coal_source(Domain *domain);
static void ik_iac_breakage_source(Domain *domain);
static real iac_dissipation_rate(Domain *domain, Thread *t, Thread *pt, Thread *mt, cell_t c);
static void ym_iac_coalescence_source(Domain *domain);
static void ym_iac_breakage_source(Domain *domain);
static void ym_iac_boiling_nucleation_source(Domain *domain);

void Model_Initialize_iac(void);

#if RP_DOUBLE
#define PB_SMALL 1.e-20
#else
#define PB_SMALL 1.e-10
#endif


