/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

FLUENT_EXPORT real Zbrent (real (*func) (real, void *), real, real, real, void *, cxboolean *);
FLUENT_EXPORT int Ivp_rk23(real *x, real *y, real (*func) (real, real, void *),
                           real xend, real *h, real tol_abs, real tol_rel,
                           int mxstep, int *nstep, void *par);
