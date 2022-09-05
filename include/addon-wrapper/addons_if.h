/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_ADDONS_IF_H_
#define _FLUENT_ADDONS_IF_H_

enum
{
  READ_ALL = 0,
  TOPOLOGY_ONLY = 1,
  SURFACE_MESH
};

FLUENT_EXPORT int AF_Get_TL_N(void);
FLUENT_EXPORT int AF_Get_Cell_Zone_Masks_For_IO(void);
FLUENT_EXPORT int AF_Get_Face_Zone_Masks_For_IO(void);

FLUENT_EXPORT Thread *AF_Get_Domain_Thread(const Domain *const, const int);
FLUENT_EXPORT Thread *AF_Get_Domain_Cell_Thread(const Domain *const);
FLUENT_EXPORT Thread *AF_Get_Domain_Face_Thread(const Domain *const);
FLUENT_EXPORT Thread *AF_Get_Next_Thread(const Thread *const);
FLUENT_EXPORT int AF_Is_Solve_Mask(const int);
FLUENT_EXPORT int AF_Is_Nosolve_Mask(const int);
FLUENT_EXPORT int AF_Get_Thread_Id(const Thread *const);
FLUENT_EXPORT int AF_Get_Thread_Id_Checked(const Thread *const);

FLUENT_EXPORT cxboolean AF_Is_Grid_Appending(void);
FLUENT_EXPORT cxboolean AF_Is_Old_Thread(const Domain *, const int);
FLUENT_EXPORT int AF_Get_Max_Thread_Id(const Domain *const);
FLUENT_EXPORT cxindex AF_Get_Max_Cell_Id_Before_Appending(void);
FLUENT_EXPORT cxindex AF_Get_Max_Face_Id_Before_Appending(void);
FLUENT_EXPORT cxindex AF_Get_Max_Node_Id_Before_Appending(void);
FLUENT_EXPORT void AF_Add_Old_New_Ids_To_Changed_List(const int, const int);
FLUENT_EXPORT int AF_Get_Updated_Thread_Id(int id);

FLUENT_EXPORT int AF_Get_Thread_Nelements(const Thread *const);
FLUENT_EXPORT int AF_Get_Thread_Nelements_Interior(const Thread *const);
FLUENT_EXPORT int AF_Get_Thread_Nelements_Interior_Rexterior(const Thread *const);
#if 0
FLUENT_EXPORT int AF_Get_Face_Thread_Nelements_Principal(const Thread *const);
#endif /* 0 */
FLUENT_EXPORT Thread_Type AF_Get_Thread_Type(const Thread *const);
FLUENT_EXPORT int AF_Get_Thread_Element_Type(const Thread *const);
FLUENT_EXPORT Thread *AF_Get_Thread_T0(const Thread *const);
FLUENT_EXPORT int AF_Get_Thread_T0_Id(const Thread *const);
FLUENT_EXPORT Thread *AF_Get_Thread_T1(const Thread *const);
FLUENT_EXPORT int AF_Get_Thread_T1_Id(const Thread *const);


FLUENT_EXPORT Thread *AF_Get_Thread_Child(const Thread *const);
FLUENT_EXPORT int AF_Get_Thread_Child_Id(const Thread *const);

#if USE_FEMCORE
FLUENT_EXPORT unsigned int AF_Is_Interpolation_Node_Thread(const Thread *const);
#endif

FLUENT_EXPORT unsigned int AF_Is_Cell_Thread(const Thread *const);
FLUENT_EXPORT int AF_Cell_Thread_Has_Uniform_Cells(const Thread *const);
FLUENT_EXPORT int AF_Cell_Has_Grouped_Cells(const Thread *const tc);
FLUENT_EXPORT int AF_Cell_Use_Grouped_Cells();

FLUENT_EXPORT unsigned int AF_Is_Face_Thread(const Thread *const);
FLUENT_EXPORT int AF_Face_Thread_Has_Uniform_Faces(const Thread *const);
FLUENT_EXPORT int AF_Face_Thread_Has_Cell0_Thread(const Thread *const);
FLUENT_EXPORT int AF_Face_Thread_Has_Cell1_Thread(const Thread *const);
FLUENT_EXPORT int AF_Is_Sliding_Interface_Face_Thread(const Thread *const);
FLUENT_EXPORT void AF_Get_Face_Thread_Shadow_Info(const Thread *const, int *const, int *const, int *const);
FLUENT_EXPORT Thread *AF_Get_Thread_Shadow(const Thread *const);
FLUENT_EXPORT int AF_Get_Thread_Shadow_Id(const Thread *const);

