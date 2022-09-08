/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SURF_H
#define _FLUENT_SURF_H

#include "dll.h"

#ifdef __cplusplus
extern "C" {
#endif

/* NODES_PER_CELL = FACES_PER_CELL = RP_3D ? 4 : 3 (from mem.h) */

#if RP_3D
#define FACETS_PER_CELL 4
#else
#define FACETS_PER_CELL 1
#endif

#if PARALLEL
#define CHARS_PER_NUM 16
#endif

#define STORE_CX_CELL(cx_cell,cell,thread)((cx_cell)->ct.c = (cell), (cx_cell)->ct.t = (thread))
#define RP_CELL(cx_cell)((cell_t)(cx_cell)->ct.c)
#define RP_FACE(cx_cell)((cell_t)(cx_cell)->ct.f)
#define RP_THREAD(cx_cell)((struct thread_struct *)(cx_cell)->ct.t)
#define SET_RP_THREAD(cx_cell,thread)((cx_cell)->ct.t = (thread))

extern FLUENT_EXPORT int rp_thread(CX_Cell_Id *c);

#define REUSE_ALLOC(old_len, new_len, type, ptr)\
 if (old_len < new_len) {\
  if (old_len !=0) CX_Free((char *) ptr);\
  ptr = (type *) CX_Malloc((unsigned) new_len * sizeof(type));\
  old_len = new_len;\
}

/* Array temporaries that are used in CX_End_Surface, Contour_Surface,
 * lisosurface, lpointsurface, IsoSurface, PointSurface.
 * It is important to note that not two uses can overlap
 */
extern FLUENT_EXPORT float *floats_array1;
extern FLUENT_EXPORT int floats_array1_len;

#if PARALLEL
extern FLUENT_EXPORT int *ints_array1;
extern FLUENT_EXPORT int  ints_array1_len;
#endif


/* quadric definition structure
 * f(X,Y,Z) = xx*X^2 + yy*Y^2 + zz*Z^2 + xy*X*Y ...
 */
/* Quadric struct is now defined in cxiface.h */

FLUENT_EXPORT void Clear_Post_Node_List(void);
FLUENT_EXPORT void ApplyQuadric(Quadric *);
FLUENT_EXPORT void Scale_Surface_Threads(Thread **thread_list,
                                         int n,
                                         float scale_factor);

FLUENT_EXPORT void PartitionSurface(int int_cell_p,
                                    int out_surf,
                                    int in_part1,
                                    int in_part2);
FLUENT_EXPORT cxboolean exterior_cell_p(cell_t, Thread *);

FLUENT_EXPORT face_t face_index_to_face(cell_t, Thread *, int f, Thread **);

FLUENT_EXPORT Thread *thread_arg(Pointer x, const char *msg);

FLUENT_EXPORT int surface_id_arg(Pointer x, const char *msg);

FLUENT_EXPORT cxboolean compute_line_facet_normal( Surface *, int, real []);
FLUENT_EXPORT cxboolean compute_facet_normal( Surface *, int, real []);
FLUENT_EXPORT cxboolean compute_facet_centroid( Surface *, int, float []);
FLUENT_EXPORT void Zone_Surface(int, Thread *);
FLUENT_EXPORT void compute_surface_min_max_points( Surface *s, float p_min[3], float p_max[3]);

#if RP_NODE
# define INTERFACE_FACE(f,t) \
  (((!NULL_CELL_P(F_C0(f,t))) && (!NULL_CELL_P(F_C1(f,t)))) && \
  (!I_AM_NODE_SAME_P(C_PART_ACTIVE(F_C0(f,t),(t)->t0)) || \
   !I_AM_NODE_SAME_P(C_PART_ACTIVE(F_C1(f,t),(t)->t1))))
#endif

#ifdef __cplusplus
}
#endif

#endif /* _FLUENT_SURF_H */
