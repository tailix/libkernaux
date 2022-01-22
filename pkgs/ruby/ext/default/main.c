#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <kernaux.h>
#include <ruby.h>

#define CMDLINE_ARGV_COUNT_MAX 256
#define CMDLINE_BUFFER_SIZE 4096

struct Cmdline {
    char error_msg[KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX];
    char *argv[CMDLINE_ARGV_COUNT_MAX];
    char buffer[CMDLINE_BUFFER_SIZE];
};

static const struct rb_data_type_struct cmdline_rbdata = {
    .wrap_struct_name = "cmdline",
    .function = {
        .dmark = NULL,
        .dfree = RUBY_DEFAULT_FREE,
        .dsize = NULL,
        .dcompact = NULL,
        .reserved = { 0 },
    },
    .parent = NULL,
    .data = NULL,
    .flags = RUBY_TYPED_FREE_IMMEDIATELY,
};

static VALUE rb_KernAux = Qnil;
static VALUE rb_KernAux_Cmdline = Qnil;

static VALUE rb_KernAux_Error = Qnil;
static VALUE rb_KernAux_CmdlineError = Qnil;

static void assert_cb(const char *file, int line, const char *str);

static VALUE rb_KernAux_assert_cb(VALUE self);
static VALUE rb_KernAux_assert_cb_EQ(VALUE self, VALUE assert_cb);
static
VALUE rb_KernAux_assert_do(VALUE self, VALUE file, VALUE line, VALUE msg);

static VALUE rb_KernAux_Cmdline_ALLOC(VALUE klass);

#ifdef HAVE_KERNAUX_UTOA10
static VALUE rb_KernAux_utoa10(VALUE self, VALUE number);
#endif
#ifdef HAVE_KERNAUX_ITOA10
static VALUE rb_KernAux_itoa10(VALUE self, VALUE number);
#endif
#ifdef HAVE_KERNAUX_SNPRINTF
static VALUE rb_KernAux_snprintf1(int argc, const VALUE *argv, VALUE self);
#endif
#ifdef HAVE_KERNAUX_CMDLINE
static VALUE rb_KernAux_cmdline(VALUE self, VALUE str);
#endif

void Init_default()
{
    rb_KernAux = rb_define_module("KernAux");
    rb_KernAux_Cmdline =
        rb_define_class_under(rb_KernAux, "Cmdline", rb_cObject);

    rb_define_alloc_func(rb_KernAux_Cmdline, rb_KernAux_Cmdline_ALLOC);

    rb_KernAux_Error =
        rb_define_class_under(rb_KernAux, "Error", rb_eRuntimeError);
    rb_KernAux_CmdlineError =
        rb_define_class_under(rb_KernAux, "CmdlineError", rb_KernAux_Error);

    kernaux_assert_cb = assert_cb;

    rb_define_singleton_method(rb_KernAux, "assert_cb",
                               rb_KernAux_assert_cb, 0);
    rb_define_singleton_method(rb_KernAux, "assert_cb=",
                               rb_KernAux_assert_cb_EQ, 1);
    rb_define_singleton_method(rb_KernAux, "assert_do",
                               rb_KernAux_assert_do, 3);

#ifdef HAVE_KERNAUX_UTOA10
    rb_define_singleton_method(rb_KernAux, "utoa10", rb_KernAux_utoa10, 1);
#endif
#ifdef HAVE_KERNAUX_ITOA10
    rb_define_singleton_method(rb_KernAux, "itoa10", rb_KernAux_itoa10, 1);
#endif
#ifdef HAVE_KERNAUX_SNPRINTF
    rb_define_singleton_method(rb_KernAux, "snprintf1",
                               rb_KernAux_snprintf1, -1);
#endif
#ifdef HAVE_KERNAUX_CMDLINE
    rb_define_singleton_method(rb_KernAux, "cmdline", rb_KernAux_cmdline, 1);
#endif
}

