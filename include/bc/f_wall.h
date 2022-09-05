/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_F_WALL_H
#define _FLUENT_F_WALL_H

#include "dll.h"
#include "icing_bc.h"

enum
{
  THERMAL_BC_TEMPERATURE = 0,
  THERMAL_BC_HEAT_FLUX   = 1,
  THERMAL_BC_CONVECTION  = 2,
  THERMAL_BC_COUPLED     = 3,
  THERMAL_BC_RADIATION   = 4,
  THERMAL_BC_MIXED       = 5,
  THERMAL_BC_NETWORK     = 6,
  THERMAL_BC_SKIP        = 7  /* bc handled by the "shadow" */
};

enum
{

  GTEMP_BC_JACKSON_FLUX  = 0,
  GTEMP_BC_GIVEN_FLUX    = 1,
  GTEMP_BC_TEMPERATURE   = 2
};



enum
{
  RADIATION_BC_GRAY = 0,
  RADIATION_BC_SPECULAR = 1,
  RADIATION_BC_SEMI_TRANSPARENT = 2,
  RADIATION_BC_OPAQUE = 3
};

enum
{
  MOTION_BC_STATIONARY        = 0,
  MOTION_BC_MOVING            = 1
};

enum
{
  SHEAR_BC_NOSLIP           = 0,
  SHEAR_BC_SPECIFIED_SHEAR  = 1,
  SHEAR_BC_MARANGONI_STRESS = 2,
  SHEAR_BC_SPECULAR_COEFF   = 3,
  SHEAR_BC_FINITE_SLIP      = 4,
  SHEAR_BC_PARTIAL_SLIP     = 5
};

enum
{
  ROUGH_BC_STANDARD        = 0,
  ROUGH_BC_OPTION          = 1
};

enum
{
  SPECIES_BC_NEUMANN     = 0,
  SPECIES_BC_DIRICHLET   = 1,
  SPECIES_BC_REACT       = 2
};
#if RP_WALL_FILM && RP_3D
enum
{
  WALL_FILM_BC = 0, /* boundary condition film wall */
  WALL_FILM_IC = 1  /* initial condition film wall  */
};
#endif

/*MC specific data struct*/
typedef struct mc_poldpairs
{
  real pangle;
  real pint;
} MC_Poldpairs;
/*..........................*/

struct tv_wall_struct
{
  int thermal_bc;   /* thermal bc type (see enumeration above) */
  int radiation_bc;   /* radiation bc type (see enumeration above) */
  int motion_bc;                /* motion bc type (see enumeration above) */
  int shear_bc;                 /* shear bc type (see enumeration above) */
  int rough_bc;                 /* roughness models (see enumeration above) */
  int gtemp_bc;                 /* granular temperature type (see enumeration above) */
  int stabilization_method;     /* fsi thermal stabilization method*/
  icing_wall icingp;
  real d;     /* thickness */
  Profile T;      /* temperature */
  Profile q;      /* heat flux */
  Profile *q_irrad;/* irradiation */
  Profile *q_irrad_diffuse;/* diffuse irradiation */
  real *diffuse_frac;/* fraction of irradiation that is diffuse */
  cxboolean parallel_collimated_beam; /* Specify direction for irradiation w.r.t beam direction */
  cxboolean radiating_s2s_surface;  /* identify s2s radiating surface  ? */
  cxboolean critical_zone;  /* identify s2s critical surface  ? */
  real fpsc;                    /* Faces per surface cluster */
  cxboolean solar_fluxes;         /* identify surfaces with solar load  ? */
  cxboolean solar_direction;
  cxboolean solar_irradiation;
  cxboolean fsi_interface;
  cxboolean thermal_stabilization; /*fsi thermal stabilization switch*/
  Profile v_trans;  /* visible transmissivity */
  Profile ir_trans; /* IR transmissivity */
  Profile d_trans; /* Diffuse transmissivity */
  Profile v_absorb;         /* visible absorbtivity */
  Profile ir_absorb;          /* IR absorbtivity */
  Profile d_absorb;         /* Diffuse absorbtivity */
  Profile v_opq_absorb;         /* visible absorbtivity */
  Profile ir_opq_absorb;          /* IR absorbtivity */
  Profile h;      /* convective heat transfer coefficient */
  Profile Tinf;     /* ambient (free stream) temperature */
  Profile Trad;     /* ambient radiation temperature */
  Profile ex_emiss;   /* external emissivity */
  Profile in_emiss;   /* internal emissivity */
  Profile *in_band_emiss; /* band emissivity */
  Profile area_enhancement_factor;  /* for serrated surfaces */
  Profile q_dot;      /* heat generated per unit volume */
  cxboolean int_rad;              /* wall radiates internally to a specified
           temperature */
  real Trad_int;    /* internal radiation temperature */
  real sc_scale_factor;            /* fsi thermal stabilization scale factor*/
  cxboolean planar_conduction;    /* in plane conduction for thick walls ? */
  Profile caf;                    /* convective augmentation factor (gas side) */
#if RP_SHELL
  int nShellLayer;
#endif
  cxboolean react;                /* surface reactions enabled */

