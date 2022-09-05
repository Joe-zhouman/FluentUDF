/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/**********************************************************************
 * bsp.h
 *
 * The files bsp.h and bsp.c provide for:
 *      * Creating binary space partitioning (BSP) trees.
 *      * Deleting BSP trees.
 *      * Searching them for items within a sphere.
 *      * Finding the closest item to a point.
 *      * Find the BSP tree leaf containing a point.
 *      * Finding intersections between BSP tree items and a ray.
 *
 * Joe Maruszewski, 09/27/2002
 **********************************************************************/
#ifndef BSP_H
#define BSP_H


#include "global.h"
typedef real BSP_Real;
#define BSP_REAL_IS_DOUBLE  RP_DOUBLE


/**********************************************************************
 * BSP_Tree
 *
 *  BSP tree structure definition.
 **********************************************************************/
typedef struct BSP_Tree
{
  int splitDir;
  BSP_Real rMin[3];
  BSP_Real rMax[3];

  int nItems;
  int *item;

  struct BSP_Tree *kid[2];
}
BSP_Tree;


/**********************************************************************
 * Function prototypes:
 *
 * BSP_freeTreeNode
 *
 *  Free a BSP tree node back to our own free list.  The freed
 *  node is put back on the top of the list.  The free list is
 *  connected through the "kid[0]" pointer.
 *
 * BSP_allocateTreeNode
 *
 *  Get a BSP tree node from our own free list.  If the free
 *  list is empty we try to allocate another block of nodes,
 *  and return "NULL" if another block cannot be allocated.
 *  The free list is connected through the "kid[0]" pointer.
 *
 * BSP_freeTree
 *
 *  Free a BSP tree.
 *
 * BSP_buildTree
 *
 *  Build a BSP tree.  The function "refine()" is used to decide
 *  if a voxel needs to be refined further, and "compare()" is
 *  used to determine which kid voxel an item is in when
 *  distributing items to the kids.
 *
 * BSP_boxBoxIntersect
 *
 *  Determine if there is an intersection between the axis-aligned box
 *  specified by its bounding planes "tMin[]" and "tMax[]" and the
 *  bounding box specified by its bounding planes "rMin[]" and "rMax[]".
 *
 * BSP_sphereBoxIntersect
 *
 *  Determine if there is an intersection between the sphere
 *  given by its center "rc[]" and its radius "radius" and the
 *  bounding box specified by its bounding planes "rMin[]" and
 *  "rMax[]".  Algorithm from Graphics Gems I.
 *
 * BSP_itemsInBox
 *
 *  Find all items in voxels which are partially contained in
 *  the bounding box specified by its bounding planes "tMin[]" and "tMax[]".
 *  The function "inside()" is used to determine if the item is
 *  inside the box or not.  Specifying NULL as the function
 *  pointer for "inside()" finds all items that could
 *  possibly be inside the sphere, and so requires less time
 *  since it doesn't need to call "inside()".
 *  Note that there may be duplicates in the array of items returned,
 *  since multiple voxels can contain the same item.
 *
 * BSP_itemsInSphere
 *
 *  Find all items in which are contained in the sphere
 *  specified by its center "rc[]" and its radius "radius".
 *  The function "inside()" is used to determine if the item is
 *  inside the sphere or not.  Specifying NULL as the function
 *  pointer for "inside()" finds all items that could
 *  possibly be inside the sphere, and so requires less time
 *  since it doesn't need to call "inside()".
 *  Note that there may be duplicates in the array of items returned,
 *  since multiple voxels can contain the same item.
 *
 * BSP_closestItem
 *
 *  Find the item which is closest to the point "rc[]".  The
 *  function "distance()" is used to calculate the distance
 *  between the point and a particular item.  The index of
 *  the closest item is returned, or -1 if no item can be found.
 *
 * BSP_rayBoxIntersect
 *
 *  Determine if there is an intersection between a ray specified
 *  by is origin "ro[]" and the unit vector "sv[]" with a
 *  bounding box specified by is bounding planes "rMin[]" and
 *  "rMax[]".  The minimum and maximum intersection points
 *  along the ray are returned in "*dMin" and "*dMax".
 *
 * BSP_rayTreeIntersect
 *
 *  Find the intersection point "ri[]" of a ray (specified by
 *  its origin "ro[]" and the unit vector "sv[]") with items in
 *  the tree.  The function "intersect()" is used to test for
 *  intersection with leaf items and to compute the intersection
 *  point and return the item intersected.
 **********************************************************************/
FLUENT_EXPORT void      BSP_freeTreeNode(BSP_Tree *p);
FLUENT_EXPORT BSP_Tree *BSP_allocateTreeNode(void);
FLUENT_EXPORT void      BSP_freeTree(BSP_Tree *t);
FLUENT_EXPORT int       BSP_buildTree(BSP_Tree *t,
                                      int refine(BSP_Tree *t),
                                      int compare(int item, int splitDir,
                                                  BSP_Real splitLoc));
FLUENT_EXPORT int       BSP_boxBoxIntersect(BSP_Real tMin[], BSP_Real tMax[],
                                            BSP_Real rMin[], BSP_Real rMax[]);
FLUENT_EXPORT int       BSP_sphereBoxIntersect(BSP_Real rc[], BSP_Real radius,
                                               BSP_Real rMin[], BSP_Real rMax[]);
FLUENT_EXPORT int       BSP_itemsInBox(BSP_Tree *t, BSP_Real tMin[], BSP_Real tMax[],
                                       int inside(int item, BSP_Real iMin[], BSP_Real iMax[]),
                                       int *nItems, int **item, int *size);
FLUENT_EXPORT int       BSP_itemsInSphere(BSP_Tree *t, BSP_Real rc[], BSP_Real radius,
                                          int inside(int item, BSP_Real rc[], BSP_Real radius),
                                          int *nItems, int **item, int *itemSize);
FLUENT_EXPORT int       BSP_closestItem(BSP_Tree *t, BSP_Real rc[],
                                        BSP_Real distance(int item, BSP_Real rc[]));
FLUENT_EXPORT int       BSP_rayTreeIntersect(BSP_Tree *t, BSP_Real ro[], BSP_Real sv[],
                                             int intersect(BSP_Tree *t,
                                                           BSP_Real ro[], BSP_Real sv[],
                                                           BSP_Real dMin, BSP_Real dMax,
                                                           BSP_Real ri[], int *hitItem),
                                             BSP_Real ri[], int *hitItem);


#endif /* BSP_H */
