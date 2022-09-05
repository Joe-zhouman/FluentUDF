/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_ARRAYS_H
#define _FLUENT_ARRAYS_H

#include "dll.h"
#include "global.h"

FLUENT_EXPORT char *create_array(size_t size, char *file, int line);
FLUENT_EXPORT char *realloc_array(char *old, size_t size, char *file, int line);
FLUENT_EXPORT void return_array(char *array, char *file, int line);
FLUENT_EXPORT size_t sizeof_array(char *array);
FLUENT_EXPORT void array_stats(void);
FLUENT_EXPORT size_t array_memory_used(void);
FLUENT_EXPORT size_t array_memory_allocated(void);
FLUENT_EXPORT void free_all_arrays(void);
FLUENT_EXPORT void free_unused_arrays(void);

FLUENT_EXPORT char *array1(int, int, size_t, char *, int);
FLUENT_EXPORT char **array2(int, int, int, int, size_t, char *, int);
FLUENT_EXPORT char ***array3(int, int, int, int, int, int, size_t, char *, int);
FLUENT_EXPORT char ****array4(int, int, int, int, int, int, int, int, size_t, char *, int);
FLUENT_EXPORT char *****array5(int, int, int, int, int, int, int, int, int, int, size_t, char *, int);
FLUENT_EXPORT void free1(char *, int, size_t, char *, int);
FLUENT_EXPORT void free2(char **, int, int, size_t, char *, int);
FLUENT_EXPORT void free3(char ***, int, int, int, size_t, char *, int);
FLUENT_EXPORT void free4(char ****, int, int, int, int, size_t, char *, int);
FLUENT_EXPORT void free5(char *****, int, int, int, int, int, size_t, char *, int);

#define NEW_ARRAY(size) create_array(size,__FILE__,__LINE__)
#define REALLOC_ARRAY(old,size) realloc_array(old,size,__FILE__,__LINE__)
#define FREE_ARRAY(a) return_array(a,__FILE__,__LINE__)

#define NEW_ARRAY_1(il,ih,size) \
  array1(il,ih,size,__FILE__,__LINE__)
#define NEW_ARRAY_2(il,ih,jl,jh,size) \
  array2(il,ih,jl,jh,size,__FILE__,__LINE__)
#define NEW_ARRAY_3(il,ih,jl,jh,kl,kh,size) \
  array3(il,ih,jl,jh,kl,kh,size,__FILE__,__LINE__)
#define NEW_ARRAY_4(il,ih,jl,jh,kl,kh,ll,lh,size) \
  array4(il,ih,jl,jh,kl,kh,ll,lh,size,__FILE__,__LINE__)
#define NEW_ARRAY_5(il,ih,jl,jh,kl,kh,ll,lh,ml,mh,size) \
  array5(il,ih,jl,jh,kl,kh,ll,lh,ml,mh,size,__FILE__,__LINE__)

#define FREE_ARRAY_1(p,il,ih,size) \
  free1((char *)(p),il,size,__FILE__,__LINE__)
#define FREE_ARRAY_2(p,il,ih,jl,jh,size) \
  free2((char **)(p),il,jl,size,__FILE__,__LINE__)
#define FREE_ARRAY_3(p,il,ih,jl,jh,kl,kh,size) \
  free3((char ***)(p),il,jl,kl,size,__FILE__,__LINE__)
#define FREE_ARRAY_4(p,il,ih,jl,jh,kl,kh,ll,lh,size) \
  free4((char ****)(p),il,jl,kl,ll,size,__FILE__,__LINE__)
#define FREE_ARRAY_5(p,il,ih,jl,jh,kl,kh,ll,lh,ml,mh,size) \
  free5((char *****)(p),il,jl,kl,ll,ml,size,__FILE__,__LINE__)

#if USE_OFFSET_MALLOC
void *offset_malloc(size_t size, char *file, int line);
void *offset_realloc(void *p, size_t size, char *file, int line);
void *offset_calloc(size_t num, size_t size, char *file, int line);
void offset_free(void *p, char *file, int line);
#elif !IN_ARRAYS_C
#define offset_malloc CX_Malloc_MU
#define offset_realloc CX_Realloc_MU
#define offset_calloc CX_Calloc_MU
#define offset_free CX_Free_MU
#endif /* USE_OFFSET_MALLOC */

#ifndef USE_NUMA_ALLOC
#  ifdef ALLOW_NUMA_ALLOC
#    define USE_NUMA_ALLOC 1
#  else
#    define USE_NUMA_ALLOC 0
#  endif
#endif

#if USE_NUMA_ALLOC
FLUENT_EXPORT int Check_Numa_Alloc(void);
FLUENT_EXPORT void Enable_Numa_Alloc(const char *numa_lib_path);
FLUENT_EXPORT void Disable_Numa_Alloc(void);
#endif /* USE_NUMA_ALLOC */

#endif /* _FLUENT_ARRAYS_H */
