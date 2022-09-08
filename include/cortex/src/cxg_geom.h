/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _CXG_GEOM_H
#define _CXG_GEOM_H

#include "cxconfig.h"  /* for WORKING_CXX if exists */
#ifdef WORKING_CXX

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

void generate_point_on_circle(float *points, float *center, float radius, float angle);
void generate_points_on_circle(float *points, float *center, float radius, int numpoints);

long CreateSphere(char *segment, float *center, float radius, int numsides);

#if defined(__cplusplus)
}  /* end extern "C" */
#endif

#endif /* WORKING_CXX */

#endif /* _CXG_GEOM_H */
