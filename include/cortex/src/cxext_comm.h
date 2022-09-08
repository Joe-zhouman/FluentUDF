/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/*
 *  cxext_comm.h
 *  Code for communication with ext. port
 *  Copyright 1987-2022 Ansys Inc
 */
#ifndef _CXEXT_COMM_H_
#define _CXEXT_COMM_H_

/* ext port ID: obtained through command-line argument */
extern int extCmdPortID;
/* ext port address: obtained through command-line argument */
extern char extCmdPortAddr[256];
/* ext port handle. Obtained after connection  */
extern int extCmdPort;
/* scheme port wrapper to extCmdPort */
extern Pointer extCmdPort_port;
extern int extPortWaitForMessage;
extern int extPortReadingMessage;
/* Flag to switch off reply message to WB. */
extern CXBoolean extCmdReplyNeeded;

FLUENT_EXPORT Pointer Make_Socket_Port(int *socket_fd);
FLUENT_EXPORT void Close_Socket_Port(Pointer *z);

/* establish connection with ext. port */
FLUENT_EXPORT void Establish_Ext_Port_Connection(void);

/* process any command from ext port */
FLUENT_EXPORT void Process_Ext_Port_Messages(cxboolean allowRecursive);
FLUENT_EXPORT void Process_Ext_Error_Port_Messages(void);

FLUENT_EXPORT void Close_Ext_Socket(void);
FLUENT_EXPORT void Send_Ext_Port_Complete_Gui_Log(char *);

void    CX_Register_File_List(Pointer fileEventInfo);
void    CX_Register_File(Pointer fileEventInfo);
void    CX_Register_Albion_Event(Pointer eventInfo);
void    CX_Send_WB_Command(Pointer list);

#endif
