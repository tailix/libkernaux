#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "assert.h"

#include <kernaux/generic/malloc.h>
#include <kernaux/memmap.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct KernAux_Memmap_Builder
KernAux_Memmap_Builder_create(const KernAux_Malloc malloc)
{
    KERNAUX_NOTNULL(malloc);

    return (struct KernAux_Memmap_Builder){
        .is_finished = false,
        .memmap = { .node = NULL, .malloc = malloc },
    };
}

struct KernAux_Memmap
KernAux_Memmap_Builder_finish(const KernAux_Memmap_Builder builder)
{
    KERNAUX_NOTNULL(builder);
    KERNAUX_ASSERT(!builder->is_finished);
    KERNAUX_ASSERT(builder->memmap.malloc);

    builder->is_finished = true;
    struct KernAux_Memmap memmap = builder->memmap;
    builder->memmap.node = NULL;
    builder->memmap.malloc = NULL;
    return memmap;
}

void KernAux_Memmap_free(const KernAux_Memmap memmap)
{
    KERNAUX_NOTNULL(memmap);
    if (!memmap->node) return;
    KERNAUX_ASSERT(memmap->malloc);

    for (KernAux_Memmap_Node node = memmap->node; node;) {
        const KernAux_Memmap_Node next = node->next;
        KernAux_Malloc_free(memmap->malloc, (void*)node);
        node = next;
    }

    memmap->node = NULL;
    memmap->malloc = NULL;
}
