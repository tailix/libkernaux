#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/multiboot2.h>

#include <stddef.h>
#include <stdint.h>

void KernAux_Multiboot2_Header_print(
    const struct KernAux_Multiboot2_Header *const multiboot2_header,
    void (*const printf)(const char *format, ...) __attribute__((format(printf, 1, 2)))
) {
    printf("Multiboot 2 header\n");
    printf("  magic: %u\n", multiboot2_header->magic);
    printf(
        "  arch: %u (%s)\n",
        multiboot2_header->arch,
        KernAux_Multiboot2_Header_Arch_to_str(multiboot2_header->arch)
    );
    printf("  size: %u\n", multiboot2_header->total_size);
    printf("  checksum: %u\n", multiboot2_header->checksum);

    const struct KernAux_Multiboot2_HTagBase *tag_base =
        (struct KernAux_Multiboot2_HTagBase*)
        KERNAUX_MULTIBOOT2_DATA(multiboot2_header);

    while (tag_base <
           (struct KernAux_Multiboot2_HTagBase*)
           ((uint8_t*)multiboot2_header + multiboot2_header->total_size))
    {
        if (!KernAux_Multiboot2_HTagBase_is_valid(tag_base)) return;

        KernAux_Multiboot2_HTagBase_print(tag_base, printf);

        tag_base = KERNAUX_MULTIBOOT2_HTAG_NEXT(tag_base);
    }
}

void KernAux_Multiboot2_HTagBase_print(
    const struct KernAux_Multiboot2_HTagBase *const tag_base,
    void (*const printf)(const char *format, ...) __attribute__((format(printf, 1, 2)))
) {
    if (!KernAux_Multiboot2_HTagBase_is_valid(tag_base)) return;

    printf("Multiboot 2 header tag\n");

    printf(
        "  type: %u (%s)\n",
        tag_base->type,
        KernAux_Multiboot2_HTag_to_str(tag_base->type)
    );

    printf("  flags: %u\n", tag_base->flags);
    printf("  size: %u\n", tag_base->size);

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
