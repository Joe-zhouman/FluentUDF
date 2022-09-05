/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/* Contains parameters, structures, variables and functions related to non-/partially-premixed model lookup table
   creation and interpolation */

#ifndef _FLUENT_PDF_TABLE_H
#define _FLUENT_PDF_TABLE_H

#include "dll.h"

extern FLUENT_EXPORT cxboolean pdf_multi_tabulation;
extern FLUENT_EXPORT cxboolean Need_Pdf_Pollut_Point;
extern FLUENT_EXPORT cxboolean pdf_table_nodes_dynamic;
#define NUM_PP 56  /* number of elements in par_premix_poly array */
extern FLUENT_EXPORT real *par_premix_poly;
extern FLUENT_EXPORT real *par_premix_poly_sec;
extern FLUENT_EXPORT int n_table_scalars;
#define FMEAN_SMALL  (real)1.0e-10
#define FVAR_SMALL   (real)1.0e-4
#define SMALL_WEIGHT (real)1.0E-6
#define MAX_ENTHALPY_GRID_PTS 500

#define ENTHALPY_ADIABATIC 0
#define ENTHALPY_COLD -1
#define ENTHALPY_HOT  1

#define LINEAR 0
#define POLYNOMIAL 2
#define Pollut_Solve_Size_Max 3 /* this is good enough as no pollutant var have more than 3 fields in tables*/


enum
{
  TABLE_SCALAR_YCVAR = 0,
  TABLE_SCALAR_HOR /* heat of reaction */
};

enum
{
  NO_CHANGE = 0,
  OLD_VERSION = 1,
  NEWLY_GENERATED,
  MULTIPLE_FLAMELET_FILES
};

enum
{
  VERSION_PRE_5_0 = 200,
  VERSION_5_0 = 300,
  VERSION_6_0 = 400,
  VERSION_6_1 = 410,
  VERSION_6_2 = 420,
  VERSION_13_0 = 430,
  VERSION_14_5 = 440,
  VERSION_15_0 = 450,
  VERSION_18_0 = 460,
  VERSION_19_5 = 470,
  VERSION_21_2 = 480
};

enum
{
  STD_SINGLE_FLAMELET = 0,
  STD_MULTIPLE_FLAMELET,
  FLUENT_UNSTEADY_FLAMELET,
  STD_MULTIPLE_NONADIA_FLAMELET
};

/* Define pdf function type and quadrature for 2 mixture fraction pdf. */
enum
{
  PDF_TYPE_DELTA,
  PDF_TYPE_BETA
};

#define SCADISTOL 1.e-4
#define COLD_SIDE 0.75
#define COLD_FLA  0.667
#define pdf_spe_loop(i) for(i=0;i<n_spe_pdf;i++)

enum
{
  FUEL_STREAM,
  SECONDARY_STREAM
};

enum
{
  CONSTANT_TEMPERATURE,
  ADIABATIC_ENTHALPY,
  CONSTANT_ENTHALPY,
  CONSTANT_COMPOSITION
};
enum
{
  FGM_NONAD_4D,
  FGM_NONAD_5D
};

typedef struct pdf_empirical_struct
{
  int ico2, iwater, icarbon, ihydrogen, iso2, isulfur;
  real href_empirical[N_STRMS];
  real mw_empirical[N_STRMS];
} Pdf_Empirical;

typedef struct pdf_define_struct
{
  int iequfl;
  int lmulti;
  int empirical[N_STRMS];
  real hcombustion_empirical[N_STRMS];
  real cp_empirical[N_STRMS];
  real tinm[N_STRMS]; /* temperatures at inlets */
  /* IMPORTANT: The ordering of streams is as follows:
     0        = primary fuel
     ......  = secondary streams, for the current 2-mixture fraction
     implementation this is 1
     nstrm-1 = oxidiser stream, this is always the last index.
     so in the current implementation:
     for the single mixture fraction case, this is 1,
     and for the two mixture fractions cases, this is 2.*/
  real rfl[N_MF];
  real tmin, tmax, tmaxratio, tloss, tadd;
  int frozen_boundaries;
  int include_equil_flamelet;
  int nfl;
  int nfl2;
  int nne;
  int nne_cold;
  int nne_hot;
  int nstrm;    /*number of streams */
  int nmf;    /*number of mixture fractions */
  int nfbm[N_MF];
  int numfl;
  int num_nonadfla;
  real scadmx;
  cxboolean mole_or_mass;
  int max_species;
  cxboolean nonAdiaLamFlameSpeed;
  cxboolean premixFlamelet;
  int n_table_scalars;
  cxboolean strained_fla;
  int xnfgm_nh;
  int xnfgm_nf;
  int xnfgm_nx;
  cxboolean fla_sl_available;
  real fsto;
  cxboolean lam_prop_tab;
} Pdf_Define;

