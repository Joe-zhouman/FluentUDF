/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/
typedef struct cx_mem_block_struct
{
  char   *alloc_mem;
  char   *avail_mem;
  int     avail_mem_size;
  struct  cx_mem_block_struct *next;
} cx_mem_block_t;

typedef struct cx_mem_manager_struct
{
  cx_mem_block_t *mb;
  int             unit_size;
  int             alloc_count;
} cx_mem_manager_t;

#define ALLOC_COUNT_TREE_NODE 32768
#define ALLOC_COUNT_ELT       ALLOC_COUNT_TREE_NODE*8
#define ALLOC_COUNT_V         ALLOC_COUNT_ELT*8

void   CX_Build_Tree_MT(int, float *, const int, char *, const size_t, int, int);
double CX_Shortest_Dist_Point_Tree_MT(float *, CX_Face_t *, cxboolean *);
void   CX_Free_Tree_MT(void);

