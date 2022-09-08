/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _AMG_HYGRID_HEADER_
#define _AMG_HYGRID_HEADER_

FLUENT_EXPORT void Use_Hybrid_AMG_System(int sys_id);
FLUENT_EXPORT int If_AMG_Hybrid(AMG_Controls *amg, Level *g, int nlevel);
FLUENT_EXPORT int AMG_Global_Matrix_To_Blocks
(Level *g, int *part, AMG_Controls *amg, AMG_Methods *amg_methods);
FLUENT_EXPORT int AMG_Block_Solution(Level *g, AMG_Controls *amg);
FLUENT_EXPORT int AMG_Block_Global_Solution(AMG_Controls *amg, System *s);
FLUENT_EXPORT int AMG_Update_Hybrid_Exterior(System *s, real *x);

FLUENT_EXPORT int AMG_Create_X_Col_Map(Level *f, Level *g);
FLUENT_EXPORT void AMG_Collect(void *p, int s, int if_x_map, int if_real,
                               int unit, int root);
FLUENT_EXPORT void AMG_Dispatch(void *p, int s, int if_x_map, int if_real,
                                int unit, int root);
FLUENT_EXPORT int do_global_cycles(Level *PTR_RESTRICT g);
FLUENT_EXPORT void Destroy_Hybrid_Coarse_Levels(int sys_id);
FLUENT_EXPORT Level *Make_Hybrid_Levels(Level *, AMG_Controls *, AMG_Methods *, cxboolean);
FLUENT_EXPORT int Get_Master_Comm(void *);
FLUENT_EXPORT int Get_Machine_Comm(void *);
FLUENT_EXPORT void Exchange_Buffer_Hybrid(System *, void *, int,
                                          Exchange_Stage);
FLUENT_EXPORT int AMG_Solve_Hybrid_Group(Level *, AMG_Controls *);
FLUENT_EXPORT int AMG_Solve_Hybrid_Final(Level *, AMG_Controls *);
FLUENT_EXPORT Level *Group_Matrix(Level *, AMG_Controls *, int, int *);
FLUENT_EXPORT void Ungroup_Solution(Level *);
FLUENT_EXPORT void Group_Solution_and_Source(Level *);
#endif
