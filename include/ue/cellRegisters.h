/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/
#ifndef _CELL_REG_EXPR_
#define _CELL_REG_EXPR_

#ifdef __cplusplus
extern "C" {
#endif
#include "dll.h"
#include "global.h"
#include "models.h"
#include "expr/ExprC.h"

FLUENT_EXPORT void Compute_Expression_Dependencies(const char *expr);

FLUENT_EXPORT int Count_Cells_for_Expression(const char *expr);
FLUENT_EXPORT void SV_Expr_Register_Surface(int surfaceId, const char *expr, int surfFlag, int maxCells);

#ifdef __cplusplus
}
#endif
#endif
