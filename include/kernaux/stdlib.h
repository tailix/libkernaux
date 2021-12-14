#ifndef KERNAUX_INCLUDED_STDLIB
#define KERNAUX_INCLUDED_STDLIB 1

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

void *kernaux_memset(void *buffer, int value, size_t size);

size_t kernaux_strlen(const char *s);

char *kernaux_strncpy(char *dest, const char *src, size_t slen);

void kernaux_itoa(int d, char *buf, int base);

#ifdef __cplusplus
}
#endif

#endif
