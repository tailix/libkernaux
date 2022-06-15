#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/memmap.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define MEMMAP (*memmap)

void KernAux_MemMap_init(KernAux_MemMap memmap, const size_t memory_size)
{
    MEMMAP.is_finished = false;
    MEMMAP.memory_size = memory_size;
    MEMMAP.entries_count = 0;
    memset(MEMMAP.entries, 0, sizeof(MEMMAP.entries));
}

bool KernAux_MemMap_add_entry(
    KernAux_MemMap memmap,
    const bool is_available,
    const char *const tag,
    const size_t start,
    const size_t size
) {
    if (MEMMAP.is_finished) {
        KERNAUX_PANIC("memmap is finished");
        return false;
    }

    if (MEMMAP.entries_count >= KERNAUX_MEMMAP_ENTRIES_MAX) {
        KERNAUX_PANIC("memmap is full");
        return false;
    }

    if (SIZE_MAX - start < size) {
        KERNAUX_PANIC("memmap entry limit is too high");
        return false;
    }

    memset(MEMMAP.entries[MEMMAP.entries_count], 0, sizeof(MEMMAP.entries[MEMMAP.entries_count]));
    const size_t index = MEMMAP.entries_count++;

    MEMMAP.entries[index]->is_available = is_available;
    if (tag) {
        memset (MEMMAP.entries[index]->tag, 0,   KERNAUX_MEMMAP_ENTRY_TAG_SIZE_MAX);
        strncpy(MEMMAP.entries[index]->tag, tag, KERNAUX_MEMMAP_ENTRY_TAG_SLEN_MAX);
    }
    MEMMAP.entries[index]->start = start;
    MEMMAP.entries[index]->size  = size;
    MEMMAP.entries[index]->end   = start + size - 1;
    MEMMAP.entries[index]->limit = start + size;

    return true;
}
