/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_AMG_H
#define _FLUENT_AMG_H


#include "dll.h"
#define NULL_INDEX  -1
#define CHILD_NONE 0
#define MAX_N_SETS  10
#define MAX_SIM_EQ  81   /* 1 + 4*MAX_PHASES for nphase full coupled MP */
#define MAX_OVERLAP     2

#if RP_DOUBLE
#define AMG_SMALL 1.e-20
#else
#define AMG_SMALL 1.e-10
#endif


#define USE_ILU   1

#ifndef AMG_CHUNKED_MEMORY
#define AMG_CHUNKED_MEMORY 1
#endif
#if AMG_CHUNKED_MEMORY
typedef struct coeff_mem_t_
{
  /* segragated */
  real *s_d;
  real **s_dp;
  int s_d_size;
  real *s_value;
  real **s_valuep;
  int s_value_size;
  /* coupled */
  real *c_d;
  real **c_dp;
  int c_d_size;
  real *c_value;
  real **c_valuep;
  int c_value_size;
} coeff_mem_t;
#endif

#define SYSTEM_NAME_LEN 128
#define MAX_LEVELS  50

typedef struct Matrix
{
  char system_name[SYSTEM_NAME_LEN]; /* name of the linear system */
  int tot_size;     /* # of simultaneous equations             */
  int size;     /* # of solved simultaneous equations      */
  int n_coeffs;     /* # of off-diagonal coefficients          */
  int n_ceqn;     /* # of coupled equations        */

  real *PTR_RESTRICT d;   /* matrix diagonal coefficients (size)     */
  real *PTR_RESTRICT value;   /* off-diagonal coefficients  (n_coeffs) */
  int *PTR_RESTRICT row;  /* row start pointers     (size + 1) */
#if RP_AMG_SM
  int *PTR_RESTRICT row_u;  /* row start pointers     (size + 1) */
#endif
  int *PTR_RESTRICT col;  /* column indices     (n_coeffs) */
  int *PTR_RESTRICT nconn;      /* number of connections        (n_coeffs) */
  real *PTR_RESTRICT accum_weight;
  real *PTR_RESTRICT store_weight;
#if OVERSET_NUMERICS
  real *PTR_RESTRICT work;      /* overset receptor/dead/neighbor mask     */
  size_t work_size;             /* current allocated size of work vector   */
#endif

  size_t d_size;    /* current allocated size of d vector      */
  size_t value_size;    /* current allocated size of value vector  */
  size_t row_size;    /* current allocated size of row vector    */
#if RP_AMG_SM
  size_t row_u_size;    /* current allocated size of row vector    */
#endif
  size_t col_size;    /* current allocated size of col vector    */
  size_t nconn_size;            /* ""                        nconn vector  */
  size_t accumw_size;
  size_t storew_size;
  /* SAMG data */
  int nRows;
  int nCols;
  cxboolean store_d;

#if AMG_CHUNKED_MEMORY
  real **PTR_RESTRICT valuep;
  real **PTR_RESTRICT dp;
  real **PTR_RESTRICT Ep;
  coeff_mem_t sc;
#else
  int SQRn_ceqn;
#endif
  real *y;
  real *r;
  real *z;
  size_t y_size;
  size_t r_size;
  size_t z_size;

  int *PTR_RESTRICT neighb;   /* neighbor column indices  (n_coeffs) */
  size_t neighb_size;

#if RP_AMG_LAPLACE_C
  real *lcoeff;          /* LAPLACE coefficients */
  size_t lcoeff_size;
#endif
#if OVERSET_NUMERICS
  cxboolean press_corr_p;      /* flag indicating segregated system pressure correction system */
  int  my_level_id;            /* level is the matrix associated  */
  struct Matrix *myC;
#endif
}
Matrix;


typedef struct Table
{
  int *size[MAX_OVERLAP]; /* number of equations       (n_neighbors) */
  int **map[MAX_OVERLAP]; /* equation indices    (n_neighbors, size) */
}
Table;


typedef struct System
{
  int n_overlap;                /* # of exterior layers                    */
  int n_neighbors;    /* # of neighbors                          */
  int n_neighbors_o;    /* # of neighbors                          */
  int n_compute_nodes;          /* # of compute nodes                      */
  int n_cells;                  /* # of cells in my compute node           */
  int my_id;      /* multiport id                            */
  int *nb_id;                   /* multiport id of neighbor  (n_neighbors) */
  Table intr;     /* interior table                          */
  Table extr;     /* exterior table                          */
  int *local;                   /* the local neighbor id                   */
  int *remote;                  /* the remote neighbor id                  */
  int level;
  int part;
  int hlevel;
#if RP_NODE
  void *e;                      /* the exchange buffer related */
#endif
}
System;


