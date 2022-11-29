#include "main.h"

#ifdef KERNAUX_VERSION_WITH_NTOA

static VALUE rb_KernAux_utoa(int argc, const VALUE *argv, VALUE self);
static VALUE rb_KernAux_itoa(int argc, const VALUE *argv, VALUE self);
static VALUE rb_KernAux_utoa2(VALUE self, VALUE number);
static VALUE rb_KernAux_itoa2(VALUE self, VALUE number);
static VALUE rb_KernAux_utoa8(VALUE self, VALUE number);
static VALUE rb_KernAux_itoa8(VALUE self, VALUE number);
static VALUE rb_KernAux_utoa10(VALUE self, VALUE number);
static VALUE rb_KernAux_itoa10(VALUE self, VALUE number);
static VALUE rb_KernAux_utoa16(VALUE self, VALUE number);
static VALUE rb_KernAux_itoa16(VALUE self, VALUE number);

static ID rb_intern_b = Qnil;
static ID rb_intern_B = Qnil;
static ID rb_intern_h = Qnil;
static ID rb_intern_H = Qnil;
static ID rb_intern_o = Qnil;
static ID rb_intern_O = Qnil;
static ID rb_intern_d = Qnil;
static ID rb_intern_D = Qnil;
static ID rb_intern_x = Qnil;
static ID rb_intern_X = Qnil;

static VALUE rb_KernAux_InvalidNtoaBaseError = Qnil;
static VALUE rb_KernAux_TooLongNtoaPrefixError = Qnil;

static int convert_base(VALUE base);

void init_ntoa()
{
    rb_gc_register_mark_object(ID2SYM(rb_intern_b      = rb_intern("b")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_B      = rb_intern("B")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_h      = rb_intern("h")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_H      = rb_intern("H")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_o      = rb_intern("o")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_O      = rb_intern("O")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_d      = rb_intern("d")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_D      = rb_intern("D")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_x      = rb_intern("x")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_X      = rb_intern("X")));

    rb_gc_register_mark_object(rb_KernAux_InvalidNtoaBaseError =
        rb_define_class_under(rb_KernAux, "InvalidNtoaBaseError",
                              rb_KernAux_Error));
    rb_gc_register_mark_object(rb_KernAux_TooLongNtoaPrefixError =
        rb_define_class_under(rb_KernAux, "TooLongNtoaPrefixError",
                              rb_KernAux_Error));

    rb_define_singleton_method(rb_KernAux, "utoa", rb_KernAux_utoa, -1);
    rb_define_singleton_method(rb_KernAux, "itoa", rb_KernAux_itoa, -1);
    rb_define_singleton_method(rb_KernAux, "utoa2", rb_KernAux_utoa2, 1);
    rb_define_singleton_method(rb_KernAux, "itoa2", rb_KernAux_itoa2, 1);
    rb_define_singleton_method(rb_KernAux, "utoa8", rb_KernAux_utoa8, 1);
    rb_define_singleton_method(rb_KernAux, "itoa8", rb_KernAux_itoa8, 1);
    rb_define_singleton_method(rb_KernAux, "utoa10", rb_KernAux_utoa10, 1);
    rb_define_singleton_method(rb_KernAux, "itoa10", rb_KernAux_itoa10, 1);
    rb_define_singleton_method(rb_KernAux, "utoa16", rb_KernAux_utoa16, 1);
    rb_define_singleton_method(rb_KernAux, "itoa16", rb_KernAux_itoa16, 1);
}

VALUE rb_KernAux_utoa(const int argc, const VALUE *argv, const VALUE self)
{
    if (argc < 2 || argc > 3) {
        rb_raise(
            rb_eArgError,
            "wrong number of arguments (given %d, expected 2..3)",
            argc
        );
    }

    VALUE number_rb = argv[0];
    VALUE base_rb   = argv[1];
    VALUE prefix_rb = argc == 3 ? argv[2] : Qnil;

    const uint64_t number = NUM2ULL(number_rb);

    if (rb_funcall(number_rb, rb_intern_LESS, 1, INT2FIX(0))) {
        rb_raise(rb_eRangeError, "can't convert negative number to uint64_t");
    }

    const char *prefix = NULL;
    long prefix_len = 0;
    if (!NIL_P(prefix_rb)) {
        prefix = StringValueCStr(prefix_rb);
        prefix_len = RSTRING_LEN(prefix_rb);

        if (prefix_len > KERNAUX_NTOA_MAX_PREFIX_LEN || prefix_len < 0) {
            rb_raise(
                rb_KernAux_TooLongNtoaPrefixError,
                "prefix length %ld is too long",
                prefix_len
            );
        }
    }

    char buffer[KERNAUX_UTOA_MIN_BUFFER_SIZE + prefix_len];
    kernaux_utoa(number, buffer, convert_base(base_rb), prefix);
    return rb_funcall(rb_str_new2(buffer), rb_intern_freeze, 0);
}

VALUE rb_KernAux_itoa(const int argc, const VALUE *argv, const VALUE self)
{
    if (argc < 2 || argc > 3) {
        rb_raise(
            rb_eArgError,
            "wrong number of arguments (given %d, expected 2..3)",
            argc
        );
    }

    VALUE number_rb = argv[0];
    VALUE base_rb   = argv[1];
    VALUE prefix_rb = argc == 3 ? argv[2] : Qnil;

    const int64_t number = NUM2LL(number_rb);

    const char *prefix = NULL;
    long prefix_len = 0;
    if (!NIL_P(prefix_rb)) {
        prefix = StringValueCStr(prefix_rb);
        prefix_len = RSTRING_LEN(prefix_rb);

        if (prefix_len > KERNAUX_NTOA_MAX_PREFIX_LEN || prefix_len < 0) {
            rb_raise(
                rb_KernAux_TooLongNtoaPrefixError,
                "prefix length %ld is too long",
                prefix_len
            );
        }
    }

    char buffer[KERNAUX_ITOA_MIN_BUFFER_SIZE + prefix_len];
    kernaux_itoa(number, buffer, convert_base(base_rb), prefix);
    return rb_funcall(rb_str_new2(buffer), rb_intern_freeze, 0);
}

