/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _NRBC2_H
#define _NRBC2_H

typedef enum
{
  BAC_OFF = 0,
  BAC_NRBC,
  BAC_IMPEDANCE,
  BAC_IWAVE
} bac_enum_t; /* boundary acoustic options */

#define T_STORAGE_R_N5V(t,sv)T_STORAGE(t,sv,real (*)[5])
#define F_STORAGE_R_N5V(f,t,n)(T_STORAGE_R_N5V(t,n)[f])
#define F_Q_N(f,t) F_STORAGE_R_N5V(f,t,SV_Q_N)

extern real ms_co[10];


void  Update_GENERAL_NRBC(Domain *domain, int nstage);
void  IS_NRBC_ON(Domain *domain) ;
void  IS_ANRBC_ON(Domain *domain) ;
FLUENT_EXPORT real NRBC_get_K_factor(Domain *domain);

extern FLUENT_EXPORT cxboolean M_nrbc;
extern FLUENT_EXPORT cxboolean M_impedance;
extern FLUENT_EXPORT cxboolean M_iwave;
extern FLUENT_EXPORT cxboolean M_BAC;

FLUENT_EXPORT int Count_NRBC(Domain *domain);
FLUENT_EXPORT void Update_NRBC(Domain *domain);
FLUENT_EXPORT void nrbc_pp_coeffs2(Thread *t);
FLUENT_EXPORT void nrbc_update_pressure(Thread *t);
FLUENT_EXPORT void  Update_PO_NRBC(Domain *domain, int nstage);
FLUENT_EXPORT void  Update_P_Inlet_NRBC(Domain *domain, int nstage);
FLUENT_EXPORT void  Update_Vinlet_NRBC(Domain *domain, int nstage);

extern FLUENT_EXPORT int n_imp_rp;
extern FLUENT_EXPORT int n_imp_cp;

FLUENT_EXPORT int Count_Impedance(Domain *domain);
FLUENT_EXPORT int Count_IWave(Domain *domain);

#define F_IMP_W5(f,t)C_STORAGE_R(f,t,SV_IMP_W5)
#define F_IMP_W5_M1(f,t)C_STORAGE_R(f,t,SV_IMP_W5_M1)

#define F_IMP_W1(f,t)C_STORAGE_R(f,t,SV_IMP_W1)
#define F_IMP_W1_M1(f,t)C_STORAGE_R(f,t,SV_IMP_W1_M1)

#define SV_IMP_RP_MAX (SV_IMP_RP_9+1)
#define SV_IMP_RE_MAX (SV_IMP_RE_9+1)
#define SV_IMP_IM_MAX (SV_IMP_IM_9+1)

#define SV_IMP_RP_MAX_M1 (SV_IMP_RP_9_M1+1)
#define SV_IMP_RE_MAX_M1 (SV_IMP_RE_9_M1+1)
#define SV_IMP_IM_MAX_M1 (SV_IMP_IM_9_M1+1)

#define SV_IMP_RP(i)((Svar)(SV_IMP_RP_0+(i)))
#define SV_IMP_RE(i)((Svar)(SV_IMP_RE_0+(i)))
#define SV_IMP_IM(i)((Svar)(SV_IMP_IM_0+(i)))

#define SV_IMP_RP_M1(i)((Svar)(SV_IMP_RP_0_M1+(i)))
#define SV_IMP_RE_M1(i)((Svar)(SV_IMP_RE_0_M1+(i)))
#define SV_IMP_IM_M1(i)((Svar)(SV_IMP_IM_0_M1+(i)))

#define F_IMP_RP(f,t,i)F_STORAGE_R(f,t,SV_IMP_RP(i))
#define F_IMP_RE(f,t,i)F_STORAGE_R(f,t,SV_IMP_RE(i))
#define F_IMP_IM(f,t,i)F_STORAGE_R(f,t,SV_IMP_IM(i))

#define F_IMP_RP_M1(f,t,i)F_STORAGE_R(f,t,SV_IMP_RP_M1(i))
#define F_IMP_RE_M1(f,t,i)F_STORAGE_R(f,t,SV_IMP_RE_M1(i))
#define F_IMP_IM_M1(f,t,i)F_STORAGE_R(f,t,SV_IMP_IM_M1(i))

#define M_BAC_THREAD_P(t) (M_BAC && THREAD_VAR(t).pi.ac_op > BAC_OFF)
#define M_BAC_ENERGY_THREAD_P(t)(M_BAC_THREAD_P(t)  && !(M_compressible_liquid || sg_mphase))

#define ANY_THREAD_BAC_P(t) \
  ((THREAD_TYPE(t) == THREAD_F_POUTLET  || \
    THREAD_TYPE(t) == THREAD_F_PINLET   || \
    THREAD_TYPE(t) == THREAD_F_VINLET   || \
    THREAD_TYPE(t) == THREAD_F_MFINLET) && \
    THREAD_VAR(t).po.ac_op > BAC_OFF)

#define ANY_THREAD_IWAVE_P(t) \
  (( THREAD_TYPE(t) == THREAD_F_POUTLET ||  \
    THREAD_TYPE(t) == THREAD_F_PINLET  ||  \
    THREAD_TYPE(t) == THREAD_F_VINLET  ||  \
    THREAD_TYPE(t) == THREAD_F_MFINLET ) &&   \
    (THREAD_VAR(t).po.ac_op == BAC_IWAVE))


#endif
