/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/* orig from seem.h, cxconfig.h, rcx.h, cx.h, and List.h */
#if _nec /* || _aix43 */
# ifdef PROTO
#  undef PROTO
# endif
#endif

#ifndef PROTO
# if _NT
# define PROTO(proto)proto
# else
#  if defined(__STDC__) || defined(__STDCPP__) || _nec || defined(__cplusplus)
#   define PROTO(proto)proto
#  else
#   define PROTO(proto)()
#   ifndef const
#    define const
#   endif
#  endif
# endif
#endif

