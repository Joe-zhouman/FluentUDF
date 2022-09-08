/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_OVERSET_H
#define _FLUENT_OVERSET_H

#if RP_OVERSET

#include "mesh_flags.h"

#define C_OVERSET_BD(_c,_t) C_STORAGE_R(_c,_t,SV_OVERSET_BD)
#define C_OVERSET_SIZE_RATIO(_c,_t) C_STORAGE_R(_c,_t,SV_OVERSET_SIZE_RATIO)
#define F_OVERSET_WEIGHT(_f,_t) F_STORAGE_R(_f,_t,SV_OVERSET_WEIGHT)

#define OVERSET_CELL_FLAGS  (OVERSET_CELL_FL_SOLVE | \
                             OVERSET_CELL_FL_RECEPTOR | \
                             OVERSET_CELL_FL_DONOR | \
                             OVERSET_CELL_FL_ORPHAN | \
                             OVERSET_CELL_FL_DEAD | \
                             OVERSET_CELL_FL_SOLVE_OLD | \
                             OVERSET_CELL_FL_RECEPTOR_OLD | \
                             OVERSET_CELL_FL_DEAD_OLD | \
                             OVERSET_CELL_FL_RENDER | \
                             OVERSET_CELL_FL_DONOR_POST)

#define OVERSET_SOLVE_CELL_P(_c,_t)        (C_ENTITY_FLAGS(_c,_t) & \
                                            OVERSET_CELL_FL_SOLVE)
#define OVERSET_RECEPTOR_CELL_P(_c,_t)     (sg_overset?C_ENTITY_FLAGS(_c,_t) & \
                                            OVERSET_CELL_FL_RECEPTOR:0)
#define OVERSET_DONOR_CELL_P(_c,_t)        (C_ENTITY_FLAGS(_c,_t) & \
                                            OVERSET_CELL_FL_DONOR)
#define OVERSET_ORPHAN_CELL_P(_c,_t)       (C_ENTITY_FLAGS(_c,_t) & \
                                            OVERSET_CELL_FL_ORPHAN)
#define OVERSET_DEAD_CELL_P(_c,_t)         (sg_overset?C_ENTITY_FLAGS(_c,_t) & \
                                            OVERSET_CELL_FL_DEAD:0)
#define OVERSET_SOLVE_OLD_CELL_P(_c,_t)    (C_ENTITY_FLAGS(_c,_t) & \
                                            OVERSET_CELL_FL_SOLVE_OLD)
#define OVERSET_RECEPTOR_OLD_CELL_P(_c,_t) (C_ENTITY_FLAGS(_c,_t) & \
                                            OVERSET_CELL_FL_RECEPTOR_OLD)
#define OVERSET_DEAD_OLD_CELL_P(_c,_t)     (C_ENTITY_FLAGS(_c,_t) & \
                                            OVERSET_CELL_FL_DEAD_OLD)
#define OVERSET_RENDER_CELL_P(_c,_t)       (C_ENTITY_FLAGS(_c,_t) & \
                                            OVERSET_CELL_FL_RENDER)
#define OVERSET_EXTENDED_CELL_P(_c,_t)     (C_ENTITY_FLAGS(_c,_t) & \
                                            OVERSET_CELL_FL_EXTENDED)
#define OVERSET_DONOR_POST_CELL_P(_c,_t)   (C_ENTITY_FLAGS(_c,_t) & \
                                            OVERSET_CELL_FL_DONOR_POST)
#define OVERSET_UNIDENTIFIED_CELL_P(_c,_t) !(OVERSET_SOLVE_CELL_P(_c,_t) || \
                                             OVERSET_RECEPTOR_CELL_P(_c,_t) || \
                                             OVERSET_DEAD_CELL_P(_c,_t))
#define OVERSET_DEAD_TO_SOLVE_CELL_P(_c,_t) (OVERSET_SOLVE_CELL_P(_c,_t) && \
                                             OVERSET_DEAD_OLD_CELL_P(_c,_t))

#define SET_OVERSET_CELL_FLAGS SET_C_ENTITY_FLAGS
#define CLEAR_OVERSET_CELL_FLAGS CLEAR_C_ENTITY_FLAGS
#define OVERSET_CELL_FLAG C_ENTITY_FLAG

/* overset cell plotting marks */
#define OVERSET_SOLVE_CELL         1
#define OVERSET_RECEPTOR_CELL      0
#define OVERSET_DONOR_CELL         2
#define OVERSET_ORPHAN_CELL       -1
#define OVERSET_DEAD_CELL         -2
#define OVERSET_UNIDENTIFIED_CELL -3

#define OVERSET_FACE_FLAGS  (OVERSET_FACE_FL_SOLVE_SOLVE | \
                             OVERSET_FACE_FL_SOLVE_RECEPTOR | \
                             OVERSET_FACE_FL_RECEPTOR_RECEPTOR | \
                             OVERSET_FACE_FL_OVERSET | \
                             OVERSET_FACE_FL_DEAD | \
                             OVERSET_FACE_FL_OVERLAP)

