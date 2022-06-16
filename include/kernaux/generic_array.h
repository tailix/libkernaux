#ifndef KERNAUX_INCLUDED_GENERIC_ARRAY
#define KERNAUX_INCLUDED_GENERIC_ARRAY

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef struct KernAux_GenericArray {
    size_t memory_size;
    void *ptr;
} *KernAux_GenericArray;

struct KernAux_GenericArray
KernAux_GenericArray_create(size_t memory_size, void *ptr);

void KernAux_GenericArray_init(
    KernAux_GenericArray generic_array,
    size_t memory_size,
    void *ptr
);

#ifdef __cplusplus
}
#endif

#endif
