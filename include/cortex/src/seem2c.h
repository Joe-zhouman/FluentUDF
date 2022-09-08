/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/*
 *  seem2c.h
 *  @(#)seem2c.h  1.5 04/07/97
 */
#ifndef NULLP
#define NULLP(x)((x)==NULL)
#endif
#define LONG_ARG(p,m)   fixnum_arg(p,m)
#define DOUBLE_ARG(p,m) flonum_arg(p,m)
#define FLOAT_ARG(p,m)  (float)flonum_arg(p,m)
#define INT_ARG(p,m)    (int)fixnum_arg(p,m)
#define INT64_T_ARG(p,m)    (int64_t)fixnum_arg(p,m)
#define CHAR_ARG(p,m) (TYPEP(p,tc_char) ? CHAR(p) :\
       (TYPEP(p,tc_false) ? (char) 0 :\
        (seem_err(m,p), (char) 0)))
#define PORT_ARG(p,m) (TYPEP(p,tc_port) ? PORT(p) : (seem_err(m,p),(Port *)NULL))
#define PROCEDURE_ARG(p,m) (TYPEP(p,tc_symbol) ? p :\
          (TYPEP(p,tc_false) ? (Pointer)NULL :\
           (seem_err(m,p),(Pointer)NULL)))
#define STRING_ARG(p,m) (TYPEP(p,tc_string) ? STRING(p) :\
       (TYPEP(p,tc_symbol) ? PNAME(p) :\
        (TYPEP(p,tc_false) ? (char *)NULL :\
         (seem_err(m,p),(char *)NULL))))
#define BOOLEAN_ARG(p,m) (TYPEP(p,tc_false) ? 0 : 1)

#define RETURN_NIL(r) r; return NIL
#if WIN64
#define RETURN_FIXNUM(f) return fixcons((LONG64)f)
#else
#define RETURN_FIXNUM(f) return fixcons((long)f)
#endif
#define RETURN_FLONUM(f) return flocons((double)f)
#define RETURN_STRING(s) return stringcons((char *)s)
#define RETURN_BOOLEAN(b) return ((b) ? S_truth : S_false)
