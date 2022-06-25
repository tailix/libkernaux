#include "main.h"

ID rb_intern_call   = Qnil;
ID rb_intern_freeze = Qnil;
ID rb_intern_LESS   = Qnil;
ID rb_intern_new    = Qnil;

VALUE rb_KernAux = Qnil;
VALUE rb_KernAux_Error = Qnil;

void Init_default()
{
    rb_gc_register_mark_object(ID2SYM(rb_intern_call   = rb_intern("call")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_freeze = rb_intern("freeze")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_LESS   = rb_intern("<")));
    rb_gc_register_mark_object(ID2SYM(rb_intern_new    = rb_intern("new")));

    rb_gc_register_mark_object(rb_KernAux = rb_define_module("KernAux"));
    rb_gc_register_mark_object(rb_KernAux_Error =
        rb_define_class_under(rb_KernAux, "Error", rb_eRuntimeError));

    init_version();
    init_assert();

#ifdef KERNAUX_VERSION_WITH_CMDLINE
    init_cmdline();
#endif // KERNAUX_VERSION_WITH_CMDLINE
#ifdef KERNAUX_VERSION_WITH_NTOA
    init_ntoa();
#endif // KERNAUX_VERSION_WITH_NTOA
#ifdef KERNAUX_VERSION_WITH_PRINTF
    init_printf();
#endif // KERNAUX_VERSION_WITH_PRINTF
}
