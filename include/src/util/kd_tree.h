/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SLIDEUTIL_H
#define _FLUENT_SLIDEUTIL_H

#include "dll.h"

/* kd face trhead search tree. (see tgrid for more)
 * is assumed that all faces are on the same thread */

typedef struct kd_tree_struct KdTree;

struct kd_tree_struct
{
  int split;      /* treshold (when to split) */
  int merge;      /* threshold when to merge */
  int bucket_size;    /* max no of data in a bucket */
  real xlowl[3];    /* lower left corner of bound box */
  real xsize[3];    /* size bound box */
  void *mem_alloc;    /* memory for tree */
  int mem_id;
  struct bucket_list_object_struct *blist; /* definition of bucket list */
  struct kd_node_struct *root;  /* root */
  struct thread_struct *thread; /* face thread */
};

extern FLUENT_EXPORT KdTree *Create_KD_Tree(Thread *, int, real [], real [], int, int);
extern FLUENT_EXPORT void Delete_KD_Tree(KdTree *);

extern FLUENT_EXPORT int KD_Face_Overlaps_Root(KdTree *, face_t);
extern FLUENT_EXPORT int KD_Face_Insert(KdTree *, face_t);
extern FLUENT_EXPORT int KD_Face_Range_Search(KdTree *, real [], real, face_t [], int, int *);

#endif /* _FLUENT_SLIDEUTIL_H */


