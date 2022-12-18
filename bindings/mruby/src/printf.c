#include "main.h"
#include "dynarg.h"

#include <mruby/array.h>
#include <mruby/error.h>
#include <mruby/presym.h>
#include <mruby/string.h>

#define BUFFER_SIZE 4096

#ifdef KERNAUX_VERSION_WITH_PRINTF

static mrb_value rb_KernAux_sprintf(mrb_state *mrb, mrb_value self);

void init_printf(mrb_state *const mrb)
{
    struct RClass *const rb_KernAux = mrb_module_get_id(mrb, MRB_SYM(KernAux));

    mrb_define_class_method(mrb, rb_KernAux, "sprintf", rb_KernAux_sprintf,
                            MRB_ARGS_REQ(1) | MRB_ARGS_REST());
}

#define TAKE_ARG \
    if (arg_index >= argc) { \
        mrb_raise(mrb, E_ARGUMENT_ERROR, "too few arguments"); \
    } \
    mrb_value arg_rb = args[arg_index++]; \
    do {} while (0)

mrb_value rb_KernAux_sprintf(mrb_state *const mrb, mrb_value self)
{
    const char *format;
    mrb_value *args;
    mrb_int argc;
    mrb_get_args(mrb, "z*", &format, &args, &argc);

    int arg_index = 0;
    mrb_value result = mrb_str_new_lit(mrb, "");

    while (*format) {
        if (*format != '%') {
            mrb_str_cat(mrb, result, format, 1);
            ++format;
            continue;
        }

        ++format;
        struct KernAux_PrintfFmt_Spec spec =
            KernAux_PrintfFmt_Spec_create_out(&format);

        if (spec.set_width) {
            TAKE_ARG;
            KernAux_PrintfFmt_Spec_set_width(&spec, mrb_integer(arg_rb));
        }
        if (spec.set_precision) {
            TAKE_ARG;
            KernAux_PrintfFmt_Spec_set_precision(&spec, mrb_integer(arg_rb));
        }

        struct DynArg dynarg = DynArg_create();

        if (spec.type == KERNAUX_PRINTF_FMT_TYPE_INT) {
            TAKE_ARG;
            mrb_ensure_int_type(mrb, arg_rb);
            DynArg_use_long_long(&dynarg, mrb_integer(arg_rb));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_UINT) {
            TAKE_ARG;
            mrb_ensure_int_type(mrb, arg_rb);
            DynArg_use_unsigned_long_long(&dynarg, mrb_integer(arg_rb));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_FLOAT ||
                   spec.type == KERNAUX_PRINTF_FMT_TYPE_EXP)
        {
            TAKE_ARG;
            mrb_ensure_float_type(mrb, arg_rb);
            DynArg_use_double(&dynarg, mrb_float(arg_rb));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_CHAR) {
            TAKE_ARG;
            mrb_ensure_string_type(mrb, arg_rb);
            DynArg_use_char(&dynarg, *RSTRING_PTR(arg_rb));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_STR) {
            TAKE_ARG;
            mrb_ensure_string_type(mrb, arg_rb);
            DynArg_use_str(&dynarg, RSTRING_CSTR(mrb, arg_rb));
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

        mrb_str_cat(mrb, result, buffer, slen);
    }

    if (arg_index < argc) {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "too many arguments");
    }

    return mrb_obj_freeze(mrb, result);
}

#endif // KERNAUX_VERSION_WITH_PRINTF
