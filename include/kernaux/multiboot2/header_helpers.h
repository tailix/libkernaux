#ifndef KERNAUX_INCLUDED_MULTIBOOT2_HEADER_HELPERS
#define KERNAUX_INCLUDED_MULTIBOOT2_HEADER_HELPERS

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/multiboot2.h>

const struct KernAux_Multiboot2_HTagBase
*KernAux_Multiboot2_Header_first_tag_with_type(
    const struct KernAux_Multiboot2_Header *multiboot2_header,
    uint16_t tag_type
);

const struct KernAux_Multiboot2_HTagBase
*KernAux_Multiboot2_Header_tag_with_type_after(
    const struct KernAux_Multiboot2_Header *multiboot2_header,
    uint16_t tag_type,
    const struct KernAux_Multiboot2_HTagBase *after_tag
);

#ifdef __cplusplus
}
#endif

#endif
