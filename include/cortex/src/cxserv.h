/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _CXServ_h_
#define _CXServ_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dll.h"
#include "cxmacros.h"
#include "cxbool.h"
#include "cxlist.h"
#include "cxm.h"
#include "cxconfig.h"
#include "CxHoops/CxGraphicsDefines.h"
#include "cxsurfdefn.h"

#if ultrix || __ultrix || _solaris /* def'd in seem.c or cxlocalize.h */
extern char *strdup(const char *);
#endif

#define Internal_Error(m) CX_Internal_Error(m,__LINE__,__FILE__)

#ifndef FLGUI
#include "seem.h"
#endif

#define CX_MAX_PATH 2048

#ifndef MOTIF
typedef CX_POINTER_SIZED_INT Widget;
typedef const char *String;
#endif

#if !UDF_COMPILER

#include <float.h>
/* 64-bit integer type */
#if (_lnx86 || _lnamd64 || _linmic || _lop64 || _lnarm64 || _lnia64 || _aix51_64 || _ultra_64 || _aix51 )
# include <stdint.h>
#else
# if (_hpux11 || _hpux11_64 || _hpux11_ia64)
#  include <inttypes.h>
# else
typedef long long int64_t;
# endif
#endif
#if (_lnamd64)
# define int64_fmt "ld"
#else
# define int64_fmt "lld"
#endif

#define PACK_INT64_INTO_2INT(i64,ihigh,ilow) (ihigh) = (int) ((i64) >> 32), (ilow) = (int) ((i64) & ((((int64_t) 1) << 32) - 1))
#define UNPACK_2INT_TO_INT64(ihigh,ilow,i64) (i64) = (((int64_t) ((unsigned int) (ihigh))) << 32) | ((int64_t) ((unsigned int) (ilow)))

#endif /* UDF_COMPILER */
extern int iReferenceWinID;   // Reference primary window to which all the windows should be synchronized.

typedef enum
{
  COLOR_SCHEME_WORKBENCH = 0,
  COLOR_SCHEME_CLASSIC
} Graphics_Color_Scheme ;

//Mostly lifted from qnamespace.h
typedef enum
{
  ArrowCursor,
  UpArrowCursor,
  CrossCursor,
  WaitCursor,
  IBeamCursor,
  SizeVerCursor,
  SizeHorCursor,
  SizeBDiagCursor,
  SizeFDiagCursor,
  SizeAllCursor,
  BlankCursor,
  SplitVCursor,
  SplitHCursor,
  PointingHandCursor,
  ForbiddenCursor,
  WhatsThisCursor,
  BusyCursor,
  OpenHandCursor,
  ClosedHandCursor,
  DragCopyCursor,
  DragMoveCursor,
  DragLinkCursor
} CxCursorShape;

//If ExpressionType and ValidExprType is modified then
//please update corresponding types in cxgui.scm
typedef enum
{
  CONSTANT,
  EXPRESSION,
  PARAMETER,
  PROFILE,
  NONE_EXPRESSION,
  CELL_REGISTER
} ExpressionType;
typedef enum
{
  TYPELESS_EXPR,
  REAL_EXPR,
  INT_EXPR,
  BOOL_EXPR,
  REAL_LIST_EXPR,
  INT_LIST_EXPR
} ValidExprType;

typedef enum LicenseTypeRequest
{
  PRO = 0,/*Do not change it is used to set the value of requiested license from the server*/
  PREMIUM,
  ENTERPRISE
} LicenseTypeRequest;
extern LicenseTypeRequest cxLicenseLevel;

/* Scene defines - needs to match scheme code in cxrender.scm */
#define CX_SCENE_TYPE_BOOLEAN 0
#define CX_SCENE_TYPE_FLOAT 1
#define CX_SCENE_TYPE_FLOAT_ARR 2
#define CX_SCENE_TYPE_INT   3
#define CX_SCENE_TYPE_STRING  4

#define CX_TYPE_CONTOUR         0
#define CX_TYPE_VECTOR          1
#define CX_TYPE_SURFACE         2
#define CX_TYPE_GRID          3
#define CX_TYPE_PATH            4
#define CX_TYPE_PROFILE   5
#define CX_TYPE_TEXT    6
#define CX_TYPE_OTHER_GEOM  7
#define CX_TYPE_DPM             8

/* work arrays are used for storing float values for xy plotting, surface data */

#define CX_WORK_ARRAY_SCALAR 0
#define CX_WORK_ARRAY_VECTOR 1


#ifndef  UDF_COMPILER
# define UDF_COMPILER 0
#endif

#if  ! UDF_COMPILER
#if DEBUG
#define CX_Message_If_Debug(...) CX_Message(__VA_ARGS__)
#else
#define CX_Message_If_Debug(...) ((void)0)
#endif
#endif


#define HSMAP_EINDEX(h,i) \
  (h->use_int64 ? ((long*)h->entity_id)[i] : ((int*)h->entity_id)[i])
#define HSMAP_EIDX(h,i) (h->idx ? h->idx[i] : -1)
#define HSMAP_FLAG(h,i) (h->flags ? h->flags[i] : 0)
#define SET_HSMAP_FLAG(h,i,flag) if(h->flags) h->flags[i] = flag;
#define HSMAP_SIZE(h,i) (h->szmap ? h->szmap[i] : -1)
#define HSMAP_SKEW(h,i) (h->skmap ? h->skmap[i] : -1)

#define ENTITY_FREE 0x1
#define ENTITY_MULTI 0x2
#define ENTITY_SIZE 0x4
#define ENTITY_SKEW 0x8

#define HSMAP_GET_ENTITY_FLAG(h,i,flag) \
  (h->flags ? (h->flags[i] & flag) : 0)

typedef struct CX_Shell_Map_Struct
{
  CXBoolean use_int64;
  void *entity_id;           /* cxindex */
  int *idx;                  /* local idx, e,g, cell-face idx */
  int *flags;                /* face entity flag map. Storing info if face is free/multi*/
  float *szmap;
  float *skmap;
} CX_Shell_Map;

/* Callback data structure. */

#define CX_INTEGER_DATA 1
#define CX_REAL_DATA 2
#define CX_STRING_DATA 3
#define CX_STRING_LIST_DATA 4

#define FLU_LONG_PTR CX_POINTER_SIZED_INT

typedef struct cx_cbdata
{
  int type;
  union uval
  {
    FLU_LONG_PTR asInteger;
    float asReal;
    const char *asString;
    char **asStringList;
  } value;
} CX_CBData;

/* C callbacks are pointers to functions returning void. */
typedef void (*CX_CCallback) (Widget, CX_CBData *);

#ifdef FLGUI
typedef char *Pointer;
/* prototype for stringcons is declared in sprim.h, as I don't include
   any seem file, the iris complains for uixm_text.c
*/
Pointer stringcons (char *s);
#else
/* Scheme callbacks are pointers to Scheme objects. The object should be
   a symbol, and the value of the symbol in the user-initial-environment
   should be a procedure. The procedure will be called with two arguments,
   a widget identifier and a data value. The type of the data value depends
   upon the type of the widget.
 */

typedef Pointer CX_SCallback;
#endif

/* Generic callback structure */
typedef char *CX_Callback;

/*  Specification of position of panel components. */

typedef struct cx_panel_position
{
  char *op;     /* left-of, right-of, above, below */
  union
  {
    Widget widget;    /* These should be the same size ... */
    long integer;
    double real;                /*Not in use, Just for size issue with CX_Attrib*/
  } as;
  int dummy;      /* Needed to match CX_Attrib struct size. */
} CX_Panel_Position;

#define CX_SET_POSITION_ARG(pos, n, d) \
  ((void)( (pos).op = n, (pos).as.widget = (Widget)(d), (&(pos)+1)->op = 0 ))

/* Maximum number of colors in the colormap. */
#define CX_MAX_COLOR_RAMP 100

/* Maximum Number of Graphics Windows */
#define MAX_WINDOWS_OLD 20
#define MAX_WINDOWS 100
#define GRAPHICS_WINDOWS_LOWER_LIMIT 0
#define GRAPHICS_WINDOWS_UPPER_LIMIT 99
#define USER_WINDOWS_LOWER_LIMIT 50
#define USER_WINDOWS_UPPER_LIMIT 99
#define RESERVED_WINDOWS_LOWER_LIMIT 0
#define RESERVED_WINDOWS_UPPER_LIMIT 49

/* Maximum label, name length (geometry, attributes in cxscene) */
#define MAX_NAME_LENGTH 256

/* Constants for real entry */
#define CX_REAL_ENTRY_LIST_MAX 50
#define CX_REAL_ENTRY_MAX 1.e20
#define CX_REAL_ENTRY_MIN -1.e20

/* Constants for integer entry */
#define CX_INTEGER_ENTRY_MAX 1000000
#define CX_INTEGER_ENTRY_MIN -1000000

/* Constants for list */
#define CX_LIST_STR_MAX_LEN 1024/*Max number of characters in a string of list-item symbol-list-item drop-down-list-item etc*/
#define CX_JOURNAL_STR_LEN 2048/*Number of characters in a string being used for journaling*/

#define CX_LIST_TREE_WIDGET_PATH_LENGTH 512

#define SM_MAX_FIELD 100/*no of variables*/

#define SERVER_INFO_PATH_MAX_LEN 4096

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/* cxserv.c */
extern int *cmdArgCountPtr;    //For caching command line argument count
extern char **cmdArgs;     //For caching command line argument(s)
void  CX_Server_Init    (int *, char *[], char *, char *);
FLUENT_EXPORT Pointer CX_Eval_Scheme_Fn(char *fname, ...);
FLUENT_EXPORT Pointer CX_Interpret_String(const char *);
FLUENT_EXPORT Pointer CX_Execute_Command(Pointer);
FLUENT_EXPORT char *CX_Interpret_String_To_String(char *);
FLUENT_EXPORT extern void CX_Wake_Up_Main_Thread(void);
FLUENT_EXPORT void CX_Set_JournalFileName(const char *);
FLUENT_EXPORT void CX_Set_CaseFileName(const char *);
FLUENT_EXPORT void CX_Set_ProjectFileName(const char *);
char *CX_Get_JournalFile_Name(void);
char *CX_Get_ProjectFile_Name(void);
char *CX_Get_CaseFile_Name(void);
char *CX_Get_Next_Command_Option(void);
void CX_Mark_Command_Option_Complete(void);
FLUENT_EXPORT void CX_ReSet_ErrorExceptions(void);
FLUENT_EXPORT const char *CX_Get_ErrorExceptions(void);
FLUENT_EXPORT void CX_AddStringToErrorException(const char *p_szNewString);
FLUENT_EXPORT void CX_AddCharToErrorException(char p_charNewCharacter);

FLUENT_EXPORT void      CX_Start_Gui_Action(void);
FLUENT_EXPORT void      CX_End_Gui_Action(void);
void CX_Remoting_Transmit_Error(const char *, int);
void      CX_Append_Client_Message(char *);
Widget    CX_Create_Message_Box(void);
char *cx_extract_msg_type(char *, int *);
void    CX_Set_Graphics_Mode_Changing_Flag(int);
int CX_Reading_Journal  (void);
int CX_Writing_Journal  (void);
void  CX_Check_Journal  (void);
void  CX_Stop_Reading_Journal (void);
Pointer CX_Call_Callback(char *, Widget, CX_CBData *, int);
FLUENT_EXPORT void  CX_Next_Event   (void);
void CX_Process_UI_Events(void);
FLUENT_EXPORT void  CX_Process_Events (void);
void CX_Show_Current_Graphics_Event(char *event);
void    CX_Process_Pending_Callbacks(void);
CXBoolean CX_Is_3D_Mode(void);
CXBoolean CX_Is_Grid_Valid(void);
int CX_Delay_Splash_Screen(void);

FLUENT_EXPORT int CX_Interrupts_Enabled (void);
FLUENT_EXPORT void  CX_Disable_Interrupts (void);
FLUENT_EXPORT void  CX_Enable_Interrupts  (void);
FLUENT_EXPORT void  CX_Interrupt    (void);
FLUENT_EXPORT void  CX_User_Interrupt (void);
FLUENT_EXPORT int CX_IterationTimeStep_Interrupt(int interruptFromSignal);

FLUENT_EXPORT void raise_SIGINT(void);
/*
 * For transient/unsteady simulations, user can interrupt during a timestep.
 * Here, a flag is set telling cortex to interrupt simulation at the end
 * of timestep. This flag is queried using the function
 * 'CX_To_Be_Interrupted_End_Of_Timestep'
 * At the end of timestep, cortex process will be signaled
 * about the conclusion of the timestep. This information can be queried using
 * the function CX_Is_End_Of_Timestep.
 */
FLUENT_EXPORT int CX_Check_Interrupt(void);
int CX_Check_Pending_Interrupt (void);
FLUENT_EXPORT void  CX_Reset_Interrupt  (void);

FLUENT_EXPORT void      CX_Signal_Timesteps_Start       (void);
FLUENT_EXPORT void      CX_Signal_Timesteps_End       (void);
FLUENT_EXPORT void      CX_Signal_Timestep_Start       (void);
FLUENT_EXPORT void      CX_Signal_Timestep_End       (void);
FLUENT_EXPORT void      CX_Signal_Iterations_Start       (void);
FLUENT_EXPORT void      CX_Signal_Iterations_End       (void);

FLUENT_EXPORT CXBoolean CX_Get_First_Interrupt(void);
FLUENT_EXPORT void CX_Set_First_Interrupt(CXBoolean yesNo);
FLUENT_EXPORT CXBoolean CX_Get_Second_Interrupt(void);
FLUENT_EXPORT void CX_Set_Second_Interrupt(CXBoolean yesNo);

