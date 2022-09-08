/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#include "cxconfig.h"  /* for WORKING_CXX if exists */
#include <map>
#ifdef WORKING_CXX

#ifndef _CXG_ANIM_H
#define _CXG_ANIM_H

class AnimationSequence;

#if defined(__cplusplus)

extern "C" {
#endif /* __cplusplus */
/* allowable storage types
      - currently hps_segment and hmf_file are implimented */
typedef enum SceneStorageType
{
  storage_unknown = 0,
  storage_hps_segment,
  storage_hmf_file,
  storage_image_file,
  storage_ppm_file,
  storage_hsf_file,
  storage_tiff_file,
  storage_png_file,
  storage_jpeg_file
} SceneStorageType;

//TODO: create a methode returning extenstion based on SceneStorageType
//currently this static casues to have private copy into each file it is used eg cxg_asr, cxg_graph, etc
static std::map<SceneStorageType, const char *> SceneStorageTypeToFormat
{
  {storage_hps_segment, "hsf"},
  {storage_hmf_file, ".hmf"},
  {storage_image_file, "rgb" },
  {storage_ppm_file, ".ppm" },
  { storage_hsf_file, ".hsf" },
  { storage_tiff_file, ".tiff" },
  { storage_png_file, ".png" },
  { storage_jpeg_file, ".jpeg" }
};

/* C callable/accessable routines structures and variables*/
char *dir_name_sep(char *fullname);

void cxg_ani_pause(float secs);

/*
 *  animation interface routines
 *    note: the use of the 'enum' keyword in the following
 *    declarations is required because this header is used
 *    by c files (not just c++ files) and thus must follow ANSI C
 *    (we could probably just as well done a typedef enum ... above)
 */

void CXG_Anim_OnCaseDataLoad(int seqNum);

void CXG_Anim_WriteToCxa(int seqNumFrom, int seqNumTo);

void CXG_Set_Hardcopy_Options(char *driver);

/* convert enum type to string or integer index */
int CXG_ConvertStorageTypeToText(SceneStorageType type, char *text);
int CXG_ConvertStorageTypeToIndex(SceneStorageType etype);
SceneStorageType CXG_ConvertIndexToStorageType(int itype);

/* default storage type is to use hmf files,
    this function will change that default */
void CXG_SetDefaultStorage(SceneStorageType def_type);

/* get the current default storage type */
SceneStorageType CXG_GetDefaultStorage(void);

/* get the storage type of the current sequence */
SceneStorageType CXG_GetCurrentStorage(void);

int CXG_GetCurrentSequence(void);

/* get the basename of the current animation sequence */
void CXG_GetCurrentName(char *ani_name);

/* get the storage directory of the current animation sequence */
void CXG_GetCurrentDir(char *ani_dir);
/* get the number of frames recorded in the current animation sequence */
int CXG_GetCurrentFrames(void);

/* get the window id for the current animation sequence */
int CXG_GetCurrentWindowID(void);

/* get the current number of animation sequences recorded */
int CXG_AnimationSequenceCount(void);

bool CXG_IsCurrentSequencePlotAnimation();

AnimationSequence *GetSequencePointer(int seq_num);
SceneStorageType CXG_GetSequenceStorage(int seq_num);
void CXG_GetSequenceName(int seq_num, char *ani_name);
void CXG_GetSequenceStoragePath(int seq_num, char *anim_dir);
int CXG_GetSequenceFrames(int seq_num);
int CXG_GetSequenceWindowID(int seq_num);
void CXG_GetSequenceAbsoluteStoragePath(int seq_num, char *anim_dir);

void CXG_SetSequenceAbsoluteStoragePath(int seq_num, char *new_path);
char const *CXG_Get_Sequence_Info(int seq_number, int *win_id, int *type, int *frames);


/* Users must make sure arrays are properly sized */
int CXG_Get_Defined_Animations(int sequences[], char const **names, int win_ids[], int types[], int frames[]);

/* return array of currently defined sequence id's */
int *CXG_Get_Defined_Animation_Sequences(void);

/* get frame location/filename list for given sequence
 * returns number of frames by reference */
char **CXG_Get_Frame_Name_List(int seq_num, int *nframes);
void CXG_Free_Frame_List(char **frame_list, int nframes);

/* function to start the creation of an animation sequence
    args are: the base file name and the window to record from
    returns the animation sequence id
 */
int CXG_Start_Animation(char *bname, char *dir, int window_id);

/* add current window contents to the animation sequence
   (adds to end of sequence) */
int CXG_Snap_Frame(void);

/* end the animation sequence */
void CXG_End_Animation(void);

void CXG_Store_Playback_Camera(void);
void CXG_Discard_Playback_Camera(void);


/*  load a frame from the current animation sequence */
int CXG_Load_And_Save_Animation_Frame(int frame_ndx, bool save_frame);

/* set the current animation sequence */
int CXG_Set_Current_Animation_Sequence(int seq);

/* write an animation sequence record to file */
int CXG_Write_Animation_Sequence(int seq_num);

/* read in an animation sequence record from a file */
int CXG_Read_Animation_Sequence(char *fname);

/* writes video file */
void CXG_Encode_Animation_sequence_To_Movie(int seq_num, int startFrame, int endFrame, int skipFrames);

/* To set animation sequence frames from sequence file */
int CXG_Set_Animation_Sequence_Frames(int seq_num, char *fname);

/* rename the animation sequence
    will only change basename (and directory)
    will NOT change location of any existing frames */
void CXG_Rename_Animation_Sequence(int seq_num, char *new_name);
void CXG_Reset_Storage_Path_Animation_Sequence(int seq_num, char *new_path);

void CXG_Change_Animation_Sequence_Window(int seq_num, int win_id);
void CXG_Set_Animation_Sequence_Frames_To_Read(int seq_num, int n);
void CXG_Change_Animation_Sequence_Storage(int seq_num, int new_storage_index);

/* change storage mode of sequence
  will convert all existing frames */
void CXG_Convert_Animation_Sequence(int seq_num, int new_itype);

/* delete an animation sequence (including any files produced) */
void CXG_Delete_Animation_Sequence(int seq_num);
/* delete animation sequnece frames */
void CXG_Delete_Animation_Sequence_Frames(int seq_num);

void RemoveAnimPlaybackPanel(int windowId);

void CXG_Reset_animation_AbsDirectory();

const char *CXG_ConvertStorageTypeToExentention(SceneStorageType type);

#if defined(__cplusplus)
}  /* end extern "C" */
#endif

#endif /* CXGHMF_H */
#endif /* WORKING_CXX */
