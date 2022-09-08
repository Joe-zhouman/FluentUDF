/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _CX_STACK_TRACE_H
#define _CX_STACK_TRACE_H

#include "stdio.h"
#include "cxlocalize.h"

#if defined(__cplusplus)
extern "C"
{
#endif

void print_stack_trace(FILE *, int, int);

#if defined(__cplusplus)
}
#endif

#endif /* _CX_STACK_TRACE_H */
