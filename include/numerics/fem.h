
/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_FEM_H
#define _FLUENT_FEM_H

#define begin_gauss_loop(igauss, etype, order) for (igauss=0; igauss<get_ngauss(etype, order); igauss++) {
#define   end_gauss_loop(igauss, etype, order) }

/* 32 = 8 x ( 1 + 3 )                                           */
/* Considering 8 noded hex to be the max NNODES for any element */
/* 1 for the shape function itself                              */
/* 3 for the derivatives of the shape function w.r.t x,y,z      */
#define ALLOC_SHFN(shfn) shfn = CX_Malloc(32*sizeof(real));
#define FREE_SHFN(shfn) FREE_TEMP(shfn);

int   get_ngauss(int etype, int order);

/* 2D: xg[]   = [ x1 y2 x2 y2 x3 y3 ... xi yi ]                  i = 1:NNODES                */
/*     shfn[] = [ N1 N1,x N1,y  N2 N2,x N2,y  ... Ni Ni,x Ni,y ] i = 1:NNODES                */
/* 3D: xg[]   = [ x1 y1 z1 x2 y2 z2 x3 y3 z3 ... xi yi zi ]                     i = 1:NNODES */
/*     shfn[] = [ N1 N1,x N1,y N1,z  N2 N2,x N2,y N2,z  ... Ni Ni,x Ni,y Ni,z ] i = 1:NNODES */
/* wt = weight                                                                               */
/* j  = |J|                                                                                  */
void  get_shfn_jw(real *xg, int etype, int order, int igauss, real *shfn, real *j, real *wt);

#define SHFN(shfn,inode,ideri) (shfn[inode*(ND_ND+1) + ideri])

#endif /* _FLUENT_FEM_H */