  Reaction_Mech *react_mech;    /* reaction mechanism on CVD walls */
  char *react_mech_name    ;    /* reaction mechanism name on CVD walls */
  real washcoat_factor;         /* wall washcoat surface area multiplier */

  int ablation_model;
  real vielle_a;
  real vielle_n;
  Profile *ablation_yi;
  cxboolean ablation_flux;

  int partially_catalytic_recombination_model;
  cxboolean partially_catalytic;
  int partially_catalytic_material;
  Profile partially_catalytic_recombination_coefficient_o;
  Profile partially_catalytic_recombination_coefficient_n;

  cxboolean relative;   /* is motion specified relative to grid? */
  cxboolean rotating;   /* rotation or translation? */
  cxboolean components;   /* specify wall velocity components? */
  cxboolean sys_coupling;
  Profile u, v, w;  /* wall velocity components */
  Profile translate_mag;  /* translation velocity magnitude */
  real NV_VEC(translate_dir); /* translation velocity direction */
  Profile omega;    /* angular speed */
  real NV_VEC(origin);    /* origin of rotation */
#if RP_3D
  real NV_VEC(axis);    /* axis of rotation */
#endif
#if RP_WALL_FILM && RP_3D
  cxboolean film_wall;          /* wall with thin liquid film */
  int film_wall_bc;             /* 0: boundary condition; 1: initial condition */
  Profile film_h;               /* film height condition */
  Profile NV_VEC(film_vel);     /* film velocity condition */
  Profile film_t;               /* film temperature condition */
  Profile film_s;               /* film passive scalar condition */
  cxboolean film_source_terms;  /* user defined film source terms */
  Profile film_h_src;           /* film height (mass) source */
  Profile NV_VEC(film_vel_src); /* film velocity (momentum) source */
  Profile film_t_src;           /* film temperature (energy) source */
  Profile film_s_src;           /* film passive scalar (mass) source */
  cxboolean film_splash_wall;   /* dpm/wall splashing */
  cxboolean film_mom_coupling;  /* film/flow momentum coupling */
  cxboolean film_relative_vel;  /* relative film initial/bc velocity */
  cxboolean film_bc_dyna_pres;  /* include film bc dynamic pressure */
  cxboolean film_vapor_wall;    /* solve condensation/vaporization on film wall */
  int film_vapor_model;         /* condensation/vaporization model */
  real film_cond_const;         /* condensation constant */
  real film_vapo_const;         /* vaporisation constant */
  Profile film_cond_rate;       /* condensation rate (user defined) */
  Profile film_vapo_rate;       /* vaporisation rate (user defined) */
  cxboolean film_contact_angle; /* film contact angle force */
  Profile film_contact_angle_mean; /* contact angle mean (gaussian distribution) */
  real film_contact_angle_rstd; /* contact angle percentage std. dev. */
  real film_contact_angle_beta; /* contact angle force scaling factor */
  cxboolean film_vof_coupling_high; /* film/vof coupling enabled/disabled */
  cxboolean film_vof_coupling_low;  /* film/vof coupling enabled/disabled */
  real film_vof_trans_high;       /* film-to-vof transition fraction criteria */
  real film_vof_trans_high_thres; /* film-to-vof transition film height high threshold */
  real film_vof_trans_high_relax; /* film-to-vof transition relaxation */
  real film_vof_trans_low;        /* vof-to-film transition fraction criteria */
  real film_vof_trans_low_thres;  /* film-to-vof transition film height low threshold */
  real film_vof_trans_low_relax;  /* vof-to-film transition relaxation */
  cxboolean film_boundary_separation; /* allow film boundary separation */
#endif
  int dpm_bc;                   /* DPM bc type (types defined in dpm.h) */
  int dpm_reinj_inj_id;   /* do not want to #include "dpm_types.h" here --> need to use Lookup_Injection_In_List() later on... */
  Objp *dpm_bc_collision_partner; /* DEM */
  int dpm_bc_collision_partner_index; /* DEM */
  UDF_Thread_Data dpm_udf;                 /* UDF fcn for DPM_BC_UDF */
  Polynomial nor_coeff_restitution;       /* coefficient of restitution for reflecting particles */
  Polynomial tan_coeff_restitution; /* tangential coefficient */
  Polynomial fric_coeff;        /* Coefficient of friction. Used in the reflecting law for rotating particles.*/
  cxboolean  erosion_generic;   /* Fluent generic wall erosion model flag */
  Polynomial erosion_rate_f;  /* Erosion rate function of impingment angle */
  Polynomial erosion_rate_c;  /* Erosion rate function of diameter */
  Polynomial erosion_rate_n;  /* Erosion rate function of velocity */
  cxboolean  erosion_finnie;    /* Finnie wall erosion model */
  real erosion_finnie_k;        /* Finnie model constant k */
  real erosion_finnie_vel_exp;  /* Finnie velocity exponent */
  real erosion_finnie_max_erosion_angle;/* Finnie wall erosion model, angle of maximum erosion */
  cxboolean  erosion_mclaury;   /* McLaury wall erosion model flag */
  real erosion_mclaury_a;       /* McLaury model constant a */
  real erosion_mclaury_b;       /* McLaury model constant b */
  real erosion_mclaury_c;       /* McLaury model constant c */
  real erosion_mclaury_w;       /* McLaury model constant w */
  real erosion_mclaury_x;       /* McLaury model constant x */
  real erosion_mclaury_y;       /* McLaury model constant y */
  real erosion_mclaury_vel_exp;  /* McLaury velocity exponent */
  real erosion_mclaury_transition_angle;/* McLaury wall erosion model, transition angle for impact angle function */
  cxboolean  erosion_oka;       /* Oka wall erosion model flag */
  real erosion_oka_e90;         /* Oka reference erosion ratio */
  real erosion_oka_hv;          /* Oka wall material Vickers hardness */
  real erosion_oka_n1;          /* Oka model constant n1 */
  real erosion_oka_n2;          /* Oka model constant n2 */
  real erosion_oka_k2;          /* Oka model constant k2 */
  real erosion_oka_k3;          /* Oka model constant k3 */
  real erosion_oka_dref;        /* Oka reference diameter */
  real erosion_oka_vref;        /* Oka reference velocity */
  cxboolean erosion_dnv;        /* DNV wall erosion model flag */
  real erosion_dnv_k;           /* DNV model constant k */
  real erosion_dnv_n;           /* DNV model constant n */
  cxboolean erosion_dnv_ductile;/* DNV model ductile wall material flag */
  cxboolean erosion_wall_shear; /* Wall shear stress erosion model flag */
  real erosion_shear_v;         /* Shear erosion model, velocity exponent */
  real erosion_shear_c;         /* Shear erosion model, empirical constant */
  real erosion_shear_pack;      /* Shear erosion model, solid phase packing limit */
  cxboolean erosion_shielding; /* Account for shielding due to presensce of solid phases */
  int film_splash_nsamp;        /* Number of splashed particles from wallfilm */
  cxboolean dpm_wall_heat_exchange; /* Enable particle-wall heat exchange during reflection */
  cxboolean film_condensation; /* Enable film condensation */
  cxboolean film_bl_model; /* Enable Boundary Layer Model */
  int crit_temp_option; /* critical temperature option */
  real crit_temp_factor; /* critical temperature factor for wall film models */
  real calibratable_temp; /* calibratable temperature for wall film models */
  real partial_evap_ratio; /* partial evaporation ratio for stochastic Kuhnke model */
  real T_deposition_offset; /* Offset between Saturation Temperature and Upper Deposition Limit for stochastic Kuhnke model */
  real T_delta;/* Upper - Lower Deposition Limit Temperature Difference for stochastic Kuhnke model */
  real A_wet; /* Laplace number constant for stochastic Kuhnke model */
  cxboolean film_stripping; /*Enable LWF film stripping */
  real crit_stripping_const; /* critical stripping constant (shear stress or Weber based) */
  real critical_we_number; /* critical weber number for separation */
  real film_separation_angle; /* film separation angle */
  int film_separation_model; /* film separation models (defined in sg_film.h */
  int  impingement_model; /* impingement models (defined in dpm.h) */
  real ra_roughness;  /* DPM model Mean roughness Ra */
  real rq_roughness;  /* DPM model RMS roughness, Rq */
  real rz_roughness;  /* DPM model Mean roughness depth, Rz */
  real rsm_roughness; /* DPM model Mean roughness slope, RSm */
  cxboolean film_allow_lwf_to_vof;   /* allow LWF-to-VOF on this wall */
  cxboolean film_allow_vof_to_lwf;   /* allow VOF-to-LWF on this wall */
  /* LWF Initialization */
  cxboolean initialize_lwf; /* Enable LWF Initialization */
  real initial_height;      /* initial film height */
  real initial_x_velocity;  /* initial film x velocity */
  real initial_y_velocity;  /* initial film y velocity */
  real initial_z_velocity;  /* initial film z velocity */
  real initial_temperature; /* initial film temperature */
  char initial_injection[80]; /* injection definition for initialization */
  real film_parcel_density; /* number of film parcels per unit surface area */
  int  minimum_number_of_parcels; /* minimum number of film parcels per face */
  cxboolean rough_nasa;          /* nasa sand-grain roughness model? */
  cxboolean rough_shin;          /* shin-et-al sand-grain roughness model? */
  cxboolean rough_ice3d;         /* variable roughness from ice3d? */

