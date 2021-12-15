#ifndef KERNAUX_INCLUDED_LIBC
#define KERNAUX_INCLUDED_LIBC 1

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

void *memset(void *s, int c, size_t n);
size_t strlen(const char *s);
char *strcpy(char *dest, const char *src);

#ifdef __cplusplus
}
#endif

#endif
