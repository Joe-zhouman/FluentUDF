/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_MIGRATE_H
#define _FLUENT_MIGRATE_H

#if RP_NODE
FLUENT_EXPORT cxboolean
Migrate_Repartitioned_Cells(Domain *, double *, Domain *, char *, int);
FLUENT_EXPORT cxboolean Migrate_Global_Domain_Data(const char *, const char *,
                                                   Svar *, int, cxboolean, cxboolean);
FLUENT_EXPORT cxindex Total_Number_Of_Dest_Cells_Migrating (Domain *);
FLUENT_EXPORT void Set_Migrate_Node_Coord_N (cxboolean);

FLUENT_EXPORT void free_cached_migrate_arrays(void);
FLUENT_EXPORT cxboolean
Count_And_Allocate_Svar_Migrate_List(Domain *, Svar **, int *, cxboolean);
FLUENT_EXPORT void Add_Migrate_Cell_Info_Svar(Domain *, ...);
FLUENT_EXPORT void Remove_Migrate_Cell_Info_Svar(Domain *, ...);
FLUENT_EXPORT void Get_Cell_Info_Svars(int *, Svar **);
void Set_MI_Ext_Cell_Status(Thread *);
#endif /* RP_NODE */

#if RP_HOST || RP_NODE
FLUENT_EXPORT void Print_Migration_Statistics(Domain *);
FLUENT_EXPORT void Migrate_Partitions(Domain *, cxboolean);
#endif /* RP_HOST || RP_NODE */

FLUENT_EXPORT void Ensure_Svars_Allocated(Domain *domain, Svar *sv_list, int count_nv);
FLUENT_EXPORT void Ensure_Svars_Allocated_in_Thread_List(Objp *t_list, Svar *sv_list, int count_nv);
FLUENT_EXPORT cxboolean Is_Svar_Allocated(Domain *domain, Svar nv);
FLUENT_EXPORT cxboolean Is_Svar_Allocated_in_Thread_List(Objp *t_list, Svar nv);
FLUENT_EXPORT cxboolean Is_Svar_Type_Stored_in_Thread_List(Objp *t_list, Svar nv);
#endif /* _FLUENT_MIGRATE_H */
