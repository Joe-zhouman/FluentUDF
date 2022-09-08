/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _MEM_DUMP_H
#define _MEM_DUMP_H

#if RP_HANG
typedef struct fchild_
{
  int nkids;
  cxindex parent;
  cxindex child[MAX_KIDS_PER_FACE];
} fchild;

struct cchild
{
  int nkids;
  cxindex parent;
  cxindex child[MAX_KIDS_PER_CELL];
};

typedef enum
{
  EMPTY_DUMP,
  FKID_DUMP,
  CKID_DUMP,
  FMOM_DUMP,
  CLINK_DUMP
} kidmemtype;

#define FKID_DUMP_P(km)(km->type == FKID_DUMP)
#define CKID_DUMP_P(km)(km->type == CKID_DUMP)
#define FMOM_DUMP_P(km)(km->type == FMOM_DUMP)
#define CLINK_DUMP_P(km)(km->type == CLINK_DUMP)

struct kidmem
{
  int nparents;
  struct kidmem *next;
  kidmemtype type;
#if RP_HOST
  int id;
#endif
  union
  {
    fchild *f;
    struct cchild *c;
  } kids;
  struct thread_struct *tp;
  struct thread_struct *tk;
};

#endif /* RP_HANG */

struct cdata
{
#if PARALLEL
  cxindex cid;
  int tid;
#endif
  int ctype;
};

/*Data for Laplace smoothing*/
struct claplace
{
  cxindex lgco_id;  /*group cell owner id*/
};

struct ccell
{
  int offset;
  cxindex part;
#if !RP_NODE
  struct thread_struct *thread;
#endif
  struct cdata d;
};

struct cndata
{
#if PARALLEL
  cxindex cid;
  int tid;
#endif
  int ctype;
  int nnodes;
  cxindex nodes[MAX_NODES_PER_CELL];
};

struct fdata
{
#if PARALLEL
  cxindex fid;
  int tid;
#endif
  int fnodes;
  cxindex shadow;
  cxindex c0, c1;
#if RP_POLYHEDRA
  cxindex *v;
#else
  cxindex v[MAX_NODES_PER_FACE];
#endif
  int ftype;
};

struct fcell
{
#if PARALLEL
  cxindex fid;
#endif
#if RP_NODE
  fchild *dc; /* future opt: don't need parent */
#endif
#if !RP_NODE
  struct thread_struct *thread;
#else
  int p0, p1;
  int tid0, tid1;
#endif
  union
  {
    int offset;
  } as;
};

struct vdata
{
  double ND_VEC(x, y, z);
};
struct vcell
{
  unsigned int flags;
#if PARALLEL
  cxindex shadow;
#endif
  cxindex sid;
  struct _tg_node_struct *v;
  struct vdata d;
};


/* Eventually, we should start using struct of arrays
 * instead of array of struct, as is used currently.
 * These are not extensively used right now.
 */
#if PARALLEL

typedef struct cdump_t__
{
  cxindex *cid;
  struct thread_struct **thread;
  int *tid;
  int *part;
  short *ctype;
  cxindex *nnodes; /* good to use offsetted? */
  cxindex *nodes;
  cxindex *nkids;
  cxindex *kids;
  cxindex *parent;
} cdump_t;

typedef struct fdump_t__
{
  cxindex *fid;
  struct thread_struct **thread;
  int *tid;
  int *part;
  cxindex *nnodes;
  cxindex *nodes;
  cxindex *nkids;
  cxindex *kids;
  cxindex *parent;
  cxindex *shadow;
  cxindex *c0;
  cxindex *c1;
  int *p0;
  int *p1;
  int *tid0;
  int *tid1;
} fdump_t;

typedef struct vdump_t__
{
  cxindex *vid;
  struct thread_struct **thread;
  int *tid;
  double *x;
  unsigned int *flags;
  cxindex *shadow;
  cxindex *sid;
  cxindex *nprocs;
  int *procid;
} vdump_t;

typedef struct dump_t__
{
  cdump_t cell;
  fdump_t face;
  vdump_t node;
  cxindex cell_0, cell_1, cell_n, max_cell_id, ncells;
  cxindex face_0, face_1, face_n, max_face_id, nfaces;
  cxindex vert_0, vert_1, vert_n, max_vert_id, nverts;
  short what; /* volume-mesh/case = 1, surface-mesh = 2 */
} dump_t;

#endif /* PARALLEL */

/* Additional bits set in ctype in filling dump/IO */
#define BL_IO_FLAG 0x40
#define CART_IO_FLAG 0x80

#endif /* _MEM_DUMP_H */
