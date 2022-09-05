/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _NCI_H
#define _NCI_H

#if PARALLEL
FLUENT_EXPORT cxboolean Optimize_NCI_Intersections_P(Domain *);
FLUENT_EXPORT void Update_NCI_Intersections(Domain *);
FLUENT_EXPORT void Clear_Leftover_Wall_If_Needed(Domain *);
FLUENT_EXPORT void Calc_Sided_Area_Vector_Fraction(Domain *);
FLUENT_EXPORT void Register_NCI_Node_Coords_HDF_IO_Manager(void);
FLUENT_EXPORT cxboolean NCI_With_Node_Coords_P(void);
FLUENT_EXPORT void Free_NCI_Node_Coords(Domain *);
FLUENT_EXPORT void Refill_NCI_Node_Coords(Domain *);
FLUENT_EXPORT void Free_Mem_Manager_For_Node_Coords(void);
# if RP_NODE
FLUENT_EXPORT void Use_Cached_NCI_Neighborhood(Domain *);
FLUENT_EXPORT void Free_NCI_Neighborhood_Cache(Domain *);
FLUENT_EXPORT void Update_NCI_Grid_Node_Id(void);
FLUENT_EXPORT cxboolean NCI_Node_Changed_P(void);
# endif
#endif /* PARALLEL */

FLUENT_EXPORT int clip_poly(int w_size, real w[][ND_ND],
                            int *c_size, real c[][ND_ND], real small_vp);
#endif /* _NCI_H   */

