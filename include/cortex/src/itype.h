/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef __ITYPE_H__
#define __ITYPE_H__

#ifndef USE_INT64
#define USE_INT64 0 /* Contradicts the definition in fluent/src/main/config.h,
                     * so this (itype.h) must NOT be included BEFORE that (config.h)!
                     */
#endif

#define CXINT64_MAX 9223372036854775807
#define CXINT64_MIN (-9223372036854775807)   /* reduced by 1 for Windows Intel compiler warnings */
#define CXINT32_MAX 2147483647
#define CXINT32_MIN (-2147483648)

#if USE_INT64
#if _NT
typedef long long cxindex;
typedef unsigned long long cxindexU;
#else
typedef long cxindex;
typedef unsigned long cxindexU;
#endif
#define CXINDEX_MAX CXINT64_MAX
#define CXINDEX_MIN CXINT64_MIN
#else
typedef int cxindex;
typedef unsigned int cxindexU;
#define CXINDEX_MAX CXINT32_MAX
#define CXINDEX_MIN CXINT32_MIN
#endif

#endif

