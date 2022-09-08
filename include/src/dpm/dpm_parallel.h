/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DPM_PARALLEL_H
#define _FLUENT_DPM_PARALLEL_H

#include "mpmonitor.h"   /* MUTEX_T */
#include "dpm_types.h"
#if 00     /* Use helgrind header file to tell helgrind when thread mutex locks are set? */
/* NOTE: When you use valgrind's helgrind tool to find data race conditions,
 * best make sure you deactivate ordered DPM source term deposition -- also
 * known as "ordered hybrid" parallel DPM particle tracking -- because that
 * uses thread locks in a way that helgrind does not accept as completely
 * safe so that it reports false-positive data race conditions...
 * ALSO, make sure to edit .../vNNN/fluent/fluent/src/dpm/dpm_types.h and
 * deactivate the type check code around check_tp_type_tp + check_pp_type_p,
 * because that would produce tons of true positives in helgrind output...!
 */
#include "/home/jschuetz/ftp/valgrind-3.17.0/include/valgrind.h"
#include "/home/jschuetz/ftp/valgrind-3.17.0/helgrind/helgrind.h"
/* The above file has been modified such that it does not try to #include
 * "valgrind.h" if that has already been done, i.e. __VALGRIND_H is defined.
 * That way, using the absolute path in the TWO #include's above, I do not
 * need to add the valgrind / helgrind directories to the include path...
 */
#else
/* define all the macros now used in Fluent sources as empty:
 */
#define VALGRIND_HG_MUTEX_INIT_POST(_mutex, _mbRec)
#define VALGRIND_HG_MUTEX_LOCK_PRE(_mutex, _isTryLock)
#define VALGRIND_HG_MUTEX_LOCK_POST(_mutex)
#define VALGRIND_HG_MUTEX_UNLOCK_PRE(_mutex)
#define VALGRIND_HG_MUTEX_UNLOCK_POST(_mutex)
#define VALGRIND_HG_MUTEX_DESTROY_PRE(_mutex)
#endif

#define MAX_PARALLEL_DPM_RECURSION_DEPTH (RP_Get_Integer("dpm/parallel/max-recursion-depth"))

/* all neighbors thus made valid for particle relocation
   via "net-wide circulation" in parallel dpm */
#define DPM_NEIGHBOR_P(neighbor) ((((I_AM_NODE_LAST_P ? 0 : myid+1) == pe) || \
                                   ((I_AM_NODE_ZERO_P ? (compute_node_count-1) : \
                                     myid-1) == pe) ||                  \
                                     VALID_NEIGHBOR_EXT_P(neighbor)) && !I_AM_NODE_SAME_P(pe) \
                                  || (NNULLP(neighbor->dpm_Ip[0]) && !I_AM_NODE_SAME_P(pe)) \
                                  || (NNULLP(neighbor->dpm_Ip[1]) && !I_AM_NODE_SAME_P(pe)) )

FLUENT_EXPORT int  Pack_Injection(Injection *, char **, cxboolean);
FLUENT_EXPORT int  Unpack_Injection(Injection *, char *, int, cxboolean,
                                    Injection *injections_list);
FLUENT_EXPORT int  Pack_Particle_List(Particle **, char **, cxboolean);
FLUENT_EXPORT int  Unpack_Particle_List(Particle **, char *, int, cxboolean,
                                        Injection *injections_list);
FLUENT_EXPORT void alloc_particle_buffer(char **buff, size_t buffsize, cxboolean homogeneous_net);
FLUENT_EXPORT int  Get_Injection_Id_From_List(Injection *I, Injection *ilist);
FLUENT_EXPORT Injection *Lookup_Injection_In_List(int id, Injection *ilist);

FLUENT_EXPORT void exchange_particles(Domain *domain, Injection *injections_list);

#if RP_NODE
FLUENT_EXPORT void Distribute_Data_To_Neighbors(void (*  pack_send_buffer)(Dom_Neighbor *neighbor, int neighbor_idx, void *data),
                                                void (*unpack_recv_buffer)(Dom_Neighbor *neighbor, int neighbor_idx, void *data),
                                                void *data);
#endif

FLUENT_EXPORT void dem_hybrid_particle_particle(void (*particle_particle)(Particle *, Particle *));
FLUENT_EXPORT int  Update_DPM_Neighbor_Buffers_In_Injection(Domain *domain, Particle **pl);
FLUENT_EXPORT int  Move_Exchanged_Particles_To_Injection(Domain *domain, Injection *I);
FLUENT_EXPORT fat_t find_face_in_cell(Domain *domain, cell_t cell, Thread *cthread, cxindex face_id);
FLUENT_EXPORT fat_t find_face_in_neighbor_cell(Domain *domain, cell_t cell, Thread *cthread, cxindex face_id, const cxboolean exterior_only);
FLUENT_EXPORT int  Exchange_Particles_In_All_Injections(Domain *domain);
FLUENT_EXPORT void Exchange_Particle_List(Domain *, Particle **);

