/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/

#ifndef _FLUENT_CDAT_H
#define _FLUENT_CDAT_H

#ifdef __cplusplus
extern "C" {
#endif

FLUENT_EXPORT void Write_Surface_CDAT_Data(Domain *domain, FILE *filename, Pointer surfaces, const char *variable, cxboolean binary, int nScalars);
FLUENT_EXPORT void Write_Surface_CDAT_Mesh(Domain *domain,
#if !RP_NODE
                                           FILE *fp,
#endif
                                           Pointer surfaces, cxboolean binary);
FLUENT_EXPORT void Write_Surface_CDAT_Fluxes(Domain *domain, FILE *fp, Pointer surfaces, cxboolean binary, int nScalars);
FLUENT_EXPORT void Fill_Data_On_Internal_Flow_Zones(Domain *);

#ifdef __cplusplus
}
#endif

#endif
