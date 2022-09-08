/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SC_H
#define _FLUENT_SC_H

#include "dynamesh_tools.h"
#include "refcountedmem.h"
#define DEBUG_SC 0

typedef struct meshfilter_struct
{
  int id;
  char region_name[512];
  char region_disp_name[512];
  int step_offset;
  int iter_offset;
  int thread_id;

  struct meshfilter_struct *next;
} Mesh_Filter;
typedef struct meshfilter_struct Region_Filter;

typedef struct resultfilter_struct
{
  int id;
  char region_name[512];
  char region_disp_name[512];
  char name[512];
  char disp_name[512];
  int hasnodedata;
  int resultid;
  int thread_id;

  struct resultfilter_struct *next;
} Result_Filter;

typedef enum
{
  sc_force,
  sc_heatflow,
  sc_temperature,
  sc_near_wall_temperature,
  sc_htc,
  sc_htc2,
  sc_force_x,
  sc_force_y,
  sc_force_z,
  sc_node_ids_coords,
  sc_heatrate
} scTransData;
/* SC's element types. Only few are used by Fluent */
typedef enum
{
  kPoint0,
  /*
     kLine2
     topology: i, j

     i*-----------*j
     */
  kLine2,
  /*
     kLine3
     topology: i, j, k

     i*-----*k-----*j
     */
  kLine3,
  /*
     kBeam3
     topology: i, j, k ( k being orientation node )

   *k

   i*-----------*j

  */
  kBeam3,
  /*
     kBeam4
     topology: i, j, k, l ( l being orientation node )
   *l

   i*-----k-----*j


  */
  kBeam4,
  kTri3,
  kTri6,
  kQuad4,
  kQuad8,
  kTet4,
  kTet10,
  kHex8,
  kHex20,
  kWedge6,
  kWedge15,
  kPyramid5,
  kPyramid13,
  /*
     kGroupTopology
     topology: N - number of groups, { number of nodes in each group }, groups  : special interface access
     */
  kGroupTopology,
  kPolygon, /* special interface access trhough IElementUse*/
  kPolyhedron, /* special interface access through IElementUse */
  kNumElementTypes,
  kMixedNoPolyhedra,  /* TODO: go wit this for now such that we can deal with the case where it is */
  kMixedNoPolygon     /* expensive for the implementation to generate pure type data */
} eElementType;

#define NODE_MARK_SC(v) (NODE_TMP_2 (v).asInt)
#define F_SC_MEAN_THERMAL_DATA_HTC(f,t)  F_STORAGE(f,t,SV_F_SC_MEAN_HTC, real *)
#define F_SC_MEAN_THERMAL_DATA_TREF(f,t) F_STORAGE(f,t,SV_F_SC_MEAN_TREF, real *)
#define F_SC_THERMAL_DATA(f,t) F_STORAGE(f,t,SV_F_SC_THERM,real *)
#define F_SC_THERMAL_NWT_DATA(f,t) F_STORAGE(f,t,SV_F_SC_NWT,real *)
#define F_SC_THERMAL_TRAD_DATA(f,t) F_STORAGE(f,t,SV_F_SC_TRAD,real *)
#if FIXED_PROFILE_NAME_LENGTH
#define F_SC_THERM_DATA(f,t,prof) ((prof).field_name[0] == '\0'  ? (SV_ALLOCATED_P(t,SV_F_SC_THERM) ? F_SC_THERMAL_DATA(f,t) : 0.) : ((prof).field_name[1] == 'i' ? (SV_ALLOCATED_P(t,SV_F_SC_NWT) ? F_SC_THERMAL_NWT_DATA(f,t) : 0.) : (SV_ALLOCATED_P(t,SV_F_SC_TRAD) ? F_SC_THERMAL_TRAD_DATA(f,t) : 0.)))
#define THERMALLY_SYSTEM_COUPLED_WALL_P(t,prof) (THREAD_TYPE((t)) == THREAD_F_WALL && THREAD_VAR((t)).wall.sys_coupling && ((prof).profile_name[3] == 'C'))/*sysCoupled*/
#else
#define F_SC_THERM_DATA(f,t,prof) (NULLP((prof).field_name)  ? (SV_ALLOCATED_P(t,SV_F_SC_THERM) ? F_SC_THERMAL_DATA(f,t) : 0.) : ((strlen((prof).field_name) > 1) && (prof).field_name[1] == 'i' ? (SV_ALLOCATED_P(t,SV_F_SC_NWT) ? F_SC_THERMAL_NWT_DATA(f,t) : 0.) : (SV_ALLOCATED_P(t,SV_F_SC_TRAD) ? F_SC_THERMAL_TRAD_DATA(f,t) : 0.)))
#define THERMALLY_SYSTEM_COUPLED_WALL_P(t,prof) (THREAD_TYPE((t)) == THREAD_F_WALL && THREAD_VAR((t)).wall.sys_coupling && (NNULLP((prof).profile_name) && strlen((prof).profile_name) > 3 && (prof).profile_name[3] == 'C'))/*sysCoupled*/
#endif
#define INIT_NODE_MARK_SC(f,thread,nodeindex) \
{\
   begin_f_loop (f,thread)\
     f_node_loop (f,thread,nodeindex) NODE_MARK_SC(F_NODE(f,thread,nodeindex)) = -1;\
     end_f_loop (f,thread)\
}

