/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_LMAIN_H
#define _FLUENT_LMAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dll.h"

#define ASSQ_LIST_TYPECONS(l,typecons,label,value)\
  l = cons(NIL,l);\
  CAR(l) = cons(NIL,NIL);\
  CAR(CAR(l)) = intern(label);\
  CDR(CAR(l)) = typecons(value);
#define ASSQ_LIST_FLOCONS(l,label,value)\
       ASSQ_LIST_TYPECONS(l,flocons,label,value)
#define ASSQ_LIST_FIXCONS(l,label,value)\
       ASSQ_LIST_TYPECONS(l,fixcons,label,value)
#define ASSQ_LIST_STRINGCONS(l,label,value)\
       ASSQ_LIST_TYPECONS(l,stringcons,label,value)
#define ASSQ_LIST_INTERN(l,label,value)\
       ASSQ_LIST_TYPECONS(l,intern,label,value)
#define ASSQ_LIST_BOOLCONS(l,label,value)\
       ASSQ_LIST_TYPECONS(l,booleancons,label,value)

#define ASSQ_LIST_FLOCONS_LIST(l,label,array,length) \
  l = cons(NIL,l);\
  CAR(l) = cons(NIL,NIL);\
  CAR(CAR(l)) = intern(label);\
  {\
    int index;\
    if (length > 0)\
      for (index=length-1; index>=0; index--)\
        {\
          CDR(CAR(l)) = cons(NIL,CDR(CAR(l)));\
          CAR(CDR(CAR(l))) = flocons(array[index]);\
        }\
  }\

#if RP_NODE
FLUENT_EXPORT void PRF_interrupt_host(void);
FLUENT_EXPORT void PRF_spawned(void);
FLUENT_EXPORT extern void PRF_Node_repl(void);
FLUENT_EXPORT void complete_command(cxboolean);
#else
FLUENT_EXPORT Pointer rpgetvar(const char *);
FLUENT_EXPORT Pointer rpgetvar_errprotect(const char *s);
FLUENT_EXPORT Pointer domaingetvar(int, const char *);
#endif

FLUENT_EXPORT Thread *thread_arg (Pointer, const char *);
FLUENT_EXPORT Thread *domain_thread_arg (Domain *, Pointer, const char *);
FLUENT_EXPORT real *vector_arg (Pointer, real *, int, const char *);
FLUENT_EXPORT FILE *file_port_arg(Pointer, const char *);
FLUENT_EXPORT Pointer RP_Get_List_Ref(const char *s, int n);
FLUENT_EXPORT Pointer RP_Get_Sub_List_Ref(const char *s, int n, int m);

FLUENT_EXPORT real Get_Input_Parameter(const char *param_id);
#define RP_Get_Input_Parameter Get_Input_Parameter

#if PARALLEL
FLUENT_EXPORT const char *PRF_Command_Start(const char *, ...);
# if RP_HOST
FLUENT_EXPORT void PRF_Host_Finish(cxboolean, const char *, int);
# endif /* RP_HOST */

# if RP_NODE
FLUENT_EXPORT void PRF_Node_Finish(cxboolean, const char *, int);
# endif /* RP_NODE */

# if RP_HOST
#  define PRF_START(command_args) \
  {                               \
    START_PROFILE2;\
       DISABLE_INTERRUPTS(); \
       PRF_Command_Start command_args;
#  define PRF_FINISH(wait) \
        if (wait) PRF_Host_Finish(TRUE,__FILE__,__LINE__); \
  RESTORE_INTERRUPTS();                                    \
  STOP_PROFILE2;\
      }

#  define PRF_START_NO_PROFILE(command_args) \
  {                               \
       DISABLE_INTERRUPTS(); \
       PRF_Command_Start command_args;
#  define PRF_FINISH_NO_PROFILE(wait) \
        if (wait) PRF_Host_Finish(TRUE,__FILE__,__LINE__); \
  RESTORE_INTERRUPTS();                                    \
  }

# endif /* RP_HOST */
# if RP_NODE
#  define PRF_START(command_args) START_PROFILE2;
#  define PRF_FINISH(wait) if (wait) PRF_Node_Finish(TRUE,__FILE__,__LINE__); \
  STOP_PROFILE2;

#  define PRF_START_NO_PROFILE(command_args)
#  define PRF_FINISH_NO_PROFILE(wait) if (wait) PRF_Node_Finish(TRUE,__FILE__,__LINE__);

# endif /* RP_NODE */
#else
/* # if RP_DPM_CACHE
 */ /* workpile requires thread locks (mutexes), must avoid interrupts: */
#  define PRF_START(command_args)  { DISABLE_INTERRUPTS();
#  define PRF_FINISH(wait)           RESTORE_INTERRUPTS(); }
/* # else
 * #  define PRF_START(command_args)
 * #  define PRF_FINISH(wait)
 * # endif
 */
#endif /* PARALLEL */

FLUENT_EXPORT void init_rsubrs(void);
FLUENT_EXPORT void CreateDomainForIMesh(long, int, int *, int *, int *, int *);
FLUENT_EXPORT void ResetMixedInteriorThreadType(void);
FLUENT_EXPORT Domain *Get_Domain(int id);
FLUENT_EXPORT Domain *Get_Domain_By_Name(const char *name);
FLUENT_EXPORT char *cx_strdup(const char *orig);
FLUENT_EXPORT void transfer_file_to_nodes(char *file_to_transfer, int *gl_active_nodes, int remove);
extern FLUENT_EXPORT int postDomainId;

#if RP_NODE
FLUENT_EXPORT void get_multiport_bin(char *);
#endif

FLUENT_EXPORT void rpsetvar(const char *, Pointer);
FLUENT_EXPORT Domain *Set_Current_Global_Domain(Domain *d);
FLUENT_EXPORT void registerSchemeBindings();

FLUENT_EXPORT cxboolean Delayed_Error_P(void);

#ifdef __cplusplus
}
#endif

#endif /* _FLUENT_LMAIN_H */
