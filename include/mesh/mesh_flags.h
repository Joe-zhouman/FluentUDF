/*
 * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _MESH_FLAGS_H
#define _MESH_FLAGS_H

/**
 * @file
 *   mesh_flags.h
 * @brief
 *   Header file for mesh entity flags
 */

#include "dll.h"

/* * * * * * * * * * * * * * * Macro Definitions * * * * * * * * * * * * * * */

/* Face flags */
#define OVERSET_FACE_FL_SOLVE_SOLVE       (1 << 0)
#define OVERSET_FACE_FL_SOLVE_RECEPTOR    (1 << 1)
#define OVERSET_FACE_FL_SOLVE_DEAD        (1 << 2)
#define OVERSET_FACE_FL_RECEPTOR_RECEPTOR (1 << 3)
#define OVERSET_FACE_FL_OVERSET           (1 << 4)
#define OVERSET_FACE_FL_DEAD              (1 << 5)
#define OVERSET_FACE_FL_RENDER            (1 << 6)
#define OVERSET_FACE_FL_EXTENDED          (1 << 7)
#define OVERSET_FACE_FL_OVERLAP           (1 << 8)
#define NARROW_GAP_ALL_BLOCKED_FACE_FL    (1 << 9)
#define NARROW_GAP_EXT_BLOCKED_FACE_FL   (1 << 10)
#define NARROW_GAP_ALL_MODELED_FACE_FL   (1 << 11)
#define NARROW_GAP_EXT_MODELED_FACE_FL   (1 << 12)
#define FACE_TMP_FLAG_BGN                 13
#define FACE_TMP_FLAG_END                 31

/* Cell flags */
#define OVERSET_CELL_FL_SOLVE             (1 << 0)
#define OVERSET_CELL_FL_RECEPTOR          (1 << 1)
#define OVERSET_CELL_FL_DONOR             (1 << 2)
#define OVERSET_CELL_FL_ORPHAN            (1 << 3)
#define OVERSET_CELL_FL_DEAD              (1 << 4)
#define OVERSET_CELL_FL_SOLVE_OLD         (1 << 5)
#define OVERSET_CELL_FL_RECEPTOR_OLD      (1 << 6)
#define OVERSET_CELL_FL_DEAD_OLD          (1 << 7)
#define OVERSET_CELL_FL_RENDER            (1 << 8)
#define OVERSET_CELL_FL_EXTENDED          (1 << 9)
#define OVERSET_CELL_FL_DONOR_POST        (1 << 10)
#define CELL_MODIFIED_CENTROID_FLAG       (1 << 11)
#define CELL_REFINE_FLAG                  (1 << 12)
#define CELL_COARSE_FLAG                  (1 << 13)
#define CELL_PMN_FLAG                     (1 << 14)
#define NARROW_GAP_BLOCKED_CELL_FL        (1 << 15)
#define NARROW_GAP_BLOCKED_CELL_FL_OLD    (1 << 16)
#define NARROW_GAP_MODELED_CELL_FL        (1 << 17)
#define NARROW_GAP_MODELED_CELL_FL_OLD    (1 << 18)
#define CELL_DEGENERATED_FLAG             (1 << 19)
#define CELL_TMP_FLAG_BGN                 20      /* do not change number of tmp flags!!
                                                     needed for overset (3) + adaption (8) combination */
#define CELL_TMP_FLAG_END                 31

/* Mesh entity enumerants */
#define MESH_NODE 0
#define MESH_EDGE 1
#define MESH_FACE 2
#define MESH_CELL 3

/* Return flag corresponding to bit */
#define MESH_BIT_FLAG(_n) (1 << _n)

#define GET_TMP_MESH_BIT(_type) \
  GetMeshBit(_type, __FILE__, __LINE__)

#define GET_TMP_MESH_FLAG(_type) \
  GetMeshFlag(_type, __FILE__, __LINE__)

#define FREE_TMP_MESH_BIT(_type, _bit) \
  FreeMeshBit(_type, _bit, __FILE__, __LINE__)

#define FREE_TMP_MESH_FLAG(_type, _flags) \
  FreeMeshFlag(_type, _flags, __FILE__, __LINE__)

/* * * * * * * * * * * * Global Function Definitions * * * * * * * * * * * * */

FLUENT_EXPORT int GetMeshBit(const int, const char *, const int);
FLUENT_EXPORT int GetMeshFlag(const int, const char *, const int);
FLUENT_EXPORT void FreeMeshBit(const int, const int, const char *, const int);
FLUENT_EXPORT void FreeMeshFlag(const int, const int, const char *, const int);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#endif /* _MESH_FLAGS_H */

/*****************************************************************************/
