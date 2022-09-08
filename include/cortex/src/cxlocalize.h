/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/* cxlocalize.h  $Revision: 1.222 $ $Date: 2010/09/10 13:04:13 $ */
/*
 *  This file is to customize the build options/switches for the various supported
 *   platforms as well as some build-time code inclusion options.
 *
 *
 *  Pre-processing options
 *    C     - CPPFLAGS
 *              = CPP_SWITCH_SYSTEM CPP_SWITCH_UI  CPP_SWITCH_GR CPP_ARCH_DEF CPP_64BIT_DEF
 *    C++   - CPPFLAGS and CXXFLAGS
 *
 *  compile options
 *    C     - CFLAGS
 *              = CPPFLAGS C_SWITCH_OPTIMIZE C_SWITCH_SYSTEM
 *    C++   - CXX_FLAGS + CPPFLAGS
 *              = CXX_FLAGS C_SWITCH_OPTIMIZE CPP_SWITCH_UI  CPP_SWITCH_GR CPP_ARCH_DEF CPP_64BIT_DEF
 *
 *  Link:
 *          - LDFLAGS
 *              = LD_SWITCH_OPTIMIZE LD_SWITCH_SYSTEM LD_SWITCH_UI LD_SWITCH_GR
 *
 *  Defaults (in makefile.c)
 *      CPP_64BIT_DEF    (_64BIT) ? -D_64BIT : ""
 *      CPP_SWITCH_GR -I../../include
 *      CPP_SWITCH_UI ""
 *      CPP_SWITCH_MP -I$(MPDIR)
 *      CPP_SWITCH_SYSTEM ""
 *
 *      C_SWITCH_SYSTEM
 *      C_SWITCH_OPTIMIZE -O
 *
 *      LD_SWITCH_GR -Llib
 *      LD_SWITCH_UD ""
 *      LD_SWITCH_SYSTEM ""
 *      LD_SWITCH_OPTIMIZE -O -s
 *      LD_SWITCH_CXX
 */


#ifndef DEVELOP
# define DEVELOP 0      /* DEFINE AS ZERO FOR RELEASES */
#endif

#if __uxpv__
/* fujitsu */
# define CC_ vcc
# define HAVE_MOTIF 0
# define GRAPHICS 0
# define C_SWITCH_OPTIMIZE -Wv,-sc -O -K3
# define LD_SWITCH_OPTIMIZE -dy
# define LIBS_SYSTEM  -lrpcsoc -lsocket -lnsl -lresolv -lm
#endif

#ifdef _necsx
/* necsx */
# define CC_ sxcc
# define AR_ sxar
# define GRAPHICS 0
# define HAVE_MOTIF 0
# define SECURITY_KEY 0

# define PORTMAP 1

# define CPP_SWITCH_SYSTEM -D__svr4__ -Dunix
# define C_SWITCH_SYSTEM -hansi -hfloat0
# define LD_SWITCH_SYSTEM -hfloat0
#endif

#if sun || Sun || _ultra || defined(_fujitsu_pp)  /* Fluent defines Sun or Solaris */

# if  _fujitsu_pp
#    define CC_ /opt/FSUNf90/bin/fcc
# endif
# define PORTMAP 1

# ifdef MAKEFILE
#  if DEVELOP
#   ifdef CC_
#    define DEBUG_FLAGS -g
#   else
#    define DEBUG_FLAGS -g
#   endif
#  else
#   define DEBUG_FLAGS
#  endif /* DEVELOP */

#  if _64BIT
#   define NBIT_SWITCH -xarch=v9a
#  else
#   define NBIT_SWITCH
#  endif

#  if _fujitsu_pp
#       define CPP_SWITCH_SYSTEM  -DSUN -DSOLARIS -DSUN64 -DHAL -DNDEBUG -DOS64BIT -DDPRCSN -D_fujitsu_pp
#  else
#   if _ultra
#     define CPP_SWITCH_SYSTEM -D__svr4__ -Dsparc -D__sparc -Dsun -Dunix -D_solaris
#     if ! defined(CC_)
#      define C_SWITCH_SYSTEM -Xc
#     endif
#    else
#     if _ultra_64
#     define CPP_SWITCH_SYSTEM -D__svr4__ -Dsparc -D__sparc -Dsun -Dunix -D_solaris -xarch=v9a -D__EXTENSIONS__
#     if ! defined(CC_)
#      define C_SWITCH_SYSTEM -Xc
#     endif
#     else
#      define CPP_SWITCH_SYSTEM  -Dsparc -D__sparc -Dsun -Dunix -D_sun4 -D__USE_FIXED_PROTOTYPES__
#     endif /* _ultra_64 */
#    endif /* _ultra */
#  endif /* fujitsu_pp*/

#  if defined(CC_)
#    if _fujitsu_pp
#       define C_SWITCH_OPTIMIZE        -KV9
#   else
#       define C_SWITCH_OPTIMIZE DEBUG_FLAGS -ansi -Wall -Wno-parentheses
#       define LD_SWITCH_OPTIMIZE DEBUG_FLAGS
#   endif
#  else
#   define C_SWITCH_OPTIMIZE DEBUG_FLAGS
#   define LD_SWITCH_OPTIMIZE DEBUG_FLAGS
#  endif


