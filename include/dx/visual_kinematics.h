/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _VISUAL_KINEMATICS_H
#define _VISUAL_KINEMATICS_H

#include "dll.h"

#if SEEM
#if VKI_LIB
#include "vdm/vdm.h"

#define VIS_THERMAL 0
#define MAX_SCALAR_VKI 5
#define MAX_SCALAR_VKI_STRUCTURAL 3
#define MAX_SCALAR_VKI_THERMAL 3
#define MAX_SCALAR_VKI_RESULTS 38
#define MAX_FSI_SETS 50

/* CGNS library can write bc-name of atmost 32 characters. */
#define MAX_LENGTH_CGNS_BCNAME 32

#if RP_DOUBLE
#define Vreal Vdouble
#else
#define Vreal Vfloat
#endif

#define VIEW_FLAG(flags,ind) (((flags) >> ((ind)-1)) & 1)

#define VALID_POLY_FACE_THREAD(thread) (BOUNDARY_FACE_THREAD_P (thread) && !SHELL_FACE_THREAD_P (thread)&&\
                                        !SLIDING_INTERFACE_THREAD_P (thread) && !SLIDING_BOUNDARY_THREAD_P (thread))
typedef enum Export_File_Type
{
  ABAQUS = 1,
  NASTRAN,
  SDRC_UNIVERSAL,
  PATRAN,
  ANSYS,
  TECPLOT,
#if DEBUG_VKI
  CGNS,
  NATIVE
#else
  CGNS
#endif
} Export_File_Type_t;

typedef struct Loads_For_Export
{
  char *var_name; /* variable name*/
  void (*load_func)(Domain *, Pointer, Pointer, cxboolean); /* loading function */
} Loads_For_Export_t;

typedef struct FSI_Loads_For_Export
{
  char *var_name; /* variable name*/
  void (*load_func)(Domain *); /* loading function */
} Fsi_Loads_For_Export_t;

typedef struct Results_For_Export
{
  char *fluent_var_name; /* Fluent variable name*/
  void (*load_func)(Domain *, Pointer, char *, cxboolean); /* loading function */
  int result_no;
  int qualifier;
} Results_For_Export_t;

#if !RP_NODE
/*redefined in fl_api.h ... changes should be synchronised*/
typedef struct Vki_Import_Object
{
  int nnodes;             /*number of nodes in fem mesh*/
  int nelems;             /*number of elements in fem mesh*/
  Vfloat extent[2][3];   /*max-min values of vertices*/
  int num;                /* number of node sets*/
  int fnum;                /* number of face sets*/
  int elnum;              /* number of element sets*/
  int file_type;          /* input file type */
  cxboolean volume_mesh;
  int setlist[MAX_FSI_SETS];           /* hash key corresponding to node sets */
  int fsetlist[MAX_FSI_SETS];           /* hash key corresponding to face sets */
  int elsetlist[MAX_FSI_SETS];         /* hash key corresponding to element sets */
  char filename[256];     /* input file name */
  void *input_fp;
  vis_Model *model;
  vis_Connect *connect;
  vis_GridFun *gf;
  vdm_DataFun *datafun;
  vdm_LMan  *lman;
  vis_Group *grp_src, *grp_dst;
  vis_LCase *lcase;
  vis_RCase *rcase;
  cxboolean case_read;    /* already case held in vki library */
  Vchar *setname[MAX_FSI_SETS];     /* node set name */
  Vchar *fsetname[MAX_FSI_SETS];  /* face set name */
  Vchar *elsetname[MAX_FSI_SETS];   /* element set name */
  double fsi_length_factor;
} Vki_Object_t;

