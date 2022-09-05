/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLTG_MEM_H
#define _FLTG_MEM_H

#ifndef LEAN_MEM_TEST
#define LEAN_MEM_TEST 0
#endif


#include "entity.h"   /* Node */
/* #include "mem.h" */   /* Domain */
/* This doesn't work, because mem.h includes this file.
 * --> must make sure that mem.h has been included before this
 * file is included, and include mem.h where this file is needed:
 */
#ifndef _FLUENT_MEM_H
# error Must include mem.h to include mem_grid.h
#endif
#if USE_FEMCORE
#include "inz_manager.h"
#endif


typedef struct objp_struct Objp;

typedef int face_t;
#if (sys_irix65 || sys_irix65_mips4 || sys_irix65_mips4_64)
typedef int fluent_cell_t;
# define cell_t fluent_cell_t
#else
typedef int cell_t;
#endif

#if USE_FEMCORE
typedef int interpolation_node_t;
#endif
typedef struct face_and_thread_struct
{
  face_t f;
  struct thread_struct *t;
} fat_t;

typedef struct cell_and_thread_struct
{
  cell_t c;
  struct thread_struct *t;
} cat_t;

typedef struct c_t_struct
{
  struct cell_and_thread_struct ct;
  struct c_t_struct *next;
} ct_struct;


typedef struct face_child_and_parent_struct
{
  cxindex child;
  cxindex parent;
} fcap_t;

#if RP_NODE
typedef union cell_or_face_union
{
  cell_t c;
  face_t f;
} cf_t;

#if NEW_PARALLEL_NEIGHBOR
typedef struct thread_neighbor_struct
{
  int id; /* multiport id of neighbor */
  int depth; /* number of entity layers */

  union
  {
    int asInt;
  } n1;

  int *interior_count;
  int *exterior_count;
  int interface_count;

  union cell_or_face_union **interior; /* array of 1d arrays,
                                            [layer index][entity index] */
  union cell_or_face_union **exterior; /* array of 1d arrays,
                                            [layer index][entity index] */
  face_t *interface;                   /* 1d array, [entity index] */

  struct thread_neighbor_struct *next;
} Thread_Neighbor;

#define NEIGHBOR_INDEX(n) ((n)->n1.asInt)

typedef struct domain_neighbor_struct
{
  int id; /* multiport id of neighbor */

  struct domain_neighbor_struct *next;
} Domain_Neighbor;

#endif /* NEW_PARALLEL_NEIGHBOR */

