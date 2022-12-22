#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "../assert.h"

#include <kernaux/multiboot2.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

bool KernAux_Multiboot2_Header_is_valid(
    const struct KernAux_Multiboot2_Header *const multiboot2_header
) {
    KERNAUX_NOTNULL(multiboot2_header);

    if (multiboot2_header->magic != KERNAUX_MULTIBOOT2_HEADER_MAGIC) {
        return false;
    }

    if (multiboot2_header->arch != KERNAUX_MULTIBOOT2_HEADER_ARCH_I386 &&
        multiboot2_header->arch != KERNAUX_MULTIBOOT2_HEADER_ARCH_MIPS32)
    {
        return false;
    }

    if (multiboot2_header->total_size <
        sizeof(struct KernAux_Multiboot2_Header) +
        sizeof(struct KernAux_Multiboot2_HTag_None))
    {
        return false;
    }

    if (multiboot2_header->total_size % KERNAUX_MULTIBOOT2_TAG_ALIGN != 0) {
        return false;
    }

    if (multiboot2_header->checksum !=
        KERNAUX_MULTIBOOT2_HEADER_CHECKSUM(
            multiboot2_header->arch,
            multiboot2_header->total_size
        )
    ) {
        return false;
    }

    const struct KernAux_Multiboot2_HTagBase *tag_base =
        (struct KernAux_Multiboot2_HTagBase*)
        KERNAUX_MULTIBOOT2_DATA(multiboot2_header);

    const struct KernAux_Multiboot2_HTagBase *none_tag_base = NULL;

    while (tag_base <
           (struct KernAux_Multiboot2_HTagBase*)
           ((uint8_t*)multiboot2_header + multiboot2_header->total_size))
    {
        if (!KernAux_Multiboot2_HTagBase_is_valid(tag_base)) return false;

        if (tag_base->type == KERNAUX_MULTIBOOT2_HTAG_NONE &&
            none_tag_base == NULL
        ) {
            none_tag_base = tag_base;
        }

        tag_base = KERNAUX_MULTIBOOT2_HTAG_NEXT(tag_base);
    }

    if (tag_base !=
        (struct KernAux_Multiboot2_HTagBase*)
        ((uint8_t*)multiboot2_header + multiboot2_header->total_size))
    {
        return false;
    }

    if (none_tag_base !=
        (struct KernAux_Multiboot2_HTagBase*)
        ((uint8_t*)tag_base -
         sizeof(struct KernAux_Multiboot2_HTag_None)))
    {
        return false;
    }

    return true;
}

bool KernAux_Multiboot2_HTagBase_is_valid(
    const struct KernAux_Multiboot2_HTagBase *tag_base
) {
    KERNAUX_NOTNULL(tag_base);

    switch (tag_base->type) {
    case KERNAUX_MULTIBOOT2_HTAG_NONE:
        return KernAux_Multiboot2_HTag_None_is_valid(
            (struct KernAux_Multiboot2_HTag_None*)tag_base
        );
    case KERNAUX_MULTIBOOT2_HTAG_INFO_REQ:
        return KernAux_Multiboot2_HTag_InfoReq_is_valid(
            (struct KernAux_Multiboot2_HTag_InfoReq*)tag_base
        );
    case KERNAUX_MULTIBOOT2_HTAG_ADDR:
        return KernAux_Multiboot2_HTag_Addr_is_valid(
            (struct KernAux_Multiboot2_HTag_Addr*)tag_base
        );
    case KERNAUX_MULTIBOOT2_HTAG_ENTRY_ADDR:
        return KernAux_Multiboot2_HTag_EntryAddr_is_valid(
            (struct KernAux_Multiboot2_HTag_EntryAddr*)tag_base
        );
    case KERNAUX_MULTIBOOT2_HTAG_FLAGS:
        return KernAux_Multiboot2_HTag_Flags_is_valid(
            (struct KernAux_Multiboot2_HTag_Flags*)tag_base
        );
    case KERNAUX_MULTIBOOT2_HTAG_FRAMEBUFFER:
        return KernAux_Multiboot2_HTag_Framebuffer_is_valid(
            (struct KernAux_Multiboot2_HTag_Framebuffer*)tag_base
        );
    case KERNAUX_MULTIBOOT2_HTAG_MODULE_ALIGN:
        return KernAux_Multiboot2_HTag_ModuleAlign_is_valid(
            (struct KernAux_Multiboot2_HTag_ModuleAlign*)tag_base
        );
    case KERNAUX_MULTIBOOT2_HTAG_EFI_BOOT_SERVICES:
        return KernAux_Multiboot2_HTag_EFIBootServices_is_valid(
            (struct KernAux_Multiboot2_HTag_EFIBootServices*)tag_base
        );
    case KERNAUX_MULTIBOOT2_HTAG_EFI_I386_ENTRY_ADDR:
        return KernAux_Multiboot2_HTag_EFII386EntryAddr_is_valid(
            (struct KernAux_Multiboot2_HTag_EFII386EntryAddr*)tag_base
        );
    case KERNAUX_MULTIBOOT2_HTAG_EFI_AMD64_ENTRY_ADDR:
        return KernAux_Multiboot2_HTag_EFIAmd64EntryAddr_is_valid(
            (struct KernAux_Multiboot2_HTag_EFIAmd64EntryAddr*)tag_base
        );
    case KERNAUX_MULTIBOOT2_HTAG_RELOCATABLE_HEADER:
        return KernAux_Multiboot2_HTag_RelocatableHeader_is_valid(
            (struct KernAux_Multiboot2_HTag_RelocatableHeader*)tag_base
        );
    default:
        return false;
    }
}

