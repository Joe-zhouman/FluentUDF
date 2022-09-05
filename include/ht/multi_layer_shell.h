/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 * All Rights Reserved
 */

#ifndef _MULTI_LAYER_SHELL_H
#define _MULTI_LAYER_SHELL_H

#include "dll.h"
#if RP_SHELL && RP_3D
FLUENT_EXPORT void ML_Update_Shell_Metrics(Domain *);
FLUENT_EXPORT void ML_Create_Shell_Threads(Domain *d, Thread *tf, real thickness);
FLUENT_EXPORT void ML_Create_all_Shells (Domain *);
FLUENT_EXPORT void ML_Create_Shell_On_Geometry_Thread(Thread *);
FLUENT_EXPORT void ML_Report_Shell_Status (Domain *, int);
FLUENT_EXPORT void Draw_Shell_Junction (Domain *, Objp *);
FLUENT_EXPORT face_t Get_Shell_Cell_Base_Face (cell_t, Thread *, Thread **);
FLUENT_EXPORT face_t Get_Shell_Cell_Cap_Face (cell_t, Thread *, Thread **);
FLUENT_EXPORT face_t Get_Shell_Outer_Face(face_t, Thread *, Thread **);
FLUENT_EXPORT face_t Get_Shell_Layer_Face(face_t, Thread *, int, Thread **);
FLUENT_EXPORT cxboolean ML_Delete_Shell_Zones (Domain *, Objp *, cxboolean, cxboolean);
FLUENT_EXPORT cxboolean ML_Delete_Shell_Zones_IO (Domain *, Objp *, cxboolean);
FLUENT_EXPORT void ML_Scale_Shell_Volume (Thread *, real);
FLUENT_EXPORT void Update_Shell_Temperature_Dynamic_Mesh(Domain *domain);
FLUENT_EXPORT void ML_Update_Shell_Face_Metrics(face_t, Thread *);
FLUENT_EXPORT void ML_Update_Shell_Cell_Metrics(cell_t, Thread *);
FLUENT_EXPORT void Update_Planar_Wall_Node_Coord_N(Domain *);
void Allocate_Uds_Memory_For_Shell(Domain *);
int  Encapsulate_All_Coupled_Wall_Faces(Domain *, cxboolean, cxboolean (*)(Thread *));
void Encapsulate_Coupled_Planar_Walls(Domain *, cxboolean(*)(Thread *));
void Encapsulate_Planar_Wall_Faces(Domain *);
void Laplace_Encapsulation(Domain *, int);
void Set_Max_Nodes_Per_Face_For_Shell(Domain *);
void Set_Max_Shell_Layers(Domain *);
void Update_MLS_Settings(Domain *, Domain *);
cxboolean Internal_Wall_With_Shell_Created(Thread *);
FLUENT_EXPORT cxboolean Case_Has_Shell(Domain *);
FLUENT_EXPORT cxboolean Case_Has_Shell_On_NCI(Domain *);
cxboolean Is_Shell_Model_Created_Thread(Thread *, Pointer);
void Generate_Shell_Junction_Connectivity(Domain *, cxboolean);
cxindex Label_Shell_Faces(Domain *, cxboolean, Thread *, cxboolean);
FLUENT_EXPORT void Encapsulate_Shell_Junctions(Domain *, int);
void Fetch_Shell_Face_Threads(Thread *, Thread **);
#if PARALLEL
FLUENT_EXPORT cxboolean Check_Partition_Interface_Has_Planar_Wall(Domain *);
#endif
# if RP_NODE
FLUENT_EXPORT void Test_Migrate_Shell_Cells (Domain *, Objp *);

