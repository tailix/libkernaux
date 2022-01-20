#include <stdint.h>

#include <kernaux.h>
#include <ruby.h>

static VALUE rb_KernAux = Qnil;

static void assert_cb(const char *file, int line, const char *str);

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

void Init_default()
{
    rb_KernAux = rb_define_module("KernAux");

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
