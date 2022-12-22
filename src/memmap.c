#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "assert.h"

#include <kernaux/generic/malloc.h>
#include <kernaux/memmap.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static void free_node(KernAux_Malloc malloc, struct KernAux_Memmap_Node *node);

KernAux_Memmap_Builder
KernAux_Memmap_Builder_new(const KernAux_Malloc malloc)
{
    KERNAUX_NOTNULL(malloc);

    struct KernAux_Memmap_Builder *const builder =
        KernAux_Malloc_malloc(malloc, sizeof(*builder));
    if (!builder) {
        return NULL;
    }

    struct KernAux_Memmap *const memmap =
        KernAux_Malloc_malloc(malloc, sizeof(*memmap));
    if (!memmap) {
        KernAux_Malloc_free(malloc, builder);
        return NULL;
    }

    struct KernAux_Memmap_Node *const root_node =
        KernAux_Malloc_malloc(malloc, sizeof(*root_node));
    if (!root_node) {
        KernAux_Malloc_free(malloc, memmap);
        KernAux_Malloc_free(malloc, builder);
        return NULL;
    }

    *root_node = (struct KernAux_Memmap_Node){
        .mem_start = 0x0,
        .mem_end   = 0xffffffffffffffff, // 2**64 - 1
        .mem_size  = 0xffffffffffffffff, // 2**64 - 1
        .next = NULL,
        .children = NULL,
    };
    *memmap = (struct KernAux_Memmap){
        .malloc = malloc,
        .root_node = root_node,
    };
    *builder = (struct KernAux_Memmap_Builder){
        .memmap = memmap,
    };

    return builder;
}

KernAux_Memmap_Node KernAux_Memmap_Builder_add(
    const KernAux_Memmap_Builder builder,
    KernAux_Memmap_Node parent_node,
    const uint64_t mem_start,
    const uint64_t mem_size
) {
    KERNAUX_NOTNULL(builder);
    KERNAUX_ASSERT(builder->memmap);
    KERNAUX_ASSERT(builder->memmap->root_node);
    KERNAUX_ASSERT(builder->memmap->malloc);
    KERNAUX_ASSERT(mem_size > 0);

    struct KernAux_Memmap_Node *const new_node =
        KernAux_Malloc_malloc(builder->memmap->malloc, sizeof(*new_node));
    if (!new_node) return NULL;

    new_node->mem_start = mem_start;
    new_node->mem_size = mem_size;
    new_node->mem_end = mem_start + mem_size - 1;

    if (!parent_node) {
        parent_node = (struct KernAux_Memmap_Node*)builder->memmap->root_node;
    }

    if (parent_node->children) {
        for (
            struct KernAux_Memmap_Node *curr_node =
                (struct KernAux_Memmap_Node*)parent_node->children;
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
        ((struct KernAux_Memmap_Node*)parent_node)->children = new_node;
    }

    return new_node;
}

KernAux_Memmap
KernAux_Memmap_Builder_finish_and_free(const KernAux_Memmap_Builder builder)
{
    KERNAUX_NOTNULL(builder);
    KERNAUX_ASSERT(builder->memmap);
    KERNAUX_ASSERT(builder->memmap->root_node);
    KERNAUX_ASSERT(builder->memmap->malloc);

    KernAux_Memmap memmap = builder->memmap;
    builder->memmap = NULL;
    KernAux_Malloc_free(memmap->malloc, builder);
    return memmap;
}

void KernAux_Memmap_free(const KernAux_Memmap memmap)
{
    KERNAUX_NOTNULL(memmap);
    KERNAUX_ASSERT(memmap->root_node);
    KERNAUX_ASSERT(memmap->malloc);
    KERNAUX_ASSERT(memmap->root_node->next == NULL);

    free_node(memmap->malloc, (struct KernAux_Memmap_Node*)memmap->root_node);

    KernAux_Malloc malloc = memmap->malloc;

    ((struct KernAux_Memmap*)memmap)->root_node = NULL;
    ((struct KernAux_Memmap*)memmap)->malloc = NULL;

    KernAux_Malloc_free(malloc, (void*)memmap);
}

void free_node(
    const KernAux_Malloc malloc,
    struct KernAux_Memmap_Node *const node
)
{
    KERNAUX_NOTNULL(malloc);
    KERNAUX_NOTNULL(node);

    for (
        struct KernAux_Memmap_Node *child_node =
            (struct KernAux_Memmap_Node*)node->children;
        child_node;
        child_node = (struct KernAux_Memmap_Node*)child_node->next
    ) {
        free_node(malloc, child_node);
    }

    KernAux_Malloc_free(malloc, node);
}
