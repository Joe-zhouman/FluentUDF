/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#include "dll.h"

typedef struct Inert_Struct
{
  cxboolean enabled;
  int initialized;

  /* EGR species list */
  struct
  {
    Material **mat;
    int *indx;
    real *mw;                 /* molecular weight */
  } sp;

  real *xi;
  real *yi;
  real sum_rho_rbar;       /* cached sum of y_i/mw_i * R */
  real ave_mw;             /* cached molecular weight */
  int nspecies;            /* number of inert species */
  real href;               /* reference enthalpy */
  int nHInert;
  real *hInert;
  real hInDtUrf;
  real hTMin, hTMax, hDTemp;
} Inert_Par;

FLUENT_EXPORT char *Inert_Spe_Name(int);
FLUENT_EXPORT void  Inert_Model_Init(Domain *);
FLUENT_EXPORT void  Inert_Model_Reset(void);
FLUENT_EXPORT void  Inert_EGR_Set(Objp *);
FLUENT_EXPORT void  Print_Inert_Parameters(void);
FLUENT_EXPORT real  Inert_Density(cell_t, Thread *, real);
FLUENT_EXPORT real  Inert_Cp(cell_t, Thread *, real);
FLUENT_EXPORT real  Inert_Enthalpy(cell_t, Thread *, real, cxboolean);
FLUENT_EXPORT real  Inert_Temperature(cell_t, Thread *, real, real);
FLUENT_EXPORT real  Inert_Mw(void);
FLUENT_EXPORT real  Inert_href(void);
FLUENT_EXPORT int   Inert_Nspe(void);
FLUENT_EXPORT void  Inert_Yi(real *);
FLUENT_EXPORT real  Inert_Yi_I(int);
FLUENT_EXPORT void  Inert_Xi(real *);
FLUENT_EXPORT real  Inert_Xi_I(int);
FLUENT_EXPORT void  Inert_Variable_Transform(real, real *, real *, real *, real *);
FLUENT_EXPORT void  Model_Initialize_inert(void);
FLUENT_EXPORT void Free_Inert_Parameters(void);
FLUENT_EXPORT cxboolean Inert_Variables_Transformed ;

extern FLUENT_EXPORT Inert_Par inert_par;
