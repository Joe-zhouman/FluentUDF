/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*
* Contains methode declarations of both to import and export images, mpeg files
*/

#pragma once
#include "cxconfig.h"
#if WIN64
#include "basetsd.h"
#endif
#include "cxbool.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int nwd; /* number of window dumps/hardcopies */

void CX_Insert_Image(char *name, char *pickedseg, float Xpos, float Ypos, unsigned imgWd, unsigned imgHt, unsigned char *image, unsigned pixel_size);
void CX_Annotate_Image(char *imagefile);
void CX_Load_Image_In_Window(char *filename, char *format, int window_id, char *dest_path);
void CX_Load_Image_In_Segment(char *filename, char *format, char *segment);
unsigned char *CX_PPM_Read(char *filename, unsigned int *x, unsigned int *y);
CXBoolean CX_Handle_Export_Format(const char *file, const char *format, const char *driver);

void write_image_file(const char *format, const char *file, unsigned char *rgb, int image_x, int image_y);

#if HAVE_MPEG
CX_POINTER_SIZED_INT CX_MPEG_Open(char *fn, int bufsiz);
void CX_MPEG_Close(CX_POINTER_SIZED_INT m);
int  CX_MPEG_Next(CX_POINTER_SIZED_INT ml);
void CX_MPEG_Rewind(CX_POINTER_SIZED_INT m);
#endif /*HAVE_MPEG*/

#ifdef __cplusplus
}
#endif
