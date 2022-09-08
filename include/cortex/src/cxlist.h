/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/********************************************************************

    cxlist.h

    Generic Linked List

    Written By: Paul Felix  4/10/91

*********************************************************************/

/* See documentation in cxlist.c!
 */

#if  ( ( ! defined ( _CXLIST_H ) ) || defined ( CX_LIST_TYPE_NAME ) )
#ifndef   CX_LIST_TYPE_NAME       /* "regular" mode */
# define  CX_LIST_TYPE_NAME  List
# define  CX_LIST_DEFAULT    List
# define _CXLIST_H
# ifdef  OBJ
#  warning redefining OBJ because CX_LIST_TYPE_NAME is not defined
#  undef OBJ
# endif
# define OBJ char*
#else   /* i.e. ifdef CX_LIST_TYPE_NAME, i.e. "NON-regular" mode, a custom, non-pointer type for the payload: */
# ifndef OBJ
#  error must define OBJ along with CX_LIST_TYPE_NAME
# endif
#endif

#include "cxmacros.h"   /* CATTWOARGS(..., ...) */
#include "cxbool.h"     /* FALSE */

/* Will be undef'd below: */
#define CX_LIST_ADD_PREFIX_TO(funnam)  CATTWOARGS(CX_LIST_TYPE_NAME, funnam)


#ifndef NULL
# define NULL 0
#endif

/* Without the following, couldn't compile cxgui/CxPanelItem.hpp, included in cxqt/CxPanelItemQt.hpp.. */
#ifndef XMD_H
typedef int BOOL;
#endif

#ifndef CX_MALLOC
#define CX_MALLOC CX_Malloc
#define CX_FREE(obj) {if (obj) CX_Free(obj); obj = NULL;}
#endif


typedef void (*CX_LIST_ADD_PREFIX_TO(Callback)) (OBJ, OBJ);

typedef struct CX_LIST_ADD_PREFIX_TO(element)
{
  struct CX_LIST_ADD_PREFIX_TO(element)* prev;
  struct CX_LIST_ADD_PREFIX_TO(element)* next;
  OBJ             obj;
}
CX_LIST_ADD_PREFIX_TO(_Element);


typedef struct CX_LIST_ADD_PREFIX_TO(cxlist)
{
  struct CX_LIST_ADD_PREFIX_TO(element)* first;
  struct CX_LIST_ADD_PREFIX_TO(element)* last;
  struct CX_LIST_ADD_PREFIX_TO(element)* current;
  OBJ             nullobj;
  int             size;
}
CX_LIST_TYPE_NAME;

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

void CX_LIST_ADD_PREFIX_TO(Add)          (CX_LIST_TYPE_NAME *, OBJ);
void CX_LIST_ADD_PREFIX_TO(AddFirst)     (CX_LIST_TYPE_NAME *, OBJ);
OBJ  CX_LIST_ADD_PREFIX_TO(After)        (CX_LIST_TYPE_NAME *, OBJ);
OBJ  CX_LIST_ADD_PREFIX_TO(At)           (CX_LIST_TYPE_NAME *, int);
OBJ  CX_LIST_ADD_PREFIX_TO(Before)       (CX_LIST_TYPE_NAME *, OBJ);
CX_LIST_TYPE_NAME     *CX_LIST_ADD_PREFIX_TO(Create)       (void);
OBJ  CX_LIST_ADD_PREFIX_TO(Current)      (CX_LIST_TYPE_NAME *);
void CX_LIST_ADD_PREFIX_TO(Delete)       (CX_LIST_TYPE_NAME *);
OBJ  CX_LIST_ADD_PREFIX_TO(First)        (CX_LIST_TYPE_NAME *);
void CX_LIST_ADD_PREFIX_TO(ForEachDo)    (CX_LIST_TYPE_NAME *, CX_LIST_ADD_PREFIX_TO(Callback), OBJ);
void CX_LIST_ADD_PREFIX_TO(ForEachDoRev) (CX_LIST_TYPE_NAME *, CX_LIST_ADD_PREFIX_TO(Callback), OBJ);
void CX_LIST_ADD_PREFIX_TO(FreeAll)      (CX_LIST_TYPE_NAME *);
cxboolean CX_LIST_ADD_PREFIX_TO(Includes)     (CX_LIST_TYPE_NAME *, OBJ);
void CX_LIST_ADD_PREFIX_TO(InsertAfter)  (CX_LIST_TYPE_NAME *, OBJ, OBJ);
void CX_LIST_ADD_PREFIX_TO(InsertAt)     (CX_LIST_TYPE_NAME *, int, OBJ);
void CX_LIST_ADD_PREFIX_TO(InsertBefore) (CX_LIST_TYPE_NAME *, OBJ, OBJ);
cxboolean CX_LIST_ADD_PREFIX_TO(IsEmpty)      (CX_LIST_TYPE_NAME *);
OBJ  CX_LIST_ADD_PREFIX_TO(Last)         (CX_LIST_TYPE_NAME *);
OBJ  CX_LIST_ADD_PREFIX_TO(Next)         (CX_LIST_TYPE_NAME *);
OBJ  CX_LIST_ADD_PREFIX_TO(Prev)         (CX_LIST_TYPE_NAME *);
OBJ  CX_LIST_ADD_PREFIX_TO(PopFirst)     (CX_LIST_TYPE_NAME *);
OBJ  CX_LIST_ADD_PREFIX_TO(PopLast)      (CX_LIST_TYPE_NAME *);
void CX_LIST_ADD_PREFIX_TO(Remove)       (CX_LIST_TYPE_NAME *, OBJ);
void CX_LIST_ADD_PREFIX_TO(RemoveAll)    (CX_LIST_TYPE_NAME *);
void CX_LIST_ADD_PREFIX_TO(Rewind)       (CX_LIST_TYPE_NAME *);
void CX_LIST_ADD_PREFIX_TO(SetCurrent)   (CX_LIST_TYPE_NAME *, OBJ);
int  CX_LIST_ADD_PREFIX_TO(Size)         (CX_LIST_TYPE_NAME *);
CX_LIST_ADD_PREFIX_TO(_Element) *CX_LIST_ADD_PREFIX_TO(FindElement)  (CX_LIST_TYPE_NAME *, OBJ);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#undef CX_LIST_ADD_PREFIX_TO

#ifdef CX_LIST_DEFAULT
#undef CX_LIST_TYPE_NAME   /* Make sure this .h file isn't processed twice in "regular" mode. */
#endif

#ifndef _INSIDE_CXLIST_C
#undef   CX_LIST_DEFAULT   /* No more need for this. */
#endif

#endif /* _CXLIST_H */

