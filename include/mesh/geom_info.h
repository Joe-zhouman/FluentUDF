/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "storage/mem.h"
#include "storage/typedefs.h"

typedef struct interior_geom_info_struct
{
  ConstIntArray fc0;
  ConstIntArray fc1;
  ConstRealVectorArray A;
  ConstRealVectorArray dr0;
  ConstRealVectorArray dr1;
  ConstRealArray ds;
  ConstRealArray A_by_es;
  ConstRealVectorArray es;
  ConstRealVectorArray centroid;
  ConstRealVectorArray centroid0;
  ConstRealVectorArray centroid1;
  ConstRealArray volume0;
  ConstRealArray volume1;
} Interior_Geom_Info;

typedef struct periodic_geom_info_struct
{
  ConstIntArray fc0;
  ConstIntArray fc1;
  face_t *const f_shadow;
  ConstRealVectorArray A;
  ConstRealVectorArray centroid;
  ConstRealVectorArray centroid_shadow;
  ConstRealVectorArray centroid0;
  ConstRealVectorArray centroid1;
  ConstRealArray volume0;
  ConstRealArray volume1;
} Periodic_Geom_Info;

typedef struct boundary_geom_info_struct
{
  ConstIntArray fc0;
  ConstRealVectorArray A;
  ConstRealVectorArray centroid;
  ConstRealVectorArray centroid0;
  ConstRealArray volume0;
} Boundary_Geom_Info;

extern FLUENT_EXPORT Interior_Geom_Info Get_Interior_Geom_Info(Thread *t);
extern FLUENT_EXPORT Periodic_Geom_Info Get_Periodic_Geom_Info(Thread *t);
extern FLUENT_EXPORT Boundary_Geom_Info Get_Boundary_Geom_Info(Thread *t);

#define GET_PERIODIC_FACE_GEOMETRY(f, c0, c1, pgi, ds, es, A_by_es, dr0, dr1, rm)\
{ real NV_VEC(dr1r);\
    NV_VV(dr0, =, pgi.centroid[f],-,pgi.centroid0[c0]);\
    NV_VV(dr1, =, pgi.centroid_shadow[pgi.f_shadow[f]],-,pgi.centroid1[c1]);\
    NV_ROTN_V(dr1r, =, dr1,rm);\
    NV_VV(es, =, dr0,-,dr1r);\
    ds = NV_MAG(es);\
    NV_S(es,/=,ds);\
    A_by_es = NV_DOT(pgi.A[f],pgi.A[f])/NV_DOT(es,pgi.A[f]);\
}

#define GET_BOUNDARY_FACE_GEOMETRY( f, c0, bgi, ds, es, A_by_es, dr0 ) \
{                                                                      \
    NV_VV(dr0,=,bgi.centroid[f], -, bgi.centroid0[c0]);                \
    ds = NV_MAG(dr0);                                                  \
    NV_VS(es,=,dr0,/,ds);                                              \
    A_by_es = NV_DOT(bgi.A[f], bgi.A[f])/ NV_DOT(es, bgi.A[f]);        \
}

#define  CACHE_INTERIOR_FACE_GEOMETRY(gi,f,t,A,ds,es,A_by_es,dr0,dr1) \
      NV_V(A,=,(gi).A[f]);       \
      ds = gi.ds[f];             \
      NV_V(es,=,(gi).es[f]);     \
      A_by_es = (gi).A_by_es[f]; \
      NV_V(dr0, =,(gi).dr0[f]);  \
      NV_V(dr1, =,(gi).dr1[f]);

/* long diffusion for solid materials in porous regions */
#define GET_INTERIOR_FACE_GEOMETRY_LD(f,t,gi,fA,d0,d1,A_by_dr0,A_by_dr1)\
{\
  fA =  NV_MAG2(gi.A[f]);        /* face Area magnitude */ \
  A_by_dr0 = fA/NV_DOT(gi.dr0[f],gi.A[f]); \
  A_by_dr1 = fA/NV_DOT(gi.dr1[f],gi.A[f]); \
  fA = sqrt(fA);                           \
  d0 =  NV_DOT(gi.dr0[f],gi.A[f])/fA; /* dr0 = X_f - X_c0    */ \
  d1 =  NV_DOT(gi.dr1[f],gi.A[f])/fA; /* dr1 = X_f - X_c1    */ \
  if(d0 < REAL_MIN) d0 = ABS(d0); /* in case of dr0 or dr1  */ \
  if(d1 < REAL_MIN) d1 = ABS(d1); /* in opp. dir. w.r.t A */ \
}
#define GET_INTERIOR_FACE_GEOMETRY_LONG(f,t,gi,es0,es1,A_by_es0,A_by_es1) \
{ \
    real Amag2 = NV_MAG2(gi.A[f]); \
    NV_VS(es0, =, gi.dr0[f], /, NV_MAG(gi.dr0[f])); \
    NV_VS(es1, =, gi.dr1[f], /, NV_MAG(gi.dr1[f])); \
    A_by_es0 = Amag2/NV_DOT(es0,gi.A[f]); \
    A_by_es1 = Amag2/NV_DOT(es1,gi.A[f]); \
}


#ifdef __cplusplus
}
#endif
