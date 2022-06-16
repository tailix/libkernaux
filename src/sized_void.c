#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/sized_void.h>

#include <stddef.h>
#include <string.h>

struct KernAux_SizedVoid
KernAux_SizedVoid_create(const size_t memory_size, void *const ptr)
{
    KERNAUX_ASSERT(memory_size);
    KERNAUX_ASSERT(ptr);

    struct KernAux_SizedVoid sized_void;
    KernAux_SizedVoid_init(&sized_void, memory_size, ptr);
    return sized_void;
}

void KernAux_SizedVoid_init(
    const KernAux_SizedVoid sized_void,
    const size_t memory_size,
    void *const ptr
) {
    KERNAUX_ASSERT(sized_void);
    KERNAUX_ASSERT(memory_size);
    KERNAUX_ASSERT(ptr);

    sized_void->memory_size = memory_size;
    sized_void->ptr = ptr;
}

void KernAux_SizedVoid_memset(const KernAux_SizedVoid sized_void, const int c)
{
    KERNAUX_ASSERT(sized_void);
    KERNAUX_ASSERT(sized_void->ptr);

    memset(sized_void->ptr, c, sized_void->memory_size);
}
