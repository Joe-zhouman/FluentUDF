/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/
/*
 * A Utility class for reading csv profile format
 *
 * COPYRIGHT ANSYS. ALL RIGHTS RESERVED.
 *
 */
#ifndef _PROFILEREADER_
#define _PROFILEREADER_

#ifdef __cplusplus
#include <cstdio>
#include "stringutils.h"
#endif

#include "global.h"

#ifdef __cplusplus
extern "C" {
#endif

FLUENT_EXPORT int CSV_Get_Profile(char *name, int *n_fields, const char **field_name,  double **values, int *nrow, int index, cxboolean method, char *ref_name);
FLUENT_EXPORT int CSV_Read_Profile(FILE *filep); /*returns number of profiles read*/
FLUENT_EXPORT void CSV_Read_Profile_Done(); /*Release memory*/
FLUENT_EXPORT int Read_Generic_CSV_File(FILE *fp);
#if RP_HOST
FLUENT_EXPORT void CSV_Get_Profile_Name(int index, char *name);
FLUENT_EXPORT void CSV_Get_Profile_Ref_Name(char *, char *);
FLUENT_EXPORT int CSV_Get_Nprofiles(void);
FLUENT_EXPORT void CSV_Get_Reference_Frame_Name(int, char *);
FLUENT_EXPORT void CSV_Get_Reference_Frame_Parent_Name(int, char *);
FLUENT_EXPORT void CSV_Get_Reference_Frame_Origin(int, double[3]);
FLUENT_EXPORT void CSV_Get_Reference_Frame_Zpoint(int, double[3]);
FLUENT_EXPORT void CSV_Get_Reference_Frame_XZpoint(int, double[3]);
FLUENT_EXPORT int CSV_Get_Nframes(void);
FLUENT_EXPORT void CSV_Set_Reference_Frame_Name(int, const char *);
FLUENT_EXPORT void Clear_CSV_Profile_Data_Members(void);
FLUENT_EXPORT int CSV_Get_profile_Parameter_Size(int index);
FLUENT_EXPORT void CSV_Get_Profile_Parameter_First_Value(int index1, int index2, char *name);
FLUENT_EXPORT double CSV_Get_Profile_Parameter_Second_Value(int index1, int index2);
FLUENT_EXPORT int CSV_Get_profile_Spatial_Field_Size(int);
FLUENT_EXPORT void CSV_Get_Profile_Spatial_Fields(int, int, char *name);
FLUENT_EXPORT size_t CSV_Get_Profile_Nnodes(const char *);
FLUENT_EXPORT size_t CSV_Get_Profile_Nfaces(const char *);
FLUENT_EXPORT size_t CSV_Get_Profile_Nnodes_Per_Face(const char *, int);
FLUENT_EXPORT int CSV_Get_Profile_Node_Id(const char *, int, int);
FLUENT_EXPORT void Get_Profile_Field_Unit(const char *, const char *, char *);
#endif
#ifdef __cplusplus
}
#endif

#endif /* _PROFILEREADER_*/
