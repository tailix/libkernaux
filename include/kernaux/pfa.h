#ifndef KERNAUX_INCLUDED_PFA
#define KERNAUX_INCLUDED_PFA 1

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define KERNAUX_PFA_PAGE_SIZE (4 * 1024)
#define KERNAUX_PFA_PAGES_COUNT_MAX (1024 * 1024)

struct KernAux_PFA {
    bool pages[KERNAUX_PFA_PAGES_COUNT_MAX];
};

void KernAux_PFA_initialize(struct KernAux_PFA *pfa)
__attribute__((nonnull));

void KernAux_PFA_mark_available(
    struct KernAux_PFA *pfa,
    unsigned int start,
    unsigned int end
)
__attribute__((nonnull));

void KernAux_PFA_mark_unavailable(
    struct KernAux_PFA *pfa,
    unsigned int start,
    unsigned int end
)
__attribute__((nonnull));

unsigned int KernAux_PFA_alloc_page(struct KernAux_PFA *pfa)
__attribute__((nonnull));

void KernAux_PFA_free_page(struct KernAux_PFA *pfa, unsigned int page_addr)
__attribute__((nonnull));

#ifdef __cplusplus
}
#endif

#endif
