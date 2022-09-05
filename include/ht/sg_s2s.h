/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/*....................................................*/
/*.........Atul Kumar Verma : Sept 2000 ..............*/
/*....................................................*/

#ifndef _FLUENT_SG_S2S_H
#define _FLUENT_SG_S2S_H

#include "dll.h"
#include "sg_s2s_data.h"
#if RP_S2S

#  define F_NP_P(f,t) F_STORAGE_I(f, t, SV_FI_TMP_0)
/* Define constants, macros and prototypes for s2s radiation */

#define S_GLOB_J(i) s2s_glob[i].radiosity
#define S_GLOB_T(i) s2s_glob[i].temperature
#define S_GLOB_E(i) s2s_glob[i].emissivity
#define S_GLOB_ID(i) s2s_glob[i].sglob_ids
#define S_GLOB_GID(i) s2s_glob[i].gid
#define S_GLOB_VF(i,j) s2s_glob[i].viewfactors[j]
#define S_GLOB_QRAD(i) s2s_glob[i].qrad
#define S_GLOB_RADSUM(i) s2s_glob[i].radsum
#define S_GLOB_RADFLAG(i) s2s_glob[i].radflag
#define S_GLOB_THREAD O_F_THREAD
#define F_S2S_RADSUM(f,t) F_STORAGE_R(f,t,SV_S2S_RADSUM)

#define SKIP_S2S_BOUNDARY_FACES(f,t) (SV_ALLOCATED_P(t, SV_FI_TMP_0) && F_NP_P(f, t))
#define GET_SB_FPSC(t, sb_fpsc)\
    { int i_;\
      sb_fpsc = 1;\
      for(i_=0; i_ < THREAD_SI_NCHILDS(t); i_++)\
        sb_fpsc = MAX(THREAD_VAR(THREAD_SI_CHILD_THREAD_P(t, i_)[0]).wall.fpsc, sb_fpsc);\
    }

#define NCI_CHILD_PARTICIPATING_P(t) \
  (THREAD_TYPE(t) == THREAD_F_WALL && THREAD_VAR(t).wall.radiating_s2s_surface)
#define S2S_BOUNDARY_THREAD_P(t) (Is_Bndry_Thread(t)) /* && !SLIDING_INTERFACE_THREAD_P(t))*/
#define SET_SB_RAD_S2S_SURF(t, radiating_s2s_thread)\
    { int i_;\
      radiating_s2s_thread = FALSE;\
      for(i_=0; i_ < THREAD_SI_NCHILDS(t); i_++)\
      if(THREAD_VAR(THREAD_SI_CHILD_THREAD_P(t, i_)[0]).wall.radiating_s2s_surface) { radiating_s2s_thread = TRUE; break;} \
    }

#define DEBUG_S2S 0
#define PRINT_S2S_INFO 0

typedef struct surface_s2s_glob_struct
{
  real radiosity;            /* radiosity */
  real temperature;          /* surface glob temperature */
  real emissivity;           /* surface glob emissivity */
  real qrad;                 /* Net radiation from the surface */
  real radsum;               /* SUM (F(i,j) * J(j)) */
  cxboolean radflag;           /* used in sg_temp.c */
  real area;                 /* surface glob area */
  int  sglob_ids;            /*  glob ids    */
  Thread *thread;            /* thread to which the faces belong */
  Objp  *f_list;             /* link list of faces in the glob */
  real *viewfactors;         /* view factors for the glob */
  int gid;
} Surface_S2s_Glob;

typedef struct cluster_struct
{
  int nnodes;
  int *nodeids;
} Cluster;

typedef struct S2s_Grp
{
  int nFaces;
  int id;
  struct S2s_Grp *next;
  real plane[3];
}
S2s_Grp;

typedef struct S2s_str
{
  int n_sglobs;
  cxboolean converged;
  FILE *fp;
  cxboolean binary; /* binary file */
  cxboolean double_data;  /* double precision reals in file */
  real residual;
  int viewfactors_read;
  int viewfactors_done;
  int globs_s2s_done;
}
S2s;

typedef struct S2s_Face
{
  face_t f;
  Thread *tface;
  struct S2s_Face *next;
}
S2s_Face;

extern FLUENT_EXPORT Surface_S2s_Glob *s2s_glob;

#if RP_NODE
void Set_F_S_Glob_Id_Offset(int);
int Get_F_S_Glob_Id_Offset(void);
void Set_Global_F_S_Glob_Id(Domain *, cxboolean);
void Reset_Global_F_S_Glob_Id(Domain *, cxboolean);
#endif


