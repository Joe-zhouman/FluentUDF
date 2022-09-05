/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_FILTER_H
#define _FLUENT_FILTER_H

#include "dll.h"

#define MAX_FIELD_NAME 64

#if !RP_HOST
# if RP_3D
#  define NCHILDREN 8
# else
#  define NCHILDREN 4
# endif
#endif

#if !RP_HOST
typedef struct point_struct
{
  real x[3];
  real *value;
  struct point_struct *next;
  cell_t cell;
  Thread *thread;
} OPoint;

typedef struct oct_sruct
{
  OPoint *pointlist;
  real minx[3];
  real maxx[3];
  struct oct_sruct *children[NCHILDREN];
  struct oct_sruct *parent;
  int npoints;
  OPoint *points;
  real *values;
} Oct_Tree;

#endif
typedef struct field_struct
{
  char name[MAX_FIELD_NAME];     /* The displayed name */
  char pick[MAX_FIELD_NAME];     /* key name */
  Svar sv;                       /* storage variable for this field */
  int  nd;                       /* domain index */
  struct field_struct *next;
} FIELD;

FLUENT_EXPORT void Interpolate_From_File(Domain * domain
#if !RP_NODE
                               , const char * fname
#endif
                               , int * zones, int nzones);
FLUENT_EXPORT void Initialize_and_Update_Data(Domain *domain);
FLUENT_EXPORT void Write_Interp_Data(Domain *,
#if !RP_NODE
                                     const char *,
#endif
                                     char [][MAX_FIELD_NAME], int,
                                     int [], int);
FLUENT_EXPORT Pointer Interp_Field_Names(Domain *domain);
FLUENT_EXPORT void init_field_list(Domain *);
FLUENT_EXPORT FIELD *pick_field(char *);
FLUENT_EXPORT void init_selected_fields_list(Domain *, char [][MAX_FIELD_NAME], int, int [], int);
extern FLUENT_EXPORT int total_selected_fields;
extern FLUENT_EXPORT FIELD **selected_fields_list;
#if !RP_HOST
FLUENT_EXPORT void Interpolate_From_Oct_Tree(Domain *, Oct_Tree *);
FLUENT_EXPORT Oct_Tree *new_oct(void);
FLUENT_EXPORT void add_points_to_tree(Oct_Tree *oct, int total_points, int total_fields, int *f_lengths);
FLUENT_EXPORT void traverse_tree(real key[3], Oct_Tree *oct);
FLUENT_EXPORT void make_tree(Oct_Tree *oct);
FLUENT_EXPORT void remove_tree(void);
#else
FLUENT_EXPORT void Interpolate_From_Oct_Tree(Domain *);
#endif

#endif /* _FLUENT_FILTER_H */
/*  ------  */
/* -------  */
