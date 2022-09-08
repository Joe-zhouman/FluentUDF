/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_RP_MEM_H
#define _FLUENT_RP_MEM_H

#include "dll.h"

enum
{
  W_R = 0,
  ND_VEC(W_U, W_V, W_W),
  W_E
};
#if RP_2D
extern FLUENT_EXPORT int W_W;
#endif

#define SV_EQN_W(sv) ((sv))
#define SV_EQN_WO(sv)((Svar)((sv)+SV_P_WO-SV_P))
#define SV_EQN_FW(sv)((Svar)((sv)+SV_P_FW-SV_P))
#define SV_EQN_DW(sv)((Svar)((sv)+SV_P_DW-SV_P))
#define SV_EQN_WV(sv)((Svar)((sv)+SV_P_WV-SV_P))
#define SV_EQN_WN(sv)((Svar)((sv)+SV_P_WN-SV_P))
#define SV_EQN_G(sv) ((Svar)((sv)+SV_P_G -SV_P))
#define SV_EQN_RG(sv)((Svar)((sv)+SV_P_RG-SV_P))
#define SV_EQN_M1(sv)((Svar)((sv)+SV_P_M1-SV_P))
#define SV_EQN_M2(sv)((Svar)((sv)+SV_P_M2-SV_P))
#define SV_EQN_AP(sv)((Svar)((sv)+SV_P_AP-SV_P))
#define SV_EQN_S(sv) ((Svar)((sv)+SV_P_S -SV_P))
#define SV_EQN_R(sv) ((Svar)((sv)+SV_P_R -SV_P))

#define T_EQN_W(t,sv) T_STORAGE_R(t,SV_EQN_W(sv))
#define T_EQN_WO(t,sv)T_STORAGE_R(t,SV_EQN_WO(sv))
#define T_EQN_FW(t,sv)T_STORAGE_R(t,SV_EQN_FW(sv))
#define T_EQN_DW(t,sv)T_STORAGE_R(t,SV_EQN_DW(sv))
#define T_EQN_WV(t,sv)T_STORAGE_R(t,SV_EQN_WV(sv))
#define T_EQN_WN(t,sv)T_STORAGE_R(t,SV_EQN_WN(sv))
#define T_EQN_R(t,sv) T_STORAGE_R(t,SV_EQN_R(sv))
#define T_EQN_G(t,sv) T_STORAGE_R_NV(t,SV_EQN_G(sv))
#define T_EQN_RG(t,sv)T_STORAGE_R_NV(t,SV_EQN_RG(sv))
#define T_EQN_M1(t,sv)T_STORAGE_R(t,SV_EQN_M1(sv))
#define T_EQN_M2(t,sv)T_STORAGE_R(t,SV_EQN_M2(sv))

#define C_EQN_W(c,t,sv) (T_EQN_W (t,sv)[c])
#define C_EQN_WO(c,t,sv)(T_EQN_WO(t,sv)[c])
#define C_EQN_FW(c,t,sv)(T_EQN_FW(t,sv)[c])
#define C_EQN_DW(c,t,sv)(T_EQN_DW(t,sv)[c])
#define C_EQN_WV(c,t,sv)(T_EQN_WV(t,sv)[c])
#define C_EQN_WN(c,t,sv)(T_EQN_WN(t,sv)[c])
#define C_EQN_R(c,t,sv)(T_EQN_R(t,sv)[c])
#define C_EQN_G(c,t,sv) (T_EQN_G (t,sv)[c])
#define C_EQN_RG(c,t,sv)(T_EQN_RG(t,sv)[c])
#define C_EQN_M1(c,t,sv)(T_EQN_M1(t,sv)[c])
#define C_EQN_M2(c,t,sv)(T_EQN_M2(t,sv)[c])

/* mapping from eqn index to AMG eqn index, for single phase PBCS only */
#define AMG_EQN_INDEX(__eqn)((__eqn == EQ_CONTINUITY) ? W_R : __eqn - 1)

#define C_P_WN(c,t)C_EQN_WN(c,t,SV_P)
#define C_U_WN(c,t)C_EQN_WN(c,t,SV_U)
#define C_V_WN(c,t)C_EQN_WN(c,t,SV_V)
#define C_W_WN(c,t)C_EQN_WN(c,t,SV_W)
#define C_T_WN(c,t)C_EQN_WN(c,t,SV_T)
#define C_YI_WN(c,t,i)C_STORAGE_R_XV(c,t,SV_Y_WN,i)

#define C_sv_(c,t,sv,dx)(C_STORAGE_R(c,t,sv)+NV_DOT(C_STORAGE_R_NV(c,t,(sv)+SV_P_RG-SV_P),dx))
#define C_sv_yi_xv_(c,t,sv,i,dx)(C_STORAGE_R_XV(c,t,sv,i)+NV_DOT(C_STORAGE_R_NV_XV(c,t,SV_Y_RG,i),dx))

#define C_P_(c,t,dx)C_sv_(c,t,SV_P,dx)
#define C_U_(c,t,dx)C_sv_(c,t,SV_U,dx)
#define C_V_(c,t,dx)C_sv_(c,t,SV_V,dx)
#define C_W_(c,t,dx)C_sv_(c,t,SV_W,dx)
#define C_T_(c,t,dx)C_sv_(c,t,SV_T,dx)
#define C_YI_(c,t,i,dx)C_sv_yi_xv_(c,t,SV_Y,i,dx)

