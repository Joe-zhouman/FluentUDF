/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_TURB_KE_H
#define _FLUENT_TURB_KE_H

extern FLUENT_EXPORT int n_eas;

extern FLUENT_EXPORT cxboolean sg_rsm_kw_wilcox;   /* RSM with Std k-omega model (Wilcox) */

extern FLUENT_EXPORT Low_Re_Model_Type lowRe_model_Index; /* Index for low-Re k-epsilon model     */

extern FLUENT_EXPORT real M_Sakar_const;

extern FLUENT_EXPORT cxboolean M_turb_positive_linearization_separate;

extern FLUENT_EXPORT cxboolean M_kw_lowre_mod;
extern FLUENT_EXPORT cxboolean M_turb_compress_mod;
extern FLUENT_EXPORT cxboolean M_kw_shear_mod;
extern FLUENT_EXPORT cxboolean M_is_kw_any_sas_term_on;
extern FLUENT_EXPORT cxboolean M_is_turb_any_des_mode_on;
extern FLUENT_EXPORT cxboolean M_is_turb_any_sbes_mode_on;
extern FLUENT_EXPORT cxboolean M_solve_rans_for_sbes;

extern FLUENT_EXPORT cxboolean M_trans_udf_flength;
extern FLUENT_EXPORT cxboolean M_trans_udf_retheta_c;
extern FLUENT_EXPORT cxboolean M_trans_udf_retheta_t;

extern FLUENT_EXPORT cxboolean M_ke_sbes;
extern FLUENT_EXPORT cxboolean M_ke_sbes_allowed_models;

extern FLUENT_EXPORT cxboolean M_kw_linearize_diss_Newton;
extern FLUENT_EXPORT cxboolean M_kw_sst_lin_neg_Dw;
extern FLUENT_EXPORT real M_kw_sst_lim_Dw_nYw;

extern FLUENT_EXPORT real M_kw_beta_i;
extern FLUENT_EXPORT real M_kw_sig_k;
extern FLUENT_EXPORT real M_kw_sig_w;

extern FLUENT_EXPORT real M_bf_f1_sig_w2;

extern FLUENT_EXPORT cxboolean M_geko;
extern FLUENT_EXPORT cxboolean M_geko_enforce_wdf;
extern FLUENT_EXPORT cxboolean M_geko_bf_pre193;

extern FLUENT_EXPORT real M_intermit_sig;
extern FLUENT_EXPORT real M_retheta_sig;
extern FLUENT_EXPORT cxboolean M_trans_sst_kato_launder;
extern FLUENT_EXPORT cxboolean M_trans_sst_rghcor;
extern FLUENT_EXPORT cxboolean M_trans_sst_udf_geomrgh;

extern FLUENT_EXPORT int trans_one_eqn_dUdn_method;
extern FLUENT_EXPORT cxboolean M_trans_one_eqn_crossflow;

extern FLUENT_EXPORT cxboolean M_eles_dynamic_present;
extern FLUENT_EXPORT cxboolean M_eles_present;

extern FLUENT_EXPORT cxboolean M_les_wmles_SmnsOmg_r145;

extern FLUENT_EXPORT cxboolean M_sst_v61;

extern FLUENT_EXPORT real M_hyd_dia_fact;

extern FLUENT_EXPORT Turb_Model_Type mp_ke_type;
extern FLUENT_EXPORT Turb_Model_Type mp_rsm_type;
extern FLUENT_EXPORT Turb_Model_Type mp_les_type;

extern FLUENT_EXPORT cxboolean mp_mfluid_turb_mixt;

FLUENT_EXPORT Turb_Model_Type MP_Phase_Turb_Model(int phase);

FLUENT_EXPORT void Model_Initialize_ke(void);
FLUENT_EXPORT void Model_Initialize_evt(void);

FLUENT_EXPORT real get_transition_fss(real mu, real Rmag, real kt, real rho);

#endif /* _FLUENT_TURB_KE_H */

