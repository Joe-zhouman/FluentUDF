#ifndef _FLUENT_UTIL_LOOSE_OCTREE_H
#define _FLUENT_UTIL_LOOSE_OCTREE_H

/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#include "global.h"
#include "mem.h"

/**
 * @addtogroup loose_octree Loose Octree for arbitrary elements
 * @{
 * @file
 * routines for using the octree-based localization method
 */

/* always search in 3 dimensions */
#define OCTREE_DIM ND_ND

#define LOOSE_OCTREE_STORE_BBOX 1

typedef real octree_rcoord[OCTREE_DIM];

/* bounding box */
typedef struct
{
  octree_rcoord lower;
  octree_rcoord upper;
} octree_rbbox;

typedef unsigned int octree_i;

/* spatial coordinate */
typedef octree_i octree_icoord[OCTREE_DIM];

/* bounding box */
typedef struct
{
  octree_icoord lower;
  octree_icoord upper;
} octree_ibbox;

typedef struct octree_element_s
{
  struct octree_element_s *next;
#if LOOSE_OCTREE_STORE_BBOX
  octree_ibbox ibbox;
#endif
} octree_element_t;

typedef enum
{
  OT_FILL_PRL_DATA,
  OT_COMPUTE_WEIGHTS
} ot_create_suboctant_mode;

typedef struct ot_parallel_element_s
{
  struct ot_parallel_element_s *next;
  void *element;
} ot_parallel_element_t;

/* forward decls for loose_octree.c */
struct octree_s;
struct octree_walker_s;

FLUENT_EXPORT void octree_add_one_element(struct octree_s *ot, void *element, const octree_rbbox *rbbox, struct octree_walker_s *octree_walker, int mode, int from_other_node);
FLUENT_EXPORT void rbbox_init(octree_rbbox *rbbox);
FLUENT_EXPORT void rbbox_add_box(octree_rbbox *rbbox, octree_rcoord box_lower, octree_rcoord box_upper);
FLUENT_EXPORT void rbbox_sphere(octree_rbbox *rbbox, real center[], real radius);

FLUENT_EXPORT  int octree_rbbox_coordinate(const struct octree_s *ot, const octree_rbbox *rbbox, octree_icoord icenter);
typedef void (* octree_generate_fn) (struct octree_s *ot, struct octree_walker_s *walker, void *storage, void *elements, int from_other_node);
FLUENT_EXPORT void octree_add_elements(struct octree_s *ot, void *storage, void *elements, octree_generate_fn generate, int from_other_node);
FLUENT_EXPORT void get_global_extents(octree_rbbox *rbbox);
FLUENT_EXPORT void make_rbbox_cubic(octree_rbbox *rbbox);
FLUENT_EXPORT octree_i octree_icoord_abs(const struct octree_s *ot, real rcoord, int dim);
FLUENT_EXPORT cxboolean octree_intersect_box(struct octree_s *ot,
                                             const octree_ibbox *ibbox,
                                             cxboolean (* fn) (void *, void *), void *param);
FLUENT_EXPORT cxboolean octree_intersect_rbbox(struct octree_s *ot,
                                               const octree_rbbox *rbbox,
                                               cxboolean (* fn) (void *, void *), void *param);

#if RP_NODE
FLUENT_EXPORT void create_oct_mgmt_data_hash_table(void);
FLUENT_EXPORT void free_oct_mgmt_data_hash_table(void);

struct exchange_param_s;
FLUENT_EXPORT void octree_create_valid_neighbors(Domain *d, struct octree_s *ot);
FLUENT_EXPORT void octree_exchange_parallel_elements(struct octree_s *ot,
                                                     void *storage,
                                                     octree_generate_fn generate,
                                                     struct exchange_param_s *ex_param,
                                                     Domain *d,
                                                     void *element_param,
                                                     void **pl);

#endif /* RP_NODE */
/**
 * @returns pointer to new octree
 */
FLUENT_EXPORT struct octree_s *New_Octree(octree_rbbox *);

FLUENT_EXPORT void Delete_Octree(struct octree_s **);

FLUENT_EXPORT struct octree_s *Create_Octree_On_Fluid_Cells(void);

FLUENT_EXPORT void Remove_Octree_On_Fluid_Cells(void);

FLUENT_EXPORT cxboolean Fluid_Cells_Locate_Point(real pos[3], cell_t *c, Thread **t);

FLUENT_EXPORT void print_oct_mgmt_data_ht(void);

/* @} losoe_octree */

#endif /* _FLUENT_UTIL_LOOSE_OCTREE_H */
