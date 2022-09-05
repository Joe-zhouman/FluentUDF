/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_PAMG_H
#define _FLUENT_PAMG_H

#if RP_AMG_V5

#include "dll.h"

FLUENT_EXPORT int AMG_Solve_V5(AMG_Controls controls, Level fine, real residual0[]);

#endif /* RP_AMG_V5 */

#endif /* _FLUENT_PAMG_H */
