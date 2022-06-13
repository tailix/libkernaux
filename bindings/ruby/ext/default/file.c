#include "main.h"

#ifdef KERNAUX_VERSION_SUPPORTS_FILE

static VALUE rb_KernAux_File_initialize(VALUE self, VALUE out);

static ID rb_intern_ATout = Qnil;

static VALUE rb_KernAux = Qnil;
static VALUE rb_KernAux_File = Qnil;

void init_file() {
    rb_gc_register_mark_object(ID2SYM(rb_intern_ATout = rb_intern("@out")));

    rb_gc_register_mark_object(rb_KernAux = rb_define_module("KernAux"));
    rb_gc_register_mark_object(rb_KernAux_File =
        rb_define_class_under(rb_KernAux, "File", rb_cObject));

    rb_define_method(rb_KernAux_File, "initialize",
                     rb_KernAux_File_initialize, 1);
}

VALUE rb_KernAux_File_initialize(VALUE self, VALUE out)
{
    rb_ivar_set(self, rb_intern_ATout, out);
    return Qnil;
}

#endif // KERNAUX_VERSION_SUPPORTS_FILE