#  if defined(_ultra) || defined(_fujitsu_pp) /* Solaris > 2.3 (2.[12] are broken) */
#   define MOTIF_INCLUDE -I/usr/dt/include -I/usr/openwin/include
#   define MOTIF_LIB -L/usr/dt/lib -L/usr/openwin/lib
#   define CPP_SWITCH_UI MOTIF_INCLUDE NBIT_SWITCH
#   if _fujitsu_pp
#      define LD_SWITCH_SYSTEM MOTIF_LIB NBIT_SWITCH -L/usr/ucblib/sparcv9
#   else
#      define LD_SWITCH_SYSTEM MOTIF_LIB NBIT_SWITCH -L/usr/ucblib  -lrt /*-lrt for nanosleep*/
#   endif

#    define LIBS_TIFF -Bstatic -ltiff -Bdynamic /* Link to our static tiff lib */
#   define LIBS_PNG -Bstatic -lpng -lz -Bdynamic
#   define LIBS_XPM -Bstatic -lXpm -Bdynamic
#    define LIBS_UI -lXm -lXt -lSM -lICE -lXext -lX11 -lw -ldl
/*   tested on sunos 5.6 SC4.2 only */

#    ifndef CXX_FLAGS
#     define CXX_FLAGS
/*    stlport no longer needed w/ Sun Workshop 6 update 1 C++ 5.2 */
/*    -I../../include/stl -D_STL_USE_OWN_NAMESPACE=1 */
#    endif

#   define LINK_ $(CXX)

#   ifndef LIBS_SYSTEM
#    define LIBS_SYSTEM  -lrpcsoc -lsocket -lnsl -lresolv -lm -lintl
#   endif
#   define CPP_SWITCH_PIC -KPIC
#   define RANLIB_ /bin/true

#  endif /* ultra */

# endif /* MAKEFILE */

# define WORKING_CXX 1
# define CXX_ CC
# if _64BIT
#   if _fujitsu_pp
#     define CORTEX_ARCH fujitsu_pp
#     define CORTEX_SERVER_ARCH ultra
#   else
#     define CORTEX_ARCH ultra_64
#     define CORTEX_SERVER_ARCH ultra
#   endif
# else
#   define CORTEX_ARCH ultra
# endif

#endif /*sun*/

/* this file no longer supports irix5 only irix6.2 or greater
 * irix6r8   -> irix6.1 no longer supported make this a link to irix6r10
 * irix6r10  -> irix6.2 no longer supported
 * irix65xxx -> irix65
 */
#if sgi

# define LMGRVERSION 70

# define WORKING_CXX 1
# define CXX_ CC
# ifndef SPACEBALL
#  define SPACEBALL 0
# endif

# ifdef MAKEFILE

#  if DEVELOP
#   ifndef C_SWITCH_OPTIMIZE
#    ifdef __GNUC__
#     define C_SWITCH_OPTIMIZE -g -ansi -Dunix -Dsgi -fpcc-struct-return -Wall -Wno-parentheses
#    else
#     define C_SWITCH_OPTIMIZE -g /* -fullwarn -O -woff 835 */
#    endif
#   endif
#   ifndef LD_SWITCH_OPTIMIZE
#    define LD_SWITCH_OPTIMIZE -g
#   endif
#  endif /* DEVELOP */


/* Do not use the irix5 cortex.3.x.x on irix 6.x anymore */
/* define NBIT_SWITCH and if server arch is different */
#  if defined _irix6r10
#   define NBIT_SWITCH -n32 -mips3
/* irix cpp does not recognize the elif command */
#  else
#   if defined _irix6r10_64
#    define CORTEX_SERVER_ARCH irix6r10
#    define NBIT_SWITCH -64 -mips3
#   else
#    if defined _irix65
#     define NBIT_SWITCH -n32 -mips3
#    else
#     if defined _irix65_mips4
#       define CORTEX_ARCH irix65_mips4
#      define NBIT_SWITCH -n32 -mips4
#     else
#      if defined _irix65_64
#       define CORTEX_SERVER_ARCH irix65
#       define NBIT_SWITCH -64 -mips3
#      else
#       if defined _irix65_mips4_64
#       define CORTEX_ARCH irix65_mips4_64
#        define CORTEX_SERVER_ARCH irix65_mips4
#        define NBIT_SWITCH -64 -mips4
#       endif
#      endif
#     endif
#    endif
#   endif
#  endif

/* any irix65 */
#  if defined _irix65 || defined _irix65_64 || defined _irix65_mips4 || defined _irix65_mips4_64

#    ifndef LIB_HOOPS
#     if SPACEBALL
#      define LIB_HOOPS -lhoops610_sb
#     endif
#    endif

#   define LIBS_SYSTEM -lPW -lm
/* removed because of memory lead: -lmalloc */

#   ifndef CXX_FLAGS
#    define CXX_FLAGS NBIT_SWITCH -LANG:ansi-for-init-scope=ON
#   endif

#   define LD_SWITCH_SYSTEM NBIT_SWITCH -LD_MSG:off=85,134
#  endif /* irix65 */

/* common to all irix6 arch's */
#  define LIBS_UI -lXm -lXt -lX11

#  ifndef LINK_
#   define LINK_ $(CXX)
#  endif

