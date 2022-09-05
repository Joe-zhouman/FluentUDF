/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_NEIGHBOR_H
#define _FLUENT_NEIGHBOR_H

#if RP_NODE
int Show_Neighborhood_Id(Domain *domain);
void Update_Neighborhood_Id(Domain *domain);
void Create_Full_Neighborhood(Domain *);
void Check_Neighborhood(Domain *);
void Write_Neighborhood(Domain *, cxboolean, char *);
void Fill_SI_Parent_Children(Domain *);
void fill_si_parent_children(Domain *);
void fill_degenerate_iface_corner_nodes(Domain *);

/* neighbor buffer exchange */
void Neighbor_Set_Valid(Dom_Neighbor* neighbor, int valid);
void Neighbor_Set_Send_Size(Dom_Neighbor* neighbor, size_t size);
void Neighbor_Set_Recv_Size(Dom_Neighbor* neighbor, size_t size);
size_t Neighbor_Get_Send_Size(Dom_Neighbor* neighbor);
size_t Neighbor_Get_Recv_Size(Dom_Neighbor* neighbor);
void* Neighbor_Get_Send_Buffer(Dom_Neighbor* neighbor);
void* Neighbor_Get_Recv_Buffer(Dom_Neighbor* neighbor);
void Neighbor_Allocate_Buffers(Domain* domain);
void Neighbor_Free_Buffers(Domain* domain);
void Neighbor_Exchange_Sizes(Domain* domain);
void Neighbor_Exchange_Buffers(Domain* domain);

/* array exchanger */
typedef struct array_data_exchanger_t_
{
  int (*get_send_index_from_recv_count)(struct array_data_exchanger_t_* provider, int pe);
  void (*fill_send_index_from_recv)(struct array_data_exchanger_t_* provider, int pe, int* buf);

  void (*fill_buffer)(struct array_data_exchanger_t_* provider, int pe, char *buffer);
  void (*use_buffer)(struct array_data_exchanger_t_* provider, int pe, char *buffer);

  void* parameters[10];
  
  int case_id;
  int grid_id;
  Domain* domain;
  
  int* send_count;
  int* recv_count;
  int** send_array_index;
  int** recv_array_index;

  int unit_size;
  void** send_array;
  void** recv_array;
} array_data_exchanger_t;

array_data_exchanger_t* Create_Data_Exchanger(array_data_exchanger_t* source);
void Data_Exchanger_Set_Unit_Size(array_data_exchanger_t* provider, int unit_size);
void Apply_Data_Exchanger(array_data_exchanger_t* provider, int unit_size);
void Delete_Data_Exchanger(array_data_exchanger_t* provider);
void Data_Exchanger_Set_Unit_Size_If_Diff(array_data_exchanger_t* provider, int unit_size);
array_data_exchanger_t* Recreate_Data_Exchanger_As_Needed(array_data_exchanger_t* source, array_data_exchanger_t** saved);

#endif /* RP_NODE */

#endif
