/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef CXTURBO_H
#define CXTURBO_H

#include "cxiface.h"

void Set_Turbo_Axis(float axis[3], float origin[3]);
void Set_Zero_Dir(float zero[3]);
double Surface_Flow_Angle(Surface *s, double depth, int gtype, int atype);
double Swirl_Number(Surface *s, double depth, int gtype);
void CX_Turbo_Surface(int index, int type, Surface *s, float *state);
void CX_Transform_Turbo_Surface(int index, int type, int  machine_type);

#endif /* CXTURBO_H */
