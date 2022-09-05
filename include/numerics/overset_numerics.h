/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_OVERSET_NUMERICS_H
#define _FLUENT_OVERSET_NUMERICS_H

#include "turb.h"
#include "sg.h"

typedef struct _hc_lsf_detector_ws
{
  Domain *domain;
  cell_t cr;
  Thread *tcr;
  cell_t cmarked;
  Thread *tcmarked;
  cxboolean detector;
  int neleminate;
} HC_LSF_DETECTOR_WS;

#if RP_OVERSET
enum overset_interpolation
{
  INVERSE_DISTANCE = 0,
  LEAST_SQUARES,
  HYBRID_IMO
};

enum interpolation_check_level
{
  WEIGHT_SUM = 1,
  WEIGHT_EXTRAPOLATION,
  WEIGHT_SUM_AND_EXTRAPOLATION /* default = 3 with LSF, does not apply for IDW */
};

enum update_dead_to_generic
{
  DEAD_CELL_UPDATE = 0,
  DEAD_TO_RECEPTOR,
  DEAD_TO_SOLVE,
  DEAD_TO_ORPHAN
};

enum general_overset_cell_type
{
  DEAD = 0,
  DEAD_2_SOLVE,
  DEAD_2_RECEPTOR,
  RECEPTOR,
  DONOR,
  SOLVE
} GOType;

typedef enum bounds_overset_type
{
  NO_BOUNDS = 0,
  UPPER_LOWER_BOUNDS,
  LOWER_BOUND,
  UPPER_BOUND
} boss_t;

typedef struct Bound_Overset_Interpolation_Struct
{
  real phi_min;
  real phi_max;
  boss_t    type;   /* lower, upper, upper lower & no bounds*/
  /* experimental option - to apply for cell status interpolations */
  int bound_method; /* 0 - solution limits (current default),
                       1 - domain average -
                       2 - thread average
                       3 - closest neigbor */
} Boss;

enum overset_mass_conservation_type
{
  OMC_NONE = 0,
  OMC_HADZIC,
  OMC_SVENJA_VS
};

/* performance */
FLUENT_EXPORT void update_receptor_list(Domain *d, cxboolean force_p);
/* overset options (globals, rpvar settings etc.)  update mechanism */
FLUENT_EXPORT void overset_update_pre(Domain *d);
/* interpolation  */
FLUENT_EXPORT void update_receptor_weights(Domain *d, cxboolean hyb_init_p);
FLUENT_EXPORT real Interpolate_Receptor_SVAR_From_Donors(Domain *domain, cell_t c, Thread *tc, Svar nv, int idx);
FLUENT_EXPORT real interpolate_cell_data_from_donors (Objp *donor, real *wtd, Svar nv);
FLUENT_EXPORT void Interpolate_XV_Cell_Data_From_Donors (Objp *donor, cell_t cr, Thread *tr, real *wtd, Svar nv);
FLUENT_EXPORT void update_receptor_cell_data(Domain *d, Svar nv);
FLUENT_EXPORT void update_receptor_cell_data_high_order(Domain *d, Svar nv, cxboolean high_order, Svar nvg);
FLUENT_EXPORT void update_receptor_cell_vector(Domain *d, Svar nv, cxboolean use_principal_donor_p);
FLUENT_EXPORT void interpolate_generic_vector_from_donors (Objp *donor,
                                                           real *wtd,
                                                           cell_t cr, Thread *tcr, cell_t cdnr, Thread *tdnr,
                                                           Svar nv,
                                                           cxboolean use_principal_donor_p);

FLUENT_EXPORT void interpolate_cell_vector_from_donors (Objp *donor,
                                                        real *wtd,
                                                        cell_t cr, Thread *tcr);

FLUENT_EXPORT void update_receptor_cell_velocity(Domain *d);

/* generic interpolations */
FLUENT_EXPORT void Update_Receptor_Scalar_Svar_List_Data(Domain *domain, ...);

FLUENT_EXPORT void Overset_Interpolate_Scalar_Svar_List(Domain *domain, cell_t c, Thread *tc,
                                                        Var_Attribute **sv_list,
                                                        int *iw_index_list,
                                                        int nsvs,
                                                        cxboolean need_bounds_p);

