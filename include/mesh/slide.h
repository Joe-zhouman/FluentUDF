/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SLIDE_H
#define _FLUENT_SLIDE_H

#include "dll.h"
#if !UDF_COMPILER
#include "prime/tgrid/hash2.h"
#endif

/*typedef enum
{
  SCALAR = 0,
  VECTOR,
  COUPLED_SCALAR,
  COUPLED_RG,
  COUPLED_G
}
Eqn_Type;*/

typedef enum
{
  AREA = 0,
  MASS = 1
} Mpm_Avg;

typedef struct
{
  cxboolean mixing;
  cxboolean scalep;
  Profile_Type prof_type;
  Mpm_Avg avg_method;
  real min;
  real max;
  int bins;
  int bins_requested;
} gcm_g;

typedef struct
{
  cxboolean periodic;
  cxboolean coupled;
  cxboolean pitch_scale;
  cxboolean no_pitch_scale;
  cxboolean face_periodic;
  cxboolean phase_lag_fp;
  cxboolean matching;
  cxboolean mixing;
  cxboolean mapped;
  /* since "static" is a reserved word, "is_static" is used instead */
  cxboolean is_static;
  cxboolean turbo_non_overlap;
  cxboolean boundary_interface;
} si_type_bool;

/* compressed row storage */
typedef struct compressed_row_storage CRS;
struct compressed_row_storage
{
  cxindex *val;  /* stored value */
  int *col;      /* col index */
  int *row;      /* row index */
};

/* interior id map */
typedef struct interior_id_map Interior_Id_Map;
#if !UDF_COMPILER
struct interior_id_map
{
  Hash_Table *id_hash;     /* hash table for lookup */
};
#endif
typedef struct sliding_interface Sliding_interface;
struct sliding_interface
{
  char name[MAX_NAME_LENGTH];

  struct objp_struct *t0; /* def face thread 0 */
  struct objp_struct *t1; /* def face thread 1 */
  struct objp_struct *ti; /* interior face-thread */
  struct objp_struct *tb0;  /* boundary 0 face-thread */
  struct objp_struct *tb1;  /* boundary 1 face-thread */
  struct objp_struct *mti0;      /* mapped interface thread for face thread 0 */
  struct objp_struct *mti1;      /* mapped interface thread for face thread 1 */
  struct objp_struct *mttmp;     /* temporary threads */
  struct objp_struct *texclusion; /* exclusion pairs from 'one to one' interface creations*/
  struct objp_struct *tmoving;    /* moving zones */
  struct objp_struct *mperiodics; /* multiple periodics (in 3d) */
#if RP_3D
  struct objp_struct *cell_faces; /* threads on no-solve */
#endif
  Node *vlow0;  /* node on lower per bound on thread t0 */
  Node *vlow1;  /* node on lower per bound on thread t1 */
  Node *vhigh0; /* node on upper per bound on thread t0 */
  Node *vhigh1; /* node on upper per bound on thread t1 */
  cxboolean check_vhigh0;
  cxboolean check_vhigh1;

  int nshift;     /* to cover top by bot (periods) */
  cxboolean periodic;
  cxboolean matching;
  int type;     /* type of interface */
  si_type_bool *type_bool;      /* boolean of all available interface types */
  gcm_g gcm;                    /*implicit mixing plane - attributes*/

  int compute_node;
  int flags;

  real origin[3];   /* center of rotation or trans origin */
  real axis[3];     /* rot axis or trans direction */
  double pitch0;                  /* periodicity of t0 zone */
  double pitch1;                  /* periodicity of t1 zone */

  /* for mapped interfaces */
  real mapped_tol_length_factor;  /* relative tolerance */
  real mapped_tol;                /* absolute tolerance */

