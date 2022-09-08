/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DOMAINS_H
#define _FLUENT_DOMAINS_H

#include "dll.h"

typedef struct domain_model_names_struct
{
  char *label;
  Domain_Model_ID id;
} Domain_Model_Names;


typedef enum
{
  DOMAIN_NULL = 0,
  DOMAIN_GEOM,
  DOMAIN_PHASE,
  DOMAIN_INTERACTION,
  DOMAIN_TYPE_MAX
} Domain_Type;

typedef struct domain_type_names_struct
{
  char *label;
  Domain_Type id;
} Domain_Type_Names;


FLUENT_EXPORT void Create_Phase_Domain(Domain *parent, int child_id,
                                       Domain_Type type);
FLUENT_EXPORT Domain *Lookup_Domain(Domain *, int);
FLUENT_EXPORT Domain *Lookup_Root_Domain(Domain *);
FLUENT_EXPORT void Update_Sub_Domain(Domain *, Domain *);
FLUENT_EXPORT void Free_Phase_Domain(Domain *, int, Domain_Type);
FLUENT_EXPORT void Set_Domain_Variables(Domain *, Pointer);
FLUENT_EXPORT void Set_Mass_Transfer(Domain *, Pointer);
FLUENT_EXPORT void Set_Model_Transition(Domain *, Pointer);
FLUENT_EXPORT void Set_Cavitation(Domain *, Pointer);
FLUENT_EXPORT void Set_Het_Reactions(Domain *, Pointer);
FLUENT_EXPORT Domain_Type domain_type(const char *);
FLUENT_EXPORT void Update_Threads_On_Subdomains(Domain *);
FLUENT_EXPORT void Init_Thread_Sub_Thread_Pointers (Thread *);
FLUENT_EXPORT Thread *create_subthread(Domain *subdomain,
                                       Domain *domain, Thread *thread);
FLUENT_EXPORT void Create_Subdomain_Threads(Domain *);
FLUENT_EXPORT void Sync_Subdomain_Thread_Types(Domain *, int, int *);
extern FLUENT_EXPORT real syamlal_c1, syamlal_d1;

#if RP_NODE
FLUENT_EXPORT void Copy_Domain_Neighborhood(Domain *, Domain *);
#endif

FLUENT_EXPORT Domain *Clone_Domain(Domain *domain);
FLUENT_EXPORT Thread *Clone_Thread(Domain *domain, Domain *newdomain, Thread *thread);

FLUENT_EXPORT int phase_id(Domain *d, const char *name);

#endif /* _FLUENT_DOMAINS_H */
