#ifndef KERNAUX_INCLUDED_MALLOC
#define KERNAUX_INCLUDED_MALLOC

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

#include <stddef.h>

typedef void *(*KernAux_Malloc_Calloc) (void *malloc, size_t nmemb, size_t size);
typedef void  (*KernAux_Malloc_Free)   (void *malloc, void *ptr);
typedef void *(*KernAux_Malloc_Malloc) (void *malloc, size_t size);
typedef void *(*KernAux_Malloc_Realloc)(void *malloc, void *ptr, size_t size);

typedef const struct KernAux_Malloc {
    KernAux_Malloc_Calloc  KERNAUX_PROTECTED_FIELD(calloc);
    KernAux_Malloc_Free    KERNAUX_PROTECTED_FIELD(free);
    KernAux_Malloc_Malloc  KERNAUX_PROTECTED_FIELD(malloc);
    KernAux_Malloc_Realloc KERNAUX_PROTECTED_FIELD(realloc);
} *KernAux_Malloc;

void *KernAux_Malloc_malloc (KernAux_Malloc malloc, size_t size);
void  KernAux_Malloc_free   (KernAux_Malloc malloc, void *ptr);
void *KernAux_Malloc_calloc (KernAux_Malloc malloc, size_t nmemb, size_t size);
void *KernAux_Malloc_realloc(KernAux_Malloc malloc, void *ptr, size_t size);

#ifdef __cplusplus
}
#endif

#endif
