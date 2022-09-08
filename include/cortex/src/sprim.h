/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _CX_SPRIM_H
#define _CX_SPRIM_H 1

#include "dll.h"

#ifndef UDF_COMPILER
# define UDF_COMPILER 0
#endif

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif
typedef Pointer (*PrimSubr)();

FLUENT_EXPORT Pointer
            linputportp (Pointer x),
            loutputportp  (Pointer x),

            lopenfile (Pointer, Pointer),
            sopeninputfile  (const char *s, const char *m),
            sopenoutputfile (const char *s, const char *m),

            Make_File_Port  (void),
            Make_Echoing_Port (void),
            Make_InstantaaS_Port (void),/*called to instantiate the insatnt port, but instant port is not used*/
            lopeninputstring  (Pointer x),
            lopenoutputstring (void),
            Make_String_Port  (void),
            lcloseinputport (Pointer x),
            lcloseoutputport  (Pointer x),
            lflushoutputport  (Pointer x),
            lportname (Pointer x),
            lportechoing  (Pointer x),
            lechoports  (Pointer x),
            lsetechoports (Pointer x, Pointer y),
            lfileexists (Pointer x),
            lfiledirectory  (Pointer x),
            lpathequal  (Pointer x, Pointer y),
            lfilemodtime  (Pointer x),
            lfileowner  (Pointer x),
            lshowpermissions (Pointer, Pointer),
            lexpandfilename (Pointer x),
            lremovefile (Pointer),
            lrenamefile (Pointer, Pointer),
            lsetfilepos (Pointer, Pointer),
            lgettempfilename  (Pointer),
            nextfree  (void),
            alloc_cells (fixnum n),

            vectorp (Pointer x),
            ivector_cons  (fixnum n, Pointer x),
            lmakevector (Pointer x, Pointer y),
            lvectorlength (Pointer x),
            lvectorsize (Pointer x),
            lvectorref  (Pointer x, Pointer y),
            lvectorset  (Pointer x, Pointer y, Pointer z),
            list_to_vector  (Pointer x),
            subvector_to_list (Pointer x, Pointer y, Pointer z),
            subvector_fill  (Pointer x, Pointer y, Pointer z, Pointer a),

            continp (Pointer),
            vcontinp  (Pointer),
            contin_cons (void),

            stringp (Pointer x),
            istringcons (fixnum n, int c),
            stringcons  (const char *s),
            lmakestring (Pointer x, Pointer y),
            string_length (Pointer x),
            sstring_ref (Pointer x, Pointer n),
            string_set  (Pointer x, Pointer n, Pointer o),
            list_to_string  (Pointer x),
            substring_to_list (Pointer x, Pointer s, Pointer e),
            substring (Pointer x, Pointer s, Pointer e),
            substring_fill  (Pointer x, Pointer s, Pointer e, Pointer y),
            string_append (Pointer x, Pointer y),
            string_eq (Pointer x, Pointer y),
            string_lt (Pointer x, Pointer y),
            string_gt (Pointer x, Pointer y),
            string_ci_eq  (Pointer x, Pointer y),
            string_ci_lt  (Pointer x, Pointer y),
            string_ci_gt  (Pointer x, Pointer y),
            string_has_char(Pointer x, Pointer y),
            string_split(Pointer args),

            cons    (Pointer x, Pointer y),
            car   (Pointer x),
            cdr   (Pointer x),
            general_car_cdr (Pointer x, Pointer n),
            setcar  (Pointer x, Pointer y),
            setcdr  (Pointer x, Pointer y),
            consp   (Pointer x),
            length  (Pointer x),
            memq    (Pointer x, Pointer alist),
            memv    (Pointer x, Pointer alist),
            assq    (Pointer x, Pointer alist),
            assv    (Pointer x, Pointer alist),
            assvcdr   (Pointer x, Pointer alist),
            sorta     (Pointer alist),
            sortd     (Pointer alist),
            assoc         (Pointer x, Pointer alist),

            intern  (const char *name),
            symbol_boundp (Pointer symbol, Pointer env),
            symbol_assignedp  (Pointer symbol, Pointer env),
            sym2str (Pointer x),
            str2sym (Pointer x),
            symbolp (Pointer x),
            procedurep  (Pointer x),

            nilp    (Pointer x),
            notp    (Pointer x),
            eq    (Pointer x, Pointer y),
            eqv   (Pointer x, Pointer y),
            equal   (Pointer x, Pointer y),
            realp   (Pointer x),
            integerp  (Pointer x),

            fixcons (fixnum i),

            flocons (double x),

            fix_quotient  (Pointer x, Pointer y),
            fix_remainder (Pointer x, Pointer y),

            generic_eq  (Pointer x, Pointer y),
            generic_lt  (Pointer x, Pointer y),
            generic_gt  (Pointer x, Pointer y),
            generic_add (Pointer x, Pointer y),
            generic_subtract  (Pointer x, Pointer y),
            generic_multiply  (Pointer x, Pointer y),
            generic_divide  (Pointer x, Pointer y),

            generic_float (Pointer x),
            generic_int (Pointer x),
            generic_truncate  (Pointer x),

            generic_floor (Pointer x),
            generic_ceiling (Pointer x),
            generic_exp (Pointer x),
            generic_log (Pointer x),
            generic_log10 (Pointer x),
            generic_sin (Pointer x),
            generic_cos (Pointer x),
            generic_tan (Pointer x),
            generic_asin  (Pointer x),
            generic_acos  (Pointer x),
            generic_atan  (Pointer x),
            generic_atan2 (Pointer x, Pointer y),
            generic_sqrt  (Pointer x),
            generic_expt  (Pointer x, Pointer y),

            char_cons (int c),
            charp   (Pointer x),
            char_to_integer (Pointer x),
            integer_to_char (Pointer x),
            char_eq (Pointer x, Pointer y),
            char_lt (Pointer x, Pointer y),
            char_gt (Pointer x, Pointer y),
            char_alphabetic (Pointer x),
            char_numeric    (Pointer x),
            char_whitespace (Pointer x),
            char_upper_case (Pointer x),
            char_lower_case (Pointer x),
            char_upcase (Pointer x),
            char_downcase (Pointer x),

            bit_setp  (Pointer ln, Pointer lx),
            set_bit (Pointer ln, Pointer lx),
            clear_bit (Pointer ln, Pointer lx),
            toggle_bit  (Pointer ln, Pointer lx),
            slogical_and  (Pointer a, Pointer b),
            slogical_or (Pointer a, Pointer b),
            slogical_xor  (Pointer a, Pointer b),
            slogical_not  (Pointer a),
            logical_left_shift  (Pointer lx, Pointer ln),
            logical_right_shift (Pointer lx, Pointer ln),

            lcharready  (Pointer port),
            lpeekchar (Pointer port),
            lreadchar (Pointer port),
            lread   (Pointer port),
            lreadf  (Port *p),
            lwritechar  (Pointer c, Pointer port),
            lwritestring  (Pointer c, Pointer port),
            lset_aas_output_port (Pointer p), /*turn on  proxy for remote customer*/
            lnil_aas_output_port (void),      /*turn off proxy for remote customer*/
            lis_aas_call(void),/*returns #t for aas calls, otherwise #f*/
            laas_raise_question(void),/*throws question exception. This is not an error!*/
            laas_raise_question_menu_get(Pointer x, Pointer y, Pointer z, Pointer t), /*throws question exception. This is not an error!*/
            laas_raise_question_yes_no(Pointer x, Pointer y, Pointer z, Pointer t), /*throws question exception. This is not an error!*/
            laas_raise_question_readq_generic(Pointer x, Pointer y, Pointer z, Pointer t), /*throws question exception. This is not an error!*/
            laas_raise_question_readunquoted_string(Pointer x, Pointer y, Pointer z, Pointer t), /*throws question exception. This is not an error!*/
            laas_raise_invalid_command(Pointer x),/*throws  exception. This is an user error!*/
            lwrite  (Pointer x, Pointer port),
            leofp   (Pointer port),
            errp          (Pointer x),
            lnumbertostring (Pointer x, Pointer y),
            lstringtonumber (Pointer x, Pointer y),
            lchecknumber  (Pointer s),

            eval    (Pointer x, Pointer env),
            eval_define (Pointer args, Pointer env),
            eval_lambda (Pointer args, Pointer env),
            eval_apply  (Pointer args, Pointer env),
            eval_time (void),
            ltime   (void),
            llocaltime  (Pointer gmt_time),
            lformattime (Pointer /*time*/, Pointer /*format*/),
            envlookup (Pointer var, Pointer env),
            call_cc (Pointer args, Pointer env),
            set_cc  (Pointer cc, Pointer val),
            eval_errprotect (Pointer args, Pointer env),
            eval_errprotect_mt  (Pointer args, Pointer env),
            quit    (int),
            closure (Pointer env, Pointer code),
            linterrupted  (void),

            portcons      (void),
            subrcons  (int type, const char *name, Pointer (*f)()),
            oblistfn  (void),
            copy_list (Pointer x),
            append  (Pointer x),
            appendd (Pointer x, Pointer y),
            reverse (Pointer x),

            gc    (void),
            gc_status (void),
            gc_dump (Pointer fname),
            fasl_read (Pointer port, Pointer primitives, Pointer symbols),

            lerr    (Pointer message, Pointer x),
            laas_broadcast(Pointer message),
            lsystem (Pointer string),
            lchdir  (Pointer string),
            machine_id    (void),
            lgetenv (Pointer string),
            lputenv (Pointer string);

