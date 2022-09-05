/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef FLUENT_MATRIX_TOOLS_H_
# define FLUENT_MATRIX_TOOLS_H_ 1

#include "amgif.h"

typedef struct matrix_stats_struct
{
  int row_count;
  int offdiag_count;
  int coupled_eqn_count;

  int min_neighbors;
  int max_neighbors;

  double diagonal_dominance_max;
  double diagonal_dominance_min;
} Matrix_Stats_t;

extern FLUENT_EXPORT Level *matrix_fine_level_p; /* last fine level solved or read */
extern FLUENT_EXPORT Matrix_Stats_t matrix_stats;

#define MATRIX_ALLOCATE(v, ap, r) Matrix_Allocate((void **)(&(v)), ap, r)

FLUENT_EXPORT void *Matrix_Allocate(void **v, size_t *allocated_size, size_t required_size);
FLUENT_EXPORT int Write_Matrix_P(char *sysname);
FLUENT_EXPORT int Read_Matrix(const char *head);
FLUENT_EXPORT int Write_Matrix(const char *head, int niter, int *ascii_io);
FLUENT_EXPORT int Write_Matrix_Row(int niter, int irow);
FLUENT_EXPORT void Write_Matrix_Diagnostics(void);
FLUENT_EXPORT int Solve_Matrix_Kernel(AMG_Controls controls, Level fine, real *residual0,
                                      void (*solver_kernel)(AMG_Controls controls, Level fine),
                                      void (*preconditioner_kernel)(AMG_Controls controls, Level fine),
                                      int initialize_solution,
                                      int compute_initial_residual,
                                      int check_convergence,
                                      int verbosity);
FLUENT_EXPORT int Solve_Matrix_Base(AMG_Controls controls, Level fine, real residual0[],
                                    char *solver_name,
                                    char *preconditioner_name,
                                    int initialize_solution);
FLUENT_EXPORT int Solve_Matrix(const char *solver_name, const char *preconditioner_name);
FLUENT_EXPORT void Compute_Matrix_Residual(Level fine, double residual[]);
FLUENT_EXPORT void Matrix_Residual(void);
FLUENT_EXPORT void FLUENT_AMG_Residual(void);
FLUENT_EXPORT void Matrix_Statistics(int print);
FLUENT_EXPORT void Read_And_Solve_Matrix_AMG(const char *head);
FLUENT_EXPORT void Print_Coefficients(AMG_Controls controls, Level fine);
FLUENT_EXPORT void Dump_Coefficients(AMG_Controls controls, Level fine);

typedef struct sparse_connectivity_matrix_struct
{
  int rows;
  int cols;
  int nonzeros;
  int *row;
  int *col;
} Sparse_Connectivity_Matrix;

FLUENT_EXPORT void SCM_Resize(int rows, int cols, int nonzeros,
                              Sparse_Connectivity_Matrix *A);
FLUENT_EXPORT void SCM_Count_Nonzeros(Sparse_Connectivity_Matrix *A);
FLUENT_EXPORT void SCM_Reset_Rows(Sparse_Connectivity_Matrix *A);
FLUENT_EXPORT void SCM_Transpose(Sparse_Connectivity_Matrix *A,
                                 Sparse_Connectivity_Matrix *T);
FLUENT_EXPORT void SCM_Product(Sparse_Connectivity_Matrix *A,
                               Sparse_Connectivity_Matrix *B,
                               Sparse_Connectivity_Matrix *R);
FLUENT_EXPORT void SCM_Free(Sparse_Connectivity_Matrix *A);
FLUENT_EXPORT void SCM_Order_Columns(Sparse_Connectivity_Matrix *A);
FLUENT_EXPORT void SCM_Print(Sparse_Connectivity_Matrix *A, char *label);

#endif /* FLUENT_MATRIX_TOOLS_H_ */
