#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "assert.h"

#include <kernaux/memmap.h>

#include <stdbool.h>
#include <stddef.h>

struct KernAux_Memmap_Builder KernAux_Memmap_Builder_create_from_buffer(
    void *const buffer,
    const size_t buffer_size
) {
    KERNAUX_NOTNULL(buffer);
    KERNAUX_ASSERT(buffer_size > 0);

    return (struct KernAux_Memmap_Builder){
        .is_finished = false,
        .memmap = {
            .buffer = buffer,
            .buffer_size = buffer_size,
            .malloc = NULL,
        },
    };
}

struct KernAux_Memmap_Builder
KernAux_Memmap_Builder_create_from_malloc(const KernAux_Malloc malloc)
{
    KERNAUX_NOTNULL(malloc);

    return (struct KernAux_Memmap_Builder){
        .is_finished = false,
        .memmap = {
            .buffer = NULL,
            .buffer_size = 0,
            .malloc = malloc,
        },
    };
}

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