#if  RP_AMG_DO
# include "mem.h"
#endif

typedef enum
{
  AMG_STORE_X = 0,
  AMG_STORE_Y,
  AMG_STORE_T,
  AMG_STORE_B,
  AMG_STORE_D,
  AMG_STORE_E,
  AMG_STORE_VALUE,
  AMG_STORE_COL,
  AMG_STORE_ROW,
  AMG_STORE_CHILD,
  AMG_STORE_MAPU,
  AMG_STORE_MAPD,
  AMG_STORE_MAX
} amg_store_enum_t;

typedef struct amg_store_t_
{
  void **store;
  size_t *size;
  SV_Dimension dimension;
  int *neq;
} amg_store_t;

typedef struct Level
{
  int n_sets;     /* number of sets of equations             */
  int coarsen_on[MAX_N_SETS]; /* equation to coarsen on in each set      */
  int set[MAX_N_SETS + 1];  /* set limit equation indices              */
  int set_interface_start[MAX_N_SETS];  /* set inerface index start        */

#if OVERSET_NUMERICS
  Matrix C;                     /* receptor cell coefficients  */
#endif
  System s;     /* neighbor overlap information            */
  Matrix A;     /* coefficient matrix                      */
  real *PTR_RESTRICT E;   /* inverse diagonal of ILU decomposition   */
  real *PTR_RESTRICT x;   /* solution vector                         */
  int xzero;                    /* flag to specify: 0 for x==0 1 otherwise */
  real *PTR_RESTRICT b;   /* right hand side vector                  */
  real *PTR_RESTRICT t;   /* right hand side vector                  */
  int *PTR_RESTRICT child;  /* coarse level child index                */

  int flex_sweeps;    /* number of flexible cycle sweeps         */
  size_t x_size;    /* current allocated size of x vector      */
  size_t b_size;    /* current allocated size of b vector      */
  size_t t_size;    /* current allocated size of b vector      */
  size_t child_size;    /* current allocated size of child vector  */
  size_t e_size;    /* current allocated size of E vector      */

#if RP_AMG_DO
  int *cindex;
  size_t cindex_size;
  cat_t *parents;
  int *parent_start;
  size_t parents_size;
  size_t parent_start_size;

  fat_t *bfaces;
  int *bface_start;
  size_t bfaces_size;
  size_t bface_start_size;

  fat_t *ifaces;
  int *iface_start;
  size_t ifaces_size;
  size_t iface_start_size;
  real (*iface_area)[ND_ND];
  size_t iface_area_size;

  real **I;
  real **Ib;
  int I_len0, I_len1;
  int Ib_len0, Ib_len1;

  real **a_term;
  real **e_term;
  real **s_term;
  int aterm_len0, aterm_len1;
  int eterm_len0, eterm_len1;
  int sterm_len0, sterm_len1;
#endif

  /* SAMG data */
  Matrix P;
  int *order;
  struct Level *next;

  /* reorder */
  cat_t *reorder_index;
  int nreorder_index;

  /* the stores */
  amg_store_t *store;
  int nstore;

  /* the cross level related data */
  void *cross;
  int ilevel;

  /* optimization
   * can skip the initial residual computation */
  cxboolean delta_form_p;
}
Level;

typedef enum
{
  FLUENT_SOLVER_FVM = 0,
  FLUENT_SOLVER_FEA = 1
}
AMG_Solver_Mode;

typedef enum
{
  FLEXIBLE_CYCLE = 0,
  V_CYCLE = 1,
  W_CYCLE = 2,
  F_CYCLE = 3
}
AMG_Cycle_Type;


typedef enum
{
  SMOOTHER_JACOBI,
  SMOOTHER_GAUSS_SEIDEL,
  SMOOTHER_ILU
}
AMG_Smoother_Type;

typedef enum
{
  METHOD_AGGREGATIVE,
  METHOD_SELECTIVE
}
AMG_Method;

typedef enum
{
  SOLVE_STATUS_NORMAL,
  SOLVE_STATUS_GLOBAL,
  SOLVE_STATUS_HYBRID,
  SOLVE_STATUS_HYBRID_GLOBAL,
  SOLVE_STATUS_GROUP,
  SOLVE_STATUS_FINAL
}
AMG_Solve_Status;

typedef enum amg_grouping_method_e
{
  AMG_GROUPING_TRADITIONAL = 0,
  AMG_GROUPING_LARGE_GROUP_SIZE,
  AMG_GROUPING_GREEDY,
  AMG_GROUPING_GREEDY_FLUX,
  AMG_GROUPING_GREEDY_NEW
}
AMG_Grouping_Method;