  /* for stretched interfaces */
  struct objp_struct *ti_s;         /* other stretched interior thread */
  struct objp_struct *t_stretched0; /* stretched face threads */
  struct objp_struct *t_stretched1;
  struct objp_struct *tb0_s;        /* stretched left-over wall threads */
  struct objp_struct *tb1_s;
  struct objp_struct *mperiodics_s;
  Node *vl0;                        /* feature nodes with lowest theta */
  Node *vl1;                        /* ...*/

  /* For GTI non-overlapping wall thread split*/
  struct objp_struct *tb0_gti;    /* gti boundary face-thread tb0 */
  struct objp_struct *tb1_gti;    /* gti boundary face-thread tb1 */
  real avgMeridLength;            /* Average Meridional length for splitting non-overlapping wall thread*/

  /* number of periods of central periodic, for full rotation */
  int nper;
  int nper_str;
  /* central periodic threads, for full rotation  */
  struct objp_struct *cperiodic;
  struct objp_struct *cperiodic_s;

  /* number of periods of mperiodic, for full coverage with PS and NPS model.
   Their values will be stored under SI_MAJOR and SI_MINOR */
  int maxnpos;
  int maxnneg;

  struct
  {
    real angle;     /* periodic angle */
    real trans[ND_ND];    /* translation */
    cxboolean rotational; /* rotation face periodic */
    cxboolean major;    /* true if t0 is periodic */
  } fp;

  int side_switch_indicator;    /* whether sides NEED to be switched or not */
  int side_switched;            /* whether sides HAVE BEEN switched or not    */

  Interior_Id_Map *interior_id_map;
  struct sliding_interface *child_major; /* interface exclusively used by stretched interface */
  struct sliding_interface *child_minor; /* interface exclusively used by stretched interface */
  struct sliding_interface *parent;      /* pointer to original stretched interface used by child only*/
  struct sliding_interface *next;
  struct sliding_interface *next_si;
};

/* periodic transformation "matrix" */
typedef struct strans_struct STrans;
struct strans_struct
{
  real rot[3][3];   /* rotation matrix */
  real trans[ND_ND];    /* translation vector */
  real origin[ND_ND];
  cxboolean translate;
  cxboolean rotate;
};

/* interface types */
#define SI_DEFAULT_INTERFACE 0
#define SI_SIDE_PERIODIC_INTERFACE 1
#define SI_SIDE_PERIODIC_WALL_INTERFACE 2
#define SI_FACE_PERIODIC_INTERFACE 3
#define SI_COUPLED_INTERFACE 4
#define SI_MIXED_INTERFACE 5
#define SI_STRETCHED_INTERFACE 6
#define SI_PHASE_LAG_FACE_PERIODIC_INTERFACE 7
#define SI_PHASE_LAG_SIDE_PERIODIC_INTERFACE 8
#define SI_MAPPED_INTERFACE 9
#define SI_STATIC_INTERFACE 10
#define SI_BOUNDARY_INTERFACE 11

/* interface predicates */
#define DEFAULT_INTERFACE_P(s)\
  ((s)->type == SI_DEFAULT_INTERFACE)
#define SIDE_PERIODIC_INTERFACE_P(s)\
  ((s)->type == SI_SIDE_PERIODIC_INTERFACE)
#define SIDE_PERIODIC_WALL_INTERFACE_P(s)\
  ((s)->type == SI_SIDE_PERIODIC_WALL_INTERFACE)
#define FACE_PERIODIC_INTERFACE_P(s)\
  ((s)->type == SI_FACE_PERIODIC_INTERFACE)
#define COUPLED_INTERFACE_P(s)\
  ((s)->type == SI_COUPLED_INTERFACE)
#define MIXED_INTERFACE_P(s)\
  ((s)->type == SI_MIXED_INTERFACE)
#define STRETCHED_INTERFACE_P(s)\
  ((s)->type == SI_STRETCHED_INTERFACE)
#define IS_MIXING_INTERFACE_P(s)\
  ((s)->gcm.mixing)
#define PHASE_LAG_FACE_PERIODIC_INTERFACE_P(s)\
  ((s)->type == SI_PHASE_LAG_FACE_PERIODIC_INTERFACE)
