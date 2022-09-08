/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef MESH_ADAPTION_H
#define MESH_ADAPTION_H

/**
 * @file
 *   mesh_adaption.h
 * @brief
 *   Header file for mesh adaption functions
 */

#include "global.h"
#include "mem.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * @enum
 *   Adapt_Option
 * @brief
 *   Valid modes for mesh adaption
 */
typedef enum adapt_option_enum
{
  ADAPT_OPTION_HANG  = 0,
  ADAPT_OPTION_2D    = 1,
  ADAPT_OPTION_3D    = 2,
  ADAPT_OPTION_INVALID
} Adapt_Option;

/**
 * @enum
 *   Adapt_History_Action
 * @brief
 *   Valid history action options
 */
typedef enum adapt_history_action_enum
{
  ADAPT_HISTORY_ACTION_APPLY_MOVE,
  ADAPT_HISTORY_ACTION_FETCH_MOVE,
  ADAPT_HISTORY_ACTION_APPLY_COPY,
  ADAPT_HISTORY_ACTION_FETCH_COPY,
  ADAPT_HISTORY_ACTION_GLOBALIZE,
  ADAPT_HISTORY_ACTION_LOCALIZE,
  ADAPT_HISTORY_ACTION_INVALID
} Adapt_History_Action;

/**
 * @struct
 *   Adapt_Data
 * @brief
 *   Data structure for mesh adaption options
 */
typedef struct adapt_data_struct
{
  /* Member data */

  /** Pointer to Fluent domain */
  Domain *m_domain;

  /** Face refinement history map */
  cxindex *m_faceHistoryMap;

  /** Size of the face refinement history map */
  size_t m_nFaceHistoryItems;

  /** Cell refinement history map */
  cxindex *m_cellHistoryMap;

  /** Size of the cell refinement history map */
  size_t m_nCellHistoryItems;

  /** Allocation flag */
  int m_alloc;

  /** Adaption validity check */
  int m_valid;

  /** Anisotropy flag */
  int m_anisotropy;

  /** Flag to determine global history */
  cxboolean m_global;

  /** Adaption option */
  Adapt_Option m_option;

  /** Mesh data output name */
  const char *m_output_name;

  /** Mesh data output type */
  const char *m_output_type;

} Adapt_Data;

/**
 * @struct
 *   Adapt_Criteria
 * @brief
 *   Data structure for adaption criteria filling options
 */
typedef struct adapt_criteria_struct
{
  /* Member data */

  /** Pointer to Fluent domain */
  Domain *m_domain;

  /** Criteria type */
  const char *m_type;

  /** Variable name */
  const char *m_name;

  /** Scaling option */
  int m_scale;

  /** Weighting factor */
  real m_weight;

  /** Sample count */
  size_t m_count;

  /** Global minimum */
  real m_minimum;

  /** Global maximum */
  real m_maximum;

  /** Global average */
  real m_average;

  /** Global standard deviation */
  real m_std_dev;

  /** Global variance */
  real m_variance;

  /** Minimum cell location */
  Cell *m_min_cell;

  /** Maximum cell location */
  Cell *m_max_cell;

  /** Host flag */
  cxboolean m_on_host;

  /** Zone scaling flag */
  cxboolean m_per_zone;

} Adapt_Criteria;

/**
 * @typedef
 *   Allow_Adapt_P
 * @brief
 *   Function pointer for adaption predicates
 */
typedef cxboolean (*Allow_Adapt_P)(cell_t, Thread *);

/* * * * * * * * * * * * * * * Macro Definitions * * * * * * * * * * * * * * */

#define I_REFINE_TYPE 0
#define N_REFINE_TYPE 1
#define T_REFINE_TYPE 2
#define OPTION_REFINE_BIT (1 << 0)
#define OPTION_COARSE_BIT (1 << 1)
#define OPTION_ADAPT_BITS (OPTION_REFINE_BIT | OPTION_COARSE_BIT)
#define CELL_ADAPTION_FLAGS (CELL_REFINE_FLAG | CELL_COARSE_FLAG)
#define ADAPT_OBJECT_ALLOCATED_P(t) SV_ALLOCATED_P_NEW(t, SV_ADAPT_OBJECT)
#define ADAPT_OBJECT_INITIALIZED_p(t) SV_INITIALIZED_P(t, SV_ADAPT_OBJECT)

