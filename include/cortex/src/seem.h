/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/**************************************************************************************/
/* IMPORTANT [2019/05/07]: If you touch this file for even the most harmless of things,
 * it might still break some FLCORE test, as this file is included in one of
 * the 'interpreted UDF' files which tries to use an imitation 'C inerpreter'
 * but of course can't support it completely. Try using !UDF_COMPILER macro test for
 * doing normal C/C++ things. */
/**************************************************************************************/

#ifndef _Seem_h_
#define _Seem_h_
#define Seem_h /* backward compatibility */

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#if !UDF_COMPILER
#include <stdio.h>
#endif

#include "dll.h"
#if WIN64
#include "basetsd.h"
#endif

#include "cxm.h"   /* realloc() */

#if WIN64
typedef LONG64 fixnum;
#else
typedef long fixnum;
#endif
typedef double flonum;
/* 2010-04-28 ubecker
 * The compiler flags _lnx86, _lnia64, and _lnamd64 are not defined when compiling UDF.
 * As a consequence, the Pointer datatype has a different size for UDF, if relying only on these flags.
 * Fix by adding also the fluent flavors of system flags: sys_lnx86, sys_lnia64, and sys_lnamd64.
 * Note: These are not known for cortex, so one does need both with the current build system.
 */
#if __convex__ || _lnx86 || sys_lnx86 || _SX || _lnia64 || sys_lnia64 || _lnamd64 || sys_lnamd64
/* With shorts, Convex doesn't double-word-align this structure.
 * Ends up being 3 words long instead of 4, which makes the dumps
 * incompatible.
 * Only advantage of shorts might be that fewer bits are manipulated.
 */
typedef int Sshortint;
#else
typedef short Sshortint;
#endif

#if _lnia64 || sys_lnia64
struct __attribute__ ((aligned)) obj
#elif WIN64
__declspec(align(16)) struct obj
#else
struct obj
#endif
{
  union
  {
    struct {fixnum ncell; struct obj *vcell;} symbol;
    struct {struct obj *car; struct obj *cdr;}  cons;
    struct {struct obj *env; struct obj *code;} closure;
    struct {fixnum ncell; struct obj *(*f)();}  subr;
    struct {unsigned char data;}    character;
    struct {fixnum data;}     fixednum;
    struct {flonum data;}     floatnum;
    struct {fixnum ncell; fixnum length;} string;
    struct {fixnum ncell; fixnum length;} vector;
    struct {fixnum ncell; short valid;}   continuation;
    struct {fixnum ncell; struct obj *next;}  free;
    struct {fixnum ncell;}      port;
    struct {fixnum id; char *data;}   foreign;
  } as;

  Sshortint gc_mark;
  Sshortint type;
};

#define CAR(x)    ((x)->as.cons.car)
#define CDR(x)    ((x)->as.cons.cdr)
#define PNAME(x)  ((char *)((x)+1))
#define VCELL(x)  ((x)->as.symbol.vcell)
#define SUBRF(x)  (*((x)->as.subr.f))
#define FLONM(x)  ((x)->as.floatnum.data)
#define FIXNM(x)  ((x)->as.fixednum.data)
#define CHAR(x)   ((x)->as.character.data)
#define VECTOR_LENGTH(x) ((x)->as.vector.length)
#define VECTOR(x) ((Pointer *)((x)+1))
#define PORT(x)   ((Port *)((x)+1))
#define SEEM_STRING_LENGTH(x)((x)->as.string.length)
#define STRING(x) ((char *)((x)+1))
#define CONTINUATION_LENGTH(x)((x)->as.continuation.length)
#define CONTINUATION_VALID(x)((x)->as.continuation.valid)
#define CONTINUATION(x)((char *)((x)+1))
#define NEXT_FREE(x)((x)->as.free.next)
#define CELL_LENGTH(x)((x)->as.vector.ncell)
#define FOREIGN_ID(x)((x)->as.foreign.id)
#define FOREIGN_DATA(x)((x)->as.foreign.data)


typedef struct obj **stack;
typedef struct obj Obj;
typedef struct obj *Pointer;

#define NIL ((struct obj *) NULL)
#define EQ(x,y)((x) == (y))
#define NEQ(x,y)((x) != (y))
#define NILP(x)EQ(x,NIL)
#define NNILP(x)NEQ(x,NIL)
#define RETURNP(x)return ((x) ? S_truth : S_false)

#define FALSEP(x)EQ(x,S_false)
#define NFALSEP(x)NEQ(x,S_false)

#define TYPE(x)(NILP(x) ? 0 : (x)->type)
#define TYPEP(x,y)(TYPE(x) == (y))
#define NTYPEP(x,y)(TYPE(x) != (y))
#define PAIRP(x)(TYPE(x) == tc_cons)
#define NPAIRP(x)(TYPE(x) != tc_cons)

#define SYMBOLP(x)(TYPE(x) == tc_symbol)
#define FLOATP(x)(TYPE(x) == tc_flonum)
#define INTEGERP(x)(TYPE(x) == tc_fixnum)
#define NUMBERP(x)(TYPE(x) == tc_flonum || TYPE(x) == tc_fixnum)
#define CHARP(x)(TYPE(x) == tc_char)
#define STRINGP(x)(TYPE(x) == tc_string)
#define VECTORP(x)(TYPE(x) == tc_vector)
#define BOOLEANP(x)(TYPE(x) == tc_true || TYPE(x) == tc_false)

