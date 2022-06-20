#ifndef KERNAUX_INCLUDED_MEMMAP
#define KERNAUX_INCLUDED_MEMMAP

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

#include <stdbool.h>
#include <stddef.h>

#define KERNAUX_MEMMAP_ENTRIES_MAX 100

#define KERNAUX_MEMMAP_ENTRY_TAG_SLEN_MAX 24
#define KERNAUX_MEMMAP_ENTRY_TAG_SIZE_MAX (KERNAUX_MEMMAP_ENTRY_TAG_SLEN_MAX + 1)

typedef const struct KernAux_MemMap_Entry {
    bool KERNAUX_PRIVATE_FIELD(is_available);
    char KERNAUX_PRIVATE_FIELD(tag)[KERNAUX_MEMMAP_ENTRY_TAG_SIZE_MAX];
    size_t KERNAUX_PRIVATE_FIELD(start);
    size_t KERNAUX_PRIVATE_FIELD(size);
    size_t KERNAUX_PRIVATE_FIELD(end);
    size_t KERNAUX_PRIVATE_FIELD(limit);
} *KernAux_MemMap_Entry;

typedef struct KernAux_MemMap {
    bool KERNAUX_PRIVATE_FIELD(is_finished);
    size_t KERNAUX_PRIVATE_FIELD(memory_size);
    size_t KERNAUX_PRIVATE_FIELD(entries_count);
    struct KernAux_MemMap_Entry KERNAUX_PRIVATE_FIELD(entries)[KERNAUX_MEMMAP_ENTRIES_MAX];
} KernAux_MemMap[1];

struct KernAux_MemMap KernAux_MemMap_create(size_t memory_size);
void KernAux_MemMap_init(KernAux_MemMap memmap, size_t memory_size);

/// @warning Must only be called with NOT finished memmap, otherwise panics.
bool KernAux_MemMap_add_entry(
    KernAux_MemMap memmap,
    bool is_available,
    const char *tag,
    size_t start,
    size_t size
);

/// @warning Must only be called with NOT finished memmap, otherwise panics.
bool KernAux_MemMap_finish(KernAux_MemMap memmap);

/// @warning Must only be called with finished memmap, otherwise panics.
KernAux_MemMap_Entry
KernAux_MemMap_entry_by_index(KernAux_MemMap memmap, size_t index);

/// @warning Must only be called with finished memmap, otherwise panics.
KernAux_MemMap_Entry
KernAux_MemMap_entry_by_start(KernAux_MemMap memmap, size_t start);

/// @warning Must only be called with finished memmap, otherwise panics.
KernAux_MemMap_Entry
KernAux_MemMap_entry_by_addr(KernAux_MemMap memmap, size_t addr);

#ifdef __cplusplus
}
#endif

#endif
