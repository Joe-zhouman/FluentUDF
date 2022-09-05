/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_PART_H
#define _FLUENT_PART_H

#include "mem.h"
#include "case.h"

#define PART_UNDEFINED -1
#define PART_MULTIPLE -2

typedef enum
{
  DECOMP = 0,
  COMPLETE,
  HYPERCUBE,
  TREELEAF,
  MESH2D,
  MESH3D,
  TORUS2D,
  TORUS3D
} Network_Topology;

# define ACTIVE_PARTITION_COUNT(d) Get_Active_Partition_Count(d,__FILE__,__LINE__)
#define STORED_PARTITION_COUNT(d) Get_Stored_Partition_Count(d,__FILE__,__LINE__)
#define SET_ACTIVE_PARTITION_COUNT(d,val) Set_Active_Partition_Count(d,val,__FILE__,__LINE__)
#define SET_STORED_PARTITION_COUNT(d,val) Set_Stored_Partition_Count(d,val,__FILE__,__LINE__)

/*
 * Metis prototype definitions
 * int may enable it to go up to 2 billion cells
 */

#define METIS_32BIT 0

#if METIS_32BIT
typedef int idxtype;
typedef float realtype;

#else

#if _NT
typedef __int64 idxtype;
typedef double realtype;
#else
typedef int64_t idxtype;
typedef double realtype;
#endif /* ends _NT */

#endif

/* FL_METIS_NOPTIONS tracks METIS_NOPTIONS which is 40
 * (see metislib/include/metis.h)
 */
#define FL_METIS_NOPTIONS 40

typedef struct metis_t_
{
  idxtype *vtxdist;
  idxtype *xadj;
  idxtype *adjncy;
  idxtype *vwgt;
  idxtype *adjwgt;
  idxtype nv;   /* number of vertices */
  idxtype nadj; /* number of edges */
  idxtype wgtflag;
  idxtype numflag;
  idxtype nparts;
  idxtype options[FL_METIS_NOPTIONS];
  idxtype edgecut;
  idxtype *part;
  idxtype *comm;
  idxtype ncon;
  realtype *tpwgts;
  realtype *ubvec;
  realtype itr; /* set 1000 as default */
  realtype *xyz;
  idxtype *vsize;
  int verbosity;
  /* some other flags not related to metis, but for the clean of code */
  float *loadvec;
  void (*parmetis_fnc)();
  cxboolean need_load_balance;
  cxboolean if_agglomerate;
  int laplace;
  cxboolean ignore_model_weight;
  cxboolean only_dpm_weight;
} metis_t;

extern cxboolean has_grouped_cells;

FLUENT_EXPORT cxboolean Is_Not_Target_Thread(Thread *);
FLUENT_EXPORT int Partition_method_is_metis(char *);

FLUENT_EXPORT void Move_Offset_Forward(int *, int);
FLUENT_EXPORT int Get_Range_Index(int, int *, int);
FLUENT_EXPORT int Create_Compacted_Grouped(Domain *, int, int, int *, int *, int *,
                                           cxboolean (*is_marked)(cell_t, Thread *));
FLUENT_EXPORT void Exchange_All_To_All(int *, int *, int);
FLUENT_EXPORT int Size_To_Offset(int *, int);
FLUENT_EXPORT void Offset_To_Size(int *nsend, int len);
FLUENT_EXPORT void Exchange_All_To_All_Buf(int *, int *, int *, int *);
FLUENT_EXPORT void Exchange_All_To_All_Buf_Index(cxindex *, cxindex *, int *, int *, int);
FLUENT_EXPORT int Get_Part(cell_t, Thread *, int);
FLUENT_EXPORT int *Form_Offset_Table(int);
FLUENT_EXPORT void Set_Part(cell_t, Thread *, int, int);

#if SEEM && !RP_NODE
FLUENT_EXPORT Pointer Part_Function_Names(Domain *domain);
FLUENT_EXPORT Pointer Part_Function_Picks(Domain *domain);
FLUENT_EXPORT Pointer Pretest_Part_Function_Names(Domain *domain);
FLUENT_EXPORT Pointer Must_Pretest_Part_Function_Names(Domain *domain);
#endif
FLUENT_EXPORT void Clear_Partition_Bit_SI(Domain *domain);
FLUENT_EXPORT void Set_Partition_Bit(Domain *d);
FLUENT_EXPORT void Partition_Domain(Domain *d,
                                    const char *method,
                                    int n,
                                    float *loadvec,
                                    cxboolean before_adapt_p,
                                    int marker);
FLUENT_EXPORT void Partition_Domain_By_Thread_Mask (Domain *,
                                                    int,
                                                    float *,
                                                    cxboolean,
                                                    cxboolean (*)(Thread *));