typedef struct table_point_struct
{
  cxboolean success;
  real temp ;
  real den ;
  real *xmol ;
  real cp;
  real mol_wt ;
  real kin_src ;
  real enth;
  Pollut_Rate **pdf_s_pollut;
  real *pollut_rates;
  real *scalars;
} Table_Point;

typedef struct prepdf_struct
/* the variables in this structure are used in the mean properties
   calculation stage. They are used in generating the pdf tables and also
   when computing the integrated properties on the fly */
{
  int n_pdf_points[N_MF]; /*number of points for each mixrure fractions
          for PDF integrations*/
  real *stoich ;  /*stoichiometric coefficients in mixed-is-burnt model */

  real *fpm[N_MF] ; /* mixture fraction values for integration with the PDF's */
  real *wtm[N_MF]; /* persentage probability at each location above */
  cxboolean *point_active[N_MF]; /* the point is required for the mean properties calculation (the weights wtm are non-zero) */

  real *xm;   /*work array for reacted mixture mole fractions */
  real *xmolic; /*work array for unreacted mixture mole fractions */
  real *ym;   /*work array for reacted mixture mass fractions */

  real *tmin_curve;
  real *tmax_curve;
  real **tmin_slice;
  real **tmax_slice;
  Table_Point *rich_limit[N_MF];
  Table_Point rich_limit_2;
  real htop_rich, hbot_rich;
  Table_Point *curve;
  Table_Point **slice;
  Table_Point ***volume;
  Table_Point ***slice3d;
} Prepdf;

typedef struct pdf_file_struct
/* the variables in this structure are saved in the pdf file*/
{
  real xinm[N_STRMS][MAX_PDF_SPECIES]; /* mole fractions at inlets */
  real yinm[N_STRMS][MAX_PDF_SPECIES]; /* mass fractions at inlets */

  real *fmeanm[N_MF]; /* mixture fraction intervals in PDF file,
       in the current implementation
       this is the same as fpm for the beta function option */
  real *ffl ;/* mixture fraction variance intervals in PDF file */
  real *ffl2;
  real *hbar_hot ;
  real *hbar_cold ;
  real *hbar_enth ;
  real *hbar_postproc;
  /* Pdf instantaneous property values 2 mixture fraction adiabatic */
  Table_Point **adia2mf;
  /* Pdf instantaneous property values 2 mixture fraction nonadiabatic */
  Table_Point  ***nonadia2mf;
  /* non-adiabatic multiple flamelets */
  /* Pdf integrated property values 1 mixture fraction adiabatic */
  Table_Point **adia1mf ;
  /* Pdf integrated property values 1 mixture fraction nonadiabatic */
  Table_Point  ***nonadia1mf ;
  /* Pdf integrated property values multiple strained flamelets adiabatic */
  Table_Point  ***adiastrained ;
  /* Pdf integrated property values multiple strained flamelets nonadiabatic */
  Table_Point  ****nonadiastrained ;
  Table_Point  ****premix_flamelet_tab; /*for 4D adiabatic FGM*/
  Table_Point  ****nonadia_fgm_props;
  Table_Point  *****nonadia_fgm_tab; /*Full 5D nonadiabatic FGM*/
  Table_Point  ****adia2mf_tab; /* Full 4D tabulation of mean 2mf tables */
  Table_Point  *****nonadia2mf_tab; /* Full 5D tabulation of mean 2mf tables */
  real ****xmolxe ;
  real ****xmol0xe ;
  real *scadd ; /* scalar dissipation includes 0 equilibrium slice */
  real **exp_table ;
  real *prmx_alpha; /* reaction progress = c = Sum( prmx_alpha_i * Y_i ) / equil */
  real *Yc_eq; /* denominator fcn(mf) to normalize reaction progress */
  real **Yc_eq_2d;
  real **Yc_eq_sqr;
  real **Yc_eq_nonad;
  real **Yc_in_nonad;
  real **Nfgm_enth;
  real ***lam_mu;
  real ***lam_ktc;
} Pdf_File;

typedef struct flamelet_import_struct
{
  real *scd;/* scalar dissipation */
  real *sr;/* strain rate */
  real *react_progress; /* premixed flamelets */
  int *num_grd_pnts ; /*Number of grid points of a flamelet*/
  real **phit_x ;
  real ***phix_x ;
  real **cdot; /* premixed flamelet source */
  real *z_sto ;
  real **z_x ;
  real **z_c ;
  real **z_h ;
} Flamelet_Import;

typedef struct nonadia_fgm_import_struct
{
  int num_fpts ; /*number of mixture fraction points*/
  int num_cpts ;
  int num_hpts ;
  int num_h_cold_pts ;

  real    z_sto  ;  /* constant value*/

  real ***temp   ;  /* T [ih][ic][iff]*/
  real ****yi    ;  /* yi[ih][ic][ins][iff]*/
  real ***ycdot  ;  /* ycdot [ih][ic][iff] */
  real ***fgrid  ;  /* f[ih][ic][iff] */
  real ***cgrid   ;  /* c[ih][ic][iff] */
  real **hgrid   ;  /* h[iff][ih] */
} Nonadia_Fgm_Import;


