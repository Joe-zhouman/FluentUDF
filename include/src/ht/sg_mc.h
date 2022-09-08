/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/

#ifndef _FLUENT_SG_MC_H
#define _FLUENT_SG_MC_H

#include "dll.h"

#define C_MC_S(c,t) C_STORAGE_R(c, t, SV_MC_SOURCE)
#define F_MC_S(e,t) C_MC_S(e,t)
#define C_MC_SDV(c,t) C_STORAGE_R(c, t, SV_MC_SDV)
#define F_MC_SDV(e,t) C_MC_SDV(e,t)
#define C_MC_ID(c,t) C_STORAGE_INDEX(c, t, SV_MC_CID)
#define F_MC_ID(e,t) C_STORAGE_INDEX(e, t, SV_MC_FID)
#define F_MC_SP_C0(f,t) F_STORAGE_INDEX(f,t,SV_MC_SP_C0)
#define F_MC_SP_C1(f,t) F_STORAGE_INDEX(f,t,SV_MC_SP_C1)
#define F_MC_FPRIM(f,t) F_STORAGE_INDEX(f,t,SV_MC_FPRIM)
#define F_MC_NPRIM(f,t) F_STORAGE_INDEX(f,t,SV_MC_NPRIM)
#define F_MC_IRR_QT(f,t,nb) F_STORAGE_R_XV(f,t,SV_MC_IRR_QTRANS,nb)
#define F_MC_IRR_QR(f,t,nb) F_STORAGE_R_XV(f,t,SV_MC_IRR_QREFL,nb)
#define F_MC_IRR_QA(f,t,nb) F_STORAGE_R_XV(f,t,SV_MC_IRR_QABS,nb)
#define F_MC_QM(f,t)F_STORAGE_R(f,t,SV_MC_QMINUS)
#define F_MC_QA(f,t,nb)F_STORAGE_R_XV(f,t,SV_MC_QABS,nb)
#define F_MC_QR(f,t,nb)F_STORAGE_R_XV(f,t,SV_MC_QREFL,nb)
#define F_MC_QT(f,t,nb)F_STORAGE_R_XV(f,t,SV_MC_QTRANS,nb)
#define C_MC_I(c, t, nb) C_STORAGE_R_XV(c, t, SV_MC_I, nb)
#define RADIATING_THREAD_MC_P(t)(THREAD_VAR(t).cell.radiating)
#define MC_PARTICIPATING_THREAD_P(t) (!SHELL_CELL_THREAD_P(THREAD_T0(t)) && !HELPER_THREAD_P(t) && !SLIDING_INTERFACE_THREAD_P(t) && !UNREFERENCED_THREAD_P(t))

#if !RP_HOST
FLUENT_EXPORT cxboolean Init_MonteCarlo(Domain *domain, int global_master_rank);
FLUENT_EXPORT void map_CFXData(Domain *domain);
FLUENT_EXPORT Domain *fill_MC_Domain(Domain *domain, int global_master_rank);


/*FLUENT_EXPORT int load_cfxrad_api();*/
FLUENT_EXPORT void update_solution_properties(Domain *domain);

FLUENT_EXPORT void update_band_limits(int);
void spectral_band_void_check(void);
#endif
FLUENT_EXPORT real Get_irradiation_contribution(face_t f, Thread *PTR_RESTRICT tf, real A[], real At);
FLUENT_EXPORT cxboolean fill_MC_data(Domain *domain, int global_master_rank);
FLUENT_EXPORT int Get_MC_List(Domain *domain, Svar **list, cxboolean isPar, cxboolean mapping, cxboolean data_valid);
FLUENT_EXPORT int Is_MC_Domain(Domain *);
FLUENT_EXPORT void Init_Spectral_Bands_MC(void);
FLUENT_EXPORT void Free_MC_Memory(void);
FLUENT_EXPORT void Model_Initialize_mc(void);

/*Post Processing*/
FLUENT_EXPORT int Get_MC_Post_Vars_List(Svar **list);
FLUENT_EXPORT void Fill_MC_Post_Vars(Domain *);


#if PARALLEL
FLUENT_EXPORT void clear_mc_domain(Domain *domain);
FLUENT_EXPORT Domain *recomposed_domain(Domain *domain, int global_master_rank);
FLUENT_EXPORT Domain *fill_MC_Domain(Domain *domain, int global_master_rank);

#endif
extern FLUENT_EXPORT  int mc_sub_comm_handle;
extern FLUENT_EXPORT  int *mc_subrank_map;
extern FLUENT_EXPORT int mc_global_master;
extern FLUENT_EXPORT int mc_nproc_sub_comm;
#endif
