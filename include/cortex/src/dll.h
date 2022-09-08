/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _CORTEX_DLL_H
#define _CORTEX_DLL_H


/*
 * Define DLL_EXPORT to indicate whether a global
 * symbol is to be exported or imported.
 *
 * This is really only useful for windows DLLs but
 * the DLL_EXPORT macro should in the declarations
 * of all intentionally exported symbols.
 *
 * For UNIX it will be undefined, for Windows it
 * will specify either dllexport or dllimport as
 * given by the xxxx_EXPORTING macro.
 */

/* add known archs that don't support dynamic linking */
#if defined (_aix414) || defined (fugitsu)
# define NO_DYNAMIC_LINKING 1
#endif

/* FLUENT */
#if (defined(_WIN32) || defined (WIN64)) && !defined(UDFCONFIG_H)
#  ifdef FLUENT_EXPORTING
# define FLUENT_EXPORT __declspec(dllexport)
#  else
# define FLUENT_EXPORT __declspec(dllimport)
#  endif
#else
#  define FLUENT_EXPORT
#endif

/* UDFs and other DLLs */
#if (defined(_WIN32) || defined (WIN64))
#  ifdef UDF_EXPORTING
# define UDF_EXPORT __declspec(dllexport)
#  else
/* we can't implicitly import from unknown UDFs */
# define UDF_EXPORT /* __declspec(dllimport) */
#  endif
#else
#  define UDF_EXPORT
#endif

/* C++ */
#ifdef __cplusplus
# define EXTERNC extern "C"
#else
# define EXTERNC
#endif

/* system-independent DLL calls */
#if !defined(UDFCONFIG_H)
/*
 *  Not for UDF consumption,first because they should'nt
 *  have to load DLLs with this mechanism and second because
 *  the stdarg.h inclusion fails with interpreted UDFs
 */
#include <stdarg.h>
typedef void (*CX_DLL_PTF_void) (); /* pointer to function returnning void */

#ifdef __cplusplus
extern "C"
{
#endif
#if !(defined(_WIN32) || defined (WIN64))
FLUENT_EXPORT void *CX_DLL_OpenLib_Globally(char *name, char *dir, int items, ...);
#endif
FLUENT_EXPORT void *CX_DLL_OpenLib(char *name, char *dir, int items, ...);
FLUENT_EXPORT int CX_DLL_CloseLib(void *lib);
FLUENT_EXPORT CX_DLL_PTF_void CX_DLL_GetProc(void *lib, const char *name);
FLUENT_EXPORT void *CX_DLL_GetData(void *lib, const char *name);
FLUENT_EXPORT char *CX_DLL_GetError(void);
FLUENT_EXPORT int RegFile(const char *file);
#ifdef __cplusplus
}
#endif
#endif
#endif /* _CORTEX_DLL_H */

