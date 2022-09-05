/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SG_POLLUT_H
#define _FLUENT_SG_POLLUT_H

#include "dll.h"

/* Define constants, macros and prototypes for pollutants */
#define MAX_FUEL_STREAMS 3   /* Make sure to modify rpvar "pollut/max-fuel-streams" */
#define MAX_FUEL_SPEC   10   /* Make sure to modify rpvar "nox/max-fuel-spec"    */
#define MAX_FSPE_STREAM  5   /* Make sure to modify rpvar "nox/max-fspe-stream   */
#define MAX_RBFUEL_SPEC  5   /* Make sure to modify rpvar "nox/max-rbfuel-spec"  */
#define MAX_SOOT_PREC    5   /* Make sure to modify rpvar "soot/max-prec-spec"   */
#define MAX_SGROW_SPEC   5   /* Make sure to modify rpvar "soot/max-sgs-spec"    */
#define MAX_SOOT_FUEL    3   /* Make sure to modify rpvar "soot/max-soot-fuel"   */
#define MAX_PREC_COEFF  34   /* 1 + 3*11 */
#define MAX_REAC_FUEL   11   /* Number of rates in fuel NOx model */
#define MAX_REAC_SNCR   10   /* Number of rates in sncr model */
#define MAX_REAC_SOX    24   /* Number of rates in SOx model */
/* Define NULL Species Index */
#define POLLUT_NULL_SPECIES_INDEX -1
#define SV_SOOT_MOM_I(i) ((Svar) ((SV_SOOT_MOM_0+(i)*(SV_SOOT_MOM_1-SV_SOOT_MOM_0))))
#define SV_SOOT_MOM_M1(i) ((Svar) (SV_SOOT_MOM_I(i) +SV_SOOT_MOM_0_M1-SV_SOOT_MOM_0))
#define SV_SOOT_MOM_M2(i) ((Svar) (SV_SOOT_MOM_I(i) +SV_SOOT_MOM_0_M2-SV_SOOT_MOM_0))

#define SV_SOOT_MOM_AGG_I(i) ((Svar) ((SV_SOOT_MOM_AGG_0+ (i)*(SV_SOOT_MOM_AGG_1-SV_SOOT_MOM_AGG_0))))
#define SV_SOOT_MOM_AGG_M1(i) ((Svar) ((SV_SOOT_MOM_AGG_I(i) +(SV_SOOT_MOM_AGG_0_M1-SV_SOOT_MOM_AGG_0))))
#define SV_SOOT_MOM_AGG_M2(i) ((Svar) ((SV_SOOT_MOM_AGG_I(i) +(SV_SOOT_MOM_AGG_0_M2-SV_SOOT_MOM_AGG_0))))


/* Scalar equations solved for pollutants */
typedef enum
{
  EQ_NO = 0,
  EQ_HCN,
  EQ_NH3,
  EQ_N2O,
  EQ_UREA,
  EQ_HNCO,
  EQ_NCO,
  EQ_SO2,
  EQ_H2S,
  EQ_SO3,
  EQ_SH,
  EQ_SO,
  EQ_SOOT,
  EQ_NUCLEI, /*This ID:13 has been used in rfcell.scm to identify this eq-name. In case of modification, make sure to update the scheme file also*/
  EQ_CTAR,
  EQ_HG,
  EQ_HGCL2,
  EQ_HCL,
  EQ_HGO,
  EQ_CL,
  EQ_CL2,
  EQ_HGCL,
  EQ_HOCL
} EQ_Pollut;

#define IT_NOX_START    EQ_NO
#define IT_SOX_START    EQ_SO2  /* Make sure to modify rpvar "pollut_sox/eq_start"  */
#define IT_SOOT_START   EQ_SOOT /* Make sure to modify rpvar "pollut_soot/eq_start" 2 places*/
#define IT_HG_START     EQ_HG   /* Make sure to modify rpvar "pollut_hg/eq_start" 2 places*/

