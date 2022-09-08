/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#define MAX_RINGS 10

typedef struct
{
  int n_r, n_cells;                /* number of rings, number of cells */
  cxboolean ring_dynamics;           /* include inertial terms */
  real bore;                       /* cylinder specific bore */
  real temp;                       /* wall temperature */
  real clearance;                  /* piston to wall clearance */
  real sector;                     /* sector angle for periodic simulations */
  real ring_width[MAX_RINGS];      /* ring specific geometry */
  real ring_mass[MAX_RINGS];       /*  see documentation     */
  real ring_thickness[MAX_RINGS];
  real ring_spacing[MAX_RINGS];
  real land_length[MAX_RINGS];
  real gap_height[MAX_RINGS][3];   /* height and area associated with gaps */
  real gap_area[MAX_RINGS][3];
  real vol[2 * MAX_RINGS + 1];     /* volume for each pressure */
  real press[2 * MAX_RINGS + 1];   /* volume for each pressure */
  real q_tot;                      /* total mass flow into ring pack */
  struct odeint_work_s *odeint_work; /* odeint workspace */
} *crevice_data;

/* function definitions */

FLUENT_EXPORT void init_crevice_memory(void);
FLUENT_EXPORT void free_crevice_memory(void);
FLUENT_EXPORT void crevice_model_init(Domain *domain);
FLUENT_EXPORT void Print_Crevice_Summary(crevice_data);
FLUENT_EXPORT void Read_Crevice_Data(FILE *file, cxboolean binary, cxboolean double_data);
FLUENT_EXPORT void Write_Crevice_Data(FILE *file, cxboolean binary);
FLUENT_EXPORT void Model_Initialize_crevice(void);

#if MPI_IO
FLUENT_EXPORT void Read_MPI_Crevice_Data(int fhandle, int *headerbuf, cxboolean double_data);
FLUENT_EXPORT void Write_MPI_Crevice_Data(int fhandle);
#endif
