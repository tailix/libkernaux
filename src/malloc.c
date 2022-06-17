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

#define ALIGN_MASK(align) ((align) - 1) // align should be a power of 2
#define ALIGN_UP(val, align) (((val) + ALIGN_MASK(align)) & ~ALIGN_MASK(align))

#define MIN_MALLOC_SIZE (32) // 2**5

struct KernAux_Malloc KernAux_Malloc_create()
{
    struct KernAux_Malloc malloc;
    KernAux_Malloc_init(&malloc);
    return malloc;
}

void KernAux_Malloc_init(const KernAux_Malloc malloc)
{
    KERNAUX_ASSERT(malloc);

    (void)malloc;
}

void KernAux_Malloc_add_memory_block(
    const KernAux_Malloc malloc,
    void *const ptr,
    const size_t size
) {
    KERNAUX_ASSERT(malloc);
    KERNAUX_ASSERT(ptr);
    KERNAUX_ASSERT(size);

    (void)malloc;
    (void)ptr;
    (void)size;
}

void *KernAux_Malloc_malloc(const KernAux_Malloc malloc, const size_t size)
{
    KERNAUX_ASSERT(malloc);
    if (size == 0) return NULL;

    const size_t actual_size = ALIGN_UP(size, MIN_MALLOC_SIZE);
    // Too large, let's not care about the case.
    if (actual_size < size) return NULL;

    (void)malloc;

    return NULL;
}

void KernAux_Malloc_free(const KernAux_Malloc malloc, void *const ptr)
{
    KERNAUX_ASSERT(malloc);

    (void)malloc;
    (void)ptr;
}
