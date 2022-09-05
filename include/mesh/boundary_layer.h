/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef BOUNDARY_LAYER_H
#define BOUNDARY_LAYER_H

/**
 * @file
 *   boundary_layer.h
 * @brief
 *   Header file for boundary layer functions
 */

#include "global.h"
#include "mem.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

FLUENT_EXPORT void Mark_Boundary_Layer_Cells(Domain *);
FLUENT_EXPORT void Exchange_Boundary_Layer_Flag(Domain *);
FLUENT_EXPORT void Register_Boundary_Layer_IO_Managers(void);
FLUENT_EXPORT void Pairwise_Reduce(size_t, real*, real*, real*, real*, real*);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#endif /* BOUNDARY_LAYER_H */

/*****************************************************************************/