# ifndef CPP_SWITCH_SYSTEM
#  define CPP_SWITCH_SYSTEM -Dlint -signed -woff 1174,1552,3187
/* compiler 7.2.1 -woff 1048,1412 */
# endif
# ifndef C_SWITCH_SYSTEM
#  define C_SWITCH_SYSTEM NBIT_SWITCH
# endif
# ifndef C_SWITCH_OPTIMIZE
#  define C_SWITCH_OPTIMIZE -O -OPT:Olimit=2469
# endif
#define CPP_SWITCH_PIC -KPIC

# define RANLIB_ /bin/true

# define HAVE_CPP_M 1

# endif /* MAKEFILE */

#endif /*sgi*/

#if _AIX || _aix43 || _aix43_64 || _power3 || _power3_64 || _aix51 || _aix51_64
/* not using gcc or g++ */
# ifdef MAKEFILE
/* IBM decide to have their cpp output "#line 222 filename" instead of
 * "# 222 filename" like everyone else so the default DEP_GEN doesn't
 * work.  In addition, they provide cpp -M, but it creates a .u file
 * instead of writing to stdout.  Very nice. */
#  define DEP_GEN(src)($(CPP) -M -w $(CPPFLAGS) src > /dev/null; /bin/cat $*.u; /bin/rm $*.u)
#  define DEP_GENCXX(src)($(CXX) -c -M -w $(CXXFLAGS) src > /dev/null; /bin/cat $*.u; /bin/rm $*.u)

#  define GL_DEFERRED_LINK 0

#  if DEVELOP
#   define C_SWITCH_OPTIMIZE -g
#   define LD_SWITCH_OPTIMIZE -g
/* -bnoquiet */
#  endif


#  if _aix43 || _aix43_64 || _power3 || _power3_64 || _aix51 || _aix51_64
#   if _64BIT
#     define _OBJECT_MODE -q64
#     define AR_ ar -X64
#   else
#     define _OBJECT_MODE
#     define CORTEX_ARCH aix51
#   endif

/* not building 64 bit cortex binaries */
#   if _aix43_64
#    define CORTEX_ARCH aix43_64
#    define CORTEX_SERVER_ARCH aix43
#   else
#    if _power3_64
#    define CORTEX_ARCH power3_64
#     define CORTEX_SERVER_ARCH power3
#    endif
#   endif
#   if _aix51_64
#    define CORTEX_ARCH aix51_64
#    define CORTEX_SERVER_ARCH aix51
#   endif


#   define CPP_SWITCH_GR -DOGL -I../../include HOOPS_INCLUDES
#   define CPP_SWITCH_SYSTEM -Dunix -qmaxmem=6000 -qlanglvl=ansi -qlonglong -qnolm -qarch=pwr4 -qtune=balanced -qinline+evaluate_polynomial:evaluate_polynomial_integral:evaluate_polynomial_plinear _OBJECT_MODE
/* -qlibansi -qonce */

#   define C_SWITCH_OPTIMIZE -O3

#   define CXX_ /usr/vacpp/bin/xlC
#    define CC_ $(CXX)
#    define CPP $(CXX)
#    define LINK_ $(CXX)
/* temp turn off to link with new hoops library */
#   ifndef CXX_FLAGS
#    define CXX_FLAGS -I/usr/vacpp/include -D__IOC_ANSI_STREAM
/* -qtwolink -w -qtempinc -qtempmax=5 -qnotempinc */
/*
  c++ may need a different langlvl
    c:    ansi, extended ;;; feature
    c++:  ansi, extended
    c++ features:
        typdefclass, ansifor, newexcp, redefmac
*/
#   endif /* CXX_FLAGS */
#   ifndef LD_SWITCH_CXX
#     define LD_SWITCH_CXX -brtl
/* -Wl,-bnoquiet */
#   endif
#  endif


/*  hoops 9.2 and 10 only have builds for aix5.x */
#  if _aix43 || _aix43_64 || _power3 || _power3_64
#   ifndef LIB_HOOPS
#    define LIB_HOOPS -lhoops900
#    define HOOPS_INCLUDES -I../include/hoops92
#   endif
#  endif

/* all aix */
/* override the system 256M process size limit */
# ifndef LD_SWITCH_SYSTEM
#  if _64BIT
#   define LD_SWITCH_SYSTEM -bD:0xffffffffffffffff  -qnolm  _OBJECT_MODE LD_SWITCH_CXX
#  else
#   define LD_SWITCH_SYSTEM -bD:0x7fffffff  -qnolm  _OBJECT_MODE LD_SWITCH_CXX
#  endif
# endif

#ifndef LIBS_SYSTEM
#  define LIBS_SYSTEM -lcxbt -lxlf90
#endif

#  define RANLIB_ /bin/true
# endif /* MAKEFILE */

# define HAVE_MPEG 0
# define WORKING_CXX 1

#endif /*_AIX */


#ifndef _necsx

#if hpux || _hpux || __hpux

#if __HP_CXD_SPP && !_HPUX11
# define _SPPUX 1
#endif

# if _hpux11 || _hpux11_64 || _hpux10pa1 || _hpux10p8 || _hpux11_ia64
#  define WORKING_CXX 1
#  if _hpux10pa1 || _hpux10p8 || _hpux11_ia64
#   define HAVE_HOOPS_STREAMS 0
#  endif
# else
#  define HAVE_VRML 0
#  define HAVE_HOOPS_STREAMS 0
# endif

#ifdef MAKEFILE

#define SYSTEM_DEFS -Dhpux -D_HPUX_SOURCE -Dunix
#define STATIC_LINK  -Wl,-a,archive
#define DYNAMIC_LINK -Wl,-a,default