FLUENT_EXPORT void Set_View_Factors_Read(cxboolean status);
FLUENT_EXPORT void Set_View_Factors_Done(cxboolean status);
FLUENT_EXPORT cxboolean Get_View_Factors_Read(void);
FLUENT_EXPORT cxboolean Get_View_Factors_Done(void);
FLUENT_EXPORT int Get_Total_S2s_Globs(Domain *);
FLUENT_EXPORT void Set_S2s_Globs_Done(cxboolean status);
FLUENT_EXPORT cxboolean Get_S2s_Globs_Done(void);
FLUENT_EXPORT void Get_S2s_Globs_Info(int *n_sglobs);
FLUENT_EXPORT void Check_FPSC_Val(Domain *domain);
FLUENT_EXPORT void Clear_Cluster_Threads_Tag(Domain *domain);
FLUENT_EXPORT void Group_S2s_Globs(Domain *domain);
FLUENT_EXPORT void Tag_Cluster_Threads(Domain *domain);
FLUENT_EXPORT void Alloc_Mark_And_Label_SB_Threads(Domain *domain);
FLUENT_EXPORT void Free_NP_Face_SB(Domain *domain);
FLUENT_EXPORT void Read_S2s_Clusters(Domain *domain, FILE *fd);
FLUENT_EXPORT void Read_S2s_Clusters_and_Viewfac(Domain *domain, FILE *fd);
FLUENT_EXPORT void Update_S2s_Memory(void);
FLUENT_EXPORT void Solve_S2s_For_Nita(Domain *domain);
FLUENT_EXPORT void Get_Glob_S2s_Info(int *n_s_globs);
FLUENT_EXPORT void Get_S2s_Glob( int glob_id, Objp **face_list);
FLUENT_EXPORT void Display_S2s_Globs(int typeGlob);
FLUENT_EXPORT int Read_Clusters_From_File(Domain *domain, FILE *fd);
FLUENT_EXPORT int Read_Clusters_Vf_From_File(Domain *domain, FILE *fd);
FLUENT_EXPORT void Delete_All_S2S_Groups(void);
FLUENT_EXPORT Pointer Print_Thread_Clusters(Domain *domain);
FLUENT_EXPORT void Print_Zonewise_Radiation(Domain *domain);
FLUENT_EXPORT void Print_Zonewise_Radiation_Gui(Domain *domain, int *id_list1, int *id_list2, int len1, int len2, int btstate, char **t_from, char **t_to, const char *filename, const char *mode);
FLUENT_EXPORT void Glob_Elements(void);
FLUENT_EXPORT int Write_S2S_Periodic_Face_Section(Domain *domain, FILE *fd);
FLUENT_EXPORT int  Write_S2S_Face_Section_Thread(Domain *domain, Thread *thread,
                                                 FILE *fd, cxboolean binary, cxboolean);
FLUENT_EXPORT int  Write_S2S_Face_Section(Domain *domain,
                                          FILE *fd, cxboolean binary, cxboolean);
FLUENT_EXPORT int  Write_S2S_Node_Section(Domain *domain,
                                          FILE *fd, cxboolean binary, cxboolean);
FLUENT_EXPORT int  Write_S2S_Cluster_Section(Domain *domain,
                                             FILE *fd, cxboolean binary, cxboolean);
FLUENT_EXPORT int  Write_Glob_View_Factors(Domain *domain,
                                           FILE *fp, cxboolean binary);
FLUENT_EXPORT int Read_Glob_Rad_Flux_Data(Domain *domain, FILE *fp,
                                          cxboolean binary, cxboolean double_data, cxboolean readHDF, char *fn);
FLUENT_EXPORT int Write_Glob_Rad_Flux_Data(Domain *domain, FILE *fp,
                                           cxboolean binary, cxboolean writeHDF, char *fn);
FLUENT_EXPORT int HDF_Write_Glob_Rad_Flux(Domain *domain, char *fn);
FLUENT_EXPORT int HDF_Read_Glob_Rad_Flux(Domain *domain, char *fn);
FLUENT_EXPORT int CX_Num_S2s_Globs(void);
FLUENT_EXPORT int CX_Get_S2s_Glob(int glob_id, int *n_elements, int *type, CX_Face_Def **bndry);
FLUENT_EXPORT void CX_Delete_All_S2s_Globs(void);
FLUENT_EXPORT void CX_S2s_Glob_Elements(real split_angle, cxboolean bndry_only);
#if MPI_IO
FLUENT_EXPORT int Read_MPI_Glob_Rad_Flux_Data(Domain *domain, int fhandle,
                                              int *headerbuf, cxboolean double_data);
