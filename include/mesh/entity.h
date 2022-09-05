/*
 * Copyright 1987-2022 ANSYS, Inc.  All Rights Reserved.
 */
#ifndef ENTITY_H
#define ENTITY_H

/* We should keep these structures in sync with entity0.h in PRIME/tgrid
 * so that the data structures can be shared between Solver and Meshing */

/* mesh connectivity */
#if RP_3D
# define _ND_ 3
# define MAX_NODES_PER_CELL 20
# define MAX_NODES_PER_POLY_CELL 4095
# define MAX_FACES_PER_CELL 6
# define MAX_FACES_PER_POLY_CELL 4095
# define MAX_NODES_PER_FACE 8
# define MAX_NODES_PER_EDGE 3
/* In cortex/cxsurf.h redefined  MAX_NODES_PER_POLY_FACE
 * as CX_MAX_NODES_PER_POLY_FACE = 256.
 * Please keep both values in sync.*/
# define MAX_NODES_PER_POLY_FACE 256
# define MAX_EDGES_PER_FACE 4
# define MAX_EDGES_PER_CELL 12

# define MAX_KIDS_PER_FACE 4
# if LEAN_MEM_TEST
#  define MAX_KIDS_PER_CELL 1
# else
#  define MAX_KIDS_PER_CELL 10
# endif
#else
# define _ND_ 2
# define MAX_NODES_PER_CELL 4
# define MAX_FACES_PER_CELL 4
# define MAX_NODES_PER_FACE 2
# define MAX_NODES_PER_EDGE 1
# define MAX_EDGES_PER_FACE 1
# define MAX_EDGES_PER_CELL 4
# define MAX_KIDS_PER_FACE 2
# define MAX_KIDS_PER_CELL 4
#endif

#define MAX_NBORS_PER_EDGE 2
#define MAX_NBORS_PER_FACE 2
#define MAX_FACES_PER_FACE 4

#define LINEAR_EDGE_NNODES 2
#define LINEAR3_EDGE_NNODES 3

#define TRI_NNODES  3
#define TRI_NFACES 3

#define TRI6_NNODES 6
#define TRI6_NFACES 3

#define QUAD_NNODES 4
#define QUAD_NFACES 4

#define QUAD8_NNODES 8
#define QUAD8_NFACES 4

#define TET_NNODES 4
#define TET_NFACES 4

#define TET10_NNODES 10
#define TET10_NFACES 4

#define HEX_NNODES 8
#define HEX_NFACES 6

#define HEX20_NNODES 20
#define HEX20_NFACES 6

#define WEDGE_NNODES 6
#define WEDGE_NFACES 5

#define WEDGE15_NNODES 15
#define WEDGE15_NFACES 5

#define PYRAMID_NNODES 5
#define PYRAMID_NFACES 5

#define PYRAMID13_NNODES 13
#define PYRAMID13_NFACES 5

#define     TET_NEDGES 6
#define     HEX_NEDGES 12
#define   WEDGE_NEDGES 9
#define PYRAMID_NEDGES 8

typedef struct _tg_node_struct Node;
typedef struct _tg_face_struct Face;
typedef struct _tg_cell_struct Cell;
typedef struct thread_struct Thread;

# if PARALLEL
#  if USE_INT64
#   if _NT
typedef long long tgindex;
#   else
typedef long tgindex;
#   endif
#  else
typedef int tgindex;
#  endif
# else
typedef unsigned int tgindex;
# endif

#if RP_POLYHEDRA

/* Union defined to handle int to pointer conversion on 64bit m/c */
typedef union
{
    int i;
    long cxi;
    void *p;
} IdPtr ;

typedef char Storage;

struct c_cell_struct
{
    union
    {
        Node *nodes[MAX_NODES_PER_CELL];
        Face *faces[MAX_NODES_PER_CELL + MAX_FACES_PER_CELL];
        Cell *cells[MAX_NODES_PER_CELL + MAX_FACES_PER_CELL];
        struct _tg_entity_struct
            *entities[MAX_NODES_PER_CELL + MAX_FACES_PER_CELL];
    } nf;
};