FLUENT_EXPORT int Get_SC_Status(void);
FLUENT_EXPORT void Set_SC_Status_For_Nodes(cxboolean);
FLUENT_EXPORT cxboolean Get_SC_Status_For_Nodes(void);
FLUENT_EXPORT void SC_Set_Coupling_Method(int);
FLUENT_EXPORT cxboolean SC_Explicit_Coupling_P(void);
FLUENT_EXPORT int SC_Get_Step_Iteration(void);
FLUENT_EXPORT void Free_SC_Vars(void);
FLUENT_EXPORT void Set_SC_Verbosity(void);
FLUENT_EXPORT int Get_SC_Verbosity(void);
FLUENT_EXPORT char *Get_SC_Thermal_Data_Type(void);
FLUENT_EXPORT void Set_SC_Thermal_Data_Type(const char *name);
FLUENT_EXPORT cxindex Get_MaxElementCount(Domain *, int );
FLUENT_EXPORT cxboolean Unsupported_Coupling_Surface_P(int);
#if !PARALLEL
FLUENT_EXPORT void SC_Delete_Zone_Data(void);
#endif

/*----------- MeshData Methods -------------------*/
FLUENT_EXPORT void SC_GetNodeCount(cxindex id, long *count);
FLUENT_EXPORT void SC_GetNodes(cxindex id, cxindex offset, cxindex maxlength, int buffer_size, long **nodeids, int *nelements_valid1, double **coords, int *nelements_valid2);
FLUENT_EXPORT void SC_GetElementTypes(cxindex id, cxindex offset, cxindex maxlength, cxindex bufferSize, int **types, int *nelements_valid);
FLUENT_EXPORT void SC_GetElementIds(cxindex id, int type, cxindex offset, cxindex maxlength, int buffer_size, long **el_id, int *nelements_valid);
FLUENT_EXPORT void SC_GetElementNodeCounts(cxindex id, int type, cxindex offset, cxindex maxlength, int bufferSize, int **ncount, int *nelements_valid);
FLUENT_EXPORT int SC_GetElementNodeIds(cxindex id, int type, cxindex offset, cxindex maxlength, int buffer_size, long **nids, int *nelements_valid);
FLUENT_EXPORT void SC_GetElementCount(Thread *t, long *count, char *);
FLUENT_EXPORT int SC_Get_Max_Nodes(Thread *);
FLUENT_EXPORT void SC_GetElements(cxindex id, int type, cxindex offset, cxindex maxlength, int bufferSize, long **el_id, int **etype, int **ncount, long **nids, int *nelements_valid1, int *nelements_valid2, char *name, long **c0_ids, long **c1_ids);
FLUENT_EXPORT void Update_Before_SC_Data_Transfer(void);

/*--------- MeshFilter Methods --------------------*/
FLUENT_EXPORT int Create_New_Filter_And_Return_Id(void);
FLUENT_EXPORT void Delete_Mesh_Filter(int);
FLUENT_EXPORT int Set_Region_Name_For_Given_Filerid(int id, const char *name);
FLUENT_EXPORT int Set_Region_Disp_Name_For_Given_Filerid(int id, const char *name);
FLUENT_EXPORT int Set_Region_Id_For_Given_Filterid(int id, int regionid, char *name);

/*--------- MeshInfo Methods ----------------------*/
FLUENT_EXPORT int Apply_Filter_By_Id(int id);
FLUENT_EXPORT void Clear_Current_Filter(void);
FLUENT_EXPORT int Get_Current_Filter_Id(void);
FLUENT_EXPORT char *Get_Current_Filter_Region_Name(void);
FLUENT_EXPORT void Get_Regions_For_Current_Filter(void);
FLUENT_EXPORT void Get_Topol_Dimension_For_Current_Filter(int **dim);

