#include "main.h"
#include "dynarg.h"

#define BUFFER_SIZE 4096

#ifdef KERNAUX_VERSION_WITH_PRINTF

/**
 * Typical `printf`.
 *
 * @param format [String] format string
 * @return [String] formatted output
 *
 * @example
 *   KernAux.sprintf 'foo%*scar%d', 5, 'bar', 123
 *   #=> "foo  barcar123"
 */
static VALUE rb_KernAux_sprintf(int argc, VALUE *argv, VALUE self);

void init_printf()
{
    rb_define_singleton_method(rb_KernAux, "sprintf", rb_KernAux_sprintf, -1);
}

#define TAKE_ARG \
    if (arg_index >= argc) rb_raise(rb_eArgError, "too few arguments"); \
    VALUE arg_rb = argv[arg_index++]; \
    do {} while (0)

VALUE rb_KernAux_sprintf(const int argc, VALUE *const argv, VALUE self)
{
    if (argc == 0) rb_raise(rb_eArgError, "too few arguments");

    const char *format = StringValueCStr(argv[0]);
    int arg_index = 1;
    VALUE result = rb_str_new_literal("");

    while (*format) {
        if (*format != '%') {
            rb_str_cat(result, format, 1);
            ++format;
            continue;
        }

        ++format;
        struct KernAux_PrintfFmt_Spec spec =
            KernAux_PrintfFmt_Spec_create_out(&format);

        if (spec.set_width) {
            TAKE_ARG;
            KernAux_PrintfFmt_Spec_set_width(&spec, NUM2INT(arg_rb));
        }
        if (spec.set_precision) {
            TAKE_ARG;
            KernAux_PrintfFmt_Spec_set_precision(&spec, NUM2INT(arg_rb));
        }

        struct DynArg dynarg = DynArg_create();

        if (spec.type == KERNAUX_PRINTF_FMT_TYPE_INT) {
            TAKE_ARG;
            DynArg_use_long_long(&dynarg, NUM2LL(arg_rb));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_UINT) {
            TAKE_ARG;
            DynArg_use_unsigned_long_long(&dynarg, NUM2ULL(arg_rb));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_FLOAT ||
                   spec.type == KERNAUX_PRINTF_FMT_TYPE_EXP)
        {
            TAKE_ARG;
            DynArg_use_double(&dynarg, NUM2DBL(arg_rb));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_CHAR) {
            TAKE_ARG;
            Check_Type(arg_rb, T_STRING);
            DynArg_use_char(&dynarg, *StringValuePtr(arg_rb));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_STR) {
            TAKE_ARG;
            Check_Type(arg_rb, T_STRING);
            DynArg_use_str(&dynarg, StringValueCStr(arg_rb));
        }

        // 1 additional byte for the '%' character.
        // 1 additional byte for the terminating '\0' character.
        char old_format[2 + spec.format_limit - spec.format_start];
        memset(old_format, '\0', sizeof(old_format));
        old_format[0] = '%';
        strncpy(&old_format[1], spec.format_start, sizeof(old_format) - 2);

        char buffer[BUFFER_SIZE];
        int slen;

        if (spec.set_width) {
            if (spec.set_precision) {
                if (dynarg.use_dbl) {
                    slen = kernaux_snprintf(buffer, BUFFER_SIZE, old_format,
                                            spec.width, spec.precision,
                                            dynarg.dbl);
                } else {
                    slen = kernaux_snprintf(buffer, BUFFER_SIZE, old_format,
                                            spec.width, spec.precision,
                                            dynarg.arg);
                }
            } else {
                if (dynarg.use_dbl) {
                    slen = kernaux_snprintf(buffer, BUFFER_SIZE, old_format,
                                            spec.width, dynarg.dbl);
                } else {
                    slen = kernaux_snprintf(buffer, BUFFER_SIZE, old_format,
                                            spec.width, dynarg.arg);
                }
            }
        } else {
            if (spec.set_precision) {
                if (dynarg.use_dbl) {
                    slen = kernaux_snprintf(buffer, BUFFER_SIZE, old_format,
                                            spec.precision, dynarg.dbl);
                } else {
                    slen = kernaux_snprintf(buffer, BUFFER_SIZE, old_format,
                                            spec.precision, dynarg.arg);
                }
            } else {
                if (dynarg.use_dbl) {
                    slen = kernaux_snprintf(buffer, BUFFER_SIZE, old_format, dynarg.dbl);
                } else {
                    slen = kernaux_snprintf(buffer, BUFFER_SIZE, old_format, dynarg.arg);
                }
            }
        }

        rb_str_cat(result, buffer, slen);
    }

    if (arg_index < argc) rb_raise(rb_eArgError, "too many arguments");

    return rb_funcall(result, rb_intern_freeze, 0);
}

#endif // KERNAUX_VERSION_WITH_PRINTF
