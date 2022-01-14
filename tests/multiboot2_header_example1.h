static const struct {
    struct KernAux_Multiboot2_Header multiboot2_header;
    struct KernAux_Multiboot2_HTag_None tag_none;
} multiboot2_header_example1 = {
    .multiboot2_header = {
        .magic = KERNAUX_MULTIBOOT2_HEADER_MAGIC,
        .arch = KERNAUX_MULTIBOOT2_HEADER_ARCH_MIPS32,
        .total_size = sizeof(multiboot2_header_example1),
        .checksum = KERNAUX_MULTIBOOT2_HEADER_CHECKSUM(
            KERNAUX_MULTIBOOT2_HEADER_ARCH_MIPS32,
            sizeof(multiboot2_header_example1)
        ),
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_HTAG_NONE,
            .flags = 0,
            .size = sizeof(multiboot2_header_example1.tag_none),
        },
    },
};
