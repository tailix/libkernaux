#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/generic/display.h>
#include <kernaux/macro.h>
#include <kernaux/multiboot2.h>

#include <stddef.h>
#include <stdint.h>

#define PRINTLN(s) do { KernAux_Display_println(display, s); } while (0)
#define PRINTLNF(format, ...) \
    do { KernAux_Display_printlnf(display, format, __VA_ARGS__); } while (0)

#define HEADER(Type) do { \
    KERNAUX_ASSERT(tag);                                                       \
    KERNAUX_ASSERT(display);                                                   \
                                                                               \
    if (!KernAux_Multiboot2_HTag_##Type##_is_valid(tag)) return;               \
                                                                               \
    KERNAUX_CAST_CONST(unsigned long, flags, tag->base.flags);                 \
    KERNAUX_CAST_CONST(unsigned long, size,  tag->base.size);                  \
                                                                               \
    PRINTLN("Multiboot 2 header tag");                                         \
    PRINTLNF("  type: %u (%s)",                                                \
        tag->base.type,                                                        \
        KernAux_Multiboot2_HTag_to_str(tag->base.type)                         \
    );                                                                         \
    PRINTLNF("  flags: %lu", flags);                                           \
    PRINTLNF("  size: %lu", size);                                             \
} while (0)

void KernAux_Multiboot2_Header_print(
    const struct KernAux_Multiboot2_Header *const multiboot2_header,
    const KernAux_Display display
) {
    KERNAUX_ASSERT(multiboot2_header);
    KERNAUX_ASSERT(display);

    KERNAUX_CAST_CONST(unsigned long, magic,      multiboot2_header->magic);
    KERNAUX_CAST_CONST(unsigned long, total_size, multiboot2_header->total_size);
    KERNAUX_CAST_CONST(unsigned long, checksum,   multiboot2_header->checksum);

    PRINTLN("Multiboot 2 header");
    PRINTLNF("  magic: %lu", magic);
    PRINTLNF("  arch: %u (%s)",
        multiboot2_header->arch,
        KernAux_Multiboot2_Header_Arch_to_str(multiboot2_header->arch)
    );
    PRINTLNF("  size: %lu", total_size);
    PRINTLNF("  checksum: %lu", checksum);

    const struct KernAux_Multiboot2_HTagBase *tag_base =
        (struct KernAux_Multiboot2_HTagBase*)
        KERNAUX_MULTIBOOT2_DATA(multiboot2_header);

    while (tag_base <
           (struct KernAux_Multiboot2_HTagBase*)
           ((uint8_t*)multiboot2_header + multiboot2_header->total_size))
    {
        if (!KernAux_Multiboot2_HTagBase_is_valid(tag_base)) return;
        KernAux_Multiboot2_HTagBase_print(tag_base, display);
        tag_base = KERNAUX_MULTIBOOT2_HTAG_NEXT(tag_base);
    }
}

