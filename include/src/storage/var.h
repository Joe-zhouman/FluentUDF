/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_VAR_H
#define _FLUENT_VAR_H

#include "dll.h"
#if WIN64
#include <basetsd.h>
#endif

FLUENT_EXPORT cxboolean RP_Variable_Exists_P(const char *s);
FLUENT_EXPORT double RP_Get_Float(const char *s);
#if WIN64
FLUENT_EXPORT LONG64 RP_Get_Integer(const char *s);
FLUENT_EXPORT void RP_Set_Integer(const char *s, LONG64 v);
#else
FLUENT_EXPORT long RP_Get_Integer(const char *s);
FLUENT_EXPORT void RP_Set_Integer(const char *s, long v);
#endif
FLUENT_EXPORT const char *RP_Get_String(const char *s);
FLUENT_EXPORT cxboolean RP_Get_Boolean(const char *s);

FLUENT_EXPORT int RP_Get_List_Length(const char *s);
FLUENT_EXPORT const char *RP_Get_List_Ref_String(const char *s, int n);
FLUENT_EXPORT double RP_Get_List_Ref_Float(const char *s, int n);
FLUENT_EXPORT double RP_Get_Sub_List_Ref_Float(const char *s, int n, int m);
FLUENT_EXPORT cxboolean RP_Get_Sub_List_Ref_Boolean(const char *s, int n, int m);
FLUENT_EXPORT int RP_Get_Sub_List_Ref_Int(const char *s, int n, int m);
FLUENT_EXPORT const char *RP_Get_Sub_List_Ref_String(const char *s, int n, int m);
FLUENT_EXPORT cxboolean RP_Get_List_Ref_Boolean(const char *s, int n);
FLUENT_EXPORT int RP_Get_List_Ref_Int(const char *s, int n);

FLUENT_EXPORT void RP_Set_Float(const char *s, double v);
FLUENT_EXPORT void RP_Set_Boolean(const char *s, cxboolean v);
FLUENT_EXPORT void RP_Set_String(const char *s, const char *v);
FLUENT_EXPORT void RP_Set_Symbol(const char *s, const char *v);
FLUENT_EXPORT void RP_Set_List_of_Boolean(const char *s, cxboolean [], int length);
FLUENT_EXPORT void RP_Set_List_of_Float(const char *s, double *a, int length);
FLUENT_EXPORT void RP_Set_List_of_Real(const char *s, real *a, int length);
FLUENT_EXPORT void RP_Set_List_of_Integer(const char *s, int *a, int length);
FLUENT_EXPORT void RP_Set_List_of_String(const char *s, const char *const *a, int length);
FLUENT_EXPORT void RP_Set_A_Member_Of_A_List_Of_Strings(const char *s, const char *a, int index);

#define RP_Get_Real(s)((real)RP_Get_Float(s))
#define RP_Set_Real(s,v)RP_Set_Float(s,(double)(v))
#define RP_Get_Double(s)((double)RP_Get_Float(s))

/* domainvars */
FLUENT_EXPORT double Domainvar_Get_Float(int did, const char *s);
#if WIN64
FLUENT_EXPORT LONG64 Domainvar_Get_Integer(int did, const char *s);
#else
FLUENT_EXPORT long Domainvar_Get_Integer(int did, const char *s);
#endif
FLUENT_EXPORT const char *Domainvar_Get_String(int did, const char *s);
FLUENT_EXPORT cxboolean Domainvar_Get_Boolean(int did, const char *s);

FLUENT_EXPORT int Domainvar_Get_List_Length(int did, const char *s);
FLUENT_EXPORT const char *Domainvar_Get_List_Ref_String(int did, const char *s, int n);
FLUENT_EXPORT double Domainvar_Get_List_Ref_Float(int did, const char *s, int n);
FLUENT_EXPORT double Domainvar_Get_Sub_List_Ref_Float(int did, const char *s, int n, int m);
FLUENT_EXPORT cxboolean Domainvar_Get_List_Ref_Boolean(int did, const char *s, int n);
FLUENT_EXPORT int Domainvar_Get_List_Ref_Int(int did, const char *s, int n);

