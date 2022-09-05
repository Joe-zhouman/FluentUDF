/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_RNG_H
#define _FLUENT_RNG_H

#include "dll.h"
#include "global.h"

FLUENT_EXPORT void Initialize_RNG_KE(void);
FLUENT_EXPORT real rng_alpha(real alpha0, real effvisc, real molvisc);
FLUENT_EXPORT real rng_viscosity(real rho, real mu, real k, real d);
FLUENT_EXPORT real rng_strainrate_term(real ts2, real ke, real eps, real mu_t);
FLUENT_EXPORT void Compute_Linearized_RNG_Strain_Term(real k, real d, real mu_t, real s2,
                                                      real *a, real *b);

#endif /* _FLUENT_RNG_H */
