#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/generic_array.h>

#include <stddef.h>

struct KernAux_GenericArray
KernAux_GenericArray_create(const size_t memory_size, void *const ptr)
{
    KERNAUX_ASSERT(memory_size);
    KERNAUX_ASSERT(ptr);

    struct KernAux_GenericArray generic_array;
    KernAux_GenericArray_init(&generic_array, memory_size, ptr);
    return generic_array;
}

void KernAux_GenericArray_init(
    const KernAux_GenericArray generic_array,
    const size_t memory_size,
    void *const ptr
) {
    KERNAUX_ASSERT(generic_array);
    KERNAUX_ASSERT(memory_size);
    KERNAUX_ASSERT(ptr);

    generic_array->memory_size = memory_size;
    generic_array->ptr = ptr;
}
