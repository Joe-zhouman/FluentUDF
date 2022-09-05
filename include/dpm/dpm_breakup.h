/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DPM_BREAKUP_H
#define _FLUENT_DPM_BREAKUP_H

#include "global.h"
#include "dpm_types.h"

/*************************************************************
 * Breakup models
 *************************************************************/

#define MAX_CHILD_DROPS 200
#define N_CLASSES 100

FLUENT_EXPORT void Reset_Breakup(Tracked_Particle *tp);
FLUENT_EXPORT cxboolean Init_Breakup(Tracked_Particle *);
FLUENT_EXPORT real Stick(real, real, real);
FLUENT_EXPORT void Move_Matter_from_Parcel_to_Parcel(Particle *big, Particle *little, real numcoll, int ndim);
FLUENT_EXPORT real Compute_Levich_Core_Length(Tracked_Particle *);
FLUENT_EXPORT void Levich_Breakup(Tracked_Particle *);
FLUENT_EXPORT void Tab_Breakup(Tracked_Particle *, Particle *, cxboolean);
FLUENT_EXPORT void Wave_Breakup(Tracked_Particle *, Particle *, cxboolean);
FLUENT_EXPORT void SSD_Breakup(Tracked_Particle *, Particle *, cxboolean);
FLUENT_EXPORT void Madabhushi_Breakup(Tracked_Particle *tp, Particle *pp, cxboolean update);
FLUENT_EXPORT void PilchErdman_Breakup(Tracked_Particle *tp, Particle *pp, cxboolean update);
FLUENT_EXPORT void Schmehl_Breakup(Tracked_Particle *tp, Particle *pp, cxboolean update);
FLUENT_EXPORT void Breakup_Particle(Tracked_Particle *, Particle *, cxboolean);
FLUENT_EXPORT Breakup_Type Init_Breakup_Type(Particle *);

#endif /* #ifndef _FLUENT_DPM_BREAKUP_H */
