/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _AMG_GPU_H
#define _AMG_GPU_H

FLUENT_EXPORT void AMGX_print(const char *, int);
FLUENT_EXPORT cxboolean AMGX_Solve_P(Level *);
FLUENT_EXPORT int  AMGX_Solve(AMG_Controls *, Level *, real *);
FLUENT_EXPORT void AMGX_Cleanup(void);
FLUENT_EXPORT void AMGX_Download_Params(void);

#endif
