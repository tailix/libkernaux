#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/multiboot2.h>

#ifdef WITH_MEMMAP
#include <kernaux/memmap.h>
#endif

#include <stdbool.h>

#ifdef WITH_MEMMAP
// TODO: implement this
bool KernAux_Multiboot2_Info_to_memmap(
    const struct KernAux_Multiboot2_Info *multiboot2_info,
    KernAux_MemMap memmap
) {
    KERNAUX_ASSERT(multiboot2_info);

    KernAux_MemMap_init(memmap, 0);
    if (!KernAux_Multiboot2_Info_is_valid(multiboot2_info)) return false;

    const struct KernAux_Multiboot2_ITagBase *const basic_memory_info_tag_base =
        KernAux_Multiboot2_Info_first_tag_with_type(
            multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO
        );
    const struct KernAux_Multiboot2_ITagBase *const memory_map_tag_base =
        KernAux_Multiboot2_Info_first_tag_with_type(
            multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP
        );

    if (basic_memory_info_tag_base == NULL || memory_map_tag_base == NULL) {
        return false;
    }

    const struct KernAux_Multiboot2_ITag_BasicMemoryInfo *const
        basic_memory_info_tag =
        (const struct KernAux_Multiboot2_ITag_BasicMemoryInfo*)
        basic_memory_info_tag_base;
    const struct KernAux_Multiboot2_ITag_MemoryMap *const
        memory_map_tag =
        (const struct KernAux_Multiboot2_ITag_MemoryMap*)
        memory_map_tag_base;

    (void)basic_memory_info_tag;
    (void)memory_map_tag;

    return false;
}
#endif
