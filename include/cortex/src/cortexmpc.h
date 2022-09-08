/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#include "cxconfig.h"
#ifndef _CORTEXMPC_H_
#define _CORTEXMPC_H_
#if MPC_PLATFORM

#include "dll.h"
#include "ansrpc.h"
#include "cxbool.h"

enum EXIT_TYPE
{
  NOT_EXITED,
  REMOTE_FATAL_ERROR,
  REMOTE_SHUT_DOWN,
  FATAL_ERROR,
  SHUT_DOWN
};

extern enum EXIT_TYPE exit_status;

enum TOPOL_DIM
{
  kPoint,
  kLine,
  kSurface,
  kVolume
};

typedef struct current_regions_struct
{
  int size;
  RpcInt64 *regionids;
  RpcInt32 *topol_dim;
} Regions;

typedef struct current_results_struct
{
  int size;
  int *resultids;
  int *componentcounts;
  int *hasnodedata;
  int *thread_ids;
} Results;

typedef struct monitor_data
{
  char *Name;
  double *Values;
} MonitorData;

FLUENT_EXPORT int GetStepIndex(void);
FLUENT_EXPORT double GetStartTime(void);
FLUENT_EXPORT double GetEndTime(void);
FLUENT_EXPORT CXBoolean Is_Volumetric_Coupling_Active(void);
FLUENT_EXPORT void CX_RPC_Connect(const char *hostname, int portnum, const char *solvername, int timeout);
FLUENT_EXPORT void CX_RPC_Disconnect(void);
FLUENT_EXPORT void UnsetLastRequest(void);
FLUENT_EXPORT void GetAllSyncPoints(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void AssignToken(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void ContinueFromSyncPoint(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void CX_PauseAtSyncPoint(const char *sync_name);
FLUENT_EXPORT void ServeUntilCondition(int (*cond)());
FLUENT_EXPORT void CX_YieldToken(void);
FLUENT_EXPORT void MPC_Connection(const char *mpc_host, int mpc_port, const char *solvername);
FLUENT_EXPORT int Get_MPC_On(void);
FLUENT_EXPORT void GetGlobalStatus(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void Set_MPC_On(int status);
FLUENT_EXPORT int Get_User_Interrupt(void);
FLUENT_EXPORT void Shutdown(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void FatalError(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void GetBuildInfo(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void GetExecutionStartTime(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void GetProcessName(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT int AssignToken_Called(void);
FLUENT_EXPORT int ContinueFromSyncPoint_Called(void);
FLUENT_EXPORT void GetRootLevelName(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void GetParentLevelName(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void GetChildLevelNames(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void GetChartableDataNamesByLevel(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void GetLevelDataNamesByLevel(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void GetLevelEndIndex(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void GetLevelStartIndex(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void SetChartInfo(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void GetChartableDataCount(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void GetChartableDataRaw(char *ChartableDataName, int start, int size);
FLUENT_EXPORT void GetChartableData(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void GetLevelIndices(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void GetLevelData(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void GetLevelAssociation(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void GetChartableDataNames(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void GetLevelNamesByChartableData(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void SetChartInfoForRefinement(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void WriteResultAndRestart(RpcRequest *request, RpcResponse *response);
FLUENT_EXPORT void Set_Flag_Sc_Write_Data(int flag);
FLUENT_EXPORT int  Get_Flag_Sc_Write_Data(void);
FLUENT_EXPORT void CX_SC_Get_Chartable_Equations(char *eqName, int eqStatus);
FLUENT_EXPORT void Accumulate_Chartable_Data(char **eqName, int numEqns);
FLUENT_EXPORT void Set_Source_Var_Name(char *);
FLUENT_EXPORT char *Get_Source_Var_Name(void);
FLUENT_EXPORT void CX_Set_MPC_Host_Name(const char *);
FLUENT_EXPORT char *CX_Get_MPC_Host_Name(void);
FLUENT_EXPORT void CX_Set_MPC_Port_Num(int);
FLUENT_EXPORT int CX_Get_MPC_Port_Num(void);
FLUENT_EXPORT void CX_Set_MPC_SolverName(char *);
FLUENT_EXPORT char *CX_Get_MPC_SolverName(void);
FLUENT_EXPORT void CX_Set_SC_Boolean(void);
FLUENT_EXPORT void SC_Acle_Not_Available(const char *);
FLUENT_EXPORT void Update_Chartable_Monitor_Names(const char *const *, int );
FLUENT_EXPORT void SetMonitorSurfaceNames(const char *const *, int);
FLUENT_EXPORT void SetMonitorVolumeNames(const char *const *, int);
FLUENT_EXPORT void SetMonitorDragNames(const char *const *, int);
FLUENT_EXPORT void SetMonitorLiftNames(const char *const *, int);
FLUENT_EXPORT void SetMonitorMomentNames(const char *const *, int);
FLUENT_EXPORT void SetMonitorStatisticsNames(const char *const *, int);
FLUENT_EXPORT void SetReportMonitorNames(const char *const *, int);
FLUENT_EXPORT int GetNMonitorStatistics(void);
FLUENT_EXPORT void CXGetCurrentMonitorValue(int, const char *, double);
FLUENT_EXPORT void SetMaxIterations_P(int);
FLUENT_EXPORT int GetMaxIterations_P(void);
FLUENT_EXPORT void SetGlobalnMonitors(int);
FLUENT_EXPORT int GetGlobalnMonitors(void);
FLUENT_EXPORT void Allocate_and_Initialize_Monitor_Data(void);
FLUENT_EXPORT void free_monitor_data(void);
FLUENT_EXPORT void PutMonitorData(int, const char *, double);
FLUENT_EXPORT void PutStatisticsMonitorData(char *, int);
FLUENT_EXPORT int IsMonitorSurface(char *);
FLUENT_EXPORT int IsDatarequiredatIterationLevel(char *);
FLUENT_EXPORT int GetDataFrequency(char *);
FLUENT_EXPORT int GetAvgover(char *);
FLUENT_EXPORT int isFlowEquationName(char *);
FLUENT_EXPORT int isMonitorName(char *);
FLUENT_EXPORT int IsMonitorVolume(char *);
FLUENT_EXPORT int IsMonitorDrag(char *);
FLUENT_EXPORT int IsMonitorLift(char *);
FLUENT_EXPORT int IsMonitorMoment(char *);
FLUENT_EXPORT int IsMonitorReport(char *);
FLUENT_EXPORT void processChartDataIndices(RpcRequest *, RpcResponse *, char *, RpcInt64 *);
FLUENT_EXPORT void ProcessChartableData(RpcRequest *, RpcResponse *, char *, RpcDouble *, int);
FLUENT_EXPORT void Server_Update_meshBufferSize(long);
FLUENT_EXPORT void SetGlobalnMonitorNames(const char *const *, int);
FLUENT_EXPORT void free_mesh_data_buffer(void);
FLUENT_EXPORT void Check_Rpc_Status(int, char *, char *, int );
FLUENT_EXPORT void Get_SC_Status_From_Cortex(int *);
FLUENT_EXPORT void SC_Set_Global_Error_Message(char *);
FLUENT_EXPORT void Server_Update_New_Meshfilter_Id(int);
FLUENT_EXPORT void Server_Update_Apply_Meshfilter_Status(int);
FLUENT_EXPORT void Server_Update_Apply_Regionfilter_Status(int);
FLUENT_EXPORT void Server_Update_Region_Ids(int, int *);
FLUENT_EXPORT void Server_Update_Topol_Dim(int, int *);
FLUENT_EXPORT void Server_Update_New_Resultfilter_Id(int);
FLUENT_EXPORT void Server_Update_Apply_Resultfilter_Status(int);
FLUENT_EXPORT void Server_Update_Result_Ids(int, int *);
FLUENT_EXPORT void Server_Update_Component_Counts(int, int *);
FLUENT_EXPORT void Server_Update_Has_Node_Data(int, int *);
FLUENT_EXPORT void Server_Update_Result_Thread_Ids(int, int *);
FLUENT_EXPORT void GetElementCountRaw(long, char *);
FLUENT_EXPORT void cortex_update_element_count(long);
FLUENT_EXPORT void server_update_element_count(long);
FLUENT_EXPORT void GetNodeCountRaw(long);
FLUENT_EXPORT void cortex_update_node_count(long);
FLUENT_EXPORT void server_update_node_count(long);
FLUENT_EXPORT void GetElementsRaw(long, int, long, long, char *);
FLUENT_EXPORT void cortex_update_element_types(int *, int);
FLUENT_EXPORT void server_update_element_types(int *, int);
FLUENT_EXPORT void GetElementTypesRaw(long, long, long);
FLUENT_EXPORT void cortex_update_element_ids(long *, int);
FLUENT_EXPORT void cortex_update_element_c0_ids(long *, int);
FLUENT_EXPORT void cortex_update_element_c1_ids(long *, int);
FLUENT_EXPORT void server_update_element_ids(long *, int);
FLUENT_EXPORT void server_update_element_c0_ids(long *, int);
FLUENT_EXPORT void server_update_element_c1_ids(long *, int);
FLUENT_EXPORT void GetElementIdsRaw(long, int, long, long);
FLUENT_EXPORT void cortex_update_element_node_counts(int *, int);
FLUENT_EXPORT void server_update_element_node_counts(int *, int);
FLUENT_EXPORT void GetElementNodeCountsRaw(long, int, long, long);
FLUENT_EXPORT void cortex_update_element_node_ids(long *, int);
FLUENT_EXPORT void server_update_element_node_ids(long *, int);
FLUENT_EXPORT void GetElementNodeIdsRaw(long, int, long, long);
FLUENT_EXPORT void cortex_update_node_ids(long *, int);
FLUENT_EXPORT void cortex_update_node_coords(double *, int);
FLUENT_EXPORT void server_update_nodes(long *, int, double *, int);
FLUENT_EXPORT void GetNodesRaw(long, long, long);
FLUENT_EXPORT void GetNodeDataCountRaw(long);
FLUENT_EXPORT void TestGetNodeDataCountRaw(long);
FLUENT_EXPORT void cortex_update_node_data(double *, int);
FLUENT_EXPORT void server_update_node_data(double *, int);
FLUENT_EXPORT void TestGetNodeDataRaw(long, long, long);
FLUENT_EXPORT void test_update_node_data(int, int, int, void *);
FLUENT_EXPORT void server_get_node_data(double *, int);
FLUENT_EXPORT void Create_Server(void);
FLUENT_EXPORT int  CX_Get_Ansrpc_Server_Port(void);
FLUENT_EXPORT char *CX_Get_Ansrpc_Server_Host(void);
FLUENT_EXPORT void Create_Client(void);
FLUENT_EXPORT void Create_Assigntoken_Locally(void);
FLUENT_EXPORT void Mpc_Register_Interface_Methods(void);
FLUENT_EXPORT double GetProfileData(int);

/* COUPLING RUN CONTROL REQUESTS */
FLUENT_EXPORT int Get_Coupling_Definition_Method(void);
FLUENT_EXPORT int Get_Coupling_Step(int offset);
FLUENT_EXPORT int Get_Coupling_Iteration_Index(int cpldefmethod, int stepi, int offset);
FLUENT_EXPORT double Get_Analysis_Initial_Time(void);
FLUENT_EXPORT double Get_Analysis_End_Time(void);
FLUENT_EXPORT int Get_General_Num_of_Coupling_Steps(void);
FLUENT_EXPORT double Get_Timestep_Start_Time(int tstepi);
FLUENT_EXPORT double Get_Timestep_End_Time(int tstepi);
FLUENT_EXPORT int Is_Analysis_Complete(void);
FLUENT_EXPORT int Is_Step_Complete(int cpldefmethod, int cpldstep);
FLUENT_EXPORT void CX_SC_Get_Data(int);
FLUENT_EXPORT int Get_Max_Coupling_Iterations(int cpldefmethod, int stepi);
FLUENT_EXPORT void GetNodeDataRaw(long, long, long, char *, char *);
FLUENT_EXPORT int Get_Min_Coupling_Iterations(int, int);
FLUENT_EXPORT int Get_Restart_Initial_Step_Index(void);
FLUENT_EXPORT void CX_Insert_Point_Data_As_Marker(int, cxboolean);

/* error handling */
FLUENT_EXPORT void Set_Fatal_Error(int);
FLUENT_EXPORT int Is_Fatal_Error(void);
FLUENT_EXPORT void  Handle_Fluent_User_Interrupt(const char *);
FLUENT_EXPORT void Set_User_Interrupt(int);
FLUENT_EXPORT int Get_User_Interrupt();
FLUENT_EXPORT void MPC_Set_Convergence_Flag(int);
FLUENT_EXPORT int Get_Token_Status(void);
FLUENT_EXPORT void Send_Mpc_Fatal_Error(char *);
FLUENT_EXPORT int GetExitStatus(void);
FLUENT_EXPORT void Send_Service_Registry_Fatal_Error(const char *where);
FLUENT_EXPORT void Send_SCAnalysis_Fatal_Error(const char *where);

FLUENT_EXPORT void Set_Global_Start_Iter_Index(int);
FLUENT_EXPORT void Set_Global_End_Iter_Index(int);
#endif

#endif /* _CORTEXMPC_H_ */
