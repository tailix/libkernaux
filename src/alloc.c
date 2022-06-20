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

#define NODE_HEADER_SIZE (offsetof(struct KernAux_Alloc_Node, block))
#define MIN_ZONE_SIZE (2 * NODE_HEADER_SIZE)
#define MIN_SPLIT_SIZE (NODE_HEADER_SIZE + 16)

#define CONTAINER_OF(ptr, type, member) ((type*)((uintptr_t)(ptr) - offsetof(type, member)))

//#define ALIGN_MASK(align) ((align) - 1) // align should be a power of 2
//#define ALIGN_UP(val, align) (((val) + ALIGN_MASK(align)) & ~ALIGN_MASK(align))

//#define PTR_ALIGNMENT (sizeof(void*)) // TODO: align node to this value

#define LOCK(alloc)                               \
    do {                                          \
        if ((alloc)->mutex) {                     \
            KernAux_Mutex_lock((alloc)->mutex);   \
        }                                         \
    } while (0)

#define UNLOCK(alloc)                             \
    do {                                          \
        if ((alloc)->mutex) {                     \
            KernAux_Mutex_unlock((alloc)->mutex); \
        }                                         \
    } while (0)

static void KernAux_Alloc_insert(
    KernAux_Alloc alloc,
    KernAux_Alloc_Node node,
    KernAux_Alloc_Node prev,
    KernAux_Alloc_Node next
);
static void KernAux_Alloc_remove(KernAux_Alloc alloc, KernAux_Alloc_Node node);

struct KernAux_Alloc KernAux_Alloc_create(const KernAux_Mutex mutex)
{
    struct KernAux_Alloc alloc;
    KernAux_Alloc_init(&alloc, mutex);
    return alloc;
}

void KernAux_Alloc_init(const KernAux_Alloc alloc, const KernAux_Mutex mutex)
{
    KERNAUX_ASSERT(alloc);

    alloc->mutex = mutex;
    alloc->head = NULL;
}

void KernAux_Alloc_add_zone(
    const KernAux_Alloc alloc,
    void *const ptr,
    const size_t size
) {
    KERNAUX_ASSERT(alloc);
    KERNAUX_ASSERT(ptr);
    KERNAUX_ASSERT(size >= MIN_ZONE_SIZE);

    LOCK(alloc);

    KernAux_Alloc_Node new_node = ptr;
    new_node->actual_size = size;
    new_node->user_size = size - NODE_HEADER_SIZE;
    KernAux_Alloc_insert(alloc, new_node, NULL, alloc->head);

    UNLOCK(alloc);
}

void *KernAux_Alloc_malloc(const KernAux_Alloc alloc, const size_t size)
{
    KERNAUX_ASSERT(alloc);
    if (size == 0) return NULL;

    LOCK(alloc);

    KernAux_Alloc_Node node = NULL;

    for (
        KernAux_Alloc_Node item_node = alloc->head;
        item_node;
        item_node = item_node->next
    ) {
        if (item_node->user_size >= size) {
            node = item_node;
            break;
        }
    }

    if (node) {
        // Can we split the block?
        if (node->actual_size - size >= MIN_SPLIT_SIZE) {
            KernAux_Alloc_Node new_node =
                (KernAux_Alloc_Node)(((uintptr_t)&node->block) + size);
            new_node->actual_size = node->actual_size - size - NODE_HEADER_SIZE;
            new_node->user_size   = node->user_size   - size - NODE_HEADER_SIZE;
            KernAux_Alloc_insert(alloc, new_node, node, node->next);
        }

        KernAux_Alloc_remove(alloc, node);
    }

    UNLOCK(alloc);

    if (node) {
        return &node->block;
    } else {
        return NULL;
    }
}

void KernAux_Alloc_free(const KernAux_Alloc alloc, void *const ptr)
{
    KERNAUX_ASSERT(alloc);
    if (!ptr) return;

    LOCK(alloc);

    KernAux_Alloc_Node node =
        CONTAINER_OF(ptr, struct KernAux_Alloc_Node, block);

    KernAux_Alloc_Node last_node = NULL;

    for (
        KernAux_Alloc_Node item_node = alloc->head;
        item_node;
        item_node = item_node->next
    ) {
        last_node = item_node;

        if (item_node > node) {
            KernAux_Alloc_insert(alloc, node, item_node->prev, item_node);
            goto block_added;
        }
    }

    KernAux_Alloc_insert(alloc, node, last_node, NULL);

block_added:

    UNLOCK(alloc);
}

void KernAux_Alloc_insert(
    const KernAux_Alloc alloc,
    const KernAux_Alloc_Node node,
    const KernAux_Alloc_Node prev,
    const KernAux_Alloc_Node next
) {
    KERNAUX_ASSERT(alloc);
    KERNAUX_ASSERT(node);
    KERNAUX_ASSERT(node != prev);
    KERNAUX_ASSERT(node != next);

    if (!prev) alloc->head = node;
    node->next = next;
    node->prev = prev;
    if (node->next) node->next->prev = node;
    if (node->prev) node->prev->next = node;
}

void KernAux_Alloc_remove(
    const KernAux_Alloc alloc,
    const KernAux_Alloc_Node node
) {
    KERNAUX_ASSERT(alloc);
    KERNAUX_ASSERT(node);

    if (alloc->head == node) alloc->head = node->next;
    if (node->next) node->next->prev = node->prev;
    if (node->prev) node->prev->next = node->next;
}