FLUENT_EXPORT void Overset_Interpolate_Cell_Scalar(Domain *domain, Svar nv, cxboolean principal_p);
FLUENT_EXPORT void Overset_Interpolate_Cell_Velocity(Domain *domain, cxboolean principal_p);
FLUENT_EXPORT void Overset_Interpolate_Cell_Vector(Domain *domain, Svar nv, cxboolean principal_p);

/* generalized interpolation */
FLUENT_EXPORT int Compute_Overset_Generalized_Weights(Domain *domain);

FLUENT_EXPORT void Overset_General_Cell_Scalar_Update(Domain *domain, Svar nv, cxboolean principal_p);
FLUENT_EXPORT void Overset_General_Cell_Velocity_Update(Domain *domain, cxboolean principal_p);
FLUENT_EXPORT void Overset_General_Cell_Vector_Update(Domain *domain, Svar nv, cxboolean principal_p);

FLUENT_EXPORT void Overset_Orphan_Degenerate_Cell_Scalar_Gradient(Domain *domain, Svar nv, Svar nvg, cxboolean use_principal_p);
FLUENT_EXPORT  void Overset_Cell_Scalar_Gradient(Domain *domain, Svar nv, Svar nvg, cxboolean use_principal_p);

FLUENT_EXPORT  void Overset_Cell_Vector_Gradient(Domain *domain, ND_VEC(Svar gx, Svar gy, Svar gz), cxboolean use_principal_p);
FLUENT_EXPORT void Overset_Orphan_Degenerate_Cell_Vector_Gradient(Domain *domain,   ND_VEC(Svar gx, Svar gy, Svar gz), cxboolean use_principal_p);

FLUENT_EXPORT void Overset_Fill_Gradient_Vector(Domain *domain, ND_VEC(Svar gx, Svar gy, Svar gz),
                                                cxboolean is_or_treat_like_rg_p,
                                                cxboolean interpolate_p,
                                                cxboolean handle_degeneracy_p,
                                                cxboolean use_principal_p);
FLUENT_EXPORT void Overset_Fill_Gradient_Vector_From_Reconstruction_Gradient(Domain *domain,
    ND_VEC(Svar wx, Svar wy, Svar wz),
    ND_VEC(Svar dwx, Svar dwy, Svar dwz),
    ND_VEC(Svar rgwx, Svar rgwy, Svar rgwz));
FLUENT_EXPORT void Overset_General_Vector_Gradient_Accumulate(Domain *domain,
                                                              ND_VEC(Svar nU,   Svar nV,   Svar nW),
                                                              ND_VEC(Svar nU_G, Svar nV_G, Svar nW_G),
                                                              ND_VEC(Svar nU_RG, Svar nV_RG, Svar nW_RG));

FLUENT_EXPORT void Overset_Fill_Gradient_Scalar(Domain *domain, Svar nv, Svar nvg,
                                                cxboolean is_or_treat_like_rg_p,
                                                cxboolean interpolate_p,
                                                cxboolean handle_degeneracy_p,
                                                cxboolean use_principal_p);
FLUENT_EXPORT void Overset_Fill_Gradient_Scalar_From_Reconstruction_Gradient(Domain *domain, int n, Svar nv, Svar nvrg, Svar nvg);
FLUENT_EXPORT void Overset_General_Scalar_Derivative_Accumulate(Domain *d, Svar sw, int ns, Svar gw, Svar rgw);
FLUENT_EXPORT void Overset_General_Vector_Derivative_Accumulate(Domain *domain,
                                                                ND_VEC(Svar nU,   Svar nV,   Svar nW),
                                                                ND_VEC(Svar nU_G, Svar nV_G, Svar nW_G),
                                                                ND_VEC(Svar nU_RG, Svar nV_RG, Svar nW_RG));
FLUENT_EXPORT int Overset_Interpolation_Weight_Index(Domain *domain, Svar nv);
FLUENT_EXPORT cxboolean Overset_Interpolation_Needed_Before_G_Or_RG_P(Domain *domain, Svar nv, cxboolean is_rg_p);
FLUENT_EXPORT cxboolean  Overset_Get_Principal_Gradient_P(Domain *domain, Svar nv, cxboolean recon_p);
FLUENT_EXPORT cxboolean  Overset_Get_Principal_Solution_P(Domain *domain, Svar nv);
FLUENT_EXPORT cxboolean Overset_Gradient_Use_Accumulator(Domain *domain, Svar nv, int method);


/* interpolation - gradients */
FLUENT_EXPORT void update_receptor_cell_gradients(Domain *d,
                                                  Svar nv, Svar nvg);
