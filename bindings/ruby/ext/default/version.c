#include "main.h"

static VALUE rb_KernAux_Version_with_cmdlineQN(VALUE self);
static VALUE rb_KernAux_Version_with_ntoaQN(VALUE self);
static VALUE rb_KernAux_Version_with_printfQN(VALUE self);

static VALUE rb_KernAux_Version = Qnil;

void init_version()
{
    rb_gc_register_mark_object(rb_KernAux_Version =
        rb_define_module_under(rb_KernAux, "Version"));

    rb_define_singleton_method(rb_KernAux_Version, "with_cmdline?",
                               rb_KernAux_Version_with_cmdlineQN, 0);
    rb_define_singleton_method(rb_KernAux_Version, "with_ntoa?",
                               rb_KernAux_Version_with_ntoaQN, 0);
    rb_define_singleton_method(rb_KernAux_Version, "with_printf?",
                               rb_KernAux_Version_with_printfQN, 0);
}

VALUE rb_KernAux_Version_with_cmdlineQN(VALUE self)
{
#ifdef KERNAUX_VERSION_WITH_CMDLINE
    return Qtrue;
#else
    return Qfalse;
#endif
}

VALUE rb_KernAux_Version_with_ntoaQN(VALUE self)
{
#ifdef KERNAUX_VERSION_WITH_NTOA
    return Qtrue;
#else
    return Qfalse;
#endif
}

VALUE rb_KernAux_Version_with_printfQN(VALUE self)
{
#ifdef KERNAUX_VERSION_WITH_PRINTF
    return Qtrue;
#else
    return Qfalse;
#endif
}
