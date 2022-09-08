/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _CXG_H
#define _CXG_H
#ifdef __cplusplus
extern "C" {
#endif
#if ADD_MISSING_PROTOS
int fread ();
int fscanf  (FILE *, const char *, ...);
int fwrite  (char *, int, int, FILE *);
int tolower (int);
#endif

/* cxgcolor.c */
#define USER_PREFERENCE_COLOR_STRING "preference color"
#define PREFERENCE_BACKGROUND_COLOR_STRING "background"
/* #define PREFERENCE_BACK_GROUND_STYLE_STRING "background-style" */
#define PREFERENCE_BACKGROUND_GRADIENT_COLOR_STRING "background-gradient"
#define PREFERENCE_FOREGROUND_COLOR_STRING "foreground"
#define PREFERENCE_WALL_COLOR_STRING "pref-wall-color"
#define PREFERENCE_EDGE_COLOR_STRING "pref-edge-color"
#define PREFERENCE_SURFACE_COLOR_STRING "pref-surface-color"


/* lcxg.cpp */
void init_lcxg(void);

Pointer gui_not_available(void);
CX_Callback CALLBACK_ARG(Pointer p, char *m);

/* for text subwindow */
#define N_TEXT_LINES   4
#if GRAPHICS
extern CXBoolean inFrame;

/* cxgraph.cpp */
/* These keys will be caught when pressed in the graphics window. */
#include "CxGraphicsStructures.h"
#define KEY_EVENTS "arrow, control, function, _, ^"

#define MAXPTS 32



// True will load and False will unload hoops wrapper library
CXBoolean handleCxHoopsLibrary(CXBoolean load);

extern float cxGrVersion;
extern CXBoolean cxSuspendGraphicsUpdates;
extern void display3dVectorsForInletOrOutlet(const char *segment, HC_KEY keySurfaceShell, int surfaceId);

CXBoolean CX_Segment_Key_Exists(HC_KEY key);

#ifdef HOOPS_INTERUPTS
void CX_Set_Hoops_Callbacks(void);
void CX_Clear_Hoops_Callbacks(void);
#endif

/* HOOPS-21.x onward, the direct specification of event checker address
 * has been replaced with callback definition.
 */
typedef void
(*him_function)(HC_ANY_ARGS);

#define HIM_FUNCTION(function) (him_function)(function)




extern float colormap[2 + CX_MAX_COLOR_RAMP][3];

void unlimit_colors(void);
void install_colormap(void);


/* cxscene.c */
void CX_Set_One_Geoms_Attr_In_Hoops(int gindx);
void CX_Transfer_Mmatrix_To_Highlight(int index);
int show_color_by_value(char *filter, float out[3]);

/* cxgraph.cpp */
void CX_Surface_Add_Conditional_Action(const char *actionStyle, const char *actionCondition, int surfaceID, CXBoolean isNegativeSurfaceCondition);

void CX_Set_Edge_Color_For_Grid_Style();

void CX_Setup_Window_Level_Styles();
void CX_Redefine_Alias(const char *alias, const char *newPath);
#if !WIN64
CXBoolean CXG_Hardware_Acceleration_Has_Problems(CXBoolean ShowWarningsInConsole);
#endif
char *CXG_Get_Linux_Distribution();

void updateFastDisplayModeStyle();


/* cxgevent.cpp */
extern CXBoolean wf_mode;
extern CXBoolean autospin;


FLUENT_EXPORT Selection_Info *CX_Select_Multiple_Geometry_Box(int *sel_count, char *entity, cxboolean);
FLUENT_EXPORT void *CX_Select_Multiple_Geometry_Polygon(void);
FLUENT_EXPORT Selection_Info *Get_Multiple_Geometry_Polygon(int *sel_count, char *entity, cxboolean);

HC_KEY Mouse_Polyline(char *highlight);

void CXG_Save_Camera_Xform(void);
int CXG_Restore_Camera_Xform(void);
void Clear_Saved_Camera_Xform(void);

void CXG_Update_Graphics_Window_Line_Style(const float lineWidth);
void CXG_Update_Text_Window_Line_Style(const float lineWidth);
void CXG_Update_Hardcopy_Line_Style(void);

/* To reset the color which is defined in hoops database.
 * colorName : Simple name to be added to the list of definitions.
 *  newRGB   : RGB values to compose new color definition.
 */
void CXG_Reset_Hoops_Color_Name(const char *colorName, float newRGB[3]);

/* To convert Hex color code to rgb.
 * preferenceVar: preference var
 * rgb          : returned to user in the range 0 to 1.
 */
void CXG_Get_RGB_Value(const char *colorNameorHexValue, float rgb[3]);
void CXG_Set_Graphics_Foreground_Color(const char *colorNameorHexValue);
void CXG_Set_Graphics_Background_Color(const char *colorNameorHexValue);
void CXG_Set_Graphics_Background_Style(const char *style);
void CXG_Set_Graphics_Background_Gradient_Color(const char *colorNameorHexValue);
void CXG_Set_Graphics_Wall_Face_Color(const char *colorNameorHexValue);
void CXG_Set_Graphics_Edge_Color(const char *colorNameorHexValue);
void CXG_Set_Graphics_Surface_Color(const char *colorNameorHexValue);
void CXG_Set_Graphics_Title_Window_Frame_Color(const char *colorNameorHexValue);
void CXG_Set_Graphics_Window_Help_Text_Color(const char *colorNameorHexValue);
void CXG_Redraw_Active_Window_Boundary_Vectors_For_Surface(int surfaceId, CXBoolean isNewGraphicsObject, void *dataService);
//Doesn't update display. Caller should make sure to do it.
void CXG_Redraw_Boundary_Markers_For_Active_Window();
void CX_Redraw_Boundary_Markers_For_All_Windows();
void CXG_Update_Inlet_Markers_Style(void);
void CXG_Update_Outlet_Markers_Style(void);
void CXG_Apply_Inlet_Outlet_Markers_Color(CXBoolean inlet);
void CXG_Update_Inlet_Outlet_Markers_Colors(void);


#if SPACEBALL

void process_spaceball_motion (char *);
void process_spaceball_button (char *);

#endif /* SPACEBALL */

/* TGrid or Meshing mode related declarations */
void CX_TGrid_Set_Color_On_Flag_Faces(int, const char *);
void CX_TGrid_Unset_Color_On_Flag_Faces(int);
void CX_TG_Initialize_Zone_Edges(const char *, const char *, CXBoolean);
void CX_TGrid_Set_Visibility_On_Flag_Faces(int, CXBoolean);
#endif      // GRAPHICS

#ifdef __cplusplus
}
#endif

#endif /* CXG_H */
