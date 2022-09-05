/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SG_HEATXC_H
#define _FLUENT_SG_HEATXC_H

#if RP_3D

/* Declaration of structures */
typedef struct heat_ex_group HXG;
typedef struct heat_ex_bank HX_BANK;
typedef struct hxc_macro_struct HXC_Macro;
typedef struct macro_cell_struct MCell;

#define HEAT_MAXNAMELEN 50
#define MAX_TABLE_ROW 20
#define MAX_TABLE_COL 20
/* Define all structures */

/* There can be multiple series of heat exchanger groups. "next" and
 * "previous" are pointers to the heat exchanger group in same series
 * whereas "Nseries" is pointer to the next series heat exchanger group */

typedef enum
{
  INPUT_CONSTANT = 0,
  INPUT_POLYNOMIAL,
  INPUT_UDF
} Input_type;

typedef struct pinput
{
  Input_type type;  /* constant, polynomial or udf */
  union
  {
    Polynomial *pl;
    real (*pudf)(real);
  } input;
  real xoutval;
} Pinput;

typedef struct heat_rej_table
{
  int ng;
  int nc;
  real Thot, Tcold;
  real gas_flow_rate[MAX_TABLE_ROW]; /* size ng */
  real cool_flow_rate[MAX_TABLE_COL]; /* size nc */
  real heat_rej[MAX_TABLE_ROW][MAX_TABLE_COL]; /* size ng*nc */
} HRTable;

typedef struct hxc_geom_struct
{
  real height, width;
  int nrow, ncol, npasses;
  real dir_2[ND_ND], dir_3[ND_ND], origin[ND_ND];
} HxcGeom;

#define RESET_TABLE(t)  memset((void *)t, 0, sizeof(HRTable))

#define RESET_INPUT(v) memset((void *)&v, 0, sizeof(Pinput))

struct heat_ex_group
{
  HXG *previous;
  HXG *next;
  HXG *Nseries;
  HXG *Pseries;
  HX_BANK *first;
  char Name[HEAT_MAXNAMELEN];
  int G_ID;
  int Num_of_hxcs;
  Pinput Cool_Flow_Rate; /* Should always be positive */
  Pinput Cool_Inlet_Temperature; /* if first HXG then provided by user else */
  Pinput Cool_Inlet_Pressure;    /* by previous HXG */
  Pinput Cool_Inlet_Quality;
  real Cool_Inlet_Enthalpy;  /* calculated from Cool_Inlet_Temperature */
  real Cool_Press_Drop;
  real Cool_Exit_Enthalpy; /* Averaged Enthalpy  over all the heat-xc
          * in parallel */
  cxboolean Aux_Stream;
  Pinput Aux_mf_Rate; /* May be  positive or  negetive */
  Pinput Aux_Enthalpy;
  cxboolean ON;
};


struct heat_ex_bank
{
  HX_BANK *next;
  HXG *parent;
  HXC_Macro *Macro;
  Thread *t;
  int Num_macros; /* total number of macros in a bank */
  int Num_cols_per_pass; /* number of macros per pass in a row */
  int Num_rows_per_pass; /* number of macros per pass in a column */
  int Num_of_Eff;
  real *Eff_Vel; /*for ntu model read this as gas flow rate*/
  real *Eff_Eff; /*for ntu model read this as ntu values*/
  Pinput Q_Rej;
  real CP;
  real Mdot;    /* Flow rate of coolant */
  real (*prop)(cell_t, Thread *, real *, int);
  real Farea;   /* Total frontal area of the bank */
  HRTable *table; /* table containing the heat rejection for various mass
                   flow rates of gas and coolant */
  HxcGeom geom;
  cxboolean ntu_method;
  cxboolean ON;
};

struct hxc_macro_struct
{
  MCell *C_List;  /* linked list of all the cells in this macro */
  real H_Inlet;   /* inlet enthalpy of the coolant */
  real Tin_g;     /* inlet temperature of the gas */
  real Pavg;
  real Face_Area;
  real Volume;
  real Mdot_c;   /* Mass flow rate of the coolant */
  real Mdot_g;   /* Mass flow rate of gas */
  real Q_Sum;
  real MdotCP;   /* heat capacity rate for gas*/
  real Eff_Ave;
};


