/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_PROFILE_H
#define _FLUENT_PROFILE_H

#include "dll.h"
#include "fluent_sc.h"

/* max length of profile name */
#define PROFILE_NAME_LENGTH 100
#define MAX_PROFILE_PARAMETERS 100
#define MAX_PROFILE_SPATIAL_FIELDS 100
#define MAX_PROFILE_NAME_ID_PAIRS 1024
#define MAX_PROFILE_REF_FRAMES 100
/* Profile Boundary Conditions */

struct thread_profile_struct
{
#if FIXED_PROFILE_NAME_LENGTH
  char profile_name[PROFILE_NAME_LENGTH]; /* name of profile */
  char field_name[PROFILE_NAME_LENGTH]; /* name of data section */
#else
  char *profile_name;
  char *field_name;
#endif

  Svar direct_copy_nvp1; /* the intial value is zero corresponding to SV_NULL = -1 */

  cxboolean profilep;   /* profile in use? */
  int position;     /* profile number. 0 = SV_PROFILE_0, etc. */
  Svar nv;
  real constant;    /* constant value */
  int timestamp;
  /* for equation sources or fixed value profiles this boolean
     indicates whether the variable has a source or fixed value specified */
  cxboolean active;
};
typedef struct thread_profile_struct Profile;

#define IS_PROFILE(prof)((prof).profilep)
#define IS_DIRECT_COPY_SV_NNULL(prof) (!(((prof).direct_copy_nvp1 - 1) == SV_NULL))
#define F_PROFILE_DIRECT_COPY(f,t,prof) (F_STORAGE_R(f,t,((prof).direct_copy_nvp1 -(1))))
#define MDA_OR_SC(t,prof) (IS_DIRECT_COPY_SV_NNULL(prof) || THERMALLY_SYSTEM_COUPLED_WALL_P(t,prof))
#define F_MDA_OR_SC(f,t,prof) (IS_DIRECT_COPY_SV_NNULL(prof) ? F_PROFILE_DIRECT_COPY(f,t,prof) : F_SC_THERM_DATA(f,t,prof))
#if 0
#define F_VAR(f,t,prof) (IS_DIRECT_COPY_SV_NNULL(prof) ? F_PROFILE_DIRECT_COPY(f,t,prof) : \
                          ((THERMALLY_SYSTEM_COUPLED_WALL_P(t,prof)) ? F_SC_THERM_DATA(f,t,prof) : \
                            (IS_PROFILE(prof) ? F_PROFILE(f,t,(prof).position) : \
                              (prof).constant)))
/* the definition above is similar to the another active defintion shown below */
#endif
#define F_VAR(f,t,prof) (MDA_OR_SC(t,prof) ? F_MDA_OR_SC(f,t,prof) : \
                          ((IS_PROFILE(prof) ? ((prof).position >= 0 ? F_PROFILE(f,t,(prof).position) : (prof).constant) : (prof).constant)))

/* Profile Definition */

typedef enum
{
  PROFILE_NONE          = -1,   /*Not specified yet. For internal use only*/
  PROFILE_POINT         = 0,    /* unstructured point data, 0th order */
  PROFILE_LINE          = 1,    /* line data, 0th order interpolation */
  PROFILE_MESH          = 2,    /* mesh data, 0th order interpolation */
  PROFILE_RADIAL        = 3,    /* radial line, 1st order interpolation */
  PROFILE_AXIAL         = 4,    /* axial line, 1st order interpolation */
  PROFILE_TRANSIENT     = 5     /* for transient data */
} Profile_Type;
typedef struct profile_ref_frame_struct
{
  char Ref_Name[1024];
  int id;
  char Option[1024];
  char Frame_Type[1024];
  real Origin_Point[ND_ND];
  real Axis_3_Point[ND_ND];
  real Plane_13_Point[ND_ND];
  char Ref_Coord_Frame[1024];
} Profile_Ref_Frame_Struct;
typedef struct profile_name_id_pair_struct
{
  char name[PROFILE_NAME_LENGTH];
  int id;
} Profile_Name_Id_Pair;
typedef struct profile_parameter_struct
{
  char name[PROFILE_NAME_LENGTH];
  double value;
} Profile_Parameter;
typedef struct profile_face_node_struct
{
  cxindex nnodes;
  cxindex *node_ids;
} Profile_Facet;
typedef struct input_profile_struct
{
  char name[PROFILE_NAME_LENGTH];
  char ref_name[PROFILE_NAME_LENGTH];
  Profile_Type type;
  cxboolean periodic; /*true for periodic transient profile */
  int ndata;   /* number of data points in each field */
  int nbin;    /* number of bins for sorting radial/axial profiles */
  struct { int m, n; } mesh;
  int nparameters;
  struct profile_parameter_struct parameter[MAX_PROFILE_PARAMETERS];
  int nspatialfields;
  char *spatialfields[MAX_PROFILE_SPATIAL_FIELDS];
  cxindex nprofile_faces;
  struct profile_face_node_struct *profile_faces;
  struct profile_field_struct *field;
  struct input_profile_struct *next;
  int interp_method;
} Input_Profile;

