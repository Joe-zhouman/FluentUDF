/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _CXG_ASR_H
#define _CXG_ASR_H

#if defined(__cplusplus)

// C++ specific headers
/*
 * so far, works for
 *          irix65,
 *          lnx86 g++ (2.9) ,
 *          sun's SC4.2 + ultra build host,
 *          osf1 4.0 cxx,
 *          hpux11, hpux10pa1's aCC
 *          ntx86 w/ ms vc++ project
 *
 *     does NOT work for aix yet - will try gnu c++
 */

#include <stddef.h>

#if defined(_ultra) || defined(_alpha) || defined(_aix43) || defined (_aix51) || defined (_power3) || defined(_fujitsu_pp) || defined(linux)

# include <list>

#elif defined(_hpux11) || defined(_NT) || defined (_hpux10pa1) || defined (_hpux10p8) || defined(_hiux)

# include <list>

#else  /* irix65 and lnx86 g++ */

# include <list.h>
#endif

#include "cxg_anim.h"
class AnimationFrameRecord;

#if defined(_aix43) || defined (_aix51) || defined (_power3) || defined(_ultra) || defined(_fujitsu_pp) || defined (linux)
using std::list;
using std::ostream;
using std::istream;
#elif defined(_NT)
using std::list;
# endif

/*
 *  Class to hold information about each animation sequence
 */
class AnimationSequence
{
protected:
  // base filename or segment for frame storage :this is combination of .cxa file folder path + animation object name
  //Absolute ->  D:/Test/Projects/Animations/Jpeg\\myanimation   AND yeah yeah path saved is like linux with forwardslash here even for windows (it works- microsoft done it)
  //relative -> out/myfolder\\myAnimation    this will turn out tobe   out/myfolder\\\\myAnimation_0000.png for frame ..literally \\\\ still works
  //Linux : /nfs/home2/gmundhe/Projects/Jpeg/jpeg
  char *basename;

  //using dir_name_sep we identify posi "\\" or "/"  from last and make them emptry and treat is as dirname  ...damn

  char *dirname;                  // if file, store the directory where frames are //this can be relative path
  char *absolutedirname;          //THis is absolute path for sequnece location: constructed from only(for now) reading standalone animation files ,
  int window_id;                  // window id from which scene is taken
  int sequence_index;             // unique identifier
  SceneStorageType storage_type;  // storage type
  bool saving_frames;
  int numberOfFramesToRead;       // numberOfFramesToRead-> -1: Will read whole frames, Valid number: Will read speficed rows from sequence file.
//    std::
  list<AnimationFrameRecord *> frames; // list of individual frames
  bool plot_animation;            // Is this a 2D plot animation sequence?
  bool standaloneAnimation = false;

  // static data and access functions
  //    for maintaining unique identifiers for each sequence
  static int last_index;
  static int NewInstanceIndex(void) {return ++last_index;}
  static void SetInstanceIndex(int ndx) {last_index = ndx;}
  static int GetInstanceIndex(void) {return last_index;}

public:
  // constructors
  AnimationSequence(void);
  // basic for creating from required info
  AnimationSequence(char *bname, char *dir, int win_id, SceneStorageType store_as);
  // copy constructor
  // warning - this can be dangerous
#if 0
  AnimationSequence(const AnimationSequence &seq);
#endif
  // copy + convert constructor
  AnimationSequence(const AnimationSequence &seq, SceneStorageType new_type);
  //destructor
  ~AnimationSequence();
#if 0
  // overloaded equal operator
  const AnimationSequence &operator = (const AnimationSequence &s2);
#endif


  // data "get" routines
  const char *BaseName(void) const {return (const char *)basename;}
  const char *Directory(void) const {return (const char *)dirname;}
  const char *AbsoluteDirectory(void) const { return (this->storage_type == storage_hps_segment) ? "" : (const char *)absolutedirname;}
  int SequenceNumber(void) const {return sequence_index;}
  int NumberOfFrames(void) const {return (int)frames.size();}
//    int NumberOfFrames(void) const {return frames.size();}
  int WindowID(void) const {return window_id;}
  bool SavingFrames(void) const {return saving_frames;}
  inline bool IsStandaloneAnimation() const { return standaloneAnimation; }
  inline bool IsPlotAnimation() const { return plot_animation; }

  SceneStorageType StorageType(void) const
  {
    return storage_type;
  }
  char **FrameList(int &nframes) const;
  const list <AnimationFrameRecord *> SequenceList(void) const
  {
    return (const list <AnimationFrameRecord *>) frames;
  }

  // data "set" routines
  void SetSaveFrames(bool save) {saving_frames = save;}
  void SetStorageType(SceneStorageType store_as) {storage_type = store_as;}
  void SetWindowID(int win_id) { window_id = win_id;}
  void SetNumberOfFramesToRead(int n) { numberOfFramesToRead = n; }
  void SetStorageName(const char *bname);
  void SetDirectory(char *dir);
  void SetPlotAnimation(bool val) { plot_animation = val; }
  void SetAbsoluteDirectory(const char *);
  void SetStandaloneAnimation(bool val) { standaloneAnimation = val; }
  // clear out the list
  void ClearList(void);
  void ResetAbsDir(bool doResetFramesPath = false);

protected:
  // function to fill this list from another list of frame records
  int CopyFromList(const list<AnimationFrameRecord *> &inframes);
  // function to add a frame record to the end of the list
  void AddFrameRecord(AnimationFrameRecord *r)
  {
    frames.push_back(r);
  }
  // function to create the name of the frame file
  char *FrameName(int frame_num) const;

  // function to create the frame file
  //    or copy to the saved hoops location
//    void StoreFrame(AnimationFrameRecord* frame);
  //For export video this methode create temp input param file
  void createInputFile(const std::string &, const int &, const int &, const int &);
public:
  void OnCaseDataLoad();
  void writeToCxa(AnimationSequence &seqTo);
  // take snapshot of window to add a frame to sequence
  void Snap(void);
  // load (display) the specified frame in the window
  // save_frame == 1; save frame_ndx on disk - currently used for png/tiff format for mpeg ppm input files
  int LoadFrame(int frame_ndx, bool save_camera = true, bool save_frame = false);
  // convert storage type for each frame
  void ConvertFrames(SceneStorageType newtype, bool save_old_location = false);
  // stream operators
  friend std::ostream &operator <<(std::ostream &os, AnimationSequence &s);
  friend std::istream &operator >>(std::istream &is, AnimationSequence &s);
  char *CheckandReturnAbsoluteDir() const;
/// <summary>
/// <para>This methode create args to pass to UDIL Movie Encoder</para>
/// </summary>
  void EncodeMovie(int &, int &, int &);
  void SaveQtFrameAsPPM(int frameIndex, char *fileName);
};
#endif /* __cplusplus */
#endif /* _CXG_ASR_H */