typedef struct dom_neighbor_struct
{
  /* phasing out */
  int tmp1;
  int tmp2;

  int interior_cell_count;
  int exterior_cell_count;
  int interface_face_count;
  int interface_face_shadow_count;
#if RP_HANG
  int parent_interior_cell_count;
  int parent_exterior_cell_count;
  int parent_interface_face_count;
# if RP_EDGE
  int interface_edge_count;
  int corner_edge_count;
  int parent_interface_edge_count;
  int parent_corner_edge_count;
# endif
#endif
  int helper_interface_face_count;
  int exterior_face_count;
  int interior_bface_count;
  int exterior_bface_count;
  int interface_node_count;
  int corner_node_count;
  int exterior_node_count;
  int boundary_interface_node_count;
  int boundary_corner_node_count;
  cxindex sendbuf_size;
  cxindex recvbuf_size;

  struct objp_struct *int_cl;
  struct objp_struct *ext_cl;
  struct objp_struct *iface_fl;
  struct objp_struct *iface_shadow_fl;
#if RP_HANG
  struct objp_struct *parent_int_cl;
  struct objp_struct *parent_ext_cl;
  struct objp_struct *parent_iface_fl;
# if RP_EDGE
  struct objp_struct *iface_el;
  struct objp_struct *corner_el;
  struct objp_struct *parent_iface_el;
  struct objp_struct *parent_corner_el;
# endif
#endif
  struct objp_struct *helper_iface_fl;
  struct objp_struct *ext_fl;
  struct objp_struct *int_bfl;
  struct objp_struct *ext_bfl;
  struct objp_struct *iface_vl;
  struct objp_struct *corner_vl;
  struct objp_struct *ext_vl;
  struct objp_struct *boundary_iface_vl;
  struct objp_struct *boundary_corner_vl;

  /* complete lists */
  struct objp_struct *ext_cl_ext;
  struct objp_struct *int_cl_ext;
  struct objp_struct *ext_fl_ext;
  struct objp_struct *int_fl_ext;
  struct objp_struct *ext_vl_ext;
  struct objp_struct *int_vl_ext;
  struct objp_struct *int_vl_src;  /* Structure nci */
  struct objp_struct *ext_vl_src;  /* Structure nci */
  struct objp_struct *parent_ext_cl_ext;
  struct objp_struct *parent_int_cl_ext;

  /* complete list counts */
  int exterior_cell_count_ext;
  int interior_cell_count_ext;
  int exterior_face_count_ext;
  int interior_face_count_ext;
  int exterior_node_count_ext;
  int interior_node_count_ext;
  int parent_exterior_cell_count_ext;
  int parent_interior_cell_count_ext;
  int interior_node_src_count;    /* Structure nci */
  int exterior_node_src_count;    /* Structure nci */

#if RP_OVERSET
  /* Overset interface faces */
  int overset_send_interface_face_count;
  int overset_recv_interface_face_count;
  struct objp_struct *overset_send_iface_fl;
  struct objp_struct *overset_recv_iface_fl;

  /* Overset exterior donors */
  int overset_int_donor_cell_count;
  int overset_ext_donor_cell_count;
  struct objp_struct *overset_int_donor_cl;
  struct objp_struct *overset_ext_donor_cl;

  /* Overset exterior receptors */
  int overset_int_receptor_cell_count;
  int overset_ext_receptor_cell_count;
  struct objp_struct *overset_int_receptor_cl;
  struct objp_struct *overset_ext_receptor_cl;

# endif

  char *sendbuf;
  char *recvbuf;
  struct injection_struct *dpm_Ip[2]; /* 0: outgoing, 1: incoming */
  void *send_elements; /* parallel element list like (Particle*) with a pointer to the (->next) */
  void *recv_elements; /* element list like (Particle*) */
  char *dpm_sendbuf, *dpm_recvbuf;    /* send/recv buffers */
  int   dpm_sendbuf_size[2];          /* 0: size in bytes/reals, 1: TRUE (!=0), if another chunk required later */
  int   dpm_recvbuf_size[2];          /* as above */
  int   dpm_sendbuf_allocd;           /* allocated buffer size */
  void *first_send_element;
  void *last_recv_element;

  /* send/recv buffers, they are volatile, no persistency
   * should be set the size, allocate them, use them, and free them
   */
  struct exchange_buffer_t
  {
    int valid;

    void *send;
    void *recv;

    size_t send_size;
    size_t recv_size;
  } exchange_buffer;
} Dom_Neighbor;

# define VALID_NEIGHBOR_P(neigh)                                        \
    ((!NULLP(neigh)) &&                                                 \
     ((neigh)->exterior_cell_count > 0 || (neigh)->interior_cell_count > 0))
#define VALID_NEIGHBOR_EXT_P(neigh) ( (!NULLP(neigh)) &&                       \
                                      ((neigh)->exterior_cell_count > 0     || \
                                       (neigh)->interior_cell_count > 0     || \
                                       (neigh)->exterior_cell_count_ext > 0 || \
                                       (neigh)->interior_cell_count_ext > 0 || \
                                       NNULLP((neigh)->iface_vl)            || \
                                       NNULLP((neigh)->iface_fl)            || \
                                       NNULLP((neigh)->corner_vl)) )
# define VALID_BF_NEIGHBOR_P(neigh)                                     \
    ((!NULLP(neigh)) &&                                                 \
     ((neigh)->interior_bface_count > 0 || (neigh)->exterior_bface_count > 0))
# define VALID_CORNER_NEIGHBOR_P(neigh) ((neigh)->corner_node_count > 0)
# define NEIGHBOR_SEND_COUNT(n) (n)->tmp1
# define NEIGHBOR_RECV_COUNT(n) (n)->tmp2
# define NNEIGHBOR(d,n) ((((d)->neighbors)+n))
# define neighbor_loop(neigh,d,n)                           \
    for (n=0,neigh=(d)->neighbors;                          \
         !NULLP((d)->neighbors) && n<compute_node_count;    \
         n++,neigh++)