FLUENT_EXPORT CXBoolean CX_Get_Timesteps_Start(void);
FLUENT_EXPORT void CX_Set_Timesteps_Start(CXBoolean yesNo);
FLUENT_EXPORT CXBoolean CX_Get_Timesteps_End(void);
FLUENT_EXPORT void CX_Set_Timesteps_End(CXBoolean yesNo);
FLUENT_EXPORT CXBoolean CX_Get_Timestep_Start(void);
FLUENT_EXPORT void CX_Set_Timestep_Start(CXBoolean yesNo);
FLUENT_EXPORT CXBoolean CX_Get_Timestep_End(void);
FLUENT_EXPORT void CX_Set_Timestep_End(CXBoolean yesNo);
FLUENT_EXPORT CXBoolean CX_Get_Iterations_Start(void);
FLUENT_EXPORT void CX_Set_Iterations_Start(CXBoolean yesNo);
FLUENT_EXPORT CXBoolean CX_Get_Iterations_End(void);
FLUENT_EXPORT void CX_Set_Iterations_End(CXBoolean yesNo);

// Fires a callback when the state changes from solving to not solving & vice-versa
FLUENT_EXPORT void CX_Update_Solution_State();

void    CX_Enable_Checkpoint_Signal (void);
void    CX_Disable_Checkpoint_Signal (void);
FLUENT_EXPORT void  CX_Primitive_Error  (const char *, ...);
void  CX_Internal_Error (const char *, int, const char *);
FLUENT_EXPORT int CX_Message    (const char *, ...);
FLUENT_EXPORT int CX_Warning    (const char *, ...);
FLUENT_EXPORT void  CX_Message_Literal(const char *);
FLUENT_EXPORT void  CX_Warning_Literal(const char *);
FLUENT_EXPORT int   cxprintf  (FILE *, const char *, ...);
void CX_Warning_On_Cortex_Init(const char *message);
void CX_Message_On_Cortex_Init(const char *message);

void  CX_Need_Update    (CX_Callback);
char *CX_Client_PWD   (void);
void  CX_Client_CD    (char *);

int CX_Client_LS    (char *, char *, char *, char ***, int *);
void  CX_Client_LS_Return (char **, int);
int cx_readdir    (char *, char *, char *, char ***, int *);

int CX_Log (char *, ...);
char *CX_Expand_Filename(const char *, char *, int, int);

void CX_Html_To_Plain_Text(char *text, const char *html);

FLUENT_EXPORT void *CX_Malloc_MU  (size_t, const char *, int);
FLUENT_EXPORT void *CX_Realloc_MU (void *, size_t, const char *, int);
FLUENT_EXPORT void *CX_Calloc_MU (size_t, size_t, const char *, int);
FLUENT_EXPORT void  CX_Free_MU    (void *, const char *, int);
/* Mem functions which do not handle interrupts */
FLUENT_EXPORT void *CX_Malloc_MU_Unsafe (size_t, const char *, int);
FLUENT_EXPORT void *CX_Realloc_MU_Unsafe  (void *, size_t, const char *, int);
FLUENT_EXPORT void *CX_Calloc_MU_Unsafe (size_t, size_t, const char *, int);
FLUENT_EXPORT void  CX_Free_MU_Unsafe   (void *, const char *, int);
int    Get_myid(void);
void setmtrace(int);
void setmtracelog(char *);
void reportmemusage(void);
void WB_Set_Acle_Available(CXBoolean isAvail);
void WB_Set_Modal_Dialog_Open(CXBoolean isOpen);
void WB_Set_Editor_Busy(CXBoolean);
void CX_Set_SC_License_Port_At_Host(const char *porthost);/*sets license proxy for shared licensed run for system-coupling*/
void CX_Set_SC_License_Id(const char *licid);/*sets license-id  for shared licensed run for system-coupling*/
extern void rubberband_polyline_points(float *);
CXBoolean CX_Is_Modal_Dialog_Open(void);

void CX_Update_Last_Active_Time(void);
int CX_Max_Idle_Timeout(void);
long CX_Get_Idle_Time(void);
void CX_Set_Idle_Timeout_Cb(CX_Callback cb, int idle_timeout_sec);

FLUENT_EXPORT int CX_Inquire_Requested_License_Type();
/* Zoom around the current mouse pointer location */
extern void zoom_wheel(float zoomFactor, float winx, float winy);

extern CXBoolean CX_mouse_scroll_enabled;

CXBoolean Scheme_Object (Pointer); /* This should probably be in seem */

#if _NT
int strcasecmp  (const char *, const char *);
int strncasecmp (const char *, const char *, int);
#endif

/* cxrun.c */
int CX_Command_Port   (void);
Pointer CX_Connect_Info   (void);
Pointer CX_Run      (Pointer, Pointer, Pointer, Pointer);
Pointer CX_Set_Current_Process  (Pointer);
Pointer CX_Get_Current_Process  (void);
Pointer CX_Is_Process_Running (Pointer);
Pointer CX_Get_Max_Processes  (void);
Pointer CX_Listen   (int);
FLUENT_EXPORT int CX_Get_Client_ID  (void);
int CX_Set_Client_ID  (char *, int);
void  CX_Interrupt_Client (void);
void  CX_Clear_Client_Interrupt (void);
void  CX_Terminate_Client (void);
Pointer CX_Kill     (void);
Pointer CX_Kill_Current_Process (void);
FLUENT_EXPORT Pointer CX_IO_Busy    (Pointer);
CXBoolean CX_Is_Solution_Iterating(void);
Pointer CX_Is_Application_Busy (void);
FLUENT_EXPORT Pointer CX_IO_Done    (void);
void cx_client_gone(char *msg);
FLUENT_EXPORT int CX_Is_Any_Workspace_Connected(void);

#if !CX_SINGLE
void    CX_Kill_Solver          (void);
#endif

/* cxgraph.cpp */
extern CXBoolean serverTerminating;
CXBoolean cx_graphics_init  (void);
void  cx_graphics_term  (void);
void   CX_Define_Graphics_Callbacks_For_Meshing_Mode(void);
FLUENT_EXPORT CXBoolean cx_graphics_check_events  (void);
void CX_Show_Selection_Position(float *xwindow, float *ywindow, float *zwindow, float *xcamera, float *ycamera, float *zcamera);
void  cx_graphics_next_event  (void);
FLUENT_EXPORT void resetHoopsView(int windowID, CXBoolean resetHoopsViewName, CXBoolean isAPlotWindow);
void CX_Set_Model_Edge_Visibility_For_Active_Window(CXBoolean edgesOn);
void cx_reset_driver_ambient_light();
void cx_reset_driver_specular_color();
void cx_reset_driver_emission_color();
void cxg_reset_pastel_colors();
FLUENT_EXPORT CXBoolean CX_Is_One_Of_The_Darker_Graphics_Themes();

/* [2018/02/15] : The official new way of calling HC_Update_Display.
 * Now until we separate out HOOPS into its own dll, NO ONE will call the hoops one directly! :)
 */
void    CX_Update_Display();

/*Just like CX_Update_Display, but forces a full display instead of the optimized one*/
void    CX_Update_Display_Full();

//Update modern [as of 2019/03/04] graphics effects whenever relevant preferences change
FLUENT_EXPORT void CX_Update_Graphics_Effects();

FLUENT_EXPORT void CX_Enable_Update_Graphics_Effects(CXBoolean);

void CX_Update_Graphics  (void);
void    CX_Update_Display_And_Components   (void);
CXBoolean CX_Compute_Text_Extent(const char *segment, const char *text, float *xsize, float *ysize);
FLUENT_EXPORT void  CX_Restore_Logo_Size(char *win_name);/*if win_name is NULL, it will work on active window*/
FLUENT_EXPORT void CX_Restore_Axes_Size(char *win_name);

void CX_Clean_Frame(int activeWindow, const char *frameSegment);
void  CX_Start_Frame    (CXBoolean, const char *, int numPoints, const char *hoopsViewName);
FLUENT_EXPORT void  CX_End_Frame    (CXBoolean isGraphicsObject);

void CX_Set_Boundary_Markers_Conditional_Styles(void);
void  CX_Set_Rendering_Options (void);
void  CX_Set_Hidden_Surface_Options (void);
void CX_Fluent_Highlight_Surface(char *segment, int surface_id, int hi);

CXBoolean CX_Is_Running_Hardware_Driver();
CXBoolean CX_Is_Running_Null_Driver();
void CX_Get_Current_Graphics_Driver(char *name); /*puts the present graphics driver in the argument 'name', used in cxapip.cpp*/

void  CX_Layout_Windows (char *wname); /*if wname is NULL, it should work for active-window*/
void    CX_Adjust_Navigation_Pane_Width (void) ;

void  CX_Set_Titles   (void);
void  CX_Resize_Titles  (char *);
void  CX_Sync_Views_And_Update_Axes (void);

void  CX_Draw_Periodics (void);
void  CX_Periodic   (int, int, float []);

void  CX_Symmetry   (float []);
void CX_Turn_Fast_Display_Mode_On_If_Applicable(CXBoolean mousePressNeeded);
void CX_Turn_Fast_Display_Mode_On();
void CX_Turn_Fast_Display_Mode_Off();
void CX_Turn_Fast_Display_Mode_Off_If_Automatic_And_Remove_Culling();
CXBoolean CX_Is_Fast_Display_Mode_On();
void  CX_Wf_Start             (void);
void  CX_Wf_End               (void);


typedef void (*premotingcmd)();
typedef int (*premotingcmdbegin)();
typedef void (*premotingcmdend)();

typedef void (*Event_Loop_Fn)(void *);
typedef struct
{
  Event_Loop_Fn fn;
  void *data;
} Event_Loop_Fn_Info;



FLUENT_EXPORT CX_Surface *CX_Get_Surface_List(void);
FLUENT_EXPORT void CX_Set_Surface_List(CX_Surface *sflist);
FLUENT_EXPORT void CX_Set_Remoting_Fun(premotingcmd p_remotingFun, premotingcmdbegin p_remotingFunBegin, premotingcmdend p_remotingFunEnd);
FLUENT_EXPORT int CX_Register_Event_Loop_Fn(Event_Loop_Fn fn, void *data);
FLUENT_EXPORT void CX_Clear_Event_Loop_Fn(int index);
FLUENT_EXPORT void CX_Execute_Event_Loop_Fn(int index);
void executeRemotingFunEnd(void);
void executeRemotingFunBegin(void);

void  CX_Set_Color_Ramp_Range (float, float, float, float);
void  CX_Set_Color_Ramp (int, float [][3]);
void    CX_Object_Contour_Poly(Pointer p, int npt, float *pt, float val[]);
FLUENT_EXPORT void CX_Object_Insert_Pathline(Pointer, int *, float *, float *);
FLUENT_EXPORT void CX_Object_Reset_Pathline(Pointer p);
CXBoolean CX_Equal_RGB(const float rgb1[3], const float rgb2[3]);
void    CX_Set_Color            (const char *);
float CX_Color_Index_To_Value (int, int);
float   CX_Active_Ramp_Index_To_Value (int ind);
float   CX_Active_Ramp_Index_To_Value_From_Selection(int ind);
int CX_Value_To_Color_Index (float);
void  CX_Value_To_Color_FIndex_List (float *, float *, int);
void  CX_Color_Segments (void);
void  CX_Color_By_Value (float);
void  CX_Color_By_Number  (int);
void  CX_Draw_Color_Scale (void);
void  CX_Highlight_Color_Scale (int);
void  CX_Highlight_Color_Scale_Value (float);
int CX_Get_Background_Color (void);
void  CX_Update_Window  (void);
void    CX_Apply_Workbench_Color (void);

CXBoolean CX_Segment_Exists (const char *);
void  CX_Auto_Fit_Easy (void);
FLUENT_EXPORT void  CX_Auto_Scale   (void);
void  CX_Compute_BBox   (char *, float *, float *, float *, float *, float *, float *);
void    CX_Set_Auto_Scale_BBox(float bbox[3][3]);
const char *Get_Mouse_Hover_Display_Proble_Vaue(float,  float);
void ClearMouseHoverProbeAddedStuff();
void    handle_hover_event(float, float);
void    Drag_Handle(int);
float  *Get_Handle_Position(void);
void  Set_Handle_Position(float, float, float);
void  Draw_Handles(CXBoolean, CXBoolean, CXBoolean);
float  *Get_Handle_Direction(int);
void  Set_Handle_Direction(int, float, float, float);

CX_POINTER_SIZED_INT  CX_Select_Geometry  (CXBoolean *oSomethingSelected);
void  CX_Highlight_Item (char *, CX_POINTER_SIZED_INT);

void  CX_Set_Selection_Callback (CX_Callback);
CX_Callback CX_Show_Selection_Callback (void);

void  CX_Annotate (float *, float *, const char *, char *);

void  CX_Mouse_Annotate (char *);
void  CX_Mouse_Dolly    (char *);
void  CX_Mouse_Edit   (void);
void  CX_Text_Edit    (void);
FLUENT_EXPORT int CX_Mouse_Orbit    (char *);
void  CX_Mouse_Select   (void);
void  CX_Mouse_Zoom_RBBox (void);
void  CX_Mouse_MultiSelect_Box(CXBoolean add, CXBoolean toggle);
void  CX_Mouse_Roll_Zoom    (void);
void  MS_Mouse_Roll_Zoom(void);

int CX_Rubberband_Box (char *, float, float);
int CX_Rubberband_Line  (char *, float, float, float);

int CX_Multiselect_Mode (void);

void  CX_Suspend_Graphics_Updates (CXBoolean);
void  CX_Need_Graphics_Update (CXBoolean);
void    CX_Flush_Temp_Geom  (int);

