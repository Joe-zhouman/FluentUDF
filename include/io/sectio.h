/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SECTIO_H
#define _FLUENT_SECTIO_H

#if PARALLEL
#include "buffered_reader.h"
#endif /* PARALLEL */
#include "dll.h"

#if PARALLEL
typedef struct section_head_struct
{
  int section;
  int id;
  cxindex ind1;
  cxindex indn;
  int val1;
  int val2;
  void *pt1;
  cxindex nsent;
} Section_Head;

typedef struct face_data_struct_tag
{
  int fnodes;
  cxindex fid;
#if RP_POLYHEDRA
  cxindex *vid;
#else
  cxindex vid[MAX_NODES_PER_FACE];
#endif
  cxindex cid0, cid1;
} face_data_struct;

struct Buffered_Case_Write_Settings_Type
{
  int io_buf_size;
  int min_case_size;
  int min_case_size_pwrite;
  int min_thread_data_pwrite;
  int min_inter_machine_bw;
  int min_distribution_node_count;
  int min_sorting_node_count;
  int fsync_flag;
  int use_nonblocking;
};

extern FLUENT_EXPORT Section_Head *section_head;
extern FLUENT_EXPORT int section_head_allocd;
extern FLUENT_EXPORT int section_head_filled;

typedef struct cnode_head
{
  int tid;
  cxindex cmin;
  cxindex cmax;
} Cnode_Section_Head;


extern FLUENT_EXPORT Cnode_Section_Head *cnode_section_head;
extern FLUENT_EXPORT int cnode_head_allocd;
extern FLUENT_EXPORT int cnode_head_filled;

extern struct Buffered_Case_Write_Settings_Type buffered_case_write_settings;

int pack_cdata(char *dest, struct cdata *source, int nelems);
int unpack_cdata(struct cdata *dest, char *source, int nelems);

#if PARALLEL
FLUENT_EXPORT int Pack_fdata_struct(char *, struct fdata *, int);
FLUENT_EXPORT int Unpack_fdata_struct(struct fdata *, char *, int);
FLUENT_EXPORT int Pack_fcap_t(char *, fcap_t *, int);
FLUENT_EXPORT int Unpack_fcap_t(fcap_t *, char *, int);
FLUENT_EXPORT void Free_Cell_Node_Section_Heads(void);
#endif /* PARALLEL */

FLUENT_EXPORT void Set_Check_Partition_Mismatch(cxboolean);
FLUENT_EXPORT void Alloc_Section_Heads(int);
FLUENT_EXPORT void Free_Section_Heads(void);
FLUENT_EXPORT void Fast_IO_Transfer_Dumps(void);
FLUENT_EXPORT cxboolean Fast_IO_P(int);
FLUENT_EXPORT cxboolean New_Fast_IO_P(int);
FLUENT_EXPORT void Dump_Section_Heads(void);
FLUENT_EXPORT cxboolean check_if_reading_surface_mesh(void);
FLUENT_EXPORT cxboolean check_if_exceeding_cell_limit(void);
FLUENT_EXPORT int Write_Cell_Section_Buffered(Domain *, FILE *, cxboolean);
FLUENT_EXPORT int Write_Face_Section_Buffered(Domain *, FILE *, cxboolean, cxboolean);
FLUENT_EXPORT int Write_Node_Section_Buffered(Domain *, FILE *, cxboolean, cxboolean, cxindex);
FLUENT_EXPORT int Write_Node_Flag_Section_Buffered(Domain *, FILE *, cxboolean, cxindex);
FLUENT_EXPORT int Write_Partition_Section_Buffered(Domain *, FILE *, cxboolean);
FLUENT_EXPORT int Write_Periodic_Face_Section_Buffered(Domain *, FILE *, cxboolean);
#if RP_HANG
FLUENT_EXPORT int Write_Face_Tree_Section_Buffered(Domain *, FILE *, cxboolean);
FLUENT_EXPORT int Write_Cell_Tree_Section_Buffered(Domain *, FILE *, cxboolean);
#endif
FLUENT_EXPORT int Write_Node_SId_Section_Buffered (Domain *, FILE *, cxboolean, cxindex);
FLUENT_EXPORT int Write_Face_Parent_Section_Buffered(Domain *, FILE *, cxboolean);
FLUENT_EXPORT int Write_NC_Metric_Section_Buffered(Domain *, FILE *, cxboolean binary);
FLUENT_EXPORT int Write_Ghost_Cell_Link_Section_Buffered(Domain *, FILE *, cxboolean);
#endif
FLUENT_EXPORT Objp *cache_virtual_thread_ids (int, Objp *);
FLUENT_EXPORT Objp *Append_Id_To_Changed_List(Objp *, int);

