/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_DYN_BSEARCH_H
#define _FLUENT_DYN_BSEARCH_H

FLUENT_EXPORT void Delete_Dynamic_Sorted_Array (int);
FLUENT_EXPORT int Create_Dynamic_Sorted_Array (int, size_t);
FLUENT_EXPORT void Sort_Dynamic_Sorted_Array (int);
FLUENT_EXPORT void Add_Dynamic_Sorted_Array (int, cxindex, void *, cxboolean);
#define Insert_Dynamic_Sorted_Array(dsa_id, id, entry) \
  Add_Dynamic_Sorted_Array (dsa_id, id, entry, TRUE)
#define Append_Dynamic_Sorted_Array(dsa_id, id, entry) \
  Add_Dynamic_Sorted_Array (dsa_id, id, entry, FALSE)
FLUENT_EXPORT cxboolean Search_Dynamic_Sorted_Array (int, cxindex, void **, int);
FLUENT_EXPORT int DSA_get_size_used(int dsa_id);

#endif /* _FLUENT_DYN_BSEARCH_H */


