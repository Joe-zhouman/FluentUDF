/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifdef __cplusplus
#define EXTERN_C     extern "C"
#else
#define EXTERN_C     extern
#endif

#define C_AC_MODESAN_MI(c,t,i)C_STORAGE_R(c,t,SV_AC_MODESAN_M_I(i))

void OPShift(const DOUBLE_COMPLEX omega_shift, const int n, cxboolean run_ama, Domain *domain, const DOUBLE_COMPLEX *v, DOUBLE_COMPLEX *w);
FLUENT_EXPORT void Write_Modal_Analysis_Section(FILE *fd, cxboolean binary);
FLUENT_EXPORT void Read_Modal_Analysis_Section(FILE *fd, int section);
FLUENT_EXPORT void Ac_Modal_Analysis(Domain *domain, int nev);
