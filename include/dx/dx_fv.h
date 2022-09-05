/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/* ------------------------------------------------------------ */
/* Fieldview Unstructured output */
/* The definitions are copied from sample files provided by Fieldview */
/* Numeric tags (codes) for FIELDVIEW binary file format. */

#ifndef _FLUENT_DX_FV_H
#define _FLUENT_DX_FV_H

#include "dll.h"

#define FV_MAGIC   0x00010203 /* decimal 66051 */
#define FV_VERSION_MAJOR 3
#define FV_VERSION_MINOR 0
/* Content of the file (grid only, results only or combined). */
#define FV_GRIDS_FILE           1
#define FV_RESULTS_FILE         2
#define FV_COMBINED_FILE        3

#define FV_NODES                1001
#define FV_FACES                1002
#define FV_ELEMENTS             1003
#define FV_VARIABLES            1004
#define FV_BNDRY_VARS           1006
#define FV_ARB_POLY_FACES       1007
#define FV_ARB_POLY_ELEMENTS    1008
#define FV_ARB_POLY_BNDRY_VARS  1009

#define FV_TET_ELEM_ID          1
#define FV_HEX_ELEM_ID          2
#define FV_WEDGE_ELEM_ID        3
#define FV_PYR_ELEM_ID          4
#define FV_ARB_POLY_ELEM_ID     5

#define MAX_NUM_ELEM_FACES     6
#define BITS_PER_WALL  3
#define ELEM_TYPE_BIT_SHIFT    (MAX_NUM_ELEM_FACES*BITS_PER_WALL)
#define GRID (fileType==FV_GRIDS_FILE ? TRUE:FALSE)
#define RESULT (fileType==FV_RESULTS_FILE ? TRUE:FALSE)
/*#define BOTH (fileType==FV_COMBINED_FILE ? TRUE:FALSE)*/
/* Values for "wall_info" array (see comments in fv_encode_elem_header). */
#if defined(__STDC__) || _NT
#define A_WALL         (07u)
#define NOT_A_WALL     (0u)
#else
#define A_WALL         (07)
#define NOT_A_WALL     (0)
#endif
#define FV_EPSILON     1e-04
#define NODE_FIRST(n) (2*n-1)
#define NODE_SECOND(n) (2*n)
FLUENT_EXPORT void Write_Fv_Uns(Domain *, FILE *, Pointer, Pointer);
FLUENT_EXPORT void Write_Fv_Uns_Region(Domain *, FILE *, Pointer, Pointer);
FLUENT_EXPORT void Write_Fv(Domain *, FILE *, Pointer);
FLUENT_EXPORT void WriteFvUnsHeader(const char *, Domain *, Pointer);
FLUENT_EXPORT void WriteFvUnsFastResultInfo(Domain *, Pointer);
FLUENT_EXPORT void WriteFvUnsMeshData(Domain *, const char *, Pointer, Pointer, Pointer);
FLUENT_EXPORT size_t fwrite_str80(const char *str, FILE *fp);
FLUENT_EXPORT void WriteFvUnsFastResult(Domain *, Pointer);
FLUENT_EXPORT void WriteFvUnsFastVelocity(Domain *, Pointer);

FLUENT_EXPORT void Initialize_Parallel_FV_Export(Domain *, Pointer, Pointer, Pointer, Pointer, Pointer);
FLUENT_EXPORT void Store_Parallel_FV_Result(Domain *, Pointer, Pointer);
FLUENT_EXPORT void Store_Parallel_FV_Velocities(Domain *, Pointer);
FLUENT_EXPORT void Store_Parallel_FV_BResults(Domain *, Pointer);
FLUENT_EXPORT void Write_Parallel_FV_File(Domain *, Pointer, Pointer, Pointer, Pointer);
FLUENT_EXPORT void Finalize_Parallel_FV_Export(Domain *);

/* Multigird surface export */
FLUENT_EXPORT void Init_Parallel_FV_SurfExport(Domain *, Pointer, Pointer, Pointer, Pointer);
FLUENT_EXPORT void Write_Parallel_FV_SurfFile(Domain *, Pointer, Pointer, Pointer);
FLUENT_EXPORT void Store_FV_Surf_Result(Pointer, Pointer);
FLUENT_EXPORT void Store_FV_Surf_Bresults(Domain *, Pointer);
FLUENT_EXPORT void Finalize_FV_Surf_Export(void);

FLUENT_EXPORT void WriteFvUnsSurfHeader(const char *, Domain *, Pointer);
FLUENT_EXPORT void WriteFvUnsSurfMeshData(Domain *, const char *, Pointer, Pointer, Pointer);

#endif /* _FLUENT_DX_FV_H */
