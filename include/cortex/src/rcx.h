/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _Rcx_h
#define _Rcx_h

#ifndef CX_PROGRAM

#include "seem.h"
#include "cxfields.h"

/* An arbitrary port for the portmapper (decimal 805306487) */
#define CX_PROGRAM 0x30000077
#define CX_VERSION 1

/* An arbitrary port for the portmapper */
#define SV_PROGRAM 0x30000097
#define SV_VERSION 1

/* RCX data structures */

# define CX_XDR XDR
# define CX_XPRT SVCXPRT
# define CX_SVC_REQ struct svc_req *
# define CX_CLIENT CLIENT

/* RPC argument data structures. */

/* Maximum length of a string argument (including the terminal '\0'). */
#define HOOPS_STRING_LENGTH 256
#define CORTEX_STRING_LENGTH HOOPS_STRING_LENGTH

/* Maximum length of lists of floats and ints. */
/*  #define HOOPS_FLOATS_LENGTH 2040  (dt - Nov 10, 1998) */
#define HOOPS_FLOATS_LENGTH 20400
#define HOOPS_INTS_LENGTH 1020
#define HOOPS_LONGS_LENGTH 1020
#define HOOPS_BYTES_LENGTH 81920
#define CORTEX_FLOATS_LENGTH HOOPS_FLOATS_LENGTH

#if _AIX
#ifndef TCP_MAX_REQUEST_SIZE
#define TCP_MAX_REQUEST_SIZE 8388608
#endif
#define BREAK_RPC_MSGS 1
/* keep the size less than max allowed  31/32(= 0.96875).
   This number is arbitrary just to make sure
   the resulting numbers are integers less than one
   but close to one.*/
#define MAX_FLT_RPC_LEN 0.96875*TCP_MAX_REQUEST_SIZE/sizeof(float)
#define MAX_INT_RPC_LEN 0.96875*TCP_MAX_REQUEST_SIZE/sizeof(int)
#define MAX_LONG_RPC_LEN 0.96875*TCP_MAX_REQUEST_SIZE/sizeof(long)
#else
#define BREAK_RPC_MSGS 0
#endif


/* Variable length list of floats */
typedef struct float_list
{
  float *f;
  unsigned int n;
} float_list;

/* A re-numbered float list: */
typedef struct rfloat_list
{
  float *f;
  unsigned int n;
#if WIN64
  LONG_PTR k;
#else
  long k;
#endif
} rfloat_list;

typedef struct double_list
{
  double *d;
  unsigned int n;
} double_list;

typedef struct xy_float_array
{
  unsigned int n;
  float *x;
  float *y;
  int *active;
  unsigned int nactive;
} xy_float_array;

typedef struct int_list
{
  int *i;
  unsigned int n;
#if BREAK_RPC_MSGS
  unsigned int n_total;
#endif
} int_list;

typedef struct string
{
  char *s;
} string;

typedef struct string_list
{
  char **s;
  unsigned int n;
} string_list;

/* for CX_Start_Draw_Grid rpc */
typedef struct int2_str2
{
  int i, j;
  char *s, *t;
} int2_str2;

/* Lots of HOOPS calls take exactly two strings. */
typedef struct two_strings
{
  char *s1, *s2;
} two_strings;

typedef struct string_int
{
  char *s;
  int i;
} string_int;

/* Shell data structure. */
typedef struct shell
{
  unsigned int np, nf, nk;
  float *points;
  int *faces;
  long *indices;                /* cxindex */
  long k;
} shell;

/* tgrid shell data structure. */
/* used to account for (USE_INT64) and cxindex that are
 * not used in cortex currently, once USE_INT64 and cxindex are available the
 * indices can be set cxindex */
typedef struct shell_xfer
{
  int index, order;
  unsigned int np, nfl, nf;
  float *points;
  int *facets;
  void *indices;             /* cxindex (int for rinsert, long for rlinsert */
  void *flags;
  float *fsize;
  float *fskew;
#if BREAK_RPC_MSGS
  unsigned int np_total, nfl_total, nf_total;
#endif
} shell_xfer;

typedef struct shell_multi_xfer
{
  int nshells;
  int ntotalp, ntotalfl, ntotalf;
  int *index, *order;
  unsigned int *np, *nfl, *nf;
  float *points;
  int *facets;
  void *indices;             /* cxindex (int for rinsert, long for rlinsert */
  void *flags;
  float *fsize;
  float *fskew;
  char *seg;
#if BREAK_RPC_MSGS
  unsigned int np_total, nfl_total, nf_total;
#endif
} shell_multi_xfer;

