#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/generic/display.h>
#include <kernaux/multiboot2.h>

#include <stddef.h>
#include <stdint.h>

#define DISPLAY(func, ...) KernAux_Display_##func(display, __VA_ARGS__)

void KernAux_Multiboot2_Header_print(
    const struct KernAux_Multiboot2_Header *const multiboot2_header,
    const KernAux_Display display
) {
    KERNAUX_ASSERT(multiboot2_header);
    KERNAUX_ASSERT(display);

    DISPLAY(println, "Multiboot 2 header");
    DISPLAY(printlnf, "  magic: %u", multiboot2_header->magic);
    DISPLAY(printlnf,
        "  arch: %u (%s)",
        multiboot2_header->arch,
        KernAux_Multiboot2_Header_Arch_to_str(multiboot2_header->arch)
    );
    DISPLAY(printlnf, "  size: %u", multiboot2_header->total_size);
    DISPLAY(printlnf, "  checksum: %u", multiboot2_header->checksum);

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

    if (!KernAux_Multiboot2_HTagBase_is_valid(tag_base)) return;

    DISPLAY(println, "Multiboot 2 header tag");

    DISPLAY(
        printlnf,
        "  type: %u (%s)",
        tag_base->type,
        KernAux_Multiboot2_HTag_to_str(tag_base->type)
    );

    DISPLAY(printlnf, "  flags: %u", tag_base->flags);
    DISPLAY(printlnf, "  size: %u", tag_base->size);

    switch (tag_base->type) {
    case KERNAUX_MULTIBOOT2_HTAG_NONE:
        break;
    case KERNAUX_MULTIBOOT2_HTAG_INFO_REQ:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_HTAG_ADDR:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_HTAG_ENTRY_ADDR:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_HTAG_FLAGS:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_HTAG_FRAMEBUFFER:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_HTAG_MODULE_ALIGN:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_HTAG_EFI_BOOT_SERVICES:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_HTAG_EFI_I386_ENTRY_ADDR:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_HTAG_EFI_AMD64_ENTRY_ADDR:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_HTAG_RELOCATABLE_HEADER:
        {
            // TODO: print
        }
        break;
    }
}