#if  ! UDF_COMPILER
#define fprintf_stderr(...)  fprintf_std(stderr, __VA_ARGS__)
#define fprintf_stdout(...)  fprintf_std(stdout, __VA_ARGS__)
#endif   /*  ! UDF_COMPILER */
FLUENT_EXPORT void
               fprintf_std(FILE *file, const char *, ...),
               seem_err  (const char *msg, Pointer obj),
               aas_delayed_err (char *msg),
               aas_broadcast (const char *msg),
               aas_broadcast_rpsetvar(const char *rpvar_name),
               aas_raise_question(void),
               aas_raise_question_yes_no(Pointer x, Pointer y, Pointer z, Pointer t),
               aas_raise_question_menu_get(Pointer x, Pointer y, Pointer z, Pointer t),
               aas_raise_question_readq_generic(Pointer x, Pointer y, Pointer z, Pointer t),
               aas_raise_question_readunquoted_string(Pointer x, Pointer y, Pointer z, Pointer t),
               aas_raise_invalid_command(Pointer x),
               init_seem (int (*)(const char *)),
               tg_init_seem(void),
               init_subr (const char * /*name*/, int /*type*/, Pointer (*)() ),
               init_heap     (void),
               init_ports    (void),
               reset_jump_env (volatile void *oldjmpp, int ret_val),
               free_cells    (Pointer p),
               gc_udump      (char *fname),
               process_cla (int *argc, char **argv),
               sload   (const char *filename, Pointer env),
               symdef  (Pointer var, Pointer val),
               writef  (Pointer x, Port *port),
               writef_ToErrorException(Pointer x, char **p_pszAasErrorExceptionsBuffer, size_t *p_pLenAasErrorExceptionsBuffer),
               AddStringToErrorException(const char *p_szNewException, char **p_pszAasErrorExceptionsBuffer, size_t *p_pLenAasErrorExceptionsBuffer),
               AddCharToErrorException(char p_charNewCharacter, char **p_pszAasErrorExceptionsBuffer, size_t *p_pLenAasErrorExceptionsBuffer),
               Port_Echo_Char (Port *, int),
               Port_Echo_String (Port *, const char *),
               free_port_buffers(Port *),
               fix_exp_fmt (char *),
               buildusertree (void),
               buildtgridtree(void);

