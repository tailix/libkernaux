#include <kernaux/macro.h>

#include <kernaux/macro/packing_start.run>

// Minimal example
static const struct {
    struct KernAux_Multiboot2_Info multiboot2_info;
    struct KernAux_Multiboot2_ITag_None tag_none;
}
KERNAUX_PACKED
multiboot2_info_example0 = {
    .multiboot2_info = {
        .total_size = sizeof(multiboot2_info_example0),
        .reserved1 = 0,
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
            .size = sizeof(multiboot2_info_example0.tag_none),
        },
    },
};

#include <kernaux/macro/packing_end.run>
