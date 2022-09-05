/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef DPM_LOGGING_H
#define DPM_LOGGING_H

#include "dpm.h"
#include "dpm_subtet.h"

struct track_data_s;

/**
 * @addtogroup dpm Discrete Particle Model
 * @{
 *
 * @file
 * DPM: functions required for DPM logging
 *
 */

#define DPM_TOOLS_LOG_ID  dpm_par.tp_log_id
#define LOG_MSG CX_Message_MT

/* to log global cell / face IDs */
#define LOG_MSG_E_ID sizeof

/* Logging macros that are always enabled */
#define LOG_2D_VEC_ENABLED(msg1, vec)                  LOG_MSG("%s: [%g, %g]\n", msg1, vec[0], vec[1])
#define LOG_3D_VEC_ENABLED(msg1, vec)                  LOG_MSG("%s: [%g, %g, %g]\n", msg1, vec[0], vec[1], vec[2])
#define LOG_4D_VEC_ENABLED(msg1, vec)                  LOG_MSG("%s: [%g, %g, %g, %g]\n", msg1, vec[0], vec[1], vec[2], vec[3])
#define LOG_3D_VEC_12_ENABLED(msg1, vec)               LOG_MSG("%s: [%.12g, %.12g, %.12g]\n", msg1, vec[0], vec[1], vec[2])
#define LOG_3D_VEC_INT_ENABLED(msg1, indx, msg2, vec)  LOG_MSG("%s: %d, %s: [%g, %g, %g]\n", msg1, indx, msg2, vec[0], vec[1], vec[2])
#define LOG_3D_VEC_2INTS_ENABLED(msg1, indx1, msg2, indx2, msg3, vec)                                  \
  LOG_MSG("%s: %d, %s: %d, %s: [%g, %g, %g]\n", msg1, indx1, msg2, indx2, msg3, vec[0], vec[1], vec[2])

#if RP_3D
#define LOG_ND_VEC_ENABLED(msg1, vec)  LOG_3D_VEC_ENABLED(msg1, vec)
#else
#define LOG_ND_VEC_ENABLED(msg1, vec)  LOG_2D_VEC_ENABLED(msg1, vec)
#endif


/* always enabled */
#if RP_3D
#define LOG_TET_POINT(name, indx, point)               LOG_MSG("%s[%d] = [%g, %g, %g]\n", name, indx, point[indx][0], point[indx][1], point[indx][2])
#else
#define LOG_TET_POINT(name, indx, point)               LOG_MSG("%s[%d] = [%g, %g]\n", name, indx, point[indx][0], point[indx][1])
#endif

#define LOG_ALL_TET_POINTS(name, point, npoints)        \
          {                                             \
            int m_i;                                    \
            for (m_i = 0; m_i < npoints; ++m_i)         \
              LOG_TET_POINT(name, m_i, point);          \
          }


#define  LOG_PART_ID_P  FALSE
#if LOG_PART_ID_P
FLUENT_EXPORT void log_pp_id(        Particle *pp, char *function, int line, char *file);
FLUENT_EXPORT void log_tp_id(Tracked_Particle *tp, char *function, int line, char *file);
#define     LOG_NEW_PART_ID(pp)  log_pp_id(pp, __FUNCTION__, __LINE__, __FILE__)
#define LOG_TRACKED_PART_ID(tp)  log_tp_id(tp, __FUNCTION__, __LINE__, __FILE__)
#else
#define     LOG_NEW_PART_ID(pp)  do { } while (0)
#define LOG_TRACKED_PART_ID(tp)  do { } while (0)
#endif


FLUENT_EXPORT void log_cell(const cell_t c, Thread *tc);
FLUENT_EXPORT void log_subtet(const char *comment, const Subtet_Tracking_Location *loc);
FLUENT_EXPORT void log_lightweight_subtet(const char *comment, const Subtet_LightWeight *loc);
FLUENT_EXPORT void log_locate_params(cxboolean params[]);
FLUENT_EXPORT void log_track_segment(const struct track_data_s *track, const int indx);

FLUENT_EXPORT void log_overset_cell_type(const cell_t c, Thread *tc);

FLUENT_EXPORT void log_cell_node_positions_at_t_delta(const cell_t c, Thread *tc, const double t_delta);
FLUENT_EXPORT void log_face_node_positions_at_t_delta(const face_t f, Thread *tf, const double t_delta);
FLUENT_EXPORT void log_subtet_node_positions_at_t_delta(Tracked_Particle *tp, const double t_delta);

FLUENT_EXPORT void log_subtet_face_node_coordinates(Subtet_Tracking_Location *loc, const int iFace);

FLUENT_EXPORT void log_entry_to_NextPos(Tracked_Particle *tp, Particle *pp, const int LOG_ID);
FLUENT_EXPORT void log_wall_film_height(const char *comment, const int LOG_ID, const int LOG_FACE_ID);
FLUENT_EXPORT void log_if_position_is_in_cell(const char *comment, Tracked_Particle *tp, real *pos, const real t_delta);


/* @} dpm */

#endif   /* #ifndef DPM_LOGGING_H */

