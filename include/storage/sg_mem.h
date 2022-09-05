/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SG_MEM_H
#define _FLUENT_SG_MEM_H

#define C_MASS_IMBALANCE(c,t)FAST_C_STORAGE_R(c,t,SV_MASS_IMBALANCE)
#define C_SOURCE_MASS_USER(c,t)(NULLP(THREAD_STORAGE(t,SV_S_MASS_USER))? \
                                0.0: FAST_C_STORAGE_R(c,t,SV_S_MASS_USER))
#define C_MASS_SOURCE(c,t)FAST_C_STORAGE_R(c,t,SV_MASS_SOURCE)

#define C_U_S(c,t)FAST_C_STORAGE_R(c,t,SV_U_S)
#define C_V_S(c,t)FAST_C_STORAGE_R(c,t,SV_V_S)
#define C_W_S(c,t)FAST_C_STORAGE_R(c,t,SV_W_S)
#define C_T_S(c,t)FAST_C_STORAGE_R(c,t,SV_T_S)
#define C_T_MAXWELL(c,t)C_STORAGE_R(c,t,SV_T_MAXWELL)
#define F_T_MAXWELL(c,t)F_STORAGE_R(c,t,SV_T_MAXWELL)
#define C_H_S(c,t)FAST_C_STORAGE_R(c,t,SV_H_S)
#define C_NUT_S(c,t)FAST_C_STORAGE_R(c,t,SV_NUT_S)
#define C_K_S(c,t)FAST_C_STORAGE_R(c,t,SV_K_S)
#define C_D_S(c,t)FAST_C_STORAGE_R(c,t,SV_D_S)
#define C_O_S(c,t)FAST_C_STORAGE_R(c,t,SV_O_S)
#define C_YI_0_S(c,t)FAST_C_STORAGE_R(c,t,SV_Y_0_S)
#define C_YI_S(c,t,i)C_STORAGE_R_XV(c,t,SV_Y_S,i)
#define C_UDSI_S(c,t,i)C_STORAGE_R(c,t,SV_UDS_I(i)+SV_UDS_0_S-SV_UDS_0)
#define C_ADSI_S(c,t,i)C_STORAGE_R(c,t,SV_ADS_I(i)+SV_ADS_0_S-SV_ADS_0)
#define C_CDS_S(c,t)C_STORAGE_R(c,t,SV_CDS_S)

#define C_P_AP(c,t)FAST_C_STORAGE_R(c,t,SV_P_AP)
#define C_U_AP(c,t)FAST_C_STORAGE_R(c,t,SV_U_AP)
#define C_V_AP(c,t)FAST_C_STORAGE_R(c,t,SV_V_AP)
#define C_W_AP(c,t)FAST_C_STORAGE_R(c,t,SV_W_AP)
#define C_T_AP(c,t)FAST_C_STORAGE_R(c,t,SV_T_AP)
#define C_H_AP(c,t)FAST_C_STORAGE_R(c,t,SV_H_AP)
#define C_NUT_AP(c,t)FAST_C_STORAGE_R(c,t,SV_NUT_AP)
#define C_K_AP(c,t)FAST_C_STORAGE_R(c,t,SV_K_AP)
#define C_D_AP(c,t)FAST_C_STORAGE_R(c,t,SV_D_AP)
#define C_O_AP(c,t)FAST_C_STORAGE_R(c,t,SV_O_AP)
#define C_YI_0_AP(c,t)FAST_C_STORAGE_R(c,t,SV_Y_0_AP)
#define C_YI_AP(c,t,i)C_STORAGE_R_XV(c,t,SV_Y_AP,i)
#define C_UDSI_AP(c,t,i)C_STORAGE_R(c,t,SV_UDSI_AP)
#define C_ADSI_AP(c,t,i)C_STORAGE_R(c,t,SV_ADSI_AP)
#define C_CDS_AP(c,t)C_STORAGE_R(c,t,SV_CDS_AP)
#define C_EPDF_S(c,t,ns) C_STORAGE_R(c,t,SV_EPDF_0_S)
#define C_EPDF_AP(c,t,ns) C_STORAGE_R(c,t,SV_EPDF_0_AP)
#define C_EPDF_H_S(c,t) C_STORAGE_R(c,t,SV_EPDF_H_S)
#define C_EPDF_H_AP(c,t) C_STORAGE_R(c,t,SV_EPDF_H_AP)


#define C_VV_PREV(c,t) FAST_C_STORAGE_R_NV(c,t,SV_V_PREV)

#define C_BF_VV(c,t)FAST_C_STORAGE_R_NV(c,t,SV_BF_V)
#define C_BF_U(c,t)C_BF_VV(c,t)[0]
#define C_BF_V(c,t)C_BF_VV(c,t)[1]
#if RP_3D
# define C_BF_W(c,t)C_BF_VV(c,t)[2]
#endif

#define C_BFP_VV(c,t)FAST_C_STORAGE_R_NV(c,t,SV_BFP_V)
#define C_BFP_U(c,t)C_BFP_VV(c,t)[0]
#define C_BFP_V(c,t)C_BFP_VV(c,t)[1]
#if RP_3D
# define C_BFP_W(c,t)C_BFP_VV(c,t)[2]
#endif

#define C_SA_VV(c,t)FAST_C_STORAGE_R_NV(c,t,SV_SA_V)
#define C_SA_U(c,t)C_SA_VV(c,t)[0]
#define C_SA_V(c,t)C_SA_VV(c,t)[1]
#if RP_3D
# define C_SA_W(c,t)C_SA_VV(c,t)[2]
#endif

/**** JS US 48617 *******************************/

#define C_VM_VV(c,t)C_STORAGE_R_NV(c,t,SV_VM_V)
#define C_VM_U(c,t)C_VM_VV(c,t)[0]
#define C_VM_V(c,t)C_VM_VV(c,t)[1]
#if RP_3D
# define C_VM_W(c,t)C_VM_VV(c,t)[2]
#endif

#define C_VM_VV_TMP(c,t)C_STORAGE_R_NV(c,t,SV_VM_V_TMP)
#define C_VM_U_TMP(c,t)C_VM_VV_TMP(c,t)[0]
#define C_VM_V_TMP(c,t)C_VM_VV_TMP(c,t)[1]
#if RP_3D
# define C_VM_W_TMP(c,t)C_VM_VV_TMP(c,t)[2]
#endif

#define C_VMASS_VFLUX(c,t,i)FAST_C_STORAGE_R_XV(c,t,SV_VMASS_VFLUX,i)

/************************************************/

#define C_DP(c,t) FAST_C_STORAGE_R_NV(c,t,SV_P_G)   /* Obsolete. 
                                                  will be replaced by C_P_G(c,t), see mem.h */
#define C_FMEAN(c,t)FAST_C_STORAGE_R(c,t,SV_FMEAN)
#define C_FMEAN_AP(c,t)FAST_C_STORAGE_R(c,t,SV_FMEAN_AP)
#define C_FMEAN_S(c,t)FAST_C_STORAGE_R(c,t,SV_FMEAN_S)
#define F_FMEAN(e,t) C_FMEAN(e,t)

#define C_FMEAN2(c,t)C_STORAGE_R(c,t,SV_FMEAN2)
#define C_FMEAN2_AP(c,t)C_STORAGE_R(c,t,SV_FMEAN2_AP)
#define C_FMEAN2_S(c,t)C_STORAGE_R(c,t,SV_FMEAN2_S)
#define F_FMEAN2(e,t) C_FMEAN2(e,t)

#define C_FVAR(c,t)FAST_C_STORAGE_R(c,t,SV_FVAR)
#define C_FVAR_AP(c,t)FAST_C_STORAGE_R(c,t,SV_FVAR_AP)
#define C_FVAR_S(c,t)FAST_C_STORAGE_R(c,t,SV_FVAR_S)
#define F_FVAR(e,t) C_FVAR(e,t)