void CX_Sync_Window_Views(float  position[3], float  target[3], float  up[3], float w, float h, char *project);

void  CX_Set_Camera   (float [3], float [3], float [3],
                       float, float, char *);
void  CX_Refresh_OSPRayCamera();
void  CX_Show_Camera    (float [3], float [3], float [3],
                         float *, float *, char *);
void  CX_Dolly_Camera   (float, float, float);
void  CX_Orbit_Camera   (float, float);
void  CX_Pan_Camera   (float, float);
void  CX_Roll_Camera    (float);
void  CX_Zoom_Camera    (float);
CXBoolean   show_snap_to_axis(void);
void  enable_snap_to_axis(CXBoolean flag);
void set_camera_change_should_update_graphics_effects(CXBoolean shouldUpdate);

void  CX_Set_Transform  (float m[4][4]);
void  CX_Show_Transform (float m[4][4]);
void  CX_Enable_Display_Interrupt_Callbacks (CXBoolean flag);
/* cxplane.c */
#if WIN64
int CX_Plane_Tool_Interact  (LONG64, float[][3], float[][3], float[3]);
#else
int CX_Plane_Tool_Interact  (long, float[][3], float[][3], float[3]);
#endif
void  CX_Plane_Define         (int, float[][3], int);
void  CX_Create_Plane_Tool();
void  CX_Display_Plane_Tool(const float points[3][3], const char *mode);
void  CX_Hide_Plane_Tool(void);
void CX_Get_Plane_Tool_State(float points[3][3], float centroid[3], float normal[3]);
void CX_Get_Plane_Tool_Full_State(float points[4][3], float axes[3][3], float centroid[3]);
void CX_Three_Points_From_Point_Normal(float point[3], float normal[3], CXBoolean viewPlane, float output[4][3]);
void    CX_Mpt_Shell_Define     (float[]);

void    CX_Set_Headlight        (void);
void    CX_Update_Headlight     (void);

/* cxvis.c */
void  CX_Start_Draw_Grid  (char *, int, int, char *);
void    CX_End_Draw_Grid        (void);
void  CX_Meridional_Projection  (float *, float *);
void  CX_Insert_Line    (float *);
void  CX_Insert_Polyline  (int, float *);
void  CX_Insert_Polygon (int, float *);
void  CX_Insert_Triangle  (float *);
void  CX_Insert_Tetra   (float *);
void  CX_Insert_Quad    (float *);
void  CX_Insert_Hex   (float *);
void  CX_Insert_Pyr   (float *);
void  CX_Insert_Wedge   (float *);
void  CX_Insert_Polyhedron  (int, float *, int, int *);

void  CX_RInsert_Line   (float *, int);
void  CX_RInsert_Polyline (int, float *, int);
void  CX_RInsert_Polygon  (int, float *, int);
void  CX_RInsert_Triangle (float *, int);
void  CX_RInsert_Quad         (float *, int);
void  CX_RInsert_Tetra  (float *, int);
void  CX_RInsert_Hex    (float *, int);
void  CX_RInsert_Pyr    (float *, int);
void  CX_RInsert_Wedge    (float *, int);
void  CX_RInsert_Polyhedron   (int, float *, int, int *, int);

void  CX_RLInsert_Line    (float *, long);
void  CX_RLInsert_Polyline  (int, float *, long);
void  CX_RLInsert_Polygon (int, float *, long);
void  CX_RLInsert_Triangle  (float *, long);
void  CX_RLInsert_Quad         (float *, long);
void  CX_RLInsert_Tetra (float *, long);
void  CX_RLInsert_Hex   (float *, long);
void  CX_RLInsert_Pyr   (float *, long);
void  CX_RLInsert_Wedge   (float *, long);
void  CX_RLInsert_Polyhedron    (int, float *, int, int *, long);

void  CX_Update_Contour_Type();
void  CX_Contour_Triangle (float *, float *);
void  CX_Contour_Quadrilateral (float *, float *);
void  CX_Contour_Line   (float *, float *);
void  CX_Contour_Poly   (int, float *, float *);
void  CX_Set_Grid_Options (void);
void  CX_Set_Contour_Options  (void);
void  CX_Set_Vector_Options (void);
Pointer CX_Inquire_Vector_Styles  (void);
int CX_Calc_Perpendicular_Vectors(float[], float *, float *, float *);
void  CX_Vector   (float[], float[], float);
void    CX_Define_Surface       (int, float *, int, int *, int, int, int);
extern CXBoolean CX_Is_Actual_Surface_ID(int surfaceId);
void  CX_Free_Shell   (void);
void    CX_Suspend_All_Surfaces (void);
void    CX_Render_Shell   (CX_Surface *, int, int surfaceId);
void  CX_Copy_Displayed_Shell (CX_Surface *, int, int );
void    CX_Destroy_Surface      (int);
void    CX_Destroy_Surface_All  (void);
void    CX_Append_Surface       (int, int);
void    CX_Display_Surface      (int);
void  CX_Contour_Surface  (int, int, float *, int, int *);
void  CX_Set_Vis_Name   (char *, int);
void    CX_Set_Current_Pathline_Object(Pointer w);
int   CX_Stitch_Shells  (void);

void  CX_Create_Vector_Normal(float[3], float[3]);
void CX_Read_Case_Info(const char *fileName);

float  *CX_Work_Array_Alloc(const char *where, const char *name, int n);
int     CX_Work_Array_Length(const char *where, const char *name);
int     CX_Work_Array_Type(const char *where, const char *name);
void    CX_Work_Array_Set_Type(const char *where, const char *name, int array_type);
float  *CX_Work_Array(const char *where, const char *name);
void    CX_Fill_Array(const char *func, float *val, int len);

int *CX_Active_Array_Alloc(const char *where, int n);
void CX_Fill_Active_Array(const char *func, int *val, int len);
int *CX_Active_Array(void);
int CX_Active_Array_Length(void);

double CX_Surface_Projected_Area(double [], double, List *);
void  CX_Surface_Normal (int, float[], float[], int);
int CX_Toggle_Shell_Mode(void);
int CX_Shell_Only_Mode(void);

/* Facet_X takes a pointer to the facelist that contains
 * the face descriptor. It sums-up the x co-ordinates
 * of the points in the face. Note that it is not possible
 * to determine the cell on which the face lies without an
 * additional pointer to the cell list of the same surface. */

FLUENT_EXPORT float CX_Facet_X (CX_Surface *, int);
FLUENT_EXPORT float CX_Facet_Y (CX_Surface *, int);
FLUENT_EXPORT float CX_Facet_Z (CX_Surface *, int);
FLUENT_EXPORT void CX_Surface_Normal_at_Facet(int index, int findex, float n[], int dim);

/* cxgrid.c */
void  CX_Start_Grid   (int, int, int);
void  CX_Open_Grid    (int, char *, char * );
void  CX_Add_Grid_Points  (int, int, float *);
void  CX_Add_Grid_Facets  (int, int, int *);
void  CX_End_Grid   (void);
void  CX_Open_Grid_Attr (int, char *, char *);
void  CX_Set_Grid_Attr  (int, char *);
void  CX_Set_Grid_Elements  (int, int *);
void  CX_Close_Grid   (void);
void  CX_Use_Grid_Points  (int);
void  CX_Display_Grid   (int);
void  CX_Delete_Grid    (int);
void  CX_Delete_All_Grids (void);
void  CX_Grid_Info    (int, int *, int *, int *);


/* cxg_export.c */
unsigned char *CX_PNG_Read(const char *filename, unsigned int *pWidth, unsigned int *pHeight);
unsigned char *CX_PPM_Read(char *filename, unsigned int *x, unsigned int *y);

/* cxpath_dpy.c */
void  CX_Reset_Pathlines  (void);
void  CX_Draw_Pathlines   (float, float, int);
void  CX_Loop_Pathlines (float, float, int);
void  CX_UnLoop_Pathlines (void);
void  CX_Insert_Pathline  (int *, float *, float *);
fixnum  CX_Get_N_Path   (void);
Pointer CX_Get_X_Axis_List  (void);
int CX_Plot_Pathline  (FILE *, int path, char *xaxis);
int     CX_Write_IBL            (FILE *fp);
int     CX_Write_FieldView_File (FILE *fp, char *name);
Pointer CX_Read_FieldView_File  (FILE *fp);
int     CX_Write_Ensight_Particle_File(char *, char *, char *, int);

/* uiXXXXX.c - User interface toolkit specific functions. */
CXBoolean ui_create   (int *, char *[]);
CXBoolean ui_create_minimal(int *argc, char **argv);
CXBoolean ui_init     (void);
void  ui_term     (void);
void  ui_busy     (int);
void  cx_busy     (int);
CXBoolean ui_check_events   (void);
void  ui_next_event   (cxboolean wait);
void  ui_delay    (long);

void  CX_Enable_Busy_Events (Widget, int);

#if ! CX_SINGLE
unsigned long ui_add_input  (int, void (*)(void *, int *, void *), long);
void  ui_del_input    (int, unsigned long);
#endif

void  ui_add_window_id  (long);
FLUENT_EXPORT void  CX_Stuff_Input    (char *);
void  CX_Set_Console_Wrap_Mode(const char *);
void  CX_Set_Console_Text_Pattern_Format(const char *pattern, const char *attr, const char *val);
FLUENT_EXPORT int CX_Query_Shift_Down (void);
FLUENT_EXPORT int CX_Query_Control_Down (void);//[Workaroun] [Hoops Wrapper]grahics event manager is not listening to control events
int CX_Query_Alt_Down (void);
int CX_Query_Left_Mouse_Button_Down(void);
int CX_Query_Any_Mouse_Button_Down(void);
void  CX_GUI_Layout(char *, int, int, int, int);
void  CX_Set_Layout(int);
void  CX_Get_Layout_Option(char *, char *);
void  CX_Set_Layout_Option(char *, char *);
void  CX_Save_GUI_Layout();
void  CX_Read_Graphics_Layout(char *);
void  CX_Show_Main_Window(cxboolean);
void  CX_Show_Main_Window_Init(cxboolean);
void  CX_Raise_Exit_Signal();
Widget  CX_Name_To_ID(char *);
void  CX_Register_Profile_Method (char *, char *, CX_Callback);
float getDevicePixelRatio();
void CX_Update_Console_Visibility(CXBoolean showConsole, CXBoolean showPanel);
void CX_Create_Message_Panel();
int CX_Get_Console_State();
void CX_Set_Console_State(int state);

/* Interpreter console IO functions implemented by the ui toolkit. */
typedef enum
{
  CX_Console_Message_Type_None = 0,
  CX_Console_Message_Type_Info,
  CX_Console_Message_Type_Warning,
  CX_Console_Message_Type_Error
} CX_Console_Message_Type;

/* ToDo : All these functions now demand a separate class for console text operations */
Pointer ui_get_sexp   (void);
int ui_putc     (int);
FLUENT_EXPORT int ui_puts(const char *);
FLUENT_EXPORT int ui_puts_err(const char *);
FLUENT_EXPORT int ui_puts_warn(const char *);
FLUENT_EXPORT CXBoolean ui_show_message(CX_Console_Message_Type type, const char *text);
/* Add a single message to the message buffer (i.e., don't display right now).
 * Could be extended for multiple messages if needed */
FLUENT_EXPORT void ui_buffer_message(CX_Console_Message_Type type, const char *text);

FLUENT_EXPORT CXBoolean ui_buffer_has_messages();

/* Flush the messages buffer (i.e. display buffered messages immediately if any.
 * Please note that this is not the same as ui_flush() etc. that just flushes messages already
 * output on the console. This one actually first displays the messages in a temporary queue, then flushes them */
FLUENT_EXPORT void ui_flush_messages_buffer();

FLUENT_EXPORT char *ui_gets();
FLUENT_EXPORT void ui_flush();
FLUENT_EXPORT void ui_flush_immediate();

#if WIN64
FLUENT_EXPORT LONG64  CX_Add_Timer    (int, CX_Callback);
FLUENT_EXPORT void  CX_Remove_Timer   (LONG64);
#else
FLUENT_EXPORT long  CX_Add_Timer    (int, CX_Callback);
FLUENT_EXPORT void  CX_Remove_Timer   (long);
#endif

void  CX_Set_Client_Information (char *, char *, char *, char *);
void  CX_Await_Client   (long);
void  CX_Sleep          (long);
Widget  CX_Add_Menu   (char *, int);
Widget  CX_Add_Script_Editor_Menu   (char *, int);
void  CX_Delete_Menu    (Widget);
void  CX_Clear_Menu(Widget);
Widget  CX_Add_Item(Widget, char *, int, String, CX_Callback);
Widget  CX_Add_HItem    (Widget, char *, int);
void    CX_Update_View_Menu(void);
void  CX_Set_Item_Position  (int);
Widget  CX_Get_Menu_Bar(void);
Widget  CX_Get_Menu (char *label);
void  CX_Set_Menu_Visiblity (char *label, CXBoolean visible);

void  CX_Error_Dialog   (char *, CX_Callback);
CXBoolean CX_Warning_Dialog (char *, CX_Callback);
void    CX_Set_Warning_Dialog_No_Cancel(void);/*Hide the cancel button in warning dialog*/
CXBoolean CX_Ok_Cancel_Dialog (char *, CX_Callback);
CXBoolean CX_Yes_No_Dialog  (char *, CX_Callback, CXBoolean);
CXBoolean CX_Prompt_Dialog  (char *, char *, int, CX_Callback);
FLUENT_EXPORT Widget  CX_Info_Dialog    (char *, CX_Callback, CXBoolean);
void CX_Set_Advance_Info_Dialog (int advance, char amsg[]);
Widget  CX_Working_Dialog (char *, CX_Callback, CX_Callback);
Widget  CX_Working_Dialog2  (char *, CX_Callback, CX_Callback);
CXBoolean CX_Select_Dialog  (char *, char *[], char *, char *,
                             int, CX_Callback);
