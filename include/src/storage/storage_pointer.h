/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_STORAGE_POINTER_H
#define _FLUENT_STORAGE_POINTER_H

typedef enum
{
  SV_STATE_FREE = 0,
  SV_STATE_IN_USE,
  SV_STATE_BLOCKED
} SV_Usage_State;

typedef enum
{
  SV_STATE_UNALLOCATED = 0,
  SV_STATE_ALLOCATED
} SV_Alloc_State;

typedef struct
{
  real *storage;
  Svar nv;
  cxboolean force_allocate;
  cxboolean need_free;
  SV_Usage_State usage_state;
  SV_Alloc_State alloc_state;
} Storage_Pointer;

#define GET_STORAGE_POINTER(_sp,_t,_nv) \
  real *_sp;\
  Storage_Pointer _spo = {0};\
  _spo.nv = _nv;\
  Get_Storage_Pointers(_t,&(_spo),NULL);\
  _sp = _spo.storage;

#define DISPOSE_STORAGE_POINTER(_sp,_t,_nv) \
  Dispose_Storage_Pointers(_t,&(_spo),NULL);


#if  ! UDF_COMPILER
#define __VA_NARGS__(...) __VA_NARGS_IMPL__(__VA_ARGS__, 5,4,3,2,1)
#define __VA_NARGS_IMPL__(_1,_2,_3,_4,_5,N,...) N
#define TEST_DECLARATION(...) \
  const int _nargs = __VA_NARGS__(__VA_ARGS__);\
  Storage_Pointer _spo2[__VA_NARGS__(__VA_ARGS__)];\
  CX_Message("\nNARGS = %d\n", _nargs);
#endif

#if 00
#define GET_STORAGE_POINTER2(_t,__VA_ARGS__) \
  real *_sp;\
  Storage_Pointer[__VA_NARGS__(__VA_ARGS__)] _spo = {0};\
  Get_Storage_Pointers2(_t,&(_spo),__VA_NARGS__(__VA_ARGS__));

#define DISPOSE_STORAGE_POINTER2(_t,__VA_ARGS__) \
  Dispose_Storage_Pointers2(_t,&(_spo),__VA_NARGS__(__VA_ARGS__));
#endif

FLUENT_EXPORT void SV_Set_State(Svar nv, Thread *t, SV_Usage_State state);
FLUENT_EXPORT SV_Usage_State SV_Get_State(Svar nv, Thread *t);
FLUENT_EXPORT int SV_Get_Nrefs(Svar nv, Thread *t);
FLUENT_EXPORT real *SP_Get_Storage(Storage_Pointer *sp);
FLUENT_EXPORT void SP_Set_Force_Allocate(Storage_Pointer *sp, cxboolean force);
FLUENT_EXPORT void Get_Storage_Pointers(Thread *thread, ...);
FLUENT_EXPORT void Dispose_Storage_Pointers(Thread *thread, ...);

FLUENT_EXPORT void UTest_Thread_Correct_C_Velocity(Thread *t);
FLUENT_EXPORT void UTest_Correct_C_Velocity(void);

#endif /*_FLUENT_STORAGE_POINTER_H*/
