/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_UDMS_H
#define _FLUENT_UDMS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dll.h"


typedef struct user_defined_vars_t
{
  char name [64];   /* Full name of UDM */
  char units[64];   /* units (must be lower case and hyphenated */
  cxboolean user_set_p;
  int index;
} User_Defined_Vars;

extern FLUENT_EXPORT User_Defined_Vars *user_memory_vars;
extern FLUENT_EXPORT User_Defined_Vars *user_node_memory_vars;
extern FLUENT_EXPORT User_Defined_Vars *user_scalar_vars;

FLUENT_EXPORT void Model_Initialize_uds(void);
FLUENT_EXPORT void Model_Initialize_udm(void);

FLUENT_EXPORT void Reset_N_User_Memory_Vars(void);
FLUENT_EXPORT void Init_User_Memory_Vars(void);
FLUENT_EXPORT void Init_User_Node_Memory_Vars(void);
FLUENT_EXPORT void Init_User_Scalar_Vars(void);
FLUENT_EXPORT Pointer lupdateudmconfig(void);

FLUENT_EXPORT void Set_User_Memory_Name(int i, char *name);
FLUENT_EXPORT void Set_User_Memory_Units(int i, char *units);
FLUENT_EXPORT void Set_User_Node_Memory_Name(int i, char *name);
FLUENT_EXPORT void Set_User_Node_Memory_Units(int i, char *units);
FLUENT_EXPORT void Set_User_Scalar_Name(int i, char *name);
FLUENT_EXPORT void Set_User_Scalar_Units(int i, char *units);
FLUENT_EXPORT void Clean_Units_String(char *str);

FLUENT_EXPORT void Set_UDS_Variables(Pointer p);
FLUENT_EXPORT void UDS_Derivatives(Domain *domain, int ns);

FLUENT_EXPORT int Read_User_Node_Memory_Data(Domain *domain, FILE *file, cxboolean binary, cxboolean double_data);
FLUENT_EXPORT int Write_User_Node_Memory_Data(Domain *domain, FILE *file, cxboolean binary);

FLUENT_EXPORT void Register_Node_UDM_HDF_Data_IO_Managers(void);
FLUENT_EXPORT void Deregister_Node_UDM_HDF_Data_IO_Managers(void);
#define UDM_UNRESERVED -1
/* reserve UDMs for UDF library */
FLUENT_EXPORT int Reserve_User_Memory_Vars(int n);
FLUENT_EXPORT int Reserved_User_Memory_Vars(void);
FLUENT_EXPORT void Inc_Res_User_Memory_Vars(int n);
#define UDS_UNRESERVED -1
/* reserve UDSs for UDF library */
FLUENT_EXPORT int Reserve_User_Scalar_Vars(int n);
FLUENT_EXPORT int Reserved_User_Scalar_Vars(void);
#if !RP_NODE
FLUENT_EXPORT void Reset_Reserved_User_Scalars(void);
#endif
FLUENT_EXPORT void Inc_Res_User_Scalar_Vars(int n);

typedef struct
{
  int domain_id;
  int zonetype;
  int n_zones;
  int *solution_zones;
  char flux_fcn[PROP_UDF_NAME_LENGTH];
  char unsteady_fcn[PROP_UDF_NAME_LENGTH];
} UDS_Var;

extern FLUENT_EXPORT UDS_Var uds_vars[MAX_UDS_EQNS];

#ifdef __cplusplus
}
#endif

#endif /* _FLUENT_UDMS_H */