typedef struct flamelet_expert_struct
{
  real expinv;
  int flamtyp ;
  real flammult ;
  real flampar ;
  real fvarlim ;
  double dfsto; /* stochiometric mixture fraction times 2*/
} Flamelet_Expert ;

typedef struct pdf_variables_struct
/*the variables in this structure are computed after reading the pdf file
  and need not be saved in the pdf file */
{
  real *htop_curve; /*enthalpies at top temperature curve */
  real *hbot_curve; /* enthalpies at bottom temperature curve */
  real **htop_slice ; /*enthalpies at top temperature slice */
  real **hbot_slice ; /*enthalpies at bottom temperature slice */
  real *hadia_curve; /* adiabatic mixture enthalpy curve */
  real **hadia_slice; /* adiabatic mixture enthalpy slice */
  real **enth_slice; /* enthalpy of mixture in properties table */
  real ***enth_volume; /* enthalpy of mixture in properties table for 2 mixture fractions*/
  Table_Point ***table_interpolated; /*for multiple strained flamelets nonadiabatic */
  Table_Point  ***nonadia_c; /* for partially premixed non adiabatic single mixture fraction */
  real entmax;
  real entmin;
  real hinm[N_STRMS];
} Pdf_Variables;

typedef struct pdf_grid_struct
{
  int nfbm[N_MF];
  int nfl;
  int nfl2;
  int nne;
  int nne_cold;
  int nne_hot;
  real *fmean[N_MF];
  real *fvar;
  real *cvar;
  real *hbar_cold;
  real *hbar_hot;
} Pdf_Grid;

typedef struct multi_fgm_struct
{
  cxboolean adia;
  cxboolean flame_index_uds;
  cxboolean flame_index_udm;
  int flame_index_var_id;
  int premix_grid[5];
  int diff_grid[5];
  real fgm_fac_min;
  real fgm_fac_max;
  char **first_table_sp_names;
  Table_Point *****multi_fgm_tab;
} Multi_Fgm ;

typedef struct flamelet_flame_speed_struct
{
  int num_fpts ; /*number of mixture fraction points*/
  int num_hpts ;
  int num_spe  ;
  real fuel_temp  ;
  real ox_temp    ;
  real yi_fuel[MAX_PDF_SPECIES]   ;  
  real yi_oxid[MAX_PDF_SPECIES]   ;  
  real fgrid[1000]     ;  /* f[iff] */
  real hgrid[1000]     ;  /* h[ih] */
  real **fl_sl    ;  /* sl[ih][iff] */
} Flamelet_Sl;

extern FLUENT_EXPORT Multi_Fgm *mfgm;
extern FLUENT_EXPORT Prepdf *pr ;
extern FLUENT_EXPORT Pdf_File *pf ;
extern FLUENT_EXPORT Flamelet_Import *fl ;
extern FLUENT_EXPORT Pdf_Variables *pv ;
extern FLUENT_EXPORT Pdf_Define *pd ;
extern FLUENT_EXPORT Pdf_Empirical *pe ;
extern FLUENT_EXPORT Flamelet_Expert *fe ;
extern FLUENT_EXPORT Pdf_Grid *pdf_grid ;
extern FLUENT_EXPORT cxboolean Multi_Fgm_Ad;
extern FLUENT_EXPORT Nonadia_Fgm_Import *Nfgm;
extern FLUENT_EXPORT Flamelet_Sl *Fla_Sl;

typedef struct
{
  int nID;
  char *Name;
} PDF_VAR;

/*free table point */
#define FREETP(value) {                                 \
    CX_Free(value.xmol);                                \
    value.xmol = NULL;                                  \
}
#define FREE_TP_SCALARS(value)\
{\
 if(NNULLP(value.scalars))\
    CX_Free(value.scalars);\
    value.scalars=NULL; \
}

#define FREETP_POLLUT(value) { \
int ipz; \
if(NNULLP(value.pdf_s_pollut))\
    {\
for (ipz=0; ipz< MAX_POLLUT_EQNS ; ipz ++) \
{ \
FREE_POLLUT_RATE(value.pdf_s_pollut[ipz]) \
}\
CX_Free(value.pdf_s_pollut);\
value.pdf_s_pollut=NULL;}}

#define FREE_PDF_SPECIE_NAMES {\
if(NNULLP(pdf_species_names))\
FREE_ARRAY_2(pdf_species_names,0,pdf_species_names_length-1,0,CHAR_SIZE-1,sizeof (char));\
pdf_species_names=NULL;}

