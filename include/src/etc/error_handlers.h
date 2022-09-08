/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _Error_Handler_H
#define _Error_Handler_H

typedef void (*Error_Handler)(void);

FLUENT_EXPORT void Init_Error_Handler (void);
FLUENT_EXPORT void Push_Error_Handler (Error_Handler);
FLUENT_EXPORT Error_Handler Pop_Error_Handler (void);
FLUENT_EXPORT int FL_Error (char *, ...);
FLUENT_EXPORT void FL_Install_Error_Handlers (void);
FLUENT_EXPORT void FL_Restore_Error_Handlers (void);

#endif
