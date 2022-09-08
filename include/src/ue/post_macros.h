/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#pragma once

#include "overset.h"
#include "narrow_gaps.h"

#define INACTIVE_GAP_OR_CONTACT_CELL_P(c, t) \
  ((contact_active_p && !render_blocked_cells && CONTACT_ZONE_CELL_P (c, t)) \
  || \
  (NNULLP(Narrow_Gap_Model) && NARROW_GAPS_ENABLED_P(Narrow_Gap_Model) && \
   !NARROW_GAPS_POSTPROCESS_DATA_P(Narrow_Gap_Model) && NARROW_GAPS_INVALID_POST_CELL_P(c, t)))
#define INACTIVE_CELL_P(c, t) (INACTIVE_GAP_OR_CONTACT_CELL_P(c, t) || (overset_render_p && !OVERSET_RENDER_CELL_P (c, t))) 



static cxboolean
post_solved_cell_p(cell_t c, Thread *t)
{
  cxboolean solved_cell_p = TRUE;
  if (contact_active_p &&
      NULLP(Narrow_Gap_Model) &&
      !render_blocked_cells &&
      CONTACT_ZONE_CELL_P(c, t)
     )
  {
    solved_cell_p = FALSE;
  }
  else if (NNULLP(Narrow_Gap_Model) &&
           NARROW_GAPS_ENABLED_P(Narrow_Gap_Model) &&
           !NARROW_GAPS_POSTPROCESS_DATA_P(Narrow_Gap_Model) &&
           NARROW_GAPS_INVALID_POST_CELL_P(c, t)
          )
  {
    solved_cell_p = FALSE;
  }
  else if (sg_overset && !OVERSET_SOLVE_CELL_P(c, t))
  {
    solved_cell_p = FALSE;
  }
  return solved_cell_p;
}

static cxboolean
post_rendered_cell_p(cell_t c, Thread *t)
{
  cxboolean render_cell_p = TRUE;
  if (THREAD_RENDERP(t))
  {
    if (contact_active_p &&
        NULLP(Narrow_Gap_Model) &&
        !render_blocked_cells &&
        CONTACT_ZONE_CELL_P(c, t)
       )
    {
      render_cell_p = FALSE;
    }
    else if (NNULLP(Narrow_Gap_Model) &&
             NARROW_GAPS_ENABLED_P(Narrow_Gap_Model) &&
             !NARROW_GAPS_POSTPROCESS_DATA_P(Narrow_Gap_Model) &&
             NARROW_GAPS_INVALID_POST_CELL_P(c, t)
            )
    {
      render_cell_p = FALSE;
    }
    else if (sg_overset && !OVERSET_RENDER_CELL_P(c, t))
    {
      render_cell_p = FALSE;
    }
  }
  else
  {
    render_cell_p = FALSE;
  }
  return render_cell_p;
}

static cxboolean
post_dead_cell_p(cell_t c, Thread *t)
{
  cxboolean dead_cell_p = FALSE;
  if (contact_active_p &&
      NULLP(Narrow_Gap_Model) &&
      !render_blocked_cells &&
      CONTACT_ZONE_CELL_P(c, t)
     )
  {
    dead_cell_p = TRUE;
  }
  else if (NNULLP(Narrow_Gap_Model) &&
           NARROW_GAPS_ENABLED_P(Narrow_Gap_Model) &&
           !NARROW_GAPS_POSTPROCESS_DATA_P(Narrow_Gap_Model) &&
           NARROW_GAPS_INVALID_POST_CELL_P(c, t)
          )
  {
    dead_cell_p = TRUE;
  }
  else if (sg_overset && OVERSET_DEAD_CELL_P(c, t))
  {
    dead_cell_p = TRUE;
  }
  return dead_cell_p;
}

static cxboolean
post_active_cell_p(cell_t c, Thread *t)
{
  return !post_dead_cell_p(c, t);
}
static cxboolean
post_dead_face_p(face_t f, Thread *t)
{
  cxboolean dead_face_p = FALSE;
  if (sg_overset)
  {
    if (
      (THREAD_T0(t) && post_dead_cell_p(F_C0(f, t), THREAD_T0(t))) &&
      (THREAD_T1(t) && post_dead_cell_p(F_C1(f, t), THREAD_T1(t)))
    )
    {
      dead_face_p = TRUE;
    }
  }
  return dead_face_p;
}

static cxboolean
post_rendered_face_p(face_t f, Thread *t)
{
  cxboolean render_face_p = TRUE;

  if ( sg_overset ||
       (contact_active_p && NULLP(Narrow_Gap_Model) && !render_blocked_cells) ||
       ( NNULLP(Narrow_Gap_Model) && NARROW_GAPS_ENABLED_P(Narrow_Gap_Model) &&
         !NARROW_GAPS_POSTPROCESS_DATA_P(Narrow_Gap_Model)
       )
     )
  {
    if ( (THREAD_T0(t) && post_dead_cell_p(F_C0(f, t), THREAD_T0(t))) &&
         (THREAD_T1(t) && post_dead_cell_p(F_C1(f, t), THREAD_T1(t)))
       )
    {
      render_face_p = FALSE;
    }
  }
  return render_face_p;
}

static cxboolean
post_solved_face_p(face_t f, Thread *t)
{
  cxboolean solved_face_p = TRUE;
  if ( sg_overset ||
       (contact_active_p && NULLP(Narrow_Gap_Model) && !render_blocked_cells) ||
       (NNULLP(Narrow_Gap_Model) && NARROW_GAPS_ENABLED_P(Narrow_Gap_Model) &&
        !NARROW_GAPS_POSTPROCESS_DATA_P(Narrow_Gap_Model)
       )
     )
  {
    if ( (THREAD_T0(t) && !post_solved_cell_p(F_C0(f, t), THREAD_T0(t))) &&
         (!THREAD_T1(t) || (THREAD_T1(t) && !post_solved_cell_p(F_C1(f, t), THREAD_T1(t))))
       )
    {
      solved_face_p = FALSE;
    }
  }
  return solved_face_p;
}

#define begin_c_loop_post_int(c,t,filter) \
          begin_c_loop_int(c,t) \
          { \
            if(post_ ## filter ## _cell_p(c, t)) \
            {
#define end_c_loop_post_int(c,t,filter) \
         }} end_c_loop_int(c,t)

#define begin_c_loop_post(c,t,filter) \
          begin_c_loop(c,t) \
          { \
            if(post_ ## filter ## _cell_p(c, t)) \
            {
#define end_c_loop_post(c,t,filter) \
         }} end_c_loop(c,t)

#define begin_f_loop_post_int(f,t,filter) \
          begin_f_loop(f,t) \
          { \
            if(post_ ## filter ## _face_p(f, t)) \
            {
#define end_f_loop_post_int(f,t,filter) \
         }} end_f_loop_int(f,t)

#define begin_f_loop_post(f,t,filter) \
          begin_f_loop(f,t) \
          { \
            if(post_ ## filter ## _face_p(f, t)) \
            {
#define end_f_loop_post(f,t,filter) \
         }} end_f_loop(f,t)


