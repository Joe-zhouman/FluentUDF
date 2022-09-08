/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_AMG_CROSS_H
#define _FLUENT_AMG_CROSS_H

#if RP_NODE
#include "amg.h"

FLUENT_EXPORT extern void pre_group_cross(Level *f, int **iset, int **part);
FLUENT_EXPORT extern void post_group_cross(Level *f);
FLUENT_EXPORT extern int *Get_Cross_Part(Level *f, int **part, int *size);
FLUENT_EXPORT extern void Restrict_AMG_Overlap_Tables_Cross(Level *f, Level *c,
                                                            AMG_Methods *amg_methods);
FLUENT_EXPORT extern void update_fine_matrix_memory(Level *fine);

#endif /* RP_NODE */

#define AMG_USE_ROW(part, i) (!(part) || (part)[i] == myid)

#endif /* _FLUENT_AMG_CROSS_H */
