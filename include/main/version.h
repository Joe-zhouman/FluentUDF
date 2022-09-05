/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_VERSION_H
#define _FLUENT_VERSION_H

#if !defined(MAKEFILE)
#include "dll.h"
#endif

/* set this to build-id desired for release */
/* id > 10000 turns off prototype warning */
#define VER_VAR_MAX_CHAR_SIZE 256        /* Max char length of version variables, example: RampantServicePackVersion */
#define RampantReleaseBuild 10212

#define RampantReleaseMajor 22
#define RampantReleaseMinor 2
#define RampantReleaseRevision 0
/* If it is a servicepack; define relevant service pack strings to max length of VERSION_VAR_STRING_LEN, otherwice set it to null string "". */
#define RampantServicePackVersion ""     /* A null string "" indicates its not a service pack */
#define RampantCopyrightYear 2022        /* Copyright year */

#define ReleaseStartMonth 10
#define ReleaseStartDay 15
#define ReleaseStartYear 2021

#if !defined(MAKEFILE) && !defined(_UDF)

FLUENT_EXPORT int CX_Release_Revision(void);

#undef RampantReleaseRevision
#define RampantReleaseRevision CX_Release_Revision()

extern FLUENT_EXPORT void Inquire_Release(int *major, int *minor, int *revision, char *service_pack, int *copyright_year);
FLUENT_EXPORT char *Inquire_Fluent_Build_Time(void);
FLUENT_EXPORT void Report_Build_Times(void);
FLUENT_EXPORT int Inquire_Fluent_Build_Id(void);
FLUENT_EXPORT long Inquire_Source_Rev_Id(void);
FLUENT_EXPORT char *Inquire_Source_Vcs_Id(void);
FLUENT_EXPORT char *Inquire_Source_Vcs_Branch(void);
char *Inquire_External_Product_Version(void);
#endif /* MAKEFILE */

#endif /* _FLUENT_VERSION_H */
