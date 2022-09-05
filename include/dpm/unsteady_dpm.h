/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#include "dpm_dist.h"   /* Dpm_Distribution */

enum
{
  UNSTEADY_INIT,
  UNSTEADY_ACCUM,
  UNSTEADY_CONVERT,
  UNSTEADY_RESET_IF_ZERO_TIME_SAMPLED
};


FLUENT_EXPORT void thread_unsteady_statistics_dpm(Thread *t, Svar v, Svar v_mean, real physical_dt,
                                                  real del_tim_samp_dpm, real del_tim_samp_dpm_volfrac, int flag);
FLUENT_EXPORT void initialize_thread_unsteady_statistics_dpm(Thread *t, Svar var_dpm_tstat, real del_tim_samp_dpm,
                                                             real del_tim_samp_dpm_volfrac, int flag);
FLUENT_EXPORT void
accumulate_thread_unsteady_statistics_dpm(Thread *t, Svar var, Svar var_dpm_tstat, real physical_dt, Dpm_Distribution *dist);


FLUENT_EXPORT double cellDPMTransientStat(cell_t c, Thread *t, int vindex);

FLUENT_EXPORT void thread_unst_stat_scr_urea_depo_risk(Thread *t, Svar v, Svar v_mean, real physical_dt, real delta_time_sampled, int flag);