struct f_face_struct
{
    union
    {
        Node *nodes[MAX_NODES_PER_FACE + MAX_NBORS_PER_FACE];
        IdPtr inodes[MAX_NODES_PER_FACE + MAX_NBORS_PER_FACE];
    } nf;
};

struct e_edge_struct
{
    union
    {
        Node *nodes[MAX_NODES_PER_EDGE + MAX_NBORS_PER_EDGE];
        IdPtr *inodes[MAX_NODES_PER_EDGE + MAX_NBORS_PER_EDGE];
    } nf;
};
#endif

struct _tg_list_entity
{
    unsigned int prev;
    unsigned int next;
};

struct _tg_entity_struct
{
    tgindex id;
    unsigned int flags;
    unsigned int idx;
    unsigned int kind;
    Thread *thread;
};

struct _tg_node_struct
{
    tgindex id;
    unsigned int flags;
    unsigned int idx;
    unsigned int kind;
    Thread *thread;
    double x[_ND_];
};

struct _tg_edge_struct
{
    tgindex id;
    unsigned int flags;
    unsigned int idx;
    unsigned int kind;
    Thread *thread;
#if RP_POLYHEDRA
    struct e_edge_struct e;
#else
    Node *v0, *v1;
    Face *f0, *f1;
#endif
};

struct _tg_face_struct
{
    tgindex id;
    unsigned int flags;
    unsigned int idx;
    unsigned int kind;
    Thread *thread;
#if RP_POLYHEDRA
    struct f_face_struct f;
#else
    Node *nodes[MAX_NODES_PER_FACE];
    Cell *c0, *c1;
#endif
};

struct _tg_cell_struct
{
    tgindex id;
    unsigned int flags;
    unsigned int idx;
    unsigned int kind;
    Thread *thread;
#if RP_POLYHEDRA
    struct c_cell_struct c;
#else
    Node *nodes[MAX_NODES_PER_CELL];
    Face *faces[MAX_FACES_PER_CELL];
#endif
};

#define ENTITY_ID1(s) (((struct _tg_entity_struct *)(s))->id)
#define NODE_ID1(s) ENTITY_ID1(s)
#define EDGE_ID1(s) ENTITY_ID1(s)
#define FACE_ID1(s) ENTITY_ID1(s)
#define CELL_ID1(s) ENTITY_ID1(s)

#define ENTITY_FLAGS(s) (((struct _tg_entity_struct *)(s))->flags)
#define ENTITY_FLAG(s,mask) (ENTITY_FLAGS(s) & (mask))
#define ENTITY_FLAGS_ALL(s, mask) ((ENTITY_FLAGS(s) & (mask)) == (mask))
#define SET_ENTITY_FLAGS(s,mask) ENTITY_FLAGS(s) |= (mask)
#define CLEAR_ENTITY_FLAGS(s,mask) ENTITY_FLAGS(s) &= ~(mask)
#define TOGGLE_ENTITY_FLAGS(s,mask) ENTITY_FLAGS(s) ^= (mask)

#define ENTITY_SV_IDX(e) (((struct _tg_entity_struct *)(e))->idx)
#define ENTITY_THREAD2(e) (((struct _tg_entity_struct *)(e))->thread)

#define LEFT 0
#define RIGHT 1
#define OTHER_HAND(h) (h?LEFT:RIGHT)

#if RP_POLYHEDRA
# define E_NEIGH(s) ((Face **)(EDGE_NODES(s)+EDGE_NNODES(s)))
# define F_NEIGH(s) ((Cell **)(FACE_NODES(s)+FACE_NNODES(s)))

# define EDGE_NODES(s) ((s)->e.nf.nodes)
# define E_INODES(s)   ((s)->e.nf.inodes)
# define FACE_NODES(s) ((s)->f.nf.nodes)
# define F_INODES(s)   ((s)->f.nf.inodes)

