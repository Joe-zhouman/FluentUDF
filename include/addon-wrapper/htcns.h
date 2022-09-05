/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_HTC_NS_H_
#define _FLUENT_HTC_NS_H_

#include "global.h"
#include "mem.h"

FLUENT_EXPORT cxboolean Open_Htc_Ns_Library(cxboolean);
FLUENT_EXPORT cxboolean Close_Htc_Ns_Library(void);
FLUENT_EXPORT cxboolean HTC_Ns_Library_Opened(cxboolean);
FLUENT_EXPORT void Clear_HTC_Ns_Domain(cxboolean);
FLUENT_EXPORT void InitializeHtcNsPrimitives(void);

#if defined(_WIN32) || defined (WIN64)
#define HTC_STDCALL __stdcall
#else
#define HTC_STDCALL
#endif

#define HTC_LAYER_ZERO_CELLS            0
#define HTC_LAYER_CPU_CELLS             1
#define HTC_LAYER_CPU_INT_GPU_EXT_CELLS 2
#define HTC_LAYER_GPU_INT_CPU_EXT_CELLS 3
#define HTC_LAYER_GPU_CELLS             4
#define HTC_LAYER_GPU_REXT_CELLS        5
#define HTC_LAYER_CPU_REXT_CELLS        6
#define HTC_LAYER_EEXT_CELLS            7
#define HTC_LAYER_MAX_CELLS             8
#define HTC_LAYER_GPU_EXT_CPU_INT_CELLS HTC_LAYER_CPU_INT_GPU_EXT_CELLS
#define HTC_LAYER_CPU_EXT_GPU_INT_CELLS HTC_LAYER_GPU_INT_CPU_EXT_CELLS

#define HTC_LAYER_ZERO_FACES            0
#define HTC_LAYER_CPU_FACES             1
#define HTC_LAYER_CPU_GPU_FACES         2
#define HTC_LAYER_GPU_FACES             3
#define HTC_LAYER_EXT_FACES             4
#define HTC_LAYER_MAX_FACES             5
#define HTC_LAYER_GPU_CPU_FACES         HTC_LAYER_CPU_GPU_FACES


#if RP_HTC

FLUENT_EXPORT int    HTC_Mark_Cells_Faces(Domain *);
FLUENT_EXPORT void   HTC_Reorder_Cells_Faces(Domain *, int **, int **, int **, int ***, int);
FLUENT_EXPORT void   HTC_Cleanup_Memory_Cells_Faces(Domain *, int **, int **, int **, int ***);
FLUENT_EXPORT double cellHtcCellMark(cell_t, Thread *);
FLUENT_EXPORT double cellHtcCellIndex(cell_t, Thread *);

FLUENT_EXPORT void   HTC_Solve_Disco(void);
FLUENT_EXPORT void   Model_Initialize_HTC_Ns(void);
FLUENT_EXPORT void   HTC_Acc_Ns_Shutdown(void);

#endif

#endif
