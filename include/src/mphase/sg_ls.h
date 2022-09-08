/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/* Level-set model */

extern FLUENT_EXPORT cxboolean sg_lsf;
extern FLUENT_EXPORT cxboolean LSF_Front_Recon_P;
extern FLUENT_EXPORT cxboolean LSF_Front_Area_Compute_P;

extern FLUENT_EXPORT void Domain_LSF_Signed_Distance(Domain *domain, Svar sv_lsf);
extern FLUENT_EXPORT int Create_Tree(Domain *domain);
extern FLUENT_EXPORT void Free_Tree(Domain *domain);
extern FLUENT_EXPORT void Recon_LSF_Front(Domain *phaseDomain);
extern FLUENT_EXPORT void LSF_PreProcessing(Domain *domain);
extern FLUENT_EXPORT void LSF_PostProcessing(Domain *domain);
extern FLUENT_EXPORT real get_surface_distance_scaled(cell_t c, Thread *t);
extern FLUENT_EXPORT void LSF_Surface_Tension(Domain *mdomain, Svar sv_lsf);
extern FLUENT_EXPORT void LSF_Derivatives(Domain *mdomain);

#define C_LSF(c,t)   C_STORAGE_R(c,t,SV_LSF)
#define F_LSF(e,t) C_LSF(e,t)

#define C_LSF_G(c,t)    C_STORAGE_R_NV(c,t,SV_LSF_G)
#define C_LSF_RG(c,t)   C_STORAGE_R_NV(c,t,SV_LSF_RG)
#define C_LSF_M1(c,t)   C_STORAGE_R(c,t,SV_LSF_M1)
#define C_LSF_M2(c,t)   C_STORAGE_R(c,t,SV_LSF_M2)
#define C_LSF_AP(c,t)   C_STORAGE_R(c,t,SV_LSF_AP)
#define C_LSF_S(c,t)    C_STORAGE_R(c,t,SV_LSF_S)
#define C_LSF_M1_0(c,t)   C_STORAGE_R(c,t,SV_LSF_M1_0)

#define LSF_BC_FLUX 0
#define LSF_BC_VALUE 1

/* Use UDS0 as SV_LS temporarily until SV_LS equation established */
/*#define SV_LS SV_UDS_I(0)
#define SV_LS_M1 SV_UDSI_M1(0)
#define SV_LS_M2 SV_UDSI_M2(0)
#define SV_LS_RG SV_UDSI_RG(0)
#define SV_LS_G SV_UDSI_G(0)*/

/* end of temporary */
/*typedef real realGeo;*/

void Model_Initialize_lsf(void);
cxboolean if_lsf(void);
cxboolean if_lsf_on_domain(Domain *d);

#if RP_POLYHEDRA && RP_3D
extern FLUENT_EXPORT cxboolean use_polyhedral;

typedef struct polycell_struct
{
  real (*r_n)[ND_ND];    /* node coordinates */
  real (*farea)[ND_ND];  /* face area vectors */
  real *fxmin;           /* min x of each face */
  real *fxmax;           /* max x of each face */
  real (*edges)[ND_ND];  /* used in find_cut_volume */
  int *faces;               /* face->node connectivity */
  int *face_nnodes;         /* no. of nodes per face */
  int nfaces;               /* no. of faces */
  int nnodes;               /* no. of nodes */
  int max_nodes_per_face;   /* max. no. of nodes in a face of cell */
  int memory_allocated;     /* length of char memory allocated */
} PolyCell;

extern FLUENT_EXPORT void free_polycell(PolyCell *pc);
extern FLUENT_EXPORT real get_surface_distance_scaled_polyhedra(PolyCell *pc, cell_t c, Thread *t);
extern FLUENT_EXPORT void init_polycell(PolyCell *pc);

#endif /* RP_POLYHEDRA && RP_3D */

#define DEBUG_LSF 0
#define LSF_DEBUG_AREA 0

typedef enum /* used in facet area compute via get_intersection_facet in vof_dist.c */
{
  LINE_FACET_2D = 0,
  AXI_FACET_2D = 1,
  POLYGON_FACET_3D = 2
} LSF_Facet_Type;
