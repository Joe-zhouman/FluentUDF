/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DPM_TOOLS_H
#define _FLUENT_DPM_TOOLS_H

#include "dll.h"
#include "dpm_types.h"
#include "dpm_parallel.h"

/**
 * @addtogroup dpm Discrete Particle Model
 * @{
 *
 * @file
 * DPM: tools and interface to Discrete Particle Model (dependent on internal types)
 */


#define DEBUG_PARTICLE_LIMITER 0


/* The following is meant to be used in the form...
 *    if (i % 2)
 *      DPM_WARN_IN_TEST(8, "%d is odd", i) */
#ifndef DPM_WARN_IN_TEST

#if RP_NODE
/* Dont't now how to determine whether node is on same machine as host,
 * which is needed for MATRIX_STD and SOLVER_BIN env. var.'s to be there.
 * --> Say "Warning" in non-developer testing, say "DEV Note" otherwise;
 * "Warning" is filtered away by the regression testing perl scripts.
 */
# define  DPM_WARN_IN_TEST_MAY_BE_REMOTE       \
                                          TRUE
/* Following alternative formulation contains
 * another environment variable, appeared to work,
 * but has also been reported to fail recently:
 * (( ! NULLP(getenv("DATABASE_TABLE")))    &&  \
 *  NULLP(strstr(getenv("DATABASE_TABLE"), "dev_fluent")))
 */
#else
# define  DPM_WARN_IN_TEST_MAY_BE_REMOTE  FALSE
#endif

#if  ! UDF_COMPILER

#define DPM_WARN_IN_TEST(_warncount_max, _the_message_, ...)   \
  {                                                               \
    if (dpm_par.warn_in_test)                                        \
    {                                                                   \
      static int _warncount = 0;                                           \
                                                                              \
      /* Restrict to as many instances  */                                       \
      /* as specified as first argument */                                          \
      if (_warncount < _warncount_max)                                                 \
      {                                                                                   \
        ++_warncount;                                                                        \
         /* remove this\______________/to hide messages in regression testing */                \
        CX_Message_MT("\n%s, NOT an Error: %s at %s:%d called on node-%d:\n" _the_message_ ".\n",  \
                      ((dpm_par.particle_relocation <= 3) &&   /* legacy migration, */                \
                       ( (( ! NULLP(getenv("MATRIX_STD"))) &&  /* in regression testing */               \
                          ( ! NULLP(getenv("SOLVER_BIN")))) || /* env. var.'s not on remote machines..: */  \
                         DPM_WARN_IN_TEST_MAY_BE_REMOTE )  ) ? /* (evaluated <= _warncount_max times..) */     \
                        "Warning" : "DEV Note",   /* DEV Note shows up in regression test, Warning does not. */   \
                      __FUNCTION__, __FILE__, __LINE__, myid, __VA_ARGS__);                                         \
                                                                                                                      \
        if (_warncount_max <= _warncount)                                                                               \
          CX_Message_MT("This message will never appear again from this process during this entire Fluent session.\n\n"); \
      }                                                                                                                   \
    }                                                                                                                     \
  }    /* end of the macro */

#endif   /*  ! UDF_COMPILER */

#endif   /* #ifndef DPM_WARN_IN_TEST */

#define ERR_INT -1000000000

#define ALMOST_ZERO 1.e-20
/* used in UNIT_VECT() applied to face area normal vector, which must not be zero for a 10_µm x 10_µm face... */
#define ZEROP(A) (ABS(A) <= ALMOST_ZERO)
#define VZEROP(A) (ZEROP(A[0]) && ZEROP(A[1]) && ZEROP(A[2]))

/* optimization for DBL_EQUAL(A, 0.0) */
#define DPM_DBL_NEAR_ZERO(A) ((A) == 0.0)


/* time relative to the flow solver - only relevant for unsteady tracking with unsteady flow */
#define UNSTEADY_TP_ACCUM_TIME(_tp) ( dpm_par.unsteady_accum_time + (_tp)->tp_accumulated_time )
#define T_DELTA(_tp) ( UNSTEADY_TP_ACCUM_TIME(_tp) - solver_par.flow_time_step )



