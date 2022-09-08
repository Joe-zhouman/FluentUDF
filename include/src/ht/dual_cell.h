/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _DUAL_CELL_H
#define _DUAL_CELL_H
#include "bsp.h"
#include "neighbor.h"
typedef struct DUAL_CELL DC;
typedef struct MULTIPASS_DUAL_CELL MDC;

/*function prototypes*/
FLUENT_EXPORT BSP_Tree *Make_Binary_Tree(Thread *th);
FLUENT_EXPORT DC *Create_Dual_Cell_Connectivity(int pid, int aid);
FLUENT_EXPORT void Dual_Cell_Source_Term(Domain *domain);
FLUENT_EXPORT DC *Add_Dual_Cell_Hxc(Domain *dom, const char *name, int pid, int aid, real q_targeted,
                                    int id, real urf, int iter_intv, real parea, real aarea, cxboolean rd, int nprim,
                                    int naux, real *pmdot, real *amdot, real **qdot, real thot, real tcold, real **NTU,
                                    const char *fltyp, cxboolean multipass);
FLUENT_EXPORT void Modify_Dual_Cell_Hxc(Domain *dom, const char *oldname, const char *name, int pid, int aid,
                                        real q_targeted, int id, real urf, int iter_intv, real parea, real aarea, cxboolean rd,
                                        int nprim, int naux, real *pmdot, real *amdot, real **qdot, real thot, real tcold, real **NTU,
                                        const char *fltyp, cxboolean multipass);
FLUENT_EXPORT void Get_Frontal_Area(Domain *, int, real *);
FLUENT_EXPORT void Add_Multipass_Dual_Cell_Hxc(Domain *dom, const char *name, int pid, int *aid, int npass,
                                               real q_targeted, int id, real urf, int iter_intv, real parea, real aarea, cxboolean rd,
                                               int nprim, int naux, real *pmdot, real *amdot, real **qdot, real thot, real tcold, real **NTU,
                                               const char *fltyp, const char *t_coupling);
FLUENT_EXPORT void Modify_Multipass_Dual_Cell_Hxc(Domain *dom, const char *oldname, const char *name, int pid, int *aid,
                                                  int npass, real q_targeted, int id, real urf, int itn_intv, real parea, real aarea, cxboolean rd,
                                                  int nprim, int naux, real *pmdot, real *amdot, real **qdot, real thot, real tcold, real **NTU,
                                                  const char *fltyp, const char *t_coupling);
FLUENT_EXPORT void Free_Dual_Cell_Memory(void);
FLUENT_EXPORT void Report_Dual_Cell_Model(const char *, const char *, const char *, real *);
FLUENT_EXPORT void Initialize_Dual_Cell_Zones(const char *, real *, real *, real *, real *);
FLUENT_EXPORT void Get_Area_Average_Inlet_Temperature(int id, real *T);
FLUENT_EXPORT DC *Get_Dual_Cell_Pointer(const char *hxc_name);
FLUENT_EXPORT void Initialize_For_Alternate_Formulation(void);
FLUENT_EXPORT void Get_Dc_Ntu_Array(const char *hxc_name, real ntu[], int *np, int *na);
FLUENT_EXPORT void Delete_Dual_Cell_Hxc_Model(const char *name);
FLUENT_EXPORT void Set_Dc_Fixqrej_Data(const char *name, real *T);
FLUENT_EXPORT real Get_Heat_Rejected(DC *dc);
FLUENT_EXPORT int Isdchxc(Thread *);
FLUENT_EXPORT void Generate_Connectivity(Thread *, Thread *);
FLUENT_EXPORT void Collect_Dual_Cell_Svar(Thread *, Thread *, Svar, real **);
FLUENT_EXPORT void Collect_Dual_Cell_Data(Thread *, Thread *, real *, real **);
FLUENT_EXPORT void Send_Svar_To_Dual_Cell(Thread *, Thread *, Svar, real **);
FLUENT_EXPORT void Send_Data_To_Dual_Cell(Thread *, Thread *, real *, real **);
FLUENT_EXPORT void Restore_Dual_Cell_Connectivity(Domain *);

/*non equilibrium thermal model (NETM)*/
FLUENT_EXPORT int Get_Dual_Zone_Id(Thread *);
FLUENT_EXPORT void Initialize_NETM(Domain *, cxboolean);
FLUENT_EXPORT void Free_NETM(Domain *);
FLUENT_EXPORT void NETM_Source(Domain *);

FLUENT_EXPORT cxboolean haveNETM(Domain *);
FLUENT_EXPORT void Error_NETM(cxboolean);