#define PHASE_LAG_SIDE_PERIODIC_INTERFACE_P(s)\
  ((s)->type == SI_PHASE_LAG_SIDE_PERIODIC_INTERFACE)
#define BOUNDARY_INTERFACE_P(s)\
  ((s)->type == SI_BOUNDARY_INTERFACE)

#define PHASE_LAG_INTERFACE_P(si)\
  (PHASE_LAG_FACE_PERIODIC_INTERFACE_P(si) || \
   PHASE_LAG_SIDE_PERIODIC_INTERFACE_P(si))
#define UNEQUAL_PITCH_INTERFACE_P(si)\
  (STRETCHED_INTERFACE_P(si) ||\
   PHASE_LAG_INTERFACE_P(si))

#define MATCHING_INTERFACE_P(s)\
  ((s)->type_bool->matching)
#define STATIC_INTERFACE_P(s)\
  ((s)->type_bool->is_static)
#define MAPPED_INTERFACE_P(s)\
  ((s)->type_bool->mapped)
#define MAPPED_SLIDING_INTERFACE_P(t) \
  (SLIDING_INTERFACE_THREAD_P ((t)) && \
   NNULLP (PF0_THREAD ((t))) && \
   NNULLP ((PF0_THREAD((t)))->mapped_interface_thread))
#define MAPPED_SLIDING_INTERFACE_WALL_P(t) \
  (SLIDING_INTERFACE_THREAD_P ((t)) && \
   NNULLP (PF0_THREAD ((t))) && \
   (t) == (PF0_THREAD ((t)))->mapped_interface_thread)
#define MAPPED_SLIDING_INTERFACE_LEFTOVER_WALL_P(t) \
  (MAPPED_SLIDING_INTERFACE_P ((t)) && \
   NNULLP (PF0_THREAD ((t))) && \
   (t) != (PF0_THREAD ((t)))->mapped_interface_thread)

#define INTERIOR_INTERFACE_P(s)\
  (DEFAULT_INTERFACE_P(s) ||\
   (s)->type == SI_STATIC_INTERFACE)

#define SI_COMPUTE_NODE(s)((s)->compute_node)

#define SI_FLAG(s,mask)       (((s)->flags & (mask)) == (mask))
#define SET_SI_FLAGS(s,mask)   ((s)->flags |= (mask))
#define CLEAR_SI_FLAGS(s,mask) ((s)->flags &= ~(mask))

/* interface flag section */
#define SI_ROTATIONAL_PERIODIC             0x00002 /* rotational periodicity */
#define SI_TRANSLATIONAL_PERIODIC          0x00004 /* translational periodicity */
#define SI_INITIALIZED_FLAG                0x00008 /* sliding interfac intialized */
#define SI_T0_SLIDE_FLAG                   0x00010 /* thread t0 slides */
#define SI_T1_SLIDE_FLAG                   0x00020 /* thread t1 slides */
#define SI_EMPTY_FLAG                      0x00040 /* intersections are not taken yet */
#define SI_SIDE_PERIODIC_COUPLED_FLAG      0x00080 /* side periodic coupled interface */
#define SI_PITCHSCALE_INTERFACE_FLAG       0x00100 /* pitch scale turbo interface through stretching */
#define SI_PHASE_LAG_FACE_PERIODIC_FLAG    0x00200 /* phase-lag bc interface for periodic bc */
#define SI_PHASE_LAG_SIDE_PERIODIC_FLAG    0x00400 /* phase-lag bc interface for periodic repeats */
#define SI_STATIONARY_INTERFACE_FLAG       0x00800 /* stationary interfaces in transient simulation */
#define SI_PROFILES_STRETCHED_FLAG         0x01000 /* transformed sliding boundaries are stretched */
#define SI_NO_PITCHSCALE_INTERFACE_FLAG    0X02000 /* no pitch scale turbo interface */

