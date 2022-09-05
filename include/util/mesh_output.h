/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef FLUENT_MESH_OUTPUT_H
#define FLUENT_MESH_OUTPUT_H

/**
 * @file
 *   mesh_output.h
 * @brief
 *   Header file for Mesh Output functions
 */

#include "global.h"
#include "mem.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * Mesh output flags
 */
typedef enum Mesh_Output_Flag_Enum
{
  OUTPUT_FLAG_XML      = 0,
  OUTPUT_FLAG_PVD      = 1,
  OUTPUT_FLAG_PVTU     = 2,
  OUTPUT_FLAG_BINARY   = 3,
  OUTPUT_FLAG_BOUNDS   = 4,
  OUTPUT_FLAG_STAMPS   = 5,
  OUTPUT_FLAG_SKIP_IDS = 6,
  OUTPUT_FLAG_NODE_BND = 7,
  OUTPUT_FLAG_INVALID
} Mesh_Output_Flag;

/**
 * VTK location types
 */
typedef enum VTK_Loc_Type_Enum
{
  VTK_LOC_POINT   = 0,
  VTK_LOC_ELEMENT = 1,
  VTK_LOC_INVALID
} VTK_Loc_Type;

/**
 * VTK array data types
 */
typedef enum VTK_Data_Type_Enum
{
  VTK_TYPE_INT    = 0,
  VTK_TYPE_UINT   = 1,
  VTK_TYPE_LONG   = 2,
  VTK_TYPE_ULONG  = 3,
  VTK_TYPE_SCHAR  = 4,
  VTK_TYPE_UCHAR  = 5,
  VTK_TYPE_SSHORT = 6,
  VTK_TYPE_USHORT = 7,
  VTK_TYPE_FLOAT  = 8,
  VTK_TYPE_DOUBLE = 9,
  VTK_TYPE_STRING = 10,
  VTK_TYPE_INVALID
} VTK_Data_Type;

/**
 * VTK element types
 * Taken from the VTK File Formats document
 */
typedef enum VTK_Element_Map_Enum
{
  VTK_VERTEX         = 1,
  VTK_POLY_VERTEX    = 2,
  VTK_LINE           = 3,
  VTK_POLY_LINE      = 4,
  VTK_TRIANGLE       = 5,
  VTK_TRIANGLE_STRIP = 6,
  VTK_POLYGON        = 7,
  VTK_PIXEL          = 8,
  VTK_QUAD           = 9,
  VTK_TETRA          = 10,
  VTK_VOXEL          = 11,
  VTK_HEXAHEDRON     = 12,
  VTK_WEDGE          = 13,
  VTK_PYRAMID        = 14,
  VTK_POLYHEDRON     = 42,
  VTK_INVALID
} VTK_Element_Map;

/**
 * @struct
 *   VTK_Array_Data_Struct
 * @brief
 *   Data structure for VTK arrays
 */
typedef struct VTK_Array_Data_Struct
{
  /* Member data */

  /** Location type */
  VTK_Loc_Type loc;

  /** Data type */
  VTK_Data_Type type;

  /** Array size */
  int size;

  /** Number of components */
  int n_components;

  /** Array name */
  char name[50];

  /** Array */
  void *array;

  /** Data size width */
  size_t width;

  /** Optional SVar */
  Svar sv;

  /** Optional post-processing procedure */
  void (*post)(char *);

} VTK_Array_Data;

/* * * * * * * * * * * * Global Function Definitions * * * * * * * * * * * * */

FLUENT_EXPORT Mesh_Output_Flag Get_Mesh_Output_Flags (void);
FLUENT_EXPORT cxboolean Chk_Mesh_Output_Flag (const Mesh_Output_Flag);
FLUENT_EXPORT void Clr_Mesh_Output_Flag (const Mesh_Output_Flag);
FLUENT_EXPORT void Set_Mesh_Output_Flag (const Mesh_Output_Flag);
FLUENT_EXPORT void Set_Mesh_Output_Flags (const Mesh_Output_Flag);
FLUENT_EXPORT void Set_Mesh_Output_Bounds (const real *, const real *);
FLUENT_EXPORT void Set_Mesh_Output_Sub_Directory (const char *);
FLUENT_EXPORT void Write_PVD_File (const char *, const char *,
                                   int, double, int);
FLUENT_EXPORT void Write_PVTU_File (const char *, const char *,
                                    int, VTK_Array_Data *);
FLUENT_EXPORT void Write_VTK_File (const char *, int, int, int,
                                   double **, int **, int *, int *,
                                   int, VTK_Array_Data *, cxboolean);
FLUENT_EXPORT void Output_Mesh_Entities_Attributes (const char *, Objp *, int,
                                                    int, VTK_Array_Data *);
FLUENT_EXPORT void Output_Mesh_Entities (const char *, Objp *, int);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#endif /* FLUENT_MESH_OUTPUT_H */

/*****************************************************************************/