#define C_FVAR2(c,t)C_STORAGE_R(c,t,SV_FVAR2)
#define C_FVAR2_AP(c,t)C_STORAGE_R(c,t,SV_FVAR2_AP)
#define C_FVAR2_S(c,t)C_STORAGE_R(c,t,SV_FVAR2_S)
#define F_FVAR2(e,t) C_FVAR2(e,t)

#define C_FVAR_PROD(c,t)FAST_C_STORAGE_R(c,t,SV_FVAR_PROD)
#define C_FVAR2_PROD(c,t)C_STORAGE_R(c,t,SV_FVAR2_PROD)

#define C_TVAR(c,t)C_STORAGE_R(c,t,SV_TVAR)
#define C_TVAR_AP(c,t)C_STORAGE_R(c,t,SV_TVAR_AP)
#define C_TVAR_S(c,t)C_STORAGE_R(c,t,SV_TVAR_S)
#define F_TVAR(e,t) C_TVAR(e,t)
#define C_TVAR_PROD(c,t)C_STORAGE_R(c,t,SV_TVAR_PROD)

/* Unsteady Flamelet (and Constructed PDF) model */
#define F_UFLA_YI(e,t,i) C_UFLA_YI(e,t,i)
#define C_UFLA_YI(c,t,i) C_STORAGE_R(c,t,SV_UFLA_YI(i))
#define C_UFLA_YI_AP(c,t) C_STORAGE_R(c,t,SV_UFLA_YI_0_AP)
#define C_UFLA_YI_S(c,t) C_STORAGE_R(c,t,SV_UFLA_YI_0_S)
#define C_UFLA_YI_I_NUM(c,t,i,ns) C_STORAGE_R_XV(c,t,(Svar) (SV_UFLA_YI_I_NUM_0+i),ns)
#define C_UFLA_TEMP_I_NUM(c,t,i) C_STORAGE_R(c,t,(Svar) (SV_UFLA_TEMP_I_NUM_0+i))
#define C_UFLA_DEN_I(c,t,i) C_STORAGE_R(c,t, (Svar) (SV_UFLA_DEN_I_0+i))

/* electro-chemistry */
#define F_PHI_1(e,t) C_PHI_1(e,t)
#define C_PHI_1(c,t) C_STORAGE_R(c,t,SV_PHI_1)
#define F_PHI_2(e,t) C_PHI_2(e,t)
#define C_PHI_2(c,t) C_STORAGE_R(c,t,SV_PHI_2)
#define C_TRANSFER_CURRENT(c,t) C_STORAGE_R(c,t,SV_TRANSFER_CURRENT)
#define C_CURRENT(c,t) C_STORAGE_R(c,t,SV_CURRENT)
#define C_OVER_POTENTIAL(c,t) C_STORAGE_R(c,t,SV_OVER_POTENTIAL)
#define C_JOULE_HEATING(c,t) C_STORAGE_R(c,t,SV_JOULE_HEATING)
#define C_ELECTRO_VOF_AP(c,t) C_STORAGE_R(c,t,SV_ELECTRO_VOF_AP)
#define C_OSMOTIC_DRAG(c,t) C_STORAGE_R(c,t,SV_OSMOTIC_DRAG)
#define C_CP_COEFF(c,t) C_STORAGE_R(c,t,SV_CP_COEFF)
#define C_LITHIUM(c,t) C_STORAGE_R(c,t,SV_LITHIUM)
#define F_LITHIUM(e,t) C_LITHIUM(e,t)

#define C_BATTERY_CURRENT(c,t) C_STORAGE_R(c,t,SV_BATTERY_CURRENT)
#define C_BATTERY_CURR_X(c,t) C_STORAGE_R(c,t,SV_BATTERY_CURR_X)
#define C_BATTERY_CURR_Y(c,t) C_STORAGE_R(c,t,SV_BATTERY_CURR_Y)
#define C_BATTERY_CURR_Z(c,t) C_STORAGE_R(c,t,SV_BATTERY_CURR_Z)
#define C_BATTERY_OHMIC_SOURCE(c,t) C_STORAGE_R(c,t,SV_BATTERY_OHMIC_SOURCE)
#define C_BATTERY_ECHEM_SOURCE(c,t) C_STORAGE_R(c,t,SV_BATTERY_ECHEM_SOURCE)
#define C_BATTERY_ACTIVATION(c,t) C_STORAGE_R(c,t,SV_BATTERY_ACTIVATION)
#define C_BATTERY_DISCHARGE_DEPTH(c,t) C_STORAGE_R(c,t,SV_BATTERY_DISCHARGE_DEPTH)
#define C_BATTERY_CURR_SOURCE(c,t) C_STORAGE_R(c,t,SV_BATTERY_CURR_SOURCE)
#define C_BATTERY_CURR_PX(c,t) C_STORAGE_R(c,t,SV_BATTERY_CURR_PX)
#define C_BATTERY_CURR_PY(c,t) C_STORAGE_R(c,t,SV_BATTERY_CURR_PY)
#define C_BATTERY_CURR_PZ(c,t) C_STORAGE_R(c,t,SV_BATTERY_CURR_PZ)
#define C_BATTERY_CURR_NX(c,t) C_STORAGE_R(c,t,SV_BATTERY_CURR_NX)
#define C_BATTERY_CURR_NY(c,t) C_STORAGE_R(c,t,SV_BATTERY_CURR_NY)
#define C_BATTERY_CURR_NZ(c,t) C_STORAGE_R(c,t,SV_BATTERY_CURR_NZ)
#define C_BATTERY_SHORT_R(c,t) C_STORAGE_R(c,t,SV_BATTERY_SHORT_R)
#define C_BATTERY_SHORT_CURR(c,t) C_STORAGE_R(c,t,SV_BATTERY_SHORT_CURR)
#define C_BATTERY_CURR_ECHEM(c,t) C_STORAGE_R(c,t,SV_BATTERY_CURR_ECHEM)
#define C_BATTERY_SHORT_SOURCE(c,t) C_STORAGE_R(c,t,SV_BATTERY_SHORT_SOURCE)
#define C_BATTERY_ROM_PHI_P(c,t) C_STORAGE_R(c,t,SV_BATTERY_ROM_PHI_P)
#define C_BATTERY_ROM_PHI_N(c,t) C_STORAGE_R(c,t,SV_BATTERY_ROM_PHI_N)
#define C_BATTERY_ROM_JH(c,t) C_STORAGE_R(c,t,SV_BATTERY_ROM_JH)
#define C_BATTERY_SEI_REACTION(c,t) C_STORAGE_R(c,t,SV_BATTERY_SEI_REACTION)
#define C_BATTERY_PE_REACTION(c,t) C_STORAGE_R(c,t,SV_BATTERY_PE_REACTION)
#define C_BATTERY_NE_REACTION(c,t) C_STORAGE_R(c,t,SV_BATTERY_NE_REACTION)
#define C_BATTERY_E_REACTION(c,t) C_STORAGE_R(c,t,SV_BATTERY_E_REACTION)
#define C_BATTERY_ISC_REACTION(c,t) C_STORAGE_R(c,t,SV_BATTERY_ISC_REACTION)
#define C_BATTERY_ABUSE_SOURCE(c,t) C_STORAGE_R(c,t,SV_BATTERY_ABUSE_SOURCE)
#define C_BATTERY_PHI_SOURCE(c,t) C_STORAGE_R(c,t,SV_BATTERY_PHI_SOURCE)
#define C_BATTERY_PHI_AP(c,t) C_STORAGE_R(c,t,SV_BATTERY_PHI_AP)
#define C_BATTERY_T_SOURCE(c,t) C_STORAGE_R(c,t,SV_BATTERY_T_SOURCE)
#define C_BATTERY_CELL_U(c,t) C_STORAGE_R(c,t,SV_BATTERY_CELL_U)
#define C_BATTERY_CELL_R(c,t) C_STORAGE_R(c,t,SV_BATTERY_CELL_R)
#define C_BATTERY_CLUSTER(c,t) C_STORAGE_R(c,t,SV_BATTERY_CLUSTER)
#define C_BATTERY_CLUSTER_ID(c,t) C_STORAGE_I(c,t,SV_BATTERY_CLUSTER_ID)
#define C_BATTERY_SWELL_N_REF(c,t) C_STORAGE_R_NV(c,t,SV_BATTERY_SWELL_N_REF)
#define C_BATTERY_SWELL_N_DEF(c,t) C_STORAGE_R_NV(c,t,SV_BATTERY_SWELL_N_DEF)
#define C_BATTERY_SWELL_EPSILON_1D(c,t) C_STORAGE_R(c,t,SV_BATTERY_SWELL_EPSILON_1D)
#define C_BATTERY_TOTAL_EPSILON_1D(c,t) C_STORAGE_R(c,t,SV_BATTERY_TOTAL_EPSILON_1D)
#define C_BATTERY_TOTAL_SIGMA_1D(c,t) C_STORAGE_R(c,t,SV_BATTERY_TOTAL_SIGMA_1D)
#define C_BATTERY_TOTAL_SIGMA_1D_OLD(c,t) C_STORAGE_R(c,t,SV_BATTERY_TOTAL_SIGMA_1D_OLD)
#define F_BATTERY_ROM_PHI_P(e,t) C_BATTERY_ROM_PHI_P(e,t)
#define F_BATTERY_ROM_PHI_N(e,t) C_BATTERY_ROM_PHI_N(e,t)

