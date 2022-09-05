/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_PARA_H
#define _FLUENT_PARA_H

#include "dll.h"
#include "prf.h"

extern FLUENT_EXPORT cxboolean rp_host;
extern FLUENT_EXPORT cxboolean rp_node;
extern FLUENT_EXPORT cxboolean rp_net;
extern FLUENT_EXPORT cxboolean rp_lsf;
extern FLUENT_EXPORT cxboolean rp_sge;
extern FLUENT_EXPORT int myid;
extern FLUENT_EXPORT void CX_Free_Host_Domain(void);
extern FLUENT_EXPORT int compute_node_count;
extern FLUENT_EXPORT int is_mixed_platform;

#define NODE_HOST 999999
#define NODE_SERIAL 1000000
#define PRF_RPVAR_STRING_LEN 2048

#define N_TYPE_IN_IO_BUFFER 16384

#if PARALLEL
# define START_POST_PROCESSING_TIMER Start_Post_Processing_Timer()
#else
# define START_POST_PROCESSING_TIMER
#endif

#if PARALLEL
# define STOP_POST_PROCESSING_TIMER(c) End_Post_Processing_Timer(c)
#else
# define STOP_POST_PROCESSING_TIMER(c)
#endif


#if RP_HOST || RP_NODE

extern FLUENT_EXPORT const char *lmain_command;


/*
 * define's
 */

#define CEILING(numer, denom) \
  (((numer)/(denom)) + ((((numer)%(denom)) == 0)?0:1))

#ifndef  SIZE_T_MAX
# define SIZE_T_MAX ((size_t)((~((size_t)0))>>1))   /* >>1 may not be needed it size_t is fully unsigned */
#endif



# define RV_NULL SV_NULL
# define RV_W SV_P
# define RV_WO SV_P_WO
# define RV_WV SV_P_WV
# define RV_WN SV_P_WN
# define RV_FW SV_P_FW
# define RV_G SV_P_G
# define RV_RG SV_P_RG
# define RV_M1 SV_P_M1
# define RV_M2 SV_P_M2

/*
 * globals
 */
extern FLUENT_EXPORT int node_serial;
extern FLUENT_EXPORT int node_host;
extern FLUENT_EXPORT int node_one;
extern FLUENT_EXPORT int node_last;
extern FLUENT_EXPORT int node_zero;
extern FLUENT_EXPORT int any_node;
extern FLUENT_EXPORT int *int_buf1;
extern FLUENT_EXPORT int *int_buf2;
extern FLUENT_EXPORT long *long_buf1;
extern FLUENT_EXPORT long *long_buf2;
extern FLUENT_EXPORT cxindex *index_buf1;
extern FLUENT_EXPORT cxindex *index_buf2;
extern FLUENT_EXPORT float *float_buf1;
extern FLUENT_EXPORT float *float_buf2;
extern FLUENT_EXPORT double *double_buf1;
extern FLUENT_EXPORT double *double_buf2;
extern FLUENT_EXPORT double *node_buf;
# if RP_DOUBLE
#  define real_buf1 double_buf1
#  define real_buf2 double_buf2
# else
#  define real_buf1 float_buf1

#  define real_buf2 float_buf2
# endif
extern FLUENT_EXPORT int n_type_in_io_buffer;
# if RP_HOST
extern FLUENT_EXPORT cxboolean Host_Only;
# endif

/*
 * to contain the parallel global flags
 */
#include "para_common.h"

/*
 * public routine prototypes
 */
FLUENT_EXPORT cxboolean PRF_Anyone_Received_Signal(cxboolean);
FLUENT_EXPORT void PRF_Reset_Signal(void);
FLUENT_EXPORT void Print_Compute_Node_Messages(int id);
FLUENT_EXPORT void Print_Case_Timer(Domain *d);
FLUENT_EXPORT void Print_Data_Timer(Domain *d);
FLUENT_EXPORT void Print_Flow_Timer(Domain *d);

FLUENT_EXPORT void Clear_Flow_Timer(Domain *d);
FLUENT_EXPORT void Clear_Case_Timer(Domain *d);
FLUENT_EXPORT void Clear_Data_Timer(Domain *d);
FLUENT_EXPORT void Clear_Post_Timer(Domain *d);
FLUENT_EXPORT void Clear_Domain_Timers(Domain *d);
FLUENT_EXPORT void Clear_Post_Timer(Domain *d);

FLUENT_EXPORT void Start_Read_Case_Timer(void);
FLUENT_EXPORT void End_Read_Case_Timer(Domain *d);
FLUENT_EXPORT void Start_Write_Case_Timer(void);
FLUENT_EXPORT void End_Write_Case_Timer(Domain *d);
FLUENT_EXPORT void Start_Read_Data_Timer(void);
FLUENT_EXPORT void End_Read_Data_Timer(Domain *d);
FLUENT_EXPORT void Start_Write_Data_Timer(void);
FLUENT_EXPORT void End_Write_Data_Timer(Domain *d);

FLUENT_EXPORT void Start_Read_Case_Section_Timer(void);
FLUENT_EXPORT void End_Read_Case_Section_Timer(Domain *d);
FLUENT_EXPORT void Start_Write_Case_Section_Timer(void);
FLUENT_EXPORT void End_Write_Case_Section_Timer(Domain *d);
FLUENT_EXPORT void Start_Read_Data_Section_Timer(void);
FLUENT_EXPORT void End_Read_Data_Section_Timer(Domain *d);
FLUENT_EXPORT void Start_Write_Data_Section_Timer(void);
FLUENT_EXPORT void End_Write_Data_Section_Timer(Domain *d);

FLUENT_EXPORT void Start_Post_Processing_Timer(void);
FLUENT_EXPORT void End_Post_Processing_Timer(Domain *d);

FLUENT_EXPORT void Start_Wall_Clock_Timer(Timer *th);
FLUENT_EXPORT void End_Wall_Clock_Timer(Timer *th, Domain *domain);

FLUENT_EXPORT int My_Compute_Node_Id(void);
FLUENT_EXPORT unsigned int Case_Buffer_Size(void);
FLUENT_EXPORT void Set_Case_Buffer_Size(int size);
FLUENT_EXPORT void spawn_nodes(void *);
FLUENT_EXPORT Domain *Spawn_Compute_Node(Domain *d, const char *c, const char *h, const char *u, const char *p,
                                         int parent, int child);
FLUENT_EXPORT Domain *Kill_Compute_Node(Domain *d, int id);
FLUENT_EXPORT void Kill_Zero_Cell_Compute_Nodes(Domain *d);
FLUENT_EXPORT void PRF_Push_Error(const char *file, int line, const char *message);
FLUENT_EXPORT int Alloc_Parallel_IO_Buffers(unsigned int, cxboolean, const char *, int);
FLUENT_EXPORT void set_parallel_globals(void);
FLUENT_EXPORT void Free_Parallel_IO_Buffers(void);
FLUENT_EXPORT void Limit_Parallel_IO_Buffer_Size(unsigned int);
FLUENT_EXPORT void Query_Parallel_IO_Buffers(int *);
FLUENT_EXPORT int Get_Parallel_IO_Buffer_Size_1(void);
FLUENT_EXPORT int Get_Parallel_IO_Buffer_Size_2(void);
FLUENT_EXPORT void Init_Parallel_IO_Buffers_AsInt(void);
FLUENT_EXPORT int Alloc_Smart_Parallel_IO_Buffers(Domain *domain);
FLUENT_EXPORT void Fill_Any_Storage_Allocated(Domain *d);
FLUENT_EXPORT int Gset_Face_To_Cell_Threads(Domain *domain, cxboolean with_host, int master_id);
FLUENT_EXPORT void Establish_Host_Domain_If_Needed(Domain *d);
FLUENT_EXPORT void Disable_DPM_Fill_Host_Domain(Domain *d);
FLUENT_EXPORT void Enable_DPM_Fill_Host_Domain(Domain *d);
FLUENT_EXPORT void Fill_Host_Domain(Domain *d, int cells, int exclude_method);
FLUENT_EXPORT void DPM_Fill_Host_Domain(Domain *d);
FLUENT_EXPORT void Solar_Fill_Host_Domain(Domain *d);
FLUENT_EXPORT cxboolean Is_Host_Domain_Filled_P(Domain *d, cxboolean with_node);
FLUENT_EXPORT cxboolean Is_Host_Domain_Filled_P_checkSvars(Domain *d, cxboolean with_node, ...);
FLUENT_EXPORT void Node_To_Host_Vars(Domain *d, ...);
FLUENT_EXPORT void Node_To_Host_Thread_Vars(Domain *d, Thread *t, ...);
FLUENT_EXPORT void Node_To_Host_Node_Value(Domain *d);
FLUENT_EXPORT void Host_To_Node_Vars(Domain *d, ...);
FLUENT_EXPORT void Host_To_Node_Vars_Solar(Domain *d, ...);
FLUENT_EXPORT void transfer_files_to_tmp_directory(char *,char *,char*);
FLUENT_EXPORT void remove_tmp_directory(char *);

