#include "main.h"

static VALUE rb_KernAux_Version_supports_cmdlineQN(VALUE self);
static VALUE rb_KernAux_Version_supports_fileQN(VALUE self);
static VALUE rb_KernAux_Version_supports_ntoaQN(VALUE self);
static VALUE rb_KernAux_Version_supports_printfQN(VALUE self);

static VALUE rb_KernAux = Qnil;
static VALUE rb_KernAux_Version = Qnil;

void init_version()
{
    rb_gc_register_mark_object(rb_KernAux = rb_define_module("KernAux"));
    rb_gc_register_mark_object(rb_KernAux_Version =
        rb_define_module_under(rb_KernAux, "Version"));

    rb_define_singleton_method(rb_KernAux_Version, "supports_cmdline?",
                               rb_KernAux_Version_supports_cmdlineQN, 0);
    rb_define_singleton_method(rb_KernAux_Version, "supports_file?",
                               rb_KernAux_Version_supports_fileQN, 0);
    rb_define_singleton_method(rb_KernAux_Version, "supports_ntoa?",
                               rb_KernAux_Version_supports_ntoaQN, 0);
    rb_define_singleton_method(rb_KernAux_Version, "supports_printf?",
                               rb_KernAux_Version_supports_printfQN, 0);
}

VALUE rb_KernAux_Version_supports_cmdlineQN(VALUE self)
{
#ifdef KERNAUX_VERSION_SUPPORTS_CMDLINE
    return Qtrue;
#else
    return Qfalse;
#endif
}

VALUE rb_KernAux_Version_supports_fileQN(VALUE self)
{
#ifdef KERNAUX_VERSION_SUPPORTS_FILE
    return Qtrue;
#else
    return Qfalse;
#endif
}

VALUE rb_KernAux_Version_supports_ntoaQN(VALUE self)
{
#ifdef KERNAUX_VERSION_SUPPORTS_NTOA
    return Qtrue;
#else
    return Qfalse;
#endif
}

VALUE rb_KernAux_Version_supports_printfQN(VALUE self)
{
#ifdef KERNAUX_VERSION_SUPPORTS_PRINTF
    return Qtrue;
#else
    return Qfalse;
#endif
}