FLUENT_EXPORT int Write_MPI_Glob_Rad_Flux_Data(Domain *domain, int fhandle);
#endif
FLUENT_EXPORT void Compute_View_Factors(int isBinary, char *filename, cxboolean file_io, int *sub_comm, S2S_VF_Calc *vf_calc);
FLUENT_EXPORT void Compute_RT_VF_GPU(int isBinary, char *filename);
FLUENT_EXPORT void Compute_VF_VF_GPU(int isBinary, int cpucnt, int gpucnt, int gpucpurat, char *filename);
FLUENT_EXPORT int Get_Mixed_Mode(void);
FLUENT_EXPORT void Compute_Viewfac_Mixed_Mode(int *viewfacVars, char *path, int methodgpu);
FLUENT_EXPORT int  Read_Glob_View_Factors(Domain *domain, FILE *fp);
FLUENT_EXPORT int  Read_Glob_View_Factors_CRF(Domain *domain, FILE *fp);
FLUENT_EXPORT int  Read_View_Factors_HDF(Domain *domain);
FLUENT_EXPORT void Free_Glob_View_Factor_Arrays(void);
FLUENT_EXPORT void Free_Glob_Radsum(void);
FLUENT_EXPORT void Init_S2s_Radiosity(Domain *domain);
FLUENT_EXPORT int  Count_Boundary_Faces(Domain *domain);
FLUENT_EXPORT int  Count_Boundary_Faces_Poly(Domain *domain);
FLUENT_EXPORT int  Count_Boundary_Nodes(Domain *domain);
FLUENT_EXPORT Objp *insert_s2s(Objp *head_list, face_t f, Thread *t);
FLUENT_EXPORT cxboolean Check_Glob_Id_Bound(Domain *domain, cxboolean all);
FLUENT_EXPORT void S2s_Calc_Fpsc(Domain *domain);
FLUENT_EXPORT real *Dist_Calc(Domain *domain);
FLUENT_EXPORT void Cluster_To_Cluster(Domain *domain);
FLUENT_EXPORT void Model_Initialize_s2s(void);
FLUENT_EXPORT int Write_S2S_Face_Section_Cluster(Domain *domain, FILE *fd, cxboolean binary, cxboolean all);
#if !PARALLEL
FLUENT_EXPORT int Label_S2S_Nodes(Domain *domain);
FLUENT_EXPORT int Label_S2S_Nodes_Clust(Domain *domain);
#endif
# if RP_NODE
FLUENT_EXPORT int Map_Boundary_Nodes(Domain *domain);
FLUENT_EXPORT int Map_Boundary_Nodes_Clust(Domain *domain);
FLUENT_EXPORT int Map_Boundary_Nodes_Clust_IPC(Domain *domain);
FLUENT_EXPORT void Count_Rad_Faces_Clusters_Par(Thread *thread, int *rad_clusters, int *rad_faces);
int local_boundary_vertices(Domain *domain);
int local_boundary_vertices_rt(Domain *domain);
# endif
FLUENT_EXPORT void Init_Radsum(Domain *domain);

#if RP_SHELL && RP_3D
FLUENT_EXPORT void Remove_Shell_Threads (Domain *domain);
FLUENT_EXPORT void Restore_Shell_Threads (Domain *domain);
#endif /* RP_SHELL && RP_3D */

#if PARALLEL
FLUENT_EXPORT cxboolean Coupled_SI_Exists_P(Domain *);
FLUENT_EXPORT cxboolean is_s2s_interface_clean(Domain *);
FLUENT_EXPORT int  fill_s2s_data(Domain *domain, cxboolean, cxboolean binary);
int fill_s2s_vars(Domain *domain, int s2s_global_master, FILE *fd, cxboolean binary, int vf_method, cxboolean ipcm);
int fill_s2s_face_section_parallel(Domain *domain, cxboolean all, int s2s_global_master, int s2s_global_master_rank);
int *get_global_master_rank_s2s(int *s2s_global_master, int *s2s_global_master_rank, int *s2s_comm_handle);
int fill_s2s_node_section(Domain *domain, cxboolean all, int s2s_global_master, int s2s_global_master_rank, int lnverts, FILE *fd, cxboolean binary);
int fill_s2s_node_section_rt(Domain *domain, int lnverts, int s2s_sub_commh);
int fill_s2s_face_section_f2f(Domain *domain, cxboolean all, int s2s_global_master, int s2s_global_master_rank, FILE *fd, cxboolean binary);
int fill_s2s_face_section_rt(Domain *domain, int s2s_sub_commh);
int fill_s2s_face_section_cluster(Domain *domain, cxboolean all, int s2s_global_master, int s2s_global_master_rank, FILE *fd, cxboolean binary);
#endif
FLUENT_EXPORT void Recompute_ViewFactor(Domain *domain);
#endif /* RP_S2S */
#endif /* _FLUENT_SG_S2S_H */