#define LIBS_PNG STATIC_LINK -lpng -lz DYNAMIC_LINK
#define LIBS_XPM STATIC_LINK -lXpm DYNAMIC_LINK

# if _hpux11 || _hpux11_64
# define CC_ /opt/ansic/bin/cc
#endif

# if _64BIT || _hpux11_64 || _hpux11_ia64
#  define CORTEX_SERVER_ARCH hpux11 /* Use the hpux11 cortex.3.3.x on hpux11_64 */
#  if _hpux11_ia64
#   define CORTEX_ARCH hpux11_ia64
#   define NBIT_SWITCH +DD64
#   define C_SWITCH_OPTIMIZE +O3 +Odataprefetch +Onolimit +Onoinfo +Oinitcheck +Ofltacc=limited +Optrs_ansi
#   define C_SWITCH_SYSTEM +DSblended -Ae NBIT_SWITCH -D_64BIT
#  else
#   define CORTEX_ARCH hpux11_64
#   define NBIT_SWITCH +DD64 +DA2.0W
#  endif
# else
#   define CORTEX_ARCH hpux11
#  define NBIT_SWITCH
# endif

# if DEVELOP
#  ifdef __GNUC__
#   define CPP_SWITCH_SYSTEM SYSTEM_DEFS
#   define C_SWITCH_OPTIMIZE -g -ansi -fpcc-struct-return -Wall -Wno-parentheses
#   define LD_SWITCH_OPTIMIZE -g
#   define CPP_SWITCH_PIC -fpic
#  else
#   define CPP_SWITCH_SYSTEM SYSTEM_DEFS
#   define C_SWITCH_OPTIMIZE -g
#   define LD_SWITCH_OPTIMIZE -g
#   define LD_SWITCH_SYSTEM -Wl,+s,+vnocompatwarnings -N
#   define CPP_SWITCH_PIC +z
#  endif /*__GNUC__*/
# else
#   define CPP_SWITCH_SYSTEM -w SYSTEM_DEFS
#   define LD_SWITCH_SYSTEM -Wl,+s,+vnocompatwarnings -N
#   define CPP_SWITCH_PIC +z
# endif /*DEVELOP*/


# if _HPUX11 || _hpux11 || _hpux11_64 || _hpux11_ia64
#  define CPP_SWITCH_UI -I/usr/include/Motif2.1 -I/usr/include/X11R6
/* -I../../include/hpux/X11R6 */
#  define LD_SWITCH_UI -L/usr/lib/Motif2.1 -L/usr/lib/X11R6
#  define LIBS_SYSTEM -lrpcsoc -lrpcsvc -lm
# else
#  define CPP_SWITCH_UI -I/usr/include/Motif1.2 -I/usr/include/X11R5
#  define LD_SWITCH_UI -L/usr/lib/Motif1.2 -L/usr/lib/X11R5
# endif /* _HPUX11 */

# if _hpux11 || _hpux11_64 || _hpux10pa1 || _hpux10p8 || _hpux11_ia64
#  define CPP_ARG_CXX -c +m
#  define CXX_ /opt/aCC/bin/aCC
#  ifdef MAKEFILE
#   define LINK_ $(CXX)
#  endif
#  ifndef CXX_FLAGS
#   if _hpux11 || _hpux11_64 || _hpux11_ia64
#    define CXX_FLAGS NBIT_SWITCH -Aa -I/opt/aCC/include -I/opt/aCC/include/iostream
#   else   /* hpux10 */
#    define CXX_FLAGS NBIT_SWITCH -I/opt/aCC/include -I/opt/aCC/include/iostream
#   endif
#  endif
#   if _hpux10pa1 || _hpux10p8
#    ifndef LIB_HOOPS
#     define LIB_HOOPS -lhoops620
#    endif
#   endif
#   ifndef LD_SWITCH_GR
#    define LD_SWITCH_GR -Llib
#   endif
#  ifndef C_SWITCH_SYSTEM
#   define C_SWITCH_SYSTEM NBIT_SWITCH -Ae
#  endif
#  ifndef LD_SWITCH_CXX
#   define LD_SWITCH_CXX -Aa
#  endif
# endif  /* all hpux11 and hpux10 */

# if _SPPUX
#  ifndef LIBS_GR
#   define LIBS_GR
#  endif
#  define LIBS_UI STATIC_LINK -lXext -lXm -lXt -lX11 DYNAMIC_LINK
# else   /* all non-sppux hp's */
#   ifndef LIBS_UI
#    define LIBS_UI -lXext -lXm -lXt -lX11
#   endif
# endif /* __HP_CXD_SPP */

# endif /* MAKEFILE */
#endif /* hpux */

#endif /* !_necsx */


#if _hiux

#  define GRAPHICS 0
#  define HAVE_MOTIF 0
/* #  define WORKING_CXX 1*/

