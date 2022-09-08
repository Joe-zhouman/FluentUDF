/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/* Functions for setting and evaluating polynomials used in property calculations
   etc. */

#ifndef _CORTEX_CXPOLY_H
#define _CORTEX_CXPOLY_H

#include "dll.h"

#define POLYNOMIAL_DATA_SIZE        100
#define POLYNOMIAL_MAX_COEFFS       8
#define POLYNOMIAL_MAX_PAIRS        (POLYNOMIAL_DATA_SIZE/2)
#define POLYNOMIAL_PIECEWISE_LENGTH (POLYNOMIAL_MAX_COEFFS+4)  /* min, max + coeffs */
#define POLYNOMIAL_MAX_RANGES       (POLYNOMIAL_DATA_SIZE/POLYNOMIAL_PIECEWISE_LENGTH)

/* copied from cortex/cxprofile.h
   (can't include the file directly because it has prototypes which use
   Widget etc structures not defined in any of client includes
   */
#define CX_PROFILE_CONSTANT   "constant"
#define CX_PROFILE_POLYNOMIAL   "polynomial"
#define CX_PROFILE_HARMONIC   "harmonic"
#define CX_PROFILE_PIECEWISE    "piecewise-polynomial"
#define CX_PROFILE_NASA_PIECEWISE    "nasa-9-piecewise-polynomial"
#define CX_PROFILE_LINEAR   "piecewise-linear"

typedef enum
{
  POLYNOMIAL = 0,
  PIECEWISE_POLYNOMIAL,
  PIECEWISE_LINEAR,
  HARMONIC,
  NASA_PIECEWISE_POLYNOMIAL
} Poly_type;

typedef enum
{
  POLY_FUNC_OF_TEMP,
  POLY_FUNC_OF_X,
  POLY_FUNC_OF_Y,
  POLY_FUNC_OF_Z,
  POLY_FUNC_OF_TIME,
  POLY_FUNC_OF_VN,
  POLY_FUNC_OF_ANGLE,
  POLY_FUNC_OF_DIAMETER,
  POLY_FUNC_OF_PRESS,
  POLY_FUNC_OF_REL_VEL,
  POLY_FUNC_OF_SOC,
  POLY_FUNC_OF_CS,
  POLY_FUNC_OF_CE,
  POLY_FUNC_OF_SOL
} Poly_Func;

typedef struct polynomial_struct
{
  Poly_type type;
  Poly_Func func_of;
  int n_ranges;   /* number of ranges for piecewise polynomial or piecewise linear */
  int n_coeffs[POLYNOMIAL_MAX_RANGES];
  float data[POLYNOMIAL_DATA_SIZE];  /* a0, a1, ... for single polynomial,
               x0, y0, x1, y1, .... for piecewise linear,
               xmin_0, xmax_0, a0_0, a1_0, ... a8_0,
               xmin_1, xmax_1, a0_1 ...
               for piecewise polynomials */
} Polynomial;

/* single polynomial */
#define PY_NCOEFFS(p)((p)->n_coeffs[0])
#define PY_COEFF(p,i)((p)->data[(i)])

/* piece-wise polynomial */
#define PPY_NRANGES(p)((p)->n_ranges)
#define PPY_NCOEFFS(p,i)((p)->n_coeffs[(i)])
#define PPY_XMIN(p,i)   ((p)->data[(i)*POLYNOMIAL_PIECEWISE_LENGTH      ])
#define PPY_XMAX(p,i)   ((p)->data[(i)*POLYNOMIAL_PIECEWISE_LENGTH+1    ])
#define PPY_YMIN(p,i)   ((p)->data[(i)*POLYNOMIAL_PIECEWISE_LENGTH+2     ])
#define PPY_YMAX(p,i)   ((p)->data[(i)*POLYNOMIAL_PIECEWISE_LENGTH+3    ])
#define PPY_COEFF(p,i,j)((p)->data[(i)*POLYNOMIAL_PIECEWISE_LENGTH+4+(j)])

/* piece-wise linear */
#define PL_NRANGES(p)((p)->n_ranges)
#define PL_XMIN(p,i)((p)->data[2*(i)  ])
#define PL_YMIN(p,i)((p)->data[2*(i)+1])
#define PL_XMAX(p,i)((p)->data[2*(i)+2])
#define PL_YMAX(p,i)((p)->data[2*(i)+3])


/* these are only applicable for old style single range polynomials */
#define POLYNOMIAL_NUM_COEFF(p) (p)->n_coeffs[0]
#define POLYNOMIAL_COEFF(p,n) (p)->data[n]

FLUENT_EXPORT Polynomial *allocate_polynomial(void);
FLUENT_EXPORT void set_polynomial(Polynomial *p, Pointer x);
FLUENT_EXPORT float evaluate_polynomial(Polynomial *p, float x);
FLUENT_EXPORT float evaluate_polynomial_derivative(Polynomial *p, float x);
FLUENT_EXPORT double evaluate_polynomial_integral(Polynomial *p, double x0, double x1);
FLUENT_EXPORT double evaluate_polynomial_over_x_integral(Polynomial *p, double x0, double x1);
FLUENT_EXPORT void prep_before_eval_poly_in_openmp(void);
FLUENT_EXPORT void done_after__eval_poly_in_openmp(void);

#endif /* _CORTEX_CXPOLY_H */
