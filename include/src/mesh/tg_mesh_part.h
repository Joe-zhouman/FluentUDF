/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef TG_MESH_PART_H
#define TG_MESH_PART_H

#include "global.h"

/*---------------------------------------------------------------------------*
 * Partitions a 2D/3D surface/volume mesh using
 * Geometric Recursive Inertial Bisection (RIB).
 *
 * ARGUMENTS
 * =========
 * verbosity             (IN)   This specifies the verbosity of information
 *                              to be output during the execution of the
 *                              routine.
 *                              verbosity:
 *                              = 0  No output.
 *                              = 1  Principal axes are printed.
 *                                   Separator Planes are printed.
 *                                   Times for Inertial matrix determination,
 *                                   Sorting partition arrays are printed.
 *                              = 2  In addition, partition IDs are written to
 *                                   a file.
 *                              = 3  (DO NOT USE for large problems)
 *                                   In addition, coordinates, centroids, volumes
 *                                   are printed.
 *
 * ndims                 (IN)   Number of dimensions representing the elements
 *                              of the mesh (currently 2 and 3 only supported).
 *
 * p                     (IN)   The number of partitions to create.
 *
 * nelements             (IN)   Number of vertices
 *                              or faces
 *                              or cells
 *
 * centroids             (IN)   Coordinates of vertices
 *                              or face centroids
 *                              or cell centroids
 *
 * volumes               (IN)   Areas of faces
 *                              or
 *                              volumes of cells.
 *                              (NULL if coordinates of vertices
 *                               are provided in centroids.)
 *
 * partitionIDs          (OUT)  Each vertex/face/cell gets a partition ID.
 *
 * separatorPlanePoints  (OUT)
 * separatorPlaneNormals (OUT)  There will be 'p - 1' separator planes.
 *                              Each plane will be defined by a normal
 *                              vector (perpendicular to the plane)
 *                              and a known point on the plane.
 *
 * A return code of 0 means successful execution.
 * A negative return code means failure.
 *
 * Further Details (Memory layout of inputs and outputs, etc)
 * ==========================================================
 * The sizes of the IN and OUT arrays are:
 *
 * centroids             - nelements x ndims
 * volumes               - nelements
 * partitionIDs          - nelements
 * separatorPlanePoints  - (p - 1) x ndims
 * separatorPlaneNormals - (p - 1) x ndims
 *
 * The caller must allocate the arrays above.
 *
 * Centroids are stored as follows:
 * In 2D:
 *     x1 y1 x2 y2 x3 y3 ... x{nelements} y{nelements}
 * In 3D:
 *     x1 y1 z1 x2 y2 z3 x3 y3 z3 ... x{nelements} y{nelements} z{nelements}
 *
 * Volumes are stored as follows:
 *     V1 V2 ... V{nelements}
 *
 * If areas of faces are supplied, then each element will be considered a cell
 * with volume = area.
 *
 * Each element will have a partition ID.
 *
 * Separator planes are stored as follows (where p1, p2, p3, ... p{p}  are partitions).
 * There will be a plane separating two partitions, hence shown between two partitions:
 *
 *        p1          p2           p3          p4    ...    p{p - 1}                  p{p}
 * In 2D:
 *          spx1 spy1    spx2 spy2   spx3 spy3                     spx{p-1} spy{p-1}
 * Separator plane points are {spx1, spy1}, {spx2, spy2}, ...
 *          snx1 sny1    snx2 sny2   snx3 sny3                     snx{p-1} sny{p-1}
 * Separator plane normals are {snx1, sny1}, {snx2, sny2}, ...
 *
 * In 3D:
 *          spx1 spy1 spz1   spx2 spy2 spz2                      spx{p-1} spy{p-1} spz{p-1}
 * Separator plane points are {spx1, spy1, spz1}, {spx2, spy2, spz2}, ...
 *          snx1 sny1 snz1   snx2 sny2 snz2                      snx{p-1} sny{p-1} snz{p-1}
 * Separator plane normals are {snx1, sny1, snz1}, {snx2, sny2, snz2}, ...
 *
 * Usage
 * =====
 *
 * For example, to partition in 2D (verbose mode),
 *
 * unsigned short verbosity = 1;
 * unsigned short ndims = 2;
 * int p = 4;
 * cxindex nelements = 100000;
 * real* coordinates = (real*)malloc(sizeof(real)*nelements*ndims);
 * int* partitionIDs = (int*)malloc(sizeof(int)*nelements);
 * real* separatorPlanePoints = (real*)malloc(sizeof(real)*(p - 1)*ndims);
 * real* separatorPlaneNormals = (real*)malloc(sizeof(real)*(p - 1)*ndims);
 *
 * // Fill coordinates...
 *
 * int rc = Geometric_Partition_Mesh(
 *            ndims, verbosity, p, nelements, coordinates, NULL,
 *            partitionIDs, separatorPlanePoints, separatorPlaneNormals
 * );
 *
 * // Check for call success or failure.
 *
 * free(separatorPlaneNormals);
 * free(separatorPlanePoints);
 * free(partitionIDs);
 * free(coordinates);
 *---------------------------------------------------------------------------*/

FLUENT_EXPORT int Geometric_Partition_Mesh(
  unsigned short verbosity,
  unsigned short ndims,
  int p,
  cxindex nelements,
  real *centroids,
  real *volumes,
  int *partitionIDs,
  real *separatorPlanePoints,
  real *separatorPlaneNormals
);

#endif

