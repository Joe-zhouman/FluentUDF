/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/* hash table entry */

typedef struct Hash_Entry
{
  Pointer             formal;
  Pointer             actual;
  struct Hash_Entry   *next;
} Hash_Entry;

extern Hash_Entry *hash_entry;

void       seem_hash_init   (Pointer);
void       tg_seem_hash_init(void);
void       seem_hash_insert (Pointer, Pointer);
void       tg_seem_hash_insert (Pointer, Pointer);
Hash_Entry *seem_hash_lookup(const char *);
Hash_Entry *tg_seem_hash_lookup(const char *);
Pointer    seem_hash_stats  (void);

