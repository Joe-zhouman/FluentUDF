/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/*
 *  cxsurf.h
 *  Included by CORTEX client-side files.
 */
#ifndef Cxsurf_h
#define Cxsurf_h

#include "cxiface.h"

#define NCELL_GEOM 7

#define X_DIM 0
#define Y_DIM 1
#define Z_DIM 2
#define SCALAR_FLD 3
#define QUADRIC_FLD 4

#define MAX_ISO_VALUES 1000
/*In cortex/cxsurf.h redefined  MAX_NODES_PER_POLY_FACE as CX_MAX_NODES_PER_POLY_FACE = 256. Based
  on RP_POLYHEDRA we need to use either MAX_NODES_PER_POLY_FACE or MAX_NODES_PER_FACE. Further
  RP_POLYHEDRA is not available in cortex and it will be decided based on RP_3D and RP_2D.
  Cortex doesn't know whether Fluent is 3d/2d. Same cortex exe is used for both Fluent 3d and 2d */

#define CX_MAX_NODES_PER_POLY_FACE 256

/*  Surface integral geometry types */
#define SURF_INTEGRATE_3D 1
#define SURF_INTEGRATE_AXI  2
#define SURF_INTEGRATE_2D 3

#define TWOPI 6.283185308

/* Surfaces */
#define SET_EVAL_POINT(val,p)\
{int _i;\
  for( _i=0, val =0.0; _i < (p).nc; _i++)\
     val+=((((p).ip)[_i]).wt*SV_node_value(SV_cell_node_id(&((p).cell),((p).ip)[_i].nid)));}

#define SET_POINT_COORD(c,p,d)\
{int _i;\
  for( _i=0, c =0; _i < (p).nc; _i++)\
     c+=((((p).ip)[_i]).wt*SV_node_coord(SV_cell_node_id(&((p).cell),((p).ip)[_i].nid), d));}


#define SET_FACET_AREA_3D(area,v0,v1,v2)\
   area[0] = 0.5*((v1[1]-v0[1])*(v2[2]-v0[2]) - (v2[1]-v0[1])*(v1[2]-v0[2]));\
   area[1] = 0.5*((v1[2]-v0[2])*(v2[0]-v0[0]) - (v2[2]-v0[2])*(v1[0]-v0[0]));\
   area[2] = 0.5*((v1[0]-v0[0])*(v2[1]-v0[1]) - (v2[0]-v0[0])*(v1[1]-v0[1]))

#define SET_FACET_AREA_2D_AXI(area,v0,v1)\
   if (SV_Is_X_Axis_Symmetry())\
   {\
      area[0] = (v1[1] - v0[1])*(v1[1]+v0[1])/2.;\
      area[1] = (v0[0] - v1[0])*(v1[1]+v0[1])/2.;\
   }\
   else\
   {\
      area[0] = (v1[1] - v0[1])*(v1[0]+v0[0])/2.;\
      area[1] = (v0[0] - v1[0])*(v1[0]+v0[0])/2.;\
   }

#define SET_FACET_AREA_2D(area,v0,v1)\
   area[0] = v1[1] - v0[1];\
   area[1] = v0[0] - v1[0]

/* if the directional avg flag is set, filters the velocity vectors pointing
   to the opposite direction
*/

#define FILTER_DIRECTION(adotv)\
{\
  int avg_dir = Get_Avg_Dir();\
  if (avg_dir)\
     if ((avg_dir*adotv) < 0) adotv = 0;\
}


/* This must be consistent with cxiface.h */
#ifndef CELL_COMPATIBILITY
# define CELL_COMPATIBILITY 1
#endif

#ifdef CELL_COMPATIBILITY
# define COPY_CELL_ID(d,s) memcpy((char *)(d),(char *)(s),sizeof(CX_Cell_Id))
#else
# define COPY_CELL_ID(d,s) *(d)=*(s)
#endif

extern FLUENT_EXPORT int max_nodes_per_cell;
extern FLUENT_EXPORT int dim;


#if CX_NODE
# define EMPTY_SURFACE_WARNING(s) \
   if ((MPT_GISUM1(s->nfl) == 0) && (myid == node_zero))\
        CX_Message("\n Warning: surface-integrate: empty surface")
#endif

#if CX_HOST
# define EMPTY_SURFACE_WARNING(s)
#endif

