/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_REORDER_H
#define _FLUENT_REORDER_H

#include "dll.h"

FLUENT_EXPORT void pr_bandwidth(Domain *d);
FLUENT_EXPORT void Order_Objp_C_By_Id(Objp *o);
FLUENT_EXPORT void Order_Objp_F_By_Id(Objp *o);
FLUENT_EXPORT void Order_Objp_V_By_Id(Objp *o);
FLUENT_EXPORT void Order_Objp_T_By_Id (Objp *);
#if RP_EDGE
FLUENT_EXPORT void Order_Objp_E_By_Id(Objp *o);
# if RP_HANG
FLUENT_EXPORT void Order_Objp_E_By_Level(Objp *);
# endif
#endif
FLUENT_EXPORT cxboolean reorder_threads(Thread **t);
FLUENT_EXPORT void Reorder_Cells_By_Position(Domain *d);
FLUENT_EXPORT void Reorder_Cells_By_Partition_Id(Domain *d);
FLUENT_EXPORT void Reorder_Domain(Domain *d, const char *method, cxboolean verbose);
FLUENT_EXPORT void Reorder_Domain_Threads(Domain *d, cxboolean verbose);
FLUENT_EXPORT int Set_C_Index_with_Reorder(cat_t **pold_index, int *ncells,
                                           int *index_start,
                                           int fluid_or_solid, Domain *domain);
FLUENT_EXPORT void Free_Reorder_Memory (cat_t **r, int *nr, Domain *domain);
FLUENT_EXPORT int Reverse_Cuthill_Mckee_Graph(int *, int *, int, int *, int *, int *, int);
FLUENT_EXPORT void Reorder_Cell_Thread(Domain *domain, Thread *tc, cell_t *new_rank, int nc);
FLUENT_EXPORT void Reorder_Cell_Thread_Extended(Domain *domain, Thread *tc, cell_t *new_rank);
FLUENT_EXPORT void Reorder_Face_Thread(Domain *domain, Thread *tf, cell_t *new_rank, int nf);
# if !RP_HOST
FLUENT_EXPORT int Reorder_F(Domain *d);
# endif
FLUENT_EXPORT void Reorder_Cells_Faces_By_Id(Domain *d);
#endif /* _FLUENT_REORDER_H */
