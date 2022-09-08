/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/* Contains solver and Unsteady Flamelet related functions for non-/partially-premixed model */

#ifndef _FLUENT_SG_PDF_H
#define _FLUENT_SG_PDF_H

#include "dll.h"

FLUENT_EXPORT void Write_Pdf(FILE *fd, cxboolean binary);
FLUENT_EXPORT void Read_Pdf(FILE *fd);
FLUENT_EXPORT void Import_Flamelets(const char *const *, int, const char *, cxboolean);
FLUENT_EXPORT void Write_Flamelet(FILE *);
FLUENT_EXPORT void Pdf_Init(Domain *domain);
FLUENT_EXPORT void PDF_Update_Boundary_Enthalpy(Domain *domain);
FLUENT_EXPORT void PDF_Init_Enthalpy(Domain *domain, cxboolean force);
FLUENT_EXPORT cxboolean Pdf_Pollut_Rate_Initialized(Domain *domain);
FLUENT_EXPORT cxboolean Pdf_Table_Valid_P(void);
FLUENT_EXPORT int Pdf_Table_Modified_P(void);
FLUENT_EXPORT int Flamelet_Data_Modified_P(void);
FLUENT_EXPORT cxboolean Flamelet_Data_Valid_P(void);
FLUENT_EXPORT void Set_Flamelet_Type (void);
FLUENT_EXPORT void Set_prepdf_rpvars(cxboolean *, real *, char **, double *, double[][3], int, cxboolean);
FLUENT_EXPORT void fill_flamelet_import_struct(Material *, int, double *, double *, double *, double *,
                                               double, double, cxboolean, cxboolean, cxboolean, cxboolean,
                                               int, int, cxboolean, double);
FLUENT_EXPORT void Update_Unsteady_Pdf_Table(Domain *, cxboolean force_initialization);
FLUENT_EXPORT void Unsteady_Pdf_Parameters_Changed(void);
FLUENT_EXPORT void Model_Initialize_pdf (void);
FLUENT_EXPORT void Free_Pdf_Memory(void);
FLUENT_EXPORT void Calculate_Pdf (Domain *, int, char **, cxboolean, real *, real *, real *);
FLUENT_EXPORT void Calculate_Pdf_Grid (Domain *, int, char **, cxboolean, real *, real *, real *);
FLUENT_EXPORT void Calc_Par_Premix_Props(Domain *, cxboolean );
FLUENT_EXPORT void Set_Par_Premix_Props(Pointer);
FLUENT_EXPORT void convert_diffusion_FGM_to_premix_FGM(int ii, double *prmx_alpha, real *Yc_eq,
                                                       int num_zt, double *zt);
#if PARALLEL
FLUENT_EXPORT void sendPrmxFlaData(void);
#endif

#if !RP_HOST
FLUENT_EXPORT void Convert_from_fvar_to_fsqr(Domain *domain, Svar nv_fvar_in, Svar nv_fmean_in,
                                             Svar nv_fvar_m1, Svar nv_fmean_m1,
                                             Svar nv_fvar_m2, Svar nv_fmean_m2);
FLUENT_EXPORT void Convert_from_fsqr_to_fvar(Domain *domain, Svar nv_fvar_in, Svar nv_fmean,
                                             Svar nv_fvar_m1, Svar nv_fmean_m1,
                                             Svar nv_fvar_m2, Svar nv_fmean_m2);
#endif

#endif /* _FLUENT_SG_PDF_H */
