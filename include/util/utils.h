/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_UTILS_H
#define _FLUENT_UTILS_H

#include "seem.h"

FLUENT_EXPORT Pointer lprintquadchecksums(Pointer d, Pointer w);
FLUENT_EXPORT void print_quad_check_sums(Domain *domain, const char *when,
                                         cxboolean weight_by_partition_p,
                                         cxboolean weight_by_cell_id_p,
                                         cxboolean do_average_p,
                                         cxboolean do_all_p);

#endif /* _FLUENT_UTILS_H */

