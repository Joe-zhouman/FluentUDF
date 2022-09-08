/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _CX_MPTFLUSH_H
#define _CX_MPTFLUSH_H

/*---------------------------------------------------------------------------*/

#define  CX_SIGNAL_NULL     -1
#define  CX_SIGNAL_INTERNAL -2

/*
 * For cxboolean, Get_myid...
 */
#include "cx.h"

/*---------------------------------------------------------------------------*/

/*
 * Prints backtrace using backtrace() on Unix/Linux...
 *                        StackWalker on Windows
 *
 * Not async-signal-safe...
 */
extern void
CX_Print_backtrace(
  const char *title
);

extern void
CX_Get_backtrace(
  size_t *size,
  char ***strings
);

/*---------------------------------------------------------------------------*/

/*
 * Only if this flag is set, we will call non async-signal-safe functions...
 */
extern cxboolean
CX_Signal_use_async_safe_flag(void);

/*---------------------------------------------------------------------------*/

/*
 * Verbosity of diagnostic information from signals, error handling()...
 */
extern int
CX_Signal_debug_verbosity(void);

#define CX_SIGNAL_DEBUG_VERBOSE ((CX_Signal_debug_verbosity() > 0) \
                                 && (CX_Signal_use_async_safe_flag()))

/*---------------------------------------------------------------------------*/

#if _NT

extern char *
CX_Signal_get_fluent_error_file_and_pre(
  char *file,
  char *pre
);

extern void
CX_Print_backtrace_atexit(
  const char *msg
);

#endif

/*---------------------------------------------------------------------------*/

/*
 * This function is used in 'seval.c' and hence had to be pulled out from
 * 'errsignal.h'
 */
extern void
CX_Cleanup_errors(void);

/*---------------------------------------------------------------------------*/

#endif /* _CX_MPTFLUSH_H */

