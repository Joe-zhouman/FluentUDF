/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DX_PLOT3D_H
#define _FLUENT_DX_PLOT3D_H

#include "dll.h"

#if SEEM
FLUENT_EXPORT void Write_Fast_Grid(Domain *, FILE *, int);
FLUENT_EXPORT void Write_Fast_Velocities(Domain *, FILE *, int);
FLUENT_EXPORT void Write_Fast_Scalar(Domain *, FILE *, int);
FLUENT_EXPORT void Write_Fast_Solution(Domain *, FILE *, int);
#endif /*SEEM*/

#endif /* _FLUENT_DX_PLOT3D_H */