FLUENT_EXPORT int Read_Cell_Section(Domain *, FILE *, cxboolean,
                                    cxindex, cxindex, struct ccell *, int);
FLUENT_EXPORT int Read_Cell_Node_Section(Domain *, FILE *, cxboolean,
                                         cxindex, cxindex, struct cndata *, int);
FLUENT_EXPORT int Write_Cell_Section(Domain *, FILE *, cxboolean);
FLUENT_EXPORT int Read_Face_Section(Domain *, FILE *, cxboolean,
                                    cxindex, cxindex, struct fcell *, struct fdata *, int);
FLUENT_EXPORT int Write_Face_Section(Domain *, FILE *, cxboolean, cxboolean);
FLUENT_EXPORT cxindex Read_Node_Section(Domain *, FILE *, cxboolean, cxboolean,
                                        cxindex, cxindex, struct vcell *);
FLUENT_EXPORT int Write_Node_Section(Domain *, FILE *, cxboolean, cxboolean, cxindex);
FLUENT_EXPORT int Read_Node_Flag_Section(Domain *, FILE *, cxboolean, cxindex,
                                         cxindex, struct vcell *);
FLUENT_EXPORT int Write_Node_Flag_Section(Domain *, FILE *, cxboolean, cxindex);
FLUENT_EXPORT int Read_Partition_Section(Domain *, FILE *, cxboolean, cxindex,
                                         cxindex, int *, struct ccell *, int);
FLUENT_EXPORT int Write_Partition_Section(Domain *, FILE *, cxboolean);
FLUENT_EXPORT int Read_Periodic_Face_Section(Domain *, FILE *, cxboolean,
                                             struct fdata *, int);
FLUENT_EXPORT int Write_Periodic_Face_Section(Domain *, FILE *, cxboolean);
FLUENT_EXPORT int Read_Virtual_Face_Pair_Section(Domain *, FILE *, cxboolean, int);
#if RP_HANG
FLUENT_EXPORT int Read_Face_Tree_Section(Domain *, FILE *, cxboolean,
                                         int, cxindex, cxindex,
                                         struct kidmem **,
                                         fchild *,
                                         struct fcell *);
FLUENT_EXPORT int Write_Face_Tree_Section(Domain *, FILE *, cxboolean);
FLUENT_EXPORT int Read_Cell_Tree_Section(Domain *, FILE *, cxboolean,
                                         int, cxindex, cxindex,
                                         struct kidmem **,
                                         struct cchild *,
                                         struct cchild *);
FLUENT_EXPORT int Write_Cell_Tree_Section(Domain *, FILE *, cxboolean);
#endif /* RP_HANG */
FLUENT_EXPORT int Read_Node_SId_Section (Domain *, FILE *, cxboolean, cxindex,
                                         cxindex, struct vcell *);
FLUENT_EXPORT int Write_Node_SId_Section (Domain *, FILE *, cxboolean, cxindex);

FLUENT_EXPORT int Write_Face_Parent_Section(Domain *, FILE *, cxboolean);
FLUENT_EXPORT int Read_Face_Parent_Section(Domain *, FILE *, cxboolean, int,
                                           cxindex, cxindex,
                                           struct kidmem **, fchild *, struct fcell *);

