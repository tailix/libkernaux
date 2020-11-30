#ifndef KERNAUX_INCLUDED_PFA
#define KERNAUX_INCLUDED_PFA 1

#include <kernaux/stdlib.h>

#define KERNAUX_PFA_ZONES_COUNT_MAX 10
#define KERNAUX_PFA_ZONE_NAME_SIZE_MAX 256
#define KERNAUX_PFA_ZONE_NAME_SLEN_MAX (KERNAUX_PFA_ZONE_NAME_SIZE_MAX - 1)
#define KERNAUX_PFA_PAGE_SIZE (4 * 1024)
#define KERNAUX_PFA_ZONE_PAGES_COUNT_MAX (1024 * 1024)
#define KERNAUX_PFA_ZONE_PAGE_LIST_SIZE (KERNAUX_PFA_ZONE_PAGES_COUNT_MAX / 8)

#ifdef __cplusplus
extern "C" {
#endif

struct KernAux_PFA_Zone {
    char name[KERNAUX_PFA_ZONE_NAME_SIZE_MAX];

    unsigned long long start;
    unsigned long long end;
    unsigned long long size;

    unsigned char pages[KERNAUX_PFA_ZONE_PAGE_LIST_SIZE];
    unsigned int pages_count;
};

struct KernAux_PFA {
    kernaux_bool initialized;

    struct KernAux_PFA_Zone zones[KERNAUX_PFA_ZONES_COUNT_MAX];
    unsigned int zones_count;
};

kernaux_bool KernAux_PFA_initialize_start(
    struct KernAux_PFA *pfa
)
__attribute__((nonnull));

kernaux_bool KernAux_PFA_initialize_add_zone(
    struct KernAux_PFA *pfa,
    const char *name,
    unsigned long long start,
    unsigned long long end
)
__attribute__((nonnull));

kernaux_bool KernAux_PFA_initialize_finish(
    struct KernAux_PFA *pfa
)
__attribute__((nonnull));

#ifdef __cplusplus
}
#endif

#endif
