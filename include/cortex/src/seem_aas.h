/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/
#if _NT
#  include "windows.h"
#  define seem_dlopenprocess() (void*)(GetModuleHandle(0))
#  define seem_dlopen(path) (void*)(LoadLibrary(path))
#  define seem_dlsym(handle, symbol) GetProcAddress((HMODULE)(handle), symbol)
#  define seem_dlclose(handle) FreeLibrary((HMODULE)(handle))
#else
#  include <dlfcn.h>
#  define seem_dlopenprocess() dlopen(0, RTLD_LAZY)
#  define seem_dlopen(path) dlopen(path, RTLD_LAZY)
#  define seem_dlsym(handle, symbol) dlsym(handle, symbol)
#  define seem_dlclose(handle) dlclose(handle)
#endif

/*procedure types in ORB Exception client*/
typedef int     (*HookToFluentExceptionHolderDllProc)();
typedef const char *(*GetLastErrorMessageProc)();
typedef int     (*InitObjectRequestBrokerProc)();
typedef int     (*ConnectToExceptionHolderUsingIorProc)(const char *);
typedef int     (*ConnectToExceptionHolderUsingIorFileProc)(const char *);
typedef int     (*AddMessageToExceptionHandlerProc)(const char *);
typedef int     (*SetQuestionTypeProc)(const char *);
typedef int     (*SetQuestionPromptProc)(const char *);
typedef int     (*SetQuestionDefaultAnswerProc)(const char *);
typedef int     (*SetQuestionMenuProc)(const char *);
typedef int     (*SetQuestionHelpProc)(const char *);
typedef int     (*SetQuestionMsgProc)(const char *);
typedef int     (*TerminateProcessProc)();

typedef struct
{
  HookToFluentExceptionHolderDllProc      hookToFluentExceptionHolderDll;
  /*methods dlsymed from exception client*/
  GetLastErrorMessageProc           exceptionclient_getLastErrorMessage;
  InitObjectRequestBrokerProc         exceptionclient_initObjectRequestBroker;
  ConnectToExceptionHolderUsingIorProc    exceptionclient_connectToExceptionHolderUsingIor;
  ConnectToExceptionHolderUsingIorFileProc  exceptionclient_connectToExceptionHolderUsingIorFile;
  AddMessageToExceptionHandlerProc      exceptionclient_addMessageToExceptionHandler;
  SetQuestionTypeProc             exceptionclient_setQuestionType;
  SetQuestionPromptProc           exceptionclient_setQuestionPrompt;
  SetQuestionDefaultAnswerProc        exceptionclient_setQuestionDefaultAnswer;
  SetQuestionMenuProc             exceptionclient_setQuestionMenu;
  SetQuestionHelpProc             exceptionclient_setQuestionHelp;
  SetQuestionMsgProc              exceptionclient_setQuestionMsg;
  TerminateProcessProc            exceptionclient_terminateProcess;
  /*status of Fluent aaS and ORB Exception client*/
  char                   *g_szIor;
  int                     iIsAasOn;
  int                     iFluentExceptionClientLoaded;
  int                     iORBInitialized;
  int                     iHandlerConnected;
  int                     iQuitRequested;
} ExcClientStruct;

extern ExcClientStruct aas;

int resolve_aas_initialization();
FLUENT_EXPORT void set_exchandler_ior (const char *ior);
int isAasOn(void);