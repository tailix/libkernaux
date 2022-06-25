#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/generic/malloc.h>

#include <stddef.h>

void *KernAux_Malloc_calloc(KernAux_Malloc malloc, size_t nmemb, size_t size)
{
    KERNAUX_ASSERT(malloc);
    KERNAUX_ASSERT(malloc->calloc);

    return malloc->calloc(malloc, nmemb, size);
}

void KernAux_Malloc_free(KernAux_Malloc malloc, void *ptr)
{
    KERNAUX_ASSERT(malloc);
    KERNAUX_ASSERT(malloc->free);

    malloc->free(malloc, ptr);
}

void *KernAux_Malloc_malloc(KernAux_Malloc malloc, size_t size)
{
    KERNAUX_ASSERT(malloc);
    KERNAUX_ASSERT(malloc->malloc);

    return malloc->malloc(malloc, size);
}

void *KernAux_Malloc_realloc(KernAux_Malloc malloc, void *ptr, size_t size)
{
    KERNAUX_ASSERT(malloc);
    KERNAUX_ASSERT(malloc->realloc);

    return malloc->realloc(malloc, ptr, size);
}
