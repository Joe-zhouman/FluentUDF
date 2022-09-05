/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef ADDON_WRAPPER_TABULATION_H_
#define ADDON_WRAPPER_TABULATION_H_

/**
 * \file
 * \brief Wrapper interface for AFD tabulation module
 */

#include "global.h" /* Need arithmetic type (real) and CX_Malloc */


/** Opaque pointer for 1D tables */
typedef void *p_Table_1D;
/** Function type that takes a single argument and returns a real value */
typedef real (*Function_1D)(const real x);

/** Opaque pointer for 2D tables */
typedef void *p_Table_2D;
/** Function type that takes two arguments and returns a real value */
typedef real (*Function_2D)(const real x0, const real x1);

/**
 * \brief A structure holding tabulation function pointers.
 */
typedef struct Structured_Cartesian_Tables_Functions_struct
{
  p_Table_1D (*Create_1D_From_Data)(const char *nameIn,
                                    const char *nameOut,
                                    const int npoints,
                                    const real *points,
                                    const real *values);
  p_Table_1D (*Create_1D_From_Function)(const char *nameIn,
                                        const char *nameOut,
                                        Function_1D f,
                                        const int n_initial_points,
                                        const real *initial_points,
                                        const real tolerance);
  void (*Delete_1D)(p_Table_1D table);
  void (*Export_1D)(const char *filename,
                    p_Table_1D table);
  void (*Get_Data_1D)(const p_Table_1D table,
                      int *npoints,
                      const real **points,
                      const real **values);
  real (*Lookup_1D)(p_Table_1D table,
                    const real x);
  real (*Derivative_1D)(p_Table_1D table,
                        const real x);
  real (*BlendedDerivative_1D)(p_Table_1D table,
                               const real x);

  p_Table_2D (*Create_2D_From_Data)(const char *nameIn0,
                                    const char *nameIn1,
                                    const char *nameOut,
                                    const int npoints0,
                                    const real *points0,
                                    const int npoints1,
                                    const real *points1,
                                    const real *values);
  p_Table_2D (*Create_2D_From_Function)(const char *nameIn0,
                                        const char *nameIn1,
                                        const char *nameOut,
                                        Function_2D f,
                                        const int n_initial_points,
                                        const real *initial_points0,
                                        const real *initial_points1,
                                        const real tolerance);
  void (*Delete_2D)(p_Table_2D table);
  void (*Export_2D)(const char *filename,
                    p_Table_2D table,
                    p_Table_1D saturationT,
                    p_Table_1D saturationProp,
                    p_Table_1D spinodalT,
                    p_Table_1D spinodalProp);
  void (*Get_Data_2D)(const p_Table_2D table,
                      int *npoints0,
                      const real **points0,
                      int *npoints1,
                      const real **points1,
                      const real **values);
  real (*Lookup_2D)(p_Table_2D table,
                    const real x0,
                    const real x1);
  real (*Derivative_X0_2D)(p_Table_2D table,
                           const real x0,
                           const real x1);
  real (*Derivative_X1_2D)(p_Table_2D table,
                           const real x0,
                           const real x1);
  real (*BlendedDerivative_X0_2D)(p_Table_2D table,
                                  const real x0,
                                  const real x1);
  real (*BlendedDerivative_X1_2D)(p_Table_2D table,
                                  const real x0,
                                  const real x1);
} Structured_Cartesian_Tables_Functions_Type;

extern Structured_Cartesian_Tables_Functions_Type *Structured_Cartesian_Tables_Functions;

#define Table1D_Create_From_Data(si,so,n,p,v) Structured_Cartesian_Tables_Functions->Create_1D_From_Data(si,so,n,p,v)
#define Table1D_Create_From_Function(si,so,f,n,p,tol) Structured_Cartesian_Tables_Functions->Create_1D_From_Function(si,so,f,n,p,tol)
#define Table1D_Delete(t) Structured_Cartesian_Tables_Functions->Delete_1D(t)
#define Table1D_Export(t,s) Structured_Cartesian_Tables_Functions->Export_1D(t,s)
#define Table1D_Get_Data(t,n,p,v) Structured_Cartesian_Tables_Functions->Get_Data_1D(t,n,p,v)

