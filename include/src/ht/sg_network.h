/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#if RP_NETWORK
#ifndef _FLUENT_SG_NETWORK_H
#define _FLUENT_SG_NETWORK_H

typedef struct network_neighbor_struct
{
  int nwindex; /* store network index of extenal neighbor */
  int id;   /* network_cell_id or face-thread-id */
  int f_index0; /* for amg colum index for neighbor*/
  Property enthalpy_coeff;
  Property mass_flow; /* Defined this way so that user can hook a udf if needed */
  real temperature; /* link temperature */
  int *node_f_index0;/* f_index0 values for nodes connected
       to the same thread */
} Network_nb;

typedef struct network_cell_struct
{
  int index;   /* cell index */
  int n_internal_nb;   /* internal neighboring cells */
  int n_face_nb;       /* real face neighbor */
  int n_external_nb;   /* external network neighbors*/
  int n_end_nb;
  Network_nb *internal_nb;  /* virtual cell neighbor */
  Network_nb *face_nb; /* real face neighbor */
  Network_nb *external_nb; /* external network neighbor */
  Network_nb *end_nb;
  Property enthalpy_source;/* enthalpy source defined as a property so that it
                              can  be specified through a udf or a
                              polynomial  */
  real temperature;
  real temperature_M1;
  real temperature_M2;
  real mass;
  Property capacitance;
} Network_cell;

enum
{
  node = -1,  /* Had to keep this in lower case to prevent conflict
       with cgns include file */
  INTNB = 0,
  EXTNB,
  FACENB,
  ENDNB
};

typedef struct network_struct
{
  int zid;
  int ncells;
  int type;
  int offset; /* for calculating network cell index in AMG solver */
  Network_cell *cell;
} Network;

typedef struct network_objp_struct   /* Structure for facilitating more                                         than one node to be connected to                                     a face zone */
{
  int n; /* Network id */
  int c; /* Cell id in Network n */
  int *index1;  /*Gives location of the  node for AMG matrix */
  int *index2;  /* Gives  location of the c0 of face for AMG matrix */
  struct network_objp_struct *next;
} Network_Objp;
#define MAX_END_NEIGHBOR 20

typedef struct network_link
{
  int n, c, nb;
} Network_Link;

typedef struct network_end
{
  int zid;
  real temperature;
  int n_nb;
  Network_Link link[MAX_END_NEIGHBOR];
} Network_End;

extern FLUENT_EXPORT Network *network;
extern FLUENT_EXPORT Network_End *nw_end;

#define NW_NULL -1


#define NW_ID(n)(network[n].zid)
#define NW_NELEMENTS(n)(network[n].ncells)
#define NW_OFFSET(n)(network[n].offset)
#if !UDF_COMPILER
#define NW_CELL(n)(network[n].cell)
#endif /* !UDF_COMPILER */
#define NWC_INDEX(n,c)(NW_CELL(n)[c].index)
#define NWC_N_INTNB(n,c)(NW_CELL(n)[c].n_internal_nb)
#define NWC_N_FACENB(n,c)(NW_CELL(n)[c].n_face_nb)
#define NWC_N_EXTNB(n,c)(NW_CELL(n)[c].n_external_nb)
#define NWC_N_ENDNB(n,c)(NW_CELL(n)[c].n_end_nb)
#define NWC_INTNB(n,c)(NW_CELL(n)[c].internal_nb)
#define NWC_FACENB(n,c)(NW_CELL(n)[c].face_nb)
#define NWC_EXTNB(n,c)(NW_CELL(n)[c].external_nb)
#define NWC_ENDNB(n,c)(NW_CELL(n)[c].end_nb)
#if !UDF_COMPILER
#define NWC_T(n,c)(NW_CELL(n)[c].temperature)
#endif /* !UDF_COMPILER */
#define NWC_T_M1(n,c)(NW_CELL(n)[c].temperature_M1)
#define NWC_T_M2(n,c)(NW_CELL(n)[c].temperature_M2)
#define NWC_H_SRC(n,c)(NW_CELL(n)[c].enthalpy_source)
#define NWC_MASS(n,c)(NW_CELL(n)[c].mass)
#define NWC_CAPACITANCE(n,c)(NW_CELL(n)[c].capacitance)
#define NWC_INTNB_MDOT(n,c,nb)(NWC_INTNB(n,c)[nb].mass_flow)
#define NWC_FACENB_MDOT(n,c,nb)(NWC_FACENB(n,c)[nb].mass_flow)
#define NWC_EXTNB_MDOT(n,c,nb)(NWC_EXTNB(n,c)[nb].mass_flow)
#define NWC_ENDNB_MDOT(n,c,nb)(NWC_ENDNB(n,c)[nb].mass_flow)
#define NWC_INTNB_H_COEFF(n,c,nb)(NWC_INTNB(n,c)[nb].enthalpy_coeff)
#define NWC_FACENB_H_COEFF(n,c,nb)(NWC_FACENB(n,c)[nb].enthalpy_coeff)
#define NWC_EXTNB_H_COEFF(n,c,nb)(NWC_EXTNB(n,c)[nb].enthalpy_coeff)
#define NWC_ENDNB_H_COEFF(n,c,nb)(NWC_ENDNB(n,c)[nb].enthalpy_coeff)
#define NWC_INTNB_ID(n,c,nb)(NWC_INTNB(n,c)[nb].id)
#define NWC_FACENB_ID(n,c,nb)(NWC_FACENB(n,c)[nb].id)
#define NWC_EXTNB_ID(n,c,nb)(NWC_EXTNB(n,c)[nb].id)
#define NWC_ENDNB_ID(n,c,nb)(NWC_ENDNB(n,c)[nb].id)
#define NWC_INTNB_F0(n,c,nb)(NWC_INTNB(n,c)[nb].f_index0)
#define NWC_FACENB_F0(n,c,nb)(NWC_FACENB(n,c)[nb].f_index0)
#define NWC_FACENB_NODE_F0(n,c,nb,i)(NWC_FACENB(n,c)[nb].node_f_index0[i])
#define NWC_EXTNB_F0(n,c,nb)(NWC_EXTNB(n,c)[nb].f_index0)
#define NWC_INTNB_T(n,c,nb)(NWC_INTNB(n,c)[nb].temperature)
#define NWC_FACENB_T(n,c,nb)(NWC_FACENB(n,c)[nb].temperature)
#define NWC_EXTNB_T(n,c,nb)(NWC_EXTNB(n,c)[nb].temperature)
#define NWC_ENDNB_T(n,c,nb)(NWC_ENDNB(n,c)[nb].temperature)
#define NWC_EXTNB_NWID(n,c,nb)(NWC_EXTNB(n,c)[nb].nwindex)

