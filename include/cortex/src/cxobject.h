/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _CXOBJECT_H
#define _CXOBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "cxconfig.h"
#include "cxmacros.h"
#include "cxlist.h"
#include "cxtype.h"
typedef char CXBoolean;
#define MY_NEW 0

#if MY_NEW
#undef new
#define new ::new
#undef delete
#define delete ::delete
#endif

#define FREEOBJ(p) if (p) delete p; p = NULL
#define CAST(class, obj) (((obj) ? (class*)((CxObject*)obj)->as(CLASS(class)) : (class*)0))

#define CLASS(name) CAT2(name,::,classID())
#define CLASSID(name) char CAT2(name,::,_classID) = 0;

#define CLASSDEF(myclass,superclass)          \
        private:              \
  static char _classID;           \
        public: \
        static CXPtrAsInt classID() { return (CXPtrAsInt)&_classID; }     \
    char* className() { return QUOTE(myclass); }      \
    CXBoolean isMemberOf(CXPtrAsInt classId) {return classId == (CXPtrAsInt)&_classID;}\
        CXBoolean isKindOf(CXPtrAsInt classId)          \
          {               \
            CXBoolean flag = FALSE;           \
            if (classId == myclass::classID()) flag = TRUE;   \
            else if (superclass::isKindOf(classId)) flag = TRUE;  \
            return flag;            \
          }               \
        void* as(CXPtrAsInt classId)            \
          {               \
            if (classId == myclass::classID()) return this;   \
            return superclass::as(classId);       \
      }

#define CLASSDEF2(myclass,superclass1,superclass2)      \
        private:              \
  static char _classID;           \
        public:               \
    static CXPtrAsInt classID() { return (CXPtrAsInt)&_classID; }     \
        char* className() { return QUOTE(myclass); }      \
        CXBoolean isMemberOf(CXPtrAsInt classId) {return classId == (CXPtrAsInt)&_classID;}\
        CXBoolean isKindOf(CXPtrAsInt classId)          \
          {               \
            CXBoolean flag = FALSE;           \
            if (classId == myclass::classID()) flag = TRUE;   \
            else if (superclass1::isKindOf(classId)) flag = TRUE; \
            else if (superclass2::isKindOf(classId)) flag = TRUE; \
            return flag;            \
          }               \
        void* as(CXPtrAsInt classId)            \
          {               \
      void* p;              \
            if (classId == myclass::classID()) return this;   \
            if (p = superclass1::as(classId)) return p;     \
            return superclass2::as(classId);        \
          }

typedef char *String;

char *FlStrDup(const char *str);

class CxObject
{

// DEFINITION: base class for all Cortex objects.

private:
  static int _classID;

protected:
  char *iErrorMsg;
  List *iDependents;

public:
  CxObject();
  virtual ~CxObject();

  void    addDependent(CxObject *obj);
  virtual void *as(CXPtrAsInt classId);
  virtual void  changed(char *msg = NULL);
  static CXPtrAsInt classID();
  virtual char *className();
  void    dependsOn(CxObject *obj);
  virtual void  error(char *str, ...);
  virtual CXBoolean isKindOf(CXPtrAsInt classId);
  virtual CXBoolean isMemberOf(CXPtrAsInt classId);
  void    removeDependent(CxObject *obj);
  virtual void  update(CxObject *obj, char *msg);
};

#endif /* _CXOBJECT_H */
