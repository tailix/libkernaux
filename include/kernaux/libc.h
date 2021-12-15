#ifndef KERNAUX_INCLUDED_LIBC
#define KERNAUX_INCLUDED_LIBC 1

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

void *memset(void *s, int c, size_t n);
char *strcpy(char *dest, const char *src);
size_t strlen(const char *s);

#ifdef __cplusplus
}
#endif

#endif
