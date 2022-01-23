#ifndef KERNAUX_INCLUDED_LIBC
#define KERNAUX_INCLUDED_LIBC

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

// <ctype.h>
int isdigit(int c);

// <string.h>
void *memset(void *s, int c, size_t n);
char *strcpy(char *dest, const char *src);
size_t strlen(const char *s);
size_t strnlen(const char *s, size_t maxlen);

#ifdef __cplusplus
}
#endif

#endif