FLUENT_EXPORT void Clear_Partition_Bit(Domain *, int);
FLUENT_EXPORT void Set_Partition_Bit_By_Register(Domain *, unsigned int);
FLUENT_EXPORT void Set_Partition_Bit_By_Thread(Domain *, Thread *, int);
FLUENT_EXPORT void Set_Partition_In_Marked_Region(Domain *d, unsigned int, int);
FLUENT_EXPORT void Set_Selected_Cells_to_Part_ID (Domain *, int);
FLUENT_EXPORT void Get_Partition_Statistics (Domain *, cxboolean, real *, real *);
FLUENT_EXPORT int Repartition_Cleared_Bit(Domain *, int, int);
FLUENT_EXPORT void Offset_Partition_Stored(Domain *, Thread *, int);
FLUENT_EXPORT void LoadBalance_Check(Domain *domain, int verbosity, const char *method);
FLUENT_EXPORT void Print_Partitions(Domain *domain,
                                    cxboolean use_stored_partition_p,
                                    int verbosity);
FLUENT_EXPORT cxboolean Check_Fluid_Cell_Deviation(Domain *domain);
FLUENT_EXPORT void Test_Remap_Partitions(Domain *domain);
FLUENT_EXPORT int Merge_Partition_Clusters(Domain *d, int n, int v, cxboolean w_h);
FLUENT_EXPORT int Smooth_Partition(Domain *d, int n, int v, cxboolean w_h);
FLUENT_EXPORT int Combine_Partition(Domain *d, int ncombine, int v);
FLUENT_EXPORT int Laplace_Smooth_Partition(Domain *, real, cxboolean,
                                           cxboolean, int);
FLUENT_EXPORT int Laplace_Partition(Domain *, real, int, int);
#if PARALLEL
FLUENT_EXPORT void Repartition_Banded_By_Cell_Type(Domain *, int);
#endif
FLUENT_EXPORT void Partition_Marked(Domain *, Objp *, int, int,
                                    cxboolean (*is_cell_marked_p)(cell_t, Thread *));
FLUENT_EXPORT int Encapsulate_Partition(Domain *, int, int,
                                        cxboolean (*ifGroup)(face_t, Thread *),
                                        cxboolean,
                                        int (*scaleWight)(face_t, Thread *, int));
FLUENT_EXPORT int Encapsulate_Coupled_Walls(Domain *, int, int, int);
FLUENT_EXPORT void Global_Sort_Real(real *array, int *index, int n);
FLUENT_EXPORT int Check_Parmetis_Data(metis_t *);
FLUENT_EXPORT int Group_Cells_Before_Write(Domain *domain);
FLUENT_EXPORT void Set_Have_Read_Owner_Cell_Ids();

#if RP_HANG
FLUENT_EXPORT void Partition_Parent_C(int, Domain *d);
FLUENT_EXPORT void Enforce_Parent_Child_Partition(int, Domain *);
#endif

#if RP_NODE
FLUENT_EXPORT void SI_Remigration_After_Adaption (Domain *domain);
FLUENT_EXPORT void Prepare_SI_Cells_Migration (Domain *domain);
FLUENT_EXPORT void Encapsulate_SI_Destination_Id (Domain *domain);
FLUENT_EXPORT void Fill_Face_Part_With_Same(Domain *d);
FLUENT_EXPORT void Fill_Node_Part_With_Same(Domain *d);
FLUENT_EXPORT void Fill_Face_Part_With_Different(Domain *d);
FLUENT_EXPORT int Fill_Node_And_Face_Part_With_Different(Domain *d, Objp **cl);
FLUENT_EXPORT void Fill_Node_Part_With_Different(Domain *d);
FLUENT_EXPORT void Assign_Local_Node_Part_Skip_Face_Zones(Domain *, Objp *);
FLUENT_EXPORT void Assign_Local_Node_Part(Domain *);
FLUENT_EXPORT void Fill_Node_And_Face_Part_Without_Shadows(Domain *, Objp **);

# if RP_EDGE
FLUENT_EXPORT void Fill_Edge_Part(Domain *d);
# endif
#endif
FLUENT_EXPORT int Local_Cluster_Domain(Domain *d, cxboolean w_h, cxboolean );
FLUENT_EXPORT int Global_Cluster_Domain(Domain *d, cxboolean w_h);

#define Fill_Face_Partitions Fill_Face_Part_With_Same /* until flowf.c modified */

#define C_PART_BIT_SET(c,t)C_STORAGE_BIT_SET(c,t,SV_C_PART_BIT)
#define C_PART_BIT_CLEAR(c,t)C_STORAGE_BIT_CLEAR(c,t,SV_C_PART_BIT)
#define C_PART_BIT(c,t)C_STORAGE_BIT_GET(c,t,SV_C_PART_BIT)

#define MAX_NUM_SUB_PARTITIONS 4096

#if !RP_HOST
FLUENT_EXPORT int Max_Partition(Domain *);
FLUENT_EXPORT int Max_Partition_S(Domain *);
#endif

FLUENT_EXPORT cxboolean Solid_Fluid_Weights_Defined(real *sweight, real *fweight);
#if !RP_NODE
FLUENT_EXPORT void Update_Cell_Thread_Weight(void);
#endif /* !RP_NODE */
FLUENT_EXPORT void Check_Cell_Thread_Weight(void);

#if PARALLEL
FLUENT_EXPORT void Partition_Dump(Domain *, char *, cxboolean,
                                  struct ccell *,
                                  struct vcell *,
                                  struct fcell *,
                                  struct fdata *,
                                  cxindex, cxindex, cxindex, cxindex);
