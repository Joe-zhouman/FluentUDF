/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef KRYLOV_H
#define KRYLOV_H

typedef int ( krylov_method ) (int n_rows, int n_tot_rows, int n_cols, real *X[], real x[]);
typedef krylov_method *krylov_method_pt;

FLUENT_EXPORT krylov_method mpe;
FLUENT_EXPORT krylov_method rre;


typedef struct
{
  int  ext_counter;
  int iter_counter;
  Svar sv_cell[SV_MAX];
  Svar sv_face[SV_MAX];
  krylov_method_pt method;
  int verbosity;
  int n_rows;
  int n_tot_rows;
  int n_cols;
  int n_skip;
} Krylov_Controls;


FLUENT_EXPORT void Reset_Krylov_Counters(void);
FLUENT_EXPORT void Restart_Krylov(Domain *domain, Krylov_Controls *krylov);
FLUENT_EXPORT void Model_Initialize_Krylov(void);

#endif /* KRYLOV_H */
