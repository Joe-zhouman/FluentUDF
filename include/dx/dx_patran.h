/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DX_PATRAN_H
#define _FLUENT_DX_PATRAN_H

#include "dll.h"

#if SEEM

#define PNF_TITLE                     25
#define PNF_SUMMARY                   26
#define PNF_NODE                       1
#define PNF_ELEMENT                    2
#define PNF_DISTRIB_LOAD               6
#define PNF_NODE_FORCE                 7
#define PNF_NODE_TEMPERATURE          10
#define PNF_ELEMENT_TEMPERATURE       11
#define PNF_NODE_HEAT_FLUX            15
#define PNF_ELEMENT_HEAT_FLUX         16
#define PNF_FACE_CONVECTION           17  /* Used for radtherm export */
#define PNF_FACE_RADIATION            18  /* Used for radtherm export */
#define PNF_ELEMENT_FLOW_VELOCITY     97  /* Used for radtherm export */
#define PNF_NAMED                     21
#define PNF_END                       99
#if !PARALLEL
FLUENT_EXPORT void Write_Pnf_Domain(Domain *, FILE *, Pointer, Pointer, int);
FLUENT_EXPORT void Write_Pnf_Cell_Temperature(Domain *, Pointer, FILE *, Pointer);
# endif
FLUENT_EXPORT void Write_Radiation_Scalar(Domain *, Pointer, FILE *, Pointer,
                                          cxboolean, cxboolean);
FLUENT_EXPORT void Write_Pnf_Surfaces(Domain *, Pointer, Pointer, FILE *, Pointer, Pointer, int);
FLUENT_EXPORT void Write_Patran_Scalars(Domain *, Pointer, FILE *, Pointer);
FLUENT_EXPORT void Write_Patran_Template(Domain *, FILE *, Pointer);
#endif /*SEEM */

#endif /* _FLUENT_DX_PATRAN_H */