/* NOTE: The following uses MAG(...), which always uses all 3 (three)
 *       components, even for RP_2D (regardless of rp_axi_swirl etc.)!
 *  ---> In 2d, make sure the third component is initialised (e.g. 0.)!
 */
#define UNIT_VECT(A,R) {if (VZEROP(A)) R[0] = R[1] = R[2] = 0.0; \
      else { \
          real _m; \
        _m = MAG(A); \
            R[0] = A[0]/_m; \
          R[1] = A[1]/_m; \
              R[2] = A[2]/_m; } }


/* have a smaller limit to check for zero vectors in particular for area vectors. */
/* NOTE: The following uses MAG(...), which always uses all 3 (three)
 *       components, even for RP_2D (regardless of rp_axi_swirl etc.)!
 *  ---> In 2d, make sure the third component is initialised (e.g. 0.)!
 */
#define DPM_UNIT_VECT(A,R) {\
                             if ((ABS(A[0]) > 1e3*REAL_MIN) || \
                                 (ABS(A[1]) > 1e3*REAL_MIN) || \
                                 (ABS(A[2]) > 1e3*REAL_MIN))    \
                               { \
               double _m; \
                                 _m = 1./MAG(A); \
         R[0] = A[0]*_m; \
         R[1] = A[1]*_m; \
         R[2] = A[2]*_m; \
                               } \
                             else \
                               R[0] = R[1] = R[2] = 0.; \
                            }


/* NOTE: The following uses MAG(...), which always uses all 3 (three)
 *       components, even for RP_2D (regardless of rp_axi_swirl etc.)!
 *  ---> In 2d, make sure the third component is initialised (e.g. 0.)!
 */
#define DPM_UNIT_VECT_MAG(A,R,M)    \
{           \
  if ((ABS(A[0]) > 1e3*REAL_MIN) ||   \
      (ABS(A[1]) > 1e3*REAL_MIN) ||   \
      (ABS(A[2]) > 1e3*REAL_MIN))   \
    {           \
      double _m;        \
      M = MAG(A);       \
      _m = 1./M;        \
      R[0] = A[0]*_m;       \
      R[1] = A[1]*_m;       \
      R[2] = A[2]*_m;       \
    }           \
  else            \
    R[0] = R[1] = R[2] = M = 0.;    \
}

/**
 * 3-dimensional dot product
 */
#define DOT_PROD(A,B)  (A[0]*B[0] + A[1]*B[1] + A[2]*B[2])

/**
 * 3-dimensional cross product: r = a cross b
 */
#define DPM_V_CROSS(a,b,r)\
        ((r)[0] = (a)[1]*(b)[2] - (b)[1]*(a)[2],\
         (r)[1] = (a)[2]*(b)[0] - (b)[2]*(a)[0],\
         (r)[2] = (a)[0]*(b)[1] - (b)[0]*(a)[1])

/**
 * 3-dimensional norm
 * This uses 3 (three) components regardless of RP_2D and rp_axi_swirl!
 * --> In 2d, please make sure that the third element is initialised (0.)!
 */
#define MAG(A) (sqrt((double)(SQR(A[0])+SQR(A[1])+SQR(A[2]))))

/* Rotate a given 2-d vector (vec0, first arg) around the
 * X axis in 3-d space to the given location (pos),
 * store the result in vec1 (last arg).
 * (in RP_3D, just set vec1 = vec0)
 */
