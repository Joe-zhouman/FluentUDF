/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_AMARK_H
#define _FLUENT_AMARK_H

#include "dll.h"
#include "mem.h"

FLUENT_EXPORT cxboolean Set_Cell_Thread_Marking_Flag(const cxboolean);

FLUENT_EXPORT void Clear_All_Marked_Cells(Domain *);

FLUENT_EXPORT void Clear_Bit_In_All_Marked_Cells(Domain *, unsigned int);

FLUENT_EXPORT void Clear_Pair_Bits_In_All_Marked_Cells(Domain *,
                                                       unsigned int,
                                                       unsigned int);

FLUENT_EXPORT void Clear_Marked_Cells(Domain *);

FLUENT_EXPORT void Clear_Bit_In_Marked_Cells(Domain *, unsigned int);

FLUENT_EXPORT void Clear_Pair_Bits_In_Marked_Cells(Domain *,
                                                   unsigned int,
                                                   unsigned int);

FLUENT_EXPORT void Set_Bit_In_Marked_Cells(Domain *, unsigned int);

FLUENT_EXPORT void Toggle_Bit_In_Marked_Cells(Domain *, unsigned int);

FLUENT_EXPORT void Copy_Bits_In_Marked_Cells(Domain *,
                                             unsigned int,
                                             unsigned int);

FLUENT_EXPORT void Copy_Pair_Bits_In_Marked_Cells(Domain *,
                                                  unsigned int,
                                                  unsigned int,
                                                  unsigned int,
                                                  unsigned int);

FLUENT_EXPORT void And_Bits_In_Marked_Cells(Domain *,
                                            unsigned int,
                                            unsigned int,
                                            unsigned int);

FLUENT_EXPORT void Or_Bits_In_Marked_Cells(Domain *,
                                           unsigned int,
                                           unsigned int,
                                           unsigned int);

FLUENT_EXPORT void Xor_Bits_In_Marked_Cells(Domain *,
                                            unsigned int,
                                            unsigned int,
                                            unsigned int);

FLUENT_EXPORT void Not_Bit_In_Marked_Cells(Domain *,
                                           unsigned int,
                                           unsigned int);

FLUENT_EXPORT int Smooth_Bit_In_Marked_Cells(Domain *, unsigned int);

FLUENT_EXPORT void Mark_Cells_Below_Min_Volume(Domain *, unsigned int);

FLUENT_EXPORT void Mark_Cells_Above_Max_Refine_Level(Domain *, unsigned int);

FLUENT_EXPORT void Predicates_For_Marking(Domain *, const char *, const char *);

FLUENT_EXPORT void Predicates_For_Dynamic_Adaption(Domain *, const char *);

FLUENT_EXPORT void Mark_With_Yplus_Per_Thread(Domain *, Domain *, Thread *, Thread *,
                                              unsigned int,
                                              unsigned int,
                                              int *, int *);

FLUENT_EXPORT int Mark_With_Volume(Domain *,
                                   real,
                                   unsigned int);

FLUENT_EXPORT int Mark_With_Volume_Change(Domain *,
                                          real r,
                                          unsigned int);

FLUENT_EXPORT void Mark_With_Refine_Level(Domain *,
                                          unsigned int,
                                          unsigned int,
                                          int *, int *);

FLUENT_EXPORT int Mark_Cell_With_ID(Domain *, unsigned int, int, int);

FLUENT_EXPORT void Fill_Boundary_Volume(Domain *);

FLUENT_EXPORT int Mark_With_Boundary_Volume(Domain *, unsigned int);

FLUENT_EXPORT int Mark_Boundary_Cells_Per_Thread (Domain *,
                                                  Thread *,
                                                  unsigned int);

FLUENT_EXPORT int Mark_Inside_Sphere(Domain *,
                                     unsigned int,
                                     real, real, real,
                                     real);

FLUENT_EXPORT int Mark_Inside_Cylinder(Domain *,
                                       unsigned int,
                                       real, real,
                                       real, real,
                                       real, real,
                                       real);

FLUENT_EXPORT int Mark_Inside_Hex(Domain *,
                                  unsigned int,
                                  real, real,
                                  real, real,
                                  real, real);

