#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "../assert.h"

#include <kernaux/multiboot2.h>

#include <stddef.h>
#include <stdint.h>

const struct KernAux_Multiboot2_HTagBase
*KernAux_Multiboot2_Header_first_tag_with_type(
    const struct KernAux_Multiboot2_Header *const multiboot2_header,
    const uint16_t tag_type
) {
    KERNAUX_NOTNULL(multiboot2_header);

    const struct KernAux_Multiboot2_HTagBase *tag_base =
        (struct KernAux_Multiboot2_HTagBase*)
        KERNAUX_MULTIBOOT2_DATA(multiboot2_header);

    while (tag_base <
           (struct KernAux_Multiboot2_HTagBase*)
           ((uint8_t*)multiboot2_header + multiboot2_header->total_size))
    {
        if (!KernAux_Multiboot2_HTagBase_is_valid(tag_base)) return NULL;
        if (tag_base->type == tag_type) return tag_base;

        tag_base = KERNAUX_MULTIBOOT2_HTAG_NEXT(tag_base);
    }

    return NULL;
}

const struct KernAux_Multiboot2_HTagBase
*KernAux_Multiboot2_Header_tag_with_type_after(
    const struct KernAux_Multiboot2_Header *const multiboot2_header,
    const uint16_t tag_type,
    const struct KernAux_Multiboot2_HTagBase *const after_tag
) {
    KERNAUX_NOTNULL(multiboot2_header);
    KERNAUX_NOTNULL(after_tag);

    const struct KernAux_Multiboot2_HTagBase *tag_base =
        (struct KernAux_Multiboot2_HTagBase*)
        KERNAUX_MULTIBOOT2_DATA(multiboot2_header);

    KERNAUX_ASSERT(tag_base <= after_tag);

    while (tag_base <
           (struct KernAux_Multiboot2_HTagBase*)
           ((uint8_t*)multiboot2_header + multiboot2_header->total_size))
    {
        if (!KernAux_Multiboot2_HTagBase_is_valid(tag_base)) return NULL;
        if (tag_base->type == tag_type && tag_base > after_tag) return tag_base;

        tag_base = KERNAUX_MULTIBOOT2_HTAG_NEXT(tag_base);
    }

    return NULL;
}