#define OVERSET_SOLVE_FACE_P(_f,_t)             (sg_overset?F_ENTITY_FLAGS(_f,_t) & \
                                                 (OVERSET_FACE_FL_SOLVE_SOLVE | \
                                                  OVERSET_FACE_FL_SOLVE_RECEPTOR | \
                                                  OVERSET_FACE_FL_RECEPTOR_RECEPTOR):1)
#define OVERSET_SOLVE_SOLVE_FACE_P(_f,_t)       (F_ENTITY_FLAGS(_f,_t) & \
                                                 OVERSET_FACE_FL_SOLVE_SOLVE)
#define OVERSET_SOLVE_RECEPTOR_FACE_P(_f,_t)    (F_ENTITY_FLAGS(_f,_t) & \
                                                 OVERSET_FACE_FL_SOLVE_RECEPTOR)
#define OVERSET_SOLVE_DEAD_FACE_P(_f,_t)        (F_ENTITY_FLAGS(_f,_t) & \
                                                 OVERSET_FACE_FL_SOLVE_DEAD)
#define OVERSET_RECEPTOR_RECEPTOR_FACE_P(_f,_t) (F_ENTITY_FLAGS(_f,_t) & \
                                                 OVERSET_FACE_FL_RECEPTOR_RECEPTOR)
#define OVERSET_OVERSET_FACE_P(_f,_t)           (F_ENTITY_FLAGS(_f,_t) & \
                                                 OVERSET_FACE_FL_OVERSET)
#define OVERSET_DEAD_FACE_P(_f,_t)              (F_ENTITY_FLAGS(_f,_t) & \
                                                 OVERSET_FACE_FL_DEAD)
#define OVERSET_OVERLAP_FACE_P(_f,_t)           (F_ENTITY_FLAGS(_f,_t) & \
                                                 OVERSET_FACE_FL_OVERLAP)
#define OVERSET_RENDER_FACE_P(_f,_t)            (F_ENTITY_FLAGS(_f,_t) & \
                                                 OVERSET_FACE_FL_RENDER)
#define OVERSET_EXTENDED_FACE_P(_f,_t)          (F_ENTITY_FLAGS(_f,_t) & \
                                                 OVERSET_FACE_FL_EXTENDED)

#define SET_OVERSET_FACE_FLAGS SET_F_ENTITY_FLAGS
#define CLEAR_OVERSET_FACE_FLAGS CLEAR_F_ENTITY_FLAGS
#define OVERSET_FACE_FLAG F_ENTITY_FLAG

#define NOT_OVERSET_OR_SOLVE_CELL_P(_c,_t) (!sg_overset || \
                                            OVERSET_SOLVE_CELL_P(_c,_t))
typedef struct axis_aligned_bounding_box_struct
{
  real xmin[ND_ND];         /* min corner of axis-aligned bounding box */
  real xmax[ND_ND];         /* max corner of axis-aligned bounding box */
} AABBox;

#define AABB_XMIN(bb) ((bb)->xmin)
#define AABB_XMAX(bb) ((bb)->xmax)

#define OCD_NWEIGHTS 3

/* overset cell donors */
typedef struct overset_cell_donor_struct
{
  Cell *csp;
  real weight[OCD_NWEIGHTS];
  real gradient_weight[ND_ND];
  unsigned int flags;  /* lowest 24 bits (0xffffff) are used to store partition
                          ID, higher bits are used as donor flags */
} Overset_Cell_Donor;

#define C_OVERSET_DONOR(_c,_t) \
  C_STORAGE(_c,_t,SV_OVERSET_DONOR,struct objp_struct **)
#define C_OVERSET_NDONOR(_c,_t) C_STORAGE_I(_c,_t,SV_OVERSET_NDONOR)

#define OCD_FL_PRINCIPAL   (1<<24)
#define OCD_FL_CENTRAL     (1<<25)
#define OCD_FL_USED        (1<<26)
#define OCD_FL_SAME_MESH   (1<<27)

/*bits 29, 30, and 31 are for lsf flag values*/
#define    OCD_LSF_DEF_GRADX       (1<<28)
#define    OCD_LSF_DEF_GRADY       (2<<28)
#define    OCD_LSF_DEF_GRADZ       (4<<28)
#define    OCD_LSF_DEF_GRADXY      (3<<28)
#define    OCD_LSF_DEF_GRADXZ      (5<<28)
#define    OCD_LSF_DEF_GRADYZ      (6<<28)
#define    OCD_LSF_DEF_GRADXYZ     (7<<28)

