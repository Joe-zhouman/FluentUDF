/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_CGNS_IMP_H
#define _FLUENT_CGNS_IMP_H

#include "dll.h"

#if SEEM
#if !RP_NODE
FLUENT_EXPORT void filter_cgns_data(Domain *, const char *, int *, int );
#else
FLUENT_EXPORT void filter_cgns_data(Domain *, int *, int );
#endif
#if !PARALLEL
void Write_Cgns_Domain(const char *filename, Domain *, Pointer, Pointer, cxboolean);
#endif
#endif /*SEEM*/

#endif /* _FLUENT_CGNS_IMP_H */