/*#  ifdef MAKEFILE */
#    define SYSTEM_DEFS -D_hiux -D_HPUX_SOURCE -Dunix
#    define STATIC_LINK  -Wl,-a,archive
#    define DYNAMIC_LINK -Wl,-a,default
# if DEVELOP
#  ifdef __GNUC__
#   define CPP_SWITCH_SYSTEM SYSTEM_DEFS
#   define C_SWITCH_OPTIMIZE -g -ansi -fpcc-struct-return -Wall -Wno-parentheses
#   define LD_SWITCH_OPTIMIZE -g
#  else
#   define CPP_SWITCH_SYSTEM SYSTEM_DEFS
#   define C_SWITCH_OPTIMIZE -g
#   define LD_SWITCH_OPTIMIZE -g
#   define LD_SWITCH_SYSTEM -Wl
#  endif /*__GNUC__*/
# else
#   define CPP_SWITCH_SYSTEM  SYSTEM_DEFS
#   define LD_SWITCH_SYSTEM  -Wl
/*#   define LD_SWITCH_OPTIMIZE  +O3 -Wc,-h +Oprefetch +DB     */
#   define LD_SWITCH_OPTIMIZE
# endif /*DEVELOP*/

# define CPP_ARG_CXX -c
/* # define CXX_ /usr/bin/KCC */
# define CXX_ /usr/bin/KCC
# ifndef CXX_FLAGS
#   define CXX_FLAGS -I/usr/kai/KCC_BASE/include
# endif

/* #  define CPP_SWITCH_UI -I/usr/include/Motif2.1 -I/usr/include/X11R6 */
/*#  define CPP_SWITCH_UI  -I/usr/include/X11R6 */

/* #  define LD_SWITCH_UI -L/usr/lib/Motif2.1 -L/usr/lib/X11R6 */
#  define LIBS_SYSTEM -lm
/*#endif  MAMEKFILE */
#endif  /* hiux */


#define __APPEND_TO_ONE(value)  1 ## value
#define   APPEND_TO_ONE(value)  __APPEND_TO_ONE(value)


#ifdef _NT
# if APPEND_TO_ONE(_NT) != 1   /* == 1 would mean that _NT is defined empty */
#  if  ! _NT
/* #   warning _NT defined as zero or false -- will undef it */
/* That will definitely cause trouble where _NT is expected to not be empty.
 * Therefore I'm doing it this way rather than changing the code here such
 * that it would expect _NT to have a value and complain if it hadn't.
 */
#   undef _NT
#  endif
# endif
#endif


#ifdef _NT

#define SECURITY_KEY 0
#ifndef MS_WINDOWS
#define MS_WINDOWS 1
#endif
#ifndef LIB_HOOPS
#if DEVELOP
# define LIB_HOOPS hoops_streamd.lib hoopsd.lib hoops_utilsstat_mt.lib
#else
# define LIB_HOOPS hoops_stream.lib hoops.lib hoops_utilsstat_mt.lib
#endif
# define HOOPS_INCLUDES -I../include/hoops/3dgs -I../include/hoops/base_stream -I../include/hoops/stream -I../include/hoops/utility
#endif
#define WORKING_CXX 1

#ifndef MAKEFILE

#pragma warning(disable: 4051) /* type conversion: possible loss of data */
#pragma warning(disable: 4135) /* conversion between different integral types */
#pragma warning(disable: 4136) /* conversion between different floating-point types */
#pragma warning(disable: 4244) /* conversion between different floating-point types */
#pragma warning(disable: 4237) /* keyword is reserved for future use */
#pragma warning(disable: 4250)
#pragma warning(disable: 4305) /* truncation from const double to float */
#pragma warning(disable: 4761) /* integral size mismatch, conversion supplied */

#endif

/* NT says these routines are not ansi-standard */
#define chdir   _chdir
#define getcwd  _getcwd
#define getpid  _getpid
#if defined(__STDC__)
#define stat    _stat
#endif
#define strdup  _strdup
#define open    _open
#define sleep   Sleep
#define putenv  _putenv
#define S_IFDIR _S_IFDIR
#define O_RDWR  _O_RDWR
#define O_NDELAY 0
#define O_NONBLOCK 0

#endif /* _NT */

#if cray

/* No HOOPS. */
# define GRAPHICS 0
# define WORKING_CXX 0


# ifdef CPP_
#  undef CPP_
# endif
# define CPP_ /opt/ctl/bin/cpp
# define HAVE_CPP_M 1
# define RANLIB_ /bin/true
# define C_SWITCH_OPTIMIZE -h tolerant
# define CPP_SWITCH_UI -I/opt/ctl/cvt/cvt/include
# define LD_SWITCH_UI -L/opt/ctl/cvt/cvt/lib
# define LIBS_SYSTEM -lICE -lSM -lm

#endif /* cray */

#if CRAY
#define _Offsetof(p_type,field) \
(sizeof(int)*((unsigned int)&(((p_type)NULL)->field)))
#endif

#if (_lnx86 || _lnarm64 || _lnia64 || _lnamd64 || _linmic)
# define _linux 1  /* keep compatible with sys_master.h */
#else
# define _linux 0
#endif


#ifndef MPC_PLATFORM
#define MPC_PLATFORM (_lnamd64 || _linmic || _lnx86 || _NT || _lnia64 || _aix51 || _aix51_64 || _hpux11_ia64 || _hpux11_64 || _hpux11)
#endif

#if _linux
#define LD_DYNAMIC -rdynamic
#endif


#if _lnia64
# define ICC_PATH
# if _IA64_32BIT
#  define IA64_32BIT_CORTEX +DD32
# else
#  define IA64_32BIT_CORTEX
# endif

#ifndef GCC_ROOT
# define GCC_ROOT "../../packages16.0/gcc-4.1.1/lnia64"
#endif