typedef struct AMG_Controls
{
  int sys_id;

  /* Equation controls. */
  int scale_corrections;
  int scale_filter;
  AMG_Cycle_Type cycle_type;
  double termination_epsilon;
  double restriction_epsilon;
  double divergence_epsilon;
  double tolerance;

  /* Coarsening parameters. */
  int max_levels;
  int group_size;
  int level_group_size[MAX_LEVELS];
  int min_group_size;
  AMG_Grouping_Method group_method;
  AMG_Grouping_Method group_method_fallback;
  cxboolean greedy_force_nonsymmetric;
  cxboolean map_neighb;
  int coarsening_assume_symmetry;
  cxboolean grouping_check_self;
  cxboolean grouping_check_exterior;
  double grouping_check_exterior_scale;
  int grouping_stop_method;

  /* Fixed cycle parameters. */
  int pre_sweeps;
  int post_sweeps;
  int min_cycles;
  int max_cycles;
  cxboolean cont_positive;

  /* Flexible cycle parameters. */
  int max_coarse_sweeps;
  int max_fine_sweeps;
  int smoother_sweeps;

  /* Options. */
  int verbosity;
  int smoother;
  int sweep_exchange;
  int global_solve;
  int global_solve_optimization;
  int in_global_solve;
  int in_global_coarsening;
  int ignore_slow_communication;
  int force_slow_communication;
  int machine_count;
  double ilu_seg_relax;
  double ilu_cpl_relax;
  int ilu_relax_method;
  int save_temps;
  int v5;
  int method; /* aggregative or selective */
  cxboolean dd_diagnostics;
  cxboolean residual_record;

  /*Smoother options*/
  cxboolean sweep_partition_interface;
  double smoother_under_relax_factor;

  /* Memory */
  double malloc_oversize_percent;
  size_t memory_chunk_size;
  int memory_chunk_use;

  /* Global solve parameters */
  int global_residual;
  int check_global_solution;
  int max_global_cycles;
  int global_solve_type; /* 0 - global solve before fixed cycle
                          * 1 - global solve only once per cycle
                          * 2 - global solve for every sub cycle
                          */
  /* solve status */
  AMG_Solve_Status solve_status;
  int use_hybrid;
  int use_hybrid_optimization;
  int use_hierarchy;
  int repeat;
  cxboolean protective_enhanced;
  int stall_cycle;
  cxboolean early_protection;
  int stall_iter;
  real stall_rate;
  int diverge_iter;
  real diverge_rate;
  int global_master_dist; /* 0 - as apart as possible (default)
                           * 1 - as close as possible
                           */
  /* resuse */
  int precondition_reuse;  /* control to reuse in precondition:
                            * 0 - re-create coarse levels everytime
                            * 1 - Keep using the coarse levels (all levels local, hybrid or global) and reuse the ILU_Decomposition
                            */
  int reuse;  /* 0 - re-create coarse levels everytime
               * 1 - Keep using the coarse levels (all levels local, hybrid or global) and reuse the ILU_Decomposition
               */

  /* the 2/3 rule of coarsening, whether checked globally */
  int global_check_coarsening;

  /* check for preset child */
  int child_preset; /* 0 - no partitions with all preset
                     * 1 - my partition is all preset
                     * 2 - all partions are preset
                     */

  /* second layer of protection/stabilization */
  cxboolean stabilization_protection; /* protect the stabilization if fails */
  cxboolean solver_protection;        /* protect any solver if fails Now for CG and BCGSTAB */
  int solver_protection_method;       /* solver"amg-stabilization" used as 2nd layer of protection */
  cxboolean use_solver_protection;    /* switch to indicate that the 2nd layer layer of protection is activated */

  /* use cross partition coarsening */
  int cross;

  /* use overlap communication and computation */
  int overlap_cc;

  cxboolean udsmootherilu;
  cxboolean udsmoothergs;
  cxboolean udlinearsolver;
}
AMG_Controls;

extern FLUENT_EXPORT void Setup_Equation_Grouping(AMG_Grouping_Method,
                                                  AMG_Controls *);

typedef struct AMG_Methods
{
  void (*ILU_Decomposition)        (Matrix, real []);
  int  (*Make_Coarse_Level)        (Level *, int);
  int  (*Group_Equations)          (Level *, Level *);
  void (*Init_Overlap_Tables)      (Level *, Level *);
  void (*Restrict_Overlap_Table)   (int, int, int *, Table *, Table *);
  void (*Localize_Child_Numbering) (System *, int *, int *);
  int  (*Restrict_Matrix)          (Level *, Level *);
} AMG_Methods;

