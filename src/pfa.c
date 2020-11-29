#include <kernaux/pfa.h>

unsigned char KernAux_PFA_initialize_start(
    struct KernAux_PFA *const pfa,
    const unsigned long long page_size
) {
    if (pfa->initialized) {
        return 0;
    }

    if (page_size < KERNAUX_PFA_PAGE_SIZE_MIN) {
        return 0;
    }

    if (page_size > KERNAUX_PFA_PAGE_SIZE_MAX) {
        return 0;
    }

    for (unsigned long long i = 0; i < sizeof(*pfa); ++i) {
        *((unsigned char*)pfa + i) = 0;
    }

    pfa->page_size = page_size;
    pfa->zones_count = 0;
}

unsigned char KernAux_PFA_initialize_add_zone(
    struct KernAux_PFA *const pfa,
    const char *const name,
    const unsigned long long start,
    const unsigned long long end
) {
    if (pfa->initialized) {
        return 0;
    }

    if (pfa->zones_count >= KERNAUX_PFA_ZONES_COUNT_MAX) {
        return 0;
    }
}

unsigned char KernAux_PFA_initialize_finish(
    struct KernAux_PFA *const pfa
) {
    if (pfa->initialized) {
        return 0;
    }
}
