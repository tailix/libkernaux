#ifndef KERNAUX_INCLUDED_SIZED_VOID
#define KERNAUX_INCLUDED_SIZED_VOID

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef struct KernAux_SizedVoid {
    size_t memory_size;
    void *ptr;
} *KernAux_SizedVoid;

struct KernAux_SizedVoid
KernAux_SizedVoid_create(size_t memory_size, void *ptr);

void KernAux_SizedVoid_init(
    KernAux_SizedVoid sized_void,
    size_t memory_size,
    void *ptr
);

#ifdef __cplusplus
}
#endif

#endif
