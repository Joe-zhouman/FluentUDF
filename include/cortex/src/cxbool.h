/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _CXBOOL_H
#define _CXBOOL_H

#ifndef True
# define True (1)
#endif

#ifndef False
# define False (0)
#endif

#ifndef TRUE
# define TRUE (1)
#endif
#ifndef FALSE
# define FALSE (0)
#endif

#ifndef SKIP_BOOL
typedef int cxboolean;
#endif

#ifndef MOTIF
# if CRAY
typedef long CXBoolean;
# else
typedef char CXBoolean;
# endif
#else
typedef char CXBoolean;
#endif /* MOTIF */

#endif /* CXBOOL_H */