  Profile ks;                   /* wall roughness height (length) */
  Profile kcon;                 /* wall roughness constant */
  Profile ks_cp;                /* wall roughness height (length) */
  Profile kcon_cp;              /* wall roughness constant */
  Profile kcon_nasa;             /* wall roughness constant */
  Profile kcon_shin;             /* wall roughness constant */
  Profile kcon_data;             /* wall roughness constant */
  Profile cliq;                 /* liquid content in air (density) */
  Profile cliq_cp;              /* liquid content in air (density) */
  Profile dliq;                 /* droplet diameter (length)  */
  Profile kvar;                 /* varibale roughness from ice3d  */

  real vel_inf;                  /* free stream velocity */
  real temp_inf;                 /* free stream temperature */
  real length_cr;                /* characteristic length  */
  real temp_inf_cp;              /* free stream temperature */
  real length_cr_cp;             /* characteristic length  */

  Profile *yi_or_flux;            /* species mass / mole fractions or diffusive flux */
  int  *species_bc_type;  /* species mass / mole fractions */
  int phi1_type;                /* electric potential BC type */
  Profile phi1;                 /* electric potential */
  int phi2_type;                /* electric potential BC type */
  Profile phi2;                 /* electric potential */
  int li_ion_type;              /* li-ion concentration BC type */
  Profile li_ion;               /* li-ion concentration */

