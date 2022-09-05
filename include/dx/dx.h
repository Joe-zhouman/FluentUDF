/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DX_H
#define _FLUENT_DX_H

#include "dll.h"
#include "sg_mphase.h"
#include "seem2c.h"
#include "bsp.h"
#if SEEM
#define DISK_WRITE_ERROR(str)  { \
      Message("%s writing failed",str); \
      Error("Either the disk is full or you don't have the write permission\n");\
      }
FLUENT_EXPORT real distance(int i, BSP_Real re[]);
FLUENT_EXPORT void free_fem_interpolation_variables(void);
extern FLUENT_EXPORT real htc_reference_temperature;
#if VKI_LIB
extern FLUENT_EXPORT cxboolean merge_shadow;
extern FLUENT_EXPORT cxboolean domain_export;
#endif
# if !RP_NODE
FLUENT_EXPORT int stamp_fvuns_file (const char *, unsigned char [4]);
#endif
FLUENT_EXPORT real face_heat_xfer_coef(face_t f, Thread *t);
/*** Marks nodes while going through begin_node_loop macro ***/
FLUENT_EXPORT int Mark_Nodes(Domain *);
FLUENT_EXPORT void Calculate_Face_Force(Thread *thread);
/* Fill Face forces for all these surfaces */
FLUENT_EXPORT void Fill_Face_Forces(Domain *, Pointer);
/*** Marks all the nodes including UNUSED_NODE through begin_node_loop macro ***/
FLUENT_EXPORT int Mark_Nodes_All(Domain *);
/*** Marks nodes while going through begin_node_loop macro and for ***/
/*** shadow nodes don't count the nodes twice ***/
FLUENT_EXPORT int Mark_Nodes_No_Shadow(Domain *);
/*** Marks nodes while going through all the cell threads ***/
FLUENT_EXPORT int Mark_Nodes_Via_Cell(Domain *);
FLUENT_EXPORT int Mark_Nodes_Via_Cell_int(Domain *);
/*** Marks nodes while going through all the face threads ***/
FLUENT_EXPORT int Mark_Nodes_Via_Face(Domain *, cxboolean );
/*** Marks only solid nodes through cell threads ***/
FLUENT_EXPORT int Mark_Solid_Nodes(Domain *);
FLUENT_EXPORT int Mark_Interpolated_Nodes(Domain *, Pointer);
/*** Mark Nodes on a particular cell thread only ***/
FLUENT_EXPORT int Mark_Nodes_Cell_Threads(Domain *domain, Thread *thread);
/*** Mark Nodes on a particular face thread only ***/
FLUENT_EXPORT int Mark_Nodes_Face_Threads(Domain *, Thread *[], cxboolean [], int);
FLUENT_EXPORT extern const unsigned char ildata[320];
FLUENT_EXPORT void Convert_Lowercase_Print_Names(char *);
FLUENT_EXPORT void Interpolate_FEM_Surface(Pointer, Pointer, Domain *, const char *);
FLUENT_EXPORT int Write_FEM_Node_Based_Data(FILE *, Domain *, Pointer, void (*)(FILE *, Node *, int nnode, int thread_id));
FLUENT_EXPORT int Write_FEM_Face_Based_Data(FILE *, Domain *, Pointer, void (*)(FILE *, Thread *, face_t, int ));
#if !PARALLEL
FLUENT_EXPORT int Mark_Nodes_On_Marked_Cells(Domain *domain, unsigned int bit);
FLUENT_EXPORT int Marked_Nodes_On_Thread(Domain *domain, Thread *thread);
#endif

#define SHADOW  -1
#define INVALID_NODE_P(n) (UNUSED_NODE_P(n)||(NODE_ID(n)==SHADOW))
#define LENGTH_FACE(ft) (ft->nelements)
#define NODE_AVERAGE_VALUE(n) (NNULLP(NODE_SHADOW(n))? (NODE_VALUE(n)+\
                               NODE_VALUE(NODE_SHADOW(n)))/2: NODE_VALUE(n))
#define EXPORT_THREAD_NAME(buf,thread,names) { int i_; \
                                       strncpy(buf,Thread_Name(THREAD_ID(thread),names),sizeof(buf)-1);\
                                       buf[sizeof(buf)-1] = '\0';\
                                       for(i_=0; buf[i_]!='\0'; i_++)\
                                         if((buf[i_] == ':') ||(buf[i_] =='.'))\
                                          buf[i_] = '-';\
                                       }
#define EXPORT_SURFACE_NAME(buf,surf_index,names) { int i_; \
                                       strncpy(buf,Surface_Name(surf_index,names),sizeof(buf)-1);\
                                       buf[sizeof(buf)-1] = '\0';\
                                       for(i_=0; buf[i_]!='\0'; i_++)\
                                         if((buf[i_] == ':') ||(buf[i_] =='.'))\
                                          buf[i_] = '-';\
                                       }
