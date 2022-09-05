/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */
#ifndef NCI_NUMERICS_H
#define NCI_NUMERICS_H

typedef struct _nci_ws
{
  int nsi;
  int nsb;
  int required_si_thread_index;
  int *si_thread_nelements;
  int *si_id_map;
  int *sb_thread_nelements;
  int *sb_id_map;
  cxboolean *si_stretched_interface;
  Thread **tsi;
  Thread **tsb;
  real **sb_child_sum_area;
  real **si_area_fraction_0;
  real **si_area_fraction_1;

} NCI_WS;


typedef void (*area_fraction01)(face_t f, Thread *thread, real *A0, real *A1);
typedef void (*area_fraction0)(face_t f, Thread *thread, real *A0);

extern FLUENT_EXPORT cxboolean nci_af_computed;

void Find_Number_Of_SI_And_SB(Domain *domain, int *nsi, int *nsb);
void fill_si_and_sb_map_and_nelements(Domain *domain);

void fill_sb_children_area_sum(void);
FLUENT_EXPORT int Find_SI_Thread_Index(Thread *t);
int find_sb_thread_index(Thread *t);
void fill_si_area_fraction(void);

FLUENT_EXPORT void ALLOCATE_NCI_WS(Domain *domain);
FLUENT_EXPORT void FREE_NCI_WS(NCI_WS *);
FLUENT_EXPORT void Construct_NCI_Area_Fraction(Domain *domain);


void si_area_fraction_01(face_t f, Thread *thread, real *A0, real *A1);
void periodic_si_area_fraction_01(face_t f, Thread *thread, real *A0, real *A1);
void si_area_fraction_0(face_t f, Thread *thread, real *A0);
void nci_wt_area_fraction_01(face_t f, Thread *thread, real *A0, real *A1);
void periodic_nci_wt_area_fraction_01(face_t f, Thread *thread, real *A0, real *A1);
void nci_wt_area_fraction_0(face_t f, Thread *thread, real *A0);

FLUENT_EXPORT void Assign_Af_Function_Pointer01(area_fraction01 *fptr, Thread *thread);
FLUENT_EXPORT void Assign_Af_Function_Pointer0(area_fraction0 *fptr, Thread *thread);
FLUENT_EXPORT cxboolean Water_Tight_Nci_Applied(Thread *t);
#endif /*  NCI_NUMERICS_H */
