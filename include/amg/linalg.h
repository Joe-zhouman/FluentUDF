/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_LINALG_H
#define _FLUENT_LINALG_H

#include "dll.h"

#define MAX_GE_EQ   500
#define ID(ie, je, n_cols)  ((ie)*(n_cols) + (je)) /* store by rows */


FLUENT_EXPORT void Gauss_Elimination(const int n_rows,
                                     const int n_cols,
                                     real A[], /* A[n_rows, n_rows] matrix (destroyed) */
                                     real X[], /* X[n_rows, n_cols] solution matrix  */
                                     real B[], /* B[n_rows, n_cols] source (destroyed) */
                                     int swap_rows);

FLUENT_EXPORT cxboolean Gauss_Elimination_3D_Fan_Zone(const int n_rows,
                                                      const int n_cols,
                                                      real A[], /* A[n_rows, n_rows] matrix (destroyed) */
                                                      real X[], /* X[n_rows, n_cols] solution matrix  */
                                                      real B[], /* B[n_rows, n_cols] source (destroyed) */
                                                      int swap_rows,
                                                      int fan_zone_id);

FLUENT_EXPORT cxboolean Gauss_Elimination_dp(const int n_rows,
                                             const int n_cols,
                                             double A[], /* A[n_rows, n_rows] matrix (destroyed) */
                                             double X[], /* X[n_rows, n_cols] solution matrix  */
                                             double B[], /* B[n_rows, n_cols] source (destroyed) */
                                             int swap_rows);

FLUENT_EXPORT int  Matrix_Inverse(real *a, int n);
FLUENT_EXPORT real Matrix_Norm(real *a, int n);
FLUENT_EXPORT real Matrix_Condition(real *a, int n);

#endif /* _FLUENT_LINALG_H */
