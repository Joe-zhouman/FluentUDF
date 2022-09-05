/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/
#ifndef FLUENT_DB_MANAGER
#define FLUENT_DB_MANAGER

#include "config.h"
#include "itype.h"
#include "cxbool.h"

#if RP_DOUBLE
typedef double real;
#else
typedef float real;
#endif

#include <string.h>

typedef struct db_manager_t_
{
  void (*newClass) (void **);     /* input the reference of new DataBaseManager class */
  void (*deleteClass) (void **);  /* input the reference of new DataBaseManager class */

  char *(*getChar) (void **, const char *);
  cxboolean *(*getBoolean) (void **, const char *);
  int *(*getInt) (void **, const char *);
  cxindex *(*getIndex) (void **, const char *);
  size_t *(*getSizeT) (void **, const char *);
  real *(*getReal) (void **, const char *);
  double *(*getDouble) (void **, const char *);
  real *(*getReal3) (void **, const char *);
  char *(*getString) (void **, const char *, size_t);
  int *(*getIntVec) (void **, const char *, size_t);
  cxindex *(*getIndexVec) (void **, const char *, size_t);
  real *(*getRealVec) (void **, const char *, size_t);
  void **(*getPointer) (void **, const char *);
  void *(*getByteVec) (void **, const char *, size_t);
  void *(*getSizeTMap) (void **, const char *);

  size_t(*getVecSize) (void **, const char *);

  char *(*findChar) (void **, const char *);
  cxboolean *(*findBoolean) (void **, const char *);
  int *(*findInt) (void **, const char *);
  cxindex *(*findIndex) (void **, const char *);
  size_t *(*findSizeT) (void **, const char *);
  real *(*findReal) (void **, const char *);
  double *(*findDouble) (void **, const char *);
  real *(*findReal3) (void **, const char *);
  char *(*findString) (void **, const char *, size_t *);
  int *(*findIntVec) (void **, const char *, size_t *);
  cxindex *(*findIndexVec)(void **, const char *, size_t *);
  real *(*findRealVec) (void **, const char *, size_t *);
  void **(*findPointer) (void **, const char *);
  void *(*findByteVec) (void **, const char *, size_t *);
  void *(*findSizeTMap) (void **, const char *);

  void (*setChar) (void **, const char *, const char);
  void (*setBoolean) (void **, const char *, const cxboolean);
  void (*setInt) (void **, const char *, const int);
  void (*setIndex) (void **, const char *, const cxindex);
  void (*setSizeT) (void **, const char *, const size_t);
  void (*setReal) (void **, const char *, const real);
  void (*setDouble) (void **, const char *, const double);
  void (*setReal3) (void **, const char *, const real *);
  void (*setString) (void **, const char *, const char *);
  void (*setIntVec) (void **, const char *, size_t size, const int *);
  void (*setIndexVec) (void **, const char *, size_t size, const cxindex *);
  void (*setRealVec) (void **, const char *, size_t size, const real *);
  void (*setPointer) (void **, const char *, const void *);
  void (*setByteVec) (void **, const char *, size_t size, const void *);

  void (*setSizeTMapValue)(void *v, size_t first, size_t second);
  int (*findSizeTMapKey)(const void *v, size_t first);
  size_t (*getSizeTMapValue)(const void *v, size_t first);

  size_t(*getSize)(void **dbref, const char *key);
  size_t(*getUnitSize)(void **dbref, const char *key);
  int (*getType)(void **dbref, const char *key);
  const char *(*getTypeName)(void **dbref, const char *key);  
  
  void (*appendInt)(void **dbref, const char *key, void *data);
  void (*appendIndex)(void **dbref, const char *key, void *data);
  void (*appendReal)(void **dbref, const char *key, void *data);
  void (*appendDouble)(void **dbref, const char *key, void *data);
  void (*appendString)(void **dbref, const char *key, void *data);
  
  void (*remove) (void **, const char *);
  void (*clear) (void **);
  void (*print) (void **);
  void (*test) (void **);
  void  (*printBrief) (void **);
  size_t (*footprint) (void **);

} db_manager_t;

extern db_manager_t db_manager;

