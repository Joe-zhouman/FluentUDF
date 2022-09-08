/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SG_VFR_H
#define _FLUENT_SG_VFR_H

#include "dll.h"

#define SMALL_VFR 1.e-10

FLUENT_EXPORT void Read_Thread_Rad_Flux_Data(Domain *domain, FILE *fp, cxboolean binary, cxboolean double_data);
FLUENT_EXPORT void Write_Thread_Rad_Flux_Data(Domain *domain, FILE *fp, cxboolean binary);
FLUENT_EXPORT int  Write_Thread_View_Factors(Domain *domain, FILE *fp, cxboolean binary);
FLUENT_EXPORT void Read_Thread_View_Factors(Domain *domain, FILE *fp, int section);
FLUENT_EXPORT void Free_Thread_View_Factor_Arrays(Domain *domain);
FLUENT_EXPORT void Init_Radiosity(Domain *domain);
FLUENT_EXPORT void Model_Initialize_vfr(void);

#if MPI_IO
FLUENT_EXPORT void Read_MPI_Thread_Rad_Flux_Data(Domain *domain, int fhandle, int *headerbuf, cxboolean double_data);
FLUENT_EXPORT void Write_MPI_Thread_Rad_Flux_Data(Domain *domain, int fhandle);
#endif

#endif /* _FLUENT_SG_VFR_H */
