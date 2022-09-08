/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef REPAIR_GRAD_H
#define REPAIR_GRAD_H

extern FLUENT_EXPORT cxboolean Store_Hinv_Norm(void);
extern FLUENT_EXPORT void Model_Initialize_repair(void);
extern FLUENT_EXPORT void Repair_Gradient(Domain *PTR_RESTRICT domain,
                                          Svar w, Svar gw);
extern FLUENT_EXPORT void Compute_Grad_Quality_Measure(Domain *d);
/**
   info:
   for segregated vector variables
   the 'eqn' argument will be used
   as index in the vector field.
 */
extern FLUENT_EXPORT void Repair_Solution(Domain *PTR_RESTRICT domain,
                                          int eqn, Svar nv, char *name, real omega,
                                          AMG_System_Type amg_id,
                                          cxboolean delta_form);
extern FLUENT_EXPORT void Set_Bad_Cells_Mark(Domain *domain);
extern FLUENT_EXPORT void Release_Bad_Cells_Mark(Domain *domain);

typedef enum
{
  REPAIR_GRADIENT_INI = -1,
  REPAIR_GRADIENT_OFF = 0,  /* disable alltogether */
  REPAIR_GRADIENT_JAVG,     /* average gradients in a jacobi update style */
  REPAIR_GRADIENT_NO_GRAD,
  REPAIR_GRADIENT_HINV,
  REPAIR_GRADIENT_NO_GRAD_REALLY
} repair_gradient_mode_t;

typedef enum
{
  REPAIR_SLTN_OFF = 0,
  REPAIR_SLTN_JAVG
} repair_sltn_mode_t;

/* avoid conflicts with SV_FLAGS */
extern Svar sv_pmn_flags;
#define C_PMN_FLAGS(c,t) C_STORAGE_UI(c,t,sv_pmn_flags)
#define C_PMN_FLAG(c,t,mask) (C_PMN_FLAGS(c,t) & (mask))
#endif