#if !PARALLEL
#  define EMPTY_SURFACE_WARNING(s) \
    if (s->nfl == 0)\
         CX_Message("\n Warning: surface-integrate: empty surface")
#endif

/*The area of the facet with connectivity with respect to *pts provided by *facet. npts is the number of nodes of the facet */
FLUENT_EXPORT void Surface_Facet_Area(Surf_Point *pts, int *facet, int npts, double area[], cxboolean axisymmetric);
FLUENT_EXPORT void Surface_Zone_Face_Area(void *surfData, CX_Cell_Id *cxcell, double area[]);

FLUENT_EXPORT float Get_Surface_Point_Coord(Surf_Point *spt, int dim);
float Get_Surface_Point_Value(Surf_Point *spt);
float Tri_Facet_Area_3d(float v0[], float v1[], float v2[]);
void Facet_Area_Vector_2d(float v0[], float v1[], float v2[], float vec[]);
float Facet_Area_2d(float v0[], float v1[], float v2[]);
void Facet_Length_Vector_2d(float v0[], float v1[], double vec[]);
float Facet_Length_2d(float v0[], float v1[]);
void Facet_Normal_Vector_2d(float v0[], float v1[], double normal[]);
float Facet_Area_2d_Axi(float v0[], float v1[]);

void CX_Iso_Clip (int d_index, int *s_index, int nsurfs, float min, float max, int type, Quadric *qd);

/* Surface Management Routines */
void CX_Delete_Surface (int index);

void CX_CL_Append_Surface (int index_1, int index_2);

/* Other Surface Routines */
void CX_Cell_Surface (int s_index, int d_index);
void CX_Probe_Surface_Info (int active, int surf_index, int node_index);
void Vertex_Info (int surf_index, int node_index, float *vertex);

void Centroid_Info (int surf_index, int node_index, float *centroid);

void CX_Draw_Surface_Elements (int index);
int Pt_Proj_In_Face(float *, CX_Face_t *);
void CX_Imprint_Surface_Zones(int, int *, int, int);
void CX_Transform_Surface(int *, int, float [4][4], float, int, int);
float *CX_Get_Surface_Node_Tmp(void);
float *CX_Get_Surface_Node_Tmp_S(void);
void CX_Set_Surface_Node_Tmp_Size_S( int size );
void CX_Apply_Quadric_On_Surface (int, Quadric *, float *, float *);



/* Facet_X takes a pointer to the facelist that contains
 * the face descriptor. It sums-up the x co-ordinates
 * of the points in the face. Note that it is not possible
 * to determine the cell on which the face lies without an
 * additional pointer to the cell list of the same surface. */
float Facet_X (Surface *s, int i);
float Facet_Y (Surface *s, int i);
float Facet_Z (Surface *s, int i);

int CX_Surface_Nfacets (int i);

int ray_face (float[], float[], float *, float[][3], float[], float *, int, int, int);

/* Pathlines */
/* Utility routine -- used in pathines. */
void CX_Comp_Inv_Dist_Wts (float *, float [][3], float [], int);

int Calc_Quad_Interp_Vectors ( float v[4][2], float *point, ip_vec ip[4]);

/*void trans_ip (CX_Cell_Id *fc, Surf_Point *p, ip_vec *ipn);*/

/* Turbo machinery */


extern  const int cxfaces_per_cell[NCELL_GEOM];
extern  const int cxfacets_per_cell[NCELL_GEOM];
extern  const int cxnodes_per_cell[NCELL_GEOM];
extern  const int cxnodes_per_face[NCELL_GEOM];
extern  const int cxnodes_per_facet[NCELL_GEOM];

extern int cxFastIso;
void CX_Start_Fast_Iso (void);
void CX_End_Fast_Iso (void);
void CX_Suspend_Fast_Iso (void);
void CX_Activate_Fast_Iso (void);
void CX_Fast_Iso_Surface (int index, float *vals, int nvals, int nt, int *tids);
void checkAndAllocateSurface(int index);

#ifdef __cplusplus
extern "C" {
#endif
void PSV_Host_Finish(const char *, int);
#ifdef __cplusplus
}
#endif

#if (CX_NODE || CX_HOST)
#  if CX_HOST
#    define PCX_START(command_args) \
       {\
         CX_Disable_Interrupts();\
         PRF_Command_Start command_args;
#    define PCX_FINISH() \
         PSV_Host_Finish(__FILE__,__LINE__);\
         CX_Enable_Interrupts();\
       }
