/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/*
 *  cx.h
 *  Included by CORTEX client applications.
 *  @(#)cx.h  1.92 07/16/98
 */

#ifndef _CX_H
#define _CX_H

#include "seem.h"
#include "dll.h"
#include "cxbool.h"
#include "cxm.h"
#include "string_safe.h"

#ifndef HC_POINT
# define HC_POINT void

/* NOTE: if you want a real definition for "HC_POINT", do:

typedef struct {float x, y, z;} Point;

#define HC_POINT  Point

   in your program before including cx.h.
*/

#endif /* HC_POINT */

#if !UDF_COMPILER

/* Implement "static assertion":
 * From: http://www.pixelbeat.org/programming/gcc/static_assert.html,
 * "Code on the page is licensed under the GNU All-Permissive License."
 */
/* Note we need the 2 concats below because arguments to ##
 * are not expanded, so we need to expand __LINE__ with one indirection
 * before doing the actual concatenation. */
#define ASSERT_CONCAT_(a, b) a##b
#define ASSERT_CONCAT(a, b) ASSERT_CONCAT_(a, b)
/* These can't be used after statements in c89. */
#ifdef __COUNTER__
#  define STATIC_ASSERT(e,m) \
     /* ; */ enum { ASSERT_CONCAT(static_assert_, __COUNTER__) = 1/(int)(!!(e)) }
#else
/* This can't be used twice on the same line so ensure if using in headers
 * that the headers are not included twice (by wrapping in #ifndef...#endif)
 * Note it doesn't cause an issue when used on same line of separate modules
 * compiled with gcc -combine -fwhole-program.  */
#  define STATIC_ASSERT(e,m) \
     /* ; */ enum { ASSERT_CONCAT(assert_line_, __LINE__) = 1/(int)(!!(e)) }
#endif
/* Leading semicolons (';') commented out by Jochen, because they cause a warning,
 * which in tgridmesher is treated as an error and breaks the build. (They were
 * implemented for a reason by the originator of this code snippet -- cf. above.)
 */

#include <float.h>
/* define 64-bit integer type,
   cortex uses _ARCH macros, while those are only set on some architectures while compiling in
   a fluent or addon context, so add also sys_ARCH macros, if not sure */
#if (_lnx86 || _lnamd64 || _linmic || _lop64 || _lnarm64 ||_lnia64 || _aix51 || _aix51_64 || _ultra_64 || sys_aix51 || sys_aix51_64 || sys_ultra_64)
# include <stdint.h>
#else
# if (_hpux11 || _hpux11_64 || _hpux11_ia64 || sys_hpux11 || sys_hpux11_64 || sys_hpux11_ia64)
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
/* Test for the assumption used in the above two macros: */
STATIC_ASSERT(sizeof(int64_t) == 2 * sizeof(int), "Error: assumed int64 to be twice as big as int");

/* Test for an assumption made in prf.h: */
STATIC_ASSERT(sizeof(int64_t) == sizeof(long long), "Error: assumed 'long long' to be equivalent to int64_t");

#endif /* UDF_COMPILER */