# if RP_DTRM
FLUENT_EXPORT void DTRM_Host_To_Node_Source(Domain *d);
# endif /* RP_DTRM */
FLUENT_EXPORT cat_t Lookup_Cell_By_Id(Domain *, cxindex);
# if RP_NODE
FLUENT_EXPORT cat_t Lookup_Exterior_Cell_By_Id(Domain *, cxindex);
# endif
FLUENT_EXPORT fat_t Lookup_Face_By_Id(Domain *, cxindex);
# if RP_NODE
FLUENT_EXPORT cat_t Lookup_Cell_By_Id_In_Thread_List(Domain *, map_id_t **, int *,  Objp *, cxindex);
FLUENT_EXPORT fat_t Lookup_Face_By_Id_In_Thread_List(Domain *, map_id_t **, int *,  Objp *, cxindex);
# endif
FLUENT_EXPORT void Alloc_Coupled_Face_Id_Maps(Domain *);
FLUENT_EXPORT Node *Lookup_Node_By_Id(Domain *, cxindex);
FLUENT_EXPORT void Free_Id_Maps(Domain *domain);
FLUENT_EXPORT void Create_Id_Maps(Domain *domain);
# if RP_NODE
FLUENT_EXPORT void Create_Cell_Id_Map_In_Thread_List(Domain *domain, map_id_t **map, int *map_count, Objp *t_list);
FLUENT_EXPORT void Create_Face_Id_Map_In_Thread_List(Domain *domain, map_id_t **map, int *map_count, Objp *t_list);
# endif
FLUENT_EXPORT double cbenchmark(int from, int to, const char *argv, int for_latency);
# if RP_HOST
FLUENT_EXPORT void Free_Host_Domain(Domain *domain);
# endif /* RP_HOST */

#if !UDF_COMPILER
FLUENT_EXPORT void Clear_Timer(Timer *time);
#endif


/* Data shipper */
/*===========================================================================*/
/* data shipper class */
/*---------------------------------------------------------------------------*/
/* note(s):
 * todo:
 *  - skip zero-size messages
 *  - potentially reduce memory requirements by splitting messages and using
 *    smaller buffers.
 */

typedef struct datashipper_s
{
  cxindex nbufServer;     /* total size of server-side buffer */
  cxindex nbufClient;     /* total size of client-side buffer */
  cxindex sizeServer;     /* buffer size on server side */
  cxindex *bufClient;     /* sizes of client-side proc buffers [nproc] */
  cxindex *bufServer;     /* sizes of server-side proc buffers [nproc] */
  cxindex *offClient;     /* offsets for client-side buffers [nproc] */
  cxindex *offServer;     /* offsets for server-side buffers [nproc] */
  cxindex *indexClient;   /* client indices for client-side sets [nbufClient] */
  cxindex *indexServer;   /* server indices for server-side sets; indices are in local space [sizeServer] */
} Datashipper;

FLUENT_EXPORT void Datashipper_delete(Datashipper *thisPtr);
FLUENT_EXPORT Datashipper *Datashipper_new(const cxindex nbufServer,
                                           const cxindex nbufClient, const cxindex map_offset,
                                           const cxindex isrvr_clnt[] );
FLUENT_EXPORT void Datashipper_distribute(Datashipper *thisPtr,
                                          MPT_Datatype dtype,
                                          const int ncomp_src, const void *buf_src,
                                          const int ncomp_dest, void *buf_dest);
FLUENT_EXPORT void Datashipper_collect(Datashipper *thisPtr,
                                       MPT_Datatype dtype,
                                       const int ncomp_src, const void *buf_src,
                                       const int ncomp_dest, void *buf_dest);

# define compute_node_loop(cn) for(cn=node_zero;cn<compute_node_count;cn++)
# define compute_node_loop_not_zero(cn) for(cn=node_one;cn<compute_node_count;cn++)
# define compute_node_loop_not_zero_and_host(cn) for(cn=node_host;cn<compute_node_count || cn==node_host; cn = ((node_host==cn)?node_one:cn+1))
# define compute_node_loop_not_last(cn) for(cn=node_zero;cn<node_last;cn++)
# define compute_node_loop_not_me(cn) for(cn=node_zero; cn<compute_node_count;cn++) \
                                        if(cn != myid)
# define reversed_compute_node_loop(cn) for(cn=node_last; cn>=node_zero; cn--)
# define reversed_compute_node_loop_not_zero(cn) for(cn=node_last; cn>=node_one; cn--)

# define MULTIPLE_COMPUTE_NODE_P (compute_node_count > 1)
# define ONE_COMPUTE_NODE_P (compute_node_count == 1)
# define ZERO_COMPUTE_NODE_P (compute_node_count == 0)

# define I_AM_COMPUTE_NODE_P (! (node_host == myid || node_serial == myid))
# define I_AM_NODE_SERIAL_P FALSE
# define I_AM_NODE_HOST_P (myid == node_host)
# define I_AM_NODE_ZERO_P (myid == node_zero)
# define I_AM_NODE_ONE_P (myid == node_one)
# define I_AM_NODE_LAST_P (myid == node_last)
# define I_AM_NODE_SAME_P(n) (myid == (n))
# define I_AM_NODE_LESS_P(n) (myid < (n))
# define I_AM_NODE_MORE_P(n) (myid > (n))

# define INTERIOR_CELL_P(c,t) I_AM_NODE_SAME_P(C_PART_ACTIVE(c,t))
# define EXTERIOR_CELL_P(c,t) (! INTERIOR_CELL_P(c,t))
# define EXTERIOR_CELL_REG_P(c,t) (c>=THREAD_N_ELEMENTS_INT(t) && \
                                   c<(THREAD_N_ELEMENTS_INT(t)+THREAD_N_ELEMENTS_REXT(t)))
# define EXTERIOR_CELL_EXT_P(c,t) (c>=THREAD_N_ELEMENTS_INT(t)+THREAD_N_ELEMENTS_REXT(t))

# define TWO_CELL_FACE_P(f,t) (!NULL_CELL_P(F_C0(f,t)) && \
                               (NULL != F_C1_THREAD(f,t)) && \
                               !NULL_CELL_P(F_C1(f,t)))
# define PRINCIPAL_TWO_CELL_FACE_P(f,t) \
    (!(I_AM_NODE_MORE_P(C_PART_ACTIVE(F_C0(f,t),F_C0_THREAD(f,t)))  || \
       I_AM_NODE_MORE_P(C_PART_ACTIVE(F_C1(f,t),F_C1_THREAD(f,t)))))

# define PRINCIPAL_FACE_P(f,t) (!TWO_CELL_FACE_P(f,t) || PRINCIPAL_TWO_CELL_FACE_P(f,t))

# if RP_HOST
# define PRINCIPAL_TWO_CELL_FACE_FOR_DEST_P(f,t,dest)     \
  (!((dest)>C_PART_ACTIVE(F_C0(f,t),F_C0_THREAD(f,t)) ||  \
     (dest)>C_PART_ACTIVE(F_C1(f,t),F_C1_THREAD(f,t))))

# define PRINCIPAL_FACE_FOR_DEST_P(f,t,dest) (!TWO_CELL_FACE_P(f,t) || PRINCIPAL_TWO_CELL_FACE_FOR_DEST_P(f,t,(dest)))
# define I_AM_NODE_MASTER_P        FALSE
# define I_AM_NODE_HOST_OR_MASTER_P TRUE
# endif /* RP_HOST */

#if RP_NODE
#define IDLE_WAIT(root_node)                                              \
  {                                                                       \
    if (!rp_net)                                                          \
    {                                                                     \
      int _wakeup = 1, _cn;                                               \
      if (myid==root_node)                                                \
      {                                                                   \
        for(_cn=node_zero;_cn<compute_node_count;_cn++)                   \
          if (myid!=_cn)                                                  \
            PRF_ISEND_INT(_cn,&_wakeup,1,myid);                           \
        PRF_WAIT_ALL();                                                   \
      }                                                                   \
      else                                                                \
        MPT_crecv_poll(root_node,&_wakeup,1,MPT_INT,root_node,0.0,100.0); \
    }                                                                     \
  }

/* if parallel.master hasn't been allocated, make every node behave like a master...(?) */
# define I_AM_NODE_MASTER_P (NULLP(parallel.master) ? TRUE : (myid == parallel.master[myid]))
# define I_AM_NODE_HOST_OR_MASTER_P I_AM_NODE_MASTER_P
#endif

