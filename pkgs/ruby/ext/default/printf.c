#include <kernaux.h>
#include <ruby.h>

#include "dynarg.h"

#ifdef HAVE_KERNAUX_SNPRINTF

static VALUE rb_KernAux_snprintf1(int argc, const VALUE *argv, VALUE self);

static ID rb_intern_freeze = Qnil;
static VALUE rb_KernAux = Qnil;

void init_printf()
{
    rb_gc_register_mark_object(ID2SYM(rb_intern_freeze = rb_intern("freeze")));
    rb_gc_register_mark_object(rb_KernAux = rb_define_module("KernAux"));

    rb_define_singleton_method(rb_KernAux, "snprintf1",
                               rb_KernAux_snprintf1, -1);
}

// TODO: is this implementation correct?
// FIXME: rewrite to ensure no memory leak on exception.
VALUE rb_KernAux_snprintf1(
    const int argc,
    const VALUE *const argv_rb,
    const VALUE self __attribute__((unused))
) {
    if (argc < 2 || argc > 5) rb_raise(rb_eArgError, "expected 2, 3, 4 or 5 args");

    const VALUE size_rb = argv_rb[0];
    VALUE format_rb = argv_rb[1];

    const int size = NUM2INT(size_rb);
    const char *const format = StringValueCStr(format_rb);

    if (size < 0) rb_raise(rb_eRangeError, "expected non-negative size");

    const char *fmt = format;

    while (*fmt && *fmt != '%') ++fmt;
    if (*(fmt++) != '%') rb_raise(rb_eArgError, "invalid format");

    struct KernAux_PrintfFmt_Spec spec = KernAux_PrintfFmt_Spec_create();
    KernAux_PrintfFmt_Spec_parse_flags(&spec, &fmt);
    KernAux_PrintfFmt_Spec_parse_width(&spec, &fmt);
    KernAux_PrintfFmt_Spec_parse_precision(&spec, &fmt);
    KernAux_PrintfFmt_Spec_parse_length(&spec, &fmt);
    KernAux_PrintfFmt_Spec_parse_type(&spec, &fmt);

    while (*fmt) {
        if (*(fmt++) == '%') rb_raise(rb_eArgError, "invalid format");
    }

    int arg_index = 2;
    if (spec.set_width && argc > arg_index) {
        KernAux_PrintfFmt_Spec_set_width(&spec, NUM2INT(argv_rb[arg_index++]));
    }
    if (spec.set_precision && argc > arg_index) {
        KernAux_PrintfFmt_Spec_set_precision(&spec, NUM2INT(argv_rb[arg_index++]));
    }

    struct DynArg dynarg = DynArg_create();
    if (argc > arg_index) {
        VALUE arg_rb = argv_rb[arg_index];

        if (spec.type == KERNAUX_PRINTF_FMT_TYPE_INT) {
            RB_INTEGER_TYPE_P(arg_rb);
            DynArg_use_long_long(&dynarg, NUM2LL(arg_rb));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_UINT) {
            RB_INTEGER_TYPE_P(arg_rb);
            DynArg_use_unsigned_long_long(&dynarg, NUM2ULL(arg_rb));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_FLOAT ||
                   spec.type == KERNAUX_PRINTF_FMT_TYPE_EXP)
        {
            RB_FLOAT_TYPE_P(arg_rb);
            DynArg_use_double(&dynarg, NUM2DBL(arg_rb));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_CHAR) {
            Check_Type(arg_rb, T_STRING);
            DynArg_use_char(&dynarg, *StringValuePtr(arg_rb));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_STR) {
            Check_Type(arg_rb, T_STRING);
            DynArg_use_str(&dynarg, StringValueCStr(arg_rb));
        }
    }

    char *const str = malloc(size);
    if (!str) rb_raise(rb_eNoMemError, "snprintf1 buffer malloc");

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

    const VALUE output_rb =
        rb_funcall(rb_str_new2(str), rb_intern_freeze, 0);
    free(str);

    const VALUE result_rb = rb_ary_new2(2);
    rb_ary_push(result_rb, output_rb);
    rb_ary_push(result_rb, INT2NUM(slen));
    return rb_funcall(result_rb, rb_intern_freeze, 0);
}

#endif // HAVE_KERNAUX_SNPRINTF