#define O_P_OCD(objp) ((Overset_Cell_Donor *) O_P(objp))
#define OCD_CSP(ocd) ((ocd)->csp)
#define OCD_WEIGHT(ocd,i) ((ocd)->weight[i])
#define OCD_G_WEIGHT(ocd,i) ((ocd)->gradient_weight[i])
#define OCD_FLAGS(ocd) ((ocd)->flags)
#define OCD_LSF_FLAGS(ocd) ((ocd)->flags)
#define SET_OCD_FLAGS(ocd,_flag) (OCD_FLAGS(ocd) |= (_flag))
#define SET_OCD_LSF_FLAGS(ocd,_flag) (OCD_LSF_FLAGS(ocd) |= (_flag))
#define CLEAR_OCD_FLAGS(ocd,_flag) (OCD_FLAGS(ocd) &= ~(_flag))
#define CLEAR_OCD_LSF_FLAGS(ocd,_flag) (OCD_LSF_FLAGS(ocd) &= ~(_flag))
#define OCD_PRINCIPAL_P(ocd) ((OCD_FLAGS(ocd) & OCD_FL_PRINCIPAL) != 0)
#define OCD_CENTRAL_P(ocd) ((OCD_FLAGS(ocd) & OCD_FL_CENTRAL) != 0)
#define OCD_USED_P(ocd) ((OCD_FLAGS(ocd) & OCD_FL_USED) != 0)
#define OCD_SAME_MESH_P(ocd) ((OCD_FLAGS(ocd) & OCD_FL_SAME_MESH) != 0)

#define OCD_LSF_DEF_GRAD_X(ocd)((OCD_LSF_FLAGS(ocd) & OCD_LSF_DEF_GRADX))
#define OCD_LSF_DEF_GRAD_Y(ocd)((OCD_LSF_FLAGS(ocd) & OCD_LSF_DEF_GRADY))
#define OCD_LSF_DEF_GRAD_Z(ocd)((OCD_LSF_FLAGS(ocd) & OCD_LSF_DEF_GRADZ))

#define OCD_PART(ocd) (OCD_FLAGS(ocd) & 0xffffff)
#define SET_OCD_PART(ocd,_part) (OCD_FLAGS(ocd) = \
                                 ((OCD_FLAGS(ocd) & 0xff000000) | \
                                  ((_part) & 0xffffff)))

#define C_OVERSET_RECEPTOR(_c,_t) \
  C_STORAGE(_c,_t,SV_OVERSET_RECEPTOR,struct objp_struct **)
#define C_OVERSET_NRECEPTOR(_c,_t) C_STORAGE_I(_c,_t,SV_OVERSET_NRECEPTOR)

/* overset bounding cells */
typedef struct overset_bounding_cell_struct
{
  Cell *csp;
  cxindex id;
  int tid;             /* original (parent) thread ID if extended threads are used */
  unsigned int flags;  /* lowest 24 bits (0xffffff) are used to store partition
                          ID, next 2 bits are used as bounding cell flags */
  unsigned int oflags; /* overset cell flags of the bounding cell */
  real priority;
} Overset_Bounding_Cell;

#define C_OVERSET_BCELL(_c,_t) \
  C_STORAGE(_c,_t,SV_OVERSET_BCELL,struct objp_struct **)
#define OBC_FL_VALID       (1<<24)
#define OBC_FL_USED        (1<<25)  /* currently not used */
#define OBC_FL_TMP         (1<<26)
#define OBC_FL_NBR         (1<<27)

#define O_P_OBC(objp) ((Overset_Bounding_Cell *) O_P(objp))
#define OBC_CSP(obc) ((obc)->csp)
#define OBC_ID(obc) ((obc)->id)
#define OBC_TID(obc) ((obc)->tid)
#define OBC_FLAGS(obc) ((obc)->flags)
#define SET_OBC_FLAGS(obc,_flag) (OBC_FLAGS(obc) |= (_flag))
#define CLEAR_OBC_FLAGS(obc,_flag) (OBC_FLAGS(obc) &= ~(_flag))
#define OBC_VALID_P(obc) ((OBC_FLAGS(obc) & OBC_FL_VALID) != 0)
#define OBC_USED_P(obc) ((OBC_FLAGS(obc) & OBC_FL_USED) != 0)
#define OBC_TMP_P(obc) ((OBC_FLAGS(obc) & OBC_FL_TMP) != 0)
#define OBC_NBR_P(obc) ((OBC_FLAGS(obc) & OBC_FL_NBR) != 0)
#define OBC_PART(obc) (OBC_FLAGS(obc) & 0xffffff)
#define SET_OBC_PART(obc,_part) (OBC_FLAGS(obc) = \
                                 ((OBC_FLAGS(obc) & 0xff000000) | \
                                  ((_part) & 0xffffff)))
