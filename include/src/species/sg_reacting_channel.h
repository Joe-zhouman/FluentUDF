/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_REACTING_CHANNEL_H
#define _FLUENT_REACTING_CHANNEL_H

#include "dll.h"
typedef struct channel_group_struct
{
  real temp ;
  real mf ;
  real pressure ;
  real flow_direction[ND_ND];
  cxboolean group_as_tube;
  real *yi  ;
  Material *m ; /*material */
  int num_species ;
  int *thread_ids  ;
  int num_bands;
  int num_walls ;
  cxboolean surf_rxn;
  cxboolean porous_media;
  real surf_vol_ratio;
  real porosity ;
  real inertial_resis;
  real visc_resis;
  Material *solid_mat;
  cxboolean user_defined_bc ;
  char user_defined_bc_fcn[PROP_UDF_NAME_LENGTH];
  char surf_rxn_mech_name[MATERIAL_NAME_LENGTH];
} Channel_Group;

typedef struct band_data
{
  face_t *f_index;
  Thread *tf ;
} Band_Data;

typedef struct band_struct
{
  real direction[3];   /* approximate vector of tube axis */
  real stretch;        /* band grid stretch factor */
  real length;          /* length of band */
  real xmin, xmax ; /*local cordinates of the band*/
  real T;        /* band temperature */
  real qdot;     /* band heat flux */
  real xf[3];        /* centroid of band */
  int  nfaces;   /* number of wall faces in band */
  real area ;
  real wall_area;
  real vel ; /*required for varying area of the band cross-section*/
  real rho ;
  real *yi ; /*storing composition and enthalpy*/
  real vol; /*may be required for non reactive coupling : not sure at this moment*/
  real wall_temp ;
  real Nu ;
  real qdot_temp ;
  real cell_temp ;
  real cell_dist ;
  real cell_ktc ;
  real theta ;
  real *yi_surf; /*surface species mass fraction: wall_f_dr*/
  real *yi_wall; /*gas phase species mass fraction at wall*/
  real *cell_wall_site ; /*cell_wall_stie, site fraction*/
  real *wall_f_dr ;
  real *cell_wall_site_old;
  real *wall_yi_site;
  real *surf_rxn_src;
  real hsrc_yi, hsrc_dr, h_surf_site, wall_dr_total;
  real *diff_l;
  real mass_flow_rate ;
  real pressure;
  real rho_solid, cp_solid;
} Channel_Band ;

typedef struct channel_struct
{
  int n_bands;
  int n_walls ;
  Band_Data *f_t ;
  int *thread_ids ; /*n_tubes CFD > n_tubes for 1D code*/
  int group_id ;
  cxboolean tube_is_periodic ;
  Channel_Band *bands ;
  Channel_Group *group ;
} Channel_Tube;


extern FLUENT_EXPORT Channel_Tube *channel_tubes;
extern FLUENT_EXPORT Channel_Group *channel_groups;
extern FLUENT_EXPORT cxboolean solve_reacting_channel ;
extern FLUENT_EXPORT int N_channel_groups ;

FLUENT_EXPORT void Set_Reacting_Channel_Variables(Pointer p);
FLUENT_EXPORT void Solve_Reacting_Channel(Domain *d);
FLUENT_EXPORT Material *Pick_Reacting_Channel_Material(int i);
FLUENT_EXPORT void  Get_Reacting_Channel_Band_Variables(real *temp, real *hf, cxboolean *surf_rxn, real *rc_dzdt, cxboolean *rc_porous, real *rc_porosity);
FLUENT_EXPORT Pointer Get_Reacting_Channel_Variables_Data(const char *, int *, int);
FLUENT_EXPORT Pointer Get_Reacting_Channel_Reports(Pointer, int *, int);
FLUENT_EXPORT void Read_Reacting_Channel_Data(Domain *, FILE *, cxboolean, cxboolean);
FLUENT_EXPORT void Write_Reacting_Channel_Data(Domain *, FILE *, cxboolean);
FLUENT_EXPORT cxboolean Is_outer_flow_reacting(void);
FLUENT_EXPORT void Free_All_Channel_Memory(void);
#if PARALLEL
FLUENT_EXPORT void Register_Reacting_Channel_HDF_IO_Manager(void);
FLUENT_EXPORT void Deregister_Reacting_Channel_HDF_IO_Manager(void);
#endif
#endif /*_FLUENT_REACTING_CHANNEL_H*/