FLUENT_EXPORT void Migrate_Shell_Back(Domain *);
FLUENT_EXPORT cxindex Label_Faces_Shell(Domain *, cxboolean, int, cxboolean);
FLUENT_EXPORT cxindex Label_Faces_Shell_New(Domain *, cxboolean, Thread *, cxboolean);
# endif
FLUENT_EXPORT void Model_Initialize_shell(void);
FLUENT_EXPORT cxboolean Update_Shell_Thermal_Data(Thread *, cxboolean);
void Allocate_And_Copy_Shell_Data(Thread *, Thread *);
#endif/*RP_SHELL && RP_3D*/
cxboolean Shell_Between_Parents_P(Thread *, Thread *);
FLUENT_EXPORT Thread *get_next_shell_layer(Thread *);
FLUENT_EXPORT Thread *get_prev_shell_layer(Thread *);
#if RP_SHELL
extern FLUENT_EXPORT int shell_max_nodes_poly_face;
extern FLUENT_EXPORT int case_has_shells;
extern FLUENT_EXPORT int shell_update_storage;
extern FLUENT_EXPORT int  max_junct_faces;
extern FLUENT_EXPORT int max_shell_layers;
#endif

FLUENT_EXPORT cxboolean Shell_Zones_Read(void);
FLUENT_EXPORT cxboolean ML_is_any_ext_planar_wall_p(void);
FLUENT_EXPORT cxboolean Original_Two_Sided_Planar_Wall_P(Thread *);
FLUENT_EXPORT cxboolean Original_One_Sided_Planar_Wall_P(Thread *);
FLUENT_EXPORT void Reset_Original_Planar_Wall(Thread *);
FLUENT_EXPORT void Uncouple_Original_Planar_Wall(Thread *);
FLUENT_EXPORT cxboolean Root_Planar_Wall_P(Thread *);
FLUENT_EXPORT Thread *Get_PlanarSI_Original_Adjacent_Cell_Zone(Thread *);
FLUENT_EXPORT Thread *Get_Shell_Outermost_Wall(Thread *);
FLUENT_EXPORT cxboolean Is_Original_Root_Wall(Thread *);
FLUENT_EXPORT Thread *Get_Outermost_Planar_Wall_By_Walking(Thread *);
FLUENT_EXPORT Thread *Get_Root_Planar_Wall(Thread *);
cxboolean Is_Shell_Shared_Profile_Var(Profile *, Thread *);
FLUENT_EXPORT void Setup_Shell_Zones(Domain *);
/*#if RP_SHELL_NCI*/
FLUENT_EXPORT void Get_Si_Original_Adjacency(Thread *ti, Thread **pf0, Thread **pf1, Thread **tsh);
FLUENT_EXPORT Thread *Get_Sb_Original_Non_Overlap_Thread(Thread *sb);
FLUENT_EXPORT cxboolean Sb_Has_Shell(Thread *sb);
FLUENT_EXPORT void Get_Values_At_Other_Side_Of_Shell(Thread *tf, char *what, Svar nv, real *output);
/* If data has a corresponding Svar , svar index can be specified otherwise
 * set its value to SV_NULL.
 * Optionally, argument 'what' can have one of the following values:
 * - "adjacent-cell-temperature or c0-temperature"
 * - "adjacent-cell-distance"
 * - "c1-temperature"
 * - "face-temperature"
 * - "heat-flux"
 * - "radiative-heat-flux"*/
/* original sliding interface intersected/non-overlapping wall*/
#define SHELL_ROOT_SI_P(t) (SLIDING_INTERFACE_THREAD_P(t) &&\
                            COUPLED_WALL_FACE_THREAD_P(t) &&\
                            SHELL_CELL_THREAD_P(THREAD_T1(t)) && !SHELL_CELL_THREAD_P(THREAD_T0(t)) &&\
                            SHELL_ROOT_LAYER_P(PF1_THREAD(t)) &&\
                            THREAD_TYPE(SHELL_ROOT_LAYER(PF1_THREAD(t))) == THREAD_F_SLIDING_BOUNDARY)
/* original sliding interface intersected wall shadow*/
#define SHELL_OUTERMOST_SI_P(t) (SLIDING_INTERFACE_THREAD_P(t) &&\
                            COUPLED_WALL_FACE_THREAD_P(t) &&\
                            SHELL_CELL_THREAD_P(THREAD_T1(t)) && !SHELL_CELL_THREAD_P(THREAD_T0(t)) &&\
                            !SHELL_ROOT_LAYER_P(PF1_THREAD(t)) &&\
                            THREAD_TYPE(SHELL_ROOT_LAYER(PF1_THREAD(t))) == THREAD_F_SLIDING_BOUNDARY)