#define OBC_OFLAGS(obc) ((obc)->oflags)
#define SET_OBC_OFLAGS(obc,_flag) (OBC_OFLAGS(obc) |= (_flag))
#define CLEAR_OBC_OFLAGS(obc,_flag) (OBC_OFLAGS(obc) &= ~(_flag))
#define OBC_SOLVE_CELL_P(obc) (OBC_OFLAGS(obc) & OVERSET_CELL_FL_SOLVE)
#define OBC_DEAD_CELL_P(obc) (OBC_OFLAGS(obc) & OVERSET_CELL_FL_DEAD)
#define OBC_DEAD_OLD_CELL_P(obc) (OBC_OFLAGS(obc) & OVERSET_CELL_FL_DEAD_OLD)
#define OBC_RECEPTOR_CELL_P(obc) (OBC_OFLAGS(obc) & OVERSET_CELL_FL_RECEPTOR)
#define OBC_PRIORITY(obc) ((obc)->priority)
#define OBC_CONTACT_CELL_P(obc) (OBC_OFLAGS(obc) & NARROW_GAP_BLOCKED_CELL_FL)
#define OBC_CONTACT_OLD_CELL_P(obc) (OBC_OFLAGS(obc) & NARROW_GAP_BLOCKED_CELL_FL_OLD)
#define OBC_BLOCKED_NARROW_GAP_CELL_P(obc) (OBC_OFLAGS(obc) & NARROW_GAP_BLOCKED_CELL_FL)
#define OBC_BLOCKED_NARROW_GAP_OLD_CELL_P(obc) (OBC_OFLAGS(obc) & NARROW_GAP_BLOCKED_CELL_FL_OLD)

#if PARALLEL
/* dci cell type
     lowest 24 bits (0xffffff) are used to store the number of donors,
     next 4 bits are used for cell type */
#define C_DCI_TYPE(_c,_t) C_STORAGE_UI(_c,_t,SV_DCI_TYPE)
#define DCI_CELL_FL_SOLVE     (1<<24)
#define DCI_CELL_FL_RECEPTOR  (1<<25)
#define DCI_CELL_FL_DONOR     (1<<26)
#define DCI_CELL_FL_DEAD      (1<<27)
#define C_DCI_NDONOR(_c,_t) ((int)(C_DCI_TYPE(_c,_t) & 0xffffff))
#define SET_DCI_NDONOR(_c,_t,_n) (C_DCI_TYPE(_c,_t) = \
                                   ((C_DCI_TYPE(_c,_t) & 0xff000000) | \
                                    ((_n) & 0xffffff)))
#define DCI_SOLVE_CELL_P(_c,_t) (C_DCI_TYPE(_c,_t) & DCI_CELL_FL_SOLVE)
#define DCI_RECEPTOR_CELL_P(_c,_t) (C_DCI_TYPE(_c,_t) & DCI_CELL_FL_RECEPTOR)
#define DCI_DONOR_CELL_P(_c,_t) (C_DCI_TYPE(_c,_t) & DCI_CELL_FL_DONOR)
#define DCI_DEAD_CELL_P(_c,_t) (C_DCI_TYPE(_c,_t) & DCI_CELL_FL_DEAD)
#define SET_DCI_CELL_FLAGS(_c,_t,_flags) (C_DCI_TYPE(_c,_t) |= (_flags))

/* dci cell donors */
typedef struct dci_cell_donor_struct
{
  cxindex cid;
  int tid;
  unsigned int flags;  /* lowest 24 bits (0xffffff) are used to store partition
                          ID, next 4 bits are used as donor flags */
} DCI_Cell_Donor;

#define C_DCI_DONOR(_c,_t) \
  C_STORAGE(_c,_t,SV_DCI_DONOR,struct objp_struct **)
#define DCI_DONOR_FL_PRINCIPAL   (1<<24)
#define DCI_DONOR_FL_CENTRAL     (1<<25)
#define DCI_DONOR_FL_USED        (1<<26)
#define DCI_DONOR_FL_SAME_MESH   (1<<27)
#define O_P_DCI(objp) ((DCI_Cell_Donor *) O_P(objp))
#define DCI_DONOR_ID(dci) ((dci)->cid)
#define DCI_DONOR_TID(dci) ((dci)->tid)
#define DCI_DONOR_FLAGS(dci) ((dci)->flags)
#define SET_DCI_DONOR_FLAGS(dci,_flag) (DCI_DONOR_FLAGS(dci) |= (_flag))
#define CLEAR_DCI_DONOR_FLAGS(dci,_flag) (DCI_DONOR_FLAGS(dci) &= ~(_flag))
#define DCI_DONOR_PRINCIPAL_P(dci) ((DCI_DONOR_FLAGS(dci) & DCI_DONOR_FL_PRINCIPAL) != 0)
#define DCI_DONOR_CENTRAL_P(dci) ((DCI_DONOR_FLAGS(dci) & DCI_DONOR_FL_CENTRAL) != 0)
#define DCI_DONOR_USED_P(dci) ((DCI_DONOR_FLAGS(dci) & DCI_DONOR_FL_USED) != 0)
#define DCI_DONOR_SAME_MESH_P(dci) ((DCI_DONOR_FLAGS(dci) & DCI_DONOR_FL_SAME_MESH) != 0)
#define DCI_DONOR_PART(dci) (DCI_DONOR_FLAGS(dci) & 0xffffff)
#define SET_DCI_DONOR_PART(dci,_part) (DCI_DONOR_FLAGS(dci) = \
                                       ((DCI_DONOR_FLAGS(dci) & 0xff000000) | \
                                        ((_part) & 0xffffff)))

