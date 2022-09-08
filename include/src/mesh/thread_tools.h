/* * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_THREAD_TOOLS_H
#define _FLUENT_THREAD_TOOLS_H

#include "dll.h"
#define MOVE_OFFSET(c,t) C_STORAGE(c,t,SV_COMPACTED_OFFSET,cell_t *)
FLUENT_EXPORT Thread *Make_Thread (Domain *, Thread *, int, int,
                                   cxboolean, cxboolean, cxboolean, cxboolean);
FLUENT_EXPORT void Copy_Face_Thread(Thread *, Thread *, Domain *);
FLUENT_EXPORT Thread *Copy_Cell_Thread (Domain *, Thread *);
FLUENT_EXPORT void Copy_Cell_Threads(Domain *domain, Thread **threads, int n_threads);
FLUENT_EXPORT int Orient_Face_Thread(Domain *, Thread *);
FLUENT_EXPORT void Reverse_Thread_Orientation (Thread *);
FLUENT_EXPORT void Duplicate_Junction_Nodes(Objp *, Domain *);
FLUENT_EXPORT void Uncouple_Adjacent_Face_Threads (Domain *, Objp *);
FLUENT_EXPORT void Uncouple_Face_Threads(Objp *, Domain *);
FLUENT_EXPORT void Uncouple_Periodic_Threads(Domain *, Objp *);
FLUENT_EXPORT void Uncouple_All_Periodic_Threads (Domain *);
FLUENT_EXPORT void Recover_All_Periodic_Threads(Domain *);
FLUENT_EXPORT Thread *Uncouple_Slit_Face_Thread(Domain *, Thread *, Objp *);
FLUENT_EXPORT Thread *Slit_Face_Thread(Domain *, Thread *);
FLUENT_EXPORT int Slit_Two_Sided_Wall(Domain *, Objp *, cxboolean);
FLUENT_EXPORT int Slit_Two_Sided_Wall_Batch(Domain *,Objp *, cxboolean);
FLUENT_EXPORT void Slit_All_Two_Sided_Walls(Domain *, cxboolean, cxboolean);
FLUENT_EXPORT void Slit_All_Two_Sided_Walls_With_Ext_Threads(Domain *, cxboolean);
FLUENT_EXPORT int Slit_Two_Sided_Wall_Parallel(Domain *, Thread *, cxboolean);
FLUENT_EXPORT int Slit_Sliding_Interface_Wall_Parallel(Domain *, Thread *, cxboolean);
FLUENT_EXPORT int Orient_Face_and_Extended_Thread(Domain *, Thread *, cxboolean);
FLUENT_EXPORT void Orient_Face_Thread_List(Domain *, Objp *);
FLUENT_EXPORT int Orient_All_Two_Sided_Walls(Domain *);
FLUENT_EXPORT int Orient_All_Two_Sided_Walls_With_Ext(Domain *);
FLUENT_EXPORT Thread *Slit_Face_Thread_Parallel(Domain *, Thread *);
FLUENT_EXPORT void Check_Interior_Between_Different_Materials(Domain *);
FLUENT_EXPORT Pointer Get_Interior_Between_Solids(Domain *);
FLUENT_EXPORT Pointer Get_Interface_Between_Solids(Domain *);
FLUENT_EXPORT int Get_Major_Thread_Id(Thread *);
FLUENT_EXPORT int Sew_Two_Sided_Wall(Domain *, Objp *);
FLUENT_EXPORT Objp *Sew_All_Two_Sided_Walls(Domain *);
FLUENT_EXPORT int Repair_Duplicate_Shadows(Domain *);
FLUENT_EXPORT int Repair_Coupled_Thread_Orientation(Domain *, Thread *);
FLUENT_EXPORT void Orient_Fan_Zones (Domain *);
FLUENT_EXPORT void Separate_Face_Thread_By_Angle(Domain *, Thread *,
#if !RP_HOST
                                                 real,
#endif
                                                 cxboolean,
                                                 Objp **, cxboolean);
FLUENT_EXPORT void Separate_Face_Thread_By_Face(Domain *, Thread *, cxboolean,
                                                Objp **, cxboolean);
FLUENT_EXPORT void Separate_Face_Thread_By_Mark(Domain *, Thread *, Thread *, unsigned int,
                                                cxboolean, cxboolean,
                                                Objp **, cxboolean, cxboolean);
FLUENT_EXPORT void Separate_Cell_Thread_By_Mark(Domain *, Thread *, unsigned int,
                                                cxboolean, cxboolean,
                                                Objp **, cxboolean);

FLUENT_EXPORT void Separate_Cell_Thread_By_Region(Domain *, Thread *, cxboolean,
                                                  Objp **, cxboolean);

FLUENT_EXPORT int Fuse_Threads(Domain *, Thread *, Thread *, cxboolean, cxboolean);
FLUENT_EXPORT int Check_Fuse_Threads(Domain *, Thread *, Thread *, cxboolean);

FLUENT_EXPORT void Compute_Rotation_Angle (real *, real *, real *,
#if RP_3D
                                           real *,
#endif
                                           real *);
FLUENT_EXPORT cxboolean Find_Face_Pairs(Domain *, Thread *, Thread *, cxboolean,
                                        real *, cxboolean, cxboolean);
FLUENT_EXPORT cxboolean Split_Periodic(Domain *, Thread *);
FLUENT_EXPORT cxboolean Merge_Periodic (Domain *, Thread *, Thread *,
                                        cxboolean, real []);
FLUENT_EXPORT cxboolean Merge_Periodic_pre (Domain *, Thread *, Thread *,
                                        cxboolean, real []);
FLUENT_EXPORT void Merge_Periodic_post (Domain *);
FLUENT_EXPORT void Print_Face_And_Shadow_Nodes (face_t, Thread *);
FLUENT_EXPORT void Repair_Periodic_Node_Order (Domain *, cxboolean);
FLUENT_EXPORT void Repair_Rotational_Periodic(Domain *, Thread *, real);
FLUENT_EXPORT void Repair_Translational_Periodic(Domain *, Thread *);
FLUENT_EXPORT void Repair_Rotational_Periodic_Angles(Domain *, Objp **);
FLUENT_EXPORT void Reset_Periodic_Groups(Domain *);
FLUENT_EXPORT void Destroy_Periodic_Groups(Domain *domain);
FLUENT_EXPORT void exchange_periodic_scalar(Domain *, Svar);
FLUENT_EXPORT void exchange_periodic_vector(Domain *, Svar);
FLUENT_EXPORT void exchange_periodic_tensor(Domain *, Svar, Svar, Svar, Svar, Svar, Svar, int);
FLUENT_EXPORT void update_subthreads(Thread *);
FLUENT_EXPORT void update_subthread_ids(Thread *);
FLUENT_EXPORT void update_thread_nb_pointers(Thread *, Thread *, Thread *);

FLUENT_EXPORT cxboolean Equal_Thread(Thread *, Thread *);
FLUENT_EXPORT cxboolean Equal_Thread_Ignore_Id(Thread *, Thread *);
FLUENT_EXPORT void Merge_Threads(Thread *, Thread *, Domain *);
FLUENT_EXPORT void Merge_Threads_At_Once(Thread **, int, Domain *);
FLUENT_EXPORT void Delete_Cell_Thread(Thread *, Objp *, Domain *);
FLUENT_EXPORT Pointer Deactivate_Cell_Threads(Objp *, Domain *);
FLUENT_EXPORT Pointer Activate_Cell_Threads(Objp *, Domain*
#if RP_NODE
                                            , cxboolean
#endif
                                           );
FLUENT_EXPORT Objp *Add_Thread_To_Olist(Objp *obj, Thread *tf);
FLUENT_EXPORT void Make_Thread_Deactive(Thread *);
FLUENT_EXPORT void Make_Thread_Deactive_2(Thread *);
FLUENT_EXPORT void Make_Thread_Active(Thread *, Thread *, Thread *);
FLUENT_EXPORT void Make_Thread_Active_2(Thread *, Thread *, Thread *);
FLUENT_EXPORT cxboolean create_face_and_shadow_pair(Domain *, Thread *, Thread *);
FLUENT_EXPORT cxboolean create_face_and_shadow_pair_of_face_thread_list(Domain *, Objp *, Objp *);
FLUENT_EXPORT void Activate_Deactivated_Threads(Domain *);
FLUENT_EXPORT void Deactivate_Activated_Threads(Domain *);
FLUENT_EXPORT int Inquire_Periodic_Transform(Domain *, float []);
FLUENT_EXPORT int Inquire_Periodic_Transform_Thread(Thread *, float []);

#if PARALLEL && 0
FLUENT_EXPORT void Clean_Interface(Domain *);
#endif

FLUENT_EXPORT void mark_multi_nodes(Domain *, Thread *, cxboolean);
FLUENT_EXPORT void mark_single_nodes(Domain *, Thread *, cxboolean);
FLUENT_EXPORT void mark_single_and_multi_nodes(Domain *, Thread *);
FLUENT_EXPORT void clear_node_shadow(face_t face, Thread *thread);

FLUENT_EXPORT cxboolean Adopt_Kids(Domain *const, Thread *, Thread * );
#if RP_3D
FLUENT_EXPORT void Extrude_Face_Thread(Domain *, Thread *, int, double *, Objp **);
#endif
#if RP_GEOM
FLUENT_EXPORT void Project_Nodes_To_BgMesh(Domain *);
FLUENT_EXPORT void Update_Thread_Geom_Information(Domain *);
FLUENT_EXPORT void Update_Thread_Geom_Controls(Thread *, Pointer);
#endif

#if PARALLEL
FLUENT_EXPORT cxboolean is_interface_clean(Domain *);
#endif

FLUENT_EXPORT cxboolean Face_Thread_Is_Degenerate (Thread *thread, Domain *domain, int);
FLUENT_EXPORT cxboolean Sliding_Interfaces_Are_Connected (Objp *, Objp *, Domain *);
typedef struct nt_map_struct
{
  Thread *parent;
  Thread *thread;
} NT_Map;

#define NTMAP_PARENT(map,n) ((map)[n]).parent
#define NTMAP_THREAD(map,n) ((map)[n]).thread

/* Multiple periodics groups */
struct multiple_periodics_groups_t_
{
  Objp    **per_exc_grps;
  int       per_exc_grps_cnt;
  cxboolean ang_per_exist_p;
};

FLUENT_EXPORT int Inquire_New_Thread_Map (NT_Map **);
FLUENT_EXPORT void Reset_New_Thread_Map (void);
FLUENT_EXPORT void Duplicate_Single_Connected_Nodes(Domain *, Thread *);

FLUENT_EXPORT cxboolean Mesh_Has_Multiple_Shadow_Nodes_P (Domain *);
FLUENT_EXPORT void Merge_Duplicated_Nodes (Domain *, cxboolean, cxboolean);
#if !RP_HOST
FLUENT_EXPORT void Interpolate_Cell_Data_From_Coupled_Wall (Thread *, Thread *,
                                                            Thread *);
#endif
FLUENT_EXPORT cxboolean Is_Default_Interior_Thread(Thread *);


#if DEBUG
FLUENT_EXPORT void List_Threads_All(Domain *);
#endif

Thread *Copy_Planar_Wall_Thread(Domain *, Thread *, cxboolean);
#endif /* _FLUENT_THREAD_TOOLS_H */
