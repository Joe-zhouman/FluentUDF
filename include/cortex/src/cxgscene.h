/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifdef WORKING_CXX

#ifndef _CXG_SCENE_H
#define _CXG_SCENE_H


#if defined(__cplusplus)
void cxg_basename(const char *name_in, char *base_name);
void cxg_change_path_to_relative(char *segment, char *from, char *rel_path);


extern "C" {
#endif /* __cplusplus */

/* c callable routines */
void CXG_Geometry_Search(char *start_segment);
void CXG_Segment_Search(char *start_segment);
int CXG_Copy_Hoops_Attributes(const char *from_seg, const char *to_seg);
void CXG_Replace_Include_Segments(char *start_segment);

//Copy all oldPath segment children direclty to newPath, replace external
//'outer' includes with direct copies
void CXG_Copy_Self_Contained_Segment(const char *oldPath, const char *newPath);

#if defined(__cplusplus)
}       /* end of extern "C" */
#endif /* __cplusplus */


#endif /* _CXG_SCENE_H */
#endif /* WORKING_CXX */
