/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_TURBO_H
#define _FLUENT_TURBO_H

#include "dll.h"
#include "filter.h"

typedef struct pt3_struct
{
  real x, y, z;
  real param;
} Pt3;

/* Turbo data stored for each grid point.
   Variables added here should also be added to copyTurboCurve() */
typedef struct turbo_struct
{
  real xp, yp, zp, r, z;     /* x, y, z, radius, axial length */
  real length, lengthAbs;    /* relative and absolute meridional length */
  real thetaMin, thetaMax;   /* theta value at min and max span */
  real paramAvg;             /* Average param value */
  real paramTot;             /* Running total of parameter values */
  int  nBin;                 /* Number of parameter values */
  real dist;                 /* Distance to cell center value being used */
  real rtheta;               /* blade to blade value */
} Turbo;


/* 2D structured i, j turbo grid */
typedef struct turbo_grid_struct
{
  Turbo     **pts;
  int         nIPts;
  int         nJPts;
  real        minParam;      /* min/max values are for color mapping */
  real        maxParam;
#if !RP_HOST
  Oct_Tree    *turbo_tree;
#endif
} TurboGrid;

typedef struct turbo_topology_struct
{
  int *cell_zone_ids;
  int ncell_zones;
  /* Turbo grid points */
  TurboGrid *constMeridGrid;
  TurboGrid *constSpanGrid;
  TurboGrid *turboMerid ;

  int nGridRes;
  int nThetaPts;
  int nIncreasingAxial;
  int nUseRadialAlgorithm;
  int theta_sign_change;
  cxboolean turboInitialized;
  cxboolean useRawGrid;

  /* Turbo surface outlines */
  Turbo *turboHub;
  Turbo *turboShroud;
  Turbo *turboInlet;
  Turbo *turboOutlet;
  Turbo *turboTheta;
  Turbo *turboThetaMin;
  Turbo *turboThetaMax;

  Thread **turboHub_t_list;
  Thread **turboShroud_t_list;
  Thread **turboInlet_t_list;
  Thread **turboOutlet_t_list;
  Thread **turboTheta_t_list;
  Thread **turboThetaMin_t_list;
  Thread **turboThetaMax_t_list;

  int t_list_length[7]; /* Stores the  length of *_t_list arrays */
  /* 0 -> Hub_l_t_list; 1 Shroud ; 2 Inlet ; 3 Outlet;
     4 Theta ; 5 ThetaMin ; 6 ThetaMax; */
  /* Turbo linear points */
  Turbo *turboHubMinLine;
  Turbo *turboShroudMinLine;
  Turbo *turboHubMaxLine;
  Turbo *turboShroudMaxLine;
  Turbo *turboHubLine;
  Turbo *turboShroudLine;
  Turbo *turboInletLine;
  Turbo *turboOutletLine;

  /* Hub and Shroud inlet origins */
  Turbo    hubInOrigin;
  Turbo    shroudInOrigin;
  Turbo    hubOutOrigin;
  Turbo    shroudOutOrigin;
  Turbo    hubOriginMinTheta;
  Turbo    shroudOriginMinTheta;
  Turbo    hubOriginMaxTheta;
  Turbo    shroudOriginMaxTheta;

} Turbo_Topology;

#if RP_3D


extern FLUENT_EXPORT Turbo_Topology *turboGrid_List;
extern FLUENT_EXPORT  int N_Blade_Rows;
extern FLUENT_EXPORT int theta_sign_change; /* temparory << */

#define TURBO_TOPO(blade_row,item) turboGrid_List[blade_row].item

#define T_HUB(blade_row) TURBO_TOPO(blade_row,turboHub)
#define T_SHROUD(blade_row) TURBO_TOPO(blade_row,turboShroud)
#define T_INLET(blade_row) TURBO_TOPO(blade_row,turboInlet)
#define T_OUTLET(blade_row) TURBO_TOPO(blade_row,turboOutlet)
#define T_THETA(blade_row) TURBO_TOPO(blade_row,turboTheta)
#define T_THETAMIN(blade_row) TURBO_TOPO(blade_row,turboThetaMin)
#define T_THETAMAX(blade_row) TURBO_TOPO(blade_row,turboThetaMax)


#define T_HUBL(blade_row) TURBO_TOPO(blade_row,turboHub_t_list)
#define T_SHROUDL(blade_row) TURBO_TOPO(blade_row,turboShroud_t_list)
#define T_INLETL(blade_row) TURBO_TOPO(blade_row,turboInlet_t_list )
#define T_OUTLETL(blade_row) TURBO_TOPO(blade_row,turboOutlet_t_list )
#define T_THETAL(blade_row) TURBO_TOPO(blade_row,turboTheta_t_list )
#define T_THETAMINL(blade_row) TURBO_TOPO(blade_row,turboThetaMin_t_list )
#define T_THETAMAXL(blade_row) TURBO_TOPO(blade_row,turboThetaMax_t_list )

#define T_L_LENGTH(blade_row) TURBO_TOPO(blade_row,t_list_length)
#define T_MERID(blade_row) TURBO_TOPO(blade_row,turboMerid)
#define T_ZONE(blade_row) TURBO_TOPO(blade_row,cell_zone_ids)
#endif /* RP_3D */