#if !USING_MOTIF || _NT
Widget  CX_File_Dialog    (char *, char *, char *, char *, CXBoolean, CX_Callback, CX_Callback);
#else
Widget  CX_File_Dialog    (char *, char *, char *, CX_Callback, CX_Callback, CX_BOOLEAN);
#endif
void  CX_Set_File_Dialog_Remote (int);
void  CX_Set_File_Dialog_Multiple (int);
int     CX_Is_File_Dialog_Remote(void);
int     CX_Is_File_Dialog_Multiple(void);
Widget  CX_Set_File_Dialog_Append (int);
void  CX_Set_File_Dialog_Filter (int);
Widget  CX_Show_File_Dialog_Frame (void);
Widget CX_Get_File_Dialog(void);
Widget  CX_Table_Dialog   (char *, CX_Callback, CX_Callback);
FLUENT_EXPORT void  CX_Dialog_Done    (Widget);

void    CX_Pre_Append_App_Title (char *name);/*Pre-appends the fluent title in main window*/
Widget  _CX_Create_Panel    (char *, CX_Callback, char *);
Widget  _CX_Create_Preview_Panel(char *, CX_Callback, char *);
Widget  CX_Create_Hoops_Panel (char *, CX_Callback, char *);
void  CX_Set_Panel_Modal  (Widget);
void  CX_Show_Panel   (Widget);
void    CX_Show_ToolBar     (Widget, int);
int  CX_Wait_For_Panel (Widget);
void  CX_Hide_Panel   (Widget);
void  CX_Set_Parent_Panel (Widget);
void  CX_Delete_Item    (Widget);
void  CX_Enable_Item    (Widget, int);
void  CX_Activate_Item  (Widget);
void  CX_Hide_Dock_Widget   (char *, CXBoolean);
void  CX_Rename_Dock_Widget (char *, char *);
void  CX_Remove_Dock_Widget   (char *);
void  CX_Move_Dock_Widget (char *, char *);
void  CX_Move_Focus   (Widget);
void  CX_Set_Focus    (Widget, Widget);
Widget  CX_Show_Focus   (Widget);
void  CX_Show_Item    (Widget);
void  CX_Hide_Item    (Widget);
void  CX_Set_Position   (Widget, CX_Panel_Position *);
void  CX_Set_Redisplay  (int);


void  CX_Set_Label    (Widget, char *);
String CX_Show_Label   (Widget);
Widget  CX_Track_Pointer  (void);

Widget  CX_Add_Hoops_Draw_Area  (Widget, char *, CX_Panel_Position *, int, int, CX_Callback);
String CX_Show_Hoops_Draw_Area_Segment (Widget);
Widget  CX_Add_Frame    (Widget, char *, int,
                         CX_Panel_Position *);
void    CX_Add_Ribbon_Widget(Widget, Widget);
Widget  CX_Get_Ribbon_Widget(Widget, int);
void    CX_Update_Ribbon_Widget(Widget);
Widget CX_Create_Ribbon_Group (Widget parent, char *title, CX_Panel_Position *pos);
void   CX_Minimize_Ribbon_Group(Widget ribbon, CXBoolean minimize);
void   CX_Expand_Collapse_Ribbon_Area(void);
Widget  CX_Ribbon_Top_Area(void);
void    CX_Activate_Tab_Button    (Widget);
void    CX_Enable_Tab_Button    (Widget, CXBoolean);
void    CX_Hide_Tab_Button      (Widget, CXBoolean);
void    CX_Hide_Tabbar(Widget w, CXBoolean);
void    CX_Activate_Tab_Index(Widget, int);
Widget  CX_Get_Active_Tab(Widget);
Widget  CX_Add_Table    (Widget, CX_Panel_Position *);
void  CX_Set_Table_Default_Options (Widget, String[]);
void  CX_Set_Table_Child_Options (Widget, char *[]);
void CX_Remove_Widget_From_Table(Widget table, Widget widget);
Widget  CX_Add_Text   (Widget, char *, int,
                       CX_Panel_Position *);

Widget  CX_Add_Check_Button_Box (Widget, char *, CX_Panel_Position *);
Widget  CX_Add_Radio_Button_Box (Widget, char *, CX_Panel_Position *);
Widget  CX_Add_Horizontal_Radio_Button_Box  (Widget, char *, CX_Panel_Position *);
void  CX_Show_Toggle_Button_Box (Widget, const char *[]);
Widget  CX_Add_Toggle_Button  (Widget, char *, int, CX_Callback);
void  CX_Set_Toggle_Button  (Widget, int);
void  CX_Set_Toggle_Button2 (Widget, int);
CXBoolean CX_Show_Toggle_Button (Widget);
Widget  CX_Add_Check_Button (Widget, char *, int,
                             CX_Panel_Position *, CX_Callback);

Widget  CX_Add_Text_Entry (Widget, char *, char *, char *, int,
                           CX_Panel_Position *, CX_Callback);
void  CX_Set_Text_Entry (Widget, char *);
void  CX_Set_File_Dialog_Entries  (Widget, char **, char *);
String CX_Show_Text  (Widget);
String CX_Show_Text_Entry  (Widget);
void  CX_Set_Text_Entry_Echo  (Widget, int);
void  CX_Set_Text_Entry_Editable(Widget, CXBoolean);

void CX_Set_Spread_Sheet_Entry(Widget, int, int, char *);
void CX_Set_Spread_Sheet_RowHeader(Widget, int, char *);
void CX_Set_Spread_Sheet_ColumnHeader(Widget, int, char *);
const char *CX_Get_Spread_Sheet_Entry(Widget, int, int);

Widget  CX_Add_Symbol_Entry (Widget, char *, char *, char *, int,
                             CX_Panel_Position *, CX_Callback);
void  CX_Set_Symbol_Entry (Widget, char *);
String CX_Show_Symbol_Entry  (Widget);

Widget  CX_Add_Integer_Entry  (Widget, char *, char *, int64_t, int64_t, int64_t,
                               int, CX_Panel_Position *, CX_Callback);
void  CX_Set_Integer_Entry  (Widget, int64_t);
int64_t CX_Show_Integer_Entry (Widget);
void  CX_Set_Integer_Entry_Limits (Widget, int64_t, int64_t);
void  CX_Set_Integer_Entry_Increment (Widget, int64_t);

Widget  CX_Add_Real_Entry (Widget, char *, char *, double, double,
                           double, int, CX_Panel_Position *);
void  CX_Set_Real_Entry (Widget, double);
void  CX_Set_Real_Entry_List  (Widget, double *, int);
double  CX_Show_Real_Entry  (Widget);
void  CX_Show_Real_Entry_List (Widget, double *, int *);
void  CX_Set_Real_Entry_Limits (Widget, double, double);
void  CX_Set_Real_Entry_Units (Widget, double, double);
void  CX_Set_Real_Entry_Quantity (Widget, char *);
void  CX_Update_Real_Entry_Units (char *);
void  CX_Update_Expression_Toolbar(Widget);
void  CX_Update_Expression_Validation_Status(Widget);
void  CX_Remove_Toolbar_Item(Widget);
void  CX_Add_Widget_To_Toolbar(Widget, Widget);
void  CX_Hide_Widget_From_Toolbar(Widget, Widget);

Pointer CX_Show_Expression_Entry(Widget);
void CX_Set_Expression_Entry(Widget, String, ExpressionType);
void CX_Set_Expression_Entry_Items(Widget w, Pointer l, CXBoolean update);

Widget CX_Create_Expr_Plot(
  Widget parent,
  const char *title,
  const char *exprName,
  const char *exprStr);

Widget  CX_Add_List   (Widget, char *, CX_Panel_Position *,
                       int, char *[], int, int, CX_Callback);
Widget  CX_Add_Drop_Down_List (Widget, char *, char *,
                               CX_Panel_Position *, int,
                               char *[], int, int, CX_Callback);
void  CX_Set_List_Default_Button (Widget, Widget);
void  CX_Add_List_Items (Widget, char *[], int, char *typeItems[]);
void  CX_Delete_List_Items  (Widget, char *[], char *[]);
void  CX_Set_List_Items (Widget, char *[], char *[]);
CXBoolean CX_Is_Widget_DDList   (Widget);
void  CX_Set_List_Selectable  (Widget, int);
void  CX_Set_List_Selections  (Widget, char *[], int);
void  CX_Add_List_Selections  (Widget, char *[], int);
void  CX_Del_List_Selections  (Widget, char *[], int);
void  CX_Toggle_List_Selections (Widget, char *[], int);
void  CX_Show_List_Selections (Widget, char **[], int);
void  CX_Free_List_Selections (char *[]);
int CX_Has_List_Item  (Widget, String);
String CX_Get_Filter_Text(Widget);
void CX_Set_Filter_Text(Widget, String);
void CX_Enable_Wildcard_Widgets(Widget, CXBoolean);
CXBoolean CX_Is_Use_Wildcard_Selected(Widget);
void CX_Select_In_Wildcard_Dropdown(Widget, String);
void CX_Set_List_View(Widget, String);
Pointer CX_Get_Colormap(Widget);

Widget  CX_Add_Scale    (Widget, char *, CX_Panel_Position *,
                         int, int, int, int, CX_Callback);
void  CX_Set_Scale    (Widget, int);
int CX_Show_Scale   (Widget);
void  CX_Set_Scale_Max  (Widget, int);
void  CX_Set_Scale_Min  (Widget, int);

Widget  CX_Add_Dial   (Widget, char *, CX_Panel_Position *,
                       int, int, int, CX_Callback);
void  CX_Set_Dial   (Widget, int);
int CX_Show_Dial    (Widget);

void CX_Show_Message_Box(CXBoolean);
Widget CX_Set_TaskPage_Button_Label(Widget, char *, char *);

FLUENT_EXPORT void  CX_Append_Text_Edit (Widget, const char *);
void  CX_Set_Text_Edit(Widget, const char *);
char  *CX_Show_Text_Edit(Widget);

Widget   CX_Add_List_Tree                (Widget, char *, CX_Panel_Position *, CX_Callback);
Widget   CX_Add_Leaf_To_List_Tree        (Widget, Widget, char *, fixnum, CXBoolean);
Widget   CX_Add_Leaf_To_List_Tree_After        (Widget, Widget, char *, fixnum, Widget, const char *, const char *);
Widget   CX_Add_Node_To_List_Tree(Widget, Widget, char **, fixnum, Widget, CXBoolean, const char *, const char *);
void     CX_Set_List_Tree_Header(Widget, char **);
void     CX_Sort_List_Tree_Leaf          (Widget, Widget);
Widget   CX_Load_List_Tree_Bitmap        (Widget, char *);
Widget   CX_Show_List_Tree_Item_Parent   (Widget w, Widget item);
char   **CX_Show_List_Tree_Item_Child_Names (Widget w, Widget item);
Widget   CX_Add_Popup_To_List_Tree       (Widget, Pointer, CX_Callback, fixnum);
void     CX_Enable_List_Tree_Popups      (Widget, CXBoolean);
Widget   CX_Get_List_Tree_Item           (Widget tree, Widget parent, char *name);
char    *CX_Clear_List_Tree              (Widget);
char    *CX_Remove_Item_From_List_Tree   (Widget, Widget, CXBoolean);
char    *CX_Rename_Item_In_List_Tree     (Widget, Widget, char *, const char *, const char *);
char    *CX_Get_List_Tree_Item_Path      (Widget, Widget, char *, CXBoolean);
char    *CX_Get_List_Tree_Item_Data      (Widget, Widget, fixnum *);
char    *CX_Set_List_Tree_Item_Data      (Widget, Widget, fixnum);
CXBoolean CX_Get_List_Tree_Item_Toggled(Widget, Widget);
void  CX_Set_List_Tree_Item_Toggled(Widget, Widget, CXBoolean);
typedef enum
{
  LT_FONTSTYLE_DEFAULT,
  LT_FONTSTYLE_HEADING,
  LT_FONTSTYLE_HEADING2,
  LT_FONTSTYLE_GROUP,
  LT_FONTSTYLE_GROUP_CHILD,
  LT_FONTSTYLE_MAX
} ListTreeItemFontStyle;
typedef struct
{
  fixnum data;
  ListTreeItemFontStyle fontStyle;
} TreeItemInfo;
char    *CX_Set_List_Tree_Item_Font_Style (Widget, Widget, ListTreeItemFontStyle);
void     CX_Set_List_Tree_Item_Editable(Widget, Widget, CXBoolean);
void     CX_Set_List_Tree_Item_Status_Icons(Widget, Widget, const char **);
char   **CX_Show_List_Tree_Selections    (Widget, CXBoolean);
Widget  *CX_Show_List_Tree_Selected_Items(Widget);
void     CX_Free_List_Tree_Selections    (char **);
char    *CX_Set_List_Tree_Item_Selection (Widget, Widget, CXBoolean, CXBoolean);
void     CX_Set_List_Tree_Selections     (Widget, char **);
void     CX_Set_List_Tree_Item_Icon      (Widget, Widget, Widget);
void     CX_Expand_List_Tree_Item        (Widget, Widget, CXBoolean, CXBoolean);
CXBoolean CX_Get_List_Tree_Item_Expanded(Widget, Widget);
Widget   CX_Show_List_Tree_Item_By_Path  (Widget, Widget, char *);
void     CX_Set_List_Tree_Item_Suffix(Widget, Widget, const char *);
void   CX_Set_List_Tree_Default_Button (Widget, Widget);
void     CX_List_Tree_Right_Click(Widget);
CXBoolean     CX_List_Tree_Right_Mouse_Button_Pressed(Widget);
void     CX_Set_List_Tree_Node_Selectable(Widget, Widget, CXBoolean, CXBoolean);
void     CX_List_Tree_Enable_Node(Widget, Widget, CXBoolean);
void CX_List_Tree_Show_Child_Indicator(Widget, Widget, CXBoolean);