#define SHELL_OTO_NCI_P(domain) (Any_One_To_One_Interface(domain) && RP_Get_Boolean("shell/oto-nci?"))
cxboolean Is_Many_To_Many_Interface(Thread *);
/*#endif*/
#if !RP_NODE
int Write_Shell_Thread_Flag_Section(Domain *, FILE *);
#endif
int Read_Shell_Thread_Flags(Domain *, FILE *);
FLUENT_EXPORT void Alloc_Shell_Data_Vars(Domain *);
FLUENT_EXPORT void Free_Shell_Data_Vars(Domain *);
FLUENT_EXPORT void Set_Update_Shell_Data(cxboolean);
FLUENT_EXPORT cxboolean Shell_Data_Svars_Allocated_P(Domain *);
FLUENT_EXPORT cxboolean Update_Shell_Data_P(void);
#if RP_3D && PARALLEL
FLUENT_EXPORT void Register_Shell_HDF_IO_Manager(void);
int Encapsulate_Shell_Junction_Faces(Domain *);
#endif
void Allocate_Rad_Vars_On_Shell_Side_Zones(Domain *);
Thread *Find_ShellCellZone_SB(Thread *);

#define NODE_EDGE_SHELL(v) (NODE_TMP_2 (v).asEdge)
#define SHELL_CREATED_P(t)\
 ((NULLP(THREAD_T1(t)) &&\
   SHELL_CELL_THREAD_P(THREAD_T0(t))) ||\
  (NNULLP(THREAD_T1(t)) &&\
   (SHELL_CELL_THREAD_P(THREAD_T1(t)) || SHELL_CELL_THREAD_P(THREAD_T0(t)))))

#define ML_COPY_OF_ORIGINAL_PLANAR_WALL_P(t) (THREAD_VAR((t)).wall.planar_conduction && SHELL_CELL_THREAD_P(THREAD_T0((t))))

#define SHELL_UPDATE_PROFILE_P(var,thread)\
  (!Is_Shell_Shared_Profile_Var((var),(thread)) ||\
   OUTERMOST_EXT_WALL_P((thread)))

#define PLANAR_CONDUCTION_WALL_P(thread)\
  (THREAD_TYPE((thread)) == THREAD_F_WALL &&\
   THREAD_VAR((thread)).wall.planar_conduction)


/*Note for outermost external wall it'll return FALSE, so
 * care should be taken its not called for outermost wall.
 * Note the check for planar wall is commented below. The
 * reason that during re-reading of case in same session
 * first the thread var is switched off and then the deletion
 * routine is called leading to invalid check.*/
#define PLANAR_WALL_SLITTED_P(tp) (/*THREAD_VAR(tp).wall.planar_conduction &&*/ THREAD_TYPE(tp) == THREAD_F_WALL && SHELL_CREATED_P(tp) && COUPLED_FACE_THREAD_P(tp) && THREAD_T1(tp) == THREAD_T0(THREAD_SHADOW(tp)))
/*#define DX_CAP_FACE(f,t,dx)\
{\
  Thread *tbase;\
  F_AREA(dx,f,t);\
  Get_Shell_Cell_Base_Face(F_C0(f,t), F_C0_THREAD(f,t), &tbase);\
  NV_VS(dx,=,dx,/,NV_MAG(dx));\
  if(!MINOR_FACE_THREAD_P(t))\
  NV_VS(dx,=,dx,*,(THREAD_VAR(tbase).wall.d*-0.5));\
  else\
  NV_VS(dx,=,dx,*,(THREAD_VAR(tbase).wall.d*0.5));\
}

#define DX_BASE_FACE(f,t,dx)\
{\
  F_AREA(dx,f,t);\
  NV_VS(dx,=,dx,/,NV_MAG(dx));\
  NV_VS(dx,=,dx,*,(THREAD_VAR(t).wall.d*0.5));\
}*/

