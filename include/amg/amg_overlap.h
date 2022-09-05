
/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_AMG_OVERLAP_H
#define _FLUENT_AMG_OVERLAP_H

#if 1

#define amg_loop_interface(_f, _n, _i)                                  \
  for (_n = 0; _n < _f->n_sets; ++_n)                                   \
    for (_i = _f->set_interface_start[_n]; _i < _f->set[_n + 1]; ++_i)

#define amg_loop_interior(_f, _n, _i)                                   \
  for (_n = 0; _n < _f->n_sets; ++_n)                                   \
    for (_i = _f->set[_n]; _i < _f->set_interface_start[_n]; ++_i)

#define amg_loop_interface_reverse(_f, _n, _i)                          \
  for (_n = 0; _n < _f->n_sets; ++_n)                                   \
    for (_i = _f->set[_n + 1]-1; _i >=_f->set_interface_start[_n] ; --_i)

#define amg_loop_interior_reverse(_f, _n, _i)                           \
  for (_n = 0; _n < _f->n_sets; ++_n)                                   \
    for (_i = _f->set_interface_start[_n]-1; _i >=_f->set[_n] ; --_i)

#else

#define amg_loop_interface(_f, _n, _i)                                  \
  for (_n = 0; _n < _f->n_sets; ++_n)                                   \
    for (_i = _f->set[_n]; _i < _f->set_interior_start[_n]; ++_i)

#define amg_loop_interior(_f, _n, _i)                                   \
  for (_n = 0; _n < _f->n_sets; ++_n)                                   \
    for (_i = _f->set_interior_start[_n]; _i < _f->set[_n + 1]; ++_i)

#define amg_loop_interface_reverse(_f, _n, _i)                          \
  for (_n = 0; _n < _f->n_sets; ++_n)                                   \
    for (_i = _f->set_interior_start[_n]-1; _i >=_f->set[_n] ; --_i)

#define amg_loop_interior_reverse(_f, _n, _i)                           \
  for (_n = 0; _n < _f->n_sets; ++_n)                                   \
    for (_i = _f->set[_n + 1]-1; _i >=_f->set_interior_start[_n] ; --_i)

#endif

extern void amg_ensure_overlap_layers(Level *f, Level *c, int *tmp);

#endif /* _FLUENT_AMG_OVERLAP_H */