# ifndef CC_
#  define CC_ GCC_ROOT"/bin/gcc"
# endif
# define CORTEX_ARCH lnia64
# if _IA64_32BIT
#   define CPP_SWITCH_UI -I/usr/X11R6/include
#   define LD_SWITCH_UI  -L/usr/X11R6/lib
# else
#   define CPP_SWITCH_UI -I/usr/X11R6/include
#   define LD_SWITCH_UI  -L/usr/X11R6/lib
# endif

# define HAVE_IMAGE 0
# define HAVE_MOTIF 0
# define HAVE_MPEG 0
# define HAVE_HOOPS_STREAMS 1

# define CPP_ cc
# define CPP_ARG -MM
# define CPP_ARG_CXX -MM

# define WORKING_CXX 1
# ifdef MAKEFILE
#   define CXX_ GCC_ROOT"/bin/c++"
#   define LINK_ $(CXX)
/*  unfortunatly the stlport headers are not working for
 *   g++ on linux - too many errors conflicting with native headers
#  ifndef CXX_FLAGS
#   define CXX_FLAGS -I../../include/stl
#  endif
*/

/* #   define C_SWITCH_OPTIMIZE -tpp2 -ftz -O2 IA64_32BIT_CORTEX */
#   define C_SWITCH_OPTIMIZE -O3

#   ifndef LIB_HOOPS
#if DEVELOP
#    define LIB_HOOPS -lhoopsd -lhoops_streamd
#else
#    define LIB_HOOPS -lhoops -lhoops_stream
#endif
#    define HOOPS_INCLUDES -I../include/hoops/3dgs -I../include/hoops/base_stream -I../include/hoops/stream -I../include/hoops/utility
#   endif
#   ifndef LIBS_GR
#    define LIBS_GR -ldl
#   endif
#   if DEVELOP
#    define C_SWITCH_OPTIMIZE -g
#    define LD_SWITCH_OPTIMIZE -g
#   endif
#   define CPP_SWITCH_SYSTEM -DXM_1_2_XTMACROS -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -I/usr/X11R6/include -I/usr/X11R6/include/Xm
/* #   define CPP_SWITCH_SYSTEM -DXM_1_2_XTMACROS -Dlinux -Dunix -DSYSV */
#   define LD_SWITCH_SYSTEM -L/usr/X11R6/lib -L ICC_PATH/lib
#   define CPP_SWITCH_PIC -fpic
#   define LIBS_MOTIF -lXm -lXmu -lXp
#   define LIBS_UI LIBS_MOTIF LIBS_X11
#   define LIBS_TIFF -Wl,-Bstatic -ltiff -Wl,-Bdynamic
#   define LIBS_PNG -Wl,-Bstatic -lpng -lz -Wl,-Bdynamic
#   define LIBS_XPM -Wl,-Bstatic -lXpm -Wl,-Bdynamic
/* We must link to shared X11 in order to link to shared OpenGL */
#   ifndef STATIC_X11
#    define STATIC_X11 0
#   endif
#   if STATIC_X11
#    define LIBS_X11 -Wl,-Bstatic -lXt -lXext -lX11 -lSM -lICE -Wl,-Bdynamic
#   else
#    define LIBS_X11 -lXt -lXext -lX11
#   endif
/* #  define LIBS_SYSTEM -static-libcxa */

#  endif /* MAKEFILE */

#endif /* _lnia64 */

#if _lnamd64

#ifndef ICC_ROOT
# define ICC_ROOT "../../packages18.0/intel/lnamd64"
#endif

# define HAVE_IMAGE 0

#if _AMD64_32BIT
#  define AMD64_32BIT_CORTEX -m32
#endif

# ifndef GCC_ROOT
#  if (POSIX_VERSION >= 200809)
#   define GCC_ROOT "../../packages18.0/gcc4.6.1_suse11.1"
#  else
#   define GCC_ROOT "../../packages18.0/gcc-4.8.3/lnamd64"
#  endif
# endif

# ifndef CC_
#  define CC_ ICC_ROOT"/bin/icc"
# endif

# define CORTEX_ARCH lnamd64
# if _AMD64_32BIT
#   define CPP_SWITCH_UI -I/usr/X11/include
#   define LD_SWITCH_UI  -L/usr/X11/lib
# endif

# define HAVE_MOTIF 0
# define HAVE_MPEG 0

# define CPP_ARG -MM
# define CPP_ARG_CXX -MM

# ifndef  WORKING_CXX
#  define WORKING_CXX 1
# endif
#  ifdef MAKEFILE
#   ifndef CXX_
#    define CXX_ ICC_ROOT"/bin/icpc"
#   endif
#   define LINK_ $(CXX)
/*  unfortunatly the stlport headers are not working for
 *   g++ on linux - too many errors conflicting with native headers
#  ifndef CXX_FLAGS
#   define CXX_FLAGS -I../../include/stl
#  endif
*/

#if DEVELOP
#    define C_SWITCH_OPTIMIZE -g -Wall -pedantic -Wmissing-prototypes
#    define LD_SWITCH_OPTIMIZE -g
#else
#   define C_SWITCH_OPTIMIZE -O3
#   define LD_SWITCH_OPTIMIZE
#endif
#   define HAVE_HOOPS_STREAMS 1
#   define LIBS_HOOPS_STREAM

