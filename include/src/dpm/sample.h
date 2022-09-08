/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SAMPLE_H
#define _FLUENT_SAMPLE_H

#include "dll.h"

/* max length of sample name */
#define SAMPLE_NAME_LENGTH 256
#define SAMPLE_DATA_MAX 100

typedef struct input_sample_struct
{
  char name[SAMPLE_NAME_LENGTH];
  int ndata;   /* number of data points in each field */
  /* int nbin; */  /* number of bins for sorting radial/axial samples */
  char *data_names[SAMPLE_DATA_MAX];
  struct sample_field_struct *field;
  struct input_sample_struct *next;
} Input_Sample;

typedef struct sample_field_struct
{
  real *data;
  struct sample_field_struct *next;
} Sample_Field;

FLUENT_EXPORT Input_Sample *Alloc_Sample(void);
FLUENT_EXPORT Sample_Field *Alloc_Sample_Field(Input_Sample *sample);
FLUENT_EXPORT Input_Sample *Sample_List(void);
FLUENT_EXPORT Input_Sample *Pick_Input_Sample(const char *);
FLUENT_EXPORT int Find_Field_Index(Input_Sample *, const char *);
FLUENT_EXPORT void Delete_All_Samples(void);
FLUENT_EXPORT void Delete_Sample(Input_Sample *);
#if !RP_NODE
FLUENT_EXPORT void Read_Sample_Section(FILE *, int section);
#endif
FLUENT_EXPORT void Update_Dynamic_Samples(Domain *);
FLUENT_EXPORT Sample_Field *Lookup_Sample_Field(Input_Sample *, char *);
FLUENT_EXPORT void Sample_Bins(const char *, const char *, const char *, const char *, cxboolean,
                               cxboolean, cxboolean, cxboolean, cxboolean, cxboolean,
                               real, real, int, double *, const char *);
FLUENT_EXPORT void Sample_Min_Max(const char *, const char *, real *, real *);

#endif /* _FLUENT_SAMPLE_H */