#if RP_POLYHEDRA

#define SV_GLOBAL_PARENT SV_ID_TMP
#define REFINE_LEVEL_ALLOCATED_P(t) SV_ALLOCATED_P_NEW(t, SV_REFINE_LEVEL)
#define PARENT_INDEX_ALLOCATED_P(t) SV_ALLOCATED_P_NEW(t, SV_PARENT_INDEX)
#define REFINE_LEVEL_INITIALIZED_P(t) SV_INITIALIZED_P(t, SV_REFINE_LEVEL)
#define PARENT_INDEX_INITIALIZED_P(t) SV_INITIALIZED_P(t, SV_PARENT_INDEX)
#define GLOBAL_PARENT_ALLOCATED_P(t) SV_ALLOCATED_P_NEW(t, SV_GLOBAL_PARENT)

#define ADAPT_STR(t, sv, type) FAST_T_STORAGE(t, sv, type)
#define REFINE_LEVEL_STORE(i, t) (ADAPT_STR(t, SV_REFINE_LEVEL, int *)[i])
#define PARENT_INDEX_STORE(i, t) (ADAPT_STR(t, SV_PARENT_INDEX, cxindex *)[i])
#define GLOBAL_PARENT_STORE(i, t) (ADAPT_STR(t, SV_GLOBAL_PARENT, cxindex *)[i])

#define REFINE_SHIFT(type) (8 * type)
#define REFINE_MASK(type) (0xFF << REFINE_SHIFT(type))
#define EXTRACT_REFINE_LEVEL(s, type) \
  ((s & REFINE_MASK(type)) >> REFINE_SHIFT(type))
#define SET_ALL_REFINE_PACK_BITS(lv, value) \
  lv = (((lv) & ~0xFFFFFF) | value)
#define SET_REFINE_PACK_BITS(lv, type, value) \
  lv = ((lv) & ~REFINE_MASK(type)) | ((value) << REFINE_SHIFT(type))
#define SET_REFINE_LEVELS(i, t, value) \
  SET_ALL_REFINE_PACK_BITS(REFINE_LEVEL_STORE(i, t), value)
#define SET_REFINE_BITS(i, t, type, value) \
  SET_REFINE_PACK_BITS(REFINE_LEVEL_STORE(i, t), type, value)
#define EXTRACT_I_REFINE_LEVEL(s) EXTRACT_REFINE_LEVEL(s, I_REFINE_TYPE)
#define EXTRACT_N_REFINE_LEVEL(s) EXTRACT_REFINE_LEVEL(s, N_REFINE_TYPE)
#define EXTRACT_T_REFINE_LEVEL(s) EXTRACT_REFINE_LEVEL(s, T_REFINE_TYPE)
#define SET_I_REFINE_LEVEL(i, t, s) SET_REFINE_BITS(i, t, I_REFINE_TYPE, s)
#define SET_N_REFINE_LEVEL(i, t, s) SET_REFINE_BITS(i, t, N_REFINE_TYPE, s)
#define SET_T_REFINE_LEVEL(i, t, s) SET_REFINE_BITS(i, t, T_REFINE_TYPE, s)
#define I_REFINE_LEVEL(i, t) EXTRACT_I_REFINE_LEVEL(REFINE_LEVEL_STORE(i, t))
#define N_REFINE_LEVEL(i, t) EXTRACT_N_REFINE_LEVEL(REFINE_LEVEL_STORE(i, t))
#define T_REFINE_LEVEL(i, t) EXTRACT_T_REFINE_LEVEL(REFINE_LEVEL_STORE(i, t))

#define FACE_REFINE_LEVEL(f, t) I_REFINE_LEVEL(f, t)
#define CELL_REFINE_LEVEL(c, t) I_REFINE_LEVEL(c, t)
#define FACE_REFINE_INFO(f, t) REFINE_LEVEL_STORE(f, t)
#define CELL_REFINE_INFO(c, t) REFINE_LEVEL_STORE(c, t)
#define FACE_PARENT_INDEX(f, t) PARENT_INDEX_STORE(f, t)
#define CELL_PARENT_INDEX(c, t) PARENT_INDEX_STORE(c, t)
#define CELL_GLOBAL_PARENT(c, t) GLOBAL_PARENT_STORE(c, t)

