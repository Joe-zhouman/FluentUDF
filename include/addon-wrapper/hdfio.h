/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_HDFIO_H_
#define _FLUENT_HDFIO_H_

FLUENT_EXPORT cxboolean Open_Hdfio_Library(void);
FLUENT_EXPORT cxboolean Close_Hdfio_Library(void);
FLUENT_EXPORT void InitializeHdfioPrimitives(void);
FLUENT_EXPORT void Write_Partial_Typed_User_Dataset(char *, char *, void *, MPT_Datatype, size_t, size_t, size_t);
FLUENT_EXPORT void Write_Partial_User_Dataset(char *, char *, real *, size_t, size_t, size_t);
FLUENT_EXPORT void Write_Complete_Typed_User_Dataset(char *, char *, void *, MPT_Datatype, size_t);
FLUENT_EXPORT void Write_Complete_User_Dataset(char *, char *, real *, size_t);
FLUENT_EXPORT void Write_User_Attributes(char *, char *, ...);
FLUENT_EXPORT void Read_Partial_Typed_User_Dataset(char *, char *, void *, MPT_Datatype, size_t, size_t);
FLUENT_EXPORT void Read_Partial_User_Dataset(char *, char *, real *, size_t, size_t);
FLUENT_EXPORT void Read_Complete_Typed_User_Dataset(char *, char *, void *, MPT_Datatype, size_t);
FLUENT_EXPORT void Read_Complete_User_Dataset(char *, char *, real *, size_t);
FLUENT_EXPORT void Read_User_Attributes(char *, char *, ...);
FLUENT_EXPORT cxboolean Link_Exists_In_File(const char *, const char *, const char *, const char *, const char *);
FLUENT_EXPORT void Get_Next_User_Link_Name(char *, char *, char *, char *);
#if PARALLEL
FLUENT_EXPORT void CreateThreadsInDomain(Domain *, long, int, int *, int *, int *);
#endif /* PARALLEL */
FLUENT_EXPORT int HDF_Write_Attributes(const char *filename, const char *parent, const char *path, ...);
FLUENT_EXPORT int HDF_Write_Section(const char *, const char *, const int, const char *, const char *, const char *, const size_t, const size_t, MPT_Datatype, void *, const size_t);
FLUENT_EXPORT int HDF_Write_String(const char *filename, const char *parent, const char *path, const char *name, const char *sstr);
FLUENT_EXPORT void HDF_Write_Ac_Receivers_Data(const char *, const char *, double *, size_t);
FLUENT_EXPORT void HDF_Write_Ac_Receivers_Attributes(const char *, const char *, ...);
FLUENT_EXPORT int HDF_Read_Ac_Receivers_Attributes(const char *, const char *, ...);
FLUENT_EXPORT void HDF_Read_Ac_Receivers_Data(const char *, const char *, double *, size_t);
FLUENT_EXPORT int HDF_Write_Ghost_Cell_Link_Section(char *, char *, cxindex *, size_t, ...);
FLUENT_EXPORT int HDF_Write_Network_Section(char *, int *, size_t, ...);
FLUENT_EXPORT int HDF_Write_Network_Data(char *, int *, size_t, real *, size_t);
FLUENT_EXPORT void HDF_Write_Special_Attributes(char *, char *, ...);
FLUENT_EXPORT int HDF_Read_Attributes(char *, char *, char *, ...);
FLUENT_EXPORT int HDF_Read_Special_Attributes(char *, char *, ...);
FLUENT_EXPORT int HDF_Read_Section(const char *, const char *, const char *, const char *, const char *, const size_t, const size_t, MPT_Datatype, void *, const size_t);
FLUENT_EXPORT char *HDF_Read_String(const char *filename, const char *parent, const char *path, const char *name);
FLUENT_EXPORT int HDF_Read_Special_Section(char *, char *, void *, MPT_Datatype, size_t);
struct kidmem;
FLUENT_EXPORT void Create_Threads_In_Domain_new(Domain *const domain, const long, const int, const size_t, int *const,
                                                int *const, int *const,
                                                int *const, int *const, const int, const size_t, int *const,
                                                const size_t, int *const, const size_t, int *const, int *const,
                                                const size_t, int *const, const size_t, int *const, int *const,
                                                struct kidmem **);

/*
 * Related to APIs for I/O of thread-data by developers
 */