# define CELL_NODES(s) ((s)->c.nf.nodes)
# define CELL_FACES(s) ((s)->c.nf.faces+CELL_NNODES(s))
# define C_ENTITIES(s) ((s)->c.nf.entities+CELL_NNODES(s))
# define C_CELLS(s)    ((s)->c.nf.cells+CELL_NNODES(s))

# define OTHER_FACE(f,e)                                                    \
    (LEFT_E_NEIGHBOR(e) == (f) ? RIGHT_E_NEIGHBOR(e) : LEFT_E_NEIGHBOR(e))
# define E_HAS_NEIGHBORS(e)                                                 \
    (!NULLP(LEFT_E_NEIGHBOR(e)) || !NULLP(RIGHT_E_NEIGHBOR(e)))
# define E_HAS_NO_NEIGHBORS(e) (!HAS_NEIGHBORS(e))
# define E_NEIGHBORS_FULL(e)                                                \
    (!NULLP(LEFT_E_NEIGHBOR(e)) && !NULLP(RIGHT_E_NEIGHBOR(e)))
# define ForEachEdgeNeighbor(f,e,h)                                         \
    for (f=E_NEIGH(e)[h=0]; h<2; ++h,f=E_NEIGH(e)[1])

# define E_INEIGH(s) ((IdPtr *)(E_INODES(s)+EDGE_NNODES(s)))
# define EDGE_INEIGHBOR(s,h)    (E_INEIGH(s)[h]).i
# define LEFT_E_INEIGHBOR(s)    (E_INEIGH(s)[LEFT]).i
# define RIGHT_E_INEIGHBOR(s)   (E_INEIGH(s)[RIGHT]).i
# define LEFT_E_XNEIGHBOR(s)    (E_INEIGH(s)[LEFT]).cxi
# define RIGHT_E_XNEIGHBOR(s)   (E_INEIGH(s)[RIGHT]).cxi
# define SET_E_INEIGHBOR(s,h,n) (E_INEIGH(s)[h].i = n)
# define OTHER_FACE_X(f,e)                                                  \
    (LEFT_E_XNEIGHBOR(e) == (f) ? RIGHT_E_XNEIGHBOR(e) : LEFT_E_XNEIGHBOR(e))


# define OTHER_CELL(c,f)                                                    \
     (LEFT_F_NEIGHBOR(f) == (c) ? RIGHT_F_NEIGHBOR(f) : LEFT_F_NEIGHBOR(f))
# define F_HAS_NEIGHBORS(f)                                                 \
     (!NULLP(LEFT_F_NEIGHBOR(f)) || !NULLP(RIGHT_F_NEIGHBOR(f)))
# define F_HAS_NO_NEIGHBORS(f) (!F_HAS_NEIGHBORS(f))
# define F_NEIGHBORS_FULL(f)                                                \
     (!NULLP(LEFT_F_NEIGHBOR(f)) && !NULLP(RIGHT_F_NEIGHBOR(f)))
# define ForEachFaceNeighbor(c,f,h)                                         \
     for (c=F_NEIGH(f)[h=0]; h<2; ++h,c=F_NEIGH(f)[1])

# define F_INEIGH(s) ((IdPtr *)(F_INODES(s)+FACE_NNODES(s)))
# define FACE_INEIGHBOR(s,h)    (F_INEIGH(s)[h]).i
# define LEFT_F_INEIGHBOR(s)    (F_INEIGH(s)[LEFT]).i
# define RIGHT_F_INEIGHBOR(s)   (F_INEIGH(s)[RIGHT]).i
# define LEFT_F_XNEIGHBOR(s)    (F_INEIGH(s)[LEFT]).cxi
# define RIGHT_F_XNEIGHBOR(s)   (F_INEIGH(s)[RIGHT]).cxi
# define SET_F_INEIGHBOR(s,h,n) (F_INEIGH(s)[h].i = n)
# define OTHER_CELL_X(c,f)                                                  \
    (LEFT_F_XNEIGHBOR(f) == (c) ? RIGHT_F_XNEIGHBOR(f) : LEFT_F_XNEIGHBOR(f))

