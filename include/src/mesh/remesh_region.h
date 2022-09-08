/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_REMESH_REGION_H
#define _FLUENT_REMESH_REGION_H

extern FLUENT_EXPORT Svar sv_node_normal;

#define NODE_NORMAL(v)(NODE_MANAGED_TMP_ND(v,sv_node_normal))
/* needed to access individual components */
#define NODE_NORMAL_X(v) NODE_NORMAL(v)[0]
#define NODE_NORMAL_Y(v) NODE_NORMAL(v)[1]
#define NODE_NORMAL_Z(v) NODE_NORMAL(v)[2]

FLUENT_EXPORT cxboolean Mark_Remesh_Face_Regions (Domain *, cxboolean *);
FLUENT_EXPORT void Remesh_Face_Regions (Domain *);
# if RP_3D
FLUENT_EXPORT cxboolean Mark_Remesh_Regions (Domain *, cxboolean *);
FLUENT_EXPORT void Remesh_Regions (Domain *);
FLUENT_EXPORT void Mark_Remesh_Gocart_Thread (Domain *, cxboolean *);
FLUENT_EXPORT cxboolean Remesh_Gocart_Thread (Domain *);
# endif
FLUENT_EXPORT cxboolean Mark_Remesh_Threads_On_Cell_Quality (Domain *, real,
                                                             cxboolean);
# if RP_3D
FLUENT_EXPORT cxboolean Mark_Remesh_Threads_On_Prism_Quality_At_Loop (Domain *,
                                                                      real, cxboolean);
# endif
FLUENT_EXPORT cxboolean Remesh_Marked_Threads (Domain *, cxboolean, int, int,
                                               cxboolean, cxboolean);

FLUENT_EXPORT void Create_Face_Search_Tree (Domain *, Thread *);
FLUENT_EXPORT void Create_Face_Search_Trees (Domain *, cxboolean);
FLUENT_EXPORT void Free_Face_Search_Tree (Domain *, Thread *);
FLUENT_EXPORT void Free_Face_Search_Trees (Domain *);

FLUENT_EXPORT int Dynamic_Thread_Construct_Loops (Domain *, Dynamic_Thread *);
FLUENT_EXPORT void Dynamic_Thread_Free_Loops (Dynamic_Thread *);
# if RP_3D
FLUENT_EXPORT void Fill_Loop_Node_Normal (Node *);
# endif

#endif /* _FLUENT_REMESH_REGION_H */

