/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 *
 */

#ifndef _SECT_READ_H
#define _SECT_READ_H

struct mem_block
{
  void *mem;
  struct mem_block *next;
};

struct mem_block_list_type
{
  struct mem_block *head;
  struct mem_block *curr;
  int offset;
  int size;
};

void init_memblock_list(struct mem_block_list_type *mem_block_list, int size);
void add_mem_block(struct mem_block_list_type *mem_block_list);
void *get_mem_chunk(struct mem_block_list_type *mem_block_list, int request);
void reset_memblock_list(struct mem_block_list_type *mem_block_list);
void free_memblock_list(struct mem_block_list_type *mem_block_list);

int
Read_Partition_Section_Buffered(Domain *domain,
                                struct  buffered_reader_type *reader,
                                cxboolean binary,
                                cxindex cell_1,
                                cxindex cell_n,
                                int *npart_read,
                                struct ccell *cdumpmem,
                                int section);
int
Read_Node_Flag_Section_Buffered(Domain *domain,
                                struct buffered_reader_type *reader,
                                cxboolean binary,
                                cxindex vert_1,
                                cxindex vert_n,
                                struct vcell *vdumpmem);

int
Read_Node_SId_Section_Buffered (Domain *domain,
                                struct buffered_reader_type *reader,
                                cxboolean binary,
                                cxindex vert_1,
                                cxindex vert_n,
                                struct vcell *vdumpmem);
int
Read_Node_Section_Buffered(Domain *domain,
                           struct buffered_reader_type *reader,
                           cxboolean binary,
                           cxboolean double_data,
                           cxindex vert_1,
                           cxindex vert_n,
                           struct vcell *vdumpmem);
int
Read_Periodic_Face_Section_Buffered(Domain *domain,
                                    struct buffered_reader_type *reader,
                                    cxboolean binary,
                                    struct fdata *fdatadump,
                                    int section);
int
Read_Virtual_Face_Pair_Section_Buffered(Domain *domain,
                                        struct buffered_reader_type *reader,
                                        cxboolean binary,
                                        int section);
#if PARALLEL
int
Read_Face_Section_Buffered_On_Node(Domain *domain,
                                   struct buffered_reader_type *reader,
                                   cxboolean binary,
                                   cxindex face_1,
                                   cxindex face_n,
                                   struct fcell *fdumpmem,
                                   struct fdata *fdatadumpmem,
                                   int section);
#endif

int
Read_Face_Section_Buffered(Domain *domain,
                           struct buffered_reader_type *reader,
                           cxboolean binary,
                           cxindex face_1,
                           cxindex face_n,
                           struct fcell *fdumpmem,
                           struct fdata *fdatadumpmem,
                           int section);

int
Read_Face_Tree_Section_Buffered(Domain *domain,
                                struct buffered_reader_type *reader,
                                cxboolean binary,
                                int section,
                                cxindex face_1,
                                cxindex face_n,
                                struct kidmem **kdumpmem,
                                fchild *fkdump,
                                struct fcell *fdumpmem);

int
Read_Cell_Tree_Section_Buffered(Domain *domain,
                                struct buffered_reader_type *reader,
                                cxboolean binary,
                                int section,
                                cxindex cell_1,
                                cxindex cell_n,
                                struct kidmem **kdumpmem,
                                struct cchild *ckdump,
                                struct cchild *chdumpmem);
int
Read_Face_Parent_Section_Buffered(Domain *domain,
                                  struct buffered_reader_type *reader,
                                  cxboolean binary,
                                  int section,
                                  cxindex face_1,
                                  cxindex face_n,
                                  struct kidmem **kdumpmem,
                                  fchild *fkdump,
                                  struct fcell *fdumpmem);
int
Read_Ghost_Cell_Link_Section_Buffered (Domain *domain,
                                       struct buffered_reader_type *reader,
                                       cxboolean binary,
                                       int section,
                                       cxindex cell_1,
                                       cxindex cell_n,
                                       struct kidmem **kdumpmem,
                                       struct cchild *ckdump,
                                       struct cchild *chdumpmem);
int
Read_NC_Child_Section_Buffered(Domain *domain, struct buffered_reader_type *reader, cxboolean binary, int section);

int
Read_NC_Metric_Section_Buffered(Domain *domain,
                                struct buffered_reader_type *reader,
                                cxboolean binary,
                                cxboolean double_data);

int
Read_Cell_Section_Buffered(Domain *domain,
                           struct buffered_reader_type *reader,
                           cxboolean binary,
                           cxindex cell_1,
                           cxindex cell_n,
                           struct ccell *cdumpmem,
                           int section);
#endif
