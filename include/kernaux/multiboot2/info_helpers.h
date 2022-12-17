#ifndef KERNAUX_INCLUDED_MULTIBOOT2_INFO_HELPERS
#define KERNAUX_INCLUDED_MULTIBOOT2_INFO_HELPERS

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/multiboot2.h>

const struct KernAux_Multiboot2_ITagBase
*KernAux_Multiboot2_Info_first_tag_with_type(
    const struct KernAux_Multiboot2_Info *multiboot2_info,
    uint32_t tag_type
);

const struct KernAux_Multiboot2_ITagBase
*KernAux_Multiboot2_Info_tag_with_type_after(
    const struct KernAux_Multiboot2_Info *multiboot2_info,
    uint32_t tag_type,
    const struct KernAux_Multiboot2_ITagBase *after_tag
);

const char *KernAux_Multiboot2_Info_boot_cmd_line(
    const struct KernAux_Multiboot2_Info *multiboot2_info
);

#ifdef __cplusplus
}
#endif

#endif
