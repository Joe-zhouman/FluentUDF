/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SG_DTRM_H
#define _FLUENT_SG_DTRM_H

#include "dll.h"

#if RP_DTRM
# include "mem.h"

/* Define constants, macros and prototypes for dtrm */

#define S_G_I(i) s_globs[i].intensity
#define S_G_T(i) s_globs[i].temperature
#define S_G_Q_M(i) s_globs[i].q_minus
#define V_G_T(i) v_globs[i].temperature
#define V_G_ABS_COEFF(i) v_globs[i].abs_coeff
#define V_G_SOURCE(i) v_globs[i].source
#define V_G_FACTOR(i) v_globs[i].factor
#define S_GLOB_THREAD O_F_THREAD
#define V_GLOB_THREAD O_C_THREAD

typedef struct surface_glob_struct
{
  real intensity;             /* ray intensity */
  real temperature;           /* surface glob temperature */
  real q_minus;               /* irradiation flux */
  real area;                  /* surface glob area */
  Thread *thread;             /* thread to which the faces belong */
  Objp  *f_list;              /* link list of faces in the glob */
} Surface_Glob;

typedef struct volume_glob_struct
{
  real temperature;          /* volume glob temperature */
  real abs_coeff;            /* volume glob absorption coefficient */
  real source;               /* volume glob source term */
  real factor;               /* ray factor */
  real volume;               /* glob volume */
  Thread *thread;            /* thread to which the cells belong */
  Objp *c_list;              /* cells in the glob */
} Volume_Glob;


extern FLUENT_EXPORT Surface_Glob *s_globs;

FLUENT_EXPORT void Set_Rays_Read(cxboolean status);
FLUENT_EXPORT cxboolean Get_Rays_Read(int *nphi, int *ntheta);
FLUENT_EXPORT void Set_Globs_Done(cxboolean status);
FLUENT_EXPORT cxboolean Get_Globs_Done(void);
FLUENT_EXPORT void Group_Cells(Domain *domain, int cell_size, int face_size);
FLUENT_EXPORT void Delete_All_Groups(void);
FLUENT_EXPORT void Read_Rays(FILE *fp);
FLUENT_EXPORT void Update_Dtrm_Memory(void);
FLUENT_EXPORT void Solve_Dtrm_For_Nita(void);
FLUENT_EXPORT void Get_Glob_Info(int *n_v_globs, int *n_s_globs);
FLUENT_EXPORT void Get_V_Glob( int glob_id, Objp **cell_list);
FLUENT_EXPORT void Get_S_Glob( int glob_id, Objp **face_list);
FLUENT_EXPORT void Display_Globs(int typeGlob);
FLUENT_EXPORT void Init_Dtrm_Intensity(void);
FLUENT_EXPORT void Free_Glob_Qminus(void);
FLUENT_EXPORT int Write_Glob_Qminus(FILE *fp, cxboolean binary);
#if !RP_NODE
FLUENT_EXPORT int Read_Glob_Qminus(FILE *fp, cxboolean binary, cxboolean double_data);
#endif

#endif /* RP_DTRM */
FLUENT_EXPORT cxboolean SV_get_neighbour_cache( CX_Cell_Id *cell, CX_Face_Id fNum, CX_Cell_Id *n, int globbing);
FLUENT_EXPORT void Fill_Cell_Node_Coords_Min_Max(int ncells, float **min, float **max);
FLUENT_EXPORT void Fill_Cell_On_Bndry(cxboolean *cell_on_bndry);
FLUENT_EXPORT void Free_Cface_Neighbor_Cells(void);
FLUENT_EXPORT void Fill_Cface_Neighbor_Cells(int globbing);
FLUENT_EXPORT void Free_Cid_Cache(void);
FLUENT_EXPORT int Fill_Cid_Cache(void);
FLUENT_EXPORT void SV_Mark_Ext_Cells(int mark);
FLUENT_EXPORT cxboolean Is_Bndry_Thread(Thread *tface);
FLUENT_EXPORT int SV_is_wall_face(CX_Cell_Id *c, CX_Face_Id f);
FLUENT_EXPORT int face_index(cell_t cell, Thread *tcell, face_t f, Thread *tf);
FLUENT_EXPORT int SV_get_dimn(void);

#if !RP_HOST
FLUENT_EXPORT void Get_S_Glob( int glob_id, Objp **face_list);
FLUENT_EXPORT void Get_V_Glob( int glob_id, Objp **cell_list);
#endif

#if RP_NODE
FLUENT_EXPORT int SV_is_interior_cell (CX_Cell_Id *c);
#endif
#if PARALLEL
FLUENT_EXPORT void BroadCastdtrmdata(void);
#endif
FLUENT_EXPORT void Store_v_globs(void);
FLUENT_EXPORT void Model_Initialize_dtrm(void);
#endif /* _FLUENT_SG_DTRM_H */