#define MAX_TABLE_ROW 20
#define MAX_TABLE_COL 20
#define DEBUG_DC 0
#define MAX_PASSES 200
#define C_DHX_NBR_ID(c,t) C_STORAGE_INDEX(c,t,SV_DC_NBR_ID)
#define C_DHX_NBR_P(c,t) ((real *)THREAD_STORAGE(t,SV_DC_NBR_DATA))[9*(c)+sv_p]
#define C_DHX_NBR_T(c,t) ((real *)THREAD_STORAGE(t,SV_DC_NBR_DATA))[9*(c)+sv_t]
#define C_DHX_NBR_U(c,t) ((real *)THREAD_STORAGE(t,SV_DC_NBR_DATA))[9*(c)+sv_u]
#define C_DHX_NBR_V(c,t) ((real *)THREAD_STORAGE(t,SV_DC_NBR_DATA))[9*(c)+sv_v]
#define C_DHX_NBR_W(c,t) ((real *)THREAD_STORAGE(t,SV_DC_NBR_DATA))[9*(c)+sv_w]
#define C_DHX_NBR_R(c,t) ((real *)THREAD_STORAGE(t,SV_DC_NBR_DATA))[9*(c)+sv_rho]
#define C_DHX_NBR_RGAS(c,t) ((real *)THREAD_STORAGE(t,SV_DC_NBR_DATA))[9*(c)+sv_r]
#define C_DHX_NBR_CP(c,t) ((real *)THREAD_STORAGE(t,SV_DC_NBR_DATA))[9*(c)+sv_cp]
#define C_DHX_NBR_MDOT(c,t) ((real *)THREAD_STORAGE(t,SV_DC_NBR_DATA))[9*(c)+sv_mdot]
#define VALID_PRIM_CELL(dc,c) ((dc)->prim_nbr[(c)] !=-1)
#define VALID_AUX_CELL(dc,c) ((dc)->aux_nbr[(c)] !=-1)


#if PARALLEL
typedef enum
{
  NOT_HXC,
  PRIM_ZONE,
  AUX_ZONE,
  BOTH
} Node_Type;
#endif

typedef enum
{
  PARALLEL_FLOW,
  COUNTER_FLOW,
  CROSS_FLOW_UNMIXED,
  HXC_NONE
} Flow_Type;

typedef enum
{
  mass_weighted_average,
  conformal,
  none
} coupling;

typedef struct FIXED_HEAT_REJ
{
  int aux_inlet_id;        /*auxiliary inlet zone whose temp will be changed*/
  int prim_inlet_id;        /*primary inlet zone id*/
  real q_rej;               /*user defined heat rejection: Assumed POSITIVE*/
  real urf;
  int iter_intv;
  real T[2];                /*previous two iteration temp of the inlet zone*/
  real q_comp[2];           /*previous two iteration computed heat rejection */
} Fixed_Heat_Rej;

/*
struct DATA
{
  real **prim_nbr_data;
  real **aux_nbr_data;
};*/

typedef struct heat_transfer_table
{
  int np;
  int na;
  real Tprim, Taux;
  real prim_flow_rate[MAX_TABLE_ROW];
  real aux_flow_rate[MAX_TABLE_COL];
  real heat_rej_rate[MAX_TABLE_ROW][MAX_TABLE_COL];
  cxboolean changed;/*this is true every time the table is set*/
} HTable;

typedef struct NTU_table
{
  int np;
  int na;
  real prim_flow_rate[MAX_TABLE_ROW];
  real aux_flow_rate[MAX_TABLE_COL];
  real NTU[MAX_TABLE_ROW][MAX_TABLE_COL];
  real poly_coefftt[6];
  real exp_decay3[MAX_TABLE_COL][3];
  real exp_decay5[MAX_TABLE_COL][5];
  char method[50];/*interpolation/extrapolation method*/
} NTUTable;

struct DUAL_CELL
{
  int ON;
  cxboolean multipass;
  char name[50];
  int prim_id;    /*primary fluid thread id*/
  int aux_id;           /*auxiliary fluid thread id*/
  BSP_Tree *prim_rt;  /*root pointer of primary fluid zone BSP*/
  BSP_Tree *aux_rt; /*root pointer of auxiliary fluid zone BSP*/

  int *prim_nbr;  /*auxiliary cell nbrs for primary fluid cells*/
  int *aux_nbr;   /*primary cell nbrs for auxiliary fluid cells*/

#if RP_NODE
  array_data_exchanger_t *prim_exch;
  array_data_exchanger_t *aux_exch;
#endif

#if PARALLEL
  unsigned int *prim_nbr_node;  /*nbr's compute node id*/
  unsigned int *aux_nbr_node; /*nbr's compute node id*/
  Node_Type node_type;
#endif
  real prim_min_max[ND_ND][2];  /*bounding box for primary fluid zone*/
  real aux_min_max[ND_ND][2];   /*bounding box for auxiliary fluid zone*/
  real prim_frontal_area;
  real aux_frontal_area;
  real prim_totvol;
  real aux_totvol;
  real total_pass_volume;
  real prim_q_gain;      /*total heat gained by primary fluid cells summed over all comp nodes*/
  real aux_q_rej;        /*total heat rejected by auxiliary fluid cells summed over all comp nodes*/
  real UA_scaled;        /* = Sum [(UA_scaled)cell * (Volume)cell]*/
  Fixed_Heat_Rej fhr;    /*user specified fixed heat rejection*/
  Flow_Type flow_type;
#if 0
  struct DATA data;      /*data for heat transfer calculations*/
#endif
  HTable *ht_table;
  NTUTable *ntu_table;
  struct DUAL_CELL *next;
};

struct MULTIPASS_DUAL_CELL
{
  int ON;
  char name[50];
  int npass;
  int outlet_inlet[MAX_PASSES - 1][2]; /*outlet inlet pair for coupling,total pair = npass-1*/
  /*real *T_profile_x[MAX_PASSES-1];
    real *T_profile_y[MAX_PASSES-1];
  #if RP_3D
    real *T_profile_z[MAX_PASSES-1];
  #endif
    real *T_profile_t[MAX_PASSES-1];*/
  struct DUAL_CELL *dc_list[MAX_PASSES];
  coupling temperature_coupling;
  struct MULTIPASS_DUAL_CELL *next;
};
#endif/*_DUAL_CELL_H*/
