/**
 * The code was inspired by the Embedded Artistry's libmemory.
 *
 * Copyright (c) 2017-2022 Embedded Artistry LLC
 * Copyright (c) 2022      Alex Kotov
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "assert.h"

#include <kernaux/free_list.h>
#include <kernaux/generic/malloc.h>
#include <kernaux/generic/mutex.h>
#include <kernaux/macro.h>

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define NODE_HEADER_SIZE (offsetof(struct KernAux_FreeList_Node, block))
#define MIN_ZONE_SIZE (2 * NODE_HEADER_SIZE)
#define MIN_SPLIT_SIZE (NODE_HEADER_SIZE + 16)

#define ALIGN_MASK(align) ((align) - 1) // align should be a power of 2
#define ALIGN_UP(val, align) (((val) + ALIGN_MASK(align)) & ~ALIGN_MASK(align))

#define PTR_ALIGNMENT (sizeof(void*))

#define LOCK(free_list)                               \
    do {                                              \
        if ((free_list)->mutex) {                     \
            KernAux_Mutex_lock((free_list)->mutex);   \
        }                                             \
    } while (0)

#define UNLOCK(free_list)                             \
    do {                                              \
        if ((free_list)->mutex) {                     \
            KernAux_Mutex_unlock((free_list)->mutex); \
        }                                             \
    } while (0)

static void  KernAux_FreeList_free   (void *malloc, void *ptr);
static void *KernAux_FreeList_malloc (void *malloc, size_t size);
static void *KernAux_FreeList_realloc(void *malloc, void *ptr, size_t size);

static void KernAux_FreeList_defrag(KernAux_FreeList free_list);
static void KernAux_FreeList_insert(
    KernAux_FreeList free_list,
    KernAux_FreeList_Node node,
    KernAux_FreeList_Node prev,
    KernAux_FreeList_Node next
);
static void KernAux_FreeList_remove(
    KernAux_FreeList free_list,
    KernAux_FreeList_Node node
);

struct KernAux_FreeList KernAux_FreeList_create(const KernAux_Mutex mutex)
{
    struct KernAux_FreeList free_list;
    KernAux_FreeList_init(&free_list, mutex);
    return free_list;
}

void KernAux_FreeList_init(
    const KernAux_FreeList free_list,
    const KernAux_Mutex mutex
) {
    KERNAUX_NOTNULL(free_list);

    free_list->malloc.calloc  = NULL;
    free_list->malloc.free    = KernAux_FreeList_free;
    free_list->malloc.malloc  = KernAux_FreeList_malloc;
    free_list->malloc.realloc = KernAux_FreeList_realloc;
    free_list->mutex = mutex;
    free_list->head = NULL;
}

void KernAux_FreeList_add_zone(
    const KernAux_FreeList free_list,
    void *const ptr,
    const size_t size
) {
    KERNAUX_NOTNULL(free_list);
    KERNAUX_NOTNULL(ptr);
    KERNAUX_ASSERT(size >= MIN_ZONE_SIZE);

    LOCK(free_list);

    KernAux_FreeList_Node new_node =
        (KernAux_FreeList_Node)ALIGN_UP((uintptr_t)ptr, PTR_ALIGNMENT);
    new_node->orig_ptr = ptr;
    new_node->size = size;

    KernAux_FreeList_Node prev_node = NULL;
    KernAux_FreeList_Node next_node;
    KernAux_FreeList_Node last_node = NULL;

    for (
        KernAux_FreeList_Node item_node = free_list->head;
        item_node;
        item_node = item_node->next
    ) {
        last_node = item_node;

        if (item_node > new_node) {
            next_node = item_node;
            if (item_node->prev) prev_node = item_node->prev;
            goto block_found;
        }
    }

    prev_node = last_node;
    next_node = NULL;

block_found:
    KernAux_FreeList_insert(free_list, new_node, prev_node, next_node);
    KernAux_FreeList_defrag(free_list);

    UNLOCK(free_list);
}

void KernAux_FreeList_free(void *const malloc, void *const ptr)
{
    const KernAux_FreeList free_list = malloc;
    KERNAUX_NOTNULL(free_list);
    KERNAUX_NOTNULL(ptr);

    LOCK(free_list);

    KernAux_FreeList_Node node =
        KERNAUX_CONTAINER_OF(ptr, struct KernAux_FreeList_Node, block);
    KernAux_FreeList_Node last_node = NULL;

    for (
        KernAux_FreeList_Node item_node = free_list->head;
        item_node;
        item_node = item_node->next
    ) {
        last_node = item_node;

        if (item_node > node) {
            KernAux_FreeList_insert(
                free_list,
                node,
                item_node->prev,
                item_node
            );
            goto block_added;
        }
    }

    KernAux_FreeList_insert(free_list, node, last_node, NULL);

block_added:
    KernAux_FreeList_defrag(free_list);

    UNLOCK(free_list);
}

void *KernAux_FreeList_malloc(void *const malloc, size_t size)
{
    const KernAux_FreeList free_list = malloc;
    KERNAUX_NOTNULL(free_list);
    KERNAUX_ASSERT(size);

    LOCK(free_list);

    size = ALIGN_UP(size, PTR_ALIGNMENT);

    KernAux_FreeList_Node node = NULL;

    for (
        KernAux_FreeList_Node item_node = free_list->head;
        item_node;
        item_node = item_node->next
    ) {
        if (item_node->size - NODE_HEADER_SIZE >= size) {
            node = item_node;
            break;
        }
    }

    if (node) {
        // Can we split the block?
        if (node->size - size >= MIN_SPLIT_SIZE) {
            KernAux_FreeList_Node new_node =
                (KernAux_FreeList_Node)(((uintptr_t)&node->block) + size);

            KERNAUX_ASSERT(
                ((uintptr_t)new_node)
                ==
                ALIGN_UP((uintptr_t)new_node, PTR_ALIGNMENT)
            );

            new_node->orig_ptr = new_node;
            new_node->size = node->size - size - NODE_HEADER_SIZE;
            node->size = NODE_HEADER_SIZE + size;
            KernAux_FreeList_insert(free_list, new_node, node, node->next);
        }

        KernAux_FreeList_remove(free_list, node);
    }

    UNLOCK(free_list);

    if (node) {
        return &node->block;
    } else {
        return NULL;
    }
}

void *KernAux_FreeList_realloc(
    void *const malloc,
    void *const old_ptr,
    const size_t new_size
) {
    const KernAux_FreeList free_list = malloc;
    KERNAUX_NOTNULL(free_list);
    KERNAUX_NOTNULL(old_ptr);
    KERNAUX_ASSERT(new_size);

    LOCK(free_list);

    KernAux_FreeList_Node node =
        KERNAUX_CONTAINER_OF(old_ptr, struct KernAux_FreeList_Node, block);
    const size_t old_size = node->size - NODE_HEADER_SIZE;

    void *new_ptr = KernAux_FreeList_malloc(free_list, new_size);

    if (new_ptr) {
        const size_t min_size = old_size < new_size ? old_size : new_size;
        memcpy(new_ptr, old_ptr, min_size);
    }

    UNLOCK(free_list);
    return new_ptr;
}

void KernAux_FreeList_defrag(const KernAux_FreeList free_list)
{
    KERNAUX_NOTNULL(free_list);

    for (
        KernAux_FreeList_Node item_node = free_list->head;
        item_node;
        item_node = item_node->next
    ) {
        const KernAux_FreeList_Node node = item_node->prev;
        if (!node) continue;
        if (((uintptr_t)node) + node->size != (uintptr_t)item_node->orig_ptr) {
            continue;
        }

        node->size += item_node->size;
        KernAux_FreeList_remove(free_list, item_node);
    }
}

void KernAux_FreeList_insert(
    const KernAux_FreeList free_list,
    const KernAux_FreeList_Node node,
    const KernAux_FreeList_Node prev,
    const KernAux_FreeList_Node next
) {
    KERNAUX_NOTNULL(free_list);
    KERNAUX_NOTNULL(node);
    KERNAUX_ASSERT(node != prev);
    KERNAUX_ASSERT(node != next);
    KERNAUX_ASSERT(!prev || prev->next == next);
    KERNAUX_ASSERT(!next || next->prev == prev);

    if (!prev) free_list->head = node;
    node->next = next;
    node->prev = prev;
    if (node->next) node->next->prev = node;
    if (node->prev) node->prev->next = node;
}

void KernAux_FreeList_remove(
    const KernAux_FreeList free_list,
    const KernAux_FreeList_Node node
) {
    KERNAUX_NOTNULL(free_list);
    KERNAUX_NOTNULL(node);
    KERNAUX_ASSERT(!node->next || node->next->prev == node);
    KERNAUX_ASSERT(!node->prev || node->prev->next == node);

    if (free_list->head == node) free_list->head = node->next;
    if (node->next) node->next->prev = node->prev;
    if (node->prev) node->prev->next = node->next;
}
