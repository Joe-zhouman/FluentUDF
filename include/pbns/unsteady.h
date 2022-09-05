/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */


#ifndef _UNSTEADY_H_
#define _UNSTEADY_H_


#include "global.h"
#include "mem.h"
#include "storage.h"

#include "dll.h"
#include "cxbool.h"
#include "seem.h"

typedef enum
{
  CONSTANT_EXTRAPOLATION,
  FIRST_ORDER_LINEAR_EXTRAPOLATION,
  SECOND_ORDER_LINEAR_EXTRAPOLATION,
  QUADRATIC_EXTRAPOLATION,
  LEGACY_EXTRAPOLATION
} Temporal_Extraploations;

typedef enum
{
  FIXED_DT,
  ADAPTIVE_UDF_BASED_DT,
  ADAPTIVE_CFL_BASED_DT,
  ADAPTIVE_ERROR_BASED_DT,
  ADAPTIVE_MULTIPHASE_SPECIFIC_DT
} Time_Step_Size_Methods;

/* Please don't change the order of enum variables*/
typedef enum
{
  ACOUSTIC_CFL = 0,
  FLUX_BASED_CFL = 1,
  CONVECTIVE_CFL = 2,
  VISCOUS_CFL = 3,
  FLOW_BASED_CFL = 4
} Time_Step_Size_CFL_TYPES;

typedef enum
{
  MIN_ALLOWED_DT,
  WEIGHTED_AVERAGE_DT,
  MAX_ALLOWED_DT
} Time_Step_Size_Options;

extern FLUENT_EXPORT real dt_factor;
extern FLUENT_EXPORT real dt_factor_n;
extern FLUENT_EXPORT real dt_factor_M1;
extern FLUENT_EXPORT real dt_factor_M2;

/**
 * \brief External API
 */
FLUENT_EXPORT void unsteady_statistics(Domain *domain, int flag);
FLUENT_EXPORT void AssignCFFUnsteady(Domain *, int);
FLUENT_EXPORT void Accumulate_Statistics(Domain *);
FLUENT_EXPORT void Accumulate_Statistics_Each_CFF(Domain *, int);
FLUENT_EXPORT cxboolean Compute_Fluid_Timestep_Size(Domain *, cxboolean);
FLUENT_EXPORT cxboolean Compute_Fluid_Timestep_Size_Based_on_CFL(Domain *, cxboolean);

/*mesh change (adaption) specific - start  */
FLUENT_EXPORT cxboolean allow_recompute_dt_after_mesh_modified_p;
FLUENT_EXPORT cxboolean recompute_dt_after_mesh_modified_p;
FLUENT_EXPORT void      Set_Recompute_Physical_Timestep_After_Mesh_Change(Domain *, cxboolean);
FLUENT_EXPORT cxboolean Get_Recompute_Physical_Timestep_After_Mesh_Change(Domain *);
FLUENT_EXPORT void          Recompute_Physical_Timestep_After_Mesh_Change(Domain *, int, real *, cxboolean );
FLUENT_EXPORT void Second_Order_Transient_Scheme_Metrics_Update(Domain *, cxboolean);
/*mesh change (adaption) specific  - end  */

FLUENT_EXPORT cxboolean Compute_dt_increment(Domain *, cxboolean);
FLUENT_EXPORT cxboolean Compute_dt_increment_mp_mfluid(Domain *, cxboolean);
FLUENT_EXPORT void Convert_Unsteady_Statistics(Domain *);
FLUENT_EXPORT void Fill_Unsteady_Stat_CFF_Data(Pointer);
FLUENT_EXPORT void Init_Free_Unsteady_Stat_CFF_Storage(Domain *, int);
FLUENT_EXPORT void Initialize_Statistics(Domain *);
FLUENT_EXPORT void Patch_Old_Time_Levels(Domain *, Svar);
FLUENT_EXPORT void Previous_Time_Level_Svars(Svar sv, Svar *sv_m1, Svar *sv_m2);
FLUENT_EXPORT SV_Store_Type store_cff(Thread *t, Svar n);
FLUENT_EXPORT void Update_Old_Time_Levels(Domain *);
FLUENT_EXPORT void Time_Extrapolate_Coeff(real *coeff_PHI_n, real *coeff_PHI_m1, real *coeff_PHI_m2, cxboolean highorder_p);

FLUENT_EXPORT void Set_Delta_Time_Sampled(real time_sampled);

