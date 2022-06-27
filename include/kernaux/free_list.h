#ifndef KERNAUX_INCLUDED_FREE_LIST
#define KERNAUX_INCLUDED_FREE_LIST

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>
#include <kernaux/generic/malloc.h>
#include <kernaux/generic/mutex.h>

#include <stddef.h>

typedef struct KernAux_FreeList_Node {
    void                         *KERNAUX_PRIVATE_FIELD(orig_ptr);
    struct KernAux_FreeList_Node *KERNAUX_PRIVATE_FIELD(next);
    struct KernAux_FreeList_Node *KERNAUX_PRIVATE_FIELD(prev);
    size_t                        KERNAUX_PRIVATE_FIELD(size);
    char                         *KERNAUX_PRIVATE_FIELD(block);
} *KernAux_FreeList_Node;

typedef struct KernAux_FreeList {
    struct KernAux_Malloc malloc;
    KernAux_Mutex         KERNAUX_PRIVATE_FIELD(mutex);
    KernAux_FreeList_Node KERNAUX_PRIVATE_FIELD(head);
} *KernAux_FreeList;

struct KernAux_FreeList KernAux_FreeList_create(KernAux_Mutex mutex);
void KernAux_FreeList_init(KernAux_FreeList free_list, KernAux_Mutex mutex);

void
KernAux_FreeList_add_zone(KernAux_FreeList free_list, void *ptr, size_t size);

#ifdef __cplusplus
}
#endif

#endif
