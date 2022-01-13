#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/multiboot2.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

bool KernAux_Multiboot2_Header_is_valid(
    const struct KernAux_Multiboot2_Header *const multiboot2_header
) {
    if (multiboot2_header->total_size <
        sizeof(struct KernAux_Multiboot2_Header) +
        sizeof(struct KernAux_Multiboot2_HTag_None))
    {
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
    // TODO: write this
    return false;
}

bool KernAux_Multiboot2_HTag_None_is_valid(
    const struct KernAux_Multiboot2_HTag_None *tag
) {
    // TODO: write this
    return false;
}

bool KernAux_Multiboot2_HTag_InfoReq_is_valid(
    const struct KernAux_Multiboot2_HTag_InfoReq *tag
) {
    // TODO: write this
    return false;
}

bool KernAux_Multiboot2_HTag_Addr_is_valid(
    const struct KernAux_Multiboot2_HTag_Addr *tag
) {
    // TODO: write this
    return false;
}

bool KernAux_Multiboot2_HTag_EntryAddr_is_valid(
    const struct KernAux_Multiboot2_HTag_EntryAddr *tag
) {
    // TODO: write this
    return false;
}

bool KernAux_Multiboot2_HTag_Flags_is_valid(
    const struct KernAux_Multiboot2_HTag_Flags *tag
) {
    // TODO: write this
    return false;
}

bool KernAux_Multiboot2_HTag_Framebuffer_is_valid(
    const struct KernAux_Multiboot2_HTag_Framebuffer *tag
) {
    // TODO: write this
    return false;
}

bool KernAux_Multiboot2_HTag_ModuleAlign_is_valid(
    const struct KernAux_Multiboot2_HTag_ModuleAlign *tag
) {
    // TODO: write this
    return false;
}

bool KernAux_Multiboot2_HTag_EFIBootServices_is_valid(
    const struct KernAux_Multiboot2_HTag_EFIBootServices *tag
) {
    // TODO: write this
    return false;
}

bool KernAux_Multiboot2_HTag_EFII386EntryAddr_is_valid(
    const struct KernAux_Multiboot2_HTag_EFII386EntryAddr *tag
) {
    // TODO: write this
    return false;
}

bool KernAux_Multiboot2_HTag_EFIAmd64EntryAddr_is_valid(
    const struct KernAux_Multiboot2_HTag_EFIAmd64EntryAddr *tag
) {
    // TODO: write this
    return false;
}

bool KernAux_Multiboot2_HTag_RelocatableHeader_is_valid(
    const struct KernAux_Multiboot2_HTag_RelocatableHeader *tag
) {
    // TODO: write this
    return false;
}