#define SET_FACE_REFINE_LEVEL(f, t, s) SET_I_REFINE_LEVEL(f, t, s)
#define SET_CELL_REFINE_LEVEL(c, t, s) SET_I_REFINE_LEVEL(c, t, s)
#define SET_FACE_REFINE_LEVELS(f, t, s) SET_REFINE_LEVELS(f, t, s)
#define SET_CELL_REFINE_LEVELS(c, t, s) SET_REFINE_LEVELS(c, t, s)
#define SET_FACE_REFINE_INFO(f, t, s) FACE_REFINE_INFO(f, t) = (int)(s)
#define SET_CELL_REFINE_INFO(c, t, s) CELL_REFINE_INFO(c, t) = (int)(s)
#define SET_FACE_PARENT_INDEX(f, t, s) FACE_PARENT_INDEX(f, t) = (cxindex)(s)
#define SET_CELL_PARENT_INDEX(c, t, s) CELL_PARENT_INDEX(c, t) = (cxindex)(s)
#define SET_CELL_GLOBAL_PARENT(c, t, s) CELL_GLOBAL_PARENT(c, t) = (cxindex)(s)

#define NODE_REFINE_LEVEL(v) \
  I_REFINE_LEVEL(NODE_INDEX(v), NODE_THREAD(v))
#define FSP_REFINE_LEVEL(fsp) \
  I_REFINE_LEVEL(FSP_IDX(fsp), FSP_THREAD(fsp))
#define CSP_REFINE_LEVEL(csp) \
  I_REFINE_LEVEL(CSP_IDX(csp), CSP_THREAD(csp))
#define NODE_REFINE_INFO(v) \
  REFINE_LEVEL_STORE(NODE_INDEX(v), NODE_THREAD(v))
#define FSP_REFINE_INFO(fsp) \
  REFINE_LEVEL_STORE(FSP_IDX(fsp), FSP_THREAD(fsp))
#define CSP_REFINE_INFO(csp) \
  REFINE_LEVEL_STORE(CSP_IDX(csp), CSP_THREAD(csp))
#define FSP_PARENT_INDEX(fsp) \
  PARENT_INDEX_STORE(FSP_IDX(fsp), FSP_THREAD(fsp))
#define CSP_PARENT_INDEX(csp) \
  PARENT_INDEX_STORE(CSP_IDX(csp), CSP_THREAD(csp))
#define CSP_GLOBAL_PARENT(csp) \
  GLOBAL_PARENT_STORE(CSP_IDX(csp), CSP_THREAD(csp))

#define SET_NODE_REFINE_LEVEL(v, s) \
  SET_I_REFINE_LEVEL(NODE_INDEX(v), NODE_THREAD(v), s)
#define SET_FSP_REFINE_LEVEL(fsp, s) \
  SET_I_REFINE_LEVEL(FSP_IDX(fsp), FSP_THREAD(fsp), s)
#define SET_CSP_REFINE_LEVEL(csp, s) \
  SET_I_REFINE_LEVEL(CSP_IDX(csp), CSP_THREAD(csp), s)
#define SET_NODE_REFINE_INFO(v, s) \
  NODE_REFINE_INFO(v) = (int)(s)
#define SET_FSP_REFINE_INFO(fsp, s) \
  SET_FACE_REFINE_INFO(FSP_IDX(fsp), FSP_THREAD(fsp), s)
#define SET_CSP_REFINE_INFO(csp, s) \
  SET_CELL_REFINE_INFO(CSP_IDX(csp), CSP_THREAD(csp), s)
#define SET_NODE_REFINE_LEVELS(v, s) \
  SET_REFINE_LEVELS(NODE_INDEX(v), NODE_THREAD(v), s)
#define SET_FSP_REFINE_LEVELS(fsp, s) \
  SET_REFINE_LEVELS(FSP_IDX(fsp), FSP_THREAD(fsp), s)