FLUENT_EXPORT void AF_Get_Thread_Element_Ids(const Thread *const, size_t *const, const size_t);

FLUENT_EXPORT cxindex AF_Get_Node_Id(const Node *const);
FLUENT_EXPORT void AF_Allocate_Node_Thread_SV_N_TMP_1(const Domain *const);
FLUENT_EXPORT void AF_Free_Node_Thread_SV_N_TMP_1(const Domain *const);
FLUENT_EXPORT void AF_Set_Node_Mark(const Node *, int);
FLUENT_EXPORT int AF_Get_Node_Mark(const Node *);

FLUENT_EXPORT int AF_Is_Null_Face(const face_t);
FLUENT_EXPORT cxindex AF_Get_Face_Id(const cxindex, const Thread *const);
#if 0
FLUENT_EXPORT void AF_Get_Principal_Face_Ids(const Thread *const, size_t *const, const size_t);
#endif /* 0 */
FLUENT_EXPORT void AF_Get_Face_Ids(const Thread *const, size_t *const, const size_t);
FLUENT_EXPORT cxindex AF_Get_Face_Shadow(const cxindex, const Thread *const);
FLUENT_EXPORT void AF_Get_Face_Shadow_Ids(const Thread *const, void *const, const size_t, const int);
#if 0
FLUENT_EXPORT void AF_Get_Principal_Face_Shadow_Ids(const Thread *const, void *const, const size_t, const int);
#endif /* 0 */
FLUENT_EXPORT int AF_Get_Face_Node_Count(const cxindex, const Thread *const);
FLUENT_EXPORT size_t AF_Get_Face_Node_Counts(const Thread *const, short *const, const size_t);
#if 0
FLUENT_EXPORT size_t AF_Get_Principal_Face_Node_Counts(const Thread *const, short *const, const size_t);
#endif /* 0 */
FLUENT_EXPORT Node *AF_Get_Face_Node(const cxindex, const Thread *const, const int);
FLUENT_EXPORT cxindex AF_Get_Face_Node_Id(const cxindex, const Thread *const, const int);
FLUENT_EXPORT void AF_Get_Face_Node_Ids(const Thread *const, void *const, const size_t, const int);
#if 0
FLUENT_EXPORT void AF_Get_Principal_Face_Node_Ids(const Thread *const, void *const, const size_t, const int);
#endif /* 0 */
FLUENT_EXPORT int AF_Get_Face_Children_Count(const cxindex, const Thread *const);
FLUENT_EXPORT face_t AF_Get_Face_Child(const cxindex, const Thread *const, const int);
FLUENT_EXPORT int AF_Is_Valid_Face_Child(const cxindex, const Thread *const, const int);
FLUENT_EXPORT cxindex AF_Get_Face_Child_Id(const cxindex, const Thread *const, const int);
FLUENT_EXPORT cell_t AF_Get_Face_Cell0(const cxindex, const Thread *const);
FLUENT_EXPORT cell_t AF_Get_Face_Cell1(const cxindex, const Thread *const);
FLUENT_EXPORT cxindex AF_Get_Face_Shadow_Id(const cxindex, const Thread *const);
FLUENT_EXPORT face_t AF_Get_Face_Parent_Face0(const cxindex, const Thread *const);
FLUENT_EXPORT cxindex AF_Get_Face_Parent_Face0_Id_Checked(const cxindex, const Thread *const, const Thread *const);
FLUENT_EXPORT Thread *AF_Get_Face_Parent_Face0_Thread(const Thread *const);
FLUENT_EXPORT face_t AF_Get_Face_Parent_Face1(const cxindex, const Thread *const);
FLUENT_EXPORT cxindex AF_Get_Face_Parent_Face1_Id_Checked(const cxindex, const Thread *const, const Thread *const);
FLUENT_EXPORT Thread *AF_Get_Face_Parent_Face1_Thread(const Thread *const);
FLUENT_EXPORT cxindex AF_Get_Face_Cell0_Id_Checked(const cxindex, const Thread *const);
FLUENT_EXPORT void AF_Get_Face_Cell0_Ids(const Thread *const, void *const, const size_t, const int);
#if 0
FLUENT_EXPORT void AF_Get_Principal_Face_Cell0_Ids(const Thread *const, void *const, const size_t, const int);
#endif /* 0 */
FLUENT_EXPORT cxindex AF_Get_Face_Cell1_Id_Checked(const cxindex, const Thread *const);
FLUENT_EXPORT void AF_Get_Face_Cell1_Ids(const Thread *const, void *const, const size_t, const int);
#if 0
FLUENT_EXPORT void AF_Get_Principal_Face_Cell1_Ids(const Thread *const, void *const, const size_t, const int);
#endif /* 0 */
FLUENT_EXPORT void AF_Set_Face_Cell0_Ids(const size_t *const, const size_t, const size_t);
FLUENT_EXPORT void AF_Set_Face_Cell1_Ids(const size_t *const, const size_t, const size_t);
FLUENT_EXPORT void AF_Set_Face_Node_Counts(const short *const, const size_t, const size_t);
FLUENT_EXPORT void AF_Set_Uniform_Face_Node_Count(const short, const size_t, const size_t);
FLUENT_EXPORT void AF_Set_Face_Node_Ids(const size_t *const, const size_t, const size_t);
FLUENT_EXPORT void AF_Set_Face_Shadow_Ids(const size_t *const, const size_t, const size_t);

