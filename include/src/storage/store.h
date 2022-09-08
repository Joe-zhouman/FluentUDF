/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_STORE_H
#define _FLUENT_STORE_H

#include "dll.h"

typedef struct memory_block_struct
{
  void *b;  /* Pointer to memory block */
  int n;  /* Number of elements in block */
} MemoryBlock;


struct store_struct
{
  void *_data;
  size_t _nbytes;
  int _dimension;
  void *_link; /* fluent attaches thread tuple here */
#if 1 /* remove once tuple complete */
  int n_allocd;
  int max_n_allocd;
#endif
  int _init;
  struct variable_attribute_struct *sv;
  struct store_struct *next;
  struct store_struct **prev;
  unsigned int flags;  /* used to tag storage obj for migration etc */
  struct domain_struct *domain;
};
typedef struct store_struct Store;

FLUENT_EXPORT void *ST_Malloc(size_t, size_t *, struct domain_struct *);
FLUENT_EXPORT void *ST_Realloc(void *, size_t, size_t *, struct domain_struct *);
FLUENT_EXPORT void ST_Free(void **);
FLUENT_EXPORT void ST_Set_First_Store(Store *s, struct domain_struct *);
FLUENT_EXPORT Store *ST_First_Store(struct domain_struct *);
FLUENT_EXPORT Store *ST_Create_Store(size_t, size_t *, int, struct domain_struct *);
FLUENT_EXPORT Store *ST_Resize_Store(Store *, size_t, size_t *, int, struct domain_struct *);
FLUENT_EXPORT void ST_Free_Store_Data(Store *, struct domain_struct *);
FLUENT_EXPORT void ST_Delete_Store(Store **s, struct domain_struct *);
FLUENT_EXPORT void ST_Free_And_Delete_All_Stores(struct domain_struct *);
FLUENT_EXPORT void ST_Store_Usage(int *, size_t *, size_t *, struct domain_struct *);
FLUENT_EXPORT void ST_Store_Check_Inconsistency(struct domain_struct *);

FLUENT_EXPORT void Reset_All_Storage_Flags(struct domain_struct *);
FLUENT_EXPORT void Reset_All_Storage_Tag_Flag(struct domain_struct *);

#define ST_STORE_DATA_NBYTES(s) ((s)->_nbytes)
#define ST_STORE_DATA(s) ((s)->_data)
#define ST_STORE_LINK(s) ((s)->_link)
#define ST_STORE_INIT_P(s) ((s)->_init)
#define ST_STORE_DIMENSION(s) ((s)->_dimension)

#define STORAGE_FLAGS(s) s->flags
#define STORAGE_TAG_FLAG (1)
/*
 * not sure if other bits are used for other purpose, here just use the 31st bit.
 */
#define STORAGE_TEMPORARY_FOR_IO_FLAG (1<<31)

#define STORAGE_FLAG_P(s,flags) (STORAGE_FLAGS(s) & flags)
#define SET_STORAGE_FLAGS(s,flags) (STORAGE_FLAGS(s) |= flags)
#define CLEAR_STORAGE_FLAGS(s,flags) (STORAGE_FLAGS(s) &= ~flags)

#define STORAGE_TAG_P(s) (STORAGE_FLAG_P(s,STORAGE_TAG_FLAG))
#define CLEAR_STORAGE_TAG_FLAG(s) (CLEAR_STORAGE_FLAGS(s,STORAGE_TAG_FLAG))
#define SET_STORAGE_TAG_FLAG(s) (SET_STORAGE_FLAGS(s,STORAGE_TAG_FLAG))
#define CLEAR_STORAGE_TEMPORARY_IO_FLAG(s) (CLEAR_STORAGE_FLAGS(s,STORAGE_TEMPORARY_FOR_IO_FLAG))
#define SET_STORAGE_TEMPORARY_IO_FLAG(s) (SET_STORAGE_FLAGS(s,STORAGE_TEMPORARY_FOR_IO_FLAG))
#define TEMPORARY_STORAGE_FOR_IO(s) STORAGE_FLAG_P(s,STORAGE_TEMPORARY_FOR_IO_FLAG)

