/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_REMESH_LOCAL_H
#define _FLUENT_REMESH_LOCAL_H

FLUENT_EXPORT void Init_Remesh_Local (Domain *, Objp *);
FLUENT_EXPORT void Free_Remesh_Local (Domain *);

FLUENT_EXPORT cxboolean Check_Coarsening_During_Remesh_Local_Cavities (void);
#if RP_NODE
FLUENT_EXPORT void Exchange_Info_Data_Ext (Domain *);
FLUENT_EXPORT cxboolean local_cell_p (cell_t, Thread *);
#endif
FLUENT_EXPORT void Mark_Remesh_Local_Cavities (Domain *, cxboolean,
                                               cxboolean *);
FLUENT_EXPORT void Remesh_Local_Cavities (Domain *);
FLUENT_EXPORT void Mark_And_Remesh_Local_Cavities (Domain *);
FLUENT_EXPORT void Draw_Mark_Remesh_Local_Cavities (Domain *, unsigned int);
FLUENT_EXPORT void Print_Mark_Remesh_Local_Cavities (Domain *);

FLUENT_EXPORT real Evaluate_Cavity_Marking (cell_t, Thread *);
FLUENT_EXPORT real Evaluate_Cavity_Type (cell_t, Thread *);
FLUENT_EXPORT real Evaluate_Cavity_Seeds (cell_t, Thread *);

# if !RP_HOST
FLUENT_EXPORT Node *Node_Opposite_Longest_Edge (cell_t, Thread *);
FLUENT_EXPORT void Export_Cell_List (Objp *, cell_t, char *);
# endif
#if DEBUG
FLUENT_EXPORT void Print_Cavity_Marks (Domain *, Objp *, char *);
#endif

#endif /* _FLUENT_REMESH_LOCAL_H */