void assert_cb(const char *const file, const int line, const char *const str)
{
    const VALUE assert_cb_rb = rb_iv_get(rb_KernAux, "@assert_cb");
    if (assert_cb_rb == Qnil) return;
    const VALUE file_rb = rb_str_new2(file);
    const VALUE line_rb = INT2FIX(line);
    const VALUE str_rb = rb_str_new2(str);
    rb_funcall(assert_cb_rb, rb_intern("call"), 3, file_rb, line_rb, str_rb);
}

VALUE rb_KernAux_assert_cb(const VALUE self)
{
    return rb_iv_get(self, "@assert_cb");
}

VALUE rb_KernAux_assert_cb_EQ(const VALUE self, const VALUE assert_cb_rb)
{
    return rb_iv_set(self, "@assert_cb", assert_cb_rb);
}

VALUE rb_KernAux_assert_do(
    const VALUE self_rb __attribute__((unused)),
    VALUE file_rb,
    const VALUE line_rb,
    VALUE msg_rb
) {
    const char *const file = StringValueCStr(file_rb);
    const int line = FIX2INT(line_rb);
    const char *const msg = StringValueCStr(msg_rb);

    kernaux_assert_do(file, line, msg);

    return Qnil;
}

VALUE rb_KernAux_Cmdline_ALLOC(const VALUE klass)
{
    struct Cmdline *cmdline;
    return
        TypedData_Make_Struct(klass, struct Cmdline, &cmdline_rbdata, cmdline);
}

#ifdef HAVE_KERNAUX_UTOA10
VALUE rb_KernAux_utoa10(
    const VALUE self_rb __attribute__((unused)),
    const VALUE number_rb
) {
    RB_INTEGER_TYPE_P(number_rb);
    if (rb_funcall(number_rb, rb_intern("<"), 1, INT2FIX(0))) {
        rb_raise(rb_eRangeError, "can't convert negative number to uint64_t");
    }
    char buffer[KERNAUX_ITOA_BUFFER_SIZE];
    kernaux_utoa10(NUM2ULL(number_rb), buffer);
    return rb_funcall(rb_str_new2(buffer), rb_intern("freeze"), 0);
}
#endif

#ifdef HAVE_KERNAUX_ITOA10
VALUE rb_KernAux_itoa10(
    const VALUE self_rb __attribute__((unused)),
    const VALUE number_rb
) {
    RB_INTEGER_TYPE_P(number_rb);
    char buffer[KERNAUX_ITOA_BUFFER_SIZE];
    kernaux_itoa10(NUM2LL(number_rb), buffer);
    return rb_funcall(rb_str_new2(buffer), rb_intern("freeze"), 0);
}
#endif

