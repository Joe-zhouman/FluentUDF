/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_CL_DPM_H
#define _FLUENT_CL_DPM_H

#include "dpm_types.h"
#include "dpm_dem_wall.h"

/**
 * @addtogroup dpm Discrete Particle Model
 * @{
 *
 * @file
 * DPM: accessing solver data and grid
 */

FLUENT_EXPORT void Set_DPM_Relax(cxboolean);

/** @addtogroup dpm_storage accessing storage on grid
    @{ */

/**
 * @addtogroup dpm_storage_filmcoll wallfilm and collision
 * @{
 *************************************************************/

FLUENT_EXPORT void Alloc_Wall_Film_Storage(Domain *domain);
FLUENT_EXPORT void Alloc_Wall_Film_Storage_On_Zone(Thread *tf, const cxboolean initialize);
FLUENT_EXPORT void Init_Wall_Film_Storage(Domain *domain, cxboolean at_start, cxboolean post_p);
FLUENT_EXPORT void Free_Wall_Film_Storage(Domain *domain);
FLUENT_EXPORT void Alloc_Wall_Force_Storage(Domain *domain);
FLUENT_EXPORT void Init_DPM_Wall_Force (void);
FLUENT_EXPORT void Time_Avrg_DPM_Wall_Force(void);
FLUENT_EXPORT void Free_Wall_Force_Storage(Domain *domain);

FLUENT_EXPORT void Alloc_Collision_Storage(Domain *domain);
FLUENT_EXPORT void Set_Collision_Storage(Domain *domain, const cxboolean display);
FLUENT_EXPORT void Free_Collision_Storage(Domain *domain);

FLUENT_EXPORT void Initialize_DPM_Weighting_Storage(Domain *domain);
FLUENT_EXPORT void SV_InitDPMFaces (void);
FLUENT_EXPORT void Init_DPM_Wall_Heat_Exchange (void);

/* @} */

/**
 * @addtogroup dpm_storage_source source terms
 * @{
 *************************************************************/

FLUENT_EXPORT void SV_InitDPM (cxboolean, cxboolean);
FLUENT_EXPORT void SV_DPMCheckSources (cxboolean);
FLUENT_EXPORT void SV_AddDPMSource (cell_t, Thread *, Thread *, face_t, Thread *,
                                    dpms_t *, int[2], int, int *, cxboolean, int, real[3], real);
FLUENT_EXPORT void SV_AddPICSource (cell_t, Thread *, Thread *, face_t, Thread *,
                                    dpms_t *, int[2], int, int *, cxboolean, int, real[3]);
FLUENT_EXPORT void SV_AddWallFilmProps(const face_t f, Thread *tf, film_props_t *props);
FLUENT_EXPORT void Alloc_Sources_Storage(Domain *domain);
FLUENT_EXPORT void Alloc_Species_Sources_Storage(Domain *domain);
FLUENT_EXPORT void Initialize_Source_Storage(Domain *domain);
FLUENT_EXPORT void Free_Sources_Storage(Domain *domain);
FLUENT_EXPORT void Free_Species_Sources_Storage(Domain *domain);
FLUENT_EXPORT void Alloc_Lin_Sources_Storage(Domain *domain);
FLUENT_EXPORT void Initialize_Lin_Source_Storage(Domain *domain);
FLUENT_EXPORT void Free_Lin_Sources_Storage(Domain *domain);
/* @} dpm_storage_source */

/**
 * @addtogroup dpm_storage_computevar compute flow variables at particle position
 * @{
 *************************************************************/

extern FLUENT_EXPORT Domain *DPM_mixture_domain;

#define DPM_INTERACT_WITH_ALL_PHASES(I) (-2 == DPM_INTERACT_DOMAIN_INDX(I))

/* For injections with interaction with all phases
 * i-th index is set during loop over all phase domains.)
 */
#define DPM_INTERACT_DOMAIN_IN_LOOP(I, i) (DPM_INTERACT_WITH_ALL_PHASES(I) \
                                            ? i : DPM_INTERACT_DOMAIN_INDX(I))
/**
 * correct thread selected with DPM_Phase_Id in multiphase flows
 */