struct macro_cell_struct
{
  struct cell_and_thread_struct c;
  real asReal;
  struct macro_cell_struct *next;
};




/* Define prototypes for heat exchanger model */
FLUENT_EXPORT void Reset_HXG_Memory(void);
FLUENT_EXPORT HX_BANK *Lookup_HX_Bank(int tid);
FLUENT_EXPORT void Set_Inlet_Enthalpy(int tid, int count, real enth_list[]);
FLUENT_EXPORT void Get_Inlet_Enthalpy(int tid, int *count, real enth_list[]);
FLUENT_EXPORT void Set_HXC_Eff(int tid, int num_of_points, real vel[], real eff[]);
FLUENT_EXPORT void Set_gas_cool_table(int tid, int gas_points, int cool_points,
                                      real thot, real tcold, real gas_fr[],
                                      real cool_fr[], real q[]);
FLUENT_EXPORT real Get_Temp(real enth, real press, HX_BANK *bnk);
FLUENT_EXPORT real Get_Enthalpy(real temp, real press, real qual, HX_BANK *bnk);
FLUENT_EXPORT void Set_HXC_Coolant(HX_BANK *bnk, real hin, real qrej, real cp, real mdot);
FLUENT_EXPORT HXG *Get_HXG(int hid);
FLUENT_EXPORT void Init_HXG(Domain *dm, const char *name, int id, int nbanks,
                            int uphxid, Pointer mdot, real cp, Pointer qrej, Pointer tin, Pointer pin,
                            real qual, real del_p, cxboolean aux, Pointer amdot, Pointer at,
                            real aq, Pointer input);
FLUENT_EXPORT void Change_HXG_Memory(Domain *domain, int id, const char *name,
                                     int uphid, int Num_of_Threads, int th_ids[]);
FLUENT_EXPORT void Allocate_HXG_Memory(Domain *domain, int id, const char *name,
                                       int uphid, int Num_of_Threads, int th_ids[]);
FLUENT_EXPORT int Ishxc(Thread *t);


FLUENT_EXPORT void Set_HXG_Enthalpy(void);
FLUENT_EXPORT void Init_HXC_Model(Domain *d, HX_BANK *bnk, int nrow, int ncol,
                                  real width, real height, real depth,
                                  real cen[], real dir_2[], real dir_3[],
                                  real tin, real pin, real qual, Pointer q_rej, real cp,
                                  real mdot, const char *fcn, const char flow_dir[], cxboolean override, cxboolean);
FLUENT_EXPORT void HXC_Draw_Macro(HX_BANK *b, int index);
FLUENT_EXPORT void HXC_Source_Term(Domain *domain);
FLUENT_EXPORT void HXC_Source(HX_BANK *bnk, int opt);
FLUENT_EXPORT void Get_HXC_Dimension(Domain *domain, Thread *t, real *h,
                                     real *w, real *d, real r[], real g[], real b[], real c[]);


FLUENT_EXPORT void Get_HXC_Info(int tid, int opt, real res[]);
FLUENT_EXPORT void Write_Macro_Report(int tid, const char *filename, const char *zname);
FLUENT_EXPORT void Set_HXC_Status(int tid, cxboolean status);
FLUENT_EXPORT HXC_Macro *Get_Macro(HX_BANK *bnk, int index);
FLUENT_EXPORT void Report_Connectivity(void);
FLUENT_EXPORT void Delete_HXG(const char *name);



FLUENT_EXPORT int Get_Ntu_Array(int tid, real ntu[], int *np, int *na);
FLUENT_EXPORT void Report_Macro_Model(int tid, const char *type, const char *zone, real *val);
FLUENT_EXPORT void Get_Aux_Mdot(int tid, real *mdot);


/* this is needed for user defined functions */
extern FLUENT_EXPORT real (*HXC_Cell_Source)(cell_t c, Thread *, real *, int);
FLUENT_EXPORT real Default_HXC_Cell_Source(cell_t c, Thread *tc, real *por, int m_index);
FLUENT_EXPORT cxboolean Ismmhxc(Thread *);
FLUENT_EXPORT void Restore_Macro_Model_Connectivity(Domain *);