/* get macros to allocate and return the container */
#define DB_GET_BOOLEAN(_str)             (db_manager.getBoolean(NULL, _str))
#define DB_GET_REAL(_str)                (db_manager.getReal(NULL, _str))
#define DB_GET_DOUBLE(_str)              (db_manager.getDouble(NULL, _str))
#define DB_GET_INT(_str)                 (db_manager.getInt(NULL, _str))
#define DB_GET_INDEX(_str)               (db_manager.getIndex(NULL, _str))
#define DB_GET_INT_VEC(_str, _size)      (db_manager.getIntVec(NULL, _str, _size))
#define DB_GET_INDEX_VEC(_str, _size)   (db_manager.getIndexVec(NULL, _str, _size))
#define DB_GET_REAL_VEC(_str, _size)     (db_manager.getRealVec(NULL, _str, _size))
#define DB_GET_DOUBLE_VEC(_str, _size)   (db_manager.getDoubleVec(NULL, _str, _size))
#define DB_GET_STRING(_str, _size)       (db_manager.getString(NULL, _str, _size))
#define DB_GET_POINTER(_str)             (db_manager.getPointer(NULL, _str))
#define DB_GET_BYTE_VEC(_str, _size)     (db_manager.getByteVec(NULL, _str, _size))
#define DB_GET_SIZE_T_MAP(_str)          (db_manager.getSizeTMap(NULL, _str))

/* find macros to allocate and return the container */
#define DB_FIND_BOOLEAN(_str)            (db_manager.findBoolean(NULL, _str))
#define DB_FIND_REAL(_str)               (db_manager.findReal(NULL, _str))
#define DB_FIND_DOUBLE(_str)             (db_manager.findDouble(NULL, _str))
#define DB_FIND_INT(_str)                (db_manager.findInt(NULL, _str))
#define DB_FIND_INDEX(_str)              (db_manager.findIndex(NULL, _str))
#define DB_FIND_INT_VEC(_str, _size)     (db_manager.findIntVec(NULL, _str, &(_size)))
#define DB_FIND_INDEX_VEC(_str, _size)   (db_manager.findIndexVec(NULL, _str, &(_size)))
#define DB_FIND_REAL_VEC(_str, _size)    (db_manager.findRealVec(NULL, _str, &(_size)))
#define DB_FIND_DOUBLE_VEC(_str, _size)  (db_manager.findDoubleVec(NULL, _str, &(_size)))
#define DB_FIND_STRING(_str, _size)      (db_manager.findString(NULL, _str, &(_size)))
#define DB_FIND_POINTER(_str)            (db_manager.findPointer(NULL, _str))
#define DB_FIND_BYTE_VEC(_str, _size)    (db_manager.findByteVec(NULL, _str, &(_size)))
#define DB_FIND_SIZE_T_MAP(_str)         (db_manager.findSizeTMap(NULL, _str))

/* set macros */
#define DB_SET_BOOLEAN(_str, _val)                (db_manager.setBoolean(NULL, _str, _val))
#define DB_SET_REAL(_str, _val)                   (db_manager.setReal(NULL, _str, _val))
#define DB_SET_DOUBLE(_str, _val)                 (db_manager.setDouble(NULL, _str, _val))
#define DB_SET_INT(_str, _val)                    (db_manager.setInt(NULL, _str, _val))
#define DB_SET_INDEX(_str, _val)                  (db_manager.setIndex(NULL, _str, _val))
#define DB_SET_INT_VEC(_str, _size, _val)         (db_manager.setIntVec(NULL, _str, _size, _val))
#define DB_SET_INDEX_VEC(_str, _size, _val)       (db_manager.setIndexVec(NULL, _str, _size, _val))
#define DB_SET_REAL_VEC(_str, _size, _val)        (db_manager.setRealVec(NULL, _str, _size, _val))
#define DB_SET_DOUBLE_VEC(_str, _size, _val)      (db_manager.setDoubleVec(NULL, _str, _size, _val))
#define DB_SET_STRING(_str, _val)                 (db_manager.setString(NULL, _str, _val))
#define DB_SET_POINTER(_str, _val)                (db_manager.setPointer(NULL, _str, _val))
#define DB_SET_BYTE_VEC(_str, _val)               (db_manager.setByteVec(NULL, _str, _val))

/* map set macros */
#define DB_SET_SIZE_T_MAP_VALUE(v, first, second) (db_manager.setSizeTMapValue(v, first, second))
#define DB_FIND_SIZE_T_MAP_KEY(v, first)          (db_manager.findSizeTMapKey(v, first))
#define DB_GET_SIZE_T_MAP_VALUE(v, first)         (db_manager.getSizeTMapValue(v, first))

