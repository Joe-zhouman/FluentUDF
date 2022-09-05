/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_WSGGM_H
#define _FLUENT_WSGGM_H

#include "dll.h"

FLUENT_EXPORT real Get_WSGGM_Absorption(real t, real p_c, real p_w, real p_t, real s);
FLUENT_EXPORT real Get_WSGGM_Absorption_Coefficient(real t, real p_c, real p_w, int i_gas);
FLUENT_EXPORT real Get_WSGGM_Emissivity_Weights(real t, real p_c, real p_w, int i_gas);
FLUENT_EXPORT real Get_SOOT_Absorption_General(real t, real conc_soot);
FLUENT_EXPORT void Get_Cell_Yi_Xi_TotalP(Thread *t, cell_t c, real yi[], real xi[], real *p_t);

#endif /* _FLUENT_WSGGM_H */
