/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_COPPALLE_H
#define _FLUENT_COPPALLE_H

#include "dll.h"

FLUENT_EXPORT real Get_Coppalle_Emissivity(real t, real p_c, real p_w, real p_t, real s);
FLUENT_EXPORT real Get_Coppalle_Absorption_Coefficient(real p_c, real p_w, int i_gas);
FLUENT_EXPORT real Get_Coppalle_Emissivity_Weights(real t, real p_c, real p_w, int i_gas);

#endif /* _FLUENT_COPPALLE_H */