#if RP_AMG_LAPLACE_C
typedef struct amg_laplace_t_
{
  /* the current sys_id */
  int sys_id;
  /* this is the indicator for having any laplace coarsening
     for either scalar or coupled systems */
  cxboolean on;
  /* if grouping is done at fine level*/
  cxboolean child_saved[AMG_MAX_SYSTEMS];
  /* see if need to do regrouping, first set in make fine level,
     then double checked in make coarse level */
  cxboolean regroup[AMG_MAX_SYSTEMS];
  /* the basice indicator for whether use laplace coarsening */
  cxboolean enable[AMG_MAX_SYSTEMS];

  /* remember the fine level child */
  int *child[AMG_MAX_SYSTEMS];
  /* the fine level child size */
  size_t child_size[AMG_MAX_SYSTEMS];
  /* to see if in coarsening of global levels */
  cxboolean in_global_coarsening;
} amg_laplace_t;
#endif /* #if RP_AMG_LAPLACE_C */

#if RP_NODE
/* Declarations for parallel timers. */
extern FLUENT_EXPORT int par_amg_cycle_count;
extern FLUENT_EXPORT int par_amg_sweep_count;
extern FLUENT_EXPORT int par_amg_exchange_count;
extern FLUENT_EXPORT int par_amg_global_solve_count;
extern FLUENT_EXPORT double par_amg_global_solve_time;
extern FLUENT_EXPORT int par_amg_solve_count;
extern FLUENT_EXPORT double par_amg_solve_time;
extern FLUENT_EXPORT int par_amg_global_matrix_size;
extern FLUENT_EXPORT int par_amg_diverged_count;
extern FLUENT_EXPORT int par_amg_diverged_recovered_count;
extern FLUENT_EXPORT int amg_early_protection_stage1_count;
extern FLUENT_EXPORT int amg_early_protection_stage2_count;
#endif /* RP_NODE */

FLUENT_EXPORT void AMG_Get_Residual(Matrix *A, real *x, real *b, real *t, real residual[], int n_ceqn);
FLUENT_EXPORT void AMG_Get_Residualg(Matrix *A, real *x, real *b, real *t, real residual[], int n_ceqn);
FLUENT_EXPORT int Smoother_Solve(AMG_Controls controls, Level fine, real residual0[]);
FLUENT_EXPORT int AMG_Solve(AMG_Controls controls, Level fine, real residual0[]);
FLUENT_EXPORT int SAMG_solve(AMG_Controls *amgC, Level *f, real residual0[]);

FLUENT_EXPORT Level *Make_All_Coarse_Levels(AMG_Controls controls, Level fine);
FLUENT_EXPORT void Fixed_Cycle(Level *PTR_RESTRICT level, int m, int cycle_type,
                               int invoke_globle_solve, int invoke_exchange);
FLUENT_EXPORT int Equation_Coarse_Level_Index(int id, int n);

FLUENT_EXPORT void *Resize_Vector_AMG(void **v, size_t *allocated_size,
                                      size_t required_size,
                                      int resize,
                                      char *file, int line);

FLUENT_EXPORT void *Resize_Vector_Chunk_AMG(void **v, size_t *allocated_size,
                                            size_t required_size, Matrix *A,
                                            int cont, int resize,
                                            char *file, int line);
FLUENT_EXPORT void Free_Chunk_Memory_AMG (Matrix *A);

#define Resize_Vector(v, allocated_size, required_size) \
  Resize_Vector_AMG((void **)(&(v)), (allocated_size), (required_size), 1,\
        __FILE__, __LINE__)

#define Resize_Vector_Chunk(v, allocated_size, required_size, A, cont)  \
  Resize_Vector_Chunk_AMG((void **)(&(v)), (allocated_size), (required_size), &(A), cont, \
        1, __FILE__, __LINE__)

#if AMG_CHUNKED_MEMORY
typedef struct amg_mem_head_t_
{
  char cont;
  char use_chunk;
  short n_ceqn;

  real **p;
  void *manager;
  size_t chunk_size;
  size_t p_size;
} amg_mem_head_t;
#ifndef AMG_CHUNKED_MEMORY_E
#define AMG_CHUNKED_MEMORY_E 1
#endif
extern int size_of_amg_mem_head;
#define A_VALUEP(B,i) ((B).valuep[i])
#define A_DP(B,i) ((B).dp[i])
#if AMG_CHUNKED_MEMORY_E
#define A_EP(_E_,i,SQRn_ceqn) ((((amg_mem_head_t *)     \
         ((char *)(_E_)-size_of_amg_mem_head))->p)[i])