#if RP_2D
#define ROT_VEC_TO_POS( vec0, pos, vec1)                        \
{                                                               \
  if (rp_axi_swirl)                                             \
  {                                                             \
    real R = sqrt((pos)[1] * (pos)[1] + (pos)[2] * (pos)[2]);   \
    if (R > 1.0e-20)                                            \
    {                                                           \
      double _vec01_over_R = (vec0)[1] / R;                     \
      (vec1)[0] = (vec0)[0];                                    \
      (vec1)[1] = _vec01_over_R * (pos)[1];                     \
      (vec1)[2] = _vec01_over_R * (pos)[2];                     \
    }                                                           \
    else                                                        \
      NV_V( (vec1), =, (vec0));                                 \
  }                                                             \
  else                                                          \
    NV_V( (vec1), =, (vec0));                                   \
}
#else
#define ROT_VEC_TO_POS( vec0, pos, vec1) { NV_V( (vec1), =, (vec0) ); }
#endif

#if RP_2D
/* This projects a 3d-tracked point into the 2d plane for axisymmetric
 * cases with stochastic tracking (turbulent diffusion) or swirl:
 */
#define project_axi_to_xy(v_orig,v_proj) \
{ \
  if( rp_axi_swirl ) \
    { \
      (v_proj)[0] = (v_orig)[0]; \
      (v_proj)[1] = sqrt( SQR((v_orig)[1]) + SQR((v_orig)[2]) ); \
    } \
  else \
    NV_V((v_proj),=,(v_orig)); \
  (v_proj)[2] = 0.; \
}
#else
#define project_axi_to_xy(v_orig,v_proj) \
{ NV_V((v_proj),=,(v_orig)); }
#endif

#define zero_mem(addr, size) \
   if(!addr)Message0("\nTry to initialize null pointer at %s:%d\n", __FILE__, __LINE__);\
   else memset(addr, 0, size);

#define FOURTHIRDPI 4.*M_PI/3.

#define DPM_CROSSSECTIONAL_AREA(radius) ((real)(M_PI * SQR(radius)))
#define DPM_SURFACE_AREA(diameter) ((real)(M_PI * SQR(diameter)))
#define DPM_AREA(diameter) ((real)(M_PI * SQR(diameter)))
#define DPM_VOLUME(diameter) ((real) (M_PI / 6.0 * CUB(diameter)))
#define DPM_DIAM_FROM_VOL(v) ((real)pow((6.0 * MAX(0., (v)) / M_PI), 1./3.))

/* roundoff can cause ang > | 1.000... | */
#define LIMIT_ACOS(A) (acos(MAX(-1.0, MIN((A), 1.0))))
#define LIMIT_ASIN(A) (asin(MAX(-1.0, MIN((A), 1.0))))

#define DPM_LOWEST_VOLUME        dpm_par.lowest_volume
#define DPM_LOWEST_DIAMETER      dpm_par.lowest_diam
#if HAVE_OLD_P_MACROS
#define DPM_MINIMUM_DIAMETER(p)  DPM_LOWEST_DIAMETER
#endif

#define TP_DPM_MINIMUM_MASS(tp) (dpm_par.lowest_volume * TP_RHO(tp))
#define PP_DPM_MINIMUM_MASS(pp) (dpm_par.lowest_volume * PP_RHO(pp))
#if HAVE_OLD_P_MACROS
#define    DPM_MINIMUM_MASS(p)  (dpm_par.lowest_volume *  P_RHO(p))
#endif

/* some mesh related macros to get mesh information from previous time step which is not stored */
#define TWOD_AREA_X_M1(v0,v1)(NODE_Y_M1(v1) - NODE_Y_M1(v0))
#define TWOD_AREA_Y_M1(v0,v1)(NODE_X_M1(v0) - NODE_X_M1(v1))

#define AXI_AREA_X_M1(v0,v1)\
((NODE_Y_M1(v1) - NODE_Y_M1(v0))*(NODE_Y_M1(v1) + NODE_Y_M1(v0))/2.)
#define AXI_AREA_Y_M1(v0,v1)\
((NODE_X_M1(v0) - NODE_X_M1(v1))*(NODE_Y_M1(v1) + NODE_Y_M1(v0))/2.)

