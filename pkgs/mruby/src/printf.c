#include "dynarg.h"
#include "main.h"

#include <kernaux.h>

#include <mruby.h>
#include <mruby/array.h>
#include <mruby/presym.h>
#include <mruby/string.h>

#include <stdlib.h>

static mrb_value rb_KernAux_snprintf1(mrb_state *mrb, mrb_value self);

void init_printf(mrb_state *const mrb)
{
    struct RClass *const rb_KernAux = mrb_module_get_id(mrb, MRB_SYM(KernAux));

    mrb_define_class_method(mrb, rb_KernAux, "snprintf1", rb_KernAux_snprintf1,
                            MRB_ARGS_REQ(2) | MRB_ARGS_OPT(2));
}

// FIXME: rewrite to ensure no memory leak on exception.
mrb_value rb_KernAux_snprintf1(mrb_state *const mrb, mrb_value self)
{
    mrb_int size = 0;
    const char *format = NULL;
    mrb_value rest[3];
    mrb_bool rest_given[3];

    mrb_get_args(
        mrb,
        "iz|o?o?o?",
        &size,
        &format,
        &rest[0], &rest_given[0],
        &rest[1], &rest_given[1],
        &rest[2], &rest_given[2]
    );

    if (size < 0) mrb_raise(mrb, E_RANGE_ERROR, "expected non-negative size");

    const char *fmt = format;

    while (*fmt && *fmt != '%') ++fmt;
    if (*(fmt++) != '%') mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid format");

    struct KernAux_PrintfFmt_Spec spec = KernAux_PrintfFmt_Spec_create();

    fmt = KernAux_PrintfFmt_Spec_parse(&spec, fmt);

    while (*fmt) {
        if (*(fmt++) == '%') mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid format");
    }

    int argc = 0;
    for (int i = 0; i < 3; ++i) if (rest_given[i]) ++argc;

    int arg_index = 0;
    if (spec.set_width && argc > arg_index) {
        KernAux_PrintfFmt_Spec_set_width(&spec, mrb_integer(rest[arg_index++]));
    }
    if (spec.set_precision && argc > arg_index) {
        KernAux_PrintfFmt_Spec_set_precision(&spec, mrb_integer(rest[arg_index++]));
    }

    struct DynArg dynarg = DynArg_create();
    if (argc > arg_index) {
        mrb_value arg_rb = rest[arg_index];

        if (spec.type == KERNAUX_PRINTF_FMT_TYPE_INT) {
            DynArg_use_long_long(&dynarg, mrb_integer(arg_rb));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_UINT) {
            mrb_int arg = mrb_integer(arg_rb);
            if (arg < 0) mrb_raise(mrb, E_ARGUMENT_ERROR, "expected non-negative argument");
            DynArg_use_unsigned_long_long(&dynarg, arg);
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_FLOAT ||
                   spec.type == KERNAUX_PRINTF_FMT_TYPE_EXP)
        {
            DynArg_use_double(&dynarg, mrb_float(mrb_ensure_float_type(mrb, arg_rb)));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_CHAR) {
            DynArg_use_char(&dynarg, *RSTRING_CSTR(mrb, arg_rb));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_STR) {
            DynArg_use_str(&dynarg, RSTRING_CSTR(mrb, arg_rb));
        }
    }

    char *const str = malloc(size);
    if (!str) mrb_raise(mrb, mrb_exc_get_id(mrb, MRB_ERROR_SYM(NoMemoryError)), "snprintf1 buffer malloc");

    int slen;
    if (spec.set_width) {
        if (spec.set_precision) {
            slen = dynarg.use_dbl
                ? kernaux_snprintf(str, size, format, spec.width, spec.precision, dynarg.dbl)
                : kernaux_snprintf(str, size, format, spec.width, spec.precision, dynarg.arg);
        } else {
            slen = dynarg.use_dbl
                ? kernaux_snprintf(str, size, format, spec.width, dynarg.dbl)
                : kernaux_snprintf(str, size, format, spec.width, dynarg.arg);
        }
    } else {
        if (spec.set_precision) {
            slen = dynarg.use_dbl
                ? kernaux_snprintf(str, size, format, spec.precision, dynarg.dbl)
                : kernaux_snprintf(str, size, format, spec.precision, dynarg.arg);
        } else {
            slen = dynarg.use_dbl
                ? kernaux_snprintf(str, size, format, dynarg.dbl)
                : kernaux_snprintf(str, size, format, dynarg.arg);
        }
    }

    mrb_value output_rb =
        mrb_obj_freeze(mrb, mrb_str_cat_cstr(mrb, mrb_str_new_lit(mrb, ""), str));
    free(str);

    mrb_value values[2];
    values[0] = output_rb;
    values[1] = mrb_fixnum_value(slen);
    return mrb_obj_freeze(mrb, mrb_ary_new_from_values(mrb, 2, values));
}
