/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_HTC_LB_H_
#define _FLUENT_HTC_LB_H_

#include "global.h"
#include "mem.h"

FLUENT_EXPORT cxboolean HTC_LB_Enabled(void);
FLUENT_EXPORT cxboolean Open_Htc_Lb_Library(cxboolean);
FLUENT_EXPORT cxboolean Close_Htc_Lb_Library(void);
FLUENT_EXPORT cxboolean HTC_Lb_Library_Opened(cxboolean);
FLUENT_EXPORT void Clear_HTC_Lb_Domain(cxboolean);
FLUENT_EXPORT void InitializeHtcLbPrimitives(void);
FLUENT_EXPORT void Register_HTC_LB_IO_Managers(void);
FLUENT_EXPORT void HTC_LB_Set_Enabled(const cxboolean);
FLUENT_EXPORT cxboolean HTC_LB_Get_Reading(void);
FLUENT_EXPORT void HTC_LB_Set_Reading(cxboolean);


typedef struct htc_io_struct
{
  int id;
  Thread_Type type;
  const char *name;
  char buffer[MAX_NAME_LENGTH];
} htc_io_t;

#if defined(_WIN32) || defined (WIN64)
#define HTC_STDCALL __stdcall
#else
#define HTC_STDCALL
#endif

typedef const char **
(HTC_STDCALL *HTCSolutionVarFn)
(
  const char *,
  const int, const int,
  real *, size_t *, size_t *
);

FLUENT_EXPORT void HTC_LB_Save_Data_Id(void);
FLUENT_EXPORT void HTC_LB_Update_Data_Id(void);
FLUENT_EXPORT cxboolean HTC_LB_Data_Modified_P(void);
FLUENT_EXPORT HTCSolutionVarFn HTC_LB_Get_Solution_Var_Fn(void);
FLUENT_EXPORT void HTC_LB_Read_Data(const char *);
FLUENT_EXPORT void HTC_LB_Write_Data(const char *);
FLUENT_EXPORT void HTC_LB_Write_Surface_Data(const char *, const cxboolean,
                                             const size_t, const char **);
FLUENT_EXPORT void HTC_LB_Query_Data_File(const char *, cxboolean *);
FLUENT_EXPORT void HTC_LB_Query_Case_File(const char *, cxboolean *);
FLUENT_EXPORT void HTC_LB_Read_Settings(const char *, const char *,
                                        const size_t, const char **,
                                        char **);
FLUENT_EXPORT void HTC_LB_Write_Settings(const char *, const char *,
                                         const cxboolean,
                                         const size_t, const char **,
                                         const char **);
FLUENT_EXPORT void HTC_LB_Read_Surface_Mesh(const char *,
                                            size_t *, htc_io_t **,
                                            const cxboolean);
FLUENT_EXPORT void HTC_LB_Write_Surface_Mesh(const char *,
                                             const size_t, const htc_io_t *,
                                             const cxboolean, const cxboolean);

#define HTC_LB_LAYER_ZERO  0
#define HTC_LB_LAYER_INT   1
#define HTC_LB_LAYER_EXT   2
#define HTC_LB_LAYER_MAX   3

typedef struct region_info_struct
{
  char map;
  int  type;
  real geomv[ND_3];
  real geoms;
  real bcv[ND_3];
} region_info_t;

#define HTC_LB_NEIGHBOR_NULL -1
#define HTC_LB_NEIGHBOR_E     0
#define HTC_LB_NEIGHBOR_W     1
#define HTC_LB_NEIGHBOR_N     2
#define HTC_LB_NEIGHBOR_S     3
#define HTC_LB_NEIGHBOR_F     4
#define HTC_LB_NEIGHBOR_B     5
#define HTC_LB_NEIGHBOR_NE    6
#define HTC_LB_NEIGHBOR_SW    7
#define HTC_LB_NEIGHBOR_NW    8
#define HTC_LB_NEIGHBOR_SE    9
#define HTC_LB_NEIGHBOR_FE   10
#define HTC_LB_NEIGHBOR_BW   11
#define HTC_LB_NEIGHBOR_FW   12
#define HTC_LB_NEIGHBOR_BE   13
#define HTC_LB_NEIGHBOR_FN   14
#define HTC_LB_NEIGHBOR_BS   15
#define HTC_LB_NEIGHBOR_FS   16
#define HTC_LB_NEIGHBOR_BN   17
#define HTC_LB_NNEIGHBORS    18