/* define macros */
#define loop_macro(i,mc,mc0) for(i = 0, mc = mc0; mc != NULL; mc = mc->next, ++i)
#define loop_hxg(g, g0) for( g = g0; g != NULL; g = (g->next ? g->next : g->Nseries))

#define FIRST(p)        (p)->first      /* first child's pointer         */
#define NEXT(p)         (p)->next
#define PREV(p)         (p)->previous

#define NSERIES(g)      (g)->Nseries
#define PSERIES(g)      (g)->Pseries
#define HXG_BANK(g)     FIRST(g)
#define HXG_NAME(g)     (g)->Name
#define HXG_ID(g)       (g)->G_ID
#define HXG_NBANKS(g)   (g)->Num_of_hxcs
#define HXG_CFR(g)      (g)->Cool_Flow_Rate
#define HXG_CIE(g)      (g)->Cool_Inlet_Enthalpy
#define HXG_CIT(g)      (g)->Cool_Inlet_Temperature
#define HXG_CIP(g)      (g)->Cool_Inlet_Pressure
#define HXG_CIX(g)      (g)->Cool_Inlet_Quality
#define HXG_CPD(g)      (g)->Cool_Press_Drop
#define HXG_CEE(g)      (g)->Cool_Exit_Enthalpy
#define HXG_AS_ON(g)    (g)->Aux_Stream
#define HXG_AS_MFR(g)   (g)->Aux_mf_Rate
#define HXG_AS_ENTH(g)  (g)->Aux_Enthalpy
#define HXG_ON(g)       (g)->ON


#define HXG(b)          (b)->parent
#define HXC_MACRO(b)    (b)->Macro
#define HXC_THREAD(b)   (b)->t
#define HXC_NMACROS(b)  (b)->Num_macros
#define HXC_COLSPP(b)   (b)->Num_cols_per_pass
#define HXC_ROWSPP(b)   (b)->Num_rows_per_pass
#define HXC_NEFF(b)     (b)->Num_of_Eff
#define HXC_EFF(b)      (b)->Eff
#define HXC_EVEL(b)     (b)->Eff_Vel
#define HXC_EEFF(b)     (b)->Eff_Eff
#define HXC_QREJ(b)     (b)->Q_Rej
#define HXC_CP(b)       (b)->CP
#define HXC_PROP(b)     (b)->prop
#define HXC_MDOT(b)     (b)->Mdot
#define HXC_FAREA(b)    (b)->Farea
#define HXC_TABLE(b)    (b)->table
#define HXC_TNGFR(b)    (b)->table->ng
#define HXC_TNCFR(b)    (b)->table->nc
#define HXC_TGFR(b)     (b)->table->gas_flow_rate
#define HXC_TCFR(b)     (b)->table->cool_flow_rate
#define HXC_THR(b)      (b)->table->heat_rej
#define HXC_TTHOT(b)    (b)->table->Thot
#define HXC_TTCOLD(b)   (b)->table->Tcold
#define HXC_ON(b)       (b)->ON

#define MACRO_CLIST(b,m)      (b)->Macro[m].C_List
#define MACRO_HINLET(b,m)     (b)->Macro[m].H_Inlet
#define MACRO_TING(b,m)       (b)->Macro[m].Tin_g
#define MACRO_PAVG(b,m)       (b)->Macro[m].Pavg
#define MACRO_FACE_AREA(b,m)  (b)->Macro[m].Face_Area
#define MACRO_VOLUME(b,m)     (b)->Macro[m].Volume
#define MACRO_MDOTC(b,m)      (b)->Macro[m].Mdot_c
#define MACRO_MDOTG(b,m)      (b)->Macro[m].Mdot_g
#define MACRO_QSUM(b,m)       (b)->Macro[m].Q_Sum
#define MACRO_MDOTCP(b,m)     (b)->Macro[m].MdotCP
#define MACRO_EFF_AVE(b,m)    (b)->Macro[m].Eff_Ave

#define M_CELL(o)        (o)->c.c
#define M_CELL_THREAD(o) (o)->c.t
#define M_CELL_Q(o)      (o)->asReal



/* global variable declaration */
extern FLUENT_EXPORT int Num_of_HXG;
extern FLUENT_EXPORT HXG *Root_HXG;
extern FLUENT_EXPORT real hxc_update_time;

#endif /* if RP_3D */
#endif