/*
  Please make sure that you update storage.h, sg_mem.h and sg_pdf.c
  according to the enumerations defined below. Also look
  for SV_PDF_xxx and update their occurances.
*/
/*The enum should be defined in a way that for a given equation, all options should be together*/
typedef enum
{
  NO_THERMAL,
  NO_PROMPT,
  NO_FUEL_HCN,
  NO_FUEL_NH3,
  NO_N2O,
  NO_REBURN,
  NO_SNCR_NH3,
  NO_SNCR_NCO,
  HCN_FUEL,
  HCN_REBURN,
  NH3_FUEL,
  NH3_SNCR,
  NH3_SNCR_UREA,
  N2O_SELF,
  N2O_SNCR,
  UREA_SNCR,
  HNCO_SNCR,
  NCO_SNCR,
  SOOT_YI,
  SOOT_YI_NUC_USER,
  SOOT_YI_SGS_USER,
  SOOT_YI_OXID_USER,
  SOOT_NUC,
  SOOT_NUC_NUC_USER,
  SOOT_NUC_COAG_USER,
  POLLUT_USER,
  MULTI_NO,
  MULTI_HCN,
  MULTI_NH3,
  MULTI_N2O,
  MULTI_UREA,
  MULTI_HNCO,
  MULTI_NCO,
  MULTI_SOOT,
  MULTI_NUCLEI,
  MAX_POLLUT_INDEX /*if any change here, modify it in pdf_props.h: need to fix this*/
} Pollut_Vars_Index;

typedef enum
{
  FUEL = 0,                               /* Fuel specie index for Prompt model*/
  RBFUEL = MAX_FUEL_SPEC,                 /* Reburn fuel species index */
  SNCRSP = MAX_FUEL_SPEC + MAX_RBFUEL_SPEC, /* SNCR species index        */
  PRECSP,
  SGROWS = PRECSP + MAX_SOOT_PREC,
  SOOT_FUEL = SGROWS + MAX_SGROW_SPEC,
  SOOT_OXID = SOOT_FUEL + MAX_SOOT_FUEL,
  O2,
  O,
  OH,
  H2,
  H,
  H2O,
  N2,
  N,
  CO,
  CH,
  CH2,
  CH3,
  S,
  C2H2,
  C6H6,
  C6H5,
  CO2,
  MAX_FLUENT_SPEC
} Pollut_Species_Index;

#define IDX(f) MAX_FLUENT_SPEC + EQ_##f
#define MAX_POLLUT_SPEC MAX_FLUENT_SPEC + MAX_POLLUT_EQNS

enum
{
  POLLUT_NOX = 0,
  POLLUT_SOX,
  POLLUT_SOOT,
  POLLUT_HG
};

enum
{
  NUC_NUC = 0,
  NUC_COAG,
  YI_NUC,
  YI_SGS,
  YI_OXID
};
typedef enum
{
  FUEL_G = 0,
  FUEL_L,
  FUEL_S
} Pollut_Fuel_Type;

typedef enum
{
  IN_PDF = 0,
  OUT_PDF,
  SET_VAR,
  GET_VAR
} Pollut_Io_Pdf;

typedef enum
{
  THERMAL_NOX = 0,
  PROMPT_NOX,
  FUEL_NOX,
  N2OPATH,
  REBURN,
  SNCR,
  USER_NOX,
  MAX_NOX_MODEL
} NOx_Model;

typedef enum
{
  SOOTM_NUCL = 0,
  SOOTM_SURF,
  SOOTM_OXID,
  MAX_SOOTM_MODEL
} Soot_Mass_Model;

typedef enum
{
  NUCLEI_NUCL = 0,
  NUCLEI_COAG,
  MAX_NUCLEI_MODEL
} Soot_Nuclei_Model;

enum
{
  FULL_EQUILIBRIUM = 0,
  PARTIAL_EQUILIBRIUM,
  LOCAL_MASS_FRACTION
};

/* Arrhenious Rate expression */
typedef struct Rate_Const_struct
{
  real A, B, C;
} Rate_Const;

typedef struct Rate_Const_d_struct
{
  double A, B, C;
} Rate_Const_D;

