/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_F_PERIODIC_H
#define _FLUENT_F_PERIODIC_H

#include "dll.h"

struct tv_per_struct
{
  real angle;     /* periodic angle */
  real dp;      /* periodic pressure jump */
  real rm[3][3];    /* rotation matrix.  Be careful: need
         * to make sure this is updated
         * whenever the rotational axis is
         * changed. */
  real dr[ND_ND];               /* translation vector */
  cxboolean angular;    /* angular periodicity? */
};

FLUENT_EXPORT void thread_periodic_default(Domain *, Thread *);

#endif /* _FLUENT_F_PERIODIC_H */