  int x_disp_type;              /* x displacement BC type */
  Profile x_disp_value;         /* x displacement */
  int y_disp_type;              /* y displacement BC type */
  Profile y_disp_value;         /* y displacement */
  int z_disp_type;              /* z displacement BC type */
  Profile z_disp_value;         /* z displacement */

  Profile per_dispx;            /* periodic displacement comp x */
  Profile per_dispy;            /* periodic displacement comp y */
  Profile per_dispz;            /* periodic displacement comp z */
  Profile per_imagx;            /* periodic displacement imag comp x */
  Profile per_imagy;            /* periodic displacement imag comp y */
  Profile per_imagz;            /* periodic displacement imag comp z */
  Profile freq;                 /* periodic displacement freq   */
  Profile amp;                  /* periodic displacement amplitude */
  real phase_angle;             /* periodic displacement phase angle */
  cxboolean nodal_diam;         /* periodic displacement nodal diameter */
  cxboolean fwd;                /* Forward travelling wave? */
  int method;                   /* TWM method? */
  cxboolean aero;               /* Aerodamping calculation selected? */
  cxboolean cmplx;              /* Is it a complex mode shape? */
  cxboolean norm;               /* Is it a normalized mode shape? */
  Profile pass_number;          /* periodic displacement passage number */

