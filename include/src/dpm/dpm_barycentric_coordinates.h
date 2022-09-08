/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef DPM_BARYCENTRIC_COORDINATES_H
#define DPM_BARYCENTRIC_COORDINATES_H

#include "dpm.h"
#include "global.h"


/**
 * @addtogroup dpm Discrete Particle Model
 * @{
 *
 * @file
 * DPM: calculating and storing barycentric coordinates
 *
 */

/* macros for a 4-element array of barycentric coordinates */
#define INIT_BARY_COORDS(_coords)       (_coords[0]) = 0.0; (_coords[1]) = 0.0; (_coords[2]) = 0.0; (_coords[3]) = 0.0;
#define SET_BARY_COORDS(_coords, _val)  (_coords[0]) = (_val[0]); (_coords[1]) = (_val[1]); (_coords[2]) = (_val[2]); (_coords[3]) = (_val[3]);
#define SUM_BARY_COORDS(_coords)        ((_coords[0]) + (_coords[1]) + (_coords[2]) + (_coords[3]))
#define BARY_COORDS_SET_P(_coords)      (SUM_BARY_COORDS(_coords) > FLT_MIN)

/*
 * functions used outside of dpm_barycentric_coordinates.c
 */
FLUENT_EXPORT void GetBarycentricCoordinates(double bary_coords[4], const double position[3], double (*vtx_coord)[3],
                                             double (* p_r_matrix)[3][3]);
FLUENT_EXPORT void GetMollerVector(const double edge_1[3], const double edge_2[3], const double d[3],
                                   double coords[3], const double o_vec[3]);

FLUENT_EXPORT cxboolean GetInvertedBarycentricMatrix(double r_matrix[3][3], double (* node_coords)[3]);
FLUENT_EXPORT cxboolean IsSubtetDegenerate(double vtx_coord[4][3]);

cxboolean is_point_in_sector_barycentric(const double *pos, double tetPts[4][3], const double epsilon,
                                         double (* p_r_matrix)[3][3], double bary_coords[4]);
cxboolean is_point_beyond_plane(const double *pos, double tetPts[4][3], double (* p_r_matrix)[3][3]);

FLUENT_EXPORT double get_volume_of_subtet(double node_coords[4][3]);


#if RP_2D
FLUENT_EXPORT double rotate_pos_to_axi_plane(double position[3]);

FLUENT_EXPORT void rotate_pos_from_axi_plane(const double pos[3], const double theta, double new_pos[3]);
FLUENT_EXPORT void rotate_vector_to_axi_plane(double vector[3], const double position[3], const double radius);
#endif



/* @} dpm */

#endif   /* #ifndef DPM_BARYCENTRIC_COORDINATES_H */

