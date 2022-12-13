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
    KERNAUX_NOTNULL(multiboot2_info);

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

    // FIXME: Basic memory info tag may not be provided by some boot loaders on
    // EFI platforms if EFI boot services are enabled and available for the
    // loaded image (EFI boot services not terminated tag exists in Multiboot2
    // information structure).
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

    // FIXME: The value returned for upper memory is maximally the address of
    // the first upper memory hole minus 1 megabyte. It is not guaranteed to be
    // this value.
    const size_t memory_size = (size_t)basic_memory_info_tag->mem_upper * 1024;
    KernAux_MemMap_init(memmap, memory_size);

    (void)memory_map_tag;

    return false;
}
#endif
