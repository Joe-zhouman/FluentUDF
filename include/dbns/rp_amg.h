/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_RP_AMG_H
#define _FLUENT_RP_AMG_H

#include "dll.h"
#include "amgif.h"

FLUENT_EXPORT void Init_Fine_Level_Matrix(Domain *domain);
FLUENT_EXPORT void RP_Set_AMG_Soln_Init(int sys_id, cxboolean state);
FLUENT_EXPORT void RP_Zero_AMG_Soln_Vector(int sys_id);
FLUENT_EXPORT int  RP_AMG_Solve(real ratioTol, int n_tries);


#endif /* _FLUENT_RP_AMG_H */