#define ST_ALLOC_FACTOR 0.1

#if RP_TOUCH_MEMORY
extern FLUENT_EXPORT unsigned char touch_value;
#endif /* RP_TOUCH_MEMORY */



/********************************************************

 * move certain global or static variables under domain
 * to make it possible to create multiple domains, for
 * the purpose of seperate DPM domain,
 * or harmonic simulations
 *
 * could put this in a serperate file

 *******************************************************/

#ifndef USE_DOMAIN_DATA_MANAGER
#define USE_DOMAIN_DATA_MANAGER 1
#endif /* USE_DOMAIN_DATA_MANAGER */

typedef struct multiple_shadow_node_t msn_t;
typedef struct pair_if_t_ pair_if_t;
typedef struct multiple_shadow_node_pair_t msn_pair_t;

typedef struct msn_data_manager_t_
{
  int has_msn_p;
  int grid_id;
  int neighborhood_id;
  cxindex vid_start;
  int nmsn;
  int nmsn_pairc;
  int nmsn_pairf;
  int nif_pair;

  msn_t *msn;
  pair_if_t *if_pair;
  msn_pair_t *msn_pairc;
  msn_pair_t *msn_pairf;
  cxboolean recover_msn;
  cxboolean add_msn_iface_corner;
} msn_data_manager_t;

typedef struct domain_store_manager_t_
{
  /* store */
  struct store_struct *root_store;
  size_t st_nbytes_in_heap;
  int stores_per_alloc;
  int stores_in_dump;
  int stores_used;
  struct store_struct *store_dump;
  struct memory_block_struct *store_block;
  int nstore_blocks;
  int store_block_size;
  int store_block_per_alloc;
} domain_store_manager_t;

typedef struct domain_tuple_manager_t_
{
  /* tuple */
  struct tuple_struct *root_tuple;
  int tuples_per_alloc;
  int tuples_in_dump;
  int tuples_used;
  struct tuple_struct *tuple_dump;
  struct memory_block_struct *tuple_block;
  int ntuple_blocks;
  int tuple_block_size;
  int tuple_block_per_alloc;
} domain_tuple_manager_t;

typedef struct domain_node_manager_t_
{
  /* node */
  Node *node_list;
  int nodes_in_dump;
  int nodes_used;
  struct node_block_struct *node_block; /* Array of pointers to node blocks. */
  int nnode_blocks; /* Number of node block entries used. */
  int node_block_size;  /* Number of node block entries allocated. */
} domain_node_manager_t;

/* Placeholder for domain related identifiers (IDs) */
typedef struct identifier_data_manager_t_
{
  int neighborhood_id;
  int grid_id;
} identifier_data_manager_t;

/* Forward declaration; Defined in para.c */
typedef struct map_id_struct map_id_t;

typedef struct map_data_manager_t_
{
  map_id_t *maps[3];
  int map_counts[3];
  /* 0: Interior cell map
   * 1: Exterior cell map
   * 2: Face map (all faces)
   */
} map_data_manager_t;

/* Forward declaration: Define in thread_tools.c */
typedef struct multiple_periodics_groups_t_ mpg_t;

/* Placeholder for domain dependent obj data */
typedef struct obj_data_manager_t_
{
  mpg_t *mpg;

} obj_data_manager_t;

typedef struct domain_data_manager_t
{
  domain_store_manager_t store;
  domain_tuple_manager_t tuple;
  domain_node_manager_t  node;

  int wall_distance_calculated;
  void *nci_cached_neighborhood;

  identifier_data_manager_t ids;
  msn_data_manager_t msn;
  map_data_manager_t maps;
  obj_data_manager_t objs;

} domain_data_manager_t;

#define WALL_DISTANCE_CALCULATED(d)                    \
  (DOMAIN_DATA_MANAGER(d).wall_distance_calculated)
#define DOMAIN_DATA_MANAGER(d) ((Lookup_Node_Thread_Domain(d))->data_manager)
#define RDOMAIN_DATA_MANAGER(d) ((d)->data_manager) /* d already root domain */

