/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#include "dll.h"

#if SEEM
/* for icem cfd export*/

#if _NT || __alpha || linux

FLUENT_EXPORT int fwrite_int(int *ptr, size_t size, size_t nitems, FILE *stream);
FLUENT_EXPORT int fwrite_float(float *ptr, size_t size, size_t nitems, FILE *stream);
FLUENT_EXPORT int fwrite_double(double *ptr, size_t size, size_t nitems, FILE *stream);

#else

#define fwrite_int(a, b, c, d)  fwrite(a, b, c, d)
#define fwrite_float(a, b, c, d) fwrite(a, b, c, d)
#define fwrite_double(a, b, c, d) fwrite(a, b, c, d)

#endif

#if RP_DOUBLE
#define fwrite_real(a,b,c,d) fwrite_double(a,b,c,d)
#else
#define fwrite_real(a,b,c,d) fwrite_float(a,b,c,d)
#endif

FLUENT_EXPORT void Write_Icemcfd(Domain *, FILE *);
FLUENT_EXPORT void Write_Nodemap(const char *, Domain *);
#endif /*SEEM */