FLUENT_EXPORT int  abort_trapped_particles(Injection *);
FLUENT_EXPORT int  abort_parallel_levels(Injection *, cxboolean);
FLUENT_EXPORT int Free_Lost_Particle_List(Particle *lost, char *funcname, char *fun);

#if RP_NODE
FLUENT_EXPORT void exchange_migrant_particles(Domain *domain, Injection *injections_list, int *lmigrant);
FLUENT_EXPORT void Free_DPM_Exchange_Buffers(Domain *domain);
#endif

#define NEW_HOST_TO_NODE_PARTICLES TRUE
FLUENT_EXPORT void Host_to_Node_Injections(Injection **);
FLUENT_EXPORT void Node_to_Host_Injections(Injection **);

FLUENT_EXPORT void nodes_to_nodezero_particle_list(Particle **, Injection *);
FLUENT_EXPORT void nodezero_to_nodes_particle_list(Particle **, Injection *);

FLUENT_EXPORT void Locate_Particle_List_In_Cell_List(Domain *domain,
                                                     Particle **pl, Particle **found, Particle **lost, Objp *cell_list);
FLUENT_EXPORT void Locate_Particle_List_In_Cell_List_Using_Global_IDs(Domain *domain,
                                                                      Particle **pl, Particle **found, Particle **lost, Objp *cell_list);

/* if in hybrid */
#if RP_DPM_CACHE && _OPENMP
# define MPT_IN_HYBRID (dpm_par.parallel_hybrid &&      \
                        dpm_par.parallel_nthreads > 1)   /* this is set ONLY in track_particle_chunk() <--
                                                          *                     track_particles_in_loop() <--
                                                          *                     DPM_Compute_Pathlines() <--
                                                          *                     DPM_Iteration()...,
                                                          * ..but it is USED even in DO_LOCATION_HIT_RECORDING,
                                                          * which in turn is used in DPM_Locate_Point_in_Domain()...
                                                          */
# define GET_OMP_THREAD_ID (MPT_IN_HYBRID?omp_get_thread_num():0)
# define GET_OMP_NUM_THRDS (MPT_IN_HYBRID?omp_get_num_threads():1)
#else /* RP_DPM_CACHE && _OPENMP */
# define MPT_IN_HYBRID FALSE
# define GET_OMP_THREAD_ID 0
# define GET_OMP_NUM_THRDS 1
#endif /* RP_DPM_CACHE && _OPENMP */


#if  ! UDF_COMPILER

typedef struct fl_omp_gv_mgt_struct
{
  MUTEX_T mtx;
  int n_vals_alloced;
  int writerequester;
  int n_conc_readers;
  char *conc_readers;
} fl_omp_gv_mgt_t;

#define  DEFINE_FL_OMP_GV_TYPE_T(type, typnam)    \
typedef struct fl_omp_gv_ ## typnam ## _struct {  \
  type *vals;                                     \
  fl_omp_gv_mgt_t mgt;                            \
} fl_omp_gv_ ## typnam ## _t;

DEFINE_FL_OMP_GV_TYPE_T(int,       int)
DEFINE_FL_OMP_GV_TYPE_T(int *,   p_int)
DEFINE_FL_OMP_GV_TYPE_T(real,     real)
DEFINE_FL_OMP_GV_TYPE_T(real *, p_real)

DEFINE_FL_OMP_GV_TYPE_T(void *, p_void)   /* Mostly for internal use. */

FLUENT_EXPORT void   init_fl_omp_gv_p_void(fl_omp_gv_p_void_t *flompgv);

FLUENT_EXPORT void  init_fl_omp_gv_int(fl_omp_gv_int_t *flompgv);
FLUENT_EXPORT int   *get_fl_omp_gv_int(fl_omp_gv_int_t *flompgv);
FLUENT_EXPORT int  *take_fl_omp_gv_int(fl_omp_gv_int_t *flompgv);
FLUENT_EXPORT void leave_fl_omp_gv_int(fl_omp_gv_int_t *flompgv);
FLUENT_EXPORT void  init_fl_omp_gv_p_int(fl_omp_gv_p_int_t *flompgv);
FLUENT_EXPORT int  **get_fl_omp_gv_p_int(fl_omp_gv_p_int_t *flompgv);
FLUENT_EXPORT int **take_fl_omp_gv_p_int(fl_omp_gv_p_int_t *flompgv);
FLUENT_EXPORT void leave_fl_omp_gv_p_int(fl_omp_gv_p_int_t *flompgv);