/*face centroid to cell centroid vector if c0 is shell cell thread*/
#define DX0_PLANAR_FACE(f,t,dx)\
{\
  real areaMag = 0.;\
  F_AREA(dx,f,t);\
  areaMag = NV_MAG(dx);\
  if(areaMag > REAL_MIN)\
  {\
    NV_VS(dx,=,dx,/,areaMag);\
    NV_VS(dx,=,dx,*,(SHELL_CELL_THICKNESS(F_C0_THREAD(f,t))*-0.5));\
  }\
}

/*face centroid to cell centroid vector if c1 is shell cell thread*/
#define DX1_PLANAR_FACE(f,t,dx)\
{\
  real areaMag = 0.;\
  F_AREA(dx, f, t); \
  areaMag = NV_MAG(dx);\
  if(areaMag > REAL_MIN)\
  {\
    NV_VS(dx,=,dx,/,areaMag);\
    NV_VS(dx, =, dx, *, (SHELL_CELL_THICKNESS(F_C1_THREAD(f, t)) * 0.5)); \
  }\
}

#define shell_layer_loop(p,init)for((p)=(init);NULL!=(p);(p)=SHELL_THREAD_COPY(p))/*loops all the layers inlcuding the outermost*/
#define shell_layer_loop_not_self(p,init)for((p)=SHELL_THREAD_COPY((init));NULL!=(p);(p)=SHELL_THREAD_COPY(p))/*skips itself*/
#define shell_layer_loop_not_last(p,init)for((p)=(init);!OUTERMOST_WALL_P(p);(p)=SHELL_THREAD_COPY(p))/*loops all the layers excluding the outermost*/
#define PLANAR_COUPLED_WALL_P(t) Original_Two_Sided_Planar_Wall_P((t))/* (THREAD_TYPE(t) == THREAD_F_WALL && COUPLED_FACE_THREAD_P(t) && THREAD_VAR((t)).wall.planar_conduction && !SHELL_CELL_THREAD_P(THREAD_T0(t))) */
#define PLANAR_ONE_SIDED_WALL_P(t) Original_One_Sided_Planar_Wall_P((t))/*(THREAD_TYPE(t) == THREAD_F_WALL && !COUPLED_FACE_THREAD_P(t) && THREAD_VAR((t)).wall.planar_conduction && !SHELL_CELL_THREAD_P(THREAD_T0(t))) */
#define NON_PLANAR_ONE_SIDED_WALL_P(t) (THREAD_TYPE(t) == THREAD_F_WALL && !THREAD_VAR(t).wall.planar_conduction && NULLP((t)->t1))
#define NON_PLANAR_TWO_SIDED_WALL_P(t) (THREAD_TYPE(t) == THREAD_F_WALL && !THREAD_VAR(t).wall.planar_conduction && NNULLP((t)->t1) !SHELL_CELL_THREAD_P((t)->t1))

