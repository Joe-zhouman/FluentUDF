/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_F_EXTERIOR_H
#define _FLUENT_F_EXTERIOR_H

#include "dll.h"

FLUENT_EXPORT void Fluid_Exterior_Derivative(Thread *thread);
FLUENT_EXPORT void Solid_Exterior_Derivative(Thread *thread);
FLUENT_EXPORT void Exterior_Reconstruct(Thread *thread);

#endif /* _FLUENT_F_EXTERIOR_H */
