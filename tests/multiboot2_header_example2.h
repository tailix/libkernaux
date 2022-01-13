static const struct {
    struct KernAux_Multiboot2_Header multiboot2_header;

    struct KernAux_Multiboot2_HTag_None tag_none;
} multiboot2_header_example2 = {
    .multiboot2_header = {
        .magic = KERNAUX_MULTIBOOT2_MAGIC,
        .arch = KERNAUX_MULTIBOOT2_ARCH_I386,
        .total_size = sizeof(multiboot2_header_example2),
        .checksum = KERNAUX_MULTIBOOT2_CHECKSUM(
            KERNAUX_MULTIBOOT2_ARCH_I386,
            sizeof(multiboot2_header_example2)
        ),
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_HTAG_NONE,
            .size = sizeof(multiboot2_header_example2.tag_none),
        },
    },
};
