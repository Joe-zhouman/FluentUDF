/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#pragma once

#include "Ppoint.h"

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "cxbool.h"
#include "seem.h"

#define labelXOffset  0.08
#define scaleXOffset  0.03
#define labelYOffset  0.12
#define scaleYOffset  0.02

#define winMinX 0.30
#define winMaxX 0.90
#define winMinY 0.20
#define winMaxY 0.90

#define minorTick 0.005
#define majorTick 0.010
#if _NT
#define labelHeightString "size=0.035wru"
#define scaleHeightString "size=0.024wru"
#define keyHeightString   "size=0.125wru"
#define keyHeightStringLessEntries "size=0.25wru"
#else
#define labelHeightString "size=0.03wru"
#define scaleHeightString "size=0.02wru"
#define keyHeightString   "size=0.02sru"
#endif

// This factor was decided based on what size looks appropriate visually
extern int plotWindowMarkerFactor;

typedef struct Rule
{
  int n_major, n_minor;
  double d_major, d_minor;
  double nice_min, nice_max;
  CXBoolean tight;
  double ini_delta_on_axis;   // This will be used to shift the drawing of major (and corresponding minor) ticks on the axis in a way that they are only drawn for the numbers of the format: X.Y*e^Z
} Rule;


void  CX_Display_Plot_Direction(int sid);
void    CX_XY_Sort_Data         (int, float *, float *, int *);
FLUENT_EXPORT int CX_XY_Plot_Data   (int, float *, float *, FILE *, int *, CXBoolean);
int CX_XY_Append_Data (int, int, float *, float *);
void    CX_Insert_Axes_In_Main  (float, float, float, float, float, float, CXBoolean *);
Pointer CX_XY_Read_From_File(FILE *fp);
void    CX_XY_Check_Text_Size(void);
void    CX_XY_Set_Text_Sizes(CXBoolean);
void    CX_Check_Set_Readable_Font_Size(void);

void Nice_Range(int npts, double *xmin, double *xmax, Rule *rule, CXBoolean integerp, CXBoolean userSelectedRange);
void XY_Frame(const char *xunit, const char *yunit, CXBoolean xlog, CXBoolean ylog,
              double xmin, double xmax, double ymin, double ymax,
              Rule *xrule, Rule *yrule, CXBoolean skip_xlabel);
void XY_Scale( double xmin, double xmax, double ymin, double ymax);
void XY_ClipToRange(double xmin, double xmax, double ymin, double ymax);

void constructXTitle(char *title);
void constructYTitle(char *title);

// When text size of label for Y-Axis is going out of window bounds, reduce the size of the text
// till it fits into window, required only for non-axis aligned text
void XY_UpdateYLabelTextSize(int winId);

#ifdef __cplusplus
}
#endif