typedef struct profile_field_struct
{
  char name[PROFILE_NAME_LENGTH];
  real *data;
  struct profile_field_struct *next;
  int timestamp;
} Profile_Field;

/* User defined scalar boundary condition types. */
enum
{
  UDS_BC_FLUX    = 0,
  UDS_BC_VALUE   = 1,
  UDS_BC_COUPLED = 2
};

extern FLUENT_EXPORT cxboolean profile_needs_update;

FLUENT_EXPORT Svar Get_Profile_Svar(Thread *thread, const char *profile, const char *field);
FLUENT_EXPORT void Reset_Thread_Profile_Name(void *owner, Profile *prof,
                                             cxboolean reset_profile_name,
                                             cxboolean reset_field_name);
FLUENT_EXPORT void Set_Thread_Profile_Name(void *owner, Profile *prof,
                                           const char *prof_name,
                                           const char *field_name);
FLUENT_EXPORT void Set_Thread_Profile_Direct_Copy_Svar(void *owner, Profile *prof, Svar nv);
FLUENT_EXPORT void Reset_Thread_Profile_Direct_Copy_Svar(void *owner, Profile *prof);
FLUENT_EXPORT cxboolean Any_Thread_Has_Profile_P(Domain *);
FLUENT_EXPORT cxboolean Set_Profile_Update_Interval(Domain *);
FLUENT_EXPORT cxboolean Is_Udf_Profile(Profile *var);
FLUENT_EXPORT cxboolean Is_Define_Profile_Source(Profile *var);
FLUENT_EXPORT Input_Profile *Profile_List(void);
FLUENT_EXPORT Input_Profile *Pick_Input_Profile(const char *);
FLUENT_EXPORT void Delete_All_Profiles(void);
FLUENT_EXPORT void Delete_Profile(Input_Profile *);
#if !RP_NODE
FLUENT_EXPORT void Read_Profile_Section(Domain *, FILE *, int section);
FLUENT_EXPORT void Write_Profile_Section(Domain *, FILE *, cxboolean);
FLUENT_EXPORT void Write_CSV_Profile_Section(Domain *, FILE *, cxboolean);
FLUENT_EXPORT void Read_Transient_Tabular_Profile(Domain *, FILE *, int section);
FLUENT_EXPORT void Read_CSV_Profile(Domain *, FILE *);
#else
FLUENT_EXPORT void Read_Profile_Section(Domain *, int section);
FLUENT_EXPORT void Read_Transient_Tabular_Profile(Domain *, int section);
FLUENT_EXPORT void Read_CSV_Profile(Domain *);
#endif
FLUENT_EXPORT void Write_CSV_Harmonic(char *, char *, char *, Domain *, Thread *);
FLUENT_EXPORT void Get_Profile_Index(Input_Profile *p, real xtime, int *ix, real *ifact);
FLUENT_EXPORT void Set_Target_Profile_Reference_Frame_Id(int);
FLUENT_EXPORT int Get_Target_Profile_Reference_Frame_Id();
FLUENT_EXPORT void Set_Profile_Reference_Frames(char *, int, char *, char *, real [3], real [3], real [3], char * );
FLUENT_EXPORT void ReSet_Profile_Reference_Frames();
#if RP_HOST
void Write_Profile_Ref_Frame_Header_Definitions(FILE *);
#endif
#if RP_NODE
FLUENT_EXPORT void Sync_Profile_List(void);
#endif