typedef struct Vki_Import_Fns
{
  vdm_DataFun *(*vdm_DataFunBegin_) (void);
  void *(*vdm_LibBegin_)(void);
  void (*vdm_InitDataFun_) (void *, vdm_DataFun *);
  void (*vdm_PLOT3DLibSetGridType_) (void *, Vint, Vint, Vint);
  void (*vdm_DataFunSetConvention_) (vdm_DataFun *, Vint);
  void (*vdm_DataFunOpen_) (vdm_DataFun *, Vint, Vchar *, Vint);
  void (*vdm_DataFunNumDomains_) (vdm_DataFun *, Vchar *, Vint, Vint *);
  void (*vdm_ABALibUpgradeOdb_)(void *, Vchar *, Vchar *);
  void (*vdm_ABALibGetInteger_) (void *, Vint, Vint *);
  /* void (*vdm_DataFunGetNumEntities_) (vdm_DataFun *, Vint, Vint *);*/
  Vint (*vdm_DataFunError_) (vdm_DataFun *);
  vis_Model *(*vis_ModelBegin_) (void);
  vdm_LMan *(*vdm_LManBegin_) (void);
  void (*vdm_LManSetObject_) (vdm_LMan *, Vint, Vobject *);
  void (*vdm_LManLoadModel_) (vdm_LMan *, vis_Model *);
  Vint (*vdm_LManError_) (vdm_LMan *);
  void (*vis_ModelSetObject_)(vis_Model *, Vint, Vobject *);
  void (*vis_ModelDelete_)(vis_Model *);
  void (*vdm_LManSetParami_)(vdm_LMan *, Vint, Vint);
  void (*vdm_DataFunClose_) (vdm_DataFun *);
  void (*vdm_DataFunEnd_) (vdm_DataFun *);
  void *(*vdm_LibEnd_) (void *);
  void (*vdm_LManEnd_) (vdm_LMan *);
  void (*convert_2d_)(vis_Model *model);
  void (*mod_partid_elemset_)(vis_Model *model);
  void (*add_inter_nodeset_)(vis_Model *model);
  void (*process_ensight_)(vis_Model *model);
  void (*process_tgrid_)(vis_Model *model);
  void (*process_shelltointer_)(vis_Model *model);
  void (*ignore_periodic1d_)(vis_Model *model);
  void (*add_inter_elementset_)(vis_Model *model);
  void (*process_contacttoshell_)(vis_Model *model);
  int (*get_model_)(Vki_Object_t *, Vint, Vint, Vint);
  void (*free_memory_)(Vki_Object_t *);
} Vki_Import_Fn_t;

