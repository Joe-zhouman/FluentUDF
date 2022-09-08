/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _MAPPED_CHT_H
#define _MAPPED_CHT_H
#include "bsp.h"

typedef enum COUPLING_TYPE
{
  CT_NONE = -1,
  T_HTCNWT,
  T_Q,
  T_HTC,
  CT_IMPLICIT
} coupling_type;

enum
{
  IT_NONE = -1,
  MI_FL_SOL,
  MI_FL_FL,
  MI_SOL_SOL,
  MI_MIXED
};

typedef struct CHT_INPUT_PROFILE
{
  int ndata;
  real *coord[3];
  real *data;
  BSP_Tree *root;
} cht_inp_prof;

typedef struct DATA_STATISTICS
{
  real total_time_sampled;
  real delta_time_sampled;
  char datasetname[MAX_NAME_LENGTH];
} data_stat;

typedef struct CHT_PAIR
{
  char name[MAX_NAME_LENGTH];
  Objp *fth, *sth;
  cht_inp_prof *prof[5];/* size should match with MAX_PROF*/
  coupling_type ct;
  int method;/*interpolation method*/
  real *qdotTarget, *qdotRadTarget;
  real tolerance;
  int mf;
  data_stat dtst;
  cxboolean timeAveraged_p;
  /*struct CHT_PAIR *next;*/
} cht_pair;

#define ROOT_CHT_PAIR Get_Root_Cht_Pair()
#define TOT_CHT_PAIRS Get_Cht_Pair_Count()
#define IMPLICIT_MAPPED_INTERFACE_P(t) (Get_Thread_Coupling_Type((t)) == CT_IMPLICIT)
#define EXPLICIT_AREA_BASED_MAPPED_INTERFACE_P(t) (NNULLP(Get_Thread_Cht_Pair((t))) ? EXPLICIT_AREA_BASED_P(Get_Thread_Cht_Pair((t))) : FALSE)
#define EXPLICIT_COUPLING_P(cp) ((cp)->ct != CT_IMPLICIT)
#define IMPLICIT_COUPLING_P(cp) ((cp)->ct == CT_IMPLICIT)
#define EXPLICIT_PROFILE_BASED_P(cp) (!IMPLICIT_COUPLING_P((cp)) && (cp)->method != 3)
#define EXPLICIT_AREA_BASED_P(cp) (!IMPLICIT_COUPLING_P((cp)) && (cp)->method == 3)
#define AREA_BASED_COUPLING_P(cp) (IMPLICIT_COUPLING_P(cp) || EXPLICIT_AREA_BASED_P(cp))
#define F_JNT_T(f,t) F_STORAGE_R(f,t,SV_JNT_T)
#define loop_chtp(p,i)for((i)=0,(p)= ROOT_CHT_PAIR; (i) < TOT_CHT_PAIRS; ++(p),++(i))
#define CHT_PAIR_EMPTY_P (Get_Cht_Pair_Count() == 0)
#define F_Ci(f,t,n) (F_STORAGE_R_N3V(f,t,SV_TOT_HEATFLUX_COEFFS)[n])
#define F_Cir(f,t,n) (F_STORAGE_R_N3V(f,t,SV_RADFLUX_COEFFS)[n])
#define MULTIPLE_MAPPED_CHT_PAIR_P(chtp) (o_length((chtp)->fth) > 1 || o_length((chtp)->sth) > 1)

FLUENT_EXPORT cht_pair *Set_Cht_Pair(const char *, Objp *, Objp *, coupling_type, int, cxboolean);
FLUENT_EXPORT void Couple_Cht_Pairs(Domain *);
FLUENT_EXPORT int Delete_Cht_Pairs(void);
FLUENT_EXPORT int Delete_Cht_Pair(const char *);
FLUENT_EXPORT coupling_type Get_Thread_Coupling_Type(Thread *t);
FLUENT_EXPORT cht_pair *Get_Thread_Cht_Pair(Thread *t);
FLUENT_EXPORT int Get_Thread_Cht_Side(Thread *);
FLUENT_EXPORT cht_pair *Get_Cht_Pair(const char *);
coupling_type Get_Cht_Pair_Coupling_Type(char *, int *);
void Set_Cht_Thermalbc(cht_pair *);
#if RP_3D
void Reset_Planar_Mapped_Interface_Thread(Thread *);
void Set_All_Planar_Mapped_Interface_Threads(Domain *);
#endif
FLUENT_EXPORT Objp *Get_Mapped_Interface_Thread_List(cht_pair *);
FLUENT_EXPORT Objp *Get_Cht_Threads_Needing_Connectivity(void);
FLUENT_EXPORT int Get_Cht_Pair_Count(void);
FLUENT_EXPORT cht_pair *Get_Root_Cht_Pair(void);
FLUENT_EXPORT cxboolean Need_Cht_Connectivity_P(void);
FLUENT_EXPORT cxboolean Cht_Pair_Need_Connectivity_P(cht_pair *);
FLUENT_EXPORT void Compute_Cht_Connectivity(Domain *);
FLUENT_EXPORT void Free_Cht_Connectivity(cxboolean);
FLUENT_EXPORT cxboolean Mapped_Face_Storage_Allocated_P(cht_pair *, cxboolean);
FLUENT_EXPORT void Free_Cht_Pairs(cxboolean);
FLUENT_EXPORT void Free_Cht_Pair(char *, cxboolean);
#if RP_NODE
FLUENT_EXPORT void PreExchange_Data_From_Child_To_Parent(Domain *, ...);
FLUENT_EXPORT void PostExchange_Data_From_Parent_To_Child(Domain *, ...);
#endif
FLUENT_EXPORT void Compute_Min_Max_Dist(Objp *, Objp *, real *, real *);
void Print_Mapped_Chtp_Temperature_Range(void);
void Print_Mapped_Chtp_Quality(void);
void Apply_Explicit_Profile_Coupling(real, cxboolean);
Thread *Check_Valid_Mapped_Interface_Thread(Thread *);
void Interface_Type(Objp *, Objp *, char *);
FLUENT_EXPORT void compute_total_mapped_area(Domain *, cxboolean, cxboolean);
FLUENT_EXPORT void Add_Solar_Load_Mapped_Interface(void);
FLUENT_EXPORT cxboolean Add_Solar_Mapped_Intf_Source(Thread *);
FLUENT_EXPORT int Get_Interface_Type(cht_pair *, char *);
FLUENT_EXPORT void Create_Profile(cht_inp_prof **, Objp *, char *, Svar);
FLUENT_EXPORT real Get_Closest_Profile_Value(real [], cht_inp_prof *);
FLUENT_EXPORT void Free_Profile(cht_inp_prof **);
cxboolean Time_Averaged_Mapped_Intf_P(cht_pair *);
void Update_Cht_Pairs_After_Data_Read(Domain *);
#if PARALLEL
void Clear_Mapped_Interface_Exterior_Cells(Domain *);
#endif
void Map_Face_Svar(Thread *from, Thread *to, Svar nv);
#endif/*_MAPPED_CHT_H*/
