/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_COMPARE_H
#define _FLUENT_COMPARE_H

#include "dll.h"

FLUENT_EXPORT int Compare_C_ID (void *, void *);
FLUENT_EXPORT int Compare_F_ID (void *, void *);
FLUENT_EXPORT int Compare_NODE_ID (const void *, const void *);
FLUENT_EXPORT int Compare_NODE_Pointer_ID (void *, void *);
FLUENT_EXPORT int Compare_THREAD_ID (void *, void *);
FLUENT_EXPORT int Compare_Real_Ascending (const void *, const void *);
FLUENT_EXPORT int Compare_Real_Descending (const void *, const void *);
FLUENT_EXPORT int Compare_Int (void *, void *);
FLUENT_EXPORT int Compare_Index (void *, void *);

#endif /* _FLUENT_COMPARE_H */
