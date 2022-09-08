/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/*....................................................*/
/*.........Atul Kumar Verma : Jan 2003 ..............*/
/*....................................................*/

#ifndef _FLUENT_SG_SOLAR_H
#define _FLUENT_SG_SOLAR_H

#include "dll.h"

#if RP_SOLAR

typedef enum
{
  SOLAR_INPUT_CONSTANT = 0,
  SOLAR_INPUT_CALCULATOR,
  SOLAR_INPUT_POLYNOMIAL,
  SOLAR_INPUT_UDF
} Solar_Input_type;

typedef struct sinput
{
  Solar_Input_type type;  /* constant, polynomial or udf */
  union
  {
    Polynomial *pl;
    real (*pudf)(real, real, real, int, int);
  } input;
  real xoutval;
} Sinput;

#define F_SOLAR_SOURCE(f,t)  F_STORAGE_R(f,t,SV_SOLAR_SOURCE)
#define F_SOLAR_BIN(f,t)  F_STORAGE_R(f,t,SV_SOLAR_BIN)
#define COPY_MAJOR_THREAD_PROPERTIES_P(t) ((THREAD_VAR(t).wall.thermal_bc == THERMAL_BC_COUPLED) && MINOR_FACE_THREAD_P(t) && SOLID_THREAD_P(THREAD_T1(t)))

FLUENT_EXPORT void Solar_Calc(cxboolean update_intensity, cxboolean update_direction);
FLUENT_EXPORT void Init_Solar_Flux(Domain *domain);
FLUENT_EXPORT void Init_Solar_Model(Pointer x, Pointer y);
FLUENT_EXPORT void DO_Update_Solar_Load(void);
#if RP_NODE
FLUENT_EXPORT void Exchange_Svar_Coupled_Wall_Face_Messages (Domain *, Svar);
FLUENT_EXPORT void Collect_Reals_For_Sending(Dom_Neighbor *, real *, Svar);
FLUENT_EXPORT void Apply_Reals_To_Svars(Dom_Neighbor *, real *, Svar);
#endif

#if !PARALLEL
FLUENT_EXPORT void Write_Solar_Source_Data(Domain *domain, FILE *fname, cxboolean binary);
#endif
FLUENT_EXPORT void Read_Solar_Source_Data(Domain *domain, FILE *fname);

#define SV_SOLAR_HLIST SV_CENTROID, SV_AREA

#define SV_SOLAR_NLIST \
    SV_SOLAR_SOURCE, SV_SOLAR_BIN, SV_SOLAR_QTRANS, SV_SOLAR_QABS, SV_SOLAR_QREFL

FLUENT_EXPORT void Finish_Solar_Load_Async(Domain *domain);
FLUENT_EXPORT int Solar_WIP(void);
FLUENT_EXPORT Domain *Solar_Domain(void);
FLUENT_EXPORT cxboolean Is_Solar_Domain_Present(void);

#endif /* RP_SOLAR */
#endif /* _FLUENT_SG_SOLAR_H */
