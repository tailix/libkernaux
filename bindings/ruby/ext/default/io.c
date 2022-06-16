#include "main.h"

#ifdef KERNAUX_VERSION_WITH_IO

static VALUE rb_KernAux_OldFile_initialize(VALUE self, VALUE out);

static ID rb_intern_ATout = Qnil;

static VALUE rb_KernAux_OldFile = Qnil;

void init_io() {
    rb_gc_register_mark_object(ID2SYM(rb_intern_ATout = rb_intern("@out")));

    rb_gc_register_mark_object(rb_KernAux_OldFile =
        rb_define_class_under(rb_KernAux, "File", rb_cObject));

    rb_define_method(rb_KernAux_OldFile, "initialize",
                     rb_KernAux_OldFile_initialize, 1);
}

VALUE rb_KernAux_OldFile_initialize(VALUE self, VALUE out)
{
    rb_ivar_set(self, rb_intern_ATout, out);
    return Qnil;
}

#endif // KERNAUX_VERSION_WITH_IO
