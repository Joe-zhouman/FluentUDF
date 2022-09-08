/*
 *  * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 *   */

#ifndef _FLUENT_PERFORATED_H
#define _FLUENT_PERFORATED_H
#include "dll.h"
#include "typedefs.h"
#include "mem.h"
#include "materials.h"

#define IINFO_LEN 10
#define RINFO_LEN 800
#define PROLFILE_CD_LEN 11
#define MAX_SPECIES MAX_PDF_SPECIES

typedef enum
{
  DIA_DC = 0,
  LEN_DC,
  AREA_DC,
  PRESS_INJ_DC,
  PRESS_EXT_DC,
  TEMP_DC,
  DEN_DC,
  XVEL_DC,
  YVEL_DC,
  ZVEL_DC
}CD_PROFILE_UDF;

typedef enum
{
  Un_Homo_Static,
  Un_Inhomo_Static,
  Cou_Homo_Static,
  Cou_Homo_Dynamic,
  Cou_Inhomo_Static,
  Cou_Inhomo_Dynamic
} Perforated_model_index;

typedef enum
{
  CD_index = 0,
  Direc_index = 1,
  Angle_index = 4,
  POINT1_index = 7,
  POINT2_index = 10,
  DIAM_index = 13,
  MF_index = 14,
  LENGTH_INDEX = 15,
  CENTER_INDEX = 16,
  TEM_INDEX = 19,
  MFRACTION_INDEX = 20,
  MFRACTION2_INDEX = 21,
  PV_INDEX = 22,
  SPE_INDEX = 23,
  SPE_LAST_INDEX = SPE_INDEX - 1 + MAX_SPECIES
} RInfo_index;

typedef enum
{
  Exttype_index = 0,
  InjDire_index = 1, /*ipfinfo[InjDire_index]=0: normal; =1: angel; =2: cylinder axis*/
  Injtype_index = 2,
  Cdtype_index  = 3  /*ipfinfo[Cdtype_index]=0: cd; =1: acd*/
} IInfo_index;

/*Perforated Face Group*/
typedef struct perforated_face_group_struct
{
    int nface;
    face_t *face;
    real (*dv)[ND_ND];
    real mf;
    real mf_new;
    real area;
    real pressure;
    real temperature;
    real gamma;
    real gas_constant;
    real rho;
    real vel[ND_ND];
    real scale;
    real (*source)[MAX_EQNS];
    real static_inj[MAX_EQNS];
    int ipfinfo[IINFO_LEN];
    real rpfinfo[RINFO_LEN];
} Perforated_Face;

/*Perforated Data Type*/
typedef struct perforated_data_struct
{
    cxboolean model_is_valid;
    Thread *inj_thread;
    int ninj;
    Perforated_Face *inj;

    cxboolean coupled;  /*true: coupled; false: uncoupled*/
    cxboolean homo;  /*true: homogeneous; false: inhomogeneous*/
    cxboolean dynamic;  /*true: dynamic; false: static*/
    Perforated_model_index model;

    Thread *ext_thread;
    int next;
    Perforated_Face *ext;
    int ext_type; /*0: distributed; 1: discrete*/
    int formulation_type; /*0: incompressible; 1: compressible*/
    int cd_type; /*0: constant cd; 1: use profile*/

    int *inj2ext_pair;  /*Only need this pairing info when (ninj>1 && next>1)*/
} Perforated_Data;

/*Perforated Data*/
extern FLUENT_EXPORT int n_perforated_thread;

/*Perforated Functions*/
FLUENT_EXPORT void perforated_model_update(Domain *);
FLUENT_EXPORT void perforated_model_free_storage(Domain *);
FLUENT_EXPORT void perforated_calculate(Domain *);
FLUENT_EXPORT void perforated_source(Domain *, int eqn, Svar sv_v, Svar sv_ap, Svar sv_source);
FLUENT_EXPORT void perforated_source_dynamic(Domain *, int eqn, Svar sv_v, Svar sv_ap, Svar sv_source, int ii);
FLUENT_EXPORT void perforated_source_static(Domain *, int eqn, Svar sv_v, Svar sv_ap, Svar sv_source, int ii);
FLUENT_EXPORT void perforated_integral_flux(Thread *, real *, int compute);

FLUENT_EXPORT void Peforated_Tagged_Hole(Domain *);
FLUENT_EXPORT void facePeforated_Tagged_Hole(Thread *, int, Svar);
FLUENT_EXPORT void Peforated_Pressure(Domain *);
FLUENT_EXPORT void facePeforated_Pressure(Thread *, int, Svar);
FLUENT_EXPORT void Peforated_Mass_Flow_Rate(Domain *);
FLUENT_EXPORT void facePeforated_mass_flow_rate(Thread *, int, Svar);

#endif