#define F_DCI_WEIGHT(_f,_t) F_STORAGE_R(_f,_t,SV_DCI_WEIGHT)
#endif /* PARALLEL */

enum
{
  OT_CELL_THREAD          = 0,
  OT_INTERIOR_FACE_THREAD = 1,
  OT_OVERSET_FACE_THREAD  = 2,
  OT_CUT_FACE_THREAD      = 3,
  OT_PASSIVE_FACE_THREAD  = 4
};

typedef struct overset_thread_struct
{
  struct thread_struct *thread;
  struct thread_struct *extended_thread;
  struct thread_struct *extended_interior_thread; /*filled for cell threads */
  int type;
  int id_parent;
  int priority;
  real xmin[ND_ND];  /* min corner of global axis-aligned bounding box */
  real xmax[ND_ND];  /* max corner of global axis-aligned bounding box */
#if RP_NODE
  real *ll0;         /* local cell max length scale, available on all processes */
  real *xlmin;       /* min corner of local axis-aligned bounding box, available
                        on all processes */
  real *xlmax;       /* max corner of local axis-aligned bounding box, available
                        on all processes */
  int *bmap_nxyz;    /* resolution of bit array covering local axis-aligned
                        bounding box, available on all processes */
  int *bmap_size;    /* size of bit array in words (char),
                        available on all processes */
  char **bmap;       /* bit array covering local axis-aligned bounding box,
                        available on all processes */
#endif
  real xlmin_ext[ND_ND];  /* local axis-aligned bounding box of extended thread */
  real xlmax_ext[ND_ND];  /* local axis-aligned bounding box of extended thread */
  real l0;  /* length scale used in bounding box overlap calculations */
  real h0;  /* average adjacent cell height; used only for cut face threads */
  cxboolean have_cut_seed_cell_p; /* marks cell zones with cut cell seed */
  cxboolean have_poly_cells_p; /* TRUE if associated cell zone has polyhedral cells */
  cxboolean have_hexcore_p; /* TRUE if assoc. cell zone is hexcore (hanging nodes) */
  int user_overlap; /* 0 = auto, 1 = include, -1 = exclude */
  cxboolean feature_angle_filled_p; /* TRUE if feature angle filled on original threads */
  cxboolean extended_feature_angle_filled_p; /* TRUE if feature angle filled on extended threads */
  struct objp_struct *cut_control; /* cut control overset cell thread IDs */
  struct objp_struct *ltf_interior; /* interior face threads of overset thread */
  struct objp_struct *ltf_overset;  /* overset type boundary face threads */
  struct objp_struct *ltf_cut;      /* hole cutting face threads */
  struct objp_struct *ltf_passive;  /* face threads not used in hole cutting */
} Overset_Thread;

#define O_P_OT(objp) ((Overset_Thread *)O_P(objp))
#define OT_THREAD(ot) ((ot)->thread)
#define OT_EXTENDED_THREAD(ot) ((ot)->extended_thread)
#define OT_EXTENDED_INTERIOR_THREAD(ot) ((ot)->extended_interior_thread)
#define OT_TYPE(ot) ((ot)->type)
#define OT_PARENT_ID(ot) ((ot)->id_parent)
#define OT_PRIORITY(ot) ((ot)->priority)
#define OT_XMIN(ot) ((ot)->xmin)
#define OT_XMAX(ot) ((ot)->xmax)
#define OT_XMIN_EXT(ot) ((ot)->xlmin_ext)
#define OT_XMAX_EXT(ot) ((ot)->xlmax_ext)
#define OT_LENGTH0(ot) ((ot)->l0)
#define OT_HEIGHT0(ot) ((ot)->h0)
#define OT_CUT_SEED_P(ot) ((ot)->have_cut_seed_cell_p)
#define OT_POLY_CELL_P(ot) ((ot)->have_poly_cells_p)
#define OT_HEXCORE_P(ot) ((ot)->have_hexcore_p)
#define OT_USER_OVERLAP(ot) ((ot)->user_overlap)
#define OT_CUT_CONTROL(ot) ((ot)->cut_control)
#define OT_FEATURE_ANGLE_FILLED_P(ot) ((ot)->feature_angle_filled_p)
#define OT_EXTENDED_FEATURE_ANGLE_FILLED_P(ot) ((ot)->extended_feature_angle_filled_p)
#define OT_TF_INTERIOR(ot) ((ot)->ltf_interior)
#define OT_TF_OVERSET(ot) ((ot)->ltf_overset)
#define OT_TF_CUT(ot) ((ot)->ltf_cut)
#define OT_TF_PASSIVE(ot) ((ot)->ltf_passive)