FLUENT_EXPORT int resolve_aas_initialization(void);
FLUENT_EXPORT int
portprintf(Port *, const char *, ...);

FLUENT_EXPORT void *
set_new_jump_env (volatile void *newjmpp);

FLUENT_EXPORT double
flonum_arg  (Pointer x, const char *msg);

#if WIN64
FLUENT_EXPORT LONG64
#else
FLUENT_EXPORT long
#endif
fixnum_arg  (Pointer x, const char *msg),
            ilength (Pointer x);

FLUENT_EXPORT unsigned char
char_arg      (Pointer x, const char *msg);

#define boolean_arg(x,msg)((x) != S_false)
#define booleancons(x)((x)?S_truth:S_false)

#if vms
# define Char_Downcase CharDowncase
#endif

FLUENT_EXPORT char
Char_Downcase (int c),
              *Port_Name  (Port *p),
              *write_mode (void),
              *read_mode  (void);

FLUENT_EXPORT const char
*string_arg (Pointer x, const char *msg);

FLUENT_EXPORT unsigned long
logical_arg (Pointer, const char *);

FLUENT_EXPORT Pointer
foreignp  (Pointer),
          foreign_cons  (fixnum, const char *),
          lmakeforeign  (Pointer, Pointer),
          lforeignid  (Pointer),
          lforeigndata  (Pointer);

FLUENT_EXPORT Pointer
lstacksize  (void),
            lstackobject  (Pointer);

#if _NT
FLUENT_EXPORT void fix_exp_fmt  (char *);
#endif
/*Seem to C exit code   */
FLUENT_EXPORT void set_exit_code(int);
FLUENT_EXPORT int get_exit_code(void);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif  /* _CX_SPRIM_H */

