/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_MIX_PLANE_H
#define _FLUENT_MIX_PLANE_H

#include "dll.h"
#include "slide.h"

typedef enum
{
  GEN_SCALAR = 0,
  GEN_VECTOR,
  DB_QS,
  DB_RECONGRAD_QS,
  DB_GRAD_QS,
  PB_VELCOMP
}
Eqn_Type;

FLUENT_EXPORT Pointer Update_Imp_Mpm_Settings(Domain *domain, Pointer var);
FLUENT_EXPORT void Compute_Implicit_MPM(Domain *domain, Svar sv, Svar sv2, Svar sv3, Eqn_Type eqn_type);
FLUENT_EXPORT void Scale_GCM(Domain *domain);
FLUENT_EXPORT void Debug_GCM(Domain *domain);
FLUENT_EXPORT void List_MPM_Settings(Domain *domain);
FLUENT_EXPORT cxboolean Is_MPM_Zone_Attached(Domain *domain, Thread *t);
FLUENT_EXPORT void Create_Strips_Implicit_MPM(Sliding_interface *si, Thread *thread, Thread *t_sb_str);
#endif /* _FLUENT_MIX_PLANE_H */