FLUENT_EXPORT void   init_fl_omp_gv_real(fl_omp_gv_real_t *flompgv);
FLUENT_EXPORT real   *get_fl_omp_gv_real(fl_omp_gv_real_t *flompgv);
FLUENT_EXPORT real  *take_fl_omp_gv_real(fl_omp_gv_real_t *flompgv);
FLUENT_EXPORT void  leave_fl_omp_gv_real(fl_omp_gv_real_t *flompgv);
FLUENT_EXPORT void   init_fl_omp_gv_p_real(fl_omp_gv_p_real_t *flompgv);
FLUENT_EXPORT real  **get_fl_omp_gv_p_real(fl_omp_gv_p_real_t *flompgv);
FLUENT_EXPORT real **take_fl_omp_gv_p_real(fl_omp_gv_p_real_t *flompgv);
FLUENT_EXPORT void  leave_fl_omp_gv_p_real(fl_omp_gv_p_real_t *flompgv);

#endif   /*  ! UDF_COMPILER */


/* USE_DPM_DEBUG_WRITE activates
 * DPMDBGWRT macros so that they
 * write debug output into a file dpmdbg-<node_id>.out.
 * DPMDBGERR macros are similar, but if DEBUG is on, they
 * throw an Error if USE_DPM_DEBUG_WRITE is on or they
 * issue a message to the text console if the latter is not.
 * If DEBUG is off, DPMDBGERR is like DPMDBGWRT, which
 * under that circumstance does not do anything.
 */

#ifndef   USE_DPM_DEBUG_WRITE
# define  USE_DPM_DEBUG_WRITE     00  ||  DEBUG   &&  00
/*arning The FIRST "11" in the above line must become 00 again...!! */
#endif

#if  ! UDF_COMPILER

#if USE_DPM_DEBUG_WRITE
# define DPMDBGWRT(...) dpmdbgwrt(__FILE__, __LINE__, __VA_ARGS__)
FLUENT_EXPORT int dpmdbgwrt(char *filename, int line, char *format, ...);
#else
# define DPMDBGWRT(...) donothing()
/* Must define a STATIC function...
 * static int donothing(void) {};   %* Hopefully, calls to this will be optimized out. *%
 * ...in every .c file that uses this, because only such a static function
 * can be optimized out in the optimized production build!
 *
 * This is needed only if one wants to be able to do...
 *    DPMDBGWRT("something"), <more code>;
 * ...i.e. use a comma after DPMDBGWRT(...).
 * If that is not needed, we can probably do:
 * #define  DPMDBGWRT(...)
 */
#endif

#endif   /*  ! UDF_COMPILER */

#if DEBUG
# if USE_DPM_DEBUG_WRITE
#  define  DPMDBGERR  Error
# else
#  define  DPMDBGERR(...)    fprintf(stderr, __VA_ARGS__), fflush(stderr)
# endif
#else
# define   DPMDBGERR  DPMDBGWRT
#endif

#if RP_NODE && _OPENMP
FLUENT_EXPORT extern int num_thread_locks;
#endif

#define PROTO_LOCK(lock) MPT_LOCK_##lock