/*Cylinder data structure */
typedef struct cylinder_str
{
  float *points;
  int np;
  float r;
  char *s;
} cylinder_str;


typedef struct surface_xfer
{
  int index, nf, dim;
  unsigned int np, nfl;
  float *points;
  int *facets;
#if BREAK_RPC_MSGS
  unsigned int np_total, nfl_total;
#endif
} surface_xfer;


typedef struct point_str
{
  float x, y, z;
  char *s;
} point_str;

/* pathline xfer data structure - GM */
typedef struct path_xfer
{
  unsigned int size_p, size_sc, size_i;
  float     *points;
  float *scalars;
  int         *path_ints;
} path_xfer;

typedef struct camera_by_volume
{
  char *p;
  float x0, x1, y0, y1;
} camera_by_volume;


/* Image data.  (dt) */
typedef struct image_data
{
  float x, y, z;
  char *format;
  int width, height;
  unsigned char *data;
} image_data;

/*  RCX data (de)serialization protocol functions. Hide the underlying
 *  XDR procedures to allow us to bypass them if desired.
 */

# define cx_xdr_void  xdr_void
# define cx_xdr_u_char  xdr_u_char
# define cx_xdr_short xdr_short
# define cx_xdr_int xdr_int
# define cx_xdr_u_int   xdr_u_int
# define cx_xdr_enum  xdr_enum
# define cx_xdr_long  xdr_long
# define cx_xdr_fixnum  xdr_long
# define cx_xdr_float xdr_float
# define cx_xdr_double  xdr_double
# define cx_xdr_flonum  xdr_double
#if __alpha
# define cx_xdr_array(x,a,n,l,s,p)  xdr_array(x,a,n,l,s,(xdrproc_t)p)
#else
# define cx_xdr_array xdr_array
#endif
# define cx_xdr_string  xdr_string
# define cx_xdr_bytes   xdr_bytes

int xdr_hoops_floats    (CX_XDR *, float_list *);
int xdr_hoops_doubles   (CX_XDR *, double_list *);
int xdr_hoops_rfloats   (CX_XDR *, rfloat_list *);
int xdr_hoops_ints    (CX_XDR *, int_list *);
int xdr_hoops_string    (CX_XDR *, char **);
int xdr_hoops_string_int  (CX_XDR *, string_int *);
int xdr_hoops_2strings    (CX_XDR *, two_strings *);
int xdr_hoops_shell   (CX_XDR *, shell *);
int xdr_hoops_lshell    (CX_XDR *, shell *);
int xdr_hoops_rshell    (CX_XDR *, shell *);
int xdr_hoops_point_str   (CX_XDR *, point_str *);
int xdr_hoops_cambyvol    (CX_XDR *, camera_by_volume *);
int xdr_hoops_image   (CX_XDR *, image_data *);
int xdr_hoops_cylinder_str      (CX_XDR *, cylinder_str *);

int xdr_cortex_floats   (CX_XDR *, float_list *);
int xdr_cortex_doubles(CX_XDR *, double_list *);
int xdr_cortex_xyfloats         (CX_XDR *, xy_float_array *);
int xdr_cortex_int2_str2  (CX_XDR *, int2_str2 *);
int xdr_cortex_surface_xfer (CX_XDR *, surface_xfer *);
int xdr_rshell_xfer(CX_XDR *xdrs, shell_xfer *s);
int xdr_rshell_multi_xfer(CX_XDR *xdrs, shell_multi_xfer *s);
int xdr_rlshell_xfer(CX_XDR *xdrs, shell_xfer *s);
int xdr_rlshell_multi_xfer(CX_XDR *xdrs, shell_multi_xfer *s);
int xdr_cortex_surface_data (CX_XDR *xdrs, surface_data *s);
int xdr_cortex_surface_data_list(CX_XDR *xdrs, surface_data_list *sdl);
int xdr_cortex_vector(CX_XDR *xdrs, vec *v);
int xdr_cortex_vector_data  (CX_XDR *xdrs, vector_data *vd);
int xdr_cortex_vector_data_list(CX_XDR *xdrs, vector_data_list *vdl);
int xdr_cortex_path_xfer  (CX_XDR *, path_xfer *);
int xdr_cortex_wrap_string      (CX_XDR *, char ** );
int xdr_cortex_string         (CX_XDR *, string *);
int xdr_cortex_string_list  (CX_XDR *, string_list *);
int xdr_cortex_string_int (CX_XDR *, string_int *);
int xdr_cortex_encode_pointer   (XDR *, Pointer *);
int xdr_cortex_decode_pointer   (XDR *, Pointer *);
int xdr_int_array_xfer    (CX_XDR *, int_list *);