  Profile phi_jump;             /* potential jump at wall */
  Profile phi_resistance;       /* potential contact resistance */
  cxboolean echem_react_on;           /* whether the wall has echem reactoin or not */
  Reaction_Mech *echem_react_mech;    /* echem reaction mechanism */
  char *echem_react_mech_name;        /* echem reaction mechanism */
  cxboolean faradaic_heat;            /* include heat source due to electro-chemical reactions */
  Profile *uds;                 /* user defined scalar bc's */
  int *uds_bc_type;
  Profile dw[NUM_ENV];          /* Eulerian PDF transport model bc */
  int dw_bc_type[NUM_ENV];
  Profile *pb_disc;             /*population balance variables*/
  int *pb_disc_bc_type;
  Profile *pb_qmom;             /*population balance variables*/
  int *pb_qmom_bc_type;
  Profile *pb_smm;              /* population balance variables */
  int *pb_smm_bc_type;
  Profile pb_dqmom[1];                         /* DQMOM */
  int pb_dqmom_bc_type[1];
  Profile iac; /* interfacial area */
  int iac_bc_type;
  Profile lsf; /* level-set function */
  int lsf_bc_type;
  /*real qn[3];*/                   /* collimated radiation direction */
  Profile qn[3];                   /* collimated radiation direction */
  cxboolean mc_bsource_p;       /*For MC: true if user provides boundary source on external wall*/
  int mc_npolfnpairs;           /*Number of polar function data pairs*/
  cxboolean mc_poldfun_p;       /*For MC: true if user opts for poldfunction external wall*/
  real coll_dtheta, coll_dphi;  /* collimated direction solid angle */
  Profile *adh_angle;
  int n_adh_angle;
  Profile Sx, Sy, Sz;           /* specified shear stress components */
  real fslip, eslip;            /*finite slip condition related coefficients*/
  real partial_slip_mom_coef;     /* momentum accomodation coef for rarefied gasses */
  real partial_slip_thermal_coef; /* thermal accomodation coef for rarefied gasses */
  real partial_slip_vibelec_coef; /* vibrational-electronic accomodation coef for rarefied gasses */
  Profile R_contact;            /* contact resistance for melt problems */
  real surf_tens_gradient;      /* surf. tens. grad. for Marangoni stress */
  real gran_spec_coeff;         /* Granular specularity coefficient */
  Profile gT;                   /* Granular Temperature Profile */
  Profile q_gT;                  /* Granular flux */
  real e_gw_restitution;      /* particle-wall restitution coefficient */
  MC_Poldpairs *opoldfunp;

  real ablative_density;
#if RP_NETWORK
  Network_Objp *network_objp;
#endif
};

typedef struct solid_advect_struct /* Groups solid advection data */
{
  cxboolean vnorm_check;
  real vnorm_tol;
  int vnorm_nfail;
  real max_dot;
  real NV_VEC(xf_max_dot);
} Solid_Advect;

#define TEMPERATURE_WALL(t)\
  (THERMAL_BC_TEMPERATURE == THREAD_VAR(t).wall.thermal_bc)
#define HEAT_FLUX_WALL(t)\
  (THERMAL_BC_HEAT_FLUX == THREAD_VAR(t).wall.thermal_bc)
#define CONVECTION_WALL(t)\
  (THERMAL_BC_CONVECTION == THREAD_VAR(t).wall.thermal_bc)
#define COUPLED_WALL(t)\
  (THERMAL_BC_COUPLED == THREAD_VAR(t).wall.thermal_bc)
#define RADIATION_WALL(t)\
  (THERMAL_BC_RADIATION == THREAD_VAR(t).wall.thermal_bc)
#define MIXED_WALL(t)\
  (THERMAL_BC_MIXED == THREAD_VAR(t).wall.thermal_bc)
#if RP_NETWORK
# define NETWORK_WALL(t)\
  (THERMAL_BC_NETWORK == THREAD_VAR(t).wall.thermal_bc)
#endif

#define WALL_Q(T0,r0,T1,r1,rw)(((T1) - (T0))/((r0)+(rw)+(r1)))
/* These forms depend on q being known or already computed. */
#define WALL_TW0(q,T0,r0) ((T0) + (r0)*(q))
#define WALL_TW1(q,T1,r1) ((T1) - (r1)*(q))