# define TRI_AREA_i_M1(ND_CROSS_i,v0,v1,v2)(ND_CROSS_i(\
NODE_X_M1(v1) - NODE_X_M1(v0),NODE_Y_M1(v1) - NODE_Y_M1(v0),NODE_Z_M1(v1) - NODE_Z_M1(v0),\
NODE_X_M1(v2) - NODE_X_M1(v0),NODE_Y_M1(v2) - NODE_Y_M1(v0),NODE_Z_M1(v2) - NODE_Z_M1(v0))/2)

# define TRI_AREA_X_M1(v0,v1,v2)TRI_AREA_i_M1(ND_CROSS_X,v0,v1,v2)
# define TRI_AREA_Y_M1(v0,v1,v2)TRI_AREA_i_M1(ND_CROSS_Y,v0,v1,v2)
# define TRI_AREA_Z_M1(v0,v1,v2)TRI_AREA_i_M1(ND_CROSS_Z,v0,v1,v2)

# define QUAD_AREA_i_M1(ND_CROSS_i,v0,v1,v2,v3)(ND_CROSS_i(\
NODE_X_M1(v2) - NODE_X_M1(v0),NODE_Y_M1(v2) - NODE_Y_M1(v0),NODE_Z_M1(v2) - NODE_Z_M1(v0),\
NODE_X_M1(v3) - NODE_X_M1(v1),NODE_Y_M1(v3) - NODE_Y_M1(v1),NODE_Z_M1(v3) - NODE_Z_M1(v1))/2)

# define QUAD_AREA_X_M1(v0,v1,v2,v3)QUAD_AREA_i_M1(ND_CROSS_X,v0,v1,v2,v3)
# define QUAD_AREA_Y_M1(v0,v1,v2,v3)QUAD_AREA_i_M1(ND_CROSS_Y,v0,v1,v2,v3)
# define QUAD_AREA_Z_M1(v0,v1,v2,v3)QUAD_AREA_i_M1(ND_CROSS_Z,v0,v1,v2,v3)

# if RP_2D
#  define FCalc_F_Area_M1(A,f,t)\
  switch (F_NNODES(f,t))\
    {\
    case MIXED_FACE:            /* Accumulated face  */\
    case LINEAR_FACE:   /* 2D face */\
    default: \
      if (rp_axi)\
  {\
    A[0] = AXI_AREA_X_M1(F_NODE(f,t,0),F_NODE(f,t,1));\
    A[1] = AXI_AREA_Y_M1(F_NODE(f,t,0),F_NODE(f,t,1));\
  }\
      else\
  {\
    A[0] = TWOD_AREA_X_M1(F_NODE(f,t,0),F_NODE(f,t,1));\
    A[1] = TWOD_AREA_Y_M1(F_NODE(f,t,0),F_NODE(f,t,1));\
  }\
      break;\
    }

# else /* RP_3D */

#  define FCalc_F_Area_M1(A,f,t)\
  switch (F_NNODES(f,t))\
    {\
    case TRI_FACE:    /* 3D triangular face */\
      {\
  Node *_n0 = F_NODE(f,t,0);\
  Node *_n1 = F_NODE(f,t,1);\
  Node *_n2 = F_NODE(f,t,2);\
  A[0] = TRI_AREA_X_M1(_n0,_n1,_n2);\
  A[1] = TRI_AREA_Y_M1(_n0,_n1,_n2);\
  A[2] = TRI_AREA_Z_M1(_n0,_n1,_n2);\
      }\
      break;\
\
    case QUAD_FACE:   /* 3D quad face */\
      {\
  Node *_n0 = F_NODE(f,t,0);\
  Node *_n1 = F_NODE(f,t,1);\
  Node *_n2 = F_NODE(f,t,2);\
  Node *_n3 = F_NODE(f,t,3);\
  A[0] = QUAD_AREA_X_M1(_n0,_n1,_n2,_n3);\
  A[1] = QUAD_AREA_Y_M1(_n0,_n1,_n2,_n3);\
  A[2] = QUAD_AREA_Z_M1(_n0,_n1,_n2,_n3);\
      }\
      break;\
\
    case MIXED_FACE:            /* Accumulated face  */\
    case POLY_FACE:\
    default:      /* 3D polygonal face */\
      {\
  register int _i;\
  \
  NV_S (A, =, 0.);\
\
  for (_i = 0; _i < F_NNODES(f,t); ++_i)\
    {\
      Node *_n0 = F_NODE (f, t, _i);\
      Node *_n1 = F_NODE (f, t, (_i+1)%F_NNODES(f,t));\
      ND_MAP(A[0],A[1],A[2], +=,\
       (NODE_Y_M1(_n1) + NODE_Y_M1(_n0))*(NODE_Z_M1(_n1) - NODE_Z_M1(_n0)),\
       (NODE_Z_M1(_n1) + NODE_Z_M1(_n0))*(NODE_X_M1(_n1) - NODE_X_M1(_n0)),\
       (NODE_X_M1(_n1) + NODE_X_M1(_n0))*(NODE_Y_M1(_n1) - NODE_Y_M1(_n0)));\
    }\
  NV_S (A, /=, 2.);\
      }\
      break;\
    }
