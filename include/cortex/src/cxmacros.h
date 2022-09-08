/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/* @(#)cxmacros.h 1.17 09/04/97
 */

#ifndef _CXMACROS_H
#define _CXMACROS_H

#define CX_BIG_POS 1.0e+20
#define CX_BIG_NEG -1.0e+20


#if (defined(__alpha) && ! _NT) || hiux
# include <sys/param.h>
#else
# ifndef MIN
#  define MIN(a,b)((a)>(b)?(b):(a))
# endif
# ifndef MAX
#  define MAX(a,b)((a)<(b)?(b):(a))
# endif
#endif

#ifndef ABS
#define ABS(a) (((a)<0.)?-(a):(a))
#endif

#ifndef SQR
#define SQR(A) ((A)*(A))
#endif

#ifndef SETMAX
#define SETMAX(i,j)if((j)>i)i=j;else
#endif

#ifndef SETMIN
#define SETMIN(i,j)if((j)<i)i=j;else
#endif

#ifndef STREQ
#define STREQ(a,b) (strcmp(a,b) == 0)
#endif

#ifndef STRNEQ
#define STRNEQ(a,b,n) (strncmp(a,b,n) == 0)
#endif

#ifndef NULLP
#define NULLP(x)  (((x) == NULL) ? 1 : 0)
#endif

#ifndef NNULLP
#define NNULLP(x) (!NULLP(x))
#endif

#ifndef STRNCPY
#define STRNCPY(dest, source, size)\
        strncpy(dest, source, size);\
        if (strlen(source) >=(size)) { fprintf(stderr, "STRNCPY Error: source value \"%s\" is being clipped after %d chars\n", source, (size)-1);\
            dest[size]='\0';}
#endif

/* (x,y,0) X (x,y,0) */


/* who uses this, I couldn't find any use of these macros in cortex or client */
#ifndef VECTOR_OPER_INC
#define VECTOR_OPER_INC

# define N2D_CROSS_X(x1,y1,x2,y2) (-(y2))
# define N2D_CROSS_Y(x1,y1,x2,y2) (x2)

#ifndef _FLUENT_FLOW_H   /* Avoid warning "incompatible redefinition of macro" */
# define N3D_CROSS_X(x1,y1,z1,x2,y2,z2) (((y1)*(z2))-((y2)*(z1)))
# define N3D_CROSS_Y(x1,y1,z1,x2,y2,z2) (((z1)*(x2))-((z2)*(x1)))
# define N3D_CROSS_Z(x1,y1,z1,x2,y2,z2) (((x1)*(y2))-((x2)*(y1)))
# define ND_MAP(x,y,z,op,u,v,w)(x)op(u),(y)op(v),(z)op(w)
# define ND_OP(op,x,y,z)((x)op(y)op(z))
#define ND_SUM(x,y,z)ND_OP(+,x,y,z)
#define ND_DOT(x,y,z,u,v,w)ND_SUM((x)*(u),(y)*(v),(z)*(w))
#define ND_MAG2(x,y,z)ND_DOT(x,y,z,x,y,z)
#define ND_SET(x,y,z,u,v,w)ND_MAP(x,y,z,=,u,v,w)
#endif

#define N3D_SET(x,y,z,u,v,w) ((x) = (u), (y) = (v), (z) = (w))
#define N2D_SET(x,y,u,v) (x) = (u); (y) = (v);
#define N3D_IP(x,y,z,u,v,w) ((x)*(u)+(y)*(v)+(z)*(w))
#define N2D_IP(x,y,u,v) ((x)*(u)+(y)*(v))

#ifndef PI
# define PI 3.14159265358979323846
#endif

#ifndef ALMOST_ZERO
#define ALMOST_ZERO 1.e-10
#endif
#define ZEROP(A) (ABS(A) <= ALMOST_ZERO)
#define VZEROP(A) (ZEROP(A[0]) && ZEROP(A[1]) && ZEROP(A[2]))
#define MAG(A) (sqrt((double)(SQR(A[0])+SQR(A[1])+SQR(A[2]))))
#define CROSS_PROD(A,B,R) { \
        R[0] = A[1]*B[2] - A[2]*B[1]; \
            R[1] = A[2]*B[0] - A[0]*B[2]; \
          R[2] = A[0]*B[1] - A[1]*B[0]; \
            }

