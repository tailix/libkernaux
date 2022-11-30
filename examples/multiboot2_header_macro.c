#include <kernaux/macro.h>
#include <kernaux/multiboot2.h>
#include <kernaux/multiboot2/header_macro.h>

#include <assert.h>

#include <kernaux/macro/packing_start.run>

__attribute__((aligned(KERNAUX_MULTIBOOT2_HEADER_ALIGN)))
const struct {
    struct KernAux_Multiboot2_Header header;
    // Here is where the macros are used:
    KERNAUX_MULTIBOOT2_HFIELDS_INFO_REQ_EVEN(tag_info_req_even, 2)
    KERNAUX_MULTIBOOT2_HFIELDS_INFO_REQ_ODD(tag_info_req_odd, 1, _align1)
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
    .tag_info_req_even = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_HTAG_INFO_REQ,
                .flags = KERNAUX_MULTIBOOT2_HTAG_BASE_FLAG_OPTIONAL,
                .size = sizeof(multiboot2_header.tag_info_req_even),
            },
        },
        .mbi_tag_types = {
            KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE,
            KERNAUX_MULTIBOOT2_ITAG_BOOT_LOADER_NAME,
        },
    },
    .tag_info_req_odd = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_HTAG_INFO_REQ,
                .flags = KERNAUX_MULTIBOOT2_HTAG_BASE_FLAG_OPTIONAL,
                .size = sizeof(multiboot2_header.tag_info_req_odd),
            },
        },
        .mbi_tag_types = {
            KERNAUX_MULTIBOOT2_ITAG_ELF_SYMBOLS,
        },
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
