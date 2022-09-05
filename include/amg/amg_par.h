/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef AMG_PAR_HEAD__
#define AMG_PAR_HEAD__

typedef enum Data_Type
{
  /* INT_DATA_TYPE=0, not implemented */
  FLOAT_DATA_TYPE = 1,
  DOUBLE_DATA_TYPE = 2
} Data_Type;

/* This will used for staging the exchange to enable overlapping */
typedef enum Exchange_Function_Type_
{
  AMG_EXCHANGE_SEND_RECV, /* only invoke the send/recv */
  AMG_EXCHANGE_WAIT_SET,  /* only do the wait all, and update from exch buffer */
  AMG_EXCHANGE_ALL        /* do all the avove */
} Exchange_Stage;

#define IF_EXCH exch_stage == AMG_EXCHANGE_SEND_RECV ||  \
    exch_stage == AMG_EXCHANGE_ALL
#define IF_ALLOC IF_EXCH
#define IF_WAIT exch_stage == AMG_EXCHANGE_WAIT_SET ||   \
    exch_stage == AMG_EXCHANGE_ALL

void New_Exchange_Buffer(int commtype,
                         int datatype);
void Alloc_Exchange_Buffer(int neighbors,
                           int my_id,
                           int *nb_id,
                           int overlapping,
                           int neq,
                           int **interior,
                           int **exterior);
void Perform_Exchange_Buffer(void *x,
                             int **interior,
                             int ***interior_map,
                             int **exterior,
                             int ***exterior_map,
                             Exchange_Stage exch_stage);
void Perform_Exchange_Buffer_I(int *x,
                               int **interior,
                               int ***interior_map,
                               int **exterior,
                               int ***exterior_map,
                               Exchange_Stage exch_stage);

extern void Alloc_Exchange_Buffer_DistGraph(int commType, int myid, int numEqs, 
                                    int numNeighbors,int* neighbors,
                                    int* interior, int* exterior);
extern void Perform_Exchange_Buffer_Real_DistGraph(real *x,
                             int *interior,
                             int **interior_map,
                             int *exterior,
                             int **exterior_map);
extern void Perform_Exchange_Buffer_Index_DistGraph(int *x,
                               int *interior,
                               int **interior_map,
                               int *exterior,
                               int **exterior_map);
#endif
