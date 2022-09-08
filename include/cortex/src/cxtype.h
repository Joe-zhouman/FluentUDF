/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _CXTYPE_H
#define _CXTYPE_H

#if _NT
#if WIN64
typedef INT_PTR CXPtrAsInt;
#else
typedef int CXPtrAsInt;
#endif
#else
typedef long CXPtrAsInt;
#endif /*_NT*/

#endif /* CXTYPE_H */