#if 1

# define fast_neighbor_loop_begin(neigh,d,n)                            \
  { int __ipe;                                                          \
    int __nneighbors = (d)->valid_neighbors_ready?                      \
      (d)->n_valid_neighbors:compute_node_count;                        \
    for (__ipe = 0;  !NULLP((d)->neighbors) && __ipe < __nneighbors; __ipe++){ \
      n = (d)->valid_neighbors_ready?(d)->valid_neighbors[__ipe]:__ipe; \
      neigh = &(d)->neighbors[n];                                       \
      {

# define fast_neighbor_loop_end(neigh,d,n) }}}

#else /* 1 */

extern FLUENT_EXPORT int *exchange_order;
# define fast_neighbor_loop_begin(neigh,d,n)                            \
    { int neigh##_count=0;                                              \
    if (exchange_order != NULL && (d) != NULL && (d)->neighbors != NULL) \
        for (neigh##_count=0,n=exchange_order[0],neigh=&((d)->neighbors[exchange_order[0]]); \
             exchange_order[neigh##_count]>=0 && !NULLP(&((d)->neighbors[n])) && neigh##_count<compute_node_count; \
             n=exchange_order[++neigh##_count], neigh=&((d)->neighbors[n])) {
# define fast_neighbor_loop_end(neigh,d,n) }}

#endif /* 1 */
#endif /* RP_NODE */

/* move the definition from amgif.h to here, and also lowering
   the max user systems to 2 */
#define AMG_MAX_USER_SYSTEMS 2
typedef enum
{
  AMG_NONE = -1,
  AMG_PVT = 0,
  AMG_SCALAR,
  AMG_PISO,
  AMG_SCALAR_FLAT,
  AMG_LAST, /* new systems should be added before AMG_LAST */
  AMG_MAX_SYSTEMS = AMG_LAST + AMG_MAX_USER_SYSTEMS
} AMG_System_Type;

/* US168773 - MAX_PHASES and MAX_SUB_DOMAINS is now defined in materials.h */

#define MAX_LAYER 2
# if RP_HANG
#  define N_LAYER (2*(MAX_LAYER+1))
# else
#  define N_LAYER (MAX_LAYER+1)
# endif
#define LAYER_INTERFACE -1
#define LAYER_INTERIOR 0
#define LAYER_PRIMARY 1
#define LAYER_SECONDARY 2

#define COMPACT_STORAGE_ARRAY 1
#define STORAGE_SHORTCUTS 1   /*  ( ! DEBUG)  --- not needed with the *named* SV_Shortcut enum */

#ifndef ALLOCATE_STORAGE_ARRAY_DYNAMIC
#define ALLOCATE_STORAGE_ARRAY_DYNAMIC 0
#endif

#ifndef ALLOCATE_STORAGE_ARRAY_ON_DEMAND
#define ALLOCATE_STORAGE_ARRAY_ON_DEMAND ALLOCATE_STORAGE_ARRAY_DYNAMIC
#endif

#define SET_STORAGE_NULL(_t, _v) if(NNULLP(_t) && NNULLP((_t)->storage))\
    THREAD_STORAGE(_t, _v) = NULL
#define SET_STORE_NULL(_t, _v) if(NNULLP(_t) && NNULLP((_t)->store))\
    THREAD_STORE(_t, _v) = NULL

#if RP_FC
typedef struct domain_fourier_decomposition
{
  cxboolean exists;
  cxboolean zero_fcset;
  int fcset[2];
  int nfreq;
  int nicfc;
  int ntstepc;
  int scale;
  int *ifreqr;
  int *facta;
  real efact;
  real factc;
  real errs;
  real *tshift;
  real *rfreq;
  real *coefa;
  real *coefb;
  real *costa;
  real *sinta;
  real **costr;
  real **sintr;
  Thread *tc;
} dom_fourier_d;
#endif

/*
 * MAX_NAME_LENGTH constrained by cortex (????)
 * for displaying thread by name
 */
#define MAX_NAME_STRLEN 255
#define MAX_NAME_LENGTH 256
#define MAX_STORAGE_ARRAY_SIZE SV_MAX/10

struct thread_struct
{
  void *head;
  int element_type; /* bits 1-6: topological types, see enum's in entity.h
                       bit    7: boundary layer flag
                       bit    8: Cartesian flag */

#if RP_GEOM
  struct geom_struct
  {
    union
    {
      void *bgMesh;
      long bgMeshId;
    } bg;

    int geom_thread;
    int geomflags; /* geometry related flags */
    double dir[3];  /* direction of projection */
    int levels; /* levels of deformation propogation */

    void (*Node_Projection_Function)(int);
  } geometry;

#endif

  char name[MAX_NAME_LENGTH];

  int sv_length; /* number of elements allocated on thread */
  int nelements; /* number of existing elements on thread */
  int t_itmp;
#if RP_NODE
  int nelements_in_layer[N_LAYER]; /* [0] - interior
                                        [1] - primary exterior
                                        [2] - secondary exterior
                                        ...
                                        [NLAYER/2]   - new interior
                                        [NLAYER/2+1] - new primary exterior
                                        [NLAYER/2+2] - new secondary exterior
                                        ... */
  int nlayer;
#if NEW_PARALLEL_NEIGHBOR
  struct thread_neighbor_struct *neighbor;
#endif /* NEW_PARALLEL_NEIGHBOR */
#endif

  struct thread_struct *t0;    /* pointers from bndry threads to adjacent...*/
  struct thread_struct *t1;    /* cell threads (f->c0 is on t0, f->c1 on t1)*/

  struct
  {
    struct thread_struct *tpf0; /* sliding mesh, pointers to parent faces of */
    struct thread_struct *tpf1; /* interface faces */
    int nno;                    /* no fo node s on thread */
    Node *nodes;  /* storage of unmoved coords */
    struct thread_struct *siparent; /* inactive cell-faces */
    struct thread_struct *sichild;  /* active cell-faces */
    void *childs;                   /* "children " */
    void **child_threads;           /* child threads */
    int nchilds;
    struct thread_struct *thelper;  /* helper threads used for mapped interface io */
    struct thread_struct *tmapped;  /* mapped threads used for mapped interface io */
    struct thread_struct *tnoverlap;/* non-overlap thread for a sliding boundary */
    struct thread_struct *tnoverlap_gti;/* non-overlap thread for a sliding boundary */
    cxboolean sided_area_p;         /* sided area vector */
  } sm;

  struct
  {
    real *avg_f;
    int *f_bin;
    int bins;
    real **edge;
    cxboolean mixing;
    real *f_dist;
    real *P;
    real *T;
    real **Vel;
    real *alpha;
  } mpm_avg;               /*Implicit Mixing Plane*/

  struct
  {
    real *avg_f;
    int bins;
    int *f_bin;
    real *f_dist;
    real *bin_rad;
  } pitchwise_profile;

#if RP_PLBC
  /* pointer to sliding interface structure */
  struct sliding_interface *si;
#endif

  /* extended threads are need to keep the whole face zone on all compute nodes
     these threads keep all the faces and the adjacent cells*/
  struct thread_struct *extended_thread;

  struct thread_struct *next;    /* next thread */
  struct thread_struct *shadow;    /* periodic shadow thread */
#if RP_SHELL
  struct thread_struct *shadow_junction;
  struct thread_struct *root_layer;
  struct thread_struct *copy;
#endif
  struct thread_struct *parent; /* parent thread (hanging nodes) */
  struct thread_struct *child;  /* child thread (hanging nodes) */
  struct thread_struct *coarse; /* next coarser multigrid level */

  struct thread_struct *super_thread;  /*parent thread for subdomain thread */

  struct thread_struct *dual_thread;    /*pointer to dual thread */
  struct thread_struct *virtual_thread; /*pointer to nodeless face thread*/

  /*
   *  For sliding boundary only:
   *    pointer to a mapped interface thread, which has the same duplicated
   *    faces, nodes, and mapped face list
   */
  struct thread_struct *mapped_interface_thread;
  /* array of thread pointers to corresponding threads on
     sub-domains; max size "+1" used to permit less complicated
     logic in the third expression of the for loops used in the
     sub thread loop macros */
  struct thread_struct *sub_threads[MAX_SUB_DOMAINS + 1];

  struct dynamic_thread_struct *dtptr; /* pointer to dynamic_thread_struct */
#if RP_OVERSET
  struct overset_thread_struct *otptr; /* pointer to overset_thread_struct */
  void *otree;                         /* pointer to overset search tree */
#endif
  struct thread_struct *tint;          /* pointer to interior face thread */
  struct thread_struct *tmp1;
  struct thread_struct *tmp2;

  struct thread_struct *cnz;           /* cell nodal zone */
  struct thread_struct *fnz;           /* face nodal zone */

#if RP_POLYHEDRA
  void *node_weight_manager[ND_ND + 1];
#endif
#if USE_FEMCORE
  void *element_interpolation_nodes_manager[N_INTERP_TYPE];  /* belonging table from element to interpolation nodes */
  struct thread_struct *cinz[N_INTERP_TYPE];           /* cell interpolation node zone */
  struct thread_struct *finz[N_INTERP_TYPE];           /* face interpolation node zone */
  InzObjectAccess *inz_obj_access;                     /* position in interpolation node zone*/
#endif

  int id;
  size_t flags;
  union
  {
    void *astree;                             /* search tree */
    struct thread_struct **prev;        /* for double linking */
    struct thread_struct *asThread;        /* for duplicating */
  } tp;
  cxboolean renderp;                        /* for contouring */

  int *dpm_dist;
  int dpm_dist_nreals;       /* for SV_DPM_DIST */
  int dpm_bndry_dist_nreals; /* for SV_BNDRY_DPM_DIST */

#if RP_WALL_FILM && RP_3D
  void *ftree;
  void *etree;
#endif

  cxindex id_start; /* to avoid the label of IDs to save memmory */
  unsigned char amg_mapping_status[AMG_MAX_SYSTEMS];

  int comm_handle;

  struct domain_struct *domain; /* pointer to domain containing thread */
#if ALLOCATE_STORAGE_ARRAY_DYNAMIC
  void **storage;
  struct store_struct **store;
# if PARALLEL
  unsigned char *any_storage_allocated;
# endif /* PARALLEL */
#else /* ALLOCATE_STORAGE_ARRAY_DYNAMIC */
# if COMPACT_STORAGE_ARRAY
  void **storage;
  struct store_struct **store;
  void *storageArray[MAX_STORAGE_ARRAY_SIZE];
  struct store_struct *storeArray[MAX_STORAGE_ARRAY_SIZE];
# else
  void *storage[SV_MAX];
  struct store_struct *store[SV_MAX];
#endif

# if PARALLEL
  unsigned char any_storage_allocated[SV_MAX];
# endif /* PARALLEL */
#endif  /* ALLOCATE_STORAGE_ARRAY_DYNAMIC */

  int   passage_no;
  real  wave_dir;
  real  phase_angle;
  real  amplitude;
  real  freq;
  cxboolean cmplx;

#if RP_FC
  dom_fourier_d dfd;
#endif
};

/* objp */
struct objp_struct
{
  union
  {
    void *pointer;
    char *array;
    struct thread_struct *t;
    cat_t c;
    fat_t f;
    Node *v;
#if RP_EDGE
    struct edge_struct *e;
#endif
    int i;
    cxindex id;
  } as;
  union
  {
    struct objp_struct *oprev;  /* for circular lists */
    struct objp_struct **prev;  /* for double linking */
    Node *asNode;
    struct thread_struct *t;
    int id;
    int size;
  } op;
  struct objp_struct *next;
};
#define O_P(objp) ((objp)->as.pointer)
#define O_C(objp) ((objp)->as.c.c)
#define O_C_THREAD(objp) ((objp)->as.c.t)
#define O_F(objp) ((objp)->as.f.f)
#define O_F_THREAD(objp) ((objp)->as.f.t)
#define O_NODE(objp) ((objp)->as.v)
#define O_V O_NODE
#define O_THREAD(objp) ((objp)->as.t)
#define O_OPID(objp) ((objp)->op.id)
#define O_PTR(o) ((o)->as.pointer)
#define O_V0(o) ((o)->as.v)
#define O_V1(o) ((o)->op.asNode)
#define O_EXT_T(o) ((o)->as.t)
#define O_NEXT(o) ((o)->next)
#define O_I(o) ((o)->as.i)

#endif  /* _FLTG_MEM_H */