#define NWE_ID(e)(nw_end[e].zid)
#if !UDF_COMPILER
#define NWE_T(e)(nw_end[e].temperature)
#endif
#define NWE_N_NB(e)(nw_end[e].n_nb)
#define NWE_NWID(e,l)(nw_end[e].link[l].n)
#define NWE_CID(e,l)(nw_end[e].link[l].c)
#define NWE_NBID(e,l)(nw_end[e].link[l].nb)

FLUENT_EXPORT int Num_Network(void);
FLUENT_EXPORT int Which_Network(int);
FLUENT_EXPORT void Free_Network_Arrays(Domain *);
FLUENT_EXPORT void Check_Network(Domain *);
FLUENT_EXPORT void Init_Network_Temperature(real );
FLUENT_EXPORT void Read_Network_Section(Domain *, FILE *, int );
FLUENT_EXPORT void Read_Network_Data(Domain *, FILE *, cxboolean, cxboolean);
FLUENT_EXPORT int Write_Network_Section(Domain *, FILE *, cxboolean);
FLUENT_EXPORT void Write_Network_Data(Domain *, FILE *, cxboolean);
FLUENT_EXPORT void Read_Network_Vars(Domain *, Pointer);
FLUENT_EXPORT int Write_Network_Vars_Port(Domain *, Pointer);
FLUENT_EXPORT int Write_Network_Vars(Domain *, FILE *);
FLUENT_EXPORT void Set_Network_End_T(Domain *);
FLUENT_EXPORT void Set_Network_Link_T(Domain *);
FLUENT_EXPORT void Set_Network_Massflow_Facezone_T(Domain *domain);
FLUENT_EXPORT void Update_Network_Old_Temperature(void);
FLUENT_EXPORT Pointer Get_Network_Var(int, int, int, const char var[]);
FLUENT_EXPORT Pointer Get_Network_Nb(int, int);
FLUENT_EXPORT void Set_Network_Var(int, int, int, Pointer);
FLUENT_EXPORT void Network_Temperature(int zone, int id);
FLUENT_EXPORT void Write_Network_History(void);
FLUENT_EXPORT Thread *Lookup_Face_Neighbor(Domain *, int);
FLUENT_EXPORT real Network_Enthalpysrc(int, int );
FLUENT_EXPORT real Network_Capacitance( int, int, real );
FLUENT_EXPORT real Network_Thermalcoeff(int, int, int, int );
FLUENT_EXPORT real Network_Capacitance_Integral(int, int, real,
                                                real );
FLUENT_EXPORT real NetworkNb_Massflow(int, int, int, int );
FLUENT_EXPORT void Check_Network_Massflow_Balance(Domain *);
FLUENT_EXPORT extern cxboolean network_disco;
FLUENT_EXPORT extern cxboolean network_uds;

#if PARALLEL /* hdfio */
FLUENT_EXPORT int Write_HDF_Network_Section(Domain *, char *);
FLUENT_EXPORT int Read_HDF_Network_Section(Domain *, char *);
FLUENT_EXPORT int Write_HDF_Network_Data(Domain *, char *);
FLUENT_EXPORT int Read_HDF_Network_Data(Domain *, char *);
#endif

#if MPI_IO
FLUENT_EXPORT void Write_MPI_Network_Data(Domain *domain, int fhandle);
FLUENT_EXPORT void Read_MPI_Network_Data(Domain *domain, int fhandle, int *headerbuf,
                                         cxboolean double_data);
#endif

#endif /*_FLUENT_SG_NETWORK */
#if RP_NODE
FLUENT_EXPORT void Encapsulate_Network_Boundary(Domain *domain);
FLUENT_EXPORT void Create_Network_Exterior_Cells(Domain *domain);
FLUENT_EXPORT void Set_Network_Ext_Cell_Status(Domain *domain);
FLUENT_EXPORT void Compute_Network_Linearized_Coefficients(Domain *domain);
FLUENT_EXPORT void Fill_Exterior_Network_Nbr_Cell_Linearized_Coeffs(Domain *domain);
#endif
FLUENT_EXPORT void Clear_Network_Exterior_Cells(Domain *domain);
#endif /*RP_NETWORK*/
