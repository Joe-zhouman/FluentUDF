/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_CG_H
#define _FLUENT_CG_H

#include "dll.h"
#include "stab.h"

FLUENT_EXPORT int
BCGSTAB_solve(AMG_Controls amg, Level *f,
              preconditionSolveFunc preconditionSolve, real residual0[], int save_b, char *name);
FLUENT_EXPORT int
CG_solve(AMG_Controls amg, Level *f,
         preconditionSolveFunc preconditionSolve, real residual0[], int save_b, char *name);

#endif /* _FLUENT_CG_H */




