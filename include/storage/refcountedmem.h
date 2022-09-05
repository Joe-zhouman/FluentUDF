/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */
#ifndef _REFCOUNTEDMEM_
#define _REFCOUNTEDMEM_

#ifdef __cplusplus
extern "C" {
#endif
#include "dll.h"

#define FIXED_PROFILE_NAME_LENGTH 0
/* Use Alloc_Ref_Counted_Memory to allocate memory. The user needs to
 * provide some owner for the memory being allocated. When the owner is
 * copied, Ref_Counted_Memory_Copied should be called. This will
 * increase the reference counts for all memories that the owner (src)
 * holds.
 e.g: Lets say we have a container
 typedef struct bag_struct {
    char *name;
    char *values;
 } Bag;

 // We want to allow shallow copy as well as deep copy of Bag.
 // The following function does it one by one.

 void func()
 {
    Bag A;
    A.name = Alloc_Ref_Counted_Memory(&A, 10); // owner is A and size 10
    A.values = Alloc_Ref_Counted_Memory(&A, 100);

    Bag B = A; // shallow copy A into B.
    // inform the system that A is now copied to B
    Ref_Counted_Memory_Copied(&A, &B);

    // Now let us create different memory into B.
    Free_Ref_Counted_Memory(&B, B.name);
    Free_Ref_Counted_Memory(&B, B.values);
    B.name = Alloc_Ref_Counted_Memory(&B, 15); // Now B gets its own memory
    B.values = Alloc_Ref_Counted_Memory(&B, 20); // B values are its own too.

    // Before A & B go out of context. Inform the system to free up the
    // memories
    Free_Ref_Counted_Memory(&A, NULL); // all memory contained in A should be freed
    Free_Ref_Counted_Memory(&B, NULL); // all memory contained in B should be freed
 }
 */
FLUENT_EXPORT void *Alloc_Ref_Counted_Memory(void *owner, size_t size);
FLUENT_EXPORT void Ref_Counted_Memory_Copied(void *src, void *dest);
/* If ptr is a ref counted memory, its ref count will be reduced.
   If ptr is null, all ref counted memory in the owner will be reduced ref-count.
   If owner doesn't own any ref counted memory, this won't do anything.
*/
FLUENT_EXPORT void Free_Ref_Counted_Memory(void *owner, void *ptr);
#ifdef __cplusplus
}
#endif

#endif