#ifndef DOT_PROD
#define DOT_PROD(A,B)  ( A[0]*B[0] + A[1]*B[1] + A[2]*B[2] )
#endif

#ifndef UNIT_VECT
#define UNIT_VECT(A,R) {if (VZEROP(A)) R[0] = R[1] = R[2] = 0.0; \
      else { \
          float m; \
        m = MAG(A); \
            R[0] = A[0]/m; \
          R[1] = A[1]/m; \
              R[2] = A[2]/m; } }
#endif

#define SET_VECT(v,x,y,z) (((v)[0]=(x)),((v)[1]=(y)),((v)[2]=(z)))
#define SET_VECT_FROM_VECT(TO,FROM) { TO[0] = FROM[0]; TO[1] = FROM[1]; TO[2] = FROM[2]; }
#define SCALE_VECT(A,S,R) { R[0] = A[0]*(S); R[1] = A[1]*(S); R[2] = A[2]*(S); }
#define ADD_VECT(A,B,R) { R[0] = A[0] + B[0]; R[1] = A[1] + B[1]; R[2] = A[2] + B[2]; }
#define SUB_VECT(A,B,R) { R[0] = A[0] - B[0]; R[1] = A[1] - B[1]; R[2] = A[2] - B[2]; }
#define POINT_VECT(A,R) {R[0] = A[1][0] - A[0][0]; R[1] = A[1][1] - A[0][1]; R[2] = A[1][2] - A[0][2];}
#define IS_EQUAL_VECT(A,B) (A[0] == B[0] && A[1] == B[1] && A[2] == B[2])
#define NOT_ALL_ZERO_VECT(A) (!(A[0] == 0 && A[1] == 0 && A[2] == 0))

#endif /* VECTOR_OPER_INC */

/* for string literals */
#define CATSTR(s1, s2) s1 s2
#define CATSTR2(s1, s2, s3) s1 s2 s3

#if _NT

#define CAT(s1,s2) s1##s2
#define CAT2(s1,s2,s3) s1##s2##s3
#define QUOTE(name) #name

#else

#if __STDC__ || sgi || _nec || defined(__cplusplus) || defined(c_plusplus) || defined(_fujitsu_pp)
#define CAT(s1,s2) s1##s2
#define CAT2(s1,s2,s3) s1##s2##s3
#define QUOTE(name) #name
#else
#define CAT(s1,s2) s1/**/s2
#define CAT2(s1,s2,s3) s1/**/s2/**/s3
#define QUOTE(name) "name"
#endif

#endif

#define    CATTWOARGS(arg1, arg2)         CAT(arg1, arg2)
#define  CATTHREEARGS(arg1, arg2, arg3)  CAT2(arg1, arg2, arg3)
/* These are needed if (at least) one arg is a macro that you want to be expanded. */


/* l = ((x y z) l) */
#define LIST_CONS_3D(l,x,y,z) \
  l = cons(NIL,l),  \
  CAR(l) = cons(NIL,NIL), \
  CAR(CAR(l)) = x,  \
  CDR(CAR(l)) = cons(NIL,NIL),  \
  CAR(CDR(CAR(l))) = y, \
  CDR(CDR(CAR(l))) = cons(NIL,NIL), \
  CAR(CDR(CDR(CAR(l)))) = z

#define LIST_CONS_2D(l,x,y) \
  l = cons(NIL,l),  \
  CAR(l) = cons(NIL,NIL), \
  CAR(CAR(l)) = x,  \
  CDR(CAR(l)) = cons(NIL,NIL),  \
  CAR(CDR(CAR(l))) = y

/* in cxbool.h */
/*
typedef char boolean;
*/
/*string needed for newcx*/
#define CX_MAIN_WINDOW      "cx-main-window"/*used only for newcx*/
#define CX_GRAPHICS_LAYOUT_INDEX  "graphics-layout-index"
enum CxMessageType {CXMSGWARNING = -1, CXMSGDEFAULT = 0};

#if _NT
#   if _MSC_VER < 1900
#   define snprintf _snprintf
#   endif
#endif

#endif /* _CXMACROS_H */
