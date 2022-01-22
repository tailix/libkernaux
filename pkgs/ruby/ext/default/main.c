#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <kernaux.h>
#include <ruby.h>

static ID rb_intern_LESS, rb_intern_call, rb_intern_freeze;

static VALUE rb_KernAux = Qnil;
static VALUE rb_KernAux_Error = Qnil;

static void assert_cb(const char *file, int line, const char *str);

#ifdef HAVE_KERNAUX_CMDLINE
void init_cmdline();
#endif // HAVE_KERNAUX_CMDLINE

static VALUE rb_KernAux_assert_cb(VALUE self);
static VALUE rb_KernAux_assert_cb_EQ(VALUE self, VALUE assert_cb);
static
VALUE rb_KernAux_assert_do(VALUE self, VALUE file, VALUE line, VALUE msg);

#ifdef HAVE_KERNAUX_UTOA10
static VALUE rb_KernAux_utoa10(VALUE self, VALUE number);
#endif
#ifdef HAVE_KERNAUX_ITOA10
static VALUE rb_KernAux_itoa10(VALUE self, VALUE number);
#endif
#ifdef HAVE_KERNAUX_SNPRINTF
static VALUE rb_KernAux_snprintf1(int argc, const VALUE *argv, VALUE self);
#endif

void Init_default()
{
#ifdef HAVE_KERNAUX_CMDLINE
    init_cmdline();
#endif // HAVE_KERNAUX_CMDLINE

    rb_gc_register_mark_object(rb_intern_LESS   = rb_intern("<"));
    rb_gc_register_mark_object(rb_intern_call   = rb_intern("call"));
    rb_gc_register_mark_object(rb_intern_freeze = rb_intern("freeze"));

    rb_gc_register_mark_object(rb_KernAux = rb_define_module("KernAux"));

    rb_gc_register_mark_object(rb_KernAux_Error =
        rb_define_class_under(rb_KernAux, "Error", rb_eRuntimeError));

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
}

void assert_cb(const char *const file, const int line, const char *const str)
{
    const VALUE assert_cb_rb = rb_iv_get(rb_KernAux, "@assert_cb");
    if (assert_cb_rb == Qnil) return;
    const VALUE file_rb = rb_str_new2(file);
    const VALUE line_rb = INT2FIX(line);
    const VALUE str_rb = rb_str_new2(str);
    rb_funcall(assert_cb_rb, rb_intern_call, 3, file_rb, line_rb, str_rb);
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

#ifdef HAVE_KERNAUX_UTOA10
VALUE rb_KernAux_utoa10(
    const VALUE self_rb __attribute__((unused)),
    const VALUE number_rb
) {
    RB_INTEGER_TYPE_P(number_rb);
    if (rb_funcall(number_rb, rb_intern_LESS, 1, INT2FIX(0))) {
        rb_raise(rb_eRangeError, "can't convert negative number to uint64_t");
    }
    char buffer[KERNAUX_ITOA_BUFFER_SIZE];
    kernaux_utoa10(NUM2ULL(number_rb), buffer);
    return rb_funcall(rb_str_new2(buffer), rb_intern_freeze, 0);
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
    return rb_funcall(rb_str_new2(buffer), rb_intern_freeze, 0);
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
    {
        bool flags;
        do {
            if (*fmt == '0' || *fmt == '-' || *fmt == '+' || *fmt == ' ' ||
                *fmt == '#')
            {
                ++fmt;
                flags = true;
            } else {
                flags = false;
            }
        } while (flags);
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

    bool use_dbl = false;
    double dbl;
    union {
        const char *str;
        long long ll;
        unsigned long long ull;
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
            RB_FLOAT_TYPE_P(arg_rb);
            use_dbl = true;
            dbl = NUM2DBL(arg_rb);
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
    const int slen = use_dbl
        ? kernaux_snprintf(str, size, format, dbl)
        : kernaux_snprintf(str, size, format, arg);
    const VALUE output_rb =
        rb_funcall(rb_str_new2(str), rb_intern_freeze, 0);
    free(str);

    const VALUE result_rb = rb_ary_new2(2);
    rb_ary_push(result_rb, output_rb);
    rb_ary_push(result_rb, INT2NUM(slen));
    return rb_funcall(result_rb, rb_intern_freeze, 0);
}
#endif
