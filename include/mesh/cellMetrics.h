/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef MESH_CELLMETRICS_H_
#define MESH_CELLMETRICS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "storage/mem.h"

#ifdef __cplusplus
}
#endif

EXTERNC FLUENT_EXPORT double Calculate_Cell_Metrics_DP (double *, const cell_t, const Thread *, const cxboolean);

#if RP_DOUBLE
#define Calculate_Cell_Metrics Calculate_Cell_Metrics_DP
#else
EXTERNC FLUENT_EXPORT float Calculate_Cell_Metrics_SP (float *, const cell_t, const Thread *, const cxboolean);
#define Calculate_Cell_Metrics Calculate_Cell_Metrics_SP
#endif

#endif /* MESH_CELLMETRICS_H_ */
