/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DPM_DIST_H
#define _FLUENT_DPM_DIST_H

#include "global.h"
#include "mem.h"
#include "prop.h"
#include "profile.h"
#include "slide.h"
#include "threads.h"
#include "dpm.h"
#include "dpm_types.h"
#include "dpm_laws.h"
#include "flowf.h"

Pointer lDPMDistTest(void);

/**
 * Variable type specifier.
 * Primitive variables are the physical variables,
 * e.g. velocity, temperature,
 * derived are the statistical evaluations of
 * primitive variables, e.g. mean, variance etc.
 */
typedef enum dpm_dist_var_type_e
{
  DPM_DIST_VAR_PRIMARY,
  DPM_DIST_VAR_DERIVED,
  DPM_DIST_VAR_TYPE_MAX
} DPM_Dist_Var_Type;

/* variable storage type,
   internally, permanent variables come first */
typedef enum dpm_dist_var_storage_spec_e
{
  PERMANENT,
  TEMPORARY,
  STORAGE_SPEC_MAX
} DPM_Dist_Var_Storage_Spec;

/* what should happen with the variable */
typedef enum dpm_dist_var_action_spec_e
{
  DPM_DIST_VAR_UNSPECIFIED_SPEC = 0,
  DPM_DIST_VAR_DELETE,
  DPM_DIST_VAR_ALLOCATE,
  DPM_DIST_VAR_UNALLOCATE,
  DPM_DIST_VAR_MEM_SPEC_MAX
} DPM_Dist_Var_Action_Spec;

typedef enum accum_cmd_spec_e
{
  ACCUM_DONT_ACCUM = -1,
  ACCUM_ADD,
  ACCUM_SUBTRACT,
  ACCUM_CMD_MAX
} Accum_Cmd_Spec;

typedef enum dist_avg_cmd_spec_e
{
  NULL_CMD = -1,
  DO_CELLS,
  DO_FACES,
  DO_NODES,
  DO_CELLS_NO_EXCH,   /* used inside sub-stepping */
  DO_FACES_NO_EXCH,
  DIST_AVG_CMD_MAX
} Dist_Avg_Cmd_Spec;

typedef enum dist_var_time_stat_spec_e
{
  STAT_DONT_CALC,
  STAT_ONLY_ACCUM,
  STAT_CALC_MEAN,
  STAT_CALC_RMS,
  STAT_CALC_VOF,
  STAT_MAX
} Dist_Var_Stat_Mom_Spec;

/*struct p_primitive_var_s;*/
struct dpm_distribution_s;
struct dpm_dist_var_s;

/* retrieve primitive variable */
typedef real (* getvar_fn_t) (struct dpm_dist_var_s *var, Tracked_Particle *tp, int i_dim, face_t, Thread *ft);

typedef void (* accumulate_fn_t) (real *accu, real value, Tracked_Particle *tp, real number, int i_dim, real weight);
typedef void (* average_fn_t) (real *accu, struct dpm_distribution_s *dist, int i_class, int i_dim, int te, Thread *t, real tsratio);
typedef cxboolean (* store_fn_t) (Thread *t);
/* The average_post function does not change the accumulated value! This function is used only for post-processing purposes. */
typedef double (* average_post_fn_t) (real accu, struct dpm_distribution_s *dist, int i_class, int i_dim, int te, Thread *t, Svar sv);

typedef real (* sort_fn_t) (Tracked_Particle *tp, Particle_Variable_ID varid);

typedef void (* name_fn_t) (char *name, int len_name, struct dpm_dist_var_s *var, int i_dim);

typedef cxboolean (* display_fn_t) (const struct dpm_dist_var_s *var, const int i_dim);

typedef real (* node_weight_fn_t) (Node *v, real weight, real c_volume);

/*typedef struct p_primitive_var_s
{
  int dim;
  Particle_Variable_ID varid;
  getvar_fn_t getvar;

} p_primitive_var_t;*/

typedef struct dpm_dist_var_s
{
  int dim;
  Particle_Variable_ID varid;
  getvar_fn_t getvar;
  int index;
  struct dpm_dist_var_s *next;
  struct dpm_dist_var_s *prev;
  DPM_Dist_Var_Type type;
  DPM_Dist_Var_Storage_Spec storage_spec;
  DPM_Dist_Var_Action_Spec action_spec;
  int n_reals;
  /*Dpm_Distribution distribution;*/
  accumulate_fn_t accumulate;
  average_fn_t average;
  average_post_fn_t average_post;
  store_fn_t store;
  node_weight_fn_t get_node_weight;
  average_fn_t cell_average;   /* us20658 unify averaging code */
  struct dpm_dist_var_s *parent;
  char name[CF_NAME_MAX_LEN];
  char pick[CF_NAME_MAX_LEN];
  name_fn_t name_fn;
  name_fn_t pick_fn;
  cxboolean is_defined;
  cxboolean needs_n_particles;
  display_fn_t display;
  char unit[CF_NAME_MAX_LEN]; /* unit's name */
  Dist_Var_Stat_Mom_Spec statistics_level;
} DPM_Dist_Var;