/* premixed combustion */

#define C_PREMIXC(c,t)FAST_C_STORAGE_R(c,t,SV_PREMIXC)
#define C_PREMIXC_AP(c,t)FAST_C_STORAGE_R(c,t,SV_PREMIXC_AP)
#define C_PREMIXC_S(c,t)FAST_C_STORAGE_R(c,t,SV_PREMIXC_S)
#define F_PREMIXC(e,t) C_PREMIXC(e,t)
#define C_PREMIXC_RATE(c,t)FAST_C_STORAGE_R(c,t,SV_PREMIXC_RATE)
#define C_PREMIXC_T(c,t)C_STORAGE_R(c,t,SV_PREMIXC_T)
#define C_PREMIXC_GMAG(c,t)FAST_C_STORAGE_R(c,t,SV_PREMIXC_GMAG)

#define C_TSS_SCALAR(c,t,ns)C_STORAGE_R(c,t,(Svar) (SV_TSS_SCALAR_0+ns))
#define C_TSS_SCALAR_AP(c,t)C_STORAGE_R(c,t,SV_TSS_SCALAR_AP)
#define C_TSS_SCALAR_S(c,t)C_STORAGE_R(c,t,SV_TSS_SCALAR_S)

#define C_TSS_FWD_RATE(c,t,ns)C_STORAGE_R(c,t,(Svar) (SV_TSS_SCALAR_FWD_RATE_0 + ns))
#define C_TSS_REV_RATE(c,t,ns)C_STORAGE_R(c,t,(Svar) (SV_TSS_SCALAR_REV_RATE_0 + ns))
#define C_TSS_NET_RATE(c,t,ns)C_STORAGE_R(c,t,(Svar) (SV_TSS_SCALAR_NET_RATE_0 + ns))

/* rsm */

#define C_RUU(c,t)FAST_C_STORAGE_R(c,t,SV_RUU)
#define C_RVV(c,t)FAST_C_STORAGE_R(c,t,SV_RVV)
#define C_RWW(c,t)FAST_C_STORAGE_R(c,t,SV_RWW)
#define C_RUV(c,t)FAST_C_STORAGE_R(c,t,SV_RUV)
#define C_RVW(c,t)FAST_C_STORAGE_R(c,t,SV_RVW)
#define C_RUW(c,t)FAST_C_STORAGE_R(c,t,SV_RUW)

#define F_RVW(e,t) C_RVW(e,t)
#define F_RUW(e,t) C_RUW(e,t)

#define C_RST(c,t,i)C_STORAGE_R(c,t,SV_RST(SV_RUU,i))
#define F_RST(e,t,i) C_RST(e,t,i)

#define C_STORAGE_R_RST(c,t,n,i)(((T_STORAGE_R_RST(t,n))[c])[i])

#define C_RST_AP(c,t,i)C_STORAGE_R(c,t,SV_RST(SV_RUU_AP,i))
#define C_RST_S(c,t,i)C_STORAGE_R(c,t,SV_RST(SV_RUU_S,i))
#define C_RST_CONV_S(c,t,i)C_STORAGE_R_RST(c,t,SV_RST_DEFERRED_CONVECTION_S,i)
#define C_RST_DIFF_S(c,t,i)C_STORAGE_R_RST(c,t,SV_RST_DEFERRED_DIFFUSION_S,i)
#define C_RST_RG(c,t,i)C_STORAGE_R_NV(c,t,SV_RST(SV_RUU_RG,i))
#define C_RST_G(c,t,i)C_STORAGE_R_NV(c,t,SV_RST(SV_RUU_G,i))
#define C_TKE(c,t)((C_RUU(c,t)+C_RVV(c,t)+C_RWW(c,t))*0.5)
#define C_WALL_DIST_G(c,t)C_STORAGE_R_NV(c,t,SV_WALL_DIST_G)
#define C_WALL_DIST_RG(c,t)FAST_C_STORAGE_R_NV(c,t,SV_WALL_DIST_RG)
#define C_WALL_NORMAL(c,t)FAST_C_STORAGE_R_NV(c,t,SV_WALL_NORMAL)

/* swirl */

#define C_WSWIRL(c,t)FAST_C_STORAGE_R(c,t,SV_W)
#define C_WSWIRL_AP(c,t)FAST_C_STORAGE_R(c,t,SV_W_AP)
#define C_WSWIRL_S(c,t)FAST_C_STORAGE_R(c,t,SV_W_S)

#define C_P1(c,t)FAST_C_STORAGE_R(c,t,SV_P1)
#define C_P1_AP(c,t)FAST_C_STORAGE_R(c,t,SV_P1_AP)
#define C_P1_S(c,t)FAST_C_STORAGE_R(c,t,SV_P1_S)
#define C_P1_IRRAD(c,t,nb)C_STORAGE_R_XV(c,t,SV_P1_IRRAD,nb)

#define WALL_G_INNER(f,t)FAST_F_STORAGE_R(f,t,SV_WALL_G_INNER)
#define WALL_G_OUTER(f,t)F_STORAGE_R(f,t,SV_WALL_G_OUTER) /* same as F_P1(f,t) */
#define WALL_G_OUTER_IRRAD(f,t,nb)F_STORAGE_R_XV(f,t,SV_WALL_G_OUTER_IRRAD,nb) /* same as F_P1_IRRAD(f,t,nb) */

