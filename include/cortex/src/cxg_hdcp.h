/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/*
 *  cxg_hdcp.h
 *  Cortex graphics - hardcopy functions.
 */
#ifndef _CXG_HDCP_H
#define _CXG_HDCP_H

#include <hc.h>
#include "cxbool.h"

#ifdef __cplusplus
extern "C" {
#endif

extern HC_KEY hardcopy_key;

int CX_Valid_Hardcopy_Format_With_Embedded_Window( const char *fmt );
int CX_Valid_Hardcopy_Format( const char *fmt );
char *CX_Hardcopy_Filename (char *file);
void CX_Hardcopy_Window(char *file);
void CX_Hardcopy_Preview(const char *previewsegment);
void CX_Hardcopy_Segment(char *file, char *segment);
int get_hardcopy_driver(const char *inFormat, char *outDriverType, char *outHardcopySegmentPath /* or NULL */, const char *inFile /* or NULL*/, CXBoolean *outHardwareAccelerated /* or NULL*/);
void CX_Reset_Windownumber(void);

#ifdef __cplusplus
}
#endif

#endif /* _CXG_HDCP_H */
