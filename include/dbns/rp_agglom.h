/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_RP_AGGLOM_H
#define _FLUENT_RP_AGGLOM_H

#include "dll.h"

FLUENT_EXPORT void Create_Coarse_Grid_Levels(Domain *, int);
FLUENT_EXPORT void Reset_Coarsen_Flags(void);
FLUENT_EXPORT void Delete_Grid_Level(Domain *, int n);
FLUENT_EXPORT void Delete_Coarse_Levels(Domain *);
FLUENT_EXPORT void Agglomerate_Fine_Domain(Domain *, int, cxboolean);
FLUENT_EXPORT void Update_Masked_Cells(Domain *, unsigned int, unsigned int);
FLUENT_EXPORT void Update_Coarse_Mesh(Domain *, int);
FLUENT_EXPORT cxboolean Agglomeration_Need_Update(cxboolean);

#define C_COARSE_CELL(c,t)C_STORAGE(c,t,SV_COARSE_CELL,cell_t *)
#define F_COARSE_FACE(f,t)F_STORAGE(f,t,SV_COARSE_FACE,face_t *)
#define F_FINE_FACE(f,t)F_STORAGE(f,t,SV_FINE_FACE,face_t *)

extern cxboolean in_agg_on_demand;

#endif /* _FLUENT_RP_AGGLOM_H */
