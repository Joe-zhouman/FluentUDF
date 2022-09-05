/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_PROX_H
#define _FLUENT_PROX_H

#include "dll.h"

#define V_DOT(a,b)\
   ND_DOT((a).x[0],(a).x[1],(a).x[2],\
    (b).x[0],(b).x[1],(b).x[2])
#if RP_2D
#define V_CROSS(a,b) ((a).x[0]*(b).x[1] - (b).x[0]*(a).x[1])
#else
#define V_CROSS(a,b,r)\
        ((r).x[0] = (a).x[1]*(b).x[2] - (b).x[1]*(a).x[2],\
         (r).x[1] = (a).x[2]*(b).x[0] - (b).x[2]*(a).x[0],\
         (r).x[2] = (a).x[0]*(b).x[1] - (b).x[0]*(a).x[1])
#endif

#define ALTERNATE_XYZ_SPLIT(a) (((a)+1) == ND_ND ? 0 : (a)+1)

#define BIGPOS  1.0e+08
#define BIGNEG -1.0e+08

typedef struct point
{
  real x[ND_ND];
} Point;

typedef struct voxl_struct
{
  real distance;
  Point min, max, ctr;
  real vmag2;
  Point vnrm;
  union
  {
    Node *v;
  } as;
  struct voxl_struct *next;
} Voxl;

typedef struct twig_struct
{
  real distance;
  Point min, max;
  int xyz_split;
  int num_buds;
  Voxl *buds;
  struct twig_struct **prev, *next;
} Twig;

typedef struct tree_struct
{
  int num_twigs;
  Twig *twigs;
} Tree;

enum
{
  ALGEBRAIC_WD,
  LAPLACIAN_WD
};

#if !RP_HOST
/* Stores function pointers for the extra varialbe in elem-struct */
typedef struct Geom_Elt_Property_Provider
{
  size_t nbytes;
  void *(*get_face_prop_ref)(const face_t, Thread *const);
  void *(*get_cell_prop_ref)(const cell_t, Thread *const);
  cxboolean used;
} CX_Geom_Elt_Property_Provider;

typedef struct lookup_stats_struct
{
  double time;
  int count;
} Lookup_Stats ;
#endif /* !RP_HOST */

FLUENT_EXPORT void Test_Wall_Property(Domain *);

#if !RP_HOST
FLUENT_EXPORT cxboolean Wall_Roughness_Used(void);
FLUENT_EXPORT cxboolean Fill_Cell_Wall_Distance(Domain *d);
FLUENT_EXPORT cxboolean Fill_Cell_Wall_Distance_Alternative(Domain *d);
FLUENT_EXPORT cxboolean Calc_Cell_Wall_Distance_Alternative(Domain *d, Svar nv);
FLUENT_EXPORT cxboolean Calc_Cell_Wall_Distance_New(Domain *d, Svar nv);
#endif
/* The following function is defined in flowf.c (created from an
 * existing function and kept there for minimal "cvs diff" output): */
FLUENT_EXPORT cxboolean Init_Cell_Wall_Dist_If_Needed(Domain *domain);
FLUENT_EXPORT cxboolean Compute_Wall_Distance (Domain *, cxboolean);
FLUENT_EXPORT cxboolean cell_wall_dist(Domain *);

FLUENT_EXPORT void Fill_Cell_NrmDist_And_EqLenSq(Domain *d);
FLUENT_EXPORT void Solve_Laplacian_WD(Domain *domain, Svar nv, int method, cxboolean verbose);
FLUENT_EXPORT void Model_Initialize_lap_wd(void);

FLUENT_EXPORT void NodesFromBoundary(Domain *d);
FLUENT_EXPORT void initBoundaryNormalDistance(Domain *d);
FLUENT_EXPORT void initCellsFromBoundary(Domain *d);
#endif /* _FLUENT_PROX_H */
