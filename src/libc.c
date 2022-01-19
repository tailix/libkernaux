#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/libc.h>

#ifdef WITH_LIBC_MEMSET
void *memset(void *s, int c, size_t n)
{
    char *ss = s;
    while (n-- > 0) *ss++ = c;
    return s;
}
#endif // WITH_LIBC_MEMSET

#ifdef WITH_LIBC_STRCPY
char *strcpy(char *dest, const char *src)
{
    char *tmp = dest;
    while ((*dest++ = *src++) != '\0');
    return tmp;
}
#endif // WITH_LIBC_STRCPY

#ifdef WITH_LIBC_STRLEN
size_t strlen(const char *s)
{
    const char *ss = s;
    while (*ss != '\0') ++ss;
    return ss - s;
}
#endif // WITH_LIBC_STRLEN

#ifdef WITH_LIBC_STRNLEN
size_t strnlen(const char *s, size_t maxlen)
{
    const char *ss = s;
    while (*ss != '\0' && maxlen--) ++ss;
    return ss - s;
}
#endif // WITH_LIBC_STRNLEN
