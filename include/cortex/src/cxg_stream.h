/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _CXG_STREAM_H
#define _CXG_STREAM_H

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

// Hoops stream files import limit related.
static int cxCurrentNumberOfStreamFilesImported = 0;
static int cxMaxNumberOfStreamFilesImportLimit = 0;
int CX_Get_Max_Number_Of_Stream_Files_Import_Limit();
void CX_Set_Max_Number_Of_Stream_Files_Import_Limit();
//Other
void CXG_Write_Hoops_Stream(const char *segment, const char *file);
void CXG_Read_Hoops_Stream(const char *segment, const char *file);
void CXG_Write_Geom_Hoops_Stream(const char *file);

void CXG_Write_Metafile(const char *filename, const char *top_segment, CXBoolean save_state);
int CXG_Read_Metafile(const char *filename, const char *target_segment, int window_id);
void CXG_Write_Stream_Frame(const char *filename, const char *top_segment);
int CXG_Read_Stream_Frame(const char *filename, const char *target_segment, int window_id);

#if defined(__cplusplus)
}  /* end extern "C" */
#endif

#endif