#define ALLOCATE_PDF_SPECIES_NAMES(num){\
FREE_PDF_SPECIE_NAMES;\
pdf_species_names_length=num;\
if(NULLP(pdf_species_names=(char**)\
NEW_ARRAY_2(0,num-1,0,CHAR_SIZE-1,sizeof(char))))\
Error("cannot allocate pdf memory! (species names): abort\n");\
}\

#define SETNULL_POLLUT_TP(tp){\
  tp.pollut_rates =NULL ;}

#define ALLOCATE_POLLUT_TP(tp)\
{\
    if(NULLP(tp.pollut_rates))\
      {\
        int iss;\
        tp.pollut_rates = (real *) CX_Malloc(Pollut_Solve_Size_Max*Num_Pollut_Vars_Tabulated*sizeof(real));\
        for(iss=0;iss< Pollut_Solve_Size_Max*Num_Pollut_Vars_Tabulated;iss++)\
        tp.pollut_rates[iss] = 0.;\
      }\
}
#define FREE_POLLUT_TP(tp)\
{\
    if(NNULLP(tp.pollut_rates))\
       CX_Free(tp.pollut_rates);\
    tp.pollut_rates=NULL;\
}
/*AVTTP = ASSIGN_VALUE_TO_TABLE_POINT*/
#define AVTTP(RETVAL,TEMP,DEN,XMOL_SIZE,CP,POLLUT){             \
    int itp;                                                    \
    if(NNULLP(RETVAL.pollut_rates))\
      {\
        for(itp=0;itp<Pollut_Solve_Size_Max*Num_Pollut_Vars_Tabulated;itp++)\
          {\
                RETVAL.pollut_rates[itp]=0.;\
          }\
      }\
    RETVAL.success=FALSE;                                       \
    RETVAL.temp=TEMP;                                           \
    RETVAL.den=DEN;                                             \
    if(XMOL_SIZE<=0)                                            \
      RETVAL.xmol=NULL;                                         \
    else {                                                      \
      RETVAL.xmol=(real *)CX_Malloc(sizeof(real)*XMOL_SIZE);            \
    }                                                                   \
    RETVAL.cp=CP;                                               \
    RETVAL.mol_wt = 0.;                                         \
    RETVAL.enth  = 0.;                                         \
    RETVAL.pdf_s_pollut = POLLUT;}

#define SETNULLTP(RETVAL)                                \
  {                                                      \
    memset((char *) &(RETVAL), 0, sizeof(Table_Point));  \
    RETVAL.success=FALSE;                                \
  }

#define ALLOCATE_TP_SCALARS(RETVAL)\
{\
    if(n_table_scalars > 0)\
      {\
        int iz;\
        RETVAL.scalars=(real *)CX_Malloc(sizeof(real)*n_table_scalars);\
        for(iz=0;iz<n_table_scalars;iz++)\
          {\
            RETVAL.scalars[iz] = 0.;\
          }\
      }\
    else\
    RETVAL.scalars = NULL;\
}

#define ALLOCATE_POLLUT_MEMORY(VAL) { \
int ipz; int iss; \
if(Pdf_Interpolation_Method_Linear)\
VAL.pdf_s_pollut = NULL;\
else{\
if (VAL.pdf_s_pollut == NULL){ \
VAL.pdf_s_pollut = (Pollut_Rate **) CX_Malloc( sizeof(Pollut_Rate *) * MAX_POLLUT_EQNS); \
for (ipz=0; ipz< MAX_POLLUT_EQNS ; ipz ++) \
VAL.pdf_s_pollut[ipz] = NULL;} \
for (ipz=0; ipz< MAX_POLLUT_EQNS ; ipz ++) { \
if (VAL.pdf_s_pollut[ipz] == NULL){ \
if (Pollut_Par->pollut_solve[ipz]) { \
ALLOCATE_POLLUT_RATE(VAL.pdf_s_pollut[ipz] , MAX_POLLUT_MODEL[ipz]) \
ZERO_POLLUT_RATE(VAL.pdf_s_pollut[ipz], MAX_POLLUT_MODEL[ipz], iss) \
}}}}}


#define COPY_FROM_FGM(T1,i,j,k,l,do_species,table)\
{\
    int jj,kk,psize;\
    if(table==0)\
    {\
     T1.success = P_SUCCESS_FGM_PROPS(pf_shared,i,j,k,l);\
     pdf_interp_vars_loop(jj)\
      {\
        int ins,ll,iindex,mm ;\
        ll = Pdf_Interp_Vars[jj];\
        iindex = (ll < INTERP_SP_START)? ll : (ll <INTERP_SP_MAX)? INTERP_SP_START: INTERP_POLLUT_START;\
        if (ll > INTERP_POLLUT_MAX) iindex = INTERP_SCALAR_START;\
        switch(iindex)\
        {\
          case INTERP_TEMP:\
               T1.temp =P_T_FGM_PROPS(pf_shared,i,j,k,l);\
            break;\
          case INTERP_RHO:\
               T1.den=P_RHO_FGM_PROPS(pf_shared,i,j,k,l);\
            break ;\
          case INTERP_CP:\
               T1.cp=P_CP_FGM_PROPS(pf_shared,i,j,k,l);\
            break ;\
          case INTERP_MW:\
               T1.mol_wt=P_MW_FGM_PROPS(pf_shared,i,j,k,l);\
            break;\
         default:\
         break;\
       }\
     }\
   }\
}

