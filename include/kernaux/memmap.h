#ifndef KERNAUX_INCLUDED_MEMMAP
#define KERNAUX_INCLUDED_MEMMAP

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/generic/malloc.h>
#include <kernaux/macro.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef const struct KernAux_Memmap_Node {
    uint64_t mem_start, mem_end, mem_size;
    const struct KernAux_Memmap_Node *next;
} *KernAux_Memmap_Node;

typedef struct KernAux_Memmap {
    struct KernAux_Memmap_Node *KERNAUX_PRIVATE_FIELD(node);
    KernAux_Malloc              KERNAUX_PRIVATE_FIELD(malloc);
} *KernAux_Memmap;

typedef struct KernAux_Memmap_Builder {
    bool                  KERNAUX_PRIVATE_FIELD(is_finished);
    struct KernAux_Memmap KERNAUX_PRIVATE_FIELD(memmap);
} *KernAux_Memmap_Builder;

struct KernAux_Memmap_Builder
KernAux_Memmap_Builder_create(KernAux_Malloc malloc);

bool KernAux_Memmap_Builder_add(
    KernAux_Memmap_Builder builder,
    uint64_t mem_start,
    uint64_t mem_size
);

struct KernAux_Memmap
KernAux_Memmap_Builder_finish(KernAux_Memmap_Builder builder);

void KernAux_Memmap_free(KernAux_Memmap memmap);

#ifdef __cplusplus
}
#endif

#endif
