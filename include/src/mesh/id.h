/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_ID_H
#define _FLUENT_ID_H

#include "dll.h"
/* Defining bit update flags with shifting operations, because of flags' location differences, bit-wise operations will result in distinctive values no matter the operation combinations. */
#define GRID_NODE_UPDATE_BIT (1)
#define GRID_FACE_UPDATE_BIT (1<<1)
#define GRID_CELL_UPDATE_BIT (1<<2)
#define GRID_TOPOLOGY_UPDATE_BIT (1<<3) /* grid topology update*/
#define GRID_PARALLEL_TOPOLOGY_UPDATE_BIT (1<<4) /* parallel grid topology update on a single comupting node, e.g., grid partition / migration can trigger grid topology update (gain or lose cell zones) */
#define GRID_ALL_UPDATE_BITS (GRID_NODE_UPDATE_BIT | GRID_FACE_UPDATE_BIT | GRID_CELL_UPDATE_BIT | GRID_TOPOLOGY_UPDATE_BIT | GRID_PARALLEL_TOPOLOGY_UPDATE_BIT)


typedef enum
{
  GNID_LSF_W = 0,
  GNID_LSF_GGW,
  GNID_QUALITY,
  GNID_METRICS,
  GNID_WALL_DIST,
  GNID_MAX

} Grid_Node_Id_Cache;


FLUENT_EXPORT cxboolean Check_License_Limit(cxboolean);
FLUENT_EXPORT void Update_Grid_Id(int);
FLUENT_EXPORT void Update_Case_Id(void);
FLUENT_EXPORT void Update_Data_Id(void);
FLUENT_EXPORT void Update_Boundary_Type_Id(void);
FLUENT_EXPORT void Update_Cell_Marking_Id(void);
FLUENT_EXPORT void Update_Node_Marking_Id(void);

FLUENT_EXPORT void Save_Grid_Id(void);
FLUENT_EXPORT void Set_Grid_Id(int);
FLUENT_EXPORT void Save_Casefile_Grid_Id(void);
FLUENT_EXPORT void Save_Case_Id(void);
FLUENT_EXPORT void Save_Data_Id(void);
FLUENT_EXPORT void save_case_file_name(const char *);

FLUENT_EXPORT cxboolean Casefile_Grid_Id_Current(void);

FLUENT_EXPORT void Set_Case_Id(int);
FLUENT_EXPORT int Show_Grid_Id(void);
FLUENT_EXPORT int Show_Case_Id(void);
FLUENT_EXPORT int Show_Data_Id(void);
FLUENT_EXPORT int Show_Boundary_Type_Id(void);
FLUENT_EXPORT int Show_Cell_Marking_Id(void);
FLUENT_EXPORT int Show_Node_Marking_Id(void);
FLUENT_EXPORT int Show_Grid_Node_Id(void);
FLUENT_EXPORT int Show_Grid_Face_Id(void);
FLUENT_EXPORT int Show_Grid_Cell_Id(void);
FLUENT_EXPORT int Show_Grid_Topology_Id(void);
FLUENT_EXPORT int Show_Grid_Parallel_Topology_Id(void);

FLUENT_EXPORT void Cache_Grid_Node_Id(int);
FLUENT_EXPORT cxboolean Grid_Node_Id_Same_As_Cached(int);

FLUENT_EXPORT const char *get_saved_case_file_name(void);

FLUENT_EXPORT cxboolean Grid_Modified_P(void);
FLUENT_EXPORT cxboolean Case_Modified_P(void);
FLUENT_EXPORT cxboolean Data_Modified_P(void);

FLUENT_EXPORT void Set_Case_Valid(cxboolean);
FLUENT_EXPORT void Set_Data_Valid(cxboolean);
FLUENT_EXPORT void Set_Grid_Valid(cxboolean);
FLUENT_EXPORT void Set_Machine_Valid(cxboolean);

FLUENT_EXPORT cxboolean Grid_Valid_P(void);
FLUENT_EXPORT cxboolean Case_Valid_P(void);
FLUENT_EXPORT cxboolean Data_Valid_P(void);
FLUENT_EXPORT cxboolean Machine_Valid_P(void);

FLUENT_EXPORT cxindex Label_Cells (Domain *);
FLUENT_EXPORT cxindex Label_Nodes (Domain *, cxboolean);
FLUENT_EXPORT cxindex Label_Faces (Domain *, cxboolean);
FLUENT_EXPORT cxindex Label_Cells_If_Needed (Domain *);
FLUENT_EXPORT cxindex Label_Nodes_If_Needed (Domain *, cxboolean);
FLUENT_EXPORT cxindex Label_Faces_If_Needed (Domain *, cxboolean);
FLUENT_EXPORT cxindex Get_Node_Count (Domain *, cxboolean);
#if RP_NODE
FLUENT_EXPORT void Label_Surface_Mesh(Domain *);
FLUENT_EXPORT void Relabel_Entities (Domain *, cxboolean, cxboolean, cxboolean);
FLUENT_EXPORT void Relabel_Entities_If_Needed (Domain *, cxboolean, cxboolean, cxboolean);
FLUENT_EXPORT cxindex Label_Helper_Thread_Faces (Domain *);
#endif
FLUENT_EXPORT void Set_Retain_Label_Order(const cxboolean);
FLUENT_EXPORT cxindex Get_Thread_Element_Count(Thread *, cxboolean);
FLUENT_EXPORT cxboolean Check_If_Relabel_Needed (Domain *, cxboolean);
FLUENT_EXPORT void Min_Max_Id_Thread_C(Thread *t, cxindex *min, cxindex *max, cxboolean wh, cxboolean reduce_later);
FLUENT_EXPORT void Min_Max_Id_Thread_F(Thread *t, cxindex *min, cxindex *max, cxboolean wh, cxboolean reduce_later);
FLUENT_EXPORT void Min_Max_Node_Id (Domain *domain, cxindex *minid,
                                    cxindex *maxid, cxboolean with_host);
/* determines and returns the min/max (first/last) global IDs for the given
 * thread.  For parallel, all subdomains are considered.
 */
FLUENT_EXPORT void
Thread_Min_Max_Id(Thread *thread, cxindex *first_id, cxindex *last_id,
                  int with_host, cxboolean reduce_later);
#if PARALLEL || DEBUG
FLUENT_EXPORT cxindex Max_Node_Id(Domain *domain, cxboolean wh);
FLUENT_EXPORT cxindex Max_Face_Id(Domain *domain, cxboolean wh);
FLUENT_EXPORT cxindex Max_Face_Id_Without_Helper(Domain *domain, cxboolean wh);
FLUENT_EXPORT cxindex Max_Face_Id_Without_Shell(Domain *domain, cxboolean wh);
FLUENT_EXPORT cxindex Max_Cell_Id(Domain *domain, cxboolean wh);
FLUENT_EXPORT cxindex Max_Cell_Id_Without_Shell(Domain *domain, cxboolean wh, Thread *);
#endif
#if USE_INT64
FLUENT_EXPORT void Offset_ID(cxindex, cxindex, cxindex, int, Domain *);
#endif
#endif /* _FLUENT_ID_H */