/* sg_mphase OR mp_mfluid should be used here ??? !!! */
/* To Do: replace DPM_Phase_Id by TP_CPHASE_INDX(tp, phase) after resolving all model incompatibilities within DPM */
#define DPM_THREAD(thread, tp) (sg_mphase ? THREAD_SUB_THREAD(thread, DPM_Phase_Id) : thread)


FLUENT_EXPORT void compute_rho_g_and_p_down_ofI(Injection *, real [3]);
FLUENT_EXPORT void recompute_rho_g_and_p_down_ofI(Injection *I, cxboolean only_rho);
FLUENT_EXPORT void wall_velocity_at_xf_bare(dpm_collision_face_t *face_data, real *u, real *xf);
FLUENT_EXPORT void wall_velocity_at_xf(const face_t, const Thread *, real *, real *);



/* @} dpm_storage_computevar */
/* @} dpm_storage */

/** @addtogroup dpm_grid Grid
    @{ */

/**
 * @addtogroup dpm_grid_adjustvel adjust particle velocity to mesh
 * @{
 *************************************************************/
FLUENT_EXPORT void convert_particle_velocity(Tracked_Particle *tp, CX_Cell_Id *cx_neigh);
FLUENT_EXPORT void compute_in_plane(real vel[], real n[]);
FLUENT_EXPORT void Convert_P_Vel_To_Absolute_Frame(real vp[], real pos[], Thread *tf, Thread *tc, cphase_state_t *c, int idim, real vp_d[]);
FLUENT_EXPORT void Convert_P_Vel_To_Relative_Frame(real vp[], int idim, real vp_d[]);
/* @} */

/**
 * @addtogroup dpm_grid_locatepointface Location of Points in faces/threads
 * @{
 *************************************************************/
FLUENT_EXPORT void Cyclic_Transform(Thread *tface, STrans *tmat);
FLUENT_EXPORT fat_t SV_closest_face (Domain *, real [], real *, const real );
FLUENT_EXPORT fat_t SV_closest_face_centroid (Domain *, real [], real *, int );
FLUENT_EXPORT cxboolean SV_is_point_on_face(face_t f, Thread *t, real pos[], const real t_delta, double wall_eqn1[3], double wall_eqnV[3]);
FLUENT_EXPORT real distance2_to_face(real pos[], real dt, face_t f, Thread *t);
#if RP_DOUBLE
FLUENT_EXPORT real distance2_to_face_real(const real pos[], const real dt, const face_t f, Thread *t);
#endif
FLUENT_EXPORT int computePlaneEquation(double pts[][3], double *fEq);
FLUENT_EXPORT void computePlaneEquations(gtpv_t *pgvtp, double facePts0[][3][3], const cxboolean interpolate_in_time);
FLUENT_EXPORT cxboolean compute_edge_plane(double p1[3], double p0[3], double norm[3], double fEq[4]);
/* @} */

/**
 * @addtogroup dpm_grid_locatepointcell Location of Points in cells/threads (see dpm.h for octree)
 * @{
 *************************************************************/

/**
 * default search depth for DPM_Locate_Point_In_Domain
 */
#define DPM_FIND_CELL_DEPTH 2000

FLUENT_EXPORT cxboolean IsPointInCell(CX_Cell_Id *, cell_t, Thread *, real [], real,
                                      gtpv_t *, int []);
FLUENT_EXPORT cxboolean IsPointInSectorByVertices(const double point_coord[ND_ND], double vtx_coord[4][3],
                                                  const cxboolean check_vertex_order, const double tolerance);
FLUENT_EXPORT cxboolean SV_is_point_in_cell (CX_Cell_Id *, cell_t, Thread *, real [], real); /* left here for the fiber addon */
FLUENT_EXPORT int SV_relocate_point_in_cell_list (const real [], CX_Cell_Id *, Objp *);
#if RP_NODE
FLUENT_EXPORT cxboolean Locate_Film_Particle_Face_By_Face_Id(Domain *domain, Particle *p);
#endif
FLUENT_EXPORT int SV_locate_point_in_cell_list (real [], CX_Cell_Id *, Objp *);
FLUENT_EXPORT cxboolean Find_Global_Cell_Id_In_Cell_List(cxindex cid, CX_Cell_Id *cx_cell, Objp *cell_list);
#if RP_NODE
FLUENT_EXPORT cxboolean Find_Film_Particle_Global_Face_Id_In_Cell_List(Domain *domain, Particle *p, Objp *cell_list);
#endif

