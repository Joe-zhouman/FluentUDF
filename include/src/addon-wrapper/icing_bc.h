/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/
#ifndef _ICING_BC_H
#define _ICING_BC_H

#include "dll.h"

typedef struct icing_inlet_struct
{
  int  fensapice_flow_bc_subtype;
  cxboolean fensapice_drop_bccustom;
  real fensapice_drop_lwc;
  real fensapice_drop_dtemp;
  real fensapice_drop_ddiam;
  cxboolean fensapice_drop_dv;
  real fensapice_drop_dx;
  real fensapice_drop_dy;
  real fensapice_drop_dz;
  cxboolean fensapice_dpm_surface_injection;
  int  fensapice_dpm_inj_nstream;
  real fensapice_drop_icc;
  real fensapice_drop_ctemp;
  real fensapice_drop_cdiam;
  cxboolean fensapice_drop_cv;
  real fensapice_drop_cx;
  real fensapice_drop_cy;
  real fensapice_drop_cz;
  cxboolean fensapice_drop_vrh_flag;
  real fensapice_drop_vrh;
  real fensapice_drop_vc;
} icing_inlet;

typedef struct icing_outlet_struct
{
  int  fensapice_flow_bc_subtype;
} icing_outlet;

typedef struct icing_wall_struct
{
  int  fensapice_ice_icing_mode;
  cxboolean fensapice_ice_hflux_flag;
  real fensapice_ice_hflux;
  cxboolean fensapice_drop_vwet_flag;
} icing_wall;

int icing_inlet_thread_set_var(char *name,
                               icing_inlet *pstruct,
                               Pointer value);

int icing_outlet_thread_set_var(char *name,
                               icing_outlet *pstruct,
                               Pointer value);
int icing_wall_thread_set_var(char *name,
                              icing_wall *pstruct,
                              Pointer value);
void icing_inlet_init_memory(icing_inlet *pstruct);
void icing_outlet_init_memory(icing_outlet *pstruct);
void icing_wall_init_memory(icing_wall *pstruct);

#endif