#define PITCHSCALE_INTERFACE_P(s)      (STRETCHED_INTERFACE_P(s) && SI_FLAG(s, SI_PITCHSCALE_INTERFACE_FLAG))
#define NO_PITCHSCALE_INTERFACE_P(s)   (STRETCHED_INTERFACE_P(s) && SI_FLAG(s, SI_NO_PITCHSCALE_INTERFACE_FLAG))
/* macros for accessing objp in si structure. */
#define SI_T0_OBJP(si)((si)->t0)
#define SI_T1_OBJP(si)((si)->t1)
#define SI_TI_OBJP(si)((si)->ti)
#define SI_TEXCLUSION_OBJP(si)((si)->texclusion)
#define SI_TB0_OBJP(si)((si)->tb0)
#define SI_TB1_OBJP(si)((si)->tb1)
#define SI_MOVING_OBJP(si) ((si)->tmoving)
#define SI_MTI0_OBJP(si)((si)->mti0)
#define SI_MTI1_OBJP(si)((si)->mti1)
#define SI_MTTMP_OBJP(si) ((si)->mttmp)
#define SI_MPER_OBJP(si)((si)->mperiodics)
#define SI_CPER_OBJP(si)((si)->cperiodic)
#define SI_T0_STR_OBJP(si)((si)->t_stretched0)
#define SI_T1_STR_OBJP(si)((si)->t_stretched1)
#define SI_TI_STR_OBJP(si)((si)->ti_s)
#define SI_TB0_STR_OBJP(si)((si)->tb0_s)
#define SI_TB1_STR_OBJP(si)((si)->tb1_s)
#define SI_MPER_STR_OBJP(si)((si)->mperiodics_s)
#define SI_CPER_STR_OBJP(si)((si)->cperiodic_s)

/* macros for accessing threads in si structure. */
#define SI_T0(si)(O_THREAD(SI_T0_OBJP(si)))
#define SI_T1(si)(O_THREAD(SI_T1_OBJP(si)))
#define SI_TI(si)(O_THREAD(SI_TI_OBJP(si)))
#define SI_TB0(si)(O_THREAD(SI_TB0_OBJP(si)))
#define SI_TB1(si)(O_THREAD(SI_TB1_OBJP(si)))
#define SI_MPER(si)(O_THREAD(SI_MPER_OBJP(si)))
#define SI_CPER(si)(O_THREAD(SI_CPER_OBJP(si)))
#define SI_T0_STR(si)(O_THREAD(SI_T0_STR_OBJP(si)))
#define SI_T1_STR(si)(O_THREAD(SI_T1_STR_OBJP(si)))
#define SI_TI_STR(si)(O_THREAD(SI_TI_STR_OBJP(si)))
#define SI_TB0_STR(si)(O_THREAD(SI_TB0_STR_OBJP(si)))
#define SI_TB1_STR(si)(O_THREAD(SI_TB1_STR_OBJP(si)))
#define SI_MPER_STR(si)(O_THREAD(SI_MPER_STR_OBJP(si)))
#define SI_CPER_STR(si)(O_THREAD(SI_CPER_STR_OBJP(si)))
#define SI_MAJOR(si) ((si)->child_major)
#define SI_MINOR(si) ((si)->child_minor)
#define SI_PARENT(si) ((si)->parent)

/* macros for accesing phase lag objps, and threads */
#define SI_T0_PHLAG_OBJP SI_T0_STR_OBJP
#define SI_T1_PHLAG_OBJP SI_T1_STR_OBJP
#define SI_TI_PHLAG_OBJP SI_TI_STR_OBJP
#define SI_T0_PHLAG SI_T0_STR
#define SI_T1_PHLAG SI_T1_STR
#define SI_TI_PHLAG SI_TI_STR

/* Macros for accessing objp of newly created turbo gti non-overlapping wall thread after split */
#define SI_TB0_GTI_OBJP(si)((si)->tb0_gti)
#define SI_TB1_GTI_OBJP(si)((si)->tb1_gti)

