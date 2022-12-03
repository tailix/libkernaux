#ifndef KERNAUX_INCLUDED_PFA
#define KERNAUX_INCLUDED_PFA

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define KERNAUX_PFA_PAGE_SIZE (4 * 1024)
#define KERNAUX_PFA_PAGES_COUNT_MAX (1024 * 1024)
#define KERNAUX_PFA_FLAGS_SIZE (KERNAUX_PFA_PAGES_COUNT_MAX / 8)

typedef struct KernAux_PFA *KernAux_PFA;

struct KernAux_PFA {
    uint8_t flags[KERNAUX_PFA_FLAGS_SIZE];
};

void KernAux_PFA_initialize(KernAux_PFA pfa)
KERNAUX_NOTNULL_ALL;

bool KernAux_PFA_is_available(KernAux_PFA pfa, size_t page_addr)
KERNAUX_NOTNULL_ALL;

void KernAux_PFA_mark_available(KernAux_PFA pfa, size_t start, size_t end)
KERNAUX_NOTNULL_ALL;
void KernAux_PFA_mark_unavailable(KernAux_PFA pfa, size_t start, size_t end)
KERNAUX_NOTNULL_ALL;

size_t KernAux_PFA_alloc_pages(KernAux_PFA pfa, size_t mem_size)
KERNAUX_NOTNULL_ALL;
void KernAux_PFA_free_pages(KernAux_PFA pfa, size_t page_addr, size_t mem_size)
KERNAUX_NOTNULL_ALL;

#ifdef __cplusplus
}
#endif

#endif
