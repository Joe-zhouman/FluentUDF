/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#include "dll.h"

#if SEEM
#if !PARALLEL
#if ANSYS_LIB
#if sys_hpux11_64 || (_linux && (!sys_lnx86))
#define ANSYS_BININI binini_
#endif
#if _NT
#define ANSYS_BININI BININI
#define ANSYS_BINWRT BINWRT
#define ANSYS_BINRD  BINRD
#define ANSYS_BINIQR BINIQR
#define ANSYS_BINSET BINSET
#define ANSYS_BINTF0 BINTFO
#define ANSYS_BINHED BINHED
#define ANSYS_BINCL0 BINCLO
#define ANSYS_INEXC4 INEXC4
#define ANSYS_TEMP_INEXC4 ANSYS_INEXC4
#else
#if __sun  ||  __sgi  || __alpha || _linux || sys_hpux11_64 || sys_lnia64
#if sys_lnx86
#define ANSYS_BININI ansys_lib.binini
#define ANSYS_BINWRT ansys_lib.binwrt
#define ANSYS_BINRD  ansys_lib.binrd
#define ANSYS_BINIQR ansys_lib.biniqr
#define ANSYS_BINSET ansys_lib.binset
#define ANSYS_BINTF0 ansys_lib.bintfo
#define ANSYS_BINHED ansys_lib.binhed
#define ANSYS_BINCL0 ansys_lib.binclo
#define ANSYS_INEXC4 ansys_lib.inexc4
#else
#define ANSYS_BINWRT binwrt_
#define ANSYS_BINRD  binrd_
#define ANSYS_BINIQR biniqr_
#define ANSYS_BINSET binset_
#define ANSYS_BINTF0 bintfo_
#define ANSYS_BINHED binhed_
#define ANSYS_BINCL0 binclo_
#define ANSYS_INEXC4 inexc4_
#endif
#else
#define ANSYS_BINWRT binwrt
#define ANSYS_BINRD  binrd
#define ANSYS_BINIQR biniqr
#define ANSYS_BINSET binset
#define ANSYS_BINTF0 bintfo
#define ANSYS_BINHED binhed
#define ANSYS_BINCL0 binclo
#define ANSYS_INEXC4 inexc4
#endif
#if !(_linux)
#define ANSYS_TEMP_INEXC4(a,b,c,d) ANSYS_INEXC4(a,c,d)
#else
#define ANSYS_TEMP_INEXC4(a,b,c,d) ANSYS_INEXC4(a,c,d,b)
#endif
#endif


#if __alpha || sys_hpux11_64
#define INT int
#else
#define INT long int
#endif

#if _NT
#define ANSYS_EXPORT __stdcall
extern INT ANSYS_EXPORT ANSYS_BININI(INT *);
#else
#define ANSYS_EXPORT
#endif

#if !sys_lnx86
extern INT ANSYS_EXPORT ANSYS_BINWRT(INT *, INT *, INT *, INT *, INT *,  INT *);
extern INT ANSYS_EXPORT ANSYS_BINIQR(INT *, INT *);
extern void ANSYS_EXPORT ANSYS_BINHED(INT *, INT *, INT *, INT *);
extern void ANSYS_EXPORT ANSYS_BINRD(INT *, INT *, INT *, INT *, INT *, INT *);
#if _NT
extern INT ANSYS_EXPORT ANSYS_BINSET(INT *, INT *, INT *, INT *, INT *, INT *, char *, unsigned int, INT *, INT *, INT *);
extern void ANSYS_EXPORT ANSYS_BINTF0(char title[2][80], unsigned int, char *, unsigned int, INT *, INT *);
extern void ANSYS_EXPORT ANSYS_BINCL0(INT *, char *, unsigned int, INT *);
extern void ANSYS_EXPORT ANSYS_INEXC4(char *, unsigned int, INT *, INT *);
#elif _linux
extern int ANSYS_EXPORT ANSYS_BININI(INT *);
extern INT ANSYS_EXPORT ANSYS_BINSET(INT *, INT *, INT *, INT *, INT *, INT *, char *, INT *, INT *, INT *, INT);
extern void ANSYS_EXPORT ANSYS_BINTF0(char title[2][80], char *, INT *, INT *, INT, INT);
extern void ANSYS_EXPORT ANSYS_BINCL0(INT *, char *, INT *, INT);
extern void ANSYS_EXPORT ANSYS_INEXC4(char *, INT *, INT *, INT);
#else
extern INT ANSYS_EXPORT ANSYS_BINSET(INT *, INT *, INT *, INT *, INT *, INT *, char *, INT *, INT *, INT *);
extern void ANSYS_EXPORT ANSYS_BINTF0(char title[2][80], char *, INT *, INT *);
extern void ANSYS_EXPORT ANSYS_BINCL0(INT *, char *, INT *);
extern void ANSYS_EXPORT ANSYS_INEXC4(char *, INT *, INT *);
#endif
#else
typedef struct Ansys_Lib_Lnx86
{
  INT (*binwrt)(INT *, INT *, INT *, INT *, INT *,  INT *);
  INT (*biniqr)(INT *, INT *);
  void (*binhed)(INT *, INT *, INT *, INT *);
  void (*binrd)(INT *, INT *, INT *, INT *, INT *, INT *);
  int (*binini)(INT *);
  INT (*binset)(INT *, INT *, INT *, INT *, INT *, INT *, char *, INT *, INT *, INT *, INT);
  void (*bintfo)(char title[2][80], char *, INT *, INT *, INT, INT);
  void (*binclo)(INT *, char *, INT *, INT);
  void (*inexc4)(char *, INT *, INT *, INT);
} ansys_lib_t;
#endif

