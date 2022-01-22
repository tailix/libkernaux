#include <kernaux.h>
#include <ruby.h>

#ifdef HAVE_KERNAUX_SNPRINTF

static VALUE rb_KernAux_snprintf1(int argc, const VALUE *argv, VALUE self);

static ID rb_intern_freeze;

static VALUE rb_KernAux = Qnil;

void init_printf()
{
    rb_gc_register_mark_object(rb_intern_freeze = rb_intern("freeze"));

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
    if (argc < 2 || argc > 4) rb_raise(rb_eArgError, "expected 2, 3 or 4 args");

    const VALUE size_rb = argv_rb[0];
    VALUE format_rb = argv_rb[1];

    const int size = NUM2INT(size_rb);
    const char *const format = StringValueCStr(format_rb);

    if (size < 0) rb_raise(rb_eRangeError, "expected non-negative size");

    const char *fmt = format;

    while (*fmt && *fmt != '%') ++fmt;
    if (*(fmt++) != '%') rb_raise(rb_eArgError, "invalid format");

    bool has_width = false;

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
        has_width = true;
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

    int width = 0;
    if (has_width && argc > 2) width = NUM2INT(argv_rb[2]);

    bool use_dbl = false;
    double dbl;
    union {
        const char *str;
        long long ll;
        unsigned long long ull;
        char chr;
    } __attribute__((packed)) arg = { .str = "" };

    if (argc == (has_width ? 4 : 3)) {
        VALUE arg_rb = argv_rb[has_width ? 3 : 2];

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

    int slen;
    if (has_width) {
        slen = use_dbl
            ? kernaux_snprintf(str, size, format, width, dbl)
            : kernaux_snprintf(str, size, format, width, arg);
    } else {
        slen = use_dbl
            ? kernaux_snprintf(str, size, format, dbl)
            : kernaux_snprintf(str, size, format, arg);
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