FLUENT_EXPORT int AF_Get_Node_Thread_Id(Domain *const);

FLUENT_EXPORT cxindex AF_Get_Cell_Id(const cxindex, const Thread *const);
FLUENT_EXPORT void AF_Get_Cell_Ids(const Thread *const, size_t *const, const size_t);
FLUENT_EXPORT int AF_Get_Cell_Type(const cxindex, const Thread *const);
FLUENT_EXPORT void AF_Get_Cell_Types(const Thread *const, int *const, const size_t);
FLUENT_EXPORT int AF_Get_Cell_Stored_Partition(const cxindex, const Thread *const);
FLUENT_EXPORT void AF_Get_Stored_Cell_Partition_Ids(const Thread *const, int *const, const size_t);
FLUENT_EXPORT void AF_Get_Stored_Laplace_Groups(const Thread *const tc, size_t *const cgId, const size_t len);
FLUENT_EXPORT int AF_Get_Cell_Children_Count(const cxindex, const Thread *const);
FLUENT_EXPORT cxindex AF_Get_Cell_Child_Id(const cxindex, const Thread *const, const int);
FLUENT_EXPORT void AF_Set_Cell_Partitions(const int *const, const size_t, const size_t, const int);
FLUENT_EXPORT void AF_Set_Cell_Groups(const size_t *const group, const size_t len, const size_t dump_offset);
FLUENT_EXPORT void AF_Set_Cell_Types(const short *const, const size_t, const size_t);
FLUENT_EXPORT void AF_Set_Uniform_Cell_Type(const short, const size_t, const size_t);
FLUENT_EXPORT void AF_Set_Cell_Node_Counts(const short *const, const size_t, const size_t);
FLUENT_EXPORT void AF_Set_Uniform_Cell_Node_Count(const short, const size_t, const size_t);
FLUENT_EXPORT void AF_Set_Cell_Node_Ids(const size_t *const, const size_t, const size_t);

FLUENT_EXPORT void AF_Append_New_Kidmem(const int);
FLUENT_EXPORT void AF_Allocate_Interface_Child_Tree_Dump(const cxindex, const size_t);
FLUENT_EXPORT void AF_Set_Interface_Child_Tree_Dump(const size_t *const, const size_t *const, const size_t);
FLUENT_EXPORT void AF_Get_Child_Counts(const Thread *const, short *const, const size_t);
FLUENT_EXPORT void AF_Get_Child_Ids(const Thread *const, cxindex *const, const size_t);

FLUENT_EXPORT void AF_Allocate_Face_Child_Tree_Dump(const cxindex, const size_t);
FLUENT_EXPORT void AF_Set_Face_Child_Tree_Dump(const size_t *const, const short *const, const size_t);

FLUENT_EXPORT void AF_Allocate_Laplace_Smoothing_Dump(const size_t);

FLUENT_EXPORT void AF_Allocate_Cell_Child_Tree_Dump(const cxindex, const size_t);
FLUENT_EXPORT void AF_Set_Cell_Child_Tree_Dump(const size_t *const, const short *const, const size_t);

FLUENT_EXPORT void AF_Set_Total_Cell_Count(const size_t);
FLUENT_EXPORT void AF_Set_Total_Cell_Count_For_CellNode(const size_t);
FLUENT_EXPORT void AF_Set_Total_Face_Count(const size_t);
FLUENT_EXPORT void AF_Set_Total_Node_Count(const size_t);

FLUENT_EXPORT void AF_Set_Cat(const int, const cxindex, const size_t, const size_t, const int);
FLUENT_EXPORT void AF_Set_Fat(const int, const cxindex, const size_t, const size_t);
FLUENT_EXPORT void AF_Set_Node_And_Thread(const int, const cxindex, const size_t, const size_t);

