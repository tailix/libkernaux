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

bool KernAux_Memmap_Builder_add(
    const KernAux_Memmap_Builder builder,
    const uint64_t mem_start,
    const uint64_t mem_size
) {
    KERNAUX_NOTNULL(builder);
    KERNAUX_ASSERT(builder->memmap.malloc);
    KERNAUX_ASSERT(mem_size > 0);

    struct KernAux_Memmap_Node *const new_node =
        KernAux_Malloc_malloc(builder->memmap.malloc, sizeof(*new_node));
    if (!new_node) return false;

    new_node->mem_start = mem_start;
    new_node->mem_size = mem_size;
    new_node->mem_end = mem_start + mem_size - 1;

    if (builder->memmap.node) {
        for (
            struct KernAux_Memmap_Node *curr_node = builder->memmap.node;
            curr_node;
            curr_node = (struct KernAux_Memmap_Node*)curr_node->next
        ) {
            if (!curr_node->next ||
                curr_node->next->mem_start > new_node->mem_start)
            {
                if (new_node->next) {
                    KERNAUX_ASSERT(new_node->mem_end <
                                   new_node->next->mem_start);
                }
                new_node->next = curr_node->next;
                curr_node->next = new_node;
                break;
            }
        }
    } else {
        new_node->next = NULL;
        builder->memmap.node = new_node;
    }

    return true;
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