/* info get macros */
#define DB_GET_SIZE(_str)                         (db_manager.getSize(NULL, _str))
#define DB_GET_UNIT_SIZE(_str)                    (db_manager.getUnitSize(NULL, _str))
#define DB_GET_TYPE(_str)                         (db_manager.getType(NULL, _str))
#define DB_GET_TYPE_NAME(_str)                    (db_manager.getTypeName(NULL, _str))

/* pass in the address of the data, if string, just the string address */
#define DB_APPEND_INT(_str, _data)                (db_manager.appendInt(NULL, _str, _data))
#define DB_APPEND_INDEX(_str, _data)              (db_manager.appendIndex(NULL, _str, _data))
#define DB_APPEND_REAL(_str, _data)               (db_manager.appendReal(NULL, _str, _data))
#define DB_APPEND_DOUBLE(_str, _data)             (db_manager.appendDouble(NULL, _str, _data))
#define DB_APPEND_STRING(_str, _data)             (db_manager.appendString(NULL, _str, _data))

#define DB_REMOVE(_str)   (db_manager.remove(NULL, _str))
#define DB_TEST           (db_manager.test(NULL))
#define DB_PRINT          (db_manager.print(NULL))
#define DB_PRINTBRIEF     (db_manager.printBrief(NULL))
#define DB_FOOTPRINT      (db_manager.footprint(NULL))

/* MACROS FOR A GIVEN REFERENCE FOR A TEMPORARY DATA BASE MANAGER CLASS */
/* get macros to allocate and return the container */
#define DB_LOCAL_NEW_CLASS(_dbref)                         (db_manager.newClass(_dbref))
#define DB_LOCAL_DELETE_CLASS(_dbref)                      (db_manager.deleteClass(_dbref))

#define DB_LOCAL_GET_BOOLEAN(_dbref, _str)                 (db_manager.getBoolean(_dbref, _str))
#define DB_LOCAL_GET_REAL(_dbref, _str)                    (db_manager.getReal(_dbref, _str))
#define DB_LOCAL_GET_DOUBLE(_dbref, _str)                  (db_manager.getDouble(_dbref, _str))
#define DB_LOCAL_GET_INT(_dbref, _str)                     (db_manager.getInt(_dbref, _str))
#define DB_LOCAL_GET_INDEX(_dbref, _str)                   (db_manager.getIndex(_dbref, _str))
#define DB_LOCAL_GET_INT_VEC(_dbref, _str, _size)          (db_manager.getIntVec(_dbref, _str, _size))
#define DB_LOCAL_GET_INTDEX_VEC(_dbref, _str, _size)       (db_manager.getIndexVec(_dbref, _str, _size))
#define DB_LOCAL_GET_REAL_VEC(_dbref, _str, _size)         (db_manager.getRealVec(_dbref, _str, _size))
#define DB_LOCAL_GET_DOUBLE_VEC(_dbref, _str, _size)       (db_manager.getDoubleVec(_dbref, _str, _size))
#define DB_LOCAL_GET_STRING(_dbref, _str, _size)           (db_manager.getString(_dbref, _str, _size))
#define DB_LOCAL_GET_POINTER(_dbref, _str)                 (db_manager.getPointer(_dbref, _str))
#define DB_LOCAL_GET_BYTE_VEC(_dbref, _str, _size)         (db_manager.getByteVec(_dbref, _str, _size))
#define DB_LOCAL_GET_SIZE_T_MAP(_dbref, _str)              (db_manager.getSizeTMap(_dbref, _str))

