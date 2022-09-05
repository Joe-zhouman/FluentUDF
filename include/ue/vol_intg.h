/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_VOLINTG_H
#define _FLUENT_VOLINTG_H

#include "dll.h"
FLUENT_EXPORT double Volume_Integral_Mass_Average(int *, int, char **, int);
FLUENT_EXPORT double Volume_Integral_Mass_Integral(int *, int, char **, int);
FLUENT_EXPORT double Volume_Integral_Mass(int *, int, char **, int);
FLUENT_EXPORT double Volume_Integral_Sum(int *, int, char **, int);
FLUENT_EXPORT double Volume_Integral_TwoPISum(int *, int, char **, int);
FLUENT_EXPORT double Volume_Integral_Min(int *, int, char **, int);
FLUENT_EXPORT double Volume_Integral_Max(int *, int, char **, int);
FLUENT_EXPORT double Volume_Integral_Min_LB(int *, int, char **, int);
FLUENT_EXPORT double Volume_Integral_Max_LB(int *, int, char **, int);
FLUENT_EXPORT double Volume_Integral_Volume(int *, int, char **, int);
FLUENT_EXPORT double Volume_Integral_Volume_Average(int *, int, char **, int);
FLUENT_EXPORT double Volume_Integral(int *, int, char **, int);
FLUENT_EXPORT void Compute_Volume_Integral(const char *, const char *, int *, int, char **, int, double *);
#endif
