/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SG_DISCO_H
#define _FLUENT_SG_DISCO_H

#include "dll.h"

#define C_DO_I(c,t,i)C_STORAGE_R_XV(c,t,SV_DO_I,i)
#define F_DO_I(e,t,i) C_DO_I(e,t,i)
#define C_DO_IRRAD(c,t,nb)C_STORAGE_R_XV(c,t,SV_DO_IRRAD,nb)
#define F_DO_IRRAD_SHELL(f,t,nb)F_STORAGE_R_XV(f,t,SV_DO_IRRAD_SHELL,nb)
#define F_DO_QM(f,t)F_STORAGE_R(f,t,SV_DO_QMINUS)
#define F_DO_QNET(f,t)F_STORAGE_R(f,t,SV_DO_QNET)
#define F_DO_QA(f,t,nb)F_STORAGE_R_XV(f,t,SV_DO_QABS,nb)
#define F_DO_QR(f,t,nb)F_STORAGE_R_XV(f,t,SV_DO_QREFL,nb)
#define F_DO_QT(f,t,nb)F_STORAGE_R_XV(f,t,SV_DO_QTRANS,nb)
#define F_DO_IRR_QT(f,t,nb)F_STORAGE_R_XV(f,t,SV_DO_IRR_QTRANS,nb)
#define F_DO_IRR_QR(f,t,nb)F_STORAGE_R_XV(f,t,SV_DO_IRR_QREFL,nb)
#define F_DO_IRR_QA(f,t,nb)F_STORAGE_R_XV(f,t,SV_DO_IRR_QABS,nb)

#define RADIATING_THREAD_P(t)(THREAD_VAR(t).cell.radiating)
#define COLLIMATED_NTHETA_PIX 20
#define COLLIMATED_NPHI_PIX 20
#if RP_3D
# define S2_SIZE 6
#else
# define S2_SIZE 4
#endif
#define RAD_FLOW_BOUNDARY_P(t) (THREAD_F_VINLET == THREAD_TYPE(t) ||\
                                   THREAD_F_MFINLET == THREAD_TYPE(t) ||\
                                   THREAD_F_PINLET == THREAD_TYPE(t) ||\
                                   THREAD_F_POUTLET == THREAD_TYPE(t) ||\
                                   THREAD_F_PFAR == THREAD_TYPE(t) ||\
                                   THREAD_F_OUTFLOW == THREAD_TYPE(t))

extern FLUENT_EXPORT cxboolean sg_comet, pixel_interior;
extern FLUENT_EXPORT int current_ns, current_ni, disco_scheme;
extern FLUENT_EXPORT int n_theta_pix, n_phi_pix;
extern FLUENT_EXPORT real (*disco_ords)[3];
extern FLUENT_EXPORT real *disco_weights;
extern FLUENT_EXPORT real (*disco_surf_weights)[3];
extern FLUENT_EXPORT real ****pixel_ords;
extern FLUENT_EXPORT real ****pixel_surf_weights;
extern FLUENT_EXPORT real **pixel_weights;
extern FLUENT_EXPORT real ***collimated_ords;
extern FLUENT_EXPORT real ***collimated_surf_weights;

extern FLUENT_EXPORT real (*disco_s2_weights)[S2_SIZE];
extern FLUENT_EXPORT real (*disco_surf_weights2)[3];
extern FLUENT_EXPORT real (*disco_s2_weights2)[S2_SIZE];

FLUENT_EXPORT void Init_Disco(Domain *domain);
FLUENT_EXPORT void Init_Spectral_Bands(void);
FLUENT_EXPORT void Init_Intensities(Domain *domain);
FLUENT_EXPORT void Solve_Disco(Domain *domain, int nb, int ni);
FLUENT_EXPORT cxboolean Solve_Disco_Acc_P(Domain *domain);
FLUENT_EXPORT void Solve_Disco_Acc(Domain *domain);
FLUENT_EXPORT void Solve_DOM(Domain *domain);
FLUENT_EXPORT void Update_Boundary_Intensities(Domain *domain);
FLUENT_EXPORT void Update_DO_Sources_UDF(int c, Thread *t, int nb, real *volEmitRad);
FLUENT_EXPORT void Update_Irradiation(Domain *domain, int nb);
FLUENT_EXPORT void Init_Irradiation_Tmp(Domain *domain);
FLUENT_EXPORT void Init_Irradiation(Domain *domain);
FLUENT_EXPORT void Free_Disco_Memory(void);
FLUENT_EXPORT void Cell_Disco_Intensity(cell_t c, Thread *t, int i, real u[3]);
FLUENT_EXPORT real Diffuse_Reflectivity(real n);
FLUENT_EXPORT real Interface_Reflectivity(real cos_theta1, real cos_theta2, real n1, real n2);
FLUENT_EXPORT  cxboolean Effective_Reflectivity(real cos_theta1,
                                                real n1, real n2, real nw,
                                                real dw, real kw,
                                                real *cos_theta2, real *sin_theta2,
                                                real *reflectivity, real *transmissivity);
FLUENT_EXPORT void Effective_Diffuse_Reflectivity(real n1, real n2, real nw,
                                                  real dw, real kw,
                                                  real *reflectivity1, real *transmissivity1,
                                                  real *reflectivity2, real *transmissivity2);
FLUENT_EXPORT void Get_Bands(real **, real **);

FLUENT_EXPORT void Free_Material_Scattering_Matrix(Material *m, int size);
FLUENT_EXPORT void Free_Scattering_Matrices(Domain *domain, int size);
FLUENT_EXPORT void Update_Scattering_Matrices(Domain *domain);
FLUENT_EXPORT real Emissivity_Weighting_Factor(cell_t c0, Thread *thread, real T, int nb);
FLUENT_EXPORT real Black_Body_Emission_Factor(real T, int nb);
FLUENT_EXPORT int  Pixel_Index(real e[3]);
FLUENT_EXPORT int  Sn_Index(real *e, real *A, cxboolean check_all);
FLUENT_EXPORT void Find_Collimated_Pixels(real qn[3], real coll_dtheta, real coll_dphi);
FLUENT_EXPORT void do_local_residual(Domain *const, Level *const, Svar, Svar, int, real *);
FLUENT_EXPORT cxboolean Is_Radiating_Thread(Thread *);
FLUENT_EXPORT real Get_Rad_Temperature(int index, Thread *t);
FLUENT_EXPORT real Get_Rad_Face_Temp(face_t f, Thread *t);
FLUENT_EXPORT real Get_Sided_Face_Refractive_Index(int index, Thread *t, int nb);
FLUENT_EXPORT cxboolean Is_Radiation_Model_Enabled(void);
FLUENT_EXPORT cxboolean Is_DPMS_Radiation_Enabled_P(void);
real Flow_Boundary_External_Blackbody_Emission(face_t, Thread *, int);

#if RP_AMG_DO
FLUENT_EXPORT void Solve_Comet(Domain *domain);
FLUENT_EXPORT void Comet_Domain_Check(Domain *domain);
FLUENT_EXPORT void Init_I_CORR(Domain *domain);
FLUENT_EXPORT void Model_Initialize_disco(void);
#endif


#endif /* _FLUENT_SG_DISCO_H */