#else

# define I_AM_NODE_SERIAL_P TRUE
# define I_AM_COMPUTE_NODE_P FALSE
# define I_AM_NODE_HOST_P FALSE
# define I_AM_NODE_ZERO_P TRUE
# define I_AM_NODE_ONE_P FALSE
# define I_AM_NODE_LAST_P TRUE   /* OK? */
# define I_AM_NODE_SAME_P(n) TRUE
# define I_AM_NODE_LESS_P(n) FALSE
# define I_AM_NODE_MORE_P(n) FALSE
# define I_AM_NODE_MASTER_P         TRUE   /* apply even for serial */
# define I_AM_NODE_HOST_OR_MASTER_P TRUE   /* apply even for serial */
# define PRINCIPAL_TWO_CELL_FACE_P(f,t) TRUE
# define PRINCIPAL_FACE_P(f,t) TRUE

#endif /* RP_HOST || RP_NODE */

FLUENT_EXPORT double Get_Timer(void);
FLUENT_EXPORT void Set_Env_Vars(const char *vlist, int enforce);
FLUENT_EXPORT void trace_command(const char *argv);
FLUENT_EXPORT void Get_Parallel_Flags(void);
FLUENT_EXPORT void Set_Parallel_IO_Flags(void);
FLUENT_EXPORT void Comm_Type_Evaluating_Initialize(int);
FLUENT_EXPORT void Comm_Type_Evaluating_Finalize(int, int);


FLUENT_EXPORT void Model_Initialize_parallel(void);


#if RP_NODE

/*
 * structures
 */
typedef struct message_exchange_struct
{
  int sendbuf_size;
  int recvbuf_size;

  char *sendbuf;
  char *recvbuf;
} Exchange_Message;

typedef struct node_exch_provider_t_
{
  int flag;
  Domain *domain;
  int (*nbytes)(struct node_exch_provider_t_* provider);
  void (*fill_buffer)(struct node_exch_provider_t_* provider, Node *v, char *buffer);
  void (*use_buffer )(struct node_exch_provider_t_* provider, Node *v, char *buffer);

} node_exch_provider_t;

typedef struct Entity_Data_t
{
  /* Entity: Cell, Face, Node */
  cxindex id;  /* Entity ID */
  int tid;     /* Entity Thread ID */
  int index;   /* Entity index */
  int part;    /* Entity home partition */
} Entity_Data;

/*
 * public routines
 */

#define EXC_SUM  1
#define EXC_MIN  2
#define EXC_MAX  3
#define EXC_LOR  4
#define EXC_LAND 5
FLUENT_EXPORT void Compute_Node_init_seem(void);
FLUENT_EXPORT cxboolean Set_Svar_Messages(Svar first, ...);
FLUENT_EXPORT void Set_Rvar_Messages(Svar first, ...);
FLUENT_EXPORT void Set_Max_Exchange_Svars_Limit(int max_svar_count, cxboolean isGlobal);
FLUENT_EXPORT int  Get_Max_Exchange_Svars_Limit(void);
FLUENT_EXPORT void Exchange_UDMI(Domain *, int, int, const char *, int);
FLUENT_EXPORT void Exchange_Svar_Messages (Domain *, const char *, const char *, int);
FLUENT_EXPORT void Reverse_Exchange_Svar_Messages (Domain *, const char *, const char *, int);
FLUENT_EXPORT void Reverse_Exchange_Svar_Messages_Ext (Domain *, const char *, const char *, int);
FLUENT_EXPORT void Exchange_Svar_Messages_All (Domain *, const char *, const char *, int);
FLUENT_EXPORT void Exchange_Svar_Messages_Ext (Domain *, const char *, const char *, int);
FLUENT_EXPORT void Exchange_Svar_Messages_All_Ext (Domain *, const char *, const char *, int);
FLUENT_EXPORT void Exchange_Svar_Face_Messages (Domain *, const char *, const char *, int);
FLUENT_EXPORT void Exchange_Svar_Face_And_Shadow_Messages (Domain *, const char *, const char *, int);
FLUENT_EXPORT void Exchange_Svar_IFace_Messages (Domain *, const char *, const char *, int);
FLUENT_EXPORT void Exchange_Svar_BFace_Messages (Domain *, const char *, const char *, int);
#if RP_OVERSET
FLUENT_EXPORT void Exchange_Svar_OFace_Messages (Domain *, const char *, const char *, int);
FLUENT_EXPORT void Exchange_Svar_Donor_Messages (Domain *, const char *, const char *, int);
FLUENT_EXPORT void Exchange_Svar_Receptor_Messages (Domain *, const char *, const char *, int);
#endif
FLUENT_EXPORT void Exchange_Svar_All_Face_Messages (Domain *, const char *, const char *, int);
FLUENT_EXPORT void Exchange_Svar_All_Face_Messages_Ext (Domain *, const char *, const char *, int);
FLUENT_EXPORT void Accumulate_Svar_Face_int(Svar nv, Domain *domain);

FLUENT_EXPORT void Exchange_Svar_Node_Messages (Domain *, const char *, const char *, int);
FLUENT_EXPORT void Exchange_Node_Generic_Messages(Domain *, node_exch_provider_t *, const char *, const char *, int);
FLUENT_EXPORT void Exchange_Node_Flag_Messages(Domain *, int, const char *, int);
FLUENT_EXPORT void Exchange_Node_Values2(Domain *, const char *, int);
FLUENT_EXPORT void Exchange_Node_Values_And_Weights(Domain *, const char *, int);
FLUENT_EXPORT void Exchange_Node_Mark(Domain *, const char *, int);
FLUENT_EXPORT void Exchange_Svar_Node_Messages_Op (Domain *, int, const char *, const char *, int);
FLUENT_EXPORT void Exchange_Cell_Node_Ids(Domain *d);
#if RP_HANG
FLUENT_EXPORT void Exchange_Cell_Children(Domain *d);
#endif
FLUENT_EXPORT void Set_Parallel_Face(Domain *, Svar);
FLUENT_EXPORT void Set_Parallel_Face_Deferred_S(Domain *, Svar, Svar);
FLUENT_EXPORT void Set_Parallel_Face_Not_Jump(Domain *, Svar);
FLUENT_EXPORT int Create_Messages(Domain *, unsigned int);
FLUENT_EXPORT void Free_Messages(Domain *);
FLUENT_EXPORT void PRF_all_to_one_csend_real(int final_dest, real *buffer, int buflen);
FLUENT_EXPORT void PRF_all_to_one_csend_float(int final_dest, float *buffer, int buflen);
FLUENT_EXPORT void PRF_all_to_one_csend_int(int final_dest, int *buffer, int buflen);
FLUENT_EXPORT void PRF_all_to_one_csend_char(int final_dest, char *buffer, int buflen);

FLUENT_EXPORT void set_exchange_order(Domain *d);


#define Exchange_Tmp(d)EXCHANGE_SVAR_MESSAGE(d,(SV_RTMP_0,SV_NULL))


# define EXTERIOR_FACE_P(f,t) \
  ((NULL_CELL_P(F_C0(f,t)) || !I_AM_NODE_SAME_P(C_PART_ACTIVE(F_C0(f,t),F_C0_THREAD(f,t)))) && \
   (NULL_CELL_P(F_C1(f,t)) || !I_AM_NODE_SAME_P(C_PART_ACTIVE(F_C1(f,t),F_C1_THREAD(f,t)))))
# define INTERFACE_FACE_P(_f,_t) \
  (!NULL_CELL_P(F_C0(_f,_t)) && !NULL_CELL_P(F_C1(_f,_t)) &&  \
   NNULLP(F_C0_THREAD(_f,_t)) && NNULLP(F_C1_THREAD(_f,_t)) &&          \
   (I_AM_NODE_SAME_P(C_PART_ACTIVE(F_C0(_f,_t),F_C0_THREAD(_f,_t))) || \
    I_AM_NODE_SAME_P(C_PART_ACTIVE(F_C1(_f,_t),F_C1_THREAD(_f,_t))))  && \
   (C_PART_ACTIVE(F_C0(_f,_t),F_C0_THREAD(_f,_t)) != C_PART_ACTIVE(F_C1(_f,_t),F_C1_THREAD(_f,_t))))

