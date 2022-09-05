/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#include "dll.h"

#ifndef MAX
# define MAX(a, b) ((a)>(b)? (a): (b))
# define MIN(a, b) ((a)>(b)? (b): (a))
#endif


#if RP_DOUBLE
#  define REAL_FMT "%le"
#  define INT_FMT "%d"
#else
#  define REAL_FMT "%e"
#  define INT_FMT "%d"
#endif

#ifndef TRUE
# define TRUE 1
#endif
#ifndef FALSE
# define FALSE 0
#endif

FLUENT_EXPORT void Find_Element_Values_From_XML_File_Element(char *, char *, int, char *);
FLUENT_EXPORT void Trigger_Maxwell(const char *, const char *, const char *, const char *, const char *, const char *, const char *, const char *, const char *, const char *, const char *);
FLUENT_EXPORT void Write_Cell_Centroid_xyz (const char *, Pointer );
#if PARALLEL
FLUENT_EXPORT void Write_Centroid_Data_For_Maxwell(Pointer, Pointer);
FLUENT_EXPORT void Distribute_Maxwell_Loss_Parallel(Pointer, Pointer, Pointer);
#if RP_HOST
typedef struct MAXWELL_CELL_STRUCT
{
	int cell_ids;
	float cell_volumes;
	float cell_centroids[ND_ND];
}maxwell_cell_data;
FLUENT_EXPORT int cell_struct_comparator(const void *p1, const void *p2);
#endif
#endif
FLUENT_EXPORT void Assign_Averaged_Loss(Pointer, const char *, const char *);
FLUENT_EXPORT void Create_Input_Xml_File(char *, char *, char *, char *, char *, char *, char *, char *, char *, char *, char *, int);
FLUENT_EXPORT void Write_Temperature_For_EM(const char *tfile, const char *cfile, Pointer p);
