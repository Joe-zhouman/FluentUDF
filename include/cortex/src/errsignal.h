/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _CX_ERRSIGNAL_H
#define _CX_ERRSIGNAL_H

/*---------------------------------------------------------------------------*/

#include <setjmp.h>

/*---------------------------------------------------------------------------*/

#if __alpha
# if vms
typedef __int64 *jmp_buf_ptr; /* for passing around pointers to jmp_bufs */
# else
typedef long *jmp_buf_ptr; /* for passing around pointers to jmp_bufs */
# endif
#elif defined _MIPS_ISA && ( _MIPS_ISA == _MIPS_ISA_MIPS3 || _MIPS_ISA == _MIPS_ISA_MIPS4 )
typedef __uint64_t *jmp_buf_ptr;
#elif _hiux
typedef long *jmp_buf_ptr; /* for passing around pointers to jmp_bufs */
#elif  _aix51_64
typedef long *jmp_buf_ptr; /* for passing around pointers to jmp_bufs */
#else
typedef int *jmp_buf_ptr; /* for passing around pointers to jmp_bufs */
#endif

/*---------------------------------------------------------------------------*/

/*
 * For cxboolean...
 */
#include "cx.h"

/*---------------------------------------------------------------------------*/

#if ! CX_NODE

/* Signal handling options */
extern cxboolean handleFPE; /* Trap floating point errors */
extern cxboolean handleAbort; /* Trap programming errors */
extern int errjmp_ok;
#endif

/*---------------------------------------------------------------------------*/

extern int
CX_Signal_handlers_old(
  cxboolean handleFPE,
  cxboolean handleAbort
);

/*---------------------------------------------------------------------------*/

/*
 * This is the Error() function called by the user to report errors.
 * This is a simple variant of CX_Primitive_Error...
 * All that the processes do is print the error message and siglongjmp...
 */
extern void
CX_Primitive_Error2(
  const char *format, ...
);

/*---------------------------------------------------------------------------*/

extern int
CX_Signal_handlers(
  int oldHandlers
);

/*---------------------------------------------------------------------------*/

#endif /* _CX_ERRSIGNAL_H */

