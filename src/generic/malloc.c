#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "../assert.h"

#include <kernaux/generic/malloc.h>

#include <stddef.h>
#include <string.h>

void *KernAux_Malloc_calloc(KernAux_Malloc malloc, size_t nmemb, size_t size)
{
    KERNAUX_NOTNULL(malloc);

    // Common implementation
    const size_t total_size = nmemb * size;
    if (!total_size) return NULL;
    if (total_size / nmemb != size) return NULL;

    // Inherited implementation
    if (malloc->calloc) return malloc->calloc((void*)malloc, nmemb, size);

    // Default implementation
    void *const ptr = KernAux_Malloc_malloc(malloc, total_size);
    if (ptr) memset(ptr, 0, total_size);
    return ptr;
}

void KernAux_Malloc_free(KernAux_Malloc malloc, void *ptr)
{
    KERNAUX_NOTNULL(malloc);
    KERNAUX_ASSERT(malloc->free);

    // Common implementation
    if (!ptr) return;

    // Inherited implementation
    malloc->free((void*)malloc, ptr);
}

void *KernAux_Malloc_malloc(KernAux_Malloc malloc, size_t size)
{
    KERNAUX_NOTNULL(malloc);
    KERNAUX_ASSERT(malloc->malloc);

    // Common implementation
    if (!size) return NULL;

    // Inherited implementation
    return malloc->malloc((void*)malloc, size);
}

void *KernAux_Malloc_realloc(KernAux_Malloc malloc, void *ptr, size_t size)
{
    KERNAUX_NOTNULL(malloc);
    KERNAUX_ASSERT(malloc->realloc);

    // Common implementation
    if (!ptr) return KernAux_Malloc_malloc(malloc, size);
    if (!size) {
        KernAux_Malloc_free(malloc, ptr);
        return NULL;
    }

    // Inherited implementation
    return malloc->realloc((void*)malloc, ptr, size);
}
