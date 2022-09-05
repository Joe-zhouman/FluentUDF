/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#if !(_NT || sys_ntx86|| sys_win64)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <pwd.h>
#endif
#include <string.h>

/* This list should be same as in monitor/src/global.h */
#define MAX_MSG_LEN 1000
enum
{
  NEW_JOB,
  MY_JOBS,
  MANAGER_JOBS,
  DELETE_JOB,
  GET_INFO,
  MON_INFO,
  DATABASE,
  COM_START,
  COM_OVER,
  PRINT_JOB,
  EXITING,


  ADD_MON,
  STOP_MON,
  CHANGE_FREQ,
  EXIT_MON,
  RESTART_MON,
  SHOW_MON,
  JOBS,
  KILL,
  CHKPNT,
  REQ_OVER,

  MON_DIED,
  MANAGER_DIED,
  FLUENT_DIED,
  USER_DIED,
  OTHER,

  MONITOR,
  FLUENTJOB,
  MONUSER = 88888,
  MANAGER = 99999


};

int Contact_Monitor1(char *host, int port, char *msg);
int WhoAmI(char *myname);
void Emmit_Signal(int sig, int cnid);

