/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#if CX_GUI
# define UIBUSY(_b) ui_busy(_b)
#else
# define UIBUSY(_b) /* no_op */
#endif

#define REF_FRAME( norm, tngt, binorm, radius, resolution ) \
    UNIT_VECT( norm, norm ); \
    UNIT_VECT( tngt, tngt ); \
    CROSS_PROD( norm, tngt, binorm); \
    UNIT_VECT( binorm, binorm); \
    SCALE_VECT( norm, radius, norm );\
    SCALE_VECT( binorm, radius, binorm ); \
    if ( resolution == 2 ) \
       SCALE_VECT( binorm, 0.05, binorm )

/* Allocate _n floats */
#define FLOAT_MALLOC(_n) ((float*)CX_Malloc((_n)*sizeof(float)))

#define UPDATE_INTERVAL 333 /* should match UPDATE_INTERVAL in dpm_path.c */

#define NUM_ANGLE_SUBDIV 20
#ifndef PI
#define PI 3.14159265358979323846
#endif

#define SMALL_LENGTH 1e-10

/* Number of particle paths and path chunks to allocate at a time. */
#define PART_PATH_ALLOC 100
#define PATH_CHUNK_ALLOC 100

#define PROFILE_EXPORT 0

#define MAX_PATH_SCALARS 10

/* A segment of a particle path */
typedef struct path_chunk
{
  int   npts, curr_index, nsegments;
  float   *pts, *scalars;
  int           nscalars;
  int           step_begin;
  int           step_end;
  struct path_chunk *next;
} Path_Chunk;

/* A single particle's complete path is stored as a list of Path_Chunks. */
typedef struct particle_path
{
  int64_t       part_id;
  int   tot_num_pts, pts_rendered;
  int   curr_index;   /* for rendering assist */
  int           nchunks;
  cxboolean     do_sort;
  float   norm[3], tngt[3];
  Path_Chunk  *first, *to_be_rendered;
} Particle_Path;

/* Store parameters for looped paths. */
typedef struct temp_path_struct
{
  float  min, max;
  int    max_steps;
  int  resolution;
} Path_Tmp_Data;

typedef struct PathHashEntry_s
{
  struct PathHashEntry_s *next;
  Particle_Path track;
} PathHashEntry;

Path_Chunk *Path_Chunk_Malloc(void);
void Path_Chunk_Free(Path_Chunk *part);
void Order_Path_Chunks_If_Needed(Particle_Path *track, void ***chunk_array, size_t *chunk_array_size);
int Hash_64_To_Table(int64_t key, int table_size);
float Get_Points_Distance(float *pt0, float *pt1);
float *Insert_Cross_Section(float *cs, int res, float norm[3], float binorm[3], float sin_tab[], float cos_tab[], float ep[]);
void Rotate_Vector_By_Cos_Inplace(float *axis, float cos_alpha, float *norm);

#ifdef __cplusplus
}
#endif
