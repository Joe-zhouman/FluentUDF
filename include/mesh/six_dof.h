/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DYNAMESH_6DOF_H
#define _FLUENT_DYNAMESH_6DOF_H

typedef struct six_dof_object
{

  char name[132];
  real mass;

  real Ixx;
  real Iyy;
  real Izz;
  real Ixy;
  real Iyz;
  real Ixz;

  cxboolean onedof_t_p;
  cxboolean onedof_r_p;
  cxboolean onedof_cons_p;

  real dir[3];
  real rot_loc[3];

  real loc;
  real loc_n;
  real init;
  real min;
  real max;

  real preload;
  real spring;

  struct six_dof_object *next;
} Six_DOF_Object;

/* vector quantities should be subsequent entries
   (see macros below) */
typedef enum
{
  SDOF_MASS = 0,
  SDOF_IXX,
  SDOF_IYY,
  SDOF_IZZ,
  SDOF_IXY,
  SDOF_IXZ,
  SDOF_IYZ,
  SDOF_LOAD_LOCAL,         /* boolean */
  SDOF_LOAD_F_X,
  SDOF_LOAD_F_Y,
  SDOF_LOAD_F_Z,
  SDOF_LOAD_M_X,
  SDOF_LOAD_M_Y,
  SDOF_LOAD_M_Z,
  SDOF_CUSTOM_TRANS,       /* boolean */
  SDOF_CTRANS_11,
  SDOF_CTRANS_12,
  SDOF_CTRANS_13,
  SDOF_CTRANS_21,
  SDOF_CTRANS_22,
  SDOF_CTRANS_23,
  SDOF_CTRANS_31,
  SDOF_CTRANS_32,
  SDOF_CTRANS_33,
  SDOF_DTRANS_11,
  SDOF_DTRANS_12,
  SDOF_DTRANS_13,
  SDOF_DTRANS_21,
  SDOF_DTRANS_22,
  SDOF_DTRANS_23,
  SDOF_DTRANS_31,
  SDOF_DTRANS_32,
  SDOF_DTRANS_33,
  SDOF_ZERO_TRANS_X,       /* all zero switches are boolean */
  SDOF_ZERO_TRANS_Y,
  SDOF_ZERO_TRANS_Z,
  SDOF_ZERO_ROT_X,
  SDOF_ZERO_ROT_Y,
  SDOF_ZERO_ROT_Z,
  SDOF_SYMMETRY_X,
  SDOF_SYMMETRY_Y,
  SDOF_SYMMETRY_Z,
  SDOF_SIZE_PROP           /* has to be the last entry */
} SDOF_Prop;

#define SDOFP_MASS(s)         (s[SDOF_MASS])
#define SDOFP_MOI(s)          (s+SDOF_IXX)          /* moments of inertia */
#define SDOFP_POI(s)          (s+SDOF_IXY)          /* products of inertia */
#define SDOFP_LOAD_LOCAL(s)   (s[SDOF_LOAD_LOCAL])  /* load forces/moments */
#define SDOFP_LOAD_F(s)       (s+SDOF_LOAD_F_X)
#define SDOFP_LOAD_M(s)       (s+SDOF_LOAD_M_X)
#define SDOFP_CUSTOM_TRANS(s) (s[SDOF_CUSTOM_TRANS])/* costum transformations */
#define SDOF_CTRANS           SDOF_CTRANS_11
#define SDOF_DTRANS           SDOF_DTRANS_11
#define SDOFP_CTRANS(s)       (s+SDOF_CTRANS)
#define SDOFP_DTRANS(s)       (s+SDOF_DTRANS)
#define SDOFP_ZERO_TRANS(s)   (s+SDOF_ZERO_TRANS_X)
#define SDOFP_ZERO_ROT(s)     (s+SDOF_ZERO_ROT_X)
#define SDOFP_SYMMETRY(s)     (s+SDOF_SYMMETRY_X)   /* symmetry plane normal */

#define SDOFO_NAME(sobj)      ((sobj)->name)
#define SDOFO_MASS(sobj)      ((sobj)->mass)
#define SDOFO_IXX(sobj)       ((sobj)->Ixx)
#define SDOFO_IYY(sobj)       ((sobj)->Iyy)
#define SDOFO_IZZ(sobj)       ((sobj)->Izz)
#define SDOFO_IXY(sobj)       ((sobj)->Ixy)
#define SDOFO_IYZ(sobj)       ((sobj)->Iyz)
#define SDOFO_IXZ(sobj)       ((sobj)->Ixz)
#define SDOFO_1DOF_T_P(sobj)  ((sobj)->onedof_t_p)
#define SDOFO_1DOF_R_P(sobj)  ((sobj)->onedof_r_p)
#define SDOFO_CONS_P(sobj)    ((sobj)->onedof_cons_p)
#define SDOFO_DIR(sobj)       ((sobj)->dir)
#define SDOFO_CENTER_ROT(sobj)((sobj)->rot_loc)
#define SDOFO_INIT(sobj)      ((sobj)->init)
#define SDOFO_LOC(sobj)       ((sobj)->loc)
#define SDOFO_LOC_N(sobj)     ((sobj)->loc_n)
#define SDOFO_MIN(sobj)       ((sobj)->min)
#define SDOFO_MAX(sobj)       ((sobj)->max)
#define SDOFO_F(sobj)         ((sobj)->preload)
#define SDOFO_K(sobj)         ((sobj)->spring)
#define SDOFO_NEXT(sobj)      ((sobj)->next)

extern FLUENT_EXPORT Six_DOF_Object *sdof_objs;

FLUENT_EXPORT void Create_SDOF_Object(Pointer *);
FLUENT_EXPORT void Delete_SDOF_Object(const char *);
FLUENT_EXPORT Six_DOF_Object *Get_SDOF_Object(char[132]);
FLUENT_EXPORT Six_DOF_Object *Allocate_SDOF_Object(char[132]);
FLUENT_EXPORT void Get_Prop_From_Obj(real *, Six_DOF_Object *);

FLUENT_EXPORT cxboolean SDOF_Collect_Threads (Domain *);
FLUENT_EXPORT void SDOF_Free_Threads (void);
FLUENT_EXPORT void SDOF_Threads_Compute_Motion (Domain *, real, real);
FLUENT_EXPORT void SDOF_Threads_Store_Constraint(void);
FLUENT_EXPORT void SDOF_Threads_Reset_Constraint(void);
FLUENT_EXPORT void SDOF_Update_Constraints(void);
FLUENT_EXPORT void SDOF_Get_Motion (Dynamic_Thread *,
                                    real[3], real[3], real[3]);
FLUENT_EXPORT void SDOF_Fill_RB_State (Dynamic_Thread *, rb_state *, real, real);
FLUENT_EXPORT void SDOF_Overwrite_Motion (Dynamic_Thread *,
                                          real[3], real[3], real[3]);
FLUENT_EXPORT void SDOF_Write_File_Motion_History(real, real);
FLUENT_EXPORT void SDOF_Get_File_Motion_History_Store_Name (Dynamic_Thread *,
                                                            char *);
#endif /* _FLUENT_DYNAMESH_6DOF_H */