FLUENT_EXPORT void Partition_Dump_new(char *const);

FLUENT_EXPORT void Partition_Graph(Domain *,
# if RP_NODE
                                   cxboolean
# else
                                   idxtype *, idxtype **, int **, int **, int *
# endif
                                  );

FLUENT_EXPORT void Replace_Partition(Domain *domain, Objp *del_cell_th_list);
FLUENT_EXPORT void dump_fill_loadvec(float *loadvec, int npart);
#endif

FLUENT_EXPORT void Partition_Cell_Count(Domain *,
#if RP_NODE
                                        int
#else
                                        int *
#endif
                                       );

FLUENT_EXPORT int Reorder_Partitions(Domain *, int method);

#if RP_NODE
FLUENT_EXPORT void Parallel_Sort_Real(real *local_block, int *global_position, int len);
FLUENT_EXPORT void Form_Cell_Groups(int *, int *, int *, int *, int, int );
FLUENT_EXPORT void cartesian_axes(Domain *, int, int, int);
#endif /* RP_NODE */

#if !RP_HOST
FLUENT_EXPORT void Cell_Count_After_Adaption(Domain *, int *, cxboolean);
#endif

FLUENT_EXPORT void Copy_Active_Part_To_Stored(Domain *, char *, int);
FLUENT_EXPORT void Copy_Active_Part_To_Dest  (Domain *, char *, int);
FLUENT_EXPORT void Copy_Active_Part_To_Owner (Domain *, char *, int);

FLUENT_EXPORT void Copy_Dest_Part_To_Owner   (Domain *, char *, int);
FLUENT_EXPORT void Copy_Dest_Part_To_Stored  (Domain *, char *, int);

FLUENT_EXPORT void Copy_Owner_Part_To_Stored (Domain *, char *, int);
FLUENT_EXPORT void Copy_Stored_Part_To_Dest  (Domain *, char *, int);

FLUENT_EXPORT int  Get_Active_Partition_Count(Domain *, char *, int);
FLUENT_EXPORT int  Get_Stored_Partition_Count(Domain *, char *, int);

FLUENT_EXPORT void Set_Active_Partition_Count(Domain *, int, char *, int);
FLUENT_EXPORT void Set_Stored_Partition_Count(Domain *, int, char *, int);
FLUENT_EXPORT void Initialize_Partition_ID(Domain *);
FLUENT_EXPORT void Encapsulate_Migrate_Cells_with_Multiple_Shadow_Nodes(Domain *domain);
FLUENT_EXPORT int Encapsulate_Node_Pairs(Domain *, cxboolean, cxboolean);
FLUENT_EXPORT double get_scaled_weights(Domain *domain,
                                        cxboolean use_stored_partition_p,
                                        int with_host, int *inpart, int *inwm,
                                        double **itw, int **iwuse);
FLUENT_EXPORT void Cell_Weights(Domain *domain);
FLUENT_EXPORT cxboolean If_Hex_Core_Mesh(Domain *domain, cxboolean for_dump);
FLUENT_EXPORT cxboolean If_Encapsulate_Hex_Core(void);
FLUENT_EXPORT int Multicore_Remap(Domain *, int *, cxboolean, cxboolean);
FLUENT_EXPORT int Get_Machine_Number(int *, int *, void *);

FLUENT_EXPORT void eigenvectors(real [][ND_ND], real [][ND_ND], real [ND_ND]);

FLUENT_EXPORT int Partition_Bands_For_SV(Domain *, Svar, real, int, int,
                                         int *, int *, cxboolean);
FLUENT_EXPORT void save_stored_partition(Svar, Domain *);
FLUENT_EXPORT void recover_saved_partition_skip_marker(Svar, Domain *, int);
FLUENT_EXPORT void copy_cell_svar_skip_marker(Svar, Svar, Domain *, int);
FLUENT_EXPORT int dem_hybrid_partition_pair(Objp **op, int nparts, int n_cc,
                                            int *load_vec, int verbosity,
                                            int part_method);
FLUENT_EXPORT int set_c_metis_index(int *pcounter, Thread *t, Domain *domain, int marked);

FLUENT_EXPORT Thread *get_root_parent(cell_t, Thread *, cell_t *);
FLUENT_EXPORT void Print_Additional_Partition_Statistics(Domain *domain, cxboolean use_stored_partition_p, int verbosity);

FLUENT_EXPORT void Fill_Partition_Export_Functions(void);

#if RP_NODE
FLUENT_EXPORT void compute_send_recv_counts(int *nsend, int *nrecv, int count, int *nsend_total, int *nrecv_total);
FLUENT_EXPORT void create_displacement_array(int *nsend, int *nrecv, int **sdispls, int **rdispls, int count);
FLUENT_EXPORT void scale_and_swap_send_recv_arrays(int *nsend, int *nrecv, int count, int scale);
#endif

/* update the resource stack size using setrlimit */
#if sys_linux && RP_NODE
void Update_Stack_Size(size_t new_size);
#endif


#endif /* _FLUENT_PART_H */
