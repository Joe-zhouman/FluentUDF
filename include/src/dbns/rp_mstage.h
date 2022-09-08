/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_RP_MSTAGE_H
#define _FLUENT_RP_MSTAGE_H

#include "dll.h"

FLUENT_EXPORT void Solve_Coupled(Domain *);
FLUENT_EXPORT void Coupled_Face_Flux_n_Mass_Imbalance(Domain *);
FLUENT_EXPORT void Multi_Stage(Domain *, int code, int level);
FLUENT_EXPORT void Limit_Solution(Domain *);
FLUENT_EXPORT void Viscous_Residuals(Domain *, cxboolean);
FLUENT_EXPORT void Update_Time_Step(Domain *, real cfl, real cfl_solid);
FLUENT_EXPORT void Save_Residuals(Domain *);

FLUENT_EXPORT void Update_Global_Time_Step(Domain *);
FLUENT_EXPORT void update_uref2(Domain *);
FLUENT_EXPORT cxboolean check_if_at_time_interval(void);    /* WW */

FLUENT_EXPORT void cell_precon_matrix(cell_t c, Thread *thread, cxboolean p, real g[]);

FLUENT_EXPORT void decomp(int n, real ul[]);
FLUENT_EXPORT void bfsubs(int n, real ul[], real rhs[], real sol[], real work[]);


FLUENT_EXPORT void rotational_sources(Domain *);
FLUENT_EXPORT void rp_user_sources(Domain *);
FLUENT_EXPORT void rp_dynmesh_sources(Domain *);
FLUENT_EXPORT void species_sources(Domain *, cxboolean);
FLUENT_EXPORT void dpm_sources(Domain *);
FLUENT_EXPORT void crev_sources(Domain *);

FLUENT_EXPORT void init_solution_limits(void);

#if RP_STIFF_CHEM
FLUENT_EXPORT int Limit_Chemical_Time_Step(cell_t c, Thread *thread, real jac[], int n,
                                           real dt_ratio, int spe_verb,
                                           real *g, real *gi, double *ar,
                                           double *ai, double *wr, double *wi, double *zr,
                                           double *zi, double *fv1, double *fv2, double *fv3);
FLUENT_EXPORT void Apply_Chemical_Time_Step_Scale_Factor(Domain *domain);
#endif

FLUENT_EXPORT real Rho_P     (cell_t, Thread *, Material *);
FLUENT_EXPORT real Enthalpy_P(cell_t, Thread *, Material *);

FLUENT_EXPORT real Rho_T     (cell_t, Thread *, Material *, real yi[], real rho_i[]);
FLUENT_EXPORT real Enthalpy_T(cell_t, Thread *, Material *, real yi[], real rho_i[]);

FLUENT_EXPORT void Rho_Yi     (cell_t, Thread *, Material *, real rho_i[], real rho_yi[]);
FLUENT_EXPORT void Enthalpy_Yi(cell_t, Thread *, Material *, real rho_yi[], real h_yi[]);

extern FLUENT_EXPORT cxboolean dissipation_stage_p;
extern FLUENT_EXPORT cxboolean dissipation_store_fw;
extern FLUENT_EXPORT cxboolean viscous_stage_p;
extern FLUENT_EXPORT cxboolean dbns_enhanced_time_scheme_p;

enum
{
  ROE_FDS = 0,
  AUSM,
  LROE_FDS,
  AUSMPUP /*hooking up the AUSMpUP flux*/
};

#define ROBUST_CDBS 1 /*set to 1 to activate robustness changes */
#ifndef ROBUST_CDBS
# define ROBUST_CDBS 0
#endif

#if ROBUST_CDBS && 0 /* to be activated later, just remove "&& 0" */

#define F_UREF2(uref2_0, uref2_1) MAX((uref2_0),(uref2_1))

#define F_ALPHA(ideal_gas,uref2_0,c2_0,uref2_1, c2_1) \
  ((ideal_gas) ? \
    (1.0 - MAX((uref2_0)/(c2_0),(uref2_1)/(c2_1)))*0.5 : 0.5)

#else /* the original treatment */

#define F_UREF2(uref2_0, uref2_1) (((uref2_0) + (uref2_1))*0.5)

#define F_ALPHA(ideal_gas,uref2_0,c2_0,uref2_1, c2_1) \
  ((ideal_gas) ? \
    (1.0 - ((uref2_0)/(c2_0) +(uref2_1)/(c2_1))*0.5)*0.5 : 0.5)

#endif


# define COUPLED_VARS(ext) \
    SV_P_##ext, \
    COUPLED_VARS_WV(ext)

# define COUPLED_VARS_WV(ext) \
    SV_U_##ext, \
    SV_V_##ext, \
    SV_W_##ext, \
    SV_T_##ext, \
    COUPLED_VARS_SPE(ext)

# define COUPLED_VARS_SPE(ext) \
    SV_Y_##ext

/* all these variables are necessary in rp_mstage.h */

#endif /* _FLUENT_RP_MSTAGE_H */