FLUENT_EXPORT int Read_NC_Child_Section(Domain *, FILE *, cxboolean, int);
FLUENT_EXPORT int Read_NC_Metric_Section(Domain *, FILE *, cxboolean, cxboolean);
FLUENT_EXPORT int Write_NC_Metric_Section(Domain *, FILE *, cxboolean binary);

FLUENT_EXPORT int Read_Ghost_Cell_Link_Section (Domain *, FILE *, cxboolean,
                                                int, cxindex, cxindex,
                                                struct kidmem **,
                                                struct cchild *,
                                                struct cchild *);

FLUENT_EXPORT int Write_Ghost_Cell_Link_Section(Domain *, FILE *, cxboolean);

#if RP_NODE
void set_local_index(cxindex, cxindex, cxindex *, cxindex *, int *);
#endif

FLUENT_EXPORT cxindex Fast_Transfer_Face_Dump(int, cxindex **);
#if RP_NODE
FLUENT_EXPORT cxindex Fast_Transfer_Face_Dump_Nodes(int nfd_max, cxindex **fnode_buf, cxboolean reading_surf_mesh);
#endif
FLUENT_EXPORT cxindex Fast_Transfer_Cell_Dump(void);
FLUENT_EXPORT cxindex Fast_Transfer_Cell_Node_Dump(void);
FLUENT_EXPORT int total_cell_sections(int);
FLUENT_EXPORT int total_face_sections(int);
FLUENT_EXPORT int get_collect_flag(void);
FLUENT_EXPORT int get_sort_flag(int only_collect);
FLUENT_EXPORT int get_parallel_case_write_flag(void);
FLUENT_EXPORT void set_default_buffered_case_write_settings(void);
#if RP_HOST
FLUENT_EXPORT void send_tree(int final_dest, int n_elem, struct kidmem *kidmem);
#endif
#if RP_NODE
FLUENT_EXPORT void recv_tree(struct kidmem *kidmem);
FLUENT_EXPORT  void set_face_child_dump(cxindex face_1, cxindex face_n, struct kidmem *kidmem, struct fcell *fdumpmem);
FLUENT_EXPORT void set_cell_child_dump(int cell_1, int cell_n, struct kidmem *kidmem, struct cchild *chdumpmem);
#endif

#if PARALLEL /* hdfio */
FLUENT_EXPORT int Write_HDF_Ghost_Cell_Link_Section(Domain *, char *);
FLUENT_EXPORT int Read_HDF_Ghost_Cell_Link_Section(Domain *, char *, int, cxindex, cxindex,
                                                   struct kidmem **, struct cchild *, struct cchild *);
#endif /* PARALLEL */

#if PARALLEL

cxboolean Get_sub_block_indices(
  int nid,
  cxindex block_ind1, cxindex block_indn,
  cxindex *sub_block_ind1, cxindex *sub_block_indn
);

cxboolean
Get_Block_Size_For_Uniform_Facetypes(
  cxindex ind1,
  cxindex indn,
  int face_type,
  cxindex *num_elements_per_face_record,
  cxindex *num_of_face_records_in_a_block,
  cxindex *total_elements_in_face_section,
  cxindex *block_size_in_elements
);

cxboolean
Read_Face_Section_Transfer_Face_Data(
  cxboolean mixed_or_poly,
  cxindex block_ind1, cxindex block_indn,
  cxindex *face_records,
  cxindex num_of_cxindex_elements_to_send,
  cxindex *array_of_cxindex_elements_to_send_to_processes,
  cxindex num_elements_per_face_record,
  cxindex num_of_face_records_in_a_block,
  cxboolean *my_sub_block_enclosed,
  cxindex *my_block_ind1, cxindex *my_block_indn,
  cxboolean *all_faces_in_current_section_dumped
);

cxboolean
Read_Face_Section_Fill_Face_Dump(
  cxboolean mixed_or_poly,
  int face_type,
  Thread *thread,
  cxindex face_0, cxindex my_block_ind1, cxindex my_block_indn,
  cxindex *face_records,
  cxindex *my_faces_count, cxindex *my_faces_reversed_count
);

