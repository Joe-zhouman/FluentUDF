/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef OCTREE_MESHER_WRAPPER_H
#define OCTREE_MESHER_WRAPPER_H

/**
 * @file
 *   octree_mesher.h
 * @brief
 *   Header file for octree mesher functions
 */

#include "stddef.h"

#include "dll.h"

///maximum length of zone names
#ifndef M_OCTREE_MAX_ZONE_NAME_LENGTH
#define M_OCTREE_MAX_ZONE_NAME_LENGTH 256
#endif

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * @enum
 *   Octree_Mode
 * @brief
 *   Valid modes for octree mesher
 */
typedef enum octree_mode_enum
{
  OCTREE_MODE_TGRID  = 0,
  OCTREE_MODE_FLUENT = 1,
  OCTREE_MODE_INVALID
} Octree_Mode;

/**
 * @struct
 *   octree_mesher_geo_zone_info
 * @brief
 *   Stores basic information for each surface zone in boundary geometry
 */
typedef struct octree_mesher_geo_zone_info
{
  /** Boundary zone ID */
  int m_id;

  /** Name of surface zone */
  char *m_name;

  /** Pointer to thread */
  void *m_thread;

  /** Number of facets in face zone */
  double m_nFacets;

  /** Area of surface zone */
  double m_area;

  /** Average triangle area of surface zone */
  double m_avgArea;

  /** Average triangle edge length of surface zone */
  double m_avgLength;

  /** Bounding box of surface zone */
  double m_xMin[3], m_xMax[3];

} Octree_Geo_Zone_Info;

/**
 * @struct
 *   Octree_Mesh_Zone
 * @brief
 *   Data structure for octree mesh zones
 */
typedef struct octree_mesh_zone_struct
{
  /* Member data */

  /** Boundary zone ID */
  int m_id;

  /** Pointer to thread */
  void *m_thread;

  /** Boundary mesh size */
  double m_meshSize;

  /** Flag if the base mesh size should take facetting into account */
  double m_facetRefinementLimit;

  /** External boundary orientation / baffle */
  int m_orientation;

  /** Number of constant size boundary layers */
  int m_bndLayers;

  /** Angle for feature refinement in degree */
  double m_ref_angle;

  /** Number of refinement steps for surface zone */
  int m_num_angle_refinements;

  /** Surface area of zone */
  double m_area;

  /** Pointer to next zone */
  struct octree_mesh_zone_struct *m_next;

} Octree_Mesh_Zone;


/**
 * @struct
 *   Octree_Cell_Zone
 * @brief
 *   Data structure for octree cell zones
 */
typedef struct octree_cell_zone_struct
{
  /* Member data */

  /** Cell zone thread ID */
  int m_id;

  /** Pointer to thread */
  void *m_thread;

  /** cell zone name */
  char m_name[M_OCTREE_MAX_ZONE_NAME_LENGTH];

  /** pointer to associated surface zone IDs */
  int *m_surfZoneIds;

  /** material point of cell zone */
  double m_matPt[3];

  /** Pointer to next zone */
  struct octree_cell_zone_struct *m_next;

} Octree_Cell_Zone;


/**
 * @struct
 *   Octree_Refine_Box
 * @brief
 *   Data structure for octree refinement boxes
 */
typedef struct octree_refine_box_struct
{
  /* Member data */

  /** Mesh size in refinement box */
  double m_meshSize;

  /** Bounding box of refinement region */
  double m_xMin[3], m_xMax[3];

  /** Pointer to next zone */
  struct octree_refine_box_struct *m_next;

} Octree_Refine_Box;

typedef struct bnd_projection_prism_info
{
  /** Number of prisms for the configured boundary zone Ids */
  int m_numPrisms;

  /** Mode for prism Layer generation 0: first layer height, 1: aspect*/
  int m_mode;

  /** first prism layer height */
  double m_firstLayerHeight;

  /** first prism layer aspect ratio */
  double m_aspectRatio;

  /**automatic configuration of aspect ratio */
  int m_isAutoAspect;

  /** growth rate for layer */
  double m_growthRate;

  /**automatic configuration of growth rate */
  int m_isAutoGrowthRate;

  /** expansion factor for prismatic layers */
  double m_prismExpansionRatio;

  /**automatic configuration of expansion */
  int m_isAutoExpansionRatio;

  /** List of boundary zone ids */
  int m_prismRegion;

  /** pointer to next prism config */
  struct bnd_projection_prism_info *m_next;

} Bnd_Projection_Prism_Info;

/**
 * @struct
 *   Bnd_Projection_Params
 * @brief
 *   Data structure for parameters used in boundary projection
 */
typedef struct bnd_projection_params_struct
{
  /* Member data */

  /** Computation scheme for PseudoNormals */
  int m_pseudoNormalMode;

  /** factor for distance based erosion (fraction of octant length) */
  double m_distErosionFactor;

  /** maximum number of iterations for inflection point removal */
  int m_maxInflectionPointIterations;

  /** ignore skewed cells beyond this limit in aspect ratio improvement */
  double m_improveAspectQualityLimit;

  /** set target cell skewness in domain */
  double m_targetMaxCellSkew;

  /** mesh optimization mode */
  int m_optimizationMode;

  /** activate improved feature resolution */
  int m_doFeatureProjection;

  /** prism layer expansion methods */
  int m_prismExpansionMode;

  /** expansion factor for prismatic layers */
  double m_prismExpansionRatio;

  /** number of layer threshold for prism expansion */
  int m_prismExpansionNumLayerThreshold;

  /** list of prism regions */
  Bnd_Projection_Prism_Info *m_prismRegions;

} Bnd_Projection_Params;

