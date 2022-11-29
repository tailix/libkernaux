#include "main.h"

#include "dynarg.h"

#include <stddef.h>
#include <stdlib.h>

#ifdef KERNAUX_VERSION_WITH_PRINTF

/*************
 * ::KernAux *
 *************/

static VALUE rb_KernAux_snprintf1(int argc, const VALUE *argv, VALUE self);

static VALUE rb_KernAux_snprintf1_PROTECT(VALUE userdata);

/************************
 * ::KernAux::Snprintf1 *
 ************************/

static VALUE rb_KernAux_Snprintf1 = Qnil;

static size_t rb_KernAux_Snprintf1_DSIZE(const void *ptr);

const rb_data_type_t rb_KernAux_Snprintf1_DTYPE = {
    .wrap_struct_name = "KernAux::Snprintf1",
    .parent = NULL,
    .data = NULL,
    .flags = RUBY_TYPED_FREE_IMMEDIATELY,
    .function = {
        .dfree = RUBY_DEFAULT_FREE,
        .dsize = rb_KernAux_Snprintf1_DSIZE,
        .dmark = NULL,
        .dcompact = NULL,
        .reserved = { 0 },
    },
};

struct rb_KernAux_Snprintf1_DATA {
    const struct KernAux_PrintfFmt_Spec *spec;
    const struct DynArg *dynarg;
    int size;
    const char *format;
    char *str;
};

/********
 * Main *
 ********/

void init_printf()
{
    rb_gc_register_mark_object(
        rb_KernAux_Snprintf1 =
            // @api private
            rb_define_class_under(rb_KernAux, "Snprintf1", rb_cObject));
    rb_funcall(rb_KernAux, rb_intern("private_constant"), 1, ID2SYM(rb_intern("Snprintf1")));

    rb_define_singleton_method(rb_KernAux, "snprintf1",
                               rb_KernAux_snprintf1, -1);
}

/*************
 * ::KernAux *
 *************/

VALUE rb_KernAux_snprintf1(
    const int argc,
    const VALUE *const argv_rb,
    const VALUE self KERNAUX_UNUSED
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

    fmt = KernAux_PrintfFmt_Spec_parse(&spec, fmt);

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
            DynArg_use_long_long(&dynarg, NUM2LL(arg_rb));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_UINT) {
            DynArg_use_unsigned_long_long(&dynarg, NUM2ULL(arg_rb));
        } else if (spec.type == KERNAUX_PRINTF_FMT_TYPE_FLOAT ||
                   spec.type == KERNAUX_PRINTF_FMT_TYPE_EXP)
        {
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

    struct rb_KernAux_Snprintf1_DATA *userdata;
    VALUE userdata_rb = TypedData_Make_Struct(
        rb_KernAux_Snprintf1,
        struct rb_KernAux_Snprintf1_DATA,
        &rb_KernAux_Snprintf1_DTYPE,
        userdata
    );
    if (NIL_P(userdata_rb) || userdata == NULL) {
        free(str);
        rb_raise(rb_eNoMemError, "snprintf1 userdata alloc");
    }

    userdata->spec = &spec;
    userdata->dynarg = &dynarg;
    userdata->size = size;
    userdata->format = format;
    userdata->str = str;

    int state = 0;
    VALUE result =
        rb_protect(rb_KernAux_snprintf1_PROTECT, userdata_rb, &state);

    free(str);

    if (state == 0) {
        return result;
    } else {
        rb_jump_tag(state);
    }
}

VALUE rb_KernAux_snprintf1_PROTECT(VALUE userdata_rb)
{
    const struct rb_KernAux_Snprintf1_DATA *userdata = NULL;
    TypedData_Get_Struct(
        userdata_rb,
        struct rb_KernAux_Snprintf1_DATA,
        &rb_KernAux_Snprintf1_DTYPE,
        userdata
    );

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

    const VALUE output_rb =
        rb_funcall(rb_str_new2(userdata->str), rb_intern_freeze, 0);

    const VALUE result_rb = rb_ary_new2(2);
    rb_ary_push(result_rb, output_rb);
    rb_ary_push(result_rb, INT2NUM(slen));
    return rb_funcall(result_rb, rb_intern_freeze, 0);
}

/************************
 * ::KernAux::Snprintf1 *
 ************************/

size_t rb_KernAux_Snprintf1_DSIZE(const void *const ptr)
{
    return sizeof(struct rb_KernAux_Snprintf1_DATA);
}

#endif // KERNAUX_VERSION_WITH_PRINTF