typedef enum
{
  PROTO_LOCK(field),
  PROTO_LOCK(random),
  PROTO_LOCK(summary),
  PROTO_LOCK(cloud_element),
  PROTO_LOCK(erosion_accretion),
  PROTO_LOCK(new_particle),
  PROTO_LOCK(deep_copy_particle),
  PROTO_LOCK(particle),
  PROTO_LOCK(report),
  PROTO_LOCK(minmax),
  PROTO_LOCK(display),
  PROTO_LOCK(history),
  PROTO_LOCK(prepend_neighbor_list),
  PROTO_LOCK(rethread_collision_particle),
  PROTO_LOCK(collide_particle_move_bin),
  PROTO_LOCK(c_count),
  PROTO_LOCK(wall_heat_flux),
  PROTO_LOCK(update_cell_temperature),
  PROTO_LOCK(film_objp_access),
  PROTO_LOCK(film_mass_access),
  PROTO_LOCK(film_h_wall_access),
  PROTO_LOCK(film_heat_flux_access),
  PROTO_LOCK(film_height_access),
  PROTO_LOCK(film_mass_m0_access),
  PROTO_LOCK(film_height_m0_access),
  PROTO_LOCK(film_heat_flux_m0_access),
  PROTO_LOCK(film_temperature_m0_access),
  PROTO_LOCK(film_mu_m0_access),
  PROTO_LOCK(film_surf_tension_m0_access),
  PROTO_LOCK(film_p_face_access),
  PROTO_LOCK(film_m_imp_access),
  PROTO_LOCK(reflect_heat_flux_access),
  PROTO_LOCK(store_cx_cell),
  PROTO_LOCK(Uniform_Random),
  PROTO_LOCK(Spawn_Particle),
  PROTO_LOCK(DPM_Memory),
  PROTO_LOCK(generic_property),
  PROTO_LOCK(fn_all_count),
  PROTO_LOCK(COPYTP),
  PROTO_LOCK(CX_Find_Cell_With_Point),
  PROTO_LOCK(Find_Film_Particle_In_Cell),
  PROTO_LOCK(Find_Point_In_Cell),
  PROTO_LOCK(Lookup_Cell_By_Id),
  PROTO_LOCK(location_hits),
  PROTO_LOCK(location_tests),
  PROTO_LOCK(CX_Distance2_Element),
  PROTO_LOCK(free_particle),
  PROTO_LOCK(dist_accumulate),
  PROTO_LOCK(dist_average),
  PROTO_LOCK(MEMORY_STD),
  PROTO_LOCK(Deposit_Cache_Film_Props),
  PROTO_LOCK(Deposit_Cache_Sources),
  PROTO_LOCK(Deposit_Cache_Real),
  PROTO_LOCK(wall_film_uniform_random),
  PROTO_LOCK(Pdf_XY),
  PROTO_LOCK(HYBWP),
  PROTO_LOCK(par_fprintf),
  PROTO_LOCK(CX_Message),
  PROTO_LOCK(ORD_BARR),
  PROTO_LOCK(DPM_Wall_Force),

  PROTO_LOCK(THREADLOCK),
  PROTO_LOCK(PICLETAKER),
  PROTO_LOCK(DEADLOCKTRCR),

  PROTO_LOCK(DEBUGGING),
  MPT_LOCK_MAX
} mpt_lock_type;

/* Only for access to thread locks from UDFs:
 */
FLUENT_EXPORT void Mpt_Lock(mpt_lock_type lockid);
FLUENT_EXPORT void Mpt_Unlock(mpt_lock_type lockid);

#ifndef _UDF
# define _UDF 0
#endif
#if _UDF
# define MPT_LOCK(name)    Mpt_Lock(MPT_LOCK_##name)
# define MPT_UNLOCK(name)  Mpt_Unlock(MPT_LOCK_##name)
#elif RP_DPM_CACHE && (MPT_THREAD || _OPENMP)

# if MPT_THREAD
extern mpt_thread_mutex_t mpt_mutex_lock[MPT_LOCK_MAX];
extern mpt_barrier_t dpm_cloud_element_barrier;
extern mpt_barrier_t dpm_barrier;
extern mpt_barrier_t dpm_particle_barrier;
extern int n_mutex;
# endif /* MPT_THREAD */

# if _OPENMP
extern omp_lock_t mpt_omp_lock[MPT_LOCK_MAX];
extern double mpt_omp_lock_time[MPT_LOCK_MAX];
extern double mpt_omp_lock_wait_time[MPT_LOCK_MAX];
extern double mpt_omp_lock_time_start[MPT_LOCK_MAX];
extern size_t mpt_omp_lock_count[MPT_LOCK_MAX];
extern cxboolean mpt_omp_lock_trace;
extern void Start_MPT_OMP_Lock_Track(cxboolean start);
extern void Reset_MPT_OMP_Lock_Track(void);
extern void Print_MPT_OMP_Lock_Track(void);
# endif /* _OPENMP */

#if RP_NODE
# define DPM_MT (dpm_par.parallel_hybrid)
#else /* RP_NODE */
# define DPM_MT rp_dpm_cache
#endif /* RP_NODE */

/* profile */
# if _OPENMP && USE_FLUENT_PROFILE && defined(PROFILE_THREAD_MAX)
extern double mpt_omp_lock_prof_time_start[PROFILE_THREAD_MAX];
extern int mpt_omp_lock_prof_id[PROFILE_THREAD_MAX];
#define START_OMP_LOCK_PROFILE(_before)                         \
  {                                                             \
    if (MPT_get_profile_flag() && mpt_omp_lock_trace)           \
    {                                                           \
      int _thread_id = MPT_IN_HYBRID?                           \
        omp_get_thread_num():0;                                 \
      if(_thread_id >= 0 && _thread_id < PROFILE_THREAD_MAX)    \
        mpt_omp_lock_prof_time_start[_thread_id] = (_before);   \
    }                                                           \
  }