# define FACE_EXTERIOR_CELL(f,t) EXTERIOR_CELL_P(F_C0(f,t),F_C0_THREAD(f,t)) ? F_C0(f,t) : F_C1(f,t)
# define FACE_EXTERIOR_CELL_THREAD(f,t) EXTERIOR_CELL_P(F_C0(f,t),F_C0_THREAD(f,t)) ? F_C0_THREAD(f,t) : F_C1_THREAD(f,t)
# define FACE_INTERIOR_CELL(f,t) INTERIOR_CELL_P(F_C0(f,t),F_C0_THREAD(f,t)) ? F_C0(f,t) : F_C1(f,t)
# define FACE_INTERIOR_CELL_THREAD(f,t) INTERIOR_CELL_P(F_C0(f,t),F_C0_THREAD(f,t)) ? F_C0_THREAD(f,t) : F_C1_THREAD(f,t)

# define FACE_EXTERIOR_CELL_PART(f,t) C_PART_ACTIVE(FACE_EXTERIOR_CELL(f,t),FACE_EXTERIOR_CELL_THREAD(f,t))
# define FACE_INTERIOR_CELL_PART(f,t) C_PART_ACTIVE(FACE_INTERIOR_CELL(f,t),FACE_INTERIOR_CELL_THREAD(f,t))

#else
# define INTERFACE_FACE_P(_f,_t) \
  (!NULL_CELL_P(F_C0(_f,_t)) && !NULL_CELL_P(F_C1(_f,_t)) && \
   (C_PART_ACTIVE(F_C0(_f,_t),F_C0_THREAD(_f,_t)) != C_PART_ACTIVE(F_C1(_f,_t),F_C1_THREAD(_f,_t))))
#endif /* RP_NODE */
#define FAST_INTERFACE_FACE_P(_f,_t) (C_PART_ACTIVE(F_C0(_f,_t),F_C0_THREAD(_f,_t)) != C_PART_ACTIVE(F_C1(_f,_t),F_C1_THREAD(_f,_t)))


/*
 * parallel loop macros
 */
#if RP_NODE
# define EXCHANGE_UDMI(_d,_i1,_i2) \
    do \
      { \
        if (MULTIPLE_COMPUTE_NODE_P) \
          { \
            Exchange_UDMI(_d,_i1,_i2,__FILE__,__LINE__); \
          } \
      } \
    while (0)

/* Now maximum number of svars that can be exchanged in one go can be restricted
   using functions Set_Max_Exchange_Svars_Limit and   Get_Max_Exchange_Svars_Limit.
   Hence actual exchange routines may need to called repeatedely. */

#define REVERSE_EXCHANGE_SVAR_MESSAGE(d,dm_flags) \
   if (MULTIPLE_COMPUTE_NODE_P) \
   { \
     cxboolean exchange_incomplete = FALSE; \
     do \
     { \
          const char *print_flags = #dm_flags; \
          exchange_incomplete = Set_Svar_Messages dm_flags;   \
          Reverse_Exchange_Svar_Messages(d,print_flags,__FILE__,__LINE__); \
     } \
     while (exchange_incomplete); \
   }

#define REVERSE_EXCHANGE_SVAR_MESSAGE_EXT(d,dm_flags) \
   if (MULTIPLE_COMPUTE_NODE_P) \
   { \
     cxboolean exchange_incomplete = FALSE; \
     do \
     { \
          const char *print_flags = #dm_flags; \
          exchange_incomplete = Set_Svar_Messages dm_flags;   \
          Reverse_Exchange_Svar_Messages_Ext(d,print_flags,__FILE__,__LINE__); \
     } \
     while (exchange_incomplete); \
   }

# define EXCHANGE_SVAR_MESSAGE(d,dm_flags) \
   if (MULTIPLE_COMPUTE_NODE_P) \
     { \
      cxboolean exchange_incomplete = FALSE; \
      do \
       { \
            const char *print_flags = #dm_flags; \
            exchange_incomplete = Set_Svar_Messages dm_flags;        \
            START_PROFILE_BASE("Exchange_Svar_Messages", 1, 5); \
            Exchange_Svar_Messages(d,print_flags,__FILE__,__LINE__);    \
            STOP_PROFILE_BASE("Exchange_Svar_Messages", 1, 5); \
       } \
      while (exchange_incomplete);\
     }

# define EXCHANGE_SVAR_MESSAGE_ALL(d,dm_flags) \
  if (MULTIPLE_COMPUTE_NODE_P) \
      { \
        cxboolean exchange_incomplete = FALSE;  \
        do \
          { \
            const char *print_flags = #dm_flags; \
            exchange_incomplete = Set_Svar_Messages dm_flags; \
            Exchange_Svar_Messages_All(d,print_flags,__FILE__,__LINE__); \
          } \
        while (exchange_incomplete); \
      }

# define EXCHANGE_SVAR_MESSAGE_EXT(d,dm_flags) \
   if (MULTIPLE_COMPUTE_NODE_P) \
     { \
      cxboolean exchange_incomplete = FALSE; \
      do \
       { \
            const char *print_flags = #dm_flags; \
            exchange_incomplete = Set_Svar_Messages dm_flags;        \
            START_PROFILE_BASE("Exchange_Svar_Messages_EXT", 1, 5);\
            Exchange_Svar_Messages_Ext(d,print_flags,__FILE__,__LINE__); \
            STOP_PROFILE_BASE("Exchange_Svar_Messages_EXT", 1, 5);\
       } \
      while (exchange_incomplete);\
     }

# define EXCHANGE_SVAR_MESSAGE_ALL_EXT(d,dm_flags) \
  if (MULTIPLE_COMPUTE_NODE_P) \
      { \
        cxboolean exchange_incomplete = FALSE;  \
        do \
          { \
            const char *print_flags = #dm_flags; \
            exchange_incomplete = Set_Svar_Messages dm_flags; \
            Exchange_Svar_Messages_All_Ext(d,print_flags,__FILE__,__LINE__); \
          } \
        while (exchange_incomplete); \
      }

# define EXCHANGE_SVAR_ALL_FACE_MESSAGE(d,dm_flags) \
  if (MULTIPLE_COMPUTE_NODE_P)                      \
      { \
        cxboolean exchange_incomplete = FALSE;  \
        do  \
          { \
            const char *print_flags = #dm_flags; \
            exchange_incomplete = Set_Svar_Messages dm_flags; \
            Exchange_Svar_All_Face_Messages(d,print_flags,__FILE__,__LINE__); \
          } \
        while (exchange_incomplete);\
      }

# define EXCHANGE_SVAR_ALL_FACE_MESSAGE_EXT(d,dm_flags) \
  if (MULTIPLE_COMPUTE_NODE_P)                      \
      { \
        cxboolean exchange_incomplete = FALSE;  \
        do  \
          { \
            const char *print_flags = #dm_flags; \
            exchange_incomplete = Set_Svar_Messages dm_flags; \
            Exchange_Svar_All_Face_Messages_Ext(d,print_flags,__FILE__,__LINE__); \
          } \
        while (exchange_incomplete);\
      }

# define EXCHANGE_SVAR_FACE_MESSAGE(d,dm_flags) \
      if (MULTIPLE_COMPUTE_NODE_P) \
      { \
        cxboolean exchange_incomplete = FALSE;  \
        cxboolean use_new_exchange_api_ = RP_Get_Boolean("parallel/use-exchange-face-shadow-svar-message?");\
        do  \
          { \
            const char *print_flags = #dm_flags; \
            exchange_incomplete = Set_Svar_Messages dm_flags; \
            if (use_new_exchange_api_)\
            {\
              Exchange_Svar_Face_And_Shadow_Messages(d,print_flags,__FILE__,__LINE__); \
            }\
            else\
            {\
              Exchange_Svar_Face_Messages(d,print_flags,__FILE__,__LINE__); \
            }\
          } \
        while (exchange_incomplete);\
      }
#define EXCHANGE_SVAR_FACE_AND_SHADOW_MESSAGE(d,dm_flags) \
      if (MULTIPLE_COMPUTE_NODE_P) \
      { \
         cxboolean exchange_incomplete = FALSE; \
         do \
         { \
            const char *print_flags = #dm_flags; \
            exchange_incomplete = Set_Svar_Messages dm_flags; \
            Exchange_Svar_Face_And_Shadow_Messages(d,print_flags,__FILE__,__LINE__); \
         } \
         while (exchange_incomplete); \
      }



# define EXCHANGE_SVAR_IFACE_MESSAGE(d,dm_flags) \
      if (MULTIPLE_COMPUTE_NODE_P) \
      { \
        cxboolean exchange_incomplete = FALSE;  \
        do  \
          { \
            const char *print_flags = #dm_flags; \
            exchange_incomplete = Set_Svar_Messages dm_flags; \
            Exchange_Svar_IFace_Messages(d,print_flags,__FILE__,__LINE__); \
          } \
        while (exchange_incomplete);\
      }

