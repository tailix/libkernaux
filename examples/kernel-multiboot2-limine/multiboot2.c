#include <kernaux/multiboot2.h>

__attribute__((section(".multiboot"), used))
__attribute__((aligned(4)))
const struct {
    struct KernAux_Multiboot2_Header multiboot2_header;
    struct KernAux_Multiboot2_HTag_None tag_none;
} multiboot2_header = {
    .multiboot2_header = {
        .magic = KERNAUX_MULTIBOOT2_HEADER_MAGIC,
        .arch = KERNAUX_MULTIBOOT2_ARCH_NONE,
        .total_size = sizeof(multiboot2_header),
        .checksum = KERNAUX_MULTIBOOT2_HEADER_CHECKSUM(
            KERNAUX_MULTIBOOT2_ARCH_NONE,
            sizeof(multiboot2_header)
        ),
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_HTAG_NONE,
            .flags = 0,
            .size = sizeof(multiboot2_header.tag_none),
        },
    },
};