/* RHOOPS/RCX procedure mappings. */

enum rcx_request
{
  HR_DEFINE_COLOR_NAME = 1, /* Leave space for the NULLPROC */
  HR_SET_COLOR,
  HR_SET_COLOR_BY_INDEX,
  HR_SET_HEURISTICS,
  HR_SET_MARKER_SYMBOL,
  HR_SET_USER_OPTIONS,
  HR_SET_VISIBILITY,
  HR_FLUSH_CONTENTS,
  HR_INSERT_MARKER,
  HR_RINSERT_MARKER,
  HR_INSERT_POLYGON,
  HR_RINSERT_POLYGON,
  HR_INSERT_POLYLINE,
  HR_RINSERT_POLYLINE,
  HR_INITIALIZE_SHELL,
  HR_INSERT_SHELL,
  HR_RINSERT_SHELL,
  HR_CLOSE_SEGMENT,
  HR_INCLUDE_SEGMENT,
  HR_OPEN_SEGMENT,
  HR_DELETE_SEGMENT,
  HR_UPDATE_DISPLAY,
  HR_STYLE_SEGMENT,
  HR_SET_MARKER_SIZE,
  HR_SET_TEXT_ALIGNMENT,
  HR_SET_TEXT_FONT,
  HR_INSERT_CIRCLE,
  HR_INSERT_TEXT,
  HR_SET_CAMERA_BY_VOLUME,
  HR_INSERT_MESH,
  HR_RINSERT_MESH,
  HR_INSERT_IMAGE,
  HR_TRANSLATE_OBJECT,
  HR_ROTATE_OBJECT,
  HR_SET_LINE_WEIGHT,
  HR_SET_LINE_PATTERN,
  HR_INSERT_CYLINDER,

  MIN_RCX_REQUEST = 4000, /* Leave space for more HR_ procs */

  RCX_COLOR_BY_VALUE,
  RCX_PERIODIC,
  RCX_SYMMETRY,
  RCX_SET_CONTOUR_OPTIONS,
  RCX_CONTOUR_TRIANGLES,
  RCX_CONTOUR_LINES,
  RCX_CONTOUR_POLYS,
  RCX_VECTORS,
  RCX_SET_COLOR,
  RCX_COLOR_SEGMENTS,

  RCX_SET_VIS_NAME,
  RCX_INSERT_PATHLINE,

  RCX_DEFINE_SURFACE,
  RCX_DESTROY_SURFACE,
  RCX_APPEND_SURFACE,
  RCX_CONTOUR_SURFACE,
  RCX_PROFILE_SURFACE,
  RCX_DISPLAY_SURFACE,
  RCX_DESTROY_SURFACE_ALL,
  RCX_SUSPEND_ALL_SURFACES,
  RCX_INIT_DEFINE_SURFACE,
  RCX_FILL_FIELD_DATA,
  RCX_FILL_VECTOR_DATA,

  RCX_START_DRAW_GRID,
  RCX_END_DRAW_GRID,
  RCX_INSERT_LINE,
  RCX_INSERT_TRIANGLE,
  RCX_INSERT_TETRA,
  RCX_INSERT_QUAD,
  RCX_INSERT_HEX,
  RCX_RINSERT_LINE,
  RCX_RINSERT_POLYLINE,
  RCX_RINSERT_TRIANGLE,
  RCX_RINSERT_TETRA,

  RCX_INIT_LICENSE,
  RCX_CHECKOUT_LICENSE,
  RCX_CHECKOUT_N_LICENSES,
  RCX_CHECKOUT_N_NEUTRAL_LICENSES,
  RCX_CHECK_FEATURE_MATCH,
  RCX_FREE_LICENSE,
  RCX_ANSYS_AVAIL,
  RCX_IS_EDUCATIONALONLY,
  RCX_IS_EDUCATIONALONLYLOGO,
  RCX_IS_STUDENTONLY,
  RCX_IS_POSTONLY,
  RCX_IS_MESHING,
  RCX_CHECK_LICENSE_CONNECTION,
  RCX_GET_LICENSE_TIMEOUT,
  RCX_GET_LICENSE_LEVEL,

  RCX_GET_INTERRUPT_COUNT,
  RCX_IS_ANY_WORKSPACE_CONNECTED,

  RCX_CLIENT_LS,
  RCX_SERVER_VERSION,
  RCX_COMMAND_PORT,
  RCX_GET_CLIENT_ID,
  RCX_SET_CLIENT_ID,

  RCX_START_FILL_ARRAY,
  RCX_FILL_ARRAY,