typedef struct thread_data_manager_t__
{
  MPT_Datatype (*get_mpt_datatype)();

  /* before any write operation */
  /* NULL: not required */
  int (*update_before_write)();

  /* should return true if at least one element of this thread has data */
  /* NULL: all threads (cell, face and node) will be checked for this data */
  /*       recommended to use if information is available */
  cxboolean (*thread_has_data)(Thread *);

  /* returns if elements in use of this thread has same amount of data */
  /* NULL: no thread in use has uniform data */
  /*       suggested to use this if uniform data is used */
  cxboolean (*thread_has_uniform_data)(Thread *, int *);

  /* returns number of data points of this element to be written */
  /* this will not be called for threads which have uniform data */
  /* NULL: if all elements of all threads *in use* have uniform data */
  int (*get_num_cell_data)(cell_t, Thread *);
  int (*get_num_face_data)(face_t, Thread *);
  int (*get_num_node_data)(Node *);
#if USE_FEMCORE
  int (*get_num_interpolation_node_data)(interpolation_node_t, Thread *);
#endif
  /* number of rows in this compute-process */
  /* number of columns across all compute-processes; should be same */
  int (*get_num_direct_data)(size_t *, int *);

  /* gets the data in a void pointer */
  /* at least one needs to be valid */
  int (*get_cell_data)(cell_t, Thread *, void *);
  int (*get_face_data)(face_t, Thread *, void *);
  int (*get_node_data)(Node *, void *);
#if USE_FEMCORE
  int (*get_interpolation_node_data)(interpolation_node_t, Thread *, void *);
#endif

  /* fill up data present in this compute-process */
  int (*get_direct_data)(size_t, int, void *);

  /* after all write operation */
  /* NULL: not required */
  int (*update_after_write)();

  /* before any read operation */
  /* NULL: not required */
  int (*update_before_read)();

  /* This gets called if data is not available, prepare your model that way */
  /* NULL: not needed */
  int (*data_not_available)();

  /* This thread is read from file and is used to set this information */
  /* NULL: not required */
  int (*set_thread_has_data)(Thread *);

  /* Allocate memory on active threads */
  /* NULL: not required */
  int (*update_before_reading_num_data)();

  /* Pass information about uniform data from file to memory */
  /* NULL: not required */
  int (*set_thread_has_uniform_data)(Thread *, int);

  /* Pass information to solver which is read from file */
  /* NULL: not required */
  int (*set_num_cell_data)(cell_t, Thread *, int);
  int (*set_num_face_data)(face_t, Thread *, int);
  int (*set_num_node_data)(Node *, int);
#if USE_FEMCORE
  int (*set_num_interpolation_node_data)(interpolation_node_t, Thread *, int);
#endif

  /* number of rows and columns in the file */
  int (*set_num_direct_data)(size_t, int);

  /* after filling the num-data information */
  /* NULL: not required */
  int (*update_after_reading_num_data)();

  /* Allocate memory on active threads */
  /* NULL: not required */
  int (*update_before_reading_data)();

  /* how many elements this process should read */
  /* NULL: everything will be read in process-0 */
  int (*get_num_direct_data_reading_local)(size_t *);

  /* Set the data */
  /* al least one needs to be valid */
  int (*set_cell_data)(cell_t, Thread *, int, MPT_Datatype, void *);
  int (*set_face_data)(face_t, Thread *, int, MPT_Datatype, void *);
  int (*set_node_data)(Node *, int, MPT_Datatype, void *);
#if USE_FEMCORE
  int (*set_interpolation_node_data)(interpolation_node_t, Thread *,int, MPT_Datatype, void *);
#endif

  int (*set_direct_data)(size_t, int, MPT_Datatype, void *);

  /* after filling the data */
  /* NULL: not required */
  int (*update_after_reading_data)();

  /* after all read operation */
  /* NULL: not required */
  int (*update_after_read)();

  /* set appropriate flag */
  /* must use for direct data */
  int flags;
} HDF_Thread_Data_Manager;

typedef enum thread_data_manager_enum_t__
{
  HDFIO_GET_MPT_DATATYPE,
  HDFIO_UPDATE_BEFORE_WRITE,
  HDFIO_THREAD_HAS_DATA,
  HDFIO_THREAD_HAS_UNIFORM_DATA,
  HDFIO_GET_NUM_CELL_DATA,
  HDFIO_GET_NUM_FACE_DATA,
  HDFIO_GET_NUM_NODE_DATA,
#if USE_FEMCORE
  HDFIO_GET_NUM_INTERPOLATION_NODE_DATA,
#endif
  HDFIO_GET_NUM_DIRECT_DATA,
  HDFIO_GET_CELL_DATA,
  HDFIO_GET_FACE_DATA,
  HDFIO_GET_NODE_DATA,
#if USE_FEMCORE
  HDFIO_GET_INTERPOLATION_NODE_DATA,
#endif
  HDFIO_GET_DIRECT_DATA,
  HDFIO_UPDATE_AFTER_WRITE,
  HDFIO_UPDATE_BEFORE_READ,
  HDFIO_DATA_NOT_AVAILABLE,
  HDFIO_SET_THREAD_HAS_DATA,
  HDFIO_UPDATE_BEFORE_READING_NUM_DATA,
  HDFIO_SET_THREAD_HAS_UNIFORM_DATA,
  HDFIO_SET_NUM_CELL_DATA,
  HDFIO_SET_NUM_FACE_DATA,
  HDFIO_SET_NUM_NODE_DATA,
#if USE_FEMCORE
  HDFIO_SET_NUM_INTERPOLATION_NODE_DATA,
#endif
  HDFIO_SET_NUM_DIRECT_DATA,
  HDFIO_UPDATE_AFTER_READING_NUM_DATA,
  HDFIO_UPDATE_BEFORE_READING_DATA,
  HDFIO_GET_NUM_DIRECT_DATA_READING_LOCAL,
  HDFIO_SET_CELL_DATA,
  HDFIO_SET_FACE_DATA,
  HDFIO_SET_NODE_DATA,
#if USE_FEMCORE
  HDFIO_SET_INTERPOLATION_NODE_DATA,
#endif
  HDFIO_SET_DIRECT_DATA,
  HDFIO_UPDATE_AFTER_READING_DATA,
  HDFIO_UPDATE_AFTER_READ,
  HDFIO_SET_FLAG,
  HDFIO_END_CALLBACKS
} HDF_Thread_Data_Callback;


