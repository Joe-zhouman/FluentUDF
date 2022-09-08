/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _CXM_H
#define _CXM_H

#define CX_Malloc(s) CX_Malloc_MU((s),__FILE__,__LINE__)
#define CX_Realloc(n,s) CX_Realloc_MU((n),(s),__FILE__,__LINE__)
#define CX_Calloc(n,s) CX_Calloc_MU((n),(s),__FILE__,__LINE__)
#define CX_Free(s) CX_Free_MU((s),__FILE__,__LINE__)

#define CX_Malloc_Unsafe(s) CX_Malloc_MU_Unsafe((s),__FILE__,__LINE__)

/* Searching for a memory leak, I want -- just temporarily --
 * to replace *all* occurrences of [vm]alloc/free etc. by
 * calls to temporary macros that go into CX_Free_MU etc.
 * so that really all memory allocation can be logged.
 * To do that, I run this over my work area...
 *
   sed -i -e 's#\([^:]\)\<\(\(\|vm\)\(\(m\|c\|re\)alloc\|free\)\)\( *(\)#\1\2tmp\6#g' \
           `greps -l '[^:]\<\(\|vm\)\(\(m\|c\|re\)alloc\|free\) *(' . | grep -v multiport`

   sed -i -e 's#\([^:]\)\<\(\(\|vm\)\(\(m\|c\|re\)alloc\|free\)\)tmp\( *(\)#\1\2\6#g' \
           `greps -l '[^:]\<\(\|vm\)\(\(m\|c\|re\)alloc\|free\)tmp *(' . | grep -v multiport`
 *
 * ...and activate the following.
 *
 * Then I run Fluent with "-trace" on the command line and do the suspicous calculation twice,
 * once a small number of iterations / time steps and once a somewhat larger number.
 * In each run, I use lines like...:
 *    (mtrace-start "s dti 5 12" 0)
 *    /solve/dual-time-iterate  5 12
 *    (mtrace-stop "s dti 5 12")
 *
 * Each run produces "mem-*" files, which can be run through
 * .../vNNN/fluent/fluent/devtools/run_purge_mtrace.x, and
 * comparing the resulting '*-uniq[_n]?' files should show
 * pretty obviously what causes the memory leak...
 *
 *
 *    A special catch, though...:
 *
 * At many places, Fluent source contains things like "strdup()", which call malloc() and
 * therefore require that the memory allocated by them be free()'d using nothing but free().
 * The above strategy, however, replaces every call to free() by freetmp()...
 * To avoid crashes by passing such a pointer (e.g. from strdup()) to CX_Free_MU(),
 * the macro TRACE_MORE_MEM controls code in cxclient.c and cxnodes.c that modifies
 * the behaviour: Every memory allocated through the wrappers is marked with a magic number,
 * and memory that does not have this magic number is released using pure free()...
 */

#if 00   /* cf. instructions above.. */

# define TRACE_MORE_MEM  11
# define TMMMAGIC ((size_t) 0xABCDEF9876543210)


# define      freetmp     CX_Free
# define    malloctmp   CX_Malloc
# define    calloctmp   CX_Calloc
# define   realloctmp  CX_Realloc

#ifdef __cplusplus
extern "C"
{
#endif

#include "stddef.h"

void     CX_Free_MU(void  *a,         const char *b, int c);
void  *CX_Malloc_MU(size_t a,         const char *b, int c);
void *CX_Realloc_MU(void  *a, size_t, const char *b, int c);
void  *CX_Calloc_MU(size_t a, size_t, const char *b, int c);

#ifdef __cplusplus
}
#endif

# define    vmfreetmp     CX_Free_MU
# define   vmalloctmp   CX_Malloc_MU
# define  vmcalloctmp   CX_Calloc_MU
# define vmrealloctmp  CX_Realloc_MU

#else

# define TRACE_MORE_MEM  00

#endif


/* The "true" calls into the OS to obtain and release memory,
 * never to be wrapped e.g. by the procedure described above:
 */
#define    vmfreetrue    vmfree
#define   vmalloctrue   vmalloc
#define  vmcalloctrue  vmcalloc
#define vmrealloctrue vmrealloc

#define      freetrue      free
#define    malloctrue    malloc
#define    calloctrue    calloc
#define   realloctrue   realloc


#endif /*_CXM_H*/

