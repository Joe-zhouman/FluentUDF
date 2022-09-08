/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_COARSE_PAR_H
#define _FLUENT_COARSE_PAR_H

#include "dll.h"

#define INTERFACE_C_BUFF_INTS sizeof(InterFace_C_Msg_Buff_t)/sizeof(int)

typedef struct InterFace_C_Msg_Buff_Struct
{
  int old_int_cell_id;
  int old_ext_cell_id;
  int new_int_cell_id;
  int face_node_id[MAX_FACES_PER_CELL][MAX_NODES_PER_FACE];
  int cell_node_id[MAX_NODES_PER_CELL];
  int new_cell_node_id;
  int new_periodic_node_id;
  int part_id;
} InterFace_C_Msg_Buff_t;

typedef float ND_Float_t[ND_ND];

typedef struct Swap_Msg_Buff_Struct
{
  int int_cell_id;
  int ext_cell_id;
  int part_id;
  int active;
} Swap_Msg_Buff_t;

#define ADD_SWAP_MSG_BUFF(f,tf) \
 BUFF_MEM_CHK(swap_buff_ind, Swap_Msg_Buff_Len, Swap_Msg_Buff, Swap_Msg_Buff_t);\
 Swap_Msg_Buff[swap_buff_ind].int_cell_id = C_ID(FACE_INTERIOR_CELL(f,tf),FACE_INTERIOR_CELL_THREAD(f,tf));\
 Swap_Msg_Buff[swap_buff_ind].ext_cell_id = C_ID(FACE_EXTERIOR_CELL(f,tf),FACE_EXTERIOR_CELL_THREAD(f,tf));\
 Swap_Msg_Buff[swap_buff_ind].part_id = FACE_EXTERIOR_CELL_PART(f,tf);\
 Swap_Msg_Buff[swap_buff_ind].active = TRUE;\
 swap_buff_ind++

FLUENT_EXPORT void Free_Coarse_Buffs(void);
FLUENT_EXPORT void gen_remote_swap_msg(cell_t, Thread *, face_t, Thread *, int old_cell_id);

FLUENT_EXPORT void Swap_Phase_Begin (void);
FLUENT_EXPORT void Swap_Phase_End (Domain *domain);

extern FLUENT_EXPORT Swap_Msg_Buff_t *Swap_Msg_Buff;
extern FLUENT_EXPORT int swap_buff_ind;
extern FLUENT_EXPORT int Swap_Msg_Buff_Len;

#endif /* _FLUENT_COARSE_PAR_H */