typedef struct Vki_Fsi_Fns
{
  void (*vis_ConnectCoords_)(const vis_Connect *, Vint, Vint [], Vfloat [][3]);
  void (*vis_ConnectCoordsdv_)(const vis_Connect *, Vint, Vint [], Vdouble [][3]);
  void (*vis_ConnectEdgeGroup_)(vis_Connect *, Vint, vis_Group *, vis_Group *);
  void (*vis_ConnectElemAssoc_)(vis_Connect *, Vint, Vint, Vint [], Vint []);
  void (*vis_ConnectSetElemAssoc_)(vis_Connect *, Vint, Vint, Vint);
  void (*vis_ConnectElemNode_)(const vis_Connect *, Vint, Vint *, Vint []);
  void (*vis_ConnectElemNum_)(const vis_Connect *, Vint, Vint, Vint *);
  void (*vis_ConnectElemCorn_)(const vis_Connect *, Vint, Vint, Vint, Vint *, Vint []);
  void (*vis_ConnectExtent_)(vis_Connect *, vis_Group *, Vfloat [2][3]);
  void (*vis_ConnectFaceGroup_)(vis_Connect *, Vint, vis_Group *, vis_Group *);
  void (*vis_ConnectGridFun_)(vis_Connect *, vis_GridFun *);
  void (*vis_ConnectNumber_)(const vis_Connect *, Vint, Vint *);

  void (*vis_ConnectKernel_) (vis_Connect *, Vint);
  void (*vis_ConnectNodeElem_)(const vis_Connect *, Vint, Vint *, Vint []);
  void (*vis_ConnectNumElemNode_)(const vis_Connect *, Vint, Vint *);
  void (*vis_ConnectNumNodeElem_)(const vis_Connect *, Vint, Vint *);
  void (*vis_ConnectSizeElemdv_)(vis_Connect *, Vint, Vint, Vint, Vdouble *);
  void (*vis_ConnectNodeAdj_)(const vis_Connect *, Vint, Vint [], Vint *, Vint []);


  vis_GridFun *(*vis_GridFunBegin_)(void);
  vis_Group *(*vis_GroupBegin_)(void);
  void (*vis_GroupBoolean_)(vis_Group *, Vint, vis_Group *);
  void (*vis_GroupClear_)(vis_Group *);
  void (*vis_GroupCopy_)(vis_Group *, vis_Group *);
  void (*vis_GroupCount_)(const vis_Group *, Vint *, Vint *);
  void (*vis_GroupDef_)(vis_Group *, Vint, Vint, Vint );
  void (*vis_GroupIdTran_)(vis_Group *, vis_IdTran *);
  void (*vis_GroupInitIndex_)(vis_Group *);
  void (*vis_GroupNextIndex_)(vis_Group *, Vint *, Vint *);
  void (*vis_GroupSetIndex_)(vis_Group *, Vint, Vint );
  void (*vis_GroupEnd_)(vis_Group *);
  vis_IdTran *(*vis_IdTranBegin_)(void);
  void (*vis_IdTranDef_)(vis_IdTran *, Vint );
  void (*vis_IdTranEnd_)(vis_IdTran *);
  void (*vis_IdTranGetId_)(const vis_IdTran *, Vint, Vint *);
  void (*vis_IdTranInq_)(const vis_IdTran *, Vint *);
  vis_LCase *(*vis_LCaseBegin_)(void);
  void (*vis_LCaseSetConc_)(vis_LCase *, Vint, Vint, Vreal [3]);
  void (*vis_LCaseConc_)(vis_LCase *, Vint, Vint, Vreal [3]);
  void (*vis_LCaseSetDist_)(vis_LCase *, Vint, Vint, Vint, Vint, Vreal []);
  void (*vis_LCaseSetObject_)(vis_LCase *, Vint, Vobject *);
  void (*vis_ModelGetHashTable_)(vis_Model *, Vint, vsy_HashTable **);
  void (*vis_ModelSetHashTable_)(vis_Model *, Vint, vsy_HashTable *);
  void (*vis_ModelSetObject_)(vis_Model *, Vint, Vobject *);
  vis_RCase *(*vis_RCaseBegin_)(void);
  void (*vis_RCaseSetSPC_)(vis_RCase *, Vint, Vint, Vint, Vreal [], Vint );
  vis_SProp *(*vis_SPropBegin_)(void);
  void (*vis_SPropDef_)(vis_SProp *, Vint );
  void (*vis_SPropSetValued_)(vis_SProp *, Vint, Vdouble );
  void (*vis_SPropSetValuei_)(vis_SProp *, Vint, Vint );
  vis_EProp *(*vis_EPropBegin_) (void);
  void (*vis_EPropDef_)(vis_EProp *, Vint);
  void (*vis_EPropInq_)(vis_EProp *, Vint);
  void (*vis_EPropSetValued_)(vis_EProp *, Vint, Vdouble );
  void (*vis_EPropSetValuei_)(vis_EProp *, Vint, Vint );
  vis_MProp *(*vis_MPropBegin_) (void);
  void (*vis_MPropDef_)(vis_MProp *, Vint);
  void (*vis_MPropSetValued_)(vis_MProp *, Vint, Vdouble );
  void (*vis_MPropSetValuei_)(vis_MProp *, Vint, Vint );
  void (*vis_ModelWrite_)(vis_Model *, Vint, Vchar *);
  vsy_HashTable *(*vsy_HashTableBegin_)(void);
  void (*vsy_HashTableInsert_)(vsy_HashTable *, Vint, Vobject *);
  void (*vsy_HashTableLookup_)(const vsy_HashTable *, Vint, Vobject **);
  vsy_List *(*vsy_ListBegin_)(void);
  void (*vsy_ListInsert_)(vsy_List *, Vint, Vobject *);
  void (*vis_ModelSetList_)(vis_Model *, Vint, vsy_List *);
} Vki_Fsi_Fns_t;