FLUENT_EXPORT void interpolate_cell_gradients_from_donors(cell_t cr,
                                                          Thread *tcr,
                                                          Objp *donor, Svar nv);
/* interpolation - gradients - velocity */
FLUENT_EXPORT void update_receptor_cell_vector_gradients(Domain *d,
                                                         ND_VEC(Svar nug,
                                                                Svar nvg,
                                                                Svar nwg));
FLUENT_EXPORT void interpolate_cell_vector_gradients_from_donors(cell_t cr,
                                                                 Thread *tcr,
                                                                 Objp *donor,
                                                                 ND_VEC(Svar ux,
                                                                     Svar uy,
                                                                     Svar uz));

/* LSF methods  */
FLUENT_EXPORT int Compute_Overset_LSF_Weights(Domain *domain);
FLUENT_EXPORT int overset_lsf_weights(Domain *domain_in);
FLUENT_EXPORT int compute_inverse_distance_weights(Domain *d, Objp *clist, int iw_index);
FLUENT_EXPORT void Overset_Fill_Model_Specific_Weights(Domain *domain);
FLUENT_EXPORT int Overset_Need_Model_Specific_Weights(Domain *domain);
FLUENT_EXPORT int Overset_Get_Model_Specific_Interpolation_Index(Domain *domain);
FLUENT_EXPORT int Overset_Get_Svar_Specific_Interpolation_Index(Domain *domain, Svar nv);
FLUENT_EXPORT void overset_model_specific_receptor_cell_gradients(Domain *domain, Svar nv, Svar nvg);
FLUENT_EXPORT void Clear_Receptor_Cells_Temp_Flag(Domain *d);
FLUENT_EXPORT void overset_lsf_interpolate_face_vars(Domain *domain_in, Svar nv, cxboolean temp);
FLUENT_EXPORT void overset_vector_accumulate(Domain *d,
                                             ND_VEC(Svar nU,   Svar nV,   Svar nW),
                                             ND_VEC(Svar nU_G, Svar nV_G, Svar nW_G),
                                             ND_VEC(Svar nU_RG, Svar nV_RG, Svar nW_RG));
FLUENT_EXPORT void overset_default_scalar_deriv_accumulate(Domain *d, Svar sw, int ns, Svar gw, Svar rgw);
FLUENT_EXPORT void overset_lsf_gradient(Domain *domain_in, Svar nv, Svar nvg);
FLUENT_EXPORT void overset_lsf_vector_gradient(Domain *domain_in, ND_VEC(Svar gx, Svar gy, Svar gz));
FLUENT_EXPORT void overset_recon_cell_limit(Domain *d, Svar nv, int ns, Svar rgw, real eps);

/* dead and orphan cell treatments */

FLUENT_EXPORT void update_orphan_cell_scalar(Domain *d, Svar nv);
FLUENT_EXPORT void update_orphan_cell_vector(Domain *d, Svar nv);
FLUENT_EXPORT void update_orphan_cell_velocity(Domain *d);
/* ---- LSF orphan and degenerate gradient updates */
FLUENT_EXPORT void update_orphan_cell_gradients(Domain *d, Svar nvg);
FLUENT_EXPORT void update_orphan_cell_vector_gradients(Domain *d,
                                                       ND_VEC(Svar nug, Svar nvg, Svar nwg));

FLUENT_EXPORT void update_degenerate_cell_gradients(Domain *d, Svar nvg);
FLUENT_EXPORT void update_degenerate_cell_vector_gradients(Domain *d,
                                                           ND_VEC(Svar nug, Svar nvg, Svar nwg));
FLUENT_EXPORT void update_dead_cell_variables(Domain *d);

/* transients & moving meshes   */
FLUENT_EXPORT void Calculate_Overset_Orphan_Grid_Update_Interpolation_Weights(Domain *, Objp *, cxboolean, cxboolean);
FLUENT_EXPORT void update_new_cells_and_faces(Domain *d, cxboolean force_p);
FLUENT_EXPORT void update_overset_flow_after_grid_update(Domain *d, Objp *new);

FLUENT_EXPORT void mp_update_receptor_cell_data(Domain *d, Svar nv, cxboolean principal_p);
FLUENT_EXPORT void mp_update_receptor_cell_gradients(Domain *d, Svar nv, Svar nvg);