/* find macros to allocate and return the container */
#define DB_LOCAL_FIND_BOOLEAN(_dbref, _str)                (db_manager.findBoolean(_dbref, _str))
#define DB_LOCAL_FIND_REAL(_dbref, _str)                   (db_manager.findReal(_dbref, _str))
#define DB_LOCAL_FIND_DOUBLE(_dbref, _str)                 (db_manager.findDouble(_dbref, _str))
#define DB_LOCAL_FIND_INT(_dbref, _str)                    (db_manager.findInt(_dbref, _str))
#define DB_LOCAL_FIND_INDEX(_dbref, _str)                  (db_manager.findIndex(_dbref, _str))
#define DB_LOCAL_FIND_INT_VEC(_dbref, _str, _size)         (db_manager.findIntVec(_dbref, _str, &(_size)))
#define DB_LOCAL_FIND_INTDEX_VEC(_dbref, _str, _size)      (db_manager.findIndexVec(_dbref, _str, &(_size)))
#define DB_LOCAL_FIND_REAL_VEC(_dbref, _str, _size)        (db_manager.findRealVec(_dbref, _str, &(_size)))
#define DB_LOCAL_FIND_DOUBLE_VEC(_dbref, _str, _size)      (db_manager.findDoubleVec(_dbref, _str, &(_size)))
#define DB_LOCAL_FIND_STRING(_dbref, _str, _size)          (db_manager.findString(_dbref, _str, &(_size)))
#define DB_LOCAL_FIND_POINTER(_dbref, _str)                (db_manager.findPointer(_dbref, _str))
#define DB_LOCAL_FIND_BYTE_VEC(_dbref, _str, _size)        (db_manager.findByteVec(_dbref, _str, &(_size)))
#define DB_LOCAL_FIND_SIZE_T_MAP(_dbref, _str)             (db_manager.findSizeTMap(_dbref, _str))

/* set macros */
#define DB_LOCAL_SET_BOOLEAN(_dbref, _str, _val)           (db_manager.setBoolean(_dbref, _str, _val))
#define DB_LOCAL_SET_REAL(_dbref, _str, _val)              (db_manager.setReal(_dbref, _str, _val))
#define DB_LOCAL_SET_DOUBLE(_dbref, _str, _val)            (db_manager.setDouble(_dbref, _str, _val))
#define DB_LOCAL_SET_INT(_dbref, _str, _val)               (db_manager.setInt(_dbref, _str, _val))
#define DB_LOCAL_SET_INDEX(_dbref, _str, _val)             (db_manager.setIndex(_dbref, _str, _val))
#define DB_LOCAL_SET_INT_VEC(_dbref, _str, _size, _val)    (db_manager.setIntVec(_dbref, _str, _size, _val))
#define DB_LOCAL_SET_INDEX_VEC(_dbref, _str, _size, _val)  (db_manager.setIndexVec(_dbref, _str, _size, _val))
#define DB_LOCAL_SET_REAL_VEC(_dbref, _str, _size, _val)   (db_manager.setRealVec(_dbref, _str, _size, _val))
#define DB_LOCAL_SET_DOUBLE_VEC(_dbref, _str, _size, _val) (db_manager.setDoubleVec(_dbref, _str, _size, _val))
#define DB_LOCAL_SET_STRING(_dbref, _str, _val)            (db_manager.setString(_dbref, _str, _val))
#define DB_LOCAL_SET_POINTER(_dbref, _str, _val)           (db_manager.setPointer(_dbref, _str, _val))
#define DB_LOCAL_SET_BYTE_VEC(_dbref, _str, _val)          (db_manager.setByteVec(_dbref, _str, _val))

/* info get macros */
#define DB_LOCAL_GET_SIZE(_dbref, _str)                    (db_manager.getSize(_dbref, _str))
#define DB_LOCAL_GET_UNIT_SIZE(_dbref, _str)               (db_manager.getUnitSize(_dbref, _str))
#define DB_LOCAL_GET_TYPE(_dbref, _str)                    (db_manager.getType(_dbref, _str))
#define DB_LOCAL_GET_TYPE_NAME(_dbref, _str)               (db_manager.getTypeName(_dbref, _str))

/* pass in the address of the data, if string, just the string address */
#define DB_LOCAL_APPEND_DATA(_str, _data)                  (db_manager.appendData(_dbref, _str, _data))

#define DB_LOCAL_REMOVE(_dbref, _str)                      (db_manager.remove(_dbref, _str))
#define DB_LOCAL_TEST(_dbref)                              (db_manager.test(_dbref))
#define DB_LOCAL_PRINT(_dbref)                             (db_manager.print(_dbref))
#define DB_LOCAL_PRINTBRIEF(_dbref)                        (db_manager.printBrief(_dbref))
#define DB_LOCAL_FOOTPRINT(_dbref)                         (db_manager.footprint(_dbref))

#endif /* FLUENT_DB_MANAGER */
