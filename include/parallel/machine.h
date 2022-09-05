/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_MACHINE_H
#define _FLUENT_MACHINE_H

#include "dll.h"

typedef int (*reader_type)(void *, char *, int);

FLUENT_EXPORT void Init_File_Machine_Config(void);
FLUENT_EXPORT void Init_My_Machine_Config(void);
FLUENT_EXPORT int Machine_is_int64_index_required(void);

FLUENT_EXPORT char *Write_Machine_Config_Section(FILE *);
FLUENT_EXPORT int Read_Machine_Config_Section(FILE *, cxboolean);
FLUENT_EXPORT int Read_Machine_Config_Section_Port(Port *, cxboolean);
FLUENT_EXPORT int Require_Int64_Index(Domain *domain, cxindex maxid, cxboolean with_host);
FLUENT_EXPORT int Read_Bin_Ints(FILE *, int *result, int ndata);
FLUENT_EXPORT int Read_Bin_Longs(FILE *, long *result, int ndata);
FLUENT_EXPORT int Read_Bin_Indices(FILE *, cxindex *result, int ndata);
FLUENT_EXPORT int Read_Bin_Floats(FILE *, float *result, int ndata);
FLUENT_EXPORT int Read_Bin_Doubles(FILE *, double *result, int ndata);
FLUENT_EXPORT int Read_Bin_Reals(FILE *, real *result, int ndata, cxboolean double_data);
FLUENT_EXPORT int Sync_Env_Var(char *);
FLUENT_EXPORT int get_file_native_int(void);
FLUENT_EXPORT int get_file_native_float(void);
FLUENT_EXPORT int get_file_native_double(void);
FLUENT_EXPORT int get_file_native_real(void);
FLUENT_EXPORT int get_file_native_long(void);
FLUENT_EXPORT int get_file_native_index(void);
FLUENT_EXPORT int get_file_need_swap(void);
FLUENT_EXPORT int Convert_Bin_Ints(reader_type reader, void *reader_handle, int *result, int ndata);
FLUENT_EXPORT int Convert_Bin_Longs(reader_type reader, void *reader_handle, long *result, int ndata);
FLUENT_EXPORT int Convert_Bin_Indices(reader_type reader, void *reader_handle, cxindex *result, int ndata);
FLUENT_EXPORT int Convert_Bin_Floats(reader_type reader, void *reader_handle, float *result, int ndata) ;
FLUENT_EXPORT int Convert_Bin_Doubles(reader_type reader, void *reader_handle, double *result, int ndata);
FLUENT_EXPORT int Convert_Bin_Reals(reader_type reader, void *reader_handle, real *result, int ndata, cxboolean double_data);

#define Read_Bin_Int(fp,fptr)Read_Bin_Ints(fp,fptr,1)
#define Read_Bin_Long(fp,fptr)Read_Bin_Longs(fp,fptr,1)
#define Read_Bin_Float(fp,fptr)Read_Bin_Floats(fp,fptr,1)
#define Read_Bin_Double(fp,fptr)Read_Bin_Doubles(fp,fptr,1)
#define Read_Bin_Real(fp,fptr,d)Read_Bin_Reals(fp,fptr,1,d)
/* to be implemented for long */

typedef struct
{
  int machine;
  int big_endian;
  int fp_format;
  int sizeof_char;
  int sizeof_short;
  int sizeof_int;
  int sizeof_long;
  int sizeof_float;
  int sizeof_double;
  int sizeof_real;
  int sizeof_pointer;
  int sizeof_index;

  int require_int64_index;
} Machine_Config;

extern Machine_Config my_machine_config;

#if USE_INT64
#define Read_Bin_Index(fp,fptr)  (Read_Bin_Indices(fp,fptr,1))
#if _NT
#define XF_Read_Dindex(fp,iptr)        (XF_Read_Dlonglong(fp,iptr)          )
#define XF_Read_Xindex(fp,iptr)        (XF_Read_Xlonglong(fp,iptr)          )
#define XF_Read_Bin_Indices(fp,fptr,n) (XF_Read_Bin_LongLongs(fp,fptr,n))
#define XF_Write_Bin_Index(fp,i)\
    if (my_machine_config.require_int64_index)\
    XF_Write_Bin_Long_Long(fp, i)\
    else\
    XF_Write_Bin_Int(fp, i)
#define XF_Write_Dindex(fp,i)    (XF_Write_Dlonglong(fp,i))
#define XF_Write_Xindex(fp,i)    (XF_Write_Xlonglong(fp,i))
#else
#define XF_Read_Dindex(fp,iptr)        (XF_Read_Dlong(fp,iptr)      )
#define XF_Read_Xindex(fp,iptr)        (XF_Read_Xlong(fp,iptr)      )
#define XF_Read_Bin_Indices(fp,fptr,n) (XF_Read_Bin_Longs(fp,fptr,n))
#define XF_Write_Bin_Index(fp,i)\
    if (my_machine_config.require_int64_index)\
    XF_Write_Bin_Long(fp, i)\
    else\
    XF_Write_Bin_Int(fp, i)