FLUENT_EXPORT void Domainvar_Set_Float(int did, const char *s, double v);
#if WIN64
FLUENT_EXPORT void Domainvar_Set_Integer(int did, const char *s, LONG64 v);
#else
FLUENT_EXPORT void Domainvar_Set_Integer(int did, const char *s, long v);
#endif
FLUENT_EXPORT void Domainvar_Set_Boolean(int did, const char *s, cxboolean v);
FLUENT_EXPORT void Domainvar_Set_String(int did, const char *s, const char *v);
FLUENT_EXPORT void Domainvar_Set_Symbol(int did, const char *s, const char *v);
FLUENT_EXPORT void Domainvar_Set_List_of_Boolean(int did, const char *s, cxboolean [], int length);
FLUENT_EXPORT void Domainvar_Set_List_of_Float(int did, const char *s, double *a, int length);
FLUENT_EXPORT void Domainvar_Set_List_of_Real(int did, const char *s, real *a, int length);
FLUENT_EXPORT void Domainvar_Set_List_of_Integer(int did, const char *s, int *a, int length);
FLUENT_EXPORT void Domainvar_Set_List_of_String(int did, const char *s, const char *const *a, int length);
FLUENT_EXPORT void Domainvar_Set_A_Member_Of_A_List_Of_Strings(int did, const char *s, const char *a, int index);

#define Domainvar_Get_Real(d,s)((real)Domainvar_Get_Float(d,s))
#define Domainvar_Set_Real(d,s,v)Domainvar_Set_Float(d,s,(double)(v))



FLUENT_EXPORT cxboolean PRF_get_boolean(const char *s);
FLUENT_EXPORT int PRF_get_integer(const char *s);
FLUENT_EXPORT double PRF_get_real(const char *s);
FLUENT_EXPORT const char *PRF_get_string(const char *s);

FLUENT_EXPORT cxboolean PRF_get_boolean_list(const char *s, int n);
FLUENT_EXPORT double PRF_get_real_list(const char *s, int n);
FLUENT_EXPORT int PRF_get_int_list(const char *s, int n);
FLUENT_EXPORT const char *PRF_get_string_list(const char *s, int n);

FLUENT_EXPORT int PRF_get_list_length(const char *s);

FLUENT_EXPORT void PRF_set_boolean(const char *s, int len, cxboolean *ptr);
FLUENT_EXPORT void PRF_set_integer(const char *s, int len, int *ptr);
FLUENT_EXPORT void PRF_set_real(const char *s, int len, double *ptr);
FLUENT_EXPORT void PRF_set_string(const char *s, int len, const char *ptr);

FLUENT_EXPORT void prf_print_vars(void);
FLUENT_EXPORT void PRF_Update_All_RPvars(void);
#if PARALLEL
FLUENT_EXPORT void PRF_Set_RPvars(int id);
#endif


FLUENT_EXPORT cxboolean D_PRF_get_boolean(int did, const char *s);
FLUENT_EXPORT int D_PRF_get_integer(int did, const char *s);
FLUENT_EXPORT double D_PRF_get_real(int did, const char *s);
FLUENT_EXPORT const char *D_PRF_get_string(int did, const char *s);

FLUENT_EXPORT cxboolean D_PRF_get_boolean_list(int did, const char *s, int n);
FLUENT_EXPORT double D_PRF_get_real_list(int did, const char *s, int n);
FLUENT_EXPORT int D_PRF_get_int_list(int did, const char *s, int n);
FLUENT_EXPORT const char *D_PRF_get_string_list(int did, const char *s, int n);

FLUENT_EXPORT int D_PRF_get_list_length(int did, const char *s);

FLUENT_EXPORT void D_PRF_set_boolean(int did, const char *s, int len, cxboolean *ptr);
FLUENT_EXPORT void D_PRF_set_integer(int did, const char *s, int len, int *ptr);
FLUENT_EXPORT void D_PRF_set_real(int did, const char *s, int len, double *ptr);
FLUENT_EXPORT void D_PRF_set_string(int did, const char *s, int len, const char *ptr);


#endif /* _FLUENT_VAR_H */

