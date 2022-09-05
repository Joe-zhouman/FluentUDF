/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SG_VOF_H
#define _FLUENT_SG_VOF_H

#include "dll.h"

/* Define constants, macros and prototypes common for multiphase files only */

#define ADD_DRIFT_FLUX 1 /*0 not supported anymore and this flag is being deleted now*/
#define TIME_AVARAGED 1

#define SMALL_GRAD 1.e-10
#define LARGE_NUMBER 1.e10
#define SMALL_NUMBER 1.e-10

#define SV_NON_SMOOTHED_GRAD SV_VOF_G
#define SV_SMOOTHED_GRAD SV_VOF_RG

#define C_VOF_S(c,t)   FAST_C_STORAGE_R(c,t,SV_VOF_S)

/*..... ................. ..  ..........I */
#define C_SP_PACK_FLAG(c, t)  C_STORAGE_R(c, t, SV_SP_PACK_FLAG)

#define INTERIOR_TREATED_FACE_THREADS_P(t) ((THREAD_TYPE(t) == THREAD_F_INTERIOR) ||\
                                            (THREAD_TYPE(t) == THREAD_F_PERIODIC) ||\
                                            (THREAD_TYPE(t) == THREAD_F_SHADOW) ||\
                                            (THREAD_TYPE(t) == THREAD_F_JUMP))

#if RP_3D
# define MAX_EDGES_PER_CELL 12
#else
# define MAX_EDGES_PER_CELL 4
#endif

#define MAX_NODES_PER_FV 2*MAX_NODES_PER_FACE

extern FLUENT_EXPORT int Edge_Number[N_CELL_TYPES];
extern FLUENT_EXPORT int FV_TYPE[];

extern FLUENT_EXPORT int
Edge_Nodes[N_CELL_TYPES][12][4];

FLUENT_EXPORT void Copy_Fluid_Cell_Vector(Domain *domain, Svar var_from, Svar var_to);
FLUENT_EXPORT void Calc_Drift_Flux(Domain *domain, Svar nFlux);
FLUENT_EXPORT void Flotsam_Indicator(Domain *domain, Svar sw, cxboolean filter_sw);
FLUENT_EXPORT void Scalar_Smoothing_Cell_Based(Domain *domain, Svar sw, Svar sw_sm);
FLUENT_EXPORT void Scalar_Smoothing_Node_Based(Domain *domain, Svar sw, Svar sw_sm);
FLUENT_EXPORT void Volume_Weighted_Scalar_Smoothing(Domain *domain, Svar sw, Svar sw_sm, cxboolean node_based, int n_smooth);
FLUENT_EXPORT void Vector_Smoothing(Domain *domain, Svar sw, Svar sw_sm);
FLUENT_EXPORT void Phase_Averaged_Scalar_Smoothing(Domain *domain, Svar sw, Svar sw_sm, int scale_id, int num);
FLUENT_EXPORT void Execute_Volume_Fraction_Smoothing(Domain *mdomain);
FLUENT_EXPORT void Reconstruct_Geo_Reconstruct_VOF(Domain *domain, Svar sv_Vof, real time, real dt);
FLUENT_EXPORT void Reconstruct_Quad_Donor_Acceptor(Domain *domain, Svar sv_Vof, real time, real dt);
FLUENT_EXPORT void Recon_Front(Domain *phaseDomain, Svar sw);
FLUENT_EXPORT double X_Volume(real y_vof, real NV_VEC((*r_n)), real *y_n,
                              int nNodes, int nEdges, int edgeN[MAX_EDGES_PER_CELL][4],
                              int index[MAX_NODES_PER_CELL]);
FLUENT_EXPORT void Transform_Coordinate(int nodes, real *e_n, real *rc,
                                        real NV_VEC((*r_n)), real lc);
FLUENT_EXPORT void Index_Rank_EdgeN(int n, real NV_VEC((*r)), int *index, int *rank,
                                    int nEdge, int (*edge_pt)[4], int (*edgeN)[4]);
FLUENT_EXPORT void Store_VOF_Gradients(Domain *domain, int disc_scheme, cxboolean secnd_order, cxboolean diffusion_in_vof);
FLUENT_EXPORT real Get_Surface_Distance(cell_t c, Thread *t);
FLUENT_EXPORT void VOF_Compressive_Beta_Factor(Domain *domain, Svar sw);
FLUENT_EXPORT void Update_Compressive_Beta_Max(Domain *domain);
FLUENT_EXPORT void BGM_Calc_Alpha_Star(Domain *phaseDomain, Svar sv_vof, Svar sv_vFlux);
FLUENT_EXPORT void MP_Case_Check(Domain *domain, int verbosity);

#endif /* _FLUENT_SG_VOF_H */

