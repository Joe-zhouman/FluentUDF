/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_PDF_GRAPHICS_H
#define _FLUENT_PDF_GRAPHICS_H

#include "dll.h"

FLUENT_EXPORT Pointer Inquire_PDF_1D_Function_Names(void);
FLUENT_EXPORT Pointer Inquire_PDF_2D_Function_Names(void);
FLUENT_EXPORT Pointer Get_PDF_1D_Array(const char *);
FLUENT_EXPORT Pointer Get_PDF_Curve (const char *, int, real);
FLUENT_EXPORT Pointer Inquire_Flamelet_1D_Function_Names(void);
FLUENT_EXPORT Pointer Inquire_Flamelet_2D_Function_Names(void);
FLUENT_EXPORT Pointer Get_Flamelet_1D_Array(const char *);
FLUENT_EXPORT Pointer Get_Flamelet_Curve(char *, int, real);
FLUENT_EXPORT void Contour_PDF_2D_Function(void);
FLUENT_EXPORT void Grid_PDF_2D_Function(void);
FLUENT_EXPORT Pointer Fill_Flamelet_2d_Func_Arrays (const int, const char *);
FLUENT_EXPORT Pointer Fill_PDF_2d_Func_Arrays (const char *, int, real, const char *, int, const char *, const char *, const char *, const char *, int, real);
FLUENT_EXPORT Pointer Inquire_Pdf_Type (void);
FLUENT_EXPORT Pointer Inquire_Flamelet_Type (void);
FLUENT_EXPORT Pointer Inquire_Par_Premix_Props(void);
FLUENT_EXPORT Pointer Fill_Strained_Flamelet_Flame_Speed_Arrays (const int , const char *);


#endif /* _FLUENT_PDF_GRAPHICS_H */