#define SET_CSP_REFINE_LEVELS(csp, s) \
  SET_REFINE_LEVELS(CSP_IDX(csp), CSP_THREAD(csp), s)
#define SET_FSP_PARENT_INDEX(fsp, s) \
  FSP_PARENT_INDEX(fsp) = (cxindex)(s)
#define SET_CSP_PARENT_INDEX(csp, s) \
  CSP_PARENT_INDEX(csp) = (cxindex)(s)
#define SET_CSP_GLOBAL_PARENT(csp, s) \
  CSP_GLOBAL_PARENT(csp) = (cxindex)(s)

#define NODE_REFINE_LEVEL_STORE(v) \
  REFINE_LEVEL_STORE(NODE_INDEX(v), NODE_THREAD(v))
#define FSP_REFINE_LEVEL_STORE(fsp) \
  REFINE_LEVEL_STORE(FSP_IDX(fsp), FSP_THREAD(fsp))
#define CSP_REFINE_LEVEL_STORE(csp) \
  REFINE_LEVEL_STORE(CSP_IDX(csp), CSP_THREAD(csp))

#else

#define EMPTY_ASSIGNMENT do {} while (0)
#define GLOBAL_PARENT_ALLOCATED_P(t) FALSE
#define REFINE_LEVEL_ALLOCATED_P(t) FALSE
#define PARENT_INDEX_ALLOCATED_P(t) FALSE
#define REFINE_LEVEL_INITIALIZED_P(t) FALSE
#define PARENT_INDEX_INITIALIZED_P(t) FALSE
#define NODE_REFINE_INFO(v) 0
#define NODE_REFINE_LEVEL(v) 0
#define FACE_REFINE_INFO(f, t) 0
#define CELL_REFINE_INFO(c, t) 0
#define FACE_REFINE_LEVEL(f, t) 0
#define CELL_REFINE_LEVEL(c, t) 0
#define FACE_PARENT_INDEX(f, t) 0
#define CELL_PARENT_INDEX(c, t) 0
#define CELL_GLOBAL_PARENT(c, t) 0
#define REFINE_LEVEL_STORE(i, t) 0
#define PARENT_INDEX_STORE(i, t) 0
#define EXTRACT_REFINE_LEVEL(s, type) 0
#define SET_NODE_REFINE_INFO(v, s) EMPTY_ASSIGNMENT
#define SET_NODE_REFINE_LEVEL(v, s) EMPTY_ASSIGNMENT
#define SET_FACE_REFINE_INFO(f, t, s) EMPTY_ASSIGNMENT
#define SET_CELL_REFINE_INFO(c, t, s) EMPTY_ASSIGNMENT
#define SET_FACE_REFINE_LEVEL(f, t, s) EMPTY_ASSIGNMENT
#define SET_CELL_REFINE_LEVEL(c, t, s) EMPTY_ASSIGNMENT
#define SET_FACE_PARENT_INDEX(f, t, s) EMPTY_ASSIGNMENT
#define SET_CELL_PARENT_INDEX(c, t, s) EMPTY_ASSIGNMENT
#define SET_CELL_GLOBAL_PARENT(c, t, s) EMPTY_ASSIGNMENT
#define FSP_REFINE_INFO(fsp) 0
#define CSP_REFINE_INFO(csp) 0
#define FSP_REFINE_LEVEL(fsp) 0
#define CSP_REFINE_LEVEL(csp) 0
#define FSP_PARENT_INDEX(fsp) 0
#define CSP_PARENT_INDEX(csp) 0
#define CSP_GLOBAL_PARENT(csp) 0
#define SET_FSP_REFINE_INFO(fsp, s) EMPTY_ASSIGNMENT
#define SET_CSP_REFINE_INFO(csp, s) EMPTY_ASSIGNMENT
#define SET_FSP_REFINE_LEVEL(fsp, s) EMPTY_ASSIGNMENT
#define SET_CSP_REFINE_LEVEL(csp, s) EMPTY_ASSIGNMENT
#define SET_FSP_PARENT_INDEX(fsp, s) EMPTY_ASSIGNMENT
#define SET_CSP_PARENT_INDEX(csp, s) EMPTY_ASSIGNMENT
#define SET_CSP_GLOBAL_PARENT(csp, s) EMPTY_ASSIGNMENT

