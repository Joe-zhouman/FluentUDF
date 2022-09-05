/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_REMESH_BND_H
#define _FLUENT_REMESH_BND_H

#if RP_3D
FLUENT_EXPORT cxboolean Mark_Remesh_Prism_Regions (Domain *, cxboolean *);
FLUENT_EXPORT void Remesh_Prism_Regions (Domain *);

# if PARALLEL
FLUENT_EXPORT cxboolean Mark_Migration_Extruded_Columns_Encapsulation (Domain *, Objp *, cxboolean);
# endif

FLUENT_EXPORT real Max_Allowed_Face_Skewness_On_Thread (Thread *);
FLUENT_EXPORT real Evaluate_Prism_Face_Cavity_Marking (cell_t, Thread *);
FLUENT_EXPORT void Smooth_Extruded_Regions (Domain *);

#endif /* RP_3D */
#endif /* _FLUENT_REMESH_BND_H */