#define STOP_OMP_LOCK_PROFILE                                           \
  {                                                                     \
    if (MPT_get_profile_flag() && mpt_omp_lock_trace)                   \
    {                                                                   \
      int _thread_id = MPT_IN_HYBRID?                                   \
        omp_get_thread_num():0;                                         \
      if(_thread_id >= 0 && _thread_id < PROFILE_THREAD_MAX)            \
        log_time_used(_thread_id, &mpt_omp_lock_prof_id[_thread_id],    \
                      mpt_omp_lock_prof_time_start[_thread_id],         \
                      Get_Timer(), "MPT_LOCK",                          \
                      "dpm_parallel.c", 0, 1, FALSE);                   \
    }                                                                   \
  }
# else /* _OPENMP && USE_FLUENT_PROFILE */
#define START_OMP_LOCK_PROFILE(_before)
#define STOP_OMP_LOCK_PROFILE
# endif /* _OPENMP && USE_FLUENT_PROFILE */

#if USE_FLUENT_PROFILE && _OPENMP && defined(PROFILE_THREAD_MAX)
# define START_PROFILE_MT(_name)                                        \
  {                                                                     \
    unsigned char if_use_profile = MPT_get_profile_flag();              \
    double _prof_log_time_start = (if_use_profile>2)?Get_Timer():0.0;   \
    const int _start_line = __LINE__

# define STOP_PROFILE_MT(_name)                                         \
  {                                                                     \
    static int _prof_log_id_mt[PROFILE_THREAD_MAX] = {                  \
      -1, -1, -1, -1, -1, -1, -1, -1,                                   \
      -1, -1, -1, -1, -1, -1, -1, -1,                                   \
      -1, -1, -1, -1, -1, -1, -1, -1,                                   \
      -1, -1, -1, -1, -1, -1, -1, -1,                                   \
      -1, -1, -1, -1, -1, -1, -1, -1,                                   \
      -1, -1, -1, -1, -1, -1, -1, -1,                                   \
      -1, -1, -1, -1, -1, -1, -1, -1,                                   \
      -1, -1, -1, -1, -1, -1, -1, -1};                                  \
    if(if_use_profile>2)                                                \
      {                                                                 \
        int _thread_id = MPT_IN_HYBRID? omp_get_thread_num():0;         \
        if(_thread_id >= 0 && _thread_id < PROFILE_THREAD_MAX)          \
          log_time_used(_thread_id, &_prof_log_id_mt[_thread_id],       \
                        _prof_log_time_start, Get_Timer(),              \
                        _name, __FILE__, _start_line, __LINE__, FALSE); \
      }                                                                 \
  }}
#else
# define START_PROFILE_MT(_name)
# define STOP_PROFILE_MT(_name)
#endif /* USE_FLUENT_PROFILE && _OPENMP && defined(PROFILE_THREAD_MAX) */

# define START_PROFILE_MT1 START_PROFILE_MT(__FUNCTION__)
# define STOP_PROFILE_MT1 STOP_PROFILE_MT(__FUNCTION__)

/* lock for omp */
#define MPT_OMP_LOCK(name, lockptr)                             \
  {                                                             \
    double _before = mpt_omp_lock_trace?MPT_wall_time():0.0;    \
    START_OMP_LOCK_PROFILE(_before);                            \
    VALGRIND_HG_MUTEX_LOCK_PRE(lockptr, 0);                     \
    omp_set_lock(lockptr);                                      \
    VALGRIND_HG_MUTEX_LOCK_POST(lockptr);                       \
    if(mpt_omp_lock_trace){                                     \
      mpt_omp_lock_time_start[name] = _before;                  \
      mpt_omp_lock_wait_time[name] +=                           \
        MPT_wall_time()-mpt_omp_lock_time_start[name];          \
      mpt_omp_lock_count[name]++;}                              \
  }

#define MPT_OMP_UNLOCK(name, lockptr)                           \
  {                                                             \
    if(mpt_omp_lock_trace){                                     \
      mpt_omp_lock_time[name] +=                                \
        MPT_wall_time()-mpt_omp_lock_time_start[name];}         \
    VALGRIND_HG_MUTEX_UNLOCK_PRE(lockptr);                      \
    omp_unset_lock(lockptr);                                    \
    VALGRIND_HG_MUTEX_UNLOCK_POST(lockptr);                     \
    STOP_OMP_LOCK_PROFILE;                                      \
  }

