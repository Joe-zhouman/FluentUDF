/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

typedef enum
{
  GVAR_SOLVE,
  GVAR_ALGEBRAIC,
  GVAR_NONE,
  GVAR_HYBRID
} Gvar_Type;

typedef struct Geqn_Struct
{
  cxboolean aniso_gvar_diff;
  cxboolean curvature;
  real cusp_g_gmag_limit;
  real dfac;
  int verbosity;
  Gvar_Type gvar_type;
  real gvar_lim;
} Geqn_Par;

FLUENT_EXPORT cxboolean reinitialized_g;
FLUENT_EXPORT Gvar_Type gvariance_type;
FLUENT_EXPORT real algebraic_var_const;
FLUENT_EXPORT cxboolean Reinitialize_G(Domain *domain, cxboolean setCells,
                                       cxboolean setBounds,
                                       cxboolean first_flame);
FLUENT_EXPORT void calcProg(Domain *domain, cxboolean flame,
                            cxboolean cellSizeCached, cxboolean correctG);
FLUENT_EXPORT Gvar_Type get_gvar_type(char *gvar_switch);
FLUENT_EXPORT real get_gvar(cell_t c, Thread *t, Gvar_Type gvar_type,
                            cxboolean limit_gvar, cxboolean cellSizeCached);
FLUENT_EXPORT Geqn_Par *getGeqnPar(void);
FLUENT_EXPORT void Model_Initialize_geqn(void);
FLUENT_EXPORT void geqn_model_init(void);
FLUENT_EXPORT void Update_Premixed_Combustion_Temperature(Domain *domain);
