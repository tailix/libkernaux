#include "main.h"

#ifdef KERNAUX_VERSION_WITH_MULTIBOOT2

VALUE rb_KernAux_Multiboot2 = Qnil;

void init_multiboot2()
{
    rb_gc_register_mark_object(rb_KernAux_Multiboot2 =
        rb_define_module_under(rb_KernAux, "Multiboot2"));
}

#endif