typedef struct overset_interface
{
  char name[MAX_NAME_LENGTH];
  struct objp_struct *bg;        /* background meshes */
  struct objp_struct *comp;      /* component meshes */
  struct objp_struct *all;       /* combined list of comp and bg meshes */
  cxboolean stationary_p;        /* interface with no mesh motion */
  cxboolean solid_body_motion_p; /* some zones have moving or dynamic mesh motion*/
  cxboolean thin_two_five_p;     /* thin (one- or two-element thick) 2.5D interface */
  cxboolean symm_two_five_p;     /* 2.5D interface with symmetry top and bottom zones */
  cxboolean intersected_p;       /* intersected interface */
  cxboolean bcells_filled_p;     /* TRUE if bounding cells filled */
  int nbcells_max;               /* max number of bounding cells any cell can have */
  cxboolean marked_overlaps_p;   /* TRUE if any cut faces are marked for overlaps */
  cxboolean extended_cut_threads_filled_p;   /* TRUE if extended threads filled */
  cxboolean extended_donor_threads_filled_p; /* TRUE if extended threads filled */
#if PARALLEL
  cxboolean dci_filled_p;        /* TRUE if DCI is filled */
#endif
  struct overset_interface *next;
} Overset_Interface;

#define OI_NAME(oi) ((oi)->name)
#define OI_BG_OBJP(oi) ((oi)->bg)
#define OI_COMP_OBJP(oi) ((oi)->comp)
#define OI_ALL_OBJP(oi) ((oi)->all)
#define OI_STATIONARY_P(oi) ((oi)->stationary_p)
#define OI_SOLID_BODY_MOTION_P(oi) ((oi)->solid_body_motion_p)
#define OI_THIN_TWO_FIVE_P(oi) ((oi)->thin_two_five_p)
#define OI_SYMM_TWO_FIVE_P(oi) ((oi)->symm_two_five_p)
#define OI_INTERSECTED_P(oi) ((oi)->intersected_p)
#define OI_BCELLS_FILLED_P(oi) ((oi)->bcells_filled_p)
#define OI_NBCELLS_MAX(oi) ((oi)->nbcells_max)
#define OI_MARKED_OVERLAPS_P(oi) ((oi)->marked_overlaps_p)
#if PARALLEL
#define OI_DCI_FILLED_P(oi) ((oi)->dci_filled_p)
#endif
#define OI_EXTENDED_CUT_THREADS_FILLED_P(oi) ((oi)->extended_cut_threads_filled_p)
#define OI_EXTENDED_DONOR_THREADS_FILLED_P(oi) ((oi)->extended_donor_threads_filled_p)

#define loop_oi(oi,domain)\
  loop (oi,domain->overset_interfaces)

FLUENT_EXPORT Objp *oi_all_objp(Overset_Interface *, cxboolean);
FLUENT_EXPORT Overset_Interface *Get_Overset_Interface_From_Thread(Domain *, Thread *);
FLUENT_EXPORT void Get_Overset_Component_Zones(Domain *, Objp **);
FLUENT_EXPORT cxboolean Check_Overset_Boundary_Threads(Domain *);
FLUENT_EXPORT cxboolean Overset_Interface_Face_Thread_P(Thread *);
FLUENT_EXPORT cxboolean Overset_Interface_Cut_Face_Thread_P(Thread *);
FLUENT_EXPORT cxboolean Overset_Interface_Cell_Thread_P(Thread *);
FLUENT_EXPORT void Create_Overset_Interface(Domain *, Pointer);
FLUENT_EXPORT void Update_Overset_Interface(Domain *, Pointer);
FLUENT_EXPORT void Delete_Overset_Interface(Domain *, Pointer);
FLUENT_EXPORT void Intersect_Overset_Interface(Domain *, Pointer, cxboolean);
FLUENT_EXPORT void Intersect_All_Overset_Interfaces(Domain *, cxboolean, cxboolean, cxboolean);
FLUENT_EXPORT void Reintersect_All_Overset_Interfaces(Domain *);
FLUENT_EXPORT void Get_Overset_Donor_Min_Max(int *, int *);
FLUENT_EXPORT void Clear_Overset_Interface(Domain *, Pointer, cxboolean, cxboolean, cxboolean);
FLUENT_EXPORT void Clear_All_Overset_Interfaces(Domain *, cxboolean, cxboolean, cxboolean, cxboolean, cxboolean, cxboolean, cxboolean);
#if PARALLEL
FLUENT_EXPORT void Fill_Overset_DCI(Domain *, cxboolean);
FLUENT_EXPORT void Free_Overset_DCI(Domain *);
FLUENT_EXPORT void Update_All_Overset_Interfaces_From_DCI(Domain *);
FLUENT_EXPORT void Write_Overset_DCI(Domain *, char *);
#endif
FLUENT_EXPORT void Overset_Update_Storage(Domain *);
FLUENT_EXPORT void List_Overset_Interface(Domain *, char *);
FLUENT_EXPORT void Write_Overset_Cell_Counts(Domain *, const char *);
FLUENT_EXPORT void Write_Overset_Cell_Types(Domain *, const char *);
FLUENT_EXPORT unsigned int Overset_Get_Temporary_Cell_Entity_Tmp_Flag(void);
FLUENT_EXPORT unsigned int Overset_Get_Temporary_Cell_Entity_Mark0_Flag(void);
FLUENT_EXPORT unsigned int Overset_Get_Temporary_Cell_Entity_Mark1_Flag(void);
FLUENT_EXPORT unsigned int Overset_Get_Temporary_Cell_Entity_Mark2_Flag(void);
#if PARALLEL
FLUENT_EXPORT void Find_Overset_Bounding_Cell(Domain *, cxindex);
FLUENT_EXPORT void Find_All_Overset_Bounding_Cells(Domain *);
#endif
#if RP_NODE
FLUENT_EXPORT void Overset_Update_Bounding_Cell_Pointers(Domain *, int *);
#endif
FLUENT_EXPORT void Overset_Donor_Checksum(Domain *);
FLUENT_EXPORT void Overset_Weighted_Area(Domain *);
FLUENT_EXPORT void Write_Overset_Area_Weights(Domain *, const char *);
FLUENT_EXPORT void Set_Overset_Cell_Mark_Bounds(real *, real);
FLUENT_EXPORT void Get_Overset_Cell_Mark_Bounds(real *, real *);
FLUENT_EXPORT cxindex Mark_Overset_Cells(Domain *, Thread *, unsigned int,
                                         unsigned int, unsigned int);
