/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_CASE_H
#define _FLUENT_CASE_H

#include "dll.h"

#ifndef BUILD_GRID_OPT
#define BUILD_GRID_OPT 0
#endif

FLUENT_EXPORT cxindex cell_count_from_dump(void);
FLUENT_EXPORT void Set_Node_Read_Count (cxindex);
FLUENT_EXPORT void Init_Grid(void);
FLUENT_EXPORT void create_nosolve_face_threads(Domain *);
FLUENT_EXPORT Domain *Build_Grid(Domain *d);
FLUENT_EXPORT Domain *Clear_Domain(Domain *d);
FLUENT_EXPORT Domain *Clear_Grid(Domain *d, cxboolean create_new_domain);
FLUENT_EXPORT void Clear_Partial_Grid(Domain *d);
#if PARALLEL
FLUENT_EXPORT void get_max_ids_before_appending(Domain *d);
#endif

#if PARALLEL
FLUENT_EXPORT void Dump_Dataship_new(void);
#endif

FLUENT_EXPORT void VKI_Parallel_Transfer_host_to_node0(cxboolean);
extern FLUENT_EXPORT void Free_Dumpmem(void);

FLUENT_EXPORT int Alloc_Cell_Dump(cxindex, cxindex, cxboolean);
FLUENT_EXPORT int Alloc_Cell_Node_Dump(cxindex, cxindex, cxboolean);
FLUENT_EXPORT int Alloc_Face_Dump(cxindex, cxindex, cxboolean);
FLUENT_EXPORT int Alloc_Node_Dump(cxindex, cxindex, cxboolean);

FLUENT_EXPORT int id_present_in_list(int);
FLUENT_EXPORT int find_old_thread_id(int);
FLUENT_EXPORT int find_new_thread_id(int);
FLUENT_EXPORT int find_thread_in_append_list(Thread *);

#if RP_HOST
FLUENT_EXPORT void Send_Cell(int);
FLUENT_EXPORT void Send_Face(int);
FLUENT_EXPORT void Send_Vert(int);
FLUENT_EXPORT void Send_Partition(int);
FLUENT_EXPORT void Send_Node_Flags(int);
FLUENT_EXPORT void Send_Node_Sids (int);
FLUENT_EXPORT void Scan_Store_Grid_Section_Heads(Domain *domain, FILE *fd, int section);
FLUENT_EXPORT void Scan_Store_Grid_Section_Heads_New(Domain *domain, FILE *fd);
#endif
#if !RP_NODE
FLUENT_EXPORT long get_grid_section_end(void);
FLUENT_EXPORT void reset_grid_section_end(void);
#else
FLUENT_EXPORT void Recv_Cell(cxindex, cxindex);
FLUENT_EXPORT void Recv_Face(cxindex, cxindex);
FLUENT_EXPORT void Recv_Vert(cxindex, cxindex);
FLUENT_EXPORT void Recv_Partition(cxindex, cxindex);
FLUENT_EXPORT void Recv_Node_Flags(cxindex, cxindex);
FLUENT_EXPORT void Recv_Node_Sids (cxindex, cxindex);
#endif

#if PARALLEL
FLUENT_EXPORT void Auto_Encapsulate_SI (Domain *domain);
FLUENT_EXPORT void Auto_Partition (Domain *domain, const char *method,
                                   cxboolean pretest);
#endif

struct buffered_reader_type;
FLUENT_EXPORT Domain *Read_Grid_Section(Domain *d, FILE *, int section);
FLUENT_EXPORT Domain *Read_Grid_Section_Buffered(Domain *domain, struct buffered_reader_type *reader, int section, int *host_reader, cxboolean is_regular_file, cxboolean allow_node0_reads);
FLUENT_EXPORT FILE *Write_Grid_Sections(Domain *d, FILE *, cxboolean binary, cxboolean all);
FLUENT_EXPORT void Write_S2S_Grid_Sections(Domain *d, FILE *, cxboolean binary, cxboolean all);

#if PARALLEL /* hdfio */
FLUENT_EXPORT int Write_HDF_Special_Case_Sections(Domain *, const char *, const char *, int);
FLUENT_EXPORT int Read_HDF_Special_Case_Sections_Before_Build_Grid(Domain *, const char *, const char *);
FLUENT_EXPORT int Read_HDF_Special_Case_Sections_After_Build_Grid(Domain *, const char *, const char *);
/*For reading Shell IDs and Thread Flags.*/
FLUENT_EXPORT int Shell_Read_Thread_Flags_HDF(char *, char *, Domain *const);
#endif

extern FLUENT_EXPORT cxindex cell_0, face_0, vert_0;
extern FLUENT_EXPORT cxindex cell_1, face_1, vert_1;
extern FLUENT_EXPORT cxindex cell_n, face_n, vert_n;
#if PARALLEL
extern FLUENT_EXPORT size_t ncell_per_chunk;
extern FLUENT_EXPORT int nface_per_chunk, nvert_per_chunk;
extern FLUENT_EXPORT cxboolean have_inquired_all_adjacent_threads;
#endif
extern FLUENT_EXPORT cxindex node_read_count;
extern FLUENT_EXPORT cxboolean have_read_partitioned_case;
extern FLUENT_EXPORT cxboolean have_cleared_grid;
extern FLUENT_EXPORT cxboolean have_read_face_pairs;
extern FLUENT_EXPORT cxboolean have_read_periodics_old;
extern FLUENT_EXPORT cxboolean have_read_periodics;
extern FLUENT_EXPORT cxboolean have_read_shadows;
extern FLUENT_EXPORT cxboolean have_read_sliding_boundary;
extern FLUENT_EXPORT cxboolean have_read_face_parents;
extern FLUENT_EXPORT cxboolean have_read_nc_metrics;
extern FLUENT_EXPORT cxboolean have_read_nc_child_faces; /* for obsolete nc interfaces */
extern FLUENT_EXPORT cxboolean have_read_child_tree;
extern FLUENT_EXPORT cxboolean have_read_cell_child_tree;
extern FLUENT_EXPORT cxboolean have_read_owner_cell_ids;
extern FLUENT_EXPORT cxboolean have_read_node_sids;
extern FLUENT_EXPORT Objp *changed_thread_id_list;
extern FLUENT_EXPORT cxboolean have_read_ghost_cell_links;
extern FLUENT_EXPORT cxboolean have_read_cell_nodes;