typedef struct Vki_Export_Fns
{
  vdm_DataFun *(*vdm_DataFunBegin_)(void);
  void (*vdm_DataFunEnd_)(vdm_DataFun *);
  vdm_LMan *(*vdm_LManBegin_)(void);
  void (*vdm_LManEnd_)(vdm_LMan *);
  void (*vdm_LManSetObject_)(vdm_LMan *, Vint, Vobject *);
  vis_Connect *(*vis_ConnectBegin_)(void);
  void (*vis_ConnectPre_)(vis_Connect *, Vint);
  void (*vis_ConnectDef_)(vis_Connect *, Vint, Vint );
  void (*vis_ConnectElemNum_)(const vis_Connect *, Vint, Vint, Vint *);
  void (*vis_ConnectEnd_)(vis_Connect *);
  void (*vis_ConnectGridFun_)(vis_Connect *, vis_GridFun *);
#if RP_DOUBLE
  void (*vis_ConnectSetCoords_)(vis_Connect *, Vint, Vdouble [3]);
#else
  void (*vis_ConnectSetCoords_)(vis_Connect *, Vint, Vfloat [3]);
#endif
  void (*vis_ConnectSetElemAssoc_)(vis_Connect *, Vint, Vint, Vint );
  void (*vis_ConnectSetElemNode_)(vis_Connect *, Vint, Vint []);
  void (*vis_ConnectSetNodeAssoc_)(vis_Connect *, Vint, Vint, Vint );
  void (*vis_ConnectSetPartName_)(vis_Connect *, Vint, Vchar *);
  void (*vis_ConnectSetTopology_)(vis_Connect *, Vint, Vint, Vint, Vint, Vint );
  vis_EProp *(*vis_EPropBegin_)(void);
  void (*vis_EPropDef_)(vis_EProp *, Vint );
  void (*vis_EPropSetValuef_)(vis_EProp *, Vint, Vfloat );
  void (*vis_EPropSetValuei_)(vis_EProp *, Vint, Vint );
  vis_GridFun *(*vis_GridFunBegin_)(void);
  void (*vis_GridFunEnd_)(vis_GridFun *);
  vis_IdTran *(*vis_IdTranBegin_)(void);
  void (*vis_IdTranEnd_)(vis_IdTran *);
  void (*vis_IdTranIndex_)(vis_IdTran *, Vint, Vint *);
  void (*vis_IdTranIndices_)(vis_IdTran *, Vint, Vint [], Vint []);
  void (*vis_IdTranSetId_)(vis_IdTran *, Vint, Vint );
  void (*vis_IdTranSetName_)(vis_IdTran *, Vchar *);
  vis_LCase *(*vis_LCaseBegin_)(void);
#if RP_DOUBLE
  void (*vis_LCaseSetConc_)(vis_LCase *, Vint, Vint, Vdouble [3]);
#else
  void (*vis_LCaseSetConc_)(vis_LCase *, Vint, Vint, Vfloat [3]);
#endif
#if RP_DOUBLE
  void (*vis_LCaseSetDist_)(vis_LCase *, Vint, Vint, Vint, Vint, Vdouble []);
#else
  void (*vis_LCaseSetDist_)(vis_LCase *, Vint, Vint, Vint, Vint, Vfloat []);
#endif
  void (*vis_LCaseSetObject_)(vis_LCase *, Vint, Vobject *);
  void (*vis_ModelEnd_)(vis_Model *);
  void (*vis_ModelPrint_)(vis_Model *);
  vis_MProp *(*vis_MPropBegin_)(void);
  void (*vis_MPropDef_)(vis_MProp *, Vint );
  void (*vis_MPropSetValued_)(vis_MProp *, Vint, Vdouble );
  vis_RCase *(*vis_RCaseBegin_)(void);
#if RP_DOUBLE
  void (*vis_RCaseSetSPC_)(vis_RCase *, Vint, Vint, Vint, Vdouble [], Vint);
#else
  void (*vis_RCaseSetSPC_)(vis_RCase *, Vint, Vint, Vint, Vfloat [], Vint );
#endif
  vis_RProp *(*vis_RPropBegin_)(void);
  void (*vis_RPropDef_)(vis_RProp *, Vint, Vint );
  void (*vis_RPropEnd_)(vis_RProp *);
#if 0
  void (*vis_RPropSetCAux_)(vis_RProp *, Vchar *);
#endif
  void (*vis_RPropSetQual_)(vis_RProp *, Vint, Vint [], Vchar *);
  void (*vis_RPropSetIds_)(vis_RProp *, Vint id1, Vint id2, Vint id3);
  void (*vis_RPropSetType_)(vis_RProp *, Vint );
  void (*vis_RPropSetValued_)(vis_RProp *, Vint, Vdouble);
  vis_SProp *(*vis_SPropBegin_)(void);
  void (*vis_SPropDef_)(vis_SProp *, Vint );
  void (*vis_SPropSetValued_)(vis_SProp *, Vint, Vdouble );
  void (*vis_SPropSetValuei_)(vis_SProp *, Vint, Vint );
  vis_State *(*vis_StateBegin_)(void);
  void (*vis_StateDef_)(vis_State *, Vint, Vint, Vint, Vint );
  void (*vis_StateEnd_)(vis_State *);
#if RP_DOUBLE
  void (*vis_StateSetData_)(vis_State *, Vint, Vdouble []);
#else
  void (*vis_StateSetData_)(vis_State *, Vint, Vfloat []);
#endif
  void (*vis_StateSetObject_)(vis_State *, Vint, Vobject *);
  void (*vsy_HashTableEnd_)(vsy_HashTable *);
  void (*vsy_HashTableForEach_)(vsy_HashTable *, Vfunc1 *);
  void (*vsy_HashTableInsert_)(vsy_HashTable *, Vint, Vobject *);
  void (*vsy_ListEnd_)(vsy_List *);
  void (*vsy_ListForEach_)(vsy_List *, Vfunc1 *);
  void (*vsy_ListInsert_)(vsy_List *, Vint, Vobject *);
} vki_export_fns_t;