#define HTC_LB_POP_C     0
#define HTC_LB_POP_E     1
#define HTC_LB_POP_W     2
#define HTC_LB_POP_N     3
#define HTC_LB_POP_S     4
#define HTC_LB_POP_F     5
#define HTC_LB_POP_B     6
#define HTC_LB_POP_NE    7
#define HTC_LB_POP_SW    8
#define HTC_LB_POP_NW    9
#define HTC_LB_POP_SE   10
#define HTC_LB_POP_FE   11
#define HTC_LB_POP_BW   12
#define HTC_LB_POP_FW   13
#define HTC_LB_POP_BE   14
#define HTC_LB_POP_FN   15
#define HTC_LB_POP_BS   16
#define HTC_LB_POP_FS   17
#define HTC_LB_POP_BN   18
#define HTC_LB_NPOPS    19

#define HTC_LB_BNDR_NULL  0
#define HTC_LB_BNDR_E     1
#define HTC_LB_BNDR_W     2
#define HTC_LB_BNDR_N     3
#define HTC_LB_BNDR_S     4
#define HTC_LB_BNDR_F     5
#define HTC_LB_BNDR_B     6

#define HTC_LB_INVERSE_NEIGHBOR_E    HTC_LB_NEIGHBOR_W
#define HTC_LB_INVERSE_NEIGHBOR_W    HTC_LB_NEIGHBOR_E
#define HTC_LB_INVERSE_NEIGHBOR_N    HTC_LB_NEIGHBOR_S
#define HTC_LB_INVERSE_NEIGHBOR_S    HTC_LB_NEIGHBOR_N
#define HTC_LB_INVERSE_NEIGHBOR_F    HTC_LB_NEIGHBOR_B
#define HTC_LB_INVERSE_NEIGHBOR_B    HTC_LB_NEIGHBOR_F
#define HTC_LB_INVERSE_NEIGHBOR_NE   HTC_LB_NEIGHBOR_SW
#define HTC_LB_INVERSE_NEIGHBOR_SW   HTC_LB_NEIGHBOR_NE
#define HTC_LB_INVERSE_NEIGHBOR_NW   HTC_LB_NEIGHBOR_SE
#define HTC_LB_INVERSE_NEIGHBOR_SE   HTC_LB_NEIGHBOR_NW
#define HTC_LB_INVERSE_NEIGHBOR_FE   HTC_LB_NEIGHBOR_BW
#define HTC_LB_INVERSE_NEIGHBOR_BW   HTC_LB_NEIGHBOR_FE
#define HTC_LB_INVERSE_NEIGHBOR_FW   HTC_LB_NEIGHBOR_BE
#define HTC_LB_INVERSE_NEIGHBOR_BE   HTC_LB_NEIGHBOR_FW
#define HTC_LB_INVERSE_NEIGHBOR_FN   HTC_LB_NEIGHBOR_BS
#define HTC_LB_INVERSE_NEIGHBOR_BS   HTC_LB_NEIGHBOR_FN
#define HTC_LB_INVERSE_NEIGHBOR_FS   HTC_LB_NEIGHBOR_BN
#define HTC_LB_INVERSE_NEIGHBOR_BN   HTC_LB_NEIGHBOR_FS

#define HTC_LB_INVERSE_POP_C    HTC_LB_POP_C
#define HTC_LB_INVERSE_POP_E    HTC_LB_POP_W
#define HTC_LB_INVERSE_POP_W    HTC_LB_POP_E
#define HTC_LB_INVERSE_POP_N    HTC_LB_POP_S
#define HTC_LB_INVERSE_POP_S    HTC_LB_POP_N
#define HTC_LB_INVERSE_POP_F    HTC_LB_POP_B
#define HTC_LB_INVERSE_POP_B    HTC_LB_POP_F
#define HTC_LB_INVERSE_POP_NE   HTC_LB_POP_SW
#define HTC_LB_INVERSE_POP_SW   HTC_LB_POP_NE
#define HTC_LB_INVERSE_POP_NW   HTC_LB_POP_SE
#define HTC_LB_INVERSE_POP_SE   HTC_LB_POP_NW
#define HTC_LB_INVERSE_POP_FE   HTC_LB_POP_BW
#define HTC_LB_INVERSE_POP_BW   HTC_LB_POP_FE
#define HTC_LB_INVERSE_POP_FW   HTC_LB_POP_BE
#define HTC_LB_INVERSE_POP_BE   HTC_LB_POP_FW
#define HTC_LB_INVERSE_POP_FN   HTC_LB_POP_BS
#define HTC_LB_INVERSE_POP_BS   HTC_LB_POP_FN
#define HTC_LB_INVERSE_POP_FS   HTC_LB_POP_BN
#define HTC_LB_INVERSE_POP_BN   HTC_LB_POP_FS