FLUENT_EXPORT int SV_locate_point_in_thread (real [], Thread *, CX_Cell_Id *);
FLUENT_EXPORT cell_t Find_bounding_cell_in_thread (real [], Thread *);
FLUENT_EXPORT cell_t Find_bounding_cell (Domain *, real [], Thread **);
FLUENT_EXPORT void Reset_DPM_Locate_Point_In_Domain_Warnings(void);
FLUENT_EXPORT int DPM_Locate_Point(real [], CX_Cell_Id *, const real, int ); /* Returns TRUE only if particle is found in fluid cell.*/
FLUENT_EXPORT int DPM_Locate_Point_In_Domain(const real [], CX_Cell_Id *, real, int );
FLUENT_EXPORT CX_Cell_Id DPM_Find_Cell(real [], CX_Cell_Id, int );
FLUENT_EXPORT cxboolean find_point_in_threads(Domain *, real *, CX_Cell_Id *, cell_t *, Thread **, real *, real );
FLUENT_EXPORT cxboolean is_point_in_cell_barycentric(const real pos[3], const cell_t c, Thread *tc, const double dt);
FLUENT_EXPORT int Point_In_Bbox_Real( real *point, real *v, int num_pts, int dim);
FLUENT_EXPORT int Choose_Method_And_Fill_Particle_Topart_In_Injection(Domain *srcDomain, Domain *destDomain,
                                                                      Injection *I, int method, cxboolean use_entity_database);
FLUENT_EXPORT int dpm_particle_search_CL_callback(const Domain *domain, void *nodeAttachData, double pCoord[ND_ND], void *particleSearchAttachData, void *dataCarryBack, Cell **cells);
FLUENT_EXPORT real cell_equivalent_length(cell_t c, Thread *tc);
/* @} */

/**
 * @addtogroup dpm_grid_movep Moving Particles in cells or on faces
 * @{
 *************************************************************/
FLUENT_EXPORT void move_into_neighbor_cell( real *pos, CX_Cell_Id *cxneigh, const real dtime );
FLUENT_EXPORT cxboolean move_away_from_face_normal(face_t f, Thread *tf, CX_Cell_Id *cxcell, real norm[], real pos[], real factor, Tracked_Particle *tp);
FLUENT_EXPORT void project_particle_into_cell(CX_Cell_Id *cx_cell, real p_pos[], const real dt);
FLUENT_EXPORT void move_towards_cell_centroid(CX_Cell_Id *cxcell, real pos[], real factor, const real dt);
FLUENT_EXPORT void move_towards_face_centroid(double pts[4][3], real pos[], real factor, int npts);
FLUENT_EXPORT int Move_Particles_In_Thread(Particle *p, real dtime);
#if DEBUG
FLUENT_EXPORT void reset_move_towards_cell_centroid(CX_Cell_Id *cxcell, real pos[], real factor);
#endif


/* @} */

/**
 * @addtogroup dpm_grid_cellbin bin particles between injections and cells
 * @{
 *************************************************************/
FLUENT_EXPORT int64_t bin_particles_in_cells(Domain *domain, cxboolean init_cells, cxboolean only_ddpm_injections, Domain *subdomain);
FLUENT_EXPORT void unthread_particles_to_all_inj(Domain *domain, cxboolean check_injection_pointers);
/* @} */

/**
 * @addtogroup dpm_grid_locateparticle Particles in cells or faces
 * @{
 *************************************************************/
FLUENT_EXPORT void calcFaceEquations_core(CX_Cell_Id *cell, gtpv_t *pgvtp, const double t_delta);
FLUENT_EXPORT void calcFaceEquations(Tracked_Particle *);
FLUENT_EXPORT cxboolean Is_Particle_In_Right_Cell_And_Face(Domain *domain, Particle *p, real t_delta);
FLUENT_EXPORT cxboolean Find_Tracked_Particle (Domain *, Tracked_Particle *);
FLUENT_EXPORT cxboolean Find_Particle_Local (Particle *, real);
FLUENT_EXPORT int check_particle_cell_face_ids(const Particle *pl);
FLUENT_EXPORT int Locate_Particles_Using_CellID(Domain *srcDomain, Domain *destDomain, Injection *I, int method, cxboolean use_entity_database);
FLUENT_EXPORT void Locate_O_Particle_List_Local(Particle **pl, Particle **found, Particle **lost, int depth);
FLUENT_EXPORT void Locate_Particle_List_in_Domain_Local(Particle **, Particle **, Particle **, Domain *);