#  else       /* CX_NODE */
#    define PCX_START(command_args)
void PSV_Node_Finish(const char *, int); /* defined in lmain.c */
#    define PCX_FINISH() PSV_Node_Finish(__FILE__,__LINE__);
#  endif      /* CX_HOST */
void CX_End_Draw_Pathlines (void);
void CX_End_Draw_Pathlines_Phase (void);
#else       /* Serial Cortex */
#  define PCX_START(command_args)
#  define PCX_FINISH()

#endif        /* CX_HOST || CX_NODE */


/*Parallel Cortex */
#if PARALLEL
#define PCX_BUFF_SIZE 8192
extern  FLUENT_EXPORT int node_zero;
extern  FLUENT_EXPORT int node_one;
extern  FLUENT_EXPORT int node_last;
extern  FLUENT_EXPORT int node_host;
extern  FLUENT_EXPORT int myid;
extern  FLUENT_EXPORT int compute_node_count;
#endif

/************** cxsrfevl.c functions ********************/
/*
double Surface_Area (Surface *s, double depth, int gtype);
double Surface_Integral (Surface *s, double depth, int gtype);
int Surface_Facet_Count (Surface *s);
double Surface_Facet_Sum (Surface *s);
int Surface_Vertex_Count (Surface *s);
double Surface_Vertex_Sum (Surface *s);
double Surface_Flow_Rate (Surface *s, double depth, int gtype);
double Surface_Mass_Flow_Rate (Surface *s, double depth, int gtype);
double Surface_Mass_Average_Num (Surface *s, double depth, int gtype);
double Surface_Mass_Average_Den (Surface *s, double depth, int gtype);
*/
/*
void CX_Surface_Velocity_Vectors (int index, int node_values);
*/


FLUENT_EXPORT int SurfaceIdArg (Pointer x, char *msg);
FLUENT_EXPORT void CX_Surface_Centroids (int nsurf, int axi, float *x, float *y, float *z, float *a, CX_Cell_Id **c);
FLUENT_EXPORT void CX_Surface_Centroid_Normal(int *sids, int count, int axi, float centroid[3], float normal[3]);
FLUENT_EXPORT void CX_Surface_Values (int index, int node_values);
FLUENT_EXPORT void CX_Surface_Get_Min_Max (int sid, int fn, int node_values, int for_integral, float *min, float *max);
FLUENT_EXPORT void CX_Surface_Fill_Node_Tmp (int sid, int fn, float *min, float *max);

FLUENT_EXPORT void CX_Surface_Centroids_And_Cells(int nsurf, int axi,
                                                  float *x, float *y, float *z,
                                                  float *a, CX_Cell_Id **c);



FLUENT_EXPORT void CX_Surface_Write_Values (FILE *fp, int index, int node_values, float xunit[], float vunit[]);
FLUENT_EXPORT double CX_Surface_Integrate (int *, int, double, const char *, int );

FLUENT_EXPORT cxboolean Is_Face_Val_Initialized(Surface *s);
FLUENT_EXPORT cxboolean Is_Face_Rendered(Surface *s);
FLUENT_EXPORT cxboolean Is_Cell_Rendered(Surface *s);

FLUENT_EXPORT void SV_Zone_Surface_Svar_Min(Surface *s, float *min, cxboolean for_integral);
FLUENT_EXPORT void SV_Zone_Surface_Svar_Max(Surface *s, float *max, cxboolean for_integral);

void calc_surface_force_torque (Surface *s, int f, int g, double d, float *c, float *nf, float *nm);
FLUENT_EXPORT int Get_Avg_Dir (void);

void Set_Zero_Dir(float zero[3]);
void Set_Turbo_Axis(float axis[3], float origin[3]);
void CX_Turbo_Surface(int index, int type, Surface *s, float *state);
void CX_Transform_Turbo_Surface(int index, int type, int m_type);
FLUENT_EXPORT void InitializeSurfacePrimitives(void);
void CX_Set_Surface_Node_Tmp_Size(int);
void CX_Add_2D_Cell_To_Surface(CX_Cell_Id *);
void CX_Add_3D_Cell_To_Surface(CX_Cell_Id *);
int Calc_Hex_Interp_Vectors(float v[8][3], float *point, ip_vec ip[8]);
double facet_flux_3D(Surface *s, int i, int nfacet);
double facet_flux_2Daxi(Surface *, int, int);
double facet_flux_2D(Surface *, int, int, double);
void cx_reset_edge_mem(void);
float CX_Eng_Loss_Coef(Pointer idinlet, Pointer idoutlet);


