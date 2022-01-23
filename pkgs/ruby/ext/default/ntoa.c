#include <kernaux.h>
#include <ruby.h>

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
static ID rb_intern_freeze = Qnil;
static VALUE rb_KernAux = Qnil;

void init_ntoa()
{
    rb_gc_register_mark_object(rb_intern_LESS   = rb_intern("<"));
    rb_gc_register_mark_object(rb_intern_freeze = rb_intern("freeze"));
    rb_gc_register_mark_object(rb_KernAux       = rb_define_module("KernAux"));

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

#ifdef HAVE_KERNAUX_UTOA10
VALUE rb_KernAux_utoa10(
    const VALUE self_rb __attribute__((unused)),
    const VALUE number_rb
) {
    RB_INTEGER_TYPE_P(number_rb);
    if (rb_funcall(number_rb, rb_intern_LESS, 1, INT2FIX(0))) {
        rb_raise(rb_eRangeError, "can't convert negative number to uint64_t");
    }
    char buffer[KERNAUX_ITOA10_BUFFER_SIZE];
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
    char buffer[KERNAUX_ITOA16_BUFFER_SIZE];
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
