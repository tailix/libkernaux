#include <kernaux/macro/packing_start.run>

static const struct {
    struct KernAux_Multiboot2_Header multiboot2_header;

    struct KernAux_Multiboot2_HTag_Flags tag_flags1;
    uint8_t _align1[4];

    struct KernAux_Multiboot2_HTag_Flags tag_flags2;
    uint8_t _align2[4];

    struct KernAux_Multiboot2_HTag_Flags tag_flags3;
    uint8_t _align3[4];

    struct KernAux_Multiboot2_HTag_Flags tag_flags4;
    uint8_t _align4[4];

    struct KernAux_Multiboot2_HTag_None tag_none;
}
KERNAUX_PACKED
multiboot2_header_example1 = {
    .multiboot2_header = {
        .magic = KERNAUX_MULTIBOOT2_HEADER_MAGIC,
        .arch = KERNAUX_MULTIBOOT2_HEADER_ARCH_MIPS32,
        .total_size = sizeof(multiboot2_header_example1),
        .checksum = KERNAUX_MULTIBOOT2_HEADER_CHECKSUM(
            KERNAUX_MULTIBOOT2_HEADER_ARCH_MIPS32,
            sizeof(multiboot2_header_example1)
        ),
    },
    .tag_flags1 = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_HTAG_FLAGS,
            .flags = 0,
            .size = sizeof(multiboot2_header_example1.tag_flags1),
        },
        .console_flags = 0,
    },
    .tag_flags2 = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_HTAG_FLAGS,
            .flags = 0,
            .size = sizeof(multiboot2_header_example1.tag_flags2),
        },
        .console_flags = KERNAUX_MULTIBOOT2_HTAG_FLAGS_REQUIRE_CONSOLE,
    },
    .tag_flags3 = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_HTAG_FLAGS,
            .flags = 0,
            .size = sizeof(multiboot2_header_example1.tag_flags3),
        },
        .console_flags = KERNAUX_MULTIBOOT2_HTAG_FLAGS_EGA_SUPPORT,
    },
    .tag_flags4 = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_HTAG_FLAGS,
            .flags = 0,
            .size = sizeof(multiboot2_header_example1.tag_flags4),
        },
        .console_flags =
            KERNAUX_MULTIBOOT2_HTAG_FLAGS_REQUIRE_CONSOLE |
            KERNAUX_MULTIBOOT2_HTAG_FLAGS_EGA_SUPPORT,
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_HTAG_NONE,
            .flags = 0,
            .size = sizeof(multiboot2_header_example1.tag_none),
        },
    },
};

#include <kernaux/macro/packing_end.run>