/* lock for pthread */
#define MPT_PTHREAD_LOCK(name)                                  \
  {                                                             \
    mpt_thread_mutex_lock(&mpt_mutex_lock[name]);               \
    ++n_mutex;                                                  \
  }

#define MPT_PTHREAD_UNLOCK(name)                                \
  {                                                             \
    mpt_thread_mutex_unlock(&mpt_mutex_lock[name]);             \
  }

#if _UDF
/* compiling a UDF -- MPT_LOCK and MPT_UNLOCK have been defined above */
#else
# if MPT_THREAD && _OPENMP
#define MPT_LOCK_BY_ID(name) if(DPM_MT){                                \
    if(rp_dpm_cache)                                                    \
      {                                                                 \
        MPT_PTHREAD_LOCK(name);                                         \
      }                                                                 \
    else if (MPT_IN_HYBRID)                                             \
      {                                                                 \
        MPT_OMP_LOCK(name, &mpt_omp_lock[name]);                        \
      }                                                                 \
  }

#define MPT_UNLOCK_BY_ID(name) if(DPM_MT){                              \
    if(rp_dpm_cache)                                                    \
      {                                                                 \
        MPT_PTHREAD_UNLOCK(name);                                       \
      }                                                                 \
    else if (MPT_IN_HYBRID)                                             \
      {                                                                 \
        MPT_OMP_UNLOCK(name, &mpt_omp_lock[name]);                      \
      }}


# elif MPT_THREAD /* MPT_THREAD && _OPENMP */

#define MPT_LOCK_BY_ID(name) if(DPM_MT){                                \
    if(rp_dpm_cache)                                                    \
      {                                                                 \
        MPT_PTHREAD_LOCK(name);                                         \
      }}

#define MPT_UNLOCK_BY_ID(name) if(DPM_MT){                              \
    if(rp_dpm_cache)                                                    \
      {                                                                 \
        MPT_PTHREAD_UNLOCK(name);                                       \
      }}

# else /* MPT_THREAD && _OPENMP */

#define MPT_LOCK_BY_ID(name) if(DPM_MT){                                \
    if (MPT_IN_HYBRID)                                                  \
      {                                                                 \
        MPT_OMP_LOCK(name, &mpt_omp_lock[name]);                        \
      }}

#define MPT_UNLOCK_BY_ID(name) if(DPM_MT){                              \
    if (MPT_IN_HYBRID)                                                  \
      {                                                                 \
        MPT_OMP_UNLOCK(name, &mpt_omp_lock[name]);                      \
      }}

# endif /* MPT_THREAD && _OPENMP */
#define MPT_LOCK(name)    MPT_LOCK_BY_ID(MPT_LOCK_##name)
#define MPT_UNLOCK(name)  MPT_UNLOCK_BY_ID(MPT_LOCK_##name)
#endif  /* _UDF */

# ifdef CX_Malloc
# undef CX_Malloc
# endif

# ifdef CX_Realloc
# undef CX_Realloc
# endif

# ifdef CX_Calloc
# undef CX_Calloc
# endif

# ifdef CX_Free
# undef CX_Free
# endif

#define CX_Malloc(s) CX_Malloc_MT((s),__FILE__,__LINE__)
#define CX_Realloc(n,s) CX_Realloc_MT((n),(s),__FILE__,__LINE__)
#define CX_Calloc(n,s) CX_Calloc_MT((n),(s),__FILE__,__LINE__)
#define CX_Free(s) CX_Free_MT((s),__FILE__,__LINE__)
FLUENT_EXPORT void *mtm_malloc(size_t size, void **imanager,
                               char *file, int line);
FLUENT_EXPORT void  mtm_free(void *p, void **imanager,
                             char *file, int line);
FLUENT_EXPORT void *mtm_realloc(void *p, size_t size, void **imanager,
                                char *file, int line);

# if _OPENMP && RP_NODE   /* reminder: still in: #if RP_DPM_CACHE && (MPT_THREAD || _OPENMP) */

#if  ! UDF_COMPILER

