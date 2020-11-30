#include "config.h"

#include <kernaux/pfa.h>

kernaux_bool KernAux_PFA_initialize_start(
    struct KernAux_PFA *const pfa,
    const unsigned long long page_size
) {
    if (pfa->initialized) {
        return KERNAUX_FALSE;
    }

    if (page_size < KERNAUX_PFA_PAGE_SIZE_MIN) {
        return KERNAUX_FALSE;
    }

    if (page_size > KERNAUX_PFA_PAGE_SIZE_MAX) {
        return KERNAUX_FALSE;
    }

    for (unsigned long long i = 0; i < sizeof(*pfa); ++i) {
        *((unsigned char*)pfa + i) = 0;
    }

    pfa->page_size = page_size;
    pfa->zones_count = 0;
}

kernaux_bool KernAux_PFA_initialize_add_zone(
    struct KernAux_PFA *const pfa,
    const char *const name,
    const unsigned long long start,
    const unsigned long long end
) {
    if (pfa->initialized) {
        return KERNAUX_FALSE;
    }

    if (pfa->zones_count >= KERNAUX_PFA_ZONES_COUNT_MAX) {
        return KERNAUX_FALSE;
    }
}

kernaux_bool KernAux_PFA_initialize_finish(
    struct KernAux_PFA *const pfa
) {
    if (pfa->initialized) {
        return KERNAUX_FALSE;
    }
}
