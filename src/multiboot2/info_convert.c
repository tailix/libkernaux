#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "../assert.h"

#include <kernaux/generic/malloc.h>
#include <kernaux/macro.h>
#include <kernaux/memmap.h>
#include <kernaux/multiboot2.h>

#include <stddef.h>

#ifdef WITH_MEMMAP
KernAux_Memmap_Builder KernAux_Multiboot2_Info_to_memmap_builder(
    const struct KernAux_Multiboot2_Info *const multiboot2_info,
    const KernAux_Malloc malloc
) {
    KERNAUX_NOTNULL(multiboot2_info);
    KERNAUX_NOTNULL(malloc);

    if (!KernAux_Multiboot2_Info_is_valid(multiboot2_info)) return NULL;

    const struct KernAux_Multiboot2_ITag_MemoryMap *const memory_map_tag =
        (const struct KernAux_Multiboot2_ITag_MemoryMap*)
        KernAux_Multiboot2_Info_first_tag_with_type(
            multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP
        );
    if (!memory_map_tag) return NULL;

    const void *const data = KERNAUX_MULTIBOOT2_DATA(memory_map_tag);
    size_t data_size = memory_map_tag->base.size - sizeof(*memory_map_tag);
    const void *const data_end = ((const char*)data) + data_size;

    if (memory_map_tag->entry_size <
        sizeof(struct KernAux_Multiboot2_ITag_MemoryMap_EntryBase))
    {
        return NULL;
    }

    KernAux_Memmap_Builder builder =
        KernAux_Memmap_Builder_new(malloc);
    if (!builder) return NULL;

    for (
        const struct KernAux_Multiboot2_ITag_MemoryMap_EntryBase *entry = data;
        (const char*)entry < (const char*)data_end;
        entry =
            (const struct KernAux_Multiboot2_ITag_MemoryMap_EntryBase*)
            (((const char*)entry) + memory_map_tag->entry_size)
    ) {
        const void *const node = KernAux_Memmap_Builder_add(
            builder,
            NULL,
            entry->base_addr,
            entry->length,
            KernAux_Multiboot2_ITag_MemoryMap_EntryBase_Type_to_str(
                entry->type
            )
        );

        if (!node) {
            KernAux_Memmap_Builder_finish_and_free(builder);
            return NULL;
        }
    }

    return builder;
}
#endif
