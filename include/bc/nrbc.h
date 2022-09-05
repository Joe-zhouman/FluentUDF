/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _NRBC_H_
#define _NRBC_H_

/* KMAX Max number of quasi radials */
/* JMAX Max number of circumferential points */


typedef struct nr_boundary_struct
{
  Thread *thread;   /* associated boundary thread */
  Thread *partner;    /* mixing-plane partner */
  int kmax   ;      /* max number of quasi radials */

  real pitch ;

  int  *jmax ;                  /* of dimension [KMAX]       */
  real *qq   ;

  real **phi ;                  /* of dimension [KMAX][JMAX] */
  real **dphi;

  face_t **face;


#if RP_3D
  real *cosp;   /* cos of local slope angle of quasi radial */
  real *sinp;   /* sin of local slope angle of quasi radia; */
#endif

  real (*u_ave)[ND_3];   /* of dimension [KMAX][ND_3] */

  real *p_ave  ;        /* of dimension [KMAX]       */
  real *r_ave  ;
  real *s0_ave ;
  real *h0_ave ;
  real *Cp_ave ;
  real *Rg_ave ;
  real *tke_ave;
  real *tds_ave;

  int compute_node;   /* index of compute node (parallel) */

  struct nr_boundary_struct *next;

} NR_Boundary_Data;


int  Initialize_Non_Reflecting_Boundaries(Domain *);
void Update_Non_Reflecting_Boundary_Corrections(Domain *domain, int);
int  Free_Non_Reflecting_BC_Data(Domain *domain) ;
void compute_radial_pressure_profile(Thread *t, int nbins, real bin_p[], real *rmax, real *rmin, real *dp_tmfr);

#endif


