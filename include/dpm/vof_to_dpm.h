/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_VOF_TO_DPM_H
#define _FLUENT_VOF_TO_DPM_H

#include "dll.h"         /* FLUENT_EXPORT */
#include "mem.h"         /* Domain */
#include "sg_vof.h"
#include "dpm_types.h"   /* Injection */


#define  LUMP_DET_USE_QUEUE_ARRAY  00


FLUENT_EXPORT void Model_Initialize_vof_to_dpm(void);
FLUENT_EXPORT void Update_After_VtD_Or_DtV(Domain *domain);
FLUENT_EXPORT void VtD_DtV_Par_Exch_Mess(Domain *dom1, Domain *dom2);
FLUENT_EXPORT cxindex adapt_mesh_in_loop_to_end(Domain *domain, cxboolean coarsen_p, cxboolean refine_p);


/* Following is defined here just for being used below:
 */
typedef struct lump_det_param_set_struct
{
  int liq_phase_index;             /* phase domain index of liquid phase */
  int gas_phase_index;             /* phase domain index of   gas  phase */
  real lump_det_vof_inside;        /* e.g. 0.9, lower limit above which to detect a lump core */
  real lump_det_vof_lower_limit;   /* e.g. 1.e-06, lower limit down to which a lump is found  */
  real lump_max_vof_surface;       /* e.g. 1. - 1.e-06, limit below which it's lump _surface_ */
  real min_diam;                   /* Minimum diameter for transformation */
  real max_diam;                   /* Maximum diameter for transformation */
  real max_Lump_Vof;               /* Maximum VOF found anywhere inside this lump */
  real max_Asph_by_surf_area;      /* Asphericity by surface area of the liq lump */
  real max_Asph_by_av_radius;      /* Asphericity by area-weighted avarage radius */
  real max_Asph_by_sigma_rad;      /* Asphericity by standard deviation of radius */
  real max_Asph_by_orthogity;      /* Asphericity by radius-surface orthogonality */
  real over_fill_factor;           /* by this factor we allow a particle to be larger than the cell */
  cxboolean coarsen_mesh_p;        /* Whether to coarsen the mesh between lump detection and particle insertion */
  Injection *injection;            /* The injection to append the newly inserted particle( parcel)s to. */
  const char *gas_phase_species_name;  /* The species in the gas phase to add the converted volume to. */
  int maxspe;                      /* Lowest number of species found in any thread's material. */
  cxboolean average_enthalpy_p;    /* Whether to average the (specific) enthalpy or just temperature. */
  char *lump_conv_trn;             /* name of the "sampling" file to write when parcels are created. */
} lump_det_param_set_t;


/* Following is defined here for the
 * use of DEFINE_DPM_OUTPUT in
 * VOF-to-DPM:
 */
typedef struct convert_lump_args_struct
{
  Domain *domain;
  int last_lump_id;      /* starting from 1 (one), not 0 (zero)...! */
  real **lump_summ;      /* First index is lump_prop_indx_t, second is lump id */
  real **lumspesumm;     /* First index is species, second is lump id */
  lump_det_param_set_t myldps;       /* cf. above */
} convert_lump_args_type;


FLUENT_EXPORT extern convert_lump_args_type convert_lump_args;


typedef enum
{
  LPI_VOL_DIAM,   /* accumulate volume, calc & store diameter */
  LPI_MASS_RHO,
  ND_VEC(LPI_X,
         LPI_Y,
         LPI_Z),
  ND_VEC(LPI_U,
         LPI_V,
         LPI_W),
  LPI_T,
  LPI_H,
  LPI_PforTfromH,  /* Pressure, needed to calculate a temperature from an enthalpy using Temperature(..).. */
  LPI_MAX_N,
  /* End of characteristics that somehow go into the Lagrangian parcel;
   * Following below are those "Asphericity" characteristics for automatic election:
   */
  LPI_RAD = LPI_MAX_N,   /* Don't produce a gap because of the "LPI_MAX_N" above...
                          * accumulate abs(radius) weighted by surface area;
                          *                          calc & store *normalized* by radius from volume, reduced by 1.0 */
  LPI_RAD_SQR_SIG,       /* accumulate SQR(radius) weighted by surface area;
                          *                          calc & store *normalized* (by radius) standard deviation of the radius */
  LPI_SURF_AREA,         /* accumulate surface area; calc & store *normalized* (by sphere surface from diameter from volume) surface area */
  LPI_ORTHOGITY,         /* accumulate "orgthogonality" between radius vector and surface area normal vector, individually normalized by their product
                          * (i.e. the scalar product of the two vectors divided by the product of the absolute values of the two vectors),
                          * weighted by surface area; calc & store 1.0 - the weighted average. */
  LPI_ALL_N,
  LPI_MAXI_VOF = LPI_ALL_N,   /* Must have this after LPI_ALL_N, because this is not summed -- has its own treatment (GRHIGH).. */
  LPI_TOTAL_N
} lump_prop_indx_t;


/* The following is "exported" for dpm_to_vof.c: */
#if  ! ( 00 || LUMP_DET_USE_QUEUE_ARRAY )

#ifndef  _VOF_TO_DPM_H_CATLIST
#define  _VOF_TO_DPM_H_CATLIST

#undef   OBJ
#define  OBJ  cat_t   /* used to define a double-linked list or FIFO buffer ("queue") of cell-and-thread elements */

#define  CX_LIST_TYPE_NAME  catList

#include "cxlist.h"   /* .c is included in vof_to_dpm.c, provides catList even to dpm_to_vof.c */

#undef   CX_LIST_TYPE_NAME

typedef catList *cats_t;

FLUENT_EXPORT cats_t new_cats(void);
FLUENT_EXPORT void free_cats(cats_t cats);
FLUENT_EXPORT void add_cat(cats_t cats, cat_t cat);
FLUENT_EXPORT cat_t pop_cat(cats_t cats);
FLUENT_EXPORT int len_cats(cats_t cats);

#endif   /* ndef _VOF_TO_DPM_H_CATLIST */

#endif   /*  ! ( 00 || LUMP_DET_USE_QUEUE_ARRAY ) */


#include "grid.h"   /* Face_Type_Nkids() */

/* Given a face, the following loops over all child faces,
 * both children in the hanging-node data structures...
 *  and children in the non-conformal interfaces!
 */
#define begin_f_self_or_child_loop(f, t, fk, tk)           \
 { int _k;                                                 \
   single_or_child_or_sichild_face_loop (fk, tk, f, t, _k) \

#define end_f_self_or_child_loop(f, t, fk, tk)  /* }}} */  }


#define  begin_c_neighbour_loop(cs, cts, c1, ct1)           \
         {                                                  \
           int _cell_ngh_lp_i;                              \
                                                            \
           c_face_loop (cs, cts, _cell_ngh_lp_i)            \
           {                                                \
             face_t   fkid,  _f  = C_FACE(       cs, cts, _cell_ngh_lp_i);  \
             Thread *tfkid, *_ft = C_FACE_THREAD(cs, cts, _cell_ngh_lp_i);  \
                                                            \
             begin_f_self_or_child_loop (_f, _ft, fkid, tfkid) \
             {                                              \
               if (NULL_CELL_P(c1 = get_c_in_f_not_c (fkid, tfkid, cs, cts, &ct1)))  \
                 continue;

#define  end_c_neighbour_loop(cs, cts, c1, ct1) /* }} */ }}}  \
         end_f_self_or_child_loop(f, t, fk, tk)


#endif /* _FLUENT_VOF_TO_DPM_H */