/* flow */
FLUENT_EXPORT void overset_face_pressure_update(Domain *d);
FLUENT_EXPORT void overset_convert_face_flux_to_vn(Domain *d, cxboolean vn_to_flux_p);
FLUENT_EXPORT void overset_convert_vn_to_face_flux(Domain *d);
FLUENT_EXPORT void set_receptor_face_flux(Domain *d, cell_t cdr, Thread *tdr,
                                          cell_t  cr, Thread *tr,
                                          face_t   f, Thread *tf, cxboolean is_init, cxboolean convert_to_relative);
FLUENT_EXPORT void Overset_Update_Face_Flux(Domain *d, cxboolean init_p);
FLUENT_EXPORT void mp_receptor_mass_flux(Domain *d);
FLUENT_EXPORT void overset_interface_correct_mass_flux(Domain *d);
FLUENT_EXPORT void Overset_Mass_Flux_Explicit_Conservation(Domain *d);
FLUENT_EXPORT void overset_boundary_coeff(face_t   f, Thread *tf,
                                          cell_t cdr, Thread *tdr,
                                          cell_t  cr, Thread *tr,
                                          cxboolean skip_anb_update_p,
                                          cxboolean need_sav_p,
                                          int iw_index);
FLUENT_EXPORT void update_receptor_coeff(Domain *d, cxboolean skip_anb_update_p,
                                         cxboolean need_sav_p);
FLUENT_EXPORT void recompute_pressure_anb(face_t  f, Thread *tf,
                                          cell_t cr, Thread *tr, cxboolean coupled_p);

FLUENT_EXPORT void recompute_pressure_coupled_anb(face_t  f, Thread *tf,
                                                  cell_t cr, Thread *tr);

FLUENT_EXPORT void receptor_pressure_anb(Domain *d, cxboolean is_coupled_p);
/* PISO & SIMPLEC  */
FLUENT_EXPORT void zero_pressure_anb(face_t  f, Thread *tf, cell_t cr, Thread *tr);
FLUENT_EXPORT void receptor_pressure_zero_anb(Domain *d);

FLUENT_EXPORT void coupled_update_receptor_coeff(Domain *d);
FLUENT_EXPORT void coupled_update_receptor_neighbor_coeff(cell_t cr, Thread *tcr,
                                                          face_t  f, Thread *tf, int flow_iw_index, int model_iw_index);
FLUENT_EXPORT void dbns_coupled_update_receptor_neighbor_coeff(cell_t cr, Thread *tcr,
                                                               face_t f, Thread *tf, int flow_iw_index);
FLUENT_EXPORT void update_scalar_receptor_coeff(Domain *domain, Svar sv_phi);

FLUENT_EXPORT void Update_PISO_Avalue(Domain *d, cxboolean allocate_avalue_p);
FLUENT_EXPORT void Update_Overset_lsf_Pgrad_Velocity_Correction(Domain *domain, cxboolean use_principal );

FLUENT_EXPORT void add_overset_boundary_flux_imbalance(Domain *d, Svar nv);

/* generic */
FLUENT_EXPORT void update_receptor_scalar_coeff(Domain *d, Svar nv);

/* amg */
FLUENT_EXPORT void Overset_AMG_Entries(cell_t c0, Thread *t0, cell_t c1, Thread *t1,
                                       Level *fine);
FLUENT_EXPORT void Overset_AMG_Coeffs(int sys_id, face_t face, Thread *thread,
                                      cell_t c0, Thread *t0,
                                      cell_t c1, Thread *t1, Level *fine);
FLUENT_EXPORT void Overset_AMG_Zero_Fine_Level(int sys_id, int iter_nita);

FLUENT_EXPORT cxboolean Overset_IDW_For_Intergrid_AMG_Coupling(Svar nv);

FLUENT_EXPORT void print_amg_matrix(Domain *d, int sys_id);
FLUENT_EXPORT void update_receptor_neighbor_coeff(cell_t cr, Thread *tcr,
                                                  face_t  f, Thread *tf, int model_iw_index);
FLUENT_EXPORT void Overset_Receptor_Fix_AMG_Solution(cell_t c, Thread *tc, int index, real phix, real diagx, real rhsx);
FLUENT_EXPORT void fill_receptor_coefficient_matrix(Domain *d, Svar nv);

FLUENT_EXPORT void coupled_fill_receptor_coefficient_matrix(Domain *d);

/* turbulence specific */
FLUENT_EXPORT void fill_receptor_coefficient_matrix_turb(Domain *d, Svar nv, Turb_BC_Type bc_type);

