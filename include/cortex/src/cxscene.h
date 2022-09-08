/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/*
 *  Scene attribute type macros -
 *    defined in cxserv.h
 *
 *    CX_SCENE_TYPE_BOOLEAN
 *    CX_SCENE_TYPE_FLOAT
 *    CX_SCENE_TYPE_FLOAT_ARR   (really triples)
 *    CX_SCENE_TYPE_INT
 *    CX_SCENE_TYPE_STRING
 */
#ifndef _CXSCENE_H
#define _CXSCENE_H

#include "cxconfig.h"
#include "cxbool.h"
#include "cxserv.h"
#include "cxlist.h"
#include "hc.h"



#define CX_SCENE_ROT  0
#define CX_SCENE_TRANS  1
#define CX_SCENE_SCALE  2
#define CX_SCENE_CEN  3
#define CX_SCENE_XPAR 4
#define CX_SCENE_FCOL 5
#define CX_SCENE_ECOL 6
#define CX_SCENE_LCOL 7
#define CX_SCENE_VIS  8
#define CX_SCENE_VFACE  9
#define CX_SCENE_VEDGE  10
#define CX_SCENE_VPER 11
#define CX_SCENE_VLINE  12
#define CX_SCENE_VLIGHT 13
#define CX_SCENE_CH 14
#define CX_SCENE_BBOX 15
#define CX_SCENE_ISOVAL 16
#define CX_SCENE_PATH_STP 17
#define CX_SCENE_FONT_NAME 18
#define CX_SCENE_FONT_COLOR 19
#define CX_SCENE_FONT_SLANT 20
#define CX_SCENE_FONT_SIZE 21
#define CX_SCENE_FONT_WT 22
#define CX_SCENE_MCOL 23
#define CX_SCENE_VMARKER 24
#define CX_SCENE_VOFACE 25
#define CX_SCENE_TIME_STEP 26
/* old types */
#define CX_SCENE_RX 27
#define CX_SCENE_RY 28
#define CX_SCENE_RZ 29
#define CX_SCENE_TX 30
#define CX_SCENE_TY 31
#define CX_SCENE_TZ 32
#define CX_SCENE_SX 33
#define CX_SCENE_SY 34
#define CX_SCENE_SZ 35
#define CX_SCENE_CX 36
#define CX_SCENE_CY 37
#define CX_SCENE_CZ 38
#define CX_SCENE_XC 39
#define CX_SCENE_YC 40
#define CX_SCENE_ZC 41

#define CX_SCENE_MAX_ATTR 42

typedef union
{
  long  asBool;
  long  asInt;
  float asFloat[3];
  char  asString[64];
} CX_Geom_Attrib_Val;

typedef struct cx_geom_attr
{
  int     attr;
  int     type;
  CX_Geom_Attrib_Val  val;
} CX_Geom_Attrib;


typedef struct attr_tab
{
  char name[MAX_NAME_LENGTH];
  int  type;
} attr_table;


typedef struct geom_info
{
  char name[MAX_NAME_LENGTH];                     /* geometry name. */
  int id;                                         /* id, if any. */
  HC_KEY key;                                     /* Hoops segment key. */
  HC_KEY keyPath[30];                             /* In case the geometry is inside an included segment */
  int keyPathCount;                               /* Number of keys in the keyPath */
  int type;                                       /* type of geometry. */
  int nattr_set;                                  /* number of attrs set. */
  CX_Geom_Attrib attr_vals[CX_SCENE_MAX_ATTR];
  /* List of attributes for this geometry. */
  struct geom_info *next; /* For maintaining free list.  More
                 * efficient to do it here than another List */
} cx_geom_info;



#define KEYS_PER_ALLOC 10
#define GEOMS_PER_ALLOC 20

/* cxkeyfrm.c */

typedef struct key_info
{
  int frame;
  List *geoms;
  int nattr_set;    /* number of attr actually set. */
  CX_Geom_Attrib attr_val[CX_SCENE_MAX_ATTR];
  struct key_info *next;  /* free list. */
} cx_key_info;



#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif


List *make_copy_of_scene_info(List *orig_info, CXBoolean copy_attr);
void free_geom_list(List *geom_list, CXBoolean keep_text);
int get_attr_type(char *attr_name, int *attr_ind);
int get_num_defined_attr(int ind);

void CX_Init_Win_Geoms(void);

cx_geom_info *CX_Add_Geometry(int type, const char *name, int id, HC_KEY key,
                              const char *srfname, const int *shadows, int shadowlen);
cx_geom_info *CX_Add_Geometry_With_Path(int type, const char *name, int id, HC_KEY *keyPath, int
                                        keyCount, const char *srfname, const int *shadows, int shadowlen);
void CX_Set_Geom_Seg_Key(int index, HC_KEY key);
HC_KEY CX_Get_Geom_Segment(int win_id, char *name, int id, int type);
void CX_Get_Next_Geom_Desc(char *name, char *type, HC_KEY *seg_key, int *id);

void CX_Remove_Geometry_Window(int win_id, CXBoolean keep_text);
void CX_Remove_Geometry(int type, char *name, int id, int index);
int  CX_Get_Num_Geoms(int win_id);
void CX_Set_All_Geoms_Attr_In_Hoops(void);
void CX_Set_One_Geoms_Attr_In_Hoops(int gindx);
void CX_Scene_Set_Geom_Info(void);
void CX_Set_Geom_Attr(int index, int attr, CX_Geom_Attrib_Val val, int val_type);
void CX_Transfer_Mmatrix_To_Highlight(int gindex);
CXBoolean CX_Get_Geom_Attr(int gindex, int aindex, char *attr_name, CX_Geom_Attrib_Val *val, int *val_type);


List *CX_Get_Window_Geom_List(int win_id);
void CX_Set_Window_Geom_List(int win_id, List *new_list);
List *CX_Swap_Window_Geom_List(int win_id, List *new_list);


/* cxkeyfrm.c */


void CX_Init_Keyframes(void);
void CX_Scene_Interp_Frame(int frame, CXBoolean force);
void CX_Insert_Keyframe(int key_frame );
void CX_Delete_Keyframe(int key_frame );


#if defined(__cplusplus) || defined(c_plusplus)
}


//cpp specific functions
#include <set>
#include <string>
#include <unordered_map>
std::unordered_map<int, int> &CX_Get_Window_SurfaceID_With_Counts(int win_id);
//Get the names of surfaces displayed at the moment in the given window.
// includeHiddenSurfaces : Count invisible / hidden (by selection) surfaces as well in the names (by default it doesn't)
std::set<std::string> CX_Get_Displayed_Surface_Names(int win_id, bool includeHiddenSurfaces = false);

#endif





#endif /* _CXSCENE_H */
