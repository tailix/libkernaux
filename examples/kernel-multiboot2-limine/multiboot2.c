#include <kernaux/multiboot2.h>

__attribute__((section(KERNAUX_MULTIBOOT2_HEADER_SECTION), used))
__attribute__((aligned(KERNAUX_MULTIBOOT2_HEADER_ALIGN)))
const struct {
    struct KernAux_Multiboot2_Header multiboot2_header;
    struct KernAux_Multiboot2_HTag_None tag_none;
}
__attribute__((packed))
multiboot2_header = {
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