FLUENT_EXPORT void AF_Assign_Kidmem_Id(struct kidmem *const, const int);
FLUENT_EXPORT void AF_Allocate_NC_Metric_Storage(Thread *const);
FLUENT_EXPORT void AF_Set_NC_Metric_Storage(const Thread *const);
FLUENT_EXPORT void AF_Set_NC_Metrics(void);
FLUENT_EXPORT void AF_Get_Parent_Face0_Ids(const Thread *const, cxindex *const, const size_t);
FLUENT_EXPORT void AF_Get_Parent_Face1_Ids(const Thread *const, cxindex *const, const size_t);

FLUENT_EXPORT int AF_Should_Write_Particle_Data(const short);
FLUENT_EXPORT int AF_Cell_Thread_Has_Persistent_Data(Thread *const, const int);
FLUENT_EXPORT int AF_Face_Thread_Has_Persistent_Data(Thread *const, const int);
FLUENT_EXPORT int AF_Get_SV_MIN(void);
FLUENT_EXPORT int AF_Get_SV_MAX(void);
FLUENT_EXPORT int AF_Get_SV_Y(void);
FLUENT_EXPORT void AF_Get_All_SV_Enum_Names(char *const, const int);
FLUENT_EXPORT char *AF_Get_Svar_Enumeration_Name(const int);
FLUENT_EXPORT int AF_Get_Data_Section_Id(const int);
FLUENT_EXPORT int AF_Get_Residual_Section_Id(const int);
FLUENT_EXPORT int AF_Get_Available_Svars_For_Write(const Domain *const, int *const, const int);
FLUENT_EXPORT void AF_Set_Custom_Svars_For_Write(const int, int *const, const cxboolean, const cxboolean);
FLUENT_EXPORT void AF_Unset_Custom_Svars_For_Write(const cxboolean);
FLUENT_EXPORT int AF_Check_Thread_Svar_Writability(const Thread *const, const int);
FLUENT_EXPORT int AF_Is_Storage_Allocated_For_Thread(const Thread *const, const int);
FLUENT_EXPORT void AF_Set_Storage_Initialized_For_Thread(Thread *const, const int, const cxboolean);
FLUENT_EXPORT size_t AF_Get_Storage_Num_Component(Thread *const, const int);
FLUENT_EXPORT size_t AF_Get_Storage_Num_Segragation(Thread *const, const int);
FLUENT_EXPORT real *AF_Get_Storage_Pointer(const Thread *const, const int, const size_t);
FLUENT_EXPORT int AF_Get_Equation_Index(Domain *const, const int);
FLUENT_EXPORT char *AF_Get_Equation_Label(Domain *const, const int);
FLUENT_EXPORT int AF_Get_Residual_Store(Domain *const, const int);
FLUENT_EXPORT int AF_Get_Storage_Size(const Domain *const, const int);
FLUENT_EXPORT void AF_Get_SV_AREA_Info(Thread *const, real **, size_t *, size_t *);
FLUENT_EXPORT void AF_Get_SV_CENTROID_Info(Thread *const, real **, size_t *, size_t *);
FLUENT_EXPORT void AF_Set_Node_Coordinates(real *const, const size_t, const size_t);
FLUENT_EXPORT void AF_Set_Node_Coordinates_DP(double *const, const size_t, const size_t);
FLUENT_EXPORT void AF_Alloc_And_Set_All_Node_Marks(Domain *const, const int);
FLUENT_EXPORT void AF_Free_All_Node_Marks(Domain *const);
FLUENT_EXPORT size_t AF_Get_Node_Count(Domain *const);
FLUENT_EXPORT void AF_Get_Node_Ids(Domain *const, size_t *const, const size_t);
#if USE_FEMCORE
FLUENT_EXPORT void AF_Get_Interpolation_Node_Ids(const Thread *const, size_t *const, const size_t);
#endif
FLUENT_EXPORT void AF_Get_Node_Coordinates(real *const, const size_t);
FLUENT_EXPORT void AF_Get_Node_Coordinates_DP(double *const, const size_t);
FLUENT_EXPORT int AF_Get_Domain_Id(Domain *const);
FLUENT_EXPORT int AF_Get_Num_Sub_Domains(Domain *const);
FLUENT_EXPORT Domain *AF_Get_Sub_Domain(Domain *const, const int);
FLUENT_EXPORT int AF_Get_Max_Domain_Id(Domain *const);
FLUENT_EXPORT void AF_Set_Residuals(Domain *const, const int, const int, const int, const int, const int, int *const, real *const);
FLUENT_EXPORT void AF_Get_Residual_Data(Domain *const, const int, const int, const int, real *const, size_t);
FLUENT_EXPORT Input_Profile *AF_Create_New_Profile(char *const, const short, const size_t, const size_t, const size_t, const size_t, const char **names, const double *values, const size_t, size_t *const, const size_t, size_t *const, const size_t);
FLUENT_EXPORT real *AF_Create_New_Profile_Field(Input_Profile *const, char *const, int *);
FLUENT_EXPORT real *AF_Get_Profile_Field_Data_Pointer(Profile_Field *const, const size_t);
FLUENT_EXPORT char const *AF_Get_Profile_Name(Input_Profile *const);
FLUENT_EXPORT char const *AF_Get_Profile_Field_Name(Profile_Field *const);
FLUENT_EXPORT short AF_Get_Profile_Type(Input_Profile *const);
FLUENT_EXPORT void AF_Get_Profile_Num_Points(Input_Profile *const, size_t *const);
FLUENT_EXPORT int AF_Get_Profile_Num_Bins(Input_Profile *const);
FLUENT_EXPORT int AF_Get_Profile_Num_Parameters(Input_Profile *const);
FLUENT_EXPORT cxindex AF_Get_Profile_Num_Faces(Input_Profile *const);
FLUENT_EXPORT void AF_Get_Profile_Num_Nodes(Input_Profile *const, size_t *const);
FLUENT_EXPORT void AF_Get_Profile_Num_NodeIds(Input_Profile *const, size_t *const);
FLUENT_EXPORT void AF_Get_Profile_Parameters(Input_Profile *const, int, char *, double *);
FLUENT_EXPORT Profile_Field *AF_Get_Profile_Field(Input_Profile *const, int *const);
FLUENT_EXPORT Input_Profile *AF_Get_Next_Profile(Input_Profile *const);
FLUENT_EXPORT Profile_Field *AF_Get_Next_Profile_Field(Profile_Field *const);

