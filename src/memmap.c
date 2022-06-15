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

struct KernAux_MemMap KernAux_MemMap_create(const size_t memory_size)
{
    struct KernAux_MemMap memmap;
    KernAux_MemMap_init(&memmap, memory_size);
    return memmap;
}

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

    if (MEMMAP.entries_count >= KERNAUX_MEMMAP_ENTRIES_MAX) return false;
    if (SIZE_MAX - start < size) return false;

    memset(&MEMMAP.entries[MEMMAP.entries_count], 0, sizeof(MEMMAP.entries[MEMMAP.entries_count]));
    const size_t index = MEMMAP.entries_count++;

    MEMMAP.entries[index].is_available = is_available;
    if (tag) {
        memset (MEMMAP.entries[index].tag, 0,   KERNAUX_MEMMAP_ENTRY_TAG_SIZE_MAX);
        strncpy(MEMMAP.entries[index].tag, tag, KERNAUX_MEMMAP_ENTRY_TAG_SLEN_MAX);
    }
    MEMMAP.entries[index].start = start;
    MEMMAP.entries[index].size  = size;
    MEMMAP.entries[index].end   = start + size - 1;
    MEMMAP.entries[index].limit = start + size;

    return true;
}

bool KernAux_MemMap_finish(KernAux_MemMap memmap)
{
    if (MEMMAP.is_finished) {
        KERNAUX_PANIC("memmap is finished");
        return false;
    }

    if ((MEMMAP.entries_count == 0 && MEMMAP.memory_size != 0) ||
        MEMMAP.entries_count > KERNAUX_MEMMAP_ENTRIES_MAX      ||
        MEMMAP.entries[0].start != 0                           ||
        MEMMAP.entries[MEMMAP.entries_count - 1].limit != MEMMAP.memory_size)
    {
        return false;
    }

    // At first, let's validate the individual entries.
    for (size_t index = 0; index < MEMMAP.entries_count; ++index) {
        if (SIZE_MAX - MEMMAP.entries[index].start <
            MEMMAP.entries[index].size
            ||
            MEMMAP.entries[index].end !=
            MEMMAP.entries[index].start + MEMMAP.entries[index].size - 1
            ||
            MEMMAP.entries[index].limit !=
            MEMMAP.entries[index].start + MEMMAP.entries[index].size)
        {
            return false;
        }
    }

    // TODO: Next, let's sort the entries.

    // Finally, let's validate that the entries fit each other properly.
    for (size_t index = 1; index < MEMMAP.entries_count; ++index) {
        if (MEMMAP.entries[index - 1].limit != MEMMAP.entries[index].start) {
            return false;
        }
    }

    return MEMMAP.is_finished = true;
}

KernAux_MemMap_Entry
KernAux_MemMap_entry_by_index(KernAux_MemMap memmap, const size_t index)
{
    if (!MEMMAP.is_finished) {
        KERNAUX_PANIC("memmap is not finished");
        return NULL;
    }

    if (index >= MEMMAP.entries_count) return NULL;
    return &MEMMAP.entries[index];
}

KernAux_MemMap_Entry
KernAux_MemMap_entry_by_start(KernAux_MemMap memmap, const size_t start)
{
    if (!MEMMAP.is_finished) {
        KERNAUX_PANIC("memmap is not finished");
        return NULL;
    }

    for (size_t index = 0; index < MEMMAP.entries_count; ++index) {
        if (MEMMAP.entries[index].start == start) return &MEMMAP.entries[index];
    }

    return NULL;
}
