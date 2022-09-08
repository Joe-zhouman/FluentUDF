/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _CXG_WIN_H
#define _CXG_WIN_H


#include <stdio.h>
#if WIN64
#include <basetsd.h>
#endif

#if !_NT && 0
#include <X11/Xlib.h>
#endif /* !_NT */

#include "cxbool.h"


typedef struct window_layout
{
  int window;
  float left, right, bottom, top;
} window_layout;


#if defined(__cplusplus)
extern "C" {
#endif

/*
extern int cxActiveWindow;
*/
extern CXBoolean queueHOOPSEvents;
extern CXBoolean events_queued;
extern CXBoolean track_queued_events;

void      get_window_name(int window_id, char *win_name);
void      CX_Get_Active_Window_Name(char *windowName);
int       get_window_id_from_name(char *);
void      layout_xyplot_segment(char *win_name);
float     get_text_segment_height_offset(char *win_name);
float     getResolutionFactor();
float     calculateResolutionFactor(int iResolutionX, int iResolutionY);

void      CX_Setup_Window_Segment_Tree(void);
void      CX_Setup_XY_Plot_Segment(void);
void      CX_Scale_Layout(char *name, int width, int height);
void      CX_Resize_Color_Scale(char *win_name);
void      CX_Resize_Scale_Ruler();
float     CX_Test_Graphics_Performance(CXBoolean useFullUpdate);
void      CX_Update_Visibility_Of_Scale_Ruler();
void      CX_Update_Scale_Ruler_Units(char *, float);
int       CX_Next_Available_User_Window(void);
/*Please note the diffrence between CX_Next_Available_Reserved_Window(void) and CX_Next_Available_UnreservedWindow_Id.
  CX_Next_Available_Reserved_Window is similar to CX_Next_Available_User_Window and always opens a next reserved window but it won't
  look whether previously opened reserved windows are unreserved and can be used for rendering. The other function it will check always
  if any previous open reserve window is not reserved it will return that
  CX_Next_Available_Reserved_Window: Independent of window state reserved, will check only whether it is opened or not.
  CX_Next_Available_Unreserved_Window_Id: Will check window state reserved, will return if an immediate unreserved window is encountered from its
                                          initial range to final range. */
int       CX_Next_Available_Reserved_Window(void);
int       CX_Next_Available_Unreserved_Window_Id(void);
#if 0
int       CX_Next_Available_Unreserved_User_Window_Id(void);
int       CX_Next_Available_Unreserved_Automatic_Window_Id(void);
#endif
int       CX_Current_Window(void);
int       CX_Active_Window(void);
void      CX_Set_Hoops_View_Name_String(const char *name);
const char *CX_Get_Hoops_View_Name_String();
CXBoolean CX_Active_Window_Busy (void);
CXBoolean   CX_Window_Opened(int window_id);
void      CX_Lock_Active_Window(void);
void      CX_Unlock_Active_Window(void);
int       CX_Is_Active_Window_Locked(void);
void      CX_Set_Rendering_Options_To_All_Windows(void);
void      CX_Update_Foreground_Background_For_All_Colormaps(void);
int      *CX_Get_Open_Window_List(void);

int       CX_Set_Window_Owner(char *owner_label);
int       CX_Get_Window_Owner(char *owner_label);
int       CX_Get_Window_With_Owner(char *owner_label);
void      CX_Check_Set_Readable_Font_Size();

/* Returns TRUE if it's found successful in setting the given driver */
CXBoolean      CX_Try_Setting_Graphics_Driver(const char *);

/* To set the flag `creatingGraphicsWindow`*/
void      CX_Set_Is_Creating_Window(CXBoolean);

/* To get the flag `creatingGraphicsWindow`*/
CXBoolean CX_Get_Is_Creating_Window(void);

/* To create graphics primitive segments (or sbubsegments) under "?Active/inner" segment */
void      CX_Create_Graphics_Primitive_Segments(void);

/* To resume back graphics segment tree when we flush everything below "?Active/inner" segment.
   Example: Animation playback workflow, reference FUNCTION: `CX_Prep_Window_For_Image()`,
   CALL: `HC_Flush_Contents("?active/inner", "everything")`.
*/
void      CX_Resume_Graphics_Segment_Tree(void);

float     Pref_Get_Graphics_Window_Line_Width(void);
float     Pref_Get_Titles_Line_Width(void);
/* To know whether physical screen is a 4K or higher resolution monitor */
CXBoolean CX_Is_A_4k_OR_Higher_Resolution_Monitor(void);
/* To get the width and the height of the physical screen in pixels */
void      CX_Get_Screen_Resolution(int *width, int *height);
void      CX_Open_Window(int window_id);
void      PrepareWindowForQtPlot(int windowID, CXBoolean triggerEvents);
void      CX_Activate_Window_By_ID(int window_id, CXBoolean setDefaultView);
void      CX_Set_Window_Size_Position(char *win_name);
void      CX_Close_Window(int window_id);
void      CX_Hide_Window(int window_id);

void      CX_Set_Graphics_Color_Scheme (const char *) ;
void      CX_Set_Current_Graphics_Color_Scheme (void) ;

void      CX_Set_Window_Title(int window_id, const char *title);
void      CX_Set_Windows_Titles_For_Object(const char *objectName, const char *title);
void      CX_Get_Window_Title(int window_id, char *title);

void      CX_On_Window_Changed(int newWindowID);

//If you're unsure, send 'triggerEvents' as TRUE.
//It can be set to FALSE for background update purposes, for example.
void      CX_Set_Current_Window(int windowID);
void      CX_Set_Active_Window(int windowID, CXBoolean triggerEvents);
int       CX_Use_Window(int window_id, CXBoolean triggerEvents);
int       CX_Use_Window_Name(char *window_name, CXBoolean triggerEvents);

void      CX_Update_Current_Window_Alias(const char *segment);

int       CX_Reserve_Window(int window_id);
int       CX_Reserve_N_Windows(int first, int number);
void      CX_Free_Reserved_Window(int window_id);
void      CX_Free_N_Reserved_Windows(int first_id, int number);
int       CX_Is_Window_Reserved(int window_id);
int       CX_Next_Window_Can_Reserve(int start);
int      *CX_Get_User_Window_List(int *num);
int      *CX_Get_Reserved_List(int *num);
void      CX_Get_Graphics_Object_Internal_Name_By_WindowID(int windowID, char *oName);
void      CX_Get_Graphics_Content_Name_By_Window_Id(int windowId, char *returnString);
CXBoolean CX_Is_A_Mesh_Window(int windowID, CXBoolean countSceneWithOnlyMeshes);
CXBoolean CX_Is_A_Reserved_Window(int windowId);
CXBoolean CX_Is_A_User_Window(int windowID);
CXBoolean CX_Is_An_Embedded_Window(int windowID);

void      CX_Update_Window(void);
#if WIN64
LONG64    CX_Prep_Window_For_Image(int window_id);
#else
long      CX_Prep_Window_For_Image(int window_id);
#endif


#if !_NT && 0
void      CX_Graphics_Window_Cursor(Display *d, Cursor c);
#endif /* !_NT */

int       CX_Show_Subwindow(const char *segment, char *subwindow);
void      CX_Show_Subwindow_Segment(const char *subwindow, char *segment);


void      CX_Graphics_Layout(int window, float left, float right, float bottom, float top);
void      CX_Save_Graphics_Layout(FILE *f);

void      CX_Raise_Window(int);
void      OpenURL(const char *url);

int         CX_Is_Hardcopy_Mode(void);
void        CX_Activate_Graphics_Hardcopy_Mode(void);
void        CX_Activate_Graphics_Normal_Mode(void);
CXBoolean   CX_Is_Scale_Pixel_Aspect_Ratio_Changed();
void        CX_Set_Scale_Pixel_Aspect_Ratio_Changed(CXBoolean changed);
void        CX_Set_Current_Hardcopy_Segment(const char *segment);
const char *CX_Get_Current_Hardcopy_Segment();
void        CX_Update_Event_Cheker(void);
CXBoolean   CX_Window_Has_Geometry(int windowID);
CXBoolean   CX_Is_Qt_Plot_Window(int windowID);
CXBoolean doesGlobalColormapExistsForWindow(int iWinID);


#if defined(__cplusplus)
}
#endif

#endif /* CXG_WIN_H */
