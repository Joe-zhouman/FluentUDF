/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _SG_CLUSTER_H
#define _SG_CLUSTER_H

struct int_list
{
  int f;
  struct int_list *next;
};

typedef struct int_list Face_List;

typedef struct int_list Dual_Edge_List;

typedef struct dual_node_struct
{
  int id;
  int mark;
  int nfaces;
  int *face_list;
  Dual_Edge_List *dl;
  real area;
  real perimeter;
  real plane[3];
  struct dual_node_struct *next;
  struct dual_node_struct *previous;

} Dual_Node;

typedef struct dual_edge_struct
{
  Dual_Node *v0, *v1;
  real weight;
  real length;
  cxboolean merge;
} Dual_Edge;

FLUENT_EXPORT int Write_Cluster(Domain *domain);
FLUENT_EXPORT void S2s_Glob_Elements(Domain *domain, real split_angle);
FLUENT_EXPORT int Find_Junction_Face(face_t, Thread *, Thread *);
#endif
