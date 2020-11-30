#include "config.h"

#include <kernaux/pfa.h>
#include <kernaux/stdlib.h>

kernaux_bool KernAux_PFA_initialize_start(
    struct KernAux_PFA *const pfa
) {
    if (pfa->initialized) {
        return KERNAUX_FALSE;
    }

    for (unsigned long long i = 0; i < sizeof(*pfa); ++i) {
        *((unsigned char*)pfa + i) = 0;
    }

    pfa->zones_count = 0;

    return KERNAUX_TRUE;
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

    if (start >= end) {
        return KERNAUX_FALSE;
    }

    if (start % KERNAUX_PFA_PAGE_SIZE != 0) {
        return KERNAUX_FALSE;
    }

    if ((end + 1) % KERNAUX_PFA_PAGE_SIZE != 0) {
        return KERNAUX_FALSE;
    }

    const unsigned int name_slen = kernaux_strlen(name);

    if (name_slen > KERNAUX_PFA_ZONE_NAME_SLEN_MAX) {
        return KERNAUX_FALSE;
    }

    struct KernAux_PFA_Zone *const zone = &pfa->zones[pfa->zones_count++];

    kernaux_strncpy(zone->name, name, name_slen);

    zone->start = start;
    zone->end   = end;
    zone->size  = end - start + 1;

    return KERNAUX_TRUE;
}

kernaux_bool KernAux_PFA_initialize_finish(
    struct KernAux_PFA *const pfa
) {
    if (pfa->initialized) {
        return KERNAUX_FALSE;
    }

    pfa->initialized = KERNAUX_TRUE;

    return KERNAUX_TRUE;
}