#if USE_DPM_DEBUG_WRITE
# define     FLOMP_TAKE_PARTICLE(pp, Tp, ...)  (DPMDBGWRT(__VA_ARGS__),    flomp_take_Particle(pp, Tp))
# define  FLOMP_RELEASE_PARTICLE(pp, Tp, ...)  (DPMDBGWRT(__VA_ARGS__), flomp_release_Particle(pp, Tp))
# define     FLOMP_TAKE_A_THREAD(my, to, ...)  (DPMDBGWRT(__VA_ARGS__),    flomp_take_a_Thread(my, to))
# define  FLOMP_RELEASE_A_THREAD(ThrdID, ...)  (DPMDBGWRT(__VA_ARGS__), flomp_release_a_Thread(ThrdID))
#else
# define     FLOMP_TAKE_PARTICLE(pp, Tp, ...)                              flomp_take_Particle(pp, Tp)
# define  FLOMP_RELEASE_PARTICLE(pp, Tp, ...)                           flomp_release_Particle(pp, Tp)
# define     FLOMP_TAKE_A_THREAD(my, to, ...)                              flomp_take_a_Thread(my, to)
# define  FLOMP_RELEASE_A_THREAD(ThrdID, ...)                           flomp_release_a_Thread(ThrdID)
#endif

#endif   /*  ! UDF_COMPILER */

FLUENT_EXPORT cxboolean flomp_take_Particle(Particle *pp, Tracked_Particle *Tp);
FLUENT_EXPORT void   flomp_release_Particle(Particle *pp, Tracked_Particle *Tp);
FLUENT_EXPORT cxboolean flomp_take_a_Thread(short myownid, short towaitfor);
FLUENT_EXPORT void   flomp_release_a_Thread(short Thread_ID);

#  if USE_VMALLOC   /* defined by .../vNNN/fluent/fluent/multiport/src/vmalloc.h,
                     * included via ./vNNN/fluent/fluent/src/main/global.h  and
                     *            .../vNNN/fluent/fluent/multiport/src/mport.h.
                     */
#define MTM_MALLOC(x) mtm_malloc((x), Get_OMP_Mem(OM_MEMORY_MANAGER),   \
                                 __FILE__, __LINE__)
#define MTM_FREE(x) mtm_free((x), Get_OMP_Mem(OM_MEMORY_MANAGER),       \
                             __FILE__, __LINE__)
#define MTM_REALLOC(x, y) mtm_realloc((x), (y), Get_OMP_Mem(OM_MEMORY_MANAGER),\
                                      __FILE__, __LINE__);

#  else   /* i.e.,  #if ( ! USE_VMALLOC)... */
#   define MTM_MALLOC(x) CX_Malloc_MT(x, __FILE__, __LINE__)
#   define MTM_FREE(x) CX_Free_MT(x, __FILE__, __LINE__)
#   define MTM_REALLOC(x, y) CX_Realloc_MT(x, y, __FILE__, __LINE__)
/* These CX_..._MT() macros will always use thread locks because
 * in dpm_parallel.c, use_locks_in_malloc() will
 * always return TRUE if ( ! USE_VMALLOC)...
 */
#  endif   /* #  if USE_VMALLOC ... #  else ... */

# else   /* i.e. NOT [ _OPENMP && RP_NODE ]  (all inside  #if RP_DPM_CACHE && (MPT_THREAD || _OPENMP) ) */

#if  ! UDF_COMPILER
#define    FLOMP_TAKE_PARTICLE(pp, Tp, ...)  TRUE
#define FLOMP_RELEASE_PARTICLE(pp, Tp, ...)
#define    FLOMP_TAKE_A_THREAD(my, to, ...)  TRUE
#define FLOMP_RELEASE_A_THREAD(ThrdID, ...)
#endif   /*  ! UDF_COMPILER */

#define MTM_MALLOC(x) CX_Malloc(x)
#define MTM_FREE(x) CX_Free(x)
#define MTM_REALLOC(x, y) CX_Realloc(x, y)

# endif    /* # if _OPENMP && RP_NODE ... # else ... */


# if _OPENMP
typedef struct ordered_barrier_struct
{
  int         n_threads;         /* number of threads for which the data have been allocated */
  int        *n_threads_array;   /* actual number of threads -- each thread gets this from omp_get_num_threads() */
  int        *active_in_group;   /* flag to tell whether any thread still cooperates or has left the group */
  omp_lock_t *perthread_locks;   /* per-thread locks, i.e. one lock for every thread */
} ordered_barrier_t;


extern ordered_barrier_t *depo_cach_order_barr;

ordered_barrier_t *alloc_ordered_barrier(int numthreads);
int                 free_ordered_barrier(ordered_barrier_t *);

void       enter_ordered_barrier      (ordered_barrier_t *the_ord_bar, int thread_id);
void       leave_ordered_barrier      (ordered_barrier_t *the_ord_bar, int thread_id);
void remove_from_ordered_barrier_group(ordered_barrier_t *the_ord_bar, int thread_id);
# endif /* _OPENMP */

#else /* RP_DPM_CACHE && (MPT_THREAD || _OPENMP) */