#define COPY_FGM_TO_FGM(i1,j1,k1,l1,i,j,k,l,do_species,table)\
{\
    int jj,kk,psize;\
    if(table==0)\
    {\
     P_SUCCESS_FGM_PROPS(pf_shared,i1,j1,k1,l1) = P_SUCCESS_FGM_PROPS(pf_shared,i,j,k,l);\
     pdf_interp_vars_loop(jj)\
      {\
        int ins,ll,iindex,mm ;\
        ll = Pdf_Interp_Vars[jj];\
        iindex = (ll < INTERP_SP_START)? ll : (ll <INTERP_SP_MAX)? INTERP_SP_START: INTERP_POLLUT_START;\
        if (ll > INTERP_POLLUT_MAX) iindex = INTERP_SCALAR_START;\
        switch(iindex)\
        {\
          case INTERP_TEMP:\
               P_T_FGM_PROPS(pf_shared,i1,j1,k1,l1) =P_T_FGM_PROPS(pf_shared,i,j,k,l);\
            break;\
          case INTERP_RHO:\
               P_RHO_FGM_PROPS(pf_shared,i1,j1,k1,l1)=P_RHO_FGM_PROPS(pf_shared,i,j,k,l);\
            break ;\
          case INTERP_CP:\
               P_CP_FGM_PROPS(pf_shared,i1,j1,k1,l1)=P_CP_FGM_PROPS(pf_shared,i,j,k,l);\
            break ;\
          case INTERP_MW:\
               P_MW_FGM_PROPS(pf_shared,i1,j1,k1,l1)=P_MW_FGM_PROPS(pf_shared,i,j,k,l);\
            break;\
         default:\
         break;\
       }\
     }\
   }\
}

#define COPY_TO_FGM_PRMX(pf_shared,T1,i,j,k,l,do_species)\
{\
    int jj,kk,psize;\
    pdf_interp_vars_loop(jj)\
      {\
        int ins,ll,iindex,mm ;\
        ll = Pdf_Interp_Vars[jj];\
        iindex = (ll < INTERP_SP_START)? ll : (ll <INTERP_SP_MAX)? INTERP_SP_START: INTERP_POLLUT_START;\
        if (ll > INTERP_POLLUT_MAX) iindex = INTERP_SCALAR_START;\
        switch(iindex)\
          {\
          case INTERP_TEMP:\
            P_T_FGM_PRMX(pf_shared,i,j,k,l) = T1.temp;\
            break;\
          case INTERP_RHO:\
            P_RHO_FGM_PRMX(pf_shared,i,j,k,l) = T1.den;\
            break ;\
          case INTERP_CP:\
            P_CP_FGM_PRMX(pf_shared,i,j,k,l) = T1.cp;\
            break ;\
          case INTERP_MW:\
            P_MW_FGM_PRMX(pf_shared,i,j,k,l) = T1.mol_wt ;\
            break;\
          case INTERP_SP_START:\
                    {\
                      if(do_species)\
                      pdf_interp_vars_spe_loop(kk,jj,ins)\
                        {\
                          P_XMOL_FGM_PRMX(pf_shared,i,j,k,l,ins) = T1.xmol[ins];\
                        }\
                      jj=kk;\
                    }\
            break ;\
            case INTERP_SCALAR_START:\
                    {\
                      pdf_interp_vars_scalar_loop(kk,jj,ins)\
                        {\
                          P_SCALARS_FGM_PRMX(pf_shared,i,j,k,l,ins) = T1.scalars[ins];\
                        }\
                      jj=kk;\
                    }\
            break ;\
          default:\
            break;\
          }\
      }\
}

#define COPY_TO_FGM_PROPS(pf_shared,T1,i,j,k,l,do_species)\
{\
    int jj,kk,psize;\
    pdf_interp_vars_loop(jj)\
      {\
        int ins,ll,iindex,mm ;\
        ll = Pdf_Interp_Vars[jj];\
        iindex = (ll < INTERP_SP_START)? ll : (ll <INTERP_SP_MAX)? INTERP_SP_START: INTERP_POLLUT_START;\
        if (ll > INTERP_POLLUT_MAX) iindex = INTERP_SCALAR_START;\
        switch(iindex)\
          {\
          case INTERP_TEMP:\
                           P_T_FGM_PROPS(pf_shared,i,j,k,l) = T1.temp;\
            break;\
          case INTERP_RHO:\
                          P_RHO_FGM_PROPS(pf_shared,i,j,k,l) = T1.den;\
            break ;\
          case INTERP_CP:\
                         P_CP_FGM_PROPS(pf_shared,i,j,k,l) = T1.cp;\
            break ;\
          case INTERP_MW:\
                         P_MW_FGM_PROPS(pf_shared,i,j,k,l) = T1.mol_wt ;\
            break;\
            break;\
          case INTERP_SP_START:\
            break ;\
           case INTERP_POLLUT_START:\
            break;\
            case INTERP_SCALAR_START:\
            break ;\
          default:\
            break;\
          }\
      }\
}


