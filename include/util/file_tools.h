/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/
#ifndef _FLUENT_UTIL_FILE_TOOLS_H
#define _FLUENT_UTIL_FILE_TOOLS_H

#include "global.h"

/* maximum history file line length, see para.c */
#define FILE_MAX_LINE_LENGTH 2048

enum {MAX_PATH_LEN = 4096};

#if _NT
/* windows does provide different 64-bit pointers to locate a position in file */
/* NOTE:
 * If a Windows process reads a UNIX/Linux-style text file,
 * fseek / _fseeki64 returns incorrect values (too large by one
 * for every LF line ending already passed, because they're
 * converted to CRLF internally). To avoid trouble, please
 * make sure to open the file using 'fopen(..., "rb")',
 * i.e. in some kind of binary mode..!
 */
#define DPM_FTELL _ftelli64
#define DPM_FSEEK _fseeki64
#define DPM_FPOS  __int64
#else
#define DPM_FTELL ftell
#define DPM_FSEEK fseek
#define DPM_FPOS  long
#endif

FLUENT_EXPORT void
ftruncate_at_current_position(FILE *fp);

FLUENT_EXPORT int
fseek_string_forward(FILE *file, char *str);

FLUENT_EXPORT int
fseek_string_backward(FILE *file, char *str);

FLUENT_EXPORT void
fskip_lines(FILE *f, int nlines);

FLUENT_EXPORT cxboolean
file_exists_p(const char *fname);

#endif /* _FLUENT_UTIL_FILE_TOOLS_H */
