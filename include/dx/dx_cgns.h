/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#if SEEM

/* "cgsize_t" is nothing but "cxindex" data type. But using cgsize_t is helpful when working with
   cgns mid-level library. In addition, 2 new eleemnt types will be supported "PYRA_13" and "NFACE_n"*/

#if RP_NODE
#ifndef CGNSTYPES_H
#define CGNSTYPES_H

#if USE_INT64
#define CG_BUILD_64BIT  1
#else
#define CG_BUILD_64BIT  0
#endif

#ifdef _WIN32
# define CG_LONG_T __int64
#else
# define CG_LONG_T long
#endif

# if CG_BUILD_64BIT
typedef CG_LONG_T cgsize_t;
# else
typedef int cgsize_t;
# endif
typedef int cgerr_t;
typedef int cgint_t;
typedef double cgid_t;

typedef CG_LONG_T cglong_t;
typedef unsigned CG_LONG_T cgulong_t;
#endif

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *\
 *      Element types                                                    *
 \* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef enum
{
  ElementTypeNull, ElementTypeUserDefined,  /* 0, 1,  */
  NODE, BAR_2, BAR_3,         /* 2, 3, 4,   */
  TRI_3, TRI_6,         /* 5, 6,  */
  QUAD_4, QUAD_8, QUAD_9,       /* 7, 8, 9, */
  TETRA_4, TETRA_10,        /* 10, 11,  */
  PYRA_5, PYRA_14,        /* 12, 13,  */
  PENTA_6, PENTA_15, PENTA_18,      /* 14, 15, 16,  */
  HEXA_8, HEXA_20, HEXA_27,       /* 17, 18, 19,  */
  MIXED, PYAR_13, NGON_n, NFACE_n     /* 20, 21, 22, 23 */
} ElementType_t;
#endif
#if CGNS_LIB
FLUENT_EXPORT void build_face_elements(Thread **, cgsize_t *, int, cxboolean);
/*FLUENT_EXPORT void build_face_elements(cxboolean, Thread **, int *, int);*/
FLUENT_EXPORT int element_zone_type_face(Thread **, int);
FLUENT_EXPORT int get_face_element_array_size_cell(Thread **, int *, int, cxboolean);
FLUENT_EXPORT void build_element_array_cell(Domain *, Thread **, cgsize_t *, cxboolean, int);
FLUENT_EXPORT void build_solution_array_face(Domain *, Thread **, char *, real *, int, cxboolean);
FLUENT_EXPORT void get_size_cell(Domain *, Thread **, cgsize_t *, int);
FLUENT_EXPORT void Store_Face_Global_Ids(Thread **, int, cxindex **, cxboolean);
FLUENT_EXPORT void Store_Cell_Global_Ids(Thread **, int, cxindex **);
#endif /*CGNS_LIB*/

#endif /*SEEM*/
