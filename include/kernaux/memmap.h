#ifndef KERNAUX_INCLUDED_MEMMAP
#define KERNAUX_INCLUDED_MEMMAP

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/generic/display.h>
#include <kernaux/generic/malloc.h>
#include <kernaux/macro.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define KERNAUX_MEMMAP_FREE(memmap) do { \
    KernAux_Memmap_free(memmap); \
    memmap = NULL; \
} while (0)

/*********
 * Types *
 *********/

typedef const struct KernAux_Memmap_Node {
    uint64_t mem_start, mem_end, mem_size;
    bool is_available;
    const char *tag;
    const struct KernAux_Memmap_Node *next, *children;
} *KernAux_Memmap_Node;

typedef const struct KernAux_Memmap {
    KernAux_Memmap_Node root_node;

    KernAux_Malloc KERNAUX_PRIVATE_FIELD(malloc);
} *KernAux_Memmap;

typedef struct KernAux_Memmap_Builder {
    KernAux_Memmap KERNAUX_PRIVATE_FIELD(memmap);
} *KernAux_Memmap_Builder;

/*************
 * Functions *
 *************/

KernAux_Memmap_Builder
KernAux_Memmap_Builder_new(KernAux_Malloc malloc);

KernAux_Memmap_Node
KernAux_Memmap_Builder_add(
    KernAux_Memmap_Builder builder,
    uint64_t mem_start,
    uint64_t mem_size,
    bool is_available,
    const char *tag
);

KernAux_Memmap
KernAux_Memmap_Builder_finish_and_free(KernAux_Memmap_Builder builder);

void KernAux_Memmap_free(KernAux_Memmap memmap);
void KernAux_Memmap_print(KernAux_Memmap memmap, KernAux_Display display);

KernAux_Memmap_Node
KernAux_Memmap_node_by_addr(KernAux_Memmap memmap, uint64_t addr);

#ifdef __cplusplus
}
#endif

#endif
