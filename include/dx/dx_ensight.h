/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_MPGS_H
#define _FLUENT_MPGS_H

#include "dll.h"

#if SEEM

#define VALID_FACE(ft) (((THREAD_TYPE(ft)!=THREAD_F_INTERIOR)&&(!SHELL_FACE_THREAD_P(ft)) && ((LENGTH_FACE(ft))!=0)&&\
                         (!SLIDING_INTERFACE_THREAD_P(ft))&&(!SHADOW_FACE_THREAD_P(ft)))\
                        ||(SHADOW_FACE_THREAD_P(ft)&&(MAJOR_FACE_THREAD_P(ft))))

#define VALID_EMPTY_FACE(ft) (((THREAD_TYPE(ft)!=THREAD_F_INTERIOR)&&(!SHELL_FACE_THREAD_P(ft)) &&\
                         (!SLIDING_INTERFACE_THREAD_P(ft))&&(!SHADOW_FACE_THREAD_P(ft)))\
                        ||(SHADOW_FACE_THREAD_P(ft)&&(MAJOR_FACE_THREAD_P(ft))))

#define VALID_INTERIOR_FACE(ft) (((THREAD_TYPE(ft)==THREAD_F_INTERIOR)&&(!SHELL_FACE_THREAD_P(ft)) && ((LENGTH_FACE(ft))!=0)&&\
                         (!SLIDING_INTERFACE_THREAD_P(ft))&&(!SHADOW_FACE_THREAD_P(ft)))\
                        ||(SHADOW_FACE_THREAD_P(ft)&&(MAJOR_FACE_THREAD_P(ft))))
#define VALID_PARTITION_FACE(face, ft) ((myid == (C_PART_ACTIVE(F_C0(face, ft), F_C0_THREAD(face, ft)))))

FLUENT_EXPORT void Write_Mpgs_Case(Domain *, FILE *, Pointer, cxboolean);
FLUENT_EXPORT void Write_Mpgs_Gold_Geo(Domain *, FILE *, Pointer, cxboolean, Pointer);
FLUENT_EXPORT void Write_Mpgs_Gold_Scalar(Domain *, FILE *, cxboolean, cxboolean, Pointer);
FLUENT_EXPORT void Write_Mpgs_Gold_Velocity(Domain *, FILE *, cxboolean, int, cxboolean, Pointer);
FLUENT_EXPORT void Write_Mpgs_Transient_Case(Domain *, FILE *, Pointer);
FLUENT_EXPORT void Write_Mpgs_Geo(Domain *, FILE *, Pointer );
FLUENT_EXPORT void Write_Mpgs_Velocity(Domain *, FILE *);
FLUENT_EXPORT void Write_Mpgs_Scalar(Domain *, FILE *);
FLUENT_EXPORT void Set_Ensight_Variable(const char *);

FLUENT_EXPORT void Write_EnGold_Surf_Geom( Domain *,
                                           int binary,
                                           const char *basename,
                                           const char *filename,
                                           Pointer surfaces,
                                           Pointer names);

FLUENT_EXPORT void Write_EnGold_Surf_Scalar(Domain *domain,
                                            int binary,
                                            const char *basename,
                                            const char *filename,
                                            Pointer surfaces,
                                            int nodeVal,
                                            int nScalars,
                                            const char *sclname,
                                            int isCff);

FLUENT_EXPORT void Initialize_EnGold_Surf_Parallel(Domain *domain,
                                                   int binary,
                                                   const char *filename,
                                                   Pointer surfaces,
                                                   Pointer scalars,
                                                   int nodeVal);

FLUENT_EXPORT void Write_EnGold_Surf_Vel ( Domain *domain,
                                           int binary,
                                           const char *basename,
                                           const char *filename,
                                           Pointer surfaces,
                                           int cellVal,
                                           int phaseId);

FLUENT_EXPORT void Write_EnGold_SOS_Case ( Domain *domain,
                                           const char *basename,
                                           const char *filename,
                                           int transient,
                                           int cellCentered,
                                           cxboolean isIsoSurf,
                                           Pointer scalars );

FLUENT_EXPORT void Write_EnGold_Geom( Domain *domain,
                                      int binary,
                                      int cellVal,
                                      const char *basename,
                                      const char *filename,
                                      Pointer zonelist,
                                      Pointer names);

FLUENT_EXPORT void Write_EnGold_Scalar( Domain *domain,
                                        int binary,
                                        const char *basename,
                                        const char *filename,
                                        Pointer cellzones,
                                        int nodeVal,
                                        int nscalar,
                                        const char *sclname,
                                        int isCff);

FLUENT_EXPORT void Write_EnGold_Velocity( Domain *domain,
                                          int binary,
                                          const char *basename,
                                          const char *filename,
                                          Pointer cellzones,
                                          int cellVal,
                                          int phaseId);

FLUENT_EXPORT void Set_DVS_Servers( const char *hostname,
                                    int hostBasePort,
                                    const char *cacheDir,
                                    int nodesPerSever,
                                    cxboolean autoExport,
                                    cxboolean startDVSServer);
/*------------------------------------------------
 * EnSight Surface Export Only
 *------------------------------------------------*/
FLUENT_EXPORT void DVS_Send_Surf_Geom( Domain *domain, 
                                       const char *filename,
                                       Pointer surfaces, 
                                       Pointer names,
                                       Pointer scalars,
                                       Pointer varDisplayNames,
                                       Pointer varDimensions,
                                       Pointer varLabels,
                                       cxboolean cellCentered,
                                       cxboolean autoExport,
                                       cxboolean beginInit);

FLUENT_EXPORT void DVS_Send_Surf_Scalar( Domain *domain,
                   		                 Pointer surfaces,
			                             cxboolean cellVal,
                                         int totalScalars,
			                             int nScalars,
			                             cxboolean isCff);
FLUENT_EXPORT void DVS_Send_Surf_Vel( Domain *domain,
  	                                  Pointer surfaces,
                                      int varIndex,
                                      cxboolean cellVal,
                                      int phaseId);
/*------------------------------------------------
 * EnSight Volumetric Export
 *------------------------------------------------*/
FLUENT_EXPORT void DVS_Send_Volm_Geom( Domain *domain,
                                       const char *filename,
                                       Pointer zonelist,
                                       Pointer names,
                                       Pointer scalars,
                                       Pointer varDisplayNames,
                                       Pointer varDimensions,
                                       Pointer varLabels,
                                       cxboolean cellCentered,
                                       int numResiduals,
                                       Pointer residualNames,
                                       Pointer residualVals,
                                       cxboolean autoExport,
                                       cxboolean beginInit);

FLUENT_EXPORT void DVS_Send_Volm_Scalar( Domain *domain,
                                         Pointer cellzones,
                                         cxboolean cellVal,
                                         int nscalar);

FLUENT_EXPORT void DVS_Send_Volm_Velocity( Domain *domain,
                                           Pointer cellzones,
                                           int varIndex,
                                           cxboolean cellVal,
                                           int phaseId);

FLUENT_EXPORT void DVS_Shutdown_Servers();
FLUENT_EXPORT void DVS_Clear_StoredIds();
FLUENT_EXPORT Pointer Convert_Fluent_to_EnSight_Unit(const char *in);

#endif /*SEEM. End of if*/

#endif /* _FLUENT_MPGS_H */