FLUENT_EXPORT cxboolean scalar_skip_interpolation(Svar w);

/*conjugate heat transfer - to handle coupled wall and regular wall overlap situation */
#define OVERSET_DEAD_CELL_AT_COUPLED_WALL_P(c0, t0, c1, t1) \
 (OVERSET_DEAD_CELL_P(c0,t0) || OVERSET_DEAD_CELL_P(c1, t1))
/* porous zones */
FLUENT_EXPORT void Overset_Check_Porous_Zones_Setup(Domain *domain);

/* DO model specific */
FLUENT_EXPORT void Overset_Set_DO_XV_Index(int ns);
FLUENT_EXPORT int Overset_Get_DO_XV_Index(void);
FLUENT_EXPORT real Interpolate_Receptor_XV_SVAR_From_Donors(Domain *domain, cell_t c, Thread *tc, Svar nv, int idx, int nsl);
FLUENT_EXPORT void Overset_Fill_Receptor_Coefficient_Matrix_DO(Domain *domain, Svar nv, cxboolean interpolate_during_linear_solve_p);
FLUENT_EXPORT int  ost_do_ns_index;
FLUENT_EXPORT int  ost_do_max_index;

/* utilities & debug */
FLUENT_EXPORT void init_receptor(Domain *d);
FLUENT_EXPORT void update_face_on_receptor_cells(Domain *d);
FLUENT_EXPORT void my_store_loop(Domain *d);
FLUENT_EXPORT void identify_principal_donors(Domain *d);
FLUENT_EXPORT void Print_Overset_Interpolation_Weights_Per_Cell(cell_t c, Thread *tc);
/* parallel debug */
FLUENT_EXPORT void check_receptor_has_valid_donors_in_parallel(Domain *d);

/* debug flags */
FLUENT_EXPORT cxboolean ost_init_flux_dbg;
FLUENT_EXPORT cxboolean ost_update_flux_dbg;
FLUENT_EXPORT cxboolean ost_flux_imbalance_dbg;
FLUENT_EXPORT cxboolean ost_mom_coeff_dbg;
FLUENT_EXPORT cxboolean ost_interpolate_cell_dbg;
FLUENT_EXPORT cxboolean ost_interpolate_scalar_grad_dbg;
FLUENT_EXPORT cxboolean ost_interpolate_vector_grad_dbg;
FLUENT_EXPORT cxboolean ost_press_coeffs_dbg;
FLUENT_EXPORT cxboolean ost_press_corr_dbg;
FLUENT_EXPORT cxboolean ost_face_flux_corr_dbg;
FLUENT_EXPORT cxboolean ost_face_press_corr_dbg;
FLUENT_EXPORT cxboolean ost_face_press_dbg;
FLUENT_EXPORT cxboolean ost_use_principal_donor_for_anb_p;

FLUENT_EXPORT real omega_v_ost;
FLUENT_EXPORT cxboolean ost_init_flux_dbg;
FLUENT_EXPORT cxboolean ost_update_flux_dbg;

/* overset interpolation & gradient options  */
FLUENT_EXPORT int ost_interpolation_method;
FLUENT_EXPORT cxboolean ost_lsf_limit_recon_p;
FLUENT_EXPORT cxboolean ost_lsf_use_recon_p;
FLUENT_EXPORT cxboolean ost_weighted_lsf_p;
FLUENT_EXPORT cxboolean ost_lsf_init;  /*set overset_numerics.c */
FLUENT_EXPORT cxboolean ost_vof_use_lsf_p;
FLUENT_EXPORT cxboolean ost_scalars_use_lsf_p;
FLUENT_EXPORT cxboolean ost_disco_use_lsf_p;
FLUENT_EXPORT cxboolean ost_lsf_ip_wts_check_p;
FLUENT_EXPORT int       ost_lsf_ip_wts_check_level;
FLUENT_EXPORT cxboolean ost_lsf_matrix_enforce_zero_deltax_p;
FLUENT_EXPORT int       ost_lsf_disco_bounding_type;