/*--------- ResultData Methods -------------------*/
FLUENT_EXPORT void SC_GetNodeDataCount(int id, long *count);
FLUENT_EXPORT void SC_FillNodeForces(Thread *);
FLUENT_EXPORT void SC_GetNodeData(cxindex resultid, cxindex offset, cxindex maxlength, long **buffer1, int *nelements_valid1, double **buffer2, int *nelements_valid2, int buffer_size, scTransData var);
FLUENT_EXPORT cxboolean Has_Any_SC_Boundary(Domain *);
#if PARALLEL
FLUENT_EXPORT void SC_GetFaceData(cxindex resultid, cxindex offset, cxindex maxlength, long **buffer1, double **buffer2, scTransData var);
FLUENT_EXPORT void SC_Apply_Face_Data(cxindex thread_id, const char *var_name, double *buffer, int offset, int recv_count);
#endif
FLUENT_EXPORT void SC_FillNodeTempData(scTransData var, Thread *);
FLUENT_EXPORT void SC_FillNodeHeatFlowData(scTransData var, Thread *);
FLUENT_EXPORT void SC_FillNodeHTCData(Thread *);
FLUENT_EXPORT void SC_FillNodeHTCDataMethod2(Thread *, cxindex id, cxindex offset, cxindex maxlength, double **data, int buffer_size, scTransData var, int *nelements_valid);
FLUENT_EXPORT void SC_FillNodeNWTData(Thread *);
FLUENT_EXPORT void SC_GetSolverResidualData(Domain *, int, int, double **, const char *);
FLUENT_EXPORT void Apply_SC_Data_To_Thread(cxindex, char *);
FLUENT_EXPORT void Process_SC_Data(cxindex thread_id, const char *var_name, double *buffer, int offset, int recv_count, int time_update);

/*---------- ResultFilter Methods -----------------*/
FLUENT_EXPORT int Create_New_Result_Filter_And_Return_Id(void);
FLUENT_EXPORT int Set_Region_Name_For_Given_Result_Filerid(int id, const char *name, int thread_id);
FLUENT_EXPORT int Set_Region_Display_Name_For_Given_Result_Filerid(int id, const char *name);
FLUENT_EXPORT int Set_Name_For_Given_Result_Filerid(int id, const char *name);
FLUENT_EXPORT int Set_Display_Name_For_Given_Result_Filerid(int id, const char *name);
FLUENT_EXPORT int Set_Has_Node_Data_For_Given_Result_Filerid(int id, int req);
FLUENT_EXPORT Result_Filter *find_rfilter_by_resultid(int id);

/*---------- ResultInfo Methods -------------------*/
FLUENT_EXPORT int Apply_ResultFilter_By_Id(int id);
FLUENT_EXPORT char *Get_Current_Result_Filter_Region_Name(void);
FLUENT_EXPORT void Set_ResultId_For_Current_Filter(int **);

/*---------------------- RegionFilter Public Methods ---------------------------------*/
FLUENT_EXPORT int Create_New_Region_Filter_And_Return_Id(void);
FLUENT_EXPORT void Delete_Region_Filter(int id);
FLUENT_EXPORT int Set_Region_Name_For_Given_Region_Filterid(int id, const char *name);
FLUENT_EXPORT int Set_Region_Disp_Name_For_Given_Region_Filterid(int id, const char *name);

/*--------------------- RegionInfo Public Methods --------------------------------------*/
FLUENT_EXPORT char *Get_Current_Region_Filter_Region_Name(void);
FLUENT_EXPORT int Apply_Region_Filter_By_Id(int id);
FLUENT_EXPORT void Clear_Current_RegionFilter(void);
FLUENT_EXPORT int Get_Current_RegionFilter_Id(void);


FLUENT_EXPORT int Set_Region_Id_For_Given_RFilterid(int id, int regionid, const char *regionName);
FLUENT_EXPORT int Get_Current_Result_Filter_Thread_Id(void);
FLUENT_EXPORT int Delete_ResultFilter_By_Id(int);
FLUENT_EXPORT void Interpolate_forces_from_fluid_to_solid_zone(Domain *, Thread *, Thread *, char *);
FLUENT_EXPORT real Compute_mphase_HTC(Thread *, face_t, cxboolean, real, real);
#if RP_NODE
FLUENT_EXPORT void SC_Accumulate_Statistics(Domain *);
FLUENT_EXPORT void SC_Reset_Thermal_Data_Accumulation(Domain *);
FLUENT_EXPORT void SC_Update_Thermal_Data_Accumulation(Domain *);
FLUENT_EXPORT void SC_Delete_Thermal_Data_Accumulation(Domain *);
FLUENT_EXPORT void SC_Delete_Face_Zone_Map(void);
FLUENT_EXPORT real SC_Get_Face_HTC(face_t f, Thread *thread, cxboolean tref_htc, real Tref, real sc_epsilon);
FLUENT_EXPORT real SC_Get_Face_NWT(face_t f, Thread *thread, cxboolean tref_htc, real Tref);
FLUENT_EXPORT void Compute_Face_Forces(Thread *thread, double *);
FLUENT_EXPORT void Compute_Face_Forces_On_Solid_Sliding_Boundary_Thread(Thread *t, double *);
FLUENT_EXPORT void SC_Store_Or_Patch_Initial_Node_Coord(Thread *thread, cxboolean time_update);
#endif
#endif /* _FLUENT_SC_H */
