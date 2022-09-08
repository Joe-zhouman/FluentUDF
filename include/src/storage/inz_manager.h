/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/* 
 * File:   inz_manager.h
 * Author: agoublom
 *
 * Created on July 22, 2019
 */

#ifndef INZ_MANAGER_H
#define INZ_MANAGER_H

#include "dll.h"
#include "mem_grid.h"
/** MACROS **/
#if USE_FEMCORE
#define loop_interpolation_type(i) for (InterpolationType i = INTERP_BEGIN; i != N_INTERP_TYPE; ++i)

#define loop_inz_all_access(i) for (InzObjectAccessType i = INZACC_BEGIN; i != INZACC_END; ++i)
#define loop_inz_first_access(i) for (InzObjectAccessType i = INZACC_N_BEGIN; i != INZACC_N_END; ++i)
#define loop_inz_N_access(i) for (InzObjectAccessType i = INZACC_N_BEGIN; i != INZACC_N_END; ++i)
#define loop_inz_P0_access(i) for (InzObjectAccessType i = INZACC__P0_BEGIN; i != INZACC_P0_END; ++i)
#define loop_inz_P0_Ext_access(i) for (InzObjectAccessType i = INZACC_P0_EXT_BEGIN; i != INZACC_P0_EXT_END; ++i)
#endif
#define INTERP_NAME_LENGTH 50
#define CASE_CELL_THREAD_ALLOWED_FOR_INTERPOLATION_NODES case THREAD_C_GENERIC:
#define CASE_FACE_THREAD_ALLOWED_FOR_INTERPOLATION_NODES  \
  case THREAD_F_WALL:                                     \
  case THREAD_F_INTERIOR:
#define THREAD_INTERP_NODES(t,interp) (t)->element_interpolation_nodes_manager[interp]

#define FREE_THREAD_INTERPOLATION_NODES(t,interp)                                \
  if ( NNULLP(THREAD_INTERP_NODES(t,interp)))                                    \
    Free_Memory_Manager(&THREAD_INTERP_NODES(t,interp))

#ifdef __cplusplus
extern "C"
{
#endif
#if USE_FEMCORE
/* Interpolation types */
typedef enum
{
  INTERP_UNDEFINED = -1,
  INTERP_BEGIN,
  INTERP_CONST_PER_ELEMENT=INTERP_BEGIN, /* 0 */
  INTERP_LINEAR,                         /* 1 */
  INTERP_SERENDIP,                       /* 2 */
  INTERP_QUADRATIC,                      /* 3 */
  N_INTERP_TYPE
} InterpolationType;

typedef enum inz_creation_mode
{
  INZ_Create_Non = 0,
  INZ_Create_For_All,
  INZ_Create_For_Solid
} INZ_Creation_Mode;
/* For the cnz, the equivalent of the following structure is defined in mem.h. */
typedef struct inz_manager_struct
{
  int mode;                                 /* created mode, all or solid only */
  int grid_id;                              /* saved grid id */
  int case_id;                              /* saved case id */
  struct thread_struct *cinz;               /* cell interpolation nodes zone */
  struct thread_struct *finz;               /* face interpolation nodes zone */
} inz_manager_t;

typedef enum
{
/* _N_<object type> is related to the number of interpolation nodes of <object type>.
 * _P0_<object type> is related to the position of first of interpolation nodes of <object type>.
 * _P0_EXT_ <object type> is related to the position of first of interpolation nodes of external <object type>.
 +*/                                           /* ALL      !RP_EDGE      !RP_NODE       !RP_EGDE&&!RP_NODE  */
  INZACC_BEGIN = 0,                            /*  0           0            0                   0           */
  INZACC_N_BEGIN = INZACC_BEGIN,               /*  0           0            0                   0           */
  INZACC_N_VERTICES = INZACC_N_BEGIN,          /*  0           0            0                   0           */
#if RP_EDGE
  INZACC_N_EDGES,                              /*  1                        1                               */
#endif
  INZACC_N_FACES,                              /*  2           1            2                   1           */
  INZACC_N_CELLS,                              /*  3           2            3                   2           */
  INZACC_N_END,                                /*  4           3            4                   3           */
  INZACC_P0_BEGIN = INZACC_N_END,              /*  4           3            4                   3           */
  INZACC_PO_VERTEX = INZACC_P0_BEGIN,          /*  4           3            4                   3           */
#if RP_EDGE
  INZACC_P0_EDGES,                             /*  5                        5                               */
#endif
  INZACC_P0_FACES,                             /*  6           4            6                   4           */
  INZACC_P0_CELLS,                             /*  7           5            7                   5           */
  INZACC_P0_END,                               /*  8           6            8                   6           */
#if RP_NODE
  INZACC_P0_EXT_BEGIN = INZACC_P0_END,         /*  8           6                                            */
  INZACC_PO_EXT_VERTEX = INZACC_P0_EXT_BEGIN,  /*  8           6                                            */
#if RP_EDGE
  INZACC_P0_EXT_EDGES,                         /*  9                                                        */
#endif
  INZACC_P0_EXT_FACES,                         /* 10           7                                            */
  INZACC_P0_EXT_CELLS,                         /* 11           8                                            */
  INZACC_P0_EXT_END,                           /* 12           9                                            */
  INZACC_END = INZACC_P0_EXT_END               /* 12           9                                            */
#else
  INZACC_END = INZACC_P0_END                   /*  8           6                                            */
#endif
} InzObjectAccessType;
typedef struct inz_object_access_struct
{
  InterpolationType interp;                /* saved interpolation type */
  cxindex access[INZACC_END];
} InzObjectAccess;

/* return 1 success, 0 failed */
FLUENT_EXPORT int Create_Interpolation_Nodal_Threads_As_Needed(Domain* domain, InterpolationType interp, int creation_mode, cxboolean with_host);
/* return 1 success, 0 failed */
FLUENT_EXPORT int Create_Interpolation_Nodal_Threads(Domain* domain, InterpolationType interp, int creation_mode, cxboolean with_host);
/* return 1 success, 0 failed */
FLUENT_EXPORT int Free_All_Interpolation_Nodal_Threads(Domain* domain, cxboolean with_host);
FLUENT_EXPORT int Test_Interpolation_Nodal_Threads(Domain* domain, int creation_mode, cxboolean with_host);
FLUENT_EXPORT void Model_Initialize_fem_interpolation_nodes(void);
#endif

#ifdef __cplusplus
}
#endif
#endif  /* INZ_MANAGER_H */
