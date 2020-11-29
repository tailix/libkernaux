#include <kernaux/multiboot2.h>

const struct KernAux_Multiboot2_TagBase *KernAux_Multiboot2_first_tag_with_type(
    const struct KernAux_Multiboot2 *const multiboot2,
    const enum KernAux_Multiboot2_TagType tag_type
) {
    const struct KernAux_Multiboot2_TagBase *tag_base =
        (struct KernAux_Multiboot2_TagBase*)multiboot2->data;

    while ((void*)tag_base < (void*)multiboot2 + multiboot2->total_size) {
        if (!KernAux_Multiboot2_TagBase_is_valid(tag_base)) {
            return 0;
        }

        if (tag_base->type == tag_type) {
            return tag_base;
        }

        tag_base = (struct KernAux_Multiboot2_TagBase*)(
            (void*)tag_base + ((tag_base->size + 7) & ~7)
        );
    }

    return 0;
}

const struct KernAux_Multiboot2_TagBase *KernAux_Multiboot2_tag_with_type_after(
    const struct KernAux_Multiboot2 *const multiboot2,
    const enum KernAux_Multiboot2_TagType tag_type,
    const struct KernAux_Multiboot2_TagBase *const after_tag
) {
    const struct KernAux_Multiboot2_TagBase *tag_base =
        (struct KernAux_Multiboot2_TagBase*)multiboot2->data;

    while ((void*)tag_base < (void*)multiboot2 + multiboot2->total_size) {
        if (!KernAux_Multiboot2_TagBase_is_valid(tag_base)) {
            return 0;
        }

        if (tag_base->type == tag_type && tag_base > after_tag) {
            return tag_base;
        }

        tag_base = (struct KernAux_Multiboot2_TagBase*)(
            (void*)tag_base + ((tag_base->size + 7) & ~7)
        );
    }

    return 0;
}

const char *KernAux_Multiboot2_boot_cmd_line(
    const struct KernAux_Multiboot2 *const multiboot2
) {
    const struct KernAux_Multiboot2_Tag_BootCmdLine *const tag =
        (struct KernAux_Multiboot2_Tag_BootCmdLine*)
        KernAux_Multiboot2_first_tag_with_type(
            multiboot2,
            KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_CMD_LINE
        );

    if (!tag) {
        return 0;
    }

    return tag->cmdline;
}
