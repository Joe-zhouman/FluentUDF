/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/
#ifndef CX_FUNCTION_MANAGER_H
#define CX_FUNCTION_MANAGER_H


extern int fluent_register_export_function(const char *name, const char *type, void *function);
extern void *fluent_get_export_function(const char *name, const char *type);

extern int fluent_get_num_export_function();
extern const char *fluent_get_export_function_name(int i);
extern const char *fluent_get_export_function_type(int i);

/* export_function.h */
#define FLUENT_REGISTER_EXPORT_FUNCTION(a_function, type)               \
  fluent_register_export_function(#a_function, type, a_function);

#define FLUENT_GET_EXPORT_FUNCTION(name, type)          \
  fluent_get_export_function(#name, type);

#endif
