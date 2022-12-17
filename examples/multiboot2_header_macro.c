#include <kernaux/multiboot2.h>

#include <assert.h>

#include <kernaux/macro/packing_start.run>

KERNAUX_ALIGNED(KERNAUX_MULTIBOOT2_HEADER_ALIGN)
static const struct {
    struct KernAux_Multiboot2_Header header;
    // This macro may be used to create the tag
    // of type "KernAux_Multiboot2_HTag_InfoReq"
    // when the number of requested information
    // tag types is even (n % 2 == 0).
    //
    // cppcheck-suppress unknownMacro
    KERNAUX_MULTIBOOT2_HFIELDS_INFO_REQ_EVEN(
        // This is the name of the structure field.
        tag_info_req_even,
        // This is the number of requested information tag types.
        // IT MUST BE EVEN!!! (n % 2 == 0)
        2
    )
    // This macro may be used to create the tag
    // of type "KernAux_Multiboot2_HTag_InfoReq"
    // when the number of requested information
    // tag types is odd (n % 2 == 1).
    //
    // cppcheck-suppress unknownMacro
    KERNAUX_MULTIBOOT2_HFIELDS_INFO_REQ_ODD(
        // This is the name of the structure field.
        tag_info_req_odd,
        // This is the number of requested information tag types.
        // IT MUST BE ODD!!! (n % 2 == 1)
        1,
        // This is the name of the additional structure field
        // which will be used to align the following tags properly.
        // You may keep it unassigned.
        _align1
    )
    // This macro may be used for all other header tag types.
    //
    // cppcheck-suppress unknownMacro
    KERNAUX_MULTIBOOT2_HFIELDS_COMMON(
        // This is the name of the structure field.
        tag_none,
        // This is the type of the structure field
        // without the "KernAux_Multiboot2_HTag_" prefix.
        None
    )
}
KERNAUX_PACKED
multiboot2_header = {
    .header = {
        .magic = KERNAUX_MULTIBOOT2_HEADER_MAGIC,
        .arch = KERNAUX_MULTIBOOT2_HEADER_ARCH_I386,
        .total_size = sizeof(multiboot2_header),
        // This macro helps to calculate the checksum.
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
