/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _CXG_AFR_H
#define _CXG_AFR_H

#include <stddef.h>  /* for NULL */
#include <iostream>
#include "cxg_anim.h"

class QPixmap;

// Class to hold information to keep track of individual animation frames
// Individual frames(image data) will be stored only in case of 2D plots
class AnimationFrameRecord
{
private:
  char *storage_location;   // filename or hoops segment
  QPixmap *frame;          // Frame stored in case of 2d plots
  bool plotFrame;         // Does this frame belong to a 2D plot animation?

protected:
  int frame_number;         // frame number in the owner sequence
  int orig_window_id;       // window id from which frame was taken
  SceneStorageType storage_type;  // mode of storage

  QPixmap *grabPlotFrame(int windowId);   // Grab the frame from plot window

public:
  // default constructor - empty record
  AnimationFrameRecord(bool plot_frame);
  // basic constructor for use when saving frame
  AnimationFrameRecord(SceneStorageType type, char *store_name, int frame_num, int win_id, bool plot_frame);
  // copy constructor by pointer
  // USE WITH CARE!!! This does not create a copy of the actual
  //  frame, and will actually reference the same location as from
  //   the frame copied
#if 0
  AnimationFrameRecord(AnimationFrameRecord *r);
#endif
  // destructor
  ~AnimationFrameRecord();

  // overloaded equal operator
#if 0
  const AnimationFrameRecord &operator = (const AnimationFrameRecord &r2);
#endif
  // data "get" routines
  int FrameNumber(void) const {return frame_number;}
  SceneStorageType StorageType(void) const {return storage_type;}
  const char *Location(void) const {return (const char *) storage_location;}
  int OrigWindowID(void) const { return orig_window_id; }
  bool getPlotFrame() const { return plotFrame; }
  QPixmap *getFrame() const { return frame; }

  // data "set" routines
  void SetFrame(int frame) { frame_number = frame;}
  void setPlotFrame(bool plotFrame) { this->plotFrame = plotFrame; }
protected:
  void SetWindowID(int win_id) {orig_window_id = win_id;}
  void SetStorageType(SceneStorageType type) {storage_type = type;}

  static int GetSegmentUsers(char *segment);
  static void SetSegmentUsers(char *segment, int users);
public:
  void SetLocation(const char *loc);

public:
  /*
  * load frame into designated hoops window
  * if dest_frame_path != NULL, stores this frame on disk(currently as ppm)
  */
  void LoadFrame(int window_id, bool save_camera = 1, char *dest_fram = NULL);
  // load to a specified hoops location
  void LoadTo(char *segment);
  void StoreSegmentFrame(char *store_loc, char *from_segment);
  void StoreWindowFrame(char *store_loc, int win_id);
  void DeleteFrame(void);
  // convert from current storage type to designated type
  void ConvertStorageTo(SceneStorageType newtype, bool save_old_storage = false);

  // overloaded stream operators
  // write frame info to sequence record file
  // they do not write the frames themselves
  friend std::ostream &operator << (std::ostream &os, const AnimationFrameRecord *r);
  friend std::istream &operator >> (std::istream &is, AnimationFrameRecord *r);
};

#endif /* _cxg_afr_h */