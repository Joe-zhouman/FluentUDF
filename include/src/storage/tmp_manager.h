/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef TMP_MANAGER_H
#define TMP_MANAGER_H

/* #include "storage.h" */   /* Svar */
/* This doesn't work, because storage.h includes this file.
 * --> must make sure that storage.h has been included before this
 * file is included, and include storage.h where this file is needed:
 */
#ifndef _FLUENT_STORAGE_H
# error Must include storage.h to include tmp_manager.h
#endif

extern FLUENT_EXPORT Svar get_tmp_svar(int type, const int line, const char *file);
extern FLUENT_EXPORT void return_tmp_svar(int svar, const int line, const char *file);
extern FLUENT_EXPORT void print_tmp_svar_manager(void);

#define GET_TMP_SVAR(_type) \
  get_tmp_svar(_type, __LINE__, __FILE__)

#define RETURN_TMP_SVAR(_svar) \
  return_tmp_svar(_svar, __LINE__, __FILE__)

#endif