#define C_RNG_ALPHA(c,t)FAST_C_STORAGE_R(c,t,SV_RNG_ALPHA)
#define C_PRODUCTION(c,t)FAST_C_STORAGE_R(c,t,SV_PRODUCTION)
#define C_PRODUCTION_L(c,t)C_STORAGE_R(c,t,SV_PRODUCTION_L)
#define C_BUOY_PROD(c,t) FAST_C_STORAGE_R(c,t,SV_BUOY_PROD)
#define C_BSL_SST_F1(c,t)FAST_C_STORAGE_R(c,t,SV_BSL_SST_F1)
#define C_GEKO_CSEP(c,t)C_STORAGE_R(c,t,SV_GEKO_CSEP)
#define C_GEKO_CNW(c,t)C_STORAGE_R(c,t,SV_GEKO_CNW)
#define C_GEKO_CMIX(c,t)C_STORAGE_R(c,t,SV_GEKO_CMIX)
#define C_GEKO_BF(c,t)C_STORAGE_R(c,t,SV_GEKO_BF)
#define C_K_PREV_IT(c,t) C_STORAGE_R(c,t,SV_K_PREV_IT)
#define C_SBES_BF(c,t)C_STORAGE_R(c,t,SV_SBES_BF)
#define C_D_DENSITY(c,t) FAST_C_STORAGE_R_NV(c,t,SV_DENSITY_G) /* Obsolete. 
                                                             Has ben replaced by C_R_G(c,t),
                                                             see mem.h*/
#define C_REF_INDEX(c,t,nb)FAST_C_STORAGE_R_XV(c,t,SV_REF_INDEX,nb)
#define C_ABS_COEFF(c,t)FAST_C_STORAGE_R(c,t,SV_ABS_COEFF)
#define C_PDF_DEPARTURE_ENTHALPY(c,t)(M_pdf_real_gas && SV_INITIALIZED_P(t,SV_PDF_DEPARTURE_ENTHALPY)) ?\
 C_STORAGE_R(c,t,SV_PDF_DEPARTURE_ENTHALPY): 0.
#define C_PDF_DEPARTURE_ENTHALPY_U(c,t)(M_pdf_real_gas && sg_par_premix && SV_INITIALIZED_P(t,SV_PDF_DEPARTURE_ENTHALPY_U)) ?\
 C_STORAGE_R(c,t,SV_PDF_DEPARTURE_ENTHALPY_U): 0.
#define C_PDF_H2O(c,t)C_STORAGE_R(c,t,SV_PDF_H2O)
#define C_PDF_CO2(c,t)C_STORAGE_R(c,t,SV_PDF_CO2)
#define C_BAND_ABS_COEFF(c,t,nb)C_STORAGE_R_XV(c,t,SV_BAND_ABS_COEFF,nb)
#define C_SCAT_COEFF(c,t)FAST_C_STORAGE_R(c,t,SV_SCAT_COEFF)

#define C_LAM_FLAME_SPEED(c,t)(NULLP(THREAD_STORAGE(t,SV_LAM_FLAME_SPEED)) ?\
        THREAD_PROP(t,PROP_premix_laminar_speed,0) :\
        FAST_C_STORAGE_R(c,t,SV_LAM_FLAME_SPEED))
#define C_LAM_FLAME_THICK(c,t)(NULLP(THREAD_STORAGE(t,SV_LAM_FLAME_THICK)) ?\
        THREAD_PROP(t,PROP_premix_laminar_thick,0) :\
        C_STORAGE_R(c,t,SV_LAM_FLAME_THICK))
#define C_CRITICAL_STRAIN_RATE(c,t)(NULLP(THREAD_STORAGE(t,SV_CRITICAL_STRAIN_RATE)) ?\
        THREAD_PROP(t,PROP_premix_critical_strain,0) :\
        C_STORAGE_R(c,t,SV_CRITICAL_STRAIN_RATE))
#define C_PREMIX_ADIABATIC_TEMP(c,t)(NULLP(THREAD_STORAGE(t,SV_PREMIX_ADIABATIC_TEMP)) ?\
        THREAD_PROP(t,PROP_premix_adiabatic_temp,0) :\
        C_STORAGE_R(c,t,SV_PREMIX_ADIABATIC_TEMP))
#define C_PREMIX_FUEL_MF(c,t)(NULLP(THREAD_STORAGE(t,SV_PREMIX_FUEL_MF)) ?\
        THREAD_PROP(t,PROP_premix_unburnt_fuel_mf,0) :\
        C_STORAGE_R(c,t,SV_PREMIX_FUEL_MF))

#define C_VGS_DTRM(c,t)C_STORAGE_R(c,t,SV_VGS_DTRM)
#define C_VGF_DTRM(c,t)C_STORAGE_R(c,t,SV_VGF_DTRM)

#define C_LIQF(c,t) C_STORAGE_R(c,t,SV_LIQF)
#define C_LIQF_M1(c,t) C_STORAGE_R(c,t,SV_LIQF_M1)
#define C_HSRC_YI(c,t)FAST_C_STORAGE_R(c,t,SV_HSRC_YI)
#define C_TOT_RXN(c,t)FAST_C_STORAGE_R(c,t,SV_TOT_RXN)
#define C_HSRC_VD(c,t)FAST_C_STORAGE_R(c,t,SV_HSRC_VD)
#define F_HSRC_VD(e,t) C_HSRC_VD(e,t)

#define C_POLLUT(c,t,i)C_STORAGE_R(c,t, (Svar)(SV_POLLUT0+i))
#define C_SOURCE_POLLUT(c,t)C_STORAGE_R(c,t,SV_POLLUT_S)
#define C_AP_POLLUT(c,t)C_STORAGE_R(c,t,SV_POLLUT_AP)
#define C_VAR1_POLLUT(c,t)C_STORAGE_R(c,t,SV_VAR1_POLLUT)
#define C_VAR2_POLLUT(c,t)C_STORAGE_R(c,t,SV_VAR2_POLLUT)
#define C_VAR3_POLLUT(c,t)C_STORAGE_R(c,t,SV_VAR3_POLLUT)
#define C_VAR4_POLLUT(c,t)C_STORAGE_R(c,t,SV_VAR4_POLLUT)
#define C_VAR5_POLLUT(c,t)C_STORAGE_R(c,t,SV_VAR5_POLLUT)
#define F_POLLUT(e,t,i) C_POLLUT(e,t,i)
#define C_PDF_SOOT_FUEL(c,t,i)C_STORAGE_R(c,t, (Svar)(SV_PDF_SOOT_FUEL0+i))
#define C_PDF_SOOT_OXID(c,t)C_STORAGE_R(c,t,SV_PDF_SOOT_OXID)

#define C_GAMMA(c,t)(C_CP(c,t)/(C_CP(c,t)-C_RGAS(c,t)))
#define PR_TURB(t)(GVAR_TURB(coeff, ke_prt))

#define C_SET_PHI(c,t)FAST_C_STORAGE_I(c,t,SV_SET_PHI)

#define CELL_DVOLUME_DT(c,t) FAST_C_STORAGE_R(c,t,SV_DVOLUME_DT)
#define CELL_DVOLUME_M2_DT(c,t) C_STORAGE_R(c,t,SV_DVOLUME_M2_DT)

#define C_OLD_VOLUME(c,t,dt) (NULLP(THREAD_STORAGE(t,SV_DVOLUME_DT))?\
                              C_VOLUME(c,t):\
            C_VOLUME(c,t)-CELL_DVOLUME_DT(c,t)*(dt))

#define C_SIGMA_XX(c,t)C_STORAGE_R(c,t,SV_SIGMA_XX)
#define C_SIGMA_YY(c,t)C_STORAGE_R(c,t,SV_SIGMA_YY)
#define C_SIGMA_XY(c,t)C_STORAGE_R(c,t,SV_SIGMA_XY)
#define C_SIGMA_ZZ(c,t)C_STORAGE_R(c,t,SV_SIGMA_ZZ)
#if RP_3D
#define C_SIGMA_YZ(c,t)C_STORAGE_R(c,t,SV_SIGMA_YZ)
#define C_SIGMA_XZ(c,t)C_STORAGE_R(c,t,SV_SIGMA_XZ)
#endif

