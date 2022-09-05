/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#define PARALLEL 1
#define MULTIPORT 1
#if RP_HOST_LIB
# define BUILD_host 0
# define CX_SINGLE 1
# define CX_HOST_SINGLE 1
# undef GRAPHICS
# define GRAPHICS 0
# undef LICENSE_MANAGER
# define LICENSE_MANAGER 1
# undef CX_GUI
# define CX_GUI 0
#endif
#if RP_NODE_LIB
# undef GRAPHICS
# define GRAPHICS 0
# undef LICENSE_MANAGER
# define LICENSE_MANAGER 1
# define BUILD_net 0
# define BUILD_mpi 1
#endif
#if RP_HOST
# define CX_HOST 1
#endif
#if RP_NODE
# define CX_NODE 1
#endif

#ifndef CX_HOST_SINGLE
#define CX_HOST_SINGLE 0
#endif

#ifdef MAKEFILE

#if RP_NODE

# ifndef BUILD_mpi
#  define BUILD_mpi 1
# endif

#endif /* RP_NODE */

/*
 * general
 */
#ifndef BUILD_serial
# define BUILD_serial 0
#endif
#if RP_HOST
# ifndef BUILD_host
#  define BUILD_host 1
# endif
#else
# if RP_NODE
#  ifndef BUILD_net
#   define BUILD_net 0
#  endif
# endif
#endif

#endif /* MAKEFILE */