typedef enum pdv_e
{
  PDV_N,            /* sum of number in parcel */
  PDV_T,
  PDV_DIAM,
  PDV_SRC_MASS,
  PDV_USER

} pdv_t;

typedef enum pda_e
{
  PDA_MEAN,
  PDA_VARIANCE,
  PDA_CALORIC_AVERAGE,
  PDA_USER
} pda_t;

typedef enum thread_base_e
{
  CELL_BASED_DIST = 0,
  FACE_BASED_DIST,
  NODE_BASED_DIST
} thread_base_t;

#define DPM_DIST_CLASS_PHRASE_LEN 32
#define DPM_DIST_CLASS_STRING_LEN 32

typedef struct dpm_classification_data_s
{
  /* variable for condition applied */
  Particle_Variable_ID var_id;
  sort_fn_t sort_getvar;
  /* class segmentation */
  real *segmentation;
  /* number of classes */
  int n_class;

  /* Phrase to denote classes.  NULL pointer means to use 'Class'/'class' for name/pick. *//* us20658 */
  char *class_phrase_name;
  char *class_phrase_pick;

  /* support names for classes rather than numbers only
   */
  char **class_name;
  char **class_pick;

} DPM_Classification_Data;

/* dpm distribution definition */
typedef struct dpm_distribution_s
{
  /* organized as double-linked list */
  struct dpm_distribution_s *next;
  struct dpm_distribution_s *prev;
  /* particle classification */
  DPM_Classification_Data classification_data;
  /* index in real array of first particle distribution variable in first class */
  /* double-linked list of particle variables */
  DPM_Dist_Var *first_var;
  DPM_Dist_Var *last_var;

  char name[CF_NAME_MAX_LEN];
  char pick[CF_NAME_MAX_LEN];
  DPM_Dist_Var *n_particles;  /* 2012-08-09 mbraun This is the sum of number_in_parcel, therefore call it n_particles! */
  /* specify basis for accumulation */
  thread_base_t thread_b;
  cxboolean sample;
  cxboolean active;
  cxboolean is_defined;
  Svar svar;
} Dpm_Distribution;

typedef struct dpm_distribution_list_s
{
  Dpm_Distribution *first_dist;
  Dpm_Distribution *last_dist;
} Dpm_Distribution_List;

typedef void *Dist_Handle;

FLUENT_EXPORT Dpm_Distribution_List dpm_distributions;

/* 2012-01-19 ubecker During property calculation, we may access
 * DPM_DIST_VAR storage before any distributions have been defined.
 * Then the new d->svar points to SV_P and may or may not give a
 * segmentation violation.  But v->index is also garbage and so will
 * be the return value.  Need to guard against this: Only use
 * distribution, if it is_defined.
 *
 * Snatch: DPM_DIST_VAR was also understood as a storage access and
 * used as such in many places.
 *
 * Introduce new macro DPM_DIST_VAR_IF_DEFINED for protected storage
 * access for places that may be accessed before the distribution
 * setup occured, like in functions called directly from routines
 * "elsewhere" in the code.
 *
 *    "te"  means thread element; i.e.,  node, face, or cell.
 */
#define DPM_DIST_VAR(te,t,d,v,i_class,i_dim) (T_STORAGE_R_XV(t,(d)->svar,t->dpm_dist[(v)->index] + i_class + i_dim * (d)->classification_data.n_class)[te])
#define DPM_DIST_VAR_IF_DEFINED(et,t,d,v,i_class,i_dim) (((d)->is_defined &&  ! NULLP(THREAD_STORAGE(t, (d)->svar))) ? DPM_DIST_VAR(et,t,d,v,i_class,i_dim) : 0)
/* The addition " &&  ! NULLP(THREAD_STORAGE(t, (d)->svar))" above
 * avoids invalid memory access when e.g. a cell zone is split into two.
 * Those pointers need to be dereferenced for the DPM_DIST_VAR(...) anyway,
 * so with an efficiently optimizing compiler the overhead should be negligible.
 */

/* To access   dist->n_particles.
 * Arguments are of this type: (Dpm_Distribution *dist, int i_class, int te, Thread *t)
 */
#define DPM_DIST_N_PARTICLES(dist, i_class, te, t) DPM_DIST_VAR(te,t,dist,(dist)->n_particles,i_class,0)
/* keep this for backward compatibility of UDFs */
#define DPM_DIST_NUMBER_IN_PARCEL(dist, i_class, te, t) DPM_DIST_VAR(te,t,dist,dist->n_particles,i_class,0)


void
init_dpm_stat(Domain *domain, Var_Attribute *sv);

void
init_dpm_stat_bndry(Domain *domain, Var_Attribute *sv);

void
init_dpm_stat_on_node_thread(Domain *domain, Var_Attribute *sv);

SV_Store_Type
store_dpm_stat(Thread *t, Svar nv);

SV_Store_Type
store_dpm_stat_bndry(Thread *t, Svar nv);