typedef struct pollut_tci_parameters
{
  cxboolean turbulent;  /* Flag indicating if turbulence interaction is ON */
  int turb_mode;        /* 0: none; 1: T; 2: T + S1; 3: S1 + S2; 4: mixture fraction*/
  int pdf_points;       /* Number of points in PDF table */
  int tvar_method;
  int pdf_type;
  int tmax_method;
  real tmax_value1;
  real fmin1, fmax1;    /* Temperature and species mass fraction limits */
  real fmin2, fmax2;
} Tci_Params;

typedef struct pollut_param_struct
{
  EQ_Pollut pollut_equ;
  cxboolean pollut_solve[MAX_POLLUT_EQNS];
  Pollut_Fuel_Type pollut_type[MAX_FUEL_STREAMS];  /* 0: gas, 1: oil, 2: coal */
  Pollut_Io_Pdf pollut_io_pdf;

  /* fuel streams */
  int nfstreams;                                   /* number of fuel streams: maximum 3 */
  int pdfs_id[MAX_FUEL_STREAMS];                   /* pdf stream index */
  int fuel_type[MAX_FUEL_STREAMS];                 /* 0: gas, 1: oil, 2: coal */
  int nfspe[MAX_FUEL_STREAMS];                     /* number of fuel species */
  int fuel_idx[MAX_FSPE_STREAM][MAX_FUEL_STREAMS]; /* fuel species index */
  int fuel_dup[MAX_FSPE_STREAM][MAX_FUEL_STREAMS]; /* flag-up duplicate fuel species */

  /* N2O quasi model */
  cxboolean n2o_quasi;

  /* SNCR reagent and water injection */
  int sncr_species_index, sncr_injection_type, sncr_pdf_stream_id;
  real sncr_pdf_f_reagent;
  int h2o_species_index, h2o_pdf_stream_id;
  real h2o_pdf_frac;

  /* Advanced options */
  cxboolean plot_rate_fuel, plot_rate_sncr, plot_rate_sox;

  /* tar from coal volatiles */
  int ctar_nfs;                                    /* number of fuel streams: maximum 3 */
  int ctar_pdfsid[MAX_FUEL_STREAMS];               /* pdf stream index */
  int ctar_nfspe[MAX_FUEL_STREAMS];                /* number of fuel species */
  int ctar_fuelidx[MAX_FSPE_STREAM][MAX_FUEL_STREAMS]; /* fuel species index */
  real ctar_frac[MAX_FUEL_STREAMS];                /* mass fraction of tar in coal volatiles */

  /* Species list */
  struct
  {
    int idx; /* Species global index */
    real mw; /* molecular weight */
  } sp[MAX_POLLUT_SPEC];
  real mw_fluentsp[MAX_SPE_EQNS_PDF]; /* storage for fluent species molecular weights */
  /* Flow properties */
  real uni_R;  /* J/mole/K */
  cxboolean turbulent;  /* Flag indicating if turbulence interaction is ON */
  cxboolean pdf_all_cells; /* if TRUE apply pdf integrations in all cells */

  int turb_mode;        /* 0: none; 1: T; 2: T + S1; 3: S1 + S2; 4: mixture fraction*/
  int turb_speidx;      /* Index of species used for pollut/turbulence interaction */
  int pdf_points;       /* Number of points in PDF table */
  int tvar_method;
  int pdf_type;
  int tmax_method;
  real tmax_value1;
  real fmin1, fmax1;    /* Temperature and species mass fraction limits */
  real fmin2, fmax2;
  cxboolean skip_pdf_pollut, do_pollut;

  Rate_Const K_O[2], K_OH;
} Pollut_Parameter;