VALUE rb_KernAux_utoa2(
    const VALUE self_rb KERNAUX_UNUSED,
    const VALUE number_rb
) {
    const uint64_t number = NUM2ULL(number_rb);
    if (rb_funcall(number_rb, rb_intern_LESS, 1, INT2FIX(0))) {
        rb_raise(rb_eRangeError, "can't convert negative number to uint64_t");
    }
    char buffer[KERNAUX_UTOA2_BUFFER_SIZE];
    kernaux_utoa2(number, buffer);
    return rb_funcall(rb_str_new2(buffer), rb_intern_freeze, 0);
}

VALUE rb_KernAux_itoa2(
    const VALUE self_rb KERNAUX_UNUSED,
    const VALUE number_rb
) {
    const int64_t number = NUM2LL(number_rb);
    char buffer[KERNAUX_ITOA2_BUFFER_SIZE];
    kernaux_itoa2(number, buffer);
    return rb_funcall(rb_str_new2(buffer), rb_intern_freeze, 0);
}

VALUE rb_KernAux_utoa8(
    const VALUE self_rb KERNAUX_UNUSED,
    const VALUE number_rb
) {
    const uint64_t number = NUM2ULL(number_rb);
    if (rb_funcall(number_rb, rb_intern_LESS, 1, INT2FIX(0))) {
        rb_raise(rb_eRangeError, "can't convert negative number to uint64_t");
    }
    char buffer[KERNAUX_UTOA8_BUFFER_SIZE];
    kernaux_utoa8(number, buffer);
    return rb_funcall(rb_str_new2(buffer), rb_intern_freeze, 0);
}

VALUE rb_KernAux_itoa8(
    const VALUE self_rb KERNAUX_UNUSED,
    const VALUE number_rb
) {
    const int64_t number = NUM2LL(number_rb);
    char buffer[KERNAUX_ITOA8_BUFFER_SIZE];
    kernaux_itoa8(number, buffer);
    return rb_funcall(rb_str_new2(buffer), rb_intern_freeze, 0);
}

VALUE rb_KernAux_utoa10(
    const VALUE self_rb KERNAUX_UNUSED,
    const VALUE number_rb
) {
    const uint64_t number = NUM2ULL(number_rb);
    if (rb_funcall(number_rb, rb_intern_LESS, 1, INT2FIX(0))) {
        rb_raise(rb_eRangeError, "can't convert negative number to uint64_t");
    }
    char buffer[KERNAUX_UTOA10_BUFFER_SIZE];
    kernaux_utoa10(number, buffer);
    return rb_funcall(rb_str_new2(buffer), rb_intern_freeze, 0);
}

VALUE rb_KernAux_itoa10(
    const VALUE self_rb KERNAUX_UNUSED,
    const VALUE number_rb
) {
    const int64_t number = NUM2LL(number_rb);
    char buffer[KERNAUX_ITOA10_BUFFER_SIZE];
    kernaux_itoa10(number, buffer);
    return rb_funcall(rb_str_new2(buffer), rb_intern_freeze, 0);
}

VALUE rb_KernAux_utoa16(
    const VALUE self_rb KERNAUX_UNUSED,
    const VALUE number_rb
) {
    const uint64_t number = NUM2ULL(number_rb);
    if (rb_funcall(number_rb, rb_intern_LESS, 1, INT2FIX(0))) {
        rb_raise(rb_eRangeError, "can't convert negative number to uint64_t");
    }
    char buffer[KERNAUX_UTOA16_BUFFER_SIZE];
    kernaux_utoa16(number, buffer);
    return rb_funcall(rb_str_new2(buffer), rb_intern_freeze, 0);
}

VALUE rb_KernAux_itoa16(
    const VALUE self_rb KERNAUX_UNUSED,
    const VALUE number_rb
) {
    const int64_t number = NUM2LL(number_rb);
    char buffer[KERNAUX_ITOA16_BUFFER_SIZE];
    kernaux_itoa16(number, buffer);
    return rb_funcall(rb_str_new2(buffer), rb_intern_freeze, 0);
}

int convert_base(const VALUE base_rb)
{
    if (TYPE(base_rb) == T_SYMBOL) {
        const ID base_id = SYM2ID(base_rb);
        if      (base_id == rb_intern_b) return 'b';
        else if (base_id == rb_intern_B) return 'B';
        else if (base_id == rb_intern_h) return 'h';
        else if (base_id == rb_intern_H) return 'H';
        else if (base_id == rb_intern_o) return 'o';
        else if (base_id == rb_intern_O) return 'O';
        else if (base_id == rb_intern_d) return 'd';
        else if (base_id == rb_intern_D) return 'D';
        else if (base_id == rb_intern_x) return 'x';
        else if (base_id == rb_intern_X) return 'X';
        else {
            rb_raise(rb_KernAux_InvalidNtoaBaseError, "invalid base");
        }
    } else {
        return NUM2INT(base_rb);
    }
}

#endif // KERNAUX_VERSION_WITH_NTOA
