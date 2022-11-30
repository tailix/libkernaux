#include <kernaux/macro.h>
#include <kernaux/multiboot2.h>
#include <kernaux/multiboot2/header_macro.h>

#include <assert.h>

#include <kernaux/macro/packing_start.run>

__attribute__((aligned(KERNAUX_MULTIBOOT2_HEADER_ALIGN)))
const struct {
    struct KernAux_Multiboot2_Header header;
    // Here is where the macros are used:
    KERNAUX_MULTIBOOT2_HFIELDS_COMMON(tag_none, None)
}
KERNAUX_PACKED
multiboot2_header = {
    .header = {
        .magic = KERNAUX_MULTIBOOT2_HEADER_MAGIC,
        .arch = KERNAUX_MULTIBOOT2_HEADER_ARCH_I386,
        .total_size = sizeof(multiboot2_header),
        .checksum = KERNAUX_MULTIBOOT2_HEADER_CHECKSUM(
            KERNAUX_MULTIBOOT2_HEADER_ARCH_I386,
            sizeof(multiboot2_header)
        ),
    },
    .tag_none = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_HTAG_NONE,
                .flags = 0,
                .size = sizeof(multiboot2_header.tag_none),
            },
        },
    },
};

#include <kernaux/macro/packing_end.run>

void example_main()
{
    assert(KernAux_Multiboot2_Header_is_valid(&multiboot2_header.header));
}
