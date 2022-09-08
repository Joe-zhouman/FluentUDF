/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "dll.h"
#include "cxbool.h"
#include "stddef.h"


typedef enum
{
  LocationTypeSurface,
  LocationTypeThread
} LocationType;

/*data structures to fill field data through rpc*/
typedef struct surface_data
{
  size_t len;     /* Number of scalars */
  float *flist;     /* List of scalars */
  size_t nactive;                /* iactive pointer length (can be zero)*/
  int *iactive;                  /* whether scalar value is valid (can be null)*/
  int i;      /* Surface id */
  LocationType type; /*type: surface or thread*/
#if BREAK_RPC_MSGS
  unsigned int len_total;
  unsigned int nactive_total;
#endif
} surface_data;

typedef struct surface_data_list
{
  surface_data *s;  /*individual surface data*/
  size_t nids;   /*number of surfaces*/
  const char *name;       /*name of the field*/
  int nodeValues;   /*bool flag to check node values are stored in surface data*/
} surface_data_list;

typedef struct vec
{
  float base[3];
  float vector[3];
  float normal[3];
} vec;

typedef struct vector_data
{
  vec *v;
  size_t len;
  int id;            /*surface id*/
  LocationType type; /*type: surface or thread*/
} vector_data;

typedef struct vector_data_list
{
  vector_data *vd;         /*individual surface's vector data*/
  size_t nids;  /*number of surfaces*/
  const char *vname;        /*name of vector field*/
  float scale;       /*scale*/
} vector_data_list;


/*
 *  For the given ids, prepare the data values for a given field name
 */
FLUENT_EXPORT void CX_Prepare_Field_Data(const char *name, const int *const ids, int nids, cxboolean node_values, LocationType type);

/*
 *  For the given id, fetch the data values for a given field name
 */
FLUENT_EXPORT void CX_Get_Field_Data(const char *const name, LocationType type, int id, cxboolean node_values, float **data, int *size, int **active, int *activesize);

/*
 *  For the given ids, prepare the data values for a given vector field name
 */
FLUENT_EXPORT void CX_Prepare_Vector_Field_Data(const char *const vname, const int *const ids, int nids, char *components[], LocationType type);

/*
 *  For the given id, fetch the data values for a given vector field name
 */
FLUENT_EXPORT void CX_Get_Vector_Field_Data(const char *const vname, LocationType type, int id, vec **data, float *scale, char *components[]);

/*
 *  Clear field & vector data for given surface ids
 */
FLUENT_EXPORT void CX_Clear_Cached_Data_For_Surfaces(int *surface_ids, int nids);

/*
 *  clear field data for a given field function
 */
FLUENT_EXPORT void CX_Clear_Field_Data(const char *name);

/*
 *  clear all field data
 */
FLUENT_EXPORT void CX_Clear_All_Fields(void);

/*
 *  clear active data for a given surface id
 */
FLUENT_EXPORT void CX_Clear_Active_Data(int id);

FLUENT_EXPORT void CX_Fill_Field_Data(const char *name, cxboolean node_values, int nids, surface_data *s);
FLUENT_EXPORT void CX_Fill_Vector_Data(const char *vname, float scale, int nids, vector_data *vd);
typedef struct CX_Surface_Comp_Struct CX_Surface;
FLUENT_EXPORT CX_Surface *CX_Get_Surface(int id);
/*
surfaceId   : surface id.
group       : TRUE: Flag to get surface zone group. FALSE: Flag to get surface zone type.
result      : Zone group or its type. Returned to user.
resultLength: string length of zone group or its type.

*/
FLUENT_EXPORT void CX_Get_Surface_Zone(int surfaceId, CXBoolean group, char *reulst, int resultLength);

#ifdef __cplusplus
}
#endif