#if USE_DOMAIN_DATA_MANAGER

#define DOMAIN_NCI_CACHED_NEIGHBORHOOD(d)  (DOMAIN_DATA_MANAGER(d).nci_cached_neighborhood)

/* Macros for IDs related to domain */
#define DOMAIN_IDS_NEIGHBORHOOD_ID(d) (DOMAIN_DATA_MANAGER(d).ids.neighborhood_id)
#define DOMAIN_IDS_GRID_ID(d) (DOMAIN_DATA_MANAGER(d).ids.grid_id)

/* MSN related macros */
#define DOMAIN_MSN_HAS_MSN_P(d)       (DOMAIN_DATA_MANAGER(d).msn.has_msn_p)
#define DOMAIN_MSN_GRID_ID(d)         (DOMAIN_DATA_MANAGER(d).msn.grid_id)
#define DOMAIN_MSN_NEIGHBORHOOD_ID(d) (DOMAIN_DATA_MANAGER(d).msn.neighborhood_id)
#define DOMAIN_MSN_VID_START(d)       (DOMAIN_DATA_MANAGER(d).msn.vid_start)
#define DOMAIN_MSN_NMSN(d)            (DOMAIN_DATA_MANAGER(d).msn.nmsn)
#define DOMAIN_MSN_NMSN_PAIRC(d)      (DOMAIN_DATA_MANAGER(d).msn.nmsn_pairc)
#define DOMAIN_MSN_NMSN_PAIRF(d)      (DOMAIN_DATA_MANAGER(d).msn.nmsn_pairf)
#define DOMAIN_MSN_NIF_PAIR(d)        (DOMAIN_DATA_MANAGER(d).msn.nif_pair)
#define DOMAIN_MSN_MSN(d)             (DOMAIN_DATA_MANAGER(d).msn.msn)
#define DOMAIN_MSN_IF_PAIR(d)         (DOMAIN_DATA_MANAGER(d).msn.if_pair)
#define DOMAIN_MSN_MSN_PAIRC(d)       (DOMAIN_DATA_MANAGER(d).msn.msn_pairc)
#define DOMAIN_MSN_MSN_PAIRF(d)       (DOMAIN_DATA_MANAGER(d).msn.msn_pairf)
#define DOMAIN_MSN_RECOVER_MSN(d)     (DOMAIN_DATA_MANAGER(d).msn.recover_msn)
#define DOMAIN_MSN_ADD_MSN_IFACE_CORNER(d)     (DOMAIN_DATA_MANAGER(d).msn.add_msn_iface_corner)

/* Cell and Face map related macros; this is used to locate cy cell/face ID */
#define DOMAIN_MAP_INT_CMAP(d)              (DOMAIN_DATA_MANAGER(d).maps.maps[0])
#define DOMAIN_MAP_EXT_CMAP(d)              (DOMAIN_DATA_MANAGER(d).maps.maps[1])
#define DOMAIN_MAP_ALL_FMAP(d)              (DOMAIN_DATA_MANAGER(d).maps.maps[2])
#define DOMAIN_MAP_INT_CMAP_COUNT(d)        (DOMAIN_DATA_MANAGER(d).maps.map_counts[0])
#define DOMAIN_MAP_EXT_CMAP_COUNT(d)        (DOMAIN_DATA_MANAGER(d).maps.map_counts[1])
#define DOMAIN_MAP_ALL_FMAP_COUNT(d)        (DOMAIN_DATA_MANAGER(d).maps.map_counts[2])

/* Macros for accessing objects stored under domain data manager */
#define DOMAIN_OBJS_MPG(d)             (DOMAIN_DATA_MANAGER(d).objs.mpg)
#define DOMAIN_OBJS_MPG_GROUPS(d)      (DOMAIN_DATA_MANAGER(d).objs.mpg->per_exc_grps)
#define DOMAIN_OBJS_MPG_COUNT(d)       (DOMAIN_DATA_MANAGER(d).objs.mpg->per_exc_grps_cnt)
#define DOMAIN_OBJS_MPG_EXISTS(d)      (DOMAIN_DATA_MANAGER(d).objs.mpg->ang_per_exist_p)