#ifdef __cplusplus
extern "C"
{
#endif

/* Cortex client-side globals */
extern CXBoolean cxStudentOnly;
extern CXBoolean cxPostOnly;
extern CXBoolean cxEducationalOnly;
extern CXBoolean cxEducationalOnlyLogo;
extern int cxInterrupted;

/* Cortex defines */
#define CX_PATH_END 0
#define CX_PATH_ACTIVE  1
#define CX_PATH_BREAK 2
#define CX_PATH_ABORT   3

#define CX_TYPE_CONTOUR   0
#define CX_TYPE_VECTOR    1
#define CX_TYPE_SURFACE   2
#define CX_TYPE_PATHLINE    3

/* Cortex functions */
void  CX_Initialize   (int *, char *[], char *, char *(*)());
int CX_Client_Register  (char *, int, int, int);
void  CX_Client_Unregister  (void);
FLUENT_EXPORT Pointer CX_Interpret_String(char *);
FLUENT_EXPORT Pointer CX_Execute_Command(Pointer);
void  CX_Terminate    (void);

int     CX_Client               (void);
int CX_Single   (void);
#if  !(CX_NODE || CX_HOST)
int CX_Start_Monitor_Thread(int port, char *hname);
#endif

FLUENT_EXPORT void CX_Init_Release_Revision(char *exeName);
FLUENT_EXPORT int CX_Release_Revision(void);

FLUENT_EXPORT void  CX_Primitive_Error  (const char *, ...);
FLUENT_EXPORT void  CX_Disable_Interrupts (void);
FLUENT_EXPORT void  CX_Enable_Interrupts  (void);
FLUENT_EXPORT int CX_Interrupts_Enabled (void);
FLUENT_EXPORT void      CX_Stop                 (const char *, ...) ;
int CX_Check_Interrupt  (void);
int CX_Check_Pending_Interrupt (void);
void  CX_Reset_Interrupt  (void);
FLUENT_EXPORT int CX_Is_Any_Workspace_Connected(void);

#ifndef _nec
FLUENT_EXPORT int     CX_Message  (const char *, ...);
FLUENT_EXPORT int     CX_Warning(const char *, ...);
#endif
#if  CX_NODE || CX_HOST
FLUENT_EXPORT int     CX_Message0       (const char *, ...);
FLUENT_EXPORT int     CX_Warning0       (const char *, ...);
#else
#define  CX_Message0  CX_Message
#define  CX_Warning0  CX_Warning
#endif
FLUENT_EXPORT int     cxprintf    (FILE *, const char *, ...);
FLUENT_EXPORT cxboolean  Is_system_interrupted(void);
FLUENT_EXPORT void   *CX_Malloc_MU_Silent(size_t, const char *, int);
FLUENT_EXPORT void   *CX_Realloc_MU_Silent(void *, size_t, const char *, int);
FLUENT_EXPORT void   *CX_Calloc_MU_Silent(size_t, size_t, const char *, int);
FLUENT_EXPORT void   *CX_Malloc_MU  (size_t, const char *, int);
FLUENT_EXPORT void   *CX_Realloc_MU (void *, size_t, const char *, int);
FLUENT_EXPORT void   *CX_Calloc_MU      (size_t, size_t, const char *, int);
FLUENT_EXPORT void    CX_Free_MU  (void *, const char *, int);
/* Mem functions which do not handle interrupts */
FLUENT_EXPORT void   *CX_Malloc_MU_Unsafe(size_t, const char *, int);
FLUENT_EXPORT void   *CX_Realloc_MU_Unsafe(void *, size_t, const char *, int);
FLUENT_EXPORT void   *CX_Calloc_MU_Unsafe(size_t, size_t, const char *, int);
FLUENT_EXPORT void    CX_Free_MU_Unsafe(void *, const char *, int);
int    Get_myid(void);
size_t get_meminfo_peak(size_t *current);
void   setmtrace(int);
void   setmtracelog(char *);
void   reportmemusage(void);
FLUENT_EXPORT void CX_Send_String_List(char **pca, int size);

#if _NT
int strcasecmp  (const char *, const char *);
int strncasecmp (const char *, const char *, int);
#endif

int cx_readdir    (char *, char *, char *, char ***, int *);

double  CX_Current_Time   (void);

/* Remote calls */

FLUENT_EXPORT void  CX_Flush    (void);
void  CX_Periodic   (int, int, float *);
void  CX_Symmetry   (const HC_POINT *);
void  CX_Color_Segments (void);
void    CX_Set_Contour_Options  (void);
void  CX_Contour_Triangle (const HC_POINT *, const HC_POINT *);
void  CX_Contour_Line   (const HC_POINT *, const HC_POINT *);
void  CX_Contour_Poly   (int, const HC_POINT *,
                         const HC_POINT *);
void  CX_Vector   (const HC_POINT *, const HC_POINT *,
                   float);

FLUENT_EXPORT void    CX_Update_Graphics      (void);
FLUENT_EXPORT void  CX_Color_By_Value (float);
FLUENT_EXPORT void    CX_Set_Color            (char *);
FLUENT_EXPORT void    CX_Define_Surface       (int, float *, int, int *, int, int, int);

/**
 * RInsert use integer keys, RLInsert use long key, used in tgrid for
 * for cxindex (USE_INT64), once cxindex is used in cortex these functions can
 * be combined in one.
 */
FLUENT_EXPORT void CX_RInsert_Shell(int, int, int, const HC_POINT *, int, int *, int, int *, int *, float *, float *);
FLUENT_EXPORT void CX_RInsert_Multi_Shells(int *, int *, int *, float *, int *, int *, int *, int *, int *, float *,
                                           float *, int, char *);
void CX_RLInsert_Shell(int, int, int, const HC_POINT *, int, int *, int,
                       long *, int *, float *, float *);
void CX_RLInsert_Multi_Shells(int *, int *, int *, float *, int *, int *, int *, long *, int *, float *,
                              float *, int, char *);

void    CX_Suspend_All_Surfaces (void);
void    CX_Contour_Surface      (int, int, float *, int, int *);
void  CX_Set_Vis_Name   (char *, int);
void  CX_Insert_Pathline  (int *, float *, float *);

FLUENT_EXPORT void    CX_Start_Draw_Grid      (char *, int, int, char *);
FLUENT_EXPORT void    CX_End_Draw_Grid        (void);
FLUENT_EXPORT void    CX_Insert_Line          (const HC_POINT *);
FLUENT_EXPORT void    CX_Insert_Triangle  (const HC_POINT *);
FLUENT_EXPORT void    CX_Insert_Tetra   (const HC_POINT *);
FLUENT_EXPORT void    CX_Insert_Quad    (const HC_POINT *);
FLUENT_EXPORT void    CX_Insert_Hex   (const HC_POINT *);
FLUENT_EXPORT void    CX_Insert_Pyr   (const HC_POINT *);
FLUENT_EXPORT void    CX_Insert_Wedge   (const HC_POINT *);

void    CX_Insert_Polyhedron (int, const HC_POINT *, int, int []);

FLUENT_EXPORT void    CX_RInsert_Line   (const HC_POINT *, int);

void    CX_RInsert_Polyline (int, const HC_POINT *, int);
void    CX_RInsert_Triangle (const HC_POINT *, int);
void    CX_RInsert_Quad   (const HC_POINT *, int);
void    CX_RInsert_Polygon  (int, const HC_POINT *, int);
void    CX_RInsert_Tetra  (const HC_POINT *, int);
void    CX_RInsert_Hex          (const HC_POINT *, int);
void    CX_RInsert_Pyr          (const HC_POINT *, int);
void    CX_RInsert_Wedge  (const HC_POINT *, int);
void    CX_RInsert_Polyhedron   (int, const HC_POINT *, int, int [], int);

/**
 * RLInsert use long keys, RInsert functions above use int key,
 * The RLInsert functions are used in tgrid for for cxindex (USE_INT64),
 * once cxindex is used in cortex, the RLInsert function can take cxindex.
 * (USE_INT64 is used in parallel, also rpc/xdr calls may need update to
 * handle cxindex depending how implementation is done).
 * L is used as tag only to distinguish this set of functions
 * R to follow similar names to already exisitng funxtions (above).
 */

void    CX_RLInsert_Line    (const HC_POINT *, long);
void    CX_RLInsert_Polyline (int, const HC_POINT *, long);
void    CX_RLInsert_Triangle  (const HC_POINT *, long);
void    CX_RLInsert_Quad  (const HC_POINT *, long);
void    CX_RLInsert_Polygon   (int, const HC_POINT *, long);
void    CX_RLInsert_Tetra (const HC_POINT *, long);
void    CX_RLInsert_Hex         (const HC_POINT *, long);
void    CX_RLInsert_Pyr         (const HC_POINT *, long);
void    CX_RLInsert_Wedge (const HC_POINT *, long);
void    CX_RLInsert_Polyhedron  (int, const HC_POINT *, int, int [], long);

void  CX_Client_LS_Return (char **, int);

int CX_Server_Version (void);
int CX_Command_Port   (void);

float CX_Distance2_Element  (float [], int, float [][3]);


void    CX_Fill_Array           (char *, float *, int);
void    CX_Fill_Active_Array    (char *, int *, int);
void    CX_Fill_Temp_Bitmap     (char *, int, int, char *);

int CX_XY_Plot_Data   (int npts, float *x, float *y, FILE *f, int *active_flag, CXBoolean reAdjustWindow);
int     CX_Write_IBL            (FILE *);
int     CX_Write_FieldView_File (FILE *, char *);
Pointer CX_Read_FieldView_File  (FILE *);
int     CX_Write_Ensight_Particle_File(char *, char *, char *, int);


#if 0 /* no longer used (see cxgrid.c comments) */
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
#endif /* no longer used (see cxgrid.c comments) */

/* cxcf.c */
/* CX_Field_Eval: Eval custom field functions. */
/*   name: name of custom field function
 *   node_values: whether node_values is to be filled
 *   svar: Svar to fill in (only if node_values is FALSE); if svar == -1, SV_POST_VAR is filled
 *   fill_values: Whether values need to be filled in Svar or NODE_VALUE
 *   compute_min_max: Whether min/max needs to be computed
 *   min_p: pointer to store min value
 *   max_p: pointer to store max value
 *
 *   return value: 1 --> CFF does not exist, 0 --> success
 */
int CX_Field_Eval(const char *name, CXBoolean node_values, int svar,
                  CXBoolean fill_values, CXBoolean compute_min_max, float *min_p, float *max_p);



FLUENT_EXPORT void CX_Eval_Vi(void);

/* license.c */
int Client_Init_License(int, char *[]);
int CX_Init_License             (char *);
int CX_Checkout_License         (void);
int CX_Checkout_N_Licenses      (int);
int CX_Checkout_N_Neutral_Licenses (int);
int CX_Check_Feature_Match  (char *, int);
int CX_Free_Feature(char *);
int CX_Free_License             (void);
int CX_License_Feature_With_Holdtime(char *, int);
int CX_Release_Holdtime_Licenses(void);
int CX_Check_Feature_Valid      (char *);
int CX_ANSYS_Avail              (void);
int CX_Is_EducationalOnly (void);
int CX_Is_EducationalOnlyLogo (void);
FLUENT_EXPORT int CX_Is_StudentOnly    (void);
FLUENT_EXPORT int CX_Is_PostOnly    (void);
int CX_Is_Meshing               (void);
FLUENT_EXPORT int CX_License_Feature    (char *);
FLUENT_EXPORT void CX_Call_Vi   (void);
FLUENT_EXPORT int CX_Check_License_Connection (void);
FLUENT_EXPORT int CX_Get_License_Timeout      (void);
int CX_Get_License_Use_Type (void); /*returns 0: Commercial, 1:Student, 2: Teaching, 3: Other Academic cases.*/
FLUENT_EXPORT int CX_Get_License_Level        (void);
FLUENT_EXPORT int CX_Get_Interrupt_Count      (void);
int CX_Enable_License_Sharing(char *appName, char *licenseCSV);
void CX_End_License_Sharing();
void CX_License_Sharing_Push();
void CX_License_Sharing_Pop();
#include "cxiface.h"
#include "cxpoly.h"

cxboolean CX_CFF_Check_Evaluable_On_Thread(const char *name, ThreadHandle thread);
/* Supported client-side Hoops functions - these eliminate the need to
 * include hc.h in clients.
 */

void  HC_Define_Color_Name  (const char *, const char *,
                             const char *, const char *);
void  HC_Set_Camera_By_Volume (const char *, double, double,
                               double, double);
void  HC_Set_Heuristics (const char *);
void  HC_Set_Text_Font  (const char *);
void  HC_Set_Text_Alignment (const char *);
void  HC_Set_User_Options (const char *);
FLUENT_EXPORT void  HC_Set_Color    (const char *);
FLUENT_EXPORT void  HC_Set_Color_By_Index (const char *, int);
FLUENT_EXPORT void  HC_Set_Marker_Size  (double);
FLUENT_EXPORT void  HC_Set_Marker_Symbol  (const char *);
FLUENT_EXPORT void  HC_Set_Visibility (const char *);
FLUENT_EXPORT void  HC_Flush_Contents (const char *, const char *);
FLUENT_EXPORT void HC_Set_Line_Weight    (double);
FLUENT_EXPORT void HC_Set_Line_Pattern   (const char *);
#if WIN64
void  HC_RInsert_Marker (double, double, double, LONG_PTR);
#else
void  HC_RInsert_Marker (double, double, double, long);
#endif
void  HC_RInsert_Mesh   (int, int, const HC_POINT *, long);
#if WIN64
void  HC_RInsert_Polygon  (int, const HC_POINT *, LONG_PTR);
void  HC_RInsert_Polyline (int, const HC_POINT *, LONG_PTR);
#else
void  HC_RInsert_Polygon  (int, const HC_POINT *, long);
void  HC_RInsert_Polyline (int, const HC_POINT *, long);
#endif
void  HC_RInsert_Shell  (int, const HC_POINT *, int, int [], long);

FLUENT_EXPORT void  CX_HC_Initialize_Shell(int, int); /* For transfer of shells of big sizes*/


FLUENT_EXPORT void  HC_Close_Segment  (void);
#if _WIN64 || __INTEL_COMPILER
FLUENT_EXPORT void  HC_Include_Segment  (const char *);
FLUENT_EXPORT void  HC_Insert_Circle  (const HC_POINT *, const HC_POINT *,
                                       const HC_POINT *);
FLUENT_EXPORT void HC_Insert_Cylinder    (const HC_POINT *, const HC_POINT *, double, char *);
FLUENT_EXPORT void  HC_Insert_Image   (double, double, double, char *,
                                       int, int, unsigned char *);
FLUENT_EXPORT void  HC_Insert_Marker  (double, double, double);
void  HC_Insert_Mesh    (int, int, const HC_POINT *);
FLUENT_EXPORT void HC_Insert_Polygon  (int, const HC_POINT *);
FLUENT_EXPORT void  HC_Insert_Polyline  (int, const HC_POINT *);
FLUENT_EXPORT void  HC_Insert_Shell   (int, const HC_POINT *, int, int []);
FLUENT_EXPORT void  HC_Insert_Text    (double, double, double, const char *);
FLUENT_EXPORT void  HC_Open_Segment   (const char *);
FLUENT_EXPORT void  HC_Style_Segment  (const char *);
FLUENT_EXPORT void  HC_Update_Display (void);
#endif
FLUENT_EXPORT void  HC_Translate_Object (double, double, double);
FLUENT_EXPORT void  HC_Rotate_Object  (double, double, double);
FLUENT_EXPORT void  HC_Delete_Segment (const char *);

#ifdef __cplusplus
}
#endif

/* Rampant compatibility */

#if RP_3D || RP_2D
# if PARALLEL
#  define Message0 CX_Message0
#  define Warning0 CX_Warning0
# else
#  define Message0 CX_Message
#  define Warning0 CX_Warning
# endif
# define Message CX_Message
#ifndef Warning
# define Warning CX_Warning
#endif
# define Primitive_Error CX_Primitive_Error
# define disable_interrupts CX_Disable_Interrupts
# define enable_interrupts CX_Enable_Interrupts
# define interrupts_enabled CX_Interrupts_Enabled

#endif

#endif /* _CX_H */
