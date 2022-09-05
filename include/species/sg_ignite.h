/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/* Define constants, macros and prototypes for autoignition */

#include "dll.h"

/* Types of models for Autoginition */

typedef enum
{
  HARDENBURG_HASE,
  DOUAUD_EYZAT,
  GENERALIZED_SINGLE,
  MAX_IG_TYPES
} Ignition_Type;

/* Species for Autoginition */

typedef enum
{
  FUEL = 0,
  O2,
  CO2,
  H2O,
  N2,
  MAX_IG_SPEC
} Ignition_Species_Index;

typedef struct Ignition_Struct
{
  cxboolean ignition_enabled;
  cxboolean ignition_solved;
  cxboolean autoignition;
  cxboolean ignition_delay;
  cxboolean ignition_started;     /* flag -- once started ignition continues */
  Ignition_Type ig_type;          /* Ignition type */

  /* Ignition species list */
  struct
  {
    int idx;         /* Species global index */
    real mw;         /* molecular weight */
    real xi;         /* mole fraction */
    real yi;         /* mass fraction */
  } sp[MAX_IG_SPEC];

  /* parameters for each model */
  struct
  {
    real pre_exp;    /* Pre-exponential */
    real activation; /* Activation energy */
    real octane_num; /* Octane number of the fuel */
    real octane_exp; /* Exponential for Octane number correlation */
    real press_exp;  /* "              " pressure     "         " */
    real temp_exp;   /* "              " temperature  "         " */
    real rpm_exp;    /* "              " rpm          "         " */
    real equiv_exp;  /* "              " equivalance ratio "    " */
  } term;

  real dt;                 /* cache'd flow time step */
  real stoich_equiv_ratio; /* stoichometric equivalence ratio of the fuel */
  real f_max;              /* mixture fraction corresponding to fuel/air = 4.0 */
  real f_min;              /* mixture fraction corresponding to fuel/air = 0.1 */
  real op_press;           /* overall operating pressure */
  real rpm;                /* engine rpm  */
  real ca_2_s;             /* conversion from crank angle to seconds  */
  real stroke;             /* piston stroke  */
  real ignition_cutoff;    /* Criteria for ignition to have occured (above one) */
  real prod_fuel_cut;      /* Fuel cutoff, above which the ignition species is produced */
  real ignite_sp_cut;      /* Ignition species cutoff, above which a source is added to the
            progress variable for the premixed model, once the ignition
            species is above ignition_cutoff */
  real knock_pre_exp;      /* A in chemical rate (1/sec) (tau =1/(A exp (T_a/T))) */
  real knock_act_temp;     /* Activation temperature for knock rate */
  real dt_multiplier;      /* limit for chemical time scale is dt_m * dt */
  real ignite_sp_max;      /* limit for the value of ignition variable */
  real A1;                 /* Cache'd value of A * On^Oe (octane # doesn't change) */

} Ignition_Par;

FLUENT_EXPORT void ignition_model_init(Domain *domain);
FLUENT_EXPORT cxboolean evaluate_ignition_criteria(Domain *domain);
FLUENT_EXPORT void Model_Initialize_autoignition(void);

extern FLUENT_EXPORT Ignition_Par ai_par;

#define NULLIDX(ig_str,spe)((ig_str)->sp[spe].idx == -1)
#define C_DIFF_EFF_IGNITE(c,t)(C_R(c,t)*1.e-5 + C_MU_T(c,t)/M_species_sct)
#define WALL_CELL_P C_ITMP0
#define SV_WALL_CELL_P SV_ITMP_0