#define C_R_(c,t,dx)(C_R(c,t)+NV_DOT(C_STORAGE_R_NV(c,t,SV_DENSITY_RG),dx))
#define C_H_(c,t,dx)(C_H(c,t)+NV_DOT(C_STORAGE_R_NV(c,t,SV_H_RG),dx))

#define C_EQN_W_(c,t,sv,dx)(C_EQN_W(c,t,sv)+NV_DOT(C_EQN_RG(c,t,sv),dx))

#define C_DT(c,t)C_STORAGE_R(c,t,SV_DT)
#define C_DT_SCALE(c,t)C_STORAGE_R(c,t,SV_DT_SCALE)
#define C_UREF2(c,t)C_STORAGE_R(c,t,SV_UREF2)
#define C_DISCONT(c,t)C_STORAGE_R(c,t,SV_DISCONT)
#define C_NORMAL_MACH(c,t)C_STORAGE_R(c,t,SV_NORMAL_MACH)

#define C_TWOTT(c,t)C_STORAGE_R(c,t,SV_TWOTT)
#define C_TWOTE(c,t)C_STORAGE_R(c,t,SV_TWOTE)
#define C_TWOTE_(c,t,dx)(SV_ALLOCATED_P(t,SV_TWOTE_RG) ? C_sv_(c,t,SV_TWOTE,dx) : C_TWOTE(c,t))

#define C_E(c,t)(C_H(c,t) - ABS_P(C_P(c,t),op_pres)/C_R(c,t) + C_VMAG2(c,t)/2.)
#define C_HHI(c,t,i,n)(T_STORAGE(t,SV_SPE_ENTHALPY,real *)[(c)*(n)+(i)])

#define C_SPE_JACOBIAN(c,t,i,j,nspe)(T_STORAGE(t,SV_SPE_JACOBIAN,real *)[(c)*(nspe)*(nspe-1) + (i)*(nspe)+(j)])

/* In the following loops, <eqn> runs from 0 to THREAD_N_EQNS,
 * while <sv> runs through the corresponding Svars. */

#define bounded_eqn_loop(eqn0,eqn1,eqn,sv,t)for(sv=THREAD_EQN_INDEX(t,eqn=eqn0);eqn<eqn1;sv=THREAD_EQN_INDEX(t,++eqn))
#define eqn_loop(eqn,sv,t)bounded_eqn_loop(0,THREAD_N_EQNS(t),eqn,sv,t)
#define scalar_eqn_loop(eqn,sv,t)bounded_eqn_loop(THREAD_N_PVT_EQNS(t),THREAD_N_EQNS(t),eqn,sv,t)
#define spe_eqn_loop(eqn,sv,t)bounded_eqn_loop(THREAD_N_FLOW_EQNS(t),THREAD_N_EQNS(t),eqn,sv,t)

/*
 Note 1:
 ------
   Please note that I have modified this macro, because previous version of this has following issues:
   i)  CR 73778
   ii) For the cases where we have solid + fluid region both & if "thread_loop_c" starts with the solid
       thread as first_solve_thread then, this loop will only populate the SV_T gradient & will not
       populate the other scalar gradient which are solved in coupled manner, like SV_P ...etc.

 Note 2:
 ------
   Please make sure follwing while using this macro:
   This macro take care for the cases where we have
   i)  Only Fluid Zone
   ii) Fluid & Solid Zone both

   But it don't take care of the cases where we have only Solid Zone, so one need to put an "else" statement
   to handle them. For example:

   begin_domain_eqn_loop(eqn,sv,domain)
   {
      //this is a very important statement we have to use this
      //always to prevent the parallel issue found in CR 73778
      sv = PRF_GIHIGH(sv);
      Repain_Gradient(domain,sv,SV_EQN_RG(sv));
   }
   else
      Repain_Gradient(domain,SV_T,SV_EQN_RG(SV_T));
   end_domain_eqn_loop(eqn,sv,domain);
*/
#define  begin_domain_eqn_loop(eqn,sv,d)                                                                \
{                                                                                                       \
  int _domain_nr_equations=0;                                                                           \
  Thread* _first_solve_thread=NULL, *_thread;                                                           \
    cxboolean has_fluid = FALSE;                                                                        \
  thread_loop_c(_thread,d)                                                                              \
    {                                                                                                   \
      _domain_nr_equations=THREAD_N_EQNS(_thread);                                                      \
      _domain_nr_equations=PRF_GIHIGH1(_domain_nr_equations);                                           \
      if((_domain_nr_equations!=0)&& FLUID_THREAD_P(_thread)){                                                                      \
        _first_solve_thread=_thread;                                                                    \
        has_fluid = TRUE;                                                                               \
        break;                                                                                          \
      }                                                                                                 \
    }                                                                                                   \
    if(PRF_ANYONE(has_fluid,FALSE))                                                                     \
      bounded_eqn_loop(0,_domain_nr_equations,eqn,sv,_first_solve_thread)

#define  end_domain_eqn_loop(eqn,sv,d) }




#include "rp_agglom.h"

#endif /* _FLUENT_RP_MEM_H */
