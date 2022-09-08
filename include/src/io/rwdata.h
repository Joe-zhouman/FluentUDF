/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_RWDATA_H
#define _FLUENT_RWDATA_H

#include "dll.h"

#if SEEM

#include "acoustics.h"  /* only for t_n_vars */

FLUENT_EXPORT cxboolean Read_Data_Section(Domain *d, FILE *, int section);
FLUENT_EXPORT cxboolean PRF_Read_Data_Buffer(Domain *d);
FLUENT_EXPORT void Write_Data_Section(Domain *, FILE *, cxboolean, Pointer, cxboolean);
FLUENT_EXPORT void Write_Cell_Fn_Data_Section(Domain *, FILE *, cxboolean, cxboolean);
FLUENT_EXPORT void Write_Residual_Sections(Domain *domain, FILE *, cxboolean binary, cxboolean only_active);
FLUENT_EXPORT void Update_Before_Data_Write(Domain *domain);
FLUENT_EXPORT void Write_Thread_Data_Section(Domain *, Thread *, Svar,
                                             FILE *, cxboolean);
FLUENT_EXPORT void Write_Thread_Svar(Domain *domain, Thread *t,
                                     int nv, int len, int num,
                                     FILE *fd, cxboolean binary, cxboolean seg_vector,
                                     cxindex first_id, cxindex last_id);
FLUENT_EXPORT void Write_Acoustic_Data (Domain *domain, FILE *, Pointer threads_n_vars);
FLUENT_EXPORT void Write_Acoustic_Data_CGNS (Domain *, const char *, Pointer);
FLUENT_EXPORT void Write_Acoustic_Data_Q_CGNS (Domain *, const char *, Pointer);
FLUENT_EXPORT void Write_Mesh_File_CGNS (Domain *, const char *, Pointer);
FLUENT_EXPORT void Write_Mesh_File_Q_CGNS(Domain *, const char *, Pointer);
FLUENT_EXPORT void Store_Element_Global_IDs(Domain *, cxboolean);
FLUENT_EXPORT void Initialize_Acoustic_File_For_Read (Domain *domain, Pointer threads, Pointer names);
FLUENT_EXPORT void Set_Acoustic_Threads_To_Read(Domain *, Pointer, Pointer, Pointer);
FLUENT_EXPORT void Set_Acoustic_Vars_To_Read(Domain *domain, Pointer filenames, Pointer threads);
FLUENT_EXPORT void Finish_Acoustic_File_For_Read(void);
FLUENT_EXPORT double Read_Next_Acoustic_Timestep (Domain *domain);
FLUENT_EXPORT void Set_Adjacent_Cell_Zone(Pointer threads, cxboolean on_the_fly);
FLUENT_EXPORT void Set_Acoustic_Machine_Config_Flag (void);
FLUENT_EXPORT void Update_Old_Time_Levels_DBNS_Expl(Domain *domain);
FLUENT_EXPORT void Inquire_Acoustic_Variables(Domain *domain, t_n_vars *t_n_v);
FLUENT_EXPORT void Fill_Previous_Acoustic_Svar (Domain *domain, Thread *t, Svar sv);
FLUENT_EXPORT void Generate_SV_List(Domain *, int **, int *);

#if PARALLEL /* hdfio */
FLUENT_EXPORT int Write_HDF_Special_Data_Sections(Domain *, const char *, const char *, int);
FLUENT_EXPORT int Read_HDF_Special_Data_Sections(Domain *, const char *, const char *);
#endif /* PARALLEL */

# if !RP_NODE
FLUENT_EXPORT char *Write_Grid_Size_Section(Domain *domain, FILE *, int section);
# endif

#if RP_3D
FLUENT_EXPORT void Write_Vortex_Method_Section(Domain *domain, FILE *fd);
FLUENT_EXPORT void Read_Vortex_Method_Section(Domain *domain, FILE *fd);
FLUENT_EXPORT void Store_Shell_Temperature_Dynamic_Mesh(Domain *domain);
#endif


FLUENT_EXPORT FILE *fopen_input_compressed(char *fn);
FLUENT_EXPORT void fclose_input_compressed (FILE *fp, char *fn);
FLUENT_EXPORT int find_file_that_exists (char *fn);
FLUENT_EXPORT void Ac_Write_Centroid_Info(FILE *fp, Domain *domain);
FLUENT_EXPORT void Set_Ac_Display_Flow_Time(cxboolean flag);
FLUENT_EXPORT void Set_Ac_Cylindrical_Export (cxboolean flag);

FLUENT_EXPORT void APECS_Grid_Connectivity (Domain *domain);
FLUENT_EXPORT void APECS_Surface_Grid_Connectivity(Domain *domain, int thread_id);

FLUENT_EXPORT Pointer free_dispensable_storage_vars(Pointer);

#endif /* SEEM */

#if PARALLEL


FLUENT_EXPORT real *PRF_Read_Real(FILE *fd, int nb, int len, cxboolean bin,
                                  int doub, int *nbr, char *f, int l);
FLUENT_EXPORT void PRF_Write_Real(FILE *fd, real *buffer, real *work, int nb, int len,
                                  cxboolean bin, int *nbw, char *f, int l);
# define PRF_READ_REAL(fd,nb,len,bin,doub,nbr) \
  PRF_Read_Real(fd,nb,len,bin,doub,nbr,__FILE__,__LINE__)
# define PRF_WRITE_REAL(fd,buf,work,nb,len,bin,nbw) \
  PRF_Write_Real(fd,buf,work,nb,len,bin,nbw,__FILE__,__LINE__)

FLUENT_EXPORT void Enable_Read_Write_In_Chunks(cxboolean val);
FLUENT_EXPORT cxboolean Read_Write_In_Chunks(int section);
FLUENT_EXPORT void Free_Data_IO_Chunk_Buffer(void);

FLUENT_EXPORT void pre_process_before_io(void);
FLUENT_EXPORT void clean_up_after_io(void);
#endif

FLUENT_EXPORT void Clear_Allocated_Equation_Counts(void);

#endif /* _FLUENT_RWDATA_H */
