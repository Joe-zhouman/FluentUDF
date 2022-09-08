/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_MEMBLOCK_H
#define _FLUENT_MEMBLOCK_H

FLUENT_EXPORT void *Create_Memory_Manager1 (size_t, size_t, const char *, int);
# define Create_Memory_Manager(s1,s2) \
   Create_Memory_Manager1((s1),(s2),__FILE__,__LINE__)
FLUENT_EXPORT void Free_Memory_Manager1 (void **, const char *, int);
# define Free_Memory_Manager(man) \
   Free_Memory_Manager1((man), __FILE__, __LINE__)
FLUENT_EXPORT void Free_Memory_Blocks (void *);
FLUENT_EXPORT void *Get_Memory1 (void *, size_t, const char *, int);
# define Get_Memory(man, size) Get_Memory1((man), (size), __FILE__, __LINE__)
FLUENT_EXPORT void Print_Memory_Manager_Statistic (void *);
FLUENT_EXPORT void Get_Memory_Manager_Statistic (void *, size_t *, size_t *);

# define Insert_Memory_Block_Data(mbd, mm, free, size, freesize)        \
    Insert_Memory_Block_Data1(mbd, mm, free, size, freesize, __FILE__, __LINE__)
FLUENT_EXPORT void Insert_Memory_Block_Data1(void *, void *, void *,
                                             size_t, size_t, const char *, int);

#endif
