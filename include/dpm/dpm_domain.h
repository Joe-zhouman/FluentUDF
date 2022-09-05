/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef DPM_DOMAIN_HEADER
#define DPM_DOMAIN_HEADER

#if RP_NODE
typedef struct migrate_array_t_
{
  int ncells;
  cat_t *cells;
  char *cell_dup;
  cxindex *cid;
  int cell_nt;
  struct thread_map_t_ *cell_tmap;
  cat_t *cells_mapped;
  int ncells_mapped;

  int nfaces;
  fat_t *faces;
  char *face_dup;
  cxindex *fid;
  int face_nt;
  struct thread_map_t_ *face_tmap;
  fat_t *faces_mapped;
  int nfaces_mapped;

  int nnodes;
  Node **nodes;
  Node **snodes; /* shadow nodes */
  char *node_dup;

  /* exterior cells */
  int necells;
  cat_t *ecells;
  char *ecell_dup;
  cxindex *ecid;
  int ecell_nt;
  struct thread_map_t_ *ecell_tmap;
  cat_t *ecells_mapped;
  int necells_mapped;
} migrate_array_t;
#endif /* RP_NODE */

FLUENT_EXPORT cxboolean Domain_Is_DPM_Domain(Domain *domain);
FLUENT_EXPORT cxboolean DPM_Domain_Pre(Domain **, cxboolean, cxboolean display_or_report);
FLUENT_EXPORT cxboolean DPM_Domain_Post(Domain **, cxboolean);
FLUENT_EXPORT int Part_DPM_Domain(int, int, int, cxboolean, int, Domain *);
FLUENT_EXPORT void Invalidate_DPM_Domain(void);
FLUENT_EXPORT Domain *Fill_DPM_Domain(Domain *domain);
FLUENT_EXPORT void Remove_Domain(Domain *domain);
FLUENT_EXPORT Domain *DPM_Domain_Destroy(cxboolean relocate_particles);
FLUENT_EXPORT void DPM_Domain_Sync_Alloc(int);
FLUENT_EXPORT void Init_DPM_Steps(Domain *domain);
FLUENT_EXPORT struct migrate_array_t_ **Get_Migrate_Map(const char *, cxboolean,
                                                        const char *);
FLUENT_EXPORT Domain *Get_Global_Domain(const char *);
FLUENT_EXPORT Domain *Get_DPM_Domain(void);
FLUENT_EXPORT Domain *Set_Current_Root_Domain(Domain *);
FLUENT_EXPORT cxboolean Update_Domain_Field(const char *, const char *,
                                            cxboolean, cxboolean, cxboolean);
FLUENT_EXPORT int Get_Global_Domain_Data(const char *, const char *_name, int);
FLUENT_EXPORT int Clear_Global_Domain_Data(void);
FLUENT_EXPORT void Init_DPM_Domain_Counters(void);
FLUENT_EXPORT void Create_All_Exchange_Submaps(int, Svar, int);
FLUENT_EXPORT cxboolean Is_DPM_Domain_Grid_Id_Same_As_Root_Domain(void);
FLUENT_EXPORT cxboolean DPM_Domain_Rebalance_If_Needed(void);
FLUENT_EXPORT int Get_DPM_List(Svar **list, const char *from, cxboolean full_data);
FLUENT_EXPORT void DPM_Balance_Machine_Load(real balance_percent, Domain *domain);
FLUENT_EXPORT cxboolean DPM_Domain_Check_If_Kick_Off(Domain *domain);
FLUENT_EXPORT cxboolean DPM_Domain_Is_In_Use(void);
FLUENT_EXPORT void DPM_Domain_Reset_Is_In_Use(void);
#if RP_NODE
FLUENT_EXPORT void Copy_DPM_Domain_Partition_To_Stored(void);
#endif
#if PARALLEL
FLUENT_EXPORT cxboolean DPM_Domain_Load_Statistics(real imbalance_percent,
                                                   real *imbalance_current,
                                                   cxboolean check_balance,
                                                   Svar var, Domain *domain);
#endif
#endif