#define DOMAIN_STORE(d) (DOMAIN_DATA_MANAGER(d).store)
#define DOMAIN_TUPLE(d) (DOMAIN_DATA_MANAGER(d).tuple)
#define DOMAIN_NODE(d) (DOMAIN_DATA_MANAGER(d).node)
#define RDOMAIN_STORE(d) (RDOMAIN_DATA_MANAGER(d).store)
#define RDOMAIN_TUPLE(d) (RDOMAIN_DATA_MANAGER(d).tuple)
#define RDOMAIN_NODE(d) (RDOMAIN_DATA_MANAGER(d).node)
#define DOMAIN_NODE_THREAD(d) ((Lookup_Node_Thread_Domain(d))->node_thread)

#define DOMAIN_NODE_LIST(d) (DOMAIN_NODE(d).node_list)
#define DOMAIN_NODES_USED(d) (DOMAIN_NODE(d).nodes_used)
#define DOMAIN_NODES_IN_DUMP(d) (DOMAIN_NODE(d).nodes_in_dump)
#define DOMAIN_NODE_BLOCK(d) (DOMAIN_NODE(d).node_block)
#define DOMAIN_NNODE_BLOCKS(d) (DOMAIN_NODE(d).nnode_blocks)
#define DOMAIN_NODE_BLOCK_SIZE(d) (DOMAIN_NODE(d).node_block_size)

/* domain d already root domain, to skip the loopup of root domain */
#define RDOMAIN_NODE_THREAD(d) ((d)->node_thread)
#define RDOMAIN_NODE_LIST(d) (RDOMAIN_NODE(d).node_list)
#define RDOMAIN_NODES_USED(d) (RDOMAIN_NODE(d).nodes_used)
#define RDOMAIN_NODES_IN_DUMP(d) (RDOMAIN_NODE(d).nodes_in_dump)
#define RDOMAIN_NODE_BLOCK(d) (RDOMAIN_NODE(d).node_block)
#define RDOMAIN_NNODE_BLOCKS(d) (RDOMAIN_NODE(d).nnode_blocks)
#define RDOMAIN_NODE_BLOCK_SIZE(d) (RDOMAIN_NODE(d).node_block_size)

FLUENT_EXPORT struct domain_struct *Lookup_Node_Thread_Domain(struct domain_struct *);
FLUENT_EXPORT struct thread_struct *Get_Node_Thread(struct domain_struct *);

#else /* USE_DOMAIN_DATA_MANAGER */
extern struct thread_struct *node_thread;
extern struct domain_struct *root_domain;
#define NODE_THREAD(v) node_thread
#define DOMAIN_NODE_THREAD(d) node_thread
#define DOMAIN_NODE_LIST(d) node_list
#define Get_Node_Thread(_d) node_thread
#define DOMAIN_NODES_USED(d) nodes_used
#define DOMAIN_NODES_IN_DUMP(d) nodes_in_dump
#define DOMAIN_NODE_BLOCK(d) node_block
#define DOMAIN_NNODE_BLOCKS(d) nnode_blocks
#define RDOMAIN_NODE_BLOCK(d) node_block
#define RDOMAIN_NNODE_BLOCKS(d) nnode_blocks
#define DOMAIN_NODE_BLOCK_SIZE(d) node_block_size
#endif /* USE_DOMAIN_DATA_MANAGER */

FLUENT_EXPORT void Free_Domain_Data_Manager(struct domain_struct *);
/*******************************************************/
/* QUADRATIC_FIT_SCHEME is used in storage.h and in mem.h.
 * This header file is the only, which is icluded in both. */
#if RP_3D && !sys_ntx86 && !sys_win64 && !sys_lnarm64
#define QUADRATIC_FIT_SCHEME TRUE
#else
#define QUADRATIC_FIT_SCHEME FALSE
#endif
#endif /* _FLUENT_STORE_H */