#define N_SHELL_LAYER(t) (CELL_THREAD_P(t) ? THREAD_VAR(t).cell.nShellLayer : THREAD_VAR(t).wall.nShellLayer)
#define SHELL_ROOT_LAYER(t) ((t))->root_layer
#define SHELL_THREAD_COPY(t) ((t))->copy
#define SHELL_CELL_THICKNESS(t) THREAD_VAR((t)).cell.dShell
#define LAYER_NOS(t) (N_SHELL_LAYER(SHELL_ROOT_LAYER(t)) - N_SHELL_LAYER(t))/*roots' layer no = 0*/
/*do not use LAST_LAYER macros outside shell creation*/
#define LAST_LAYER_P(t) (LAYER_NOS(t) + 1 == N_SHELL_LAYER(SHELL_ROOT_LAYER(t)))
#define LAST_LAYER_INT_WALL_P(t) (LAST_LAYER_P(t) && PLANAR_COUPLED_WALL_P(SHELL_ROOT_LAYER(t)))
#define SINGLE_LAYER_P(t) (N_SHELL_LAYER(SHELL_ROOT_LAYER(t)) == 1)
#define SINGLE_LAYER_INT_WALL_P(t) (SINGLE_LAYER_P(t) && PLANAR_COUPLED_WALL_P(SHELL_ROOT_LAYER(t)))
#define MULTI_LAYER_P(t) (!SINGLE_LAYER_P(t))
#define VALID_SHELL_JUNCTION_THREAD_P(tf,tp) (SHELL_FACE_THREAD_P(tf) && SHELL_ROOT_LAYER(tf) != SHELL_ROOT_LAYER(tp))
#define SAME_ROOT_LAYER_P(t1,t2) (SHELL_ROOT_LAYER(t1) == SHELL_ROOT_LAYER(t2))
#define SHELL_ROOT_LAYER_P(t) (SHELL_ROOT_LAYER(t) == (t))
#define OUTERMOST_WALL_P(t) (/*THREAD_VAR(t).wall.planar_conduction &&*/NNULLP(SHELL_ROOT_LAYER(t)) && (SLIDING_BOUNDARY_THREAD_P(t) ? !SHELL_GEOM_THREAD_P(t) : N_SHELL_LAYER(t) == 0))/*keep the first check commented as sometimes the var is switched off but shell zones are still there.*/
#define OUTERMOST_EXT_WALL_P(t) (OUTERMOST_WALL_P(t) && !COUPLED_FACE_THREAD_P(t))
#define OUTERMOST_INT_WALL_P(t) (OUTERMOST_WALL_P(t) && MAJOR_FACE_THREAD_P(t))
#define SAME_LAYER_P(t1,t2) (N_SHELL_LAYER(t1) == N_SHELL_LAYER(t2))

#define SHELL_EXT_WALL_P(t) (NULLP(THREAD_T1(t)) && !SHELL_FACE_THREAD_P(t) && SHELL_CELL_THREAD_P(THREAD_T0(t))) /* Same as OUTERMOST_EXT_WALL_P but does not depend on layer numbering*/
/*#if RP_SHELL_NCI*/
#define SHELL_GEOM_THREAD_P(t) (NNULLP(t) && THREAD_FLAG_P((t), THREAD_FL_GEOMETRY) /*&& SHELL_CELL_THREAD_P(THREAD_T0(t))*/)
/*#endif*/
#define COUPLED_FACE_THREAD_NOT_MINOR_P(t) (COUPLED_WALL_FACE_THREAD_P((t)) && !MINOR_FACE_THREAD_P((t)))
#define SLIDING_INTERFACE_COUPLED_MAJOR_P(t) (SLIDING_INTERFACE_THREAD_P(t) && COUPLED_FACE_THREAD_NOT_MINOR_P(t))
#define SLIDING_INTERFACE_COUPLED_WALL_P(t) (SLIDING_INTERFACE_THREAD_P(t) && (COUPLED_WALL_FACE_THREAD_P(t) || MAPPED_SLIDING_INTERFACE_WALL_P(t)))
#define SHELL_SI_LEFTOVER_WALL_P(t) (SLIDING_INTERFACE_THREAD_P(t) && NULLP(THREAD_T1(t)) && SHELL_CREATED_P(t))
#define SB_CONVERTED_TO_WALL_P(tf) (!SHELL_CELL_THREAD_P (THREAD_T0(tf)) &&\
                                    (NNULLP(THREAD_T1(tf)) && SHELL_CELL_THREAD_P(THREAD_T1(tf))) &&\
                                    SHELL_ROOT_LAYER_P(tf) &&\
                                    SLIDING_BOUNDARY_THREAD_P(Get_Shell_Outermost_Wall(tf)))
#define SHELL_CAP_CONVERTED_TO_SB_P(tf) (SHELL_CELL_THREAD_P (THREAD_T0(tf)) &&\
                                         NULLP(THREAD_T1(tf)) &&\
                                         SLIDING_BOUNDARY_THREAD_P(tf))

#endif /* _FLUENT_SHELL_CONDUCTION_H*/
