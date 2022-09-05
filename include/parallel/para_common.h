/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_PARA_COMMON_H
#define _FLUENT_PARA_COMMON_H

/*
 * to contain the parallel global flags
 */

#if RP_NODE
typedef struct Entity_Database_t Entity_Database;
#endif

typedef struct parallel_virtual_machine_t_
{
  int *master; /* each machine as a group, and the first rank as the master */
  int *machine; /* the unique machine id */
  int *machine_size; /* how many ranks on each machine, it's a dist array */
  int *machine_ranks; /* sorted by machine id */
  int nmachine;
  cxboolean equal_number_of_ranks_per_machine;
  
  int saved_compute_node_count;
  int saved_ranks_per_machine;
  
  int vm_id; /* add id to indicate if the vm is updated */
} parallel_virtual_machine_t;

typedef struct parallel_t_
{
  char comm_name[32];
  Communication_Type comm_type;
  Communication_Type comm_type_amg;
  Communication_Type comm_type_io;
  int comm_type_evaluating;
  double time[8];
  int *master; /* each machine as a group, and the first rank as the master */
  int *machine; /* the unique machine id */
  int *machine_size; /* how many ranks on each machine, it's a dist array */
  int *machine_ranks; /* sorted by machine id */
  int nmachine;
  cxboolean equal_number_of_ranks_per_machine;
  int i_am_in_tgrid;
  int tgrid_comm;
  cxboolean data_read_use_polled_recv;
  cxboolean all_to_all_use_hierarchy;
#if RP_NODE
  Entity_Database *EntityDb[2]; /* Entity database for parallel lookups, see entity_db.c */
#endif
  
  parallel_virtual_machine_t vm;
} parallel_t;

extern FLUENT_EXPORT parallel_t parallel;

#endif /* _FLUENT_PARA_COMMON_H */