/* Macros for accessing threads in si tructure for newly created turbo gti non-overlapping wall thread after split */
#define SI_TB0_GTI(si)(O_THREAD(SI_TB0_GTI_OBJP(si)))
#define SI_TB1_GTI(si)(O_THREAD(SI_TB1_GTI_OBJP(si)))

#if RP_PLBC
#define SI_TDIR_PHLAG(si,idir) (idir == IF_RE ? SI_T0_PHLAG(si) : (idir == IB_RE ? SI_T1_PHLAG(si) : NULL))
#define SI_TDIR(si,idir) (idir == IF_RE ? SI_T0(si) : (idir == IB_RE ? SI_T1(si) : NULL))
#endif

/* some more, for accessing si parameters */
#define SI_ROTATIONAL(si)((si)->fp.rotational)
#define SI_TRANSLATIONAL(si)(!SI_ROTATIONAL(si))
#define SI_FP_ANGLE(si)((si)->fp.angle)
#define SI_FP_TRANS(si)((si)->fp.trans)
#define SI_TYPE(si)((si)->type)
#define SI_PITCH0(si)((si)->pitch0)
#define SI_PITCH1(si)((si)->pitch1)
#define SI_NPER(si)((si)->nper)
#define SI_NPER_STR(si)((si)->nper_str)

#define SI_NNEGPER(si)((si)->maxnneg)
#define SI_NPOSPER(si)((si)->maxnpos)

#define SLIDING_INTERFACES(domain) ((domain)->sliding_interfaces)
#define SIS(domain)                ((domain)->sis)
#define loop_si_of_type(si,domain,type)\
  loop (si,domain->sliding_interfaces)\
    if (SI_TYPE(si) == type)

#define loop_si_of_either_type(si,domain,type1,type2)\
  loop (si,domain->sliding_interfaces)\
    if  ((SI_TYPE(si) == type1) || (SI_TYPE(si) == type2))

FLUENT_EXPORT cxboolean Moving_Thread_P (Thread *);
FLUENT_EXPORT real sliding_bnd_area_diff (Domain *, Objp *, Objp *);
FLUENT_EXPORT real Get_Sliding_Bnd_Area_Diff (Domain *, Pointer);
FLUENT_EXPORT void Get_Sliding_Interface(Domain *, const char *, int *, char **, int *);
FLUENT_EXPORT Pointer Identify_Mapped_Interface_Threads(Domain *, Pointer);
FLUENT_EXPORT int SI_Creation_For_Shell(Domain *, Thread *, Thread *, char *);
FLUENT_EXPORT Pointer Create_Sliding_Interface(Domain *, Pointer, cxboolean);
FLUENT_EXPORT Pointer Auto_Pairing_Update_Sliding_Interface(Domain *, Pointer);
FLUENT_EXPORT Pointer Auto_Pairing_Delete_Sliding_Interface(Domain *, Pointer);
FLUENT_EXPORT void Update_Si_Structure(Domain *, Sliding_interface *, Objp *, cxboolean);
FLUENT_EXPORT Pointer Exclusion_Sliding_Interface(Domain *, Pointer);
FLUENT_EXPORT void Free_Sliding_Interface_Dump(Domain *);
FLUENT_EXPORT void Delete_Sliding_Interface(Domain *, Pointer);
FLUENT_EXPORT void Delete_List_of_Sliding_Interfaces(Domain *, Objp *);
FLUENT_EXPORT void Delete_All_Sliding_Interfaces(Domain *);
FLUENT_EXPORT void Delete_All_Old_Sliding_Interfaces(Domain *);
FLUENT_EXPORT void Clear_Sliding_Interfaces(Domain *, cxboolean full);
FLUENT_EXPORT void List_Sliding_Interfaces(Domain *);
FLUENT_EXPORT Thread *Create_Stretched_Thread (Domain *, int *, cxboolean *,
                                               cxboolean, Thread *, Thread *);
