#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/memmap.h>

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define MEMMAP (*memmap)

void KernAux_MemMap_init(KernAux_MemMap memmap, const size_t memory_size)
{
    MEMMAP.is_finished = false;
    MEMMAP.memory_size = memory_size;
    MEMMAP.entries_count = 0;
    memset(MEMMAP.entries, 0, sizeof(MEMMAP.entries));
}