void KernAux_Multiboot2_HTagBase_print(
    const struct KernAux_Multiboot2_HTagBase *const tag_base,
    const KernAux_Display display
) {
    KERNAUX_ASSERT(tag_base);
    KERNAUX_ASSERT(display);

    switch (tag_base->type) {
    case KERNAUX_MULTIBOOT2_HTAG_NONE:
        KernAux_Multiboot2_HTag_None_print(
            (struct KernAux_Multiboot2_HTag_None*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_INFO_REQ:
        KernAux_Multiboot2_HTag_InfoReq_print(
            (struct KernAux_Multiboot2_HTag_InfoReq*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_ADDR:
        KernAux_Multiboot2_HTag_Addr_print(
            (struct KernAux_Multiboot2_HTag_Addr*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_ENTRY_ADDR:
        KernAux_Multiboot2_HTag_EntryAddr_print(
            (struct KernAux_Multiboot2_HTag_EntryAddr*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_FLAGS:
        KernAux_Multiboot2_HTag_Flags_print(
            (struct KernAux_Multiboot2_HTag_Flags*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_FRAMEBUFFER:
        KernAux_Multiboot2_HTag_Framebuffer_print(
            (struct KernAux_Multiboot2_HTag_Framebuffer*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_MODULE_ALIGN:
        KernAux_Multiboot2_HTag_ModuleAlign_print(
            (struct KernAux_Multiboot2_HTag_ModuleAlign*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_EFI_BOOT_SERVICES:
        KernAux_Multiboot2_HTag_EFIBootServices_print(
            (struct KernAux_Multiboot2_HTag_EFIBootServices*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_EFI_I386_ENTRY_ADDR:
        KernAux_Multiboot2_HTag_EFII386EntryAddr_print(
            (struct KernAux_Multiboot2_HTag_EFII386EntryAddr*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_EFI_AMD64_ENTRY_ADDR:
        KernAux_Multiboot2_HTag_EFIAmd64EntryAddr_print(
            (struct KernAux_Multiboot2_HTag_EFIAmd64EntryAddr*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_RELOCATABLE_HEADER:
        KernAux_Multiboot2_HTag_RelocatableHeader_print(
            (struct KernAux_Multiboot2_HTag_RelocatableHeader*)tag_base,
            display
        );
        break;
    }
}

void KernAux_Multiboot2_HTag_None_print(
    const struct KernAux_Multiboot2_HTag_None *const tag,
    const KernAux_Display display
) {
    HEADER(None);

    // TODO: print
}

void KernAux_Multiboot2_HTag_InfoReq_print(
    const struct KernAux_Multiboot2_HTag_InfoReq *const tag,
    const KernAux_Display display
) {
    HEADER(InfoReq);

    // TODO: print

    // TODO: Print data?
}

void KernAux_Multiboot2_HTag_Addr_print(
    const struct KernAux_Multiboot2_HTag_Addr *const tag,
    const KernAux_Display display
) {
    HEADER(Addr);

    // TODO: print
}

void KernAux_Multiboot2_HTag_EntryAddr_print(
    const struct KernAux_Multiboot2_HTag_EntryAddr *const tag,
    const KernAux_Display display
) {
    HEADER(EntryAddr);

    // TODO: print
}

void KernAux_Multiboot2_HTag_Flags_print(
    const struct KernAux_Multiboot2_HTag_Flags *const tag,
    const KernAux_Display display
) {
    HEADER(Flags);

    // TODO: print
}

void KernAux_Multiboot2_HTag_Framebuffer_print(
    const struct KernAux_Multiboot2_HTag_Framebuffer *const tag,
    const KernAux_Display display
) {
    HEADER(Framebuffer);

    // TODO: print
}

void KernAux_Multiboot2_HTag_ModuleAlign_print(
    const struct KernAux_Multiboot2_HTag_ModuleAlign *const tag,
    const KernAux_Display display
) {
    HEADER(ModuleAlign);

    // TODO: print
}

void KernAux_Multiboot2_HTag_EFIBootServices_print(
    const struct KernAux_Multiboot2_HTag_EFIBootServices *const tag,
    const KernAux_Display display
) {
    HEADER(EFIBootServices);

    // TODO: print
}

void KernAux_Multiboot2_HTag_EFII386EntryAddr_print(
    const struct KernAux_Multiboot2_HTag_EFII386EntryAddr *const tag,
    const KernAux_Display display
) {
    HEADER(EFII386EntryAddr);

    // TODO: print
}

void KernAux_Multiboot2_HTag_EFIAmd64EntryAddr_print(
    const struct KernAux_Multiboot2_HTag_EFIAmd64EntryAddr *const tag,
    const KernAux_Display display
) {
    HEADER(EFIAmd64EntryAddr);

    // TODO: print
}

void KernAux_Multiboot2_HTag_RelocatableHeader_print(
    const struct KernAux_Multiboot2_HTag_RelocatableHeader *const tag,
    const KernAux_Display display
) {
    HEADER(RelocatableHeader);

    // TODO: print
}