/*Pre v15.0, C_VOLUME_M2 did not account for timestep change on the fly
  with 2nd order in time; added arguement for M1 level time step */
#define C_VOLUME_M2(c,t,dt,dt_m1)(NULLP(THREAD_STORAGE(t,SV_DVOLUME_DT)) || NULLP(THREAD_STORAGE(t,SV_DVOLUME_M2_DT))?\
                                  C_VOLUME(c,t):\
                                  C_VOLUME(c,t)-CELL_DVOLUME_DT(c,t)*(dt)-CELL_DVOLUME_M2_DT(c,t)*(dt_m1))

#define F_FLUX(f,t)FAST_F_STORAGE_R(f,t,SV_FLUX)
#define F_FLUX_M1(f,t)FAST_F_STORAGE_R(f,t,SV_FLUX_M1)
#define F_FLUX_M2(f,t)FAST_F_STORAGE_R(f,t,SV_FLUX_M2)

#define F_GRID_FLUX(f,t)FAST_F_STORAGE_R(f,t,SV_GRID_FLUX)
#define F_GRID_FLUX_M2(f,t)F_STORAGE_R(f,t,SV_GRID_FLUX_M2)

#define F_P_PRIME(f,t)FAST_F_STORAGE_R(f,t,SV_PP)

#define WALL_F_DR(f,t,i)F_STORAGE_R(f,t, (Svar)(SV_DR_SURF_0+(i)))
#define CELL_WALL_SITE(f,t,i)F_STORAGE_R(f,t, (Svar)(SV_SITE_F_0+(i)))
#define CELL_WALL_SITE_OLD(f,t,i)F_STORAGE_R(f,t, (Svar)(SV_SITE_OLD_0+(i)))
#define CELL_WALL_SURF(f,t,i)F_STORAGE_R(f,t, (Svar)(SV_SURF_F_0+(i)))
#define CELL_WALL_YI(c,t,i)C_STORAGE_R_XV(c,t,SV_WALL_SPE,i)

#define WALL_F_CVD_AP(f,t,i)F_STORAGE_R_XV(f,t,SV_CVD_AP,i)
#define WALL_F_CVD_S(f,t,i)F_STORAGE_R_XV(f,t,SV_CVD_S,i)

#define NLBF_AVG_TEMP(f,t) F_STORAGE_R(f,t,SV_NLBF_AVG_TEMP)
#define EVAP_HEAT_FLUX(f,t) F_STORAGE_R(f,t,SV_EVAP_FLUX)
#define QUENCH_HEAT_FLUX(f,t) F_STORAGE_R(f,t,SV_QUENCH_FLUX)
#define LIQUID_PHASE_HEAT_FLUX(f,t) F_STORAGE_R(f,t,SV_LIQUID_PHASE_FLUX)
#define VAPOR_PHASE_HEAT_FLUX(f,t) F_STORAGE_R(f,t,SV_VAPOR_PHASE_FLUX)
#define THIN_FILM_HEAT_FLUX(f,t) F_STORAGE_R(f,t,SV_THIN_FILM_FLUX)
#define WALL_ABLATION_RATE(f,t) F_STORAGE_R(f,t,SV_WALL_ABLATION_RATE)

#define CONVERT_TO_RELATIVE_INTR(t0,t1)(M_abs_frame && \
                                        (sg_dynmesh || \
                                         THREAD_VAR(t0).fluid.mgrid.is_moving || \
                                         THREAD_VAR(t1).fluid.mgrid.is_moving || \
                                         THREAD_VAR(t0).fluid.mrf.is_moving || \
                                         THREAD_VAR(t1).fluid.mrf.is_moving))
#define CONVERT_TO_RELATIVE(t0)(M_abs_frame && \
                                (sg_dynmesh || \
                                 THREAD_VAR(t0).fluid.mgrid.is_moving || \
                                 THREAD_VAR(t0).fluid.mrf.is_moving))

#define WALL_F_VV(f,t)FAST_F_STORAGE(f,t,SV_WALL_V,real (*)[3])

#define BOUNDARY_F_GRID_VV(_f,_t) FAST_F_STORAGE (_f, _t, SV_BND_GRID_V, real (*)[3])
#define BOUNDARY_F_GRID_VV_REQUIRED(_t)     \
 ((THREAD_TYPE (_t) == THREAD_F_WALL) ||    \
  (THREAD_TYPE (_t) == THREAD_F_PINLET) ||  \
  (THREAD_TYPE (_t) == THREAD_F_POUTLET) || \
  (THREAD_TYPE (_t) == THREAD_F_MFINLET) || \
  (THREAD_TYPE (_t) == THREAD_F_VINLET))
#define POROUS_THREAD_P(t) (THREAD_VAR(t).fluid.porous)
#define POROUS_INTERFACE_THREAD_P(t) (POROUS_THREAD_P(t->t0) || POROUS_THREAD_P(t->t1))
#define STRUCTURE_THREAD_P(t) (SOLID_THREAD_P(t) || (FLUID_THREAD_P(t) && POROUS_THREAD_P(t) && THREAD_VAR(t).cell.porous_structure))
#define STRUCTURE_POROUS_THREAD_P(t) (FLUID_THREAD_P(t) && POROUS_THREAD_P(t) && THREAD_VAR(t).cell.porous_structure)
#define NUM_BEACH_P(t) (THREAD_VAR(t).fluid.numerical_beach)
#define CELL_GRID_VV(_c,_t) F_STORAGE (_c, _t, SV_CELL_GRID_V, real (*)[3])
#define CELL_GRID_VV_REQUIRED(t) (CELL_THREAD_P(t) || POROUS_THREAD_P(t) || NUM_BEACH_P(t))

#define BOUNDARY_HEAT_FLUX(f,t)FAST_F_STORAGE_R(f,t,SV_HEAT_FLUX)
#define BOUNDARY_HEAT_FLUX_SENSIBLE(f,t) \
((THREAD_TYPE(t) == THREAD_F_PINLET) || \
 (THREAD_TYPE(t) == THREAD_F_POUTLET) || \
 (THREAD_TYPE(t) == THREAD_F_OUTFLOW) || \
 (THREAD_TYPE(t) == THREAD_F_VINLET) || \
 (THREAD_TYPE(t) == THREAD_F_MFINLET) || \
 (THREAD_TYPE(t) == THREAD_F_PFAR)  )  ?  \
 FAST_F_STORAGE_R(f,t,SV_HEAT_FLUX_SENSIBLE) : FAST_F_STORAGE_R(f,t,SV_HEAT_FLUX)
#define BOUNDARY_HEAT_FLUX_MEAN(f,t)FAST_F_STORAGE_R(f,t,SV_HEAT_FLUX_MEAN)
#define HTC_WALL_FUNCTION(f,t) Face_Heat_Xfer_Coef_Wall(f,t,TRUE,zero_wfhtc)
#define HTC_WALL_YPLUS(f,t,yplus,tfluid_p) Face_Heat_Xfer_Coef_Wall_Yplus(f,t, yplus, tfluid_p)

#define BOUNDARY_RAD_HEAT_FLUX(f,t)FAST_F_STORAGE_R(f,t,SV_RAD_HEAT_FLUX)

#define WALL_HEAT_FLUX BOUNDARY_HEAT_FLUX
#define WALL_RAD_HEAT_FLUX BOUNDARY_RAD_HEAT_FLUX

/* inner is on c1 side of wall, outer is on c0 side */
#define WALL_TEMP_INNER(f,t)FAST_F_STORAGE_R(f,t,SV_WALL_T_INNER)
#define WALL_TEMP_OUTER(f,t)F_STORAGE_R(f,t,SV_WALL_T_OUTER) /* same as F_T(f,t) */

