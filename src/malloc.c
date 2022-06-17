/**
 * The code was inspired by the Embedded Artistry's libmemory.
 *
 * Copyright (c) 2017-2022 Embedded Artistry LLC
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/malloc.h>

#include <stddef.h>
#include <stdint.h>

#define ALIGN_MASK(align) ((align) - 1) // align should be a power of 2
#define ALIGN_UP(val, align) (((val) + ALIGN_MASK(align)) & ~ALIGN_MASK(align))

#define PTR_ALIGNMENT (sizeof(void*)) // TODO: align node to this value

#define ALLOC_HEADER_SIZE (offsetof(struct KernAux_Malloc_Node, block))
#define MIN_ALLOC_SIZE (ALLOC_HEADER_SIZE + 16)

struct KernAux_Malloc KernAux_Malloc_create()
{
    struct KernAux_Malloc malloc;
    KernAux_Malloc_init(&malloc);
    return malloc;
}

void KernAux_Malloc_init(const KernAux_Malloc malloc)
{
    KERNAUX_ASSERT(malloc);

    malloc->head = NULL;
}

void KernAux_Malloc_add_memory_block(
    const KernAux_Malloc malloc,
    void *const ptr,
    const size_t size
) {
    KERNAUX_ASSERT(malloc);
    KERNAUX_ASSERT(ptr);
    KERNAUX_ASSERT(size >= 2 * sizeof(struct KernAux_Malloc_Node));

    KernAux_Malloc_Node new_node = ptr;
    new_node->free = true;
    new_node->actual_size = size;
    new_node->user_size = size - sizeof(struct KernAux_Malloc_Node);

    // TODO: lock
    new_node->next = malloc->head;
    malloc->head = new_node;
    // TODO: unlock
}

void *KernAux_Malloc_malloc(const KernAux_Malloc malloc, const size_t size)
{
    KERNAUX_ASSERT(malloc);
    if (size == 0) return NULL;

    KernAux_Malloc_Node node = NULL;
    void *ptr = NULL;

    // TODO: lock

    for (
        KernAux_Malloc_Node item_node = malloc->head;
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
            KernAux_Malloc_Node new_node =
                (KernAux_Malloc_Node)(((uintptr_t)&node->block) + size);
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

void KernAux_Malloc_free(const KernAux_Malloc malloc, void *const ptr)
{
    KERNAUX_ASSERT(malloc);

    // TODO: implement this

    (void)malloc;
    (void)ptr;
}
