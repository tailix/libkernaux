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
KernAux_SizedVoid_create(void *ptr, size_t memory_size);

void KernAux_SizedVoid_init(
    KernAux_SizedVoid sized_void,
    void *ptr,
    size_t memory_size
);

void KernAux_SizedVoid_memset(KernAux_SizedVoid sized_void, int c);

#ifdef __cplusplus
}
#endif

#endif