FLUENT_EXPORT Pointer Get_Stretched_Thread_Ids(Domain *, const char *);
FLUENT_EXPORT Pointer Inquire_SI_Periodics(Domain *, const char *, int);
FLUENT_EXPORT Pointer Inquire_SI_MPer_Angles(Domain *, const char *, int);
#if RP_PLBC
FLUENT_EXPORT Pointer Inquire_Multilayer_Ghost_Face_Threads (Domain *);
#endif

FLUENT_EXPORT cxboolean Is_Moving_P(Domain *);
FLUENT_EXPORT int Count_Nonconformal_Interfaces(Domain *);
FLUENT_EXPORT cxboolean Has_Active_Sliding_Interfaces(Domain *domain);
FLUENT_EXPORT int Count_Default_Interfaces(Domain *);
FLUENT_EXPORT int Count_Stretched_Interfaces(Domain *);
FLUENT_EXPORT cxboolean Check_Orphan_SI_Boundary (Domain *domain, cxboolean verbose);

FLUENT_EXPORT void Slide_Grid(Domain *, real);

FLUENT_EXPORT void Alloc_Thread_Child_Storage(Thread *, int);
FLUENT_EXPORT void Free_Thread_Child_Storage(Thread *);
FLUENT_EXPORT int Create_Sliding_Boundary_Childs_For_Mapped_Interface(Sliding_interface *);
FLUENT_EXPORT int Create_Sliding_Boundary_Childs(Sliding_interface *);
FLUENT_EXPORT void Create_Mapped_Boundary_Childs(Sliding_interface *);
FLUENT_EXPORT void Create_Stretched_Boundary_Childs(Sliding_interface *);
FLUENT_EXPORT cxboolean Check_Duplicate_SB_List(Sliding_interface *);
FLUENT_EXPORT void Fill_SI_Periodic_Parameters (Domain *, Sliding_interface *);
FLUENT_EXPORT void Transform_Point(STrans *const, real [], real []);

FLUENT_EXPORT void set_face_parent_threads (Domain *domain, Sliding_interface *si);
FLUENT_EXPORT void nci_set_face_parent_threads (Domain *domain, Sliding_interface *si);
FLUENT_EXPORT void md_rotate_velocity_and_derivatives_per_dt (Domain  *domain);

FLUENT_EXPORT Thread *find_sb_neighbor (Domain *domain, Thread *sb);
FLUENT_EXPORT void Sliding_Interface_Side_Switch(Domain *);
FLUENT_EXPORT void Single_Sliding_Interface_Side_Switch(Sliding_interface *si);
FLUENT_EXPORT void Set_Sliding_Interface_Side_Switch_Indicator(Domain *);
FLUENT_EXPORT Pointer OList_To_ScmList(Objp *);
#if !UDF_COMPILER
FLUENT_EXPORT cxindex Lookup_Interior_Id_Map(cxindex, cxindex, Interior_Id_Map *);
#endif
#if RP_NODE
FLUENT_EXPORT void Label_Faces_If_No_NC_Metrics_Read (Domain *domain);
#endif
FLUENT_EXPORT void Update_Periodic_Interface_Info(Domain *, Thread *);
FLUENT_EXPORT void Update_Stretched_Interface_Mperiodic_Info (Domain *);
FLUENT_EXPORT int Compute_Face_Periodic_Shift (Domain *, Thread *, Thread *, cxboolean, real *);
FLUENT_EXPORT void Get_Interface_Boundary_Threads (Domain *, int, int *, int *);
FLUENT_EXPORT void Label_Interface_Intersection_Threads (Domain *);
FLUENT_EXPORT Pointer Split_Turbo_NonOverlapping_Wall_Thread (Domain *, int, cxboolean);

#include "intf_stretch.h"

FLUENT_EXPORT void Mesh_Interface_Init_Node_Visit(Domain *domain);
FLUENT_EXPORT void Mesh_Interface_Free_Node_Visit(Domain *domain);
#endif /* _FLUENT_SLIDE_H */
