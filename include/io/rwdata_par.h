/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_RWDATA_PAR_H
#define _FLUENT_RWDATA_PAR_H

#include "dll.h"

#if PARALLEL
/* These string should match scm side lib/rppario.scm strings
 * 68  Defined in xfile.[h,scm] as mpi data section
 * This may help later in reading pdat file with a serial program
 * Do not change total length of string section. Keep it same for
 * all such sections.
 */

#define MPI_STRING_SECTION "(68 \"####MPI-STRING-SECTION#####\""
#define MPI_DATA_SECTION   "(68 \"#####MPI-DATA-SECTION######\""
#define MPI_EOF_SECTION    "(68 \"#######MPI-FILE-EOF#######\")"
#define MPI_SECTION_END    "   \"##END-MPI-SECTION##########\")"

/* to be used for all MPI IO related debugging messages across all files */
#define DEBUG_MPI_IO 0

/* The DATA HEADER SIZE is kept a bit large to leave room for future
 * additions.  Other than the section ID (which is the first int in the
 * header), the contents of the section headers are specific to the different
 * sections.
 */
#define MPI_DATA_HEADER_SIZE 20
#define H_SECTION(buf)     (buf[0])

struct New_Pdat_Write_Settings_Type
{
  int min_buffer_size;
  int min_rebalance_bytes;
  int large_data_bytes;
  int contiguous_write_limit;
};

extern struct New_Pdat_Write_Settings_Type pdat_write_settings;

#if SEEM


FLUENT_EXPORT void Set_Panasas_file_layout_policy(const char *policy_str);
FLUENT_EXPORT void Set_panfs_optimum_file_layout(Domain *domain, const char *filename);
FLUENT_EXPORT void Set_MPI_IO_nonblocking_behaviour(int value);
FLUENT_EXPORT void Set_MPI_IO_chunk_size(int chunk_size);
FLUENT_EXPORT void Rwdatap_init(void);
FLUENT_EXPORT void Read_MPI_Data_Section(Domain *domain, int fhandle);
FLUENT_EXPORT void Fill_Tmp_Id_Array_On_Thread (Thread *);
FLUENT_EXPORT void Write_MPI_Data_Section(Domain *domain, int fhandle);
FLUENT_EXPORT void Write_MPI_Data_Section_New(Domain *domain, int fhandle);
FLUENT_EXPORT void Write_MPI_Residual_Sections(Domain *domain, int fhandle, int sec_id);
FLUENT_EXPORT void exchange_exterior_values_after_data_read(void);
#if RP_3D
FLUENT_EXPORT void Write_MPI_Vortex_Method_Section(Domain *domain, int fhandle);
#endif /* RP_3D */
/* this funciton is defined in lmain.c */
void read_mpi_ud_data_section(int fhandle, int *headerbuf);

#endif /* SEEM */
#endif /* PARALLEL */
#endif /* _FLUENT_RWDATA_PAR_H */