#   ifndef LIB_HOOPS
#if DEVELOP
#    define LIB_HOOPS -lhoopsd -lhoops_streamd
#else
#    define LIB_HOOPS -lhoops -lhoops_stream
#endif
#    define HOOPS_INCLUDES -I../include/hoops/3dgs -I../include/hoops/base_stream -I../include/hoops/stream -I../include/hoops/utility
#   endif
#   ifndef LIBS_HOOPS_STREAM
#if DEVELOP
#    define LIBS_HOOPS_STREAM -lhoops_streamd
#else
#    define LIBS_HOOPS_STREAM -lhoops_stream
#endif
#   endif
#   ifndef LIBS_GR
#    define LIBS_GR -ldl
/* -lGLU -lGL */
#   endif
#   define CPP_SWITCH_PIC -fpic
#   define CPP_SWITCH_SYSTEM  -DHAVE_HOOPS_STREAMS=1 -DXM_1_2_XTMACROS -Dlinux -Dunix -I../include/X11R6/include
#   define LD_SWITCH_SYSTEM -L../../lib/lnamd64 -L/usr/X11R6/lib64
#if 0
#   define LIBS_MOTIF /usr/X11/lib/libXm.so.3 /usr/X11/lib/libXp.so.6
#endif
#   define LIBS_MOTIF   -Wl,-Bstatic  -lXm -lXmu -lXp  -Wl,-Bdynamic
#   define LIBS_UI LIBS_MOTIF LIBS_X11
#   define LIBS_TIFF -Wl,-Bstatic -ltiff -Wl,-Bdynamic
#   define LIBS_PNG -Wl,-Bstatic -lpng -lz -Wl,-Bdynamic
#   define LIBS_XPM -Wl,-Bstatic -lXpm -Wl,-Bdynamic
/* We must link to shared X11 in order to link to shared OpenGL */
#   ifndef STATIC_X11
#    define STATIC_X11 0
#   endif
#   if STATIC_X11
#    define LIBS_X11 -Wl,-Bstatic -lXt -lXext -lX11 -lXft -lSM -lICE -Wl,-Bdynamic
#   else
#if 0
#    define LIBS_X11 /usr/X11/lib/libXt.so.6 /usr/X11/lib/libXext.so.6 /usr/X11/lib/libX11.so.6
#endif
#    define LIBS_X11 -lXt -lXext -lX11 -lXft
#   endif

#  endif /* MAKEFILE */

#endif /* _lnamd64 */

#if _linmic

# define HAVE_IMAGE 0

#if _AMD64_32BIT
#  define AMD64_32BIT_CORTEX -m32
#endif

# ifndef ICC_ROOT
#   define ICC_ROOT ../../../../FBU_Dependencies/thirdparty/compilers/intel/linx64/bin
# endif

# ifndef CC_
#  define CC_ ICC_ROOT"/icc"
# endif

/* Cortex arch will still be lnamd64 as we need only *.lib for linmic */
# define CORTEX_ARCH lnamd64
# if _AMD64_32BIT
#   define CPP_SWITCH_UI -I/usr/X11/include
#   define LD_SWITCH_UI  -L/usr/X11/lib
# endif

# define HAVE_MOTIF 0
# define HAVE_MPEG 0

# define CPP_ARG -MM
# define CPP_ARG_CXX -MM

#  define WORKING_CXX 1
#  ifdef MAKEFILE
#   ifndef CXX_
#    define CXX_ ICC_ROOT"/icpc"
#   endif
#   define LINK_ $(CXX)

#if DEVELOP
#    define C_SWITCH_OPTIMIZE -g -O0 -mmic
#    define LD_SWITCH_OPTIMIZE -g -mmic
#else
#   define C_SWITCH_OPTIMIZE -O3 -mmic
#   define LD_SWITCH_OPTIMIZE -mmic
#endif
#   define HAVE_HOOPS_STREAMS 0
#   define LIBS_HOOPS_STREAM

#   ifndef LIB_HOOPS
#    define LIB_HOOPS -lhoops1922
#    define HOOPS_INCLUDES -I../include/hoops1922
#   endif
#   ifndef LIBS_HOOPS_STREAM
#    define LIBS_HOOPS_STREAM -lhoops_stream1922
#   endif
#   ifndef LIBS_GR
#    define LIBS_GR -ldl
/* -lGLU -lGL */
#   endif
#   define CPP_SWITCH_PIC -fpic
#   define CPP_SWITCH_SYSTEM  -DHAVE_HOOPS_STREAMS=0 -DXM_1_2_XTMACROS -Dlinux -Dunix -I/usr/X11R6/include -I../include/X11R6/include/ -I/usr/X11R6/include/Xm -I../include/X11R6/include/Xm
#   define LD_SWITCH_SYSTEM -L/usr/X11R6/lib64
#if 0
#   define LIBS_MOTIF /usr/X11/lib/libXm.so.3 /usr/X11/lib/libXp.so.6
#endif
#   define LIBS_MOTIF   -Wl,-Bstatic  -lXm -lXmu -lXp  -Wl,-Bdynamic
#   define LIBS_UI LIBS_MOTIF LIBS_X11
#   define LIBS_TIFF -Wl,-Bstatic -ltiff -Wl,-Bdynamic
#   define LIBS_PNG -Wl,-Bstatic -lpng -lz -Wl,-Bdynamic
#   define LIBS_XPM -Wl,-Bstatic -lXpm -Wl,-Bdynamic
/* We must link to shared X11 in order to link to shared OpenGL */
#   ifndef STATIC_X11
#    define STATIC_X11 0
#   endif
#   if STATIC_X11
#    define LIBS_X11 -Wl,-Bstatic -lXt -lXext -lX11 -lSM -lICE -Wl,-Bdynamic
#   else
#if 0
#    define LIBS_X11 /usr/X11/lib/libXt.so.6 /usr/X11/lib/libXext.so.6 /usr/X11/lib/libX11.so.6
#endif
#    define LIBS_X11 -lXt -lXext -lX11
#   endif

