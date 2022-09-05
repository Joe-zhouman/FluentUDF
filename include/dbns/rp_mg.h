/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_RP_MG_H
#define _FLUENT_RP_MG_H

#include "dll.h"

FLUENT_EXPORT void RP_Multigrid_Cycle(Domain *domain, int level, int pass);
FLUENT_EXPORT void RP_FMG_Multigrid_Cycle(Domain *domain);
FLUENT_EXPORT void RP_MG_Restrict(Domain *d, Domain *cdomain);
FLUENT_EXPORT void RP_MG_Interp(Domain *d, Domain *cdomain);
FLUENT_EXPORT void RP_MG_Interp_Solution(Domain *d, Domain *cdomain);

/*used by FMG */
typedef struct _TPair
{
  int  t_id;
  int  t2_id;
  char str[64];
} TPair;

#define MaxMixPThreads 1024

extern FLUENT_EXPORT TPair   FMG_MixPProfTList[MaxMixPThreads];
extern FLUENT_EXPORT int     FMG_NTPairs;
FLUENT_EXPORT int     FMG_InsertTPair(int t_id, int t2_id, const char *str, int nr);
extern FLUENT_EXPORT cxboolean used_by_FMG;
extern FLUENT_EXPORT int     FMG_clevel;
extern FLUENT_EXPORT real    FMG_ResN;
extern FLUENT_EXPORT cxboolean FMG_fine_domain_iter_p;
FLUENT_EXPORT void    FMG_Update_Mixing_Plane_Profiles(Domain *domain);
FLUENT_EXPORT void Fill_Coarse_Domain_Svars(Domain *, Svar [], int nvars);
FLUENT_EXPORT void Apply_Coarse_Domain_Svars(Domain *, Svar [], int nvars);


#endif /* _FLUENT_RP_MG_H */
