#include "main.h"

#include <stddef.h>

#ifdef KERNAUX_VERSION_WITH_MULTIBOOT2

#define RBNSMDL rb_KernAux_Multiboot2
#define RBNS(s) rb_KernAux_Multiboot2_##s

#define EXTRACT_BASE_PTR(Type, name, data, Qnegresult) \
    const struct KernAux_Multiboot2_##Type *const name =                    \
        (const struct KernAux_Multiboot2_##Type*)                           \
        StringValuePtr(data);                                               \
    const long data_size = RSTRING_LEN(data);                               \
    do {                                                                    \
        if (data_size < 0) return (Qnegresult);                             \
        if ((size_t)data_size < sizeof(struct KernAux_Multiboot2_##Type)) { \
            return (Qnegresult);                                            \
        }                                                                   \
    } while (0)

#define ENSURE_WHOLE_SIZE(name, Qnegresult) do { \
    if ((size_t)data_size < (name)->total_size) return (Qnegresult); \
} while (0)

VALUE RBNSMDL             = Qnil; // KernAux::Multiboot2
VALUE RBNS(BaseSizeError) = Qnil; // KernAux::Multiboot2::BaseSizeError
VALUE RBNS(InvalidError)  = Qnil; // KernAux::Multiboot2::InvalidError
VALUE RBNS(Struct)        = Qnil; // KernAux::Multiboot2::Struct
VALUE RBNS(Header)        = Qnil; // KernAux::Multiboot2::Header
VALUE RBNS(Info)          = Qnil; // KernAux::Multiboot2::Info



/*******************************
 * KernAux::Multiboot2::Header *
 *******************************/

/**
 * Test whether a Multiboot 2 header data is not shorter than it's base.
 *
 * @return [Boolean]
 */
static VALUE rb_KernAux_Multiboot2_Header_enoughQN(VALUE self);

/**
 * Test whether a Multiboot 2 header is valid.
 *
 * @return [Boolean]
 */
static VALUE rb_KernAux_Multiboot2_Header_validQN(VALUE self);

/**
 * Return the magic field of the Multiboot 2 header.
 *
 * @return [nil, Integer]
 *
 * @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Header-magic-fields
 */
static VALUE rb_KernAux_Multiboot2_Header_magic(VALUE self);

/**
 * Return the architecture field of the Multiboot 2 header.
 *
 * @return [nil, Integer]
 *
 * @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Header-magic-fields
 */
static VALUE rb_KernAux_Multiboot2_Header_arch(VALUE self);

/**
 * Return the total size (length) field of the Multiboot 2 header.
 *
 * @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Header-magic-fields
 *
 * @return [nil, Integer]
 */
static VALUE rb_KernAux_Multiboot2_Header_total_size(VALUE self);

/**
 * Return the checksum field of the Multiboot 2 header.
 *
 * @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Header-magic-fields
 *
 * @return [nil, Integer]
 */
static VALUE rb_KernAux_Multiboot2_Header_checksum(VALUE self);

/*****************************
 * KernAux::Multiboot2::Info *
 *****************************/

/**
 * Test whether a Multiboot 2 information data is not shorter than it's base.
 *
 * @return [Boolean]
 */
static VALUE rb_KernAux_Multiboot2_Info_enoughQN(VALUE self);

/**
 * Test whether a Multiboot 2 information is valid.
 *
 * @return [Boolean]
 */
static VALUE rb_KernAux_Multiboot2_Info_validQN(VALUE self);

/**
 * Return the total size field of the Multiboot 2 information.
 *
 * @return [nil, Integer]
 *
 * @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Basic-tags-structure
 */
static VALUE rb_KernAux_Multiboot2_Info_total_size(VALUE self);

/**
 * Return the reserved field of the Multiboot 2 information.
 *
 * @return [nil, Integer]
 *
 * @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Basic-tags-structure
 */
static VALUE rb_KernAux_Multiboot2_Info_reserved(VALUE self);



/*************************
 * Extension initializer *
 *************************/

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
    rb_define_method(rb_KernAux_Multiboot2_Header, "enough?",
                     rb_KernAux_Multiboot2_Header_enoughQN, 0);
    rb_define_method(rb_KernAux_Multiboot2_Header, "valid?",
                     rb_KernAux_Multiboot2_Header_validQN, 0);
    rb_define_method(rb_KernAux_Multiboot2_Header, "magic",
                     rb_KernAux_Multiboot2_Header_magic, 0);
    rb_define_method(rb_KernAux_Multiboot2_Header, "arch",
                     rb_KernAux_Multiboot2_Header_arch, 0);
    rb_define_method(rb_KernAux_Multiboot2_Header, "total_size",
                     rb_KernAux_Multiboot2_Header_total_size, 0);
    rb_define_method(rb_KernAux_Multiboot2_Header, "checksum",
                     rb_KernAux_Multiboot2_Header_checksum, 0);

    // KernAux::Multiboot2::Info
    rb_gc_register_mark_object(rb_KernAux_Multiboot2_Info =
        rb_define_class_under(
            rb_KernAux_Multiboot2, "Info", rb_KernAux_Multiboot2_Struct));
    rb_define_method(rb_KernAux_Multiboot2_Info, "enough?",
                     rb_KernAux_Multiboot2_Info_enoughQN, 0);
    rb_define_method(rb_KernAux_Multiboot2_Info, "valid?",
                     rb_KernAux_Multiboot2_Info_validQN, 0);
    rb_define_method(rb_KernAux_Multiboot2_Info, "total_size",
                     rb_KernAux_Multiboot2_Info_total_size, 0);
    rb_define_method(rb_KernAux_Multiboot2_Info, "reserved",
                     rb_KernAux_Multiboot2_Info_reserved, 0);
}