FLUENT_EXPORT cxboolean AF_Write_Single_Precision_Node_Coordinates(void);

FLUENT_EXPORT cxboolean AF_Should_Write_Single_Precision_Result_Data(void);

/* surface */
FLUENT_EXPORT void AF_Set_IOSurface(const int);
FLUENT_EXPORT cxboolean AF_IOSurface_Has_Mesh(void);
FLUENT_EXPORT void AF_Reset_IOSurface(void);
FLUENT_EXPORT size_t AF_Get_Surface_Face_Count(void);
FLUENT_EXPORT size_t AF_Get_Surface_Node_Count(void);
FLUENT_EXPORT size_t AF_Get_Surface_Face_Zone_Min_Id(void);
FLUENT_EXPORT size_t AF_Get_Surface_Node_Zone_Min_Id(void);
FLUENT_EXPORT size_t AF_Get_Surface_Face_Zone_Max_Id(void);
FLUENT_EXPORT size_t AF_Get_Surface_Node_Zone_Max_Id(void);
FLUENT_EXPORT size_t AF_Get_Surface_Face_Zone_Total_Size(void);
FLUENT_EXPORT size_t AF_Get_Surface_Node_Zone_Total_Size(void);
FLUENT_EXPORT size_t AF_Get_Surface_Face_Zone_Interior_Size(void);
FLUENT_EXPORT size_t AF_Get_Surface_Node_Zone_Interior_Size(void);
FLUENT_EXPORT void AF_Get_Surface_Face_Zone_Global_Ids(const size_t, size_t *const);
FLUENT_EXPORT void AF_Get_Surface_Node_Zone_Global_Ids(const size_t, size_t *const);
FLUENT_EXPORT void AF_Get_Surface_Node_Coordinates_DP(const size_t, double *const);
FLUENT_EXPORT size_t AF_Get_Surface_Face_Node_Counts(const size_t, short *const);
FLUENT_EXPORT void AF_Get_Surface_Face_Node_Ids(const size_t, void *const, const int);

FLUENT_EXPORT const char *AF_Face_Type_Name(int type);
FLUENT_EXPORT const char *AF_Cell_Type_Name(int type);
FLUENT_EXPORT const char *AF_Zone_Boundary_Type_Name(int type);

FLUENT_EXPORT const char *AF_Get_Zone_Name(const Thread *t);
FLUENT_EXPORT int AF_Is_Parent_Thread(const Thread *t);
FLUENT_EXPORT void Fill_Addons_Interface_Export_Functions(void);

FLUENT_EXPORT cxboolean AF_Check_If_DPM_Domain_Is_On(void);
FLUENT_EXPORT int AF_Get_Thread_Periodic_Type(const Thread *const );
FLUENT_EXPORT int AF_Get_Mesh_Option(void);

#endif /* _FLUENT_ADDONS_IF_H_ */