#define HTC_LB_CHILD_NULL -1
#define HTC_LB_CHILD_BSW   0
#define HTC_LB_CHILD_BSE   1
#define HTC_LB_CHILD_BNW   2
#define HTC_LB_CHILD_BNE   3
#define HTC_LB_CHILD_FSW   4
#define HTC_LB_CHILD_FSE   5
#define HTC_LB_CHILD_FNW   6
#define HTC_LB_CHILD_FNE   7
#define HTC_LB_NCHILDREN   8

#define HTC_LB_OCT_LEAF_FLAG             (1)
#define HTC_LB_OCT_EXTERIOR_FLAG         (1<<1)
#define HTC_LB_OCT_MARK_FLAG             (1<<2)
#define HTC_LB_OCT_INTERIOR_FLAG         (1<<3)
#define HTC_LB_OCT_SYMMETRY_FLAG         (1<<4)
#define HTC_LB_OCT_POUTLET_FLAG          (1<<5)
#define HTC_LB_OCT_VINLET_FLAG           (1<<6)
#define HTC_LB_OCT_WALL_FLAG             (1<<7)

#define HTC_FV_TO_LB 0
#define HTC_LB_TO_FV 1

#define HTC_LB_RGN_UNKNOWN    -3
#define HTC_LB_RGN_DEAD       -2
#define HTC_LB_RGN_INTERIOR   -1

#define HTC_LB_THREAD_FL_BAFFLE_FACE   THREAD_FL_MAJOR_FACE
#define HTC_LB_BAFFLE_FACE_THREAD_P(t) (THREAD_FLAGS(t) & HTC_LB_THREAD_FL_BAFFLE_FACE)

/*TODO: Remove when obsolete */
#define C_HTC_LB_VOF(c,t) C_STORAGE_R(c, t, SV_HTC_LB_VOF)
#define C_HTC_LB_BNDR(c,t) C_STORAGE_I(c, t, SV_HTC_LB_BNDR)
#define C_HTC_LB_POST(c,t) C_STORAGE_R(c, t, SV_HTC_LB_POST)

/**
 * @struct
 *   Lb_Bnd_Info
 * @brief
 *   Data to store info about boundaries affecting a cell for LB
 */
typedef struct lb_bnd_info_struct
{
  /** Normal vector from boundary to cell centroid */
  real m_normal[3];

  /** Area of this boundary affecting this cell */
  real m_area;

  /** Boundary Id */
  int m_bndId;

} Lb_Bnd_Info;

FLUENT_EXPORT cxboolean LbBndInfoManagerValid_P(void);
FLUENT_EXPORT Lb_Bnd_Info *GetLbBndInfo(size_t size);
FLUENT_EXPORT void AllocLbBndInfo(size_t size);
FLUENT_EXPORT void FreeLbBndInfo(void);

typedef struct lboctn_struct
{
   int nnbrs;
   int *nbr_pes;
   int *n_octs;
   int **oct_indices;
}lboct_n;

#define C_HTC_LB_CNTR_PRED(c,t) T_STORAGE(t, SV_HTC_LB_CNTR_PRED, uchar_fl*)[c]
#define C_HTC_LB_BNDR_CNT(c,t) T_STORAGE(t, SV_HTC_LB_BNDR_CNT, uchar_fl*)[c]
#define C_HTC_LB_BNDR_PTR(c,t) T_STORAGE(t, SV_HTC_LB_BNDR_PTR, Lb_Bnd_Info**)[c]

#define HTC_LB_CNTR_INOUT_MASK 0x3
#define HTC_LB_CELL_CUT_MASK 0x4
#define C_HTC_LB_CNTR_INSIDE(c,t) ((C_HTC_LB_CNTR_PRED(c,t) & HTC_LB_CNTR_INOUT_MASK) == 2)
#define C_HTC_LB_CNTR_OUTSIDE(c,t) ((C_HTC_LB_CNTR_PRED(c,t) & HTC_LB_CNTR_INOUT_MASK) == 0)
#define C_HTC_LB_CNTR_CUT(c,t) ((C_HTC_LB_CNTR_PRED(c,t) & HTC_LB_CNTR_INOUT_MASK) == 1)
#define C_HTC_LB_CELL_CUT(c,t) (C_HTC_LB_CNTR_PRED(c,t) & HTC_LB_CELL_CUT_MASK)

#define C_HTC_LB_OCT_FACES(c, t) C_STORAGE(c, t, SV_HTC_LB_OCT_FACES, Objp **)

