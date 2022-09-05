/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/

#ifndef _SEDMGLOBAL_H
#define _SEDMGLOBAL_H

#define M_LGRN() (M_sp_vfc == 1)
#define M_SED() (M_sp_vfc == 2)

extern FLUENT_EXPORT void sedm_compute_mflux_from_vflux(Domain *d);
extern FLUENT_EXPORT void sedm_init_continuity_source(Domain *domain);
extern FLUENT_EXPORT void sedm_add_pp_source(Domain *domain);
extern FLUENT_EXPORT void sedm_continuity_pdf_source(Domain *domain);

#endif

