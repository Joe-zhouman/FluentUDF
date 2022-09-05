/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_PART_OVERSET_H
#define _FLUENT_PART_OVERSET_H

typedef struct Overset_Donor_Ext_Rec
{
  cell_t cell;
  Thread *t;
  idxtype mid;   /* Metis ID    */
  cxindex cid;   /* Cell ID     */
} OD_ext_r;

#if !RP_HOST

extern int
count_receptor_partitions(Domain *domain);

#if RP_METIS
extern int
update_local_DR_connectivity(Domain *domain, idxtype *xadj, int *nsend, int cell_start,
                             int nedge);

extern int
metis_form_xadj_overset(Domain *domain, Thread *t,
                        idxtype *xadj, int vertices, cxindex cell_start);

extern int
metis_form_adjncy_overset(Domain *domain, Thread *t, idxtype *xadj, idxtype *adjncy,
                          idxtype cell_start, int consider_fw);

#endif /* RP_METIS */

extern void
fill_donor_other(Domain *domain, int *nsend, int n);

int
fill_ext_OR(Domain *domain, OD_ext_r *od_ext_r, cxindex *min_cid, cxindex *max_cid);

extern int
fill_non_local_donors(Domain *domain, int *nsend, cxindex *sbuf,
                      cxboolean include_metis_id);

#endif  /* !RP_HOST */

extern int
update_overset_partition_interface_stats (Domain *domain, int npart, int *nintercells,
                                          int use_stored_partition_p
#if RP_NODE
                                          , neighbor_id_list **neighbor, cxboolean form_neighbor
#endif
                                         );

extern void
Overset_Repartition_With_MWP(Domain *, cxboolean);

#endif /* End _FLUENT_PART_OVERSET_H */
