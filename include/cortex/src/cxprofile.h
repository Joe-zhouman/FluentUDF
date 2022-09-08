/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/*
 *  cxprofile.h
 *
 */

#include "cxlist.h"

/* Constants for Profile */
#define CX_PROFILE_CONSTANT   "constant"
#define CX_PROFILE_POLYNOMIAL   "polynomial"
#define CX_PROFILE_HARMONIC   "harmonic"
#define CX_PROFILE_PIECEWISE    "piecewise-polynomial"
#define CX_PROFILE_NASA_PIECEWISE    "nasa-9-piecewise-polynomial"
#define CX_PROFILE_LINEAR   "piecewise-linear"

#define CX_PROFILE_FUNC_OF_TEMP   "temperature"
#define CX_PROFILE_FUNC_OF_X    "x-coordinate"
#define CX_PROFILE_FUNC_OF_Y    "y-coordinate"
#define CX_PROFILE_FUNC_OF_Z    "z-coordinate"
#define CX_PROFILE_FUNC_OF_TIME   "time"
#define CX_PROFILE_FUNC_OF_VN   "normal-velocity"
#define CX_PROFILE_FUNC_OF_V    "velocity-mag"
#define CX_PROFILE_FUNC_OF_ANGLE  "angle"
#define CX_PROFILE_FUNC_OF_DIAMETER     "diameter"
#define CX_PROFILE_FUNC_OF_PRESS        "pressure"
#define CX_PROFILE_FUNC_OF_MIXTF        "mixture-fraction"
#define CX_PROFILE_FUNC_OF_SOC      "soc"
#define CX_PROFILE_FUNC_OF_SOL      "sol"
#define CX_PROFILE_FUNC_OF_CS       "cs"
#define CX_PROFILE_FUNC_OF_CE       "ce"

#define CX_METHOD_NONE      0
#define CX_METHOD_SIMPLE    1
#define CX_METHOD_COMPLEX   2

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

void  cx_profile_edit   (List *, String , int);
Pointer cx_profile_get    (List *);
Pointer cx_profile_get_current  (List *);
char *cx_profile_set    (List *, Widget, Pointer);
char *cx_profile_set_current  (List *, Widget, Pointer);
void  cx_profile_set_current_method (List *, Widget, String);
int cx_profile_type   (List *, String);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
