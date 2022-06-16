#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/memmap.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

static KernAux_MemMap memmap;

#define MEMSET memset(memmap, 0xff, sizeof(memmap))
#define MEMMAP (*memmap)

int main()
{
    {
        MEMSET;
        KernAux_MemMap_init(memmap, 0);

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 0);
        assert(MEMMAP.entries_count == 0);

        assert(KernAux_MemMap_finish(memmap));

        assert(MEMMAP.is_finished);
        assert(MEMMAP.memory_size == 0);
        assert(MEMMAP.entries_count == 0);

        assert(KernAux_MemMap_entry_by_index(memmap, 0) == NULL);
    }

    {
        MEMSET;
        KernAux_MemMap_init(memmap, 0);

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 0);
        assert(MEMMAP.entries_count == 0);

        assert(!KernAux_MemMap_add_entry(memmap, false, NULL, 0, 0));

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 0);
        assert(MEMMAP.entries_count == 0);

        assert(KernAux_MemMap_finish(memmap));

        assert(MEMMAP.is_finished);
        assert(MEMMAP.memory_size == 0);
        assert(MEMMAP.entries_count == 0);

        assert(KernAux_MemMap_entry_by_index(memmap, 0) == NULL);
    }

    {
        MEMSET;
        KernAux_MemMap_init(memmap, 1);

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 1);
        assert(MEMMAP.entries_count == 0);

        assert(KernAux_MemMap_add_entry(memmap, false, NULL, 0, 1));

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 1);
        assert(MEMMAP.entries_count == 1);

        assert(KernAux_MemMap_finish(memmap));

        assert(MEMMAP.is_finished);
        assert(MEMMAP.memory_size == 1);
        assert(MEMMAP.entries_count == 1);
        assert(MEMMAP.entries[0].is_available == false);
        assert(MEMMAP.entries[0].tag[0] == '\0');
        assert(MEMMAP.entries[0].start == 0);
        assert(MEMMAP.entries[0].size == 1);
        assert(MEMMAP.entries[0].end == 0);
        assert(MEMMAP.entries[0].limit == 1);

        assert(KernAux_MemMap_entry_by_index(memmap, 0) == &MEMMAP.entries[0]);
    }

    {
        MEMSET;
        KernAux_MemMap_init(memmap, 2);

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 2);
        assert(MEMMAP.entries_count == 0);

        assert(KernAux_MemMap_add_entry(memmap, false, NULL, 0, 2));

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 2);
        assert(MEMMAP.entries_count == 1);

        assert(KernAux_MemMap_finish(memmap));

        assert(MEMMAP.is_finished);
        assert(MEMMAP.memory_size == 2);
        assert(MEMMAP.entries_count == 1);
        assert(MEMMAP.entries[0].is_available == false);
        assert(MEMMAP.entries[0].tag[0] == '\0');
        assert(MEMMAP.entries[0].start == 0);
        assert(MEMMAP.entries[0].size == 2);
        assert(MEMMAP.entries[0].end == 1);
        assert(MEMMAP.entries[0].limit == 2);

        assert(KernAux_MemMap_entry_by_index(memmap, 0) == &MEMMAP.entries[0]);
    }

    {
        MEMSET;
        KernAux_MemMap_init(memmap, 1);

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 1);
        assert(MEMMAP.entries_count == 0);

        assert(KernAux_MemMap_add_entry(memmap, false, NULL, 0, 2));

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 1);
        assert(MEMMAP.entries_count == 1);

        assert(!KernAux_MemMap_finish(memmap));

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 1);
        assert(MEMMAP.entries_count == 1);
        assert(MEMMAP.entries[0].is_available == false);
        assert(MEMMAP.entries[0].tag[0] == '\0');
        assert(MEMMAP.entries[0].start == 0);
        assert(MEMMAP.entries[0].size == 2);
        assert(MEMMAP.entries[0].end == 1);
        assert(MEMMAP.entries[0].limit == 2);

        assert(KernAux_MemMap_entry_by_index(memmap, 0) == NULL);
    }

    {
        MEMSET;
        KernAux_MemMap_init(memmap, 2);

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 2);
        assert(MEMMAP.entries_count == 0);

        assert(KernAux_MemMap_add_entry(memmap, false, NULL, 0, 1));

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 2);
        assert(MEMMAP.entries_count == 1);

        assert(KernAux_MemMap_add_entry(memmap, false, NULL, 1, 1));

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 2);
        assert(MEMMAP.entries_count == 2);

        assert(KernAux_MemMap_finish(memmap));

        assert(MEMMAP.is_finished);
        assert(MEMMAP.memory_size == 2);
        assert(MEMMAP.entries_count == 2);
        assert(MEMMAP.entries[0].is_available == false);
        assert(MEMMAP.entries[0].tag[0] == '\0');
        assert(MEMMAP.entries[0].start == 0);
        assert(MEMMAP.entries[0].size == 1);
        assert(MEMMAP.entries[0].end == 0);
        assert(MEMMAP.entries[0].limit == 1);
        assert(MEMMAP.entries[1].is_available == false);
        assert(MEMMAP.entries[1].tag[0] == '\0');
        assert(MEMMAP.entries[1].start == 1);
        assert(MEMMAP.entries[1].size == 1);
        assert(MEMMAP.entries[1].end == 1);
        assert(MEMMAP.entries[1].limit == 2);

        assert(KernAux_MemMap_entry_by_index(memmap, 0) == &MEMMAP.entries[0]);
        assert(KernAux_MemMap_entry_by_index(memmap, 1) == &MEMMAP.entries[1]);
    }

    return 0;
}