/*******************************
 * KernAux::Multiboot2::Header *
 *******************************/

// KernAux::Multiboot2::Header#enough?
VALUE rb_KernAux_Multiboot2_Header_enoughQN(VALUE self)
{
    VALUE data = rb_ivar_get(self, rb_intern("@data"));
    EXTRACT_BASE_PTR(Header, multiboot2_header, data, Qfalse);
    (void)multiboot2_header; // unused
    return Qtrue;
}

// KernAux::Multiboot2::Header#valid?
VALUE rb_KernAux_Multiboot2_Header_validQN(VALUE self)
{
    VALUE data = rb_ivar_get(self, rb_intern("@data"));
    EXTRACT_BASE_PTR(Header, multiboot2_header, data, Qfalse);
    ENSURE_WHOLE_SIZE(multiboot2_header, Qfalse);

    if (KernAux_Multiboot2_Header_is_valid(multiboot2_header)) {
        return Qtrue;
    } else {
        return Qfalse;
    }
}

// KernAux::Multiboot2::Header#magic
VALUE rb_KernAux_Multiboot2_Header_magic(VALUE self)
{
    VALUE data = rb_ivar_get(self, rb_intern("@data"));
    EXTRACT_BASE_PTR(Header, multiboot2_header, data, Qnil);
    KERNAUX_CAST_CONST(unsigned long, magic, multiboot2_header->magic);
    return ULONG2NUM(magic);
}

// KernAux::Multiboot2::Header#arch
VALUE rb_KernAux_Multiboot2_Header_arch(VALUE self)
{
    VALUE data = rb_ivar_get(self, rb_intern("@data"));
    EXTRACT_BASE_PTR(Header, multiboot2_header, data, Qnil);
    KERNAUX_CAST_CONST(unsigned long, arch, multiboot2_header->arch);
    return ULONG2NUM(arch);
}

// KernAux::Multiboot2::Header#total_size
VALUE rb_KernAux_Multiboot2_Header_total_size(VALUE self)
{
    VALUE data = rb_ivar_get(self, rb_intern("@data"));
    EXTRACT_BASE_PTR(Header, multiboot2_header, data, Qnil);
    KERNAUX_CAST_CONST(unsigned long, total_size,
                       multiboot2_header->total_size);
    return ULONG2NUM(total_size);
}

// KernAux::Multiboot2::Header#checksum
VALUE rb_KernAux_Multiboot2_Header_checksum(VALUE self)
{
    VALUE data = rb_ivar_get(self, rb_intern("@data"));
    EXTRACT_BASE_PTR(Header, multiboot2_header, data, Qnil);
    KERNAUX_CAST_CONST(unsigned long, checksum, multiboot2_header->checksum);
    return ULONG2NUM(checksum);
}

/*****************************
 * KernAux::Multiboot2::Info *
 *****************************/

// KernAux::Multiboot2::Info#enough?
VALUE rb_KernAux_Multiboot2_Info_enoughQN(VALUE self)
{
    VALUE data = rb_ivar_get(self, rb_intern("@data"));
    EXTRACT_BASE_PTR(Info, multiboot2_info, data, Qfalse);
    (void)multiboot2_info; // unused
    return Qtrue;
}

// KernAux::Multiboot2::Info#valid?
VALUE rb_KernAux_Multiboot2_Info_validQN(VALUE self)
{
    VALUE data = rb_ivar_get(self, rb_intern("@data"));
    EXTRACT_BASE_PTR(Info, multiboot2_info, data, Qfalse);
    ENSURE_WHOLE_SIZE(multiboot2_info, Qfalse);

    if (KernAux_Multiboot2_Info_is_valid(multiboot2_info)) {
        return Qtrue;
    } else {
        return Qfalse;
    }
}

// KernAux::Multiboot2::Info#total_size
VALUE rb_KernAux_Multiboot2_Info_total_size(VALUE self)
{
    VALUE data = rb_ivar_get(self, rb_intern("@data"));
    EXTRACT_BASE_PTR(Info, multiboot2_info, data, Qnil);
    KERNAUX_CAST_CONST(unsigned long, total_size, multiboot2_info->total_size);
    return ULONG2NUM(total_size);
}

// KernAux::Multiboot2::Info#reserved
VALUE rb_KernAux_Multiboot2_Info_reserved(VALUE self)
{
    VALUE data = rb_ivar_get(self, rb_intern("@data"));
    EXTRACT_BASE_PTR(Info, multiboot2_info, data, Qnil);
    KERNAUX_CAST_CONST(unsigned long, reserved, multiboot2_info->reserved);
    return ULONG2NUM(reserved);
}

#endif
