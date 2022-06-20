#ifndef KERNAUX_INCLUDED_ALLOC
#define KERNAUX_INCLUDED_ALLOC

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>
#include <kernaux/mutex.h>

#include <stddef.h>

typedef struct KernAux_Alloc_Node {
    struct KernAux_Alloc_Node *KERNAUX_PRIVATE_FIELD(next);
    struct KernAux_Alloc_Node *KERNAUX_PRIVATE_FIELD(prev);
    size_t KERNAUX_PRIVATE_FIELD(size);
    char *KERNAUX_PRIVATE_FIELD(block);
} *KernAux_Alloc_Node;

typedef struct KernAux_Alloc {
    KernAux_Mutex KERNAUX_PRIVATE_FIELD(mutex);
    KernAux_Alloc_Node KERNAUX_PRIVATE_FIELD(head);
} *KernAux_Alloc;

struct KernAux_Alloc KernAux_Alloc_create(KernAux_Mutex mutex);
void KernAux_Alloc_init(KernAux_Alloc alloc, KernAux_Mutex mutex);

void KernAux_Alloc_add_zone(KernAux_Alloc alloc, void *ptr, size_t size);

void *KernAux_Alloc_malloc(KernAux_Alloc alloc, size_t size);
void  KernAux_Alloc_free  (KernAux_Alloc alloc, void *ptr);

#ifdef __cplusplus
}
#endif

#endif