typedef struct Vki_Error_Handler
{
  void (*vut_ErrorSetHandler_) (void (*) (const Vchar *, Vint, const Vchar *));
  Vchar *(*vut_ErrorString_) (Vint);
} Vki_Error;

extern FLUENT_EXPORT void *libvki;
extern FLUENT_EXPORT Vki_Object_t *vki_model;
extern FLUENT_EXPORT Vki_Import_Fn_t *vki_import_fns;
extern FLUENT_EXPORT Vki_Error *vki_error_fns;
#endif

#define VALID_LOAD_FACE(ft) (((BOUNDARY_FACE_THREAD_P(ft))&&(THREAD_TYPE(ft) == THREAD_F_WALL)\
                             && (!SHELL_FACE_THREAD_P(ft)) && ((LENGTH_FACE(ft))!=0)&&\
                             (!SLIDING_INTERFACE_THREAD_P(ft))&&(!SHADOW_FACE_THREAD_P(ft)))\
                             ||(SHADOW_FACE_THREAD_P(ft)&&(MAJOR_FACE_THREAD_P(ft)))\
                             ||(PERIODIC_FACE_THREAD_P(ft)))
#define MAJOR_THREAD(t) (NNULLP(t) && MAJOR_FACE_THREAD_P(t) && NNULLP(THREAD_SHADOW(t)))

#define VALID_EXPORT_FACE(thread, merge_shadow) ((THREAD_TYPE(thread) != THREAD_F_INTERIOR)&&\
                                                 (NULLP(THREAD_SHADOW(thread))||\
                                                  (MAJOR_THREAD(thread)  && merge_shadow)||\
                                                  (NNULLP(THREAD_SHADOW(thread)) && !merge_shadow))&&\
                                                 (!((NULLP(THREAD_T1(thread))) && SHELL_CELL_THREAD_P(THREAD_T0(thread))))&&\
                                                 (!SLIDING_INTERFACE_THREAD_P(thread)))
#define VALID_CGNS_EXPORT_FACE(thread, merge_shadow) (((THREAD_TYPE(thread) != THREAD_F_INTERIOR) || (!INTERIOR_FACE_THREAD_P(thread)))&&\
                                                      (NULLP(THREAD_SHADOW(thread))||\
                                                      (MAJOR_THREAD(thread)  && merge_shadow)||\
                                                      (NNULLP(THREAD_SHADOW(thread)) && !merge_shadow))&&\
                                                      (!((NULLP(THREAD_T1(thread))) && SHELL_CELL_THREAD_P(THREAD_T0(thread))))&&\
                                                      (!SLIDING_INTERFACE_THREAD_P(thread)))

FLUENT_EXPORT void Write_Model_Object(const char *, Domain *, Export_File_Type_t, Pointer, Pointer, Pointer, Pointer, Pointer, cxboolean );
FLUENT_EXPORT Pointer Import_Visual_Kinematics(Domain **, int, const char *, cxboolean );
FLUENT_EXPORT Pointer Import_Fem_Mesh(Domain *, int, const char *, Pointer, Pointer, Pointer);
FLUENT_EXPORT void Delete_Fem_Mesh(void);
FLUENT_EXPORT void Display_Fem_Threads(Pointer, Pointer);
#if !RP_NODE
FLUENT_EXPORT int load_model(void);
FLUENT_EXPORT int init_model(void);
FLUENT_EXPORT void user_ErrorHandler(const Vchar *, Vint, const Vchar *);
FLUENT_EXPORT cxboolean Init_Import_API(void);
FLUENT_EXPORT cxboolean Init_Error_API(void);

FLUENT_EXPORT void Free_Import_API(void);
FLUENT_EXPORT void Free_Error_API(void);
FLUENT_EXPORT int delete_model(void);
#endif
FLUENT_EXPORT cxboolean VKI_Open_Library(void);
FLUENT_EXPORT void VKI_Close_Library(void);
#endif
#endif
#endif