/* cell thread info for model-weighted partition */
#if PARALLEL
extern FLUENT_EXPORT int num_cell_threads;
extern FLUENT_EXPORT int *cell_threads_id;
extern FLUENT_EXPORT int *cell_threads_weight;
extern FLUENT_EXPORT cxindex *cell_threads_cid_start;
extern FLUENT_EXPORT cxindex *cell_threads_cid_end;
#endif /* PARALLEL */

#include "mem_dump.h"

struct io_buffer
{
  int fsync_flag;
  char *data;
  int nbytes;
  FILE *stream;
  int failed;
  int current_section;
  int more;
  int lock;
  int thread_created;
  char *fdatap1, *fdatap2;
  char *current_buffer;
  int io_buf_size;
  char *current_ptr;
};

extern struct io_buffer buffer_data;


/* this distinction is only necessary for sections with floats,
 * (e.g. node coordinates) but it doesn't hurt the rest. */
#if RP_DOUBLE
# define R_DATA "%le"
# define R_DATA2 "%le%le"
# define W_DATA "%23.16e "
# define BINARY_SECTION(id)(id+XF_DELIMITED_DOUBLE_BINARY_START)
#else
# define R_DATA "%e"
# define R_DATA2 "%e%e"
# define W_DATA "%15.8e "
# define BINARY_SECTION(id)(id+XF_DELIMITED_SINGLE_BINARY_START)
#endif

#if PARALLEL
# if RP_NODE
#  define COMPUTE_NODE_TO_INDEX(cnid,n_per_chunk) ((cxindex)(cnid)*(n_per_chunk)+1)
# endif
# if RP_HOST
#  define COMPUTE_NODE_TO_INDEX(cnid,n_per_chunk) 1
# endif
# define INDEX_TO_COMPUTE_NODE(indx, n_per_chunk) (((indx)-1)/(n_per_chunk))
#endif


extern FLUENT_EXPORT struct ccell *cdumpmem;
extern FLUENT_EXPORT struct vcell *vdumpmem;
extern FLUENT_EXPORT struct fcell *fdumpmem;
extern FLUENT_EXPORT struct ccell *cdump;
extern FLUENT_EXPORT struct vcell *vdump;
extern FLUENT_EXPORT struct fcell *fdump;
extern FLUENT_EXPORT struct fdata *fdatadump;
extern FLUENT_EXPORT struct fdata *fdatadumpmem;
extern FLUENT_EXPORT struct cndata *cndump;
extern FLUENT_EXPORT struct cndata *cndumpmem;
extern FLUENT_EXPORT int vki_nvert;
extern FLUENT_EXPORT int *vki_fzone_ttype, *vki_fzone_start_index, *vki_fzone_end_index;
extern FLUENT_EXPORT int *vki_czone_ttype, *vki_czone_start_index, *vki_czone_end_index;
extern FLUENT_EXPORT struct claplace *clpdumpmem;
#if RP_HANG
extern FLUENT_EXPORT struct cchild *chdump;
extern FLUENT_EXPORT struct cchild *chdumpmem;
extern FLUENT_EXPORT struct kidmem *kdumpmem;
#endif
#if PARALLEL
extern FLUENT_EXPORT dump_t gdumpmem;
#endif /* PARALLEL */

extern FLUENT_EXPORT struct objp_struct *virtual_ids;
FLUENT_EXPORT fchild *get_f_child_mem (int nc);
#if RP_POLYHEDRA
extern FLUENT_EXPORT void init_f_nodes_mem (size_t init_alloc_size);
extern FLUENT_EXPORT cxindex *get_f_nodes_mem (int nnodes);
extern void free_f_nodes_mem (void);
#endif
extern void wait_for_io_complete(struct io_buffer *);
extern void init_io_buffer(struct io_buffer *, FILE *, int);
FLUENT_EXPORT void SetDomainInfoFromIMesh(void);
extern void update_before_grid_write (Domain *);
extern void update_after_grid_write (Domain *);
extern int estimate_face_io_buffer_size_in_index(int);

extern void set_local_range(cxindex, cxindex, cxindex *, cxindex *);
FLUENT_EXPORT void Fill_Case_Export_Functions(void);
FLUENT_EXPORT int Get_Reading_Option(void);
#if PARALLEL
FLUENT_EXPORT void Free_Cell_Dump_new(dump_t *const dump);
FLUENT_EXPORT void Free_Face_Dump_new(dump_t *const dump);
FLUENT_EXPORT void Free_Node_Dump_new(dump_t *const dump);
FLUENT_EXPORT void Free_Global_Dump_new(void);
#endif /* PARALLEL */

#endif /* _FLUENT_CASE_H */