#define SMALL (1.e-10)

FLUENT_EXPORT void thread_wall_default(Domain *, Thread *);

FLUENT_EXPORT real Face_Heat_Xfer_Coef_Wall(face_t, Thread *, cxboolean, cxboolean);
FLUENT_EXPORT real Face_Heat_Xfer_Coef_Wall_Yplus(face_t, Thread *, real, cxboolean);

FLUENT_EXPORT void Wall_Temperature_and_Flux(Thread *, face_t, real *A, real At,
                                             real *Tw0, real *Tw1, real *q0, cxboolean);

FLUENT_EXPORT void Set_New_Solid_Advection(cxboolean);
FLUENT_EXPORT void Set_Face_Pressure_Usage_For_Forces(cxboolean);
FLUENT_EXPORT cxboolean Get_Face_Pressure_Usage(void);
FLUENT_EXPORT cxboolean Get_New_Solid_Advection(void);
FLUENT_EXPORT void Set_Wall_Boundary_Solid_Advection(void);
FLUENT_EXPORT cxboolean Get_Wall_Boundary_Solid_Advection(Thread *t);
FLUENT_EXPORT cxboolean Moving_Or_Deforming_Solid(Thread *t);
FLUENT_EXPORT cxboolean Need_Solid_Advection(Thread *t);
FLUENT_EXPORT void Init_Solid_Advect(Thread *t, Solid_Advect *);
FLUENT_EXPORT real Moving_Wall_Advection_Vflux(face_t, Thread *);
FLUENT_EXPORT void Moving_Wall_Advection_Check(face_t, Thread *, Solid_Advect *);
FLUENT_EXPORT void Moving_Wall_Vnorm_Error(Thread *, Solid_Advect *);

FLUENT_EXPORT void Check_Moving_Wall_Velocity_Angle(Domain *);

FLUENT_EXPORT void Compute_Force_And_Moment (Domain *, Thread *, real *,
                                             real *, real *, cxboolean);

FLUENT_EXPORT void Surface_Heat_Transfer_Coef(Domain *);
FLUENT_EXPORT void Surface_Heat_Transfer_Coef_Wall_Adj(Domain *);
FLUENT_EXPORT void Surface_Heat_Transfer_Coef_Wall_Yplus(Domain *);
FLUENT_EXPORT void Surface_Heat_Transfer_Coef_Wall_Func(Domain *);
FLUENT_EXPORT void Surface_Heat_Flux(Domain *);
FLUENT_EXPORT void Surface_Nusselt_Number(Domain *);
FLUENT_EXPORT void Surface_Stanton_Number(Domain *);
FLUENT_EXPORT void Surface_Evap_Heat_Flux(Domain *);
FLUENT_EXPORT void Surface_Thin_Film_Heat_Flux(Domain *);
FLUENT_EXPORT void Surface_Quench_Heat_Flux(Domain *);
FLUENT_EXPORT void Surface_Liquid_Heat_Flux(Domain *);
FLUENT_EXPORT void Surface_Vapor_Heat_Flux(Domain *);
FLUENT_EXPORT void Surface_SBM_SP_Heat_Flux(Domain *);
FLUENT_EXPORT void Surface_SBM_Nuc_Heat_Flux(Domain *);
FLUENT_EXPORT void Wall_Ablation_Rate(Domain *);

FLUENT_EXPORT void Surface_Heat_Transfer_Coef_Mean(Domain *);
FLUENT_EXPORT void SC_Heat_Transfer_Coef_Mean(Domain *);
FLUENT_EXPORT void SC_Reference_Temperature_Mean(Domain *);
FLUENT_EXPORT void Surface_Heat_Flux_Mean(Domain *);
FLUENT_EXPORT void Surface_Nusselt_Number_Mean(Domain *);
FLUENT_EXPORT void Surface_Stanton_Number_Mean(Domain *);

FLUENT_EXPORT void Skin_Friction_Coefficient(Domain *);
FLUENT_EXPORT void Skin_Friction_Mean_Coefficient(Domain *);