FLUENT_EXPORT void Overset_Mark_Adaption(Domain *, cxboolean, cxboolean, cxboolean, cxboolean,
                                         cxindex *, cxindex *, cxindex*, cxindex *, cxboolean *, cxboolean);
FLUENT_EXPORT void Overset_Consolidate_Refinement_Coarsening_Marks(Domain *);
FLUENT_EXPORT void Overset_Adapt_Mesh(Domain *, int);
FLUENT_EXPORT void Overset_Register_Adaption_Predicates(cxboolean);
FLUENT_EXPORT void Pre_Overset_Dynamic_Adapt_Mesh(Domain *);
FLUENT_EXPORT cxboolean Overset_Needs_Dynamic_Adapt_Sweep_P(int);
FLUENT_EXPORT void Post_Overset_Dynamic_Adapt_Mesh(Domain *);
FLUENT_EXPORT void Inherit_Overset_Cell_Flags(cell_t *, Thread **, int,
                                              cell_t *, Thread **, int);
FLUENT_EXPORT void Fill_Overset_Tmp_Mark(Domain *, const char *, cxindex);
FLUENT_EXPORT void Fill_Overset_Donor_Size_Ratio(Domain *);
FLUENT_EXPORT void Free_Overset_Donor_Size_Ratio(Domain *);
FLUENT_EXPORT cxboolean Overset_Donor_Size_Ratio_Filled_P(void);
FLUENT_EXPORT void Overset_Set_Store_Flood_Fill_Level(cxboolean);
FLUENT_EXPORT cxboolean Overset_Flood_Fill_Level_Filled_P(void);
FLUENT_EXPORT Svar Overset_Flood_Fill_Level_Svar(void);
FLUENT_EXPORT void Check_Overset_Interfaces(Domain *);
FLUENT_EXPORT int Count_Overset_Interfaces(Domain *);
FLUENT_EXPORT cxboolean Any_Overset_Interface_Intersected_P(Domain *);
FLUENT_EXPORT cxboolean Any_Overset_Interface_Not_Intersected_P(Domain *);
FLUENT_EXPORT cxboolean All_Overset_Interfaces_Intersected_P(Domain *);
FLUENT_EXPORT cxboolean Unintersected_Overset_Interfaces_P(Domain *);
FLUENT_EXPORT cxboolean Overset_Interface_BCells_Filled_P(Domain *, Pointer);
FLUENT_EXPORT cxboolean Any_Overset_Interface_BCells_Filled_P(Domain *);
FLUENT_EXPORT cxboolean Overset_Interface_Extended_Threads_Filled_P(Domain *, Pointer);
FLUENT_EXPORT cxboolean Any_Overset_Interface_Extended_Threads_Filled_P(Domain *);
#if PARALLEL
FLUENT_EXPORT cxboolean Any_Overset_DCI_Filled_P(Domain *);
FLUENT_EXPORT cxboolean All_Overset_DCI_Filled_P(Domain *);
#endif
FLUENT_EXPORT void Incremental_Overset_Neighborhood(Domain *domain);
FLUENT_EXPORT cxboolean Overset_Interface_Stationary_P(Domain *, Pointer);
FLUENT_EXPORT cxboolean Any_Overset_Interface_Stationary_P(Domain *);
FLUENT_EXPORT cxboolean Check_Orphan_Overset_Boundary(Domain *, cxboolean);
FLUENT_EXPORT cxboolean Check_Solid_Zones_In_Overset(Domain *, cxboolean);
FLUENT_EXPORT cxboolean Check_Mesh_Interface_In_Overset(Domain *, cxboolean);
FLUENT_EXPORT cxboolean Check_Mesh_Interface_Overset_Proximity(Domain *, cxboolean);
FLUENT_EXPORT cxboolean Check_Periodic_Boundary_In_Overset(Domain *, cxboolean);
FLUENT_EXPORT cxboolean Check_Overset_Orphan_Cells(Domain *, int, cxboolean, cxboolean, cxboolean, cxboolean *);
FLUENT_EXPORT cxboolean Check_Overset_Dead_To_Solve_Cells(Domain *, int, cxboolean);
FLUENT_EXPORT cxboolean Check_Overset_Dead_Zones(Domain *, Overset_Interface *, cxboolean);
FLUENT_EXPORT cxboolean Check_Overset_Donor_Receptor_Connectivity(Domain *, int);
FLUENT_EXPORT cxboolean Check_Overset_Donor_Receptor_Size_Change(Domain *, int);
FLUENT_EXPORT cxboolean Check_Overset_Dead_Solve_Cell_Adjacency(Domain *, cxboolean, int);
FLUENT_EXPORT cxboolean Find_Donor_Cell_At_Location(cell_t *receptor_cell, Thread **receptor_thread, real pos[3], real delta_t);
FLUENT_EXPORT void get_overset_major_donor_cell(const cell_t c_receptor, Thread *tc_receptor, cell_t *c, Thread **tc);
#if RP_NODE
FLUENT_EXPORT void Add_Overset_Donor_Cells_Int_Ext(Domain *);
FLUENT_EXPORT void Fill_Overset_Exchange_Lists(Domain *);
#endif
FLUENT_EXPORT void Overset_Update_Cell_Donor_Pointers(Domain *);
FLUENT_EXPORT void Overset_Free_Extended_Entities(Domain *, cxboolean, cxboolean);
#if RP_NODE
FLUENT_EXPORT void Overset_Free_Extended_Entity_Hash_Tables(Domain *, cxboolean, cxboolean, cxboolean);
FLUENT_EXPORT void Mark_Overset_Dangling_Donor_Entities_Active(Domain *);
#endif
FLUENT_EXPORT void Overset_Free_Bounding_Cells(Domain *);
FLUENT_EXPORT cxboolean Overset_Neighborhood_Optimization_Permissible_P(Domain *);
FLUENT_EXPORT void Update_Overset_Render_Flag(Domain *);
#if PARALLEL
FLUENT_EXPORT void Find_Cell_With_ID(cxindex, cxboolean);
FLUENT_EXPORT void Find_Donors_With_ID(cxindex, cxboolean);
FLUENT_EXPORT void Find_Cell_With_Centroid(real *, real, cxboolean);
#endif
FLUENT_EXPORT void Set_Overset_BD_Needs_Update(cxboolean);
FLUENT_EXPORT cxboolean Overset_BD_Needs_Update_P(void);