# endif /* RP_3D */

/* macros for looping over particles in a cell    */
/* For spray and PDF Transport where the particle */
/* linked list is ordered by cells                */
#define begin_particle_cell_loop(pp,c,t) \
     { loop(pp, C_STORAGE(c,t,SV_DPM_PARTICLE_BIN,Particle **)) \
         {  \
           if (!PP_REMOVED_P(pp)) {
#define end_particle_cell_loop(pp,c,t) \
                                }\
         }\
     }


/* *************************************************************
 * dpm internal functions/variables */

extern FLUENT_EXPORT common_parameters_t c_par;
extern FLUENT_EXPORT dpm_solver_parameters_t solver_par;
extern FLUENT_EXPORT dpm_injection_parameters_t injection_par;

/* ***** Reporting functions defined in <dpm.c> */
FLUENT_EXPORT void add_to_dpm_summary(Tracked_Particle *tp, Particle_Fate fate, Thread *thread);
FLUENT_EXPORT void add_to_dpm_summary_nolock(Tracked_Particle *tp, Injection *I, Particle_Fate fate, Thread *t);
FLUENT_EXPORT void add_p_to_dpm_summary_fate(Particle *p, Injection *I, Particle_Fate fate);
FLUENT_EXPORT void add_p_to_dpm_summary_fate_nolock(Particle *p, Injection *I, Particle_Fate fate);
FLUENT_EXPORT void add_plist_to_dpm_summary_fate_nolock(Particle *list, Particle_Fate fate);
FLUENT_EXPORT void print_dpm_summary(FILE *report_file, const char *iname, cxboolean want_indomain_particles);
FLUENT_EXPORT void print_pathline_summary(FILE *report_file);
FLUENT_EXPORT void add_two_dpm_summaries(dpm_summary_t *s, dpm_summary_t *t);
FLUENT_EXPORT void Host_to_NodeZero_Summary(void);
#if PARALLEL
FLUENT_EXPORT void nodes_to_nodezero_dpm_summary(Injection *I, int *t_np_total, cxboolean *t_mass_report_p, cxboolean *t_combusting_p, cxboolean *t_wet_combusting_p, cxboolean *t_multiple_surface_p, cxboolean *t_multiple_droplet_p, cxboolean *t_latent_report_p);
#endif
FLUENT_EXPORT void add_to_pathline_summary(Tracked_Particle *tp, Thread *thread);
FLUENT_EXPORT void set_dpm_summary(void);
FLUENT_EXPORT void init_pathline_summary(void);
FLUENT_EXPORT void set_dpm_post_sig_figures(int);
FLUENT_EXPORT void sort_particle_to_file(FILE *sort_file, Tracked_Particle *tp, Thread *thread, Plane *plane);
FLUENT_EXPORT void sort_to_file_header(FILE *sort_file, Thread *thread, Plane *plane, const char *name);
FLUENT_EXPORT void init_dpm_summary(void);
FLUENT_EXPORT void dpm_alloc_per_inj_and_fate_summaries(void);
FLUENT_EXPORT void dpm_alloc_thread_per_inj_summaries(Thread *);
FLUENT_EXPORT void dpm_alloc_all_per_inj_and_fate_or_thread_summaries(void);
FLUENT_EXPORT void dpm_rmv_inj_from_per_inj_summaries(Injection *);