#if RP_3D
FLUENT_EXPORT void Oriented_Profile(Domain *, Pointer args);
FLUENT_EXPORT void Create_Oriented_Profile(Domain *, Pointer args);
FLUENT_EXPORT void Replicate_Profile(Domain *, Pointer args);
#endif
FLUENT_EXPORT Pointer Display_Profile_Points(Domain *, Pointer p);
FLUENT_EXPORT Pointer Display_Interpolated_Data(Thread *, const char *, const char *, const char *);
FLUENT_EXPORT void Update_Dynamic_Profiles(Domain *);
FLUENT_EXPORT void Register_Profile(Thread *profile_thread, Profile *var);
FLUENT_EXPORT cxboolean Is_Registered_Profile(Profile *var);
FLUENT_EXPORT void Interpolate_Profile_Var(Thread *, Profile *);
FLUENT_EXPORT void Interpolate_Profile_Var_On_Nodes(double *node_var, Thread *, Profile *);
#if RP_3D && !RP_HOST
FLUENT_EXPORT void Update_Bins_and_Interpolate_Profile(Thread *, Profile *);
#endif
FLUENT_EXPORT real Get_Transient_Interpolated_Profile_Var(Profile *, Thread *thread, real flow_time);
FLUENT_EXPORT real Get_Time_Interpolated_Input_Profile_Value(const char *profile_name,
                                                             const char *field_name,
                                                             real flow_time);
FLUENT_EXPORT Profile_Field *Lookup_Profile_Field(const Input_Profile *, const char *);
FLUENT_EXPORT Profile_Field *Lookup_Transient_Profile_Time_Field(Input_Profile *profile);
FLUENT_EXPORT void Create_Mixing_Plane_Profile(Domain *, Pointer args);
FLUENT_EXPORT void Update_Mixing_Plane_Profiles(Domain *domain);

FLUENT_EXPORT void Update_Mixing_Plane_Profile(Thread *, Thread *, const char *);

FLUENT_EXPORT void Reset_Profile_Time_Stamps (Domain *d);
FLUENT_EXPORT void Update_Field_Time_Stamps(Input_Profile *);
FLUENT_EXPORT cxboolean Mixing_Planes_Out_Of_Tol(Domain *domain, int *ids, int *types, int len);
FLUENT_EXPORT real Get_Massflux(face_t f, Thread *t);
FLUENT_EXPORT void Display_Profiles_On_Thread(Domain *d, Thread *t);

extern FLUENT_EXPORT Input_Profile *profile_list;
FLUENT_EXPORT struct BSP_Tree *Build_Profile_Bsp_Tree(int, real [], real [], real []);
FLUENT_EXPORT void Set_Profile_Items(real *, real *, real *);
FLUENT_EXPORT int BSP_Profile_Items_In_Sphere(struct BSP_Tree *, real [], real, int (*)(int, real [], real), int *, int **, int *);
FLUENT_EXPORT int BSP_Profile_Closest_Item(struct BSP_Tree *, real [], real (*)(int, real []));

FLUENT_EXPORT Profile_Field *alloc_profile_field(Input_Profile *profile);
FLUENT_EXPORT Input_Profile *alloc_profile(void);
FLUENT_EXPORT real TotalTemperature(cell_t c, Thread *t, real dx[]);
FLUENT_EXPORT real TotalPressure(cell_t c, Thread *t, real dx[]);
FLUENT_EXPORT int CSV_Create_Polygon_Zone(Input_Profile *);
FLUENT_EXPORT void Contour_Profile_Field(Input_Profile *, const char *);
FLUENT_EXPORT void Fill_Profile_Ndata_Points(Input_Profile *, double **, int *);
#if RP_NODE
FLUENT_EXPORT void Compute_Min_Max_Profile_Fields(register Input_Profile *, const char *, real *, real *);
#endif
#endif /* _FLUENT_PROFILE_H */
