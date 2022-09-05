/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_QUATERNION_H
#define _FLUENT_QUATERNION_H

/**
 *   Provides functionality for quaternions.
 */

#include "global.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define ND_Q 4
#define NQV_V(a,EQ,x)((a)[0]EQ(x)[0],(a)[1]EQ(x)[1],    \
                      (a)[2]EQ(x)[2],(a)[3]EQ(x)[3])

typedef real quaternion[4];

extern const quaternion Identity_Q;


typedef struct
{
  real angle;

  real axis[ND_3];
} Axis_Angle;

#define AA_ANGLE(orient)((orient)->angle)
#define AA_AXIS(orient)((orient)->axis)

FLUENT_EXPORT void Real_To_Pureq (real[3], quaternion *);
FLUENT_EXPORT void Pureq_To_Real (quaternion, real[3]);
FLUENT_EXPORT void Double_To_Pureq(double[3], quaternion *);
FLUENT_EXPORT void Pureq_To_Double(quaternion, double[3]);
FLUENT_EXPORT void Q_Assign (const quaternion, quaternion *);
FLUENT_EXPORT void Rot_Matrix_From_Q (quaternion, real[3][3]);
FLUENT_EXPORT void Axis_Angle_From_Q(quaternion, Axis_Angle *);
FLUENT_EXPORT void Theta_From_Q (quaternion, real[3]);
FLUENT_EXPORT void Q_From_Theta (real[3], quaternion *);
FLUENT_EXPORT void Q_From_Vectors (real[3], real[3], quaternion *);
FLUENT_EXPORT void Q_From_Axis_Angle(Axis_Angle, quaternion *);
FLUENT_EXPORT void Rot_Matrix_From_Vector_Basis(real[3], real[3], real[3],
                                                real[3], real[3], real[3],
                                                real[3][3]);
FLUENT_EXPORT void Q_Normalize (quaternion, quaternion *);
FLUENT_EXPORT void Q_Conjugate (quaternion, quaternion *);
FLUENT_EXPORT void Q_Inverse (quaternion, quaternion *);
FLUENT_EXPORT void Q_Prod (quaternion, quaternion, quaternion *);
FLUENT_EXPORT void Q_Prod_Norm (quaternion, quaternion, quaternion *);
FLUENT_EXPORT real Q_Distance_Fast(quaternion, quaternion);
FLUENT_EXPORT void Transform_Vector_Q (real[3], quaternion, real[3]);
FLUENT_EXPORT void Inv_Transform_Vector_Q (real[3], quaternion, real[3]);
FLUENT_EXPORT void Rotate_Q(quaternion, quaternion, quaternion *, cxboolean);
FLUENT_EXPORT void Rotate_Vector_Q (real[3], quaternion, real[3]);
FLUENT_EXPORT void Rotate_Vector_Q_DP(double[3], quaternion, double[3]);
FLUENT_EXPORT void Theta_From_Euler (real[3], real[3]);
FLUENT_EXPORT void Rot_Matrix_From_Euler (real[3], real[3][3]);
FLUENT_EXPORT void Q_From_Rot_Matrix (real[3][3], quaternion *);
FLUENT_EXPORT void Euler_From_Q (quaternion, real[3]);
FLUENT_EXPORT void Get_Rotation_Q_From_Qs(quaternion, quaternion, quaternion *);
FLUENT_EXPORT void Omega_From_Theta_Angles(real[3], real[3], real, real[3]);
FLUENT_EXPORT void Omega_From_Euler_Angles(real[3], real[3], real, real[3]);
FLUENT_EXPORT void Get_Closest_Angle(real[3], real[3], real[3], real *);

#endif /* _FLUENT_QUATERNION_H */
