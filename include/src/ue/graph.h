/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_GRAPH_H
#define _FLUENT_GRAPH_H

#include "dll.h"

#define ROTATE_UNDEFINED -1

#if PARALLEL || GRAPHICS

# if (RP_NODE || RP_HOST)
#  define PRF_BUFF_SIZE 8192
# endif

extern FLUENT_EXPORT void Draw_Face_Thread_Mesh(Domain *, Thread *);
extern FLUENT_EXPORT void Draw_Cell_Thread_Mesh(Domain *, Thread *);
extern FLUENT_EXPORT void Grid_Partition_Boundary(Domain *domain);

extern FLUENT_EXPORT void Draw_Periodics(Domain *, int);

extern FLUENT_EXPORT void Draw_Symmetries(Thread *);
extern FLUENT_EXPORT void Draw_Coarse_Level(Domain *domain, int level);

# if RP_2D
extern FLUENT_EXPORT void Contour_Domain(Domain *domain, int nv, const char *viz_name);
# endif
extern FLUENT_EXPORT void Contour_Surface(int surface_index,
                                          cxboolean node_values,
                                          const char *viz_name);

FLUENT_EXPORT  void Fill_Field_Data(char *name, int *indices,
                                    int nids, int node_values);

extern FLUENT_EXPORT void Velocity_Vector_Domain(Domain *domain,
                                                 char *viz_name,
                                                 cxboolean scaled,
                                                 int sample,
                                                 char *components[]);

extern FLUENT_EXPORT void Velocity_Vector_Surface(Domain *domain,
                                                  int index,
                                                  char *viz_name,
                                                  cxboolean  in_plane,
                                                  cxboolean scaled,
                                                  int sample,
                                                  char *components[]);

FLUENT_EXPORT real Compute_Vector_Scale(Domain *domain);

FLUENT_EXPORT void CVF_Vector_Domain(Domain *domain,
                                     char *name,
                                     cxboolean scaled,
                                     int sample,
                                     char *vname);

FLUENT_EXPORT void CVF_Vector_Surface (int index,
                                       char *name,
                                       cxboolean in_plane,
                                       cxboolean scaled,
                                       int  sample, char *vname);

# if PARALLEL
FLUENT_EXPORT void Draw_Cell_By_Id(Domain *domain,
                                   int cell_id);
FLUENT_EXPORT void Draw_Face_By_Cell_Ids(Domain *domain,
                                         int cell_id1,
                                         int cell_id2);
# endif

# if RP_HOST
FLUENT_EXPORT void Host_Insert_Faces(void);
FLUENT_EXPORT void Host_Insert_Cells(void);
# endif

#endif /* PARALLEL || GRAPHICS */

#endif /* _FLUENT_GRAPH_H */