#if RP_NODE
/*FLUENT_EXPORT void Unmark_Particles_Found_in_Domain_Netwide(Particle *pl, int *nfound, Domain *domain);*/
#endif
FLUENT_EXPORT void Unmark_Particles_Found_On_Faces_in_Domain_Local(Particle *pl, int *nfound, int *nlost, Domain *domain);
FLUENT_EXPORT void Locate_WF_Particle_List_Local(Particle **wfpl, Particle **found, Particle **lost);
FLUENT_EXPORT void Closest_Distance_Particle_List_in_Domain(Particle *pl, real *dist, real *dist_int, Domain *domain);
FLUENT_EXPORT void Closest_Face_Distance_Marked_Particles_in_Domain(Particle *pl, real *dist, Domain *domain);
FLUENT_EXPORT void Locate_Particle_List_Local(Particle **, Particle **, Particle **, cxboolean, int);

#if RP_NODE
FLUENT_EXPORT void Lookup_Cells_Faces_For_Migrated_Particle_List(Domain *domain, Particle **pl, Particle **found, Particle **lost);
#endif
FLUENT_EXPORT void Mark_Lost_Particles_Local_WF_Cell(Particle *pl, int *nfound, int *nlost, int depth);
#if RP_NODE
FLUENT_EXPORT int Locate_Particle_List_Netwide(Particle **, Particle **, Particle **, cxboolean, int);

#endif
FLUENT_EXPORT int Relocate_Particles_In_Thread(Injection *I, Particle *p, Particle *prev);
FLUENT_EXPORT void Relocate_Inj_List_Particles(cxboolean netwide, cxboolean urge_picles_into_domain, cxboolean free_lost_picles, Injection *inj_list);
FLUENT_EXPORT void Relocate_One_Inj_Particles(cxboolean netwide, cxboolean urge_picles_into_domain, cxboolean free_lost_picles, Injection *one_inj);
FLUENT_EXPORT void Relocate_Unsteady_Particles(cxboolean);
FLUENT_EXPORT void Relocate_PDF_Particles(void);
FLUENT_EXPORT void DPM_Relocate_All_Unsteady_Particles(Domain *srcDomain, Domain *destDomain, int method, cxboolean netwide);
FLUENT_EXPORT Find_Face_Err_Code Find_Boundary_Face_And_Thread(Particle *p, Injection *I, face_t *f, Thread **ft);
FLUENT_EXPORT int Fill_Particle_Cell_Face_Id(Domain *domain, Injection *Ilist, cxboolean do_wallfilm_particles);
/* @} */

/**
 * @addtogroup dpm_grid_pathface path-face intersection
 * @{
 *************************************************************/
#if RP_2D
FLUENT_EXPORT cxboolean FindIntersectionSegment2D(real p0[3], real d[3], real *t, real *u, real p_intersect[3], double pts[][3]);
FLUENT_EXPORT cxboolean FindIntersectionRay2D(real p0[3], real d[3], real *t, real *u, real p_intersect[3], double pts[][3]);
FLUENT_EXPORT cxboolean FindIntersectionSegment2DGauss(real p0[3], real d[3], real *t, real *u, real p_intersect[3], double pts[][3], real eps);
FLUENT_EXPORT cxboolean FindIntersectionRay2DGauss(real p0[3], real d[3], real *t, real *u, real p_intersect[3], double pts[][3], real eps);
#else
FLUENT_EXPORT cxboolean FindIntersectionSegment3D(real p0[3], real d[3], real *t, real *u, real *v, real p_intersect[3], double pts[][3]);
FLUENT_EXPORT cxboolean FindIntersectionRay3D(real p0[3], real d[3], real *t, real *u,  real *v, real p_intersect[3], double pts[][3]);
FLUENT_EXPORT cxboolean FindIntersectionSegment3DGauss(real p0[3], real d[3], real *t, real *u,  real *v, real p_intersect[3], double pts[][3], real eps);
FLUENT_EXPORT cxboolean FindIntersectionRay3DGauss(real p0[3], real d[3], real *t, real *u,  real *v, real p_intersect[3], double pts[][3], real eps);
#endif /* RP_2D */