#endif

/* * * * * * * * * * * * Global Function Definitions * * * * * * * * * * * * */

FLUENT_EXPORT cxboolean MeshIsAdapted(void);
FLUENT_EXPORT size_t AdaptionObjectCount(void);
FLUENT_EXPORT cxboolean AdaptionHistoryIsGlobal(void);
FLUENT_EXPORT cxboolean AtDynamicAdaptionInterval(void);
FLUENT_EXPORT cxboolean IgnoreAdaptionObjectIntervals(const cxboolean);

FLUENT_EXPORT int AdaptionPredicateCount(void);
FLUENT_EXPORT const char *AdaptionPredicateString(const int);

FLUENT_EXPORT void AdaptFluentMesh(Adapt_Data *);
FLUENT_EXPORT void ApplyFluentMeshDelegate(Adapt_Data *, const char *);

FLUENT_EXPORT void AdaptTetMesh(Domain *);

FLUENT_EXPORT void InitAdaptPolyhedralMesh(void);
FLUENT_EXPORT void FreeAdaptPolyhedralMesh(void);
FLUENT_EXPORT void InitializeAdaptionStorage(void);
FLUENT_EXPORT void DynamicAdaptPolyhedralMesh(void);
FLUENT_EXPORT void InitializeAdaptionPrimitives(void);
FLUENT_EXPORT void RegisterPolyhedraAdaptionIOManagers(void);
FLUENT_EXPORT void MigrationForPolyhedraAdaption(const char *);
FLUENT_EXPORT void EncapsulationForPolyhedraAdaption(const char *);
FLUENT_EXPORT void WriteOutPolyhedraMeshData(const char *, const char *);
FLUENT_EXPORT void InvokeHistoryAction(Adapt_History_Action, Adapt_Data *);

FLUENT_EXPORT void CacheCellAdaptionFlags(Domain *);
FLUENT_EXPORT void RestoreCellAdaptionFlags(Domain *);
FLUENT_EXPORT void PrioritizeRefinementFlags(Domain *);
FLUENT_EXPORT void LimitCellVolumeRefinement(Domain *);
FLUENT_EXPORT void SetManualAdaptionMode(const cxboolean);
FLUENT_EXPORT void FillAdaptionCriterion(Adapt_Criteria *);
FLUENT_EXPORT void GetMultiLayerAdaptionOption(const char *, void *);
FLUENT_EXPORT void SetCellAdaptionFlag(Domain *, const unsigned int);
FLUENT_EXPORT void ClearCellAdaptionFlags(Domain *, const unsigned int);
FLUENT_EXPORT void WriteCellAdaptionFlags(Domain *, const unsigned int);
FLUENT_EXPORT void ApplyAdaptionPredicate(const unsigned int, Allow_Adapt_P);
FLUENT_EXPORT void ClearAdaptionPredicate(const unsigned int, Allow_Adapt_P);
FLUENT_EXPORT void CountAdaptionFlags(Domain *, const unsigned int, size_t *);
FLUENT_EXPORT void ExtendMarkingWithSecurityLayer(Domain *, const unsigned int);

FLUENT_EXPORT void AllocateAdaptionObjects(Domain *);
FLUENT_EXPORT void DeallocateAdaptionObjects(Domain *);
FLUENT_EXPORT void SetDynamicAdaptionInterval(const int);
FLUENT_EXPORT void RegisterAdaptionObject(const char *, void **);
FLUENT_EXPORT void DeregisterAdaptionObject(const char *);
FLUENT_EXPORT void InitExteriorAdaptionObjects(Domain *);
FLUENT_EXPORT void FreeExteriorAdaptionObjects(Domain *);
FLUENT_EXPORT void GetCellRefineType(cell_t, Thread *, int *);
FLUENT_EXPORT void MapAdaptionObjects(cell_t *, Thread **, int,
                                      cell_t *, Thread **, int);

FLUENT_EXPORT void GetAdaptionObjectForMigration(cell_t, Thread *, cxindex *);
FLUENT_EXPORT void SetAdaptionObjectForMigration(cell_t, Thread *, cxindex *);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#endif /* MESH_ADAPTION_H */

/*****************************************************************************/
