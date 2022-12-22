#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "../assert.h"

#include <kernaux/multiboot2.h>

#include <stddef.h>
#include <stdint.h>

const struct KernAux_Multiboot2_ITagBase
*KernAux_Multiboot2_Info_first_tag_with_type(
    const struct KernAux_Multiboot2_Info *const multiboot2_info,
    const uint32_t tag_type
) {
    KERNAUX_NOTNULL(multiboot2_info);

    const struct KernAux_Multiboot2_ITagBase *tag_base =
        (struct KernAux_Multiboot2_ITagBase*)
        KERNAUX_MULTIBOOT2_DATA(multiboot2_info);

    while (tag_base <
           (struct KernAux_Multiboot2_ITagBase*)
           ((uint8_t*)multiboot2_info + multiboot2_info->total_size))
    {
        if (!KernAux_Multiboot2_ITagBase_is_valid(tag_base)) return NULL;
        if (tag_base->type == tag_type) return tag_base;

        tag_base = KERNAUX_MULTIBOOT2_ITAG_NEXT(tag_base);
    }

    return NULL;
}

const struct KernAux_Multiboot2_ITagBase
*KernAux_Multiboot2_Info_tag_with_type_after(
    const struct KernAux_Multiboot2_Info *const multiboot2_info,
    const uint32_t tag_type,
    const struct KernAux_Multiboot2_ITagBase *const after_tag
) {
    KERNAUX_NOTNULL(multiboot2_info);
    KERNAUX_NOTNULL(after_tag);

    const struct KernAux_Multiboot2_ITagBase *tag_base =
        (struct KernAux_Multiboot2_ITagBase*)
        KERNAUX_MULTIBOOT2_DATA(multiboot2_info);

    KERNAUX_ASSERT(tag_base <= after_tag);

    while (tag_base <
           (struct KernAux_Multiboot2_ITagBase*)
           ((uint8_t*)multiboot2_info + multiboot2_info->total_size))
    {
        if (!KernAux_Multiboot2_ITagBase_is_valid(tag_base)) return NULL;
        if (tag_base->type == tag_type && tag_base > after_tag) return tag_base;

        tag_base = KERNAUX_MULTIBOOT2_ITAG_NEXT(tag_base);
    }

    return NULL;
}

const char *KernAux_Multiboot2_Info_boot_cmd_line(
    const struct KernAux_Multiboot2_Info *const multiboot2_info
) {
    KERNAUX_NOTNULL(multiboot2_info);

    const struct KernAux_Multiboot2_ITag_BootCmdLine *const tag =
        (struct KernAux_Multiboot2_ITag_BootCmdLine*)
        KernAux_Multiboot2_Info_first_tag_with_type(
            multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE
        );

    if (!tag) return NULL;

    return (char*)KERNAUX_MULTIBOOT2_DATA(tag);
}
