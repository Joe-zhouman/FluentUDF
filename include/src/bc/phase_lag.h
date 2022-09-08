/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _PHASE_LAG_H
#define _PHASE_LAG_H

#if RP_PLBC

#define NO_PHASE_LAG_BOUNDARIES(si)\
  (NULLP(SI_T0_PHLAG_OBJP(si)) && NULLP(SI_T1_PHLAG_OBJP(si)))

#define PHASE_LAG_BOUNDARIES_EXIST(si)\
  !NO_PHASE_LAG_BOUNDARIES(si)

#define PHASE_LAG_TO_NO_SOLVE_LIST FALSE
#define PHASE_LAG_THREAD_ON_SOLVE_LIST(t,d) (Count_Phase_Lag_Interfaces(d) > 0 && \
                                 THREAD_TYPE(t) == THREAD_F_SLIDING_BOUNDARY && \
                                 !PHASE_LAG_TO_NO_SOLVE_LIST)

#define THREAD_ORG(t)((t)->tmp1)

#define si_sequence_loop(o,o1,o2,count)\
  for(((o)=(o1),(count)=0);(NULL!=(o));\
      (((o)->next==NULL)&&((count)==0))?((count=1),(o)=(o2)):((o)=(o)->next))

#define si_sb_objp_loop(o,si,n)\
  si_sequence_loop(o,SI_T0_OBJP(si),SI_T1_OBJP(si),n)
#define si_phlag_objp_loop(o,si,n)\
  si_sequence_loop(o,SI_T0_PHLAG_OBJP(si),SI_T1_PHLAG_OBJP(si),n)

enum
{
  FACE_SHARING = 1,
  NODE_SHARING = 2
};

#define INVALID_GHOST_CELL_LAYERS_P  (ghost_cell_layer_count < 1)
#define ONE_GHOST_CELL_LAYER_P       (ghost_cell_layer_count == 1)
#define MULTIPLE_GHOST_CELL_LAYERS_P (ghost_cell_layer_count > 1)
#define FACE_SHARED_MARKING_P        (ghost_cell_layer_type == FACE_SHARING)
#define NODE_SHARED_MARKING_P        (ghost_cell_layer_type == NODE_SHARING)

FLUENT_EXPORT int Count_Phase_Lag_Interfaces (Domain *);
FLUENT_EXPORT void Print_Ghost_Cell_Transformation (Domain *);
FLUENT_EXPORT void Update_Ghost_Storage_From_Phase_Lag_Threads(Domain *);
FLUENT_EXPORT void Create_Phase_Lag_Threads (Domain *);
FLUENT_EXPORT void Create_Phase_Lag_Interface (Domain *, Sliding_interface *);
FLUENT_EXPORT void Delete_Neighbor_Face_Threads_On_Ghost (Domain *, Sliding_interface *);

FLUENT_EXPORT cxboolean PL_Compute_Time_Level_Values(Domain *, cxboolean);
FLUENT_EXPORT void PL_Copy_Ghost_Cell_Scalar(Domain *, Svar);
FLUENT_EXPORT void PL_Copy_Adjacent_Scalar_Gradient(Domain *, Svar);
FLUENT_EXPORT void PL_Copy_Adjacent_Vector_Gradient(Domain *, ND_VEC(Svar, Svar, Svar));
FLUENT_EXPORT void PL_Copy_RG_Qs(Domain *);
FLUENT_EXPORT void PL_Copy_G_Qs(Domain *);
FLUENT_EXPORT void PL_Copy_Cpld_Coeffs(Domain *);
FLUENT_EXPORT void PL_Copy_Scalar_Coeffs(Domain *, int);

#endif  /* RP_PLBC */

#endif  /* _PHASE_LAG_H */
