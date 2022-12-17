#include "main.h"

#include <stddef.h>

#ifdef KERNAUX_VERSION_WITH_MULTIBOOT2

#define RBNSMDL rb_KernAux_Multiboot2
#define RBNS(s) rb_KernAux_Multiboot2_##s

#define ENSURE_BASE_SIZE(data, Type) do { \
    const long len = RSTRING_LEN(data);                                       \
    if (len < 0 || (size_t)len <= sizeof(struct KernAux_Multiboot2_##Type)) { \
        return Qnil;                                                          \
    }                                                                         \
} while (0)

VALUE RBNSMDL             = Qnil; // KernAux::Multiboot2
VALUE RBNS(BaseSizeError) = Qnil; // KernAux::Multiboot2::BaseSizeError
VALUE RBNS(InvalidError)  = Qnil; // KernAux::Multiboot2::InvalidError
VALUE RBNS(Struct)        = Qnil; // KernAux::Multiboot2::Struct
VALUE RBNS(Header)        = Qnil; // KernAux::Multiboot2::Header

/**
 * Return the magic field of the Multiboot 2 header.
 *
 * @return [nil, Integer]
 *
 * @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Header-magic-fields
 */
// KernAux::Multiboot2::Header#magic
static VALUE rb_KernAux_Multiboot2_Header_magic(VALUE self);

void init_multiboot2()
{
    // KernAux::Multiboot2
    rb_gc_register_mark_object(rb_KernAux_Multiboot2 =
        rb_define_module_under(rb_KernAux, "Multiboot2"));

    // KernAux::Multiboot2::BaseSizeError
    rb_gc_register_mark_object(rb_KernAux_Multiboot2_BaseSizeError =
        rb_define_class_under(
            rb_KernAux_Multiboot2, "BaseSizeError", rb_KernAux_Error));

    // KernAux::Multiboot2::InvalidError
    rb_gc_register_mark_object(rb_KernAux_Multiboot2_InvalidError =
        rb_define_class_under(
            rb_KernAux_Multiboot2, "InvalidError", rb_KernAux_Error));

    // KernAux::Multiboot2::Struct
    rb_gc_register_mark_object(rb_KernAux_Multiboot2_Struct =
        rb_define_class_under(
            rb_KernAux_Multiboot2, "Struct", rb_cObject));

    // KernAux::Multiboot2::Header
    rb_gc_register_mark_object(rb_KernAux_Multiboot2_Header =
        rb_define_class_under(
            rb_KernAux_Multiboot2, "Header", rb_KernAux_Multiboot2_Struct));
    rb_define_method(rb_KernAux_Multiboot2_Header, "magic",
                     rb_KernAux_Multiboot2_Header_magic, 0);
}

// KernAux::Multiboot2::Header#magic
VALUE rb_KernAux_Multiboot2_Header_magic(VALUE self)
{
    VALUE data = rb_ivar_get(self, rb_intern("@data"));
    const struct KernAux_Multiboot2_Header *const multiboot2_header =
        (const struct KernAux_Multiboot2_Header*)
        StringValuePtr(data);
    ENSURE_BASE_SIZE(data, Header);
    KERNAUX_CAST_CONST(unsigned long, magic, multiboot2_header->magic);
    return ULONG2NUM(magic);
}

#endif
