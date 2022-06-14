#include "main.h"

#include "dynarg.h"

#include <stddef.h>
#include <stdlib.h>

#include <mruby/array.h>
#include <mruby/error.h>
#include <mruby/presym.h>
#include <mruby/string.h>

#ifdef KERNAUX_VERSION_WITH_PRINTF

struct snprintf1_userdata {
    const struct KernAux_PrintfFmt_Spec *spec;
    const struct DynArg *dynarg;
    mrb_int size;
    const char *format;
    char *str;
};

static mrb_value rb_KernAux_snprintf1(mrb_state *mrb, mrb_value self);

static mrb_value snprintf1_protect(mrb_state *mrb, void *userdata);

void init_printf(mrb_state *const mrb)
{
    struct RClass *const rb_KernAux = mrb_module_get_id(mrb, MRB_SYM(KernAux));

    mrb_define_class_method(mrb, rb_KernAux, "snprintf1", rb_KernAux_snprintf1,
                            MRB_ARGS_REQ(2) | MRB_ARGS_OPT(2));
}

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
            DynArg_use_double(&dynarg, mrb_as_float(mrb, arg_rb));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_CHAR) {
            DynArg_use_char(&dynarg, *RSTRING_CSTR(mrb, arg_rb));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_STR) {
            DynArg_use_str(&dynarg, RSTRING_CSTR(mrb, arg_rb));
        }
    }

    char *const str = malloc(size);
    if (!str) mrb_raise(mrb, mrb_exc_get_id(mrb, MRB_ERROR_SYM(NoMemoryError)), "snprintf1 buffer malloc");

    struct snprintf1_userdata userdata = {
        .spec = &spec,
        .dynarg = &dynarg,
        .size = size,
        .format = format,
        .str = str,
    };
    mrb_bool error;
    mrb_value result = mrb_protect_error(mrb, snprintf1_protect, &userdata, &error);

    free(str);

    if (error) {
        mrb_exc_raise(mrb, result);
    } else {
        return result;
    }
}

mrb_value snprintf1_protect(mrb_state *const mrb, void *const userdata_raw)
{
    const struct snprintf1_userdata *const userdata = userdata_raw;

    int slen;
    if (userdata->spec->set_width) {
        if (userdata->spec->set_precision) {
            slen = userdata->dynarg->use_dbl
                ? kernaux_snprintf(userdata->str, userdata->size, userdata->format, userdata->spec->width, userdata->spec->precision, userdata->dynarg->dbl)
                : kernaux_snprintf(userdata->str, userdata->size, userdata->format, userdata->spec->width, userdata->spec->precision, userdata->dynarg->arg);
        } else {
            slen = userdata->dynarg->use_dbl
                ? kernaux_snprintf(userdata->str, userdata->size, userdata->format, userdata->spec->width, userdata->dynarg->dbl)
                : kernaux_snprintf(userdata->str, userdata->size, userdata->format, userdata->spec->width, userdata->dynarg->arg);
        }
    } else {
        if (userdata->spec->set_precision) {
            slen = userdata->dynarg->use_dbl
                ? kernaux_snprintf(userdata->str, userdata->size, userdata->format, userdata->spec->precision, userdata->dynarg->dbl)
                : kernaux_snprintf(userdata->str, userdata->size, userdata->format, userdata->spec->precision, userdata->dynarg->arg);
        } else {
            slen = userdata->dynarg->use_dbl
                ? kernaux_snprintf(userdata->str, userdata->size, userdata->format, userdata->dynarg->dbl)
                : kernaux_snprintf(userdata->str, userdata->size, userdata->format, userdata->dynarg->arg);
        }
    }

    mrb_value output_rb =
        mrb_obj_freeze(mrb, mrb_str_cat_cstr(mrb, mrb_str_new_lit(mrb, ""), userdata->str));

    mrb_value values[2];
    values[0] = output_rb;
    values[1] = mrb_fixnum_value(slen);
    return mrb_obj_freeze(mrb, mrb_ary_new_from_values(mrb, 2, values));
}

#endif // KERNAUX_VERSION_WITH_PRINTF