#define COPYTP_OPT(T1,T2,do_species) \
{\
    int jj,kk,psize;\
    T2.success = T1.success;        \
    pdf_interp_vars_loop(jj)\
      {\
        int ins,ll,iindex,mm ;\
        ll = Pdf_Interp_Vars[jj];\
        iindex = (ll < INTERP_SP_START)? ll : (ll <INTERP_SP_MAX)? INTERP_SP_START: INTERP_POLLUT_START;\
        if (ll > INTERP_POLLUT_MAX) iindex = INTERP_SCALAR_START;\
        switch(iindex)\
          {\
          case INTERP_TEMP:\
                           T2.temp = T1.temp;\
            T2.enth = T1.enth;\
            break;\
          case INTERP_RHO:\
                          T2.den = T1.den;\
            break ;\
          case INTERP_CP:\
                         T2.cp = T1.cp;\
            break ;\
          case INTERP_MW:\
                         T2.mol_wt = T1.mol_wt ;\
            break;\
          case INTERP_SP_START:\
                    {\
                      if(do_species)\
                      pdf_interp_vars_spe_loop(kk,jj,ins)\
                        {\
                          T2.xmol[ins] = T1.xmol[ins];\
                        }\
                      jj=kk;\
                    }\
            break ;\
           case INTERP_POLLUT_START:\
              {\
                pdf_interp_vars_pollut_loop(kk,jj,ins)\
                  {\
                    ll = Pollut_Solve_Size_Max*Pollut_Solve_Index[ins] ;\
                    psize = Pollut_Solve_Size[ins] ;\
                    for(mm=0;mm<psize;mm++)\
                      T2.pollut_rates[ll+mm] = T1.pollut_rates[ll+mm];\
                  }\
                jj=kk;\
              }\
            break;\
            case INTERP_SCALAR_START:\
                    {\
                      pdf_interp_vars_scalar_loop(kk,jj,ins)\
                        {\
                          T2.scalars[ins] = T1.scalars[ins];\
                        }\
                      jj=kk;\
                    }\
            break ;\
          default:\
            break;\
          }\
      }\
}

/* copy table point */
#define COPYTP(T1, T2, do_species, do_pollut)\
{\
    int iscp;\
  if(Pdf_Interpolation_Method_Linear)\
      {\
        COPYTP_OPT(T1, T2,do_species);\
      }\
    else\
  { \
    /* MPT_LOCK(COPYTP); */                             \
    if (do_species)         \
      {             \
  if(num_spe_pdf_interp == MAX_PDF_SPECIES) \
    {           \
      pdf_spe_loop (iscp)       \
        T2.xmol[iscp] = T1.xmol[iscp];    \
    }           \
  else            \
    {           \
      int iz ;          \
      for(iz=0;iz<num_spe_pdf_interp;iz++)  \
        {           \
         iscp=xmol_pdf_interp[iz] ;   \
         T2.xmol[iscp] = T1.xmol[iscp];   \
        }           \
    }           \
      }             \
    T2.mol_wt = T1.mol_wt ;       \
    T2.temp = T1.temp;          \
    T2.enth = T1.enth;          \
    T2.den = T1.den;          \
    T2.cp = T1.cp;          \
    T2.success = T1.success;        \
      if(NNULLP(T2.scalars) && NNULLP(T1.scalars))\
      {\
        int iz;\
        for(iz=0;iz<n_table_scalars;iz++)\
          {\
            T2.scalars[iz] = T1.scalars[iz];\
          }\
      }\
  }\
    if (do_pollut) { int ipz;     \
      for (iscp=0; iscp< MAX_POLLUT_EQNS ; iscp ++) { \
  if (Pollut_Par->pollut_solve[iscp]) {        \
    T2.pdf_s_pollut[iscp]->fwdrate = T1.pdf_s_pollut[iscp]->fwdrate; \
    T2.pdf_s_pollut[iscp]->revrate = T1.pdf_s_pollut[iscp]->revrate; \
  T2.pdf_s_pollut[iscp]->quasirate = T1.pdf_s_pollut[iscp]->quasirate; \
  for (ipz = 0; ipz < MAX_POLLUT_MODEL[iscp]; ipz++)  \
    T2.pdf_s_pollut[iscp]->rate[ipz] = T1.pdf_s_pollut[iscp]->rate[ipz];}}} \
  /* MPT_UNLOCK(COPYTP); */}

