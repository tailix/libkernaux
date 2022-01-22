#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <kernaux.h>
#include <ruby.h>

void init_assert();
#ifdef HAVE_KERNAUX_SNPRINTF
void init_printf();
#endif // HAVE_KERNAUX_SNPRINTF
#ifdef HAVE_KERNAUX_CMDLINE
void init_cmdline();
#endif // HAVE_KERNAUX_CMDLINE

#ifdef HAVE_KERNAUX_UTOA10
static VALUE rb_KernAux_utoa10(VALUE self, VALUE number);
#endif
#ifdef HAVE_KERNAUX_ITOA10
static VALUE rb_KernAux_itoa10(VALUE self, VALUE number);
#endif

static ID rb_intern_LESS = Qnil;
static ID rb_intern_call = Qnil;
static ID rb_intern_freeze = Qnil;

static VALUE rb_KernAux = Qnil;
static VALUE rb_KernAux_Error = Qnil;

void Init_default()
{
    init_assert();
#ifdef HAVE_KERNAUX_SNPRINTF
    init_printf();
#endif // HAVE_KERNAUX_SNPRINTF
#ifdef HAVE_KERNAUX_CMDLINE
    init_cmdline();
#endif // HAVE_KERNAUX_CMDLINE

    rb_gc_register_mark_object(rb_intern_LESS   = rb_intern("<"));
    rb_gc_register_mark_object(rb_intern_call   = rb_intern("call"));
    rb_gc_register_mark_object(rb_intern_freeze = rb_intern("freeze"));

    rb_gc_register_mark_object(rb_KernAux = rb_define_module("KernAux"));
    rb_gc_register_mark_object(rb_KernAux_Error =
        rb_define_class_under(rb_KernAux, "Error", rb_eRuntimeError));

#ifdef HAVE_KERNAUX_UTOA10
    rb_define_singleton_method(rb_KernAux, "utoa10", rb_KernAux_utoa10, 1);
#endif
#ifdef HAVE_KERNAUX_ITOA10
    rb_define_singleton_method(rb_KernAux, "itoa10", rb_KernAux_itoa10, 1);
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
