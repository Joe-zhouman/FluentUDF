/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#include "dll.h"


extern FLUENT_EXPORT real m1, m2, m3, m4, int_red_factor;
extern FLUENT_EXPORT cxboolean strategy_modified, start_averaging;
extern FLUENT_EXPORT int interval_count, interval_length, pre_iters, initial_phase, nstr;
extern FLUENT_EXPORT void compute_steering_metrics(Domain *);
extern FLUENT_EXPORT void update_courant_number(void);
extern FLUENT_EXPORT void update_blending_factor(void);
extern FLUENT_EXPORT void init_steering_parameters(void);