void  CX_Set_Scrollbar  (Widget, int, int);
int CX_Show_Scrollbar (Widget);
Widget  CX_Add_Scrollbar(Widget parent, int vert, int min, int max, int visib, CX_Panel_Position *pos, CX_Callback cb);

Widget  CX_Add_Panel_Button (Widget, char *, CX_Callback);
Widget  CX_Get_Panel_Button_ID  (Widget, char *);
Widget  CX_Set_Panel_Button_Label (Widget, char *, char *);
Widget  CX_Add_Button   (Widget, char *, CX_Panel_Position *,
                         CX_Callback);
void  CX_Set_Button_Icon  (Widget, char *);
Widget  CX_Add_Buttons    (Widget, char *[], CX_Panel_Position *,
                           int, CX_Callback);
Widget  CX_Get_Button_ID  (Widget, char *);
void  CX_Set_Buttons_Minor_Dim (Widget, int);
void  CX_Set_Buttons_Radio_Mode (Widget);

void  CX_Show_Help    (String);
int     CX_Use_HTML_Help        (void);
void    CX_Show_More_Documentation (void);
void    CX_Open_Url (char *);

//help Menu Items
void    CX_Help_Version(void);
void    CX_Help_Contents(void);
void    CX_Help_Index(void);
void    CX_Help_Using(void);
void    CX_Help_PDF(void);
void    CX_Help_License(void);
void    CX_Help_OTR(void);
void    CX_Help_Context(void);
Widget CX_Load_Bitmap(char *);

char *getConsoleText(void);

Pointer Make_Widget_Port(Widget w);

//Status Bar Items
Widget CX_Get_Status_Bar(void);
void CX_Set_Status_Bar_Message(char *);
void CX_Clear_Status_Bar_Message(void);
void CX_Hide_Status_Bar(void);
void CX_Show_Status_Bar(void);
void CX_Hide_Progress_Bar(void);
void CX_Show_Progress_Bar(void);
void CX_Copy_Selection (char **itemList, char **typeList);
void CX_Paste_Selection(void);
CXBoolean CX_Paste_Available(void);
void CX_Set_Selecting_Point_Flag(CXBoolean selectingFlag);
//script editor items
void CX_Add_TUIs_To_Script_Editor(Widget ide, Pointer tui_menu_strs);
void CX_Set_Script_Editor_Checkpoints(char **names, int count);
void CX_Restore_Script_Editor_To_Checkpoint(char *name);

void CX_Copy_Objects_To_Clipboard(Pointer p);
char *CX_Get_Mime_Type_From_Clipboard();
void CX_Import_Mime_Data_From_File(const char *, const char *, Widget);
void CX_Export_Mime_Data_To_File(const char *, Pointer, Widget);
char *CX_Get_Mime_Data_From_Clipboard();

void CX_Set_Property_Checkbox_State(Widget w, int v);

/* online help files and directories */
#define HELP_LOOKUP_FILE  "html/ug/lookup.htm"
#define HELP_HTML_FILE_PATH     "html/ug/"
#define HELP_INDEX_FILE   "index.htm"
#define HELP_MAIN_FILE    "main.tex"
#define HELP_NETSCAPE_EXEC_FILE "netscape.remote"
#define HELP_CONTENTS_TAG "helpcontents"
#define HELP_INDEX_TAG    "helpindex"
#define HELP_PDF_TAG        "PDFdownload"
/*#define HELP_GS_FILE             "flu_gs.pdf"
#define HELP_UG_FILE             "flu_ug.pdf"
#define HELP_TH_FILE             "flu_th.pdf"
#define HELP_FL_IN_WB_UG_FILE    "flu_wb.pdf"
#define HELP_TG_FILE             "flu_tg.pdf"
#define HELP_UDF_FILE            "flu_udf.pdf"
#define HELP_TCL_FILE            "flu_tcl.pdf"
#define HELP_FIB_FILE            "flu_fib.pdf"
#define HELP_FCM_FILE            "flu_fcm.pdf"
#define HELP_MHD_FILE            "flu_mhd.pdf"
#define HELP_PBM_FILE            "flu_pbm.pdf"
#define HELP_LSF_FILE            "flu_lsf.pdf"
#define HELP_PBS_FILE            "flu_pbs.pdf"
#define HELP_SGE_FILE            "flu_sge.pdf"
#define HELP_ASMM_FILE           "flu_adj.pdf"
#define HELP_BMM_FILE            "flu_bat.pdf"
#define HELP_MM_FILE             "flu_mig.pdf"
#define HELP_MUG_FILE            "tgd_usr.pdf"
#define HELP_MTG_FILE            "tgd_tut.pdf"
#define HELP_MTCL_FILE           "tgd_cmd.pdf"
#define HELP_SERVER_FILE         "aas_usr.pdf"*/
#define HELP_USING_TAG    "usinghelp"

/* lcx.c - Cortex scheme bindings. */
double  CX_Get_Float (const char *s);
#if WIN64
LONG64  CX_Get_Integer (const char *s);
#else
long  CX_Get_Integer (const char *s);
#endif
const char   *CX_Get_String (const char *s);
CXBoolean CX_Get_Boolean (const char *s);

int   CX_Get_List_Length (const char *s);
int CX_Get_List_Ref_Integer(const char *s, int n);
double  CX_Get_List_Ref_Float (const char *s, int n);
CXBoolean CX_Get_List_Ref_Boolean (const char *s, int n);
const char   *CX_Get_List_Ref_String  (const char *s, int n);
int CX_Get_Light (int, char **, int *, float *, float *);
int CX_Get_Periodic (float []);

FLUENT_EXPORT void CX_Set_Float (const char *s, double v);
FLUENT_EXPORT void CX_Set_Integer (const char *s, fixnum v);
FLUENT_EXPORT void CX_Set_Boolean (const char *s, CXBoolean v);
FLUENT_EXPORT void CX_Set_String (const char *s, const char *v);
#if GRAPHICS
void CX_Set_Graphics_Window_View_Widget(int view_id, int id, Widget p);
int  CX_Get_Saved_Graphics_Layout_Index(void);
void CX_Reposition_Windows();
#endif

#define CX_Get_Real(s)((real)CX_Get_Float(s))
#define CX_Set_Real(s,v)CX_Set_Float(s,(double)(v))

void  init_lcx    (void);
void  init_license(void); //for new binding method for license

/* lhoops.c - HOOPS scheme bindings. */
void  init_lhoops   (void);


#if LICENSE_MANAGER
/* license.c */
FLUENT_EXPORT int CX_Init_License             (char *);
int CX_Checkout_License         (void);
int CX_Checkout_N_Licenses      (int);
int CX_Checkout_N_Neutral_Licenses (int);
int CX_Check_Feature_Match  (char *, int);
int CX_Free_License             (void);
int CX_License_Feature_With_Holdtime(char *, int);
int CX_Release_Holdtime_Licenses(void);
int CX_Print_License_Usage     (char *);
int CX_Print_License_Usage_Testing(void);
char *CX_Get_License_Server_Path(void);
int CX_Free_All_Licenses        (void);
int CX_Free_All_Licenses_Only   (void);
int CX_License_Switch_Mode      (char *);
int CX_License_Switch_Keep_Solver(int enable);
CXBoolean CX_License_Mode_Switch_Skip();
int CX_Check_Feature_Valid      (char *);
FLUENT_EXPORT int CX_Is_EducationalOnly       (void);
int CX_Is_EducationalOnlyLogo   (void);
int CX_Is_StudentOnly           (void);
int CX_Is_PostOnly              (void);
int CX_Is_Meshing               (void);
/* export CX_License_Feature for use in 3rd party UDFs */
FLUENT_EXPORT int CX_License_Feature             (char *);
int CX_Free_Feature   (char *);
FLUENT_EXPORT int CX_Check_License_Connection (void);
FLUENT_EXPORT int CX_Get_License_Timeout      (void);
FLUENT_EXPORT int CX_Get_Interrupt_Count(void);
int CX_ANSYS_Avail(void);/*Remote usages from solver*/
int CX_Check_License_Availability(char *base_feature, int check_parallel, int count);
int License_Initialized(void);
char *CX_License_Level_Name(void);
int CX_Get_License_Level(void);
char *CX_Get_License_Hashkey(char *, int n_proc);

/* Client apps license sharing */
int CX_Enable_License_Sharing(char *appName, char *licenseCSV);
void CX_End_License_Sharing();
void CX_License_Sharing_Push();
void CX_License_Sharing_Pop();

/*ACLE related functions*/
int CX_Has_ACLE(void);
int CX_Checkout_ACLE(void);
int CX_Checkin_ACLE(void);
const char *CX_Get_License_Name(void);
void CX_Get_License_Key(unsigned int cm, char *string);
char *CX_Get_EM_Hashkey(void);
int mask_signal_interrupt(int on);

#endif

/* Cortex global variables. */
extern char cxPname[], cxHost[];  /* Process name and host */
extern char *cxAppNames[20];
extern CXBoolean        cxClientOrCortexDebug;                 /* is TRUE when client or cortex in debug mode*/
FLUENT_EXPORT extern CXBoolean  cxNoGUI;    /* No gui mode */
extern CXBoolean  cxGUIHidden;    /* Gui mode, but hidden (NT only) */
FLUENT_EXPORT extern CXBoolean  cxNoGr;     /* No graphics mode */
extern CXBoolean  cxStudentOnly;   /* No iterations mode */
extern CXBoolean  cxPostOnly;   /* No iterations mode */
extern CXBoolean  cxEducationalOnly;  /* Educational mode */
extern CXBoolean  cxEducationalOnlyLogo;    /* Educational mode logo*/
FLUENT_EXPORT extern void CX_Set_Educational_Only_Logo(CXBoolean eduOnlyLogo);    /* Set educational mode logo*/
FLUENT_EXPORT void CX_Build_Server_Info_Path(char *path);
extern CXBoolean  cxStdErr;   /* Write cx messages to std error */
extern CXBoolean cxGui2; /*if running with 2nd generaton cortex-GUI*/
extern CXBoolean cxInWB; /* Is FLUENT running under WorkBench */
FLUENT_EXPORT extern CXBoolean cxInFLREMOTE;
extern CXBoolean cxInAAS;
extern CXBoolean cxACTEnable; /* Is ACT enabled? */
extern char *cxGuiComponentNames[];
extern CXBoolean cxAutoDisplayMesh; /* Indicates whether to display mesh after reading case */
extern Graphics_Color_Scheme cxGraphicsColorScheme;
extern CXBoolean cxEmbeddedGraphicsWindows; /*This is to enable floating graphics windows in  new GUI (cxGui2) */
extern CXBoolean cxServerInitialized ;/*CX_Server_Init has been called*/
extern char feature_parallel_preferred[];
extern const char *cxAppName;
extern char *fontList;

/* in cxgraph.cpp */
extern char cxGrVersionString[];  /* Version of graphics library. */
/* in cxserv.c */
extern int  cxGraphicsWindowCount;  /* Number of currently open graphics windows */
extern int  cxScreenHeight;/*in pixel*/
extern CXBoolean cxR16Layout;

extern CXBoolean  cxInterrupted;    /* True if Ctrl-C has been noticed */
extern CXBoolean  cxInterruptedByUser;  /* similar to above but flag will be available to scheme side and will be reset only in check_update for pending callbacks */
FLUENT_EXPORT extern CXBoolean  cxIsBusy;   /* True if waiting for a response */
FLUENT_EXPORT extern CXBoolean cxProcessEventsWhileWaiting; /*True by default, if false then events are processed in background.*/
FLUENT_EXPORT extern CXBoolean  cxInStartup;    /* True if in startup */
extern CXBoolean  cxUseHostAddr;    /* Use host addr rather than host name */
extern CXBoolean        cxInWB;                /* True if  FLUENT is running under WorkBench */
extern int        cxUILocked;   /* true if UI is locked (from WB) */
extern CXBoolean  cxGuiLogSuspended;/*if true, don't send gui logs to WB during journal replay(TUI logs already don't go).*/
extern int cxCmdPort;     /* Port to use for command stream socket */
extern int cxRPCPort;     /* Port to use for RPC stream socket */

extern void cx_svc_process(int fd);
extern void cx_svc_init(int rpc_rendezvous);
extern void cx_svc_connect(int rpcfd);

extern Pointer user_init_env;

extern CXBoolean cxMinimize;    /* Run minimized/hiiden on NT? */
extern CXBoolean cxShowSplash;    /* Show splash */

extern Pointer  sym_uienv;    /* Stored seem user env */

extern CXBoolean minimalUICreated;

#ifndef FLGUI
/* cxserv.c */
extern CXBoolean  cxGraphicsNeedUpdate; /* Flag to trigger call to Update_Display */
/* cxgcolor.c */
extern int  cxNColorLevels;   /* Number of entries in the current colormap */
extern float  cxColorValue[];   /* Values of current colormap */
extern CXBoolean  cxColorsInitialized;  /* (Unreliable) indicator of color keys */
/* cxvis.c */
extern CX_Surface *cxSurfaceList;  /* Cortex surfaces */
extern int maxCortexSurfaceId;      /* Sync'd with maxSurfaceId in cxiface.h */
#endif
extern CXBoolean CX_Ready_For_Ext_Input;
extern CXBoolean default_mesher_mode;