/**
 * @struct
 *   Octree_Mesher_Data
 * @brief
 *   Data structure for octree mesher options
 */
typedef struct octree_mesher_struct
{
  /* Member data */

  /** Pointer to domain */
  void *m_domain;

  /** Pointer to faceted geometry */
  void *m_geom;

  /** Pointer to octree */
  void *m_octree;

  /** Pointer to Cartesian boundary snapper */
  void *m_snapperCart;

  /** Pointer to normal boundary snapper */
  void *m_snapperNormal;

  /** Pointer to octree snap-Cartesian mesher */
  void *m_octreeSnapCartMesher;

  /** Pointer to octree snap-normal mesher */
  void *m_octreeSnapNormalMesher;

  /** Debug level */
  int m_debug;

  /** Octree mesher mode */
  Octree_Mode m_mode;

  /** Flag to activate parallel geometry treatment (temporary) */
  int m_isGeoParallel;

  /** Flag to activate HTC LB mode */
  int m_htcLBM;

  /** Optionally map solution fields */
  int m_mapping;

  /** Optionally extract hierarchy */
  int m_hierarchy;

  /** Optionally extract volume fractions */
  int m_fractions;

  /** Optionally encapsulate cells */
  int m_encapsulate;

  /** Optionally separate Cartesian/non-Cartesian cell/face threads */
  int m_separateCart;

  /** Optionally clear volume mesh */
  int m_clearVolMesh;

  /** Optionally map surfaces to volume octants */
  int m_mapSurfaceToOct;

  /** Bounding box extension factor during mapping */
  double m_extendFactor;

  /** Geometry parameters */

  /** Point count */
  size_t m_nPoints;

  /** Facet count */
  size_t m_nFacets;

  /** Pointer to points array */
  double *m_points;

  /** Pointer to point IDs array */
  size_t *m_pointId;

  /** Pointer to facets array */
  size_t *m_facets;

  /** Pointer to zone IDs array */
  int *m_zoneId;

  /** Optional pre-defined cell zone ID */
  int m_czId;

  /** Optionally snap to boundary geometry */
  int m_snap;

  /** In case of m_snap: normal projection? (else Cartesian projection) */
  int m_snapNormal;

  /** Optionally invert geometry */
  int m_invert;

  /** Optionally specify absolute extents */
  int m_absolute;

  /** Optionally specify relative extents */
  int m_relative;

  /** LBM Boundary priority list */
  int *m_LbmBndPriority;

  /** LBM Boundary priority list size */
  int m_LbmBndPriorityCount;

  /** LBM store mode ID for closest point computation */
  int m_LbmClosestPtMode;

  /** Bounding box zone IDs */
  int m_boxZoneIds[6];

  /** flag to control name of boxes (0:auto,1:fixes) */
  int m_rename_box_threads;

  /** Boundary face zone count */
  size_t m_boundaryCount;

  /** Boundary face zone IDs */
  Octree_Mesh_Zone *m_boundaryZones;

  /** Cell zone count */
  size_t m_cellZoneCount;

  /** Cell zone IDs (to be extended for more info)*/
  Octree_Cell_Zone *m_cellZones;

  /** vector of boundary priority regions for boundary conforming mesh*/
  int *m_priorityRegions;

  /** number of priority regions for boundary conforming mesh */
  size_t m_numPriorityRegions;

  /** Boundary box of all geometry face zones */
  double m_bMin[3], m_bMax[3];

  /** User specified min / max for absolute / relative options */
  double m_xMin[3], m_xMax[3];

  /** Refinement box count */
  size_t m_refineBoxCount;

  /** Refinement boxes */
  Octree_Refine_Box *m_refineBoxes;

  /** Pointer to partitions array */
  size_t *m_partitions;

  /** Mesh generation parameters */

  /** Global mesh scale */
  double m_scale;

  /** Global geometry offset */
  double m_offset[3];

  /** Global bounding box extent */
  double m_extent[3];

  /** Global bounding box mesh size */
  double m_meshSize;

  /** Number of refinement steps */
  size_t m_nRefSteps;

  /** Flag hinting if geometry is manifold or not */
  int m_isManifoldGeo;

  /** mode of flow volume determination corresponds to FluxIncludes.hpp enum
   * MPT_OPT_COORDINATE = 0,           // material point coordinates are given
   * MPT_OPT_EXTERIOR = 1,             // exterior flow is bounded by box
   * MPT_OPT_INTERIOR = 2,             // flow volume is entirely bounded by geometry
   * MPT_OPT_ALL_CELLS = 3,            // developer only: activate the old behavior
   * MPT_OPT_RESPECT_INVERT_FLAG = 4   // developer only: activate the old behavior
   */
  int m_matPtMode;

  /** material point for flow volume determination */
  double m_matPt[3];

  /** Storage for configurable parameters in boundary projection scheme */
  Bnd_Projection_Params *m_bndProjectionParams;

  /** mode for cell count estimation */
  int m_cellEstLevel;

  /** estimated number of cells, filled if dry run is selected */
  int m_estCellCount;

  /** flag to specify whether to agglomerate mesh to node_zero */
  int m_aggNodeZero;

} Octree_Mesher_Data;

/* * * * * * * * * * * * Global Function Definitions * * * * * * * * * * * * */

FLUENT_EXPORT void InitializeOctreeMesherPrimitives(void);
FLUENT_EXPORT void MapSurfaceToOctreeDomain(void *, void *);
FLUENT_EXPORT void PartitionOctreePointCloud(Octree_Mesher_Data *);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#endif /* OCTREE_MESHER_WRAPPER_H */

/*****************************************************************************/