#if RP_3D
# define EXCHANGE_SVAR_BFACE_MESSAGE(d,dm_flags) \
      if (MULTIPLE_COMPUTE_NODE_P) \
      { \
        cxboolean exchange_incomplete = FALSE;  \
        do  \
          { \
            const char *print_flags = #dm_flags; \
            exchange_incomplete = Set_Svar_Messages dm_flags; \
            Exchange_Svar_BFace_Messages(d,print_flags,__FILE__,__LINE__); \
          } \
        while (exchange_incomplete);\
      }
#else
# define EXCHANGE_SVAR_BFACE_MESSAGE(d,dm_flags)
#endif

# if RP_OVERSET
# define EXCHANGE_SVAR_OFACE_MESSAGE(d,dm_flags) \
      if (MULTIPLE_COMPUTE_NODE_P) \
      { \
        cxboolean exchange_incomplete = FALSE;  \
        do  \
          { \
            const char *print_flags = #dm_flags; \
            exchange_incomplete = Set_Svar_Messages dm_flags; \
            Exchange_Svar_OFace_Messages(d,print_flags,__FILE__,__LINE__); \
          } \
        while (exchange_incomplete);\
      }
# define EXCHANGE_SVAR_DONOR_MESSAGE(d, dm_flags) \
      if (MULTIPLE_COMPUTE_NODE_P) \
      { \
        cxboolean exchange_incomplete = FALSE;  \
        do  \
          { \
            const char *print_flags = #dm_flags; \
            exchange_incomplete = Set_Svar_Messages dm_flags; \
            Exchange_Svar_Donor_Messages(d,print_flags,__FILE__,__LINE__); \
          } \
        while (exchange_incomplete);\
      }

# define EXCHANGE_SVAR_RECEPTOR_MESSAGE(d, dm_flags) \
      if (MULTIPLE_COMPUTE_NODE_P) \
       { \
        cxboolean exchange_incomplete = FALSE;  \
        do  \
          { \
            const char *print_flags = #dm_flags; \
            exchange_incomplete = Set_Svar_Messages dm_flags; \
            Exchange_Svar_Receptor_Messages(d,print_flags,__FILE__,__LINE__); \
          } \
        while (exchange_incomplete);\
      }

# endif

# define EXCHANGE_SVAR_NODE_MESSAGE(d,dm_flags) \
      if (MULTIPLE_COMPUTE_NODE_P) \
      { \
        cxboolean exchange_incomplete = FALSE;  \
        do  \
          { \
            const char *print_flags = #dm_flags; \
            exchange_incomplete = Set_Svar_Messages dm_flags; \
            Exchange_Svar_Node_Messages(d,print_flags,__FILE__,__LINE__); \
          } \
        while (exchange_incomplete);\
      }
# define EXCHANGE_SVAR_NODE_MESSAGE_OP(d,op,dm_flags) \
      if (MULTIPLE_COMPUTE_NODE_P) \
      { \
        cxboolean exchange_incomplete = FALSE;  \
        do  \
          { \
            const char *print_flags = #dm_flags; \
            exchange_incomplete = Set_Svar_Messages dm_flags; \
            Exchange_Svar_Node_Messages_Op(d,op,print_flags,__FILE__,__LINE__); \
          } \
        while (exchange_incomplete);\
      }

# define EXCHANGE_RVAR_MESSAGE(d,dm_flags) \
    do \
      { \
        if (MULTIPLE_COMPUTE_NODE_P) \
          { \
            const char *print_flags = #dm_flags; \
            Set_Rvar_Messages dm_flags; \
            Exchange_Svar_Messages(d,print_flags,__FILE__,__LINE__); \
          } \
      } \
    while (0)

# define EXCHANGE_RVAR_MESSAGE_EXT(d,dm_flags) \
    do \
      { \
        if (MULTIPLE_COMPUTE_NODE_P) \
          { \
            const char *print_flags = #dm_flags; \
            Set_Rvar_Messages dm_flags; \
            Exchange_Svar_Messages_Ext(d,print_flags,__FILE__,__LINE__); \
          } \
      } \
    while (0)
#else
# define EXCHANGE_UDMI(_d,_i1,_i2)
# define EXCHANGE_SVAR_MESSAGE(d,dm_flags)
# define EXCHANGE_SVAR_MESSAGE_ALL(d,dm_flags)
# define EXCHANGE_SVAR_MESSAGE_EXT(d,dm_flags)
# define EXCHANGE_SVAR_MESSAGE_ALL_EXT(d,dm_flags)
# define EXCHANGE_SVAR_FACE_MESSAGE(d,dm_flags)
# define EXCHANGE_SVAR_BFACE_MESSAGE(d,dm_flags)
# define EXCHANGE_SVAR_IFACE_MESSAGE(d,dm_flags)
# if RP_OVERSET
# define EXCHANGE_SVAR_OFACE_MESSAGE(d,dm_flags)
# define EXCHANGE_SVAR_DONOR_MESSAGE(d, dm_flags)
# define EXCHANGE_SVAR_RECEPTOR_MESSAGE(d, dm_flags)
# endif
# define EXCHANGE_SVAR_NODE_MESSAGE(d,dm_flags)
# define EXCHANGE_SVAR_NODE_MESSAGE_OP(d,op,dm_flags)
# define EXCHANGE_RVAR_MESSAGE(d,dm_flags)
# define EXCHANGE_RVAR_MESSAGE_EXT(d,dm_flags)
#endif /* RP_NODE */

#if RP_NODE
#define EXCHANGE_CELL_MARK(d) EXCHANGE_SVAR_MESSAGE_EXT(d,(SV_MARKING_REGISTER,SV_NULL))
#else
#define EXCHANGE_CELL_MARK(d)
#endif


/**********************************************************
 *
 * Loop macros
 *
 **********************************************************/

/* face thread loops */
#if RP_NODE

# define begin_face_thread_loop(t,d,dm_flags) \
  { \
    if (MPT_Trace()) MPT_debug("begin_face_thread_loop",__FILE__,__LINE__,""); \
    thread_loop_f (t,d) \
      {

# define end_face_thread_loop(d) \
       } \
  }

#else

# define begin_face_thread_loop(t,d,dm_flags) thread_loop_f (t,d)
# define end_face_thread_loop(d)

#endif /* RP_NODE */

/* Wrappers for timers.
 * Usage/format (the braces are required):
 *
 *   {
 *     START_TIMER();
 *
 *     statement;
 *
 *     STOP_TIMER(element);
 *   }
 */

# define START_TIMER() double wall_clock = Get_Timer();

# define STOP_TIMER(timer)\
  { \
    double wall_clock_1; \
    wall_clock_1 = Get_Timer() - wall_clock; \
    (timer) += wall_clock_1; \
  }

#if PARALLEL

#if RP_DOUBLE
#  define host_to_node_real   host_to_node_double
#  define host_to_node_real_1 host_to_node_double_1
#  define host_to_node_real_2 host_to_node_double_2
#  define host_to_node_real_3 host_to_node_double_3
#  define host_to_node_real_4 host_to_node_double_4
#  define host_to_node_real_5 host_to_node_double_5
#  define host_to_node_real_6 host_to_node_double_6
#  define host_to_node_real_7 host_to_node_double_7
#  define host_to_node_real_8 host_to_node_double_8
#  define host_to_node_real_9 host_to_node_double_9
#  define node_to_host_real   node_to_host_double
#  define node_to_host_real_1 node_to_host_double_1
#  define node_to_host_real_2 node_to_host_double_2
#  define node_to_host_real_3 node_to_host_double_3
#  define node_to_host_real_4 node_to_host_double_4
#  define node_to_host_real_5 node_to_host_double_5
#  define node_to_host_real_6 node_to_host_double_6
#  define node_to_host_real_7 node_to_host_double_7
#else /* RP_DOUBLE */
#  define host_to_node_real   host_to_node_float
#  define host_to_node_real_1 host_to_node_float_1
#  define host_to_node_real_2 host_to_node_float_2
#  define host_to_node_real_3 host_to_node_float_3
#  define host_to_node_real_4 host_to_node_float_4
#  define host_to_node_real_5 host_to_node_float_5
#  define host_to_node_real_6 host_to_node_float_6
#  define host_to_node_real_7 host_to_node_float_7
#  define host_to_node_real_8 host_to_node_float_8
#  define host_to_node_real_9 host_to_node_float_9
#  define node_to_host_real   node_to_host_float
#  define node_to_host_real_1 node_to_host_float_1
#  define node_to_host_real_2 node_to_host_float_2
#  define node_to_host_real_3 node_to_host_float_3
#  define node_to_host_real_4 node_to_host_float_4
#  define node_to_host_real_5 node_to_host_float_5
#  define node_to_host_real_6 node_to_host_float_6
#  define node_to_host_real_7 node_to_host_float_7
#endif /* RP_DOUBLE */