#define tc_nil    0
#define tc_true   1
#define tc_false  31

#define tc_cons   2
#define tc_symbol 3
#define tc_flonum 4
#define tc_fixnum 5
#define tc_char   6
#define tc_string 7
#define tc_vector 8
#define tc_continuation 9
#define tc_nm_vector  10
#define tc_free   11
#define tc_port   12

#define tc_lambda 13
#define tc_closure  14
#define tc_quote  15
#define tc_define 16
#define tc_setq   17
#define tc_begin  18
#define tc_if   19
#define tc_and    20
#define tc_or   21
#define tc_tenv   22
#define tc_access 23
#define tc_apply  24

#define tc_subr_0 25
#define tc_subr_1 26
#define tc_subr_2 27
#define tc_subr_3 28
#define tc_subr_4 29
#define tc_fsubr  30
#define tc_lsubr  32

#define tc_foreign  33

extern FLUENT_EXPORT int Seem_Eval_Status(void);
extern FLUENT_EXPORT Pointer S_truth, S_false;
extern Pointer ErrorObject;
extern Pointer ErrorMessage;
extern char str_parse_failed[];
#define  MAX_STR_LEN 256
extern FLUENT_EXPORT stack *stack_end, *stack_now, *stack_start;
extern FLUENT_EXPORT int stack_size, default_stack_size;
extern int errjmp_ok;
extern int nointerrupt;
extern int gc_verbose;
extern int seem_fatalerror;
extern void (*seem_init_ports)();
extern void CPUtime (double *u, double *s);

#define Reallocate_Stack()                      \
{                                               \
  size_t origOffset = stack_now - stack_start;  \
  stack_size += default_stack_size;             \
  stack_start = (stack *)realloc(stack_start,   \
                   sizeof(stack)*stack_size);   \
  stack_now = stack_start + origOffset;         \
  stack_end = stack_start + stack_size;         \
}

#define Push_Stack(_x)               \
{                                    \
  if(stack_now==stack_end) {         \
    Reallocate_Stack();              \
  }                                  \
  *stack_now++ = &(_x);              \
  (_x)=NIL;                          \
}

#define Push_Stack0(_x)              \
{                                    \
  if(stack_now==stack_end) {         \
    Reallocate_Stack();              \
  }                                  \
  *stack_now++ = &(_x);              \
}

#define Save_Stack()               (stack_now - stack_start)
#define Restore_Stack(stackOffset) (stack_now = stack_start + stackOffset)

#define START_SSCHEME_STACK(_result) \
{ \
   size_t stackOffset = Save_Stack(); \
   Push_Stack(_result)

#define END_SSCHEME_STACK(_result) \
   Restore_Stack(stackOffset); \
}

struct port
{
  int (*put_c) (int, struct port *); /* put character */
  int (*put_s) (const char *, struct port *); /* put string */
  int (*get_c) (struct port *);   /* get character */
  int (*unget_c) (int, struct port *); /* unget character */
  int (*ready_c) (struct port *);   /* character ready? */
  void (*flush) (struct port *);  /* flush */
  Pointer (*close) (struct port *); /* close */
  union
  {
    FILE *file;         /* FILE pointer */
    void *ptr;                                  /* Any pointer */
    int fd;         /* File descriptor */
  } as;
  Pointer string;       /* string port */
  Pointer name;         /* filename */
  Pointer echo;         /* echo port */
  int _c_ready;
  int _c_unget;
  int _nc;
  char *cbuf;
  int ncbuf;
  int linebuffered;
};

typedef struct port Port;
typedef Pointer (*Subr)();

#define PORT_GETC(p)(*(p->get_c))(p)
#define PORT_UNGETC(c,p)(*(p->unget_c))(c,p)
#define PORT_PUTC(c,p)(*(p->put_c))(c,p)
#define PORT_PUTS(s,p)(*(p->put_s))(s,p)
#define PORT_FLUSH(p)(*(p->flush))(p)
#define PORT_CHAR_READY(p)((p)->_c_ready)

#define PORT_FILE(p)  ((p)->as.file)
#define PORT_STRING(p)  ((p)->string)
#define PORT_FD(p)  ((p)->as.fd)
#define PORT_PTR(p) ((p)->as.ptr)


#define EVAL_SUCCESS 0
#define EVAL_ERROR 1
#define EVAL_INTERRUPT 2

#include "sprim.h"

int psystem(const char *str);
extern char *time_string(char *);
extern void print_back_trace_to_file(FILE *fp, int nlevel, int id);
void pprint_thread(FILE *fp);

#if ADD_MISSING_PROTOS
# define NOPROTO(x) ()
/* missing prototypes */
extern int fclose NOPROTO((FILE *));
extern int fflush NOPROTO((FILE *));
extern int fgetc  NOPROTO((FILE *));
extern int fprintf  NOPROTO((FILE *, const char *, ...));
extern int fputc  NOPROTO((const char, FILE *));
extern int fputs  NOPROTO((char *, FILE *));
extern int printf NOPROTO((const char *, ...));
extern int putenv NOPROTO((char *));
extern int read   NOPROTO((int, char *, int));
extern int remove NOPROTO((const char *));
extern int rename NOPROTO((const char *, const char *));
extern int sscanf NOPROTO((const char *, const char *, ...));
extern int system NOPROTO((char *));
extern int ungetc NOPROTO((const char, FILE *));
extern int _filbuf  NOPROTO((FILE *));
#endif

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _Seem_h_ */

/* EOF */
