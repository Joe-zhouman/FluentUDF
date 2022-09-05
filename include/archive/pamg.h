/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_PAMG_H
#define _FLUENT_PAMG_H

#include "dll.h"

#define NULL_INDEX  -1
#define MAX_N_SETS  10
#define MAX_SIM_EQ  80   /* 4 * MAX_PHASES for Full Coupled MP */
#define MAX_OVERLAP     2


typedef struct Matrix
{
  int tot_size;     /* # of simultaneous equations             */
  int size;     /* # of solved simultaneous equations      */
  int n_coeffs;     /* # of off-diagonal coefficients          */
  int n_ceqn;     /* # of coupled equations        */

  real *d;      /* matrix diagonal coefficients (size)     */
  real *value;      /* off-diagonal coefficients  (n_coeffs) */
  int *row;     /* row start pointers     (size + 1) */
  int *col;     /* column indices     (n_coeffs) */

  size_t d_size;    /* current allocated size of d vector      */
  size_t value_size;    /* current allocated size of value vector  */
  size_t row_size;    /* current allocated size of row vector    */
  size_t col_size;    /* current allocated size of col vector    */
}
Matrix;


typedef struct Table
{
  int *size[MAX_OVERLAP]; /* number of equations       (n_neighbors) */
  int **map[MAX_OVERLAP]; /* equation indices    (n_neighbors, size) */
}
Table;


typedef struct System
{
  int n_overlap;                /* # of exterior layers                    */
  int n_neighbors;    /* # of neighbors                          */
  int n_compute_nodes;          /* # of compute nodes                      */
  int n_cells;                  /* # of cells in my compute node           */
  int my_id;      /* multiport id                            */
  int *nb_id;                   /* multiport id of neighbor  (n_neighbors) */
  Table intr;     /* interior table                          */
  Table extr;     /* exterior table                          */
}
System;


typedef struct Level
{
  int n_sets;     /* number of sets of equations             */
  int coarsen_on[MAX_N_SETS]; /* equation to coarsen on in each set      */
  int set[MAX_N_SETS + 1];  /* set limit equation indices              */

  System s;     /* neighbor overlap information            */
  Matrix A;     /* coefficient matrix                      */
  real *x;      /* solution vector                         */
  real *b;      /* right hand side vector                  */
  int *child;     /* coarse level child index                */

  int flex_sweeps;    /* number of flexible cycle sweeps         */

  size_t x_size;    /* current allocated size of x vector      */
  size_t b_size;    /* current allocated size of b vector      */
  size_t child_size;    /* current allocated size of child vector  */
}
Level;


typedef enum
{
  FLEXIBLE_CYCLE = 0,
  V_CYCLE = 1,
  W_CYCLE = 2,
  F_CYCLE = 3
}
AMG_Cycle_Type;


typedef enum
{
  SMOOTHER_JACOBI,
  SMOOTHER_GAUSS_SEIDEL
}
AMG_Smoother_Type;


typedef struct AMG_Controls
{
  /* Equation controls. */
  int scale_corrections;
  int cycle_type;
  real termination_epsilon;
  real restriction_epsilon;
  real divergence_epsilon;
  real tolerance;

  /* Coarsening parameters. */
  int max_levels;
  int group_size;

  /* Fixed cycle parameters. */
  int pre_sweeps;
  int post_sweeps;
  int max_cycles;

  /* Flexible cycle parameters. */
  int max_coarse_sweeps;
  int max_fine_sweeps;
  int smoother_sweeps;

  /* Options. */
  int verbosity;
  int smoother;
  int sweep_exchange;
  int global_solve;
}
AMG_Controls;


FLUENT_EXPORT int AMG_Solve(AMG_Controls controls, Level fine, real residual0[]);
FLUENT_EXPORT void Get_Residual(Matrix A, real x[], real b[], real residual[]);
FLUENT_EXPORT void *Resize_Vector(void *v, size_t *allocated_size, size_t required_size);
#if RP_NODE
FLUENT_EXPORT void Reset_Parallel_AMG_Timers(void);
FLUENT_EXPORT void Get_Parallel_AMG_Timers(int *cycles,
                                           int *sweeps,
                                           int *exchanges,
                                           int *global_solve_count,
                                           double *global_solve_time,
                                           int *solve_count,
                                           double *solve_time,
                                           int *global_matrix_size);
#endif /* RP_NODE */

#endif /* _FLUENT_PAMG_H */
