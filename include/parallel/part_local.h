
/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_PART_LOCAL_H
#define _FLUENT_PART_LOCAL_H

extern void
METIS_PartGraphRecursive
(idxtype *nvtxs, idxtype *xadj, idxtype *adjncy, idxtype *vwgt, idxtype *adjwgt,
 idxtype *wgtflag, idxtype *numflag, idxtype *nparts, idxtype *options, idxtype *edgecut,
 idxtype *part);

extern void
METIS_PartGraphKway
(idxtype *nvtxs, idxtype *xadj, idxtype *adjncy, idxtype *vwgt, idxtype *adjwgt,
 idxtype *wgtflag, idxtype *numflag, idxtype *nparts, idxtype *options, idxtype *edgecut,
 idxtype *part);

extern void
METIS_WPartGraphRecursive
(idxtype *nvtxs, idxtype *xadj, idxtype *adjncy, idxtype *vwgt, idxtype *adjwgt,
 idxtype *wgtflag, idxtype *numflag, idxtype *nparts, realtype *tpwgts, idxtype *options,
 idxtype *edgecut, idxtype *part);

extern void
METIS_WPartGraphKway
(idxtype *nvtxs, idxtype *xadj, idxtype *adjncy, idxtype *vwgt, idxtype *adjwgt,
 idxtype *wgtflag, idxtype *numflag, idxtype *nparts, realtype *tpwgts, idxtype *options,
 idxtype *edgecut, idxtype *part);

extern int
METIS_PartGraphKway_V3
(idxtype *nvtxs, idxtype *ncon, idxtype *xadj, idxtype *adjncy,
 idxtype *vwgt, idxtype *vsize, idxtype *adjwgt, idxtype *nparts,
 realtype *tpwgts, realtype *ubvec, idxtype *options, idxtype *objval,
 idxtype *part);


#if RP_NODE

extern void
ParMETIS_PartGeomKway
(idxtype *vtxdist, idxtype *xadj, idxtype *adjncy, idxtype *vwgt,
 idxtype *adjwgt, idxtype *wgtflag, idxtype *numflag, idxtype *ndims, realtype *xyz,
 idxtype *nparts, idxtype *options, idxtype *edgecut, idxtype *part, void *comm);
#define USE_PARMETIS_V3 1
#if USE_PARMETIS_V3
extern void
ParMETIS_V3_PartKway
(idxtype *vtxdist, idxtype *xadj, idxtype *adjncy, idxtype *vwgt,
 idxtype *adjwgt, idxtype *wgtflag, idxtype *numflag, idxtype *ncon, idxtype *nparts,
 realtype *tpwgts, realtype *ubvec, idxtype *options, idxtype *edgecut, idxtype *part,
 void *comm);

extern void
ParMETIS_V3_PartGeom
(idxtype *vtxdist, idxtype *ndims, realtype *xyz, idxtype *part, void *comm);

extern void
ParMETIS_V3_AdaptiveRepart
(idxtype *vtxdist, idxtype *xadj, idxtype *adjncy, idxtype *vwgt,
 idxtype *vsize, idxtype *adjwgt, idxtype *wgtflag, idxtype *numflag, idxtype *ncon, int *nparts,
 realtype *tpwgts, realtype *ubvec, realtype *itr, idxtype *options, idxtype *edgecut, idxtype *part,
 void *comm);

#else
#define ParMETIS_V3_PartKway ParMETIS_PartKway
extern void
ParMETIS_PartKway
(idxtype *vtxdist, idxtype *xadj, idxtype *adjncy, idxtype *vwgt,
 idxtype *adjwgt, idxtype *wgtflag, idxtype *numflag, idxtype *nparts,
 idxtype *options, idxtype *edgecut, idxtype *part, void *comm);
#endif

