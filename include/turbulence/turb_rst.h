/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

extern FLUENT_EXPORT int n_rse;
extern FLUENT_EXPORT const int stress_tensor_ii[6];
extern FLUENT_EXPORT const int stress_tensor_jj[6];

extern FLUENT_EXPORT cxboolean drsm_tke_solve;
extern FLUENT_EXPORT cxboolean drsm_ps_wall;
extern FLUENT_EXPORT cxboolean drsm_ssg_ps;
extern FLUENT_EXPORT cxboolean drsm_omega_based;
extern FLUENT_EXPORT cxboolean drsm_bsl_based;
extern FLUENT_EXPORT cxboolean drsm_omega_or_bsl_based;
extern FLUENT_EXPORT cxboolean drsm_boundary_tke_updated_before_omega;
extern FLUENT_EXPORT real M_coeff_drsm_omega_or_bsl_mu_dok;

#if !RP_HOST
extern FLUENT_EXPORT void Solve_ke_rst (Domain *);
extern FLUENT_EXPORT void Solve_k_omega_rst (Domain *);
#endif

FLUENT_EXPORT void Model_Initialize_rst(void);
FLUENT_EXPORT void Project_Rstress_Onto_Symmetry(face_t f, Thread *t, real CRST[6], int n_rse, real FRST[6]);
FLUENT_EXPORT void update_boundary_tke(Domain *domain, Svar sv_phi);

/*finding RST components*/
#if RP_3D
#define IS_RST_COMPONENT(var)(var == SV_RUU || var == SV_RVV || var == SV_RUV \
            || var == SV_RUW || var == SV_RVW || var == SV_RWW)
#else
#define IS_RST_COMPONENT(var)(var == SV_RUU || var == SV_RVV || var == SV_RUV || var == SV_RWW)
#if (sg_swirl && RP_AXI)
#define IS_RST_COMPONENT(var)(var == SV_RUU || var == SV_RVV || var == SV_RUV \
            || var == SV_RUW || var == SV_RVW || var == SV_RWW)
#endif
#endif
