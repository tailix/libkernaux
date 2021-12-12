#ifndef KERNAUX_INCLUDED_STDLIB
#define KERNAUX_INCLUDED_STDLIB 1

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void *kernaux_memset(void *buffer, int value, size_t size)
__attribute__((nonnull));

unsigned int kernaux_strlen(const char *s) __attribute__((nonnull));

char *kernaux_strncpy(
    char *dest,
    const char *src,
    unsigned long slen
)
__attribute__((nonnull));

void kernaux_itoa(int d, char *buf, int base) __attribute__((nonnull));

#ifdef __cplusplus
}
#endif

#endif
