#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/stack_trace.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>

#define MIN_SIZE 20
#define MAX_SIZE (MIN_SIZE + 5)

static size_t min_count = 0;
static const void *min_addresses[MIN_SIZE];

static size_t max_count = 0;
static const void *max_addresses[MAX_SIZE];

#define PREPARE(lower, upper) \
    do { \
        lower##_count = 0; \
        memset(lower##_addresses, 0, sizeof(lower##_addresses)); \
\
        for ( \
            struct KernAux_StackTrace_Frame frame = \
                KernAux_StackTrace_Frame_create(); \
            KernAux_StackTrace_Frame_has_more(&frame); \
            KernAux_StackTrace_Frame_use_next(&frame) \
        ) { \
            assert(lower##_count < upper##_SIZE); \
            lower##_addresses[lower##_count] = \
                KernAux_StackTrace_Frame_get_ptr(&frame); \
            printf("%lu: 0x%p\n", \
                   lower##_count, lower##_addresses[lower##_count]); \
            ++lower##_count; \
        } \
\
        putchar('\n'); \
    } while (0)

void test_main()
{
    PREPARE(min, MIN);

    PREPARE(max, MAX);
    assert(max_count == min_count);
    for (size_t index = 0; index < max_count; ++index) {
        assert(max_addresses[index] == min_addresses[index]);
    }
}