typedef struct pollut_cell_struct
{
  real temp_m;
  real den;
  real press;           /* Pa (N/m^2) */
  real cell_V;          /* cell volume */
  real meanmw;          /* Mean molecular weight kg/kg-mol */
  real fmean;           /* Mean mixture fraction */
  real r_fuel_gls[MAX_FUEL_STREAMS];      /* mean limiting reaction rate of gasous fuel or gas/volatile release rate from liquid/solid (kg/m^3/s) */
  real r_char[MAX_FUEL_STREAMS];          /* rate of char burn out (kg/m^3/s) (solid fuel) */
  real part_con;        /* particle concentration (kg/m^3) (solid fuel) */
  real oxy_order;       /* oxygen_order */
  real r_reagent;       /* rate of reagent release from liquid injection */
  real r_ctar;          /* rate of tar release from coal (kg/m^3/s) */
  real turb_tscale;     /* time scale of turbulence */
  real yi[MAX_POLLUT_SPEC];
  struct
  {
    real fwdrate;
    real revrate;
    real quasirate;
    real yi[MAX_POLLUT_SPEC];
    real temp;          /* K */
    real den;
    /* Molar rates of reaction : mol/m3/sec */
    real molar_rate_sncr[MAX_REAC_SNCR];
    real molar_rate_fuel[MAX_REAC_FUEL];
    real molar_rate_sox[MAX_REAC_SOX];
  } fluct;
  /* Molar rates of reaction (mean) : mol/m3/sec */
  real molar_rate_sncr[MAX_REAC_SNCR];
  real molar_rate_fuel[MAX_REAC_FUEL];
  real molar_rate_sox[MAX_REAC_SOX];
} Pollut_Cell;

#define ARRH(pollut,k)((k).A*pow((pollut)->fluct.temp, (k).B)*exp(MIN(70, MAX(-70, -(k).C/(pollut)->fluct.temp))))
#define ARRH_TR(pollut,k,tr)((k).A*pow((pollut)->fluct.temp/tr, (k).B)*exp(MIN(70, MAX(-70, -(k).C/(pollut)->fluct.temp))))
#define ARRH_TM(pollut,k)((k).A*pow((pollut)->temp_m, (k).B)*exp(MIN(70, MAX(-70, -(k).C/(pollut)->temp_m))))
#define ARRH_TS(pollut,k,ts)((k).A*pow(MAX((pollut)->fluct.temp+ts, 0.), (k).B)*exp(MIN(70, MAX(-70, -(k).C/((pollut)->fluct.temp+ts)))))

#define POLLUT_GASDEN(pollut)((pollut)->fluct.den)

/* Macro to convert mass fraction to mole concentration (mole/m^3) */
#define MOLECON(pollut,spe)(POLLUT_GASDEN((pollut))*MAX(0., (pollut)->fluct.yi[spe])*1000./Pollut_Par->sp[spe].mw)

#define NULLIDX(pollut,spe)((pollut)->sp[spe].idx == POLLUT_NULL_SPECIES_INDEX)

#define POLLUT_FRATE(pollut)((pollut)->fluct.fwdrate)
#define POLLUT_RRATE(pollut)((pollut)->fluct.revrate)
#define POLLUT_QRATE(pollut)((pollut)->fluct.quasirate)
#define POLLUT_MOLRATE_SNCR(pollut,i)((pollut)->molar_rate_sncr[i]*1.e-03)
#define POLLUT_MOLRATE_FUEL(pollut,i)((pollut)->molar_rate_fuel[i]*1.e-03)
#define POLLUT_MOLRATE_SOX(pollut,i)((pollut)->molar_rate_sox[i]*1.e-03)
#define POLLUT_FLUCTDEN(pollut)((pollut)->fluct.den)
#define POLLUT_FLUCTTEM(pollut)((pollut)->fluct.temp)
#define POLLUT_FLUCTYI(pollut,spe)((pollut)->fluct.yi[spe])
#define POLLUT_CTMAX(pollut)((pollut)->fmax1)
#define POLLUT_EQN(pollut)((pollut)->pollut_equ)
#define IDEQ(pollut)((pollut)->pollut_equ+MAX_FLUENT_SPEC)

#define ALLOCATE_POLLUT_RATE(pollut_rate, MAX_MODEL) \
{pollut_rate = (Pollut_Rate *) CX_Malloc(sizeof(Pollut_Rate)); \
 pollut_rate->rate = MAX_MODEL==0 ? NULL :(real *) CX_Malloc(sizeof(real) * MAX_MODEL);}