/* overset boundary flux parameters */
FLUENT_EXPORT cxboolean add_press_diss_p;
FLUENT_EXPORT cxboolean use_prev_vel_p;
FLUENT_EXPORT cxboolean add_high_order_p;
FLUENT_EXPORT cxboolean orphan_p;
FLUENT_EXPORT cxboolean orphan_treatment_p;
FLUENT_EXPORT cxboolean overset_degenerate_cells_p;
FLUENT_EXPORT cxboolean ost_lsf_orphan_or_degenerate_p;
FLUENT_EXPORT real *Avalue_oi;
FLUENT_EXPORT cxboolean ost_apply_mass_flux_correction_p;
FLUENT_EXPORT int ost_mass_flux_correction_method;

/*overset dead, dead to solve and orphan update  */
FLUENT_EXPORT cxboolean orphan_update_connectivity_p;
FLUENT_EXPORT cxboolean dead_to_solve_update_connectivity_p;
FLUENT_EXPORT cxboolean dead_update_connectivity_p;

FLUENT_EXPORT cxboolean ost_idw_use_recon_p;

FLUENT_EXPORT int       orphan_treatment_method;
FLUENT_EXPORT cxboolean ost_orphan_depends_on_receptors_p;
FLUENT_EXPORT int       ost_hyb_weights_for_interpolation;
FLUENT_EXPORT real      ost_hyb_interpolation_tolerance;
FLUENT_EXPORT int       ost_hyb_idw_exponent;
FLUENT_EXPORT cxboolean ost_principal_solution_p;
FLUENT_EXPORT cxboolean ost_principal_gradient_p;
FLUENT_EXPORT cxboolean ost_interpolate_before_reconstruction_p;
FLUENT_EXPORT cxboolean ost_interpolate_before_derivatives_p;
FLUENT_EXPORT int       ost_hyb_idw_gradient_method;
FLUENT_EXPORT int       ost_hyb_gradient_mode;
FLUENT_EXPORT int       ost_hyb_amg_weights_mode;
FLUENT_EXPORT cxboolean ost_hyb_orphan_or_degenerate_p;
FLUENT_EXPORT cxboolean ost_hyb_apply_bounds_p;
FLUENT_EXPORT cxboolean ost_hyb_unlimited_gradient_p;
FLUENT_EXPORT cxboolean ost_hyb_unlimited_reconstruction_gradient_p;
FLUENT_EXPORT cxboolean ost_hyb_use_recon_p ;
FLUENT_EXPORT cxboolean ost_hyb_limit_recon_p;
FLUENT_EXPORT cxboolean ost_hyb_weighted_system_p;  /*  (ost/weighted-hybrid?)     */
FLUENT_EXPORT cxboolean ost_hyb_ip_wts_check_p;     /*  (ost/weights-check?)       */
FLUENT_EXPORT int       ost_hyb_ip_wts_check_type;       /*  (ost/weights-check-level) */
FLUENT_EXPORT cxboolean ost_hyb_bounded_solution_p;
FLUENT_EXPORT cxboolean ost_hyb_matrix_enforce_zero_deltax_p;  /*  (ost/enforce-zero-deltax-in-lsf-matrix?) */
FLUENT_EXPORT cxboolean Overset_Use_Principal_Gradient_P(Domain *domain, Svar nv);
FLUENT_EXPORT cxboolean Overset_Use_Principal_Solution_P(Domain *domain, Svar nv);
FLUENT_EXPORT int Overset_Set_Interpolation_Tolerance(Domain *domain, int method);

#define OVERSET_IDW_INTERPOLATION_P (ost_interpolation_method == INVERSE_DISTANCE)
#define OVERSET_LSF_INTERPOLATION_P (ost_interpolation_method == LEAST_SQUARES)
#define OVERSET_HYB_INTERPOLATION_P (ost_interpolation_method == HYBRID_IMO)
#define OVERSET_LSF_INTERPOLATION_IDW_FALLBACK_P(domain)  (OVERSET_LSF_INTERPOLATION_P && Unintersected__Overset_Interfaces_P(domain))
#define OVERSET_HYB_INTERPOLATION_IDW_FALLBACK_P(domain)  (OVERSET_HYB_INTERPOLATION_P && Unintersected__Overset_Interfaces_P(domain))

#define OVERSET_LSF_ORPHAN_OR_DEGENERACY_P  (OVERSET_LSF_INTERPOLATION_P && ost_lsf_orphan_or_degenerate_p)
#define OVERSET_HYB_ORPHAN_OR_DEGENERACY_P  (OVERSET_HYB_INTERPOLATION_P && ost_hyb_orphan_or_degenerate_p)
#define OVERSET_INTERPOLATE_SOLUTION_BEFORE_GRADIENT_P (ost_interpolate_before_derivatives_p)
#define OVERSET_INTERPOLATE_SOLUTION_BEFORE_RECONSTRUCTION_P (ost_interpolate_before_recon_p)
#define OVERSET_ORPHAN_DEPENDS_ON_RECEPTOR_P (ost_orphan_depends_on_receptors_p)
#define OVERSET_APPLY_BOUNDS_P (ost_hyb_apply_bounds_p ? TRUE: FALSE )

