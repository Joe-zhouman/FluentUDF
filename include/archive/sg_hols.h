/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SG_HOLS_H
#define  _FLUENT_SG_HOLS_H

#define C_HOLS_MARK(c,t)C_STORAGE_I(c,t,SV_HOLS_MARK)
#define F_HOLS_MARK(f,t)F_STORAGE_I(f,t,SV_HOLS_MARK)
#define C_HOLS_BOUND(c,t)C_STORAGE_I(c,t,SV_HOLS_BOUND)
#define F_HOLS_BOUND(f,t)F_STORAGE_I(f,t,SV_HOLS_BOUND)
#define F_DIFF_CENTRE(f,t)F_STORAGE_R(f,t,SV_DIFF_CENTRE)
FLUENT_EXPORT void Free_sg_memory(Domain *domain);

FLUENT_EXPORT void Init_Hols_Deriv(Domain *domain);

FLUENT_EXPORT void HOLS_Scalar_Reconstruction(Domain *domain, Svar w, Svar rgw);

FLUENT_EXPORT void
HOLS_Vector_Reconstruction(Domain *domain, ND_VEC(Svar wx, Svar wy, Svar wz)
                           , ND_VEC(Svar rgwx, Svar rgwy, Svar rgwz) );


FLUENT_EXPORT real
Hols_Second_Derivative_Source(face_t f, Thread *t, Svar p, Svar dp,
                              real *dr, real *es, real *A, real ds,
                              real dr0, real dr1, real A_by_es, real k);

FLUENT_EXPORT real
Boundary_Hols_Second_Derivative_Source(Svar phi, cell_t c0, Thread *t0,
                                       real *dr, real *es);

FLUENT_EXPORT real
H_Boundary_Secondary_Gradient_Source(face_t f, Thread *t, Svar p,
                                     real grad[], real ds,
                                     real A_by_es, real k);

FLUENT_EXPORT real
H_Secondary_Gradient_Source(face_t f, Thread *t, Svar p, Svar dp,
                            real grad[], real es[], real ds,
                            real A_by_es, real k);
FLUENT_EXPORT real
diffusion_coeff(face_t f, Thread *t, real k, Svar p, real *es, real A_by_es);

FLUENT_EXPORT real
Diff_Secondary_Gradient(face_t f, Thread *t, Svar p, Svar dp, real k);

FLUENT_EXPORT void
H_Face_Gradient(face_t f, Thread *t, Svar p, Svar dp);

FLUENT_EXPORT void
H_Boundary_Gradient(face_t f, Thread *t, Svar p, Svar dp);

#endif