#endif /* PARALLEL */

#if USE_INT64
#if _NT
# define node_to_host_index_1 node_to_host_long_long_1
# define node_to_host_index_2 node_to_host_long_long_2
# define node_to_host_index_3 node_to_host_long_long_3
# define node_to_host_index_4 node_to_host_long_long_4
# define node_to_host_index_5 node_to_host_long_long_5
# define node_to_host_index_6 node_to_host_long_long_6
# define node_to_host_index_7 node_to_host_long_long_7
# define node_to_host_index   node_to_host_long_long
# define host_to_node_index_1 host_to_node_long_long_1
# define host_to_node_index_2 host_to_node_long_long_2
# define host_to_node_index_3 host_to_node_long_long_3
# define host_to_node_index_4 host_to_node_long_long_4
# define host_to_node_index_5 host_to_node_long_long_5
# define host_to_node_index_6 host_to_node_long_long_6
# define host_to_node_index_7 host_to_node_long_long_7
# define host_to_node_index   host_to_node_long_long
#else
# define node_to_host_index_1 node_to_host_long_1
# define node_to_host_index_2 node_to_host_long_2
# define node_to_host_index_3 node_to_host_long_3
# define node_to_host_index_4 node_to_host_long_4
# define node_to_host_index_5 node_to_host_long_5
# define node_to_host_index_6 node_to_host_long_6
# define node_to_host_index_7 node_to_host_long_7
# define node_to_host_index   node_to_host_long
# define host_to_node_index_1 host_to_node_long_1
# define host_to_node_index_2 host_to_node_long_2
# define host_to_node_index_3 host_to_node_long_3
# define host_to_node_index_4 host_to_node_long_4
# define host_to_node_index_5 host_to_node_long_5
# define host_to_node_index_6 host_to_node_long_6
# define host_to_node_index_7 host_to_node_long_7
# define host_to_node_index   host_to_node_long
#endif
#else
# define node_to_host_index_1 node_to_host_int_1
# define node_to_host_index_2 node_to_host_int_2
# define node_to_host_index_3 node_to_host_int_3
# define node_to_host_index_4 node_to_host_int_4
# define node_to_host_index_5 node_to_host_int_5
# define node_to_host_index_6 node_to_host_int_6
# define node_to_host_index_7 node_to_host_int_7
# define node_to_host_index   node_to_host_int
# define host_to_node_index_1 host_to_node_int_1
# define host_to_node_index_2 host_to_node_int_2
# define host_to_node_index_3 host_to_node_int_3
# define host_to_node_index_4 host_to_node_int_4
# define host_to_node_index_5 host_to_node_int_5
# define host_to_node_index_6 host_to_node_int_6
# define host_to_node_index_7 host_to_node_int_7
# define host_to_node_index   host_to_node_int
#endif

#if DEBUG_PARALLEL
extern FLUENT_EXPORT void Debug_Par(const char *, int );
extern FLUENT_EXPORT void Debug_Cell(const char *, int);
extern FLUENT_EXPORT void Debug_Part(const char *, int);
extern FLUENT_EXPORT void Debug_Face(const char *, int);
# define DEBUG_PAR() Debug_Par(__FILE__, __LINE__)
# define DEBUG_PART() Debug_Part(__FILE__,__LINE__)
# define DEBUG_CELL() Debug_Cell(__FILE__,__LINE__)
# define DEBUG_FACE() Debug_Face(__FILE__,__LINE__)
# define OPEN_DEBUG_FILE() Open_Debug_File()
#elif PARALLEL
# define DEBUG_PAR()
# define DEBUG_PART()
# define DEBUG_CELL()
# define DEBUG_FACE()
# define OPEN_DEBUG_FILE()
#endif

extern FLUENT_EXPORT FILE *fpdeb;
extern FLUENT_EXPORT void Open_Debug_File(void);
extern FLUENT_EXPORT void fill_loadvec(float *, int);

FLUENT_EXPORT void Parallel_Next_Value(void);

#define PACK_OFFSET_FLOAT_ 100000
#define PACK_INT_2_FLOAT_SIZE 2
#define PACK_INT_2_FLOAT(int_number,buf)                                 \
  { (buf)[0] = (int_number)%PACK_OFFSET_FLOAT_;                               \
    (buf)[1] = (int_number)/PACK_OFFSET_FLOAT_ + ((int_number)>0?0.1:(-0.1));}
#define UNPACK_INT_2_FLOAT(int_number,buf)                               \
  { (int_number) = (cxindex)((buf)[0]) + ((cxindex)((buf)[1])) * PACK_OFFSET_FLOAT_;}


#if RP_DOUBLE
#define PACK_INT_2_REAL_SIZE 1
#define PACK_INT_2_REAL(int_number,buf)                         \
  {(buf)[0] = (int_number) + ((int_number)>0?0.1:(-0.1));}
#define UNPACK_INT_2_REAL(int_number,buf)       \
  {(int_number) = (cxindex)((buf)[0]);}
#define PACK_INT_2_REAL_WITH_INDEX(int_number,buf,index)        \
  {PACK_INT_2_REAL((int_number),&((buf)[index])); (index)+=1;}
#define UNPACK_INT_2_REAL_WITH_INDEX(int_number,buf,index)              \
  {UNPACK_INT_2_REAL((int_number),&((buf)[index])); (index)+=1;}
#define PACK_INT_2_REAL_WITH_ADDRESS(int_number,buf)    \
  {PACK_INT_2_REAL((int_number),(buf)); (buf)+=1;}
#define UNPACK_INT_2_REAL_WITH_ADDRESS(int_number,buf)  \
  {UNPACK_INT_2_REAL((int_number),(buf)); (buf)+=1;}
#define PACK_OFFSET_ 10000000000
#define PACK_LONG_2_REAL_SIZE 2
#define PACK_LONG_2_REAL(long_number,buf) \
  { (buf)[0] = (long_number) % PACK_OFFSET_ + ((long_number) > 0 ? 0.1 : -0.1); \
    (buf)[1] = (long_number/PACK_OFFSET_) + ((long_number) > 0 ? 0.1 : -0.1); }
#define UNPACK_LONG_2_REAL(long_number,buf) \
  { (long_number) = (int64_t)((buf)[0]) + ((int64_t)((buf)[2])) * PACK_OFFSET_; }
#define PACK_LONG_2_REAL_WITH_ADDRESS(long_number,buf)    \
  { PACK_LONG_2_REAL((long_number),(buf)); (buf)+=2; }
#define UNPACK_LONG_2_REAL_WITH_ADDRESS(long_number,buf)  \
  { UNPACK_LONG_2_REAL((long_number),(buf)); (buf)+=2; }
#else
#define PACK_OFFSET_ 100000
#define PACK_INT_2_REAL_SIZE PACK_INT_2_FLOAT_SIZE
#define PACK_INT_2_REAL(int_number,buf)                                 \
  { (buf)[0] = (int_number)%PACK_OFFSET_;                               \
    (buf)[1] = (int_number)/PACK_OFFSET_ + ((int_number)>0?0.1:(-0.1));}
#define UNPACK_INT_2_REAL(int_number,buf)                               \
  { (int_number) = (cxindex)((buf)[0]) + ((cxindex)((buf)[1])) * PACK_OFFSET_;}
#define PACK_INT_2_REAL_WITH_INDEX(int_number,buf,index)        \
  {PACK_INT_2_REAL((int_number),&((buf)[index])); (index)+=2;}
#define UNPACK_INT_2_REAL_WITH_INDEX(int_number,buf,index)              \
  {UNPACK_INT_2_REAL((int_number),&((buf)[index])); (index)+=2;}
#define PACK_INT_2_REAL_WITH_ADDRESS(int_number,buf)    \
  {PACK_INT_2_REAL((int_number),(buf)); (buf)+=2;}
#define UNPACK_INT_2_REAL_WITH_ADDRESS(int_number,buf)  \
  {UNPACK_INT_2_REAL((int_number),(buf)); (buf)+=2;}
#define PACK_LONG_2_REAL_SIZE 4
#define PACK_LONG_2_REAL(long_number,buf) \
  { (buf)[0] = (long_number) % PACK_OFFSET_ + ((long_number) > 0 ? 0.1 : -0.1); \
    (buf)[1] = (long_number/PACK_OFFSET_) % PACK_OFFSET_ + ((long_number) > 0 ? 0.1 : -0.1); \
    (buf)[2] = (long_number/PACK_OFFSET_/PACK_OFFSET_) % PACK_OFFSET_ + ((long_number) > 0 ? 0.1 : -0.1); \
    (buf)[3] = (long_number/PACK_OFFSET_/PACK_OFFSET_/PACK_OFFSET_) + ((long_number) > 0 ? 0.1 : -0.1); }