#define begin_surface_loop(surf,index,surfaces) {Pointer sp; \
                                            for(sp=surfaces; PAIRP(sp); sp=CDR(sp)) \
                                            { index = surface_id_arg(CAR(sp), "invalid surface"); \
                                              surf = SurfaceList +  index;
#define end_surface_loop(surf,index,surfaces) }}
#define FIND_CLOSEST_ITEM(i,f_min,t_min,d_min,face,fem_thread) int i; \
                                                  face_t  f_min = -1; \
                                                Thread* t_min = NULL; \
                                                real    d_min = 1e10; \
                                                      real re[ND_ND]; \
                                                      NV_S(re, =, 0); \
                                Update_Face_Metrics(face,fem_thread); \
                                    F_CENTROID(re, face, fem_thread); \
                             i = BSP_closestItem(root, re, distance); \
                                            f_min = store_fat_t[i].f; \
                                            t_min = store_fat_t[i].t; \
                                             d_min = distance(i, re);
FLUENT_EXPORT char *Thread_Name(int, Pointer );
FLUENT_EXPORT int abaqus_face_number(face_t, Thread *, cell_t, Thread *);
FLUENT_EXPORT int Surface_Nnodes_Solid(Pointer );
FLUENT_EXPORT char *Surface_Name(int, Pointer);
FLUENT_EXPORT int Surface_Nnodes( Pointer );
FLUENT_EXPORT int Surface_Nfacets( Pointer );
extern FLUENT_EXPORT BSP_Tree *root;
FLUENT_EXPORT void Surface_Point( Surf_Point *, real *);
FLUENT_EXPORT real Surface_Value( Surf_Point * );
FLUENT_EXPORT real SurfaceFacet_Value(Surface *, int );
FLUENT_EXPORT double SurfFacet_MassFlux(Surface *s, int, int, double );
FLUENT_EXPORT double SurfFacet_HeatFlux(Surface *s, int nfacet, int npoints, double depth);
FLUENT_EXPORT real Surface_Value_Shadow( Surf_Point *, Thread *);
FLUENT_EXPORT void Surface_Force( Surf_Point *, real *);
FLUENT_EXPORT void Surface_Force_Shadow( Surf_Point *, real *, Thread *);
FLUENT_EXPORT Node *Zone_Surface_Node(Surf_Point *);
FLUENT_EXPORT cxboolean Heat_Flux_Available(void);
FLUENT_EXPORT cxboolean if_periodic(Domain *);
FLUENT_EXPORT cxboolean if_cell_t_rot_periodic(Domain *, Thread *, real *);
FLUENT_EXPORT int round_of(real);
extern FLUENT_EXPORT cxboolean fem_map;
extern FLUENT_EXPORT fat_t *store_fat_t_interp;
extern FLUENT_EXPORT fat_t *store_fat_t;
FLUENT_EXPORT int local_count_c_pointer(Domain *, Pointer);
FLUENT_EXPORT int global_count_c_pointer(Domain *, cxboolean, Pointer);
FLUENT_EXPORT int Store_Node_Velocity(Domain *, cxboolean, float **, int);

FLUENT_EXPORT real Face_Heat_Flux(face_t f, Thread *t);
FLUENT_EXPORT real Face_Temp(face_t f, Thread *t);
FLUENT_EXPORT Thread *Get_Phase_Thread(Thread *, int);
#if !RP_HOST
FLUENT_EXPORT real Face_Integrated_Heat_Flux(face_t f, Thread *t);
FLUENT_EXPORT real Face_Radiative_Flux(face_t f, Thread *t);
FLUENT_EXPORT real Face_Flow_Rate(face_t f, Thread *t);
FLUENT_EXPORT real Face_Yplus(face_t f, Thread *t);
FLUENT_EXPORT real Face_U(face_t f, Thread *t);
FLUENT_EXPORT real Face_V(face_t f, Thread *t);
FLUENT_EXPORT real Face_W(face_t f, Thread *t);
FLUENT_EXPORT real Face_UDMI(face_t f, Thread *t, int i );
FLUENT_EXPORT real Face_Pressure(face_t f, Thread *t);
FLUENT_EXPORT real Face_Temperature_EM_Surface_source(face_t f, Thread *t);
FLUENT_EXPORT real Face_uds_0_scalar(face_t f, Thread *t);
#endif /* !RP_HOST */

FLUENT_EXPORT int Interpolate_Node_Forces(Domain *, Pointer, real **);
#if !PARALLEL
#if 0
FLUENT_EXPORT static void Wall_Face_Forces(Thread *, real *);
FLUENT_EXPORT static int Wall_Node_Forces(Domain *, real **);
#endif
FLUENT_EXPORT int Surface_Node_Forces(Domain *, Pointer, real **);
#endif
FLUENT_EXPORT int Store_Temp_Scalars(Domain *, Pointer, Pointer, real **tf);
FLUENT_EXPORT void Node_Function_Values(Domain *, const char *);
FLUENT_EXPORT void Cell_Center_Values(Domain *, const char *);
FLUENT_EXPORT void Cell_Function_Values_Rom(Domain *, const char *);
FLUENT_EXPORT void Face_Function_Thread_Values(Thread *, Domain *, const char *);

FLUENT_EXPORT void Export_Data(Domain *, Pointer, Pointer, FILE *, int, const char *, Pointer, Pointer, int, int, int);
FLUENT_EXPORT void Map_Data_To_FEM(Domain *, Pointer, Pointer, FILE *, int, char *, Pointer, Pointer, int, int, int);

FLUENT_EXPORT void Export_APECS_Data(Domain *, Pointer, FILE *, Pointer);
FLUENT_EXPORT int Get_Number_Of_Extra_Nodes(Pointer);
FLUENT_EXPORT void Reset_Element_Global_IDs(Domain *, cxboolean);
FLUENT_EXPORT cxboolean Polygonal_Wall_P(Domain *domain);
FLUENT_EXPORT cxboolean Is_Face_Value_Initialized(Surface *s);

#if RP_NODE
FLUENT_EXPORT void Mark_Domain_Nodes_In_Parallel(Domain *);
#endif
/* for icem cfd export*/

#endif /* SEEM */

#endif /* _FLUENT_DX_H */
