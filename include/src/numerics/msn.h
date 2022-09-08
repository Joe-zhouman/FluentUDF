/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef __MSN_HEADER__
#define __MSN_HEADER__

FLUENT_EXPORT void MSN_Create_Local_Nodes(Domain *domain);
FLUENT_EXPORT void MSN_Free_Local_Nodes(Domain *domain);
FLUENT_EXPORT int MSN_Count(Domain *domain);
FLUENT_EXPORT Node *MSN_Get_C_Node_Local(const cell_t c, const Thread *t,
                                         const int n);
FLUENT_EXPORT Node *MSN_Get_F_Node_Local(const face_t f, const Thread *t,
                                         const int n);
FLUENT_EXPORT Node *MSN_Get_FSP_Node_Local(const Face *, const int);
FLUENT_EXPORT void MSN_Init_Node_Value(Domain *domain, Svar nv, real value);
FLUENT_EXPORT void MSN_Check(Domain *domain, int verbosity);
FLUENT_EXPORT void MSN_Set_Node_Mark(Domain *domain, int which);
FLUENT_EXPORT void MSN_Print_Svar(Domain *domain, Svar sv);
FLUENT_EXPORT void MSN_Update_Coord(Domain *domain);
FLUENT_EXPORT void MSN_Update_Coord_M1(Domain *domain);
FLUENT_EXPORT void MSN_Remove_Local_Nodes_From_Interface_and_Corner(Domain *domain);
FLUENT_EXPORT void MSN_Add_Local_Nodes_to_Interface_and_Corner(Domain *domain);
FLUENT_EXPORT void MSN_Remove_Local_Nodes_From_Interface_and_Corner_If_Exists(Domain *domain);
FLUENT_EXPORT void MSN_Recover_Local_Nodes_In_Interface_and_Corner_If_Needed(Domain *domain);
FLUENT_EXPORT void MSN_Free_Local_Nodes_If_Needed(Domain *domain);
FLUENT_EXPORT void MSN_Recover_Local_Nodes_If_Needed(Domain *domain);
FLUENT_EXPORT cxboolean MSN_Have_Local_Nodes(Domain *domain, cxboolean with_host);

#define C_NODE_LOCAL(c, t, n) ((!DOMAIN_MSN_HAS_MSN_P((ROOT_DOMAIN_P(t->domain)?t->domain:DOMAIN_SUPER_DOMAIN(t->domain))) || \
                                !NODE_MSN(C_NODE(c, t, n)))? C_NODE(c, t, n): \
                               MSN_Get_C_Node_Local(c, t, n))

#define F_NODE_LOCAL(f, t, n) ((!DOMAIN_MSN_HAS_MSN_P((ROOT_DOMAIN_P(t->domain)?t->domain:DOMAIN_SUPER_DOMAIN(t->domain)))|| \
                                !NODE_MSN(F_NODE(f, t, n)))? F_NODE(f, t, n):  \
                               MSN_Get_F_Node_Local(f, t, n))

#define FSP_NODE_LOCAL(_fsp, _n) ((!DOMAIN_MSN_HAS_MSN_P((ROOT_DOMAIN_P(_fsp->thread->domain)?_fsp->thread->domain:DOMAIN_SUPER_DOMAIN(fsp->thread->domain)))|| \
                                   !NODE_MSN (FSP_NODE (_fsp, _n))) ? FSP_NODE (_fsp, _n) : \
                                  MSN_Get_FSP_Node_Local (_fsp, _n))

#define F_NODE_LOCAL_SHADOW(f, t, n)                                    \
  ((!SV_ALLOCATED_P(t,SV_SHADOW) || NULL_FACE_P(F_SHADOW(f,t))) ?       \
   NULL : F_NODE_LOCAL(F_SHADOW(f,t), THREAD_SHADOW(t),F_NNODES(f,t)-(n)-1))

/* for multiple shadow nodes, the node shadow from cell will be itself */
#define C_NODE_LOCAL_SHADOW(c, t, n) ((!DOMAIN_MSN_HAS_MSN_P((ROOT_DOMAIN_P(t->domain)?t->domain:DOMAIN_SUPER_DOMAIN(t->domain)))||                    \
                                       !NODE_MSN(C_NODE(c, t, n)))?     \
                                      NODE_SHADOW(C_NODE(c, t, n)):     \
                                      MSN_Get_C_Node_Local(c, t, n))
#endif