# define OTHER_NODE(v,e)                        \
    ((EDGE_NODE(e,0)==v) ? EDGE_NODE(e,1) :     \
    ((EDGE_NODE(e,1)==v) ? EDGE_NODE(e,0) : NULL))

#else

# define EDGE_NODES(e) ((Node **)&(e->v0))
# define FACE_NODES(f) (f->nodes)
# define E_NEIGH(e) ((Face **)&(e->f0))
# define F_NEIGH(f) ((Cell **)&(f->c0))
# define CELL_NODES(c) (c->nodes)
# define CELL_FACES(c) (c->faces)

#endif

#define EDGE_NEIGHBOR(s,h)     (E_NEIGH(s)[h])
#define LEFT_E_NEIGHBOR(s)     (E_NEIGH(s)[LEFT])
#define RIGHT_E_NEIGHBOR(s)    (E_NEIGH(s)[RIGHT])
#define SET_E_NEIGHBOR(s,h,n)  (E_NEIGH(s)[h] = (n))

#define FACE_NEIGHBOR(s,h)     (F_NEIGH(s)[h])
#define LEFT_F_NEIGHBOR(s)     (F_NEIGH(s)[LEFT])
#define RIGHT_F_NEIGHBOR(s)    (F_NEIGH(s)[RIGHT])
#define SET_F_NEIGHBOR(s,h,n)  (F_NEIGH(s)[h] = (n))

#define NODE_COORD1(v) ((v)->x)

/*
 * e->kind(32 bits) == [ 6 bits -> entity type     ]
 *                     [ 1 bit  -> cart entity flag]
 *                     [ 1 bit  -> bl entity flag  ]
 *                     [12 bits -> entity nfaces   ]
 *                     [12 bits -> entity nnodes   ]
 */
#define ENTITY_KIND(s) (((struct _tg_entity_struct *)(s))->kind)

#define NNODES_MASK 0xfff
#define NFACES_MASK 0xfff000
#define NFACES_SHIFT 12

#define ENTITY_TYPE_MASK 0xfc000000
#define ENTITY_TYPE_SHIFT 26

#define BL_ENTITY_FLAG 0x1000000
#define SET_BL_ENTITY(e)   (ENTITY_KIND(e) |=  BL_ENTITY_FLAG)
#define CLEAR_BL_ENTITY(e) (ENTITY_KIND(e) &= ~BL_ENTITY_FLAG)
#define BL_ENTITY(e)       (ENTITY_KIND(e) &   BL_ENTITY_FLAG)

#define CART_ENTITY_FLAG 0x2000000
#define SET_CART_ENTITY(e)   (ENTITY_KIND(e) |=  CART_ENTITY_FLAG)
#define CLEAR_CART_ENTITY(e) (ENTITY_KIND(e) &= ~CART_ENTITY_FLAG)
#define CART_ENTITY(e)       (ENTITY_KIND(e) &   CART_ENTITY_FLAG)

#define ENTITY_NNODES(e) ((int)((ENTITY_KIND(e)) & NNODES_MASK))
#define ENTITY_NFACES(e) ((int)(((ENTITY_KIND(e)) & NFACES_MASK) >> NFACES_SHIFT))
#define ENTITY_TYPE(e) \
    ((int)(((ENTITY_KIND(e)) & ENTITY_TYPE_MASK) >> ENTITY_TYPE_SHIFT))

#define SET_ENTITY_NNODES(e, nn)                            \
    ENTITY_KIND(e) = ((ENTITY_KIND(e) & ~NNODES_MASK) | nn)
#define SET_ENTITY_NFACES(e, nf)                            \
    ENTITY_KIND(e) = ((ENTITY_KIND(e) & ~NFACES_MASK)       \
                      | ((nf) << NFACES_SHIFT))
#define INIT_ENTITY_KIND(e) (ENTITY_KIND(e) = 0)
#define SET_ENTITY_TYPE(e, n)                               \
    ENTITY_KIND(e) = ((ENTITY_KIND(e) & ~ENTITY_TYPE_MASK)  \
                      | ((n) << ENTITY_TYPE_SHIFT))