#define ZERO_POLLUT_RATE(pollut_rate, MAX_MODEL, is) \
{pollut_rate->fwdrate = 0.0; pollut_rate->revrate = 0.0; \
pollut_rate->quasirate = 0.0; \
for (is=0;is<MAX_MODEL;is++) if (NNULLP (pollut_rate->rate)) pollut_rate->rate[is]=0.0;}

#define FREE_POLLUT_RATE(pollut_rate) \
  if (NNULLP (pollut_rate)){ if (NNULLP (pollut_rate->rate)) {CX_Free(pollut_rate->rate); pollut_rate->rate = NULL;} \
CX_Free(pollut_rate); pollut_rate = NULL;} \

#define ALLOCATE_POLLUT_CELL(Pollut) {Pollut = (Pollut_Cell *) CX_Malloc(sizeof(Pollut_Cell));}
#define FREE_POLLUT_CELL(Pollut) {CX_Free(Pollut); Pollut = NULL;}

FLUENT_EXPORT void
Pollut_Integral(Thread *t, cell_t c,  Pollut_Cell *Pollut, Pollut_Rate *s_pollut,
                real fmean1, real fmean2, real fvar1, real fvar2, cxboolean fluc1, cxboolean fluc2);
FLUENT_EXPORT void Assign_Cell_Properties(cell_t c, Thread *thread, Pollut_Cell *Pollut);
FLUENT_EXPORT int Pollut_Pdf_Init(void);
FLUENT_EXPORT void Model_Initialize_pollut(void);
FLUENT_EXPORT real cell_MeanMW(cell_t c, Thread *t);
FLUENT_EXPORT void fill_pdf_interpolation_input_params(cell_t c, Thread *t, real *input_params);
FLUENT_EXPORT cxboolean Pollut_Init(Domain *domain, cxboolean update_properties);
FLUENT_EXPORT void Get_Turb_Rate(cell_t c, Thread *t, Pollut_Cell *Pollut, Pollut_Rate *s_pollut);
FLUENT_EXPORT real get_oeq(Pollut_Cell *Pollut, int o_mode);
FLUENT_EXPORT real get_oheq(Pollut_Cell *Pollut, int oh_mode, real o_eq);
FLUENT_EXPORT void check_spe_duplication(void);
FLUENT_EXPORT int set_pollut_turb_params(Domain *domain, char *pn1, int pollut_flag);
FLUENT_EXPORT real reagent_release_rate(Thread *t, cell_t c);
FLUENT_EXPORT void fuel_release_rate(Thread *t, cell_t c, int ifstream, real r_reagent, real cell_V,
                                     real *r_fuel_gls_ifs, real *r_char_ifs);
FLUENT_EXPORT real oxygen_order(cell_t c, Thread *t, Pollut_Cell *Pollut);

FLUENT_EXPORT cxboolean if_sg_pollut_i(int i);

extern FLUENT_EXPORT Pollut_Parameter *Pollut_Par;
extern FLUENT_EXPORT int MAX_POLLUT_MODEL[MAX_POLLUT_EQNS];
extern FLUENT_EXPORT int Pollut_Global_Index[MAX_POLLUT_INDEX];
extern FLUENT_EXPORT int Pollut_Solve_Index[MAX_POLLUT_INDEX];
extern FLUENT_EXPORT int Pollut_Solve_Size[MAX_POLLUT_INDEX];
extern FLUENT_EXPORT int Num_Pollut_Vars_Tabulated;
extern FLUENT_EXPORT void Free_Pdf_Tables_Pollut_Data(void);
extern FLUENT_EXPORT void Fill_Pdf_Tables_Pollut_Data(Domain *domain);
extern FLUENT_EXPORT cxboolean Tab_Def_Nuc_Rates;
extern FLUENT_EXPORT cxboolean Tab_Def_Yi_Rates;
extern FLUENT_EXPORT cxboolean Soot_Rates_Udf[MAX_SOOT_UDF_VARS];
extern FLUENT_EXPORT cxboolean Soot_Udf_Add_Default_Rates[MAX_SOOT_UDF_VARS];
extern FLUENT_EXPORT void  Set_Soot_Nuc_Sgs_Mech(Pointer p, Pointer x);
#endif /* _FLUENT_SG_POLLUT_H */
