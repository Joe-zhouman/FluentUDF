/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef __GRID_PAR_EXT_HEADER__
#define __GRID_PAR_EXT_HEADER__

extern FLUENT_EXPORT void exchange_svar_for_exterior_cells(Domain *);
extern FLUENT_EXPORT void Exchange_Svar_For_Regular_Exterior_Cells(Domain *);
extern FLUENT_EXPORT void Exchange_Real_Svar_For_Exterior_Cells(Domain *);
extern FLUENT_EXPORT void Exchange_Exterior_Extensive_Values(Domain *);
extern FLUENT_EXPORT  int Resolve_Node_Lists_Ext(Domain *);
extern FLUENT_EXPORT  int Add_Exterior_Cells_Ext(Domain *);
extern FLUENT_EXPORT void Disable_Extended_Neighborhood(Domain *);
extern FLUENT_EXPORT void Enable_Extended_Neighborhood(Domain *);
extern FLUENT_EXPORT void Disable_Neighborhood_Ext(Domain *, cxboolean,
                                                   cxboolean, cxboolean);
extern FLUENT_EXPORT void Enable_Neighborhood_Ext(Domain *, cxboolean,
                                                  cxboolean, cxboolean);
extern FLUENT_EXPORT void Refuse_Zero_Id_Cells(Domain *);
extern FLUENT_EXPORT int Refuse_Cells_With_Zero_Face_Connections(Domain *);
extern FLUENT_EXPORT void Refuse_Extended_Exterior_Cells(Domain *);
extern FLUENT_EXPORT void Resolve_Exterior_Parent_Face_Child (Domain *);
extern FLUENT_EXPORT void Garbage_Collect_Ext (Domain *, cxboolean, cxboolean);
extern FLUENT_EXPORT cxboolean Allow_Extended_Neighborhood(Domain *);
# if RP_EDGE
extern FLUENT_EXPORT int Add_Domain_Edges_Ext (Domain *);
#endif
extern FLUENT_EXPORT void Create_Neighbor_Corner_V_List_Coll(Domain *);
extern FLUENT_EXPORT void Create_Neighbor_Corner_V_List(Domain *domain);
extern FLUENT_EXPORT int sync_corner_nodes(Objp **corner_list);
extern FLUENT_EXPORT void Set_New_Corner_Node_Coord_And_Flag(Domain *domain);
extern FLUENT_EXPORT void Set_New_Iface_Node_Coord_And_Flag(Domain *domain);
# if RP_3D
extern FLUENT_EXPORT void Fill_Face_Edge (face_t, Thread *, Domain *);
# endif
extern FLUENT_EXPORT cxboolean Create_Missed_Corner_Nodes (Domain *domain);
extern FLUENT_EXPORT cxboolean Create_Missed_Iface_Nodes (Domain *domain);
extern FLUENT_EXPORT void store_pf0_pf1_ids(Domain *domain, Objp **tlist0, Objp **tlist1);
extern FLUENT_EXPORT void fill_pf0_pf1(Domain *domain, Objp *tlist0, Objp *tlist1);

extern FLUENT_EXPORT cell_t *Fill_Cells_In_Extended_Exterior(Domain *domain, int ncells, cxindex *cids, int *tids, int *cparts);
extern FLUENT_EXPORT void Move_Eext_Cells_To_Rext(Domain *domain, int *count_buf);

#endif /* __GRID_PAR_EXT_HEADER__ */