/* This part is from Metis (metislib/include/metis.h) */
typedef enum
{
  METIS_OPTION_PTYPE,
  METIS_OPTION_OBJTYPE,
  METIS_OPTION_CTYPE,
  METIS_OPTION_IPTYPE,
  METIS_OPTION_RTYPE,
  METIS_OPTION_DBGLVL,
  METIS_OPTION_NITER,
  METIS_OPTION_NCUTS,
  METIS_OPTION_SEED,
  METIS_OPTION_NO2HOP,
  METIS_OPTION_MINCONN,
  METIS_OPTION_CONTIG,
  METIS_OPTION_COMPRESS,
  METIS_OPTION_CCORDER,
  METIS_OPTION_PFACTOR,
  METIS_OPTION_NSEPS,
  METIS_OPTION_UFACTOR,
  METIS_OPTION_NUMBERING,

  /* Used for command-line parameter purposes */
  METIS_OPTION_HELP,
  METIS_OPTION_TPWGTS,
  METIS_OPTION_NCOMMON,
  METIS_OPTION_NOOUTPUT,
  METIS_OPTION_BALANCE,
  METIS_OPTION_GTYPE,
  METIS_OPTION_UBVEC
} fl_moptions_et;


#endif /* RP_NODE */

typedef struct part_struct
{
  int *ncell_in_p;      /* number of cells in partition */
  int *id;              /* partition id */
  cxindex ncell_alloc;      /* number of cells arrays can accommodate */
  cxindex ncell;            /* number of cells in arrays (<= ncell_alloc) */
  int npart;            /* number of partitions */
  cxindex ncell_global;
  int p;                /* partition id to repartition */
  cxboolean across_zones; /* partition across zone boundaries? */
  cxboolean ignore_model_weight;
  cxboolean only_dpm_weight;
}
Parts;

typedef struct part_function_struct
{
  char *pick;
  char *name;           /* printing name */
  void (*partsetup)();  /* partition setup function */
  void (*partfill)();   /* partition fill function */
  cxboolean recurse;      /* recusive bisection? */
  cxboolean (*enable)();  /* enabling flag  */
  cxboolean pretest;      /* pre-test flag */
  cxboolean must_pretest; /* pre-test not optional */
}
PART_FUNCTION;

#if RP_NODE

/* could be changed to array of size[numpartitions][max_neighbors]
*/

typedef struct partition_neighbor_id_linked_list
{
  int neighbor;
  struct partition_neighbor_id_linked_list *next;
} neighbor_id_list;

#endif

extern PART_FUNCTION *lookup_part_function(char *pick);

#define MEM_CHECK_WITH_GBOR(_p)                                         \
  if(PRF_GBOR1(NULLP(_p)))                                              \
    {                                                                   \
      Error("\nFailed to allocate memory @ %s:%d\n",__FILE__, __LINE__); \
    }

#define MEM_CHECK(_p, _size)                                            \
  if(NULLP(_p))                                                         \
    {                                                                   \
      Error("\nFailed to allocate memory %gMB %s:%d\n",                 \
            (_size)/1024.0/1024.0,                                      \
            __FILE__, __LINE__);                                        \
    }

#if !RP_HOST
#if RP_METIS
extern FLUENT_EXPORT void set_c_part_all(Domain *domain, Thread *t,
#if RP_NODE
                                         cxindex start,
#endif
                                         idxtype *part);
#endif /* RP_METIS */
#endif /* RP_HOST  */

#if !RP_HOST
#if RP_METIS
extern FLUENT_EXPORT int
set_c_metis_index(int *pcounter, Thread *t, Domain *domain,
                  int marked);

extern FLUENT_EXPORT void
partition_metis(Domain *domain, Thread *t, Parts *parts, PART_FUNCTION *fnc,
                float *loadvec,
#if RP_NODE
                void (*parmetis_fnc)(), cxboolean need_load_balance,
                cxboolean if_agglomerate,
#endif
                int verbosity, int marker);

#endif /* RP_METIS */

#endif /* RP_HOST  */

extern FLUENT_EXPORT int
get_nmachines(void);

extern FLUENT_EXPORT int require_weighting
(Domain *domain);

extern FLUENT_EXPORT void
set_cell_svar_value(Domain *domain, int var, int value, int nosolve);

extern FLUENT_EXPORT int
find_cell_weight(cell_t cell, Thread *thread);


#if !RP_HOST
#if RP_METIS

extern int
metis_form_xadj(Domain *domain, Thread *t,
                idxtype *xadj, int vertices, cxindex cell_start);

extern int
metis_form_adjncy(Domain *domain, Thread *t, idxtype *xadj, idxtype *adjncy,
                  idxtype cell_start, int consider_fw);

extern int
fill_metis_xadj_face(cell_t cell, Thread *cthread,
                     face_t face, Thread *thread,
                     idxtype *xadj, cxindex cell_start,
                     Thread *ct_original, int consider_fw,
                     int metis_edge_max);

