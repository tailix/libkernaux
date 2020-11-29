#include <kernaux/multiboot2.h>

const char *KernAux_Multiboot2_boot_cmd_line(
    const struct KernAux_Multiboot2 *const multiboot2
) {
    const struct KernAux_Multiboot2_TagBase *tag_base =
        (struct KernAux_Multiboot2_TagBase*)multiboot2->data;

    while ((void*)tag_base < (void*)multiboot2 + multiboot2->total_size) {
        if (!KernAux_Multiboot2_TagBase_is_valid(tag_base)) {
            return 0;
        }

        if (tag_base->type == KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_CMD_LINE) {
            const struct KernAux_Multiboot2_Tag_BootCmdLine *const tag =
                (struct KernAux_Multiboot2_Tag_BootCmdLine*)tag_base;

            return tag->cmdline;
        }

        tag_base = (struct KernAux_Multiboot2_TagBase*)(
            (void*)tag_base + ((tag_base->size + 7) & ~7)
        );
    }

    return 0;
}