  RCX_START_ACTIVE_ARRAY,
  RCX_FILL_ACTIVE_ARRAY,

  RCX_INSERT_PYR,
  RCX_INSERT_WEDGE,
  RCX_INSERT_POLYHEDRON,

  RCX_START_GRID,
  RCX_ADD_GRID_PTS,
  RCX_REUSE_GRID_PTS,
  RCX_ADD_GRID_FACETS,
  RCX_END_GRID,
  RCX_DELETE_GRID,
  RCX_DISPLAY_GRID,
  RCX_OPEN_GRID,
  RCX_SET_GRID_ATTR,
  RCX_SET_GRID_ELEM,
  RCX_CLOSE_GRID_ATTR,
  RCX_DELETE_ALL_GRIDS,

  RCX_SET_SV_RPC_PORT,
  RCX_SEND,
  RCX_SET_SOLVER_RESULT,
  RCX_KILL_SOLVER,
  RCX_GET_RPC_STREAM_P,

  RCX_RINSERT_QUAD,
  RCX_RINSERT_HEX,
  RCX_RINSERT_PYR,
  RCX_RINSERT_WEDGE,
  RCX_RINSERT_POLYGON,
  RCX_RINSERT_POLYHEDRON,

  RCX_RLINSERT_LINE,
  RCX_RLINSERT_POLYLINE,
  RCX_RLINSERT_TRIANGLE,
  RCX_RLINSERT_TETRA,
  RCX_RLINSERT_QUAD,
  RCX_RLINSERT_HEX,
  RCX_RLINSERT_PYR,
  RCX_RLINSERT_WEDGE,
  RCX_RLINSERT_POLYGON,
  RCX_RLINSERT_POLYHEDRON,

  RCX_CALL_VI,

  RCX_LICENSE_FEATURE,
  RCX_LICENSE_KEY,

  RCX_START_XY_PLOT_DATA,
  RCX_XY_PLOT_DATA,
  RCX_UPDATE_GRAPHICS,

  RCX_CHECK_FEATURE_VALID,

  RCX_REPORT_HOST_PROCESS_STATUS,
  RCX_START_MONITOR_THREAD,

  RCX_INIT_RINSERT_SHELL,
  RCX_RINSERT_SHELL,
  RCX_RLINSERT_SHELL,

  RCX_INIT_RINSERT_MULTI_SHELL,
  RCX_RINSERT_MULTI_SHELL,
  RCX_RLINSERT_MULTI_SHELL,

  RCX_SERVER_UPDATE_ELEMENT_COUNT,
  RCX_SERVER_UPDATE_NODE_COUNT,
  RCX_SERVER_UPDATE_ELEMENT_TYPES,
  RCX_SERVER_UPDATE_ELEMENT_IDS,
  RCX_SERVER_UPDATE_ELEMENT_C0_IDS,
  RCX_SERVER_UPDATE_ELEMENT_C1_IDS,
  RCX_SERVER_UPDATE_ELEMENT_NODE_COUNTS,
  RCX_SERVER_UPDATE_ELEMENT_NODE_IDS,
  RCX_SERVER_UPDATE_NODE_IDS,
  RCX_SERVER_UPDATE_NODE_COORDS,
  RCX_SERVER_UPDATE_NODE_DATA,
  RCX_SERVER_GET_NODE_DATA,
  RCX_SC_GET_STATUS,
  RCX_SC_SET_ERR_MSG,
  RCX_SC_GET_NEW_MESHFILTER_ID,
  RCX_SC_APPLY_MESHFILTER_STATUS,
  RCX_SC_APPLY_REGIONFILTER_STATUS,
  RCX_SC_GET_REGIONS,
  RCX_SC_GET_REGIONS_START,
  RCX_SC_GET_TOPOL_DIM,
  RCX_SC_GET_NEW_RESULTFILTER_ID,
  RCX_SC_APPLY_RESULTFILTER_STATUS,
  RCX_SC_GET_RESULTID_START,
  RCX_SC_GET_RESULT_TID_START,
  RCX_SC_GET_RESULT_TID,
  RCX_SC_GET_RESULTID,
  RCX_SERVER_UPDATE_MESH_BUFFER_SIZE,
  RCX_MESSAGE,
  RCX_WARNING_MESSAGE,
  RCX_APIPINITIALIZE,
  RCX_APIPFINALIZE,
  RCX_APIPPOSTSTRING,
  RCX_APIPPOPASNEEDED,
  RCX_APIPENABLED,
  RCX_SEND_STRING_LIST,
  RCX_LAST      /* Don't put anything after this one */
};

#endif /* CX_PROGRAM */

#endif /* _Rcx_h */