#define C_HTC_LB_OCT_IDX(c,tc) ((int*)(&(C_STORAGE(c,tc,SV_HTC_LB_OCT,void**))))[0]
#define C_HTC_LB_OCT_LEVEL(c,tc) ((int*)(&(C_STORAGE(c,tc,SV_HTC_LB_OCT,void**))))[1]

#if RP_HTC

FLUENT_EXPORT double cellHtcCellVOF(cell_t, Thread *);
FLUENT_EXPORT double cellHtcCellBndr(cell_t, Thread *);
FLUENT_EXPORT cxboolean Lb_Cell_Function_P(const char *);
FLUENT_EXPORT double cellHtcLbPost(cell_t, Thread *);
FLUENT_EXPORT void   Fill_Lb_Post(Domain *, const char *);
FLUENT_EXPORT void   Fill_Lb_Post_Boundaries(const char *, int);
FLUENT_EXPORT void   Fill_Lb_Dead_Oct_Data(int);
FLUENT_EXPORT void   HTC_Fill_Lb_Svar_Boundaries(const char *, int);

FLUENT_EXPORT void   Model_Initialize_HTC_Lb(void);
FLUENT_EXPORT void   HTC_Acc_Lb_Shutdown(void);
FLUENT_EXPORT void   HTC_LB_Get_Domains(Domain **, Domain **);
FLUENT_EXPORT void   HTC_LB_Set_Domains(Domain *, Domain *);

#if RP_NODE
FLUENT_EXPORT int    HTC_LB_Get_Alignment(Thread *tf);
FLUENT_EXPORT void  *HTC_LB_Get_Boundary_Thread_List(Domain *, int, int *);
FLUENT_EXPORT void   HTC_LB_Free_Boundary_Thread_List(void *);
FLUENT_EXPORT void  *HTC_LB_Fill_Levels(Domain *, Domain *);
FLUENT_EXPORT void   HTC_LB_Free_Levels(void *);
FLUENT_EXPORT void   HTC_LB_Free_Oct_Faces(Domain *);
FLUENT_EXPORT int    HTC_LB_Get_Compute_Mode(void *);
FLUENT_EXPORT int    HTC_LB_Get_nlevels(void *);
FLUENT_EXPORT int   *HTC_LB_Get_nocts(void *);
FLUENT_EXPORT int    HTC_LB_Get_regions(void *, Thread ***);
FLUENT_EXPORT int    HTC_LB_Get_region_info_size(void *);
FLUENT_EXPORT void   HTC_LB_Swap_int_info(void *, lboct_n **);
FLUENT_EXPORT void   HTC_LB_Swap_ext_info(void *, lboct_n **);
FLUENT_EXPORT void   HTC_LB_Swap_ids(void *, cxindex ***);
FLUENT_EXPORT void   HTC_LB_Swap_parts(void *, int ***);
FLUENT_EXPORT void   HTC_LB_Swap_flags(void *, unsigned int ***);
FLUENT_EXPORT void   HTC_LB_Swap_cells(void *, Cell ****);
FLUENT_EXPORT void   HTC_LB_Swap_parents(void *, int ***);
FLUENT_EXPORT void   HTC_LB_Swap_children(void *, int ***);
FLUENT_EXPORT void   HTC_LB_Swap_neighbors_idx(void *, int ***);
FLUENT_EXPORT void   HTC_LB_Swap_neighbors_level(void *, char ***);
FLUENT_EXPORT void   HTC_LB_Swap_region_idx(void *, char ***);
FLUENT_EXPORT void   HTC_LB_Swap_region_info(void *, region_info_t **);
FLUENT_EXPORT void   HTC_LB_Swap_region_cnt(void *, char ***);
FLUENT_EXPORT void   HTC_LB_Swap_region_info_idx(void *, int ***);
FLUENT_EXPORT void   HTC_LB_Swap_vof(void *, real ***);
FLUENT_EXPORT int    HTC_LB_Is_Orig_Boundary_Id(int threadId);
FLUENT_EXPORT void   HTC_LB_Print_Original_Boundaries(void);
FLUENT_EXPORT void   HTC_LB_Print_Boundary_Statistics(void);
FLUENT_EXPORT void   HTC_LB_Set_Monitor_Data(const char *name, real val);
FLUENT_EXPORT void   HTC_LB_Set_Openmp_Num_Threads(int nthreads);
FLUENT_EXPORT cxboolean HTC_LB_Domain_Has_Baffles_P(Domain *ds);

#endif

#endif

#endif
