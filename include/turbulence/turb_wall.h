/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

extern FLUENT_EXPORT cxboolean M_wf_thermal_jaya;
extern FLUENT_EXPORT cxboolean M_wf_thermal_jaya_mod;
extern FLUENT_EXPORT cxboolean M_wf_utau_Niter;
extern FLUENT_EXPORT cxboolean M_wf_prg;
extern FLUENT_EXPORT cxboolean M_wf_cmp;
extern FLUENT_EXPORT cxboolean M_wf_htf;
extern FLUENT_EXPORT cxboolean M_wf_trn;
extern FLUENT_EXPORT cxboolean M_wf_new_omega;
extern FLUENT_EXPORT cxboolean M_wf_new_rough_wall;
extern FLUENT_EXPORT cxboolean M_wf_roughness_colebrook;
extern FLUENT_EXPORT cxboolean M_wf_thermal_han_and_reitz;
extern FLUENT_EXPORT cxboolean M_ke_k_prev_it;
extern FLUENT_EXPORT cxboolean M_turb_wf_ustar_limiter;

#define SMALL_WF_EFFECT (1.e-5) /* Must be > EPSILON/Emod2 to ensure S0 > 1 */

FLUENT_EXPORT real
udf_Wall_Func(face_t f, Thread *t, cell_t c0, Thread *t0,
              Wall_Function_Ret_Val_Type wf_ret,
              real rkcon, real kPlus, real yPlus);