#define DPM_MT FALSE
#define MPT_LOCK(name)
#define MPT_UNLOCK(name)
#define MPT_IN_HYBRID FALSE
#define MTM_MALLOC(x) CX_Malloc(x)
#define MTM_FREE(x) CX_Free(x)
#define MTM_REALLOC(x, y) CX_Realloc(x, y)

#if  ! UDF_COMPILER

#define    FLOMP_TAKE_PARTICLE(pp, Tp, ...)  TRUE
#define FLOMP_RELEASE_PARTICLE(pp, Tp, ...)
#define    FLOMP_TAKE_A_THREAD(my, to, ...)  TRUE
#define FLOMP_RELEASE_A_THREAD(ThrdID, ...)

#endif   /*  ! UDF_COMPILER */

# define START_PROFILE_MT1 START_PROFILE1
# define STOP_PROFILE_MT1 STOP_PROFILE1

# define START_PROFILE_MT(_name) START_PROFILE(_name)
# define STOP_PROFILE_MT(_name) STOP_PROFILE(_name)

#endif /* RP_DPM_CACHE && (MPT_THREAD || _OPENMP) */

#define MTM_FREE_TEMP(p) if (NNULLP (p)) {MTM_FREE ((char *)p); p = NULL;}

#if  ! UDF_COMPILER
# define CX_Message_MT(...)          do { MPT_LOCK(CX_Message); \
         CX_Message   (__VA_ARGS__);      MPT_UNLOCK(CX_Message); } while (0)
#else
# define CX_Message_MT(format, ...)          do { MPT_LOCK(CX_Message); \
         CX_Message   (format, __VA_ARGS__);      MPT_UNLOCK(CX_Message); } while (0)
#endif

FLUENT_EXPORT void Init_All_DPM_Locks(void);
FLUENT_EXPORT void Destroy_All_DPM_Locks(void);
FLUENT_EXPORT void Allocate_OMP_Mem(int ngroups);
FLUENT_EXPORT void Free_OMP_Mem(void);
FLUENT_EXPORT void **Get_OMP_Mem(int om);

FLUENT_EXPORT void *CX_Malloc_MT  (size_t, char *, int);
FLUENT_EXPORT void *CX_Realloc_MT (void *, size_t, char *, int);
FLUENT_EXPORT void *CX_Calloc_MT  (size_t, size_t, char *, int);
FLUENT_EXPORT void  CX_Free_MT    (void *, char *, int);

FLUENT_EXPORT int get_n_threads(int nparticles, int **masterp,
                                int **group_sizep, int **thread_numberp,
                                int *max_thread_number_per_loopp,
                                cxboolean for_dem);

FLUENT_EXPORT void alloc_init_one_lock_per_thread(int numthreads);
FLUENT_EXPORT void destroy_one_lock_per_thread(void);

struct exchange_param_s
{
  void (* allocated_sendbuf_size) ( size_t *size_allocd,
                                    void    *elements,
                                    size_t   (* element_size) (void *) );

  cxboolean (* pack_to_buffer) ( void **elements,
                                 char   *buff,
                                 size_t  buff_allocd,
                                 int    *buf_size,
                                 size_t  (* element_size) (void *),
                                 void    (* pack_element) (char **, void *, void *),
                                 void   *element_param );

  void (* unpack_from_buffer) ( void **elements,
                                void **last_element,
                                char   *buff,
                                int     buf_size,
                                void   *(* unpack_element) (char **, void *),
                                void   *element_param );

  size_t (* element_size) ( void * );

  void (* pack_element) ( char **buffer,
                          void   *e,
                          void   *element_param );

  void *(* unpack_element) (char **buffer,
                            void   *element_param);

  cxboolean (* exchange_buffers) ( int pe,
                                   char *sendbuf, int sendbuf_size,
                                   char *recvbuf, int recvbuf_size );
};

typedef struct
{
  Injection *dpm_inj;

  /* caching Injection and particle size */
  int I_id;
  Injection *Iorig;
  int sz_p;

} particle_pack_param_t;

void
dpm_particle_set_exchange_param(struct exchange_param_s *param,
                                cxboolean migrating,
                                cxboolean homogeneous_net);

void
exchange_generic_elements( Domain *domain,
                           int n_neighbors,
                           int *neighbor_ranks,
                           struct exchange_param_s *exchange_param,
                           void *element_param );

FLUENT_EXPORT size_t particle_binary_size(void *element);
FLUENT_EXPORT void particle_binary_pack(char **buff, void *element, void *element_param);
FLUENT_EXPORT void *particle_binary_unpack(char **buff, void *element_param);

#endif /* _FLUENT_DPM_PARALLEL_H */