/* ***** eulerian particle solver <dpm_vof.c> */
FLUENT_EXPORT cxboolean Solve_Eulerian(cell_t, Thread *, Tracked_Particle *, int);

/** @addtogroup dpm_tools tools
    @{ */

/**
 * @addtogroup dpm_tools_misc miscellaneous tools
 * @{
 *************************************************************/
FLUENT_EXPORT void string_tolower(char *to_str);
FLUENT_EXPORT void replace_path_chars_in_string(char *to_str);
FLUENT_EXPORT void remove_spaces(int len, char text[]);
FLUENT_EXPORT void set_si_unit(int n, char text[]);
FLUENT_EXPORT void Unmark_All_Cell_Threads(void);
FLUENT_EXPORT void Mark_All_Fluid_Threads(void);
/* have this here to avoid compiler warning from cx_vis.c */
FLUENT_EXPORT int Face_Node_Coord_Real(face_t face, Thread *tface, cell_t cell, Thread *tcell, real time, real *co_ord, int *order);
FLUENT_EXPORT int SV_face_coord_all_real(CX_Cell_Id *c, int f, real time, real *co_ord, int *order);
FLUENT_EXPORT int SV_face_coord_all(CX_Cell_Id *c, int f, float time, float *co_ord, int *order);
FLUENT_EXPORT void perturb_dpm_source(Domain *domain);
/* @} dpm_tools_misc */

/**
 * @addtogroup dpm_tools_numerics numerics
 * @{
 *************************************************************/

#define KMAXX  7
#define IMAXX (KMAXX+1)

typedef struct odeint_work_s
{

  int first;
  int kmax;
  int kopt;
  int nvold;
  real epsold;
  real xnew;

  real a[IMAXX + 1];
  real alf[KMAXX + 1][KMAXX + 1];

  real dextr[KMAXX + 1][KMAXX + 1];
  real xextr[KMAXX + 1];

  void *p;
  cxboolean is_p_particle;

} odeint_work_t;

FLUENT_EXPORT void reset_ode_stats(void);
FLUENT_EXPORT void print_ode_stats(int verbosity);

/* Coupled-Implicit (stiff) ODE integrator */
FLUENT_EXPORT void stiffbs(odeint_work_t *ow, real y[], real dydx[], real (**dfdy),
                           real ymin[], real ymax[], int nv, real *xx, real *htry, real eps,
                           real yscal[], real *hdid, real *hnext, cxboolean calc_jac_in_derivs,
                           void (*derivs) (void *, real, real[], real [], real (* *), cxboolean),
                           void (*jacobn) (void *, real, real [], real (* *),
                                           void (*derivs) (void *, real, real[], real [], real (* *), cxboolean), int));
FLUENT_EXPORT void odeint(odeint_work_t *ow, real ystart[], int nvar, real yscal[], real ymin[], real ymax[],
                          real x1, real x, real eps, real h1, int *nok, int *nbad,
                          cxboolean calc_jac_in_derivs,
                          void (*derivs) (void *, real, real[], real [], real (* *), cxboolean),
                          void (*jacobn) (void *, real, real [], real (* *),
                                          void (*derivs) (void *, real, real[], real [], real (* *), cxboolean), int),
                          void (*steppr) (odeint_work_t *, real [], real [], real (* *), real [], real [], int,
                                          real *, real *, real, real [], real *, real *, cxboolean,
                                          void (*derivs) (void *, real, real[], real [], real (* *), cxboolean),
                                          void (*jacobn) (void *, real, real [], real (* *),
                                                          void (*derivs) (void *, real, real[], real [], real (* *), cxboolean), int)));

