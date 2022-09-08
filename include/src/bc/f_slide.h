/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_F_SLIDE_H
#define _FLUENT_F_SLIDE_H

#include "dll.h"

/* sliding interface */
struct tv_si_struct
{
  real rm[3][3];    /* rotation matrix. */
};

FLUENT_EXPORT void thread_sb_default(Domain *domain, Thread *t);

#endif /* _FLUENT_F_SLIDE_H */
