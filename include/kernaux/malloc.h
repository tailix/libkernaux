#ifndef KERNAUX_INCLUDED_MALLOC
#define KERNAUX_INCLUDED_MALLOC

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef struct KernAux_Malloc {
    int foobar;
} *KernAux_Malloc;

struct KernAux_Malloc KernAux_Malloc_create();
void KernAux_Malloc_init(KernAux_Malloc malloc);

void
KernAux_Malloc_add_memory_block(KernAux_Malloc malloc, void *ptr, size_t size);

void *KernAux_Malloc_malloc(KernAux_Malloc malloc, size_t size);
void  KernAux_Malloc_free  (KernAux_Malloc malloc, void *ptr);

#ifdef __cplusplus
}
#endif

#endif
