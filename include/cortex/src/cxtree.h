/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#define CUBE_ROOT(n) exp(log((n))/3)

#define DISTSQ_2D(p1,p2) \
 (((p2)[0]-(p1)[0])*((p2)[0]-(p1)[0]) + ((p2)[1]-(p1)[1])*((p2)[1]-(p1)[1]))

#define DISTSQ_3D(p1,p2) \
 (((p2)[0]-(p1)[0])*((p2)[0]-(p1)[0]) + ((p2)[1]-(p1)[1])*((p2)[1]-(p1)[1]) + ((p2)[2]-(p1)[2])*((p2)[2]-(p1)[2]))


#define DIST_SQ(p1,p2) ((dim == 2) ? DISTSQ_2D(p1,p2) : DISTSQ_3D(p1,p2))

#define V2D_DOT(v0,v1)  (v0[0]*v1[0]+v0[1]*v1[1])

#define V3D_DOT(v0,v1) (((v0)[0])*((v1)[0])+((v0)[1])*((v1)[1])+((v0)[2])*((v1)[2]))

#define V_DOT(v0,v1) \
((dim == 2) ? (V2D_DOT(v0,v1)) : (V3D_DOT(v0,v1)))

#define V2D_CROSS_X(v1,v2)(0.0)
#define V2D_CROSS_Y(v1,v2)(0.0)
#define V2D_CROSS_Z(v1,v2)(((v1[0])*(v2[1]))-((v2[0])*(v1[1])))

#define SET_V2D_CROSS(vf, v0 , v1) \
 vf[0] = V2D_CROSS_X(v0,v1); \
 vf[1] = V2D_CROSS_Y(v0,v1); \
 vf[2] = V2D_CROSS_Z(v0,v1);

#define SET_V3D_CROSS(vf,v0,v1) \
  vf[0] = N3D_CROSS_X(v0[0],v0[1], v0[2],v1[0], v1[1], v1[2]);\
  vf[1] = N3D_CROSS_Y(v0[0],v0[1], v0[2],v1[0], v1[1], v1[2]);\
  vf[2] = N3D_CROSS_Z(v0[0],v0[1], v0[2],v1[0], v1[1], v1[2])


#define SET_V_CROSS(vf,v0,v1) \
 if (dim ==2) {SET_V2D_CROSS(vf,v0,v1);}  else  { SET_V3D_CROSS(vf,v0,v1);}


/* Stores faces[points, lines, tris, and quads] as list of points; */
typedef struct Geom_Elt_Struct
{
  int np;
  float (*v)[3];
  float min[3];
  float max[3];
  char *prop;
  struct Geom_Elt_Struct *next;
} CX_Geom_Elt_t;


/* Oct Tree.
   Internal nodes store splitter. Leaf nodes store list of elements.
*/
typedef struct Geom_Elt_Tree_Struct
{
  union
  {
    float splitter;
    CX_Geom_Elt_t *elts;
  } value;
  int field;
  float min[3];    /* among all faces in tree rooted at this node */
  float max[3];
  struct Geom_Elt_Tree_Struct *left;
  struct Geom_Elt_Tree_Struct *right;
  int count;      /* of faces in tree rooted at this node */
} CX_Geom_Elt_Tree_t;

#define SPLITTER(elt_tree) (elt_tree)->value.splitter
#define ELT_LIST(elt_tree) (elt_tree)->value.elts
#define RIGHT_TREE(elt_tree) (elt_tree)->right
#define LEFT_TREE(elt_tree) (elt_tree)->left
#define LEAF_NODE(elt_tree) (NULLP(RIGHT_TREE(elt_tree)) && NULLP(LEFT_TREE(elt_tree)))
#define NEXT_NODE(elt_tree) RIGHT_TREE((elt_tree))


/* exported to cxisosurf.c */
int CX_Nearest_Power_Of_Two(int n);
int CX_Cmp_Floats( void *pf1, void *pf2);

#if CX_NODE
void CX_All_Broadcast_Geom_Elts(CX_Geom_Elt_t *elt_list, cxboolean only_zero);
#endif







