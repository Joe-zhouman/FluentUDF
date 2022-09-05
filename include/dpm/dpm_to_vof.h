/*
 * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _DPM_TO_VOF_H
#define _DPM_TO_VOF_H

#include "dll.h"         /* FLUENT_EXPORT */
#include "mem.h"         /* Domain */
#include "sg_vof.h"
#include "dpm_types.h"   /* Injection */


FLUENT_EXPORT void Add_pp_to_DPM_to_VOF(Injection *I, Particle **ptr_to_prev_next, Particle *pp);
FLUENT_EXPORT cxboolean Check_and_Add_tp_to_DPM_to_VOF(Tracked_Particle *tp, CX_Cell_Id *PcCell);
FLUENT_EXPORT void Add_tp_to_DPM_to_VOF(Tracked_Particle *tp);
FLUENT_EXPORT int  Do_LWF_to_VOF_and_vv(Domain *);
FLUENT_EXPORT int  Do_DPM_to_VOF(Domain *);
FLUENT_EXPORT void Model_Initialize_dpm_to_vof(void);

#endif   /* ndef _DPM_TO_VOF_H */

