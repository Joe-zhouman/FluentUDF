/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_TECPLOT_H
#define _FLUENT_TECPLOT_H

#include "dll.h"

#if SEEM

FLUENT_EXPORT void Write_Tecplot(Domain *d, Pointer, FILE *, Pointer, Pointer);

#endif /*SEEM*/

#endif /* _FLUENT_TECPLOT_H */