FLUENT_EXPORT void Model_Initialize_overset(void);
#if PARALLEL
FLUENT_EXPORT cxboolean Overset_Repartition_Domain_If_Needed(Domain *);
FLUENT_EXPORT void Set_Overset_Needs_Migration(cxboolean);
FLUENT_EXPORT cxboolean Overset_Needs_Migration_P(void);
FLUENT_EXPORT void Set_Migration_Needs_Overset_Update(cxboolean);
FLUENT_EXPORT cxboolean Migration_Needs_Overset_Update_P(void);
FLUENT_EXPORT cxboolean Neighborhood_Needs_Overset_Interface_Lists_Filled_P(Domain *);
FLUENT_EXPORT int Write_HDF_Overset_Section(Domain *, const char *, const char *, int);
FLUENT_EXPORT int Read_HDF_Overset_Section(Domain *, const char *, const char *);
FLUENT_EXPORT void Register_Overset_HDF_Case_IO_Manager(void);
FLUENT_EXPORT void Deregister_Overset_HDF_Case_IO_Manager(void);
FLUENT_EXPORT cxboolean Case_Has_Read_Complete_Overset_DCI(Domain *);
FLUENT_EXPORT void Compat_Update_Overset_DCI_Donor_Flags(Domain *);
FLUENT_EXPORT void Update_Overset_DCI_Partition_Data(Domain *);
FLUENT_EXPORT DCI_Cell_Donor *new_dci(void);
FLUENT_EXPORT Objp *dci_add(DCI_Cell_Donor *, Objp *);
FLUENT_EXPORT void cell_free_dci(cell_t, Thread *);
#endif
#if RP_NODE && RP_HANG
FLUENT_EXPORT cxboolean Overset_Enforce_Memory_Compaction_P(Domain *);
#endif
FLUENT_EXPORT void Test_Polygon_Polygon_Clipping(void);
#endif /* #if RP_OVERSET */

/* For NLT feature */
FLUENT_EXPORT cxboolean Is_Point_In_Cell(real *, cell_t, Thread *);

#endif /* _FLUENT_OVERSET_H */