#ifndef  UDF_COMPILER
# define UDF_COMPILER 0
#endif

#define HDF_MANAGER_FL_DIRECT_DATA (1)

FLUENT_EXPORT int HDF_Write_Managed_Threads(char *, char *, const int,
                                            char *, char *, Domain *const,
                                            HDF_Thread_Data_Manager *const);
FLUENT_EXPORT int HDF_Read_Managed_Threads(char *, char *, char *, char *, Domain *const,
                                           HDF_Thread_Data_Manager *const);
#if PARALLEL
FLUENT_EXPORT int HDF_Register_Case_IO_Manager(const char *, const char *, HDF_Thread_Data_Manager *);
FLUENT_EXPORT void HDF_Deregister_Case_IO_Manager(const char *, const char *);
FLUENT_EXPORT int HDF_Register_Data_IO_Manager(const char *, const char *, HDF_Thread_Data_Manager *);
FLUENT_EXPORT void HDF_Deregister_Data_IO_Manager(const char *, const char *);
FLUENT_EXPORT int HDF_Write_All_Managed_Case_Threads(char *, char *, const int, Domain *const);
FLUENT_EXPORT int HDF_Write_All_Managed_Data_Threads(char *, char *, const int, Domain *const);
FLUENT_EXPORT int HDF_Read_All_Managed_Case_Threads(char *, char *, Domain *const);
FLUENT_EXPORT int HDF_Read_All_Managed_Data_Threads(char *, char *, Domain *const);
FLUENT_EXPORT void HDF_Register_Test_Case_IO_Managers(void);
FLUENT_EXPORT void HDF_Deregister_Test_Case_IO_Managers(void);
FLUENT_EXPORT void HDF_Register_Test_Data_IO_Managers(void);
FLUENT_EXPORT void HDF_Deregister_Test_Data_IO_Managers(void);
FLUENT_EXPORT void HDF_Deregister_All_Case_IO_Managers(void);
FLUENT_EXPORT void HDF_Parse_IO_Options(HDF_Thread_Data_Manager *, ...);

# if  ! UDF_COMPILER

#define REGISTER_CASE_IO_MANAGER_CALLBACKS(_display, _dataset, _manager, ...)  \
{                                                                              \
  static HDF_Thread_Data_Manager _instance_##_manager;                         \
  HDF_Parse_IO_Options(&_instance_##_manager, __VA_ARGS__);                    \
  HDF_Register_Case_IO_Manager(_display, _dataset, &_instance_##_manager);     \
}

#define REGISTER_CASE_IO_MANAGER(_displayname,_datasetname,_manager,...) \
  {                                                                     \
    static HDF_Thread_Data_Manager _instance_##_manager = { __VA_ARGS__ }; \
    HDF_Register_Case_IO_Manager(_displayname,_datasetname,&_instance_##_manager); \
  }

#define REGISTER_DATA_IO_MANAGER_CALLBACKS(_display, _dataset, _manager, ...)  \
{                                                                              \
  static HDF_Thread_Data_Manager _instance_##_manager;                         \
  HDF_Parse_IO_Options(&_instance_##_manager, __VA_ARGS__);                    \
  HDF_Register_Data_IO_Manager(_display, _dataset, &_instance_##_manager);     \
}

#define REGISTER_DATA_IO_MANAGER(_displayname,_datasetname,_manager,...) \
  {                                                                     \
    static HDF_Thread_Data_Manager _instance_##_manager = { __VA_ARGS__ }; \
    HDF_Register_Data_IO_Manager(_displayname,_datasetname,&_instance_##_manager); \
  }
# endif   /*  ! UDF_COMPIILER */
#else /* PARALLEL */
# if  ! UDF_COMPILER
#  define REGISTER_CASE_IO_MANAGER_CALLBACKS(_display, _dataset, _manager, ...)
#  define REGISTER_CASE_IO_MANAGER(_displayname,...) /* nothing */
# endif   /*  ! UDF_COMPIILER */
#endif /* !PARALLEL */

#endif /* _FLUENT_HDFIO_H_ */