#define INIT_PDF_DEFINE_STRUCTURE \
{pd->iequfl = 0;pd->lmulti = 0; \
pd->empirical[0] = RP_Get_List_Ref_Boolean ("prepdf/flags", 2); \
pd->empirical[1] = RP_Get_List_Ref_Boolean ("prepdf/flags", 3); \
pd->empirical[2] = 0; \
pd->tinm[0] = 300; pd->tinm[1] = 300; pd->tinm[2] = 300; \
pd->hcombustion_empirical[0]=RP_Get_List_Ref_Float ("prepdf/equil-real-params", 2); \
pd->cp_empirical[0]=RP_Get_List_Ref_Float ("prepdf/equil-real-params", 3); \
pd->hcombustion_empirical[1]=RP_Get_List_Ref_Float ("prepdf/equil-real-params", 4); \
pd->cp_empirical[1]= RP_Get_List_Ref_Float ("prepdf/equil-real-params", 5); \
pd->hcombustion_empirical[2]=0; pd->cp_empirical[2]=0; \
pd->rfl[0]=RP_Get_List_Ref_Float ("prepdf/equil-real-params", 0); \
pd->rfl[1] = RP_Get_List_Ref_Float ("prepdf/equil-real-params", 1); \
pd->tmin=RP_Get_List_Ref_Float ("prepdf/equil-real-params", 6); \
pd->tmax = 1; pd->tmaxratio=RP_Get_List_Ref_Float ("prepdf/expert-real-params", 0); \
pd->tloss=(real) RP_Get_List_Ref_Float ("prepdf/expert-real-params", 1); \
pd->tadd=(real) RP_Get_List_Ref_Float ("prepdf/expert-real-params", 2); \
pd->frozen_boundaries=RP_Get_Integer("prepdf/frozen-boundaries"); \
pd->include_equil_flamelet=RP_Get_Boolean ("prepdf/include-equil-flamelet?") ;\
pd->nfl2=RP_Get_Integer ("prepdf/nfl2"); \
pd->nfl=RP_Get_Integer ("prepdf/nfl"); \
pd->nne=RP_Get_Integer ("prepdf/nne"); \
pd->nne_cold = (int) (COLD_SIDE * pd->nne) ; \
pd->nne_hot = pd->nne - pd->nne_cold ; \
pd->num_nonadfla = 0;\
pd->nstrm=2;pd->nmf=1; \
pd->nfbm[0]=RP_Get_Integer ("prepdf/nfb"); \
pd->nfbm[1]=RP_Get_Integer ("prepdf/nfb2"); \
pd->numfl=0; pd->scadmx=0; \
pd->mole_or_mass=FALSE; pd->max_species=RP_Get_Integer("prepdf/max-species"); \
pd->nonAdiaLamFlameSpeed=FALSE; \
pd->premixFlamelet=FALSE;\
    pd->n_table_scalars=0;\
    pd->strained_fla = FALSE;\
    pd->xnfgm_nh=RP_Get_Integer("pdf/strained-fla-nh");\
    pd->xnfgm_nf=RP_Get_Integer("pdf/strained-fla-nf");\
    pd->xnfgm_nx=RP_Get_Integer("pdf/strained-fla-nx");\
    pd->fla_sl_available = FALSE;\
    pd->fsto = -1.0;\
    pd->lam_prop_tab=FALSE;}

#define INIT_FLAMELET_EXPERT \
{fe->expinv=1.;fe->flamtyp=0;fe->flammult=3.;fe->flampar=1.;fe->fvarlim=(real)1.E-5;fe->dfsto=(double)0.2;}

#if !RP_NODE
FLUENT_EXPORT void Fill_multi_table(void);
#endif

FLUENT_EXPORT Table_Point
Interpolate_multi_table(real fmean0, real fvar0, real fmean1, real fvar1, real h, int what,
                        cxboolean do_species, int Num_Pdf_Interp_Vars, int *Pdf_Interp_Vars);
FLUENT_EXPORT int
pdf_locate (real x, real *xx, int nx, cxboolean *on_grid_line, real tolerance, real xmin, real xmax);
FLUENT_EXPORT real pdf_interp_1d (real fmean, int nfmt, real *fmt, real *table);
FLUENT_EXPORT real
pdf_interp_2d (real fmean, real fvar, int nfmt, int nfvt, real *fmt, real *fvt, real **table,
               real fmean_max, real fvar_max);
FLUENT_EXPORT Table_Point
pdf_interp_2d_table_point (cell_t c, Thread *t, real fmean, real fvar, int nfmt, int nfvt, real *fmt, real *fvt,
                           Table_Point **table, real fmean_max, real fvar_max,
                           int what, cxboolean do_species, cxboolean do_pollut, Pollut_Cell *Pollut,
                           int Num_Pdf_Interp_Vars, int *Pdf_Interp_Vars);