void
dpm_dist_free_thread_memory(Thread *);

FLUENT_EXPORT void
Define_DPM_Dist_Var(Dpm_Distribution *dist,
                    DPM_Dist_Var *var,
                    DPM_Dist_Var *parent,
                    int dim,
                    Particle_Variable_ID varid,
                    getvar_fn_t getvar,
                    accumulate_fn_t accumulate,
                    average_fn_t average,
                    average_fn_t cell_average,  /* us20658 unify averaging code */
                    average_post_fn_t average_post,
                    cxboolean needs_n_particles,
                    cxboolean volume_weighted,
                    store_fn_t store,
                    DPM_Dist_Var_Storage_Spec store_spec,
                    char *name, name_fn_t name_fn,
                    char *pick, name_fn_t pick_fn,
                    display_fn_t display_fn,
                    char *unit_string,
                    Dist_Var_Stat_Mom_Spec statistics_level);

FLUENT_EXPORT void
Register_Distribution(Dpm_Distribution *dist);

FLUENT_EXPORT void
Unregister_Distribution(Dpm_Distribution *dist);

FLUENT_EXPORT cxboolean
Dist_Store_On_Boundary_Threads(Thread *t);

FLUENT_EXPORT cxboolean
Dist_Store_On_Cell_Threads(Thread *t);

FLUENT_EXPORT cxboolean
Dist_Store_On_Node_Thread(Thread *t);

FLUENT_EXPORT cxboolean
Store_Everywhere(Thread *t);

FLUENT_EXPORT void
Release_Classification_Data(DPM_Classification_Data *data);

FLUENT_EXPORT void
DPM_Classification_Linear_Data(DPM_Classification_Data *data, int n, real minvalue, real maxvalue);

FLUENT_EXPORT void
DPM_Classification_Logarithmic_Data(DPM_Classification_Data *data, int n, real minvalue, real maxvalue);

FLUENT_EXPORT void
DPM_Classification_Volumetric_Data(DPM_Classification_Data *data, int n, real minvalue, real maxvalue);

FLUENT_EXPORT void
Define_Distribution(Dpm_Distribution *dist, DPM_Classification_Data *classification, Svar svar, char *name, char *pick);

FLUENT_EXPORT void
Accumulate_Particle(Tracked_Particle *tp, real number, DPM_List *cell_list_p, face_t f, Thread *ft, Accum_Cmd_Spec accum_cmd);

FLUENT_EXPORT void
Average_Distributions(Dist_Avg_Cmd_Spec              do_cells_cmd,
                      Dist_Avg_Cmd_Spec              do_faces_cmd,
                      Dist_Avg_Cmd_Spec unstdy_tracking_nodes_cmd);

FLUENT_EXPORT void
Reset_All_Distributions(void);

FLUENT_EXPORT void
Reset_Sampled_Distributions(int cphase_interaction, int display, int report,
                            Dist_Avg_Cmd_Spec              do_cells_cmd,
                            Dist_Avg_Cmd_Spec              do_faces_cmd,
                            Dist_Avg_Cmd_Spec unstdy_tracking_nodes_cmd);

FLUENT_EXPORT void
Distribute_from_Nodes_to_Cells(Dpm_Distribution *node_dist, Dpm_Distribution *cell_dist);

FLUENT_EXPORT void
Update_Dist_Storage(void);

FLUENT_EXPORT void
Invalidate_Dist_Storage(Thread *thread);

FLUENT_EXPORT int
DPM_Dist_n_Display_Vars(int cftype);

FLUENT_EXPORT void
DPM_Dist_Fill_Display_Vars(CELL_FUNCTION **g, CELL_FUNCTION *f);

FLUENT_EXPORT cxboolean
DPM_Dist_Is_Allocated(DPM_Dist_Var *var, Thread *thread);

FLUENT_EXPORT void
DPM_Dist_Get_Variable(int index, Dpm_Distribution **dist, DPM_Dist_Var **var, int *i_dim, int *i_class);

FLUENT_EXPORT Dpm_Distribution_List *
Get_Dpm_Distributions(void);

FLUENT_EXPORT void
Invalidate_Dist_Handle(Dist_Handle dist_obj, size_t obj_size);

FLUENT_EXPORT void
Remove_DPM_Dist_Var(Dpm_Distribution *dist, DPM_Dist_Var *var);

FLUENT_EXPORT void
Remove_Dpm_Dist(Dpm_Distribution *dist);

FLUENT_EXPORT void
Switch_PVar_Action_Spec(DPM_Dist_Var_Action_Spec old_spec, DPM_Dist_Var_Action_Spec new_spec);

FLUENT_EXPORT cxboolean
Update_Statistics(int cphase_interaction, int display, int report);

/* us20658 have distribution cell functions together
 * with other "Discrete Phase Variables ..."
 */
FLUENT_EXPORT double
cellDistVarI(cell_t c, Thread *t, int index);

FLUENT_EXPORT int
If_DPM_Dist(void);

FLUENT_EXPORT void
InitDPMDistCall(void);


#endif
