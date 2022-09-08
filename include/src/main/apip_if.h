/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_APIP_IF_H
#define _FLUENT_APIP_IF_H

#include "dll.h"
#include "prf.h"

extern FLUENT_EXPORT int apipPostGeneralData(void);
extern FLUENT_EXPORT int apipPostPerfData(void);
extern FLUENT_EXPORT void apipPop(void);

#endif /* _FLUENT_APIP_IF_H */
