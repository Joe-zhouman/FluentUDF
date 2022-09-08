/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SHELL_CONDUCTION_H
#define _FLUENT_SHELL_CONDUCTION_H

#include "dll.h"
#if RP_SHELL && RP_3D
FLUENT_EXPORT void Update_Shell_Metrics(Domain *);
FLUENT_EXPORT void Create_Shell_Threads(Domain *d, Thread *tf, real thickness);
FLUENT_EXPORT void Create_Shell_Threads_Parallel(Domain *d, Thread *tf, real thickness);
FLUENT_EXPORT void Create_all_Shells (Domain *);
FLUENT_EXPORT cxboolean Disable_all_Shells (Domain *);
FLUENT_EXPORT void Delete_all_Shells (Domain *);
FLUENT_EXPORT void Free_Shell_Threads(Domain *);
FLUENT_EXPORT void Report_Shell_Status (Domain *, int);
FLUENT_EXPORT face_t get_shell_major_face (cell_t, Thread *, Thread **);
FLUENT_EXPORT void Delete_Shell_Thread (Domain *, Thread *);
FLUENT_EXPORT void Scale_Shell_Volume (Thread *, real);
FLUENT_EXPORT void Update_Shell_Temperature_Dynamic_Mesh(Domain *domain);
FLUENT_EXPORT void Update_Shell_Face_Metrics(face_t, Thread *);
FLUENT_EXPORT void Update_Shell_Cell_Metrics(cell_t, Thread *);
void Get_Dx_One_Sided(real NV_VEC(dx), const real wall_thick);
void Get_Dx_Two_Sided(const face_t f, Thread *PTR_RESTRICT t, const cell_t c0, const real f_cent[ND_ND], const real wall_thick, real dx[ND_ND]);
# if RP_NODE
FLUENT_EXPORT void Migrate_Shell_Back(Domain *);
FLUENT_EXPORT cxindex Label_Faces_Shell(Domain *d, cxboolean with_host, int tid, cxboolean do_exterior_faces);
# endif
#define COPY_OF_ORIGINAL_PLANAR_WALL_P(t) (THREAD_VAR((t)).wall.planar_conduction && COUPLED_FACE_THREAD_P((t)) && NULLP(THREAD_T1((t))) && SHELL_CELL_THREAD_P(THREAD_T0((t))))
#endif/*RP_SHELL && RP_3D*/
#if RP_SHELL
FLUENT_EXPORT int Grid_Check_Partition_Shell (
# if !RP_HOST
  Domain *
# else
  void
# endif
);

extern FLUENT_EXPORT int shell_max_nodes_poly_face;
extern FLUENT_EXPORT int case_has_shells;
extern FLUENT_EXPORT int shell_update_storage;
#endif
FLUENT_EXPORT cxboolean if_one_sided_planar_wall_and_shell_created_p(Thread *);
FLUENT_EXPORT cxboolean is_any_ext_planar_wall_p(void);
#define S2S_COUPLED_WALL_P(t) (THREAD_TYPE((t)) == THREAD_F_WALL && COUPLED_FACE_THREAD_P((t)) && !THREAD_VAR((t)).wall.planar_conduction && S2S_BOUNDARY_THREAD_P((t)))
#endif /* _FLUENT_SHELL_CONDUCTION_H*/
