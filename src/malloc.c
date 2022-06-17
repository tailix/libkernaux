#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/malloc.h>

#include <stddef.h>

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

void *KernAux_Malloc_malloc(const KernAux_Malloc malloc, size_t size)
{
    KERNAUX_ASSERT(malloc);
    if (size == 0) return NULL;

    (void)malloc;
    (void)size;

    return NULL;
}

void KernAux_Malloc_free(const KernAux_Malloc malloc, void *const ptr)
{
    KERNAUX_ASSERT(malloc);

    (void)malloc;
    (void)ptr;
}
