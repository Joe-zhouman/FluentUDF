/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SG_GLOB_H
#define _FLUENT_SG_GLOB_H

#include "dll.h"

#if RP_S2S

typedef struct surface_s_glob_struct
{
  Thread *thread;             /* thread to which the faces belong */
  Objp  *f_list;              /* link list of faces in the glob */
} SGlob;

extern FLUENT_EXPORT SGlob *sglob;

FLUENT_EXPORT  void Get_Globs_Info(int *n_sglobs);
FLUENT_EXPORT  cxboolean Get_SGlobs_Done(void);
FLUENT_EXPORT  void Set_SGlobs_Done(cxboolean status);
FLUENT_EXPORT  void Update_Globs_Memory(void);
FLUENT_EXPORT  void Group_Globs(Domain *domain);
FLUENT_EXPORT  void Get_SGlob( int glob_id, Objp **face_list);
FLUENT_EXPORT  void Delete_All_SGroups(void);
FLUENT_EXPORT  int Write_S2S_Header_Section(Domain *domain, FILE *fd, cxboolean binary);
FLUENT_EXPORT  int Write_S2S_Vars(Domain *domain, FILE *fd, cxboolean binary);

#endif /* RP_S2S */

#endif /* _FLUENT_SG_GLOB_H */

