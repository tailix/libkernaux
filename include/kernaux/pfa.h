#ifndef KERNAUX_INCLUDED_PFA
#define KERNAUX_INCLUDED_PFA 1

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

#define KERNAUX_PFA_PAGE_SIZE (4 * 1024)
#define KERNAUX_PFA_PAGES_COUNT_MAX (1024 * 1024)

typedef struct KernAux_PFA *KernAux_PFA;

struct KernAux_PFA {
    bool pages[KERNAUX_PFA_PAGES_COUNT_MAX];
};

void KernAux_PFA_initialize(KernAux_PFA pfa)
__attribute__((nonnull));

void KernAux_PFA_mark_available(KernAux_PFA pfa, size_t start, size_t end)
__attribute__((nonnull));

void KernAux_PFA_mark_unavailable(KernAux_PFA pfa, size_t start, size_t end)
__attribute__((nonnull));

size_t KernAux_PFA_alloc_page(KernAux_PFA pfa)
__attribute__((nonnull));

void KernAux_PFA_free_page(KernAux_PFA pfa, size_t page_addr)
__attribute__((nonnull));

#ifdef __cplusplus
}
#endif

#endif