extern CXBoolean use_socket_notifier;

typedef float Color[3];
void Color_Filter(const char *options, Color *cmap, int ncolors);
int Hardcopy_Write_Driver(char *segment, char *text, float *xfrac_hcp, float *yfrac_hcp);

/* cxgevent.cpp */
extern int hoops_timeout;
void enable_snap_to_axis(CXBoolean flag);
CXBoolean show_snap_to_axis(void);
void CX_Resize_Screen(void);
void MS_Mouse_Roll_Zoom(void);
FLUENT_EXPORT void CX_Flush_All_Events(void);
FLUENT_EXPORT CXBoolean CX_Check_For_Events(void);
void CX_Await_Event(char *eventCategory);
void CX_Show_Selection_Source(char *locater, char *picture, char *action, int *status);

void CX_Set_Screen_Geometry(int, int);
int CX_Get_Screen_Width();
int CX_Get_Screen_Height();
int CX_Get_HScale(int);
int CX_Get_VScale(int);
int CX_Get_VHScale(int);

CXBoolean isLightTheme(void);
FLUENT_EXPORT CXBoolean isDarkTheme(void);
CXBoolean isClassicTheme(void);
CXBoolean isClassicLightTheme(void);
CXBoolean isClassicLightSCTheme(void);

const char *CX_Get_Light_Color_Stylesheet(char *);
const char *CX_Get_Dark_Color_Stylesheet(char *);

FLUENT_EXPORT void CX_Send_String_List(char **s, int);
FLUENT_EXPORT void CX_Register_For_String_List(void(*) (char **, int));


/*****************************************************************************
  New Cortex API bindings
******************************************************************************/
#define CxAabove                "above"
#define CxAactivateCallback     "activate-callback"
#define CxAgetPopupMenuFn       "popup-menu-fn"
#define CxAloseFocusActivate    "lose-focus-activate"
#define CxAallMethods           "all-methods"
#define CxAapplyCallback        "apply-callback"
#define CxAapplyClose           "apply-close"
#define CxAautoHide             "auto-hide"
#define CxAbelow                "below"
#define CxAblockWhenBusy        "block-when-busy"
#define CxAqueueWhenBusy        "queue-when-busy"
#define CxAnchild               "nchild"
#define CxAblockWhenModal       "block-when-modal"
#define CxAborder               "border"
#define CxAborderWithoutLabel   "border-without-label"
#define CxAwhitebkg             "white-background"
#define CxAcacheRowChanges      "cache-row-changes"
#define CxAenableContextMenu    "enable-context-menu"
#define CxAcloseCallback        "close-callback"
#define CxAcompressed           "compressed"
#define CxAcolumn               "col"
#define CxAcolumnSpan           "col-span"
#define CxAcurrentButton        "current-button"
#define CxAcurrentMethod        "current-method"
#define CxAcurrentProfile       "current-profile"
#define CxAdefaultButton        "default-button"
#define CxAdefaultValue         "default-value"
#define CxAdefaultText          "default-text"
#define CxAdrawCallback         "draw-callback"
#define CxAinsertRowAboveCallback    "insert-row-above-callback"
#define CxAinsertRowBelowCallback    "insert-row-below-callback"
#define CxAdeleteRowCallback    "delete-row-callback"
#define CxAdropCallback         "drop-callback"
#define CxAfilterlabel          "filterlabel"
#define CxAeditable             "editable"
#define CxAeditCallback         "edit-callback"
#define CxAenabled              "enabled"
#define CxAfilterCategory       "filter-category"
#define CxAfocusGainedCallback  "focus-gained-callback"
#define CxAfocusLostCallback    "focus-lost-callback"
#define CxAfunctionOf           "function-of"
#define CxAgraphicsToolBar      "graphics-toolbar"
#define CxAheight               "height"
#define CxAminHeight            "min-height"
#define CxAhelpString           "help-string"
#define CxAhideVerticalHeader   "hide-vertical-header"
#define CxAhoopsPanel           "hoops-panel"
#define CxAhoopsSegment         "hoops-segment"
#define CxAiconButton           "icon-button"
#define CxAincrement            "increment"
#define CxAinitialPosition      "initial-position"
#define CxAjournable            "journable"
#define CxAlabel                "label"
#define CxAhelptag              "help-tag"
#define CxAlabelPosition        "label-position"
#define CxAisPrimary            "primary-button"
#define CxAphText               "ph-text"
#define CxAadvancedOption       "advanced-option"
#define CxAleftOf               "left-of"
#define CxAlength               "length"
#define CxAlocations            "locations"
#define CxAlowerCase            "lower-case"
#define CxAsingleClickEdit      "single-click-edit"
#define CxAmargin               "margin"
#define CxAmarked               "marked"
#define CxAcolor                "color"
#define CxAmaximum              "maximum"
#define CxAmaxHeight            "max-height"
#define CxAmethods              "methods"
#define CxAmethodCallback       "method-callback"
#define CxAmessage              "message"
#define CxAminimum              "minimum"
#define CxAminorDimension       "minor-dimension"
#define CxAmixedCase            "mixed-case"
#define CxAmodal                "modal"
#define CxAmultipleSelections   "multiple-selections"
#define CxAshowListSelIcons     "show-list-selections-icons"
#define CxAsingleDeselection    "single-deselection" /*For single-selection list to have deselect button*/
#define CxAinvertSelections     "invert-selections"
#define CxAlistShowHideControl  "list-show-hide-control"
#define CxAshowSelectedCount    "show-selected-count"
#define CxAnumberOfColors       "number-of-colors"
#define CxAonEditActivate       "on-edit-activate"
#define CxApanel                "panel"
#define CxAtaskpage             "taskpage"
#define CxAdock                 "dock"
#define CxApanelButton          "panel-button"
#define CxApanelButtons         "panel-buttons"
#define CxApairedWidget         "paired-widget"
#define CxAparametricTree       "parametric-tree"
#define CxApasswordMode         "password-mode"
#define CxApattern              "pattern"
#define CxAprofileInfo          "profile-info"
#define CxAprofiles             "profiles"
#define CxAradioMode            "radio-mode"
#define CxArealEntry            "real-entry"
#define CxAredisplay            "redisplay"
#define CxAremote               "remote"
#define CxAqueueCallbacks       "queue-callbacks"
#define CxArightClickCallback   "right-click-callback"
#define CxArightOf              "right-of"
#define CxArow                  "row"
#define CxArowSpan              "row-span"
#define CxAscrollWith           "scroll-with"
#define CxAselectable           "selectable"
#define CxAselectionAction      "selection-action"
#define CxAselectionCallback    "selection-callback"
#define CxAselectionStatus      "selection-status"
#define CxAselectionX           "selection-x"
#define CxAselectionY           "selection-y"
#define CxAshowButtons          "show-buttons"
#define CxAshowCallback         "show-callback"
#define CxAshowValue            "show-value"
#define CxAsliderSize           "slider-size"
#define CxAsorted               "sorted"
#define CxAspacing              "spacing"
#define CxAsimReportDrag        "sim-report-drag"
#define CxAstate                "state"
#define CxAstretchColumn        "stretch-column"
#define CxAsymbolMode           "symbol-mode"
#define CxAexprNameMode         "expr-name-mode"
#define CxAerrorMessage         "error-message"
#define CxAclearButton          "clear-button"
#define CxAtabbed               "tabbed"
#define CxAribbon               "ribbon"
#define CxAsplitter             "splitter"
#define CxAsplitterStretchItem  "splitter-stretch-item"
#define CxAtableOptions         "table-options"
#define CxAtableSizeHintHeight  "table-size-hint-height"
#define CxAtemplateIcons        "template-icons"
#define CxAtoggleButtons        "toggle-buttons"
#define CxAtoggleMode           "toggle-mode"
#define CxAtoggleState          "toggle-state"
#define CxAtreeView             "tree-view"
#define CxAudfType              "udf-type"
#define CxAupdateCallback       "update-callback"
#define CxAunitsFactor          "units-factor"
#define CxAunitsOffset          "units-offset"
#define CxAunitsQuantity        "units-quantity"
#define CxAdisplayUnit          "display-unit"
#define CxAuserData             "user-data"
#define CxAvalue                "value"
#define CxAvalueAsInt           "value"
#define CxAvalueAsReal          "value"
#define CxAvertical             "vertical"
#define CxAvisible              "visible"
#define CxAvisibleLines         "visible-lines"
#define CxAvisibleRows          "visible-rows"
#define CxAwidth                "width"
#define CxAx                    "x"
#define CxAy                    "y"
#define CxAindent               "indent"
#define CxAmenuButton           "menubutton"
#define CxAtoolTip              "tooltip"
#define CxAtoolTipOnDisable     "tooltip-on-disable"
#define CxAdropDownList         "drop-down-list"
#define CxAgraphicsArea         "graphics-area"
#define CxAseparator            "separator"
#define CxAmnemonic             "mnemonic"
#define CxAaccelerator          "accelerator"
#define CxArowsize              "rowsize"
#define CxAcolumnsize           "columnsize"
#define CxArenameCallback       "rename-callback"
#define CxAmouseEnterCallback   "mouse-enter-callback"
#define CxAmouseEnterDelay      "mouse-enter-delay"
#define CxAbold                 "bold-text"
#define CxAwordWrap             "word-wrap"
#define CxAlocalize             "localize"
#define CxAuppercase            "uppercase-text"
#define CxAdefaultPos           "default-pos"    //for dock-widget
#define CxAdockableAreas        "dockable-areas" //for dock-widget
#define CxAfloating             "floating"       //for dock widget
#define CxAfixed                "fixed"          //for dock widget
#define CxAclosable             "closable"       //for dock widget
#define CxAsplitVertical        "split-vertical" //for dock widget
#define CxAposIndex             "pos-index"      //for status Bar widgets only
#define CxAuniqueItems          "unique-items"  /*property for CxList to avoid duplicates*/
#define CxAsearchable           "searchable" //for combolist
#define CxAdraggable            "draggable"  //navigation tree
#define CxAiconSize             "icon-size"  //navigation tree
#define CxAfilterWidth          "filter-width"
#define CxAfield                "field"
#define CxAfilled               "filled"
#define CxAcontourLines         "contour-lines?"
#define CxAoffset               "offset"
#define CxAinRange              "in-range"
#define CxAautoRange            "auto-range"
#define CxAglobalRange          "global-range"
#define CxAnodeValues           "node-values"
#define CxAboundaryValues       "boundary-values"
#define CxAbanded               "banded"
#define CxAcmOffset             "colormap-offset"
#define CxAcmFactor             "colormap-factor"
#define CxAcmColor              "colormap-color"
#define CxAcmVisible            "colormap-visibility?"
#define CxAcmSize               "colormap-size"
#define CxAcmLog                "colormap-log-scale?"
#define CxAcmFormat             "colormap-format"
#define CxAcmUserSkip           "colormap-user-skip"
#define CxAcmShowAll            "colormap-show-all"
#define CxAcmPosition           "colormap-position"
#define CxAcmFontName           "colormap-font-name"
#define CxAcmFontAutomatic      "colormap-font-automatic"
#define CxAcmFontSize           "colormap-font-size"
#define CxAcmLength             "colormap-length"
#define CxAcmWidth              "colormap-width"
#define CxAcmChangeSceneLayout  "colormap-change-layout?"
#define CxAcolormap             "colormap"
#define CxAsurfacesList         "surfaces-list"
#define CxAdefaultTreeView      "default-tree-view"
#define CxAmultiEditBC          "multi-edit-bc"
#define CxAlistSelType          "list-sel-type"
#define CxAresizable            "resizable"
#define CxAhideShowStretch      "hide-show-stretch"
#define CxAmodal                "modal"
#define CxAautoScale            "auto-scale?"
#define CxAheadScale            "head-scale"
#define CxAfixedLength          "fixed-length?"
#define CxAxComponent           "x-component?"
#define CxAyComponent           "y-component?"
#define CxAzComponent           "z-component?"
#define CxAwrapMode             "wrap-mode"
#define CxAscale                "vector/scale"
#define CxAvectorColor          "vector/color"
#define CxAvectorStyle          "vector/style"
#define CxAvectorName           "vector-name"
#define CxAvectorInplane        "vector/in-plane?"
#define CxAvectorSkip           "vector/skip"
#define CxAcomponentList        "vector/components"
#define CxAhelpvisible          "help-visible?"
#define CxAunits                "units"
#define CxAaddSpacerAtTheEnd    "add-spacer-at-the-end"
#define CxAmarkParentModified   "mark-parent-modified"
#define CxAtemporary            "temporary"
#define CxAwildcardCallback     "wildcard-callback"
#define CxAparametricStudyCallback "parametric-study-callback"
#define CxAshowSpacer           "show-spacer"
#define CxAshowHVScrollBars     "show-horz-vert-scroll-bars"
#define CxArmbSelect            "rmb-select"
#define CxAhorzHeaderWordWrap   "horz-header-word-wrap"
#define CxAhorzCellPadding      "horz-cell-padding"

// mesh objects
#define CxAshrinkFactor         "shrink-factor"
#define CxAnodes                "nodes?"
#define CxAedges                "edges?"
#define CxAfaces                "faces?"
#define CxApartitions           "partitions?"
#define CxAoverset              "overset?"
#define CxAedgesAll             "edge-all?"
#define CxAedgesOutline         "edge-outline?"
#define CxAedgesFeature         "edge-feature?"
#define CxAfeatureAngle         "feature-angle"
#define CxAautomatic            "automatic?"
#define CxAcolorFacesBy         "color-faces-by"
#define CxAcolorMaterialFacesBy "color-material-face-by"
#define CxAcolorEdgesBy         "color-edges-by"
#define CxAcolorNodesBy         "color-nodes-by"
#define CxAcolorBy              "color-by"