/* defined in <path.c> */
FLUENT_EXPORT int path_face_intersection(real[], real[], real[], real[], real, real[][3], real[], real[], real *, int, int, int);
FLUENT_EXPORT int Path_Plane_Linear_Intersection(real p[], real v[], real eq[], real q[], real *dt, int ldim);
FLUENT_EXPORT int point_within_tri(real[][3], real[], int, real[]);

/* @} */

/**
 * @addtogroup dpm_grid_threadmarker cell thread marker
 * @{
 *************************************************************/
FLUENT_EXPORT void Unmark_All_Cell_Threads(void);
FLUENT_EXPORT void Mark_All_Fluid_Threads(void);
FLUENT_EXPORT cxboolean Check_Non_Fluid_Threads_P(Domain *domain);
/* @} */


/**
 * @addtogroup dpm_distance_computation distance computation
 * @{
 *************************************************************/

#if RP_3D
FLUENT_EXPORT void Distance2_To_Triangle_3d(const real bb[3], const real e0[3], const real e1[3],
                                            const real xx[3], real *dd, real yy[3]);
FLUENT_EXPORT void Distance2_To_Triangle_3d_double(const double bb[3], const double e0[3], const double e1[3],
                                                   const real xx[3], real *dd, real yy[3]);
#endif

#if RP_2D
FLUENT_EXPORT void Distance2_To_Line_Segment_2d(const real p0[2], const real p1[2], const real xx[2], real *dd, real yy[2]);
FLUENT_EXPORT void Distance2_To_Line_Segment_2d_double(const double p0[2], const double p1[2], const real xx[2], real *dd, real yy[2]);
#endif

FLUENT_EXPORT void Compute_Detailed_Distance2_To_Face(dpm_collision_face_t *face_data, real NV_VEC(xx));

/* @} dpm_dpm_distance_computation */

/**
 * @addtogroup dpm_node_access
 * @{
 *************************************************************/
#define NODE_DPM_WT(v)      N_STORAGE_R(NODE_INDEX(v), NODE_THREAD(v), SV_N_RTMP_0)
#define NODE_DPM_N_WT(v)    N_STORAGE_R(NODE_INDEX(v), NODE_THREAD(v), SV_N_RTMP_1)

#define NODE_DPM_NORMAL(v)  N_STORAGE_R_NV(NODE_INDEX(v), NODE_THREAD(v), SV_N_NORMAL)
#define NODE_DPM_CORRECT(v) N_STORAGE_I(NODE_INDEX(v), NODE_THREAD(v), SV_N_CORRECT)

typedef enum
{
  INTERNAL_NODE = 0,
  BOUNDARY_NODE = 1,
  WALL_NODE     = 2,
  NCI_NODE      = 3,
  PERIODIC_NODE = 4
} NODE_MARK_TYPE;

FLUENT_EXPORT void Update_Transient_Flow_Variables_on_Nodes(Domain *domain);
FLUENT_EXPORT void Init_Node_Averages(Domain *domain, cxboolean display_or_report);
FLUENT_EXPORT void Cleanup_Node_Averages(const cxboolean display_or_report, const cxboolean free_weights_memory);
FLUENT_EXPORT void Cleanup_Nodal_Vars(void);
FLUENT_EXPORT void compute_kb_weights_of_xp(cell_t c, Thread *t, real xp[ND_ND], real wts[], int kernel, real gauss, cxboolean use_m1);
FLUENT_EXPORT void compute_kb_weights_of_coords_xp(real x[][ND_ND], int n, real xp[ND_ND], real wts[], int kernel, real gauss);
FLUENT_EXPORT void compute_kb_weights_of_face_xp(Face *fsp, real xp[ND_ND], real wts[], int kernel, real gaussian_a, cxboolean use_m1_mesh);
FLUENT_EXPORT cxboolean nodal_svars_needed(const cxboolean display_or_report);
/* @} */

/* @} dpm_grid */

/* @} dpm */

#endif
