#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "assert.h"

#include <kernaux/memmap.h>

#include <stdbool.h>
#include <stddef.h>

struct KernAux_Memmap
KernAux_Memmap_Builder_finish(const KernAux_Memmap_Builder builder)
{
    KERNAUX_NOTNULL(builder);
    KERNAUX_ASSERT(!builder->is_finished);

    builder->is_finished = true;
    struct KernAux_Memmap memmap = builder->memmap;
    builder->memmap.buffer = NULL;
    builder->memmap.buffer_size = 0;
    builder->memmap.malloc = NULL;
    return memmap;
}