//materials
#define CxAdiffuseColor                "diffuse-color"
#define CxAdiffuseTexturePath          "diffuse-texture-path"
#define CxAdiffuseTexture              "diffuse-texture"
#define CxAspecularColor               "specular-color"
#define CxAspecularTexturePath         "specular-texture-path"
#define CxAspecularTexture             "specular-texture"
#define CxAmirrorValue                 "mirror-value"
#define CxAemissionColor               "emission-color"
#define CxAbumpTexturePath             "bump-texture-path"
#define CxAbumpTexture                 "bump-texture"
#define CxAenvironmentTexturePath      "environment-texture-path"
#define CxAenvironmentTexture          "environment-texture"
#define CxAmatTransparency             "transparency"
#define CxAmatScale                    "mat-scale"
#define CxAmatRotation                 "mat-rotation"
#define CxAgloss                       "mat-gloss"

//pathlines and particle-track attributes
#define CxAplot                  "plot?"
#define CxAresolution           "resolution"
#define CxArecalculate          "recalculate"
#define CxAreverse              "reverse"
#define CxAmaxSteps             "max-steps"
#define CxAtimestep             "timestep"
#define CxApulse                "pulse"
#define CxAoilflow              "oil-flow"
#define CxAoilflowZone          "oil-flow-zone"
#define CxAoilflowZonesName     "oil-flow-zone-name"
#define CxAtrackSkip            "track-skip"
#define CxAerrorControl         "error-control?"
#define CxAmaxError             "max-error"
#define CxAdisplaySteps         "display-steps"
#define CxAvelocityDomain       "velocity-domain"
#define CxAisSavePulseAnimation   "save-pluse-animation"
#define CxAsavePulseFilePath    "pulse-save-file-path"
#define CxAisSavePulseFileFormatVideo     "pulse-save-format-video"
#define CxAisTiSavePulseAnimation         "ti-save-pluse-animation"

#define CxAinjectionsList       "injections-list"
#define CxAfieldsList           "fields-list"
#define CxAvectorOf             "vector-of"
#define CxAtrackStream          "track-stream"
#define CxAfreeStreamParticles  "free-stream-particles"
#define CxAwallFilmParticles    "wall-film-particles"
#define CxAtrackPdfParticles    "track-pdf-particles"

#define CxAfilterEnabled        "filter-enabled"
#define CxAfilterField          "filter-field"
#define CxAfilterRangeMinimum   "filter-range-minimum"
#define CxAfilterRangeMaximum   "filter-range-maximum"
#define CxAfilterInside         "filter-inside"

//style attributes
#define CxAlineWidth           "line-width"
#define CxAarrowSpace          "arrow-space"
#define CxAarrowScale          "arrow-scale"
#define CxAmarkerSize          "marker-size"
#define CxAsphereSize          "sphere-size"
#define CxAsphereLod           "sphere-lod"
#define CxAtrackRadius         "sphere-radius"
#define CxAribbonScaleFactor   "ribbon-scalefactor"
#define CxAribbonField         "ribbon-field"
#define CxAtwistMinimum        "twist-min"
#define CxAtwistMaximum        "twist-max"
#define CxAisPathline          "is-pathline"
#define CxAsphereAuto          "sphere-auto?"
#define CxAsphereSizeConst     "sphere-constant?"
#define CxAsphereScale         "sphere-scale"
#define CxAsphereMin           "sphere-min"
#define CxAsphereMax           "sphere-max"
#define CxAvectorLength        "vector-length"
#define CxAvectorScale         "vector-scale"
#define CxAvectorCylRatio      "vector-cyl-ratio"
#define CxAcheckable           "checkable"
#define CxAtvarName            "tvar-name"
#define CxAtrackable           "trackable"
#define CxAdiffValueProperty   "diff-value-property"
#define CxAapplyProperty       "apply-property"
#define CxAapplyEnabled        "apply-enabled"
#define CxAtransparent         "transparent"
#define CxAdataService         "data-service"
#define CxAexprSel             "expr-sel"
#define CxAexprPopupCB         "expr-popup-cb"
#define CxAexprStr             "expr-str"
#define CxAinfoProvider        "info-provider"
#define CxAinfoProviderCtxt    "info-provider-ctxt"
#define CxAxAxisLabel          "x-axis-label"
#define CxAyAxisLabel          "y-axis-label"
#define CxAvalidExprType       "valid-expr-type"
#define CxAvalid               "valid"
#define CxAsingleValueExpr     "single-value-expr"
#define CxAfullContextRequired "full-context"
#define CxAphase               "phase"
#define CxAparamValueExpr      "param-value-expr"
#define CxAselectionCB         "selection-cb"
#define CxAprogressBarVal      "progress-bar-val"
#define CxAprogressBarStepSize "progress-bar-step-size"
#define CxAprogressBarMessage  "progress-bar-message"
#define CxApanelPosition       "panel-position"
#define CxAmovable             "movable?"

// lic attributes
#define CxAorientedLic         "lic-oriented?"
#define CxApixelInterp         "lic-pixel-interpolation?"
#define CxAlicNormalize        "lic-normalize?"
#define CxAlicMaxSteps         "lic-max-steps"
#define CxAtextureSize         "texture-size"
#define CxAtextureSpacing      "texture-spacing"
#define CxAintensityFactor     "lic-intensity-factor"
#define CxAimageFilter         "lic-image-filter"

#define CxAlicColorByField     "lic-color-by-field?"
#define CxAlicColor            "lic-color"
#define CxAgrayScale           "gray-scale?"
#define CxAintensityAlpha      "lic-intensity-alpha?"
#define CxAfastLic             "lic-fast?"
#define CxAimageToDisplay      "image-to-display"
/*
#define CxAlicTransparency     "lic-transparency?"
#define CxAlicBgAlpha          "lic-bg-alpha"
*/

#define ATTRIB_VAL(v)   (*(CX_Attrib_Val*)&v)

#define CX_INIT   1
#define CX_SET    2
#define CX_GET    3
#define CX_REALIZE  4
#define CX_PRESET 5

#define CX_STRING_LIST_MAX 50

#define CX_ATTRIB_BOOLEAN 0
#define CX_ATTRIB_INT   1
#define CX_ATTRIB_REAL    2
#define CX_ATTRIB_STRING  3
#define CX_ATTRIB_STRING_LIST 4
#define CX_ATTRIB_SYMBOL  5
#define CX_ATTRIB_SYMBOL_LIST 6
#define CX_ATTRIB_CALLBACK  7
#define CX_ATTRIB_POINTER 8
#define CX_ATTRIB_UNKNOWN -1
#define CX_ATTRIB_ERROR   -2

#define CX_ATTRIB_PAIR(name, type, value) name, type, value
#define CX_ATTRIB_PINT(name, value) CX_ATTRIB_PAIR(name, CX_INT, value)
#define CX_ATTRIB_PREAL(name, value) CX_ATTRIB_PAIR(name, CX_REAL, value)
#define CX_ATTRIB_PBOOL(name, value) CX_ATTRIB_PAIR(name, CX_BOOLEAN, value)
#define CX_ATTRIB_PSTR(name, value) CX_ATTRIB_PAIR(name, CX_STR, value)
#define CX_ATTRIB_PPROC(name, value) CX_ATTRIB_PAIR(name, CX_CALLBACK, value)
#define CX_ATTRIB_PPTR(name, value) CX_ATTRIB_PAIR(name, CX_WIDGET, value)
#define CX_ATTRIB_END NULL

typedef const char *String_List[CX_STRING_LIST_MAX];
typedef const char *Symbol;
typedef String_List Symbol_List;

typedef union
{
  CX_POINTER_SIZED_INT      b;
  CX_Callback cb;
  double    f;
  CX_POINTER_SIZED_INT      i;
  Pointer p;
  const char   *s;
  const char  **sl;
} CX_Attrib_Val;

#if CRAY
typedef long CX_Attrib_Ptr;
#else
typedef Pointer CX_Attrib_Ptr;
#endif

typedef struct
{
  char   *name;
  CX_Attrib_Val val;
  int   type;
} CX_Attrib;

typedef enum
{
  CX_UNKNOWN = -1,
  CX_INT = 0,
  CX_REAL,
  CX_STR,
  CX_BOOLEAN,
  CX_CALLBACK,
  CX_WIDGET,
  CX_MAX
} AttValType;

CX_Attrib  *CX_Attrib_List    (char *, ...);
void    CX_Show_Attributes  (Widget, ...);
void    CX_Set_Attributes (Widget, ...);
void    CX_Set_Attribute_List (Widget, CX_Attrib *);
void    CX_Show_Attribute_List  (Widget, CX_Attrib *);

/* Attribute functions */
CX_Attrib *ATTRIBS_ARG(Pointer a, char *m);
CXBoolean cx_attrib_CXBoolean (int, CX_Attrib *, CXBoolean *);
CXBoolean cx_attrib_CX_Callback (int, CX_Attrib *, CX_Callback *);
CXBoolean cx_attrib_float   (int, CX_Attrib *, float *);
CXBoolean cx_attrib_double    (int, CX_Attrib *, double *);
CXBoolean cx_attrib_int   (int, CX_Attrib *, int *);
CXBoolean cx_attrib_int64_t   (int, CX_Attrib *, int64_t *);
CXBoolean cx_attrib_long    (int, CX_Attrib *, CX_POINTER_SIZED_INT *);
CXBoolean cx_attrib_String  (int, CX_Attrib *, String *);
CXBoolean cx_attrib_String_List (int, CX_Attrib *, String *);
CXBoolean cx_attrib_Symbol  (int, CX_Attrib *, Symbol *);
CXBoolean cx_attrib_Symbol_List (int, CX_Attrib *, Symbol *);
CXBoolean cx_attrib_Widget  (int, CX_Attrib *, Widget *);
CXBoolean cx_attrib_Pointer (int, CX_Attrib *, Pointer *);

CX_Attrib_Ptr cx_attrib_val_float (float);

#define CX_Set_Int_Attribute(w, a, v) CX_Set_Attributes(w, a, CX_ATTRIB_INT, v, NULL)
#define CX_Set_Real_Attribute(w, a, v) CX_Set_Attributes(w, a, CX_ATTRIB_REAL, v, NULL)
#define CX_Set_Bool_Attribute(w, a, v) CX_Set_Attributes(w, a, CX_ATTRIB_BOOLEAN, v, NULL)
#define CX_Set_String_Attribute(w, a, v) CX_Set_Attributes(w, a, CX_ATTRIB_STRING, v, NULL)
#define CX_Set_Callback_Attribute(w, a, v) CX_Set_Attributes(w, a, CX_ATTRIB_CALLBACK, v, NULL)
#define CX_Set_Widget_Attribute(w, a, v) CX_Set_Attributes(w, a, CX_ATTRIB_POINTER, v, NULL)

#define CX_Show_Attribute(w, a, v) CX_Show_Attributes(w, a, v, NULL)