#define UNPACK_LONG_2_REAL(long_number,buf) \
  { (long_number) = (int64_t)((buf)[0]) + (((int64_t)((buf)[1])) + (((int64_t)((buf)[2])) + ((int64_t)((buf)[3])) * PACK_OFFSET_) * PACK_OFFSET_) * PACK_OFFSET_; }
#define PACK_LONG_2_REAL_WITH_ADDRESS(long_number,buf)    \
  { PACK_LONG_2_REAL((long_number),(buf)); (buf) += 4; }
#define UNPACK_LONG_2_REAL_WITH_ADDRESS(long_number,buf)  \
  { UNPACK_LONG_2_REAL((long_number),(buf)); (buf) += 4; }
#endif

FLUENT_EXPORT FILE *par_fopen(const char *, const char *, int, int);
FLUENT_EXPORT int par_fprintf(FILE *, const char *, ...);
FLUENT_EXPORT int par_fprintf_head(FILE *, const char *, ...);
FLUENT_EXPORT int par_fclose(FILE *);
FLUENT_EXPORT void par_fsort(FILE *, FILE *, int, int);

#ifndef USE_FLUENT_PROFILE
# define USE_FLUENT_PROFILE 1
#endif

/* this has been defined in mport.h, but serial will not include mport.h */
#if !PARALLEL
#include "mptimer.h"
#endif /* !PARALLEL */

/* macros for parallel MPE logging */
#if USE_FLUENT_PROFILE_FOR_MPE_LOG
# define START_MPE_LOG(name,color)  START_PROFILE(name)
# define STOP_MPE_LOG(name)  STOP_PROFILE(name)
#else
# define START_MPE_LOG(name,color)
# define STOP_MPE_LOG(name)
#endif /* USE_FLUENT_PROFILE_FOR_MPE_LOG */

/* functions used to print out messages by host */
#if RP_NODE
extern FLUENT_EXPORT int hprintf(const char *format, ... );
extern FLUENT_EXPORT int hprintf0(const char *format, ... );
#else
#define hprintf Message
#define hprintf0 Message0
#endif /* RP_NODE */

#if PARALLEL
extern FLUENT_EXPORT void hflush(void);
extern FLUENT_EXPORT void hflush0(void);
#else
#define hflush() {fflush(stdout); fflush(stderr);}
#define hflush0() {fflush(stdout); fflush(stderr);}
#endif /* PARALLEL && _NT */

#if FPRINT_DEBUG
#define fprint_int(i)                                           \
  {                                                             \
    char fname[32];                                             \
    FILE *fp = NULL;                                            \
    sprintf(fname, "print-%d.dat", myid);                       \
    fp = fopen(fname, "a");                                     \
    if(fp)                                                      \
      {                                                         \
        fprintf(fp, "\n%d: %s = %d (%s:%d)", myid, #i, i,       \
                __FILE__, __LINE__);                            \
        fclose(fp);                                             \
      }                                                         \
    else                                                        \
      {                                                         \
        fprintf(stderr, "\n%d: %s = %d (%s:%d)", myid, #i, i,   \
                __FILE__, __LINE__);                            \
        fflush(stderr);                                         \
      }                                                         \
  }
#else
#define fprint_int(i)
#endif

