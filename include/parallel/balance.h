/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_BALANCE_H
#define _FLUENT_BALANCE_H

#include "dll.h"

FLUENT_EXPORT cxboolean Calculate_Balanced_Partitions(Domain *, int, int, double *, double *);
FLUENT_EXPORT void Print_Time_Stamps_To_File(Domain *);
FLUENT_EXPORT void Print_Global_Timer_Offsets(void);
FLUENT_EXPORT void Calculate_Global_Timer_Offset(void);
FLUENT_EXPORT void Clear_Balance_Timer_History(void);
FLUENT_EXPORT void Load_Balance_Before_Adaption(Domain *);
FLUENT_EXPORT cxboolean Load_Balance_Before_Killing_Compute_Node(Domain *, int);
FLUENT_EXPORT int Repartition_Before_Balancing(Domain *);
FLUENT_EXPORT void Load_Balance(Domain *);
enum
{
  BALANCE_ENUMERATE_SEQUENCE,
  BALANCE_COMBINE_SEQUENCE,
#if RP_METIS
  BALANCE_METIS
#endif
};
typedef struct lbalance_tag
{
  /* weights */
  /* base */
  double wbase;
  /* 0-fluid, 1-solid */
  double wmaterial[2];
  int balance_material;
  double a[2][2];
  double b[2];

  /* imbalance_threshold 10% as default*/
  real balance_threshold;


} lbalance_t;

extern lbalance_t lbalance;
#endif /* _FLUENT_BALANCE_H */