void    CX_Show_Splash(CXBoolean);
void    CX_Splash_Message(char *);
Widget  CX_Create_Panel   (char *, CX_Attrib *);
Widget  CX_Create_Preview_Panel(char *, CX_Attrib *);
Widget  CX_Create_Panel_Item  (char *, Widget, char *, CX_Attrib *);
Widget  CX_Create_Draw_Area (Widget, char *, CX_Attrib *);
Widget  CX_Create_Frame   (Widget, char *, CX_Attrib *);
Widget  CX_Create_Table   (Widget, char *, CX_Attrib *);
#if !_NT
Widget CX_Create_Table_Without_Frame(Widget parent, CX_Attrib *attribs);
#endif
Widget  CX_Create_Line          (Widget, char *, CX_Attrib *);
Widget  CX_Create_Button_Box  (Widget, char *, CX_Attrib *);
Widget  CX_Create_Text    (Widget, char *, CX_Attrib *);
Widget  CX_Create_Button  (Widget, char *, CX_Attrib *);
Widget  CX_Create_Icon_Button (Widget, char *, char *, CX_Attrib *);
Widget  CX_Create_Icon_Button (Widget, char *, char *, CX_Attrib *);
Widget  CX_Create_Toggle_Button (Widget, char *, CX_Attrib *);
Widget  CX_Create_Spread_Sheet (Widget, char *, CX_Attrib *);
Widget  CX_Create_Text_Entry  (Widget, char *, CX_Attrib *);
Widget  CX_Create_Integer_Entry (Widget, char *, CX_Attrib *);
Widget  CX_Create_Real_Entry  (Widget, char *, CX_Attrib *);
Widget  CX_Create_List    (Widget, char *, CX_Attrib *);
Widget  CX_Create_Drop_Down_List (Widget, char *, CX_Attrib *);
Widget  CX_Create_Scale   (Widget, char *, CX_Attrib *);
Widget  CX_Create_Dial    (Widget, char *, CX_Attrib *);
Widget  CX_Create_List_Tree (Widget, char *, CX_Attrib *);
Widget  CX_Create_Scrollbar (Widget, char *, CX_Attrib *);
Widget  CX_Create_Profile (Widget, char *, CX_Attrib *);
Widget  CX_Create_TaskPage  (char *, CX_Attrib *);
Widget  CX_Create_Text_Edit (Widget, char *, CX_Attrib *);
Widget  CX_Create_Expression_Entry(Widget, char *, CX_Attrib *);
Widget  CX_Create_Expression_Plot(Widget, char *, CX_Attrib *);
Widget  CX_Create_Colormap_Editor(Widget, char *, CX_Attrib *);
Widget  CX_Create_Progress_Bar(Widget, char *, CX_Attrib *);
Widget  CX_Get_Tree_Tabbar(void);
Widget  CX_Get_Tree_Dock();
Widget  CX_Get_Workflow_Editor_Dock();
Widget  CX_Get_Workflow_Area(void);
Widget  CX_Get_Navigation_Area  (void);
void    CX_Copy_to_Clipboard (void);
Widget  CX_Create_Dock_Window   (char *, CX_Attrib *);
Widget  CX_Get_TaskPage_Area  (void);
CXBoolean  CX_Get_TaskPage_Closed(void);
Widget  CX_Get_JobSubmission_Area (void);
Widget  CX_Get_Graphics_Area  (void);
Widget  CX_Get_Graphics_Dock  (void);
Widget  CX_Get_Parameters_Area(void);
Widget  CX_Get_Outline_Area(void);
Widget  CX_Get_DP_Area(void);
Widget  CX_Get_Status_Area(void);
Widget  CX_Get_Nav_Taskpage_Splitter(void);
Widget  CX_Create_Splitter (Widget, char *, CX_Attrib *) ;
void    CX_Show_Splitter   (Widget, int) ;
void    CX_Resize_Splitter_Children (Widget) ;
void    CX_Resize_Splitter_To_Child_Size(Widget widget, int child);
Widget  CX_Create_Graphics_View (Widget, char *, CX_Attrib *) ;
Widget  CX_Create_ToolBar   (char *, CX_Attrib *);
Widget  CX_Create_ToolBar_Item (Widget, char *, CX_Attrib *) ;
Widget  CX_Get_ToolBar_Item (Widget, char *) ;
void    CX_Enable_ToolBar_Item(char *, CXBoolean);
Widget  CX_Create_Menu (char *, CX_Attrib *) ;
Widget  CX_Create_Submenu (Widget, char *, CX_Attrib *) ;
Widget  CX_Create_Menu_Item (Widget, char *, CX_Attrib *) ;
CXBoolean CX_Component_Visible(char *);
void  CX_Show_Component(char *, CXBoolean);
void  CX_Show_Popup_Menu(Widget popup, Widget widget);
void CX_Update_Taskpages(void);
void CX_Init_Script_Editor(void);
void CX_Script_Editor_Set_Text(char *, CXBoolean);
CXBoolean CX_Script_Editor_Get_Text(int block_number, char **str);
void CX_Set_Script_Editor_Commands(int, char **);
void CX_Set_Script_Editor_Command_Classes(int, char **);
void CX_Set_Script_Editor_Command_Properties(char *, int, char **);
CXBoolean CX_Set_Style_Sheet(const char *);
CXBoolean CX_Set_Color_Theme(const char *);
CXBoolean CX_Set_Font_Size(int);
void CX_Update_MainWindow();
void CX_Set_Ui_Style(const char *);
CXBoolean CX_Can_Set_Client_Mode(char *, int);
void CX_Set_Client_Mode(char *);
char *CX_Advance_Message(void);
void CX_Read_Graphics_ToolBar_Layout(char *);
void CX_Save_Graphics_ToolBar_Layout(char *);
void CX_Activate_SubWindow(int id);
void CX_Add_TUIs_To_Console(Pointer tui_menu_strs, CXBoolean);
void CX_Add_Inputs_To_Console(Pointer);
void CX_Add_TUIs_To_Quick_Search(Pointer tui_menu_strs);
void CX_Show_Startup_Page(Pointer show);
void CX_Close_Startup_Page();
void CX_Enable_Startup_Page(Pointer show);
void CX_Client_Mode_Changed();
void CX_Set_Console_Reading_FileName(CXBoolean arg);
void CX_Set_Console_Reading_Input(CXBoolean arg);
void CX_Disable_Console_Completer();
void CX_Set_Console_ReadOnly(CXBoolean arg);
Widget CX_Add_Extra_Console(char *, char *, char *, CXBoolean autoRaise);
void CX_Rename_Extra_Console(char *, char *);
void CX_Remove_Extra_Console(char *);
void CX_Clear_Extra_Console(char *);
CXBoolean CX_Is_Console_Hidden();
FLUENT_EXPORT CXBoolean CX_Append_To_Console (Widget w, const char *t);
void CX_Start_Console_Message(CXBoolean val);
void CX_Set_Spreadsheet_Widgets(Widget widget, Widget *itemList);
void CX_Set_Spreadsheet_Cell_Data(Widget widget, int row, int column, char *text);
const char *CX_Get_Spreadsheet_Cell_Data(Widget widget, int row, int column);
CXBoolean CX_Is_Spread_Sheet_Cell_Edited(Widget widget, int row, int column);
void CX_Clear_Spread_Sheet_Cell_Edited_Flag(Widget widget, int row, int column);
void CX_Set_Spreadsheet_Cell_Color(Widget widget, int row, int column, const char *color, CXBoolean backColor);
void CX_Set_Spreadsheet_Cell_Alignment(Widget widget, int row, int column, const char *alignment);
void CX_Set_Spreadsheet_Model_Data(Widget widget, int row, int column, char *text);
const char *CX_Get_Spreadsheet_Model_Data(Widget widget, int row, int column);
void CX_Set_Spreadsheet_Column_Data(Widget widget, int column, const char *items[]);
const char **CX_Get_Spreadsheet_Column_Data(Widget widget, int column);
void CX_Set_Spreadsheet_Data_Types(Widget widget, char *items[]);
void CX_Set_Spreadsheet_Format_Strings(Widget widget, char *items[]);
void CX_Set_Spreadsheet_Columns_Editable(Widget widget, char *items[]);
void CX_Set_Spreadsheet_Row_Editable(Widget widget, int row, CXBoolean state);
void CX_Set_Spreadsheet_Cell_Editable(Widget widget, int row, int col, CXBoolean state);
void CX_Set_Spreadsheet_Hide_Checkbox(Widget widget, int row, int col, CXBoolean hide);
const char *CX_Get_Spreadsheet_Column_Data_Type(Widget widget, int column);
const char *CX_Get_Spreadsheet_Column_Format_String(Widget widget, int column);
void CX_Set_Spreadsheet_Selections(Widget widget, int column, const char *items[]);
void CX_Set_Spreadsheet_Selection_By_Row_Column(Widget widget, int row, int column);
void CX_Show_Spreadsheet_Selections(Widget widget, int column, char **items[]);
void CX_Get_Spreadsheet_Rows_For_Data(Widget widget, int column, char *items[], int *rows[], int *n);
void CX_Clear_Spreadsheet(Widget widget, CXBoolean saveCells);
int CX_Get_Spreadsheet_Selected_Row(Widget widget);
int CX_Get_Spreadsheet_Selected_Column(Widget widget);
void CX_Clear_Spreadsheet_Cell(Widget widget, int row, int column);
CXBoolean CX_Spreadsheet_Cells_Empty(Widget widget);
CXBoolean CX_Spreadsheet_Cells_Invalid(Widget widget);
void CX_Set_Spreadsheet_Row_Header(Widget widget, int row, char *text);
void CX_Set_Spreadsheet_Column_Header(Widget widget, int column, char *text);
const char *CX_Get_Spreadsheet_Column_Header(Widget widget, int column);
int CX_Get_Spreadsheet_Column_By_Header(Widget widget, const char *text);
void CX_Set_Spreadsheet_Column_Width(Widget widget, int column, int width);
int CX_Get_Spreadsheet_Column_Width(Widget widget, int column);
int CX_Get_Spreadsheet_Column_Count(Widget widget);
void CX_Load_Cached_Rows(Widget widget);
void CX_Get_Cached_Row_Numbers(Widget widget, int *items[], int *n);
void CX_Get_Cached_Row_Data(Widget widget, char **items[], int row, CXBoolean oldOrNew);
void CX_Insert_Cached_Row_Data(Widget widget, char *oldRowName, char *newItems[]);
void CX_Add_Column_Rule_Allowed_Values(Widget widget, int ruleColumn, int columnRuleId, char *allowedValueItems[]);
void CX_Add_Column_Rule_Dependency_Columns(Widget widget, int ruleColumn, int columnRuleId, int *dependencyColumnItems);
void CX_Add_Column_Rule_Dependency_Values(Widget widget, int ruleColumn, int columnRuleId, char *dependencyValueItems[]);
void CX_Free_Spreadsheet_List_Data(char *[]);
CXBoolean CX_Get_Cells_Updated(Widget widget);
void CX_Reset_Cells_Updated(Widget widget);
void CX_Reset_Cached_Row_Data(Widget widget);
void CX_Set_Spreadsheet_Filter_Categories(Widget widget, const char *items[], const char *typeItems[]);
void CX_Set_Spreadsheet_Columns_Visible(Widget widget, int *dependencyColumnItems, CXBoolean bShow);
void Cx_Set_Spreadsheet_Button_Visible(Widget widget, const char *name, CXBoolean bShow);
void CX_Set_Spreadsheet_Columns_Stretchable(Widget widget, int *dependencyColumnItems);
void Cx_Size_Spread_Sheet_To_Contents(Widget widget);

void CX_Delete_Help_Page(Widget widget);

char *CX_Get_Linux_Distribution();

void CX_Browse_Folder(String panelname, char *path, int path_len);
void CX_Reparent_Widget(Widget w, Widget p);
void CX_Show_Console_Message_Box(String val);
void CX_Clear_Console_Message_Box(String val);
void CX_Set_Console_Status_Button(Widget b);

/* cxg_win.cpp */
void CX_Refit_Scale_Contents(CXBoolean force, CXBoolean decreaseOnly);
void Compute_Surface_Edges(CX_Surface *s);
int In_Surface_Normal_List(CX_Surface *s);
void Shrink_Element(int, float *, float);

Pointer convertToQVariant(Pointer p);

void  cx_units_read_table (String, char **, double *, double *);
void  CX_Get_Unit_Dimensions(const char *quantity, double dimensions[10]);

CXBoolean CX_Is_Feature_Available(const char *feature_name);

/* Defined in cxgui.cxx */
extern CXBoolean Is_CX_Or_Client_Busy(void);
int CX_Button_Status(void);
void CX_Register_Graphics_Window(char *, int);
void CX_Unregister_Graphics_Window(int);
void CX_Set_Graphics_Window_Title(int id, const char *const title);
void CX_Get_Graphics_Window_Title(int id, char *returnString);

void CX_Set_Override_Cursor(CxCursorShape cursorShape);
void CX_Restore_Override_Cursor();
void CX_Set_Plot_Window_Title(int windowId, const char *const title);
void CX_Set_Graphics_Window_Icon(int window_id, const char *icon_name, CXBoolean grayscale);
void CX_Set_Console_Buttons_Beta();

void CX_Get_Last_Activated_MDI_Window(char *returnString);

// embedded windows apis
void CX_Set_Block_Swap_Windows(CXBoolean block);
CXBoolean CX_Get_Block_Swap_Windows();
CXBoolean CX_Is_Embedded_Window(int windowId);
void CX_Close_Embedded_Window(int windowId);
void CX_Move_Back_Embedded_Window(int windowId);
void CX_Close_All_Embedded_Windows(int parentWindowId);
void CX_MoveBack_All_Embedded_Windows(int parentWindowId);
void CX_Raise_All_Embedded_Windows(int parentWindowId);
void CX_Hide_All_Embedded_Windows(int parentWindowId, CXBoolean hideWindow);
void CX_Update_All_Embedded_Windows_Details();
void CX_Embed_In(int winId, int parentWinId);
int CX_Get_Mesh_Window_Id();
void CX_Set_Solution_View_Id(int id);
int CX_Get_Solution_View_Id();
int CX_Create_Solution_View();
CXBoolean CX_Is_Embedded_Windows_Feature_Available();
void CX_Update_Embedded_Window_Status(int winId, CXBoolean update);
void CX_Auto_Embed_Windows(int win_id);
void CX_Swap_Embedded_Window(int winId);
int CX_Get_Parent_Id_For_Embedded_Window(int winId);
void CX_Disable_Graphics_Drawing_Area(CXBoolean);

CXBoolean CX_Is_Fluent_Application();
CXBoolean CX_Is_Full_Screen();
void CX_Toggle_Full_Screen();

void CX_Stop_Progress_Server(void);
void CX_Start_Progress_Server(void);
void CX_Push_Progress_Data(char *[20], double *, int);
void Send_Ext_Port_Progress_Data(char *field, char *value, int tag);
/* Common routines for the html help */
#define HELP_MAX_STRING 128

typedef enum
{
  HELP_TOKEN_EOF = 0,
  HELP_TOKEN_CASE,
  HELP_TOKEN_PAROPEN,
  HELP_TOKEN_PARCLOSE,
  HELP_TOKEN_COLON,
  HELP_TOKEN_BREAK,
  HELP_TOKEN_JUMP,
  HELP_TOKEN_STRING,
  HELP_TOKEN_ERROR
} Help_Token_Type;

typedef struct help_token_struct
{
  Help_Token_Type type;
  char s[HELP_MAX_STRING];
} Help_Token;

typedef struct help_node_struct
{
  char filename[HELP_MAX_STRING];
  char anchor[HELP_MAX_STRING];
  struct help_node_struct *next;
} Help_Node;

void CX_Help_Free_Table(void);
void CX_Help_Parse_File(char *);
char *CX_Help_Get_File_Name(char *);
void CX_Help_Dump_Table(char *);
void CX_Send_Help_Command(char * );

void CX_TGrid_Help_Display(char * );

void init_general_utils(void);
void initialize_library_exp_proxy(void);
void initialize_library_dm_exp(void);

#if !_NT
void Set_Select_Folder(CXBoolean);
char *Get_Folder_Path(void);
#endif

FLUENT_EXPORT char *getCacheCommandLine(void);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _CXServ_h_ */

