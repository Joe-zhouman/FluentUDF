/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef MESH_CONVERTER_WRAPPER_H
#define MESH_CONVERTER_WRAPPER_H

/**
 * @file
 *   meshConverter.h
 * @brief
 *   Header file for mesh conversion functions
 */

#include "global.h"
#include "mem.h"

#if PARALLEL

FLUENT_EXPORT void CellToFaceMeshConversion(void);
FLUENT_EXPORT void AcmoMeshToFluent(const char *, int, int);

#endif

#endif /* MESH_CONVERTER_WRAPPER_H */