#define Table2D_Create_From_Data(si0,si1,so,n0,p0,n1,p1,v) Structured_Cartesian_Tables_Functions->Create_2D_From_Data(si0,si1,so,n0,p0,n1,p1,v)
#define Table2D_Create_From_Function(si0,si1,so,f,n,p0,p1,tol) Structured_Cartesian_Tables_Functions->Create_2D_From_Function(si0,si1,so,f,n,p0,p1,tol)
#define Table2D_Delete(t) Structured_Cartesian_Tables_Functions->Delete_2D(t)
#define Table2D_Export(s,t,satT,satProp,spinT,spinProp) Structured_Cartesian_Tables_Functions->Export_2D(s,t,satT,satProp,spinT,spinProp)
#define Table2D_Get_Data(t,n0,p0,n1,p1,v) Structured_Cartesian_Tables_Functions->Get_Data_2D(t,n0,p0,n1,p1,v)

cxboolean Load_Tabulation_Library(void);
cxboolean Unload_Tabulation_Library(void);

/**
 * \brief Structure for 1D table with range check information.
 */
typedef struct table_1d_with_range_check_struct
{
  p_Table_1D table; /**< the table */
  real xmin;        /**< lower range */
  real xmax;        /**< upper range  */
  int nmin;         /**< no. of calls out of lower range */
  int nmax;         /**< no. of calls out of upper range  */

  real xcrit;       /**< critical value for argument limiting */
} Table_1D_With_Range_Check;

void Table1D_Initialize_Range_Check(Table_1D_With_Range_Check *table, p_Table_1D table_without_check, const real xcrit);
real Table1D_Lookup(Table_1D_With_Range_Check *table, const real x);
#define Table1D_Derivative(t,x,blended) ((blended) ? Structured_Cartesian_Tables_Functions->BlendedDerivative_1D((t)->table,x) : Structured_Cartesian_Tables_Functions->Derivative_1D((t)->table,x))

/**
 * \brief Structure for 2D table with range check information.
 */
typedef struct table_2d_with_range_check_struct
{
  p_Table_2D table; /**< the table */
  real xmin0;       /**< lower range for 1st argument */
  real xmax0;       /**< upper range for 1st argument */
  real xmin1;       /**< lower range for 2nd argument */
  real xmax1;       /**< upper range for 2nd argument */
  int nmin0;        /**< no. of calls out of lower range for 1st argument */
  int nmax0;        /**< no. of calls out of upper range for 1st argument */
  int nmin1;        /**< no. of calls out of lower range for 2nd argument */
  int nmax1;        /**< no. of calls out of upper range for 2nd argument */

  int iclip;        /**< clipping option: 0=off, 1=x0lim, 2=x0bnd */
  p_Table_1D x0bnd; /**< boundary table for first argument */
  p_Table_1D valbnd;/**< boundary table for property values */
  p_Table_1D x0lim; /**< limiter for first argument */
  real x0crit;      /**< critical value x0 for boundary curve clipping */
  real x1crit;      /**< critical value x1 for boundary curve clipping */
  cxboolean x0bndlo;/**< boundary applied as lower or upper limit for x0 */
} Table_2D_With_Range_Check;

Table_2D_With_Range_Check *Table2D_Create_With_Range_Check(p_Table_2D table, const int iclip, p_Table_1D x0bnd, p_Table_1D valbnd, p_Table_1D x0lim, const real x0crit, const real x1crit, const cxboolean x0bndlo);
real Table2D_Lookup(Table_2D_With_Range_Check *table, const real x0, const real x1);
real Table2D_Derivative_X0(Table_2D_With_Range_Check *table, const real x0, const real x1, const cxboolean blended);
real Table2D_Derivative_X1(Table_2D_With_Range_Check *table, const real x0, const real x1, const cxboolean blended);

#endif /* ADDON_WRAPPER_TABULATION_H_ */
