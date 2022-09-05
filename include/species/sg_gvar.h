/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

FLUENT_EXPORT void Solve_gvar(Domain *domain, cxboolean aniso_diff,
                              Objp **spark_cells);
FLUENT_EXPORT void update_boundary_gvar(Domain *domain, Gvar_Type gvar_type);
FLUENT_EXPORT int residual_gvar(Domain *domain, Var_Attribute *sv,
                                SV_Residual_Code code);
FLUENT_EXPORT SV_Store_Type store_gvar(Thread *t, Svar nv);