#  endif /* MAKEFILE */

#endif /* _linmic */

#if _lnx86
# define CORTEX_ARCH lnx86

# define HAVE_IMAGE 0
# define HAVE_MPEG 0

# define CPP_ARG -MM
# define CPP_ARG_CXX -MM

#ifndef GCC_ROOT
# define GCC_ROOT "../../packages18.0/gcc-4.8.3/lnamd64"
#endif

# ifndef CC_
#  define CC_ GCC_ROOT"/bin/gcc"
# endif

#  define WORKING_CXX 1
#  ifdef MAKEFILE
#   ifndef CXX_
#    define CXX_ GCC_ROOT"/bin/g++"
#   endif
#   define LINK_ $(CXX)

#   ifndef LIBS_GR
#    define LIBS_GR -ldl
/* -lGLU -lGL */
#   endif
#   if DEVELOP
#    define C_SWITCH_OPTIMIZE -g -Wall -pedantic -Wmissing-prototypes
#    define LD_SWITCH_OPTIMIZE -g
#   endif
#   if _rh7
/* For the Redhat 7 build, hardwire use of hoops8.0 and disable hoops stream */
#if DEVELOP
#    define LIB_HOOPS -lhoopsd
#else
#    define LIB_HOOPS -lhoops
#endif

#    define HOOPS_INCLUDES -I../include/hoops/3dgs -I../include/hoops/base_stream -I../include/hoops/stream -I../include/hoops/utility
#    define HAVE_HOOPS_STREAMS 0
#    define CPP_SWITCH_SYSTEM -DHAVE_HOOPS_STREAMS=0 -DXM_1_2_XTMACROS -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -I/usr/X11R6/include -I/usr/X11R6/include/Xm
#   else
#    define CPP_SWITCH_SYSTEM -DXM_1_2_XTMACROS -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -I/usr/X11R6/include -I/usr/X11R6/include/Xm
#   endif
#   define CPP_SWITCH_PIC -fpic
#   define LD_SWITCH_SYSTEM -L/usr/X11R6/lib
#   define LIBS_MOTIF -Wl,-Bstatic -z muldefs -lXm -lXmu -lXp -Wl,-Bdynamic
#   define LIBS_UI LIBS_MOTIF LIBS_X11
#   define LIBS_TIFF -Wl,-Bstatic -ltiff -Wl,-Bdynamic
#   define LIBS_PNG -Wl,-Bstatic -lpng -lz -Wl,-Bdynamic
#   define LIBS_XPM -Wl,-Bstatic -lXpm -Wl,-Bdynamic
/* We must link to shared X11 in order to link to shared OpenGL */
#   if _rh8
#    define STATIC_X11 1
#   endif
#   ifndef STATIC_X11
#    define STATIC_X11 0
#   endif
#   if STATIC_X11
#    define LIBS_X11 -Wl,-Bstatic -lXt -lXext -lX11 -lSM -lICE -Wl,-Bdynamic
#   else
#    define LIBS_X11 -lXt -lXext -lX11
#   endif

#  endif /* MAKEFILE */

#endif /* _lnx86 */

#if _alpha
# define CORTEX_ARCH alpha
# define HAVE_JPEG 0
# define HAVE_MPEG 0
# define WORKING_CXX 1

# ifdef MAKEFILE

#  ifndef LIBS_GR
#   define LIBS_GR -lXext
#  endif
#  define LIBS_SYSTEM -lm -ldnet_stub
#  define RANLIB_ ranlib
#  define CPP_SWITCH_SYSTEM -Dunix

#  if DEVELOP
#   define C_SWITCH_OPTIMIZE -g -verbose
/* -msg_display_number */
/* -w0 */
#   define LD_SWITCH_OPTIMIZE -g -verbose -WL,-v -msg_display_number
/* -WL,-warning_unresolved  */
#  else
/*#   define C_SWITCH_OPTIMIZE -O -Olimit 2000 */
#   define C_SWITCH_OPTIMIZE -tune ev5 -O3
#  endif

#  define C_SWITCH_SYSTEM -non_shared -migrate -std1 -trapuv
/* -misalign -assume noaligned_objects */
/* use ANSI C compilation mode */

#  ifdef CPP_
#   undef CPP_
#  endif
#  define CPP_ /usr/bin/cpp -N

#  define HAVE_CPP_M _alpha


#  define CXX_ cxx
#  define LINK_ $(CXX)
#  ifndef CXX_FLAGS
#   define CXX_FLAGS -newcxx -non_shared -migrate -std1 -trapuv
/* -misalign */
/* -assume noaligned_objects */
/* stlport not working */
#  endif

# endif /* MAKEFILE */

#endif /* _alpha */

#if _lnarm64
#  define GRAPHICS 0
#  define CX_GUI 0
#endif   /* _lnarm64 */