#else
#define A_EP(_E_,i,SQRn_ceqn) ((_E_)+ (i)*SQRn_ceqn)
#endif
#else
#define A_VALUEP(B,i) ((B).value + (i)*(B).SQRn_ceqn)
#define A_DP(B,i) ((B).d + (i)*(B).SQRn_ceqn)
#define A_EP(_E_,i,SQRn_ceqn) ((_E_)+ (i)*SQRn_ceqn)
#endif

#define ZERO_A_VALUEP(B,i)      \
  if(1 == (B).n_ceqn)       \
    *(A_VALUEP((B),i)) = 0.0;     \
  else            \
    {           \
      real * PTR_RESTRICT _r = A_VALUEP((B),i); \
      int _n = SQR((B).n_ceqn);     \
      int _i;         \
      for(_i=0;_i<_n;_i++)      \
  _r[_i] = 0.0;       \
    }

#define ZERO_A_DP(B,i)        \
  if(1 == (B).n_ceqn)       \
    *(A_DP((B),i)) = 0.0;     \
  else            \
    {           \
      real * PTR_RESTRICT _r = A_DP((B),i); \
      int _n = SQR((B).n_ceqn);     \
      int _i;         \
      for(_i=0;_i<_n;_i++)      \
  _r[_i] = 0.0;       \
    }

#define get_amg_local_buf(required_size)        \
  (amg_local_buf = Resize_Vector_AMG(&amg_local_buf, &amg_local_buf_size, (required_size), 1, __FILE__, __LINE__))
#define free_amg_local_buf(p)

#if RP_NODE
FLUENT_EXPORT void Reset_Parallel_AMG_Timers(void);
FLUENT_EXPORT void Get_Parallel_AMG_Timers(int *cycles,
                                           int *sweeps,
                                           int *exchanges,
                                           int *global_solve_count,
                                           double *global_solve_time,
                                           int *solve_count,
                                           double *solve_time,
                                           int *global_matrix_size,
                                           int *early_protection_stage1_count,
                                           int *early_protection_stage2_count);
FLUENT_EXPORT void AMG_Exchange(System *, int, void *, int);
FLUENT_EXPORT void Exchange_Solution(System *, int, real *);
FLUENT_EXPORT void Exchange_Indices(System *, int array[]);
FLUENT_EXPORT int Need_Exchange_Solution (System *, int, int);
FLUENT_EXPORT void alloc_solution_exchange_buffers(System *s, int n_ceqn);

#endif /* RP_NODE */

FLUENT_EXPORT int Malloc_Additional_Smoother_Memory(AMG_Controls *, Level *);
FLUENT_EXPORT void Allocate_Level_Array(AMG_Controls *);
#if RP_AMG_V5
# include "amg_v5.h"
#endif


/* BCGSTAB */
typedef enum
{
  STABILIZATION_NONE,
  STABILIZATION_BCGSTAB,
  STABILIZATION_RPM,
  STABILIZATION_CG,
  STABILIZATION_GMRES
} AMG_Stabilization;

void freeLevels(Level *f);
void destroy_coarse_levels (cxboolean regroup);
FLUENT_EXPORT void Destroy_All_Coarse_Levels(int sys_id);
FLUENT_EXPORT void Init_AMG_Status(void);
FLUENT_EXPORT void Disable_Laplace_Coarsening_Regrouping(int sys_id);
FLUENT_EXPORT int Make_DO_Coarse_Level(Level   *PTR_RESTRICT level, int m);

#  define AMG_MALLOC(x) offset_malloc((x), __FILE__, __LINE__)
#  define AMG_REALLOC(x,y) offset_realloc((x), (y),__FILE__, __LINE__)
#  define AMG_CALLOC(x,y) offset_calloc((x), (y),__FILE__, __LINE__)
#  define AMG_FREE(x) offset_free((x), __FILE__, __LINE__)

extern amg_laplace_t amg_laplace;
FLUENT_EXPORT int make_coarse_level_wrapper(Level *, int, AMG_Controls *);
FLUENT_EXPORT Level *Get_AMG_Level_Array(void);
extern int is_nan(real f);

FLUENT_EXPORT void Fill_Neighbor_Map(Matrix *A);

#if RP_NODE
void Set_UD_Smoother_Context(int ilvst, int ilvnd, int status, int which_smoother);
#endif
FLUENT_EXPORT void Get_User_Defined_Smoother(char *info, int which_smoother);
FLUENT_EXPORT void Get_User_Defined_Linear_Solver(int sys_id, char *info);
#endif /* _FLUENT_AMG_H */