#define XF_Write_Dindex(fp,i)    (XF_Write_Dlong(fp,i))
#define XF_Write_Xindex(fp,i)    (XF_Write_Xlong(fp,i))
#endif
#else /*USE_INT64*/
#define Read_Bin_Index(fp,fptr)  (Read_Bin_Int(fp,fptr))
#define XF_Read_Dindex(fp,iptr)        (XF_Read_Dint(fp,iptr)     )
#define XF_Read_Xindex(fp,iptr)        (XF_Read_Xint(fp,iptr)     )
#define XF_Read_Bin_Indices(fp,fptr,n) (XF_Read_Bin_Ints(fp,fptr,n) )
#define XF_Write_Bin_Index(fp,i) (XF_Write_Bin_Int(fp,i))
#define XF_Write_Dindex(fp,i)    (XF_Write_Dint(fp,i))
#define XF_Write_Xindex(fp,i)    (XF_Write_Xint(fp,i))
#endif

/* converting binary data to a specified format */
#if ! UDF_COMPILER
void Get_File_Machine_Config(Machine_Config *machine_config);
void Set_File_Machine_Config(Machine_Config *machine_config);
void Convert_Binary_Int_To_Machine(size_t ndata, int *int_data);
void Convert_Binary_Int64_To_Machine(size_t ndata, int64_t *int64_data);
void Convert_Binary_Float_To_Machine(size_t ndata, float *float_data);
void Convert_Binary_Double_To_Machine(size_t ndata, double *double_data);
#endif

#if _NT
FLUENT_EXPORT char *ConvertPathToUNC(char *, const char *, cxboolean);
void  FLUENT_EXPORT SetUNCPathAsCwd(void);
#endif

#if sys_ntx86 || sys_win64
FLUENT_EXPORT FILE *fluent_fopen(char *fname, char *mode);
FLUENT_EXPORT int fluent_fclose(FILE *fp);
FLUENT_EXPORT size_t fluent_fread(void *buffer, size_t size, size_t count, FILE *stream);
FLUENT_EXPORT size_t fluent_fwrite(const void *buffer, size_t size, size_t count, FILE *stream);
FLUENT_EXPORT int fluent_fprintf(FILE *fp, const char *format, ...);
FLUENT_EXPORT int fluent_fscanf(FILE *fp, const char *format, ...);
FLUENT_EXPORT void  fluent_clearerr(FILE *fp);
FLUENT_EXPORT int   fluent_feof    (FILE *fp);
FLUENT_EXPORT int   fluent_ferror  (FILE *fp);
FLUENT_EXPORT int   fluent_fflush  (FILE *fp);
FLUENT_EXPORT int   fluent_fgetc   (FILE *fp);
FLUENT_EXPORT int   fluent_fgetpos (FILE *fp, fpos_t *pos);
FLUENT_EXPORT char *fluent_fgets   (char *str, int n, FILE *fp);
FLUENT_EXPORT int   fluent_fputc   (int c, FILE *fp);
FLUENT_EXPORT int   fluent_fputs   (const char *str, FILE *fp);
FLUENT_EXPORT FILE *fluent_freopen (const char *path, const char *mode, FILE *fp);
FLUENT_EXPORT int   fluent_fseek   (FILE *fp, long offset, int origin);
FLUENT_EXPORT int   fluent_fsetpos (FILE *fp, const fpos_t *pos);
FLUENT_EXPORT long  fluent_ftell   (FILE *fp);
FLUENT_EXPORT void  fluent_rewind  (FILE *fp);
FLUENT_EXPORT void  fluent_setbuf  (FILE *fp, char *buf);
FLUENT_EXPORT FILE *fluent_tmpfile (void);
FLUENT_EXPORT int   fluent_ungetc  (int c, FILE *fp);
FLUENT_EXPORT int   fluent_vfprintf(FILE *fp, const char *format, va_list argptr);
FLUENT_EXPORT int   fluent_getc    (FILE *fp);
FLUENT_EXPORT int   fluent_putc    (int c, FILE *fp);
FLUENT_EXPORT int   fluent_setvbuf (FILE *fp, char *buf, int mode, size_t size);
FLUENT_EXPORT FILE *fluent_stdout(void);
FLUENT_EXPORT FILE *fluent_stderr(void);
FLUENT_EXPORT FILE *fluent_stdin(void);
# if USE_FLUENT_IO_API
#define   fopen     fluent_fopen
#define   fclose    fluent_fclose
#define   fread     fluent_fread
#define   fwrite    fluent_fwrite
#define   fprintf   fluent_fprintf
#define   fscanf    fluent_fscanf
#define clearerr fluent_clearerr
#define feof     fluent_feof
#define ferror   fluent_ferror
#define fflush   fluent_fflush
#define fgetc    fluent_fgetc
#define fgetpos  fluent_fgetpos
#define fgets    fluent_fgets
#define fputc    fluent_fputc
#define fputs    fluent_fputs
#define freopen  fluent_freopen
#define fseek    fluent_fseek
#define fsetpos  fluent_fsetpos
#define ftell    fluent_ftell
#define rewind   fluent_rewind
#define setbuf   fluent_setbuf
#define tmpfile  fluent_tmpfile
#define ungetc   fluent_ungetc
#define vfprintf fluent_vfprintf
#define getc     fluent_getc
#define putc     fluent_putc
#define setvbuf  fluent_setvbuf
#undef  stdout
#undef  stderr
#undef  stdin
#define stdout   (fluent_stdout())
#define stderr   (fluent_stderr())
#define stdin    (fluent_stdin())
# endif /* USE_FLUENT_IO_API */
#endif   /* sys_ntx86 || sys_win64 */

FLUENT_EXPORT void MSLEEP(int);
FLUENT_EXPORT char *par_getenv(char *env);
FLUENT_EXPORT  int start_cancel_box(void);
FLUENT_EXPORT  int stop_cancel_box(void);
FLUENT_EXPORT  int report_license_problem(void);

#endif /* _FLUENT_MACHINE_H */