/*Inner/outer terminolgy for wall temperature is removed from GUI.
 * As such defining consistently named macros below.*/
#define WALL_TEMPERATURE(f,t) WALL_TEMP_OUTER(f,t)
#define WALL_TEMPERATURE_THIN(f,t) WALL_TEMP_INNER(f,t)

#define WALL_TEMP_OUTER_MEAN(f,t)F_STORAGE_R(f,t,SV_WALL_T_OUTER_MEAN) /* same as F_T(f,t) */

#define WALL_GAS_T(f,t)F_STORAGE_R(f,t,SV_WALL_GAS_T)

#define F_COEFF_01(f,t)AMG_OD(F_INDEX0(f,t))
#define F_COEFF_10(f,t)AMG_OD(F_INDEX1(f,t))
#define F_COEFF_01_CACHE(_cp,f)AMG_OD(_cp[f])
#define F_COEFF_10_CACHE(_cp,f)AMG_OD(_cp[f])
#define F_COEFF_REAL_01(f,t)AMG_OD(F_GHOSTLINK(f,t))

#define F_COEFF_SYS_01(id,f,t)SAMG_OD(id,F_INDEX0(f,t))
#define F_COEFF_SYS_10(id,f,t)SAMG_OD(id,F_INDEX1(f,t))
#define F_COEFF_REAL_SYS_01(id,f,t)SAMG_OD(id,F_GHOSTLINK(f,t))

/* crevice model */
#define C_SOURCE_MASS_CREV(c,t)C_STORAGE_R(c,t,SV_CREV_MASS)
#define C_SOURCE_MOM_CREV(c,t)C_STORAGE_R_NV(c,t,SV_CREV_MOM)
#define C_SOURCE_ENRG_CREV(c,t)C_STORAGE_R(c,t,SV_CREV_ENRG)
#define C_SOURCE_YI_CREV(c,t,i)C_STORAGE_R(c,t, (Svar)(SV_CREV_SPECIES_0+i))

/* spark model */
#define C_HSRC_SPARK(c,t) FAST_C_STORAGE_R(c,t,SV_HSRC_SPARK)
#define C_DIFF_SPARK(c,t) FAST_C_STORAGE_R(c,t,SV_DIFF_SPARK)

/* loop for reynolds-stresses */
#define loop_rstress(i,n)for((i)=0; (i)<(n); (i)++)

/* dpm model */
#define C_DPM_YI(c,t,i) C_STORAGE_R_XV(c,t,SV_DPM_Y_I,i)

#define C_DPMS_MASS(c,t)FAST_C_STORAGE_R(c,t,SV_DPMS_MASS)
#define C_DPMS_DS_MASS(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_MASS)

#define C_DPMS_MOM_S(c,t)FAST_C_STORAGE_R_NV(c,t,SV_DPMS_MOM_S)
#define C_DPMS_MOM_AP(c,t)FAST_C_STORAGE_R_NV(c,t,SV_DPMS_MOM_AP)
#define C_DPMS_DS_MOM_S(c,t)C_STORAGE_R_NV(c,t,SV_DPMS_DS_MOM_S)
#define C_DPMS_DS_MOM_AP(c,t)C_STORAGE_R_NV(c,t,SV_DPMS_DS_MOM_AP)

#define C_DPMS_WSWIRL_S(c,t)C_STORAGE_R(c,t,SV_DPMS_WSWIRL_S)
#define C_DPMS_WSWIRL_AP(c,t)C_STORAGE_R(c,t,SV_DPMS_WSWIRL_AP)
#define C_DPMS_DS_WSWIRL_S(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_WSWIRL_S)
#define C_DPMS_DS_WSWIRL_AP(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_WSWIRL_AP)

#define C_DPMS_ENERGY(c,t)FAST_C_STORAGE_R(c,t,SV_DPMS_ENERGY)
#define C_DPMS_ENERGY_AP(c,t)FAST_C_STORAGE_R(c,t,SV_DPMS_ENERGY_AP)
#define C_DPMS_DS_ENERGY(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_ENERGY)
#define C_DPMS_DS_ENERGY_AP(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_ENERGY_AP)

/* access to dpm species source terms, where i is the species index */
#define C_DPMS_YI(c,t,i) (injection_par.yi2s[i]<0?0.:FAST_C_STORAGE_R_XV(c,t,SV_DPMS_SPECIES,injection_par.yi2s[i]))
#define C_DPMS_YI_AP(c,t,i) (injection_par.yi2s[i]<0?0.:C_STORAGE_R_XV(c,t,SV_DPMS_SPECIES_AP,injection_par.yi2s[i]))
#define C_DPMS_DS_YI(c,t,i) (injection_par.yi2s[i]<0?0.:C_STORAGE_R_XV(c,t,SV_DPMS_DS_SPECIES,injection_par.yi2s[i]))
#define C_DPMS_DS_YI_AP(c,t,i) (injection_par.yi2s[i]<0?0.:C_STORAGE_R_XV(c,t,SV_DPMS_DS_SPECIES_AP,injection_par.yi2s[i]))

#define C_DPMS_SURF_YI(c,t,i)C_STORAGE_R(c,t, (Svar)(SV_DPMS_SURFACE_SPECIES_0+i))
#define C_DPMS_DS_SURF_YI(c,t,i)C_STORAGE_R(c,t, (Svar)(SV_DPMS_DS_SURFACE_SPECIES_0+i))

#define C_DPMS_REACTION_RATE_POST(c,t,i)C_STORAGE_R(c,t, (Svar)(SV_DPMS_REACTION_RATE_POST_0+i))

#define C_DPMS_VAP_PER_MAT(c,t,i)C_STORAGE_R(c,t, (Svar)(SV_DPMS_VAP_PER_MAT_0+i))
#define C_DPMS_DS_VAP_PER_MAT(c,t,i)C_STORAGE_R(c,t, (Svar)(SV_DPMS_DS_VAP_PER_MAT_0+i))

#define C_DPMS_DEVOL_PER_MAT(c,t,i)C_STORAGE_R(c,t, (Svar)(SV_DPMS_DEVOL_PER_MAT_0+i))
#define C_DPMS_DS_DEVOL_PER_MAT(c,t,i)C_STORAGE_R(c,t, (Svar)(SV_DPMS_DS_DEVOL_PER_MAT_0+i))

#define C_DPMS_BURN_PER_MAT(c,t,i)C_STORAGE_R(c,t, (Svar)(SV_DPMS_BURN_PER_MAT_0+i))
#define C_DPMS_DS_BURN_PER_MAT(c,t,i)C_STORAGE_R(c,t, (Svar)(SV_DPMS_DS_BURN_PER_MAT_0+i))

#define C_DPMS_PDF_1(c,t)FAST_C_STORAGE_R(c,t,SV_DPMS_PDF_1)
#define C_DPMS_PDF_1_AP(c,t)C_STORAGE_R(c,t,SV_DPMS_PDF_1_AP)
#define C_DPMS_DS_PDF_1(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_PDF_1)
#define C_DPMS_DS_PDF_1_AP(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_PDF_1_AP)

#define C_DPMS_PDF_2(c,t)C_STORAGE_R(c,t,SV_DPMS_PDF_2)
#define C_DPMS_PDF_2_AP(c,t)C_STORAGE_R(c,t,SV_DPMS_PDF_2_AP)
#define C_DPMS_DS_PDF_2(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_PDF_2)
#define C_DPMS_DS_PDF_2_AP(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_PDF_2_AP)

#define C_DPMS_INERT(c,t)C_STORAGE_R(c,t,SV_DPMS_INERT)
#define C_DPMS_INERT_AP(c,t)C_STORAGE_R(c,t,SV_DPMS_INERT_AP)
#define C_DPMS_DS_INERT(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_INERT)
#define C_DPMS_DS_INERT_AP(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_INERT_AP)