/* Cash-Karp Runge-Kutta integrator */
FLUENT_EXPORT int rkck(Tracked_Particle *, real [], real [], int, real, real, real [],
                       real [], int (*derivs)(Tracked_Particle *, real, real [], real []), real *rwork);
FLUENT_EXPORT int rkck_help(Tracked_Particle *tp, real y[], real dydx[], int nv,
                            real x, real h, real yout[], real yerr[],
                            int (*derivs)(Tracked_Particle *, real, real [], real []),
                            real *ak2, real *ak3, real *ak4, real *ak5, real *ak6, real *ytemp );

FLUENT_EXPORT cxboolean DPM_Gauss_Elimination(const int n_rows, const int n_cols, real A[], real X[], real B[], int swap_rows, int rs[]);

FLUENT_EXPORT int Solve_quadratic(double c[3], double roots[]);
FLUENT_EXPORT int Solve_cubic(double C[3], double roots[3], const double t_min, const double t_max);
FLUENT_EXPORT void bSort4(void *base, size_t nmemb, size_t size, int (*compare)(const void *, const void *));
/* @} dpm_tools_numerics */


/**
 * @addtogroup dpm_tools_random random numbers
 * @{
 *************************************************************/
FLUENT_EXPORT real DPM_Uniform_Random(void);
FLUENT_EXPORT real DPM_Gauss_Random(void);
FLUENT_EXPORT real DPM_Uniform_Random_Seeded(uniform_random_seed *);
FLUENT_EXPORT real DPM_Gauss_Random_Seeded(gauss_random_seed *);
FLUENT_EXPORT real dpm_uniform_random(Tracked_Particle *tp);
FLUENT_EXPORT real dpm_uniform_random_on_particle(Particle *p);
FLUENT_EXPORT real dpm_gauss_random(Tracked_Particle *tp);
FLUENT_EXPORT real wall_film_uniform_random_s(Tracked_Particle *tp);

#if (MPT_THREAD || _OPENMP)
FLUENT_EXPORT void Create_Random_Pool(void);
FLUENT_EXPORT void Free_Random_Pool(void);
FLUENT_EXPORT void Return_Random_Pool(Tracked_Particle *tp);
FLUENT_EXPORT int Get_Random_Pool_Size(void);
# endif /*  #if (MPT_THREAD || _OPENMP)  */

FLUENT_EXPORT void randomize_particles_in_array(gauss_random_seed *rand_picles_seed, Particle **p_array, int n_particles);
FLUENT_EXPORT void Randomize_Particles(Injection *I);
/* @} dpm_tools_random */

/**
 * @addtogroup dpm_tools_postproc post-processing
 * @{
 *************************************************************/
FLUENT_EXPORT Pointer Get_Penetration_Length_Bins(Pointer args, Pointer *result);
/* @} dpm_tools_postproc */

FLUENT_EXPORT double dist_to_point_sq_double   (const double *p1,  const double *p2);
FLUENT_EXPORT double dist_to_line_sq_double    (const double *pos, const double *node0, const double *node1);
FLUENT_EXPORT double dist_to_tri_sq_double     (const double *p, double t[3][3]);
FLUENT_EXPORT double dist_to_quad_sq_double    (const double *p, double q[4][3]);
FLUENT_EXPORT double dist_to_polygon_sq_double (const double *p, double q[][3], const int nnodes);

FLUENT_EXPORT void project_point_to_plane(double pos[3], const double normal[3], const double point[3]);
FLUENT_EXPORT cxboolean are_points_coincident(double pt1[3], double pt2[3], const double scale);
FLUENT_EXPORT cxboolean are_points_colinear(double pt1[3], double pt2[3], double pt3[3], const double scale);

FLUENT_EXPORT void Abort_Tracked_Particle(Tracked_Particle *tp, const char *where, const char *message, const cxboolean add_to_summary);
FLUENT_EXPORT void Abort_Particle(Particle *tp, char *where);
/* @} dpm_tools */

#endif /* _FLUENT_DPM_TOOLS_H */
