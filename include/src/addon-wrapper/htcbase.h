/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_HTC_BASE_H_
#define _FLUENT_HTC_BASE_H_

#include "global.h"
#include "mem.h"

#if defined(_WIN32) || defined (WIN64)
#define HTC_STDCALL __stdcall
#else
#define HTC_STDCALL
#endif

#define HTC_CPU_MODE                    1
#define HTC_GPU_MODE                    2
#define HTC_HYBRID_MODE                 3

#define HTC_STORAGE_UNDEF  0
#define HTC_STORAGE_INT    1
#define HTC_STORAGE_REAL   2
#define HTC_STORAGE_INDEX  3
#define HTC_STORAGE_UINT   4
#define HTC_STORAGE_CHAR   5
#define HTC_STORAGE_PTR    6

#if RP_HTC

FLUENT_EXPORT void  *HTC_Get_Svar_Ptr(Thread *, int, int);
FLUENT_EXPORT void  *HTC_Get_Seg_Svar_Ptr(Thread *, int, int, int);
FLUENT_EXPORT void   HTC_Get_Svar_Info(Thread *, int, int *, int *, int *);
FLUENT_EXPORT int    HTC_Get_GPU_Device(void);

#endif

#endif