/* DPM sources into radiation */
#define C_DPMS_EMISS(c,t)FAST_C_STORAGE_R(c,t,SV_DPMS_EMISS)
#define C_DPMS_DS_EMISS(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_EMISS)
#define C_DPMS_ABS(c,t)FAST_C_STORAGE_R(c,t,SV_DPMS_ABS)
#define C_DPMS_DS_ABS(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_ABS)
#define C_DPMS_SCAT(c,t)FAST_C_STORAGE_R(c,t,SV_DPMS_SCAT)
#define C_DPMS_DS_SCAT(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_SCAT)

#define C_DPMS_BURNOUT(c,t)FAST_C_STORAGE_R(c,t,SV_DPMS_BURNOUT)
#define C_DPMS_DS_BURNOUT(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_BURNOUT)

#define C_DPMS_CONCENTRATION(c,t)FAST_C_STORAGE_R(c,t,SV_DPMS_CONCENTRATION)
#define F_DPMS_EROSION(c,t,i)F_STORAGE_R_XV(c,t,SV_DPMS_EROSION,i)
#define F_DPMS_ACCRETION(c,t)F_STORAGE_R(c,t,SV_DPMS_ACCRETION)
#define F_DPMS_EROSION_MDM(c,t)F_STORAGE_R(c,t,SV_DPMS_EROSION_MDM)
#define F_DPMS_EROSION_SHIELDING(c,t)F_STORAGE_R(c,t,SV_DPMS_EROSION_SHIELDING)

/* DPM sources into turbulence */
#define C_DPMS_TKE(c,t)C_STORAGE_R(c,t,SV_DPMS_TKE)
#define C_DPMS_DS_TKE(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_TKE)
#define C_DPMS_O(c,t)C_STORAGE_R(c,t,SV_DPMS_O)
#define C_DPMS_DS_O(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_O)
#define C_DPMS_D(c,t)C_STORAGE_R(c,t,SV_DPMS_D)
#define C_DPMS_DS_D(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_D)
#define C_DPMS_TKE_RUU(c,t)C_STORAGE_R(c,t,SV_DPMS_TKE_RUU)
#define C_DPMS_DS_TKE_RUU(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_TKE_RUU)
#define C_DPMS_TKE_RVV(c,t)C_STORAGE_R(c,t,SV_DPMS_TKE_RVV)
#define C_DPMS_DS_TKE_RVV(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_TKE_RVV)
#define C_DPMS_TKE_RWW(c,t)C_STORAGE_R(c,t,SV_DPMS_TKE_RWW)
#define C_DPMS_DS_TKE_RWW(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_TKE_RWW)
#define C_DPMS_TKE_RUV(c,t)C_STORAGE_R(c,t,SV_DPMS_TKE_RUV)
#define C_DPMS_DS_TKE_RUV(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_TKE_RUV)
#define C_DPMS_TKE_RVW(c,t)C_STORAGE_R(c,t,SV_DPMS_TKE_RVW)
#define C_DPMS_DS_TKE_RVW(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_TKE_RVW)
#define C_DPMS_TKE_RUW(c,t)C_STORAGE_R(c,t,SV_DPMS_TKE_RUW)
#define C_DPMS_DS_TKE_RUW(c,t)C_STORAGE_R(c,t,SV_DPMS_DS_TKE_RUW)

/* dpm model mppic */
#define C_DPMS_MOM_C(c,t)FAST_C_STORAGE_R_NV(c,t,SV_DPMS_MOM_S)
#define C_DPMS_MOM_LIN(c,t)FAST_C_STORAGE_R_NV(c,t,SV_DPMS_MOM_AP)

#define C_DPMS_ENERGY_C(c,t)FAST_C_STORAGE_R(c,t,SV_DPMS_ENERGY)
#define C_DPMS_ENERGY_LIN(c,t)FAST_C_STORAGE_R(c,t,SV_DPMS_ENERGY_AP)

/* DPM pressure in a cell */
#define C_DPM_P_LIQ(c,t)(C_STORAGE_R(c,t,SV_DPM_P_LIQ)
#define C_DPM_P_RG(c,t)(C_STORAGE_R_NV(c,t,SV_DPM_P_LIQ_RG)
#define C_DPM_P_G(c,t)(C_STORAGE_R_NV(c,t,SV_DPM_P_LIQ_G)

/* autoignition model */
#define C_IGNITE(c,t)C_STORAGE_R(c,t,SV_IGNITE)
#define C_IGNITE_G(c,t)C_STORAGE_R_NV(c,t,SV_IGNITE_G)
#define C_IGNITE_RG(c,t)C_STORAGE_R_NV(c,t,SV_IGNITE_RG)
#define C_IGNITE_AP(c,t)C_STORAGE_R(c,t,SV_IGNITE_AP)
#define C_IGNITE_S(c,t)C_STORAGE_R(c,t,SV_IGNITE_S)
#define C_IGNITE_RATE(c,t)C_STORAGE_R(c,t,SV_IGNITE_RATE)
#define F_IGNITE(e,t) C_IGNITE(e,t)

/* extended coherent flamelet model */
#define C_ECFM_SIGMA(c,t)C_STORAGE_R(c,t,SV_ECFM_SIGMA)
#define C_ECFM_SIGMA_G(c,t)C_STORAGE_R_NV(c,t,SV_ECFM_SIGMA_G)
#define C_ECFM_SIGMA_RG(c,t)C_STORAGE_R_NV(c,t,SV_ECFM_SIGMA_RG)
#define C_ECFM_SIGMA_AP(c,t)C_STORAGE_R(c,t,SV_ECFM_SIGMA_AP)
#define C_ECFM_SIGMA_S(c,t)C_STORAGE_R(c,t,SV_ECFM_SIGMA_S)
#define C_ECFM_SIGMA_P(c,t)C_STORAGE_R(c,t,SV_ECFM_SIGMA_P)
#define C_ECFM_SIGMA_P2(c,t)C_STORAGE_R(c,t,SV_ECFM_SIGMA_P2)
#define F_ECFM_SIGMA(e,t) C_ECFM_SIGMA(e,t)
#define C_PREMIXCM(c,t)C_STORAGE_R(c,t,SV_PREMIXCM)
#define C_ECFM_SLES(c,t)C_STORAGE_R(c,t,SV_ECFM_SLES)

/*   Local burnt and unbunt properties for extended coherent flamelet model
     in conjuction with partially premixed option*/
#define C_T_U(c,t)C_STORAGE_R(c,t,SV_ECFM_U_TEMP)
#define C_T_B(c,t)C_STORAGE_R(c,t,SV_ECFM_B_TEMP)
#define C_RHO_B(c,t)C_STORAGE_R(c,t,SV_ECFM_B_DEN)

/* g equation model */
#define C_GEQN(c,t)FAST_C_STORAGE_R(c,t,SV_GEQN)
#define C_GEQN_G(c,t)FAST_C_STORAGE_R_NV(c,t,SV_GEQN_G)
#define C_GEQN_RG(c,t)FAST_C_STORAGE_R_NV(c,t,SV_GEQN_RG)
#define C_GEQN_AP(c,t)C_STORAGE_R(c,t,SV_GEQN_AP)
#define C_GEQN_S(c,t)C_STORAGE_R(c,t,SV_GEQN_S)
#define F_GEQN(e,t) C_GEQN(e,t)

