/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_PARA_LOCAL_H
#define _FLUENT_PARA_LOCAL_H

typedef struct para_exchange_t_
{
  Svar list[SV_MAX];
  int used;
  int i;
} para_exchange_t;

#define loop_exch_svars(_nv, _sv)                                   \
  for (para_exchange.i = 0; para_exchange.i < para_exchange.used; ++para_exchange.i) \
    if ((_nv = (Svar)para_exchange.list[para_exchange.i]) != SV_NULL &&       \
        (_sv = sv_master + _nv))

#if 0
#define loop_exch_svars(_nv, _sv)                   \
  for (_nv=SV_MIN,_sv=sv_master; _nv<SV_MAX; ++_nv,++_sv)    \
    if (sv_mesg_flags[_nv])
#endif

#define loop_exch_svars_dim(_nv, _sv, _dim)     \
  loop_exch_svars(_nv, _sv)                     \
       if(_sv->dimension == _dim)

#endif /* _FLUENT_PARA_LOCAL_H */
