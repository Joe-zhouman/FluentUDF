/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _DYNAMESH_CONTACT_H
#define _DYNAMESH_CONTACT_H

/**
 * @file
 *   dynamesh_contact.h
 * @brief
 *   Header file for Contact Detection functions
 */

#include "global.h"
#include "mem.h"
#include "flow.h"
#include "prime/tgrid/tg_obbtree.h"
#include "prime/tgrid/tg_lib.h"
#include "thread_tools.h"

#define CELL_CONTACT_FLAGS (NARROW_GAP_BLOCKED_CELL_FL | NARROW_GAP_BLOCKED_CELL_FL_OLD)

/* * * * * * * * * * * * Global Function Definitions * * * * * * * * * * * * */

FLUENT_EXPORT void Init_Contact (Domain *);
FLUENT_EXPORT void Init_Generic_Contact (Domain *, int, int *, real *);
FLUENT_EXPORT int Max_Number_Of_Contact_Threads (void);
FLUENT_EXPORT void Free_Contact (Domain *);
FLUENT_EXPORT void Detect_Contact (Domain *, real, real, cxboolean);
FLUENT_EXPORT void Mark_Contact_Nodes (Domain *, cxboolean);
FLUENT_EXPORT void Clear_Node_Contact_Marks (Domain *, cxboolean);
FLUENT_EXPORT void Tag_Cells_For_Contact (Domain *);
FLUENT_EXPORT void Separate_Contact_Threads (Domain *);
FLUENT_EXPORT void Construct_Contact_Tree (TG_OBB_Tree *);
FLUENT_EXPORT void Download_Contact_Parameters (void);
FLUENT_EXPORT void Reset_Contact_Thread_Map (void);
FLUENT_EXPORT void Reset_Contact_Interface_Thread_Map (void);
FLUENT_EXPORT void Unlink_Contact_Interface_Threads (Domain *);
FLUENT_EXPORT void Create_Contact_Interface_Threads (Thread *);
FLUENT_EXPORT void Separate_Contact_Interface_Threads (Domain *);
FLUENT_EXPORT void Mark_Contact_Cells (Domain *, cxboolean);
FLUENT_EXPORT void Mark_Contact_Faces (Domain *);
FLUENT_EXPORT void Orient_Contact_Faces(Domain *);
FLUENT_EXPORT void Clear_Contact (Domain *, cxboolean);
FLUENT_EXPORT void Fill_Contact_Lists (Domain *);
FLUENT_EXPORT void Free_Contact_Lists (void);
FLUENT_EXPORT void Update_Contact_Face_Marks_And_Lists(Domain *);
FLUENT_EXPORT void Pre_Merge_Contact_Threads (Domain *);
FLUENT_EXPORT void Merge_Contact_Interface_Threads (Domain *);
FLUENT_EXPORT void Initialize_Contact_Detection_Primitives (void);
FLUENT_EXPORT void Transfer_Interface_Node_Displacement (Domain *);
FLUENT_EXPORT void Inquire_Contact_Interface_Thread_Map (NT_Map **, int *);
FLUENT_EXPORT void Inquire_Contact_Thread_Map (NT_Map **, int *);
FLUENT_EXPORT int Create_Contact_Thread (int, Thread *);
FLUENT_EXPORT int Test_Contact_Interaction (int, int, cxboolean);
#if PARALLEL
FLUENT_EXPORT void Register_Contact_Detection_IO_Manager (void);
#endif
FLUENT_EXPORT void
Move_And_Project(Dynamic_Thread *dt, real time, real dtime,
                 void *get_vel,
                 Objp *moving_zones, Objp *project_to_zones,
                 cxboolean move_p, cxboolean project_p);

FLUENT_EXPORT void Draw_Tree (int, int);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

FLUENT_EXPORT Objp *mesh_contact_cells0;
FLUENT_EXPORT Objp *mesh_contact_cells1;
FLUENT_EXPORT Objp *mesh_contact_faces0;
FLUENT_EXPORT Objp *mesh_contact_faces1;

#endif /* _DYNAMESH_CONTACT_H */

/*****************************************************************************/