#undef ANSYS_EXPORT

#define ANSYS_TITLE_CHAR 80
#define ANSYS_VARIABLE_LENGTH 5
#define ANSYS_RESULT_NUM 40
#define ANSYS_FILE_CHAR 50
#define ANSYS_JOB_CHAR  8
#define ANSYS_DATASETS 1
#define ANSYS_UNIT 1
#define ANSYS_CONVERGENCE_KEY 1
#define ANSYS_BIT_MASK_NUMBER 8391680
#define ANSYS_ELEMENT_TYPE 1
#define ANSYS_ELEMENT_SHAPE_3D 6
#define ANSYS_ELEMENT_SHAPE_2D 4
#define ANSYS_FREQ_VAL 1
#define ANSYS_GLOBAL_ITENUM 100
#define ANSYS_LOAD_NUM 1
#define ANSYS_RXTRAP 1
#define ANSYS_ITENUM_START 1
#define ANSYS_DOF_POINTER 373
#define ANSYS_DOF_HED_POINTER 306
#define ANSYS_UNSTEADY 1
#define ANSYS_STEADY 0
#define ANSYS_3D 142
#define ANSYS_2D 141
#define ANSYS_NULL 0
#define ANSYS_DOFR_VX 10
#define ANSYS_DOFR_VY 11
#define ANSYS_DOFR_VZ 12
#define ANSYS_DOFR_TEMP 20
#define ANSYS_DOFR_PRES 19
#define ANSYS_DOFR_TKE 23
#define ANSYS_DOFR_TDS 24
#define ANSYS_TIME_NUM 1000
#define ANSYS_DATA_NUM 2000
#define ANSYS_STEP_NUM 3000
#define ANSYS_RES_MAX 1000
#define ANSYS_RES_KEY 12
#define ANSYS_NUMDOF_3D 7
#define ANSYS_NUMDOF_2D 6
#define ANSYS_INTPDP 2
#define ANSYS_LOAD_STEP 1
#define ANSYS_SUB_STEP 1
#define ANSYS_GEO_NUM 20
#define ANSYS_CSYSIZ 24
#define ANSYS_ETYSIZ 150
#define ANSYS_NODE_3D 8
#define ANSYS_NODE_2D 4
#define ANSYS_TYPE_DESC 150
#define ANSYS_TITLE_NUM 2
#define ANSYS_SOLHED_NUM 100
#define ANSYS_TITLE1_NUM 20
#define ANSYS_SOLHED_EXT 200
#define ANSYS_DENSITY 1
#define ANSYS_VISCOSITY 2
#define ANSYS_PTOT  18
#define ANSYS_TTOT 19
#define ANSYS_PCOEF 20
#define ANSYS_HEATFLUX 23
#define ANSYS_HFLM 24
#define ANSYS_HEDEXT 64
#define ANSYS_VISCOSITY_EFF 3
#define ANSYS_COND 4
#define ANSYS_COND_EFF 5
#define ANSYS_STREAM_FUNCTION 22
#define ANSYS_SPHT 27
#define ANSYS_TAUW 26
#define ANSYS_MACH_NUMBER  21

#endif /*ANSYS_LIB*/
FLUENT_EXPORT void Write_Ansys_Domain(const char *filename, Domain *, Pointer);
#endif /*!PARALLEL*/
#endif /*SEEM */