FLUENT_EXPORT int Mark_Inside_Iso_Range(Domain *,
                                        unsigned int,
                                        real, real, const char *, cxboolean);

FLUENT_EXPORT void Unmark_Cells_By_Volume_And_Level(Domain *, unsigned int);
#if RP_OVERSET
FLUENT_EXPORT void Unmark_Overset_Dead_Cells(Domain *, unsigned int);
#endif

FLUENT_EXPORT Svar Get_Residual_Svar_For_Equation(Domain *domain, const char *eqn,
                                                  Domain **svar_domain);
FLUENT_EXPORT void Mark_Cells_With_Svar_Above_Threshold(Domain *domain,
                                                        Svar nv, real val,
                                                        unsigned int bitIndex);
#if !RP_HOST
FLUENT_EXPORT int Get_Svar_Minmax(Domain *domain, Svar nv, real minmax[2]);
#endif
FLUENT_EXPORT int Mark_Percent_Of_Ncells(Domain *,
#if !RP_HOST || RP_3D
                                         unsigned int,
#endif
#if !RP_HOST
                                         real,
#endif
                                         int
#if !RP_HOST
                                         , real *, real *
#endif
                                        );

FLUENT_EXPORT void Local_Count_Marked_Cells(Domain *,
                                            unsigned int,
                                            unsigned int,
                                            int *, int *);

FLUENT_EXPORT void Limit_Marked_Cells(Domain *,
                                      unsigned int,
                                      unsigned int,
                                      int *, int *);

FLUENT_EXPORT cxboolean Fill_Cell_Values_From_Base_Zone(Domain *domain,
                                                        Objp *tlist,
                                                        int cell_distance);

#if GRAPHICS && CORTEX
FLUENT_EXPORT cell_t Pick_Marked_Cell(Domain *, Thread **, int);

FLUENT_EXPORT void Display_Marked_Cells(Domain *,
                                        unsigned int,
                                        unsigned int,
                                        unsigned int);
#endif

#define SET_BIT_MKR(m,n)(((cxindexU)(m)) | (0x0001 << (n)))
#define CLR_BIT_MKR(m,n)(((cxindexU)(m)) & (~(0x0001 << (n))))
#define TOG_BIT_MKR(m,n)(((cxindexU)(m)) ^ (0x0001 << (n)))
#define CHK_BIT_MKR(m,n)(((cxindexU)(m)) & (0x0001 << (n)))

#define SET_BIT(c,t,n)SET_BIT_MKR(C_MARK(c,t),n)
#define CLR_BIT(c,t,n)CLR_BIT_MKR(C_MARK(c,t),n)
#define TOG_BIT(c,t,n)TOG_BIT_MKR(C_MARK(c,t),n)
#define CHK_BIT(c,t,n)CHK_BIT_MKR(C_MARK(c,t),n)

#define A_OR_B_INTO_C(u,t,a,b,c)  \
     ((CHK_BIT(u,t,a) |  CHK_BIT(u,t,b)) ? SET_BIT(u,t,c) : CLR_BIT(u,t,c))
#define A_AND_B_INTO_C(u,t,a,b,c) \
     ((CHK_BIT(u,t,a) && CHK_BIT(u,t,b)) ? SET_BIT(u,t,c) : CLR_BIT(u,t,c))
#define A_XOR_B_INTO_C(u,t,a,b,c) \
     (((CHK_BIT(u,t,a)!=0) ^ (CHK_BIT(u,t,b)!=0)) ? SET_BIT(u,t,c) : CLR_BIT(u,t,c))
#define NEG_A_INTO_C(u,t,a,c) (CHK_BIT(u,t,a) ? CLR_BIT(u,t,c) : SET_BIT(u,t,c))

#if RP_AXI
# define ADAPT_VOLUME(c,t) ((rp_axi) ? C_VOLUME_2D(c,t) : C_VOLUME(c,t))
#else
# define ADAPT_VOLUME(c,t) C_VOLUME(c,t)
#endif

#endif /* _FLUENT_AMARK_H */
