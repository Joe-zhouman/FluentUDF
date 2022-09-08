/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_STOREIF_H
#define _FLUENT_STOREIF_H

#include "dll.h"
#include "mem.h"
#include "storage.h"
#include "store.h"

struct tuple_struct
{
  int n;
  unsigned char flags;

  struct objp_struct *list;

  struct tuple_struct *next;
  struct tuple_struct **prev;
  struct domain_struct *domain;
};
typedef struct tuple_struct Tuple;

/* Tuple flags */
#define TUPLE_FLAGS(t) ((t)->flags)
#define SET_TUPLE_FLAGS(t,flag) (TUPLE_FLAGS(t) |= (flag))
#define CLEAR_TUPLE_FLAGS(t,flag) (TUPLE_FLAGS(t) &= ~(flag))

#define TUPLE_FL_MARK (1)

#define SET_TUPLE_MARK(t) SET_TUPLE_FLAGS(t,TUPLE_FL_MARK)
#define CLEAR_TUPLE_MARK(t) CLEAR_TUPLE_FLAGS(t,TUPLE_FL_MARK)
#define TUPLE_MARK_P(t) (TUPLE_FLAGS(t) & TUPLE_FL_MARK)

#define SET_STORE_TUPLE(s,tuple) ST_STORE_LINK(s) = (void *)tuple
#define STORE_TUPLE(s) ((Tuple *)ST_STORE_LINK(s))
#define STORE_FIRST_THREAD(s) (STORE_TUPLE(s)->list->as.t)
#define STORE_THREAD_ID(s) THREAD_ID(STORE_TUPLE(s)->list->as.t)

FLUENT_EXPORT void Free_And_Delete_All_Tuples(Domain *);
FLUENT_EXPORT Thread *Lookup_Thread_By_Store(Domain *, Store *);
FLUENT_EXPORT Store *Create_Store(size_t, size_t *, Thread *, Var_Attribute *, int, Domain *);
FLUENT_EXPORT Store *Resize_Store(Store *, size_t, size_t *, Thread *, Var_Attribute *, int, Domain *);
FLUENT_EXPORT void Share_Store(Store *, Thread *);
FLUENT_EXPORT void Remove_Store(Store *, Thread *);
FLUENT_EXPORT void Garbage_Collect_Tuples(Domain *);
FLUENT_EXPORT void Display_Tuples(Domain *);
FLUENT_EXPORT Tuple *First_Tuple(Domain *);
FLUENT_EXPORT void Collect_Threads_By_ID(Domain *, int, Objp **);
FLUENT_EXPORT void Resize_Thread_Storage(Thread *, const int);
FLUENT_EXPORT void Reorder_Stores(Domain *);

#endif /* _FLUENT_STOREIF_H */