FLUENT_EXPORT void initTurboCoord( Domain * );
FLUENT_EXPORT void nodeMeridionalCoordinate( Domain * );
FLUENT_EXPORT void nodeMeridionalCoordinateAbs( Domain * );
FLUENT_EXPORT void nodeSpanwiseCoordinate( Domain * );
FLUENT_EXPORT void nodeSpanwiseCoordinateAbs( Domain * );   /* Hub to Shroud */
FLUENT_EXPORT void nodeSpanwiseSHCoordinateAbs( Domain * ); /* Shroud to hub */
FLUENT_EXPORT void nodePitchwiseCoordinate( Domain * );
FLUENT_EXPORT void nodePitchwiseCoordinateAbs( Domain * );
FLUENT_EXPORT void fl_spline(real x[], real y[], int n, real yp1, real ypn, real y2[]);
FLUENT_EXPORT void splint(real xa[], real ya[], real y2a[], int n, real x, real *y);
FLUENT_EXPORT void findNodeInGrid(Node *n, int *pimin, int *pimax, int *pjmin,
                                  int *pjmax, int nUseJ, int index, int method);
FLUENT_EXPORT void getCylindricalCoord(Node *n, real *axial, real *radius);
FLUENT_EXPORT void freeTurboMemory(void);
FLUENT_EXPORT void determineOrigin(Turbo *turboSurf, int nSurfNodes,
                                   Turbo *turboInletLine, int nInletLineNodes, int nSurf, int index);
FLUENT_EXPORT void copyTurboCurve(Turbo *curve1, Turbo *curve2);
FLUENT_EXPORT void determineOriginPoints(Turbo *turboHubLine, int nHubLineNodes,
                                         Turbo *turboShroudLine, int nShroudLineNodes,
                                         Turbo *turboInletLine, int nInletLineNodes,
                                         Turbo *turboOutletLine, int nOutletLineNodes, int index);
FLUENT_EXPORT real determineTheta(Node *node);
FLUENT_EXPORT Turbo *fillTurboThread(Domain *domain, Thread *thread, Turbo *turbo, int *pnNodes);
FLUENT_EXPORT Turbo *sortNodes(Turbo *turbo, Turbo *pOrigin, int nNodes);
FLUENT_EXPORT Turbo *calcLinearValue(Turbo *turbo, int nNodes);
FLUENT_EXPORT Turbo *transferThetaMax(Turbo *minLine, int nMinPts, Turbo *maxLine, int nMaxPts);
FLUENT_EXPORT Turbo *removeDuplicateNodes(Turbo *turbo, int *pnNodes);
FLUENT_EXPORT Turbo *determineIntersectingNodes(Turbo *pt, Turbo *turbo, int nNodes,
                                                Turbo *intersect, int *pnNodes);
FLUENT_EXPORT TurboGrid *create2DTurboGrid(Turbo *hubLine, Turbo *shroudLine,
                                           Turbo *inletLine, Turbo *outletLine,
                                           int nHubNodes, int nShroudNodes,
                                           int nInletNodes, int nOutletNodes, int index);


FLUENT_EXPORT TurboGrid *create2DTurboGridRaw(Turbo *hubLine, Turbo *shroudLine,
                                              Turbo *inletLine, Turbo *outletLine,
                                              int nHubNodes, int nShroudNodes,
                                              int nInletNodes, int nOutletNodes);
FLUENT_EXPORT void renderTurboAvg(void);
FLUENT_EXPORT void renderTurboGrid(int);
FLUENT_EXPORT void cyl2cartesian(real r, real a, real theta, real *pt);
FLUENT_EXPORT void findPointInGrid(real Cx, real Cy, int *pimin, int *pimax,
                                   int *pjmin, int *pjmax, int nUseJ, int index);
FLUENT_EXPORT void findPointInGridTree(real Cx, real Cy, int *pimin, int *pimax,
                                       int *pjmin, int *pjmax, int index);
FLUENT_EXPORT void findPointInGridSerial(real Cx, real Cy, int *pimin, int *pimax,
                                         int *pjmin, int *pjmax, int index);
FLUENT_EXPORT real determineThetaFromPoints(real xp, real yp, real zp);
FLUENT_EXPORT void createSpanwiseSurface(Domain *domain, char *param, real percent,
                                         int type, real *valmin, real *valmax);

FLUENT_EXPORT void calcTurboAverages(Domain *domain, real *min,
                                     real *max, real *minall, real *maxall);
FLUENT_EXPORT void createMeridionalSurface(Domain *domain, char *param, real percent,
                                           int type, real *valmin, real *valmax);
FLUENT_EXPORT void createTurboSurface(Domain *domain, char *param, real percent,
                                      int type, real *valmin, real *valmax);
FLUENT_EXPORT int plotTurboXYData(int type, real dist, const char *fname);
FLUENT_EXPORT void renderTurboSurf(int type);

FLUENT_EXPORT int Define_Turbo_Topology(Domain *domain, int *list_length, int **list, int index);
FLUENT_EXPORT void  Delete_Turbo_Topology(int index);
FLUENT_EXPORT int find_turbo_list_id(int index);
FLUENT_EXPORT void turbo_add_cell_zone(int index, Thread *thread);
#if RP_3D

#endif /* RP_3D */
#endif
