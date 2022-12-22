#ifndef KERNAUX_INCLUDED_MEMMAP
#define KERNAUX_INCLUDED_MEMMAP

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/generic/malloc.h>
#include <kernaux/macro.h>

#include <stdbool.h>
#include <stddef.h>

typedef struct KernAux_Memmap {
    void          *KERNAUX_PRIVATE_FIELD(buffer);
    size_t         KERNAUX_PRIVATE_FIELD(buffer_size);
    KernAux_Malloc KERNAUX_PRIVATE_FIELD(malloc);
} *KernAux_Memmap;

typedef struct KernAux_Memmap_Builder {
    bool                  KERNAUX_PRIVATE_FIELD(is_finished);
    struct KernAux_Memmap KERNAUX_PRIVATE_FIELD(memmap);
} *KernAux_Memmap_Builder;

struct KernAux_Memmap_Builder
KernAux_Memmap_Builder_create_from_buffer(void *buffer, size_t buffer_size);
struct KernAux_Memmap_Builder
KernAux_Memmap_Builder_create_from_malloc(KernAux_Malloc malloc);

struct KernAux_Memmap
KernAux_Memmap_Builder_finish(KernAux_Memmap_Builder builder);

void KernAux_Memmap_free(KernAux_Memmap memmap);

#ifdef __cplusplus
}
#endif

#endif