bool KernAux_Multiboot2_HTag_None_is_valid(
    const struct KernAux_Multiboot2_HTag_None *tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_HTAG_NONE &&
        tag->base.size == 8
    );
}

bool KernAux_Multiboot2_HTag_InfoReq_is_valid(
    const struct KernAux_Multiboot2_HTag_InfoReq *tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_HTAG_INFO_REQ &&
        tag->base.size > 8 &&
        tag->base.size % 4 == 0
    );
}

bool KernAux_Multiboot2_HTag_Addr_is_valid(
    const struct KernAux_Multiboot2_HTag_Addr *tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_HTAG_ADDR &&
        tag->base.size == 24
    );
}

bool KernAux_Multiboot2_HTag_EntryAddr_is_valid(
    const struct KernAux_Multiboot2_HTag_EntryAddr *tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_HTAG_ENTRY_ADDR &&
        tag->base.size == 12
    );
}

bool KernAux_Multiboot2_HTag_Flags_is_valid(
    const struct KernAux_Multiboot2_HTag_Flags *tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_HTAG_FLAGS &&
        tag->base.size == 12
    );
}

bool KernAux_Multiboot2_HTag_Framebuffer_is_valid(
    const struct KernAux_Multiboot2_HTag_Framebuffer *tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_HTAG_FRAMEBUFFER &&
        tag->base.size == 20
    );
}

bool KernAux_Multiboot2_HTag_ModuleAlign_is_valid(
    const struct KernAux_Multiboot2_HTag_ModuleAlign *tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_HTAG_MODULE_ALIGN &&
        tag->base.size == 8
    );
}

bool KernAux_Multiboot2_HTag_EFIBootServices_is_valid(
    const struct KernAux_Multiboot2_HTag_EFIBootServices *tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_HTAG_EFI_BOOT_SERVICES &&
        tag->base.size == 8
    );
}

bool KernAux_Multiboot2_HTag_EFII386EntryAddr_is_valid(
    const struct KernAux_Multiboot2_HTag_EFII386EntryAddr *tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_HTAG_EFI_I386_ENTRY_ADDR &&
        tag->base.size == 12
    );
}

bool KernAux_Multiboot2_HTag_EFIAmd64EntryAddr_is_valid(
    const struct KernAux_Multiboot2_HTag_EFIAmd64EntryAddr *tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_HTAG_EFI_AMD64_ENTRY_ADDR &&
        tag->base.size == 12
    );
}

bool KernAux_Multiboot2_HTag_RelocatableHeader_is_valid(
    const struct KernAux_Multiboot2_HTag_RelocatableHeader *tag
) {
    KERNAUX_NOTNULL(tag);

    if (!(
        tag->base.type == KERNAUX_MULTIBOOT2_HTAG_RELOCATABLE_HEADER &&
        tag->base.size == 24 &&
        tag->min_addr <= tag->max_addr
    )) {
        return false;
    }

    switch (tag->preference) {
    case KERNAUX_MULTIBOOT2_HTAG_RELOCATABLE_HEADER_PREFERENCE_NONE:    break;
    case KERNAUX_MULTIBOOT2_HTAG_RELOCATABLE_HEADER_PREFERENCE_LOWEST:  break;
    case KERNAUX_MULTIBOOT2_HTAG_RELOCATABLE_HEADER_PREFERENCE_HIGHEST: break;
    default:
        return false;
    }

    return true;
}