#define EDGE_NNODES(e) ENTITY_NNODES(e)
#define FACE_NNODES(e) ENTITY_NNODES(e)
#define CELL_NNODES(e) ENTITY_NNODES(e)

#define CELL_NFACES(e) ENTITY_NFACES(e)

#define NODE_TYPE(e) ENTITY_TYPE(e)
#define EDGE_TYPE(e) ENTITY_TYPE(e)
#define FACE_TYPE(e) ENTITY_TYPE(e)
#define CELL_TYPE(e) ENTITY_TYPE(e)

#define SET_EDGE_NNODES(e, nn) SET_ENTITY_NNODES(e, nn)
#define SET_FACE_NNODES(e, nn) SET_ENTITY_NNODES(e, nn)
#define SET_CELL_NNODES(e, nn) SET_ENTITY_NNODES(e, nn)

#define SET_CELL_NFACES(e, nf) SET_ENTITY_NFACES(e, nf)

#define SET_NODE_TYPE(e, n) SET_ENTITY_TYPE(e, n)
#define SET_EDGE_TYPE(e, n) SET_ENTITY_TYPE(e, n)
#define SET_FACE_TYPE(e, n) SET_ENTITY_TYPE(e, n)
#define SET_CELL_TYPE(e, n) SET_ENTITY_TYPE(e, n)

enum
{
    SIMPLE_NODE  = 0,    /* the default node type */
    HARD_NODE    = 1,    /* immovable node */

    /* to be safe, I(kmb) am skipping 2 and 3 as node types  because
     * GEOMESH sometimes  writes 2 and 3 as node types, refer to
     * the comment above _tg_etype2memtype definition. */

    FEATURE_NODE = 4,    /* node that can be moved along feature edges */
    HANGING_NODE = 5,    /* mid (bridge) nodes */
    FROZEN_NODE  = 6,
    N_NODE_TYPES
};

enum
{
    LINEAR_EDGE  = 0,          /* 2 nodes */
    LINEAR3_EDGE = 1,          /* quadratic edge with 3 nodes */
    N_EDGE_TYPES
};

enum
{
    MIXED_FACE  = 0,
    LINEAR_FACE = 2,           /* 2 nodes, 0 edges */
    TRI_FACE    = 3,           /* 3 nodes, 3 edges */
    QUAD_FACE   = 4,           /* 4 nodes, 4 edges */
    POLY_FACE   = 5,           /* arbitrary number of nodes/edges */
    TRI6_FACE   = 6,           /* Quadratic Triangle with 3 midside nodes */
    QUAD8_FACE  = 7,           /* Quadratic Quad with 4 midside nodes */
    N_FACE_TYPES
};

enum
{
    MIXED_CELL     = 0,
    TRI_CELL       = 1,          /* 3 nodes, 3 faces */
    TET_CELL       = 2,          /* 4 nodes, 4 faces */
    QUAD_CELL      = 3,          /* 4 nodes, 4 faces */
    HEX_CELL       = 4,          /* 8 nodes, 6 faces */
    PYRAMID_CELL   = 5,          /* 5 nodes, 5 faces */
    WEDGE_CELL     = 6,          /* 6 nodes, 5 faces */
    POLY_CELL      = 7,          /* support for write only */
    GHOST_CELL     = 8,          /* 2 nodes, 1 face (only for 2D) */
    TET10_CELL     = 9,          /* 10 nodes, 4 faces - quadratic tet */
    HEX20_CELL     = 10,         /* 20 nodes, 6 faces - quadratic hex */
    PYRAMID13_CELL = 11,         /* 13 nodes, 5 faces - quadratic pyramid */
    WEDGE15_CELL   = 12,         /* 15 nodes, 5 faces - quadratic wedge */
    N_CELL_TYPES
};

/* _D_ is number of dimensions */
/* _N_ is the number of nodes, faces, neighbors of an n-simplex */
/* _E_ is the number of edges */
#if RP_2D
# define _D_ 2
# define _N_ 3
# define _E_ 3
#else
# define _D_ 3
# define _N_ 4
# define _E_ 6
#endif

#endif /* ENTITY_H */
