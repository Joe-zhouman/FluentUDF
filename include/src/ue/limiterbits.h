/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */
#ifndef _LIMITERBITS_
#define _LIMITERBITS_
#include "global.h"

#ifdef __cplusplus
extern "C" {
#endif

FLUENT_EXPORT void Set_Variable_Marking_Bit(const char *limiterVariableName,
                                            const int bitIndex);
/* variable marker can have at most 1 bit set for marking this variable*/
FLUENT_EXPORT cxindexU Get_Variable_Marker(const char *limiterVariableName);
FLUENT_EXPORT void Free_Marker(const char *limiterVariableOrEquationName);

/* it sets the count and returns a pointer to int array.
 * This pointer points to a static array and doesn't needs to be freed*/
FLUENT_EXPORT int *Get_Valid_Limiter_Bits(int *count);

FLUENT_EXPORT void Get_Float_Minmax_Index(const float *values, size_t count,
                                          size_t minmax[2]);
FLUENT_EXPORT void Get_Double_Minmax_Index(const double *values, size_t count,
                                           size_t minmax[2]);
void Set_Residual_Marking_Bits(const char **equations,
                               const int n_equations,
                               const int bitIndex,
                               const real threshold);

cxindexU Get_Residual_Marker(char *equation, real *threshold);

int Check_Residual_Storage_Need(const char *equation);

#ifdef __cplusplus
}
#endif
#endif