cxboolean
Read_Face_Section_Transfer_Mixed_Face_Data_And_Fill_Dump(
  Thread *thread,
  cxindex face_0,
  cxindex block_ind1, cxindex block_indn,
  cxindex *face_records,
  cxindex num_of_cxindex_elements_to_send,
  cxindex *array_of_cxindex_elements_to_send_to_processes,
  cxindex *my_faces_count, cxindex *my_faces_reversed_count,
  cxboolean *all_faces_in_current_section_dumped
);

cxboolean
Read_Face_Section_Transfer_Uniform_Face_Data_And_Fill_Dump(
  Thread *thread,
  cxindex face_0,
  cxindex block_ind1, cxindex block_indn,
  cxindex *face_records,
  cxindex num_of_cxindex_elements_in_a_block,
  cxindex num_elements_per_face_record,
  cxindex num_of_face_records_in_a_block,
  int face_type,
  cxindex *my_faces_count, cxindex *my_faces_reversed_count,
  cxboolean *all_faces_in_current_section_dumped
);

cxboolean Case_Fread(
  struct buffered_reader_type *,
  FILE *fd,
  Thread *thread,
  cxindex *read_buffer,
  cxindex starting_index,
  cxindex num_elements_to_read
);

cxboolean
Read_Face_Section_Bin_Mixed_IO_Native_Index(
  struct buffered_reader_type *,
  FILE *fd,
  Thread *thread,
  int num_elements_in_io_buffer,
  cxindex block_ind1,
  cxboolean *read_part_of_face_record,
  cxindex *face_record_fragment_len,
  cxindex **face_record_fragment,
  cxindex total_face_records_in_face_section,
  cxindex *num_face_records_read_so_far,
  cxindex *current_node,
  cxindex ind1, cxindex indn,
  cxindex *num_elements_read_to_be_sent,
  cxindex *total_num_of_elements_assigned,
  cxindex *array_of_cxindex_elements_to_send_to_processes
);

cxboolean
Read_Face_Section_Bin_Mixed_IO_Non_Native_Index(
  struct buffered_reader_type *,
  FILE *fd,
  Thread *thread,
  int num_elements_in_io_buffer,
  int *nodes_per_face,
  cxboolean *face_type_saved,
  cxindex total_face_records_in_face_section,
  cxindex *num_face_records_read_so_far,
  cxindex *current_node,
  cxindex ind1, cxindex indn,
  cxindex *num_elements_read_to_be_sent,
  cxindex *total_num_of_elements_assigned,
  cxindex *array_of_cxindex_elements_to_send_to_processes
);

cxboolean
Read_Face_Section_Bin_Mixed_Overlap_IO_and_Fill_Dump_Parallel(
  struct buffered_reader_type *,
  FILE *fd,
  Thread *thread,
  cxindex face_0, cxindex ind1, cxindex indn,
  cxindex *nfaces_read, cxindex *nfaces_reversed
);

cxboolean
Read_Face_Section_Bin_Uniform_Overlap_IO_and_Fill_Dump_Parallel(
  struct buffered_reader_type *,
  FILE *fd,
  Thread *thread,
  cxindex face_0, cxindex ind1, cxindex indn,
  int face_type,
  cxindex *nfaces_read, cxindex *nfaces_reversed
);

#endif

cxboolean
Read_Face_Section_Main_Face_Loop(
  cxindex face_0,
  cxindex ind1, cxindex indn,
  cxindex block_ind1, cxindex block_indn,
  cxboolean binary,
  int face_type, int section,
  FILE *fd,
  struct fcell *fdumpmem, struct fdata *fdatadumpmem,
  struct fcell **fc_dp, struct fdata **fcd_dp,
  Thread *thread,
  int *nfnode_max, cxindex *fnode_buf,
  int *nid, cxindex *nread, cxindex *reverse_count
);

#endif /* _FLUENT_SECTIO_H */
