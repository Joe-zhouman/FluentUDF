/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/

#ifndef _SEDM_H
#define _SEDM_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <signal.h>

#include "global.h"
#include "mem.h"
#include "para.h"
#include "sg.h"
#include "metric.h"
#include "flow.h"
#include "sg_mphase.h"
#include "amgif.h"
#include "sg_press.h"
#include "sedmglobal.h"

extern FLUENT_EXPORT void sedm_continuity_fmean_source(Domain *domain, Svar nv);
extern FLUENT_EXPORT void sedm_continuity_fvar_source(Domain *domain, Svar nv);
extern FLUENT_EXPORT void sedm_collect_source(Domain *domain, Svar nv_s, Svar nv_iden);
extern FLUENT_EXPORT void calc_den_inverse_deriv(Domain *d);
#endif