FLUENT_EXPORT void Define_Statistics_Datasets(Pointer);
FLUENT_EXPORT void Clear_Statistics_Datasets(void);
FLUENT_EXPORT void Free_statistics_dataset_storage(Domain *, int);
FLUENT_EXPORT SV_Store_Type store_stat_dataset(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_seg_stat_dataset(Thread *t, Svar n);

FLUENT_EXPORT void Save_Statistics_Datasets(Domain *);
FLUENT_EXPORT void Save_Statistics_Datasets_for_Explicit_Transient_Formulation(Domain *);

FLUENT_EXPORT void General_Exchange_For_Allocated_Svars(Domain *domain);
FLUENT_EXPORT void Exchange_Unsteady_Solution_Vars(Domain *domain);
FLUENT_EXPORT void Exchange_Misc_Solution_Vars(Domain *domain);

FLUENT_EXPORT int get_max_datset_average_over(void);

FLUENT_EXPORT cxboolean fillfaceMovingAverage(Thread *t, char *datasetname, Svar sv);
FLUENT_EXPORT cxboolean resetMovingAverage(Domain *domain, char *datasetname);
FLUENT_EXPORT cxboolean isFullWindowDataAvailable(char *datasetname);

#define CFF_NAME_MAX_SIZE 256
typedef struct
{
  char cffname[CFF_NAME_MAX_SIZE];
  int cffindex;
} UnsStatCffData;

#define DATASET_STRING_MAX_SIZE 256

/*data structures to fill surface statistics data*/
typedef struct
{
  size_t len;     /* Number of scalars */
  real *rlist;     /* List of scalars */
  int i;      /* Surface id */
  char surface_name[DATASET_STRING_MAX_SIZE];
}  Surface_statistics_data;

typedef struct
{
  size_t len;     /* Number of scalars */
  real **moving_avg_data; /* data for moving average*/
  int i;      /* Surface id */
  char surface_name[DATASET_STRING_MAX_SIZE];
}  Surface_statistics_moving_average_data;
#define INIT_MAX_STAT_DATA 500

typedef struct
{
  int dataset_index;
  int nsurfaces;
  Surface_statistics_data *surfaces_mean_data;
  Surface_statistics_data *surfaces_rmse_data;
  Surface_statistics_data *surfaces_min_data;
  Surface_statistics_data *surfaces_max_data;
  Surface_statistics_moving_average_data *surfaces_moving_average_data;
} Statistics_Data;


#define EXPR_STRING_MAX_SIZE 256
typedef struct
{
  char datasetname[DATASET_STRING_MAX_SIZE];
  char expression[EXPR_STRING_MAX_SIZE];
  int *thread_ids;
  int nthreads;
  int *surface_ids;
  char **surface_names;
  int nsurfaces;
  int index;
  char quantity_for_unit[DATASET_STRING_MAX_SIZE];
  int start_timestep;
  int end_timestep;
  cxboolean min;
  cxboolean max;
  cxboolean mean;
  cxboolean rmse;
  cxboolean moving_average;
  int average_over;
  /* TODO real timestep_or_iter_accumulated; */
} Statistics_Dataset;

extern FLUENT_EXPORT UnsStatCffData *cffMap;
extern FLUENT_EXPORT int cffNameIndexLen;

extern FLUENT_EXPORT Statistics_Dataset *stat_datasets;
extern FLUENT_EXPORT int nstat_datasets;

extern FLUENT_EXPORT Statistics_Data *stat_data;
extern FLUENT_EXPORT int nstat_data;

#define SV_CFF_MEAN(i)((Svar)((SV_CFF_0_MEAN+(i)*(SV_CFF_1_MEAN-SV_CFF_0_MEAN))))
#define SV_CFF_RMS(i)((Svar)((SV_CFF_0_RMS+(i)*(SV_CFF_1_RMS-SV_CFF_0_RMS))))

#define SV_STAT_DATASET_MEAN(i) ((Svar)((SV_STAT_DATASET_0_MEAN+(i)*(SV_STAT_DATASET_1_MEAN-SV_STAT_DATASET_0_MEAN))))
#define SV_STAT_DATASET_RMS(i) ((Svar)((SV_STAT_DATASET_0_RMS+(i)*(SV_STAT_DATASET_1_RMS-SV_STAT_DATASET_0_RMS))))
#define SV_STAT_SEG_DATASET_MOV_AVG(i) ((Svar)((SV_STAT_SEG_DATASET_0_MOV_AVG+(i)*(SV_STAT_SEG_DATASET_1_MOV_AVG-SV_STAT_SEG_DATASET_0_MOV_AVG))))

#define SV_STAT_DATASET_MIN(i) ((Svar)((SV_STAT_DATASET_0_MIN+(i)*(SV_STAT_DATASET_1_MIN-SV_STAT_DATASET_0_MIN))))
#define SV_STAT_DATASET_MAX(i) ((Svar)((SV_STAT_DATASET_0_MAX+(i)*(SV_STAT_DATASET_1_MAX-SV_STAT_DATASET_0_MAX))))

#endif

