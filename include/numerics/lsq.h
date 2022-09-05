/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef LSQ_H
#define LSQ_H
typedef struct _qr_ws
{
  real **a;
  real **ai;
  real **q;
  real **r;
  real *scale;
  real *dumrow;
  real *qtrhs;
  real **v;
  real *vcol;
  real *rhs1;
  real *sol1;
  real **rhs3;
  real **sol3;
  real *dx;
  real **vt;
  real **u;
  real *w;
  real *weights;
  int irow;
  int icol;
  int irowmax;
  int icolmax;
  int freemode;
  cxboolean mrf15;
  cxboolean cell_lsf_weighted ;
  cxboolean os_lsf_qr;
  cxboolean hc_lsf_qr;
  cxboolean lsf_def_grad_x;
  cxboolean lsf_def_grad_y;
  cxboolean lsf_def_grad_z;
} QR_WS;

typedef struct _os_lsf_ws
{
  int irow;
  int icol;
  cxboolean os_lsf_flag;
  cxboolean lsf_def_grad_x;
  cxboolean lsf_def_grad_y;
  cxboolean lsf_def_grad_z;
  QR_WS *qr_ws;
} OS_LSF_WS;

/* NEW hybrid NBG-LSQ functions declaration */

FLUENT_EXPORT void QR_SOLVE( int mode, QR_WS *qr_ws);
FLUENT_EXPORT void QR_Mult_RHS_SOLVE(int nrhs, int mode, QR_WS *qr_ws);
FLUENT_EXPORT void ALLOCATE_SCALAR_QR_WS(QR_WS *qr_ws);
FLUENT_EXPORT void ALLOCATE_VECTOR_QR_WS(QR_WS *qr_ws);
FLUENT_EXPORT void Free_QR_WS(QR_WS *qr_ws);
FLUENT_EXPORT void least_squares (real **, int, int, real [], real []);
FLUENT_EXPORT int svd (real **, int, int, real *, real **);
FLUENT_EXPORT void svd_back_substitution(real **, real *, real **, int, int, real *, real *);
FLUENT_EXPORT int sv_decomposition (real **a, int m, int n, real w[], real **v);
FLUENT_EXPORT void sv_back_substitution (real **u, real w[], real **v, int m, int n, real b[], real x[]);

void qr_mod_gram_shmit(real **a, int m, int n, real **q, real **r, real *scale, QR_WS *qr_ws);
void qr_solve2(real **q, real **r, real *scale, real *rhs, int irow, int icol, real *sol, QR_WS *qr_ws);
FLUENT_EXPORT void QR_SOLVE(int mode, QR_WS *qr_ws);
FLUENT_EXPORT void QR_Mult_RHS_SOLVE(int nrhs, int mode, QR_WS *qr_ws);
FLUENT_EXPORT void svd_inverse (QR_WS *qr_ws, int m, int n);
FLUENT_EXPORT real norm2(real *v, int n);
void Vt_Mat_Mul(real *v_in, real **a_in, int irow, int icol, real *result);
void MatT_V_Mul(real **a_in, real *v_in, int irow, int icol, real *result);
void Vt_V_Mul(real *vt_in, real *v_in, int n, real *result);
void V_Vt_Mul(real *v_in, real *vt_in, int n, real  **result);
void v_mul_diag_inv_lam(real **a, int m, real *Lam);
void mat_a_mul_b_transpose (real **a, int m, int n, int l, real **b, real **c);

FLUENT_EXPORT void ALLOCATE_OS_LSF_WS(OS_LSF_WS *os_lsf);
FLUENT_EXPORT void FREE_OS_LSF_WS(OS_LSF_WS *os_lsf);
#endif /* LSQ_H */