#define OVERSET_HYB_USE_UNLIMITED_G_OR_RG(is_rg_p) (is_rg_p ? ost_hyb_unlimited_reconstruction_gradient_p: ost_hyb_unlimited_gradient_p)

#define OVERSET_HYB_USE_LIMITED_RECONSTRUCTION_P  (ost_hyb_limit_recon_p)
#define OVERSET_HYB_USE_LSF_WEIGHTS_P (ost_hyb_weights_for_interpolation == 1)
#define OVERSET_HYB_BOUND_SOLUTION_P (ost_hyb_bounded_solution_p)
#define OVERSET_HYB_USE_IDW_WEIGHTS_P (ost_hyb_weights_for_interpolation == 0)
#define EXACT_MATCH_P(distance) (distance < ost_hyb_interpolation_tolerance)
#define ZERO_DELTA_P(deltax) ( ABS(deltax) < EPSILON)
#define IDW_PRINCIPAL_DONOR_GRADIENT_P(principal_p) (ost_hyb_idw_gradient_method == 0 || principal_p)

#endif /* #if RP_OVERSET */

FLUENT_EXPORT void Fill_Overset_Numerics_Parameters(Domain *domain, cxboolean init_p);

FLUENT_EXPORT void Report_Overset_Interpolation_Weights(Domain *domain, cell_t c_specified, int, cxboolean, cxboolean);

FLUENT_EXPORT void Report_Solution_Based_On_Cell_Type(Domain *domain, Svar nv, int type,
                                                      cxboolean include_location_p,
                                                      cxboolean include_donors_p);

FLUENT_EXPORT void Report_Solution_Based_On_Cell_Type_General(Domain *domain, int type,
                                                              cxboolean include_location_p,
                                                              cxboolean include_donors_p);

FLUENT_EXPORT void Report_Gradient_Based_On_Cell_Type(Domain *domain, Svar nv,
                                                      int type, cxboolean is_rg_p, cxboolean is_velocity);

typedef struct overset_numerics_controls
{
  int method;                     /* interpolation method    */
  int solution_weight_index;      /* default solution index  */
  int gradient_weight_index;      /* default is the gradient weight */
  int idw_exponent;               /* 1/d, 1/d^2, 1/d^3 option for IDW */
  cxboolean principal_solution_p; /* globally force central donor solution */
  cxboolean principal_gradient_p; /* globally force central donor gradient */
  int tolerance_type;             /* tolerance type - user specified (default), mesh size based, precision (REAL_MIN) */
  real tolerance;                 /* tolerance value */
  cxboolean deltax_tolerance_p;   /* enforce deltax tolerance during lsf matrix formation */
  real deltax_tolerance;          /* tolerance in deltax */
  /* experimental/future options - start  */
  cxboolean model_specific_p;      /* model specific weights - vof request */
  int model_specific_index;        /* weight index used for model specific weights */
  cxboolean compute_gradient_p;    /* compute gradient at the receptor directy via GGCB (experimental) */
  cxboolean rg_extrapolation_p;    /* use \phi = \sum w*\phi + w'*\grad\phi\dot \vec{dr}*/
  cxboolean rg_extrapolation_type; /* bounding cell only, w' definition above */
  cxboolean specify_location_p;    /* redefine interpolation location other than receptor centroid */
  cxboolean virtual_receptor_p;    /* use virtual cell to increase layers of interpolation - at overset interface */
  cxboolean high_order_p;          /* */
  cxboolean matrix_interpolation_p; /* \phi = [M] x \Phi using AMG structure - performance/streamline/high order */
  /* experimental options - end  */
} chimerical;
#if DEBUG
FLUENT_EXPORT void My_Algorithm_Tracer_By_Name(char *);
FLUENT_EXPORT void My_Algorithm_Tracer(char *, Svar nv);
FLUENT_EXPORT void My_Gradient_Tracer(char *, Svar nv, Svar nvg);
#endif
#endif /*_FLUENT_OVERSET_NUMERICS_H */