#define begin_surface_facet_loop(surface, facet_index, facet_array_index) {  \
    for (facet_array_index=0,facet_index=0;                                         \
         facet_index < surface->nf;                                                 \
         facet_array_index +=surface->facets[facet_array_index ]+1, facet_index++)  \
    {                                                                               \


#define end_surface_facet_loop() }}
/* if only some cells are going to be solved, skip facets belonging to inactive
 * cell */

#define begin_surface_facet_loop_solved(surface, facet_index, facet_array_index) {  \
    cxboolean need_to_check_solved = SV_Need_To_Check_If_Cell_Solved();             \
    for (facet_array_index=0,facet_index=0;                                         \
         facet_index < surface->nf;                                                 \
         facet_array_index +=surface->facets[facet_array_index ]+1, facet_index++)  \
    {                                                                               \
        if (!need_to_check_solved ||                                                \
            SV_Check_If_Cell_Solved(&surface->cells[facet_index])) {                \

#define end_surface_facet_loop_solved() }}}

/* Mark active points by setting s->points[n].nc to negative value */

#define begin_surface_point_loop_solved(surface, node_index) {                \
    cxboolean need_to_check_solved                                            \
    = SV_Need_To_Check_If_Cell_Solved();                                      \
    if (need_to_check_solved)                                                 \
    {                                                                         \
        int i__, k__;                                                         \
        begin_surface_facet_loop_solved(surface, k__, i__)  {                 \
            int j__;                                                          \
            for (j__ = 0; j__ < surface->facets[i__]; ++j__)   {              \
                int m__ = surface->facets[i__+j__+1];                         \
                if (surface->points[m__].nc > 0)                              \
                    surface->points[m__].nc = -surface->points[m__].nc;       \
            }                                                                 \
        }                                                                     \
        end_surface_facet_loop_solved()                                       \
    }                                                                         \
    for (node_index =0 ; node_index < surface->np;                            \
           ++node_index)     {                                                \
        if (need_to_check_solved) {                                           \
            if (surface->points[node_index].nc > 0)                           \
                continue;                                                     \
            surface->points[node_index].nc =                                  \
                     - surface->points[node_index].nc;                        \
        }                                                                     \
        {

#define end_surface_point_loop_solved()  }}}

/* macros to loop through only facets belonging to rendered cells */

#define begin_surface_facet_loop_rendered(surface, facet_index, facet_array_index) {\
    cxboolean need_to_check_active = SV_Need_To_Check_If_Cell_Active();             \
    for (facet_array_index=0,facet_index=0;                                         \
         facet_index < surface->nf;                                                 \
         facet_array_index +=surface->facets[facet_array_index ]+1, facet_index++)  \
    {                                                                               \
        if (!need_to_check_active ||                                                \
            SV_Check_If_Cell_Active(&surface->cells[facet_index])) {                \

#define end_surface_facet_loop_rendered() }}}

/* Mark active points by setting s->points[n].nc to negative value */

#define begin_surface_point_loop_rendered(surface, node_index) {         \
    cxboolean need_to_check_rendered                                     \
    = SV_Need_To_Check_If_Cell_Active();                                 \
    if (need_to_check_rendered)                                          \
    {                                                                    \
        int i__, k__;                                                    \
        begin_surface_facet_loop_rendered(surface, k__, i__)  {          \
            int j__;                                                     \
            for (j__ = 0; j__ < surface->facets[i__]; ++j__)   {         \
                int m__ = surface->facets[i__+j__+1];                    \
                if (surface->points[m__].nc > 0)                         \
                    surface->points[m__].nc = -surface->points[m__].nc;  \
            }                                                            \
        }                                                                \
        end_surface_facet_loop_rendered()                                \
    }                                                                    \
    for (node_index =0 ; node_index < surface->np;                       \
           ++node_index)     {                                           \
        if (need_to_check_rendered) {                                    \
            if (surface->points[node_index].nc > 0)                      \
                continue;                                                \
            surface->points[node_index].nc =                             \
                     - surface->points[node_index].nc;                   \
        }                                                                \
        {

#define end_surface_point_loop_rendered()  }}}



#endif /* _CXSURF_H */





