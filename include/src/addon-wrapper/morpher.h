/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _MORPHER_H_
#define _MORPHER_H_

FLUENT_EXPORT int Open_Morpher_Library(void);
FLUENT_EXPORT void Morph_Mesh(int);
FLUENT_EXPORT void mmo_get_bounding_box(Pointer, real *);
FLUENT_EXPORT void Init_Mesh(void);
FLUENT_EXPORT void Store_Mesh(void);
FLUENT_EXPORT real Mesh_Quality_Morpher(int);
FLUENT_EXPORT int OptNewuoa(int, double *, int, double, double, int *);
FLUENT_EXPORT double objective_function_main(int, double *);
FLUENT_EXPORT cxboolean solver_convergence_check_newuoa(Pointer);
FLUENT_EXPORT double **make2darray(int, int);
FLUENT_EXPORT void free2darray(double **, int, int);
FLUENT_EXPORT void init_param_limits(void);
FLUENT_EXPORT int param_bounded(int, double *);
FLUENT_EXPORT void get_initial_parameter(int, double *);

void print_thread_coords(cxindex);

FLUENT_EXPORT void Create_Bounding_Region(Pointer);
FLUENT_EXPORT void Delete_Bounding_Region(const char *);
FLUENT_EXPORT int Add_Custom_CP(Pointer);
FLUENT_EXPORT void Edit_Custom_CP(Pointer, Pointer);
FLUENT_EXPORT void Delete_Custom_CP(int);
FLUENT_EXPORT void Add_Parametric_Motion(Pointer);
FLUENT_EXPORT void Delete_Parametric_Motion(Pointer);
FLUENT_EXPORT void Add_Deformation_Settings(Pointer, Pointer);
FLUENT_EXPORT void Delete_Deformation_Settings(Pointer, Pointer);
FLUENT_EXPORT void Clean_Morpher_Settings(void);
FLUENT_EXPORT real Get_MinCP_Dist(void);
FLUENT_EXPORT Pointer Get_Bcp_Coords(Pointer);
FLUENT_EXPORT void Enable_Boundary_Cont(int, const char *);
FLUENT_EXPORT Pointer Cluster_Zone_Morpher(int, int);

typedef struct morpher_deformation_parameters
{
  int reg, cp, par;
  float scafac[3];
} dpar;

typedef struct residual_settings
{
  Pointer eqn;
  cxboolean checkconvg;
  float valconvg;
} resid;

typedef struct parameter_bounds
{
  char *pname;
  cxboolean check_bounds[2];
  double lim[2];
} pbounds;

Pointer lmorph_mmo (Pointer);
Pointer literate_mmo(Pointer);
Pointer ludfondemand_mmo(Pointer);
Pointer lcheckudfondemand_mmo(Pointer);
Pointer lgridcheck_mmo(void);
Pointer lmeshquality_mmo(Pointer);
Pointer lsolverresiduals_mmo(void);
Pointer linitflow_mmo(void);
#endif
