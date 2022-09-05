/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_GRANULAR_H
#define _FLUENT_GRANULAR_H

#define SPECULAR_COEFF(t) THREAD_VAR(t).wall.gran_spec_coeff

#define C_GT(c,t)  FAST_C_STORAGE_R(c,t,SV_GRANULAR_TEMP)
#define F_GT(e,t) C_GT(e,t)
#define C_GT_AP(c,t)  C_STORAGE_R(c,t,SV_GRANULAR_TEMP_AP)
#define C_GT_S(c,t)  C_STORAGE_R(c,t,SV_GRANULAR_TEMP_S)
#define C_GT_GRAD(c,t)  C_STORAGE_R_NV(c,t,SV_GRANULAR_TEMP_G)
#define C_GT_RGRAD(c,t)  C_STORAGE_R_NV(c,t,SV_GRANULAR_TEMP_RG)
#define C_GT_M1(c,t)  FAST_C_STORAGE_R(c,t,SV_GRANULAR_TEMP_M1)
#define C_GT_M2(c,t)  C_STORAGE_R(c,t,SV_GRANULAR_TEMP_M2)
#define F_GT_M1(e,t) C_GT_M1(e,t)
#define F_GT_M2(e,t) C_GT_M2(e,t)
#define C_GT_R(c,t)  C_STORAGE_R(c,t,SV_GRANULAR_TEMP_R)

#define SV_GT_SMOOTHED SV_C_TMP_0
#define SV_AREAW SV_C_TMP_1
#define SV_GRANULAR_TEMP_GEN SV_C_TMP_0
#define SV_DIV_GV SV_C_TMP_1
#define C_GT_GEN(c,t)  C_STORAGE_R(c,t,SV_GRANULAR_TEMP_GEN)
#define C_DIV_GV(c,t)  C_STORAGE_R(c,t,SV_DIV_GV)

#define C_EM(c,t)  FAST_C_STORAGE_R(c,t,SV_DGP_DVOF)
#define C_VOF_GM(c,t)  FAST_C_STORAGE_R(c,t,SV_VOF_GMAX)

extern FLUENT_EXPORT int granular_count (void);
extern FLUENT_EXPORT cxboolean if_granular(void);
extern FLUENT_EXPORT void
Get_Uslip_Granular(real u, real v, real w, real xf[], real x0[], real A[],
                   real Vw[ND_3], real Vsw[ND_3], real f_slp);
extern FLUENT_EXPORT real Maximum_Granular_Vof(Domain *domain);
extern FLUENT_EXPORT void Adjust_Granular_Packed(Domain *domain);
extern FLUENT_EXPORT void Unsteady_Adjust_Granular_Packed(Domain *domain, cxboolean do_adjust_global_mass_p);
extern FLUENT_EXPORT real Mpg_G0(cell_t c, Thread *t, int i, int j);
extern FLUENT_EXPORT real Mpg_F_G0(face_t f, Thread *t, int i, int j);
extern FLUENT_EXPORT real Get_Mpg_Pressure_Udf(cell_t c, Thread *t);
extern FLUENT_EXPORT real Get_Mpg_E_Modulus_Udf(cell_t c, Thread *t);
extern FLUENT_EXPORT real Get_Mpg_Frictional_Pressure_Udf(cell_t c, Thread *t);

extern FLUENT_EXPORT void Update_Max_Packed_Vof(Domain *domain, cxboolean init_only);
extern FLUENT_EXPORT real Mpg_Cell_Pressure(cell_t c, Thread *t);
extern FLUENT_EXPORT real Mpg_I_Face_Pressure(face_t f, Thread *t);
extern FLUENT_EXPORT real Mpg_B_Face_Pressure(face_t f, Thread *t, real Tgi);
extern FLUENT_EXPORT real Mpg_Elasticity_Modulus(cell_t c, Thread *t);
extern FLUENT_EXPORT real Get_Frictional_Pressure(int f_method, real vof_gran, real vofi, real vof_max, real fric_pack);
extern FLUENT_EXPORT real Get_Mpg_Friction_Packing_Limit_Udf(cell_t c, Thread *t);
extern FLUENT_EXPORT void update_face_granular_temperature(Domain *domain);
typedef enum
{
  GP_KINETIC =   0,
  GP_COLLISION = 1,
  GP_KIN_COLL  = 2
} Solids_Pressure_Part;

#endif /* _FLUENT_GRANULAR_H */
