/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FIELD_EXPRS_
#define _FIELD_EXPRS_

#ifdef __cplusplus
extern "C" {
#endif

#include "global.h"
#include "mem.h"
#include "expr/ExprC.h"


FLUENT_EXPORT cxboolean Eval_Expr_Profile (const char *exp_str, Thread *thread, real *outputArray);
FLUENT_EXPORT cxboolean Eval_Expr_Face_Thread_Node_Profile(const char *exp_str, Thread *thread, double *outputArray);
FLUENT_EXPORT real Eval_Expr_Profile_Single_Val(int *status, const char *exp_str, Thread *t);
FLUENT_EXPORT void *Expr_Get_Property_Object(const char *defn);
FLUENT_EXPORT void Expr_Free_Property_Object(void *property);
double Expr_Eval_Property(cell_t c, Thread *t, Property *p, int id, real T);
FLUENT_EXPORT double Expr_Eval_Property_Temperature_Derivative(cell_t c, Thread *t, Property *p, int id, real T);
FLUENT_EXPORT double Expr_Eval_Property_Pressure_Derivative(cell_t c, Thread *t, Property *p, int id, real T);
FLUENT_EXPORT cxboolean Expr_Property_Is_Pressure_Dependent(Property *p, int id);
FLUENT_EXPORT cxboolean Expr_Property_Is_Temperature_Dependent(Property *p, int id);


ExprContextHandle Get_Expr_Context_Handle_For_Thread(
  Thread *thread,
  const char *serviceName,
  ExprContextHandle parentContext,
  cxboolean considerAdjCellValues);
ExprContextHandle Get_Expr_Context_Handle_For_Surface(
  char *thread,
  const char *serviceName,
  ExprContextHandle parentContext);
ExprContextHandle Get_Expr_Context_Handle_For_Domain(
  Domain *domain,
  const char *serviceName,
  cxboolean considerAdjCellValues);
ExprContextHandle Get_Expr_Context_Handle_For_Thread_List(
  Thread **threadList,
  int numThread,
  const char *serviceName,
  cxboolean considerAdjCellValues);
ExprContextHandle Get_Expr_Context_Handle_For_Thread_Surface_List(
  Thread **threadList,
  int numThread,
  char **surfaceList,
  int numSirface,
  const char *serviceName,
  cxboolean considerAdjCellValues);
DataServiceHandle Get_Expr_DataService_Handle(const char *serviceName);

cxboolean Expr_Is_Named_Expr(const char *str, char *expr_name);
void Expr_Fill_Post_Data(Domain *domain, char *name, Svar sv,
                         cxboolean fill_cell_values,
                         cxboolean fill_boundary_values,
                         cxboolean compute_node_values);

FLUENT_EXPORT void Expr_Fill_Post_Data_With_IExpr(Domain *domain, const char *name,
                                                  ExprHandle expression, Svar sv,
                                                  cxboolean fill_cell_values,
                                                  cxboolean fill_boundary_values,
                                                  cxboolean compute_node_values,
                                                  cxboolean update_min_max);
#if RP_DOUBLE
#define Expr_Fill_Array_Real Expr_Fill_Array_Double
#else
#define Expr_Fill_Array_Real Expr_Fill_Array_Float
#endif


#ifdef __cplusplus
}
#endif
#endif
