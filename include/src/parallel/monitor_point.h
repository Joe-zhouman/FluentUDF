
/*
  Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/

#ifndef MONITOR_POINT_H
#define MONITOR_POINT_H

extern FLUENT_EXPORT void Add_Point_Monitor_Args(const char *args);
extern FLUENT_EXPORT void Add_Surface_Monitor_Args(const char *args);
extern FLUENT_EXPORT void Write_Point_Monitor(Domain *domain);
extern FLUENT_EXPORT void Write_Surface_Monitor(Domain *domain);
extern FLUENT_EXPORT void Write_Monitors(Domain *domain);

#endif
