#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/multiboot2.h>

#include <stddef.h>

static const char *KernAux_Multiboot2_HTag_to_str(
    enum KernAux_Multiboot2_HTag tag_type
);

const char *KernAux_Multiboot2_HTag_to_str(
    enum KernAux_Multiboot2_HTag tag_type
) {
    switch (tag_type) {
    case KERNAUX_MULTIBOOT2_HTAG_NONE:
        return "none";
    case KERNAUX_MULTIBOOT2_HTAG_INFO_REQ:
        return "information request";
    case KERNAUX_MULTIBOOT2_HTAG_ADDR:
        return "address";
    case KERNAUX_MULTIBOOT2_HTAG_ENTRY_ADDR:
        return "entry address";
    case KERNAUX_MULTIBOOT2_HTAG_FLAGS:
        return "flags";
    case KERNAUX_MULTIBOOT2_HTAG_FRAMEBUFFER:
        return "framebuffer";
    case KERNAUX_MULTIBOOT2_HTAG_MODULE_ALIGN:
        return "module alignment";
    case KERNAUX_MULTIBOOT2_HTAG_EFI_BOOT_SERVICES:
        return "EFI boot services";
    case KERNAUX_MULTIBOOT2_HTAG_EFI_I386_ENTRY_ADDR:
        return "EFI i386 entry address";
    case KERNAUX_MULTIBOOT2_HTAG_EFI_AMD64_ENTRY_ADDR:
        return "EFI AMD64 entry address";
    case KERNAUX_MULTIBOOT2_HTAG_RELOCATABLE_HEADER:
        return "relocatable header";
    default:
        return NULL;
    }
}

void KernAux_Multiboot2_Header_print(
    const struct KernAux_Multiboot2_Header *const multiboot2_header,
    void (*const printf)(const char *format, ...) __attribute__((format(printf, 1, 2)))
) {
    printf("Multiboot 2 header\n");
    printf("  magic: %u\n", multiboot2_header->magic);
    printf("  arch: %u\n", multiboot2_header->arch);
    printf("  size: %u\n", multiboot2_header->total_size);
    printf("  checksum: %u\n", multiboot2_header->checksum);

    // TODO: write this
}
