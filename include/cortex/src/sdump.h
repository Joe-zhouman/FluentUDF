/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#define SEEM_DUMP_ID 11

extern int Seem_Dump_ID;
extern int Seem_Dump_App_ID;

#if cray || __alpha || _MIPS_SZPTR == 64 || _nec || NECSX || _64BIT
# define SEEM_DUMP_EXTENSION "-64"
#else
# define SEEM_DUMP_EXTENSION "-32"
#endif
