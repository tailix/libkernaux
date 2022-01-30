#include <kernaux.h>
#include <ruby.h>

#ifdef HAVE_KERNAUX_UTOA
static VALUE rb_KernAux_utoa(VALUE self, VALUE number, VALUE base);
#endif
#ifdef HAVE_KERNAUX_ITOA
static VALUE rb_KernAux_itoa(VALUE self, VALUE number, VALUE base);
#endif
#ifdef HAVE_KERNAUX_UTOA10
static VALUE rb_KernAux_utoa10(VALUE self, VALUE number);
#endif
#ifdef HAVE_KERNAUX_ITOA10
static VALUE rb_KernAux_itoa10(VALUE self, VALUE number);
#endif
#ifdef HAVE_KERNAUX_UTOA16
static VALUE rb_KernAux_utoa16(VALUE self, VALUE number);
#endif
#ifdef HAVE_KERNAUX_ITOA16
static VALUE rb_KernAux_itoa16(VALUE self, VALUE number);
#endif

static ID rb_intern_LESS = Qnil;
static ID rb_intern_b = Qnil;
static ID rb_intern_B = Qnil;
static ID rb_intern_freeze = Qnil;
static ID rb_intern_h = Qnil;
static ID rb_intern_H = Qnil;
static ID rb_intern_o = Qnil;
static ID rb_intern_O = Qnil;
static ID rb_intern_d = Qnil;
static ID rb_intern_D = Qnil;
static ID rb_intern_x = Qnil;
static ID rb_intern_X = Qnil;

static VALUE rb_KernAux = Qnil;
static VALUE rb_KernAux_Error = Qnil;
static VALUE rb_KernAux_InvalidNtoaBaseError = Qnil;

#if defined(HAVE_KERNAUX_UTOA) || defined(HAVE_KERNAUX_ITOA)
static int convert_base(VALUE base);
#endif

void init_ntoa()
{
    rb_gc_register_mark_object(ID2SYM(rb_intern_LESS   = rb_intern("<")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_b      = rb_intern("b")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_B      = rb_intern("B")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_freeze = rb_intern("freeze")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_h      = rb_intern("h")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_H      = rb_intern("H")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_o      = rb_intern("o")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_O      = rb_intern("O")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_d      = rb_intern("d")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_D      = rb_intern("D")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_x      = rb_intern("x")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_X      = rb_intern("X")));

    rb_gc_register_mark_object(rb_KernAux = rb_define_module("KernAux"));
    rb_gc_register_mark_object(rb_KernAux_Error =
        rb_define_class_under(rb_KernAux, "Error", rb_eRuntimeError));
    rb_gc_register_mark_object(rb_KernAux_InvalidNtoaBaseError =
        rb_define_class_under(rb_KernAux, "InvalidNtoaBaseError",
                              rb_KernAux_Error));

#ifdef HAVE_KERNAUX_UTOA
    rb_define_singleton_method(rb_KernAux, "utoa", rb_KernAux_utoa, 2);
#endif
#ifdef HAVE_KERNAUX_ITOA
    rb_define_singleton_method(rb_KernAux, "itoa", rb_KernAux_itoa, 2);
#endif
#ifdef HAVE_KERNAUX_UTOA10
    rb_define_singleton_method(rb_KernAux, "utoa10", rb_KernAux_utoa10, 1);
#endif
#ifdef HAVE_KERNAUX_ITOA10
    rb_define_singleton_method(rb_KernAux, "itoa10", rb_KernAux_itoa10, 1);
#endif
#ifdef HAVE_KERNAUX_UTOA16
    rb_define_singleton_method(rb_KernAux, "utoa16", rb_KernAux_utoa16, 1);
#endif
#ifdef HAVE_KERNAUX_ITOA16
    rb_define_singleton_method(rb_KernAux, "itoa16", rb_KernAux_itoa16, 1);
#endif
}

#ifdef HAVE_KERNAUX_UTOA
VALUE rb_KernAux_utoa(
    const VALUE self_rb __attribute__((unused)),
    const VALUE number_rb,
    const VALUE base_rb
) {
    RB_INTEGER_TYPE_P(number_rb);
    if (rb_funcall(number_rb, rb_intern_LESS, 1, INT2FIX(0))) {
        rb_raise(rb_eRangeError, "can't convert negative number to uint64_t");
    }
    char buffer[KERNAUX_UTOA_BUFFER_SIZE];
    kernaux_utoa(NUM2ULL(number_rb), buffer, convert_base(base_rb));
    return rb_funcall(rb_str_new2(buffer), rb_intern_freeze, 0);
}
#endif

#ifdef HAVE_KERNAUX_ITOA
VALUE rb_KernAux_itoa(
    const VALUE self_rb __attribute__((unused)),
    const VALUE number_rb,
    const VALUE base_rb
) {
    RB_INTEGER_TYPE_P(number_rb);
    char buffer[KERNAUX_ITOA_BUFFER_SIZE];
    kernaux_itoa(NUM2LL(number_rb), buffer, convert_base(base_rb));
    return rb_funcall(rb_str_new2(buffer), rb_intern_freeze, 0);
}
#endif

#ifdef HAVE_KERNAUX_UTOA10
VALUE rb_KernAux_utoa10(
    const VALUE self_rb __attribute__((unused)),
    const VALUE number_rb
) {
    RB_INTEGER_TYPE_P(number_rb);
    if (rb_funcall(number_rb, rb_intern_LESS, 1, INT2FIX(0))) {
        rb_raise(rb_eRangeError, "can't convert negative number to uint64_t");
    }
    char buffer[KERNAUX_UTOA10_BUFFER_SIZE];
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
    char buffer[KERNAUX_ITOA10_BUFFER_SIZE];
    kernaux_itoa10(NUM2LL(number_rb), buffer);
    return rb_funcall(rb_str_new2(buffer), rb_intern_freeze, 0);
}
#endif

#ifdef HAVE_KERNAUX_UTOA16
VALUE rb_KernAux_utoa16(
    const VALUE self_rb __attribute__((unused)),
    const VALUE number_rb
) {
    RB_INTEGER_TYPE_P(number_rb);
    if (rb_funcall(number_rb, rb_intern_LESS, 1, INT2FIX(0))) {
        rb_raise(rb_eRangeError, "can't convert negative number to uint64_t");
    }
    char buffer[KERNAUX_UTOA16_BUFFER_SIZE];
    kernaux_utoa16(NUM2ULL(number_rb), buffer);
    return rb_funcall(rb_str_new2(buffer), rb_intern_freeze, 0);
}
#endif

#ifdef HAVE_KERNAUX_ITOA16
VALUE rb_KernAux_itoa16(
    const VALUE self_rb __attribute__((unused)),
    const VALUE number_rb
) {
    RB_INTEGER_TYPE_P(number_rb);
    char buffer[KERNAUX_ITOA16_BUFFER_SIZE];
    kernaux_itoa16(NUM2LL(number_rb), buffer);
    return rb_funcall(rb_str_new2(buffer), rb_intern_freeze, 0);
}
#endif

#if defined(HAVE_KERNAUX_UTOA) || defined(HAVE_KERNAUX_ITOA)
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
#endif