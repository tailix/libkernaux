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

struct KernAux_Memmap_Builder
KernAux_Memmap_Builder_create(const KernAux_Malloc malloc)
{
    KERNAUX_NOTNULL(malloc);

    struct KernAux_Memmap_Builder builder = {
        .is_finished = false,
        .memmap = {
            .malloc = malloc,
            .root_node = {
                .mem_start = 0x0,
                .mem_end   = 0xffffffffffffffff, // 2**64 - 1
                .mem_size  = 0xffffffffffffffff, // 2**64 - 1
                .next = NULL,
                .children = NULL,
            },
        },
    };
    return builder;
}

bool KernAux_Memmap_Builder_add(
    const KernAux_Memmap_Builder builder,
    KernAux_Memmap_Node parent_node,
    const uint64_t mem_start,
    const uint64_t mem_size
) {
    KERNAUX_NOTNULL(builder);
    KERNAUX_ASSERT(!builder->is_finished);
    KERNAUX_ASSERT(builder->memmap.malloc);
    KERNAUX_ASSERT(mem_size > 0);

    struct KernAux_Memmap_Node *const new_node =
        KernAux_Malloc_malloc(builder->memmap.malloc, sizeof(*new_node));
    if (!new_node) return false;

    new_node->mem_start = mem_start;
    new_node->mem_size = mem_size;
    new_node->mem_end = mem_start + mem_size - 1;

    if (!parent_node) parent_node = &builder->memmap.root_node;

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
    builder->memmap.malloc = NULL;
    builder->memmap.root_node = (struct KernAux_Memmap_Node){
        .mem_start = 0,
        .mem_end = 0,
        .mem_size = 0,
        .next = NULL,
        .children = NULL,
    };
    return memmap;
}

KernAux_Memmap_Node KernAux_Memmap_root_node(const KernAux_Memmap memmap)
{
    KERNAUX_NOTNULL(memmap);
    KERNAUX_ASSERT(memmap->malloc);

    return &memmap->root_node;
}

void KernAux_Memmap_free(const KernAux_Memmap memmap)
{
    KERNAUX_NOTNULL(memmap);
    KERNAUX_ASSERT(memmap->root_node.next == NULL);
    if (!memmap->root_node.children) return;
    KERNAUX_ASSERT(memmap->malloc);

    free_node(memmap->malloc, &memmap->root_node);

    memmap->malloc = NULL;
    memmap->root_node = (struct KernAux_Memmap_Node){
        .mem_start = 0,
        .mem_end = 0,
        .mem_size = 0,
        .next = NULL,
        .children = NULL,
    };
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
