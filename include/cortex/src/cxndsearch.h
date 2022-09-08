/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#define ND_TABLE_ALLOC_SIZE 5000
#define GOLDEN_RATIO 0.69336127
#define MAX_DIM 6

typedef struct nd_point_struct
{
  double *values;
  void *data;
  struct nd_point_struct *next;
} ND_Point;

typedef struct nd_table_struct
{
  double min;
  double max;
  struct nd_table_struct *next_table;
  struct nd_table_struct *sub_table;
  ND_Point *points;
  int num;
} ND_Table;

typedef struct nd_table_dump_struct
{
  ND_Table table[ND_TABLE_ALLOC_SIZE];
  struct nd_table_dump_struct *next;
} ND_Table_Dump;

typedef struct nd_search_struct
{
  ND_Table *table;
  ND_Table_Dump *table_dump;
  int table_num_remain;
  ND_Point *points;
  double *min;
  double *max;
  int dim;
  int num;
  double *values;
  void *data;
  int total_dump_alloced;
} ND_Search;

ND_Search *CX_New_Search(int num, int dim, int sizeof_data);
void CX_Init_Search(ND_Search *, int max_dim, int max_depth);
void CX_End_Search(ND_Search *);

/* point search functions */
FLUENT_EXPORT ND_Search *CX_Start_ND_Point_Search(ND_Search *, cxboolean do_domain, int t_id);
FLUENT_EXPORT ND_Search *CX_Start_ND_Point_Search_Receptor(ND_Search *, cxboolean do_domain, int t_id, 
                                                           const cxboolean receptor_cells);
FLUENT_EXPORT CX_Cell_Id *CX_Find_Cell_With_Point(ND_Search *, double v[3], double time);
FLUENT_EXPORT CX_Cell_Id *CX_Find_Closest_Cell_To_Point(ND_Search *, double v[3], double *dist, double eps);
FLUENT_EXPORT ND_Search *CX_End_ND_Point_Search(ND_Search *);
FLUENT_EXPORT int SV_Fill_ND_Points(CX_Cell_Id *pdata, double *values,
                                    double *tot_min, double *tot_max, int dim);
FLUENT_EXPORT int SV_Fill_ND_Points_Receptor(CX_Cell_Id *pdata, double *values, double *tot_min, double *tot_max, 
                                             int dim, const cxboolean receptor_cells);

FLUENT_EXPORT void CX_Find_Multiple_Cells_With_Point(ND_Search *search_table, double v[3], CX_Cell_Id **cells, int* numCells);

void print_nd_diagnostics(ND_Search *s);