FLUENT_EXPORT Table_Point
pdf_interp_flam_table_point (real fmean, real fvar, real scad, Table_Point  ***table, int what,
                             cxboolean do_species, int Num_Pdf_Interp_Vars, int *Pdf_Interp_Vars);
FLUENT_EXPORT void pdf_weights (real *fmean_local, real *fvar_local, real small, real fvar_small);
FLUENT_EXPORT Table_Point
pdf_integration_table_point (cell_t c, Thread *t, Table_Point *struct1, Table_Point **struct2,
                             int what, cxboolean do_species, cxboolean do_pollut, Pollut_Cell *Pollut,
                             int Num_Pdf_Interp_Vars, int *Pdf_Interp_Vars);
FLUENT_EXPORT Table_Point
integrate_ins_enthalpy(cell_t c, Thread *t, real h_adia, real enth, int side, Table_Point **slice,
                       cxboolean do_species, cxboolean do_pollut, real *previous_multiplier,
                       Pollut_Cell *Pollut, int Num_Pdf_Interp_Vars, int *Pdf_Interp_Vars);
FLUENT_EXPORT Table_Point
nonadia2mix_interp_table_point (cell_t c, Thread *t, real fmean1, real fmean2, real h, Table_Point  ***phi,
                                int what, cxboolean do_species, cxboolean do_pollut, Pollut_Cell *Pollut,
                                int Num_Pdf_Interp_Vars, int *Pdf_Interp_Vars);
FLUENT_EXPORT real Get_Pdf_DH (real ff1, real ff2, real h, real h_adiabatic);
FLUENT_EXPORT real Fvar_scale (real fmean, real fldim);
FLUENT_EXPORT real Scaled_fvar (real fmean, real fvar);
FLUENT_EXPORT real pdf_interp_3d (real fmean, real fvar, real h, real h_adiabatic, real  ***table);
FLUENT_EXPORT Table_Point
pdf_interp_3d_table_point (real fmean, real fvar, real h, real h_adiabatic, Table_Point  ***table,
                           int what, cxboolean do_species, real *hbar, int *h_state,
                           int Num_Pdf_Interp_Vars, int *Pdf_Interp_Vars);
FLUENT_EXPORT void
pdf_interp_flam_nonadiabatic (real fmean, real fvar, real scad, real h, real hadia, int what,
                              cxboolean do_species, cxboolean do_pollut,
                              int Num_Pdf_Interp_Vars, int *Pdf_Interp_Vars);
FLUENT_EXPORT real betai(real a, real b, real x);
FLUENT_EXPORT Pointer get_const_property (char *species, char *propname, int set_pdf);
FLUENT_EXPORT char *get_pdf_table_type (int type);
FLUENT_EXPORT int empirical_stream(void);
FLUENT_EXPORT double erfcinv(double c);
FLUENT_EXPORT void Discretize_Enthalpy (void);
FLUENT_EXPORT void fitted_fuel_index(Material *m, int *fuel_index, int *fluent_fuel_index,
                                     real yi_fuel[], real yi_oxid[], int strm_indx,
                                     cxboolean print_message);
FLUENT_EXPORT real fitted_lam_flame_speed(int fuel_index, real p, real y_f, real Tu, real Tb);

FLUENT_EXPORT Table_Point Pdf_Interpolate_3D_Table(real fmean, real fvar, real h, real h_adiab,
                                                   Table_Point ***table, cxboolean do_species,
                                                   int h_state, real hbar, int Num_Pdf_Interp_Vars,
                                                   int *Pdf_Interp_Vars, int *limit);
FLUENT_EXPORT void get_hbar_hstate(real h, real h_adiab, real fmean, real *hbot_curve,
                                   real *htop_curve, int *hstate, real *hb, int *limit);
FLUENT_EXPORT void Pdf_Integrate_Pollut_Var(cell_t c, Thread *t, real *input_params, real *rf,
                                            real *rr, Pollut_Vars_Index pvar_index,
                                            int Num_Pdf_Interp_Vars, int *Pdf_Interp_Vars);
FLUENT_EXPORT real pdf_interp_1d_lin (real fmean, int nfmt, real *fmt, real *table);
FLUENT_EXPORT real pdf_interp_1d_lin_dufl (real fmean, int nfmt, real *fmt, real *table, int ii);
FLUENT_EXPORT void Update_Pdf_Table_on_nodes(Domain *domain, cxboolean force);
FLUENT_EXPORT Table_Point Pdf_Interpolate_5D_Nfgm_Table(real fmean0, real fldim0, real fmean1, real fldim1, real h,
                                                        Table_Point *****fgm5dtab, int Num_Pdf_Interp_Vars, int *Pdf_Interp_Vars,
                                                        cxboolean get_only_kin_src);/*ryadav_delete_it_before_commiting*/

FLUENT_EXPORT real* pdf_xmol_thread_safe(void);
#endif /*_FLUENT_PDF_TABLE_H*/
