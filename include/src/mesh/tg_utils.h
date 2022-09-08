/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef TG_UTILS_H
#define TG_UTILS_H

#include "global.h"

#if TGRID
Domain *Get_Mesh_From_TGrid(Domain *domain, cxboolean dumps_p, cxboolean free_tgrid);
void Send_Mesh_To_TGrid(Domain *domain);
void Reset_Mesh_To_TGrid(Domain *domain);
void Build_Mesh_For_TGrid(Domain *domain);
#endif

#endif