FLUENT_EXPORT void Surface_Shear(Domain *);
FLUENT_EXPORT void Surface_Shear_Mean(Domain *);
FLUENT_EXPORT void faceSurface_Deposition_Rate(Thread *thread, int ns, Svar store_in);
FLUENT_EXPORT void faceSurface_Site_Coverage(Thread *thread, int ns, Svar store_in);
FLUENT_EXPORT void faceSurface_Bulk_Activity(Thread *thread, int ns, Svar store_in);
FLUENT_EXPORT void Surface_Deposition_Rate(Domain *, int ns);
FLUENT_EXPORT void Surface_Reaction_Rate(Domain *, int ns);
FLUENT_EXPORT void Surface_Site_Coverage(Domain *, int ns);
FLUENT_EXPORT void Surface_Bulk_Activity(Domain *, int ns);
FLUENT_EXPORT void Surface_Shear_NDX(Domain *, int nd);
FLUENT_EXPORT void Surface_Shear_NDX_Mean(Domain *, int nd);

FLUENT_EXPORT void MP_Surface_Shear(Domain *);
FLUENT_EXPORT void MP_Surface_Shear_NDX(Domain *, int n);

FLUENT_EXPORT void Surface_Surf_Tension(Domain *);
FLUENT_EXPORT void Surface_Surf_Tension_NDX(Domain *, int nd);

FLUENT_EXPORT void NLBF_Averaged_Temp(Domain *domain);
FLUENT_EXPORT void Wall_Temp_Out(Domain *);
FLUENT_EXPORT void Wall_Temp_In(Domain *);
FLUENT_EXPORT void Ext_Temp_Shell(Domain *);
FLUENT_EXPORT void Wall_Adj_Temp(Domain *);
FLUENT_EXPORT void Wall_Yplus_Ref_Temp(Domain *);
FLUENT_EXPORT void Surface_Rad_Heat_Flux(Domain *);
FLUENT_EXPORT void Surface_Incident_Radiation(Domain *);

FLUENT_EXPORT void DPM_Wall_Force(Domain *, int n);
FLUENT_EXPORT void DPM_Wall_Normal_Pressure(Domain *domain);
FLUENT_EXPORT void Surface_Erosion(Domain *, int);
FLUENT_EXPORT void Surface_Accretion(Domain *);
FLUENT_EXPORT void Surface_Yplus(Domain *);
FLUENT_EXPORT void Surface_Yplus_Utau(Domain *);
FLUENT_EXPORT void Wall_Cell_Yplus(Thread *);
FLUENT_EXPORT void Wall_Cell_Yplus_Utau(Thread *);

FLUENT_EXPORT void Wall_Film_Height(Domain *);
FLUENT_EXPORT void Wall_Film_Coverage(Domain *);
FLUENT_EXPORT void Wall_Film_Mass_Fraction(Domain *, int n);
FLUENT_EXPORT void Wall_Film_Mass(Domain *);
FLUENT_EXPORT void Wall_Film_Mass_M0(Domain *);
FLUENT_EXPORT void Wall_Film_Temp(Domain *);
FLUENT_EXPORT void Wall_Film_Surface_Temp(Domain *);
FLUENT_EXPORT void Wall_Film_Heat_Flux(Domain *);
FLUENT_EXPORT void Wall_Film_HTC(Domain *);
FLUENT_EXPORT void Wall_Film_Vel(Domain *, int n);
FLUENT_EXPORT void Wall_Film_Vel_Mag(Domain *);
FLUENT_EXPORT void Wall_Film_M_Imp(Domain *);
FLUENT_EXPORT void Fill_Wall_Velocities(Domain *);
FLUENT_EXPORT void Wall_Film_Leidenfrost(Domain *);

FLUENT_EXPORT real Partial_Slip_Mom_Coef(const cell_t c, const Thread *t,
                                         const int type, const real sigma);
FLUENT_EXPORT real Partial_Slip_Thermal_Coef(const cell_t c, const Thread *t,
                                             const int type, const real sigma);


#if RP_NETWORK
struct tv_network_end_struct
{
  int thermal_bc;
  Profile T;
  Profile q;
};

FLUENT_EXPORT void thread_network_end_default(Domain *, Thread *);

FLUENT_EXPORT void wall_face_velocity(const face_t f, const Thread *thread, real *u, const cxboolean distance_weighted);

#endif /* RP_NETWORK */
#endif /* _FLUENT_F_WALL_H */
