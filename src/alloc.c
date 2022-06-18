/**
 * The code was inspired by the Embedded Artistry's libmemory.
 *
 * Copyright (c) 2017-2022 Embedded Artistry LLC
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/alloc.h>
#include <kernaux/assert.h>

#include <stddef.h>
#include <stdint.h>

#define ALIGN_MASK(align) ((align) - 1) // align should be a power of 2
#define ALIGN_UP(val, align) (((val) + ALIGN_MASK(align)) & ~ALIGN_MASK(align))

#define PTR_ALIGNMENT (sizeof(void*)) // TODO: align node to this value

#define ALLOC_HEADER_SIZE (offsetof(struct KernAux_Alloc_Node, block))
#define MIN_ALLOC_SIZE (ALLOC_HEADER_SIZE + 16)

struct KernAux_Alloc KernAux_Alloc_create()
{
    struct KernAux_Alloc alloc;
    KernAux_Alloc_init(&alloc);
    return alloc;
}

void KernAux_Alloc_init(const KernAux_Alloc alloc)
{
    KERNAUX_ASSERT(alloc);

    alloc->head = NULL;
}

void KernAux_Alloc_add_zone(
    const KernAux_Alloc alloc,
    void *const ptr,
    const size_t size,
    const bool dynamic
) {
    KERNAUX_ASSERT(alloc);
    KERNAUX_ASSERT(ptr);
    KERNAUX_ASSERT(size >= 2 * sizeof(struct KernAux_Alloc_Node));

    // TODO: implement dynamic zones
    KERNAUX_ASSERT(dynamic == false);
    (void)dynamic;

    KernAux_Alloc_Node new_node = ptr;
    new_node->free = true;
    new_node->actual_size = size;
    new_node->user_size = size - sizeof(struct KernAux_Alloc_Node);

    // TODO: lock
    new_node->next = alloc->head;
    alloc->head = new_node;
    // TODO: unlock
}

void *KernAux_Alloc_malloc(const KernAux_Alloc alloc, const size_t size)
{
    KERNAUX_ASSERT(alloc);
    if (size == 0) return NULL;

    KernAux_Alloc_Node node = NULL;
    void *ptr = NULL;

    // TODO: lock

    for (
        KernAux_Alloc_Node item_node = alloc->head;
        item_node;
        item_node = item_node->next
    ) {
        if (item_node->free && item_node->user_size >= size) {
            node = item_node;
            break;
        }
    }

    if (node) {
        // Can we split the block?
        if (node->actual_size - size >= MIN_ALLOC_SIZE) {
            KernAux_Alloc_Node new_node =
                (KernAux_Alloc_Node)(((uintptr_t)&node->block) + size);
            new_node->free = true;
            new_node->actual_size = node->actual_size - size - ALLOC_HEADER_SIZE;
            new_node->user_size   = node->user_size   - size - ALLOC_HEADER_SIZE;
            new_node->next = node->next;
            node->next = new_node;
        }

        node->free = false;
        ptr = &node->block;
    }

    // TODO: unlock

    return ptr;
}

void KernAux_Alloc_free(const KernAux_Alloc alloc, void *const ptr)
{
    KERNAUX_ASSERT(alloc);

    // TODO: implement this

    (void)alloc;
    (void)ptr;
}
