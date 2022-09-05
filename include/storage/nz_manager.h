/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/* 
 * File:   nz_manager.h
 * Author: rjia
 *
 * Created on January 22, 2018, 3:10 PM
 */

#ifndef NZ_MANAGER_H
#define NZ_MANAGER_H

#include "dll.h"
#include "mem.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum nz_creation_mode
{
  NZ_Create_Non = 0,
  NZ_Create_For_All,
  NZ_Create_For_Solid
} NZ_Creation_Mode;

/* return 1 success, 0 failed */
FLUENT_EXPORT int Create_Nodal_Threads_As_Needed(Domain* domain, int creation_mode, cxboolean with_host);
/* return 1 success, 0 failed */
FLUENT_EXPORT int Create_Nodal_Threads(Domain* domain, int creation_mode, cxboolean with_host);
/* return 1 success, 0 failed */
FLUENT_EXPORT int Free_Nodal_Threads(Domain* domain, cxboolean with_host);
FLUENT_EXPORT int Test_Nodal_Threads(Domain* domain, int creation_mode, cxboolean with_host);

#ifdef __cplusplus
}
#endif

#endif /* NZ_MANAGER_H */
