#include <stdint.h>

#include <kernaux.h>
#include <ruby.h>

static VALUE rb_KernAux = Qnil;

static VALUE rb_KernAux_utoa10(VALUE self, VALUE number);
static VALUE rb_KernAux_itoa10(VALUE self, VALUE number);

void Init_default()
{
    rb_KernAux = rb_define_module("KernAux");
    rb_define_singleton_method(rb_KernAux, "utoa10", rb_KernAux_utoa10, 1);
    rb_define_singleton_method(rb_KernAux, "itoa10", rb_KernAux_itoa10, 1);
}

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

VALUE rb_KernAux_itoa10(
    const VALUE self_rb __attribute__((unused)),
    const VALUE number_rb
) {
    RB_INTEGER_TYPE_P(number_rb);
    char buffer[KERNAUX_ITOA_BUFFER_SIZE];
    kernaux_itoa10(NUM2LL(number_rb), buffer);
    return rb_funcall(rb_str_new2(buffer), rb_intern("freeze"), 0);
}
