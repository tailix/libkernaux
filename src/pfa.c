#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/pfa.h>
#include <kernaux/stdlib.h>

static void KernAux_PFA_mark(
    struct KernAux_PFA *pfa,
    bool status,
    unsigned int start,
    unsigned int end
)
__attribute__((nonnull));

void KernAux_PFA_initialize(struct KernAux_PFA *const pfa)
{
    kernaux_memset(pfa->pages, false, sizeof(pfa->pages));
}

void KernAux_PFA_mark_available(
    struct KernAux_PFA *const pfa,
    unsigned int start,
    unsigned int end
) {
    KernAux_PFA_mark(pfa, true, start, end);
}

void KernAux_PFA_mark_unavailable(
    struct KernAux_PFA *const pfa,
    unsigned int start,
    unsigned int end
) {
    KernAux_PFA_mark(pfa, false, start, end);
}

void KernAux_PFA_mark(
    struct KernAux_PFA *const pfa,
    const bool status,
    unsigned int start,
    unsigned int end
) {
    if (start >= end) {
        return;
    }

    const unsigned int start_rem = start % KERNAUX_PFA_PAGE_SIZE;
    const unsigned int end_rem = (end + 1) % KERNAUX_PFA_PAGE_SIZE;

    if (start_rem != 0) {
        start = start - start_rem + KERNAUX_PFA_PAGE_SIZE;
    }

    if (end_rem != 0) {
        end = end - end_rem;
    }

    const unsigned int start_index = start / KERNAUX_PFA_PAGE_SIZE;
    const unsigned int end_index   = end   / KERNAUX_PFA_PAGE_SIZE;

    for (unsigned int index = start_index; index <= end_index; ++index) {
        pfa->pages[index] = status;
    }
}

unsigned int KernAux_PFA_alloc_page(struct KernAux_PFA *pfa)
{
    // We start from 1 because 0 indicates failure.
    // It is not very usefull to alloc page at address 0;
    //
    for (unsigned int index = 1; index < KERNAUX_PFA_PAGES_COUNT_MAX; ++index) {
        if (pfa->pages[index]) {
            pfa->pages[index] = false;
            return index * KERNAUX_PFA_PAGE_SIZE;
        }
    }

    return 0;
}

void KernAux_PFA_free_page(struct KernAux_PFA *pfa, unsigned int page_addr)
{
    if (page_addr % KERNAUX_PFA_PAGE_SIZE != 0) {
        return;
    }

    pfa->pages[page_addr / KERNAUX_PFA_PAGE_SIZE] = true;
}