extern const char *take_away_path(const char *file);
#define print_int1(i) \
{\
  fprintf(stderr, "\n%d: %s = %ld (%s:%d)", myid, #i, i, take_away_path(__FILE__), __LINE__);\
  fflush(stderr);\
}

#define print_int2(i1,i2)                         \
{\
  fprintf(stderr, "\n%d: %s = %ld %s = %ld (%s:%d)", \
          myid, #i1, i1, #i2, i2, take_away_path(__FILE__), __LINE__);   \
  fflush(stderr);\
}

#define print_int3(i1,i2,i3)                      \
{\
  fprintf(stderr, "\n%d: %s = %ld %s = %ld %s = %ld (%s:%d)", \
          myid, #i1, i1, #i2, i2, #i3, i3, take_away_path(__FILE__), __LINE__);   \
  fflush(stderr);\
}

#define print_int4(i1,i2,i3,i4)                   \
{\
  fprintf(stderr, "\n%d: %s = %ld %s = %ld %s = %ld %s = %ld (%s:%d)", \
          myid, #i1, i1, #i2, i2, #i3, i3, #i4, i4, take_away_path(__FILE__), __LINE__);   \
  fflush(stderr);\
}

#define print_int5(i1,i2,i3,i4,i5)              \
{\
  fprintf(stderr, "\n%d: %s = %ld %s = %ld %s = %ld %s = %ld %s =%ld (%s:%d)",\
          myid, #i1, i1, #i2, i2, #i3, i3, #i4, i4, #i5, i5, take_away_path(__FILE__), __LINE__);   \
  fflush(stderr);\
}

FLUENT_EXPORT FILE *open_node_file(const char *name, const char *mode);

#if LM_TRACE


#if PARALLEL
#define print_follow_up_in_console (myid==node_zero)
#else
#define print_follow_up_in_console 1
#endif


#define sprint_int1(buf,i) \
{\
  sprintf(buf, "\n%d: %s = %ld (%s:%d)", myid, #i, (long)i, __FILE__, __LINE__); \
}

#define sprint_int2(buf,i1,i2)                         \
{\
  sprintf(buf, "\n%d: %s = %ld %s = %ld (%s:%d)", \
          myid, #i1, (long)i1, #i2, (long)i2, __FILE__, __LINE__);   \
}

#define sprint_int3(buf,i1,i2,i3)                      \
{\
  sprintf(buf, "\n%d: %s = %ld %s = %ld %s = %ld (%s:%d)", \
          myid, #i1, (long)i1, #i2, (long)i2, #i3, (long)i3, __FILE__, __LINE__);   \
}

#define sprint_int4(buf,i1,i2,i3,i4)                   \
{\
  sprintf(buf, "\n%d: %s = %ld %s = %ld %s = %ld %s = %ld (%s:%d)", \
          myid, #i1, (long)i1, #i2, (long)i2, #i3, (long)i3, #i4, (long)i4, __FILE__, __LINE__);   \
}

#define sprint_int5(buf,i1,i2,i3,i4,i5)              \
{\
  sprintf(buf, "\n%d: %s = %ld %s = %ld %s = %ld %s = %ld %s =%ld (%s:%d)",\
          myid, #i1, (long)i1, #i2, (long)i2, #i3, (long)i3, #i4, (long)i4, #i5, (long)i5, __FILE__, __LINE__);   \
}

#define LMTRACE_STR(s) if(if_lm_trace){                                 \
    static int fcount = 0;                                              \
    follow_up(__FUNCTION__, __FILE__, __LINE__, " ", fcount, s);        \
    fcount++;                                                           \
  }

#define LMTRACE_INT1(i1) if(if_lm_trace){                               \
    static int fcount = 0;                                              \
    char info[512];                                                    \
    sprint_int1(info,i1);                                               \
    follow_up(__FUNCTION__, __FILE__, __LINE__, " ", fcount, info);     \
    fcount++;                                                           \
  }
#define LMTRACE_INT2(i1,i2) if(if_lm_trace){                            \
    static int fcount = 0;                                              \
    char info[512];                                                    \
    sprint_int2(info,i1,i2);                                            \
    follow_up(__FUNCTION__, __FILE__, __LINE__, " ", fcount, info);     \
    fcount++;                                                           \
  }
#define LMTRACE_INT3(i1,i2,i3) if(if_lm_trace){                         \
    static int fcount = 0;                                              \
    char info[512];                                                    \
    sprint_int3(info,i1,i2,i3);                                         \
    follow_up(__FUNCTION__, __FILE__, __LINE__, " ", fcount, info);     \
    fcount++;                                                           \
  }
#define LMTRACE_INT4(i1,i2,i3,i4) if(if_lm_trace){                      \
    static int fcount = 0;                                              \
    char info[512];                                                    \
    sprint_int4(info,i1,i2,i3,i4);                                      \
    follow_up(__FUNCTION__, __FILE__, __LINE__, " ", fcount, info);     \
    fcount++;                                                           \
  }
#define LMTRACE_INT5(i1,i2,i3,i4,i5) if(if_lm_trace){                   \
    static int fcount = 0;                                              \
    char info[512];                                                    \
    sprint_int5(info,i1,i2,i3,i4,i5);                                   \
    follow_up(__FUNCTION__, __FILE__, __LINE__, " ", fcount, info);     \
    fcount++;                                                           \
  }

#else

#define LMSTART
#define LMSTOP
#define LMTRACE_STR(s)
#define LMTRACE_INT1(i1)
#define LMTRACE_INT2(i1,i2)
#define LMTRACE_INT3(i1,i2,i3)
#define LMTRACE_INT4(i1,i2,i3,i4)
#define LMTRACE_INT5(i1,i2,i3,i4,i5)
#endif

#if PARALLEL || DEBUG_PARALLEL
extern FLUENT_EXPORT cxboolean get_node_arch(char **, const char *);
extern FLUENT_EXPORT cxboolean get_node_command(char **, const char *, const char *);
extern FLUENT_EXPORT void Ptrace_Begin(const char *, const char *, int);
extern FLUENT_EXPORT void Ptrace_End(void);
extern FLUENT_EXPORT void Ptrace_Reset(void);
# define PTRACE_BEGIN(fname) LMSTART;Ptrace_Begin(fname, __FILE__, __LINE__)
# define PTRACE_BEGIN_3(fname, file, line) LMSTART;Ptrace_Begin(fname, file, line)
# define PTRACE_END() LMSTOP;Ptrace_End()

extern FLUENT_EXPORT void Node_Idle_Wait_Host(void);
#endif /* PARALLEL || DEBUG_PARALLEL */

extern FLUENT_EXPORT int Have_Solid_Thread(Domain *);
extern FLUENT_EXPORT int Global_Mpi_Trace_Status(const char *, int, int);

#if PARALLEL && ! UDF_COMPILER
FLUENT_EXPORT void prf_csend_int64(int to, int64_t *v, unsigned int d, int tag);
FLUENT_EXPORT void prf_crecv_int64(int from, int64_t *v, unsigned int d, int tag);
FLUENT_EXPORT int64_t prf_gi64sum1(int64_t v);
FLUENT_EXPORT int64_t prf_gi64high1_with_host(int64_t v);
FLUENT_EXPORT void node_to_host_int64(int64_t *v, int len);
FLUENT_EXPORT void host_to_node_int64(int64_t *v, int len);
FLUENT_EXPORT void mphost_to_node_int64_1(int64_t *i0);
FLUENT_EXPORT void mphost_to_node_int64_2(int64_t *i0, int64_t *i1);
FLUENT_EXPORT void mpnode_to_host_int64_1(int64_t *i0);
FLUENT_EXPORT void mpnode_to_host_int64_2(int64_t *i0, int64_t *i1);
#define host_to_node_int64_1(i0) mphost_to_node_int64_1(&(i0))
#define host_to_node_int64_2(i0,i1) mphost_to_node_int64_2(&(i0),&(i1))
#define node_to_host_int64_1(i0) mpnode_to_host_int64_1(&(i0))
#define node_to_host_int64_2(i0,i1) mpnode_to_host_int64_2(&(i0),&(i1))
#endif

#if RP_NODE
FLUENT_EXPORT void Create_Thread_Comms(Domain *);
FLUENT_EXPORT int *Get_Node_Master(int **);
FLUENT_EXPORT parallel_virtual_machine_t *Get_Virtual_Machine(parallel_virtual_machine_t *vm);
FLUENT_EXPORT void Idle_Wait(int *);
FLUENT_EXPORT void Idle_Wait_All_Nodes(int *);
FLUENT_EXPORT int Get_Max_Allowable_Threads(cxboolean);

FLUENT_EXPORT void all_to_all_exchange_int(int *, int *);
FLUENT_EXPORT void all_to_all_test(void);
# define ALL_TO_ALL_EXCHANGE_INT(_s, _r)                \
  if (MULTIPLE_COMPUTE_NODE_P)                          \
    {                                                   \
      START_PROFILE_2("ALL_TO_ALL_EXCHANGE_INT");       \
      all_to_all_exchange_int(_s, _r);                  \
      STOP_PROFILE_2("ALL_TO_ALL_EXCHANGE_INT");        \
    }
#endif

extern FLUENT_EXPORT int Get_Num_Physical_Cores(void);
extern FLUENT_EXPORT int Get_MPP_Optimization_Status(void);
extern FLUENT_EXPORT void MPP_Optimization(cxboolean);
extern FLUENT_EXPORT void Use_Interactive_Session(int);
extern FLUENT_EXPORT void At_Exit(void);
extern FLUENT_EXPORT void Disable_Print_Stack_At_Exit(void);

/* chunked exchange */
FLUENT_EXPORT void
csendrecv_chunked(int ndest, void *data, cxindex size, int tag,
                  cxindex chunk_size, SV_Dimension dimension, cxboolean for_send);
#define PRF_CSEND_INDEX_CHUNKED(ndest, data, size, tag) csendrecv_chunked \
  (ndest, (void *)data, size, tag, 0, SV_DIM_INDEX, TRUE)
#define PRF_CSEND_INT_CHUNKED(ndest, data, size, tag) csendrecv_chunked \
  (ndest, (void *)data, size, tag, 0, SV_DIM_INT, TRUE)
#define PRF_CSEND_REAL_CHUNKED(ndest, data, size, tag) csendrecv_chunked \
  (ndest, (void *)data, size, tag, 0, SV_DIM_REAL, TRUE)

#define PRF_CRECV_INDEX_CHUNKED(ndest, data, size, tag) csendrecv_chunked \
  (ndest, (void *)data, size, tag, 0, SV_DIM_INDEX, FALSE)
#define PRF_CRECV_INT_CHUNKED(ndest, data, size, tag) csendrecv_chunked \
  (ndest, (void *)data, size, tag, 0, SV_DIM_INT, FALSE)
#define PRF_CRECV_REAL_CHUNKED(ndest, data, size, tag) csendrecv_chunked \
  (ndest, (void *)data, size, tag, 0, SV_DIM_REAL, FALSE)

#define CHECK_NULL_MEM(array)                                           \
  if (NULLP(array))                                                     \
    Error("\n%d: Failed to malloc %s in %s (%s:%d)\n", myid, #array,    \
          __FUNCTION__, __FILE__, __LINE__);

#if RP_NODE
# if RP_DOUBLE
#  define   prf_gather_real_even(rarray, sarray, n_longs, root) \
          prf_gather_double_even(rarray, sarray, n_longs, root)
#  define  prf_scatter_real_even(rarray, sarray, n_longs, root) \
         prf_scatter_double_even(rarray, sarray, n_longs, root)
# else
#  define   prf_gather_real_even(rarray, sarray, n_longs, root) \
           prf_gather_float_even(rarray, sarray, n_longs, root)
#  define  prf_scatter_real_even(rarray, sarray, n_longs, root) \
          prf_scatter_float_even(rarray, sarray, n_longs, root)
# endif


FLUENT_EXPORT void prf_gather_int_even(int *, int *, int, int);
FLUENT_EXPORT void prf_scatter_int_even(int *, int *, int, int);
FLUENT_EXPORT void prf_gather_long_even(long *, long *, int, int);
FLUENT_EXPORT void prf_scatter_long_even(long *, long *, int, int);
FLUENT_EXPORT void prf_gather_float_even(float *, float *, int, int);
FLUENT_EXPORT void prf_scatter_float_even(float *, float *, int, int);
FLUENT_EXPORT void prf_gather_double_even(double *, double *, int, int);
FLUENT_EXPORT void prf_scatter_double_even(double *, double *, int, int);
FLUENT_EXPORT void prf_gather_int64_even(int64_t *, int64_t *, int, int);
FLUENT_EXPORT void prf_scatter_int64_even(int64_t *, int64_t *, int, int);
FLUENT_EXPORT void prf_gather_char_even(char *, char *, int, int);
FLUENT_EXPORT void prf_scatter_char_even(char *, char *, int, int);
FLUENT_EXPORT void prf_gather_uchar_even(unsigned char *, unsigned char *, int, int);
FLUENT_EXPORT void prf_scatter_uchar_even(unsigned char *, unsigned char *, int, int);
FLUENT_EXPORT void prf_gather_uint_even(unsigned int *, unsigned int *, int, int);
FLUENT_EXPORT void prf_scatter_uint_even(unsigned int *, unsigned int *, int, int);
#if !UDF_COMPILER
FLUENT_EXPORT void prf_gather_long_long_even(long long *, long long *, int, int);
FLUENT_EXPORT void prf_scatter_long_long_even(long long *, long long *, int, int);
#endif
#endif /* RP_NODE */

#if !_NT && RP_NODE
FLUENT_EXPORT void Cache_Flush(size_t *);
FLUENT_EXPORT void Flush_Cache(size_t *);
FLUENT_EXPORT void Check_Cache(size_t *, size_t *, size_t *, size_t *, size_t *);
#endif

FLUENT_EXPORT void Kill_OMP_Threads(int);

#if !PARALLEL
# include "par_stubs.h"
#endif

#endif /* _FLUENT_PARA_H */