#ifdef HAVE_KERNAUX_SNPRINTF
// TODO: is this implementation correct?
// FIXME: rewrite to ensure no memory leak on exception.
VALUE rb_KernAux_snprintf1(
    const int argc,
    const VALUE *const argv_rb,
    const VALUE self __attribute__((unused))
) {
    if (argc != 2 && argc != 3) rb_raise(rb_eArgError, "expected 2 or 3 args");

    const VALUE size_rb = argv_rb[0];
    VALUE format_rb = argv_rb[1];

    const int size = NUM2INT(size_rb);
    const char *const format = StringValueCStr(format_rb);

    if (size < 0) rb_raise(rb_eRangeError, "expected non-negative size");

    const char *fmt = format;

    while (*fmt && *fmt != '%') ++fmt;
    if (*(fmt++) != '%') rb_raise(rb_eArgError, "invalid format");

    // Mimic printf behavior.
    if (*fmt == '0' || *fmt == '-' || *fmt == '+' || *fmt == ' ' ||
        *fmt == '#')
    {
        ++fmt;
    }
    if (*fmt >= '0' && *fmt <= '9') {
        while (*fmt >= '0' && *fmt <= '9') ++fmt;
    } else if (*fmt == '*') {
        ++fmt;
    }
    if (*fmt == '.') {
        ++fmt;
        if (*fmt >= '0' && *fmt <= '9') {
            while (*fmt >= '0' && *fmt <= '9') ++fmt;
        } else if (*fmt == '*') {
            ++fmt;
        }
    }
    if (*fmt == 'l') {
        ++fmt;
        if (*fmt == 'l') ++fmt;
    } else if (*fmt == 'h') {
        ++fmt;
        if (*fmt == 'h') ++fmt;
    } else if (*fmt == 't' || *fmt == 'j' || *fmt == 'z') {
        ++fmt;
    }

    const char c = *fmt;

    if (*fmt == '%') ++fmt;
    while (*fmt) {
        if (*(fmt++) == '%') rb_raise(rb_eArgError, "invalid format");
    }

    union {
        const char *str;
        long long ll;
        unsigned long long ull;
        double dbl;
        char chr;
    } __attribute__((packed)) arg = { .str = "" };

    if (argc == 3) {
        VALUE arg_rb = argv_rb[2];

        if (c == 'd' || c == 'i') {
            RB_INTEGER_TYPE_P(arg_rb);
            arg.ll = NUM2LL(arg_rb);
        } else if (c == 'u' || c == 'x' || c == 'X' || c == 'o' || c == 'b') {
            RB_INTEGER_TYPE_P(arg_rb);
            arg.ull = NUM2ULL(arg_rb);
        } else if (c == 'f' || c == 'F' ||
                   c == 'e' || c == 'E' ||
                   c == 'g' || c == 'G')
        {
            // FIXME: this doesn't work
            RB_FLOAT_TYPE_P(arg_rb);
            arg.dbl = NUM2DBL(arg_rb);
        } else if (c == 'c') {
            Check_Type(arg_rb, T_STRING);
            arg.chr = *StringValuePtr(arg_rb);
        } else if (c == 's') {
            Check_Type(arg_rb, T_STRING);
            arg.str = StringValueCStr(arg_rb);
        }
    }

    char *const str = malloc(size);
    if (!str) rb_raise(rb_eNoMemError, "snprintf1 buffer malloc");
    const int slen = kernaux_snprintf(str, size, format, arg, "", "", "");
    const VALUE output_rb =
        rb_funcall(rb_str_new2(str), rb_intern("freeze"), 0);
    free(str);

    const VALUE result_rb = rb_ary_new2(2);
    rb_ary_push(result_rb, output_rb);
    rb_ary_push(result_rb, INT2NUM(slen));
    return rb_funcall(result_rb, rb_intern("freeze"), 0);
}
#endif

#ifdef HAVE_KERNAUX_CMDLINE
VALUE rb_KernAux_cmdline(const VALUE self_rb, VALUE str_rb)
{
    const char *const str = StringValueCStr(str_rb);
    size_t argc;

    const VALUE cmdline_rb =
        rb_funcall(rb_KernAux_Cmdline, rb_intern("new"), 0);
    struct Cmdline *cmdline;
    TypedData_Get_Struct(cmdline_rb, struct Cmdline, &cmdline_rbdata, cmdline);
    if (!cmdline) rb_raise(rb_KernAux_CmdlineError, "internal error");

    const bool result = kernaux_cmdline(
        str,
        cmdline->error_msg,
        &argc,
        cmdline->argv,
        cmdline->buffer,
        CMDLINE_ARGV_COUNT_MAX,
        CMDLINE_BUFFER_SIZE
    );

    if (!result) rb_raise(rb_KernAux_CmdlineError, "%s", cmdline->error_msg);

    VALUE result_rb = rb_ary_new2(argc);
    for (size_t index = 0; index < argc; ++index) {
        rb_ary_push(
            result_rb,
            rb_funcall(rb_str_new2(cmdline->argv[index]),
                                   rb_intern("freeze"), 0)
        );
    }
    return rb_funcall(result_rb, rb_intern("freeze"), 0);
}
#endif