/* g variance for g equation model */
#define C_GVAR(c,t)FAST_C_STORAGE_R(c,t,SV_GVAR)
#define C_GVAR_G(c,t)C_STORAGE_R_NV(c,t,SV_GVAR_G)
#define C_GVAR_RG(c,t)C_STORAGE_R_NV(c,t,SV_GVAR_RG)
#define C_GVAR_AP(c,t)C_STORAGE_R(c,t,SV_GVAR_AP)
#define C_GVAR_S(c,t)C_STORAGE_R(c,t,SV_GVAR_S)
#define F_GVAR(e,t) C_GVAR(e,t)

/* inert transport (EGR) model */
#define C_INERT(c,t)FAST_C_STORAGE_R(c,t,SV_INERT)
#define C_INERT_G(c,t)FAST_C_STORAGE_R_NV(c,t,SV_INERT_G)
#define C_INERT_RG(c,t)FAST_C_STORAGE_R_NV(c,t,SV_INERT_RG)
#define C_INERT_AP(c,t)FAST_C_STORAGE_R(c,t,SV_INERT_AP)
#define C_INERT_S(c,t)FAST_C_STORAGE_R(c,t,SV_INERT_S)
#define C_INERT_H_PDF(c,t)FAST_C_STORAGE_R(c,t,SV_INERT_H)
#define F_INERT_H_PDF(c,t)FAST_F_STORAGE_R(c,t,SV_INERT_H)
#define F_INERT(e,t) C_INERT(e,t)

/* NTC collision */
#define C_PARTICLE_N(c,t)C_STORAGE_R(c,t,SV_DPM_PARTICLE_NUMBER)
#define C_PARTICLE_VOL(c,t)C_STORAGE_R(c,t,SV_DPM_PARTICLE_VOLUME)
#define C_PARCEL_N(c,t)C_STORAGE_R(c,t,SV_DPM_PARCEL_NUMBER)
#define C_MAX_DPM_RELVEL(c,t)C_STORAGE_R(c,t,SV_DPM_MAX_RELVEL)
#define C_MAX_DPM_CROSS(c,t)C_STORAGE_R(c,t,SV_DPM_MAX_CROSS)
#define C_MAX_DPM_NP(c,t)C_STORAGE_R(c,t,SV_DPM_MAX_PARTICLE_N)
#define C_N_COLLISIONS(c,t)C_STORAGE_R(c,t,SV_DPM_N_COLLISIONS)

/* wall film model */
#define F_WALL_FILM_HEIGHT(f,t)FAST_F_STORAGE_R(f,t,SV_FILM_HEIGHT)
#define F_WALL_FILM_MASS(f,t)FAST_F_STORAGE_R(f,t,SV_FILM_MASS)
#define F_WALL_FILM_HEIGHT_M0(f,t)FAST_F_STORAGE_R(f,t,SV_FILM_HEIGHT_M0)
#define F_WALL_FILM_MASS_M0(f,t)FAST_F_STORAGE_R(f,t,SV_FILM_MASS_M0)
#define F_WALL_FILM_TEMP(f,t)FAST_F_STORAGE_R(f,t,SV_FILM_TEMP)
#define F_WALL_FILM_SURFACE_TEMP(f,t)FAST_F_STORAGE_R(f,t,SV_FILM_SURFACE_TEMP)
#define F_WALL_FILM_SURFACE_TEMP_M0(f,t)FAST_F_STORAGE_R(f,t,SV_FILM_SURFACE_TEMP_M0)
#define F_WALL_FILM_HEAT_FLUX(f,t)FAST_F_STORAGE_R(f,t,SV_FILM_HFLUX)
#define F_WALL_FILM_TEMP_M0(f,t)FAST_F_STORAGE_R(f,t,SV_FILM_TEMP_M0)
#define F_WALL_FILM_HEAT_FLUX_M0(f,t)FAST_F_STORAGE_R(f,t,SV_FILM_HFLUX_M0)
#define F_WALL_REFLECT_HEAT_FLUX(f,t)F_STORAGE_R(f,t,SV_REFLECT_HFLUX)
#define F_WALL_FILM_H_WALL(f,t)FAST_F_STORAGE_R(f,t,SV_FILM_H_WALL)
#define F_WALL_FILM_M_IMP_M0(f,t)FAST_F_STORAGE_R(f,t,SV_FILM_M_IMP_M0)
#define F_WALL_FILM_M_IMP_M1(f,t)FAST_F_STORAGE_R(f,t,SV_FILM_M_IMP_M1)
#define F_WALL_FILM_P_FACE(f,t)F_STORAGE_R(f,t,SV_FILM_P_FACE)
#define F_WALL_FILM_P_FACE_G(f,t)F_STORAGE_R_NV(f,t,SV_FILM_P_FACE_G)
#define F_WALL_FILM_V(f,t)FAST_F_STORAGE_R_NV(f,t,SV_FILM_VELOCITY)
#define F_WALL_FILM_V_M0(f,t)FAST_F_STORAGE_R_NV(f,t,SV_FILM_VELOCITY_M0)
#define F_WALL_FILM_P_IMP(f,t)F_STORAGE_R_NV(f,t,SV_FILM_P_IMP)
#define F_WALL_FILM_P_IMP_M1(f,t)F_STORAGE_R_NV(f,t,SV_FILM_P_IMP_M1)
#define N_WALL_FILM_HEIGHT(v) FAST_N_STORAGE_R(NODE_INDEX(v),NODE_THREAD(v),SV_N_FILM_HEIGHT)
#define F_WALL_FILM_MU(f,t)F_STORAGE_R(f,t,SV_FILM_MU)
#define F_WALL_FILM_SURF_TENSION(f,t)FAST_F_STORAGE_R(f,t,SV_FILM_SURF_TENSION)
#define F_WALL_FILM_MU_M0(f,t)F_STORAGE_R(f,t,SV_FILM_MU_M0)
#define F_WALL_FILM_SURF_TENSION_M0(f,t)FAST_F_STORAGE_R(f,t,SV_FILM_SURF_TENSION_M0)
#define F_WALL_FILM_STRIPPED(f,t)F_STORAGE_R(f,t,SV_FILM_STRIPPED)
#define F_WALL_FILM_LEIDENFROST(f,t)FAST_F_STORAGE_R(f,t,SV_FILM_LEIDENFROST)
#define F_WALL_FILM_MASS_OF_I(f,t,i)F_STORAGE_R(f,t, (Svar)(SV_FILM_MASS_OF_0+i))

#define WALL_FV_VV(f,t)FAST_F_STORAGE(f,t,SV_WALL_VV,real (*)[3])

/* acoustics wave equation model */
#define C_SOUND_VAR(c,t)C_STORAGE_R(c,t,SV_SOUND_VAR)
#define C_SOUND_VAR_AP(c,t)C_STORAGE_R(c,t,SV_SOUND_VAR_AP)
#define C_SOUND_VAR_S(c,t)C_STORAGE_R(c,t,SV_SOUND_VAR_S)
#define C_SOUND_VAR_M1(c,t)C_STORAGE_R(c,t,SV_SOUND_VAR_M1)
#define C_SOUND_DDT(c,t)C_STORAGE_R(c,t,SV_SOUND_DDT)
#define C_SOUND_DDT_M1(c,t)C_STORAGE_R(c,t,SV_SOUND_DDT_M1)
#define C_SOUND_D2DT2(c,t)C_STORAGE_R(c,t,SV_SOUND_D2DT2)
#define C_SOUND_D2DT2_M1(c,t)C_STORAGE_R(c,t,SV_SOUND_D2DT2_M1)
#define C_SOUND_SPACE_TERM(c,t)C_STORAGE_R(c,t,SV_SOUND_SPACE_TERM)
#define C_SOUND_SPACE_TERM_M1(c,t)C_STORAGE_R(c,t,SV_SOUND_SPACE_TERM_M1)
#endif /* _FLUENT_SG_MEM_H */