extern int
fill_metis_adjncy_face(cell_t cell, Thread *cthread,
                       face_t face, Thread *thread,
                       idxtype *xadj, cxindex cell_start,
                       idxtype *adjncy, int *counter,
                       Thread *ct_original, int consider_fw,
                       int metis_edge_max);

#endif /* !RP_HOST */
#endif /* RP_METIS */


extern int
sum_face_weight(Domain *domain);

#if RP_NODE
#if RP_METIS
extern FLUENT_EXPORT void
metis_form_xyz(Domain *domain, Thread *t,
               cxindex start, realtype *xyz);

#endif /* RP_METIS */
#endif /* RP_NODE */

extern FLUENT_EXPORT void Invoke_Metis(metis_t *);

extern FLUENT_EXPORT void
add_model_weights(Domain *domain, metis_t *metis);

extern FLUENT_EXPORT void
add_model_weights_new(Domain *domain, metis_t *metis);

extern FLUENT_EXPORT int
add_face_weight(Domain *domain, metis_t *metis, cxindex cell_start);

extern FLUENT_EXPORT cxboolean
sv_initialized_p(Domain *domain, Svar sv);

extern FLUENT_EXPORT void
scale_weights_dpm(Domain *domain, idxtype icon);

extern FLUENT_EXPORT void
rescale_weights(Domain *domain, idxtype icon);

extern FLUENT_EXPORT void
add_weights_to_metis(Domain *domain, metis_t *metis, idxtype icon,
                     cxindex cell_start, cxboolean use_kid_weight);

/* new banded partitioning method */
extern FLUENT_EXPORT void
partition_cells_in_band_new(int npart, int band,
                            cxboolean ignore_model_weight, cxboolean only_dpm_weight,
                            Domain *domain);

extern FLUENT_EXPORT void
copy_int_to_idxtype(int *src, idxtype *dest, int size);

extern  FLUENT_EXPORT void
metis_graph_part(metis_t *);

extern  FLUENT_EXPORT void
metis_set_loadvec(metis_t *metis, float *loadvec);

extern  FLUENT_EXPORT void
metis_set_tpwgts(metis_t *metis);

extern  FLUENT_EXPORT void
metis_set_ubvec(realtype *ubvec, idxtype ncon);

extern FLUENT_EXPORT void
restrict_or_reset_MWP(Domain *domain, cxboolean if_banded, cxboolean restrict_flag);

extern FLUENT_EXPORT void
get_distribution_and_filter_weights(Domain *domain);

extern FLUENT_EXPORT int
filter_weights(Domain *domain, metis_t *metis);

#if RP_NODE
extern FLUENT_EXPORT void
insert_neighbor(neighbor_id_list **neighbor_p0, neighbor_id_list **neighbor_p1,
                int p0, int p1);
#endif

typedef struct histogram_struct
{
  int nbins;              /* number of bins                  */
  real min;               /* min value                       */
  real max;               /* max value of the bin            */
  cxboolean linspacing;   /* #t = linear, #f = log spacing   */
  real *bins;             /* bins                            */
  cxindex *val;           /* histogram                       */
} Hist;

extern FLUENT_EXPORT void
fill_histogram(Domain *domain, Hist *hist, real (*hist_fill_func)(cell_t, Thread *));

extern FLUENT_EXPORT void
fill_histogram_metis(metis_t *metis, Hist *hist, idxtype icon);

extern FLUENT_EXPORT void
alloc_histogram(Hist *hist, int verbosity);

extern FLUENT_EXPORT void
free_histogram(Hist *hist);

#if RP_NODE
extern FLUENT_EXPORT void
write_histogram(Hist *hist, FILE *fp);
#endif

/* macros for communication routines used in setting up Metis data structure */

#if METIS_32BIT

#define PRF_CRECV_IDX PRF_CRECV_INT
#define PRF_CSEND_IDX PRF_CSEND_INT
#define MPT_IDX MPT_INT

#else

#define PRF_CRECV_IDX PRF_CRECV_INDEX
#define PRF_CSEND_IDX PRF_CSEND_INDEX
#define MPT_IDX MPT_INDEX

#endif /* ends METIS_32BIT */

#endif /* PART_LOCAL_H */
